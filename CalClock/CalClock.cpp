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
 * Last modified for version 1.5.1.0
 */

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "resource.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <winver.h>
#include "AlarmActions.h"
#include "AnalogClockHost.h"
#include "CalendarLocaleScope.h"
#include "CalClockTypes.h"
#include "DateFormats.h"
#include "Localization.h"
#include "NtpClient.h"
#include "SettingsStorage.h"
#include "TimeFormats.h"
#include "TimeSignal.h"
#include "TimeZoneSupport.h"
#include "WidgetLayout.h"
#include "WindowRedrawScope.h"
#include <windowsx.h>
#include <algorithm>
#include <atomic>
#include <climits>
#include <cmath>
#include <commctrl.h>
#include <commdlg.h>
#include <dlgs.h>
#include <cstring>
#include <cwctype>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <memory>
#include <shellapi.h>
#include <string>
#include <utility>
#include <uxtheme.h>
#include <vssym32.h>
#include <vector>

#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Comdlg32.lib")
#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "UxTheme.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Version.lib")

/// Function pointer types
typedef LCID(WINAPI* GetUserDefaultLcidProc)();
typedef int(WINAPI* GetLocaleInfoWProc)(LCID locale, LCTYPE type, LPWSTR data, int characters);
typedef int(WINAPI* GetCalendarInfoWProc)(LCID locale, CALID calendar, CALTYPE type, LPWSTR data,
    int characters, LPDWORD value);
typedef int(WINAPI* GetCalendarInfoExProc)(LPCWSTR localeName, CALID calendar, LPCWSTR reserved,
    CALTYPE type, LPWSTR data, int characters, LPDWORD value);
typedef int(WINAPI* GetCalendarDateFormatProc)(CALID calendar, DWORD flags, const void* calendarDate,
    LPCWSTR format, LPWSTR data, int characters);
typedef BOOL(WINAPI* ConvertCalDateTimeToSystemTimeProc)(const void* calendarDate, SYSTEMTIME* systemTime);
typedef HRESULT(WINAPI* D2D1CreateFactoryProc)(D2D1_FACTORY_TYPE factoryType, REFIID interfaceId,
    const D2D1_FACTORY_OPTIONS* factoryOptions, void** factory);
typedef HRESULT(WINAPI* DWriteCreateFactoryProc)(DWRITE_FACTORY_TYPE factoryType, REFIID interfaceId,
    IUnknown** factory);

/// Window layout and font dialog types
/// Selects whether the shared font dialog exposes face and style only or also permits size changes.
enum FontDialogMode {
    FONT_DIALOG_FACE_AND_STYLE,
    FONT_DIALOG_WITH_SIZE
};

/// Orders foreground controls above extended checkbox hit areas and background text labels.
enum SettingsControlLayer {
    SETTINGS_CONTROL_FOREGROUND,
    SETTINGS_CONTROL_CHECKBOX,
    SETTINGS_CONTROL_LABEL
};

/// Pairs a child window with its rectangle for batched settings layout updates.
struct PositionedControl {
    HWND window;
    RECT rect;
};

/// Records a control's requested visibility for applying settings-page changes in a consistent order.
struct ControlVisibility {
    HWND control;
    bool visible;
};

/// Records a control's requested enabled state for a settings availability update.
struct ControlState {
    HWND control;
    bool enabled;
};

/// Groups regular and alarm widget sources sharing one system-time target, including canceled alarm contributors.
struct TimeSignalSourceGroup {
    ULONGLONG target = 0;
    std::vector<int> regularWidgetIds;
    std::vector<int> alarmWidgetIds;
    std::vector<int> cancelledAlarmWidgetIds;
};

/// Identifies a widget's proposed system-time target and whether it comes from a recurring signal or alarm.
struct TimeSignalCandidate {
    ULONGLONG target;
    bool regular;
    int widgetId;
};

/// Pairs a live widget with a planned screen rectangle before applying an arrangement.
struct PendingWidgetPlacement {
    Widget* widget;
    RECT rect;
};

/// Groups widgets by monitor for independent work-area arrangement.
struct MonitorGroup {
    HMONITOR monitor;
    std::vector<Widget*> items;
};

/// Caches a native calendar's measured size together with the locale, font, theme, and style options that affect it.
struct CalendarSizeEntry {
    AppLanguage language;
    bool weekNumbers;
    bool borderless;
    bool showToday;
    bool themesDisabled;
    int fontAntialiasing;
    int fontWeight;
    bool fontItalic;
    BYTE fontCharSet;
    std::wstring fontFace;
    SIZE size;
};

/// Contains the panel's client size and rectangles for its calendar, clock faces, captions, times, days, and footer.
struct PanelLayout {
    SIZE clientSize = {};
    RECT calendar = {};
    RECT clocks[ADDITIONAL_CLOCK_COUNT + 1] = {};
    RECT names[ADDITIONAL_CLOCK_COUNT] = {};
    RECT times[ADDITIONAL_CLOCK_COUNT + 1] = {};
    RECT days[ADDITIONAL_CLOCK_COUNT + 1] = {};
    RECT footer = {};
};

/// Stores initial About or Help control rectangles for later resizing and wrapped-label layout.
struct InformationWindowLayout {
    RECT text = {};
    RECT close = {};
    RECT product = {};
    RECT website = {};
    RECT link = {};
    bool initialized = false;
};

/// Window classes and product constants
const wchar_t CLASS_NAME[] = L"CalClockMultiWidgetWindow";
const wchar_t BLACKOUT_CLASS_NAME[] = L"CalClockBlackoutWindow";
const wchar_t CONTROLLER_TITLE[] = L"CalClockMessageController";
const wchar_t ABOUT_WEBSITE_URL[] = L"https://fortsoft.cz/calclock/";
const wchar_t WIDGET_CLIPBOARD_FORMAT[] = L"FortSoft.CalClock.Widgets.XML.v1";
const wchar_t SETTINGS_COMBO_HEIGHT_PROPERTY[] = L"CalClock.SettingsComboHeight";

/// Window messages, timers and subclass identifiers
const UINT WM_TRAYICON = WM_APP + 1;
const UINT WM_SHOW_EXISTING = WM_APP + 2;
const UINT WM_NTP_RESULT = WM_APP + 3;
const UINT WM_AUDIO_FINISHED = WM_APP + 4;
const UINT WM_SETTINGS_AUDIO_FINISHED = WM_APP + 5;
const UINT WM_REFRESH_DISPLAYS = WM_APP + 6;
const UINT WM_TIME_SIGNAL_FINISHED = WM_APP + 8;
const UINT_PTR TIMER_REFRESH = 1;
static const UINT_PTR TIMER_EDIT_CLICKS = 0xCC01;
static const ULONGLONG FULLSCREEN_CURSOR_IDLE_DELAY = 3000;
const UINT_PTR ABOUT_CONTROL_SUBCLASS_ID = 0xCC03;
const UINT_PTR COMBO_BOX_DROPDOWN_SUBCLASS_ID = 0xCC04;
const UINT_PTR SETTINGS_CONTROL_SUBCLASS_ID = 0xCC05;
const UINT_PTR ABOUT_LICENSE_SUBCLASS_ID = 0xCC06;

/// Layout, appearance and alarm constants
const int ABOUT_WINDOW_HEIGHT = 528;
const int ABOUT_WINDOW_WIDTH = 550;
const int ALARM_DAY_COUNT = 7;
const COLORREF IDENTIFY_COLOR = RGB(80, 190, 255);
static const int PANEL_CALENDAR_OFFSET_Y = -4;
static const int PANEL_SIDE_PADDING = 12;
const int SETTINGS_HORIZONTAL_SCALE_DENOMINATOR = 5;
const int SETTINGS_HORIZONTAL_SCALE_NUMERATOR = 6;
const int SETTINGS_PAGE_CONTENT_RIGHT = 418;
const int SETTINGS_WIDGET_LIST_RIGHT = 312;
const int SETTINGS_WINDOW_HEIGHT = 521;
const int SETTINGS_WINDOW_WIDTH = 778;
const int TIME_SIGNAL_VOLUME_SLIDER_MIN = 0;
const int TIME_SIGNAL_VOLUME_SLIDER_MAX = 2000;
const int TIME_SIGNAL_VOLUME_SLIDER_MIDDLE = 1000;
const double TIME_SIGNAL_VOLUME_SLIDER_MIN_DB = -60.0;
const double TIME_SIGNAL_VOLUME_SLIDER_MIDDLE_DB = -18.0;
static const int WORK_AREA_SNAP_DISTANCE = 5;

/// Widget panel control identifiers
const int ID_PANEL_BOTTOM_FONT = 3075;
const int ID_PANEL_DATE_LINK = 115;
const int ID_PANEL_TIME_FONT = 3074;
const int ID_PANEL_TIME_ZONE_LINK = 116;
const int ID_PANEL_TOP_FONT = 3073;

/// Menu command identifiers
const int ID_MENU_ABOUT = 1023;
const int ID_MENU_ABOUT_COPY_INFORMATION = 1102;
const int ID_MENU_ABOUT_COPY_URL = 1101;
const int ID_MENU_ABOUT_OPEN_LINK = 1100;
const int ID_MENU_ALARM_ENABLED = 1006;
const int ID_MENU_ARRANGE_WIDGETS = 1050;
const int ID_MENU_DATE_FORMAT_BASE = 1060;
const int ID_MENU_EXIT = 1024;
const int ID_MENU_HELP = 1022;
const int ID_MENU_HIDE_ALL = 1021;
const int ID_MENU_SHOW_TODAY = 1014;
const int ID_MENU_MUTE = 1008;
const int ID_MENU_SECONDS = 1004;
const int ID_MENU_SETTINGS = 1001;
const int ID_MENU_SHOW_ALL = 1020;
const int ID_MENU_SIZE_104 = 1010;
const int ID_MENU_SIZE_198 = 1013;
const int ID_MENU_STOP_ALARM = 1005;
const int ID_MENU_TIME_SIGNAL_ENABLED = 1007;
const int ID_MENU_TODAY = 1009;
const int ID_MENU_TOPMOST = 1003;
const int ID_MENU_VISIBLE = 1002;
const int ID_MENU_WIDGET_BASE = 2000;

/// Information window control identifiers
const int ID_INFO_CLOSE = 3050;
const int ID_INFO_ICON = 3200;
const int ID_INFO_LINK = 3203;
const int ID_INFO_PRODUCT = 3201;
const int ID_INFO_TEXT = 3051;
const int ID_INFO_WEBSITE = 3202;

/// Settings control identifiers
const int ID_ADD = 3003;
const int ID_ADD_TYPE = 3002;
const int ID_ADDITIONAL_ENABLED_BASE = 3110;
const int ID_ADDITIONAL_NAME_BASE = 3120;
const int ID_ADDITIONAL_SIZE_BASE = 3140;
const int ID_ADDITIONAL_TIMEZONE_BASE = 3130;
const int ID_ALARM_BACKGROUND_COLOR = 3054;
const int ID_ALARM_DAY_BASE = 3082;
const int ID_ALARM_ENABLED = 3030;
const int ID_ALARM_TEXT_COLOR = 3053;
const int ID_ALARM_TIME = 3031;
const int ID_ALARM_TIME_SIGNAL = 3079;
const int ID_ALARM_VOLUME = 3097;
const int ID_APP_ANTIALIAS = 3048;
const int ID_APP_FONT = 3049;
const int ID_APP_FONT_DEFAULT = 3076;
const int ID_APPLY = 3043;
const int ID_BACKGROUND_COLOR = 3026;
const int ID_BLACKOUT_MONITORS = 3070;
const int ID_BORDER = 3056;
const int ID_BORDER_COLOR = 3090;
const int ID_BORDER_WIDTH = 3059;
const int ID_BROWSE = 3034;
const int ID_CANCEL = IDCANCEL;
const int ID_COMMAND = 3033;
const int ID_DATE_FORMAT = 3029;
const int ID_DEFAULT_APPEARANCE = 3058;
const int ID_DUPLICATE = 3005;
const int ID_EXPORT_SETTINGS = 3046;
const int ID_FONT = 3052;
const int ID_FONT_SIZE = 3022;
const int ID_IMPORT_SETTINGS = 3045;
const int ID_SHOW_TODAY = 3092;
const int ID_LANGUAGE = 3040;
const int ID_LEADING_ZERO = 3023;
const int ID_LIST_WIDGETS = 3001;
const int ID_LOOP_AUDIO = 3035;
const int ID_MONITOR_LIST = 3071;
const int ID_NAME = 3010;
const int ID_NTP_PRESET = 3063;
const int ID_NTP_SERVERS = 3061;
const int ID_NTP_SYNC = 3062;
const int ID_OFFSET = 3017;
const int ID_OPACITY = 3021;
const int ID_PADDING = 3055;
const int ID_REMOTE_SCRIPT = 3037;
const int ID_REMOTE_SCRIPT_URL = 3038;
const int ID_REMOVE = 3004;
const int ID_RUN_COMMAND = 3032;
const int ID_SAVE = IDOK;
const int ID_SECONDS = 3014;
const int ID_SHOW_AM_PM = 3100;
const int ID_SIZE = 3020;
const int ID_SNAP_TO_WORK_AREA = 3091;
const int ID_SOUNDS_ENABLED = 3089;
const int ID_START_WITH_WINDOWS = 3081;
const int ID_SUNDAY_FIRST = 3028;
const int ID_TABS = 3006;
const int ID_TEST_COMMAND = 3036;
const int ID_TEXT_COLOR = 3025;
const int ID_TIME_SIGNAL = 3078;
const int ID_TIME_SIGNAL_NOTE = 3080;
const int ID_TIME_SIGNAL_SOUND = 3093;
const int ID_TIME_SIGNAL_VOLUME = 3094;
const int ID_TIME_SIGNAL_TEST = 3095;
const int ID_TIME_SOURCE = 3060;
const int ID_TIME_FORMAT = 3101;
const int ID_TIMEZONE = 3016;
const int ID_TOPMOST = 3013;
const int ID_TRANSPARENT_BG = 3024;
const int ID_TYPE = 3011;
const int ID_USE_XML_SETTINGS = 3047;
const int ID_UTC = 3015;
const int ID_UTC_TEXT = 3019;
const int ID_VISIBLE = 3012;
const int ID_VISUAL_STYLES = 3041;
const int ID_WEEK_NUMBERS = 3027;
const int ID_WIDGET_ANTIALIAS = 3072;
const int ID_WIDGET_DISABLE_THEMES = 3057;
const int ID_WIDGET_LANGUAGE = 3018;

/// Language order
static const AppLanguage LANGUAGE_DISPLAY_ORDER[LANG_COUNT] = {
    LANG_CZ,
    LANG_EN,
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
    LANG_NO,
    LANG_SV,
    LANG_TR
};

static_assert(ID_MENU_ARRANGE_WIDGETS < ID_MENU_DATE_FORMAT_BASE
    || ID_MENU_ARRANGE_WIDGETS >= ID_MENU_DATE_FORMAT_BASE + DATE_FORMAT_COUNT);

/// Application instance
HINSTANCE hInstance = nullptr;

/// Thread, mutex and event handles
HANDLE hNtpThread = nullptr;
HANDLE hSingleInstanceMutex = nullptr;
HANDLE settingsPreviewMuteEvent = nullptr;
HANDLE settingsPreviewStopEvent = nullptr;

/// Loaded modules
HMODULE d2dModule = nullptr;
HMODULE dwriteModule = nullptr;

/// Fonts
HFONT hUiFont = nullptr;
HFONT hAboutFont = nullptr;

/// Windows and tooltips
HWND hController = nullptr;
HWND hSettings = nullptr;
HWND hHelp = nullptr;
HWND hAbout = nullptr;
HWND hAboutTooltip = nullptr;

/// Settings pages and widget list
HWND hWidgetList = nullptr;
HWND hAddType = nullptr;
HWND hTabs = nullptr;
HWND hGeneralPage = nullptr;
HWND hAppearancePage = nullptr;
HWND hAlarmPage = nullptr;
HWND hTimeSignalPage = nullptr;
HWND hTimePage = nullptr;
HWND hApplicationPage = nullptr;

/// General widget controls
HWND hNameEdit = nullptr;
HWND hTypeCombo = nullptr;
HWND hVisibleCheck = nullptr;
HWND hTopmostCheck = nullptr;
HWND hSecondsCheck = nullptr;
HWND hUtcCheck = nullptr;
HWND hUtcTextCheck = nullptr;
HWND hAdditionalEnabledChecks[ADDITIONAL_CLOCK_COUNT] = {};
HWND hAdditionalNameLabels[ADDITIONAL_CLOCK_COUNT] = {};
HWND hAdditionalNameEdits[ADDITIONAL_CLOCK_COUNT] = {};
HWND hAdditionalTimeZoneLabels[ADDITIONAL_CLOCK_COUNT] = {};
HWND hAdditionalTimeZoneCombos[ADDITIONAL_CLOCK_COUNT] = {};
HWND hAdditionalSizeCombos[ADDITIONAL_CLOCK_COUNT] = {};
HWND hShowAmPmCheck = nullptr;
HWND hTimeFormatLabel = nullptr;
HWND hTimeFormatCombo = nullptr;
HWND hTimeZoneLabel = nullptr;
HWND hTimeZoneCombo = nullptr;
HWND hMonitorLabel = nullptr;
HWND hMonitorList = nullptr;
HWND hBlackoutMonitorsCheck = nullptr;
HWND hOffsetEdit = nullptr;
HWND hWidgetLanguageCombo = nullptr;
HWND hSoundsMutedCheck = nullptr;

/// Appearance controls
HWND hAlarmBackgroundColorButton = nullptr;
HWND hAlarmTextColorButton = nullptr;
HWND hBackgroundColorButton = nullptr;
HWND hBorderColorButton = nullptr;
HWND hBorderLabel = nullptr;
HWND hBorderTrackBar = nullptr;
HWND hBorderWidthLabel = nullptr;
HWND hBorderWidthTrackBar = nullptr;
HWND hBorderWidthValue = nullptr;
HWND hDateFormatCombo = nullptr;
HWND hDateFormatLabel = nullptr;
HWND hDefaultAppearanceButton = nullptr;
HWND hFontButton = nullptr;
HWND hFontDescription = nullptr;
HWND hFontSizeLabel = nullptr;
HWND hFontSizeTrackBar = nullptr;
HWND hFontSizeValue = nullptr;
HWND hLeadingZeroLabel = nullptr;
HWND hLeadingZeroCombo = nullptr;
HWND hOpacityLabel = nullptr;
HWND hOpacityTrackBar = nullptr;
HWND hOpacityValue = nullptr;
HWND hPaddingLabel = nullptr;
HWND hPaddingTrackBar = nullptr;
HWND hPaddingValue = nullptr;
HWND hPanelBottomFontButton = nullptr;
HWND hPanelTimeFontButton = nullptr;
HWND hPanelTopFontButton = nullptr;
HWND hSizeCombo = nullptr;
HWND hSizeLabel = nullptr;
HWND hShowTodayCheck = nullptr;
HWND hSundayFirstCheck = nullptr;
HWND hTextColorButton = nullptr;
HWND hTransparentBackgroundCheck = nullptr;
HWND hWeekNumbersCheck = nullptr;
HWND hWidgetAntialiasCombo = nullptr;
HWND hWidgetAntialiasLabel = nullptr;
HWND hWidgetDisableThemesCheck = nullptr;

/// Alarm and time signal controls
HWND hAlarmDayChecks[ALARM_DAY_COUNT] = {};
HWND hAlarmEnabledCheck = nullptr;
HWND hAlarmTimeEdit = nullptr;
HWND hAlarmTimeSignalCheck = nullptr;
HWND hBrowseButton = nullptr;
HWND hCommandEdit = nullptr;
HWND hLoopAudioCheck = nullptr;
HWND hAlarmVolumeLabel = nullptr;
HWND hAlarmVolumeTrackBar = nullptr;
HWND hAlarmVolumeValue = nullptr;
HWND hRemoteScriptEdit = nullptr;
HWND hRemoteScriptCheck = nullptr;
HWND hRemoteScriptLabel = nullptr;
HWND hRunCommandCheck = nullptr;
HWND hTestCommandButton = nullptr;
HWND hTimeSignalCombo = nullptr;

/// Time source controls
HWND hNtpPresetCombo = nullptr;
HWND hNtpPresetLabel = nullptr;
HWND hNtpServersEdit = nullptr;
HWND hNtpServersLabel = nullptr;
HWND hNtpStatus = nullptr;
HWND hNtpSyncButton = nullptr;
HWND hTimeSourceCombo = nullptr;

/// Application settings controls
HWND hAppAntialiasCombo = nullptr;
HWND hAppFontButton = nullptr;
HWND hAppFontDefaultButton = nullptr;
HWND hAppFontLabel = nullptr;
HWND hDisableThemesCheck = nullptr;
HWND hLanguageCombo = nullptr;
HWND hSnapToWorkAreaCheck = nullptr;
HWND hTimeSignalSoundCombo = nullptr;
HWND hTimeSignalTestButton = nullptr;
HWND hTimeSignalVolumeLabel = nullptr;
HWND hTimeSignalVolumeTrackBar = nullptr;
HWND hTimeSignalVolumeValue = nullptr;
HWND hStartWithWindowsCheck = nullptr;
HWND hUseXmlSettingsCheck = nullptr;

/// Mouse interaction windows
static HWND hFullscreenCursorWindow = nullptr;
static HWND lastClickedEdit = nullptr;

/// Graphics factories
ID2D1Factory* d2dFactory = nullptr;
IDWriteFactory* dwriteFactory = nullptr;

/// Resolved locale functions
GetUserDefaultLcidProc originalGetUserDefaultLcid = nullptr;
GetLocaleInfoWProc originalGetLocaleInfoW = nullptr;
GetCalendarInfoWProc originalGetCalendarInfoW = nullptr;
GetCalendarInfoExProc originalGetCalendarInfoEx = nullptr;
GetCalendarDateFormatProc originalGetCalendarDateFormat = nullptr;
ConvertCalDateTimeToSystemTimeProc convertCalDateTimeToSystemTime = nullptr;

/// Notification area data
NOTIFYICONDATAW trayIcon = {};

/// Information window layouts
static InformationWindowLayout helpWindowLayout;
static InformationWindowLayout aboutWindowLayout;

/// Mouse interaction positions
static POINT fullscreenCursorPosition = {};
static POINT lastEditClickPoint = {};

/// Language and widget type
AppLanguage appLanguage = LANG_EN;
WidgetType lastAddedWidgetType = WIDGET_ANALOG;

/// State flags
bool appFontItalic = false;
bool displayRefreshPending = false;
static bool fullscreenCursorHidden = false;
bool ntpHasSynchronized = false;
bool ntpLastQueryFailed = false;
bool settingsAppearancePreviewActive = false;
bool settingsAppFontItalic = false;
bool settingsApplicationFontPreviewActive = false;
bool settingsCommandTestActive = false;
bool settingsVisualPreviewActive = false;
bool snapWidgetsToWorkArea = true;
bool generatedTimeSignal = true;
bool timeSignalVolumeDragging = false;
bool settingsTimeSignalTestActive = false;
bool startWithWindows = false;
bool storageUsesXml = false;
bool themesDisabled = false;
bool trayUsesVersion4 = false;
bool updatingNtpPresetControls = false;
bool updatingSettingsControls = false;
bool useNtpTime = true;
bool winsockReady = false;

/// Numeric settings and positions
int aboutX = CW_USEDEFAULT;
int aboutY = CW_USEDEFAULT;
int appFontAntialiasing = FONT_ANTIALIAS_CLEARTYPE;
int appFontDialogSize = 90;
int appFontWeight = FW_NORMAL;
int helpX = CW_USEDEFAULT;
int helpY = CW_USEDEFAULT;
int nextWidgetId = 1;
int ntpPreset = NTP_PRESET_AUTO;
int selectedDraftIndex = 0;
int settingsAppFontDialogSize = 90;
int settingsAppFontWeight = FW_NORMAL;
int settingsContentHeight = 0;
int settingsContentWidth = 0;
int settingsTab = 0;
int settingsVisualPreviewWidgetId = -1;
int settingsX = CW_USEDEFAULT;
int settingsY = CW_USEDEFAULT;
double timeSignalVolume = TIME_SIGNAL_VOLUME_DEFAULT;
std::shared_ptr<std::atomic<int>> settingsPreviewVolume;
static int editClickCount = 0;

/// Message and generation identifiers
ULONG settingsPreviewGeneration = 0;
UINT taskbarCreatedMessage = 0;

/// Timing state
LONGLONG currentTimeSignalOffset = 0;
ULONGLONG lastNtpAttemptTick = 0;
ULONGLONG nextNtpAttemptTick = 0;
static ULONGLONG fullscreenCursorActivityTick = 0;

/// Thread-safe NTP state
std::atomic<ULONG> ntpGeneration = 0;
std::atomic<LONGLONG> ntpOffset100Nanoseconds = 0;
std::atomic<bool> ntpQueryRunning = false;
std::atomic<bool> ntpStopRequested = false;
std::atomic<bool> ntpTimeValid = false;

/// Font names and NTP servers
std::wstring appFontFace;
std::wstring ntpActiveServer;
std::wstring ntpServers;
std::wstring settingsAppFontFace;

/// Widgets
std::vector<std::unique_ptr<Widget>> widgets;

/// Widget configuration drafts
std::vector<WidgetConfig> settingsAppearanceOriginals;
std::vector<WidgetConfig> settingsDraft;
std::vector<WidgetConfig> settingsAppliedWidgets;

/// Widget identifiers
std::vector<TimeSignalSourceGroup> currentTimeSignalSources;
std::vector<int> lastHiddenWidgetIds;
std::vector<int> lastMutedWidgetIds;
std::vector<int> settingsAppearancePreviewIds;
std::vector<int> disabledArrangementCommands;

/// Monitors and time zones
std::vector<DisplayMonitor> displayMonitors;
std::vector<DYNAMIC_TIME_ZONE_INFORMATION> timeZones;

/// Window and control collections
std::vector<HWND> alarmControls;
std::vector<HWND> appearanceControls;
std::vector<HWND> applicationControls;
std::vector<HWND> blackoutWindows;
std::vector<HWND> generalControls;
std::vector<HWND> timeControls;
std::vector<HWND> timeSignalControls;

/// Forward declarations

/// Dispatches controller, widget, settings-page, and information-window messages.
/// Coordinates painting, input, timers, background-worker results, settings actions, and orderly application shutdown.
static LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

/// Integrates the primary native clock with widget dragging, face-only second-hand toggling, context menus, and
/// identification painting.
static LRESULT CALLBACK AnalogChildProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

/// Handles an additional clock's size menu, panel dragging, background painting, and theme updates without enabling a
/// second hand.
static LRESULT CALLBACK AdditionalAnalogChildProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
    UINT_PTR subclassId, DWORD_PTR referenceData);

/// Preserves native calendar navigation while distinguishing title clicks from widget drags.
/// Applies the widget locale to native processing and handles context menus and identification feedback.
static LRESULT CALLBACK CalendarChildProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

/// Handles panel-link pointer feedback, focus on clicks, and hover highlighting.
/// Treats double-clicks as button presses and removes the subclass on destruction.
static LRESULT CALLBACK PanelLinkButtonSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
    UINT_PTR subclassId, DWORD_PTR referenceData);

/// Adds Ctrl+A and triple-click line selection while preserving normal edit and dialog behavior.
/// Clears click tracking on timeout, focus changes, other mouse buttons, and destruction.
static LRESULT CALLBACK EditSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
    UINT_PTR subclassId, DWORD_PTR referenceData);

/// Handles list selection and widget keyboard commands, including copy, paste, removal, and duplication.
/// On associated buttons, transfers focus to the widget list before handling the shortcut.
static LRESULT CALLBACK WidgetListSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
    UINT_PTR subclassId, DWORD_PTR referenceData);

/// Tracks mouse capture on the volume slider to control preview playback and stops it during subclass destruction.
static LRESULT CALLBACK TimeSignalVolumeSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
    UINT_PTR subclassId, DWORD_PTR referenceData);

/// Serializes selected widgets to the application's registered clipboard format, transferring memory ownership only on
/// success.
static void CopySelectedWidgetsToClipboard();

/// Reads and validates the application's bounded clipboard payload, validates pending edits, and appends widget copies.
static void PasteWidgetsFromClipboard();

/// Updates a visible widget through the rendering path appropriate to its type, resizing only when needed.
static void RenderWidget(Widget* widget);

/// Captures current settings and saves them to the selected XML or registry backend.
/// Removes registry settings after a successful switch to XML storage.
static void SaveAllSettings();

/// Captures the form's screen position, using and translating its normal placement when minimized.
static void SaveFormPosition(HWND window, int* x, int* y);

/// Temporarily substitutes committed widget configurations while saving, then restores the active appearance previews.
static void SaveSettingsWithoutAppearancePreviews();

/// Opens or activates the non-topmost settings form and optionally selects a widget by ID.
/// Creates draft snapshots and fullscreen previews when opening a new form.
static void ShowSettingsWindow(int widgetId = -1);

/// Hides inactive pages before revealing the selected page, updates its state and mnemonics, and ends inapplicable
/// previews.
static void ShowSettingsTab(int tab);

/// Propagates a live menu change into draft, applied, and preview-original configurations.
/// Updates selected controls as needed and reevaluates Apply without rebuilding the settings form.
static void SynchronizeOpenSettings(const Widget* widget, int command);

/// Updates open Help and About windows for the application language and recalculates their layouts.
static void RefreshInformationWindows();

/// Anchors Help or About controls to the client area, measures wrapped product text, and preserves right and bottom
/// spacing.
static void LayoutInformationWindow(HWND window);

/// Returns the Windows message-font face, falling back to the stock GUI font or an empty string.
static std::wstring GetSystemMessageFontFace();

/// Creates a caller-owned GDI font using the widget's point size, style, face, and antialiasing settings.
static HFONT CreateWidgetDrawingFont(const WidgetConfig& config);

/// Creates a caller-owned GDI font from panel font properties, converting the dialog size from tenths of a point.
static HFONT CreatePanelFont(const FontSelection& selection, int fontAntialiasing);

/// Cancels the alarm test, releases its event handles, restores temporary visual alarm state, and resets the Test
/// caption.
static void StopSettingsPreview();

/// Updates font-button captions and the selected widget's font description without rewriting unchanged text.
static void UpdateFontDescription(const WidgetConfig& config);

/// Creates the application font if needed, applies font and theme settings to a form and its children, and requests
/// repainting.
static void ApplyUiStyle(HWND window);

/// Updates control enabled states for the selected widget and temporarily clears inapplicable checkbox values.
/// When requested, hides inapplicable controls before relayout and reveals applicable controls afterward.
static void UpdateSettingControlAvailability(bool updateLayout = false);

/// Reenables Apply when pending changes exist; disabling is reserved for a successful explicit Apply action.
static void UpdateSettingsApplyButton();

/// Saves the selected appearance draft, tracks the widget for later restoration, and updates its live preview.
static void PreviewSelectedWidgetAppearance(bool structuralChange);

/// Restores committed configurations for previewed widgets and clears preview tracking.
static void RestoreSettingsAppearancePreview();

/// Reconciles fullscreen clocks, settings previews, and blackout windows with current monitor and visibility settings.
static void RefreshFullscreenPresentation();

/// Returns a borrowed pointer to the widget with the given persistent ID, or null when absent.
static Widget* FindWidgetById(int id);

/// Requests audio cancellation, closes the widget-owned event handles, and advances the generation to reject stale
/// notifications.
static void CloseWidgetAudio(Widget* widget);

/// Rebuilds a widget for a new configuration while preserving screen-edge attachments and relevant runtime state.
static void RecreateWidgetForConfiguration(Widget* widget, const WidgetConfig& configuration);

/// Creates a calendar font from system message-font metrics and widget face and style settings.
/// Returns null on failure; the caller owns the returned GDI font.
static HFONT CreateCalendarUiFont(const WidgetConfig& config);

/// Returns an owned copy of a control's current Unicode text.
static std::wstring GetControlText(HWND control);

/// Moves or resizes a control only when necessary, retaining combo height and extending settings text controls to the
/// common right edge.
static void SetControlPosition(HWND control, int x, int y, int width, int height);

/// Tests whether a handle matches one of the settings page handles.
static bool IsSettingsPageWindow(HWND window);

/// Updates a nonnull control's text only when the visible string changes.
static void SetControlText(HWND control, const wchar_t* text);

/// Updates a caption only when its text differs after mnemonic removal, preserving existing mnemonic assignments
/// otherwise.
static void SetControlCaption(HWND control, const wchar_t* caption);

/// Changes a nonnull control's enabled state only when needed.
static void SetControlEnabled(HWND control, bool enabled);

/// Changes a nonnull control's own visibility style only when needed.
static void SetControlVisible(HWND control, bool visible);

/// Changes a combo box selection only when the selected index differs.
static void SetComboSelection(HWND combo, int selection);

/// Updates a trackbar's range only when either endpoint differs.
static void SetTrackBarRange(HWND trackBar, int minimum, int maximum);

/// Clamps a requested trackbar position to its range and updates it only when changed.
static void SetTrackBarPosition(HWND trackBar, int position);

/// Updates an owner-drawn button's stored color and invalidates it only when the color changes.
static void SetButtonColor(HWND button, COLORREF color);

/// Changes a checkbox's checked state only when it differs from the requested state.
static void SetCheck(HWND control, bool checked);

/// Shows or hides one widget, updates fullscreen presentation and open settings as needed, and saves the visibility
/// change.
static void SetWidgetVisible(Widget* widget, bool visible);

/// Selects the widget's displayed current date, optionally preserving the calendar's month, year, or decade view.
/// An explicit navigation request returns to month view and focuses the calendar.
static void SelectCalendarToday(Widget* widget, bool preserveView = false);

/// Returns system UTC adjusted by the last valid NTP offset when network time is enabled.
static void GetApplicationUtcTime(SYSTEMTIME* utc);

/// Returns a borrowed common UI string in the current application language.
static const wchar_t* T(TextId id) {
    return TEXT[appLanguage][id];
}

/// Reports whether a widget type supports alarms and time signals; standalone calendars do not.
static bool WidgetSupportsSound(WidgetType type) {
    return type != WIDGET_CALENDAR;
}

/// Maps a language selector's display index to its stored language value, defaulting to US English.
static AppLanguage LanguageFromCombo(HWND combo) {
    int selection = static_cast<int>(SendMessageW(combo, CB_GETCURSEL, 0, 0));
    if (selection < 0 || selection >= LANG_COUNT) {
        return LANG_EN;
    }
    return LANGUAGE_DISPLAY_ORDER[selection];
}

/// Finds a stored language in the selector's display order, defaulting to the US English entry.
static int ComboIndexForLanguage(AppLanguage language) {
    for (int index = 0; index < LANG_COUNT; index++) {
        if (LANGUAGE_DISPLAY_ORDER[index] == language) {
            return index;
        }
    }
    return 1;
}

/// Reads a valid stored antialiasing mode from the selected item's data, or returns defaultValue.
static int SelectedFontAntialiasing(HWND combo, int defaultValue) {
    if (combo == nullptr) {
        return defaultValue;
    }
    LRESULT selection = SendMessageW(combo, CB_GETCURSEL, 0, 0);
    if (selection == CB_ERR) {
        return defaultValue;
    }
    LRESULT mode = SendMessageW(combo, CB_GETITEMDATA, selection, 0);
    return mode >= 0 && mode < FONT_ANTIALIAS_COUNT ? static_cast<int>(mode) : defaultValue;
}

/// Selects the item whose stored data matches the requested antialiasing mode.
static void SelectFontAntialiasing(HWND combo, int mode) {
    int count = static_cast<int>(SendMessageW(combo, CB_GETCOUNT, 0, 0));
    for (int index = 0; index < count; index++) {
        if (SendMessageW(combo, CB_GETITEMDATA, index, 0) == mode) {
            SetComboSelection(combo, index);
            return;
        }
    }
}

/// Adds localized ClearType, GDI, and no-antialiasing choices with their independent stored mode values.
static void PopulateFontAntialiasingCombo(HWND combo) {
    const FontAntialiasing modes[] = {
        FONT_ANTIALIAS_CLEARTYPE,
        FONT_ANTIALIAS_GDI,
        FONT_ANTIALIAS_NONE
    };
    for (FontAntialiasing mode : modes) {
        LRESULT index = SendMessageW(combo, CB_ADDSTRING, 0,
            reinterpret_cast<LPARAM>(ANTIALIASING_NAMES[appLanguage][mode]));
        SendMessageW(combo, CB_SETITEMDATA, index, mode);
    }
}

/// Adds supported language names in their defined display order.
static void PopulateLanguageCombo(HWND combo) {
    for (int index = 0; index < LANG_COUNT; index++) {
        AppLanguage language = LANGUAGE_DISPLAY_ORDER[index];
        SendMessageW(combo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(LANGUAGE_NAMES[language]));
    }
}

/// Returns a borrowed widget-type name in the application language.
static const wchar_t* TypeName(WidgetType type) {
    if (type == WIDGET_FULLSCREEN) {
        return FULLSCREEN_WIDGET_NAMES[appLanguage];
    }
    return T(static_cast<TextId>(TXT_ANALOG + static_cast<int>(type)));
}

/// Returns a borrowed common string in the widget's language, or the application language for a null widget.
static const wchar_t* WT(const Widget* widget, TextId id) {
    AppLanguage language = widget == nullptr ? appLanguage : widget->config.language;
    return TEXT[language][id];
}

/// Normalizes a character to uppercase for comparing assigned keyboard mnemonics.
static wchar_t MnemonicKey(wchar_t character) {
    CharUpperBuffW(&character, 1);
    return character;
}

/// Preserves an available preferred mnemonic or assigns an unused character while escaping literal ampersands.
/// Records the chosen key in usedMnemonics.
static std::wstring UniqueMnemonic(const wchar_t* text, std::vector<wchar_t>* usedMnemonics) {
    std::wstring plainText;
    size_t preferredPosition = std::wstring::npos;
    for (size_t index = 0; text[index] != L'\0'; index++) {
        if (text[index] == L'&' && text[index + 1] != L'\0') {
            if (text[index + 1] == L'&') {
                plainText += L'&';
                index++;
            } else if (preferredPosition == std::wstring::npos) {
                preferredPosition = plainText.size();
            }
            continue;
        }
        plainText += text[index];
    }
    size_t mnemonicPosition = std::wstring::npos;
    if (preferredPosition < plainText.size()) {
        wchar_t key = MnemonicKey(plainText[preferredPosition]);
        if (std::iswalnum(plainText[preferredPosition])
                && std::find(usedMnemonics->begin(), usedMnemonics->end(), key) == usedMnemonics->end()) {
            mnemonicPosition = preferredPosition;
        }
    }
    if (mnemonicPosition == std::wstring::npos) {
        for (size_t index = 0; index < plainText.size(); index++) {
            wchar_t key = MnemonicKey(plainText[index]);
            if (std::iswalnum(plainText[index])
                    && std::find(usedMnemonics->begin(), usedMnemonics->end(), key) == usedMnemonics->end()) {
                mnemonicPosition = index;
                break;
            }
        }
    }
    std::wstring result;
    for (size_t index = 0; index < plainText.size(); index++) {
        if (index == mnemonicPosition) {
            result += L'&';
        }
        if (plainText[index] == L'&') {
            result += L'&';
        }
        result += plainText[index];
    }
    if (mnemonicPosition != std::wstring::npos) {
        usedMnemonics->push_back(MnemonicKey(plainText[mnemonicPosition]));
    }
    return result;
}

/// Appends a menu command with a mnemonic unique among the supplied used keys.
static void AppendMenuCommand(HMENU menu, UINT flags, UINT_PTR command, const wchar_t* text,
        std::vector<wchar_t>* usedMnemonics) {
    std::wstring label = UniqueMnemonic(text, usedMnemonics);
    AppendMenuW(menu, flags, command, label.c_str());
}

/// Appends localized Settings, Help, About, and Exit commands with distinct menu mnemonics.
static void AppendApplicationMenuCommands(HMENU menu, AppLanguage language, std::vector<wchar_t>* usedMnemonics) {
    AppendMenuCommand(menu, MF_STRING, ID_MENU_SETTINGS, TEXT[language][TXT_SETTINGS], usedMnemonics);
    AppendMenuCommand(menu, MF_STRING, ID_MENU_HELP, TEXT[language][TXT_HELP], usedMnemonics);
    AppendMenuCommand(menu, MF_STRING, ID_MENU_ABOUT, TEXT[language][TXT_ABOUT], usedMnemonics);
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendMenuCommand(menu, MF_STRING, ID_MENU_EXIT, TEXT[language][TXT_EXIT], usedMnemonics);
}

/// Supplies the active calendar locale to common controls, otherwise forwarding to the original locale query.
static LCID WINAPI CalendarGetUserDefaultLCID() {
    if (activeCalendarLocale != 0) {
        return activeCalendarLocale;
    }
    return originalGetUserDefaultLcid == nullptr ? LOCALE_USER_DEFAULT : originalGetUserDefaultLcid();
}

/// Forwards a locale-property request using the active calendar override when present.
static int WINAPI CalendarGetLocaleInfoW(LCID locale, LCTYPE type, LPWSTR data, int characters) {
    if (originalGetLocaleInfoW == nullptr) {
        return 0;
    }
    LCID selectedLocale = activeCalendarLocale == 0 ? locale : activeCalendarLocale;
    return originalGetLocaleInfoW(selectedLocale, type, data, characters);
}

/// Forwards a calendar-property request using the active calendar locale when present.
static int WINAPI CalendarGetCalendarInfoW(LCID locale, CALID calendar, CALTYPE type, LPWSTR data, int characters,
        LPDWORD value) {
    if (originalGetCalendarInfoW == nullptr) {
        return 0;
    }
    LCID selectedLocale = activeCalendarLocale == 0 ? locale : activeCalendarLocale;
    return originalGetCalendarInfoW(selectedLocale, calendar, type, data, characters, value);
}

/// Converts the active calendar override to a locale name and forwards the calendar-property request.
static int WINAPI CalendarGetCalendarInfoEx(LPCWSTR localeName, CALID calendar, LPCWSTR reserved, CALTYPE type,
        LPWSTR data, int characters, LPDWORD value) {
    if (originalGetCalendarInfoEx == nullptr) {
        return 0;
    }
    wchar_t selectedName[LOCALE_NAME_MAX_LENGTH] = {};
    LPCWSTR selectedLocaleName = localeName;
    if (activeCalendarLocale != 0
            && LCIDToLocaleName(activeCalendarLocale, selectedName, ARRAYSIZE(selectedName), 0) != 0) {
        selectedLocaleName = selectedName;
    }
    return originalGetCalendarInfoEx(selectedLocaleName, calendar, reserved, type, data, characters, value);
}

/// Formats a calendar date in the active override locale when conversion is available.
/// Falls back to the original common-controls date-formatting import otherwise.
static int WINAPI CalendarGetCalendarDateFormat(CALID calendar, DWORD flags, const void* calendarDate, LPCWSTR format,
        LPWSTR data, int characters) {
    if (activeCalendarLocale != 0 && calendarDate != nullptr && data != nullptr && characters > 0) {
        if (convertCalDateTimeToSystemTime == nullptr) {
            HMODULE kernel = GetModuleHandleW(L"kernel32.dll");
            if (kernel != nullptr) {
                convertCalDateTimeToSystemTime =
                    reinterpret_cast<ConvertCalDateTimeToSystemTimeProc>(GetProcAddress(kernel,
                        "ConvertCalDateTimeToSystemTime"));
            }
        }
        SYSTEMTIME systemTime = {};
        wchar_t localeName[LOCALE_NAME_MAX_LENGTH] = {};
        if (convertCalDateTimeToSystemTime != nullptr
                && convertCalDateTimeToSystemTime(calendarDate, &systemTime)
                && LCIDToLocaleName(activeCalendarLocale, localeName, ARRAYSIZE(localeName), 0) != 0) {
            int result = GetDateFormatEx(localeName, flags, &systemTime, format, data, characters, nullptr);
            if (result != 0) {
                return result;
            }
        }
    }
    if (originalGetCalendarDateFormat == nullptr) {
        return 0;
    }
    return originalGetCalendarDateFormat(calendar, flags, calendarDate, format, data, characters);
}

/// Replaces a named comctl32 import with a locale wrapper and saves the original address.
/// Temporarily changes memory protection and returns false if the import cannot be patched.
static bool PatchCommonControlsImport(const char* functionName, ULONG_PTR replacement, ULONG_PTR* original) {
    HMODULE commonControls = GetModuleHandleW(L"comctl32.dll");
    if (commonControls == nullptr) {
        return false;
    }
    BYTE* base = reinterpret_cast<BYTE*>(commonControls);
    IMAGE_DOS_HEADER* dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
        return false;
    }
    IMAGE_NT_HEADERS* ntHeaders = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dosHeader->e_lfanew);
    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE) {
        return false;
    }
    IMAGE_DATA_DIRECTORY imports = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    if (imports.VirtualAddress == 0) {
        return false;
    }
    IMAGE_IMPORT_DESCRIPTOR* descriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(base + imports.VirtualAddress);
    for (; descriptor->Name != 0; descriptor++) {
        if (descriptor->OriginalFirstThunk == 0 || descriptor->FirstThunk == 0) {
            continue;
        }
        IMAGE_THUNK_DATA* names = reinterpret_cast<IMAGE_THUNK_DATA*>(base + descriptor->OriginalFirstThunk);
        IMAGE_THUNK_DATA* addresses = reinterpret_cast<IMAGE_THUNK_DATA*>(base + descriptor->FirstThunk);
        for (; names->u1.AddressOfData != 0; names++, addresses++) {
            if (IMAGE_SNAP_BY_ORDINAL(names->u1.Ordinal)) {
                continue;
            }
            IMAGE_IMPORT_BY_NAME* importName = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(base + names->u1.AddressOfData);
            if (strcmp(reinterpret_cast<const char*>(importName->Name), functionName) != 0) {
                continue;
            }
            DWORD oldProtect = 0;
            if (!VirtualProtect(&addresses->u1.Function, sizeof(addresses->u1.Function), PAGE_READWRITE, &oldProtect)) {
                return false;
            }
            *original = addresses->u1.Function;
            addresses->u1.Function = replacement;
            DWORD ignored = 0;
            VirtualProtect(&addresses->u1.Function, sizeof(addresses->u1.Function), oldProtect, &ignored);
            FlushInstructionCache(GetCurrentProcess(), &addresses->u1.Function, sizeof(addresses->u1.Function));
            return true;
        }
    }
    return false;
}

/// Installs the common-controls locale wrappers once and records the original entry points.
static bool InstallCalendarLocaleHook() {
    if (originalGetUserDefaultLcid != nullptr) {
        return true;
    }
    ULONG_PTR original = 0;
    bool defaultHook = PatchCommonControlsImport("GetUserDefaultLCID",
        reinterpret_cast<ULONG_PTR>(&CalendarGetUserDefaultLCID), &original);
    originalGetUserDefaultLcid = reinterpret_cast<GetUserDefaultLcidProc>(original);
    original = 0;
    bool localeHook = PatchCommonControlsImport("GetLocaleInfoW",
        reinterpret_cast<ULONG_PTR>(&CalendarGetLocaleInfoW), &original);
    originalGetLocaleInfoW = reinterpret_cast<GetLocaleInfoWProc>(original);
    original = 0;
    bool calendarHook = PatchCommonControlsImport("GetCalendarInfoW",
        reinterpret_cast<ULONG_PTR>(&CalendarGetCalendarInfoW), &original);
    originalGetCalendarInfoW = reinterpret_cast<GetCalendarInfoWProc>(original);
    original = 0;
    PatchCommonControlsImport("GetCalendarInfoEx",
        reinterpret_cast<ULONG_PTR>(&CalendarGetCalendarInfoEx), &original);
    originalGetCalendarInfoEx = reinterpret_cast<GetCalendarInfoExProc>(original);
    original = 0;
    bool dateHook = PatchCommonControlsImport("GetCalendarDateFormat",
        reinterpret_cast<ULONG_PTR>(&CalendarGetCalendarDateFormat), &original);
    originalGetCalendarDateFormat = reinterpret_cast<GetCalendarDateFormatProc>(original);
    return defaultHook && localeHook && calendarHook && dateHook;
}

/// Appends a monitor's geometry, device name, and primary flag to the enumeration result.
static BOOL CALLBACK CollectDisplayMonitor(HMONITOR monitor, HDC, LPRECT, LPARAM data) {
    std::vector<DisplayMonitor>* monitors = reinterpret_cast<std::vector<DisplayMonitor> *>(data);
    MONITORINFOEXW information = {};
    information.cbSize = sizeof(information);
    if (monitors != nullptr && GetMonitorInfoW(monitor, &information)) {
        DisplayMonitor item = {};
        item.rect = information.rcMonitor;
        item.device = information.szDevice;
        item.primary = (information.dwFlags & MONITORINFOF_PRIMARY) != 0;
        monitors->push_back(item);
    }
    return TRUE;
}

/// Rebuilds the monitor list with the primary monitor first, then orders the remainder by screen position.
static void RefreshDisplayMonitors() {
    displayMonitors.clear();
    EnumDisplayMonitors(nullptr, nullptr, CollectDisplayMonitor, reinterpret_cast<LPARAM>(&displayMonitors));
    std::stable_sort(displayMonitors.begin(), displayMonitors.end(),
        [](const DisplayMonitor& left, const DisplayMonitor& right) {
            if (left.primary != right.primary) {
                return left.primary;
            }
            if (left.rect.top != right.rect.top) {
                return left.rect.top < right.rect.top;
            }
            return left.rect.left < right.rect.left;
    });
}

/// Tests case-insensitive membership in a semicolon-separated list of monitor device names.
static bool ContainsMonitorDevice(const std::wstring& devices, const std::wstring& device) {
    size_t start = 0;
    while (start <= devices.size()) {
        size_t end = devices.find(L';', start);
        std::wstring current = devices.substr(start, end == std::wstring::npos ? std::wstring::npos : end - start);
        if (_wcsicmp(current.c_str(), device.c_str()) == 0) {
            return true;
        }
        if (end == std::wstring::npos) {
            break;
        }
        start = end + 1;
    }
    return false;
}

/// Returns borrowed pointers to selected monitors, falling back to the first available display.
/// The pointers remain valid only until the monitor list is rebuilt.
static std::vector<const DisplayMonitor*> SelectedDisplayMonitors(const WidgetConfig& config) {
    if (displayMonitors.empty()) {
        RefreshDisplayMonitors();
    }
    std::vector<const DisplayMonitor*> selected;
    for (size_t index = 0; index < displayMonitors.size(); index++) {
        if (ContainsMonitorDevice(config.monitorDevices, displayMonitors[index].device)) {
            selected.push_back(&displayMonitors[index]);
        }
    }
    if (selected.empty() && !displayMonitors.empty()) {
        selected.push_back(&displayMonitors[0]);
    }
    return selected;
}

/// Copies the first selected monitor's rectangle, returning false if no monitor or destination is available.
static bool GetPrimarySelectedMonitorRect(const WidgetConfig& config, RECT* rect) {
    std::vector<const DisplayMonitor*> selected = SelectedDisplayMonitors(config);
    if (selected.empty() || rect == nullptr) {
        return false;
    }
    *rect = selected[0]->rect;
    return true;
}

/// Fills a four-entry size buffer from the native clock implementation, using standard sizes if detection fails.
static int GetAnalogClockSizes(int* sizes) {
    int count = GetSupportedAnalogClockSizes(sizes, 4);
    if (count > 0) {
        return count;
    }
    const int fallbackSizes[] = {
        104,
        130,
        166,
        198
    };
    CopyMemory(sizes, fallbackSizes, sizeof(fallbackSizes));
    return ARRAYSIZE(fallbackSizes);
}

/// Maps equivalent legacy clock sizes to the current implementation, otherwise choosing the nearest supported size.
static int NormalizeAnalogClockSize(int size) {
    int sizes[4] = {};
    int count = GetAnalogClockSizes(sizes);
    const int vistaSizes[] = {
        103,
        128,
        129,
        160
    };
    const int otherSizes[] = {
        104,
        130,
        166,
        198
    };
    const int* sourceSizes = sizes[0] == vistaSizes[0] ? otherSizes : vistaSizes;
    for (int index = 0; index < ARRAYSIZE(vistaSizes); index++) {
        if (size == sourceSizes[index]) {
            return sizes[index];
        }
    }
    int result = sizes[0];
    int distance = std::abs(size - result);
    for (int index = 1; index < count; index++) {
        int candidateDistance = std::abs(size - sizes[index]);
        if (candidateDistance < distance) {
            result = sizes[index];
            distance = candidateDistance;
        }
    }
    return result;
}

/// Returns the native size represented by a selector item, or fallback when the selection is unavailable.
static int GetSelectedAnalogClockSize(int fallback, HWND combo = hSizeCombo) {
    if (combo == nullptr) {
        return fallback;
    }
    int sizes[4] = {};
    int count = GetAnalogClockSizes(sizes);
    int selected = static_cast<int>(SendMessageW(combo, CB_GETCURSEL, 0, 0));
    return selected >= 0 && selected < count ? sizes[selected] : fallback;
}

/// Resets a widget's appearance for its type using the current application antialiasing choice and system font
/// defaults.
static void SetDefaultWidgetAppearance(WidgetConfig* config, WidgetType type) {
    if (config == nullptr) {
        return;
    }
    config->size = 130;
    for (AdditionalClockConfig& clock : config->additionalClocks) {
        clock.size = 104;
    }
    config->opacity = 100;
    config->fontSize = 44;
    config->fontDialogSize = type == WIDGET_DIGITAL ? config->fontSize * 10 : 90;
    int selectedAppFontAntialiasing = SelectedFontAntialiasing(hAppAntialiasCombo, appFontAntialiasing);
    config->fontAntialiasing = std::clamp(selectedAppFontAntialiasing, 0, FONT_ANTIALIAS_COUNT - 1);
    config->leadingZeroMode = LEADING_ZERO_VISIBLE;
    config->transparentBackground = false;
    config->disableThemes = false;
    if (type == WIDGET_DIGITAL) {
        config->fontFace = L"Arial";
    } else if (type == WIDGET_FULLSCREEN) {
        config->fontFace = L"Arial Narrow";
    } else {
        config->fontFace = GetSystemMessageFontFace();
    }
    config->fontWeight = FW_NORMAL;
    config->fontItalic = false;
    config->fontUnderline = false;
    config->fontStrikeOut = false;
    config->fontCharSet = DEFAULT_CHARSET;
    config->padding = 8;
    config->borderStyle = DIGITAL_BORDER_TOOL_WINDOW;
    config->borderWidth = type == WIDGET_DIGITAL ? 0 : 1;
    config->borderColor = RGB(151, 151, 151);
    config->textColor = type == WIDGET_FULLSCREEN ? RGB(255, 255, 255) : RGB(16, 16, 16);
    config->backgroundColor = type == WIDGET_FULLSCREEN ? RGB(0, 0, 0) : RGB(255, 255, 255);
    config->alarmTextColor = RGB(220, 0, 0);
    config->alarmBackgroundColor = RGB(255, 255, 128);
    config->showToday = true;
    config->weekNumbers = false;
    config->sundayFirst = false;
    config->dateCopyFormat = DATE_LOCAL_SHORT;
    FontSelection panelFont;
    panelFont.face = GetSystemMessageFontFace();
    config->panelTopFont = panelFont;
    config->panelTimeFont = panelFont;
    config->panelBottomFont = panelFont;
}

/// Builds a visible widget with localized defaults and an initial position, allocating a new widget ID.
static WidgetConfig DefaultConfig(WidgetType type, int index) {
    WidgetConfig config = {};
    config.id = nextWidgetId++;
    config.type = type;
    config.name = TypeName(type);
    config.visible = true;
    config.topMost = true;
    config.showSeconds = true;
    config.showUtc = false;
    config.showUtcText = false;
    config.language = appLanguage;
    config.timeZoneKey = GetSystemTimeZoneKey(timeZones);
    for (AdditionalClockConfig& clock : config.additionalClocks) {
        clock.timeZoneKey = config.timeZoneKey;
    }
    if (type == WIDGET_FULLSCREEN) {
        RefreshDisplayMonitors();
        if (!displayMonitors.empty()) {
            config.monitorDevices = displayMonitors[0].device;
        }
    }
    config.offsetMilliseconds = 0;
    config.x = 100 + index * 28;
    config.y = 100 + index * 28;
    SetDefaultWidgetAppearance(&config, type);
    config.alarmEnabled = false;
    config.alarmDays = ALARM_DAYS_ALL;
    config.alarmTimeSignal = false;
    config.soundsMuted = false;
    config.alarmHour = 6;
    config.alarmMinute = 0;
    config.runCommand = false;
    config.loopAudio = false;
    config.callRemoteScript = false;
    config.timeSignal = TIME_SIGNAL_NONE;
    return config;
}

/// Selects a supported language from the Windows UI language, defaulting to US English.
static void SelectSystemLanguage() {
    LANGID systemLanguage = GetUserDefaultUILanguage();
    switch (PRIMARYLANGID(systemLanguage)) {
        case LANG_CZECH:
            appLanguage = LANG_CZ;
            break;
        case LANG_ENGLISH:
            if (SUBLANGID(systemLanguage) == SUBLANG_ENGLISH_UK) {
                appLanguage = LANG_EN_GB;
            } else if (SUBLANGID(systemLanguage) == SUBLANG_ENGLISH_AUS) {
                appLanguage = LANG_EN_AU;
            } else {
                appLanguage = LANG_EN;
            }
            break;
        case LANG_GERMAN:
            appLanguage = LANG_DE;
            break;
        case LANG_FRENCH:
            appLanguage = LANG_FR;
            break;
        case LANG_SPANISH:
            appLanguage = LANG_ES;
            break;
        case LANG_ITALIAN:
            appLanguage = LANG_IT;
            break;
        case LANG_POLISH:
            appLanguage = LANG_PL;
            break;
        case LANG_SLOVAK:
            appLanguage = LANG_SK;
            break;
        case LANG_PORTUGUESE:
            appLanguage = LANG_PT;
            break;
        case LANG_NORWEGIAN:
            appLanguage = LANG_NO;
            break;
        case LANG_SWEDISH:
            appLanguage = LANG_SV;
            break;
        case LANG_FINNISH:
            appLanguage = LANG_FI;
            break;
        case LANG_DANISH:
            appLanguage = LANG_DA;
            break;
        case LANG_ICELANDIC:
            appLanguage = LANG_IS;
            break;
        case LANG_TURKISH:
            appLanguage = LANG_TR;
            break;
        default:
            appLanguage = LANG_EN;
            break;
    }
}

/// Copies application and widget settings, including the latest positions of open settings and information windows.
static SettingsSnapshot CaptureSettingsSnapshot() {
    SettingsSnapshot snapshot = {};
    snapshot.language = appLanguage;
    snapshot.themesDisabled = themesDisabled;
    snapshot.snapWidgetsToWorkArea = snapWidgetsToWorkArea;
    snapshot.generatedTimeSignal = generatedTimeSignal;
    snapshot.timeSignalVolume = timeSignalVolume;
    snapshot.fontAntialiasing = appFontAntialiasing;
    snapshot.fontFace = appFontFace;
    snapshot.fontDialogSize = appFontDialogSize;
    snapshot.fontWeight = appFontWeight;
    snapshot.fontItalic = appFontItalic;
    snapshot.useNtpTime = useNtpTime;
    snapshot.ntpPreset = ntpPreset;
    snapshot.ntpServers = ntpServers;
    snapshot.settingsX = settingsX;
    snapshot.settingsY = settingsY;
    snapshot.settingsTab = settingsTab;
    snapshot.lastAddedWidgetType = lastAddedWidgetType;
    snapshot.helpX = helpX;
    snapshot.helpY = helpY;
    snapshot.aboutX = aboutX;
    snapshot.aboutY = aboutY;
    SaveFormPosition(hSettings, &snapshot.settingsX, &snapshot.settingsY);
    SaveFormPosition(hHelp, &snapshot.helpX, &snapshot.helpY);
    SaveFormPosition(hAbout, &snapshot.aboutX, &snapshot.aboutY);
    for (size_t index = 0; index < widgets.size(); index++) {
        snapshot.widgets.push_back(widgets[index]->config);
    }
    return snapshot;
}

/// Restores application options and rebuilds widget state from a stored snapshot, normalizing bounded values and the
/// next ID.
static void ApplySettingsSnapshot(const SettingsSnapshot& snapshot) {
    appLanguage = snapshot.language;
    themesDisabled = snapshot.themesDisabled;
    snapWidgetsToWorkArea = snapshot.snapWidgetsToWorkArea;
    generatedTimeSignal = snapshot.generatedTimeSignal;
    timeSignalVolume = std::clamp<double>(snapshot.timeSignalVolume, TIME_SIGNAL_VOLUME_MIN, TIME_SIGNAL_VOLUME_MAX);
    appFontAntialiasing = std::clamp(snapshot.fontAntialiasing, 0, FONT_ANTIALIAS_COUNT - 1);
    appFontFace = snapshot.fontFace.size() < LF_FACESIZE ? snapshot.fontFace : L"";
    appFontDialogSize = std::clamp(snapshot.fontDialogSize, 10, 9990);
    appFontWeight = std::clamp(snapshot.fontWeight, 0, 1000);
    appFontItalic = snapshot.fontItalic;
    useNtpTime = snapshot.useNtpTime;
    ntpPreset = std::clamp(snapshot.ntpPreset, 0, NTP_PRESET_COUNT - 1);
    ntpServers = ntpPreset == NTP_PRESET_CUSTOM ? snapshot.ntpServers : NtpServersForPreset(ntpPreset);
    if (ntpServers.empty()) {
        ntpPreset = NTP_PRESET_GLOBAL;
        ntpServers = NtpServersForPreset(ntpPreset);
    }
    ntpGeneration++;
    ntpTimeValid = false;
    ntpActiveServer.clear();
    ntpLastQueryFailed = false;
    lastNtpAttemptTick = 0;
    nextNtpAttemptTick = 0;
    settingsX = snapshot.settingsX;
    settingsY = snapshot.settingsY;
    settingsTab = std::clamp(snapshot.settingsTab, 0, SETTINGS_TAB_COUNT - 1);
    lastAddedWidgetType =
        static_cast<WidgetType>(std::clamp(static_cast<int>(snapshot.lastAddedWidgetType), 0, WIDGET_TYPE_COUNT - 1));
    helpX = snapshot.helpX;
    helpY = snapshot.helpY;
    aboutX = snapshot.aboutX;
    aboutY = snapshot.aboutY;
    lastHiddenWidgetIds.clear();
    widgets.clear();
    nextWidgetId = 1;
    for (size_t index = 0; index < snapshot.widgets.size(); index++) {
        std::unique_ptr<Widget> widget(new Widget());
        widget->config = snapshot.widgets[index];
        nextWidgetId = std::max(nextWidgetId, widget->config.id + 1);
        widgets.push_back(std::move(widget));
    }
}

/// Refreshes the application's named and fixed-offset time-zone list.
static void LoadTimeZones() {
    LoadTimeZoneList(&timeZones);
}

/// Creates language-specific widget defaults for storage readers while restoring temporary global default state.
static WidgetConfig CreateStoredWidgetDefaults(WidgetType type, int index, AppLanguage language, int fontAntialiasing) {
    int savedNextWidgetId = nextWidgetId;
    AppLanguage savedLanguage = appLanguage;
    int savedFontAntialiasing = appFontAntialiasing;
    appLanguage = language;
    appFontAntialiasing = fontAntialiasing;
    WidgetConfig config = DefaultConfig(type, index);
    nextWidgetId = savedNextWidgetId;
    appLanguage = savedLanguage;
    appFontAntialiasing = savedFontAntialiasing;
    config.language = language;
    config.fontAntialiasing = std::clamp(fontAntialiasing, 0, FONT_ANTIALIAS_COUNT - 1);
    return config;
}

/// Returns the quoted executable path for the startup registry value, or an empty string if it cannot be obtained.
static std::wstring StartWithWindowsCommand() {
    wchar_t executable[MAX_PATH] = {};
    DWORD length = GetModuleFileNameW(nullptr, executable, ARRAYSIZE(executable));
    if (length == 0 || length >= ARRAYSIZE(executable)) {
        return L"";
    }
    return L"\"" + std::wstring(executable, length) + L"\"";
}

/// Checks whether the per-user startup entry matches this executable's quoted path.
static bool IsStartWithWindowsEnabled() {
    const wchar_t startupPath[] = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t startupValue[] = L"CalClock";
    std::wstring expected = StartWithWindowsCommand();
    if (expected.empty()) {
        return false;
    }
    wchar_t actual[MAX_PATH * 2] = {};
    DWORD size = sizeof(actual);
    if (RegGetValueW(HKEY_CURRENT_USER, startupPath, startupValue, RRF_RT_REG_SZ, nullptr, actual, &size) !=
            ERROR_SUCCESS) {
        return false;
    }
    return _wcsicmp(actual, expected.c_str()) == 0;
}

/// Creates or removes this application's per-user Windows startup entry and reports registry-operation success.
static bool SetStartWithWindowsEnabled(bool enabled) {
    const wchar_t startupPath[] = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t startupValue[] = L"CalClock";
    if (!enabled) {
        HKEY key = nullptr;
        LSTATUS opened = RegOpenKeyExW(HKEY_CURRENT_USER, startupPath, 0, KEY_SET_VALUE, &key);
        if (opened == ERROR_FILE_NOT_FOUND) {
            return true;
        }
        if (opened != ERROR_SUCCESS) {
            return false;
        }
        LSTATUS deleted = RegDeleteValueW(key, startupValue);
        RegCloseKey(key);
        return deleted == ERROR_SUCCESS || deleted == ERROR_FILE_NOT_FOUND;
    }
    std::wstring command = StartWithWindowsCommand();
    if (command.empty()) {
        return false;
    }
    HKEY key = nullptr;
    DWORD disposition = 0;
    if (RegCreateKeyExW(HKEY_CURRENT_USER, startupPath, 0, nullptr, 0, KEY_SET_VALUE, nullptr, &key, &disposition) != ERROR_SUCCESS) {
        return false;
    }
    LSTATUS written = RegSetValueExW(key, startupValue, 0, REG_SZ,
        reinterpret_cast<const BYTE*>(command.c_str()), static_cast<DWORD>((command.size() + 1) * sizeof(wchar_t)));
    RegCloseKey(key);
    return written == ERROR_SUCCESS;
}

/// Loads language and startup defaults, time zones, and persisted XML or registry settings.
/// Creates an initial analog widget if no stored settings can be loaded.
static void LoadAllSettings() {
    SelectSystemLanguage();
    startWithWindows = IsStartWithWindowsEnabled();
    ntpPreset = NTP_PRESET_AUTO;
    ntpServers = NtpServersForPreset(ntpPreset);
    LoadTimeZones();
    std::wstring xmlPath = AutomaticXmlSettingsPath(false);
    storageUsesXml = !xmlPath.empty() && GetFileAttributesW(xmlPath.c_str()) != INVALID_FILE_ATTRIBUTES;
    SettingsSnapshot snapshot = {};
    if (storageUsesXml && ReadSettingsXml(xmlPath, appLanguage, CreateStoredWidgetDefaults, &snapshot)) {
        ApplySettingsSnapshot(snapshot);
        return;
    }
    SettingsSnapshot defaults = CaptureSettingsSnapshot();
    if (ReadRegistrySettings(defaults, CreateStoredWidgetDefaults, &snapshot)) {
        ApplySettingsSnapshot(snapshot);
        return;
    }
    std::unique_ptr<Widget> widget(new Widget());
    widget->config = DefaultConfig(WIDGET_ANALOG, 0);
    widgets.push_back(std::move(widget));
}

/// Captures current settings and saves them to the selected XML or registry backend.
/// Removes registry settings after a successful switch to XML storage.
static void SaveAllSettings() {
    SettingsSnapshot snapshot = CaptureSettingsSnapshot();
    if (storageUsesXml) {
        std::wstring path = AutomaticXmlSettingsPath(true);
        if (WriteSettingsXml(path, snapshot)) {
            RemoveRegistrySettings();
        }
        return;
    }
    WriteRegistrySettings(snapshot);
}

/// Splits numeric input into digit groups, optionally accepting a leading sign.
/// Skips separators but rejects letters and underscores; returns false when no digits are found.
static bool SplitNumericInput(const wchar_t* text, bool allowSign, bool* negative, std::vector<std::wstring>* groups) {
    if (text == nullptr || groups == nullptr) {
        return false;
    }
    groups->clear();
    const wchar_t* position = text;
    while (iswspace(*position)) {
        position++;
    }
    bool parsedNegative = false;
    if (*position == L'-' || *position == L'+') {
        if (!allowSign) {
            return false;
        }
        parsedNegative = *position == L'-';
        position++;
    }
    while (*position != 0) {
        if (iswdigit(*position)) {
            const wchar_t* start = position;
            while (iswdigit(*position)) {
                position++;
            }
            groups->emplace_back(start, position);
            continue;
        }
        if (iswalpha(*position) || *position == L'_') {
            return false;
        }
        position++;
    }
    if (negative != nullptr) {
        *negative = parsedNegative;
    }
    return !groups->empty();
}

/// Converts a previously validated digit group to an unsigned 64-bit value with overflow checking.
static bool ParseUnsignedGroup(const std::wstring& text, ULONGLONG* value) {
    if (text.empty() || value == nullptr) {
        return false;
    }
    ULONGLONG parsed = 0;
    for (wchar_t character : text) {
        unsigned int digit = static_cast<unsigned int>(character - L'0');
        if (parsed > (ULLONG_MAX - digit) / 10) {
            return false;
        }
        parsed = parsed * 10 + digit;
    }
    *value = parsed;
    return true;
}

/// Parses signed compact or separated clock-offset input into milliseconds with hundredth-second precision.
/// Rejects invalid component ranges and values that would overflow the result.
static bool ParseOffset(const wchar_t* text, LONGLONG* result) {
    if (result == nullptr) {
        return false;
    }
    bool negative = false;
    std::vector<std::wstring> groups;
    if (!SplitNumericInput(text, true, &negative, &groups) || groups.size() > 4) {
        return false;
    }
    ULONGLONG hours = 0;
    ULONGLONG minutes = 0;
    ULONGLONG seconds = 0;
    ULONGLONG hundredths = 0;
    if (groups.size() == 1) {
        const std::wstring& compact = groups[0];
        size_t secondsStart = compact.size() > 2 ? compact.size() - 2 : 0;
        if (!ParseUnsignedGroup(compact.substr(secondsStart), &seconds)) {
            return false;
        }
        size_t minutesStart = secondsStart > 2 ? secondsStart - 2 : 0;
        if (secondsStart > 0
                && !ParseUnsignedGroup(compact.substr(minutesStart, secondsStart - minutesStart), &minutes)) {
            return false;
        }
        if (minutesStart > 0
                && !ParseUnsignedGroup(compact.substr(0, minutesStart), &hours)) {
            return false;
        }
    } else {
        ULONGLONG values[4] = {};
        for (size_t index = 0; index < groups.size(); index++) {
            if (!ParseUnsignedGroup(groups[index], &values[index])) {
                return false;
            }
        }
        if (groups.size() == 2) {
            minutes = values[0];
            seconds = values[1];
        } else if (groups.size() == 3) {
            hours = values[0];
            minutes = values[1];
            seconds = values[2];
        } else if (groups.size() == 4) {
            hours = values[0];
            minutes = values[1];
            seconds = values[2];
            hundredths = values[3];
        } else {
            return false;
        }
    }
    if (minutes > 59 || seconds > 59 || hundredths > 99 || hours > static_cast<ULONGLONG>(LLONG_MAX) / 3600000ULL) {
        return false;
    }
    ULONGLONG milliseconds = ((hours * 60ULL + minutes) * 60ULL + seconds) * 1000ULL + hundredths * 10ULL;
    if (milliseconds > static_cast<ULONGLONG>(LLONG_MAX)) {
        return false;
    }
    *result = negative ? -static_cast<LONGLONG>(milliseconds) : static_cast<LONGLONG>(milliseconds);
    return true;
}

/// Formats a signed millisecond offset as hours, minutes, seconds, and hundredths without overflowing on the minimum
/// value.
static std::wstring FormatOffset(LONGLONG milliseconds) {
    bool negative = milliseconds < 0;
    ULONGLONG value = negative
        ? static_cast<ULONGLONG>(-(milliseconds + 1)) + 1ULL
        : static_cast<ULONGLONG>(milliseconds);
    ULONGLONG hours = value / 3600000;
    int minutes = static_cast<int>(value / 60000 % 60);
    int seconds = static_cast<int>(value / 1000 % 60);
    int hundredths = static_cast<int>(value / 10 % 100);
    wchar_t text[64] = {};
    swprintf_s(text, L"%s%02llu:%02d:%02d.%02d", negative ? L"-" : L"", hours, minutes, seconds, hundredths);
    return text;
}

/// Parses compact or separated alarm input into a valid 24-hour hour and minute, leaving outputs unchanged on failure.
static bool ParseAlarmTime(const wchar_t* text, int* hour, int* minute) {
    if (hour == nullptr || minute == nullptr) {
        return false;
    }
    std::vector<std::wstring> groups;
    if (!SplitNumericInput(text, false, nullptr, &groups) || groups.size() > 2) {
        return false;
    }
    if (groups.size() == 1) {
        if (groups[0].size() < 1 || groups[0].size() > 4) {
            return false;
        }
        if (groups[0].size() == 3 || groups[0].size() == 4) {
            size_t hourDigits = groups[0].size() - 2;
            std::wstring compact = groups[0];
            groups.clear();
            groups.push_back(compact.substr(0, hourDigits));
            groups.push_back(compact.substr(hourDigits));
        }
    }
    ULONGLONG parsedHour = 0;
    ULONGLONG parsedMinute = 0;
    if (!ParseUnsignedGroup(groups[0], &parsedHour)
            || groups.size() == 2 && !ParseUnsignedGroup(groups[1], &parsedMinute)
            || parsedHour > 23
            || parsedMinute > 59) {
        return false;
    }
    *hour = static_cast<int>(parsedHour);
    *minute = static_cast<int>(parsedMinute);
    return true;
}

/// Returns milliseconds elapsed in the current local hour using the application's corrected UTC time.
/// Falls back to UTC fields if conversion to the Windows local time zone fails.
static ULONGLONG GetNtpHourPosition() {
    SYSTEMTIME utc = {};
    GetApplicationUtcTime(&utc);
    SYSTEMTIME local = {};
    if (!SystemTimeToTzSpecificLocalTime(nullptr, &utc, &local)) {
        local = utc;
    }
    return (local.wMinute * 60ULL + local.wSecond) * 1000 + local.wMilliseconds;
}

/// Starts a due or forced NTP query on the UI thread, postponing automatic requests around the hour until HH:00:10.
/// Manual requests bypass that postponement. Failed attempts retry after one minute before the first successful
/// synchronization in this process, or ten minutes afterward; successful results schedule the next hourly request.
static void StartNtpSynchronization(bool force, bool manual = false) {
    if (!useNtpTime || !winsockReady || ntpQueryRunning) {
        return;
    }
    if (force) {
        nextNtpAttemptTick = 0;
    }
    ULONGLONG now = GetTickCount64();
    if (now < nextNtpAttemptTick) {
        return;
    }
    if (!manual) {
        ULONGLONG hourPosition = GetNtpHourPosition();
        if (hourPosition < 10000 || hourPosition >= 3595000) {
            ULONGLONG delay = hourPosition < 10000 ? 10000 - hourPosition : 3610000 - hourPosition;
            nextNtpAttemptTick = now + delay;
            return;
        }
    }
    ntpQueryRunning = true;
    if (hNtpThread != nullptr) {
        CloseHandle(hNtpThread);
        hNtpThread = nullptr;
    }
    ntpStopRequested = false;
    lastNtpAttemptTick = now;
    nextNtpAttemptTick = now + (ntpHasSynchronized ? 10ULL : 1ULL) * 60 * 1000;
    hNtpThread = StartNtpQueryThread(ntpServers, ntpGeneration.load(), hController,
        WM_NTP_RESULT, &ntpStopRequested, &ntpQueryRunning);
    if (hNtpThread == nullptr) {
        ntpQueryRunning = false;
        ntpLastQueryFailed = true;
    }
}

/// Requests NTP cancellation, waits up to three seconds, and releases pending result messages.
/// Returns whether the worker finished within the wait.
static bool StopNtpSynchronization() {
    ntpStopRequested = true;
    bool threadFinished = true;
    if (hNtpThread != nullptr) {
        DWORD waitResult = WaitForSingleObject(hNtpThread, 3000);
        threadFinished = waitResult == WAIT_OBJECT_0;
        CloseHandle(hNtpThread);
        hNtpThread = nullptr;
    }
    MSG pending = {};
    while (PeekMessageW(&pending, nullptr, WM_NTP_RESULT, WM_NTP_RESULT, PM_REMOVE)) {
        delete reinterpret_cast<NtpThreadResult*>(pending.lParam);
        ntpQueryRunning = false;
    }
    if (threadFinished) {
        ntpQueryRunning = false;
    }
    return threadFinished;
}

/// Returns the active NTP correction shared by widget display and time-signal scheduling, in FILETIME ticks.
static LONGLONG GetApplicationTimeOffset() {
    return useNtpTime && ntpTimeValid ? ntpOffset100Nanoseconds.load() : 0;
}

/// Returns system UTC adjusted by the last valid NTP offset when network time is enabled.
static void GetApplicationUtcTime(SYSTEMTIME* utc) {
    ULONGLONG value = static_cast<ULONGLONG>(static_cast<LONGLONG>(CurrentFileTimeValue()) + GetApplicationTimeOffset());
    FILETIME fileTime = {};
    ULARGE_INTEGER parts = {};
    parts.QuadPart = value;
    fileTime.dwLowDateTime = parts.LowPart;
    fileTime.dwHighDateTime = parts.HighPart;
    FileTimeToSystemTime(&fileTime, utc);
}

/// Converts application UTC to the widget's selected zone or UTC, then applies its millisecond offset.
/// Uses the current application time when applicationUtc is zero.
static void GetDisplayedTime(const WidgetConfig& config, SYSTEMTIME* displayed, ULONGLONG applicationUtc = 0) {
    SYSTEMTIME utc = {};
    if (applicationUtc == 0) {
        GetApplicationUtcTime(&utc);
    } else {
        ULARGE_INTEGER value = {};
        value.QuadPart = applicationUtc;
        FILETIME fileTime = { value.LowPart, value.HighPart };
        FileTimeToSystemTime(&fileTime, &utc);
    }
    if (config.showUtc) {
        *displayed = utc;
    } else {
        const DYNAMIC_TIME_ZONE_INFORMATION* selected = nullptr;
        for (size_t index = 0; index < timeZones.size(); index++) {
            if (_wcsicmp(timeZones[index].TimeZoneKeyName, config.timeZoneKey.c_str()) == 0) {
                selected = &timeZones[index];
                break;
            }
        }
        if (selected == nullptr || !ConvertUtcToTimeZone(*selected, utc, displayed)) {
            SystemTimeToTzSpecificLocalTime(nullptr, &utc, displayed);
        }
    }
    FILETIME fileTime = {};
    SystemTimeToFileTime(displayed, &fileTime);
    ULARGE_INTEGER value = {};
    value.LowPart = fileTime.dwLowDateTime;
    value.HighPart = fileTime.dwHighDateTime;
    LONGLONG adjusted = static_cast<LONGLONG>(value.QuadPart) + config.offsetMilliseconds * 10000;
    value.QuadPart = static_cast<ULONGLONG>(adjusted);
    fileTime.dwLowDateTime = value.LowPart;
    fileTime.dwHighDateTime = value.HighPart;
    FileTimeToSystemTime(&fileTime, displayed);
}

/// Converts SYSTEMTIME fields to FILETIME ticks without changing their time zone; returns zero on conversion failure.
static ULONGLONG SystemTimeValue(const SYSTEMTIME& time) {
    FILETIME fileTime = {};
    if (!SystemTimeToFileTime(&time, &fileTime)) {
        return 0;
    }
    ULARGE_INTEGER value = {};
    value.LowPart = fileTime.dwLowDateTime;
    value.HighPart = fileTime.dwHighDateTime;
    return value.QuadPart;
}

/// Clears the UI thread's tracked widget contributors to scheduled time signals.
static void ClearCurrentTimeSignalSources() {
    currentTimeSignalSources.clear();
}

/// Reports whether any listed widget still exists and has sound enabled.
static bool HasUnmutedTimeSignalSource(const std::vector<int>& widgetIds) {
    for (size_t index = 0; index < widgetIds.size(); index++) {
        Widget* widget = FindWidgetById(widgetIds[index]);
        if (widget != nullptr && !widget->config.soundsMuted) {
            return true;
        }
    }
    return false;
}

/// Mutes each shared sequence only when none of its regular or alarm contributors is audible.
static void UpdateCurrentTimeSignalMute() {
    for (const TimeSignalSourceGroup& group : currentTimeSignalSources) {
        bool audible = HasUnmutedTimeSignalSource(group.regularWidgetIds)
            || HasUnmutedTimeSignalSource(group.alarmWidgetIds);
        SetTimeSignalMuted(group.target, !audible);
    }
}

/// Tests a Windows day-of-week value against the alarm's Monday-based weekday mask.
static bool AlarmEnabledOnDay(const WidgetConfig& config, WORD dayOfWeek) {
    int mondayBasedDay = dayOfWeek == 0 ? 6 : dayOfWeek - 1;
    return (config.alarmDays & 1U << mondayBasedDay) != 0;
}

/// Returns a localized abbreviated weekday for a Monday-based index, using English abbreviations if formatting fails.
static std::wstring GetWeekdayAbbreviation(AppLanguage language, int mondayBasedDay) {
    SYSTEMTIME date = {};
    date.wYear = 2001;
    date.wMonth = 1;
    date.wDay = static_cast<WORD>(1 + std::clamp(mondayBasedDay, 0, ALARM_DAY_COUNT - 1));
    wchar_t text[32] = {};
    if (GetDateFormatEx(LANGUAGE_LOCALES[language], 0, &date, L"ddd", text, ARRAYSIZE(text), nullptr) > 0) {
        return text;
    }
    static const wchar_t* fallback[ALARM_DAY_COUNT] = {
        L"Mon",
        L"Tue",
        L"Wed",
        L"Thu",
        L"Fri",
        L"Sat",
        L"Sun"
    };
    return fallback[std::clamp(mondayBasedDay, 0, ALARM_DAY_COUNT - 1)];
}

/// Returns the locale's first weekday as a Monday-based index, defaulting to Monday.
static int GetCultureFirstAlarmDay(AppLanguage language) {
    wchar_t firstDayText[4] = {};
    if (GetLocaleInfoEx(LANGUAGE_LOCALES[language], LOCALE_IFIRSTDAYOFWEEK, firstDayText, ARRAYSIZE(firstDayText)) > 0) {
        int firstDay = _wtoi(firstDayText);
        if (firstDay >= 0 && firstDay < ALARM_DAY_COUNT) {
            return firstDay;
        }
    }
    return 0;
}

/// Builds a localized alarm menu caption with its time and any restricted weekdays in culture order.
static std::wstring AlarmMenuLabel(const WidgetConfig& config) {
    wchar_t time[16] = {};
    swprintf_s(time, L"%02d:%02d", config.alarmHour, config.alarmMinute);
    std::wstring label = TEXT[config.language][TXT_ALARM];
    label += L" ";
    label += time;
    unsigned int alarmDays = config.alarmDays & ALARM_DAYS_ALL;
    if (alarmDays != ALARM_DAYS_ALL) {
        label += L" (";
        bool first = true;
        int firstDay = GetCultureFirstAlarmDay(config.language);
        for (int position = 0; position < ALARM_DAY_COUNT; position++) {
            int day = (firstDay + position) % ALARM_DAY_COUNT;
            if ((alarmDays & 1U << day) == 0) {
                continue;
            }
            if (!first) {
                label += L", ";
            }
            label += GetWeekdayAbbreviation(config.language, day);
            first = false;
        }
        if (first) {
            label += L"–";
        }
        label += L")";
    }
    return label;
}

/// Schedules approaching regular and alarm GTS targets from each widget's displayed time, retaining fractional offsets.
/// Retimes existing sequences when the NTP correction changes, preserving their contributors and canceled alarms.
/// Groups identical targets and updates the shared mute state.
static void CheckTimeSignals() {
    ULONGLONG systemNow = CurrentFileTimeValue();
    LONGLONG applicationOffset = GetApplicationTimeOffset();
    LONGLONG adjustment = currentTimeSignalOffset - applicationOffset;
    if (adjustment != 0) {
        AdjustTimeSignalPlaybackTime(adjustment);
        for (TimeSignalSourceGroup& group : currentTimeSignalSources) {
            group.target = static_cast<ULONGLONG>(static_cast<LONGLONG>(group.target) + adjustment);
        }
        currentTimeSignalOffset = applicationOffset;
    }
    ULONGLONG applicationNow = static_cast<ULONGLONG>(static_cast<LONGLONG>(systemNow) + applicationOffset);
    for (auto group = currentTimeSignalSources.begin(); group != currentTimeSignalSources.end();) {
        if (group->target + 10000000 < systemNow) {
            group = currentTimeSignalSources.erase(group);
        } else {
            group++;
        }
    }
    std::vector<TimeSignalCandidate> candidates;
    for (size_t index = 0; index < widgets.size(); index++) {
        Widget* widget = widgets[index].get();
        int mode = static_cast<int>(widgets[index]->config.timeSignal);
        bool supportsSound = WidgetSupportsSound(widget->config.type);
        bool regularSignal = supportsSound && mode > TIME_SIGNAL_NONE && mode < TIME_SIGNAL_COUNT;
        bool alarmSignal = supportsSound && widget->config.alarmEnabled && widget->config.alarmTimeSignal;
        if (!regularSignal && !alarmSignal) {
            continue;
        }
        SYSTEMTIME displayed = {};
        GetDisplayedTime(widget->config, &displayed, applicationNow);
        ULONGLONG displayedValue = SystemTimeValue(displayed);
        if (displayedValue == 0) {
            continue;
        }
        displayedValue += applicationNow % 10000;
        ULONGLONG target = 0;
        if (regularSignal && CalculateTimeSignalTarget(displayedValue, systemNow,
            static_cast<TimeSignalMode>(mode), &target)) {
            candidates.push_back(TimeSignalCandidate{
                target,
                true,
                widget->config.id
            });
        }
        if (alarmSignal && CalculateAlarmTimeSignalTarget(displayedValue, systemNow,
            widget->config.alarmHour, widget->config.alarmMinute, &target)) {
            bool enabledOnTargetDay = false;
            if (target >= systemNow) {
                ULARGE_INTEGER targetDisplayedValue = {};
                targetDisplayedValue.QuadPart = displayedValue + target - systemNow;
                FILETIME targetDisplayedFileTime = {};
                targetDisplayedFileTime.dwLowDateTime = targetDisplayedValue.LowPart;
                targetDisplayedFileTime.dwHighDateTime = targetDisplayedValue.HighPart;
                SYSTEMTIME targetDisplayedTime = {};
                enabledOnTargetDay = FileTimeToSystemTime(&targetDisplayedFileTime, &targetDisplayedTime)
                    && AlarmEnabledOnDay(widget->config, targetDisplayedTime.wDayOfWeek);
            }
            if (enabledOnTargetDay) {
                candidates.push_back(TimeSignalCandidate{
                    target,
                    false,
                    widget->config.id
                });
            }
        }
    }
    for (auto group = currentTimeSignalSources.begin(); group != currentTimeSignalSources.end();) {
        bool shouldCancel = group->target > systemNow + 5 * 10000000ULL;
        if (shouldCancel) {
            for (const TimeSignalCandidate& candidate : candidates) {
                if (candidate.target == group->target) {
                    shouldCancel = false;
                    break;
                }
            }
        }
        if (shouldCancel) {
            CancelTimeSignalPlayback(group->target);
            group = currentTimeSignalSources.erase(group);
        } else {
            group++;
        }
    }
    for (const TimeSignalCandidate& candidate : candidates) {
        auto existing = currentTimeSignalSources.begin();
        while (existing != currentTimeSignalSources.end()) {
            if (candidate.target == existing->target) {
                break;
            }
            existing++;
        }
        if (existing == currentTimeSignalSources.end() || adjustment != 0) {
            if (!StartTimeSignalPlayback(candidate.target, true, generatedTimeSignal,
                timeSignalVolume, hController, WM_TIME_SIGNAL_FINISHED)) {
                continue;
            }
            if (existing == currentTimeSignalSources.end()) {
                currentTimeSignalSources.push_back(TimeSignalSourceGroup{ candidate.target });
                existing = currentTimeSignalSources.end() - 1;
            }
        }
        auto cancelledAlarmWidget = std::find(existing->cancelledAlarmWidgetIds.begin(),
            existing->cancelledAlarmWidgetIds.end(), candidate.widgetId);
        if (!candidate.regular && cancelledAlarmWidget != existing->cancelledAlarmWidgetIds.end()) {
            continue;
        }
        std::vector<int>& sourceIds = candidate.regular ? existing->regularWidgetIds : existing->alarmWidgetIds;
        if (std::find(sourceIds.begin(), sourceIds.end(), candidate.widgetId) == sourceIds.end()) {
            sourceIds.push_back(candidate.widgetId);
        }
    }
    UpdateCurrentTimeSignalMute();
}

/// Replaces the widget's date-copy tooltip and displays it briefly near the pointer.
static void ShowCopiedDateTooltip(Widget* widget, const std::wstring& text) {
    if (widget == nullptr || widget->window == nullptr) {
        return;
    }
    if (widget->copyTooltip != nullptr && IsWindow(widget->copyTooltip)) {
        DestroyWindow(widget->copyTooltip);
    }
    widget->copyTooltipText = text;
    widget->copyTooltip = CreateWindowExW(WS_EX_TOPMOST, TOOLTIPS_CLASSW, nullptr,
        WS_POPUP | TTS_ALWAYSTIP | TTS_NOPREFIX, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, widget->window, nullptr, hInstance, nullptr);
    if (widget->copyTooltip == nullptr) {
        return;
    }
    TOOLINFOW information = {};
    information.cbSize = sizeof(information);
    information.uFlags = TTF_TRACK | TTF_ABSOLUTE;
    information.hwnd = widget->window;
    information.uId = 1;
    information.lpszText = const_cast<wchar_t*>(widget->copyTooltipText.c_str());
    SendMessageW(widget->copyTooltip, TTM_ADDTOOLW, 0, reinterpret_cast<LPARAM>(&information));
    POINT cursor = {};
    GetCursorPos(&cursor);
    SendMessageW(widget->copyTooltip, TTM_TRACKPOSITION, 0, MAKELPARAM(cursor.x + 12, cursor.y + 20));
    SendMessageW(widget->copyTooltip, TTM_TRACKACTIVATE, TRUE, reinterpret_cast<LPARAM>(&information));
    widget->copyTooltipEndTick = GetTickCount64() + 1400;
}

/// Replaces clipboard contents with Unicode text, transferring the allocation to Windows only on success.
static bool CopyTextToClipboard(HWND owner, const std::wstring& text) {
    SIZE_T bytes = (text.size() + 1) * sizeof(wchar_t);
    HGLOBAL memory = GlobalAlloc(GMEM_MOVEABLE, bytes);
    if (memory == nullptr) {
        return false;
    }
    void* target = GlobalLock(memory);
    if (target == nullptr) {
        GlobalFree(memory);
        return false;
    }
    CopyMemory(target, text.c_str(), bytes);
    GlobalUnlock(memory);
    if (!OpenClipboard(owner)) {
        GlobalFree(memory);
        return false;
    }
    EmptyClipboard();
    bool copied = SetClipboardData(CF_UNICODETEXT, memory) != nullptr;
    if (!copied) {
        GlobalFree(memory);
    }
    CloseClipboard();
    return copied;
}

/// Formats and copies a calendar date, showing a confirmation tooltip only after a successful clipboard update.
static void CopyWidgetDate(Widget* widget, const SYSTEMTIME& date) {
    if (widget == nullptr) {
        return;
    }
    std::wstring text = FormatWidgetDate(widget->config, date, widget->config.dateCopyFormat);
    if (CopyTextToClipboard(widget->window, text)) {
        ShowCopiedDateTooltip(widget, text);
    }
}

/// Measures a native calendar for the widget's locale, font, theme, and display options, caching matching results.
static SIZE GetCalendarSize(const WidgetConfig& config, bool borderless) {
    static std::vector<CalendarSizeEntry> cache;
    bool disabledThemes = themesDisabled || config.disableThemes;
    bool showToday = config.type != WIDGET_PANEL && (config.type != WIDGET_CALENDAR || config.showToday);
    for (size_t index = 0; index < cache.size(); index++) {
        const CalendarSizeEntry& entry = cache[index];
        bool matches = entry.language == config.language
            && entry.weekNumbers == config.weekNumbers
            && entry.borderless == borderless
            && entry.showToday == showToday
            && entry.themesDisabled == disabledThemes
            && entry.fontAntialiasing == config.fontAntialiasing
            && entry.fontWeight == config.fontWeight
            && entry.fontItalic == config.fontItalic
            && entry.fontCharSet == config.fontCharSet
            && entry.fontFace == config.fontFace;
        if (matches) {
            return entry.size;
        }
    }
    SIZE size = {
        config.weekNumbers ? 250 : 227,
        160
    };
    DWORD style = WS_POPUP | (config.weekNumbers ? MCS_WEEKNUMBERS : 0);
    if (!showToday) {
        style |= MCS_NOTODAY;
    }
    CalendarLocaleScope localeScope(LANGUAGE_LOCALES[config.language]);
    HWND calendar = CreateWindowExW(0, MONTHCAL_CLASSW, L"", style, 0, 0, 0, 0, nullptr, nullptr, hInstance, nullptr);
    if (calendar != nullptr) {
        const wchar_t* themeName = disabledThemes ? L"" : nullptr;
        SetWindowTheme(calendar, themeName, themeName);
        if (borderless) {
            MonthCal_SetCalendarBorder(calendar, TRUE, 0);
        }
        HFONT font = CreateCalendarUiFont(config);
        if (font != nullptr) {
            SendMessageW(calendar, WM_SETFONT, reinterpret_cast<WPARAM>(font), FALSE);
        }
        RECT minimum = {};
        if (MonthCal_GetMinReqRect(calendar, &minimum)) {
            size.cx = minimum.right - minimum.left;
            size.cy = minimum.bottom - minimum.top;
        }
        DestroyWindow(calendar);
        if (font != nullptr) {
            DeleteObject(font);
        }
    }
    cache.push_back(CalendarSizeEntry{
        config.language,
        config.weekNumbers,
        borderless,
        showToday,
        disabledThemes,
        config.fontAntialiasing,
        config.fontWeight,
        config.fontItalic,
        config.fontCharSet,
        config.fontFace, size
    });
    return size;
}

/// Returns the pixel inset reserved for a selected border style.
static int GetBorderStyleInset(int borderStyle) {
    if (borderStyle == DIGITAL_BORDER_NONE) {
        return 0;
    }
    if (borderStyle == DIGITAL_BORDER_TOOL_WINDOW) {
        return 1;
    }
    if (borderStyle == DIGITAL_BORDER_3D) {
        return 4;
    }
    return 2;
}

/// Adds the native window and extended style bits required by the selected border style.
static void ApplyNativeBorderStyle(int borderStyle, DWORD* style, DWORD* extendedStyle) {
    if (borderStyle == DIGITAL_BORDER_NONE) {
        return;
    }
    *style |= WS_BORDER;
    if (borderStyle == DIGITAL_BORDER_SINGLE) {
        *extendedStyle |= WS_EX_DLGMODALFRAME;
    } else if (borderStyle == DIGITAL_BORDER_3D) {
        *extendedStyle |= WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE;
    }
}

/// Reports whether this widget uses a native thin frame whose color is painted by the application.
static bool UsesConfigurableNativeFrame(const Widget* widget) {
    if (widget == nullptr || widget->config.borderStyle != DIGITAL_BORDER_TOOL_WINDOW) {
        return false;
    }
    return widget->config.type == WIDGET_CALENDAR
        || widget->config.type == WIDGET_PANEL
        || widget->config.type == WIDGET_DIGITAL && !widget->config.transparentBackground;
}

/// Measures a stable time-text extent using the widest digit and applicable AM/PM markers in the selected GDI font.
static SIZE MeasureClockTime(HDC dc, const WidgetConfig& config, SYSTEMTIME time) {
    wchar_t widestDigit = L'0';
    LONG digitWidth = 0;
    for (wchar_t digit = L'0'; digit <= L'9'; digit++) {
        SIZE extent = {};
        if (GetTextExtentPoint32W(dc, &digit, 1, &extent) && extent.cx > digitWidth) {
            widestDigit = digit;
            digitWidth = extent.cx;
        }
    }
    SIZE maximum = {};
    int samples = config.showAmPm && WidgetUsesTwelveHourTime(config) ? 2 : 1;
    for (int index = 0; index < samples; index++) {
        std::wstring sample = FormatWidgetTime(config, time);
        for (wchar_t& character : sample) {
            if (character >= L'0' && character <= L'9') {
                character = widestDigit;
            }
        }
        if (config.showUtc && config.showUtcText) {
            sample += L" UTC";
        }
        SIZE extent = {};
        if (GetTextExtentPoint32W(dc, sample.c_str(), static_cast<int>(sample.size()), &extent)) {
            maximum.cx = std::max(maximum.cx, extent.cx);
            maximum.cy = std::max(maximum.cy, extent.cy);
        }
        time.wHour = (time.wHour + 12) % 24;
    }
    return maximum;
}

/// Formats the localized name or visibility caption for a zero-based additional-clock index.
static std::wstring AdditionalClockLabel(AppLanguage language, int index, bool show) {
    const wchar_t* format = show ? ADDITIONAL_CLOCK_SHOW_FORMATS[language] : ADDITIONAL_CLOCK_NAME_FORMATS[language];
    wchar_t text[128] = {};
    swprintf_s(text, format, index + 1);
    return text;
}

/// Returns an additional clock's custom name, or its localized default name when empty.
static std::wstring AdditionalClockName(const WidgetConfig& config, int index) {
    const std::wstring& name = config.additionalClocks[index].name;
    return name.empty() ? AdditionalClockLabel(config.language, index, false) : name;
}

/// Reports whether either optional panel clock is enabled.
static bool HasAdditionalClocks(const WidgetConfig& config) {
    for (const AdditionalClockConfig& clock : config.additionalClocks) {
        if (clock.enabled) {
            return true;
        }
    }
    return false;
}

/// Derives a panel clock configuration with its own time zone and size and with seconds and explicit UTC text disabled.
static WidgetConfig AdditionalClockConfiguration(const WidgetConfig& config, int index) {
    WidgetConfig clock = config;
    clock.showSeconds = false;
    clock.showUtc = false;
    clock.showUtcText = false;
    clock.timeZoneKey = config.additionalClocks[index].timeZoneKey;
    if (clock.timeZoneKey.empty()) {
        clock.timeZoneKey = config.timeZoneKey;
    }
    clock.size = NormalizeAnalogClockSize(config.additionalClocks[index].size);
    return clock;
}

/// Calculates the width needed by a panel clock's face and stable time-text measurement.
static int GetPanelClockGroupWidth(const WidgetConfig& config) {
    int width = config.size;
    HDC screen = GetDC(nullptr);
    HFONT font = CreatePanelFont(config.panelTimeFont, config.fontAntialiasing);
    if (screen != nullptr && font != nullptr) {
        HGDIOBJ previous = SelectObject(screen, font);
        SYSTEMTIME sample = {};
        sample.wHour = 23;
        sample.wMinute = 58;
        sample.wSecond = 58;
        SIZE extent = MeasureClockTime(screen, config, sample);
        width = std::max(width, static_cast<int>(extent.cx) + 4);
        SelectObject(screen, previous);
    }
    if (font != nullptr) {
        DeleteObject(font);
    }
    if (screen != nullptr) {
        ReleaseDC(nullptr, screen);
    }
    return width;
}

/// Measures panel fonts and enabled clocks and calculates all child rectangles and the required client size.
static PanelLayout CalculatePanelLayout(const WidgetConfig& config) {
    PanelLayout layout;
    SIZE calendarSize = GetCalendarSize(config, true);
    bool additional = HasAdditionalClocks(config);
    int lineHeight = 25;
    int nameHeight = 24;
    int timeTextHeight = 21;
    int footerTextHeight = 24;
    int footerHeight = 28;
    int weekdayWidth = 0;
    HDC dc = GetDC(nullptr);
    HFONT font = CreatePanelFont(config.panelTimeFont, config.fontAntialiasing);
    if (dc != nullptr && font != nullptr) {
        HGDIOBJ oldFont = SelectObject(dc, font);
        TEXTMETRICW metrics = {};
        if (GetTextMetricsW(dc, &metrics)) {
            timeTextHeight = static_cast<int>(metrics.tmHeight);
            lineHeight = std::max(lineHeight, timeTextHeight + 4);
        }
        if (additional) {
            SYSTEMTIME date = {
                2026,
                9,
                0,
                1,
                0,
                0,
                0,
                0
            };
            for (int day = 1; day <= 7; day++) {
                date.wDay = static_cast<WORD>(day);
                wchar_t text[128] = {};
                GetDateFormatEx(LANGUAGE_LOCALES[config.language], 0, &date, L"dddd", text, ARRAYSIZE(text), nullptr);
                SIZE extent = {};
                GetTextExtentPoint32W(dc, text, static_cast<int>(wcslen(text)), &extent);
                weekdayWidth = std::max(weekdayWidth, static_cast<int>(extent.cx) + 4);
            }
        }
        SelectObject(dc, oldFont);
    }
    if (font != nullptr) {
        DeleteObject(font);
    }
    font = CreatePanelFont(config.panelTopFont, config.fontAntialiasing);
    if (dc != nullptr && font != nullptr) {
        HGDIOBJ oldFont = SelectObject(dc, font);
        TEXTMETRICW metrics = {};
        if (GetTextMetricsW(dc, &metrics)) {
            nameHeight = std::max(nameHeight, static_cast<int>(metrics.tmHeight) + 4);
        }
        SelectObject(dc, oldFont);
    }
    if (font != nullptr) {
        DeleteObject(font);
    }
    font = CreatePanelFont(config.panelBottomFont, config.fontAntialiasing);
    if (dc != nullptr && font != nullptr) {
        HGDIOBJ oldFont = SelectObject(dc, font);
        TEXTMETRICW metrics = {};
        if (GetTextMetricsW(dc, &metrics)) {
            footerTextHeight = static_cast<int>(metrics.tmHeight);
            footerHeight = std::max(footerHeight, footerTextHeight + 4);
        }
        SelectObject(dc, oldFont);
    }
    if (font != nullptr) {
        DeleteObject(font);
    }
    if (dc != nullptr) {
        ReleaseDC(nullptr, dc);
    }
    int clockHeight = config.size;
    for (const AdditionalClockConfig& clock : config.additionalClocks) {
        if (clock.enabled) {
            clockHeight = std::max(clockHeight, NormalizeAnalogClockSize(clock.size) + nameHeight);
        }
    }
    int groupHeight = clockHeight + 2 + lineHeight;
    if (additional) {
        groupHeight += lineHeight;
    }
    int contentHeight = std::max(static_cast<int>(calendarSize.cy), groupHeight);
    int calendarTop = 35 + (contentHeight - calendarSize.cy) / 2 + PANEL_CALENDAR_OFFSET_Y;
    layout.calendar = RECT{
        PANEL_SIDE_PADDING,
        calendarTop,
        PANEL_SIDE_PADDING + calendarSize.cx,
        calendarTop + calendarSize.cy
    };
    int clockBottom = 35 + (contentHeight - groupHeight) / 2 + clockHeight;
    int left = layout.calendar.right + 12;
    for (int index = 0; index <= ADDITIONAL_CLOCK_COUNT; index++) {
        if (index > 0 && !config.additionalClocks[index - 1].enabled) {
            continue;
        }
        WidgetConfig clock = index == 0 ? config : AdditionalClockConfiguration(config, index - 1);
        int width = std::max(GetPanelClockGroupWidth(clock), weekdayWidth);
        int clockLeft = left + (width - clock.size) / 2;
        layout.clocks[index] = RECT{
            clockLeft,
            clockBottom - clock.size,
            clockLeft + clock.size,
            clockBottom
        };
        layout.times[index] = RECT{
            left,
            clockBottom + 2,
            left + width,
            clockBottom + 2 + lineHeight
        };
        if (additional) {
            layout.days[index] = RECT{
                left,
                layout.times[index].bottom - 2,
                left + width,
                layout.times[index].bottom + lineHeight - 2
            };
        }
        if (index > 0) {
            layout.names[index - 1] = RECT{
                left,
                clockBottom - clock.size - nameHeight - 2,
                left + width,
                clockBottom - clock.size - 2
            };
        }
        left += width + 12;
    }
    layout.clientSize.cx = left - 12 + PANEL_SIDE_PADDING;
    int footerTop = 35 + contentHeight + 4;
    if (additional) {
        int rowGap = lineHeight - timeTextHeight - 2;
        int dayTextBottom = layout.days[0].top + (lineHeight - timeTextHeight) / 2 + timeTextHeight;
        int footerTextOffset = (footerHeight - footerTextHeight) / 2;
        footerTop = std::max(static_cast<int>(layout.calendar.bottom) + 4, dayTextBottom + rowGap - footerTextOffset);
    }
    layout.footer = RECT{
        PANEL_SIDE_PADDING,
        footerTop,
        layout.clientSize.cx - PANEL_SIDE_PADDING,
        footerTop + footerHeight
    };
    layout.clientSize.cy = layout.footer.bottom + 7;
    return layout;
}

/// Calculates outer widget dimensions from its type, content, font, padding, border, and selected monitor.
static void GetWidgetDimensions(const WidgetConfig& config, int* width, int* height) {
    if (config.type == WIDGET_FULLSCREEN) {
        RECT monitorRect = {};
        if (GetPrimarySelectedMonitorRect(config, &monitorRect)) {
            *width = monitorRect.right - monitorRect.left;
            *height = monitorRect.bottom - monitorRect.top;
        } else {
            *width = GetSystemMetrics(SM_CXSCREEN);
            *height = GetSystemMetrics(SM_CYSCREEN);
        }
        return;
    }
    bool borderlessCalendar = config.type == WIDGET_PANEL || config.type == WIDGET_CALENDAR;
    SIZE calendarSize = GetCalendarSize(config, borderlessCalendar);
    if (config.type == WIDGET_ANALOG) {
        *width = config.size;
        *height = config.size;
    } else if (config.type == WIDGET_DIGITAL) {
        SYSTEMTIME sample = {};
        sample.wHour = 23;
        sample.wMinute = 58;
        sample.wSecond = 58;
        SIZE extent = {};
        TEXTMETRICW metrics = {};
        HDC screen = GetDC(nullptr);
        HFONT font = CreateWidgetDrawingFont(config);
        if (screen != nullptr && font != nullptr) {
            HGDIOBJ oldFont = SelectObject(screen, font);
            extent = MeasureClockTime(screen, config, sample);
            GetTextMetricsW(screen, &metrics);
            SelectObject(screen, oldFont);
        }
        if (font != nullptr) {
            DeleteObject(font);
        }
        if (screen != nullptr) {
            ReleaseDC(nullptr, screen);
        }
        int borderInset = config.transparentBackground ? GetBorderStyleInset(config.borderStyle) : 0;
        int inset = config.padding + borderInset + config.borderWidth;
        *width = std::max(1, static_cast<int>(extent.cx) + inset * 2 + 4);
        *height = std::max(38, std::max(static_cast<int>(extent.cy), static_cast<int>(metrics.tmHeight)) + inset * 2 + 4);
        if (!config.transparentBackground) {
            DWORD style = WS_POPUP;
            DWORD extendedStyle = WS_EX_TOOLWINDOW;
            ApplyNativeBorderStyle(config.borderStyle, &style, &extendedStyle);
            RECT rect = {
                0,
                0,
                *width,
                *height
            };
            if (AdjustWindowRectEx(&rect, style, FALSE, extendedStyle)) {
                *width = rect.right - rect.left;
                *height = rect.bottom - rect.top;
            }
        }
    } else if (config.type == WIDGET_CALENDAR) {
        *width = calendarSize.cx;
        *height = calendarSize.cy;
    } else {
        PanelLayout layout = CalculatePanelLayout(config);
        *width = layout.clientSize.cx;
        *height = layout.clientSize.cy;
    }
    if (config.type == WIDGET_CALENDAR || config.type == WIDGET_PANEL) {
        DWORD style = WS_POPUP | WS_CLIPCHILDREN;
        DWORD extendedStyle = WS_EX_TOOLWINDOW;
        ApplyNativeBorderStyle(config.borderStyle, &style, &extendedStyle);
        RECT rect = {
            0,
            0,
            *width,
            *height
        };
        if (AdjustWindowRectEx(&rect, style, FALSE, extendedStyle)) {
            *width = rect.right - rect.left;
            *height = rect.bottom - rect.top;
        }
    }
}

/// Calculates a resized window's position relative to its current monitor's work-area edges.
/// Returns false when snapping is disabled or the window, output, or monitor geometry is unavailable.
static bool GetPositionPreservingWorkAreaAttachment(HWND window, int newWidth, int newHeight, POINT* position,
    bool* horizontalAttachment = nullptr, bool* verticalAttachment = nullptr) {
    if (!snapWidgetsToWorkArea || window == nullptr || position == nullptr) {
        return false;
    }
    RECT rect = {};
    if (!GetWindowRect(window, &rect)) {
        return false;
    }
    HMONITOR monitor = MonitorFromRect(&rect, MONITOR_DEFAULTTONEAREST);
    MONITORINFO information = {
        sizeof(information)
    };
    if (monitor == nullptr || !GetMonitorInfoW(monitor, &information)) {
        return false;
    }
    *position = PreserveWidgetWorkAreaAttachment(rect, information.rcWork, newWidth, newHeight,
        WORK_AREA_SNAP_DISTANCE, horizontalAttachment, verticalAttachment);
    return true;
}

/// Resizes a live widget while retaining nearby work-area edge attachments and updating its stored position.
static void ResizeWidgetPreservingWorkAreaAttachment(Widget* widget, int width, int height, UINT flags) {
    if (widget == nullptr || widget->window == nullptr) {
        return;
    }
    POINT position = {
        widget->config.x,
        widget->config.y
    };
    if (GetPositionPreservingWorkAreaAttachment(widget->window, width, height, &position)) {
        widget->config.x = position.x;
        widget->config.y = position.y;
        flags &= ~SWP_NOMOVE;
    }
    SetWindowPos(widget->window, nullptr, position.x, position.y, width, height, flags);
}

/// Copies the requested calendar, primary clock, and time-text rectangles from the calculated panel layout.
static void GetPanelLayout(const WidgetConfig& config, RECT* calendarRect, POINT* clockPosition, RECT* timeRect) {
    PanelLayout layout = CalculatePanelLayout(config);
    if (calendarRect != nullptr) {
        *calendarRect = layout.calendar;
    }
    if (clockPosition != nullptr) {
        *clockPosition = POINT{ layout.clocks[0].left, layout.clocks[0].top };
    }
    if (timeRect != nullptr) {
        *timeRect = layout.times[0];
    }
}

/// Moves the configured position inside the nearest work area, or monitor bounds for fullscreen widgets.
static void ClampWidgetPosition(WidgetConfig* config) {
    int width = 0;
    int height = 0;
    GetWidgetDimensions(*config, &width, &height);
    RECT desired = {
        config->x,
        config->y,
        config->x + width,
        config->y + height
    };
    HMONITOR monitor = MonitorFromRect(&desired, MONITOR_DEFAULTTONEAREST);
    MONITORINFO information = {};
    information.cbSize = sizeof(information);
    if (monitor == nullptr || !GetMonitorInfoW(monitor, &information)) {
        return;
    }
    int workLeft = static_cast<int>(information.rcWork.left);
    int workTop = static_cast<int>(information.rcWork.top);
    int workRight = static_cast<int>(information.rcWork.right);
    int workBottom = static_cast<int>(information.rcWork.bottom);
    config->x = width >= workRight - workLeft ? workLeft : std::clamp(config->x, workLeft, workRight - width);
    config->y = height >= workBottom - workTop ? workTop : std::clamp(config->y, workTop, workBottom - height);
}

/// Constrains a saved form position to the nearest work area while preserving CW_USEDEFAULT coordinates.
static void ClampFormPosition(int* x, int* y, int width, int height) {
    if (*x == CW_USEDEFAULT || *y == CW_USEDEFAULT) {
        return;
    }
    RECT desired = {
        *x,
        *y,
        *x + width,
        *y + height
    };
    HMONITOR monitor = MonitorFromRect(&desired, MONITOR_DEFAULTTONEAREST);
    MONITORINFO information = {};
    information.cbSize = sizeof(information);
    if (monitor == nullptr || !GetMonitorInfoW(monitor, &information)) {
        return;
    }
    int workLeft = static_cast<int>(information.rcWork.left);
    int workTop = static_cast<int>(information.rcWork.top);
    int workRight = static_cast<int>(information.rcWork.right);
    int workBottom = static_cast<int>(information.rcWork.bottom);
    *x = std::clamp(*x, workLeft, std::max(workLeft, workRight - width));
    *y = std::clamp(*y, workTop, std::max(workTop, workBottom - height));
}

/// Captures the form's screen position, using and translating its normal placement when minimized.
static void SaveFormPosition(HWND window, int* x, int* y) {
    if (window == nullptr) {
        return;
    }
    RECT rect = {};
    if (IsIconic(window)) {
        WINDOWPLACEMENT placement = {};
        placement.length = sizeof(placement);
        if (!GetWindowPlacement(window, &placement)) {
            return;
        }
        rect = placement.rcNormalPosition;
        bool toolWindow = GetWindowLongPtrW(window, GWL_EXSTYLE) & WS_EX_TOOLWINDOW;
        if (!toolWindow) {
            HMONITOR monitor = MonitorFromWindow(window, MONITOR_DEFAULTTONEAREST);
            MONITORINFO information = {};
            information.cbSize = sizeof(information);
            if (!GetMonitorInfoW(monitor, &information)) {
                return;
            }
            OffsetRect(&rect, information.rcWork.left - information.rcMonitor.left,
                information.rcWork.top - information.rcMonitor.top);
        }
    } else if (!GetWindowRect(window, &rect)) {
        return;
    }
    *x = rect.left;
    *y = rect.top;
}

/// Returns the Windows message-font face, falling back to the stock GUI font or an empty string.
static std::wstring GetSystemMessageFontFace() {
    NONCLIENTMETRICSW metrics = {};
    metrics.cbSize = sizeof(metrics);
    if (SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof(metrics), &metrics, 0)
            && metrics.lfMessageFont.lfFaceName[0] != L'\0') {
        return metrics.lfMessageFont.lfFaceName;
    }
    HFONT fallbackFont = static_cast<HFONT>(GetStockObject(DEFAULT_GUI_FONT));
    LOGFONTW fallback = {};
    if (fallbackFont != nullptr
            && GetObjectW(fallbackFont, sizeof(fallback), &fallback) == sizeof(fallback)
            && fallback.lfFaceName[0] != L'\0') {
        return fallback.lfFaceName;
    }
    return std::wstring();
}

/// Maps a stored antialiasing mode to the corresponding GDI font quality.
static BYTE FontQuality(int fontAntialiasing) {
    switch (fontAntialiasing) {
        case FONT_ANTIALIAS_CLEARTYPE:
            return CLEARTYPE_QUALITY;
        case FONT_ANTIALIAS_NONE:
            return NONANTIALIASED_QUALITY;
        default:
            return ANTIALIASED_QUALITY;
    }
}

/// Maps a stored antialiasing mode to ClearType, grayscale, or aliased Direct2D text rendering.
static D2D1_TEXT_ANTIALIAS_MODE DirectWriteAntialiasMode(int fontAntialiasing) {
    switch (fontAntialiasing) {
        case FONT_ANTIALIAS_CLEARTYPE:
            return D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE;
        case FONT_ANTIALIAS_NONE:
            return D2D1_TEXT_ANTIALIAS_MODE_ALIASED;
        default:
            return D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE;
    }
}

/// Creates a calendar font from system message-font metrics and widget face and style settings.
/// Returns null on failure; the caller owns the returned GDI font.
static HFONT CreateCalendarUiFont(const WidgetConfig& config) {
    NONCLIENTMETRICSW metrics = {};
    metrics.cbSize = sizeof(metrics);
    if (!SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof(metrics), &metrics, 0)) {
        return nullptr;
    }
    metrics.lfMessageFont.lfWeight = config.fontWeight;
    metrics.lfMessageFont.lfItalic = config.fontItalic;
    metrics.lfMessageFont.lfQuality = FontQuality(config.fontAntialiasing);
    if (!config.fontFace.empty()) {
        wcsncpy_s(metrics.lfMessageFont.lfFaceName, config.fontFace.c_str(), _TRUNCATE);
        metrics.lfMessageFont.lfCharSet = config.fontCharSet;
    }
    return CreateFontIndirectW(&metrics.lfMessageFont);
}

/// Refreshes the application font caption and whether restoring the default font is available.
static void UpdateApplicationFontButtons() {
    if (hAppFontButton != nullptr) {
        std::wstring caption = settingsAppFontFace.empty()
            ? SYSTEM_DEFAULT_FONT_LABELS[appLanguage]
            : settingsAppFontFace;
        caption += L"…";
        SetWindowTextW(hAppFontButton, caption.c_str());
    }
    if (hAppFontDefaultButton != nullptr) {
        EnableWindow(hAppFontDefaultButton, !settingsAppFontFace.empty()
            || settingsAppFontWeight != FW_NORMAL
            || settingsAppFontItalic
            || settingsAppFontDialogSize != 90);
    }
}

/// Deletes the cached application GDI font and clears its handle.
static void ResetUiFont() {
    if (hUiFont != nullptr) {
        DeleteObject(hUiFont);
        hUiFont = nullptr;
    }
}

/// Marks a matching font as found and stops font enumeration.
static int CALLBACK FindFontCallback(const LOGFONTW*, const TEXTMETRICW*, DWORD, LPARAM parameter) {
    *reinterpret_cast<bool*>(parameter) = true;
    return 0;
}

/// Tests whether GDI can enumerate the requested font family.
static bool IsFontAvailable(const wchar_t* face) {
    HDC screen = GetDC(nullptr);
    if (screen == nullptr) {
        return false;
    }
    LOGFONTW font = {};
    font.lfCharSet = DEFAULT_CHARSET;
    wcsncpy_s(font.lfFaceName, face, _TRUNCATE);
    bool found = false;
    EnumFontFamiliesExW(screen, &font, FindFontCallback, reinterpret_cast<LPARAM>(&found), 0);
    ReleaseDC(nullptr, screen);
    return found;
}

/// Creates the About license font with an available monospaced face and a Courier New fallback.
/// The caller owns the returned GDI font, which may be null on failure.
static HFONT CreateAboutFont() {
    NONCLIENTMETRICSW metrics = {};
    metrics.cbSize = sizeof(metrics);
    LOGFONTW font = {};
    if (SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof(metrics), &metrics, 0)) {
        font = metrics.lfMessageFont;
    } else {
        font.lfHeight = -12;
        font.lfCharSet = DEFAULT_CHARSET;
    }
    HDC screen = GetDC(nullptr);
    int dpi = screen == nullptr ? 96 : GetDeviceCaps(screen, LOGPIXELSY);
    if (screen != nullptr) {
        ReleaseDC(nullptr, screen);
    }
    font.lfHeight = -MulDiv(825, dpi > 0 ? dpi : 96, 7200);
    font.lfWidth = 0;
    font.lfWeight = FW_NORMAL;
    font.lfItalic = FALSE;
    font.lfUnderline = FALSE;
    font.lfStrikeOut = FALSE;
    font.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;
    const wchar_t* face = IsFontAvailable(L"Consolas") ? L"Consolas" : L"Courier New";
    wcsncpy_s(font.lfFaceName, face, _TRUNCATE);
    HFONT result = CreateFontIndirectW(&font);
    if (result == nullptr && wcscmp(face, L"Courier New") != 0) {
        wcsncpy_s(font.lfFaceName, L"Courier New", _TRUNCATE);
        result = CreateFontIndirectW(&font);
    }
    return result;
}

/// Applies draft application font choices to open forms while retaining committed settings for restoration.
static void ApplyApplicationFontPreview() {
    std::wstring savedFace = appFontFace;
    int savedWeight = appFontWeight;
    bool savedItalic = appFontItalic;
    HFONT previousFont = hUiFont;
    appFontFace = settingsAppFontFace;
    appFontWeight = settingsAppFontWeight;
    appFontItalic = settingsAppFontItalic;
    hUiFont = nullptr;
    if (hSettings != nullptr) {
        ApplyUiStyle(hSettings);
    }
    if (hHelp != nullptr) {
        ApplyUiStyle(hHelp);
    }
    if (hAbout != nullptr) {
        ApplyUiStyle(hAbout);
    }
    appFontFace = savedFace;
    appFontWeight = savedWeight;
    appFontItalic = savedItalic;
    if (hUiFont != nullptr && previousFont != nullptr) {
        DeleteObject(previousFont);
    } else if (hUiFont == nullptr) {
        hUiFont = previousFont;
    }
    settingsApplicationFontPreviewActive = true;
}

/// Restores committed application fonts after a preview and releases the temporary font when replaced.
static void RestoreApplicationFontPreview() {
    if (!settingsApplicationFontPreviewActive) {
        return;
    }
    HFONT previewFont = hUiFont;
    hUiFont = nullptr;
    if (hSettings != nullptr) {
        ApplyUiStyle(hSettings);
    }
    if (hHelp != nullptr) {
        ApplyUiStyle(hHelp);
    }
    if (hAbout != nullptr) {
        ApplyUiStyle(hAbout);
    }
    if (hUiFont != nullptr && previewFont != nullptr) {
        DeleteObject(previewFont);
    } else if (hUiFont == nullptr) {
        hUiFont = previewFont;
    }
    settingsApplicationFontPreviewActive = false;
}

/// Applies the current UI font and theme policy to a child, preserving the separate About license font.
static BOOL CALLBACK ApplyFontAndTheme(HWND child, LPARAM) {
    HFONT font = GetParent(child) == hAbout && GetDlgCtrlID(child) == ID_INFO_TEXT && hAboutFont != nullptr
        ? hAboutFont
        : hUiFont;
    if (font != nullptr) {
        SendMessageW(child, WM_SETFONT, reinterpret_cast<WPARAM>(font), TRUE);
    }
    const wchar_t* themeName = themesDisabled ? L"" : nullptr;
    SetWindowTheme(child, themeName, themeName);
    return TRUE;
}

/// Creates the application font if needed, applies font and theme settings to a form and its children, and requests
/// repainting.
static void ApplyUiStyle(HWND window) {
    if (hUiFont == nullptr) {
        NONCLIENTMETRICSW metrics = {};
        metrics.cbSize = sizeof(metrics);
        if (SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof(metrics), &metrics, 0)) {
            metrics.lfMessageFont.lfWeight = appFontWeight;
            metrics.lfMessageFont.lfItalic = appFontItalic;
            metrics.lfMessageFont.lfQuality = FontQuality(appFontAntialiasing);
            if (!appFontFace.empty()) {
                wcsncpy_s(metrics.lfMessageFont.lfFaceName, appFontFace.c_str(), _TRUNCATE);
                metrics.lfMessageFont.lfCharSet = DEFAULT_CHARSET;
            }
            hUiFont = CreateFontIndirectW(&metrics.lfMessageFont);
        }
    }
    const wchar_t* themeName = themesDisabled ? L"" : nullptr;
    SetWindowTheme(window, themeName, themeName);
    EnumChildWindows(window, ApplyFontAndTheme, 0);
    if (window == hHelp || window == hAbout) {
        LayoutInformationWindow(window);
    }
    RedrawWindow(window, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN);
}

/// Applies the combined application and widget theme-disable settings and invalidates the window and its children.
static void ApplyWidgetTheme(HWND window, const WidgetConfig& config) {
    if (window == nullptr) {
        return;
    }
    bool disabled = themesDisabled || config.disableThemes;
    const wchar_t* themeName = disabled ? L"" : nullptr;
    SetWindowTheme(window, themeName, themeName);
    RedrawWindow(window, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN);
}

/// Replaces the live calendar font and adjusts its native minimum size, releasing the previous font.
static void ApplyCalendarFont(Widget* widget) {
    if (widget == nullptr || widget->calendarChild == nullptr) {
        return;
    }
    HFONT replacement = CreateCalendarUiFont(widget->config);
    if (replacement == nullptr) {
        return;
    }
    SendMessageW(widget->calendarChild, WM_SETFONT, reinterpret_cast<WPARAM>(replacement), TRUE);
    if (widget->calendarFont != nullptr) {
        DeleteObject(widget->calendarFont);
    }
    widget->calendarFont = replacement;
    RECT minimum = {};
    if (MonthCal_GetMinReqRect(widget->calendarChild, &minimum)) {
        SetWindowPos(widget->calendarChild, nullptr, 0, 0, minimum.right - minimum.left, minimum.bottom - minimum.top,
            SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
    }
    RedrawWindow(widget->calendarChild, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_UPDATENOW);
}

/// Restores and activates a valid window, temporarily attaching input queues when the foreground thread differs.
static bool SetForegroundWindowEx(HWND window) {
    if (window == nullptr || !IsWindow(window)) {
        return false;
    }
    DWORD currentThread = GetCurrentThreadId();
    DWORD foregroundThread = GetWindowThreadProcessId(GetForegroundWindow(), nullptr);
    if (foregroundThread != 0 && foregroundThread != currentThread) {
        AttachThreadInput(currentThread, foregroundThread, TRUE);
    }
    ShowWindow(window, SW_SHOWNORMAL);
    BringWindowToTop(window);
    bool result = SetForegroundWindow(window) != FALSE;
    if (foregroundThread != 0 && foregroundThread != currentThread) {
        AttachThreadInput(currentThread, foregroundThread, FALSE);
    }
    return result;
}

/// Updates the primary and additional analog controls using each clock's displayed time and time zone.
static void UpdateAnalogTime(Widget* widget) {
    if (widget == nullptr) {
        return;
    }
    SYSTEMTIME time = {};
    if (widget->analogChild != nullptr) {
        GetDisplayedTime(widget->config, &time);
        SetAnalogClockTime(widget->analogChild, time);
    }
    for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
        if (widget->additionalAnalogChildren[index] != nullptr) {
            WidgetConfig clock = AdditionalClockConfiguration(widget->config, index);
            GetDisplayedTime(clock, &time);
            SetAnalogClockTime(widget->additionalAnalogChildren[index], time);
        }
    }
}

/// Returns the widget's native analog background or the system fallback for a missing clock.
static COLORREF ReadAnalogBackground(const Widget* widget) {
    return ReadAnalogClockBackground(widget == nullptr ? nullptr : widget->analogChild);
}

/// Caches the native clock background and invalidates the widget only when that color changes.
static void CaptureAnalogBackground(Widget* widget) {
    if (widget == nullptr) {
        return;
    }
    COLORREF color = ReadAnalogBackground(widget);
    if (widget->analogBackground != color) {
        widget->analogBackground = color;
        InvalidateRect(widget->window, nullptr, FALSE);
    }
}

/// Returns a cached panel background when available, otherwise reading the native clock background.
static COLORREF PanelBackgroundColor(const Widget* widget) {
    if (widget != nullptr && widget->analogBackground != CLR_INVALID) {
        return widget->analogBackground;
    }
    return ReadAnalogBackground(widget);
}

/// Creates a top-down 32-bit DIB and exposes its writable pixels.
/// The caller must delete the returned bitmap; the pixel pointer is valid only while the bitmap exists.
static bool CreateDib(HDC reference, int width, int height, HBITMAP* bitmap, DWORD** pixels) {
    BITMAPINFO information = {};
    information.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    information.bmiHeader.biWidth = width;
    information.bmiHeader.biHeight = -height;
    information.bmiHeader.biPlanes = 1;
    information.bmiHeader.biBitCount = 32;
    information.bmiHeader.biCompression = BI_RGB;
    void* bits = nullptr;
    *bitmap = CreateDIBSection(reference, &information, DIB_RGB_COLORS, &bits, nullptr, 0);
    *pixels = static_cast<DWORD*>(bits);
    return *bitmap != nullptr && bits != nullptr;
}

/// Presents a bitmap with per-pixel alpha and overall opacity, preserving the widget's position and edge attachments.
static void PresentLayeredBitmap(Widget* widget, HDC sourceDC, HDC screenDC, int width, int height, BYTE opacity) {
    RECT current = {};
    GetWindowRect(widget->window, &current);
    POINT destination = {};
    if (widget->rendered) {
        destination.x = current.left;
        destination.y = current.top;
    } else {
        destination.x = widget->config.x;
        destination.y = widget->config.y;
    }
    if (widget->rendered && (current.right - current.left != width || current.bottom - current.top != height)) {
        GetPositionPreservingWorkAreaAttachment(widget->window, width, height, &destination);
        widget->config.x = destination.x;
        widget->config.y = destination.y;
    }
    POINT source = {
        0,
        0
    };
    SIZE size = { width, height };
    BLENDFUNCTION blend = { AC_SRC_OVER, 0, opacity, AC_SRC_ALPHA };
    if (UpdateLayeredWindow(widget->window, screenDC, &destination, &size, sourceDC, &source, 0, &blend, ULW_ALPHA)) {
        widget->rendered = true;
    }
}

/// Renders the current analog clock into a new 32-bit bitmap over the requested background.
/// Transfers bitmap ownership on success and deletes it on rendering failure.
static bool RenderAnalogBackground(Widget* widget, HDC reference, DWORD background, HBITMAP* bitmap, DWORD** pixels) {
    if (widget == nullptr
            || widget->analogChild == nullptr
            || !CreateDib(reference, widget->config.size, widget->config.size, bitmap, pixels)) {
        return false;
    }
    HDC memory = CreateCompatibleDC(reference);
    if (memory == nullptr) {
        DeleteObject(*bitmap);
        *bitmap = nullptr;
        return false;
    }
    HGDIOBJ oldBitmap = SelectObject(memory, *bitmap);
    UpdateAnalogTime(widget);
    bool rendered = RenderAnalogClock(widget->analogChild, memory, background);
    SelectObject(memory, oldBitmap);
    DeleteDC(memory);
    if (!rendered) {
        DeleteObject(*bitmap);
        *bitmap = nullptr;
    }
    return rendered;
}

/// Renders the native face against light and dark backgrounds to reconstruct transparency, then presents the layered
/// widget.
static void RenderAnalogWidget(Widget* widget) {
    HDC screen = GetDC(nullptr);
    if (screen == nullptr) {
        return;
    }
    int size = widget->config.size;
    HBITMAP whiteBitmap = nullptr;
    HBITMAP blackBitmap = nullptr;
    DWORD* whitePixels = nullptr;
    DWORD* blackPixels = nullptr;
    if (!RenderAnalogBackground(widget, screen, 0xFFFFFFFF, &whiteBitmap, &whitePixels)
            || !RenderAnalogBackground(widget, screen, 0xFF000000, &blackBitmap, &blackPixels)) {
        if (whiteBitmap != nullptr) {
            DeleteObject(whiteBitmap);
        }
        if (blackBitmap != nullptr) {
            DeleteObject(blackBitmap);
        }
        ReleaseDC(nullptr, screen);
        return;
    }
    HBITMAP outputBitmap = nullptr;
    DWORD* output = nullptr;
    if (!CreateDib(screen, size, size, &outputBitmap, &output)) {
        DeleteObject(whiteBitmap);
        DeleteObject(blackBitmap);
        ReleaseDC(nullptr, screen);
        return;
    }
    HDC outputDC = CreateCompatibleDC(screen);
    for (int index = 0; index < size * size; index++) {
        DWORD white = whitePixels[index];
        DWORD black = blackPixels[index];
        int wb = static_cast<BYTE>(white);
        int wg = static_cast<BYTE>(white >> 8);
        int wr = static_cast<BYTE>(white >> 16);
        int bb = static_cast<BYTE>(black);
        int bg = static_cast<BYTE>(black >> 8);
        int br = static_cast<BYTE>(black >> 16);
        int alpha = 255 - std::clamp((wr - br + (wg - bg) + (wb - bb)) / 3, 0, 255);
        if (alpha < 2) {
            output[index] = 0;
            continue;
        }
        if (alpha > 253) {
            alpha = 255;
        }
        int red = std::min(br, alpha);
        int green = std::min(bg, alpha);
        int blue = std::min(bb, alpha);
        if (widget->identifyActive && widget->identifyPhase) {
            const int tintStrength = 150;
            int tintRed = 80 * alpha / 255;
            int tintGreen = 190 * alpha / 255;
            int tintBlue = alpha;
            red = (red * (255 - tintStrength) + tintRed * tintStrength) / 255;
            green = (green * (255 - tintStrength) + tintGreen * tintStrength) / 255;
            blue = (blue * (255 - tintStrength) + tintBlue * tintStrength) / 255;
        } else if (widget->alarmActive && widget->flashPhase) {
            red = alpha;
            green /= 3;
            blue /= 3;
        }
        output[index] = static_cast<DWORD>(alpha) << 24 | red << 16 | green << 8 | blue;
    }
    HGDIOBJ oldOutput = SelectObject(outputDC, outputBitmap);
    PresentLayeredBitmap(widget, outputDC, screen, size, size, static_cast<BYTE>(widget->config.opacity * 255 / 100));
    SelectObject(outputDC, oldOutput);
    DeleteObject(outputBitmap);
    DeleteDC(outputDC);
    DeleteObject(whiteBitmap);
    DeleteObject(blackBitmap);
    ReleaseDC(nullptr, screen);
}

/// Creates a caller-owned GDI font from panel font properties, converting the dialog size from tenths of a point.
static HFONT CreatePanelFont(const FontSelection& selection, int fontAntialiasing) {
    HDC screen = GetDC(nullptr);
    int dpi = screen == nullptr ? 96 : GetDeviceCaps(screen, LOGPIXELSY);
    if (screen != nullptr) {
        ReleaseDC(nullptr, screen);
    }
    int height = -MulDiv(std::clamp(selection.dialogSize, 10, 9990), dpi, 720);
    return CreateFontW(height, 0, 0, 0, selection.weight, selection.italic, selection.underline,
        selection.strikeOut, selection.charSet, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        FontQuality(fontAntialiasing), DEFAULT_PITCH | FF_DONTCARE, selection.face.c_str());
}

/// Creates a caller-owned GDI font using the widget's point size, style, face, and antialiasing settings.
static HFONT CreateWidgetDrawingFont(const WidgetConfig& config) {
    HDC screen = GetDC(nullptr);
    int dpi = screen == nullptr ? 96 : GetDeviceCaps(screen, LOGPIXELSY);
    if (screen != nullptr) {
        ReleaseDC(nullptr, screen);
    }
    int height = -MulDiv(config.fontSize, dpi, 72);
    return CreateFontW(height, 0, 0, 0, config.fontWeight, config.fontItalic, config.fontUnderline,
        config.fontStrikeOut, config.fontCharSet, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        FontQuality(config.fontAntialiasing), DEFAULT_PITCH | FF_DONTCARE, config.fontFace.c_str());
}

/// Builds sample clock text with uniform digits and any fullscreen AM/PM or UTC footer for stable measurement.
static std::wstring FullscreenClockMeasurementText(const WidgetConfig& config, wchar_t digit, int hour) {
    SYSTEMTIME time = {};
    time.wHour = static_cast<WORD>(hour);
    time.wMinute = 58;
    time.wSecond = 58;
    std::wstring text = FormatWidgetTime(config, time);
    for (wchar_t& character : text) {
        if (character >= L'0' && character <= L'9') {
            character = digit;
        }
    }
    if (config.showUtc && config.showUtcText) {
        text += L"\r\nUTC";
    }
    return text;
}

/// Measures stable GDI bounds for the clock and its footer, considering the widest digit and both day periods.
static SIZE MeasureFullscreenClockText(HDC dc, const WidgetConfig& config, SIZE* clockSize) {
    wchar_t widestDigit = L'0';
    LONG digitWidth = 0;
    for (wchar_t digit = L'0'; digit <= L'9'; digit++) {
        SIZE extent = {};
        if (GetTextExtentPoint32W(dc, &digit, 1, &extent) && extent.cx > digitWidth) {
            widestDigit = digit;
            digitWidth = extent.cx;
        }
    }
    SIZE maximum = {};
    *clockSize = {};
    for (int hour = 11; hour <= 23; hour += 12) {
        std::wstring text = FullscreenClockMeasurementText(config, widestDigit, hour);
        size_t lineEnd = text.find(L"\r\n");
        std::wstring clockText = text.substr(0, lineEnd);
        SIZE extent = {};
        GetTextExtentPoint32W(dc, clockText.c_str(), static_cast<int>(clockText.size()), &extent);
        clockSize->cx = std::max(clockSize->cx, extent.cx);
        clockSize->cy = std::max(clockSize->cy, extent.cy);
        RECT bounds = {};
        DrawTextW(dc, text.c_str(), static_cast<int>(text.size()), &bounds, DT_CALCRECT | DT_NOPREFIX);
        maximum.cx = std::max(maximum.cx, bounds.right);
        maximum.cy = std::max(maximum.cy, bounds.bottom);
    }
    return maximum;
}

/// Creates a caller-owned fullscreen GDI font scaled to the widget and reduced as necessary to fit the measured text.
static HFONT CreateFullscreenDrawingFont(const WidgetConfig& config, const RECT& client, HDC dc) {
    int width = client.right - client.left;
    int height = client.bottom - client.top;
    int pixelHeight = std::max(1, height *
        std::clamp(config.fontSize, FULLSCREEN_FONT_SIZE_MIN, FULLSCREEN_FONT_SIZE_MAX) / 100);
    HFONT font = CreateFontW(-pixelHeight, 0, 0, 0, config.fontWeight, config.fontItalic, config.fontUnderline,
        config.fontStrikeOut, config.fontCharSet, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        FontQuality(config.fontAntialiasing), DEFAULT_PITCH | FF_DONTCARE, config.fontFace.c_str());
    if (font == nullptr || dc == nullptr) {
        return font;
    }
    HGDIOBJ oldFont = SelectObject(dc, font);
    SIZE clockSize = {};
    SIZE measured = MeasureFullscreenClockText(dc, config, &clockSize);
    SelectObject(dc, oldFont);
    while ((measured.cx > width || measured.cy > height) && measured.cx > 0 && measured.cy > 0 && pixelHeight > 1) {
        int widthFittedHeight = MulDiv(pixelHeight, width, measured.cx);
        int heightFittedHeight = MulDiv(pixelHeight, height, measured.cy);
        pixelHeight = std::max(1, std::min(pixelHeight - 1, std::min(widthFittedHeight, heightFittedHeight)));
        DeleteObject(font);
        font = CreateFontW(-pixelHeight, 0, 0, 0, config.fontWeight, config.fontItalic, config.fontUnderline,
            config.fontStrikeOut, config.fontCharSet, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            FontQuality(config.fontAntialiasing), DEFAULT_PITCH | FF_DONTCARE, config.fontFace.c_str());
        if (font == nullptr) {
            return nullptr;
        }
        oldFont = SelectObject(dc, font);
        measured = MeasureFullscreenClockText(dc, config, &clockSize);
        SelectObject(dc, oldFont);
    }
    return font;
}

/// Draws text with the supplied font, color, alignment flags, and optional opaque background, restoring the selected
/// font.
static void DrawCenteredText(HDC dc, const std::wstring& text, RECT rect, HFONT font, COLORREF color,
        UINT format = DT_CENTER | DT_VCENTER | DT_SINGLELINE, COLORREF backgroundColor = CLR_INVALID) {
    HGDIOBJ oldFont = SelectObject(dc, font);
    SetTextColor(dc, color);
    if (backgroundColor == CLR_INVALID) {
        SetBkMode(dc, TRANSPARENT);
    } else {
        SetBkColor(dc, backgroundColor);
        SetBkMode(dc, OPAQUE);
    }
    DrawTextW(dc, text.c_str(), -1, &rect, format);
    SelectObject(dc, oldFont);
}

/// Draws clock text while reserving the measured leading-zero space when that zero is hidden.
static void DrawClockText(HDC dc, const std::wstring& text, RECT rect, HFONT font, COLORREF color, int leadingZeroMode,
        UINT format = DT_CENTER | DT_VCENTER | DT_SINGLELINE, COLORREF backgroundColor = CLR_INVALID) {
    if (leadingZeroMode != LEADING_ZERO_RESERVED || text.empty() || text[0] != L'0') {
        DrawCenteredText(dc, text, rect, font, color, format, backgroundColor);
        return;
    }
    int savedDC = SaveDC(dc);
    if (savedDC == 0) {
        return;
    }
    size_t lineEnd = text.find(L"\r\n");
    std::wstring firstLine = text.substr(0, lineEnd);
    std::wstring visibleLine = firstLine.substr(1);
    HGDIOBJ oldFont = SelectObject(dc, font);
    SIZE fullExtent = {};
    SIZE visibleExtent = {};
    GetTextExtentPoint32W(dc, firstLine.c_str(), static_cast<int>(firstLine.size()), &fullExtent);
    GetTextExtentPoint32W(dc, visibleLine.c_str(), static_cast<int>(visibleLine.size()), &visibleExtent);
    SelectObject(dc, oldFont);
    IntersectClipRect(dc, rect.left, rect.top, rect.right, rect.bottom);
    RECT firstRect = rect;
    firstRect.left += fullExtent.cx - visibleExtent.cx;
    UINT firstFormat = format | DT_SINGLELINE | DT_NOCLIP;
    if ((format & DT_SINGLELINE) == 0) {
        firstFormat &= ~DT_VCENTER;
    }
    DrawCenteredText(dc, visibleLine, firstRect, font, color, firstFormat, backgroundColor);
    if (lineEnd != std::wstring::npos) {
        rect.top += fullExtent.cy;
        DrawCenteredText(dc, text.substr(lineEnd + 2), rect, font, color, format, backgroundColor);
    }
    RestoreDC(dc, savedDC);
}

/// Draws the numeric time and its prefix or suffix in stable measured regions so proportional digits do not shift the
/// marker.
static void DrawWidgetTimeText(HDC dc, const std::wstring& text, RECT rect, HFONT font, COLORREF color,
        const WidgetConfig& config, UINT format = DT_CENTER | DT_VCENTER | DT_SINGLELINE,
        COLORREF backgroundColor = CLR_INVALID) {
    size_t firstDigit = text.find_first_of(L"0123456789");
    if (firstDigit == std::wstring::npos) {
        DrawClockText(dc, text, rect, font, color, config.leadingZeroMode, format, backgroundColor);
        return;
    }
    int savedDC = SaveDC(dc);
    if (savedDC == 0) {
        return;
    }
    size_t lastDigit = text.find_last_of(L"0123456789");
    WidgetConfig clock = config;
    clock.showAmPm = false;
    clock.showUtcText = false;
    SYSTEMTIME sample = {};
    sample.wHour = 23;
    sample.wMinute = 58;
    sample.wSecond = 58;
    HGDIOBJ oldFont = SelectObject(dc, font);
    SIZE clockSize = MeasureClockTime(dc, clock, sample);
    SIZE fullSize = MeasureClockTime(dc, config, sample);
    LONG prefixWidth = firstDigit == 0 ? 0 : std::max(0L, fullSize.cx - clockSize.cx);
    size_t hourEnd = text.find_first_not_of(L"0123456789", firstDigit);
    if (config.leadingZeroMode == LEADING_ZERO_OMITTED && hourEnd == firstDigit + 1) {
        sample.wHour = 1;
        clockSize = MeasureClockTime(dc, clock, sample);
    }
    SelectObject(dc, oldFont);
    LONG left = rect.left;
    if (format & DT_CENTER) {
        left += (rect.right - rect.left - fullSize.cx) / 2;
    } else if (format & DT_RIGHT) {
        left = rect.right - fullSize.cx;
    }
    RECT clockRect = { left + prefixWidth, rect.top, left + prefixWidth + clockSize.cx, rect.bottom };
    UINT lineFormat = format & ~(DT_CENTER | DT_RIGHT) | DT_NOCLIP;
    IntersectClipRect(dc, rect.left, rect.top, rect.right, rect.bottom);
    if (firstDigit != 0) {
        RECT prefixRect = { left, rect.top, clockRect.left, rect.bottom };
        DrawCenteredText(dc, text.substr(0, firstDigit), prefixRect, font, color, lineFormat, backgroundColor);
    }
    DrawClockText(dc, text.substr(firstDigit, lastDigit - firstDigit + 1), clockRect, font, color, config.leadingZeroMode, lineFormat, backgroundColor);
    if (lastDigit + 1 < text.size()) {
        RECT suffixRect = { clockRect.right, rect.top, left + fullSize.cx, rect.bottom };
        DrawCenteredText(dc, text.substr(lastDigit + 1), suffixRect, font, color, lineFormat, backgroundColor);
    }
    RestoreDC(dc, savedDC);
}

/// Draws a centered fullscreen clock with stable numeric bounds and a separately centered footer using GDI.
static void DrawFullscreenClockText(HDC dc, const std::wstring& text, const RECT& rect, const WidgetConfig& config,
        COLORREF color, COLORREF backgroundColor) {
    HFONT font = CreateFullscreenDrawingFont(config, rect, dc);
    if (font == nullptr) {
        return;
    }
    HGDIOBJ oldFont = SelectObject(dc, font);
    SIZE clockSize = {};
    SIZE measured = MeasureFullscreenClockText(dc, config, &clockSize);
    SelectObject(dc, oldFont);
    size_t lineEnd = text.find(L"\r\n");
    RECT clockRect = rect;
    clockRect.left += (rect.right - rect.left - clockSize.cx) / 2;
    clockRect.right = clockRect.left + clockSize.cx;
    clockRect.top += (rect.bottom - rect.top - measured.cy) / 2;
    clockRect.bottom = clockRect.top + clockSize.cy;
    DrawClockText(dc, text.substr(0, lineEnd), clockRect, font, color, config.leadingZeroMode,
        DT_LEFT | DT_TOP | DT_SINGLELINE | DT_NOPREFIX, backgroundColor);
    if (lineEnd != std::wstring::npos) {
        RECT footerRect = rect;
        footerRect.top = clockRect.bottom;
        footerRect.bottom = footerRect.top + clockSize.cy;
        DrawCenteredText(dc, text.substr(lineEnd + 2), footerRect, font, color,
            DT_CENTER | DT_TOP | DT_SINGLELINE | DT_NOPREFIX, backgroundColor);
    }
    DeleteObject(font);
}

/// Loads a library by filename from the Windows system directory; the caller must release the returned module.
static HMODULE LoadSystemLibrary(const wchar_t* fileName) {
    wchar_t systemDirectory[MAX_PATH] = {};
    UINT length = GetSystemDirectoryW(systemDirectory, ARRAYSIZE(systemDirectory));
    if (length == 0 || length >= ARRAYSIZE(systemDirectory)) {
        return nullptr;
    }
    wchar_t path[MAX_PATH] = {};
    if (swprintf_s(path, L"%s\\%s", systemDirectory, fileName) < 0) {
        return nullptr;
    }
    return LoadLibraryW(path);
}

/// Releases DirectWrite and Direct2D factories before unloading their dynamically loaded libraries.
static void ShutdownDirectTextRendering() {
    if (dwriteFactory != nullptr) {
        dwriteFactory->Release();
        dwriteFactory = nullptr;
    }
    if (d2dFactory != nullptr) {
        d2dFactory->Release();
        d2dFactory = nullptr;
    }
    if (dwriteModule != nullptr) {
        FreeLibrary(dwriteModule);
        dwriteModule = nullptr;
    }
    if (d2dModule != nullptr) {
        FreeLibrary(d2dModule);
        d2dModule = nullptr;
    }
}

/// Loads optional DirectWrite and Direct2D support and creates their factories, cleaning up if initialization fails.
static void InitializeDirectTextRendering() {
    d2dModule = LoadSystemLibrary(L"d2d1.dll");
    dwriteModule = LoadSystemLibrary(L"dwrite.dll");
    if (d2dModule == nullptr || dwriteModule == nullptr) {
        ShutdownDirectTextRendering();
        return;
    }
    D2D1CreateFactoryProc createD2dFactory =
        reinterpret_cast<D2D1CreateFactoryProc>(GetProcAddress(d2dModule, "D2D1CreateFactory"));
    DWriteCreateFactoryProc createDwriteFactory =
        reinterpret_cast<DWriteCreateFactoryProc>(GetProcAddress(dwriteModule, "DWriteCreateFactory"));
    if (createD2dFactory == nullptr || createDwriteFactory == nullptr) {
        ShutdownDirectTextRendering();
        return;
    }
    D2D1_FACTORY_OPTIONS options = {};
    HRESULT d2dResult = createD2dFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), &options,
        reinterpret_cast<void**>(&d2dFactory));
    HRESULT dwriteResult = createDwriteFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown**>(&dwriteFactory));
    if (FAILED(d2dResult) || FAILED(dwriteResult) || d2dFactory == nullptr || dwriteFactory == nullptr) {
        ShutdownDirectTextRendering();
    }
}

/// Creates a temporary DirectWrite layout and returns its metrics for the supplied font and layout bounds.
static HRESULT MeasureDirectText(IDWriteTextFormat* format, const std::wstring& text, float width, float height,
        DWRITE_TEXT_METRICS* metrics) {
    IDWriteTextLayout* layout = nullptr;
    HRESULT result = dwriteFactory->CreateTextLayout(text.c_str(), static_cast<UINT32>(text.size()), format, width,
        height, &layout);
    if (SUCCEEDED(result) && layout != nullptr) {
        result = layout->GetMetrics(metrics);
        layout->Release();
    }
    return result;
}

/// Measures stable DirectWrite bounds for the clock and footer using the widest digit and both day periods.
static HRESULT MeasureFullscreenDirectText(IDWriteTextFormat* format, const WidgetConfig& config, float width,
        float height, DWRITE_TEXT_METRICS* maximum, DWRITE_TEXT_METRICS* clockMetrics) {
    wchar_t widestDigit = L'0';
    float digitWidth = 0.0f;
    for (wchar_t digit = L'0'; digit <= L'9'; digit++) {
        DWRITE_TEXT_METRICS metrics = {};
        HRESULT result = MeasureDirectText(format, std::wstring(1, digit), width, height, &metrics);
        if (FAILED(result)) {
            return result;
        }
        if (metrics.widthIncludingTrailingWhitespace > digitWidth) {
            widestDigit = digit;
            digitWidth = metrics.widthIncludingTrailingWhitespace;
        }
    }
    *maximum = {};
    *clockMetrics = {};
    for (int hour = 11; hour <= 23; hour += 12) {
        std::wstring text = FullscreenClockMeasurementText(config, widestDigit, hour);
        DWRITE_TEXT_METRICS metrics = {};
        HRESULT result = MeasureDirectText(format, text, width, height, &metrics);
        if (FAILED(result)) {
            return result;
        }
        maximum->widthIncludingTrailingWhitespace =
            std::max(maximum->widthIncludingTrailingWhitespace, metrics.widthIncludingTrailingWhitespace);
        maximum->height = std::max(maximum->height, metrics.height);
        result = MeasureDirectText(format, text.substr(0, text.find(L"\r\n")), width, height, &metrics);
        if (FAILED(result)) {
            return result;
        }
        clockMetrics->widthIncludingTrailingWhitespace =
            std::max(clockMetrics->widthIncludingTrailingWhitespace, metrics.widthIncludingTrailingWhitespace);
        clockMetrics->height = std::max(clockMetrics->height, metrics.height);
    }
    return S_OK;
}

/// Renders fullscreen clock text through DirectWrite and Direct2D with stable positioning and the selected
/// antialiasing.
/// Returns false when optional rendering support is unavailable or drawing fails.
static bool DrawFullscreenText(HDC dc, const wchar_t* text, const RECT& rect, const WidgetConfig& config,
        COLORREF color, COLORREF backgroundColor) {
    if (d2dFactory == nullptr || dwriteFactory == nullptr || dc == nullptr || text == nullptr || text[0] == L'\0') {
        return false;
    }
    int width = std::max(1L, rect.right - rect.left);
    int height = std::max(1L, rect.bottom - rect.top);
    D2D1_RENDER_TARGET_PROPERTIES properties = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE), 96.0f, 96.0f,
        D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE);
    ID2D1DCRenderTarget* target = nullptr;
    HRESULT result = d2dFactory->CreateDCRenderTarget(&properties, &target);
    if (FAILED(result) || target == nullptr) {
        return false;
    }
    result = target->BindDC(dc, &rect);
    if (FAILED(result)) {
        target->Release();
        return false;
    }
    float fontSize = std::max(1.0f, static_cast<float>(height) * static_cast<float>(std::clamp(config.fontSize,
        FULLSCREEN_FONT_SIZE_MIN, FULLSCREEN_FONT_SIZE_MAX)) / 100.0f);
    DWRITE_FONT_WEIGHT weight = static_cast<DWRITE_FONT_WEIGHT>(std::clamp(config.fontWeight, 1, 999));
    DWRITE_FONT_STYLE style = config.fontItalic ? DWRITE_FONT_STYLE_ITALIC : DWRITE_FONT_STYLE_NORMAL;
    IDWriteTextFormat* format = nullptr;
    const wchar_t* fontFace = config.fontFace.empty() ? L"Arial" : config.fontFace.c_str();
    result = dwriteFactory->CreateTextFormat(fontFace, nullptr, weight, style, DWRITE_FONT_STRETCH_NORMAL,
        fontSize, LANGUAGE_LOCALES[config.language], &format);
    if (FAILED(result) || format == nullptr) {
        target->Release();
        return false;
    }
    format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
    format->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
    DWRITE_TEXT_METRICS metrics = {};
    DWRITE_TEXT_METRICS clockMetrics = {};
    result = MeasureFullscreenDirectText(format, config,
        static_cast<float>(width), static_cast<float>(height), &metrics, &clockMetrics);
    if (SUCCEEDED(result)
            && (metrics.widthIncludingTrailingWhitespace > static_cast<float>(width)
                || metrics.height > static_cast<float>(height))) {
        float widthScale = metrics.widthIncludingTrailingWhitespace > 0.0f
            ? static_cast<float>(width) / metrics.widthIncludingTrailingWhitespace
            : 1.0f;
        float heightScale = metrics.height > 0.0f
            ? static_cast<float>(height) / metrics.height :
            1.0f;
        fontSize = std::max(1.0f, fontSize * std::min(widthScale, heightScale));
        format->Release();
        format = nullptr;
        result = dwriteFactory->CreateTextFormat(fontFace, nullptr, weight, style, DWRITE_FONT_STRETCH_NORMAL,
            fontSize, LANGUAGE_LOCALES[config.language], &format);
        if (SUCCEEDED(result) && format != nullptr) {
            format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
            format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
            format->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
            result = MeasureFullscreenDirectText(format, config,
                static_cast<float>(width), static_cast<float>(height), &metrics, &clockMetrics);
        }
    }
    std::wstring clockText = text;
    size_t lineEnd = clockText.find(L"\r\n");
    std::wstring footerText;
    if (lineEnd != std::wstring::npos) {
        footerText = clockText.substr(lineEnd + 2);
        clockText.resize(lineEnd);
    }
    UINT32 length = static_cast<UINT32>(clockText.size());
    IDWriteTextLayout* layout = nullptr;
    IDWriteTextLayout* footerLayout = nullptr;
    if (SUCCEEDED(result) && format != nullptr) {
        result = dwriteFactory->CreateTextLayout(clockText.c_str(), length, format,
            clockMetrics.widthIncludingTrailingWhitespace, clockMetrics.height, &layout);
    }
    if (SUCCEEDED(result) && !footerText.empty()) {
        result = dwriteFactory->CreateTextLayout(footerText.c_str(), static_cast<UINT32>(footerText.size()),
            format, static_cast<float>(width), clockMetrics.height, &footerLayout);
        if (SUCCEEDED(result) && footerLayout != nullptr) {
            footerLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
            DWRITE_TEXT_RANGE footerRange = {
                0,
                static_cast<UINT32>(footerText.size())
            };
            footerLayout->SetUnderline(config.fontUnderline, footerRange);
            footerLayout->SetStrikethrough(config.fontStrikeOut, footerRange);
        }
    }
    if (FAILED(result) || format == nullptr || layout == nullptr) {
        if (footerLayout != nullptr) {
            footerLayout->Release();
        }
        if (layout != nullptr) {
            layout->Release();
        }
        if (format != nullptr) {
            format->Release();
        }
        target->Release();
        return false;
    }
    DWRITE_TEXT_RANGE range = {
        0,
        length
    };
    layout->SetUnderline(config.fontUnderline, range);
    layout->SetStrikethrough(config.fontStrikeOut, range);
    ID2D1SolidColorBrush* brush = nullptr;
    result = target->CreateSolidColorBrush(D2D1::ColorF(GetRValue(color) / 255.0f, GetGValue(color) / 255.0f,
        GetBValue(color) / 255.0f), &brush);
    ID2D1SolidColorBrush* hiddenBrush = nullptr;
    if (SUCCEEDED(result) && config.leadingZeroMode == LEADING_ZERO_RESERVED && text[0] == L'0') {
        result = target->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f), &hiddenBrush);
        if (SUCCEEDED(result)) {
            DWRITE_TEXT_RANGE leadingZeroRange = {
                0,
                1
            };
            result = layout->SetDrawingEffect(hiddenBrush, leadingZeroRange);
        }
    }
    if (SUCCEEDED(result) && brush != nullptr) {
        target->SetTextAntialiasMode(DirectWriteAntialiasMode(config.fontAntialiasing));
        target->BeginDraw();
        target->Clear(D2D1::ColorF(GetRValue(backgroundColor) / 255.0f, GetGValue(backgroundColor) / 255.0f,
            GetBValue(backgroundColor) / 255.0f));
        float clockLeft = (static_cast<float>(width) - clockMetrics.widthIncludingTrailingWhitespace) / 2.0f;
        float clockTop = (static_cast<float>(height) - metrics.height) / 2.0f;
        target->DrawTextLayout(D2D1::Point2F(clockLeft, clockTop), layout, brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
        if (footerLayout != nullptr) {
            target->DrawTextLayout(D2D1::Point2F(0.0f, clockTop + clockMetrics.height), footerLayout, brush,
                D2D1_DRAW_TEXT_OPTIONS_CLIP);
        }
        result = target->EndDraw();
    }
    if (hiddenBrush != nullptr) {
        hiddenBrush->Release();
    }
    if (brush != nullptr) {
        brush->Release();
    }
    if (footerLayout != nullptr) {
        footerLayout->Release();
    }
    layout->Release();
    format->Release();
    target->Release();
    return SUCCEEDED(result);
}

/// Draws the selected native-looking or flat border around the supplied dimensions.
static void DrawBorderStyle(HDC dc, int width, int height, int borderStyle, COLORREF color) {
    RECT borderRect = {
        0,
        0,
        width,
        height
    };
    if (borderStyle == DIGITAL_BORDER_TOOL_WINDOW) {
        DrawEdge(dc, &borderRect, EDGE_RAISED, BF_RECT);
    } else if (borderStyle == DIGITAL_BORDER_SINGLE) {
        HPEN pen = CreatePen(PS_SOLID, 1, color);
        HGDIOBJ oldPen = SelectObject(dc, pen);
        HGDIOBJ oldBrush = SelectObject(dc, GetStockObject(HOLLOW_BRUSH));
        Rectangle(dc, 0, 0, width, height);
        SelectObject(dc, oldBrush);
        SelectObject(dc, oldPen);
        DeleteObject(pen);
    } else if (borderStyle == DIGITAL_BORDER_3D) {
        DrawEdge(dc, &borderRect, EDGE_SUNKEN, BF_RECT);
    }
}

/// Converts a COLORREF to a fully opaque ARGB pixel for a layered bitmap.
static DWORD LayeredOpaquePixel(COLORREF color) {
    return 0xFF000000
        | static_cast<DWORD>(GetRValue(color)) << 16
        | static_cast<DWORD>(GetGValue(color)) << 8
        | GetBValue(color);
}

/// Writes one inset frame directly to an ARGB buffer with separate top-left and bottom-right colors.
static void DrawLayeredFrameLine(DWORD* pixels, int width, int height, int inset, COLORREF topLeftColor,
    COLORREF bottomRightColor) {
    DWORD topLeftPixel = LayeredOpaquePixel(topLeftColor);
    DWORD bottomRightPixel = LayeredOpaquePixel(bottomRightColor);
    int right = width - inset - 1;
    int bottom = height - inset - 1;
    for (int x = inset; x <= right; x++) {
        pixels[inset * width + x] = topLeftPixel;
        pixels[bottom * width + x] = bottomRightPixel;
    }
    for (int y = inset; y <= bottom; y++) {
        pixels[y * width + inset] = topLeftPixel;
        pixels[y * width + right] = bottomRightPixel;
    }
}

/// Writes the four system-colored frame lines used by a transparent digital widget's three-dimensional border.
static void DrawTransparentDigital3DBorder(DWORD* pixels, int width, int height) {
    DrawLayeredFrameLine(pixels, width, height, 0, GetSysColor(COLOR_3DHIGHLIGHT), GetSysColor(COLOR_3DDKSHADOW));
    DrawLayeredFrameLine(pixels, width, height, 1, GetSysColor(COLOR_3DLIGHT), GetSysColor(COLOR_3DSHADOW));
    DrawLayeredFrameLine(pixels, width, height, 2, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DLIGHT));
    DrawLayeredFrameLine(pixels, width, height, 3, GetSysColor(COLOR_3DDKSHADOW), GetSysColor(COLOR_3DHIGHLIGHT));
}

/// Draws the configured number of nested flat border lines inside the supplied inset.
static void DrawDigitalWidthBorder(HDC dc, int width, int height, int inset, int borderWidth, COLORREF color) {
    if (borderWidth <= 0) {
        return;
    }
    HPEN pen = CreatePen(PS_SOLID, 1, color);
    HGDIOBJ oldPen = SelectObject(dc, pen);
    HGDIOBJ oldBrush = SelectObject(dc, GetStockObject(HOLLOW_BRUSH));
    for (int border = 0; border < borderWidth; border++) {
        int edge = inset + border;
        Rectangle(dc, edge, edge, width - edge, height - edge);
    }
    SelectObject(dc, oldBrush);
    SelectObject(dc, oldPen);
    DeleteObject(pen);
}

/// Formats the current displayed time into a bounded buffer and adds an enabled UTC suffix or fullscreen footer.
static void GetDigitalTimeText(const WidgetConfig& config, wchar_t* text, size_t textCount) {
    SYSTEMTIME time = {};
    GetDisplayedTime(config, &time);
    std::wstring formatted = FormatWidgetTime(config, time);
    if (config.showUtc && config.showUtcText) {
        formatted += config.type == WIDGET_FULLSCREEN ? L"\r\nUTC" : L" UTC";
    }
    wcsncpy_s(text, textCount, formatted.c_str(), _TRUNCATE);
}

/// Calculates digital text padding, scaling fullscreen preview padding and limiting it to the available client area.
static int GetDigitalTextInset(const Widget* widget, const RECT& client) {
    if (widget->config.type != WIDGET_FULLSCREEN) {
        return widget->config.padding + widget->config.borderWidth;
    }
    int clientWidth = static_cast<int>(client.right - client.left);
    int clientHeight = static_cast<int>(client.bottom - client.top);
    int inset = widget->config.padding;
    if (widget->fullscreenPreview) {
        RECT monitorRect = {};
        if (GetPrimarySelectedMonitorRect(widget->config, &monitorRect)) {
            int monitorWidth = static_cast<int>(monitorRect.right - monitorRect.left);
            int monitorHeight = static_cast<int>(monitorRect.bottom - monitorRect.top);
            int clientSize = std::max(1, std::min(clientWidth, clientHeight));
            int monitorSize = std::max(1, std::min(monitorWidth, monitorHeight));
            inset = MulDiv(inset, clientSize, monitorSize);
        }
    }
    int maximumInset = std::max(0, (std::min(clientWidth, clientHeight) - 2) / 2);
    return std::clamp(inset, 0, maximumInset);
}

/// Paints an opaque digital or fullscreen clock, including alarm colors, borders, and any identification outline.
static void PaintOpaqueDigitalWidget(Widget* widget, HWND window, HDC dc) {
    RECT client = {};
    GetClientRect(window, &client);
    bool alarmFlash = widget->alarmActive && widget->flashPhase;
    COLORREF textColor = alarmFlash ? widget->config.alarmTextColor : widget->config.textColor;
    COLORREF backgroundColor = alarmFlash ? widget->config.alarmBackgroundColor : widget->config.backgroundColor;
    HBRUSH background = CreateSolidBrush(backgroundColor);
    FillRect(dc, &client, background);
    DeleteObject(background);
    wchar_t text[128] = {};
    GetDigitalTimeText(widget->config, text, _countof(text));
    RECT textRect = client;
    int textInset = GetDigitalTextInset(widget, client);
    InflateRect(&textRect, -textInset, -textInset);
    bool fullscreenDrawn = widget->config.type == WIDGET_FULLSCREEN
        && DrawFullscreenText(dc, text, textRect, widget->config, textColor, backgroundColor);
    if (!fullscreenDrawn) {
        if (widget->config.type == WIDGET_FULLSCREEN) {
            DrawFullscreenClockText(dc, text, textRect, widget->config, textColor, backgroundColor);
        } else {
            HFONT font = CreateWidgetDrawingFont(widget->config);
            DrawWidgetTimeText(dc, text, textRect, font, textColor, widget->config,
                DT_LEFT | DT_VCENTER | DT_SINGLELINE, backgroundColor);
            DeleteObject(font);
        }
    }
    if (widget->config.type != WIDGET_FULLSCREEN) {
        DrawDigitalWidthBorder(dc, client.right, client.bottom, 0, widget->config.borderWidth, textColor);
    }
    if (widget->identifyActive && widget->identifyPhase) {
        HPEN pen = CreatePen(PS_SOLID, 3, IDENTIFY_COLOR);
        HGDIOBJ oldPen = SelectObject(dc, pen);
        HGDIOBJ oldBrush = SelectObject(dc, GetStockObject(HOLLOW_BRUSH));
        Rectangle(dc, 1, 1, client.right - 1, client.bottom - 1);
        SelectObject(dc, oldBrush);
        SelectObject(dc, oldPen);
        DeleteObject(pen);
    }
}

/// Builds and presents the digital widget's layered bitmap with text, border, background transparency, and opacity.
static void RenderCustomWidget(Widget* widget) {
    int width = 0;
    int height = 0;
    GetWidgetDimensions(widget->config, &width, &height);
    HDC screen = GetDC(nullptr);
    if (screen == nullptr) {
        return;
    }
    HBITMAP bitmap = nullptr;
    DWORD* pixels = nullptr;
    HDC dc = CreateCompatibleDC(screen);
    if (!CreateDib(screen, width, height, &bitmap, &pixels) || dc == nullptr) {
        if (bitmap) {
            DeleteObject(bitmap);
        }
        if (dc) {
            DeleteDC(dc);
        }
        ReleaseDC(nullptr, screen);
        return;
    }
    HGDIOBJ oldBitmap = SelectObject(dc, bitmap);
    bool transparentDigital = widget->config.type == WIDGET_DIGITAL && widget->config.transparentBackground;
    bool alarmFlash = widget->alarmActive && widget->flashPhase;
    COLORREF textColor = alarmFlash ? widget->config.alarmTextColor : widget->config.textColor;
    COLORREF backgroundColor = alarmFlash ? widget->config.alarmBackgroundColor : widget->config.backgroundColor;
    HBRUSH background = CreateSolidBrush(transparentDigital ? RGB(255, 255, 255) : backgroundColor);
    RECT full = {
        0,
        0,
        width,
        height
    };
    FillRect(dc, &full, background);
    DeleteObject(background);
    wchar_t text[128] = {};
    GetDigitalTimeText(widget->config, text, _countof(text));
    int borderStyleInset = GetBorderStyleInset(widget->config.borderStyle);
    int inset = widget->config.padding + borderStyleInset + widget->config.borderWidth;
    RECT textRect = {
        inset,
        inset,
        width - inset,
        height - inset
    };
    HFONT font = CreateWidgetDrawingFont(widget->config);
    DrawWidgetTimeText(dc, text, textRect, font, transparentDigital ? RGB(0, 0, 0) : textColor,
        widget->config, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
    DeleteObject(font);
    if (transparentDigital && widget->config.borderStyle == DIGITAL_BORDER_SINGLE) {
        DrawBorderStyle(dc, width, height, DIGITAL_BORDER_TOOL_WINDOW, RGB(0, 0, 0));
    } else if (!transparentDigital) {
        DrawBorderStyle(dc, width, height, widget->config.borderStyle, textColor);
    }
    DrawDigitalWidthBorder(dc, width, height, borderStyleInset,
        widget->config.borderWidth, transparentDigital ? RGB(0, 0, 0) : textColor);
    if (widget->identifyActive && widget->identifyPhase) {
        HPEN pen = CreatePen(PS_SOLID, 3, IDENTIFY_COLOR);
        HGDIOBJ oldPen = SelectObject(dc, pen);
        HGDIOBJ oldBrush = SelectObject(dc, GetStockObject(HOLLOW_BRUSH));
        Rectangle(dc, 1, 1, width - 1, height - 1);
        SelectObject(dc, oldBrush);
        SelectObject(dc, oldPen);
        DeleteObject(pen);
    }
    SelectObject(dc, oldBitmap);
    BYTE opacity = static_cast<BYTE>(widget->config.opacity * 255 / 100);
    if (transparentDigital) {
        COLORREF color = widget->identifyActive && widget->identifyPhase ? IDENTIFY_COLOR : textColor;
        int minimumHitTestAlpha = (255 + opacity - 1) / std::max(1, static_cast<int>(opacity));
        for (int index = 0; index < width * height; index++) {
            DWORD pixel = pixels[index];
            int coverage = 255
                - (static_cast<BYTE>(pixel) + static_cast<BYTE>(pixel >> 8) + static_cast<BYTE>(pixel >> 16)) / 3;
            int alpha = std::max(minimumHitTestAlpha, coverage);
            int red = GetRValue(color) * alpha / 255;
            int green = GetGValue(color) * alpha / 255;
            int blue = GetBValue(color) * alpha / 255;
            pixels[index] = static_cast<DWORD>(alpha) << 24 | red << 16 | green << 8 | blue;
        }
        if (!(widget->identifyActive && widget->identifyPhase)) {
            if (widget->config.borderStyle == DIGITAL_BORDER_TOOL_WINDOW) {
                DrawLayeredFrameLine(pixels, width, height, 0, widget->config.borderColor, widget->config.borderColor);
            } else if (widget->config.borderStyle == DIGITAL_BORDER_3D) {
                DrawTransparentDigital3DBorder(pixels, width, height);
            }
        }
    } else {
        for (int index = 0; index < width * height; index++) {
            pixels[index] |= 0xFF000000;
        }
    }
    oldBitmap = SelectObject(dc, bitmap);
    PresentLayeredBitmap(widget, dc, screen, width, height, opacity);
    SelectObject(dc, oldBitmap);
    DeleteObject(bitmap);
    DeleteDC(dc);
    ReleaseDC(nullptr, screen);
}

/// Replaces a panel link's GDI font and deletes its previous owned font after successful creation.
static void ApplyPanelLinkFont(HWND link, const FontSelection& selection, int fontAntialiasing, HFONT* currentFont) {
    if (link == nullptr || currentFont == nullptr) {
        return;
    }
    HFONT replacement = CreatePanelFont(selection, fontAntialiasing);
    if (replacement == nullptr) {
        return;
    }
    SendMessageW(link, WM_SETFONT, reinterpret_cast<WPARAM>(replacement), TRUE);
    if (*currentFont != nullptr) {
        DeleteObject(*currentFont);
    }
    *currentFont = replacement;
}

/// Updates a panel link's text only when changed, then sizes and centers its clickable area within the supplied bounds.
static void UpdatePanelLinkButton(HWND link, HFONT font, const std::wstring& text, const RECT& bounds) {
    if (link == nullptr) {
        return;
    }
    if (GetControlText(link) != text) {
        SetWindowTextW(link, text.c_str());
    }
    HDC dc = GetDC(link);
    HGDIOBJ previousFont = SelectObject(dc, font);
    SIZE textSize = {};
    GetTextExtentPoint32W(dc, text.c_str(), static_cast<int>(text.size()), &textSize);
    SelectObject(dc, previousFont);
    ReleaseDC(link, dc);
    int width = std::min(textSize.cx + 4, bounds.right - bounds.left);
    int height = std::min(textSize.cy + 4, bounds.bottom - bounds.top);
    int x = bounds.left + (bounds.right - bounds.left - width) / 2;
    int y = bounds.top + (bounds.bottom - bounds.top - height) / 2;
    SetWindowPos(link, nullptr, x, y, width, height, SWP_NOZORDER | SWP_NOACTIVATE);
}

/// Draws a dotted focus rectangle using the system window-text color.
static void DrawPanelLinkFocusRect(HDC dc, const RECT& rect) {
    COLORREF color = GetSysColor(COLOR_WINDOWTEXT);
    int right = rect.right - 1;
    int bottom = rect.bottom - 1;
    for (int x = rect.left; x <= right; x += 2) {
        SetPixelV(dc, x, rect.top, color);
        SetPixelV(dc, x, bottom, color);
    }
    for (int y = rect.top + 2; y < bottom; y += 2) {
        SetPixelV(dc, rect.left, y, color);
        SetPixelV(dc, right, y, color);
    }
}

/// Updates the panel's date and time-zone links using its displayed date, configured zone, and offset.
static void UpdatePanelLinks(Widget* widget, const SYSTEMTIME& time) {
    if (widget == nullptr) {
        return;
    }
    RECT client = {};
    GetClientRect(widget->window, &client);
    wchar_t dateText[128] = {};
    GetDateFormatEx(LANGUAGE_LOCALES[widget->config.language], DATE_LONGDATE, &time, nullptr, dateText,
        ARRAYSIZE(dateText), nullptr);
    RECT dateRect = { PANEL_SIDE_PADDING, 7, client.right - PANEL_SIDE_PADDING, 34 };
    UpdatePanelLinkButton(widget->panelDateLink, widget->panelDateFont, dateText, dateRect);
    std::wstring zoneName = widget->config.showUtc ? L"UTC" : widget->config.timeZoneKey;
    if (!widget->config.showUtc) {
        for (size_t index = 0; index < timeZones.size(); index++) {
            if (_wcsicmp(timeZones[index].TimeZoneKeyName, widget->config.timeZoneKey.c_str()) == 0) {
                zoneName = timeZones[index].StandardName;
                break;
            }
        }
    }
    std::wstring zoneText = WT(widget, TXT_TIMEZONE);
    zoneText += L" ";
    zoneText += zoneName;
    if (widget->config.offsetMilliseconds != 0) {
        zoneText += L"  (" + FormatOffset(widget->config.offsetMilliseconds) + L")";
    }
    PanelLayout layout = CalculatePanelLayout(widget->config);
    UpdatePanelLinkButton(widget->panelTimeZoneLink, widget->panelTimeZoneFont, zoneText, layout.footer);
}

/// Handles panel-link pointer feedback, focus on clicks, and hover highlighting.
/// Treats double-clicks as button presses and removes the subclass on destruction.
static LRESULT CALLBACK PanelLinkButtonSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    UNREFERENCED_PARAMETER(referenceData);
    if (message == WM_SETCURSOR) {
        SetCursor(LoadCursorW(nullptr, IDC_HAND));
        return TRUE;
    }
    HWND parent = GetParent(window);
    Widget* widget = reinterpret_cast<Widget*>(GetWindowLongPtrW(parent, GWLP_USERDATA));
    if (message == WM_LBUTTONDOWN || message == WM_LBUTTONDBLCLK) {
        SetFocus(window);
        if (message == WM_LBUTTONDBLCLK) {
            return DefSubclassProc(window, WM_LBUTTONDOWN, wParam, lParam);
        }
    }
    if (widget != nullptr) {
        bool* hot = window == widget->panelDateLink ? &widget->panelDateHot : &widget->panelTimeZoneHot;
        if (message == WM_MOUSEMOVE && !*hot) {
            *hot = true;
            TRACKMOUSEEVENT tracking = {
                sizeof(tracking),
                TME_LEAVE,
                window,
                0
            };
            TrackMouseEvent(&tracking);
            InvalidateRect(window, nullptr, FALSE);
        } else if (message == WM_MOUSELEAVE) {
            *hot = false;
            InvalidateRect(window, nullptr, FALSE);
        }
    }
    if (message == WM_NCDESTROY) {
        RemoveWindowSubclass(window, PanelLinkButtonSubclassProc, subclassId);
    }
    return DefSubclassProc(window, message, wParam, lParam);
}

/// Creates the panel's owner-drawn date and time-zone buttons, assigns their fonts, and installs the date tooltip.
static void CreatePanelLinks(Widget* widget) {
    if (widget->config.type != WIDGET_PANEL) {
        return;
    }
    widget->panelDateLink = CreateWindowExW(0, L"BUTTON", L"", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_OWNERDRAW,
        0, 0, 0, 0, widget->window, reinterpret_cast<HMENU>(ID_PANEL_DATE_LINK), hInstance, nullptr);
    if (widget->panelDateLink == nullptr) {
        return;
    }
    SetWindowSubclass(widget->panelDateLink, PanelLinkButtonSubclassProc, ID_PANEL_DATE_LINK, 0);
    ApplyWidgetTheme(widget->panelDateLink, widget->config);
    ApplyPanelLinkFont(widget->panelDateLink, widget->config.panelTopFont, widget->config.fontAntialiasing, &widget->panelDateFont);
    widget->panelTimeZoneLink = CreateWindowExW(0, L"BUTTON", L"", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_OWNERDRAW,
        0, 0, 0, 0, widget->window, reinterpret_cast<HMENU>(ID_PANEL_TIME_ZONE_LINK), hInstance, nullptr);
    if (widget->panelTimeZoneLink == nullptr) {
        return;
    }
    SetWindowSubclass(widget->panelTimeZoneLink, PanelLinkButtonSubclassProc, ID_PANEL_TIME_ZONE_LINK, 0);
    ApplyWidgetTheme(widget->panelTimeZoneLink, widget->config);
    ApplyPanelLinkFont(widget->panelTimeZoneLink, widget->config.panelBottomFont,
        widget->config.fontAntialiasing, &widget->panelTimeZoneFont);
    SetWindowPos(widget->panelDateLink, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    SetWindowPos(widget->calendarChild, widget->panelDateLink, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    SetWindowPos(widget->panelTimeZoneLink, widget->calendarChild, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    SYSTEMTIME displayed = {};
    GetDisplayedTime(widget->config, &displayed);
    UpdatePanelLinks(widget, displayed);
    widget->panelDateTooltip = CreateWindowExW(WS_EX_TOPMOST | WS_EX_NOACTIVATE, TOOLTIPS_CLASSW, nullptr,
        WS_POPUP | TTS_ALWAYSTIP | TTS_NOPREFIX, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        widget->window, nullptr, hInstance, nullptr);
    if (widget->panelDateTooltip == nullptr) {
        return;
    }
    ApplyWidgetTheme(widget->panelDateTooltip, widget->config);
    TOOLINFOW information = {};
    information.cbSize = sizeof(information);
    information.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
    information.hwnd = widget->window;
    information.uId = reinterpret_cast<UINT_PTR>(widget->panelDateLink);
    information.lpszText = LPSTR_TEXTCALLBACKW;
    if (!SendMessageW(widget->panelDateTooltip, TTM_ADDTOOLW, 0, reinterpret_cast<LPARAM>(&information))) {
        DestroyWindow(widget->panelDateTooltip);
        widget->panelDateTooltip = nullptr;
    }
}

/// Paints the panel background, clock captions, times, weekdays, links, and alarm or identification feedback.
static void PaintPanelWidget(Widget* widget, HDC dc) {
    if (widget == nullptr) {
        return;
    }
    RECT full = {};
    GetClientRect(widget->window, &full);
    int width = full.right;
    int height = full.bottom;
    HBRUSH background = CreateSolidBrush(PanelBackgroundColor(widget));
    FillRect(dc, &full, background);
    DeleteObject(background);
    SYSTEMTIME time = {};
    GetDisplayedTime(widget->config, &time);
    UpdatePanelLinks(widget, time);
    HFONT timeFont = CreatePanelFont(widget->config.panelTimeFont, widget->config.fontAntialiasing);
    HFONT nameFont = CreatePanelFont(widget->config.panelTopFont, widget->config.fontAntialiasing);
    PanelLayout layout = CalculatePanelLayout(widget->config);
    bool additional = HasAdditionalClocks(widget->config);
    for (int index = 0; index <= ADDITIONAL_CLOCK_COUNT; index++) {
        if (index > 0 && !widget->config.additionalClocks[index - 1].enabled) {
            continue;
        }
        WidgetConfig clock = index == 0 ? widget->config : AdditionalClockConfiguration(widget->config, index - 1);
        wchar_t clockText[128] = {};
        GetDigitalTimeText(clock, clockText, ARRAYSIZE(clockText));
        DrawWidgetTimeText(dc, clockText, layout.times[index], timeFont, RGB(0, 0, 0), clock);
        if (additional) {
            GetDisplayedTime(clock, &time);
            wchar_t day[128] = {};
            GetDateFormatEx(LANGUAGE_LOCALES[clock.language], 0, &time, L"dddd", day, ARRAYSIZE(day), nullptr);
            DrawCenteredText(dc, day, layout.days[index], timeFont, RGB(0, 0, 0));
        }
        if (index > 0) {
            DrawCenteredText(dc, AdditionalClockName(widget->config, index - 1), layout.names[index - 1], nameFont,
                RGB(0, 0, 0), DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOPREFIX);
        }
    }
    DeleteObject(nameFont);
    DeleteObject(timeFont);
    bool identifyFrame = widget->identifyActive && widget->identifyPhase;
    bool alarmFrame = widget->alarmActive && widget->flashPhase;
    if (identifyFrame || alarmFrame) {
        HPEN pen = CreatePen(PS_SOLID, 3, identifyFrame ? IDENTIFY_COLOR : RGB(220, 0, 0));
        HGDIOBJ oldPen = SelectObject(dc, pen);
        HGDIOBJ oldBrush = SelectObject(dc, GetStockObject(HOLLOW_BRUSH));
        Rectangle(dc, 1, 1, width - 1, height - 1);
        SelectObject(dc, oldBrush);
        SelectObject(dc, oldPen);
        DeleteObject(pen);
    }
}

/// Paints a panel or opaque digital widget through an offscreen bitmap to avoid intermediate visible drawing.
static void PaintWidgetBuffered(Widget* widget, HWND window, HDC target, bool panel) {
    if (widget == nullptr || target == nullptr) {
        return;
    }
    RECT client = {};
    GetClientRect(window, &client);
    int width = client.right - client.left;
    int height = client.bottom - client.top;
    if (width <= 0 || height <= 0) {
        return;
    }
    HDC buffer = CreateCompatibleDC(target);
    HBITMAP bitmap = CreateCompatibleBitmap(target, width, height);
    if (buffer == nullptr || bitmap == nullptr) {
        if (bitmap != nullptr) {
            DeleteObject(bitmap);
        }
        if (buffer != nullptr) {
            DeleteDC(buffer);
        }
        if (panel) {
            PaintPanelWidget(widget, target);
        } else {
            PaintOpaqueDigitalWidget(widget, window, target);
        }
        return;
    }
    HGDIOBJ oldBitmap = SelectObject(buffer, bitmap);
    if (panel) {
        PaintPanelWidget(widget, buffer);
    } else {
        PaintOpaqueDigitalWidget(widget, window, buffer);
    }
    BitBlt(target, 0, 0, width, height, buffer, 0, 0, SRCCOPY);
    SelectObject(buffer, oldBitmap);
    DeleteObject(bitmap);
    DeleteDC(buffer);
}

/// Updates a visible widget through the rendering path appropriate to its type, resizing only when needed.
static void RenderWidget(Widget* widget) {
    if (widget == nullptr || !widget->config.visible || widget->window == nullptr) {
        return;
    }
    if (widget->config.type == WIDGET_ANALOG) {
        if (widget->analogChild != nullptr) {
            RenderAnalogWidget(widget);
        }
        return;
    }
    if (widget->config.type == WIDGET_PANEL) {
        UpdateAnalogTime(widget);
        SYSTEMTIME displayed = {};
        GetDisplayedTime(widget->config, &displayed);
        int dateKey = displayed.wYear * 10000 + displayed.wMonth * 100 + displayed.wDay;
        if (!widget->rendered || widget->lastPanelDateKey != dateKey || widget->alarmActive) {
            widget->lastPanelDateKey = dateKey;
            InvalidateRect(widget->window, nullptr, FALSE);
        } else {
            PanelLayout layout = CalculatePanelLayout(widget->config);
            for (int index = 0; index <= ADDITIONAL_CLOCK_COUNT; index++) {
                if (index > 0 && !widget->config.additionalClocks[index - 1].enabled) {
                    continue;
                }
                RECT textRect = layout.times[index];
                textRect.bottom = std::max(textRect.bottom, layout.days[index].bottom);
                InvalidateRect(widget->window, &textRect, FALSE);
            }
        }
        widget->rendered = true;
        return;
    }
    if (widget->config.type == WIDGET_CALENDAR) {
        widget->rendered = true;
        return;
    }
    if (widget->config.type == WIDGET_FULLSCREEN) {
        InvalidateRect(widget->window, nullptr, FALSE);
        UpdateWindow(widget->window);
        for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
            InvalidateRect(widget->fullscreenWindows[index], nullptr, FALSE);
            UpdateWindow(widget->fullscreenWindows[index]);
        }
        widget->rendered = true;
        return;
    }
    if (widget->config.transparentBackground) {
        RenderCustomWidget(widget);
    } else {
        int desiredWidth = 0;
        int desiredHeight = 0;
        GetWidgetDimensions(widget->config, &desiredWidth, &desiredHeight);
        RECT current = {};
        if (GetWindowRect(widget->window, &current)
                && (current.right - current.left != desiredWidth || current.bottom - current.top != desiredHeight)) {
            ResizeWidgetPreservingWorkAreaAttachment(widget, desiredWidth, desiredHeight,
                SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
        }
        InvalidateRect(widget->window, nullptr, FALSE);
        UpdateWindow(widget->window);
        widget->rendered = true;
    }
}

/// Requests the rendering needed to display or clear a widget's identification highlight.
static void RenderWidgetIdentification(Widget* widget) {
    if (widget == nullptr || widget->window == nullptr) {
        return;
    }
    if (widget->config.type == WIDGET_ANALOG) {
        RenderAnalogWidget(widget);
    } else if (widget->config.type == WIDGET_DIGITAL) {
        RenderCustomWidget(widget);
    } else if (widget->config.type == WIDGET_FULLSCREEN) {
        InvalidateRect(widget->window, nullptr, FALSE);
        for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
            InvalidateRect(widget->fullscreenWindows[index], nullptr, FALSE);
        }
    } else if (widget->config.type == WIDGET_PANEL) {
        InvalidateRect(widget->window, nullptr, FALSE);
    } else if (widget->config.type == WIDGET_CALENDAR && widget->calendarChild != nullptr) {
        InvalidateRect(widget->calendarChild, nullptr, TRUE);
    }
}

/// Changes the widget's topmost state without activation. Explicitly unpinning may also send it to the back.
static void ApplyWidgetZOrder(Widget* widget, bool sendToBack = false) {
    if (widget == nullptr || widget->window == nullptr) {
        return;
    }
    bool topMost = widget->config.topMost || widget->config.type == WIDGET_FULLSCREEN;
    HWND insertAfter = topMost ? HWND_TOPMOST : HWND_NOTOPMOST;
    if (!topMost && sendToBack) {
        insertAfter = HWND_BOTTOM;
    }
    SetWindowPos(widget->window, insertAfter, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
        SetWindowPos(widget->fullscreenWindows[index], insertAfter, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
}

/// Raises the widget's windows within the appropriate normal or topmost group without taking focus.
static void BringWidgetForward(Widget* widget) {
    if (widget == nullptr || widget->window == nullptr) {
        return;
    }
    HWND insertAfter = widget->config.topMost || widget->config.type == WIDGET_FULLSCREEN ? HWND_TOPMOST : HWND_TOP;
    SetWindowPos(widget->window, insertAfter, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
        SetWindowPos(widget->fullscreenWindows[index], insertAfter, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
}

/// Brings an alarming widget to the foreground and then restores its configured topmost policy.
static void RaiseWidgetForAlarm(Widget* widget) {
    if (widget == nullptr || widget->window == nullptr) {
        return;
    }
    UINT flags = SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE;
    SetWindowPos(widget->window, HWND_TOPMOST, 0, 0, 0, 0, flags);
    for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
        SetWindowPos(widget->fullscreenWindows[index], HWND_TOPMOST, 0, 0, 0, 0, flags);
    }
    SetForegroundWindowEx(widget->window);
    if (!widget->config.topMost && widget->config.type != WIDGET_FULLSCREEN) {
        SetWindowPos(widget->window, HWND_NOTOPMOST, 0, 0, 0, 0, flags);
        for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
            SetWindowPos(widget->fullscreenWindows[index], HWND_NOTOPMOST, 0, 0, 0, 0, flags);
        }
    }
}

/// Temporarily reveals and raises a widget, starts its identification highlight, and remembers state to restore
/// afterward.
static void IdentifyWidget(Widget* widget) {
    if (widget == nullptr || widget->window == nullptr) {
        return;
    }
    if (!widget->identifyActive) {
        widget->identifyRestoreHidden = !widget->config.visible;
        widget->identifyRestoreNotTopmost = !widget->config.topMost;
        if (widget->identifyRestoreHidden) {
            widget->config.visible = true;
            ShowWindow(widget->window, SW_SHOWNOACTIVATE);
            if (!widget->fullscreenPreview) {
                for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
                    ShowWindow(widget->fullscreenWindows[index], SW_SHOWNOACTIVATE);
                }
            }
        }
    }
    widget->identifyActive = true;
    widget->identifyPhase = true;
    widget->identifyEndTick = GetTickCount64() + 1600;
    SetWindowPos(widget->window, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
        SetWindowPos(widget->fullscreenWindows[index], HWND_TOPMOST, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
    RenderWidgetIdentification(widget);
}

/// Ends the identification highlight and restores any temporary visibility and stacking changes.
static void FinishWidgetIdentification(Widget* widget) {
    if (widget == nullptr || !widget->identifyActive) {
        return;
    }
    widget->identifyActive = false;
    widget->identifyPhase = false;
    RenderWidgetIdentification(widget);
    if (widget->identifyRestoreHidden) {
        widget->config.visible = false;
        ShowWindow(widget->window, SW_HIDE);
        for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
            ShowWindow(widget->fullscreenWindows[index], SW_HIDE);
        }
    }
    if (widget->identifyRestoreNotTopmost) {
        ApplyWidgetZOrder(widget);
    }
    widget->identifyRestoreHidden = false;
    widget->identifyRestoreNotTopmost = false;
}

/// Requests audio cancellation, closes the widget-owned event handles, and advances the generation to reject stale
/// notifications.
static void CloseWidgetAudio(Widget* widget) {
    if (widget == nullptr) {
        return;
    }
    widget->audioGeneration++;
    if (widget->audioStopEvent != nullptr) {
        SetEvent(widget->audioStopEvent);
        CloseHandle(widget->audioStopEvent);
        widget->audioStopEvent = nullptr;
    }
    if (widget->audioMuteEvent != nullptr) {
        CloseHandle(widget->audioMuteEvent);
        widget->audioMuteEvent = nullptr;
    }
}

/// Applies the selected draft widget's mute state to the active alarm preview.
static void UpdateSettingsPreviewMute() {
    if (settingsPreviewMuteEvent == nullptr
            || selectedDraftIndex < 0
            || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
        return;
    }
    SetAudioPlaybackMuted(settingsPreviewMuteEvent, settingsDraft[selectedDraftIndex].soundsMuted);
}

/// Copies a live widget's mute state into its settings draft and updates the selected checkbox when applicable.
static void SynchronizeWidgetSoundsMuted(const Widget* widget) {
    if (hSettings == nullptr || !IsWindow(hSettings) || widget == nullptr) {
        return;
    }
    for (size_t index = 0; index < settingsDraft.size(); index++) {
        if (settingsDraft[index].id != widget->config.id) {
            continue;
        }
        settingsDraft[index].soundsMuted = widget->config.soundsMuted;
        if (static_cast<int>(index) == selectedDraftIndex) {
            SetCheck(hSoundsMutedCheck, widget->config.soundsMuted);
        }
        break;
    }
}

/// Updates a sound-capable widget's mute state across audio playback, shared time signals, and its settings preview.
static void ApplyWidgetSoundsMuted(Widget* widget, bool muted) {
    if (widget == nullptr || !WidgetSupportsSound(widget->config.type)) {
        return;
    }
    widget->config.soundsMuted = muted;
    SetAudioPlaybackMuted(widget->audioMuteEvent, muted);
    UpdateCurrentTimeSignalMute();
    if (selectedDraftIndex >= 0
        && selectedDraftIndex < static_cast<int>(settingsDraft.size())
        && settingsDraft[selectedDraftIndex].id == widget->config.id) {
        SetAudioPlaybackMuted(settingsPreviewMuteEvent, muted);
    }
}

/// Changes a widget's mute state when needed, synchronizes open settings, and saves committed settings.
static void SetWidgetSoundsMuted(Widget* widget, bool muted) {
    if (widget == nullptr || !WidgetSupportsSound(widget->config.type) || widget->config.soundsMuted == muted) {
        return;
    }
    ApplyWidgetSoundsMuted(widget, muted);
    SynchronizeWidgetSoundsMuted(widget);
    SaveSettingsWithoutAppearancePreviews();
}

/// Mutes all currently audible widgets or restores the previous set of widgets muted by this command, then saves
/// settings.
static void ToggleAllWidgetSounds() {
    bool anyUnmuted = false;
    for (const std::unique_ptr<Widget>& widget : widgets) {
        if (WidgetSupportsSound(widget->config.type) && !widget->config.soundsMuted) {
            anyUnmuted = true;
            break;
        }
    }
    if (anyUnmuted) {
        lastMutedWidgetIds.clear();
        for (size_t index = 0; index < widgets.size(); index++) {
            Widget* widget = widgets[index].get();
            if (WidgetSupportsSound(widget->config.type) && !widget->config.soundsMuted) {
                lastMutedWidgetIds.push_back(widget->config.id);
                ApplyWidgetSoundsMuted(widget, true);
                SynchronizeWidgetSoundsMuted(widget);
            }
        }
    } else {
        std::vector<int> widgetIds = lastMutedWidgetIds;
        if (widgetIds.empty()) {
            for (size_t index = 0; index < widgets.size(); index++) {
                if (WidgetSupportsSound(widgets[index]->config.type)) {
                    widgetIds.push_back(widgets[index]->config.id);
                }
            }
        }
        for (size_t index = 0; index < widgetIds.size(); index++) {
            Widget* widget = FindWidgetById(widgetIds[index]);
            if (widget != nullptr && widget->config.soundsMuted) {
                ApplyWidgetSoundsMuted(widget, false);
                SynchronizeWidgetSoundsMuted(widget);
            }
        }
    }
    SaveSettingsWithoutAppearancePreviews();
}

/// Returns the owning widget for a main, child, or additional fullscreen input window, or null when none matches.
static Widget* WidgetFromInputWindow(HWND window) {
    for (size_t widgetIndex = 0; widgetIndex < widgets.size(); widgetIndex++) {
        Widget* widget = widgets[widgetIndex].get();
        if (window == widget->window || IsChild(widget->window, window)) {
            return widget;
        }
        for (size_t windowIndex = 0; windowIndex < widget->fullscreenWindows.size(); windowIndex++) {
            HWND fullscreenWindow = widget->fullscreenWindows[windowIndex];
            if (window == fullscreenWindow || IsChild(fullscreenWindow, window)) {
                return widget;
            }
        }
    }
    return nullptr;
}

/// Clears cursor-idle tracking for the tracked window and restores the pointer if it was hidden there.
static void ResetFullscreenCursor(HWND window) {
    if (window != hFullscreenCursorWindow) {
        return;
    }
    POINT position = {};
    if (fullscreenCursorHidden && GetCursorPos(&position) && WindowFromPoint(position) == window) {
        SetCursor(LoadCursorW(nullptr, IDC_ARROW));
    }
    hFullscreenCursorWindow = nullptr;
    fullscreenCursorHidden = false;
}

/// Tracks pointer activity and hides an idle cursor over fullscreen clocks and blackout windows.
/// Excludes settings previews and active menu or capture interactions; returns whether this policy applies.
static bool UpdateFullscreenCursor(bool mouseActivity = false, bool forceCursor = false) {
    POINT position = {};
    bool positionAvailable = GetCursorPos(&position) != FALSE;
    HWND window = positionAvailable ? WindowFromPoint(position) : nullptr;
    if (window == nullptr) {
        ResetFullscreenCursor(hFullscreenCursorWindow);
        return false;
    }
    Widget* widget = WidgetFromInputWindow(window);
    bool fullscreen = widget != nullptr
        && widget->config.type == WIDGET_FULLSCREEN
        && widget->config.visible
        && !widget->fullscreenPreview;
    bool blackout = std::find(blackoutWindows.begin(), blackoutWindows.end(), window) != blackoutWindows.end();
    if (!fullscreen && !blackout) {
        ResetFullscreenCursor(hFullscreenCursorWindow);
        return false;
    }
    GUITHREADINFO information = {};
    information.cbSize = sizeof(information);
    bool interacting = false;
    if (GetGUIThreadInfo(0, &information)) {
        interacting = information.flags & (GUI_INMENUMODE | GUI_POPUPMENUMODE | GUI_SYSTEMMENUMODE | GUI_INMOVESIZE)
            || information.hwndCapture != nullptr && information.hwndCapture != window;
    }
    if (interacting) {
        ResetFullscreenCursor(hFullscreenCursorWindow);
        return false;
    }
    bool changedWindow = window != hFullscreenCursorWindow;
    bool moved = position.x != fullscreenCursorPosition.x || position.y != fullscreenCursorPosition.y;
    bool buttonDown = GetAsyncKeyState(VK_LBUTTON) < 0
        || GetAsyncKeyState(VK_RBUTTON) < 0
        || GetAsyncKeyState(VK_MBUTTON) < 0
        || GetAsyncKeyState(VK_XBUTTON1) < 0
        || GetAsyncKeyState(VK_XBUTTON2) < 0;
    ULONGLONG tick = GetTickCount64();
    if (changedWindow || moved || mouseActivity || buttonDown) {
        fullscreenCursorActivityTick = tick;
    }
    bool hidden = tick - fullscreenCursorActivityTick >= FULLSCREEN_CURSOR_IDLE_DELAY;
    if (changedWindow || hidden != fullscreenCursorHidden || forceCursor) {
        SetCursor(hidden ? nullptr : LoadCursorW(nullptr, IDC_ARROW));
    }
    hFullscreenCursorWindow = window;
    fullscreenCursorPosition = position;
    fullscreenCursorHidden = hidden;
    return true;
}

/// Updates fullscreen cursor activity from mouse and lifecycle messages and handles applicable client-area cursor
/// requests.
static bool HandleFullscreenCursorMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_SETCURSOR:
            if (LOWORD(lParam) == HTCLIENT) {
                return UpdateFullscreenCursor(false, true);
            }
            break;
        case WM_MOUSEMOVE:
            UpdateFullscreenCursor();
            break;
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONDBLCLK:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONDBLCLK:
        case WM_XBUTTONDOWN:
        case WM_XBUTTONDBLCLK:
        case WM_MOUSEWHEEL:
        case WM_MOUSEHWHEEL:
        case WM_ENTERMENULOOP:
        case WM_EXITMENULOOP:
            UpdateFullscreenCursor(true);
            break;
        case WM_SHOWWINDOW:
            if (!wParam) {
                ResetFullscreenCursor(window);
            }
            break;
        case WM_NCDESTROY:
            ResetFullscreenCursor(window);
            break;
    }
    return false;
}

/// Stops a widget's audio and visual alarm and removes its alarm contribution from shared time signals.
/// Preserves other contributors and remembers cancellation so the same alarm sequence is not immediately restarted.
static void StopWidgetAlarm(Widget* widget) {
    if (widget == nullptr) {
        return;
    }
    CloseWidgetAudio(widget);
    widget->alarmActive = false;
    widget->flashPhase = false;
    ULONGLONG now = CurrentFileTimeValue();
    for (TimeSignalSourceGroup& group : currentTimeSignalSources) {
        if (group.target > now + 5 * 10000000ULL) {
            continue;
        }
        if (std::find(group.alarmWidgetIds.begin(), group.alarmWidgetIds.end(), widget->config.id) !=
                group.alarmWidgetIds.end()) {
            group.cancelledAlarmWidgetIds.push_back(widget->config.id);
        }
        group.alarmWidgetIds.erase(std::remove(group.alarmWidgetIds.begin(), group.alarmWidgetIds.end(),
            widget->config.id), group.alarmWidgetIds.end());
        if (group.regularWidgetIds.empty() && group.alarmWidgetIds.empty()) {
            CancelTimeSignalPlayback(group.target);
        }
    }
    UpdateCurrentTimeSignalMute();
    RenderWidget(widget);
    if (widget->config.type == WIDGET_PANEL && widget->window != nullptr) {
        InvalidateRect(widget->window, nullptr, FALSE);
    }
}

/// Stops every widget's active audio, visual alarm, and alarm time-signal contribution.
static void StopAllAlarms() {
    for (size_t index = 0; index < widgets.size(); index++) {
        StopWidgetAlarm(widgets[index].get());
    }
}

/// Shows and raises a widget, starts its visual alarm, and launches configured audio, local command, or remote URL
/// actions.
static void StartWidgetAlarm(Widget* widget) {
    if (widget == nullptr) {
        return;
    }
    CloseWidgetAudio(widget);
    widget->alarmActive = true;
    widget->flashPhase = true;
    if (!widget->config.visible) {
        SetWidgetVisible(widget, true);
    }
    RaiseWidgetForAlarm(widget);
    if (widget->config.runCommand && !widget->config.command.empty()) {
        if (LooksLikeAudio(widget->config.command)) {
            StartAudioPlaybackAsync(widget->config.command, widget->config.loopAudio, widget->config.soundsMuted,
                std::make_shared<std::atomic<int>>(widget->config.alarmVolume), hController, WM_AUDIO_FINISHED,
                widget->config.id, widget->audioGeneration, &widget->audioStopEvent, &widget->audioMuteEvent);
        } else {
            StartLocalCommandAsync(widget->config.command);
        }
    }
    if (widget->config.callRemoteScript) {
        StartRemoteScriptAsync(widget->config.remoteScriptUrl);
    }
    RenderWidget(widget);
}

/// Checks displayed-minute transitions against the enabled weekdays and alarm time, preventing duplicate activation for
/// that minute.
static void CheckWidgetAlarm(Widget* widget) {
    if (widget == nullptr || !WidgetSupportsSound(widget->config.type)) {
        return;
    }
    SYSTEMTIME time = {};
    GetDisplayedTime(widget->config, &time);
    int date = time.wYear * 10000 + time.wMonth * 100 + time.wDay;
    int minute = time.wHour * 60 + time.wMinute;
    bool minuteChanged = widget->lastObservedAlarmDate >= 0
        && widget->lastObservedAlarmMinute >= 0
        && (widget->lastObservedAlarmDate != date || widget->lastObservedAlarmMinute != minute);
    widget->lastObservedAlarmDate = date;
    widget->lastObservedAlarmMinute = minute;
    if (!widget->config.alarmEnabled || !minuteChanged) {
        return;
    }
    bool shouldStartAlarm = AlarmEnabledOnDay(widget->config, time.wDayOfWeek)
        && time.wHour == widget->config.alarmHour
        && time.wMinute == widget->config.alarmMinute
        && (widget->lastAlarmDate != date || widget->lastAlarmMinute != minute);
    if (shouldStartAlarm) {
        widget->lastAlarmDate = date;
        widget->lastAlarmMinute = minute;
        StartWidgetAlarm(widget);
    }
}

/// Copies a nonfullscreen widget's current screen position into live and draft settings, then saves without appearance
/// previews.
static void SaveWidgetPosition(Widget* widget) {
    if (widget == nullptr || widget->window == nullptr || widget->config.type == WIDGET_FULLSCREEN) {
        return;
    }
    RECT rect = {};
    if (GetWindowRect(widget->window, &rect)) {
        widget->config.x = rect.left;
        widget->config.y = rect.top;
        std::vector<WidgetConfig>* configurations[] = {
            &settingsDraft,
            &settingsAppliedWidgets,
            &settingsAppearanceOriginals
        };
        for (std::vector<WidgetConfig>* group : configurations) {
            for (WidgetConfig& config : *group) {
                if (config.id == widget->config.id) {
                    config.x = rect.left;
                    config.y = rect.top;
                    break;
                }
            }
        }
        SaveSettingsWithoutAppearancePreviews();
    }
}

/// Temporarily substitutes committed widget configurations while saving, then restores the active appearance previews.
static void SaveSettingsWithoutAppearancePreviews() {
    std::vector<std::pair<Widget*, WidgetConfig>> previewConfigurations;
    for (size_t idIndex = 0; idIndex < settingsAppearancePreviewIds.size(); idIndex++) {
        Widget* previewWidget = FindWidgetById(settingsAppearancePreviewIds[idIndex]);
        if (previewWidget == nullptr) {
            continue;
        }
        for (size_t originalIndex = 0; originalIndex < settingsAppearanceOriginals.size(); originalIndex++) {
            if (settingsAppearanceOriginals[originalIndex].id == previewWidget->config.id) {
                previewConfigurations.push_back(std::make_pair(previewWidget, previewWidget->config));
                previewWidget->config = settingsAppearanceOriginals[originalIndex];
                break;
            }
        }
    }
    SaveAllSettings();
    for (size_t index = 0; index < previewConfigurations.size(); index++) {
        previewConfigurations[index].first->config = previewConfigurations[index].second;
    }
}

/// Identifies a widget and makes its visibility persistent across live state, the draft, and saved settings.
static void IdentifyAndShowWidget(Widget* widget, int draftIndex) {
    if (widget == nullptr || draftIndex < 0 || draftIndex >= static_cast<int>(settingsDraft.size())) {
        return;
    }
    IdentifyWidget(widget);
    widget->identifyRestoreHidden = false;
    widget->config.visible = true;
    settingsDraft[draftIndex].visible = true;
    for (size_t index = 0; index < settingsAppearanceOriginals.size(); index++) {
        if (settingsAppearanceOriginals[index].id == widget->config.id) {
            settingsAppearanceOriginals[index].visible = true;
            break;
        }
    }
    if (draftIndex == selectedDraftIndex && hVisibleCheck != nullptr) {
        SendMessageW(hVisibleCheck, BM_SETCHECK, BST_CHECKED, 0);
    }
    RefreshFullscreenPresentation();
    SaveSettingsWithoutAppearancePreviews();
}

/// Saves a fullscreen widget's reduced preview position without replacing its fullscreen monitor placement.
static void SaveFullscreenPreviewPosition(Widget* widget) {
    if (widget == nullptr || widget->window == nullptr || !widget->fullscreenPreview) {
        return;
    }
    RECT rect = {};
    if (!GetWindowRect(widget->window, &rect)) {
        return;
    }
    widget->config.previewX = rect.left;
    widget->config.previewY = rect.top;
    for (size_t index = 0; index < settingsDraft.size(); index++) {
        if (settingsDraft[index].id == widget->config.id) {
            settingsDraft[index].previewX = rect.left;
            settingsDraft[index].previewY = rect.top;
            break;
        }
    }
    for (size_t index = 0; index < settingsAppearanceOriginals.size(); index++) {
        if (settingsAppearanceOriginals[index].id == widget->config.id) {
            settingsAppearanceOriginals[index].previewX = rect.left;
            settingsAppearanceOriginals[index].previewY = rect.top;
            break;
        }
    }
    SaveSettingsWithoutAppearancePreviews();
}

/// Creates and subclasses the primary native clock control, placing panel clocks onscreen and layered-widget source
/// controls offscreen.
static void CreateAnalogChild(Widget* widget) {
    if (widget == nullptr) {
        return;
    }
    int childX = -widget->config.size - 2;
    int childY = 0;
    if (widget->config.type == WIDGET_PANEL) {
        POINT clockPosition = {};
        GetPanelLayout(widget->config, nullptr, &clockPosition, nullptr);
        childX = clockPosition.x;
        childY = clockPosition.y;
    }
    bool showAnalogSeconds = widget->config.showSeconds && AnalogClockSupportsSeconds(widget->config.size);
    widget->analogChild = CreateAnalogClockControl(widget->window, childX, childY, widget->config.size,
        showAnalogSeconds, true);
    if (widget->analogChild != nullptr) {
        ApplyWidgetTheme(widget->analogChild, widget->config);
        if (!ConfigureAnalogClockControl(widget->analogChild, widget->config.size, showAnalogSeconds)) {
            DestroyWindow(widget->analogChild);
            widget->analogChild = nullptr;
            return;
        }
        widget->analogProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(widget->analogChild, GWLP_WNDPROC,
            reinterpret_cast<LONG_PTR>(AnalogChildProc)));
        UpdateAnalogTime(widget);
        if (widget->config.type == WIDGET_PANEL) {
            CaptureAnalogBackground(widget);
        }
    }
}

/// Creates and subclasses each enabled additional panel clock with its own size and no second hand.
static void CreateAdditionalAnalogChildren(Widget* widget) {
    if (widget->config.type != WIDGET_PANEL) {
        return;
    }
    PanelLayout layout = CalculatePanelLayout(widget->config);
    for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
        if (!widget->config.additionalClocks[index].enabled) {
            continue;
        }
        const RECT& rect = layout.clocks[index + 1];
        int size = rect.right - rect.left;
        HWND child = CreateAnalogClockControl(widget->window, rect.left, rect.top, size, false, true);
        if (child == nullptr) {
            continue;
        }
        ApplyWidgetTheme(child, widget->config);
        if (!ConfigureAnalogClockControl(child, size, false)) {
            DestroyWindow(child);
            continue;
        }
        if (!SetWindowSubclass(child, AdditionalAnalogChildProc, index + 1, index)) {
            DestroyWindow(child);
            continue;
        }
        widget->additionalAnalogChildren[index] = child;
    }
    UpdateAnalogTime(widget);
}

/// Changes the primary clock's second-hand state in place when possible, otherwise replaces only that native child.
static bool UpdateAnalogSeconds(Widget* widget) {
    if (widget == nullptr || widget->window == nullptr || widget->analogChild == nullptr) {
        return false;
    }
    bool showAnalogSeconds = widget->config.showSeconds && AnalogClockSupportsSeconds(widget->config.size);
    if (SetAnalogClockSeconds(widget->analogChild, widget->config.size, showAnalogSeconds)) {
        if (widget->config.type == WIDGET_PANEL) {
            InvalidateRect(widget->analogChild, nullptr, FALSE);
        }
        return true;
    }
    int childX = -widget->config.size - 2;
    int childY = 0;
    if (widget->config.type == WIDGET_PANEL) {
        POINT clockPosition = {};
        GetPanelLayout(widget->config, nullptr, &clockPosition, nullptr);
        childX = clockPosition.x;
        childY = clockPosition.y;
    }
    HWND replacement = CreateAnalogClockControl(widget->window, childX, childY, widget->config.size,
        showAnalogSeconds, false);
    if (replacement == nullptr) {
        return false;
    }
    ApplyWidgetTheme(replacement, widget->config);
    if (!ConfigureAnalogClockControl(replacement, widget->config.size, showAnalogSeconds)) {
        DestroyWindow(replacement);
        return false;
    }
    WNDPROC replacementProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(replacement, GWLP_WNDPROC,
        reinterpret_cast<LONG_PTR>(AnalogChildProc)));
    if (replacementProc == nullptr) {
        DestroyWindow(replacement);
        return false;
    }
    HWND previousChild = widget->analogChild;
    WNDPROC previousProc = widget->analogProc;
    widget->analogChild = replacement;
    widget->analogProc = replacementProc;
    widget->analogBackground = CLR_INVALID;
    UpdateAnalogTime(widget);
    if (widget->config.type == WIDGET_PANEL) {
        CaptureAnalogBackground(widget);
    }
    SetWindowPos(replacement, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
    RedrawWindow(replacement, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
    if (previousProc != nullptr) {
        SetWindowLongPtrW(previousChild, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(previousProc));
    }
    DestroyWindow(previousChild);
    if (widget->config.type == WIDGET_ANALOG) {
        RenderAnalogWidget(widget);
    }
    return true;
}

/// Creates and subclasses a native calendar with the widget's locale, font, weekday, week-number, and Today-row
/// settings.
static void CreateCalendarChild(Widget* widget) {
    if (widget == nullptr) {
        return;
    }
    SIZE calendarSize = GetCalendarSize(widget->config, true);
    int childX = 0;
    int childY = 0;
    if (widget->config.type == WIDGET_PANEL) {
        RECT calendarRect = {};
        GetPanelLayout(widget->config, &calendarRect, nullptr, nullptr);
        childX = calendarRect.left;
        childY = calendarRect.top;
    }
    DWORD style = WS_CHILD | WS_TABSTOP | (widget->config.weekNumbers ? MCS_WEEKNUMBERS : 0);
    if (widget->config.type == WIDGET_PANEL || !widget->config.showToday) {
        style |= MCS_NOTODAY;
    }
    CalendarLocaleScope localeScope(LANGUAGE_LOCALES[widget->config.language]);
    widget->calendarChild = CreateWindowExW(0, MONTHCAL_CLASSW, L"", style, 0, 0, 0, 0, widget->window,
        reinterpret_cast<HMENU>(114), hInstance, nullptr);
    if (widget->calendarChild != nullptr) {
        ApplyWidgetTheme(widget->calendarChild, widget->config);
    }
    if (widget->calendarChild != nullptr) {
        ApplyCalendarFont(widget);
        MonthCal_SetCalendarBorder(widget->calendarChild, TRUE, 0);
        SYSTEMTIME displayed = {};
        GetDisplayedTime(widget->config, &displayed);
        MonthCal_SetToday(widget->calendarChild, &displayed);
        MonthCal_SetCurSel(widget->calendarChild, &displayed);
        widget->lastCalendarDateKey = displayed.wYear * 10000 + displayed.wMonth * 100 + displayed.wDay;
        MonthCal_SetFirstDayOfWeek(widget->calendarChild, widget->config.sundayFirst ? 6 : 0);
        RECT minimum = {};
        if (MonthCal_GetMinReqRect(widget->calendarChild, &minimum)) {
            calendarSize.cx = minimum.right - minimum.left;
            calendarSize.cy = minimum.bottom - minimum.top;
        }
        SetWindowPos(widget->calendarChild, nullptr, childX, childY, calendarSize.cx, calendarSize.cy,
            SWP_NOZORDER | SWP_NOACTIVATE);
        widget->calendarProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(widget->calendarChild, GWLP_WNDPROC,
            reinterpret_cast<LONG_PTR>(CalendarChildProc)));
        ShowWindow(widget->calendarChild, SW_SHOWNOACTIVATE);
        RedrawWindow(widget->calendarChild, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_UPDATENOW);
    }
}

/// Calculates bounded preview dimensions from the selected monitor's aspect ratio, returning false if geometry is
/// unavailable.
static bool GetFullscreenPreviewDimensions(const WidgetConfig& config, int* width, int* height) {
    if (width == nullptr || height == nullptr) {
        return false;
    }
    RECT monitorRect = {};
    if (!GetPrimarySelectedMonitorRect(config, &monitorRect)) {
        return false;
    }
    int monitorWidth = monitorRect.right - monitorRect.left;
    int monitorHeight = monitorRect.bottom - monitorRect.top;
    *width = std::min(480, std::max(240, monitorWidth / 4));
    *height = std::max(120, MulDiv(*width, monitorHeight, std::max(1, monitorWidth)));
    if (*height > 300) {
        *height = 300;
        *width = std::max(160, MulDiv(*height, monitorWidth, std::max(1, monitorHeight)));
    }
    return true;
}

/// Converts a fullscreen widget's main window to its settings preview and hides its additional fullscreen windows.
static bool SetFullscreenPreview(Widget* widget) {
    if (widget == nullptr || widget->window == nullptr || widget->config.type != WIDGET_FULLSCREEN) {
        return false;
    }
    RECT monitorRect = {};
    if (!GetPrimarySelectedMonitorRect(widget->config, &monitorRect)) {
        return false;
    }
    int previewWidth = 0;
    int previewHeight = 0;
    if (!GetFullscreenPreviewDimensions(widget->config, &previewWidth, &previewHeight)) {
        return false;
    }
    int monitorWidth = monitorRect.right - monitorRect.left;
    int monitorHeight = monitorRect.bottom - monitorRect.top;
    int previewX = widget->config.previewX == CW_USEDEFAULT
        ? monitorRect.left + (monitorWidth - previewWidth) / 2
        : widget->config.previewX;
    int previewY = widget->config.previewY == CW_USEDEFAULT
        ? monitorRect.top + (monitorHeight - previewHeight) / 2
        : widget->config.previewY;
    RECT currentRect = {};
    if (widget->fullscreenPreview && GetWindowRect(widget->window, &currentRect)) {
        POINT position = { currentRect.left, currentRect.top };
        GetPositionPreservingWorkAreaAttachment(widget->window, previewWidth, previewHeight, &position);
        previewX = position.x;
        previewY = position.y;
    }
    ClampFormPosition(&previewX, &previewY, previewWidth, previewHeight);
    ResetFullscreenCursor(widget->window);
    widget->fullscreenPreview = true;
    SetWindowPos(widget->window, HWND_TOPMOST, previewX, previewY, previewWidth, previewHeight, SWP_NOACTIVATE);
    for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
        ShowWindow(widget->fullscreenWindows[index], SW_HIDE);
    }
    return true;
}

/// Creates a widget's main and required child or monitor windows and applies layout, theme, rendering, and visibility.
/// Activates the main window when replacing an active widget; other creation paths leave activation unchanged.
static void CreateWidgetWindow(Widget* widget, bool activate = false) {
    if (widget == nullptr) {
        return;
    }
    if (widget->config.type == WIDGET_ANALOG || widget->config.type == WIDGET_PANEL) {
        widget->config.size = NormalizeAnalogClockSize(widget->config.size);
        for (AdditionalClockConfig& clock : widget->config.additionalClocks) {
            clock.size = NormalizeAnalogClockSize(clock.size);
        }
    }
    bool fullscreen = widget->config.type == WIDGET_FULLSCREEN;
    std::vector<const DisplayMonitor*> selectedMonitors;
    if (fullscreen) {
        selectedMonitors = SelectedDisplayMonitors(widget->config);
        if (!selectedMonitors.empty()) {
            widget->config.x = selectedMonitors[0]->rect.left;
            widget->config.y = selectedMonitors[0]->rect.top;
        }
    } else {
        ClampWidgetPosition(&widget->config);
    }
    int width = 0;
    int height = 0;
    GetWidgetDimensions(widget->config, &width, &height);
    bool parentedControl = widget->config.type == WIDGET_PANEL || widget->config.type == WIDGET_CALENDAR;
    DWORD extended = WS_EX_TOOLWINDOW | (widget->config.topMost || fullscreen ? WS_EX_TOPMOST : 0);
    if (!fullscreen && (!parentedControl || widget->config.opacity < 100)) {
        extended |= WS_EX_LAYERED;
    }
    DWORD style = WS_POPUP | (parentedControl ? WS_CLIPCHILDREN : 0);
    bool nativeBorder = widget->config.type == WIDGET_CALENDAR
        || widget->config.type == WIDGET_PANEL
        || widget->config.type == WIDGET_DIGITAL && !widget->config.transparentBackground;
    if (nativeBorder) {
        ApplyNativeBorderStyle(widget->config.borderStyle, &style, &extended);
    }
    widget->window = CreateWindowExW(extended, CLASS_NAME, widget->config.name.c_str(), style,
        widget->config.x, widget->config.y, width, height, nullptr, nullptr, hInstance, widget);
    ApplyWidgetTheme(widget->window, widget->config);
    widget->fullscreenWindows.clear();
    widget->fullscreenPreview = false;
    if (fullscreen) {
        for (size_t index = 1; index < selectedMonitors.size(); index++) {
            const RECT& rect = selectedMonitors[index]->rect;
            HWND additional = CreateWindowExW(extended, CLASS_NAME, widget->config.name.c_str(), WS_POPUP,
                rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, widget);
            if (additional != nullptr) {
                ApplyWidgetTheme(additional, widget->config);
                widget->fullscreenWindows.push_back(additional);
            }
        }
        if (hSettings != nullptr && IsWindow(hSettings)) {
            SetFullscreenPreview(widget);
        }
    }
    widget->analogChild = nullptr;
    widget->analogProc = nullptr;
    for (HWND& child : widget->additionalAnalogChildren) {
        child = nullptr;
    }
    widget->calendarChild = nullptr;
    widget->calendarProc = nullptr;
    widget->calendarFont = nullptr;
    widget->panelDateLink = nullptr;
    widget->panelDateFont = nullptr;
    widget->panelDateHot = false;
    widget->panelTimeZoneLink = nullptr;
    widget->panelTimeZoneFont = nullptr;
    widget->panelTimeZoneHot = false;
    widget->dragging = false;
    widget->rendered = false;
    widget->alarmActive = false;
    widget->flashPhase = false;
    widget->lastAlarmDate = -1;
    widget->lastAlarmMinute = -1;
    SYSTEMTIME alarmObservation = {};
    GetDisplayedTime(widget->config, &alarmObservation);
    widget->lastObservedAlarmDate = alarmObservation.wYear * 10000 + alarmObservation.wMonth * 100
        + alarmObservation.wDay;
    widget->lastObservedAlarmMinute = alarmObservation.wHour * 60 + alarmObservation.wMinute;
    widget->lastRenderKey = -1;
    widget->lastPanelDateKey = -1;
    widget->panelDateTooltip = nullptr;
    widget->analogBackground = CLR_INVALID;
    widget->alarmStoppedTick = 0;
    widget->identifyActive = false;
    widget->identifyPhase = false;
    widget->identifyRestoreHidden = false;
    widget->identifyRestoreNotTopmost = false;
    widget->identifyEndTick = 0;
    widget->copyTooltip = nullptr;
    widget->copyTooltipEndTick = 0;
    widget->lastAnalogClickTick = 0;
    widget->lastAnalogClickPoint = {};
    if (widget->config.type == WIDGET_ANALOG || widget->config.type == WIDGET_PANEL) {
        CreateAnalogChild(widget);
        CreateAdditionalAnalogChildren(widget);
    }
    if (widget->config.type == WIDGET_CALENDAR || widget->config.type == WIDGET_PANEL) {
        CreateCalendarChild(widget);
    }
    CreatePanelLinks(widget);
    if (parentedControl && widget->config.opacity < 100) {
        SetLayeredWindowAttributes(widget->window, 0, static_cast<BYTE>(widget->config.opacity * 255 / 100), LWA_ALPHA);
    } else if (widget->config.type == WIDGET_DIGITAL && !widget->config.transparentBackground) {
        SetLayeredWindowAttributes(widget->window, 0, static_cast<BYTE>(widget->config.opacity * 255 / 100), LWA_ALPHA);
    }
    if (widget->config.visible) {
        RenderWidget(widget);
        ShowWindow(widget->window, activate ? SW_SHOWNORMAL : SW_SHOWNOACTIVATE);
        RedrawWindow(widget->window, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
        if (!widget->fullscreenPreview) {
            for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
                ShowWindow(widget->fullscreenWindows[index], SW_SHOWNOACTIVATE);
                RedrawWindow(widget->fullscreenWindows[index], nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
            }
        }
    }
}

/// Stops widget audio and destroys its windows, tooltips, and owned fonts, then clears the associated runtime handles.
static void DestroyWidgetWindow(Widget* widget) {
    if (widget->alarmActive || widget->audioStopEvent != nullptr) {
        StopWidgetAlarm(widget);
    }
    if (widget->copyTooltip != nullptr && IsWindow(widget->copyTooltip)) {
        DestroyWindow(widget->copyTooltip);
    }
    widget->copyTooltip = nullptr;
    if (widget->window != nullptr && IsWindow(widget->window)) {
        DestroyWindow(widget->window);
    }
    if (widget->calendarFont != nullptr) {
        DeleteObject(widget->calendarFont);
        widget->calendarFont = nullptr;
    }
    if (widget->panelDateFont != nullptr) {
        DeleteObject(widget->panelDateFont);
        widget->panelDateFont = nullptr;
    }
    if (widget->panelTimeZoneFont != nullptr) {
        DeleteObject(widget->panelTimeZoneFont);
        widget->panelTimeZoneFont = nullptr;
    }
    for (size_t windowIndex = 0; windowIndex < widget->fullscreenWindows.size(); windowIndex++) {
        if (IsWindow(widget->fullscreenWindows[windowIndex])) {
            DestroyWindow(widget->fullscreenWindows[windowIndex]);
        }
    }
    widget->fullscreenWindows.clear();
    widget->window = nullptr;
    widget->analogChild = nullptr;
    widget->analogProc = nullptr;
    for (HWND& child : widget->additionalAnalogChildren) {
        child = nullptr;
    }
    widget->calendarChild = nullptr;
    widget->calendarProc = nullptr;
}

/// Destroys blackout windows, stops all alarms, and releases every widget's window resources.
static void DestroyWidgetWindows() {
    for (size_t index = 0; index < blackoutWindows.size(); index++) {
        if (IsWindow(blackoutWindows[index])) {
            DestroyWindow(blackoutWindows[index]);
        }
    }
    blackoutWindows.clear();
    StopAllAlarms();
    for (const std::unique_ptr<Widget>& widget : widgets) {
        DestroyWidgetWindow(widget.get());
    }
}

/// Paints a fullscreen blackout window and participates in shared pointer-idle handling.
static LRESULT CALLBACK BlackoutWindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    if (HandleFullscreenCursorMessage(window, message, wParam, lParam)) {
        return TRUE;
    }
    if (message == WM_ERASEBKGND) {
        RECT rect = {};
        GetClientRect(window, &rect);
        FillRect(reinterpret_cast<HDC>(wParam), &rect, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
        return 1;
    }
    if (message == WM_PAINT) {
        PAINTSTRUCT paint = {};
        HDC dc = BeginPaint(window, &paint);
        FillRect(dc, &paint.rcPaint, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
        EndPaint(window, &paint);
        return 0;
    }
    return DefWindowProcW(window, message, wParam, lParam);
}

/// Reconciles fullscreen clocks, settings previews, and blackout windows with current monitor and visibility settings.
static void RefreshFullscreenPresentation() {
    for (size_t index = 0; index < blackoutWindows.size(); index++) {
        if (IsWindow(blackoutWindows[index])) {
            DestroyWindow(blackoutWindows[index]);
        }
    }
    blackoutWindows.clear();
    RefreshDisplayMonitors();
    bool settingsOpen = hSettings != nullptr && IsWindow(hSettings);
    for (size_t widgetIndex = 0; widgetIndex < widgets.size(); widgetIndex++) {
        Widget* widget = widgets[widgetIndex].get();
        if (widget->config.type != WIDGET_FULLSCREEN || widget->window == nullptr) {
            continue;
        }
        if (settingsOpen) {
            SetFullscreenPreview(widget);
        } else {
            widget->fullscreenPreview = false;
        }
    }
    bool blackoutRequested = false;
    HWND escapeTarget = nullptr;
    std::vector<std::wstring> occupiedDevices;
    for (size_t widgetIndex = 0; widgetIndex < widgets.size(); widgetIndex++) {
        Widget* widget = widgets[widgetIndex].get();
        if (widget->config.type != WIDGET_FULLSCREEN
                || !widget->config.visible
                || widget->fullscreenPreview
                || widget->window == nullptr) {
            continue;
        }
        for (size_t windowIndex = 0; windowIndex < widget->fullscreenWindows.size(); windowIndex++) {
            ShowWindow(widget->fullscreenWindows[windowIndex], SW_HIDE);
        }
        blackoutRequested = blackoutRequested || widget->config.blackoutOtherMonitors;
        if (escapeTarget == nullptr) {
            escapeTarget = widget->window;
        }
        std::vector<const DisplayMonitor*> selected = SelectedDisplayMonitors(widget->config);
        for (size_t monitorIndex = 0; monitorIndex < selected.size(); monitorIndex++) {
            occupiedDevices.push_back(selected[monitorIndex]->device);
            HWND target = nullptr;
            if (monitorIndex == 0) {
                target = widget->window;
            } else if (monitorIndex - 1 < widget->fullscreenWindows.size()) {
                target = widget->fullscreenWindows[monitorIndex - 1];
            }
            if (target != nullptr) {
                const RECT& rect = selected[monitorIndex]->rect;
                SetWindowPos(target, HWND_TOPMOST, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
                    SWP_NOACTIVATE | SWP_SHOWWINDOW);
            }
        }
    }
    if (blackoutRequested) {
        for (size_t monitorIndex = 0; monitorIndex < displayMonitors.size(); monitorIndex++) {
            bool occupied = false;
            for (const std::wstring& device : occupiedDevices) {
                if (_wcsicmp(device.c_str(), displayMonitors[monitorIndex].device.c_str()) == 0) {
                    occupied = true;
                    break;
                }
            }
            if (occupied) {
                continue;
            }
            const RECT& rect = displayMonitors[monitorIndex].rect;
            HWND blackout = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_NOACTIVATE,
                BLACKOUT_CLASS_NAME, L"", WS_POPUP, rect.left, rect.top, rect.right - rect.left,
                rect.bottom - rect.top, nullptr, nullptr, hInstance, nullptr);
            if (blackout != nullptr) {
                ShowWindow(blackout, SW_SHOWNOACTIVATE);
                SetWindowPos(blackout, HWND_TOPMOST, rect.left, rect.top, rect.right - rect.left,
                    rect.bottom - rect.top, SWP_NOACTIVATE | SWP_SHOWWINDOW);
                blackoutWindows.push_back(blackout);
            }
        }
    }
    for (size_t widgetIndex = 0; widgetIndex < widgets.size(); widgetIndex++) {
        Widget* widget = widgets[widgetIndex].get();
        if (widget->config.type == WIDGET_FULLSCREEN && widget->config.visible && !widget->fullscreenPreview) {
            BringWidgetForward(widget);
        }
    }
    if (!settingsOpen && escapeTarget != nullptr) {
        SetForegroundWindowEx(escapeTarget);
        SetFocus(escapeTarget);
    }
}

/// Destroys and rebuilds every widget window, then refreshes the fullscreen presentation.
static void RecreateAllWidgetWindows() {
    DestroyWidgetWindows();
    for (size_t index = 0; index < widgets.size(); index++) {
        CreateWidgetWindow(widgets[index].get());
    }
    RefreshFullscreenPresentation();
}

/// Returns a borrowed pointer to the widget with the given persistent ID, or null when absent.
static Widget* FindWidgetById(int id) {
    for (size_t index = 0; index < widgets.size(); index++) {
        if (widgets[index]->config.id == id) {
            return widgets[index].get();
        }
    }
    return nullptr;
}

/// Records a nonempty set of widget IDs for the next restore-hidden command.
static void RememberHiddenWidgets(const std::vector<int>& widgetIds) {
    if (!widgetIds.empty()) {
        lastHiddenWidgetIds = widgetIds;
    }
}

/// Shows or hides one widget, updates fullscreen presentation and open settings as needed, and saves the visibility
/// change.
static void SetWidgetVisible(Widget* widget, bool visible) {
    if (widget == nullptr) {
        return;
    }
    if (widget->config.visible && !visible) {
        RememberHiddenWidgets(std::vector<int>{ widget->config.id });
    }
    widget->config.visible = visible;
    if (visible) {
        ShowWindow(widget->window, SW_SHOWNOACTIVATE);
        if (!widget->fullscreenPreview) {
            for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
                ShowWindow(widget->fullscreenWindows[index], SW_SHOWNOACTIVATE);
            }
        }
        RenderWidget(widget);
        BringWidgetForward(widget);
    } else {
        SaveWidgetPosition(widget);
        ShowWindow(widget->window, SW_HIDE);
        for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
            ShowWindow(widget->fullscreenWindows[index], SW_HIDE);
        }
    }
    if (widget->config.type == WIDGET_FULLSCREEN && (hSettings == nullptr || !IsWindow(hSettings))) {
        RefreshFullscreenPresentation();
    }
    SynchronizeOpenSettings(widget, ID_MENU_VISIBLE);
    SaveAllSettings();
}

/// Shows or hides all widgets, remembering the previously visible set before hiding and saving the resulting state.
static void SetAllVisible(bool visible) {
    if (!visible) {
        std::vector<int> hiddenWidgetIds;
        for (size_t index = 0; index < widgets.size(); index++) {
            if (widgets[index]->config.visible) {
                hiddenWidgetIds.push_back(widgets[index]->config.id);
            }
        }
        RememberHiddenWidgets(hiddenWidgetIds);
    }
    for (size_t index = 0; index < widgets.size(); index++) {
        widgets[index]->config.visible = visible;
        if (visible) {
            ShowWindow(widgets[index]->window, SW_SHOWNOACTIVATE);
            if (!widgets[index]->fullscreenPreview) {
                for (size_t windowIndex = 0; windowIndex < widgets[index]->fullscreenWindows.size(); windowIndex++) {
                    ShowWindow(widgets[index]->fullscreenWindows[windowIndex], SW_SHOWNOACTIVATE);
                }
            }
            RenderWidget(widgets[index].get());
            BringWidgetForward(widgets[index].get());
        } else {
            SaveWidgetPosition(widgets[index].get());
            ShowWindow(widgets[index]->window, SW_HIDE);
            for (size_t windowIndex = 0; windowIndex < widgets[index]->fullscreenWindows.size(); windowIndex++) {
                ShowWindow(widgets[index]->fullscreenWindows[windowIndex], SW_HIDE);
            }
        }
        SynchronizeOpenSettings(widgets[index].get(), ID_MENU_VISIBLE);
    }
    RefreshFullscreenPresentation();
    SaveAllSettings();
}

/// Plans changed positions for visible nonfullscreen widgets per monitor without moving any windows.
/// Uses the supplied widget as the grid anchor; returns no placements if arrangement is unavailable or fails.
static std::vector<PendingWidgetPlacement> PlanVisibleWidgetArrangement(Widget* anchor) {
    if (anchor != nullptr
            && (anchor->window == nullptr
                || !IsWindowVisible(anchor->window)
                || !anchor->config.visible
                || anchor->config.type == WIDGET_FULLSCREEN)) {
        return {};
    }
    std::vector<MonitorGroup> groups;
    HMONITOR anchorMonitor = anchor == nullptr ? nullptr : MonitorFromWindow(anchor->window, MONITOR_DEFAULTTONEAREST);
    for (size_t index = 0; index < widgets.size(); index++) {
        Widget* current = widgets[index].get();
        if (!current->config.visible
                || current->window == nullptr
                || !IsWindowVisible(current->window)
                || current->config.type == WIDGET_FULLSCREEN) {
            continue;
        }
        HMONITOR monitor = MonitorFromWindow(current->window, MONITOR_DEFAULTTONEAREST);
        if (anchorMonitor != nullptr && monitor != anchorMonitor) {
            continue;
        }
        size_t groupIndex = 0;
        while (groupIndex < groups.size() && groups[groupIndex].monitor != monitor) {
            groupIndex++;
        }
        if (groupIndex == groups.size()) {
            groups.push_back(MonitorGroup{
                monitor,
                std::vector<Widget*>{}
            });
        }
        groups[groupIndex].items.push_back(current);
    }
    if (groups.empty()) {
        return {};
    }
    std::vector<PendingWidgetPlacement> pending;
    bool failed = false;
    for (size_t groupIndex = 0; groupIndex < groups.size() && !failed; groupIndex++) {
        MONITORINFO monitorInformation = {};
        monitorInformation.cbSize = sizeof(monitorInformation);
        if (!GetMonitorInfoW(groups[groupIndex].monitor, &monitorInformation)) {
            failed = true;
            break;
        }
        std::vector<WidgetPlacement> placements;
        for (Widget* current : groups[groupIndex].items) {
            RECT rect = {};
            if (!GetWindowRect(current->window, &rect)) {
                failed = true;
                break;
            }
            placements.push_back(WidgetPlacement{
                current->config.id,
                rect
            });
        }
        if (failed || !ArrangeWidgetPlacements(&placements, monitorInformation.rcWork,
            anchor == nullptr ? -1 : anchor->config.id)) {
            failed = true;
            break;
        }
        for (size_t index = 0; index < placements.size(); index++) {
            Widget* current = groups[groupIndex].items[index];
            RECT original = {};
            if (!GetWindowRect(current->window, &original)) {
                failed = true;
                break;
            }
            if (!EqualRect(&original, &placements[index].rect)) {
                pending.push_back(PendingWidgetPlacement{
                    current,
                    placements[index].rect
                });
            }
        }
    }
    if (failed) {
        return {};
    }
    return pending;
}

/// Returns menu flags for the selected grid command, reevaluating and reenabling a previously used command when
/// movement becomes possible.
static UINT WidgetArrangementMenuFlags(Widget* anchor) {
    int id = anchor == nullptr ? -1 : anchor->config.id;
    std::vector<int>::iterator disabled = std::find(disabledArrangementCommands.begin(),
        disabledArrangementCommands.end(), id);
    if (disabled == disabledArrangementCommands.end()) {
        return MF_STRING;
    }
    if (PlanVisibleWidgetArrangement(anchor).empty()) {
        return MF_STRING | MF_GRAYED;
    }
    disabledArrangementCommands.erase(disabled);
    return MF_STRING;
}

/// Applies a planned grid arrangement, synchronizes stored positions, and records the invoked command's disabled state.
/// Reenables commands using the other grid origin so tray and widget arrangements remain independent.
static void ArrangeVisibleWidgets(Widget* anchor) {
    int id = anchor == nullptr ? -1 : anchor->config.id;
    if (anchor == nullptr) {
        disabledArrangementCommands.clear();
    } else {
        std::vector<int>::iterator trayCommand = std::find(disabledArrangementCommands.begin(),
            disabledArrangementCommands.end(), -1);
        if (trayCommand != disabledArrangementCommands.end()) {
            disabledArrangementCommands.erase(trayCommand);
        }
    }
    if (std::find(disabledArrangementCommands.begin(), disabledArrangementCommands.end(), id) ==
            disabledArrangementCommands.end()) {
        disabledArrangementCommands.push_back(id);
    }
    std::vector<PendingWidgetPlacement> pending = PlanVisibleWidgetArrangement(anchor);
    if (pending.empty()) {
        return;
    }
    for (size_t index = 0; index < pending.size(); index++) {
        Widget* current = pending[index].widget;
        current->config.x = pending[index].rect.left;
        current->config.y = pending[index].rect.top;
        SetWindowPos(current->window, nullptr, current->config.x, current->config.y, 0, 0,
            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
        for (WidgetConfig& draft : settingsDraft) {
            if (draft.id == current->config.id) {
                draft.x = current->config.x;
                draft.y = current->config.y;
            }
        }
        for (WidgetConfig& original : settingsAppearanceOriginals) {
            if (original.id == current->config.id) {
                original.x = current->config.x;
                original.y = current->config.y;
            }
        }
    }
    SaveAllSettings();
}

/// Restores the remembered hidden widgets, or available hidden widgets when none of those remain, and brings them
/// forward.
/// Returns false when no widgets can be restored.
static bool RestoreLastHiddenWidgets() {
    std::vector<Widget*> restoredWidgets;
    for (size_t index = 0; index < lastHiddenWidgetIds.size(); index++) {
        Widget* widget = FindWidgetById(lastHiddenWidgetIds[index]);
        if (widget == nullptr || widget->config.visible) {
            continue;
        }
        restoredWidgets.push_back(widget);
    }
    if (restoredWidgets.empty()) {
        for (size_t index = 0; index < widgets.size(); index++) {
            Widget* widget = widgets[index].get();
            if (widget->config.visible) {
                continue;
            }
            restoredWidgets.push_back(widget);
            break;
        }
    }
    if (restoredWidgets.empty()) {
        return false;
    }
    bool fullscreenVisibilityChanged = false;
    for (size_t index = 0; index < restoredWidgets.size(); index++) {
        Widget* widget = restoredWidgets[index];
        widget->config.visible = true;
        ShowWindow(widget->window, SW_SHOWNOACTIVATE);
        if (!widget->fullscreenPreview) {
            for (size_t windowIndex = 0; windowIndex < widget->fullscreenWindows.size(); windowIndex++) {
                ShowWindow(widget->fullscreenWindows[windowIndex], SW_SHOWNOACTIVATE);
            }
        }
        RenderWidget(widget);
        SynchronizeOpenSettings(widget, ID_MENU_VISIBLE);
        fullscreenVisibilityChanged = fullscreenVisibilityChanged || widget->config.type == WIDGET_FULLSCREEN;
    }
    if (fullscreenVisibilityChanged) {
        RefreshFullscreenPresentation();
    }
    SetForegroundWindowEx(restoredWidgets[0]->window);
    for (size_t index = 0; index < restoredWidgets.size(); index++) {
        BringWidgetForward(restoredWidgets[index]);
    }
    SaveAllSettings();
    return true;
}

/// Hides currently visible widgets or restores the last hidden group when all are hidden.
static void ToggleAllFromTray() {
    bool anyVisible = false;
    for (const std::unique_ptr<Widget>& widget : widgets) {
        if (widget->config.visible) {
            anyVisible = true;
            break;
        }
    }
    if (anyVisible) {
        SetAllVisible(false);
        return;
    }
    RestoreLastHiddenWidgets();
}

/// Creates the notification-area icon with localized tooltip text and negotiates version 4 notification behavior.
static void AddTrayIcon() {
    trayIcon = {};
    trayIcon.cbSize = sizeof(trayIcon);
    trayIcon.hWnd = hController;
    trayIcon.uID = 1;
    trayIcon.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_SHOWTIP;
    trayIcon.uCallbackMessage = WM_TRAYICON;
    trayIcon.hIcon = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_CLOCK));
    wcscpy_s(trayIcon.szTip, T(TXT_APP));
    Shell_NotifyIconW(NIM_ADD, &trayIcon);
    trayIcon.uVersion = NOTIFYICON_VERSION_4;
    trayUsesVersion4 = Shell_NotifyIconW(NIM_SETVERSION, &trayIcon) != FALSE;
}

/// Removes the notification-area icon and clears its cached state.
static void RemoveTrayIcon() {
    if (trayIcon.cbSize != 0) {
        Shell_NotifyIconW(NIM_DELETE, &trayIcon);
    }
    trayIcon = {};
    trayUsesVersion4 = false;
}

/// Updates an existing notification-area icon's localized tooltip.
static void UpdateTrayIcon() {
    if (trayIcon.cbSize == 0) {
        return;
    }
    trayIcon.uFlags = NIF_TIP | NIF_SHOWTIP;
    wcscpy_s(trayIcon.szTip, T(TXT_APP));
    Shell_NotifyIconW(NIM_MODIFY, &trayIcon);
}

/// Applies a widget context-menu command, synchronizing settings and recreating or redrawing the widget when required.
static void HandleWidgetMenuCommand(Widget* widget, int command) {
    if (widget == nullptr) {
        return;
    }
    bool recreate = false;
    WidgetConfig recreateConfiguration = {};
    if (command == ID_MENU_VISIBLE) {
        SetWidgetVisible(widget, !widget->config.visible);
    } else if (command == ID_MENU_TOPMOST) {
        widget->config.topMost = !widget->config.topMost;
        ApplyWidgetZOrder(widget, !widget->config.topMost);
        SynchronizeOpenSettings(widget, command);
        SaveAllSettings();
    } else if (command == ID_MENU_SHOW_TODAY && widget->config.type == WIDGET_CALENDAR) {
        recreateConfiguration = widget->config;
        recreateConfiguration.showToday = !recreateConfiguration.showToday;
        recreate = true;
    } else if (command == ID_MENU_TODAY) {
        SelectCalendarToday(widget);
    } else if (command == ID_MENU_SECONDS) {
        if (widget->config.type == WIDGET_ANALOG && !AnalogClockSupportsSeconds(widget->config.size)) {
            return;
        }
        bool previousShowSeconds = widget->config.showSeconds;
        widget->config.showSeconds = !widget->config.showSeconds;
        if ((widget->config.type == WIDGET_ANALOG || widget->config.type == WIDGET_PANEL)
                && !UpdateAnalogSeconds(widget)) {
            widget->config.showSeconds = previousShowSeconds;
            return;
        }
        if (widget->config.type == WIDGET_DIGITAL) {
            int width = 0;
            int height = 0;
            GetWidgetDimensions(widget->config, &width, &height);
            ResizeWidgetPreservingWorkAreaAttachment(widget, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
        }
    } else if (command == ID_MENU_STOP_ALARM) {
        StopWidgetAlarm(widget);
    } else if (command == ID_MENU_ALARM_ENABLED) {
        if (!WidgetSupportsSound(widget->config.type)) {
            return;
        }
        if (!widget->config.alarmEnabled && (widget->config.alarmDays & ALARM_DAYS_ALL) == 0) {
            settingsTab = 2;
            ShowSettingsWindow(widget->config.id);
            if (hTabs != nullptr) {
                TabCtrl_SetCurSel(hTabs, settingsTab);
                ShowSettingsTab(settingsTab);
            }
            return;
        }
        widget->config.alarmEnabled = !widget->config.alarmEnabled;
        if (!widget->config.alarmEnabled) {
            StopWidgetAlarm(widget);
        }
        SynchronizeOpenSettings(widget, command);
        SaveSettingsWithoutAppearancePreviews();
    } else if (command == ID_MENU_TIME_SIGNAL_ENABLED) {
        if (!WidgetSupportsSound(widget->config.type)) {
            return;
        }
        widget->config.timeSignal = widget->config.timeSignal == TIME_SIGNAL_NONE
            ? TIME_SIGNAL_EVERY_HOUR
            : TIME_SIGNAL_NONE;
        SynchronizeOpenSettings(widget, command);
        SaveSettingsWithoutAppearancePreviews();
    } else if (command == ID_MENU_MUTE) {
        if (!WidgetSupportsSound(widget->config.type)) {
            return;
        }
        SetWidgetSoundsMuted(widget, !widget->config.soundsMuted);
    } else if (command >= ID_MENU_SIZE_104 && command <= ID_MENU_SIZE_198) {
        int sizes[4] = {};
        int sizeCount = GetAnalogClockSizes(sizes);
        int sizeIndex = command - ID_MENU_SIZE_104;
        if (sizeIndex >= sizeCount) {
            return;
        }
        recreateConfiguration = widget->config;
        recreateConfiguration.size = sizes[sizeIndex];
        if (recreateConfiguration.type == WIDGET_DIGITAL) {
            const int fonts[] = {
                28,
                44,
                58,
                72
            };
            recreateConfiguration.fontSize = fonts[sizeIndex];
        }
        recreate = true;
    } else if (command >= ID_MENU_DATE_FORMAT_BASE && command < ID_MENU_DATE_FORMAT_BASE + DATE_FORMAT_COUNT) {
        widget->config.dateCopyFormat = command - ID_MENU_DATE_FORMAT_BASE;
        SynchronizeOpenSettings(widget, command);
        SaveAllSettings();
    } else if (command == ID_MENU_ARRANGE_WIDGETS) {
        ArrangeVisibleWidgets(widget);
    } else if (command == ID_MENU_SETTINGS) {
        ShowSettingsWindow(widget->config.id);
    } else if (command == ID_MENU_HELP || command == ID_MENU_ABOUT || command == ID_MENU_EXIT) {
        SendMessageW(hController, WM_COMMAND, MAKEWPARAM(command, 0), 0);
    }
    if (recreate) {
        if (widget->alarmActive || widget->audioStopEvent != nullptr) {
            StopWidgetAlarm(widget);
        }
        RecreateWidgetForConfiguration(widget, recreateConfiguration);
        SynchronizeOpenSettings(widget, command);
        SaveAllSettings();
    } else if (command == ID_MENU_SECONDS) {
        RenderWidget(widget);
        SynchronizeOpenSettings(widget, command);
        SaveAllSettings();
    }
}

/// Builds the widget's localized context menu with applicable states, displays it, and dispatches the selected command.
static void ShowWidgetContextMenu(Widget* widget, HWND owner) {
    HMENU menu = CreatePopupMenu();
    std::vector<wchar_t> menuMnemonics;
    AppendMenuCommand(menu, MF_STRING, ID_MENU_VISIBLE, widget->config.visible ?
        HIDE_WIDGET_LABELS[widget->config.language] : SHOW_WIDGET_LABELS[widget->config.language], &menuMnemonics);
    if (widget->config.type != WIDGET_FULLSCREEN) {
        AppendMenuCommand(menu, MF_STRING | (widget->config.topMost ? MF_CHECKED : 0), ID_MENU_TOPMOST,
            WT(widget, TXT_TOPMOST), &menuMnemonics);
    }
    if (widget->config.type == WIDGET_CALENDAR) {
        AppendMenuCommand(menu, MF_STRING, ID_MENU_TODAY, PANEL_TODAY_TOOLTIP[widget->config.language], &menuMnemonics);
        AppendMenuCommand(menu, MF_STRING | (widget->config.showToday ? MF_CHECKED : 0),
            ID_MENU_SHOW_TODAY, SHOW_TODAY_LABELS[widget->config.language], &menuMnemonics);
    }
    if (widget->config.type != WIDGET_CALENDAR) {
        bool secondsAvailable = widget->config.type != WIDGET_ANALOG || AnalogClockSupportsSeconds(widget->config.size);
        UINT secondsFlags = MF_STRING | (widget->config.showSeconds && secondsAvailable ? MF_CHECKED : 0);
        if (!secondsAvailable) {
            secondsFlags |= MF_GRAYED;
        }
        AppendMenuCommand(menu, secondsFlags, ID_MENU_SECONDS, WT(widget, TXT_SECONDS), &menuMnemonics);
    }
    if (WidgetSupportsSound(widget->config.type)) {
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        UINT alarmFlags = MF_STRING | (widget->config.alarmEnabled ? MF_CHECKED : 0);
        std::wstring alarmLabel = AlarmMenuLabel(widget->config);
        AppendMenuCommand(menu, alarmFlags, ID_MENU_ALARM_ENABLED, alarmLabel.c_str(), &menuMnemonics);
        AppendMenuCommand(menu, MF_STRING | (widget->config.timeSignal != TIME_SIGNAL_NONE ? MF_CHECKED : 0),
            ID_MENU_TIME_SIGNAL_ENABLED, TIME_SIGNAL_MENU_LABELS[widget->config.language], &menuMnemonics);
        AppendMenuCommand(menu, MF_STRING | (widget->config.soundsMuted ? MF_CHECKED : 0),
            ID_MENU_MUTE, MUTE_LABELS[widget->config.language], &menuMnemonics);
    }
    if (widget->config.type == WIDGET_ANALOG || widget->config.type == WIDGET_PANEL) {
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        int sizes[4] = {};
        int sizeCount = GetAnalogClockSizes(sizes);
        for (int index = 0; index < sizeCount; index++) {
            std::wstring label = WT(widget, TXT_SIZE);
            label += L" ";
            label += std::to_wstring(sizes[index]);
            AppendMenuCommand(menu, MF_STRING | (widget->config.size == sizes[index] ? MF_CHECKED : 0),
                ID_MENU_SIZE_104 + index, label.c_str(), &menuMnemonics);
        }
    }
    if (widget->config.type == WIDGET_CALENDAR || widget->config.type == WIDGET_PANEL) {
        HMENU dateMenu = CreatePopupMenu();
        std::vector<wchar_t> dateMenuMnemonics;
        SYSTEMTIME selectedDate = {};
        if (widget->calendarChild == nullptr || !MonthCal_GetCurSel(widget->calendarChild, &selectedDate)) {
            GetDisplayedTime(widget->config, &selectedDate);
        }
        for (int index = 0; index < DATE_FORMAT_COUNT; index++) {
            if (DateFormatStartsGroup(index)) {
                AppendMenuW(dateMenu, MF_SEPARATOR, 0, nullptr);
            }
            std::wstring label = DateFormatCaption(widget->config, selectedDate, index);
            AppendMenuCommand(dateMenu, MF_STRING | (widget->config.dateCopyFormat == index ? MF_CHECKED : 0),
                ID_MENU_DATE_FORMAT_BASE + index, label.c_str(), &dateMenuMnemonics);
        }
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        AppendMenuCommand(menu, MF_POPUP, reinterpret_cast<UINT_PTR>(dateMenu),
            DATE_COPY_LABELS[widget->config.language], &menuMnemonics);
    }
    if (widget->alarmActive) {
        AppendMenuCommand(menu, MF_STRING, ID_MENU_STOP_ALARM, WT(widget, TXT_STOP_ALARM), &menuMnemonics);
    }
    if (widget->config.type != WIDGET_FULLSCREEN) {
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        UINT arrangeFlags = WidgetArrangementMenuFlags(widget);
        AppendMenuCommand(menu, arrangeFlags, ID_MENU_ARRANGE_WIDGETS, ARRANGE_WIDGET_LABELS[widget->config.language],
            &menuMnemonics);
    }
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendApplicationMenuCommands(menu, widget->config.language, &menuMnemonics);
    POINT point = {};
    GetCursorPos(&point);
    SetForegroundWindow(owner);
    int command = TrackPopupMenu(menu, TPM_RETURNCMD | TPM_RIGHTBUTTON, point.x, point.y, 0, owner, nullptr);
    DestroyMenu(menu);
    if (command != 0) {
        HandleWidgetMenuCommand(widget, command);
    }
}

/// Creates a size-only context menu for one additional panel clock.
/// The caller owns the returned menu and must destroy it.
static HMENU CreateAdditionalClockMenu(const Widget* widget, int index) {
    HMENU menu = CreatePopupMenu();
    std::vector<wchar_t> mnemonics;
    const AdditionalClockConfig& clock = widget->config.additionalClocks[index];
    int sizes[4] = {};
    int count = GetAnalogClockSizes(sizes);
    for (int item = 0; item < count; item++) {
        std::wstring label = std::wstring(WT(widget, TXT_SIZE)) + L" " + std::to_wstring(sizes[item]);
        AppendMenuCommand(menu, MF_STRING | (NormalizeAnalogClockSize(clock.size) == sizes[item] ? MF_CHECKED : 0),
            ID_MENU_SIZE_104 + item, label.c_str(), &mnemonics);
    }
    return menu;
}

/// Applies a valid size command to one additional panel clock, recreates the panel as needed, and synchronizes and
/// saves settings.
static void HandleAdditionalClockMenuCommand(Widget* widget, int index, int command) {
    if (widget == nullptr
            || index < 0
            || index >= ADDITIONAL_CLOCK_COUNT
            || widget->config.type != WIDGET_PANEL
            || command < ID_MENU_SIZE_104
            || command > ID_MENU_SIZE_198) {
        return;
    }
    int sizes[4] = {};
    int count = GetAnalogClockSizes(sizes);
    int selected = command - ID_MENU_SIZE_104;
    if (selected >= count) {
        return;
    }
    WidgetConfig configuration = widget->config;
    configuration.additionalClocks[index].size = sizes[selected];
    RecreateWidgetForConfiguration(widget, configuration);
    SynchronizeOpenSettings(widget, ID_ADDITIONAL_SIZE_BASE + index);
    SaveAllSettings();
}

/// Displays a size-only menu at the supplied screen point and dispatches the selected additional-clock command.
static void ShowAdditionalClockContextMenu(Widget* widget, int index, POINT point) {
    HMENU menu = CreateAdditionalClockMenu(widget, index);
    SetForegroundWindow(widget->window);
    int command = TrackPopupMenu(menu, TPM_RETURNCMD | TPM_RIGHTBUTTON, point.x, point.y, 0, widget->window, nullptr);
    DestroyMenu(menu);
    if (command != 0) {
        HandleAdditionalClockMenuCommand(widget, index, command);
    }
}

/// Builds and displays the tray menu for widget visibility, shared actions, and application commands, then dispatches
/// the selection.
static void ShowTrayContextMenu() {
    HMENU menu = CreatePopupMenu();
    std::vector<wchar_t> menuMnemonics;
    for (size_t index = 0; index < widgets.size(); index++) {
        std::wstring label = std::to_wstring(index + 1) + L". " + widgets[index]->config.name;
        AppendMenuW(menu, MF_STRING | (widgets[index]->config.visible ? MF_CHECKED : 0),
            ID_MENU_WIDGET_BASE + static_cast<UINT>(index), label.c_str());
    }
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendMenuCommand(menu, MF_STRING, ID_MENU_SHOW_ALL, T(TXT_SHOW_ALL), &menuMnemonics);
    AppendMenuCommand(menu, MF_STRING, ID_MENU_HIDE_ALL, T(TXT_HIDE_ALL), &menuMnemonics);
    bool activeAlarm = false;
    for (size_t index = 0; index < widgets.size(); index++) {
        activeAlarm = activeAlarm || widgets[index]->alarmActive;
    }
    if (activeAlarm) {
        AppendMenuCommand(menu, MF_STRING, ID_MENU_STOP_ALARM, T(TXT_STOP_ALARM), &menuMnemonics);
    }
    bool hasSoundWidget = false;
    bool allMuted = true;
    for (const std::unique_ptr<Widget>& widget : widgets) {
        if (!WidgetSupportsSound(widget->config.type)) {
            continue;
        }
        hasSoundWidget = true;
        if (!widget->config.soundsMuted) {
            allMuted = false;
            break;
        }
    }
    if (!hasSoundWidget) {
        allMuted = false;
    }
    UINT muteFlags = MF_STRING;
    if (allMuted) {
        muteFlags |= MF_CHECKED;
    }
    if (!hasSoundWidget) {
        muteFlags |= MF_GRAYED;
    }
    AppendMenuCommand(menu, muteFlags, ID_MENU_MUTE, MUTE_ALL_LABELS[appLanguage], &menuMnemonics);
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    UINT arrangeFlags = WidgetArrangementMenuFlags(nullptr);
    AppendMenuCommand(menu, arrangeFlags, ID_MENU_ARRANGE_WIDGETS, ARRANGE_WIDGET_LABELS[appLanguage], &menuMnemonics);
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendApplicationMenuCommands(menu, appLanguage, &menuMnemonics);
    POINT point = {};
    GetCursorPos(&point);
    SetForegroundWindow(hController);
    int command = TrackPopupMenu(menu, TPM_RETURNCMD | TPM_RIGHTBUTTON, point.x, point.y, 0, hController, nullptr);
    DestroyMenu(menu);
    if (command >= ID_MENU_WIDGET_BASE && command < ID_MENU_WIDGET_BASE + static_cast<int>(widgets.size())) {
        SetWidgetVisible(widgets[command - ID_MENU_WIDGET_BASE].get(),
            !widgets[command - ID_MENU_WIDGET_BASE]->config.visible);
    } else {
        SendMessageW(hController, WM_COMMAND, command, 0);
    }
}

/// Prefixes the localized common caption with a mnemonic marker.
static std::wstring Mnemonic(TextId id) {
    return std::wstring(L"&") + T(id);
}

/// Classifies a settings child as a foreground control, checkbox, or background label for clipping and hit testing.
static SettingsControlLayer GetSettingsControlLayer(HWND control) {
    wchar_t className[32] = {};
    GetClassNameW(control, className, ARRAYSIZE(className));
    if (_wcsicmp(className, L"STATIC") == 0) {
        return SETTINGS_CONTROL_LABEL;
    }
    if (_wcsicmp(className, L"BUTTON") == 0) {
        LONG_PTR style = GetWindowLongPtrW(control, GWL_STYLE);
        UINT type = static_cast<UINT>(style & BS_TYPEMASK);
        if (type == BS_CHECKBOX || type == BS_AUTOCHECKBOX || type == BS_3STATE || type == BS_AUTO3STATE) {
            return SETTINGS_CONTROL_CHECKBOX;
        }
    }
    return SETTINGS_CONTROL_FOREGROUND;
}

/// Orders settings children by control layer, placing right-hand text controls above overlapping left-hand controls.
static bool SettingsControlIsAbove(const PositionedControl& left, const PositionedControl& right) {
    SettingsControlLayer leftLayer = GetSettingsControlLayer(left.window);
    SettingsControlLayer rightLayer = GetSettingsControlLayer(right.window);
    if (leftLayer != rightLayer) {
        return leftLayer < rightLayer;
    }
    if (leftLayer == SETTINGS_CONTROL_FOREGROUND) {
        return false;
    }
    return left.rect.left == right.rect.left ? left.rect.top < right.rect.top : left.rect.left > right.rect.left;
}

/// Creates a transparent, sibling-clipped label extending to the common settings content edge and optionally records it
/// in a group.
static HWND AddUnderlayStatic(HWND parent, const wchar_t* text, DWORD style, int x, int y, int height,
        std::vector<HWND>* group = nullptr) {
    int right = parent == hSettings ? SETTINGS_WIDGET_LIST_RIGHT : SETTINGS_PAGE_CONTENT_RIGHT;
    HWND control = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", text,
        WS_CHILD | WS_CLIPSIBLINGS | style | SS_LEFTNOWORDWRAP,
        x, y, right - x, height, parent, nullptr, hInstance, nullptr);
    if (group != nullptr) {
        group->push_back(control);
    }
    return control;
}

/// Creates a visible localized settings label with a mnemonic marker and the common right edge.
static HWND AddStatic(HWND parent, TextId id, int x, int y, int height, std::vector<HWND>* group = nullptr) {
    std::wstring text = Mnemonic(id);
    return AddUnderlayStatic(parent, text.c_str(), WS_VISIBLE, x, y, height, group);
}

/// Creates a visible settings child and installs edit or widget-list keyboard subclasses where applicable.
/// Optionally appends the handle to its page's control group.
static HWND AddControl(DWORD extended, const wchar_t* className, const wchar_t* text, DWORD style,
        int x, int y, int width, int height, HWND parent, int id, std::vector<HWND>* group = nullptr) {
    HWND control = CreateWindowExW(extended, className, text, WS_CHILD | WS_VISIBLE | style,
        x, y, width, height, parent, reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)), hInstance, nullptr);
    if (control != nullptr && _wcsicmp(className, L"EDIT") == 0) {
        SetWindowSubclass(control, EditSubclassProc, static_cast<UINT_PTR>(id), 0);
    } else if (control != nullptr
            && (id == ID_LIST_WIDGETS || id == ID_MONITOR_LIST || id == ID_REMOVE || id == ID_DUPLICATE)) {
        SetWindowSubclass(control, WidgetListSubclassProc, static_cast<UINT_PTR>(id), 0);
    }
    if (group != nullptr) {
        group->push_back(control);
    }
    return control;
}

/// Creates a tooltip attached to a control, destroying it if registration fails.
/// The supplied text must remain valid while the tooltip uses it.
static HWND CreateControlTooltip(HWND parent, HWND control, const wchar_t* text) {
    if (parent == nullptr || control == nullptr || text == nullptr) {
        return nullptr;
    }
    HWND tooltip = CreateWindowExW(WS_EX_TOPMOST | WS_EX_NOACTIVATE, TOOLTIPS_CLASSW,
        nullptr, WS_POPUP | TTS_ALWAYSTIP | TTS_NOPREFIX, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, parent, nullptr, hInstance, nullptr);
    if (tooltip == nullptr) {
        return nullptr;
    }
    TOOLINFOW information = {};
    information.cbSize = sizeof(information);
    information.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
    information.hwnd = parent;
    information.uId = reinterpret_cast<UINT_PTR>(control);
    information.lpszText = const_cast<wchar_t*>(text);
    if (!SendMessageW(tooltip, TTM_ADDTOOLW, 0, reinterpret_cast<LPARAM>(&information))) {
        DestroyWindow(tooltip);
        return nullptr;
    }
    return tooltip;
}

/// Converts a logical settings x coordinate or width using the common horizontal scale factor.
static int ScaleSettingsHorizontal(int value) {
    return MulDiv(value, SETTINGS_HORIZONTAL_SCALE_NUMERATOR, SETTINGS_HORIZONTAL_SCALE_DENOMINATOR);
}

/// Calculates a nonresizable settings window that fits the work area and adds scrollbars when its content cannot fit.
static void GetSettingsWindowLayout(DWORD extendedStyle, DWORD* style, int* width, int* height) {
    const DWORD baseStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
    int desiredWidth = ScaleSettingsHorizontal(SETTINGS_WINDOW_WIDTH);
    int desiredHeight = SETTINGS_WINDOW_HEIGHT;
    RECT frame = {};
    AdjustWindowRectEx(&frame, baseStyle, FALSE, extendedStyle);
    settingsContentWidth = desiredWidth - (frame.right - frame.left);
    settingsContentHeight = desiredHeight - (frame.bottom - frame.top);
    RECT desired = {
        settingsX,
        settingsY,
        settingsX + desiredWidth,
        settingsY + desiredHeight
    };
    HMONITOR monitor = settingsX == CW_USEDEFAULT || settingsY == CW_USEDEFAULT
        ? MonitorFromPoint(POINT{}, MONITOR_DEFAULTTOPRIMARY)
        : MonitorFromRect(&desired, MONITOR_DEFAULTTONEAREST);
    MONITORINFO information = {};
    information.cbSize = sizeof(information);
    RECT workArea = {
        0,
        0,
        GetSystemMetrics(SM_CXSCREEN),
        GetSystemMetrics(SM_CYSCREEN)
    };
    if (monitor != nullptr && GetMonitorInfoW(monitor, &information)) {
        workArea = information.rcWork;
    }
    int workWidth = std::max(1, static_cast<int>(workArea.right - workArea.left));
    int workHeight = std::max(1, static_cast<int>(workArea.bottom - workArea.top));
    int horizontalScrollHeight = GetSystemMetrics(SM_CYHSCROLL);
    int verticalScrollWidth = GetSystemMetrics(SM_CXVSCROLL);
    bool horizontalScroll = desiredWidth > workWidth;
    bool verticalScroll = desiredHeight > workHeight;
    for (int pass = 0; pass < 2; pass++) {
        *width = std::min(workWidth, desiredWidth + (verticalScroll ? verticalScrollWidth : 0));
        *height = std::min(workHeight, desiredHeight + (horizontalScroll ? horizontalScrollHeight : 0));
        if (*width - (verticalScroll ? verticalScrollWidth : 0) < desiredWidth) {
            horizontalScroll = true;
        }
        if (*height - (horizontalScroll ? horizontalScrollHeight : 0) < desiredHeight) {
            verticalScroll = true;
        }
    }
    *width = std::min(workWidth, desiredWidth + (verticalScroll ? verticalScrollWidth : 0));
    *height = std::min(workHeight, desiredHeight + (horizontalScroll ? horizontalScrollHeight : 0));
    *style = baseStyle;
    if (horizontalScroll) {
        *style |= WS_HSCROLL;
    }
    if (verticalScroll) {
        *style |= WS_VSCROLL;
    }
}

/// Initializes enabled settings scrollbars from the full content dimensions and current client size.
static void InitializeSettingsScrollBars() {
    if (hSettings == nullptr || !IsWindow(hSettings)) {
        return;
    }
    RECT client = {};
    GetClientRect(hSettings, &client);
    LONG_PTR style = GetWindowLongPtrW(hSettings, GWL_STYLE);
    if ((style & WS_HSCROLL) != 0) {
        SCROLLINFO horizontal = {};
        horizontal.cbSize = sizeof(horizontal);
        horizontal.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
        horizontal.nMin = 0;
        horizontal.nMax = std::max(0, settingsContentWidth - 1);
        horizontal.nPage = static_cast<UINT>(std::max(0L, client.right - client.left));
        horizontal.nPos = 0;
        SetScrollInfo(hSettings, SB_HORZ, &horizontal, TRUE);
    }
    if ((style & WS_VSCROLL) != 0) {
        SCROLLINFO vertical = {};
        vertical.cbSize = sizeof(vertical);
        vertical.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
        vertical.nMin = 0;
        vertical.nMax = std::max(0, settingsContentHeight - 1);
        vertical.nPage = static_cast<UINT>(std::max(0L, client.bottom - client.top));
        vertical.nPos = 0;
        SetScrollInfo(hSettings, SB_VERT, &vertical, TRUE);
    }
}

/// Applies a scrollbar request within its valid range and scrolls the settings child windows by the resulting delta.
static bool ScrollSettingsWindow(int bar, int request) {
    if (hSettings == nullptr || !IsWindow(hSettings)) {
        return false;
    }
    SCROLLINFO information = {};
    information.cbSize = sizeof(information);
    information.fMask = SIF_ALL;
    if (!GetScrollInfo(hSettings, bar, &information)) {
        return false;
    }
    int oldPosition = information.nPos;
    int position = oldPosition;
    int lineSize = 24;
    switch (request) {
        case SB_LINELEFT:
            position -= lineSize;
            break;
        case SB_LINERIGHT:
            position += lineSize;
            break;
        case SB_PAGELEFT:
            position -= static_cast<int>(information.nPage);
            break;
        case SB_PAGERIGHT:
            position += static_cast<int>(information.nPage);
            break;
        case SB_THUMBPOSITION:
        case SB_THUMBTRACK:
            position = information.nTrackPos;
            break;
        case SB_LEFT:
            position = information.nMin;
            break;
        case SB_RIGHT:
            position = information.nMax;
            break;
        default:
            return true;
    }
    int maximum = information.nMax - std::max(0, static_cast<int>(information.nPage) - 1);
    position = std::clamp(position, information.nMin, std::max(information.nMin, maximum));
    information.fMask = SIF_POS;
    information.nPos = position;
    SetScrollInfo(hSettings, bar, &information, TRUE);
    information.fMask = SIF_POS;
    GetScrollInfo(hSettings, bar, &information);
    position = information.nPos;
    if (position == oldPosition) {
        return true;
    }
    int deltaX = bar == SB_HORZ ? oldPosition - position : 0;
    int deltaY = bar == SB_VERT ? oldPosition - position : 0;
    ScrollWindowEx(hSettings, deltaX, deltaY, nullptr, nullptr, nullptr, nullptr,
        SW_SCROLLCHILDREN | SW_INVALIDATE | SW_ERASE);
    UpdateWindow(hSettings);
    return true;
}

/// Translates wheel input into three line-scroll steps per notch, using horizontal scrolling with Shift when available.
static bool ScrollSettingsWheel(WPARAM wParam) {
    LONG_PTR style = GetWindowLongPtrW(hSettings, GWL_STYLE);
    int bar = (GET_KEYSTATE_WPARAM(wParam) & MK_SHIFT) != 0 && (style & WS_HSCROLL) != 0 ? SB_HORZ : SB_VERT;
    if (bar == SB_HORZ && (style & WS_HSCROLL) == 0 || bar == SB_VERT && (style & WS_VSCROLL) == 0) {
        return false;
    }
    int steps = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
    int request = steps > 0 ? SB_LINELEFT : SB_LINERIGHT;
    for (int index = 0; index < abs(steps) * 3; index++) {
        ScrollSettingsWindow(bar, request);
    }
    return true;
}

/// Applies the common horizontal scale to each direct child's position and width while preserving vertical dimensions.
static void ScaleSettingsChildren(HWND parent) {
    if (parent == nullptr) {
        return;
    }
    HWND child = GetWindow(parent, GW_CHILD);
    while (child != nullptr) {
        HWND next = GetWindow(child, GW_HWNDNEXT);
        RECT rect = {};
        if (GetWindowRect(child, &rect)) {
            MapWindowPoints(HWND_DESKTOP, parent, reinterpret_cast<POINT*>(&rect), 2);
            SetWindowPos(child, nullptr, ScaleSettingsHorizontal(rect.left), rect.top,
                ScaleSettingsHorizontal(rect.right - rect.left), rect.bottom - rect.top, SWP_NOZORDER | SWP_NOACTIVATE);
        }
        child = next;
    }
}

/// Moves or resizes a control only when necessary, retaining combo height and extending settings text controls to the
/// common right edge.
static void SetControlPosition(HWND control, int x, int y, int width, int height) {
    if (control == nullptr) {
        return;
    }
    HWND parent = GetParent(control);
    if ((parent == hSettings || IsSettingsPageWindow(parent))
            && GetSettingsControlLayer(control) != SETTINGS_CONTROL_FOREGROUND) {
        int right = parent == hSettings ? SETTINGS_WIDGET_LIST_RIGHT : SETTINGS_PAGE_CONTENT_RIGHT;
        width = std::max(1, ScaleSettingsHorizontal(right) - x);
    }
    wchar_t className[32] = {};
    GetClassNameW(control, className, ARRAYSIZE(className));
    bool combo = _wcsicmp(className, WC_COMBOBOXW) == 0;
    RECT current = {};
    UINT flags = SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS;
    if (GetWindowRect(control, &current)) {
        MapWindowPoints(HWND_DESKTOP, GetParent(control), reinterpret_cast<POINT*>(&current), 2);
        LONG_PTR currentHeight = current.bottom - current.top;
        if (combo) {
            currentHeight = reinterpret_cast<LONG_PTR>(GetPropW(control, SETTINGS_COMBO_HEIGHT_PROPERTY));
        }
        if (current.left == x && current.top == y) {
            flags |= SWP_NOMOVE;
        }
        if (current.right - current.left == width && currentHeight == height) {
            flags |= SWP_NOSIZE;
        }
    }
    if ((flags & (SWP_NOMOVE | SWP_NOSIZE)) == (SWP_NOMOVE | SWP_NOSIZE)) {
        return;
    }
    if (SetWindowPos(control, nullptr, x, y, width, height, flags) && combo) {
        SetPropW(control, SETTINGS_COMBO_HEIGHT_PROPERTY, reinterpret_cast<HANDLE>(static_cast<INT_PTR>(height)));
    }
}

/// Applies logical settings coordinates through the horizontal scale before updating a control's rectangle.
static void SetSettingsControlPosition(HWND control, int x, int y, int width, int height) {
    SetControlPosition(control, ScaleSettingsHorizontal(x), y, ScaleSettingsHorizontal(width), height);
}

/// Tests a screen point against visible siblings above a control, including disabled siblings that still block input.
static bool IsSettingsControlPointCovered(HWND control, POINT point) {
    for (HWND sibling = GetWindow(control, GW_HWNDPREV); sibling != nullptr; sibling = GetWindow(sibling, GW_HWNDPREV)) {
        RECT rect = {};
        if (IsWindowVisible(sibling) && GetWindowRect(sibling, &rect) && PtInRect(&rect, point)) {
            return true;
        }
    }
    return false;
}

/// Prevents mouse clicks and captured releases from activating controls covered by higher siblings.
/// Allows programmatic BM_CLICK activation and removes the subclass when the control is destroyed.
static LRESULT CALLBACK SettingsControlSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    switch (message) {
        case BM_CLICK:
        {
            SetWindowSubclass(window, SettingsControlSubclassProc, subclassId, 1);
            LRESULT result = DefSubclassProc(window, message, wParam, lParam);
            DWORD_PTR currentData = 0;
            if (GetWindowSubclass(window, SettingsControlSubclassProc, subclassId, &currentData)) {
                SetWindowSubclass(window, SettingsControlSubclassProc, subclassId, referenceData);
            }
            return result;
        }
        case WM_NCHITTEST:
        {
            POINT point = {
                GET_X_LPARAM(lParam),
                GET_Y_LPARAM(lParam)
            };
            if (IsSettingsControlPointCovered(window, point)) {
                return HTTRANSPARENT;
            }
            break;
        }
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
        {
            if (referenceData != 0) {
                break;
            }
            POINT point = {
                GET_X_LPARAM(lParam),
                GET_Y_LPARAM(lParam)
            };
            ClientToScreen(window, &point);
            if (IsSettingsControlPointCovered(window, point)) {
                return 0;
            }
            break;
        }
        case WM_MOUSEMOVE:
        case WM_LBUTTONUP:
        {
            if (referenceData != 0) {
                break;
            }
            if (GetSettingsControlLayer(window) == SETTINGS_CONTROL_CHECKBOX) {
                POINT point = {
                    GET_X_LPARAM(lParam),
                    GET_Y_LPARAM(lParam)
                };
                ClientToScreen(window, &point);
                if (IsSettingsControlPointCovered(window, point)) {
                    if (message == WM_LBUTTONUP) {
                        SendMessageW(window, BM_SETSTATE, FALSE, 0);
                    }
                    return DefSubclassProc(window, message, wParam, MAKELPARAM(-1, -1));
                }
            }
            break;
        }
        case WM_NCDESTROY:
            RemoveWindowSubclass(window, SettingsControlSubclassProc, subclassId);
            break;
    }
    return DefSubclassProc(window, message, wParam, lParam);
}

/// Extends labels and checkboxes to the common right edge, enables sibling clipping, and enforces their Z order.
/// Installs input guards so disabled foreground controls cannot pass clicks to covered controls.
static void UpdateSettingsTextControlLayout(HWND parent) {
    if (parent == nullptr) {
        return;
    }
    std::vector<PositionedControl> controls;
    for (HWND control = GetWindow(parent, GW_CHILD); control != nullptr; control = GetWindow(control, GW_HWNDNEXT)) {
        DWORD_PTR referenceData = 0;
        if (!GetWindowSubclass(control, SettingsControlSubclassProc, SETTINGS_CONTROL_SUBCLASS_ID, &referenceData)) {
            SetWindowSubclass(control, SettingsControlSubclassProc, SETTINGS_CONTROL_SUBCLASS_ID, 0);
        }
        RECT rect = {};
        if (!GetWindowRect(control, &rect)) {
            continue;
        }
        MapWindowPoints(HWND_DESKTOP, parent, reinterpret_cast<POINT*>(&rect), 2);
        if (GetSettingsControlLayer(control) != SETTINGS_CONTROL_FOREGROUND) {
            LONG_PTR style = GetWindowLongPtrW(control, GWL_STYLE);
            if ((style & WS_CLIPSIBLINGS) == 0) {
                SetWindowLongPtrW(control, GWL_STYLE, style | WS_CLIPSIBLINGS);
            }
            SetControlPosition(control, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
        }
        controls.push_back(PositionedControl{ control, rect });
    }
    std::stable_sort(controls.begin(), controls.end(), SettingsControlIsAbove);
    HWND previous = nullptr;
    for (const PositionedControl& control : controls) {
        if (GetWindow(control.window, GW_HWNDPREV) != previous) {
            SetWindowPos(control.window, previous, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOCOPYBITS);
        }
        previous = control.window;
    }
}

/// Cancels triple-click tracking and its timer for the last edit control.
static void ResetEditClicks() {
    if (lastClickedEdit != nullptr) {
        KillTimer(lastClickedEdit, TIMER_EDIT_CLICKS);
    }
    lastClickedEdit = nullptr;
    lastEditClickPoint = {};
    editClickCount = 0;
}

/// Extends the edit selection to the boundaries of its current text line.
static void SelectEditLine(HWND window) {
    DWORD selectionStart = 0;
    DWORD selectionEnd = 0;
    SendMessageW(window, EM_GETSEL, reinterpret_cast<WPARAM>(&selectionStart), reinterpret_cast<LPARAM>(&selectionEnd));
    std::wstring text = GetControlText(window);
    size_t start = std::min(static_cast<size_t>(selectionStart), text.size());
    size_t end = text.find_first_of(L"\r\n", start);
    if (end == std::wstring::npos) {
        end = text.size();
    }
    end = std::max(end, std::min(static_cast<size_t>(selectionEnd), text.size()));
    while (start > 0 && text[start - 1] != L'\r' && text[start - 1] != L'\n') {
        start--;
    }
    SendMessageW(window, EM_SETSEL, static_cast<WPARAM>(start), static_cast<LPARAM>(end));
}

/// Adds Ctrl+A and triple-click line selection while preserving normal edit and dialog behavior.
/// Clears click tracking on timeout, focus changes, other mouse buttons, and destruction.
static LRESULT CALLBACK EditSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    UNREFERENCED_PARAMETER(referenceData);
    if (message == WM_TIMER && wParam == TIMER_EDIT_CLICKS) {
        KillTimer(window, TIMER_EDIT_CLICKS);
        if (lastClickedEdit == window) {
            ResetEditClicks();
        }
        return 0;
    }
    bool isMouseButtonMessage = message == WM_RBUTTONDOWN
        || message == WM_RBUTTONDBLCLK
        || message == WM_MBUTTONDOWN
        || message == WM_MBUTTONDBLCLK
        || message == WM_XBUTTONDOWN
        || message == WM_XBUTTONDBLCLK;
    bool editLostFocus = message == WM_KILLFOCUS && lastClickedEdit == window;
    if (isMouseButtonMessage || editLostFocus) {
        ResetEditClicks();
    }
    if (message == WM_LBUTTONDOWN || message == WM_LBUTTONDBLCLK) {
        if (lastClickedEdit != window) {
            ResetEditClicks();
        }
        lastClickedEdit = window;
        KillTimer(window, TIMER_EDIT_CLICKS);
        LRESULT result = DefSubclassProc(window, message, wParam, lParam);
        DWORD selectionStart = 0;
        DWORD selectionEnd = 0;
        SendMessageW(window, EM_GETSEL, reinterpret_cast<WPARAM>(&selectionStart),
            reinterpret_cast<LPARAM>(&selectionEnd));
        POINT clickPoint = {
            GET_X_LPARAM(lParam),
            GET_Y_LPARAM(lParam)
        };
        if (selectionEnd > selectionStart) {
            editClickCount = 2;
        } else if (editClickCount == 0
                || abs(clickPoint.x - lastEditClickPoint.x) < 2 && abs(clickPoint.y - lastEditClickPoint.y) < 2) {
            editClickCount++;
        } else {
            editClickCount = 0;
        }
        lastEditClickPoint = clickPoint;
        if (editClickCount == 3) {
            ResetEditClicks();
            DefSubclassProc(window, WM_LBUTTONUP, wParam & ~static_cast<WPARAM>(MK_LBUTTON), lParam);
            if ((GetWindowLongPtrW(window, GWL_STYLE) & ES_MULTILINE) != 0) {
                SelectEditLine(window);
            } else {
                SendMessageW(window, EM_SETSEL, 0, -1);
            }
            SetFocus(window);
            return 0;
        }
        SetTimer(window, TIMER_EDIT_CLICKS, GetDoubleClickTime(), nullptr);
        return result;
    }
    bool selectAll = message == WM_KEYDOWN && wParam == L'A' && (GetKeyState(VK_CONTROL) & 0x8000) != 0;
    selectAll = selectAll || message == WM_CHAR && wParam == 1;
    if (selectAll) {
        SendMessageW(window, EM_SETSEL, 0, -1);
        return 0;
    }
    if (message == WM_NCDESTROY) {
        if (lastClickedEdit == window) {
            ResetEditClicks();
        }
        RemoveWindowSubclass(window, EditSubclassProc, subclassId);
    }
    return DefSubclassProc(window, message, wParam, lParam);
}

/// Handles list selection and widget keyboard commands, including copy, paste, removal, and duplication.
/// On associated buttons, transfers focus to the widget list before handling the shortcut.
static LRESULT CALLBACK WidgetListSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    UNREFERENCED_PARAMETER(referenceData);
    bool widgetCommands = subclassId == ID_LIST_WIDGETS || subclassId == ID_REMOVE || subclassId == ID_DUPLICATE;
    HWND list = widgetCommands ? hWidgetList : window;
    if (message == WM_KEYDOWN && widgetCommands && GetFocus() == window) {
        bool controlPressed = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
        bool clipboardShortcut = controlPressed && (wParam == L'A' || wParam == L'C' || wParam == L'V');
        bool listShortcut = clipboardShortcut || wParam == VK_DELETE || wParam == VK_INSERT;
        if (listShortcut) {
            SetFocus(list);
        }
    }
    if (message == WM_KEYDOWN && wParam == L'A' && (GetKeyState(VK_CONTROL) & 0x8000) != 0) {
        SendMessageW(list, LB_SETSEL, TRUE, -1);
        SendMessageW(GetParent(list), WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(list), LBN_SELCHANGE),
            reinterpret_cast<LPARAM>(list));
        return 0;
    }
    if (message == WM_KEYDOWN && widgetCommands && GetFocus() == list && (GetKeyState(VK_CONTROL) & 0x8000) != 0) {
        if (wParam == L'C') {
            CopySelectedWidgetsToClipboard();
            return 0;
        }
        if (wParam == L'V') {
            PasteWidgetsFromClipboard();
            return 0;
        }
    }
    if (message == WM_KEYDOWN && wParam == VK_DELETE && widgetCommands) {
        SendMessageW(hSettings, WM_COMMAND, MAKEWPARAM(ID_REMOVE, BN_CLICKED), 0);
        return 0;
    }
    if (message == WM_KEYDOWN && wParam == VK_INSERT && widgetCommands) {
        int count = static_cast<int>(SendMessageW(list, LB_GETCOUNT, 0, 0));
        int caretIndex = static_cast<int>(SendMessageW(list, LB_GETCARETINDEX, 0, 0));
        if (caretIndex >= 0 && caretIndex < count) {
            bool selected = SendMessageW(list, LB_GETSEL, caretIndex, 0) > 0;
            SendMessageW(list, LB_SETSEL, !selected, caretIndex);
            SendMessageW(list, LB_SETCARETINDEX, std::min(caretIndex + 1, count - 1), TRUE);
            SendMessageW(hSettings, WM_COMMAND, MAKEWPARAM(ID_LIST_WIDGETS, LBN_SELCHANGE),
                reinterpret_cast<LPARAM>(list));
        }
        return 0;
    }
    if (message == WM_NCDESTROY) {
        RemoveWindowSubclass(window, WidgetListSubclassProc, subclassId);
    }
    return DefSubclassProc(window, message, wParam, lParam);
}

/// Changes a checkbox's checked state only when it differs from the requested state.
static void SetCheck(HWND control, bool checked) {
    LRESULT state = checked ? BST_CHECKED : BST_UNCHECKED;
    if (SendMessageW(control, BM_GETCHECK, 0, 0) != state) {
        SendMessageW(control, BM_SETCHECK, state, 0);
    }
}

/// Reports whether a checkbox is fully checked.
static bool GetCheck(HWND control) {
    return SendMessageW(control, BM_GETCHECK, 0, 0) == BST_CHECKED;
}

/// Hides visible fullscreen widgets, remembers them for restoration, and saves settings without preview appearance
/// changes.
/// Returns whether any widget was hidden.
static bool HideFullscreenWidgetsFromEscape() {
    bool hidden = false;
    std::vector<int> hiddenWidgetIds;
    for (size_t widgetIndex = 0; widgetIndex < widgets.size(); widgetIndex++) {
        Widget* widget = widgets[widgetIndex].get();
        if (widget->config.type != WIDGET_FULLSCREEN || !widget->config.visible) {
            continue;
        }
        if (widget->alarmActive || widget->audioStopEvent != nullptr) {
            StopWidgetAlarm(widget);
        }
        widget->config.visible = false;
        hiddenWidgetIds.push_back(widget->config.id);
        ShowWindow(widget->window, SW_HIDE);
        for (size_t windowIndex = 0; windowIndex < widget->fullscreenWindows.size(); windowIndex++) {
            ShowWindow(widget->fullscreenWindows[windowIndex], SW_HIDE);
        }
        for (size_t draftIndex = 0; draftIndex < settingsDraft.size(); draftIndex++) {
            if (settingsDraft[draftIndex].id == widget->config.id) {
                settingsDraft[draftIndex].visible = false;
                if (static_cast<int>(draftIndex) == selectedDraftIndex && hVisibleCheck != nullptr) {
                    SetCheck(hVisibleCheck, false);
                }
                break;
            }
        }
        for (size_t originalIndex = 0; originalIndex < settingsAppearanceOriginals.size(); originalIndex++) {
            if (settingsAppearanceOriginals[originalIndex].id == widget->config.id) {
                settingsAppearanceOriginals[originalIndex].visible = false;
                break;
            }
        }
        hidden = true;
    }
    if (hidden) {
        RememberHiddenWidgets(hiddenWidgetIds);
        RefreshFullscreenPresentation();
        UpdateTrayIcon();
        SaveSettingsWithoutAppearancePreviews();
    }
    return hidden;
}

/// Returns an owned copy of a control's current Unicode text.
static std::wstring GetControlText(HWND control) {
    int length = GetWindowTextLengthW(control);
    std::vector<wchar_t> text(length + 1, 0);
    GetWindowTextW(control, text.data(), static_cast<int>(text.size()));
    return text.data();
}

/// Updates a nonnull control's text only when the visible string changes.
static void SetControlText(HWND control, const wchar_t* text) {
    if (control != nullptr && GetControlText(control) != text) {
        SetWindowTextW(control, text);
    }
}

/// Removes mnemonic markers while converting escaped ampersands to literal ampersands.
static std::wstring RemoveCaptionMnemonic(const std::wstring& caption) {
    std::wstring text;
    for (size_t index = 0; index < caption.size(); index++) {
        if (caption[index] != L'&') {
            text += caption[index];
        } else if (index + 1 < caption.size() && caption[index + 1] == L'&') {
            text += L'&';
            index++;
        }
    }
    return text;
}

/// Updates a caption only when its text differs after mnemonic removal, preserving existing mnemonic assignments
/// otherwise.
static void SetControlCaption(HWND control, const wchar_t* caption) {
    if (control != nullptr && RemoveCaptionMnemonic(GetControlText(control)) != RemoveCaptionMnemonic(caption)) {
        SetWindowTextW(control, caption);
    }
}

/// Changes a nonnull control's enabled state only when needed.
static void SetControlEnabled(HWND control, bool enabled) {
    if (control != nullptr && (IsWindowEnabled(control) != FALSE) != enabled) {
        EnableWindow(control, enabled);
    }
}

/// Changes a nonnull control's own visibility style only when needed.
static void SetControlVisible(HWND control, bool visible) {
    if (control != nullptr && ((GetWindowLongPtrW(control, GWL_STYLE) & WS_VISIBLE) != 0) != visible) {
        ShowWindow(control, visible ? SW_SHOW : SW_HIDE);
    }
}

/// Changes a combo box selection only when the selected index differs.
static void SetComboSelection(HWND combo, int selection) {
    if (combo != nullptr && SendMessageW(combo, CB_GETCURSEL, 0, 0) != selection) {
        SendMessageW(combo, CB_SETCURSEL, selection, 0);
    }
}

/// Updates a trackbar's range only when either endpoint differs.
static void SetTrackBarRange(HWND trackBar, int minimum, int maximum) {
    if (trackBar != nullptr
            && (SendMessageW(trackBar, TBM_GETRANGEMIN, 0, 0) != minimum
                || SendMessageW(trackBar, TBM_GETRANGEMAX, 0, 0) != maximum)) {
        SendMessageW(trackBar, TBM_SETRANGE, TRUE, MAKELPARAM(minimum, maximum));
    }
}

/// Clamps a requested trackbar position to its range and updates it only when changed.
static void SetTrackBarPosition(HWND trackBar, int position) {
    if (trackBar == nullptr) {
        return;
    }
    int minimum = static_cast<int>(SendMessageW(trackBar, TBM_GETRANGEMIN, 0, 0));
    int maximum = static_cast<int>(SendMessageW(trackBar, TBM_GETRANGEMAX, 0, 0));
    position = std::clamp(position, minimum, maximum);
    if (SendMessageW(trackBar, TBM_GETPOS, 0, 0) != position) {
        SendMessageW(trackBar, TBM_SETPOS, TRUE, position);
    }
}

/// Updates an owner-drawn button's stored color and invalidates it only when the color changes.
static void SetButtonColor(HWND button, COLORREF color) {
    if (button != nullptr && static_cast<COLORREF>(GetWindowLongPtrW(button, GWLP_USERDATA)) != color) {
        SetWindowLongPtrW(button, GWLP_USERDATA, color);
        InvalidateRect(button, nullptr, FALSE);
    }
}

/// Draws descriptive text within the supplied bounds using measured word wrapping and the current font's line height.
static void DrawWordWrappedText(HDC dc, const std::wstring& text, const RECT& bounds) {
    TEXTMETRICW metrics = {};
    if (!GetTextMetricsW(dc, &metrics)) {
        return;
    }
    int lineHeight = metrics.tmHeight + metrics.tmExternalLeading;
    int maximumWidth = bounds.right - bounds.left;
    int y = bounds.top;
    size_t position = 0;
    std::wstring line;
    while (position < text.size() && y < bounds.bottom) {
        if (text[position] == L'\r' || text[position] == L'\n') {
            if (!line.empty()) {
                RECT lineRect = {
                    bounds.left,
                    y,
                    bounds.right,
                    std::min(static_cast<LONG>(y + lineHeight), bounds.bottom)
                };
                DrawTextW(dc, line.c_str(), -1, &lineRect, DT_LEFT | DT_TOP | DT_SINGLELINE | DT_NOPREFIX);
                line.clear();
            }
            wchar_t newline = text[position++];
            if (position < text.size() && newline == L'\r' && text[position] == L'\n') {
                position++;
            }
            y += lineHeight;
            continue;
        }
        while (position < text.size() && iswspace(text[position]) && text[position] != L'\r' && text[position] != L'\n') {
            position++;
        }
        size_t wordStart = position;
        while (position < text.size() && !iswspace(text[position])) {
            position++;
        }
        if (wordStart == position) {
            continue;
        }
        std::wstring word = text.substr(wordStart, position - wordStart);
        std::wstring candidate = line.empty() ? word : line + L" " + word;
        SIZE extent = {};
        GetTextExtentPoint32W(dc, candidate.c_str(), static_cast<int>(candidate.size()), &extent);
        if (!line.empty() && extent.cx > maximumWidth) {
            RECT lineRect = {
                bounds.left,
                y,
                bounds.right,
                std::min(static_cast<LONG>(y + lineHeight), bounds.bottom)
            };
            DrawTextW(dc, line.c_str(), -1, &lineRect, DT_LEFT | DT_TOP | DT_SINGLELINE | DT_NOPREFIX);
            y += lineHeight;
            line = word;
        } else {
            line = candidate;
        }
    }
    if (!line.empty() && y < bounds.bottom) {
        RECT lineRect = {
            bounds.left,
            y,
            bounds.right,
            std::min(static_cast<LONG>(y + lineHeight), bounds.bottom)
        };
        DrawTextW(dc, line.c_str(), -1, &lineRect, DT_LEFT | DT_TOP | DT_SINGLELINE | DT_NOPREFIX);
    }
}

/// Assigns nonconflicting mnemonics to eligible visible child captions using the shared set of already assigned keys.
static void AssignSettingsMnemonicsToChildren(HWND parent, std::vector<wchar_t>* usedMnemonics) {
    for (HWND control = GetWindow(parent, GW_CHILD); control != nullptr; control = GetWindow(control, GW_HWNDNEXT)) {
        LONG_PTR style = GetWindowLongPtrW(control, GWL_STYLE);
        if ((style & WS_VISIBLE) == 0) {
            continue;
        }
        wchar_t className[32] = {};
        GetClassNameW(control, className, ARRAYSIZE(className));
        std::wstring text = GetControlText(control);
        bool button = _wcsicmp(className, L"Button") == 0 && (style & WS_TABSTOP) != 0;
        bool label = _wcsicmp(className, L"Static") == 0
            && (style & SS_TYPEMASK) != SS_OWNERDRAW
            && control != hNtpStatus
            && text.find(L':') != std::wstring::npos;
        if (!button && !label) {
            continue;
        }
        std::wstring caption = UniqueMnemonic(text.c_str(), usedMnemonics);
        if (caption != text) {
            SetWindowTextW(control, caption.c_str());
        }
    }
}

/// Returns the settings page corresponding to a tab index, or null for an invalid index.
static HWND GetSettingsPage(int tab) {
    switch (tab) {
        case 0:
            return hGeneralPage;
        case 1:
            return hAppearancePage;
        case 2:
            return hAlarmPage;
        case 3:
            return hTimeSignalPage;
        case 4:
            return hTimePage;
        case 5:
            return hApplicationPage;
        default:
            return nullptr;
    }
}

/// Tests whether a handle matches one of the settings page handles.
static bool IsSettingsPageWindow(HWND window) {
    return window == hGeneralPage
        || window == hAppearancePage
        || window == hAlarmPage
        || window == hTimeSignalPage
        || window == hTimePage
        || window == hApplicationPage;
}

/// Assigns unique mnemonics across the main settings controls and the active page.
static void AssignSettingsMnemonics() {
    if (hSettings == nullptr || !IsWindow(hSettings)) {
        return;
    }
    int tab = hTabs == nullptr ? 0 : TabCtrl_GetCurSel(hTabs);
    HWND activePage = GetSettingsPage(tab);
    std::vector<wchar_t> usedMnemonics;
    AssignSettingsMnemonicsToChildren(hSettings, &usedMnemonics);
    if (activePage != nullptr) {
        AssignSettingsMnemonicsToChildren(activePage, &usedMnemonics);
    }
}

/// Copies the selected built-in NTP server list into its edit control without treating the update as a custom edit.
static void ApplySelectedNtpPresetToEdit() {
    if (hNtpPresetCombo == nullptr || hNtpServersEdit == nullptr) {
        return;
    }
    int preset = static_cast<int>(SendMessageW(hNtpPresetCombo, CB_GETCURSEL, 0, 0));
    if (preset < 0 || preset >= NTP_PRESET_CUSTOM) {
        return;
    }
    std::wstring servers = NtpServersForPreset(preset);
    updatingNtpPresetControls = true;
    SetControlText(hNtpServersEdit, servers.c_str());
    updatingNtpPresetControls = false;
}

/// Maps stored generator volume to the piecewise decibel slider with -18 dB at its midpoint and silence at the left
/// endpoint.
static int TimeSignalVolumeSliderPosition(double volume) {
    if (volume <= TIME_SIGNAL_VOLUME_MIN) {
        return TIME_SIGNAL_VOLUME_SLIDER_MIN;
    }
    double decibels = TimeSignalVolumeDecibels(volume);
    double position = 0.0;
    if (decibels < TIME_SIGNAL_VOLUME_SLIDER_MIDDLE_DB) {
        position = 1.0 + (decibels - TIME_SIGNAL_VOLUME_SLIDER_MIN_DB)
            * (TIME_SIGNAL_VOLUME_SLIDER_MIDDLE - 1)
            / (TIME_SIGNAL_VOLUME_SLIDER_MIDDLE_DB - TIME_SIGNAL_VOLUME_SLIDER_MIN_DB);
    } else {
        position = TIME_SIGNAL_VOLUME_SLIDER_MIDDLE + (decibels - TIME_SIGNAL_VOLUME_SLIDER_MIDDLE_DB)
            * (TIME_SIGNAL_VOLUME_SLIDER_MAX - TIME_SIGNAL_VOLUME_SLIDER_MIDDLE)
            / -TIME_SIGNAL_VOLUME_SLIDER_MIDDLE_DB;
    }
    return std::clamp(static_cast<int>(std::lround(position)), TIME_SIGNAL_VOLUME_SLIDER_MIN + 1,
        TIME_SIGNAL_VOLUME_SLIDER_MAX);
}

/// Maps the slider's two decibel segments back to stored generator volume, reserving the left endpoint for silence.
static double TimeSignalVolumeFromSliderPosition(int position) {
    position = std::clamp(position, TIME_SIGNAL_VOLUME_SLIDER_MIN, TIME_SIGNAL_VOLUME_SLIDER_MAX);
    if (position == TIME_SIGNAL_VOLUME_SLIDER_MIN) {
        return TIME_SIGNAL_VOLUME_MIN;
    }
    double decibels = 0.0;
    if (position < TIME_SIGNAL_VOLUME_SLIDER_MIDDLE) {
        decibels = TIME_SIGNAL_VOLUME_SLIDER_MIN_DB + static_cast<double>(position - 1)
            * (TIME_SIGNAL_VOLUME_SLIDER_MIDDLE_DB - TIME_SIGNAL_VOLUME_SLIDER_MIN_DB)
            / (TIME_SIGNAL_VOLUME_SLIDER_MIDDLE - 1);
    } else {
        decibels = TIME_SIGNAL_VOLUME_SLIDER_MIDDLE_DB + static_cast<double>(position - TIME_SIGNAL_VOLUME_SLIDER_MIDDLE)
            * -TIME_SIGNAL_VOLUME_SLIDER_MIDDLE_DB / (TIME_SIGNAL_VOLUME_SLIDER_MAX - TIME_SIGNAL_VOLUME_SLIDER_MIDDLE);
    }
    return TimeSignalVolumeFromDecibels(decibels);
}

/// Converts the shared decibel slider position to alarm volume in hundredths of a decibel, including the silence
/// sentinel.
static int AlarmVolumeFromSliderPosition(int position) {
    if (position == 0) {
        return ALARM_VOLUME_MIN;
    }
    return static_cast<int>(std::lround(100.0 * TimeSignalVolumeDecibels(TimeSignalVolumeFromSliderPosition(position))));
}

/// Maps alarm hundredths of a decibel to the shared volume slider, placing silence at its left endpoint.
static int AlarmVolumeSliderPosition(int volume) {
    return volume == ALARM_VOLUME_MIN ? 0 : TimeSignalVolumeSliderPosition(TimeSignalVolumeFromDecibels(volume / 100.0));
}

/// Returns the draft's exact alarm volume while its slider position is unchanged, otherwise converting the new
/// position.
static int SelectedAlarmVolume() {
    int position = static_cast<int>(SendMessageW(hAlarmVolumeTrackBar, TBM_GETPOS, 0, 0));
    if (selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
        int volume = settingsDraft[selectedDraftIndex].alarmVolume;
        if (position == AlarmVolumeSliderPosition(volume)) {
            return volume;
        }
    }
    return AlarmVolumeFromSliderPosition(position);
}

/// Refreshes the alarm's decibel label and atomically updates the active audio preview volume.
static void UpdateAlarmVolumeControls() {
    int volume = SelectedAlarmVolume();
    wchar_t label[32] = {};
    if (volume == ALARM_VOLUME_MIN) {
        wcscpy_s(label, L"−∞ dB");
    } else {
        swprintf_s(label, L"%.2f dB", volume / 100.0);
    }
    SetControlText(hAlarmVolumeValue, label);
    if (settingsPreviewVolume != nullptr) {
        settingsPreviewVolume->store(volume);
    }
}

/// Preserves the exact saved generator volume when its slider position is unchanged, otherwise converting the new
/// position.
static double SelectedTimeSignalVolume() {
    int position = static_cast<int>(SendMessageW(hTimeSignalVolumeTrackBar, TBM_GETPOS, 0, 0));
    return position == TimeSignalVolumeSliderPosition(timeSignalVolume)
        ? timeSignalVolume
        : TimeSignalVolumeFromSliderPosition(position);
}

/// Starts or stops the merged time-signal preview from the Test button and active slider drag, updating the button
/// caption.
static void UpdateTimeSignalVolumePreview() {
    bool dragging = timeSignalVolumeDragging
        && hTimeSignalVolumeTrackBar != nullptr
        && IsWindowEnabled(hTimeSignalVolumeTrackBar);
    if (settingsTimeSignalTestActive || dragging) {
        bool generatedTone = IsTimeSignalGeneratorRequired()
            || SendMessageW(hTimeSignalSoundCombo, CB_GETCURSEL, 0, 0) == 0;
        double volume = SelectedTimeSignalVolume();
        if (!StartTimeSignalVolumePreview(generatedTone, volume)) {
            settingsTimeSignalTestActive = false;
        }
    } else {
        StopTimeSignalVolumePreview();
    }
    const wchar_t* caption = settingsTimeSignalTestActive
        ? STOP_TEST_LABELS[appLanguage]
        : TEST_COMMAND_LABELS[appLanguage];
    SetControlCaption(hTimeSignalTestButton, caption);
}

/// Tracks mouse capture on the volume slider to control preview playback and stops it during subclass destruction.
static LRESULT CALLBACK TimeSignalVolumeSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    UNREFERENCED_PARAMETER(referenceData);
    if (message == WM_LBUTTONDOWN || message == WM_LBUTTONDBLCLK) {
        LRESULT result = DefSubclassProc(window, message, wParam, lParam);
        if (IsWindowEnabled(window) && GetCapture() == window) {
            timeSignalVolumeDragging = true;
            UpdateTimeSignalVolumePreview();
        }
        return result;
    }
    if (message == WM_LBUTTONUP
        || message == WM_CAPTURECHANGED
        || message == WM_CANCELMODE
        || message == WM_ENABLE && wParam == FALSE
        || message == WM_SHOWWINDOW && wParam == FALSE) {
        timeSignalVolumeDragging = false;
        UpdateTimeSignalVolumePreview();
    }
    if (message == WM_NCDESTROY) {
        timeSignalVolumeDragging = false;
        StopTimeSignalVolumePreview();
        RemoveWindowSubclass(window, TimeSignalVolumeSubclassProc, subclassId);
    }
    return DefSubclassProc(window, message, wParam, lParam);
}

/// Enables generator volume controls only when applicable, updates the decibel label, and refreshes preview state.
static void UpdateTimeSignalVolumeControls() {
    if (hTimeSignalVolumeTrackBar == nullptr || hTimeSignalVolumeLabel == nullptr || hTimeSignalVolumeValue == nullptr) {
        return;
    }
    bool enabled = IsTimeSignalGeneratorRequired() || SendMessageW(hTimeSignalSoundCombo, CB_GETCURSEL, 0, 0) == 0;
    SetControlEnabled(hTimeSignalVolumeTrackBar, enabled);
    SetControlEnabled(hTimeSignalVolumeLabel, enabled);
    SetControlEnabled(hTimeSignalVolumeValue, enabled);
    double volume = SelectedTimeSignalVolume();
    wchar_t label[32] = {};
    if (volume == 0) {
        wcscpy_s(label, L"−∞ dB");
    } else {
        double decibels = TimeSignalVolumeDecibels(volume);
        swprintf_s(label, L"%.2f dB", decibels);
    }
    SetControlText(hTimeSignalVolumeValue, label);
    SetTimeSignalPreviewVolume(volume);
    if (!enabled) {
        timeSignalVolumeDragging = false;
    }
    UpdateTimeSignalVolumePreview();
}

/// Updates NTP option availability and the localized synchronization status for the selected time source.
static void UpdateNtpSettingsControls() {
    if (hTimeSourceCombo == nullptr || hNtpPresetCombo == nullptr || hNtpServersEdit == nullptr) {
        return;
    }
    int source = static_cast<int>(SendMessageW(hTimeSourceCombo, CB_GETCURSEL, 0, 0));
    bool ntpSelected = source == 1;
    int selectedPreset = static_cast<int>(SendMessageW(hNtpPresetCombo, CB_GETCURSEL, 0, 0));
    bool settingsApplied = ntpSelected == useNtpTime
        && selectedPreset == ntpPreset
        && GetControlText(hNtpServersEdit) == ntpServers;
    SetControlEnabled(hNtpPresetLabel, ntpSelected);
    SetControlEnabled(hNtpPresetCombo, ntpSelected);
    SetControlEnabled(hNtpServersLabel, ntpSelected);
    SetControlEnabled(hNtpServersEdit, ntpSelected);
    SetControlEnabled(hNtpSyncButton, ntpSelected && winsockReady && settingsApplied);
    std::wstring status;
    if (!ntpSelected) {
        status = NTP_STATUS_SYSTEM[appLanguage];
    } else if (!winsockReady) {
        status = NTP_STATUS_FAILED[appLanguage];
    } else if (ntpQueryRunning) {
        status = NTP_STATUS_WAITING[appLanguage];
    } else if (ntpTimeValid && ntpLastQueryFailed) {
        LONGLONG offsetMilliseconds = ntpOffset100Nanoseconds.load() / 10000;
        status = NTP_STATUS_RETAINED[appLanguage];
        status += L" " + ntpActiveServer + L" (" + FormatOffset(offsetMilliseconds) + L")";
    } else if (ntpTimeValid) {
        LONGLONG offsetMilliseconds = ntpOffset100Nanoseconds.load() / 10000;
        status = NTP_STATUS_SYNCHRONIZED[appLanguage];
        status += L" " + ntpActiveServer + L" (" + FormatOffset(offsetMilliseconds) + L")";
    } else if (lastNtpAttemptTick != 0) {
        status = NTP_STATUS_FAILED[appLanguage];
    } else {
        status = NTP_STATUS_WAITING[appLanguage];
    }
    if (GetControlText(hNtpStatus) != status) {
        SetControlText(hNtpStatus, status.c_str());
    }
}

/// Hides inactive pages before revealing the selected page, updates its state and mnemonics, and ends inapplicable
/// previews.
static void ShowSettingsTab(int tab) {
    HWND activePage = GetSettingsPage(tab);
    for (int index = 0; index < SETTINGS_TAB_COUNT; index++) {
        HWND page = GetSettingsPage(index);
        if (page != nullptr && page != activePage) {
            SetControlVisible(page, false);
        }
    }
    if (tab != 5) {
        timeSignalVolumeDragging = false;
        UpdateTimeSignalVolumePreview();
    }
    if (selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
        bool calendar = settingsDraft[selectedDraftIndex].type == WIDGET_CALENDAR;
        bool singleSelection = hWidgetList != nullptr && SendMessageW(hWidgetList, LB_GETSELCOUNT, 0, 0) == 1;
        if (tab == 2 && (!singleSelection || calendar)) {
            for (size_t index = 0; index < alarmControls.size(); index++) {
                SetControlEnabled(alarmControls[index], FALSE);
            }
        }
    }
    AssignSettingsMnemonics();
    if (activePage != nullptr && (GetWindowLongPtrW(activePage, GWL_STYLE) & WS_VISIBLE) == 0) {
        SetWindowPos(activePage, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        SetControlVisible(activePage, true);
    }
}

/// Returns the page for the currently selected tab, using the first tab when the tab control is unavailable.
static HWND GetActiveSettingsPage() {
    int tab = hTabs == nullptr ? 0 : TabCtrl_GetCurSel(hTabs);
    return GetSettingsPage(tab);
}

/// Returns the active widget-specific page, or null for the global Time and Application pages.
static HWND GetActiveWidgetSettingsPage() {
    HWND page = GetActiveSettingsPage();
    if (page == hTimePage || page == hApplicationPage) {
        return nullptr;
    }
    return page;
}

/// Orders controls by vertical position and then horizontal position for spatial keyboard navigation.
static bool SettingsControlComesFirst(const PositionedControl& left, const PositionedControl& right) {
    return left.rect.top == right.rect.top ? left.rect.left < right.rect.left : left.rect.top < right.rect.top;
}

/// Collects visible, enabled tab-stop controls for the active page, using spatial order on the Appearance page.
static std::vector<HWND> GetSettingsTabOrder() {
    HWND page = GetActiveSettingsPage();
    const std::vector<HWND>* groups[] = {
        &generalControls,
        &appearanceControls,
        &alarmControls,
        &timeSignalControls,
        &timeControls,
        &applicationControls
    };
    const std::vector<HWND>* group = nullptr;
    for (int tab = 0; tab < SETTINGS_TAB_COUNT; tab++) {
        if (GetSettingsPage(tab) == page) {
            group = groups[tab];
            break;
        }
    }
    if (group == nullptr) {
        return {};
    }
    std::vector<PositionedControl> positionedControls;
    for (HWND control : *group) {
        if (control == nullptr || GetParent(control) != page || !IsWindowVisible(control) || !IsWindowEnabled(control)) {
            continue;
        }
        LONG_PTR style = GetWindowLongPtrW(control, GWL_STYLE);
        RECT rect = {};
        if ((style & WS_TABSTOP) != 0 && GetWindowRect(control, &rect)) {
            positionedControls.push_back(PositionedControl{
                control,
                rect
            });
        }
    }
    if (page == hAppearancePage) {
        std::sort(positionedControls.begin(), positionedControls.end(), SettingsControlComesFirst);
    }
    std::vector<HWND> controls;
    for (size_t index = 0; index < positionedControls.size(); index++) {
        controls.push_back(positionedControls[index].window);
    }
    return controls;
}

/// Returns the first or last available tab-stop control on the active page, or null when none exists.
static HWND GetSettingsPageBoundaryControl(bool last) {
    std::vector<HWND> controls = GetSettingsTabOrder();
    if (controls.empty()) {
        return nullptr;
    }
    return last ? controls.back() : controls.front();
}

/// Returns the selected listbox indices in list order, or an empty vector when selection cannot be read.
static std::vector<int> GetSelectedWidgetIndices() {
    std::vector<int> selected;
    if (hWidgetList == nullptr || !IsWindow(hWidgetList)) {
        return selected;
    }
    int count = static_cast<int>(SendMessageW(hWidgetList, LB_GETSELCOUNT, 0, 0));
    if (count <= 0) {
        return selected;
    }
    selected.resize(count);
    int copied = static_cast<int>(SendMessageW(hWidgetList, LB_GETSELITEMS, count,
        reinterpret_cast<LPARAM>(selected.data())));
    if (copied < 0) {
        selected.clear();
    } else {
        selected.resize(copied);
    }
    return selected;
}

/// Updates add and duplicate availability from the widget limit and selection, then refreshes page control
/// availability.
static void UpdateSettingsSelectionState(bool updateLayout = false) {
    size_t selectedCount = GetSelectedWidgetIndices().size();
    bool canAdd = settingsDraft.size() < MAX_WIDGET_COUNT;
    SetControlEnabled(GetDlgItem(hSettings, ID_ADD), canAdd);
    SetControlEnabled(GetDlgItem(hSettings, ID_DUPLICATE), canAdd && selectedCount > 0);
    UpdateSettingControlAvailability(updateLayout);
}

/// Clears the list selection, selects a valid requested item, and optionally refreshes dependent controls.
static void SelectOnlyWidgetIndex(int index, bool updateControls = true) {
    if (hWidgetList == nullptr || !IsWindow(hWidgetList)) {
        return;
    }
    SendMessageW(hWidgetList, LB_SETSEL, FALSE, -1);
    if (index >= 0 && index < static_cast<int>(settingsDraft.size())) {
        SendMessageW(hWidgetList, LB_SETSEL, TRUE, index);
        SendMessageW(hWidgetList, LB_SETCARETINDEX, index, FALSE);
    }
    if (updateControls) {
        UpdateSettingsSelectionState();
    }
}

/// Rebuilds numbered widget captions with redraw suspended, optionally preserving selection by persistent widget IDs.
static void RefreshWidgetList(bool preserveSelection = true, bool updateControls = true) {
    WindowRedrawScope redraw(hWidgetList);
    std::vector<int> selectedIds;
    if (preserveSelection) {
        std::vector<int> selectedIndices = GetSelectedWidgetIndices();
        for (size_t index = 0; index < selectedIndices.size(); index++) {
            LRESULT id = SendMessageW(hWidgetList, LB_GETITEMDATA, selectedIndices[index], 0);
            if (id != LB_ERR) {
                selectedIds.push_back(static_cast<int>(id));
            }
        }
    }
    SendMessageW(hWidgetList, LB_RESETCONTENT, 0, 0);
    for (size_t index = 0; index < settingsDraft.size(); index++) {
        std::wstring label = std::to_wstring(index + 1) + L". " + settingsDraft[index].name;
        int item = static_cast<int>(SendMessageW(hWidgetList, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(label.c_str())));
        SendMessageW(hWidgetList, LB_SETITEMDATA, item, settingsDraft[index].id);
    }
    if (!settingsDraft.empty()) {
        selectedDraftIndex = std::clamp(selectedDraftIndex, 0, static_cast<int>(settingsDraft.size()) - 1);
        bool restored = false;
        for (size_t index = 0; index < settingsDraft.size(); index++) {
            if (std::find(selectedIds.begin(), selectedIds.end(), settingsDraft[index].id) != selectedIds.end()) {
                SendMessageW(hWidgetList, LB_SETSEL, TRUE, index);
                restored = true;
            }
        }
        if (!restored || SendMessageW(hWidgetList, LB_GETSEL, selectedDraftIndex, 0) == 0) {
            SendMessageW(hWidgetList, LB_SETSEL, TRUE, selectedDraftIndex);
        }
        SendMessageW(hWidgetList, LB_SETCARETINDEX, selectedDraftIndex, FALSE);
    }
    if (updateControls) {
        UpdateSettingsSelectionState();
    }
}

/// Selects the item whose stored zone key matches case-insensitively, defaulting to the first item when absent.
static void SelectTimeZoneInCombo(const std::wstring& key, HWND combo = hTimeZoneCombo) {
    int selected = 0;
    int count = static_cast<int>(SendMessageW(combo, CB_GETCOUNT, 0, 0));
    for (int index = 0; index < count; index++) {
        size_t zoneIndex = static_cast<size_t>(SendMessageW(combo, CB_GETITEMDATA, index, 0));
        if (zoneIndex < timeZones.size() && _wcsicmp(timeZones[zoneIndex].TimeZoneKeyName, key.c_str()) == 0) {
            selected = index;
            break;
        }
    }
    SetComboSelection(combo, selected);
}

/// Refreshes monitor captions only when needed and applies the widget's monitor selection, defaulting to the first
/// display.
static void LoadMonitorSelection(const WidgetConfig& config) {
    if (hMonitorList == nullptr) {
        return;
    }
    RefreshDisplayMonitors();
    std::vector<std::wstring> labels;
    bool changed = SendMessageW(hMonitorList, LB_GETCOUNT, 0, 0) != static_cast<LRESULT>(displayMonitors.size());
    for (size_t index = 0; index < displayMonitors.size(); index++) {
        int width = displayMonitors[index].rect.right - displayMonitors[index].rect.left;
        int height = displayMonitors[index].rect.bottom - displayMonitors[index].rect.top;
        labels.push_back(std::to_wstring(index + 1) + L".  (" + std::to_wstring(width) + L" × "
            + std::to_wstring(height) + L")");
        if (!changed) {
            LRESULT length = SendMessageW(hMonitorList, LB_GETTEXTLEN, index, 0);
            std::wstring current(length == LB_ERR ? 0 : static_cast<size_t>(length) + 1, L'\0');
            if (length != LB_ERR) {
                SendMessageW(hMonitorList, LB_GETTEXT, index, reinterpret_cast<LPARAM>(current.data()));
                current.resize(static_cast<size_t>(length));
            }
            changed = length == LB_ERR || current != labels.back();
        }
    }
    if (changed) {
        WindowRedrawScope redraw(hMonitorList);
        SendMessageW(hMonitorList, LB_RESETCONTENT, 0, 0);
        for (size_t index = 0; index < labels.size(); index++) {
            int item = static_cast<int>(SendMessageW(hMonitorList, LB_ADDSTRING, 0,
                reinterpret_cast<LPARAM>(labels[index].c_str())));
            SendMessageW(hMonitorList, LB_SETITEMDATA, item, index);
        }
    }
    bool anySelected = false;
    for (const DisplayMonitor& monitor : displayMonitors) {
        if (ContainsMonitorDevice(config.monitorDevices, monitor.device)) {
            anySelected = true;
            break;
        }
    }
    for (size_t index = 0; index < displayMonitors.size(); index++) {
        bool selected =
            ContainsMonitorDevice(config.monitorDevices, displayMonitors[index].device) || !anySelected && index == 0;
        if ((SendMessageW(hMonitorList, LB_GETSEL, index, 0) > 0) != selected) {
            SendMessageW(hMonitorList, LB_SETSEL, selected, index);
        }
    }
}

/// Serializes selected monitor device names with semicolons, defaulting to the first display when no valid item is
/// selected.
static std::wstring GetSelectedMonitorDevices() {
    std::wstring devices;
    if (hMonitorList == nullptr) {
        return devices;
    }
    int count = static_cast<int>(SendMessageW(hMonitorList, LB_GETCOUNT, 0, 0));
    for (int item = 0; item < count; item++) {
        if (SendMessageW(hMonitorList, LB_GETSEL, item, 0) <= 0) {
            continue;
        }
        size_t monitorIndex = static_cast<size_t>(SendMessageW(hMonitorList, LB_GETITEMDATA, item, 0));
        if (monitorIndex >= displayMonitors.size()) {
            continue;
        }
        if (!devices.empty()) {
            devices += L';';
        }
        devices += displayMonitors[monitorIndex].device;
    }
    if (devices.empty() && !displayMonitors.empty()) {
        devices = displayMonitors[0].device;
    }
    return devices;
}

/// Updates a numeric slider label with its suffix only when the formatted text changes.
static void SetSliderValueText(HWND label, int value, const wchar_t* suffix) {
    if (label == nullptr) {
        return;
    }
    wchar_t text[32] = {};
    swprintf_s(text, L"%d%s", value, suffix);
    if (GetControlText(label) == text) {
        return;
    }
    SetControlText(label, text);
}

/// Refreshes appearance slider values and units, including the font description when its size changes.
static void UpdateAppearanceSliderLabels(HWND changedTrackBar = nullptr) {
    if (hOpacityTrackBar == nullptr) {
        return;
    }
    int opacity = static_cast<int>(SendMessageW(hOpacityTrackBar, TBM_GETPOS, 0, 0));
    int fontSize = static_cast<int>(SendMessageW(hFontSizeTrackBar, TBM_GETPOS, 0, 0));
    int padding = static_cast<int>(SendMessageW(hPaddingTrackBar, TBM_GETPOS, 0, 0));
    int borderWidth = static_cast<int>(SendMessageW(hBorderWidthTrackBar, TBM_GETPOS, 0, 0));
    if (changedTrackBar == nullptr || changedTrackBar == hOpacityTrackBar) {
        SetSliderValueText(hOpacityValue, opacity, L" %");
    }
    if (changedTrackBar == nullptr || changedTrackBar == hFontSizeTrackBar) {
        bool fullscreen = selectedDraftIndex >= 0
            && selectedDraftIndex < static_cast<int>(settingsDraft.size())
            && settingsDraft[selectedDraftIndex].type == WIDGET_FULLSCREEN;
        SetSliderValueText(hFontSizeValue, fontSize, fullscreen ? L" %" : L" pt");
    }
    if (changedTrackBar == nullptr || changedTrackBar == hPaddingTrackBar) {
        SetSliderValueText(hPaddingValue, padding, L" px");
    }
    if (changedTrackBar == nullptr || changedTrackBar == hBorderWidthTrackBar) {
        SetSliderValueText(hBorderWidthValue, borderWidth, L" px");
    }
    if (changedTrackBar == hFontSizeTrackBar
            && selectedDraftIndex >= 0
            && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
        WidgetConfig preview = settingsDraft[selectedDraftIndex];
        preview.fontSize = fontSize;
        UpdateFontDescription(preview);
    }
}

/// Copies appearance controls into a widget configuration, mapping selector indices to supported sizes and modes.
static void ReadAppearanceControls(WidgetConfig& config) {
    int sizes[4] = {};
    int sizeCount = GetAnalogClockSizes(sizes);
    int sizeIndex = static_cast<int>(SendMessageW(hSizeCombo, CB_GETCURSEL, 0, 0));
    if (sizeIndex >= 0 && sizeIndex < sizeCount) {
        config.size = sizes[sizeIndex];
    }
    for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
        config.additionalClocks[index].size = GetSelectedAnalogClockSize(config.additionalClocks[index].size,
            hAdditionalSizeCombos[index]);
    }
    config.opacity = std::clamp(static_cast<int>(SendMessageW(hOpacityTrackBar, TBM_GETPOS, 0, 0)),
        WIDGET_OPACITY_MIN, WIDGET_OPACITY_MAX);
    int minimumFontSize = config.type == WIDGET_FULLSCREEN ? FULLSCREEN_FONT_SIZE_MIN : DIGITAL_FONT_SIZE_MIN;
    int maximumFontSize = config.type == WIDGET_FULLSCREEN ? FULLSCREEN_FONT_SIZE_MAX : DIGITAL_FONT_SIZE_MAX;
    config.fontSize = std::clamp(static_cast<int>(SendMessageW(hFontSizeTrackBar, TBM_GETPOS, 0, 0)),
        minimumFontSize, maximumFontSize);
    if (config.type == WIDGET_DIGITAL) {
        config.fontDialogSize = config.fontSize * 10;
    }
    config.fontAntialiasing = SelectedFontAntialiasing(hWidgetAntialiasCombo, config.fontAntialiasing);
    int maximumPadding = config.type == WIDGET_FULLSCREEN ? FULLSCREEN_PADDING_MAX : DIGITAL_PADDING_MAX;
    config.padding = std::clamp(static_cast<int>(SendMessageW(hPaddingTrackBar, TBM_GETPOS, 0, 0)), 0,
        maximumPadding);
    config.borderStyle = std::clamp(static_cast<int>(SendMessageW(hBorderTrackBar, TBM_GETPOS, 0, 0)), 0,
        DIGITAL_BORDER_STYLE_COUNT - 1);
    config.borderWidth = std::clamp(static_cast<int>(SendMessageW(hBorderWidthTrackBar, TBM_GETPOS, 0, 0)), 0,
        DIGITAL_BORDER_WIDTH_MAX);
    config.borderColor = static_cast<COLORREF>(GetWindowLongPtrW(hBorderColorButton, GWLP_USERDATA));
    config.leadingZeroMode = std::clamp(static_cast<int>(SendMessageW(hLeadingZeroCombo, CB_GETCURSEL, 0, 0)), 0,
        LEADING_ZERO_MODE_COUNT - 1);
    config.transparentBackground = GetCheck(hTransparentBackgroundCheck);
    config.disableThemes = GetCheck(hWidgetDisableThemesCheck);
    config.textColor = static_cast<COLORREF>(GetWindowLongPtrW(hTextColorButton, GWLP_USERDATA));
    config.backgroundColor = static_cast<COLORREF>(GetWindowLongPtrW(hBackgroundColorButton, GWLP_USERDATA));
    config.alarmTextColor = static_cast<COLORREF>(GetWindowLongPtrW(hAlarmTextColorButton, GWLP_USERDATA));
    config.alarmBackgroundColor = static_cast<COLORREF>(GetWindowLongPtrW(hAlarmBackgroundColorButton, GWLP_USERDATA));
    config.showToday = GetCheck(hShowTodayCheck);
    config.weekNumbers = GetCheck(hWeekNumbersCheck);
    config.sundayFirst = GetCheck(hSundayFirstCheck);
    int dateFormat = static_cast<int>(SendMessageW(hDateFormatCombo, CB_GETCURSEL, 0, 0));
    if (dateFormat >= 0 && dateFormat < DATE_FORMAT_COUNT) {
        config.dateCopyFormat = dateFormat;
    }
}

/// Saves appearance controls into the selected draft widget and returns false if no valid draft is selected.
static bool SaveAppearanceControlsToDraft() {
    if (selectedDraftIndex < 0 || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
        return false;
    }
    ReadAppearanceControls(settingsDraft[selectedDraftIndex]);
    return true;
}

/// Hides controls inapplicable to the selected widget type; when showApplicable is true, also reveals applicable
/// controls.
static void UpdateSettingControlVisibility(bool showApplicable) {
    if (selectedDraftIndex < 0 || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
        return;
    }
    WidgetType type = settingsDraft[selectedDraftIndex].type;
    bool fullscreen = type == WIDGET_FULLSCREEN;
    bool digital = type == WIDGET_DIGITAL || fullscreen;
    bool calendar = type == WIDGET_CALENDAR || type == WIDGET_PANEL;
    bool panel = type == WIDGET_PANEL;
    bool supportsBorderStyle = !fullscreen && (digital || calendar);
    bool hasSize = type == WIDGET_ANALOG || panel;
    bool hasTextFont = digital || calendar;
    ControlVisibility controlStates[] = {
        { hMonitorLabel, fullscreen },
        { hMonitorList, fullscreen },
        { hBlackoutMonitorsCheck, fullscreen },
        { hSizeLabel, hasSize },
        { hSizeCombo, hasSize },
        { hFontSizeLabel, digital },
        { hFontSizeTrackBar, digital },
        { hFontSizeValue, digital },
        { hFontDescription, digital },
        { hLeadingZeroLabel, digital || panel },
        { hLeadingZeroCombo, digital || panel },
        { hTransparentBackgroundCheck, digital && !fullscreen },
        { hTextColorButton, digital },
        { hAlarmTextColorButton, digital },
        { hAlarmBackgroundColorButton, digital },
        { hPaddingLabel, digital },
        { hPaddingTrackBar, digital },
        { hPaddingValue, digital },
        { hBorderLabel, supportsBorderStyle },
        { hBorderTrackBar, supportsBorderStyle },
        { hBorderColorButton, supportsBorderStyle },
        { hBorderWidthLabel, digital && !fullscreen },
        { hBorderWidthTrackBar, digital && !fullscreen },
        { hBorderWidthValue, digital && !fullscreen },
        { hFontButton, hasTextFont },
        { hPanelTopFontButton, panel },
        { hPanelTimeFontButton, panel },
        { hPanelBottomFontButton, panel },
        { hDefaultAppearanceButton, true },
        { hBackgroundColorButton, digital },
        { hShowTodayCheck, type == WIDGET_CALENDAR },
        { hWeekNumbersCheck, calendar },
        { hSundayFirstCheck, calendar },
        { hDateFormatLabel, calendar },
        { hDateFormatCombo, calendar },
        { hTimeFormatLabel, digital || panel },
        { hTimeFormatCombo, digital || panel },
        { hShowAmPmCheck, digital || panel }
    };
    for (const ControlVisibility& state : controlStates) {
        if (state.control != nullptr && (!state.visible || showApplicable)) {
            SetControlVisible(state.control, state.visible);
        }
    }
    for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
        HWND controls[] = {
            hAdditionalEnabledChecks[index],
            hAdditionalNameLabels[index],
            hAdditionalNameEdits[index],
            hAdditionalTimeZoneLabels[index],
            hAdditionalTimeZoneCombos[index],
            hAdditionalSizeCombos[index]
        };
        for (HWND control : controls) {
            if (control != nullptr && (!panel || showApplicable)) {
                SetControlVisible(control, panel);
            }
        }
    }
}

/// Updates control enabled states for the selected widget and temporarily clears inapplicable checkbox values.
/// When requested, hides inapplicable controls before relayout and reveals applicable controls afterward.
static void UpdateSettingControlAvailability(bool updateLayout) {
    if (selectedDraftIndex < 0 || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
        return;
    }
    if (updateLayout) {
        UpdateSettingControlVisibility(false);
    }
    WidgetType type = settingsDraft[selectedDraftIndex].type;
    bool fullscreen = type == WIDGET_FULLSCREEN;
    bool digital = type == WIDGET_DIGITAL || fullscreen;
    bool calendar = type == WIDGET_CALENDAR || type == WIDGET_PANEL;
    bool panel = type == WIDGET_PANEL;
    WidgetConfig timeConfiguration = settingsDraft[selectedDraftIndex];
    timeConfiguration.language = LanguageFromCombo(hWidgetLanguageCombo);
    timeConfiguration.showUtc = GetCheck(hUtcCheck);
    int timeZoneSelection = static_cast<int>(SendMessageW(hTimeZoneCombo, CB_GETCURSEL, 0, 0));
    if (timeZoneSelection != CB_ERR) {
        size_t zoneIndex = static_cast<size_t>(SendMessageW(hTimeZoneCombo, CB_GETITEMDATA, timeZoneSelection, 0));
        if (zoneIndex < timeZones.size()) {
            timeConfiguration.timeZoneKey = timeZones[zoneIndex].TimeZoneKeyName;
        }
    }
    timeConfiguration.timeFormat = static_cast<int>(SendMessageW(hTimeFormatCombo, CB_GETCURSEL, 0, 0));
    bool supportsBorderStyle = !fullscreen && (digital || calendar);
    bool utc = GetCheck(hUtcCheck);
    bool hasSize = type == WIDGET_ANALOG || type == WIDGET_PANEL;
    bool hasTextFont = digital || calendar;
    bool globalThemesDisabled = hDisableThemesCheck == nullptr ? themesDisabled : GetCheck(hDisableThemesCheck);
    bool widgetThemesDisabled = hWidgetDisableThemesCheck == nullptr
        ? settingsDraft[selectedDraftIndex].disableThemes
        : GetCheck(hWidgetDisableThemesCheck);
    bool calendarFontEnabled = globalThemesDisabled || widgetThemesDisabled;
    bool supportsAlarm = WidgetSupportsSound(type);
    bool runCommand = supportsAlarm && GetCheck(hRunCommandCheck);
    std::wstring commandText = GetControlText(hCommandEdit);
    bool hasCommand = false;
    for (wchar_t character : commandText) {
        if (iswspace(character) == 0) {
            hasCommand = true;
            break;
        }
    }
    int selectedSize = GetSelectedAnalogClockSize(settingsDraft[selectedDraftIndex].size);
    bool supportsSeconds = type != WIDGET_CALENDAR
        && (type != WIDGET_ANALOG || AnalogClockSupportsSeconds(selectedSize));
    bool supportsAmPm = (digital || panel)
        && WidgetUsesTwelveHourTime(timeConfiguration)
        && GetSelectedWidgetIndices().size() == 1;
    SetCheck(hShowAmPmCheck, settingsDraft[selectedDraftIndex].showAmPm && supportsAmPm);
    if (type == WIDGET_ANALOG || type == WIDGET_CALENDAR) {
        SetCheck(hSecondsCheck, settingsDraft[selectedDraftIndex].showSeconds && supportsSeconds);
    }
    if (fullscreen) {
        SetCheck(hTopmostCheck, true);
    }
    if (updateLayout) {
        int minimumFontSize = fullscreen ? FULLSCREEN_FONT_SIZE_MIN : DIGITAL_FONT_SIZE_MIN;
        int maximumFontSize = fullscreen ? FULLSCREEN_FONT_SIZE_MAX : DIGITAL_FONT_SIZE_MAX;
        SetTrackBarRange(hFontSizeTrackBar, minimumFontSize, maximumFontSize);
        int currentFontSize = static_cast<int>(SendMessageW(hFontSizeTrackBar, TBM_GETPOS, 0, 0));
        SetTrackBarPosition(hFontSizeTrackBar, std::clamp(currentFontSize, minimumFontSize, maximumFontSize));
        int maximumPadding = fullscreen ? FULLSCREEN_PADDING_MAX : DIGITAL_PADDING_MAX;
        SetTrackBarRange(hPaddingTrackBar, 0, maximumPadding);
        int currentPadding = static_cast<int>(SendMessageW(hPaddingTrackBar, TBM_GETPOS, 0, 0));
        SetTrackBarPosition(hPaddingTrackBar, std::clamp(currentPadding, 0, maximumPadding));
        UpdateAppearanceSliderLabels();
        SetSettingsControlPosition(hBlackoutMonitorsCheck, 8, 318, 226, 24);
        SetSettingsControlPosition(hSoundsMutedCheck, 308, 87, 110, 24);
    }
    if (updateLayout) {
        int opacityTop = hasSize ? 38 : 4;
        SetSettingsControlPosition(hOpacityLabel, 8, opacityTop + 7, SETTINGS_PAGE_CONTENT_RIGHT - 8, 22);
        SetSettingsControlPosition(hOpacityTrackBar, 121, opacityTop, 250, 32);
        SetSettingsControlPosition(hOpacityValue, 368, opacityTop + 7, 48, 22);
        if (hasTextFont) {
            int fontX = panel ? 238 : 52;
            int fontY = 0;
            if (digital) {
                fontY = 70;
            } else if (panel) {
                fontY = 106;
            } else {
                fontY = 76;
            }
            SetSettingsControlPosition(hFontButton, fontX, fontY, 178, 27);
        }
        if (panel) {
            SetSettingsControlPosition(hPanelTopFontButton, 52, 76, 178, 27);
            SetSettingsControlPosition(hPanelTimeFontButton, 238, 76, 178, 27);
            SetSettingsControlPosition(hPanelBottomFontButton, 52, 106, 178, 27);
            SetSettingsControlPosition(hLeadingZeroLabel, 8, 262, SETTINGS_PAGE_CONTENT_RIGHT - 8, 22);
            SetSettingsControlPosition(hLeadingZeroCombo, 148, 258, 87, 120);
        } else if (digital) {
            SetSettingsControlPosition(hLeadingZeroLabel, 8, 262, SETTINGS_PAGE_CONTENT_RIGHT - 8, 22);
            SetSettingsControlPosition(hLeadingZeroCombo, 148, 258, 87, 120);
            SetSettingsControlPosition(hTransparentBackgroundCheck, 242, 258, 174, 24);
        }
        int defaultAppearanceX = 238;
        int defaultAppearanceY = 318;
        SetSettingsControlPosition(hDefaultAppearanceButton, defaultAppearanceX, defaultAppearanceY, 178, 27);
        if (digital) {
            SetSettingsControlPosition(hBackgroundColorButton, 238, 100, 178, 27);
        }
        if (calendar) {
            int calendarTop = panel ? 140 : 110;
            SetSettingsControlPosition(hWeekNumbersCheck, 8, calendarTop, 150, 24);
            if (panel) {
                SetSettingsControlPosition(hSundayFirstCheck, 165, calendarTop, 205, 24);
            } else {
                SetSettingsControlPosition(hSundayFirstCheck, 8, calendarTop + 30, 205, 24);
            }
            SetSettingsControlPosition(hShowTodayCheck, 8, calendarTop + 60, 364, 24);
            int dateFormatTop = calendarTop + (panel ? 30 : 90);
            SetSettingsControlPosition(hDateFormatLabel, 8, dateFormatTop + 4, SETTINGS_PAGE_CONTENT_RIGHT - 8, 22);
            int dateFormatWidth = ScaleSettingsHorizontal(238)
                + ScaleSettingsHorizontal(178)
                - ScaleSettingsHorizontal(191);
            SetControlPosition(hDateFormatCombo, ScaleSettingsHorizontal(191), dateFormatTop, dateFormatWidth, 240);
        }
        if (supportsBorderStyle) {
            int borderTop = 0;
            if (digital) {
                borderTop = 226;
            } else if (panel) {
                borderTop = 208;
            } else {
                borderTop = 238;
            }
            SetSettingsControlPosition(hBorderLabel, 8, borderTop + 8, SETTINGS_PAGE_CONTENT_RIGHT - 8, 22);
            SetSettingsControlPosition(hBorderTrackBar, 121, borderTop, 111, 32);
            SetSettingsControlPosition(hBorderColorButton, 238, borderTop + 2, 178, 27);
        }
        if (hWidgetDisableThemesCheck != nullptr
                && hWidgetAntialiasLabel != nullptr
                && hWidgetAntialiasCombo != nullptr) {
            const int optionsTop = 292;
            SetSettingsControlPosition(hWidgetAntialiasLabel, 8, optionsTop + 4, SETTINGS_PAGE_CONTENT_RIGHT - 8, 22);
            SetSettingsControlPosition(hWidgetAntialiasCombo, 148, optionsTop, 87, 100);
            SetSettingsControlPosition(hWidgetDisableThemesCheck, 243, optionsTop, 130, 24);
        }
    }
    std::vector<ControlState> controlStates = {
        { hTransparentBackgroundCheck, !fullscreen },
        { hPaddingTrackBar, digital },
        { hBorderTrackBar, supportsBorderStyle },
        {
            hBorderColorButton,
            supportsBorderStyle && SendMessageW(hBorderTrackBar, TBM_GETPOS, 0, 0) == DIGITAL_BORDER_TOOL_WINDOW
        },
        { hBorderWidthTrackBar, !fullscreen },
        { hFontButton, digital || calendarFontEnabled },
        { hSecondsCheck, supportsSeconds },
        { hTimeFormatCombo, (digital || panel) && !WidgetUsesUtcTime(timeConfiguration) },
        { hShowAmPmCheck, supportsAmPm },
        { hUtcTextCheck, (digital || panel) && utc },
        { hTimeZoneLabel, !utc },
        { hTimeZoneCombo, !utc },
        { hTopmostCheck, !fullscreen },
        { hOpacityTrackBar, !fullscreen },
        { hSoundsMutedCheck, supportsAlarm },
        { hAlarmEnabledCheck, supportsAlarm },
        { hAlarmTimeEdit, supportsAlarm },
        { hRunCommandCheck, supportsAlarm },
        { hCommandEdit, runCommand },
        { hBrowseButton, runCommand },
        { hAlarmVolumeLabel, runCommand && LooksLikeAudio(commandText) },
        { hAlarmVolumeTrackBar, runCommand && LooksLikeAudio(commandText) },
        { hAlarmVolumeValue, runCommand && LooksLikeAudio(commandText) },
        { hLoopAudioCheck, runCommand && hasCommand },
        { hTestCommandButton, settingsCommandTestActive || runCommand && hasCommand },
        { hRemoteScriptCheck, supportsAlarm },
        { hRemoteScriptLabel, supportsAlarm && GetCheck(hRemoteScriptCheck) },
        { hRemoteScriptEdit, supportsAlarm && GetCheck(hRemoteScriptCheck) }
    };
    bool singleSelection = GetSelectedWidgetIndices().size() == 1;
    for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
        bool enabled = panel && GetCheck(hAdditionalEnabledChecks[index]);
        controlStates.push_back(ControlState{ hAdditionalEnabledChecks[index], panel });
        controlStates.push_back(ControlState{ hAdditionalNameLabels[index], enabled });
        controlStates.push_back(ControlState{ hAdditionalNameEdits[index], enabled });
        controlStates.push_back(ControlState{ hAdditionalTimeZoneLabels[index], enabled });
        controlStates.push_back(ControlState{ hAdditionalTimeZoneCombos[index], enabled });
        controlStates.push_back(ControlState{ hAdditionalSizeCombos[index], enabled });
    }
    for (int day = 0; day < ALARM_DAY_COUNT; day++) {
        controlStates.push_back(ControlState{ hAlarmDayChecks[day], supportsAlarm && GetCheck(hAlarmEnabledCheck) });
    }
    const std::vector<HWND>* groups[] = {
        &generalControls,
        &appearanceControls,
        &alarmControls,
        &timeSignalControls
    };
    for (const std::vector<HWND>* group : groups) {
        bool groupEnabled = singleSelection;
        if (group == &alarmControls || group == &timeSignalControls) {
            groupEnabled = groupEnabled && supportsAlarm;
        }
        for (HWND control : *group) {
            bool enabled = groupEnabled;
            for (const ControlState& state : controlStates) {
                if (state.control == control) {
                    enabled = enabled && state.enabled;
                    break;
                }
            }
            SetControlEnabled(control, enabled);
        }
    }
    if (updateLayout) {
        UpdateSettingsTextControlLayout(hGeneralPage);
        UpdateSettingsTextControlLayout(hAppearancePage);
        UpdateSettingControlVisibility(true);
        if (GetActiveWidgetSettingsPage() != nullptr) {
            AssignSettingsMnemonics();
        }
    }
}

/// Adjusts a dropdown's pending position and size to the monitor work area before it becomes visible.
/// Removes its subclass when the native list window is destroyed.
static LRESULT CALLBACK ComboBoxDropDownSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR subclassId, DWORD_PTR referenceData) {
    if (message == WM_WINDOWPOSCHANGING) {
        WINDOWPOS* position = reinterpret_cast<WINDOWPOS*>(lParam);
        HWND combo = reinterpret_cast<HWND>(referenceData);
        HMONITOR monitor = MonitorFromWindow(combo, MONITOR_DEFAULTTONEAREST);
        MONITORINFO information = {};
        information.cbSize = sizeof(information);
        RECT current = {};
        RECT comboRect = {};
        if (position != nullptr
                && GetMonitorInfoW(monitor, &information)
                && GetWindowRect(window, &current)
                && GetWindowRect(combo, &comboRect)) {
            LONG workWidth = information.rcWork.right - information.rcWork.left;
            if (workWidth > 0) {
                LONG currentWidth = position->flags & SWP_NOSIZE ? current.right - current.left : position->cx;
                LONG minimumWidth = std::max(1L, comboRect.right - comboRect.left);
                LONG width = std::max(minimumWidth, std::min(currentWidth, workWidth));
                LONG left = position->flags & SWP_NOMOVE ? current.left : position->x;
                LONG maximumLeft = information.rcWork.right - width;
                LONG minimumLeft = std::min(information.rcWork.left, maximumLeft);
                LONG fittedLeft = std::clamp(left, minimumLeft, maximumLeft);
                if (width != currentWidth) {
                    position->cx = width;
                    if (position->flags & SWP_NOSIZE) {
                        position->cy = current.bottom - current.top;
                    }
                    position->flags &= ~SWP_NOSIZE;
                }
                if (fittedLeft != left) {
                    position->x = fittedLeft;
                    if (position->flags & SWP_NOMOVE) {
                        position->y = current.top;
                    }
                    position->flags &= ~SWP_NOMOVE;
                }
            }
        }
    } else if (message == WM_NCDESTROY) {
        RemoveWindowSubclass(window, ComboBoxDropDownSubclassProc, subclassId);
    }
    return DefSubclassProc(window, message, wParam, lParam);
}

/// Refreshes time-zone captions and current UTC offsets only when changed, retaining selection by stored zone index.
static void FillTimeZoneCombo(HWND combo = hTimeZoneCombo) {
    if (combo == nullptr) {
        return;
    }
    SYSTEMTIME utc = {};
    GetApplicationUtcTime(&utc);
    std::vector<std::wstring> labels;
    labels.reserve(timeZones.size());
    bool changed = SendMessageW(combo, CB_GETCOUNT, 0, 0) != static_cast<LRESULT>(timeZones.size());
    for (size_t index = 0; index < timeZones.size(); index++) {
        std::wstring label = TimeZoneDisplayName(timeZones[index], utc);
        if (!changed) {
            int length = static_cast<int>(SendMessageW(combo, CB_GETLBTEXTLEN, index, 0));
            if (length != static_cast<int>(label.size())
                    || SendMessageW(combo, CB_GETITEMDATA, index, 0) != static_cast<LRESULT>(index)) {
                changed = true;
            } else {
                std::wstring current(length + 1, L'\0');
                changed = SendMessageW(combo, CB_GETLBTEXT, index,
                    reinterpret_cast<LPARAM>(current.data())) != length || label != current.c_str();
            }
        }
        labels.push_back(std::move(label));
    }
    if (!changed) {
        return;
    }
    WindowRedrawScope redraw(combo);
    int selected = static_cast<int>(SendMessageW(combo, CB_GETCURSEL, 0, 0));
    LRESULT selectedZone = selected == CB_ERR ? CB_ERR : SendMessageW(combo, CB_GETITEMDATA, selected, 0);
    SendMessageW(combo, CB_RESETCONTENT, 0, 0);
    for (size_t index = 0; index < labels.size(); index++) {
        int item = static_cast<int>(SendMessageW(combo, CB_ADDSTRING, 0,
            reinterpret_cast<LPARAM>(labels[index].c_str())));
        if (item != CB_ERR && item != CB_ERRSPACE) {
            SendMessageW(combo, CB_SETITEMDATA, item, index);
            if (selectedZone == static_cast<LRESULT>(index)) {
                SendMessageW(combo, CB_SETCURSEL, item, 0);
            }
        }
    }
}

/// Measures current items in the dropdown font immediately before opening, adding borders, padding, and scrollbar
/// space.
/// Keeps the dropdown at least as wide as its combo and installs work-area positioning support.
static void UpdateComboBoxDropDownWidth(HWND combo) {
    if (combo == nullptr) {
        return;
    }
    bool timeZoneCombo = combo == hTimeZoneCombo;
    for (HWND additional : hAdditionalTimeZoneCombos) {
        timeZoneCombo = timeZoneCombo || combo == additional;
    }
    if (timeZoneCombo) {
        FillTimeZoneCombo(combo);
    }
    COMBOBOXINFO information = {};
    information.cbSize = sizeof(information);
    HWND list = combo;
    if (GetComboBoxInfo(combo, &information) && information.hwndList != nullptr) {
        list = information.hwndList;
        SetWindowSubclass(information.hwndList, ComboBoxDropDownSubclassProc, COMBO_BOX_DROPDOWN_SUBCLASS_ID,
            reinterpret_cast<DWORD_PTR>(combo));
    }
    HDC dc = GetDC(list);
    if (dc == nullptr) {
        return;
    }
    HFONT font = reinterpret_cast<HFONT>(SendMessageW(list, WM_GETFONT, 0, 0));
    if (font == nullptr) {
        font = reinterpret_cast<HFONT>(SendMessageW(combo, WM_GETFONT, 0, 0));
    }
    if (font == nullptr) {
        font = static_cast<HFONT>(GetStockObject(DEFAULT_GUI_FONT));
    }
    HGDIOBJ previousFont = SelectObject(dc, font);
    LONG maximumWidth = 0;
    int count = static_cast<int>(SendMessageW(combo, CB_GETCOUNT, 0, 0));
    for (int index = 0; index < count; index++) {
        int length = static_cast<int>(SendMessageW(combo, CB_GETLBTEXTLEN, index, 0));
        if (length <= 0) {
            continue;
        }
        std::wstring text(length + 1, L'\0');
        if (SendMessageW(combo, CB_GETLBTEXT, index, reinterpret_cast<LPARAM>(text.data())) == CB_ERR) {
            continue;
        }
        SIZE size = {};
        if (GetTextExtentPoint32W(dc, text.c_str(), length, &size)) {
            ABC spacing = {};
            wchar_t lastCharacter = text[length - 1];
            if (GetCharABCWidthsW(dc, lastCharacter, lastCharacter, &spacing)) {
                size.cx += std::max(0, -spacing.abcC);
            }
            maximumWidth = std::max(maximumWidth, size.cx);
        }
    }
    SelectObject(dc, previousFont);
    ReleaseDC(list, dc);
    LONG width = maximumWidth + 2 * GetSystemMetrics(SM_CXEDGE);
    DWORD listStyle = WS_BORDER;
    DWORD listExtendedStyle = 0;
    if (information.hwndList != nullptr) {
        listStyle = static_cast<DWORD>(GetWindowLongPtrW(information.hwndList, GWL_STYLE));
        listExtendedStyle = static_cast<DWORD>(GetWindowLongPtrW(information.hwndList, GWL_EXSTYLE));
    }
    RECT listRect = {
        0,
        0,
        width,
        1
    };
    if (AdjustWindowRectEx(&listRect, listStyle, FALSE, listExtendedStyle)) {
        width = listRect.right - listRect.left;
    } else {
        width += 2 * GetSystemMetrics(SM_CXBORDER);
    }
    width += GetSystemMetrics(SM_CXVSCROLL);
    RECT rect = {};
    if (GetWindowRect(combo, &rect)) {
        width = std::max(width, rect.right - rect.left);
    }
    SendMessageW(combo, CB_SETDROPPEDWIDTH, width, 0);
}

/// Refreshes date-format captions and examples for the widget language and displayed date while retaining the selected
/// format.
static void FillDateFormatCombo(const WidgetConfig& config) {
    if (hDateFormatCombo == nullptr) {
        return;
    }
    SYSTEMTIME date = {};
    GetDisplayedTime(config, &date);
    std::vector<std::wstring> labels;
    bool changed = SendMessageW(hDateFormatCombo, CB_GETCOUNT, 0, 0) != DATE_FORMAT_COUNT;
    for (int index = 0; index < DATE_FORMAT_COUNT; index++) {
        labels.push_back(DateFormatCaption(config, date, index));
        if (!changed) {
            LRESULT length = SendMessageW(hDateFormatCombo, CB_GETLBTEXTLEN, index, 0);
            std::wstring current(length == CB_ERR ? 0 : static_cast<size_t>(length) + 1, L'\0');
            if (length != CB_ERR) {
                SendMessageW(hDateFormatCombo, CB_GETLBTEXT, index, reinterpret_cast<LPARAM>(current.data()));
                current.resize(static_cast<size_t>(length));
            }
            changed = length == CB_ERR || current != labels.back();
        }
    }
    int selection = std::clamp(config.dateCopyFormat, 0, DATE_FORMAT_COUNT - 1);
    if (changed) {
        WindowRedrawScope redraw(hDateFormatCombo);
        SendMessageW(hDateFormatCombo, CB_RESETCONTENT, 0, 0);
        for (const std::wstring& label : labels) {
            SendMessageW(hDateFormatCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(label.c_str()));
        }
        SetComboSelection(hDateFormatCombo, selection);
    } else {
        SetComboSelection(hDateFormatCombo, selection);
    }
}

/// Loads the selected widget into settings controls while suppressing edit notifications.
/// Hides inapplicable controls before changing values, then updates visibility, layout, and availability.
static void LoadDraftIntoControls() {
    if (selectedDraftIndex < 0 || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
        return;
    }
    bool previousUpdating = updatingSettingsControls;
    updatingSettingsControls = true;
    UpdateSettingControlVisibility(false);
    const WidgetConfig& config = settingsDraft[selectedDraftIndex];
    SetControlText(hNameEdit, config.name.c_str());
    SetComboSelection(hTypeCombo, config.type);
    SetCheck(hVisibleCheck, config.visible);
    SetCheck(hTopmostCheck, config.type == WIDGET_FULLSCREEN || config.topMost);
    bool supportsSeconds = config.type != WIDGET_CALENDAR
        && (config.type != WIDGET_ANALOG || AnalogClockSupportsSeconds(config.size));
    SetCheck(hSecondsCheck, config.showSeconds && supportsSeconds);
    SetCheck(hUtcCheck, config.showUtc);
    SetCheck(hUtcTextCheck, config.showUtcText);
    SetComboSelection(hTimeFormatCombo, config.timeFormat);
    SetComboSelection(hWidgetLanguageCombo, ComboIndexForLanguage(config.language));
    SelectTimeZoneInCombo(config.timeZoneKey);
    for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
        const AdditionalClockConfig& clock = config.additionalClocks[index];
        SetCheck(hAdditionalEnabledChecks[index], clock.enabled);
        SetControlText(hAdditionalNameEdits[index], clock.name.c_str());
        SelectTimeZoneInCombo(clock.timeZoneKey.empty()
            ? config.timeZoneKey
            : clock.timeZoneKey, hAdditionalTimeZoneCombos[index]);
    }
    LoadMonitorSelection(config);
    SetCheck(hBlackoutMonitorsCheck, config.blackoutOtherMonitors);
    SetCheck(hSoundsMutedCheck, config.soundsMuted);
    SetControlText(hOffsetEdit, FormatOffset(config.offsetMilliseconds).c_str());
    int sizes[4] = {};
    int sizeIndex = 1;
    int sizeCount = GetAnalogClockSizes(sizes);
    for (int index = 0; index < sizeCount; index++) {
        if (sizes[index] == config.size) {
            sizeIndex = index;
        }
    }
    SetComboSelection(hSizeCombo, sizeIndex);
    for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
        int size = NormalizeAnalogClockSize(config.additionalClocks[index].size);
        for (int item = 0; item < sizeCount; item++) {
            if (sizes[item] == size) {
                SetComboSelection(hAdditionalSizeCombos[index], item);
                break;
            }
        }
    }
    bool fullscreen = config.type == WIDGET_FULLSCREEN;
    int minimumFontSize = fullscreen ? FULLSCREEN_FONT_SIZE_MIN : DIGITAL_FONT_SIZE_MIN;
    int maximumFontSize = fullscreen ? FULLSCREEN_FONT_SIZE_MAX : DIGITAL_FONT_SIZE_MAX;
    int maximumPadding = fullscreen ? FULLSCREEN_PADDING_MAX : DIGITAL_PADDING_MAX;
    SetTrackBarRange(hFontSizeTrackBar, minimumFontSize, maximumFontSize);
    SetTrackBarRange(hPaddingTrackBar, 0, maximumPadding);
    SetTrackBarPosition(hOpacityTrackBar, config.opacity);
    SetTrackBarPosition(hFontSizeTrackBar, config.fontSize);
    SelectFontAntialiasing(hWidgetAntialiasCombo, config.fontAntialiasing);
    SetTrackBarPosition(hPaddingTrackBar, config.padding);
    SetTrackBarPosition(hBorderTrackBar, config.borderStyle);
    SetTrackBarPosition(hBorderWidthTrackBar, config.borderWidth);
    UpdateAppearanceSliderLabels();
    UpdateFontDescription(config);
    SetComboSelection(hLeadingZeroCombo, config.leadingZeroMode);
    SetCheck(hTransparentBackgroundCheck, config.transparentBackground);
    SetCheck(hWidgetDisableThemesCheck, config.disableThemes);
    SetButtonColor(hTextColorButton, config.textColor);
    SetButtonColor(hBackgroundColorButton, config.backgroundColor);
    SetButtonColor(hBorderColorButton, config.borderColor);
    SetButtonColor(hAlarmTextColorButton, config.alarmTextColor);
    SetButtonColor(hAlarmBackgroundColorButton, config.alarmBackgroundColor);
    SetCheck(hShowTodayCheck, config.showToday);
    SetCheck(hWeekNumbersCheck, config.weekNumbers);
    SetCheck(hSundayFirstCheck, config.sundayFirst);
    FillDateFormatCombo(config);
    SetCheck(hAlarmEnabledCheck, config.alarmEnabled);
    for (int day = 0; day < ALARM_DAY_COUNT; day++) {
        SetCheck(hAlarmDayChecks[day], (config.alarmDays & 1U << day) != 0);
    }
    wchar_t alarm[16] = {};
    swprintf_s(alarm, L"%02d:%02d", config.alarmHour, config.alarmMinute);
    SetControlText(hAlarmTimeEdit, alarm);
    SetCheck(hRunCommandCheck, config.runCommand);
    SetControlText(hCommandEdit, config.command.c_str());
    SetCheck(hLoopAudioCheck, config.loopAudio);
    SetTrackBarPosition(hAlarmVolumeTrackBar, AlarmVolumeSliderPosition(config.alarmVolume));
    UpdateAlarmVolumeControls();
    SetCheck(hRemoteScriptCheck, config.callRemoteScript);
    SetControlText(hRemoteScriptEdit, config.remoteScriptUrl.c_str());
    SetCheck(hAlarmTimeSignalCheck, config.alarmTimeSignal);
    SetComboSelection(hTimeSignalCombo, config.timeSignal);
    UpdateSettingsSelectionState(true);
    updatingSettingsControls = previousUpdating;
}

/// Validates offset, alarm, and command inputs and copies settings controls into a widget configuration.
/// Optionally displays validation errors and focuses the offending control; returns false for invalid input.
static bool ReadWidgetControls(WidgetConfig& config, bool showErrors) {
    LONGLONG offset = 0;
    std::wstring offsetText = GetControlText(hOffsetEdit);
    if (!ParseOffset(offsetText.c_str(), &offset)) {
        if (showErrors) {
            MessageBoxW(hSettings, T(TXT_INVALID_OFFSET), T(TXT_SETTINGS), MB_OK | MB_ICONWARNING);
            SetFocus(hOffsetEdit);
        }
        return false;
    }
    int hour = config.alarmHour;
    int minute = config.alarmMinute;
    std::wstring alarmText = GetControlText(hAlarmTimeEdit);
    if (!ParseAlarmTime(alarmText.c_str(), &hour, &minute)) {
        if (showErrors) {
            MessageBoxW(hSettings, T(TXT_INVALID_TIME), T(TXT_SETTINGS), MB_OK | MB_ICONWARNING);
            SetFocus(hAlarmTimeEdit);
        }
        return false;
    }
    int selectedType = static_cast<int>(SendMessageW(hTypeCombo, CB_GETCURSEL, 0, 0));
    bool remoteScriptEnabled = GetCheck(hRemoteScriptCheck);
    std::wstring remoteScriptUrl = GetControlText(hRemoteScriptEdit);
    if (selectedType != WIDGET_CALENDAR && remoteScriptEnabled && !IsRemoteScriptUrlValid(remoteScriptUrl)) {
        if (showErrors) {
            MessageBoxW(hSettings, INVALID_REMOTE_SCRIPT_URL[appLanguage], T(TXT_SETTINGS), MB_OK | MB_ICONWARNING);
            SetFocus(hRemoteScriptEdit);
            SendMessageW(hRemoteScriptEdit, EM_SETSEL, 0, -1);
        }
        return false;
    }
    config.name = GetControlText(hNameEdit);
    if (config.name.empty()) {
        config.name = TypeName(config.type);
    }
    if (selectedType >= 0 && selectedType < WIDGET_TYPE_COUNT) {
        config.type = static_cast<WidgetType>(selectedType);
    }
    bool supportsSound = WidgetSupportsSound(config.type);
    config.visible = GetCheck(hVisibleCheck);
    config.topMost = GetCheck(hTopmostCheck);
    int selectedSize = GetSelectedAnalogClockSize(config.size);
    bool preserveSeconds = config.type == WIDGET_CALENDAR
        || config.type == WIDGET_ANALOG && !AnalogClockSupportsSeconds(selectedSize);
    if (!preserveSeconds) {
        config.showSeconds = GetCheck(hSecondsCheck);
    }
    config.showUtc = GetCheck(hUtcCheck);
    config.showUtcText = GetCheck(hUtcTextCheck);
    if (IsWindowEnabled(hShowAmPmCheck)) {
        config.showAmPm = GetCheck(hShowAmPmCheck);
    }
    config.timeFormat = std::clamp(static_cast<int>(SendMessageW(hTimeFormatCombo, CB_GETCURSEL, 0, 0)), 0,
        TIME_FORMAT_COUNT - 1);
    config.language = LanguageFromCombo(hWidgetLanguageCombo);
    int zoneSelection = static_cast<int>(SendMessageW(hTimeZoneCombo, CB_GETCURSEL, 0, 0));
    if (zoneSelection != CB_ERR) {
        size_t zoneIndex = static_cast<size_t>(SendMessageW(hTimeZoneCombo, CB_GETITEMDATA, zoneSelection, 0));
        if (zoneIndex < timeZones.size()) {
            config.timeZoneKey = timeZones[zoneIndex].TimeZoneKeyName;
        }
    }
    for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
        AdditionalClockConfig& clock = config.additionalClocks[index];
        clock.enabled = GetCheck(hAdditionalEnabledChecks[index]);
        clock.name = GetControlText(hAdditionalNameEdits[index]);
        int selected = static_cast<int>(SendMessageW(hAdditionalTimeZoneCombos[index], CB_GETCURSEL, 0, 0));
        if (selected != CB_ERR) {
            size_t zone = static_cast<size_t>(SendMessageW(hAdditionalTimeZoneCombos[index], CB_GETITEMDATA,
                selected, 0));
            if (zone < timeZones.size()) {
                clock.timeZoneKey = timeZones[zone].TimeZoneKeyName;
            }
        }
    }
    if (config.type == WIDGET_FULLSCREEN) {
        config.monitorDevices = GetSelectedMonitorDevices();
        config.blackoutOtherMonitors = GetCheck(hBlackoutMonitorsCheck);
    }
    config.offsetMilliseconds = offset;
    config.soundsMuted = supportsSound && GetCheck(hSoundsMutedCheck);
    ReadAppearanceControls(config);
    config.alarmEnabled = supportsSound && GetCheck(hAlarmEnabledCheck);
    config.alarmDays = 0;
    for (int day = 0; day < ALARM_DAY_COUNT; day++) {
        if (GetCheck(hAlarmDayChecks[day])) {
            config.alarmDays |= 1U << day;
        }
    }
    config.alarmTimeSignal = supportsSound && GetCheck(hAlarmTimeSignalCheck);
    config.alarmHour = hour;
    config.alarmMinute = minute;
    config.runCommand = GetCheck(hRunCommandCheck);
    config.command = GetControlText(hCommandEdit);
    config.loopAudio = GetCheck(hLoopAudioCheck);
    config.alarmVolume = SelectedAlarmVolume();
    config.callRemoteScript = remoteScriptEnabled;
    config.remoteScriptUrl = remoteScriptUrl;
    int timeSignal = static_cast<int>(SendMessageW(hTimeSignalCombo, CB_GETCURSEL, 0, 0));
    config.timeSignal = supportsSound
        ? static_cast<TimeSignalMode>(std::clamp(timeSignal, 0, TIME_SIGNAL_COUNT - 1))
        : TIME_SIGNAL_NONE;
    return true;
}

/// Validates and saves controls into the selected draft widget, treating no active draft as a successful no-op.
static bool SaveControlsToDraft(bool showErrors) {
    if (selectedDraftIndex < 0 || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
        return true;
    }
    return ReadWidgetControls(settingsDraft[selectedDraftIndex], showErrors);
}

/// Displays the localized widget-limit notice and returns focus to the widget list after dismissal.
static void ShowWidgetLimitMessage() {
    wchar_t message[256] = {};
    swprintf_s(message, WIDGET_LIMIT_MESSAGES[appLanguage], MAX_WIDGET_COUNT);
    MessageBoxW(hSettings, message, T(TXT_SETTINGS), MB_OK | MB_ICONINFORMATION);
    SetFocus(hWidgetList);
}

/// Validates pending edits and copies selected widget configurations in list order; returns false when no items are
/// selected.
static bool CollectSelectedWidgetConfigs(std::vector<WidgetConfig>* selected) {
    std::vector<int> indices = GetSelectedWidgetIndices();
    if (indices.empty() || !SaveControlsToDraft(true)) {
        return false;
    }
    std::sort(indices.begin(), indices.end());
    selected->clear();
    for (int index : indices) {
        selected->push_back(settingsDraft[index]);
    }
    return true;
}

/// Appends copies in source order with new IDs and localized copy suffixes, selecting the added widgets.
/// Adds only those that fit within the widget limit and reports any omitted copies.
static void AppendWidgetCopies(const std::vector<WidgetConfig>& originals) {
    if (originals.empty()) {
        return;
    }
    size_t availableCount = MAX_WIDGET_COUNT - std::min<size_t>(settingsDraft.size(), MAX_WIDGET_COUNT);
    size_t copyCount = std::min(originals.size(), availableCount);
    if (copyCount == 0) {
        ShowWidgetLimitMessage();
        return;
    }
    int firstCopyIndex = static_cast<int>(settingsDraft.size());
    for (size_t index = 0; index < copyCount; index++) {
        WidgetConfig copy = originals[index];
        copy.id = nextWidgetId++;
        copy.name += WIDGET_COPY_SUFFIXES[appLanguage];
        copy.x = std::min(copy.x, INT_MAX - 28) + 28;
        copy.y = std::min(copy.y, INT_MAX - 28) + 28;
        settingsDraft.push_back(copy);
    }
    selectedDraftIndex = firstCopyIndex;
    RefreshWidgetList(false, false);
    for (int index = firstCopyIndex; index < static_cast<int>(settingsDraft.size()); index++) {
        SendMessageW(hWidgetList, LB_SETSEL, TRUE, index);
    }
    LoadDraftIntoControls();
    UpdateSettingsSelectionState();
    UpdateSettingsApplyButton();
    if (copyCount < originals.size()) {
        ShowWidgetLimitMessage();
    }
}

/// Serializes selected widgets to the application's registered clipboard format, transferring memory ownership only on
/// success.
static void CopySelectedWidgetsToClipboard() {
    std::vector<WidgetConfig> selected;
    if (!CollectSelectedWidgetConfigs(&selected)) {
        return;
    }
    std::vector<BYTE> data;
    if (!SerializeWidgetClipboardData(selected, &data)) {
        return;
    }
    UINT format = RegisterClipboardFormatW(WIDGET_CLIPBOARD_FORMAT);
    if (format == 0) {
        return;
    }
    DWORD length = static_cast<DWORD>(data.size());
    HGLOBAL memory = GlobalAlloc(GMEM_MOVEABLE, sizeof(length) + data.size());
    if (memory == nullptr) {
        return;
    }
    BYTE* buffer = static_cast<BYTE*>(GlobalLock(memory));
    if (buffer == nullptr) {
        GlobalFree(memory);
        return;
    }
    CopyMemory(buffer, &length, sizeof(length));
    CopyMemory(buffer + sizeof(length), data.data(), data.size());
    GlobalUnlock(memory);
    if (!OpenClipboard(hSettings)) {
        GlobalFree(memory);
        return;
    }
    bool success = EmptyClipboard() && SetClipboardData(format, memory) != nullptr;
    CloseClipboard();
    if (!success) {
        GlobalFree(memory);
    }
}

/// Reads and validates the application's bounded clipboard payload, validates pending edits, and appends widget copies.
static void PasteWidgetsFromClipboard() {
    UINT format = RegisterClipboardFormatW(WIDGET_CLIPBOARD_FORMAT);
    if (format == 0 || !IsClipboardFormatAvailable(format) || !OpenClipboard(hSettings)) {
        return;
    }
    HGLOBAL memory = GetClipboardData(format);
    SIZE_T size = GlobalSize(memory);
    std::vector<BYTE> data;
    if (memory != nullptr && size >= sizeof(DWORD)) {
        const BYTE* buffer = static_cast<const BYTE*>(GlobalLock(memory));
        if (buffer != nullptr) {
            DWORD length = 0;
            CopyMemory(&length, buffer, sizeof(length));
            if (length > 0 && length <= size - sizeof(length) && length <= MAX_WIDGET_CLIPBOARD_BYTES) {
                data.assign(buffer + sizeof(length), buffer + sizeof(length) + length);
            }
            GlobalUnlock(memory);
        }
    }
    CloseClipboard();
    std::vector<WidgetConfig> originals;
    if (!DeserializeWidgetClipboardData(data, appLanguage, CreateStoredWidgetDefaults, &originals)
            || !SaveControlsToDraft(true)) {
        return;
    }
    AppendWidgetCopies(originals);
}

/// Copies appearance and calendar-display options while preserving the target's identity, placement, time, and alarm
/// settings.
static void CopyWidgetAppearance(WidgetConfig* target, const WidgetConfig& source) {
    if (target == nullptr) {
        return;
    }
    target->size = source.size;
    for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
        target->additionalClocks[index].size = source.additionalClocks[index].size;
    }
    target->opacity = source.opacity;
    target->fontSize = source.fontSize;
    target->fontDialogSize = source.fontDialogSize;
    target->fontAntialiasing = source.fontAntialiasing;
    target->leadingZeroMode = source.leadingZeroMode;
    target->transparentBackground = source.transparentBackground;
    target->disableThemes = source.disableThemes;
    target->fontFace = source.fontFace;
    target->fontWeight = source.fontWeight;
    target->fontItalic = source.fontItalic;
    target->fontUnderline = source.fontUnderline;
    target->fontStrikeOut = source.fontStrikeOut;
    target->fontCharSet = source.fontCharSet;
    target->panelTopFont = source.panelTopFont;
    target->panelTimeFont = source.panelTimeFont;
    target->panelBottomFont = source.panelBottomFont;
    target->padding = source.padding;
    target->borderStyle = source.borderStyle;
    target->borderWidth = source.borderWidth;
    target->borderColor = source.borderColor;
    target->textColor = source.textColor;
    target->backgroundColor = source.backgroundColor;
    target->alarmTextColor = source.alarmTextColor;
    target->alarmBackgroundColor = source.alarmBackgroundColor;
    target->showToday = source.showToday;
    target->weekNumbers = source.weekNumbers;
    target->sundayFirst = source.sundayFirst;
    target->dateCopyFormat = source.dateCopyFormat;
}

/// Compares all stored font face, size, style, and character-set properties.
static bool FontSelectionsEqual(const FontSelection& left, const FontSelection& right) {
    return left.face == right.face
        && left.dialogSize == right.dialogSize
        && left.weight == right.weight
        && left.italic == right.italic
        && left.underline == right.underline
        && left.strikeOut == right.strikeOut
        && left.charSet == right.charSet;
}

/// Compares all widget configuration fields, including additional clocks and nested font selections.
static bool WidgetConfigurationsEqual(const WidgetConfig& left, const WidgetConfig& right) {
    for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
        const AdditionalClockConfig& first = left.additionalClocks[index];
        const AdditionalClockConfig& second = right.additionalClocks[index];
        if (first.enabled != second.enabled
                || first.name != second.name
                || first.timeZoneKey != second.timeZoneKey
                || first.size != second.size) {
            return false;
        }
    }
    return left.id == right.id
        && left.type == right.type
        && left.name == right.name
        && left.visible == right.visible
        && left.topMost == right.topMost
        && left.showSeconds == right.showSeconds
        && left.showUtc == right.showUtc
        && left.showUtcText == right.showUtcText
        && left.language == right.language
        && left.timeZoneKey == right.timeZoneKey
        && left.monitorDevices == right.monitorDevices
        && left.blackoutOtherMonitors == right.blackoutOtherMonitors
        && left.offsetMilliseconds == right.offsetMilliseconds
        && left.x == right.x
        && left.y == right.y
        && left.previewX == right.previewX
        && left.previewY == right.previewY
        && left.size == right.size
        && left.opacity == right.opacity
        && left.fontSize == right.fontSize
        && left.fontDialogSize == right.fontDialogSize
        && left.fontAntialiasing == right.fontAntialiasing
        && left.leadingZeroMode == right.leadingZeroMode
        && left.showAmPm == right.showAmPm
        && left.timeFormat == right.timeFormat
        && left.transparentBackground == right.transparentBackground
        && left.disableThemes == right.disableThemes
        && left.fontFace == right.fontFace
        && left.fontWeight == right.fontWeight
        && left.fontItalic == right.fontItalic
        && left.fontUnderline == right.fontUnderline
        && left.fontStrikeOut == right.fontStrikeOut
        && left.fontCharSet == right.fontCharSet
        && FontSelectionsEqual(left.panelTopFont, right.panelTopFont)
        && FontSelectionsEqual(left.panelTimeFont, right.panelTimeFont)
        && FontSelectionsEqual(left.panelBottomFont, right.panelBottomFont)
        && left.padding == right.padding
        && left.borderStyle == right.borderStyle
        && left.borderWidth == right.borderWidth
        && left.borderColor == right.borderColor
        && left.textColor == right.textColor
        && left.backgroundColor == right.backgroundColor
        && left.alarmTextColor == right.alarmTextColor
        && left.alarmBackgroundColor == right.alarmBackgroundColor
        && left.showToday == right.showToday
        && left.weekNumbers == right.weekNumbers
        && left.sundayFirst == right.sundayFirst
        && left.dateCopyFormat == right.dateCopyFormat
        && left.timeSignal == right.timeSignal
        && left.soundsMuted == right.soundsMuted
        && left.alarmEnabled == right.alarmEnabled
        && left.alarmDays == right.alarmDays
        && left.alarmTimeSignal == right.alarmTimeSignal
        && left.alarmHour == right.alarmHour
        && left.alarmMinute == right.alarmMinute
        && left.runCommand == right.runCommand
        && left.loopAudio == right.loopAudio
        && left.alarmVolume == right.alarmVolume
        && left.command == right.command
        && left.callRemoteScript == right.callRemoteScript
        && left.remoteScriptUrl == right.remoteScriptUrl;
}

/// Compares global controls and validated widget drafts with applied settings, disregarding runtime position changes.
/// Treats invalid current input as a pending change so Apply can remain available for validation.
static bool HasPendingSettingsChanges() {
    if (LanguageFromCombo(hLanguageCombo) != appLanguage
            || GetCheck(hDisableThemesCheck) != themesDisabled
            || GetCheck(hStartWithWindowsCheck) != startWithWindows
            || GetCheck(hUseXmlSettingsCheck) != storageUsesXml
            || GetCheck(hSnapToWorkAreaCheck) != snapWidgetsToWorkArea
            || SelectedFontAntialiasing(hAppAntialiasCombo, appFontAntialiasing) != appFontAntialiasing
            || settingsAppFontFace != appFontFace
            || settingsAppFontDialogSize != appFontDialogSize
            || settingsAppFontWeight != appFontWeight
            || settingsAppFontItalic != appFontItalic
            || SendMessageW(hTimeSignalSoundCombo, CB_GETCURSEL, 0, 0) != (IsTimeSignalGeneratorRequired()
                || generatedTimeSignal ? 0 : 1)
            || SendMessageW(hTimeSignalVolumeTrackBar, TBM_GETPOS, 0, 0) !=
                TimeSignalVolumeSliderPosition(timeSignalVolume)
            || SendMessageW(hTimeSourceCombo, CB_GETCURSEL, 0, 0) != (useNtpTime ? 1 : 0)
            || SendMessageW(hNtpPresetCombo, CB_GETCURSEL, 0, 0) != ntpPreset) {
        return true;
    }
    if (ntpPreset == NTP_PRESET_CUSTOM && GetControlText(hNtpServersEdit) != ntpServers) {
        return true;
    }
    if (settingsDraft.size() != settingsAppliedWidgets.size()) {
        return true;
    }
    for (size_t index = 0; index < settingsDraft.size(); index++) {
        WidgetConfig candidate = settingsDraft[index];
        if (static_cast<int>(index) == selectedDraftIndex && !ReadWidgetControls(candidate, false)) {
            return true;
        }
        const WidgetConfig& applied = settingsAppliedWidgets[index];
        candidate.x = applied.x;
        candidate.y = applied.y;
        candidate.previewX = applied.previewX;
        candidate.previewY = applied.previewY;
        if (!WidgetConfigurationsEqual(candidate, applied)) {
            return true;
        }
    }
    return false;
}

/// Reenables Apply when pending changes exist; disabling is reserved for a successful explicit Apply action.
static void UpdateSettingsApplyButton() {
    if (hSettings == nullptr || updatingSettingsControls || !IsWindowEnabled(hSettings)) {
        return;
    }
    HWND button = GetDlgItem(hSettings, ID_APPLY);
    if (button == nullptr) {
        return;
    }
    if (HasPendingSettingsChanges()) {
        EnableWindow(button, TRUE);
    }
}

/// Tests whether differences are limited to fields that can be updated without rebuilding the widget window.
static bool WidgetConfigurationsDifferOnlyInRuntimeSettings(const WidgetConfig& left, const WidgetConfig& right) {
    WidgetConfig normalized = left;
    normalized.name = right.name;
    normalized.visible = right.visible;
    normalized.topMost = right.topMost;
    normalized.showSeconds = right.showSeconds;
    normalized.x = right.x;
    normalized.y = right.y;
    normalized.previewX = right.previewX;
    normalized.previewY = right.previewY;
    normalized.fontDialogSize = right.fontDialogSize;
    normalized.dateCopyFormat = right.dateCopyFormat;
    normalized.alarmEnabled = right.alarmEnabled;
    normalized.alarmDays = right.alarmDays;
    normalized.alarmHour = right.alarmHour;
    normalized.alarmMinute = right.alarmMinute;
    normalized.runCommand = right.runCommand;
    normalized.loopAudio = right.loopAudio;
    normalized.alarmVolume = right.alarmVolume;
    normalized.command = right.command;
    normalized.callRemoteScript = right.callRemoteScript;
    normalized.remoteScriptUrl = right.remoteScriptUrl;
    normalized.timeSignal = right.timeSignal;
    normalized.alarmTimeSignal = right.alarmTimeSignal;
    normalized.soundsMuted = right.soundsMuted;
    return WidgetConfigurationsEqual(normalized, right);
}

/// Builds a replacement panel before releasing the old window, transferring runtime alarm and identification state.
/// Returns false if the replacement window cannot be created.
static bool RecreatePanelWidgetBuffered(Widget* widget, const WidgetConfig& configuration) {
    Widget replacement;
    replacement.config = configuration;
    bool activate = GetActiveWindow() == widget->window;
    CreateWidgetWindow(&replacement, activate);
    if (replacement.window == nullptr) {
        return false;
    }
    replacement.alarmActive = widget->alarmActive;
    replacement.flashPhase = widget->flashPhase;
    replacement.lastAlarmDate = widget->lastAlarmDate;
    replacement.lastAlarmMinute = widget->lastAlarmMinute;
    replacement.lastObservedAlarmDate = widget->lastObservedAlarmDate;
    replacement.lastObservedAlarmMinute = widget->lastObservedAlarmMinute;
    replacement.audioStopEvent = widget->audioStopEvent;
    replacement.audioMuteEvent = widget->audioMuteEvent;
    replacement.audioGeneration = widget->audioGeneration;
    replacement.alarmStoppedTick = widget->alarmStoppedTick;
    replacement.identifyActive = widget->identifyActive;
    replacement.identifyPhase = widget->identifyPhase;
    replacement.identifyRestoreHidden = widget->identifyRestoreHidden;
    replacement.identifyRestoreNotTopmost = widget->identifyRestoreNotTopmost;
    replacement.identifyEndTick = widget->identifyEndTick;
    replacement.copyTooltipText = widget->copyTooltipText;
    Widget previous = std::move(*widget);
    *widget = std::move(replacement);
    SetWindowLongPtrW(widget->window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(widget));
    SetWindowLongPtrW(previous.window, GWLP_USERDATA, 0);
    widget->rendered = false;
    RenderWidget(widget);
    RedrawWindow(widget->window, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
    if (previous.copyTooltip != nullptr && IsWindow(previous.copyTooltip)) {
        DestroyWindow(previous.copyTooltip);
    }
    DestroyWindow(previous.window);
    if (previous.calendarFont != nullptr) {
        DeleteObject(previous.calendarFont);
    }
    if (previous.panelDateFont != nullptr) {
        DeleteObject(previous.panelDateFont);
    }
    if (previous.panelTimeZoneFont != nullptr) {
        DeleteObject(previous.panelTimeZoneFont);
    }
    return true;
}

/// Rebuilds a widget for a new configuration while preserving screen-edge attachments and relevant runtime state.
static void RecreateWidgetForConfiguration(Widget* widget, const WidgetConfig& configuration) {
    if (widget == nullptr || widget->window == nullptr) {
        return;
    }
    RECT rect = {};
    bool hasPosition = GetWindowRect(widget->window, &rect) != FALSE;
    int targetX = rect.left;
    int targetY = rect.top;
    bool horizontalAttachment = false;
    if (hasPosition) {
        int newWidth = 0;
        int newHeight = 0;
        GetWidgetDimensions(configuration, &newWidth, &newHeight);
        POINT position = { targetX, targetY };
        if (GetPositionPreservingWorkAreaAttachment(widget->window, newWidth, newHeight, &position,
            &horizontalAttachment)) {
            targetX = position.x;
            targetY = position.y;
        }
    }
    if (hasPosition
            && !horizontalAttachment
            && widget->config.type == WIDGET_PANEL
            && configuration.type == WIDGET_PANEL) {
        POINT previousClockPosition = {};
        POINT newClockPosition = {};
        GetPanelLayout(widget->config, nullptr, &previousClockPosition, nullptr);
        GetPanelLayout(configuration, nullptr, &newClockPosition, nullptr);
        targetX = rect.left + previousClockPosition.x - newClockPosition.x;
    }
    bool fullscreenChanged = widget->config.type == WIDGET_FULLSCREEN || configuration.type == WIDGET_FULLSCREEN;
    WidgetConfig positionedConfiguration = configuration;
    if (hasPosition) {
        positionedConfiguration.x = targetX;
        positionedConfiguration.y = targetY;
    }
    if (widget->config.type == WIDGET_PANEL
            && configuration.type == WIDGET_PANEL
            && RecreatePanelWidgetBuffered(widget, positionedConfiguration)) {
        return;
    }
    bool activate = GetActiveWindow() == widget->window;
    bool alarmActive = widget->alarmActive;
    bool flashPhase = widget->flashPhase;
    int lastAlarmDate = widget->lastAlarmDate;
    int lastAlarmMinute = widget->lastAlarmMinute;
    int lastObservedAlarmDate = widget->lastObservedAlarmDate;
    int lastObservedAlarmMinute = widget->lastObservedAlarmMinute;
    ULONGLONG alarmStoppedTick = widget->alarmStoppedTick;
    bool identifyActive = widget->identifyActive;
    bool identifyPhase = widget->identifyPhase;
    bool identifyRestoreHidden = widget->identifyRestoreHidden;
    bool identifyRestoreNotTopmost = widget->identifyRestoreNotTopmost;
    ULONGLONG identifyEndTick = widget->identifyEndTick;
    if (configuration.type == WIDGET_CALENDAR && (widget->alarmActive || widget->audioStopEvent != nullptr)) {
        StopWidgetAlarm(widget);
        alarmActive = false;
        flashPhase = false;
    }
    if (widget->copyTooltip != nullptr && IsWindow(widget->copyTooltip)) {
        DestroyWindow(widget->copyTooltip);
    }
    widget->copyTooltip = nullptr;
    DestroyWindow(widget->window);
    if (widget->calendarFont != nullptr) {
        DeleteObject(widget->calendarFont);
        widget->calendarFont = nullptr;
    }
    if (widget->panelDateFont != nullptr) {
        DeleteObject(widget->panelDateFont);
        widget->panelDateFont = nullptr;
    }
    if (widget->panelTimeZoneFont != nullptr) {
        DeleteObject(widget->panelTimeZoneFont);
        widget->panelTimeZoneFont = nullptr;
    }
    for (size_t windowIndex = 0; windowIndex < widget->fullscreenWindows.size(); windowIndex++) {
        DestroyWindow(widget->fullscreenWindows[windowIndex]);
    }
    widget->fullscreenWindows.clear();
    widget->window = nullptr;
    widget->analogChild = nullptr;
    widget->analogProc = nullptr;
    for (HWND& child : widget->additionalAnalogChildren) {
        child = nullptr;
    }
    widget->calendarChild = nullptr;
    widget->calendarProc = nullptr;
    widget->config = positionedConfiguration;
    CreateWidgetWindow(widget, activate);
    if (fullscreenChanged && (hSettings == nullptr || !IsWindow(hSettings))) {
        RefreshFullscreenPresentation();
    }
    widget->alarmActive = alarmActive;
    widget->flashPhase = flashPhase;
    widget->lastAlarmDate = lastAlarmDate;
    widget->lastAlarmMinute = lastAlarmMinute;
    widget->lastObservedAlarmDate = lastObservedAlarmDate;
    widget->lastObservedAlarmMinute = lastObservedAlarmMinute;
    widget->alarmStoppedTick = alarmStoppedTick;
    widget->identifyActive = identifyActive;
    widget->identifyPhase = identifyPhase;
    widget->identifyRestoreHidden = identifyRestoreHidden;
    widget->identifyRestoreNotTopmost = identifyRestoreNotTopmost;
    widget->identifyEndTick = identifyEndTick;
    RenderWidget(widget);
}

/// Rebuilds a matching widget using only the supplied appearance fields, retaining its other settings.
static void RecreateWidgetForAppearance(Widget* widget, const WidgetConfig& appearance) {
    if (widget == nullptr || widget->window == nullptr || widget->config.type != appearance.type) {
        return;
    }
    WidgetConfig configuration = widget->config;
    CopyWidgetAppearance(&configuration, appearance);
    RecreateWidgetForConfiguration(widget, configuration);
}

/// Applies draft appearance to a live widget, using in-place updates where possible and rebuilding for structural
/// changes.
static void ApplyWidgetAppearancePreview(Widget* widget, const WidgetConfig& appearance, bool structuralChange) {
    if (widget == nullptr || widget->window == nullptr || widget->config.type != appearance.type) {
        return;
    }
    if (widget->config.type == WIDGET_FULLSCREEN) {
        CopyWidgetAppearance(&widget->config, appearance);
        SetFullscreenPreview(widget);
        widget->rendered = false;
        RenderWidget(widget);
        return;
    }
    bool digital = widget->config.type == WIDGET_DIGITAL;
    bool calendarWidget = widget->config.type == WIDGET_CALENDAR || widget->config.type == WIDGET_PANEL;
    bool themeChanged = widget->config.disableThemes != appearance.disableThemes;
    bool fontAntialiasingChanged = widget->config.fontAntialiasing != appearance.fontAntialiasing;
    bool fontSelectionChanged = widget->config.fontFace != appearance.fontFace
        || widget->config.fontWeight != appearance.fontWeight
        || widget->config.fontItalic != appearance.fontItalic
        || widget->config.fontCharSet != appearance.fontCharSet;
    bool panelFontChanged = !FontSelectionsEqual(widget->config.panelTopFont, appearance.panelTopFont)
        || !FontSelectionsEqual(widget->config.panelTimeFont, appearance.panelTimeFont)
        || !FontSelectionsEqual(widget->config.panelBottomFont, appearance.panelBottomFont);
    bool borderStyleChanged = widget->config.borderStyle != appearance.borderStyle;
    bool borderColorChanged = widget->config.borderColor != appearance.borderColor;
    bool digitalFrameChanged = digital && borderStyleChanged;
    bool nativeFrameChanged = borderStyleChanged && (widget->config.type == WIDGET_CALENDAR
        || digital && !appearance.transparentBackground);
    bool digitalDimensionsChanged = digital && (digitalFrameChanged
        || widget->config.borderWidth != appearance.borderWidth
        || widget->config.padding != appearance.padding
        || widget->config.leadingZeroMode != appearance.leadingZeroMode
        || widget->config.fontSize != appearance.fontSize
        || widget->config.fontFace != appearance.fontFace
        || widget->config.fontWeight != appearance.fontWeight
        || widget->config.fontItalic != appearance.fontItalic
        || widget->config.fontUnderline != appearance.fontUnderline
        || widget->config.fontStrikeOut != appearance.fontStrikeOut
        || widget->config.fontCharSet != appearance.fontCharSet);
    bool requiresRecreation = widget->config.transparentBackground != appearance.transparentBackground
        || !digital && (structuralChange
            || widget->config.size != appearance.size
            || widget->config.showToday != appearance.showToday
            || widget->config.weekNumbers != appearance.weekNumbers
            || widget->config.sundayFirst != appearance.sundayFirst)
        || calendarWidget && (fontSelectionChanged || themeChanged)
        || widget->config.type == WIDGET_PANEL && (borderStyleChanged || panelFontChanged || fontAntialiasingChanged);
    if (requiresRecreation) {
        RecreateWidgetForAppearance(widget, appearance);
        return;
    }
    bool redrawFramedWindow = false;
    if (nativeFrameChanged) {
        DWORD style = static_cast<DWORD>(GetWindowLongPtrW(widget->window, GWL_STYLE));
        DWORD extendedStyle = static_cast<DWORD>(GetWindowLongPtrW(widget->window, GWL_EXSTYLE));
        style &= ~WS_BORDER;
        extendedStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE);
        extendedStyle &= ~WS_EX_COMPOSITED;
        ApplyNativeBorderStyle(appearance.borderStyle, &style, &extendedStyle);
        SetWindowLongPtrW(widget->window, GWL_STYLE, static_cast<LONG_PTR>(style));
        SetWindowLongPtrW(widget->window, GWL_EXSTYLE, static_cast<LONG_PTR>(extendedStyle));
    }
    CopyWidgetAppearance(&widget->config, appearance);
    if ((panelFontChanged || fontAntialiasingChanged) && widget->config.type == WIDGET_PANEL) {
        ApplyPanelLinkFont(widget->panelDateLink, widget->config.panelTopFont, widget->config.fontAntialiasing,
            &widget->panelDateFont);
        ApplyPanelLinkFont(widget->panelTimeZoneLink, widget->config.panelBottomFont, widget->config.fontAntialiasing,
            &widget->panelTimeZoneFont);
        widget->rendered = false;
    }
    if ((fontAntialiasingChanged || fontSelectionChanged) && widget->calendarChild != nullptr) {
        ApplyCalendarFont(widget);
    }
    if (widget->config.type == WIDGET_CALENDAR && borderStyleChanged) {
        int width = 0;
        int height = 0;
        GetWidgetDimensions(widget->config, &width, &height);
        UINT flags = SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOREDRAW | SWP_FRAMECHANGED;
        ResizeWidgetPreservingWorkAreaAttachment(widget, width, height, flags);
        widget->rendered = false;
        redrawFramedWindow = true;
    } else if (digitalDimensionsChanged && !widget->config.transparentBackground) {
        int width = 0;
        int height = 0;
        GetWidgetDimensions(widget->config, &width, &height);
        UINT flags = SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOREDRAW | SWP_FRAMECHANGED;
        ResizeWidgetPreservingWorkAreaAttachment(widget, width, height, flags);
        widget->rendered = false;
        redrawFramedWindow = true;
    }
    if (themeChanged) {
        ApplyWidgetTheme(widget->window, widget->config);
        if (widget->analogChild != nullptr) {
            ApplyWidgetTheme(widget->analogChild, widget->config);
            bool showAnalogSeconds = widget->config.showSeconds && AnalogClockSupportsSeconds(widget->config.size);
            ConfigureAnalogClockControl(widget->analogChild, widget->config.size, showAnalogSeconds);
        }
        if (widget->calendarChild != nullptr) {
            ApplyWidgetTheme(widget->calendarChild, widget->config);
        }
        if (widget->panelDateLink != nullptr) {
            ApplyWidgetTheme(widget->panelDateLink, widget->config);
        }
        if (widget->panelTimeZoneLink != nullptr) {
            ApplyWidgetTheme(widget->panelTimeZoneLink, widget->config);
        }
        if (widget->panelDateTooltip != nullptr) {
            ApplyWidgetTheme(widget->panelDateTooltip, widget->config);
        }
    }
    if (widget->config.type == WIDGET_PANEL || widget->config.type == WIDGET_CALENDAR) {
        LONG_PTR extendedStyle = GetWindowLongPtrW(widget->window, GWL_EXSTYLE);
        if ((extendedStyle & WS_EX_LAYERED) == 0) {
            SetWindowLongPtrW(widget->window, GWL_EXSTYLE, extendedStyle | WS_EX_LAYERED);
        }
        SetLayeredWindowAttributes(widget->window, 0, static_cast<BYTE>(widget->config.opacity * 255 / 100), LWA_ALPHA);
    } else if (widget->config.type == WIDGET_DIGITAL && !widget->config.transparentBackground) {
        SetLayeredWindowAttributes(widget->window, 0, static_cast<BYTE>(widget->config.opacity * 255 / 100), LWA_ALPHA);
    }
    if (redrawFramedWindow) {
        RedrawWindow(widget->window, nullptr, nullptr, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE);
        if (widget->calendarChild != nullptr) {
            RedrawWindow(widget->calendarChild, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE);
        }
        if (widget->config.type == WIDGET_PANEL && widget->analogChild != nullptr) {
            RedrawWindow(widget->analogChild, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE);
        }
        widget->rendered = true;
    } else {
        RenderWidget(widget);
        if (borderColorChanged && UsesConfigurableNativeFrame(widget)) {
            RedrawWindow(widget->window, nullptr, nullptr, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW);
        }
    }
}

/// Saves the selected appearance draft, tracks the widget for later restoration, and updates its live preview.
static void PreviewSelectedWidgetAppearance(bool structuralChange) {
    if (!SaveAppearanceControlsToDraft()) {
        return;
    }
    WidgetConfig& appearance = settingsDraft[selectedDraftIndex];
    Widget* widget = FindWidgetById(appearance.id);
    if (widget == nullptr || widget->config.type != appearance.type) {
        return;
    }
    if (std::find(settingsAppearancePreviewIds.begin(), settingsAppearancePreviewIds.end(), appearance.id) ==
            settingsAppearancePreviewIds.end()) {
        settingsAppearancePreviewIds.push_back(appearance.id);
    }
    settingsAppearancePreviewActive = true;
    ApplyWidgetAppearancePreview(widget, appearance, structuralChange);
}

/// Restores committed configurations for previewed widgets and clears preview tracking.
static void RestoreSettingsAppearancePreview() {
    if (!settingsAppearancePreviewActive) {
        return;
    }
    for (size_t idIndex = 0; idIndex < settingsAppearancePreviewIds.size(); idIndex++) {
        int id = settingsAppearancePreviewIds[idIndex];
        Widget* widget = FindWidgetById(id);
        if (widget == nullptr) {
            continue;
        }
        for (size_t originalIndex = 0; originalIndex < settingsAppearanceOriginals.size(); originalIndex++) {
            if (settingsAppearanceOriginals[originalIndex].id == id) {
                RecreateWidgetForConfiguration(widget, settingsAppearanceOriginals[originalIndex]);
                break;
            }
        }
    }
    settingsAppearancePreviewActive = false;
    settingsAppearancePreviewIds.clear();
}

/// Selects a draft by persistent ID after validating the previous selection; negative IDs leave selection unchanged.
static bool SelectDraftWidgetById(int widgetId) {
    if (widgetId < 0) {
        return true;
    }
    int targetIndex = -1;
    for (size_t index = 0; index < settingsDraft.size(); index++) {
        if (settingsDraft[index].id == widgetId) {
            targetIndex = static_cast<int>(index);
            break;
        }
    }
    if (targetIndex < 0) {
        return false;
    }
    if (targetIndex != selectedDraftIndex && !SaveControlsToDraft(true)) {
        SelectOnlyWidgetIndex(selectedDraftIndex);
        return false;
    }
    selectedDraftIndex = targetIndex;
    SelectOnlyWidgetIndex(selectedDraftIndex, false);
    LoadDraftIntoControls();
    return true;
}

/// Applies a committed configuration with the least required window work, preserving unchanged widgets and updating
/// runtime-only fields in place.
static void ApplyWidgetConfiguration(Widget* widget, const WidgetConfig& configuration, bool previousThemesDisabled) {
    if (widget->window == nullptr) {
        widget->config = configuration;
        CreateWidgetWindow(widget);
        return;
    }
    bool previousThemeDisabled = previousThemesDisabled || widget->config.disableThemes;
    bool newThemeDisabled = themesDisabled || configuration.disableThemes;
    bool themeChanged = previousThemeDisabled != newThemeDisabled;
    if (!themeChanged && WidgetConfigurationsEqual(widget->config, configuration)) {
        return;
    }
    if (themeChanged || !WidgetConfigurationsDifferOnlyInRuntimeSettings(widget->config, configuration)) {
        bool sendToBack = widget->config.topMost && !configuration.topMost;
        RecreateWidgetForConfiguration(widget, configuration);
        if (sendToBack) {
            ApplyWidgetZOrder(widget, true);
        }
        return;
    }
    WidgetConfig previous = widget->config;
    bool alarmChanged = previous.alarmEnabled != configuration.alarmEnabled
        || previous.alarmDays != configuration.alarmDays
        || previous.alarmHour != configuration.alarmHour
        || previous.alarmMinute != configuration.alarmMinute
        || previous.runCommand != configuration.runCommand
        || previous.loopAudio != configuration.loopAudio
        || previous.alarmVolume != configuration.alarmVolume
        || previous.command != configuration.command
        || previous.callRemoteScript != configuration.callRemoteScript
        || previous.remoteScriptUrl != configuration.remoteScriptUrl;
    if (alarmChanged && (widget->alarmActive || widget->audioStopEvent != nullptr)) {
        StopWidgetAlarm(widget);
    }
    if (previous.soundsMuted != configuration.soundsMuted) {
        ApplyWidgetSoundsMuted(widget, configuration.soundsMuted);
    }
    widget->config = configuration;
    bool positionChanged = previous.x != configuration.x || previous.y != configuration.y;
    int targetX = configuration.x;
    int targetY = configuration.y;
    if (widget->fullscreenPreview) {
        positionChanged = previous.previewX != configuration.previewX || previous.previewY != configuration.previewY;
        targetX = configuration.previewX;
        targetY = configuration.previewY;
    }
    RECT currentPosition = {};
    if (positionChanged && GetWindowRect(widget->window, &currentPosition)
        && (currentPosition.left != targetX || currentPosition.top != targetY)) {
        SetWindowPos(widget->window, nullptr, targetX, targetY, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    }
    if (previous.name != configuration.name) {
        SetWindowTextW(widget->window, configuration.name.c_str());
        for (HWND window : widget->fullscreenWindows) {
            SetWindowTextW(window, configuration.name.c_str());
        }
    }
    if (previous.visible != configuration.visible) {
        ShowWindow(widget->window, configuration.visible ? SW_SHOWNOACTIVATE : SW_HIDE);
        if (!widget->fullscreenPreview) {
            for (HWND window : widget->fullscreenWindows) {
                ShowWindow(window, configuration.visible ? SW_SHOWNOACTIVATE : SW_HIDE);
            }
        }
        if (configuration.visible) {
            BringWidgetForward(widget);
        }
    }
    if (previous.topMost != configuration.topMost) {
        ApplyWidgetZOrder(widget, !configuration.topMost);
    }
    bool secondsChanged = previous.showSeconds != configuration.showSeconds;
    if (secondsChanged) {
        if (configuration.type == WIDGET_ANALOG || configuration.type == WIDGET_PANEL) {
            if (!UpdateAnalogSeconds(widget)) {
                RecreateWidgetForConfiguration(widget, configuration);
                return;
            }
        } else if (configuration.type == WIDGET_DIGITAL) {
            int width = 0;
            int height = 0;
            GetWidgetDimensions(configuration, &width, &height);
            ResizeWidgetPreservingWorkAreaAttachment(widget, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
        }
    }
    if (secondsChanged || previous.visible != configuration.visible && configuration.visible) {
        widget->lastRenderKey = -1;
        RenderWidget(widget);
    }
}

/// Commits global controls and widget drafts, reconciles live widgets and previews, saves settings, and refreshes
/// affected UI and time services.
static void ApplySettingsDraft() {
    bool previousUpdating = updatingSettingsControls;
    updatingSettingsControls = true;
    timeSignalVolumeDragging = false;
    UpdateTimeSignalVolumePreview();
    StopSettingsPreview();
    StopTimeSignalPlayback();
    ClearCurrentTimeSignalSources();
    snapWidgetsToWorkArea = GetCheck(hSnapToWorkAreaCheck);
    generatedTimeSignal = SendMessageW(hTimeSignalSoundCombo, CB_GETCURSEL, 0, 0) == 0;
    timeSignalVolume = SelectedTimeSignalVolume();
    std::vector<int> hiddenWidgetIds;
    for (size_t widgetIndex = 0; widgetIndex < widgets.size(); widgetIndex++) {
        if (!widgets[widgetIndex]->config.visible) {
            continue;
        }
        for (size_t draftIndex = 0; draftIndex < settingsDraft.size(); draftIndex++) {
            if (settingsDraft[draftIndex].id == widgets[widgetIndex]->config.id && !settingsDraft[draftIndex].visible) {
                hiddenWidgetIds.push_back(widgets[widgetIndex]->config.id);
                break;
            }
        }
    }
    RememberHiddenWidgets(hiddenWidgetIds);
    for (size_t draftIndex = 0; draftIndex < settingsDraft.size(); draftIndex++) {
        Widget* current = FindWidgetById(settingsDraft[draftIndex].id);
        if (current != nullptr && current->window != nullptr) {
            RECT rect = {};
            if (GetWindowRect(current->window, &rect)) {
                if (current->fullscreenPreview) {
                    int previewWidth = rect.right - rect.left;
                    int previewHeight = rect.bottom - rect.top;
                    GetFullscreenPreviewDimensions(settingsDraft[draftIndex], &previewWidth, &previewHeight);
                    POINT position = { rect.left, rect.top };
                    GetPositionPreservingWorkAreaAttachment(current->window, previewWidth, previewHeight, &position);
                    settingsDraft[draftIndex].previewX = position.x;
                    settingsDraft[draftIndex].previewY = position.y;
                } else {
                    int newWidth = 0;
                    int newHeight = 0;
                    GetWidgetDimensions(settingsDraft[draftIndex], &newWidth, &newHeight);
                    POINT position = { rect.left, rect.top };
                    bool horizontalAttachment = false;
                    GetPositionPreservingWorkAreaAttachment(current->window, newWidth, newHeight, &position,
                        &horizontalAttachment);
                    if (!horizontalAttachment
                            && current->config.type == WIDGET_PANEL
                            && settingsDraft[draftIndex].type == WIDGET_PANEL) {
                        POINT currentClockPosition = {};
                        POINT draftClockPosition = {};
                        GetPanelLayout(current->config, nullptr, &currentClockPosition, nullptr);
                        GetPanelLayout(settingsDraft[draftIndex], nullptr, &draftClockPosition, nullptr);
                        position.x = rect.left + currentClockPosition.x - draftClockPosition.x;
                    }
                    settingsDraft[draftIndex].x = position.x;
                    settingsDraft[draftIndex].y = position.y;
                }
            }
        }
    }
    AppLanguage previousLanguage = appLanguage;
    appLanguage = LanguageFromCombo(hLanguageCombo);
    if (previousLanguage != appLanguage) {
        RefreshInformationWindows();
    }
    bool previousThemesDisabled = themesDisabled;
    themesDisabled = GetCheck(hDisableThemesCheck);
    int previousAppFontAntialiasing = appFontAntialiasing;
    appFontAntialiasing = SelectedFontAntialiasing(hAppAntialiasCombo, appFontAntialiasing);
    std::wstring previousAppFontFace = appFontFace;
    int previousAppFontWeight = appFontWeight;
    bool previousAppFontItalic = appFontItalic;
    appFontFace = settingsAppFontFace;
    appFontDialogSize = std::clamp(settingsAppFontDialogSize, 10, 9990);
    appFontWeight = std::clamp(settingsAppFontWeight, 0, 1000);
    appFontItalic = settingsAppFontItalic;
    storageUsesXml = GetCheck(hUseXmlSettingsCheck);
    bool requestedStartWithWindows = GetCheck(hStartWithWindowsCheck);
    if (requestedStartWithWindows != startWithWindows) {
        if (SetStartWithWindowsEnabled(requestedStartWithWindows)) {
            startWithWindows = requestedStartWithWindows;
        } else {
            SetCheck(hStartWithWindowsCheck, startWithWindows);
        }
    }
    bool newUseNtpTime = SendMessageW(hTimeSourceCombo, CB_GETCURSEL, 0, 0) == 1;
    int newNtpPreset = std::clamp(static_cast<int>(SendMessageW(hNtpPresetCombo, CB_GETCURSEL, 0, 0)), 0,
        NTP_PRESET_COUNT - 1);
    std::wstring newNtpServers = newNtpPreset == NTP_PRESET_CUSTOM
        ? GetControlText(hNtpServersEdit)
        : NtpServersForPreset(newNtpPreset);
    if (!HasNtpServers(newNtpServers)) {
        newNtpPreset = NTP_PRESET_GLOBAL;
        newNtpServers = NtpServersForPreset(newNtpPreset);
    }
    bool previousUseNtpTime = useNtpTime;
    bool ntpSettingsChanged = previousUseNtpTime != newUseNtpTime
        || ntpPreset != newNtpPreset
        || ntpServers != newNtpServers;
    bool keepCurrentNtpTime = previousUseNtpTime && newUseNtpTime && ntpTimeValid.load();
    useNtpTime = newUseNtpTime;
    ntpPreset = newNtpPreset;
    ntpServers = newNtpServers;
    if (ntpSettingsChanged) {
        ntpGeneration++;
        if (!keepCurrentNtpTime) {
            ntpTimeValid = false;
            ntpActiveServer.clear();
        }
        ntpLastQueryFailed = false;
        lastNtpAttemptTick = 0;
        nextNtpAttemptTick = 0;
    }
    if (previousThemesDisabled != themesDisabled) {
        SetThemeAppProperties(themesDisabled
            ? STAP_ALLOW_NONCLIENT
            : STAP_ALLOW_NONCLIENT | STAP_ALLOW_CONTROLS | STAP_ALLOW_WEBCONTENT);
    }
    for (const WidgetConfig& configuration : settingsDraft) {
        Widget* current = FindWidgetById(configuration.id);
        if (current == nullptr) {
            auto added = std::make_unique<Widget>();
            added->config = configuration;
            CreateWidgetWindow(added.get());
            widgets.push_back(std::move(added));
        } else {
            ApplyWidgetConfiguration(current, configuration, previousThemesDisabled);
        }
    }
    for (const std::unique_ptr<Widget>& widget : widgets) {
        bool retained = false;
        for (const WidgetConfig& configuration : settingsDraft) {
            if (configuration.id == widget->config.id) {
                retained = true;
                break;
            }
        }
        if (!retained) {
            DestroyWidgetWindow(widget.get());
        }
    }
    std::vector<std::unique_ptr<Widget>> appliedWidgets;
    appliedWidgets.reserve(settingsDraft.size());
    for (const WidgetConfig& configuration : settingsDraft) {
        for (std::unique_ptr<Widget>& widget : widgets) {
            if (widget != nullptr && widget->config.id == configuration.id) {
                appliedWidgets.push_back(std::move(widget));
                break;
            }
        }
    }
    widgets = std::move(appliedWidgets);
    settingsAppearancePreviewActive = false;
    settingsAppearancePreviewIds.clear();
    settingsAppearanceOriginals.clear();
    bool appFontChanged = previousAppFontAntialiasing != appFontAntialiasing
        || previousAppFontFace != appFontFace
        || previousAppFontWeight != appFontWeight
        || previousAppFontItalic != appFontItalic;
    if (appFontChanged) {
        ResetUiFont();
    }
    bool uiStyleChanged = previousThemesDisabled != themesDisabled || appFontChanged;
    if (uiStyleChanged) {
        ApplyUiStyle(hSettings);
        if (hHelp != nullptr) {
            ApplyUiStyle(hHelp);
        }
        if (hAbout != nullptr) {
            ApplyUiStyle(hAbout);
        }
    }
    settingsApplicationFontPreviewActive = false;
    settingsAppliedWidgets.clear();
    for (const std::unique_ptr<Widget>& widget : widgets) {
        settingsAppliedWidgets.push_back(widget->config);
    }
    UpdateTrayIcon();
    SaveAllSettings();
    if (useNtpTime) {
        StartNtpSynchronization(ntpSettingsChanged);
    }
    settingsDraft = settingsAppliedWidgets;
    settingsAppearanceOriginals = settingsAppliedWidgets;
    settingsAppFontFace = appFontFace;
    settingsAppFontDialogSize = appFontDialogSize;
    settingsAppFontWeight = appFontWeight;
    settingsAppFontItalic = appFontItalic;
    if (SendMessageW(hNtpPresetCombo, CB_GETCURSEL, 0, 0) != ntpPreset) {
        SendMessageW(hNtpPresetCombo, CB_SETCURSEL, ntpPreset, 0);
    }
    if (GetControlText(hNtpServersEdit) != ntpServers) {
        SetWindowTextW(hNtpServersEdit, ntpServers.c_str());
    }
    UpdateNtpSettingsControls();
    if (selectedDraftIndex >= 0
            && selectedDraftIndex < static_cast<int>(settingsDraft.size())
            && GetSelectedWidgetIndices().size() == 1) {
        const WidgetConfig& configuration = settingsDraft[selectedDraftIndex];
        if (GetControlText(hNameEdit) != configuration.name) {
            SetWindowTextW(hNameEdit, configuration.name.c_str());
        }
        std::wstring offset = FormatOffset(configuration.offsetMilliseconds);
        if (GetControlText(hOffsetEdit) != offset) {
            SetWindowTextW(hOffsetEdit, offset.c_str());
        }
        wchar_t alarm[16] = {};
        swprintf_s(alarm, L"%02d:%02d", configuration.alarmHour, configuration.alarmMinute);
        if (GetControlText(hAlarmTimeEdit) != alarm) {
            SetWindowTextW(hAlarmTimeEdit, alarm);
        }
        if (configuration.type == WIDGET_FULLSCREEN && SendMessageW(hMonitorList, LB_GETSELCOUNT, 0, 0) == 0) {
            LoadMonitorSelection(configuration);
        }
    }
    updatingSettingsControls = previousUpdating;
    UpdateSettingsApplyButton();
}

/// Copies placement and the field affected by a context-menu command into a settings snapshot without overwriting
/// unrelated edits.
static void CopyWidgetMenuSetting(WidgetConfig* target, const WidgetConfig& source, int command) {
    target->x = source.x;
    target->y = source.y;
    target->previewX = source.previewX;
    target->previewY = source.previewY;
    if (command == ID_MENU_VISIBLE) {
        target->visible = source.visible;
    } else if (command == ID_MENU_TOPMOST) {
        target->topMost = source.topMost;
    } else if (command == ID_MENU_SECONDS) {
        target->showSeconds = source.showSeconds;
    } else if (command == ID_MENU_ALARM_ENABLED) {
        target->alarmEnabled = source.alarmEnabled;
    } else if (command == ID_MENU_TIME_SIGNAL_ENABLED) {
        target->timeSignal = source.timeSignal;
    } else if (command == ID_MENU_SHOW_TODAY) {
        target->showToday = source.showToday;
    } else if (command >= ID_MENU_DATE_FORMAT_BASE && command < ID_MENU_DATE_FORMAT_BASE + DATE_FORMAT_COUNT) {
        target->dateCopyFormat = source.dateCopyFormat;
    } else if (command >= ID_MENU_SIZE_104 && command <= ID_MENU_SIZE_198) {
        target->size = source.size;
        if (source.type == WIDGET_DIGITAL) {
            target->fontSize = source.fontSize;
            target->fontDialogSize = source.fontSize * 10;
        }
    } else if (command >= ID_ADDITIONAL_SIZE_BASE && command < ID_ADDITIONAL_SIZE_BASE + ADDITIONAL_CLOCK_COUNT) {
        int index = command - ID_ADDITIONAL_SIZE_BASE;
        target->additionalClocks[index].size = source.additionalClocks[index].size;
    }
}

/// Propagates a live menu change into draft, applied, and preview-original configurations.
/// Updates selected controls as needed and reevaluates Apply without rebuilding the settings form.
static void SynchronizeOpenSettings(const Widget* widget, int command) {
    if (hSettings == nullptr || !IsWindow(hSettings) || widget == nullptr) {
        return;
    }
    std::vector<WidgetConfig>* groups[] = {
        &settingsDraft,
        &settingsAppliedWidgets,
        &settingsAppearanceOriginals
    };
    for (std::vector<WidgetConfig>* group : groups) {
        for (WidgetConfig& configuration : *group) {
            if (configuration.id == widget->config.id) {
                CopyWidgetMenuSetting(&configuration, widget->config, command);
                break;
            }
        }
    }
    bool isOnlySelectedWidget = selectedDraftIndex >= 0
        && selectedDraftIndex < static_cast<int>(settingsDraft.size())
        && settingsDraft[selectedDraftIndex].id == widget->config.id
        && GetSelectedWidgetIndices().size() == 1;
    if (isOnlySelectedWidget) {
        bool previousUpdating = updatingSettingsControls;
        updatingSettingsControls = true;
        const WidgetConfig& configuration = settingsDraft[selectedDraftIndex];
        if (command == ID_MENU_VISIBLE) {
            SetCheck(hVisibleCheck, configuration.visible);
        } else if (command == ID_MENU_TOPMOST) {
            SetCheck(hTopmostCheck, configuration.type == WIDGET_FULLSCREEN || configuration.topMost);
        } else if (command == ID_MENU_SECONDS) {
            bool supported = configuration.type != WIDGET_CALENDAR
                && (configuration.type != WIDGET_ANALOG || AnalogClockSupportsSeconds(configuration.size));
            SetCheck(hSecondsCheck, supported && configuration.showSeconds);
        } else if (command == ID_MENU_ALARM_ENABLED) {
            SetCheck(hAlarmEnabledCheck, configuration.alarmEnabled);
            UpdateSettingControlAvailability();
        } else if (command == ID_MENU_TIME_SIGNAL_ENABLED) {
            SetComboSelection(hTimeSignalCombo, configuration.timeSignal);
        } else if (command == ID_MENU_SHOW_TODAY) {
            SetCheck(hShowTodayCheck, configuration.showToday);
        } else if (command >= ID_MENU_DATE_FORMAT_BASE && command < ID_MENU_DATE_FORMAT_BASE + DATE_FORMAT_COUNT) {
            SetComboSelection(hDateFormatCombo, configuration.dateCopyFormat);
        } else {
            int sizes[4] = {};
            int count = GetAnalogClockSizes(sizes);
            HWND combo = hSizeCombo;
            int size = configuration.size;
            if (command >= ID_ADDITIONAL_SIZE_BASE && command < ID_ADDITIONAL_SIZE_BASE + ADDITIONAL_CLOCK_COUNT) {
                int index = command - ID_ADDITIONAL_SIZE_BASE;
                combo = hAdditionalSizeCombos[index];
                size = configuration.additionalClocks[index].size;
            }
            for (int index = 0; index < count; index++) {
                if (sizes[index] == size) {
                    SetComboSelection(combo, index);
                    break;
                }
            }
            if (configuration.type == WIDGET_DIGITAL) {
                SetTrackBarPosition(hFontSizeTrackBar, configuration.fontSize);
                UpdateAppearanceSliderLabels(hFontSizeTrackBar);
            }
            UpdateSettingControlAvailability();
        }
        updatingSettingsControls = previousUpdating;
    }
    UpdateSettingsApplyButton();
}

/// Opens the color dialog using the button's current color and updates the button only when a choice is accepted.
static bool ChooseButtonColor(HWND button) {
    static COLORREF customColors[16] = {};
    CHOOSECOLORW choice = {};
    choice.lStructSize = sizeof(choice);
    choice.hwndOwner = hSettings;
    choice.rgbResult = static_cast<COLORREF>(GetWindowLongPtrW(button, GWLP_USERDATA));
    choice.lpCustColors = customColors;
    choice.Flags = CC_FULLOPEN | CC_RGBINIT;
    if (!ChooseColorW(&choice)) {
        return false;
    }
    SetButtonColor(button, choice.rgbResult);
    return true;
}

/// Updates font-button captions and the selected widget's font description without rewriting unchanged text.
static void UpdateFontDescription(const WidgetConfig& config) {
    if (hFontButton != nullptr) {
        std::wstring caption = config.type == WIDGET_CALENDAR
            || config.type == WIDGET_PANEL ? CALENDAR_FONT_LABELS[appLanguage] : config.fontFace + L"…";
        SetControlCaption(hFontButton, caption.c_str());
    }
    if (hPanelTopFontButton != nullptr) {
        SetControlCaption(hPanelTopFontButton, PANEL_TOP_FONT_LABELS[appLanguage]);
    }
    if (hPanelTimeFontButton != nullptr) {
        SetControlCaption(hPanelTimeFontButton, PANEL_TIME_FONT_LABELS[appLanguage]);
    }
    if (hPanelBottomFontButton != nullptr) {
        SetControlCaption(hPanelBottomFontButton, PANEL_BOTTOM_FONT_LABELS[appLanguage]);
    }
    if (hFontDescription == nullptr) {
        return;
    }
    std::wstring description = config.fontFace + L", " + std::to_wstring(config.fontDialogSize / 10) + L" pt";
    if (config.fontWeight >= FW_BOLD) {
        description += L", Bold";
    }
    if (config.fontItalic) {
        description += L", Italic";
    }
    if (config.fontUnderline) {
        description += L", Underline";
    }
    if (config.fontStrikeOut) {
        description += L", Strikeout";
    }
    SetControlText(hFontDescription, description.c_str());
}

/// Hides unused font-dialog controls, retaining face, style, buttons, and optionally size controls.
static void SetFontDialogControlVisibility(HWND dialog, FontDialogMode mode) {
    HWND child = GetWindow(dialog, GW_CHILD);
    while (child != nullptr) {
        int id = GetDlgCtrlID(child);
        bool visible = id == stc1 || id == stc2 || id == cmb1 || id == cmb2 || id == IDOK || id == IDCANCEL;
        visible = visible || mode == FONT_DIALOG_WITH_SIZE && (id == stc3 || id == cmb3);
        if (!visible) {
            ShowWindow(child, SW_HIDE);
            SetWindowPos(child, nullptr, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOZORDER);
        }
        child = GetWindow(child, GW_HWNDNEXT);
    }
}

/// Customizes the native font dialog's control visibility, compact layout, and background painting.
static UINT_PTR CALLBACK FontDialogHook(HWND dialog, UINT message, WPARAM, LPARAM parameter) {
    if (message == WM_PAINT) {
        PAINTSTRUCT paint = {};
        HDC dc = BeginPaint(dialog, &paint);
        FillRect(dc, &paint.rcPaint, GetSysColorBrush(COLOR_3DFACE));
        EndPaint(dialog, &paint);
        return 1;
    }
    if (message != WM_INITDIALOG) {
        return 0;
    }
    const CHOOSEFONTW* choice = reinterpret_cast<const CHOOSEFONTW*>(parameter);
    FontDialogMode mode = choice == nullptr
        ? FONT_DIALOG_FACE_AND_STYLE
        : static_cast<FontDialogMode>(choice->lCustData);
    SetFontDialogControlVisibility(dialog, mode);
    RECT faceRect = {};
    RECT styleRect = {};
    RECT sizeRect = {};
    RECT okRect = {};
    RECT cancelRect = {};
    HWND hFace = GetDlgItem(dialog, cmb1);
    HWND hStyle = GetDlgItem(dialog, cmb2);
    HWND hSize = GetDlgItem(dialog, cmb3);
    HWND hOk = GetDlgItem(dialog, IDOK);
    HWND hCancel = GetDlgItem(dialog, IDCANCEL);
    bool invalidControls = hFace == nullptr
        || hStyle == nullptr
        || hOk == nullptr
        || hCancel == nullptr
        || !GetWindowRect(hFace, &faceRect)
        || !GetWindowRect(hStyle, &styleRect)
        || !GetWindowRect(hOk, &okRect)
        || !GetWindowRect(hCancel, &cancelRect);
    if (invalidControls) {
        return 0;
    }
    bool invalidSizeControl = mode == FONT_DIALOG_WITH_SIZE && (hSize == nullptr || !GetWindowRect(hSize, &sizeRect));
    if (invalidSizeControl) {
        return 0;
    }
    MapWindowPoints(nullptr, dialog, reinterpret_cast<POINT*>(&faceRect), 2);
    MapWindowPoints(nullptr, dialog, reinterpret_cast<POINT*>(&styleRect), 2);
    if (mode == FONT_DIALOG_WITH_SIZE) {
        MapWindowPoints(nullptr, dialog, reinterpret_cast<POINT*>(&sizeRect), 2);
    }
    MapWindowPoints(nullptr, dialog, reinterpret_cast<POINT*>(&okRect), 2);
    MapWindowPoints(nullptr, dialog, reinterpret_cast<POINT*>(&cancelRect), 2);
    RECT clientRect = {};
    RECT windowRect = {};
    GetClientRect(dialog, &clientRect);
    GetWindowRect(dialog, &windowRect);
    int horizontalMargin = std::max(static_cast<int>(faceRect.left), 8);
    int verticalMargin = horizontalMargin;
    int buttonGap = std::max(static_cast<int>(cancelRect.left - okRect.right), 6);
    int buttonWidth = okRect.right - okRect.left;
    int buttonHeight = okRect.bottom - okRect.top;
    int contentRight = static_cast<int>(std::max(faceRect.right, styleRect.right));
    int contentBottom = static_cast<int>(std::max(faceRect.bottom, styleRect.bottom));
    if (mode == FONT_DIALOG_WITH_SIZE) {
        contentRight = std::max(contentRight, static_cast<int>(sizeRect.right));
        contentBottom = std::max(contentBottom, static_cast<int>(sizeRect.bottom));
    }
    int newClientWidth = std::max(contentRight + horizontalMargin, buttonWidth * 2 + buttonGap + horizontalMargin * 2);
    int buttonY = contentBottom + verticalMargin;
    int cancelX = newClientWidth - horizontalMargin - buttonWidth;
    int okX = cancelX - buttonGap - buttonWidth;
    SetWindowPos(hOk, nullptr, okX, buttonY, buttonWidth, buttonHeight, SWP_NOACTIVATE | SWP_NOZORDER);
    SetWindowPos(hCancel, nullptr, cancelX, buttonY, buttonWidth, buttonHeight, SWP_NOACTIVATE | SWP_NOZORDER);
    int newClientHeight = buttonY + buttonHeight + verticalMargin;
    int nonClientWidth = windowRect.right - windowRect.left - (clientRect.right - clientRect.left);
    int nonClientHeight = windowRect.bottom - windowRect.top - (clientRect.bottom - clientRect.top);
    SetWindowPos(dialog, nullptr, 0, 0, newClientWidth + nonClientWidth, newClientHeight + nonClientHeight,
        SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
    return 0;
}

/// Opens the customized font dialog with size in tenths of a point and copies accepted attributes back to the caller.
/// Returns false for missing required outputs or a canceled or unsuccessful dialog.
static bool ChooseFontAttributes(HWND owner, std::wstring* face, int* sizeTenths, int* weight, bool* italic,
        BYTE* charSet, FontDialogMode mode, bool* underline = nullptr, bool* strikeOut = nullptr) {
    if (face == nullptr || sizeTenths == nullptr || weight == nullptr || italic == nullptr || charSet == nullptr) {
        return false;
    }
    HDC screen = GetDC(owner);
    int dpi = screen == nullptr ? 96 : GetDeviceCaps(screen, LOGPIXELSY);
    if (screen != nullptr) {
        ReleaseDC(owner, screen);
    }
    LOGFONTW font = {};
    font.lfHeight = -MulDiv(std::clamp(*sizeTenths, 10, 9990), dpi, 720);
    font.lfWeight = std::clamp(*weight, 0, 1000);
    font.lfItalic = *italic;
    font.lfUnderline = underline != nullptr && *underline;
    font.lfStrikeOut = strikeOut != nullptr && *strikeOut;
    font.lfCharSet = *charSet;
    font.lfOutPrecision = OUT_DEFAULT_PRECIS;
    font.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    font.lfQuality = DEFAULT_QUALITY;
    font.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
    wcsncpy_s(font.lfFaceName, face->c_str(), _TRUNCATE);
    CHOOSEFONTW choice = {};
    choice.lStructSize = sizeof(choice);
    choice.hwndOwner = owner;
    choice.lpLogFont = &font;
    choice.iPointSize = std::clamp(*sizeTenths, 10, 9990);
    choice.Flags = CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT | CF_FORCEFONTEXIST | CF_ENABLEHOOK;
    choice.lCustData = static_cast<LPARAM>(mode);
    choice.lpfnHook = FontDialogHook;
    if (!ChooseFontW(&choice) || font.lfFaceName[0] == L'\0') {
        return false;
    }
    *face = font.lfFaceName;
    if (mode == FONT_DIALOG_WITH_SIZE) {
        *sizeTenths = std::clamp(choice.iPointSize, 10, 9990);
    }
    *weight = std::clamp(static_cast<int>(font.lfWeight), 0, 1000);
    *italic = font.lfItalic != FALSE;
    if (underline != nullptr) {
        *underline = font.lfUnderline != FALSE;
    }
    if (strikeOut != nullptr) {
        *strikeOut = font.lfStrikeOut != FALSE;
    }
    *charSet = font.lfCharSet;
    return true;
}

/// Edits the selected widget's font, synchronizes digital font size, and previews the accepted appearance.
static void ChooseWidgetFont() {
    if (selectedDraftIndex < 0 || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
        return;
    }
    WidgetConfig& config = settingsDraft[selectedDraftIndex];
    FontDialogMode mode = config.type == WIDGET_DIGITAL ? FONT_DIALOG_WITH_SIZE : FONT_DIALOG_FACE_AND_STYLE;
    if (!ChooseFontAttributes(hSettings, &config.fontFace, &config.fontDialogSize, &config.fontWeight,
        &config.fontItalic, &config.fontCharSet, mode, &config.fontUnderline, &config.fontStrikeOut)) {
        return;
    }
    if (config.type == WIDGET_DIGITAL) {
        config.fontSize = std::clamp((config.fontDialogSize + 5) / 10, DIGITAL_FONT_SIZE_MIN, DIGITAL_FONT_SIZE_MAX);
        config.fontDialogSize = config.fontSize * 10;
        SendMessageW(hFontSizeTrackBar, TBM_SETPOS, TRUE, config.fontSize);
        UpdateAppearanceSliderLabels();
    }
    UpdateFontDescription(config);
    PreviewSelectedWidgetAppearance(false);
}

/// Edits a panel text font including its size and previews accepted changes on the selected widget.
static void ChoosePanelFont(FontSelection* selection) {
    if (selection == nullptr) {
        return;
    }
    if (!ChooseFontAttributes(hSettings, &selection->face, &selection->dialogSize, &selection->weight,
        &selection->italic, &selection->charSet, FONT_DIALOG_WITH_SIZE, &selection->underline, &selection->strikeOut)) {
        return;
    }
    PreviewSelectedWidgetAppearance(false);
}

/// Edits the draft application font, starting from system defaults when unspecified, and previews the accepted choice.
static void ChooseApplicationFont() {
    std::wstring selectedFace = settingsAppFontFace;
    BYTE charSet = DEFAULT_CHARSET;
    if (selectedFace.empty()) {
        NONCLIENTMETRICSW metrics = {};
        metrics.cbSize = sizeof(metrics);
        if (SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof(metrics), &metrics, 0)) {
            selectedFace = metrics.lfMessageFont.lfFaceName;
            charSet = metrics.lfMessageFont.lfCharSet;
        }
    }
    if (ChooseFontAttributes(hSettings, &selectedFace, &settingsAppFontDialogSize, &settingsAppFontWeight,
        &settingsAppFontItalic, &charSet, FONT_DIALOG_FACE_AND_STYLE)) {
        settingsAppFontFace = selectedFace;
        UpdateApplicationFontButtons();
        ApplyApplicationFontPreview();
    }
}

/// Restores type-specific appearance defaults in the selected draft and previews them on the live widget.
static void ResetWidgetAppearance() {
    if (selectedDraftIndex < 0 || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
        return;
    }
    WidgetConfig& config = settingsDraft[selectedDraftIndex];
    WidgetConfig defaults = {};
    SetDefaultWidgetAppearance(&defaults, config.type);
    CopyWidgetAppearance(&config, defaults);
    LoadDraftIntoControls();
    PreviewSelectedWidgetAppearance(false);
}

/// Cancels the alarm test, releases its event handles, restores temporary visual alarm state, and resets the Test
/// caption.
static void StopSettingsPreview() {
    settingsPreviewGeneration++;
    settingsCommandTestActive = false;
    if (settingsPreviewStopEvent != nullptr) {
        SetEvent(settingsPreviewStopEvent);
        CloseHandle(settingsPreviewStopEvent);
        settingsPreviewStopEvent = nullptr;
    }
    if (settingsPreviewMuteEvent != nullptr) {
        CloseHandle(settingsPreviewMuteEvent);
        settingsPreviewMuteEvent = nullptr;
    }
    if (settingsVisualPreviewActive) {
        Widget* widget = FindWidgetById(settingsVisualPreviewWidgetId);
        if (widget != nullptr) {
            widget->alarmActive = false;
            widget->flashPhase = false;
            RenderWidget(widget);
            if (widget->config.type == WIDGET_PANEL && widget->window != nullptr) {
                InvalidateRect(widget->window, nullptr, FALSE);
            }
        }
    }
    settingsVisualPreviewWidgetId = -1;
    settingsVisualPreviewActive = false;
    if (hTestCommandButton != nullptr && GetControlText(hTestCommandButton) != TEST_COMMAND_LABELS[appLanguage]) {
        SetWindowTextW(hTestCommandButton, TEST_COMMAND_LABELS[appLanguage]);
    }
}

/// Toggles the configured alarm test, validating applicable inputs and launching its audio, visual, and remote actions.
static void TestSettingsCommand() {
    if (settingsCommandTestActive) {
        StopSettingsPreview();
        UpdateSettingControlAvailability();
        return;
    }
    if (settingsPreviewStopEvent != nullptr || settingsVisualPreviewActive) {
        StopSettingsPreview();
    }
    std::wstring path = GetControlText(hCommandEdit);
    bool hasCommand = false;
    for (wchar_t character : path) {
        if (iswspace(character) == 0) {
            hasCommand = true;
            break;
        }
    }
    if (!hasCommand) {
        UpdateSettingControlAvailability();
        return;
    }
    bool remoteScriptEnabled = GetCheck(hRemoteScriptCheck);
    std::wstring remoteScriptUrl = GetControlText(hRemoteScriptEdit);
    if (remoteScriptEnabled && !IsRemoteScriptUrlValid(remoteScriptUrl)) {
        MessageBoxW(hSettings, INVALID_REMOTE_SCRIPT_URL[appLanguage], T(TXT_SETTINGS), MB_OK | MB_ICONWARNING);
        SetFocus(hRemoteScriptEdit);
        SendMessageW(hRemoteScriptEdit, EM_SETSEL, 0, -1);
        return;
    }
    settingsCommandTestActive = true;
    SaveAppearanceControlsToDraft();
    PreviewSelectedWidgetAppearance(false);
    if (selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
        Widget* widget = FindWidgetById(settingsDraft[selectedDraftIndex].id);
        if (widget != nullptr && widget->config.type != WIDGET_CALENDAR && !widget->alarmActive) {
            settingsVisualPreviewWidgetId = widget->config.id;
            settingsVisualPreviewActive = true;
            widget->alarmActive = true;
            widget->flashPhase = true;
            RenderWidget(widget);
            if (widget->config.type == WIDGET_PANEL && widget->window != nullptr) {
                InvalidateRect(widget->window, nullptr, FALSE);
            }
        }
    }
    SetCheck(hRunCommandCheck, true);
    if (LooksLikeAudio(path)) {
        bool muted = selectedDraftIndex >= 0
            && selectedDraftIndex < static_cast<int>(settingsDraft.size())
            && settingsDraft[selectedDraftIndex].soundsMuted;
        settingsPreviewVolume = std::make_shared<std::atomic<int>>(SelectedAlarmVolume());
        StartAudioPlaybackAsync(path, GetCheck(hLoopAudioCheck), muted, settingsPreviewVolume,
            hController, WM_SETTINGS_AUDIO_FINISHED, -1, settingsPreviewGeneration, &settingsPreviewStopEvent,
            &settingsPreviewMuteEvent);
    } else {
        StartLocalCommandAsync(path);
    }
    if (remoteScriptEnabled) {
        StartRemoteScriptAsync(remoteScriptUrl);
    }
    if (settingsPreviewStopEvent == nullptr && !settingsVisualPreviewActive) {
        StopSettingsPreview();
        return;
    }
    SetWindowTextW(hTestCommandButton, STOP_TEST_LABELS[appLanguage]);
}

/// Opens the localized file picker, enables the selected alarm command, and defaults recognized audio files to looping
/// playback.
static void BrowseForCommand() {
    wchar_t fileName[MAX_PATH] = {};
    OPENFILENAMEW dialog = {};
    dialog.lStructSize = sizeof(dialog);
    dialog.hwndOwner = hSettings;
    dialog.lpstrFile = fileName;
    dialog.nMaxFile = ARRAYSIZE(fileName);
    dialog.lpstrFilter = COMMAND_FILE_FILTERS[appLanguage];
    dialog.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    if (GetOpenFileNameW(&dialog)) {
        SetCheck(hRunCommandCheck, true);
        SetWindowTextW(hCommandEdit, fileName);
        if (LooksLikeAudio(fileName)) {
            SetCheck(hLoopAudioCheck, true);
        }
        UpdateSettingControlAvailability();
    }
}

/// Creates all settings pages and controls, populates selectors, and applies shared layout, clipping, scrolling, fonts,
/// and themes.
static void CreateSettingsControls() {
    WindowRedrawScope redraw(hSettings);
    bool previousUpdating = updatingSettingsControls;
    updatingSettingsControls = true;
    generalControls.clear();
    appearanceControls.clear();
    alarmControls.clear();
    timeSignalControls.clear();
    timeControls.clear();
    applicationControls.clear();
    AddStatic(hSettings, TXT_TYPE, 10, 10, 22);
    hAddType = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST, 62, 7, 160, 220, hSettings, ID_ADD_TYPE);
    for (int type = 0; type < WIDGET_TYPE_COUNT; type++) {
        SendMessageW(hAddType, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(TypeName(static_cast<WidgetType>(type))));
    }
    SendMessageW(hAddType, CB_SETCURSEL, lastAddedWidgetType, 0);
    AddControl(0, L"BUTTON", Mnemonic(TXT_ADD).c_str(), WS_TABSTOP, 228, 5, 84, 27, hSettings, ID_ADD);
    hWidgetList = AddControl(WS_EX_CLIENTEDGE, L"LISTBOX", L"",
        WS_TABSTOP | LBS_NOTIFY | LBS_EXTENDEDSEL | LBS_NOINTEGRALHEIGHT | WS_VSCROLL,
        10, 39, 302, 368, hSettings, ID_LIST_WIDGETS);
    AddControl(0, L"BUTTON", Mnemonic(TXT_REMOVE).c_str(), WS_TABSTOP, 10, 413, 148, 27, hSettings, ID_REMOVE);
    AddControl(0, L"BUTTON", Mnemonic(TXT_DUPLICATE).c_str(), WS_TABSTOP, 164, 413, 148, 27, hSettings, ID_DUPLICATE);
    hTabs = AddControl(0, WC_TABCONTROLW, L"", WS_TABSTOP | TCS_FOCUSONBUTTONDOWN, 322, 7, 430, 435, hSettings, ID_TABS);
    if (hTabs == nullptr) {
        return;
    }
    TCITEMW tab = {};
    tab.mask = TCIF_TEXT;
    tab.pszText = const_cast<wchar_t*>(T(TXT_GENERAL));
    TabCtrl_InsertItem(hTabs, 0, &tab);
    tab.pszText = const_cast<wchar_t*>(T(TXT_APPEARANCE));
    TabCtrl_InsertItem(hTabs, 1, &tab);
    tab.pszText = const_cast<wchar_t*>(T(TXT_ALARM));
    TabCtrl_InsertItem(hTabs, 2, &tab);
    tab.pszText = const_cast<wchar_t*>(TIME_SIGNAL_TAB_LABELS[appLanguage]);
    TabCtrl_InsertItem(hTabs, 3, &tab);
    tab.pszText = const_cast<wchar_t*>(TIME_TAB_LABELS[appLanguage]);
    TabCtrl_InsertItem(hTabs, 4, &tab);
    tab.pszText = const_cast<wchar_t*>(APPLICATION_TAB_LABELS[appLanguage]);
    TabCtrl_InsertItem(hTabs, 5, &tab);
    RECT pageRect = {
        0,
        0,
        430,
        435
    };
    TabCtrl_AdjustRect(hTabs, FALSE, &pageRect);
    int pageX = 322 + pageRect.left;
    int pageY = 7 + pageRect.top;
    int pageWidth = pageRect.right - pageRect.left;
    int pageHeight = pageRect.bottom - pageRect.top;
    hGeneralPage = CreateWindowExW(WS_EX_CONTROLPARENT, CLASS_NAME, L"", WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
        pageX, pageY, pageWidth, pageHeight, hSettings, nullptr, hInstance, nullptr);
    hAppearancePage = CreateWindowExW(WS_EX_CONTROLPARENT, CLASS_NAME, L"", WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
        pageX, pageY, pageWidth, pageHeight, hSettings, nullptr, hInstance, nullptr);
    hAlarmPage = CreateWindowExW(WS_EX_CONTROLPARENT, CLASS_NAME, L"", WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
        pageX, pageY, pageWidth, pageHeight, hSettings, nullptr, hInstance, nullptr);
    hTimeSignalPage = CreateWindowExW(WS_EX_CONTROLPARENT, CLASS_NAME, L"", WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
        pageX, pageY, pageWidth, pageHeight, hSettings, nullptr, hInstance, nullptr);
    hTimePage = CreateWindowExW(WS_EX_CONTROLPARENT, CLASS_NAME, L"", WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
        pageX, pageY, pageWidth, pageHeight, hSettings, nullptr, hInstance, nullptr);
    hApplicationPage = CreateWindowExW(WS_EX_CONTROLPARENT, CLASS_NAME, L"", WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
        pageX, pageY, pageWidth, pageHeight, hSettings, nullptr, hInstance, nullptr);
    int left = 8;
    int label = 162;
    int field = 244;
    int fieldLeft = left + label + 4;
    AddStatic(hGeneralPage, TXT_NAME, left, 11, 22, &generalControls);
    hNameEdit = AddControl(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_TABSTOP | ES_AUTOHSCROLL,
        fieldLeft, 8, field, 24, hGeneralPage, ID_NAME, &generalControls);
    AddStatic(hGeneralPage, TXT_TYPE, left, 42, 22, &generalControls);
    hTypeCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST,
        fieldLeft, 38, field, 220, hGeneralPage, ID_TYPE, &generalControls);
    for (int type = 0; type < WIDGET_TYPE_COUNT; type++) {
        SendMessageW(hTypeCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(TypeName(static_cast<WidgetType>(type))));
    }
    hVisibleCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_VISIBLE).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX,
        left, 66, 105, 24, hGeneralPage, ID_VISIBLE, &generalControls);
    hTopmostCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_TOPMOST).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX,
        left + 150, 66, 145, 24, hGeneralPage, ID_TOPMOST, &generalControls);
    hSecondsCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_SECONDS).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX,
        left + 300, 66, 110, 24, hGeneralPage, ID_SECONDS, &generalControls);
    hUtcCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_UTC).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX,
        left, 87, 120, 24, hGeneralPage, ID_UTC, &generalControls);
    hUtcTextCheck = AddControl(0, L"BUTTON", UTC_TEXT_LABELS[appLanguage], WS_TABSTOP | BS_AUTOCHECKBOX,
        left + 150, 87, 145, 24, hGeneralPage, ID_UTC_TEXT, &generalControls);
    hSoundsMutedCheck = AddControl(0, L"BUTTON", MUTED_LABELS[appLanguage], WS_TABSTOP | BS_AUTOCHECKBOX,
        left + 300, 87, 110, 24, hGeneralPage, ID_SOUNDS_ENABLED, &generalControls);
    SetCheck(hSoundsMutedCheck, false);
    hTimeZoneLabel = AddStatic(hGeneralPage, TXT_TIMEZONE, left, 118, 22, &generalControls);
    hTimeZoneCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST | WS_VSCROLL,
        fieldLeft, 114, field, 260, hGeneralPage, ID_TIMEZONE, &generalControls);
    FillTimeZoneCombo();
    AddStatic(hGeneralPage, TXT_OFFSET, left, 149, 22, &generalControls);
    hOffsetEdit = AddControl(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_TABSTOP | ES_AUTOHSCROLL,
        fieldLeft, 146, 126, 24, hGeneralPage, ID_OFFSET, &generalControls);
    AddUnderlayStatic(hGeneralPage, WIDGET_LANGUAGE_LABELS[appLanguage], WS_VISIBLE, left, 180, 22, &generalControls);
    hWidgetLanguageCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST,
        fieldLeft, 176, field, 220, hGeneralPage, ID_WIDGET_LANGUAGE, &generalControls);
    PopulateLanguageCombo(hWidgetLanguageCombo);
    hTimeFormatLabel = AddUnderlayStatic(hGeneralPage, TIME_FORMAT_LABELS[appLanguage], WS_VISIBLE, left, 212, 22,
        &generalControls);
    hTimeFormatCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST,
        fieldLeft, 208, 126, 120, hGeneralPage, ID_TIME_FORMAT, &generalControls);
    for (int mode = 0; mode < TIME_FORMAT_COUNT; mode++) {
        SendMessageW(hTimeFormatCombo, CB_ADDSTRING, 0,
            reinterpret_cast<LPARAM>(TIME_FORMAT_MODE_LABELS[appLanguage][mode]));
    }
    hShowAmPmCheck = AddControl(0, L"BUTTON", L"AM/PM", WS_TABSTOP | BS_AUTOCHECKBOX,
        left + 300, 208, 94, 24, hGeneralPage, ID_SHOW_AM_PM, &generalControls);
    for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
        int top = 234 + index * 80;
        std::wstring label = AdditionalClockLabel(appLanguage, index, true);
        hAdditionalEnabledChecks[index] = AddControl(0, L"BUTTON", label.c_str(),
            WS_TABSTOP | WS_CLIPSIBLINGS | BS_AUTOCHECKBOX, left, top, 244, 24, hGeneralPage,
            ID_ADDITIONAL_ENABLED_BASE + index, &generalControls);
        hAdditionalNameLabels[index] = AddStatic(hGeneralPage, TXT_NAME, left, top + 28, 22, &generalControls);
        hAdditionalNameEdits[index] = AddControl(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_TABSTOP | ES_AUTOHSCROLL,
            fieldLeft, top + 24, field, 24, hGeneralPage, ID_ADDITIONAL_NAME_BASE + index, &generalControls);
        std::wstring name = AdditionalClockLabel(appLanguage, index, false);
        SendMessageW(hAdditionalNameEdits[index], EM_SETCUEBANNER, TRUE, reinterpret_cast<LPARAM>(name.c_str()));
        hAdditionalTimeZoneLabels[index] = AddStatic(hGeneralPage, TXT_TIMEZONE, left, top + 58, 22, &generalControls);
        hAdditionalTimeZoneCombos[index] = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST | WS_VSCROLL,
            fieldLeft, top + 54, field, 260, hGeneralPage, ID_ADDITIONAL_TIMEZONE_BASE + index, &generalControls);
        FillTimeZoneCombo(hAdditionalTimeZoneCombos[index]);
    }
    hMonitorLabel = AddUnderlayStatic(hGeneralPage, MONITOR_LABELS[appLanguage], 0, left, 254, 22, &generalControls);
    hMonitorList = AddControl(WS_EX_CLIENTEDGE, L"LISTBOX", L"",
        WS_TABSTOP | LBS_EXTENDEDSEL | LBS_NOINTEGRALHEIGHT | WS_VSCROLL,
        fieldLeft, 250, field, 64, hGeneralPage, ID_MONITOR_LIST, &generalControls);
    hBlackoutMonitorsCheck = AddControl(0, L"BUTTON", BLACKOUT_MONITOR_LABELS[appLanguage],
        WS_TABSTOP | BS_AUTOCHECKBOX, left, 318, 350, 24, hGeneralPage, ID_BLACKOUT_MONITORS, &generalControls);
    hSizeLabel = AddStatic(hAppearancePage, TXT_SIZE, 8, 12, 22, &appearanceControls);
    hSizeCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST,
        148, 8, 87, 180, hAppearancePage, ID_SIZE, &appearanceControls);
    int sizes[4] = {};
    int sizeCount = GetAnalogClockSizes(sizes);
    for (int index = 0; index < sizeCount; index++) {
        std::wstring sizeLabel = std::to_wstring(sizes[index]) + L" px";
        SendMessageW(hSizeCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(sizeLabel.c_str()));
    }
    for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
        hAdditionalSizeCombos[index] = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST,
            239 + index * 91, 8, 87, 180, hAppearancePage, ID_ADDITIONAL_SIZE_BASE + index, &appearanceControls);
        for (int item = 0; item < sizeCount; item++) {
            std::wstring label = std::to_wstring(sizes[item]) + L" px";
            SendMessageW(hAdditionalSizeCombos[index], CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(label.c_str()));
        }
    }
    hOpacityLabel = AddStatic(hAppearancePage, TXT_OPACITY, 8, 11, 22, &appearanceControls);
    hOpacityTrackBar = AddControl(0, TRACKBAR_CLASSW, L"", WS_TABSTOP | TBS_HORZ | TBS_AUTOTICKS,
        121, 4, 250, 32, hAppearancePage, ID_OPACITY, &appearanceControls);
    SendMessageW(hOpacityTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(WIDGET_OPACITY_MIN, WIDGET_OPACITY_MAX));
    SendMessageW(hOpacityTrackBar, TBM_SETTICFREQ, 5, 0);
    SendMessageW(hOpacityTrackBar, TBM_SETLINESIZE, 0, 1);
    SendMessageW(hOpacityTrackBar, TBM_SETPAGESIZE, 0, 5);
    hOpacityValue = CreateWindowExW(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_RIGHT,
        368, 11, 48, 22, hAppearancePage, nullptr, hInstance, nullptr);
    appearanceControls.push_back(hOpacityValue);
    hFontSizeLabel = AddStatic(hAppearancePage, TXT_FONT_SIZE, 8, 45, 22, &appearanceControls);
    hFontSizeTrackBar = AddControl(0, TRACKBAR_CLASSW, L"", WS_TABSTOP | TBS_HORZ | TBS_AUTOTICKS,
        121, 38, 250, 32, hAppearancePage, ID_FONT_SIZE, &appearanceControls);
    SendMessageW(hFontSizeTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(DIGITAL_FONT_SIZE_MIN, DIGITAL_FONT_SIZE_MAX));
    SendMessageW(hFontSizeTrackBar, TBM_SETTICFREQ, 5, 0);
    SendMessageW(hFontSizeTrackBar, TBM_SETLINESIZE, 0, 1);
    SendMessageW(hFontSizeTrackBar, TBM_SETPAGESIZE, 0, 5);
    hFontSizeValue = CreateWindowExW(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_RIGHT,
        368, 45, 48, 22, hAppearancePage, nullptr, hInstance, nullptr);
    appearanceControls.push_back(hFontSizeValue);
    hFontButton = AddControl(0, L"BUTTON", FONT_BUTTON_LABELS[appLanguage], WS_TABSTOP,
        52, 70, 178, 27, hAppearancePage, ID_FONT, &appearanceControls);
    hPanelTopFontButton = AddControl(0, L"BUTTON", PANEL_TOP_FONT_LABELS[appLanguage], WS_TABSTOP,
        52, 76, 178, 27, hAppearancePage, ID_PANEL_TOP_FONT, &appearanceControls);
    hPanelTimeFontButton = AddControl(0, L"BUTTON", PANEL_TIME_FONT_LABELS[appLanguage], WS_TABSTOP,
        238, 76, 178, 27, hAppearancePage, ID_PANEL_TIME_FONT, &appearanceControls);
    hPanelBottomFontButton = AddControl(0, L"BUTTON", PANEL_BOTTOM_FONT_LABELS[appLanguage], WS_TABSTOP,
        52, 106, 178, 27, hAppearancePage, ID_PANEL_BOTTOM_FONT, &appearanceControls);
    hTextColorButton = AddControl(0, L"BUTTON", Mnemonic(TXT_TEXT_COLOR).c_str(), WS_TABSTOP,
        52, 100, 178, 27, hAppearancePage, ID_TEXT_COLOR, &appearanceControls);
    hBackgroundColorButton = AddControl(0, L"BUTTON", Mnemonic(TXT_BACKGROUND_COLOR).c_str(), WS_TABSTOP,
        238, 100, 178, 27, hAppearancePage, ID_BACKGROUND_COLOR, &appearanceControls);
    hAlarmTextColorButton = AddControl(0, L"BUTTON", ALARM_TEXT_COLOR_LABELS[appLanguage], WS_TABSTOP,
        52, 130, 178, 27, hAppearancePage, ID_ALARM_TEXT_COLOR, &appearanceControls);
    hAlarmBackgroundColorButton = AddControl(0, L"BUTTON", ALARM_BACKGROUND_COLOR_LABELS[appLanguage], WS_TABSTOP,
        238, 130, 178, 27, hAppearancePage, ID_ALARM_BACKGROUND_COLOR, &appearanceControls);
    hPaddingLabel = AddUnderlayStatic(hAppearancePage, PADDING_LABELS[appLanguage], WS_VISIBLE,
        8, 169, 22, &appearanceControls);
    hPaddingTrackBar = AddControl(0, TRACKBAR_CLASSW, L"", WS_TABSTOP | TBS_HORZ | TBS_AUTOTICKS,
        121, 162, 250, 32, hAppearancePage, ID_PADDING, &appearanceControls);
    SendMessageW(hPaddingTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(0, DIGITAL_PADDING_MAX));
    SendMessageW(hPaddingTrackBar, TBM_SETTICFREQ, 5, 0);
    SendMessageW(hPaddingTrackBar, TBM_SETLINESIZE, 0, 1);
    SendMessageW(hPaddingTrackBar, TBM_SETPAGESIZE, 0, 5);
    hPaddingValue = CreateWindowExW(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_RIGHT,
        368, 169, 48, 22, hAppearancePage, nullptr, hInstance, nullptr);
    appearanceControls.push_back(hPaddingValue);
    hBorderWidthLabel = AddUnderlayStatic(hAppearancePage, BORDER_WIDTH_LABELS[appLanguage], WS_VISIBLE,
        8, 201, 22, &appearanceControls);
    hBorderWidthTrackBar = AddControl(0, TRACKBAR_CLASSW, L"", WS_TABSTOP | TBS_HORZ | TBS_AUTOTICKS,
        121, 194, 250, 32, hAppearancePage, ID_BORDER_WIDTH, &appearanceControls);
    SendMessageW(hBorderWidthTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(0, DIGITAL_BORDER_WIDTH_MAX));
    SendMessageW(hBorderWidthTrackBar, TBM_SETTICFREQ, 1, 0);
    SendMessageW(hBorderWidthTrackBar, TBM_SETLINESIZE, 0, 1);
    SendMessageW(hBorderWidthTrackBar, TBM_SETPAGESIZE, 0, 1);
    hBorderWidthValue = CreateWindowExW(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_RIGHT,
        368, 201, 48, 22, hAppearancePage, nullptr, hInstance, nullptr);
    appearanceControls.push_back(hBorderWidthValue);
    hBorderLabel = AddUnderlayStatic(hAppearancePage, BORDER_LABELS[appLanguage], WS_VISIBLE,
        8, 233, 22, &appearanceControls);
    hBorderTrackBar = AddControl(0, TRACKBAR_CLASSW, L"", WS_TABSTOP | TBS_HORZ | TBS_AUTOTICKS,
        121, 226, 111, 32, hAppearancePage, ID_BORDER, &appearanceControls);
    SendMessageW(hBorderTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(0, 3));
    SendMessageW(hBorderTrackBar, TBM_SETTICFREQ, 1, 0);
    SendMessageW(hBorderTrackBar, TBM_SETLINESIZE, 0, 1);
    SendMessageW(hBorderTrackBar, TBM_SETPAGESIZE, 0, 1);
    hBorderColorButton = AddControl(0, L"BUTTON", BORDER_COLOR_LABELS[appLanguage], WS_TABSTOP,
        238, 228, 178, 27, hAppearancePage, ID_BORDER_COLOR, &appearanceControls);
    hLeadingZeroLabel = AddUnderlayStatic(hAppearancePage, T(TXT_LEADING_ZERO), WS_VISIBLE,
        8, 262, 22, &appearanceControls);
    hLeadingZeroCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST,
        148, 258, 87, 120, hAppearancePage, ID_LEADING_ZERO, &appearanceControls);
    for (int mode = 0; mode < LEADING_ZERO_MODE_COUNT; mode++) {
        SendMessageW(hLeadingZeroCombo, CB_ADDSTRING, 0,
            reinterpret_cast<LPARAM>(LEADING_ZERO_MODE_LABELS[appLanguage][mode]));
    }
    hTransparentBackgroundCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_TRANSPARENT_BG).c_str(),
        WS_TABSTOP | BS_AUTOCHECKBOX,
        242, 258, 174, 24, hAppearancePage, ID_TRANSPARENT_BG, &appearanceControls);
    hWeekNumbersCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_WEEK_NUMBERS).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX,
        8, 110, 150, 24, hAppearancePage, ID_WEEK_NUMBERS, &appearanceControls);
    hSundayFirstCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_SUNDAY_FIRST).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX,
        8, 140, 205, 24, hAppearancePage, ID_SUNDAY_FIRST, &appearanceControls);
    hShowTodayCheck = AddControl(0, L"BUTTON", SHOW_TODAY_LABELS[appLanguage], WS_TABSTOP | BS_AUTOCHECKBOX,
        8, 170, 364, 24, hAppearancePage, ID_SHOW_TODAY, &appearanceControls);
    hDateFormatLabel = AddUnderlayStatic(hAppearancePage, DATE_FORMAT_LABELS[appLanguage], WS_VISIBLE,
        8, 110, 22, &appearanceControls);
    hDateFormatCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST | WS_VSCROLL,
        191, 106, 225, 240, hAppearancePage, ID_DATE_FORMAT, &appearanceControls);
    hWidgetAntialiasLabel = AddUnderlayStatic(hAppearancePage, ANTIALIASING_LABELS[appLanguage], WS_VISIBLE,
        8, 296, 22, &appearanceControls);
    hWidgetAntialiasCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST,
        148, 292, 87, 100, hAppearancePage, ID_WIDGET_ANTIALIAS, &appearanceControls);
    PopulateFontAntialiasingCombo(hWidgetAntialiasCombo);
    hWidgetDisableThemesCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_VISUAL_STYLES).c_str(),
        WS_TABSTOP | BS_AUTOCHECKBOX, 243, 292, 130, 24, hAppearancePage, ID_WIDGET_DISABLE_THEMES, &appearanceControls);
    hDefaultAppearanceButton = AddControl(0, L"BUTTON", DEFAULT_APPEARANCE_LABELS[appLanguage], WS_TABSTOP,
        238, 318, 178, 27, hAppearancePage, ID_DEFAULT_APPEARANCE, &appearanceControls);
    int y = 12;
    hAlarmEnabledCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_ALARM_ACTIVE).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX,
        left, y, 175, 24, hAlarmPage, ID_ALARM_ENABLED, &alarmControls);
    y += 28;
    int firstAlarmDay = GetCultureFirstAlarmDay(appLanguage);
    for (int position = 0; position < ALARM_DAY_COUNT; position++) {
        int day = (firstAlarmDay + position) % ALARM_DAY_COUNT;
        std::wstring dayLabel = GetWeekdayAbbreviation(appLanguage, day);
        hAlarmDayChecks[day] = AddControl(0, L"BUTTON", dayLabel.c_str(), WS_TABSTOP | BS_AUTOCHECKBOX,
            left + position * 52, y, 50, 24, hAlarmPage, ID_ALARM_DAY_BASE + day, &alarmControls);
    }
    y += 32;
    std::wstring alarmTimeLabel = Mnemonic(TXT_ALARM_TIME);
    AddUnderlayStatic(hAlarmPage, alarmTimeLabel.c_str(), WS_VISIBLE, left, y - 1, 22, &alarmControls);
    hAlarmTimeEdit = AddControl(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_TABSTOP | ES_AUTOHSCROLL,
        left + 154, y - 4, 100, 24, hAlarmPage, ID_ALARM_TIME, &alarmControls);
    y += 36;
    hRunCommandCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_RUN_FILE).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX,
        left, y, 290, 24, hAlarmPage, ID_RUN_COMMAND, &alarmControls);
    y += 30;
    hCommandEdit = AddControl(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_TABSTOP | ES_AUTOHSCROLL, left, y, 275, 24,
        hAlarmPage, ID_COMMAND, &alarmControls);
    hBrowseButton = AddControl(0, L"BUTTON", Mnemonic(TXT_BROWSE).c_str(), WS_TABSTOP, left + 282, y - 3, 88, 27,
        hAlarmPage, ID_BROWSE, &alarmControls);
    y += 32;
    hTestCommandButton = AddControl(0, L"BUTTON", TEST_COMMAND_LABELS[appLanguage], WS_TABSTOP,
        left, y - 2, 102, 27, hAlarmPage, ID_TEST_COMMAND, &alarmControls);
    hLoopAudioCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_LOOP_AUDIO).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX,
        left + 110, y, 260, 24, hAlarmPage, ID_LOOP_AUDIO, &alarmControls);
    y += 34;
    hAlarmVolumeLabel = AddUnderlayStatic(hAlarmPage, ALARM_VOLUME_LABELS[appLanguage], WS_VISIBLE,
        left, y + 7, 22, &alarmControls);
    hAlarmVolumeTrackBar = AddControl(0, TRACKBAR_CLASSW, L"", WS_TABSTOP | TBS_HORZ, 174, y, 174, 32,
        hAlarmPage, ID_ALARM_VOLUME, &alarmControls);
    SendMessageW(hAlarmVolumeTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(TIME_SIGNAL_VOLUME_SLIDER_MIN,
        TIME_SIGNAL_VOLUME_SLIDER_MAX));
    for (int decibels = -54; decibels < 0; decibels += 6) {
        SendMessageW(hAlarmVolumeTrackBar, TBM_SETTIC, 0, AlarmVolumeSliderPosition(decibels * 100));
    }
    SendMessageW(hAlarmVolumeTrackBar, TBM_SETLINESIZE, 0, 10);
    SendMessageW(hAlarmVolumeTrackBar, TBM_SETPAGESIZE, 0, 100);
    hAlarmVolumeValue = AddControl(0, L"STATIC", L"", SS_RIGHT, 352, y + 7, 66, 22, hAlarmPage, 0, &alarmControls);
    y += 36;
    hRemoteScriptCheck = AddControl(0, L"BUTTON", REMOTE_SCRIPT_LABELS[appLanguage], WS_TABSTOP | BS_AUTOCHECKBOX,
        left, y, 300, 24, hAlarmPage, ID_REMOTE_SCRIPT, &alarmControls);
    y += 30;
    hRemoteScriptLabel = AddUnderlayStatic(hAlarmPage, REMOTE_SCRIPT_URL_LABELS[appLanguage], WS_VISIBLE,
        left, y + 3, 22, &alarmControls);
    hRemoteScriptEdit = AddControl(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_TABSTOP | ES_AUTOHSCROLL,
        left + 96, y, 274, 24, hAlarmPage, ID_REMOTE_SCRIPT_URL, &alarmControls);
    y += 34;
    hAlarmTimeSignalCheck = AddControl(0, L"BUTTON", ALARM_TIME_SIGNAL_LABELS[appLanguage],
        WS_TABSTOP | BS_AUTOCHECKBOX,
        left, y, 360, 24, hAlarmPage, ID_ALARM_TIME_SIGNAL, &alarmControls);
    AddUnderlayStatic(hTimeSignalPage, TIME_SIGNAL_FIELD_LABELS[appLanguage], WS_VISIBLE,
        left, 16, 22, &timeSignalControls);
    hTimeSignalCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST,
        fieldLeft + 50, 12, field - 50, 220, hTimeSignalPage, ID_TIME_SIGNAL, &timeSignalControls);
    for (int mode = 0; mode < TIME_SIGNAL_COUNT; mode++) {
        SendMessageW(hTimeSignalCombo, CB_ADDSTRING, 0,
            reinterpret_cast<LPARAM>(TIME_SIGNAL_MODE_LABELS[appLanguage][mode]));
    }
    HWND timeSignalNote = AddControl(0, L"STATIC", TIME_SIGNAL_NOTE[appLanguage], SS_OWNERDRAW,
        left, 56, 364, pageHeight - 64, hTimeSignalPage, ID_TIME_SIGNAL_NOTE);
    timeSignalControls.push_back(timeSignalNote);
    AddUnderlayStatic(hTimePage, TIME_SOURCE_LABELS[appLanguage], WS_VISIBLE, 8, 16, 22, &timeControls);
    hTimeSourceCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST,
        132, 12, 240, 180, hTimePage, ID_TIME_SOURCE, &timeControls);
    SendMessageW(hTimeSourceCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(SYSTEM_TIME_LABELS[appLanguage]));
    SendMessageW(hTimeSourceCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(NTP_TIME_LABELS[appLanguage]));
    SendMessageW(hTimeSourceCombo, CB_SETCURSEL, useNtpTime ? 1 : 0, 0);
    hNtpPresetLabel = AddUnderlayStatic(hTimePage, NTP_PRESET_FIELD_LABELS[appLanguage], WS_VISIBLE,
        8, 50, 22, &timeControls);
    hNtpPresetCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST,
        132, 46, 240, 220, hTimePage, ID_NTP_PRESET, &timeControls);
    for (int preset = 0; preset < NTP_PRESET_COUNT; preset++) {
        SendMessageW(hNtpPresetCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(NTP_PRESET_LABELS[appLanguage][preset]));
    }
    SendMessageW(hNtpPresetCombo, CB_SETCURSEL, ntpPreset, 0);
    hNtpServersLabel = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", NTP_SERVERS_LABELS[appLanguage],
        WS_CHILD | WS_VISIBLE,
        8, 82, 364, 22, hTimePage, nullptr, hInstance, nullptr);
    timeControls.push_back(hNtpServersLabel);
    hNtpServersEdit = AddControl(WS_EX_CLIENTEDGE, L"EDIT", ntpServers.c_str(), WS_TABSTOP | ES_AUTOHSCROLL,
        8, 106, 364, 24, hTimePage, ID_NTP_SERVERS, &timeControls);
    hNtpSyncButton = AddControl(0, L"BUTTON", NTP_SYNC_LABELS[appLanguage], WS_TABSTOP,
        8, 140, 180, 27, hTimePage, ID_NTP_SYNC, &timeControls);
    hNtpStatus = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT,
        8, 178, 364, 66, hTimePage, nullptr, hInstance, nullptr);
    timeControls.push_back(hNtpStatus);
    HWND timeGlobalNote = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", TIME_GLOBAL_NOTE[appLanguage],
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        8, 264, 364, 42, hTimePage, nullptr, hInstance, nullptr);
    timeControls.push_back(timeGlobalNote);
    UpdateNtpSettingsControls();
    hAppFontLabel = AddUnderlayStatic(hApplicationPage, APPLICATION_FONT_LABELS[appLanguage], WS_VISIBLE,
        8, 18, 22, &applicationControls);
    hAppFontButton = AddControl(0, L"BUTTON", L"", WS_TABSTOP, 174, 12, 154, 27, hApplicationPage,
        ID_APP_FONT, &applicationControls);
    hAppFontDefaultButton = AddControl(0, L"BUTTON", DEFAULT_FONT_LABELS[appLanguage], WS_TABSTOP,
        334, 12, 84, 27, hApplicationPage, ID_APP_FONT_DEFAULT, &applicationControls);
    UpdateApplicationFontButtons();
    AddUnderlayStatic(hApplicationPage, ANTIALIASING_LABELS[appLanguage], WS_VISIBLE,
        8, 50, 22, &applicationControls);
    hAppAntialiasCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST,
        174, 46, 244, 100, hApplicationPage, ID_APP_ANTIALIAS, &applicationControls);
    PopulateFontAntialiasingCombo(hAppAntialiasCombo);
    SelectFontAntialiasing(hAppAntialiasCombo, appFontAntialiasing);
    AddUnderlayStatic(hApplicationPage, APPLICATION_LANGUAGE_LABELS[appLanguage], WS_VISIBLE,
        8, 84, 22, &applicationControls);
    hLanguageCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST,
        174, 80, 244, 220, hApplicationPage, ID_LANGUAGE, &applicationControls);
    PopulateLanguageCombo(hLanguageCombo);
    SendMessageW(hLanguageCombo, CB_SETCURSEL, ComboIndexForLanguage(appLanguage), 0);
    HWND timeSignalSoundLabel = AddUnderlayStatic(hApplicationPage, TIME_SIGNAL_SOUND_LABELS[appLanguage],
        WS_VISIBLE, 8, 118, 22, &applicationControls);
    hTimeSignalSoundCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST,
        174, 114, 136, 100, hApplicationPage, ID_TIME_SIGNAL_SOUND, &applicationControls);
    SendMessageW(hTimeSignalSoundCombo, CB_ADDSTRING, 0,
        reinterpret_cast<LPARAM>(TIME_SIGNAL_GENERATED_SOUND_LABELS[appLanguage]));
    SendMessageW(hTimeSignalSoundCombo, CB_ADDSTRING, 0,
        reinterpret_cast<LPARAM>(TIME_SIGNAL_SYSTEM_SOUND_LABELS[appLanguage]));
    bool generatorRequired = IsTimeSignalGeneratorRequired();
    SendMessageW(hTimeSignalSoundCombo, CB_SETCURSEL, generatorRequired || generatedTimeSignal ? 0 : 1, 0);
    EnableWindow(hTimeSignalSoundCombo, !generatorRequired);
    EnableWindow(timeSignalSoundLabel, !generatorRequired);
    settingsTimeSignalTestActive = false;
    hTimeSignalTestButton = AddControl(0, L"BUTTON", TEST_COMMAND_LABELS[appLanguage], WS_TABSTOP,
        316, 114, 102, 27, hApplicationPage, ID_TIME_SIGNAL_TEST, &applicationControls);
    hTimeSignalVolumeLabel = AddUnderlayStatic(hApplicationPage, TIME_SIGNAL_VOLUME_LABELS[appLanguage], WS_VISIBLE,
        8, 151, 22, &applicationControls);
    hTimeSignalVolumeTrackBar = AddControl(0, TRACKBAR_CLASSW, L"", WS_TABSTOP | TBS_HORZ,
        174, 144, 174, 32, hApplicationPage, ID_TIME_SIGNAL_VOLUME, &applicationControls);
    SendMessageW(hTimeSignalVolumeTrackBar, TBM_SETRANGE, TRUE,
        MAKELPARAM(TIME_SIGNAL_VOLUME_SLIDER_MIN, TIME_SIGNAL_VOLUME_SLIDER_MAX));
    for (int decibels = -54; decibels < 0; decibels += 6) {
        SendMessageW(hTimeSignalVolumeTrackBar, TBM_SETTIC, 0,
            TimeSignalVolumeSliderPosition(TimeSignalVolumeFromDecibels(decibels)));
    }
    SendMessageW(hTimeSignalVolumeTrackBar, TBM_SETLINESIZE, 0, 10);
    SendMessageW(hTimeSignalVolumeTrackBar, TBM_SETPAGESIZE, 0, 100);
    SendMessageW(hTimeSignalVolumeTrackBar, TBM_SETPOS, TRUE, TimeSignalVolumeSliderPosition(timeSignalVolume));
    SetWindowSubclass(hTimeSignalVolumeTrackBar, TimeSignalVolumeSubclassProc, ID_TIME_SIGNAL_VOLUME, 0);
    hTimeSignalVolumeValue = AddControl(0, L"STATIC", L"", SS_RIGHT, 352, 151, 66, 22, hApplicationPage, 0,
        &applicationControls);
    UpdateTimeSignalVolumeControls();
    hDisableThemesCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_VISUAL_STYLES).c_str(),
        WS_TABSTOP | BS_AUTOCHECKBOX, 8, 184, 240, 24, hApplicationPage, ID_VISUAL_STYLES, &applicationControls);
    SetCheck(hDisableThemesCheck, themesDisabled);
    hStartWithWindowsCheck = AddControl(0, L"BUTTON", START_WITH_WINDOWS_LABELS[appLanguage],
        WS_TABSTOP | BS_AUTOCHECKBOX, 8, 214, 300, 24, hApplicationPage, ID_START_WITH_WINDOWS, &applicationControls);
    SetCheck(hStartWithWindowsCheck, startWithWindows);
    hUseXmlSettingsCheck = AddControl(0, L"BUTTON", XML_STORAGE_LABELS[appLanguage], WS_TABSTOP | BS_AUTOCHECKBOX,
        8, 244, 240, 24, hApplicationPage, ID_USE_XML_SETTINGS, &applicationControls);
    SetCheck(hUseXmlSettingsCheck, storageUsesXml);
    hSnapToWorkAreaCheck = AddControl(0, L"BUTTON", SNAP_TO_WORK_AREA_LABELS[appLanguage], WS_TABSTOP | BS_AUTOCHECKBOX,
        8, 274, 400, 24, hApplicationPage, ID_SNAP_TO_WORK_AREA, &applicationControls);
    SetCheck(hSnapToWorkAreaCheck, snapWidgetsToWorkArea);
    AddControl(0, L"BUTTON", IMPORT_SETTINGS_LABELS[appLanguage], WS_TABSTOP, 10, 450, 148, 27, hSettings,
        ID_IMPORT_SETTINGS);
    AddControl(0, L"BUTTON", EXPORT_SETTINGS_LABELS[appLanguage], WS_TABSTOP, 164, 450, 148, 27, hSettings,
        ID_EXPORT_SETTINGS);
    AddControl(0, L"BUTTON", Mnemonic(TXT_SAVE).c_str(), WS_TABSTOP | BS_DEFPUSHBUTTON, 482, 450, 84, 27, hSettings,
        ID_SAVE);
    AddControl(0, L"BUTTON", Mnemonic(TXT_CANCEL).c_str(), WS_TABSTOP, 570, 450, 84, 27, hSettings, ID_CANCEL);
    AddControl(0, L"BUTTON", Mnemonic(TXT_APPLY).c_str(), WS_TABSTOP | WS_DISABLED, 658, 450, 84, 27, hSettings,
        ID_APPLY);
    ScaleSettingsChildren(hSettings);
    ScaleSettingsChildren(hGeneralPage);
    ScaleSettingsChildren(hAppearancePage);
    ScaleSettingsChildren(hAlarmPage);
    ScaleSettingsChildren(hTimeSignalPage);
    ScaleSettingsChildren(hTimePage);
    ScaleSettingsChildren(hApplicationPage);
    UpdateSettingsTextControlLayout(hSettings);
    for (int tab = 0; tab < SETTINGS_TAB_COUNT; tab++) {
        UpdateSettingsTextControlLayout(GetSettingsPage(tab));
    }
    InitializeSettingsScrollBars();
    ApplyUiStyle(hSettings);
    updatingSettingsControls = previousUpdating;
}

/// Stops previews and rebuilds settings controls with redraw suspended, then restores the selected tab and draft
/// values.
static void RebuildSettingsControls() {
    WindowRedrawScope redraw(hSettings);
    timeSignalVolumeDragging = false;
    settingsTimeSignalTestActive = false;
    StopTimeSignalVolumePreview();
    if (hSettings == nullptr || !IsWindow(hSettings)) {
        return;
    }
    StopSettingsPreview();
    int selectedTab = hTabs == nullptr ? 0 : TabCtrl_GetCurSel(hTabs);
    settingsTab = std::clamp(selectedTab, 0, SETTINGS_TAB_COUNT - 1);
    HWND child = GetWindow(hSettings, GW_CHILD);
    while (child != nullptr) {
        HWND next = GetWindow(child, GW_HWNDNEXT);
        DestroyWindow(child);
        child = next;
    }
    hWidgetList = nullptr;
    hTabs = nullptr;
    hGeneralPage = nullptr;
    hAppearancePage = nullptr;
    hAlarmPage = nullptr;
    hTimeSignalPage = nullptr;
    hTimePage = nullptr;
    hApplicationPage = nullptr;
    hUtcTextCheck = nullptr;
    hShowAmPmCheck = nullptr;
    hTimeFormatCombo = nullptr;
    hTimeFormatLabel = nullptr;
    hTimeZoneLabel = nullptr;
    hMonitorLabel = nullptr;
    hMonitorList = nullptr;
    hBlackoutMonitorsCheck = nullptr;
    for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
        hAdditionalEnabledChecks[index] = nullptr;
        hAdditionalNameLabels[index] = nullptr;
        hAdditionalNameEdits[index] = nullptr;
        hAdditionalTimeZoneLabels[index] = nullptr;
        hAdditionalTimeZoneCombos[index] = nullptr;
        hAdditionalSizeCombos[index] = nullptr;
    }
    hWidgetAntialiasLabel = nullptr;
    hWidgetAntialiasCombo = nullptr;
    hAppAntialiasCombo = nullptr;
    hLanguageCombo = nullptr;
    hDisableThemesCheck = nullptr;
    hUseXmlSettingsCheck = nullptr;
    hSnapToWorkAreaCheck = nullptr;
    hTimeSignalSoundCombo = nullptr;
    hTimeSignalTestButton = nullptr;
    hTimeSignalVolumeLabel = nullptr;
    hTimeSignalVolumeTrackBar = nullptr;
    hTimeSignalVolumeValue = nullptr;
    hAppFontLabel = nullptr;
    hAppFontButton = nullptr;
    hAppFontDefaultButton = nullptr;
    hRemoteScriptCheck = nullptr;
    hRemoteScriptLabel = nullptr;
    hRemoteScriptEdit = nullptr;
    hAlarmTimeSignalCheck = nullptr;
    hAlarmVolumeLabel = nullptr;
    hAlarmVolumeTrackBar = nullptr;
    hAlarmVolumeValue = nullptr;
    hTimeSignalCombo = nullptr;
    hStartWithWindowsCheck = nullptr;
    hSoundsMutedCheck = nullptr;
    hBorderColorButton = nullptr;
    for (int day = 0; day < ALARM_DAY_COUNT; day++) {
        hAlarmDayChecks[day] = nullptr;
    }
    SetWindowTextW(hSettings, T(TXT_SETTINGS));
    CreateSettingsControls();
    RefreshWidgetList(true, false);
    LoadDraftIntoControls();
    if (hTabs == nullptr) {
        return;
    }
    TabCtrl_SetCurSel(hTabs, std::clamp(selectedTab, 0, SETTINGS_TAB_COUNT - 1));
    ShowSettingsTab(TabCtrl_GetCurSel(hTabs));
    SetFocus(hAddType);
}

/// Stops tests, restores uncommitted previews, remembers the form position and selected tab, and destroys settings
/// controls.
/// Clears draft state and restores normal fullscreen presentation.
static void CloseSettingsWindow() {
    timeSignalVolumeDragging = false;
    settingsTimeSignalTestActive = false;
    StopTimeSignalVolumePreview();
    RestoreSettingsAppearancePreview();
    RestoreApplicationFontPreview();
    StopSettingsPreview();
    if (hSettings != nullptr && IsWindow(hSettings)) {
        if (hTabs != nullptr) {
            settingsTab = std::clamp(TabCtrl_GetCurSel(hTabs), 0, SETTINGS_TAB_COUNT - 1);
        }
        SaveFormPosition(hSettings, &settingsX, &settingsY);
        DestroyWindow(hSettings);
        SaveAllSettings();
    }
    hSettings = nullptr;
    hWidgetList = nullptr;
    hTabs = nullptr;
    hGeneralPage = nullptr;
    hAppearancePage = nullptr;
    hAlarmPage = nullptr;
    hTimeSignalPage = nullptr;
    hTimePage = nullptr;
    hApplicationPage = nullptr;
    hTimeFormatLabel = nullptr;
    hTimeZoneLabel = nullptr;
    hWidgetAntialiasLabel = nullptr;
    hWidgetAntialiasCombo = nullptr;
    hAppAntialiasCombo = nullptr;
    hLanguageCombo = nullptr;
    hDisableThemesCheck = nullptr;
    hUseXmlSettingsCheck = nullptr;
    hSnapToWorkAreaCheck = nullptr;
    hTimeSignalSoundCombo = nullptr;
    hTimeSignalTestButton = nullptr;
    hTimeSignalVolumeLabel = nullptr;
    hTimeSignalVolumeTrackBar = nullptr;
    hTimeSignalVolumeValue = nullptr;
    hAppFontLabel = nullptr;
    hAppFontButton = nullptr;
    hAppFontDefaultButton = nullptr;
    hRemoteScriptCheck = nullptr;
    hRemoteScriptLabel = nullptr;
    hRemoteScriptEdit = nullptr;
    hAlarmTimeSignalCheck = nullptr;
    hAlarmVolumeLabel = nullptr;
    hAlarmVolumeTrackBar = nullptr;
    hAlarmVolumeValue = nullptr;
    hTimeSignalCombo = nullptr;
    hStartWithWindowsCheck = nullptr;
    hSoundsMutedCheck = nullptr;
    hBorderColorButton = nullptr;
    for (int day = 0; day < ALARM_DAY_COUNT; day++) {
        hAlarmDayChecks[day] = nullptr;
    }
    hTimeSourceCombo = nullptr;
    hNtpPresetLabel = nullptr;
    hNtpPresetCombo = nullptr;
    hNtpServersLabel = nullptr;
    hNtpServersEdit = nullptr;
    hNtpStatus = nullptr;
    hNtpSyncButton = nullptr;
    settingsDraft.clear();
    settingsAppliedWidgets.clear();
    settingsAppearanceOriginals.clear();
    settingsAppearancePreviewIds.clear();
    settingsAppearancePreviewActive = false;
    settingsApplicationFontPreviewActive = false;
    RefreshFullscreenPresentation();
}

/// Shows an XML open or save dialog without changing the current directory and returns the accepted path.
static bool ChooseSettingsXmlFile(bool save, std::wstring* path) {
    if (path == nullptr) {
        return false;
    }
    wchar_t file[MAX_PATH] = L"CalClock-settings.xml";
    const wchar_t filter[] = L"CalClock XML (*.xml)\0*.xml\0XML (*.xml)\0*.xml\0\0";
    OPENFILENAMEW dialog = {};
    dialog.lStructSize = sizeof(dialog);
    dialog.hwndOwner = hSettings;
    dialog.lpstrFilter = filter;
    dialog.lpstrFile = file;
    dialog.nMaxFile = ARRAYSIZE(file);
    dialog.lpstrDefExt = L"xml";
    dialog.Flags = OFN_EXPLORER | OFN_NOCHANGEDIR | OFN_PATHMUSTEXIST | (save ? OFN_OVERWRITEPROMPT : OFN_FILEMUSTEXIST);
    BOOL selected = save ? GetSaveFileNameW(&dialog) : GetOpenFileNameW(&dialog);
    if (!selected) {
        return false;
    }
    *path = file;
    return true;
}

/// Validates and applies the current draft before exporting a settings snapshot to the chosen XML file, reporting write
/// failure.
static void ExportSettings() {
    std::wstring path;
    if (!ChooseSettingsXmlFile(true, &path)) {
        return;
    }
    if (!SaveControlsToDraft(true)) {
        return;
    }
    ApplySettingsDraft();
    if (!WriteSettingsXml(path, CaptureSettingsSnapshot())) {
        MessageBoxW(hSettings, SETTINGS_EXPORT_FAILED[appLanguage], T(TXT_SETTINGS), MB_OK | MB_ICONERROR);
    }
}

/// Validates a chosen XML snapshot, replaces application and widget settings, rebuilds affected windows, and saves
/// using the selected backend.
static void ImportSettings() {
    std::wstring path;
    if (!ChooseSettingsXmlFile(false, &path)) {
        return;
    }
    SettingsSnapshot snapshot = {};
    if (!ReadSettingsXml(path, appLanguage, CreateStoredWidgetDefaults, &snapshot)) {
        MessageBoxW(hSettings, INVALID_SETTINGS_FILE[appLanguage], T(TXT_SETTINGS), MB_OK | MB_ICONWARNING);
        return;
    }
    bool useXmlStorage = GetCheck(hUseXmlSettingsCheck);
    bool previousThemesDisabled = themesDisabled;
    CloseSettingsWindow();
    DestroyWidgetWindows();
    ApplySettingsSnapshot(snapshot);
    storageUsesXml = useXmlStorage;
    ResetUiFont();
    if (previousThemesDisabled != themesDisabled) {
        SetThemeAppProperties(themesDisabled
            ? STAP_ALLOW_NONCLIENT
            : STAP_ALLOW_NONCLIENT | STAP_ALLOW_CONTROLS | STAP_ALLOW_WEBCONTENT);
    }
    for (size_t index = 0; index < widgets.size(); index++) {
        CreateWidgetWindow(widgets[index].get());
    }
    RefreshFullscreenPresentation();
    RefreshInformationWindows();
    if (hHelp != nullptr) {
        ApplyUiStyle(hHelp);
    }
    if (hAbout != nullptr) {
        ApplyUiStyle(hAbout);
    }
    UpdateTrayIcon();
    SaveAllSettings();
    if (useNtpTime) {
        StartNtpSynchronization(true);
    }
    ShowSettingsWindow();
}

/// Opens or activates the non-topmost settings form and optionally selects a widget by ID.
/// Creates draft snapshots and fullscreen previews when opening a new form.
static void ShowSettingsWindow(int widgetId) {
    if (hSettings != nullptr && IsWindow(hSettings)) {
        if (!IsWindowEnabled(hSettings)) {
            HWND dialog = GetLastActivePopup(hSettings);
            if (dialog != hSettings && IsWindow(dialog)) {
                SetForegroundWindow(dialog);
            }
            return;
        }
        SelectDraftWidgetById(widgetId);
        SetForegroundWindowEx(hSettings);
        return;
    }
    settingsDraft.clear();
    for (size_t index = 0; index < widgets.size(); index++) {
        settingsDraft.push_back(widgets[index]->config);
    }
    settingsAppearanceOriginals = settingsDraft;
    settingsAppliedWidgets = settingsDraft;
    settingsAppearancePreviewIds.clear();
    settingsAppearancePreviewActive = false;
    settingsAppFontFace = appFontFace;
    settingsAppFontDialogSize = appFontDialogSize;
    settingsAppFontWeight = appFontWeight;
    settingsAppFontItalic = appFontItalic;
    selectedDraftIndex = 0;
    if (widgetId >= 0) {
        for (size_t index = 0; index < settingsDraft.size(); index++) {
            if (settingsDraft[index].id == widgetId) {
                selectedDraftIndex = static_cast<int>(index);
                break;
            }
        }
    }
    DWORD extendedStyle = WS_EX_CONTROLPARENT;
    DWORD style = 0;
    int settingsWidth = 0;
    int settingsHeight = 0;
    GetSettingsWindowLayout(extendedStyle, &style, &settingsWidth, &settingsHeight);
    ClampFormPosition(&settingsX, &settingsY, settingsWidth, settingsHeight);
    hSettings = CreateWindowExW(extendedStyle, CLASS_NAME, T(TXT_SETTINGS),
        style, settingsX, settingsY, settingsWidth, settingsHeight, nullptr, nullptr, hInstance, nullptr);
    RefreshFullscreenPresentation();
    CreateSettingsControls();
    RefreshWidgetList(true, false);
    LoadDraftIntoControls();
    if (hTabs != nullptr) {
        TabCtrl_SetCurSel(hTabs, std::clamp(settingsTab, 0, SETTINGS_TAB_COUNT - 1));
        ShowSettingsTab(TabCtrl_GetCurSel(hTabs));
    }
    UpdateSettingsApplyButton();
    ShowWindow(hSettings, SW_SHOW);
    SetForegroundWindowEx(hSettings);
    SetActiveWindow(hSettings);
    SetFocus(hAddType);
}

/// Decodes the embedded UTF-8 license, removes an optional BOM and a case-insensitive MIT License heading, and trims
/// outer whitespace.
/// Accepts whitespace between heading words, preserves the license body, and normalizes line endings for the edit
/// control.
static std::wstring LoadLicenseText() {
    HRSRC resource = FindResourceW(hInstance, MAKEINTRESOURCEW(IDR_LICENSE), RT_RCDATA);
    if (resource == nullptr) {
        return std::wstring();
    }
    HGLOBAL loadedResource = LoadResource(hInstance, resource);
    if (loadedResource == nullptr) {
        return std::wstring();
    }
    DWORD byteCount = SizeofResource(hInstance, resource);
    const char* bytes = static_cast<const char*>(LockResource(loadedResource));
    if (bytes == nullptr || byteCount == 0 || byteCount > static_cast<DWORD>(INT_MAX)) {
        return std::wstring();
    }
    int characterCount = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, bytes,
        static_cast<int>(byteCount), nullptr, 0);
    if (characterCount <= 0) {
        return std::wstring();
    }
    std::wstring decoded(characterCount, L'\0');
    if (MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, bytes, static_cast<int>(byteCount),
        decoded.data(), characterCount) != characterCount) {
        return std::wstring();
    }
    size_t headingStart = !decoded.empty() && decoded.front() == L'\uFEFF' ? 1 : 0;
    while (headingStart < decoded.size() && iswspace(decoded[headingStart])) {
        headingStart++;
    }
    size_t headingEnd = decoded.find_first_of(L"\r\n", headingStart);
    std::wstring heading = decoded.substr(headingStart, headingEnd - headingStart);
    std::wstring normalizedHeading;
    bool whitespace = false;
    for (wchar_t character : heading) {
        if (iswspace(character)) {
            whitespace = true;
        } else {
            if (whitespace && !normalizedHeading.empty()) {
                normalizedHeading += L' ';
            }
            normalizedHeading += character;
            whitespace = false;
        }
    }
    size_t bodyStart = headingStart;
    if (_wcsicmp(normalizedHeading.c_str(), L"MIT License") == 0) {
        bodyStart = headingEnd == std::wstring::npos ? decoded.size() : headingEnd;
        while (bodyStart < decoded.size() && iswspace(decoded[bodyStart])) {
            bodyStart++;
        }
    }
    decoded.erase(0, bodyStart);
    while (!decoded.empty() && iswspace(decoded.back())) {
        decoded.pop_back();
    }
    std::wstring result;
    result.reserve(decoded.size() + 32);
    for (size_t index = 0; index < decoded.size(); index++) {
        if (decoded[index] == L'\n' && (index == 0 || decoded[index - 1] != L'\r')) {
            result += L'\r';
        }
        result += decoded[index];
    }
    return result;
}

/// Returns the executable's four-part product version, or a question mark if version information cannot be read.
static std::wstring GetApplicationVersion() {
    wchar_t path[MAX_PATH] = {};
    if (GetModuleFileNameW(nullptr, path, ARRAYSIZE(path)) == 0) {
        return L"?";
    }
    DWORD ignored = 0;
    DWORD size = GetFileVersionInfoSizeW(path, &ignored);
    if (size == 0) {
        return L"?";
    }
    std::vector<BYTE> data(size);
    if (!GetFileVersionInfoW(path, 0, size, data.data())) {
        return L"?";
    }
    VS_FIXEDFILEINFO* information = nullptr;
    UINT informationSize = 0;
    bool invalidVersionInfo =
        !VerQueryValueW(data.data(), L"\\", reinterpret_cast<void**>(&information), &informationSize)
        || information == nullptr
        || informationSize < sizeof(VS_FIXEDFILEINFO)
        || information->dwSignature != VS_FFI_SIGNATURE;
    if (invalidVersionInfo) {
        return L"?";
    }
    wchar_t version[48] = {};
    swprintf_s(version, L"%u.%u.%u.%u",
        HIWORD(information->dwProductVersionMS),
        LOWORD(information->dwProductVersionMS),
        HIWORD(information->dwProductVersionLS),
        LOWORD(information->dwProductVersionLS));
    return version;
}

/// Builds the About window title from its localized caption and the application name.
static std::wstring BuildAboutTitle() {
    return std::wstring(T(TXT_ABOUT)) + L" CalClock";
}

/// Builds localized product information including description, version, copyright, and target platform.
static std::wstring BuildAboutProductText() {
    std::wstring description = ABOUT_TEXT[appLanguage];
    size_t separator = description.find(L"\r\n\r\n");
    if (separator != std::wstring::npos) {
        description.erase(0, separator + 4);
    }
    std::wstring result = L"CalClock\r\n" + description + L"\r\n\r\n";
    result += ABOUT_VERSION_LABELS[appLanguage];
    result += L" ";
    result += GetApplicationVersion();
    result += L"\r\nCopyright © Petr Červinka – FortSoft 2026\r\n";
    result += ABOUT_PLATFORM_LABELS[appLanguage];
    result += L" Win32 (x86)";
    return result;
}

/// Builds SysLink markup for the product website URL.
static std::wstring BuildAboutLinkText() {
    return std::wstring(L"<a href=\"") + ABOUT_WEBSITE_URL + L"\">" + ABOUT_WEBSITE_URL + L"</a>";
}

/// Combines product information and the labeled website URL as plain text for copying.
static std::wstring BuildAboutClipboardText() {
    return BuildAboutProductText() + L"\r\n" + ABOUT_WEBSITE_LABELS[appLanguage] + L" " + ABOUT_WEBSITE_URL;
}

/// Displays the applicable About context commands and handles opening the website or copying its URL or product
/// information.
static void ShowAboutContextMenu(HWND source, LPARAM location) {
    HMENU menu = CreatePopupMenu();
    if (menu == nullptr) {
        return;
    }
    int controlId = GetDlgCtrlID(source);
    if (controlId == ID_INFO_LINK) {
        AppendMenuW(menu, MF_STRING, ID_MENU_ABOUT_OPEN_LINK, OPEN_IN_BROWSER_LABELS[appLanguage]);
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        AppendMenuW(menu, MF_STRING, ID_MENU_ABOUT_COPY_URL, COPY_URL_LABELS[appLanguage]);
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        AppendMenuW(menu, MF_STRING, ID_MENU_ABOUT_COPY_INFORMATION, COPY_INFORMATION_LABELS[appLanguage]);
    } else {
        AppendMenuW(menu, MF_STRING, ID_MENU_ABOUT_COPY_INFORMATION, COPY_INFORMATION_LABELS[appLanguage]);
    }
    POINT point = { GET_X_LPARAM(location), GET_Y_LPARAM(location) };
    if (location == -1) {
        RECT rectangle = {};
        GetWindowRect(source, &rectangle);
        point.x = rectangle.left;
        point.y = rectangle.bottom;
    }
    int command = TrackPopupMenu(menu, TPM_RETURNCMD | TPM_RIGHTBUTTON, point.x, point.y, 0, hAbout, nullptr);
    DestroyMenu(menu);
    if (command == ID_MENU_ABOUT_OPEN_LINK) {
        ShellExecuteW(hAbout, L"open", ABOUT_WEBSITE_URL, nullptr, nullptr, SW_SHOWNORMAL);
    } else if (command == ID_MENU_ABOUT_COPY_URL) {
        CopyTextToClipboard(hAbout, ABOUT_WEBSITE_URL);
    } else if (command == ID_MENU_ABOUT_COPY_INFORMATION) {
        CopyTextToClipboard(hAbout, BuildAboutClipboardText());
    }
}

/// Adds the About context menu to product and website controls and removes the subclass on destruction.
static LRESULT CALLBACK AboutControlSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    UNREFERENCED_PARAMETER(referenceData);
    if (message == WM_CONTEXTMENU) {
        ShowAboutContextMenu(window, lParam);
        return 0;
    }
    if (message == WM_NCDESTROY) {
        RemoveWindowSubclass(window, AboutControlSubclassProc, subclassId);
    }
    return DefSubclassProc(window, message, wParam, lParam);
}

/// Measures unwrapped license text in the edit's current font and toggles the horizontal scrollbar only when needed.
/// Restores horizontal position to the start before hiding the bar; measurement also works while the bar is hidden.
static void UpdateAboutLicenseScrollBar(HWND window) {
    HDC dc = GetDC(window);
    if (dc == nullptr) {
        return;
    }
    HFONT font = reinterpret_cast<HFONT>(SendMessageW(window, WM_GETFONT, 0, 0));
    HGDIOBJ previousFont = font == nullptr ? nullptr : SelectObject(dc, font);
    std::wstring text = GetControlText(window);
    RECT textBounds = {};
    DrawTextW(dc, text.c_str(), static_cast<int>(text.size()), &textBounds, DT_CALCRECT | DT_NOPREFIX | DT_EXPANDTABS);
    if (previousFont != nullptr) {
        SelectObject(dc, previousFont);
    }
    ReleaseDC(window, dc);
    RECT format = {};
    SendMessageW(window, EM_GETRECT, 0, reinterpret_cast<LPARAM>(&format));
    bool needed = textBounds.right - textBounds.left > format.right - format.left;
    bool visible = (GetWindowLongPtrW(window, GWL_STYLE) & WS_HSCROLL) != 0;
    if (needed != visible) {
        if (!needed) {
            SendMessageW(window, WM_HSCROLL, SB_LEFT, 0);
        }
        ShowScrollBar(window, SB_HORZ, needed);
    }
}

/// Recalculates horizontal scrollbar visibility after native size, font, text, or theme updates and removes the
/// subclass on destruction.
static LRESULT CALLBACK AboutLicenseSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    UNREFERENCED_PARAMETER(referenceData);
    if (message == WM_SIZE || message == WM_SETFONT || message == WM_SETTEXT || message == WM_THEMECHANGED) {
        LRESULT result = DefSubclassProc(window, message, wParam, lParam);
        UpdateAboutLicenseScrollBar(window);
        return result;
    }
    if (message == WM_NCDESTROY) {
        RemoveWindowSubclass(window, AboutLicenseSubclassProc, subclassId);
    }
    return DefSubclassProc(window, message, wParam, lParam);
}

/// Updates open Help and About windows for the application language and recalculates their layouts.
static void RefreshInformationWindows() {
    if (hHelp != nullptr && IsWindow(hHelp)) {
        SetWindowTextW(hHelp, T(TXT_HELP));
        std::wstring helpText = std::wstring(HELP_TEXT[appLanguage])
            + HELP_ALARM_APPENDIX[appLanguage]
            + HELP_SELECTION_APPENDIX[appLanguage]
            + HELP_LAYOUT_APPENDIX[appLanguage]
            + HELP_STORAGE_APPENDIX[appLanguage]
            + HELP_SETTINGS_APPENDIX[appLanguage]
            + HELP_TIME_SIGNAL_APPENDIX[appLanguage]
            + HELP_ADDITIONAL_CLOCK_APPENDIX[appLanguage]
            + HELP_TIME_FORMAT_APPENDIX[appLanguage]
            + HELP_TIME_APPENDIX[appLanguage]
            + HELP_FULLSCREEN_APPENDIX[appLanguage];
        SetDlgItemTextW(hHelp, ID_INFO_TEXT, helpText.c_str());
        SetDlgItemTextW(hHelp, ID_INFO_CLOSE, Mnemonic(TXT_CLOSE).c_str());
    }
    if (hAbout != nullptr && IsWindow(hAbout)) {
        std::wstring title = BuildAboutTitle();
        std::wstring productText = BuildAboutProductText();
        std::wstring linkText = BuildAboutLinkText();
        SetWindowTextW(hAbout, title.c_str());
        SetDlgItemTextW(hAbout, ID_INFO_PRODUCT, productText.c_str());
        SetDlgItemTextW(hAbout, ID_INFO_WEBSITE, ABOUT_WEBSITE_LABELS[appLanguage]);
        SetDlgItemTextW(hAbout, ID_INFO_LINK, linkText.c_str());
        SetDlgItemTextW(hAbout, ID_INFO_CLOSE, Mnemonic(TXT_CLOSE).c_str());
        LayoutInformationWindow(hAbout);
        if (hAboutTooltip != nullptr) {
            SendMessageW(hAboutTooltip, TTM_UPDATE, 0, 0);
        }
    }
}

/// Returns a dialog child's window rectangle mapped to its parent's client coordinates.
static RECT InformationControlRect(HWND window, int id) {
    RECT rect = {};
    GetWindowRect(GetDlgItem(window, id), &rect);
    MapWindowPoints(HWND_DESKTOP, window, reinterpret_cast<POINT*>(&rect), 2);
    return rect;
}

/// Captures initial Help or About control rectangles for subsequent anchored layout calculations.
static void InitializeInformationWindowLayout(HWND window, bool help) {
    InformationWindowLayout& layout = help ? helpWindowLayout : aboutWindowLayout;
    layout.text = InformationControlRect(window, ID_INFO_TEXT);
    layout.close = InformationControlRect(window, ID_INFO_CLOSE);
    if (!help) {
        layout.product = InformationControlRect(window, ID_INFO_PRODUCT);
        layout.website = InformationControlRect(window, ID_INFO_WEBSITE);
        layout.link = InformationControlRect(window, ID_INFO_LINK);
    }
    layout.initialized = true;
}

/// Positions an information-window child without activation or Z-order changes, enforcing positive dimensions.
static void PlaceInformationControl(HWND window, int id, int x, int y, int width, int height) {
    HWND control = GetDlgItem(window, id);
    int controlWidth = std::max(1, width);
    int controlHeight = std::max(1, height);
    UINT flags = SWP_NOZORDER | SWP_NOACTIVATE;
    SetWindowPos(control, nullptr, x, y, controlWidth, controlHeight, flags);
}

/// Measures a label's wrapped height at the requested width using its actual font, or returns zero if a DC is
/// unavailable.
static int InformationLabelHeight(HWND control, int width) {
    HDC dc = GetDC(control);
    if (dc == nullptr) {
        return 0;
    }
    std::wstring text = GetControlText(control);
    HFONT font = reinterpret_cast<HFONT>(SendMessageW(control, WM_GETFONT, 0, 0));
    HGDIOBJ oldFont = font == nullptr ? nullptr : SelectObject(dc, font);
    RECT bounds = {
        0,
        0,
        std::max(1, width),
        0
    };
    UINT flags = DT_CALCRECT | DT_WORDBREAK | DT_NOPREFIX | DT_EXPANDTABS;
    DrawTextW(dc, text.c_str(), static_cast<int>(text.size()), &bounds, flags);
    if (oldFont != nullptr) {
        SelectObject(dc, oldFont);
    }
    ReleaseDC(control, dc);
    return bounds.bottom - bounds.top;
}

/// Anchors Help or About controls to the client area, measures wrapped product text, and preserves right and bottom
/// spacing.
static void LayoutInformationWindow(HWND window) {
    InformationWindowLayout& layout = window == hHelp ? helpWindowLayout : aboutWindowLayout;
    if (!layout.initialized || IsIconic(window)) {
        return;
    }
    RECT client = {};
    GetClientRect(window, &client);
    int margin = layout.text.left;
    int right = client.right - margin;
    int buttonWidth = layout.close.right - layout.close.left;
    int buttonHeight = layout.close.bottom - layout.close.top;
    int buttonX = right - buttonWidth;
    int buttonY = client.bottom - margin - buttonHeight;
    int textTop = layout.text.top;
    int textWidth = right - layout.text.left;
    int buttonGap = layout.close.top - layout.text.bottom;
    if (window == hAbout) {
        HWND product = GetDlgItem(window, ID_INFO_PRODUCT);
        int productWidth = right - layout.product.left;
        int measuredHeight = InformationLabelHeight(product, productWidth);
        int productHeight = std::max(static_cast<int>(layout.product.bottom - layout.product.top), measuredHeight);
        int productGap = layout.website.top - layout.product.bottom;
        int websiteY = layout.product.top + productHeight + productGap;
        int websiteWidth = layout.website.right - layout.website.left;
        int websiteHeight = layout.website.bottom - layout.website.top;
        int linkWidth = right - layout.link.left;
        int linkHeight = layout.link.bottom - layout.link.top;
        int rowHeight = std::max(websiteHeight, linkHeight);
        int textGap = layout.text.top - std::max(layout.website.bottom, layout.link.bottom);
        textTop = websiteY + rowHeight + textGap;
        PlaceInformationControl(window, ID_INFO_PRODUCT, layout.product.left, layout.product.top, productWidth,
            productHeight);
        PlaceInformationControl(window, ID_INFO_WEBSITE, layout.website.left, websiteY, websiteWidth, websiteHeight);
        PlaceInformationControl(window, ID_INFO_LINK, layout.link.left, websiteY, linkWidth, linkHeight);
    }
    int textHeight = buttonY - buttonGap - textTop;
    PlaceInformationControl(window, ID_INFO_TEXT, layout.text.left, textTop, textWidth, textHeight);
    PlaceInformationControl(window, ID_INFO_CLOSE, buttonX, buttonY, buttonWidth, buttonHeight);
    InvalidateRect(window, nullptr, TRUE);
}

/// Constrains an information window's size and position to its monitor work area, then recomputes the child layout.
static void FitInformationWindowToWorkArea(HWND window) {
    if (window == nullptr || !IsWindow(window) || IsIconic(window)) {
        return;
    }
    MONITORINFO monitor = {};
    monitor.cbSize = sizeof(monitor);
    if (!GetMonitorInfoW(MonitorFromWindow(window, MONITOR_DEFAULTTONEAREST), &monitor)) {
        return;
    }
    RECT rect = {};
    GetWindowRect(window, &rect);
    int width = std::min(rect.right - rect.left, monitor.rcWork.right - monitor.rcWork.left);
    int height = std::min(rect.bottom - rect.top, monitor.rcWork.bottom - monitor.rcWork.top);
    int x = std::clamp(static_cast<int>(rect.left), static_cast<int>(monitor.rcWork.left),
        static_cast<int>(monitor.rcWork.right) - width);
    int y = std::clamp(static_cast<int>(rect.top), static_cast<int>(monitor.rcWork.top),
        static_cast<int>(monitor.rcWork.bottom) - height);
    SetWindowPos(window, nullptr, x, y, width, height, SWP_NOZORDER | SWP_NOACTIVATE);
    LayoutInformationWindow(window);
}

/// Creates or activates Help or About with localized content, saved placement, minimization, and work-area-aware
/// layout.
static void ShowInformationWindow(bool help) {
    HWND* target = help ? &hHelp : &hAbout;
    if (*target != nullptr && IsWindow(*target)) {
        SetForegroundWindowEx(*target);
        return;
    }
    if (help) {
        helpWindowLayout = {};
    } else {
        aboutWindowLayout = {};
    }
    int* x = help ? &helpX : &aboutX;
    int* y = help ? &helpY : &aboutY;
    int aboutExtraLineHeight = 0;
    if (!help) {
        if (hAboutFont == nullptr) {
            hAboutFont = CreateAboutFont();
        }
        HDC dc = GetDC(nullptr);
        if (dc != nullptr) {
            HGDIOBJ oldFont = SelectObject(dc, hAboutFont != nullptr ? hAboutFont : hUiFont);
            TEXTMETRICW metrics = {};
            if (GetTextMetricsW(dc, &metrics)) {
                aboutExtraLineHeight = metrics.tmHeight;
            }
            SelectObject(dc, oldFont);
            ReleaseDC(nullptr, dc);
        }
    }
    int width = help ? 660 : ABOUT_WINDOW_WIDTH;
    int height = help ? 500 : ABOUT_WINDOW_HEIGHT + aboutExtraLineHeight;
    DWORD extendedStyle = WS_EX_TOPMOST | (help ? 0 : WS_EX_DLGMODALFRAME);
    std::wstring title = help ? T(TXT_HELP) : BuildAboutTitle();
    ClampFormPosition(x, y, width, height);
    *target = CreateWindowExW(extendedStyle, CLASS_NAME, title.c_str(),
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        *x, *y, width, height, nullptr, nullptr, hInstance, nullptr);
    std::wstring helpBody = std::wstring(HELP_TEXT[appLanguage])
        + HELP_ALARM_APPENDIX[appLanguage]
        + HELP_SELECTION_APPENDIX[appLanguage]
        + HELP_LAYOUT_APPENDIX[appLanguage]
        + HELP_STORAGE_APPENDIX[appLanguage]
        + HELP_SETTINGS_APPENDIX[appLanguage]
        + HELP_TIME_SIGNAL_APPENDIX[appLanguage]
        + HELP_ADDITIONAL_CLOCK_APPENDIX[appLanguage]
        + HELP_TIME_FORMAT_APPENDIX[appLanguage]
        + HELP_TIME_APPENDIX[appLanguage]
        + HELP_FULLSCREEN_APPENDIX[appLanguage];
    if (help) {
        DWORD textStyle = WS_TABSTOP | WS_VSCROLL | ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL;
        HWND text = AddControl(WS_EX_CLIENTEDGE, L"EDIT", helpBody.c_str(), textStyle,
            18, 18, 610, 385, *target, ID_INFO_TEXT);
        SendMessageW(text, EM_SETSEL, 0, 0);
        AddControl(0, L"BUTTON", Mnemonic(TXT_CLOSE).c_str(), WS_TABSTOP | BS_DEFPUSHBUTTON,
            528, 415, 100, 28, *target, ID_INFO_CLOSE);
    } else {
        std::wstring productText = BuildAboutProductText();
        std::wstring linkText = BuildAboutLinkText();
        HWND icon = AddControl(0, L"STATIC", L"", SS_ICON, 18, 18, 32, 32, *target, ID_INFO_ICON);
        HICON applicationIcon = static_cast<HICON>(LoadImageW(hInstance, MAKEINTRESOURCEW(IDI_CLOCK), IMAGE_ICON,
            32, 32, LR_SHARED));
        SendMessageW(icon, STM_SETICON, reinterpret_cast<WPARAM>(applicationIcon), 0);
        HWND product = AddControl(0, L"STATIC", productText.c_str(), SS_LEFT | SS_NOPREFIX | SS_NOTIFY,
            62, 12, 456, 126, *target, ID_INFO_PRODUCT);
        HWND website = AddControl(0, L"STATIC", ABOUT_WEBSITE_LABELS[appLanguage], SS_LEFT | SS_NOPREFIX | SS_NOTIFY,
            62, 145, 88, 20, *target, ID_INFO_WEBSITE);
        HWND link = AddControl(0, WC_LINK, linkText.c_str(), WS_TABSTOP, 150, 145, 368, 22, *target, ID_INFO_LINK);
        DWORD licenseStyle =
            WS_TABSTOP | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_READONLY | ES_AUTOHSCROLL | ES_AUTOVSCROLL;
        HWND license = AddControl(WS_EX_CLIENTEDGE, L"EDIT", LoadLicenseText().c_str(), licenseStyle,
            18, 177, 500, 256 + aboutExtraLineHeight, *target, ID_INFO_TEXT);
        SetWindowSubclass(license, AboutLicenseSubclassProc, ABOUT_LICENSE_SUBCLASS_ID, 0);
        SetWindowSubclass(product, AboutControlSubclassProc, ABOUT_CONTROL_SUBCLASS_ID, 0);
        SetWindowSubclass(website, AboutControlSubclassProc, ABOUT_CONTROL_SUBCLASS_ID, 0);
        SetWindowSubclass(link, AboutControlSubclassProc, ABOUT_CONTROL_SUBCLASS_ID, 0);
        hAboutTooltip = CreateControlTooltip(*target, link, LPSTR_TEXTCALLBACKW);
        SendMessageW(license, EM_SETSEL, 0, 0);
        HWND close = AddControl(0, L"BUTTON", Mnemonic(TXT_CLOSE).c_str(), WS_TABSTOP | BS_DEFPUSHBUTTON,
            418, 445 + aboutExtraLineHeight, 100, 28, *target, ID_INFO_CLOSE);
        SetFocus(close);
    }
    ApplyUiStyle(*target);
    InitializeInformationWindowLayout(*target, help);
    FitInformationWindowToWorkArea(*target);
    ShowWindow(*target, SW_SHOW);
    SetForegroundWindowEx(*target);
}

/// Dispatches settings notifications and actions, validating edits and coordinating selection, previews, duplication,
/// and persistence. Disables Apply only after its successful explicit invocation.
static void HandleSettingsCommand(int id, int notification) {
    if (updatingSettingsControls) {
        return;
    }
    if (id == ID_LIST_WIDGETS && notification == LBN_SELCHANGE) {
        if (!SaveControlsToDraft(true)) {
            SelectOnlyWidgetIndex(selectedDraftIndex);
            return;
        }
        if (settingsPreviewStopEvent != nullptr || settingsVisualPreviewActive) {
            StopSettingsPreview();
        }
        std::vector<int> selected = GetSelectedWidgetIndices();
        int selectionIndex = selected.size() == 1
            ? selected.front()
            : static_cast<int>(SendMessageW(hWidgetList, LB_GETCARETINDEX, 0, 0));
        if (selectionIndex >= 0 && selectionIndex < static_cast<int>(settingsDraft.size())) {
            selectedDraftIndex = selectionIndex;
        }
        LoadDraftIntoControls();
        UpdateSettingsSelectionState();
    } else if (id == ID_LIST_WIDGETS && notification == LBN_DBLCLK) {
        if (selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
            IdentifyAndShowWidget(FindWidgetById(settingsDraft[selectedDraftIndex].id), selectedDraftIndex);
        }
    } else if (id == ID_TYPE && notification == CBN_SELCHANGE) {
        if (settingsPreviewStopEvent != nullptr || settingsVisualPreviewActive) {
            StopSettingsPreview();
        }
        int type = static_cast<int>(SendMessageW(hTypeCombo, CB_GETCURSEL, 0, 0));
        if (selectedDraftIndex >= 0
                && selectedDraftIndex < static_cast<int>(settingsDraft.size())
                && type >= 0 && type < WIDGET_TYPE_COUNT) {
            WidgetConfig& config = settingsDraft[selectedDraftIndex];
            WidgetType previousType = config.type;
            std::wstring editedName = GetControlText(hNameEdit);
            if (!SaveControlsToDraft(true)) {
                SetComboSelection(hTypeCombo, previousType);
                return;
            }
            WidgetType selectedType = static_cast<WidgetType>(type);
            config.type = selectedType;
            if (selectedType != previousType) {
                bool defaultName = editedName.empty() || editedName == TypeName(previousType);
                if (defaultName) {
                    config.name = TypeName(selectedType);
                }
                Widget* widget = FindWidgetById(config.id);
                if (widget != nullptr) {
                    WidgetConfig preview = widget->config;
                    preview.type = selectedType;
                    preview.name = config.name;
                    preview.showSeconds = config.showSeconds;
                    preview.showUtc = config.showUtc;
                    preview.showUtcText = config.showUtcText;
                    preview.showAmPm = config.showAmPm;
                    preview.timeFormat = config.timeFormat;
                    preview.language = config.language;
                    preview.timeZoneKey = config.timeZoneKey;
                    for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
                        preview.additionalClocks[index] = config.additionalClocks[index];
                    }
                    preview.monitorDevices = config.monitorDevices;
                    preview.blackoutOtherMonitors = config.blackoutOtherMonitors;
                    preview.offsetMilliseconds = config.offsetMilliseconds;
                    CopyWidgetAppearance(&preview, config);
                    if (std::find(settingsAppearancePreviewIds.begin(), settingsAppearancePreviewIds.end(), config.id) ==
                            settingsAppearancePreviewIds.end()) {
                        settingsAppearancePreviewIds.push_back(config.id);
                    }
                    settingsAppearancePreviewActive = true;
                    RecreateWidgetForConfiguration(widget, preview);
                }
                RefreshWidgetList(true, false);
                LoadDraftIntoControls();
                UpdateSettingsSelectionState();
                return;
            }
        }
        UpdateSettingControlAvailability();
    } else if (id == ID_UTC && notification == BN_CLICKED || id == ID_TIMEZONE && notification == CBN_SELCHANGE) {
        UpdateSettingControlAvailability();
    } else if (id == ID_ALARM_ENABLED && notification == BN_CLICKED) {
        UpdateSettingControlAvailability();
    } else if (id == ID_RUN_COMMAND && notification == BN_CLICKED) {
        UpdateSettingControlAvailability();
    } else if (id == ID_SOUNDS_ENABLED && notification == BN_CLICKED) {
        if (selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
            bool muted = GetCheck(hSoundsMutedCheck);
            settingsDraft[selectedDraftIndex].soundsMuted = muted;
            Widget* widget = FindWidgetById(settingsDraft[selectedDraftIndex].id);
            if (widget != nullptr) {
                ApplyWidgetSoundsMuted(widget, muted);
            }
            for (WidgetConfig& applied : settingsAppliedWidgets) {
                if (applied.id == settingsDraft[selectedDraftIndex].id) {
                    applied.soundsMuted = muted;
                    break;
                }
            }
            UpdateSettingsPreviewMute();
            SaveSettingsWithoutAppearancePreviews();
        }
    } else if (id == ID_ALARM_TIME && notification == EN_CHANGE && GetFocus() == hAlarmTimeEdit) {
        SetCheck(hAlarmEnabledCheck, true);
        UpdateSettingControlAvailability();
    } else if (id == ID_COMMAND && notification == EN_CHANGE) {
        UpdateSettingControlAvailability();
    } else if (id == ID_ALARM_TIME && notification == EN_KILLFOCUS) {
        int hour = 0;
        int minute = 0;
        std::wstring text = GetControlText(hAlarmTimeEdit);
        if (ParseAlarmTime(text.c_str(), &hour, &minute)) {
            wchar_t formatted[16] = {};
            swprintf_s(formatted, L"%02d:%02d", hour, minute);
            if (text != formatted) {
                SetWindowTextW(hAlarmTimeEdit, formatted);
            }
        }
    } else if (id == ID_OFFSET && notification == EN_KILLFOCUS) {
        LONGLONG offset = 0;
        std::wstring text = GetControlText(hOffsetEdit);
        if (ParseOffset(text.c_str(), &offset)) {
            std::wstring formatted = FormatOffset(offset);
            if (text != formatted) {
                SetWindowTextW(hOffsetEdit, formatted.c_str());
            }
        }
    } else if (id == ID_REMOTE_SCRIPT && notification == BN_CLICKED) {
        bool remoteScriptEnabled = GetCheck(hRemoteScriptCheck);
        EnableWindow(hRemoteScriptLabel, remoteScriptEnabled);
        EnableWindow(hRemoteScriptEdit, remoteScriptEnabled);
        if (remoteScriptEnabled) {
            SetFocus(hRemoteScriptEdit);
        }
    } else if (id >= ID_ADDITIONAL_ENABLED_BASE
            && id < ID_ADDITIONAL_ENABLED_BASE + ADDITIONAL_CLOCK_COUNT
            && notification == BN_CLICKED) {
        UpdateSettingControlAvailability();
    } else if (id >= ID_ADDITIONAL_SIZE_BASE
            && id < ID_ADDITIONAL_SIZE_BASE + ADDITIONAL_CLOCK_COUNT
            && notification == CBN_SELCHANGE) {
        SaveAppearanceControlsToDraft();
        UpdateSettingControlAvailability();
        PreviewSelectedWidgetAppearance(true);
    } else if (id == ID_SIZE && notification == CBN_SELCHANGE) {
        SaveAppearanceControlsToDraft();
        UpdateSettingControlAvailability();
        PreviewSelectedWidgetAppearance(true);
    } else if (id == ID_WIDGET_ANTIALIAS && notification == CBN_SELCHANGE) {
        PreviewSelectedWidgetAppearance(false);
    } else if (id == ID_WIDGET_LANGUAGE && notification == CBN_SELCHANGE) {
        AppLanguage language = LanguageFromCombo(hWidgetLanguageCombo);
        if (selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
            WidgetConfig& config = settingsDraft[selectedDraftIndex];
            int dateFormat = static_cast<int>(SendMessageW(hDateFormatCombo, CB_GETCURSEL, 0, 0));
            if (dateFormat >= 0 && dateFormat < DATE_FORMAT_COUNT) {
                config.dateCopyFormat = dateFormat;
            }
            config.language = language;
            FillDateFormatCombo(config);
        }
        UpdateSettingControlAvailability();
    } else if (id == ID_TIME_FORMAT && notification == CBN_SELCHANGE) {
        UpdateSettingControlAvailability();
    } else if (id == ID_SHOW_AM_PM && notification == BN_CLICKED) {
        if (selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
            settingsDraft[selectedDraftIndex].showAmPm = GetCheck(hShowAmPmCheck);
        }
    } else if (id == ID_TIME_SIGNAL_TEST && notification == BN_CLICKED) {
        settingsTimeSignalTestActive = !settingsTimeSignalTestActive;
        UpdateTimeSignalVolumePreview();
    } else if (id == ID_TIME_SIGNAL_SOUND && notification == CBN_SELCHANGE) {
        UpdateTimeSignalVolumeControls();
    } else if (id == ID_TIME_SOURCE && notification == CBN_SELCHANGE) {
        UpdateNtpSettingsControls();
    } else if (id == ID_NTP_PRESET && notification == CBN_SELCHANGE) {
        ApplySelectedNtpPresetToEdit();
        UpdateNtpSettingsControls();
    } else if (id == ID_NTP_SERVERS && notification == EN_CHANGE) {
        if (!updatingNtpPresetControls && hNtpPresetCombo != nullptr) {
            int selectedPreset = static_cast<int>(SendMessageW(hNtpPresetCombo, CB_GETCURSEL, 0, 0));
            if (selectedPreset >= 0 && selectedPreset < NTP_PRESET_CUSTOM) {
                std::wstring expected = NtpServersForPreset(selectedPreset);
                if (GetControlText(hNtpServersEdit) != expected) {
                    SetComboSelection(hNtpPresetCombo, NTP_PRESET_CUSTOM);
                }
            }
        }
        UpdateNtpSettingsControls();
    } else if (id == ID_NTP_SYNC && notification == BN_CLICKED) {
        StartNtpSynchronization(true, true);
        UpdateNtpSettingsControls();
    } else if (id == ID_ADD) {
        if (settingsDraft.size() >= MAX_WIDGET_COUNT) {
            ShowWidgetLimitMessage();
            return;
        }
        if (!SaveControlsToDraft(true)) {
            return;
        }
        int type = static_cast<int>(SendMessageW(hAddType, CB_GETCURSEL, 0, 0));
        if (type < 0 || type >= WIDGET_TYPE_COUNT) {
            type = WIDGET_ANALOG;
        }
        lastAddedWidgetType = static_cast<WidgetType>(type);
        WidgetConfig config = DefaultConfig(static_cast<WidgetType>(type), static_cast<int>(settingsDraft.size()));
        int selectedAppFontAntialiasing = SelectedFontAntialiasing(hAppAntialiasCombo, appFontAntialiasing);
        config.fontAntialiasing = std::clamp(selectedAppFontAntialiasing, 0, FONT_ANTIALIAS_COUNT - 1);
        settingsDraft.push_back(config);
        selectedDraftIndex = static_cast<int>(settingsDraft.size()) - 1;
        RefreshWidgetList(false, false);
        LoadDraftIntoControls();
    } else if (id == ID_DUPLICATE) {
        std::vector<WidgetConfig> selected;
        if (CollectSelectedWidgetConfigs(&selected)) {
            AppendWidgetCopies(selected);
        }
    } else if (id == ID_REMOVE) {
        if (!SaveControlsToDraft(true)) {
            return;
        }
        std::vector<int> selected = GetSelectedWidgetIndices();
        if (selected.empty() && selectedDraftIndex >= 0) {
            selected.push_back(selectedDraftIndex);
        }
        if (selected.empty()) {
            return;
        }
        if (selected.size() >= settingsDraft.size()) {
            MessageBoxW(hSettings, T(TXT_AT_LEAST_ONE), T(TXT_SETTINGS), MB_OK | MB_ICONINFORMATION);
            SetFocus(hWidgetList);
            return;
        }
        int response = MessageBoxW(hSettings, T(TXT_DELETE_CONFIRM), T(TXT_SETTINGS), MB_YESNO | MB_ICONQUESTION);
        SetFocus(hWidgetList);
        if (response != IDYES) {
            return;
        }
        std::sort(selected.begin(), selected.end());
        int firstRemoved = selected.front();
        for (std::vector<int>::reverse_iterator index = selected.rbegin(); index != selected.rend(); ++index) {
            if (*index >= 0 && *index < static_cast<int>(settingsDraft.size())) {
                settingsDraft.erase(settingsDraft.begin() + *index);
            }
        }
        selectedDraftIndex = std::min(firstRemoved, static_cast<int>(settingsDraft.size()) - 1);
        RefreshWidgetList(false, false);
        LoadDraftIntoControls();
        SetFocus(hWidgetList);
    } else if (id == ID_TEXT_COLOR) {
        if (ChooseButtonColor(hTextColorButton)) {
            PreviewSelectedWidgetAppearance(false);
        }
    } else if (id == ID_BACKGROUND_COLOR) {
        if (ChooseButtonColor(hBackgroundColorButton)) {
            PreviewSelectedWidgetAppearance(false);
        }
    } else if (id == ID_BORDER_COLOR) {
        if (ChooseButtonColor(hBorderColorButton)) {
            PreviewSelectedWidgetAppearance(false);
        }
    } else if (id == ID_ALARM_TEXT_COLOR) {
        if (ChooseButtonColor(hAlarmTextColorButton)) {
            PreviewSelectedWidgetAppearance(false);
        }
    } else if (id == ID_ALARM_BACKGROUND_COLOR) {
        if (ChooseButtonColor(hAlarmBackgroundColorButton)) {
            PreviewSelectedWidgetAppearance(false);
        }
    } else if (id == ID_FONT) {
        ChooseWidgetFont();
    } else if (id == ID_PANEL_TOP_FONT
            && selectedDraftIndex >= 0
            && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
        ChoosePanelFont(&settingsDraft[selectedDraftIndex].panelTopFont);
    } else if (id == ID_PANEL_TIME_FONT
            && selectedDraftIndex >= 0
            && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
        ChoosePanelFont(&settingsDraft[selectedDraftIndex].panelTimeFont);
    } else if (id == ID_PANEL_BOTTOM_FONT
            && selectedDraftIndex >= 0
            && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
        ChoosePanelFont(&settingsDraft[selectedDraftIndex].panelBottomFont);
    } else if (id == ID_APP_FONT) {
        ChooseApplicationFont();
    } else if (id == ID_APP_FONT_DEFAULT) {
        settingsAppFontFace.clear();
        settingsAppFontDialogSize = 90;
        settingsAppFontWeight = FW_NORMAL;
        settingsAppFontItalic = false;
        UpdateApplicationFontButtons();
        ApplyApplicationFontPreview();
    } else if (id == ID_VISUAL_STYLES && notification == BN_CLICKED) {
        UpdateSettingControlAvailability();
    } else if (id == ID_DEFAULT_APPEARANCE) {
        ResetWidgetAppearance();
    } else if (id == ID_LEADING_ZERO && notification == CBN_SELCHANGE) {
        PreviewSelectedWidgetAppearance(false);
    } else if ((id == ID_TRANSPARENT_BG || id == ID_WIDGET_DISABLE_THEMES) && notification == BN_CLICKED) {
        if (id == ID_WIDGET_DISABLE_THEMES) {
            UpdateSettingControlAvailability();
        }
        PreviewSelectedWidgetAppearance(false);
    } else if ((id == ID_SHOW_TODAY || id == ID_WEEK_NUMBERS || id == ID_SUNDAY_FIRST) && notification == BN_CLICKED) {
        PreviewSelectedWidgetAppearance(true);
    } else if (id == ID_BROWSE) {
        BrowseForCommand();
    } else if (id == ID_TEST_COMMAND) {
        TestSettingsCommand();
    } else if (id == ID_IMPORT_SETTINGS) {
        ImportSettings();
    } else if (id == ID_EXPORT_SETTINGS) {
        ExportSettings();
    } else if (id == ID_SAVE || id == ID_APPLY) {
        if (!SaveControlsToDraft(true)) {
            return;
        }
        bool widgetListChanged = settingsDraft.size() != widgets.size();
        if (!widgetListChanged) {
            for (size_t index = 0; index < settingsDraft.size(); index++) {
                if (settingsDraft[index].id != widgets[index]->config.id
                        || settingsDraft[index].name != widgets[index]->config.name) {
                    widgetListChanged = true;
                    break;
                }
            }
        }
        AppLanguage previousLanguage = appLanguage;
        ApplySettingsDraft();
        if (id == ID_SAVE) {
            CloseSettingsWindow();
        } else {
            settingsDraft.clear();
            for (size_t index = 0; index < widgets.size(); index++) {
                settingsDraft.push_back(widgets[index]->config);
            }
            settingsAppearanceOriginals = settingsDraft;
            settingsAppearancePreviewIds.clear();
            settingsAppearancePreviewActive = false;
            if (previousLanguage != appLanguage) {
                RebuildSettingsControls();
            } else if (widgetListChanged) {
                RefreshWidgetList(true, false);
            }
            HWND applyButton = GetDlgItem(hSettings, ID_APPLY);
            if (GetFocus() == applyButton) {
                SetFocus(GetDlgItem(hSettings, ID_SAVE));
            }
            EnableWindow(applyButton, FALSE);
        }
    } else if (id == ID_CANCEL) {
        CloseSettingsWindow();
    }
}

/// Draws a temporary rectangular or elliptical identification outline on the supplied window.
static void DrawIdentificationOutline(HWND window, bool ellipse) {
    HDC dc = GetDC(window);
    if (dc == nullptr) {
        return;
    }
    RECT rect = {};
    GetClientRect(window, &rect);
    HPEN pen = CreatePen(PS_SOLID, 3, IDENTIFY_COLOR);
    HGDIOBJ oldPen = SelectObject(dc, pen);
    HGDIOBJ oldBrush = SelectObject(dc, GetStockObject(HOLLOW_BRUSH));
    if (ellipse) {
        Ellipse(dc, 2, 2, rect.right - 2, rect.bottom - 2);
    } else {
        Rectangle(dc, 1, 1, rect.right - 1, rect.bottom - 1);
    }
    SelectObject(dc, oldBrush);
    SelectObject(dc, oldPen);
    DeleteObject(pen);
    ReleaseDC(window, dc);
}

/// Handles an additional clock's size menu, panel dragging, background painting, and theme updates without enabling a
/// second hand.
static LRESULT CALLBACK AdditionalAnalogChildProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    HWND parent = GetParent(window);
    Widget* widget = reinterpret_cast<Widget*>(GetWindowLongPtrW(parent, GWLP_USERDATA));
    int index = static_cast<int>(referenceData);
    if (message == WM_NCDESTROY) {
        RemoveWindowSubclass(window, AdditionalAnalogChildProc, subclassId);
    } else if (widget != nullptr && index >= 0 && index < ADDITIONAL_CLOCK_COUNT) {
        if (message == WM_ERASEBKGND) {
            RECT client = {};
            GetClientRect(window, &client);
            HBRUSH background = CreateSolidBrush(PanelBackgroundColor(widget));
            FillRect(reinterpret_cast<HDC>(wParam), &client, background);
            DeleteObject(background);
            return 1;
        }
        if (message == WM_RBUTTONUP || message == WM_CONTEXTMENU) {
            POINT point = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
            if (message == WM_RBUTTONUP) {
                ClientToScreen(window, &point);
            } else if (point.x == -1 && point.y == -1) {
                RECT rect = {};
                GetWindowRect(window, &rect);
                point = POINT{ (rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2 };
            }
            ShowAdditionalClockContextMenu(widget, index, point);
            return 0;
        }
        if (message == WM_LBUTTONDBLCLK) {
            return 0;
        }
        if (message == WM_LBUTTONDOWN || message == WM_LBUTTONUP || message == WM_MOUSEMOVE) {
            POINT point = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
            MapWindowPoints(window, parent, &point, 1);
            return SendMessageW(parent, message, wParam, MAKELPARAM(point.x, point.y));
        }
    }
    LRESULT result = DefSubclassProc(window, message, wParam, lParam);
    if (message == WM_THEMECHANGED && widget != nullptr && index >= 0 && index < ADDITIONAL_CLOCK_COUNT) {
        ConfigureAnalogClockControl(window,
            NormalizeAnalogClockSize(widget->config.additionalClocks[index].size), false);
    }
    return result;
}

/// Recognizes successive panel-face clicks within Windows double-click time and distance limits and updates click
/// tracking.
static bool IsPanelAnalogDoubleClick(Widget* widget, LPARAM lParam) {
    if (widget == nullptr || widget->config.type != WIDGET_PANEL) {
        return false;
    }
    ULONGLONG tick = GetTickCount64();
    POINT point = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
    bool doubleClick = widget->lastAnalogClickTick != 0
        && tick - widget->lastAnalogClickTick <= GetDoubleClickTime()
        && std::abs(point.x - widget->lastAnalogClickPoint.x) <= GetSystemMetrics(SM_CXDOUBLECLK) / 2
        && std::abs(point.y - widget->lastAnalogClickPoint.y) <= GetSystemMetrics(SM_CYDOUBLECLK) / 2;
    if (doubleClick) {
        widget->lastAnalogClickTick = 0;
    } else {
        widget->lastAnalogClickTick = tick;
        widget->lastAnalogClickPoint = point;
    }
    return doubleClick;
}

/// Integrates the primary native clock with widget dragging, face-only second-hand toggling, context menus, and
/// identification painting.
static LRESULT CALLBACK AnalogChildProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    HWND parent = GetParent(window);
    Widget* widget = reinterpret_cast<Widget*>(GetWindowLongPtrW(parent, GWLP_USERDATA));
    if (widget != nullptr) {
        if (message == WM_ERASEBKGND && widget->config.type == WIDGET_PANEL) {
            RECT client = {};
            GetClientRect(window, &client);
            HBRUSH background = CreateSolidBrush(PanelBackgroundColor(widget));
            FillRect(reinterpret_cast<HDC>(wParam), &client, background);
            DeleteObject(background);
            return 1;
        }
        if (message == WM_LBUTTONDOWN && IsPanelAnalogDoubleClick(widget, lParam)) {
            message = WM_LBUTTONDBLCLK;
        }
        if (message == WM_LBUTTONDBLCLK) {
            widget->lastAnalogClickTick = 0;
        }
        if (message == WM_LBUTTONDOWN
                || message == WM_LBUTTONUP
                || message == WM_MOUSEMOVE
                || message == WM_LBUTTONDBLCLK
                || message == WM_RBUTTONUP
                || message == WM_CONTEXTMENU) {
            if (message != WM_CONTEXTMENU) {
                POINT point = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
                MapWindowPoints(window, parent, &point, 1);
                lParam = MAKELPARAM(point.x, point.y);
            }
            return SendMessageW(parent, message, wParam, lParam);
        }
        if (widget->analogProc != nullptr) {
            LRESULT result = CallWindowProcW(widget->analogProc, window, message, wParam, lParam);
            if (message == WM_THEMECHANGED) {
                bool showAnalogSeconds = widget->config.showSeconds && AnalogClockSupportsSeconds(widget->config.size);
                ConfigureAnalogClockControl(window, widget->config.size, showAnalogSeconds);
            }
            return result;
        }
    }
    return DefWindowProcW(window, message, wParam, lParam);
}

/// Preserves native calendar navigation while distinguishing title clicks from widget drags.
/// Applies the widget locale to native processing and handles context menus and identification feedback.
static LRESULT CALLBACK CalendarChildProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    HWND parent = GetParent(window);
    Widget* widget = reinterpret_cast<Widget*>(GetWindowLongPtrW(parent, GWLP_USERDATA));
    if (widget != nullptr) {
        if (message == WM_RBUTTONUP || message == WM_CONTEXTMENU) {
            return SendMessageW(parent, message, wParam, lParam);
        }
        if (message == WM_CAPTURECHANGED || message == WM_CANCELMODE) {
            widget->calendarTitlePressed = false;
            if (message == WM_CANCELMODE && GetCapture() == window) {
                ReleaseCapture();
            }
        }
        if (message == WM_MOUSEMOVE && widget->calendarTitlePressed) {
            POINT cursor = {};
            GetCursorPos(&cursor);
            int distanceX = abs(cursor.x - widget->calendarTitlePressScreen.x);
            int distanceY = abs(cursor.y - widget->calendarTitlePressScreen.y);
            if ((wParam & MK_LBUTTON) != 0
                && (distanceX >= GetSystemMetrics(SM_CXDRAG) || distanceY >= GetSystemMetrics(SM_CYDRAG))) {
                widget->calendarTitlePressed = false;
                ReleaseCapture();
                SendMessageW(parent, WM_LBUTTONDOWN, wParam, lParam);
                if (widget->dragging) {
                    RECT rect = {};
                    GetWindowRect(parent, &rect);
                    widget->dragOffset.x = widget->calendarTitlePressScreen.x - rect.left;
                    widget->dragOffset.y = widget->calendarTitlePressScreen.y - rect.top;
                    SendMessageW(parent, WM_MOUSEMOVE, wParam, lParam);
                }
            }
            return 0;
        }
        if (message == WM_LBUTTONUP && widget->calendarTitlePressed) {
            widget->calendarTitlePressed = false;
            ReleaseCapture();
            if (widget->calendarProc != nullptr) {
                CalendarLocaleScope localeScope(LANGUAGE_LOCALES[widget->config.language]);
                CallWindowProcW(widget->calendarProc, window, WM_LBUTTONDOWN,
                    widget->calendarTitlePressKeys, widget->calendarTitlePressPosition);
                return CallWindowProcW(widget->calendarProc, window, WM_LBUTTONUP, wParam, lParam);
            }
            return 0;
        }
        if ((message == WM_LBUTTONDOWN || message == WM_LBUTTONDBLCLK) && widget->config.type == WIDGET_CALENDAR) {
            MCHITTESTINFO hit = {};
            hit.cbSize = sizeof(hit);
            hit.pt.x = GET_X_LPARAM(lParam);
            hit.pt.y = GET_Y_LPARAM(lParam);
            MonthCal_HitTest(window, &hit);
            bool titleArea = hit.uHit == MCHT_TITLEBK || hit.uHit == MCHT_TITLEMONTH || hit.uHit == MCHT_TITLEYEAR;
            if (titleArea) {
                widget->calendarTitlePressed = true;
                widget->calendarTitlePressPosition = lParam;
                widget->calendarTitlePressKeys = wParam;
                GetCursorPos(&widget->calendarTitlePressScreen);
                SetCapture(window);
                return 0;
            }
            bool draggableArea = hit.uHit == MCHT_NOWHERE || hit.uHit == MCHT_CALENDARBK;
            if (draggableArea) {
                return SendMessageW(parent, message, wParam, lParam);
            }
        }
        if (widget->calendarProc != nullptr) {
            CalendarLocaleScope localeScope(LANGUAGE_LOCALES[widget->config.language]);
            LRESULT result = CallWindowProcW(widget->calendarProc, window, message, wParam, lParam);
            if ((message == WM_THEMECHANGED || message == WM_SETTINGCHANGE) && widget->calendarFont != nullptr) {
                SendMessageW(window, WM_SETFONT, reinterpret_cast<WPARAM>(widget->calendarFont), TRUE);
            }
            if (message == WM_PAINT && widget->config.type == WIDGET_CALENDAR && widget->identifyActive && widget->identifyPhase) {
                DrawIdentificationOutline(window, false);
            }
            return result;
        }
    }
    return DefWindowProcW(window, message, wParam, lParam);
}

/// Selects the widget's displayed current date, optionally preserving the calendar's month, year, or decade view.
/// An explicit navigation request returns to month view and focuses the calendar.
static void SelectCalendarToday(Widget* widget, bool preserveView) {
    if (widget == nullptr || widget->calendarChild == nullptr) {
        return;
    }
    if (widget->panelDateTooltip != nullptr) {
        SendMessageW(widget->panelDateTooltip, TTM_POP, 0, 0);
    }
    SYSTEMTIME today = {};
    GetDisplayedTime(widget->config, &today);
    DWORD view = preserveView ? MonthCal_GetCurrentView(widget->calendarChild) : MCMV_MONTH;
    bool suspendRedraw = view != MCMV_MONTH && IsWindowVisible(widget->calendarChild);
    if (suspendRedraw) {
        SendMessageW(widget->calendarChild, WM_SETREDRAW, FALSE, 0);
    }
    MonthCal_SetToday(widget->calendarChild, &today);
    MonthCal_SetCurrentView(widget->calendarChild, MCMV_MONTH);
    MonthCal_SetCurSel(widget->calendarChild, &today);
    MonthCal_SetCurrentView(widget->calendarChild, view);
    if (suspendRedraw) {
        SendMessageW(widget->calendarChild, WM_SETREDRAW, TRUE, 0);
        RedrawWindow(widget->calendarChild, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME);
    }
    widget->lastCalendarDateKey = today.wYear * 10000 + today.wMonth * 100 + today.wDay;
    if (!preserveView) {
        SetFocus(widget->calendarChild);
    }
}

/// Moves the calendar selection to the displayed current day when its date changes, preserving the current calendar
/// view.
static void UpdateCalendarDate(Widget* widget) {
    if (widget == nullptr || widget->calendarChild == nullptr) {
        return;
    }
    SYSTEMTIME displayed = {};
    GetDisplayedTime(widget->config, &displayed);
    int dateKey = displayed.wYear * 10000 + displayed.wMonth * 100 + displayed.wDay;
    if (widget->lastCalendarDateKey != dateKey) {
        SelectCalendarToday(widget, true);
    }
}

/// Opens the Windows Date and Time control panel, preferring the native control.exe path from a 32-bit process.
static void OpenDateTimeControlPanel(HWND owner) {
    wchar_t windowsDirectory[MAX_PATH] = {};
    std::wstring controlPanel = L"control.exe";
    if (GetWindowsDirectoryW(windowsDirectory, ARRAYSIZE(windowsDirectory)) != 0) {
        std::wstring nativeControlPanel = std::wstring(windowsDirectory) + L"\\Sysnative\\control.exe";
        if (GetFileAttributesW(nativeControlPanel.c_str()) != INVALID_FILE_ATTRIBUTES) {
            controlPanel = nativeControlPanel;
        }
    }
    ShellExecuteW(owner, L"open", controlPanel.c_str(), L"timedate.cpl", nullptr, SW_SHOWNORMAL);
}

/// Paints the window's outer frame with the configured widget border color.
static void PaintConfiguredNativeFrame(HWND window, COLORREF color) {
    HDC dc = GetWindowDC(window);
    if (dc == nullptr) {
        return;
    }
    RECT rect = {};
    if (GetWindowRect(window, &rect)) {
        OffsetRect(&rect, -rect.left, -rect.top);
        HBRUSH brush = CreateSolidBrush(color);
        FrameRect(dc, &rect, brush);
        DeleteObject(brush);
    }
    ReleaseDC(window, dc);
}

/// Dispatches controller, widget, settings-page, and information-window messages.
/// Coordinates painting, input, timers, background-worker results, settings actions, and orderly application shutdown.
static LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    Widget* widget = reinterpret_cast<Widget*>(GetWindowLongPtrW(window, GWLP_USERDATA));
    if (message == WM_NCCREATE) {
        CREATESTRUCTW* create = reinterpret_cast<CREATESTRUCTW*>(lParam);
        if (create->lpCreateParams != nullptr) {
            widget = static_cast<Widget*>(create->lpCreateParams);
            SetWindowLongPtrW(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(widget));
        }
    }
    if (widget != nullptr && widget->config.type == WIDGET_FULLSCREEN || window == hFullscreenCursorWindow) {
        if (HandleFullscreenCursorMessage(window, message, wParam, lParam)) {
            return TRUE;
        }
    }
    if (message == taskbarCreatedMessage && window == hController) {
        AddTrayIcon();
        return 0;
    }
    switch (message) {
        case WM_NCPAINT:
            if (widget != nullptr && UsesConfigurableNativeFrame(widget)) {
                LRESULT result = DefWindowProcW(window, message, wParam, lParam);
                PaintConfiguredNativeFrame(window, widget->config.borderColor);
                return result;
            }
            break;
        case DM_GETDEFID:
            if (window == hSettings) {
                return MAKELRESULT(ID_SAVE, DC_HASDEFID);
            }
            break;
        case WM_SYSCOMMAND:
            if ((wParam & 0xFFF0) == SC_MINIMIZE) {
                if (window == hHelp) {
                    SaveFormPosition(window, &helpX, &helpY);
                } else if (window == hAbout) {
                    SaveFormPosition(window, &aboutX, &aboutY);
                }
            }
            break;
        case WM_SIZE:
            if ((window == hHelp || window == hAbout) && wParam != SIZE_MINIMIZED) {
                LayoutInformationWindow(window);
                return 0;
            }
            break;
        case WM_SETTINGCHANGE:
            if (window == hHelp || window == hAbout) {
                FitInformationWindowToWorkArea(window);
            }
            break;
        case WM_DISPLAYCHANGE:
            if (window == hHelp || window == hAbout) {
                FitInformationWindowToWorkArea(window);
            }
            if (!displayRefreshPending) {
                displayRefreshPending = true;
                PostMessageW(hController, WM_REFRESH_DISPLAYS, 0, 0);
            }
            if (window == hController) {
                return 0;
            }
            break;
        case WM_REFRESH_DISPLAYS:
            if (window == hController) {
                displayRefreshPending = false;
                RecreateAllWidgetWindows();
                return 0;
            }
            break;
        case WM_AUDIO_FINISHED:
            if (window == hController) {
                Widget* finishedWidget = FindWidgetById(static_cast<int>(wParam));
                ULONG generation = static_cast<ULONG>(lParam);
                if (finishedWidget != nullptr && finishedWidget->audioGeneration == generation) {
                    if (finishedWidget->audioStopEvent != nullptr) {
                        CloseHandle(finishedWidget->audioStopEvent);
                        finishedWidget->audioStopEvent = nullptr;
                    }
                    if (finishedWidget->audioMuteEvent != nullptr) {
                        CloseHandle(finishedWidget->audioMuteEvent);
                        finishedWidget->audioMuteEvent = nullptr;
                    }
                }
                return 0;
            }
            break;
        case WM_SETTINGS_AUDIO_FINISHED:
            if (window == hController) {
                ULONG generation = static_cast<ULONG>(lParam);
                if (settingsPreviewGeneration == generation) {
                    if (settingsPreviewStopEvent != nullptr) {
                        CloseHandle(settingsPreviewStopEvent);
                        settingsPreviewStopEvent = nullptr;
                    }
                    if (settingsPreviewMuteEvent != nullptr) {
                        CloseHandle(settingsPreviewMuteEvent);
                        settingsPreviewMuteEvent = nullptr;
                    }
                }
                return 0;
            }
            break;
        case WM_TIME_SIGNAL_FINISHED:
            if (window == hController) {
                FinishTimeSignalPlayback();
                return 0;
            }
            break;
        case WM_NTP_RESULT:
            if (window == hController) {
                std::unique_ptr<NtpThreadResult> result(reinterpret_cast<NtpThreadResult*>(lParam));
                ntpQueryRunning = false;
                if (hNtpThread != nullptr) {
                    CloseHandle(hNtpThread);
                    hNtpThread = nullptr;
                }
                if (result != nullptr && result->generation != ntpGeneration.load()) {
                    StartNtpSynchronization(true);
                    UpdateNtpSettingsControls();
                    return 0;
                }
                if (result != nullptr && result->success) {
                    ntpOffset100Nanoseconds = result->offset100Nanoseconds;
                    ntpActiveServer = result->server;
                    ntpTimeValid = true;
                    ntpHasSynchronized = true;
                    ntpLastQueryFailed = false;
                    nextNtpAttemptTick = GetTickCount64() + 3610000 - GetNtpHourPosition();
                    CheckTimeSignals();
                    for (size_t index = 0; index < widgets.size(); index++) {
                        widgets[index]->lastRenderKey = -1;
                        widgets[index]->rendered = false;
                        if (widgets[index]->config.visible) {
                            RenderWidget(widgets[index].get());
                        }
                    }
                } else {
                    ntpLastQueryFailed = true;
                    if (!ntpTimeValid) {
                        ntpActiveServer.clear();
                    }
                }
                UpdateNtpSettingsControls();
                return 0;
            }
            break;
        case WM_CTLCOLORSTATIC:
        {
            HDC dc = reinterpret_cast<HDC>(wParam);
            if (IsSettingsPageWindow(window)) {
                int colorIndex = themesDisabled ? COLOR_BTNFACE : COLOR_WINDOW;
                SetTextColor(dc, GetSysColor(COLOR_WINDOWTEXT));
                SetBkColor(dc, GetSysColor(colorIndex));
                SetBkMode(dc, OPAQUE);
                return reinterpret_cast<LRESULT>(GetSysColorBrush(colorIndex));
            }
            break;
        }
        case WM_CTLCOLORBTN:
        {
            HWND control = reinterpret_cast<HWND>(lParam);
            bool tabControlChild = std::find(generalControls.begin(), generalControls.end(), control) !=
                generalControls.end()
                || std::find(appearanceControls.begin(), appearanceControls.end(), control) != appearanceControls.end()
                || std::find(alarmControls.begin(), alarmControls.end(), control) != alarmControls.end()
                || std::find(timeSignalControls.begin(), timeSignalControls.end(), control) != timeSignalControls.end()
                || std::find(timeControls.begin(), timeControls.end(), control) != timeControls.end()
                || std::find(applicationControls.begin(), applicationControls.end(), control) !=
                applicationControls.end();
            LONG_PTR style = GetWindowLongPtrW(control, GWL_STYLE);
            UINT buttonType = static_cast<UINT>(style & BS_TYPEMASK);
            if (tabControlChild
                    && (buttonType == BS_CHECKBOX
                        || buttonType == BS_AUTOCHECKBOX
                        || buttonType == BS_3STATE
                        || buttonType == BS_AUTO3STATE)) {
                int colorIndex = themesDisabled ? COLOR_BTNFACE : COLOR_WINDOW;
                SetBkColor(reinterpret_cast<HDC>(wParam), GetSysColor(colorIndex));
                SetBkMode(reinterpret_cast<HDC>(wParam), OPAQUE);
                return reinterpret_cast<LRESULT>(GetSysColorBrush(colorIndex));
            }
            break;
        }
        case WM_DRAWITEM:
        {
            DRAWITEMSTRUCT* item = reinterpret_cast<DRAWITEMSTRUCT*>(lParam);
            bool panelLink = widget != nullptr && item != nullptr
                && (item->hwndItem == widget->panelDateLink || item->hwndItem == widget->panelTimeZoneLink);
            if (panelLink) {
                int savedState = SaveDC(item->hDC);
                bool dateLink = item->hwndItem == widget->panelDateLink;
                HBRUSH background = CreateSolidBrush(PanelBackgroundColor(widget));
                FillRect(item->hDC, &item->rcItem, background);
                DeleteObject(background);
                const FontSelection& selection = dateLink ? widget->config.panelTopFont : widget->config.panelBottomFont;
                bool hot = dateLink ? widget->panelDateHot : widget->panelTimeZoneHot;
                bool focused = GetFocus() == item->hwndItem;
                HFONT font = dateLink ? widget->panelDateFont : widget->panelTimeZoneFont;
                HFONT hotFont = nullptr;
                if ((hot || focused) && !selection.underline) {
                    FontSelection hotSelection = selection;
                    hotSelection.underline = true;
                    hotFont = CreatePanelFont(hotSelection, widget->config.fontAntialiasing);
                    if (hotFont != nullptr) {
                        font = hotFont;
                    }
                }
                if (font != nullptr) {
                    SelectObject(item->hDC, font);
                }
                SetBkMode(item->hDC, TRANSPARENT);
                SetTextColor(item->hDC, RGB(0, 83, 184));
                std::wstring text = GetControlText(item->hwndItem);
                RECT textRect = item->rcItem;
                DrawTextW(item->hDC, text.c_str(), static_cast<int>(text.size()), &textRect,
                    DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
                if (focused) {
                    RECT focusRect = item->rcItem;
                    InflateRect(&focusRect, -1, -1);
                    DrawPanelLinkFocusRect(item->hDC, focusRect);
                }
                if (hotFont != nullptr) {
                    DeleteObject(hotFont);
                }
                RestoreDC(item->hDC, savedState);
                return TRUE;
            }
            if (window == hTimeSignalPage && item != nullptr && item->CtlID == ID_TIME_SIGNAL_NOTE) {
                int savedState = SaveDC(item->hDC);
                int colorIndex = themesDisabled ? COLOR_BTNFACE : COLOR_WINDOW;
                FillRect(item->hDC, &item->rcItem, GetSysColorBrush(colorIndex));
                SetBkMode(item->hDC, TRANSPARENT);
                SetTextColor(item->hDC,
                    GetSysColor(IsWindowEnabled(item->hwndItem) ? COLOR_WINDOWTEXT : COLOR_GRAYTEXT));
                HFONT font = reinterpret_cast<HFONT>(SendMessageW(item->hwndItem, WM_GETFONT, 0, 0));
                if (font != nullptr) {
                    SelectObject(item->hDC, font);
                }
                std::wstring text = GetControlText(item->hwndItem);
                RECT textRect = item->rcItem;
                DrawWordWrappedText(item->hDC, text, textRect);
                RestoreDC(item->hDC, savedState);
                return TRUE;
            }
            break;
        }
        case WM_ERASEBKGND:
            if (IsSettingsPageWindow(window)) {
                RECT rect = {};
                GetClientRect(window, &rect);
                int colorIndex = themesDisabled ? COLOR_BTNFACE : COLOR_WINDOW;
                FillRect(reinterpret_cast<HDC>(wParam), &rect, GetSysColorBrush(colorIndex));
                return 1;
            }
            if (widget != nullptr) {
                bool requiresBackground = widget->config.type == WIDGET_PANEL
                    || widget->config.type == WIDGET_CALENDAR
                    || widget->config.type == WIDGET_FULLSCREEN
                    || widget->config.type == WIDGET_DIGITAL && !widget->config.transparentBackground;
                if (requiresBackground) {
                    return 1;
                }
            }
            break;
        case WM_PRINTCLIENT:
            if (IsSettingsPageWindow(window)) {
                RECT rect = {};
                GetClientRect(window, &rect);
                int colorIndex = themesDisabled ? COLOR_BTNFACE : COLOR_WINDOW;
                FillRect(reinterpret_cast<HDC>(wParam), &rect, GetSysColorBrush(colorIndex));
                return 0;
            }
            break;
        case WM_PAINT:
            if (widget != nullptr && widget->config.type == WIDGET_CALENDAR) {
                PAINTSTRUCT paint = {};
                HDC dc = BeginPaint(window, &paint);
                RECT frameRect = {};
                GetClientRect(window, &frameRect);
                FillRect(dc, &frameRect, GetSysColorBrush(COLOR_WINDOW));
                EndPaint(window, &paint);
                return 0;
            }
            if (widget != nullptr && (widget->config.type == WIDGET_DIGITAL && !widget->config.transparentBackground
                || widget->config.type == WIDGET_FULLSCREEN)) {
                PAINTSTRUCT paint = {};
                HDC dc = BeginPaint(window, &paint);
                PaintWidgetBuffered(widget, window, dc, false);
                EndPaint(window, &paint);
                return 0;
            }
            if (widget != nullptr && widget->config.type == WIDGET_PANEL) {
                PAINTSTRUCT paint = {};
                HDC dc = BeginPaint(window, &paint);
                PaintWidgetBuffered(widget, window, dc, true);
                EndPaint(window, &paint);
                return 0;
            }
            break;
        case WM_HSCROLL:
            if (window == hAppearancePage || window == hApplicationPage || window == hAlarmPage) {
                return SendMessageW(hSettings, WM_HSCROLL, wParam, lParam);
            }
            if (window == hSettings) {
                if (lParam == 0 && ScrollSettingsWindow(SB_HORZ, LOWORD(wParam))) {
                    return 0;
                }
                HWND trackBar = reinterpret_cast<HWND>(lParam);
                if (trackBar == nullptr) {
                    break;
                }
                if (trackBar == hAlarmVolumeTrackBar) {
                    UpdateAlarmVolumeControls();
                    UpdateSettingsApplyButton();
                    return 0;
                }
                if (trackBar == hTimeSignalVolumeTrackBar) {
                    UpdateTimeSignalVolumeControls();
                    UpdateSettingsApplyButton();
                    return 0;
                }
                if (trackBar == hOpacityTrackBar
                        || trackBar == hFontSizeTrackBar
                        || trackBar == hPaddingTrackBar
                        || trackBar == hBorderTrackBar
                        || trackBar == hBorderWidthTrackBar) {
                    if (trackBar == hBorderTrackBar) {
                        SetControlEnabled(hBorderColorButton,
                            SendMessageW(trackBar, TBM_GETPOS, 0, 0) == DIGITAL_BORDER_TOOL_WINDOW);
                    }
                    UpdateAppearanceSliderLabels(trackBar);
                    PreviewSelectedWidgetAppearance(false);
                    UpdateSettingsApplyButton();
                    return 0;
                }
            }
            break;
        case WM_VSCROLL:
            if (window == hSettings && lParam == 0 && ScrollSettingsWindow(SB_VERT, LOWORD(wParam))) {
                return 0;
            }
            break;
        case WM_MOUSEWHEEL:
            if (IsSettingsPageWindow(window)) {
                return SendMessageW(hSettings, WM_MOUSEWHEEL, wParam, lParam);
            }
            if (window == hSettings && ScrollSettingsWheel(wParam)) {
                return 0;
            }
            break;
        case WM_COMMAND:
        {
            if (IsSettingsPageWindow(window)) {
                return SendMessageW(hSettings, WM_COMMAND, wParam, lParam);
            }
            int id = LOWORD(wParam);
            int notification = HIWORD(wParam);
            if (window == hSettings) {
                if (notification == CBN_DROPDOWN) {
                    HWND control = reinterpret_cast<HWND>(lParam);
                    wchar_t className[32] = {};
                    GetClassNameW(control, className, ARRAYSIZE(className));
                    if (_wcsicmp(className, WC_COMBOBOXW) == 0) {
                        UpdateComboBoxDropDownWidth(control);
                        return 0;
                    }
                }
                HandleSettingsCommand(id, notification);
                UpdateSettingsApplyButton();
                return 0;
            }
            if (window == hHelp || window == hAbout) {
                if (id == ID_INFO_CLOSE) {
                    SendMessageW(window, WM_CLOSE, 0, 0);
                }
                return 0;
            }
            if (widget != nullptr
                    && id == ID_PANEL_DATE_LINK
                    && notification == BN_CLICKED
                    && reinterpret_cast<HWND>(lParam) == widget->panelDateLink) {
                SelectCalendarToday(widget);
                return 0;
            }
            if (widget != nullptr
                    && id == ID_PANEL_TIME_ZONE_LINK
                    && notification == BN_CLICKED
                    && reinterpret_cast<HWND>(lParam) == widget->panelTimeZoneLink) {
                OpenDateTimeControlPanel(widget->window);
                return 0;
            }
            if (window == hController) {
                if (id == ID_MENU_SETTINGS) {
                    ShowSettingsWindow();
                } else if (id == ID_MENU_SHOW_ALL) {
                    SetAllVisible(true);
                } else if (id == ID_MENU_HIDE_ALL) {
                    SetAllVisible(false);
                } else if (id == ID_MENU_ARRANGE_WIDGETS) {
                    ArrangeVisibleWidgets(nullptr);
                } else if (id == ID_MENU_STOP_ALARM) {
                    StopAllAlarms();
                } else if (id == ID_MENU_MUTE) {
                    ToggleAllWidgetSounds();
                } else if (id == ID_MENU_HELP) {
                    ShowInformationWindow(true);
                } else if (id == ID_MENU_ABOUT) {
                    ShowInformationWindow(false);
                } else if (id == ID_MENU_EXIT) {
                    DestroyWindow(hController);
                }
                return 0;
            }
            break;
        }
        case WM_NOTIFY:
            if (window == hAbout
                    && hAboutTooltip != nullptr
                    && reinterpret_cast<NMHDR*>(lParam)->hwndFrom == hAboutTooltip
                    && reinterpret_cast<NMHDR*>(lParam)->code == TTN_GETDISPINFOW) {
                NMTTDISPINFOW* information = reinterpret_cast<NMTTDISPINFOW*>(lParam);
                information->lpszText = const_cast<wchar_t*>(ABOUT_VISIT_TOOLTIP[appLanguage]);
                return 0;
            }
            if (window == hAbout
                    && reinterpret_cast<NMHDR*>(lParam)->idFrom == ID_INFO_LINK
                    && (reinterpret_cast<NMHDR*>(lParam)->code == NM_CLICK
                        || reinterpret_cast<NMHDR*>(lParam)->code == NM_RETURN)) {
                ShellExecuteW(hAbout, L"open", ABOUT_WEBSITE_URL, nullptr, nullptr, SW_SHOWNORMAL);
                return 0;
            }
            if (widget != nullptr
                    && widget->panelDateTooltip != nullptr
                    && reinterpret_cast<NMHDR*>(lParam)->hwndFrom == widget->panelDateTooltip
                    && reinterpret_cast<NMHDR*>(lParam)->code == TTN_GETDISPINFOW) {
                NMTTDISPINFOW* information = reinterpret_cast<NMTTDISPINFOW*>(lParam);
                information->lpszText = const_cast<wchar_t*>(PANEL_TODAY_TOOLTIP[widget->config.language]);
                return 0;
            }
            if (widget != nullptr
                    && widget->calendarChild != nullptr
                    && reinterpret_cast<NMHDR*>(lParam)->hwndFrom == widget->calendarChild
                    && reinterpret_cast<NMHDR*>(lParam)->code == MCN_SELECT) {
                NMSELCHANGE* selection = reinterpret_cast<NMSELCHANGE*>(lParam);
                CopyWidgetDate(widget, selection->stSelStart);
                return 0;
            }
            if (window == hSettings
                    && hTabs != nullptr
                    && reinterpret_cast<NMHDR*>(lParam)->idFrom == ID_TABS
                    && reinterpret_cast<NMHDR*>(lParam)->code == TCN_SELCHANGE) {
                settingsTab = std::clamp(TabCtrl_GetCurSel(hTabs), 0, SETTINGS_TAB_COUNT - 1);
                ShowSettingsTab(settingsTab);
                return 0;
            }
            break;
        case WM_TRAYICON:
            if (window == hController) {
                UINT event = LOWORD(lParam);
                bool contextMenuRequested = false;
                bool toggleRequested = false;
                if (trayUsesVersion4) {
                    contextMenuRequested = event == WM_CONTEXTMENU;
                    toggleRequested = event == NIN_SELECT || event == NIN_KEYSELECT;
                } else {
                    contextMenuRequested = event == WM_RBUTTONUP;
                    toggleRequested = event == WM_LBUTTONUP;
                }
                if (contextMenuRequested) {
                    ShowTrayContextMenu();
                } else if (toggleRequested) {
                    ToggleAllFromTray();
                }
                return 0;
            }
            break;
        case WM_SHOW_EXISTING:
            if (window == hController) {
                bool anyVisible = false;
                for (size_t index = 0; index < widgets.size(); index++) {
                    if (widgets[index]->config.visible) {
                        anyVisible = true;
                        SetWindowPos(widgets[index]->window, HWND_TOPMOST, 0, 0, 0, 0,
                            SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
                        for (size_t windowIndex = 0;
                                windowIndex < widgets[index]->fullscreenWindows.size();
                                windowIndex++) {
                            SetWindowPos(widgets[index]->fullscreenWindows[windowIndex], HWND_TOPMOST, 0, 0, 0, 0,
                                SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
                        }
                        if (!widgets[index]->config.topMost && widgets[index]->config.type != WIDGET_FULLSCREEN) {
                            SetWindowPos(widgets[index]->window, HWND_NOTOPMOST, 0, 0, 0, 0,
                                SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
                        }
                    }
                }
                if (!anyVisible) {
                    RestoreLastHiddenWidgets();
                } else {
                    RefreshFullscreenPresentation();
                }
                if (hSettings != nullptr) {
                    SetForegroundWindowEx(hSettings);
                } else {
                    for (size_t index = 0; index < widgets.size(); index++) {
                        if (widgets[index]->config.visible) {
                            SetForegroundWindowEx(widgets[index]->window);
                            break;
                        }
                    }
                }
                return 0;
            }
            break;
        case WM_TIMER:
            if (window == hController && wParam == TIMER_REFRESH) {
                static ULONGLONG previousSecond = static_cast<ULONGLONG>(-1);
                static ULONGLONG previousHalfSecond = static_cast<ULONGLONG>(-1);
                static ULONGLONG previousIdentifyFrame = static_cast<ULONGLONG>(-1);
                ULONGLONG tick = GetTickCount64();
                UpdateFullscreenCursor();
                StartNtpSynchronization(false);
                CheckTimeSignals();
                UpdateSettingsApplyButton();
                ULONGLONG second = tick / 1000;
                ULONGLONG halfSecond = tick / 500;
                ULONGLONG identifyFrame = tick / 200;
                for (size_t index = 0; index < widgets.size(); index++) {
                    Widget* current = widgets[index].get();
                    if (current->copyTooltip != nullptr && tick >= current->copyTooltipEndTick) {
                        if (IsWindow(current->copyTooltip)) {
                            DestroyWindow(current->copyTooltip);
                        }
                        current->copyTooltip = nullptr;
                    }
                }
                bool flashChanged = halfSecond != previousHalfSecond;
                if (flashChanged) {
                    previousHalfSecond = halfSecond;
                    for (size_t index = 0; index < widgets.size(); index++) {
                        Widget* current = widgets[index].get();
                        if (current->alarmActive) {
                            current->flashPhase = !current->flashPhase;
                        }
                    }
                }
                if (identifyFrame != previousIdentifyFrame) {
                    previousIdentifyFrame = identifyFrame;
                    for (size_t index = 0; index < widgets.size(); index++) {
                        Widget* current = widgets[index].get();
                        if (!current->identifyActive) {
                            continue;
                        }
                        if (tick >= current->identifyEndTick) {
                            FinishWidgetIdentification(current);
                        } else {
                            current->identifyPhase = !current->identifyPhase;
                            RenderWidgetIdentification(current);
                        }
                    }
                }
                bool secondChanged = second != previousSecond;
                if (secondChanged) {
                    previousSecond = second;
                    for (size_t index = 0; index < widgets.size(); index++) {
                        UpdateCalendarDate(widgets[index].get());
                        CheckWidgetAlarm(widgets[index].get());
                    }
                }
                for (size_t index = 0; index < widgets.size(); index++) {
                    Widget* current = widgets[index].get();
                    if (!current->config.visible) {
                        continue;
                    }
                    SYSTEMTIME displayed = {};
                    GetDisplayedTime(current->config, &displayed);
                    bool renderSeconds = current->config.showSeconds;
                    if (current->config.type == WIDGET_ANALOG && !AnalogClockSupportsSeconds(current->config.size)) {
                        renderSeconds = false;
                    }
                    int renderKey = renderSeconds
                        ? displayed.wHour * 3600 + displayed.wMinute * 60 + displayed.wSecond
                        : displayed.wHour * 60 + displayed.wMinute;
                    bool alarmFrameChanged = current->alarmActive && flashChanged;
                    if (current->lastRenderKey != renderKey || alarmFrameChanged || !current->rendered) {
                        current->lastRenderKey = renderKey;
                        RenderWidget(current);
                    }
                }
                return 0;
            }
            break;
        case WM_LBUTTONDOWN:
            if (widget != nullptr) {
                ULONGLONG tick = GetTickCount64();
                if (widget->alarmActive || widget->audioStopEvent != nullptr) {
                    StopWidgetAlarm(widget);
                    widget->alarmStoppedTick = tick;
                    return 0;
                }
                if (widget->alarmStoppedTick != 0 && tick - widget->alarmStoppedTick <= GetDoubleClickTime()) {
                    return 0;
                }
                widget->alarmStoppedTick = 0;
                if (widget->config.type == WIDGET_FULLSCREEN && !widget->fullscreenPreview) {
                    SetForegroundWindow(window);
                    SetFocus(window);
                    return 0;
                }
                POINT cursor = {};
                GetCursorPos(&cursor);
                RECT rect = {};
                GetWindowRect(window, &rect);
                widget->dragOffset.x = cursor.x - rect.left;
                widget->dragOffset.y = cursor.y - rect.top;
                widget->dragging = true;
                SetCapture(window);
                return 0;
            }
            break;
        case WM_MOUSEMOVE:
            if (widget != nullptr && widget->dragging && wParam & MK_LBUTTON) {
                widget->lastAnalogClickTick = 0;
                POINT cursor = {};
                GetCursorPos(&cursor);
                POINT position = { cursor.x - widget->dragOffset.x, cursor.y - widget->dragOffset.y };
                RECT rect = {};
                MONITORINFO monitorInfo = { sizeof(monitorInfo) };
                HMONITOR monitor = MonitorFromPoint(cursor, MONITOR_DEFAULTTONEAREST);
                if (snapWidgetsToWorkArea && GetWindowRect(window, &rect) && GetMonitorInfoW(monitor, &monitorInfo)) {
                    position = SnapWidgetPositionToWorkArea(rect, monitorInfo.rcWork, position, WORK_AREA_SNAP_DISTANCE);
                }
                SetWindowPos(window, nullptr, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                return 0;
            }
            break;
        case WM_LBUTTONUP:
            if (widget != nullptr && widget->dragging) {
                widget->dragging = false;
                ReleaseCapture();
                if (widget->fullscreenPreview) {
                    SaveFullscreenPreviewPosition(widget);
                } else {
                    SaveWidgetPosition(widget);
                }
                return 0;
            }
            break;
        case WM_CAPTURECHANGED:
            if (widget != nullptr && widget->dragging) {
                widget->dragging = false;
                if (widget->fullscreenPreview) {
                    SaveFullscreenPreviewPosition(widget);
                } else {
                    SaveWidgetPosition(widget);
                }
                return 0;
            }
            break;
        case WM_LBUTTONDBLCLK:
            if (widget != nullptr
                    && widget->alarmStoppedTick != 0
                    && GetTickCount64() - widget->alarmStoppedTick <= GetDoubleClickTime()) {
                return 0;
            }
            if (widget != nullptr && widget->config.type == WIDGET_PANEL) {
                RECT clockRect = {};
                if (widget->analogChild == nullptr || !GetWindowRect(widget->analogChild, &clockRect)) {
                    return 0;
                }
                MapWindowPoints(nullptr, window, reinterpret_cast<POINT*>(&clockRect), 2);
                POINT point = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
                if (!PtInRect(&clockRect, point)) {
                    return 0;
                }
            }
            if (widget != nullptr && widget->config.type != WIDGET_CALENDAR) {
                HandleWidgetMenuCommand(widget, ID_MENU_SECONDS);
                return 0;
            }
            break;
        case WM_RBUTTONUP:
        case WM_CONTEXTMENU:
            if (widget != nullptr) {
                ShowWidgetContextMenu(widget, window);
                return 0;
            }
            break;
        case WM_KEYDOWN:
            if ((window == hHelp || window == hAbout) && wParam == VK_ESCAPE) {
                SendMessageW(window, WM_CLOSE, 0, 0);
                return 0;
            }
            if (widget != nullptr) {
                if (wParam == VK_ESCAPE) {
                    if (widget->alarmActive || widget->audioStopEvent != nullptr) {
                        StopWidgetAlarm(widget);
                    } else {
                        SetWidgetVisible(widget, false);
                    }
                } else if (wParam == VK_F1) {
                    ShowInformationWindow(true);
                } else if (wParam == L'B') {
                    ShowSettingsWindow();
                }
                return 0;
            }
            break;
        case WM_CLOSE:
            if (window == hSettings) {
                CloseSettingsWindow();
                return 0;
            }
            if (window == hHelp) {
                SaveFormPosition(hHelp, &helpX, &helpY);
                DestroyWindow(hHelp);
                hHelp = nullptr;
                SaveAllSettings();
                return 0;
            }
            if (window == hAbout) {
                SaveFormPosition(hAbout, &aboutX, &aboutY);
                if (hAboutTooltip != nullptr) {
                    DestroyWindow(hAboutTooltip);
                    hAboutTooltip = nullptr;
                }
                DestroyWindow(hAbout);
                hAbout = nullptr;
                SaveAllSettings();
                return 0;
            }
            if (widget != nullptr) {
                SetWidgetVisible(widget, false);
                return 0;
            }
            break;
        case WM_DESTROY:
            if (IsSettingsPageWindow(window)) {
                for (HWND control = GetWindow(window, GW_CHILD);
                        control != nullptr;
                        control = GetWindow(control, GW_HWNDNEXT)) {
                    RemovePropW(control, SETTINGS_COMBO_HEIGHT_PROPERTY);
                }
            }
            if (widget != nullptr && window == widget->window) {
                widget->panelDateTooltip = nullptr;
            }
            if (window == hController) {
                StopTimeSignalVolumePreview();
                RestoreSettingsAppearancePreview();
                StopSettingsPreview();
                StopTimeSignalPlayback();
                KillTimer(hController, TIMER_REFRESH);
                RemoveTrayIcon();
                DestroyWidgetWindows();
                SaveAllSettings();
                PostQuitMessage(0);
                return 0;
            }
            break;
    }
    return DefWindowProcW(window, message, wParam, lParam);
}

/// Enforces one application instance, initializes services and windows, and runs the message loop with custom keyboard
/// navigation.
/// Releases rendering, synchronization, and process resources before returning the message-loop exit code.
int APIENTRY wWinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE previousInstance, _In_ LPWSTR commandLine,
        _In_ int showCommand) {
    UNREFERENCED_PARAMETER(previousInstance);
    UNREFERENCED_PARAMETER(commandLine);
    UNREFERENCED_PARAMETER(showCommand);
    hInstance = instance;
    hSingleInstanceMutex = CreateMutexW(nullptr, FALSE, L"CalClock.MultiWidget.Instance");
    if (hSingleInstanceMutex != nullptr && GetLastError() == ERROR_ALREADY_EXISTS) {
        HWND existing = FindWindowW(CLASS_NAME, CONTROLLER_TITLE);
        if (existing != nullptr) {
            SendMessageW(existing, WM_SHOW_EXISTING, 0, 0);
        }
        CloseHandle(hSingleInstanceMutex);
        return 0;
    }
    INITCOMMONCONTROLSEX controls = {
        sizeof(controls),
        ICC_WIN95_CLASSES | ICC_TAB_CLASSES | ICC_DATE_CLASSES | ICC_LINK_CLASS
    };
    InitCommonControlsEx(&controls);
    WSADATA winsockData = {};
    winsockReady = WSAStartup(MAKEWORD(2, 2), &winsockData) == 0;
    InstallCalendarLocaleHook();
    LoadAllSettings();
    bool anyWidgetVisible = false;
    for (const std::unique_ptr<Widget>& widget : widgets) {
        if (widget->config.visible) {
            anyWidgetVisible = true;
            break;
        }
    }
    if (!anyWidgetVisible && !widgets.empty()) {
        widgets[0]->config.visible = true;
    }
    SetThemeAppProperties(themesDisabled
        ? STAP_ALLOW_NONCLIENT
        : STAP_ALLOW_NONCLIENT | STAP_ALLOW_CONTROLS | STAP_ALLOW_WEBCONTENT);
    WNDCLASSEXW blackoutClass = {};
    blackoutClass.cbSize = sizeof(blackoutClass);
    blackoutClass.lpfnWndProc = BlackoutWindowProc;
    blackoutClass.hInstance = instance;
    blackoutClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    blackoutClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
    blackoutClass.lpszClassName = BLACKOUT_CLASS_NAME;
    if (!RegisterClassExW(&blackoutClass)) {
        if (winsockReady) {
            WSACleanup();
        }
        return 1;
    }
    WNDCLASSEXW windowClass = {};
    windowClass.cbSize = sizeof(windowClass);
    windowClass.style = CS_DBLCLKS;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = instance;
    windowClass.hIcon = LoadIconW(instance, MAKEINTRESOURCEW(IDI_CLOCK));
    windowClass.hIconSm = windowClass.hIcon;
    windowClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    windowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1);
    windowClass.lpszClassName = CLASS_NAME;
    if (!RegisterClassExW(&windowClass)) {
        if (winsockReady) {
            WSACleanup();
        }
        return 1;
    }
    taskbarCreatedMessage = RegisterWindowMessageW(L"TaskbarCreated");
    hController = CreateWindowExW(WS_EX_TOOLWINDOW, CLASS_NAME, CONTROLLER_TITLE, WS_POPUP,
        0, 0, 0, 0, nullptr, nullptr, instance, nullptr);
    if (hController == nullptr) {
        if (winsockReady) {
            WSACleanup();
        }
        return 2;
    }
    InitializeDirectTextRendering();
    for (size_t index = 0; index < widgets.size(); index++) {
        CreateWidgetWindow(widgets[index].get());
    }
    RefreshFullscreenPresentation();
    AddTrayIcon();
    SetTimer(hController, TIMER_REFRESH, 100, nullptr);
    SaveAllSettings();
    StartNtpSynchronization(true);
    MSG message = {};
    while (GetMessageW(&message, nullptr, 0, 0) > 0) {
        Widget* inputWidget = WidgetFromInputWindow(message.hwnd);
        if ((message.message == WM_KEYDOWN || message.message == WM_SYSKEYDOWN)
                && message.wParam == VK_ESCAPE
                && inputWidget != nullptr
                && (inputWidget->alarmActive || inputWidget->audioStopEvent != nullptr)) {
            StopWidgetAlarm(inputWidget);
            continue;
        }
        if ((message.message == WM_KEYDOWN || message.message == WM_SYSKEYDOWN)
            && message.wParam == VK_ESCAPE && HideFullscreenWidgetsFromEscape()) {
            continue;
        }
        if (message.message == WM_KEYDOWN
                && message.wParam == L'M'
                && (message.lParam & 1LL << 30) == 0
                && inputWidget != nullptr) {
            ToggleAllWidgetSounds();
            continue;
        }
        if (inputWidget != nullptr
                && inputWidget->config.type == WIDGET_PANEL
                && IsDialogMessageW(inputWidget->window, &message)) {
            continue;
        }
        if (message.message == WM_KEYDOWN
                && message.wParam == VK_TAB
                && GetKeyState(VK_CONTROL) >= 0
                && hTabs != nullptr) {
            HWND focused = GetFocus();
            HWND firstPageControl = GetSettingsPageBoundaryControl(false);
            HWND lastPageControl = GetSettingsPageBoundaryControl(true);
            HWND importButton = GetDlgItem(hSettings, ID_IMPORT_SETTINGS);
            HWND lastSettingsButton = GetDlgItem(hSettings, ID_APPLY);
            if (lastSettingsButton == nullptr || !IsWindowEnabled(lastSettingsButton)) {
                lastSettingsButton = GetDlgItem(hSettings, ID_CANCEL);
            }
            HWND target = nullptr;
            bool backwards = GetKeyState(VK_SHIFT) < 0;
            HWND activePage = GetActiveSettingsPage();
            if (activePage != nullptr && (focused == activePage || IsChild(activePage, focused))) {
                std::vector<HWND> tabControls = GetSettingsTabOrder();
                for (size_t index = 0; index < tabControls.size(); index++) {
                    if (focused != tabControls[index] && !IsChild(tabControls[index], focused)) {
                        continue;
                    }
                    if (backwards) {
                        target = index == 0 ? hTabs : tabControls[index - 1];
                    } else {
                        target = index + 1 == tabControls.size() ? importButton : tabControls[index + 1];
                    }
                    break;
                }
            }
            if (target == nullptr && !backwards) {
                if (focused == hTabs) {
                    target = firstPageControl;
                } else if (focused == lastPageControl) {
                    target = importButton;
                } else if (focused == lastSettingsButton) {
                    target = hAddType;
                }
            } else if (target == nullptr) {
                if (focused == firstPageControl) {
                    target = hTabs;
                } else if (focused == importButton) {
                    target = lastPageControl;
                } else if (focused == hAddType) {
                    target = lastSettingsButton;
                }
            }
            if (target != nullptr && IsWindowVisible(target) && IsWindowEnabled(target)) {
                SetFocus(target);
                continue;
            }
        }
        if (hSettings != nullptr && IsDialogMessageW(hSettings, &message)) {
            continue;
        }
        if (hHelp != nullptr && IsDialogMessageW(hHelp, &message)) {
            continue;
        }
        if (hAbout != nullptr && IsDialogMessageW(hAbout, &message)) {
            continue;
        }
        TranslateMessage(&message);
        DispatchMessageW(&message);
    }
    ShutdownAnalogClockHost();
    if (hUiFont != nullptr) {
        DeleteObject(hUiFont);
    }
    if (hAboutFont != nullptr) {
        DeleteObject(hAboutFont);
    }
    ShutdownDirectTextRendering();
    if (hSingleInstanceMutex != nullptr) {
        CloseHandle(hSingleInstanceMutex);
        hSingleInstanceMutex = nullptr;
    }
    bool ntpThreadFinished = StopNtpSynchronization();
    if (winsockReady && ntpThreadFinished) {
        WSACleanup();
    }
    return static_cast<int>(message.wParam);
}
