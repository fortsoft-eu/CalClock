#include "TimeSignal.h"
#include "NtpClient.h"
#include <algorithm>
#include <cmath>
#include <memory>
#include <mmsystem.h>
#include <new>
#include <vector>

#pragma comment(lib, "Winmm.lib")

using RtlGetVersionFunction = LONG(WINAPI*)(OSVERSIONINFOW*);

static HANDLE hTimeSignalThread = nullptr;
static HANDLE hTimeSignalStopEvent = nullptr;
static HANDLE hTimeSignalMuteEvent = nullptr;

static const ULONGLONG FILE_TIME_TICKS_PER_MILLISECOND = 10000;
static const ULONGLONG FILE_TIME_TICKS_PER_SECOND = 10000000;
static const ULONGLONG FILE_TIME_TICKS_PER_MINUTE = 60 * FILE_TIME_TICKS_PER_SECOND;
static const ULONGLONG FILE_TIME_TICKS_PER_DAY = 24 * 60 * FILE_TIME_TICKS_PER_MINUTE;
static const ULONGLONG EARLIEST_SEQUENCE_START = 4500 * FILE_TIME_TICKS_PER_MILLISECOND;
static const ULONGLONG LATEST_SEQUENCE_START = 5500 * FILE_TIME_TICKS_PER_MILLISECOND;
static const ULONGLONG DUPLICATE_TOLERANCE = 500 * FILE_TIME_TICKS_PER_MILLISECOND;
static const DWORD BEEP_PIP_FREQUENCY = 1000;
static const DWORD BEEP_SHORT_PIP_DURATION = 180;
static const DWORD BEEP_LONG_PIP_DURATION = 950;
static const DWORD GENERATOR_PIP_FREQUENCY = 1000;
static const DWORD GENERATOR_SHORT_PIP_DURATION = 100;
static const DWORD GENERATOR_LONG_PIP_DURATION = 500;
static const DWORD GENERATOR_FADE_DURATION = 1;
static const DWORD GENERATOR_SAMPLE_RATE = 22050;
static const double GENERATOR_TONE_AMPLITUDE = 0.28;
static const double PI = 3.14159265358979323846;
static const int TIME_SIGNAL_MINUTES[TIME_SIGNAL_COUNT] = {
    0,
    1,
    5,
    10,
    15,
    20,
    30,
    60
};

struct TimeSignalRequest {
    ULONGLONG targetSystemFileTime = 0;
    HANDLE stopEvent = nullptr;
    HANDLE muteEvent = nullptr;
    HWND notifyWindow = nullptr;
    UINT notifyMessage = 0;
};

bool CalculateTimeSignalTarget(ULONGLONG displayedFileTime, ULONGLONG systemFileTime,
    TimeSignalMode mode, ULONGLONG* targetSystemFileTime) {
    int modeIndex = static_cast<int>(mode);
    if (targetSystemFileTime == nullptr || modeIndex <= TIME_SIGNAL_NONE || modeIndex >= TIME_SIGNAL_COUNT) {
        return false;
    }
    ULONGLONG interval = static_cast<ULONGLONG>(TIME_SIGNAL_MINUTES[modeIndex]) * FILE_TIME_TICKS_PER_MINUTE;
    ULONGLONG remainder = displayedFileTime % interval;
    ULONGLONG untilTarget = remainder == 0 ? interval : interval - remainder;
    if (untilTarget < EARLIEST_SEQUENCE_START || untilTarget > LATEST_SEQUENCE_START) {
        return false;
    }
    *targetSystemFileTime = systemFileTime + untilTarget;
    return true;
}

bool CalculateAlarmTimeSignalTarget(ULONGLONG displayedFileTime, ULONGLONG systemFileTime, int alarmHour, int alarmMinute,
    ULONGLONG* targetSystemFileTime) {
    if (targetSystemFileTime == nullptr || alarmHour < 0 || alarmHour > 23 || alarmMinute < 0 || alarmMinute > 59) {
        return false;
    }
    ULONGLONG timeOfDay = displayedFileTime % FILE_TIME_TICKS_PER_DAY;
    ULONGLONG alarmTime = static_cast<ULONGLONG>(alarmHour * 60 + alarmMinute) * FILE_TIME_TICKS_PER_MINUTE;
    ULONGLONG untilTarget = alarmTime > timeOfDay ? alarmTime - timeOfDay : FILE_TIME_TICKS_PER_DAY - timeOfDay + alarmTime;
    if (untilTarget < EARLIEST_SEQUENCE_START || untilTarget > LATEST_SEQUENCE_START) {
        return false;
    }
    *targetSystemFileTime = systemFileTime + untilTarget;
    return true;
}

bool TimeSignalTargetsCoincide(ULONGLONG left, ULONGLONG right) {
    ULONGLONG difference = left >= right ? left - right : right - left;
    return difference <= DUPLICATE_TOLERANCE;
}

static bool WaitUntil(ULONGLONG targetSystemFileTime, HANDLE stopEvent) {
    while (true) {
        ULONGLONG now = CurrentFileTimeValue();
        if (now >= targetSystemFileTime) {
            return true;
        }
        ULONGLONG remaining = targetSystemFileTime - now;
        if (remaining > 20 * FILE_TIME_TICKS_PER_MILLISECOND) {
            ULONGLONG coarseMilliseconds = remaining / FILE_TIME_TICKS_PER_MILLISECOND - 20;
            DWORD waitMilliseconds = static_cast<DWORD>(std::clamp<ULONGLONG>(coarseMilliseconds, 1, 50));
            if (WaitForSingleObject(stopEvent, waitMilliseconds) == WAIT_OBJECT_0) {
                return false;
            }
            continue;
        }
        while (CurrentFileTimeValue() < targetSystemFileTime) {
            if (WaitForSingleObject(stopEvent, 0) == WAIT_OBJECT_0) {
                return false;
            }
            YieldProcessor();
        }
        return true;
    }
}

static bool IsWindowsVista() {
    static int result = -1;
    if (result >= 0) {
        return result != 0;
    }
    result = 0;
    HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
    RtlGetVersionFunction getVersion = ntdll == nullptr ? nullptr : reinterpret_cast<RtlGetVersionFunction>(GetProcAddress(ntdll, "RtlGetVersion"));
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

static bool PlayVistaFallbackTone(DWORD frequency, DWORD duration) {
    size_t sampleCount = static_cast<size_t>(GENERATOR_SAMPLE_RATE) * duration / 1000;
    if (sampleCount == 0) {
        return true;
    }
    std::vector<short> samples(sampleCount);
    size_t fadeSamples = static_cast<size_t>(GENERATOR_SAMPLE_RATE) * GENERATOR_FADE_DURATION / 1000;
    if (fadeSamples * 2 > sampleCount) {
        fadeSamples = sampleCount / 2;
    }
    double phaseStep = 2.0 * PI * frequency / GENERATOR_SAMPLE_RATE;
    for (size_t index = 0; index < sampleCount; index++) {
        double envelope = 1.0;
        if (fadeSamples != 0 && index < fadeSamples) {
            envelope = static_cast<double>(index) / fadeSamples;
        } else if (fadeSamples != 0 && sampleCount - index <= fadeSamples) {
            envelope = static_cast<double>(sampleCount - index - 1) / fadeSamples;
        }
        samples[index] = static_cast<short>(32767.0 * GENERATOR_TONE_AMPLITUDE * envelope * std::sin(phaseStep * index));
    }
    WAVEFORMATEX format = {};
    format.wFormatTag = WAVE_FORMAT_PCM;
    format.nChannels = 1;
    format.nSamplesPerSec = GENERATOR_SAMPLE_RATE;
    format.wBitsPerSample = 16;
    format.nBlockAlign = format.nChannels * format.wBitsPerSample / 8;
    format.nAvgBytesPerSec = format.nSamplesPerSec * format.nBlockAlign;
    HWAVEOUT output = nullptr;
    if (waveOutOpen(&output, WAVE_MAPPER, &format, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
        return false;
    }
    WAVEHDR header = {};
    header.lpData = reinterpret_cast<LPSTR>(samples.data());
    header.dwBufferLength = static_cast<DWORD>(samples.size() * sizeof(samples[0]));
    bool prepared = waveOutPrepareHeader(output, &header, sizeof(header)) == MMSYSERR_NOERROR;
    bool started = prepared && waveOutWrite(output, &header, sizeof(header)) == MMSYSERR_NOERROR;
    if (started) {
        while ((header.dwFlags & WHDR_DONE) == 0) {
            Sleep(10);
        }
    }
    if (prepared) {
        waveOutUnprepareHeader(output, &header, sizeof(header));
    }
    waveOutClose(output);
    return started;
}

static bool PlayTimeSignalTone(bool longTone, HANDLE stopEvent, HANDLE muteEvent) {
    if (WaitForSingleObject(muteEvent, 0) == WAIT_OBJECT_0) {
        return true;
    }
    if (IsWindowsVista()) {
        DWORD frequency = GENERATOR_PIP_FREQUENCY;
        DWORD duration = longTone ? GENERATOR_LONG_PIP_DURATION : GENERATOR_SHORT_PIP_DURATION;
        if (PlayVistaFallbackTone(frequency, duration)) {
            return true;
        }
    }
    if (WaitForSingleObject(stopEvent, 0) == WAIT_OBJECT_0) {
        return false;
    }
    DWORD frequency = BEEP_PIP_FREQUENCY;
    DWORD duration = longTone ? BEEP_LONG_PIP_DURATION : BEEP_SHORT_PIP_DURATION;
    Beep(frequency, duration);
    return WaitForSingleObject(stopEvent, 0) != WAIT_OBJECT_0;
}

static DWORD WINAPI TimeSignalThreadProc(void* parameter) {
    std::unique_ptr<TimeSignalRequest> request(static_cast<TimeSignalRequest*>(parameter));
    for (int index = 0; index < 5; index++) {
        ULONGLONG target = request->targetSystemFileTime - static_cast<ULONGLONG>(5 - index) * FILE_TIME_TICKS_PER_SECOND;
        if (!WaitUntil(target, request->stopEvent)) {
            return 0;
        }
        if (!PlayTimeSignalTone(false, request->stopEvent, request->muteEvent)) {
            return 0;
        }
    }
    if (!WaitUntil(request->targetSystemFileTime, request->stopEvent)) {
        return 0;
    }
    if (!PlayTimeSignalTone(true, request->stopEvent, request->muteEvent)) {
        return 0;
    }
    PostMessageW(request->notifyWindow, request->notifyMessage, 0, 0);
    return 0;
}

bool StartTimeSignalPlayback(ULONGLONG targetSystemFileTime, bool muted, HWND notifyWindow, UINT notifyMessage) {
    if (hTimeSignalThread != nullptr || notifyWindow == nullptr || notifyMessage == 0) {
        return false;
    }
    HANDLE stopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (stopEvent == nullptr) {
        return false;
    }
    HANDLE muteEvent = CreateEventW(nullptr, TRUE, muted, nullptr);
    if (muteEvent == nullptr) {
        CloseHandle(stopEvent);
        return false;
    }
    TimeSignalRequest* request = new (std::nothrow) TimeSignalRequest();
    if (request == nullptr) {
        CloseHandle(stopEvent);
        CloseHandle(muteEvent);
        return false;
    }
    request->targetSystemFileTime = targetSystemFileTime;
    request->stopEvent = stopEvent;
    request->muteEvent = muteEvent;
    request->notifyWindow = notifyWindow;
    request->notifyMessage = notifyMessage;
    HANDLE thread = CreateThread(nullptr, 0, TimeSignalThreadProc, request, 0, nullptr);
    if (thread == nullptr) {
        delete request;
        CloseHandle(stopEvent);
        CloseHandle(muteEvent);
        return false;
    }
    hTimeSignalStopEvent = stopEvent;
    hTimeSignalMuteEvent = muteEvent;
    hTimeSignalThread = thread;
    return true;
}

void SetTimeSignalMuted(bool muted) {
    if (hTimeSignalMuteEvent == nullptr) {
        return;
    }
    if (muted) {
        SetEvent(hTimeSignalMuteEvent);
    } else {
        ResetEvent(hTimeSignalMuteEvent);
    }
}

void FinishTimeSignalPlayback() {
    if (hTimeSignalThread == nullptr) {
        return;
    }
    WaitForSingleObject(hTimeSignalThread, INFINITE);
    CloseHandle(hTimeSignalThread);
    CloseHandle(hTimeSignalStopEvent);
    CloseHandle(hTimeSignalMuteEvent);
    hTimeSignalThread = nullptr;
    hTimeSignalStopEvent = nullptr;
    hTimeSignalMuteEvent = nullptr;
}

void StopTimeSignalPlayback() {
    if (hTimeSignalThread == nullptr) {
        return;
    }
    SetEvent(hTimeSignalStopEvent);
    WaitForSingleObject(hTimeSignalThread, INFINITE);
    CloseHandle(hTimeSignalThread);
    CloseHandle(hTimeSignalStopEvent);
    CloseHandle(hTimeSignalMuteEvent);
    hTimeSignalThread = nullptr;
    hTimeSignalStopEvent = nullptr;
    hTimeSignalMuteEvent = nullptr;
}

bool IsTimeSignalPlaybackRunning() {
    return hTimeSignalThread != nullptr;
}
