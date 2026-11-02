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
 * Last modified for version 1.7.0.6
 */

#define NOMINMAX
#include "../CalClock/CalClock.h"
#include "../CalClock/AlarmSchedule.h"
#include "../CalClock/NtpClient.h"
#include "../CalClock/TimeZoneSupport.h"
#include <atomic>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>

bool NativeConvertUtcToTimeZone(const DYNAMIC_TIME_ZONE_INFORMATION& zone, const SYSTEMTIME& utc,
    SYSTEMTIME* local);
bool NativeGetTimeZoneUtcCandidates(const DYNAMIC_TIME_ZONE_INFORMATION& zone, const SYSTEMTIME& local,
    ULONGLONG(&utc)[2], unsigned int& count);

#define ConvertUtcToTimeZone NativeConvertUtcToTimeZone
#define GetTimeZoneUtcCandidates NativeGetTimeZoneUtcCandidates
#include "../CalClock/TimeZoneSupport.cpp"
#undef ConvertUtcToTimeZone
#undef GetTimeZoneUtcCandidates

static constexpr LONGLONG REFRESH_SECOND_TICKS = 10000000;
static constexpr UINT WM_NTP_RESULT = WM_APP + 3;
static constexpr UINT WM_UPDATE_SETTINGS_CONTROL_METRICS = WM_APP + 9;
static HWND hController = reinterpret_cast<HWND>(1);
static HWND hSettings = reinterpret_cast<HWND>(2);
static HANDLE hAlarmWakeTimer = nullptr;
static HANDLE hNtpThread = nullptr;
static LONGLONG alarmClockOffset = 0;
static LONGLONG alarmWakeOffset = 0;
static ULONGLONG alarmWakeTarget = 0;
static bool alarmWakeUsesNtp = false;
static bool alarmTimeZoneInitialized = false;
static DYNAMIC_TIME_ZONE_INFORMATION alarmTimeZone{};
static DYNAMIC_TIME_ZONE_INFORMATION simulatedZone{};
static ULONGLONG simulatedSystemTime = 0;
static ULONGLONG simulatedTimeline = 0;
static ULONGLONG advanceAfterSystemRead = 0;
static ULONGLONG nextNtpAttemptTick = 0;
static std::atomic<LONGLONG> ntpClockOffset100Nanoseconds = 0;
static std::atomic<LONGLONG> ntpOffset100Nanoseconds = 0;
static std::atomic<ULONG> ntpGeneration = 0;
static std::atomic<bool> ntpQueryRunning = false;
static std::atomic<bool> ntpTimeValid = false;
static bool useNtpTime = false;
static bool ntpHasSynchronized = false;
static bool ntpLastQueryFailed = false;
static std::wstring ntpActiveServer;
static std::vector<DYNAMIC_TIME_ZONE_INFORMATION> timeZones;
static std::vector<std::unique_ptr<Widget>> widgets;
static std::vector<int> alarmStarts;
static std::vector<ULONGLONG> wakeTimes;
static int failures = 0;
static int timerCreates = 0;
static int timerCancels = 0;
static int timerCloses = 0;
static int debugMessages = 0;
static int refreshRequests = 0;
static int displayRefreshRequests = 0;
static int ntpRestarts = 0;
static int signalChecks = 0;
static bool timerCreateFails = false;
static bool timerSetFails = false;
static bool wakeUnsupported = false;
static bool zoneReadFails = false;
static bool wakeArmed = false;

/// Reports each failed scenario while allowing subsequent independent scenarios to run.
static void Check(bool condition, const char* name) {
    if (!condition) {
        std::fprintf(stderr, "FAILED: %s\n", name);
        ++failures;
    }
}

/// Creates a deterministic UTC instant without changing the computer clock.
static ULONGLONG UtcTime(int day, int hour, int minute, int second = 0) {
    SYSTEMTIME time{};
    time.wYear = 2026;
    time.wMonth = 11;
    time.wDay = static_cast<WORD>(day);
    time.wHour = static_cast<WORD>(hour);
    time.wMinute = static_cast<WORD>(minute);
    time.wSecond = static_cast<WORD>(second);
    FILETIME file{};
    if (!SystemTimeToFileTime(&time, &file)) {
        std::abort();
    }
    ULARGE_INTEGER value{};
    value.LowPart = file.dwLowDateTime;
    value.HighPart = file.dwHighDateTime;
    return value.QuadPart;
}

/// Substitutes only the selected system zone while retaining the real production timezone conversion.
bool ConvertUtcToTimeZone(const DYNAMIC_TIME_ZONE_INFORMATION& zone, const SYSTEMTIME& utc,
    SYSTEMTIME* local) {
    const DYNAMIC_TIME_ZONE_INFORMATION& selected = _wcsicmp(zone.TimeZoneKeyName, SYSTEM_TIME_ZONE_KEY) == 0
        ? simulatedZone
        : zone;
    return NativeConvertUtcToTimeZone(selected, utc, local);
}

/// Uses the same simulated zone for the production inverse conversion and scheduler round trips.
bool GetTimeZoneUtcCandidates(const DYNAMIC_TIME_ZONE_INFORMATION& zone, const SYSTEMTIME& local,
        ULONGLONG(&utc)[2], unsigned int& count) {
    const DYNAMIC_TIME_ZONE_INFORMATION& selected =
        _wcsicmp(zone.TimeZoneKeyName, SYSTEM_TIME_ZONE_KEY) == 0 ? simulatedZone : zone;
    return NativeGetTimeZoneUtcCandidates(selected, local, utc, count);
}

/// Returns the simulated operating-system clock without reading or setting the real clock.
static ULONGLONG CurrentFileTimeValue() {
    ULONGLONG value = simulatedSystemTime;
    simulatedSystemTime += advanceAfterSystemRead;
    simulatedTimeline += advanceAfterSystemRead;
    return value;
}

/// Returns a continuous simulated timeline including time elapsed during suspend and hibernation.
static ULONGLONG MonotonicFileTimeValue() {
    return simulatedTimeline;
}

/// Records alarm dispatch without invoking audio, programs, scripts, or real windows.
static void StartWidgetAlarm(Widget* widget) {
    alarmStarts.push_back(widget->config.id);
}

/// Records timer creation and never creates an operating-system wake request.
static HANDLE WINAPI TestCreateWaitableTimerW(LPSECURITY_ATTRIBUTES, BOOL manual, LPCWSTR name) {
    Check(manual && name == nullptr, "manual-reset unnamed wake timer");
    ++timerCreates;
    if (timerCreateFails) {
        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        return nullptr;
    }
    return reinterpret_cast<HANDLE>(3);
}

/// Records the exact absolute UTC due time and models supported, failed, and unsupported wake requests.
static BOOL WINAPI TestSetWaitableTimer(HANDLE timer, const LARGE_INTEGER* due, LONG period,
        PTIMERAPCROUTINE callback, LPVOID context, BOOL resume) {
    Check(timer == reinterpret_cast<HANDLE>(3) && due != nullptr, "valid simulated timer request");
    Check(period == 0 && callback == nullptr && context == nullptr && resume, "one-shot resume without APC");
    Check(due->QuadPart > 0, "wake request uses absolute UTC");
    wakeTimes.push_back(static_cast<ULONGLONG>(due->QuadPart));
    wakeArmed = !timerSetFails;
    if (timerSetFails) {
        SetLastError(ERROR_ACCESS_DENIED);
        return FALSE;
    }
    if (wakeUnsupported) {
        SetLastError(ERROR_NOT_SUPPORTED);
    }
    return TRUE;
}

/// Cancels only the recorded simulated timer.
static BOOL WINAPI TestCancelWaitableTimer(HANDLE timer) {
    Check(timer == reinterpret_cast<HANDLE>(3), "cancel only test timer");
    ++timerCancels;
    wakeArmed = false;
    return TRUE;
}

/// Releases only synthetic handles used by the harness.
static BOOL WINAPI TestCloseHandle(HANDLE handle) {
    Check(handle == reinterpret_cast<HANDLE>(3) || handle == reinterpret_cast<HANDLE>(4),
        "close test handles only");
    ++timerCloses;
    return TRUE;
}

/// Captures diagnostic events without writing to the real debugger.
static void WINAPI TestOutputDebugStringW(LPCWSTR) {
    ++debugMessages;
}

/// Exposes the simulated system-zone definition without changing Windows timezone settings.
static DWORD WINAPI TestGetDynamicTimeZoneInformation(PDYNAMIC_TIME_ZONE_INFORMATION information) {
    if (zoneReadFails) {
        return TIME_ZONE_ID_INVALID;
    }
    *information = simulatedZone;
    return TIME_ZONE_ID_STANDARD;
}

/// Prevents settings metrics messages from being posted to a real window.
static BOOL WINAPI TestPostMessageW(HWND, UINT, WPARAM, LPARAM) {
    return TRUE;
}

/// Records ordinary refresh scheduling without touching the desktop.
static void ScheduleWidgetRefresh() {
    ++refreshRequests;
}

/// Records display-only refresh requests separately from alarm checks.
static void ScheduleWidgetDisplayRefresh() {
    ++displayRefreshRequests;
}

/// Leaves native widget rendering outside this scheduling integration test.
static void RenderWidget(Widget*) {}

/// Leaves calendar repainting outside this scheduling integration test.
static void UpdateCalendarDate(Widget*) {}

/// Avoids reading or writing the user's real NTP log.
static void AppendNtpSynchronizationLog(const std::vector<NtpQueryLogEntry>&) {}

/// Records stale-result retries without starting network activity.
static void StartNtpSynchronization(bool force) {
    Check(force, "stale NTP retry forced");
    ++ntpRestarts;
}

/// Suppresses user-interface updates outside the tested alarm scheduling paths.
static void UpdateNtpSettingsControls() {}

/// Makes the next-query scheduling expression independent of the computer's current uptime.
static ULONGLONG WINAPI TestGetTickCount64() {
    return simulatedTimeline / 10000;
}

/// Supplies a deterministic nonalarm NTP scheduling input.
static ULONGLONG GetNtpHourPosition() {
    return 0;
}

/// Counts signal checks without emitting any tones.
static void CheckTimeSignals() {
    ++signalChecks;
}

#define CreateWaitableTimerW TestCreateWaitableTimerW
#define SetWaitableTimer TestSetWaitableTimer
#define CancelWaitableTimer TestCancelWaitableTimer
#define CloseHandle TestCloseHandle
#define OutputDebugStringW TestOutputDebugStringW
#define GetDynamicTimeZoneInformation TestGetDynamicTimeZoneInformation
#define PostMessageW TestPostMessageW
#define GetTickCount64 TestGetTickCount64
#include "AlarmIntegrationProduction.h"

/// Dispatches the unchanged production power, clock, settings, and NTP message cases against isolated stubs.
static LRESULT DispatchMessage(UINT msg, WPARAM wParam = 0, LPARAM lParam = 0, HWND window = hController) {
    switch (msg) {
#include "AlarmIntegrationMessages.h"
        default:
            break;
    }
    return 0;
}
#undef CreateWaitableTimerW
#undef SetWaitableTimer
#undef CancelWaitableTimer
#undef CloseHandle
#undef OutputDebugStringW
#undef GetDynamicTimeZoneInformation
#undef PostMessageW
#undef GetTickCount64

/// Selects an installed zone definition and fails explicitly when a required native zone is unavailable.
static void SelectSystemZone(const wchar_t* key) {
    for (const DYNAMIC_TIME_ZONE_INFORMATION& zone : timeZones) {
        if (_wcsicmp(zone.TimeZoneKeyName, key) == 0) {
            simulatedZone = zone;
            return;
        }
    }
    std::fwprintf(stderr, L"Missing required zone: %ls\n", key);
    std::abort();
}

/// Resets isolated application and stub state between independent scenarios.
static void Begin(ULONGLONG now) {
    CancelAlarmWakeTimer();
    widgets.clear();
    alarmStarts.clear();
    wakeTimes.clear();
    alarmClockOffset = 0;
    alarmWakeOffset = 0;
    alarmWakeUsesNtp = false;
    alarmTimeZoneInitialized = false;
    alarmTimeZone = DYNAMIC_TIME_ZONE_INFORMATION{};
    simulatedTimeline = now;
    simulatedSystemTime = now;
    advanceAfterSystemRead = 0;
    useNtpTime = false;
    ntpTimeValid = false;
    ntpClockOffset100Nanoseconds = 0;
    ntpOffset100Nanoseconds = 0;
    ntpGeneration = 0;
    ntpQueryRunning = false;
    ntpHasSynchronized = false;
    ntpLastQueryFailed = false;
    ntpActiveServer.clear();
    hNtpThread = nullptr;
    timerCreateFails = false;
    timerSetFails = false;
    wakeUnsupported = false;
    zoneReadFails = false;
    wakeArmed = false;
    timerCreates = 0;
    timerCancels = 0;
    timerCloses = 0;
    debugMessages = 0;
    refreshRequests = 0;
    displayRefreshRequests = 0;
    ntpRestarts = 0;
    signalChecks = 0;
    SelectSystemZone(L"UTC");
    AlarmSystemTimeZoneChanged();
}

/// Creates a real production alarm schedule without creating a widget window.
static Widget* AddAlarm(int id, int hour, int minute = 0, bool wake = true, bool pips = false) {
    std::unique_ptr<Widget> widget = std::make_unique<Widget>();
    widget->config.id = id;
    widget->config.type = WIDGET_DIGITAL;
    widget->config.visible = false;
    widget->config.showUtc = true;
    widget->config.alarmEnabled = true;
    widget->config.alarmHour = hour;
    widget->config.alarmMinute = minute;
    widget->config.alarmWakeComputer = wake;
    widget->config.alarmTimeSignal = pips;
    widget->alarmSchedule.Reset(widget->config, timeZones, GetApplicationFileTimeValue());
    Widget* added = widget.get();
    widgets.push_back(std::move(widget));
    return added;
}

/// Advances both clocks normally while preserving any explicitly simulated system correction.
static void Elapse(ULONGLONG seconds) {
    simulatedTimeline += seconds * REFRESH_SECOND_TICKS;
    simulatedSystemTime += seconds * REFRESH_SECOND_TICKS;
}

/// Delivers a real production NTP-result message using a synthetic successful or failed sample.
static void NtpResult(LONGLONG clockOffset, bool success = true, ULONG generation = 0) {
    NtpThreadResult* result = new NtpThreadResult();
    result->success = success;
    result->generation = generation;
    result->clockOffset100Nanoseconds = clockOffset;
    result->offset100Nanoseconds = clockOffset;
    result->server = L"isolated.test";
    DispatchMessage(WM_NTP_RESULT, 0, reinterpret_cast<LPARAM>(result));
}

/// Covers wake opt-in, multiple widgets, pips, cancellation, weekdays, and timer rearm caching.
static void TestWakeRequests() {
    Begin(UtcTime(2, 7, 0));
    Widget* early = AddAlarm(1, 8, 0, false);
    Widget* late = AddAlarm(2, 9);
    CheckWidgetAlarms();
    Check(wakeTimes.back() == UtcTime(2, 9, 0), "only opted-in alarms request wake");
    early->config.alarmWakeComputer = true;
    CheckWidgetAlarms();
    Check(wakeTimes.back() == UtcTime(2, 8, 0), "earliest opted-in widget wins");
    early->config.alarmTimeSignal = true;
    CheckWidgetAlarms();
    Check(wakeTimes.back() == UtcTime(2, 7, 59, 55), "pips request five-second lead");
    size_t armed = wakeTimes.size();
    Elapse(1);
    CheckWidgetAlarms();
    Check(wakeTimes.size() == armed, "ordinary checks do not continuously rearm");
    simulatedTimeline = simulatedSystemTime = UtcTime(2, 7, 59, 55);
    CheckWidgetAlarms();
    Check(wakeTimes.back() == UtcTime(2, 8, 0), "lead instant advances wake request to alarm");
    early->config.alarmEnabled = false;
    CheckWidgetAlarms();
    Check(wakeTimes.back() == UtcTime(2, 9, 0), "disabling earliest alarm selects next widget");
    late->config.alarmDays = 0;
    CheckWidgetAlarms();
    Check(hAlarmWakeTimer == nullptr && !wakeArmed, "no eligible days cancels and closes timer");
    late->config.alarmDays = ALARM_DAYS_ALL;
    CheckWidgetAlarms();
    Check(wakeArmed, "restoring days rearms timer");
    widgets.erase(widgets.begin() + 1);
    CheckWidgetAlarms();
    Check(hAlarmWakeTimer == nullptr, "removing last eligible widget releases timer");
    early->config.type = WIDGET_CALENDAR;
    early->config.alarmEnabled = true;
    CheckWidgetAlarms();
    Check(hAlarmWakeTimer == nullptr, "calendar cannot request wake even with crafted alarm flags");
    Check(alarmStarts.empty(), "configuration changes never replay elapsed alarms");
}

/// Exercises normal suspend, hibernation, duplicate notifications, delayed processing, and long absences.
static void TestSuspendAndResume() {
    const WPARAM resumes[] = { PBT_APMRESUMEAUTOMATIC, PBT_APMRESUMESUSPEND };
    for (WPARAM resume : resumes) {
        Begin(UtcTime(2, 7, 50));
        AddAlarm(1, 8);
        CheckWidgetAlarms();
        DispatchMessage(WM_POWERBROADCAST, PBT_APMSUSPEND);
        Check(wakeArmed && alarmStarts.empty(), "suspend arms without early alarm");
        Elapse(1200);
        DispatchMessage(WM_POWERBROADCAST, resume);
        Check(alarmStarts.size() == 1, "resume catches missed alarm immediately");
        DispatchMessage(WM_POWERBROADCAST, PBT_APMRESUMEAUTOMATIC);
        DispatchMessage(WM_POWERBROADCAST, PBT_APMRESUMESUSPEND);
        DispatchMessage(WM_TIMECHANGE);
        CheckWidgetAlarms();
        Check(alarmStarts.size() == 1, "duplicate resume and timechange cannot replay alarm");
    }
    Begin(UtcTime(2, 7, 50));
    Widget* widget = AddAlarm(1, 8, 0, false);
    CheckWidgetAlarms();
    Elapse(20 * 86400 + 1200);
    CheckWidgetAlarms();
    Check(alarmStarts.size() == 1 && widget->alarmSchedule.LastDate() == 20261122,
        "long pause catches only latest eligible occurrence without wake opt-in");
    Check(hAlarmWakeTimer == nullptr, "catch-up remains independent of wake setting");
    Begin(UtcTime(2, 8, 20));
    AddAlarm(1, 8);
    DispatchMessage(WM_POWERBROADCAST, PBT_APMRESUMEAUTOMATIC);
    Check(alarmStarts.empty(), "fresh launch after alarm never catches historical occurrence");
}

/// Tests both timechange/resume orders and separates deliberate UTC changes from elapsed continuous time.
static void TestClockChanges() {
    for (int order = 0; order < 2; ++order) {
        Begin(UtcTime(2, 7, 50));
        AddAlarm(1, 8);
        CheckWidgetAlarms();
        Elapse(1200);
        if (order == 0) {
            DispatchMessage(WM_TIMECHANGE);
            DispatchMessage(WM_POWERBROADCAST, PBT_APMRESUMEAUTOMATIC);
        } else {
            DispatchMessage(WM_POWERBROADCAST, PBT_APMRESUMEAUTOMATIC);
            DispatchMessage(WM_TIMECHANGE);
        }
        Check(alarmStarts.size() == 1, "resume/timechange ordering retains elapsed alarm");
    }
    Begin(UtcTime(2, 7, 0));
    Widget* widget = AddAlarm(1, 8);
    CheckWidgetAlarms();
    simulatedSystemTime = UtcTime(2, 10, 0);
    DispatchMessage(WM_TIMECHANGE);
    Check(alarmStarts.empty(), "manual forward UTC correction does not replay alarm");
    Check(widget->alarmSchedule.Next() == UtcTime(3, 8, 0), "forward UTC correction replans next alarm");
    simulatedSystemTime = UtcTime(2, 7, 0);
    DispatchMessage(WM_TIMECHANGE);
    Elapse(3600);
    CheckWidgetAlarms();
    Check(alarmStarts.size() == 1, "alarm fires after explicit backward correction");
    simulatedSystemTime = UtcTime(2, 7, 0);
    DispatchMessage(WM_TIMECHANGE);
    Elapse(3600);
    CheckWidgetAlarms();
    Check(alarmStarts.size() == 1, "backward UTC correction retains consumed occurrence");
    Begin(UtcTime(2, 7, 50));
    AddAlarm(1, 8);
    CheckWidgetAlarms();
    Elapse(1200);
    simulatedSystemTime = UtcTime(2, 12, 0);
    DispatchMessage(WM_TIMECHANGE);
    Check(alarmStarts.size() == 1, "elapsed sleep alarm survives simultaneous manual correction");
}

/// Exercises a timer callback before the clock-change broadcast and harmless millisecond sampling
/// differences.
static void TestClockNotificationRace() {
    Begin(UtcTime(2, 7, 0));
    AddAlarm(1, 8);
    CheckWidgetAlarms();
    simulatedSystemTime = UtcTime(2, 10, 0);
    CheckWidgetAlarms();
    Check(alarmStarts.empty(), "forward UTC jump before broadcast never falsely dispatches alarm");
    DispatchMessage(WM_TIMECHANGE);
    Check(alarmStarts.empty(), "late clock-change notification retains no-replay behavior");
    Begin(UtcTime(2, 7, 50));
    AddAlarm(1, 8);
    CheckWidgetAlarms();
    Elapse(1200);
    simulatedSystemTime = UtcTime(2, 12, 0);
    CheckWidgetAlarms();
    DispatchMessage(WM_TIMECHANGE);
    Check(alarmStarts.size() == 1, "timer before broadcast preserves genuine elapsed sleep alarm");
    Begin(UtcTime(2, 7, 0));
    Widget* widget = AddAlarm(1, 8);
    CheckWidgetAlarms();
    simulatedSystemTime = UtcTime(1, 7, 0);
    CheckWidgetAlarms();
    DispatchMessage(WM_TIMECHANGE);
    Check(alarmStarts.empty() && widget->alarmSchedule.Next() == UtcTime(1, 8, 0),
        "backward UTC jump before broadcast replans without firing");
    Begin(UtcTime(2, 7, 59, 59));
    AddAlarm(1, 8);
    CheckWidgetAlarms();
    simulatedTimeline = simulatedSystemTime = UtcTime(2, 8, 0) - 10000;
    advanceAfterSystemRead = 20000;
    DispatchMessage(WM_TIMECHANGE);
    advanceAfterSystemRead = 0;
    Elapse(1);
    CheckWidgetAlarms();
    Check(alarmStarts.size() == 1, "time advancing during notification never loses exact alarm boundary");
    for (LONGLONG jitter : { -200000LL, 200000LL }) {
        Begin(UtcTime(2, 7, 59, 59));
        AddAlarm(1, 8);
        CheckWidgetAlarms();
        simulatedTimeline += REFRESH_SECOND_TICKS - 400000;
        simulatedSystemTime = static_cast<ULONGLONG>(static_cast<LONGLONG>(simulatedTimeline) + jitter);
        CheckWidgetAlarms();
        Check(alarmStarts.empty(), "small time sampling difference before boundary is not an alarm");
        simulatedTimeline += 400000 - jitter;
        simulatedSystemTime = UtcTime(2, 8, 0);
        CheckWidgetAlarms();
        Check(alarmStarts.size() == 1, "small sampling difference never skips actual alarm boundary");
        DispatchMessage(WM_TIMECHANGE);
        CheckWidgetAlarms();
        Check(alarmStarts.size() == 1, "small sampling difference never repeats consumed boundary");
    }
}

/// Verifies zone-only replanning, unrelated settings messages, and pending explicit-zone alarms after sleep.
static void TestZoneChanges() {
    Begin(UtcTime(2, 7, 0));
    Widget* system = AddAlarm(1, 8);
    system->config.showUtc = false;
    system->config.timeZoneKey = SYSTEM_TIME_ZONE_KEY;
    Widget* fixed = AddAlarm(2, 9);
    fixed->config.showUtc = false;
    fixed->config.timeZoneKey = L"UTC";
    CheckWidgetAlarms();
    ULONGLONG systemNext = system->alarmSchedule.Next();
    DispatchMessage(WM_SETTINGCHANGE);
    Check(system->alarmSchedule.Next() == systemNext, "unrelated setting does not reset schedule");
    SelectSystemZone(L"Central Europe Standard Time");
    DispatchMessage(WM_SETTINGCHANGE);
    Check(alarmStarts.empty(), "zone change does not catch unrelated old local time");
    Check(system->alarmSchedule.Next() == UtcTime(3, 7, 0), "system zone widget replanned in changed zone");
    Check(fixed->alarmSchedule.Next() == UtcTime(2, 9, 0), "explicit zone remains independent");
    for (UINT message : { WM_SETTINGCHANGE, WM_TIMECHANGE }) {
        Begin(UtcTime(2, 7, 50));
        AddAlarm(1, 8);
        Widget* named = AddAlarm(2, 9);
        named->config.showUtc = false;
        named->config.timeZoneKey = L"Central Europe Standard Time";
        CheckWidgetAlarms();
        Elapse(1200);
        SelectSystemZone(L"Central Europe Standard Time");
        DispatchMessage(message);
        DispatchMessage(WM_POWERBROADCAST, PBT_APMRESUMEAUTOMATIC);
        Check(alarmStarts.size() == 2,
            "UTC and named-zone sleep alarms survive zone notification before resume");
    }
    for (bool slept : { false, true }) {
        Begin(UtcTime(2, 7, 50));
        AddAlarm(1, 8);
        Widget* named = AddAlarm(2, 9);
        named->config.showUtc = false;
        named->config.timeZoneKey = L"Central Europe Standard Time";
        CheckWidgetAlarms();
        if (slept) {
            Elapse(1200);
        }
        simulatedSystemTime = UtcTime(2, 12, 0);
        SelectSystemZone(L"Central Europe Standard Time");
        DispatchMessage(WM_TIMECHANGE);
        DispatchMessage(WM_POWERBROADCAST, PBT_APMRESUMEAUTOMATIC);
        size_t expected = slept ? 2 : 0;
        Check(alarmStarts.size() == expected,
            "combined UTC/zone change only catches genuinely elapsed alarms");
    }
}

/// Tests NTP correction, system-clock independence, initial and failed samples, and stale generations.
static void TestNtp() {
    Begin(UtcTime(2, 7, 0));
    useNtpTime = true;
    ntpTimeValid = true;
    ntpClockOffset100Nanoseconds = 1800 * static_cast<LONGLONG>(REFRESH_SECOND_TICKS);
    AddAlarm(1, 8);
    CheckWidgetAlarms();
    Check(wakeTimes.back() == UtcTime(2, 7, 30), "NTP alarm translated into absolute system UTC");
    simulatedSystemTime = UtcTime(2, 10, 0);
    DispatchMessage(WM_TIMECHANGE);
    Check(alarmStarts.empty() && wakeTimes.back() == UtcTime(2, 10, 30),
        "system clock correction changes only NTP wake mapping");
    Elapse(1800);
    DispatchMessage(WM_POWERBROADCAST, PBT_APMRESUMEAUTOMATIC);
    Check(alarmStarts.size() == 1, "NTP resume catches continuous-clock due time");
    Begin(UtcTime(2, 7, 50));
    useNtpTime = true;
    ntpTimeValid = true;
    AddAlarm(1, 8);
    CheckWidgetAlarms();
    NtpResult(1200 * static_cast<LONGLONG>(REFRESH_SECOND_TICKS));
    Check(alarmStarts.size() == 1, "accepted NTP forward correction catches due alarm");
    NtpResult(1200 * static_cast<LONGLONG>(REFRESH_SECOND_TICKS));
    Check(alarmStarts.size() == 1, "duplicate NTP result cannot replay alarm");
    NtpResult(-1200 * static_cast<LONGLONG>(REFRESH_SECOND_TICKS));
    Check(alarmStarts.size() == 1, "backward NTP correction cannot replay consumed alarm");
    size_t armed = wakeTimes.size();
    NtpResult(0, false);
    Check(ntpTimeValid && ntpLastQueryFailed && wakeTimes.size() == armed,
        "failed NTP query preserves accepted time and pending wake");
    NtpResult(999, true, 1);
    Check(ntpRestarts == 1
        && ntpClockOffset100Nanoseconds == -1200 * static_cast<LONGLONG>(REFRESH_SECOND_TICKS),
        "stale NTP generation cannot change accepted correction");
    Begin(UtcTime(2, 7, 50));
    useNtpTime = true;
    AddAlarm(1, 8);
    CheckWidgetAlarms();
    NtpResult(0, false);
    Elapse(1200);
    CheckWidgetAlarms();
    Check(alarmStarts.size() == 1, "unsynchronized NTP selection retains system-clock catch-up");
    Begin(UtcTime(2, 7, 50));
    useNtpTime = true;
    AddAlarm(1, 8);
    CheckWidgetAlarms();
    Elapse(1200);
    NtpResult(0);
    Check(alarmStarts.size() == 1 && ntpTimeValid,
        "first successful NTP result preserves genuine missed alarm");
    Begin(UtcTime(2, 7, 0));
    AddAlarm(1, 8);
    CheckWidgetAlarms();
    NtpResult(3 * 3600 * static_cast<LONGLONG>(REFRESH_SECOND_TICKS));
    Check(alarmStarts.empty() && wakeTimes.back() == UtcTime(2, 8, 0),
        "NTP result cannot alter alarms while system time source is selected");
}

/// Verifies API failure handling, forced retry, unsupported wake, and independence of ordinary alarm
/// dispatch.
static void TestApiFailures() {
    for (int failure = 0; failure < 3; ++failure) {
        Begin(UtcTime(2, 7, 50));
        AddAlarm(1, 8);
        timerCreateFails = failure == 0;
        timerSetFails = failure == 1;
        wakeUnsupported = failure == 2;
        CheckWidgetAlarms();
        Check(!wakeArmed && debugMessages == 1, "wake API failure is contained and diagnosed");
        size_t requests = wakeTimes.size();
        int creations = timerCreates;
        CheckWidgetAlarms();
        Check(wakeTimes.size() == requests && timerCreates == creations, "failure does not spin on UI timer");
        timerCreateFails = false;
        timerSetFails = false;
        wakeUnsupported = false;
        DispatchMessage(WM_POWERBROADCAST, PBT_APMSUSPEND);
        Check(wakeArmed, "suspend forces retry after transient timer failure");
        Elapse(1200);
        DispatchMessage(WM_POWERBROADCAST, PBT_APMRESUMEAUTOMATIC);
        Check(alarmStarts.size() == 1, "timer failure never disables ordinary catch-up");
    }
    Begin(UtcTime(2, 7, 50));
    AddAlarm(1, 8);
    CheckWidgetAlarms();
    zoneReadFails = true;
    Elapse(1200);
    DispatchMessage(WM_TIMECHANGE);
    Check(alarmStarts.size() == 1, "failed timezone read does not erase elapsed alarm");
    size_t starts = alarmStarts.size();
    DispatchMessage(WM_POWERBROADCAST, PBT_APMRESUMEAUTOMATIC, 0, hSettings);
    DispatchMessage(WM_TIMECHANGE, 0, 0, hSettings);
    Check(alarmStarts.size() == starts, "noncontroller notifications never dispatch duplicate alarms");
}

/// Runs production alarm integration against simulated clocks and harmless API adapters only.
int main() {
    LoadTimeZoneList(&timeZones);
    TestWakeRequests();
    TestSuspendAndResume();
    TestClockChanges();
    TestClockNotificationRace();
    TestZoneChanges();
    TestNtp();
    TestApiFailures();
    CancelAlarmWakeTimer();
    if (failures == 0) {
        std::puts("PASS: wake requests, suspend/resume, clock/zone changes, NTP, and API failures");
    }
    return failures == 0 ? 0 : 1;
}
