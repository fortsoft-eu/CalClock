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
 * Last modified for version 1.7.0.0
 */

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "resource.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <winver.h>
#include "AboutForm.h"
#include "AlarmActions.h"
#include "AudioOutput.h"
#include "AnalogClockHost.h"
#include "CalendarLocaleScope.h"
#include "CalClock.h"
#include "ClockTime.h"
#include "DateFormats.h"
#include "HelpForm.h"
#include "Localization.h"
#include "MonitorInfo.h"
#include "NtpClient.h"
#include "PersistWindowState.h"
#include "SelectionEdit.h"
#include "SettingsStorage.h"
#include "SettingsEdit.h"
#include "SystemDialogTemplate.h"
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
#include <dwmapi.h>
#include <functional>
#include <memory>
#include <shellapi.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <string>
#include <utility>
#include <usp10.h>
#include <uxtheme.h>
#include <vssym32.h>
#include <vector>

#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Comdlg32.lib")
#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "UxTheme.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Version.lib")
#pragma comment(lib, "Dwmapi.lib")

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

/// Stores the selected font's ascent, descent, and spacing for plain UI text.
struct UiTextLine {
    LONG ascent;
    LONG descent;
    LONG gap;
};

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

/// Retains a draft control value while the Settings controls are recreated for a font preview.
struct SettingsControlValue {
    int page;
    int id;
    UINT message;
    WPARAM parameter;
    LPARAM value;
    std::wstring text;
};

/// Retains stable monitor identity, metadata and displayed text independently of sorted row positions.
struct MonitorListEntry {
    DisplayMonitor monitor;
    MonitorDetails details;
    std::wstring text[MONITOR_COLUMN_COUNT];
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

/// Groups regular and alarm sources sharing one target and output, including canceled alarm contributors.
struct TimeSignalSourceGroup {
    ULONGLONG target = 0;
    std::wstring outputDevice;
    std::vector<int> regularWidgetIds;
    std::vector<int> alarmWidgetIds;
    std::vector<int> cancelledAlarmWidgetIds;
};

/// Identifies a widget's proposed target, output, and whether it comes from a recurring signal or alarm.
struct TimeSignalCandidate {
    ULONGLONG target;
    std::wstring outputDevice;
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

/// Caches a native calendar's measured size together with the locale, font, theme, and style options that
/// affect it.
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

struct PanelNoticeLayout {
    RECT separator = {};
    RECT icon = {};
    RECT text = {};
};

/// Contains the panel's client size and rectangles for its header, calendar, clock faces, captions, times,
/// days, and footer.
struct PanelLayout {
    SIZE clientSize = {};
    RECT header = {};
    RECT calendar = {};
    RECT clocks[ADDITIONAL_CLOCK_COUNT + 1] = {};
    RECT names[ADDITIONAL_CLOCK_COUNT] = {};
    RECT times[ADDITIONAL_CLOCK_COUNT + 1] = {};
    RECT days[ADDITIONAL_CLOCK_COUNT + 1] = {};
    std::vector<PanelNoticeLayout> notices;
    RECT noticeBottomSeparator = {};
    RECT footer = {};
};

/// Retains native Unicode line-break analysis for the last information-edit text.
struct InformationWordBreakState {
    SCRIPT_STRING_ANALYSIS analysis = nullptr;
    std::wstring text;
};

/// Window classes and product constants
const wchar_t CLASS_NAME[] = L"CalClockMultiWidgetWindow";
const wchar_t BLACKOUT_CLASS_NAME[] = L"CalClockBlackoutWindow";
const wchar_t CONTROLLER_TITLE[] = L"CalClockMessageController";
const wchar_t WIDGET_CLIPBOARD_FORMAT[] = L"FortSoft.CalClock.Widgets.XML.v1";
const wchar_t SETTINGS_FIELD_LABEL_PROPERTY[] = L"CalClock.SettingsFieldLabel";
const wchar_t SETTINGS_COLOR_PREVIEW_PROPERTY[] = L"CalClock.SettingsColorPreview";
const wchar_t SETTINGS_COLOR_BUTTON_PROPERTY[] = L"CalClock.SettingsColorButton";

/// Window messages, timers and subclass identifiers
const UINT WM_TRAYICON = WM_APP + 1;
const UINT WM_SHOW_EXISTING = WM_APP + 2;
const UINT WM_NTP_RESULT = WM_APP + 3;
const UINT WM_AUDIO_FINISHED = WM_APP + 4;
const UINT WM_SETTINGS_AUDIO_FINISHED = WM_APP + 5;
const UINT WM_REFRESH_DISPLAYS = WM_APP + 6;
const UINT WM_TIME_SIGNAL_FINISHED = WM_APP + 8;
const UINT WM_UPDATE_SETTINGS_CONTROL_METRICS = WM_APP + 9;
const UINT WM_ALIGN_SETTINGS_FONT_BUTTON = WM_APP + 10;
const UINT_PTR TIMER_REFRESH = 1;
const UINT REFRESH_MAX_INTERVAL = 100;
const LONGLONG REFRESH_SECOND_TICKS = 10000000;
const LONGLONG REFRESH_MILLISECOND_TICKS = 10000;
static const ULONGLONG FULLSCREEN_CURSOR_IDLE_DELAY = 3000;
const UINT_PTR COMBO_BOX_DROPDOWN_SUBCLASS_ID = 0xCC04;
const UINT_PTR SETTINGS_CONTROL_SUBCLASS_ID = 0xCC05;
const UINT_PTR SETTINGS_REPORT_HEADER_SUBCLASS_ID = 0xCC07;
const UINT_PTR SETTINGS_LIST_BORDER_SUBCLASS_ID = 0xCC08;

/// Layout, appearance and alarm constants
const COLORREF IDENTIFY_COLOR = RGB(80, 190, 255);
const int MAX_DIALOG_BUTTON_HEIGHT = 28;
const int ALARM_DAY_COUNT = 7;
const int SETTINGS_COMBO_VISIBLE_ITEMS = 13;
const int TIME_SIGNAL_VOLUME_SLIDER_MIN = 0;
const int TIME_SIGNAL_VOLUME_SLIDER_MAX = 2000;
const int TIME_SIGNAL_VOLUME_SLIDER_MIDDLE = 1000;
const double TIME_SIGNAL_VOLUME_SLIDER_MIN_DB = -60.0;
const double TIME_SIGNAL_VOLUME_SLIDER_MIDDLE_DB = -18.0;
static const int WORK_AREA_SNAP_DISTANCE = 5;

/// Widget panel control identifiers
const int ID_PANEL_DATE_LINK = 115;
const int ID_PANEL_TIME_ZONE_LINK = 116;

/// Menu command identifiers
const int ID_MENU_ABOUT = 1023;
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
const int ID_MENU_SUNDAY_FIRST = 1016;
const int ID_MENU_TIME_SIGNAL_ENABLED = 1007;
const int ID_MENU_TODAY = 1009;
const int ID_MENU_TOPMOST = 1003;
const int ID_MENU_VISIBLE = 1002;
const int ID_MENU_WEEK_NUMBERS = 1015;
const int ID_MENU_WIDGET_BASE = 2000;

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

/// Windows and tooltips
HWND hController = nullptr;
HWND hSettings = nullptr;
HWND hSettingsDefaultButton = nullptr;

/// Settings pages and widget list
static HWND hSettingsOpenCombo = nullptr;
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
HWND hPanelTimeNoticesCheck = nullptr;
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
HWND hFontLabel = nullptr;
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
HWND hPanelBottomFontLabel = nullptr;
HWND hPanelTimeFontButton = nullptr;
HWND hPanelTimeFontLabel = nullptr;
HWND hPanelTopFontButton = nullptr;
HWND hPanelTopFontLabel = nullptr;
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
HWND hAudioOutputLabel = nullptr;
HWND hAudioOutputCombo = nullptr;
HWND hTestAudioOutputLabel = nullptr;
HWND hTestAudioOutputCombo = nullptr;
HWND hTimeSignalEnabledCheck = nullptr;
HWND hTimeSignalIntervalRadios[TIME_SIGNAL_COUNT - 1] = {};

/// Time source controls
HWND hNtpLogList = nullptr;
HWND hNtpPresetCombo = nullptr;
HWND hNtpPresetLabel = nullptr;
HWND hNtpSaveLogButton = nullptr;
HWND hNtpServersEdit = nullptr;
HWND hNtpServersLabel = nullptr;
HWND hNtpStatus = nullptr;
HWND hNtpSyncButton = nullptr;
HWND hTimeSourceCombo = nullptr;
HWND hTimeGlobalNote = nullptr;

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
HWND hWarnUnsavedChangesCheck = nullptr;

/// Mouse interaction windows
static HWND hFullscreenCursorWindow = nullptr;

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

/// Independent information forms and their shared Unicode boundary analysis
static HelpForm helpForm;
static AboutForm aboutForm;
static InformationWordBreakState informationWordBreakState;

/// Persistent form placement
static PersistWindowState settingsWindowState;
static PersistWindowState helpWindowState;
static PersistWindowState aboutWindowState;

/// Mouse interaction positions
static POINT fullscreenCursorPosition = {};

/// Edit selection state

/// Language and widget type
AppLanguage appLanguage = LANG_EN_US;
WidgetType lastAddedWidgetType = WIDGET_ANALOG;

/// State flags
static bool fullscreenCursorHidden = false;
static bool monitorColumnsInitialized = false;
static bool monitorSortAscending = true;
static bool ntpLogColumnsInitialized = false;
static bool ntpLogSortAscending = true;
static bool settingsComboAccepted = false;
static bool settingsGeneralCheckboxReferenceValid = false;
static bool settingsLayoutSuspended = false;
bool appFontItalic = false;
bool displayRefreshPending = false;
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
bool warnOnUnsavedChanges = true;
bool winsockReady = false;

/// Numeric settings and positions
static int monitorSortColumn = -1;
static int ntpLogSortColumn = -1;
static int settingsComboInitialSelection = CB_ERR;
int appFontAntialiasing = FONT_ANTIALIAS_CLEARTYPE;
int appFontDialogSize = 90;
int appFontWeight = FW_NORMAL;
int nextWidgetId = 1;
int ntpPreset = NTP_PRESET_AUTO;
int selectedDraftIndex = 0;
int settingsAppFontDialogSize = 90;
int settingsAppFontWeight = FW_NORMAL;
int settingsContentHeight = 0;
int settingsContentWidth = 0;
int settingsTab = 0;
int settingsVisualPreviewWidgetId = -1;
int settingsWidgetId = -1;
double timeSignalVolume = TIME_SIGNAL_VOLUME_DEFAULT;
std::shared_ptr<std::atomic<int>> settingsPreviewVolume;

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
std::atomic<LONGLONG> ntpClockOffset100Nanoseconds = 0;
std::atomic<LONGLONG> ntpOffset100Nanoseconds = 0;
std::atomic<bool> ntpQueryRunning = false;
std::atomic<bool> ntpStopRequested = false;
std::atomic<bool> ntpTimeValid = false;

/// Font names, file-dialog directory and NTP servers
std::wstring appFontFace;
std::wstring fileDialogDirectory;
std::wstring ntpActiveServer;
std::wstring ntpServers;
std::wstring settingsAppFontFace;
std::wstring testAudioOutputDevice;
std::wstring settingsTestAudioOutputDevice;

/// NTP synchronization history for the current process
std::vector<NtpQueryLogEntry> ntpSynchronizationLog;

/// General checkbox offsets from label baselines, captured from RC in half pixels.
static LONG settingsGeneralCheckboxBaselineDistances[3] = {};

/// Widgets
std::vector<std::unique_ptr<Widget>> widgets;

/// Widget configuration drafts
std::vector<WidgetConfig> settingsAppearanceOriginals;
std::vector<WidgetConfig> settingsDraft;
std::vector<WidgetConfig> settingsAppliedWidgets;

/// Widget identifiers
std::vector<AudioOutputDevice> settingsAudioOutputs;
std::vector<AudioOutputDevice> settingsTestAudioOutputs;
std::vector<TimeSignalSourceGroup> currentTimeSignalSources;
std::vector<int> lastHiddenWidgetIds;
std::vector<int> lastMutedWidgetIds;
std::vector<int> settingsAppearancePreviewIds;
std::vector<int> disabledArrangementCommands;

/// Monitors and time zones
std::vector<DisplayMonitor> displayMonitors;
static std::vector<MonitorListEntry> monitorListEntries;
std::vector<DYNAMIC_TIME_ZONE_INFORMATION> timeZones;

/// Window and control collections
std::vector<HWND> alarmControls;
std::vector<HWND> appearanceControls;
std::vector<HWND> applicationControls;
std::vector<HWND> blackoutWindows;
std::vector<HWND> generalControls;
std::vector<HWND> timeControls;
std::vector<HWND> timeSignalControls;

static const std::vector<HWND>* const settingsControlGroups[] = {
    &generalControls,
    &appearanceControls,
    &alarmControls,
    &timeSignalControls,
    &timeControls,
    &applicationControls
};

/// Forward declarations

/// Returns the settings page corresponding to a tab index, or null for an invalid index.
static HWND GetSettingsPage(int tab);

/// Fits pending NTP log columns on display or after the first batch, reserving each heading's sort-arrow
/// space.
static void InitializeNtpLogColumnWidths();

/// Fits monitor headings and content once when the populated list is displayed.
static void InitializeMonitorColumnWidths();

/// Dispatches monitor sorting and checkbox notifications using stable source identities.
static bool HandleMonitorListNotification(NMHDR* header, LRESULT* result);

/// Scrolls the NTP log to its last displayed row using its current native layout.
static void ScrollNtpLogToBottom();

/// Selects or reverses NTP log sorting after a column-heading click.
static void SortNtpLogByColumn(int column);

/// Extends the synchronization status to the fixed log top while preserving its position and width.
static void UpdateNtpLabelHeights();

/// Dispatches controller, widget, settings-page, and information-window messages. Coordinates painting,
/// input, timers, background-worker results, settings actions, and orderly application shutdown.
static LRESULT CALLBACK WindowProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);

/// Keeps the settings default button in step with focus and prevents clicks on covered controls.
/// Allows programmatic BM_CLICK activation and removes the subclass when the control is destroyed.
static LRESULT CALLBACK SettingsControlSubclassProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam,
    UINT_PTR subclassId, DWORD_PTR referenceData);

/// Integrates the primary native clock with widget dragging, face-only second-hand toggling, context menus,
/// and identification painting.
static LRESULT CALLBACK AnalogChildProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);

/// Handles an additional clock's size menu, panel dragging, background painting, and theme updates without
/// enabling a second hand.
static LRESULT CALLBACK AdditionalAnalogChildProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam,
    UINT_PTR subclassId, DWORD_PTR referenceData);

/// Preserves native calendar navigation while distinguishing title clicks from widget drags.
/// Applies the widget locale to native processing and handles context menus and identification feedback.
static LRESULT CALLBACK CalendarChildProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);

/// Keeps native panel-link input while presenting its text through the panel's shared buffer.
/// Supports printing, hover, focus and double-clicks without requesting paints from inside parent painting.
static LRESULT CALLBACK PanelLinkButtonSubclassProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam,
    UINT_PTR subclassId, DWORD_PTR referenceData);

/// Handles list selection and widget keyboard commands, including copy, paste, removal, and duplication.
/// On associated buttons, transfers focus to the widget list before handling the shortcut.
static LRESULT CALLBACK WidgetListSubclassProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam,
    UINT_PTR subclassId, DWORD_PTR referenceData);

/// Tracks mouse capture on the volume slider to control preview playback and stops it during subclass
/// destruction.
static LRESULT CALLBACK TimeSignalVolumeSubclassProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam,
    UINT_PTR subclassId, DWORD_PTR referenceData);

/// Refreshes the active time-signal volume preview from the current application controls.
static void UpdateTimeSignalVolumePreview();

/// Serializes selected widgets to the application's registered clipboard format, transferring memory
/// ownership only on success.
static void CopySelectedWidgetsToClipboard();

/// Reads and validates the application's bounded clipboard payload, validates pending edits, and appends
/// widget copies.
static void PasteWidgetsFromClipboard();

/// Updates a visible widget through the rendering path appropriate to its type, resizing only when needed.
static void RenderWidget(Widget* widget);

/// Temporarily substitutes committed widget configurations while saving, then restores the active appearance
/// previews.
static void SaveSettingsWithoutAppearancePreviews();

/// Stops tests, restores uncommitted previews, remembers the form position, tab and widget, and destroys
/// settings controls. Clears draft state and restores normal fullscreen presentation.
static void CloseSettingsWindow();

/// Prompts before user-requested settings closure when warning is enabled and Apply is active.
/// Saves through the existing validation path, discards on No, and keeps the form open on Cancel.
static void RequestCloseSettingsWindow();

/// Routes application exit through the settings save question and leaves all windows open when closure
/// is canceled.
static void RequestExitApplication();

/// Opens or activates the non-topmost settings form, selecting an explicit widget or restoring the last
/// closed selection. Creates draft snapshots and fullscreen previews when opening a new form; a missing
/// widget falls back to the first.
static void ShowSettingsWindow(int widgetId = -1);

/// Creates or removes this application's per-user Windows startup entry and reports registry-operation
/// success.
static bool SetStartWithWindowsEnabled(bool enabled);

/// Hides inactive pages before revealing the selected page, updates its state and mnemonics, and ends
/// inapplicable previews.
static void ShowSettingsTab(int tab);

/// Propagates a live menu change into draft, applied, and preview-original configurations.
/// Updates selected controls as needed and reevaluates Apply without rebuilding the settings form.
static void SynchronizeOpenSettings(const Widget* widget, int command);

/// Returns the Windows message-font face, falling back to the stock GUI font or an empty string.
static std::wstring GetSystemMessageFontFace();

/// Creates a caller-owned GDI font using the widget's point size, style, face, and antialiasing settings.
static HFONT CreateWidgetDrawingFont(const WidgetConfig& config);

/// Creates a caller-owned GDI font from panel font properties, converting the dialog size from tenths of
/// a point.
static HFONT CreatePanelFont(const FontSelection& selection, int fontAntialiasing);

/// Cancels the alarm test, releases its event handles, restores temporary visual alarm state, and resets
/// the Test caption.
static void StopSettingsPreview();

/// Updates font-button captions and the selected widget's font description without rewriting unchanged text.
static void UpdateFontDescription(const WidgetConfig& config);

/// Updates control enabled states for the selected widget and temporarily clears inapplicable checkbox
/// values. When requested, prepares the final layout before replacing the visible controls.
static void UpdateSettingControlAvailability(bool updateLayout = false);

/// Reenables Apply when pending changes exist; disabling is reserved for a successful explicit Apply action.
static void UpdateSettingsApplyButton();

/// Saves the selected appearance draft, tracks the widget for later restoration, and updates its live
/// preview.
static void PreviewSelectedWidgetAppearance(bool structuralChange);

/// Restores committed configurations for previewed widgets and clears preview tracking.
static void RestoreSettingsAppearancePreview();

/// Reconciles fullscreen clocks, settings previews, and blackout windows with current monitor and visibility
/// settings.
static void RefreshFullscreenPresentation();

/// Returns a borrowed pointer to the widget with the given persistent ID, or null when absent.
static Widget* FindWidgetById(int id);

/// Requests audio cancellation, closes the widget-owned event handles, and advances the generation to reject
/// stale notifications.
static void CloseWidgetAudio(Widget* widget);

/// Rebuilds a widget for a new configuration while preserving screen-edge attachments and relevant runtime
/// state.
static void RecreateWidgetForConfiguration(Widget* widget, const WidgetConfig& configuration);

static bool RecreatePanelWidgetBuffered(Widget* widget, const WidgetConfig& configuration,
    const std::vector<TimeDateNotice>* notices = nullptr, ULONGLONG applicationUtc = 0);

/// Creates a calendar font from system message-font metrics and widget face and style settings.
/// Returns null on failure; the caller owns the returned GDI font.
static HFONT CreateCalendarUiFont(const WidgetConfig& config);

/// Moves or resizes a control only when necessary, retaining combo height and resource-authored text widths.
static void SetControlPosition(HWND control, int x, int y, int width, int height);

/// Maps native settings resource geometry and dialog-unit distances.
static RECT GetSettingsResourceRect(HWND parent, int id);
static int SettingsDialogHeight(int value);
static int SettingsDialogWidth(int value);
static LONG PreferredButtonWidth(HWND button, LONG minimum, int paddingDlu = 12);
static void FitSettingsButtonWidth(HWND button, bool alignRight);
static void UpdateSettingsActionButtonWidths();
static void UpdateSettingsWindowLayout();

/// Tests whether a handle matches one of the settings page handles.
static bool IsSettingsPageWindow(HWND window);

/// Aligns Appearance fields and buttons to a common width and reserves border-slider space.
static void UpdateSettingsColorControlLayout();

/// Matches Application field gaps to the current root action-button gap.
static void UpdateApplicationControlWidths();

/// Updates a nonnull control's text only when the visible string changes.
static void SetControlText(HWND control, const wchar_t* text);

/// Updates a caption only when its text differs after mnemonic removal, preserving existing mnemonic
/// assignments otherwise.
static void SetControlCaption(HWND control, const wchar_t* caption);

/// Changes a nonnull control's enabled state and keeps its associated color preview in the same state.
static void SetControlEnabled(HWND control, bool enabled);

/// Changes a nonnull control's own visibility style and keeps its associated color preview in the same state.
static void SetControlVisible(HWND control, bool visible);

/// Changes a combo box selection only when the selected index differs.
static void SetComboSelection(HWND combo, int selection);

/// Updates a trackbar's range only when either endpoint differs.
static void SetTrackBarRange(HWND trackBar, int minimum, int maximum);

/// Clamps a requested trackbar position to its range and updates it only when changed.
static void SetTrackBarPosition(HWND trackBar, int position);

/// Updates a native color button's stored selection and repaints its associated preview when the color
/// changes.
static void SetButtonColor(HWND button, COLORREF color);

/// Changes a checkbox's checked state only when it differs from the requested state.
static void SetCheck(HWND control, bool checked);

/// Shows or hides one widget, updates fullscreen presentation and open settings as needed, and saves the
/// visibility change.
static void SetWidgetVisible(Widget* widget, bool visible);

/// Selects the widget's displayed current date, optionally preserving the calendar's month, year, or decade
/// view. An explicit navigation request returns to month view and focuses the calendar.
static void SelectCalendarToday(Widget* widget, bool preserveView = false);

/// Returns independently advancing NTP UTC when synchronized, otherwise the current system UTC.
static void GetApplicationUtcTime(SYSTEMTIME* utc);

/// Formats a signed NTP offset in seconds for status and log captions.
static std::wstring FormatNtpLogOffset(LONGLONG offset100Nanoseconds);

/// Returns a borrowed localized UI string in the current application language.
const wchar_t* T(TextId id) {
    return GetLocalizedText(appLanguage, id);
}

/// Reports whether a widget type supports alarms and time signals; standalone calendars do not.
static bool WidgetSupportsSound(WidgetType type) {
    return type != WIDGET_CALENDAR;
}

/// Returns the selected language; selector indices follow the language enum directly.
static AppLanguage LanguageFromCombo(HWND combo) {
    return static_cast<AppLanguage>(SendMessageW(combo, CB_GETCURSEL, 0, 0));
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
    const FontAntialiasing modes[] = { FONT_ANTIALIAS_CLEARTYPE, FONT_ANTIALIAS_GDI, FONT_ANTIALIAS_NONE };
    for (FontAntialiasing mode : modes) {
        LRESULT index =
            SendMessageW(combo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(T(ANTIALIASING_TEXT_IDS[mode])));
        SendMessageW(combo, CB_SETITEMDATA, index, mode);
    }
}

/// Adds supported language names in their defined display order.
static void PopulateLanguageCombo(HWND combo) {
    for (int language = 0; language < LANG_COUNT; language++) {
        const wchar_t* name = GetLocalizedText(static_cast<AppLanguage>(language), TXT_LANGUAGE_NAME);
        SendMessageW(combo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(name));
    }
}

/// Returns a borrowed widget-type name in the application language.
static const wchar_t* TypeName(WidgetType type) {
    return T(WIDGET_TYPE_TEXT_IDS[type]);
}

/// Returns a borrowed localized string in the widget's language, or the application language for a null
/// widget.
static const wchar_t* WT(const Widget* widget, TextId id) {
    AppLanguage language = widget == nullptr ? appLanguage : widget->config.language;
    return GetLocalizedText(language, id);
}

/// Normalizes a character to uppercase for comparing assigned keyboard mnemonics.
static wchar_t MnemonicKey(wchar_t character) {
    CharUpperBuffW(&character, 1);
    return character;
}

/// Preserves an available preferred mnemonic or assigns an unused character while escaping literal
/// ampersands. Records the chosen key in usedMnemonics.
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
static void AppendApplicationMenuCommands(HMENU menu, AppLanguage language,
        std::vector<wchar_t>* usedMnemonics) {
    AppendMenuCommand(menu, MF_STRING, ID_MENU_SETTINGS, GetLocalizedText(language, TXT_SETTINGS),
        usedMnemonics);
    AppendMenuCommand(menu, MF_STRING, ID_MENU_HELP, GetLocalizedText(language, TXT_HELP), usedMnemonics);
    AppendMenuCommand(menu, MF_STRING, ID_MENU_ABOUT, GetLocalizedText(language, TXT_ABOUT), usedMnemonics);
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendMenuCommand(menu, MF_STRING, ID_MENU_EXIT, GetLocalizedText(language, TXT_EXIT), usedMnemonics);
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
static int WINAPI CalendarGetCalendarInfoW(LCID locale, CALID calendar, CALTYPE type, LPWSTR data,
        int characters, LPDWORD value) {
    if (originalGetCalendarInfoW == nullptr) {
        return 0;
    }
    LCID selectedLocale = activeCalendarLocale == 0 ? locale : activeCalendarLocale;
    return originalGetCalendarInfoW(selectedLocale, calendar, type, data, characters, value);
}

/// Converts the active calendar override to a locale name and forwards the calendar-property request.
static int WINAPI CalendarGetCalendarInfoEx(LPCWSTR localeName, CALID calendar, LPCWSTR reserved,
        CALTYPE type, LPWSTR data, int characters, LPDWORD value) {
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
static int WINAPI CalendarGetCalendarDateFormat(CALID calendar, DWORD flags, const void* calendarDate,
        LPCWSTR format, LPWSTR data, int characters) {
    if (activeCalendarLocale != 0 && calendarDate != nullptr && data != nullptr && characters > 0) {
        if (convertCalDateTimeToSystemTime == nullptr) {
            HMODULE kernel = GetModuleHandleW(L"kernel32.dll");
            if (kernel != nullptr) {
                convertCalDateTimeToSystemTime = reinterpret_cast<ConvertCalDateTimeToSystemTimeProc>(
                    GetProcAddress(kernel, "ConvertCalDateTimeToSystemTime"));
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
    IMAGE_IMPORT_DESCRIPTOR* descriptor =
        reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(base + imports.VirtualAddress);
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
            IMAGE_IMPORT_BY_NAME* importName =
                reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(base + names->u1.AddressOfData);
            if (strcmp(reinterpret_cast<const char*>(importName->Name), functionName) != 0) {
                continue;
            }
            DWORD oldProtect = 0;
            if (!VirtualProtect(&addresses->u1.Function, sizeof(addresses->u1.Function), PAGE_READWRITE,
                    &oldProtect)) {
                return false;
            }
            *original = addresses->u1.Function;
            addresses->u1.Function = replacement;
            DWORD ignored = 0;
            VirtualProtect(&addresses->u1.Function, sizeof(addresses->u1.Function), oldProtect, &ignored);
            FlushInstructionCache(GetCurrentProcess(), &addresses->u1.Function,
                sizeof(addresses->u1.Function));
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
        item.work = information.rcWork;
        item.device = information.szDevice;
        item.primary = (information.dwFlags & MONITORINFOF_PRIMARY) != 0;
        monitors->push_back(item);
    }
    return TRUE;
}

/// Orders the primary monitor first, then the remaining monitors by screen position.
static bool DisplayMonitorComesFirst(const DisplayMonitor& left, const DisplayMonitor& right) {
    if (left.primary != right.primary) {
        return left.primary;
    }
    if (left.rect.top != right.rect.top) {
        return left.rect.top < right.rect.top;
    }
    return left.rect.left < right.rect.left;
}

/// Rebuilds the monitor list with the primary monitor first, then orders the remainder by screen position.
static void RefreshDisplayMonitors() {
    displayMonitors.clear();
    EnumDisplayMonitors(nullptr, nullptr, CollectDisplayMonitor, reinterpret_cast<LPARAM>(&displayMonitors));
    std::stable_sort(displayMonitors.begin(), displayMonitors.end(), DisplayMonitorComesFirst);
}

/// Tests case-insensitive membership in a semicolon-separated list of monitor device names.
static bool ContainsMonitorDevice(const std::wstring& devices, const std::wstring& device) {
    size_t start = 0;
    while (start <= devices.size()) {
        size_t end = devices.find(L';', start);
        std::wstring current =
            devices.substr(start, end == std::wstring::npos ? std::wstring::npos : end - start);
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

/// Fills a four-entry size buffer from the native clock implementation, using standard sizes if detection
/// fails.
static int GetAnalogClockSizes(int* sizes) {
    int count = GetSupportedAnalogClockSizes(sizes, 4);
    if (count > 0) {
        return count;
    }
    const int fallbackSizes[] = { 104, 130, 166, 198 };
    CopyMemory(sizes, fallbackSizes, sizeof(fallbackSizes));
    return ARRAYSIZE(fallbackSizes);
}

/// Maps equivalent legacy clock sizes to the current implementation, otherwise choosing the nearest
/// supported size.
static int NormalizeAnalogClockSize(int size) {
    int sizes[4] = {};
    int count = GetAnalogClockSizes(sizes);
    const int vistaSizes[] = { 103, 128, 129, 160 };
    const int otherSizes[] = { 104, 130, 166, 198 };
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

/// Resets a widget's appearance for its type using the current application antialiasing choice and system
/// font defaults.
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

/// Allocates an unused positive widget ID, wrapping safely when a stored ID reaches the integer limit.
static int AllocateWidgetId() {
    while (true) {
        int candidate = nextWidgetId;
        nextWidgetId = nextWidgetId < INT_MAX ? nextWidgetId + 1 : 1;
        bool used = false;
        for (const std::unique_ptr<Widget>& widget : widgets) {
            if (widget->config.id == candidate) {
                used = true;
                break;
            }
        }
        if (!used) {
            for (const WidgetConfig& config : settingsDraft) {
                if (config.id == candidate) {
                    used = true;
                    break;
                }
            }
        }
        if (!used) {
            return candidate;
        }
    }
}

/// Builds a visible widget with localized defaults and an initial position, allocating a new widget ID.
static WidgetConfig DefaultConfig(WidgetType type, int index) {
    WidgetConfig config = {};
    config.id = AllocateWidgetId();
    config.type = type;
    config.name = TypeName(type);
    config.visible = true;
    config.topMost = true;
    config.showSeconds = true;
    config.showUtc = false;
    config.showUtcText = false;
    config.language = appLanguage;
    config.timeZoneKey = SYSTEM_TIME_ZONE_KEY;
    for (int clockIndex = 0; clockIndex < ADDITIONAL_CLOCK_COUNT; clockIndex++) {
        AdditionalClockConfig& clock = config.additionalClocks[clockIndex];
        clock.name = DefaultAdditionalClockName(config.language, clockIndex);
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
    config.timeSignalEnabled = false;
    config.timeSignal = TIME_SIGNAL_EVERY_HOUR;
    return config;
}

/// Selects a supported language from the Windows UI language, defaulting to US English.
static void SelectSystemLanguage() {
    LANGID systemLanguage = GetUserDefaultUILanguage();
    switch (PRIMARYLANGID(systemLanguage)) {
        case LANG_CZECH:
            appLanguage = LANG_CS;
            break;
        case LANG_ENGLISH:
            if (SUBLANGID(systemLanguage) == SUBLANG_ENGLISH_UK) {
                appLanguage = LANG_EN_GB;
            } else if (SUBLANGID(systemLanguage) == SUBLANG_ENGLISH_AUS) {
                appLanguage = LANG_EN_AU;
            } else {
                appLanguage = LANG_EN_US;
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
            appLanguage = LANG_NB;
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
        case LANG_CROATIAN:
            switch (SUBLANGID(systemLanguage)) {
                case SUBLANG_BOSNIAN_BOSNIA_HERZEGOVINA_LATIN:
                case SUBLANG_BOSNIAN_BOSNIA_HERZEGOVINA_CYRILLIC:
                    appLanguage = LANG_BS;
                    break;
                case SUBLANG_SERBIAN_MONTENEGRO_LATIN:
                case SUBLANG_SERBIAN_MONTENEGRO_CYRILLIC:
                    appLanguage = LANG_CNR;
                    break;
                case SUBLANG_SERBIAN_LATIN:
                case SUBLANG_SERBIAN_CYRILLIC:
                case SUBLANG_SERBIAN_BOSNIA_HERZEGOVINA_LATIN:
                case SUBLANG_SERBIAN_BOSNIA_HERZEGOVINA_CYRILLIC:
                case SUBLANG_SERBIAN_SERBIA_LATIN:
                case SUBLANG_SERBIAN_SERBIA_CYRILLIC:
                    appLanguage = LANG_SR;
                    break;
                default:
                    appLanguage = LANG_HR;
                    break;
            }
            break;
        case LANG_ESTONIAN:
            appLanguage = LANG_ET;
            break;
        case LANG_IRISH:
            appLanguage = LANG_GA;
            break;
        case LANG_LITHUANIAN:
            appLanguage = LANG_LT;
            break;
        case LANG_LATVIAN:
            appLanguage = LANG_LV;
            break;
        case LANG_HUNGARIAN:
            appLanguage = LANG_HU;
            break;
        case LANG_MALTESE:
            appLanguage = LANG_MT;
            break;
        case LANG_DUTCH:
            appLanguage = LANG_NL;
            break;
        case LANG_ROMANIAN:
            appLanguage = LANG_RO;
            break;
        case LANG_GREEK:
            appLanguage = LANG_EL;
            break;
        case LANG_SLOVENIAN:
            appLanguage = LANG_SL;
            break;
        case LANG_BELARUSIAN:
            appLanguage = LANG_BE;
            break;
        case LANG_BULGARIAN:
            appLanguage = LANG_BG;
            break;
        case LANG_MACEDONIAN:
            appLanguage = LANG_MK;
            break;
        case LANG_UKRAINIAN:
            appLanguage = LANG_UK;
            break;
        case LANG_RUSSIAN:
            appLanguage = LANG_RU;
            break;
        default:
            appLanguage = LANG_EN_US;
            break;
    }
}

/// Copies application and widget settings, including the latest positions of open settings and information
/// windows.
static SettingsSnapshot CaptureSettingsSnapshot() {
    SettingsSnapshot snapshot = {};
    snapshot.language = appLanguage;
    snapshot.themesDisabled = themesDisabled;
    snapshot.snapWidgetsToWorkArea = snapWidgetsToWorkArea;
    snapshot.warnOnUnsavedChanges = warnOnUnsavedChanges;
    snapshot.generatedTimeSignal = generatedTimeSignal;
    snapshot.timeSignalVolume = timeSignalVolume;
    snapshot.testAudioOutputDevice = testAudioOutputDevice;
    snapshot.fontAntialiasing = appFontAntialiasing;
    snapshot.fontFace = appFontFace;
    snapshot.fontDialogSize = appFontDialogSize;
    snapshot.fontWeight = appFontWeight;
    snapshot.fontItalic = appFontItalic;
    snapshot.useNtpTime = useNtpTime;
    snapshot.ntpPreset = ntpPreset;
    snapshot.ntpServers = ntpServers;
    snapshot.fileDialogDirectory = fileDialogDirectory;
    snapshot.settingsWindowState = settingsWindowState.Save();
    snapshot.settingsTab = settingsTab;
    if (FindWidgetById(settingsWidgetId) != nullptr) {
        snapshot.settingsWidgetId = settingsWidgetId;
    }
    snapshot.lastAddedWidgetType = lastAddedWidgetType;
    snapshot.helpWindowState = helpWindowState.Save();
    snapshot.aboutWindowState = aboutWindowState.Save();
    for (size_t index = 0; index < widgets.size(); index++) {
        snapshot.widgets.push_back(widgets[index]->config);
    }
    return snapshot;
}

/// Restores application options and rebuilds widget state from a stored snapshot, normalizing bounded values
/// and the next ID.
static void ApplySettingsSnapshot(const SettingsSnapshot& snapshot) {
    appLanguage = snapshot.language;
    themesDisabled = snapshot.themesDisabled;
    snapWidgetsToWorkArea = snapshot.snapWidgetsToWorkArea;
    warnOnUnsavedChanges = snapshot.warnOnUnsavedChanges;
    generatedTimeSignal = snapshot.generatedTimeSignal;
    testAudioOutputDevice = snapshot.testAudioOutputDevice;
    timeSignalVolume = std::clamp<double>(snapshot.timeSignalVolume, TIME_SIGNAL_VOLUME_MIN,
        TIME_SIGNAL_VOLUME_MAX);
    appFontAntialiasing = std::clamp(snapshot.fontAntialiasing, 0, FONT_ANTIALIAS_COUNT - 1);
    appFontFace = snapshot.fontFace.size() < LF_FACESIZE ? snapshot.fontFace : L"";
    appFontDialogSize = std::clamp(snapshot.fontDialogSize, 10, 9990);
    appFontWeight = std::clamp(snapshot.fontWeight, 0, 1000);
    appFontItalic = snapshot.fontItalic;
    fileDialogDirectory = snapshot.fileDialogDirectory;
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
    settingsWindowState.Load(snapshot.settingsWindowState);
    settingsTab = std::clamp(snapshot.settingsTab, 0, SETTINGS_TAB_COUNT - 1);
    settingsWidgetId = snapshot.settingsWidgetId;
    lastAddedWidgetType = static_cast<WidgetType>(std::clamp(static_cast<int>(snapshot.lastAddedWidgetType),
        0, WIDGET_TYPE_COUNT - 1));
    helpWindowState.Load(snapshot.helpWindowState);
    aboutWindowState.Load(snapshot.aboutWindowState);
    lastHiddenWidgetIds.clear();
    widgets.clear();
    nextWidgetId = 1;
    for (size_t index = 0; index < snapshot.widgets.size(); index++) {
        std::unique_ptr<Widget> widget(new Widget());
        widget->config = snapshot.widgets[index];
        if (widget->config.id < INT_MAX) {
            nextWidgetId = std::max(nextWidgetId, widget->config.id + 1);
        }
        widgets.push_back(std::move(widget));
    }
    if (settingsWidgetId >= 0 && FindWidgetById(settingsWidgetId) == nullptr) {
        settingsWidgetId = -1;
    }
}

/// Refreshes the application's named and fixed-offset time-zone list.
static void LoadTimeZones() {
    LoadTimeZoneList(&timeZones);
}

/// Creates language-specific widget defaults for storage readers while restoring temporary global default
/// state.
static WidgetConfig CreateStoredWidgetDefaults(WidgetType type, int index, AppLanguage language,
        int fontAntialiasing) {
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
    config.timeZoneKey = GetSystemTimeZoneKey(timeZones);
    for (AdditionalClockConfig& clock : config.additionalClocks) {
        clock.timeZoneKey = config.timeZoneKey;
    }
    return config;
}

/// Returns the quoted executable path for the startup registry value, or an empty string if it cannot be
/// obtained.
static std::wstring StartWithWindowsCommand() {
    wchar_t executable[MAX_PATH] = {};
    DWORD length = GetModuleFileNameW(nullptr, executable, ARRAYSIZE(executable));
    if (length == 0 || length >= ARRAYSIZE(executable)) {
        return L"";
    }
    return L"\"" + std::wstring(executable, length) + L"\"";
}

/// Returns whether Windows startup targets this executable, removing a stale or invalid application entry.
static bool LoadStartWithWindowsSetting() {
    const wchar_t startupPath[] = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t startupValue[] = L"CalClock";
    std::wstring expected = StartWithWindowsCommand();
    if (expected.empty()) {
        SetStartWithWindowsEnabled(false);
        return false;
    }
    wchar_t actual[MAX_PATH * 2] = {};
    DWORD size = sizeof(actual);
    LSTATUS result =
        RegGetValueW(HKEY_CURRENT_USER, startupPath, startupValue, RRF_RT_REG_SZ, nullptr, actual, &size);
    bool matches = result == ERROR_SUCCESS && _wcsicmp(actual, expected.c_str()) == 0;
    if (!matches) {
        SetStartWithWindowsEnabled(false);
    }
    return matches;
}

/// Creates or removes this application's per-user Windows startup entry and reports registry-operation
/// success.
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
    if (RegCreateKeyExW(HKEY_CURRENT_USER, startupPath, 0, nullptr, 0, KEY_SET_VALUE, nullptr, &key, &disposition)
            != ERROR_SUCCESS) {
        return false;
    }
    LSTATUS written = RegSetValueExW(key, startupValue, 0, REG_SZ, reinterpret_cast<const BYTE*>(
        command.c_str()), static_cast<DWORD>((command.size() + 1) * sizeof(wchar_t)));
    RegCloseKey(key);
    return written == ERROR_SUCCESS;
}

/// Loads language, time zones, and persisted XML or registry settings. Removes a stale Windows startup entry
/// and creates an initial analog widget if no stored settings can be loaded.
static void LoadAllSettings() {
    for (PersistWindowState* placement : { &settingsWindowState, &helpWindowState, &aboutWindowState }) {
        placement->SetSavingOptions(PersistWindowStateSavingOptions::None);
        placement->SetDetectionOptions(WindowDetectionOptions::NoDetection);
        placement->SetUseWindowsDefaultLocation(false);
        placement->SetUseWindowsDefaultSize(false);
    }
    SelectSystemLanguage();
    startWithWindows = false;
    ntpPreset = NTP_PRESET_AUTO;
    ntpServers = NtpServersForPreset(ntpPreset);
    LoadTimeZones();
    std::wstring xmlPath = AutomaticXmlSettingsPath(false);
    storageUsesXml = !xmlPath.empty() && GetFileAttributesW(xmlPath.c_str()) != INVALID_FILE_ATTRIBUTES;
    SettingsSnapshot snapshot = {};
    if (storageUsesXml && ReadSettingsXml(xmlPath, appLanguage, CreateStoredWidgetDefaults, &snapshot)) {
        ApplySettingsSnapshot(snapshot);
        startWithWindows = LoadStartWithWindowsSetting();
        if (snapshot.settingsWidgetId != settingsWidgetId) {
            SaveAllSettings();
        }
        return;
    }
    SettingsSnapshot defaults = CaptureSettingsSnapshot();
    if (ReadRegistrySettings(defaults, CreateStoredWidgetDefaults, &snapshot)) {
        ApplySettingsSnapshot(snapshot);
        startWithWindows = LoadStartWithWindowsSetting();
        if (snapshot.settingsWidgetId != settingsWidgetId) {
            SaveAllSettings();
        }
        return;
    }
    SetStartWithWindowsEnabled(false);
    std::unique_ptr<Widget> widget(new Widget());
    widget->config = DefaultConfig(WIDGET_ANALOG, 0);
    widgets.push_back(std::move(widget));
}

/// Captures current settings and saves them to the selected XML or registry backend.
/// Removes registry settings after a successful switch to XML storage.
void SaveAllSettings() {
    if (settingsWidgetId >= 0 && FindWidgetById(settingsWidgetId) == nullptr) {
        settingsWidgetId = -1;
    }
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
static bool SplitNumericInput(const wchar_t* text, bool allowSign, bool* negative,
        std::vector<std::wstring>* groups) {
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
    if (minutes > 59
            || seconds > 59
            || hundredths > 99
            || hours > static_cast<ULONGLONG>(LLONG_MAX) / 3600000ULL) {
        return false;
    }
    ULONGLONG milliseconds = ((hours * 60ULL + minutes) * 60ULL + seconds) * 1000ULL + hundredths * 10ULL;
    if (milliseconds > static_cast<ULONGLONG>(LLONG_MAX)) {
        return false;
    }
    *result = negative ? -static_cast<LONGLONG>(milliseconds) : static_cast<LONGLONG>(milliseconds);
    return true;
}

/// Formats a signed millisecond offset as hours, minutes, seconds, and hundredths without overflowing on the
/// minimum value.
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

/// Parses compact or separated alarm input into a valid 24-hour hour and minute, leaving outputs unchanged
/// on failure.
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

/// Starts a due or forced NTP query on the UI thread, postponing automatic requests around the hour until
/// HH:00:10. Manual requests bypass that postponement. Failed attempts retry after one minute before the
/// first successful synchronization in this process, or ten minutes afterward; successful results schedule
/// the next hourly request.
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
    hNtpThread = StartNtpQueryThread(ntpServers, ntpGeneration.load(), hController, WM_NTP_RESULT,
        &ntpStopRequested, &ntpQueryRunning);
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

/// Returns the selected clock's offset from the continuous timeline shared by display and time signals.
static LONGLONG GetApplicationTimeOffset(ULONGLONG monotonicNow) {
    return useNtpTime && ntpTimeValid
        ? ntpClockOffset100Nanoseconds.load()
        : static_cast<LONGLONG>(CurrentFileTimeValue()) - static_cast<LONGLONG>(monotonicNow);
}

/// Returns independently advancing NTP FILETIME when synchronized, otherwise the current system FILETIME.
static ULONGLONG GetApplicationFileTimeValue() {
    ULONGLONG now = MonotonicFileTimeValue();
    return static_cast<ULONGLONG>(static_cast<LONGLONG>(now) + GetApplicationTimeOffset(now));
}

/// Calculates the next refresh delay from visible widgets and enabled alarms, including NTP and fractional
/// offsets. Keeps maintenance responsive and respects the minimum interval of the Windows UI timer.
static UINT WidgetRefreshDelay(ULONGLONG applicationNow) {
    UINT delay = REFRESH_MAX_INTERVAL;
    LONGLONG applicationPhase = static_cast<LONGLONG>(applicationNow % REFRESH_SECOND_TICKS);
    for (const std::unique_ptr<Widget>& widget : widgets) {
        if (!widget->config.visible && !widget->config.alarmEnabled) {
            continue;
        }
        LONGLONG phase =
            applicationPhase + widget->config.offsetMilliseconds % 1000 * REFRESH_MILLISECOND_TICKS;
        phase %= REFRESH_SECOND_TICKS;
        if (phase < 0) {
            phase += REFRESH_SECOND_TICKS;
        }
        LONGLONG remaining = REFRESH_SECOND_TICKS - phase;
        UINT milliseconds =
            static_cast<UINT>((remaining + REFRESH_MILLISECOND_TICKS - 1) / REFRESH_MILLISECOND_TICKS);
        delay = std::min(delay, milliseconds);
    }
    return std::max(static_cast<UINT>(USER_TIMER_MINIMUM), delay);
}

/// Reanchors the UI timer to the nearest displayed second instead of accumulating a fixed polling interval.
static void ScheduleWidgetRefresh() {
    if (hController != nullptr) {
        UINT delay = WidgetRefreshDelay(GetApplicationFileTimeValue());
        SetTimer(hController, TIMER_REFRESH, delay, nullptr);
    }
}

/// Returns independently advancing NTP UTC when synchronized, otherwise the current system UTC.
static void GetApplicationUtcTime(SYSTEMTIME* utc) {
    ULONGLONG value = GetApplicationFileTimeValue();
    FILETIME fileTime = {};
    ULARGE_INTEGER parts = {};
    parts.QuadPart = value;
    fileTime.dwLowDateTime = parts.LowPart;
    fileTime.dwHighDateTime = parts.HighPart;
    FileTimeToSystemTime(&fileTime, utc);
}

/// Applies the widget's millisecond offset to application UTC without changing the time zone.
/// Uses the current application time when applicationUtc is zero.
static void GetWidgetUtcTime(const WidgetConfig& config, SYSTEMTIME* utc, ULONGLONG applicationUtc = 0) {
    ULARGE_INTEGER value = {};
    value.QuadPart = applicationUtc == 0 ? GetApplicationFileTimeValue() : applicationUtc;
    LONGLONG current = static_cast<LONGLONG>(value.QuadPart);
    if (config.offsetMilliseconds > (LLONG_MAX - current) / 10000) {
        value.QuadPart = LLONG_MAX;
    } else if (config.offsetMilliseconds < -current / 10000) {
        value.QuadPart = 0;
    } else {
        value.QuadPart = static_cast<ULONGLONG>(current + config.offsetMilliseconds * 10000);
    }
    FILETIME fileTime = { value.LowPart, value.HighPart };
    FileTimeToSystemTime(&fileTime, utc);
}

/// Converts the widget's offset-adjusted UTC instant to its selected zone or UTC.
static void GetDisplayedTime(const WidgetConfig& config, SYSTEMTIME* displayed,
        ULONGLONG applicationUtc = 0) {
    SYSTEMTIME utc = {};
    GetWidgetUtcTime(config, &utc, applicationUtc);
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
}

/// Builds native date/time notices from one widget-specific UTC instant and the selected Windows zone.
static std::vector<TimeDateNotice> GetPanelTimeNotices(const WidgetConfig& config,
        bool calendarDateSupported = true, ULONGLONG applicationUtc = 0) {
    if (config.type != WIDGET_PANEL || !config.panelTimeNotices) {
        return {};
    }
    SYSTEMTIME utc = {};
    GetWidgetUtcTime(config, &utc, applicationUtc);
    DYNAMIC_TIME_ZONE_INFORMATION zone = {};
    const DYNAMIC_TIME_ZONE_INFORMATION* selected = nullptr;
    bool recognized = true;
    bool autoAdjustment = true;
    if (config.showUtc) {
        selected = &zone;
    } else if (_wcsicmp(config.timeZoneKey.c_str(), SYSTEM_TIME_ZONE_KEY) == 0) {
        if (GetDynamicTimeZoneInformation(&zone) != TIME_ZONE_ID_INVALID) {
            selected = &zone;
            recognized = false;
            for (const DYNAMIC_TIME_ZONE_INFORMATION& candidate : timeZones) {
                if (_wcsicmp(candidate.TimeZoneKeyName, SYSTEM_TIME_ZONE_KEY) != 0
                        && _wcsicmp(candidate.TimeZoneKeyName, zone.TimeZoneKeyName) == 0) {
                    recognized = true;
                    break;
                }
            }
            autoAdjustment = !zone.DynamicDaylightTimeDisabled
                || zone.StandardDate.wMonth != 0
                || zone.DaylightDate.wMonth != 0;
        }
    } else {
        for (const DYNAMIC_TIME_ZONE_INFORMATION& candidate : timeZones) {
            if (_wcsicmp(candidate.TimeZoneKeyName, config.timeZoneKey.c_str()) == 0) {
                selected = &candidate;
                break;
            }
        }
        if (selected == nullptr) {
            recognized = false;
            if (GetDynamicTimeZoneInformation(&zone) != TIME_ZONE_ID_INVALID) {
                selected = &zone;
                autoAdjustment = !zone.DynamicDaylightTimeDisabled
                    || zone.StandardDate.wMonth != 0
                    || zone.DaylightDate.wMonth != 0;
            }
        }
    }
    return GetTimeDateNotices(selected, utc, GetLanguageLocale(config.language), autoAdjustment,
        calendarDateSupported, recognized);
}

/// Compares the ordered text and icon contents of two native-notice snapshots.
static bool PanelTimeNoticesEqual(const std::vector<TimeDateNotice>& left,
        const std::vector<TimeDateNotice>& right) {
    if (left.size() != right.size()) {
        return false;
    }
    for (size_t index = 0; index < left.size(); index++) {
        if (left[index].text != right[index].text || left[index].icon != right[index].icon) {
            return false;
        }
    }
    return true;
}

/// Converts SYSTEMTIME fields to FILETIME ticks without changing their time zone; returns zero on conversion
/// failure.
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

/// Reports whether any listed widget is audible, also requiring regular time signals to remain enabled.
static bool HasUnmutedTimeSignalSource(const std::vector<int>& widgetIds, bool regular) {
    for (size_t index = 0; index < widgetIds.size(); index++) {
        Widget* widget = FindWidgetById(widgetIds[index]);
        if (widget != nullptr
                && !widget->config.soundsMuted
                && (!regular || widget->config.timeSignalEnabled)) {
            return true;
        }
    }
    return false;
}

/// Mutes each shared sequence only when none of its regular or alarm contributors is audible.
static void UpdateCurrentTimeSignalMute() {
    for (const TimeSignalSourceGroup& group : currentTimeSignalSources) {
        bool audible = HasUnmutedTimeSignalSource(group.regularWidgetIds, true)
            || HasUnmutedTimeSignalSource(group.alarmWidgetIds, false);
        SetTimeSignalMuted(group.target, !audible, group.outputDevice);
    }
}

/// Tests a Windows day-of-week value against the alarm's Monday-based weekday mask.
static bool AlarmEnabledOnDay(const WidgetConfig& config, WORD dayOfWeek) {
    int mondayBasedDay = dayOfWeek == 0 ? 6 : dayOfWeek - 1;
    return (config.alarmDays & 1U << mondayBasedDay) != 0;
}

/// Returns a localized abbreviated weekday for a Monday-based index, using English abbreviations if
/// formatting fails.
static std::wstring GetWeekdayAbbreviation(AppLanguage language, int mondayBasedDay) {
    SYSTEMTIME date = {};
    date.wYear = 2001;
    date.wMonth = 1;
    date.wDay = static_cast<WORD>(1 + std::clamp(mondayBasedDay, 0, ALARM_DAY_COUNT - 1));
    wchar_t text[32] = {};
    if (GetDateFormatEx(GetLanguageLocale(language), 0, &date, L"ddd", text, ARRAYSIZE(text), nullptr) > 0) {
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
    if (GetLocaleInfoEx(GetLanguageLocale(language), LOCALE_IFIRSTDAYOFWEEK, firstDayText,
        ARRAYSIZE(firstDayText)) > 0) {
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
    std::wstring label = GetLocalizedText(config.language, TXT_ALARM);
    label += L" (";
    label += time;
    label += L")";
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

/// Builds a localized signal menu caption with the retained interval, whether enabled or disabled.
/// Lowercases the interval's initial using the widget locale while preserving capitalization within
/// the phrase.
static std::wstring TimeSignalMenuLabel(const WidgetConfig& config) {
    std::wstring interval = GetLocalizedText(config.language, TIME_SIGNAL_TEXT_IDS[config.timeSignal]);
    wchar_t initial = 0;
    bool initialMapped = LCMapStringEx(GetLanguageLocale(config.language), LCMAP_LOWERCASE
        | LCMAP_LINGUISTIC_CASING, interval.c_str(), 1, &initial, 1, nullptr, nullptr, 0) == 1;
    if (initialMapped) {
        interval[0] = initial;
    }
    std::wstring label = GetLocalizedText(config.language, TXT_TIME_SIGNAL_MENU_LABEL);
    label += L" (";
    label += interval;
    label += L")";
    return label;
}

/// Removes contributors that no longer target this endpoint, retaining canceled-alarm history separately.
static void RetainCurrentTimeSignalSources(TimeSignalSourceGroup& group,
        const std::vector<TimeSignalCandidate>& candidates, bool regular) {
    std::vector<int>& sources = regular ? group.regularWidgetIds : group.alarmWidgetIds;
    for (auto source = sources.begin(); source != sources.end();) {
        bool retained = false;
        for (const TimeSignalCandidate& candidate : candidates) {
            if (candidate.target == group.target
                    && candidate.outputDevice == group.outputDevice
                    && candidate.regular == regular
                    && candidate.widgetId == *source) {
                retained = true;
                break;
            }
        }
        if (retained) {
            source++;
        } else {
            source = sources.erase(source);
        }
    }
}

/// Schedules approaching regular and alarm GTS targets from each widget's displayed time, retaining
/// fractional offsets. Retimes existing sequences when the NTP correction changes, preserving their
/// contributors and canceled alarms. Groups identical targets and updates the shared mute state.
static void CheckTimeSignals() {
    if (settingsTimeSignalTestActive || timeSignalVolumeDragging) {
        UpdateTimeSignalVolumePreview();
    }
    ULONGLONG timelineNow = MonotonicFileTimeValue();
    LONGLONG applicationOffset = GetApplicationTimeOffset(timelineNow);
    LONGLONG adjustment = currentTimeSignalOffset - applicationOffset;
    if (adjustment != 0) {
        AdjustTimeSignalPlaybackTime(adjustment);
        for (TimeSignalSourceGroup& group : currentTimeSignalSources) {
            group.target = static_cast<ULONGLONG>(static_cast<LONGLONG>(group.target) + adjustment);
        }
        currentTimeSignalOffset = applicationOffset;
    }
    ULONGLONG applicationNow = static_cast<ULONGLONG>(static_cast<LONGLONG>(timelineNow) + applicationOffset);
    for (std::vector<TimeSignalSourceGroup>::iterator group = currentTimeSignalSources.begin();
            group != currentTimeSignalSources.end();) {
        if (group->target + 10000000 < timelineNow) {
            group = currentTimeSignalSources.erase(group);
        } else {
            group++;
        }
    }
    bool generatedTone = IsTimeSignalGeneratorRequired() || generatedTimeSignal;
    std::wstring defaultOutput;
    UINT defaultOutputId = 0;
    if (generatedTone) {
        ResolveAudioOutputDevice(L"", &defaultOutput, &defaultOutputId);
    }
    std::vector<TimeSignalCandidate> candidates;
    for (size_t index = 0; index < widgets.size(); index++) {
        Widget* widget = widgets[index].get();
        int mode = static_cast<int>(widgets[index]->config.timeSignal);
        bool supportsSound = WidgetSupportsSound(widget->config.type);
        bool regularSignal = supportsSound
            && widget->config.timeSignalEnabled
            && mode > TIME_SIGNAL_NONE
            && mode < TIME_SIGNAL_COUNT;
        bool alarmSignal = supportsSound
            && widget->config.alarmEnabled
            && widget->config.alarmTimeSignal;
        if (!regularSignal && !alarmSignal) {
            continue;
        }
        std::wstring outputDevice = generatedTone ? widget->config.timeSignalOutputDevice : L"";
        if (outputDevice.empty()) {
            outputDevice = defaultOutput;
        }
        SYSTEMTIME displayed = {};
        GetDisplayedTime(widget->config, &displayed, applicationNow);
        ULONGLONG displayedValue = SystemTimeValue(displayed);
        if (displayedValue == 0) {
            continue;
        }
        displayedValue += applicationNow % 10000;
        ULONGLONG target = 0;
        if (!CalculateTimeSignalTarget(displayedValue, timelineNow, TIME_SIGNAL_EVERY_MINUTE, &target)) {
            continue;
        }
        SYSTEMTIME targetDisplayedTime = {};
        GetDisplayedTime(widget->config, &targetDisplayedTime, applicationNow + target - timelineNow);
        ULONGLONG targetDisplayedValue = SystemTimeValue(targetDisplayedTime);
        if (targetDisplayedValue == 0) {
            continue;
        }
        if (regularSignal && (!generatedTone || !outputDevice.empty())
                && IsTimeSignalBoundary(targetDisplayedValue, static_cast<TimeSignalMode>(mode))) {
            candidates.push_back(TimeSignalCandidate{ target, outputDevice, true, widget->config.id });
        }
        if (alarmSignal && (!generatedTone || !defaultOutput.empty())) {
            int targetDate = targetDisplayedTime.wYear * 10000 + targetDisplayedTime.wMonth * 100
                + targetDisplayedTime.wDay;
            int targetMinute = targetDisplayedTime.wHour * 60 + targetDisplayedTime.wMinute;
            if (AlarmEnabledOnDay(widget->config, targetDisplayedTime.wDayOfWeek)
                    && targetDisplayedTime.wHour == widget->config.alarmHour
                    && targetDisplayedTime.wMinute == widget->config.alarmMinute
                    && (widget->lastAlarmDate != targetDate || widget->lastAlarmMinute != targetMinute)) {
                candidates.push_back(TimeSignalCandidate{ target, defaultOutput, false, widget->config.id });
            }
        }
    }
    for (std::vector<TimeSignalSourceGroup>::iterator group = currentTimeSignalSources.begin();
            group != currentTimeSignalSources.end();) {
        if (group->target > timelineNow) {
            RetainCurrentTimeSignalSources(*group, candidates, true);
            RetainCurrentTimeSignalSources(*group, candidates, false);
        }
        bool shouldCancel = group->target > timelineNow + 5 * 10000000ULL
            && group->regularWidgetIds.empty() && group->alarmWidgetIds.empty();
        if (shouldCancel) {
            CancelTimeSignalPlayback(group->target, group->outputDevice);
        }
        if (shouldCancel && group->cancelledAlarmWidgetIds.empty()) {
            group = currentTimeSignalSources.erase(group);
        } else {
            group++;
        }
    }
    for (const TimeSignalCandidate& candidate : candidates) {
        if (!candidate.regular) {
            bool cancelled = false;
            for (const TimeSignalSourceGroup& group : currentTimeSignalSources) {
                if (candidate.target == group.target
                    && std::find(group.cancelledAlarmWidgetIds.begin(),
                        group.cancelledAlarmWidgetIds.end(),
                        candidate.widgetId) != group.cancelledAlarmWidgetIds.end()) {
                    cancelled = true;
                    break;
                }
            }
            if (cancelled) {
                continue;
            }
        }
        std::vector<TimeSignalSourceGroup>::iterator existing = currentTimeSignalSources.begin();
        while (existing != currentTimeSignalSources.end()) {
            if (candidate.target == existing->target && candidate.outputDevice == existing->outputDevice) {
                break;
            }
            existing++;
        }
        if (existing == currentTimeSignalSources.end() || adjustment != 0
                || existing->regularWidgetIds.empty() && existing->alarmWidgetIds.empty()) {
            if (!StartTimeSignalPlayback(candidate.target, true, generatedTimeSignal,
                timeSignalVolume, hController, WM_TIME_SIGNAL_FINISHED, candidate.outputDevice)) {
                continue;
            }
            if (existing == currentTimeSignalSources.end()) {
                currentTimeSignalSources.push_back(TimeSignalSourceGroup{
                    candidate.target, candidate.outputDevice });
                existing = currentTimeSignalSources.end() - 1;
            }
        }
        std::vector<int>& sourceIds = candidate.regular
            ? existing->regularWidgetIds
            : existing->alarmWidgetIds;
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
bool CopyTextToClipboard(HWND owner, const std::wstring& text) {
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
    bool copied = EmptyClipboard() && SetClipboardData(CF_UNICODETEXT, memory) != nullptr;
    if (!copied) {
        GlobalFree(memory);
    }
    CloseClipboard();
    return copied;
}

/// Formats and copies a calendar date, showing a confirmation tooltip only after a successful clipboard
/// update.
static void CopyWidgetDate(Widget* widget, const SYSTEMTIME& date) {
    if (widget == nullptr) {
        return;
    }
    std::wstring text = FormatWidgetDate(widget->config, date, widget->config.dateCopyFormat);
    if (CopyTextToClipboard(widget->window, text)) {
        ShowCopiedDateTooltip(widget, text);
    }
}

/// Measures a native calendar for the widget's locale, font, theme, and display options, caching matching
/// results.
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
    SIZE size = { config.weekNumbers ? 250 : 227, 160 };
    DWORD style = WS_POPUP | (config.weekNumbers ? MCS_WEEKNUMBERS : 0);
    if (!showToday) {
        style |= MCS_NOTODAY;
    }
    CalendarLocaleScope localeScope(GetLanguageLocale(config.language));
    HWND calendar =
        CreateWindowExW(0, MONTHCAL_CLASSW, L"", style, 0, 0, 0, 0, nullptr, nullptr, hInstance, nullptr);
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

/// Measures a stable time-text extent using the widest digit and applicable AM/PM markers in the selected
/// GDI font.
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
    const wchar_t* format = show
        ? GetLocalizedText(language, TXT_ADDITIONAL_CLOCK_SHOW_FORMAT)
        : GetLocalizedText(language, TXT_ADDITIONAL_CLOCK_NAME_FORMAT);
    wchar_t text[128] = {};
    swprintf_s(text, format, index + 1);
    return text;
}

/// Returns the stored additional-clock name unchanged, including an intentionally empty name.
static std::wstring AdditionalClockName(const WidgetConfig& config, int index) {
    return config.additionalClocks[index].name;
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

/// Derives a panel clock configuration with its own time zone and size and with seconds and explicit UTC
/// text disabled.
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
        width = std::max(width, static_cast<int>(extent.cx) + 6);
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

/// Measures panel content and applies the modern native flyout's font, relative-pixel, and column layout
/// rules.
static PanelLayout CalculatePanelLayout(const WidgetConfig& config,
        const std::vector<TimeDateNotice>* notices = nullptr, ULONGLONG applicationUtc = 0) {
    PanelLayout layout;
    SIZE calendarSize = GetCalendarSize(config, true);
    bool additional = HasAdditionalClocks(config);
    SYSTEMTIME displayed = {};
    GetDisplayedTime(config, &displayed, applicationUtc);
    wchar_t dateText[256] = {};
    wchar_t dayText[128] = {};
    int dateLength = GetDateFormatEx(GetLanguageLocale(config.language), DATE_LONGDATE, &displayed, nullptr,
        dateText, ARRAYSIZE(dateText), nullptr);
    int dayLength = GetDateFormatEx(GetLanguageLocale(config.language), 0, &displayed, L"dddd", dayText,
        ARRAYSIZE(dayText), nullptr);
    bool mainDay = additional || dateLength > 0 && dayLength > 0 && wcsstr(dateText, dayText) == nullptr;
    HDC dc = GetDC(nullptr);
    int dpi = dc == nullptr ? 96 : GetDeviceCaps(dc, LOGPIXELSY);
    int sidePadding = MulDiv(14, dpi, 96);
    int bodyPadding = MulDiv(10, dpi, 96);
    int clockPadding = MulDiv(4, dpi, 96);
    int extraPadding = MulDiv(8, dpi, 96);
    int timeTextHeight = MulDiv(15, dpi, 96);
    int topTextHeight = timeTextHeight;
    int footerTextHeight = timeTextHeight;
    int weekdayWidth = 0;
    int dateWidth = 0;
    int nameWidths[ADDITIONAL_CLOCK_COUNT] = {};
    HFONT font = CreatePanelFont(config.panelTimeFont, config.fontAntialiasing);
    if (dc != nullptr && font != nullptr) {
        HGDIOBJ previousFont = SelectObject(dc, font);
        TEXTMETRICW metrics = {};
        if (GetTextMetricsW(dc, &metrics)) {
            timeTextHeight = metrics.tmHeight;
        }
        if (mainDay) {
            SYSTEMTIME date = { 2026, 9, 0, 1, 0, 0, 0, 0 };
            for (int day = 1; day <= 7; day++) {
                date.wDay = static_cast<WORD>(day);
                wchar_t text[128] = {};
                GetDateFormatEx(GetLanguageLocale(config.language), 0, &date, L"dddd", text, ARRAYSIZE(text),
                    nullptr);
                SIZE extent = {};
                GetTextExtentPoint32W(dc, text, static_cast<int>(wcslen(text)), &extent);
                weekdayWidth = std::max(weekdayWidth, static_cast<int>(extent.cx));
            }
        }
        SelectObject(dc, previousFont);
    }
    if (font != nullptr) {
        DeleteObject(font);
    }
    font = CreatePanelFont(config.panelTopFont, config.fontAntialiasing);
    if (dc != nullptr && font != nullptr) {
        HGDIOBJ previousFont = SelectObject(dc, font);
        TEXTMETRICW metrics = {};
        if (GetTextMetricsW(dc, &metrics)) {
            topTextHeight = metrics.tmHeight;
        }
        SIZE extent = {};
        GetTextExtentPoint32W(dc, dateText, static_cast<int>(wcslen(dateText)), &extent);
        dateWidth = extent.cx;
        for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
            if (config.additionalClocks[index].enabled) {
                std::wstring name = AdditionalClockName(config, index);
                GetTextExtentPoint32W(dc, name.c_str(), static_cast<int>(name.size()), &extent);
                nameWidths[index] = extent.cx;
            }
        }
        SelectObject(dc, previousFont);
    }
    if (font != nullptr) {
        DeleteObject(font);
    }
    font = CreatePanelFont(config.panelBottomFont, config.fontAntialiasing);
    if (dc != nullptr && font != nullptr) {
        HGDIOBJ previousFont = SelectObject(dc, font);
        TEXTMETRICW metrics = {};
        if (GetTextMetricsW(dc, &metrics)) {
            footerTextHeight = metrics.tmHeight;
        }
        SelectObject(dc, previousFont);
    }
    if (font != nullptr) {
        DeleteObject(font);
    }
    if (dc != nullptr) {
        ReleaseDC(nullptr, dc);
    }
    int digitalHeight = timeTextHeight + 2;
    int mainHeight = clockPadding + config.size + clockPadding + digitalHeight;
    if (mainDay) {
        mainHeight += clockPadding + timeTextHeight;
    }
    int extraClockHeight = 0;
    for (const AdditionalClockConfig& clock : config.additionalClocks) {
        if (clock.enabled) {
            extraClockHeight = std::max(extraClockHeight, NormalizeAnalogClockSize(clock.size));
        }
    }
    int extraHeight = additional ? extraPadding + topTextHeight + clockPadding + extraClockHeight
        + clockPadding + digitalHeight + clockPadding + timeTextHeight : 0;
    int bodyHeight = std::max(static_cast<int>(calendarSize.cy) + bodyPadding, mainHeight);
    bodyHeight = std::max(bodyHeight, extraHeight);
    int bodyTop = sidePadding + topTextHeight + bodyPadding;
    int calendarTop = bodyTop + (bodyHeight - calendarSize.cy - bodyPadding) / 2;
    layout.calendar = RECT{
        sidePadding,
        calendarTop,
        sidePadding + calendarSize.cx,
        calendarTop + calendarSize.cy
    };
    int mainTop = bodyTop + (bodyHeight - mainHeight) / 2 + clockPadding;
    int nameTop = bodyTop + (bodyHeight - extraHeight) / 2 + extraPadding;
    int extraTop = nameTop + topTextHeight + clockPadding;
    int clockBottom = mainTop + config.size;
    if (additional) {
        clockBottom = std::max(clockBottom, extraTop + extraClockHeight);
    }
    int timeTop = clockBottom + clockPadding;
    int dayTop = timeTop + digitalHeight + clockPadding;
    int left = layout.calendar.right + bodyPadding;
    int extraCount = 0;
    for (int index = 0; index <= ADDITIONAL_CLOCK_COUNT; index++) {
        if (index > 0 && !config.additionalClocks[index - 1].enabled) {
            continue;
        }
        WidgetConfig clock = index == 0 ? config : AdditionalClockConfiguration(config, index - 1);
        int width = std::max(GetPanelClockGroupWidth(clock), weekdayWidth);
        if (index > 0) {
            if (extraCount > 0) {
                left += 10;
            }
            width = std::max(width, nameWidths[index - 1]);
            extraCount++;
        }
        int clockLeft = left + (width - clock.size) / 2;
        POINT faceCenter = GetAnalogClockFaceCenter(clock.size);
        int textLeft = clockLeft + faceCenter.x - width / 2;
        int clockTop = clockBottom - clock.size;
        layout.clocks[index] = RECT{ clockLeft, clockTop, clockLeft + clock.size, clockTop + clock.size };
        layout.times[index] = RECT{ textLeft, timeTop, textLeft + width, timeTop + timeTextHeight };
        if (index > 0 || mainDay) {
            layout.days[index] = RECT{ textLeft, dayTop, textLeft + width, dayTop + timeTextHeight };
        }
        if (index > 0) {
            int captionTop = clockTop - clockPadding - topTextHeight;
            layout.names[index - 1] = RECT{ left, captionTop, left + width, captionTop + topTextHeight };
        }
        left += width;
        if (index == 0 && additional) {
            left += bodyPadding;
        }
    }
    layout.clientSize.cx = std::max(left + sidePadding, dateWidth);
    layout.header = RECT{ 0, sidePadding, layout.clientSize.cx, sidePadding + topTextHeight };
    int footerTop = bodyTop + bodyHeight + bodyPadding;
    if (config.panelTimeNotices && notices != nullptr && !notices->empty()) {
        HDC noticeDC = GetDC(nullptr);
        HFONT noticeFont = CreatePanelFont(config.panelBottomFont, config.fontAntialiasing);
        if (noticeDC != nullptr && noticeFont != nullptr) {
            HGDIOBJ previousFont = SelectObject(noticeDC, noticeFont);
            TEXTMETRICW metrics = {};
            if (GetTextMetricsW(noticeDC, &metrics)) {
                int rowPadding = MulDiv(8, dpi, 96);
                int textPaddingTop = MulDiv(5, dpi, 96);
                int separatorHeight = MulDiv(2, dpi, 96);
                int iconSize = MulDiv(16, dpi, 96);
                int iconLeft = rowPadding;
                int textLeft = iconLeft + iconSize + rowPadding;
                int textWidth = std::max(1L, layout.clientSize.cx - rowPadding - textLeft);
                for (const TimeDateNotice& notice : *notices) {
                    RECT measured = { 0, 0, textWidth, 0 };
                    DrawTextW(noticeDC, notice.text.c_str(), static_cast<int>(notice.text.size()), &measured,
                        DT_CALCRECT | DT_WORDBREAK | DT_NOFULLWIDTHCHARBREAK | DT_NOPREFIX);
                    int textHeight = std::max(metrics.tmHeight, measured.bottom - measured.top);
                    int rowHeight = std::max(iconSize + rowPadding + rowPadding, textHeight + textPaddingTop);
                    int rowTop = footerTop + separatorHeight;
                    PanelNoticeLayout row;
                    row.separator = RECT{ 0, footerTop, layout.clientSize.cx, rowTop };
                    row.icon = RECT{
                        iconLeft,
                        rowTop + rowPadding,
                        iconLeft + iconSize,
                        rowTop + rowPadding + iconSize
                    };
                    row.text = RECT{
                        textLeft,
                        rowTop + textPaddingTop,
                        textLeft + textWidth,
                        rowTop + textPaddingTop + textHeight
                    };
                    layout.notices.push_back(row);
                    footerTop = rowTop + rowHeight + rowPadding;
                }
                layout.noticeBottomSeparator = RECT{
                    0,
                    footerTop,
                    layout.clientSize.cx,
                    footerTop + separatorHeight
                };
                footerTop += separatorHeight;
            }
            SelectObject(noticeDC, previousFont);
        }
        if (noticeFont != nullptr) {
            DeleteObject(noticeFont);
        }
        if (noticeDC != nullptr) {
            ReleaseDC(nullptr, noticeDC);
        }
    }
    int footerPadding = MulDiv(14, dpi, 96);
    layout.footer = RECT{
        0,
        footerTop,
        layout.clientSize.cx,
        footerTop + footerTextHeight + footerPadding + footerPadding
    };
    layout.clientSize.cy = layout.footer.bottom;
    return layout;
}

/// Calculates outer widget dimensions from its type, content, font, padding, border, and selected monitor.
static void GetWidgetDimensions(const WidgetConfig& config, int* width, int* height,
        const std::vector<TimeDateNotice>* notices = nullptr, ULONGLONG applicationUtc = 0) {
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
        *height = std::max(38, std::max(static_cast<int>(extent.cy),
            static_cast<int>(metrics.tmHeight)) + inset * 2 + 4);
        if (!config.transparentBackground) {
            DWORD style = WS_POPUP;
            DWORD extendedStyle = WS_EX_TOOLWINDOW;
            ApplyNativeBorderStyle(config.borderStyle, &style, &extendedStyle);
            RECT rect = { 0, 0, *width, *height };
            if (AdjustWindowRectEx(&rect, style, FALSE, extendedStyle)) {
                *width = rect.right - rect.left;
                *height = rect.bottom - rect.top;
            }
        }
    } else if (config.type == WIDGET_CALENDAR) {
        *width = calendarSize.cx;
        *height = calendarSize.cy;
    } else {
        PanelLayout layout = CalculatePanelLayout(config, notices, applicationUtc);
        *width = layout.clientSize.cx;
        *height = layout.clientSize.cy;
    }
    if (config.type == WIDGET_CALENDAR || config.type == WIDGET_PANEL) {
        DWORD style = WS_POPUP | WS_CLIPCHILDREN;
        DWORD extendedStyle = WS_EX_TOOLWINDOW;
        ApplyNativeBorderStyle(config.borderStyle, &style, &extendedStyle);
        RECT rect = { 0, 0, *width, *height };
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
    MONITORINFO information = { sizeof(information) };
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
    POINT position = { widget->config.x, widget->config.y };
    if (GetPositionPreservingWorkAreaAttachment(widget->window, width, height, &position)) {
        widget->config.x = position.x;
        widget->config.y = position.y;
        flags &= ~SWP_NOMOVE;
    }
    SetWindowPos(widget->window, nullptr, position.x, position.y, width, height, flags);
}

/// Copies the requested calendar, primary clock, and time-text rectangles from the calculated panel layout.
static void GetPanelLayout(const WidgetConfig& config, RECT* calendarRect, POINT* clockPosition,
        RECT* timeRect, const std::vector<TimeDateNotice>* notices = nullptr, ULONGLONG applicationUtc = 0) {
    PanelLayout layout = CalculatePanelLayout(config, notices, applicationUtc);
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
static void ClampWidgetPosition(WidgetConfig* config, const std::vector<TimeDateNotice>* notices = nullptr) {
    int width = 0;
    int height = 0;
    GetWidgetDimensions(*config, &width, &height, notices);
    RECT desired = { config->x, config->y, config->x + width, config->y + height };
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
    config->x = width >= workRight - workLeft
        ? workLeft
        : std::clamp(config->x, workLeft, workRight - width);
    config->y = height >= workBottom - workTop
        ? workTop
        : std::clamp(config->y, workTop, workBottom - height);
}

/// Constrains a saved form position to the nearest work area while preserving CW_USEDEFAULT coordinates.
static void ClampFormPosition(int* x, int* y, int width, int height) {
    if (*x == CW_USEDEFAULT || *y == CW_USEDEFAULT) {
        return;
    }
    RECT desired = { *x, *y, *x + width, *y + height };
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
            ? T(TXT_SYSTEM_DEFAULT_FONT_LABEL)
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

/// Reports whether the effective application font overrides the native system face or style.
bool HasApplicationUiFont() {
    const std::wstring& face = settingsApplicationFontPreviewActive ? settingsAppFontFace : appFontFace;
    int weight = settingsApplicationFontPreviewActive ? settingsAppFontWeight : appFontWeight;
    bool italic = settingsApplicationFontPreviewActive ? settingsAppFontItalic : appFontItalic;
    return !face.empty() || weight != FW_NORMAL || italic;
}

/// Creates the effective application face and style at the native system font size and window DPI.
HFONT CreateApplicationUiFont(HWND window) {
    HFONT systemFont = CreateSystemDialogFont(window);
    if (systemFont == nullptr) {
        return nullptr;
    }
    LOGFONTW font = {};
    bool described = GetObjectW(systemFont, sizeof(font), &font) != 0;
    DeleteObject(systemFont);
    if (!described) {
        return nullptr;
    }
    const std::wstring& face = settingsApplicationFontPreviewActive ? settingsAppFontFace : appFontFace;
    font.lfWeight = settingsApplicationFontPreviewActive ? settingsAppFontWeight : appFontWeight;
    font.lfItalic = settingsApplicationFontPreviewActive ? settingsAppFontItalic : appFontItalic;
    font.lfQuality = FontQuality(appFontAntialiasing);
    if (!face.empty()) {
        wcsncpy_s(font.lfFaceName, face.c_str(), _TRUNCATE);
        font.lfCharSet = DEFAULT_CHARSET;
    }
    return CreateFontIndirectW(&font);
}

/// Replaces the application font in open dialogs before releasing their previous shared font.
/// Defers final settings alignment and optional recreation until font changes and the button click complete.
static void RefreshApplicationFonts(bool rebuildSettings = true) {
    HFONT font = CreateApplicationUiFont(hSettings);
    if (font == nullptr) {
        return;
    }
    HFONT previous = hUiFont;
    hUiFont = font;
    const HWND windows[] = { hSettings, helpForm.GetWindow(), aboutForm.GetWindow() };
    for (HWND window : windows) {
        if (window != nullptr) {
            ApplyUiStyle(window);
        }
    }
    if (previous != nullptr) {
        DeleteObject(previous);
    }
    if (hSettings != nullptr) {
        PostMessageW(hSettings, WM_UPDATE_SETTINGS_CONTROL_METRICS, rebuildSettings, 0);
    }
}

/// Applies draft application font choices to open forms while retaining committed settings for restoration.
static void ApplyApplicationFontPreview() {
    settingsApplicationFontPreviewActive = true;
    RefreshApplicationFonts();
}

/// Restores committed application fonts after a preview and releases the temporary font when replaced.
static void RestoreApplicationFontPreview() {
    if (!settingsApplicationFontPreviewActive) {
        return;
    }
    settingsApplicationFontPreviewActive = false;
    RefreshApplicationFonts();
}

/// Returns the native combo inside a ComboBoxEx, or the original handle for other controls.
static HWND GetSettingsComboBox(HWND window) {
    wchar_t className[32] = {};
    GetClassNameW(window, className, ARRAYSIZE(className));
    if (_wcsicmp(className, WC_COMBOBOXEXW) == 0) {
        return reinterpret_cast<HWND>(SendMessageW(window, CBEM_GETCOMBOCONTROL, 0, 0));
    }
    return window;
}

/// Applies the current application UI font and theme policy to a child.
static BOOL CALLBACK ApplyFontAndTheme(HWND child, LPARAM) {
    HWND parent = GetParent(child);
    if (GetSettingsComboBox(parent) == child) {
        return TRUE;
    }
    HFONT font = hUiFont;
    if (font != nullptr) {
        SendMessageW(child, WM_SETFONT, reinterpret_cast<WPARAM>(font), TRUE);
    }
    const wchar_t* themeName = themesDisabled ? L"" : nullptr;
    SetWindowTheme(child, themeName, themeName);
    HWND combo = GetSettingsComboBox(child);
    if (combo != child) {
        SetWindowTheme(combo, themeName, themeName);
    }
    if (IsSettingsPageWindow(child)) {
        EnableThemeDialogTexture(child, themesDisabled ? ETDT_DISABLE : ETDT_ENABLETAB);
    }
    return TRUE;
}

/// Recognizes Unicode whitespace for license text and descriptive-text layout.
bool IsUnicodeWhitespace(wchar_t character) {
    WORD type = 0;
    return GetStringTypeW(CT_CTYPE1, &character, 1, &type) && (type & C1_SPACE) != 0;
}

/// Measures a plain-text line from the selected font's typographic metrics and the actual glyph bounds.
static UiTextLine GetUiTextLine(HDC dc, const std::wstring& text) {
    TEXTMETRICW metrics = {};
    GetTextMetricsW(dc, &metrics);
    UiTextLine line = { metrics.tmAscent, metrics.tmDescent, metrics.tmExternalLeading };
    UINT size = GetOutlineTextMetricsW(dc, 0, nullptr);
    if (size == 0) {
        return line;
    }
    std::vector<BYTE> data(size);
    OUTLINETEXTMETRICW* outline = reinterpret_cast<OUTLINETEXTMETRICW*>(data.data());
    if (GetOutlineTextMetricsW(dc, size, outline) == 0) {
        return line;
    }
    UiTextLine typographic = {
        outline->otmAscent, std::abs(outline->otmDescent),
        static_cast<LONG>(outline->otmLineGap)
    };
    MAT2 transform = {
        FIXED{ 0, 1 },
        FIXED{ 0, 0 },
        FIXED{ 0, 0 },
        FIXED{ 0, 1 }
    };
    for (wchar_t character : text) {
        if (IsUnicodeWhitespace(character)) {
            continue;
        }
        GLYPHMETRICS glyph = {};
        if (GetGlyphOutlineW(dc, character, GGO_METRICS, &glyph, 0, nullptr, &transform) != GDI_ERROR) {
            typographic.ascent = std::max(typographic.ascent, glyph.gmptGlyphOrigin.y);
            typographic.descent = std::max(typographic.descent,
                static_cast<LONG>(glyph.gmBlackBoxY) - glyph.gmptGlyphOrigin.y);
        }
    }
    if (typographic.ascent + typographic.descent + typographic.gap < metrics.tmHeight
            + metrics.tmExternalLeading) {
        line = typographic;
    }
    return line;
}

/// Measures all localized NTP states together so their text uses one stable set of font metrics.
static UiTextLine GetNtpStatusLine(HDC dc) {
    const TextId messages[] = {
        TXT_NTP_STATUS_SYSTEM,
        TXT_NTP_STATUS_WAITING,
        TXT_NTP_STATUS_FAILED,
        TXT_NTP_STATUS_RETAINED,
        TXT_NTP_STATUS_SYNCHRONIZED
    };
    std::wstring metricsText = L"Θ = +−0123456789.,:()";
    for (TextId message : messages) {
        metricsText += T(message);
    }
    return GetUiTextLine(dc, metricsText);
}

/// Sizes list-box rows from their actual text and selected font, preserving native strings and selection
/// handling.
static void UpdateSettingsListMetrics(HWND list) {
    HDC dc = GetDC(list);
    if (dc == nullptr) {
        return;
    }
    HFONT font = reinterpret_cast<HFONT>(SendMessageW(list, WM_GETFONT, 0, 0));
    HGDIOBJ previous = font == nullptr ? nullptr : SelectObject(dc, font);
    std::wstring text;
    LRESULT count = SendMessageW(list, LB_GETCOUNT, 0, 0);
    for (LRESULT index = 0; index < count; index++) {
        LRESULT length = SendMessageW(list, LB_GETTEXTLEN, index, 0);
        if (length != LB_ERR) {
            std::wstring item(static_cast<size_t>(length) + 1, L'\0');
            SendMessageW(list, LB_GETTEXT, index, reinterpret_cast<LPARAM>(item.data()));
            text.append(item.data(), static_cast<size_t>(length));
        }
    }
    UiTextLine line = GetUiTextLine(dc, text);
    int height = std::max(1L, line.ascent + line.descent + line.gap) + 2 * GetSystemMetrics(SM_CYBORDER);
    if (SendMessageW(list, LB_GETITEMHEIGHT, 0, 0) != height) {
        SendMessageW(list, LB_SETITEMHEIGHT, 0, height);
    }
    if (previous != nullptr && previous != HGDI_ERROR) {
        SelectObject(dc, previous);
    }
    ReleaseDC(list, dc);
}

/// Draws settings list text inside its native row while retaining system selection colors and focus cues.
static bool DrawSettingsListItem(const DRAWITEMSTRUCT* item) {
    if (item == nullptr || item->CtlType != ODT_LISTBOX) {
        return false;
    }
    int saved = SaveDC(item->hDC);
    bool disabled = !IsWindowEnabled(item->hwndItem);
    bool selected = (item->itemState & ODS_SELECTED) != 0 && !disabled;
    FillRect(item->hDC, &item->rcItem,
        GetSysColorBrush(disabled ? COLOR_BTNFACE : selected ? COLOR_HIGHLIGHT : COLOR_WINDOW));
    SetTextColor(item->hDC,
        GetSysColor(disabled ? COLOR_GRAYTEXT : selected ? COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT));
    SetBkMode(item->hDC, TRANSPARENT);
    HFONT font = reinterpret_cast<HFONT>(SendMessageW(item->hwndItem, WM_GETFONT, 0, 0));
    if (font != nullptr) {
        SelectObject(item->hDC, font);
    }
    if (item->itemID != static_cast<UINT>(-1)) {
        LRESULT length = SendMessageW(item->hwndItem, LB_GETTEXTLEN, item->itemID, 0);
        if (length != LB_ERR) {
            std::wstring text(static_cast<size_t>(length) + 1, L'\0');
            SendMessageW(item->hwndItem, LB_GETTEXT, item->itemID, reinterpret_cast<LPARAM>(text.data()));
            RECT content = item->rcItem;
            content.left += GetSystemMetrics(SM_CXBORDER);
            DrawTextW(item->hDC, text.data(), static_cast<int>(length), &content,
                DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
        }
    }
    if ((item->itemState & ODS_FOCUS) != 0 && (item->itemState & ODS_NOFOCUSRECT) == 0) {
        DrawFocusRect(item->hDC, &item->rcItem);
    }
    RestoreDC(item->hDC, saved);
    return true;
}

/// Paints the complete widget list into one buffer before presenting its rows and empty background together.
static LRESULT PaintSettingsWidgetList(HWND window) {
    PAINTSTRUCT paint = {};
    HDC target = BeginPaint(window, &paint);
    if (target == nullptr) {
        return 0;
    }
    RECT client = {};
    GetClientRect(window, &client);
    HDC dc = nullptr;
    HPAINTBUFFER buffer = BeginBufferedPaint(target, &client, BPBF_TOPDOWNDIB, nullptr, &dc);
    if (buffer == nullptr) {
        dc = target;
    }
    DefSubclassProc(window, WM_ERASEBKGND, reinterpret_cast<WPARAM>(dc), 0);
    DefSubclassProc(window, WM_PRINTCLIENT, reinterpret_cast<WPARAM>(dc), PRF_CLIENT | PRF_ERASEBKGND);
    if (buffer != nullptr) {
        EndBufferedPaint(buffer, TRUE);
    }
    EndPaint(window, &paint);
    return 0;
}

/// Reads an authored resource rectangle in the containing dialog's current client coordinates.
static RECT GetSettingsResourceRect(HWND parent, int id) {
    RECT bounds = {};
    HWND control = GetDlgItem(parent, id);
    if (control != nullptr && GetWindowRect(control, &bounds)) {
        MapWindowPoints(HWND_DESKTOP, parent, reinterpret_cast<POINT*>(&bounds), 2);
    }
    return bounds;
}

/// Maps a horizontal dialog-unit distance using the current interface font.
static int SettingsDialogWidth(int value) {
    SIZE units = {};
    if (!GetDialogFontBaseUnits(hUiFont, &units)) {
        return 0;
    }
    return MulDiv(value, units.cx, 4);
}

/// Maps a vertical dialog-unit distance using the current interface font and existing button height limit.
static int SettingsDialogHeight(int value) {
    SIZE units = {};
    if (!GetDialogFontBaseUnits(hUiFont, &units)) {
        return 0;
    }
    return DialogHeightFromUnits(value, units.cy);
}

/// Reads the selected control font's native metrics in its current device context without substituting
/// a font.
static bool GetSettingsTextMetrics(HWND control, TEXTMETRICW* metrics) {
    HDC dc = GetDC(control);
    if (dc == nullptr) {
        return false;
    }
    HFONT font = reinterpret_cast<HFONT>(SendMessageW(control, WM_GETFONT, 0, 0));
    HGDIOBJ previous = font == nullptr ? nullptr : SelectObject(dc, font);
    bool measured = GetTextMetricsW(dc, metrics) != FALSE;
    if (previous != nullptr && previous != HGDI_ERROR) {
        SelectObject(dc, previous);
    }
    ReleaseDC(control, dc);
    return measured;
}

/// Sizes combo rows from their selected font up to the settings height limit, retaining native border
/// dimensions.
static void UpdateSettingsComboMetrics(HWND control) {
    HWND combo = GetSettingsComboBox(control);
    RECT bounds = {};
    if (combo == nullptr || !GetWindowRect(combo, &bounds)) {
        return;
    }
    LRESULT selectionHeight = SendMessageW(combo, CB_GETITEMHEIGHT, static_cast<WPARAM>(-1), 0);
    if (selectionHeight == CB_ERR) {
        return;
    }
    TEXTMETRICW metrics = {};
    if (!GetSettingsTextMetrics(combo, &metrics)) {
        return;
    }
    LONG chromeHeight = bounds.bottom - bounds.top - static_cast<LONG>(selectionHeight);
    LONG desired = std::max(1L, std::min(metrics.tmHeight + 2 * GetSystemMetrics(SM_CYBORDER),
        SettingsDialogHeight(11) - chromeHeight));
    if (selectionHeight != desired) {
        SendMessageW(combo, CB_SETITEMHEIGHT, static_cast<WPARAM>(-1), desired);
    }
    LONG itemHeight = std::min(metrics.tmHeight, static_cast<LONG>(SettingsDialogHeight(11)));
    if (SendMessageW(combo, CB_GETITEMHEIGHT, 0, 0) != itemHeight) {
        SendMessageW(combo, CB_SETITEMHEIGHT, 0, itemHeight);
    }
    if (combo != control) {
        RECT field = {};
        RECT outer = {};
        if (!GetWindowRect(combo, &field) || !GetWindowRect(control, &outer)) {
            return;
        }
        if (outer.bottom - outer.top != field.bottom - field.top) {
            SetWindowPos(control, nullptr, 0, 0, outer.right - outer.left, field.bottom - field.top,
                SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
        }
    }
}

/// Sizes the edit viewport from its selected font up to the height limit and uses native combo margins.
/// Uses current theme or system borders and preserves position, width, and the right margin.
static void UpdateEditMetrics(HWND edit) {
    HWND frame = SettingsEdit::GetFrame(edit);
    WINDOWINFO information = {};
    information.cbSize = sizeof(information);
    if (edit == nullptr || !GetWindowInfo(frame, &information)) {
        return;
    }
    TEXTMETRICW metrics = {};
    if (!GetSettingsTextMetrics(edit, &metrics)) {
        return;
    }
    LONG contentLeft = GetSystemMetrics(SM_CXEDGE) + GetSystemMetrics(SM_CXBORDER);
    LONG contentTop = GetSystemMetrics(SM_CYEDGE) + GetSystemMetrics(SM_CYBORDER);
    LONG contentBottom = contentTop;
    if (GetWindowTheme(frame) != nullptr) {
        HTHEME theme = OpenThemeData(nullptr, L"Combobox");
        if (theme != nullptr) {
            RECT bounds = {
                0,
                0,
                information.rcWindow.right - information.rcWindow.left,
                information.rcWindow.bottom - information.rcWindow.top
            };
            RECT content = {};
            HRESULT result =
                GetThemeBackgroundContentRect(theme, nullptr, CP_READONLY, CBRO_NORMAL, &bounds, &content);
            if (SUCCEEDED(result)) {
                contentLeft = content.left;
                contentTop = content.top;
                contentBottom = bounds.bottom - content.bottom;
            }
            CloseThemeData(theme);
        }
    }
    LONG borderWidth = information.rcClient.left - information.rcWindow.left;
    LONG leftMargin = std::max(0L, contentLeft - borderWidth);
    DWORD margins = static_cast<DWORD>(SendMessageW(edit, EM_GETMARGINS, 0, 0));
    if (LOWORD(margins) != leftMargin) {
        SendMessageW(edit, EM_SETMARGINS, EC_LEFTMARGIN, MAKELPARAM(leftMargin, 0));
    }
    LONG height = std::min(static_cast<LONG>(SettingsDialogHeight(11)),
        metrics.tmHeight + contentTop + contentBottom + 2 * GetSystemMetrics(SM_CYBORDER));
    if (height != information.rcWindow.bottom - information.rcWindow.top) {
        SetWindowPos(frame, nullptr, 0, 0, information.rcWindow.right - information.rcWindow.left, height,
            SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
    }
    SettingsEdit::UpdateLayout(edit);
}

/// Measures report rows in the current font without moving or resizing the control.
/// The monitor list enables owner measurement only for layout and restores native painting before redraw.
static void UpdateSettingsReportMetrics(HWND list) {
    if (list == nullptr) {
        return;
    }
    RECT bounds = {};
    GetWindowRect(list, &bounds);
    WINDOWPOS position = {
        list,
        nullptr,
        0,
        0,
        bounds.right - bounds.left,
        bounds.bottom - bounds.top,
        SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE
    };
    bool measureMonitor =
        list == hMonitorList && (GetWindowLongPtrW(list, GWL_STYLE) & LVS_OWNERDRAWFIXED) == 0;
    if (measureMonitor) {
        WindowRedrawScope redraw(list);
        SetWindowLongPtrW(list, GWL_STYLE, GetWindowLongPtrW(list, GWL_STYLE) | LVS_OWNERDRAWFIXED);
        SendMessageW(list, WM_WINDOWPOSCHANGED, 0, reinterpret_cast<LPARAM>(&position));
        SetWindowLongPtrW(list, GWL_STYLE, GetWindowLongPtrW(list, GWL_STYLE) & ~LVS_OWNERDRAWFIXED);
    } else {
        SendMessageW(list, WM_WINDOWPOSCHANGED, 0, reinterpret_cast<LPARAM>(&position));
    }
}

/// Restores native tab sizing for the selected font, limits excessive header height, and fits each page to
/// its display area.
static void UpdateSettingsTabLayout() {
    if (hTabs == nullptr || TabCtrl_GetItemCount(hTabs) == 0) {
        return;
    }
    TabCtrl_SetItemSize(hTabs, 0, 0);
    RECT header = {};
    if (TabCtrl_GetItemRect(hTabs, 0, &header) && header.bottom - header.top > SettingsDialogHeight(11)) {
        TabCtrl_SetItemSize(hTabs, 0, SettingsDialogHeight(11));
    }
    RECT display = {};
    GetClientRect(hTabs, &display);
    TabCtrl_AdjustRect(hTabs, FALSE, &display);
    MapWindowPoints(hTabs, GetParent(hTabs), reinterpret_cast<POINT*>(&display), 2);
    for (int index = 0; index < SETTINGS_TAB_COUNT; index++) {
        HWND page = GetSettingsPage(index);
        RECT bounds = {};
        if (page != nullptr && GetWindowRect(page, &bounds)) {
            MapWindowPoints(HWND_DESKTOP, GetParent(page), reinterpret_cast<POINT*>(&bounds), 2);
            if (!EqualRect(&bounds, &display)) {
                SetWindowPos(page, nullptr, display.left, display.top, display.right - display.left,
                    display.bottom - display.top, SWP_NOZORDER | SWP_NOACTIVATE);
            }
        }
    }
}

/// Reports whether visual styles are active for Windows and the current application.
static bool AreVisualStylesActive() {
    return IsThemeActive() && IsAppThemed();
}

/// Draws the native button theme in window or client coordinates, clipped to the requested preview area.
/// Uses the associated button's enabled state and leaves classic rendering to the native static control.
static bool DrawSettingsColorPreviewTheme(HWND preview, HDC dc, bool nonClient) {
    HWND button = reinterpret_cast<HWND>(GetPropW(preview, SETTINGS_COLOR_BUTTON_PROPERTY));
    WINDOWINFO information = { sizeof(information) };
    if (button == nullptr || dc == nullptr || themesDisabled || !AreVisualStylesActive()
            || !GetWindowInfo(preview, &information)) {
        return false;
    }
    HTHEME theme = OpenThemeData(button, L"Button");
    if (theme == nullptr) {
        return false;
    }
    const RECT& origin = nonClient ? information.rcWindow : information.rcClient;
    RECT bounds = information.rcWindow;
    RECT client = information.rcClient;
    OffsetRect(&bounds, -origin.left, -origin.top);
    OffsetRect(&client, -origin.left, -origin.top);
    int saved = SaveDC(dc);
    bool drawn = false;
    if (saved != 0) {
        if (nonClient) {
            ExcludeClipRect(dc, client.left, client.top, client.right, client.bottom);
        } else {
            IntersectClipRect(dc, client.left, client.top, client.right, client.bottom);
        }
        int state = IsWindowEnabled(button) ? PBS_NORMAL : PBS_DISABLED;
        if (IsThemeBackgroundPartiallyTransparent(theme, BP_PUSHBUTTON, state)) {
            DrawThemeParentBackground(preview, dc, &bounds);
        }
        drawn = SUCCEEDED(DrawThemeBackground(theme, dc, BP_PUSHBUTTON, state, &bounds, nullptr));
        RestoreDC(dc, saved);
    }
    CloseThemeData(theme);
    return drawn;
}

/// Applies the native button border to themed previews, including printed images, and refreshes state
/// changes.
static LRESULT CALLBACK SettingsColorPreviewSubclassProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    UNREFERENCED_PARAMETER(referenceData);
    if (msg == WM_NCPAINT) {
        HDC dc = GetWindowDC(window);
        bool drawn = DrawSettingsColorPreviewTheme(window, dc, true);
        if (dc != nullptr) {
            ReleaseDC(window, dc);
        }
        if (drawn) {
            return 0;
        }
    } else if (msg == WM_NCDESTROY) {
        RemoveWindowSubclass(window, SettingsColorPreviewSubclassProc, subclassId);
    }
    LRESULT result = DefSubclassProc(window, msg, wParam, lParam);
    if (msg == WM_PRINT && (lParam & PRF_NONCLIENT) != 0) {
        DrawSettingsColorPreviewTheme(window, reinterpret_cast<HDC>(wParam), true);
    } else if (msg == WM_ENABLE || msg == WM_THEMECHANGED || msg == WM_SYSCOLORCHANGE) {
        RedrawWindow(window, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME);
    }
    return result;
}

/// Recolors the outer one-pixel native list border with the current Edit theme border color after nonclient
/// painting. Retains native painting when visual styles or theme metrics are unavailable and removes the
/// subclass on destruction.
static LRESULT CALLBACK SettingsListBorderSubclassProc(HWND window, UINT message, WPARAM wParam,
        LPARAM lParam, UINT_PTR subclassId, DWORD_PTR referenceData) {
    UNREFERENCED_PARAMETER(referenceData);
    if (message == WM_NCDESTROY) {
        RemoveWindowSubclass(window, SettingsListBorderSubclassProc, subclassId);
    }
    LRESULT result = DefSubclassProc(window, message, wParam, lParam);
    if (message != WM_NCPAINT || themesDisabled || !AreVisualStylesActive()) {
        return result;
    }
    HTHEME theme = OpenThemeData(nullptr, L"Edit");
    if (theme == nullptr) {
        return result;
    }
    COLORREF borderColor = 0;
    HRESULT colorResult =
        GetThemeColor(theme, EP_EDITBORDER_NOSCROLL, EPSN_NORMAL, TMT_BORDERCOLOR, &borderColor);
    CloseThemeData(theme);
    WINDOWINFO information = { sizeof(information) };
    if (FAILED(colorResult) || !GetWindowInfo(window, &information)) {
        return result;
    }
    HDC dc = GetWindowDC(window);
    if (dc == nullptr) {
        return result;
    }
    HBRUSH brush = CreateSolidBrush(borderColor);
    if (brush != nullptr) {
        RECT border = {
            0,
            0,
            information.rcWindow.right - information.rcWindow.left,
            information.rcWindow.bottom - information.rcWindow.top
        };
        FrameRect(dc, &border, brush);
    }
    if (brush != nullptr) {
        DeleteObject(brush);
    }
    ReleaseDC(window, dc);
    return result;
}

/// Recalculates settings tabs, list rows, labels, combos, and edits without restricting descriptive notes.
static BOOL CALLBACK UpdateSettingsFieldMetrics(HWND control, LPARAM) {
    HWND edit = SettingsEdit::GetEdit(control);
    if (edit != nullptr) {
        control = edit;
    }
    HWND parent = GetParent(SettingsEdit::GetFrame(control));
    if (control == nullptr || parent == nullptr || parent != hSettings && !IsSettingsPageWindow(parent)) {
        return TRUE;
    }
    wchar_t className[32] = {};
    GetClassNameW(control, className, ARRAYSIZE(className));
    if (control == hTabs) {
        UpdateSettingsTabLayout();
    } else if (control == hNtpLogList || control == hMonitorList) {
        UpdateSettingsReportMetrics(control);
    } else if (_wcsicmp(className, L"LISTBOX") == 0) {
        UpdateSettingsListMetrics(control);
    } else if (_wcsicmp(className, WC_COMBOBOXW) == 0 || _wcsicmp(className, WC_COMBOBOXEXW) == 0) {
        UpdateSettingsComboMetrics(control);
    } else if (_wcsicmp(className, L"EDIT") == 0
            && (GetWindowLongPtrW(control, GWL_STYLE) & ES_MULTILINE) == 0) {
        UpdateEditMetrics(control);
    } else if (_wcsicmp(className, L"BUTTON") == 0) {
        LONG_PTR type = GetWindowLongPtrW(control, GWL_STYLE) & BS_TYPEMASK;
        if (type == BS_PUSHBUTTON || type == BS_DEFPUSHBUTTON) {
            HFONT font = reinterpret_cast<HFONT>(SendMessageW(control, WM_GETFONT, 0, 0));
            SIZE units = {};
            RECT bounds = {};
            if (GetDialogFontBaseUnits(font, &units) && GetWindowRect(control, &bounds)) {
                LONG height = DialogHeightFromUnits(DIALOG_BUTTON_HEIGHT_DLU, units.cy);
                if (bounds.bottom - bounds.top != height) {
                    SetWindowPos(control, nullptr, 0, 0, bounds.right - bounds.left, height,
                        SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
                }
            }
        }
    } else if (GetPropW(control, SETTINGS_FIELD_LABEL_PROPERTY) != nullptr) {
        RECT bounds = {};
        TEXTMETRICW metrics = {};
        if (GetSettingsTextMetrics(control, &metrics) && GetWindowRect(control, &bounds)) {
            LONG height = std::min(metrics.tmHeight, static_cast<LONG>(SettingsDialogHeight(11)));
            if (bounds.bottom - bounds.top != height) {
                SetWindowPos(control, nullptr, 0, 0, bounds.right - bounds.left, height,
                    SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
            }
        }
    }
    return TRUE;
}

/// Locates native button text using the themed content rectangle or checkbox glyph size and classic border
/// metrics.
static LONG GetSettingsButtonTextTop(HWND button, const WINDOWINFO& information, const TEXTMETRICW& metrics) {
    RECT content = {
        0,
        0,
        information.rcClient.right - information.rcClient.left,
        information.rcClient.bottom - information.rcClient.top
    };
    LONG textHeight = metrics.tmHeight;
    HTHEME theme = GetWindowTheme(button);
    if (theme == nullptr) {
        content.bottom -= GetSystemMetrics(SM_CYBORDER);
    } else {
        LONG_PTR type = GetWindowLongPtrW(button, GWL_STYLE) & BS_TYPEMASK;
        if (type == BS_PUSHBUTTON || type == BS_DEFPUSHBUTTON) {
            RECT themedContent = {};
            if (SUCCEEDED(GetThemeBackgroundContentRect(theme, nullptr, BP_PUSHBUTTON, PBS_NORMAL,
                    &content, &themedContent))) {
                content = themedContent;
            }
        } else if (type == BS_CHECKBOX
                || type == BS_AUTOCHECKBOX
                || type == BS_3STATE
                || type == BS_AUTO3STATE) {
            SIZE glyph = {};
            if (SUCCEEDED(GetThemePartSize(theme, nullptr, BP_CHECKBOX, CBS_UNCHECKEDNORMAL, nullptr,
                TS_TRUE, &glyph))) {
                textHeight = std::max(textHeight, glyph.cy);
            }
        }
    }
    return content.top + (content.bottom - content.top - textHeight) / 2;
}

/// Moves a settings control vertically while preserving its size, horizontal position, and Z order. Requests
/// native repainting instead of copying pixels that another moved control may already have overwritten.
static void OffsetSettingsControl(HWND control, LONG distance) {
    control = SettingsEdit::GetFrame(control);
    RECT bounds = {};
    if (distance == 0 || control == nullptr || !GetWindowRect(control, &bounds)) {
        return;
    }
    POINT position = { bounds.left, bounds.top + distance };
    ScreenToClient(GetParent(control), &position);
    SetWindowPos(control, nullptr, position.x, position.y, 0, 0,
        SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS);
}

/// Reads a native checkbox glyph rectangle in screen pixels using its current theme or classic system
/// metrics.
static bool GetSettingsCheckboxGlyphBounds(HWND control, RECT* bounds) {
    WINDOWINFO information = { sizeof(information) };
    if (!GetWindowInfo(control, &information)) {
        return false;
    }
    SIZE glyph = { GetSystemMetrics(SM_CXMENUCHECK), GetSystemMetrics(SM_CYMENUCHECK) };
    HTHEME theme = GetWindowTheme(control);
    if (theme != nullptr) {
        SIZE themed = {};
        if (SUCCEEDED(GetThemePartSize(theme, nullptr, BP_CHECKBOX, CBS_UNCHECKEDNORMAL, nullptr, TS_TRUE,
                &themed))) {
            glyph = themed;
        }
    }
    *bounds = information.rcClient;
    bounds->right = bounds->left + glyph.cx;
    bounds->top += (bounds->bottom - bounds->top - glyph.cy) / 2;
    bounds->bottom = bounds->top + glyph.cy;
    return true;
}

/// Centers the first two General checkbox rows by their native glyphs in the free space between adjacent
/// combos. Preserves their authored row spacing, dimensions, horizontal positions, and shared text baselines.
static void CenterSettingsGeneralCheckboxes() {
    RECT upper = {};
    RECT lower = {};
    RECT first = {};
    RECT last = {};
    if (!GetWindowRect(hTypeCombo, &upper) || !GetWindowRect(hTimeZoneCombo, &lower)
            || !GetSettingsCheckboxGlyphBounds(hVisibleCheck, &first)
            || !GetSettingsCheckboxGlyphBounds(hUtcCheck, &last)) {
        return;
    }
    LONG offset = (upper.bottom + lower.top - first.top - last.bottom) / 2;
    const HWND controls[] = {
        hVisibleCheck,
        hTopmostCheck,
        hSecondsCheck,
        hUtcCheck,
        hUtcTextCheck,
        hSoundsMutedCheck
    };
    for (HWND control : controls) {
        OffsetSettingsControl(control, offset);
    }
}

/// Measures a label or button text baseline in screen pixels using its current font and native text
/// placement. Accounts for the custom NTP caption glyph ascent and returns false if the window or font
/// metrics cannot be read.
static bool GetSettingsLabelBaseline(HWND label, LONG* baseline) {
    WINDOWINFO information = { sizeof(information) };
    if (label == nullptr || !GetWindowInfo(label, &information)) {
        return false;
    }
    HDC dc = GetDC(label);
    if (dc == nullptr) {
        return false;
    }
    HFONT font = reinterpret_cast<HFONT>(SendMessageW(label, WM_GETFONT, 0, 0));
    HGDIOBJ previous = font == nullptr ? nullptr : SelectObject(dc, font);
    TEXTMETRICW metrics = {};
    bool measured = GetTextMetricsW(dc, &metrics) != FALSE;
    LONG ascent = metrics.tmAscent;
    if (measured && label == hNtpServersLabel) {
        ascent = GetUiTextLine(dc, GetControlText(label)).ascent;
    }
    if (previous != nullptr && previous != HGDI_ERROR) {
        SelectObject(dc, previous);
    }
    ReleaseDC(label, dc);
    if (!measured) {
        return false;
    }
    LONG top = information.rcClient.top;
    wchar_t className[16] = {};
    GetClassNameW(label, className, ARRAYSIZE(className));
    if (_wcsicmp(className, L"BUTTON") == 0) {
        top += GetSettingsButtonTextTop(label, information, metrics);
    } else if ((GetWindowLongPtrW(label, GWL_STYLE) & SS_CENTERIMAGE) != 0) {
        top += (information.rcClient.bottom - information.rcClient.top - metrics.tmHeight) / 2;
    }
    *baseline = top + ascent;
    return true;
}

/// Measures twice the checkbox glyph-center distance from an adjacent static's actual text baseline.
static bool GetSettingsCheckboxBaselineDistance(HWND checkbox, HWND label, LONG* distance) {
    RECT glyph = {};
    LONG baseline = 0;
    if (!GetSettingsCheckboxGlyphBounds(checkbox, &glyph) || !GetSettingsLabelBaseline(label, &baseline)) {
        return false;
    }
    *distance = glyph.top + glyph.bottom - 2 * baseline;
    return true;
}

/// Preserves the glyph-to-baseline offset captured from RC while accounting for font and theme changes.
static void AlignSettingsCheckboxToBaseline(HWND checkbox, HWND label, LONG referenceDistance) {
    LONG distance = 0;
    if (GetSettingsCheckboxBaselineDistance(checkbox, label, &distance)) {
        OffsetSettingsControl(checkbox, (referenceDistance - distance) / 2);
    }
}

/// Anchors the monitor caption above its fixed listview and positions the NTP and command fields below their
/// captions. Uses the baseline-to-field gaps authored in RC without moving the monitor listview.
static void AlignSettingsFieldsBelowLabels() {
    RECT spacing = GetSettingsResourceRect(hSettings, IDC_SETTINGS_LABEL_FIELD_GAP);
    LONG gap = spacing.bottom - spacing.top;
    RECT commandSpacing = GetSettingsResourceRect(hSettings, IDC_SETTINGS_COMMAND_FIELD_GAP);
    LONG baseline = 0;
    RECT bounds = {};
    if (GetWindowRect(hMonitorList, &bounds) && GetSettingsLabelBaseline(hMonitorLabel, &baseline)) {
        OffsetSettingsControl(hMonitorLabel, bounds.top - gap - baseline);
    }
    const HWND labels[] = { hNtpServersLabel, GetDlgItem(hAlarmPage, ID_RUN_COMMAND) };
    const HWND fields[] = { hNtpServersEdit, hCommandEdit };
    for (int index = 0; index < ARRAYSIZE(fields); index++) {
        if (GetWindowRect(SettingsEdit::GetFrame(fields[index]), &bounds)
                && GetSettingsLabelBaseline(labels[index], &baseline)) {
            LONG fieldGap = index == 0 ? gap : commandSpacing.bottom - commandSpacing.top;
            OffsetSettingsControl(fields[index], baseline + fieldGap - bounds.top);
        }
    }
}

/// Measures the native vertical adjustment needed to align a control with adjacent text without moving it.
static LONG GetSettingsControlBaselineAdjustment(HWND control, HWND reference, LONG baselineDistance) {
    WINDOWINFO controlInfo = {};
    controlInfo.cbSize = sizeof(controlInfo);
    WINDOWINFO referenceInfo = {};
    referenceInfo.cbSize = sizeof(referenceInfo);
    if (control == nullptr
            || reference == nullptr
            || !GetWindowInfo(control, &controlInfo)
            || !GetWindowInfo(reference, &referenceInfo)) {
        return 0;
    }
    HDC dc = GetDC(control);
    if (dc == nullptr) {
        return 0;
    }
    HFONT font = reinterpret_cast<HFONT>(SendMessageW(control, WM_GETFONT, 0, 0));
    HGDIOBJ previousFont = font == nullptr ? nullptr : SelectObject(dc, font);
    TEXTMETRICW metrics = {};
    bool measured = GetTextMetricsW(dc, &metrics) != FALSE;
    LONG baselineOffset = 0;
    if (measured && control == hNtpServersLabel) {
        baselineOffset = GetUiTextLine(dc, GetControlText(control)).ascent - metrics.tmAscent;
    }
    if (previousFont != nullptr && previousFont != HGDI_ERROR) {
        SelectObject(dc, previousFont);
    }
    ReleaseDC(control, dc);
    if (!measured) {
        return 0;
    }
    wchar_t className[32] = {};
    GetClassNameW(reference, className, ARRAYSIZE(className));
    LONG textTop = referenceInfo.rcClient.top;
    if (_wcsicmp(className, WC_COMBOBOXW) == 0 || _wcsicmp(className, WC_COMBOBOXEXW) == 0) {
        COMBOBOXINFO combo = {};
        combo.cbSize = sizeof(combo);
        if (!GetComboBoxInfo(GetSettingsComboBox(reference), &combo)) {
            return 0;
        }
        textTop += combo.rcItem.top + (combo.rcItem.bottom - combo.rcItem.top - metrics.tmHeight) / 2;
    } else if (_wcsicmp(className, L"EDIT") == 0) {
        RECT text = {};
        SendMessageW(reference, EM_GETRECT, 0, reinterpret_cast<LPARAM>(&text));
        textTop += text.top;
    } else if (_wcsicmp(className, L"BUTTON") == 0) {
        textTop += GetSettingsButtonTextTop(reference, referenceInfo, metrics);
    } else if (_wcsicmp(className, L"STATIC") == 0
            && (GetWindowLongPtrW(reference, GWL_STYLE) & SS_CENTERIMAGE) != 0) {
        textTop += (referenceInfo.rcClient.bottom - referenceInfo.rcClient.top - metrics.tmHeight) / 2;
    }
    wchar_t controlClass[32] = {};
    GetClassNameW(control, controlClass, ARRAYSIZE(controlClass));
    LONG controlTextTop = controlInfo.rcClient.top - controlInfo.rcWindow.top + baselineOffset;
    if (_wcsicmp(controlClass, WC_COMBOBOXW) == 0 || _wcsicmp(controlClass, WC_COMBOBOXEXW) == 0) {
        COMBOBOXINFO combo = {};
        combo.cbSize = sizeof(combo);
        if (!GetComboBoxInfo(GetSettingsComboBox(control), &combo)) {
            return 0;
        }
        controlTextTop += combo.rcItem.top + (combo.rcItem.bottom - combo.rcItem.top - metrics.tmHeight) / 2;
    } else if (_wcsicmp(controlClass, L"EDIT") == 0) {
        RECT text = {};
        SendMessageW(control, EM_GETRECT, 0, reinterpret_cast<LPARAM>(&text));
        controlTextTop += text.top;
    } else if (_wcsicmp(controlClass, L"BUTTON") == 0) {
        controlTextTop += GetSettingsButtonTextTop(control, controlInfo, metrics);
    } else if (_wcsicmp(controlClass, L"STATIC") == 0
            && (GetWindowLongPtrW(control, GWL_STYLE) & SS_CENTERIMAGE) != 0) {
        controlTextTop += (controlInfo.rcClient.bottom - controlInfo.rcClient.top - metrics.tmHeight) / 2;
    }
    return textTop + baselineDistance - controlTextTop - controlInfo.rcWindow.top;
}

/// Aligns a settings label, edit, combo, push button, or checkbox to adjacent text plus an optional baseline
/// distance. Uses native content rectangles and preserves size, horizontal position, and Z order.
void AlignSettingsControl(HWND control, HWND reference, LONG baselineDistance) {
    OffsetSettingsControl(control,
        GetSettingsControlBaselineAdjustment(control, reference, baselineDistance));
}

/// Places Sunday first at its final horizontal position and native text baseline in one move.
static void AlignSettingsSundayFirst(HWND reference, LONG baselineDistance = 0) {
    RECT bounds = {};
    if (!GetWindowRect(hSundayFirstCheck, &bounds)) {
        return;
    }
    MapWindowPoints(HWND_DESKTOP, hAppearancePage, reinterpret_cast<POINT*>(&bounds), 2);
    bool panel = settingsDraft[selectedDraftIndex].type == WIDGET_PANEL;
    RECT placement = GetSettingsResourceRect(hAppearancePage,
        panel ? IDC_LAYOUT_SUNDAY_PANEL : IDC_LAYOUT_SUNDAY_CALENDAR);
    int x = placement.left;
    int width = placement.right - placement.left;
    LONG top =
        bounds.top + GetSettingsControlBaselineAdjustment(hSundayFirstCheck, reference, baselineDistance);
    SetControlPosition(hSundayFirstCheck, x, top, width, bounds.bottom - bounds.top);
}

/// Aligns a volume value to its fixed label and moves its slider by the same baseline adjustment.
static void AlignSettingsVolumeControls(HWND label, HWND value, HWND trackBar) {
    RECT previous = {};
    if (!GetWindowRect(value, &previous)) {
        return;
    }
    AlignSettingsControl(value, label);
    RECT current = {};
    if (GetWindowRect(value, &current)) {
        OffsetSettingsControl(trackBar, current.top - previous.top);
    }
}

/// Positions an Appearance slider at the Application volume slider's verified distance from its label's text
/// baseline.
static void AlignSettingsAppearanceTrackBar(HWND trackBar, HWND label) {
    WINDOWINFO labelInfo = {};
    labelInfo.cbSize = sizeof(labelInfo);
    WINDOWINFO referenceInfo = {};
    referenceInfo.cbSize = sizeof(referenceInfo);
    RECT trackBarBounds = {};
    RECT referenceBounds = {};
    TEXTMETRICW labelMetrics = {};
    TEXTMETRICW referenceMetrics = {};
    if (trackBar == nullptr || label == nullptr
            || !GetWindowInfo(label, &labelInfo)
            || !GetWindowInfo(hTimeSignalVolumeLabel, &referenceInfo)
            || !GetWindowRect(trackBar, &trackBarBounds)
            || !GetWindowRect(hTimeSignalVolumeTrackBar, &referenceBounds)
            || !GetSettingsTextMetrics(label, &labelMetrics)
            || !GetSettingsTextMetrics(hTimeSignalVolumeLabel, &referenceMetrics)) {
        return;
    }
    LONG labelBaseline = labelInfo.rcClient.top
        + (labelInfo.rcClient.bottom - labelInfo.rcClient.top - labelMetrics.tmHeight) / 2
        + labelMetrics.tmAscent;
    LONG referenceBaseline = referenceInfo.rcClient.top
        + (referenceInfo.rcClient.bottom - referenceInfo.rcClient.top - referenceMetrics.tmHeight) / 2
        + referenceMetrics.tmAscent;
    OffsetSettingsControl(trackBar,
        referenceBounds.top - referenceBaseline + labelBaseline - trackBarBounds.top);
}

/// Spaces Appearance rows by their text baselines, including rows beginning with a push button.
static void LayoutSettingsUniformAppearanceRows() {
    if (selectedDraftIndex < 0 || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
        return;
    }
    WidgetType type = settingsDraft[selectedDraftIndex].type;
    if (type != WIDGET_ANALOG
            && type != WIDGET_PANEL
            && type != WIDGET_DIGITAL
            && type != WIDGET_FULLSCREEN) {
        return;
    }
    int rowSpacingId = type == WIDGET_ANALOG
        ? IDC_GRID_ROW_ANALOG_APPEARANCE
        : IDC_GRID_ROW_UNIFORM_APPEARANCE;
    RECT rowSpacing = GetSettingsResourceRect(hAppearancePage, rowSpacingId);
    LONG spacing = rowSpacing.bottom - rowSpacing.top;
    const HWND analogRows[] = {
        hSizeLabel, hOpacityLabel, hWidgetAntialiasLabel, hWidgetDisableThemesCheck
    };
    const HWND panelRows[] = {
        hSizeLabel,
        hOpacityLabel,
        hPanelTopFontLabel,
        hPanelTimeFontLabel,
        hPanelBottomFontLabel,
        hFontLabel,
        hWidgetAntialiasLabel,
        hBorderLabel,
        hLeadingZeroLabel,
        hWeekNumbersCheck,
        hDateFormatLabel
    };
    const HWND digitalRows[] = {
        hOpacityLabel,
        hFontSizeLabel,
        hFontLabel,
        hWidgetAntialiasLabel,
        hTextColorButton,
        hAlarmTextColorButton,
        hBorderLabel,
        hPaddingLabel,
        hBorderWidthLabel,
        hLeadingZeroLabel,
        hTransparentBackgroundCheck
    };
    const HWND* rows = digitalRows;
    int count = static_cast<int>(ARRAYSIZE(digitalRows));
    if (type == WIDGET_ANALOG) {
        rows = analogRows;
        count = static_cast<int>(ARRAYSIZE(analogRows));
    } else if (type == WIDGET_PANEL) {
        rows = panelRows;
        count = static_cast<int>(ARRAYSIZE(panelRows));
    }
    for (int index = 1; index < count; index++) {
        AlignSettingsControl(rows[index], rows[0], index * spacing);
    }
    if (type == WIDGET_PANEL) {
        AlignSettingsSundayFirst(hWeekNumbersCheck);
    } else if (type == WIDGET_DIGITAL || type == WIDGET_FULLSCREEN) {
        AlignSettingsControl(hBackgroundColorButton, hTextColorButton);
        AlignSettingsControl(hAlarmBackgroundColorButton, hAlarmTextColorButton);
    }
}

/// Preserves the standalone calendar's font, antialiasing, border, and checkbox rows.
static void LayoutSettingsCalendarAppearanceRows() {
    if (selectedDraftIndex < 0
            || selectedDraftIndex >= static_cast<int>(settingsDraft.size())
            || settingsDraft[selectedDraftIndex].type != WIDGET_CALENDAR) {
        return;
    }
    LONG spacing = SettingsDialogHeight(15);
    AlignSettingsControl(hFontLabel, hOpacityLabel, 2 * spacing);
    AlignSettingsControl(hFontButton, hFontLabel);
    AlignSettingsControl(hWidgetAntialiasCombo, hFontLabel, spacing);
    AlignSettingsControl(hBorderColorButton, hWidgetAntialiasCombo, spacing);
    AlignSettingsControl(hShowTodayCheck, hBorderColorButton, 3 * spacing);
    AlignSettingsControl(hWeekNumbersCheck, hShowTodayCheck, spacing);
    AlignSettingsSundayFirst(hWeekNumbersCheck, spacing);
    AlignSettingsControl(hDateFormatLabel, hSundayFirstCheck, spacing);
}

/// Anchors text-widget border rows to their font-based button positions and detail rows to opacity/font-size
/// spacing. Other widgets retain their fixed label anchors; sliders keep the common baseline-relative offset.
static void AlignSettingsBorderControls() {
    if (selectedDraftIndex >= 0
            && selectedDraftIndex < static_cast<int>(settingsDraft.size())
            && settingsDraft[selectedDraftIndex].type == WIDGET_CALENDAR) {
        AlignSettingsControl(hBorderLabel, hBorderColorButton);
        RECT opacity = {};
        RECT fontSize = {};
        if (GetWindowRect(hOpacityTrackBar, &opacity) && GetWindowRect(hFontSizeTrackBar, &fontSize)) {
            LONG spacing = fontSize.top - opacity.top;
            AlignSettingsControl(hPaddingLabel, hBorderColorButton, spacing);
            AlignSettingsControl(hBorderWidthLabel, hBorderColorButton, 2 * spacing);
        }
    } else {
        AlignSettingsControl(hBorderColorButton, hBorderLabel);
    }
    AlignSettingsControl(hPaddingValue, hPaddingLabel);
    AlignSettingsControl(hBorderWidthValue, hBorderWidthLabel);
    AlignSettingsAppearanceTrackBar(hBorderTrackBar, hBorderLabel);
    AlignSettingsAppearanceTrackBar(hPaddingTrackBar, hPaddingLabel);
    AlignSettingsAppearanceTrackBar(hBorderWidthTrackBar, hBorderWidthLabel);
}

/// Keeps the sound fields above the volume slider and expanded labels without moving the left row anchors.
static void UpdateApplicationControlOrder() {
    if (hAppFontLabel == nullptr) {
        return;
    }
    const HWND foreground[] = { hTimeSignalSoundCombo, hTimeSignalTestButton, hTimeSignalVolumeTrackBar };
    HWND previous = nullptr;
    for (HWND control : foreground) {
        if (GetWindow(control, GW_HWNDPREV) != previous) {
            SetWindowPos(control, previous, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        }
        previous = control;
    }
}

/// Aligns associated fields to their labels, retaining the separate text-widget antialiasing anchor.
static BOOL CALLBACK AlignSettingsFieldLabel(HWND label, LPARAM) {
    HWND field = reinterpret_cast<HWND>(GetPropW(label, SETTINGS_FIELD_LABEL_PROPERTY));
    if (field != nullptr && IsWindow(field)) {
        bool antialiasAnchor = field == hWidgetAntialiasCombo
            && selectedDraftIndex >= 0
            && selectedDraftIndex < static_cast<int>(settingsDraft.size())
            && settingsDraft[selectedDraftIndex].type == WIDGET_CALENDAR;
        if (antialiasAnchor) {
            AlignSettingsControl(label, field);
        } else {
            AlignSettingsControl(field, label);
        }
    }
    return TRUE;
}

/// Fits the widget list between Add and the lower action buttons using the authored dialog-unit gap.
static void UpdateSettingsWidgetListLayout() {
    RECT add = {};
    RECT remove = {};
    RECT list = {};
    if (hWidgetList == nullptr
            || !GetWindowRect(GetDlgItem(hSettings, ID_ADD), &add)
            || !GetWindowRect(GetDlgItem(hSettings, ID_REMOVE), &remove)
            || !GetWindowRect(hWidgetList, &list)) {
        return;
    }
    list.top = add.bottom + SettingsDialogHeight(2);
    list.bottom = remove.top - SettingsDialogHeight(2);
    MapWindowPoints(HWND_DESKTOP, GetParent(hWidgetList), reinterpret_cast<POINT*>(&list), 2);
    SetControlPosition(hWidgetList, list.left, list.top, list.right - list.left,
        std::max(1L, list.bottom - list.top));
}

/// Aligns left actions with the tab bottom and places the five bottom actions two dialog units below it.
static void LayoutSettingsWindowControls() {
    RECT tabs = GetSettingsResourceRect(hSettings, ID_TABS);
    RECT gap = GetSettingsResourceRect(hSettings, IDC_SETTINGS_FOOTER_GAP);
    int footerTop = tabs.bottom + gap.bottom - gap.top;
    const int rowIds[] = { ID_REMOVE, ID_DUPLICATE };
    const int footerIds[] = { ID_IMPORT_SETTINGS, ID_EXPORT_SETTINGS, ID_SAVE, ID_CANCEL, ID_APPLY };
    for (int id : rowIds) {
        RECT bounds = GetSettingsResourceRect(hSettings, id);
        int height = bounds.bottom - bounds.top;
        SetControlPosition(GetDlgItem(hSettings, id), bounds.left, tabs.bottom - height,
            bounds.right - bounds.left, height);
    }
    for (int id : footerIds) {
        RECT bounds = GetSettingsResourceRect(hSettings, id);
        SetControlPosition(GetDlgItem(hSettings, id), bounds.left, footerTop, bounds.right - bounds.left,
            bounds.bottom - bounds.top);
    }
}

/// Maps the rational dialog-unit span authored in RC to one pixel step and preserves control sizes.
static void SpaceSettingsControls(HWND parent, int stepId, int divisor, bool horizontal,
        const HWND* controls, int count) {
    RECT spacing = GetSettingsResourceRect(parent, stepId);
    SIZE units = {};
    if (!GetDialogFontBaseUnits(hUiFont, &units)) {
        return;
    }
    int unitPixels = horizontal ? units.cx : units.cy;
    int unitDivisor = horizontal ? 4 : 8;
    if (!horizontal && unitPixels * DIALOG_BUTTON_HEIGHT_DLU > MAX_DIALOG_BUTTON_HEIGHT * 8) {
        unitPixels = MAX_DIALOG_BUTTON_HEIGHT;
        unitDivisor = DIALOG_BUTTON_HEIGHT_DLU;
    }
    int mappedSpan = horizontal ? spacing.right - spacing.left : spacing.bottom - spacing.top;
    int dialogSpan = MulDiv(mappedSpan, unitDivisor, unitPixels);
    int step = MulDiv(dialogSpan, unitPixels, unitDivisor * divisor);
    RECT first = {};
    if (!GetWindowRect(SettingsEdit::GetFrame(controls[0]), &first)) {
        return;
    }
    MapWindowPoints(HWND_DESKTOP, parent, reinterpret_cast<POINT*>(&first), 2);
    for (int index = 1; index < count; index++) {
        HWND frame = SettingsEdit::GetFrame(controls[index]);
        RECT current = {};
        if (!GetWindowRect(frame, &current)) {
            continue;
        }
        MapWindowPoints(HWND_DESKTOP, parent, reinterpret_cast<POINT*>(&current), 2);
        int x = horizontal ? first.left + index * step : current.left;
        int y = horizontal ? current.top : first.top + index * step;
        if (x != current.left || y != current.top) {
            SetWindowPos(frame, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
        }
    }
}

/// Preserves shared row and column strides before native font-baseline alignment across every settings page.
static void LayoutSettingsControlGrids() {
    const HWND textRows[] = { hOpacityLabel, hFontSizeLabel, hFontLabel };
    const HWND sizeColumns[] = { hSizeCombo, hAdditionalSizeCombos[0], hAdditionalSizeCombos[1] };
    const HWND applicationRows[] = {
        hAppFontLabel,
        GetDlgItem(hApplicationPage, IDC_APP_ANTIALIAS_LABEL),
        GetDlgItem(hApplicationPage, IDC_APP_LANGUAGE_LABEL),
        GetDlgItem(hApplicationPage, IDC_TIME_SIGNAL_SOUND_LABEL),
        hTestAudioOutputLabel,
        hTimeSignalVolumeLabel
    };
    const HWND applicationChecks[] = {
        hDisableThemesCheck,
        hUseXmlSettingsCheck,
        hSnapToWorkAreaCheck,
        hStartWithWindowsCheck,
        hWarnUnsavedChangesCheck
    };
    const HWND timeFields[] = { GetDlgItem(hTimePage, IDC_TIME_SOURCE_LABEL), hNtpPresetLabel };
    const HWND timeActions[] = { hNtpServersEdit, hNtpSyncButton, hNtpStatus };
    HWND days[ALARM_DAY_COUNT] = {};
    int firstDay = GetCultureFirstAlarmDay(appLanguage);
    RECT applicationSpacing = GetSettingsResourceRect(hApplicationPage, IDC_GRID_ROW_APPLICATION);
    LONG applicationStep = applicationSpacing.bottom - applicationSpacing.top;
    LayoutSettingsWindowControls();
    for (int index = 0; index < ALARM_DAY_COUNT; index++) {
        days[index] = hAlarmDayChecks[(firstDay + index) % ALARM_DAY_COUNT];
    }
    SpaceSettingsControls(hAppearancePage, IDC_GRID_COLUMN_SIZE, 2, true, sizeColumns,
        ARRAYSIZE(sizeColumns));
    SpaceSettingsControls(hAlarmPage, IDC_GRID_COLUMN_WEEKDAY, 2, true, days, ARRAYSIZE(days));
    for (HWND day : days) {
        RECT bounds = GetSettingsResourceRect(hAlarmPage, GetDlgCtrlID(day));
        SetControlPosition(day, bounds.left, bounds.top, bounds.right - bounds.left,
            bounds.bottom - bounds.top);
    }
    SpaceSettingsControls(hTimeSignalPage, IDC_GRID_ROW_SIGNAL, 5, false, hTimeSignalIntervalRadios,
        ARRAYSIZE(hTimeSignalIntervalRadios));
    LONG enabledBaseline = 0;
    LONG firstRadioBaseline = 0;
    if (GetSettingsLabelBaseline(hTimeSignalEnabledCheck, &enabledBaseline)
            && GetSettingsLabelBaseline(hTimeSignalIntervalRadios[0], &firstRadioBaseline)) {
        AlignSettingsControl(hAudioOutputLabel,
            hTimeSignalIntervalRadios[ARRAYSIZE(hTimeSignalIntervalRadios) - 1],
            firstRadioBaseline - enabledBaseline);
    }
    for (int index = 1; index < ARRAYSIZE(applicationRows); index++) {
        AlignSettingsControl(applicationRows[index], applicationRows[0], index * applicationStep);
    }
    for (int index = 0; index < ARRAYSIZE(applicationChecks); index++) {
        AlignSettingsControl(applicationChecks[index], hTimeSignalVolumeLabel, (index + 2) * applicationStep);
    }
    SpaceSettingsControls(hTimePage, IDC_GRID_ROW_TIME_FIELDS, 5, false, timeFields,
        ARRAYSIZE(timeFields));
    LONG timeFieldSpacing = GetSettingsControlBaselineAdjustment(timeFields[0], hNtpPresetLabel, 0);
    AlignSettingsControl(hNtpServersLabel, hNtpPresetLabel, timeFieldSpacing);
    AlignSettingsFieldsBelowLabels();
    SpaceSettingsControls(hTimePage, IDC_GRID_ROW_TIME_ACTIONS, 5, false, timeActions,
        ARRAYSIZE(timeActions));
    OffsetSettingsControl(hNtpStatus, SettingsDialogHeight(5));
    if (selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
        WidgetType type = settingsDraft[selectedDraftIndex].type;
        if (type == WIDGET_CALENDAR) {
            SpaceSettingsControls(hAppearancePage, IDC_GRID_ROW_APPEARANCE, 1, false, textRows,
                ARRAYSIZE(textRows));
        }
    }
}

/// Aligns mixed settings rows after the shared font, theme, or page layout changes.
static void AlignSettingsControls() {
    LayoutSettingsControlGrids();
    UpdateSettingsActionButtonWidths();
    FitSettingsButtonWidth(hNtpSaveLogButton, true);
    FitSettingsButtonWidth(hNtpSyncButton, false);
    const HWND timeButtons[] = { hNtpSyncButton, hNtpSaveLogButton };
    const HWND timeFields[] = { SettingsEdit::GetFrame(hNtpServersEdit), hNtpLogList };
    for (int index = 0; index < ARRAYSIZE(timeButtons); index++) {
        RECT field = {};
        RECT button = {};
        if (GetWindowRect(timeFields[index], &field) && GetWindowRect(timeButtons[index], &button)) {
            LONG offset = field.bottom + SettingsDialogHeight(3) - button.top;
            OffsetSettingsControl(timeButtons[index], offset);
            if (index == 0) {
                OffsetSettingsControl(hNtpStatus, offset);
            }
        }
    }
    HDC statusDc = hNtpStatus == nullptr ? nullptr : GetDC(hNtpStatus);
    if (statusDc != nullptr) {
        HFONT font = reinterpret_cast<HFONT>(SendMessageW(hNtpStatus, WM_GETFONT, 0, 0));
        HGDIOBJ previous = font == nullptr ? nullptr : SelectObject(statusDc, font);
        std::wstring referenceText = T(TXT_NTP_STATUS_SYNCHRONIZED);
        referenceText += L" " + ntpActiveServer + L" (Θ = "
            + FormatNtpLogOffset(ntpOffset100Nanoseconds.load()) + L")";
        UiTextLine referenceLine = GetUiTextLine(statusDc, referenceText);
        UiTextLine statusLine = GetNtpStatusLine(statusDc);
        if (previous != nullptr && previous != HGDI_ERROR) {
            SelectObject(statusDc, previous);
        }
        ReleaseDC(hNtpStatus, statusDc);
        OffsetSettingsControl(hNtpStatus, referenceLine.ascent - statusLine.ascent);
    }
    UpdateApplicationControlWidths();
    LayoutSettingsUniformAppearanceRows();
    LayoutSettingsCalendarAppearanceRows();
    if (selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
        if (settingsDraft[selectedDraftIndex].type != WIDGET_ANALOG) {
            HWND reference = settingsDraft[selectedDraftIndex].type == WIDGET_DIGITAL
                ? hOpacityLabel
                : hSizeLabel;
            AlignSettingsControl(hWidgetDisableThemesCheck, reference, 11 * SettingsDialogHeight(15));
        }
    }
    EnumChildWindows(hSettings, AlignSettingsFieldLabel, 0);
    CenterSettingsGeneralCheckboxes();
    if (settingsGeneralCheckboxReferenceValid) {
        AlignSettingsCheckboxToBaseline(hPanelTimeNoticesCheck, hTimeFormatLabel,
            settingsGeneralCheckboxBaselineDistances[0]);
        for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
            AlignSettingsCheckboxToBaseline(hAdditionalEnabledChecks[index], hAdditionalNameLabels[index],
                settingsGeneralCheckboxBaselineDistances[index + 1]);
        }
    }
    for (HWND combo : hAdditionalSizeCombos) {
        AlignSettingsControl(combo, hSizeLabel);
    }
    AlignSettingsControl(GetDlgItem(hSettings, ID_ADD), hAddType);
    AlignSettingsControl(hBrowseButton, hCommandEdit);
    AlignSettingsControl(hLoopAudioCheck, hTestCommandButton);
    AlignSettingsControl(hFontButton, hFontLabel);
    UpdateApplicationControlOrder();
    AlignSettingsControl(hAppFontDefaultButton, hAppFontLabel);
    AlignSettingsControl(hTimeSignalTestButton, hTimeSignalSoundCombo);
    AlignSettingsControl(hOpacityValue, hOpacityLabel);
    AlignSettingsControl(hFontSizeValue, hFontSizeLabel);
    AlignSettingsVolumeControls(hAlarmVolumeLabel, hAlarmVolumeValue, hAlarmVolumeTrackBar);
    AlignSettingsVolumeControls(hTimeSignalVolumeLabel, hTimeSignalVolumeValue, hTimeSignalVolumeTrackBar);
    AlignSettingsControl(hShowAmPmCheck, hTimeFormatLabel);
    AlignSettingsControl(hBlackoutMonitorsCheck, GetDlgItem(hGeneralPage, IDC_NAME_LABEL),
        11 * SettingsDialogHeight(15));
    AlignSettingsControl(hDefaultAppearanceButton, hWidgetDisableThemesCheck);
    AlignSettingsAppearanceTrackBar(hOpacityTrackBar, hOpacityLabel);
    AlignSettingsAppearanceTrackBar(hFontSizeTrackBar, hFontSizeLabel);
    AlignSettingsBorderControls();
    UpdateSettingsColorControlLayout();
    UpdateSettingsWidgetListLayout();
}

/// Recomputes settings tabs, caps field heights, and aligns mixed rows after font, theme, or system metrics
/// changes.
static void UpdateSettingsControlMetrics() {
    EnumChildWindows(hSettings, UpdateSettingsFieldMetrics, 0);
    AlignSettingsControls();
    UpdateNtpLabelHeights();
    ntpLogColumnsInitialized = false;
    monitorColumnsInitialized = false;
    InitializeNtpLogColumnWidths();
    InitializeMonitorColumnWidths();
    UpdateSettingsWindowLayout();
}

/// Creates the application font if needed, applies font and theme settings to a form and its children, and
/// requests repainting.
void ApplyUiStyle(HWND window) {
    if (window == helpForm.GetWindow() || window == aboutForm.GetWindow()) {
        const wchar_t* theme = themesDisabled ? L"" : nullptr;
        SetWindowTheme(window, theme, theme);
        return;
    }
    if (hUiFont == nullptr) {
        hUiFont = CreateApplicationUiFont(window);
    }
    const wchar_t* themeName = themesDisabled ? L"" : nullptr;
    SetWindowTheme(window, themeName, themeName);
    EnumChildWindows(window, ApplyFontAndTheme, 0);
    if (window == hSettings) {
        SendMessageW(window, WM_SETFONT, reinterpret_cast<WPARAM>(hUiFont), FALSE);
        UpdateSettingsControlMetrics();
    }
    RedrawWindow(window, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN);
}

/// Applies the combined application and widget theme-disable settings and invalidates the window and its
/// children.
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
        SetWindowPos(widget->calendarChild, nullptr, 0, 0, minimum.right - minimum.left,
            minimum.bottom - minimum.top, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
    }
    RedrawWindow(widget->calendarChild, nullptr, nullptr,
        RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_UPDATENOW);
}

/// Restores and activates a valid window, temporarily attaching input queues when the foreground thread
/// differs.
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
static void UpdateAnalogTime(Widget* widget, ULONGLONG applicationUtc = 0) {
    if (widget == nullptr) {
        return;
    }
    SYSTEMTIME time = {};
    if (widget->analogChild != nullptr) {
        GetDisplayedTime(widget->config, &time, applicationUtc);
        SetAnalogClockTime(widget->analogChild, time);
    }
    for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
        if (widget->additionalAnalogChildren[index] != nullptr) {
            WidgetConfig clock = AdditionalClockConfiguration(widget->config, index);
            GetDisplayedTime(clock, &time, applicationUtc);
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

/// Presents a bitmap with per-pixel alpha and overall opacity, preserving the widget's position and edge
/// attachments.
static void PresentLayeredBitmap(Widget* widget, HDC sourceDC, HDC screenDC, int width, int height,
        BYTE opacity) {
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
    if (widget->rendered
            && (current.right - current.left != width || current.bottom - current.top != height)) {
        GetPositionPreservingWorkAreaAttachment(widget->window, width, height, &destination);
        widget->config.x = destination.x;
        widget->config.y = destination.y;
    }
    POINT source = { 0, 0 };
    SIZE size = { width, height };
    BLENDFUNCTION blend = { AC_SRC_OVER, 0, opacity, AC_SRC_ALPHA };
    if (UpdateLayeredWindow(widget->window, screenDC, &destination, &size, sourceDC, &source, 0, &blend,
        ULW_ALPHA)) {
        widget->rendered = true;
    }
}

/// Renders the current analog clock into a new 32-bit bitmap over the requested background.
/// Transfers bitmap ownership on success and deletes it on rendering failure.
static bool RenderAnalogBackground(Widget* widget, HDC reference, DWORD background, HBITMAP* bitmap,
        DWORD** pixels) {
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
    bool rendered = RenderAnalogClock(widget->analogChild, memory, background);
    SelectObject(memory, oldBitmap);
    DeleteDC(memory);
    if (!rendered) {
        DeleteObject(*bitmap);
        *bitmap = nullptr;
    }
    return rendered;
}

/// Renders the native face against light and dark backgrounds to reconstruct transparency, then presents
/// the layered widget.
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
    UpdateAnalogTime(widget);
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
    PresentLayeredBitmap(widget, outputDC, screen, size, size,
        static_cast<BYTE>(widget->config.opacity * 255 / 100));
    SelectObject(outputDC, oldOutput);
    DeleteObject(outputBitmap);
    DeleteDC(outputDC);
    DeleteObject(whiteBitmap);
    DeleteObject(blackBitmap);
    ReleaseDC(nullptr, screen);
}

/// Creates a caller-owned GDI font from panel font properties, converting the dialog size from tenths of
/// a point.
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

/// Builds sample clock text with uniform digits and any fullscreen AM/PM or UTC footer for stable
/// measurement.
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

/// Measures stable GDI bounds for the clock and its footer, considering the widest digit and both day
/// periods.
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

/// Creates a caller-owned fullscreen GDI font scaled to the widget and reduced as necessary to fit the
/// measured text.
static HFONT CreateFullscreenDrawingFont(const WidgetConfig& config, const RECT& client, HDC dc) {
    int width = client.right - client.left;
    int height = client.bottom - client.top;
    int pixelHeight = std::max(1, height *
        std::clamp(config.fontSize, FULLSCREEN_FONT_SIZE_MIN, FULLSCREEN_FONT_SIZE_MAX) / 100);
    HFONT font = CreateFontW(-pixelHeight, 0, 0, 0, config.fontWeight, config.fontItalic,
        config.fontUnderline, config.fontStrikeOut, config.fontCharSet, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, FontQuality(config.fontAntialiasing), DEFAULT_PITCH | FF_DONTCARE,
        config.fontFace.c_str());
    if (font == nullptr || dc == nullptr) {
        return font;
    }
    HGDIOBJ oldFont = SelectObject(dc, font);
    SIZE clockSize = {};
    SIZE measured = MeasureFullscreenClockText(dc, config, &clockSize);
    SelectObject(dc, oldFont);
    while ((measured.cx > width || measured.cy > height)
            && measured.cx > 0
            && measured.cy > 0
            && pixelHeight > 1) {
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

/// Draws text with the supplied font, color, alignment flags, and optional opaque background, restoring the
/// selected font.
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
static void DrawClockText(HDC dc, const std::wstring& text, RECT rect, HFONT font, COLORREF color,
        int leadingZeroMode, UINT format = DT_CENTER | DT_VCENTER | DT_SINGLELINE,
        COLORREF backgroundColor = CLR_INVALID) {
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

/// Centers panel time text using its current width and uses stable measured regions for standalone digital
/// clocks.
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
    if (config.type == WIDGET_PANEL) {
        GetTextExtentPoint32W(dc, text.c_str(), static_cast<int>(text.size()), &fullSize);
        GetTextExtentPoint32W(dc, text.c_str() + firstDigit, static_cast<int>(lastDigit - firstDigit + 1),
            &clockSize);
        if (firstDigit != 0) {
            SIZE prefixSize = {};
            GetTextExtentPoint32W(dc, text.c_str(), static_cast<int>(firstDigit), &prefixSize);
            prefixWidth = prefixSize.cx;
        }
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
        DrawCenteredText(dc, text.substr(0, firstDigit), prefixRect, font, color, lineFormat,
            backgroundColor);
    }
    DrawClockText(dc, text.substr(firstDigit, lastDigit - firstDigit + 1), clockRect, font, color,
        config.leadingZeroMode, lineFormat, backgroundColor);
    if (lastDigit + 1 < text.size()) {
        RECT suffixRect = { clockRect.right, rect.top, left + fullSize.cx, rect.bottom };
        DrawCenteredText(dc, text.substr(lastDigit + 1), suffixRect, font, color, lineFormat,
            backgroundColor);
    }
    RestoreDC(dc, savedDC);
}

/// Draws a centered fullscreen clock with stable numeric bounds and a separately centered footer using GDI.
static void DrawFullscreenClockText(HDC dc, const std::wstring& text, const RECT& rect,
        const WidgetConfig& config, COLORREF color, COLORREF backgroundColor) {
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

/// Loads a library by filename from the Windows system directory; the caller must release the returned
/// module.
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

/// Loads optional DirectWrite and Direct2D support and creates their factories, cleaning up if
/// initialization fails.
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
static HRESULT MeasureDirectText(IDWriteTextFormat* format, const std::wstring& text, float width,
        float height, DWRITE_TEXT_METRICS* metrics) {
    IDWriteTextLayout* layout = nullptr;
    HRESULT result = dwriteFactory->CreateTextLayout(text.c_str(), static_cast<UINT32>(text.size()), format,
        width, height, &layout);
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
            std::max(clockMetrics->widthIncludingTrailingWhitespace,
                metrics.widthIncludingTrailingWhitespace);
        clockMetrics->height = std::max(clockMetrics->height, metrics.height);
    }
    return S_OK;
}

/// Renders fullscreen clock text through DirectWrite and Direct2D with stable positioning and the selected
/// antialiasing. Returns false when optional rendering support is unavailable or drawing fails.
static bool DrawFullscreenText(HDC dc, const wchar_t* text, const RECT& rect, const WidgetConfig& config,
        COLORREF color, COLORREF backgroundColor) {
    if (d2dFactory == nullptr
            || dwriteFactory == nullptr
            || dc == nullptr
            || text == nullptr
            || text[0] == L'\0') {
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
    float fontSize = std::max(1.0f, static_cast<float>(height)
        * static_cast<float>(std::clamp(config.fontSize, FULLSCREEN_FONT_SIZE_MIN, FULLSCREEN_FONT_SIZE_MAX))
        / 100.0f);
    DWRITE_FONT_WEIGHT weight = static_cast<DWRITE_FONT_WEIGHT>(std::clamp(config.fontWeight, 1, 999));
    DWRITE_FONT_STYLE style = config.fontItalic ? DWRITE_FONT_STYLE_ITALIC : DWRITE_FONT_STYLE_NORMAL;
    IDWriteTextFormat* format = nullptr;
    const wchar_t* fontFace = config.fontFace.empty() ? L"Arial" : config.fontFace.c_str();
    result = dwriteFactory->CreateTextFormat(fontFace, nullptr, weight, style, DWRITE_FONT_STRETCH_NORMAL,
        fontSize, GetLanguageLocale(config.language), &format);
    if (FAILED(result) || format == nullptr) {
        target->Release();
        return false;
    }
    format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
    format->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
    DWRITE_TEXT_METRICS metrics = {};
    DWRITE_TEXT_METRICS clockMetrics = {};
    result = MeasureFullscreenDirectText(format, config, static_cast<float>(width),
        static_cast<float>(height), &metrics, &clockMetrics);
    if (SUCCEEDED(result)
            && (metrics.widthIncludingTrailingWhitespace > static_cast<float>(width)
                || metrics.height > static_cast<float>(height))) {
        float widthScale = metrics.widthIncludingTrailingWhitespace > 0.0f
            ? static_cast<float>(width) / metrics.widthIncludingTrailingWhitespace
            : 1.0f;
        float heightScale = metrics.height > 0.0f
            ? static_cast<float>(height) / metrics.height
            : 1.0f;
        fontSize = std::max(1.0f, fontSize * std::min(widthScale, heightScale));
        format->Release();
        format = nullptr;
        result = dwriteFactory->CreateTextFormat(fontFace, nullptr, weight, style, DWRITE_FONT_STRETCH_NORMAL,
            fontSize, GetLanguageLocale(config.language), &format);
        if (SUCCEEDED(result) && format != nullptr) {
            format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
            format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
            format->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
            result = MeasureFullscreenDirectText(format, config, static_cast<float>(width),
                static_cast<float>(height), &metrics, &clockMetrics);
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
            DWRITE_TEXT_RANGE footerRange = { 0, static_cast<UINT32>(footerText.size()) };
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
    DWRITE_TEXT_RANGE range = { 0, length };
    layout->SetUnderline(config.fontUnderline, range);
    layout->SetStrikethrough(config.fontStrikeOut, range);
    ID2D1SolidColorBrush* brush = nullptr;
    result = target->CreateSolidColorBrush(D2D1::ColorF(GetRValue(color) / 255.0f, GetGValue(color) / 255.0f,
        GetBValue(color) / 255.0f), &brush);
    ID2D1SolidColorBrush* hiddenBrush = nullptr;
    if (SUCCEEDED(result) && config.leadingZeroMode == LEADING_ZERO_RESERVED && text[0] == L'0') {
        result = target->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f), &hiddenBrush);
        if (SUCCEEDED(result)) {
            result = layout->SetDrawingEffect(hiddenBrush, DWRITE_TEXT_RANGE{ 0, 1 });
        }
    }
    if (SUCCEEDED(result) && brush != nullptr) {
        target->SetTextAntialiasMode(DirectWriteAntialiasMode(config.fontAntialiasing));
        target->BeginDraw();
        target->Clear(D2D1::ColorF(GetRValue(backgroundColor) / 255.0f, GetGValue(backgroundColor) / 255.0f,
            GetBValue(backgroundColor) / 255.0f));
        float clockLeft = (static_cast<float>(width) - clockMetrics.widthIncludingTrailingWhitespace) / 2.0f;
        float clockTop = (static_cast<float>(height) - metrics.height) / 2.0f;
        target->DrawTextLayout(D2D1::Point2F(clockLeft, clockTop), layout, brush,
            D2D1_DRAW_TEXT_OPTIONS_CLIP);
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
    RECT borderRect = { 0, 0, width, height };
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

/// Writes the four system-colored frame lines used by a transparent digital widget's three-dimensional
/// border.
static void DrawTransparentDigital3DBorder(DWORD* pixels, int width, int height) {
    DrawLayeredFrameLine(pixels, width, height, 0, GetSysColor(COLOR_3DHIGHLIGHT),
        GetSysColor(COLOR_3DDKSHADOW));
    DrawLayeredFrameLine(pixels, width, height, 1, GetSysColor(COLOR_3DLIGHT),
        GetSysColor(COLOR_3DSHADOW));
    DrawLayeredFrameLine(pixels, width, height, 2, GetSysColor(COLOR_3DSHADOW),
        GetSysColor(COLOR_3DLIGHT));
    DrawLayeredFrameLine(pixels, width, height, 3, GetSysColor(COLOR_3DDKSHADOW),
        GetSysColor(COLOR_3DHIGHLIGHT));
}

/// Draws the configured number of nested flat border lines inside the supplied inset.
static void DrawDigitalWidthBorder(HDC dc, int width, int height, int inset, int borderWidth,
        COLORREF color) {
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

/// Formats the current displayed time into a bounded buffer and adds an enabled UTC suffix or fullscreen
/// footer.
static void GetDigitalTimeText(const WidgetConfig& config, wchar_t* text, size_t textCount,
        ULONGLONG applicationUtc = 0) {
    SYSTEMTIME time = {};
    GetDisplayedTime(config, &time, applicationUtc);
    std::wstring formatted = FormatWidgetTime(config, time);
    if (config.showUtc && config.showUtcText) {
        formatted += config.type == WIDGET_FULLSCREEN ? L"\r\nUTC" : L" UTC";
    }
    wcsncpy_s(text, textCount, formatted.c_str(), _TRUNCATE);
}

/// Calculates digital text padding, scaling fullscreen preview padding and limiting it to the available
/// client area.
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

/// Paints an opaque digital or fullscreen clock, including alarm colors, borders, and any identification
/// outline.
static void PaintOpaqueDigitalWidget(Widget* widget, HWND window, HDC dc) {
    RECT client = {};
    GetClientRect(window, &client);
    bool alarmFlash = widget->alarmActive && widget->flashPhase;
    COLORREF textColor = alarmFlash ? widget->config.alarmTextColor : widget->config.textColor;
    COLORREF backgroundColor = alarmFlash
        ? widget->config.alarmBackgroundColor
        : widget->config.backgroundColor;
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

/// Builds and presents the digital widget's layered bitmap with text, border, background transparency,
/// and opacity.
static void RenderCustomWidget(Widget* widget) {
    int width = 0;
    int height = 0;
    GetWidgetDimensions(widget->config, &width, &height, &widget->panelNotices, widget->panelApplicationUtc);
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
    COLORREF textColor = alarmFlash
        ? widget->config.alarmTextColor
        : widget->config.textColor;
    COLORREF backgroundColor = alarmFlash
        ? widget->config.alarmBackgroundColor
        : widget->config.backgroundColor;
    HBRUSH background = CreateSolidBrush(transparentDigital ? RGB(255, 255, 255) : backgroundColor);
    RECT full = { 0, 0, width, height };
    FillRect(dc, &full, background);
    DeleteObject(background);
    wchar_t text[128] = {};
    GetDigitalTimeText(widget->config, text, _countof(text));
    int borderStyleInset = GetBorderStyleInset(widget->config.borderStyle);
    int inset = widget->config.padding + borderStyleInset + widget->config.borderWidth;
    RECT textRect = { inset, inset, width - inset, height - inset };
    HFONT font = CreateWidgetDrawingFont(widget->config);
    DrawWidgetTimeText(dc, text, textRect, font,
        transparentDigital ? RGB(0, 0, 0) : textColor, widget->config, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
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
            int coverage = 255 - (static_cast<BYTE>(pixel) + static_cast<BYTE>(pixel >> 8)
                + static_cast<BYTE>(pixel >> 16)) / 3;
            int alpha = std::max(minimumHitTestAlpha, coverage);
            int red = GetRValue(color) * alpha / 255;
            int green = GetGValue(color) * alpha / 255;
            int blue = GetBValue(color) * alpha / 255;
            pixels[index] = static_cast<DWORD>(alpha) << 24 | red << 16 | green << 8 | blue;
        }
        if (!(widget->identifyActive && widget->identifyPhase)) {
            if (widget->config.borderStyle == DIGITAL_BORDER_TOOL_WINDOW) {
                DrawLayeredFrameLine(pixels, width, height, 0, widget->config.borderColor,
                    widget->config.borderColor);
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

/// Requests one parent-buffer update for a panel link without invalidating native siblings.
static void InvalidatePanelLink(HWND link) {
    HWND parent = GetParent(link);
    RECT bounds = {};
    if (parent != nullptr && GetWindowRect(link, &bounds)) {
        MapWindowPoints(nullptr, parent, reinterpret_cast<POINT*>(&bounds), 2);
        RedrawWindow(parent, &bounds, nullptr, RDW_INVALIDATE | RDW_NOCHILDREN);
    }
}

/// Replaces a panel link's GDI font and deletes its previous owned font after successful creation.
static void ApplyPanelLinkFont(HWND link, const FontSelection& selection, int fontAntialiasing,
        HFONT* currentFont) {
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

/// Updates a panel link's text only when changed, then sizes and centers its clickable area within the
/// supplied bounds.
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
    RECT current = {};
    GetWindowRect(link, &current);
    MapWindowPoints(nullptr, GetParent(link), reinterpret_cast<POINT*>(&current), 2);
    if (current.left != x
            || current.top != y
            || current.right - current.left != width
            || current.bottom - current.top != height) {
        SetWindowPos(link, nullptr, x, y, width, height, SWP_NOZORDER | SWP_NOACTIVATE);
    }
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

/// Draws a panel link's text, hover underline and focus cue into the shared frame or a print DC.
static void DrawPanelLink(Widget* widget, HWND link, HDC dc, const RECT& bounds) {
    int savedState = SaveDC(dc);
    if (savedState == 0) {
        return;
    }
    bool dateLink = link == widget->panelDateLink;
    HBRUSH background = CreateSolidBrush(PanelBackgroundColor(widget));
    FillRect(dc, &bounds, background);
    DeleteObject(background);
    const FontSelection& selection = dateLink
        ? widget->config.panelTopFont
        : widget->config.panelBottomFont;
    bool hot = dateLink ? widget->panelDateHot : widget->panelTimeZoneHot;
    bool focused = GetFocus() == link;
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
        SelectObject(dc, font);
    }
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, RGB(0, 83, 184));
    std::wstring text = GetControlText(link);
    RECT textRect = bounds;
    DrawTextW(dc, text.c_str(), static_cast<int>(text.size()), &textRect,
        DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
    if (focused) {
        RECT focusRect = bounds;
        InflateRect(&focusRect, -1, -1);
        DrawPanelLinkFocusRect(dc, focusRect);
    }
    RestoreDC(dc, savedState);
    if (hotFont != nullptr) {
        DeleteObject(hotFont);
    }
}

/// Draws both links into the complete panel bitmap before any of their pixels are presented.
static void DrawPanelLinks(Widget* widget, HDC dc) {
    const HWND links[] = { widget->panelDateLink, widget->panelTimeZoneLink };
    for (HWND link : links) {
        RECT bounds = {};
        if (link != nullptr && IsWindowVisible(link) && GetWindowRect(link, &bounds)) {
            MapWindowPoints(nullptr, widget->window, reinterpret_cast<POINT*>(&bounds), 2);
            DrawPanelLink(widget, link, dc, bounds);
        }
    }
}

/// Copies completed link pixels from the panel bitmap while retaining native child clipping on the parent.
static void PresentPanelLinks(Widget* widget, HDC buffer) {
    const HWND links[] = { widget->panelDateLink, widget->panelTimeZoneLink };
    for (HWND link : links) {
        RECT bounds = {};
        if (link != nullptr && IsWindowVisible(link) && GetWindowRect(link, &bounds)) {
            MapWindowPoints(nullptr, widget->window, reinterpret_cast<POINT*>(&bounds), 2);
            HDC target = GetDC(link);
            if (target != nullptr) {
                if (BitBlt(target, 0, 0, bounds.right - bounds.left, bounds.bottom - bounds.top,
                    buffer, bounds.left, bounds.top, SRCCOPY)) {
                    ValidateRect(link, nullptr);
                }
                ReleaseDC(link, target);
            }
        }
    }
}

/// Updates the panel's date and time-zone links using its displayed date, configured zone, and offset.
static void UpdatePanelLinks(Widget* widget, const SYSTEMTIME& time) {
    if (widget == nullptr) {
        return;
    }
    PanelLayout layout =
        CalculatePanelLayout(widget->config, &widget->panelNotices, widget->panelApplicationUtc);
    wchar_t dateText[128] = {};
    GetDateFormatEx(GetLanguageLocale(widget->config.language), DATE_LONGDATE, &time, nullptr, dateText,
        ARRAYSIZE(dateText), nullptr);
    UpdatePanelLinkButton(widget->panelDateLink, widget->panelDateFont, dateText, layout.header);
    std::wstring zoneName = widget->config.showUtc ? L"UTC" : widget->config.timeZoneKey;
    if (!widget->config.showUtc && _wcsicmp(widget->config.timeZoneKey.c_str(), SYSTEM_TIME_ZONE_KEY) == 0) {
        zoneName = GetLocalizedText(widget->config.language, TXT_SYSTEM_TIME_ZONE_LABEL);
    } else if (!widget->config.showUtc) {
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
    UpdatePanelLinkButton(widget->panelTimeZoneLink, widget->panelTimeZoneFont, zoneText, layout.footer);
}

/// Keeps native panel-link input while presenting its text through the panel's shared buffer.
/// Supports printing, hover, focus and double-clicks without requesting paints from inside parent painting.
static LRESULT CALLBACK PanelLinkButtonSubclassProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    UNREFERENCED_PARAMETER(referenceData);
    if (msg == WM_SETCURSOR) {
        SetCursor(LoadCursorW(nullptr, IDC_HAND));
        return TRUE;
    }
    HWND parent = GetParent(window);
    Widget* widget = reinterpret_cast<Widget*>(GetWindowLongPtrW(parent, GWLP_USERDATA));
    if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONDBLCLK) {
        SetFocus(window);
        if (msg == WM_LBUTTONDBLCLK) {
            return DefSubclassProc(window, WM_LBUTTONDOWN, wParam, lParam);
        }
    }
    if (widget != nullptr) {
        if (msg == WM_ERASEBKGND) {
            return 1;
        }
        if (msg == WM_PAINT) {
            PAINTSTRUCT paint = {};
            BeginPaint(window, &paint);
            EndPaint(window, &paint);
            InvalidatePanelLink(window);
            return 0;
        }
        if (msg == WM_PRINTCLIENT || msg == WM_PRINT) {
            bool skipPrint = msg == WM_PRINT && ((lParam & PRF_CLIENT) == 0
                || (lParam & PRF_CHECKVISIBLE) != 0 && !IsWindowVisible(window));
            if (skipPrint) {
                return 0;
            }
            RECT bounds = {};
            GetClientRect(window, &bounds);
            DrawPanelLink(widget, window, reinterpret_cast<HDC>(wParam), bounds);
            return 0;
        }
        bool* hot = window == widget->panelDateLink
            ? &widget->panelDateHot
            : &widget->panelTimeZoneHot;
        if (msg == WM_MOUSEMOVE && !*hot) {
            *hot = true;
            TRACKMOUSEEVENT tracking = { sizeof(tracking), TME_LEAVE, window, 0 };
            TrackMouseEvent(&tracking);
            InvalidatePanelLink(window);
        } else if (msg == WM_MOUSELEAVE) {
            *hot = false;
            InvalidatePanelLink(window);
        }
    }
    if (msg == WM_NCDESTROY) {
        RemoveWindowSubclass(window, PanelLinkButtonSubclassProc, subclassId);
    }
    return DefSubclassProc(window, msg, wParam, lParam);
}

/// Creates sibling-clipped date and time-zone links below the panel's other controls, assigns their fonts,
/// and installs the date tooltip.
static void CreatePanelLinks(Widget* widget) {
    if (widget->config.type != WIDGET_PANEL) {
        return;
    }
    widget->panelDateLink = CreateWindowExW(0, L"BUTTON", L"",
        WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPSIBLINGS | BS_OWNERDRAW, 0, 0, 0, 0, widget->window,
            reinterpret_cast<HMENU>(ID_PANEL_DATE_LINK), hInstance, nullptr);
    if (widget->panelDateLink == nullptr) {
        return;
    }
    SetWindowSubclass(widget->panelDateLink, PanelLinkButtonSubclassProc, ID_PANEL_DATE_LINK, 0);
    ApplyWidgetTheme(widget->panelDateLink, widget->config);
    ApplyPanelLinkFont(widget->panelDateLink, widget->config.panelTopFont, widget->config.fontAntialiasing,
        &widget->panelDateFont);
    widget->panelTimeZoneLink = CreateWindowExW(0, L"BUTTON", L"",
        WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPSIBLINGS | BS_OWNERDRAW, 0, 0, 0, 0, widget->window,
        reinterpret_cast<HMENU>(ID_PANEL_TIME_ZONE_LINK), hInstance, nullptr);
    if (widget->panelTimeZoneLink == nullptr) {
        return;
    }
    SetWindowSubclass(widget->panelTimeZoneLink, PanelLinkButtonSubclassProc, ID_PANEL_TIME_ZONE_LINK, 0);
    ApplyWidgetTheme(widget->panelTimeZoneLink, widget->config);
    ApplyPanelLinkFont(widget->panelTimeZoneLink, widget->config.panelBottomFont,
        widget->config.fontAntialiasing, &widget->panelTimeZoneFont);
    SetWindowPos(widget->calendarChild, HWND_TOP, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    SetWindowPos(widget->panelDateLink, HWND_BOTTOM, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    SetWindowPos(widget->panelTimeZoneLink, HWND_BOTTOM, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    SYSTEMTIME displayed = {};
    GetDisplayedTime(widget->config, &displayed, widget->panelApplicationUtc);
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

/// Excludes visible child controls from the drawing region shared by all panel clock captions, times,
/// and weekdays.
static void ExcludePanelControlsFromText(HWND window, HDC dc) {
    for (HWND control = GetWindow(window, GW_CHILD);
            control != nullptr;
            control = GetWindow(control, GW_HWNDNEXT)) {
        bool visible = GetWindowLongPtrW(control, GWL_STYLE) & WS_VISIBLE;
        if (!visible) {
            continue;
        }
        RECT bounds = {};
        bool boundsAvailable = GetWindowRect(control, &bounds) != FALSE;
        if (!boundsAvailable) {
            continue;
        }
        MapWindowPoints(HWND_DESKTOP, window, reinterpret_cast<POINT*>(&bounds), 2);
        ExcludeClipRect(dc, bounds.left, bounds.top, bounds.right, bounds.bottom);
    }
}

/// Paints one native notice divider with a system-color line when theme drawing is unavailable.
static void DrawPanelNoticeSeparator(HDC dc, HTHEME theme, const RECT& separator) {
    bool drawn = theme != nullptr && SUCCEEDED(DrawThemeBackground(theme, dc, FLYOUT_DIVIDER, 0,
        &separator, nullptr));
    if (!drawn) {
        RECT line = separator;
        line.bottom = line.top + 1;
        FillRect(dc, &line, GetSysColorBrush(COLOR_3DSHADOW));
    }
}

/// Paints the native notice icons and wrapped text into the panel's existing shared buffer.
static void DrawPanelTimeNotices(Widget* widget, HDC dc, const PanelLayout& layout) {
    if (layout.notices.empty()) {
        return;
    }
    HFONT font = CreatePanelFont(widget->config.panelBottomFont, widget->config.fontAntialiasing);
    if (font == nullptr) {
        return;
    }
    HGDIOBJ previousFont = SelectObject(dc, font);
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, GetSysColor(COLOR_WINDOWTEXT));
    HTHEME theme = OpenThemeData(widget->window, L"Flyout");
    size_t count = std::min(layout.notices.size(), widget->panelNotices.size());
    for (size_t index = 0; index < count; index++) {
        const TimeDateNotice& notice = widget->panelNotices[index];
        const PanelNoticeLayout& row = layout.notices[index];
        DrawPanelNoticeSeparator(dc, theme, row.separator);
        const wchar_t* iconName = notice.icon == TimeDateNoticeIcon::Warning ? IDI_WARNING : IDI_INFORMATION;
        HICON icon = nullptr;
        if (SUCCEEDED(LoadIconMetric(nullptr, iconName, LIM_SMALL, &icon))) {
            DrawIconEx(dc, row.icon.left, row.icon.top, icon, row.icon.right - row.icon.left,
                row.icon.bottom - row.icon.top, 0, nullptr, DI_NORMAL);
            DestroyIcon(icon);
        }
        RECT text = row.text;
        DrawTextW(dc, notice.text.c_str(), static_cast<int>(notice.text.size()), &text,
            DT_WORDBREAK | DT_NOFULLWIDTHCHARBREAK | DT_NOPREFIX);
    }
    DrawPanelNoticeSeparator(dc, theme, layout.noticeBottomSeparator);
    if (theme != nullptr) {
        CloseThemeData(theme);
    }
    SelectObject(dc, previousFont);
    DeleteObject(font);
}

/// Paints the panel background and text, clipping all clock captions, times, and weekdays beneath its child
/// controls. Draws alarm or identification feedback after restoring the original drawing region.
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
    GetDisplayedTime(widget->config, &time, widget->panelApplicationUtc);
    int savedDC = SaveDC(dc);
    if (savedDC == 0) {
        return;
    }
    ExcludePanelControlsFromText(widget->window, dc);
    HFONT timeFont = CreatePanelFont(widget->config.panelTimeFont, widget->config.fontAntialiasing);
    HFONT nameFont = CreatePanelFont(widget->config.panelTopFont, widget->config.fontAntialiasing);
    PanelLayout layout =
        CalculatePanelLayout(widget->config, &widget->panelNotices, widget->panelApplicationUtc);
    for (int index = 0; index <= ADDITIONAL_CLOCK_COUNT; index++) {
        if (index > 0 && !widget->config.additionalClocks[index - 1].enabled) {
            continue;
        }
        WidgetConfig clock = index == 0
            ? widget->config
            : AdditionalClockConfiguration(widget->config, index - 1);
        wchar_t clockText[128] = {};
        GetDigitalTimeText(clock, clockText, ARRAYSIZE(clockText), widget->panelApplicationUtc);
        DrawWidgetTimeText(dc, clockText, layout.times[index], timeFont, RGB(0, 0, 0), clock);
        if (!IsRectEmpty(&layout.days[index])) {
            GetDisplayedTime(clock, &time, widget->panelApplicationUtc);
            wchar_t day[128] = {};
            GetDateFormatEx(GetLanguageLocale(clock.language), 0, &time, L"dddd", day, ARRAYSIZE(day),
                nullptr);
            DrawCenteredText(dc, day, layout.days[index], timeFont, RGB(0, 0, 0));
        }
        if (index > 0) {
            DrawCenteredText(dc, AdditionalClockName(widget->config, index - 1),
                layout.names[index - 1], nameFont, RGB(0, 0, 0),
                DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOPREFIX);
        }
    }
    DrawPanelTimeNotices(widget, dc, layout);
    RestoreDC(dc, savedDC);
    DeleteObject(nameFont);
    DeleteObject(timeFont);
    DrawPanelLinks(widget, dc);
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
    if (panel) {
        PresentPanelLinks(widget, buffer);
    }
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
        ULONGLONG previousApplicationUtc = widget->panelApplicationUtc;
        bool noticesChanged = false;
        if (widget->panelNoticesPrepared) {
            widget->panelNoticesPrepared = false;
        } else {
            widget->panelApplicationUtc = GetApplicationFileTimeValue();
            std::vector<TimeDateNotice> notices = GetPanelTimeNotices(widget->config,
                widget->panelCalendarDateSupported, widget->panelApplicationUtc);
            noticesChanged = !PanelTimeNoticesEqual(widget->panelNotices, notices);
            widget->panelNotices = std::move(notices);
        }
        SYSTEMTIME displayed = {};
        GetDisplayedTime(widget->config, &displayed, widget->panelApplicationUtc);
        int dateKey = displayed.wYear * 10000 + displayed.wMonth * 100 + displayed.wDay;
        bool dateChanged = widget->lastPanelDateKey != dateKey;
        bool layoutChanged = false;
        if (widget->rendered && dateChanged) {
            PanelLayout previous = CalculatePanelLayout(widget->config, nullptr, previousApplicationUtc);
            PanelLayout current = CalculatePanelLayout(widget->config, nullptr, widget->panelApplicationUtc);
            layoutChanged = !EqualRect(&previous.clocks[0], &current.clocks[0]);
        }
        bool resized = false;
        if (!widget->rendered || noticesChanged || dateChanged) {
            int width = 0;
            int height = 0;
            GetWidgetDimensions(widget->config, &width, &height, &widget->panelNotices,
                widget->panelApplicationUtc);
            RECT current = {};
            if (GetWindowRect(widget->window, &current)
                    && (current.right - current.left != width
                        || current.bottom - current.top != height
                        || layoutChanged)) {
                if (widget->rendered && IsWindowVisible(widget->window)) {
                    WidgetConfig positioned = widget->config;
                    POINT position = { current.left, current.top };
                    GetPositionPreservingWorkAreaAttachment(widget->window, width, height, &position);
                    positioned.x = position.x;
                    positioned.y = position.y;
                    if (RecreatePanelWidgetBuffered(widget, positioned, &widget->panelNotices,
                        widget->panelApplicationUtc)) {
                        return;
                    }
                }
                ResizeWidgetPreservingWorkAreaAttachment(widget, width, height,
                    SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOREDRAW);
                resized = true;
            }
        }
        UpdateAnalogTime(widget, widget->panelApplicationUtc);
        UpdatePanelLinks(widget, displayed);
        if (!widget->rendered || widget->lastPanelDateKey != dateKey || widget->alarmActive) {
            widget->lastPanelDateKey = dateKey;
            InvalidateRect(widget->window, nullptr, FALSE);
        } else {
            PanelLayout layout =
                CalculatePanelLayout(widget->config, &widget->panelNotices, widget->panelApplicationUtc);
            for (int index = 0; index <= ADDITIONAL_CLOCK_COUNT; index++) {
                if (index > 0 && !widget->config.additionalClocks[index - 1].enabled) {
                    continue;
                }
                RECT textRect = layout.times[index];
                textRect.bottom = std::max(textRect.bottom, layout.days[index].bottom);
                InvalidateRect(widget->window, &textRect, FALSE);
            }
        }
        if (noticesChanged && !widget->panelNotices.empty()) {
            PanelLayout layout =
                CalculatePanelLayout(widget->config, &widget->panelNotices, widget->panelApplicationUtc);
            if (!layout.notices.empty()) {
                RECT noticeBounds = {
                    0,
                    layout.notices.front().separator.top,
                    layout.clientSize.cx,
                    layout.footer.top
                };
                InvalidateRect(widget->window, &noticeBounds, FALSE);
            }
        }
        UINT redrawFlags = RDW_UPDATENOW | RDW_ALLCHILDREN;
        if (resized) {
            redrawFlags |= RDW_FRAME | RDW_INVALIDATE;
        }
        RedrawWindow(widget->window, nullptr, nullptr, redrawFlags);
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
        GetWidgetDimensions(widget->config, &desiredWidth, &desiredHeight, &widget->panelNotices,
            widget->panelApplicationUtc);
        RECT current = {};
        if (GetWindowRect(widget->window, &current)
                && (current.right - current.left != desiredWidth
                    || current.bottom - current.top != desiredHeight)) {
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
        SetWindowPos(widget->fullscreenWindows[index], insertAfter, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
}

/// Raises the widget's windows within the appropriate normal or topmost group without taking focus.
static void BringWidgetForward(Widget* widget) {
    if (widget == nullptr || widget->window == nullptr) {
        return;
    }
    HWND insertAfter = widget->config.topMost
        || widget->config.type == WIDGET_FULLSCREEN ? HWND_TOPMOST : HWND_TOP;
    SetWindowPos(widget->window, insertAfter, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
        SetWindowPos(widget->fullscreenWindows[index], insertAfter, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
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

/// Temporarily reveals and raises a widget, starts its identification highlight, and remembers state to
/// restore afterward.
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

/// Requests audio cancellation, closes the widget-owned event handles, and advances the generation to reject
/// stale notifications.
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

/// Copies a live widget's mute state into its settings draft and updates the selected checkbox when
/// applicable.
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

/// Updates a sound-capable widget's mute state across audio playback, shared time signals, and its settings
/// preview.
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
    if (widget == nullptr
            || !WidgetSupportsSound(widget->config.type)
            || widget->config.soundsMuted == muted) {
        return;
    }
    ApplyWidgetSoundsMuted(widget, muted);
    SynchronizeWidgetSoundsMuted(widget);
    SaveSettingsWithoutAppearancePreviews();
}

/// Mutes all currently audible widgets or restores the previous set of widgets muted by this command,
/// then saves settings.
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

/// Returns the owning widget for a main, child, or additional fullscreen input window, or null when none
/// matches.
static Widget* WidgetFromInputWindow(HWND window) {
    for (size_t widgetIndex = 0; widgetIndex < widgets.size(); widgetIndex++) {
        Widget* widget = widgets[widgetIndex].get();
        if (window == widget->window || IsChild(widget->window, window)) {
            return widget;
        }
        for (size_t wndIndex = 0; wndIndex < widget->fullscreenWindows.size(); wndIndex++) {
            HWND fullscreenWindow = widget->fullscreenWindows[wndIndex];
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
    bool blackout =
        std::find(blackoutWindows.begin(), blackoutWindows.end(), window) != blackoutWindows.end();
    if (!fullscreen && !blackout) {
        ResetFullscreenCursor(hFullscreenCursorWindow);
        return false;
    }
    GUITHREADINFO information = {};
    information.cbSize = sizeof(information);
    bool interacting = false;
    if (GetGUIThreadInfo(0, &information)) {
        interacting =
            information.flags & (GUI_INMENUMODE | GUI_POPUPMENUMODE | GUI_SYSTEMMENUMODE | GUI_INMOVESIZE)
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

/// Updates fullscreen cursor activity from mouse and lifecycle messages and handles applicable client-area
/// cursor requests.
static bool HandleFullscreenCursorMessage(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
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
/// Preserves other contributors and remembers cancellation so the same alarm sequence is not immediately
/// restarted.
static void StopWidgetAlarm(Widget* widget) {
    if (widget == nullptr) {
        return;
    }
    CloseWidgetAudio(widget);
    widget->alarmActive = false;
    widget->flashPhase = false;
    ULONGLONG now = MonotonicFileTimeValue();
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
            CancelTimeSignalPlayback(group.target, group.outputDevice);
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

/// Shows and raises a widget, starts its visual alarm, and launches configured audio, local command, or
/// remote URL actions.
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
            StartAudioPlaybackAsync(widget->config.command, widget->config.loopAudio,
                widget->config.soundsMuted, std::make_shared<std::atomic<int>>(widget->config.alarmVolume),
                hController, WM_AUDIO_FINISHED, widget->config.id, widget->audioGeneration,
                &widget->audioStopEvent, &widget->audioMuteEvent);
        } else {
            StartLocalCommandAsync(widget->config.command);
        }
    }
    if (widget->config.callRemoteScript) {
        StartRemoteScriptAsync(widget->config.remoteScriptUrl);
    }
    RenderWidget(widget);
}

/// Checks displayed-minute transitions against the enabled weekdays and alarm time, preventing duplicate
/// activation for that minute.
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

/// Copies a nonfullscreen widget's current screen position into live and draft settings, then saves without
/// appearance previews.
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

/// Temporarily substitutes committed widget configurations while saving, then restores the active appearance
/// previews.
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

/// Creates and subclasses the primary native clock control, placing panel clocks onscreen and layered-widget
/// source controls offscreen.
static void CreateAnalogChild(Widget* widget) {
    if (widget == nullptr) {
        return;
    }
    int childX = -widget->config.size - 2;
    int childY = 0;
    if (widget->config.type == WIDGET_PANEL) {
        POINT clockPosition = {};
        GetPanelLayout(widget->config, nullptr, &clockPosition, nullptr, &widget->panelNotices,
            widget->panelApplicationUtc);
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
    PanelLayout layout =
        CalculatePanelLayout(widget->config, &widget->panelNotices, widget->panelApplicationUtc);
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

/// Changes the primary clock's second-hand state in place when possible, otherwise replaces only that native
/// child.
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
        GetPanelLayout(widget->config, nullptr, &clockPosition, nullptr, &widget->panelNotices,
            widget->panelApplicationUtc);
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
    SetWindowPos(replacement, HWND_TOP, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
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

/// Creates and subclasses a native calendar with the widget's locale, font, weekday, week-number,
/// and Today-row settings.
static void CreateCalendarChild(Widget* widget) {
    if (widget == nullptr) {
        return;
    }
    SIZE calendarSize = GetCalendarSize(widget->config, true);
    int childX = 0;
    int childY = 0;
    if (widget->config.type == WIDGET_PANEL) {
        RECT calendarRect = {};
        GetPanelLayout(widget->config, &calendarRect, nullptr, nullptr, &widget->panelNotices,
            widget->panelApplicationUtc);
        childX = calendarRect.left;
        childY = calendarRect.top;
    }
    DWORD style = WS_CHILD | WS_TABSTOP | (widget->config.weekNumbers ? MCS_WEEKNUMBERS : 0);
    if (widget->config.type == WIDGET_PANEL || !widget->config.showToday) {
        style |= MCS_NOTODAY;
    }
    CalendarLocaleScope localeScope(GetLanguageLocale(widget->config.language));
    widget->calendarChild = CreateWindowExW(0, MONTHCAL_CLASSW, L"", style, 0, 0, 0, 0, widget->window,
        reinterpret_cast<HMENU>(114), hInstance, nullptr);
    if (widget->calendarChild != nullptr) {
        ApplyWidgetTheme(widget->calendarChild, widget->config);
    }
    if (widget->calendarChild != nullptr) {
        ApplyCalendarFont(widget);
        MonthCal_SetCalendarBorder(widget->calendarChild, TRUE, 0);
        SYSTEMTIME displayed = {};
        GetDisplayedTime(widget->config, &displayed, widget->panelApplicationUtc);
        MonthCal_SetToday(widget->calendarChild, &displayed);
        widget->panelCalendarDateSupported = MonthCal_SetCurSel(widget->calendarChild, &displayed) != FALSE;
        widget->lastCalendarDateKey = displayed.wYear * 10000 + displayed.wMonth * 100 + displayed.wDay;
        MonthCal_SetFirstDayOfWeek(widget->calendarChild, widget->config.sundayFirst ? 6 : 0);
        RECT minimum = {};
        if (MonthCal_GetMinReqRect(widget->calendarChild, &minimum)) {
            calendarSize.cx = minimum.right - minimum.left;
            calendarSize.cy = minimum.bottom - minimum.top;
        }
        SetWindowPos(widget->calendarChild, nullptr, childX, childY, calendarSize.cx, calendarSize.cy,
            SWP_NOZORDER | SWP_NOACTIVATE);
        widget->calendarProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(widget->calendarChild,
            GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(CalendarChildProc)));
        ShowWindow(widget->calendarChild, SW_SHOWNOACTIVATE);
        RedrawWindow(widget->calendarChild, nullptr, nullptr,
            RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_UPDATENOW);
    }
}

/// Calculates bounded preview dimensions from the selected monitor's aspect ratio, returning false if
/// geometry is unavailable.
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

/// Converts a fullscreen widget's main window to its settings preview and hides its additional fullscreen
/// windows.
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
    SetWindowPos(widget->window, HWND_TOPMOST, previewX, previewY, previewWidth, previewHeight,
        SWP_NOACTIVATE);
    for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
        ShowWindow(widget->fullscreenWindows[index], SW_HIDE);
    }
    return true;
}

/// Creates a widget's main and required child or monitor windows and applies layout, theme, rendering,
/// and visibility. Activates the main window when replacing an active widget; other creation paths leave
/// activation unchanged.
static void CreateWidgetWindow(Widget* widget, bool activate = false,
        const std::vector<TimeDateNotice>* notices = nullptr, ULONGLONG applicationUtc = 0) {
    if (widget == nullptr) {
        return;
    }
    if (widget->config.type == WIDGET_ANALOG || widget->config.type == WIDGET_PANEL) {
        widget->config.size = NormalizeAnalogClockSize(widget->config.size);
        for (AdditionalClockConfig& clock : widget->config.additionalClocks) {
            clock.size = NormalizeAnalogClockSize(clock.size);
        }
    }
    bool previousCalendarSupported = widget->panelCalendarDateSupported;
    widget->panelApplicationUtc = widget->config.type == WIDGET_PANEL
        ? applicationUtc == 0 ? GetApplicationFileTimeValue() : applicationUtc
        : 0;
    widget->panelNotices = notices == nullptr
        ? GetPanelTimeNotices(widget->config, previousCalendarSupported, widget->panelApplicationUtc)
        : *notices;
    widget->panelNoticesPrepared = true;
    bool fullscreen = widget->config.type == WIDGET_FULLSCREEN;
    std::vector<const DisplayMonitor*> selectedMonitors;
    if (fullscreen) {
        selectedMonitors = SelectedDisplayMonitors(widget->config);
        if (!selectedMonitors.empty()) {
            widget->config.x = selectedMonitors[0]->rect.left;
            widget->config.y = selectedMonitors[0]->rect.top;
        }
    } else {
        ClampWidgetPosition(&widget->config, &widget->panelNotices);
    }
    int width = 0;
    int height = 0;
    GetWidgetDimensions(widget->config, &width, &height, &widget->panelNotices, widget->panelApplicationUtc);
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
                rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr,
                hInstance, widget);
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
    if (widget->panelCalendarDateSupported != previousCalendarSupported) {
        widget->panelNotices = GetPanelTimeNotices(widget->config, widget->panelCalendarDateSupported,
            widget->panelApplicationUtc);
    }
    CreatePanelLinks(widget);
    if (parentedControl && widget->config.opacity < 100) {
        SetLayeredWindowAttributes(widget->window, 0, static_cast<BYTE>(widget->config.opacity * 255 / 100),
            LWA_ALPHA);
    } else if (widget->config.type == WIDGET_DIGITAL && !widget->config.transparentBackground) {
        SetLayeredWindowAttributes(widget->window, 0, static_cast<BYTE>(widget->config.opacity * 255 / 100),
            LWA_ALPHA);
    }
    if (widget->config.visible) {
        RenderWidget(widget);
        ShowWindow(widget->window, activate ? SW_SHOWNORMAL : SW_SHOWNOACTIVATE);
        RedrawWindow(widget->window, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
        if (!widget->fullscreenPreview) {
            for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
                ShowWindow(widget->fullscreenWindows[index], SW_SHOWNOACTIVATE);
                RedrawWindow(widget->fullscreenWindows[index], nullptr, nullptr,
                    RDW_INVALIDATE | RDW_UPDATENOW);
            }
        }
    }
    widget->panelNoticesPrepared = false;
}

/// Stops widget audio and destroys its windows, tooltips, and owned fonts, then clears the associated
/// runtime handles.
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
    for (size_t wndIndex = 0; wndIndex < widget->fullscreenWindows.size(); wndIndex++) {
        if (IsWindow(widget->fullscreenWindows[wndIndex])) {
            DestroyWindow(widget->fullscreenWindows[wndIndex]);
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
static LRESULT CALLBACK BlackoutWindowProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (HandleFullscreenCursorMessage(window, msg, wParam, lParam)) {
        return TRUE;
    }
    if (msg == WM_ERASEBKGND) {
        RECT rect = {};
        GetClientRect(window, &rect);
        FillRect(reinterpret_cast<HDC>(wParam), &rect, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
        return 1;
    }
    if (msg == WM_PAINT) {
        PAINTSTRUCT paint = {};
        HDC dc = BeginPaint(window, &paint);
        FillRect(dc, &paint.rcPaint, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
        EndPaint(window, &paint);
        return 0;
    }
    return DefWindowProcW(window, msg, wParam, lParam);
}

/// Reconciles fullscreen clocks, settings previews, and blackout windows with current monitor and visibility
/// settings.
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
        for (size_t wndIndex = 0; wndIndex < widget->fullscreenWindows.size(); wndIndex++) {
            ShowWindow(widget->fullscreenWindows[wndIndex], SW_HIDE);
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
                SetWindowPos(target, HWND_TOPMOST, rect.left, rect.top, rect.right - rect.left,
                    rect.bottom - rect.top, SWP_NOACTIVATE | SWP_SHOWWINDOW);
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
        if (widget->config.type == WIDGET_FULLSCREEN
                && widget->config.visible
                && !widget->fullscreenPreview) {
            BringWidgetForward(widget);
        }
    }
    if (!settingsOpen && escapeTarget != nullptr) {
        SetForegroundWindowEx(escapeTarget);
        SetFocus(escapeTarget);
    }
}

/// Rebuilds widget windows after a display change while preserving alarms, then refreshes fullscreen
/// presentation.
static void RecreateAllWidgetWindows() {
    for (const std::unique_ptr<Widget>& widget : widgets) {
        if (widget->window == nullptr) {
            CreateWidgetWindow(widget.get());
        } else {
            RecreateWidgetForConfiguration(widget.get(), widget->config);
        }
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

/// Shows or hides one widget, updates fullscreen presentation and open settings as needed, and saves the
/// visibility change.
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

/// Shows or hides all widgets, remembering the previously visible set before hiding and saving the resulting
/// state.
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
                for (size_t wndIndex = 0; wndIndex < widgets[index]->fullscreenWindows.size(); wndIndex++) {
                    ShowWindow(widgets[index]->fullscreenWindows[wndIndex], SW_SHOWNOACTIVATE);
                }
            }
            RenderWidget(widgets[index].get());
            BringWidgetForward(widgets[index].get());
        } else {
            SaveWidgetPosition(widgets[index].get());
            ShowWindow(widgets[index]->window, SW_HIDE);
            for (size_t wndIndex = 0; wndIndex < widgets[index]->fullscreenWindows.size(); wndIndex++) {
                ShowWindow(widgets[index]->fullscreenWindows[wndIndex], SW_HIDE);
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
    HMONITOR anchorMonitor =
        anchor == nullptr ? nullptr : MonitorFromWindow(anchor->window, MONITOR_DEFAULTTONEAREST);
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
            groups.push_back(MonitorGroup{ monitor, std::vector<Widget*>{} });
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
            placements.push_back(WidgetPlacement{ current->config.id, rect });
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
                pending.push_back(PendingWidgetPlacement{ current, placements[index].rect });
            }
        }
    }
    if (failed) {
        return {};
    }
    return pending;
}

/// Returns menu flags for the selected grid command, reevaluating and reenabling a previously used command
/// when movement becomes possible.
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

/// Applies a planned grid arrangement, synchronizes stored positions, and records the invoked command's
/// disabled state. Reenables commands using the other grid origin so tray and widget arrangements remain
/// independent.
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
    if (std::find(disabledArrangementCommands.begin(), disabledArrangementCommands.end(), id)
            == disabledArrangementCommands.end()) {
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

/// Restores the remembered hidden widgets, or available hidden widgets when none of those remain, and brings
/// them forward. Returns false when no widgets can be restored.
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
            for (size_t wndIndex = 0; wndIndex < widget->fullscreenWindows.size(); wndIndex++) {
                ShowWindow(widget->fullscreenWindows[wndIndex], SW_SHOWNOACTIVATE);
            }
        }
        RenderWidget(widget);
        SynchronizeOpenSettings(widget, ID_MENU_VISIBLE);
        fullscreenVisibilityChanged = fullscreenVisibilityChanged
            || widget->config.type == WIDGET_FULLSCREEN;
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

/// Creates the notification-area icon with localized tooltip text and negotiates version 4 notification
/// behavior.
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

/// Applies a widget context-menu command, synchronizing settings and recreating or redrawing the widget
/// when required.
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
    } else if ((widget->config.type == WIDGET_CALENDAR || widget->config.type == WIDGET_PANEL)
            && (command == ID_MENU_WEEK_NUMBERS
                || command == ID_MENU_SUNDAY_FIRST
                || command == ID_MENU_SHOW_TODAY)) {
        recreateConfiguration = widget->config;
        if (command == ID_MENU_WEEK_NUMBERS) {
            recreateConfiguration.weekNumbers = !recreateConfiguration.weekNumbers;
        } else if (command == ID_MENU_SUNDAY_FIRST) {
            recreateConfiguration.sundayFirst = !recreateConfiguration.sundayFirst;
        } else if (widget->config.type == WIDGET_CALENDAR) {
            recreateConfiguration.showToday = !recreateConfiguration.showToday;
        } else {
            return;
        }
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
            GetWidgetDimensions(widget->config, &width, &height, &widget->panelNotices,
                widget->panelApplicationUtc);
            ResizeWidgetPreservingWorkAreaAttachment(widget, width, height,
                SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
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
        widget->config.timeSignalEnabled = !widget->config.timeSignalEnabled;
        UpdateCurrentTimeSignalMute();
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
            const int fonts[] = { 28, 44, 58, 72 };
            recreateConfiguration.fontSize = fonts[sizeIndex];
        }
        recreate = true;
    } else if (command >= ID_MENU_DATE_FORMAT_BASE
            && command < ID_MENU_DATE_FORMAT_BASE + DATE_FORMAT_COUNT) {
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

/// Handles Alt+0 through Alt+3 on analog and calendar-with-clock widgets using their existing size commands.
/// Accepts top-row and numeric-keypad digits with either Num Lock state, distinguishing dedicated navigation
/// keys. Ignores key repeats and leaves other widgets and modified key combinations to their usual handlers.
static bool HandleWidgetSizeShortcut(Widget* widget, const MSG& msg) {
    if (widget == nullptr
            || widget->config.type != WIDGET_ANALOG && widget->config.type != WIDGET_PANEL
            || msg.message != WM_SYSKEYDOWN
            || (msg.lParam & 1LL << 29) == 0
            || GetKeyState(VK_CONTROL) < 0
            || GetKeyState(VK_SHIFT) < 0) {
        return false;
    }
    int sizeIndex = -1;
    if (msg.wParam >= L'0' && msg.wParam <= L'3') {
        sizeIndex = static_cast<int>(msg.wParam - L'0');
    } else if (msg.wParam >= VK_NUMPAD0 && msg.wParam <= VK_NUMPAD3) {
        sizeIndex = static_cast<int>(msg.wParam - VK_NUMPAD0);
    } else if ((msg.lParam & 1LL << 24) == 0) {
        switch (msg.wParam) {
            case VK_INSERT:
                sizeIndex = 0;
                break;
            case VK_END:
                sizeIndex = 1;
                break;
            case VK_DOWN:
                sizeIndex = 2;
                break;
            case VK_NEXT:
                sizeIndex = 3;
                break;
        }
    }
    if (sizeIndex < 0) {
        return false;
    }
    if ((msg.lParam & 1LL << 30) == 0) {
        int command = ID_MENU_SIZE_104 + sizeIndex;
        HandleWidgetMenuCommand(widget, command);
    }
    return true;
}

/// Builds the widget's localized context menu with applicable states, displays it, and dispatches the
/// selected command.
static void ShowWidgetContextMenu(Widget* widget, HWND owner) {
    HMENU menu = CreatePopupMenu();
    std::vector<wchar_t> menuMnemonics;
    AppendMenuCommand(menu, MF_STRING, ID_MENU_VISIBLE, widget->config.visible
        ? GetLocalizedText(widget->config.language, TXT_HIDE_WIDGET_LABEL)
        : GetLocalizedText(widget->config.language, TXT_SHOW_WIDGET_LABEL), &menuMnemonics);
    if (widget->config.type != WIDGET_FULLSCREEN) {
        AppendMenuCommand(menu, MF_STRING | (widget->config.topMost ? MF_CHECKED : 0), ID_MENU_TOPMOST,
            WT(widget, TXT_TOPMOST), &menuMnemonics);
    }
    if (widget->config.type == WIDGET_CALENDAR) {
        AppendMenuCommand(menu, MF_STRING, ID_MENU_TODAY,
            GetLocalizedText(widget->config.language, TXT_PANEL_TODAY_TOOLTIP), &menuMnemonics);
    }
    if (widget->config.type != WIDGET_CALENDAR) {
        bool secondsAvailable = widget->config.type != WIDGET_ANALOG
            || AnalogClockSupportsSeconds(widget->config.size);
        UINT secondsFlags = MF_STRING | (widget->config.showSeconds && secondsAvailable ? MF_CHECKED : 0);
        if (!secondsAvailable) {
            secondsFlags |= MF_GRAYED;
        }
        AppendMenuCommand(menu, secondsFlags, ID_MENU_SECONDS, WT(widget, TXT_SECONDS), &menuMnemonics);
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
            AppendMenuCommand(dateMenu, MF_STRING, ID_MENU_DATE_FORMAT_BASE + index, label.c_str(),
                &dateMenuMnemonics);
        }
        CheckMenuRadioItem(dateMenu, ID_MENU_DATE_FORMAT_BASE,
            ID_MENU_DATE_FORMAT_BASE + DATE_FORMAT_COUNT - 1,
            ID_MENU_DATE_FORMAT_BASE + widget->config.dateCopyFormat, MF_BYCOMMAND);
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        if (widget->config.type == WIDGET_CALENDAR) {
            AppendMenuCommand(menu, MF_STRING | (widget->config.showToday ? MF_CHECKED : 0),
                ID_MENU_SHOW_TODAY, GetLocalizedText(widget->config.language, TXT_SHOW_TODAY_LABEL),
                &menuMnemonics);
        }
        AppendMenuCommand(menu, MF_STRING | (widget->config.weekNumbers ? MF_CHECKED : 0),
            ID_MENU_WEEK_NUMBERS, WT(widget, TXT_WEEK_NUMBERS), &menuMnemonics);
        AppendMenuCommand(menu, MF_STRING | (widget->config.sundayFirst ? MF_CHECKED : 0),
            ID_MENU_SUNDAY_FIRST, WT(widget, TXT_SUNDAY_FIRST), &menuMnemonics);
        AppendMenuCommand(menu, MF_POPUP, reinterpret_cast<UINT_PTR>(dateMenu),
            GetLocalizedText(widget->config.language, TXT_DATE_COPY_LABEL), &menuMnemonics);
    }
    if (WidgetSupportsSound(widget->config.type)) {
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        UINT alarmFlags = MF_STRING | (widget->config.alarmEnabled ? MF_CHECKED : 0);
        std::wstring alarmLabel = AlarmMenuLabel(widget->config);
        AppendMenuCommand(menu, alarmFlags, ID_MENU_ALARM_ENABLED, alarmLabel.c_str(), &menuMnemonics);
        std::wstring signalLabel = TimeSignalMenuLabel(widget->config);
        AppendMenuCommand(menu, MF_STRING | (widget->config.timeSignalEnabled ? MF_CHECKED : 0),
            ID_MENU_TIME_SIGNAL_ENABLED, signalLabel.c_str(), &menuMnemonics);
        AppendMenuCommand(menu, MF_STRING | (widget->config.soundsMuted ? MF_CHECKED : 0), ID_MENU_MUTE,
            GetLocalizedText(widget->config.language, TXT_MUTE_LABEL), &menuMnemonics);
    }
    if (widget->config.type == WIDGET_ANALOG || widget->config.type == WIDGET_PANEL) {
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        int sizes[4] = {};
        int sizeCount = GetAnalogClockSizes(sizes);
        UINT selectedSizeCommand = 0;
        for (int index = 0; index < sizeCount; index++) {
            std::wstring label = WT(widget, TXT_SIZE);
            label += L" ";
            label += std::to_wstring(sizes[index]);
            AppendMenuCommand(menu, MF_STRING, ID_MENU_SIZE_104 + index, label.c_str(), &menuMnemonics);
            if (widget->config.size == sizes[index]) {
                selectedSizeCommand = ID_MENU_SIZE_104 + index;
            }
        }
        CheckMenuRadioItem(menu, ID_MENU_SIZE_104, ID_MENU_SIZE_104 + sizeCount - 1, selectedSizeCommand,
            MF_BYCOMMAND);
    }
    if (widget->alarmActive) {
        AppendMenuCommand(menu, MF_STRING, ID_MENU_STOP_ALARM, WT(widget, TXT_STOP_ALARM), &menuMnemonics);
    }
    if (widget->config.type != WIDGET_FULLSCREEN) {
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        UINT arrangeFlags = WidgetArrangementMenuFlags(widget);
        AppendMenuCommand(menu, arrangeFlags, ID_MENU_ARRANGE_WIDGETS,
            GetLocalizedText(widget->config.language, TXT_ARRANGE_WIDGET_LABEL),
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
    int selectedSize = NormalizeAnalogClockSize(clock.size);
    UINT selectedSizeCommand = 0;
    for (int item = 0; item < count; item++) {
        std::wstring label = std::wstring(WT(widget, TXT_SIZE)) + L" " + std::to_wstring(sizes[item]);
        AppendMenuCommand(menu, MF_STRING, ID_MENU_SIZE_104 + item, label.c_str(), &mnemonics);
        if (selectedSize == sizes[item]) {
            selectedSizeCommand = ID_MENU_SIZE_104 + item;
        }
    }
    CheckMenuRadioItem(menu, ID_MENU_SIZE_104, ID_MENU_SIZE_104 + count - 1, selectedSizeCommand,
        MF_BYCOMMAND);
    return menu;
}

/// Applies a valid size command to one additional panel clock, recreates the panel as needed, and
/// synchronizes and saves settings.
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

/// Displays a size-only menu at the supplied screen point and dispatches the selected additional-clock
/// command.
static void ShowAdditionalClockContextMenu(Widget* widget, int index, POINT point) {
    HMENU menu = CreateAdditionalClockMenu(widget, index);
    SetForegroundWindow(widget->window);
    int command =
        TrackPopupMenu(menu, TPM_RETURNCMD | TPM_RIGHTBUTTON, point.x, point.y, 0, widget->window, nullptr);
    DestroyMenu(menu);
    if (command != 0) {
        HandleAdditionalClockMenuCommand(widget, index, command);
    }
}

/// Builds and displays the tray menu for widget visibility, shared actions, and application commands,
/// then dispatches the selection.
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
    AppendMenuCommand(menu, muteFlags, ID_MENU_MUTE, T(TXT_MUTE_ALL_LABEL), &menuMnemonics);
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    UINT arrangeFlags = WidgetArrangementMenuFlags(nullptr);
    AppendMenuCommand(menu, arrangeFlags, ID_MENU_ARRANGE_WIDGETS, T(TXT_ARRANGE_WIDGET_LABEL),
        &menuMnemonics);
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendApplicationMenuCommands(menu, appLanguage, &menuMnemonics);
    POINT point = {};
    GetCursorPos(&point);
    SetForegroundWindow(hController);
    int command =
        TrackPopupMenu(menu, TPM_RETURNCMD | TPM_RIGHTBUTTON, point.x, point.y, 0, hController, nullptr);
    DestroyMenu(menu);
    if (command >= ID_MENU_WIDGET_BASE && command < ID_MENU_WIDGET_BASE + static_cast<int>(widgets.size())) {
        SetWidgetVisible(widgets[command - ID_MENU_WIDGET_BASE].get(),
            !widgets[command - ID_MENU_WIDGET_BASE]->config.visible);
    } else {
        SendMessageW(hController, WM_COMMAND, command, 0);
    }
}

/// Prefixes the localized common caption with a mnemonic marker.
std::wstring Mnemonic(TextId id) {
    return std::wstring(L"&") + T(id);
}

/// Classifies a settings child as a foreground control, checkbox, or background label for clipping and hit
/// testing.
static SettingsControlLayer GetSettingsControlLayer(HWND control) {
    if (GetPropW(control, SETTINGS_COLOR_BUTTON_PROPERTY) != nullptr) {
        return SETTINGS_CONTROL_FOREGROUND;
    }
    wchar_t className[32] = {};
    GetClassNameW(control, className, ARRAYSIZE(className));
    if (_wcsicmp(className, L"STATIC") == 0) {
        return SETTINGS_CONTROL_LABEL;
    }
    if (_wcsicmp(className, L"BUTTON") == 0) {
        LONG_PTR style = GetWindowLongPtrW(control, GWL_STYLE);
        UINT type = static_cast<UINT>(style & BS_TYPEMASK);
        if (type == BS_CHECKBOX
                || type == BS_AUTOCHECKBOX
                || type == BS_3STATE
                || type == BS_AUTO3STATE
                || type == BS_RADIOBUTTON
                || type == BS_AUTORADIOBUTTON) {
            return SETTINGS_CONTROL_CHECKBOX;
        }
    }
    return SETTINGS_CONTROL_FOREGROUND;
}

/// Returns a pending visibility state, resolving color previews to their associated button.
static bool IsSettingsControlApplicable(HWND control, const std::vector<ControlVisibility>& visibility) {
    HWND button = reinterpret_cast<HWND>(GetPropW(control, SETTINGS_COLOR_BUTTON_PROPERTY));
    if (button != nullptr) {
        control = button;
    }
    for (const ControlVisibility& state : visibility) {
        if (SettingsEdit::GetFrame(state.control) == control) {
            return state.visible;
        }
    }
    return true;
}

/// Keeps foreground controls above text, with incoming controls above outgoing peers during replacement.
/// Preserves leading-zero and sound-field priority and keeps the border slider beneath other foreground
/// controls.
static bool SettingsControlIsAbove(const PositionedControl& left, const PositionedControl& right,
        const std::vector<ControlVisibility>* visibility) {
    SettingsControlLayer leftLayer = GetSettingsControlLayer(left.window);
    SettingsControlLayer rightLayer = GetSettingsControlLayer(right.window);
    if (leftLayer != rightLayer) {
        return leftLayer < rightLayer;
    }
    if (visibility != nullptr) {
        bool leftVisible = IsSettingsControlApplicable(left.window, *visibility);
        bool rightVisible = IsSettingsControlApplicable(right.window, *visibility);
        if (leftVisible != rightVisible) {
            return leftVisible;
        }
    }
    if (left.window == hLeadingZeroCombo) {
        return right.window != hLeadingZeroCombo;
    }
    if (right.window == hLeadingZeroCombo) {
        return false;
    }
    bool leftSoundField = left.window == hTimeSignalSoundCombo || left.window == hTimeSignalTestButton;
    bool rightSoundField = right.window == hTimeSignalSoundCombo || right.window == hTimeSignalTestButton;
    if (leftSoundField != rightSoundField) {
        return leftSoundField;
    }
    if (leftSoundField) {
        return left.window == hTimeSignalSoundCombo && right.window != hTimeSignalSoundCombo;
    }
    if (left.window == hTimeSignalVolumeTrackBar) {
        return right.window != hTimeSignalVolumeTrackBar;
    }
    if (right.window == hTimeSignalVolumeTrackBar) {
        return false;
    }
    if (leftLayer == SETTINGS_CONTROL_FOREGROUND) {
        return left.window != hBorderTrackBar && right.window == hBorderTrackBar;
    }
    return left.rect.left == right.rect.left
        ? left.rect.top < right.rect.top
        : left.rect.left > right.rect.left;
}

/// Binds a localized label from its native dialog resource and records its field association.
static HWND BindSettingsLabel(HWND parent, int id, const wchar_t* text, std::vector<HWND>* group = nullptr) {
    HWND control = GetDlgItem(parent, id);
    if (control != nullptr) {
        SetWindowTextW(control, text);
        SetPropW(control, SETTINGS_FIELD_LABEL_PROPERTY, reinterpret_cast<HANDLE>(static_cast<INT_PTR>(1)));
    }
    if (group != nullptr) {
        group->push_back(control);
    }
    return control;
}

/// Binds a resource control, retaining native dialog geometry and installing existing edit and navigation
/// handlers.
static HWND BindSettingsControl(HWND parent, int id, const wchar_t* text,
        std::vector<HWND>* group = nullptr, HWND fieldLabel = nullptr) {
    HWND control = GetDlgItem(parent, id);
    wchar_t className[32] = {};
    GetClassNameW(control, className, ARRAYSIZE(className));
    LONG_PTR style = GetWindowLongPtrW(control, GWL_STYLE);
    bool singleLineEdit = _wcsicmp(className, L"EDIT") == 0 && (style & ES_MULTILINE) == 0;
    bool nativeCombo = _wcsicmp(className, WC_COMBOBOXEXW) == 0;
    if (control != nullptr && singleLineEdit) {
        RECT bounds = {};
        GetWindowRect(control, &bounds);
        MapWindowPoints(HWND_DESKTOP, parent, reinterpret_cast<POINT*>(&bounds), 2);
        DWORD extended = static_cast<DWORD>(GetWindowLongPtrW(control, GWL_EXSTYLE));
        HWND previous = GetWindow(control, GW_HWNDPREV);
        DestroyWindow(control);
        control = SettingsEdit::Create(hInstance, parent, extended, static_cast<DWORD>(style), text,
            bounds.left, bounds.top, bounds.right - bounds.left, bounds.bottom - bounds.top, id);
        SetWindowPos(SettingsEdit::GetFrame(control), previous == nullptr ? HWND_TOP : previous, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    } else if (control != nullptr) {
        SetWindowTextW(control, text);
    }
    if (control != nullptr && nativeCombo) {
        if (!SetWindowSubclass(control, SettingsControlSubclassProc, SETTINGS_CONTROL_SUBCLASS_ID, 0)) {
            DestroyWindow(control);
            control = nullptr;
        }
    }
    if (control != nullptr && _wcsicmp(className, L"EDIT") == 0) {
        if (!InstallSelectionEditHandler(control)) {
            DestroyWindow(SettingsEdit::GetFrame(control));
            control = nullptr;
        } else if (singleLineEdit) {
            SetWindowSubclass(control, SettingsControlSubclassProc, SETTINGS_CONTROL_SUBCLASS_ID, 0);
        }
    } else if (control != nullptr && (id == ID_LIST_WIDGETS || id == ID_REMOVE || id == ID_DUPLICATE)) {
        SetWindowSubclass(control, WidgetListSubclassProc, static_cast<UINT_PTR>(id), 0);
    }
    if (control != nullptr) {
        if (fieldLabel != nullptr) {
            SetPropW(fieldLabel, SETTINGS_FIELD_LABEL_PROPERTY, control);
        }
        if (_wcsicmp(className, L"LISTBOX") == 0 || _wcsicmp(className, WC_LISTVIEWW) == 0) {
            SetWindowSubclass(control, SettingsListBorderSubclassProc, SETTINGS_LIST_BORDER_SUBCLASS_ID, 0);
        }
        UpdateSettingsFieldMetrics(control, 0);
    }
    if (group != nullptr) {
        group->push_back(control);
    }
    return control;
}

/// Associates the native resource preview with its color button and existing theme rendering.
static void AddSettingsColorPreview(HWND button) {
    HWND preview = button == nullptr
        ? nullptr
        : GetDlgItem(GetParent(button), IDC_COLOR_PREVIEW_BASE + GetDlgCtrlID(button));
    if (preview != nullptr
        && (!SetPropW(button, SETTINGS_COLOR_PREVIEW_PROPERTY, preview)
            || !SetPropW(preview, SETTINGS_COLOR_BUTTON_PROPERTY, button)
            || !SetWindowSubclass(preview, SettingsColorPreviewSubclassProc,
                SETTINGS_CONTROL_SUBCLASS_ID, 0))) {
        RemovePropW(button, SETTINGS_COLOR_PREVIEW_PROPERTY);
        DestroyWindow(preview);
        preview = nullptr;
    }
    appearanceControls.push_back(preview);
}

/// Creates a tooltip attached to a control, destroying it if registration fails.
/// The supplied text must remain valid while the tooltip uses it.
HWND CreateControlTooltip(HWND parent, HWND control, const wchar_t* text) {
    if (parent == nullptr || control == nullptr || text == nullptr) {
        return nullptr;
    }
    HWND tooltip = CreateWindowExW(WS_EX_TOPMOST | WS_EX_NOACTIVATE, TOOLTIPS_CLASSW, nullptr,
        WS_POPUP | TTS_ALWAYSTIP | TTS_NOPREFIX, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        parent, nullptr, hInstance, nullptr);
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

/// Calculates a nonresizable settings window that fits the work area and adds scrollbars when its content
/// cannot fit.
static void GetSettingsWindowLayout(DWORD extendedStyle, DWORD* style, int* width, int* height,
        RECT* availableArea = nullptr) {
    DWORD baseStyle =
        static_cast<DWORD>(GetWindowLongPtrW(hSettings, GWL_STYLE)) & ~(WS_VISIBLE | WS_HSCROLL | WS_VSCROLL);
    RECT frame = {};
    AdjustWindowRectEx(&frame, baseStyle, FALSE, extendedStyle);
    int desiredWidth = settingsContentWidth + frame.right - frame.left;
    int desiredHeight = settingsContentHeight + frame.bottom - frame.top;
    const PersistWindowStateData& placement = settingsWindowState.GetState();
    int settingsX = placement.x;
    int settingsY = placement.y;
    RECT desired = { settingsX, settingsY, settingsX + desiredWidth, settingsY + desiredHeight };
    HMONITOR monitor = settingsX == CW_USEDEFAULT || settingsY == CW_USEDEFAULT
        ? MonitorFromPoint(POINT{}, MONITOR_DEFAULTTOPRIMARY)
        : MonitorFromRect(&desired, MONITOR_DEFAULTTONEAREST);
    MONITORINFO information = {};
    information.cbSize = sizeof(information);
    RECT workArea = { 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
    if (monitor != nullptr && GetMonitorInfoW(monitor, &information)) {
        workArea = information.rcWork;
    }
    if (availableArea != nullptr) {
        *availableArea = workArea;
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

/// Matches the font chooser's vertical bounds to the aligned Default button without changing its width.
static void AlignApplicationFontButton() {
    RECT bounds = {};
    RECT reference = {};
    if (!GetWindowRect(hAppFontButton, &bounds) || !GetWindowRect(hAppFontDefaultButton, &reference)) {
        return;
    }
    MapWindowPoints(HWND_DESKTOP, hApplicationPage, reinterpret_cast<POINT*>(&bounds), 2);
    MapWindowPoints(HWND_DESKTOP, hApplicationPage, reinterpret_cast<POINT*>(&reference), 2);
    SetControlPosition(hAppFontButton, bounds.left, reference.top, bounds.right - bounds.left,
        reference.bottom - reference.top);
}

/// Fits Settings to its content and available work area, retaining the authored gap below the bottom action
/// buttons. Updates scrollbars, preserves valid scroll positions, and skips minimized windows without
/// activating them.
static void UpdateSettingsWindowLayout() {
    if (hSettings == nullptr || settingsContentWidth <= 0 || settingsLayoutSuspended || IsIconic(hSettings)) {
        return;
    }
    DWORD currentStyle = static_cast<DWORD>(GetWindowLongPtrW(hSettings, GWL_STYLE));
    int previousX = (currentStyle & WS_HSCROLL) != 0 ? GetScrollPos(hSettings, SB_HORZ) : 0;
    int previousY = (currentStyle & WS_VSCROLL) != 0 ? GetScrollPos(hSettings, SB_VERT) : 0;
    RECT gap = GetSettingsResourceRect(hSettings, IDC_SETTINGS_BOTTOM_GAP);
    const int buttonIds[] = { ID_IMPORT_SETTINGS, ID_EXPORT_SETTINGS, ID_SAVE, ID_CANCEL, ID_APPLY };
    LONG bottom = 0;
    for (int id : buttonIds) {
        bottom = std::max(bottom, GetSettingsResourceRect(hSettings, id).bottom);
    }
    settingsContentHeight = bottom + previousY + gap.bottom - gap.top;
    DWORD extendedStyle = static_cast<DWORD>(GetWindowLongPtrW(hSettings, GWL_EXSTYLE));
    DWORD style = 0;
    int width = 0;
    int height = 0;
    RECT availableArea = {};
    GetSettingsWindowLayout(extendedStyle, &style, &width, &height, &availableArea);
    style |= currentStyle & WS_VISIBLE;
    RECT bounds = {};
    if (!GetWindowRect(hSettings, &bounds)) {
        return;
    }
    LONG x = std::clamp(bounds.left, availableArea.left, availableArea.right - width);
    LONG y = std::clamp(bounds.top, availableArea.top, availableArea.bottom - height);
    UINT flags = SWP_NOZORDER | SWP_NOACTIVATE;
    if (bounds.left == x && bounds.top == y) {
        flags |= SWP_NOMOVE;
    }
    if (style != currentStyle) {
        SetWindowLongPtrW(hSettings, GWL_STYLE, style);
        flags |= SWP_FRAMECHANGED;
    }
    bool changed = style != currentStyle
        || bounds.left != x
        || bounds.top != y
        || bounds.right - bounds.left != width
        || bounds.bottom - bounds.top != height;
    if (changed) {
        SetWindowPos(hSettings, nullptr, x, y, width, height, flags);
    }
    InitializeSettingsScrollBars();
    SCROLLINFO position = { sizeof(position), SIF_POS };
    int currentX = 0;
    int currentY = 0;
    if ((style & WS_HSCROLL) != 0) {
        position.nPos = previousX;
        SetScrollInfo(hSettings, SB_HORZ, &position, TRUE);
        currentX = GetScrollPos(hSettings, SB_HORZ);
    }
    if ((style & WS_VSCROLL) != 0) {
        position.nPos = previousY;
        SetScrollInfo(hSettings, SB_VERT, &position, TRUE);
        currentY = GetScrollPos(hSettings, SB_VERT);
    }
    int deltaX = previousX - currentX;
    int deltaY = previousY - currentY;
    if (deltaX != 0 || deltaY != 0) {
        ScrollWindowEx(hSettings, deltaX, deltaY, nullptr, nullptr, nullptr, nullptr,
            SW_SCROLLCHILDREN | SW_INVALIDATE | SW_ERASE);
    }
    if (changed) {
        RedrawWindow(hSettings, nullptr, nullptr,
            RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN | RDW_UPDATENOW);
    }
    PostMessageW(hSettings, WM_ALIGN_SETTINGS_FONT_BUTTON, 0, 0);
}

/// Applies a scrollbar request within its valid range and scrolls the settings child windows by the resulting
/// delta.
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

/// Scrolls overflowing tab headers under the pointer by one tab per wheel message, without changing selection
/// or focus. Uses the native scroll-button bounds and handles wheel input only while the scroll buttons are
/// visible. Includes transparent header gaps where native hit testing returns the settings window.
static bool ScrollSettingsTabHeaders(WPARAM wParam, LPARAM lParam) {
    int delta = GET_WHEEL_DELTA_WPARAM(wParam);
    if (delta == 0
            || hSettings == nullptr
            || hTabs == nullptr
            || GetActiveWindow() != hSettings
            || !IsWindowEnabled(hSettings)
            || !IsWindowVisible(hTabs)) {
        return false;
    }
    int count = TabCtrl_GetItemCount(hTabs);
    RECT header = {};
    RECT client = {};
    if (count <= 0 || !TabCtrl_GetItemRect(hTabs, 0, &header) || !GetClientRect(hTabs, &client)) {
        return false;
    }
    POINT point = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
    HWND hovered = WindowFromPoint(point);
    if (hovered != hTabs && hovered != hSettings && !IsChild(hTabs, hovered)) {
        return false;
    }
    ScreenToClient(hTabs, &point);
    header.left = client.left;
    header.right = client.right;
    if (!PtInRect(&header, point)) {
        return false;
    }
    HWND scrollButtons = FindWindowExW(hTabs, nullptr, UPDOWN_CLASSW, nullptr);
    if (scrollButtons == nullptr || !IsWindowVisible(scrollButtons)) {
        return false;
    }
    RECT last = {};
    RECT buttons = {};
    if (!TabCtrl_GetItemRect(hTabs, count - 1, &last) || !GetWindowRect(scrollButtons, &buttons)) {
        return true;
    }
    MapWindowPoints(HWND_DESKTOP, hTabs, reinterpret_cast<POINT*>(&buttons), 2);
    if (delta < 0 && last.right <= buttons.left) {
        return true;
    }
    int firstVisible = 0;
    for (int index = 0; index < count; index++) {
        RECT item = {};
        if (!TabCtrl_GetItemRect(hTabs, index, &item)) {
            return true;
        }
        if (item.left >= 0) {
            firstVisible = index;
            break;
        }
    }
    int direction = delta > 0 ? -1 : 1;
    int position = std::clamp(firstVisible + direction, 0, count - 1);
    SendMessageW(hTabs, WM_HSCROLL, MAKEWPARAM(SB_THUMBPOSITION, position), 0);
    SendMessageW(hTabs, WM_HSCROLL, MAKEWPARAM(SB_ENDSCROLL, position), 0);
    return true;
}

/// Translates wheel input into three line-scroll steps per notch, using horizontal scrolling with Shift when
/// available.
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

/// Moves or resizes a control only when necessary, retaining combo height and extending settings text
/// controls to the common right edge.
static void SetControlPosition(HWND control, int x, int y, int width, int height) {
    if (control == nullptr) {
        return;
    }
    control = SettingsEdit::GetFrame(control);
    HWND parent = GetParent(control);
    wchar_t className[32] = {};
    GetClassNameW(control, className, ARRAYSIZE(className));
    bool combo = _wcsicmp(className, WC_COMBOBOXW) == 0 || _wcsicmp(className, WC_COMBOBOXEXW) == 0;
    HWND nativeCombo = combo ? GetSettingsComboBox(control) : control;
    if (nativeCombo != control) {
        RECT field = {};
        if (GetWindowRect(nativeCombo, &field)) {
            height = field.bottom - field.top;
        }
    }
    bool settingsField = parent == hSettings || IsSettingsPageWindow(parent);
    if (settingsField
        && (GetPropW(control, SETTINGS_FIELD_LABEL_PROPERTY) != nullptr
            || _wcsicmp(className, L"EDIT") == 0
            && (GetWindowLongPtrW(control, GWL_STYLE) & ES_MULTILINE) == 0)) {
        height = std::min(height, SettingsDialogHeight(11));
    }
    if (GetPropW(control, SETTINGS_FIELD_LABEL_PROPERTY) != nullptr) {
        TEXTMETRICW metrics = {};
        if (GetSettingsTextMetrics(control, &metrics)) {
            height = std::min(metrics.tmHeight, static_cast<LONG>(SettingsDialogHeight(11)));
        }
    }
    RECT current = {};
    UINT flags = SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS;
    if (GetWindowRect(control, &current)) {
        MapWindowPoints(HWND_DESKTOP, GetParent(control), reinterpret_cast<POINT*>(&current), 2);
        LONG_PTR currentHeight = current.bottom - current.top;
        if (current.left == x && current.top == y) {
            flags |= SWP_NOMOVE;
        }
        if (current.right - current.left == width && currentHeight == height) {
            flags |= SWP_NOSIZE;
        }
    }
    if ((flags & (SWP_NOMOVE | SWP_NOSIZE)) != (SWP_NOMOVE | SWP_NOSIZE)) {
        SetWindowPos(control, nullptr, x, y, width, height, flags);
    }
    if (settingsField && combo) {
        UpdateSettingsComboMetrics(control);
    }
    HWND edit = SettingsEdit::GetEdit(control);
    if (edit != nullptr) {
        UpdateEditMetrics(edit);
    }
}

/// Positions a color button and its square preview using the native dialog button height.
static void SetSettingsColorControlPosition(HWND button, int x, int width, int gap) {
    RECT bounds = {};
    if (button == nullptr || !GetWindowRect(button, &bounds)) {
        return;
    }
    MapWindowPoints(HWND_DESKTOP, GetParent(button), reinterpret_cast<POINT*>(&bounds), 2);
    SetControlPosition(button, x, bounds.top, width, bounds.bottom - bounds.top);
    HWND preview = reinterpret_cast<HWND>(GetPropW(button, SETTINGS_COLOR_PREVIEW_PROPERTY));
    int height = bounds.bottom - bounds.top;
    SetControlPosition(preview, x + width + gap, bounds.top, height, height);
}

/// Aligns Appearance fields and buttons to a common width and reserves border-slider space.
static void UpdateSettingsColorControlLayout() {
    RECT save = {};
    RECT cancel = {};
    if (!GetWindowRect(GetDlgItem(hSettings, ID_SAVE), &save)
            || !GetWindowRect(GetDlgItem(hSettings, ID_CANCEL), &cancel)) {
        return;
    }
    int gap = cancel.left - save.right;
    RECT content = GetSettingsResourceRect(hAppearancePage, IDC_SETTINGS_CONTENT);
    int left = content.left;
    int right = content.right;
    int columnGap = SettingsDialogWidth(5);
    int columnWidth = (right - left - columnGap) / 2;
    RECT referenceButton = GetSettingsResourceRect(hAppearancePage, ID_TEXT_COLOR);
    int buttonWidth = columnWidth - gap - (referenceButton.bottom - referenceButton.top);
    int secondColumn = right - columnWidth;
    const HWND leftButtons[] = { hTextColorButton, hAlarmTextColorButton };
    const HWND rightButtons[] = { hBackgroundColorButton, hAlarmBackgroundColorButton, hBorderColorButton };
    for (HWND button : leftButtons) {
        SetSettingsColorControlPosition(button, left, buttonWidth, gap);
    }
    for (HWND button : rightButtons) {
        SetSettingsColorControlPosition(button, secondColumn, buttonWidth, gap);
    }
    const HWND fontButtons[] = {
        hPanelTopFontButton,
        hPanelTimeFontButton,
        hPanelBottomFontButton,
        hFontButton
    };
    for (HWND button : fontButtons) {
        RECT bounds = {};
        if (GetWindowRect(button, &bounds)) {
            MapWindowPoints(HWND_DESKTOP, GetParent(button),
                reinterpret_cast<POINT*>(&bounds), 2);
            SetControlPosition(button, secondColumn, bounds.top, buttonWidth, bounds.bottom - bounds.top);
        }
    }
    RECT antialias = {};
    if (GetWindowRect(hWidgetAntialiasCombo, &antialias)) {
        MapWindowPoints(HWND_DESKTOP, GetParent(hWidgetAntialiasCombo),
            reinterpret_cast<POINT*>(&antialias), 2);
        SetControlPosition(hWidgetAntialiasCombo, secondColumn, antialias.top, buttonWidth,
            antialias.bottom - antialias.top);
    }
    RECT dateFormat = {};
    if (GetWindowRect(hDateFormatCombo, &dateFormat)) {
        MapWindowPoints(HWND_DESKTOP, GetParent(hDateFormatCombo),
            reinterpret_cast<POINT*>(&dateFormat), 2);
        SetControlPosition(hDateFormatCombo, secondColumn, dateFormat.top, buttonWidth,
            dateFormat.bottom - dateFormat.top);
    }
    RECT leadingZero = {};
    if (GetWindowRect(hLeadingZeroCombo, &leadingZero)) {
        MapWindowPoints(HWND_DESKTOP, GetParent(hLeadingZeroCombo),
            reinterpret_cast<POINT*>(&leadingZero), 2);
        SetControlPosition(hLeadingZeroCombo, secondColumn, leadingZero.top, buttonWidth,
            leadingZero.bottom - leadingZero.top);
    }
    RECT size = {};
    if (selectedDraftIndex >= 0
            && selectedDraftIndex < static_cast<int>(settingsDraft.size())
            && settingsDraft[selectedDraftIndex].type == WIDGET_ANALOG
            && GetWindowRect(hSizeCombo, &size)) {
        MapWindowPoints(HWND_DESKTOP, GetParent(hSizeCombo),
            reinterpret_cast<POINT*>(&size), 2);
        if (size.left != secondColumn) {
            SetWindowPos(hSizeCombo, nullptr, secondColumn, size.top, 0, 0,
                SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
        }
    }
    RECT firstAdditionalSize = {};
    RECT lastAdditionalSize = {};
    if (selectedDraftIndex >= 0
            && selectedDraftIndex < static_cast<int>(settingsDraft.size())
            && settingsDraft[selectedDraftIndex].type == WIDGET_PANEL
            && GetWindowRect(hAdditionalSizeCombos[0], &firstAdditionalSize)
            && GetWindowRect(hAdditionalSizeCombos[1], &lastAdditionalSize)) {
        LONG spacing = lastAdditionalSize.left - firstAdditionalSize.left;
        LONG groupLeft =
            right - (lastAdditionalSize.right - lastAdditionalSize.left) - ADDITIONAL_CLOCK_COUNT * spacing;
        const HWND sizeCombos[] = { hSizeCombo, hAdditionalSizeCombos[0], hAdditionalSizeCombos[1] };
        for (int index = 0; index < ARRAYSIZE(sizeCombos); index++) {
            RECT bounds = {};
            if (GetWindowRect(sizeCombos[index], &bounds)) {
                MapWindowPoints(HWND_DESKTOP, GetParent(sizeCombos[index]),
                    reinterpret_cast<POINT*>(&bounds), 2);
                SetControlPosition(sizeCombos[index], groupLeft + index * spacing, bounds.top,
                    bounds.right - bounds.left, bounds.bottom - bounds.top);
            }
        }
    }
    RECT defaults = {};
    if (hDefaultAppearanceButton != nullptr && GetWindowRect(hDefaultAppearanceButton, &defaults)) {
        MapWindowPoints(HWND_DESKTOP, GetParent(hDefaultAppearanceButton),
            reinterpret_cast<POINT*>(&defaults), 2);
        SetControlPosition(hDefaultAppearanceButton, secondColumn, defaults.top, buttonWidth,
            defaults.bottom - defaults.top);
    }
    RECT border = {};
    if (hBorderTrackBar != nullptr && GetWindowRect(hBorderTrackBar, &border)) {
        MapWindowPoints(HWND_DESKTOP, GetParent(hBorderTrackBar),
            reinterpret_cast<POINT*>(&border), 2);
        int width = SettingsDialogWidth(60);
        int x = secondColumn - columnGap - width + SettingsDialogWidth(2);
        SetControlPosition(hBorderTrackBar, x, border.top, width, border.bottom - border.top);
    }
}

/// Positions a variant field using an authored rectangle from its page's native resource.
static void SetSettingsControlPosition(HWND control, int layoutId, int offsetY = 0) {
    RECT bounds = GetSettingsResourceRect(hAppearancePage, layoutId);
    SetControlPosition(control, bounds.left, bounds.top + offsetY, bounds.right - bounds.left,
        bounds.bottom - bounds.top);
}

/// Returns the larger of the minimum pixel width and the native ideal button width. If native measurement
/// is unavailable, measures the caption with its current font and includes the larger of the requested total
/// DLU padding and native text margins, plus the border edges.
static LONG PreferredButtonWidth(HWND button, LONG minimum, int paddingDlu) {
    SIZE ideal = {};
    if (!SendMessageW(button, BCM_GETIDEALSIZE, 0, reinterpret_cast<LPARAM>(&ideal))) {
        HFONT font = reinterpret_cast<HFONT>(SendMessageW(button, WM_GETFONT, 0, 0));
        SIZE units = {};
        HDC dc = GetDC(button);
        if (dc != nullptr) {
            HGDIOBJ previous = font == nullptr ? nullptr : SelectObject(dc, font);
            std::wstring text = GetControlText(button);
            RECT measured = {};
            if (GetDialogFontBaseUnits(font, &units)) {
                DrawTextW(dc, text.c_str(), static_cast<int>(text.size()), &measured,
                    DT_CALCRECT | DT_SINGLELINE);
                RECT margins = {};
                SendMessageW(button, BCM_GETTEXTMARGIN, 0, reinterpret_cast<LPARAM>(&margins));
                LONG padding = std::max(static_cast<LONG>(MulDiv(paddingDlu, units.cx, 4)),
                    margins.left + margins.right);
                ideal.cx = measured.right + padding + 2 * GetSystemMetrics(SM_CXEDGE);
            }
            if (previous != nullptr && previous != HGDI_ERROR) {
                SelectObject(dc, previous);
            }
            ReleaseDC(button, dc);
        }
    }
    return std::max(minimum, ideal.cx);
}

/// Fits an NTP action button to its caption with eight DLU text margins on each side and the standard minimum
/// width. Preserves its top and height, retaining its left edge or aligning its right edge to the page
/// content boundary.
static void FitSettingsButtonWidth(HWND button, bool alignRight) {
    HFONT font = reinterpret_cast<HFONT>(SendMessageW(button, WM_GETFONT, 0, 0));
    SIZE units = {};
    RECT bounds = {};
    if (!GetDialogFontBaseUnits(font, &units) || !GetWindowRect(button, &bounds)) {
        return;
    }
    HWND parent = GetParent(button);
    MapWindowPoints(HWND_DESKTOP, parent, reinterpret_cast<POINT*>(&bounds), 2);
    RECT margins = {};
    SendMessageW(button, BCM_GETTEXTMARGIN, 0, reinterpret_cast<LPARAM>(&margins));
    margins.left = MulDiv(8, units.cx, 4);
    margins.right = margins.left;
    SendMessageW(button, BCM_SETTEXTMARGIN, 0, reinterpret_cast<LPARAM>(&margins));
    int width = PreferredButtonWidth(button, MulDiv(DIALOG_BUTTON_WIDTH_DLU, units.cx, 4));
    int left = bounds.left;
    if (alignRight) {
        left = GetSettingsResourceRect(parent, IDC_SETTINGS_CONTENT).right - width;
    }
    SetControlPosition(button, left, bounds.top, width, bounds.bottom - bounds.top);
}

/// Sizes action buttons uniformly and shortens the widget-type combo while retaining its left edge.
static void UpdateSettingsActionButtonWidths() {
    const int footerButtonCount = 3;
    const HWND buttons[] = {
        GetDlgItem(hSettings, ID_SAVE),
        GetDlgItem(hSettings, ID_CANCEL),
        GetDlgItem(hSettings, ID_APPLY),
        GetDlgItem(hSettings, ID_ADD)
    };
    RECT bounds[ARRAYSIZE(buttons)] = {};
    HFONT font = reinterpret_cast<HFONT>(SendMessageW(buttons[0], WM_GETFONT, 0, 0));
    SIZE units = {};
    if (!GetDialogFontBaseUnits(font, &units)) {
        return;
    }
    int width = MulDiv(DIALOG_BUTTON_WIDTH_DLU, units.cx, 4);
    int addWidth = width;
    for (int index = 0; index < ARRAYSIZE(buttons); index++) {
        if (!GetWindowRect(buttons[index], &bounds[index])) {
            return;
        }
        MapWindowPoints(HWND_DESKTOP, hSettings, reinterpret_cast<POINT*>(&bounds[index]), 2);
        if (index < footerButtonCount) {
            width = PreferredButtonWidth(buttons[index], width);
        } else {
            addWidth = PreferredButtonWidth(buttons[index], addWidth, 0);
        }
    }
    RECT combo = {};
    RECT importButton = {};
    RECT exportButton = {};
    if (!GetWindowRect(hAddType, &combo)
            || !GetWindowRect(GetDlgItem(hSettings, ID_IMPORT_SETTINGS), &importButton)
            || !GetWindowRect(GetDlgItem(hSettings, ID_EXPORT_SETTINGS), &exportButton)) {
        return;
    }
    MapWindowPoints(HWND_DESKTOP, hSettings, reinterpret_cast<POINT*>(&combo), 2);
    int gap = exportButton.left - importButton.right;
    int left = bounds[footerButtonCount - 1].right - width;
    for (int index = footerButtonCount - 1; index >= 0; index--) {
        SetControlPosition(buttons[index], left, bounds[index].top, width,
            bounds[index].bottom - bounds[index].top);
        left -= width + gap;
    }
    int addLeft = bounds[footerButtonCount].right - addWidth;
    SetControlPosition(buttons[footerButtonCount], addLeft, bounds[footerButtonCount].top, addWidth,
        bounds[footerButtonCount].bottom - bounds[footerButtonCount].top);
    SetControlPosition(hAddType, combo.left, combo.top,
        std::max(1L, addLeft - SettingsDialogWidth(4) - combo.left), combo.bottom - combo.top);
}

/// Gives Default and Test the same width from their longer caption, preserving their common right edge.
/// The font selector and sound combo fill the remaining row width with the action-button gap.
static void UpdateApplicationControlWidths() {
    RECT save = {};
    RECT cancel = {};
    RECT font = {};
    RECT defaultFont = {};
    RECT sound = {};
    RECT test = {};
    const bool rectanglesUnavailable = !GetWindowRect(GetDlgItem(hSettings, ID_SAVE), &save)
        || !GetWindowRect(GetDlgItem(hSettings, ID_CANCEL), &cancel)
        || !GetWindowRect(hAppFontButton, &font)
        || !GetWindowRect(hAppFontDefaultButton, &defaultFont)
        || !GetWindowRect(hTimeSignalSoundCombo, &sound)
        || !GetWindowRect(hTimeSignalTestButton, &test);
    if (rectanglesUnavailable) {
        return;
    }
    LONG gap = cancel.left - save.right;
    MapWindowPoints(HWND_DESKTOP, hApplicationPage, reinterpret_cast<POINT*>(&font), 2);
    MapWindowPoints(HWND_DESKTOP, hApplicationPage, reinterpret_cast<POINT*>(&defaultFont), 2);
    MapWindowPoints(HWND_DESKTOP, hApplicationPage, reinterpret_cast<POINT*>(&sound), 2);
    MapWindowPoints(HWND_DESKTOP, hApplicationPage, reinterpret_cast<POINT*>(&test), 2);
    HFONT buttonFont = reinterpret_cast<HFONT>(SendMessageW(hAppFontDefaultButton, WM_GETFONT, 0, 0));
    SIZE units = {};
    if (!GetDialogFontBaseUnits(buttonFont, &units)) {
        return;
    }
    LONG width = MulDiv(DIALOG_BUTTON_WIDTH_DLU, units.cx, 4);
    width = PreferredButtonWidth(hAppFontDefaultButton, width, 0);
    width = PreferredButtonWidth(hTimeSignalTestButton, width, 0);
    LONG left = test.right - width;
    SetControlPosition(hTimeSignalTestButton, left, test.top, width, test.bottom - test.top);
    SetControlPosition(hTimeSignalSoundCombo, sound.left, sound.top, left - gap - sound.left,
        sound.bottom - sound.top);
    SetControlPosition(hAppFontDefaultButton, left, defaultFont.top,
        width, defaultFont.bottom - defaultFont.top);
    SetControlPosition(hAppFontButton, font.left, font.top, left - gap - font.left, font.bottom - font.top);
}

/// Tests a screen point against visible siblings above a control, including disabled siblings that still
/// block input.
static bool IsSettingsControlPointCovered(HWND control, POINT point) {
    for (HWND sibling = GetWindow(control, GW_HWNDPREV);
            sibling != nullptr;
            sibling = GetWindow(sibling, GW_HWNDPREV)) {
        RECT rect = {};
        if (IsWindowVisible(sibling) && GetWindowRect(sibling, &rect) && PtInRect(&rect, point)) {
            return true;
        }
    }
    return false;
}

/// Makes the focused settings push button the current default, restoring Save for other focus targets.
/// Updates only the previous and new default buttons when their roles change.
static void UpdateSettingsDefaultButton(HWND focused) {
    HWND button = GetDlgItem(hSettings, ID_SAVE);
    if (hSettingsDefaultButton == nullptr) {
        hSettingsDefaultButton = button;
    }
    if (IsChild(hSettings, focused) && IsWindowVisible(focused) && IsWindowEnabled(focused)) {
        LRESULT dialogCode = SendMessageW(focused, WM_GETDLGCODE, 0, 0);
        bool pushButton = (dialogCode & (DLGC_DEFPUSHBUTTON | DLGC_UNDEFPUSHBUTTON)) != 0;
        if (pushButton) {
            button = focused;
        }
    }
    if (button == hSettingsDefaultButton) {
        return;
    }
    if (hSettingsDefaultButton != nullptr && IsWindow(hSettingsDefaultButton)) {
        SendMessageW(hSettingsDefaultButton, BM_SETSTYLE, BS_PUSHBUTTON, TRUE);
    }
    hSettingsDefaultButton = button;
    if (button != nullptr) {
        SendMessageW(button, BM_SETSTYLE, BS_DEFPUSHBUTTON, TRUE);
    }
}

/// Temporarily bypasses covered-control mouse guards while a native programmatic button click is processed.
static LRESULT ClickSettingsControl(HWND window, WPARAM wParam, LPARAM lParam, UINT_PTR subclassId,
        DWORD_PTR referenceData) {
    SetWindowSubclass(window, SettingsControlSubclassProc, subclassId, 1);
    LRESULT result = DefSubclassProc(window, BM_CLICK, wParam, lParam);
    DWORD_PTR currentData = 0;
    if (GetWindowSubclass(window, SettingsControlSubclassProc, subclassId, &currentData)) {
        SetWindowSubclass(window, SettingsControlSubclassProc, subclassId, referenceData);
    }
    return result;
}

/// Makes a covered settings control transparent to hit testing and preserves native handling elsewhere.
static LRESULT HitTestSettingsControl(HWND window, WPARAM wParam, LPARAM lParam) {
    POINT point = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
    if (IsSettingsControlPointCovered(window, point)) {
        return HTTRANSPARENT;
    }
    return DefSubclassProc(window, WM_NCHITTEST, wParam, lParam);
}

/// Suppresses mouse presses covered by a higher sibling while preserving programmatic and native input.
static LRESULT HandleSettingsControlPress(HWND window, UINT msg, WPARAM wParam, LPARAM lParam,
        DWORD_PTR referenceData) {
    if (referenceData != 0) {
        return DefSubclassProc(window, msg, wParam, lParam);
    }
    POINT point = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
    ClientToScreen(window, &point);
    if (IsSettingsControlPointCovered(window, point)) {
        return 0;
    }
    return DefSubclassProc(window, msg, wParam, lParam);
}

/// Prevents captured checkbox movement and releases over higher siblings from activating covered controls.
static LRESULT HandleSettingsControlPointer(HWND window, UINT msg, WPARAM wParam, LPARAM lParam,
        DWORD_PTR referenceData) {
    if (referenceData != 0) {
        return DefSubclassProc(window, msg, wParam, lParam);
    }
    if (GetSettingsControlLayer(window) == SETTINGS_CONTROL_CHECKBOX) {
        POINT point = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
        ClientToScreen(window, &point);
        if (IsSettingsControlPointCovered(window, point)) {
            if (msg == WM_LBUTTONUP) {
                SendMessageW(window, BM_SETSTATE, FALSE, 0);
            }
            return DefSubclassProc(window, msg, wParam, MAKELPARAM(-1, -1));
        }
    }
    return DefSubclassProc(window, msg, wParam, lParam);
}

/// Inserts plain strings through the native ComboBoxEx item API while preserving existing combo messages.
static LRESULT InsertSettingsComboString(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (GetSettingsComboBox(window) == window) {
        return DefSubclassProc(window, msg, wParam, lParam);
    }
    COMBOBOXEXITEMW item = {};
    item.mask = CBEIF_TEXT;
    item.iItem = msg == CB_ADDSTRING ? -1 : static_cast<INT_PTR>(wParam);
    item.pszText = reinterpret_cast<wchar_t*>(lParam);
    return SendMessageW(window, CBEM_INSERTITEMW, 0, reinterpret_cast<LPARAM>(&item));
}

/// Applies the native font or theme change before recalculating the settings control's metrics.
static LRESULT HandleSettingsControlMetricsChange(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) {
    LRESULT result = DefSubclassProc(window, msg, wParam, lParam);
    UpdateSettingsFieldMetrics(window, 0);
    return result;
}

/// Lets the native static or checkbox draw its complete client area into a local buffer before presenting it.
static LRESULT PaintSettingsTextControl(HWND window) {
    PAINTSTRUCT paint = {};
    HDC target = BeginPaint(window, &paint);
    if (target == nullptr) {
        return 0;
    }
    RECT client = {};
    GetClientRect(window, &client);
    HDC dc = nullptr;
    HPAINTBUFFER buffer = BeginBufferedPaint(target, &client, BPBF_TOPDOWNDIB, nullptr, &dc);
    if (buffer == nullptr) {
        dc = target;
    }
    DrawThemeParentBackground(window, dc, nullptr);
    DefSubclassProc(window, WM_PRINTCLIENT, reinterpret_cast<WPARAM>(dc), PRF_CLIENT | PRF_ERASEBKGND);
    if (buffer != nullptr) {
        EndBufferedPaint(buffer, TRUE);
    }
    EndPaint(window, &paint);
    return 0;
}

/// Defers immediate native text/state painting until the changed control can present its complete buffered
/// image.
static LRESULT UpdateSettingsTextControlState(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) {
    WindowRedrawScope redraw(window);
    return DefSubclassProc(window, msg, wParam, lParam);
}

/// Supplies native disabled colors when a ComboBoxEx's inner combo requests its text-field brush.
static LRESULT GetSettingsComboControlBrush(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (GetSettingsComboBox(window) != window && !IsWindowEnabled(window)) {
        HDC dc = reinterpret_cast<HDC>(wParam);
        SetTextColor(dc, GetSysColor(COLOR_GRAYTEXT));
        SetBkColor(dc, GetSysColor(COLOR_BTNFACE));
        return reinterpret_cast<LRESULT>(GetSysColorBrush(COLOR_BTNFACE));
    }
    return DefSubclassProc(window, msg, wParam, lParam);
}

/// Draws enabled and disabled selected-item text with identical font metrics and native content bounds.
/// Keeps the native field background and classic selection colors; leaves frame, arrow, and dropdown drawing
/// intact.
static LRESULT DrawSettingsComboSelection(HWND window, WPARAM wParam, LPARAM lParam) {
    DRAWITEMSTRUCT* item = reinterpret_cast<DRAWITEMSTRUCT*>(lParam);
    if (item == nullptr
            || GetSettingsComboBox(window) == window
            || item->CtlType != ODT_COMBOBOX
            || (item->itemState & ODS_COMBOBOXEDIT) == 0
            || item->itemID == static_cast<UINT>(-1)) {
        return DefSubclassProc(window, WM_DRAWITEM, wParam, lParam);
    }
    LRESULT length = SendMessageW(window, CB_GETLBTEXTLEN, item->itemID, 0);
    if (length == CB_ERR) {
        return DefSubclassProc(window, WM_DRAWITEM, wParam, lParam);
    }
    std::wstring text(static_cast<size_t>(length) + 1, L'\0');
    SendMessageW(window, CB_GETLBTEXT, item->itemID, reinterpret_cast<LPARAM>(text.data()));
    int saved = SaveDC(item->hDC);
    HFONT font = reinterpret_cast<HFONT>(SendMessageW(item->hwndItem, WM_GETFONT, 0, 0));
    if (font != nullptr) {
        SelectObject(item->hDC, font);
    }
    bool disabled = (item->itemState & ODS_DISABLED) != 0;
    bool themed = !themesDisabled && AreVisualStylesActive();
    bool selected = !disabled && (item->itemState & ODS_SELECTED) != 0 && !themed;
    if (selected) {
        RECT selection = item->rcItem;
        selection.left += GetSystemMetrics(SM_CXBORDER);
        selection.right -= GetSystemMetrics(SM_CXBORDER);
        FillRect(item->hDC, &selection, GetSysColorBrush(COLOR_HIGHLIGHT));
        SetBkColor(item->hDC, GetSysColor(COLOR_HIGHLIGHT));
    }
    int textColor;
    if (disabled) {
        textColor = COLOR_GRAYTEXT;
    } else if (selected) {
        textColor = COLOR_HIGHLIGHTTEXT;
    } else {
        textColor = COLOR_WINDOWTEXT;
    }
    SetTextColor(item->hDC, GetSysColor(textColor));
    SetBkMode(item->hDC, selected ? OPAQUE : TRANSPARENT);
    RECT content = item->rcItem;
    DrawTextW(item->hDC, text.data(), static_cast<int>(length), &content,
        DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    RestoreDC(item->hDC, saved);
    if ((item->itemState & ODS_FOCUS) != 0 && (item->itemState & ODS_NOFOCUSRECT) == 0) {
        RECT focus = item->rcItem;
        focus.left += GetSystemMetrics(SM_CXBORDER);
        if (!themed) {
            focus.right -= GetSystemMetrics(SM_CXBORDER);
        }
        DrawFocusRect(item->hDC, &focus);
    }
    return TRUE;
}

/// Restricts native dropdown drawing to the current item without changing the closed-field renderer.
/// Prevents tall font metrics from allowing one row to erase or paint over adjacent rows.
static LRESULT DrawSettingsComboItem(HWND window, WPARAM wParam, LPARAM lParam) {
    const DRAWITEMSTRUCT* item = reinterpret_cast<const DRAWITEMSTRUCT*>(lParam);
    if (item == nullptr
            || item->CtlType != ODT_COMBOBOX
            || (item->itemState & ODS_COMBOBOXEDIT) != 0
            || GetSettingsComboBox(window) == window) {
        return DrawSettingsComboSelection(window, wParam, lParam);
    }
    int saved = SaveDC(item->hDC);
    if (saved == 0) {
        return DefSubclassProc(window, WM_DRAWITEM, wParam, lParam);
    }
    IntersectClipRect(item->hDC, item->rcItem.left, item->rcItem.top, item->rcItem.right,
        item->rcItem.bottom);
    LRESULT result = DefSubclassProc(window, WM_DRAWITEM, wParam, lParam);
    RestoreDC(item->hDC, saved);
    return result;
}

/// Keeps the settings default button in step with focus and prevents clicks on covered controls.
/// Allows programmatic BM_CLICK activation and removes the subclass when the control is destroyed.
static LRESULT CALLBACK SettingsControlSubclassProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    if (GetSettingsControlLayer(window) != SETTINGS_CONTROL_FOREGROUND) {
        if (msg == WM_PAINT && wParam == 0) {
            return PaintSettingsTextControl(window);
        }
        if (msg == WM_ERASEBKGND) {
            return TRUE;
        }
        if (msg == WM_ENABLE || msg == WM_SETTEXT || msg == BM_SETCHECK || msg == WM_UPDATEUISTATE) {
            return UpdateSettingsTextControlState(window, msg, wParam, lParam);
        }
    }
    switch (msg) {
        case WM_CTLCOLORSTATIC:
        case WM_CTLCOLOREDIT:
            return GetSettingsComboControlBrush(window, msg, wParam, lParam);
        case WM_DRAWITEM:
            return DrawSettingsComboItem(window, wParam, lParam);
        case CB_ADDSTRING:
        case CB_INSERTSTRING:
            return InsertSettingsComboString(window, msg, wParam, lParam);
        case WM_SETFOCUS:
            UpdateSettingsDefaultButton(window);
            break;
        case WM_KILLFOCUS:
            UpdateSettingsDefaultButton(reinterpret_cast<HWND>(wParam));
            break;
        case BM_CLICK:
            return ClickSettingsControl(window, wParam, lParam, subclassId, referenceData);
        case WM_NCHITTEST:
            return HitTestSettingsControl(window, wParam, lParam);
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
            return HandleSettingsControlPress(window, msg, wParam, lParam, referenceData);
        case WM_MOUSEMOVE:
        case WM_LBUTTONUP:
            return HandleSettingsControlPointer(window, msg, wParam, lParam, referenceData);
        case WM_SETFONT:
        case WM_THEMECHANGED:
            return HandleSettingsControlMetricsChange(window, msg, wParam, lParam);
        case WM_NCDESTROY:
            if (window == hSettingsOpenCombo) {
                hSettingsOpenCombo = nullptr;
                settingsComboInitialSelection = CB_ERR;
                settingsComboAccepted = false;
            }
            RemovePropW(window, SETTINGS_FIELD_LABEL_PROPERTY);
            RemovePropW(window, SETTINGS_COLOR_PREVIEW_PROPERTY);
            RemovePropW(window, SETTINGS_COLOR_BUTTON_PROPERTY);
            if (window == hSettingsDefaultButton) {
                hSettingsDefaultButton = nullptr;
            }
            RemoveWindowSubclass(window, SettingsControlSubclassProc, subclassId);
            break;
    }
    return DefSubclassProc(window, msg, wParam, lParam);
}

/// Enables native sibling clipping and enforces control Z order for resource-sized labels and checkboxes.
/// Makes buffered text controls opaque to parent erasure and guards input beneath foreground controls.
static void UpdateSettingsTextControlLayout(HWND parent,
        const std::vector<ControlVisibility>* visibility = nullptr) {
    if (parent == nullptr) {
        return;
    }
    std::vector<PositionedControl> controls;
    for (HWND control = GetWindow(parent, GW_CHILD);
            control != nullptr;
            control = GetWindow(control, GW_HWNDNEXT)) {
        DWORD_PTR referenceData = 0;
        if (!GetWindowSubclass(control, SettingsControlSubclassProc, SETTINGS_CONTROL_SUBCLASS_ID,
                &referenceData)) {
            SetWindowSubclass(control, SettingsControlSubclassProc, SETTINGS_CONTROL_SUBCLASS_ID, 0);
        }
        RECT rect = {};
        if (!GetWindowRect(control, &rect)) {
            continue;
        }
        MapWindowPoints(HWND_DESKTOP, parent, reinterpret_cast<POINT*>(&rect), 2);
        bool background = GetSettingsControlLayer(control) != SETTINGS_CONTROL_FOREGROUND;
        if (background || parent == hApplicationPage) {
            LONG_PTR style = GetWindowLongPtrW(control, GWL_STYLE);
            if ((style & WS_CLIPSIBLINGS) == 0) {
                SetWindowLongPtrW(control, GWL_STYLE, style | WS_CLIPSIBLINGS);
            }
        }
        if (background) {
            LONG_PTR extendedStyle = GetWindowLongPtrW(control, GWL_EXSTYLE);
            if ((extendedStyle & WS_EX_TRANSPARENT) != 0) {
                SetWindowLongPtrW(control, GWL_EXSTYLE, extendedStyle & ~WS_EX_TRANSPARENT);
            }
            SetControlPosition(control, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
        }
        controls.push_back(PositionedControl{ control, rect });
    }
    std::stable_sort(controls.begin(), controls.end(),
        std::bind(SettingsControlIsAbove, std::placeholders::_1, std::placeholders::_2, visibility));
    HWND previous = nullptr;
    for (const PositionedControl& control : controls) {
        if (GetWindow(control.window, GW_HWNDPREV) != previous) {
            SetWindowPos(control.window, previous, 0, 0, 0, 0,
                SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOCOPYBITS);
        }
        previous = control.window;
    }
}

/// Handles list selection and widget keyboard commands, including copy, paste, removal, and duplication.
/// On associated buttons, transfers focus to the widget list before handling the shortcut.
static LRESULT CALLBACK WidgetListSubclassProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    UNREFERENCED_PARAMETER(referenceData);
    if (subclassId == ID_LIST_WIDGETS) {
        if (msg == WM_PAINT && wParam == 0) {
            return PaintSettingsWidgetList(window);
        }
        if (msg == WM_ERASEBKGND) {
            return TRUE;
        }
    }
    bool widgetCommands =
        subclassId == ID_LIST_WIDGETS || subclassId == ID_REMOVE || subclassId == ID_DUPLICATE;
    HWND list = widgetCommands ? hWidgetList : window;
    if (msg == WM_KEYDOWN && widgetCommands && GetFocus() == window) {
        bool controlPressed = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
        bool clipboardShortcut = controlPressed && (wParam == L'A' || wParam == L'C' || wParam == L'V');
        bool listShortcut = clipboardShortcut || wParam == VK_DELETE || wParam == VK_INSERT;
        if (listShortcut) {
            SetFocus(list);
        }
    }
    if (msg == WM_KEYDOWN && wParam == L'A' && (GetKeyState(VK_CONTROL) & 0x8000) != 0) {
        SendMessageW(list, LB_SETSEL, TRUE, -1);
        SendMessageW(GetParent(list), WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(list), LBN_SELCHANGE),
            reinterpret_cast<LPARAM>(list));
        return 0;
    }
    if (msg == WM_KEYDOWN
            && widgetCommands
            && GetFocus() == list
            && (GetKeyState(VK_CONTROL) & 0x8000) != 0) {
        if (wParam == L'C') {
            CopySelectedWidgetsToClipboard();
            return 0;
        }
        if (wParam == L'V') {
            PasteWidgetsFromClipboard();
            return 0;
        }
    }
    if (msg == WM_KEYDOWN && wParam == VK_DELETE && widgetCommands) {
        SendMessageW(hSettings, WM_COMMAND, MAKEWPARAM(ID_REMOVE, BN_CLICKED), 0);
        return 0;
    }
    if (msg == WM_KEYDOWN && wParam == VK_INSERT && widgetCommands) {
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
    if (msg == LB_ADDSTRING || msg == LB_INSERTSTRING || msg == LB_DELETESTRING || msg == LB_RESETCONTENT) {
        LRESULT result = DefSubclassProc(window, msg, wParam, lParam);
        UpdateSettingsListMetrics(window);
        return result;
    }
    if (msg == WM_NCDESTROY) {
        RemoveWindowSubclass(window, WidgetListSubclassProc, subclassId);
    }
    return DefSubclassProc(window, msg, wParam, lParam);
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

/// Hides visible fullscreen widgets, remembers them for restoration, and saves settings without preview
/// appearance changes. Returns whether any widget was hidden.
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
        for (size_t wndIndex = 0; wndIndex < widget->fullscreenWindows.size(); wndIndex++) {
            ShowWindow(widget->fullscreenWindows[wndIndex], SW_HIDE);
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
std::wstring GetControlText(HWND control) {
    int length = GetWindowTextLengthW(control);
    std::wstring text(static_cast<size_t>(length) + 1, L'\0');
    int copied = GetWindowTextW(control, text.data(), static_cast<int>(text.size()));
    text.resize(copied);
    return text;
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

/// Updates a caption only when its text differs after mnemonic removal, preserving existing mnemonic
/// assignments otherwise.
static void SetControlCaption(HWND control, const wchar_t* caption) {
    if (control != nullptr
            && RemoveCaptionMnemonic(GetControlText(control)) != RemoveCaptionMnemonic(caption)) {
        SetWindowTextW(control, caption);
    }
}

/// Changes a nonnull control's enabled state and keeps its associated color preview in the same state.
static void SetControlEnabled(HWND control, bool enabled) {
    if (control == nullptr) {
        return;
    }
    bool currentlyEnabled = IsWindowEnabled(control) != FALSE;
    if (currentlyEnabled != enabled) {
        EnableWindow(control, enabled);
    }
    HWND preview = reinterpret_cast<HWND>(GetPropW(control, SETTINGS_COLOR_PREVIEW_PROPERTY));
    if (preview != nullptr) {
        SetControlEnabled(preview, enabled);
    }
}

/// Changes a nonnull control's own visibility style and keeps its associated color preview in the same state.
static void SetControlVisible(HWND control, bool visible) {
    control = SettingsEdit::GetFrame(control);
    if (control == nullptr) {
        return;
    }
    bool currentlyVisible = (GetWindowLongPtrW(control, GWL_STYLE) & WS_VISIBLE) != 0;
    if (currentlyVisible != visible) {
        ShowWindow(control, visible ? SW_SHOW : SW_HIDE);
    }
    HWND preview = reinterpret_cast<HWND>(GetPropW(control, SETTINGS_COLOR_PREVIEW_PROPERTY));
    if (preview != nullptr) {
        SetControlVisible(preview, visible);
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

/// Updates a native color button's stored selection and repaints its associated preview when the color
/// changes.
static void SetButtonColor(HWND button, COLORREF color) {
    if (button != nullptr && static_cast<COLORREF>(GetWindowLongPtrW(button, GWLP_USERDATA)) != color) {
        SetWindowLongPtrW(button, GWLP_USERDATA, color);
        HWND preview = reinterpret_cast<HWND>(GetPropW(button, SETTINGS_COLOR_PREVIEW_PROPERTY));
        if (preview != nullptr) {
            InvalidateRect(preview, nullptr, TRUE);
        }
    }
}

/// Draws or measures descriptive text using the same word wrapping and current font's line height.
/// Optional line metrics keep changing status messages on the same baselines.
static int DrawWordWrappedText(HDC dc, const std::wstring& text, const RECT& bounds,
        UINT prefix = DT_NOPREFIX, const UiTextLine* fixedLine = nullptr) {
    TEXTMETRICW metrics = {};
    if (!GetTextMetricsW(dc, &metrics)) {
        return 0;
    }
    UiTextLine layout = fixedLine == nullptr ? GetUiTextLine(dc, text) : *fixedLine;
    int lineHeight = std::max(1L, layout.ascent + layout.descent + layout.gap);
    bool measure = (prefix & DT_CALCRECT) != 0;
    int saved = SaveDC(dc);
    if (!measure) {
        IntersectClipRect(dc, bounds.left, bounds.top, bounds.right, bounds.bottom);
    }
    int maximumWidth = bounds.right - bounds.left;
    int y = bounds.top;
    size_t position = 0;
    std::wstring line;
    while (position < text.size() && (measure || y < bounds.bottom)) {
        if (text[position] == L'\r' || text[position] == L'\n') {
            if (!measure && !line.empty()) {
                RECT lineRect = {
                    bounds.left,
                    y + layout.ascent - metrics.tmAscent,
                    bounds.right,
                    y + layout.ascent + metrics.tmDescent
                };
                DrawTextW(dc, line.c_str(), -1, &lineRect, DT_LEFT | DT_TOP | DT_SINGLELINE | prefix);
            }
            line.clear();
            wchar_t newline = text[position++];
            if (position < text.size() && newline == L'\r' && text[position] == L'\n') {
                position++;
            }
            y += lineHeight;
            continue;
        }
        while (position < text.size()
                && IsUnicodeWhitespace(text[position])
                && text[position] != L'\r'
                && text[position] != L'\n') {
            position++;
        }
        size_t wordStart = position;
        while (position < text.size() && !IsUnicodeWhitespace(text[position])) {
            position++;
        }
        if (wordStart == position) {
            continue;
        }
        std::wstring word = text.substr(wordStart, position - wordStart);
        std::wstring candidate = line.empty() ? word : line + L" " + word;
        SIZE extent = {};
        std::wstring measured = prefix & DT_NOPREFIX ? candidate : RemoveCaptionMnemonic(candidate);
        GetTextExtentPoint32W(dc, measured.c_str(), static_cast<int>(measured.size()), &extent);
        if (!line.empty() && extent.cx > maximumWidth) {
            if (!measure) {
                RECT lineRect = {
                    bounds.left,
                    y + layout.ascent - metrics.tmAscent,
                    bounds.right,
                    y + layout.ascent + metrics.tmDescent
                };
                DrawTextW(dc, line.c_str(), -1, &lineRect, DT_LEFT | DT_TOP | DT_SINGLELINE | prefix);
            }
            y += lineHeight;
            line = word;
        } else {
            line = candidate;
        }
    }
    if (!line.empty() && (measure || y < bounds.bottom)) {
        if (!measure) {
            RECT lineRect = {
                bounds.left,
                y + layout.ascent - metrics.tmAscent,
                bounds.right,
                y + layout.ascent + metrics.tmDescent
            };
            DrawTextW(dc, line.c_str(), -1, &lineRect, DT_LEFT | DT_TOP | DT_SINGLELINE | prefix);
        }
        y += lineHeight;
    }
    RestoreDC(dc, saved);
    return y - bounds.top;
}

/// Assigns nonconflicting mnemonics to eligible visible child captions using the shared set of already
/// assigned keys.
static void AssignSettingsMnemonicsToChildren(HWND parent, std::vector<wchar_t>* usedMnemonics) {
    for (HWND control = GetWindow(parent, GW_CHILD);
            control != nullptr;
            control = GetWindow(control, GW_HWNDNEXT)) {
        LONG_PTR style = GetWindowLongPtrW(control, GWL_STYLE);
        if ((style & WS_VISIBLE) == 0) {
            continue;
        }
        wchar_t className[32] = {};
        GetClassNameW(control, className, ARRAYSIZE(className));
        std::wstring text = GetControlText(control);
        bool button = _wcsicmp(className, L"Button") == 0 && (style & WS_TABSTOP) != 0;
        bool label = _wcsicmp(className, L"Static") == 0
            && ((style & SS_TYPEMASK) != SS_OWNERDRAW || control == hNtpServersLabel)
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

/// Sizes native report rows from the selected font, localized content and native checkbox images.
static bool MeasureSettingsReportItem(MEASUREITEMSTRUCT* item) {
    if (item == nullptr
            || item->CtlType != ODT_LISTVIEW
            || item->CtlID != ID_NTP_LOG && item->CtlID != ID_MONITOR_LIST) {
        return false;
    }
    HWND page = item->CtlID == ID_MONITOR_LIST ? hGeneralPage : hTimePage;
    HWND list = GetDlgItem(page, item->CtlID);
    HDC dc = GetDC(list);
    if (dc == nullptr) {
        return false;
    }
    HFONT font = list == nullptr ? hUiFont : reinterpret_cast<HFONT>(SendMessageW(list, WM_GETFONT, 0, 0));
    HGDIOBJ previous = font == nullptr ? nullptr : SelectObject(dc, font);
    std::wstring text;
    if (item->CtlID == ID_MONITOR_LIST) {
        for (TextId textId : MONITOR_COLUMN_TEXT_IDS) {
            const wchar_t* heading = T(textId);
            text += heading;
        }
        for (const MonitorListEntry& entry : monitorListEntries) {
            for (const std::wstring& value : entry.text) {
                text += value;
            }
        }
    } else {
        text = T(TXT_NTP_STATUS_FAILED);
        for (TextId textId : NTP_LOG_COLUMN_TEXT_IDS) {
            const wchar_t* heading = T(textId);
            text += heading;
        }
        for (TextId textId : NTP_LOG_ERROR_TEXT_IDS) {
            const wchar_t* error = T(textId);
            text += error;
        }
    }
    UiTextLine line = GetUiTextLine(dc, text);
    item->itemHeight = std::max(1L, line.ascent + line.descent + line.gap) + 2 * GetSystemMetrics(SM_CYEDGE);
    HIMAGELIST stateImages = nullptr;
    if (list != nullptr) {
        stateImages = ListView_GetImageList(list, LVSIL_STATE);
    }
    int imageWidth = 0;
    int imageHeight = 0;
    if (stateImages != nullptr && ImageList_GetIconSize(stateImages, &imageWidth, &imageHeight)) {
        item->itemHeight =
            std::max(item->itemHeight, static_cast<UINT>(imageHeight + 2 * GetSystemMetrics(SM_CYBORDER)));
    }
    if (previous != nullptr && previous != HGDI_ERROR) {
        SelectObject(dc, previous);
    }
    ReleaseDC(list, dc);
    return true;
}

/// Draws log columns in the selected font while native list-view selection, scrolling, data, and sorting
/// stay intact.
static bool DrawNtpLogItem(const DRAWITEMSTRUCT* item) {
    if (item == nullptr || item->CtlType != ODT_LISTVIEW || item->hwndItem != hNtpLogList) {
        return false;
    }
    int saved = SaveDC(item->hDC);
    bool selected = (item->itemState & ODS_SELECTED) != 0;
    bool focused = GetFocus() == hNtpLogList;
    int backgroundColor;
    if (selected && focused) {
        backgroundColor = COLOR_HIGHLIGHT;
    } else if (selected) {
        backgroundColor = COLOR_BTNFACE;
    } else {
        backgroundColor = COLOR_WINDOW;
    }
    FillRect(item->hDC, &item->rcItem, GetSysColorBrush(backgroundColor));
    SetTextColor(item->hDC, GetSysColor(selected && focused ? COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT));
    SetBkMode(item->hDC, TRANSPARENT);
    HFONT font = reinterpret_cast<HFONT>(SendMessageW(hNtpLogList, WM_GETFONT, 0, 0));
    if (font != nullptr) {
        SelectObject(item->hDC, font);
    }
    for (int column = 0; column < 3; column++) {
        wchar_t text[2048] = {};
        ListView_GetItemText(hNtpLogList, item->itemID, column, text, ARRAYSIZE(text));
        RECT content = {};
        ListView_GetSubItemRect(hNtpLogList, item->itemID, column, LVIR_LABEL, &content);
        InflateRect(&content, -GetSystemMetrics(SM_CXEDGE), 0);
        DrawTextW(item->hDC, text, -1, &content,
            DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX | DT_END_ELLIPSIS);
    }
    if ((item->itemState & ODS_FOCUS) != 0 && (item->itemState & ODS_NOFOCUSRECT) == 0) {
        DrawFocusRect(item->hDC, &item->rcItem);
    }
    RestoreDC(item->hDC, saved);
    return true;
}

/// Draws a wrapped label over its parent background using the selected font and native text colors.
INT_PTR DrawWrappedTextItem(const DRAWITEMSTRUCT* item) {
    int savedState = SaveDC(item->hDC);
    DrawThemeParentBackground(item->hwndItem, item->hDC, nullptr);
    SetBkMode(item->hDC, TRANSPARENT);
    SetTextColor(item->hDC, GetSysColor(IsWindowEnabled(item->hwndItem) ? COLOR_WINDOWTEXT : COLOR_GRAYTEXT));
    HFONT font = reinterpret_cast<HFONT>(SendMessageW(item->hwndItem, WM_GETFONT, 0, 0));
    if (font != nullptr) {
        SelectObject(item->hDC, font);
    }
    std::wstring text = GetControlText(item->hwndItem);
    RECT textRect = item->rcItem;
    UINT prefix = DT_NOPREFIX;
    UiTextLine statusLine = {};
    const UiTextLine* fixedLine = nullptr;
    if (item->hwndItem == hNtpServersLabel) {
        prefix = SendMessageW(item->hwndItem, WM_QUERYUISTATE, 0, 0) & UISF_HIDEACCEL ? DT_HIDEPREFIX : 0;
    } else if (item->hwndItem == hNtpStatus) {
        statusLine = GetNtpStatusLine(item->hDC);
        fixedLine = &statusLine;
    }
    DrawWordWrappedText(item->hDC, text, textRect, prefix, fixedLine);
    RestoreDC(item->hDC, savedState);
    return TRUE;
}

/// Draws descriptive settings text over its page texture, retaining mnemonic cues and the supplied DC state.
static INT_PTR DrawSettingsPageItem(LPARAM lParam) {
    DRAWITEMSTRUCT* item = reinterpret_cast<DRAWITEMSTRUCT*>(lParam);
    if (DrawSettingsListItem(item) || DrawNtpLogItem(item)) {
        return TRUE;
    }
    if (item == nullptr
        || item->CtlID != ID_TIME_SIGNAL_NOTE
            && item->hwndItem != hNtpServersLabel
            && item->hwndItem != hNtpStatus
            && item->hwndItem != hTimeGlobalNote) {
        return FALSE;
    }
    return DrawWrappedTextItem(item);
}

/// Returns native dialog notification results for report sorting and monitor checkbox changes.
static INT_PTR HandleSettingsPageNotification(HWND window, LPARAM lParam) {
    NMHDR* header = reinterpret_cast<NMHDR*>(lParam);
    LRESULT result = 0;
    if (HandleMonitorListNotification(header, &result)) {
        SetWindowLongPtrW(window, DWLP_MSGRESULT, result);
        return TRUE;
    }
    if (header->hwndFrom == hNtpLogList && header->code == LVN_COLUMNCLICK) {
        SortNtpLogByColumn(reinterpret_cast<NMLISTVIEW*>(lParam)->iSubItem);
        return TRUE;
    }
    return FALSE;
}

/// Supplies the selected color or the native disabled button background for an empty color preview.
static INT_PTR GetSettingsColorPreviewBrush(HWND preview, HDC dc) {
    HWND button = reinterpret_cast<HWND>(GetPropW(preview, SETTINGS_COLOR_BUTTON_PROPERTY));
    if (button == nullptr) {
        return FALSE;
    }
    COLORREF color = static_cast<COLORREF>(GetWindowLongPtrW(button, GWLP_USERDATA));
    if (!IsWindowEnabled(button)) {
        if (DrawSettingsColorPreviewTheme(preview, dc, false)) {
            return reinterpret_cast<INT_PTR>(GetStockObject(NULL_BRUSH));
        }
        color = GetSysColor(COLOR_BTNFACE);
    }
    SetBkColor(dc, color);
    SetDCBrushColor(dc, color);
    return reinterpret_cast<INT_PTR>(GetStockObject(DC_BRUSH));
}

/// Uses the native tab texture for a dialog page and forwards settings commands, sliders, and scrolling.
/// Draws the wrapped signal description over the dialog background and releases child layout properties
/// on destruction.
static INT_PTR CALLBACK SettingsPageProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_INITDIALOG:
            LimitDialogVerticalUnits(window, static_cast<int>(lParam));
            BufferedPaintInit();
            EnableThemeDialogTexture(window, themesDisabled ? ETDT_DISABLE : ETDT_ENABLETAB);
            return TRUE;
        case WM_COMMAND:
        case WM_HSCROLL:
        case WM_MOUSEWHEEL:
            SendMessageW(hSettings, msg, wParam, lParam);
            return TRUE;
        case WM_NOTIFY:
            return HandleSettingsPageNotification(window, lParam);
        case WM_MEASUREITEM:
            return MeasureSettingsReportItem(reinterpret_cast<MEASUREITEMSTRUCT*>(lParam));
        case WM_DRAWITEM:
            return DrawSettingsPageItem(lParam);
        case WM_CTLCOLORSTATIC:
            return GetSettingsColorPreviewBrush(reinterpret_cast<HWND>(lParam),
                reinterpret_cast<HDC>(wParam));
        case WM_NCDESTROY:
            BufferedPaintUnInit();
            break;
    }
    return FALSE;
}

/// Routes settings actions while retaining native dialog painting, navigation and default-button behavior.
static INT_PTR CALLBACK SettingsDialogProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_INITDIALOG) {
        LimitDialogVerticalUnits(window, IDD_SETTINGS);
        return FALSE;
    }
    if (message == WM_SIZE && wParam == SIZE_RESTORED && hTabs != nullptr) {
        PostMessageW(window, WM_UPDATE_SETTINGS_CONTROL_METRICS, 0, 0);
    }
    if (message == WM_COMMAND
            || message == WM_CLOSE
            || message == WM_HSCROLL
            || message == WM_VSCROLL
            || message == WM_MOUSEWHEEL
            || message == WM_NOTIFY
            || message == WM_UPDATE_SETTINGS_CONTROL_METRICS
            || message == WM_ALIGN_SETTINGS_FONT_BUTTON
            || message == WM_DRAWITEM
            || message == DM_GETDEFID) {
        LRESULT result = WindowProc(window, message, wParam, lParam);
        if (message == WM_DRAWITEM) {
            return result;
        }
        SetWindowLongPtrW(window, DWLP_MSGRESULT, result);
        return TRUE;
    }
    if (message == WM_SETTINGCHANGE || message == WM_THEMECHANGED || message == WM_SYSCOLORCHANGE) {
        WindowProc(window, message, wParam, lParam);
    }
    return FALSE;
}

/// Creates a Settings dialog using the system or selected application font before Windows converts its DLU
/// layout.
static HWND CreateSettingsDialog(UINT resourceId, HWND owner, DLGPROC procedure, LPARAM parameter) {
    bool customFont = HasApplicationUiFont();
    HFONT font = customFont ? CreateApplicationUiFont(owner) : nullptr;
    if (customFont && font == nullptr) {
        return nullptr;
    }
    DLGTEMPLATE* definition = LoadSystemDialogTemplate(hInstance, resourceId, owner, font);
    if (font != nullptr) {
        DeleteObject(font);
    }
    if (definition == nullptr) {
        return nullptr;
    }
    HWND dialog = CreateDialogIndirectParamW(hInstance, definition, owner, procedure, parameter);
    HeapFree(GetProcessHeap(), 0, definition);
    return dialog;
}

/// Recreates resource controls with their final parent so native controls retain valid notification owners.
static bool RestoreSettingsRootControls() {
    HWND replacement = CreateSettingsDialog(IDD_SETTINGS, hSettings, SettingsDialogProc, 0);
    if (replacement == nullptr) {
        return false;
    }
    RECT content = {};
    GetClientRect(replacement, &content);
    settingsContentWidth = content.right;
    settingsContentHeight = content.bottom;
    HWND child = GetWindow(replacement, GW_CHILD);
    while (child != nullptr) {
        HWND next = GetWindow(child, GW_HWNDNEXT);
        wchar_t className[256] = {};
        GetClassNameW(child, className, ARRAYSIZE(className));
        RECT bounds = GetSettingsResourceRect(replacement, GetDlgCtrlID(child));
        DWORD style = static_cast<DWORD>(GetWindowLongPtrW(child, GWL_STYLE));
        DWORD extendedStyle = static_cast<DWORD>(GetWindowLongPtrW(child, GWL_EXSTYLE));
        std::wstring text = GetControlText(child);
        if (GetDlgCtrlID(child) == ID_LIST_WIDGETS) {
            style |= WS_VSCROLL;
        }
        HWND control = CreateWindowExW(extendedStyle, className, text.c_str(), style, bounds.left,
            bounds.top, bounds.right - bounds.left, bounds.bottom - bounds.top, hSettings,
            reinterpret_cast<HMENU>(static_cast<INT_PTR>(GetDlgCtrlID(child))), hInstance, nullptr);
        if (control == nullptr) {
            DestroyWindow(replacement);
            return false;
        }
        SendMessageW(control, WM_SETFONT, reinterpret_cast<WPARAM>(hUiFont), FALSE);
        child = next;
    }
    DestroyWindow(replacement);
    return true;
}

/// Creates a settings page from its native dialog resource without activating it.
static HWND CreateSettingsPage(int templateId) {
    return CreateSettingsDialog(templateId, hSettings, SettingsPageProc, templateId);
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

/// Copies the selected built-in NTP server list into its edit control without treating the update as
/// a custom edit.
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

/// Maps stored generator volume to the piecewise decibel slider with -18 dB at its midpoint and silence
/// at the left endpoint.
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

/// Maps the slider's two decibel segments back to stored generator volume, reserving the left endpoint for
/// silence.
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
        decibels = TIME_SIGNAL_VOLUME_SLIDER_MIDDLE_DB + static_cast<double>(position
            - TIME_SIGNAL_VOLUME_SLIDER_MIDDLE) * -TIME_SIGNAL_VOLUME_SLIDER_MIDDLE_DB
            / (TIME_SIGNAL_VOLUME_SLIDER_MAX - TIME_SIGNAL_VOLUME_SLIDER_MIDDLE);
    }
    return TimeSignalVolumeFromDecibels(decibels);
}

/// Converts the shared decibel slider position to alarm volume in hundredths of a decibel, including the
/// silence sentinel.
static int AlarmVolumeFromSliderPosition(int position) {
    if (position == 0) {
        return ALARM_VOLUME_MIN;
    }
    return static_cast<int>(std::lround(100.0
        * TimeSignalVolumeDecibels(TimeSignalVolumeFromSliderPosition(position))));
}

/// Maps alarm hundredths of a decibel to the shared volume slider, placing silence at its left endpoint.
static int AlarmVolumeSliderPosition(int volume) {
    return volume == ALARM_VOLUME_MIN
        ? 0
        : TimeSignalVolumeSliderPosition(TimeSignalVolumeFromDecibels(volume / 100.0));
}

/// Returns the draft's exact alarm volume while its slider position is unchanged, otherwise converting the
/// new position.
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

/// Preserves the exact saved generator volume when its slider position is unchanged, otherwise converting
/// the new position.
static double SelectedTimeSignalVolume() {
    int position = static_cast<int>(SendMessageW(hTimeSignalVolumeTrackBar, TBM_GETPOS, 0, 0));
    return position == TimeSignalVolumeSliderPosition(timeSignalVolume)
        ? timeSignalVolume
        : TimeSignalVolumeFromSliderPosition(position);
}

/// Reads the selected persistent endpoint ID; the first combo item always means the Windows default output.
static std::wstring SelectedAudioOutputDevice(HWND combo, const std::vector<AudioOutputDevice>& devices) {
    int selection = static_cast<int>(SendMessageW(combo, CB_GETCURSEL, 0, 0));
    return selection > 0 && selection <= static_cast<int>(devices.size()) ? devices[selection - 1].id : L"";
}

/// Refreshes available output names while preserving a saved endpoint that is temporarily disconnected.
static void FillAudioOutputCombo(HWND combo, std::vector<AudioOutputDevice>& devices,
        const std::wstring& selected) {
    devices = EnumerateAudioOutputDevices();
    bool found = selected.empty();
    for (const AudioOutputDevice& device : devices) {
        found = found || device.id == selected;
    }
    if (!found) {
        devices.push_back(AudioOutputDevice{ selected, T(TXT_AUDIO_OUTPUT_UNAVAILABLE) });
    }
    SendMessageW(combo, CB_RESETCONTENT, 0, 0);
    SendMessageW(combo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(T(TXT_AUDIO_OUTPUT_DEFAULT)));
    int selection = 0;
    for (size_t index = 0; index < devices.size(); index++) {
        const AudioOutputDevice& device = devices[index];
        SendMessageW(combo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(device.name.c_str()));
        if (device.id == selected) {
            selection = static_cast<int>(index) + 1;
        }
    }
    bool generatedTone = IsTimeSignalGeneratorRequired()
        || SendMessageW(hTimeSignalSoundCombo, CB_GETCURSEL, 0, 0) == 0;
    SetComboSelection(combo, generatedTone ? selection : 0);
}

/// Starts or stops the merged time-signal preview from the Test button and active slider drag, updating the
/// button caption.
static void UpdateTimeSignalVolumePreview() {
    bool dragging = timeSignalVolumeDragging
        && hTimeSignalVolumeTrackBar != nullptr
        && IsWindowEnabled(hTimeSignalVolumeTrackBar);
    if (settingsTimeSignalTestActive || dragging) {
        bool generatedTone =
            IsTimeSignalGeneratorRequired() || SendMessageW(hTimeSignalSoundCombo, CB_GETCURSEL, 0, 0) == 0;
        double volume = SelectedTimeSignalVolume();
        if (!StartTimeSignalVolumePreview(generatedTone, volume, generatedTimeSignal,
            settingsTestAudioOutputDevice)) {
            settingsTimeSignalTestActive = false;
        }
    } else {
        StopTimeSignalVolumePreview();
    }
    const wchar_t* caption = settingsTimeSignalTestActive
        ? T(TXT_STOP_TEST_LABEL)
        : T(TXT_TEST_COMMAND_LABEL);
    SetControlCaption(hTimeSignalTestButton, caption);
}

/// Tracks mouse capture on the volume slider to control preview playback and stops it during subclass
/// destruction.
static LRESULT CALLBACK TimeSignalVolumeSubclassProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    UNREFERENCED_PARAMETER(referenceData);
    if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONDBLCLK) {
        LRESULT result = DefSubclassProc(window, msg, wParam, lParam);
        if (IsWindowEnabled(window) && GetCapture() == window) {
            timeSignalVolumeDragging = true;
            UpdateTimeSignalVolumePreview();
        }
        return result;
    }
    if (msg == WM_LBUTTONUP
            || msg == WM_CAPTURECHANGED
            || msg == WM_CANCELMODE
            || msg == WM_ENABLE && wParam == FALSE
            || msg == WM_SHOWWINDOW && wParam == FALSE) {
        timeSignalVolumeDragging = false;
        UpdateTimeSignalVolumePreview();
    }
    if (msg == WM_NCDESTROY) {
        timeSignalVolumeDragging = false;
        StopTimeSignalVolumePreview();
        RemoveWindowSubclass(window, TimeSignalVolumeSubclassProc, subclassId);
    }
    return DefSubclassProc(window, msg, wParam, lParam);
}

/// Enables generator volume controls only when applicable, updates the decibel label, and refreshes preview
/// state.
static void UpdateTimeSignalVolumeControls() {
    if (hTimeSignalVolumeTrackBar == nullptr
            || hTimeSignalVolumeLabel == nullptr
            || hTimeSignalVolumeValue == nullptr) {
        return;
    }
    bool enabled = IsTimeSignalGeneratorRequired()
        || SendMessageW(hTimeSignalSoundCombo, CB_GETCURSEL, 0, 0) == 0;
    SetControlEnabled(hTestAudioOutputCombo, enabled);
    int outputSelection = 0;
    if (enabled) {
        for (size_t index = 0; index < settingsTestAudioOutputs.size(); index++) {
            if (settingsTestAudioOutputs[index].id == settingsTestAudioOutputDevice) {
                outputSelection = static_cast<int>(index) + 1;
                break;
            }
        }
    }
    SetComboSelection(hTestAudioOutputCombo, outputSelection);
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

/// Formats a query completion timestamp as local date and time with six fractional-second digits.
static std::wstring FormatNtpLogTime(ULONGLONG timestamp) {
    ULARGE_INTEGER value = {};
    value.QuadPart = timestamp;
    FILETIME fileTime = { value.LowPart, value.HighPart };
    SYSTEMTIME utc = {};
    bool converted = FileTimeToSystemTime(&fileTime, &utc) != FALSE;
    if (!converted) {
        return std::wstring();
    }
    SYSTEMTIME local = {};
    converted = SystemTimeToTzSpecificLocalTime(nullptr, &utc, &local) != FALSE;
    if (!converted) {
        local = utc;
    }
    unsigned long microseconds = static_cast<unsigned long>(timestamp % 10000000ULL / 10);
    wchar_t text[64] = {};
    swprintf_s(text, L"%04d-%02d-%02d %02d:%02d:%02d.%06lu", local.wYear, local.wMonth, local.wDay,
        local.wHour, local.wMinute, local.wSecond, microseconds);
    return text;
}

/// Formats an NTP offset in milliseconds without losing its 100-nanosecond resolution.
static std::wstring FormatNtpLogOffset(LONGLONG offset100Nanoseconds) {
    bool negative = offset100Nanoseconds < 0;
    ULONGLONG magnitude = negative
        ? 0ULL - static_cast<ULONGLONG>(offset100Nanoseconds)
        : static_cast<ULONGLONG>(offset100Nanoseconds);
    wchar_t separator[8] = L".";
    int separatorLength = GetLocaleInfoEx(GetLanguageLocale(appLanguage), LOCALE_SDECIMAL, separator,
        ARRAYSIZE(separator));
    if (separatorLength == 0) {
        separator[0] = L'.';
        separator[1] = L'\0';
    }
    wchar_t text[64] = {};
    swprintf_s(text, L"%ls%llu%ls%04llu ms", negative ? L"−" : L"+", magnitude / 10000, separator,
        magnitude % 10000);
    return text;
}

/// Formats query status with its offset or failure reason and the combined offset on a group's final query
/// record.
static std::wstring FormatNtpLogStatus(const NtpQueryLogEntry& entry) {
    std::wstring status;
    if (entry.success) {
        status = L"OK: ";
        status += L"θ = ";
        status += FormatNtpLogOffset(entry.offset100Nanoseconds);
    } else {
        status = L"ERR: ";
        int errorIndex = std::clamp(static_cast<int>(entry.error), 0, 3);
        status += T(NTP_LOG_ERROR_TEXT_IDS[errorIndex]);
        if (entry.errorCode != 0) {
            status += L" (" + std::to_wstring(entry.errorCode) + L")";
        }
    }
    if (entry.hasCombinedOffset) {
        status += L"; Θ = ";
        status += FormatNtpLogOffset(entry.combinedOffset100Nanoseconds);
    }
    return status;
}

/// Quotes a CSV field and doubles embedded quotation marks, preserving commas and line breaks.
static std::wstring QuoteCsvField(const std::wstring& text) {
    std::wstring field = L"\"";
    for (wchar_t character : text) {
        if (character == L'"') {
            field += L'"';
        }
        field += character;
    }
    field += L'"';
    return field;
}

/// Builds the complete current-session NTP log with localized headings and statuses, a BOM, and CSV record
/// endings.
static std::wstring NtpLogCsvText() {
    std::wstring csv = L"\uFEFF";
    for (int column = 0; column < 3; column++) {
        if (column > 0) {
            csv += L',';
        }
        csv += QuoteCsvField(T(NTP_LOG_COLUMN_TEXT_IDS[column]));
    }
    csv += L"\r\n";
    for (const NtpQueryLogEntry& entry : ntpSynchronizationLog) {
        csv += QuoteCsvField(FormatNtpLogTime(entry.completedTime));
        csv += L',';
        csv += QuoteCsvField(entry.server);
        csv += L',';
        csv += QuoteCsvField(FormatNtpLogStatus(entry));
        csv += L"\r\n";
    }
    return csv;
}

/// Encodes the current-session CSV log as UTF-8 and writes it to the selected path, reporting conversion
/// or write failure.
static bool WriteNtpLogCsv(const std::wstring& path) {
    std::wstring csv = NtpLogCsvText();
    if (csv.size() > INT_MAX) {
        return false;
    }
    int characters = static_cast<int>(csv.size());
    int byteCount = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, csv.data(), characters,
        nullptr, 0, nullptr, nullptr);
    if (byteCount == 0) {
        return false;
    }
    std::string bytes(byteCount, '\0');
    int converted = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, csv.data(), characters,
        bytes.data(), byteCount, nullptr, nullptr);
    if (converted != byteCount) {
        return false;
    }
    HANDLE file = CreateFileW(path.c_str(), GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE) {
        return false;
    }
    DWORD written = 0;
    bool saved = WriteFile(file, bytes.data(), static_cast<DWORD>(bytes.size()), &written, nullptr) != FALSE
        && written == bytes.size();
    bool closed = CloseHandle(file) != FALSE;
    return saved && closed;
}

/// Returns the last selected directory, using Documents when no valid directory is stored.
static std::wstring FileDialogInitialDirectory() {
    bool valid = !fileDialogDirectory.empty() && !PathIsRelativeW(fileDialogDirectory.c_str());
    if (valid) {
        DWORD attributes = GetFileAttributesW(fileDialogDirectory.c_str());
        valid = attributes != INVALID_FILE_ATTRIBUTES && attributes & FILE_ATTRIBUTE_DIRECTORY;
    }
    if (valid) {
        return fileDialogDirectory;
    }
    wchar_t documents[MAX_PATH] = {};
    HRESULT result = SHGetFolderPathW(nullptr, CSIDL_PERSONAL, nullptr, SHGFP_TYPE_CURRENT, documents);
    if (FAILED(result)) {
        return std::wstring();
    }
    return documents;
}

/// Remembers the accepted file's directory and persists it without committing pending appearance previews.
static void RememberFileDialogDirectory(const std::wstring& path) {
    size_t separator = path.find_last_of(L"\\/");
    if (separator == std::wstring::npos) {
        return;
    }
    size_t length = separator;
    if (separator == 2 && path[1] == L':') {
        length++;
    }
    std::wstring directory = path.substr(0, length);
    if (directory.empty() || directory == fileDialogDirectory) {
        return;
    }
    fileDialogDirectory = directory;
    SaveSettingsWithoutAppearancePreviews();
}

/// Shows a native file dialog in the shared remembered directory and persists the directory only when saving.
static bool ChooseApplicationFile(bool save, const wchar_t* fileName, const COMDLG_FILTERSPEC* filters,
        UINT filterCount, const wchar_t* title, std::wstring* path) {
    HRESULT initialized = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (FAILED(initialized)) {
        return false;
    }
    IFileDialog* dialog = nullptr;
    const CLSID& classId = save ? CLSID_FileSaveDialog : CLSID_FileOpenDialog;
    HRESULT result = CoCreateInstance(classId, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&dialog));
    FILEOPENDIALOGOPTIONS options = 0;
    if (SUCCEEDED(result)) {
        result = dialog->GetOptions(&options);
    }
    if (SUCCEEDED(result)) {
        options |= FOS_FORCEFILESYSTEM | FOS_PATHMUSTEXIST | FOS_NOCHANGEDIR;
        options |= save ? FOS_OVERWRITEPROMPT : FOS_FILEMUSTEXIST;
        result = dialog->SetOptions(options);
    }
    if (SUCCEEDED(result)) {
        result = dialog->SetFileTypes(filterCount, filters);
    }
    if (SUCCEEDED(result)) {
        result = dialog->SetFileName(fileName);
    }
    if (SUCCEEDED(result)) {
        const wchar_t* extension = PathFindExtensionW(fileName);
        if (*extension == L'.') {
            result = dialog->SetDefaultExtension(extension + 1);
        }
    }
    if (SUCCEEDED(result) && title != nullptr) {
        result = dialog->SetTitle(title);
    }
    IShellItem* folder = nullptr;
    if (SUCCEEDED(result)) {
        std::wstring directory = FileDialogInitialDirectory();
        result = SHCreateItemFromParsingName(directory.c_str(), nullptr, IID_PPV_ARGS(&folder));
    }
    if (SUCCEEDED(result)) {
        result = dialog->SetFolder(folder);
    }
    if (folder != nullptr) {
        folder->Release();
    }
    if (SUCCEEDED(result)) {
        result = dialog->Show(hSettings);
    }
    IShellItem* selected = nullptr;
    if (SUCCEEDED(result)) {
        result = dialog->GetResult(&selected);
    }
    wchar_t* selectedPath = nullptr;
    if (SUCCEEDED(result)) {
        result = selected->GetDisplayName(SIGDN_FILESYSPATH, &selectedPath);
    }
    if (SUCCEEDED(result)) {
        *path = selectedPath;
    }
    CoTaskMemFree(selectedPath);
    if (selected != nullptr) {
        selected->Release();
    }
    if (dialog != nullptr) {
        dialog->Release();
    }
    CoUninitialize();
    if (FAILED(result)) {
        return false;
    }
    if (save) {
        RememberFileDialogDirectory(*path);
    }
    return true;
}

/// Builds a suggested save filename with the current local date and time.
static std::wstring SuggestedSaveFileName(const wchar_t* prefix, const wchar_t* extension) {
    SYSTEMTIME time = {};
    GetLocalTime(&time);
    wchar_t fileName[128] = {};
    swprintf_s(fileName, L"%ls-%04d%02d%02d-%02d%02d%02d.%ls", prefix, time.wYear, time.wMonth, time.wDay,
        time.wHour, time.wMinute, time.wSecond, extension);
    return fileName;
}

/// Opens the CSV save dialog and saves all current-session NTP records without applying settings drafts.
static void SaveNtpLog() {
    const COMDLG_FILTERSPEC filters[] = {
        COMDLG_FILTERSPEC{ T(TXT_CSV_FILE_TYPE_LABEL), L"*.csv" }
    };
    std::wstring fileName = SuggestedSaveFileName(L"CalClock-NTP-log", L"csv");
    std::wstring path;
    bool selected = ChooseApplicationFile(true, fileName.c_str(), filters, ARRAYSIZE(filters),
        T(TXT_NTP_SAVE_LOG_LABEL), &path);
    if (!selected) {
        return;
    }
    bool saved = WriteNtpLogCsv(path);
    if (!saved) {
        MessageBoxW(hSettings, T(TXT_NTP_LOG_EXPORT_FAILED), T(TXT_SETTINGS), MB_OK | MB_ICONERROR);
    }
}

/// Inserts one synchronization record with localized measurement, failure, and group-result details.
static void InsertNtpLogEntry(const NtpQueryLogEntry& entry, size_t logIndex) {
    std::wstring timestamp = FormatNtpLogTime(entry.completedTime);
    LVITEMW item = {};
    item.mask = LVIF_TEXT | LVIF_PARAM;
    item.iItem = ListView_GetItemCount(hNtpLogList);
    item.pszText = timestamp.data();
    item.lParam = static_cast<LPARAM>(logIndex);
    int row = ListView_InsertItem(hNtpLogList, &item);
    if (row < 0) {
        return;
    }
    ListView_SetItemText(hNtpLogList, row, 1, const_cast<wchar_t*>(entry.server.c_str()));
    std::wstring status = FormatNtpLogStatus(entry);
    ListView_SetItemText(hNtpLogList, row, 2, status.data());
}

/// Compares stable history indices by the chosen NTP log column, retaining insertion order for equal values.
static int CALLBACK CompareNtpLogEntries(LPARAM left, LPARAM right, LPARAM sortData) {
    UNREFERENCED_PARAMETER(sortData);
    size_t leftIndex = static_cast<size_t>(left);
    size_t rightIndex = static_cast<size_t>(right);
    if (leftIndex >= ntpSynchronizationLog.size() || rightIndex >= ntpSynchronizationLog.size()) {
        return 0;
    }
    const NtpQueryLogEntry& leftEntry = ntpSynchronizationLog[leftIndex];
    const NtpQueryLogEntry& rightEntry = ntpSynchronizationLog[rightIndex];
    int comparison = 0;
    if (ntpLogSortColumn == 0) {
        if (leftEntry.completedTime < rightEntry.completedTime) {
            comparison = -1;
        } else if (leftEntry.completedTime > rightEntry.completedTime) {
            comparison = 1;
        }
    } else if (ntpLogSortColumn == 1) {
        comparison = _wcsicmp(leftEntry.server.c_str(), rightEntry.server.c_str());
    } else if (ntpLogSortColumn == 2) {
        std::wstring leftStatus = FormatNtpLogStatus(leftEntry);
        std::wstring rightStatus = FormatNtpLogStatus(rightEntry);
        comparison = wcscmp(leftStatus.c_str(), rightStatus.c_str());
    }
    if (comparison != 0) {
        return ntpLogSortAscending ? comparison : -comparison;
    }
    if (leftIndex < rightIndex) {
        return -1;
    }
    return leftIndex > rightIndex ? 1 : 0;
}

/// Applies the chosen NTP log order and marks its heading without changing the chronological source history.
static void ApplyNtpLogSort() {
    if (hNtpLogList == nullptr || ntpLogSortColumn < 0 || ntpLogSortColumn >= 3) {
        return;
    }
    ListView_SortItems(hNtpLogList, CompareNtpLogEntries, 0);
    HWND header = ListView_GetHeader(hNtpLogList);
    if (header == nullptr) {
        return;
    }
    for (int column = 0; column < 3; column++) {
        HDITEMW item = {};
        item.mask = HDI_FORMAT;
        if (!Header_GetItem(header, column, &item)) {
            continue;
        }
        item.fmt &= ~(HDF_SORTUP | HDF_SORTDOWN);
        if (column == ntpLogSortColumn) {
            item.fmt |= ntpLogSortAscending ? HDF_SORTUP : HDF_SORTDOWN;
        }
        Header_SetItem(header, column, &item);
    }
}

/// Fits pending NTP log columns on display or after the first batch, reserving each heading's sort-arrow
/// space.
static void InitializeNtpLogColumnWidths() {
    bool timePageVisible = hTimePage != nullptr
        && (GetWindowLongPtrW(hTimePage, GWL_STYLE) & WS_VISIBLE) != 0;
    if (ntpLogColumnsInitialized || hNtpLogList == nullptr || !timePageVisible) {
        return;
    }
    HWND header = ListView_GetHeader(hNtpLogList);
    if (header == nullptr || Header_GetItemCount(header) != 3) {
        return;
    }
    HDC dc = GetDC(header);
    if (dc == nullptr) {
        return;
    }
    HFONT font = reinterpret_cast<HFONT>(SendMessageW(header, WM_GETFONT, 0, 0));
    HGDIOBJ previousFont = font == nullptr ? nullptr : SelectObject(dc, font);
    for (int column = 0; column < 3; column++) {
        wchar_t caption[256] = {};
        HDITEMW item = {};
        item.mask = HDI_TEXT;
        item.pszText = caption;
        item.cchTextMax = static_cast<int>(ARRAYSIZE(caption));
        if (!Header_GetItem(header, column, &item)) {
            continue;
        }
        SIZE extent = {};
        GetTextExtentPoint32W(dc, caption, static_cast<int>(wcslen(caption)), &extent);
        int headerWidth = static_cast<int>(extent.cx) + 2 * GetSystemMetrics(SM_CXEDGE) + 8
            + GetSystemMetrics(SM_CXVSCROLL);
        ListView_SetColumnWidth(hNtpLogList, column, LVSCW_AUTOSIZE);
        int contentWidth = ListView_GetColumnWidth(hNtpLogList, column);
        ListView_SetColumnWidth(hNtpLogList, column, std::max(headerWidth, contentWidth));
    }
    if (previousFont != nullptr && previousFont != HGDI_ERROR) {
        SelectObject(dc, previousFont);
    }
    ReleaseDC(header, dc);
    ntpLogColumnsInitialized = true;
    ScrollNtpLogToBottom();
}

/// Fits monitor columns once on display using native content widths and room for heading sort arrows.
static void InitializeMonitorColumnWidths() {
    bool monitorListVisible = hGeneralPage != nullptr
        && hMonitorList != nullptr
        && (GetWindowLongPtrW(hGeneralPage, GWL_STYLE) & WS_VISIBLE) != 0
        && (GetWindowLongPtrW(hMonitorList, GWL_STYLE) & WS_VISIBLE) != 0
        && !monitorListEntries.empty();
    if (monitorColumnsInitialized || hMonitorList == nullptr || !monitorListVisible) {
        return;
    }
    HWND header = ListView_GetHeader(hMonitorList);
    if (header == nullptr || Header_GetItemCount(header) != MONITOR_COLUMN_COUNT) {
        return;
    }
    HDC dc = GetDC(header);
    if (dc == nullptr) {
        return;
    }
    HFONT font = reinterpret_cast<HFONT>(SendMessageW(header, WM_GETFONT, 0, 0));
    HGDIOBJ previousFont = font == nullptr ? nullptr : SelectObject(dc, font);
    for (int column = 0; column < MONITOR_COLUMN_COUNT; column++) {
        wchar_t caption[256] = {};
        HDITEMW item = {};
        item.mask = HDI_TEXT;
        item.pszText = caption;
        item.cchTextMax = static_cast<int>(ARRAYSIZE(caption));
        if (!Header_GetItem(header, column, &item)) {
            continue;
        }
        SIZE extent = {};
        GetTextExtentPoint32W(dc, caption, static_cast<int>(wcslen(caption)), &extent);
        int headerWidth = static_cast<int>(extent.cx) + 2 * GetSystemMetrics(SM_CXEDGE) + 8
            + GetSystemMetrics(SM_CXVSCROLL);
        ListView_SetColumnWidth(hMonitorList, column, LVSCW_AUTOSIZE);
        int contentWidth = ListView_GetColumnWidth(hMonitorList, column);
        ListView_SetColumnWidth(hMonitorList, column, std::max(headerWidth, contentWidth));
    }
    if (previousFont != nullptr && previousFont != HGDI_ERROR) {
        SelectObject(dc, previousFont);
    }
    ReleaseDC(header, dc);
    monitorColumnsInitialized = true;
}

/// Scrolls the NTP log to its last displayed row using its current native layout.
static void ScrollNtpLogToBottom() {
    if (hNtpLogList == nullptr) {
        return;
    }
    int lastRow = ListView_GetItemCount(hNtpLogList) - 1;
    if (lastRow >= 0) {
        ListView_EnsureVisible(hNtpLogList, lastRow, FALSE);
    }
}

/// Selects or reverses NTP log sorting after a column-heading click.
static void SortNtpLogByColumn(int column) {
    if (hNtpLogList == nullptr || column < 0 || column >= 3) {
        return;
    }
    if (ntpLogSortColumn == column) {
        ntpLogSortAscending = !ntpLogSortAscending;
    } else {
        ntpLogSortColumn = column;
        ntpLogSortAscending = true;
    }
    WindowRedrawScope redraw(hNtpLogList);
    ApplyNtpLogSort();
}

/// Extends the synchronization status to the fixed log top while preserving its position and width.
static void UpdateNtpLabelHeights() {
    RECT bounds = {};
    RECT log = {};
    if (hNtpStatus == nullptr || !GetWindowRect(hNtpStatus, &bounds) || !GetWindowRect(hNtpLogList, &log)) {
        return;
    }
    MapWindowPoints(HWND_DESKTOP, hTimePage, reinterpret_cast<POINT*>(&bounds), 2);
    MapWindowPoints(HWND_DESKTOP, hTimePage, reinterpret_cast<POINT*>(&log), 2);
    int height = log.top - bounds.top;
    if (height > 0) {
        SetControlPosition(hNtpStatus, bounds.left, bounds.top, bounds.right - bounds.left, height);
    }
}

/// Keeps native report headers within the button height budget while preserving their font, theme and
/// sorting.
static LRESULT CALLBACK SettingsReportHeaderSubclassProc(HWND window, UINT message, WPARAM wParam,
        LPARAM lParam, UINT_PTR subclassId, DWORD_PTR referenceData) {
    UNREFERENCED_PARAMETER(referenceData);
    LRESULT result = DefSubclassProc(window, message, wParam, lParam);
    if (message == HDM_LAYOUT && result != FALSE) {
        HDLAYOUT* layout = reinterpret_cast<HDLAYOUT*>(lParam);
        if (layout != nullptr
                && layout->pwpos != nullptr
                && layout->prc != nullptr
                && layout->pwpos->cy > SettingsDialogHeight(11)) {
            layout->prc->top -= layout->pwpos->cy - SettingsDialogHeight(11);
            layout->pwpos->cy = SettingsDialogHeight(11);
        }
    } else if (message == WM_NCDESTROY) {
        RemoveWindowSubclass(window, SettingsReportHeaderSubclassProc, subclassId);
    }
    return result;
}

/// Selects all NTP log rows with Ctrl+A, restores bottom scrolling after native layout or redraw changes,
/// and releases the log handle and subclass on destruction.
static LRESULT CALLBACK NtpLogSubclassProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    UNREFERENCED_PARAMETER(referenceData);
    bool selectAll =
        msg == WM_KEYDOWN && wParam == L'A' && GetKeyState(VK_CONTROL) < 0 && GetKeyState(VK_MENU) >= 0;
    if (selectAll) {
        ListView_SetItemState(window, -1, LVIS_SELECTED, LVIS_SELECTED);
        return 0;
    }
    if (msg == WM_NCDESTROY) {
        if (window == hNtpLogList) {
            hNtpLogList = nullptr;
        }
        RemoveWindowSubclass(window, NtpLogSubclassProc, subclassId);
    }
    LRESULT result = DefSubclassProc(window, msg, wParam, lParam);
    if (msg == WM_SETFONT || msg == WM_THEMECHANGED) {
        UpdateSettingsReportMetrics(window);
    }
    bool layoutChanged = msg == WM_SIZE
        || msg == WM_SETFONT
        || msg == WM_THEMECHANGED
        || msg == WM_SETREDRAW && wParam != FALSE
        || msg == WM_SHOWWINDOW && wParam != FALSE;
    if (layoutChanged) {
        ScrollNtpLogToBottom();
    }
    return result;
}

/// Populates the NTP list headings and restores all records collected since application startup.
static void InitializeNtpLog() {
    if (hNtpLogList == nullptr) {
        return;
    }
    ntpLogColumnsInitialized = false;
    ListView_SetExtendedListViewStyle(hNtpLogList,
        LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER | LVS_EX_GRIDLINES);
    LVCOLUMNW column = {};
    column.mask = LVCF_TEXT | LVCF_SUBITEM;
    for (int index = 0; index < 3; index++) {
        column.iSubItem = index;
        column.pszText = const_cast<wchar_t*>(T(NTP_LOG_COLUMN_TEXT_IDS[index]));
        ListView_InsertColumn(hNtpLogList, index, &column);
    }
    for (size_t index = 0; index < ntpSynchronizationLog.size(); index++) {
        InsertNtpLogEntry(ntpSynchronizationLog[index], index);
    }
    ApplyNtpLogSort();
    SetWindowSubclass(ListView_GetHeader(hNtpLogList), SettingsReportHeaderSubclassProc,
        SETTINGS_REPORT_HEADER_SUBCLASS_ID, 0);
    SetWindowSubclass(hNtpLogList, NtpLogSubclassProc, ID_NTP_LOG, 0);
    ScrollNtpLogToBottom();
}

/// Appends a completed query group, refits columns when the log was empty, and preserves later column widths.
static void AppendNtpSynchronizationLog(const std::vector<NtpQueryLogEntry>& entries) {
    size_t firstNewEntry = ntpSynchronizationLog.size();
    ntpSynchronizationLog.insert(ntpSynchronizationLog.end(), entries.begin(), entries.end());
    if (hNtpLogList == nullptr || entries.empty()) {
        return;
    }
    bool wasEmpty = ListView_GetItemCount(hNtpLogList) == 0;
    WindowRedrawScope redraw(hNtpLogList);
    for (size_t index = firstNewEntry; index < ntpSynchronizationLog.size(); index++) {
        InsertNtpLogEntry(ntpSynchronizationLog[index], index);
    }
    ApplyNtpLogSort();
    if (wasEmpty) {
        ntpLogColumnsInitialized = false;
    }
    InitializeNtpLogColumnWidths();
    ScrollNtpLogToBottom();
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
        status = T(TXT_NTP_STATUS_SYSTEM);
    } else if (!winsockReady) {
        status = T(TXT_NTP_STATUS_FAILED);
    } else if (ntpQueryRunning) {
        status = T(TXT_NTP_STATUS_WAITING);
    } else if (ntpTimeValid && ntpLastQueryFailed) {
        LONGLONG offset100Nanoseconds = ntpOffset100Nanoseconds.load();
        status = T(TXT_NTP_STATUS_RETAINED);
        status += L" " + ntpActiveServer + L" (Θ = " + FormatNtpLogOffset(offset100Nanoseconds) + L")";
    } else if (ntpTimeValid) {
        LONGLONG offset100Nanoseconds = ntpOffset100Nanoseconds.load();
        status = T(TXT_NTP_STATUS_SYNCHRONIZED);
        status += L" " + ntpActiveServer + L" (Θ = " + FormatNtpLogOffset(offset100Nanoseconds) + L")";
    } else if (lastNtpAttemptTick != 0) {
        status = T(TXT_NTP_STATUS_FAILED);
    } else {
        status = T(TXT_NTP_STATUS_WAITING);
    }
    if (GetControlText(hNtpStatus) != status) {
        SetControlText(hNtpStatus, status.c_str());
    }
}

/// Hides inactive pages before revealing the selected page, updates its state and mnemonics, and ends
/// inapplicable previews.
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
    if (activePage == hGeneralPage) {
        InitializeMonitorColumnWidths();
    }
    if (activePage == hTimePage) {
        InitializeNtpLogColumnWidths();
        ScrollNtpLogToBottom();
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

/// Orders Appearance controls spatially while always keeping Default Appearance last on the page.
static bool SettingsControlComesFirst(const PositionedControl& left, const PositionedControl& right) {
    if (left.window == hDefaultAppearanceButton) {
        return false;
    }
    if (right.window == hDefaultAppearanceButton) {
        return true;
    }
    return left.rect.top == right.rect.top
        ? left.rect.left < right.rect.left
        : left.rect.top < right.rect.top;
}

/// Collects visible, enabled tab-stop controls for the active page, using spatial order on the Appearance
/// page.
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
        if (control == nullptr
                || GetParent(SettingsEdit::GetFrame(control)) != page
                || !IsWindowVisible(control)
                || !IsWindowEnabled(control)) {
            continue;
        }
        LONG_PTR style = GetWindowLongPtrW(control, GWL_STYLE);
        RECT rect = {};
        if ((style & WS_TABSTOP) != 0 && GetWindowRect(SettingsEdit::GetFrame(control), &rect)) {
            positionedControls.push_back(PositionedControl{ control, rect });
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

/// Rebuilds numbered widget captions with redraw suspended, optionally preserving selection by persistent
/// widget IDs.
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
        int item = static_cast<int>(SendMessageW(hWidgetList, LB_ADDSTRING, 0,
            reinterpret_cast<LPARAM>(label.c_str())));
        SendMessageW(hWidgetList, LB_SETITEMDATA, item, settingsDraft[index].id);
    }
    if (!settingsDraft.empty()) {
        selectedDraftIndex = std::clamp(selectedDraftIndex, 0, static_cast<int>(settingsDraft.size()) - 1);
        bool restored = false;
        for (size_t index = 0; index < settingsDraft.size(); index++) {
            if (std::find(selectedIds.begin(), selectedIds.end(), settingsDraft[index].id)
                    != selectedIds.end()) {
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

/// Selects the item whose stored zone key matches case-insensitively, defaulting to the first item when
/// absent.
static void SelectTimeZoneInCombo(const std::wstring& key, HWND combo = hTimeZoneCombo) {
    int selected = 0;
    int count = static_cast<int>(SendMessageW(combo, CB_GETCOUNT, 0, 0));
    for (int index = 0; index < count; index++) {
        size_t zoneIndex = static_cast<size_t>(SendMessageW(combo, CB_GETITEMDATA, index, 0));
        if (zoneIndex < timeZones.size()
                && _wcsicmp(timeZones[zoneIndex].TimeZoneKeyName, key.c_str()) == 0) {
            selected = index;
            break;
        }
    }
    SetComboSelection(combo, selected);
}

/// Compares one numeric monitor value without converting it to displayed text.
template<typename Value>
static int CompareMonitorValues(Value left, Value right) {
    if (left < right) {
        return -1;
    }
    if (left > right) {
        return 1;
    }
    return 0;
}

/// Compares exact fractional refresh rates, placing unavailable values before known values in ascending
/// order.
static int CompareMonitorRefreshRates(const DISPLAYCONFIG_RATIONAL& left,
        const DISPLAYCONFIG_RATIONAL& right) {
    const bool leftKnown = left.Numerator != 0 && left.Denominator != 0;
    const bool rightKnown = right.Numerator != 0 && right.Denominator != 0;
    const int availability = CompareMonitorValues(leftKnown, rightKnown);
    if (availability != 0 || !leftKnown) {
        return availability;
    }
    const ULONGLONG leftValue = static_cast<ULONGLONG>(left.Numerator) * right.Denominator;
    const ULONGLONG rightValue = static_cast<ULONGLONG>(right.Numerator) * left.Denominator;
    return CompareMonitorValues(leftValue, rightValue);
}

/// Compares stable monitor indices by the chosen column, retaining source order for equal values.
static int CALLBACK CompareMonitorListEntries(LPARAM left, LPARAM right, LPARAM sortData) {
    UNREFERENCED_PARAMETER(sortData);
    const std::size_t leftIndex = static_cast<std::size_t>(left);
    const std::size_t rightIndex = static_cast<std::size_t>(right);
    if (leftIndex >= monitorListEntries.size()
            || rightIndex >= monitorListEntries.size()
            || monitorSortColumn < 0
            || monitorSortColumn >= MONITOR_COLUMN_COUNT) {
        return 0;
    }
    const MonitorListEntry& leftEntry = monitorListEntries[leftIndex];
    const MonitorListEntry& rightEntry = monitorListEntries[rightIndex];
    int comparison = 0;
    if (monitorSortColumn == 3) {
        comparison =
            CompareMonitorRefreshRates(leftEntry.details.refreshRate, rightEntry.details.refreshRate);
    } else if (monitorSortColumn == 4) {
        const UINT leftDepth = leftEntry.details.bitsPerColor != 0
            ? leftEntry.details.bitsPerColor
            : leftEntry.details.bitsPerPixel;
        const UINT rightDepth = rightEntry.details.bitsPerColor != 0
            ? rightEntry.details.bitsPerColor
            : rightEntry.details.bitsPerPixel;
        comparison = CompareMonitorValues(leftDepth, rightDepth);
        if (comparison == 0) {
            comparison = _wcsicmp(leftEntry.text[4].c_str(), rightEntry.text[4].c_str());
        }
    } else {
        comparison =
            _wcsicmp(leftEntry.text[monitorSortColumn].c_str(), rightEntry.text[monitorSortColumn].c_str());
    }
    if (comparison != 0) {
        return monitorSortAscending ? comparison : -comparison;
    }
    if (leftIndex < rightIndex) {
        return -1;
    }
    return leftIndex > rightIndex ? 1 : 0;
}

/// Applies the chosen monitor order and heading arrow without changing source monitor identities.
static void ApplyMonitorListSort() {
    if (hMonitorList == nullptr || monitorSortColumn < 0 || monitorSortColumn >= MONITOR_COLUMN_COUNT) {
        return;
    }
    ListView_SortItems(hMonitorList, CompareMonitorListEntries, 0);
    HWND header = ListView_GetHeader(hMonitorList);
    if (header == nullptr) {
        return;
    }
    for (int column = 0; column < MONITOR_COLUMN_COUNT; column++) {
        HDITEMW item{};
        item.mask = HDI_FORMAT;
        if (!Header_GetItem(header, column, &item)) {
            continue;
        }
        item.fmt &= ~(HDF_SORTUP | HDF_SORTDOWN);
        if (column == monitorSortColumn) {
            item.fmt |= monitorSortAscending ? HDF_SORTUP : HDF_SORTDOWN;
        }
        Header_SetItem(header, column, &item);
    }
}

/// Selects or reverses monitor sorting after a heading click without changing column widths.
static void SortMonitorListByColumn(int column) {
    if (hMonitorList == nullptr || column < 0 || column >= MONITOR_COLUMN_COUNT) {
        return;
    }
    if (monitorSortColumn == column) {
        monitorSortAscending = !monitorSortAscending;
    } else {
        monitorSortColumn = column;
        monitorSortAscending = true;
    }
    const bool updating = updatingSettingsControls;
    updatingSettingsControls = true;
    WindowRedrawScope redraw(hMonitorList);
    ApplyMonitorListSort();
    updatingSettingsControls = updating;
}

/// Reads checked source monitor identities independently of selected or sorted row positions.
static std::vector<size_t> CheckedMonitorIndices() {
    std::vector<size_t> checked;
    int count = ListView_GetItemCount(hMonitorList);
    for (int row = 0; row < count; row++) {
        if (!ListView_GetCheckState(hMonitorList, row)) {
            continue;
        }
        LVITEMW item = {};
        item.mask = LVIF_PARAM;
        item.iItem = row;
        if (ListView_GetItem(hMonitorList, &item) && static_cast<size_t>(item.lParam) < monitorListEntries.size()) {
            checked.push_back(static_cast<size_t>(item.lParam));
        }
    }
    std::sort(checked.begin(), checked.end());
    return checked;
}

/// Selects all monitor rows with Ctrl+A while retaining native checkbox, mouse and keyboard handling.
static LRESULT CALLBACK MonitorListSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    UNREFERENCED_PARAMETER(referenceData);
    bool selectAll =
        message == WM_KEYDOWN && wParam == L'A' && GetKeyState(VK_CONTROL) < 0 && GetKeyState(VK_MENU) >= 0;
    if (selectAll) {
        ListView_SetItemState(window, -1, LVIS_SELECTED, LVIS_SELECTED);
        return 0;
    }
    if (message == WM_NCDESTROY) {
        if (hMonitorList == window) {
            hMonitorList = nullptr;
        }
        RemoveWindowSubclass(window, MonitorListSubclassProc, subclassId);
    }
    LRESULT result = DefSubclassProc(window, message, wParam, lParam);
    if (message == WM_SETFONT || message == WM_THEMECHANGED) {
        UpdateSettingsReportMetrics(window);
    }
    return result;
}

/// Creates localized report columns with native checkboxes, selection, grid lines and double buffering.
static void InitializeMonitorList() {
    monitorColumnsInitialized = false;
    monitorListEntries.clear();
    if (hMonitorList == nullptr) {
        return;
    }
    ListView_SetExtendedListViewStyle(hMonitorList,
        LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER | LVS_EX_CHECKBOXES);
    LVCOLUMNW column = {};
    column.mask = LVCF_TEXT | LVCF_SUBITEM;
    for (int index = 0; index < MONITOR_COLUMN_COUNT; index++) {
        column.iSubItem = index;
        column.pszText = const_cast<wchar_t*>(T(MONITOR_COLUMN_TEXT_IDS[index]));
        ListView_InsertColumn(hMonitorList, index, &column);
    }
    SetWindowSubclass(ListView_GetHeader(hMonitorList), SettingsReportHeaderSubclassProc,
        SETTINGS_REPORT_HEADER_SUBCLASS_ID, 0);
    SetWindowSubclass(hMonitorList, MonitorListSubclassProc, ID_MONITOR_LIST, 0);
}

/// Rebuilds report values from the current monitor snapshot, retaining source identities in item data.
static void PopulateMonitorList() {
    std::vector<std::wstring> selectedDevices;
    for (int row = ListView_GetNextItem(hMonitorList, -1, LVNI_SELECTED);
            row >= 0;
            row = ListView_GetNextItem(hMonitorList, row, LVNI_SELECTED)) {
        LVITEMW item = {};
        item.mask = LVIF_PARAM;
        item.iItem = row;
        if (ListView_GetItem(hMonitorList, &item)
                && static_cast<size_t>(item.lParam) < monitorListEntries.size()) {
            selectedDevices.push_back(monitorListEntries[static_cast<size_t>(item.lParam)].monitor.device);
        }
    }
    ListView_DeleteAllItems(hMonitorList);
    const std::vector<MonitorDetails> details = ReadMonitorDetails(displayMonitors);
    monitorListEntries.resize(displayMonitors.size());
    for (size_t index = 0; index < displayMonitors.size(); index++) {
        MonitorListEntry& entry = monitorListEntries[index];
        entry.monitor = displayMonitors[index];
        entry.details = details[index];
        entry.text[0] = MonitorDisplayName(entry.monitor.device);
        if (entry.monitor.primary) {
            entry.text[0] += std::wstring(L" (") + T(TXT_MONITOR_PRIMARY_LABEL) + L")";
        }
        entry.text[1] = entry.details.model.empty() ? L"—" : entry.details.model;
        wchar_t value[96] = {};
        swprintf_s(value, L"%ld × %ld", entry.monitor.rect.right - entry.monitor.rect.left,
            entry.monitor.rect.bottom - entry.monitor.rect.top);
        entry.text[2] = value;
        entry.text[3] = MonitorRefreshRateText(entry.details);
        entry.text[4] = MonitorBitDepthText(entry.details, appLanguage);
        entry.text[5] = MonitorColorFormatText(entry.details.colorEncoding);
        entry.text[6] = MonitorColorSpaceText(entry.details.colorSpace);
        swprintf_s(value, L"x=%ld, y=%ld", entry.monitor.rect.left, entry.monitor.rect.top);
        entry.text[7] = value;
        LVITEMW item = {};
        item.mask = LVIF_TEXT | LVIF_PARAM;
        item.iItem = static_cast<int>(index);
        item.pszText = entry.text[0].data();
        item.lParam = static_cast<LPARAM>(index);
        int row = ListView_InsertItem(hMonitorList, &item);
        for (int column = 1; column < MONITOR_COLUMN_COUNT; column++) {
            ListView_SetItemText(hMonitorList, row, column, entry.text[column].data());
        }
        if (std::find(selectedDevices.begin(), selectedDevices.end(), entry.monitor.device)
                != selectedDevices.end()) {
            ListView_SetItemState(hMonitorList, row, LVIS_SELECTED, LVIS_SELECTED);
        }
    }
    if (ListView_GetNextItem(hMonitorList, -1, LVNI_SELECTED) < 0 && !monitorListEntries.empty()) {
        ListView_SetItemState(hMonitorList, 0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
    }
    ApplyMonitorListSort();
    UpdateSettingsReportMetrics(hMonitorList);
}

/// Refreshes changed monitor rows and restores checked devices without changing row selection or user column
/// widths.
static void LoadMonitorSelection(const WidgetConfig& config) {
    if (hMonitorList == nullptr) {
        return;
    }
    bool previousUpdating = updatingSettingsControls;
    updatingSettingsControls = true;
    WindowRedrawScope redraw(hMonitorList);
    RefreshDisplayMonitors();
    bool changed = displayMonitors.size() != monitorListEntries.size()
        || ListView_GetItemCount(hMonitorList) != static_cast<int>(displayMonitors.size());
    for (size_t index = 0; !changed && index < displayMonitors.size(); index++) {
        const DisplayMonitor& current = displayMonitors[index];
        const DisplayMonitor& previous = monitorListEntries[index].monitor;
        changed = current.device != previous.device
            || current.primary != previous.primary
            || !EqualRect(&current.rect, &previous.rect);
    }
    if (changed) {
        PopulateMonitorList();
    }
    bool anyChecked = false;
    for (const MonitorListEntry& entry : monitorListEntries) {
        anyChecked = anyChecked || ContainsMonitorDevice(config.monitorDevices, entry.monitor.device);
    }
    int count = ListView_GetItemCount(hMonitorList);
    for (int row = 0; row < count; row++) {
        LVITEMW item = {};
        item.mask = LVIF_PARAM;
        item.iItem = row;
        if (!ListView_GetItem(hMonitorList, &item)
                || static_cast<size_t>(item.lParam) >= monitorListEntries.size()) {
            continue;
        }
        size_t index = static_cast<size_t>(item.lParam);
        bool checked = ContainsMonitorDevice(config.monitorDevices, monitorListEntries[index].monitor.device)
            || !anyChecked && index == 0;
        if ((ListView_GetCheckState(hMonitorList, row) != FALSE) != checked) {
            ListView_SetCheckState(hMonitorList, row, checked);
        }
    }
    InitializeMonitorColumnWidths();
    updatingSettingsControls = previousUpdating;
}

/// Serializes checked devices in stable source order, defaulting to the first display when none is checked.
static std::wstring GetSelectedMonitorDevices() {
    std::wstring devices;
    if (hMonitorList == nullptr) {
        return devices;
    }
    for (size_t index : CheckedMonitorIndices()) {
        if (!devices.empty()) {
            devices += L';';
        }
        devices += monitorListEntries[index].monitor.device;
    }
    if (devices.empty() && !monitorListEntries.empty()) {
        devices = monitorListEntries.front().monitor.device;
    }
    return devices;
}

/// Handles monitor column sorting, double-click checking and checkbox change notifications.
static bool HandleMonitorListNotification(NMHDR* header, LRESULT* result) {
    if (header == nullptr || header->hwndFrom != hMonitorList) {
        return false;
    }
    *result = 0;
    if (header->code == LVN_COLUMNCLICK) {
        SortMonitorListByColumn(reinterpret_cast<NMLISTVIEW*>(header)->iSubItem);
    } else if (header->code == NM_DBLCLK) {
        int row = reinterpret_cast<NMITEMACTIVATE*>(header)->iItem;
        if (row >= 0) {
            ListView_SetCheckState(hMonitorList, row, !ListView_GetCheckState(hMonitorList, row));
        }
    } else if (header->code == NM_CUSTOMDRAW) {
        NMLVCUSTOMDRAW* drawing = reinterpret_cast<NMLVCUSTOMDRAW*>(header);
        if (drawing->nmcd.dwDrawStage == CDDS_PREPAINT) {
            *result = CDRF_NOTIFYPOSTPAINT;
        } else if (drawing->nmcd.dwDrawStage == CDDS_POSTPAINT
                && GetFocus() == hMonitorList
                && (SendMessageW(hMonitorList, WM_QUERYUISTATE, 0, 0) & UISF_HIDEFOCUS) == 0) {
            int row = ListView_GetNextItem(hMonitorList, -1, LVNI_FOCUSED);
            RECT bounds = {};
            RECT client = {};
            if (row >= 0
                    && ListView_GetItemRect(hMonitorList, row, &bounds, LVIR_BOUNDS)
                    && GetClientRect(hMonitorList, &client)) {
                bounds.left = client.left + 1;
                bounds.right = client.right - 1;
                DrawFocusRect(drawing->nmcd.hdc, &bounds);
            }
        }
    } else if (header->code == LVN_ITEMCHANGED) {
        NMLISTVIEW* change = reinterpret_cast<NMLISTVIEW*>(header);
        if (!updatingSettingsControls
                && (change->uChanged & LVIF_STATE) != 0
                && ((change->uOldState ^ change->uNewState) & LVIS_STATEIMAGEMASK) != 0) {
            UpdateSettingsApplyButton();
        }
    } else {
        return false;
    }
    return true;
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

/// Copies appearance controls into a widget configuration, mapping selector indices to supported sizes and
/// modes.
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
    if (config.type != WIDGET_CALENDAR || IsWindowEnabled(hWidgetAntialiasCombo)) {
        config.fontAntialiasing = SelectedFontAntialiasing(hWidgetAntialiasCombo, config.fontAntialiasing);
    }
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
    config.alarmBackgroundColor = static_cast<COLORREF>(GetWindowLongPtrW(hAlarmBackgroundColorButton,
        GWLP_USERDATA));
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

/// Reveals and paints the prepared controls before hiding controls that no longer apply to the selected
/// widget.
static void UpdateSettingControlVisibility() {
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
    std::vector<ControlVisibility> controlStates = {
        { hMonitorLabel, fullscreen },
        { hMonitorList, fullscreen },
        { hBlackoutMonitorsCheck, fullscreen },
        { hSizeLabel, hasSize },
        { hSizeCombo, hasSize },
        { hFontSizeLabel, digital },
        { hFontSizeTrackBar, digital },
        { hFontSizeValue, digital },
        { hFontLabel, hasTextFont },
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
        { hPanelTopFontLabel, panel },
        { hPanelTopFontButton, panel },
        { hPanelTimeFontLabel, panel },
        { hPanelTimeFontButton, panel },
        { hPanelBottomFontLabel, panel },
        { hPanelBottomFontButton, panel },
        { hDefaultAppearanceButton, true },
        { hBackgroundColorButton, digital },
        { hShowTodayCheck, type == WIDGET_CALENDAR },
        { hWeekNumbersCheck, calendar },
        { hSundayFirstCheck, calendar },
        { hDateFormatLabel, calendar },
        { hDateFormatCombo, calendar },
        { hPanelTimeNoticesCheck, panel },
        { hTimeFormatLabel, digital || panel },
        { hTimeFormatCombo, digital || panel },
        { hShowAmPmCheck, digital || panel }
    };
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
            controlStates.push_back(ControlVisibility{ control, panel });
        }
    }
    UpdateSettingsTextControlLayout(hGeneralPage, &controlStates);
    UpdateSettingsTextControlLayout(hAppearancePage, &controlStates);
    for (const ControlVisibility& state : controlStates) {
        if (state.visible && state.control != nullptr) {
            SetControlVisible(state.control, true);
            RedrawWindow(SettingsEdit::GetFrame(state.control), nullptr, nullptr,
                RDW_UPDATENOW | RDW_ALLCHILDREN);
        }
    }
    for (const ControlVisibility& state : controlStates) {
        if (!state.visible) {
            SetControlVisible(state.control, false);
        }
    }
}

/// Updates control enabled states for the selected widget and temporarily clears inapplicable checkbox
/// values. When requested, prepares the final layout before replacing the visible controls.
static void UpdateSettingControlAvailability(bool updateLayout) {
    if (selectedDraftIndex < 0 || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
        return;
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
        size_t zoneIndex = static_cast<size_t>(SendMessageW(hTimeZoneCombo, CB_GETITEMDATA,
            timeZoneSelection, 0));
        if (zoneIndex < timeZones.size()) {
            timeConfiguration.timeZoneKey = timeZones[zoneIndex].TimeZoneKeyName;
        }
    }
    timeConfiguration.timeFormat = static_cast<int>(SendMessageW(hTimeFormatCombo, CB_GETCURSEL, 0, 0));
    bool supportsBorderStyle = !fullscreen && (digital || calendar);
    bool utc = GetCheck(hUtcCheck);
    bool hasSize = type == WIDGET_ANALOG || type == WIDGET_PANEL;
    bool hasTextFont = digital || calendar;
    bool globalThemesDisabled = hDisableThemesCheck == nullptr
        ? themesDisabled
        : GetCheck(hDisableThemesCheck);
    bool widgetThemesDisabled = hWidgetDisableThemesCheck == nullptr
        ? settingsDraft[selectedDraftIndex].disableThemes
        : GetCheck(hWidgetDisableThemesCheck);
    bool calendarFontEnabled = globalThemesDisabled || widgetThemesDisabled || !AreVisualStylesActive();
    bool fontAntialiasingEnabled = type != WIDGET_CALENDAR || calendarFontEnabled;
    if (type == WIDGET_CALENDAR) {
        if (!calendarFontEnabled) {
            SelectFontAntialiasing(hWidgetAntialiasCombo, FONT_ANTIALIAS_CLEARTYPE);
        } else if (!IsWindowEnabled(hWidgetAntialiasCombo)) {
            SelectFontAntialiasing(hWidgetAntialiasCombo, settingsDraft[selectedDraftIndex].fontAntialiasing);
        }
    }
    bool supportsAlarm = WidgetSupportsSound(type);
    bool timeSignalEnabled = supportsAlarm && GetCheck(hTimeSignalEnabledCheck);
    bool generatedTone = IsTimeSignalGeneratorRequired()
        || SendMessageW(hTimeSignalSoundCombo, CB_GETCURSEL, 0, 0) == 0;
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
        int opacityLayout = hasSize ? IDC_LAYOUT_OPACITY_SIZED : IDC_LAYOUT_OPACITY_TOP;
        SetSettingsControlPosition(hOpacityLabel, opacityLayout);
        if (hasTextFont && !panel) {
            SetSettingsControlPosition(hFontLabel, IDC_LAYOUT_FONT);
        }
        if (digital) {
            SetSettingsControlPosition(hLeadingZeroLabel, IDC_LAYOUT_LEADING_TEXT);
        }
        if (type == WIDGET_CALENDAR) {
            SetSettingsControlPosition(hDateFormatLabel, IDC_LAYOUT_DATE_CALENDAR);
        }
    }
    const LRESULT borderStylePosition = SendMessageW(hBorderTrackBar, TBM_GETPOS, 0, 0);
    std::vector<ControlState> controlStates = {
        { hTransparentBackgroundCheck, !fullscreen },
        { hPaddingTrackBar, digital },
        { hBorderTrackBar, supportsBorderStyle },
        { hBorderColorButton, supportsBorderStyle && borderStylePosition == DIGITAL_BORDER_TOOL_WINDOW },
        { hBorderWidthTrackBar, !fullscreen },
        { hFontLabel, digital || calendarFontEnabled },
        { hFontButton, digital || calendarFontEnabled },
        { hWidgetAntialiasLabel, fontAntialiasingEnabled },
        { hWidgetAntialiasCombo, fontAntialiasingEnabled },
        { hSecondsCheck, supportsSeconds },
        { hTimeFormatCombo, (digital || panel) && !WidgetUsesUtcTime(timeConfiguration) },
        { hShowAmPmCheck, supportsAmPm },
        { hUtcTextCheck, (digital || panel) && utc },
        { hPanelTimeNoticesCheck, panel },
        { hTimeZoneLabel, !utc },
        { hTimeZoneCombo, !utc },
        { hTopmostCheck, !fullscreen },
        { hOpacityTrackBar, !fullscreen },
        { hSoundsMutedCheck, supportsAlarm },
        { hAlarmEnabledCheck, supportsAlarm },
        { hAudioOutputLabel, timeSignalEnabled },
        { hAudioOutputCombo, timeSignalEnabled && generatedTone },
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
        controlStates.push_back(ControlState{
            hAlarmDayChecks[day],
            supportsAlarm && GetCheck(hAlarmEnabledCheck)
        });
    }
    for (HWND radio : hTimeSignalIntervalRadios) {
        controlStates.push_back(ControlState{ radio, supportsAlarm && GetCheck(hTimeSignalEnabledCheck) });
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
            if (GetPropW(control, SETTINGS_COLOR_BUTTON_PROPERTY) != nullptr) {
                continue;
            }
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
    int audioOutputSelection = 0;
    if (generatedTone) {
        const std::wstring& selected = settingsDraft[selectedDraftIndex].timeSignalOutputDevice;
        for (size_t index = 0; index < settingsAudioOutputs.size(); index++) {
            if (settingsAudioOutputs[index].id == selected) {
                audioOutputSelection = static_cast<int>(index) + 1;
                break;
            }
        }
    }
    SetComboSelection(hAudioOutputCombo, audioOutputSelection);
    if (calendar) {
        UpdateFontDescription(settingsDraft[selectedDraftIndex]);
    }
    if (updateLayout) {
        AlignSettingsControls();
        UpdateSettingControlVisibility();
        InitializeMonitorColumnWidths();
    }
}

/// Fits dropdowns to the work area with at most thirteen whole rows and retains native scrolling.
/// Removes its subclass when the native list window is destroyed.
static LRESULT CALLBACK ComboBoxDropDownSubclassProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    if (msg == WM_WINDOWPOSCHANGING) {
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
                LONG currentWidth = position->flags & SWP_NOSIZE
                    ? current.right - current.left
                    : position->cx;
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
                if ((position->flags & SWP_HIDEWINDOW) == 0) {
                    HWND nativeCombo = GetSettingsComboBox(combo);
                    int count = static_cast<int>(SendMessageW(nativeCombo, CB_GETCOUNT, 0, 0));
                    int rowHeight = static_cast<int>(SendMessageW(nativeCombo, CB_GETITEMHEIGHT, 0, 0));
                    RECT client = {};
                    if (count >= 0 && rowHeight > 0 && GetClientRect(window, &client)) {
                        LONG chromeHeight = current.bottom - current.top - (client.bottom - client.top);
                        LONG workHeight = information.rcWork.bottom - information.rcWork.top;
                        LONG below = std::clamp(information.rcWork.bottom - comboRect.bottom, 0L, workHeight);
                        LONG above = std::clamp(comboRect.top - information.rcWork.top, 0L, workHeight);
                        int rows = std::min(count, SETTINGS_COMBO_VISIBLE_ITEMS);
                        LONG available = std::max(below, above);
                        rows = std::min(rows,
                            static_cast<int>(std::max(0L, available - chromeHeight) / rowHeight));
                        LONG height = rows * rowHeight + chromeHeight;
                        LONG top = height <= below ? comboRect.bottom : comboRect.top - height;
                        top = std::clamp(top, information.rcWork.top,
                            std::max(information.rcWork.top, information.rcWork.bottom - height));
                        LONG pendingHeight = position->flags & SWP_NOSIZE
                            ? current.bottom - current.top
                            : position->cy;
                        if (height != pendingHeight) {
                            if (position->flags & SWP_NOSIZE) {
                                position->cx = width;
                            }
                            position->cy = height;
                            position->flags &= ~SWP_NOSIZE;
                        }
                        LONG pendingTop = position->flags & SWP_NOMOVE ? current.top : position->y;
                        if (top != pendingTop) {
                            if (position->flags & SWP_NOMOVE) {
                                position->x = fittedLeft;
                            }
                            position->y = top;
                            position->flags &= ~SWP_NOMOVE;
                        }
                    }
                }
            }
        }
    } else if (msg == WM_NCDESTROY) {
        RemoveWindowSubclass(window, ComboBoxDropDownSubclassProc, subclassId);
    }
    return DefSubclassProc(window, msg, wParam, lParam);
}

/// Refreshes time-zone captions and current UTC offsets only when changed, retaining selection by stored
/// zone index.
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
        if (_wcsicmp(timeZones[index].TimeZoneKeyName, SYSTEM_TIME_ZONE_KEY) == 0) {
            label = std::wstring(T(TXT_SYSTEM_TIME_ZONE_LABEL)) + L" (" + label + L")";
        }
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

/// Measures current items in the dropdown font immediately before opening, adding borders, padding, and
/// scrollbar space. Keeps the dropdown at least as wide as its combo and installs integral-height and
/// work-area sizing.
static void UpdateComboBoxDropDownMetrics(HWND combo) {
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
    if (GetComboBoxInfo(GetSettingsComboBox(combo), &information) && information.hwndList != nullptr) {
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
    RECT listRect = { 0, 0, width, 1 };
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

/// Refreshes date-format captions and examples for the widget language and displayed date while retaining
/// the selected format.
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

/// Loads the selected widget while suppressing edit notifications and retaining the previous controls until
/// replacement. Keeps the previous Appearance image visible until all values, positions and visibility
/// states are ready.
static void LoadDraftIntoControls() {
    if (selectedDraftIndex < 0 || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
        return;
    }
    WindowRedrawScope appearanceRedraw(hAppearancePage);
    bool previousUpdating = updatingSettingsControls;
    updatingSettingsControls = true;
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
    SetCheck(hPanelTimeNoticesCheck, config.panelTimeNotices);
    SetComboSelection(hTimeFormatCombo, config.timeFormat);
    SetComboSelection(hWidgetLanguageCombo, config.language);
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
    FillAudioOutputCombo(hAudioOutputCombo, settingsAudioOutputs, config.timeSignalOutputDevice);
    SetCheck(hTimeSignalEnabledCheck, config.timeSignalEnabled);
    for (int mode = TIME_SIGNAL_EVERY_MINUTE; mode < TIME_SIGNAL_COUNT; mode++) {
        SetCheck(hTimeSignalIntervalRadios[mode - 1], config.timeSignal == mode);
    }
    UpdateSettingsSelectionState(true);
    if (GetActiveWidgetSettingsPage() != nullptr) {
        AssignSettingsMnemonics();
    }
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
            MessageBoxW(hSettings, T(TXT_INVALID_REMOTE_SCRIPT_URL), T(TXT_SETTINGS), MB_OK | MB_ICONWARNING);
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
    if (config.type == WIDGET_PANEL) {
        config.panelTimeNotices = GetCheck(hPanelTimeNoticesCheck);
    }
    if (IsWindowEnabled(hShowAmPmCheck)) {
        config.showAmPm = GetCheck(hShowAmPmCheck);
    }
    config.timeFormat = std::clamp(static_cast<int>(SendMessageW(hTimeFormatCombo, CB_GETCURSEL, 0, 0)),
        0, TIME_FORMAT_COUNT - 1);
    config.language = LanguageFromCombo(hWidgetLanguageCombo);
    int zoneSelection = static_cast<int>(SendMessageW(hTimeZoneCombo, CB_GETCURSEL, 0, 0));
    if (zoneSelection != CB_ERR) {
        size_t zoneIndex =
            static_cast<size_t>(SendMessageW(hTimeZoneCombo, CB_GETITEMDATA, zoneSelection, 0));
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
    if (IsTimeSignalGeneratorRequired() || SendMessageW(hTimeSignalSoundCombo, CB_GETCURSEL, 0, 0) == 0) {
        config.timeSignalOutputDevice = SelectedAudioOutputDevice(hAudioOutputCombo, settingsAudioOutputs);
    }
    config.timeSignalEnabled = supportsSound && GetCheck(hTimeSignalEnabledCheck);
    for (int mode = TIME_SIGNAL_EVERY_MINUTE; mode < TIME_SIGNAL_COUNT; mode++) {
        if (GetCheck(hTimeSignalIntervalRadios[mode - 1])) {
            config.timeSignal = static_cast<TimeSignalMode>(mode);
            break;
        }
    }
    return true;
}

/// Validates and saves controls into the selected draft widget, treating no active draft as a successful
/// no-op.
static bool SaveControlsToDraft(bool showErrors) {
    if (selectedDraftIndex < 0 || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
        return true;
    }
    return ReadWidgetControls(settingsDraft[selectedDraftIndex], showErrors);
}

/// Displays the localized widget-limit notice and returns focus to the widget list after dismissal.
static void ShowWidgetLimitMessage() {
    wchar_t msg[256] = {};
    swprintf_s(msg, T(TXT_WIDGET_LIMIT_MESSAGE), MAX_WIDGET_COUNT);
    MessageBoxW(hSettings, msg, T(TXT_SETTINGS), MB_OK | MB_ICONINFORMATION);
    SetFocus(hWidgetList);
}

/// Validates pending edits and copies selected widget configurations in list order; returns false when no
/// items are selected.
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
        copy.id = AllocateWidgetId();
        copy.name += T(TXT_WIDGET_COPY_SUFFIXES);
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

/// Serializes selected widgets to the application's registered clipboard format, transferring memory
/// ownership only on success.
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

/// Reads and validates the application's bounded clipboard payload, validates pending edits, and appends
/// widget copies.
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

/// Copies appearance and calendar-display options while preserving the target's identity, placement, time,
/// and alarm settings.
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
        && left.panelTimeNotices == right.panelTimeNotices
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
        && left.timeSignalOutputDevice == right.timeSignalOutputDevice
        && left.timeSignalEnabled == right.timeSignalEnabled
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

/// Compares global controls and validated widget drafts with applied settings, disregarding runtime position
/// changes. Treats invalid current input as a pending change so Apply can remain available for validation.
static bool HasPendingSettingsChanges() {
    if (LanguageFromCombo(hLanguageCombo) != appLanguage
            || GetCheck(hDisableThemesCheck) != themesDisabled
            || GetCheck(hStartWithWindowsCheck) != startWithWindows
            || GetCheck(hUseXmlSettingsCheck) != storageUsesXml
            || GetCheck(hSnapToWorkAreaCheck) != snapWidgetsToWorkArea
            || GetCheck(hWarnUnsavedChangesCheck) != warnOnUnsavedChanges
            || SelectedFontAntialiasing(hAppAntialiasCombo, appFontAntialiasing) != appFontAntialiasing
            || settingsAppFontFace != appFontFace
            || settingsTestAudioOutputDevice != testAudioOutputDevice
            || settingsAppFontDialogSize != appFontDialogSize
            || settingsAppFontWeight != appFontWeight
            || settingsAppFontItalic != appFontItalic
            || SendMessageW(hTimeSignalSoundCombo, CB_GETCURSEL, 0, 0) != (IsTimeSignalGeneratorRequired()
                || generatedTimeSignal ? 0 : 1)
            || SendMessageW(hTimeSignalVolumeTrackBar, TBM_GETPOS, 0, 0)
                != TimeSignalVolumeSliderPosition(timeSignalVolume)
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
    if (hSettings == nullptr || updatingSettingsControls || hSettingsOpenCombo != nullptr
            || !IsWindowEnabled(hSettings)) {
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
static bool WidgetConfigurationsDifferOnlyInRuntimeSettings(const WidgetConfig& left,
        const WidgetConfig& right) {
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
    normalized.timeSignalOutputDevice = right.timeSignalOutputDevice;
    normalized.timeSignalEnabled = right.timeSignalEnabled;
    normalized.timeSignal = right.timeSignal;
    normalized.alarmTimeSignal = right.alarmTimeSignal;
    normalized.soundsMuted = right.soundsMuted;
    return WidgetConfigurationsEqual(normalized, right);
}

/// Prepares a complete native panel outside the desktop, then moves it into place and hides the old panel in one batch.
/// Synchronizes the prepared surface with desktop composition before the swap. Preserves native client dimensions,
/// calendar selection, alarm and identification state; returns false on failure.
static bool RecreatePanelWidgetBuffered(Widget* widget, const WidgetConfig& configuration,
        const std::vector<TimeDateNotice>* notices, ULONGLONG applicationUtc) {
    Widget replacement;
    replacement.config = configuration;
    replacement.panelCalendarDateSupported = widget->panelCalendarDateSupported;
    bool visible = IsWindowVisible(widget->window) != FALSE;
    bool activate = GetActiveWindow() == widget->window;
    replacement.config.visible = false;
    CreateWidgetWindow(&replacement, false, notices, applicationUtc);
    if (replacement.window == nullptr) {
        return false;
    }
    LONG_PTR extendedStyle = GetWindowLongPtrW(replacement.window, GWL_EXSTYLE);
    if ((extendedStyle & WS_EX_LAYERED) == 0) {
        SetWindowLongPtrW(replacement.window, GWL_EXSTYLE, extendedStyle | WS_EX_LAYERED);
    }
    SetLayeredWindowAttributes(replacement.window, 0, static_cast<BYTE>(configuration.opacity * 255 / 100),
        LWA_ALPHA);
    RECT prepared = {};
    GetWindowRect(replacement.window, &prepared);
    int preparedX = GetSystemMetrics(SM_XVIRTUALSCREEN) - (prepared.right - prepared.left);
    int preparedY = GetSystemMetrics(SM_YVIRTUALSCREEN);
    SetWindowPos(replacement.window, nullptr, preparedX, preparedY, 0, 0,
        SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_SHOWWINDOW);
    replacement.config.visible = true;
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
    SYSTEMTIME selected = {};
    if (MonthCal_GetCurSel(widget->calendarChild, &selected)) {
        MonthCal_SetCurSel(replacement.calendarChild, &selected);
    }
    MonthCal_SetCurrentView(replacement.calendarChild, MonthCal_GetCurrentView(widget->calendarChild));
    replacement.rendered = false;
    replacement.panelNoticesPrepared = true;
    RenderWidget(&replacement);
    RedrawWindow(replacement.window, nullptr, nullptr,
        RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN | RDW_NOERASE);
    GdiFlush();
    DwmFlush();
    replacement.config.visible = configuration.visible;
    HDWP positions = BeginDeferWindowPos(2);
    if (positions != nullptr) {
        UINT flags = SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER;
        flags |= visible ? SWP_SHOWWINDOW : SWP_HIDEWINDOW;
        positions = DeferWindowPos(positions, replacement.window, widget->window, replacement.config.x,
            replacement.config.y, 0, 0, flags);
        if (positions != nullptr) {
            positions = DeferWindowPos(positions, widget->window, nullptr, 0, 0, 0, 0,
                SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_HIDEWINDOW);
        }
    }
    if (positions == nullptr || !EndDeferWindowPos(positions)) {
        replacement.audioStopEvent = nullptr;
        replacement.audioMuteEvent = nullptr;
        replacement.alarmActive = false;
        DestroyWidgetWindow(&replacement);
        return false;
    }
    Widget previous = std::move(*widget);
    *widget = std::move(replacement);
    SetWindowLongPtrW(widget->window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(widget));
    SetWindowLongPtrW(previous.window, GWLP_USERDATA, 0);
    if (activate) {
        SetActiveWindow(widget->window);
    }
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

/// Rebuilds a widget for a new configuration while preserving screen-edge attachments and relevant runtime
/// state.
static void RecreateWidgetForConfiguration(Widget* widget, const WidgetConfig& configuration) {
    if (widget == nullptr || widget->window == nullptr) {
        return;
    }
    ULONGLONG noticeUtc = configuration.type == WIDGET_PANEL && configuration.panelTimeNotices
        ? GetApplicationFileTimeValue()
        : 0;
    std::vector<TimeDateNotice> notices =
        GetPanelTimeNotices(configuration, widget->panelCalendarDateSupported, noticeUtc);
    RECT rect = {};
    bool hasPosition = GetWindowRect(widget->window, &rect) != FALSE;
    int targetX = rect.left;
    int targetY = rect.top;
    bool horizontalAttachment = false;
    if (hasPosition) {
        int newWidth = 0;
        int newHeight = 0;
        GetWidgetDimensions(configuration, &newWidth, &newHeight, &notices);
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
        GetPanelLayout(widget->config, nullptr, &previousClockPosition, nullptr, &widget->panelNotices);
        GetPanelLayout(configuration, nullptr, &newClockPosition, nullptr, &notices);
        targetX = rect.left + previousClockPosition.x - newClockPosition.x;
    }
    bool fullscreenChanged = widget->config.type == WIDGET_FULLSCREEN
        || configuration.type == WIDGET_FULLSCREEN;
    WidgetConfig positionedConfiguration = configuration;
    if (hasPosition) {
        positionedConfiguration.x = targetX;
        positionedConfiguration.y = targetY;
    }
    if (widget->config.type == WIDGET_PANEL
            && configuration.type == WIDGET_PANEL
            && RecreatePanelWidgetBuffered(widget, positionedConfiguration, &notices, noticeUtc)) {
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
    for (size_t wndIndex = 0; wndIndex < widget->fullscreenWindows.size(); wndIndex++) {
        DestroyWindow(widget->fullscreenWindows[wndIndex]);
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
    CreateWidgetWindow(widget, activate, &notices, noticeUtc);
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

/// Applies draft appearance to a live widget, using in-place updates where possible and rebuilding for
/// structural changes.
static void ApplyWidgetAppearancePreview(Widget* widget, const WidgetConfig& appearance,
        bool structuralChange) {
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
    bool opacityChanged = widget->config.opacity != appearance.opacity;
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
        || widget->config.type == WIDGET_PANEL && (borderStyleChanged || panelFontChanged
            || fontAntialiasingChanged);
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
        ApplyPanelLinkFont(widget->panelDateLink, widget->config.panelTopFont,
            widget->config.fontAntialiasing, &widget->panelDateFont);
        ApplyPanelLinkFont(widget->panelTimeZoneLink, widget->config.panelBottomFont,
            widget->config.fontAntialiasing, &widget->panelTimeZoneFont);
        widget->rendered = false;
    }
    if ((fontAntialiasingChanged || fontSelectionChanged) && widget->calendarChild != nullptr) {
        ApplyCalendarFont(widget);
    }
    if (widget->config.type == WIDGET_CALENDAR && borderStyleChanged) {
        int width = 0;
        int height = 0;
        GetWidgetDimensions(widget->config, &width, &height, &widget->panelNotices,
            widget->panelApplicationUtc);
        UINT flags =
            SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOREDRAW | SWP_FRAMECHANGED;
        ResizeWidgetPreservingWorkAreaAttachment(widget, width, height, flags);
        widget->rendered = false;
        redrawFramedWindow = true;
    } else if (digitalDimensionsChanged && !widget->config.transparentBackground) {
        int width = 0;
        int height = 0;
        GetWidgetDimensions(widget->config, &width, &height, &widget->panelNotices,
            widget->panelApplicationUtc);
        UINT flags =
            SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOREDRAW | SWP_FRAMECHANGED;
        ResizeWidgetPreservingWorkAreaAttachment(widget, width, height, flags);
        widget->rendered = false;
        redrawFramedWindow = true;
    }
    if (themeChanged) {
        ApplyWidgetTheme(widget->window, widget->config);
        if (widget->analogChild != nullptr) {
            ApplyWidgetTheme(widget->analogChild, widget->config);
            bool showAnalogSeconds = widget->config.showSeconds
                && AnalogClockSupportsSeconds(widget->config.size);
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
    if (widget->config.type == WIDGET_CALENDAR || widget->config.type == WIDGET_PANEL && opacityChanged) {
        LONG_PTR extendedStyle = GetWindowLongPtrW(widget->window, GWL_EXSTYLE);
        if ((extendedStyle & WS_EX_LAYERED) == 0) {
            SetWindowLongPtrW(widget->window, GWL_EXSTYLE, extendedStyle | WS_EX_LAYERED);
        }
        SetLayeredWindowAttributes(widget->window, 0, static_cast<BYTE>(widget->config.opacity * 255 / 100),
            LWA_ALPHA);
    } else if (widget->config.type == WIDGET_DIGITAL && !widget->config.transparentBackground) {
        SetLayeredWindowAttributes(widget->window, 0, static_cast<BYTE>(widget->config.opacity * 255 / 100),
            LWA_ALPHA);
    }
    if (redrawFramedWindow) {
        RedrawWindow(widget->window, nullptr, nullptr,
            RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE);
        if (widget->calendarChild != nullptr) {
            RedrawWindow(widget->calendarChild, nullptr, nullptr,
                RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE);
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

/// Saves the selected appearance draft, tracks the widget for later restoration, and updates its live
/// preview.
static void PreviewSelectedWidgetAppearance(bool structuralChange) {
    if (!SaveAppearanceControlsToDraft()) {
        return;
    }
    WidgetConfig& appearance = settingsDraft[selectedDraftIndex];
    Widget* widget = FindWidgetById(appearance.id);
    if (widget == nullptr || widget->config.type != appearance.type) {
        return;
    }
    if (std::find(settingsAppearancePreviewIds.begin(), settingsAppearancePreviewIds.end(), appearance.id)
            == settingsAppearancePreviewIds.end()) {
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

/// Selects a draft by persistent ID after validating the previous selection; negative IDs leave selection
/// unchanged.
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

/// Applies a committed configuration with the least required window work, preserving unchanged widgets and
/// updating runtime-only fields in place.
static void ApplyWidgetConfiguration(Widget* widget, const WidgetConfig& configuration,
        bool previousThemesDisabled) {
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
        positionChanged =
            previous.previewX != configuration.previewX || previous.previewY != configuration.previewY;
        targetX = configuration.previewX;
        targetY = configuration.previewY;
    }
    RECT currentPosition = {};
    if (positionChanged
            && GetWindowRect(widget->window, &currentPosition)
            && (currentPosition.left != targetX || currentPosition.top != targetY)) {
        SetWindowPos(widget->window, nullptr, targetX, targetY, 0, 0,
            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
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
            ResizeWidgetPreservingWorkAreaAttachment(widget, width, height,
                SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
        }
    }
    if (secondsChanged || previous.visible != configuration.visible && configuration.visible) {
        widget->lastRenderKey = -1;
        RenderWidget(widget);
    }
}

/// Commits global controls and widget drafts, reconciles live widgets and previews, saves settings,
/// and refreshes affected UI and time services.
static void ApplySettingsDraft() {
    bool previousUpdating = updatingSettingsControls;
    updatingSettingsControls = true;
    timeSignalVolumeDragging = false;
    UpdateTimeSignalVolumePreview();
    StopSettingsPreview();
    StopTimeSignalPlayback();
    ClearCurrentTimeSignalSources();
    snapWidgetsToWorkArea = GetCheck(hSnapToWorkAreaCheck);
    warnOnUnsavedChanges = GetCheck(hWarnUnsavedChangesCheck);
    generatedTimeSignal = SendMessageW(hTimeSignalSoundCombo, CB_GETCURSEL, 0, 0) == 0;
    timeSignalVolume = SelectedTimeSignalVolume();
    testAudioOutputDevice = settingsTestAudioOutputDevice;
    std::vector<int> hiddenWidgetIds;
    for (size_t widgetIndex = 0; widgetIndex < widgets.size(); widgetIndex++) {
        if (!widgets[widgetIndex]->config.visible) {
            continue;
        }
        for (size_t draftIndex = 0; draftIndex < settingsDraft.size(); draftIndex++) {
            if (settingsDraft[draftIndex].id == widgets[widgetIndex]->config.id
                    && !settingsDraft[draftIndex].visible) {
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
                    GetPositionPreservingWorkAreaAttachment(current->window, previewWidth, previewHeight,
                        &position);
                    settingsDraft[draftIndex].previewX = position.x;
                    settingsDraft[draftIndex].previewY = position.y;
                } else {
                    const WidgetConfig& draft = settingsDraft[draftIndex];
                    ULONGLONG noticeUtc = draft.type == WIDGET_PANEL && draft.panelTimeNotices
                        ? GetApplicationFileTimeValue()
                        : 0;
                    std::vector<TimeDateNotice> notices =
                        GetPanelTimeNotices(draft, current->panelCalendarDateSupported, noticeUtc);
                    int newWidth = 0;
                    int newHeight = 0;
                    GetWidgetDimensions(draft, &newWidth, &newHeight, &notices);
                    POINT position = { rect.left, rect.top };
                    bool horizontalAttachment = false;
                    GetPositionPreservingWorkAreaAttachment(current->window, newWidth, newHeight, &position,
                        &horizontalAttachment);
                    if (!horizontalAttachment
                            && current->config.type == WIDGET_PANEL
                            && settingsDraft[draftIndex].type == WIDGET_PANEL) {
                        POINT currentClockPosition = {};
                        POINT draftClockPosition = {};
                        GetPanelLayout(current->config, nullptr, &currentClockPosition, nullptr,
                            &current->panelNotices);
                        GetPanelLayout(draft, nullptr, &draftClockPosition, nullptr, &notices);
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
    appFontFace = settingsAppFontFace;
    appFontDialogSize = std::clamp(settingsAppFontDialogSize, 10, 9990);
    appFontWeight = std::clamp(settingsAppFontWeight, 0, 1000);
    appFontItalic = settingsAppFontItalic;
    settingsApplicationFontPreviewActive = false;
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
    int newNtpPreset = std::clamp(static_cast<int>(SendMessageW(hNtpPresetCombo, CB_GETCURSEL, 0, 0)),
        0, NTP_PRESET_COUNT - 1);
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
            std::unique_ptr<Widget> added = std::make_unique<Widget>();
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
    bool uiStyleChanged = previousThemesDisabled != themesDisabled
        || previousAppFontAntialiasing != appFontAntialiasing;
    if (uiStyleChanged) {
        RefreshApplicationFonts(false);
    }
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
    settingsTestAudioOutputDevice = testAudioOutputDevice;
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
        if (configuration.type == WIDGET_FULLSCREEN && CheckedMonitorIndices().empty()) {
            LoadMonitorSelection(configuration);
        }
    }
    updatingSettingsControls = previousUpdating;
    UpdateSettingsApplyButton();
}

/// Copies placement and the field affected by a context-menu command into a settings snapshot without
/// overwriting unrelated edits.
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
        target->timeSignalEnabled = source.timeSignalEnabled;
    } else if (command == ID_MENU_WEEK_NUMBERS) {
        target->weekNumbers = source.weekNumbers;
    } else if (command == ID_MENU_SUNDAY_FIRST) {
        target->sundayFirst = source.sundayFirst;
    } else if (command == ID_MENU_SHOW_TODAY) {
        target->showToday = source.showToday;
    } else if (command >= ID_MENU_DATE_FORMAT_BASE
            && command < ID_MENU_DATE_FORMAT_BASE + DATE_FORMAT_COUNT) {
        target->dateCopyFormat = source.dateCopyFormat;
    } else if (command >= ID_MENU_SIZE_104 && command <= ID_MENU_SIZE_198) {
        target->size = source.size;
        if (source.type == WIDGET_DIGITAL) {
            target->fontSize = source.fontSize;
            target->fontDialogSize = source.fontSize * 10;
        }
    } else if (command >= ID_ADDITIONAL_SIZE_BASE
            && command < ID_ADDITIONAL_SIZE_BASE + ADDITIONAL_CLOCK_COUNT) {
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
            SetCheck(hTimeSignalEnabledCheck, configuration.timeSignalEnabled);
            UpdateSettingControlAvailability();
        } else if (command == ID_MENU_WEEK_NUMBERS) {
            SetCheck(hWeekNumbersCheck, configuration.weekNumbers);
        } else if (command == ID_MENU_SUNDAY_FIRST) {
            SetCheck(hSundayFirstCheck, configuration.sundayFirst);
        } else if (command == ID_MENU_SHOW_TODAY) {
            SetCheck(hShowTodayCheck, configuration.showToday);
        } else if (command >= ID_MENU_DATE_FORMAT_BASE && command < ID_MENU_DATE_FORMAT_BASE + DATE_FORMAT_COUNT) {
            SetComboSelection(hDateFormatCombo, configuration.dateCopyFormat);
        } else {
            int sizes[4] = {};
            int count = GetAnalogClockSizes(sizes);
            HWND combo = hSizeCombo;
            int size = configuration.size;
            if (command >= ID_ADDITIONAL_SIZE_BASE
                    && command < ID_ADDITIONAL_SIZE_BASE + ADDITIONAL_CLOCK_COUNT) {
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

/// Opens the color dialog using the button's current color and updates the button only when a choice is
/// accepted.
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

/// Updates the selected widget's font labels and font-button captions without rewriting unchanged text.
static void UpdateFontDescription(const WidgetConfig& config) {
    SetControlCaption(hFontLabel, config.type == WIDGET_PANEL
        ? T(TXT_CALENDAR_FONT_LABEL)
        : T(TXT_FONT_LABEL));
    if (hFontButton != nullptr) {
        std::wstring caption = config.fontFace;
        if ((config.type == WIDGET_CALENDAR
            || config.type == WIDGET_PANEL) && !IsWindowEnabled(hFontButton)) {
            caption = T(TXT_SYSTEM_DEFAULT_FONT_LABEL);
        }
        caption += L"…";
        SetControlCaption(hFontButton, caption.c_str());
    }
    if (hPanelTopFontButton != nullptr) {
        std::wstring caption = config.panelTopFont.face + L"…";
        SetControlCaption(hPanelTopFontButton, caption.c_str());
    }
    if (hPanelTimeFontButton != nullptr) {
        std::wstring caption = config.panelTimeFont.face + L"…";
        SetControlCaption(hPanelTimeFontButton, caption.c_str());
    }
    if (hPanelBottomFontButton != nullptr) {
        std::wstring caption = config.panelBottomFont.face + L"…";
        SetControlCaption(hPanelBottomFontButton, caption.c_str());
    }
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
static UINT_PTR CALLBACK FontDialogHook(HWND dialog, UINT msg, WPARAM, LPARAM parameter) {
    if (msg == WM_PAINT) {
        PAINTSTRUCT paint = {};
        HDC dc = BeginPaint(dialog, &paint);
        FillRect(dc, &paint.rcPaint, GetSysColorBrush(COLOR_3DFACE));
        EndPaint(dialog, &paint);
        return 1;
    }
    if (msg != WM_INITDIALOG) {
        return 0;
    }
    LimitDialogVerticalUnits(dialog);
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
    bool invalidSizeControl = mode == FONT_DIALOG_WITH_SIZE
        && (hSize == nullptr || !GetWindowRect(hSize, &sizeRect));
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
    int buttonHeight = std::min(static_cast<int>(okRect.bottom - okRect.top), MAX_DIALOG_BUTTON_HEIGHT);
    int contentRight = static_cast<int>(std::max(faceRect.right, styleRect.right));
    int contentBottom = static_cast<int>(std::max(faceRect.bottom, styleRect.bottom));
    if (mode == FONT_DIALOG_WITH_SIZE) {
        contentRight = std::max(contentRight, static_cast<int>(sizeRect.right));
        contentBottom = std::max(contentBottom, static_cast<int>(sizeRect.bottom));
    }
    int newClientWidth =
        std::max(contentRight + horizontalMargin, buttonWidth * 2 + buttonGap + horizontalMargin * 2);
    int buttonY = contentBottom + verticalMargin;
    int cancelX = newClientWidth - horizontalMargin - buttonWidth;
    int okX = cancelX - buttonGap - buttonWidth;
    SetWindowPos(hOk, nullptr, okX, buttonY, buttonWidth, buttonHeight,
        SWP_NOACTIVATE | SWP_NOZORDER);
    SetWindowPos(hCancel, nullptr, cancelX, buttonY, buttonWidth, buttonHeight,
        SWP_NOACTIVATE | SWP_NOZORDER);
    int newClientHeight = buttonY + buttonHeight + verticalMargin;
    int nonClientWidth = windowRect.right - windowRect.left - (clientRect.right - clientRect.left);
    int nonClientHeight = windowRect.bottom - windowRect.top - (clientRect.bottom - clientRect.top);
    SetWindowPos(dialog, nullptr, 0, 0, newClientWidth + nonClientWidth, newClientHeight + nonClientHeight,
        SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
    return 0;
}

/// Opens the customized font dialog with size in tenths of a point and copies accepted attributes back
/// to the caller. Returns false for missing required outputs or a canceled or unsuccessful dialog.
static bool ChooseFontAttributes(HWND owner, std::wstring* face, int* sizeTenths, int* weight, bool* italic,
        BYTE* charSet, FontDialogMode mode, bool* underline = nullptr, bool* strikeOut = nullptr) {
    if (face == nullptr
            || sizeTenths == nullptr
            || weight == nullptr
            || italic == nullptr
            || charSet == nullptr) {
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
        config.fontSize =
            std::clamp((config.fontDialogSize + 5) / 10, DIGITAL_FONT_SIZE_MIN, DIGITAL_FONT_SIZE_MAX);
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
            &selection->italic, &selection->charSet, FONT_DIALOG_WITH_SIZE, &selection->underline,
            &selection->strikeOut)) {
        return;
    }
    if (selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
        UpdateFontDescription(settingsDraft[selectedDraftIndex]);
    }
    PreviewSelectedWidgetAppearance(false);
}

/// Edits the draft application font, starting from system defaults when unspecified, and previews the
/// accepted choice.
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

/// Cancels the alarm test, releases its event handles, restores temporary visual alarm state, and resets
/// the Test caption.
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
    if (hTestCommandButton != nullptr && GetControlText(hTestCommandButton) != T(TXT_TEST_COMMAND_LABEL)) {
        SetWindowTextW(hTestCommandButton, T(TXT_TEST_COMMAND_LABEL));
    }
}

/// Toggles the configured alarm test, validating applicable inputs and launching its audio, visual,
/// and remote actions.
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
        MessageBoxW(hSettings, T(TXT_INVALID_REMOTE_SCRIPT_URL), T(TXT_SETTINGS), MB_OK | MB_ICONWARNING);
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
    SetWindowTextW(hTestCommandButton, T(TXT_STOP_TEST_LABEL));
}

/// Opens the localized file picker, enables the selected alarm command, and defaults recognized audio files
/// to looping playback.
static void BrowseForCommand() {
    wchar_t fileName[MAX_PATH] = {};
    OPENFILENAMEW dialog = {};
    dialog.lStructSize = sizeof(dialog);
    dialog.hwndOwner = hSettings;
    dialog.lpstrFile = fileName;
    dialog.nMaxFile = ARRAYSIZE(fileName);
    dialog.lpstrFilter = T(TXT_COMMAND_FILE_FILTER);
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

/// Creates all settings pages and controls, populates selectors, and applies shared layout, clipping,
/// scrolling, fonts, and themes. Returns false when a required control or its text-selection handler
/// could not be created.
static bool CreateSettingsControls() {
    WindowRedrawScope redraw(hSettings);
    if (hUiFont == nullptr) {
        hUiFont = CreateApplicationUiFont(hSettings);
        if (hUiFont == nullptr) {
            return false;
        }
    }
    settingsGeneralCheckboxReferenceValid = false;
    bool previousUpdating = updatingSettingsControls;
    updatingSettingsControls = true;
    generalControls.clear();
    appearanceControls.clear();
    alarmControls.clear();
    timeSignalControls.clear();
    timeControls.clear();
    applicationControls.clear();
    HWND addTypeLabel = BindSettingsLabel(hSettings, IDC_ADD_TYPE_LABEL, Mnemonic(TXT_TYPE).c_str());
    hAddType = BindSettingsControl(hSettings, ID_ADD_TYPE, L"", nullptr, addTypeLabel);
    for (int type = 0; type < WIDGET_TYPE_COUNT; type++) {
        SendMessageW(hAddType, CB_ADDSTRING, 0,
            reinterpret_cast<LPARAM>(TypeName(static_cast<WidgetType>(type))));
    }
    SendMessageW(hAddType, CB_SETCURSEL, lastAddedWidgetType, 0);
    BindSettingsControl(hSettings, ID_ADD, Mnemonic(TXT_ADD).c_str());
    hWidgetList = BindSettingsControl(hSettings, ID_LIST_WIDGETS, L"");
    BindSettingsControl(hSettings, ID_REMOVE, Mnemonic(TXT_REMOVE).c_str());
    BindSettingsControl(hSettings, ID_DUPLICATE, Mnemonic(TXT_DUPLICATE).c_str());
    hTabs = BindSettingsControl(hSettings, ID_TABS, L"");
    if (hTabs == nullptr) {
        updatingSettingsControls = previousUpdating;
        return false;
    }
    TCITEMW tab = {};
    tab.mask = TCIF_TEXT;
    tab.pszText = const_cast<wchar_t*>(T(TXT_GENERAL));
    TabCtrl_InsertItem(hTabs, 0, &tab);
    tab.pszText = const_cast<wchar_t*>(T(TXT_APPEARANCE));
    TabCtrl_InsertItem(hTabs, 1, &tab);
    tab.pszText = const_cast<wchar_t*>(T(TXT_ALARM));
    TabCtrl_InsertItem(hTabs, 2, &tab);
    tab.pszText = const_cast<wchar_t*>(T(TXT_TIME_SIGNAL_TAB_LABEL));
    TabCtrl_InsertItem(hTabs, 3, &tab);
    tab.pszText = const_cast<wchar_t*>(T(TXT_TIME_TAB_LABEL));
    TabCtrl_InsertItem(hTabs, 4, &tab);
    tab.pszText = const_cast<wchar_t*>(T(TXT_APPLICATION_TAB_LABEL));
    TabCtrl_InsertItem(hTabs, 5, &tab);
    hGeneralPage = CreateSettingsPage(IDD_SETTINGS_GENERAL);
    hAppearancePage = CreateSettingsPage(IDD_SETTINGS_APPEARANCE);
    hAlarmPage = CreateSettingsPage(IDD_SETTINGS_ALARM);
    hTimeSignalPage = CreateSettingsPage(IDD_SETTINGS_SIGNALS);
    hTimePage = CreateSettingsPage(IDD_SETTINGS_TIME);
    hApplicationPage = CreateSettingsPage(IDD_SETTINGS_APPLICATION);
    for (int index = 0; index < SETTINGS_TAB_COUNT; index++) {
        if (GetSettingsPage(index) == nullptr) {
            updatingSettingsControls = previousUpdating;
            return false;
        }
    }
    UpdateSettingsTabLayout();
    SetWindowLongPtrW(hAppearancePage, GWL_EXSTYLE,
        GetWindowLongPtrW(hAppearancePage, GWL_EXSTYLE) | WS_EX_COMPOSITED);
    HWND nameLabel = BindSettingsLabel(hGeneralPage, IDC_NAME_LABEL, Mnemonic(TXT_NAME).c_str(),
        &generalControls);
    hNameEdit = BindSettingsControl(hGeneralPage, ID_NAME, L"", &generalControls, nameLabel);
    HWND typeLabel = BindSettingsLabel(hGeneralPage, IDC_TYPE_LABEL, Mnemonic(TXT_TYPE).c_str(),
        &generalControls);
    hTypeCombo = BindSettingsControl(hGeneralPage, ID_TYPE, L"", &generalControls, typeLabel);
    for (int type = 0; type < WIDGET_TYPE_COUNT; type++) {
        SendMessageW(hTypeCombo, CB_ADDSTRING, 0,
            reinterpret_cast<LPARAM>(TypeName(static_cast<WidgetType>(type))));
    }
    hVisibleCheck = BindSettingsControl(hGeneralPage, ID_VISIBLE, Mnemonic(TXT_VISIBLE).c_str(),
        &generalControls);
    hTopmostCheck = BindSettingsControl(hGeneralPage, ID_TOPMOST, Mnemonic(TXT_TOPMOST).c_str(),
        &generalControls);
    hSecondsCheck = BindSettingsControl(hGeneralPage, ID_SECONDS, Mnemonic(TXT_SECONDS).c_str(),
        &generalControls);
    hUtcCheck = BindSettingsControl(hGeneralPage, ID_UTC, Mnemonic(TXT_UTC).c_str(), &generalControls);
    hUtcTextCheck = BindSettingsControl(hGeneralPage, ID_UTC_TEXT, T(TXT_UTC_TEXT_LABEL),
        &generalControls);
    hSoundsMutedCheck = BindSettingsControl(hGeneralPage, ID_SOUNDS_ENABLED, T(TXT_MUTED_LABEL),
        &generalControls);
    SetCheck(hSoundsMutedCheck, false);
    hTimeZoneLabel = BindSettingsLabel(hGeneralPage, IDC_TIME_ZONE_LABEL, Mnemonic(TXT_TIMEZONE).c_str(),
        &generalControls);
    hTimeZoneCombo = BindSettingsControl(hGeneralPage, ID_TIMEZONE, L"", &generalControls, hTimeZoneLabel);
    FillTimeZoneCombo();
    HWND offsetLabel = BindSettingsLabel(hGeneralPage, IDC_OFFSET_LABEL, Mnemonic(TXT_OFFSET).c_str(),
        &generalControls);
    hOffsetEdit = BindSettingsControl(hGeneralPage, ID_OFFSET, L"", &generalControls, offsetLabel);
    HWND widgetLanguageLabel = BindSettingsLabel(hGeneralPage, IDC_WIDGET_LANGUAGE_LABEL,
        T(TXT_WIDGET_LANGUAGE_LABEL), &generalControls);
    hWidgetLanguageCombo = BindSettingsControl(hGeneralPage, ID_WIDGET_LANGUAGE, L"", &generalControls,
        widgetLanguageLabel);
    PopulateLanguageCombo(hWidgetLanguageCombo);
    hTimeFormatLabel = BindSettingsLabel(hGeneralPage, IDC_TIME_FORMAT_LABEL, T(TXT_TIME_FORMAT_LABEL),
        &generalControls);
    hTimeFormatCombo = BindSettingsControl(hGeneralPage, ID_TIME_FORMAT, L"", &generalControls,
        hTimeFormatLabel);
    for (int mode = 0; mode < TIME_FORMAT_COUNT; mode++) {
        SendMessageW(hTimeFormatCombo, CB_ADDSTRING, 0,
            reinterpret_cast<LPARAM>(T(TIME_FORMAT_TEXT_IDS[mode])));
    }
    hShowAmPmCheck = BindSettingsControl(hGeneralPage, ID_SHOW_AM_PM, L"AM/PM", &generalControls);
    hPanelTimeNoticesCheck = BindSettingsControl(hGeneralPage, ID_PANEL_TIME_NOTICES,
        T(TXT_PANEL_TIME_NOTICES_LABEL), &generalControls);
    for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
        std::wstring label = AdditionalClockLabel(appLanguage, index, true);
        hAdditionalEnabledChecks[index] = BindSettingsControl(hGeneralPage,
            ID_ADDITIONAL_ENABLED_BASE + index, label.c_str(), &generalControls);
        hAdditionalNameLabels[index] = BindSettingsLabel(hGeneralPage,
            IDC_ADDITIONAL_NAME_LABELS_BASE + index, Mnemonic(TXT_NAME).c_str(), &generalControls);
        std::wstring name = DefaultAdditionalClockName(appLanguage, index);
        hAdditionalNameEdits[index] = BindSettingsControl(hGeneralPage,
            ID_ADDITIONAL_NAME_BASE + index, name.c_str(), &generalControls, hAdditionalNameLabels[index]);
        hAdditionalTimeZoneLabels[index] = BindSettingsLabel(hGeneralPage,
            IDC_ADDITIONAL_TIME_ZONE_LABELS_BASE + index, Mnemonic(TXT_TIMEZONE).c_str(), &generalControls);
        hAdditionalTimeZoneCombos[index] = BindSettingsControl(hGeneralPage,
            ID_ADDITIONAL_TIMEZONE_BASE + index, L"", &generalControls, hAdditionalTimeZoneLabels[index]);
        FillTimeZoneCombo(hAdditionalTimeZoneCombos[index]);
    }
    hMonitorLabel = BindSettingsLabel(hGeneralPage, IDC_MONITOR_LABEL, T(TXT_MONITOR_LABEL),
        &generalControls);
    hMonitorList = BindSettingsControl(hGeneralPage, ID_MONITOR_LIST, L"", &generalControls);
    InitializeMonitorList();
    hBlackoutMonitorsCheck = BindSettingsControl(hGeneralPage, ID_BLACKOUT_MONITORS,
        T(TXT_BLACKOUT_MONITOR_LABEL), &generalControls);
    hSizeLabel = BindSettingsLabel(hAppearancePage, IDC_SIZE_LABEL, Mnemonic(TXT_SIZE).c_str(),
        &appearanceControls);
    hSizeCombo = BindSettingsControl(hAppearancePage, ID_SIZE, L"", &appearanceControls, hSizeLabel);
    int sizes[4] = {};
    int sizeCount = GetAnalogClockSizes(sizes);
    for (int index = 0; index < sizeCount; index++) {
        std::wstring sizeLabel = std::to_wstring(sizes[index]) + L" px";
        SendMessageW(hSizeCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(sizeLabel.c_str()));
    }
    for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
        hAdditionalSizeCombos[index] = BindSettingsControl(hAppearancePage,
            ID_ADDITIONAL_SIZE_BASE + index, L"", &appearanceControls);
        for (int item = 0; item < sizeCount; item++) {
            std::wstring label = std::to_wstring(sizes[item]) + L" px";
            SendMessageW(hAdditionalSizeCombos[index], CB_ADDSTRING, 0,
                reinterpret_cast<LPARAM>(label.c_str()));
        }
    }
    hOpacityLabel = BindSettingsLabel(hAppearancePage, IDC_OPACITY_LABEL,
        Mnemonic(TXT_OPACITY).c_str(), &appearanceControls);
    hOpacityTrackBar = BindSettingsControl(hAppearancePage, ID_OPACITY, L"",
        &appearanceControls);
    SendMessageW(hOpacityTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(WIDGET_OPACITY_MIN, WIDGET_OPACITY_MAX));
    SendMessageW(hOpacityTrackBar, TBM_SETTICFREQ, 5, 0);
    SendMessageW(hOpacityTrackBar, TBM_SETLINESIZE, 0, 1);
    SendMessageW(hOpacityTrackBar, TBM_SETPAGESIZE, 0, 5);
    hOpacityValue = BindSettingsControl(hAppearancePage, IDC_OPACITY_VALUE, L"",
        &appearanceControls);
    hFontSizeLabel = BindSettingsLabel(hAppearancePage, IDC_FONT_SIZE_LABEL,
        Mnemonic(TXT_FONT_SIZE).c_str(), &appearanceControls);
    hFontSizeTrackBar = BindSettingsControl(hAppearancePage, ID_FONT_SIZE, L"",
        &appearanceControls);
    SendMessageW(hFontSizeTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(DIGITAL_FONT_SIZE_MIN,
        DIGITAL_FONT_SIZE_MAX));
    SendMessageW(hFontSizeTrackBar, TBM_SETTICFREQ, 5, 0);
    SendMessageW(hFontSizeTrackBar, TBM_SETLINESIZE, 0, 1);
    SendMessageW(hFontSizeTrackBar, TBM_SETPAGESIZE, 0, 5);
    hFontSizeValue = BindSettingsControl(hAppearancePage, IDC_FONT_SIZE_VALUE, L"",
        &appearanceControls);
    hFontLabel = BindSettingsLabel(hAppearancePage, IDC_FONT_LABEL, T(TXT_FONT_LABEL),
        &appearanceControls);
    hFontButton = BindSettingsControl(hAppearancePage, ID_FONT, T(TXT_FONT_BUTTON_LABEL),
        &appearanceControls);
    hPanelTopFontLabel = BindSettingsLabel(hAppearancePage, IDC_PANEL_TOP_FONT_LABEL,
        T(TXT_PANEL_TOP_FONT_LABEL), &appearanceControls);
    hPanelTopFontButton = BindSettingsControl(hAppearancePage, ID_PANEL_TOP_FONT, L"",
        &appearanceControls, hPanelTopFontLabel);
    hPanelTimeFontLabel = BindSettingsLabel(hAppearancePage, IDC_PANEL_TIME_FONT_LABEL,
        T(TXT_PANEL_TIME_FONT_LABEL), &appearanceControls);
    hPanelTimeFontButton = BindSettingsControl(hAppearancePage, ID_PANEL_TIME_FONT, L"",
        &appearanceControls, hPanelTimeFontLabel);
    hPanelBottomFontLabel = BindSettingsLabel(hAppearancePage, IDC_PANEL_BOTTOM_FONT_LABEL,
        T(TXT_PANEL_BOTTOM_FONT_LABEL), &appearanceControls);
    hPanelBottomFontButton = BindSettingsControl(hAppearancePage, ID_PANEL_BOTTOM_FONT, L"",
        &appearanceControls, hPanelBottomFontLabel);
    hTextColorButton = BindSettingsControl(hAppearancePage, ID_TEXT_COLOR,
        Mnemonic(TXT_TEXT_COLOR).c_str(), &appearanceControls);
    hBackgroundColorButton = BindSettingsControl(hAppearancePage, ID_BACKGROUND_COLOR,
        Mnemonic(TXT_BACKGROUND_COLOR).c_str(), &appearanceControls);
    hAlarmTextColorButton = BindSettingsControl(hAppearancePage, ID_ALARM_TEXT_COLOR,
        T(TXT_ALARM_TEXT_COLOR_LABEL), &appearanceControls);
    hAlarmBackgroundColorButton = BindSettingsControl(hAppearancePage, ID_ALARM_BACKGROUND_COLOR,
        T(TXT_ALARM_BACKGROUND_COLOR_LABEL), &appearanceControls);
    hPaddingLabel = BindSettingsLabel(hAppearancePage, IDC_PADDING_LABEL, T(TXT_PADDING_LABEL),
        &appearanceControls);
    hPaddingTrackBar = BindSettingsControl(hAppearancePage, ID_PADDING, L"", &appearanceControls);
    SendMessageW(hPaddingTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(0, DIGITAL_PADDING_MAX));
    SendMessageW(hPaddingTrackBar, TBM_SETTICFREQ, 5, 0);
    SendMessageW(hPaddingTrackBar, TBM_SETLINESIZE, 0, 1);
    SendMessageW(hPaddingTrackBar, TBM_SETPAGESIZE, 0, 5);
    hPaddingValue = BindSettingsControl(hAppearancePage, IDC_PADDING_VALUE, L"",
        &appearanceControls);
    hBorderWidthLabel = BindSettingsLabel(hAppearancePage, IDC_BORDER_WIDTH_LABEL,
        T(TXT_BORDER_WIDTH_LABEL), &appearanceControls);
    hBorderWidthTrackBar = BindSettingsControl(hAppearancePage, ID_BORDER_WIDTH, L"",
        &appearanceControls);
    SendMessageW(hBorderWidthTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(0, DIGITAL_BORDER_WIDTH_MAX));
    SendMessageW(hBorderWidthTrackBar, TBM_SETTICFREQ, 1, 0);
    SendMessageW(hBorderWidthTrackBar, TBM_SETLINESIZE, 0, 1);
    SendMessageW(hBorderWidthTrackBar, TBM_SETPAGESIZE, 0, 1);
    hBorderWidthValue = BindSettingsControl(hAppearancePage, IDC_BORDER_WIDTH_VALUE, L"",
        &appearanceControls);
    hBorderLabel = BindSettingsLabel(hAppearancePage, IDC_BORDER_LABEL, T(TXT_BORDER_LABEL),
        &appearanceControls);
    hBorderTrackBar = BindSettingsControl(hAppearancePage, ID_BORDER, L"", &appearanceControls);
    SendMessageW(hBorderTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(0, 3));
    SendMessageW(hBorderTrackBar, TBM_SETTICFREQ, 1, 0);
    SendMessageW(hBorderTrackBar, TBM_SETLINESIZE, 0, 1);
    SendMessageW(hBorderTrackBar, TBM_SETPAGESIZE, 0, 1);
    hBorderColorButton = BindSettingsControl(hAppearancePage, ID_BORDER_COLOR, T(TXT_BORDER_COLOR_LABEL),
        &appearanceControls);
    const HWND colorButtons[] = {
        hTextColorButton,
        hBackgroundColorButton,
        hAlarmTextColorButton,
        hAlarmBackgroundColorButton,
        hBorderColorButton
    };
    for (HWND button : colorButtons) {
        AddSettingsColorPreview(button);
    }
    hLeadingZeroLabel = BindSettingsLabel(hAppearancePage, IDC_LEADING_ZERO_LABEL, T(TXT_LEADING_ZERO),
        &appearanceControls);
    hLeadingZeroCombo = BindSettingsControl(hAppearancePage, ID_LEADING_ZERO, L"", &appearanceControls,
        hLeadingZeroLabel);
    for (int mode = 0; mode < LEADING_ZERO_MODE_COUNT; mode++) {
        SendMessageW(hLeadingZeroCombo, CB_ADDSTRING, 0,
            reinterpret_cast<LPARAM>(T(LEADING_ZERO_TEXT_IDS[mode])));
    }
    hTransparentBackgroundCheck = BindSettingsControl(hAppearancePage, ID_TRANSPARENT_BG,
        Mnemonic(TXT_TRANSPARENT_BG).c_str(), &appearanceControls);
    hWeekNumbersCheck = BindSettingsControl(hAppearancePage, ID_WEEK_NUMBERS,
        Mnemonic(TXT_WEEK_NUMBERS).c_str(), &appearanceControls);
    hSundayFirstCheck = BindSettingsControl(hAppearancePage, ID_SUNDAY_FIRST,
        Mnemonic(TXT_SUNDAY_FIRST).c_str(), &appearanceControls);
    hShowTodayCheck = BindSettingsControl(hAppearancePage, ID_SHOW_TODAY, T(TXT_SHOW_TODAY_LABEL),
        &appearanceControls);
    hDateFormatLabel = BindSettingsLabel(hAppearancePage, IDC_DATE_FORMAT_LABEL, T(TXT_DATE_FORMAT_LABEL),
        &appearanceControls);
    hDateFormatCombo = BindSettingsControl(hAppearancePage, ID_DATE_FORMAT, L"", &appearanceControls,
        hDateFormatLabel);
    hWidgetAntialiasLabel = BindSettingsLabel(hAppearancePage, IDC_WIDGET_ANTIALIAS_LABEL,
        T(TXT_ANTIALIASING_LABEL), &appearanceControls);
    hWidgetAntialiasCombo = BindSettingsControl(hAppearancePage, ID_WIDGET_ANTIALIAS, L"",
        &appearanceControls, hWidgetAntialiasLabel);
    PopulateFontAntialiasingCombo(hWidgetAntialiasCombo);
    hWidgetDisableThemesCheck = BindSettingsControl(hAppearancePage, ID_WIDGET_DISABLE_THEMES,
        Mnemonic(TXT_VISUAL_STYLES).c_str(), &appearanceControls);
    hDefaultAppearanceButton = BindSettingsControl(hAppearancePage, ID_DEFAULT_APPEARANCE,
        T(TXT_DEFAULT_APPEARANCE_LABEL), &appearanceControls);
    hAlarmEnabledCheck = BindSettingsControl(hAlarmPage, ID_ALARM_ENABLED,
        Mnemonic(TXT_ALARM_ACTIVE).c_str(), &alarmControls);
    int firstAlarmDay = GetCultureFirstAlarmDay(appLanguage);
    for (int position = 0; position < ALARM_DAY_COUNT; position++) {
        int day = (firstAlarmDay + position) % ALARM_DAY_COUNT;
        std::wstring dayLabel = GetWeekdayAbbreviation(appLanguage, day);
        hAlarmDayChecks[day] = BindSettingsControl(hAlarmPage, ID_ALARM_DAY_BASE + day, dayLabel.c_str(),
            &alarmControls);
        RECT slot = GetSettingsResourceRect(hAlarmPage, IDC_ALARM_DAY_SLOT_BASE + position);
        SetWindowPos(hAlarmDayChecks[day], nullptr, slot.left, slot.top, slot.right - slot.left,
            slot.bottom - slot.top, SWP_NOZORDER | SWP_NOACTIVATE);
    }
    std::wstring alarmTimeLabel = Mnemonic(TXT_ALARM_TIME);
    HWND alarmTimeFieldLabel = BindSettingsLabel(hAlarmPage, IDC_ALARM_TIME_FIELD_LABEL,
        alarmTimeLabel.c_str(), &alarmControls);
    hAlarmTimeEdit = BindSettingsControl(hAlarmPage, ID_ALARM_TIME, L"", &alarmControls, alarmTimeFieldLabel);
    hRunCommandCheck = BindSettingsControl(hAlarmPage, ID_RUN_COMMAND, Mnemonic(TXT_RUN_FILE).c_str(),
        &alarmControls);
    hCommandEdit = BindSettingsControl(hAlarmPage, ID_COMMAND, L"", &alarmControls);
    hBrowseButton = BindSettingsControl(hAlarmPage, ID_BROWSE, Mnemonic(TXT_BROWSE).c_str(),
        &alarmControls);
    hTestCommandButton = BindSettingsControl(hAlarmPage, ID_TEST_COMMAND, T(TXT_TEST_COMMAND_LABEL),
        &alarmControls);
    hLoopAudioCheck = BindSettingsControl(hAlarmPage, ID_LOOP_AUDIO, Mnemonic(TXT_LOOP_AUDIO).c_str(),
        &alarmControls);
    hAlarmVolumeLabel = BindSettingsLabel(hAlarmPage, IDC_ALARM_VOLUME_LABEL, T(TXT_ALARM_VOLUME_LABEL),
        &alarmControls);
    hAlarmVolumeTrackBar = BindSettingsControl(hAlarmPage, ID_ALARM_VOLUME, L"", &alarmControls);
    SendMessageW(hAlarmVolumeTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(TIME_SIGNAL_VOLUME_SLIDER_MIN,
        TIME_SIGNAL_VOLUME_SLIDER_MAX));
    for (int decibels = -54; decibels < 0; decibels += 6) {
        SendMessageW(hAlarmVolumeTrackBar, TBM_SETTIC, 0, AlarmVolumeSliderPosition(decibels * 100));
    }
    SendMessageW(hAlarmVolumeTrackBar, TBM_SETLINESIZE, 0, 10);
    SendMessageW(hAlarmVolumeTrackBar, TBM_SETPAGESIZE, 0, 100);
    hAlarmVolumeValue = BindSettingsControl(hAlarmPage, IDC_ALARM_VOLUME_VALUE, L"", &alarmControls);
    hRemoteScriptCheck = BindSettingsControl(hAlarmPage, ID_REMOTE_SCRIPT, T(TXT_REMOTE_SCRIPT_LABEL),
        &alarmControls);
    hRemoteScriptLabel = BindSettingsLabel(hAlarmPage, IDC_REMOTE_SCRIPT_LABEL,
        T(TXT_REMOTE_SCRIPT_URL_LABEL), &alarmControls);
    hRemoteScriptEdit = BindSettingsControl(hAlarmPage, ID_REMOTE_SCRIPT_URL, L"",
        &alarmControls, hRemoteScriptLabel);
    hAlarmTimeSignalCheck = BindSettingsControl(hAlarmPage, ID_ALARM_TIME_SIGNAL,
        T(TXT_ALARM_TIME_SIGNAL_LABEL), &alarmControls);
    hTimeSignalEnabledCheck = BindSettingsControl(hTimeSignalPage, ID_TIME_SIGNAL_ENABLED,
        T(TXT_TIME_SIGNAL_ENABLED_LABEL), &timeSignalControls);
    for (int mode = TIME_SIGNAL_EVERY_MINUTE; mode < TIME_SIGNAL_COUNT; mode++) {
        DWORD style = BS_AUTORADIOBUTTON;
        if (mode == TIME_SIGNAL_EVERY_MINUTE) {
            style |= WS_GROUP | WS_TABSTOP;
        }
        hTimeSignalIntervalRadios[mode - 1] = BindSettingsControl(hTimeSignalPage,
            ID_TIME_SIGNAL_INTERVAL_BASE + mode - 1, T(TIME_SIGNAL_TEXT_IDS[mode]), &timeSignalControls);
    }
    hAudioOutputLabel = BindSettingsLabel(hTimeSignalPage, IDC_AUDIO_OUTPUT_LABEL,
        T(TXT_AUDIO_OUTPUT_LABEL), &timeSignalControls);
    hAudioOutputCombo = BindSettingsControl(hTimeSignalPage, ID_AUDIO_OUTPUT, L"",
        &timeSignalControls, hAudioOutputLabel);
    HWND timeSignalNote = BindSettingsControl(hTimeSignalPage, ID_TIME_SIGNAL_NOTE, T(TXT_TIME_SIGNAL_NOTE));
    timeSignalControls.push_back(timeSignalNote);
    HWND timeSourceLabel = BindSettingsLabel(hTimePage, IDC_TIME_SOURCE_LABEL, T(TXT_TIME_SOURCE_LABEL),
        &timeControls);
    hTimeSourceCombo = BindSettingsControl(hTimePage, ID_TIME_SOURCE, L"", &timeControls, timeSourceLabel);
    SendMessageW(hTimeSourceCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(T(TXT_SYSTEM_TIME_LABEL)));
    SendMessageW(hTimeSourceCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(T(TXT_NTP_TIME_LABEL)));
    SendMessageW(hTimeSourceCombo, CB_SETCURSEL, useNtpTime ? 1 : 0, 0);
    hNtpPresetLabel = BindSettingsLabel(hTimePage, IDC_NTP_PRESET_LABEL, T(TXT_NTP_PRESET_FIELD_LABEL),
        &timeControls);
    hNtpPresetCombo = BindSettingsControl(hTimePage, ID_NTP_PRESET, L"", &timeControls, hNtpPresetLabel);
    for (int preset = 0; preset < NTP_PRESET_COUNT; preset++) {
        SendMessageW(hNtpPresetCombo, CB_ADDSTRING, 0,
            reinterpret_cast<LPARAM>(T(NTP_PRESET_TEXT_IDS[preset])));
    }
    SendMessageW(hNtpPresetCombo, CB_SETCURSEL, ntpPreset, 0);
    hNtpServersLabel = BindSettingsControl(hTimePage, IDC_NTP_SERVERS_LABEL, T(TXT_NTP_SERVERS_LABEL));
    timeControls.push_back(hNtpServersLabel);
    hNtpServersEdit = BindSettingsControl(hTimePage, ID_NTP_SERVERS, ntpServers.c_str(), &timeControls);
    hNtpSyncButton = BindSettingsControl(hTimePage, ID_NTP_SYNC, T(TXT_NTP_SYNC_LABEL), &timeControls);
    hNtpStatus = BindSettingsControl(hTimePage, IDC_NTP_STATUS, L"");
    timeControls.push_back(hNtpStatus);
    hNtpLogList = BindSettingsControl(hTimePage, ID_NTP_LOG, L"", &timeControls);
    InitializeNtpLog();
    hNtpSaveLogButton = BindSettingsControl(hTimePage, ID_NTP_SAVE_LOG, T(TXT_NTP_SAVE_LOG_LABEL),
        &timeControls);
    hTimeGlobalNote = BindSettingsControl(hTimePage, IDC_TIME_GLOBAL_NOTE, T(TXT_TIME_GLOBAL_NOTE));
    timeControls.push_back(hTimeGlobalNote);
    UpdateNtpSettingsControls();
    hAppFontLabel = BindSettingsLabel(hApplicationPage, IDC_APP_FONT_LABEL, T(TXT_APPLICATION_FONT_LABEL),
        &applicationControls);
    hAppFontButton = BindSettingsControl(hApplicationPage, ID_APP_FONT, L"", &applicationControls);
    hAppFontDefaultButton = BindSettingsControl(hApplicationPage, ID_APP_FONT_DEFAULT,
        T(TXT_DEFAULT_FONT_LABEL), &applicationControls);
    UpdateApplicationFontButtons();
    HWND appAntialiasLabel = BindSettingsLabel(hApplicationPage, IDC_APP_ANTIALIAS_LABEL,
        T(TXT_ANTIALIASING_LABEL), &applicationControls);
    hAppAntialiasCombo = BindSettingsControl(hApplicationPage, ID_APP_ANTIALIAS, L"",
        &applicationControls, appAntialiasLabel);
    PopulateFontAntialiasingCombo(hAppAntialiasCombo);
    SelectFontAntialiasing(hAppAntialiasCombo, appFontAntialiasing);
    HWND appLanguageLabel = BindSettingsLabel(hApplicationPage, IDC_APP_LANGUAGE_LABEL,
        T(TXT_APPLICATION_LANGUAGE_LABEL), &applicationControls);
    hLanguageCombo = BindSettingsControl(hApplicationPage, ID_LANGUAGE, L"", &applicationControls,
        appLanguageLabel);
    PopulateLanguageCombo(hLanguageCombo);
    SendMessageW(hLanguageCombo, CB_SETCURSEL, appLanguage, 0);
    HWND timeSignalSoundLabel = BindSettingsLabel(hApplicationPage, IDC_TIME_SIGNAL_SOUND_LABEL,
        T(TXT_TIME_SIGNAL_SOUND_LABEL), &applicationControls);
    hTimeSignalSoundCombo = BindSettingsControl(hApplicationPage, ID_TIME_SIGNAL_SOUND, L"",
        &applicationControls,
        timeSignalSoundLabel);
    SendMessageW(hTimeSignalSoundCombo, CB_ADDSTRING, 0,
        reinterpret_cast<LPARAM>(T(TXT_TIME_SIGNAL_GENERATED_SOUND_LABEL)));
    SendMessageW(hTimeSignalSoundCombo, CB_ADDSTRING, 0,
        reinterpret_cast<LPARAM>(T(TXT_TIME_SIGNAL_SYSTEM_SOUND_LABEL)));
    bool generatorRequired = IsTimeSignalGeneratorRequired();
    SendMessageW(hTimeSignalSoundCombo, CB_SETCURSEL, generatorRequired || generatedTimeSignal ? 0 : 1, 0);
    EnableWindow(hTimeSignalSoundCombo, !generatorRequired);
    settingsTimeSignalTestActive = false;
    hTimeSignalTestButton = BindSettingsControl(hApplicationPage, ID_TIME_SIGNAL_TEST,
        T(TXT_TEST_COMMAND_LABEL), &applicationControls);
    hTestAudioOutputLabel = BindSettingsLabel(hApplicationPage, IDC_TEST_AUDIO_OUTPUT_LABEL,
        T(TXT_TEST_AUDIO_OUTPUT_LABEL), &applicationControls);
    hTestAudioOutputCombo = BindSettingsControl(hApplicationPage, ID_TEST_AUDIO_OUTPUT, L"",
        &applicationControls, hTestAudioOutputLabel);
    FillAudioOutputCombo(hTestAudioOutputCombo, settingsTestAudioOutputs, settingsTestAudioOutputDevice);
    hTimeSignalVolumeLabel = BindSettingsLabel(hApplicationPage, IDC_TIME_SIGNAL_VOLUME_LABEL,
        T(TXT_TIME_SIGNAL_VOLUME_LABEL), &applicationControls);
    hTimeSignalVolumeTrackBar = BindSettingsControl(hApplicationPage, ID_TIME_SIGNAL_VOLUME, L"",
        &applicationControls);
    SendMessageW(hTimeSignalVolumeTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(TIME_SIGNAL_VOLUME_SLIDER_MIN,
        TIME_SIGNAL_VOLUME_SLIDER_MAX));
    for (int decibels = -54; decibels < 0; decibels += 6) {
        SendMessageW(hTimeSignalVolumeTrackBar, TBM_SETTIC, 0,
            TimeSignalVolumeSliderPosition(TimeSignalVolumeFromDecibels(decibels)));
    }
    SendMessageW(hTimeSignalVolumeTrackBar, TBM_SETLINESIZE, 0, 10);
    SendMessageW(hTimeSignalVolumeTrackBar, TBM_SETPAGESIZE, 0, 100);
    SendMessageW(hTimeSignalVolumeTrackBar, TBM_SETPOS, TRUE,
        TimeSignalVolumeSliderPosition(timeSignalVolume));
    SetWindowSubclass(hTimeSignalVolumeTrackBar, TimeSignalVolumeSubclassProc, ID_TIME_SIGNAL_VOLUME, 0);
    hTimeSignalVolumeValue = BindSettingsControl(hApplicationPage, IDC_TIME_SIGNAL_VOLUME_VALUE, L"",
        &applicationControls);
    UpdateTimeSignalVolumeControls();
    hDisableThemesCheck = BindSettingsControl(hApplicationPage, ID_VISUAL_STYLES,
        Mnemonic(TXT_VISUAL_STYLES).c_str(), &applicationControls);
    SetCheck(hDisableThemesCheck, themesDisabled);
    hUseXmlSettingsCheck = BindSettingsControl(hApplicationPage, ID_USE_XML_SETTINGS,
        T(TXT_XML_STORAGE_LABEL), &applicationControls);
    SetCheck(hUseXmlSettingsCheck, storageUsesXml);
    hSnapToWorkAreaCheck = BindSettingsControl(hApplicationPage, ID_SNAP_TO_WORK_AREA,
        T(TXT_SNAP_TO_WORK_AREA_LABEL), &applicationControls);
    SetCheck(hSnapToWorkAreaCheck, snapWidgetsToWorkArea);
    hStartWithWindowsCheck = BindSettingsControl(hApplicationPage, ID_START_WITH_WINDOWS,
        T(TXT_START_WITH_WINDOWS_LABEL), &applicationControls);
    SetCheck(hStartWithWindowsCheck, startWithWindows);
    hWarnUnsavedChangesCheck = BindSettingsControl(hApplicationPage, ID_WARN_UNSAVED_CHANGES,
        T(TXT_WARN_UNSAVED_CHANGES_LABEL), &applicationControls);
    SetCheck(hWarnUnsavedChangesCheck, warnOnUnsavedChanges);
    BindSettingsControl(hSettings, ID_IMPORT_SETTINGS, T(TXT_IMPORT_SETTINGS_LABEL));
    BindSettingsControl(hSettings, ID_EXPORT_SETTINGS, T(TXT_EXPORT_SETTINGS_LABEL));
    BindSettingsControl(hSettings, ID_SAVE, Mnemonic(TXT_SAVE).c_str());
    BindSettingsControl(hSettings, ID_CANCEL, Mnemonic(TXT_CANCEL).c_str());
    BindSettingsControl(hSettings, ID_APPLY, Mnemonic(TXT_APPLY).c_str());
    const std::vector<HWND>* groups[] = {
        &generalControls,
        &appearanceControls,
        &alarmControls,
        &timeSignalControls,
        &timeControls,
        &applicationControls
    };
    for (const std::vector<HWND>* group : groups) {
        for (HWND control : *group) {
            if (control == nullptr) {
                updatingSettingsControls = previousUpdating;
                return false;
            }
        }
    }
    UpdateApplicationControlWidths();
    UpdateSettingsTextControlLayout(hSettings);
    for (int tabIndex = 0; tabIndex < SETTINGS_TAB_COUNT; tabIndex++) {
        UpdateSettingsTextControlLayout(GetSettingsPage(tabIndex));
    }
    InitializeSettingsScrollBars();
    settingsGeneralCheckboxReferenceValid =
        GetSettingsCheckboxBaselineDistance(hPanelTimeNoticesCheck, hTimeFormatLabel,
            &settingsGeneralCheckboxBaselineDistances[0])
        && GetSettingsCheckboxBaselineDistance(hAdditionalEnabledChecks[0], hAdditionalNameLabels[0],
            &settingsGeneralCheckboxBaselineDistances[1])
        && GetSettingsCheckboxBaselineDistance(hAdditionalEnabledChecks[1], hAdditionalNameLabels[1],
            &settingsGeneralCheckboxBaselineDistances[2]);
    ApplyUiStyle(hSettings);
    updatingSettingsControls = previousUpdating;
    return true;
}

/// Captures one control's text, selection, check state, slider position, or monitor checkboxes.
static void CaptureSettingsControlValue(HWND control, int page,
        std::vector<SettingsControlValue>* values) {
    wchar_t className[32] = {};
    GetClassNameW(control, className, ARRAYSIZE(className));
    int id = GetDlgCtrlID(control);
    if (_wcsicmp(className, L"EDIT") == 0) {
        values->push_back(SettingsControlValue{ page, id, WM_SETTEXT, 0, 0, GetControlText(control) });
    } else if ((_wcsicmp(className, WC_COMBOBOXEXW) == 0 || _wcsicmp(className, WC_COMBOBOXW) == 0)
            && control != hAudioOutputCombo
            && control != hTestAudioOutputCombo) {
        WPARAM selectedItemIndex = static_cast<WPARAM>(SendMessageW(control, CB_GETCURSEL, 0, 0));
        SettingsControlValue savedComboSelection{ page, id, CB_SETCURSEL, selectedItemIndex, 0, {} };
        values->push_back(savedComboSelection);
    } else if (_wcsicmp(className, L"BUTTON") == 0) {
        LONG_PTR type = GetWindowLongPtrW(control, GWL_STYLE) & BS_TYPEMASK;
        if (type == BS_AUTOCHECKBOX || type == BS_AUTORADIOBUTTON || type == BS_AUTO3STATE) {
            WPARAM savedCheckState = static_cast<WPARAM>(SendMessageW(control, BM_GETCHECK, 0, 0));
            SettingsControlValue savedButtonCheckState{ page, id, BM_SETCHECK, savedCheckState, 0, {} };
            values->push_back(savedButtonCheckState);
        }
    } else if (_wcsicmp(className, TRACKBAR_CLASSW) == 0) {
        LPARAM position = SendMessageW(control, TBM_GETPOS, 0, 0);
        SettingsControlValue sliderState{ page, id, TBM_SETPOS, TRUE, position, {} };
        values->push_back(sliderState);
    } else if (control == hMonitorList) {
        for (int item = 0; item < ListView_GetItemCount(control); item++) {
            WPARAM itemIndex = static_cast<WPARAM>(item);
            LPARAM checkState = static_cast<LPARAM>(ListView_GetItemState(control, item,
                LVIS_STATEIMAGEMASK));
            SettingsControlValue itemState{ page, id, LVM_SETITEMSTATE, itemIndex, checkState, {} };
            values->push_back(itemState);
        }
    }
}

/// Captures raw Settings values, including unfinished edit text, before the controls are replaced.
static std::vector<SettingsControlValue> CaptureSettingsControlValues() {
    std::vector<SettingsControlValue> values;
    WPARAM selectedTypeIndex = static_cast<WPARAM>(SendMessageW(hAddType, CB_GETCURSEL, 0, 0));
    SettingsControlValue typeSelection{ -1, ID_ADD_TYPE, CB_SETCURSEL, selectedTypeIndex, 0, {} };
    values.push_back(typeSelection);
    for (int page = 0; page < ARRAYSIZE(settingsControlGroups); page++) {
        for (HWND control : *settingsControlGroups[page]) {
            CaptureSettingsControlValue(control, page, &values);
        }
    }
    return values;
}

/// Destroys Settings child windows and clears handles and transient state used during their recreation.
static void DestroySettingsChildControls() {
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
    hPanelTimeNoticesCheck = nullptr;
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
    hWarnUnsavedChangesCheck = nullptr;
    hTimeSignalSoundCombo = nullptr;
    hAudioOutputLabel = nullptr;
    hAudioOutputCombo = nullptr;
    settingsAudioOutputs.clear();
    settingsTestAudioOutputs.clear();
    hTestAudioOutputLabel = nullptr;
    hTestAudioOutputCombo = nullptr;
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
    hTimeSignalEnabledCheck = nullptr;
    std::fill(std::begin(hTimeSignalIntervalRadios), std::end(hTimeSignalIntervalRadios), nullptr);
    hStartWithWindowsCheck = nullptr;
    hSoundsMutedCheck = nullptr;
    hBorderColorButton = nullptr;
    for (int day = 0; day < ALARM_DAY_COUNT; day++) {
        hAlarmDayChecks[day] = nullptr;
    }
}

/// Restores raw values, widget selection, dependent captions, and the pending Apply state.
static void RestoreSettingsControlValues(const std::vector<SettingsControlValue>& values,
        const std::vector<int>& selectedWidgets, bool applyEnabled) {
    bool previousUpdating = updatingSettingsControls;
    updatingSettingsControls = true;
    for (const SettingsControlValue& value : values) {
        HWND control = value.page < 0 ? GetDlgItem(hSettings, value.id) : nullptr;
        if (value.page >= 0) {
            for (HWND candidate : *settingsControlGroups[value.page]) {
                if (GetDlgCtrlID(candidate) == value.id) {
                    control = candidate;
                    break;
                }
            }
        }
        if (control == nullptr) {
            continue;
        }
        if (value.message == WM_SETTEXT) {
            SetWindowTextW(control, value.text.c_str());
        } else if (value.message == LVM_SETITEMSTATE) {
            LVITEMW item = {};
            item.stateMask = LVIS_STATEIMAGEMASK;
            item.state = static_cast<UINT>(value.value);
            SendMessageW(control, LVM_SETITEMSTATE, value.parameter, reinterpret_cast<LPARAM>(&item));
        } else {
            SendMessageW(control, value.message, value.parameter, value.value);
        }
    }
    SendMessageW(hWidgetList, LB_SETSEL, FALSE, -1);
    for (int index : selectedWidgets) {
        SendMessageW(hWidgetList, LB_SETSEL, TRUE, index);
    }
    updatingSettingsControls = previousUpdating;
    UpdateSettingControlAvailability();
    UpdateNtpSettingsControls();
    UpdateAlarmVolumeControls();
    UpdateAppearanceSliderLabels();
    UpdateTimeSignalVolumeControls();
    UpdateSettingsApplyButton();
    if (applyEnabled) {
        EnableWindow(GetDlgItem(hSettings, ID_APPLY), TRUE);
    }
}

/// Recreates Settings child controls with painting and outer resizing suspended, restoring values and tab.
static bool RecreateSettingsChildControls(bool preserveValues, int selectedTab,
        const std::vector<SettingsControlValue>& values, const std::vector<int>& selectedWidgets,
        bool applyEnabled) {
    WindowRedrawScope redraw(hSettings);
    settingsLayoutSuspended = true;
    DestroySettingsChildControls();
    SetWindowTextW(hSettings, T(TXT_SETTINGS));
    bool controlsCreated = RestoreSettingsRootControls() && CreateSettingsControls();
    if (controlsCreated) {
        RefreshWidgetList(true, false);
        LoadDraftIntoControls();
        if (hTabs != nullptr) {
            if (preserveValues) {
                RestoreSettingsControlValues(values, selectedWidgets, applyEnabled);
            }
            TabCtrl_SetCurSel(hTabs, std::clamp(selectedTab, 0, SETTINGS_TAB_COUNT - 1));
            ShowSettingsTab(TabCtrl_GetCurSel(hTabs));
        }
    }
    settingsLayoutSuspended = false;
    return controlsCreated;
}

/// Recreates Settings controls, retaining the selected tab and optional draft values.
/// Defers the outer resize until all controls are ready and painting is enabled.
static void RebuildSettingsControls(bool preserveValues = false) {
    timeSignalVolumeDragging = false;
    settingsTimeSignalTestActive = false;
    StopTimeSignalVolumePreview();
    if (hSettings == nullptr || !IsWindow(hSettings)) {
        return;
    }
    StopSettingsPreview();
    bool applyEnabled = preserveValues && IsWindowEnabled(GetDlgItem(hSettings, ID_APPLY));
    std::vector<SettingsControlValue> values;
    std::vector<int> selectedWidgets;
    if (preserveValues) {
        SaveControlsToDraft(false);
        selectedWidgets = GetSelectedWidgetIndices();
        values = CaptureSettingsControlValues();
    }
    int selectedTab = hTabs == nullptr ? 0 : TabCtrl_GetCurSel(hTabs);
    settingsTab = std::clamp(selectedTab, 0, SETTINGS_TAB_COUNT - 1);
    bool controlsCreated =
        RecreateSettingsChildControls(preserveValues, selectedTab, values, selectedWidgets, applyEnabled);
    if (!controlsCreated) {
        CloseSettingsWindow();
        return;
    }
    UpdateSettingsWindowLayout();
    SetFocus(preserveValues ? hAppFontButton : hAddType);
}

/// Stops tests, restores uncommitted previews, remembers the form position, tab and widget, and destroys
/// settings controls. Clears draft state and restores normal fullscreen presentation.
static void CloseSettingsWindow() {
    hSettingsOpenCombo = nullptr;
    settingsComboInitialSelection = CB_ERR;
    settingsComboAccepted = false;
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
        settingsWidgetId = -1;
        if (selectedDraftIndex >= 0
                && selectedDraftIndex < static_cast<int>(settingsDraft.size())
                && FindWidgetById(settingsDraft[selectedDraftIndex].id) != nullptr) {
            settingsWidgetId = settingsDraft[selectedDraftIndex].id;
        }
        DestroyWindow(hSettings);
        SaveAllSettings();
    }
    hSettings = nullptr;
    hSettingsDefaultButton = nullptr;
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
    hWarnUnsavedChangesCheck = nullptr;
    hTimeSignalSoundCombo = nullptr;
    hAudioOutputLabel = nullptr;
    hAudioOutputCombo = nullptr;
    settingsAudioOutputs.clear();
    settingsTestAudioOutputs.clear();
    hTestAudioOutputLabel = nullptr;
    hTestAudioOutputCombo = nullptr;
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
    hTimeSignalEnabledCheck = nullptr;
    std::fill(std::begin(hTimeSignalIntervalRadios), std::end(hTimeSignalIntervalRadios), nullptr);
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
    hNtpLogList = nullptr;
    hNtpSaveLogButton = nullptr;
    hTimeGlobalNote = nullptr;
    settingsDraft.clear();
    settingsAppliedWidgets.clear();
    settingsAppearanceOriginals.clear();
    settingsAppearancePreviewIds.clear();
    settingsAppearancePreviewActive = false;
    settingsApplicationFontPreviewActive = false;
    RefreshFullscreenPresentation();
}

/// Shows an XML open or save dialog in the shared remembered directory and returns the accepted path.
static bool ChooseSettingsXmlFile(bool save, std::wstring* path) {
    if (path == nullptr) {
        return false;
    }
    const COMDLG_FILTERSPEC filters[] = {
        COMDLG_FILTERSPEC{ T(TXT_XML_FILE_TYPE_LABEL), L"*.xml" }
    };
    std::wstring fileName;
    if (save) {
        fileName = SuggestedSaveFileName(L"CalClock-settings", L"xml");
    }
    return ChooseApplicationFile(save, fileName.c_str(), filters, ARRAYSIZE(filters), nullptr, path);
}

/// Validates and applies the current draft before exporting a settings snapshot to the chosen XML file,
/// reporting write failure.
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
        MessageBoxW(hSettings, T(TXT_SETTINGS_EXPORT_FAILED), T(TXT_SETTINGS), MB_OK | MB_ICONERROR);
    }
}

/// Validates a chosen XML snapshot, replaces application and widget settings, rebuilds affected windows,
/// and saves using the selected backend.
static void ImportSettings() {
    std::wstring path;
    if (!ChooseSettingsXmlFile(false, &path)) {
        return;
    }
    SettingsSnapshot snapshot = {};
    if (!ReadSettingsXml(path, appLanguage, CreateStoredWidgetDefaults, &snapshot)) {
        MessageBoxW(hSettings, T(TXT_INVALID_SETTINGS_FILE), T(TXT_SETTINGS), MB_OK | MB_ICONWARNING);
        return;
    }
    snapshot.fileDialogDirectory = fileDialogDirectory;
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
    if (helpForm.GetWindow() != nullptr) {
        ApplyUiStyle(helpForm.GetWindow());
    }
    if (aboutForm.GetWindow() != nullptr) {
        ApplyUiStyle(aboutForm.GetWindow());
    }
    UpdateTrayIcon();
    SaveAllSettings();
    if (useNtpTime) {
        StartNtpSynchronization(true);
    }
    ShowSettingsWindow();
}

/// Opens or activates the non-topmost settings form, selecting an explicit widget or restoring the last
/// closed selection. Creates draft snapshots and fullscreen previews when opening a new form; a missing
/// widget falls back to the first.
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
        settingsWindowState.BringToFront();
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
    settingsTestAudioOutputDevice = testAudioOutputDevice;
    settingsAppFontDialogSize = appFontDialogSize;
    settingsAppFontWeight = appFontWeight;
    settingsAppFontItalic = appFontItalic;
    if (widgetId < 0) {
        widgetId = settingsWidgetId;
    }
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
    hSettings = CreateSettingsDialog(IDD_SETTINGS, nullptr, SettingsDialogProc, 0);
    if (hSettings == nullptr) {
        return;
    }
    HICON windowIcon = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_CLOCK));
    SendMessageW(hSettings, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(windowIcon));
    SendMessageW(hSettings, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(windowIcon));
    SetWindowTextW(hSettings, T(TXT_SETTINGS));
    RECT content = {};
    GetClientRect(hSettings, &content);
    settingsContentWidth = content.right;
    settingsContentHeight = content.bottom;
    GetSettingsWindowLayout(extendedStyle, &style, &settingsWidth, &settingsHeight);
    SetWindowLongPtrW(hSettings, GWL_STYLE, style);
    const PersistWindowStateData& placement = settingsWindowState.GetState();
    SetWindowPos(hSettings, nullptr, 0, 0, settingsWidth, settingsHeight,
        SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
    if (placement.x != CW_USEDEFAULT && placement.y != CW_USEDEFAULT) {
        SetWindowPos(hSettings, nullptr, placement.x, placement.y, 0, 0,
            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    } else {
        PositionInformationWindowByWindowsDefault(hSettings);
    }
    RefreshFullscreenPresentation();
    if (!CreateSettingsControls()) {
        CloseSettingsWindow();
        return;
    }
    RefreshWidgetList(true, false);
    LoadDraftIntoControls();
    if (hTabs != nullptr) {
        TabCtrl_SetCurSel(hTabs, std::clamp(settingsTab, 0, SETTINGS_TAB_COUNT - 1));
        ShowSettingsTab(TabCtrl_GetCurSel(hTabs));
    }
    UpdateSettingsApplyButton();
    if (!settingsWindowState.Attach(hSettings, "Settings")) {
        CloseSettingsWindow();
        return;
    }
    settingsWindowState.Show();
    SetActiveWindow(hSettings);
    SetFocus(hAddType);
}

/// Lets information windows handle Enter, Escape and Tab from their read-only text fields.
LRESULT CALLBACK InformationTextSubclassProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    UNREFERENCED_PARAMETER(referenceData);
    if (msg == WM_GETDLGCODE) {
        LRESULT result = DefSubclassProc(window, msg, wParam, lParam);
        if (wParam == VK_RETURN || wParam == VK_ESCAPE || wParam == VK_TAB) {
            result &= ~DLGC_WANTALLKEYS;
        }
        return result;
    }
    if (msg == WM_NCDESTROY) {
        RemoveWindowSubclass(window, InformationTextSubclassProc, subclassId);
    }
    return DefSubclassProc(window, msg, wParam, lParam);
}

/// Releases the cached Unicode boundary analysis and its retained text.
void ResetInformationWordBreak() {
    if (informationWordBreakState.analysis != nullptr) {
        if (FAILED(ScriptStringFree(&informationWordBreakState.analysis))) {
            OutputDebugStringW(
                L"CalClock: ScriptStringFree failed while clearing Unicode word-break analysis.\r\n");
        }
        informationWordBreakState.analysis = nullptr;
    }
    informationWordBreakState.text.clear();
}

/// Supplies the same native Unicode word and cluster boundaries to the Help and About edits.
int CALLBACK InformationWordBreakProc(wchar_t* text, int position, int length, int code) {
    if (length <= 0) {
        return 0;
    }
    position = std::clamp(position, 0, length);
    if (informationWordBreakState.text.size() != static_cast<size_t>(length)
            || wmemcmp(informationWordBreakState.text.c_str(), text, length) != 0) {
        ResetInformationWordBreak();
        informationWordBreakState.text.assign(text, length);
        HRESULT status = ScriptStringAnalyse(nullptr, informationWordBreakState.text.c_str(), length, 0, -1,
            SSA_BREAK, 0, nullptr, nullptr, nullptr, nullptr, nullptr, &informationWordBreakState.analysis);
        if (FAILED(status)) {
            ResetInformationWordBreak();
            if (code == WB_ISDELIMITER) {
                return position < length && IsUnicodeWhitespace(text[position]);
            }
            return code == WB_LEFT ? 0 : length;
        }
    }
    const SCRIPT_LOGATTR* attributes = ScriptString_pLogAttr(informationWordBreakState.analysis);
    if (code == WB_ISDELIMITER) {
        return position < length && attributes[position].fWhiteSpace;
    }
    if (code == WB_LEFT) {
        if (position == length) {
            position--;
        }
        while (position > 0 && (!attributes[position].fCharStop
                || !attributes[position].fSoftBreak && !attributes[position - 1].fWhiteSpace)) {
            position--;
        }
    } else if (code == WB_RIGHT) {
        if (position < length) {
            position++;
        }
        while (position < length && (!attributes[position].fCharStop
                || !attributes[position].fSoftBreak && !attributes[position - 1].fWhiteSpace)) {
            position++;
        }
    }
    return position;
}

/// Updates each open information form through its own content and layout implementation.
void RefreshInformationWindows() {
    helpForm.Refresh();
    aboutForm.Refresh();
}

/// Positions an information-window child without activation or Z-order changes, enforcing positive
/// dimensions.
void PlaceInformationControl(HWND window, int id, int x, int y, int width, int height) {
    HWND control = GetDlgItem(window, id);
    int controlWidth = std::max(1, width);
    int controlHeight = std::max(1, height);
    UINT flags = SWP_NOZORDER | SWP_NOACTIVATE;
    SetWindowPos(control, nullptr, x, y, controlWidth, controlHeight, flags);
}

/// Measures a label's wrapped height at the requested width using its actual font, or returns zero if a DC
/// is unavailable.
int InformationLabelHeight(HWND control, int width) {
    HDC dc = GetDC(control);
    if (dc == nullptr) {
        return 0;
    }
    std::wstring text = GetControlText(control);
    HFONT font = reinterpret_cast<HFONT>(SendMessageW(control, WM_GETFONT, 0, 0));
    HGDIOBJ oldFont = font == nullptr ? nullptr : SelectObject(dc, font);
    RECT bounds = { 0, 0, std::max(1, width), 0 };
    int height = DrawWordWrappedText(dc, text, bounds, DT_CALCRECT | DT_NOPREFIX);
    if (oldFont != nullptr) {
        SelectObject(dc, oldFont);
    }
    ReleaseDC(control, dc);
    return height;
}

/// Measures native dialog base units from the supplied interface font.
bool GetDialogFontBaseUnits(HFONT font, SIZE* units) {
    HDC dc = GetDC(nullptr);
    if (dc == nullptr) {
        return false;
    }
    HGDIOBJ previous = font == nullptr ? nullptr : SelectObject(dc, font);
    SIZE alphabet = {};
    TEXTMETRICW metrics = {};
    bool measured = GetTextExtentPoint32W(dc, L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz",
        52, &alphabet) && GetTextMetricsW(dc, &metrics);
    if (measured) {
        units->cx = (alphabet.cx / 26 + 1) / 2;
        units->cy = metrics.tmHeight;
    }
    if (previous != nullptr) {
        SelectObject(dc, previous);
    }
    ReleaseDC(nullptr, dc);
    return measured;
}

/// Converts vertical dialog units to pixels using the font base unit, capped so a standard button is at most
/// 28 pixels.
int DialogHeightFromUnits(int value, int baseUnit) {
    if (baseUnit * DIALOG_BUTTON_HEIGHT_DLU > MAX_DIALOG_BUTTON_HEIGHT * 8) {
        return MulDiv(value, MAX_DIALOG_BUTTON_HEIGHT, DIALOG_BUTTON_HEIGHT_DLU);
    }
    return MulDiv(value, baseUnit, 8);
}

/// Caps initial dialog and child Y dimensions using the standard button height limit, preserving X dimensions
/// and fonts. Uses the original extended resource height when available to avoid retaining Windows initial
/// work-area clipping.
void LimitDialogVerticalUnits(HWND window, int resourceId) {
    RECT units = { 0, 0, 0, 8 };
    if (!MapDialogRect(window, &units)
            || units.bottom * DIALOG_BUTTON_HEIGHT_DLU <= MAX_DIALOG_BUTTON_HEIGHT * 8) {
        return;
    }
    HWND control = GetWindow(window, GW_CHILD);
    while (control != nullptr) {
        RECT bounds = {};
        if (GetWindowRect(control, &bounds)) {
            MapWindowPoints(HWND_DESKTOP, window, reinterpret_cast<POINT*>(&bounds), 2);
            int top = DialogHeightFromUnits(MulDiv(bounds.top, 8, units.bottom), units.bottom);
            int height =
                DialogHeightFromUnits(MulDiv(bounds.bottom - bounds.top, 8, units.bottom), units.bottom);
            SetWindowPos(control, nullptr, bounds.left, top, bounds.right - bounds.left, height,
                SWP_NOZORDER | SWP_NOACTIVATE);
        }
        control = GetWindow(control, GW_HWNDNEXT);
    }
    RECT client = {};
    RECT bounds = {};
    if (GetClientRect(window, &client) && GetWindowRect(window, &bounds)) {
        int dialogHeight = MulDiv(client.bottom, 8, units.bottom);
        HRSRC resource = FindResourceW(hInstance, MAKEINTRESOURCEW(resourceId), RT_DIALOG);
        HGLOBAL loaded = resource == nullptr ? nullptr : LoadResource(hInstance, resource);
        const WORD* definition = loaded == nullptr ? nullptr : static_cast<const WORD*>(LockResource(loaded));
        if (definition != nullptr && SizeofResource(hInstance, resource) >= 26 && definition[1] == 0xFFFF) {
            dialogHeight = static_cast<short>(definition[12]);
        }
        int height = DialogHeightFromUnits(dialogHeight, units.bottom);
        SetWindowPos(window, nullptr, 0, 0, bounds.right - bounds.left,
            bounds.bottom - bounds.top - client.bottom + height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
    }
}

/// Converts current information-dialog font units to native pixel dimensions.
SIZE InformationDialogUnits(HFONT font, int x, int y) {
    SIZE units = {};
    if (!GetDialogFontBaseUnits(font, &units)) {
        return SIZE{};
    }
    return SIZE{ MulDiv(x, units.cx, 4), DialogHeightFromUnits(y, units.cy) };
}

/// Measures the common native Close button using its current font and existing dialog-unit minimum and
/// padding.
SIZE InformationButtonSize(HWND window, HFONT font) {
    SIZE button = InformationDialogUnits(font, DIALOG_BUTTON_WIDTH_DLU, DIALOG_BUTTON_HEIGHT_DLU);
    SIZE ideal = {};
    HWND closeButton = GetDlgItem(window, ID_INFO_CLOSE);
    if (!SendMessageW(closeButton, BCM_GETIDEALSIZE, 0, reinterpret_cast<LPARAM>(&ideal))) {
        HDC dc = GetDC(closeButton);
        if (dc != nullptr) {
            HFONT controlFont = reinterpret_cast<HFONT>(SendMessageW(closeButton, WM_GETFONT, 0, 0));
            HGDIOBJ previous = controlFont == nullptr ? nullptr : SelectObject(dc, controlFont);
            std::wstring text = GetControlText(closeButton);
            RECT bounds = {};
            DrawTextW(dc, text.c_str(), static_cast<int>(text.size()), &bounds, DT_CALCRECT | DT_SINGLELINE);
            SIZE padding = InformationDialogUnits(font, 12, 0);
            ideal.cx = bounds.right + padding.cx + 2 * GetSystemMetrics(SM_CXEDGE);
            if (previous != nullptr) {
                SelectObject(dc, previous);
            }
            ReleaseDC(closeButton, dc);
        }
    }
    button.cx = std::max(button.cx, ideal.cx);
    return button;
}

/// Obtains native CW_USEDEFAULT placement from an invisible overlapped window and moves the hidden dialog
/// there.
bool PositionInformationWindowByWindowsDefault(HWND window) {
    RECT bounds = {};
    if (!GetWindowRect(window, &bounds)) {
        return false;
    }
    HWND positionWindow = CreateWindowExW(0, L"STATIC", L"", WS_OVERLAPPED, CW_USEDEFAULT, CW_USEDEFAULT,
        bounds.right - bounds.left, bounds.bottom - bounds.top, nullptr, nullptr, hInstance, nullptr);
    if (positionWindow == nullptr) {
        return false;
    }
    bool positioned = GetWindowRect(positionWindow, &bounds) != FALSE;
    DestroyWindow(positionWindow);
    if (!positioned) {
        return false;
    }
    return SetWindowPos(window, nullptr, bounds.left, bounds.top, 0, 0,
        SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE) != FALSE;
}

/// Dispatches settings notifications and actions, validating edits and coordinating selection, previews,
/// duplication, and persistence. Disables Apply only after its successful explicit invocation.
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
                && type >= 0
                && type < WIDGET_TYPE_COUNT) {
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
                    preview.panelTimeNotices = config.panelTimeNotices;
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
                    if (std::find(settingsAppearancePreviewIds.begin(), settingsAppearancePreviewIds.end(),
                        config.id) == settingsAppearancePreviewIds.end()) {
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
    } else if (id == ID_UTC && notification == BN_CLICKED
            || id == ID_TIMEZONE && notification == CBN_SELCHANGE) {
        UpdateSettingControlAvailability();
    } else if ((id == ID_ALARM_ENABLED || id == ID_TIME_SIGNAL_ENABLED) && notification == BN_CLICKED) {
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
    } else if (id == ID_TEST_AUDIO_OUTPUT && notification == CBN_SELCHANGE) {
        if (IsWindowEnabled(hTestAudioOutputCombo)) {
            settingsTestAudioOutputDevice =
                SelectedAudioOutputDevice(hTestAudioOutputCombo, settingsTestAudioOutputs);
            UpdateTimeSignalVolumePreview();
        }
    } else if (id == ID_AUDIO_OUTPUT && notification == CBN_SELCHANGE) {
        if (IsWindowEnabled(hAudioOutputCombo)
                && selectedDraftIndex >= 0
                && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
            settingsDraft[selectedDraftIndex].timeSignalOutputDevice =
                SelectedAudioOutputDevice(hAudioOutputCombo, settingsAudioOutputs);
        }
    } else if (id == ID_TIME_SIGNAL_SOUND && notification == CBN_SELCHANGE) {
        UpdateTimeSignalVolumeControls();
        UpdateSettingsSelectionState();
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
    } else if (id == ID_NTP_SAVE_LOG && notification == BN_CLICKED) {
        SaveNtpLog();
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
        WidgetConfig config = DefaultConfig(static_cast<WidgetType>(type),
            static_cast<int>(settingsDraft.size()));
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
        int response = MessageBoxW(hSettings, T(TXT_DELETE_CONFIRM), T(TXT_SETTINGS),
            MB_YESNO | MB_ICONQUESTION);
        SetFocus(hWidgetList);
        if (response != IDYES) {
            return;
        }
        std::sort(selected.begin(), selected.end());
        int firstRemoved = selected.front();
        for (std::vector<int>::reverse_iterator index = selected.rbegin();
                index != selected.rend();
                index++) {
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
    } else if ((id == ID_SHOW_TODAY || id == ID_WEEK_NUMBERS || id == ID_SUNDAY_FIRST)
            && notification == BN_CLICKED) {
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
        RequestCloseSettingsWindow();
    }
}

/// Prompts before user-requested settings closure when warning is enabled and Apply is active.
/// Saves through the existing validation path, discards on No, and keeps the form open on Cancel.
static void RequestCloseSettingsWindow() {
    if (hSettings == nullptr || !IsWindowEnabled(hSettings)) {
        return;
    }
    if (hSettingsOpenCombo != nullptr) {
        SendMessageW(hSettingsOpenCombo, CB_SHOWDROPDOWN, FALSE, 0);
    }
    UpdateSettingsApplyButton();
    HWND applyButton = GetDlgItem(hSettings, ID_APPLY);
    if (warnOnUnsavedChanges && IsWindowEnabled(applyButton)) {
        int response = MessageBoxW(hSettings, T(TXT_UNSAVED_SETTINGS_PROMPT), T(TXT_SETTINGS),
            MB_YESNOCANCEL | MB_ICONWARNING);
        if (response == IDYES) {
            HandleSettingsCommand(ID_SAVE, BN_CLICKED);
            return;
        }
        if (response != IDNO) {
            return;
        }
    }
    CloseSettingsWindow();
}

/// Routes application exit through the settings save question and leaves all windows open when closure is
/// canceled.
static void RequestExitApplication() {
    if (hSettings != nullptr) {
        RequestCloseSettingsWindow();
        if (hSettings != nullptr) {
            return;
        }
    }
    DestroyWindow(hController);
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

/// Prepares an opaque native clock face in a compatible bitmap before erasing the visible child background.
/// Keeps the native paint path and falls back to the original background brush if buffering is unavailable.
static LRESULT ErasePanelAnalogBackground(HWND window, const Widget* widget, HDC target) {
    RECT client = {};
    GetClientRect(window, &client);
    COLORREF color = PanelBackgroundColor(widget);
    HDC memory = CreateCompatibleDC(target);
    HBITMAP bitmap = CreateCompatibleBitmap(target, client.right, client.bottom);
    bool rendered = false;
    if (memory != nullptr && bitmap != nullptr) {
        HGDIOBJ previous = SelectObject(memory, bitmap);
        if (previous != nullptr && previous != HGDI_ERROR) {
            rendered = RenderAnalogClock(window, memory, LayeredOpaquePixel(color))
                && BitBlt(target, 0, 0, client.right, client.bottom, memory, 0, 0, SRCCOPY) != FALSE;
            SelectObject(memory, previous);
        }
    }
    if (bitmap != nullptr) {
        DeleteObject(bitmap);
    }
    if (memory != nullptr) {
        DeleteDC(memory);
    }
    if (!rendered) {
        HBRUSH background = CreateSolidBrush(color);
        FillRect(target, &client, background);
        DeleteObject(background);
    }
    return 1;
}

/// Handles an additional clock's size menu, panel dragging, background painting, and theme updates without
/// enabling a second hand.
static LRESULT CALLBACK AdditionalAnalogChildProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    HWND parent = GetParent(window);
    Widget* widget = reinterpret_cast<Widget*>(GetWindowLongPtrW(parent, GWLP_USERDATA));
    int index = static_cast<int>(referenceData);
    if (msg == WM_NCDESTROY) {
        RemoveWindowSubclass(window, AdditionalAnalogChildProc, subclassId);
    } else if (widget != nullptr && index >= 0 && index < ADDITIONAL_CLOCK_COUNT) {
        if (msg == WM_ERASEBKGND) {
            return ErasePanelAnalogBackground(window, widget, reinterpret_cast<HDC>(wParam));
        }
        if (msg == WM_RBUTTONUP || msg == WM_CONTEXTMENU) {
            POINT point = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
            if (msg == WM_RBUTTONUP) {
                ClientToScreen(window, &point);
            } else if (point.x == -1 && point.y == -1) {
                RECT rect = {};
                GetWindowRect(window, &rect);
                point = POINT{ (rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2 };
            }
            ShowAdditionalClockContextMenu(widget, index, point);
            return 0;
        }
        if (msg == WM_LBUTTONDBLCLK) {
            return 0;
        }
        if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP || msg == WM_MOUSEMOVE) {
            POINT point = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
            MapWindowPoints(window, parent, &point, 1);
            return SendMessageW(parent, msg, wParam, MAKELPARAM(point.x, point.y));
        }
    }
    LRESULT result = DefSubclassProc(window, msg, wParam, lParam);
    if (msg == WM_THEMECHANGED && widget != nullptr && index >= 0 && index < ADDITIONAL_CLOCK_COUNT) {
        ConfigureAnalogClockControl(window,
            NormalizeAnalogClockSize(widget->config.additionalClocks[index].size), false);
    }
    return result;
}

/// Recognizes successive panel-face clicks within Windows double-click time and distance limits and updates
/// click tracking.
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

/// Integrates the primary native clock with widget dragging, face-only second-hand toggling, context menus,
/// and identification painting.
static LRESULT CALLBACK AnalogChildProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) {
    HWND parent = GetParent(window);
    Widget* widget = reinterpret_cast<Widget*>(GetWindowLongPtrW(parent, GWLP_USERDATA));
    if (widget != nullptr) {
        if (msg == WM_ERASEBKGND && widget->config.type == WIDGET_PANEL) {
            return ErasePanelAnalogBackground(window, widget, reinterpret_cast<HDC>(wParam));
        }
        if (msg == WM_LBUTTONDOWN && IsPanelAnalogDoubleClick(widget, lParam)) {
            msg = WM_LBUTTONDBLCLK;
        }
        if (msg == WM_LBUTTONDBLCLK) {
            widget->lastAnalogClickTick = 0;
        }
        if (msg == WM_LBUTTONDOWN
                || msg == WM_LBUTTONUP
                || msg == WM_MOUSEMOVE
                || msg == WM_LBUTTONDBLCLK
                || msg == WM_RBUTTONUP
                || msg == WM_CONTEXTMENU) {
            if (msg != WM_CONTEXTMENU) {
                POINT point = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
                MapWindowPoints(window, parent, &point, 1);
                lParam = MAKELPARAM(point.x, point.y);
            }
            return SendMessageW(parent, msg, wParam, lParam);
        }
        if (widget->analogProc != nullptr) {
            LRESULT result = CallWindowProcW(widget->analogProc, window, msg, wParam, lParam);
            if (msg == WM_THEMECHANGED) {
                bool showAnalogSeconds = widget->config.showSeconds
                    && AnalogClockSupportsSeconds(widget->config.size);
                ConfigureAnalogClockControl(window, widget->config.size, showAnalogSeconds);
            }
            return result;
        }
    }
    return DefWindowProcW(window, msg, wParam, lParam);
}

/// Prepares the complete native calendar in a compatible bitmap for background erasure and client painting.
static void PaintPanelCalendarBuffered(HWND window, const Widget* widget, HDC target) {
    if (target == nullptr) {
        return;
    }
    RECT client = {};
    GetClientRect(window, &client);
    HDC memory = CreateCompatibleDC(target);
    HBITMAP bitmap = CreateCompatibleBitmap(target, client.right, client.bottom);
    HGDIOBJ previous = nullptr;
    HDC drawing = target;
    if (memory != nullptr && bitmap != nullptr) {
        previous = SelectObject(memory, bitmap);
        if (previous != nullptr && previous != HGDI_ERROR) {
            drawing = memory;
        }
    }
    CallWindowProcW(widget->calendarProc, window, WM_ERASEBKGND, reinterpret_cast<WPARAM>(drawing), 0);
    CallWindowProcW(widget->calendarProc, window, WM_PRINTCLIENT, reinterpret_cast<WPARAM>(drawing),
        PRF_CLIENT);
    if (memory != nullptr && previous != nullptr && previous != HGDI_ERROR) {
        BitBlt(target, 0, 0, client.right, client.bottom, memory, 0, 0, SRCCOPY);
        SelectObject(memory, previous);
    }
    if (bitmap != nullptr) {
        DeleteObject(bitmap);
    }
    if (memory != nullptr) {
        DeleteDC(memory);
    }
}

/// Preserves native calendar navigation while distinguishing title clicks from widget drags.
/// Applies the widget locale to native processing and handles context menus and identification feedback.
static LRESULT CALLBACK CalendarChildProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) {
    HWND parent = GetParent(window);
    Widget* widget = reinterpret_cast<Widget*>(GetWindowLongPtrW(parent, GWLP_USERDATA));
    if (widget != nullptr) {
        if (msg == WM_RBUTTONUP || msg == WM_CONTEXTMENU) {
            return SendMessageW(parent, msg, wParam, lParam);
        }
        if (msg == WM_CAPTURECHANGED || msg == WM_CANCELMODE) {
            widget->calendarTitlePressed = false;
            if (msg == WM_CANCELMODE && GetCapture() == window) {
                ReleaseCapture();
            }
        }
        if (msg == WM_MOUSEMOVE && widget->calendarTitlePressed) {
            POINT cursor = {};
            GetCursorPos(&cursor);
            int distanceX = abs(cursor.x - widget->calendarTitlePressScreen.x);
            int distanceY = abs(cursor.y - widget->calendarTitlePressScreen.y);
            if ((wParam & MK_LBUTTON) != 0
                && (distanceX >= GetSystemMetrics(SM_CXDRAG)
                    || distanceY >= GetSystemMetrics(SM_CYDRAG))) {
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
        if (msg == WM_LBUTTONUP && widget->calendarTitlePressed) {
            widget->calendarTitlePressed = false;
            ReleaseCapture();
            if (widget->calendarProc != nullptr) {
                CalendarLocaleScope localeScope(GetLanguageLocale(widget->config.language));
                CallWindowProcW(widget->calendarProc, window, WM_LBUTTONDOWN,
                    widget->calendarTitlePressKeys, widget->calendarTitlePressPosition);
                return CallWindowProcW(widget->calendarProc, window, WM_LBUTTONUP, wParam, lParam);
            }
            return 0;
        }
        if ((msg == WM_LBUTTONDOWN || msg == WM_LBUTTONDBLCLK) && widget->config.type == WIDGET_CALENDAR) {
            MCHITTESTINFO hit = {};
            hit.cbSize = sizeof(hit);
            hit.pt.x = GET_X_LPARAM(lParam);
            hit.pt.y = GET_Y_LPARAM(lParam);
            MonthCal_HitTest(window, &hit);
            bool titleArea =
                hit.uHit == MCHT_TITLEBK || hit.uHit == MCHT_TITLEMONTH || hit.uHit == MCHT_TITLEYEAR;
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
                return SendMessageW(parent, msg, wParam, lParam);
            }
        }
        if (widget->calendarProc != nullptr) {
            CalendarLocaleScope localeScope(GetLanguageLocale(widget->config.language));
            if (widget->config.type == WIDGET_PANEL) {
                if (msg == WM_ERASEBKGND) {
                    PaintPanelCalendarBuffered(window, widget, reinterpret_cast<HDC>(wParam));
                    return 1;
                }
                if (msg == WM_PAINT && wParam == 0) {
                    PAINTSTRUCT paint = {};
                    HDC target = BeginPaint(window, &paint);
                    PaintPanelCalendarBuffered(window, widget, target);
                    EndPaint(window, &paint);
                    return 0;
                }
            }
            LRESULT result = CallWindowProcW(widget->calendarProc, window, msg, wParam, lParam);
            if ((msg == WM_THEMECHANGED || msg == WM_SETTINGCHANGE) && widget->calendarFont != nullptr) {
                SendMessageW(window, WM_SETFONT, reinterpret_cast<WPARAM>(widget->calendarFont), TRUE);
            }
            if (msg == WM_PAINT
                    && widget->config.type == WIDGET_CALENDAR
                    && widget->identifyActive
                    && widget->identifyPhase) {
                DrawIdentificationOutline(window, false);
            }
            return result;
        }
    }
    return DefWindowProcW(window, msg, wParam, lParam);
}

/// Selects the widget's displayed current date, optionally preserving the calendar's month, year, or decade
/// view. An explicit navigation request returns to month view and focuses the calendar.
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
    widget->panelCalendarDateSupported = MonthCal_SetCurSel(widget->calendarChild, &today) != FALSE;
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

/// Moves the calendar selection to the displayed current day when its date changes, preserving the current
/// calendar view.
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

/// Opens the Windows Date and Time control panel, preferring the native control.exe path from a 32-bit
/// process.
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

/// Draws settings list rows and requests shared-buffer updates for native panel-link state changes.
/// Passes unrelated owner-draw requests to the native window procedure.
static LRESULT DrawWidgetItem(HWND window, Widget* widget, WPARAM wParam, LPARAM lParam) {
    DRAWITEMSTRUCT* item = reinterpret_cast<DRAWITEMSTRUCT*>(lParam);
    if (window == hSettings && DrawSettingsListItem(item)) {
        return TRUE;
    }
    bool panelLink = widget != nullptr
        && item != nullptr
        && (item->hwndItem == widget->panelDateLink || item->hwndItem == widget->panelTimeZoneLink);
    if (panelLink) {
        InvalidatePanelLink(item->hwndItem);
        return TRUE;
    }
    return DefWindowProcW(window, WM_DRAWITEM, wParam, lParam);
}

/// Defers dropdown navigation until the list closes, restores cancelled selections, and ignores unchanged
/// choices. Leaves ordinary keyboard selection changes in closed combos on their existing notification path.
static bool HandleSettingsComboNotification(HWND control, int* notification) {
    if (control == nullptr) {
        return false;
    }
    HWND parent = GetParent(control);
    if (GetSettingsComboBox(parent) == control) {
        control = parent;
    }
    wchar_t className[32] = {};
    GetClassNameW(control, className, ARRAYSIZE(className));
    if (_wcsicmp(className, WC_COMBOBOXW) != 0 && _wcsicmp(className, WC_COMBOBOXEXW) != 0) {
        return false;
    }
    if (*notification == CBN_DROPDOWN) {
        if (control == hAudioOutputCombo) {
            std::wstring selected = SelectedAudioOutputDevice(hAudioOutputCombo, settingsAudioOutputs);
            FillAudioOutputCombo(hAudioOutputCombo, settingsAudioOutputs, selected);
        }
        if (control == hTestAudioOutputCombo) {
            FillAudioOutputCombo(control, settingsTestAudioOutputs, settingsTestAudioOutputDevice);
        }
        hSettingsOpenCombo = control;
        settingsComboInitialSelection = static_cast<int>(SendMessageW(control, CB_GETCURSEL, 0, 0));
        settingsComboAccepted = false;
        UpdateComboBoxDropDownMetrics(control);
        return true;
    }
    if (control != hSettingsOpenCombo) {
        return false;
    }
    if (*notification == CBN_SELENDOK) {
        settingsComboAccepted = true;
        return true;
    }
    if (*notification == CBN_SELENDCANCEL) {
        settingsComboAccepted = false;
        return true;
    }
    if (*notification == CBN_SELCHANGE) {
        return true;
    }
    if (*notification == CBN_CLOSEUP) {
        bool changed = settingsComboAccepted
            && SendMessageW(control, CB_GETCURSEL, 0, 0) != settingsComboInitialSelection;
        if (!settingsComboAccepted) {
            SetComboSelection(control, settingsComboInitialSelection);
        }
        hSettingsOpenCombo = nullptr;
        settingsComboInitialSelection = CB_ERR;
        settingsComboAccepted = false;
        *notification = CBN_SELCHANGE;
        return !changed;
    }
    return false;
}

/// Dispatches settings, information-window, panel-link, and controller commands to their existing actions.
/// Preserves native handling for commands that do not belong to these windows.
static LRESULT HandleWindowCommand(HWND window, Widget* widget, WPARAM wParam, LPARAM lParam) {
    int id = LOWORD(wParam);
    int notification = HIWORD(wParam);
    if (window == hSettings) {
        if (HandleSettingsComboNotification(reinterpret_cast<HWND>(lParam), &notification)) {
            return 0;
        }
        HandleSettingsCommand(id, notification);
        UpdateSettingsApplyButton();
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
            helpForm.Show(hInstance, helpWindowState);
        } else if (id == ID_MENU_ABOUT) {
            aboutForm.Show(hInstance, aboutWindowState);
        } else if (id == ID_MENU_EXIT) {
            RequestExitApplication();
        }
        return 0;
    }
    return DefWindowProcW(window, WM_COMMAND, wParam, lParam);
}

/// Dispatches controller, widget, settings-page, and information-window messages. Coordinates painting,
/// input, timers, background-worker results, settings actions, and orderly application shutdown.
static LRESULT CALLBACK WindowProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) {
    Widget* widget = reinterpret_cast<Widget*>(GetWindowLongPtrW(window, GWLP_USERDATA));
    if (msg == WM_NCCREATE) {
        CREATESTRUCTW* create = reinterpret_cast<CREATESTRUCTW*>(lParam);
        if (create->lpCreateParams != nullptr) {
            widget = static_cast<Widget*>(create->lpCreateParams);
            SetWindowLongPtrW(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(widget));
        }
    }
    if (widget != nullptr && widget->config.type == WIDGET_FULLSCREEN || window == hFullscreenCursorWindow) {
        if (HandleFullscreenCursorMessage(window, msg, wParam, lParam)) {
            return TRUE;
        }
    }
    if (msg == taskbarCreatedMessage && window == hController) {
        AddTrayIcon();
        return 0;
    }
    switch (msg) {
        case WM_NCPAINT:
            if (widget != nullptr && UsesConfigurableNativeFrame(widget)) {
                LRESULT result = DefWindowProcW(window, msg, wParam, lParam);
                PaintConfiguredNativeFrame(window, widget->config.borderColor);
                return result;
            }
            break;
        case DM_GETDEFID:
            if (window == hSettings) {
                int defaultId = ID_SAVE;
                if (hSettingsDefaultButton != nullptr) {
                    defaultId = GetDlgCtrlID(hSettingsDefaultButton);
                }
                return MAKELRESULT(defaultId, DC_HASDEFID);
            }
            break;
        case WM_TIMECHANGE:
        case WM_SETTINGCHANGE:
            if (msg == WM_SETTINGCHANGE && window == hSettings) {
                PostMessageW(window, WM_UPDATE_SETTINGS_CONTROL_METRICS, 0, 0);
            }
            if (window == hController) {
                for (const std::unique_ptr<Widget>& current : widgets) {
                    current->lastRenderKey = -1;
                    current->rendered = false;
                    UpdateCalendarDate(current.get());
                    if (current->config.visible) {
                        RenderWidget(current.get());
                    }
                }
                ScheduleWidgetRefresh();
                return 0;
            }
            break;
        case WM_DISPLAYCHANGE:
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
                if (result != nullptr) {
                    AppendNtpSynchronizationLog(result->logEntries);
                }
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
                    ntpClockOffset100Nanoseconds = result->clockOffset100Nanoseconds;
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
                    ScheduleWidgetRefresh();
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
        case WM_THEMECHANGED:
        case WM_SYSCOLORCHANGE:
            if (window == hSettings) {
                PostMessageW(window, WM_UPDATE_SETTINGS_CONTROL_METRICS, 0, 0);
                RedrawWindow(window, nullptr, nullptr,
                    RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN);
            }
            break;
        case WM_ALIGN_SETTINGS_FONT_BUTTON:
            if (window == hSettings && !settingsLayoutSuspended) {
                AlignApplicationFontButton();
                return 0;
            }
            break;
        case WM_UPDATE_SETTINGS_CONTROL_METRICS:
            if (window == hSettings) {
                WindowRedrawScope redraw(wParam != 0 ? nullptr : hAppearancePage);
                if (wParam != 0) {
                    RebuildSettingsControls(true);
                    if (hSettings == nullptr) {
                        return 0;
                    }
                }
                UpdateSettingsControlMetrics();
                UpdateSettingControlAvailability(false);
                return 0;
            }
            break;
        case WM_DRAWITEM:
            return DrawWidgetItem(window, widget, wParam, lParam);
        case WM_ERASEBKGND:
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
        case WM_PAINT:
            if (widget != nullptr) {
                if (widget->config.type == WIDGET_CALENDAR) {
                    PAINTSTRUCT paint = {};
                    HDC dc = BeginPaint(window, &paint);
                    RECT frameRect = {};
                    GetClientRect(window, &frameRect);
                    FillRect(dc, &frameRect, GetSysColorBrush(COLOR_WINDOW));
                    EndPaint(window, &paint);
                    return 0;
                }
                if (widget->config.type == WIDGET_DIGITAL && !widget->config.transparentBackground
                        || widget->config.type == WIDGET_FULLSCREEN) {
                    PAINTSTRUCT paint = {};
                    HDC dc = BeginPaint(window, &paint);
                    PaintWidgetBuffered(widget, window, dc, false);
                    EndPaint(window, &paint);
                    return 0;
                }
                if (widget->config.type == WIDGET_PANEL) {
                    PAINTSTRUCT paint = {};
                    HDC dc = BeginPaint(window, &paint);
                    PaintWidgetBuffered(widget, window, dc, true);
                    EndPaint(window, &paint);
                    return 0;
                }
            }
            break;
        case WM_HSCROLL:
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
            if (window == hSettings
                    && (ScrollSettingsTabHeaders(wParam, lParam) || ScrollSettingsWheel(wParam))) {
                return 0;
            }
            break;
        case WM_COMMAND:
            return HandleWindowCommand(window, widget, wParam, lParam);
        case WM_NOTIFY:
            if (widget != nullptr) {
                if (widget->panelDateTooltip != nullptr
                        && reinterpret_cast<NMHDR*>(lParam)->hwndFrom == widget->panelDateTooltip
                        && reinterpret_cast<NMHDR*>(lParam)->code == TTN_GETDISPINFOW) {
                    NMTTDISPINFOW* information = reinterpret_cast<NMTTDISPINFOW*>(lParam);
                    information->lpszText = const_cast<wchar_t*>(GetLocalizedText(widget->config.language,
                        TXT_PANEL_TODAY_TOOLTIP));
                    return 0;
                }
                if (widget->calendarChild != nullptr
                        && reinterpret_cast<NMHDR*>(lParam)->hwndFrom == widget->calendarChild
                        && reinterpret_cast<NMHDR*>(lParam)->code == MCN_SELECT) {
                    NMSELCHANGE* selection = reinterpret_cast<NMSELCHANGE*>(lParam);
                    CopyWidgetDate(widget, selection->stSelStart);
                    return 0;
                }
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
                        SetWindowPos(widgets[index]->window, HWND_TOPMOST,
                            0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
                        for (size_t wndIndex = 0;
                                wndIndex < widgets[index]->fullscreenWindows.size();
                                wndIndex++) {
                            SetWindowPos(widgets[index]->fullscreenWindows[wndIndex], HWND_TOPMOST,
                                0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
                        }
                        if (!widgets[index]->config.topMost
                                && widgets[index]->config.type != WIDGET_FULLSCREEN) {
                            SetWindowPos(widgets[index]->window, HWND_NOTOPMOST,
                                0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
                        }
                    }
                }
                if (!anyVisible) {
                    RestoreLastHiddenWidgets();
                } else {
                    RefreshFullscreenPresentation();
                }
                if (hSettings != nullptr) {
                    settingsWindowState.BringToFront();
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
                    }
                }
                for (size_t index = 0; index < widgets.size(); index++) {
                    Widget* current = widgets[index].get();
                    CheckWidgetAlarm(current);
                    if (!current->config.visible) {
                        continue;
                    }
                    SYSTEMTIME displayed = {};
                    GetDisplayedTime(current->config, &displayed);
                    bool renderSeconds = current->config.showSeconds;
                    if (current->config.type == WIDGET_ANALOG
                            && !AnalogClockSupportsSeconds(current->config.size)) {
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
                ScheduleWidgetRefresh();
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
                if (widget->alarmStoppedTick != 0
                        && tick - widget->alarmStoppedTick <= GetDoubleClickTime()) {
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
                if (snapWidgetsToWorkArea
                        && GetWindowRect(window, &rect)
                        && GetMonitorInfoW(monitor, &monitorInfo)) {
                    position = SnapWidgetPositionToWorkArea(rect, monitorInfo.rcWork, position,
                        WORK_AREA_SNAP_DISTANCE);
                }
                SetWindowPos(window, nullptr, position.x, position.y, 0, 0,
                    SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
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
            if (widget != nullptr) {
                if (wParam == VK_ESCAPE) {
                    if (widget->alarmActive || widget->audioStopEvent != nullptr) {
                        StopWidgetAlarm(widget);
                    } else {
                        SetWidgetVisible(widget, false);
                    }
                } else if (wParam == VK_F1) {
                    helpForm.Show(hInstance, helpWindowState);
                } else if (wParam == L'B') {
                    ShowSettingsWindow();
                }
                return 0;
            }
            break;
        case WM_CLOSE:
            if (window == hController) {
                RequestExitApplication();
                return 0;
            }
            if (window == hSettings) {
                RequestCloseSettingsWindow();
                return 0;
            }
            if (widget != nullptr) {
                SetWidgetVisible(widget, false);
                return 0;
            }
            break;
        case WM_DESTROY:
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
    return DefWindowProcW(window, msg, wParam, lParam);
}

/// Enforces one application instance, initializes services and windows, and runs the message loop with
/// custom keyboard navigation. Releases rendering, synchronization, and process resources before returning
/// the message-loop exit code.
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
        ICC_WIN95_CLASSES | ICC_TAB_CLASSES | ICC_DATE_CLASSES | ICC_LINK_CLASS | ICC_USEREX_CLASSES
    };
    InitCommonControlsEx(&controls);
    WSADATA winsockData = {};
    winsockReady = WSAStartup(MAKEWORD(2, 2), &winsockData) == 0;
    InitializeLanguageLocales();
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
    ScheduleWidgetRefresh();
    SaveAllSettings();
    StartNtpSynchronization(true);
    MSG msg = {};
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        if (msg.message == WM_MOUSEWHEEL && ScrollSettingsTabHeaders(msg.wParam, msg.lParam)) {
            continue;
        }
        if (helpForm.GetWindow() != nullptr && IsDialogMessageW(helpForm.GetWindow(), &msg)) {
            continue;
        }
        if (aboutForm.GetWindow() != nullptr && IsDialogMessageW(aboutForm.GetWindow(), &msg)) {
            continue;
        }
        Widget* inputWidget = WidgetFromInputWindow(msg.hwnd);
        if ((msg.message == WM_KEYDOWN || msg.message == WM_SYSKEYDOWN)
                && msg.wParam == VK_ESCAPE
                && inputWidget != nullptr
                && (inputWidget->alarmActive || inputWidget->audioStopEvent != nullptr)) {
            StopWidgetAlarm(inputWidget);
            continue;
        }
        if ((msg.message == WM_KEYDOWN || msg.message == WM_SYSKEYDOWN)
                && msg.wParam == VK_ESCAPE
                && HideFullscreenWidgetsFromEscape()) {
            continue;
        }
        if (msg.message == WM_KEYDOWN
                && msg.wParam == L'M'
                && (msg.lParam & 1LL << 30) == 0
                && inputWidget != nullptr) {
            ToggleAllWidgetSounds();
            continue;
        }
        if (HandleWidgetSizeShortcut(inputWidget, msg)) {
            continue;
        }
        if (inputWidget != nullptr
                && inputWidget->config.type == WIDGET_PANEL
                && IsDialogMessageW(inputWidget->window, &msg)) {
            continue;
        }
        if (msg.message == WM_KEYDOWN
                && msg.wParam == VK_TAB
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
        if (hSettings != nullptr && IsDialogMessageW(hSettings, &msg)) {
            continue;
        }
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    ShutdownAnalogClockHost();
    if (hUiFont != nullptr) {
        DeleteObject(hUiFont);
    }
    aboutForm.Close();
    helpForm.Close();
    ShutdownDirectTextRendering();
    if (hSingleInstanceMutex != nullptr) {
        CloseHandle(hSingleInstanceMutex);
        hSingleInstanceMutex = nullptr;
    }
    bool ntpThreadFinished = StopNtpSynchronization();
    if (winsockReady && ntpThreadFinished) {
        WSACleanup();
    }
    return static_cast<int>(msg.wParam);
}
