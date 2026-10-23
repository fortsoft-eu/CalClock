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
 * Last modified for version 1.6.1.1
 */

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include "../CalClock/NtpClient.h"
#include "../CalClock/TimeSignal.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

static const ULONGLONG TEST_NOW = 132000000000000000ULL;
static const LONGLONG TEST_CORRECTION = 1234567;
static ULONGLONG monotonicTime = TEST_NOW;
static ULONGLONG systemTime = TEST_NOW;
static ULONGLONG sendTime = 0;
static ULONGLONG simulatedUiTick = 0;
static LONGLONG systemJumpOnReceive = 0;
static BYTE lastRequest[48] = {};
static ADDRINFOW testAddress = {};
static DYNAMIC_TIME_ZONE_INFORMATION simulatedSystemZone = {};
static NtpThreadResult* capturedResult = nullptr;
static bool invalidReply = false;
static bool simulateSystemZone = false;
static bool simulateUiClock = false;
static int systemZoneReads = 0;
static std::vector<ULONGLONG> capturedSignalTargets;

static int WSAAPI TestGetAddrInfo(PCWSTR node, PCWSTR service, const ADDRINFOW* hints, PADDRINFOW* result);
static void WSAAPI TestFreeAddrInfo(PADDRINFOW address);
static SOCKET WSAAPI TestSocket(int family, int type, int protocol);
static int WSAAPI TestConnect(SOCKET handle, const sockaddr* address, int length);
static int WSAAPI TestSetSocketOption(SOCKET handle, int level, int option, const char* value, int length);
static int WSAAPI TestSend(SOCKET handle, const char* buffer, int length, int flags);
static int WSAAPI TestReceive(SOCKET handle, char* buffer, int length, int flags);
static int WSAAPI TestCloseSocket(SOCKET handle);
static BOOL WINAPI TestPostMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
static FARPROC WINAPI TestTimeZoneGetProcAddress(HMODULE module, LPCSTR name);
static DWORD WINAPI TestGetDynamicTimeZoneInformation(PDYNAMIC_TIME_ZONE_INFORMATION information);
static bool TestStartTimeSignalPlayback(ULONGLONG target, bool muted, bool generatedTone, double volume,
    HWND notifyWindow, UINT notifyMessage);
static ULONGLONG WINAPI TestGetTickCount64();
static BOOL WINAPI TestGetCursorPos(LPPOINT point);
static HCURSOR WINAPI TestSetCursor(HCURSOR cursor);

static HWND WINAPI TestCreateWidgetWindow(DWORD extended, LPCWSTR name, LPCWSTR text, DWORD style,
    int x, int y, int width, int height, HWND parent, HMENU menu, HINSTANCE instance, LPVOID parameter);

#define CreateWindowExW TestCreateWidgetWindow
#define StartTimeSignalPlayback TestStartTimeSignalPlayback
#define GetTickCount64 TestGetTickCount64
#define GetCursorPos TestGetCursorPos
#define SetCursor TestSetCursor
#include "../CalClock/CalClock.cpp"
#undef CreateWindowExW
#undef StartTimeSignalPlayback
#undef GetTickCount64
#undef GetCursorPos
#undef SetCursor
#define GetAddrInfoW TestGetAddrInfo
#define FreeAddrInfoW TestFreeAddrInfo
#define socket TestSocket
#define connect TestConnect
#define setsockopt TestSetSocketOption
#define send TestSend
#define recv TestReceive
#define closesocket TestCloseSocket
#define PostMessageW TestPostMessage
#include "../CalClock/NtpClient.cpp"
#undef GetAddrInfoW
#undef FreeAddrInfoW
#undef socket
#undef connect
#undef setsockopt
#undef send
#undef recv
#undef closesocket
#undef PostMessageW
#include "../CalClock/TimeSignal.cpp"
#define GetProcAddress TestTimeZoneGetProcAddress
#include "../CalClock/TimeZoneSupport.cpp"
#undef GetProcAddress

/// Simulates failed native window creation so display-rebuild tests cannot open or activate any windows.
static HWND WINAPI TestCreateWidgetWindow(DWORD extended, LPCWSTR name, LPCWSTR text, DWORD style,
        int x, int y, int width, int height, HWND parent, HMENU menu, HINSTANCE instance, LPVOID parameter) {
    return nullptr;
}

/// Substitutes only the system-zone reader; named-zone conversion and all other Windows functions remain native.
static FARPROC WINAPI TestTimeZoneGetProcAddress(HMODULE module, LPCSTR name) {
    if (std::strcmp(name, "GetDynamicTimeZoneInformation") == 0) {
        return reinterpret_cast<FARPROC>(TestGetDynamicTimeZoneInformation);
    }
    return GetProcAddress(module, name);
}

/// Returns test-owned zone settings when requested without changing the computer's zone or daylight-saving settings.
static DWORD WINAPI TestGetDynamicTimeZoneInformation(PDYNAMIC_TIME_ZONE_INFORMATION information) {
    if (!simulateSystemZone) {
        return GetDynamicTimeZoneInformation(information);
    }
    *information = simulatedSystemZone;
    systemZoneReads++;
    return TIME_ZONE_ID_UNKNOWN;
}

/// Records planned pips without creating an audio worker, generating tones, or opening any audio device.
static bool TestStartTimeSignalPlayback(ULONGLONG target, bool muted, bool generatedTone, double volume,
        HWND notifyWindow, UINT notifyMessage) {
    capturedSignalTargets.push_back(target);
    return true;
}

/// Supplies a fixed UI uptime for refresh-gating tests while retaining ordinary uptime in the other scenarios.
static ULONGLONG WINAPI TestGetTickCount64() {
    return simulateUiClock ? simulatedUiTick : GetTickCount64();
}

/// Prevents timer-dispatch tests from inspecting or tracking the user's pointer.
static BOOL WINAPI TestGetCursorPos(LPPOINT point) {
    return FALSE;
}

/// Prevents timer-dispatch tests from changing the user's pointer image.
static HCURSOR WINAPI TestSetCursor(HCURSOR cursor) {
    return nullptr;
}

/// Returns simulated Windows UTC in 100-nanosecond FILETIME ticks, including system-clock jumps made by the test.
ULONGLONG CurrentFileTimeValue() {
    return systemTime;
}

/// Returns the independently advanced simulated continuous clock in 100-nanosecond FILETIME ticks.
ULONGLONG MonotonicFileTimeValue() {
    return monotonicTime;
}

/// Returns the shared fake server address without DNS lookup; the caller borrows it rather than owning it.
static int WSAAPI TestGetAddrInfo(PCWSTR node, PCWSTR service, const ADDRINFOW* hints, PADDRINFOW* result) {
    *result = &testAddress;
    return 0;
}

/// Leaves the shared fake address intact because the resolver replacement does not allocate address records.
static void WSAAPI TestFreeAddrInfo(PADDRINFOW address) {}

/// Returns a fixed fake socket handle without creating an operating-system socket.
static SOCKET WSAAPI TestSocket(int family, int type, int protocol) {
    return 1;
}

/// Reports a successful connection for the fake socket without contacting a server.
static int WSAAPI TestConnect(SOCKET handle, const sockaddr* address, int length) {
    return 0;
}

/// Accepts socket options for the simulated exchange without configuring a real socket.
static int WSAAPI TestSetSocketOption(SOCKET handle, int level, int option, const char* value, int length) {
    return 0;
}

/// Saves the 48-byte NTP request and its continuous-clock send time, then reports success without transmission.
static int WSAAPI TestSend(SOCKET handle, const char* buffer, int length, int flags) {
    std::memcpy(lastRequest, buffer, sizeof(lastRequest));
    sendTime = monotonicTime;
    return length;
}

/// Builds a valid or deliberately invalid 48-byte NTP reply using the saved request and fixed server correction.
/// Advances simulated time by 12 ms and applies the requested system-clock jump during receipt.
static int WSAAPI TestReceive(SOCKET handle, char* buffer, int length, int flags) {
    BYTE response[48] = {};
    response[0] = invalidReply ? 0xE4 : 0x24;
    response[1] = 1;
    std::memcpy(response + 24, lastRequest + 40, 8);
    WriteNtpTimestamp(response + 32, sendTime + TEST_CORRECTION + 50000);
    WriteNtpTimestamp(response + 40, sendTime + TEST_CORRECTION + 70000);
    monotonicTime += 120000;
    systemTime = static_cast<ULONGLONG>(static_cast<LONGLONG>(systemTime) + 120000 + systemJumpOnReceive);
    std::memcpy(buffer, response, sizeof(response));
    return sizeof(response);
}

/// Reports successful closure of the fake socket without releasing an operating-system resource.
static int WSAAPI TestCloseSocket(SOCKET handle) {
    return 0;
}

/// Captures the worker result instead of queuing a window message so the test controls when it is delivered.
static BOOL WINAPI TestPostMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    capturedResult = reinterpret_cast<NtpThreadResult*>(lParam);
    return TRUE;
}

/// Writes the failure message to standard error and exits with status 1 when the required condition is false.
static void Require(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "%s\n", message);
        std::exit(1);
    }
}

/// Runs the NTP worker synchronously against two fake servers with the current generation and cancellation flags.
/// Fails the test if the worker does not return a captured result.
static void RunQuery() {
    NtpThreadParameters* parameters = new NtpThreadParameters;
    parameters->serverList = L"one; two";
    parameters->notifyWindow = reinterpret_cast<HWND>(1);
    parameters->generation = ntpGeneration.load();
    parameters->stopRequested = &ntpStopRequested;
    parameters->queryRunning = &ntpQueryRunning;
    NtpThreadProc(parameters);
    Require(capturedResult != nullptr, "NTP worker did not return a result");
}

/// Verifies that display reconstruction preserves ringing, audio ownership and duplicate suppression.
/// Native window creation is inert; shutdown must still signal and release the retained audio events.
static void TestAlarmDisplayRecreation() {
    SYSTEMTIME time = {};
    time.wYear = 2026;
    time.wMonth = 10;
    time.wDay = 22;
    time.wHour = 7;
    time.wMinute = 30;
    systemTime = SystemTimeValue(time);
    bool previousUseNtp = useNtpTime;
    useNtpTime = false;
    const WidgetType types[] = { WIDGET_ANALOG, WIDGET_DIGITAL, WIDGET_PANEL, WIDGET_FULLSCREEN };
    std::vector<HANDLE> stopEvents;
    for (WidgetType type : types) {
        std::unique_ptr<Widget> widget = std::make_unique<Widget>();
        widget->config.type = type;
        widget->config.visible = false;
        widget->config.showUtc = true;
        widget->config.alarmEnabled = true;
        widget->config.alarmHour = 7;
        widget->config.alarmMinute = 30;
        widget->window = reinterpret_cast<HWND>(1);
        widget->alarmActive = true;
        widget->flashPhase = true;
        widget->lastAlarmDate = 20261022;
        widget->lastAlarmMinute = 450;
        widget->lastObservedAlarmDate = 20261022;
        widget->lastObservedAlarmMinute = 450;
        widget->audioGeneration = 42;
        widget->audioStopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
        widget->audioMuteEvent = CreateEventW(nullptr, TRUE, TRUE, nullptr);
        Require(widget->audioStopEvent != nullptr && widget->audioMuteEvent != nullptr, "Alarm events exist");
        HANDLE retained = nullptr;
        Require(DuplicateHandle(GetCurrentProcess(), widget->audioStopEvent, GetCurrentProcess(), &retained,
            0, FALSE, DUPLICATE_SAME_ACCESS) != FALSE, "Retain playback cancellation event");
        stopEvents.push_back(retained);
        widgets.push_back(std::move(widget));
    }
    WindowProc(hController, WM_REFRESH_DISPLAYS, 0, 0);
    for (const std::unique_ptr<Widget>& widget : widgets) {
        Require(widget->alarmActive && widget->flashPhase && widget->config.alarmEnabled,
            "Display change interrupted a ringing alarm");
        Require(widget->audioStopEvent != nullptr && widget->audioMuteEvent != nullptr && widget->audioGeneration == 42,
            "Display change released or invalidated live audio");
        Require(WaitForSingleObject(widget->audioStopEvent, 0) == WAIT_TIMEOUT
            && WaitForSingleObject(widget->audioMuteEvent, 0) == WAIT_OBJECT_0,
            "Display change altered audio cancellation or mute state");
        Require(widget->lastAlarmDate == 20261022
            && widget->lastAlarmMinute == 450
            && widget->lastObservedAlarmDate == 20261022
            && widget->lastObservedAlarmMinute == 450,
            "Display change discarded the alarm occurrence");
        systemTime += 10 * 10000000ULL;
        CheckWidgetAlarm(widget.get());
        systemTime -= 10 * 10000000ULL;
        Require(widget->audioGeneration == 42, "Display change replayed the same alarm minute");
    }
    DestroyWidgetWindows();
    for (const std::unique_ptr<Widget>& widget : widgets) {
        Require(!widget->alarmActive && widget->audioStopEvent == nullptr && widget->audioMuteEvent == nullptr,
            "Shutdown did not stop the preserved alarm");
    }
    for (HANDLE event : stopEvents) {
        Require(WaitForSingleObject(event, 0) == WAIT_OBJECT_0, "Shutdown did not signal audio cancellation");
        CloseHandle(event);
    }
    widgets.clear();
    useNtpTime = previousUseNtp;
    std::puts("PASS: display changes preserve alarms and audio; shutdown cancels playback");
}

/// Constructs normalized UTC-like fields and calculates their weekday without reading or changing the system clock.
static SYSTEMTIME TestTime(WORD year, WORD month, WORD day, WORD hour, WORD minute, WORD second, WORD milliseconds = 0) {
    SYSTEMTIME time = {};
    time.wYear = year;
    time.wMonth = month;
    time.wDay = day;
    time.wHour = hour;
    time.wMinute = minute;
    time.wSecond = second;
    time.wMilliseconds = milliseconds;
    FILETIME fileTime = {};
    Require(SystemTimeToFileTime(&time, &fileTime) && FileTimeToSystemTime(&fileTime, &time), "Valid test date");
    return time;
}

/// Converts simulated FILETIME ticks into fields without applying any zone or offset.
static SYSTEMTIME TestTimeFromTicks(ULONGLONG ticks) {
    ULARGE_INTEGER value = {};
    value.QuadPart = ticks;
    FILETIME fileTime = { value.LowPart, value.HighPart };
    SYSTEMTIME time = {};
    Require(FileTimeToSystemTime(&fileTime, &time) != FALSE, "Valid test FILETIME");
    return time;
}

/// Reports actual and expected fields when display conversion disagrees, including date, fraction, and weekday.
static void RequireTime(const SYSTEMTIME& actual, const SYSTEMTIME& expected) {
    if (actual.wYear != expected.wYear
            || actual.wMonth != expected.wMonth
            || actual.wDay != expected.wDay
            || actual.wHour != expected.wHour
            || actual.wMinute != expected.wMinute
            || actual.wSecond != expected.wSecond
            || actual.wMilliseconds != expected.wMilliseconds
            || actual.wDayOfWeek != expected.wDayOfWeek) {
        std::fprintf(stderr, "Displayed %04u-%02u-%02u %02u:%02u:%02u.%03u; expected %04u-%02u-%02u %02u:%02u:%02u.%03u\n",
            actual.wYear, actual.wMonth, actual.wDay, actual.wHour, actual.wMinute, actual.wSecond, actual.wMilliseconds,
            expected.wYear, expected.wMonth, expected.wDay, expected.wHour, expected.wMinute, expected.wSecond
            expected.wMilliseconds);
        Require(false, "Displayed time mismatch");
    }
}

/// Verifies supplied UTC, system-clock, and independent NTP paths plus the actual digital text without seconds.
static void RequireDisplaySources(const WidgetConfig& config, ULONGLONG utc, const SYSTEMTIME& expected) {
    SYSTEMTIME displayed = {};
    GetDisplayedTime(config, &displayed, utc);
    RequireTime(displayed, expected);
    wchar_t expectedText[16] = {};
    swprintf_s(expectedText, L"%02u:%02u", expected.wHour, expected.wMinute);
    for (bool ntp : { false, true }) {
        useNtpTime = ntp;
        ntpTimeValid = true;
        monotonicTime = utc - 7200 * FILE_TIME_TICKS_PER_SECOND;
        ntpClockOffset100Nanoseconds = 7200 * FILE_TIME_TICKS_PER_SECOND;
        systemTime = ntp ? utc + 36 * 3600 * FILE_TIME_TICKS_PER_SECOND : utc;
        GetDisplayedTime(config, &displayed);
        RequireTime(displayed, expected);
        wchar_t actualText[32] = {};
        GetDigitalTimeText(config, actualText, ARRAYSIZE(actualText));
        Require(std::wcscmp(actualText, expectedText) == 0, "Digital text without seconds follows displayed time");
    }
}

/// Finds an installed named zone for deterministic seasonal rules while retaining native Windows conversion.
static DYNAMIC_TIME_ZONE_INFORMATION TestTimeZone(const wchar_t* key) {
    for (const DYNAMIC_TIME_ZONE_INFORMATION& zone : timeZones) {
        if (std::wcscmp(zone.TimeZoneKeyName, key) == 0) {
            return zone;
        }
    }
    Require(false, "Required test time zone is installed");
    return DYNAMIC_TIME_ZONE_INFORMATION{};
}

/// Checks that UTC offsets move seasonal-transition instants, including fractional boundaries and repeated hours.
static void TestDaylightSavingOffsets() {
    WidgetConfig config = {};
    config.type = WIDGET_DIGITAL;
    config.language = LANG_CS;
    config.timeFormat = TIME_FORMAT_24_HOUR;
    config.timeZoneKey = L"Central Europe Standard Time";
    const SYSTEMTIME boundaries[] = {
        TestTime(2026, 3, 29, 1, 0, 0),
        TestTime(2026, 10, 25, 1, 0, 0),
        TestTime(2027, 3, 28, 1, 0, 0),
        TestTime(2027, 10, 31, 1, 0, 0)
    };
    const LONGLONG offsets[] = { 0, 10000, -10000, 250, -250 };
    const LONGLONG relativeMilliseconds[] = { -1, 0, 10000 };
    for (const SYSTEMTIME& boundary : boundaries) {
        bool spring = boundary.wMonth == 3;
        for (LONGLONG offset : offsets) {
            config.offsetMilliseconds = offset;
            for (LONGLONG relative : relativeMilliseconds) {
                LONGLONG correctedUtc = static_cast<LONGLONG>(SystemTimeValue(boundary)) + relative * 10000;
                ULONGLONG sourceUtc = static_cast<ULONGLONG>(correctedUtc - offset * 10000);
                int zoneHours = spring == relative >= 0 ? 2 : 1;
                SYSTEMTIME expected = TestTimeFromTicks(correctedUtc + zoneHours * 3600 * FILE_TIME_TICKS_PER_SECOND);
                RequireDisplaySources(config, sourceUtc, expected);
            }
        }
    }
    config.offsetMilliseconds = 10000;
    RequireDisplaySources(config, SystemTimeValue(TestTime(2026, 12, 31, 23, 59, 55)),
        TestTime(2027, 1, 1, 1, 0, 5));
    config.offsetMilliseconds = -10000;
    RequireDisplaySources(config, SystemTimeValue(TestTime(2027, 1, 1, 0, 0, 5)),
        TestTime(2027, 1, 1, 0, 59, 55));
    config.offsetMilliseconds = 10000;
    for (const SYSTEMTIME& boundary : boundaries) {
        config.timeZoneKey = L"UTC+01:00";
        SYSTEMTIME fixed = TestTimeFromTicks(SystemTimeValue(boundary) + 3610 * FILE_TIME_TICKS_PER_SECOND);
        RequireDisplaySources(config, SystemTimeValue(boundary), fixed);
        config.showUtc = true;
        SYSTEMTIME utc = TestTimeFromTicks(SystemTimeValue(boundary) + 10 * FILE_TIME_TICKS_PER_SECOND);
        RequireDisplaySources(config, SystemTimeValue(boundary), utc);
        config.showUtc = false;
    }
    std::puts("PASS: DST starts/ends, shifted boundaries, fractional offsets, year rollover, UTC/fixed, digital text");
}

/// Verifies fresh system-zone and automatic-seasonal settings, keeping explicit named and fixed choices independent.
static void TestSystemTimeZoneChanges() {
    Require(!timeZones.empty() && std::wcscmp(timeZones[0].TimeZoneKeyName, SYSTEM_TIME_ZONE_KEY) == 0,
        "System time zone is the first selectable entry");
    WidgetConfig config = {};
    config.type = WIDGET_DIGITAL;
    config.language = LANG_CS;
    config.timeFormat = TIME_FORMAT_24_HOUR;
    config.timeZoneKey = SYSTEM_TIME_ZONE_KEY;
    ULONGLONG utc = SystemTimeValue(TestTime(2026, 7, 1, 12, 0, 0));
    simulateSystemZone = true;
    simulatedSystemZone = TestTimeZone(L"Central Europe Standard Time");
    RequireDisplaySources(config, utc, TestTime(2026, 7, 1, 14, 0, 0));
    int previousReads = systemZoneReads;
    simulatedSystemZone = TestTimeZone(L"Tokyo Standard Time");
    RequireDisplaySources(config, utc, TestTime(2026, 7, 1, 21, 0, 0));
    Require(systemZoneReads >= previousReads + 3, "System choice queries fresh Windows zone settings");
    config.timeZoneKey = L"Central Europe Standard Time";
    RequireDisplaySources(config, utc, TestTime(2026, 7, 1, 14, 0, 0));
    config.timeZoneKey = L"UTC+01:00";
    RequireDisplaySources(config, utc, TestTime(2026, 7, 1, 13, 0, 0));
    config.timeZoneKey = SYSTEM_TIME_ZONE_KEY;
    simulatedSystemZone = TestTimeZone(L"Central Europe Standard Time");
    simulatedSystemZone.DynamicDaylightTimeDisabled = TRUE;
    ZeroMemory(&simulatedSystemZone.StandardDate, sizeof(simulatedSystemZone.StandardDate));
    ZeroMemory(&simulatedSystemZone.DaylightDate, sizeof(simulatedSystemZone.DaylightDate));
    RequireDisplaySources(config, utc, TestTime(2026, 7, 1, 13, 0, 0));
    simulatedSystemZone = TestTimeZone(L"Central Europe Standard Time");
    simulatedSystemZone.DynamicDaylightTimeDisabled = TRUE;
    RequireDisplaySources(config, utc, TestTime(2026, 7, 1, 14, 0, 0));
    simulateSystemZone = false;
    std::puts("PASS: system-zone changes and seasonal settings are fresh; explicit choices remain independent");
}

/// Checks defaults and in-memory XML round trips without opening the clipboard or writing any settings files.
static void TestTimeZonePersistence() {
    for (int type = 0; type < WIDGET_TYPE_COUNT; type++) {
        WidgetConfig config = DefaultConfig(static_cast<WidgetType>(type), 0);
        Require(config.timeZoneKey == SYSTEM_TIME_ZONE_KEY, "New widgets follow the system time zone");
        for (const AdditionalClockConfig& clock : config.additionalClocks) {
            Require(clock.timeZoneKey == SYSTEM_TIME_ZONE_KEY, "New additional clocks follow the system time zone");
        }
    }
    const std::string legacyXml = "<CalClockSettings version=\"1\"><Widget id=\"1\"/></CalClockSettings>";
    std::vector<BYTE> legacyBytes(legacyXml.begin(), legacyXml.end());
    std::vector<WidgetConfig> legacy;
    Require(DeserializeWidgetClipboardData(legacyBytes, LANG_CS, CreateStoredWidgetDefaults, &legacy)
        && legacy.size() == 1 && legacy[0].timeZoneKey == GetSystemTimeZoneKey(timeZones),
        "Older settings without a zone retain their original explicit system-zone default");
    const wchar_t* keys[] = { SYSTEM_TIME_ZONE_KEY, L"Central Europe Standard Time", L"UTC+01:00" };
    for (const wchar_t* key : keys) {
        WidgetConfig config = CreateStoredWidgetDefaults(WIDGET_PANEL, 0, LANG_CS, FONT_ANTIALIAS_CLEARTYPE);
        config.timeZoneKey = key;
        config.offsetMilliseconds = -10000;
        config.additionalClocks[0].timeZoneKey = L"Tokyo Standard Time";
        config.additionalClocks[1].timeZoneKey = L"UTC+02:00";
        std::vector<BYTE> bytes;
        std::vector<WidgetConfig> loaded;
        Require(SerializeWidgetClipboardData(std::vector<WidgetConfig>{ config }, & bytes)
            && DeserializeWidgetClipboardData(bytes, LANG_CS, CreateStoredWidgetDefaults, &loaded)
            && loaded.size() == 1, "Time-zone settings survive an XML round trip");
        Require(loaded[0].timeZoneKey == key && loaded[0].offsetMilliseconds == -10000
            && loaded[0].additionalClocks[0].timeZoneKey == L"Tokyo Standard Time"
            && loaded[0].additionalClocks[1].timeZoneKey == L"UTC+02:00",
            "Existing explicit zones, system choice and custom offset are preserved");
    }
    std::puts("PASS: system-zone defaults and existing explicit choices/offsets persist through in-memory XML");
}

/// Checks one approaching six-second signal through the real scheduler while audio and native windows are inert.
static void RequireSignalCandidate(const WidgetConfig& config, ULONGLONG utc, bool expected,
        int lastAlarmDate = -1, int lastAlarmMinute = -1,
        ULONGLONG expectedDelay = 6 * FILE_TIME_TICKS_PER_SECOND) {
    Require(widgets.empty() && timeSignalSequences.empty(), "Signal scenario starts without native playback");
    useNtpTime = false;
    systemTime = utc;
    monotonicTime = utc;
    currentTimeSignalOffset = 0;
    currentTimeSignalSources.clear();
    capturedSignalTargets.clear();
    std::unique_ptr<Widget> widget = std::make_unique<Widget>();
    widget->config = config;
    widget->lastAlarmDate = lastAlarmDate;
    widget->lastAlarmMinute = lastAlarmMinute;
    widgets.push_back(std::move(widget));
    CheckTimeSignals();
    Require(capturedSignalTargets.size() == (expected ? 1U : 0U), "Only the actual future displayed boundary is signaled");
    if (expected) {
        Require(capturedSignalTargets[0] == monotonicTime + expectedDelay,
            "Final pip occurs at the approaching transition, respecting the custom offset");
    }
    currentTimeSignalSources.clear();
    capturedSignalTargets.clear();
    widgets.clear();
}

/// Rejects phantom skipped-hour alarms and duplicate repeated-hour alarms, including shifted and half-hour changes.
static void TestDaylightSavingSignals() {
    WidgetConfig config = {};
    config.id = 1;
    config.type = WIDGET_ANALOG;
    config.timeZoneKey = L"Central Europe Standard Time";
    config.alarmEnabled = true;
    config.alarmTimeSignal = true;
    config.alarmMinute = 0;
    const LONGLONG offsets[] = { 0, 10000, -10000 };
    for (LONGLONG offset : offsets) {
        config.offsetMilliseconds = offset;
        ULONGLONG spring = SystemTimeValue(TestTime(2026, 3, 29, 0, 59, 54)) - offset * 10000;
        config.alarmHour = 3;
        RequireSignalCandidate(config, spring, true);
        config.alarmHour = 2;
        RequireSignalCandidate(config, spring, false);
        ULONGLONG autumn = SystemTimeValue(TestTime(2026, 10, 25, 0, 59, 54)) - offset * 10000;
        RequireSignalCandidate(config, autumn, true);
        config.alarmHour = 3;
        RequireSignalCandidate(config, autumn, false);
    }
    config.offsetMilliseconds = 0;
    config.alarmHour = 2;
    config.alarmMinute = 30;
    RequireSignalCandidate(config, SystemTimeValue(TestTime(2026, 10, 25, 0, 29, 54)), true);
    RequireSignalCandidate(config, SystemTimeValue(TestTime(2026, 10, 25, 1, 29, 54)), false, 20261025, 150);
    config.alarmEnabled = false;
    config.timeSignalEnabled = true;
    config.timeSignal = TIME_SIGNAL_EVERY_HOUR;
    const LONGLONG fractionalOffsets[] = { -125, 125 };
    ULONGLONG ordinaryHour = SystemTimeValue(TestTime(2026, 10, 22, 11, 0, 0));
    for (LONGLONG offset : fractionalOffsets) {
        config.offsetMilliseconds = offset;
        ULONGLONG source = ordinaryHour - offset * 10000 - 6 * FILE_TIME_TICKS_PER_SECOND + 1;
        RequireSignalCandidate(config, source, true, -1, -1, 6 * FILE_TIME_TICKS_PER_SECOND - 1);
        SYSTEMTIME displayedBoundary = {};
        GetDisplayedTime(config, &displayedBoundary, ordinaryHour - offset * 10000);
        RequireTime(displayedBoundary, TestTime(2026, 10, 22, 13, 0, 0));
    }
    config.offsetMilliseconds = 0;
    config.timeZoneKey = L"Lord Howe Standard Time";
    ULONGLONG lordHowe = SystemTimeValue(TestTime(2026, 10, 3, 15, 29, 54));
    SYSTEMTIME lordHoweBoundary = {};
    GetDisplayedTime(config, &lordHoweBoundary, lordHowe + 6 * FILE_TIME_TICKS_PER_SECOND);
    RequireTime(lordHoweBoundary, TestTime(2026, 10, 4, 2, 30, 0));
    RequireSignalCandidate(config, lordHowe, false);
    config.timeSignal = TIME_SIGNAL_EVERY_HALF_HOUR;
    RequireSignalCandidate(config, lordHowe, true);
    config.timeZoneKey = SYSTEM_TIME_ZONE_KEY;
    simulateSystemZone = true;
    simulatedSystemZone = TestTimeZone(L"Central Europe Standard Time");
    simulatedSystemZone.DynamicDaylightTimeDisabled = TRUE;
    simulatedSystemZone.DaylightBias = -15;
    ULONGLONG quarterShift = SystemTimeValue(TestTime(2026, 3, 29, 0, 59, 54));
    SYSTEMTIME quarterBoundary = {};
    GetDisplayedTime(config, &quarterBoundary, quarterShift + 6 * FILE_TIME_TICKS_PER_SECOND);
    RequireTime(quarterBoundary, TestTime(2026, 3, 29, 2, 15, 0));
    config.timeSignal = TIME_SIGNAL_EVERY_QUARTER_HOUR;
    RequireSignalCandidate(config, quarterShift, true);
    config.timeSignal = TIME_SIGNAL_EVERY_HALF_HOUR;
    RequireSignalCandidate(config, quarterShift, false);
    config.timeSignal = TIME_SIGNAL_EVERY_HOUR;
    RequireSignalCandidate(config, quarterShift, false);
    config.timeSignal = TIME_SIGNAL_EVERY_HALF_HOUR;
    RequireSignalCandidate(config, SystemTimeValue(TestTime(2026, 3, 29, 1, 14, 54)), true);
    config.timeSignal = TIME_SIGNAL_EVERY_HOUR;
    RequireSignalCandidate(config, SystemTimeValue(TestTime(2026, 3, 29, 1, 44, 54)), true);
    simulateSystemZone = false;
    ULONGLONG hour = SystemTimeValue(TestTime(2026, 10, 25, 2, 0, 0));
    Require(IsTimeSignalBoundary(hour, TIME_SIGNAL_EVERY_HOUR)
        && !IsTimeSignalBoundary(hour + FILE_TIME_TICKS_PER_SECOND, TIME_SIGNAL_EVERY_HOUR)
        && !IsTimeSignalBoundary(hour + 1, TIME_SIGNAL_EVERY_HOUR)
        && !IsTimeSignalBoundary(hour, TIME_SIGNAL_NONE)
        && !IsTimeSignalBoundary(hour, static_cast<TimeSignalMode>(TIME_SIGNAL_COUNT)),
        "Signal boundaries require exact enabled intervals");
    std::puts("PASS: DST alarm pips, shifted transitions, repeated-hour deduplication and half-hour seasonal changes");
    std::puts("PASS: hourly pips land on displayed HH:00 with positive/negative fractional and sub-ms clock offsets");
    std::puts("PASS: a 15-minute seasonal shift preserves quarter-hour, half-hour and whole-hour civil boundaries");
}

/// Advances simulated application UTC without touching Windows time; the NTP case deliberately disagrees with Windows.
static void SetTestApplicationClock(ULONGLONG utc, bool ntp) {
    useNtpTime = ntp;
    ntpTimeValid = true;
    ntpClockOffset100Nanoseconds = 0;
    monotonicTime = utc;
    systemTime = ntp ? utc + 36 * 3600 * FILE_TIME_TICKS_PER_SECOND : utc;
}

/// Verifies actual alarm activation and its optional final pip at the same corrected instant without native windows.
static void RequireAlarmAndSignal(const WidgetConfig& config, ULONGLONG target, const SYSTEMTIME& displayedTarget,
        bool expectedAlarm, bool ntp, int lastAlarmDate = -1, int lastAlarmMinute = -1) {
    Require(widgets.empty() && timeSignalSequences.empty() && hTimeSignalThread == nullptr,
        "Integrated alarm scenario starts without native playback");
    Require(config.visible && !config.runCommand && !config.callRemoteScript,
        "Integrated alarm cannot reveal windows, save visibility or launch external actions");
    currentTimeSignalOffset = 0;
    currentTimeSignalSources.clear();
    capturedSignalTargets.clear();
    std::unique_ptr<Widget> widget = std::make_unique<Widget>();
    widget->config = config;
    widget->lastAlarmDate = lastAlarmDate;
    widget->lastAlarmMinute = lastAlarmMinute;
    widgets.push_back(std::move(widget));
    Widget* current = widgets[0].get();
    SetTestApplicationClock(target - 6 * FILE_TIME_TICKS_PER_SECOND + 1, ntp);
    CheckWidgetAlarm(current);
    Require(!current->alarmActive, "Alarm is inactive before its target");
    CheckTimeSignals();
    bool expectedPips = config.timeSignalEnabled || config.alarmTimeSignal && expectedAlarm;
    Require(capturedSignalTargets.size() == (expectedPips ? 1U : 0U),
        "Only an enabled real alarm or regular interval schedules pips");
    if (expectedPips) {
        Require(capturedSignalTargets[0] == target && currentTimeSignalSources.size() == 1,
            "The final pip and alarm share one exact corrected target");
        const TimeSignalSourceGroup& group = currentTimeSignalSources[0];
        Require(group.regularWidgetIds.size() == (config.timeSignalEnabled ? 1U : 0U)
            && group.alarmWidgetIds.size() == (config.alarmTimeSignal && expectedAlarm ? 1U : 0U),
            "Coincident regular and alarm pips share their sequence without duplicate contributors");
    }
    SetTestApplicationClock(target - 1, ntp);
    CheckWidgetAlarm(current);
    Require(!current->alarmActive, "Alarm does not activate one clock tick before its final pip");
    SetTestApplicationClock(target, ntp);
    CheckWidgetAlarm(current);
    Require(current->alarmActive == expectedAlarm, "Alarm activation matches the actual corrected civil minute");
    SYSTEMTIME displayed = {};
    GetDisplayedTime(config, &displayed);
    RequireTime(displayed, displayedTarget);
    if (expectedAlarm) {
        int date = displayed.wYear * 10000 + displayed.wMonth * 100 + displayed.wDay;
        int minute = displayed.wHour * 60 + displayed.wMinute;
        Require(current->lastAlarmDate == date && current->lastAlarmMinute == minute,
            "The alarm remembers the same civil occurrence as its final pip");
    }
    ULONG generation = current->audioGeneration;
    SetTestApplicationClock(target + 1, ntp);
    CheckWidgetAlarm(current);
    CheckTimeSignals();
    Require(current->audioGeneration == generation
        && capturedSignalTargets.size() == (expectedPips ? 1U : 0U), "The occurrence cannot restart alarm or pips");
    Require(current->window == nullptr
        && current->analogChild == nullptr
        && current->audioStopEvent == nullptr
        && current->audioMuteEvent == nullptr
        && hTimeSignalThread == nullptr,
        "Integrated alarms never create windows or native audio");
    currentTimeSignalSources.clear();
    capturedSignalTargets.clear();
    widgets.clear();
}

/// Exercises skipped, valid and repeated alarm occurrences with optional pips, independent time sources and offsets.
static void TestIntegratedDaylightSavingAlarms() {
    WidgetConfig config = {};
    config.id = 1;
    config.type = WIDGET_ANALOG;
    config.visible = true;
    config.timeZoneKey = L"Central Europe Standard Time";
    config.alarmEnabled = true;
    config.alarmMinute = 0;
    const LONGLONG offsets[] = { 0, 10000, -10000, 125, -125 };
    for (LONGLONG offset : offsets) {
        config.offsetMilliseconds = offset;
        ULONGLONG spring = SystemTimeValue(TestTime(2026, 3, 29, 1, 0, 0)) - offset * 10000;
        ULONGLONG autumn = SystemTimeValue(TestTime(2026, 10, 25, 1, 0, 0)) - offset * 10000;
        for (bool pips : { false, true }) {
            config.alarmTimeSignal = pips;
            for (bool ntp : { false, true }) {
                config.alarmHour = 3;
                RequireAlarmAndSignal(config, spring, TestTime(2026, 3, 29, 3, 0, 0), true, ntp);
                config.alarmHour = 2;
                RequireAlarmAndSignal(config, spring, TestTime(2026, 3, 29, 3, 0, 0), false, ntp);
                RequireAlarmAndSignal(config, autumn, TestTime(2026, 10, 25, 2, 0, 0), true, ntp);
                RequireAlarmAndSignal(config, autumn, TestTime(2026, 10, 25, 2, 0, 0), false, ntp, 20261025, 120);
            }
        }
    }
    config.offsetMilliseconds = 125;
    config.alarmHour = 3;
    config.alarmTimeSignal = true;
    config.timeSignalEnabled = true;
    config.timeSignal = TIME_SIGNAL_EVERY_HOUR;
    ULONGLONG shared = SystemTimeValue(TestTime(2026, 3, 29, 1, 0, 0)) - 125 * 10000;
    RequireAlarmAndSignal(config, shared, TestTime(2026, 3, 29, 3, 0, 0), true, true);
    std::puts("PASS: real DST alarms and optional final pips coincide for system/NTP and shifted sub-ms clocks");
}

/// Checks every-refresh alarm detection within one UI uptime second and fractional alignment of hidden alarms.
static void TestAlarmRefreshTiming() {
    Require(hController == nullptr && hSettings == nullptr && widgets.empty(), "Refresh test has no native windows");
    bool previousWinsock = winsockReady;
    winsockReady = false;
    simulateUiClock = true;
    simulatedUiTick = 700000;
    std::unique_ptr<Widget> widget = std::make_unique<Widget>();
    widget->config.id = 1;
    widget->config.type = WIDGET_ANALOG;
    widget->config.visible = true;
    widget->config.timeZoneKey = L"Central Europe Standard Time";
    widget->config.offsetMilliseconds = 125;
    widget->config.alarmEnabled = true;
    widget->config.alarmHour = 3;
    widget->config.alarmMinute = 0;
    widgets.push_back(std::move(widget));
    ULONGLONG target = SystemTimeValue(TestTime(2026, 3, 29, 1, 0, 0)) - 125 * 10000;
    SetTestApplicationClock(target - 10000, false);
    WindowProc(nullptr, WM_TIMER, TIMER_REFRESH, 0);
    Require(!widgets[0]->alarmActive, "First refresh observes the minute before the shifted alarm");
    SetTestApplicationClock(target, false);
    WindowProc(nullptr, WM_TIMER, TIMER_REFRESH, 0);
    Require(widgets[0]->alarmActive, "A second refresh in the same uptime second detects the shifted alarm");
    widgets[0]->config.visible = false;
    ULONGLONG phase = SystemTimeValue(TestTime(2026, 3, 29, 1, 0, 0, 870));
    Require(WidgetRefreshDelay(phase) == USER_TIMER_MINIMUM, "Hidden alarms retain fractional second alignment");
    widgets[0]->config.alarmEnabled = false;
    Require(WidgetRefreshDelay(phase) == REFRESH_MAX_INTERVAL, "Hidden inactive clocks use the maintenance interval");
    widgets.clear();
    simulateUiClock = false;
    winsockReady = previousWinsock;
    std::puts("PASS: alarms react on every refresh, including hidden clocks with fractional offsets");
}

/// Verifies refresh invalidation after Windows time and setting notifications without any native widget windows.
static void TestTimeChangeNotifications() {
    Require(hController == nullptr && widgets.empty(), "Notification test starts without native windows");
    HWND previousSettings = hSettings;
    hSettings = reinterpret_cast<HWND>(1);
    std::unique_ptr<Widget> widget = std::make_unique<Widget>();
    widget->config.visible = true;
    widgets.push_back(std::move(widget));
    const UINT messages[] = { WM_TIMECHANGE, WM_SETTINGCHANGE };
    for (UINT message : messages) {
        widgets[0]->lastRenderKey = 123;
        widgets[0]->rendered = true;
        WindowProc(nullptr, message, 0, 0);
        Require(widgets[0]->lastRenderKey == -1 && !widgets[0]->rendered,
            "Windows time and setting notifications invalidate the displayed clock");
    }
    widgets.clear();
    hSettings = previousSettings;
    std::puts("PASS: Windows time/setting notifications invalidate clocks without creating native windows");
}

/// Tests NTP corrections across system-clock jumps, delayed delivery, failed synchronization, and system fallback.
/// Also verifies seasonal conversion, zone persistence and future signal targets without native audio or windows.
int main() {
    testAddress.ai_family = AF_INET;
    testAddress.ai_socktype = SOCK_DGRAM;
    testAddress.ai_protocol = IPPROTO_UDP;
    const LONGLONG jumps[] = { 0LL, 300000000LL, -300000000LL };
    for (LONGLONG jump : jumps) {
        systemJumpOnReceive = jump;
        RunQuery();
        Require(capturedResult->success, "System-clock change invalidated an NTP query");
        Require(std::llabs(capturedResult->clockOffset100Nanoseconds - TEST_CORRECTION) <= 2,
            "System-clock change contaminated the combined NTP time");
        Require(capturedResult->offset100Nanoseconds == static_cast<LONGLONG>(monotonicTime)
            + capturedResult->clockOffset100Nanoseconds - static_cast<LONGLONG>(systemTime),
            "NTP log offset no longer describes the Windows clock");
        ULONGLONG deliveredTime = monotonicTime + capturedResult->clockOffset100Nanoseconds;
        monotonicTime += 7 * 10000000ULL;
        systemTime += 90 * 10000000ULL;
        WindowProc(nullptr, WM_NTP_RESULT, 0, reinterpret_cast<LPARAM>(capturedResult));
        capturedResult = nullptr;
        Require(GetApplicationFileTimeValue() == deliveredTime + 7 * 10000000ULL,
            "Delayed NTP delivery or a system-clock change shifted application time");
        LONGLONG oldOffset = GetApplicationTimeOffset(monotonicTime);
        ULONGLONG target = 0;
        Require(CalculateTimeSignalTarget(GetApplicationFileTimeValue(), monotonicTime, TIME_SIGNAL_EVERY_MINUTE, &target),
            "Time signal target calculation failed");
        systemTime -= 180 * 10000000ULL;
        ULONGLONG repeatedTarget = 0;
        CalculateTimeSignalTarget(GetApplicationFileTimeValue(), monotonicTime, TIME_SIGNAL_EVERY_MINUTE, &repeatedTarget);
        Require(target == repeatedTarget && oldOffset == GetApplicationTimeOffset(monotonicTime),
            "System-clock change shifted a time signal target");
    }
    invalidReply = true;
    ULONGLONG beforeFailure = GetApplicationFileTimeValue();
    ULONGLONG beforeFailureTick = monotonicTime;
    RunQuery();
    Require(!capturedResult->success, "Invalid replies were accepted");
    WindowProc(nullptr, WM_NTP_RESULT, 0, reinterpret_cast<LPARAM>(capturedResult));
    capturedResult = nullptr;
    Require(ntpTimeValid && GetApplicationFileTimeValue() ==
        beforeFailure + monotonicTime - beforeFailureTick, "Failed synchronization discarded the running NTP clock");
    useNtpTime = false;
    Require(GetApplicationFileTimeValue() == systemTime, "System time source did not follow Windows time");
    useNtpTime = true;
    ntpTimeValid = false;
    Require(GetApplicationFileTimeValue() == systemTime, "Unsynchronized clock did not use system time");
    hTimeSignalStopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    Require(hTimeSignalStopEvent != nullptr, "Could not create the signal test event");
    timeSignalSequences.push_back(TimeSignalSequence{ monotonicTime + 6 * FILE_TIME_TICKS_PER_SECOND, false, true });
    std::vector<TimeSignalTone> beforeJump = PlanTimeSignalIntervals(MonotonicFileTimeValue());
    systemTime += 600 * FILE_TIME_TICKS_PER_SECOND;
    std::vector<TimeSignalTone> afterJump = PlanTimeSignalIntervals(MonotonicFileTimeValue());
    Require(!beforeJump.empty() && beforeJump.size() == afterJump.size(), "System jump changed planned pips");
    for (size_t index = 0; index < beforeJump.size(); index++) {
        Require(beforeJump[index].start ==
            afterJump[index].start && beforeJump[index].end == afterJump[index].end, "System jump shifted a planned pip");
    }
    timeSignalSequences.clear();
    CloseHandle(hTimeSignalStopEvent);
    hTimeSignalStopEvent = nullptr;
    std::puts("PASS: NTP clock jumps, delayed delivery, offsets, signal targets and pips, failed sync, system fallback");
    TestAlarmDisplayRecreation();
    LoadTimeZones();
    TestDaylightSavingOffsets();
    TestSystemTimeZoneChanges();
    TestTimeZonePersistence();
    TestDaylightSavingSignals();
    TestIntegratedDaylightSavingAlarms();
    TestAlarmRefreshTiming();
    TestTimeChangeNotifications();
    return 0;
}
