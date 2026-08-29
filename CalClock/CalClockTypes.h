#pragma once

#include <windows.h>
#include <string>
#include <vector>

const int WIDGET_OPACITY_MIN = 1;
const int WIDGET_OPACITY_MAX = 100;
const int DIGITAL_FONT_SIZE_MIN = 1;
const int DIGITAL_FONT_SIZE_MAX = 400;
const int FULLSCREEN_FONT_SIZE_MIN = 1;
const int FULLSCREEN_FONT_SIZE_MAX = 100;
const int DIGITAL_PADDING_MAX = 200;
const int FULLSCREEN_PADDING_MAX = 400;
const int DIGITAL_BORDER_WIDTH_MAX = 200;

enum WidgetType {
    WIDGET_ANALOG,
    WIDGET_DIGITAL,
    WIDGET_CALENDAR,
    WIDGET_PANEL,
    WIDGET_FULLSCREEN,
    WIDGET_TYPE_COUNT
};

enum DigitalBorderStyle {
    DIGITAL_BORDER_NONE,
    DIGITAL_BORDER_TOOL_WINDOW,
    DIGITAL_BORDER_SINGLE,
    DIGITAL_BORDER_3D,
    DIGITAL_BORDER_STYLE_COUNT
};

enum FontAntialiasing {
    FONT_ANTIALIAS_GDI,
    FONT_ANTIALIAS_CLEARTYPE,
    FONT_ANTIALIAS_COUNT
};

enum AppLanguage {
    LANG_CZ,
    LANG_EN,
    LANG_DE,
    LANG_FR,
    LANG_ES,
    LANG_IT,
    LANG_PL,
    LANG_SK,
    LANG_COUNT
};

enum NtpPreset {
    NTP_PRESET_AUTO,
    NTP_PRESET_CESNET,
    NTP_PRESET_PTB,
    NTP_PRESET_GLOBAL,
    NTP_PRESET_CUSTOM,
    NTP_PRESET_COUNT
};

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
    TXT_COUNT
};

struct FontSelection {
    std::wstring face;
    int dialogSize = 90;
    int weight = FW_NORMAL;
    bool italic = false;
    bool underline = false;
    bool strikeOut = false;
    BYTE charSet = DEFAULT_CHARSET;
};

struct WidgetConfig {
    int id = 0;
    WidgetType type = WIDGET_ANALOG;
    std::wstring name;
    bool visible = false;
    bool topMost = false;
    bool showSeconds = false;
    bool showUtc = false;
    bool showUtcText = false;
    AppLanguage language = LANG_CZ;
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
    bool leadingZero = false;
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
    int padding = 8;
    int borderStyle = DIGITAL_BORDER_SINGLE;
    int borderWidth = 1;
    bool showFrame = true;
    COLORREF textColor = 0;
    COLORREF backgroundColor = 0;
    COLORREF alarmTextColor = RGB(220, 0, 0);
    COLORREF alarmBackgroundColor = RGB(255, 255, 128);
    bool weekNumbers = false;
    bool sundayFirst = false;
    int dateCopyFormat = DATE_LOCAL_SHORT;
    bool alarmEnabled = false;
    int alarmHour = 0;
    int alarmMinute = 0;
    bool runCommand = false;
    bool loopAudio = false;
    std::wstring command;
    bool callRemoteScript = false;
    std::wstring remoteScriptUrl;
};

struct SettingsSnapshot {
    AppLanguage language = LANG_EN;
    bool themesDisabled = false;
    int fontAntialiasing = FONT_ANTIALIAS_CLEARTYPE;
    std::wstring fontFace;
    int fontDialogSize = 90;
    int fontWeight = FW_NORMAL;
    bool fontItalic = false;
    bool useNtpTime = true;
    int ntpPreset = NTP_PRESET_AUTO;
    std::wstring ntpServers;
    int settingsX = CW_USEDEFAULT;
    int settingsY = CW_USEDEFAULT;
    int settingsTab = 0;
    WidgetType lastAddedWidgetType = WIDGET_ANALOG;
    int helpX = CW_USEDEFAULT;
    int helpY = CW_USEDEFAULT;
    int aboutX = CW_USEDEFAULT;
    int aboutY = CW_USEDEFAULT;
    std::vector<WidgetConfig> widgets;
};

struct Widget {
    WidgetConfig config;
    HWND window = nullptr;
    HWND analogChild = nullptr;
    WNDPROC analogProc = nullptr;
    HWND calendarChild = nullptr;
    WNDPROC calendarProc = nullptr;
    HFONT calendarFont = nullptr;
    std::vector<HWND> fullscreenWindows;
    bool fullscreenPreview = false;
    bool dragging = false;
    POINT dragOffset = {};
    bool rendered = false;
    bool alarmActive = false;
    bool flashPhase = false;
    int lastAlarmDate = -1;
    int lastAlarmMinute = -1;
    int lastRenderKey = -1;
    int lastPanelDateKey = -1;
    COLORREF analogBackground = CLR_INVALID;
    HANDLE audioStopEvent = nullptr;
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

struct DisplayMonitor {
    HMONITOR handle = nullptr;
    RECT rect = {};
    std::wstring device;
    bool primary = false;
};
