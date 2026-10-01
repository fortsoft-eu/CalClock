/**
 * This is open-source software licensed under the terms of the MIT License.
 *
 * Copyright (c) 2026 Petr Červinka - FortSoft <cervinka@fortsoft.eu>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 **
 * Last modified for version 1.5.1.0
 */

#define NOMINMAX
#include "TimeSignal.h"
#include "NtpClient.h"
#include <algorithm>
#include <atomic>
#include <cmath>
#include <limits>
#include <memory>
#include <mmsystem.h>
#include <new>
#include <vector>

#pragma comment(lib, "Winmm.lib")

using RtlGetVersionFunction = LONG(WINAPI*)(OSVERSIONINFOW*);

/// Stores one six-pip sequence anchored to a system FILETIME target, with sound settings and completion notification.
struct TimeSignalSequence {
    ULONGLONG target = 0;
    bool muted = false;
    bool generatedTone = true;
    double volume = TIME_SIGNAL_VOLUME_DEFAULT;
    HWND notifyWindow = nullptr;
    UINT notifyMessage = 0;
};

/// Describes a scheduled tone interval in 100-nanosecond system-time ticks with normalized amplitude and output mode.
struct TimeSignalTone {
    ULONGLONG start = 0;
    ULONGLONG end = 0;
    double amplitude = 0.0;
    bool generatedTone = true;
};

/// Owns PCM samples and the waveOut header state for one queued generator buffer.
struct TimeSignalWaveBuffer {
    WAVEHDR header = {};
    std::vector<short> samples;
    bool prepared = false;
    bool queued = false;
};

/// Tracks a continuous sine wave's sample origin and zero-crossing end across successive output buffers.
struct TimeSignalPhase {
    LONGLONG origin = 0;
    LONGLONG end = 0;
    bool active = false;
};

static const ULONGLONG FILE_TIME_TICKS_PER_MILLISECOND = 10000;
static const ULONGLONG FILE_TIME_TICKS_PER_SECOND = 10000000;
static const ULONGLONG FILE_TIME_TICKS_PER_MINUTE = 60 * FILE_TIME_TICKS_PER_SECOND;
static const ULONGLONG FILE_TIME_TICKS_PER_DAY = 24 * 60 * FILE_TIME_TICKS_PER_MINUTE;
static const DWORD BEEP_PIP_FREQUENCY = 1000;
static const DWORD BEEP_SHORT_PIP_DURATION = 180;
static const DWORD BEEP_LONG_PIP_DURATION = 950;
static const DWORD GENERATOR_PIP_FREQUENCY = 1000;
static const DWORD GENERATOR_SHORT_PIP_DURATION = 100;
static const DWORD GENERATOR_LONG_PIP_DURATION = 500;
static const DWORD GENERATOR_FADE_DURATION = 1;
static const DWORD GENERATOR_SAMPLE_RATE = 48000;
static const size_t GENERATOR_BUFFER_SAMPLES = 960;
static const size_t GENERATOR_BUFFER_COUNT = 3;
static const double GENERATOR_TONE_AMPLITUDE = 0.28;
static const double PI = 3.14159265358979323846;
static const int TIME_SIGNAL_MINUTES[TIME_SIGNAL_COUNT] = { 0, 1, 5, 10, 15, 20, 30, 60 };

static HANDLE hTimeSignalThread = nullptr;
static HANDLE hTimeSignalStopEvent = nullptr;
static HANDLE hTimeSignalWakeEvent = nullptr;
static SRWLOCK timeSignalScheduleLock = SRWLOCK_INIT;
static std::vector<TimeSignalSequence> timeSignalSequences;
static bool timeSignalPreviewActive = false;
static bool timeSignalPreviewGeneratedTone = true;
static ULONGLONG timeSignalPreviewStart = 0;
static std::atomic<double> timeSignalPreviewVolume = TIME_SIGNAL_VOLUME_DEFAULT;

/// Waits for scheduled intervals and plays each merged interval once through the generator or system Beep.
/// Tracks completed time to avoid replaying already rendered portions.
static DWORD WINAPI TimeSignalThreadProc(void* parameter);

/// Maps the next displayed interval boundary to system FILETIME ticks, preserving fractional widget offsets.
/// Returns false for a disabled or invalid interval or a null output pointer.
bool CalculateTimeSignalTarget(ULONGLONG displayedFileTime, ULONGLONG systemFileTime, TimeSignalMode mode,
        ULONGLONG* targetSystemFileTime) {
    int modeIndex = static_cast<int>(mode);
    if (targetSystemFileTime == nullptr || modeIndex <= TIME_SIGNAL_NONE || modeIndex >= TIME_SIGNAL_COUNT) {
        return false;
    }
    ULONGLONG interval = static_cast<ULONGLONG>(TIME_SIGNAL_MINUTES[modeIndex]) * FILE_TIME_TICKS_PER_MINUTE;
    ULONGLONG remainder = displayedFileTime % interval;
    ULONGLONG untilTarget = remainder == 0 ? interval : interval - remainder;
    *targetSystemFileTime = systemFileTime + untilTarget;
    return true;
}

/// Maps the next occurrence of an alarm's displayed hour and minute to system FILETIME ticks.
/// Selects the following day when that time has already been reached; rejects invalid inputs.
bool CalculateAlarmTimeSignalTarget(ULONGLONG displayedFileTime, ULONGLONG systemFileTime, int alarmHour, int alarmMinute,
        ULONGLONG* targetSystemFileTime) {
    if (targetSystemFileTime == nullptr || alarmHour < 0 || alarmHour > 23 || alarmMinute < 0 || alarmMinute > 59) {
        return false;
    }
    ULONGLONG timeOfDay = displayedFileTime % FILE_TIME_TICKS_PER_DAY;
    ULONGLONG alarmTime = static_cast<ULONGLONG>(alarmHour * 60 + alarmMinute) * FILE_TIME_TICKS_PER_MINUTE;
    ULONGLONG untilTarget = alarmTime > timeOfDay
        ? alarmTime - timeOfDay
        : FILE_TIME_TICKS_PER_DAY - timeOfDay + alarmTime;
    *targetSystemFileTime = systemFileTime + untilTarget;
    return true;
}

/// Tests exact equality of system-time targets so distinct fractional offsets remain separate.
bool TimeSignalTargetsCoincide(ULONGLONG left, ULONGLONG right) {
    ULONGLONG difference = left >= right ? left - right : right - left;
    return difference == 0;
}

/// Caches whether the Windows version requires generated audio instead of system Beep output.
bool IsTimeSignalGeneratorRequired() {
    static int result = -1;
    if (result >= 0) {
        return result != 0;
    }
    result = 0;
    HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
    RtlGetVersionFunction getVersion = nullptr;
    if (ntdll != nullptr) {
        getVersion = reinterpret_cast<RtlGetVersionFunction>(GetProcAddress(ntdll, "RtlGetVersion"));
    }
    if (getVersion == nullptr) {
        return false;
    }
    OSVERSIONINFOW version = {};
    version.dwOSVersionInfoSize = sizeof(version);
    if (getVersion(&version) == 0 && version.dwMajorVersion == 6 && version.dwMinorVersion == 0) {
        result = 1;
    }
    return result != 0;
}

/// Maps an integer stored volume step to normalized amplitude, preserving the default -18 dB and full-scale endpoints.
static double TimeSignalAmplitudeAtStep(int volume) {
    if (volume == TIME_SIGNAL_VOLUME_MAX) {
        return 1.0;
    }
    if (volume == TIME_SIGNAL_VOLUME_DEFAULT) {
        return std::pow(10.0, -18.0 / 20.0);
    }
    return GENERATOR_TONE_AMPLITUDE * volume / 100.0;
}

/// Interpolates stored volume steps into normalized amplitude; clamps the range and silences nonfinite values.
static double TimeSignalAmplitude(double volume) {
    if (!std::isfinite(volume)) {
        return 0.0;
    }
    volume = std::clamp<double>(volume, TIME_SIGNAL_VOLUME_MIN, TIME_SIGNAL_VOLUME_MAX);
    int lower = static_cast<int>(volume);
    int upper = std::min<int>(lower + 1, TIME_SIGNAL_VOLUME_MAX);
    double lowAmplitude = TimeSignalAmplitudeAtStep(lower);
    return lowAmplitude + (TimeSignalAmplitudeAtStep(upper) - lowAmplitude) * (volume - lower);
}

/// Converts stored generator volume to decibels relative to full-scale sine amplitude.
/// Returns negative infinity for silence.
double TimeSignalVolumeDecibels(double volume) {
    double amplitude = TimeSignalAmplitude(volume);
    if (amplitude == 0.0) {
        return -std::numeric_limits<double>::infinity();
    }
    return 20.0 * std::log10(amplitude);
}

/// Converts generator decibels to the interpolated stored volume scale, limiting positive levels to full scale.
double TimeSignalVolumeFromDecibels(double decibels) {
    if (std::isnan(decibels)) {
        return TIME_SIGNAL_VOLUME_MIN;
    }
    double amplitude = std::pow(10.0, std::min<double>(decibels, 0.0) / 20.0);
    int lower = TIME_SIGNAL_VOLUME_MIN;
    int upper = TIME_SIGNAL_VOLUME_MAX;
    while (upper - lower > 1) {
        int middle = lower + (upper - lower) / 2;
        if (TimeSignalAmplitudeAtStep(middle) < amplitude) {
            lower = middle;
        } else {
            upper = middle;
        }
    }
    double lowAmplitude = TimeSignalAmplitudeAtStep(lower);
    double highAmplitude = TimeSignalAmplitudeAtStep(upper);
    return lower + (amplitude - lowAmplitude) / (highAmplitude - lowAmplitude);
}

/// Returns the short or long pip duration in milliseconds for the selected output method.
static DWORD TimeSignalToneDuration(bool longTone, bool generatedTone) {
    if (generatedTone) {
        return longTone ? GENERATOR_LONG_PIP_DURATION : GENERATOR_SHORT_PIP_DURATION;
    }
    return longTone ? BEEP_LONG_PIP_DURATION : BEEP_SHORT_PIP_DURATION;
}

/// Collects scheduled and preview pips intersecting the requested system-time range under the schedule lock.
/// Removes completed sequences and posts their completion notifications; preview pips follow whole seconds.
static std::vector<TimeSignalTone> CollectTimeSignalTones(ULONGLONG from, ULONGLONG through) {
    std::vector<TimeSignalTone> tones;
    AcquireSRWLockExclusive(&timeSignalScheduleLock);
    bool stopping = WaitForSingleObject(hTimeSignalStopEvent, 0) == WAIT_OBJECT_0;
    for (size_t index = 0; index < timeSignalSequences.size();) {
        const TimeSignalSequence& sequence = timeSignalSequences[index];
        ULONGLONG end = sequence.target
            + TimeSignalToneDuration(true, sequence.generatedTone) * FILE_TIME_TICKS_PER_MILLISECOND;
        if (end < from) {
            PostMessageW(sequence.notifyWindow, sequence.notifyMessage, 0, 0);
            timeSignalSequences.erase(timeSignalSequences.begin() + index);
            continue;
        }
        if (!sequence.muted && !stopping) {
            for (int pip = 0; pip <= 5; pip++) {
                ULONGLONG start = sequence.target - (5ULL - pip) * FILE_TIME_TICKS_PER_SECOND;
                bool generatedTone = timeSignalPreviewActive ? timeSignalPreviewGeneratedTone : sequence.generatedTone;
                double volume = timeSignalPreviewActive ? timeSignalPreviewVolume.load() : sequence.volume;
                ULONGLONG finish = start
                    + TimeSignalToneDuration(pip == 5, generatedTone) * FILE_TIME_TICKS_PER_MILLISECOND;
                if (finish >= from && start <= through) {
                    tones.push_back(TimeSignalTone{ start, finish, TimeSignalAmplitude(volume), generatedTone });
                }
            }
        }
        index++;
    }
    if (timeSignalPreviewActive && !stopping) {
        ULONGLONG start = std::max(timeSignalPreviewStart, from / FILE_TIME_TICKS_PER_SECOND * FILE_TIME_TICKS_PER_SECOND);
        for (; start <= through; start += FILE_TIME_TICKS_PER_SECOND) {
            bool longTone = start / FILE_TIME_TICKS_PER_SECOND % 5 == 0;
            ULONGLONG end = start
                + TimeSignalToneDuration(longTone, timeSignalPreviewGeneratedTone) * FILE_TIME_TICKS_PER_MILLISECOND;
            if (end >= from) {
                tones.push_back(TimeSignalTone{
                    start,
                    end,
                    TimeSignalAmplitude(timeSignalPreviewVolume.load()),
                    timeSignalPreviewGeneratedTone
                });
            }
        }
    }
    ReleaseSRWLockExclusive(&timeSignalScheduleLock);
    return tones;
}

/// Unions overlapping or touching tone intervals, keeping the greatest amplitude and any generator requirement.
static std::vector<TimeSignalTone> MergeTimeSignalTones(std::vector<TimeSignalTone> tones) {
    std::sort(tones.begin(), tones.end(), [](const TimeSignalTone& left, const TimeSignalTone& right) {
        return left.start < right.start;
    });
    std::vector<TimeSignalTone> merged;
    for (const TimeSignalTone& tone : tones) {
        if (!merged.empty() && tone.start <= merged.back().end) {
            merged.back().end = std::max(merged.back().end, tone.end);
            merged.back().amplitude = std::max(merged.back().amplitude, tone.amplitude);
            merged.back().generatedTone = merged.back().generatedTone || tone.generatedTone;
        } else {
            merged.push_back(tone);
        }
    }
    return merged;
}

/// Converts a system FILETIME timestamp to a signed sample offset from base, rounding toward the next sample.
static LONGLONG TimeSignalSamplePosition(ULONGLONG time, ULONGLONG base) {
    LONGLONG difference = time >= base ? static_cast<LONGLONG>(time - base) : -static_cast<LONGLONG>(base - time);
    return static_cast<LONGLONG>(std::ceil(static_cast<double>(difference) * GENERATOR_SAMPLE_RATE
        / FILE_TIME_TICKS_PER_SECOND));
}

/// Fills a PCM buffer from merged intervals while retaining oscillator phase across uninterrupted sound.
/// Starts at zero, extends each continuous segment to a full cycle, and applies a short endpoint envelope.
static void RenderTimeSignalSamples(const std::vector<TimeSignalTone>& intervals, ULONGLONG base, LONGLONG firstSample,
        std::vector<short>* samples, TimeSignalPhase* phase) {
    const LONGLONG cycle = GENERATOR_SAMPLE_RATE / GENERATOR_PIP_FREQUENCY;
    const LONGLONG fade = GENERATOR_SAMPLE_RATE * GENERATOR_FADE_DURATION / 1000;
    size_t intervalIndex = 0;
    for (size_t index = 0; index < samples->size(); index++) {
        LONGLONG sample = firstSample + index;
        while (intervalIndex < intervals.size() && TimeSignalSamplePosition(intervals[intervalIndex].end, base) < sample) {
            if (phase->active && sample <= phase->end) {
                break;
            }
            intervalIndex++;
        }
        short value = 0;
        if (intervalIndex < intervals.size()) {
            const TimeSignalTone& interval = intervals[intervalIndex];
            LONGLONG start = TimeSignalSamplePosition(interval.start, base);
            LONGLONG end = TimeSignalSamplePosition(interval.end, base);
            if (sample >= start) {
                if (!phase->active || start > phase->end) {
                    phase->origin = start;
                    phase->active = true;
                }
                phase->end = phase->origin + (end - phase->origin + cycle - 1) / cycle * cycle;
                if (sample <= phase->end) {
                    double envelope = std::clamp(
                        static_cast<double>(std::min(sample - phase->origin, phase->end - sample)) / fade, 0.0, 1.0);
                    double angle = 2.0 * PI * ((sample - phase->origin) % cycle) / cycle;
                    value = static_cast<short>(
                        std::lround(32767.0 * std::clamp(interval.amplitude, 0.0, 1.0) * envelope * std::sin(angle)));
                }
            }
        }
        if (phase->active && sample > phase->end) {
            phase->active = false;
        }
        (*samples)[index] = value;
    }
}

/// Tests under the schedule lock whether sequences or a preview remain and no stop has been requested.
static bool HasTimeSignalWork() {
    AcquireSRWLockShared(&timeSignalScheduleLock);
    bool work = !timeSignalSequences.empty() || timeSignalPreviewActive;
    ReleaseSRWLockShared(&timeSignalScheduleLock);
    return work && WaitForSingleObject(hTimeSignalStopEvent, 0) != WAIT_OBJECT_0;
}

/// Returns the active preview's output choice, or fallback when no preview is running.
static bool TimeSignalOutputUsesGenerator(bool fallback) {
    AcquireSRWLockShared(&timeSignalScheduleLock);
    bool generated = timeSignalPreviewActive ? timeSignalPreviewGeneratedTone : fallback;
    ReleaseSRWLockShared(&timeSignalScheduleLock);
    return generated;
}

/// Streams merged pips through waveOut, retaining phase and held intervals across output buffers.
/// Drains and releases audio resources before returning; optionally reports the system time rendered through.
static bool PlayGeneratedTimeSignals(ULONGLONG base, ULONGLONG* playedThrough = nullptr) {
    HANDLE completedEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (completedEvent == nullptr) {
        return false;
    }
    WAVEFORMATEX format = {};
    format.wFormatTag = WAVE_FORMAT_PCM;
    format.nChannels = 1;
    format.nSamplesPerSec = GENERATOR_SAMPLE_RATE;
    format.wBitsPerSample = 16;
    format.nBlockAlign = 2;
    format.nAvgBytesPerSec = GENERATOR_SAMPLE_RATE * 2;
    HWAVEOUT output = nullptr;
    if (waveOutOpen(&output, WAVE_MAPPER, &format, reinterpret_cast<DWORD_PTR>(completedEvent), 0, CALLBACK_EVENT) !=
            MMSYSERR_NOERROR) {
        CloseHandle(completedEvent);
        return false;
    }
    TimeSignalWaveBuffer buffers[GENERATOR_BUFFER_COUNT];
    bool ready = true;
    for (TimeSignalWaveBuffer& buffer : buffers) {
        buffer.samples.resize(GENERATOR_BUFFER_SAMPLES);
        buffer.header.lpData = reinterpret_cast<LPSTR>(buffer.samples.data());
        buffer.header.dwBufferLength = static_cast<DWORD>(buffer.samples.size() * sizeof(short));
        buffer.prepared = waveOutPrepareHeader(output, &buffer.header, sizeof(buffer.header)) == MMSYSERR_NOERROR;
        ready = ready && buffer.prepared;
    }
    LONGLONG nextSample = 0;
    size_t nextBuffer = 0;
    TimeSignalPhase phase;
    std::vector<TimeSignalTone> held;
    while (ready) {
        TimeSignalWaveBuffer& buffer = buffers[nextBuffer];
        while (buffer.queued && (buffer.header.dwFlags & WHDR_DONE) == 0) {
            WaitForSingleObject(completedEvent, INFINITE);
        }
        buffer.queued = false;
        ULONGLONG from = base + nextSample * FILE_TIME_TICKS_PER_SECOND / GENERATOR_SAMPLE_RATE;
        std::vector<TimeSignalTone> tones = CollectTimeSignalTones(from, from + FILE_TIME_TICKS_PER_SECOND);
        size_t toneCount = 0;
        for (const TimeSignalTone& tone : tones) {
            if (tone.start >= from) {
                tones[toneCount] = tone;
                toneCount++;
            }
        }
        tones.resize(toneCount);
        size_t heldCount = 0;
        for (const TimeSignalTone& tone : held) {
            if (tone.end + FILE_TIME_TICKS_PER_MILLISECOND >= from) {
                held[heldCount] = tone;
                heldCount++;
            }
        }
        held.resize(heldCount);
        tones.insert(tones.end(), held.begin(), held.end());
        ULONGLONG bufferEnd = from + GENERATOR_BUFFER_SAMPLES * FILE_TIME_TICKS_PER_SECOND / GENERATOR_SAMPLE_RATE;
        for (const TimeSignalTone& tone : tones) {
            bool shouldHoldTone = tone.start < bufferEnd && tone.end >= bufferEnd;
            if (shouldHoldTone) {
                for (const TimeSignalTone& item : held) {
                    if (item.start == tone.start && item.end == tone.end) {
                        shouldHoldTone = false;
                        break;
                    }
                }
            }
            if (shouldHoldTone) {
                held.push_back(tone);
            }
        }
        std::vector<TimeSignalTone> intervals = MergeTimeSignalTones(tones);
        bool hasWork = HasTimeSignalWork();
        if (!phase.active || nextSample > phase.end) {
            ULONGLONG bufferedDuration = GENERATOR_BUFFER_COUNT * GENERATOR_BUFFER_SAMPLES * FILE_TIME_TICKS_PER_SECOND
                / GENERATOR_SAMPLE_RATE;
            bool gap = held.empty() && (intervals.empty() || intervals.front().start > bufferEnd + bufferedDuration);
            if (gap || intervals.empty() && !hasWork || !TimeSignalOutputUsesGenerator(true)) {
                break;
            }
        }
        RenderTimeSignalSamples(intervals, base, nextSample, &buffer.samples, &phase);
        ready = waveOutWrite(output, &buffer.header, sizeof(buffer.header)) == MMSYSERR_NOERROR;
        buffer.queued = ready;
        if (ready) {
            nextSample += buffer.samples.size();
        }
        nextBuffer = (nextBuffer + 1) % GENERATOR_BUFFER_COUNT;
    }
    for (TimeSignalWaveBuffer& buffer : buffers) {
        while (buffer.queued && (buffer.header.dwFlags & WHDR_DONE) == 0) {
            WaitForSingleObject(completedEvent, INFINITE);
        }
        if (buffer.prepared) {
            waveOutUnprepareHeader(output, &buffer.header, sizeof(buffer.header));
        }
    }
    waveOutClose(output);
    CloseHandle(completedEvent);
    if (playedThrough != nullptr) {
        *playedThrough = base + nextSample * FILE_TIME_TICKS_PER_SECOND / GENERATOR_SAMPLE_RATE;
    }
    return ready;
}

/// Extends the planning horizon until the first merged tone's end is known, avoiding premature Beep interruptions.
static std::vector<TimeSignalTone> PlanTimeSignalIntervals(ULONGLONG now) {
    ULONGLONG through = now + 7 * FILE_TIME_TICKS_PER_SECOND;
    while (true) {
        std::vector<TimeSignalTone> intervals = MergeTimeSignalTones(CollectTimeSignalTones(now, through));
        if (intervals.empty() || intervals.front().end + FILE_TIME_TICKS_PER_SECOND < through) {
            return intervals;
        }
        through = intervals.front().end + 2 * FILE_TIME_TICKS_PER_SECOND;
    }
}

/// Waits for scheduled intervals and plays each merged interval once through the generator or system Beep.
/// Tracks completed time to avoid replaying already rendered portions.
static DWORD WINAPI TimeSignalThreadProc(void*) {
    HANDLE events[] = { hTimeSignalStopEvent, hTimeSignalWakeEvent };
    ULONGLONG playedUntil = 0;
    while (WaitForSingleObject(hTimeSignalStopEvent, 0) != WAIT_OBJECT_0) {
        ULONGLONG now = CurrentFileTimeValue();
        std::vector<TimeSignalTone> intervals = PlanTimeSignalIntervals(now);
        size_t intervalCount = 0;
        for (const TimeSignalTone& tone : intervals) {
            if (tone.end > playedUntil) {
                intervals[intervalCount] = tone;
                intervalCount++;
            }
        }
        intervals.resize(intervalCount);
        if (intervals.empty()) {
            WaitForMultipleObjects(ARRAYSIZE(events), events, FALSE, 50);
            continue;
        }
        TimeSignalTone tone = intervals.front();
        if (tone.start > now) {
            ULONGLONG remaining = tone.start - now;
            DWORD milliseconds = static_cast<DWORD>(std::min<ULONGLONG>(remaining / FILE_TIME_TICKS_PER_MILLISECOND, 50));
            if (milliseconds > 1) {
                WaitForMultipleObjects(ARRAYSIZE(events), events, FALSE, milliseconds - 1);
            } else {
                YieldProcessor();
            }
            continue;
        }
        ULONGLONG playedThrough = now;
        if (TimeSignalOutputUsesGenerator(tone.generatedTone)) {
            if (!PlayGeneratedTimeSignals(tone.start, &playedThrough)) {
                WaitForMultipleObjects(ARRAYSIZE(events), events, FALSE, 100);
            }
        } else {
            DWORD duration = static_cast<DWORD>(std::max<ULONGLONG>(1, (tone.end - now +
                FILE_TIME_TICKS_PER_MILLISECOND - 1) / FILE_TIME_TICKS_PER_MILLISECOND));
            Beep(BEEP_PIP_FREQUENCY, duration);
            playedThrough = tone.end;
        }
        playedUntil = std::max(playedUntil, playedThrough);
    }
    return 0;
}

/// Creates the shared playback worker and its events if needed, cleaning up handles on failure.
static bool EnsureTimeSignalThread() {
    if (hTimeSignalThread != nullptr) {
        return true;
    }
    hTimeSignalStopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    hTimeSignalWakeEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (hTimeSignalStopEvent != nullptr && hTimeSignalWakeEvent != nullptr) {
        hTimeSignalThread = CreateThread(nullptr, 0, TimeSignalThreadProc, nullptr, 0, nullptr);
    }
    if (hTimeSignalThread != nullptr) {
        return true;
    }
    if (hTimeSignalStopEvent != nullptr) {
        CloseHandle(hTimeSignalStopEvent);
    }
    if (hTimeSignalWakeEvent != nullptr) {
        CloseHandle(hTimeSignalWakeEvent);
    }
    hTimeSignalStopEvent = nullptr;
    hTimeSignalWakeEvent = nullptr;
    return false;
}

/// Stops, joins, and releases the shared worker only when neither scheduled sequences nor a preview remain.
static void StopIdleTimeSignalThread() {
    if (hTimeSignalThread == nullptr || HasTimeSignalWork()) {
        return;
    }
    SetEvent(hTimeSignalStopEvent);
    WaitForSingleObject(hTimeSignalThread, INFINITE);
    CloseHandle(hTimeSignalThread);
    CloseHandle(hTimeSignalStopEvent);
    CloseHandle(hTimeSignalWakeEvent);
    hTimeSignalThread = nullptr;
    hTimeSignalStopEvent = nullptr;
    hTimeSignalWakeEvent = nullptr;
}

/// Schedules a six-pip sequence whose final pip starts at targetSystemFileTime in system FILETIME ticks.
/// Deduplicates identical targets and starts the worker as needed; returns false for invalid notification data or
/// startup failure.
bool StartTimeSignalPlayback(ULONGLONG targetSystemFileTime, bool muted, bool generatedTone, double volume,
        HWND notifyWindow, UINT notifyMessage) {
    if (targetSystemFileTime < 5 * FILE_TIME_TICKS_PER_SECOND
            || notifyWindow == nullptr
            || notifyMessage == 0
            || !EnsureTimeSignalThread()) {
        return false;
    }
    AcquireSRWLockExclusive(&timeSignalScheduleLock);
    auto existing = timeSignalSequences.begin();
    while (existing != timeSignalSequences.end()) {
        if (existing->target == targetSystemFileTime) {
            break;
        }
        existing++;
    }
    if (existing == timeSignalSequences.end()) {
        timeSignalSequences.push_back(TimeSignalSequence{
            targetSystemFileTime,
            muted,
            IsTimeSignalGeneratorRequired() || generatedTone,
            std::clamp<double>(volume, TIME_SIGNAL_VOLUME_MIN, TIME_SIGNAL_VOLUME_MAX),
            notifyWindow,
            notifyMessage
        });
    }
    ReleaseSRWLockExclusive(&timeSignalScheduleLock);
    SetEvent(hTimeSignalWakeEvent);
    return true;
}

/// Shifts scheduled widget and alarm targets by a signed FILETIME adjustment after an application-clock correction.
/// Updates all targets under one lock, preserves preview timing, and wakes the worker to replan pending pips.
void AdjustTimeSignalPlaybackTime(LONGLONG adjustment) {
    AcquireSRWLockExclusive(&timeSignalScheduleLock);
    for (TimeSignalSequence& sequence : timeSignalSequences) {
        sequence.target = static_cast<ULONGLONG>(static_cast<LONGLONG>(sequence.target) + adjustment);
    }
    ReleaseSRWLockExclusive(&timeSignalScheduleLock);
    if (hTimeSignalWakeEvent != nullptr) {
        SetEvent(hTimeSignalWakeEvent);
    }
}

/// Changes the mute state of the sequence with the given system-time target and wakes the playback worker.
void SetTimeSignalMuted(ULONGLONG target, bool muted) {
    AcquireSRWLockExclusive(&timeSignalScheduleLock);
    for (TimeSignalSequence& sequence : timeSignalSequences) {
        if (sequence.target == target) {
            sequence.muted = muted;
        }
    }
    ReleaseSRWLockExclusive(&timeSignalScheduleLock);
    if (hTimeSignalWakeEvent != nullptr) {
        SetEvent(hTimeSignalWakeEvent);
    }
}

/// Removes matching scheduled sequences and releases the worker if no other playback work remains.
void CancelTimeSignalPlayback(ULONGLONG target) {
    AcquireSRWLockExclusive(&timeSignalScheduleLock);
    for (auto sequence = timeSignalSequences.begin(); sequence != timeSignalSequences.end();) {
        if (sequence->target == target) {
            sequence = timeSignalSequences.erase(sequence);
        } else {
            sequence++;
        }
    }
    ReleaseSRWLockExclusive(&timeSignalScheduleLock);
    StopIdleTimeSignalThread();
}

/// Atomically updates the preview volume after clamping it to the stored generator-volume range.
void SetTimeSignalPreviewVolume(double volume) {
    timeSignalPreviewVolume.store(std::clamp<double>(volume, TIME_SIGNAL_VOLUME_MIN, TIME_SIGNAL_VOLUME_MAX));
}

/// Starts or updates a preview merged with scheduled pips, beginning on the next whole system second.
/// Uses a long pip every fifth second and returns false if the playback worker cannot start.
bool StartTimeSignalVolumePreview(bool generatedTone, double volume) {
    if (!EnsureTimeSignalThread()) {
        return false;
    }
    SetTimeSignalPreviewVolume(volume);
    AcquireSRWLockExclusive(&timeSignalScheduleLock);
    timeSignalPreviewGeneratedTone = IsTimeSignalGeneratorRequired() || generatedTone;
    if (!timeSignalPreviewActive) {
        timeSignalPreviewStart = (CurrentFileTimeValue() / FILE_TIME_TICKS_PER_SECOND + 1) * FILE_TIME_TICKS_PER_SECOND;
        timeSignalPreviewActive = true;
    }
    ReleaseSRWLockExclusive(&timeSignalScheduleLock);
    SetEvent(hTimeSignalWakeEvent);
    return true;
}

/// Disables preview pips and releases the worker when no scheduled sequences remain.
void StopTimeSignalVolumePreview() {
    AcquireSRWLockExclusive(&timeSignalScheduleLock);
    timeSignalPreviewActive = false;
    ReleaseSRWLockExclusive(&timeSignalScheduleLock);
    StopIdleTimeSignalThread();
}

/// Releases an idle playback worker after sequence completion has been reported.
void FinishTimeSignalPlayback() {
    StopIdleTimeSignalThread();
}

/// Clears all scheduled sequences and releases the worker if no preview remains active.
void StopTimeSignalPlayback() {
    AcquireSRWLockExclusive(&timeSignalScheduleLock);
    timeSignalSequences.clear();
    ReleaseSRWLockExclusive(&timeSignalScheduleLock);
    StopIdleTimeSignalThread();
}

/// Reports whether scheduled sequences remain, excluding preview-only playback.
bool IsTimeSignalPlaybackRunning() {
    AcquireSRWLockShared(&timeSignalScheduleLock);
    bool running = !timeSignalSequences.empty();
    ReleaseSRWLockShared(&timeSignalScheduleLock);
    return running;
}
