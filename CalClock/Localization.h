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
 * Last modified for version 1.6.1.5
 */

#pragma once

#include "CalClockTypes.h"
#include <array>
#include <initializer_list>

/// Associates one immutable translation with its named text key during compilation.
struct LocalizedText {
    TextId id;
    const wchar_t* text;
};

/// Associates a complete translation table with one existing application language identifier.
struct LocalizedLanguage {
    AppLanguage id;
    const wchar_t* texts[TXT_COUNT];
};

/// Localized monitor-detail column captions and bit-depth formats.
struct MonitorColumnText {
    const wchar_t* model;
    const wchar_t* refreshRate;
    const wchar_t* bitDepth;
    const wchar_t* colorFormat;
    const wchar_t* colorSpace;
    const wchar_t* channelDepth;
    const wchar_t* pixelDepth;
};

/// Maps widget kinds to their named translation keys.
inline constexpr TextId WIDGET_TYPE_TEXT_IDS[] = {
    TXT_ANALOG,
    TXT_DIGITAL,
    TXT_CALENDAR,
    TXT_PANEL,
    TXT_FULLSCREEN_WIDGET_NAME,
};
static_assert(ARRAYSIZE(WIDGET_TYPE_TEXT_IDS) == WIDGET_TYPE_COUNT);

inline constexpr TextId MONITOR_COLUMN_TEXT_IDS[] = {
    TXT_MONITOR_COLUMN_DISPLAY,
    TXT_MONITOR_COLUMN_MODEL,
    TXT_MONITOR_COLUMN_RESOLUTION,
    TXT_MONITOR_COLUMN_REFRESH_RATE,
    TXT_MONITOR_COLUMN_BIT_DEPTH,
    TXT_MONITOR_COLUMN_COLOR_FORMAT,
    TXT_MONITOR_COLUMN_COLOR_SPACE,
    TXT_MONITOR_COLUMN_POSITION,
};
static_assert(ARRAYSIZE(MONITOR_COLUMN_TEXT_IDS) == MONITOR_COLUMN_COUNT);

inline constexpr TextId TIME_FORMAT_TEXT_IDS[] = {
    TXT_TIME_FORMAT_CULTURE,
    TXT_TIME_FORMAT_12_HOUR,
    TXT_TIME_FORMAT_24_HOUR,
};
static_assert(ARRAYSIZE(TIME_FORMAT_TEXT_IDS) == TIME_FORMAT_COUNT);

inline constexpr TextId LEADING_ZERO_TEXT_IDS[] = {
    TXT_LEADING_ZERO_VISIBLE,
    TXT_LEADING_ZERO_RESERVED,
    TXT_LEADING_ZERO_OMITTED,
};
static_assert(ARRAYSIZE(LEADING_ZERO_TEXT_IDS) == LEADING_ZERO_MODE_COUNT);

inline constexpr TextId TIME_SIGNAL_TEXT_IDS[] = {
    TXT_TIME_SIGNAL_NONE,
    TXT_TIME_SIGNAL_EVERY_MINUTE,
    TXT_TIME_SIGNAL_EVERY_FIVE_MINUTES,
    TXT_TIME_SIGNAL_EVERY_TEN_MINUTES,
    TXT_TIME_SIGNAL_EVERY_QUARTER_HOUR,
    TXT_TIME_SIGNAL_EVERY_TWENTY_MINUTES,
    TXT_TIME_SIGNAL_EVERY_HALF_HOUR,
    TXT_TIME_SIGNAL_EVERY_HOUR,
};
static_assert(ARRAYSIZE(TIME_SIGNAL_TEXT_IDS) == TIME_SIGNAL_COUNT);

inline constexpr TextId NTP_PRESET_TEXT_IDS[] = {
    TXT_NTP_PRESET_AUTO,
    TXT_NTP_PRESET_CESNET,
    TXT_NTP_PRESET_PTB,
    TXT_NTP_PRESET_GLOBAL,
    TXT_NTP_PRESET_CUSTOM,
};
static_assert(ARRAYSIZE(NTP_PRESET_TEXT_IDS) == NTP_PRESET_COUNT);

inline constexpr TextId NTP_LOG_COLUMN_TEXT_IDS[] = {
    TXT_NTP_LOG_COLUMN_DATE,
    TXT_NTP_LOG_COLUMN_SERVER,
    TXT_NTP_LOG_COLUMN_STATUS,
};
static_assert(ARRAYSIZE(NTP_LOG_COLUMN_TEXT_IDS) == 3);

inline constexpr TextId NTP_LOG_ERROR_TEXT_IDS[] = {
    TXT_NTP_LOG_ERROR_INVALID_REPLY,
    TXT_NTP_LOG_ERROR_NAME_RESOLUTION,
    TXT_NTP_LOG_ERROR_NETWORK,
    TXT_NTP_LOG_ERROR_TIMEOUT,
};
static_assert(ARRAYSIZE(NTP_LOG_ERROR_TEXT_IDS) == 4);

inline constexpr TextId ANTIALIASING_TEXT_IDS[] = {
    TXT_ANTIALIASING_GDI,
    TXT_ANTIALIASING_CLEARTYPE,
    TXT_ANTIALIASING_NONE,
};
static_assert(ARRAYSIZE(ANTIALIASING_TEXT_IDS) == FONT_ANTIALIAS_COUNT);

/// Returns a borrowed, immutable translation identified by the existing language enum and a named text key.
const wchar_t* GetLocalizedText(AppLanguage language, TextId id);

/// Returns the supported Windows locale name, including the existing Serbian and Montenegrin fallbacks.
const wchar_t* GetLanguageLocale(AppLanguage language);

/// Returns localized monitor-detail column captions and bit-depth formats.
MonitorColumnText MonitorColumnsText(AppLanguage language);

/// Returns the localized initial text for a newly created additional clock.
std::wstring DefaultAdditionalClockName(AppLanguage language, int index);

/// Resolves unavailable Serbian and Montenegrin Windows locale names without modifying the translation catalog.
void InitializeLanguageLocales();

/// Builds one language at compile time and rejects missing, duplicate, empty, or invalid text entries.
consteval LocalizedLanguage DefineLanguage(AppLanguage language, std::initializer_list<LocalizedText> entries) {
    if (entries.size() != TXT_COUNT) {
        throw "Every language must define every TextId exactly once.";
    }
    LocalizedLanguage result = { language, {} };
    for (const LocalizedText& entry : entries) {
        int id = static_cast<int>(entry.id);
        if (id < 0 || id >= TXT_COUNT) {
            throw "Invalid translation TextId.";
        }
        if (entry.text == nullptr || entry.text[0] == L'\0') {
            throw "A translation cannot be null or empty.";
        }
        if (result.texts[id] != nullptr) {
            throw "Duplicate translation TextId.";
        }
        result.texts[id] = entry.text;
    }
    return result;
}

/// Indexes complete languages by AppLanguage at compile time, independently of their source order.
/// Rejects missing, duplicate, or invalid language identifiers before any executable can be produced.
consteval std::array<LocalizedLanguage, LANG_COUNT> DefineLocalization(
        std::initializer_list<LocalizedLanguage> languages) {
    if (languages.size() != LANG_COUNT) {
        throw "Every AppLanguage must have a complete translation table.";
    }
    std::array<LocalizedLanguage, LANG_COUNT> result = {};
    std::array<bool, LANG_COUNT> included = {};
    for (const LocalizedLanguage& language : languages) {
        int id = static_cast<int>(language.id);
        if (id < 0 || id >= LANG_COUNT) {
            throw "Invalid localization AppLanguage.";
        }
        if (included[id]) {
            throw "Duplicate localization AppLanguage.";
        }
        for (const wchar_t* text : language.texts) {
            if (text == nullptr || text[0] == L'\0') {
                throw "Every language must contain a nonempty translation for every TextId.";
            }
        }
        result[id] = language;
        included[id] = true;
    }
    return result;
}
