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

#pragma once

#include <windows.h>
#include <string>
#include <vector>

struct WidgetConfig;

/// Tracks one widget alarm on the application UTC timeline, retaining consumed local occurrences.
class AlarmSchedule {
public:
    /// Starts a new observation interval without replaying an elapsed or currently displayed alarm minute.
    void Reset(const WidgetConfig& config, const std::vector<DYNAMIC_TIME_ZONE_INFORMATION>& zones,
        ULONGLONG now);

    /// Reports the latest elapsed alarm once, then schedules the next unconsumed occurrence.
    bool Check(const WidgetConfig& config, const std::vector<DYNAMIC_TIME_ZONE_INFORMATION>& zones,
        ULONGLONG now);

    /// Returns the next alarm in application UTC FILETIME ticks, or zero when no alarm is scheduled.
    ULONGLONG Next() const;

    /// Returns the last consumed local calendar date as YYYYMMDD, or -1 before the first alarm.
    int LastDate() const;

    /// Returns the last consumed local minute of day, or -1 before the first alarm.
    int LastMinute() const;

private:
    bool initialized = false;
    bool enabled = false;
    bool utc = false;
    unsigned int days = 0;
    int hour = 0;
    int minute = 0;
    LONGLONG offsetMilliseconds = 0;
    std::wstring zoneKey;
    DYNAMIC_TIME_ZONE_INFORMATION zone{};
    ULONGLONG observed = 0;
    ULONGLONG next = 0;
    int lastDate = -1;
    int lastMinute = -1;

    /// Identifies scheduling changes independently of unrelated widget appearance and alarm actions.
    bool Matches(const WidgetConfig& config) const;

    /// Converts one application UTC instant to this alarm's displayed calendar date and time.
    bool DisplayedTime(ULONGLONG instant, SYSTEMTIME& displayed) const;

    /// Finds the closest eligible occurrence after or at/before a boundary, skipping nonexistent local times.
    bool Find(ULONGLONG boundary, bool forward, ULONGLONG& instant, int& date) const;
};
