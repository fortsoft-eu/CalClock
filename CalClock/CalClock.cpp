#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "resource.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include "AlarmActions.h"
#include "AnalogClockHost.h"
#include "CalendarLocaleScope.h"
#include "CalClockTypes.h"
#include "DateFormats.h"
#include "Localization.h"
#include "NtpClient.h"
#include "SettingsStorage.h"
#include "TimeSignal.h"
#include "TimeZoneSupport.h"
#include "WidgetLayout.h"
#include <windowsx.h>
#include <algorithm>
#include <atomic>
#include <climits>
#include <cmath>
#include <commctrl.h>
#include <commdlg.h>
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

HINSTANCE hInstance = nullptr;
HANDLE hSingleInstanceMutex = nullptr;
HWND hController = nullptr;
HWND hSettings = nullptr;
HWND hSettingsLastFocus = nullptr;
HWND hHelp = nullptr;
HWND hAbout = nullptr;
NOTIFYICONDATAW trayIcon = {};
bool trayUsesVersion4 = false;
HFONT hUiFont = nullptr;
HFONT hAboutFont = nullptr;
UINT taskbarCreatedMessage = 0;
typedef LCID(WINAPI* GetUserDefaultLcidProc)();
typedef int(WINAPI* GetLocaleInfoWProc)(LCID locale, LCTYPE type, LPWSTR data, int characters);
typedef int(WINAPI* GetCalendarInfoWProc)(LCID locale, CALID calendar, CALTYPE type, LPWSTR data, int characters, LPDWORD value);
typedef int(WINAPI* GetCalendarInfoExProc)(LPCWSTR localeName, CALID calendar, LPCWSTR reserved, CALTYPE type, LPWSTR data, int characters, LPDWORD value);
typedef int(WINAPI* GetCalendarDateFormatProc)(CALID calendar, DWORD flags, const void* calendarDate, LPCWSTR format, LPWSTR data, int characters);
typedef BOOL(WINAPI* ConvertCalDateTimeToSystemTimeProc)(const void* calendarDate, SYSTEMTIME* systemTime);
typedef HRESULT(WINAPI* D2D1CreateFactoryProc)(D2D1_FACTORY_TYPE factoryType, REFIID interfaceId, const D2D1_FACTORY_OPTIONS* factoryOptions, void** factory);
typedef HRESULT(WINAPI* DWriteCreateFactoryProc)(DWRITE_FACTORY_TYPE factoryType, REFIID interfaceId, IUnknown** factory);
GetUserDefaultLcidProc originalGetUserDefaultLcid = nullptr;
GetLocaleInfoWProc originalGetLocaleInfoW = nullptr;
GetCalendarInfoWProc originalGetCalendarInfoW = nullptr;
GetCalendarInfoExProc originalGetCalendarInfoEx = nullptr;
GetCalendarDateFormatProc originalGetCalendarDateFormat = nullptr;
ConvertCalDateTimeToSystemTimeProc convertCalDateTimeToSystemTime = nullptr;
AppLanguage appLanguage = LANG_EN;
bool themesDisabled = false;
int appFontAntialiasing = FONT_ANTIALIAS_CLEARTYPE;
std::wstring appFontFace;
int appFontDialogSize = 90;
int appFontWeight = FW_NORMAL;
bool appFontItalic = false;
std::wstring settingsAppFontFace;
int settingsAppFontDialogSize = 90;
int settingsAppFontWeight = FW_NORMAL;
bool settingsAppFontItalic = false;
ID2D1Factory* d2dFactory = nullptr;
IDWriteFactory* dwriteFactory = nullptr;
HMODULE d2dModule = nullptr;
HMODULE dwriteModule = nullptr;
bool storageUsesXml = false;
bool useNtpTime = true;
bool winsockReady = false;
int ntpPreset = NTP_PRESET_AUTO;
std::wstring ntpServers;
std::wstring ntpActiveServer;
bool ntpLastQueryFailed = false;
std::atomic<LONGLONG> ntpOffset100Nanoseconds = 0;
std::atomic<bool> ntpTimeValid = false;
std::atomic<bool> ntpQueryRunning = false;
std::atomic<bool> ntpStopRequested = false;
std::atomic<ULONG> ntpGeneration = 0;
ULONGLONG lastNtpAttemptTick = 0;
ULONGLONG lastTimeSignalTarget = 0;
bool currentTimeSignalIncludesRegular = false;
std::vector<int> currentTimeSignalAlarmWidgetIds;
HANDLE hNtpThread = nullptr;
int settingsX = CW_USEDEFAULT;
int settingsY = CW_USEDEFAULT;
int settingsTab = 0;
WidgetType lastAddedWidgetType = WIDGET_ANALOG;
int helpX = CW_USEDEFAULT;
int helpY = CW_USEDEFAULT;
int aboutX = CW_USEDEFAULT;
int aboutY = CW_USEDEFAULT;
int nextWidgetId = 1;
int selectedDraftIndex = 0;
std::vector<std::unique_ptr<Widget>> widgets;
std::vector<int> lastHiddenWidgetIds;
std::vector<DisplayMonitor> displayMonitors;
std::vector<HWND> blackoutWindows;
std::vector<WidgetConfig> settingsDraft;
std::vector<WidgetConfig> settingsAppearanceOriginals;
std::vector<int> settingsAppearancePreviewIds;
bool settingsAppearancePreviewActive = false;
bool settingsApplicationFontPreviewActive = false;
std::vector<DYNAMIC_TIME_ZONE_INFORMATION> timeZones;

const wchar_t CLASS_NAME[] = L"CalClockMultiWidgetWindow";
const wchar_t BLACKOUT_CLASS_NAME[] = L"CalClockBlackoutWindow";
const wchar_t CONTROLLER_TITLE[] = L"CalClockMessageController";
const UINT WM_TRAYICON = WM_APP + 1;
const UINT WM_SHOW_EXISTING = WM_APP + 2;
const UINT WM_NTP_RESULT = WM_APP + 3;
const UINT WM_AUDIO_FINISHED = WM_APP + 4;
const UINT WM_SETTINGS_AUDIO_FINISHED = WM_APP + 5;
const UINT WM_REFRESH_DISPLAYS = WM_APP + 6;
const UINT WM_RESTORE_SETTINGS_FOCUS = WM_APP + 7;
const UINT WM_TIME_SIGNAL_FINISHED = WM_APP + 8;
const UINT_PTR TIMER_REFRESH = 1;
static const UINT_PTR TIMER_EDIT_CLICKS = 0xCC01;
static const int PANEL_SIDE_PADDING = 12;
static const int PANEL_CALENDAR_OFFSET_Y = -4;
const COLORREF IDENTIFY_COLOR = RGB(80, 190, 255);

const int ID_MENU_SETTINGS = 1001;
const int ID_MENU_VISIBLE = 1002;
const int ID_MENU_TOPMOST = 1003;
const int ID_MENU_SECONDS = 1004;
const int ID_MENU_STOP_ALARM = 1005;
const int ID_MENU_SIZE_104 = 1010;
const int ID_MENU_SIZE_198 = 1013;
const int ID_MENU_ARRANGE_WIDGETS = 1050;
const int ID_MENU_DATE_FORMAT_BASE = 1060;
const int ID_MENU_SHOW_ALL = 1020;
const int ID_MENU_HIDE_ALL = 1021;
const int ID_MENU_HELP = 1022;
const int ID_MENU_ABOUT = 1023;
const int ID_MENU_EXIT = 1024;
const int ID_MENU_WIDGET_BASE = 2000;

static_assert(ID_MENU_ARRANGE_WIDGETS < ID_MENU_DATE_FORMAT_BASE
    || ID_MENU_ARRANGE_WIDGETS >= ID_MENU_DATE_FORMAT_BASE + DATE_FORMAT_COUNT);

const int ID_LIST_WIDGETS = 3001;
const int ID_ADD_TYPE = 3002;
const int ID_ADD = 3003;
const int ID_REMOVE = 3004;
const int ID_DUPLICATE = 3005;
const int ID_TABS = 3006;
const int ID_NAME = 3010;
const int ID_TYPE = 3011;
const int ID_VISIBLE = 3012;
const int ID_TOPMOST = 3013;
const int ID_SECONDS = 3014;
const int ID_UTC = 3015;
const int ID_TIMEZONE = 3016;
const int ID_OFFSET = 3017;
const int ID_WIDGET_LANGUAGE = 3018;
const int ID_UTC_TEXT = 3019;
const int ID_BLACKOUT_MONITORS = 3070;
const int ID_MONITOR_LIST = 3071;
const int ID_SIZE = 3020;
const int ID_OPACITY = 3021;
const int ID_FONT_SIZE = 3022;
const int ID_LEADING_ZERO = 3023;
const int ID_TRANSPARENT_BG = 3024;
const int ID_TEXT_COLOR = 3025;
const int ID_BACKGROUND_COLOR = 3026;
const int ID_WEEK_NUMBERS = 3027;
const int ID_SUNDAY_FIRST = 3028;
const int ID_DATE_FORMAT = 3029;
const int ID_FONT = 3052;
const int ID_ALARM_TEXT_COLOR = 3053;
const int ID_ALARM_BACKGROUND_COLOR = 3054;
const int ID_PADDING = 3055;
const int ID_BORDER = 3056;
const int ID_WIDGET_DISABLE_THEMES = 3057;
const int ID_DEFAULT_APPEARANCE = 3058;
const int ID_BORDER_WIDTH = 3059;
const int ID_WIDGET_ANTIALIAS = 3072;
const int ID_PANEL_TOP_FONT = 3073;
const int ID_PANEL_TIME_FONT = 3074;
const int ID_PANEL_BOTTOM_FONT = 3075;
const int ID_SHOW_FRAME = 3077;
const int ID_TIME_SIGNAL = 3078;
const int ID_ALARM_TIME_SIGNAL = 3079;
const int ID_TIME_SIGNAL_NOTE = 3080;
const int ID_ALARM_ENABLED = 3030;
const int ID_ALARM_TIME = 3031;
const int ID_RUN_COMMAND = 3032;
const int ID_COMMAND = 3033;
const int ID_BROWSE = 3034;
const int ID_LOOP_AUDIO = 3035;
const int ID_TEST_COMMAND = 3036;
const int ID_REMOTE_SCRIPT = 3037;
const int ID_REMOTE_SCRIPT_URL = 3038;
const int ID_LANGUAGE = 3040;
const int ID_VISUAL_STYLES = 3041;
const int ID_SAVE = IDOK;
const int ID_APPLY = 3043;
const int ID_CANCEL = IDCANCEL;
const int ID_IMPORT_SETTINGS = 3045;
const int ID_EXPORT_SETTINGS = 3046;
const int ID_USE_XML_SETTINGS = 3047;
const int ID_APP_ANTIALIAS = 3048;
const int ID_APP_FONT = 3049;
const int ID_APP_FONT_DEFAULT = 3076;
const int ID_TIME_SOURCE = 3060;
const int ID_NTP_SERVERS = 3061;
const int ID_NTP_SYNC = 3062;
const int ID_NTP_PRESET = 3063;
const int ID_INFO_CLOSE = 3050;
const int ID_INFO_TEXT = 3051;
const int SETTINGS_HORIZONTAL_SCALE_NUMERATOR = 6;
const int SETTINGS_HORIZONTAL_SCALE_DENOMINATOR = 5;
const int SETTINGS_UNBOUNDED_LABEL_WIDTH = 4096;
const int SETTINGS_WINDOW_WIDTH = 778;
const int SETTINGS_WINDOW_HEIGHT = 491;

HWND hWidgetList = nullptr;
HWND hAddType = nullptr;
HWND hTabs = nullptr;
HWND hGeneralPage = nullptr;
HWND hAppearancePage = nullptr;
HWND hAlarmPage = nullptr;
HWND hTimeSignalPage = nullptr;
HWND hTimePage = nullptr;
int settingsContentWidth = 0;
int settingsContentHeight = 0;
HWND hNameEdit = nullptr;
HWND hTypeCombo = nullptr;
HWND hVisibleCheck = nullptr;
HWND hTopmostCheck = nullptr;
HWND hSecondsCheck = nullptr;
HWND hUtcCheck = nullptr;
HWND hUtcTextCheck = nullptr;
HWND hTimeZoneLabel = nullptr;
HWND hTimeZoneCombo = nullptr;
HWND hMonitorLabel = nullptr;
HWND hMonitorList = nullptr;
HWND hBlackoutMonitorsCheck = nullptr;
HWND hOffsetEdit = nullptr;
HWND hWidgetLanguageCombo = nullptr;
HWND hSizeCombo = nullptr;
HWND hOpacityTrackBar = nullptr;
HWND hOpacityValue = nullptr;
HWND hFontSizeTrackBar = nullptr;
HWND hFontSizeValue = nullptr;
HWND hWidgetAntialiasLabel = nullptr;
HWND hWidgetAntialiasCombo = nullptr;
HWND hLeadingZeroCheck = nullptr;
HWND hTransparentBackgroundCheck = nullptr;
HWND hTextColorButton = nullptr;
HWND hBackgroundColorButton = nullptr;
HWND hWeekNumbersCheck = nullptr;
HWND hSundayFirstCheck = nullptr;
HWND hShowFrameCheck = nullptr;
HWND hDateFormatLabel = nullptr;
HWND hDateFormatCombo = nullptr;
HWND hAlarmEnabledCheck = nullptr;
HWND hAlarmTimeEdit = nullptr;
HWND hAlarmTimeSignalCheck = nullptr;
HWND hRunCommandCheck = nullptr;
HWND hCommandEdit = nullptr;
HWND hBrowseButton = nullptr;
HWND hLoopAudioCheck = nullptr;
HWND hRemoteScriptCheck = nullptr;
HWND hRemoteScriptLabel = nullptr;
HWND hRemoteScriptEdit = nullptr;
HWND hTimeSignalCombo = nullptr;
HWND hLanguageCombo = nullptr;
HWND hDisableThemesCheck = nullptr;
HWND hUseXmlSettingsCheck = nullptr;
HWND hAppAntialiasCombo = nullptr;
HWND hAppFontLabel = nullptr;
HWND hAppFontButton = nullptr;
HWND hAppFontDefaultButton = nullptr;
HWND hTimeSourceCombo = nullptr;
HWND hNtpPresetLabel = nullptr;
HWND hNtpPresetCombo = nullptr;
HWND hNtpServersLabel = nullptr;
HWND hNtpServersEdit = nullptr;
HWND hNtpStatus = nullptr;
HWND hNtpSyncButton = nullptr;
HWND hSizeLabel = nullptr;
HWND hOpacityLabel = nullptr;
HWND hFontSizeLabel = nullptr;
HWND hFontButton = nullptr;
HWND hPanelTopFontButton = nullptr;
HWND hPanelTimeFontButton = nullptr;
HWND hPanelBottomFontButton = nullptr;
HWND hFontDescription = nullptr;
HWND hAlarmTextColorButton = nullptr;
HWND hAlarmBackgroundColorButton = nullptr;
HWND hPaddingLabel = nullptr;
HWND hPaddingTrackBar = nullptr;
HWND hPaddingValue = nullptr;
HWND hBorderLabel = nullptr;
HWND hBorderTrackBar = nullptr;
HWND hBorderWidthLabel = nullptr;
HWND hBorderWidthTrackBar = nullptr;
HWND hBorderWidthValue = nullptr;
bool updatingNtpPresetControls = false;
bool displayRefreshPending = false;
HWND hWidgetDisableThemesCheck = nullptr;
HWND hDefaultAppearanceButton = nullptr;
HWND hTestCommandButton = nullptr;
HANDLE settingsPreviewStopEvent = nullptr;
ULONG settingsPreviewGeneration = 0;
int settingsVisualPreviewWidgetId = -1;
bool settingsVisualPreviewActive = false;
bool settingsTimeSignalPreviewActive = false;
static HWND lastClickedEdit = nullptr;
static POINT lastEditClickPoint = {};
static int editClickCount = 0;
std::vector<HWND> generalControls;
std::vector<HWND> appearanceControls;
std::vector<HWND> alarmControls;
std::vector<HWND> timeSignalControls;
std::vector<HWND> timeControls;
std::vector<HWND> settingsUnderlayLabels;

static LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK AnalogChildProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK CalendarChildProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK EditSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR subclassId, DWORD_PTR referenceData);
static LRESULT CALLBACK WidgetListSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR subclassId, DWORD_PTR referenceData);
static void RenderWidget(Widget* widget);
static void SaveAllSettings();
static void ShowSettingsWindow(int widgetId = -1);
static void SynchronizeOpenSettings(const Widget* widget);
static void RefreshInformationWindows();
static std::wstring GetSystemMessageFontFace();
static HFONT CreateWidgetDrawingFont(const WidgetConfig& config);
static void StopSettingsPreview();
static void UpdateFontDescription(const WidgetConfig& config);
static void ApplyUiStyle(HWND window);
static void UpdateSettingControlAvailability();
static void PreviewSelectedWidgetAppearance(bool structuralChange);
static void RestoreSettingsAppearancePreview();
static void RefreshFullscreenPresentation();
static Widget* FindWidgetById(int id);
static HFONT CreateCalendarUiFont(const WidgetConfig& config);
static std::wstring GetControlText(HWND control);

static const wchar_t* T(TextId id) {
    return TEXT[appLanguage][id];
}

static const wchar_t* TypeName(WidgetType type) {
    static const wchar_t* fullscreenNames[LANG_COUNT] = {
        L"Hodiny na monitoru",
        L"Monitor clock",
        L"Monitoruhr",
        L"Horloge sur moniteur",
        L"Reloj de monitor",
        L"Orologio su monitor",
        L"Zegar na monitorze",
        L"Hodiny na monitore"
    };
    if (type == WIDGET_FULLSCREEN) {
        return fullscreenNames[appLanguage];
    }
    return T(static_cast<TextId>(TXT_ANALOG + static_cast<int>(type)));
}

static const wchar_t* WT(const Widget* widget, TextId id) {
    AppLanguage language = widget == nullptr ? appLanguage : widget->config.language;
    return TEXT[language][id];
}

static wchar_t MnemonicKey(wchar_t character) {
    CharUpperBuffW(&character, 1);
    return character;
}

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
        if (std::iswalnum(plainText[preferredPosition]) && std::find(usedMnemonics->begin(), usedMnemonics->end(), key) == usedMnemonics->end()) {
            mnemonicPosition = preferredPosition;
        }
    }
    if (mnemonicPosition == std::wstring::npos) {
        for (size_t index = 0; index < plainText.size(); index++) {
            wchar_t key = MnemonicKey(plainText[index]);
            if (std::iswalnum(plainText[index]) && std::find(usedMnemonics->begin(), usedMnemonics->end(), key) == usedMnemonics->end()) {
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

static void AppendMenuCommand(HMENU menu, UINT flags, UINT_PTR command, const wchar_t* text, std::vector<wchar_t>* usedMnemonics, bool opensWindow = false) {
    std::wstring caption = text;
    if (opensWindow) {
        caption += L"...";
    }
    std::wstring label = UniqueMnemonic(caption.c_str(), usedMnemonics);
    AppendMenuW(menu, flags, command, label.c_str());
}

static void AppendApplicationMenuCommands(HMENU menu, AppLanguage language, std::vector<wchar_t>* usedMnemonics) {
    AppendMenuCommand(menu, MF_STRING, ID_MENU_SETTINGS, TEXT[language][TXT_SETTINGS], usedMnemonics, true);
    AppendMenuCommand(menu, MF_STRING, ID_MENU_HELP, TEXT[language][TXT_HELP], usedMnemonics, true);
    AppendMenuCommand(menu, MF_STRING, ID_MENU_ABOUT, TEXT[language][TXT_ABOUT], usedMnemonics, true);
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendMenuCommand(menu, MF_STRING, ID_MENU_EXIT, TEXT[language][TXT_EXIT], usedMnemonics);
}

static LCID WINAPI CalendarGetUserDefaultLCID() {
    if (activeCalendarLocale != 0) {
        return activeCalendarLocale;
    }
    return originalGetUserDefaultLcid == nullptr ? LOCALE_USER_DEFAULT : originalGetUserDefaultLcid();
}

static int WINAPI CalendarGetLocaleInfoW(LCID locale, LCTYPE type, LPWSTR data, int characters) {
    LCID selectedLocale = activeCalendarLocale == 0 ? locale : activeCalendarLocale;
    return originalGetLocaleInfoW == nullptr ? 0 : originalGetLocaleInfoW(selectedLocale, type, data, characters);
}

static int WINAPI CalendarGetCalendarInfoW(LCID locale, CALID calendar, CALTYPE type, LPWSTR data, int characters, LPDWORD value) {
    LCID selectedLocale = activeCalendarLocale == 0 ? locale : activeCalendarLocale;
    return originalGetCalendarInfoW == nullptr ? 0 : originalGetCalendarInfoW(selectedLocale, calendar, type, data, characters, value);
}

static int WINAPI CalendarGetCalendarInfoEx(LPCWSTR localeName, CALID calendar, LPCWSTR reserved, CALTYPE type, LPWSTR data, int characters, LPDWORD value) {
    wchar_t selectedName[LOCALE_NAME_MAX_LENGTH] = {};
    LPCWSTR selectedLocaleName = localeName;
    if (activeCalendarLocale != 0 && LCIDToLocaleName(activeCalendarLocale, selectedName, ARRAYSIZE(selectedName), 0) != 0) {
        selectedLocaleName = selectedName;
    }
    return originalGetCalendarInfoEx == nullptr ? 0 : originalGetCalendarInfoEx(selectedLocaleName, calendar, reserved, type, data, characters, value);
}

static int WINAPI CalendarGetCalendarDateFormat(CALID calendar, DWORD flags, const void* calendarDate, LPCWSTR format, LPWSTR data, int characters) {
    if (activeCalendarLocale != 0 && calendarDate != nullptr && data != nullptr && characters > 0) {
        if (convertCalDateTimeToSystemTime == nullptr) {
            HMODULE kernel = GetModuleHandleW(L"kernel32.dll");
            if (kernel != nullptr) {
                convertCalDateTimeToSystemTime = reinterpret_cast<ConvertCalDateTimeToSystemTimeProc>(GetProcAddress(kernel, "ConvertCalDateTimeToSystemTime"));
            }
        }
        SYSTEMTIME systemTime = {};
        wchar_t localeName[LOCALE_NAME_MAX_LENGTH] = {};
        if (convertCalDateTimeToSystemTime != nullptr && convertCalDateTimeToSystemTime(calendarDate, &systemTime) &&
            LCIDToLocaleName(activeCalendarLocale, localeName, ARRAYSIZE(localeName), 0) != 0) {
            int result = GetDateFormatEx(localeName, flags, &systemTime, format, data, characters, nullptr);
            if (result != 0) {
                return result;
            }
        }
    }
    return originalGetCalendarDateFormat == nullptr ? 0 : originalGetCalendarDateFormat(calendar, flags, calendarDate, format, data, characters);
}

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

static bool InstallCalendarLocaleHook() {
    if (originalGetUserDefaultLcid != nullptr) {
        return true;
    }
    ULONG_PTR original = 0;
    bool defaultHook = PatchCommonControlsImport("GetUserDefaultLCID", reinterpret_cast<ULONG_PTR>(&CalendarGetUserDefaultLCID), &original);
    originalGetUserDefaultLcid = reinterpret_cast<GetUserDefaultLcidProc>(original);
    original = 0;
    bool localeHook = PatchCommonControlsImport("GetLocaleInfoW", reinterpret_cast<ULONG_PTR>(&CalendarGetLocaleInfoW), &original);
    originalGetLocaleInfoW = reinterpret_cast<GetLocaleInfoWProc>(original);
    original = 0;
    bool calendarHook = PatchCommonControlsImport("GetCalendarInfoW", reinterpret_cast<ULONG_PTR>(&CalendarGetCalendarInfoW), &original);
    originalGetCalendarInfoW = reinterpret_cast<GetCalendarInfoWProc>(original);
    original = 0;
    PatchCommonControlsImport("GetCalendarInfoEx", reinterpret_cast<ULONG_PTR>(&CalendarGetCalendarInfoEx), &original);
    originalGetCalendarInfoEx = reinterpret_cast<GetCalendarInfoExProc>(original);
    original = 0;
    bool dateHook = PatchCommonControlsImport("GetCalendarDateFormat", reinterpret_cast<ULONG_PTR>(&CalendarGetCalendarDateFormat), &original);
    originalGetCalendarDateFormat = reinterpret_cast<GetCalendarDateFormatProc>(original);
    return defaultHook && localeHook && calendarHook && dateHook;
}

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

static void RefreshDisplayMonitors() {
    displayMonitors.clear();
    EnumDisplayMonitors(nullptr, nullptr, CollectDisplayMonitor, reinterpret_cast<LPARAM>(&displayMonitors));
    std::stable_sort(displayMonitors.begin(), displayMonitors.end(), [](const DisplayMonitor& left, const DisplayMonitor& right) {
        if (left.primary != right.primary) {
            return left.primary;
        }
        if (left.rect.top != right.rect.top) {
            return left.rect.top < right.rect.top;
        }
        return left.rect.left < right.rect.left;
    });
}

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

static bool GetPrimarySelectedMonitorRect(const WidgetConfig& config, RECT* rect) {
    std::vector<const DisplayMonitor*> selected = SelectedDisplayMonitors(config);
    if (selected.empty() || rect == nullptr) {
        return false;
    }
    *rect = selected[0]->rect;
    return true;
}

static int GetAnalogClockSizes(int* sizes) {
    int count = GetSupportedAnalogClockSizes(sizes, 4);
    if (count > 0) {
        return count;
    }
    const int fallbackSizes[] = { 104, 130, 166, 198 };
    CopyMemory(sizes, fallbackSizes, sizeof(fallbackSizes));
    return ARRAYSIZE(fallbackSizes);
}

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

static int GetSelectedAnalogClockSize(int fallback) {
    if (hSizeCombo == nullptr) {
        return fallback;
    }
    int sizes[4] = {};
    int count = GetAnalogClockSizes(sizes);
    int selected = static_cast<int>(SendMessageW(hSizeCombo, CB_GETCURSEL, 0, 0));
    return selected >= 0 && selected < count ? sizes[selected] : fallback;
}

static void SetDefaultWidgetAppearance(WidgetConfig* config, WidgetType type) {
    if (config == nullptr) {
        return;
    }
    config->size = 130;
    config->opacity = 100;
    config->fontSize = 44;
    config->fontDialogSize = type == WIDGET_DIGITAL ? config->fontSize * 10 : 90;
    int selectedAppFontAntialiasing = hAppAntialiasCombo == nullptr ? appFontAntialiasing : static_cast<int>(SendMessageW(hAppAntialiasCombo, CB_GETCURSEL, 0, 0));
    config->fontAntialiasing = std::clamp(selectedAppFontAntialiasing, 0, FONT_ANTIALIAS_COUNT - 1);
    config->leadingZero = false;
    config->transparentBackground = false;
    config->disableThemes = false;
    config->fontFace = type == WIDGET_DIGITAL ? L"Arial" : type == WIDGET_FULLSCREEN ? L"Arial Narrow" : GetSystemMessageFontFace();
    config->fontWeight = FW_NORMAL;
    config->fontItalic = false;
    config->fontUnderline = false;
    config->fontStrikeOut = false;
    config->fontCharSet = DEFAULT_CHARSET;
    config->padding = 8;
    config->borderStyle = DIGITAL_BORDER_SINGLE;
    config->borderWidth = type == WIDGET_DIGITAL ? 0 : 1;
    config->showFrame = true;
    config->textColor = type == WIDGET_FULLSCREEN ? RGB(255, 255, 255) : RGB(16, 16, 16);
    config->backgroundColor = type == WIDGET_FULLSCREEN ? RGB(0, 0, 0) : RGB(255, 255, 255);
    config->alarmTextColor = RGB(220, 0, 0);
    config->alarmBackgroundColor = RGB(255, 255, 128);
    config->weekNumbers = false;
    config->sundayFirst = false;
    config->dateCopyFormat = DATE_LOCAL_SHORT;
    FontSelection panelFont;
    panelFont.face = GetSystemMessageFontFace();
    config->panelTopFont = panelFont;
    config->panelTimeFont = panelFont;
    config->panelBottomFont = panelFont;
}

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
    config.alarmTimeSignal = false;
    config.alarmHour = 6;
    config.alarmMinute = 0;
    config.runCommand = false;
    config.loopAudio = false;
    config.callRemoteScript = false;
    config.timeSignal = TIME_SIGNAL_NONE;
    return config;
}

static void SelectSystemLanguage() {
    switch (PRIMARYLANGID(GetUserDefaultUILanguage())) {
        case LANG_CZECH:
            appLanguage = LANG_CZ;
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
        default:
            appLanguage = LANG_EN;
            break;
    }
}

static SettingsSnapshot CaptureSettingsSnapshot() {
    SettingsSnapshot snapshot = {};
    snapshot.language = appLanguage;
    snapshot.themesDisabled = themesDisabled;
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
    for (size_t index = 0; index < widgets.size(); index++) {
        snapshot.widgets.push_back(widgets[index]->config);
    }
    return snapshot;
}

static void ApplySettingsSnapshot(const SettingsSnapshot& snapshot) {
    appLanguage = snapshot.language;
    themesDisabled = snapshot.themesDisabled;
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
    settingsX = snapshot.settingsX;
    settingsY = snapshot.settingsY;
    settingsTab = std::clamp(snapshot.settingsTab, 0, 4);
    lastAddedWidgetType = static_cast<WidgetType>(std::clamp(static_cast<int>(snapshot.lastAddedWidgetType), 0, WIDGET_TYPE_COUNT - 1));
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

static void LoadTimeZones() {
    LoadTimeZoneList(&timeZones);
}

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

static void LoadAllSettings() {
    SelectSystemLanguage();
    ntpPreset = NTP_PRESET_AUTO;
    ntpServers = NtpServersForPreset(ntpPreset);
    LoadTimeZones();
    SettingsSnapshot defaults = CaptureSettingsSnapshot();
    std::wstring xmlPath = AutomaticXmlSettingsPath(false);
    storageUsesXml = !xmlPath.empty() && GetFileAttributesW(xmlPath.c_str()) != INVALID_FILE_ATTRIBUTES;
    SettingsSnapshot snapshot = {};
    if (storageUsesXml && ReadSettingsXml(xmlPath, appLanguage, CreateStoredWidgetDefaults, &snapshot)) {
        ApplySettingsSnapshot(snapshot);
        return;
    }
    if (ReadRegistrySettings(defaults, CreateStoredWidgetDefaults, &snapshot)) {
        ApplySettingsSnapshot(snapshot);
        return;
    }
    std::unique_ptr<Widget> widget(new Widget());
    widget->config = DefaultConfig(WIDGET_ANALOG, 0);
    widgets.push_back(std::move(widget));
}

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
        size_t minutesStart = secondsStart > 2 ? secondsStart - 2 : 0;
        if (!ParseUnsignedGroup(compact.substr(secondsStart), &seconds)) {
            return false;
        }
        if (secondsStart > 0 && !ParseUnsignedGroup(compact.substr(minutesStart, secondsStart - minutesStart), &minutes)) {
            return false;
        }
        if (minutesStart > 0 && !ParseUnsignedGroup(compact.substr(0, minutesStart), &hours)) {
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

static std::wstring FormatOffset(LONGLONG milliseconds) {
    bool negative = milliseconds < 0;
    ULONGLONG value = negative ? static_cast<ULONGLONG>(-(milliseconds + 1)) + 1ULL : static_cast<ULONGLONG>(milliseconds);
    ULONGLONG hours = value / 3600000;
    int minutes = static_cast<int>((value / 60000) % 60);
    int seconds = static_cast<int>((value / 1000) % 60);
    int hundredths = static_cast<int>((value / 10) % 100);
    wchar_t text[64] = {};
    swprintf_s(text, L"%s%02llu:%02d:%02d.%02d", negative ? L"-" : L"", hours, minutes, seconds, hundredths);
    return text;
}

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
    if (!ParseUnsignedGroup(groups[0], &parsedHour) || groups.size() == 2 && !ParseUnsignedGroup(groups[1], &parsedMinute) || parsedHour > 23 || parsedMinute > 59) {
        return false;
    }
    *hour = static_cast<int>(parsedHour);
    *minute = static_cast<int>(parsedMinute);
    return true;
}

static void StartNtpSynchronization(bool force) {
    if (!useNtpTime || !winsockReady) {
        return;
    }
    ULONGLONG now = GetTickCount64();
    ULONGLONG interval = ntpTimeValid && !ntpLastQueryFailed ? 5ULL * 60ULL * 1000ULL : 60ULL * 1000ULL;
    if (!force && lastNtpAttemptTick != 0 && now - lastNtpAttemptTick < interval) {
        return;
    }
    bool expected = false;
    if (!ntpQueryRunning.compare_exchange_strong(expected, true)) {
        return;
    }
    if (hNtpThread != nullptr) {
        CloseHandle(hNtpThread);
        hNtpThread = nullptr;
    }
    ntpStopRequested = false;
    lastNtpAttemptTick = now;
    hNtpThread = StartNtpQueryThread(ntpServers, ntpGeneration.load(), hController, WM_NTP_RESULT, &ntpStopRequested, &ntpQueryRunning);
    if (hNtpThread == nullptr) {
        ntpQueryRunning = false;
    }
}

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

static void GetApplicationUtcTime(SYSTEMTIME* utc) {
    ULONGLONG value = CurrentFileTimeValue();
    if (useNtpTime && ntpTimeValid) {
        value = static_cast<ULONGLONG>(static_cast<LONGLONG>(value) + ntpOffset100Nanoseconds.load());
    }
    FILETIME fileTime = {};
    ULARGE_INTEGER parts = {};
    parts.QuadPart = value;
    fileTime.dwLowDateTime = parts.LowPart;
    fileTime.dwHighDateTime = parts.HighPart;
    FileTimeToSystemTime(&fileTime, utc);
}

static void GetDisplayedTime(const WidgetConfig& config, SYSTEMTIME* displayed) {
    SYSTEMTIME utc = {};
    GetApplicationUtcTime(&utc);
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

static void ClearCurrentTimeSignalSources() {
    currentTimeSignalIncludesRegular = false;
    currentTimeSignalAlarmWidgetIds.clear();
}

static void CheckTimeSignals() {
    if (IsTimeSignalPlaybackRunning()) {
        return;
    }
    ULONGLONG systemNow = CurrentFileTimeValue();
    struct TimeSignalCandidate {
        ULONGLONG target;
        bool regular;
        int alarmWidgetId;
    };
    std::vector<TimeSignalCandidate> candidates;
    for (size_t index = 0; index < widgets.size(); index++) {
        Widget* widget = widgets[index].get();
        int mode = static_cast<int>(widgets[index]->config.timeSignal);
        bool regularSignal = mode > TIME_SIGNAL_NONE && mode < TIME_SIGNAL_COUNT;
        bool alarmSignal = widget->config.alarmEnabled && widget->config.alarmTimeSignal && widget->config.type != WIDGET_CALENDAR;
        if (!regularSignal && !alarmSignal) {
            continue;
        }
        SYSTEMTIME displayed = {};
        GetDisplayedTime(widget->config, &displayed);
        ULONGLONG displayedValue = SystemTimeValue(displayed);
        if (displayedValue == 0) {
            continue;
        }
        ULONGLONG target = 0;
        if (regularSignal && CalculateTimeSignalTarget(displayedValue, systemNow, static_cast<TimeSignalMode>(mode), &target)) {
            candidates.push_back({ target, true, -1 });
        }
        if (alarmSignal && CalculateAlarmTimeSignalTarget(displayedValue, systemNow, widget->config.alarmHour, widget->config.alarmMinute,
            widget->alarmActive, &target)) {
            candidates.push_back({ target, false, widget->config.id });
        }
    }
    ULONGLONG selectedTarget = 0;
    for (size_t index = 0; index < candidates.size(); index++) {
        if (selectedTarget == 0 || candidates[index].target < selectedTarget) {
            selectedTarget = candidates[index].target;
        }
    }
    if (selectedTarget == 0) {
        return;
    }
    if (lastTimeSignalTarget != 0 && TimeSignalTargetsCoincide(selectedTarget, lastTimeSignalTarget)) {
        return;
    }
    bool includesRegular = false;
    std::vector<int> alarmWidgetIds;
    for (size_t index = 0; index < candidates.size(); index++) {
        if (!TimeSignalTargetsCoincide(candidates[index].target, selectedTarget)) {
            continue;
        }
        includesRegular = includesRegular || candidates[index].regular;
        if (candidates[index].alarmWidgetId >= 0 && std::find(alarmWidgetIds.begin(), alarmWidgetIds.end(), candidates[index].alarmWidgetId) == alarmWidgetIds.end()) {
            alarmWidgetIds.push_back(candidates[index].alarmWidgetId);
        }
    }
    if (StartTimeSignalPlayback(selectedTarget, hController, WM_TIME_SIGNAL_FINISHED)) {
        lastTimeSignalTarget = selectedTarget;
        currentTimeSignalIncludesRegular = includesRegular;
        currentTimeSignalAlarmWidgetIds = alarmWidgetIds;
    }
}

static void ShowCopiedDateTooltip(Widget* widget, const std::wstring& text) {
    if (widget == nullptr || widget->window == nullptr) {
        return;
    }
    if (widget->copyTooltip != nullptr && IsWindow(widget->copyTooltip)) {
        DestroyWindow(widget->copyTooltip);
    }
    widget->copyTooltipText = text;
    widget->copyTooltip = CreateWindowExW(WS_EX_TOPMOST, TOOLTIPS_CLASSW, nullptr, WS_POPUP | TTS_ALWAYSTIP | TTS_NOPREFIX, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, widget->window, nullptr, hInstance, nullptr);
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

static void CopyWidgetDate(Widget* widget, const SYSTEMTIME& date) {
    if (widget == nullptr) {
        return;
    }
    std::wstring text = FormatWidgetDate(widget->config, date, widget->config.dateCopyFormat);
    SIZE_T bytes = (text.size() + 1) * sizeof(wchar_t);
    HGLOBAL memory = GlobalAlloc(GMEM_MOVEABLE, bytes);
    if (memory == nullptr) {
        return;
    }
    void* target = GlobalLock(memory);
    if (target == nullptr) {
        GlobalFree(memory);
        return;
    }
    CopyMemory(target, text.c_str(), bytes);
    GlobalUnlock(memory);
    if (!OpenClipboard(widget->window)) {
        GlobalFree(memory);
        return;
    }
    EmptyClipboard();
    if (SetClipboardData(CF_UNICODETEXT, memory) == nullptr) {
        GlobalFree(memory);
    } else {
        ShowCopiedDateTooltip(widget, text);
    }
    CloseClipboard();
}

static SIZE GetCalendarSize(const WidgetConfig& config, bool borderless) {
    struct CalendarSizeEntry {
        AppLanguage language;
        bool weekNumbers;
        bool borderless;
        bool hideToday;
        bool themesDisabled;
        int fontAntialiasing;
        int fontWeight;
        bool fontItalic;
        BYTE fontCharSet;
        std::wstring fontFace;
        SIZE size;
    };
    static std::vector<CalendarSizeEntry> cache;
    bool disabledThemes = themesDisabled || config.disableThemes;
    for (size_t index = 0; index < cache.size(); index++) {
        const CalendarSizeEntry& entry = cache[index];
        bool matches = entry.language == config.language
            && entry.weekNumbers == config.weekNumbers
            && entry.borderless == borderless
            && entry.hideToday == (config.type == WIDGET_PANEL)
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
    if (config.type == WIDGET_PANEL) {
        style |= MCS_NOTODAY;
    }
    CalendarLocaleScope localeScope(LANGUAGE_LOCALES[config.language]);
    HWND calendar = CreateWindowExW(0, MONTHCAL_CLASSW, L"", style, 0, 0, 0, 0, nullptr, nullptr, hInstance, nullptr);
    if (calendar != nullptr) {
        SetWindowTheme(calendar, disabledThemes ? L"" : nullptr, disabledThemes ? L"" : nullptr);
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
    cache.push_back({
        config.language,
        config.weekNumbers,
        borderless,
        config.type == WIDGET_PANEL,
        disabledThemes,
        config.fontAntialiasing,
        config.fontWeight,
        config.fontItalic,
        config.fontCharSet,
        config.fontFace, size
        });
    return size;
}

static int GetDigitalBorderInset(int borderStyle) {
    if (borderStyle == DIGITAL_BORDER_NONE) {
        return 0;
    }
    if (borderStyle == DIGITAL_BORDER_3D) {
        return 3;
    }
    return 2;
}

static void ApplyDigitalNativeBorderStyle(int borderStyle, DWORD* style, DWORD* extendedStyle) {
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
    bool borderlessCalendar = config.type == WIDGET_PANEL || config.type == WIDGET_CALENDAR && !config.showFrame;
    SIZE calendarSize = GetCalendarSize(config, borderlessCalendar);
    if (config.type == WIDGET_ANALOG) {
        *width = config.size;
        *height = config.size;
    } else if (config.type == WIDGET_DIGITAL) {
        std::wstring sample;
        SYSTEMTIME displayed = {};
        GetDisplayedTime(config, &displayed);
        const wchar_t* hourSample = config.leadingZero || displayed.wHour >= 10 ? L"88" : L"8";
        if (config.showSeconds) {
            sample = std::wstring(hourSample) + L":88:88";
        } else {
            sample = std::wstring(hourSample) + L":88";
        }
        if (config.showUtc && config.showUtcText) {
            sample += L" UTC";
        }
        SIZE extent = {};
        TEXTMETRICW metrics = {};
        HDC screen = GetDC(nullptr);
        HFONT font = CreateWidgetDrawingFont(config);
        if (screen != nullptr && font != nullptr) {
            HGDIOBJ oldFont = SelectObject(screen, font);
            GetTextExtentPoint32W(screen, sample.c_str(), static_cast<int>(sample.size()), &extent);
            GetTextMetricsW(screen, &metrics);
            SelectObject(screen, oldFont);
        }
        if (font != nullptr) {
            DeleteObject(font);
        }
        if (screen != nullptr) {
            ReleaseDC(nullptr, screen);
        }
        int borderInset = config.transparentBackground ? GetDigitalBorderInset(config.borderStyle) : 0;
        int inset = config.padding + borderInset + config.borderWidth;
        *width = std::max(1, static_cast<int>(extent.cx) + inset * 2 + 4);
        *height = std::max(38, std::max(static_cast<int>(extent.cy), static_cast<int>(metrics.tmHeight)) + inset * 2 + 4);
        if (!config.transparentBackground) {
            DWORD style = WS_POPUP;
            DWORD extendedStyle = WS_EX_TOOLWINDOW;
            ApplyDigitalNativeBorderStyle(config.borderStyle, &style, &extendedStyle);
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
        const int clockGroupHeight = config.size + 27;
        const int contentHeight = std::max(static_cast<int>(calendarSize.cy), clockGroupHeight);
        const int zoneTop = 35 + contentHeight + 4;
        *width = PANEL_SIDE_PADDING + calendarSize.cx + 12 + config.size + PANEL_SIDE_PADDING;
        *height = zoneTop + 28 + 7;
    }
}

static void GetPanelLayout(const WidgetConfig& config, RECT* calendarRect, POINT* clockPosition, RECT* timeRect) {
    SIZE calendarSize = GetCalendarSize(config, true);
    const int contentTop = 35;
    const int clockGroupHeight = config.size + 27;
    const int contentHeight = std::max(static_cast<int>(calendarSize.cy), clockGroupHeight);
    const int calendarTop = contentTop + (contentHeight - calendarSize.cy) / 2 + PANEL_CALENDAR_OFFSET_Y;
    const int clockLeft = PANEL_SIDE_PADDING + calendarSize.cx + 12;
    const int clockTop = contentTop + (contentHeight - clockGroupHeight) / 2;
    if (calendarRect != nullptr) {
        *calendarRect = { PANEL_SIDE_PADDING, calendarTop, PANEL_SIDE_PADDING + calendarSize.cx, calendarTop + calendarSize.cy };
    }
    if (clockPosition != nullptr) {
        *clockPosition = { clockLeft, clockTop };
    }
    if (timeRect != nullptr) {
        *timeRect = { clockLeft, clockTop + config.size + 2, clockLeft + config.size, clockTop + config.size + 27 };
    }
}

static void ClampWidgetPosition(WidgetConfig* config) {
    int width = 0;
    int height = 0;
    GetWidgetDimensions(*config, &width, &height);
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
    config->x = width >= workRight - workLeft ? workLeft : std::clamp(config->x, workLeft, workRight - width);
    config->y = height >= workBottom - workTop ? workTop : std::clamp(config->y, workTop, workBottom - height);
}

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

static void SaveFormPosition(HWND window, int* x, int* y) {
    RECT rect = {};
    if (window != nullptr && GetWindowRect(window, &rect)) {
        *x = rect.left;
        *y = rect.top;
    }
}

static std::wstring GetSystemMessageFontFace() {
    NONCLIENTMETRICSW metrics = {};
    metrics.cbSize = sizeof(metrics);
    if (SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof(metrics), &metrics, 0) && metrics.lfMessageFont.lfFaceName[0] != L'\0') {
        return metrics.lfMessageFont.lfFaceName;
    }
    HFONT fallbackFont = static_cast<HFONT>(GetStockObject(DEFAULT_GUI_FONT));
    LOGFONTW fallback = {};
    if (fallbackFont != nullptr && GetObjectW(fallbackFont, sizeof(fallback), &fallback) == sizeof(fallback) && fallback.lfFaceName[0] != L'\0') {
        return fallback.lfFaceName;
    }
    return std::wstring();
}

static BYTE FontQuality(int fontAntialiasing) {
    return fontAntialiasing == FONT_ANTIALIAS_CLEARTYPE ? CLEARTYPE_QUALITY : ANTIALIASED_QUALITY;
}

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

static void UpdateApplicationFontButtons() {
    if (hAppFontButton != nullptr) {
        const wchar_t* caption = settingsAppFontFace.empty() ? SYSTEM_DEFAULT_FONT_LABELS[appLanguage] : settingsAppFontFace.c_str();
        SetWindowTextW(hAppFontButton, caption);
    }
    if (hAppFontDefaultButton != nullptr) {
        EnableWindow(hAppFontDefaultButton, !settingsAppFontFace.empty() || settingsAppFontWeight != FW_NORMAL || settingsAppFontItalic || settingsAppFontDialogSize != 90);
    }
}

static void ResetUiFont() {
    if (hUiFont != nullptr) {
        DeleteObject(hUiFont);
        hUiFont = nullptr;
    }
}

static int CALLBACK FindFontCallback(const LOGFONTW*, const TEXTMETRICW*, DWORD, LPARAM parameter) {
    *reinterpret_cast<bool*>(parameter) = true;
    return 0;
}

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

static BOOL CALLBACK ApplyFontAndTheme(HWND child, LPARAM) {
    HFONT font = GetParent(child) == hAbout && GetDlgCtrlID(child) == ID_INFO_TEXT && hAboutFont != nullptr ? hAboutFont : hUiFont;
    if (font != nullptr) {
        SendMessageW(child, WM_SETFONT, reinterpret_cast<WPARAM>(font), TRUE);
    }
    SetWindowTheme(child, themesDisabled ? L"" : nullptr, themesDisabled ? L"" : nullptr);
    return TRUE;
}

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
    SetWindowTheme(window, themesDisabled ? L"" : nullptr, themesDisabled ? L"" : nullptr);
    EnumChildWindows(window, ApplyFontAndTheme, 0);
    RedrawWindow(window, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN);
}

static void ApplyWidgetTheme(HWND window, const WidgetConfig& config) {
    if (window == nullptr) {
        return;
    }
    bool disabled = themesDisabled || config.disableThemes;
    SetWindowTheme(window, disabled ? L"" : nullptr, disabled ? L"" : nullptr);
    RedrawWindow(window, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN);
}

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
        SetWindowPos(widget->calendarChild, nullptr, 0, 0, minimum.right - minimum.left, minimum.bottom - minimum.top, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
    }
    RedrawWindow(widget->calendarChild, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_UPDATENOW);
}

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

static void UpdateAnalogTime(Widget* widget) {
    if (widget == nullptr || widget->analogChild == nullptr) {
        return;
    }
    SYSTEMTIME time = {};
    GetDisplayedTime(widget->config, &time);
    SetAnalogClockTime(widget->analogChild, time);
}

static COLORREF ReadAnalogBackground(const Widget* widget) {
    return ReadAnalogClockBackground(widget == nullptr ? nullptr : widget->analogChild);
}

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

static COLORREF PanelBackgroundColor(const Widget* widget) {
    return widget != nullptr && widget->analogBackground != CLR_INVALID ? widget->analogBackground : ReadAnalogBackground(widget);
}

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

static void PresentLayeredBitmap(Widget* widget, HDC sourceDC, HDC screenDC, int width, int height, BYTE opacity) {
    RECT current = {};
    GetWindowRect(widget->window, &current);
    POINT destination = { widget->rendered ? current.left : widget->config.x, widget->rendered ? current.top : widget->config.y };
    POINT source = { 0, 0 };
    SIZE size = { width, height };
    BLENDFUNCTION blend = { AC_SRC_OVER, 0, opacity, AC_SRC_ALPHA };
    if (UpdateLayeredWindow(widget->window, screenDC, &destination, &size, sourceDC, &source, 0, &blend, ULW_ALPHA)) {
        widget->rendered = true;
    }
}

static bool RenderAnalogBackground(Widget* widget, HDC reference, DWORD background, HBITMAP* bitmap, DWORD** pixels) {
    if (widget == nullptr || widget->analogChild == nullptr || !CreateDib(reference, widget->config.size, widget->config.size, bitmap, pixels)) {
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

static void RenderAnalogWidget(Widget* widget) {
    int size = widget->config.size;
    HDC screen = GetDC(nullptr);
    if (screen == nullptr) {
        return;
    }
    HBITMAP whiteBitmap = nullptr;
    HBITMAP blackBitmap = nullptr;
    DWORD* whitePixels = nullptr;
    DWORD* blackPixels = nullptr;
    if (!RenderAnalogBackground(widget, screen, 0xFFFFFFFF, &whiteBitmap, &whitePixels) || !RenderAnalogBackground(widget, screen, 0xFF000000, &blackBitmap, &blackPixels)) {
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
    HDC outputDC = CreateCompatibleDC(screen);
    if (!CreateDib(screen, size, size, &outputBitmap, &output)) {
        DeleteObject(whiteBitmap);
        DeleteObject(blackBitmap);
        DeleteDC(outputDC);
        ReleaseDC(nullptr, screen);
        return;
    }
    for (int index = 0; index < size * size; index++) {
        DWORD white = whitePixels[index];
        DWORD black = blackPixels[index];
        int wb = static_cast<BYTE>(white);
        int wg = static_cast<BYTE>(white >> 8);
        int wr = static_cast<BYTE>(white >> 16);
        int bb = static_cast<BYTE>(black);
        int bg = static_cast<BYTE>(black >> 8);
        int br = static_cast<BYTE>(black >> 16);
        int alpha = 255 - std::clamp(((wr - br) + (wg - bg) + (wb - bb)) / 3, 0, 255);
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
        output[index] = (static_cast<DWORD>(alpha) << 24) | (red << 16) | (green << 8) | blue;
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

static HFONT CreatePanelFont(const FontSelection& selection, int fontAntialiasing) {
    HDC screen = GetDC(nullptr);
    int dpi = screen == nullptr ? 96 : GetDeviceCaps(screen, LOGPIXELSY);
    if (screen != nullptr) {
        ReleaseDC(nullptr, screen);
    }
    int height = -MulDiv(std::clamp(selection.dialogSize, 10, 9990), dpi, 720);
    return CreateFontW(height, 0, 0, 0, selection.weight, selection.italic, selection.underline, selection.strikeOut, selection.charSet, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, FontQuality(fontAntialiasing), DEFAULT_PITCH | FF_DONTCARE, selection.face.c_str());
}

static HFONT CreateWidgetDrawingFont(const WidgetConfig& config) {
    HDC screen = GetDC(nullptr);
    int dpi = screen == nullptr ? 96 : GetDeviceCaps(screen, LOGPIXELSY);
    if (screen != nullptr) {
        ReleaseDC(nullptr, screen);
    }
    int height = -MulDiv(config.fontSize, dpi, 72);
    return CreateFontW(height, 0, 0, 0, config.fontWeight, config.fontItalic, config.fontUnderline, config.fontStrikeOut, config.fontCharSet, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, FontQuality(config.fontAntialiasing), DEFAULT_PITCH | FF_DONTCARE, config.fontFace.c_str());
}

static HFONT CreateFullscreenDrawingFont(const WidgetConfig& config, const RECT& client, HDC dc, const wchar_t* text) {
    int width = client.right - client.left;
    int height = client.bottom - client.top;
    int pixelHeight = std::max(1, height * std::clamp(config.fontSize, FULLSCREEN_FONT_SIZE_MIN, FULLSCREEN_FONT_SIZE_MAX) / 100);
    HFONT font = CreateFontW(-pixelHeight, 0, 0, 0, config.fontWeight, config.fontItalic, config.fontUnderline, config.fontStrikeOut, config.fontCharSet, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, FontQuality(config.fontAntialiasing), DEFAULT_PITCH | FF_DONTCARE, config.fontFace.c_str());
    if (font == nullptr || dc == nullptr || text == nullptr || text[0] == L'\0') {
        return font;
    }
    HGDIOBJ oldFont = SelectObject(dc, font);
    SIZE textSize = {};
    BOOL measured = GetTextExtentPoint32W(dc, text, static_cast<int>(wcslen(text)), &textSize);
    SelectObject(dc, oldFont);
    if (measured && textSize.cx > width && textSize.cx > 0) {
        int fittedHeight = std::max(1, MulDiv(pixelHeight, width, textSize.cx));
        DeleteObject(font);
        font = CreateFontW(-fittedHeight, 0, 0, 0, config.fontWeight, config.fontItalic, config.fontUnderline, config.fontStrikeOut, config.fontCharSet, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, FontQuality(config.fontAntialiasing), DEFAULT_PITCH | FF_DONTCARE, config.fontFace.c_str());
    }
    return font;
}

static void DrawCenteredText(HDC dc, const std::wstring& text, RECT rect, HFONT font, COLORREF color, UINT format = DT_CENTER | DT_VCENTER | DT_SINGLELINE, COLORREF backgroundColor = CLR_INVALID) {
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

static void InitializeDirectTextRendering() {
    d2dModule = LoadSystemLibrary(L"d2d1.dll");
    dwriteModule = LoadSystemLibrary(L"dwrite.dll");
    if (d2dModule == nullptr || dwriteModule == nullptr) {
        ShutdownDirectTextRendering();
        return;
    }
    D2D1CreateFactoryProc createD2dFactory = reinterpret_cast<D2D1CreateFactoryProc>(GetProcAddress(d2dModule, "D2D1CreateFactory"));
    DWriteCreateFactoryProc createDwriteFactory = reinterpret_cast<DWriteCreateFactoryProc>(GetProcAddress(dwriteModule, "DWriteCreateFactory"));
    if (createD2dFactory == nullptr || createDwriteFactory == nullptr) {
        ShutdownDirectTextRendering();
        return;
    }
    D2D1_FACTORY_OPTIONS options = {};
    HRESULT d2dResult = createD2dFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), &options, reinterpret_cast<void**>(&d2dFactory));
    HRESULT dwriteResult = createDwriteFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&dwriteFactory));
    if (FAILED(d2dResult) || FAILED(dwriteResult) || d2dFactory == nullptr || dwriteFactory == nullptr) {
        ShutdownDirectTextRendering();
    }
}

static bool DrawFullscreenText(HDC dc, const wchar_t* text, const RECT& rect, const WidgetConfig& config, COLORREF color, COLORREF backgroundColor) {
    if (d2dFactory == nullptr || dwriteFactory == nullptr || dc == nullptr || text == nullptr || text[0] == L'\0') {
        return false;
    }
    int width = std::max(1L, rect.right - rect.left);
    int height = std::max(1L, rect.bottom - rect.top);
    D2D1_RENDER_TARGET_PROPERTIES properties = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE), 96.0f, 96.0f, D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE);
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
    float fontSize = std::max(1.0f, static_cast<float>(height) * static_cast<float>(std::clamp(config.fontSize, FULLSCREEN_FONT_SIZE_MIN, FULLSCREEN_FONT_SIZE_MAX)) / 100.0f);
    DWRITE_FONT_WEIGHT weight = static_cast<DWRITE_FONT_WEIGHT>(std::clamp(config.fontWeight, 1, 999));
    DWRITE_FONT_STYLE style = config.fontItalic ? DWRITE_FONT_STYLE_ITALIC : DWRITE_FONT_STYLE_NORMAL;
    IDWriteTextFormat* format = nullptr;
    const wchar_t* fontFace = config.fontFace.empty() ? L"Arial" : config.fontFace.c_str();
    result = dwriteFactory->CreateTextFormat(fontFace, nullptr, weight, style, DWRITE_FONT_STRETCH_NORMAL, fontSize, LANGUAGE_LOCALES[config.language], &format);
    if (FAILED(result) || format == nullptr) {
        target->Release();
        return false;
    }
    format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    format->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
    UINT32 length = static_cast<UINT32>(wcslen(text));
    IDWriteTextLayout* layout = nullptr;
    result = dwriteFactory->CreateTextLayout(text, length, format, static_cast<float>(width), static_cast<float>(height), &layout);
    if (FAILED(result) || layout == nullptr) {
        format->Release();
        target->Release();
        return false;
    }
    DWRITE_TEXT_METRICS metrics = {};
    if (SUCCEEDED(layout->GetMetrics(&metrics)) && metrics.widthIncludingTrailingWhitespace > static_cast<float>(width) && metrics.widthIncludingTrailingWhitespace > 0.0f) {
        fontSize = std::max(1.0f, fontSize * static_cast<float>(width) / metrics.widthIncludingTrailingWhitespace);
        layout->Release();
        format->Release();
        layout = nullptr;
        format = nullptr;
        result = dwriteFactory->CreateTextFormat(fontFace, nullptr, weight, style, DWRITE_FONT_STRETCH_NORMAL, fontSize, LANGUAGE_LOCALES[config.language], &format);
        if (SUCCEEDED(result) && format != nullptr) {
            format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
            format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
            format->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
            result = dwriteFactory->CreateTextLayout(text, length, format, static_cast<float>(width), static_cast<float>(height), &layout);
        }
    }
    if (FAILED(result) || format == nullptr || layout == nullptr) {
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
    result = target->CreateSolidColorBrush(D2D1::ColorF(GetRValue(color) / 255.0f, GetGValue(color) / 255.0f, GetBValue(color) / 255.0f), &brush);
    if (SUCCEEDED(result) && brush != nullptr) {
        target->SetTextAntialiasMode(config.fontAntialiasing == FONT_ANTIALIAS_CLEARTYPE ? D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE : D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
        target->BeginDraw();
        target->Clear(D2D1::ColorF(GetRValue(backgroundColor) / 255.0f, GetGValue(backgroundColor) / 255.0f, GetBValue(backgroundColor) / 255.0f));
        target->DrawTextLayout(D2D1::Point2F(0.0f, 0.0f), layout, brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
        result = target->EndDraw();
    }
    if (brush != nullptr) {
        brush->Release();
    }
    layout->Release();
    format->Release();
    target->Release();
    return SUCCEEDED(result);
}

static void DrawDigitalBorder(HDC dc, int width, int height, int borderStyle, COLORREF color) {
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

static void GetDigitalTimeText(const WidgetConfig& config, wchar_t* text, size_t textCount) {
    SYSTEMTIME time = {};
    GetDisplayedTime(config, &time);
    if (config.showSeconds) {
        swprintf_s(text, textCount, config.leadingZero ? L"%02d:%02d:%02d" : L"%d:%02d:%02d", time.wHour, time.wMinute, time.wSecond);
    } else {
        swprintf_s(text, textCount, config.leadingZero ? L"%02d:%02d" : L"%d:%02d", time.wHour, time.wMinute);
    }
    if (config.showUtc && config.showUtcText) {
        wcscat_s(text, textCount, L" UTC");
    }
}

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

static void PaintOpaqueDigitalWidget(Widget* widget, HWND window, HDC dc) {
    RECT client = {};
    GetClientRect(window, &client);
    bool alarmFlash = widget->alarmActive && widget->flashPhase;
    COLORREF textColor = alarmFlash ? widget->config.alarmTextColor : widget->config.textColor;
    COLORREF backgroundColor = alarmFlash ? widget->config.alarmBackgroundColor : widget->config.backgroundColor;
    HBRUSH background = CreateSolidBrush(backgroundColor);
    FillRect(dc, &client, background);
    DeleteObject(background);
    wchar_t text[32] = {};
    GetDigitalTimeText(widget->config, text, _countof(text));
    RECT textRect = client;
    int textInset = GetDigitalTextInset(widget, client);
    InflateRect(&textRect, -textInset, -textInset);
    bool fullscreenDrawn = widget->config.type == WIDGET_FULLSCREEN && DrawFullscreenText(dc, text, textRect, widget->config, textColor, backgroundColor);
    if (!fullscreenDrawn) {
        HFONT font = widget->config.type == WIDGET_FULLSCREEN ? CreateFullscreenDrawingFont(widget->config, textRect, dc, text) : CreateWidgetDrawingFont(widget->config);
        DrawCenteredText(dc, text, textRect, font, textColor, DT_CENTER | DT_VCENTER | DT_SINGLELINE, backgroundColor);
        DeleteObject(font);
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
    RECT full = { 0, 0, width, height };
    FillRect(dc, &full, background);
    DeleteObject(background);
    wchar_t text[32] = {};
    GetDigitalTimeText(widget->config, text, _countof(text));
    int borderStyleInset = GetDigitalBorderInset(widget->config.borderStyle);
    int inset = widget->config.padding + borderStyleInset + widget->config.borderWidth;
    RECT textRect = { inset, inset, width - inset, height - inset };
    HFONT font = CreateWidgetDrawingFont(widget->config);
    DrawCenteredText(dc, text, textRect, font, transparentDigital ? RGB(0, 0, 0) : textColor);
    DeleteObject(font);
    DrawDigitalBorder(dc, width, height, widget->config.borderStyle, transparentDigital ? RGB(0, 0, 0) : textColor);
    DrawDigitalWidthBorder(dc, width, height, borderStyleInset, widget->config.borderWidth, transparentDigital ? RGB(0, 0, 0) : textColor);
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
            int coverage = 255 - (static_cast<BYTE>(pixel) + static_cast<BYTE>(pixel >> 8) + static_cast<BYTE>(pixel >> 16)) / 3;
            int alpha = std::max(minimumHitTestAlpha, coverage);
            int red = GetRValue(color) * alpha / 255;
            int green = GetGValue(color) * alpha / 255;
            int blue = GetBValue(color) * alpha / 255;
            pixels[index] = (static_cast<DWORD>(alpha) << 24) | (red << 16) | (green << 8) | blue;
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

static void CreatePanelDateTooltip(Widget* widget) {
    if (widget->config.type != WIDGET_PANEL) {
        return;
    }
    widget->panelDateTooltip = CreateWindowExW(WS_EX_TOPMOST | WS_EX_NOACTIVATE, TOOLTIPS_CLASSW, nullptr, WS_POPUP | TTS_ALWAYSTIP | TTS_NOPREFIX, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, widget->window, nullptr, hInstance, nullptr);
    if (widget->panelDateTooltip == nullptr) {
        return;
    }
    ApplyWidgetTheme(widget->panelDateTooltip, widget->config);
    TOOLINFOW information = {};
    information.cbSize = sizeof(information);
    information.uFlags = TTF_SUBCLASS;
    information.hwnd = widget->window;
    information.uId = 1;
    information.rect = widget->panelDateLinkRect;
    information.lpszText = LPSTR_TEXTCALLBACKW;
    if (!SendMessageW(widget->panelDateTooltip, TTM_ADDTOOLW, 0, reinterpret_cast<LPARAM>(&information))) {
        DestroyWindow(widget->panelDateTooltip);
        widget->panelDateTooltip = nullptr;
    }
}

static void PaintPanelWidget(Widget* widget, HDC dc) {
    if (widget == nullptr) {
        return;
    }
    int width = 0;
    int height = 0;
    GetWidgetDimensions(widget->config, &width, &height);
    RECT full = { 0, 0, width, height };
    HBRUSH background = CreateSolidBrush(PanelBackgroundColor(widget));
    FillRect(dc, &full, background);
    DeleteObject(background);
    SYSTEMTIME time = {};
    GetDisplayedTime(widget->config, &time);
    FontSelection topSelection = widget->config.panelTopFont;
    topSelection.underline = widget->panelDateHot;
    HFONT topFont = CreatePanelFont(topSelection, widget->config.fontAntialiasing);
    HFONT timeFont = CreatePanelFont(widget->config.panelTimeFont, widget->config.fontAntialiasing);
    HFONT bottomFont = CreatePanelFont(widget->config.panelBottomFont, widget->config.fontAntialiasing);
    wchar_t dateText[128] = {};
    GetDateFormatEx(LANGUAGE_LOCALES[widget->config.language], DATE_LONGDATE, &time, nullptr, dateText, ARRAYSIZE(dateText), nullptr);
    RECT dateRect = { PANEL_SIDE_PADDING, 7, width - PANEL_SIDE_PADDING, 34 };
    HGDIOBJ previousFont = SelectObject(dc, topFont);
    SIZE dateSize = {};
    GetTextExtentPoint32W(dc, dateText, static_cast<int>(wcslen(dateText)), &dateSize);
    SelectObject(dc, previousFont);
    LONG dateLeft = dateRect.left + (dateRect.right - dateRect.left - dateSize.cx) / 2;
    LONG dateTop = dateRect.top + (dateRect.bottom - dateRect.top - dateSize.cy) / 2;
    RECT dateLink = { dateLeft, dateTop, dateLeft + dateSize.cx, dateTop + dateSize.cy };
    RECT clippedDateLink = {};
    IntersectRect(&clippedDateLink, &dateRect, &dateLink);
    if (!EqualRect(&widget->panelDateLinkRect, &clippedDateLink)) {
        widget->panelDateLinkRect = clippedDateLink;
        if (widget->panelDateTooltip != nullptr) {
            TOOLINFOW information = {};
            information.cbSize = sizeof(information);
            information.hwnd = widget->window;
            information.uId = 1;
            information.rect = clippedDateLink;
            SendMessageW(widget->panelDateTooltip, TTM_NEWTOOLRECTW, 0, reinterpret_cast<LPARAM>(&information));
        }
    }
    DrawCenteredText(dc, dateText, dateRect, topFont, RGB(0, 83, 184));
    RECT calendarRect = {};
    RECT timeRect = {};
    GetPanelLayout(widget->config, &calendarRect, nullptr, &timeRect);
    wchar_t clockText[32] = {};
    if (widget->config.showSeconds) {
        swprintf_s(clockText, widget->config.leadingZero ? L"%02d:%02d:%02d" : L"%d:%02d:%02d", time.wHour, time.wMinute, time.wSecond);
    } else {
        swprintf_s(clockText, widget->config.leadingZero ? L"%02d:%02d" : L"%d:%02d", time.wHour, time.wMinute);
    }
    if (widget->config.showUtc && widget->config.showUtcText) {
        wcscat_s(clockText, L" UTC");
    }
    DrawCenteredText(dc, clockText, timeRect, timeFont, RGB(0, 0, 0));
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
    int zoneTop = std::max(calendarRect.bottom - PANEL_CALENDAR_OFFSET_Y, timeRect.bottom) + 4;
    RECT zoneRect = { PANEL_SIDE_PADDING, zoneTop, width - PANEL_SIDE_PADDING, zoneTop + 28 };
    DrawCenteredText(dc, zoneText, zoneRect, bottomFont, RGB(0, 83, 184), DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
    DeleteObject(topFont);
    DeleteObject(timeFont);
    DeleteObject(bottomFont);
    if (widget->config.showFrame) {
        RECT frameRect = full;
        HTHEME calendarTheme = themesDisabled || widget->config.disableThemes ? nullptr : OpenThemeData(widget->calendarChild, VSCLASS_MONTHCAL);
        HRESULT frameResult = calendarTheme == nullptr ? E_FAIL : DrawThemeBackground(calendarTheme, dc, MC_BORDERS, 0, &frameRect, nullptr);
        if (calendarTheme != nullptr) {
            CloseThemeData(calendarTheme);
        }
        if (FAILED(frameResult)) {
            DrawEdge(dc, &frameRect, EDGE_SUNKEN, BF_RECT);
        }
    }
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
            if (widget->calendarChild != nullptr && widget->lastPanelDateKey != dateKey) {
                MonthCal_SetToday(widget->calendarChild, &displayed);
            }
            widget->lastPanelDateKey = dateKey;
            InvalidateRect(widget->window, nullptr, FALSE);
        } else {
            RECT timeRect = {};
            GetPanelLayout(widget->config, nullptr, nullptr, &timeRect);
            InvalidateRect(widget->window, &timeRect, FALSE);
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
        if (GetWindowRect(widget->window, &current) && (current.right - current.left != desiredWidth || current.bottom - current.top != desiredHeight)) {
            SetWindowPos(widget->window, nullptr, 0, 0, desiredWidth, desiredHeight, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
        }
        InvalidateRect(widget->window, nullptr, FALSE);
        UpdateWindow(widget->window);
        widget->rendered = true;
    }
}

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

static void ApplyWidgetZOrder(Widget* widget) {
    if (widget == nullptr || widget->window == nullptr) {
        return;
    }
    bool topMost = widget->config.topMost || widget->config.type == WIDGET_FULLSCREEN;
    if (topMost) {
        SetWindowPos(widget->window, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    } else {
        SetWindowPos(widget->window, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        SetWindowPos(widget->window, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
    for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
        SetWindowPos(widget->fullscreenWindows[index], topMost ? HWND_TOPMOST : HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
}

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
        SetWindowPos(widget->fullscreenWindows[index], HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
    RenderWidgetIdentification(widget);
}

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
}

static void StopWidgetAlarm(Widget* widget) {
    if (widget == nullptr) {
        return;
    }
    CloseWidgetAudio(widget);
    widget->alarmActive = false;
    widget->flashPhase = false;
    currentTimeSignalAlarmWidgetIds.erase(std::remove(currentTimeSignalAlarmWidgetIds.begin(), currentTimeSignalAlarmWidgetIds.end(), widget->config.id),
        currentTimeSignalAlarmWidgetIds.end());
    if (IsTimeSignalPlaybackRunning() && !currentTimeSignalIncludesRegular && currentTimeSignalAlarmWidgetIds.empty()) {
        StopTimeSignalPlayback();
        ClearCurrentTimeSignalSources();
    }
    RenderWidget(widget);
    if (widget->config.type == WIDGET_PANEL && widget->window != nullptr) {
        InvalidateRect(widget->window, nullptr, FALSE);
    }
}

static void StopAllAlarms() {
    for (size_t index = 0; index < widgets.size(); index++) {
        StopWidgetAlarm(widgets[index].get());
    }
}

static void StartWidgetAlarm(Widget* widget) {
    if (widget == nullptr) {
        return;
    }
    CloseWidgetAudio(widget);
    widget->alarmActive = true;
    widget->flashPhase = true;
    if (widget->config.runCommand && !widget->config.command.empty()) {
        if (LooksLikeAudio(widget->config.command)) {
            StartAudioPlaybackAsync(widget->config.command, widget->config.loopAudio, hController, WM_AUDIO_FINISHED, widget->config.id, widget->audioGeneration, &widget->audioStopEvent);
        } else {
            StartLocalCommandAsync(widget->config.command);
        }
    }
    if (widget->config.callRemoteScript) {
        StartRemoteScriptAsync(widget->config.remoteScriptUrl);
    }
    RenderWidget(widget);
}

static void CheckWidgetAlarm(Widget* widget) {
    if (widget == nullptr || !widget->config.alarmEnabled || widget->config.type == WIDGET_CALENDAR) {
        return;
    }
    SYSTEMTIME time = {};
    GetDisplayedTime(widget->config, &time);
    int date = time.wYear * 10000 + time.wMonth * 100 + time.wDay;
    int minute = time.wHour * 60 + time.wMinute;
    if (time.wHour == widget->config.alarmHour && time.wMinute == widget->config.alarmMinute && (widget->lastAlarmDate != date || widget->lastAlarmMinute != minute)) {
        widget->lastAlarmDate = date;
        widget->lastAlarmMinute = minute;
        StartWidgetAlarm(widget);
    }
}

static void SaveWidgetPosition(Widget* widget) {
    if (widget == nullptr || widget->window == nullptr || widget->config.type == WIDGET_FULLSCREEN) {
        return;
    }
    RECT rect = {};
    if (GetWindowRect(widget->window, &rect)) {
        widget->config.x = rect.left;
        widget->config.y = rect.top;
        SynchronizeOpenSettings(widget);
        SaveAllSettings();
    }
}

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
    widget->analogChild = CreateAnalogClockControl(widget->window, childX, childY, widget->config.size, showAnalogSeconds, true);
    if (widget->analogChild != nullptr) {
        ApplyWidgetTheme(widget->analogChild, widget->config);
        if (!ConfigureAnalogClockControl(widget->analogChild, widget->config.size, showAnalogSeconds)) {
            DestroyWindow(widget->analogChild);
            widget->analogChild = nullptr;
            return;
        }
        widget->analogProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(widget->analogChild, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(AnalogChildProc)));
        UpdateAnalogTime(widget);
        if (widget->config.type == WIDGET_PANEL) {
            CaptureAnalogBackground(widget);
        }
    }
}

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
    HWND replacement = CreateAnalogClockControl(widget->window, childX, childY, widget->config.size, showAnalogSeconds, false);
    if (replacement == nullptr) {
        return false;
    }
    ApplyWidgetTheme(replacement, widget->config);
    if (!ConfigureAnalogClockControl(replacement, widget->config.size, showAnalogSeconds)) {
        DestroyWindow(replacement);
        return false;
    }
    WNDPROC replacementProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(replacement, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(AnalogChildProc)));
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

static void CreateCalendarChild(Widget* widget) {
    if (widget == nullptr) {
        return;
    }
    bool borderless = widget->config.type == WIDGET_PANEL || !widget->config.showFrame;
    SIZE calendarSize = GetCalendarSize(widget->config, borderless);
    int childX = 0;
    int childY = 0;
    if (widget->config.type == WIDGET_PANEL) {
        RECT calendarRect = {};
        GetPanelLayout(widget->config, &calendarRect, nullptr, nullptr);
        childX = calendarRect.left;
        childY = calendarRect.top;
    }
    DWORD style = WS_CHILD | (widget->config.weekNumbers ? MCS_WEEKNUMBERS : 0);
    if (widget->config.type == WIDGET_PANEL) {
        style |= MCS_NOTODAY;
    }
    CalendarLocaleScope localeScope(LANGUAGE_LOCALES[widget->config.language]);
    widget->calendarChild = CreateWindowExW(0, MONTHCAL_CLASSW, L"", style, 0, 0, 0, 0, widget->window, reinterpret_cast<HMENU>(114), hInstance, nullptr);
    if (widget->calendarChild != nullptr) {
        ApplyWidgetTheme(widget->calendarChild, widget->config);
    }
    if (widget->calendarChild != nullptr) {
        ApplyCalendarFont(widget);
        if (borderless) {
            MonthCal_SetCalendarBorder(widget->calendarChild, TRUE, 0);
        }
        SYSTEMTIME displayed = {};
        GetDisplayedTime(widget->config, &displayed);
        MonthCal_SetCurSel(widget->calendarChild, &displayed);
        MonthCal_SetFirstDayOfWeek(widget->calendarChild, widget->config.sundayFirst ? 6 : 0);
        RECT minimum = {};
        if (MonthCal_GetMinReqRect(widget->calendarChild, &minimum)) {
            calendarSize.cx = minimum.right - minimum.left;
            calendarSize.cy = minimum.bottom - minimum.top;
        }
        SetWindowPos(widget->calendarChild, nullptr, childX, childY, calendarSize.cx, calendarSize.cy, SWP_NOZORDER | SWP_NOACTIVATE);
        widget->calendarProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(widget->calendarChild, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(CalendarChildProc)));
        ShowWindow(widget->calendarChild, SW_SHOWNOACTIVATE);
        RedrawWindow(widget->calendarChild, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_UPDATENOW);
    }
}

static bool SetFullscreenPreview(Widget* widget) {
    if (widget == nullptr || widget->window == nullptr || widget->config.type != WIDGET_FULLSCREEN) {
        return false;
    }
    RECT monitorRect = {};
    if (!GetPrimarySelectedMonitorRect(widget->config, &monitorRect)) {
        return false;
    }
    int monitorWidth = monitorRect.right - monitorRect.left;
    int monitorHeight = monitorRect.bottom - monitorRect.top;
    int previewWidth = std::min(480, std::max(240, monitorWidth / 4));
    int previewHeight = std::max(120, MulDiv(previewWidth, monitorHeight, std::max(1, monitorWidth)));
    if (previewHeight > 300) {
        previewHeight = 300;
        previewWidth = std::max(160, MulDiv(previewHeight, monitorWidth, std::max(1, monitorHeight)));
    }
    int previewX = widget->config.previewX == CW_USEDEFAULT ? monitorRect.left + (monitorWidth - previewWidth) / 2 : widget->config.previewX;
    int previewY = widget->config.previewY == CW_USEDEFAULT ? monitorRect.top + (monitorHeight - previewHeight) / 2 : widget->config.previewY;
    RECT currentRect = {};
    if (widget->fullscreenPreview && GetWindowRect(widget->window, &currentRect)) {
        previewX = currentRect.left;
        previewY = currentRect.top;
    }
    ClampFormPosition(&previewX, &previewY, previewWidth, previewHeight);
    widget->fullscreenPreview = true;
    SetWindowPos(widget->window, HWND_TOPMOST, previewX, previewY, previewWidth, previewHeight, SWP_NOACTIVATE);
    for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
        ShowWindow(widget->fullscreenWindows[index], SW_HIDE);
    }
    return true;
}

static void CreateWidgetWindow(Widget* widget) {
    if (widget == nullptr) {
        return;
    }
    if (widget->config.type == WIDGET_ANALOG || widget->config.type == WIDGET_PANEL) {
        widget->config.size = NormalizeAnalogClockSize(widget->config.size);
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
    DWORD extended = WS_EX_TOOLWINDOW | ((widget->config.topMost || fullscreen) ? WS_EX_TOPMOST : 0);
    bool parentedControl = widget->config.type == WIDGET_PANEL || widget->config.type == WIDGET_CALENDAR;
    if (!fullscreen && (!parentedControl || widget->config.opacity < 100)) {
        extended |= WS_EX_LAYERED;
    }
    DWORD style = WS_POPUP | (parentedControl ? WS_CLIPCHILDREN : 0);
    if (widget->config.type == WIDGET_DIGITAL && !widget->config.transparentBackground) {
        ApplyDigitalNativeBorderStyle(widget->config.borderStyle, &style, &extended);
    }
    widget->window = CreateWindowExW(extended, CLASS_NAME, widget->config.name.c_str(), style, widget->config.x, widget->config.y, width, height, nullptr, nullptr, hInstance, widget);
    ApplyWidgetTheme(widget->window, widget->config);
    widget->fullscreenWindows.clear();
    widget->fullscreenPreview = false;
    if (fullscreen) {
        for (size_t index = 1; index < selectedMonitors.size(); index++) {
            const RECT& rect = selectedMonitors[index]->rect;
            HWND additional = CreateWindowExW(extended, CLASS_NAME, widget->config.name.c_str(), WS_POPUP, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, widget);
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
    widget->calendarChild = nullptr;
    widget->calendarProc = nullptr;
    widget->calendarFont = nullptr;
    widget->dragging = false;
    widget->rendered = false;
    widget->alarmActive = false;
    widget->flashPhase = false;
    widget->lastAlarmDate = -1;
    widget->lastAlarmMinute = -1;
    widget->lastRenderKey = -1;
    widget->lastPanelDateKey = -1;
    widget->panelDateLinkRect = {};
    widget->panelDateHot = false;
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
    }
    if (widget->config.type == WIDGET_CALENDAR || widget->config.type == WIDGET_PANEL) {
        CreateCalendarChild(widget);
    }
    CreatePanelDateTooltip(widget);
    if (parentedControl && widget->config.opacity < 100) {
        SetLayeredWindowAttributes(widget->window, 0, static_cast<BYTE>(widget->config.opacity * 255 / 100), LWA_ALPHA);
    } else if (widget->config.type == WIDGET_DIGITAL && !widget->config.transparentBackground) {
        SetLayeredWindowAttributes(widget->window, 0, static_cast<BYTE>(widget->config.opacity * 255 / 100), LWA_ALPHA);
    }
    if (widget->config.visible) {
        RenderWidget(widget);
        ShowWindow(widget->window, SW_SHOWNOACTIVATE);
        RedrawWindow(widget->window, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
        if (!widget->fullscreenPreview) {
            for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
                ShowWindow(widget->fullscreenWindows[index], SW_SHOWNOACTIVATE);
                RedrawWindow(widget->fullscreenWindows[index], nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
            }
        }
        ApplyWidgetZOrder(widget);
    }
}

static void DestroyWidgetWindows() {
    for (size_t index = 0; index < blackoutWindows.size(); index++) {
        if (IsWindow(blackoutWindows[index])) {
            DestroyWindow(blackoutWindows[index]);
        }
    }
    blackoutWindows.clear();
    StopAllAlarms();
    for (size_t index = 0; index < widgets.size(); index++) {
        if (widgets[index]->copyTooltip != nullptr && IsWindow(widgets[index]->copyTooltip)) {
            DestroyWindow(widgets[index]->copyTooltip);
        }
        widgets[index]->copyTooltip = nullptr;
        if (widgets[index]->window != nullptr && IsWindow(widgets[index]->window)) {
            DestroyWindow(widgets[index]->window);
        }
        if (widgets[index]->calendarFont != nullptr) {
            DeleteObject(widgets[index]->calendarFont);
            widgets[index]->calendarFont = nullptr;
        }
        for (size_t windowIndex = 0; windowIndex < widgets[index]->fullscreenWindows.size(); windowIndex++) {
            if (IsWindow(widgets[index]->fullscreenWindows[windowIndex])) {
                DestroyWindow(widgets[index]->fullscreenWindows[windowIndex]);
            }
        }
        widgets[index]->fullscreenWindows.clear();
        widgets[index]->window = nullptr;
        widgets[index]->analogChild = nullptr;
        widgets[index]->analogProc = nullptr;
        widgets[index]->calendarChild = nullptr;
        widgets[index]->calendarProc = nullptr;
    }
}

static LRESULT CALLBACK BlackoutWindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
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
    if (message == WM_SETCURSOR) {
        SetCursor(nullptr);
        return TRUE;
    }
    return DefWindowProcW(window, message, wParam, lParam);
}

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
        if (widget->config.type != WIDGET_FULLSCREEN || !widget->config.visible || widget->fullscreenPreview || widget->window == nullptr) {
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
            HWND target = monitorIndex == 0 ? widget->window : monitorIndex - 1 < widget->fullscreenWindows.size() ? widget->fullscreenWindows[monitorIndex - 1] : nullptr;
            if (target != nullptr) {
                const RECT& rect = selected[monitorIndex]->rect;
                SetWindowPos(target, HWND_TOPMOST, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOACTIVATE | SWP_SHOWWINDOW);
            }
        }
    }
    if (blackoutRequested) {
        for (size_t monitorIndex = 0; monitorIndex < displayMonitors.size(); monitorIndex++) {
            bool occupied = std::any_of(occupiedDevices.begin(), occupiedDevices.end(), [&](const std::wstring& device) {
                return _wcsicmp(device.c_str(), displayMonitors[monitorIndex].device.c_str()) == 0;
            });
            if (occupied) {
                continue;
            }
            const RECT& rect = displayMonitors[monitorIndex].rect;
            HWND blackout = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_NOACTIVATE, BLACKOUT_CLASS_NAME, L"", WS_POPUP, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, nullptr);
            if (blackout != nullptr) {
                ShowWindow(blackout, SW_SHOWNOACTIVATE);
                SetWindowPos(blackout, HWND_TOPMOST, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOACTIVATE | SWP_SHOWWINDOW);
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
    if (hSettings != nullptr && IsWindow(hSettings)) {
        SetWindowPos(hSettings, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    } else if (escapeTarget != nullptr) {
        SetForegroundWindowEx(escapeTarget);
        SetFocus(escapeTarget);
    }
}

static void RecreateAllWidgetWindows() {
    DestroyWidgetWindows();
    for (size_t index = 0; index < widgets.size(); index++) {
        CreateWidgetWindow(widgets[index].get());
    }
    RefreshFullscreenPresentation();
}

static Widget* FindWidgetById(int id) {
    for (size_t index = 0; index < widgets.size(); index++) {
        if (widgets[index]->config.id == id) {
            return widgets[index].get();
        }
    }
    return nullptr;
}

static void RememberHiddenWidgets(const std::vector<int>& widgetIds) {
    if (!widgetIds.empty()) {
        lastHiddenWidgetIds = widgetIds;
    }
}

static void SetWidgetVisible(Widget* widget, bool visible) {
    if (widget == nullptr) {
        return;
    }
    if (widget->config.visible && !visible) {
        RememberHiddenWidgets({ widget->config.id });
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
        ApplyWidgetZOrder(widget);
    } else {
        SaveWidgetPosition(widget);
        ShowWindow(widget->window, SW_HIDE);
        for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
            ShowWindow(widget->fullscreenWindows[index], SW_HIDE);
        }
    }
    RefreshFullscreenPresentation();
    SynchronizeOpenSettings(widget);
    SaveAllSettings();
}

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
        SynchronizeOpenSettings(widgets[index].get());
    }
    RefreshFullscreenPresentation();
    SaveAllSettings();
}

static void ArrangeVisibleWidgets(Widget* anchor) {
    if (anchor != nullptr && (anchor->window == nullptr || !anchor->config.visible || anchor->config.type == WIDGET_FULLSCREEN)) {
        return;
    }
    struct MonitorGroup {
        HMONITOR monitor;
        std::vector<Widget*> items;
    };
    std::vector<MonitorGroup> groups;
    HMONITOR anchorMonitor = anchor == nullptr ? nullptr : MonitorFromWindow(anchor->window, MONITOR_DEFAULTTONEAREST);
    for (size_t index = 0; index < widgets.size(); index++) {
        Widget* current = widgets[index].get();
        if (!current->config.visible || current->window == nullptr || current->config.type == WIDGET_FULLSCREEN) {
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
            groups.push_back({ monitor, {} });
        }
        groups[groupIndex].items.push_back(current);
    }
    if (groups.empty()) {
        return;
    }
    struct PendingPlacement {
        Widget* widget;
        RECT rect;
    };
    std::vector<PendingPlacement> pending;
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
            placements.push_back({ current->config.id, rect });
        }
        if (failed || !ArrangeWidgetPlacements(&placements, monitorInformation.rcWork, anchor == nullptr ? -1 : anchor->config.id)) {
            failed = true;
            break;
        }
        for (size_t index = 0; index < placements.size(); index++) {
            pending.push_back({ groups[groupIndex].items[index], placements[index].rect });
        }
    }
    if (failed) {
        return;
    }
    for (size_t index = 0; index < pending.size(); index++) {
        Widget* current = pending[index].widget;
        current->config.x = pending[index].rect.left;
        current->config.y = pending[index].rect.top;
        SetWindowPos(current->window, nullptr, current->config.x, current->config.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
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
        SynchronizeOpenSettings(widget);
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

static void ToggleAllFromTray() {
    bool anyVisible = std::any_of(widgets.begin(), widgets.end(), [](const std::unique_ptr<Widget>& widget) {
        return widget->config.visible;
    });
    if (anyVisible) {
        SetAllVisible(false);
        return;
    }
    RestoreLastHiddenWidgets();
}

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

static void RemoveTrayIcon() {
    if (trayIcon.cbSize != 0) {
        Shell_NotifyIconW(NIM_DELETE, &trayIcon);
    }
    trayIcon = {};
    trayUsesVersion4 = false;
}

static void UpdateTrayIcon() {
    if (trayIcon.cbSize == 0) {
        return;
    }
    trayIcon.uFlags = NIF_TIP | NIF_SHOWTIP;
    wcscpy_s(trayIcon.szTip, T(TXT_APP));
    Shell_NotifyIconW(NIM_MODIFY, &trayIcon);
}

static void HandleWidgetMenuCommand(Widget* widget, int command) {
    if (widget == nullptr) {
        return;
    }
    bool recreate = false;
    if (command == ID_MENU_VISIBLE) {
        SetWidgetVisible(widget, !widget->config.visible);
    } else if (command == ID_MENU_TOPMOST) {
        widget->config.topMost = !widget->config.topMost;
        ApplyWidgetZOrder(widget);
        SynchronizeOpenSettings(widget);
        SaveAllSettings();
    } else if (command == ID_MENU_SECONDS) {
        if (widget->config.type == WIDGET_ANALOG && !AnalogClockSupportsSeconds(widget->config.size)) {
            return;
        }
        bool previousShowSeconds = widget->config.showSeconds;
        widget->config.showSeconds = !widget->config.showSeconds;
        if ((widget->config.type == WIDGET_ANALOG || widget->config.type == WIDGET_PANEL) && !UpdateAnalogSeconds(widget)) {
            widget->config.showSeconds = previousShowSeconds;
            return;
        }
        if (widget->config.type == WIDGET_DIGITAL) {
            int width = 0;
            int height = 0;
            GetWidgetDimensions(widget->config, &width, &height);
            SetWindowPos(widget->window, nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
        }
    } else if (command == ID_MENU_STOP_ALARM) {
        StopWidgetAlarm(widget);
    } else if (command >= ID_MENU_SIZE_104 && command <= ID_MENU_SIZE_198) {
        int sizes[4] = {};
        int sizeCount = GetAnalogClockSizes(sizes);
        const int fonts[] = { 28, 44, 58, 72 };
        int sizeIndex = command - ID_MENU_SIZE_104;
        if (sizeIndex >= sizeCount) {
            return;
        }
        widget->config.size = sizes[sizeIndex];
        if (widget->config.type == WIDGET_DIGITAL) {
            widget->config.fontSize = fonts[sizeIndex];
        }
        recreate = true;
    } else if (command >= ID_MENU_DATE_FORMAT_BASE && command < ID_MENU_DATE_FORMAT_BASE + DATE_FORMAT_COUNT) {
        widget->config.dateCopyFormat = command - ID_MENU_DATE_FORMAT_BASE;
        SynchronizeOpenSettings(widget);
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
        if (widget->window != nullptr) {
            DestroyWindow(widget->window);
        }
        for (size_t windowIndex = 0; windowIndex < widget->fullscreenWindows.size(); windowIndex++) {
            DestroyWindow(widget->fullscreenWindows[windowIndex]);
        }
        widget->fullscreenWindows.clear();
        widget->window = nullptr;
        widget->analogChild = nullptr;
        CreateWidgetWindow(widget);
        RefreshFullscreenPresentation();
        SynchronizeOpenSettings(widget);
        SaveAllSettings();
    } else if (command == ID_MENU_SECONDS) {
        RenderWidget(widget);
        SynchronizeOpenSettings(widget);
        SaveAllSettings();
    }
}

static void ShowWidgetContextMenu(Widget* widget, HWND owner) {
    HMENU menu = CreatePopupMenu();
    std::vector<wchar_t> menuMnemonics;
    AppendMenuCommand(menu, MF_STRING, ID_MENU_VISIBLE, widget->config.visible ? HIDE_WIDGET_LABELS[widget->config.language] : SHOW_WIDGET_LABELS[widget->config.language], &menuMnemonics);
    if (widget->config.type != WIDGET_FULLSCREEN) {
        AppendMenuCommand(menu, MF_STRING | (widget->config.topMost ? MF_CHECKED : 0), ID_MENU_TOPMOST, WT(widget, TXT_TOPMOST), &menuMnemonics);
    }
    if (widget->config.type != WIDGET_CALENDAR) {
        bool secondsAvailable = widget->config.type != WIDGET_ANALOG || AnalogClockSupportsSeconds(widget->config.size);
        UINT secondsFlags = MF_STRING | (widget->config.showSeconds && secondsAvailable ? MF_CHECKED : 0);
        if (!secondsAvailable) {
            secondsFlags |= MF_GRAYED;
        }
        AppendMenuCommand(menu, secondsFlags, ID_MENU_SECONDS, WT(widget, TXT_SECONDS), &menuMnemonics);
    }
    if (widget->config.type == WIDGET_ANALOG || widget->config.type == WIDGET_PANEL) {
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        int sizes[4] = {};
        int sizeCount = GetAnalogClockSizes(sizes);
        for (int index = 0; index < sizeCount; index++) {
            std::wstring label = WT(widget, TXT_SIZE);
            label += L" ";
            label += std::to_wstring(sizes[index]);
            AppendMenuCommand(menu, MF_STRING | (widget->config.size == sizes[index] ? MF_CHECKED : 0), ID_MENU_SIZE_104 + index, label.c_str(), &menuMnemonics);
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
            AppendMenuCommand(dateMenu, MF_STRING | (widget->config.dateCopyFormat == index ? MF_CHECKED : 0), ID_MENU_DATE_FORMAT_BASE + index, label.c_str(), &dateMenuMnemonics);
        }
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        AppendMenuCommand(menu, MF_POPUP, reinterpret_cast<UINT_PTR>(dateMenu), DATE_COPY_LABELS[widget->config.language], &menuMnemonics);
    }
    if (widget->alarmActive) {
        AppendMenuCommand(menu, MF_STRING, ID_MENU_STOP_ALARM, WT(widget, TXT_STOP_ALARM), &menuMnemonics);
    }
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendMenuCommand(menu, MF_STRING, ID_MENU_ARRANGE_WIDGETS, ARRANGE_WIDGET_LABELS[widget->config.language], &menuMnemonics);
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

static void ShowTrayContextMenu() {
    HMENU menu = CreatePopupMenu();
    std::vector<wchar_t> menuMnemonics;
    for (size_t index = 0; index < widgets.size(); index++) {
        std::wstring label = std::to_wstring(index + 1) + L". " + widgets[index]->config.name;
        AppendMenuW(menu, MF_STRING | (widgets[index]->config.visible ? MF_CHECKED : 0), ID_MENU_WIDGET_BASE + static_cast<UINT>(index), label.c_str());
    }
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendMenuCommand(menu, MF_STRING, ID_MENU_SHOW_ALL, T(TXT_SHOW_ALL), &menuMnemonics);
    AppendMenuCommand(menu, MF_STRING, ID_MENU_HIDE_ALL, T(TXT_HIDE_ALL), &menuMnemonics);
    AppendMenuCommand(menu, MF_STRING, ID_MENU_ARRANGE_WIDGETS, ARRANGE_WIDGET_LABELS[appLanguage], &menuMnemonics);
    bool activeAlarm = false;
    for (size_t index = 0; index < widgets.size(); index++) {
        activeAlarm = activeAlarm || widgets[index]->alarmActive;
    }
    if (activeAlarm) {
        AppendMenuCommand(menu, MF_STRING, ID_MENU_STOP_ALARM, T(TXT_STOP_ALARM), &menuMnemonics);
    }
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendApplicationMenuCommands(menu, appLanguage, &menuMnemonics);
    POINT point = {};
    GetCursorPos(&point);
    SetForegroundWindow(hController);
    int command = TrackPopupMenu(menu, TPM_RETURNCMD | TPM_RIGHTBUTTON, point.x, point.y, 0, hController, nullptr);
    DestroyMenu(menu);
    if (command >= ID_MENU_WIDGET_BASE && command < ID_MENU_WIDGET_BASE + static_cast<int>(widgets.size())) {
        SetWidgetVisible(widgets[command - ID_MENU_WIDGET_BASE].get(), !widgets[command - ID_MENU_WIDGET_BASE]->config.visible);
    } else {
        SendMessageW(hController, WM_COMMAND, command, 0);
    }
}

static std::wstring Mnemonic(TextId id) {
    return std::wstring(L"&") + T(id);
}

static HWND AddUnderlayStatic(HWND parent, const wchar_t* text, DWORD style, int x, int y, int height, std::vector<HWND>* group = nullptr) {
    HWND control = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", text, WS_CHILD | WS_CLIPSIBLINGS | style | SS_LEFTNOWORDWRAP, x, y, SETTINGS_UNBOUNDED_LABEL_WIDTH, height, parent, nullptr, hInstance, nullptr);
    if (control != nullptr) {
        settingsUnderlayLabels.push_back(control);
    }
    if (group != nullptr) {
        group->push_back(control);
    }
    return control;
}

static HWND AddStatic(HWND parent, TextId id, int x, int y, int height, std::vector<HWND>* group = nullptr) {
    std::wstring text = Mnemonic(id);
    return AddUnderlayStatic(parent, text.c_str(), WS_VISIBLE, x, y, height, group);
}

static HWND AddControl(DWORD extended, const wchar_t* className, const wchar_t* text, DWORD style, int x, int y, int width, int height, HWND parent, int id, std::vector<HWND>* group = nullptr) {
    HWND control = CreateWindowExW(extended, className, text, WS_CHILD | WS_VISIBLE | style, x, y, width, height, parent, reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)), hInstance, nullptr);
    if (control != nullptr && _wcsicmp(className, L"EDIT") == 0) {
        SetWindowSubclass(control, EditSubclassProc, static_cast<UINT_PTR>(id), 0);
    } else if (control != nullptr && (id == ID_LIST_WIDGETS || id == ID_MONITOR_LIST)) {
        SetWindowSubclass(control, WidgetListSubclassProc, static_cast<UINT_PTR>(id), 0);
    }
    if (group != nullptr) {
        group->push_back(control);
    }
    return control;
}

static int ScaleSettingsHorizontal(int value) {
    return MulDiv(value, SETTINGS_HORIZONTAL_SCALE_NUMERATOR, SETTINGS_HORIZONTAL_SCALE_DENOMINATOR);
}

static void GetSettingsWindowLayout(DWORD extendedStyle, DWORD* style, int* width, int* height) {
    const DWORD baseStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
    int desiredWidth = ScaleSettingsHorizontal(SETTINGS_WINDOW_WIDTH);
    int desiredHeight = SETTINGS_WINDOW_HEIGHT;
    RECT frame = {};
    AdjustWindowRectEx(&frame, baseStyle, FALSE, extendedStyle);
    settingsContentWidth = desiredWidth - (frame.right - frame.left);
    settingsContentHeight = desiredHeight - (frame.bottom - frame.top);
    RECT desired = { settingsX, settingsY, settingsX + desiredWidth, settingsY + desiredHeight };
    HMONITOR monitor = settingsX == CW_USEDEFAULT || settingsY == CW_USEDEFAULT ?
        MonitorFromPoint(POINT{}, MONITOR_DEFAULTTOPRIMARY) : MonitorFromRect(&desired, MONITOR_DEFAULTTONEAREST);
    MONITORINFO information = {};
    information.cbSize = sizeof(information);
    RECT workArea = { 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
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
    *style = baseStyle | (horizontalScroll ? WS_HSCROLL : 0) | (verticalScroll ? WS_VSCROLL : 0);
}

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
    ScrollWindowEx(hSettings, deltaX, deltaY, nullptr, nullptr, nullptr, nullptr, SW_SCROLLCHILDREN | SW_INVALIDATE | SW_ERASE);
    UpdateWindow(hSettings);
    return true;
}

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
            SetWindowPos(child, nullptr, ScaleSettingsHorizontal(rect.left), rect.top, ScaleSettingsHorizontal(rect.right - rect.left), rect.bottom - rect.top, SWP_NOZORDER | SWP_NOACTIVATE);
        }
        child = next;
    }
}

static void SetSettingsControlPosition(HWND control, int x, int y, int width, int height) {
    if (control == nullptr) {
        return;
    }
    SetWindowPos(control, nullptr, ScaleSettingsHorizontal(x), y, ScaleSettingsHorizontal(width), height, SWP_NOZORDER | SWP_NOACTIVATE);
}

static void ResetEditClicks() {
    if (lastClickedEdit != nullptr) {
        KillTimer(lastClickedEdit, TIMER_EDIT_CLICKS);
    }
    lastClickedEdit = nullptr;
    lastEditClickPoint = {};
    editClickCount = 0;
}

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

static LRESULT CALLBACK EditSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR subclassId, DWORD_PTR referenceData) {
    UNREFERENCED_PARAMETER(referenceData);
    if (message == WM_TIMER && wParam == TIMER_EDIT_CLICKS) {
        KillTimer(window, TIMER_EDIT_CLICKS);
        if (lastClickedEdit == window) {
            ResetEditClicks();
        }
        return 0;
    }
    if (message == WM_RBUTTONDOWN || message == WM_RBUTTONDBLCLK || message == WM_MBUTTONDOWN || message == WM_MBUTTONDBLCLK ||
        message == WM_XBUTTONDOWN || message == WM_XBUTTONDBLCLK || message == WM_KILLFOCUS && lastClickedEdit == window) {
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
        SendMessageW(window, EM_GETSEL, reinterpret_cast<WPARAM>(&selectionStart), reinterpret_cast<LPARAM>(&selectionEnd));
        POINT clickPoint = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
        if (selectionEnd > selectionStart) {
            editClickCount = 2;
        } else if (editClickCount == 0 || abs(clickPoint.x - lastEditClickPoint.x) < 2 && abs(clickPoint.y - lastEditClickPoint.y) < 2) {
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

static LRESULT CALLBACK WidgetListSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR subclassId, DWORD_PTR referenceData) {
    UNREFERENCED_PARAMETER(referenceData);
    if (message == WM_KEYDOWN && wParam == L'A' && (GetKeyState(VK_CONTROL) & 0x8000) != 0) {
        SendMessageW(window, LB_SETSEL, TRUE, -1);
        SendMessageW(GetParent(window), WM_COMMAND, MAKEWPARAM(static_cast<int>(subclassId), LBN_SELCHANGE), reinterpret_cast<LPARAM>(window));
        return 0;
    }
    if (message == WM_KEYDOWN && wParam == VK_DELETE && subclassId == ID_LIST_WIDGETS) {
        SendMessageW(GetParent(window), WM_COMMAND, MAKEWPARAM(ID_REMOVE, BN_CLICKED), 0);
        return 0;
    }
    if (message == WM_NCDESTROY) {
        RemoveWindowSubclass(window, WidgetListSubclassProc, subclassId);
    }
    return DefSubclassProc(window, message, wParam, lParam);
}

static void SetCheck(HWND control, bool checked) {
    SendMessageW(control, BM_SETCHECK, checked ? BST_CHECKED : BST_UNCHECKED, 0);
}

static bool GetCheck(HWND control) {
    return SendMessageW(control, BM_GETCHECK, 0, 0) == BST_CHECKED;
}

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

static std::wstring GetControlText(HWND control) {
    int length = GetWindowTextLengthW(control);
    std::vector<wchar_t> text(length + 1, 0);
    GetWindowTextW(control, text.data(), static_cast<int>(text.size()));
    return text.data();
}

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
                RECT lineRect = { bounds.left, y, bounds.right, std::min(static_cast<LONG>(y + lineHeight), bounds.bottom) };
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
            RECT lineRect = { bounds.left, y, bounds.right, std::min(static_cast<LONG>(y + lineHeight), bounds.bottom) };
            DrawTextW(dc, line.c_str(), -1, &lineRect, DT_LEFT | DT_TOP | DT_SINGLELINE | DT_NOPREFIX);
            y += lineHeight;
            line = word;
        } else {
            line = candidate;
        }
    }
    if (!line.empty() && y < bounds.bottom) {
        RECT lineRect = { bounds.left, y, bounds.right, std::min(static_cast<LONG>(y + lineHeight), bounds.bottom) };
        DrawTextW(dc, line.c_str(), -1, &lineRect, DT_LEFT | DT_TOP | DT_SINGLELINE | DT_NOPREFIX);
    }
}

static void AssignSettingsMnemonicsToChildren(HWND parent, std::vector<wchar_t>* usedMnemonics) {
    for (HWND control = GetWindow(parent, GW_CHILD); control != nullptr; control = GetWindow(control, GW_HWNDNEXT)) {
        if (!IsWindowVisible(control)) {
            continue;
        }
        wchar_t className[32] = {};
        GetClassNameW(control, className, ARRAYSIZE(className));
        LONG_PTR style = GetWindowLongPtrW(control, GWL_STYLE);
        std::wstring text = GetControlText(control);
        bool button = _wcsicmp(className, L"Button") == 0 && (style & WS_TABSTOP) != 0;
        bool label = _wcsicmp(className, L"Static") == 0 && control != hNtpStatus && text.find(L':') != std::wstring::npos;
        if (!button && !label) {
            continue;
        }
        std::wstring caption = UniqueMnemonic(text.c_str(), usedMnemonics);
        if (caption != text) {
            SetWindowTextW(control, caption.c_str());
        }
    }
}

static void AssignSettingsMnemonics() {
    if (hSettings == nullptr || !IsWindow(hSettings)) {
        return;
    }
    int tab = hTabs == nullptr ? 0 : TabCtrl_GetCurSel(hTabs);
    HWND activePage = tab == 0 ? hGeneralPage
        : tab == 1 ? hAppearancePage : tab == 2 ? hAlarmPage : tab == 3 ? hTimeSignalPage : hTimePage;
    std::vector<wchar_t> usedMnemonics;
    if (activePage != nullptr && IsWindowVisible(activePage)) {
        AssignSettingsMnemonicsToChildren(activePage, &usedMnemonics);
    }
    AssignSettingsMnemonicsToChildren(hSettings, &usedMnemonics);
}

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
    SetWindowTextW(hNtpServersEdit, servers.c_str());
    updatingNtpPresetControls = false;
}

static void UpdateNtpSettingsControls() {
    if (hTimeSourceCombo == nullptr || hNtpPresetCombo == nullptr || hNtpServersEdit == nullptr) {
        return;
    }
    int source = static_cast<int>(SendMessageW(hTimeSourceCombo, CB_GETCURSEL, 0, 0));
    bool ntpSelected = source == 1;
    int selectedPreset = static_cast<int>(SendMessageW(hNtpPresetCombo, CB_GETCURSEL, 0, 0));
    bool settingsApplied = ntpSelected == useNtpTime && selectedPreset == ntpPreset && GetControlText(hNtpServersEdit) == ntpServers;
    EnableWindow(hNtpPresetLabel, ntpSelected);
    EnableWindow(hNtpPresetCombo, ntpSelected);
    EnableWindow(hNtpServersLabel, ntpSelected);
    EnableWindow(hNtpServersEdit, ntpSelected);
    EnableWindow(hNtpSyncButton, ntpSelected && winsockReady && settingsApplied);
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
    SetWindowTextW(hNtpStatus, status.c_str());
}

static void ShowSettingsTab(int tab) {
    if (hGeneralPage != nullptr) {
        ShowWindow(hGeneralPage, tab == 0 ? SW_SHOW : SW_HIDE);
    }
    if (hAppearancePage != nullptr) {
        ShowWindow(hAppearancePage, tab == 1 ? SW_SHOW : SW_HIDE);
    }
    if (hAlarmPage != nullptr) {
        ShowWindow(hAlarmPage, tab == 2 ? SW_SHOW : SW_HIDE);
    }
    if (hTimeSignalPage != nullptr) {
        ShowWindow(hTimeSignalPage, tab == 3 ? SW_SHOW : SW_HIDE);
    }
    if (hTimePage != nullptr) {
        ShowWindow(hTimePage, tab == 4 ? SW_SHOW : SW_HIDE);
    }
    HWND activePage = tab == 0 ? hGeneralPage
        : tab == 1 ? hAppearancePage : tab == 2 ? hAlarmPage : tab == 3 ? hTimeSignalPage : hTimePage;
    if (activePage != nullptr) {
        SetWindowPos(activePage, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        RedrawWindow(activePage, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN | RDW_UPDATENOW);
    }
    if (selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
        bool calendar = settingsDraft[selectedDraftIndex].type == WIDGET_CALENDAR;
        bool singleSelection = hWidgetList != nullptr && SendMessageW(hWidgetList, LB_GETSELCOUNT, 0, 0) == 1;
        if (tab == 2 && (!singleSelection || calendar)) {
            for (size_t index = 0; index < alarmControls.size(); index++) {
                EnableWindow(alarmControls[index], FALSE);
            }
        }
    }
    AssignSettingsMnemonics();
}

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
    int copied = static_cast<int>(SendMessageW(hWidgetList, LB_GETSELITEMS, count, reinterpret_cast<LPARAM>(selected.data())));
    if (copied < 0) {
        selected.clear();
    } else {
        selected.resize(copied);
    }
    return selected;
}

static void UpdateSettingsSelectionState() {
    bool singleSelection = GetSelectedWidgetIndices().size() == 1;
    if (hTabs != nullptr) {
        EnableWindow(hTabs, TRUE);
    }
    if (hGeneralPage != nullptr) {
        EnableWindow(hGeneralPage, TRUE);
    }
    if (hAppearancePage != nullptr) {
        EnableWindow(hAppearancePage, TRUE);
    }
    if (hAlarmPage != nullptr) {
        EnableWindow(hAlarmPage, TRUE);
    }
    if (hTimeSignalPage != nullptr) {
        EnableWindow(hTimeSignalPage, TRUE);
    }
    for (size_t index = 0; index < generalControls.size(); index++) {
        EnableWindow(generalControls[index], singleSelection);
    }
    for (size_t index = 0; index < appearanceControls.size(); index++) {
        EnableWindow(appearanceControls[index], singleSelection);
    }
    for (size_t index = 0; index < alarmControls.size(); index++) {
        EnableWindow(alarmControls[index], singleSelection);
    }
    for (size_t index = 0; index < timeSignalControls.size(); index++) {
        EnableWindow(timeSignalControls[index], singleSelection);
    }
    if (!singleSelection) {
        return;
    }
    UpdateSettingControlAvailability();
    int selectedTab = hTabs == nullptr ? 0 : TabCtrl_GetCurSel(hTabs);
    if (selectedTab == 2 && selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size()) &&
        settingsDraft[selectedDraftIndex].type == WIDGET_CALENDAR) {
        for (size_t index = 0; index < alarmControls.size(); index++) {
            EnableWindow(alarmControls[index], FALSE);
        }
    }
}

static void SelectOnlyWidgetIndex(int index) {
    if (hWidgetList == nullptr || !IsWindow(hWidgetList)) {
        return;
    }
    SendMessageW(hWidgetList, LB_SETSEL, FALSE, -1);
    if (index >= 0 && index < static_cast<int>(settingsDraft.size())) {
        SendMessageW(hWidgetList, LB_SETSEL, TRUE, index);
        SendMessageW(hWidgetList, LB_SETCARETINDEX, index, FALSE);
    }
    UpdateSettingsSelectionState();
}

static void RefreshWidgetList(bool preserveSelection = true) {
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
    UpdateSettingsSelectionState();
}

static void SelectTimeZoneInCombo(const std::wstring& key) {
    int selected = 0;
    int count = static_cast<int>(SendMessageW(hTimeZoneCombo, CB_GETCOUNT, 0, 0));
    for (int index = 0; index < count; index++) {
        size_t zoneIndex = static_cast<size_t>(SendMessageW(hTimeZoneCombo, CB_GETITEMDATA, index, 0));
        if (zoneIndex < timeZones.size() && _wcsicmp(timeZones[zoneIndex].TimeZoneKeyName, key.c_str()) == 0) {
            selected = index;
            break;
        }
    }
    SendMessageW(hTimeZoneCombo, CB_SETCURSEL, selected, 0);
}

static void LoadMonitorSelection(const WidgetConfig& config) {
    if (hMonitorList == nullptr) {
        return;
    }
    RefreshDisplayMonitors();
    SendMessageW(hMonitorList, LB_RESETCONTENT, 0, 0);
    bool anySelected = false;
    for (size_t index = 0; index < displayMonitors.size(); index++) {
        int width = displayMonitors[index].rect.right - displayMonitors[index].rect.left;
        int height = displayMonitors[index].rect.bottom - displayMonitors[index].rect.top;
        std::wstring label = std::to_wstring(index + 1) + L"  (" + std::to_wstring(width) + L" × " + std::to_wstring(height) + L")";
        int item = static_cast<int>(SendMessageW(hMonitorList, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(label.c_str())));
        SendMessageW(hMonitorList, LB_SETITEMDATA, item, index);
        if (ContainsMonitorDevice(config.monitorDevices, displayMonitors[index].device)) {
            SendMessageW(hMonitorList, LB_SETSEL, TRUE, item);
            anySelected = true;
        }
    }
    if (!anySelected && !displayMonitors.empty()) {
        SendMessageW(hMonitorList, LB_SETSEL, TRUE, 0);
    }
}

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

static void SetSliderValueText(HWND label, int value, const wchar_t* suffix) {
    if (label == nullptr) {
        return;
    }
    wchar_t text[32] = {};
    swprintf_s(text, L"%d%s", value, suffix);
    if (GetControlText(label) == text) {
        return;
    }
    SetWindowTextW(label, text);
    RedrawWindow(label, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
}

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
        bool fullscreen = selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size()) && settingsDraft[selectedDraftIndex].type == WIDGET_FULLSCREEN;
        SetSliderValueText(hFontSizeValue, fontSize, fullscreen ? L" %" : L" pt");
    }
    if (changedTrackBar == nullptr || changedTrackBar == hPaddingTrackBar) {
        SetSliderValueText(hPaddingValue, padding, L" px");
    }
    if (changedTrackBar == nullptr || changedTrackBar == hBorderWidthTrackBar) {
        SetSliderValueText(hBorderWidthValue, borderWidth, L" px");
    }
    if (changedTrackBar == hFontSizeTrackBar && selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
        WidgetConfig preview = settingsDraft[selectedDraftIndex];
        preview.fontSize = fontSize;
        UpdateFontDescription(preview);
    }
}

static bool SaveAppearanceControlsToDraft() {
    if (selectedDraftIndex < 0 || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
        return false;
    }
    WidgetConfig& config = settingsDraft[selectedDraftIndex];
    int sizes[4] = {};
    int sizeCount = GetAnalogClockSizes(sizes);
    int sizeIndex = static_cast<int>(SendMessageW(hSizeCombo, CB_GETCURSEL, 0, 0));
    if (sizeIndex >= 0 && sizeIndex < sizeCount) {
        config.size = sizes[sizeIndex];
    }
    config.opacity = std::clamp(static_cast<int>(SendMessageW(hOpacityTrackBar, TBM_GETPOS, 0, 0)), WIDGET_OPACITY_MIN, WIDGET_OPACITY_MAX);
    int minimumFontSize = config.type == WIDGET_FULLSCREEN ? FULLSCREEN_FONT_SIZE_MIN : DIGITAL_FONT_SIZE_MIN;
    int maximumFontSize = config.type == WIDGET_FULLSCREEN ? FULLSCREEN_FONT_SIZE_MAX : DIGITAL_FONT_SIZE_MAX;
    config.fontSize = std::clamp(static_cast<int>(SendMessageW(hFontSizeTrackBar, TBM_GETPOS, 0, 0)), minimumFontSize, maximumFontSize);
    if (config.type == WIDGET_DIGITAL) {
        config.fontDialogSize = config.fontSize * 10;
    }
    config.fontAntialiasing = std::clamp(static_cast<int>(SendMessageW(hWidgetAntialiasCombo, CB_GETCURSEL, 0, 0)), 0, FONT_ANTIALIAS_COUNT - 1);
    int maximumPadding = config.type == WIDGET_FULLSCREEN ? FULLSCREEN_PADDING_MAX : DIGITAL_PADDING_MAX;
    config.padding = std::clamp(static_cast<int>(SendMessageW(hPaddingTrackBar, TBM_GETPOS, 0, 0)), 0, maximumPadding);
    config.borderStyle = std::clamp(static_cast<int>(SendMessageW(hBorderTrackBar, TBM_GETPOS, 0, 0)), 0, DIGITAL_BORDER_STYLE_COUNT - 1);
    config.borderWidth = std::clamp(static_cast<int>(SendMessageW(hBorderWidthTrackBar, TBM_GETPOS, 0, 0)), 0, DIGITAL_BORDER_WIDTH_MAX);
    config.showFrame = GetCheck(hShowFrameCheck);
    config.leadingZero = GetCheck(hLeadingZeroCheck);
    config.transparentBackground = GetCheck(hTransparentBackgroundCheck);
    config.disableThemes = GetCheck(hWidgetDisableThemesCheck);
    config.textColor = static_cast<COLORREF>(GetWindowLongPtrW(hTextColorButton, GWLP_USERDATA));
    config.backgroundColor = static_cast<COLORREF>(GetWindowLongPtrW(hBackgroundColorButton, GWLP_USERDATA));
    config.alarmTextColor = static_cast<COLORREF>(GetWindowLongPtrW(hAlarmTextColorButton, GWLP_USERDATA));
    config.alarmBackgroundColor = static_cast<COLORREF>(GetWindowLongPtrW(hAlarmBackgroundColorButton, GWLP_USERDATA));
    config.weekNumbers = GetCheck(hWeekNumbersCheck);
    config.sundayFirst = GetCheck(hSundayFirstCheck);
    int dateFormat = static_cast<int>(SendMessageW(hDateFormatCombo, CB_GETCURSEL, 0, 0));
    if (dateFormat >= 0 && dateFormat < DATE_FORMAT_COUNT) {
        config.dateCopyFormat = dateFormat;
    }
    return true;
}

static void UpdateSettingControlAvailability() {
    if (selectedDraftIndex < 0 || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
        return;
    }
    WidgetType type = settingsDraft[selectedDraftIndex].type;
    bool fullscreen = type == WIDGET_FULLSCREEN;
    bool digital = type == WIDGET_DIGITAL || fullscreen;
    bool calendar = type == WIDGET_CALENDAR || type == WIDGET_PANEL;
    bool panel = type == WIDGET_PANEL;
    bool utc = GetCheck(hUtcCheck);
    bool hasSize = type == WIDGET_ANALOG || type == WIDGET_PANEL;
    bool hasTextFont = digital || calendar;
    bool globalThemesDisabled = hDisableThemesCheck == nullptr ? themesDisabled : GetCheck(hDisableThemesCheck);
    bool widgetThemesDisabled = hWidgetDisableThemesCheck == nullptr ? settingsDraft[selectedDraftIndex].disableThemes : GetCheck(hWidgetDisableThemesCheck);
    bool calendarFontEnabled = globalThemesDisabled || widgetThemesDisabled;
    bool supportsAlarm = type != WIDGET_CALENDAR;
    int selectedSize = GetSelectedAnalogClockSize(settingsDraft[selectedDraftIndex].size);
    bool supportsSeconds = type != WIDGET_CALENDAR && (type != WIDGET_ANALOG || AnalogClockSupportsSeconds(selectedSize));
    SetCheck(hSecondsCheck, settingsDraft[selectedDraftIndex].showSeconds && supportsSeconds);
    if (hAppearancePage != nullptr) {
        SendMessageW(hAppearancePage, WM_SETREDRAW, FALSE, 0);
    }
    if (fullscreen) {
        SetCheck(hTopmostCheck, true);
    }
    int minimumFontSize = fullscreen ? FULLSCREEN_FONT_SIZE_MIN : DIGITAL_FONT_SIZE_MIN;
    int maximumFontSize = fullscreen ? FULLSCREEN_FONT_SIZE_MAX : DIGITAL_FONT_SIZE_MAX;
    SendMessageW(hFontSizeTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(minimumFontSize, maximumFontSize));
    int currentFontSize = static_cast<int>(SendMessageW(hFontSizeTrackBar, TBM_GETPOS, 0, 0));
    SendMessageW(hFontSizeTrackBar, TBM_SETPOS, TRUE, std::clamp(currentFontSize, minimumFontSize, maximumFontSize));
    int maximumPadding = fullscreen ? FULLSCREEN_PADDING_MAX : DIGITAL_PADDING_MAX;
    SendMessageW(hPaddingTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(0, maximumPadding));
    int currentPadding = static_cast<int>(SendMessageW(hPaddingTrackBar, TBM_GETPOS, 0, 0));
    SendMessageW(hPaddingTrackBar, TBM_SETPOS, TRUE, std::clamp(currentPadding, 0, maximumPadding));
    UpdateAppearanceSliderLabels();
    int opacityTop = hasSize ? 38 : 4;
    SetSettingsControlPosition(hOpacityLabel, 8, opacityTop + 7, SETTINGS_UNBOUNDED_LABEL_WIDTH, 22);
    SetSettingsControlPosition(hOpacityTrackBar, 121, opacityTop, 250, 32);
    SetSettingsControlPosition(hOpacityValue, 368, opacityTop + 7, 48, 22);
    if (hasTextFont) {
        int fontX = panel ? 194 : 8;
        int fontY = digital ? 70 : panel ? 106 : 76;
        SetSettingsControlPosition(hFontButton, fontX, fontY, 178, 27);
    }
    if (panel) {
        SetSettingsControlPosition(hPanelTopFontButton, 8, 76, 178, 27);
        SetSettingsControlPosition(hPanelTimeFontButton, 194, 76, 178, 27);
        SetSettingsControlPosition(hPanelBottomFontButton, 8, 106, 178, 27);
        SetSettingsControlPosition(hLeadingZeroCheck, 8, 270, 178, 24);
    } else if (digital) {
        SetSettingsControlPosition(hLeadingZeroCheck, 8, 286, 130, 24);
    }
    int defaultAppearanceX = 194;
    int defaultAppearanceY = digital ? 70 : panel ? 240 : calendar ? 76 : 110;
    SetSettingsControlPosition(hDefaultAppearanceButton, defaultAppearanceX, defaultAppearanceY, 178, 27);
    if (digital) {
        SetSettingsControlPosition(hBackgroundColorButton, 194, 100, 178, 27);
    }
    if (calendar) {
        int calendarTop = panel ? 140 : 110;
        SetSettingsControlPosition(hWeekNumbersCheck, 8, calendarTop, 150, 24);
        SetSettingsControlPosition(hSundayFirstCheck, 165, calendarTop, 205, 24);
        SetSettingsControlPosition(hDateFormatLabel, 8, calendarTop + 34, SETTINGS_UNBOUNDED_LABEL_WIDTH, 22);
        SetSettingsControlPosition(hDateFormatCombo, 191, calendarTop + 30, 181, 240);
        SetSettingsControlPosition(hShowFrameCheck, 8, panel ? 240 : 208, 178, 24);
    }
    if (hWidgetDisableThemesCheck != nullptr && hWidgetAntialiasLabel != nullptr && hWidgetAntialiasCombo != nullptr) {
        int optionsTop = digital ? 258 : panel ? 208 : calendar ? 178 : 76;
        SetSettingsControlPosition(hWidgetAntialiasLabel, 8, optionsTop + 4, SETTINGS_UNBOUNDED_LABEL_WIDTH, 22);
        SetSettingsControlPosition(hWidgetAntialiasCombo, 148, optionsTop, 86, 100);
        SetSettingsControlPosition(hWidgetDisableThemesCheck, 242, optionsTop, 130, 24);
    }
    struct ControlState {
        HWND control;
        int showCommand;
        int enabled;
    };
    const int unchanged = -1;
    ControlState controlStates[] = {
        {
            hMonitorLabel,
            fullscreen ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hMonitorList,
            fullscreen ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hBlackoutMonitorsCheck,
            fullscreen ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hSizeLabel,
            hasSize ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hSizeCombo,
            hasSize ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hFontSizeLabel,
            digital ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hFontSizeTrackBar,
            digital ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hFontSizeValue,
            digital ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hFontDescription,
            digital ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hLeadingZeroCheck,
            digital || panel ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hTransparentBackgroundCheck,
            digital && !fullscreen ? SW_SHOW : SW_HIDE,
            !fullscreen
        },
        {
            hTextColorButton,
            digital ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hAlarmTextColorButton,
            digital ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hAlarmBackgroundColorButton,
            digital ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hPaddingLabel,
            digital ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hPaddingTrackBar,
            digital ? SW_SHOW : SW_HIDE,
            digital
        },
        {
            hPaddingValue,
            digital ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hBorderLabel,
            digital && !fullscreen ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hBorderTrackBar,
            digital && !fullscreen ? SW_SHOW : SW_HIDE,
            !fullscreen
        },
        {
            hBorderWidthLabel,
            digital && !fullscreen ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hBorderWidthTrackBar,
            digital && !fullscreen ? SW_SHOW : SW_HIDE,
            !fullscreen
        },
        {
            hBorderWidthValue,
            digital && !fullscreen ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hFontButton,
            hasTextFont ? SW_SHOW : SW_HIDE,
            digital || calendarFontEnabled
        },
        {
            hPanelTopFontButton,
            panel ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hPanelTimeFontButton,
            panel ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hPanelBottomFontButton,
            panel ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hDefaultAppearanceButton,
            SW_SHOW,
            unchanged
        },
        {
            hBackgroundColorButton,
            digital ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hWeekNumbersCheck,
            calendar ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hSundayFirstCheck,
            calendar ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hShowFrameCheck,
            calendar ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hDateFormatLabel,
            calendar ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hDateFormatCombo,
            calendar ? SW_SHOW : SW_HIDE,
            unchanged
        },
        {
            hSecondsCheck,
            unchanged,
            supportsSeconds
        },
        {
            hUtcTextCheck,
            unchanged,
            (digital || panel) && utc
        },
        {
            hTimeZoneLabel,
            unchanged,
            !utc
        },
        {
            hTimeZoneCombo,
            unchanged,
            !utc
        },
        {
            hTopmostCheck,
            unchanged,
            !fullscreen
        },
        {
            hOpacityTrackBar,
            unchanged,
            !fullscreen
        },
        {
            hAlarmEnabledCheck,
            unchanged,
            supportsAlarm
        },
        {
            hAlarmTimeEdit,
            unchanged,
            supportsAlarm
        },
        {
            hRunCommandCheck,
            unchanged,
            supportsAlarm
        },
        {
            hCommandEdit,
            unchanged,
            supportsAlarm
        },
        {
            hBrowseButton,
            unchanged,
            supportsAlarm
        },
        {
            hLoopAudioCheck,
            unchanged,
            supportsAlarm
        },
        {
            hTestCommandButton,
            unchanged,
            supportsAlarm
        },
        {
            hRemoteScriptCheck,
            unchanged,
            supportsAlarm
        },
        {
            hRemoteScriptLabel,
            unchanged,
            supportsAlarm && GetCheck(hRemoteScriptCheck)
        },
        {
            hRemoteScriptEdit,
            unchanged,
            supportsAlarm && GetCheck(hRemoteScriptCheck)
        }
    };
    for (const ControlState& state : controlStates) {
        if (state.control == nullptr) {
            continue;
        }
        if (state.showCommand != unchanged) {
            ShowWindow(state.control, state.showCommand);
        }
        if (state.enabled != unchanged) {
            EnableWindow(state.control, state.enabled != 0);
        }
    }
    if (hAppearancePage != nullptr) {
        SendMessageW(hAppearancePage, WM_SETREDRAW, TRUE, 0);
        RedrawWindow(hAppearancePage, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN | RDW_UPDATENOW);
    }
    AssignSettingsMnemonics();
}

static void FillDateFormatCombo(const WidgetConfig& config) {
    if (hDateFormatCombo == nullptr) {
        return;
    }
    SendMessageW(hDateFormatCombo, CB_RESETCONTENT, 0, 0);
    SendMessageW(hDateFormatCombo, CB_SETDROPPEDWIDTH, ScaleSettingsHorizontal(520), 0);
    SYSTEMTIME date = {};
    GetDisplayedTime(config, &date);
    for (int index = 0; index < DATE_FORMAT_COUNT; index++) {
        std::wstring label = DateFormatCaption(config, date, index);
        SendMessageW(hDateFormatCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(label.c_str()));
    }
    SendMessageW(hDateFormatCombo, CB_SETCURSEL, std::clamp(config.dateCopyFormat, 0, DATE_FORMAT_COUNT - 1), 0);
}

static void LoadDraftIntoControls() {
    if (selectedDraftIndex < 0 || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
        return;
    }
    const WidgetConfig& config = settingsDraft[selectedDraftIndex];
    SetWindowTextW(hNameEdit, config.name.c_str());
    SendMessageW(hTypeCombo, CB_SETCURSEL, config.type, 0);
    SetCheck(hVisibleCheck, config.visible);
    SetCheck(hTopmostCheck, config.topMost);
    SetCheck(hSecondsCheck, config.showSeconds);
    SetCheck(hUtcCheck, config.showUtc);
    SetCheck(hUtcTextCheck, config.showUtcText);
    SendMessageW(hWidgetLanguageCombo, CB_SETCURSEL, config.language, 0);
    SelectTimeZoneInCombo(config.timeZoneKey);
    LoadMonitorSelection(config);
    SetCheck(hBlackoutMonitorsCheck, config.blackoutOtherMonitors);
    SetWindowTextW(hOffsetEdit, FormatOffset(config.offsetMilliseconds).c_str());
    int sizes[4] = {};
    int sizeIndex = 1;
    int sizeCount = GetAnalogClockSizes(sizes);
    for (int index = 0; index < sizeCount; index++) {
        if (sizes[index] == config.size) {
            sizeIndex = index;
        }
    }
    SendMessageW(hSizeCombo, CB_SETCURSEL, sizeIndex, 0);
    SendMessageW(hOpacityTrackBar, TBM_SETPOS, TRUE, config.opacity);
    SendMessageW(hFontSizeTrackBar, TBM_SETPOS, TRUE, config.fontSize);
    SendMessageW(hWidgetAntialiasCombo, CB_SETCURSEL, config.fontAntialiasing, 0);
    SendMessageW(hPaddingTrackBar, TBM_SETPOS, TRUE, config.padding);
    SendMessageW(hBorderTrackBar, TBM_SETPOS, TRUE, config.borderStyle);
    SendMessageW(hBorderWidthTrackBar, TBM_SETPOS, TRUE, config.borderWidth);
    UpdateAppearanceSliderLabels();
    UpdateFontDescription(config);
    SetCheck(hLeadingZeroCheck, config.leadingZero);
    SetCheck(hTransparentBackgroundCheck, config.transparentBackground);
    SetCheck(hWidgetDisableThemesCheck, config.disableThemes);
    SetWindowLongPtrW(hTextColorButton, GWLP_USERDATA, config.textColor);
    SetWindowLongPtrW(hBackgroundColorButton, GWLP_USERDATA, config.backgroundColor);
    SetWindowLongPtrW(hAlarmTextColorButton, GWLP_USERDATA, config.alarmTextColor);
    SetWindowLongPtrW(hAlarmBackgroundColorButton, GWLP_USERDATA, config.alarmBackgroundColor);
    InvalidateRect(hTextColorButton, nullptr, TRUE);
    InvalidateRect(hBackgroundColorButton, nullptr, TRUE);
    InvalidateRect(hAlarmTextColorButton, nullptr, TRUE);
    InvalidateRect(hAlarmBackgroundColorButton, nullptr, TRUE);
    SetCheck(hWeekNumbersCheck, config.weekNumbers);
    SetCheck(hSundayFirstCheck, config.sundayFirst);
    SetCheck(hShowFrameCheck, config.showFrame);
    FillDateFormatCombo(config);
    SetCheck(hAlarmEnabledCheck, config.alarmEnabled);
    wchar_t alarm[16] = {};
    swprintf_s(alarm, L"%02d:%02d", config.alarmHour, config.alarmMinute);
    SetWindowTextW(hAlarmTimeEdit, alarm);
    SetCheck(hRunCommandCheck, config.runCommand);
    SetWindowTextW(hCommandEdit, config.command.c_str());
    SetCheck(hLoopAudioCheck, config.loopAudio);
    SetCheck(hRemoteScriptCheck, config.callRemoteScript);
    SetWindowTextW(hRemoteScriptEdit, config.remoteScriptUrl.c_str());
    SetCheck(hAlarmTimeSignalCheck, config.alarmTimeSignal);
    SendMessageW(hTimeSignalCombo, CB_SETCURSEL, config.timeSignal, 0);
    UpdateSettingControlAvailability();
}

static bool SaveControlsToDraft(bool showErrors) {
    if (selectedDraftIndex < 0 || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
        return true;
    }
    WidgetConfig& config = settingsDraft[selectedDraftIndex];
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
    config.visible = GetCheck(hVisibleCheck);
    config.topMost = GetCheck(hTopmostCheck);
    int selectedSize = GetSelectedAnalogClockSize(config.size);
    bool preserveAnalogSeconds = config.type == WIDGET_ANALOG && !AnalogClockSupportsSeconds(selectedSize);
    if (!preserveAnalogSeconds) {
        config.showSeconds = GetCheck(hSecondsCheck);
    }
    config.showUtc = GetCheck(hUtcCheck);
    config.showUtcText = GetCheck(hUtcTextCheck);
    int widgetLanguage = static_cast<int>(SendMessageW(hWidgetLanguageCombo, CB_GETCURSEL, 0, 0));
    if (widgetLanguage >= 0 && widgetLanguage < LANG_COUNT) {
        config.language = static_cast<AppLanguage>(widgetLanguage);
    }
    int zoneSelection = static_cast<int>(SendMessageW(hTimeZoneCombo, CB_GETCURSEL, 0, 0));
    if (zoneSelection != CB_ERR) {
        size_t zoneIndex = static_cast<size_t>(SendMessageW(hTimeZoneCombo, CB_GETITEMDATA, zoneSelection, 0));
        if (zoneIndex < timeZones.size()) {
            config.timeZoneKey = timeZones[zoneIndex].TimeZoneKeyName;
        }
    }
    if (config.type == WIDGET_FULLSCREEN) {
        config.monitorDevices = GetSelectedMonitorDevices();
        config.blackoutOtherMonitors = GetCheck(hBlackoutMonitorsCheck);
    }
    config.offsetMilliseconds = offset;
    SaveAppearanceControlsToDraft();
    config.alarmEnabled = GetCheck(hAlarmEnabledCheck);
    config.alarmTimeSignal = GetCheck(hAlarmTimeSignalCheck);
    config.alarmHour = hour;
    config.alarmMinute = minute;
    config.runCommand = GetCheck(hRunCommandCheck);
    config.command = GetControlText(hCommandEdit);
    config.loopAudio = GetCheck(hLoopAudioCheck);
    config.callRemoteScript = remoteScriptEnabled;
    config.remoteScriptUrl = remoteScriptUrl;
    int timeSignal = static_cast<int>(SendMessageW(hTimeSignalCombo, CB_GETCURSEL, 0, 0));
    config.timeSignal = static_cast<TimeSignalMode>(std::clamp(timeSignal, 0, TIME_SIGNAL_COUNT - 1));
    return true;
}

static void CopyWidgetAppearance(WidgetConfig* target, const WidgetConfig& source) {
    if (target == nullptr) {
        return;
    }
    target->size = source.size;
    target->opacity = source.opacity;
    target->fontSize = source.fontSize;
    target->fontDialogSize = source.fontDialogSize;
    target->fontAntialiasing = source.fontAntialiasing;
    target->leadingZero = source.leadingZero;
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
    target->showFrame = source.showFrame;
    target->textColor = source.textColor;
    target->backgroundColor = source.backgroundColor;
    target->alarmTextColor = source.alarmTextColor;
    target->alarmBackgroundColor = source.alarmBackgroundColor;
    target->weekNumbers = source.weekNumbers;
    target->sundayFirst = source.sundayFirst;
    target->dateCopyFormat = source.dateCopyFormat;
}

static bool FontSelectionsEqual(const FontSelection& left, const FontSelection& right) {
    return left.face == right.face
        && left.dialogSize == right.dialogSize
        && left.weight == right.weight
        && left.italic == right.italic
        && left.underline == right.underline
        && left.strikeOut == right.strikeOut
        && left.charSet == right.charSet;
}

static bool WidgetConfigurationsEqual(const WidgetConfig& left, const WidgetConfig& right) {
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
        && left.leadingZero == right.leadingZero
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
        && left.showFrame == right.showFrame
        && left.textColor == right.textColor
        && left.backgroundColor == right.backgroundColor
        && left.alarmTextColor == right.alarmTextColor
        && left.alarmBackgroundColor == right.alarmBackgroundColor
        && left.weekNumbers == right.weekNumbers
        && left.sundayFirst == right.sundayFirst
        && left.dateCopyFormat == right.dateCopyFormat
        && left.timeSignal == right.timeSignal
        && left.alarmEnabled == right.alarmEnabled
        && left.alarmTimeSignal == right.alarmTimeSignal
        && left.alarmHour == right.alarmHour
        && left.alarmMinute == right.alarmMinute
        && left.runCommand == right.runCommand
        && left.loopAudio == right.loopAudio
        && left.command == right.command
        && left.callRemoteScript == right.callRemoteScript
        && left.remoteScriptUrl == right.remoteScriptUrl;
}

static bool WidgetConfigurationsDifferOnlyInRuntimeSettings(const WidgetConfig& left, const WidgetConfig& right) {
    WidgetConfig normalized = left;
    normalized.showSeconds = right.showSeconds;
    normalized.timeSignal = right.timeSignal;
    normalized.alarmTimeSignal = right.alarmTimeSignal;
    return WidgetConfigurationsEqual(normalized, right);
}

static void RecreateWidgetForConfiguration(Widget* widget, const WidgetConfig& configuration) {
    if (widget == nullptr || widget->window == nullptr) {
        return;
    }
    RECT rect = {};
    bool hasPosition = GetWindowRect(widget->window, &rect) != FALSE;
    int targetX = rect.left;
    int targetY = rect.top;
    if (hasPosition && widget->config.type == WIDGET_PANEL && configuration.type == WIDGET_PANEL) {
        POINT previousClockPosition = {};
        POINT newClockPosition = {};
        GetPanelLayout(widget->config, nullptr, &previousClockPosition, nullptr);
        GetPanelLayout(configuration, nullptr, &newClockPosition, nullptr);
        targetX = rect.left + previousClockPosition.x - newClockPosition.x;
    }
    bool alarmActive = widget->alarmActive;
    bool flashPhase = widget->flashPhase;
    int lastAlarmDate = widget->lastAlarmDate;
    int lastAlarmMinute = widget->lastAlarmMinute;
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
    for (size_t windowIndex = 0; windowIndex < widget->fullscreenWindows.size(); windowIndex++) {
        DestroyWindow(widget->fullscreenWindows[windowIndex]);
    }
    widget->fullscreenWindows.clear();
    widget->window = nullptr;
    widget->analogChild = nullptr;
    widget->analogProc = nullptr;
    widget->calendarChild = nullptr;
    widget->calendarProc = nullptr;
    widget->config = configuration;
    if (hasPosition) {
        widget->config.x = targetX;
        widget->config.y = targetY;
    }
    CreateWidgetWindow(widget);
    RefreshFullscreenPresentation();
    widget->alarmActive = alarmActive;
    widget->flashPhase = flashPhase;
    widget->lastAlarmDate = lastAlarmDate;
    widget->lastAlarmMinute = lastAlarmMinute;
    widget->alarmStoppedTick = alarmStoppedTick;
    widget->identifyActive = identifyActive;
    widget->identifyPhase = identifyPhase;
    widget->identifyRestoreHidden = identifyRestoreHidden;
    widget->identifyRestoreNotTopmost = identifyRestoreNotTopmost;
    widget->identifyEndTick = identifyEndTick;
    RenderWidget(widget);
}

static void RecreateWidgetForAppearance(Widget* widget, const WidgetConfig& appearance) {
    if (widget == nullptr || widget->window == nullptr || widget->config.type != appearance.type) {
        return;
    }
    WidgetConfig configuration = widget->config;
    CopyWidgetAppearance(&configuration, appearance);
    RecreateWidgetForConfiguration(widget, configuration);
}

static void ApplyWidgetAppearancePreview(Widget* widget, const WidgetConfig& appearance, bool structuralChange) {
    if (widget == nullptr || widget->window == nullptr || widget->config.type != appearance.type) {
        return;
    }
    if (widget->config.type == WIDGET_FULLSCREEN) {
        CopyWidgetAppearance(&widget->config, appearance);
        SetFullscreenPreview(widget);
        RefreshFullscreenPresentation();
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
    bool digitalFrameChanged = digital && widget->config.borderStyle != appearance.borderStyle;
    bool digitalDimensionsChanged = digital && (digitalFrameChanged
        || widget->config.borderWidth != appearance.borderWidth
        || widget->config.padding != appearance.padding
        || widget->config.leadingZero != appearance.leadingZero
        || widget->config.fontSize != appearance.fontSize
        || widget->config.fontFace != appearance.fontFace
        || widget->config.fontWeight != appearance.fontWeight
        || widget->config.fontItalic != appearance.fontItalic
        || widget->config.fontUnderline != appearance.fontUnderline
        || widget->config.fontStrikeOut != appearance.fontStrikeOut
        || widget->config.fontCharSet != appearance.fontCharSet);
    bool requiresRecreation = widget->config.transparentBackground != appearance.transparentBackground
        || !digital && (structuralChange || widget->config.size != appearance.size || widget->config.weekNumbers != appearance.weekNumbers || widget->config.sundayFirst != appearance.sundayFirst)
        || calendarWidget && (fontSelectionChanged || themeChanged);
    if (requiresRecreation) {
        RecreateWidgetForAppearance(widget, appearance);
        return;
    }
    if (digitalFrameChanged && !appearance.transparentBackground) {
        DWORD style = static_cast<DWORD>(GetWindowLongPtrW(widget->window, GWL_STYLE));
        DWORD extendedStyle = static_cast<DWORD>(GetWindowLongPtrW(widget->window, GWL_EXSTYLE));
        style &= ~WS_BORDER;
        extendedStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE);
        ApplyDigitalNativeBorderStyle(appearance.borderStyle, &style, &extendedStyle);
        SetWindowLongPtrW(widget->window, GWL_STYLE, static_cast<LONG_PTR>(style));
        SetWindowLongPtrW(widget->window, GWL_EXSTYLE, static_cast<LONG_PTR>(extendedStyle));
    }
    CopyWidgetAppearance(&widget->config, appearance);
    if (panelFontChanged && widget->config.type == WIDGET_PANEL) {
        widget->rendered = false;
    }
    if ((fontAntialiasingChanged || fontSelectionChanged) && widget->calendarChild != nullptr) {
        ApplyCalendarFont(widget);
    }
    if (digitalDimensionsChanged && !widget->config.transparentBackground) {
        int width = 0;
        int height = 0;
        GetWidgetDimensions(widget->config, &width, &height);
        UINT flags = SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOREDRAW;
        if (digitalFrameChanged) {
            flags |= SWP_FRAMECHANGED;
        }
        SetWindowPos(widget->window, nullptr, 0, 0, width, height, flags);
        widget->rendered = false;
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
    RenderWidget(widget);
}

static void PreviewSelectedWidgetAppearance(bool structuralChange) {
    if (!SaveAppearanceControlsToDraft()) {
        return;
    }
    WidgetConfig& appearance = settingsDraft[selectedDraftIndex];
    Widget* widget = FindWidgetById(appearance.id);
    if (widget == nullptr || widget->config.type != appearance.type) {
        return;
    }
    if (std::find(settingsAppearancePreviewIds.begin(), settingsAppearancePreviewIds.end(), appearance.id) == settingsAppearancePreviewIds.end()) {
        settingsAppearancePreviewIds.push_back(appearance.id);
    }
    settingsAppearancePreviewActive = true;
    ApplyWidgetAppearancePreview(widget, appearance, structuralChange);
}

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
    SelectOnlyWidgetIndex(selectedDraftIndex);
    LoadDraftIntoControls();
    return true;
}

static void ApplySettingsDraft() {
    StopSettingsPreview();
    StopTimeSignalPlayback();
    ClearCurrentTimeSignalSources();
    lastTimeSignalTarget = 0;
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
                    settingsDraft[draftIndex].previewX = rect.left;
                    settingsDraft[draftIndex].previewY = rect.top;
                } else {
                    int targetX = rect.left;
                    if (current->config.type == WIDGET_PANEL && settingsDraft[draftIndex].type == WIDGET_PANEL) {
                        POINT currentClockPosition = {};
                        POINT draftClockPosition = {};
                        GetPanelLayout(current->config, nullptr, &currentClockPosition, nullptr);
                        GetPanelLayout(settingsDraft[draftIndex], nullptr, &draftClockPosition, nullptr);
                        targetX = rect.left + currentClockPosition.x - draftClockPosition.x;
                    }
                    settingsDraft[draftIndex].x = targetX;
                    settingsDraft[draftIndex].y = rect.top;
                }
            }
        }
    }
    AppLanguage previousLanguage = appLanguage;
    appLanguage = static_cast<AppLanguage>(std::clamp(static_cast<int>(SendMessageW(hLanguageCombo, CB_GETCURSEL, 0, 0)), 0, LANG_COUNT - 1));
    RefreshInformationWindows();
    bool previousThemesDisabled = themesDisabled;
    themesDisabled = GetCheck(hDisableThemesCheck);
    int previousAppFontAntialiasing = appFontAntialiasing;
    appFontAntialiasing = std::clamp(static_cast<int>(SendMessageW(hAppAntialiasCombo, CB_GETCURSEL, 0, 0)), 0, FONT_ANTIALIAS_COUNT - 1);
    std::wstring previousAppFontFace = appFontFace;
    int previousAppFontWeight = appFontWeight;
    bool previousAppFontItalic = appFontItalic;
    appFontFace = settingsAppFontFace;
    appFontDialogSize = std::clamp(settingsAppFontDialogSize, 10, 9990);
    appFontWeight = std::clamp(settingsAppFontWeight, 0, 1000);
    appFontItalic = settingsAppFontItalic;
    storageUsesXml = GetCheck(hUseXmlSettingsCheck);
    bool newUseNtpTime = SendMessageW(hTimeSourceCombo, CB_GETCURSEL, 0, 0) == 1;
    int newNtpPreset = std::clamp(static_cast<int>(SendMessageW(hNtpPresetCombo, CB_GETCURSEL, 0, 0)), 0, NTP_PRESET_COUNT - 1);
    std::wstring newNtpServers = newNtpPreset == NTP_PRESET_CUSTOM ? GetControlText(hNtpServersEdit) : NtpServersForPreset(newNtpPreset);
    if (!HasNtpServers(newNtpServers)) {
        newNtpPreset = NTP_PRESET_GLOBAL;
        newNtpServers = NtpServersForPreset(newNtpPreset);
    }
    bool previousUseNtpTime = useNtpTime;
    bool ntpSettingsChanged = previousUseNtpTime != newUseNtpTime || ntpPreset != newNtpPreset || ntpServers != newNtpServers;
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
    }
    if (previousThemesDisabled != themesDisabled) {
        SetThemeAppProperties(themesDisabled ? STAP_ALLOW_NONCLIENT : STAP_ALLOW_NONCLIENT | STAP_ALLOW_CONTROLS | STAP_ALLOW_WEBCONTENT);
    }
    bool runtimeOnlyOrUnchanged = previousLanguage == appLanguage
        && previousThemesDisabled == themesDisabled
        && previousAppFontAntialiasing == appFontAntialiasing
        && previousAppFontFace == appFontFace
        && previousAppFontWeight == appFontWeight
        && previousAppFontItalic == appFontItalic
        && settingsDraft.size() == widgets.size();
    for (size_t index = 0; index < settingsDraft.size(); index++) {
        Widget* current = FindWidgetById(settingsDraft[index].id);
        if (current != nullptr) {
            current->config.fontDialogSize = settingsDraft[index].fontDialogSize;
        }
    }
    if (runtimeOnlyOrUnchanged) {
        for (size_t index = 0; index < settingsDraft.size(); index++) {
            Widget* current = FindWidgetById(settingsDraft[index].id);
            if (current == nullptr || current->fullscreenPreview ||
                (!WidgetConfigurationsEqual(current->config, settingsDraft[index]) && !WidgetConfigurationsDifferOnlyInRuntimeSettings(current->config, settingsDraft[index]))) {
                runtimeOnlyOrUnchanged = false;
                break;
            }
        }
    }
    if (runtimeOnlyOrUnchanged) {
        for (size_t index = 0; index < settingsDraft.size(); index++) {
            Widget* current = FindWidgetById(settingsDraft[index].id);
            if (current == nullptr) {
                continue;
            }
            current->config.timeSignal = settingsDraft[index].timeSignal;
            current->config.alarmTimeSignal = settingsDraft[index].alarmTimeSignal;
            if (current->config.showSeconds == settingsDraft[index].showSeconds) {
                continue;
            }
            current->config.showSeconds = settingsDraft[index].showSeconds;
            if (current->config.type == WIDGET_ANALOG || current->config.type == WIDGET_PANEL) {
                if (!UpdateAnalogSeconds(current)) {
                    RecreateWidgetForConfiguration(current, settingsDraft[index]);
                }
            } else if (current->config.type == WIDGET_DIGITAL) {
                int width = 0;
                int height = 0;
                GetWidgetDimensions(current->config, &width, &height);
                SetWindowPos(current->window, nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
            }
            current->lastRenderKey = -1;
            RenderWidget(current);
        }
    } else {
        DestroyWidgetWindows();
        widgets.clear();
        for (size_t index = 0; index < settingsDraft.size(); index++) {
            std::unique_ptr<Widget> widget(new Widget());
            widget->config = settingsDraft[index];
            widgets.push_back(std::move(widget));
        }
        for (size_t index = 0; index < widgets.size(); index++) {
            CreateWidgetWindow(widgets[index].get());
        }
        RefreshFullscreenPresentation();
    }
    for (size_t index = 0; index < widgets.size(); index++) {
        if (widgets[index]->calendarChild != nullptr) {
            ApplyCalendarFont(widgets[index].get());
        }
    }
    settingsAppearancePreviewActive = false;
    settingsAppearancePreviewIds.clear();
    settingsAppearanceOriginals.clear();
    if (previousAppFontAntialiasing != appFontAntialiasing || previousAppFontFace != appFontFace || previousAppFontWeight != appFontWeight || previousAppFontItalic != appFontItalic) {
        ResetUiFont();
    }
    if (previousThemesDisabled != themesDisabled || previousAppFontAntialiasing != appFontAntialiasing || previousAppFontFace != appFontFace || previousAppFontWeight != appFontWeight || previousAppFontItalic != appFontItalic) {
        ApplyUiStyle(hSettings);
        if (hHelp != nullptr) {
            ApplyUiStyle(hHelp);
        }
        if (hAbout != nullptr) {
            ApplyUiStyle(hAbout);
        }
    }
    settingsApplicationFontPreviewActive = false;
    UpdateTrayIcon();
    SaveAllSettings();
    if (useNtpTime) {
        StartNtpSynchronization(ntpSettingsChanged);
    }
}

static void SynchronizeOpenSettings(const Widget* widget) {
    if (hSettings == nullptr || !IsWindow(hSettings) || widget == nullptr) {
        return;
    }
    for (size_t index = 0; index < settingsDraft.size(); index++) {
        if (settingsDraft[index].id == widget->config.id) {
            settingsDraft[index] = widget->config;
            if (static_cast<int>(index) == selectedDraftIndex) {
                LoadDraftIntoControls();
            }
            RefreshWidgetList();
            break;
        }
    }
}

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
    SetWindowLongPtrW(button, GWLP_USERDATA, choice.rgbResult);
    InvalidateRect(button, nullptr, TRUE);
    return true;
}

static void UpdateFontDescription(const WidgetConfig& config) {
    if (hFontButton != nullptr) {
        SetWindowTextW(hFontButton, config.type == WIDGET_CALENDAR || config.type == WIDGET_PANEL ? CALENDAR_FONT_LABELS[appLanguage] : config.fontFace.c_str());
    }
    if (hPanelTopFontButton != nullptr) {
        SetWindowTextW(hPanelTopFontButton, PANEL_TOP_FONT_LABELS[appLanguage]);
    }
    if (hPanelTimeFontButton != nullptr) {
        SetWindowTextW(hPanelTimeFontButton, PANEL_TIME_FONT_LABELS[appLanguage]);
    }
    if (hPanelBottomFontButton != nullptr) {
        SetWindowTextW(hPanelBottomFontButton, PANEL_BOTTOM_FONT_LABELS[appLanguage]);
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
    SetWindowTextW(hFontDescription, description.c_str());
}

static bool ChooseFontAttributes(HWND owner, std::wstring* face, int* sizeTenths, int* weight, bool* italic, BYTE* charSet, bool* underline = nullptr, bool* strikeOut = nullptr) {
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
    choice.Flags = CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT | CF_FORCEFONTEXIST;
    if (!ChooseFontW(&choice) || font.lfFaceName[0] == L'\0') {
        return false;
    }
    *face = font.lfFaceName;
    *sizeTenths = std::clamp(choice.iPointSize, 10, 9990);
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

static void ChooseWidgetFont() {
    if (selectedDraftIndex < 0 || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
        return;
    }
    WidgetConfig& config = settingsDraft[selectedDraftIndex];
    if (!ChooseFontAttributes(hSettings, &config.fontFace, &config.fontDialogSize, &config.fontWeight, &config.fontItalic, &config.fontCharSet, &config.fontUnderline, &config.fontStrikeOut)) {
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

static void ChoosePanelFont(FontSelection* selection) {
    if (selection == nullptr) {
        return;
    }
    if (!ChooseFontAttributes(hSettings, &selection->face, &selection->dialogSize, &selection->weight, &selection->italic, &selection->charSet, &selection->underline, &selection->strikeOut)) {
        return;
    }
    PreviewSelectedWidgetAppearance(false);
}

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
    if (ChooseFontAttributes(hSettings, &selectedFace, &settingsAppFontDialogSize, &settingsAppFontWeight, &settingsAppFontItalic, &charSet)) {
        settingsAppFontFace = selectedFace;
        UpdateApplicationFontButtons();
        ApplyApplicationFontPreview();
    }
}

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

static void StopSettingsPreview() {
    settingsPreviewGeneration++;
    if (settingsTimeSignalPreviewActive) {
        StopTimeSignalPlayback();
        settingsTimeSignalPreviewActive = false;
    }
    if (settingsPreviewStopEvent != nullptr) {
        SetEvent(settingsPreviewStopEvent);
        CloseHandle(settingsPreviewStopEvent);
        settingsPreviewStopEvent = nullptr;
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
    if (hTestCommandButton != nullptr) {
        SetWindowTextW(hTestCommandButton, TEST_COMMAND_LABELS[appLanguage]);
    }
}

static void TestSettingsCommand() {
    if (settingsPreviewStopEvent != nullptr || settingsVisualPreviewActive || settingsTimeSignalPreviewActive) {
        StopSettingsPreview();
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
    std::wstring path = GetControlText(hCommandEdit);
    if (!path.empty()) {
        SetCheck(hRunCommandCheck, true);
        if (LooksLikeAudio(path)) {
            StartAudioPlaybackAsync(path, GetCheck(hLoopAudioCheck), hController, WM_SETTINGS_AUDIO_FINISHED, -1, settingsPreviewGeneration, &settingsPreviewStopEvent);
        } else {
            StartLocalCommandAsync(path);
        }
    }
    if (remoteScriptEnabled) {
        StartRemoteScriptAsync(remoteScriptUrl);
    }
    if (GetCheck(hAlarmTimeSignalCheck) && !IsTimeSignalPlaybackRunning()) {
        const ULONGLONG testDelay = 5ULL * 10000000;
        settingsTimeSignalPreviewActive = StartTimeSignalPlayback(CurrentFileTimeValue() + testDelay, hController, WM_TIME_SIGNAL_FINISHED);
    }
    if (settingsPreviewStopEvent == nullptr && !settingsVisualPreviewActive && !settingsTimeSignalPreviewActive) {
        StopSettingsPreview();
        return;
    }
    SetWindowTextW(hTestCommandButton, STOP_TEST_LABELS[appLanguage]);
}

static void BrowseForCommand() {
    wchar_t fileName[MAX_PATH] = {};
    OPENFILENAMEW dialog = {};
    dialog.lStructSize = sizeof(dialog);
    dialog.hwndOwner = hSettings;
    dialog.lpstrFile = fileName;
    dialog.nMaxFile = ARRAYSIZE(fileName);
    dialog.lpstrFilter = L"Zvuk a programy\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Všechny soubory\0*.*\0";
    dialog.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    if (GetOpenFileNameW(&dialog)) {
        SetWindowTextW(hCommandEdit, fileName);
        SetCheck(hRunCommandCheck, true);
        if (LooksLikeAudio(fileName)) {
            SetCheck(hLoopAudioCheck, true);
        }
    }
}

static void CreateSettingsControls() {
    generalControls.clear();
    appearanceControls.clear();
    alarmControls.clear();
    timeSignalControls.clear();
    timeControls.clear();
    settingsUnderlayLabels.clear();
    AddStatic(hSettings, TXT_TYPE, 10, 10, 22);
    hAddType = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST, 62, 7, 160, 220, hSettings, ID_ADD_TYPE);
    for (int type = 0; type < WIDGET_TYPE_COUNT; type++) {
        SendMessageW(hAddType, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(TypeName(static_cast<WidgetType>(type))));
    }
    SendMessageW(hAddType, CB_SETCURSEL, lastAddedWidgetType, 0);
    AddControl(0, L"BUTTON", Mnemonic(TXT_ADD).c_str(), WS_TABSTOP, 228, 5, 84, 27, hSettings, ID_ADD);
    hWidgetList = AddControl(WS_EX_CLIENTEDGE, L"LISTBOX", L"", WS_TABSTOP | LBS_NOTIFY | LBS_EXTENDEDSEL | LBS_NOINTEGRALHEIGHT | WS_VSCROLL, 10, 39, 302, 278, hSettings, ID_LIST_WIDGETS);
    AddControl(0, L"BUTTON", Mnemonic(TXT_REMOVE).c_str(), WS_TABSTOP, 10, 323, 148, 27, hSettings, ID_REMOVE);
    AddControl(0, L"BUTTON", Mnemonic(TXT_DUPLICATE).c_str(), WS_TABSTOP, 164, 323, 148, 27, hSettings, ID_DUPLICATE);
    hTabs = AddControl(0, WC_TABCONTROLW, L"", WS_TABSTOP, 322, 7, 430, 345, hSettings, ID_TABS);
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
    RECT pageRect = { 0, 0, 430, 345 };
    TabCtrl_AdjustRect(hTabs, FALSE, &pageRect);
    int pageX = 322 + pageRect.left;
    int pageY = 7 + pageRect.top;
    int pageWidth = pageRect.right - pageRect.left;
    int pageHeight = pageRect.bottom - pageRect.top;
    hGeneralPage = CreateWindowExW(0, CLASS_NAME, L"", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, pageX, pageY, pageWidth, pageHeight, hSettings, nullptr, hInstance, nullptr);
    hAppearancePage = CreateWindowExW(0, CLASS_NAME, L"", WS_CHILD | WS_CLIPSIBLINGS, pageX, pageY, pageWidth, pageHeight, hSettings, nullptr, hInstance, nullptr);
    hAlarmPage = CreateWindowExW(0, CLASS_NAME, L"", WS_CHILD | WS_CLIPSIBLINGS, pageX, pageY, pageWidth, pageHeight, hSettings, nullptr, hInstance, nullptr);
    hTimeSignalPage = CreateWindowExW(0, CLASS_NAME, L"", WS_CHILD | WS_CLIPSIBLINGS, pageX, pageY, pageWidth, pageHeight, hSettings, nullptr, hInstance, nullptr);
    hTimePage = CreateWindowExW(0, CLASS_NAME, L"", WS_CHILD | WS_CLIPSIBLINGS, pageX, pageY, pageWidth, pageHeight, hSettings, nullptr, hInstance, nullptr);
    int left = 8;
    int label = 162;
    int field = 244;
    int fieldLeft = left + label + 4;
    AddStatic(hGeneralPage, TXT_NAME, left, 11, 22, &generalControls);
    hNameEdit = AddControl(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_TABSTOP | ES_AUTOHSCROLL, fieldLeft, 8, field, 24, hGeneralPage, ID_NAME, &generalControls);
    AddStatic(hGeneralPage, TXT_TYPE, left, 42, 22, &generalControls);
    hTypeCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST, fieldLeft, 38, field, 220, hGeneralPage, ID_TYPE, &generalControls);
    for (int type = 0; type < WIDGET_TYPE_COUNT; type++) {
        SendMessageW(hTypeCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(TypeName(static_cast<WidgetType>(type))));
    }
    hVisibleCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_VISIBLE).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, left, 72, 105, 24, hGeneralPage, ID_VISIBLE, &generalControls);
    hTopmostCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_TOPMOST).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, left + 130, 72, 145, 24, hGeneralPage, ID_TOPMOST, &generalControls);
    hSecondsCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_SECONDS).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, left + 280, 72, 82, 24, hGeneralPage, ID_SECONDS, &generalControls);
    hUtcCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_UTC).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, left, 100, 120, 24, hGeneralPage, ID_UTC, &generalControls);
    hUtcTextCheck = AddControl(0, L"BUTTON", UTC_TEXT_LABELS[appLanguage], WS_TABSTOP | BS_AUTOCHECKBOX, left + 130, 100, 220, 24, hGeneralPage, ID_UTC_TEXT, &generalControls);
    hTimeZoneLabel = AddStatic(hGeneralPage, TXT_TIMEZONE, left, 130, 22, &generalControls);
    hTimeZoneCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST | WS_VSCROLL, fieldLeft, 126, field, 260, hGeneralPage, ID_TIMEZONE, &generalControls);
    for (size_t index = 0; index < timeZones.size(); index++) {
        int item = static_cast<int>(SendMessageW(hTimeZoneCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(timeZones[index].StandardName)));
        SendMessageW(hTimeZoneCombo, CB_SETITEMDATA, item, index);
    }
    AddStatic(hGeneralPage, TXT_OFFSET, left, 161, 22, &generalControls);
    hOffsetEdit = AddControl(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_TABSTOP | ES_AUTOHSCROLL, fieldLeft, 158, 136, 24, hGeneralPage, ID_OFFSET, &generalControls);
    AddUnderlayStatic(hGeneralPage, WIDGET_LANGUAGE_LABELS[appLanguage], WS_VISIBLE, left, 194, 22, &generalControls);
    hWidgetLanguageCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST, fieldLeft, 190, field, 220, hGeneralPage, ID_WIDGET_LANGUAGE, &generalControls);
    for (int index = 0; index < LANG_COUNT; index++) {
        SendMessageW(hWidgetLanguageCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(LANGUAGE_NAMES[index]));
    }
    hMonitorLabel = AddUnderlayStatic(hGeneralPage, MONITOR_LABELS[appLanguage], 0, left, 224, 22, &generalControls);
    hMonitorList = AddControl(WS_EX_CLIENTEDGE, L"LISTBOX", L"", WS_TABSTOP | LBS_EXTENDEDSEL | LBS_NOINTEGRALHEIGHT | WS_VSCROLL, fieldLeft, 220, field, 64, hGeneralPage, ID_MONITOR_LIST, &generalControls);
    hBlackoutMonitorsCheck = AddControl(0, L"BUTTON", BLACKOUT_MONITOR_LABELS[appLanguage], WS_TABSTOP | BS_AUTOCHECKBOX, left, 288, 350, 24, hGeneralPage, ID_BLACKOUT_MONITORS, &generalControls);
    hSizeLabel = AddStatic(hAppearancePage, TXT_SIZE, 8, 12, 22, &appearanceControls);
    hSizeCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST, 100, 8, 90, 180, hAppearancePage, ID_SIZE, &appearanceControls);
    int sizes[4] = {};
    int sizeCount = GetAnalogClockSizes(sizes);
    for (int index = 0; index < sizeCount; index++) {
        std::wstring sizeLabel = std::to_wstring(sizes[index]) + L" px";
        SendMessageW(hSizeCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(sizeLabel.c_str()));
    }
    hOpacityLabel = AddStatic(hAppearancePage, TXT_OPACITY, 8, 11, 22, &appearanceControls);
    hOpacityTrackBar = AddControl(0, TRACKBAR_CLASSW, L"", WS_TABSTOP | TBS_HORZ | TBS_AUTOTICKS, 121, 4, 250, 32, hAppearancePage, ID_OPACITY, &appearanceControls);
    SendMessageW(hOpacityTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(WIDGET_OPACITY_MIN, WIDGET_OPACITY_MAX));
    SendMessageW(hOpacityTrackBar, TBM_SETTICFREQ, 5, 0);
    SendMessageW(hOpacityTrackBar, TBM_SETLINESIZE, 0, 1);
    SendMessageW(hOpacityTrackBar, TBM_SETPAGESIZE, 0, 5);
    hOpacityValue = CreateWindowExW(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_RIGHT, 368, 11, 48, 22, hAppearancePage, nullptr, hInstance, nullptr);
    appearanceControls.push_back(hOpacityValue);
    hFontSizeLabel = AddStatic(hAppearancePage, TXT_FONT_SIZE, 8, 45, 22, &appearanceControls);
    hFontSizeTrackBar = AddControl(0, TRACKBAR_CLASSW, L"", WS_TABSTOP | TBS_HORZ | TBS_AUTOTICKS, 121, 38, 250, 32, hAppearancePage, ID_FONT_SIZE, &appearanceControls);
    SendMessageW(hFontSizeTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(DIGITAL_FONT_SIZE_MIN, DIGITAL_FONT_SIZE_MAX));
    SendMessageW(hFontSizeTrackBar, TBM_SETTICFREQ, 5, 0);
    SendMessageW(hFontSizeTrackBar, TBM_SETLINESIZE, 0, 1);
    SendMessageW(hFontSizeTrackBar, TBM_SETPAGESIZE, 0, 5);
    hFontSizeValue = CreateWindowExW(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_RIGHT, 368, 45, 48, 22, hAppearancePage, nullptr, hInstance, nullptr);
    appearanceControls.push_back(hFontSizeValue);
    hFontButton = AddControl(0, L"BUTTON", FONT_BUTTON_LABELS[appLanguage], WS_TABSTOP, 8, 70, 178, 27, hAppearancePage, ID_FONT, &appearanceControls);
    hPanelTopFontButton = AddControl(0, L"BUTTON", PANEL_TOP_FONT_LABELS[appLanguage], WS_TABSTOP, 8, 76, 178, 27, hAppearancePage, ID_PANEL_TOP_FONT, &appearanceControls);
    hPanelTimeFontButton = AddControl(0, L"BUTTON", PANEL_TIME_FONT_LABELS[appLanguage], WS_TABSTOP, 194, 76, 178, 27, hAppearancePage, ID_PANEL_TIME_FONT, &appearanceControls);
    hPanelBottomFontButton = AddControl(0, L"BUTTON", PANEL_BOTTOM_FONT_LABELS[appLanguage], WS_TABSTOP, 8, 106, 178, 27, hAppearancePage, ID_PANEL_BOTTOM_FONT, &appearanceControls);
    hDefaultAppearanceButton = AddControl(0, L"BUTTON", DEFAULT_APPEARANCE_LABELS[appLanguage], WS_TABSTOP, 194, 70, 178, 27, hAppearancePage, ID_DEFAULT_APPEARANCE, &appearanceControls);
    hTextColorButton = AddControl(0, L"BUTTON", Mnemonic(TXT_TEXT_COLOR).c_str(), WS_TABSTOP, 8, 100, 178, 27, hAppearancePage, ID_TEXT_COLOR, &appearanceControls);
    hBackgroundColorButton = AddControl(0, L"BUTTON", Mnemonic(TXT_BACKGROUND_COLOR).c_str(), WS_TABSTOP, 194, 100, 178, 27, hAppearancePage, ID_BACKGROUND_COLOR, &appearanceControls);
    hAlarmTextColorButton = AddControl(0, L"BUTTON", ALARM_TEXT_COLOR_LABELS[appLanguage], WS_TABSTOP, 8, 130, 178, 27, hAppearancePage, ID_ALARM_TEXT_COLOR, &appearanceControls);
    hAlarmBackgroundColorButton = AddControl(0, L"BUTTON", ALARM_BACKGROUND_COLOR_LABELS[appLanguage], WS_TABSTOP, 194, 130, 178, 27, hAppearancePage, ID_ALARM_BACKGROUND_COLOR, &appearanceControls);
    hPaddingLabel = AddUnderlayStatic(hAppearancePage, PADDING_LABELS[appLanguage], WS_VISIBLE, 8, 169, 22, &appearanceControls);
    hPaddingTrackBar = AddControl(0, TRACKBAR_CLASSW, L"", WS_TABSTOP | TBS_HORZ | TBS_AUTOTICKS, 121, 162, 250, 32, hAppearancePage, ID_PADDING, &appearanceControls);
    SendMessageW(hPaddingTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(0, DIGITAL_PADDING_MAX));
    SendMessageW(hPaddingTrackBar, TBM_SETTICFREQ, 5, 0);
    SendMessageW(hPaddingTrackBar, TBM_SETLINESIZE, 0, 1);
    SendMessageW(hPaddingTrackBar, TBM_SETPAGESIZE, 0, 5);
    hPaddingValue = CreateWindowExW(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_RIGHT, 368, 169, 48, 22, hAppearancePage, nullptr, hInstance, nullptr);
    appearanceControls.push_back(hPaddingValue);
    hBorderWidthLabel = AddUnderlayStatic(hAppearancePage, BORDER_WIDTH_LABELS[appLanguage], WS_VISIBLE, 8, 201, 22, &appearanceControls);
    hBorderWidthTrackBar = AddControl(0, TRACKBAR_CLASSW, L"", WS_TABSTOP | TBS_HORZ | TBS_AUTOTICKS, 121, 194, 250, 32, hAppearancePage, ID_BORDER_WIDTH, &appearanceControls);
    SendMessageW(hBorderWidthTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(0, DIGITAL_BORDER_WIDTH_MAX));
    SendMessageW(hBorderWidthTrackBar, TBM_SETTICFREQ, 1, 0);
    SendMessageW(hBorderWidthTrackBar, TBM_SETLINESIZE, 0, 1);
    SendMessageW(hBorderWidthTrackBar, TBM_SETPAGESIZE, 0, 1);
    hBorderWidthValue = CreateWindowExW(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_RIGHT, 368, 201, 48, 22, hAppearancePage, nullptr, hInstance, nullptr);
    appearanceControls.push_back(hBorderWidthValue);
    hBorderLabel = AddUnderlayStatic(hAppearancePage, BORDER_LABELS[appLanguage], WS_VISIBLE, 8, 233, 22, &appearanceControls);
    hBorderTrackBar = AddControl(0, TRACKBAR_CLASSW, L"", WS_TABSTOP | TBS_HORZ | TBS_AUTOTICKS, 121, 226, 250, 32, hAppearancePage, ID_BORDER, &appearanceControls);
    SendMessageW(hBorderTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(0, 3));
    SendMessageW(hBorderTrackBar, TBM_SETTICFREQ, 1, 0);
    SendMessageW(hBorderTrackBar, TBM_SETLINESIZE, 0, 1);
    SendMessageW(hBorderTrackBar, TBM_SETPAGESIZE, 0, 1);
    hWidgetAntialiasLabel = AddUnderlayStatic(hAppearancePage, ANTIALIASING_LABELS[appLanguage], WS_VISIBLE, 8, 262, 22, &appearanceControls);
    hWidgetAntialiasCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST, 148, 258, 86, 100, hAppearancePage, ID_WIDGET_ANTIALIAS, &appearanceControls);
    for (int antialiasing = 0; antialiasing < FONT_ANTIALIAS_COUNT; antialiasing++) {
        SendMessageW(hWidgetAntialiasCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(ANTIALIASING_NAMES[antialiasing]));
    }
    hWidgetDisableThemesCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_VISUAL_STYLES).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, 242, 258, 130, 24, hAppearancePage, ID_WIDGET_DISABLE_THEMES, &appearanceControls);
    hLeadingZeroCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_LEADING_ZERO).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, 8, 286, 130, 24, hAppearancePage, ID_LEADING_ZERO, &appearanceControls);
    hTransparentBackgroundCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_TRANSPARENT_BG).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, 145, 286, 220, 24, hAppearancePage, ID_TRANSPARENT_BG, &appearanceControls);
    hWeekNumbersCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_WEEK_NUMBERS).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, 8, 76, 150, 24, hAppearancePage, ID_WEEK_NUMBERS, &appearanceControls);
    hSundayFirstCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_SUNDAY_FIRST).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, 165, 76, 205, 24, hAppearancePage, ID_SUNDAY_FIRST, &appearanceControls);
    hShowFrameCheck = AddControl(0, L"BUTTON", SHOW_FRAME_LABELS[appLanguage], WS_TABSTOP | BS_AUTOCHECKBOX, 8, 76, 178, 24, hAppearancePage, ID_SHOW_FRAME, &appearanceControls);
    hDateFormatLabel = AddUnderlayStatic(hAppearancePage, DATE_FORMAT_LABELS[appLanguage], WS_VISIBLE, 8, 110, 22, &appearanceControls);
    hDateFormatCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST | WS_VSCROLL, 191, 106, 181, 240, hAppearancePage, ID_DATE_FORMAT, &appearanceControls);
    int y = 12;
    hAlarmEnabledCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_ALARM_ACTIVE).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, left, y, 175, 24, hAlarmPage, ID_ALARM_ENABLED, &alarmControls);
    y += 32;
    std::wstring alarmTimeLabel = Mnemonic(TXT_ALARM_TIME);
    AddUnderlayStatic(hAlarmPage, alarmTimeLabel.c_str(), WS_VISIBLE, left, y - 1, 22, &alarmControls);
    hAlarmTimeEdit = AddControl(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_TABSTOP | ES_AUTOHSCROLL, left + 154, y - 4, 100, 24, hAlarmPage, ID_ALARM_TIME, &alarmControls);
    y += 36;
    hRunCommandCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_RUN_FILE).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, left, y, 290, 24, hAlarmPage, ID_RUN_COMMAND, &alarmControls);
    y += 30;
    hCommandEdit = AddControl(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_TABSTOP | ES_AUTOHSCROLL, left, y, 275, 24, hAlarmPage, ID_COMMAND, &alarmControls);
    hBrowseButton = AddControl(0, L"BUTTON", Mnemonic(TXT_BROWSE).c_str(), WS_TABSTOP, left + 282, y - 3, 88, 27, hAlarmPage, ID_BROWSE, &alarmControls);
    y += 32;
    hTestCommandButton = AddControl(0, L"BUTTON", TEST_COMMAND_LABELS[appLanguage], WS_TABSTOP, left, y - 2, 102, 27, hAlarmPage, ID_TEST_COMMAND, &alarmControls);
    hLoopAudioCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_LOOP_AUDIO).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, left + 110, y, 260, 24, hAlarmPage, ID_LOOP_AUDIO, &alarmControls);
    y += 34;
    hRemoteScriptCheck = AddControl(0, L"BUTTON", REMOTE_SCRIPT_LABELS[appLanguage], WS_TABSTOP | BS_AUTOCHECKBOX, left, y, 300, 24, hAlarmPage, ID_REMOTE_SCRIPT, &alarmControls);
    y += 30;
    hRemoteScriptLabel = AddUnderlayStatic(hAlarmPage, REMOTE_SCRIPT_URL_LABELS[appLanguage], WS_VISIBLE, left, y + 3, 22, &alarmControls);
    hRemoteScriptEdit = AddControl(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_TABSTOP | ES_AUTOHSCROLL, left + 96, y, 274, 24, hAlarmPage, ID_REMOTE_SCRIPT_URL, &alarmControls);
    y += 34;
    hAlarmTimeSignalCheck = AddControl(0, L"BUTTON", ALARM_TIME_SIGNAL_LABELS[appLanguage], WS_TABSTOP | BS_AUTOCHECKBOX, left, y, 360, 24, hAlarmPage, ID_ALARM_TIME_SIGNAL, &alarmControls);
    AddUnderlayStatic(hTimeSignalPage, TIME_SIGNAL_FIELD_LABELS[appLanguage], WS_VISIBLE, left, 16, 22, &timeSignalControls);
    hTimeSignalCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST, fieldLeft + 50, 12, field - 50, 220, hTimeSignalPage, ID_TIME_SIGNAL, &timeSignalControls);
    for (int mode = 0; mode < TIME_SIGNAL_COUNT; mode++) {
        SendMessageW(hTimeSignalCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(TIME_SIGNAL_MODE_LABELS[appLanguage][mode]));
    }
    HWND timeSignalNote = AddControl(0, L"STATIC", TIME_SIGNAL_NOTE[appLanguage], SS_OWNERDRAW, left, 56, 364, 96, hTimeSignalPage, ID_TIME_SIGNAL_NOTE);
    timeSignalControls.push_back(timeSignalNote);
    AddUnderlayStatic(hTimePage, TIME_SOURCE_LABELS[appLanguage], WS_VISIBLE, 8, 16, 22, &timeControls);
    hTimeSourceCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST, 132, 12, 240, 180, hTimePage, ID_TIME_SOURCE, &timeControls);
    SendMessageW(hTimeSourceCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(SYSTEM_TIME_LABELS[appLanguage]));
    SendMessageW(hTimeSourceCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(NTP_TIME_LABELS[appLanguage]));
    SendMessageW(hTimeSourceCombo, CB_SETCURSEL, useNtpTime ? 1 : 0, 0);
    hNtpPresetLabel = AddUnderlayStatic(hTimePage, NTP_PRESET_FIELD_LABELS[appLanguage], WS_VISIBLE, 8, 50, 22, &timeControls);
    hNtpPresetCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST, 132, 46, 240, 220, hTimePage, ID_NTP_PRESET, &timeControls);
    for (int preset = 0; preset < NTP_PRESET_COUNT; preset++) {
        SendMessageW(hNtpPresetCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(NTP_PRESET_LABELS[appLanguage][preset]));
    }
    SendMessageW(hNtpPresetCombo, CB_SETDROPPEDWIDTH, ScaleSettingsHorizontal(360), 0);
    SendMessageW(hNtpPresetCombo, CB_SETCURSEL, ntpPreset, 0);
    hNtpServersLabel = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", NTP_SERVERS_LABELS[appLanguage], WS_CHILD | WS_VISIBLE, 8, 82, 364, 22, hTimePage, nullptr, hInstance, nullptr);
    timeControls.push_back(hNtpServersLabel);
    hNtpServersEdit = AddControl(WS_EX_CLIENTEDGE, L"EDIT", ntpServers.c_str(), WS_TABSTOP | ES_AUTOHSCROLL, 8, 106, 364, 24, hTimePage, ID_NTP_SERVERS, &timeControls);
    hNtpSyncButton = AddControl(0, L"BUTTON", NTP_SYNC_LABELS[appLanguage], WS_TABSTOP, 8, 140, 180, 27, hTimePage, ID_NTP_SYNC, &timeControls);
    hNtpStatus = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT, 8, 178, 364, 66, hTimePage, nullptr, hInstance, nullptr);
    timeControls.push_back(hNtpStatus);
    HWND timeGlobalNote = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", TIME_GLOBAL_NOTE[appLanguage], WS_CHILD | WS_VISIBLE | SS_LEFT, 8, 264, 364, 42, hTimePage, nullptr, hInstance, nullptr);
    timeControls.push_back(timeGlobalNote);
    UpdateNtpSettingsControls();
    HWND applicationLanguageLabel = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", APPLICATION_LANGUAGE_LABELS[appLanguage], WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | SS_LEFTNOWORDWRAP, 10, 364, 302, 22, hSettings, nullptr, hInstance, nullptr);
    settingsUnderlayLabels.push_back(applicationLanguageLabel);
    hLanguageCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST, 164, 360, 148, 220, hSettings, ID_LANGUAGE);
    for (int index = 0; index < LANG_COUNT; index++) {
        SendMessageW(hLanguageCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(LANGUAGE_NAMES[index]));
    }
    SendMessageW(hLanguageCombo, CB_SETCURSEL, appLanguage, 0);
    hAppFontLabel = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", APPLICATION_FONT_LABELS[appLanguage], WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | SS_LEFTNOWORDWRAP, 332, 364, 322, 22, hSettings, nullptr, hInstance, nullptr);
    settingsUnderlayLabels.push_back(hAppFontLabel);
    hAppFontButton = AddControl(0, L"BUTTON", L"", WS_TABSTOP, 472, 358, 182, 27, hSettings, ID_APP_FONT);
    hAppFontDefaultButton = AddControl(0, L"BUTTON", DEFAULT_FONT_LABELS[appLanguage], WS_TABSTOP, 658, 358, 84, 27, hSettings, ID_APP_FONT_DEFAULT);
    UpdateApplicationFontButtons();
    HWND applicationAntialiasLabel = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", ANTIALIASING_LABELS[appLanguage], WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | SS_LEFTNOWORDWRAP, 10, 393, 302, 22, hSettings, nullptr, hInstance, nullptr);
    settingsUnderlayLabels.push_back(applicationAntialiasLabel);
    hAppAntialiasCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST, 164, 389, 148, 100, hSettings, ID_APP_ANTIALIAS);
    for (int antialiasing = 0; antialiasing < FONT_ANTIALIAS_COUNT; antialiasing++) {
        SendMessageW(hAppAntialiasCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(ANTIALIASING_NAMES[antialiasing]));
    }
    SendMessageW(hAppAntialiasCombo, CB_SETCURSEL, appFontAntialiasing, 0);
    hDisableThemesCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_VISUAL_STYLES).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, 332, 389, 150, 24, hSettings, ID_VISUAL_STYLES);
    SetCheck(hDisableThemesCheck, themesDisabled);
    hUseXmlSettingsCheck = AddControl(0, L"BUTTON", XML_STORAGE_LABELS[appLanguage], WS_TABSTOP | BS_AUTOCHECKBOX, 548, 389, 194, 24, hSettings, ID_USE_XML_SETTINGS);
    SetCheck(hUseXmlSettingsCheck, storageUsesXml);
    AddControl(0, L"BUTTON", IMPORT_SETTINGS_LABELS[appLanguage], WS_TABSTOP, 10, 420, 148, 27, hSettings, ID_IMPORT_SETTINGS);
    AddControl(0, L"BUTTON", EXPORT_SETTINGS_LABELS[appLanguage], WS_TABSTOP, 164, 420, 148, 27, hSettings, ID_EXPORT_SETTINGS);
    AddControl(0, L"BUTTON", Mnemonic(TXT_SAVE).c_str(), WS_TABSTOP | BS_DEFPUSHBUTTON, 482, 420, 84, 27, hSettings, ID_SAVE);
    AddControl(0, L"BUTTON", Mnemonic(TXT_APPLY).c_str(), WS_TABSTOP, 570, 420, 84, 27, hSettings, ID_APPLY);
    AddControl(0, L"BUTTON", Mnemonic(TXT_CANCEL).c_str(), WS_TABSTOP, 658, 420, 84, 27, hSettings, ID_CANCEL);
    ScaleSettingsChildren(hSettings);
    ScaleSettingsChildren(hGeneralPage);
    ScaleSettingsChildren(hAppearancePage);
    ScaleSettingsChildren(hAlarmPage);
    ScaleSettingsChildren(hTimeSignalPage);
    ScaleSettingsChildren(hTimePage);
    for (size_t index = 0; index < settingsUnderlayLabels.size(); index++) {
        SetWindowPos(settingsUnderlayLabels[index], HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
    InitializeSettingsScrollBars();
    ApplyUiStyle(hSettings);
    ShowSettingsTab(0);
}

static void RebuildSettingsControls() {
    if (hSettings == nullptr || !IsWindow(hSettings)) {
        return;
    }
    StopSettingsPreview();
    int selectedTab = hTabs == nullptr ? 0 : TabCtrl_GetCurSel(hTabs);
    settingsTab = std::clamp(selectedTab, 0, 4);
    hSettingsLastFocus = nullptr;
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
    hUtcTextCheck = nullptr;
    hTimeZoneLabel = nullptr;
    hShowFrameCheck = nullptr;
    hMonitorLabel = nullptr;
    hMonitorList = nullptr;
    hBlackoutMonitorsCheck = nullptr;
    hWidgetAntialiasLabel = nullptr;
    hWidgetAntialiasCombo = nullptr;
    hAppAntialiasCombo = nullptr;
    hAppFontLabel = nullptr;
    hAppFontButton = nullptr;
    hAppFontDefaultButton = nullptr;
    hRemoteScriptCheck = nullptr;
    hRemoteScriptLabel = nullptr;
    hRemoteScriptEdit = nullptr;
    hAlarmTimeSignalCheck = nullptr;
    hTimeSignalCombo = nullptr;
    SetWindowTextW(hSettings, T(TXT_SETTINGS));
    CreateSettingsControls();
    RefreshWidgetList();
    LoadDraftIntoControls();
    if (hTabs == nullptr) {
        return;
    }
    TabCtrl_SetCurSel(hTabs, std::clamp(selectedTab, 0, 4));
    ShowSettingsTab(TabCtrl_GetCurSel(hTabs));
}

static void CloseSettingsWindow() {
    RestoreSettingsAppearancePreview();
    RestoreApplicationFontPreview();
    StopSettingsPreview();
    if (hSettings != nullptr && IsWindow(hSettings)) {
        if (hTabs != nullptr) {
            settingsTab = std::clamp(TabCtrl_GetCurSel(hTabs), 0, 4);
        }
        SaveFormPosition(hSettings, &settingsX, &settingsY);
        DestroyWindow(hSettings);
        SaveAllSettings();
    }
    hSettings = nullptr;
    hSettingsLastFocus = nullptr;
    hWidgetList = nullptr;
    hTabs = nullptr;
    hGeneralPage = nullptr;
    hAppearancePage = nullptr;
    hAlarmPage = nullptr;
    hTimeSignalPage = nullptr;
    hTimePage = nullptr;
    hTimeZoneLabel = nullptr;
    hShowFrameCheck = nullptr;
    hWidgetAntialiasLabel = nullptr;
    hWidgetAntialiasCombo = nullptr;
    hAppAntialiasCombo = nullptr;
    hAppFontLabel = nullptr;
    hAppFontButton = nullptr;
    hAppFontDefaultButton = nullptr;
    hRemoteScriptCheck = nullptr;
    hRemoteScriptLabel = nullptr;
    hRemoteScriptEdit = nullptr;
    hAlarmTimeSignalCheck = nullptr;
    hTimeSignalCombo = nullptr;
    hTimeSourceCombo = nullptr;
    hNtpPresetLabel = nullptr;
    hNtpPresetCombo = nullptr;
    hNtpServersLabel = nullptr;
    hNtpServersEdit = nullptr;
    hNtpStatus = nullptr;
    hNtpSyncButton = nullptr;
    settingsDraft.clear();
    settingsAppearanceOriginals.clear();
    settingsAppearancePreviewIds.clear();
    settingsAppearancePreviewActive = false;
    settingsApplicationFontPreviewActive = false;
    RefreshFullscreenPresentation();
}

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
        SetThemeAppProperties(themesDisabled ? STAP_ALLOW_NONCLIENT : STAP_ALLOW_NONCLIENT | STAP_ALLOW_CONTROLS | STAP_ALLOW_WEBCONTENT);
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

static void ShowSettingsWindow(int widgetId) {
    if (hSettings != nullptr && IsWindow(hSettings)) {
        SelectDraftWidgetById(widgetId);
        SetForegroundWindowEx(hSettings);
        return;
    }
    settingsDraft.clear();
    for (size_t index = 0; index < widgets.size(); index++) {
        settingsDraft.push_back(widgets[index]->config);
    }
    settingsAppearanceOriginals = settingsDraft;
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
    DWORD extendedStyle = std::any_of(widgets.begin(), widgets.end(), [](const std::unique_ptr<Widget>& w) { return w->config.topMost; }) ? WS_EX_TOPMOST : 0;
    DWORD style = 0;
    int settingsWidth = 0;
    int settingsHeight = 0;
    GetSettingsWindowLayout(extendedStyle, &style, &settingsWidth, &settingsHeight);
    ClampFormPosition(&settingsX, &settingsY, settingsWidth, settingsHeight);
    hSettings = CreateWindowExW(extendedStyle, CLASS_NAME, T(TXT_SETTINGS), style, settingsX, settingsY, settingsWidth, settingsHeight, nullptr, nullptr, hInstance, nullptr);
    RefreshFullscreenPresentation();
    CreateSettingsControls();
    RefreshWidgetList();
    LoadDraftIntoControls();
    if (hTabs != nullptr) {
        TabCtrl_SetCurSel(hTabs, std::clamp(settingsTab, 0, 4));
        ShowSettingsTab(TabCtrl_GetCurSel(hTabs));
    }
    ShowWindow(hSettings, SW_SHOW);
    SetForegroundWindowEx(hSettings);
}

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
    int characterCount = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, bytes, static_cast<int>(byteCount), nullptr, 0);
    if (characterCount <= 0) {
        return std::wstring();
    }
    std::wstring decoded(characterCount, L'\0');
    if (MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, bytes, static_cast<int>(byteCount), decoded.data(), characterCount) != characterCount) {
        return std::wstring();
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

static std::wstring BuildAboutText() {
    std::wstring result = ABOUT_TEXT[appLanguage];
    std::wstring license = LoadLicenseText();
    if (!license.empty()) {
        result += L"\r\n\r\n";
        result += license;
    }
    return result;
}

static void RefreshInformationWindows() {
    if (hHelp != nullptr && IsWindow(hHelp)) {
        SetWindowTextW(hHelp, T(TXT_HELP));
        std::wstring helpText = std::wstring(HELP_TEXT[appLanguage]) + HELP_ALARM_APPENDIX[appLanguage] + HELP_SELECTION_APPENDIX[appLanguage] + HELP_LAYOUT_APPENDIX[appLanguage]
            + HELP_STORAGE_APPENDIX[appLanguage] + HELP_SETTINGS_APPENDIX[appLanguage] + HELP_TIME_SIGNAL_APPENDIX[appLanguage] + HELP_TIME_APPENDIX[appLanguage]
            + HELP_FULLSCREEN_APPENDIX[appLanguage];
        SetDlgItemTextW(hHelp, ID_INFO_TEXT, helpText.c_str());
        SetDlgItemTextW(hHelp, ID_INFO_CLOSE, Mnemonic(TXT_CLOSE).c_str());
    }
    if (hAbout != nullptr && IsWindow(hAbout)) {
        SetWindowTextW(hAbout, T(TXT_ABOUT));
        std::wstring aboutText = BuildAboutText();
        SetDlgItemTextW(hAbout, ID_INFO_TEXT, aboutText.c_str());
        SetDlgItemTextW(hAbout, ID_INFO_CLOSE, Mnemonic(TXT_CLOSE).c_str());
    }
}

static void ShowInformationWindow(bool help) {
    HWND* target = help ? &hHelp : &hAbout;
    if (*target != nullptr && IsWindow(*target)) {
        SetForegroundWindowEx(*target);
        return;
    }
    int* x = help ? &helpX : &aboutX;
    int* y = help ? &helpY : &aboutY;
    ClampFormPosition(x, y, 660, 500);
    *target = CreateWindowExW(WS_EX_TOPMOST, CLASS_NAME, help ? T(TXT_HELP) : T(TXT_ABOUT), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, *x, *y, 660, 500, nullptr, nullptr, hInstance, nullptr);
    std::wstring body = help ? std::wstring(HELP_TEXT[appLanguage]) + HELP_ALARM_APPENDIX[appLanguage] + HELP_SELECTION_APPENDIX[appLanguage] + HELP_LAYOUT_APPENDIX[appLanguage]
        + HELP_STORAGE_APPENDIX[appLanguage] + HELP_SETTINGS_APPENDIX[appLanguage] + HELP_TIME_SIGNAL_APPENDIX[appLanguage] + HELP_TIME_APPENDIX[appLanguage]
        + HELP_FULLSCREEN_APPENDIX[appLanguage] : BuildAboutText();
    DWORD textStyle = WS_TABSTOP | WS_VSCROLL | ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL;
    HWND text = AddControl(WS_EX_CLIENTEDGE, L"EDIT", body.c_str(), textStyle, 18, 18, 610, 385, *target, ID_INFO_TEXT);
    if (!help && hAboutFont == nullptr) {
        hAboutFont = CreateAboutFont();
    }
    SendMessageW(text, EM_SETSEL, 0, 0);
    AddControl(0, L"BUTTON", Mnemonic(TXT_CLOSE).c_str(), WS_TABSTOP | BS_DEFPUSHBUTTON, 528, 420, 100, 28, *target, ID_INFO_CLOSE);
    ApplyUiStyle(*target);
    ShowWindow(*target, SW_SHOW);
    SetForegroundWindowEx(*target);
}

static void HandleSettingsCommand(int id, int notification) {
    if (id == ID_LIST_WIDGETS && notification == LBN_SELCHANGE) {
        if (!SaveControlsToDraft(true)) {
            SelectOnlyWidgetIndex(selectedDraftIndex);
            return;
        }
        if (settingsPreviewStopEvent != nullptr || settingsVisualPreviewActive) {
            StopSettingsPreview();
        }
        int caretIndex = static_cast<int>(SendMessageW(hWidgetList, LB_GETCARETINDEX, 0, 0));
        if (caretIndex >= 0 && caretIndex < static_cast<int>(settingsDraft.size())) {
            selectedDraftIndex = caretIndex;
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
        if (selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size()) && type >= 0 && type < WIDGET_TYPE_COUNT) {
            WidgetConfig& config = settingsDraft[selectedDraftIndex];
            WidgetType previousType = config.type;
            std::wstring editedName = GetControlText(hNameEdit);
            bool defaultName = editedName.empty() || editedName == TypeName(previousType);
            if (!SaveControlsToDraft(true)) {
                SendMessageW(hTypeCombo, CB_SETCURSEL, previousType, 0);
                return;
            }
            WidgetType selectedType = static_cast<WidgetType>(type);
            config.type = selectedType;
            if (selectedType != previousType) {
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
                    preview.language = config.language;
                    preview.timeZoneKey = config.timeZoneKey;
                    preview.monitorDevices = config.monitorDevices;
                    preview.blackoutOtherMonitors = config.blackoutOtherMonitors;
                    preview.offsetMilliseconds = config.offsetMilliseconds;
                    CopyWidgetAppearance(&preview, config);
                    if (std::find(settingsAppearancePreviewIds.begin(), settingsAppearancePreviewIds.end(), config.id) == settingsAppearancePreviewIds.end()) {
                        settingsAppearancePreviewIds.push_back(config.id);
                    }
                    settingsAppearancePreviewActive = true;
                    RecreateWidgetForConfiguration(widget, preview);
                }
                RefreshWidgetList();
                LoadDraftIntoControls();
                UpdateSettingsSelectionState();
                return;
            }
        }
        UpdateSettingControlAvailability();
    } else if (id == ID_UTC && notification == BN_CLICKED) {
        UpdateSettingControlAvailability();
    } else if (id == ID_ALARM_TIME && notification == EN_CHANGE && GetFocus() == hAlarmTimeEdit) {
        SetCheck(hAlarmEnabledCheck, true);
    } else if (id == ID_ALARM_TIME && notification == EN_KILLFOCUS) {
        int hour = 0;
        int minute = 0;
        std::wstring text = GetControlText(hAlarmTimeEdit);
        if (ParseAlarmTime(text.c_str(), &hour, &minute)) {
            wchar_t formatted[16] = {};
            swprintf_s(formatted, L"%02d:%02d", hour, minute);
            SetWindowTextW(hAlarmTimeEdit, formatted);
        }
    } else if (id == ID_OFFSET && notification == EN_KILLFOCUS) {
        LONGLONG offset = 0;
        std::wstring text = GetControlText(hOffsetEdit);
        if (ParseOffset(text.c_str(), &offset)) {
            SetWindowTextW(hOffsetEdit, FormatOffset(offset).c_str());
        }
    } else if (id == ID_REMOTE_SCRIPT && notification == BN_CLICKED) {
        bool remoteScriptEnabled = GetCheck(hRemoteScriptCheck);
        EnableWindow(hRemoteScriptLabel, remoteScriptEnabled);
        EnableWindow(hRemoteScriptEdit, remoteScriptEnabled);
        if (remoteScriptEnabled) {
            SetFocus(hRemoteScriptEdit);
        }
    } else if (id == ID_SIZE && notification == CBN_SELCHANGE) {
        SaveAppearanceControlsToDraft();
        UpdateSettingControlAvailability();
        PreviewSelectedWidgetAppearance(true);
    } else if (id == ID_WIDGET_ANTIALIAS && notification == CBN_SELCHANGE) {
        PreviewSelectedWidgetAppearance(false);
    } else if (id == ID_WIDGET_LANGUAGE && notification == CBN_SELCHANGE) {
        int language = static_cast<int>(SendMessageW(hWidgetLanguageCombo, CB_GETCURSEL, 0, 0));
        if (selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size()) && language >= 0 && language < LANG_COUNT) {
            WidgetConfig& config = settingsDraft[selectedDraftIndex];
            int dateFormat = static_cast<int>(SendMessageW(hDateFormatCombo, CB_GETCURSEL, 0, 0));
            if (dateFormat >= 0 && dateFormat < DATE_FORMAT_COUNT) {
                config.dateCopyFormat = dateFormat;
            }
            config.language = static_cast<AppLanguage>(language);
            FillDateFormatCombo(config);
        }
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
                    SendMessageW(hNtpPresetCombo, CB_SETCURSEL, NTP_PRESET_CUSTOM, 0);
                }
            }
        }
        UpdateNtpSettingsControls();
    } else if (id == ID_NTP_SYNC && notification == BN_CLICKED) {
        StartNtpSynchronization(true);
        UpdateNtpSettingsControls();
    } else if (id == ID_ADD) {
        if (!SaveControlsToDraft(true)) {
            return;
        }
        int type = static_cast<int>(SendMessageW(hAddType, CB_GETCURSEL, 0, 0));
        if (type < 0 || type >= WIDGET_TYPE_COUNT) {
            type = WIDGET_ANALOG;
        }
        lastAddedWidgetType = static_cast<WidgetType>(type);
        WidgetConfig config = DefaultConfig(static_cast<WidgetType>(type), static_cast<int>(settingsDraft.size()));
        int selectedAppFontAntialiasing = static_cast<int>(SendMessageW(hAppAntialiasCombo, CB_GETCURSEL, 0, 0));
        config.fontAntialiasing = std::clamp(selectedAppFontAntialiasing, 0, FONT_ANTIALIAS_COUNT - 1);
        settingsDraft.push_back(config);
        selectedDraftIndex = static_cast<int>(settingsDraft.size()) - 1;
        RefreshWidgetList(false);
        LoadDraftIntoControls();
    } else if (id == ID_DUPLICATE) {
        if (!SaveControlsToDraft(true) || selectedDraftIndex < 0 || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
            return;
        }
        WidgetConfig copy = settingsDraft[selectedDraftIndex];
        copy.id = nextWidgetId++;
        copy.x += 28;
        copy.y += 28;
        settingsDraft.insert(settingsDraft.begin() + selectedDraftIndex + 1, copy);
        selectedDraftIndex++;
        RefreshWidgetList(false);
        LoadDraftIntoControls();
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
            return;
        }
        if (MessageBoxW(hSettings, T(TXT_DELETE_CONFIRM), T(TXT_SETTINGS), MB_YESNO | MB_ICONQUESTION) != IDYES) {
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
        RefreshWidgetList(false);
        LoadDraftIntoControls();
    } else if (id == ID_TEXT_COLOR) {
        if (ChooseButtonColor(hTextColorButton)) {
            PreviewSelectedWidgetAppearance(false);
        }
    } else if (id == ID_BACKGROUND_COLOR) {
        if (ChooseButtonColor(hBackgroundColorButton)) {
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
    } else if (id == ID_PANEL_TOP_FONT && selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
        ChoosePanelFont(&settingsDraft[selectedDraftIndex].panelTopFont);
    } else if (id == ID_PANEL_TIME_FONT && selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
        ChoosePanelFont(&settingsDraft[selectedDraftIndex].panelTimeFont);
    } else if (id == ID_PANEL_BOTTOM_FONT && selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
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
    } else if ((id == ID_LEADING_ZERO || id == ID_TRANSPARENT_BG || id == ID_WIDGET_DISABLE_THEMES) && notification == BN_CLICKED) {
        if (id == ID_WIDGET_DISABLE_THEMES) {
            UpdateSettingControlAvailability();
        }
        PreviewSelectedWidgetAppearance(false);
    } else if ((id == ID_WEEK_NUMBERS || id == ID_SUNDAY_FIRST || id == ID_SHOW_FRAME) && notification == BN_CLICKED) {
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
                if (settingsDraft[index].id != widgets[index]->config.id || settingsDraft[index].name != widgets[index]->config.name) {
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
                RefreshWidgetList();
            }
        }
    } else if (id == ID_CANCEL) {
        CloseSettingsWindow();
    }
}

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
            return SendMessageW(parent, WM_LBUTTONDBLCLK, wParam, lParam);
        }
        if (message == WM_LBUTTONDBLCLK) {
            widget->lastAnalogClickTick = 0;
        }
        if (message == WM_LBUTTONDOWN || message == WM_LBUTTONUP || message == WM_MOUSEMOVE || message == WM_LBUTTONDBLCLK || message == WM_RBUTTONUP || message == WM_CONTEXTMENU) {
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

static LRESULT CALLBACK CalendarChildProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    HWND parent = GetParent(window);
    Widget* widget = reinterpret_cast<Widget*>(GetWindowLongPtrW(parent, GWLP_USERDATA));
    if (widget != nullptr) {
        if (message == WM_RBUTTONUP || message == WM_CONTEXTMENU) {
            return SendMessageW(parent, message, wParam, lParam);
        }
        if (message == WM_LBUTTONDOWN && widget->config.type == WIDGET_CALENDAR) {
            MCHITTESTINFO hit = {};
            hit.cbSize = sizeof(hit);
            hit.pt.x = GET_X_LPARAM(lParam);
            hit.pt.y = GET_Y_LPARAM(lParam);
            MonthCal_HitTest(window, &hit);
            bool draggableArea = hit.uHit == MCHT_NOWHERE || hit.uHit == MCHT_TITLEBK || hit.uHit == MCHT_CALENDARBK;
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

static bool IsPanelDateLinkAtCursor(const Widget* widget) {
    if (widget == nullptr || widget->config.type != WIDGET_PANEL) {
        return false;
    }
    POINT point = {};
    return GetCursorPos(&point) && ScreenToClient(widget->window, &point) && PtInRect(&widget->panelDateLinkRect, point);
}

static void SetPanelDateHot(Widget* widget, bool hot) {
    if (widget == nullptr || widget->config.type != WIDGET_PANEL || widget->panelDateHot == hot) {
        return;
    }
    widget->panelDateHot = hot;
    if (!hot && widget->panelDateTooltip != nullptr) {
        SendMessageW(widget->panelDateTooltip, TTM_POP, 0, 0);
    }
    RECT header = {};
    GetClientRect(widget->window, &header);
    header.bottom = 35;
    InvalidateRect(widget->window, &header, FALSE);
}

static void SelectPanelToday(Widget* widget) {
    if (widget == nullptr || widget->calendarChild == nullptr) {
        return;
    }
    if (widget->panelDateTooltip != nullptr) {
        SendMessageW(widget->panelDateTooltip, TTM_POP, 0, 0);
    }
    SYSTEMTIME today = {};
    GetDisplayedTime(widget->config, &today);
    MonthCal_SetToday(widget->calendarChild, &today);
    MonthCal_SetCurSel(widget->calendarChild, &today);
    SetFocus(widget->calendarChild);
}

static LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    Widget* widget = reinterpret_cast<Widget*>(GetWindowLongPtrW(window, GWLP_USERDATA));
    if (message == WM_NCCREATE) {
        CREATESTRUCTW* create = reinterpret_cast<CREATESTRUCTW*>(lParam);
        if (create->lpCreateParams != nullptr) {
            widget = static_cast<Widget*>(create->lpCreateParams);
            SetWindowLongPtrW(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(widget));
        }
    }
    if (message == taskbarCreatedMessage && window == hController) {
        AddTrayIcon();
        return 0;
    }
    switch (message) {
        case WM_SETCURSOR:
            if (LOWORD(lParam) == HTCLIENT && IsPanelDateLinkAtCursor(widget)) {
                SetCursor(LoadCursorW(nullptr, IDC_HAND));
                return TRUE;
            }
            break;
        case WM_MOUSELEAVE:
            SetPanelDateHot(widget, false);
            break;
        case DM_GETDEFID:
            if (window == hSettings) {
                return MAKELRESULT(ID_SAVE, DC_HASDEFID);
            }
            break;
        case WM_ACTIVATE:
            if (window == hSettings) {
                if (LOWORD(wParam) == WA_INACTIVE) {
                    HWND focused = GetFocus();
                    if (focused == hSettings || IsChild(hSettings, focused)) {
                        hSettingsLastFocus = focused;
                    }
                } else if (hSettingsLastFocus != nullptr) {
                    PostMessageW(hSettings, WM_RESTORE_SETTINGS_FOCUS, 0, 0);
                }
            }
            break;
        case WM_RESTORE_SETTINGS_FOCUS:
            if (window == hSettings && hSettingsLastFocus != nullptr && IsWindow(hSettingsLastFocus) && IsWindowVisible(hSettingsLastFocus) && IsWindowEnabled(hSettingsLastFocus)) {
                SetFocus(hSettingsLastFocus);
            }
            return 0;
        case WM_DISPLAYCHANGE:
            if (window == hController) {
                displayRefreshPending = false;
                RecreateAllWidgetWindows();
                return 0;
            }
            if (!displayRefreshPending) {
                displayRefreshPending = true;
                PostMessageW(hController, WM_REFRESH_DISPLAYS, 0, 0);
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
                if (finishedWidget != nullptr && finishedWidget->audioGeneration == generation && finishedWidget->audioStopEvent != nullptr) {
                    CloseHandle(finishedWidget->audioStopEvent);
                    finishedWidget->audioStopEvent = nullptr;
                }
                return 0;
            }
            break;
        case WM_SETTINGS_AUDIO_FINISHED:
            if (window == hController) {
                ULONG generation = static_cast<ULONG>(lParam);
                if (settingsPreviewGeneration == generation && settingsPreviewStopEvent != nullptr) {
                    CloseHandle(settingsPreviewStopEvent);
                    settingsPreviewStopEvent = nullptr;
                }
                return 0;
            }
            break;
        case WM_TIME_SIGNAL_FINISHED:
            if (window == hController) {
                FinishTimeSignalPlayback();
                ClearCurrentTimeSignalSources();
                settingsTimeSignalPreviewActive = false;
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
                    ntpLastQueryFailed = false;
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
            if (window == hGeneralPage || window == hAppearancePage || window == hAlarmPage || window == hTimeSignalPage || window == hTimePage) {
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
            bool tabControlChild = std::find(generalControls.begin(), generalControls.end(), control) != generalControls.end()
                || std::find(appearanceControls.begin(), appearanceControls.end(), control) != appearanceControls.end()
                || std::find(alarmControls.begin(), alarmControls.end(), control) != alarmControls.end()
                || std::find(timeSignalControls.begin(), timeSignalControls.end(), control) != timeSignalControls.end()
                || std::find(timeControls.begin(), timeControls.end(), control) != timeControls.end();
            LONG_PTR style = GetWindowLongPtrW(control, GWL_STYLE);
            UINT buttonType = static_cast<UINT>(style & BS_TYPEMASK);
            if (tabControlChild && (buttonType == BS_CHECKBOX || buttonType == BS_AUTOCHECKBOX || buttonType == BS_3STATE || buttonType == BS_AUTO3STATE)) {
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
            if (window == hTimeSignalPage && item != nullptr && item->CtlID == ID_TIME_SIGNAL_NOTE) {
                int savedState = SaveDC(item->hDC);
                int colorIndex = themesDisabled ? COLOR_BTNFACE : COLOR_WINDOW;
                FillRect(item->hDC, &item->rcItem, GetSysColorBrush(colorIndex));
                SetBkMode(item->hDC, TRANSPARENT);
                SetTextColor(item->hDC, GetSysColor(IsWindowEnabled(item->hwndItem) ? COLOR_WINDOWTEXT : COLOR_GRAYTEXT));
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
            if (window == hGeneralPage || window == hAppearancePage || window == hAlarmPage || window == hTimeSignalPage || window == hTimePage) {
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
            if (window == hGeneralPage || window == hAppearancePage || window == hAlarmPage || window == hTimeSignalPage || window == hTimePage) {
                RECT rect = {};
                GetClientRect(window, &rect);
                int colorIndex = themesDisabled ? COLOR_BTNFACE : COLOR_WINDOW;
                FillRect(reinterpret_cast<HDC>(wParam), &rect, GetSysColorBrush(colorIndex));
                return 0;
            }
            break;
        case WM_PAINT:
            if (widget != nullptr && (widget->config.type == WIDGET_DIGITAL && !widget->config.transparentBackground || widget->config.type == WIDGET_FULLSCREEN)) {
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
            if (window == hAppearancePage) {
                return SendMessageW(hSettings, WM_HSCROLL, wParam, lParam);
            }
            if (window == hSettings) {
                if (lParam == 0 && ScrollSettingsWindow(SB_HORZ, LOWORD(wParam))) {
                    return 0;
                }
                HWND trackBar = reinterpret_cast<HWND>(lParam);
                if (trackBar == hOpacityTrackBar || trackBar == hFontSizeTrackBar || trackBar == hPaddingTrackBar || trackBar == hBorderTrackBar || trackBar == hBorderWidthTrackBar) {
                    UpdateAppearanceSliderLabels(trackBar);
                    PreviewSelectedWidgetAppearance(false);
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
            if (window == hGeneralPage || window == hAppearancePage || window == hAlarmPage || window == hTimeSignalPage || window == hTimePage) {
                return SendMessageW(hSettings, WM_MOUSEWHEEL, wParam, lParam);
            }
            if (window == hSettings && ScrollSettingsWheel(wParam)) {
                return 0;
            }
            break;
        case WM_COMMAND:
        {
            int id = LOWORD(wParam);
            int notification = HIWORD(wParam);
            if (window == hGeneralPage || window == hAppearancePage || window == hAlarmPage || window == hTimeSignalPage || window == hTimePage) {
                return SendMessageW(hSettings, WM_COMMAND, wParam, lParam);
            }
            if (window == hSettings) {
                HandleSettingsCommand(id, notification);
                return 0;
            }
            if (window == hHelp || window == hAbout) {
                if (id == ID_INFO_CLOSE) {
                    SendMessageW(window, WM_CLOSE, 0, 0);
                }
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
            if (widget != nullptr && widget->panelDateTooltip != nullptr && reinterpret_cast<NMHDR*>(lParam)->hwndFrom == widget->panelDateTooltip && reinterpret_cast<NMHDR*>(lParam)->code == TTN_GETDISPINFOW) {
                NMTTDISPINFOW* information = reinterpret_cast<NMTTDISPINFOW*>(lParam);
                information->lpszText = const_cast<wchar_t*>(PANEL_TODAY_TOOLTIP[widget->config.language]);
                return 0;
            }
            if (widget != nullptr && widget->calendarChild != nullptr && reinterpret_cast<NMHDR*>(lParam)->hwndFrom == widget->calendarChild && reinterpret_cast<NMHDR*>(lParam)->code == MCN_SELECT) {
                NMSELCHANGE* selection = reinterpret_cast<NMSELCHANGE*>(lParam);
                CopyWidgetDate(widget, selection->stSelStart);
                return 0;
            }
            if (window == hSettings && hTabs != nullptr && reinterpret_cast<NMHDR*>(lParam)->idFrom == ID_TABS && reinterpret_cast<NMHDR*>(lParam)->code == TCN_SELCHANGE) {
                settingsTab = std::clamp(TabCtrl_GetCurSel(hTabs), 0, 4);
                ShowSettingsTab(settingsTab);
                return 0;
            }
            break;
        case WM_TRAYICON:
            if (window == hController) {
                UINT event = LOWORD(lParam);
                if (event == (trayUsesVersion4 ? WM_CONTEXTMENU : WM_RBUTTONUP)) {
                    ShowTrayContextMenu();
                } else if (trayUsesVersion4 ? event == NIN_SELECT || event == NIN_KEYSELECT : event == WM_LBUTTONUP) {
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
                        SetWindowPos(widgets[index]->window, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
                        for (size_t windowIndex = 0; windowIndex < widgets[index]->fullscreenWindows.size(); windowIndex++) {
                            SetWindowPos(widgets[index]->fullscreenWindows[windowIndex], HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
                        }
                        if (!widgets[index]->config.topMost && widgets[index]->config.type != WIDGET_FULLSCREEN) {
                            SetWindowPos(widgets[index]->window, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
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
                StartNtpSynchronization(false);
                CheckTimeSignals();
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
                    int renderKey = renderSeconds ? displayed.wHour * 3600 + displayed.wMinute * 60 + displayed.wSecond : displayed.wHour * 60 + displayed.wMinute;
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
                if (IsPanelDateLinkAtCursor(widget)) {
                    SelectPanelToday(widget);
                    return 0;
                }
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
            if (widget != nullptr && widget->config.type == WIDGET_PANEL && !widget->dragging) {
                bool hot = IsPanelDateLinkAtCursor(widget);
                SetPanelDateHot(widget, hot);
                if (hot) {
                    TRACKMOUSEEVENT tracking = {
                        sizeof(tracking),
                        TME_LEAVE,
                        window,
                        0
                    };
                    TrackMouseEvent(&tracking);
                }
            }
            if (widget != nullptr && widget->dragging && wParam & MK_LBUTTON) {
                widget->lastAnalogClickTick = 0;
                POINT cursor = {};
                GetCursorPos(&cursor);
                SetWindowPos(window, nullptr, cursor.x - widget->dragOffset.x, cursor.y - widget->dragOffset.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
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
            if (widget != nullptr && widget->alarmStoppedTick != 0 && GetTickCount64() - widget->alarmStoppedTick <= GetDoubleClickTime()) {
                return 0;
            }
            if (IsPanelDateLinkAtCursor(widget)) {
                SelectPanelToday(widget);
                return 0;
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
                    if (widget->alarmActive) {
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
            if (widget != nullptr && window == widget->window) {
                widget->panelDateTooltip = nullptr;
            }
            if (window == hController) {
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

int APIENTRY wWinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE previousInstance, _In_ LPWSTR commandLine, _In_ int showCommand) {
    UNREFERENCED_PARAMETER(previousInstance);
    UNREFERENCED_PARAMETER(commandLine);
    UNREFERENCED_PARAMETER(showCommand);
    hInstance = instance;
    hSingleInstanceMutex = CreateMutexW(nullptr, FALSE, L"CalClock.MultiWidget.Instance");
    if (hSingleInstanceMutex != nullptr && GetLastError() == ERROR_ALREADY_EXISTS) {
        HWND existing = FindWindowExW(HWND_MESSAGE, nullptr, CLASS_NAME, CONTROLLER_TITLE);
        if (existing != nullptr) {
            SendMessageW(existing, WM_SHOW_EXISTING, 0, 0);
        }
        CloseHandle(hSingleInstanceMutex);
        return 0;
    }
    INITCOMMONCONTROLSEX controls = { sizeof(controls), ICC_WIN95_CLASSES | ICC_TAB_CLASSES | ICC_DATE_CLASSES };
    InitCommonControlsEx(&controls);
    WSADATA winsockData = {};
    winsockReady = WSAStartup(MAKEWORD(2, 2), &winsockData) == 0;
    InstallCalendarLocaleHook();
    LoadAllSettings();
    bool anyWidgetVisible = std::any_of(widgets.begin(), widgets.end(), [](const std::unique_ptr<Widget>& widget) {
        return widget->config.visible;
    });
    if (!anyWidgetVisible && !widgets.empty()) {
        widgets[0]->config.visible = true;
    }
    SetThemeAppProperties(themesDisabled ? STAP_ALLOW_NONCLIENT : STAP_ALLOW_NONCLIENT | STAP_ALLOW_CONTROLS | STAP_ALLOW_WEBCONTENT);
    WNDCLASSEXW blackoutClass = {};
    blackoutClass.cbSize = sizeof(blackoutClass);
    blackoutClass.lpfnWndProc = BlackoutWindowProc;
    blackoutClass.hInstance = instance;
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
    hController = CreateWindowExW(0, CLASS_NAME, CONTROLLER_TITLE, 0, 0, 0, 0, 0, HWND_MESSAGE, nullptr, instance, nullptr);
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
        if (hSettings != nullptr && IsWindow(hSettings)) {
            HWND focused = GetFocus();
            if (focused == hSettings || IsChild(hSettings, focused)) {
                hSettingsLastFocus = focused;
            }
        }
        if ((message.message == WM_KEYDOWN || message.message == WM_SYSKEYDOWN) && message.wParam == VK_ESCAPE && HideFullscreenWidgetsFromEscape()) {
            continue;
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
