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
#include "TimeCalculator.h"
#include <algorithm>

static constexpr ULONGLONG TICKS_PER_MINUTE = 600000000ULL;
static constexpr ULONGLONG TICKS_PER_HOUR = 60 * TICKS_PER_MINUTE;
static constexpr ULONGLONG TICKS_PER_DAY = 24 * TICKS_PER_HOUR;
static constexpr int HOURS = static_cast<int>(TimeCalculatorUnit::Hours);
static constexpr int DAYS = static_cast<int>(TimeCalculatorUnit::Days);
static constexpr int WEEKS = static_cast<int>(TimeCalculatorUnit::Weeks);
static constexpr int MONTHS = static_cast<int>(TimeCalculatorUnit::Months);
static constexpr int YEARS = static_cast<int>(TimeCalculatorUnit::Years);
static constexpr int MINUTES = static_cast<int>(TimeCalculatorUnit::Minutes);
static constexpr DWORD REPEATED_DIGIT_HIGHLIGHTS[] = {
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

/// Validates a local Gregorian date and minute and converts its fields directly to a linear tick count.
static bool ReadCalculatorTime(const SYSTEMTIME& source, SYSTEMTIME* normalized, ULONGLONG* value) {
    if (source.wYear < 1601 || source.wYear > 9999) {
        return false;
    }
    SYSTEMTIME time = source;
    time.wSecond = 0;
    time.wMilliseconds = 0;
    FILETIME fileTime = {};
    if (!SystemTimeToFileTime(&time, &fileTime) || !FileTimeToSystemTime(&fileTime, &time)) {
        return false;
    }
    ULARGE_INTEGER ticks = {};
    ticks.LowPart = fileTime.dwLowDateTime;
    ticks.HighPart = fileTime.dwHighDateTime;
    *normalized = time;
    *value = ticks.QuadPart;
    return true;
}

/// Converts a tick count back to local calendar fields without applying a timezone conversion.
static bool ReadCalculatorFields(ULONGLONG value, SYSTEMTIME* time) {
    ULARGE_INTEGER ticks = {};
    ticks.QuadPart = value;
    FILETIME fileTime = { ticks.LowPart, ticks.HighPart };
    return FileTimeToSystemTime(&fileTime, time) != FALSE;
}

/// Removes the time of day from an already validated Gregorian timestamp.
static ULONGLONG CalculatorMidnight(const SYSTEMTIME& time, ULONGLONG value) {
    return value - time.wHour * TICKS_PER_HOUR - time.wMinute * TICKS_PER_MINUTE;
}

/// Counts complete calendar months by comparing the anniversary day and minute, as in the source program.
static int CalculatorMonths(const SYSTEMTIME& start, const SYSTEMTIME& end) {
    int months = (end.wYear - start.wYear) * 12 + end.wMonth - start.wMonth;
    int startMinute = start.wHour * 60 + start.wMinute;
    int endMinute = end.wHour * 60 + end.wMinute;
    if (end.wDay < start.wDay || end.wDay == start.wDay && endMinute < startMinute) {
        months--;
    }
    return months;
}

/// Returns the number of days in a validated Gregorian month, including century leap-year rules.
static WORD CalculatorMonthDays(WORD year, WORD month) {
    static constexpr WORD monthDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
        return 29;
    }
    return monthDays[month - 1];
}

/// Builds an anniversary anchor, using the month's final day when the original day does not exist there.
static SYSTEMTIME CalculatorMonthAnchor(const SYSTEMTIME& start, int months) {
    SYSTEMTIME anchor = start;
    int month = start.wMonth - 1 + months;
    anchor.wYear = static_cast<WORD>(start.wYear + month / 12);
    anchor.wMonth = static_cast<WORD>(month % 12 + 1);
    anchor.wDay = std::min(start.wDay, CalculatorMonthDays(anchor.wYear, anchor.wMonth));
    return anchor;
}

/// Computes exact-hour totals and the midnight-based day, week, month and year totals.
static void CalculateTotals(const SYSTEMTIME& start, const SYSTEMTIME& end, ULONGLONG startValue,
    ULONGLONG endValue, ULONGLONG* totals) {
    ULONGLONG dayStart = CalculatorMidnight(start, startValue);
    SYSTEMTIME startDate = start;
    startDate.wHour = 0;
    startDate.wMinute = 0;
    totals[HOURS] = (endValue - startValue) / TICKS_PER_HOUR;
    totals[DAYS] = (endValue - dayStart) / TICKS_PER_DAY;
    totals[WEEKS] = totals[DAYS] / 7;
    totals[MONTHS] = CalculatorMonths(startDate, end);
    totals[YEARS] = totals[MONTHS] / 12;
}

/// Splits complete minutes into a requested leading fixed-length unit and smaller nonfractional units.
static void CalculateFixedParts(ULONGLONG minutes, int leadingUnit, ULONGLONG* parts) {
    if (leadingUnit == WEEKS) {
        parts[WEEKS] = minutes / 10080;
        minutes %= 10080;
    }
    if (leadingUnit == WEEKS || leadingUnit == DAYS) {
        parts[DAYS] = minutes / 1440;
        minutes %= 1440;
    }
    parts[HOURS] = minutes / 60;
    parts[MINUTES] = minutes % 60;
}

/// Recognizes enabled repeated decimal digits, requiring at least two digits.
static bool CalculatorRepeatedDigits(ULONGLONG value, DWORD highlights) {
    if (value < 10) {
        return false;
    }
    ULONGLONG digit = value % 10;
    if ((highlights & REPEATED_DIGIT_HIGHLIGHTS[digit]) == 0) {
        return false;
    }
    while (value > 0) {
        if (value % 10 != digit) {
            return false;
        }
        value /= 10;
    }
    return true;
}

/// Recognizes round hour counts using tens, hundreds or thousands according to the count's magnitude.
static bool CalculatorHourMilestone(ULONGLONG hours, DWORD highlights) {
    if (CalculatorRepeatedDigits(hours, highlights)) {
        return true;
    }
    if ((highlights & CALCULATOR_HIGHLIGHT_ROUND) == 0) {
        return false;
    }
    if (hours >= 1000) {
        return hours % 1000 == 0;
    }
    if (hours >= 100) {
        return hours % 100 == 0;
    }
    return hours >= 10 && hours % 10 == 0;
}

/// Finds the first hourly milestone actually attained within the selected local day.
static bool FindCalculatorHour(ULONGLONG startValue, ULONGLONG dayValue, ULONGLONG* hours,
    ULONGLONG* timeValue, DWORD highlights) {
    ULONGLONG firstHour = 0;
    if (dayValue > startValue) {
        firstHour = (dayValue - startValue + TICKS_PER_HOUR - 1) / TICKS_PER_HOUR;
    }
    ULONGLONG endValue = dayValue + TICKS_PER_DAY;
    ULONGLONG value = startValue + firstHour * TICKS_PER_HOUR;
    while (value < endValue) {
        if (CalculatorHourMilestone(firstHour, highlights)) {
            *hours = firstHour;
            *timeValue = value;
            return true;
        }
        firstHour++;
        value += TICKS_PER_HOUR;
    }
    return false;
}

/// Validates and normalizes a local date and minute without changing an invalid caller-supplied value.
bool TimeCalculator::Normalize(SYSTEMTIME* time) {
    if (time == nullptr) {
        return false;
    }
    SYSTEMTIME normalized = {};
    ULONGLONG value = 0;
    if (!ReadCalculatorTime(*time, &normalized, &value)) {
        return false;
    }
    *time = normalized;
    return true;
}

/// Calculates totals and minute-resolution decompositions, including valid month-end anniversary anchors.
bool TimeCalculator::Calculate(const SYSTEMTIME& start, const SYSTEMTIME& end,
        TimeCalculatorInterval* result) {
    if (result == nullptr) {
        return false;
    }
    SYSTEMTIME first = {};
    SYSTEMTIME last = {};
    ULONGLONG firstValue = 0;
    ULONGLONG lastValue = 0;
    if (!ReadCalculatorTime(start, &first, &firstValue)
            || !ReadCalculatorTime(end, &last, &lastValue)
            || lastValue < firstValue) {
        return false;
    }
    TimeCalculatorInterval interval = {};
    CalculateTotals(first, last, firstValue, lastValue, interval.totals);
    ULONGLONG minutes = (lastValue - firstValue) / TICKS_PER_MINUTE;
    CalculateFixedParts(minutes, HOURS, interval.parts[HOURS]);
    CalculateFixedParts(minutes, DAYS, interval.parts[DAYS]);
    CalculateFixedParts(minutes, WEEKS, interval.parts[WEEKS]);
    int months = CalculatorMonths(first, last);
    SYSTEMTIME anchor = CalculatorMonthAnchor(first, months);
    ULONGLONG anchorValue = 0;
    if (!ReadCalculatorTime(anchor, &anchor, &anchorValue)) {
        return false;
    }
    ULONGLONG remainingMinutes = (lastValue - anchorValue) / TICKS_PER_MINUTE;
    interval.parts[MONTHS][MONTHS] = months;
    CalculateFixedParts(remainingMinutes, DAYS, interval.parts[MONTHS]);
    interval.parts[YEARS][YEARS] = months / 12;
    interval.parts[YEARS][MONTHS] = months % 12;
    CalculateFixedParts(remainingMinutes, DAYS, interval.parts[YEARS]);
    *result = interval;
    return true;
}

/// Computes selected-day totals and the exact minute of the first interesting hourly anniversary.
bool TimeCalculator::CalculateDay(const SYSTEMTIME& start, const SYSTEMTIME& day,
        TimeCalculatorDay* result, DWORD highlights) {
    if (result == nullptr) {
        return false;
    }
    SYSTEMTIME first = {};
    SYSTEMTIME selected = {};
    ULONGLONG firstValue = 0;
    ULONGLONG selectedValue = 0;
    if (!ReadCalculatorTime(start, &first, &firstValue)
            || !ReadCalculatorTime(day, &selected, &selectedValue)) {
        return false;
    }
    ULONGLONG firstDay = CalculatorMidnight(first, firstValue);
    ULONGLONG selectedDay = CalculatorMidnight(selected, selectedValue);
    if (selectedDay < firstDay) {
        return false;
    }
    TimeCalculatorDay calculated = {};
    if (selectedDay > firstDay) {
        selected.wHour = 0;
        selected.wMinute = 0;
        CalculateTotals(first, selected, firstValue, selectedDay, calculated.totals);
        ULONGLONG hours = 0;
        ULONGLONG timeValue = 0;
        if (FindCalculatorHour(firstValue, selectedDay, &hours, &timeValue, highlights)) {
            if (!ReadCalculatorFields(timeValue, &calculated.hourTime)) {
                return false;
            }
            calculated.hasHourTime = true;
            calculated.totals[HOURS] = hours;
        }
    }
    *result = calculated;
    return true;
}

/// Tests the original calculator's milestone rules without sampling or retaining state between dates.
bool TimeCalculator::IsHighlightedDay(const SYSTEMTIME& start, const SYSTEMTIME& day, DWORD highlights) {
    SYSTEMTIME first = {};
    SYSTEMTIME selected = {};
    ULONGLONG firstValue = 0;
    ULONGLONG selectedValue = 0;
    if (!ReadCalculatorTime(start, &first, &firstValue)
            || !ReadCalculatorTime(day, &selected, &selectedValue)) {
        return false;
    }
    ULONGLONG firstDay = CalculatorMidnight(first, firstValue);
    ULONGLONG selectedDay = CalculatorMidnight(selected, selectedValue);
    if (selectedDay <= firstDay) {
        return selectedDay == firstDay && (highlights & CALCULATOR_HIGHLIGHT_START) != 0;
    }
    ULONGLONG days = (selectedDay - firstDay) / TICKS_PER_DAY;
    if (CalculatorRepeatedDigits(days, highlights)
        || (highlights & CALCULATOR_HIGHLIGHT_ROUND) != 0
            && (days >= 100 && days % 100 == 0 || days >= 10 && days < 100 && days % 10 == 0)) {
        return true;
    }
    ULONGLONG weeks = days / 7;
    if (days % 7 == 0 && ((highlights & CALCULATOR_HIGHLIGHT_FIRST_WEEKS) != 0 && weeks < 10
            || (highlights & CALCULATOR_HIGHLIGHT_ROUND) != 0 && weeks % 10 == 0
            || CalculatorRepeatedDigits(weeks, highlights))) {
        return true;
    }
    first.wHour = 0;
    first.wMinute = 0;
    selected.wHour = 0;
    selected.wMinute = 0;
    SYSTEMTIME previousDay = {};
    if (!ReadCalculatorFields(selectedDay - TICKS_PER_DAY, &previousDay)) {
        return false;
    }
    if ((highlights & CALCULATOR_HIGHLIGHT_ANNIVERSARIES) != 0
            && CalculatorMonths(first, selected) > CalculatorMonths(first, previousDay)) {
        return true;
    }
    ULONGLONG hours = 0;
    ULONGLONG timeValue = 0;
    return FindCalculatorHour(firstValue, selectedDay, &hours, &timeValue, highlights);
}

/// Resolves a calendar boundary at its first existing minute, retaining the earlier occurrence in a fold.
static bool CalculatorBoundary(const DYNAMIC_TIME_ZONE_INFORMATION& zone, SYSTEMTIME local,
        ULONGLONG* utc) {
    SYSTEMTIME normalized = {};
    ULONGLONG value = 0;
    if (!ReadCalculatorTime(local, &normalized, &value)) {
        return false;
    }
    ULONGLONG end = CalculatorMidnight(normalized, value) + TICKS_PER_DAY;
    while (value < end) {
        ULONGLONG candidates[2] = {};
        unsigned int count = 0;
        if (!GetTimeZoneUtcCandidates(zone, normalized, candidates, count)) {
            return false;
        }
        if (count > 0) {
            *utc = candidates[0];
            return true;
        }
        value += TICKS_PER_MINUTE;
        if (!ReadCalculatorFields(value, &normalized)) {
            return false;
        }
    }
    return false;
}

/// Counts real elapsed time in UTC and calendar totals in the starting input's display zone.
/// Resolves complete-month anniversaries by their UTC instant, including repeated local hours.
bool TimeCalculator::CalculateUtc(const SYSTEMTIME& start, const SYSTEMTIME& end,
        const DYNAMIC_TIME_ZONE_INFORMATION& zone, TimeCalculatorInterval* result) {
    SYSTEMTIME first = {};
    SYSTEMTIME last = {};
    SYSTEMTIME utc = {};
    ULONGLONG firstValue = 0;
    ULONGLONG lastValue = 0;
    if (result == nullptr
            || !ReadCalculatorTime(start, &utc, &firstValue)
            || !ReadCalculatorTime(end, &utc, &lastValue)
            || lastValue < firstValue
            || !ConvertUtcToTimeZone(zone, start, &first)
            || !ConvertUtcToTimeZone(zone, end, &last)) {
        return false;
    }
    TimeCalculatorInterval interval = {};
    ULONGLONG minutes = (lastValue - firstValue) / TICKS_PER_MINUTE;
    interval.totals[HOURS] = minutes / 60;
    CalculateFixedParts(minutes, HOURS, interval.parts[HOURS]);
    CalculateFixedParts(minutes, DAYS, interval.parts[DAYS]);
    CalculateFixedParts(minutes, WEEKS, interval.parts[WEEKS]);
    ULONGLONG firstLocal = 0;
    ULONGLONG lastLocal = 0;
    if (!ReadCalculatorTime(first, &first, &firstLocal) || !ReadCalculatorTime(last, &last, &lastLocal)) {
        return false;
    }
    LONGLONG dayDifference = static_cast<LONGLONG>(CalculatorMidnight(last, lastLocal))
        - static_cast<LONGLONG>(CalculatorMidnight(first, firstLocal));
    interval.totals[DAYS] = static_cast<ULONGLONG>(std::max(0LL, dayDifference)) / TICKS_PER_DAY;
    interval.totals[WEEKS] = interval.totals[DAYS] / 7;
    SYSTEMTIME firstDate = first;
    firstDate.wHour = 0;
    firstDate.wMinute = 0;
    interval.totals[MONTHS] = std::max(0, CalculatorMonths(firstDate, last));
    interval.totals[YEARS] = interval.totals[MONTHS] / 12;
    int months = std::max(0, CalculatorMonths(firstDate, last));
    ULONGLONG anchorValue = firstValue;
    while (months > 0) {
        SYSTEMTIME anchor = CalculatorMonthAnchor(first, months);
        if (CalculatorBoundary(zone, anchor, &anchorValue) && anchorValue <= lastValue) {
            break;
        }
        months--;
    }
    if (months == 0) {
        anchorValue = firstValue;
    }
    ULONGLONG remaining = (lastValue - anchorValue) / TICKS_PER_MINUTE;
    interval.parts[MONTHS][MONTHS] = months;
    interval.parts[YEARS][YEARS] = months / 12;
    interval.parts[YEARS][MONTHS] = months % 12;
    CalculateFixedParts(remaining, DAYS, interval.parts[MONTHS]);
    CalculateFixedParts(remaining, DAYS, interval.parts[YEARS]);
    *result = interval;
    return true;
}

/// Finds the first elapsed-hour milestone on an actual local date, including short and long DST days.
bool TimeCalculator::CalculateDayUtc(const SYSTEMTIME& start, const SYSTEMTIME& day,
        const DYNAMIC_TIME_ZONE_INFORMATION& zone, TimeCalculatorDay* result, DWORD highlights) {
    SYSTEMTIME first = {};
    SYSTEMTIME selected = day;
    if (result == nullptr || !ConvertUtcToTimeZone(zone, start, &first) || !Normalize(&selected)) {
        return false;
    }
    TimeCalculatorDay calculated = {};
    if (!CalculateDay(first, selected, &calculated, highlights)) {
        return false;
    }
    if (first.wYear == selected.wYear && first.wMonth == selected.wMonth && first.wDay == selected.wDay) {
        *result = calculated;
        return true;
    }
    selected.wHour = 0;
    selected.wMinute = 0;
    ULONGLONG dayValue = 0;
    ULONGLONG firstValue = 0;
    SYSTEMTIME utc = {};
    if (!CalculatorBoundary(zone, selected, &dayValue) || !ReadCalculatorTime(start, &utc, &firstValue)) {
        return false;
    }
    calculated.hasHourTime = false;
    calculated.totals[HOURS] = dayValue > firstValue ? (dayValue - firstValue) / TICKS_PER_HOUR : 0;
    ULONGLONG hours = 0;
    if (dayValue > firstValue) {
        hours = (dayValue - firstValue + TICKS_PER_HOUR - 1) / TICKS_PER_HOUR;
    }
    ULONGLONG value = firstValue + hours * TICKS_PER_HOUR;
    while (ReadCalculatorFields(value, &utc)) {
        SYSTEMTIME local = {};
        if (!ConvertUtcToTimeZone(zone, utc, &local)
                || local.wYear != selected.wYear
                || local.wMonth != selected.wMonth
                || local.wDay != selected.wDay) {
            break;
        }
        if (CalculatorHourMilestone(hours, highlights)) {
            calculated.hasHourTime = true;
            calculated.hourTime = utc;
            calculated.totals[HOURS] = hours;
            break;
        }
        hours++;
        value += TICKS_PER_HOUR;
    }
    *result = calculated;
    return true;
}

/// Combines local calendar anniversaries with real elapsed-hour milestones in the selected zone.
bool TimeCalculator::IsHighlightedDayUtc(const SYSTEMTIME& start, const SYSTEMTIME& day,
        const DYNAMIC_TIME_ZONE_INFORMATION& zone, DWORD highlights) {
    TimeCalculatorDay calculated = {};
    SYSTEMTIME first = {};
    SYSTEMTIME selected = day;
    if (!CalculateDayUtc(start, day, zone, &calculated, highlights)
            || !ConvertUtcToTimeZone(zone, start, &first)
            || !Normalize(&selected)) {
        return false;
    }
    if (calculated.hasHourTime) {
        return true;
    }
    ULONGLONG days = calculated.totals[DAYS];
    if (days == 0) {
        return (highlights & CALCULATOR_HIGHLIGHT_START) != 0;
    }
    if (CalculatorRepeatedDigits(days, highlights)
        || (highlights & CALCULATOR_HIGHLIGHT_ROUND) != 0
            && (days >= 100 && days % 100 == 0 || days >= 10 && days < 100 && days % 10 == 0)) {
        return true;
    }
    ULONGLONG weeks = days / 7;
    if (days % 7 == 0
        && ((highlights & CALCULATOR_HIGHLIGHT_FIRST_WEEKS) != 0 && weeks < 10
            || (highlights & CALCULATOR_HIGHLIGHT_ROUND) != 0 && weeks % 10 == 0
            || CalculatorRepeatedDigits(weeks, highlights))) {
        return true;
    }
    first.wHour = 0;
    first.wMinute = 0;
    selected.wHour = 0;
    selected.wMinute = 0;
    ULONGLONG localValue = 0;
    SYSTEMTIME previous = {};
    return (highlights & CALCULATOR_HIGHLIGHT_ANNIVERSARIES) != 0
        && ReadCalculatorTime(selected, &selected, &localValue)
        && localValue >= TICKS_PER_DAY
        && ReadCalculatorFields(localValue - TICKS_PER_DAY, &previous)
        && CalculatorMonths(first, selected) > CalculatorMonths(first, previous);
}
