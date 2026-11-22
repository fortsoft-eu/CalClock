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
 * Last modified for version 1.7.3.0
 */

#define wmain AlarmSettingsRegressionEntry
#define StartNtpQueryThread TestStartNtpQueryThread
#include "AlarmSettingsTests.cpp"
#undef StartNtpQueryThread
#undef wmain

static HWND ntpTestNotifyWindow = nullptr;
static int ntpTestStarts = 0;
static bool ntpTestStartFails = false;
static ULONG ntpTestGeneration = 0;
static UINT ntpTestNotifyMessage = 0;
static std::wstring ntpTestServers;

/// Records the real request parameters without creating a worker or accessing the network.
HANDLE TestStartNtpQueryThread(const std::wstring& servers, ULONG generation, HWND notifyWindow,
        UINT notifyMessage, std::atomic<bool>* stopRequested, std::atomic<bool>* queryRunning) {
    Require(stopRequested != nullptr && queryRunning != nullptr, "worker receives live atomic flags");
    ntpTestStarts++;
    ntpTestServers = servers;
    ntpTestGeneration = generation;
    ntpTestNotifyWindow = notifyWindow;
    ntpTestNotifyMessage = notifyMessage;
    return ntpTestStartFails ? nullptr : CreateEventW(nullptr, TRUE, TRUE, nullptr);
}

/// Drains the private desktop's messages and avoids leaving the production refresh timer armed.
static void PumpNtpMessages() {
    MSG message = {};
    while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&message);
        DispatchMessageW(&message);
    }
    KillTimer(hController, TIMER_REFRESH);
}

/// Delivers native Settings notifications through the production dialog procedure.
static void NtpCommand(int id, int notification, HWND control) {
    SendMessageW(hSettings, WM_COMMAND, MAKEWPARAM(id, notification), reinterpret_cast<LPARAM>(control));
}

/// Changes the native server-preset combo and invokes its actual selection handler.
static void SelectNtpPreset(int preset) {
    SetComboSelection(hNtpPresetCombo, preset);
    NtpCommand(ID_NTP_PRESET, CBN_SELCHANGE, hNtpPresetCombo);
}

/// Uses the native edit and its production notification to classify a manually entered server list.
static void EnterNtpServers(const wchar_t* servers) {
    SetControlText(hNtpServersEdit, servers);
    NtpCommand(ID_NTP_SERVERS, EN_CHANGE, hNtpServersEdit);
}

/// Posts a completed query to the real controller without changing system time or network state.
static void CompleteNtpQuery(bool success, ULONG generation, const wchar_t* server, LONGLONG offset) {
    std::unique_ptr<NtpThreadResult> result = std::make_unique<NtpThreadResult>();
    result->generation = generation;
    result->success = success;
    result->server = server;
    result->offset100Nanoseconds = offset;
    result->clockOffset100Nanoseconds = static_cast<LONGLONG>(CurrentFileTimeValue())
        - static_cast<LONGLONG>(MonotonicFileTimeValue()) + offset;
    NtpQueryLogEntry entry;
    entry.server = server;
    entry.success = success;
    entry.completedTime = CurrentFileTimeValue();
    result->logEntries.push_back(entry);
    bool posted = PostMessageW(ntpTestNotifyWindow, ntpTestNotifyMessage, 0,
        reinterpret_cast<LPARAM>(result.get())) != FALSE;
    Require(posted, "query completion is posted to the production controller");
    if (posted) {
        result.release();
    }
    PumpNtpMessages();
}

/// Restores a valid applied preset while retaining the actual native Settings controls.
static void ResetNtpSettings(bool selectedNtp = true) {
    StopNtpSynchronization();
    KillTimer(hController, TIMER_REFRESH);
    ntpStopRequested = false;
    ntpTestStarts = 0;
    ntpTestStartFails = false;
    ntpTestServers.clear();
    ntpSynchronizationLog.clear();
    ListView_DeleteAllItems(hNtpLogList);
    ntpGeneration = 1;
    useNtpTime = selectedNtp;
    winsockReady = true;
    ntpPreset = NTP_PRESET_CESNET;
    ntpServers = NtpServersForPreset(ntpPreset);
    ntpTimeValid = false;
    ntpHasSynchronized = false;
    ntpLastQueryFailed = false;
    ntpActiveServer.clear();
    lastNtpAttemptTick = 0;
    nextNtpAttemptTick = 0;
    ntpOffset100Nanoseconds = 0;
    SetComboSelection(hTimeSourceCombo, selectedNtp ? 1 : 0);
    SelectNtpPreset(ntpPreset);
    UpdateNtpSettingsControls();
}

/// Sets only CalClock's continuous-clock correction so automatic hour-boundary tests are deterministic.
static void SetNtpTestTime(int minute, int second) {
    SYSTEMTIME utc = {};
    utc.wYear = 2026;
    utc.wMonth = 11;
    utc.wDay = 21;
    utc.wHour = 12;
    utc.wMinute = static_cast<WORD>(minute);
    utc.wSecond = static_cast<WORD>(second);
    SYSTEMTIME local = {};
    Require(SystemTimeToTzSpecificLocalTime(nullptr, &utc, &local) != FALSE, "test local time converts");
    local.wMinute = static_cast<WORD>(minute);
    local.wSecond = static_cast<WORD>(second);
    Require(TzSpecificLocalTimeToSystemTime(nullptr, &local, &utc) != FALSE, "test UTC converts");
    FILETIME file = {};
    Require(SystemTimeToFileTime(&utc, &file) != FALSE, "test FILETIME converts");
    ULARGE_INTEGER ticks = {};
    ticks.LowPart = file.dwLowDateTime;
    ticks.HighPart = file.dwHighDateTime;
    ntpClockOffset100Nanoseconds = static_cast<LONGLONG>(ticks.QuadPart)
        - static_cast<LONGLONG>(MonotonicFileTimeValue());
    ntpTimeValid = true;
    ntpHasSynchronized = true;
    ntpActiveServer = L"previous.example";
}

/// Covers presets, custom input, missing networking, the Windows source, and unsaved selection changes.
static void TestNtpAvailability() {
    ResetNtpSettings();
    std::wstring applied = ntpServers;
    for (int preset = 0; preset < NTP_PRESET_COUNT; preset++) {
        SelectNtpPreset(preset);
        Require(IsWindowEnabled(hNtpSyncButton), "every valid preset enables Sync without Apply");
        Require(ntpServers == applied, "selecting a preset alone does not apply it");
    }
    EnterNtpServers(L" ; , \t ");
    Require(!IsWindowEnabled(hNtpSyncButton), "separator-only servers disable Sync");
    Require(SendMessageW(hNtpPresetCombo, CB_GETCURSEL, 0, 0) == NTP_PRESET_CUSTOM,
        "editing a built-in list switches to Custom");
    std::wstring tooLong(254, L'a');
    EnterNtpServers(tooLong.c_str());
    Require(!IsWindowEnabled(hNtpSyncButton), "a list without an accepted server disables Sync");
    EnterNtpServers(L"alpha.example; beta.example");
    Require(IsWindowEnabled(hNtpSyncButton), "valid custom input reenables Sync");
    winsockReady = false;
    UpdateNtpSettingsControls();
    Require(!IsWindowEnabled(hNtpSyncButton), "missing Winsock disables Sync");
    winsockReady = true;
    SetComboSelection(hTimeSourceCombo, 0);
    NtpCommand(ID_TIME_SOURCE, CBN_SELCHANGE, hTimeSourceCombo);
    Require(!IsWindowEnabled(hNtpSyncButton), "Windows time disables Sync");
    Require(!IsWindowEnabled(hNtpPresetCombo) && !IsWindowEnabled(hNtpServersEdit),
        "Windows time disables NTP options");
}

/// Exercises every Settings combo through tentative navigation, periodic reads and cancellation.
static void TestSettingsComboHighlights() {
    ResetNtpSettings();
    std::vector<HWND> controls{ hAddType };
    for (const std::vector<HWND>* group : settingsControlGroups) {
        for (HWND control : *group) {
            controls.push_back(control);
        }
    }
    int tested = 0;
    for (HWND control : controls) {
        wchar_t className[32] = {};
        GetClassNameW(control, className, ARRAYSIZE(className));
        if (_wcsicmp(className, WC_COMBOBOXEXW) != 0 && _wcsicmp(className, WC_COMBOBOXW) != 0) {
            continue;
        }
        int notification = CBN_DROPDOWN;
        HandleSettingsComboNotification(control, &notification);
        int original = GetSettingsComboSelection(control);
        int count = static_cast<int>(SendMessageW(control, CB_GETCOUNT, 0, 0));
        if (count > 1) {
            WidgetConfig before = settingsDraft[0];
            ReadWidgetControls(before, false);
            bool pending = HasPendingSettingsChanges();
            bool syncEnabled = IsWindowEnabled(hNtpSyncButton) != FALSE;
            std::wstring servers = GetControlText(hNtpServersEdit);
            int candidate = original == 0 ? 1 : 0;
            SetComboSelection(control, candidate);
            notification = CBN_SELCHANGE;
            Require(HandleSettingsComboNotification(control, &notification),
                "every Settings dropdown defers tentative selection notifications");
            for (int tick = 0; tick < 3; tick++) {
                UpdateNtpSettingsControls();
                UpdateSettingControlAvailability(false);
                UpdateTimeSignalVolumePreview();
                UpdateSettingsApplyButton();
            }
            WidgetConfig after = settingsDraft[0];
            ReadWidgetControls(after, false);
            Require(WidgetConfigurationsEqual(before, after),
                "tentative Settings highlights cannot enter a widget draft");
            Require(GetSettingsComboSelection(control) == original
                    && GetApplicationComboSelection(GetSettingsComboBox(control), settingsComboState) == original,
                "outer and inner combos expose only the accepted selection");
            Require(HasPendingSettingsChanges() == pending,
                "tentative Settings highlights do not create pending changes");
            Require((IsWindowEnabled(hNtpSyncButton) != FALSE) == syncEnabled
                    && GetControlText(hNtpServersEdit) == servers,
                "refreshing an open Settings combo preserves accepted NTP controls");
            tested++;
        }
        notification = CBN_SELENDCANCEL;
        HandleSettingsComboNotification(control, &notification);
        notification = CBN_CLOSEUP;
        Require(HandleSettingsComboNotification(control, &notification),
            "cancelled Settings dropdowns do not emit an accepted change");
        Require(GetSettingsComboSelection(control) == original,
            "every cancelled Settings dropdown restores its accepted selection");
    }
    Require(tested >= 15, "the complete multi-page Settings combo inventory is exercised");
    std::printf("Settings dropdowns checked: %d.\n", tested);
}

/// Keeps periodic NTP availability updates independent of unconfirmed dropdown highlights in both directions.
static void TestNtpTimeSourceHighlight() {
    for (bool selectedNtp : { true, false }) {
        ResetNtpSettings(selectedNtp);
        int original = selectedNtp ? 1 : 0;
        int proposed = selectedNtp ? 0 : 1;
        NtpCommand(ID_TIME_SOURCE, CBN_DROPDOWN, hTimeSourceCombo);
        SetComboSelection(hTimeSourceCombo, proposed);
        NtpCommand(ID_TIME_SOURCE, CBN_SELCHANGE, hTimeSourceCombo);
        for (int update = 0; update < 3; update++) {
            UpdateNtpSettingsControls();
            bool presetEnabled = IsWindowEnabled(hNtpPresetCombo) != FALSE;
            bool serversEnabled = IsWindowEnabled(hNtpServersEdit) != FALSE;
            bool syncEnabled = IsWindowEnabled(hNtpSyncButton) != FALSE;
            Require(presetEnabled == selectedNtp
                    && serversEnabled == selectedNtp
                    && syncEnabled == selectedNtp,
                "periodic refresh ignores the highlighted time source until it is accepted");
        }
        NtpCommand(ID_TIME_SOURCE, CBN_SELENDCANCEL, hTimeSourceCombo);
        NtpCommand(ID_TIME_SOURCE, CBN_CLOSEUP, hTimeSourceCombo);
        UpdateNtpSettingsControls();
        Require(SendMessageW(hTimeSourceCombo, CB_GETCURSEL, 0, 0) == original,
            "cancelled time-source navigation restores the original selection");
        Require(IsNtpTimeSourceSelected() == selectedNtp,
            "cancelled navigation retains the accepted time-source draft");
        NtpCommand(ID_TIME_SOURCE, CBN_DROPDOWN, hTimeSourceCombo);
        SetComboSelection(hTimeSourceCombo, proposed);
        NtpCommand(ID_TIME_SOURCE, CBN_SELENDOK, hTimeSourceCombo);
        UpdateNtpSettingsControls();
        Require(IsNtpTimeSourceSelected() == selectedNtp,
            "the accepted highlight is deferred until the dropdown finishes closing");
        NtpCommand(ID_TIME_SOURCE, CBN_CLOSEUP, hTimeSourceCombo);
        bool presetEnabled = IsWindowEnabled(hNtpPresetCombo) != FALSE;
        bool serversEnabled = IsWindowEnabled(hNtpServersEdit) != FALSE;
        bool syncEnabled = IsWindowEnabled(hNtpSyncButton) != FALSE;
        Require(presetEnabled != selectedNtp
                && serversEnabled != selectedNtp
                && syncEnabled != selectedNtp,
            "closing an accepted time source updates all dependent controls");
        Require(useNtpTime == selectedNtp && ntpTestStarts == 0,
            "choosing a time-source draft neither applies it nor starts synchronization");
    }
}

/// Verifies the visible selection is used while pending drafts on other tabs remain unapplied.
static void TestNtpManualSelection() {
    ResetNtpSettings();
    SetNtpTestTime(30, 0);
    LONGLONG retained = ntpClockOffset100Nanoseconds.load();
    std::wstring originalName = widgets[0]->config.name;
    settingsDraft[0].name = L"Unapplied widget name";
    SetControlText(hNameEdit, settingsDraft[0].name.c_str());
    SelectNtpPreset(NTP_PRESET_PTB);
    NtpCommand(ID_NTP_SYNC, BN_CLICKED, hNtpSyncButton);
    Require(ntpTestStarts == 1 && ntpTestServers == NtpServersForPreset(NTP_PRESET_PTB),
        "Sync starts the newly selected preset instead of the previously applied servers");
    Require(ntpPreset == NTP_PRESET_PTB && testSavedSnapshot.ntpPreset == NTP_PRESET_PTB,
        "manual Sync persists only the selected NTP preferences");
    Require(widgets[0]->config.name == originalName && testSavedSnapshot.widgets[0].name == originalName,
        "manual Sync does not apply another tab's pending widget change");
    Require(settingsDraft[0].name == L"Unapplied widget name", "manual Sync retains the pending draft");
    Require(ntpTimeValid && ntpClockOffset100Nanoseconds == retained,
        "a server change retains the accepted time until a new result arrives");
    Require(!IsWindowEnabled(hNtpSyncButton) && IsWindowEnabled(hNtpPresetCombo),
        "busy Sync is disabled while server selection remains editable");
    Require(nextNtpAttemptTick - lastNtpAttemptTick == 10ULL * 60 * 1000,
        "refresh failures after an accepted time use the ten-minute retry interval");
    NtpCommand(ID_NTP_SYNC, BN_CLICKED, hNtpSyncButton);
    Require(ntpTestStarts == 1, "a second manual click cannot start an overlapping query");
    CompleteNtpQuery(false, ntpTestGeneration, L"failed.example", 0);
    Require(ntpTimeValid && ntpLastQueryFailed && ntpClockOffset100Nanoseconds == retained,
        "a failed refresh preserves the last valid correction");
    Require(IsWindowEnabled(hNtpSyncButton), "failed query completion reenables manual Sync");
    Require(GetControlText(hNtpStatus).find(T(TXT_NTP_STATUS_RETAINED)) == 0,
        "failure with accepted time displays the retained-time status");
    EnterNtpServers(L"custom-one.example; custom-two.example");
    NtpCommand(ID_NTP_SYNC, BN_CLICKED, hNtpSyncButton);
    Require(ntpPreset == NTP_PRESET_CUSTOM
            && ntpTestServers == L"custom-one.example; custom-two.example",
        "manual Sync passes the exact custom list to the worker");
    CompleteNtpQuery(true, ntpTestGeneration, L"custom-one.example", 12345000);
    Require(ntpTimeValid && !ntpLastQueryFailed && ntpActiveServer == L"custom-one.example",
        "successful completion updates the active server and validity");
    Require(ntpOffset100Nanoseconds == 12345000 && IsWindowEnabled(hNtpSyncButton),
        "successful completion updates the correction and reenables Sync");
    Require(ListView_GetItemCount(hNtpLogList) == 2, "success and failure both reach the native query log");
    settingsDraft[0] = widgets[0]->config;
    LoadDraftIntoControls();
}

/// Checks initial failures, worker-creation failure, and immediate activation from the Windows source.
static void TestNtpFirstSynchronization() {
    ResetNtpSettings(false);
    SetComboSelection(hTimeSourceCombo, 1);
    NtpCommand(ID_TIME_SOURCE, CBN_SELCHANGE, hTimeSourceCombo);
    NtpCommand(ID_NTP_SYNC, BN_CLICKED, hNtpSyncButton);
    Require(useNtpTime && ntpTestStarts == 1, "manual Sync activates the selected NTP source without Apply");
    Require(nextNtpAttemptTick - lastNtpAttemptTick == 60000,
        "the first synchronization retries after one minute");
    CompleteNtpQuery(false, ntpTestGeneration, L"failed.example", 0);
    Require(!ntpTimeValid && ntpLastQueryFailed && IsWindowEnabled(hNtpSyncButton),
        "initial network failure keeps the fallback clock and permits retry");
    ntpTestStartFails = true;
    NtpCommand(ID_NTP_SYNC, BN_CLICKED, hNtpSyncButton);
    Require(!ntpQueryRunning && ntpLastQueryFailed && IsWindowEnabled(hNtpSyncButton),
        "worker-creation failure leaves manual Sync available");
}

/// Exercises stale replies after Apply, including changing servers and switching back to Windows time.
static void TestNtpStaleResults() {
    ResetNtpSettings();
    SetNtpTestTime(30, 0);
    NtpCommand(ID_NTP_SYNC, BN_CLICKED, hNtpSyncButton);
    ULONG previousGeneration = ntpTestGeneration;
    LONGLONG previousCorrection = ntpClockOffset100Nanoseconds.load();
    SelectNtpPreset(NTP_PRESET_GLOBAL);
    ApplySettingsDraft();
    Require(ntpPreset == NTP_PRESET_GLOBAL && testSavedSnapshot.ntpPreset == NTP_PRESET_GLOBAL,
        "normal Apply accepts and saves a new preset during a query");
    Require(ntpTestStarts == 1, "Apply cannot overlap the running query");
    CompleteNtpQuery(true, previousGeneration, L"obsolete.example", 99999999);
    Require(ntpTestStarts == 2 && ntpTestServers == NtpServersForPreset(NTP_PRESET_GLOBAL),
        "the obsolete reply starts a replacement query with the new settings");
    Require(ntpClockOffset100Nanoseconds == previousCorrection,
        "the obsolete success cannot overwrite the accepted correction");
    previousGeneration = ntpTestGeneration;
    SetComboSelection(hTimeSourceCombo, 0);
    NtpCommand(ID_TIME_SOURCE, CBN_SELCHANGE, hTimeSourceCombo);
    ApplySettingsDraft();
    Require(!useNtpTime && !testSavedSnapshot.useNtpTime,
        "normal Apply switches and saves the source back to Windows");
    CompleteNtpQuery(true, previousGeneration, L"obsolete.example", 99999999);
    Require(!useNtpTime && !ntpTimeValid && !ntpQueryRunning && ntpTestStarts == 2,
        "an obsolete result after disabling NTP cannot restart or reenable it");
    Require(!IsWindowEnabled(hNtpSyncButton), "Windows source stays disabled after the obsolete reply");
}

/// Verifies manual bypass of hour postponement and UI refresh after an automatic or undeliverable query.
static void TestNtpAutomaticRefresh() {
    ResetNtpSettings();
    SetNtpTestTime(59, 58);
    StartNtpSynchronization(true);
    Require(ntpTestStarts == 0 && nextNtpAttemptTick > GetTickCount64(),
        "automatic synchronization is postponed around the hour");
    NtpCommand(ID_NTP_SYNC, BN_CLICKED, hNtpSyncButton);
    Require(ntpTestStarts == 1, "manual synchronization bypasses hour postponement");
    CompleteNtpQuery(true, ntpTestGeneration, L"accepted.example", 0);
    ResetNtpSettings();
    SetNtpTestTime(30, 0);
    SendMessageW(hController, WM_TIMER, TIMER_REFRESH, 0);
    KillTimer(hController, TIMER_REFRESH);
    Require(ntpQueryRunning && !IsWindowEnabled(hNtpSyncButton),
        "an automatic query disables the native Sync button");
    ntpQueryRunning = false;
    nextNtpAttemptTick = GetTickCount64() + 60000;
    SendMessageW(hController, WM_TIMER, TIMER_REFRESH, 0);
    KillTimer(hController, TIMER_REFRESH);
    Require(IsWindowEnabled(hNtpSyncButton),
        "the UI recovers when a worker ends without delivering a completion message");
    ResetNtpSettings();
}

/// Reopens the actual Time page while a query runs and verifies completion updates the new controls.
static void TestNtpReopen() {
    ResetNtpSettings();
    SetNtpTestTime(30, 0);
    NtpCommand(ID_NTP_SYNC, BN_CLICKED, hNtpSyncButton);
    DestroySettingsChildControls();
    DestroyWindow(hSettings);
    hSettings = CreateSettingsDialog(IDD_SETTINGS, nullptr, SettingsDialogProc, 0);
    Require(hSettings != nullptr && CreateSettingsControls(4), "the Time page reopens during a query");
    Require(!IsWindowEnabled(hNtpSyncButton), "a reopened Time page reflects the active query");
    Require(GetControlText(hNtpServersEdit) == ntpTestServers, "reopening retains the manually used servers");
    CompleteNtpQuery(true, ntpTestGeneration, L"reopened.example", 0);
    Require(IsWindowEnabled(hNtpSyncButton) && ntpActiveServer == L"reopened.example",
        "the pending completion updates the newly created Time page");
    Require(ListView_GetItemCount(hNtpLogList) == 1, "the reopened query log receives the completion");
    ResetNtpSettings();
}

/// Runs the real Time page and handlers on an unshown private desktop with inert input and storage.
int wmain(int argc, wchar_t** argv) {
    if (argc != 2) {
        return 2;
    }
    testXmlPath = argv[1];
    HDESK previous = GetThreadDesktop(GetCurrentThreadId());
    std::wstring name = L"CalClockNtpSettingsTests-" + std::to_wstring(GetCurrentProcessId());
    HDESK desktop = CreateDesktopW(name.c_str(), nullptr, nullptr, 0, GENERIC_ALL, nullptr);
    if (desktop == nullptr || !SetThreadDesktop(desktop)) {
        std::fprintf(stderr, "Cannot create isolated NTP desktop: %lu\n", GetLastError());
        if (desktop != nullptr) {
            CloseDesktop(desktop);
        }
        return 2;
    }
    INITCOMMONCONTROLSEX common = {};
    common.dwSize = sizeof(common);
    common.dwICC = ICC_WIN95_CLASSES | ICC_STANDARD_CLASSES | ICC_USEREX_CLASSES;
    InitCommonControlsEx(&common);
    hInstance = GetModuleHandleW(nullptr);
    appLanguage = LANG_EN_US;
    useNtpTime = false;
    winsockReady = false;
    LoadTimeZones();
    std::unique_ptr<Widget> widget = std::make_unique<Widget>();
    widget->config = DefaultConfig(WIDGET_DIGITAL, 0);
    widget->config.visible = false;
    widget->config.alarmEnabled = false;
    settingsDraft.push_back(widget->config);
    widgets.push_back(std::move(widget));
    settingsAppliedWidgets = settingsDraft;
    settingsAppearanceOriginals = settingsDraft;
    selectedDraftIndex = 0;
    settingsTab = 4;
    hController = TestCreateWindowExW(WS_EX_NOACTIVATE, L"STATIC", L"", WS_POPUP,
        0, 0, 1, 1, HWND_MESSAGE, nullptr, hInstance, nullptr);
    Require(hController != nullptr, "the isolated NTP controller is created");
    SetWindowLongPtrW(hController, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WindowProc));
    hSettings = CreateSettingsDialog(IDD_SETTINGS, nullptr, SettingsDialogProc, 0);
    Require(hSettings != nullptr && CreateSettingsControls(4), "real Settings controls are created");
    if (hSettings != nullptr && hNtpSyncButton != nullptr) {
        Require(!IsWindowVisible(hSettings)
                && (GetWindowLongPtrW(hSettings, GWL_EXSTYLE) & WS_EX_NOACTIVATE) != 0,
            "Settings remains hidden and nonactivating on the private desktop");
        TestNtpAvailability();
        TestSettingsComboHighlights();
        TestNtpTimeSourceHighlight();
        TestNtpManualSelection();
        TestNtpFirstSynchronization();
        TestNtpStaleResults();
        TestNtpAutomaticRefresh();
        TestNtpReopen();
        StopNtpSynchronization();
        DestroySettingsChildControls();
        DestroyWindow(hSettings);
        hSettings = nullptr;
    }
    HWND controller = hController;
    hController = nullptr;
    DestroyWindow(controller);
    for (const std::unique_ptr<Widget>& current : widgets) {
        DestroyWidgetWindow(current.get());
    }
    widgets.clear();
    SetThreadDesktop(previous);
    CloseDesktop(desktop);
    if (testFailures != 0) {
        return 1;
    }
    std::puts("PASS: native NTP Settings, unsaved server selection, busy/failure states and stale replies.");
    return 0;
}
