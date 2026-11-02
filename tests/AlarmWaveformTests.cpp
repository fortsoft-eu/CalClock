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
 * Last modified for version 1.7.1.0
 */

#define NOMINMAX
#include <windows.h>
#include <mmsystem.h>
#include <avrt.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>

static int failures = 0;
static int notifications = 0;
static int forbiddenPlaybackCalls = 0;
static ULONGLONG simulatedNow = 1000000000;
static constexpr ULONGLONG TEST_BASE = 1000000000;
static constexpr ULONGLONG TEST_TARGET = TEST_BASE + 50000000;

/// Rejects worker creation and records the attempted hardware path as a test failure.
static HANDLE WINAPI ForbiddenWorker(LPSECURITY_ATTRIBUTES attributes, SIZE_T stackSize,
        LPTHREAD_START_ROUTINE start, LPVOID parameter, DWORD flags, LPDWORD threadId) {
    UNREFERENCED_PARAMETER(attributes);
    UNREFERENCED_PARAMETER(stackSize);
    UNREFERENCED_PARAMETER(start);
    UNREFERENCED_PARAMETER(parameter);
    UNREFERENCED_PARAMETER(flags);
    UNREFERENCED_PARAMETER(threadId);
    ++forbiddenPlaybackCalls;
    return nullptr;
}

/// Rejects system Beep playback and records the attempted hardware path as a test failure.
static BOOL WINAPI ForbiddenBeep(DWORD frequency, DWORD duration) {
    UNREFERENCED_PARAMETER(frequency);
    UNREFERENCED_PARAMETER(duration);
    ++forbiddenPlaybackCalls;
    return FALSE;
}

/// Rejects waveform device access and records the attempted hardware path as a test failure.
static MMRESULT WINAPI ForbiddenWaveOut(LPHWAVEOUT output, UINT device, LPCWAVEFORMATEX format,
        DWORD_PTR callback, DWORD_PTR instance, DWORD flags) {
    UNREFERENCED_PARAMETER(output);
    UNREFERENCED_PARAMETER(device);
    UNREFERENCED_PARAMETER(format);
    UNREFERENCED_PARAMETER(callback);
    UNREFERENCED_PARAMETER(instance);
    UNREFERENCED_PARAMETER(flags);
    ++forbiddenPlaybackCalls;
    return MMSYSERR_ERROR;
}

/// Records completion locally without sending messages to any real application window.
static BOOL WINAPI RecordNotification(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(window);
    UNREFERENCED_PARAMETER(message);
    UNREFERENCED_PARAMETER(wParam);
    UNREFERENCED_PARAMETER(lParam);
    ++notifications;
    return TRUE;
}

#define CreateThread ForbiddenWorker
#define Beep ForbiddenBeep
#define waveOutOpen ForbiddenWaveOut
#define PostMessageW RecordNotification
#include "../CalClock/TimeSignal.cpp"
#undef CreateThread
#undef Beep
#undef waveOutOpen
#undef PostMessageW


/// Supplies a deterministic continuous-clock value without reading or modifying the system clock.
ULONGLONG MonotonicFileTimeValue() {
    return simulatedNow;
}

/// Resolves only simulated endpoint names and never enumerates or opens a real audio device.
bool ResolveAudioOutputDevice(const std::wstring& requested, std::wstring* endpoint, UINT* deviceId) {
    if (endpoint != nullptr) {
        *endpoint = requested.empty() ? L"default-test-output" : requested;
    }
    if (deviceId != nullptr) {
        *deviceId = 0;
    }
    return true;
}

/// Reports an independent failed expectation while allowing subsequent scenarios to run.
static void Check(bool condition, const char* name) {
    if (!condition) {
        std::fprintf(stderr, "FAILED: %s\n", name);
        ++failures;
    }
}

/// Creates local synchronization events for a route but never starts an audio worker.
static void InitializeRoute(TimeSignalOutputRoute& route) {
    route.stopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    route.wakeEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (route.stopEvent == nullptr || route.wakeEvent == nullptr) {
        std::abort();
    }
}

/// Releases only synchronization objects explicitly created by this test.
static void DestroyRoute(TimeSignalOutputRoute& route) {
    if (route.thread != nullptr) {
        CloseHandle(route.thread);
        route.thread = nullptr;
    }
    CloseHandle(route.stopEvent);
    CloseHandle(route.wakeEvent);
    route.stopEvent = nullptr;
    route.wakeEvent = nullptr;
}

/// Builds a scheduled six-pip sequence with a simulated completion destination.
static TimeSignalSequence Sequence(ULONGLONG target, bool generated = true,
        double volume = TIME_SIGNAL_VOLUME_DEFAULT) {
    return TimeSignalSequence{ target, false, generated, volume, reinterpret_cast<HWND>(1), WM_APP + 1 };
}

/// Verifies all six durations, trimming after wake, completion, muting, and an already requested stop.
static void TestCollection() {
    for (bool generated : { false, true }) {
        TimeSignalOutputRoute route;
        InitializeRoute(route);
        route.sequences.push_back(Sequence(TEST_TARGET, generated));
        std::vector<TimeSignalTone> tones = CollectTimeSignalTones(route, TEST_BASE, TEST_TARGET + 10000000);
        Check(tones.size() == 6, "six pips collected");
        for (size_t index = 0; index < tones.size(); ++index) {
            ULONGLONG duration = generated ? 1000000 : 1800000;
            if (index == 5) {
                duration = generated ? 5000000 : 9500000;
            }
            Check(tones[index].start == TEST_BASE + index * 10000000, "pip starts at expected whole second");
            Check(tones[index].end - tones[index].start == duration,
                "short or long pip has correct duration");
            Check(tones[index].generatedTone == generated, "requested output mode retained");
        }
        tones = CollectTimeSignalTones(route, TEST_BASE + 22500000, TEST_TARGET + 10000000);
        Check(tones.size() == 3 && tones.front().start == TEST_BASE + 30000000,
            "resume between pips does not collect earlier completed pips");
        tones = CollectTimeSignalTones(route, TEST_TARGET + 500000, TEST_TARGET + 10000000);
        Check(tones.size() == 1 && tones.front().start == TEST_TARGET,
            "resume during final pip retains only live pip");
        int before = notifications;
        tones = CollectTimeSignalTones(route, TEST_TARGET + 10000001, TEST_TARGET + 70000000);
        Check(tones.empty() && route.sequences.empty(), "resume after sequence cannot replay old tones");
        Check(notifications == before + 1, "expired sequence completion is emitted once");
        CollectTimeSignalTones(route, TEST_TARGET + 20000000, TEST_TARGET + 70000000);
        Check(notifications == before + 1, "repeated resume does not duplicate completion");
        route.sequences.push_back(Sequence(TEST_TARGET, generated));
        route.sequences.back().muted = true;
        Check(CollectTimeSignalTones(route, TEST_BASE, TEST_TARGET).empty(), "muted sequence has no tones");
        route.sequences.back().muted = false;
        SetEvent(route.stopEvent);
        Check(CollectTimeSignalTones(route, TEST_BASE, TEST_TARGET).empty(),
            "stop request suppresses collection");
        DestroyRoute(route);
    }
}

/// Verifies interval unions and preview volume overrides without summing overlapping sine-wave amplitudes.
static void TestMergeAndPreview() {
    std::vector<TimeSignalTone> raw = {
        TimeSignalTone{ TEST_BASE + 200, TEST_BASE + 300, 0.25, false },
        TimeSignalTone{ TEST_BASE, TEST_BASE + 100, 0.10, false },
        TimeSignalTone{ TEST_BASE + 50, TEST_BASE + 200, 0.50, true },
        TimeSignalTone{ TEST_BASE + 400, TEST_BASE + 500, 0.75, false }
    };
    std::vector<TimeSignalTone> merged = MergeTimeSignalTones(raw);
    Check(merged.size() == 2, "overlapping and touching tones form one interval");
    Check(merged[0].start == TEST_BASE && merged[0].end == TEST_BASE + 300,
        "merged interval preserves union endpoints");
    Check(merged[0].amplitude == 0.50 && merged[0].generatedTone,
        "merge uses maximum gain and generator mode");
    TimeSignalOutputRoute route;
    InitializeRoute(route);
    route.sequences.push_back(Sequence(TEST_TARGET, true, 50));
    route.sequences.push_back(Sequence(TEST_TARGET + 250000, true, 75));
    route.previewActive = true;
    route.previewStart = TEST_BASE;
    route.previewVolume = 23.5;
    std::vector<TimeSignalTone> tones = CollectTimeSignalTones(route, TEST_BASE, TEST_TARGET);
    double expected = TimeSignalAmplitude(route.previewVolume.load());
    for (const TimeSignalTone& tone : tones) {
        Check(tone.amplitude == expected, "preview gain applies equally to overlapping scheduled sources");
    }
    std::vector<TimeSignalTone> held = tones;
    route.previewVolume = 61.75;
    tones = CollectTimeSignalTones(route, TEST_BASE, TEST_TARGET);
    RefreshHeldTimeSignalTones(tones, &held);
    expected = TimeSignalAmplitude(route.previewVolume.load());
    for (const TimeSignalTone& tone : held) {
        Check(tone.amplitude == expected, "held live tones follow preview gain change");
    }
    route.previewActive = false;
    tones = CollectTimeSignalTones(route, TEST_BASE, TEST_TARGET);
    RefreshHeldTimeSignalTones(tones, &held);
    Check(held.front().amplitude == TimeSignalAmplitude(50), "ending preview restores scheduled source gain");
    DestroyRoute(route);
}

/// Checks PCM zero crossings, representable amplitude, and silent samples outside the scheduled intervals.
static void CheckPcm(const std::vector<short>& samples, LONGLONG first, LONGLONG origin, const char* name) {
    for (size_t index = 0; index < samples.size(); ++index) {
        LONGLONG offset = first + index - origin;
        if (offset >= 0 && offset % 24 == 0) {
            Check(samples[index] == 0, name);
        }
        if (offset >= 0 && samples[index] != 0) {
            LONGLONG phase = offset % 48;
            Check(phase > 0 && phase < 24 ? samples[index] > 0 : samples[index] < 0,
                "all overlapping sources retain the same oscillator phase");
        }
        Check(samples[index] != -32768, "PCM stays inside symmetric full scale");
    }
}

/// Compares arbitrary block boundaries with one continuous rendering and requires each emitted buffer to end
/// at zero.
static void TestBufferContinuity() {
    const std::vector<TimeSignalTone> intervals = {
        TimeSignalTone{ TEST_BASE, TEST_BASE + 1234567, 0.75, true }
    };
    TimeSignalPhase referencePhase;
    std::vector<short> reference(10000);
    RenderTimeSignalSamples(intervals, TEST_BASE, 0, &reference, &referencePhase);
    const size_t sizes[] = { 1, 7, 47, 48, 49, 959, 960, 961 };
    for (size_t size : sizes) {
        TimeSignalPhase phase;
        LONGLONG first = 0;
        while (first < static_cast<LONGLONG>(reference.size())) {
            std::vector<short> block(size);
            RenderTimeSignalSamples(intervals, TEST_BASE, first, &block, &phase, true);
            Check(block.size() >= size && block.size() <= size + 47,
                "buffer extension stays within one cycle");
            Check(block.back() == 0, "every output block ends at zero");
            size_t referenceStart = static_cast<size_t>(first);
            for (size_t index = 0; index < block.size()
                && referenceStart + index < reference.size(); ++index) {
                Check(block[index] == reference[referenceStart + index],
                    "block subdivision does not alter waveform");
            }
            CheckPcm(block, first, 0, "continuous zero crossing is exact");
            first += block.size();
        }
        Check(!phase.active, "finished interval drains to inactive phase");
    }
    Check(reference.front() == 0 && reference.back() == 0, "complete waveform starts and ends at zero");
}

/// Renders complete pre-alarm sequences, including fractional overlaps, silence and output block boundaries.
static void TestCompleteSequences() {
    const LONGLONG cycle = GENERATOR_SAMPLE_RATE / GENERATOR_PIP_FREQUENCY;
    for (ULONGLONG shift : { 0ULL, 234567ULL }) {
        TimeSignalOutputRoute route;
        InitializeRoute(route);
        route.sequences.push_back(Sequence(TEST_TARGET, true, 50));
        if (shift != 0) {
            route.sequences.push_back(Sequence(TEST_TARGET + shift, true, 75));
        }
        std::vector<TimeSignalTone> tones =
            CollectTimeSignalTones(route, TEST_BASE, TEST_TARGET + 10000000);
        std::vector<TimeSignalTone> merged = MergeTimeSignalTones(tones);
        Check(merged.size() == 6, "overlapping pre-alarm sequences retain six audible bursts");
        TimeSignalPhase phase;
        std::vector<short> reference(GENERATOR_SAMPLE_RATE * 6);
        RenderTimeSignalSamples(merged, TEST_BASE, 0, &reference, &phase);
        bool silence = true;
        bool crossings = true;
        bool continuous = true;
        bool audible[6] = {};
        int previous = 0;
        for (size_t index = 0; index < reference.size(); ++index) {
            size_t pip = index / GENERATOR_SAMPLE_RATE;
            LONGLONG offset = index % GENERATOR_SAMPLE_RATE;
            ULONGLONG duration = pip == 5 ? 5000000 : 1000000;
            LONGLONG last =
                static_cast<LONGLONG>(((duration + shift) * GENERATOR_SAMPLE_RATE + 9999999) / 10000000);
            last = (last + cycle - 1) / cycle * cycle;
            if (offset > last) {
                silence = silence && reference[index] == 0;
            } else {
                audible[pip] = audible[pip] || reference[index] != 0;
            }
            if (offset % (cycle / 2) == 0) {
                crossings = crossings && reference[index] == 0;
            }
            continuous = continuous && std::abs(reference[index] - previous) <= 6000;
            previous = reference[index];
        }
        Check(silence, "whole pre-alarm sequence is silent between pips and after the final pip");
        Check(crossings, "fractional overlaps preserve exact zero crossings in every pip");
        Check(continuous, "full pre-alarm sequence has no discontinuous amplitude step");
        for (bool pipAudible : audible) {
            Check(pipAudible, "every scheduled pip produces nonzero PCM samples");
        }
        Check(!phase.active, "full pre-alarm sequence releases the oscillator after its final pip");
        for (size_t size : { 959U, 960U, 961U }) {
            route.sequences.clear();
            route.sequences.push_back(Sequence(TEST_TARGET, true, 50));
            if (shift != 0) {
                route.sequences.push_back(Sequence(TEST_TARGET + shift, true, 75));
            }
            TimeSignalPhase blockPhase;
            size_t first = 0;
            bool equal = true;
            bool endsAtZero = true;
            while (first < reference.size()) {
                ULONGLONG from = TEST_BASE + first * FILE_TIME_TICKS_PER_SECOND / GENERATOR_SAMPLE_RATE;
                ULONGLONG retainedFrom = std::max(TEST_BASE, from - FILE_TIME_TICKS_PER_MILLISECOND);
                tones = CollectTimeSignalTones(route, retainedFrom, from + FILE_TIME_TICKS_PER_SECOND);
                std::vector<TimeSignalTone> current = MergeTimeSignalTones(tones);
                std::vector<short> block(size);
                RenderTimeSignalSamples(current, TEST_BASE, static_cast<LONGLONG>(first),
                    &block, &blockPhase, true);
                endsAtZero = endsAtZero && block.back() == 0;
                for (size_t index = 0; index < block.size() && first + index < reference.size(); ++index) {
                    equal = equal && block[index] == reference[first + index];
                }
                first += block.size();
            }
            Check(equal, "whole pre-alarm sequence is identical across output buffer boundaries");
            Check(endsAtZero, "all pre-alarm output blocks end at zero");
        }
        DestroyRoute(route);
    }
}

/// Changes gain and overlap ownership during one uninterrupted tone, then tests cancellation at arbitrary
/// phases.
static void TestLiveChanges() {
    for (int stopAt : { 1, 7, 23, 24, 25, 47, 48, 49, 113 }) {
        TimeSignalPhase phase;
        std::vector<TimeSignalTone> intervals = {
            TimeSignalTone{ TEST_BASE, TEST_BASE + 10000000, 0.10, true }
        };
        LONGLONG first = 0;
        int previous = 0;
        for (int step = 0; step < 120; ++step) {
            double gain = static_cast<double>((step * 37) % 101) / 100.0;
            intervals[0].amplitude = gain;
            if (step > 20) {
                intervals[0].start = TEST_BASE + 271;
            }
            std::vector<short> block(static_cast<size_t>(stopAt));
            RenderTimeSignalSamples(intervals, TEST_BASE, first, &block, &phase);
            CheckPcm(block, first, 0, "gain changes keep zero crossings");
            for (short sample : block) {
                Check(std::abs(sample - previous) <= 6000, "gain change has no discontinuous amplitude step");
                previous = sample;
            }
            Check(phase.origin == 0, "overlap handoff does not restart oscillator");
            first += block.size();
        }
        std::vector<short> tail(200);
        RenderTimeSignalSamples(std::vector<TimeSignalTone>{}, TEST_BASE, first, & tail, & phase, true);
        CheckPcm(tail, first, 0, "cancellation drains through original zero crossing");
        for (short sample : tail) {
            Check(std::abs(sample - previous) <= 6000, "cancellation has no discontinuous amplitude step");
            previous = sample;
        }
        Check(!phase.active && tail.back() == 0, "missing input drains to silence");
        bool silent = true;
        for (size_t index = tail.size() - 48; index < tail.size(); ++index) {
            silent = silent && tail[index] == 0;
        }
        Check(silent, "cancellation leaves a silent tail");
    }
}

/// Prepares a route whose thread handle is only an inert event, keeping all worker creation prohibited.
static TimeSignalOutputRoute& AddOfflineRoute(const wchar_t* device) {
    std::unique_ptr<TimeSignalOutputRoute> route = std::make_unique<TimeSignalOutputRoute>();
    route->device = device;
    InitializeRoute(*route);
    route->thread = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (route->thread == nullptr) {
        std::abort();
    }
    timeSignalOutputs.push_back(std::move(route));
    return *timeSignalOutputs.back();
}

/// Cancels one target or a preview while retaining other targets and independent endpoint schedules.
static void TestCancellationIsolation() {
    TimeSignalOutputRoute& first = AddOfflineRoute(L"offline-output-one");
    TimeSignalOutputRoute& second = AddOfflineRoute(L"offline-output-two");
    HWND notify = reinterpret_cast<HWND>(1);
    Check(StartTimeSignalPlayback(TEST_TARGET, false, true, 50, notify, WM_APP + 1, first.device),
        "first offline target is scheduled");
    Check(StartTimeSignalPlayback(TEST_TARGET, false, true, 75, notify, WM_APP + 1, first.device),
        "identical target is accepted without duplicate sequence");
    Check(first.sequences.size() == 1, "identical targets are merged on one endpoint");
    Check(StartTimeSignalPlayback(TEST_TARGET + 10000000, false, true, 50, notify, WM_APP + 1, first.device),
        "second independent target is scheduled");
    Check(StartTimeSignalPlayback(TEST_TARGET, false, true, 75, notify, WM_APP + 1, second.device),
        "same target is independently scheduled on another endpoint");
    first.previewActive = true;
    second.previewActive = true;
    SetTimeSignalMuted(TEST_TARGET, true, first.device);
    Check(first.sequences.front().muted && !second.sequences.front().muted,
        "mute is isolated to selected output");
    CancelTimeSignalPlayback(TEST_TARGET, first.device);
    Check(first.sequences.size() == 1 && first.sequences.front().target == TEST_TARGET + 10000000,
        "cancel leaves different target on same output");
    Check(second.sequences.size() == 1 && second.sequences.front().target == TEST_TARGET,
        "cancel leaves same target on other output");
    StopTimeSignalVolumePreview();
    Check(!first.previewActive && !second.previewActive, "preview ends on all selected routes");
    Check(first.sequences.size() == 1 && second.sequences.size() == 1,
        "ending preview preserves scheduled signals");
    AdjustTimeSignalPlaybackTime(25000);
    Check(first.sequences.front().target == TEST_TARGET + 10025000
        && second.sequences.front().target == TEST_TARGET + 25000,
            "time correction shifts both routes consistently");
    for (const std::unique_ptr<TimeSignalOutputRoute>& route : timeSignalOutputs) {
        DestroyRoute(*route);
    }
    timeSignalOutputs.clear();
}

/// Exercises the production scheduler and PCM generator entirely in memory with hardware entry points
/// blocked.
int main() {
    TestCollection();
    TestMergeAndPreview();
    TestBufferContinuity();
    TestCompleteSequences();
    TestLiveChanges();
    TestCancellationIsolation();
    Check(forbiddenPlaybackCalls == 0, "offline scenarios never enter a hardware playback path");
    if (failures != 0) {
        return 1;
    }
    std::puts("PASS: six pips, delayed collection, PCM phase and zero boundaries, "
        "preview gain and route cancellation");
    return 0;
}
