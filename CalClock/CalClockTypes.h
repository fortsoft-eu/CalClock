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

#include <windows.h>
#include "PersistWindowState.h"
#include "TimeDateNotices.h"
#include <string>
#include <vector>

const int MAX_WIDGET_COUNT = 32;
const int ADDITIONAL_CLOCK_COUNT = 2;
const int WIDGET_OPACITY_MIN = 1;
const int WIDGET_OPACITY_MAX = 100;
const int ALARM_VOLUME_MIN = -10000;
const int ALARM_VOLUME_MAX = 0;
const int ALARM_VOLUME_UNITY = -1800;
const int ALARM_VOLUME_DEFAULT = ALARM_VOLUME_UNITY;

const int TIME_SIGNAL_VOLUME_MIN = 0;
const int TIME_SIGNAL_VOLUME_MAX = 357;
const int TIME_SIGNAL_VOLUME_DEFAULT = 45;
const int DIGITAL_FONT_SIZE_MIN = 1;
const int DIGITAL_FONT_SIZE_MAX = 400;
const int FULLSCREEN_FONT_SIZE_MIN = 1;
const int FULLSCREEN_FONT_SIZE_MAX = 100;
const int DIGITAL_PADDING_MAX = 200;
const int FULLSCREEN_PADDING_MAX = 400;
const int DIGITAL_BORDER_WIDTH_MAX = 200;
const unsigned int ALARM_DAYS_ALL = 0x7F;
const int SETTINGS_TAB_COUNT = 6;
const int MONITOR_COLUMN_COUNT = 8;

/// Identifies the supported widget kinds and indexes their localized names.
enum WidgetType {
    WIDGET_ANALOG,
    WIDGET_DIGITAL,
    WIDGET_CALENDAR,
    WIDGET_PANEL,
    WIDGET_FULLSCREEN,
    WIDGET_TYPE_COUNT
};

/// Selects no border, a native tool-window frame, a flat border, or a three-dimensional border.
enum DigitalBorderStyle {
    DIGITAL_BORDER_NONE,
    DIGITAL_BORDER_TOOL_WINDOW,
    DIGITAL_BORDER_SINGLE,
    DIGITAL_BORDER_3D,
    DIGITAL_BORDER_STYLE_COUNT
};

/// Selects a visible leading hour zero, an invisible zero with reserved space, or complete omission.
enum LeadingZeroMode {
    LEADING_ZERO_VISIBLE,
    LEADING_ZERO_RESERVED,
    LEADING_ZERO_OMITTED,
    LEADING_ZERO_MODE_COUNT
};

/// Selects the language's hour cycle or an explicit 12-hour or 24-hour display.
enum TimeFormatMode {
    TIME_FORMAT_CULTURE,
    TIME_FORMAT_12_HOUR,
    TIME_FORMAT_24_HOUR,
    TIME_FORMAT_COUNT
};

/// Identifies stored text-rendering modes independently of their order in the selector.
enum FontAntialiasing {
    FONT_ANTIALIAS_GDI,
    FONT_ANTIALIAS_CLEARTYPE,
    FONT_ANTIALIAS_NONE,
    FONT_ANTIALIAS_COUNT
};

/// Identifies supported application and widget languages; values are also stored in settings.
/// Append new languages before LANG_COUNT to preserve existing stored identifiers.
enum AppLanguage {
    LANG_CS,
    LANG_EN_US,
    LANG_EN_GB,
    LANG_EN_AU,
    LANG_DE,
    LANG_FR,
    LANG_ES,
    LANG_IT,
    LANG_PT,
    LANG_PL,
    LANG_SK,
    LANG_DA,
    LANG_FI,
    LANG_IS,
    LANG_NB,
    LANG_SV,
    LANG_TR,
    LANG_ET,
    LANG_GA,
    LANG_LT,
    LANG_LV,
    LANG_HU,
    LANG_MT,
    LANG_NL,
    LANG_RO,
    LANG_EL,
    LANG_BS,
    LANG_HR,
    LANG_SL,
    LANG_CNR,
    LANG_BE,
    LANG_BG,
    LANG_MK,
    LANG_SR,
    LANG_UK,
    LANG_RU,
    LANG_COUNT
};

/// Selects an automatic, regional, global, or custom NTP server list.
enum NtpPreset {
    NTP_PRESET_AUTO,
    NTP_PRESET_CESNET,
    NTP_PRESET_PTB,
    NTP_PRESET_GLOBAL,
    NTP_PRESET_CUSTOM,
    NTP_PRESET_COUNT
};

/// Indexes the available recurring Greenwich Time Signal intervals, including disabled output.
enum TimeSignalMode {
    TIME_SIGNAL_NONE,
    TIME_SIGNAL_EVERY_MINUTE,
    TIME_SIGNAL_EVERY_FIVE_MINUTES,
    TIME_SIGNAL_EVERY_TEN_MINUTES,
    TIME_SIGNAL_EVERY_QUARTER_HOUR,
    TIME_SIGNAL_EVERY_TWENTY_MINUTES,
    TIME_SIGNAL_EVERY_HALF_HOUR,
    TIME_SIGNAL_EVERY_HOUR,
    TIME_SIGNAL_COUNT
};

/// Indexes the date patterns available when copying a calendar date.
enum DateCopyFormat {
    DATE_LOCAL_SHORT,
    DATE_LOCAL_LONG,
    DATE_ISO,
    DATE_ISO_BASIC,
    DATE_ISO_SHORT_YEAR,
    DATE_BASIC_SHORT_YEAR,
    DATE_YEAR_MONTH_DAY_SLASH,
    DATE_YEAR_MONTH_DAY_DOT,
    DATE_DAY_MONTH_YEAR_DOT,
    DATE_DAY_MONTH_YEAR_DOT_PADDED,
    DATE_DAY_MONTH_YEAR_DOT_SHORT,
    DATE_DAY_MONTH_YEAR_DOT_PADDED_SHORT,
    DATE_DAY_MONTH_YEAR_SLASH,
    DATE_DAY_MONTH_YEAR_SLASH_PADDED,
    DATE_DAY_MONTH_YEAR_SLASH_PADDED_SHORT,
    DATE_DAY_MONTH_YEAR_HYPHEN,
    DATE_DAY_MONTH_YEAR_HYPHEN_PADDED,
    DATE_MONTH_DAY_YEAR_SLASH,
    DATE_MONTH_DAY_YEAR_SLASH_PADDED,
    DATE_MONTH_DAY_YEAR_SLASH_PADDED_SHORT,
    DATE_MONTH_DAY_YEAR_HYPHEN,
    DATE_MONTH_DAY_YEAR_HYPHEN_PADDED,
    DATE_DAY_SHORT_MONTH,
    DATE_DAY_MONTH,
    DATE_SHORT_MONTH_DAY,
    DATE_MONTH_DAY,
    DATE_WEEKDAY_SHORT_DAY_MONTH,
    DATE_WEEKDAY_DAY_MONTH,
    DATE_WEEKDAY_SHORT_MONTH_DAY,
    DATE_WEEKDAY_MONTH_DAY,
    DATE_RFC,
    DATE_WEEKDAY_SHORT_NUMERIC,
    DATE_WEEKDAY_NUMERIC,
    DATE_FORMAT_COUNT
};

/// Identifies every localized string independently of its source order or application language.
enum TextId {
    TXT_APP,
    TXT_SETTINGS,
    TXT_ADD,
    TXT_REMOVE,
    TXT_DUPLICATE,
    TXT_GENERAL,
    TXT_APPEARANCE,
    TXT_ALARM,
    TXT_NAME,
    TXT_TYPE,
    TXT_VISIBLE,
    TXT_TOPMOST,
    TXT_SECONDS,
    TXT_UTC,
    TXT_TIMEZONE,
    TXT_OFFSET,
    TXT_SIZE,
    TXT_OPACITY,
    TXT_FONT_SIZE,
    TXT_LEADING_ZERO,
    TXT_TRANSPARENT_BG,
    TXT_TEXT_COLOR,
    TXT_BACKGROUND_COLOR,
    TXT_WEEK_NUMBERS,
    TXT_SUNDAY_FIRST,
    TXT_ALARM_ACTIVE,
    TXT_ALARM_TIME,
    TXT_RUN_FILE,
    TXT_LOOP_AUDIO,
    TXT_BROWSE,
    TXT_LANGUAGE,
    TXT_VISUAL_STYLES,
    TXT_SAVE,
    TXT_APPLY,
    TXT_CANCEL,
    TXT_SHOW_ALL,
    TXT_HIDE_ALL,
    TXT_STOP_ALARM,
    TXT_HELP,
    TXT_ABOUT,
    TXT_EXIT,
    TXT_ANALOG,
    TXT_DIGITAL,
    TXT_CALENDAR,
    TXT_PANEL,
    TXT_INVALID_OFFSET,
    TXT_INVALID_TIME,
    TXT_DELETE_CONFIRM,
    TXT_AT_LEAST_ONE,
    TXT_CLOSE,
    TXT_LANGUAGE_NAME,
    TXT_FULLSCREEN_WIDGET_NAME,
    TXT_WIDGET_LIMIT_MESSAGE,
    TXT_WIDGET_COPY_SUFFIXES,
    TXT_XML_FILE_TYPE_LABEL,
    TXT_CSV_FILE_TYPE_LABEL,
    TXT_COMMAND_FILE_FILTER,
    TXT_LANGUAGE_LOCALE,
    TXT_WIDGET_LANGUAGE_LABEL,
    TXT_APPLICATION_LANGUAGE_LABEL,
    TXT_APPLICATION_FONT_LABEL,
    TXT_FONT_STYLE_BOLD,
    TXT_FONT_STYLE_ITALIC,
    TXT_FONT_STYLE_UNDERLINE,
    TXT_FONT_STYLE_STRIKEOUT,
    TXT_SYSTEM_TIME_ZONE_LABEL,
    TXT_SYSTEM_DEFAULT_FONT_LABEL,
    TXT_DATE_COPY_LABEL,
    TXT_DATE_FORMAT_LABEL,
    TXT_LOCAL_SHORT_LABEL,
    TXT_LOCAL_LONG_LABEL,
    TXT_ARRANGE_WIDGET_LABEL,
    TXT_SHOW_WIDGET_LABEL,
    TXT_HIDE_WIDGET_LABEL,
    TXT_UTC_TEXT_LABEL,
    TXT_MONITOR_LABEL,
    TXT_MONITOR_COLUMN_DISPLAY,
    TXT_MONITOR_COLUMN_MODEL,
    TXT_MONITOR_COLUMN_RESOLUTION,
    TXT_MONITOR_COLUMN_REFRESH_RATE,
    TXT_MONITOR_COLUMN_BIT_DEPTH,
    TXT_MONITOR_COLUMN_COLOR_FORMAT,
    TXT_MONITOR_COLUMN_COLOR_SPACE,
    TXT_MONITOR_COLUMN_POSITION,
    TXT_MONITOR_PRIMARY_LABEL,
    TXT_MONITOR_CHANNEL_DEPTH_FORMAT,
    TXT_MONITOR_PIXEL_DEPTH_FORMAT,
    TXT_BLACKOUT_MONITOR_LABEL,
    TXT_FONT_LABEL,
    TXT_FONT_BUTTON_LABEL,
    TXT_CALENDAR_FONT_LABEL,
    TXT_PANEL_TOP_FONT_LABEL,
    TXT_SHOW_TODAY_LABEL,
    TXT_PANEL_TODAY_TOOLTIP,
    TXT_PANEL_TIME_FONT_LABEL,
    TXT_PANEL_BOTTOM_FONT_LABEL,
    TXT_PANEL_TIME_NOTICES_LABEL,
    TXT_DEFAULT_FONT_LABEL,
    TXT_ALARM_TEXT_COLOR_LABEL,
    TXT_ALARM_BACKGROUND_COLOR_LABEL,
    TXT_PADDING_LABEL,
    TXT_BORDER_LABEL,
    TXT_BORDER_COLOR_LABEL,
    TXT_BORDER_WIDTH_LABEL,
    TXT_ADDITIONAL_CLOCK_NAME_FORMAT,
    TXT_ADDITIONAL_CLOCK_SHOW_FORMAT,
    TXT_TIME_FORMAT_LABEL,
    TXT_TIME_FORMAT_CULTURE,
    TXT_TIME_FORMAT_12_HOUR,
    TXT_TIME_FORMAT_24_HOUR,
    TXT_LEADING_ZERO_VISIBLE,
    TXT_LEADING_ZERO_RESERVED,
    TXT_LEADING_ZERO_OMITTED,
    TXT_TIME_SIGNAL_SOUND_LABEL,
    TXT_ALARM_VOLUME_LABEL,
    TXT_TIME_SIGNAL_VOLUME_LABEL,
    TXT_TIME_SIGNAL_SYSTEM_SOUND_LABEL,
    TXT_TIME_SIGNAL_GENERATED_SOUND_LABEL,
    TXT_TIME_SIGNAL_TAB_LABEL,
    TXT_TIME_SIGNAL_MENU_LABEL,
    TXT_TIME_SIGNAL_ENABLED_LABEL,
    TXT_TIME_SIGNAL_NONE,
    TXT_TIME_SIGNAL_EVERY_MINUTE,
    TXT_TIME_SIGNAL_EVERY_FIVE_MINUTES,
    TXT_TIME_SIGNAL_EVERY_TEN_MINUTES,
    TXT_TIME_SIGNAL_EVERY_QUARTER_HOUR,
    TXT_TIME_SIGNAL_EVERY_TWENTY_MINUTES,
    TXT_TIME_SIGNAL_EVERY_HALF_HOUR,
    TXT_TIME_SIGNAL_EVERY_HOUR,
    TXT_TIME_SIGNAL_NOTE,
    TXT_TIME_TAB_LABEL,
    TXT_TIME_SOURCE_LABEL,
    TXT_SYSTEM_TIME_LABEL,
    TXT_NTP_TIME_LABEL,
    TXT_NTP_SERVERS_LABEL,
    TXT_NTP_PRESET_FIELD_LABEL,
    TXT_NTP_PRESET_AUTO,
    TXT_NTP_PRESET_CESNET,
    TXT_NTP_PRESET_PTB,
    TXT_NTP_PRESET_GLOBAL,
    TXT_NTP_PRESET_CUSTOM,
    TXT_NTP_SYNC_LABEL,
    TXT_NTP_LOG_COLUMN_DATE,
    TXT_NTP_LOG_COLUMN_SERVER,
    TXT_NTP_LOG_COLUMN_STATUS,
    TXT_NTP_LOG_ERROR_INVALID_REPLY,
    TXT_NTP_LOG_ERROR_NAME_RESOLUTION,
    TXT_NTP_LOG_ERROR_NETWORK,
    TXT_NTP_LOG_ERROR_TIMEOUT,
    TXT_NTP_SAVE_LOG_LABEL,
    TXT_NTP_LOG_EXPORT_FAILED,
    TXT_TIME_GLOBAL_NOTE,
    TXT_NTP_STATUS_SYSTEM,
    TXT_NTP_STATUS_WAITING,
    TXT_NTP_STATUS_FAILED,
    TXT_NTP_STATUS_RETAINED,
    TXT_NTP_STATUS_SYNCHRONIZED,
    TXT_ANTIALIASING_LABEL,
    TXT_ANTIALIASING_GDI,
    TXT_ANTIALIASING_CLEARTYPE,
    TXT_ANTIALIASING_NONE,
    TXT_DEFAULT_APPEARANCE_LABEL,
    TXT_TEST_COMMAND_LABEL,
    TXT_STOP_TEST_LABEL,
    TXT_ALARM_TIME_SIGNAL_LABEL,
    TXT_REMOTE_SCRIPT_LABEL,
    TXT_REMOTE_SCRIPT_URL_LABEL,
    TXT_INVALID_REMOTE_SCRIPT_URL,
    TXT_IMPORT_SETTINGS_LABEL,
    TXT_EXPORT_SETTINGS_LABEL,
    TXT_INVALID_SETTINGS_FILE,
    TXT_SETTINGS_EXPORT_FAILED,
    TXT_XML_STORAGE_LABEL,
    TXT_START_WITH_WINDOWS_LABEL,
    TXT_MUTE_LABEL,
    TXT_MUTE_ALL_LABEL,
    TXT_MUTED_LABEL,
    TXT_HELP_TEXT,
    TXT_ABOUT_TEXT,
    TXT_ABOUT_VERSION_LABEL,
    TXT_ABOUT_PLATFORM_LABEL,
    TXT_ABOUT_WEBSITE_LABEL,
    TXT_HELP_WINDOW_TITLES,
    TXT_ABOUT_VISIT_TOOLTIP,
    TXT_ABOUT_WEBSITE_FAILED,
    TXT_ABOUT_COPY_URL_FAILED,
    TXT_ABOUT_COPY_INFORMATION_FAILED,
    TXT_ABOUT_LICENSE_UNAVAILABLE,
    TXT_OPEN_IN_BROWSER_LABEL,
    TXT_COPY_URL_LABEL,
    TXT_COPY_INFORMATION_LABEL,
    TXT_APPLICATION_TAB_LABEL,
    TXT_SNAP_TO_WORK_AREA_LABEL,
    TXT_WARN_UNSAVED_CHANGES_LABEL,
    TXT_UNSAVED_SETTINGS_PROMPT,
    TXT_COUNT
};

/// Stores a font face, dialog size, style, and character set independently of a live GDI font handle.
struct FontSelection {
    std::wstring face;
    int dialogSize = 90;
    int weight = FW_NORMAL;
    bool italic = false;
    bool underline = false;
    bool strikeOut = false;
    BYTE charSet = DEFAULT_CHARSET;
};

/// Stores one optional panel clock's enabled state, name, time zone, and analog face size.
struct AdditionalClockConfig {
    bool enabled = false;
    std::wstring name;
    std::wstring timeZoneKey;
    int size = 104;
};

/// Contains the persistent identity, layout, appearance, time, calendar, and alarm settings of one widget.
struct WidgetConfig {
    int id = 0;
    WidgetType type = WIDGET_ANALOG;
    std::wstring name;
    bool visible = false;
    bool topMost = false;
    bool showSeconds = false;
    bool showUtc = false;
    bool showUtcText = false;
    bool panelTimeNotices = true;
    AppLanguage language = LANG_CS;
    std::wstring timeZoneKey;
    std::wstring monitorDevices;
    bool blackoutOtherMonitors = true;
    LONGLONG offsetMilliseconds = 0;
    int x = 0;
    int y = 0;
    int previewX = CW_USEDEFAULT;
    int previewY = CW_USEDEFAULT;
    int size = 0;
    int opacity = 0;
    int fontSize = 0;
    int fontDialogSize = 90;
    int fontAntialiasing = FONT_ANTIALIAS_CLEARTYPE;
    int leadingZeroMode = LEADING_ZERO_VISIBLE;
    bool showAmPm = true;
    int timeFormat = TIME_FORMAT_CULTURE;
    bool transparentBackground = false;
    bool disableThemes = false;
    std::wstring fontFace;
    int fontWeight = FW_NORMAL;
    bool fontItalic = false;
    bool fontUnderline = false;
    bool fontStrikeOut = false;
    BYTE fontCharSet = DEFAULT_CHARSET;
    FontSelection panelTopFont;
    FontSelection panelTimeFont;
    FontSelection panelBottomFont;
    AdditionalClockConfig additionalClocks[ADDITIONAL_CLOCK_COUNT];
    int padding = 8;
    int borderStyle = DIGITAL_BORDER_TOOL_WINDOW;
    int borderWidth = 1;
    COLORREF borderColor = 0;
    COLORREF textColor = 0;
    COLORREF backgroundColor = 0;
    COLORREF alarmTextColor = RGB(220, 0, 0);
    COLORREF alarmBackgroundColor = RGB(255, 255, 128);
    bool showToday = true;
    bool weekNumbers = false;
    bool sundayFirst = false;
    int dateCopyFormat = DATE_LOCAL_SHORT;
    bool timeSignalEnabled = false;
    TimeSignalMode timeSignal = TIME_SIGNAL_EVERY_HOUR;
    bool soundsMuted = false;
    bool alarmEnabled = false;
    unsigned int alarmDays = ALARM_DAYS_ALL;
    bool alarmTimeSignal = false;
    int alarmHour = 0;
    int alarmMinute = 0;
    bool runCommand = false;
    bool loopAudio = false;
    int alarmVolume = ALARM_VOLUME_DEFAULT;
    std::wstring command;
    bool callRemoteScript = false;
    std::wstring remoteScriptUrl;
};

/// Captures persistent application settings, form placement, and the ordered widget configurations.
struct SettingsSnapshot {
    AppLanguage language = LANG_EN_US;
    bool themesDisabled = false;
    bool snapWidgetsToWorkArea = true;
    bool warnOnUnsavedChanges = true;
    bool generatedTimeSignal = true;
    double timeSignalVolume = TIME_SIGNAL_VOLUME_DEFAULT;
    int fontAntialiasing = FONT_ANTIALIAS_CLEARTYPE;
    std::wstring fontFace;
    int fontDialogSize = 90;
    int fontWeight = FW_NORMAL;
    bool fontItalic = false;
    bool useNtpTime = true;
    int ntpPreset = NTP_PRESET_AUTO;
    std::wstring ntpServers;
    std::wstring fileDialogDirectory;
    PersistWindowStateData settingsWindowState;
    int settingsTab = 0;
    int settingsWidgetId = -1;
    WidgetType lastAddedWidgetType = WIDGET_ANALOG;
    PersistWindowStateData helpWindowState;
    PersistWindowStateData aboutWindowState;
    std::vector<WidgetConfig> widgets;
};

/// Combines a widget's configuration with live window handles, drawing state, input tracking, and alarm resources.
struct Widget {
    WidgetConfig config;
    HWND window = nullptr;
    HWND analogChild = nullptr;
    WNDPROC analogProc = nullptr;
    HWND additionalAnalogChildren[ADDITIONAL_CLOCK_COUNT] = {};
    HWND calendarChild = nullptr;
    WNDPROC calendarProc = nullptr;
    HFONT calendarFont = nullptr;
    std::vector<HWND> fullscreenWindows;
    bool fullscreenPreview = false;
    bool dragging = false;
    POINT dragOffset = {};
    bool calendarTitlePressed = false;
    POINT calendarTitlePressScreen = {};
    LPARAM calendarTitlePressPosition = 0;
    WPARAM calendarTitlePressKeys = 0;
    bool rendered = false;
    bool alarmActive = false;
    bool flashPhase = false;
    int lastAlarmDate = -1;
    int lastAlarmMinute = -1;
    int lastObservedAlarmDate = -1;
    int lastObservedAlarmMinute = -1;
    int lastRenderKey = -1;
    int lastPanelDateKey = -1;
    std::vector<TimeDateNotice> panelNotices;
    ULONGLONG panelApplicationUtc = 0;
    bool panelNoticesPrepared = false;
    bool panelCalendarDateSupported = true;
    int lastCalendarDateKey = -1;
    HWND panelDateLink = nullptr;
    HFONT panelDateFont = nullptr;
    bool panelDateHot = false;
    HWND panelTimeZoneLink = nullptr;
    HFONT panelTimeZoneFont = nullptr;
    bool panelTimeZoneHot = false;
    HWND panelDateTooltip = nullptr;
    COLORREF analogBackground = CLR_INVALID;
    HANDLE audioStopEvent = nullptr;
    HANDLE audioMuteEvent = nullptr;
    ULONG audioGeneration = 0;
    ULONGLONG alarmStoppedTick = 0;
    bool identifyActive = false;
    bool identifyPhase = false;
    bool identifyRestoreHidden = false;
    bool identifyRestoreNotTopmost = false;
    ULONGLONG identifyEndTick = 0;
    HWND copyTooltip = nullptr;
    std::wstring copyTooltipText;
    ULONGLONG copyTooltipEndTick = 0;
    ULONGLONG lastAnalogClickTick = 0;
    POINT lastAnalogClickPoint = {};
};
