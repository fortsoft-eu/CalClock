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
 * Last modified for version 1.5.0.0
 */

#define NOMINMAX
#include "TimeFormats.h"
#include "Localization.h"
#include <algorithm>

static std::wstring GetTimeLocaleValue(AppLanguage language, LCTYPE type) {
    const wchar_t* locale = LANGUAGE_LOCALES[std::clamp(static_cast<int>(language), 0, LANG_COUNT - 1)];
    int length = GetLocaleInfoEx(locale, type | LOCALE_NOUSEROVERRIDE, nullptr, 0);
    if (length <= 1) {
        return L"";
    }
    std::wstring value(length, L'\0');
    if (GetLocaleInfoEx(locale, type | LOCALE_NOUSEROVERRIDE, value.data(), length) == 0) {
        return L"";
    }
    value.resize(length - 1);
    return value;
}

bool WidgetUsesUtcTime(const WidgetConfig& config) {
    return config.showUtc || _wcsicmp(config.timeZoneKey.c_str(), L"UTC") == 0 || _wcsicmp(config.timeZoneKey.c_str(), L"UTC+00:00") == 0;
}

bool WidgetUsesTwelveHourTime(const WidgetConfig& config) {
    if (WidgetUsesUtcTime(config)) {
        return false;
    }
    if (config.timeFormat != TIME_FORMAT_CULTURE) {
        return config.timeFormat == TIME_FORMAT_12_HOUR;
    }
    std::wstring pattern = GetTimeLocaleValue(config.language, LOCALE_STIMEFORMAT);
    bool literal = false;
    for (wchar_t character : pattern) {
        if (character == L'\'') {
            literal = !literal;
        } else if (!literal && (character == L'h' || character == L'H')) {
            return character == L'h';
        }
    }
    return false;
}

static std::wstring GetWidgetTimePattern(const WidgetConfig& config) {
    std::wstring pattern = GetTimeLocaleValue(config.language, LOCALE_STIMEFORMAT);
    bool twelveHour = WidgetUsesTwelveHourTime(config);
    std::wstring result;
    bool literal = false;
    for (size_t index = 0; index < pattern.size(); index++) {
        wchar_t character = pattern[index];
        if (character == L'\'') {
            literal = !literal;
            result += character;
        } else if (!literal && (character == L'h' || character == L'H')) {
            wchar_t hour = twelveHour ? L'h' : L'H';
            result += hour;
            if (config.leadingZeroMode != LEADING_ZERO_OMITTED) {
                result += hour;
            }
            while (index + 1 < pattern.size() && pattern[index + 1] == character) {
                index++;
            }
        } else {
            result += character;
        }
    }
    return result;
}

std::wstring FormatWidgetTime(const WidgetConfig& config, const SYSTEMTIME& time) {
    std::wstring pattern = GetWidgetTimePattern(config);
    if (pattern.empty()) {
        return L"";
    }
    DWORD flags = TIME_NOTIMEMARKER;
    if (!config.showSeconds) {
        flags |= TIME_NOSECONDS;
    }
    const wchar_t* locale = LANGUAGE_LOCALES[std::clamp(static_cast<int>(config.language), 0, LANG_COUNT - 1)];
    int length = GetTimeFormatEx(locale, flags, &time, pattern.c_str(), nullptr, 0);
    if (length <= 1) {
        return L"";
    }
    std::wstring text(length, L'\0');
    if (GetTimeFormatEx(locale, flags, &time, pattern.c_str(), text.data(), length) == 0) {
        return L"";
    }
    text.resize(length - 1);
    if (config.showAmPm && WidgetUsesTwelveHourTime(config)) {
        std::wstring marker = GetTimeLocaleValue(config.language, time.wHour < 12 ? LOCALE_S1159 : LOCALE_S2359);
        if (marker.empty()) {
            marker = time.wHour < 12 ? L"AM" : L"PM";
        }
        if (config.type == WIDGET_FULLSCREEN) {
            text += L"\r\n" + marker;
        } else if (GetTimeLocaleValue(config.language, LOCALE_ITIMEMARKPOSN) == L"1") {
            text = marker + L" " + text;
        } else {
            text += L" " + marker;
        }
    }
    return text;
}
