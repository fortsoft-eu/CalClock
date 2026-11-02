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
#define WIN32_LEAN_AND_MEAN
#include "../CalClock/resource.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <winver.h>
#include "../CalClock/AboutForm.h"
#include "../CalClock/AlarmActions.h"
#include "../CalClock/AudioOutput.h"
#include "../CalClock/AnalogClockHost.h"
#include "../CalClock/CalendarLocaleScope.h"
#include "../CalClock/CalClock.h"
#include "../CalClock/ClockTime.h"
#include "../CalClock/DateFormats.h"
#include "../CalClock/DialogFrame.h"
#include "../CalClock/HelpForm.h"
#include "../CalClock/Localization.h"
#include "../CalClock/MonitorInfo.h"
#include "../CalClock/NtpClient.h"
#include "../CalClock/PersistWindowState.h"
#include "../CalClock/SelectionEdit.h"
#include "../CalClock/SettingsStorage.h"
#include "../CalClock/SettingsEdit.h"
#include "../CalClock/SystemDialogTemplate.h"
#include "../CalClock/TimeFormats.h"
#include "../CalClock/TimeSignal.h"
#include "../CalClock/TimeZoneSupport.h"
#include "../CalClock/WidgetLayout.h"
#include "../CalClock/WindowRedrawScope.h"
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

#include <cstdio>

static int testFailures = 0;
static int testLocalCalls = 0;
static int testRemoteCalls = 0;
static int testAudioCalls = 0;
static int testSaveCalls = 0;
static std::wstring testXmlPath;
static SettingsSnapshot testSavedSnapshot;

/// Reports a regression while allowing independent scenarios to finish.
static void Require(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "FAILED: %s\n", message);
        ++testFailures;
    }
}

/// Prevents native helpers from moving the user's focus or foreground window.
static HWND WINAPI TestSetFocus(HWND window) {
    return nullptr;
}

/// Keeps active-window requests inert on the isolated test desktop.
static HWND WINAPI TestSetActiveWindow(HWND window) {
    return nullptr;
}

/// Keeps foreground and stacking activation requests inert.
static BOOL WINAPI TestWindowActivation(HWND window) {
    return TRUE;
}

/// Never joins a test thread to any other input queue.
static BOOL WINAPI TestAttachThreadInput(DWORD first, DWORD second, BOOL attach) {
    return FALSE;
}

/// Does not grant another process foreground permission.
static BOOL WINAPI TestAllowSetForegroundWindow(DWORD process) {
    return FALSE;
}

/// Keeps test windows hidden even when production code requests visible presentation.
static BOOL WINAPI TestShowWindow(HWND window, int command) {
    return ShowWindow(window, SW_HIDE);
}

/// Forces every positioning call to remain nonactivating and every top-level test window to stay hidden.
static BOOL WINAPI TestSetWindowPos(HWND window, HWND after, int x, int y, int width, int height,
    UINT flags) {
    flags |= SWP_NOACTIVATE;
    if ((GetWindowLongPtrW(window, GWL_STYLE) & WS_CHILD) == 0) {
        flags = flags & ~SWP_SHOWWINDOW | SWP_HIDEWINDOW;
    }
    return SetWindowPos(window, after, x, y, width, height, flags);
}

/// Keeps deferred positioning nonactivating as well.
static HDWP WINAPI TestDeferWindowPos(HDWP positions, HWND window, HWND after, int x, int y,
        int width, int height, UINT flags) {
    flags |= SWP_NOACTIVATE;
    if ((GetWindowLongPtrW(window, GWL_STYLE) & WS_CHILD) == 0) {
        flags = flags & ~SWP_SHOWWINDOW | SWP_HIDEWINDOW;
    }
    return DeferWindowPos(positions, window, after, x, y, width, height, flags);
}

/// Applies nonactivation before creating any production-requested top-level test window.
static HWND WINAPI TestCreateWindowExW(DWORD extended, LPCWSTR className, LPCWSTR title, DWORD style,
        int x, int y, int width, int height, HWND parent, HMENU menu, HINSTANCE instance, LPVOID parameter) {
    if ((style & WS_CHILD) == 0) {
        extended |= WS_EX_NOACTIVATE;
        style &= ~WS_VISIBLE;
    }
    return CreateWindowExW(extended, className, title, style, x, y, width, height, parent, menu, instance,
        parameter);
}

/// Makes native resource dialogs nonactivating and hidden before Windows creates their HWNDs.
static HWND WINAPI TestCreateDialogIndirectParamW(HINSTANCE instance, LPCDLGTEMPLATE source, HWND owner,
        DLGPROC procedure, LPARAM parameter) {
    WORD* words = reinterpret_cast<WORD*>(const_cast<DLGTEMPLATE*>(source));
    if (words[1] == 0xFFFF) {
        DWORD* extended = reinterpret_cast<DWORD*>(words + 4);
        DWORD* style = reinterpret_cast<DWORD*>(words + 6);
        if ((*style & WS_CHILD) == 0) {
            *extended |= WS_EX_NOACTIVATE;
            *style &= ~WS_VISIBLE;
        }
    } else {
        DLGTEMPLATE* definition = const_cast<DLGTEMPLATE*>(source);
        if ((definition->style & WS_CHILD) == 0) {
            definition->dwExtendedStyle |= WS_EX_NOACTIVATE;
            definition->style &= ~WS_VISIBLE;
        }
    }
    return CreateDialogIndirectParamW(instance, source, owner, procedure, parameter);
}

/// Records saves without accessing the user's registry or automatic XML location.
static bool TestWriteRegistrySettings(const SettingsSnapshot& snapshot) {
    ++testSaveCalls;
    testSavedSnapshot = snapshot;
    return true;
}

/// Redirects all automatic XML paths to the test build directory.
static std::wstring TestAutomaticXmlSettingsPath(bool createDirectory) {
    return testXmlPath;
}

/// Makes destructive settings-backend cleanup inert in the integrated UI test.
static void TestRemoveSettings() {}

/// Keeps message boxes out of the user desktop and permits validation tests to return normally.
static int WINAPI TestMessageBoxW(HWND owner, LPCWSTR text, LPCWSTR title, UINT type) {
    return IDOK;
}

/// Records local actions without starting a shell, file, or process.
static void TestStartLocalCommandAsync(const std::wstring& command) {
    ++testLocalCalls;
}

/// Records remote actions without any network access.
static void TestStartRemoteScriptAsync(const std::wstring& url) {
    ++testRemoteCalls;
}

/// Supplies inert event handles so production preview lifetime code runs without opening audio devices.
static bool TestStartAudioPlaybackAsync(const std::wstring& path, bool loop, bool muted,
        const std::shared_ptr<std::atomic<int>>& volume, HWND window, UINT message, int id, ULONG generation,
        HANDLE* stop, HANDLE* mute) {
    ++testAudioCalls;
    *stop = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    *mute = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    return *stop != nullptr && *mute != nullptr;
}

/// Keeps the host notification area untouched by Settings Apply and menu operations.
static BOOL WINAPI TestShellNotifyIconW(DWORD message, PNOTIFYICONDATAW data) {
    return TRUE;
}

/// Blocks any direct shell launch outside the already substituted alarm-action dispatchers.
static HINSTANCE WINAPI TestShellExecuteW(HWND owner, LPCWSTR verb, LPCWSTR file, LPCWSTR parameters,
        LPCWSTR directory, int show) {
    Require(false, "unexpected direct shell launch");
    return nullptr;
}

/// Rejects worker-thread creation if an unplanned production branch reaches it.
static HANDLE WINAPI TestCreateThread(LPSECURITY_ATTRIBUTES attributes, SIZE_T stack,
        LPTHREAD_START_ROUTINE entry, LPVOID parameter, DWORD flags, LPDWORD id) {
    Require(false, "unexpected worker-thread startup");
    return nullptr;
}

/// Avoids installing power-management wake requests during settings tests.
static BOOL WINAPI TestSetWaitableTimer(HANDLE timer, const LARGE_INTEGER* due, LONG period,
        PTIMERAPCROUTINE callback, LPVOID parameter, BOOL resume) {
    return TRUE;
}

#define SetFocus TestSetFocus
#define SetActiveWindow TestSetActiveWindow
#define SetForegroundWindow TestWindowActivation
#define BringWindowToTop TestWindowActivation
#define AttachThreadInput TestAttachThreadInput
#define AllowSetForegroundWindow TestAllowSetForegroundWindow
#define ShowWindow TestShowWindow
#define SetWindowPos TestSetWindowPos
#define DeferWindowPos TestDeferWindowPos
#define CreateWindowExW TestCreateWindowExW
#define CreateDialogIndirectParamW TestCreateDialogIndirectParamW
#define WriteRegistrySettings TestWriteRegistrySettings
#define AutomaticXmlSettingsPath TestAutomaticXmlSettingsPath
#define RemoveRegistrySettings TestRemoveSettings
#define RemoveAutomaticXmlSettings TestRemoveSettings
#define MessageBoxW TestMessageBoxW
#define StartLocalCommandAsync TestStartLocalCommandAsync
#define StartRemoteScriptAsync TestStartRemoteScriptAsync
#define StartAudioPlaybackAsync TestStartAudioPlaybackAsync
#define Shell_NotifyIconW TestShellNotifyIconW
#define ShellExecuteW TestShellExecuteW
#define CreateThread TestCreateThread
#define SetWaitableTimer TestSetWaitableTimer
#include "../CalClock/CalClock.cpp"
#undef SetFocus
#undef SetActiveWindow
#undef SetForegroundWindow
#undef BringWindowToTop
#undef AttachThreadInput
#undef AllowSetForegroundWindow
#undef ShowWindow
#undef SetWindowPos
#undef DeferWindowPos
#undef CreateWindowExW
#undef CreateDialogIndirectParamW
#undef WriteRegistrySettings
#undef AutomaticXmlSettingsPath
#undef RemoveRegistrySettings
#undef RemoveAutomaticXmlSettings
#undef MessageBoxW
#undef StartLocalCommandAsync
#undef StartRemoteScriptAsync
#undef StartAudioPlaybackAsync
#undef Shell_NotifyIconW
#undef ShellExecuteW
#undef CreateThread
#undef SetWaitableTimer

/// Creates a distinctive valid alarm whose every stored field can be compared after UI operations.
static WidgetConfig AlarmConfiguration(int id, WidgetType type = WIDGET_DIGITAL) {
    WidgetConfig config = DefaultConfig(type, 0);
    config.id = id;
    config.name = L"Alarm settings regression";
    config.visible = false;
    config.alarmEnabled = true;
    config.alarmDays = 0x55;
    config.alarmHour = 17;
    config.alarmMinute = 43;
    config.runCommand = true;
    config.command = L"C:\\Alarm test\\signal.wav";
    config.loopAudio = true;
    config.alarmVolume = -1837;
    config.callRemoteScript = true;
    config.remoteScriptUrl = L"https://example.invalid/alarm?test=1";
    config.alarmTimeSignal = true;
    config.alarmWakeComputer = true;
    return config;
}

/// Compares alarm preferences independently of unrelated control normalization.
static bool SameAlarm(const WidgetConfig& left, const WidgetConfig& right) {
    return left.alarmEnabled == right.alarmEnabled
        && left.alarmDays == right.alarmDays
        && left.alarmHour == right.alarmHour
        && left.alarmMinute == right.alarmMinute
        && left.runCommand == right.runCommand
        && left.command == right.command
        && left.loopAudio == right.loopAudio
        && left.alarmVolume == right.alarmVolume
        && left.callRemoteScript == right.callRemoteScript
        && left.remoteScriptUrl == right.remoteScriptUrl
        && left.alarmTimeSignal == right.alarmTimeSignal
        && left.alarmWakeComputer == right.alarmWakeComputer;
}

/// Loads one selected draft into the actual Settings controls.
static void LoadAlarm(const WidgetConfig& config) {
    settingsDraft[0] = config;
    selectedDraftIndex = 0;
    RefreshWidgetList(false, false);
    SelectOnlyWidgetIndex(0, false);
    LoadDraftIntoControls();
}

/// Checks the blanket disabled state and ensures enabling restores dependent controls and retained values.
static void TestAvailability() {
    WidgetConfig expected = AlarmConfiguration(1);
    LoadAlarm(expected);
    Require(IsWindowEnabled(hAlarmEnabledCheck), "alarm activation checkbox enabled for digital widget");
    Require(IsWindowEnabled(hAlarmWakeCheck), "wake available for enabled alarm");
    Require(IsWindowEnabled(hAlarmVolumeTrackBar), "audio volume available for selected audio command");
    SetCheck(hAlarmEnabledCheck, false);
    UpdateSettingControlAvailability();
    for (HWND control : alarmControls) {
        Require(IsWindowEnabled(control) == (control == hAlarmEnabledCheck),
            "disabled alarm disables entire tab");
    }
    WidgetConfig read = expected;
    Require(ReadWidgetControls(read, false), "disabled valid alarm can be saved");
    expected.alarmEnabled = false;
    Require(SameAlarm(read, expected), "disabling retains every alarm preference");
    SetCheck(hAlarmEnabledCheck, true);
    UpdateSettingControlAvailability();
    expected.alarmEnabled = true;
    Require(ReadWidgetControls(read, false) && SameAlarm(read, expected),
        "reenabling retains alarm preferences");
    SetCheck(hRunCommandCheck, false);
    SetCheck(hRemoteScriptCheck, false);
    UpdateSettingControlAvailability();
    Require(!IsWindowEnabled(hCommandEdit)
        && !IsWindowEnabled(hBrowseButton)
        && !IsWindowEnabled(hTestCommandButton), "command controls follow action checkbox");
    Require(!IsWindowEnabled(hAlarmVolumeTrackBar) && !IsWindowEnabled(hLoopAudioCheck),
        "audio controls follow command checkbox");
    Require(!IsWindowEnabled(hRemoteScriptEdit), "URL control follows remote checkbox");
    Require(IsWindowEnabled(hAlarmWakeCheck) && IsWindowEnabled(hAlarmTimeSignalCheck),
        "wake and pips independent of command and remote actions");
    SetCheck(hRunCommandCheck, true);
    SetControlText(hCommandEdit, L"notepad.exe");
    UpdateSettingControlAvailability();
    Require(IsWindowEnabled(hTestCommandButton) && !IsWindowEnabled(hAlarmVolumeTrackBar),
        "non-audio command permits test without volume control");
    LoadAlarm(AlarmConfiguration(1, WIDGET_CALENDAR));
    for (HWND control : alarmControls) {
        Require(!IsWindowEnabled(control), "standalone calendar keeps all alarm controls disabled");
    }
    LoadAlarm(AlarmConfiguration(1));
    SendMessageW(hWidgetList, LB_SETSEL, TRUE, 1);
    UpdateSettingControlAvailability();
    for (HWND control : alarmControls) {
        Require(!IsWindowEnabled(control), "multiselection disables individual alarm controls");
    }
    LoadAlarm(AlarmConfiguration(1));
}

/// Verifies every weekday bit and the empty-day state survive the actual controls-to-draft path.
static void TestWeekdays() {
    for (unsigned int days = 0; days <= ALARM_DAYS_ALL; ++days) {
        WidgetConfig expected = AlarmConfiguration(1);
        expected.alarmDays = days;
        LoadAlarm(expected);
        WidgetConfig read = expected;
        Require(ReadWidgetControls(read, false) && read.alarmDays == days, "weekday mask roundtrip");
    }
    LoadAlarm(AlarmConfiguration(1));
}

/// Reproduces disabling with unfinished alarm fields and verifies the last valid stored values survive.
static void TestDisabledValidation() {
    WidgetConfig expected = AlarmConfiguration(1);
    LoadAlarm(expected);
    SetControlText(hAlarmTimeEdit, L"unfinished");
    SetCheck(hAlarmEnabledCheck, false);
    UpdateSettingControlAvailability();
    WidgetConfig read = expected;
    expected.alarmEnabled = false;
    Require(ReadWidgetControls(read, false), "invalid disabled time must not prevent disabling alarm");
    Require(SameAlarm(read, expected), "disabled invalid time retains last valid alarm fields");
    LoadAlarm(AlarmConfiguration(1));
    SetControlText(hRemoteScriptEdit, L"invalid URL");
    SetCheck(hAlarmEnabledCheck, false);
    UpdateSettingControlAvailability();
    read = settingsDraft[0];
    Require(ReadWidgetControls(read, false), "invalid disabled remote URL must not prevent disabling alarm");
    Require(SameAlarm(read, expected), "disabled invalid URL retains last valid alarm fields");
    if (!read.alarmEnabled) {
        LoadAlarm(read);
        SetCheck(hAlarmEnabledCheck, true);
        UpdateSettingControlAvailability();
        expected.alarmEnabled = true;
        Require(ReadWidgetControls(read, false) && SameAlarm(read, expected),
            "reenabling after saving invalid disabled fields restores last valid values");
    }
    LoadAlarm(AlarmConfiguration(1));
    SetControlText(hAlarmTimeEdit, L"unfinished");
    Require(!ReadWidgetControls(read, false), "active invalid alarm time remains rejected");
    LoadAlarm(AlarmConfiguration(1));
    SetControlText(hRemoteScriptEdit, L"invalid URL");
    Require(!ReadWidgetControls(read, false), "active invalid remote URL remains rejected");
    LoadAlarm(AlarmConfiguration(1));
}

/// Runs the real child-control rebuild and preserves raw controls and precise stored alarm volume.
static void TestRebuild() {
    WidgetConfig expected = AlarmConfiguration(1);
    LoadAlarm(expected);
    SetCheck(hAlarmEnabledCheck, false);
    UpdateSettingControlAvailability();
    RebuildSettingsControls(true);
    WidgetConfig read = expected;
    expected.alarmEnabled = false;
    Require(ReadWidgetControls(read, false), "rebuilt disabled alarm can be read");
    Require(SameAlarm(read, expected), "rebuild preserves disabled alarm settings");
    Require(!IsWindowEnabled(hAlarmWakeCheck), "rebuild keeps disabled wake checkbox disabled");
    SetCheck(hAlarmEnabledCheck, true);
    UpdateSettingControlAvailability();
    expected.alarmEnabled = true;
    Require(ReadWidgetControls(read, false) && SameAlarm(read, expected),
        "rebuild then enable restores settings");
}

/// Checks actual XML and widget-clipboard persistence for enabled and disabled alarm preferences.
static void TestPersistence() {
    SettingsSnapshot snapshot{};
    snapshot.widgets.push_back(AlarmConfiguration(1));
    WidgetConfig disabled = AlarmConfiguration(2);
    disabled.alarmEnabled = false;
    snapshot.widgets.push_back(disabled);
    Require(WriteSettingsXml(testXmlPath, snapshot), "write isolated alarm settings XML");
    SettingsSnapshot restored{};
    Require(ReadSettingsXml(testXmlPath, LANG_EN_US, CreateStoredWidgetDefaults, &restored),
        "read alarm settings XML");
    Require(restored.widgets.size() == 2, "XML preserves both widgets");
    if (restored.widgets.size() == 2) {
        Require(SameAlarm(restored.widgets[0], snapshot.widgets[0]), "XML preserves enabled alarm fields");
        Require(SameAlarm(restored.widgets[1], snapshot.widgets[1]), "XML preserves disabled alarm fields");
    }
    std::vector<BYTE> bytes;
    std::vector<WidgetConfig> copied;
    Require(SerializeWidgetClipboardData(snapshot.widgets, &bytes), "serialize alarm widget clipboard");
    Require(DeserializeWidgetClipboardData(bytes, LANG_EN_US, CreateStoredWidgetDefaults, &copied),
        "deserialize alarm widget clipboard");
    Require(copied.size() == 2, "clipboard preserves widget count");
    if (copied.size() == 2) {
        Require(SameAlarm(copied[0], snapshot.widgets[0]) && SameAlarm(copied[1], snapshot.widgets[1]),
            "clipboard preserves all enabled and disabled alarm fields");
    }
}

/// Commits the real draft and toggles the context-menu alarm while redirecting saved snapshots to memory.
static void TestApplyAndMenu() {
    WidgetConfig expected = AlarmConfiguration(1);
    LoadAlarm(expected);
    for (const std::unique_ptr<Widget>& widget : widgets) {
        widget->window = TestCreateWindowExW(WS_EX_NOACTIVATE, L"STATIC", L"", WS_POPUP,
            0, 0, 1, 1, nullptr, nullptr, hInstance, nullptr);
        Require(widget->window != nullptr, "isolated widget placeholder created");
    }
    SetCheck(hAlarmEnabledCheck, false);
    UpdateSettingControlAvailability();
    Require(SaveControlsToDraft(false), "disabled draft validates before Apply");
    ApplySettingsDraft();
    expected.alarmEnabled = false;
    Require(SameAlarm(widgets[0]->config, expected), "Apply preserves disabled alarm preferences");
    Require(testSaveCalls > 0 && testSavedSnapshot.widgets.size() == 2, "Apply saves full isolated snapshot");
    if (testSavedSnapshot.widgets.size() == 2) {
        Require(SameAlarm(testSavedSnapshot.widgets[0], expected),
            "saved Apply snapshot retains alarm fields");
    }
    HandleWidgetMenuCommand(widgets[0].get(), ID_MENU_ALARM_ENABLED);
    expected.alarmEnabled = true;
    Require(SameAlarm(widgets[0]->config, expected), "menu reenable retains alarm preferences");
    Require(widgets[0]->alarmSchedule.Next() != 0, "menu reenable plans alarm immediately");
    Require(GetCheck(hAlarmEnabledCheck) && IsWindowEnabled(hAlarmWakeCheck),
        "menu reenable synchronizes open Settings and dependencies");
    HandleWidgetMenuCommand(widgets[0].get(), ID_MENU_ALARM_ENABLED);
    expected.alarmEnabled = false;
    Require(SameAlarm(widgets[0]->config, expected), "menu disable retains alarm preferences");
    Require(widgets[0]->alarmSchedule.Next() == 0, "menu disable cancels plan immediately");
    Require(!GetCheck(hAlarmEnabledCheck) && !IsWindowEnabled(hAlarmWakeCheck),
        "menu disable synchronizes open Settings and dependencies");
    for (const std::unique_ptr<Widget>& widget : widgets) {
        DestroyWindow(widget->window);
        widget->window = nullptr;
    }
    CancelAlarmWakeTimer();
}

/// Ensures stopping a visual test cannot cancel a real alarm that started while the test was active.
static void TestPreviewOverlap() {
    WidgetConfig expected = AlarmConfiguration(1);
    LoadAlarm(expected);
    Widget* widget = widgets[0].get();
    widget->config = expected;
    widget->config.visible = true;
    widget->window = nullptr;
    TestSettingsCommand();
    Require(settingsVisualPreviewActive && widget->alarmActive, "alarm test starts visual preview");
    Require(testAudioCalls > 0 && testRemoteCalls > 0, "preview uses inert audio and remote dispatch");
    StartWidgetAlarm(widget);
    Require(widget->alarmActive && widget->audioStopEvent != nullptr, "real alarm starts during preview");
    StopSettingsPreview();
    Require(widget->alarmActive, "stopping test preserves real alarm visual state");
    Require(widget->audioStopEvent != nullptr, "stopping test preserves real alarm audio");
    StopWidgetAlarm(widget);
    widget->config.visible = false;
}

/// Creates native controls on a private desktop and runs Settings paths without desktop or external effects.
int wmain(int argc, wchar_t** argv) {
    if (argc != 2) {
        return 2;
    }
    testXmlPath = argv[1];
    HDESK previous = GetThreadDesktop(GetCurrentThreadId());
    std::wstring desktopName = L"CalClockAlarmSettingsTests-" + std::to_wstring(GetCurrentProcessId());
    HDESK desktop = CreateDesktopW(desktopName.c_str(), nullptr, nullptr, 0, GENERIC_ALL, nullptr);
    if (desktop == nullptr || !SetThreadDesktop(desktop)) {
        std::fprintf(stderr, "Cannot create isolated desktop: %lu\n", GetLastError());
        return 2;
    }
    INITCOMMONCONTROLSEX common{ sizeof(common),
        ICC_WIN95_CLASSES | ICC_STANDARD_CLASSES | ICC_USEREX_CLASSES };
    InitCommonControlsEx(&common);
    hInstance = GetModuleHandleW(nullptr);
    appLanguage = LANG_EN_US;
    useNtpTime = false;
    winsockReady = false;
    LoadTimeZones();
    for (int id = 1; id <= 2; ++id) {
        std::unique_ptr<Widget> widget = std::make_unique<Widget>();
        widget->config = AlarmConfiguration(id);
        widgets.push_back(std::move(widget));
        settingsDraft.push_back(AlarmConfiguration(id));
    }
    settingsAppliedWidgets = settingsDraft;
    settingsAppearanceOriginals = settingsDraft;
    selectedDraftIndex = 0;
    settingsTab = 2;
    hSettings = CreateSettingsDialog(IDD_SETTINGS, nullptr, SettingsDialogProc, 0);
    Require(hSettings != nullptr, "native root Settings dialog created");
    Require(hSettings != nullptr
        && !IsWindowVisible(hSettings)
        && (GetWindowLongPtrW(hSettings, GWL_EXSTYLE) & WS_EX_NOACTIVATE) != 0,
        "Settings window starts hidden and nonactivating");
    if (hSettings != nullptr && CreateSettingsControls(2)) {
        TestAvailability();
        TestWeekdays();
        TestDisabledValidation();
        TestRebuild();
        TestPersistence();
        TestApplyAndMenu();
        TestPreviewOverlap();
        DestroySettingsChildControls();
        DestroyWindow(hSettings);
        hSettings = nullptr;
    } else {
        Require(false, "native Settings controls created");
    }
    widgets.clear();
    DeleteFileW(testXmlPath.c_str());
    SetThreadDesktop(previous);
    CloseDesktop(desktop);
    if (testFailures != 0) {
        return 1;
    }
    std::puts("PASS: native alarm Settings, validation, rebuild, XML, clipboard, and preview overlap");
    return 0;
}
