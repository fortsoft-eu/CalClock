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
 * Last modified for version 1.7.2.2
 */

#pragma once

#include "TimeZoneSupport.h"
#include <string>
#include <vector>

constexpr int TIME_CALCULATOR_PAGE_COUNT = 4;
constexpr int TIME_CALCULATOR_HIGHLIGHT_COUNT = 13;
constexpr DWORD TIME_CALCULATOR_ALL_HIGHLIGHTS = 0x1FFF;
constexpr DWORD TIME_CALCULATOR_DEFAULT_HIGHLIGHTS = 0x603;
constexpr int TIME_CALCULATOR_TOTAL_COUNT = 5;
constexpr int TIME_CALCULATOR_PART_COUNT = 6;
constexpr int TIME_CALCULATOR_MAX_PRESETS = 1000;
constexpr int TIME_CALCULATOR_MAX_DESCRIPTION = 4096;

/// Selects the original calendar milestone rules independently; saved bit values remain stable.
enum TimeCalculatorHighlight : DWORD {
    CALCULATOR_HIGHLIGHT_START = 0x001,
    CALCULATOR_HIGHLIGHT_ROUND = 0x002,
    CALCULATOR_HIGHLIGHT_ONES = 0x004,
    CALCULATOR_HIGHLIGHT_TWOS = 0x008,
    CALCULATOR_HIGHLIGHT_THREES = 0x010,
    CALCULATOR_HIGHLIGHT_FOURS = 0x020,
    CALCULATOR_HIGHLIGHT_FIVES = 0x040,
    CALCULATOR_HIGHLIGHT_SEVENS = 0x080,
    CALCULATOR_HIGHLIGHT_EIGHTS = 0x100,
    CALCULATOR_HIGHLIGHT_FIRST_WEEKS = 0x200,
    CALCULATOR_HIGHLIGHT_ANNIVERSARIES = 0x400,
    CALCULATOR_HIGHLIGHT_SIXES = 0x800,
    CALCULATOR_HIGHLIGHT_NINES = 0x1000
};

/// Defines both total-row indices (Hours through Years) and component-column indices (including Minutes).
enum class TimeCalculatorUnit {
    Hours,
    Days,
    Weeks,
    Months,
    Years,
    Minutes
};

/// Holds five totals and five decompositions; parts[row][unit] uses TimeCalculatorUnit indices.
/// Each row decomposes the exact interval into its leading unit and smaller units, ending with Minutes.
struct TimeCalculatorInterval {
    ULONGLONG totals[TIME_CALCULATOR_TOTAL_COUNT] = {};
    ULONGLONG parts[TIME_CALCULATOR_TOTAL_COUNT][TIME_CALCULATOR_PART_COUNT] = {};
};

/// Holds totals at the selected day's midnight; an hourly milestone replaces Hours and sets hourTime.
/// The starting day returns zero totals and no milestone time, matching the original calculator.
struct TimeCalculatorDay {
    ULONGLONG totals[TIME_CALCULATOR_TOTAL_COUNT] = {};
    bool hasHourTime = false;
    SYSTEMTIME hourTime = {};
};

/// Stores one UTC instant, its display zone and its user-supplied description.
struct TimeCalculatorPreset {
    SYSTEMTIME time = {};
    std::wstring description;
    std::wstring zone = SYSTEM_TIME_ZONE_KEY;
};

/// Stores UTC inputs and their display zones; day is a calendar date in startZone.
/// A zero day restores Today; a zero year in another date denotes an uninitialized input.
struct TimeCalculatorState {
    SYSTEMTIME from = {};
    SYSTEMTIME to = {};
    SYSTEMTIME start = {};
    SYSTEMTIME day = {};
    std::wstring fromZone = SYSTEM_TIME_ZONE_KEY;
    std::wstring toZone = SYSTEM_TIME_ZONE_KEY;
    std::wstring startZone = SYSTEM_TIME_ZONE_KEY;
    bool fromNow = false;
    bool toNow = false;
    int tab = 0;
    DWORD highlights = TIME_CALCULATOR_DEFAULT_HIGHLIGHTS;
};

/// Calculates calendar units and elapsed UTC durations, keeping display-zone rules separate.
class TimeCalculator {

public:
    /// Validates years 1601 through 9999 and local date/time fields, then clears seconds and milliseconds.
    /// The weekday is recalculated; invalid input is left unchanged and returns false.
    static bool Normalize(SYSTEMTIME* time);

    /// Returns false for invalid dates or reversed intervals and leaves result unchanged.
    /// Hours use the exact starting minute; other totals use midnight of the starting date.
    static bool Calculate(const SYSTEMTIME& start, const SYSTEMTIME& end, TimeCalculatorInterval* result);

    /// Returns false for invalid dates or a selected date before start and leaves result unchanged.
    /// Day, week, month and year totals are calendar counts from the starting date to the selected date.
    static bool CalculateDay(const SYSTEMTIME& start, const SYSTEMTIME& day, TimeCalculatorDay* result,
        DWORD highlights = TIME_CALCULATOR_DEFAULT_HIGHLIGHTS);

    /// Identifies monthly/yearly anniversaries and significant week, day and hour counts on a given date.
    /// Repeated digits require at least two digits and are disabled by default.
    static bool IsHighlightedDay(const SYSTEMTIME& start, const SYSTEMTIME& day,
        DWORD highlights = TIME_CALCULATOR_DEFAULT_HIGHLIGHTS);

    /// Uses UTC elapsed durations and calendar totals in the supplied starting zone.
    static bool CalculateUtc(const SYSTEMTIME& start, const SYSTEMTIME& end,
        const DYNAMIC_TIME_ZONE_INFORMATION& zone, TimeCalculatorInterval* result);

    /// Resolves milestones on a local calendar date; hourTime identifies the exact UTC occurrence.
    static bool CalculateDayUtc(const SYSTEMTIME& start, const SYSTEMTIME& day,
        const DYNAMIC_TIME_ZONE_INFORMATION& zone, TimeCalculatorDay* result,
        DWORD highlights = TIME_CALCULATOR_DEFAULT_HIGHLIGHTS);

    /// Highlights local calendar anniversaries and elapsed-hour milestones using the zone's rules.
    static bool IsHighlightedDayUtc(const SYSTEMTIME& start, const SYSTEMTIME& day,
        const DYNAMIC_TIME_ZONE_INFORMATION& zone, DWORD highlights = TIME_CALCULATOR_DEFAULT_HIGHLIGHTS);
};
