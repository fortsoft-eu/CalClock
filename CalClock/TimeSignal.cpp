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
 * Last modified for version 1.7.0.0
 */

#define NOMINMAX
#include "TimeSignal.h"
#include "AudioOutput.h"
#include "ClockTime.h"
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

/// Stores one six-pip sequence anchored to a continuous FILETIME target, with sound settings and completion
/// notification.
struct TimeSignalSequence {
    ULONGLONG target = 0;
    bool muted = false;
    bool generatedTone = true;
    double volume = TIME_SIGNAL_VOLUME_DEFAULT;
    HWND notifyWindow = nullptr;
    UINT notifyMessage = 0;
};

/// Describes a scheduled tone interval in 100-nanosecond continuous-clock ticks with normalized amplitude
/// and output mode.
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

/// Owns one endpoint's original scheduler, PCM phase, preview state and worker lifetime independently of other
/// outputs.
struct TimeSignalOutputRoute {
    std::wstring device;
    HANDLE thread = nullptr;
    HANDLE stopEvent = nullptr;
    HANDLE wakeEvent = nullptr;
    SRWLOCK lock = SRWLOCK_INIT;
    std::vector<TimeSignalSequence> sequences;
    bool previewActive = false;
    bool previewGeneratedTone = true;
    ULONGLONG previewStart = 0;
    std::atomic<double> previewVolume = TIME_SIGNAL_VOLUME_DEFAULT;
    std::atomic<bool> beepActive = false;
};

static const ULONGLONG FILE_TIME_TICKS_PER_MILLISECOND = 10000;
static const ULONGLONG FILE_TIME_TICKS_PER_SECOND = 10000000;
static const ULONGLONG FILE_TIME_TICKS_PER_MINUTE = 60 * FILE_TIME_TICKS_PER_SECOND;
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

static std::vector<std::unique_ptr<TimeSignalOutputRoute>> timeSignalOutputs;

/// Waits for scheduled intervals and plays each merged interval once through the generator or system Beep.
/// Tracks completed time to avoid replaying already rendered portions.
static DWORD WINAPI TimeSignalThreadProc(void* parameter);

/// Reports whether a displayed FILETIME value is an exact boundary of the enabled signal interval.
bool IsTimeSignalBoundary(ULONGLONG displayedFileTime, TimeSignalMode mode) {
    int modeIndex = static_cast<int>(mode);
    if (modeIndex <= TIME_SIGNAL_NONE || modeIndex >= TIME_SIGNAL_COUNT) {
        return false;
    }
    ULONGLONG interval = static_cast<ULONGLONG>(TIME_SIGNAL_MINUTES[modeIndex]) * FILE_TIME_TICKS_PER_MINUTE;
    return displayedFileTime % interval == 0;
}

/// Maps the next displayed interval boundary to continuous FILETIME ticks, preserving fractional widget
/// offsets. Returns false for a disabled or invalid interval or a null output pointer.
bool CalculateTimeSignalTarget(ULONGLONG displayedFileTime, ULONGLONG timelineFileTime, TimeSignalMode mode,
        ULONGLONG* targetTimelineFileTime) {
    int modeIndex = static_cast<int>(mode);
    if (targetTimelineFileTime == nullptr || modeIndex <= TIME_SIGNAL_NONE || modeIndex >= TIME_SIGNAL_COUNT) {
        return false;
    }
    ULONGLONG interval = static_cast<ULONGLONG>(TIME_SIGNAL_MINUTES[modeIndex]) * FILE_TIME_TICKS_PER_MINUTE;
    ULONGLONG untilTarget = interval - displayedFileTime % interval;
    *targetTimelineFileTime = timelineFileTime + untilTarget;
    return true;
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

/// Maps an integer stored volume step to normalized amplitude, preserving the default -18 dB and full-scale
/// endpoints.
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

/// Collects scheduled and preview pips intersecting the requested continuous-clock range under the schedule
/// lock. Removes completed sequences and posts their completion notifications; preview pips follow whole
/// seconds.
static std::vector<TimeSignalTone> CollectTimeSignalTones(TimeSignalOutputRoute& route,
        ULONGLONG from, ULONGLONG through) {
    std::vector<TimeSignalTone> tones;
    AcquireSRWLockExclusive(&route.lock);
    bool stopping = WaitForSingleObject(route.stopEvent, 0) == WAIT_OBJECT_0;
    for (size_t index = 0; index < route.sequences.size();) {
        const TimeSignalSequence& sequence = route.sequences[index];
        ULONGLONG end = sequence.target + TimeSignalToneDuration(true, sequence.generatedTone)
            * FILE_TIME_TICKS_PER_MILLISECOND;
        if (end < from) {
            PostMessageW(sequence.notifyWindow, sequence.notifyMessage, 0, 0);
            route.sequences.erase(route.sequences.begin() + index);
            continue;
        }
        if (!sequence.muted && !stopping) {
            for (int pip = 0; pip <= 5; pip++) {
                ULONGLONG start = sequence.target - (5ULL - pip) * FILE_TIME_TICKS_PER_SECOND;
                bool generatedTone = route.previewActive ? route.previewGeneratedTone : sequence.generatedTone;
                double volume = route.previewActive ? route.previewVolume.load() : sequence.volume;
                ULONGLONG finish =
                    start + TimeSignalToneDuration(pip == 5, generatedTone) * FILE_TIME_TICKS_PER_MILLISECOND;
                if (finish >= from && start <= through) {
                    TimeSignalTone tone = { start, finish, TimeSignalAmplitude(volume), generatedTone };
                    tones.push_back(std::move(tone));
                }
            }
        }
        index++;
    }
    if (route.previewActive && !stopping) {
        ULONGLONG start =
            std::max(route.previewStart, from / FILE_TIME_TICKS_PER_SECOND * FILE_TIME_TICKS_PER_SECOND);
        for (; start <= through; start += FILE_TIME_TICKS_PER_SECOND) {
            bool longTone = start / FILE_TIME_TICKS_PER_SECOND % 5 == 0;
            ULONGLONG end = start + TimeSignalToneDuration(longTone, route.previewGeneratedTone)
                * FILE_TIME_TICKS_PER_MILLISECOND;
            if (end >= from) {
                tones.push_back(TimeSignalTone{
                    start,
                    end,
                    TimeSignalAmplitude(route.previewVolume.load()),
                    route.previewGeneratedTone
                });
            }
        }
    }
    ReleaseSRWLockExclusive(&route.lock);
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

/// Converts a continuous FILETIME timestamp to a signed sample offset from base, rounding toward the next
/// sample.
static LONGLONG TimeSignalSamplePosition(ULONGLONG time, ULONGLONG base) {
    LONGLONG difference = time >= base
        ? static_cast<LONGLONG>(time - base)
        : -static_cast<LONGLONG>(base - time);
    return static_cast<LONGLONG>(std::ceil(static_cast<double>(difference) * GENERATOR_SAMPLE_RATE
        / FILE_TIME_TICKS_PER_SECOND));
}

/// Fills a PCM buffer from merged intervals while retaining oscillator phase across uninterrupted sound.
/// Starts at zero, extends each continuous segment to a full cycle, and applies a short endpoint envelope.
static void RenderTimeSignalSamples(const std::vector<TimeSignalTone>& intervals, ULONGLONG base,
        LONGLONG firstSample, std::vector<short>* samples, TimeSignalPhase* phase) {
    const LONGLONG cycle = GENERATOR_SAMPLE_RATE / GENERATOR_PIP_FREQUENCY;
    const LONGLONG fade = GENERATOR_SAMPLE_RATE * GENERATOR_FADE_DURATION / 1000;
    size_t intervalIndex = 0;
    for (size_t index = 0; index < samples->size(); index++) {
        LONGLONG sample = firstSample + index;
        while (intervalIndex < intervals.size()
                && TimeSignalSamplePosition(intervals[intervalIndex].end, base) < sample) {
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
                    double envelope = std::clamp(static_cast<double>(std::min(sample - phase->origin,
                        phase->end - sample)) / fade, 0.0, 1.0);
                    double angle = 2.0 * PI * ((sample - phase->origin) % cycle) / cycle;
                    value = static_cast<short>(std::lround(32767.0 * std::clamp(interval.amplitude, 0.0, 1.0)
                        * envelope * std::sin(angle)));
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
static bool HasTimeSignalWork(TimeSignalOutputRoute& route) {
    AcquireSRWLockShared(&route.lock);
    bool work = !route.sequences.empty() || route.previewActive;
    ReleaseSRWLockShared(&route.lock);
    return work && WaitForSingleObject(route.stopEvent, 0) != WAIT_OBJECT_0;
}

/// Returns the active preview's output choice, or fallback when no preview is running.
static bool TimeSignalOutputUsesGenerator(TimeSignalOutputRoute& route, bool fallback) {
    AcquireSRWLockShared(&route.lock);
    bool generated = route.previewActive ? route.previewGeneratedTone : fallback;
    ReleaseSRWLockShared(&route.lock);
    return generated;
}

/// Streams merged pips through waveOut, retaining phase and held intervals across output buffers. Drains
/// and releases audio resources before returning; optionally reports the continuous time rendered through.
static bool PlayGeneratedTimeSignals(TimeSignalOutputRoute& route, ULONGLONG base,
        ULONGLONG* playedThrough = nullptr) {
    std::wstring endpoint;
    UINT deviceId = WAVE_MAPPER;
    if (!ResolveAudioOutputDevice(route.device, &endpoint, &deviceId)) {
        return false;
    }
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
    if (waveOutOpen(&output, deviceId, &format, reinterpret_cast<DWORD_PTR>(completedEvent), 0, CALLBACK_EVENT)
            != MMSYSERR_NOERROR) {
        CloseHandle(completedEvent);
        return false;
    }
    TimeSignalWaveBuffer buffers[GENERATOR_BUFFER_COUNT];
    bool ready = true;
    for (TimeSignalWaveBuffer& buffer : buffers) {
        buffer.samples.resize(GENERATOR_BUFFER_SAMPLES);
        buffer.header.lpData = reinterpret_cast<LPSTR>(buffer.samples.data());
        buffer.header.dwBufferLength = static_cast<DWORD>(buffer.samples.size() * sizeof(short));
        buffer.prepared =
            waveOutPrepareHeader(output, &buffer.header, sizeof(buffer.header)) == MMSYSERR_NOERROR;
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
        std::vector<TimeSignalTone> tones =
            CollectTimeSignalTones(route, from, from + FILE_TIME_TICKS_PER_SECOND);
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
        ULONGLONG bufferEnd =
            from + GENERATOR_BUFFER_SAMPLES * FILE_TIME_TICKS_PER_SECOND / GENERATOR_SAMPLE_RATE;
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
        if (!phase.active || nextSample > phase.end) {
            ULONGLONG bufferedDuration = GENERATOR_BUFFER_COUNT * GENERATOR_BUFFER_SAMPLES
                * FILE_TIME_TICKS_PER_SECOND / GENERATOR_SAMPLE_RATE;
            bool gap = held.empty() && (intervals.empty()
                || intervals.front().start > bufferEnd + bufferedDuration);
            if (gap || !TimeSignalOutputUsesGenerator(route, true)) {
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

/// Extends the planning horizon until the first merged tone's end is known, avoiding premature Beep
/// interruptions.
static std::vector<TimeSignalTone> PlanTimeSignalIntervals(TimeSignalOutputRoute& route, ULONGLONG now) {
    ULONGLONG through = now + 7 * FILE_TIME_TICKS_PER_SECOND;
    while (true) {
        std::vector<TimeSignalTone> intervals =
            MergeTimeSignalTones(CollectTimeSignalTones(route, now, through));
        if (intervals.empty() || intervals.front().end + FILE_TIME_TICKS_PER_SECOND < through) {
            return intervals;
        }
        through = intervals.front().end + 2 * FILE_TIME_TICKS_PER_SECOND;
    }
}

/// Waits for scheduled intervals and plays each merged interval once through the generator or system Beep.
/// Tracks completed time to avoid replaying already rendered portions.
static DWORD WINAPI TimeSignalThreadProc(void* parameter) {
    TimeSignalOutputRoute& route = *static_cast<TimeSignalOutputRoute*>(parameter);
    HANDLE events[] = { route.stopEvent, route.wakeEvent };
    ULONGLONG playedUntil = 0;
    while (WaitForSingleObject(route.stopEvent, 0) != WAIT_OBJECT_0) {
        ULONGLONG now = MonotonicFileTimeValue();
        std::vector<TimeSignalTone> intervals = PlanTimeSignalIntervals(route, now);
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
            DWORD milliseconds =
                static_cast<DWORD>(std::min<ULONGLONG>(remaining / FILE_TIME_TICKS_PER_MILLISECOND, 50));
            if (milliseconds > 1) {
                WaitForMultipleObjects(ARRAYSIZE(events), events, FALSE, milliseconds - 1);
            } else {
                YieldProcessor();
            }
            continue;
        }
        ULONGLONG playedThrough = now;
        if (TimeSignalOutputUsesGenerator(route, tone.generatedTone)) {
            if (!PlayGeneratedTimeSignals(route, tone.start, &playedThrough)) {
                WaitForMultipleObjects(ARRAYSIZE(events), events, FALSE, 100);
            }
        } else {
            route.beepActive.store(true);
            ULONGLONG beepNow = MonotonicFileTimeValue();
            std::vector<TimeSignalTone> pending = PlanTimeSignalIntervals(route, beepNow);
            if (!pending.empty() && pending.front().start <= beepNow && pending.front().end > beepNow
                    && pending.front().end > playedUntil && !pending.front().generatedTone
                    && WaitForSingleObject(route.stopEvent, 0) != WAIT_OBJECT_0) {
                ULONGLONG end = pending.front().end;
                DWORD duration = static_cast<DWORD>(std::max<ULONGLONG>(1,
                    (end - beepNow + FILE_TIME_TICKS_PER_MILLISECOND - 1) / FILE_TIME_TICKS_PER_MILLISECOND));
                Beep(BEEP_PIP_FREQUENCY, duration);
                playedThrough = end;
            }
            route.beepActive.store(false);
        }
        playedUntil = std::max(playedUntil, playedThrough);
    }
    return 0;
}

/// Creates one endpoint's playback worker and its events, cleaning up handles on failure.
static bool EnsureTimeSignalThread(TimeSignalOutputRoute& route) {
    if (route.thread != nullptr) {
        return true;
    }
    route.stopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    route.wakeEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (route.stopEvent != nullptr && route.wakeEvent != nullptr) {
        route.thread = CreateThread(nullptr, 0, TimeSignalThreadProc, &route, 0, nullptr);
    }
    if (route.thread != nullptr) {
        return true;
    }
    if (route.stopEvent != nullptr) {
        CloseHandle(route.stopEvent);
    }
    if (route.wakeEvent != nullptr) {
        CloseHandle(route.wakeEvent);
    }
    route.stopEvent = nullptr;
    route.wakeEvent = nullptr;
    return false;
}

/// Stops, joins, and releases an endpoint worker when neither scheduled sequences nor a preview remain.
static void StopIdleTimeSignalThread(TimeSignalOutputRoute& route) {
    if (route.thread == nullptr || HasTimeSignalWork(route)) {
        return;
    }
    SetEvent(route.stopEvent);
    WaitForSingleObject(route.thread, INFINITE);
    CloseHandle(route.thread);
    CloseHandle(route.stopEvent);
    CloseHandle(route.wakeEvent);
    route.thread = nullptr;
    route.stopEvent = nullptr;
    route.wakeEvent = nullptr;
}

/// Finds the scheduler already associated with a canonical endpoint ID.
static TimeSignalOutputRoute* FindTimeSignalOutput(const std::wstring& device) {
    for (const std::unique_ptr<TimeSignalOutputRoute>& route : timeSignalOutputs) {
        if (route->device == device) {
            return route.get();
        }
    }
    return nullptr;
}

/// Resolves generated selections to physical endpoints and keeps all system Beep work on one logical default
/// route.
static TimeSignalOutputRoute* GetTimeSignalOutput(const std::wstring& requested, bool generatedTone) {
    std::wstring device;
    UINT deviceId = WAVE_MAPPER;
    if (generatedTone && !ResolveAudioOutputDevice(requested, &device, &deviceId)) {
        return nullptr;
    }
    TimeSignalOutputRoute* route = FindTimeSignalOutput(device);
    if (route == nullptr) {
        std::unique_ptr<TimeSignalOutputRoute> created = std::make_unique<TimeSignalOutputRoute>();
        created->device = std::move(device);
        route = created.get();
        timeSignalOutputs.push_back(std::move(created));
    }
    return route;
}

/// Stops completed output workers and releases their schedulers after the worker has returned.
static void ReleaseIdleTimeSignalOutputs() {
    for (auto route = timeSignalOutputs.begin(); route != timeSignalOutputs.end();) {
        StopIdleTimeSignalThread(**route);
        if ((*route)->thread == nullptr) {
            route = timeSignalOutputs.erase(route);
        } else {
            route++;
        }
    }
}

/// Schedules a six-pip sequence on one endpoint, merging identical targets only within that physical output.
bool StartTimeSignalPlayback(ULONGLONG targetTimelineFileTime, bool muted, bool generatedTone, double volume,
        HWND notifyWindow, UINT notifyMessage, const std::wstring& outputDevice) {
    if (targetTimelineFileTime < 5 * FILE_TIME_TICKS_PER_SECOND
            || notifyWindow == nullptr
            || notifyMessage == 0) {
        return false;
    }
    generatedTone = IsTimeSignalGeneratorRequired() || generatedTone;
    TimeSignalOutputRoute* output = GetTimeSignalOutput(generatedTone ? outputDevice : L"", generatedTone);
    if (output == nullptr || !EnsureTimeSignalThread(*output)) {
        return false;
    }
    TimeSignalOutputRoute& route = *output;
    AcquireSRWLockExclusive(&route.lock);
    auto existing = route.sequences.begin();
    while (existing != route.sequences.end()) {
        if (existing->target == targetTimelineFileTime) {
            break;
        }
        existing++;
    }
    if (existing == route.sequences.end()) {
        route.sequences.push_back(TimeSignalSequence{
            targetTimelineFileTime,
            muted,
            generatedTone,
            std::clamp<double>(volume, TIME_SIGNAL_VOLUME_MIN, TIME_SIGNAL_VOLUME_MAX),
            notifyWindow,
            notifyMessage
        });
    }
    ReleaseSRWLockExclusive(&route.lock);
    SetEvent(route.wakeEvent);
    return true;
}

/// Shifts all endpoint schedules by the application-clock correction while preserving independent preview
/// timing.
void AdjustTimeSignalPlaybackTime(LONGLONG adjustment) {
    for (const std::unique_ptr<TimeSignalOutputRoute>& output : timeSignalOutputs) {
        TimeSignalOutputRoute& route = *output;
        AcquireSRWLockExclusive(&route.lock);
        for (TimeSignalSequence& sequence : route.sequences) {
            sequence.target = static_cast<ULONGLONG>(static_cast<LONGLONG>(sequence.target) + adjustment);
        }
        ReleaseSRWLockExclusive(&route.lock);
        if (route.wakeEvent != nullptr) {
            SetEvent(route.wakeEvent);
        }
    }
}

/// Changes one endpoint's sequence mute state without affecting the same target on other outputs.
void SetTimeSignalMuted(ULONGLONG target, bool muted, const std::wstring& outputDevice) {
    TimeSignalOutputRoute* output = FindTimeSignalOutput(outputDevice);
    if (output == nullptr) {
        return;
    }
    TimeSignalOutputRoute& route = *output;
    bool changed = false;
    AcquireSRWLockExclusive(&route.lock);
    for (TimeSignalSequence& sequence : route.sequences) {
        if (sequence.target == target) {
            changed = sequence.muted != muted;
            sequence.muted = muted;
            break;
        }
    }
    ReleaseSRWLockExclusive(&route.lock);
    if (changed && route.wakeEvent != nullptr) {
        SetEvent(route.wakeEvent);
    }
}

/// Cancels the matching target only on the requested endpoint and releases workers that have become idle.
void CancelTimeSignalPlayback(ULONGLONG target, const std::wstring& outputDevice) {
    TimeSignalOutputRoute* output = FindTimeSignalOutput(outputDevice);
    if (output == nullptr) {
        return;
    }
    AcquireSRWLockExclusive(&output->lock);
    for (auto sequence = output->sequences.begin(); sequence != output->sequences.end();) {
        if (sequence->target == target) {
            sequence = output->sequences.erase(sequence);
        } else {
            sequence++;
        }
    }
    ReleaseSRWLockExclusive(&output->lock);
    ReleaseIdleTimeSignalOutputs();
}

/// Updates the existing preview on the Windows default output without changing other output streams.
void SetTimeSignalPreviewVolume(double volume) {
    for (const std::unique_ptr<TimeSignalOutputRoute>& route : timeSignalOutputs) {
        route->previewVolume.store(std::clamp<double>(volume, TIME_SIGNAL_VOLUME_MIN, TIME_SIGNAL_VOLUME_MAX));
    }
}

/// Starts a Windows-default preview on the applied sound mode's route, including when previewing the other
/// mode. Defers migration while another route's system Beep is in progress; subsequent preview updates retry
/// it.
bool StartTimeSignalVolumePreview(bool generatedTone, double volume, bool scheduledGeneratedTone) {
    generatedTone = IsTimeSignalGeneratorRequired() || generatedTone;
    scheduledGeneratedTone = IsTimeSignalGeneratorRequired() || scheduledGeneratedTone;
    TimeSignalOutputRoute* output = GetTimeSignalOutput(L"", scheduledGeneratedTone);
    if (output == nullptr || !EnsureTimeSignalThread(*output)) {
        StopTimeSignalVolumePreview();
        return false;
    }
    SetTimeSignalPreviewVolume(volume);
    bool pendingBeep = false;
    for (const std::unique_ptr<TimeSignalOutputRoute>& item : timeSignalOutputs) {
        TimeSignalOutputRoute& route = *item;
        if (&route == output) {
            continue;
        }
        AcquireSRWLockExclusive(&route.lock);
        route.previewActive = false;
        ReleaseSRWLockExclusive(&route.lock);
        pendingBeep = pendingBeep || route.beepActive.load();
        if (route.wakeEvent != nullptr) {
            SetEvent(route.wakeEvent);
        }
    }
    if (pendingBeep) {
        return true;
    }
    AcquireSRWLockExclusive(&output->lock);
    output->previewGeneratedTone = generatedTone;
    if (!output->previewActive) {
        output->previewStart =
            (MonotonicFileTimeValue() / FILE_TIME_TICKS_PER_SECOND + 1) * FILE_TIME_TICKS_PER_SECOND;
        output->previewActive = true;
    }
    ReleaseSRWLockExclusive(&output->lock);
    SetEvent(output->wakeEvent);
    ReleaseIdleTimeSignalOutputs();
    return true;
}

/// Stops test pips while retaining scheduled widget signals on every output.
void StopTimeSignalVolumePreview() {
    for (const std::unique_ptr<TimeSignalOutputRoute>& route : timeSignalOutputs) {
        AcquireSRWLockExclusive(&route->lock);
        route->previewActive = false;
        ReleaseSRWLockExclusive(&route->lock);
    }
    ReleaseIdleTimeSignalOutputs();
}

/// Releases output workers after their sequence-completion notifications have been processed.
void FinishTimeSignalPlayback() {
    ReleaseIdleTimeSignalOutputs();
}

/// Clears all widget schedules while allowing an active Windows-default preview to finish independently.
void StopTimeSignalPlayback() {
    for (const std::unique_ptr<TimeSignalOutputRoute>& route : timeSignalOutputs) {
        AcquireSRWLockExclusive(&route->lock);
        route->sequences.clear();
        ReleaseSRWLockExclusive(&route->lock);
    }
    ReleaseIdleTimeSignalOutputs();
}

/// Reports scheduled widget playback across all output endpoints, excluding preview-only streams.
bool IsTimeSignalPlaybackRunning() {
    bool running = false;
    for (const std::unique_ptr<TimeSignalOutputRoute>& route : timeSignalOutputs) {
        AcquireSRWLockShared(&route->lock);
        running = running || !route->sequences.empty();
        ReleaseSRWLockShared(&route->lock);
    }
    return running;
}
