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
 * Last modified for version 1.7.1.3
 */

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "../CalClock/TimeCalculator.h"
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

using HighlightMinutes = std::chrono::duration<long long, std::ratio<60>>;

struct HighlightHour {
    long long utcMinute = 0;
    ULONGLONG hours = 0;
    DWORD rules = 0;
};

struct HighlightExpected {
    bool valid = false;
    ULONGLONG totals[TIME_CALCULATOR_TOTAL_COUNT] = {};
    DWORD dateRules = 0;
    std::vector<HighlightHour> hours;
};

struct HighlightZone {
    const wchar_t* key = nullptr;
    int offset = 0;
    bool named = false;
    DYNAMIC_TIME_ZONE_INFORMATION information = {};
};

static constexpr int HOURS = static_cast<int>(TimeCalculatorUnit::Hours);
static constexpr int DAYS = static_cast<int>(TimeCalculatorUnit::Days);
static constexpr int WEEKS = static_cast<int>(TimeCalculatorUnit::Weeks);
static constexpr int MONTHS = static_cast<int>(TimeCalculatorUnit::Months);
static constexpr int YEARS = static_cast<int>(TimeCalculatorUnit::Years);
static constexpr DWORD DIGIT_FLAGS[] = {
    0,
    CALCULATOR_HIGHLIGHT_ONES,
    CALCULATOR_HIGHLIGHT_TWOS,
    CALCULATOR_HIGHLIGHT_THREES,
    CALCULATOR_HIGHLIGHT_FOURS,
    CALCULATOR_HIGHLIGHT_FIVES,
    CALCULATOR_HIGHLIGHT_SIXES,
    CALCULATOR_HIGHLIGHT_SEVENS,
    CALCULATOR_HIGHLIGHT_EIGHTS,
    CALCULATOR_HIGHLIGHT_NINES
};

static int failures = 0;

/// Builds literal fixture fields without calling the calculator's normalization or conversion routines.
static SYSTEMTIME Date(WORD year, WORD month, WORD day, WORD hour = 0, WORD minute = 0) {
    SYSTEMTIME value = {};
    value.wYear = year;
    value.wMonth = month;
    value.wDay = day;
    value.wHour = hour;
    value.wMinute = minute;
    return value;
}

/// Uses the standard library's Gregorian calendar as an independent date-arithmetic reference.
static std::chrono::sys_days CivilDay(const SYSTEMTIME& value) {
    return std::chrono::sys_days(std::chrono::year(value.wYear) / value.wMonth / value.wDay);
}

/// Expresses a timestamp as whole minutes from the standard library's epoch, independently of FILETIME.
static long long Minute(const SYSTEMTIME& value) {
    return std::chrono::duration_cast<HighlightMinutes>(CivilDay(value).time_since_epoch()).count()
        + value.wHour * 60LL + value.wMinute;
}

/// Converts an independent minute count back to civil fields without using production code.
static SYSTEMTIME Fields(long long minute) {
    std::chrono::sys_time<HighlightMinutes> point{ HighlightMinutes(minute) };
    std::chrono::sys_days day = std::chrono::floor<std::chrono::days>(point);
    std::chrono::year_month_day date(day);
    long long remainder = std::chrono::duration_cast<HighlightMinutes>(point - day).count();
    return Date(static_cast<WORD>(static_cast<int>(date.year())),
        static_cast<WORD>(static_cast<unsigned>(date.month())),
        static_cast<WORD>(static_cast<unsigned>(date.day())),
        static_cast<WORD>(remainder / 60),
        static_cast<WORD>(remainder % 60));
}

/// Uses decimal spelling to recognize repeated digits rather than the production division loop.
static DWORD Repetition(ULONGLONG value) {
    std::string text = std::to_string(value);
    if (text.size() < 2 || text.find_first_not_of(text.front()) != std::string::npos) {
        return 0;
    }
    return DIGIT_FLAGS[text.front() - '0'];
}

/// Recognizes a decimal suffix independently of the calculator's remainder checks.
static bool EndsWith(ULONGLONG value, const char* suffix) {
    return std::to_string(value).ends_with(suffix);
}

/// Generates the applicable hourly rules from decimal patterns and explicitly enumerated small milestones.
static DWORD HourRules(ULONGLONG hours) {
    DWORD result = Repetition(hours);
    bool round = hours >= 1000 && EndsWith(hours, "000");
    for (ULONGLONG multiplier = 1; multiplier <= 9; multiplier++) {
        round = round || hours == multiplier * 10 || hours == multiplier * 100;
    }
    if (round) {
        result |= CALCULATOR_HIGHLIGHT_ROUND;
    }
    return result;
}

/// Constructs monthly anniversary dates, placing an absent day at the start of the next month.
static std::chrono::sys_days Anniversary(const SYSTEMTIME& first, int months) {
    std::chrono::year_month month = std::chrono::year(first.wYear) / first.wMonth;
    month += std::chrono::months(months);
    std::chrono::year_month_day anniversary = month / first.wDay;
    if (!anniversary.ok()) {
        anniversary = (month + std::chrono::months(1)) / std::chrono::day(1);
    }
    return std::chrono::sys_days(anniversary);
}

/// Uses fixed offsets arithmetically or calls Windows directly for the named-zone reference.
static bool LocalFields(const HighlightZone& zone, long long minute, SYSTEMTIME* local) {
    SYSTEMTIME utc = Fields(minute);
    if (utc.wYear < 1601 || utc.wYear > 9999) {
        return false;
    }
    if (!zone.named) {
        *local = Fields(minute + zone.offset);
        return local->wYear >= 1601 && local->wYear <= 9999;
    }
    return SystemTimeToTzSpecificLocalTimeEx(&zone.information, &utc, local) != FALSE;
}

/// Resolves fixture zones from the public catalog without using production local-time conversion logic.
static HighlightZone Zone(const wchar_t* key, int offset = 0, bool named = false) {
    HighlightZone result;
    result.key = key;
    result.offset = offset;
    result.named = named;
    std::vector<DYNAMIC_TIME_ZONE_INFORMATION> zones;
    LoadTimeZoneList(&zones);
    for (const DYNAMIC_TIME_ZONE_INFORMATION& zone : zones) {
        if (wcscmp(zone.TimeZoneKeyName, key) == 0) {
            result.information = zone;
            return result;
        }
    }
    std::fwprintf(stderr, L"Missing fixture zone: %ls\n", key);
    std::exit(EXIT_FAILURE);
}

/// Enumerates actual UTC minutes on a local date, retaining every hourly event and the first existing minute.
static HighlightExpected Expected(const SYSTEMTIME& start, const SYSTEMTIME& selected,
        const HighlightZone& zone) {
    HighlightExpected result;
    long long startMinute = Minute(start);
    SYSTEMTIME first = {};
    if (!LocalFields(zone, startMinute, &first) || CivilDay(selected) < CivilDay(first)) {
        return result;
    }
    if (CivilDay(selected) == CivilDay(first)) {
        result.valid = true;
        result.dateRules = CALCULATOR_HIGHLIGHT_START;
        return result;
    }
    long long midnight = Minute(Date(selected.wYear, selected.wMonth, selected.wDay));
    long long begin = midnight - 14 * 60;
    long long end = midnight + 38 * 60;
    if (!zone.named) {
        begin = midnight - zone.offset;
        end = begin + 1440;
    }
    for (long long minute = begin; minute < end; minute++) {
        SYSTEMTIME local = {};
        if (!LocalFields(zone, minute, &local) || CivilDay(local) != CivilDay(selected)) {
            continue;
        }
        if (!result.valid) {
            result.valid = true;
            result.totals[HOURS] = static_cast<ULONGLONG>(std::max(0LL, minute - startMinute)) / 60;
        }
        long long elapsed = minute - startMinute;
        if (elapsed >= 0 && elapsed % 60 == 0) {
            ULONGLONG hours = static_cast<ULONGLONG>(elapsed / 60);
            DWORD rules = HourRules(hours);
            if (rules != 0) {
                result.hours.push_back(HighlightHour{ minute, hours, rules });
            }
        }
    }
    if (!result.valid) {
        return result;
    }
    ULONGLONG days = static_cast<ULONGLONG>((CivilDay(selected) - CivilDay(first)).count());
    ULONGLONG weeks = days / 7;
    result.totals[DAYS] = days;
    result.totals[WEEKS] = weeks;
    int months = 0;
    while (Anniversary(first, months + 1) <= CivilDay(selected)) {
        months++;
    }
    result.totals[MONTHS] = months;
    result.totals[YEARS] = months / 12;
    if (months > 0 && Anniversary(first, months) == CivilDay(selected)) {
        result.dateRules |= CALCULATOR_HIGHLIGHT_ANNIVERSARIES;
    }
    result.dateRules |= Repetition(days);
    if (days >= 100 && EndsWith(days, "00") || days >= 10 && days < 100 && EndsWith(days, "0")) {
        result.dateRules |= CALCULATOR_HIGHLIGHT_ROUND;
    }
    if (days == weeks * 7) {
        if (weeks >= 1 && weeks <= 9) {
            result.dateRules |= CALCULATOR_HIGHLIGHT_FIRST_WEEKS;
        }
        if (weeks >= 10 && EndsWith(weeks, "0")) {
            result.dateRules |= CALCULATOR_HIGHLIGHT_ROUND;
        }
        result.dateRules |= Repetition(weeks);
    }
    return result;
}

/// Reports actionable fixture details while retaining additional independent failures in the same run.
static void Check(bool condition, const char* description, const SYSTEMTIME& start,
        const SYSTEMTIME& selected, const HighlightZone& zone, DWORD mask) {
    if (condition) {
        return;
    }
    failures++;
    if (failures <= 20) {
        std::fprintf(stderr, "FAIL %s: UTC start %04u-%02u-%02u %02u:%02u, date %04u-%02u-%02u, mask 0x%lX, ",
            description, start.wYear, start.wMonth, start.wDay, start.wHour, start.wMinute,
            selected.wYear, selected.wMonth, selected.wDay, mask);
        std::fwprintf(stderr, L"zone %ls\n", zone.key);
    }
}

/// Verifies displayed totals, the first enabled event and the native calendar's highlight decision.
static void CheckMask(const SYSTEMTIME& start, const SYSTEMTIME& selected, const HighlightZone& zone,
        const HighlightExpected& expected, DWORD mask) {
    const HighlightHour* event = nullptr;
    DWORD reasons = expected.dateRules;
    for (const HighlightHour& candidate : expected.hours) {
        reasons |= candidate.rules;
        if (event == nullptr && (candidate.rules & mask) != 0) {
            event = &candidate;
        }
    }
    TimeCalculatorDay actual;
    actual.totals[HOURS] = 123456789;
    TimeCalculatorDay original = actual;
    bool valid = TimeCalculator::CalculateDayUtc(start, selected, zone.information, &actual, mask);
    bool highlighted = TimeCalculator::IsHighlightedDayUtc(start, selected, zone.information, mask);
    Check(valid == expected.valid, "date validity", start, selected, zone, mask);
    Check(highlighted == (expected.valid && (reasons & mask) != 0), "highlight", start, selected, zone, mask);
    if (!expected.valid) {
        Check(std::memcmp(&actual, &original, sizeof(actual)) == 0, "invalid result unchanged",
            start, selected, zone, mask);
        return;
    }
    Check(actual.hasHourTime == (event != nullptr), "hour event presence", start, selected, zone, mask);
    for (int unit = 0; unit < TIME_CALCULATOR_TOTAL_COUNT; unit++) {
        ULONGLONG total = expected.totals[unit];
        if (unit == HOURS && event != nullptr) {
            total = event->hours;
        }
        Check(actual.totals[unit] == total, "displayed total", start, selected, zone, mask);
    }
    if (event != nullptr) {
        Check(Minute(actual.hourTime) == event->utcMinute, "exact first enabled UTC event",
            start, selected, zone, mask);
    }
    if (!zone.named && zone.offset == 0) {
        TimeCalculatorDay wall = {};
        bool wallValid = TimeCalculator::CalculateDay(start, selected, &wall, mask);
        Check(wallValid == valid && wall.hasHourTime == actual.hasHourTime, "local day result",
            start, selected, zone, mask);
        Check(TimeCalculator::IsHighlightedDay(start, selected, mask) == highlighted,
            "local calendar highlight", start, selected, zone, mask);
        for (int unit = 0; unit < TIME_CALCULATOR_TOTAL_COUNT; unit++) {
            Check(wall.totals[unit] == actual.totals[unit], "local displayed total",
                start, selected, zone, mask);
        }
    }
}

/// Checks every individual rule and all two-rule interactions, or every possible combination when requested.
static void CheckDate(const SYSTEMTIME& start, const SYSTEMTIME& selected, const HighlightZone& zone,
        bool exhaustive = false) {
    HighlightExpected expected = Expected(start, selected, zone);
    if (exhaustive) {
        for (DWORD mask = 0; mask <= TIME_CALCULATOR_ALL_HIGHLIGHTS; mask++) {
            CheckMask(start, selected, zone, expected, mask);
        }
        return;
    }
    CheckMask(start, selected, zone, expected, 0);
    CheckMask(start, selected, zone, expected, TIME_CALCULATOR_DEFAULT_HIGHLIGHTS);
    CheckMask(start, selected, zone, expected, TIME_CALCULATOR_ALL_HIGHLIGHTS);
    for (DWORD first = 1; first <= CALCULATOR_HIGHLIGHT_NINES; first <<= 1) {
        CheckMask(start, selected, zone, expected, first);
        CheckMask(start, selected, zone, expected, TIME_CALCULATOR_ALL_HIGHLIGHTS & ~first);
        for (DWORD second = first << 1; second <= CALCULATOR_HIGHLIGHT_NINES; second <<= 1) {
            CheckMask(start, selected, zone, expected, first | second);
        }
    }
}

/// Exercises round-number transitions, every repeated digit, long anniversaries and all option combinations.
static void TestPatterns() {
    HighlightZone utc = Zone(L"UTC+00:00");
    const int offsets[] = {
        -1,
        0,
        1,
        2,
        3,
        4,
        6,
        7,
        9,
        10,
        11,
        12,
        14,
        20,
        22,
        28,
        30,
        31,
        32,
        33,
        40,
        44,
        49,
        55,
        63,
        64,
        66,
        70,
        77,
        84,
        88,
        99,
        100,
        101,
        111,
        140,
        222,
        333,
        444,
        555,
        666,
        777,
        888,
        999,
        1000,
        1111,
        2222,
        6666,
        9999,
        11111,
        77777,
        99999,
        111111
    };
    const SYSTEMTIME starts[] = {
        Date(2001, 1, 1),
        Date(2001, 1, 1, 13, 37),
        Date(2001, 1, 1, 23, 59)
    };
    for (const SYSTEMTIME& start : starts) {
        for (int offset : offsets) {
            SYSTEMTIME day = Fields(Minute(Date(start.wYear, start.wMonth, start.wDay)) + offset * 1440LL);
            CheckDate(start, day, utc);
        }
    }
    SYSTEMTIME origin = Date(2001, 1, 1, 13, 37);
    for (int offset : { 0, 28, 77, 333 }) {
        CheckDate(origin, Fields(Minute(Date(2001, 1, 1)) + offset * 1440LL), utc, true);
    }
}

/// Targets larger repeated-hour patterns and milestones exactly at local day boundaries.
static void TestHourBoundaries() {
    HighlightZone utc = Zone(L"UTC+00:00");
    const ULONGLONG milestones[] = {
        9,
        10,
        11,
        22,
        33,
        66,
        99,
        100,
        111,
        999,
        1000,
        1111,
        2222,
        6666,
        9999,
        111111,
        999999
    };
    const SYSTEMTIME starts[] = {
        Date(2001, 1, 1, 13, 37),
        Date(2001, 1, 1, 8),
        Date(2001, 1, 1, 7, 59)
    };
    for (const SYSTEMTIME& start : starts) {
        for (ULONGLONG hours : milestones) {
            SYSTEMTIME event = Fields(Minute(start) + static_cast<long long>(hours) * 60);
            SYSTEMTIME date = Date(event.wYear, event.wMonth, event.wDay);
            for (int adjacent : { -1, 0, 1 }) {
                CheckDate(start, Fields(Minute(date) + adjacent * 1440LL), utc);
            }
        }
    }
}

/// Covers leap centuries, absent anniversary days, lower and upper date limits, and non-hour fixed offsets.
static void TestCalendarEdges() {
    HighlightZone utc = Zone(L"UTC+00:00");
    const SYSTEMTIME starts[] = {
        Date(1601, 1, 1),
        Date(1699, 12, 31, 23, 59),
        Date(1899, 12, 31, 13, 37),
        Date(1999, 12, 31),
        Date(2000, 2, 29, 12, 30),
        Date(2025, 1, 31, 23, 59),
        Date(2024, 2, 29),
        Date(2099, 12, 31, 13, 37),
        Date(2399, 12, 31),
        Date(9999, 11, 30, 23, 59)
    };
    for (const SYSTEMTIME& start : starts) {
        for (int offset : { 0, 1, 27, 28, 29, 30, 31, 32, 59, 60, 365, 366 }) {
            SYSTEMTIME selected =
                Fields(Minute(Date(start.wYear, start.wMonth, start.wDay)) + offset * 1440LL);
            if (selected.wYear <= 9999) {
                selected.wHour = 23;
                selected.wMinute = 59;
                CheckDate(start, selected, utc);
            }
        }
    }
    const HighlightZone fixed[] = {
        Zone(L"UTC+05:45", 345),
        Zone(L"UTC-03:30", -210),
        Zone(L"UTC+14:00", 840),
        Zone(L"UTC-12:00", -720)
    };
    for (const HighlightZone& zone : fixed) {
        SYSTEMTIME start = Date(2026, 1, 1, 18, 37);
        for (int offset : { 0, 1, 2, 7, 28, 77, 333 }) {
            CheckDate(start, Fields(Minute(Date(2026, 1, 1)) + offset * 1440LL), zone);
        }
    }
}

/// Samples real UTC minutes across one-hour, half-hour, midnight and whole-date timezone transitions.
static void TestTransitions() {
    HighlightZone prague = Zone(L"Central Europe Standard Time", 0, true);
    HighlightZone howe = Zone(L"Lord Howe Standard Time", 0, true);
    HighlightZone cuba = Zone(L"Cuba Standard Time", 0, true);
    HighlightZone samoa = Zone(L"Samoa Standard Time", 0, true);
    const SYSTEMTIME dates[] = {
        Date(2026, 3, 29),
        Date(2026, 10, 25),
        Date(2026, 4, 5),
        Date(2026, 10, 4),
        Date(2026, 3, 8),
        Date(2026, 11, 1),
        Date(2011, 12, 29),
        Date(2011, 12, 30),
        Date(2011, 12, 31)
    };
    const HighlightZone zones[] = { prague, prague, howe, howe, cuba, cuba, samoa, samoa, samoa };
    for (size_t index = 0; index < ARRAYSIZE(dates); index++) {
        for (int hours : { 5, 10, 11, 22, 33, 66, 99, 100, 111, 666, 999, 1000, 1111 }) {
            SYSTEMTIME start = Fields(Minute(dates[index]) - hours * 60LL + 37);
            CheckDate(start, dates[index], zones[index]);
        }
    }
}

/// Asserts hand-derived instants at midnight, the final minute and both occurrences of a repeated local hour.
static void TestExplicitInstants() {
    HighlightZone utc = Zone(L"UTC+00:00");
    SYSTEMTIME start = Date(2001, 1, 1, 8);
    SYSTEMTIME selected = Date(2001, 2, 12);
    TimeCalculatorDay actual = {};
    bool valid = TimeCalculator::CalculateDayUtc(start, selected, utc.information, &actual,
        CALCULATOR_HIGHLIGHT_ROUND);
    Check(valid
        && actual.hasHourTime
        && actual.totals[HOURS] == 1000
        && Minute(actual.hourTime) == Minute(Date(2001, 2, 12)), "1000 hours exactly at midnight",
        start, selected, utc, CALCULATOR_HIGHLIGHT_ROUND);
    start = Date(2001, 1, 1, 7, 59);
    selected = Date(2001, 2, 11);
    valid = TimeCalculator::CalculateDayUtc(start, selected, utc.information, &actual,
        CALCULATOR_HIGHLIGHT_ROUND);
    Check(valid
        && actual.hasHourTime
        && actual.totals[HOURS] == 1000
        && Minute(actual.hourTime) == Minute(Date(2001, 2, 11, 23, 59)), "1000 hours at the final minute",
        start, selected, utc, CALCULATOR_HIGHLIGHT_ROUND);
    HighlightZone prague = Zone(L"Central Europe Standard Time", 0, true);
    start = Date(2026, 10, 24, 14, 30);
    selected = Date(2026, 10, 25);
    valid = TimeCalculator::CalculateDayUtc(start, selected, prague.information, &actual,
        CALCULATOR_HIGHLIGHT_ROUND);
    Check(valid
        && actual.hasHourTime
        && actual.totals[HOURS] == 10
        && Minute(actual.hourTime) == Minute(Date(2026, 10, 25, 0, 30)),
        "first autumn occurrence is ten hours", start, selected, prague, CALCULATOR_HIGHLIGHT_ROUND);
    valid = TimeCalculator::CalculateDayUtc(start, selected, prague.information, &actual,
        CALCULATOR_HIGHLIGHT_ONES);
    Check(valid
        && actual.hasHourTime
        && actual.totals[HOURS] == 11
        && Minute(actual.hourTime) == Minute(Date(2026, 10, 25, 1, 30)),
        "second autumn occurrence is eleven hours", start, selected, prague, CALCULATOR_HIGHLIGHT_ONES);
    DWORD combined = CALCULATOR_HIGHLIGHT_ROUND | CALCULATOR_HIGHLIGHT_ONES;
    valid = TimeCalculator::CalculateDayUtc(start, selected, prague.information, &actual, combined);
    Check(valid
        && actual.hasHourTime
        && actual.totals[HOURS] == 10
        && Minute(actual.hourTime) == Minute(Date(2026, 10, 25, 0, 30)),
        "combined rules choose the earlier event", start, selected, prague, combined);
}

/// Runs independent headless milestone checks without changing system time, fonts, input or saved user data.
int main() {
    TestPatterns();
    TestHourBoundaries();
    TestCalendarEdges();
    TestTransitions();
    TestExplicitInstants();
    if (failures != 0) {
        return EXIT_FAILURE;
    }
    std::puts("PASS: independent calendar milestones, displayed event times, "
        "rule combinations and DST boundaries.");
    return EXIT_SUCCESS;
}
