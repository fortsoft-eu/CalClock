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
 * Last modified for version 1.6.1.3
 */

#define NOMINMAX
#include "TimeDateNotices.h"
#include "CalendarLocaleScope.h"
#include <cstdarg>
#include <cwchar>

static const LONGLONG NOTICE_TICKS_PER_MINUTE = 600000000;
static const ULONGLONG NOTICE_WINDOW_TICKS = 7ULL * 24 * 60 * 60 * 10000000;
static const WORD NOTICE_MONTH_DAYS[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

typedef BOOL(WINAPI* NoticeGetTimeZoneInformationForYearProc)(USHORT, PDYNAMIC_TIME_ZONE_INFORMATION,
    LPTIME_ZONE_INFORMATION);

struct TimeDateTransition {
    SYSTEMTIME localTime = {};
    ULONGLONG utcValue = 0;
    LONG shiftMinutes = 0;
    bool daylight = false;
};

struct TimeDateRegistryRules {
    LONG bias;
    LONG standardBias;
    LONG daylightBias;
    SYSTEMTIME standardDate;
    SYSTEMTIME daylightDate;
};

/// Restores registered base rules when disabled automatic adjustment cleared the supplied transition dates.
static DYNAMIC_TIME_ZONE_INFORMATION ReadNoticeBaseRules(const DYNAMIC_TIME_ZONE_INFORMATION& zone) {
    DYNAMIC_TIME_ZONE_INFORMATION result = zone;
    if (zone.TimeZoneKeyName[0] == L'\0' || zone.StandardDate.wMonth != 0 && zone.DaylightDate.wMonth != 0) {
        return result;
    }
    std::wstring path = L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Time Zones\\";
    path += zone.TimeZoneKeyName;
    TimeDateRegistryRules rules = {};
    DWORD bytes = sizeof(rules);
    if (RegGetValueW(HKEY_LOCAL_MACHINE, path.c_str(), L"TZI", RRF_RT_REG_BINARY, nullptr, &rules, &bytes) == ERROR_SUCCESS
            && bytes == sizeof(rules)) {
        result.Bias = rules.bias;
        result.StandardBias = rules.standardBias;
        result.DaylightBias = rules.daylightBias;
        result.StandardDate = rules.standardDate;
        result.DaylightDate = rules.daylightDate;
    }
    return result;
}

/// Loads the time-zone rules for a specific year, including rules hidden by disabled automatic adjustment.
static void ReadNoticeYearRules(const DYNAMIC_TIME_ZONE_INFORMATION& zone, USHORT year, TIME_ZONE_INFORMATION* info) {
    static NoticeGetTimeZoneInformationForYearProc getForYear =
        reinterpret_cast<NoticeGetTimeZoneInformationForYearProc>(GetProcAddress(GetModuleHandleW(L"Kernel32.dll"),
            "GetTimeZoneInformationForYear"));
    DYNAMIC_TIME_ZONE_INFORMATION dynamic = zone;
    dynamic.DynamicDaylightTimeDisabled = FALSE;
    if (getForYear != nullptr && dynamic.TimeZoneKeyName[0] != L'\0' && getForYear(year, &dynamic, info)) {
        return;
    }
    *info = TIME_ZONE_INFORMATION{};
    info->Bias = zone.Bias;
    info->StandardDate = zone.StandardDate;
    info->StandardBias = zone.StandardBias;
    info->DaylightDate = zone.DaylightDate;
    info->DaylightBias = zone.DaylightBias;
}

/// Resolves an absolute or recurring Windows transition rule to its local date before the clock change.
static bool ResolveNoticeTransitionDate(const SYSTEMTIME& rule, USHORT year, SYSTEMTIME* date) {
    if (rule.wMonth == 0 || rule.wMonth > 12 || rule.wYear != 0 && rule.wYear != year) {
        return false;
    }
    *date = rule;
    date->wYear = year;
    if (rule.wYear == 0) {
        SYSTEMTIME first = {};
        first.wYear = year;
        first.wMonth = rule.wMonth;
        first.wDay = 1;
        FILETIME fileTime = {};
        if (!SystemTimeToFileTime(&first, &fileTime) || !FileTimeToSystemTime(&fileTime, &first)) {
            return false;
        }
        int days = NOTICE_MONTH_DAYS[rule.wMonth - 1];
        if (rule.wMonth == 2 && year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
            days++;
        }
        int day = 1 + (rule.wDayOfWeek - first.wDayOfWeek + 7) % 7 + (rule.wDay - 1) * 7;
        if (day > days) {
            day -= 7;
        }
        date->wDay = static_cast<WORD>(day);
    }
    FILETIME fileTime = {};
    return SystemTimeToFileTime(date, &fileTime) && FileTimeToSystemTime(&fileTime, date);
}

/// Converts one seasonal rule to its actual UTC instant while retaining the displayed pre-change local date.
static bool MakeNoticeTransition(const TIME_ZONE_INFORMATION& info, USHORT year, bool daylight, bool autoAdjustment,
        TimeDateTransition* transition) {
    const SYSTEMTIME& rule = daylight ? info.DaylightDate : info.StandardDate;
    if (!ResolveNoticeTransitionDate(rule, year, &transition->localTime)) {
        return false;
    }
    LONG beforeBias = info.Bias + (daylight ? info.StandardBias : info.DaylightBias);
    LONG afterBias = info.Bias + (daylight ? info.DaylightBias : info.StandardBias);
    FILETIME local = {};
    if (!SystemTimeToFileTime(&transition->localTime, &local)) {
        return false;
    }
    ULARGE_INTEGER value = {};
    value.LowPart = local.dwLowDateTime;
    value.HighPart = local.dwHighDateTime;
    LONG referenceBias = autoAdjustment ? beforeBias : info.Bias + info.StandardBias;
    LONGLONG instant = static_cast<LONGLONG>(value.QuadPart)
        + static_cast<LONGLONG>(referenceBias) * NOTICE_TICKS_PER_MINUTE;
    if (instant < 0) {
        return false;
    }
    transition->utcValue = static_cast<ULONGLONG>(instant);
    transition->shiftMinutes = afterBias - beforeBias;
    transition->daylight = daylight;
    return true;
}

/// Selects the next transition within seven days, otherwise the preceding transition within seven days.
static bool FindNoticeTransition(const DYNAMIC_TIME_ZONE_INFORMATION& zone, const SYSTEMTIME& utc, bool autoAdjustment,
        TimeDateTransition* transition, bool* future) {
    FILETIME fileTime = {};
    if (!SystemTimeToFileTime(&utc, &fileTime)) {
        return false;
    }
    ULARGE_INTEGER now = {};
    now.LowPart = fileTime.dwLowDateTime;
    now.HighPart = fileTime.dwHighDateTime;
    bool foundNext = false;
    bool foundPrevious = false;
    TimeDateTransition next = {};
    TimeDateTransition previous = {};
    DYNAMIC_TIME_ZONE_INFORMATION baseRules = ReadNoticeBaseRules(zone);
    for (int year = utc.wYear - 1; year <= utc.wYear + 1; year++) {
        if (year < 1601 || year > 30827) {
            continue;
        }
        TIME_ZONE_INFORMATION info = {};
        ReadNoticeYearRules(baseRules, static_cast<USHORT>(year), &info);
        if (info.StandardDate.wMonth == 0 || info.DaylightDate.wMonth == 0) {
            continue;
        }
        for (int kind = 0; kind < 2; kind++) {
            TimeDateTransition candidate = {};
            if (!MakeNoticeTransition(info, static_cast<USHORT>(year), kind != 0, autoAdjustment, &candidate)) {
                continue;
            }
            if (candidate.utcValue > now.QuadPart && candidate.utcValue - now.QuadPart <= NOTICE_WINDOW_TICKS
                    && (!foundNext || candidate.utcValue < next.utcValue)) {
                next = candidate;
                foundNext = true;
            }
            if (candidate.utcValue < now.QuadPart && now.QuadPart - candidate.utcValue <= NOTICE_WINDOW_TICKS
                    && (!foundPrevious || candidate.utcValue > previous.utcValue)) {
                previous = candidate;
                foundPrevious = true;
            }
        }
    }
    *future = foundNext;
    *transition = foundNext ? next : previous;
    return foundNext || foundPrevious;
}

/// Reads a Windows-owned localized string without copying or inventing fallback translations.
static std::wstring ReadNoticeString(HMODULE module, UINT identity) {
    const wchar_t* text = nullptr;
    int length = LoadStringW(module, identity, reinterpret_cast<LPWSTR>(&text), 0);
    return length > 0 ? std::wstring(text, length) : std::wstring();
}

/// Expands Windows resource inserts through its native message formatter.
static std::wstring FormatNoticeString(const std::wstring& format, DWORD_PTR* arguments) {
    wchar_t text[1024] = {};
    DWORD length = FormatMessageW(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ARGUMENT_ARRAY, format.c_str(), 0, 0, text,
        ARRAYSIZE(text), reinterpret_cast<va_list*>(arguments));
    return length > 0 ? std::wstring(text, length) : std::wstring();
}

/// Formats the native transition announcement and its matching automatic-adjustment sentence.
static std::wstring FormatTransitionNotice(HMODULE module, const TimeDateTransition& transition, bool future,
        const wchar_t* localeName, bool autoAdjustment) {
    wchar_t date[260] = {};
    wchar_t time[260] = {};
    bool legacyResources = ReadNoticeString(module, 184).empty();
    DWORD dateFlags = DATE_LONGDATE | (legacyResources ? 0 : DATE_AUTOLAYOUT);
    std::wstring dateText;
    if (GetDateFormatEx(localeName, dateFlags, &transition.localTime, nullptr, date, ARRAYSIZE(date), nullptr)) {
        dateText = date;
    } else {
        dateText = ReadNoticeString(module, 153);
    }
    GetTimeFormatEx(localeName, TIME_NOSECONDS, &transition.localTime, nullptr, time, ARRAYSIZE(time));
    UINT eventIdentity = transition.daylight ? 171 : 172;
    if (!future) {
        eventIdentity += 13;
    }
    DWORD_PTR eventArguments[] = { reinterpret_cast<DWORD_PTR>(dateText.c_str()), reinterpret_cast<DWORD_PTR>(time) };
    std::wstring event = FormatNoticeString(ReadNoticeString(module, eventIdentity), eventArguments);
    UINT actionIdentity = future ? 173 : 1186;
    if (autoAdjustment) {
        if (transition.shiftMinutes < 0) {
            actionIdentity = transition.shiftMinutes == -60 ? 175 : 177;
        } else if (transition.shiftMinutes > 0) {
            actionIdentity = transition.shiftMinutes == 60 ? 176 : 178;
        } else {
            actionIdentity = legacyResources ? 173 : 183;
        }
        if (actionIdentity >= 175 && actionIdentity <= 178) {
            if (legacyResources) {
                actionIdentity--;
            } else if (!future) {
                actionIdentity += 11;
            }
        }
    }
    LONGLONG shift = transition.shiftMinutes;
    DWORD_PTR actionArguments[] = { static_cast<DWORD_PTR>(shift < 0 ? -shift : shift) };
    std::wstring action = FormatNoticeString(ReadNoticeString(module, actionIdentity), actionArguments);
    return event.empty() || action.empty() ? std::wstring() : event + L" " + action;
}

/// Returns native date/time flyout notices for the selected zone and already-offset UTC instant.
std::vector<TimeDateNotice> GetTimeDateNotices(const DYNAMIC_TIME_ZONE_INFORMATION* zone, const SYSTEMTIME& utc,
        const wchar_t* localeName, bool autoAdjustment, bool calendarDateSupported, bool timeZoneRecognized) {
    std::vector<TimeDateNotice> notices;
    TimeDateTransition transition = {};
    bool future = false;
    bool hasTransition = zone != nullptr && FindNoticeTransition(*zone, utc, autoAdjustment, &transition, &future);
    if (calendarDateSupported && zone != nullptr && timeZoneRecognized && !hasTransition) {
        return notices;
    }
    CalendarLocaleScope locale(localeName);
    wchar_t path[MAX_PATH] = {};
    UINT length = GetSystemDirectoryW(path, ARRAYSIZE(path));
    if (length == 0 || length >= ARRAYSIZE(path) - ARRAYSIZE(L"\\timedate.cpl")) {
        return notices;
    }
    wcscat_s(path, L"\\timedate.cpl");
    HMODULE module = LoadLibraryExW(path, nullptr, LOAD_LIBRARY_AS_DATAFILE | LOAD_LIBRARY_AS_IMAGE_RESOURCE);
    if (module == nullptr) {
        return notices;
    }
    if (!calendarDateSupported) {
        std::wstring text = ReadNoticeString(module, 323);
        if (!text.empty()) {
            notices.push_back(TimeDateNotice{ text, TimeDateNoticeIcon::Information });
        }
    }
    if (hasTransition) {
        std::wstring text = FormatTransitionNotice(module, transition, future, localeName, autoAdjustment);
        if (!text.empty()) {
            notices.push_back(TimeDateNotice{ text, TimeDateNoticeIcon::Information });
        }
    }
    if (zone == nullptr || !timeZoneRecognized) {
        std::wstring text = ReadNoticeString(module, 324);
        if (!text.empty()) {
            notices.push_back(TimeDateNotice{ text, TimeDateNoticeIcon::Information });
        }
    }
    FreeLibrary(module);
    return notices;
}
