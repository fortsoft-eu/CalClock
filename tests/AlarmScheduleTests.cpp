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
#include "../CalClock/CalClock.h"
#include "../CalClock/AlarmSchedule.h"
#include "../CalClock/TimeZoneSupport.h"
#include "../CalClock/TimeSignal.h"
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cwchar>

struct ForwardScenario {
    const wchar_t* zone;
    ULONGLONG start;
    int hour;
    int minute;
};

struct CandidateScenario {
    ULONGLONG local;
    ULONGLONG first;
    ULONGLONG second;
    unsigned int count;
};

static constexpr ULONGLONG TEST_MINUTE_TICKS = 600000000;
static constexpr ULONGLONG TEST_DAY_TICKS = 864000000000;
static std::vector<DYNAMIC_TIME_ZONE_INFORMATION> zones;
static int failed = 0;

/// Fails immediately if a pure schedule test accidentally enters the real-time playback path.
ULONGLONG MonotonicFileTimeValue() {
    std::abort();
}

/// Fails immediately instead of allowing a schedule test to resolve or open an audio endpoint.
bool ResolveAudioOutputDevice(const std::wstring& requested, std::wstring* resolved, UINT* device) {
    UNREFERENCED_PARAMETER(requested);
    UNREFERENCED_PARAMETER(resolved);
    UNREFERENCED_PARAMETER(device);
    std::abort();
}

/// Constructs a simulated UTC FILETIME value and aborts if a test supplied an invalid calendar date.
static ULONGLONG UtcTime(int year, int month, int day, int hour, int minute, int second = 0,
    int milliseconds = 0) {
    SYSTEMTIME time{};
    time.wYear = static_cast<WORD>(year);
    time.wMonth = static_cast<WORD>(month);
    time.wDay = static_cast<WORD>(day);
    time.wHour = static_cast<WORD>(hour);
    time.wMinute = static_cast<WORD>(minute);
    time.wSecond = static_cast<WORD>(second);
    time.wMilliseconds = static_cast<WORD>(milliseconds);
    FILETIME file{};
    if (!SystemTimeToFileTime(&time, &file)) {
        std::abort();
    }
    ULARGE_INTEGER value{};
    value.LowPart = file.dwLowDateTime;
    value.HighPart = file.dwHighDateTime;
    return value.QuadPart;
}

/// Reports a failed expectation without hiding subsequent independent scenario failures.
static void Check(bool condition, const char* name) {
    if (!condition) {
        std::fprintf(stderr, "FAILED: %s\n", name);
        ++failed;
    }
}

/// Returns an enabled UTC digital-clock alarm while retaining the production defaults for other settings.
static WidgetConfig AlarmConfig(int hour = 8, int minute = 0) {
    WidgetConfig config;
    config.type = WIDGET_DIGITAL;
    config.alarmEnabled = true;
    config.showUtc = true;
    config.alarmHour = hour;
    config.alarmMinute = minute;
    return config;
}

/// Retrieves a required installed Windows zone, failing explicitly instead of substituting the system zone.
static const DYNAMIC_TIME_ZONE_INFORMATION& TestZone(const std::wstring& key) {
    for (const DYNAMIC_TIME_ZONE_INFORMATION& zone : zones) {
        if (_wcsicmp(zone.TimeZoneKeyName, key.c_str()) == 0) {
            return zone;
        }
    }
    std::fwprintf(stderr, L"Required Windows time zone is unavailable: %ls\n", key.c_str());
    std::exit(1);
}

/// Converts a simulated application instant by the production forward path, independently of alarm inversion.
static SYSTEMTIME DisplayedAt(const WidgetConfig& config, ULONGLONG instant) {
    ULARGE_INTEGER shifted{};
    shifted.QuadPart = static_cast<ULONGLONG>(static_cast<LONGLONG>(instant)
        + config.offsetMilliseconds * 10000);
    FILETIME file{ shifted.LowPart, shifted.HighPart };
    SYSTEMTIME utc{};
    SYSTEMTIME displayed{};
    if (!FileTimeToSystemTime(&file, &utc)) {
        std::abort();
    }
    if (config.showUtc) {
        return utc;
    }
    if (!ConvertUtcToTimeZone(TestZone(config.timeZoneKey), utc, &displayed)) {
        std::abort();
    }
    return displayed;
}

/// Computes the production next-minute signal target on a distinct simulated continuous-clock timeline.
static ULONGLONG UpcomingPipTarget(const WidgetConfig& config, ULONGLONG applicationNow) {
    SYSTEMTIME displayed = DisplayedAt(config, applicationNow);
    ULONGLONG displayedValue = UtcTime(displayed.wYear, displayed.wMonth, displayed.wDay,
        displayed.wHour, displayed.wMinute, displayed.wSecond, displayed.wMilliseconds);
    displayedValue += applicationNow % 10000;
    ULONGLONG timelineNow = applicationNow - 123456789;
    ULONGLONG target = 0;
    Check(CalculateTimeSignalTarget(displayedValue, timelineNow, TIME_SIGNAL_EVERY_MINUTE, &target),
        "pre-pip target calculation succeeds");
    return applicationNow + target - timelineNow;
}

/// Searches real UTC minutes forward without using the inverse converter or the scheduler's calendar search.
static ULONGLONG NextByForwardScan(const WidgetConfig& config, ULONGLONG after, int consumedDate = -1) {
    LONGLONG offset = config.offsetMilliseconds * 10000;
    ULONGLONG shifted = static_cast<ULONGLONG>(static_cast<LONGLONG>(after) + offset);
    ULONGLONG first = shifted / TEST_MINUTE_TICKS * TEST_MINUTE_TICKS + TEST_MINUTE_TICKS;
    for (ULONGLONG grid = first; grid <= first + 8 * TEST_DAY_TICKS; grid += TEST_MINUTE_TICKS) {
        ULONGLONG instant = static_cast<ULONGLONG>(static_cast<LONGLONG>(grid) - offset);
        SYSTEMTIME displayed = DisplayedAt(config, instant);
        int date = displayed.wYear * 10000 + displayed.wMonth * 100 + displayed.wDay;
        int weekday = (displayed.wDayOfWeek + 6) % 7;
        if (date > consumedDate
                && (config.alarmDays & 1U << weekday) != 0
                && displayed.wHour == config.alarmHour
                && displayed.wMinute == config.alarmMinute
                && displayed.wSecond == 0
                && displayed.wMilliseconds == 0) {
            return instant;
        }
    }
    return 0;
}

/// Covers exact timing, delayed processing, long sleep, startup, weekday masks, and disabled calendar alarms.
static void TestUtc() {
    WidgetConfig config = AlarmConfig();
    AlarmSchedule schedule;
    schedule.Reset(config, zones, UtcTime(2026, 11, 2, 7, 55));
    Check(schedule.Next() == UtcTime(2026, 11, 2, 8, 0), "UTC next");
    Check(!schedule.Check(config, zones, UtcTime(2026, 11, 2, 7, 59, 59, 999)), "before exact instant");
    Check(schedule.Check(config, zones, UtcTime(2026, 11, 2, 8, 0)), "exact instant");
    Check(!schedule.Check(config, zones, UtcTime(2026, 11, 2, 8, 0, 1)), "single firing");
    Check(schedule.LastDate() == 20261102 && schedule.LastMinute() == 480, "consumed identity");
    Check(schedule.Next() == UtcTime(2026, 11, 3, 8, 0), "next day");
    Check(schedule.Check(config, zones, UtcTime(2026, 11, 3, 10, 0)), "late after sleep");
    Check(!schedule.Check(config, zones, UtcTime(2026, 11, 3, 10, 0)), "resume duplicate");
    Check(schedule.Check(config, zones, UtcTime(2026, 12, 5, 7, 0)), "long sleep once");
    Check(schedule.LastDate() == 20261204, "most recent missed date");
    Check(schedule.Next() == UtcTime(2026, 12, 5, 8, 0), "next after long sleep");
    Check(!schedule.Check(config, zones, UtcTime(2026, 11, 2, 7, 0)), "backward reset");
    Check(schedule.Next() == UtcTime(2026, 12, 5, 8, 0), "backward retains high water");
    Check(!schedule.Check(config, zones, UtcTime(2026, 12, 4, 9, 0)), "return cannot duplicate");
    Check(schedule.Check(config, zones, UtcTime(2026, 12, 5, 8, 0)), "new occurrence after return");
    AlarmSchedule fresh;
    fresh.Reset(config, zones, UtcTime(2026, 11, 2, 8, 0, 20));
    Check(fresh.Next() == UtcTime(2026, 11, 3, 8, 0), "startup during alarm minute");
    Check(!fresh.Check(config, zones, UtcTime(2026, 11, 2, 8, 0, 21)), "no startup replay");
    config.alarmEnabled = false;
    Check(!fresh.Check(config, zones, UtcTime(2026, 11, 2, 8, 1)) && fresh.Next() == 0, "disable cancels");
    config.alarmEnabled = true;
    config.alarmHour = 9;
    Check(!fresh.Check(config, zones, UtcTime(2026, 11, 2, 8, 1)), "enable resets schedule");
    Check(fresh.Next() == UtcTime(2026, 11, 2, 9, 0), "changed hour");
    config.alarmDays = 1;
    fresh.Reset(config, zones, UtcTime(2026, 11, 3, 8, 1));
    Check(fresh.Next() == UtcTime(2026, 11, 9, 9, 0), "Monday weekday");
    Check(fresh.Check(config, zones, UtcTime(2027, 1, 6, 10, 0)), "long weekday pause");
    Check(fresh.LastDate() == 20270104, "latest enabled weekday");
    config.alarmDays = 0;
    fresh.Reset(config, zones, UtcTime(2026, 11, 3, 8, 1));
    Check(fresh.Next() == 0, "no weekdays");
    config.alarmDays = ALARM_DAYS_ALL;
    config.type = WIDGET_CALENDAR;
    fresh.Reset(config, zones, UtcTime(2026, 11, 3, 8, 1));
    Check(fresh.Next() == 0, "silent calendar");
}

/// Checks European DST gaps and repeated times, including offsets applied before the zone conversion.
static void TestEurope() {
    WidgetConfig config = AlarmConfig(2, 30);
    config.showUtc = false;
    config.timeZoneKey = L"Central Europe Standard Time";
    AlarmSchedule spring;
    spring.Reset(config, zones, UtcTime(2026, 3, 29, 0, 0));
    Check(spring.Next() == UtcTime(2026, 3, 30, 0, 30), "spring nonexistent minute skipped");
    Check(!spring.Check(config, zones, UtcTime(2026, 3, 29, 5, 0)), "spring gap is not missed alarm");
    Check(spring.Check(config, zones, UtcTime(2026, 3, 30, 1, 0)), "next real spring alarm caught");
    AlarmSchedule fall;
    fall.Reset(config, zones, UtcTime(2026, 10, 24, 23, 0));
    Check(fall.Next() == UtcTime(2026, 10, 25, 0, 30), "first fall occurrence");
    Check(fall.Check(config, zones, UtcTime(2026, 10, 25, 0, 30)), "first fall alarm");
    Check(fall.Next() == UtcTime(2026, 10, 26, 1, 30), "second fall occurrence suppressed");
    Check(!fall.Check(config, zones, UtcTime(2026, 10, 25, 1, 30)), "no duplicate fall alarm");
    AlarmSchedule slept;
    slept.Reset(config, zones, UtcTime(2026, 10, 24, 23, 0));
    Check(slept.Check(config, zones, UtcTime(2026, 10, 25, 2, 0)), "slept through both folds once");
    Check(slept.LastDate() == 20261025 && slept.Next() == UtcTime(2026, 10, 26, 1, 30),
        "fold catchup identity");
    AlarmSchedule restart;
    restart.Reset(config, zones, UtcTime(2026, 10, 25, 0, 30, 20));
    Check(restart.Next() == UtcTime(2026, 10, 25, 1, 30), "startup in first fold allows future second entry");
    config.alarmHour = 3;
    config.alarmMinute = 0;
    config.offsetMilliseconds = 2500;
    AlarmSchedule advanced;
    advanced.Reset(config, zones, UtcTime(2026, 3, 29, 0, 58));
    Check(advanced.Next() == UtcTime(2026, 3, 29, 0, 59, 57, 500),
        "positive fractional offset shifts transition");
    Check(advanced.Check(config, zones, UtcTime(2026, 3, 29, 1, 10)), "positive offset catchup");
    config.offsetMilliseconds = -2500;
    AlarmSchedule delayed;
    delayed.Reset(config, zones, UtcTime(2026, 3, 29, 0, 58));
    Check(delayed.Next() == UtcTime(2026, 3, 29, 1, 0, 2, 500),
        "negative fractional offset shifts transition");
}

/// Checks a fixed quarter-hour zone and Lord Howe's thirty-minute seasonal transitions.
static void TestOtherZones() {
    WidgetConfig config = AlarmConfig(8, 0);
    config.showUtc = false;
    config.timeZoneKey = L"UTC+05:45";
    AlarmSchedule fixed;
    fixed.Reset(config, zones, UtcTime(2026, 11, 2, 0, 0));
    Check(fixed.Next() == UtcTime(2026, 11, 2, 2, 15), "quarter hour fixed offset");
    config.timeZoneKey = L"Lord Howe Standard Time";
    config.alarmHour = 2;
    config.alarmMinute = 15;
    AlarmSchedule half;
    half.Reset(config, zones, UtcTime(2026, 10, 3, 12, 0));
    Check(half.Next() == UtcTime(2026, 10, 4, 15, 15), "half hour spring gap");
    Check(!half.Check(config, zones, UtcTime(2026, 10, 3, 17, 0)), "half hour nonexistent alarm not caught");
    config.alarmHour = 1;
    config.alarmMinute = 45;
    AlarmSchedule halfFall;
    halfFall.Reset(config, zones, UtcTime(2026, 4, 4, 12, 0));
    Check(halfFall.Next() == UtcTime(2026, 4, 4, 14, 45), "half hour first repeated occurrence");
    Check(halfFall.Check(config, zones, UtcTime(2026, 4, 4, 16, 0)), "half hour repeated catchup");
    Check(halfFall.Next() == UtcTime(2026, 4, 5, 15, 15), "half hour duplicate skipped");
}

/// Preserves observed and consumed alarms when widgets are copied, disabled, reenabled, or edited.
static void TestDisabledAndCopiedSchedule() {
    WidgetConfig config = AlarmConfig();
    AlarmSchedule original;
    original.Reset(config, zones, UtcTime(2026, 11, 2, 7, 55));
    AlarmSchedule copied = original;
    Check(copied.Next() == original.Next(), "copy preserves pending alarm");
    Check(copied.Check(config, zones, UtcTime(2026, 11, 2, 8, 0)), "copied pending alarm fires");
    Check(original.LastDate() == -1, "copies retain independent consumed state");
    config.alarmEnabled = false;
    Check(!copied.Check(config, zones, UtcTime(2026, 11, 2, 8, 1)), "disabled alarm stays silent");
    Check(copied.Next() == 0 && copied.LastDate() == 20261102, "disable retains consumed occurrence");
    config.alarmEnabled = true;
    Check(!copied.Check(config, zones, UtcTime(2026, 11, 2, 8, 2)), "reenabling does not replay alarm");
    Check(copied.Next() == UtcTime(2026, 11, 3, 8, 0), "reenabling schedules next occurrence");
    Check(original.Check(config, zones, UtcTime(2026, 11, 3, 7, 0)),
        "original still catches its missed alarm");
    AlarmSchedule assigned;
    assigned = copied;
    assigned.Reset(config, zones, UtcTime(2026, 11, 2, 7, 0));
    Check(assigned.LastDate() == 20261102, "assignment and reset retain consumed identity");
    Check(assigned.Next() == UtcTime(2026, 11, 3, 8, 0), "reset cannot replay consumed date");
    config.alarmHour = 9;
    Check(!assigned.Check(config, zones, UtcTime(2026, 11, 2, 8, 30)),
        "editing alarm establishes new interval");
    Check(assigned.Check(config, zones, UtcTime(2026, 11, 2, 9, 0)),
        "edited future minute can fire same day");
    AlarmSchedule disabled;
    config.alarmEnabled = false;
    disabled.Reset(config, zones, UtcTime(2026, 11, 2, 8, 30));
    Check(!disabled.Check(config, zones, UtcTime(2026, 11, 3, 10, 0)), "sleep while disabled is silent");
    config.alarmEnabled = true;
    Check(!disabled.Check(config, zones, UtcTime(2026, 11, 3, 10, 0)),
        "enable ignores interval while disabled");
    Check(disabled.Next() == UtcTime(2026, 11, 4, 9, 0), "enable after missed minute schedules tomorrow");
}

/// Keeps a consumed local alarm suppressed across repeated resets during the repeated daylight-saving hour.
static void TestRepeatedLocalReset() {
    WidgetConfig config = AlarmConfig(2, 30);
    config.showUtc = false;
    config.timeZoneKey = L"Central Europe Standard Time";
    AlarmSchedule schedule;
    schedule.Reset(config, zones, UtcTime(2026, 10, 24, 23, 0));
    Check(schedule.Check(config, zones, UtcTime(2026, 10, 25, 0, 30)),
        "consume first local fold before reset");
    const ULONGLONG instants[] = {
        UtcTime(2026, 10, 25, 0, 40), UtcTime(2026, 10, 25, 1, 0),
        UtcTime(2026, 10, 25, 1, 30), UtcTime(2026, 10, 25, 1, 59)
    };
    for (ULONGLONG instant : instants) {
        schedule.Reset(config, zones, instant);
        Check(schedule.LastDate() == 20261025, "local reset retains consumed date");
        Check(schedule.Next() == UtcTime(2026, 10, 26, 1, 30), "local reset skips repeated alarm minute");
        Check(!schedule.Check(config, zones, instant), "local reset does not refire during repeated hour");
    }
    AlarmSchedule copied = schedule;
    copied.Reset(config, zones, UtcTime(2026, 10, 25, 0, 0));
    Check(copied.Next() == UtcTime(2026, 10, 26, 1, 30), "copied fold history survives backward reset");
    Check(copied.Check(config, zones, UtcTime(2026, 10, 26, 1, 30)), "next real local day still fires");
}

/// Rejects offsets outside the FILETIME range and checks valid large offsets without touching the system
/// clock.
static void TestOffsetRange() {
    WidgetConfig config = AlarmConfig();
    ULONGLONG now = UtcTime(2026, 11, 2, 7, 0);
    const LONGLONG invalidOffsets[] = {
        LLONG_MIN, LLONG_MAX, LLONG_MIN / 10000, LLONG_MAX / 10000,
        -static_cast<LONGLONG>(now / 10000) - 1
    };
    for (LONGLONG offset : invalidOffsets) {
        config.offsetMilliseconds = offset;
        AlarmSchedule schedule;
        schedule.Reset(config, zones, now);
        Check(schedule.Next() == 0, "out-of-range offset produces no schedule");
        Check(!schedule.Check(config, zones, now + 1), "out-of-range offset cannot fire");
    }
    const LONGLONG largeOffsets[] = { -100000LL * 86400000, 100000LL * 86400000 };
    for (LONGLONG offset : largeOffsets) {
        config.offsetMilliseconds = offset;
        AlarmSchedule schedule;
        schedule.Reset(config, zones, now);
        Check(schedule.Next() == UtcTime(2026, 11, 2, 8, 0),
            "large whole-day offset preserves daily UTC minute");
        Check(schedule.Check(config, zones, UtcTime(2026, 11, 2, 8, 0)), "large supported offset fires once");
        Check(!schedule.Check(config, zones, UtcTime(2026, 11, 2, 8, 0)), "large offset does not duplicate");
    }
    config.offsetMilliseconds = 0;
    AlarmSchedule minimum;
    minimum.Reset(config, zones, 0);
    Check(minimum.Next() == UtcTime(1601, 1, 1, 8, 0), "minimum FILETIME schedules valid future alarm");
    AlarmSchedule maximum;
    maximum.Reset(config, zones, ULLONG_MAX);
    Check(maximum.Next() == 0, "unsigned FILETIME overflow cannot schedule");
    Check(!maximum.Check(config, zones, ULLONG_MAX), "unsigned FILETIME overflow cannot fire");
}

/// Covers every weekday combination and each sound-capable widget without relying on the current real date.
static void TestWidgetTypesAndWeekdays() {
    const WidgetType types[] = { WIDGET_PANEL, WIDGET_ANALOG, WIDGET_DIGITAL, WIDGET_CALENDAR,
        WIDGET_FULLSCREEN };
    ULONGLONG monday = UtcTime(2026, 11, 2, 8, 0);
    for (WidgetType type : types) {
        for (unsigned int mask = 0; mask <= ALARM_DAYS_ALL; ++mask) {
            WidgetConfig config = AlarmConfig();
            config.type = type;
            config.alarmDays = mask;
            AlarmSchedule schedule;
            schedule.Reset(config, zones, monday - 1);
            ULONGLONG expected = 0;
            if (type != WIDGET_CALENDAR) {
                for (unsigned int day = 0; day < 7; ++day) {
                    if ((mask & 1U << day) != 0) {
                        expected = monday + day * TEST_DAY_TICKS;
                        break;
                    }
                }
            }
            Check(schedule.Next() == expected, "widget type and weekday mask next occurrence");
            if (expected != 0) {
                Check(schedule.Check(config, zones, expected),
                    "weekday occurrence fires for supported widget");
                Check(!schedule.Check(config, zones, expected), "weekday occurrence is consumed once");
            } else {
                Check(!schedule.Check(config, zones, monday + 30 * TEST_DAY_TICKS),
                    "disabled schedule stays silent");
            }
        }
    }
    WidgetConfig config = AlarmConfig(0, 0);
    config.alarmDays = 1;
    config.offsetMilliseconds = 3600000;
    AlarmSchedule shifted;
    shifted.Reset(config, zones, UtcTime(2026, 11, 1, 22, 59));
    Check(shifted.Next() == UtcTime(2026, 11, 1, 23, 0), "weekday belongs to offset displayed date");
    Check(shifted.Check(config, zones, UtcTime(2026, 11, 2, 12, 0)), "offset midnight catches Monday alarm");
    Check(shifted.LastDate() == 20261102, "offset midnight stores displayed date");
}

/// Keeps pending alarms across non-scheduling edits and replans actual schedule changes without replay.
static void TestConfigurationChanges() {
    WidgetConfig config = AlarmConfig();
    AlarmSchedule schedule;
    schedule.Reset(config, zones, UtcTime(2026, 11, 2, 7, 59));
    config.name = L"Changed name";
    config.alarmWakeComputer = true;
    config.alarmTimeSignal = true;
    config.runCommand = true;
    config.command = L"not-executed.wav";
    config.callRemoteScript = true;
    config.remoteScriptUrl = L"https://example.invalid/not-requested";
    config.alarmVolume = -1800;
    config.visible = false;
    config.type = WIDGET_ANALOG;
    Check(schedule.Check(config, zones, UtcTime(2026, 11, 2, 8, 1)),
        "actions and appearance retain pending alarm");
    config.type = WIDGET_CALENDAR;
    Check(!schedule.Check(config, zones, UtcTime(2026, 11, 2, 8, 2)),
        "calendar conversion disables pending alarm");
    Check(schedule.Next() == 0, "calendar conversion has no future occurrence");
    config.type = WIDGET_PANEL;
    Check(!schedule.Check(config, zones, UtcTime(2026, 11, 2, 8, 3)),
        "restoring sound widget does not replay");
    Check(schedule.Next() == UtcTime(2026, 11, 3, 8, 0), "restoring sound widget retains consumed day");
    config.alarmHour = 9;
    Check(!schedule.Check(config, zones, UtcTime(2026, 11, 2, 8, 30)),
        "new alarm time starts new observation");
    Check(schedule.Next() == UtcTime(2026, 11, 2, 9, 0), "new alarm time keeps future same-day occurrence");
    config.showUtc = false;
    config.timeZoneKey = L"UTC+05:45";
    Check(!schedule.Check(config, zones, UtcTime(2026, 11, 2, 8, 31)),
        "zone change does not catch old wall time");
    Check(schedule.Next() == UtcTime(2026, 11, 3, 3, 15), "zone change replans named zone");
    config.offsetMilliseconds = -86400000;
    Check(!schedule.Check(config, zones, UtcTime(2026, 11, 2, 8, 32)), "offset change does not replay");
    Check(schedule.Next() == UtcTime(2026, 11, 3, 3, 15),
        "whole-day offset adjusts displayed occurrence date");
    config.alarmDays = 1U << 2;
    Check(!schedule.Check(config, zones, UtcTime(2026, 11, 2, 8, 33)), "weekday edit replans without replay");
    Check(schedule.Next() == UtcTime(2026, 11, 5, 3, 15), "weekday edit uses offset local day");
}

/// Cross-checks inverse scheduling against independent forward conversions across DST and year boundaries.
static void TestForwardAgreement() {
    const ForwardScenario scenarios[] = {
        { L"Central Europe Standard Time", UtcTime(2026, 3, 29, 0, 0), 2, 30 },
        { L"Central Europe Standard Time", UtcTime(2026, 3, 29, 0, 0), 3, 0 },
        { L"Central Europe Standard Time", UtcTime(2026, 10, 25, 0, 0), 2, 30 },
        { L"Central Europe Standard Time", UtcTime(2026, 10, 25, 0, 45), 2, 30 },
        { L"Lord Howe Standard Time", UtcTime(2026, 10, 3, 14, 0), 2, 15 },
        { L"Lord Howe Standard Time", UtcTime(2026, 10, 3, 14, 0), 2, 30 },
        { L"Lord Howe Standard Time", UtcTime(2026, 4, 4, 14, 0), 1, 45 },
        { L"UTC+05:45", UtcTime(2026, 12, 31, 17, 0), 0, 0 },
        { L"UTC-03:30", UtcTime(2026, 12, 31, 23, 0), 0, 0 },
        { L"Central Europe Standard Time", UtcTime(2028, 2, 28, 22, 0), 0, 0 }
    };
    const LONGLONG offsets[] = { -2500, 0, 1, 2500, 3600000 };
    for (const ForwardScenario& scenario : scenarios) {
        for (LONGLONG offset : offsets) {
            WidgetConfig config = AlarmConfig(scenario.hour, scenario.minute);
            config.showUtc = false;
            config.timeZoneKey = scenario.zone;
            config.offsetMilliseconds = offset;
            AlarmSchedule schedule;
            schedule.Reset(config, zones, scenario.start);
            ULONGLONG expected = NextByForwardScan(config, scenario.start);
            Check(expected != 0 && schedule.Next() == expected,
                "inverse next equals independent forward scan");
            if (expected == 0) {
                continue;
            }
            Check(!schedule.Check(config, zones, expected - 1),
                "fractional instant is not early by one tick");
            Check(schedule.Check(config, zones, expected), "fractional instant fires exactly on time");
            Check(!schedule.Check(config, zones, expected + 1),
                "fractional instant cannot duplicate by one tick");
            ULONGLONG following = NextByForwardScan(config, expected, schedule.LastDate());
            Check(schedule.Next() == following,
                "following occurrence agrees after duplicate local time suppression");
        }
    }
}

/// Uses the production signal-boundary function to verify pre-pips end at the scheduled real alarm instant.
static void TestPrePipAgreement() {
    const ForwardScenario scenarios[] = {
        { L"Central Europe Standard Time", UtcTime(2026, 3, 29, 0, 55), 3, 0 },
        { L"Central Europe Standard Time", UtcTime(2026, 10, 25, 0, 0), 2, 30 },
        { L"Lord Howe Standard Time", UtcTime(2026, 10, 3, 14, 55), 2, 30 },
        { L"UTC+05:45", UtcTime(2026, 11, 2, 2, 0), 8, 0 }
    };
    const LONGLONG offsets[] = { -2500, 0, 1, 2500 };
    for (const ForwardScenario& scenario : scenarios) {
        for (LONGLONG offset : offsets) {
            WidgetConfig config = AlarmConfig(scenario.hour, scenario.minute);
            config.showUtc = false;
            config.timeZoneKey = scenario.zone;
            config.offsetMilliseconds = offset;
            AlarmSchedule schedule;
            schedule.Reset(config, zones, scenario.start);
            ULONGLONG due = schedule.Next();
            for (ULONGLONG lead : { 50000000ULL, 41234567ULL, 10000ULL, 1ULL }) {
                ULONGLONG applicationNow = due - lead;
                Check(UpcomingPipTarget(config, applicationNow) == due,
                    "pre-pip target equals actual scheduled alarm");
            }
        }
    }
}

/// Suppresses alarm pips for nonexistent or consumed repeated times and catches only eligible missed dates.
static void TestSkippedAndRepeatedSignals() {
    WidgetConfig config = AlarmConfig(2, 30);
    config.showUtc = false;
    config.timeZoneKey = L"Central Europe Standard Time";
    AlarmSchedule spring;
    spring.Reset(config, zones, UtcTime(2026, 3, 29, 0, 50));
    ULONGLONG springTarget = UpcomingPipTarget(config, UtcTime(2026, 3, 29, 0, 59, 55));
    Check(springTarget == UtcTime(2026, 3, 29, 1, 0), "spring pip target reaches actual transition");
    Check(springTarget != spring.Next(), "spring gap cannot schedule nonexistent alarm pips");
    AlarmSchedule fall;
    fall.Reset(config, zones, UtcTime(2026, 10, 25, 0, 0));
    Check(fall.Check(config, zones, UtcTime(2026, 10, 25, 0, 30)), "consume first fold before pip check");
    ULONGLONG repeatedTarget = UpcomingPipTarget(config, UtcTime(2026, 10, 25, 1, 29, 55));
    Check(repeatedTarget == UtcTime(2026, 10, 25, 1, 30), "second fold target is real future minute");
    Check(repeatedTarget != fall.Next(), "second fold cannot schedule duplicate alarm pips");
    Check(!fall.Check(config, zones, repeatedTarget), "second fold also cannot activate alarm actions");
    config.alarmDays = 1U << 6;
    AlarmSchedule skippedSunday;
    skippedSunday.Reset(config, zones, UtcTime(2026, 3, 28, 0, 0));
    Check(skippedSunday.Next() == UtcTime(2026, 4, 5, 0, 30),
        "Sunday spring gap skips to next enabled Sunday");
    Check(!skippedSunday.Check(config, zones, UtcTime(2026, 4, 4, 12, 0)),
        "long sleep does not invent skipped Sunday");
    Check(skippedSunday.Check(config, zones, UtcTime(2026, 4, 8, 12, 0)),
        "long sleep catches latest real Sunday");
    Check(skippedSunday.LastDate() == 20260405, "catchup retains actual enabled date");
}

/// Checks exact DST boundaries, chronological candidate order, and subminute precision independently.
static void TestInverseCandidates() {
    const CandidateScenario scenarios[] = {
        {
            UtcTime(2026, 3, 29, 1, 59, 59, 999),
            UtcTime(2026, 3, 29, 0, 59, 59, 999),
            0,
            1
        }, {
            UtcTime(2026, 3, 29, 2, 0),
            0,
            0,
            0
        }, {
            UtcTime(2026, 3, 29, 2, 59, 59, 999),
            0,
            0,
            0
        }, {
            UtcTime(2026, 3, 29, 3, 0),
            UtcTime(2026, 3, 29, 1, 0),
            0,
            1
        }, {
            UtcTime(2026, 10, 25, 1, 59, 59, 999),
            UtcTime(2026, 10, 24, 23, 59, 59, 999),
            0,
            1
        }, {
            UtcTime(2026, 10, 25, 2, 0),
            UtcTime(2026, 10, 25, 0, 0),
            UtcTime(2026, 10, 25, 1, 0),
            2
        }, {
            UtcTime(2026, 10, 25, 2, 59, 59, 999),
            UtcTime(2026, 10, 25, 0, 59, 59, 999),
            UtcTime(2026, 10, 25, 1, 59, 59, 999),
            2
        }, {
            UtcTime(2026, 10, 25, 3, 0),
            UtcTime(2026, 10, 25, 2, 0),
            0,
            1
        }
    };
    const DYNAMIC_TIME_ZONE_INFORMATION& zone = TestZone(L"Central Europe Standard Time");
    for (const CandidateScenario& scenario : scenarios) {
        ULARGE_INTEGER ticks{};
        ticks.QuadPart = scenario.local;
        FILETIME file{ ticks.LowPart, ticks.HighPart };
        SYSTEMTIME local{};
        Check(FileTimeToSystemTime(&file, &local) != FALSE, "candidate scenario is a valid calendar time");
        ULONGLONG candidates[2]{ ULLONG_MAX, ULLONG_MAX };
        unsigned int count = UINT_MAX;
        Check(GetTimeZoneUtcCandidates(zone, local, candidates, count), "valid inverse request succeeds");
        Check(count == scenario.count, "inverse distinguishes gap, unique time and repeated time");
        if (count != 0) {
            Check(candidates[0] == scenario.first, "first inverse candidate has exact UTC and milliseconds");
        }
        if (count == 2) {
            Check(candidates[1] == scenario.second, "second inverse candidate is later and equally precise");
        }
    }
    SYSTEMTIME invalid{};
    invalid.wYear = 2026;
    invalid.wMonth = 13;
    invalid.wDay = 1;
    ULONGLONG candidates[2]{};
    unsigned int count = 2;
    Check(!GetTimeZoneUtcCandidates(zone, invalid, candidates, count) && count == 0,
        "invalid local date fails and clears the candidate count");
}

/// Honors fixed seasonal rules separately from fully disabled daylight saving without system changes.
static void TestStaticZoneRules() {
    DYNAMIC_TIME_ZONE_INFORMATION zone = TestZone(L"Central Europe Standard Time");
    zone.DynamicDaylightTimeDisabled = TRUE;
    std::vector<DYNAMIC_TIME_ZONE_INFORMATION> fixedZones{ zone };
    WidgetConfig config = AlarmConfig(8, 0);
    config.showUtc = false;
    config.timeZoneKey = zone.TimeZoneKeyName;
    AlarmSchedule fixedRules;
    fixedRules.Reset(config, fixedZones, UtcTime(2026, 7, 1, 0, 0));
    Check(fixedRules.Next() == UtcTime(2026, 7, 1, 6, 0),
        "disabling dynamic rules still observes the supplied seasonal transition dates");
    zone.StandardDate = SYSTEMTIME{};
    zone.DaylightDate = SYSTEMTIME{};
    fixedZones[0] = zone;
    AlarmSchedule noDaylight;
    noDaylight.Reset(config, fixedZones, UtcTime(2026, 7, 1, 0, 0));
    Check(noDaylight.Next() == UtcTime(2026, 7, 1, 7, 0),
        "cleared transition dates disable daylight saving during summer");
    Check(noDaylight.Check(config, fixedZones, UtcTime(2026, 7, 1, 7, 0)),
        "alarm fires at standard-time offset with daylight saving disabled");
    AlarmSchedule noGap;
    config.alarmHour = 2;
    config.alarmMinute = 30;
    noGap.Reset(config, fixedZones, UtcTime(2026, 3, 29, 0, 0));
    Check(noGap.Next() == UtcTime(2026, 3, 29, 1, 30),
        "disabled daylight saving keeps the normally skipped spring wall time");
}

/// Rejects invalid alarm fields and ignores bits outside the seven supported weekdays.
static void TestInvalidScheduleFields() {
    const int invalidHours[] = { INT_MIN, -1, 24, INT_MAX };
    const int invalidMinutes[] = { INT_MIN, -1, 60, INT_MAX };
    ULONGLONG now = UtcTime(2026, 11, 2, 7, 0);
    for (int hour : invalidHours) {
        WidgetConfig config = AlarmConfig(hour, 0);
        AlarmSchedule schedule;
        schedule.Reset(config, zones, now);
        Check(schedule.Next() == 0, "invalid hour produces no pending alarm");
        Check(!schedule.Check(config, zones, now + TEST_DAY_TICKS), "invalid hour cannot fire later");
    }
    for (int minute : invalidMinutes) {
        WidgetConfig config = AlarmConfig(8, minute);
        AlarmSchedule schedule;
        schedule.Reset(config, zones, now);
        Check(schedule.Next() == 0, "invalid minute produces no pending alarm");
        Check(!schedule.Check(config, zones, now + TEST_DAY_TICKS), "invalid minute cannot fire later");
    }
    WidgetConfig config = AlarmConfig();
    config.alarmDays = ~ALARM_DAYS_ALL;
    AlarmSchedule schedule;
    schedule.Reset(config, zones, now);
    Check(schedule.Next() == 0, "unsupported weekday bits do not enable an alarm");
    config.alarmDays = UINT_MAX;
    Check(!schedule.Check(config, zones, now), "adding supported days begins a fresh observation");
    Check(schedule.Next() == UtcTime(2026, 11, 2, 8, 0), "supported days survive extraneous mask bits");
    config.alarmDays = ALARM_DAYS_ALL;
    Check(schedule.Check(config, zones, UtcTime(2026, 11, 2, 8, 1)),
        "changing ignored weekday bits does not discard a due alarm");
}

/// Catches an already elapsed first occurrence even when resumed inside the repeated hour before its twin.
static void TestResumeBetweenFoldOccurrences() {
    WidgetConfig config = AlarmConfig(2, 30);
    config.showUtc = false;
    config.timeZoneKey = L"Central Europe Standard Time";
    config.offsetMilliseconds = -2500;
    AlarmSchedule schedule;
    schedule.Reset(config, zones, UtcTime(2026, 10, 25, 0, 0));
    Check(schedule.Check(config, zones, UtcTime(2026, 10, 25, 1, 10)),
        "resume before second fold occurrence catches the elapsed first occurrence immediately");
    Check(schedule.LastDate() == 20261025 && schedule.LastMinute() == 150,
        "fold catchup consumes the intended local date and minute");
    Check(schedule.Next() == UtcTime(2026, 10, 26, 1, 30, 2, 500),
        "catching the first fold suppresses its later twin even with an offset");
    config.alarmMinute = 45;
    Check(!schedule.Check(config, zones, UtcTime(2026, 10, 25, 1, 11)),
        "editing inside the repeated hour does not replay the earlier new-time occurrence");
    Check(schedule.Next() == UtcTime(2026, 10, 25, 1, 45, 2, 500),
        "editing inside the fold retains the real future occurrence of the new minute");
    Check(schedule.Check(config, zones, UtcTime(2026, 10, 25, 1, 45, 2, 500)),
        "edited future occurrence in repeated hour fires");
}

/// Cross-checks changing yearly biases using the actual Windows forward converter and long pauses.
static void TestHistoricalRuleChanges() {
    const ForwardScenario scenarios[] = {
        { L"Samoa Standard Time", UtcTime(2011, 12, 30, 0, 0), 8, 0 },
        { L"Samoa Standard Time", UtcTime(2011, 12, 31, 12, 0), 8, 0 },
        { L"Bahia Standard Time", UtcTime(2010, 12, 31, 20, 0), 0, 15 },
        { L"Venezuela Standard Time", UtcTime(2015, 12, 31, 20, 0), 0, 15 },
        { L"Turks And Caicos Standard Time", UtcTime(2017, 12, 31, 20, 0), 0, 15 }
    };
    for (const ForwardScenario& scenario : scenarios) {
        WidgetConfig config = AlarmConfig(scenario.hour, scenario.minute);
        config.showUtc = false;
        config.timeZoneKey = scenario.zone;
        config.offsetMilliseconds = -2500;
        AlarmSchedule schedule;
        schedule.Reset(config, zones, scenario.start);
        ULONGLONG expected = NextByForwardScan(config, scenario.start);
        Check(expected != 0 && schedule.Next() == expected,
            "yearly bias change retains the earliest real future wall-clock occurrence");
        ULONGLONG resume = scenario.start + 6 * TEST_DAY_TICKS;
        ULONGLONG latest = 0;
        int latestDate = -1;
        while (expected != 0 && expected <= resume) {
            latest = expected;
            SYSTEMTIME displayed = DisplayedAt(config, expected);
            latestDate = displayed.wYear * 10000 + displayed.wMonth * 100 + displayed.wDay;
            expected = NextByForwardScan(config, expected, latestDate);
        }
        Check(latest != 0 && schedule.Check(config, zones, resume),
            "sleep across yearly rule changes catches an actual elapsed occurrence");
        Check(schedule.LastDate() == latestDate,
            "historical catchup selects the latest eligible displayed date");
        Check(schedule.Next() == expected, "next alarm after historical catchup matches forward search");
        Check(!schedule.Check(config, zones, resume), "historical catchup cannot run twice");
    }
}

/// Requires every inverse conversion to recover the original UTC even when a local year boundary is crossed.
static void CheckYearBoundary(const wchar_t* key, int year) {
    for (const DYNAMIC_TIME_ZONE_INFORMATION& zone : zones) {
        if (_wcsicmp(zone.TimeZoneKeyName, key) != 0) {
            continue;
        }
        SYSTEMTIME utc{};
        utc.wYear = static_cast<WORD>(year);
        utc.wMonth = 1;
        utc.wDay = 1;
        SYSTEMTIME local{};
        Check(ConvertUtcToTimeZone(zone, utc, &local), "year-boundary UTC conversion succeeds");
        ULONGLONG candidates[2]{};
        unsigned int count = 0;
        Check(GetTimeZoneUtcCandidates(zone, local, candidates, count),
            "year-boundary inverse conversion succeeds");
        ULONGLONG original = UtcTime(year, 1, 1, 0, 0);
        bool found = false;
        for (unsigned int index = 0; index < count; ++index) {
            if (candidates[index] == original) {
                found = true;
            }
        }
        Check(found, "year-boundary roundtrip retains original UTC instant");
        return;
    }
}

/// Requires the Windows zones used by the integration scenarios instead of silently testing the system zone.
static void RequireZone(const wchar_t* key) {
    for (const DYNAMIC_TIME_ZONE_INFORMATION& zone : zones) {
        if (_wcsicmp(zone.TimeZoneKeyName, key) == 0) {
            return;
        }
    }
    std::fwprintf(stderr, L"Required Windows time zone is unavailable: %ls\n", key);
    std::exit(1);
}

/// Exercises real Windows time-zone rules with simulated UTC instants and returns nonzero on a failure.
int main() {
    LoadTimeZoneList(&zones);
    RequireZone(L"Central Europe Standard Time");
    RequireZone(L"Lord Howe Standard Time");
    RequireZone(L"UTC+05:45");
    RequireZone(L"UTC-03:30");
    RequireZone(L"Samoa Standard Time");
    RequireZone(L"Bahia Standard Time");
    RequireZone(L"Venezuela Standard Time");
    RequireZone(L"Turks And Caicos Standard Time");
    TestUtc();
    TestEurope();
    TestOtherZones();
    TestDisabledAndCopiedSchedule();
    TestRepeatedLocalReset();
    TestOffsetRange();
    TestWidgetTypesAndWeekdays();
    TestConfigurationChanges();
    TestForwardAgreement();
    TestPrePipAgreement();
    TestSkippedAndRepeatedSignals();
    TestInverseCandidates();
    TestStaticZoneRules();
    TestInvalidScheduleFields();
    TestResumeBetweenFoldOccurrences();
    TestHistoricalRuleChanges();
    CheckYearBoundary(L"Bahia Standard Time", 2011);
    CheckYearBoundary(L"Venezuela Standard Time", 2016);
    CheckYearBoundary(L"Turks And Caicos Standard Time", 2018);
    if (failed != 0) {
        return 1;
    }
    std::puts("PASS: alarm types, weekdays, missed occurrences, configuration, DST, "
        "offsets and pre-pip targets");
    return 0;
}
