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
#include "AlarmSchedule.h"
#include "CalClock.h"
#include "TimeZoneSupport.h"
#include <climits>

static constexpr ULONGLONG ALARM_TICKS_PER_DAY = 864000000000ULL;
static constexpr LONGLONG ALARM_TICKS_PER_MILLISECOND = 10000;

/// Converts a FILETIME value into calendar components without depending on the machine's local zone.
static bool AlarmSystemTime(ULONGLONG value, SYSTEMTIME& time) {
    ULARGE_INTEGER parts{};
    parts.QuadPart = value;
    FILETIME fileTime{ parts.LowPart, parts.HighPart };
    return FileTimeToSystemTime(&fileTime, &time) != FALSE;
}

/// Converts validated calendar components into FILETIME ticks.
static bool AlarmFileTime(const SYSTEMTIME& time, ULONGLONG& value) {
    FILETIME fileTime{};
    if (!SystemTimeToFileTime(&time, &fileTime)) {
        return false;
    }
    ULARGE_INTEGER parts{};
    parts.LowPart = fileTime.dwLowDateTime;
    parts.HighPart = fileTime.dwHighDateTime;
    value = parts.QuadPart;
    return true;
}

/// Applies or reverses the signed widget offset while keeping the timestamp in the Windows FILETIME range.
static bool ShiftAlarmTime(ULONGLONG value, LONGLONG milliseconds, bool reverse, ULONGLONG& shifted) {
    if (value > LLONG_MAX
            || milliseconds > LLONG_MAX / ALARM_TICKS_PER_MILLISECOND
            || milliseconds < LLONG_MIN / ALARM_TICKS_PER_MILLISECOND) {
        return false;
    }
    LONGLONG adjustment = milliseconds * ALARM_TICKS_PER_MILLISECOND;
    if (reverse) {
        adjustment = -adjustment;
    }
    if (adjustment > 0 && value > static_cast<ULONGLONG>(LLONG_MAX - adjustment)
            || adjustment < 0 && value < static_cast<ULONGLONG>(-adjustment)) {
        return false;
    }
    shifted = static_cast<ULONGLONG>(static_cast<LONGLONG>(value) + adjustment);
    return true;
}

/// Identifies scheduling changes independently of unrelated widget appearance and alarm actions.
bool AlarmSchedule::Matches(const WidgetConfig& config) const {
    bool requested = config.alarmEnabled && config.type != WIDGET_CALENDAR;
    return initialized
        && enabled == requested
        && utc == config.showUtc
        && days == (config.alarmDays & ALARM_DAYS_ALL)
        && hour == config.alarmHour
        && minute == config.alarmMinute
        && offsetMilliseconds == config.offsetMilliseconds
        && zoneKey == config.timeZoneKey;
}

/// Converts one application UTC instant to this alarm's displayed calendar date and time.
bool AlarmSchedule::DisplayedTime(ULONGLONG instant, SYSTEMTIME& displayed) const {
    ULONGLONG shifted = 0;
    SYSTEMTIME shiftedUtc{};
    if (!ShiftAlarmTime(instant, offsetMilliseconds, false, shifted)
            || !AlarmSystemTime(shifted, shiftedUtc)) {
        return false;
    }
    if (utc) {
        displayed = shiftedUtc;
        return true;
    }
    return ConvertUtcToTimeZone(zone, shiftedUtc, &displayed);
}

/// Finds the closest eligible occurrence after or at/before a boundary, skipping nonexistent local times.
bool AlarmSchedule::Find(ULONGLONG boundary, bool forward, ULONGLONG& instant, int& date) const {
    instant = 0;
    date = -1;
    if (!enabled || days == 0 || hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        return false;
    }
    SYSTEMTIME local{};
    ULONGLONG day = 0;
    if (!DisplayedTime(boundary, local) || !AlarmFileTime(local, day)) {
        return false;
    }
    day -= day % ALARM_TICKS_PER_DAY;
    int scheduledMinute = hour * 60 + minute;
    if (forward
            && lastDate >= 0
            && lastMinute == scheduledMinute
            && local.wYear * 10000 + local.wMonth * 100 + local.wDay < lastDate) {
        SYSTEMTIME last{};
        last.wYear = static_cast<WORD>(lastDate / 10000);
        last.wMonth = static_cast<WORD>(lastDate / 100 % 100);
        last.wDay = static_cast<WORD>(lastDate % 100);
        if (!AlarmFileTime(last, day)) {
            return false;
        }
    }
    while (true) {
        if (!AlarmSystemTime(day, local)) {
            return false;
        }
        int candidateDate = local.wYear * 10000 + local.wMonth * 100 + local.wDay;
        int weekday = (local.wDayOfWeek + 6) % 7;
        bool consumed = candidateDate <= lastDate && scheduledMinute == lastMinute;
        if (!forward && consumed) {
            return false;
        }
        if (!consumed && (days & 1U << weekday) != 0) {
            local.wHour = static_cast<WORD>(hour);
            local.wMinute = static_cast<WORD>(minute);
            ULONGLONG candidates[2]{};
            unsigned int count = 0;
            if (utc) {
                if (!AlarmFileTime(local, candidates[0])) {
                    return false;
                }
                count = 1;
            } else if (!GetTimeZoneUtcCandidates(zone, local, candidates, count)) {
                return false;
            }
            for (unsigned int index = 0; index < count; ++index) {
                unsigned int position = forward ? index : count - index - 1;
                ULONGLONG candidate = 0;
                if (ShiftAlarmTime(candidates[position], offsetMilliseconds, true, candidate)
                        && (forward ? candidate > boundary : candidate <= boundary)) {
                    instant = candidate;
                    date = candidateDate;
                    return true;
                }
            }
        }
        if (forward) {
            if (day > LLONG_MAX - ALARM_TICKS_PER_DAY) {
                return false;
            }
            day += ALARM_TICKS_PER_DAY;
        } else {
            if (day < ALARM_TICKS_PER_DAY) {
                return false;
            }
            day -= ALARM_TICKS_PER_DAY;
        }
    }
}

/// Starts a new observation interval without replaying an elapsed or currently displayed alarm minute.
void AlarmSchedule::Reset(const WidgetConfig& config, const std::vector<DYNAMIC_TIME_ZONE_INFORMATION>& zones,
        ULONGLONG now) {
    initialized = true;
    enabled = config.alarmEnabled && config.type != WIDGET_CALENDAR;
    utc = config.showUtc;
    days = config.alarmDays & ALARM_DAYS_ALL;
    hour = config.alarmHour;
    minute = config.alarmMinute;
    offsetMilliseconds = config.offsetMilliseconds;
    zoneKey = config.timeZoneKey;
    zone = DYNAMIC_TIME_ZONE_INFORMATION{};
    wcscpy_s(zone.TimeZoneKeyName, SYSTEM_TIME_ZONE_KEY);
    for (const DYNAMIC_TIME_ZONE_INFORMATION& candidate : zones) {
        if (_wcsicmp(candidate.TimeZoneKeyName, zoneKey.c_str()) == 0) {
            zone = candidate;
            break;
        }
    }
    observed = now;
    int nextDate = -1;
    Find(now, true, next, nextDate);
}

/// Reports the latest elapsed alarm once, then schedules the next unconsumed occurrence.
bool AlarmSchedule::Check(const WidgetConfig& config, const std::vector<DYNAMIC_TIME_ZONE_INFORMATION>& zones,
        ULONGLONG now) {
    if (!Matches(config) || now < observed) {
        Reset(config, zones, now);
        return false;
    }
    observed = now;
    if (next == 0 || now < next) {
        return false;
    }
    ULONGLONG elapsed = 0;
    int elapsedDate = -1;
    bool due = Find(now, false, elapsed, elapsedDate) && elapsed >= next;
    if (due) {
        lastDate = elapsedDate;
        lastMinute = hour * 60 + minute;
    }
    int nextDate = -1;
    Find(now, true, next, nextDate);
    return due;
}

/// Returns the next alarm in application UTC FILETIME ticks, or zero when no alarm is scheduled.
ULONGLONG AlarmSchedule::Next() const {
    return next;
}

/// Returns the last consumed local calendar date as YYYYMMDD, or -1 before the first alarm.
int AlarmSchedule::LastDate() const {
    return lastDate;
}

/// Returns the last consumed local minute of day, or -1 before the first alarm.
int AlarmSchedule::LastMinute() const {
    return lastMinute;
}
