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
 * Last modified for version 1.7.2.0
 */

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "../CalClock/TimeCalculator.h"
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using ReferenceMinutes = std::chrono::duration<LONGLONG, std::ratio<60>>;
using ReferenceTime = std::chrono::sys_time<ReferenceMinutes>;

struct MonthAnchorCase {
    const wchar_t* zone;
    SYSTEMTIME first;
    SYSTEMTIME previousAnchor;
    SYSTEMTIME anchor;
    int months;
};

static constexpr int HOURS = static_cast<int>(TimeCalculatorUnit::Hours);
static constexpr int DAYS = static_cast<int>(TimeCalculatorUnit::Days);
static constexpr int WEEKS = static_cast<int>(TimeCalculatorUnit::Weeks);
static constexpr int MONTHS = static_cast<int>(TimeCalculatorUnit::Months);
static constexpr int YEARS = static_cast<int>(TimeCalculatorUnit::Years);
static constexpr int MINUTES = static_cast<int>(TimeCalculatorUnit::Minutes);

/// Stops at the first failed requirement with a meaningful diagnostic.
static void Require(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAILED: %s\n", description);
        std::exit(EXIT_FAILURE);
    }
}

/// Creates a local timestamp independently of the production conversion functions.
static SYSTEMTIME Date(WORD year, WORD month, WORD day, WORD hour = 0, WORD minute = 0) {
    SYSTEMTIME time = {};
    time.wYear = year;
    time.wMonth = month;
    time.wDay = day;
    time.wHour = hour;
    time.wMinute = minute;
    return time;
}

/// Converts calendar fields to the standard library's independent Gregorian day representation.
static std::chrono::sys_days CalendarDay(const SYSTEMTIME& time) {
    std::chrono::year_month_day day(std::chrono::year(time.wYear), std::chrono::month(time.wMonth),
        std::chrono::day(time.wDay));
    return std::chrono::sys_days(day);
}

/// Returns the requested day offset using standard-library calendar arithmetic.
static SYSTEMTIME AddDays(const SYSTEMTIME& time, int days) {
    std::chrono::year_month_day day(CalendarDay(time) + std::chrono::days(days));
    return Date(static_cast<WORD>(static_cast<int>(day.year())),
        static_cast<WORD>(static_cast<unsigned>(day.month())),
        static_cast<WORD>(static_cast<unsigned>(day.day())), time.wHour, time.wMinute);
}

/// Checks calendar boundaries, invalid data and minute normalization without changing invalid inputs.
static void TestValidation() {
    SYSTEMTIME minimum = Date(1601, 1, 1);
    SYSTEMTIME maximum = Date(9999, 12, 31, 23, 59);
    Require(TimeCalculator::Normalize(&minimum), "minimum Gregorian date");
    Require(minimum.wDayOfWeek == 1, "1601-01-01 is Monday");
    Require(TimeCalculator::Normalize(&maximum), "maximum Gregorian date");
    Require(!TimeCalculator::Normalize(nullptr), "null normalization destination");
    SYSTEMTIME invalid[] = {
        Date(0, 1, 1),
        Date(1600, 12, 31),
        Date(10000, 1, 1),
        Date(2026, 0, 1),
        Date(2026, 13, 1),
        Date(2026, 1, 0),
        Date(2026, 1, 32),
        Date(2026, 2, 29),
        Date(1900, 2, 29),
        Date(2100, 2, 29),
        Date(2026, 4, 31),
        Date(2026, 1, 1, 24),
        Date(2026, 1, 1, 0, 60)
    };
    for (SYSTEMTIME time : invalid) {
        SYSTEMTIME previous = time;
        Require(!TimeCalculator::Normalize(&time), "invalid calendar fields rejected");
        Require(std::memcmp(&time, &previous, sizeof(time)) == 0, "invalid normalization is nondestructive");
    }
    SYSTEMTIME leap = Date(2000, 2, 29, 12, 34);
    leap.wSecond = 59;
    leap.wMilliseconds = 999;
    leap.wDayOfWeek = 6;
    Require(TimeCalculator::Normalize(&leap), "Gregorian 400-year leap exception");
    Require(leap.wSecond == 0 && leap.wMilliseconds == 0 && leap.wDayOfWeek == 2,
        "seconds discarded and weekday recomputed");
    TimeCalculatorInterval interval = {};
    interval.totals[HOURS] = 123;
    Require(!TimeCalculator::Calculate(maximum, minimum, &interval), "reversed interval rejected");
    Require(interval.totals[HOURS] == 123, "invalid interval leaves destination unchanged");
    Require(!TimeCalculator::Calculate(minimum, maximum, nullptr), "null interval destination rejected");
    Require(!TimeCalculator::Calculate(invalid[0], maximum, &interval), "unset starting date rejected");
    Require(!TimeCalculator::Calculate(minimum, invalid[0], &interval), "unset ending date rejected");
    TimeCalculatorDay day = {};
    day.totals[DAYS] = 123;
    Require(!TimeCalculator::CalculateDay(maximum, minimum, &day), "day before start rejected");
    Require(day.totals[DAYS] == 123, "invalid selected day leaves destination unchanged");
    Require(!TimeCalculator::CalculateDay(minimum, maximum, nullptr), "null day destination rejected");
    Require(!TimeCalculator::IsHighlightedDay(maximum, minimum), "day before start never highlighted");
}

/// Verifies the intentional distinction between exact elapsed time and midnight-based calendar totals.
static void TestIntervals() {
    TimeCalculatorInterval interval = {};
    Require(TimeCalculator::Calculate(Date(2026, 1, 1, 23, 30), Date(2026, 1, 2, 0, 15), &interval),
        "cross-midnight interval calculated");
    Require(interval.totals[HOURS] == 0 && interval.totals[DAYS] == 1 && interval.totals[WEEKS] == 0,
        "calendar days count midnight while hours count exact elapsed time");
    Require(interval.parts[HOURS][MINUTES] == 45 && interval.parts[DAYS][DAYS] == 0,
        "decompositions retain elapsed minutes");
    Require(TimeCalculator::Calculate(Date(2026, 1, 1), Date(2026, 1, 10, 1, 2), &interval),
        "week decomposition calculated");
    Require(interval.totals[HOURS] == 217 && interval.totals[DAYS] == 9 && interval.totals[WEEKS] == 1,
        "whole unit totals");
    Require(interval.parts[WEEKS][WEEKS] == 1
        && interval.parts[WEEKS][DAYS] == 2
        && interval.parts[WEEKS][HOURS] == 1
        && interval.parts[WEEKS][MINUTES] == 2,
        "week, day, hour and minute components");
    Require(TimeCalculator::Calculate(Date(2025, 1, 10, 12), Date(2025, 2, 10, 11, 59), &interval),
        "anniversary minute calculated");
    Require(interval.totals[MONTHS] == 1
        && interval.parts[MONTHS][MONTHS] == 0
        && interval.parts[MONTHS][DAYS] == 30
        && interval.parts[MONTHS][HOURS] == 23
        && interval.parts[MONTHS][MINUTES] == 59,
        "month total starts at midnight, decomposition at exact time");
    SYSTEMTIME first = Date(2026, 1, 1, 12, 34);
    first.wSecond = 59;
    first.wMilliseconds = 999;
    SYSTEMTIME last = Date(2026, 1, 1, 12, 34);
    Require(TimeCalculator::Calculate(first, last, &interval),
        "same minute ignores seconds without reversing");
    for (int row = 0; row < TIME_CALCULATOR_TOTAL_COUNT; row++) {
        Require(interval.totals[row] == 0, "same minute has zero totals");
        for (int unit = 0; unit < TIME_CALCULATOR_PART_COUNT; unit++) {
            Require(interval.parts[row][unit] == 0, "same minute has empty decompositions");
        }
    }
    Require(TimeCalculator::Calculate(Date(2026, 3, 29, 1, 30), Date(2026, 3, 29, 3, 30), &interval),
        "DST date calculated as local wall-clock interval");
    Require(interval.totals[HOURS] == 2, "calculator does not apply system DST rules");
}

/// Covers month ends and the original executable's invalid anchors and duplicate month subtraction.
static void TestMonthBoundaries() {
    TimeCalculatorInterval interval = {};
    Require(TimeCalculator::Calculate(Date(2025, 1, 15, 12, 30), Date(2025, 3, 10, 13, 45), &interval),
        "month subtraction regression calculated");
    Require(interval.totals[MONTHS] == 1
        && interval.parts[MONTHS][MONTHS] == 1
        && interval.parts[MONTHS][DAYS] == 23
        && interval.parts[MONTHS][HOURS] == 1
        && interval.parts[MONTHS][MINUTES] == 15, "complete month is subtracted exactly once");
    Require(interval.parts[YEARS][MONTHS] == 1 && interval.parts[YEARS][DAYS] == 23,
        "month and year decompositions use the same residual interval");
    Require(TimeCalculator::Calculate(Date(2025, 1, 31), Date(2025, 3, 1), &interval),
        "31 January to 1 March does not construct 31 February");
    Require(interval.parts[MONTHS][MONTHS] == 1 && interval.parts[MONTHS][DAYS] == 1,
        "missing anniversary day is clamped to February's end");
    Require(TimeCalculator::Calculate(Date(2025, 1, 31), Date(2025, 2, 28), &interval),
        "short ending month calculated");
    Require(interval.totals[MONTHS] == 0 && interval.parts[MONTHS][DAYS] == 28,
        "calendar-month total retains original day-number rule");
    Require(TimeCalculator::Calculate(Date(2024, 2, 29), Date(2025, 2, 28), &interval),
        "leap-day anniversary calculated");
    Require(interval.totals[YEARS] == 0
        && interval.totals[MONTHS] == 11
        && interval.parts[YEARS][MONTHS] == 11
        && interval.parts[YEARS][DAYS] == 30,
        "year and month totals preserve the original leap-day threshold");
    Require(TimeCalculator::Calculate(Date(2024, 2, 29), Date(2025, 3, 1), &interval),
        "first day after missing leap anniversary calculated");
    Require(interval.totals[YEARS] == 1
        && interval.parts[YEARS][YEARS] == 1
        && interval.parts[YEARS][DAYS] == 1, "year decomposition has a valid February anchor");
    Require(TimeCalculator::Calculate(Date(1601, 1, 1), Date(9999, 12, 31, 23, 59), &interval),
        "full supported date range calculated without overflow");
    Require(interval.totals[YEARS] == 8398
        && interval.parts[YEARS][YEARS] == 8398
        && interval.parts[YEARS][MONTHS] == 11
        && interval.parts[YEARS][DAYS] == 30,
        "full-range month and year counts");
}

/// Checks milestone times, excluded repeated digits, weekly counts and short-month anniversaries.
static void TestMilestones() {
    DWORD originalRules = TIME_CALCULATOR_ALL_HIGHLIGHTS
        & ~(CALCULATOR_HIGHLIGHT_SIXES | CALCULATOR_HIGHLIGHT_NINES);
    SYSTEMTIME start = Date(2026, 1, 1, 13, 37);
    TimeCalculatorDay result = {};
    Require(TimeCalculator::CalculateDay(start, Date(2026, 1, 1, 23, 59), &result, originalRules),
        "starting day selected");
    Require(result.totals[HOURS] == 0 && result.totals[DAYS] == 0 && !result.hasHourTime,
        "starting day displays zeros without a milestone time");
    Require(TimeCalculator::CalculateDay(start, Date(2026, 1, 2), &result, originalRules),
        "following day selected");
    Require(result.totals[HOURS] == 11
        && result.totals[DAYS] == 1
        && result.hasHourTime
        && result.hourTime.wHour == 0
        && result.hourTime.wMinute == 37,
        "repeated-digit hour is reached at the actual starting minute, not midnight");
    TimeCalculatorDay later = {};
    Require(TimeCalculator::CalculateDay(start, Date(2026, 1, 2, 23, 59), &later, originalRules),
        "selected-day time ignored");
    Require(later.totals[HOURS] == result.totals[HOURS]
        && later.hourTime.wMinute == result.hourTime.wMinute, "day result does not depend on picker time");
    SYSTEMTIME origin = Date(2001, 1, 1);
    Require(TimeCalculator::IsHighlightedDay(origin, origin, originalRules),
        "starting date highlighted");
    Require(TimeCalculator::IsHighlightedDay(origin, AddDays(origin, 7), originalRules),
        "first weekly anniversary");
    Require(TimeCalculator::IsHighlightedDay(origin, AddDays(origin, 11), originalRules),
        "repeated-digit day 11");
    Require(TimeCalculator::IsHighlightedDay(origin, AddDays(origin, 55), originalRules),
        "repeated-digit day 55");
    Require(!TimeCalculator::IsHighlightedDay(origin, AddDays(origin, 66), originalRules),
        "repeated sixes excluded");
    Require(!TimeCalculator::IsHighlightedDay(origin, AddDays(origin, 99), originalRules),
        "repeated nines excluded");
    Require(!TimeCalculator::IsHighlightedDay(origin, AddDays(origin, 84), originalRules),
        "ordinary week 12 not highlighted");
    Require(TimeCalculator::IsHighlightedDay(origin, AddDays(origin, 140), originalRules),
        "round week 20 highlighted");
    Require(TimeCalculator::CalculateDay(Date(2025, 1, 31), Date(2025, 2, 28), &result, originalRules)
        && result.totals[MONTHS] == 0, "short-month last day has not crossed original monthly threshold");
    Require(TimeCalculator::IsHighlightedDay(Date(2025, 1, 31), Date(2025, 3, 1), originalRules),
        "calendar-month threshold after short month highlighted");
    Require(TimeCalculator::CalculateDay(Date(1601, 1, 1), Date(9999, 12, 31), &result, originalRules),
        "milestone search on last supported day remains in range");
}

/// Checks independent milestone switches, default compatibility and the added repeated sixes and nines.
static void TestHighlightOptions() {
    SYSTEMTIME origin = Date(2001, 1, 1);
    DWORD repeated = TIME_CALCULATOR_ALL_HIGHLIGHTS & ~(CALCULATOR_HIGHLIGHT_START
        | CALCULATOR_HIGHLIGHT_ROUND | CALCULATOR_HIGHLIGHT_FIRST_WEEKS | CALCULATOR_HIGHLIGHT_ANNIVERSARIES);
    Require((TimeCalculatorState{}.highlights & repeated) == 0,
        "every repeated digit is disabled by default");
    DYNAMIC_TIME_ZONE_INFORMATION utc = {};
    wcscpy_s(utc.TimeZoneKeyName, L"UTC+00:00");
    utc.DynamicDaylightTimeDisabled = TRUE;
    for (int day = 0; day < 400; day++) {
        SYSTEMTIME selected = AddDays(origin, day);
        Require(!TimeCalculator::IsHighlightedDay(origin, selected, 0),
            "disabled rules leave calendar unmarked");
        Require(!TimeCalculator::IsHighlightedDayUtc(origin, selected, utc, 0),
            "UTC calendar honors disabled rules");
        bool any = false;
        for (DWORD flag = 1; flag <= CALCULATOR_HIGHLIGHT_NINES; flag <<= 1) {
            bool highlighted = TimeCalculator::IsHighlightedDay(origin, selected, flag);
            bool utcHighlighted = TimeCalculator::IsHighlightedDayUtc(origin, selected, utc, flag);
            if (highlighted != utcHighlighted) {
                std::fprintf(stderr, "Milestone mismatch: day=%d, flag=0x%lX, local=%d, utc=%d\n",
                    day, flag, highlighted, utcHighlighted);
            }
            Require(highlighted == utcHighlighted, "local and UTC rule filters agree in UTC");
            any = any || highlighted;
        }
        Require(any == TimeCalculator::IsHighlightedDay(origin, selected, TIME_CALCULATOR_ALL_HIGHLIGHTS),
            "combined rules are the union of independently enabled rules");
    }
    const DWORD digits[] = {
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
    for (int digit = 1; digit <= 9; digit++) {
        Require(TimeCalculator::IsHighlightedDay(origin, AddDays(origin, digit * 11), digits[digit - 1]),
            "each repeated digit can highlight its own day count");
    }
    Require(TimeCalculator::IsHighlightedDay(origin, origin, CALCULATOR_HIGHLIGHT_START),
        "starting-day switch");
    Require(!TimeCalculator::IsHighlightedDay(origin, AddDays(origin, 1), CALCULATOR_HIGHLIGHT_START),
        "starting-day switch does not enable later milestones");
    Require(TimeCalculator::IsHighlightedDay(origin, AddDays(origin, 7), CALCULATOR_HIGHLIGHT_FIRST_WEEKS),
        "first whole week can be enabled independently");
    Require(!TimeCalculator::IsHighlightedDay(origin, AddDays(origin, 70), CALCULATOR_HIGHLIGHT_FIRST_WEEKS),
        "first-week rule stops after nine weeks");
    Require(TimeCalculator::IsHighlightedDay(origin, AddDays(origin, 70), CALCULATOR_HIGHLIGHT_ROUND),
        "round-week rule remains separate");
    Require(TimeCalculator::IsHighlightedDay(origin, Date(2001, 2, 1), CALCULATOR_HIGHLIGHT_ANNIVERSARIES),
        "calendar anniversaries can be enabled independently");
    TimeCalculatorDay result = {};
    Require(TimeCalculator::CalculateDay(origin, AddDays(origin, 1), &result, 0) && !result.hasHourTime,
        "disabled hourly milestones leave the midnight total");
    Require(TimeCalculator::CalculateDay(origin, AddDays(origin, 1), &result, CALCULATOR_HIGHLIGHT_ROUND)
        && result.hasHourTime
        && result.totals[HOURS] == 30,
        "selected rules determine the shown hourly milestone");
}

/// Independently verifies fixed-unit totals and decomposition reconstruction across Gregorian boundaries.
static void TestCalendarMatrix() {
    const WORD years[] = { 1601, 1700, 1800, 1900, 1999, 2000, 2004, 2026, 2099, 2100, 2400, 9998 };
    const int spans[] = { 0, 1, 7, 28, 31, 59, 365 };
    for (WORD year : years) {
        for (WORD month = 1; month <= 12; month++) {
            SYSTEMTIME start = Date(year, month, 28, 13, 37);
            for (int span : spans) {
                SYSTEMTIME end = AddDays(start, span);
                end.wHour = 17;
                end.wMinute = 19;
                TimeCalculatorInterval result = {};
                Require(TimeCalculator::Calculate(start, end, &result),
                    "calendar matrix interval calculated");
                ULONGLONG minutes = static_cast<ULONGLONG>(span) * 1440 + 222;
                Require(result.totals[HOURS] == minutes / 60
                    && result.totals[DAYS] == span
                    && result.totals[WEEKS] == span / 7,
                    "Gregorian date differences match independent calendar");
                for (int row : { HOURS, DAYS, WEEKS }) {
                    ULONGLONG reconstructed = result.parts[row][WEEKS] * 10080
                        + result.parts[row][DAYS] * 1440 + result.parts[row][HOURS] * 60
                        + result.parts[row][MINUTES];
                    Require(reconstructed == minutes, "fixed-unit decomposition reconstructs exact interval");
                }
                Require(result.parts[MONTHS][MONTHS] == result.parts[YEARS][YEARS] * 12
                    + result.parts[YEARS][MONTHS], "month/year decomposition agrees");
                for (int unit : { DAYS, HOURS, MINUTES }) {
                    Require(result.parts[MONTHS][unit] == result.parts[YEARS][unit],
                        "month/year residuals agree at calendar boundaries");
                }
            }
        }
    }
}

/// Resolves a real zone from the same production catalog used by both forms.
static DYNAMIC_TIME_ZONE_INFORMATION TestZone(const wchar_t* key) {
    std::vector<DYNAMIC_TIME_ZONE_INFORMATION> zones;
    LoadTimeZoneList(&zones);
    for (const DYNAMIC_TIME_ZONE_INFORMATION& zone : zones) {
        if (wcscmp(zone.TimeZoneKeyName, key) == 0) {
            return zone;
        }
    }
    Require(false, "requested Windows zone is present");
    return DYNAMIC_TIME_ZONE_INFORMATION{};
}

/// Resolves an explicitly chosen occurrence rather than guessing an ambiguous local timestamp.
static SYSTEMTIME TestUtc(const DYNAMIC_TIME_ZONE_INFORMATION& zone, const SYSTEMTIME& local,
        unsigned int occurrence = 0) {
    ULONGLONG candidates[2] = {};
    unsigned int count = 0;
    Require(GetTimeZoneUtcCandidates(zone, local, candidates, count) && count > occurrence,
        "local timestamp has the requested occurrence");
    ULARGE_INTEGER ticks = {};
    ticks.QuadPart = candidates[occurrence];
    FILETIME file = { ticks.LowPart, ticks.HighPart };
    SYSTEMTIME utc = {};
    Require(FileTimeToSystemTime(&file, &utc) != FALSE, "candidate converts to UTC fields");
    return utc;
}

/// Checks elapsed UTC durations, repeated hours, missing times and non-hour timezone transitions.
static void TestTimeZones() {
    DYNAMIC_TIME_ZONE_INFORMATION prague = TestZone(L"Central Europe Standard Time");
    DYNAMIC_TIME_ZONE_INFORMATION howe = TestZone(L"Lord Howe Standard Time");
    DYNAMIC_TIME_ZONE_INFORMATION nepal = TestZone(L"UTC+05:45");
    TimeCalculatorInterval result = {};
    SYSTEMTIME first = TestUtc(prague, Date(2026, 3, 28, 12));
    SYSTEMTIME last = TestUtc(prague, Date(2026, 3, 29, 12));
    Require(TimeCalculator::CalculateUtc(first, last, prague, &result), "spring interval resolves");
    Require(result.totals[HOURS] == 23
        && result.totals[DAYS] == 1
        && result.parts[HOURS][HOURS] == 23, "spring day is 23 elapsed hours and one calendar day");
    first = TestUtc(prague, Date(2026, 10, 25, 2, 30), 0);
    last = TestUtc(prague, Date(2026, 10, 25, 2, 30), 1);
    Require(TimeCalculator::CalculateUtc(first, last, prague, &result)
        && result.totals[HOURS] == 1
        && result.totals[DAYS] == 0, "identical wall-clock readings in a fold are distinct UTC instants");
    Require(!TimeCalculator::CalculateUtc(last, first, prague, &result), "reverse UTC interval rejected");
    ULONGLONG candidates[2] = {};
    unsigned int count = 0;
    Require(GetTimeZoneUtcCandidates(prague, Date(2026, 3, 29, 2, 30), candidates, count) && count == 0,
        "spring missing local time is not silently shifted");
    first = TestUtc(howe, Date(2026, 4, 5, 1, 45), 0);
    last = TestUtc(howe, Date(2026, 4, 5, 1, 45), 1);
    Require(TimeCalculator::CalculateUtc(first, last, howe, &result)
        && result.parts[HOURS][HOURS] == 0
        && result.parts[HOURS][MINUTES] == 30, "half-hour fold measures thirty real minutes");
    first = TestUtc(howe, Date(2026, 10, 3, 12));
    last = TestUtc(howe, Date(2026, 10, 4, 12));
    Require(TimeCalculator::CalculateUtc(first, last, howe, &result)
        && result.parts[HOURS][HOURS] == 23
        && result.parts[HOURS][MINUTES] == 30, "half-hour spring transition is reflected in elapsed time");
    first = TestUtc(nepal, Date(2026, 1, 2, 0, 15));
    Require(first.wDay == 1
        && first.wHour == 18
        && first.wMinute == 30, "quarter-hour fixed offset crosses the UTC date correctly");
    SYSTEMTIME local = {};
    Require(ConvertUtcToTimeZone(prague, first, &local), "display in another zone succeeds");
    SYSTEMTIME sameInstant = TestUtc(prague, local);
    Require(sameInstant.wDay == first.wDay
        && sameInstant.wHour == first.wHour
        && sameInstant.wMinute == first.wMinute, "changing display zone preserves the UTC instant");
    first = TestUtc(prague, Date(2026, 10, 24, 16, 30));
    TimeCalculatorDay day = {};
    Require(TimeCalculator::CalculateDayUtc(first, Date(2026, 10, 25), prague, &day)
        && day.hasHourTime
        && day.totals[HOURS] == 10
        && day.hourTime.wHour == 0
        && day.hourTime.wMinute == 30, "milestone retains the specific UTC occurrence of a repeated hour");
    first = TestUtc(prague, Date(2026, 2, 28, 2, 30));
    last = TestUtc(prague, Date(2026, 3, 29, 3, 30));
    Require(TimeCalculator::CalculateUtc(first, last, prague, &result)
        && result.parts[MONTHS][MONTHS] == 1, "calendar months remain defined across a DST gap");
}

/// Converts valid calendar fields into independent standard-library minute arithmetic.
static ReferenceTime ReferenceMinute(const SYSTEMTIME& time) {
    return ReferenceTime(CalendarDay(time)) + std::chrono::hours(time.wHour)
        + std::chrono::minutes(time.wMinute);
}

/// Converts an independent minute timestamp to fields without using any production date helper.
static SYSTEMTIME ReferenceFields(ReferenceTime time) {
    std::chrono::sys_days date = std::chrono::floor<std::chrono::days>(time);
    std::chrono::year_month_day day(date);
    std::chrono::hh_mm_ss clock(time - date);
    return Date(static_cast<WORD>(static_cast<int>(day.year())),
        static_cast<WORD>(static_cast<unsigned>(day.month())),
        static_cast<WORD>(static_cast<unsigned>(day.day())),
        static_cast<WORD>(clock.hours().count()),
        static_cast<WORD>(clock.minutes().count()));
}

/// Finds month thresholds by chronological search, including the documented missing-anniversary-day rule.
static int ReferenceMonths(const SYSTEMTIME& first, const SYSTEMTIME& last) {
    std::chrono::year_month month = std::chrono::year(first.wYear) / std::chrono::month(first.wMonth);
    ReferenceTime end = ReferenceMinute(last);
    int low = 0;
    int high = 100800;
    while (low < high) {
        int count = low + (high - low + 1) / 2;
        std::chrono::year_month target = month + std::chrono::months(count);
        std::chrono::year_month_day anniversary = target / std::chrono::day(first.wDay);
        ReferenceTime boundary;
        if (anniversary.ok()) {
            boundary = ReferenceTime(std::chrono::sys_days(anniversary))
                + std::chrono::hours(first.wHour) + std::chrono::minutes(first.wMinute);
        } else {
            boundary = std::chrono::sys_days((target + std::chrono::months(1)) / std::chrono::day(1));
        }
        if (boundary <= end) {
            low = count;
        } else {
            high = count - 1;
        }
    }
    return low;
}

/// Builds a month anchor using the standard library's calendar validity and last-day representation.
static ReferenceTime ReferenceAnchor(const SYSTEMTIME& first, int months) {
    std::chrono::year_month month = std::chrono::year(first.wYear) / std::chrono::month(first.wMonth);
    month += std::chrono::months(months);
    std::chrono::year_month_day date = month / std::chrono::day(first.wDay);
    if (!date.ok()) {
        date = std::chrono::year_month_day(month / std::chrono::last);
    }
    return ReferenceTime(std::chrono::sys_days(date)) + std::chrono::hours(first.wHour)
        + std::chrono::minutes(first.wMinute);
}

/// Checks every total and decomposition against independent calendar arithmetic and reconstruction.
static void VerifyReferenceInterval(const SYSTEMTIME& first, const SYSTEMTIME& last,
        const TimeCalculatorInterval& result, const char* description) {
    LONGLONG minutes = (ReferenceMinute(last) - ReferenceMinute(first)).count();
    LONGLONG days = (CalendarDay(last) - CalendarDay(first)).count();
    SYSTEMTIME midnight = first;
    midnight.wHour = 0;
    midnight.wMinute = 0;
    int totalMonths = ReferenceMonths(midnight, last);
    Require(result.totals[HOURS] == static_cast<ULONGLONG>(minutes / 60)
        && result.totals[DAYS] == static_cast<ULONGLONG>(days)
        && result.totals[WEEKS] == static_cast<ULONGLONG>(days / 7)
        && result.totals[MONTHS] == totalMonths
        && result.totals[YEARS] == totalMonths / 12, description);
    const ULONGLONG scales[] = { 60, 1440, 10080 };
    for (int row = HOURS; row <= WEEKS; row++) {
        ULONGLONG rebuilt = result.parts[row][WEEKS] * 10080 + result.parts[row][DAYS] * 1440
            + result.parts[row][HOURS] * 60 + result.parts[row][MINUTES];
        Require(rebuilt == static_cast<ULONGLONG>(minutes), "fixed-unit row reconstructs elapsed minutes");
        Require(result.parts[row][row] == static_cast<ULONGLONG>(minutes) / scales[row],
            "leading fixed-unit count is exact");
        Require(result.parts[row][MINUTES] < 60
            && result.parts[row][MONTHS] == 0
            && result.parts[row][YEARS] == 0, "fixed-unit component ranges and unused fields");
        if (row != HOURS) {
            Require(result.parts[row][HOURS] < 24, "subordinate hour component is below one day");
        }
        if (row == WEEKS) {
            Require(result.parts[row][DAYS] < 7, "subordinate day component is below one week");
        }
    }
    int months = ReferenceMonths(first, last);
    ReferenceTime anchor = ReferenceAnchor(first, months);
    ULONGLONG remaining = static_cast<ULONGLONG>((ReferenceMinute(last) - anchor).count());
    Require(result.parts[MONTHS][MONTHS] == months
        && result.parts[YEARS][YEARS] == months / 12
        && result.parts[YEARS][MONTHS] == months % 12, "calendar decomposition month/year count");
    for (int row : { MONTHS, YEARS }) {
        Require(result.parts[row][DAYS] == remaining / 1440
            && result.parts[row][HOURS] == remaining % 1440 / 60
            && result.parts[row][MINUTES] == remaining % 6
            && result.parts[row][WEEKS] == 0,
            "calendar decomposition reconstructs its independent anniversary anchor");
    }
}

/// Exercises different start minutes, irregular month ends and century leap boundaries without Windows
/// arithmetic.
static void TestIndependentIntervals() {
    const WORD years[] = {
        1601,
        1699,
        1700,
        1899,
        1900,
        1999,
        2000,
        2023,
        2024,
        2099,
        2100,
        2400,
        9998,
        9999
    };
    const WORD monthDays[] = { 1, 15, 28, 29, 30, 31 };
    const int starts[] = { 0, 1, 59, 60, 754, 1439 };
    const int spans[] = {
        0,
        1,
        59,
        60,
        61,
        1439,
        1440,
        1441,
        10079,
        10080,
        10081,
        40319,
        40320,
        40321,
        41760,
        43200,
        44640,
        525599,
        525600,
        527040,
        1051200
    };
    ReferenceTime maximum = ReferenceMinute(Date(9999, 12, 31, 23, 59));
    for (WORD year : years) {
        for (WORD month = 1; month <= 12; month++) {
            for (WORD day : monthDays) {
                std::chrono::year_month_day date{
                    std::chrono::year(year),
                    std::chrono::month(month),
                    std::chrono::day(day)
                };
                if (!date.ok()) {
                    continue;
                }
                for (int minute : starts) {
                    SYSTEMTIME first = Date(year, month, day, static_cast<WORD>(minute / 60),
                        static_cast<WORD>(minute % 60));
                    for (int span : spans) {
                        ReferenceTime end = ReferenceMinute(first) + std::chrono::minutes(span);
                        if (end > maximum) {
                            continue;
                        }
                        SYSTEMTIME last = ReferenceFields(end);
                        TimeCalculatorInterval result = {};
                        bool valid = TimeCalculator::Calculate(first, last, &result);
                        if (!valid) {
                            std::fprintf(stderr,
                                "Rejected interval %u-%02u-%02u %02u:%02u -> %u-%02u-%02u %02u:%02u\n",
                                first.wYear, first.wMonth, first.wDay, first.wHour, first.wMinute,
                                last.wYear, last.wMonth, last.wDay, last.wHour, last.wMinute);
                        }
                        Require(valid, "independent calendar interval accepted");
                        VerifyReferenceInterval(first, last, result,
                            "calendar totals match independent reference");
                        if (span > 0) {
                            TimeCalculatorInterval previous = result;
                            Require(!TimeCalculator::Calculate(last, first, &result)
                                && std::memcmp(&result, &previous, sizeof(result)) == 0,
                                "reversed independent interval leaves every output component unchanged");
                        }
                    }
                }
            }
        }
    }
}

/// Checks UTC intervals in fixed zones against independently shifted civil dates and minute arithmetic.
static void TestIndependentFixedZones() {
    const wchar_t* keys[] = { L"UTC-12:00", L"UTC-03:30", L"UTC+00:00", L"UTC+05:45", L"UTC+14:00" };
    const int offsets[] = { -720, -210, 0, 345, 840 };
    const SYSTEMTIME starts[] = {
        Date(1601, 1, 2),
        Date(1900, 2, 28, 23, 59),
        Date(2000, 2, 29, 12, 34),
        Date(2024, 12, 31, 23, 59),
        Date(2026, 1, 31, 17, 43),
        Date(2026, 10, 25, 1, 30),
        Date(9998, 1, 31)
    };
    const int spans[] = { 0, 1, 59, 61, 1439, 1440, 10080, 40320, 41760, 43200, 44640, 525600 };
    for (size_t zoneIndex = 0; zoneIndex < ARRAYSIZE(keys); zoneIndex++) {
        DYNAMIC_TIME_ZONE_INFORMATION zone = TestZone(keys[zoneIndex]);
        for (const SYSTEMTIME& first : starts) {
            for (int span : spans) {
                SYSTEMTIME last = ReferenceFields(ReferenceMinute(first) + std::chrono::minutes(span));
                SYSTEMTIME firstLocal =
                    ReferenceFields(ReferenceMinute(first) + std::chrono::minutes(offsets[zoneIndex]));
                SYSTEMTIME lastLocal =
                    ReferenceFields(ReferenceMinute(last) + std::chrono::minutes(offsets[zoneIndex]));
                TimeCalculatorInterval result = {};
                Require(TimeCalculator::CalculateUtc(first, last, zone, &result),
                    "fixed-zone UTC interval accepted");
                VerifyReferenceInterval(firstLocal, lastLocal, result,
                    "fixed-zone UTC totals match independent reference");
                if (span > 0) {
                    TimeCalculatorInterval previous = result;
                    Require(!TimeCalculator::CalculateUtc(last, first, zone, &result)
                        && std::memcmp(&result, &previous, sizeof(result)) == 0,
                        "reversed UTC interval preserves every output component");
                }
            }
        }
    }
}

/// Checks elapsed decompositions minute by minute around hour and half-hour clock changes.
static void TestTransitionMinuteIntervals() {
    const wchar_t* keys[] = {
        L"Central Europe Standard Time",
        L"Central Europe Standard Time",
        L"Lord Howe Standard Time",
        L"Lord Howe Standard Time"
    };
    const SYSTEMTIME transitions[] = {
        Date(2026, 3, 29, 1),
        Date(2026, 10, 25, 1),
        Date(2026, 4, 4, 15),
        Date(2026, 10, 3, 15, 30)
    };
    const int beforeOffsets[] = { 60, 120, 660, 630 };
    const int afterOffsets[] = { 120, 60, 630, 660 };
    const int spans[] = { 0, 1, 29, 30, 31, 59, 60, 61, 119, 120, 121, 1439, 1440, 1500 };
    for (size_t index = 0; index < ARRAYSIZE(keys); index++) {
        DYNAMIC_TIME_ZONE_INFORMATION zone = TestZone(keys[index]);
        ReferenceTime transition = ReferenceMinute(transitions[index]);
        for (int startOffset = -180; startOffset <= 180; startOffset++) {
            ReferenceTime firstMinute = transition + std::chrono::minutes(startOffset);
            int firstOffset = startOffset < 0 ? beforeOffsets[index] : afterOffsets[index];
            SYSTEMTIME first = ReferenceFields(firstMinute);
            SYSTEMTIME localFirst = ReferenceFields(firstMinute + std::chrono::minutes(firstOffset));
            for (int span : spans) {
                ReferenceTime lastMinute = firstMinute + std::chrono::minutes(span);
                int lastOffset = lastMinute < transition ? beforeOffsets[index] : afterOffsets[index];
                SYSTEMTIME last = ReferenceFields(lastMinute);
                SYSTEMTIME localLast = ReferenceFields(lastMinute + std::chrono::minutes(lastOffset));
                TimeCalculatorInterval result = {};
                Require(TimeCalculator::CalculateUtc(first, last, zone, &result),
                    "DST-minute interval accepted");
                LONGLONG dayCount = (CalendarDay(localLast) - CalendarDay(localFirst)).count();
                Require(result.totals[HOURS] == span / 60
                    && result.totals[DAYS] == static_cast<ULONGLONG>(dayCount),
                    "DST-minute totals retain elapsed hours and local calendar-day boundaries");
                for (int row = HOURS; row <= YEARS; row++) {
                    ULONGLONG rebuilt = result.parts[row][WEEKS] * 10080 + result.parts[row][DAYS] * 1440
                        + result.parts[row][HOURS] * 60 + result.parts[row][MINUTES];
                    Require(rebuilt == span
                        && result.parts[row][MONTHS] == 0
                        && result.parts[row][YEARS] == 0,
                        "DST-minute decompositions never lose or duplicate repeated/skipped time");
                }
            }
        }
    }
}

/// Tests exact UTC month/year anchors before, within and after full-hour and half-hour gaps and folds.
static void TestUtcMonthAnchors() {
    const MonthAnchorCase cases[] = {
        MonthAnchorCase{
            L"Central Europe Standard Time",
            Date(2026, 9, 25, 0, 30),
            Date(2026, 9, 25, 0, 30),
            Date(2026, 10, 25, 0, 30),
            1
    }, MonthAnchorCase{
            L"Central Europe Standard Time",
            Date(2025, 10, 25, 0, 30),
            Date(2026, 9, 25, 0, 30),
            Date(2026, 10, 25, 0, 30),
            12
    }, MonthAnchorCase{
            L"Central Europe Standard Time",
            Date(2026, 1, 29, 1, 30),
            Date(2026, 2, 28, 1, 30),
            Date(2026, 3, 29, 1, 0),
            2
    }, MonthAnchorCase{
            L"Central Europe Standard Time",
            Date(2025, 3, 29, 1, 30),
            Date(2026, 2, 28, 1, 30),
            Date(2026, 3, 29, 1, 0),
            12
    }, MonthAnchorCase{
            L"Lord Howe Standard Time",
            Date(2026, 3, 4, 14, 45),
            Date(2026, 3, 4, 14, 45),
            Date(2026, 4, 4, 14, 45),
            1
    }, MonthAnchorCase{
            L"Lord Howe Standard Time",
            Date(2026, 9, 3, 15, 45),
            Date(2026, 9, 3, 15, 45),
            Date(2026, 10, 3, 15, 30), 1
    }
    };
    const int offsets[] = { -15, -1, 0, 1, 15, 30, 45, 60, 75 };
    for (const MonthAnchorCase& item : cases) {
        DYNAMIC_TIME_ZONE_INFORMATION zone = TestZone(item.zone);
        for (int offset : offsets) {
            SYSTEMTIME end = ReferenceFields(ReferenceMinute(item.anchor) + std::chrono::minutes(offset));
            TimeCalculatorInterval result = {};
            Require(TimeCalculator::CalculateUtc(item.first, end, zone, &result),
                "DST month anchor interval accepted");
            int expectedMonths = item.months;
            ReferenceTime anchor = ReferenceMinute(item.anchor);
            if (offset < 0) {
                expectedMonths--;
                anchor = ReferenceMinute(item.previousAnchor);
            }
            ULONGLONG remaining = static_cast<ULONGLONG>((ReferenceMinute(end) - anchor).count());
            if (result.parts[MONTHS][MONTHS] != expectedMonths) {
                std::fprintf(stderr,
                    "Month anchor mismatch: month=%u day=%u offset=%d expected=%d actual=%llu\n",
                    item.anchor.wMonth, item.anchor.wDay, offset, expectedMonths,
                    result.parts[MONTHS][MONTHS]);
            }
            Require(result.parts[MONTHS][MONTHS] == expectedMonths,
                "month completion uses the resolved UTC anniversary rather than repeated local-clock order");
            Require(result.parts[YEARS][YEARS] == expectedMonths / 12
                && result.parts[YEARS][MONTHS] == expectedMonths % 12,
                "year decomposition uses the same UTC anchor");
            for (int row : { MONTHS, YEARS }) {
                Require(result.parts[row][DAYS] == remaining / 1440
                    && result.parts[row][HOURS] == remaining % 1440 / 60
                    && result.parts[row][MINUTES] == remaining % 60,
                    "month/year residual follows the actual earliest existing UTC anniversary minute");
            }
        }
    }
}

/// Resolves a Windows transition date using standard Gregorian weekday arithmetic.
static SYSTEMTIME CatalogTransitionDate(WORD year, const SYSTEMTIME& rule) {
    std::chrono::year_month month = std::chrono::year(year) / rule.wMonth;
    std::chrono::sys_days day;
    if (rule.wYear != 0) {
        day = CalendarDay(rule);
    } else if (rule.wDay == 5) {
        day = std::chrono::sys_days(month / std::chrono::weekday_last(std::chrono::weekday(rule.wDayOfWeek)));
    } else {
        day = std::chrono::sys_days(month
            / std::chrono::weekday_indexed(std::chrono::weekday(rule.wDayOfWeek), rule.wDay));
    }
    return ReferenceFields(ReferenceTime(day) + std::chrono::hours(rule.wHour)
        + std::chrono::minutes(rule.wMinute));
}

/// Checks elapsed rows and local calendar totals at every distinct seasonal transition in the Windows
/// catalog.
static void TestCatalogTransitionIntervals() {
    std::vector<DYNAMIC_TIME_ZONE_INFORMATION> zones;
    LoadTimeZoneList(&zones);
    const int starts[] = { -90, -1, 0, 1, 90 };
    const int spans[] = { 0, 1, 29, 30, 59, 60, 61, 1439, 1440, 1500, 2880 };
    for (const DYNAMIC_TIME_ZONE_INFORMATION& zone : zones) {
        if (zone.StandardDate.wMonth == 0
                || zone.DaylightDate.wMonth == 0
                || wcscmp(zone.TimeZoneKeyName, SYSTEM_TIME_ZONE_KEY) == 0) {
            continue;
        }
        TIME_ZONE_INFORMATION rules = {};
        bool available = GetTimeZoneInformationForYear(2026,
            const_cast<DYNAMIC_TIME_ZONE_INFORMATION*>(&zone), &rules) != FALSE;
        if (!available) {
            Require(false, "catalog transition rules are available");
            return;
        }
        const SYSTEMTIME transitions[] = { rules.DaylightDate, rules.StandardDate };
        const LONG previousBiases[] = { rules.Bias + rules.StandardBias, rules.Bias + rules.DaylightBias };
        for (size_t index = 0; index < ARRAYSIZE(transitions); index++) {
            if (transitions[index].wMonth == 0) {
                continue;
            }
            ReferenceTime transition = ReferenceMinute(CatalogTransitionDate(2026, transitions[index]))
                + std::chrono::minutes(previousBiases[index]);
            for (int offset : starts) {
                SYSTEMTIME first = ReferenceFields(transition + std::chrono::minutes(offset));
                SYSTEMTIME firstLocal = {};
                Require(SystemTimeToTzSpecificLocalTimeEx(&zone, &first, &firstLocal) != FALSE,
                    "native catalog starting instant converts");
                for (int span : spans) {
                    SYSTEMTIME last = ReferenceFields(ReferenceMinute(first) + std::chrono::minutes(span));
                    SYSTEMTIME lastLocal = {};
                    Require(SystemTimeToTzSpecificLocalTimeEx(&zone, &last, &lastLocal) != FALSE,
                        "native catalog ending instant converts");
                    TimeCalculatorInterval result = {};
                    Require(TimeCalculator::CalculateUtc(first, last, zone, &result),
                        "catalog transition interval is valid");
                    LONGLONG dayCount = (CalendarDay(lastLocal) - CalendarDay(firstLocal)).count();
                    ULONGLONG days = static_cast<ULONGLONG>(std::max(0LL, dayCount));
                    Require(result.totals[HOURS] == span / 60
                        && result.totals[DAYS] == days
                        && result.totals[WEEKS] == days / 7
                        && result.totals[MONTHS] == 0
                        && result.totals[YEARS] == 0, "catalog interval totals match native local dates");
                    for (int row = HOURS; row <= YEARS; row++) {
                        ULONGLONG rebuilt = result.parts[row][WEEKS] * 10080 + result.parts[row][DAYS] * 1440
                            + result.parts[row][HOURS] * 60 + result.parts[row][MINUTES];
                        Require(rebuilt == span
                            && result.parts[row][MONTHS] == 0
                            && result.parts[row][YEARS] == 0,
                            "catalog transition decompositions reconstruct the original UTC interval");
                    }
                }
            }
        }
    }
}

/// Runs calculation tests without creating windows, changing system time or starting the supplied executable.
int main() {
    TestValidation();
    TestIntervals();
    TestMonthBoundaries();
    TestMilestones();
    TestHighlightOptions();
    TestCalendarMatrix();
    TestTimeZones();
    TestIndependentIntervals();
    TestIndependentFixedZones();
    TestTransitionMinuteIntervals();
    TestUtcMonthAnchors();
    TestCatalogTransitionIntervals();
    std::puts("Time Calculator: interval, month-end, leap-year, milestone and validation tests passed.");
    return EXIT_SUCCESS;
}
