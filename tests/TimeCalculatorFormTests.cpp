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
 * Last modified for version 1.7.1.3
 */

#define wmain AlarmSettingsRegressionEntry
#include "AlarmSettingsTests.cpp"
#undef wmain

struct CalculatorThreadCall {
    LPTHREAD_START_ROUTINE procedure;
    void* parameter;
};

struct CalculatorPaintRecord {
    HWND window = nullptr;
    std::wstring text;
    int paints = 0;
};

static HANDLE calculatorWorkerGate = nullptr;
static DWORD calculatorGuiThread = 0;
static std::atomic<int> calculatorWorkers = 0;
static std::atomic<bool> calculatorWorkerOnGui = false;
static bool calculatorWaiting = false;
static void WaitForCalculator();
static void LoadCalculator(const TimeCalculatorState& state);
static void RefreshCalculator();
static void ShowCalculator();
static bool calculatorSmallWorkArea = false;
static bool calculatorPresented = false;
static int calculatorAnswer = IDYES;
static bool calculatorLoadOnConfirmation = false;
static TimeCalculatorState calculatorConfirmationState;
static HWND calculatorExpectedFocus = nullptr;
static std::wstring calculatorArtifacts;
static HWND calculatorNavigationTarget = nullptr;
static bool calculatorShiftPressed = false;
static int calculatorPresetWrites = 0;
static bool calculatorPresetWriteFails = false;

/// Holds worker execution behind a test gate without blocking the GUI message queue.
static DWORD WINAPI CalculatorThreadEntry(void* parameter) {
    std::unique_ptr<CalculatorThreadCall> call(static_cast<CalculatorThreadCall*>(parameter));
    if (GetCurrentThreadId() == calculatorGuiThread) {
        calculatorWorkerOnGui.store(true);
    }
    WaitForSingleObject(calculatorWorkerGate, INFINITE);
    DWORD result = call->procedure(call->parameter);
    calculatorWorkers.fetch_sub(1);
    return result;
}

/// Tracks actual calculator worker lifetimes while preserving the production native thread creation.
static HANDLE WINAPI CalculatorCreateThread(LPSECURITY_ATTRIBUTES attributes, SIZE_T stackSize,
        LPTHREAD_START_ROUTINE procedure, LPVOID parameter, DWORD flags, LPDWORD threadId) {
    std::unique_ptr<CalculatorThreadCall> call = std::make_unique<CalculatorThreadCall>();
    call->procedure = procedure;
    call->parameter = parameter;
    calculatorWorkers.fetch_add(1);
    HANDLE thread = CreateThread(attributes, stackSize, CalculatorThreadEntry, call.get(), flags, threadId);
    if (thread != nullptr) {
        call.release();
    } else {
        calculatorWorkers.fetch_sub(1);
    }
    return thread;
}

/// Prevents activation and gives native picker popups nonactivating style before they are created.
static LRESULT CALLBACK CalculatorPopupIsolation(int code, WPARAM wParam, LPARAM lParam) {
    if (code == HCBT_CREATEWND) {
        HWND window = reinterpret_cast<HWND>(wParam);
        SetWindowLongPtrW(window, GWL_EXSTYLE, GetWindowLongPtrW(window, GWL_EXSTYLE) | WS_EX_NOACTIVATE);
    }
    if (code == HCBT_ACTIVATE || code == HCBT_SETFOCUS) {
        return 1;
    }
    return CallNextHookEx(nullptr, code, wParam, lParam);
}

/// Keeps calculator user data inside this test's artifact directory rather than the user's AppData.
static std::wstring CalculatorTestPresetsPath(bool createDirectory) {
    UNREFERENCED_PARAMETER(createDirectory);
    return calculatorArtifacts + L"\\times-isolated.xml";
}

/// Exercises actual XML writes while allowing deterministic failure without changing the real user file.
static bool CalculatorTestWritePresets(const std::wstring& path,
        const std::vector<TimeCalculatorPreset>& presets) {
    calculatorPresetWrites++;
    return !calculatorPresetWriteFails && WriteCalculatorPresets(path, presets);
}

/// Preserves a deliberately presented capture window while retaining nonactivation and hidden default
/// testing.
static BOOL WINAPI CalculatorSetWindowPos(HWND window, HWND after, int x, int y, int width, int height,
        UINT flags) {
    flags |= SWP_NOACTIVATE;
    if (!calculatorPresented && (GetWindowLongPtrW(window, GWL_STYLE) & WS_CHILD) == 0) {
        flags = flags & ~SWP_SHOWWINDOW | SWP_HIDEWINDOW;
    }
    return SetWindowPos(window, after, x, y, width, height, flags);
}
/// Captures requested focus without changing any real input queue or active window.
static HWND WINAPI CalculatorSetFocus(HWND control) {
    calculatorExpectedFocus = control;
    return nullptr;
}

/// Returns an explicit test response while keeping confirmation dialogs off every desktop.
static int WINAPI CalculatorMessageBox(HWND owner, LPCWSTR text, LPCWSTR title, UINT type) {
    testMessageCalls++;
    if (calculatorLoadOnConfirmation) {
        calculatorLoadOnConfirmation = false;
        LoadCalculator(calculatorConfirmationState);
    }
    return calculatorAnswer;
}

/// Restricts only the calculator's reported work area without changing monitor configuration.
static BOOL WINAPI CalculatorMonitorInfo(HMONITOR monitor, LPMONITORINFO information) {
    BOOL result = GetMonitorInfoW(monitor, information);
    if (result && calculatorSmallWorkArea) {
        information->rcWork.right = information->rcWork.left + 480;
        information->rcWork.bottom = information->rcWork.top + 320;
    }
    return result;
}

/// Supplies test modifiers without changing the desktop keyboard state.
static SHORT WINAPI CalculatorGetKeyState(int key) {
    if (key == VK_SHIFT) {
        return calculatorShiftPressed ? static_cast<SHORT>(0x8000) : 0;
    }
    return 0;
}

#define GetKeyState CalculatorGetKeyState
#define SetFocus CalculatorSetFocus
#define SetActiveWindow TestSetActiveWindow
#define SetForegroundWindow TestWindowActivation
#define BringWindowToTop TestWindowActivation
#define AttachThreadInput TestAttachThreadInput
#define AllowSetForegroundWindow TestAllowSetForegroundWindow
#define ShowWindow TestShowWindow
#define SetWindowPos CalculatorSetWindowPos
#define DeferWindowPos TestDeferWindowPos
#define CreateWindowExW TestCreateWindowExW
#define CreateDialogIndirectParamW TestCreateDialogIndirectParamW
#define MessageBoxW CalculatorMessageBox
#define GetMonitorInfoW CalculatorMonitorInfo
#include "../CalClock/PersistWindowState.cpp"
#define CalculatorPresetsPath CalculatorTestPresetsPath
#define WriteCalculatorPresets CalculatorTestWritePresets
#define CreateThread CalculatorCreateThread
#include "../CalClock/TimeCalculatorForm.cpp"
#undef CreateThread
#undef CalculatorPresetsPath
#undef WriteCalculatorPresets
#undef GetKeyState
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
#undef MessageBoxW
#undef GetMonitorInfoW

/// Pumps only the isolated test desktop until workers and their posted completions have drained.
static void WaitForCalculator() {
    if (calculatorWaiting) {
        return;
    }
    calculatorWaiting = true;
    ULONGLONG deadline = GetTickCount64() + 15000;
    int idle = 0;
    while (idle < 2 && GetTickCount64() < deadline) {
        MSG message = {};
        bool dispatched = false;
        while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessageW(&message);
            dispatched = true;
        }
        if (calculatorWorkers.load() == 0 && !dispatched) {
            idle++;
        } else {
            idle = 0;
        }
        Sleep(1);
    }
    Require(idle == 2, "calculator background work and posted results finish without deadlocking the dialog");
    Require(!calculatorWorkerOnGui.load(), "calculator calculations execute outside the GUI thread");
    calculatorWaiting = false;
}

/// Restores inputs and waits for their asynchronous results before inspecting them.
static void LoadCalculator(const TimeCalculatorState& state) {
    calculatorForm.Load(state);
    WaitForCalculator();
}

/// Refreshes localized controls and drains their background calculations.
static void RefreshCalculator() {
    calculatorForm.Refresh();
    WaitForCalculator();
}

/// Opens a nonactivating calculator and waits only inside the test for its background preparation.
static void ShowCalculator() {
    calculatorForm.Show(hInstance, calculatorWindowState);
    WaitForCalculator();
}

/// Locates one calculator control by its resource ID without depending on private form members.
static HWND CalculatorControl(int id) {
    WaitForCalculator();
    HWND dialog = calculatorForm.GetWindow();
    HWND direct = GetDlgItem(dialog, id);
    if (direct != nullptr) {
        return direct;
    }
    HWND child = GetWindow(dialog, GW_CHILD);
    while (child != nullptr) {
        HWND control = GetDlgItem(child, id);
        if (control != nullptr) {
            return control;
        }
        child = GetWindow(child, GW_HWNDNEXT);
    }
    return nullptr;
}

/// Returns the native description edit inside the production clipped viewport.
static HWND CalculatorDescriptionEdit() {
    HWND edit = SettingsEdit::GetEdit(CalculatorControl(ID_CALC_DESCRIPTION));
    Require(edit != nullptr, "calculator description uses the native edit viewport");
    return edit;
}
/// Creates a minute-resolution local timestamp for deterministic form scenarios.
static SYSTEMTIME CalculatorDate(WORD year, WORD month, WORD day, WORD hour = 0, WORD minute = 0) {
    SYSTEMTIME value = {};
    value.wYear = year;
    value.wMonth = month;
    value.wDay = day;
    value.wHour = hour;
    value.wMinute = minute;
    TimeCalculator::Normalize(&value);
    return value;
}

/// Sets native date fields and dispatches the user-change notification not emitted by DTM_SETSYSTEMTIME.
static void ChangeCalculatorDate(int id, const SYSTEMTIME& time) {
    HWND picker = CalculatorControl(id);
    Require(DateTime_SetSystemtime(picker, GDT_VALID, &time) != FALSE, "native picker date changed");
    NMDATETIMECHANGE change = {};
    change.nmhdr = NMHDR{ picker, static_cast<UINT_PTR>(id), DTN_DATETIMECHANGE };
    change.dwFlags = GDT_VALID;
    change.st = time;
    SendMessageW(GetParent(picker), WM_NOTIFY, id, reinterpret_cast<LPARAM>(&change));
    WaitForCalculator();
}

/// Compares persisted calculator inputs and records independently of native control geometry.
static bool SameCalculatorState(const TimeCalculatorState& first, const TimeCalculatorState& second) {
    if (CompareCalculatorDates(first.from, second.from) != 0
            || CompareCalculatorDates(first.to, second.to) != 0
            || CompareCalculatorDates(first.start, second.start) != 0
            || CompareCalculatorDates(first.day, second.day) != 0
            || first.fromNow != second.fromNow
            || first.toNow != second.toNow
            || first.tab != second.tab
            || first.highlights != second.highlights
            || first.fromZone != second.fromZone
            || first.toZone != second.toZone
            || first.startZone != second.startZone) {
        return false;
    }
    return true;
}

/// Sends a native control notification without clicking, focusing or injecting user input.
static void CalculatorCommand(int id, int code = BN_CLICKED) {
    HWND control = CalculatorControl(id);
    Require(control != nullptr, "calculator command target exists");
    SendMessageW(GetParent(control), WM_COMMAND, MAKEWPARAM(id, code), reinterpret_cast<LPARAM>(control));
    WaitForCalculator();
}

/// Changes the selected tab through the same native notification used by the tab control.
static void CalculatorPage(int index) {
    HWND tabs = CalculatorControl(ID_CALC_TABS);
    TabCtrl_SetCurSel(tabs, index);
    NMHDR notification{ tabs, ID_CALC_TABS, TCN_SELCHANGE };
    SendMessageW(calculatorForm.GetWindow(), WM_NOTIFY, ID_CALC_TABS, reinterpret_cast<LPARAM>(&notification));
    Require(calculatorForm.GetState().tab == index, "native tab notification updates selected page");
    const int representatives[] = { ID_CALC_FROM, ID_CALC_CALENDAR, ID_CALC_LIST, ID_CALC_HIGHLIGHT_BASE };
    for (int page = 0; page < TIME_CALCULATOR_PAGE_COUNT; page++) {
        HWND parent = GetParent(CalculatorControl(representatives[page]));
        bool visible = (GetWindowLongPtrW(parent, GWL_STYLE) & WS_VISIBLE) != 0;
        Require(visible == (page == index), "only the selected child page has WS_VISIBLE");
    }
}

/// Exercises wheel delivery to inactive native tab headers on the unshown private test desktop.
static void TestInactiveTabWheel(HWND window, HWND tabs) {
    HWND foreground = GetForegroundWindow();
    HWND active = GetActiveWindow();
    HWND focus = GetFocus();
    RECT bounds = {};
    GetWindowRect(tabs, &bounds);
    calculatorPresented = true;
    SetWindowPos(window, HWND_TOP, 100, 100, 0, 0,
        SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
    SetWindowPos(tabs, nullptr, 0, 0, 130, bounds.bottom - bounds.top,
        SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
    RECT first = {};
    TabCtrl_GetItemRect(tabs, 0, &first);
    POINT point = { 8, first.top + (first.bottom - first.top) / 2 };
    ClientToScreen(tabs, &point);
    LPARAM position = MAKELPARAM(point.x, point.y);
    WPARAM down = MAKEWPARAM(0, static_cast<WORD>(-WHEEL_DELTA));
    WPARAM up = MAKEWPARAM(0, WHEEL_DELTA);
    Require(GetActiveWindow() != window, "dialog stays inactive during wheel test");
    SendMessageW(tabs, WM_MOUSEWHEEL, down, position);
    RECT scrolled = {};
    TabCtrl_GetItemRect(tabs, 0, &scrolled);
    Require(scrolled.left < first.left, "direct wheel delivery scrolls inactive headers under the pointer");
    MSG message = {};
    message.hwnd = tabs;
    message.message = WM_MOUSEWHEEL;
    message.wParam = up;
    message.lParam = position;
    bool handled = false;
    if (window == calculatorForm.GetWindow()) {
        handled = calculatorForm.ProcessMessage(&message);
    } else {
        handled = ScrollDialogTabHeaders(hSettings, hTabs, message.wParam, message.lParam);
    }
    Require(handled, "queued wheel input is handled without activation");
    RECT restored = {};
    TabCtrl_GetItemRect(tabs, 0, &restored);
    Require(restored.left > scrolled.left, "reverse wheel restores the header position");
    Require(TabCtrl_GetCurSel(tabs) == 0, "header scrolling does not change the selected page");
    point.y += 100;
    message.lParam = MAKELPARAM(point.x, point.y);
    Require(!ScrollDialogTabHeaders(window, tabs, down, message.lParam),
        "wheel input outside the header is not consumed by tab scrolling");
    Require(GetActiveWindow() == active && GetFocus() == focus && GetForegroundWindow() == foreground,
        "inactive tab scrolling preserves focus and active windows");
    SetWindowPos(window, nullptr, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_HIDEWINDOW);
    calculatorPresented = false;
    SetWindowPos(tabs, nullptr, 0, 0, bounds.right - bounds.left, bounds.bottom - bounds.top,
        SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
}

/// Verifies native focus-only owner-draw transitions without moving keyboard focus or changing the desktop.
static void TestComboFocusDrawing(HWND control) {
    LRESULT selection = SendMessageW(control, CB_GETCURSEL, 0, 0);
    if (selection == CB_ERR) {
        SendMessageW(control, CB_SETCURSEL, 0, 0);
    }
    HDC source = GetDC(control);
    HDC memory = CreateCompatibleDC(source);
    BITMAPINFO information = {};
    information.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    information.bmiHeader.biWidth = 240;
    information.bmiHeader.biHeight = -28;
    information.bmiHeader.biPlanes = 1;
    information.bmiHeader.biBitCount = 32;
    void* pixels = nullptr;
    HBITMAP bitmap = CreateDIBSection(source, &information, DIB_RGB_COLORS, &pixels, nullptr, 0);
    Require(memory != nullptr && bitmap != nullptr && pixels != nullptr, "combo focus test DC created");
    if (memory != nullptr && bitmap != nullptr && pixels != nullptr) {
        HGDIOBJ previous = SelectObject(memory, bitmap);
        RECT bounds = { 0, 0, 240, 28 };
        FillRect(memory, &bounds, GetSysColorBrush(COLOR_WINDOW));
        DRAWITEMSTRUCT item = {};
        item.CtlType = ODT_COMBOBOX;
        item.itemID = static_cast<UINT>(SendMessageW(control, CB_GETCURSEL, 0, 0));
        item.itemAction = ODA_DRAWENTIRE;
        item.itemState = ODS_COMBOBOXEDIT;
        item.hwndItem = GetSettingsComboBox(control);
        item.hDC = memory;
        item.rcItem = bounds;
        SendMessageW(control, WM_DRAWITEM, 0, reinterpret_cast<LPARAM>(&item));
        GdiFlush();
        const DWORD* first = static_cast<const DWORD*>(pixels);
        std::vector<DWORD> original(first, first + 240 * 28);
        item.itemAction = ODA_FOCUS;
        item.itemState |= ODS_FOCUS;
        SendMessageW(control, WM_DRAWITEM, 0, reinterpret_cast<LPARAM>(&item));
        GdiFlush();
        Require(!std::equal(original.begin(), original.end(), first), "focus gain draws the combo focus cue");
        item.itemState &= ~ODS_FOCUS;
        SendMessageW(control, WM_DRAWITEM, 0, reinterpret_cast<LPARAM>(&item));
        GdiFlush();
        Require(std::equal(original.begin(), original.end(), first), "focus loss removes the combo focus cue");
        SelectObject(memory, previous);
    }
    if (bitmap != nullptr) {
        DeleteObject(bitmap);
    }
    if (memory != nullptr) {
        DeleteDC(memory);
    }
    ReleaseDC(control, source);
    SendMessageW(control, CB_SETCURSEL, selection, 0);
}

/// Captures dialog-manager focus requests so tab-navigation tests never change actual keyboard focus.
static LRESULT CALLBACK CalculatorNavigationProbe(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    if (message == WM_NEXTDLGCTL) {
        Require(lParam == TRUE, "tab navigation names the intended control");
        calculatorNavigationTarget = reinterpret_cast<HWND>(wParam);
        return 0;
    }
    return DefSubclassProc(window, message, wParam, lParam);
}

/// Checks the real Settings tab route from ComboBoxEx children and verifies restored keyboard focus cues.
static void TestSettingsTabNavigation() {
    LoadAlarm(AlarmConfiguration(1));
    ShowSettingsTab(0);
    SetWindowSubclass(hSettings, CalculatorNavigationProbe, 1, 0);
    SetWindowPos(hSettings, nullptr, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_SHOWWINDOW);
    SetWindowPos(hGeneralPage, nullptr, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_SHOWWINDOW);
    HWND stops[] = { SettingsEdit::GetFrame(hNameEdit), hTypeCombo, hTimeZoneCombo };
    for (HWND control : stops) {
        SetWindowPos(control, nullptr, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_SHOWWINDOW);
    }
    SendMessageW(hSettings, WM_CHANGEUISTATE, MAKEWPARAM(UIS_SET, UISF_HIDEFOCUS), 0);
    std::vector<HWND> controls = GetSettingsTabOrder();
    Require(controls.size() > 1, "Settings native tab order is populated");
    for (size_t index = 0; index + 1 < controls.size(); index++) {
        MSG message = {};
        message.hwnd = GetSettingsComboBox(controls[index]);
        message.message = WM_KEYDOWN;
        message.wParam = VK_TAB;
        calculatorNavigationTarget = nullptr;
        Require(HandleSettingsTabNavigation(message), "Settings handles Tab from each page control");
        Require(calculatorNavigationTarget == controls[index + 1], "Tab retains the existing Settings order");
        Require((SendMessageW(hSettings, WM_QUERYUISTATE, 0, 0) & UISF_HIDEFOCUS) == 0,
            "Tab exposes native keyboard focus cues");
    }
    MSG foreign = {};
    foreign.hwnd = CalculatorControl(ID_CALC_ZONE_BASE);
    foreign.message = WM_KEYDOWN;
    foreign.wParam = VK_TAB;
    Require(!HandleSettingsTabNavigation(foreign), "Settings never intercepts calculator tab navigation");
    SetWindowPos(hSettings, nullptr, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_HIDEWINDOW);
    RemoveWindowSubclass(hSettings, CalculatorNavigationProbe, 1);
}

/// Verifies automatic combo metrics and pending dropdown choices through the shared native handlers.
static void TestComboHandling(HWND control, UINT_PTR subclassId) {
    DWORD_PTR reference = 0;
    Require(GetWindowSubclass(control, ApplicationControlSubclassProc, subclassId, &reference) != FALSE,
        "both dialogs install the complete shared control handler");
    HFONT originalFont = reinterpret_cast<HFONT>(SendMessageW(control, WM_GETFONT, 0, 0));
    LOGFONTW font = {};
    GetObjectW(originalFont, sizeof(font), &font);
    font.lfHeight = -40;
    HFONT tallFont = CreateFontIndirectW(&font);
    Require(tallFont != nullptr, "large font available for combo metric change");
    if (tallFont != nullptr) {
        SendMessageW(control, WM_SETFONT, reinterpret_cast<WPARAM>(tallFont), FALSE);
        HWND combo = GetSettingsComboBox(control);
        LRESULT fieldHeight = SendMessageW(combo, CB_GETITEMHEIGHT, static_cast<WPARAM>(-1), 0);
        LRESULT rowHeight = SendMessageW(combo, CB_GETITEMHEIGHT, 0, 0);
        UpdateSettingsComboMetrics(control);
        Require(fieldHeight == SendMessageW(combo, CB_GETITEMHEIGHT, static_cast<WPARAM>(-1), 0)
            && rowHeight == SendMessageW(combo, CB_GETITEMHEIGHT, 0, 0),
            "font change already applies field and dropdown metrics");
        SendMessageW(control, WM_THEMECHANGED, 0, 0);
        Require(rowHeight == SendMessageW(combo, CB_GETITEMHEIGHT, 0, 0),
            "theme change retains matching native row metrics");
        SendMessageW(control, WM_SETFONT, reinterpret_cast<WPARAM>(originalFont), FALSE);
        DeleteObject(tallFont);
    }
    LRESULT selection = SendMessageW(control, CB_GETCURSEL, 0, 0);
    SendMessageW(control, CB_SETCURSEL, 0, 0);
    ApplicationComboState state;
    int notification = CBN_DROPDOWN;
    Require(HandleApplicationComboNotification(control, &notification, state),
        "dropdown begins a pending choice");
    SendMessageW(control, CB_SETCURSEL, 1, 0);
    notification = CBN_SELCHANGE;
    Require(HandleApplicationComboNotification(control, &notification, state),
        "open dropdown defers selection");
    notification = CBN_SELENDCANCEL;
    HandleApplicationComboNotification(control, &notification, state);
    notification = CBN_CLOSEUP;
    Require(HandleApplicationComboNotification(control, &notification, state)
        && SendMessageW(control, CB_GETCURSEL, 0, 0) == 0 && state.open == nullptr,
        "cancel restores the original choice without applying a change");
    notification = CBN_DROPDOWN;
    HandleApplicationComboNotification(control, &notification, state);
    SendMessageW(control, CB_SETCURSEL, 1, 0);
    notification = CBN_SELENDOK;
    HandleApplicationComboNotification(control, &notification, state);
    notification = CBN_CLOSEUP;
    Require(!HandleApplicationComboNotification(control, &notification, state)
        && notification == CBN_SELCHANGE && state.open == nullptr,
        "accepted change is applied once after closing the dropdown");
    SendMessageW(control, CB_SETCURSEL, selection, 0);
}

/// Counts native static painting while retaining the production window procedure.
static LRESULT CALLBACK CalculatorPaintProbe(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    CalculatorPaintRecord* record = reinterpret_cast<CalculatorPaintRecord*>(referenceData);
    if (message == WM_PAINT || message == WM_ERASEBKGND) {
        record->paints++;
    }
    return DefSubclassProc(window, message, wParam, lParam);
}

/// Records every static, including unchanged units and explanatory notes, on the real calculator pages.
static BOOL CALLBACK CollectCalculatorStatics(HWND window, LPARAM parameter) {
    wchar_t name[32] = {};
    GetClassNameW(window, name, ARRAYSIZE(name));
    if (_wcsicmp(name, L"Static") == 0) {
        std::vector<CalculatorPaintRecord>* records =
            reinterpret_cast<std::vector<CalculatorPaintRecord>*>(parameter);
        records->push_back(CalculatorPaintRecord{ window, GetControlText(window), 0 });
    }
    return TRUE;
}

/// Verifies changed dates and presets do not repaint unchanged static text on any calculator page.
static void TestCalculatorUpdatePainting() {
    TimeCalculatorState original = calculatorForm.GetState();
    size_t originalCount = calculatorForm.GetPresets().size();
    TimeCalculatorPreset preset;
    preset.time = CalculatorDate(2025, 5, 10);
    preset.description = L"Paint regression preset";
    preset.zone = L"UTC+00:00";
    std::vector<TimeCalculatorPreset> imported = { preset };
    Require(calculatorForm.MergePresets(imported), "paint regression preset created in isolated storage");
    WaitForCalculator();
    HWND window = calculatorForm.GetWindow();
    calculatorPresented = true;
    for (int action = 0; action < 3; action++) {
        CalculatorPage(action == 2 ? 1 : 0);
        SetWindowPos(window, nullptr, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_SHOWWINDOW);
        WaitForCalculator();
        RedrawWindow(window, nullptr, nullptr,
            RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN | RDW_UPDATENOW);
        std::vector<CalculatorPaintRecord> records;
        EnumChildWindows(window, CollectCalculatorStatics, reinterpret_cast<LPARAM>(&records));
        for (CalculatorPaintRecord& record : records) {
            SetWindowSubclass(record.window, CalculatorPaintProbe, 1, reinterpret_cast<DWORD_PTR>(&record));
        }
        if (action == 0) {
            ChangeCalculatorDate(ID_CALC_TO, CalculatorDate(2026, 2, 1));
        } else if (action == 1) {
            HWND combo = CalculatorControl(ID_CALC_FROM_PRESET);
            SendMessageW(combo, CB_SETCURSEL, 0, 0);
            CalculatorCommand(ID_CALC_FROM_PRESET, CBN_SELCHANGE);
        } else {
            ChangeCalculatorDate(ID_CALC_START, CalculatorDate(2025, 6, 1));
        }
        WaitForCalculator();
        for (CalculatorPaintRecord& record : records) {
            if (GetControlText(record.window) == record.text) {
                Require(record.paints == 0,
                    "unchanged calculator statics are not repainted after input changes");
                if (record.paints != 0) {
                    std::printf("Action %d static %d: %d paint messages\n",
                        action, GetDlgCtrlID(record.window), record.paints);
                }
            }
            RemoveWindowSubclass(record.window, CalculatorPaintProbe, 1);
        }
    }
    SetWindowPos(window, nullptr, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_HIDEWINDOW);
    calculatorPresented = false;
    CalculatorPage(2);
    HWND list = CalculatorControl(ID_CALC_LIST);
    ListView_SetItemState(list, -1, 0, LVIS_SELECTED);
    for (int row = 0; row < ListView_GetItemCount(list); row++) {
        LVITEMW item = {};
        item.mask = LVIF_PARAM;
        item.iItem = row;
        if (ListView_GetItem(list, &item) && item.lParam == static_cast<LPARAM>(originalCount)) {
            ListView_SetItemState(list, row, LVIS_SELECTED, LVIS_SELECTED);
        }
    }
    int previousAnswer = calculatorAnswer;
    calculatorAnswer = IDOK;
    CalculatorCommand(ID_CALC_DELETE);
    calculatorAnswer = previousAnswer;
    Require(calculatorForm.GetPresets().size() == originalCount, "paint test removes its isolated preset");
    LoadCalculator(original);
}

/// Checks native forward and reverse tab traversal after layout, including the two digit columns.
static void TestCalculatorTabOrder() {
    const std::vector<std::vector<int>> orders = {
        {
            ID_CALC_FROM,
            ID_CALC_FROM_PRESET,
            ID_CALC_FROM_NOW,
            ID_CALC_ZONE_BASE,
            ID_CALC_OFFSET_BASE,
            ID_CALC_TO,
            ID_CALC_TO_PRESET,
            ID_CALC_TO_NOW,
            ID_CALC_ZONE_BASE + 1,
            ID_CALC_OFFSET_BASE + 1
        }, {
            ID_CALC_ZONE_BASE + 2,
            ID_CALC_OFFSET_BASE + 2,
            ID_CALC_CALENDAR,
            ID_CALC_START,
            ID_CALC_PRESET
        }, {
            ID_CALC_DATE,
            ID_CALC_ZONE_BASE + 3,
            ID_CALC_OFFSET_BASE + 3,
            ID_CALC_DESCRIPTION,
            ID_CALC_ADD,
            ID_CALC_EDIT,
            ID_CALC_DELETE,
            ID_CALC_CANCEL,
            ID_CALC_LIST
        }, {
            ID_CALC_HIGHLIGHT_BASE,
            ID_CALC_HIGHLIGHT_BASE + 1,
            ID_CALC_HIGHLIGHT_BASE + 2,
            ID_CALC_HIGHLIGHT_BASE + 3,
            ID_CALC_HIGHLIGHT_BASE + 4,
            ID_CALC_HIGHLIGHT_BASE + 5,
            ID_CALC_HIGHLIGHT_BASE + 6,
            ID_CALC_HIGHLIGHT_BASE + 7,
            ID_CALC_HIGHLIGHT_BASE + 8,
            ID_CALC_HIGHLIGHT_BASE + 9,
            ID_CALC_HIGHLIGHT_BASE + 10,
            ID_CALC_HIGHLIGHT_BASE + 11,
            ID_CALC_HIGHLIGHT_BASE + 12
        }
    };
    int originalPage = calculatorForm.GetState().tab;
    calculatorPresented = true;
    HWND window = calculatorForm.GetWindow();
    SetWindowPos(window, nullptr, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_SHOWWINDOW);
    for (int pageIndex = 0; pageIndex < TIME_CALCULATOR_PAGE_COUNT; pageIndex++) {
        CalculatorPage(pageIndex);
        const std::vector<int>& order = orders[pageIndex];
        HWND page = GetParent(CalculatorControl(order.front()));
        std::vector<BOOL> enabled;
        for (int id : order) {
            HWND control = CalculatorControl(id);
            enabled.push_back(IsWindowEnabled(control));
            EnableWindow(control, TRUE);
        }
        if (pageIndex == 3) {
            SetWindowSubclass(window, CalculatorNavigationProbe, 1, 0);
            for (int row = 0; row < 4; row++) {
                HWND left = CalculatorControl(ID_CALC_HIGHLIGHT_BASE + 4 + row);
                HWND right = CalculatorControl(ID_CALC_HIGHLIGHT_BASE + 9 + row);
                RECT covered = {};
                GetWindowRect(right, &covered);
                POINT screen = { covered.left + 2, (covered.top + covered.bottom) / 2 };
                LPARAM position = MAKELPARAM(screen.x, screen.y);
                Require(SendMessageW(left, WM_NCHITTEST, 0, position) == HTTRANSPARENT,
                    "left checkbox defers covered input to the right column");
                POINT local = screen;
                ScreenToClient(left, &local);
                HDC dc = GetDC(left);
                Require(dc != nullptr && !PtVisible(dc, local.x, local.y),
                    "native sibling clipping excludes the right checkbox from the left checkbox DC");
                if (dc != nullptr) {
                    ReleaseDC(left, dc);
                }
                LRESULT checked = SendMessageW(left, BM_GETCHECK, 0, 0);
                position = MAKELPARAM(local.x, local.y);
                SendMessageW(left, WM_LBUTTONDOWN, MK_LBUTTON, position);
                SendMessageW(left, WM_LBUTTONUP, 0, position);
                Require(SendMessageW(left, BM_GETCHECK, 0, 0) == checked,
                    "covered mouse clicks cannot toggle the left checkbox");
            }
        }
        for (BOOL backwards : { FALSE, TRUE }) {
            HWND current = backwards ? CalculatorControl(order.front()) : nullptr;
            if (pageIndex == 3) {
                current = CalculatorControl(ID_CALC_TABS);
            }
            calculatorShiftPressed = backwards != FALSE;
            for (size_t index = 0; index < order.size(); index++) {
                size_t position = backwards ? order.size() - index - 1 : index;
                HWND expected = CalculatorControl(order[position]);
                if (pageIndex == 3) {
                    MSG message = {};
                    message.hwnd = current;
                    message.message = WM_KEYDOWN;
                    message.wParam = VK_TAB;
                    calculatorNavigationTarget = nullptr;
                    Require(calculatorForm.ProcessMessage(&message), "calculator handles column-order Tab");
                    current = calculatorNavigationTarget;
                } else {
                    current = GetNextDlgTabItem(page, current, backwards);
                }
                bool matches = current == expected || IsChild(expected, current);
                Require(matches, "native Tab and Shift+Tab follow the requested calculator order");
                if (!matches) {
                    std::printf("Page %d reverse %d step %zu: expected %d actual %d parent %d\n",
                        pageIndex, backwards, index, order[position], GetDlgCtrlID(current),
                        GetDlgCtrlID(GetParent(current)));
                }
            }
        }
        calculatorShiftPressed = false;
        if (pageIndex == 3) {
            RemoveWindowSubclass(window, CalculatorNavigationProbe, 1);
        }
        for (size_t index = 0; index < order.size(); index++) {
            EnableWindow(CalculatorControl(order[index]), enabled[index]);
        }
    }
    CalculatorPage(originalPage);
    SetWindowPos(window, nullptr, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_HIDEWINDOW);
    calculatorPresented = false;
}

/// Checks the shared scroll handler through both real dialog templates and their native message routes.
static void TestCalculatorTabWheel() {
    TestCalculatorUpdatePainting();
    TestCalculatorTabOrder();
    CalculatorPage(0);
    TestComboFocusDrawing(CalculatorControl(ID_CALC_ZONE_BASE));
    TestComboHandling(CalculatorControl(ID_CALC_ZONE_BASE), ID_CALC_ZONE_BASE);
    TestInactiveTabWheel(calculatorForm.GetWindow(), CalculatorControl(ID_CALC_TABS));
    settingsDraft.push_back(AlarmConfiguration(1));
    selectedDraftIndex = 0;
    hSettings = CreateSettingsDialog(IDD_SETTINGS, nullptr, SettingsDialogProc, 0);
    Require(hSettings != nullptr, "native Settings created for inactive tab wheel regression");
    if (hSettings != nullptr) {
        bool created = CreateSettingsControls(0);
        Require(created, "all Settings pages and controls created for inactive tab wheel regression");
        if (created) {
            TestComboFocusDrawing(hTimeZoneCombo);
            TestComboHandling(hTimeZoneCombo, SETTINGS_CONTROL_SUBCLASS_ID);
            TestSettingsTabNavigation();
            TestInactiveTabWheel(hSettings, hTabs);
        }
        DestroySettingsChildControls();
        DestroyWindow(hSettings);
        hSettings = nullptr;
    }
    settingsDraft.clear();
}

/// Captures one native window image into a fresh DC without changing visibility, layout or selected pages.
static void CaptureCalculatorImage(HWND window, const wchar_t* name, bool screen) {
    RECT bounds = {};
    GetWindowRect(window, &bounds);
    LONG width = bounds.right - bounds.left;
    LONG height = bounds.bottom - bounds.top;
    HDC source = screen ? GetDC(nullptr) : GetWindowDC(window);
    HDC memory = CreateCompatibleDC(source);
    BITMAPINFO information = {};
    information.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    information.bmiHeader.biWidth = width;
    information.bmiHeader.biHeight = -height;
    information.bmiHeader.biPlanes = 1;
    information.bmiHeader.biBitCount = 32;
    information.bmiHeader.biCompression = BI_RGB;
    void* pixels = nullptr;
    HBITMAP bitmap = CreateDIBSection(source, &information, DIB_RGB_COLORS, &pixels, nullptr, 0);
    Require(source != nullptr && memory != nullptr && bitmap != nullptr && pixels != nullptr,
        "hidden calculator capture allocated");
    if (source != nullptr && memory != nullptr && bitmap != nullptr && pixels != nullptr) {
        HGDIOBJ previous = SelectObject(memory, bitmap);
        if (screen) {
            Require(BitBlt(memory, 0, 0, width, height, source, bounds.left, bounds.top, SRCCOPY) != FALSE,
                "native screen DC copy succeeded");
        } else {
            Require(PrintWindow(window, memory, 0) != FALSE, "native private-desktop PrintWindow succeeded");
        }
        BITMAPFILEHEADER header = {};
        header.bfType = 0x4D42;
        header.bfOffBits = sizeof(header) + sizeof(BITMAPINFOHEADER);
        DWORD bytes = static_cast<DWORD>(width * height * 4);
        header.bfSize = header.bfOffBits + bytes;
        std::wstring path = calculatorArtifacts + L"\\" + name + L".bmp";
        HANDLE file = CreateFileW(path.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, 0, nullptr);
        Require(file != INVALID_HANDLE_VALUE, "hidden screenshot file opened");
        if (file != INVALID_HANDLE_VALUE) {
            DWORD written = 0;
            bool saved = WriteFile(file, &header, sizeof(header), &written, nullptr) != FALSE
                && WriteFile(file, &information.bmiHeader, sizeof(BITMAPINFOHEADER), &written, nullptr)
                    != FALSE
                && WriteFile(file, pixels, bytes, &written, nullptr) != FALSE;
            Require(saved, "hidden screenshot saved");
            CloseHandle(file);
        }
        SelectObject(memory, previous);
    }
    if (bitmap != nullptr) {
        DeleteObject(bitmap);
    }
    if (memory != nullptr) {
        DeleteDC(memory);
    }
    if (source != nullptr) {
        ReleaseDC(screen ? nullptr : window, source);
    }
}

/// Captures native controls on the unshown private desktop, briefly enabling visibility without activation.
static void CaptureCalculator(const wchar_t* name) {
    HWND window = calculatorForm.GetWindow();
    calculatorPresented = true;
    SetWindowPos(window, HWND_TOP, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
    MSG pending = {};
    while (PeekMessageW(&pending, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&pending);
        DispatchMessageW(&pending);
    }
    RedrawWindow(window, nullptr, nullptr,
        RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN | RDW_UPDATENOW);
    CaptureCalculatorImage(window, name, false);
    SetWindowPos(window, nullptr, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_HIDEWINDOW);
    calculatorPresented = false;
}
/// Captures each resource page and restores the previously selected tab.
static void CaptureCalculatorPages(const wchar_t* prefix) {
    HWND window = calculatorForm.GetWindow();
    int selected = calculatorForm.GetState().tab;
    calculatorPresented = true;
    SetWindowPos(window, nullptr, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_SHOWWINDOW);
    const wchar_t* pages[] = { L"interval", L"milestones", L"presets", L"highlights" };
    const int sequence[] = { 0, 2, 0, 1, 3, 2, 3, 1 };
    for (int index : sequence) {
        CalculatorPage(index);
        RedrawWindow(window, nullptr, nullptr, RDW_INVALIDATE | RDW_ALLCHILDREN | RDW_UPDATENOW);
        std::wstring name = std::wstring(prefix) + L"-" + pages[index];
        CaptureCalculatorImage(window, name.c_str(), false);
    }
    CalculatorPage(selected);
    SetWindowPos(window, nullptr, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_HIDEWINDOW);
    calculatorPresented = false;
}

/// Checks the native month header against the selected application language rather than the host locale.
static void VerifyCalculatorCalendarLanguage() {
    wchar_t header[256] = {};
    MCGRIDINFO information = {};
    information.cbSize = sizeof(information);
    information.dwPart = MCGIP_CALENDARHEADER;
    information.dwFlags = MCGIF_NAME;
    information.pszName = header;
    information.cchName = ARRAYSIZE(header);
    HWND calendar = CalculatorControl(ID_CALC_CALENDAR);
    Require(MonthCal_GetCalendarGridInfo(calendar, &information) != FALSE,
        "native month header can be queried");
    wchar_t month[64] = {};
    SYSTEMTIME selected = {};
    MonthCal_GetCurSel(calendar, &selected);
    const wchar_t* locale = GetLanguageLocale(appLanguage);
    GetLocaleInfoEx(locale, LOCALE_SMONTHNAME1 + selected.wMonth - 1, month, ARRAYSIZE(month));
    int found = FindNLSStringEx(locale, FIND_FROMSTART | NORM_IGNORECASE, header, -1, month, -1,
        nullptr, nullptr, nullptr, 0);
    if (found < 0) {
        std::fwprintf(stderr, L"Calendar header '%ls' does not contain expected month '%ls'.\n",
            header, month);
    }
    Require(found >= 0, "native calendar header follows application language");
}

/// Selects a real catalog item and dispatches the same change notification as the native combo.
static void ChangeCalculatorZone(int input, const wchar_t* key) {
    HWND combo = CalculatorControl(ID_CALC_ZONE_BASE + input);
    LRESULT count = SendMessageW(combo, CB_GETCOUNT, 0, 0);
    for (LRESULT item = 0; item < count; item++) {
        LRESULT index = SendMessageW(combo, CB_GETITEMDATA, item, 0);
        if (index >= 0 && index < static_cast<LRESULT>(timeZones.size())
                && wcscmp(timeZones[index].TimeZoneKeyName, key) == 0) {
            SendMessageW(combo, CB_SETCURSEL, item, 0);
            CalculatorCommand(ID_CALC_ZONE_BASE + input, CBN_SELCHANGE);
            return;
        }
    }
    Require(false, "requested calculator zone exists in the native combo");
}

/// Reads the selected item through the public combo API, including native ComboBoxEx controls.
static std::wstring CalculatorComboText(HWND combo) {
    LRESULT selected = SendMessageW(combo, CB_GETCURSEL, 0, 0);
    LRESULT length = SendMessageW(combo, CB_GETLBTEXTLEN, selected, 0);
    if (selected == CB_ERR || length == CB_ERR) {
        return L"";
    }
    std::wstring text(static_cast<size_t>(length) + 1, L'\0');
    SendMessageW(combo, CB_GETLBTEXT, selected, reinterpret_cast<LPARAM>(text.data()));
    text.resize(static_cast<size_t>(length));
    return text;
}

/// Exercises actual form notifications for UTC instants, gaps, folds, defaults and zone-only display changes.
static void TestCalculatorTimeZones() {
    TimeCalculatorState previous = calculatorForm.GetState();
    TimeCalculatorState state;
    state.from = CalculatorDate(2026, 10, 25, 0, 30);
    state.to = CalculatorDate(2026, 10, 25, 1, 30);
    state.start = CalculatorDate(2026, 10, 24, 14, 30);
    state.day = CalculatorDate(2026, 10, 25);
    LoadCalculator(state);
    SYSTEMTIME now = {};
    GetSystemTime(&now);
    std::vector<std::wstring> labels = BuildSettingsTimeZoneLabels(timeZones, now,
        T(TXT_SYSTEM_TIME_ZONE_LABEL));
    for (int input = 0; input < 4; input++) {
        HWND combo = CalculatorControl(ID_CALC_ZONE_BASE + input);
        Require(SendMessageW(combo, CB_GETCOUNT, 0, 0) == static_cast<LRESULT>(labels.size()),
            "all zone selectors have exactly the Settings catalog count");
        Require(SendMessageW(combo, CB_GETCURSEL, 0, 0) == 0,
            "current Windows zone is the first default choice");
        for (size_t item = 0; item < labels.size(); item++) {
            LRESULT length = SendMessageW(combo, CB_GETLBTEXTLEN, item, 0);
            std::wstring actual(static_cast<size_t>(length) + 1, L'\0');
            SendMessageW(combo, CB_GETLBTEXT, item, reinterpret_cast<LPARAM>(actual.data()));
            Require(labels[item] == actual.c_str(), "zone selector labels exactly match Settings");
        }
    }
    state.fromZone = L"Central Europe Standard Time";
    state.toZone = state.fromZone;
    state.startZone = state.fromZone;
    LoadCalculator(state);
    SYSTEMTIME first = {};
    SYSTEMTIME second = {};
    DateTime_GetSystemtime(CalculatorControl(ID_CALC_FROM), &first);
    DateTime_GetSystemtime(CalculatorControl(ID_CALC_TO), &second);
    Require(first.wHour == 2 && first.wMinute == 30 && CompareCalculatorDates(first, second) == 0,
        "two real instants display the same repeated local clock reading");
    Require(CalculatorComboText(CalculatorControl(ID_CALC_OFFSET_BASE)) == L"UTC+02:00"
        && CalculatorComboText(CalculatorControl(ID_CALC_OFFSET_BASE + 1)) == L"UTC+01:00"
        && GetControlText(CalculatorControl(ID_CALC_TOTAL_BASE)) == L"1",
        "visible offsets distinguish the fold and elapsed difference remains one hour");
    ChangeCalculatorZone(0, L"UTC+05:45");
    DateTime_GetSystemtime(CalculatorControl(ID_CALC_FROM), &first);
    Require(first.wHour == 6 && first.wMinute == 15 && CompareCalculatorDates(calculatorForm.GetState().from,
        state.from) == 0, "changing display zone preserves UTC and updates displayed date and minute");
    ChangeCalculatorZone(0, L"Central Europe Standard Time");
    ChangeCalculatorDate(ID_CALC_FROM, CalculatorDate(2026, 3, 29, 2, 30));
    Require(GetControlText(CalculatorControl(ID_CALC_TOTAL_BASE)) == L"—"
        && SendMessageW(CalculatorControl(ID_CALC_OFFSET_BASE), CB_GETCOUNT, 0, 0) == 0,
        "missing local time is never silently treated as a real instant");
    ChangeCalculatorDate(ID_CALC_FROM, CalculatorDate(2026, 10, 25, 2, 15));
    Require(SendMessageW(CalculatorControl(ID_CALC_OFFSET_BASE), CB_GETCURSEL, 0, 0) == CB_ERR,
        "new ambiguous local time requires an explicit UTC offset");
    SendMessageW(CalculatorControl(ID_CALC_OFFSET_BASE), CB_SETCURSEL, 1, 0);
    CalculatorCommand(ID_CALC_OFFSET_BASE, CBN_SELCHANGE);
    Require(calculatorForm.GetState().from.wHour == 1 && calculatorForm.GetState().from.wMinute == 15,
        "offset selection commits the exact later UTC occurrence");
    TimeCalculatorState saved = calculatorForm.GetState();
    saved.from.wSecond = 12;
    saved.from.wMilliseconds = 345;
    LoadCalculator(saved);
    Require(CompareCalculatorDates(calculatorForm.GetState().from, saved.from) == 0,
        "reopening inputs preserves the exact stored UTC instant");
    Require(CalculatorComboText(CalculatorControl(ID_CALC_OFFSET_BASE)) == L"UTC+01:00",
        "restoring UTC state preserves the exact occurrence");
    ChangeCalculatorZone(3, L"UTC+00:00");
    LoadCalculator(previous);
}

/// Checks visible interval totals and decompositions after actual date-picker and Now notifications.
static void TestCalculatorResultNotifications() {
    TimeCalculatorState original = calculatorForm.GetState();
    AppLanguage originalLanguage = appLanguage;
    appLanguage = LANG_EN_US;
    TimeCalculatorState state;
    state.fromZone = L"UTC+00:00";
    state.toZone = state.fromZone;
    state.startZone = state.fromZone;
    state.from = CalculatorDate(2026, 1, 1, 23, 30);
    state.to = CalculatorDate(2026, 1, 2, 0, 15);
    state.start = state.from;
    state.day = CalculatorDate(2026, 1, 2);
    LoadCalculator(state);
    Require(GetControlText(CalculatorControl(ID_CALC_TOTAL_BASE)) == L"0"
        && GetControlText(CalculatorControl(ID_CALC_TOTAL_BASE + 1)) == L"1",
        "visible interval distinguishes elapsed hours from a crossed calendar midnight");
    Require(GetControlText(CalculatorControl(ID_CALC_PARTS_BASE)) == L"(45 min)",
        "cross-midnight remainder is rendered as forty-five minutes");
    ChangeCalculatorDate(ID_CALC_TO, CalculatorDate(2026, 1, 2, 1, 15));
    Require(GetControlText(CalculatorControl(ID_CALC_TOTAL_BASE)) == L"1"
        && GetControlText(CalculatorControl(ID_CALC_PARTS_BASE)) == L"(1 h, 45 min)",
        "end-picker notification immediately recalculates displayed total and remainder");
    ChangeCalculatorDate(ID_CALC_FROM, CalculatorDate(2026, 1, 2, 1, 15));
    for (int row = 0; row < TIME_CALCULATOR_TOTAL_COUNT; row++) {
        Require(GetControlText(CalculatorControl(ID_CALC_TOTAL_BASE + row)) == L"0"
            && GetControlText(CalculatorControl(ID_CALC_PARTS_BASE + row)).empty(),
            "equal picker values immediately clear all rendered decompositions");
    }
    ChangeCalculatorDate(ID_CALC_FROM, CalculatorDate(2026, 1, 2, 1, 16));
    for (int row = 0; row < TIME_CALCULATOR_TOTAL_COUNT; row++) {
        Require(GetControlText(CalculatorControl(ID_CALC_TOTAL_BASE + row)) == L"—"
            && GetControlText(CalculatorControl(ID_CALC_PARTS_BASE + row)).empty(),
            "reversed picker values do not leave stale previous results visible");
    }
    ChangeCalculatorDate(ID_CALC_FROM, CalculatorDate(2024, 2, 28, 23, 59));
    ChangeCalculatorDate(ID_CALC_TO, CalculatorDate(2024, 3, 1, 0, 1));
    Require(GetControlText(CalculatorControl(ID_CALC_TOTAL_BASE)) == L"24"
        && GetControlText(CalculatorControl(ID_CALC_TOTAL_BASE + 1)) == L"2"
        && GetControlText(CalculatorControl(ID_CALC_PARTS_BASE + 1)) == L"(1 d, 2 min)",
        "leap-day picker changes refresh calendar totals and exact elapsed decomposition");
    TimeCalculatorState manual = calculatorForm.GetState();
    for (int id : { ID_CALC_FROM_NOW, ID_CALC_TO_NOW }) {
        SendMessageW(CalculatorControl(id), BM_SETCHECK, BST_CHECKED, 0);
        CalculatorCommand(id);
    }
    SendMessageW(calculatorForm.GetWindow(), WM_TIMER, CALCULATOR_TIMER, 0);
    Require(GetControlText(CalculatorControl(ID_CALC_TOTAL_BASE)) == L"0"
        && GetControlText(CalculatorControl(ID_CALC_PARTS_BASE)).empty(),
        "both Now inputs refer to the same instant in a single refresh");
    for (int id : { ID_CALC_FROM_NOW, ID_CALC_TO_NOW }) {
        SendMessageW(CalculatorControl(id), BM_SETCHECK, BST_UNCHECKED, 0);
        CalculatorCommand(id);
    }
    Require(SameCalculatorState(manual, calculatorForm.GetState())
        && GetControlText(CalculatorControl(ID_CALC_TOTAL_BASE)) == L"24",
        "disabling Now restores both manual instants and their original results");
    state.fromZone = L"Central Europe Standard Time";
    state.toZone = state.fromZone;
    state.from = CalculatorDate(2026, 9, 25, 0, 30);
    state.to = CalculatorDate(2026, 10, 25, 1, 15);
    LoadCalculator(state);
    Require(GetControlText(CalculatorControl(ID_CALC_PARTS_BASE + 3)) == L"(1 mo, 45 min)",
        "later autumn occurrence renders one elapsed calendar month and forty-five minutes");
    appLanguage = originalLanguage;
    LoadCalculator(original);
}

/// Requests the actual calendar callback and copies its masks before another notification can replace them.
static std::vector<MONTHDAYSTATE> CalculatorDayMasks(const SYSTEMTIME& first, int count) {
    NMDAYSTATE request = {};
    request.nmhdr.hwndFrom = CalculatorControl(ID_CALC_CALENDAR);
    request.nmhdr.idFrom = ID_CALC_CALENDAR;
    request.nmhdr.code = MCN_GETDAYSTATE;
    request.stStart = first;
    request.cDayState = count;
    SendMessageW(GetParent(request.nmhdr.hwndFrom), WM_NOTIFY, ID_CALC_CALENDAR,
        reinterpret_cast<LPARAM>(&request));
    WaitForCalculator();
    SendMessageW(GetParent(request.nmhdr.hwndFrom), WM_NOTIFY, ID_CALC_CALENDAR,
        reinterpret_cast<LPARAM>(&request));
    Require(request.prgDayState != nullptr, "calendar callback supplies its requested day-state array");
    if (request.prgDayState == nullptr) {
        return std::vector<MONTHDAYSTATE>(count);
    }
    return std::vector<MONTHDAYSTATE>(request.prgDayState, request.prgDayState + count);
}

/// Compares calendar callback masks against manually derived January-to-March dates in UTC.
static void CheckCalculatorQuarterMask(MONTHDAYSTATE january, MONTHDAYSTATE february, MONTHDAYSTATE march) {
    std::vector<MONTHDAYSTATE> masks = CalculatorDayMasks(CalculatorDate(2026, 1, 1), 3);
    Require(masks[0] == january && masks[1] == february && masks[2] == march,
        "calendar callback matches independently derived dates in every requested month");
}

/// Keeps a real worker blocked while exercising immediate GUI commands, replacement and close/reopen
/// lifetime.
static void TestCalculatorBackgroundWork() {
    TimeCalculatorState original = calculatorForm.GetState();
    TimeCalculatorState state;
    state.fromZone = L"UTC+00:00";
    state.toZone = state.fromZone;
    state.startZone = state.fromZone;
    state.from = CalculatorDate(2026, 1, 1);
    state.to = CalculatorDate(2026, 1, 2);
    state.start = state.from;
    state.day = state.from;
    state.highlights = CALCULATOR_HIGHLIGHT_NINES;
    LoadCalculator(state);
    HWND check = CalculatorControl(ID_CALC_HIGHLIGHT_BASE + 9);
    HWND parent = GetParent(check);
    HWND window = calculatorForm.GetWindow();
    ResetEvent(calculatorWorkerGate);
    SendMessageW(check, BM_SETCHECK, BST_CHECKED, 0);
    SendMessageW(parent, WM_COMMAND, MAKEWPARAM(ID_CALC_HIGHLIGHT_BASE + 9, BN_CLICKED),
        reinterpret_cast<LPARAM>(check));
    MSG message = {};
    while (PeekMessageW(&message, window, CALCULATOR_CALCULATE, CALCULATOR_CALCULATE, PM_REMOVE)) {
        DispatchMessageW(&message);
    }
    Require(calculatorWorkers.load() == 1, "a blocked calculator worker runs separately from the dialog");
    ULONGLONG started = GetTickCount64();
    for (int index = 0; index < 20; index++) {
        WPARAM checked = index % 2 == 0 ? BST_UNCHECKED : BST_CHECKED;
        SendMessageW(check, BM_SETCHECK, checked, 0);
        SendMessageW(parent, WM_COMMAND, MAKEWPARAM(ID_CALC_HIGHLIGHT_BASE + 9, BN_CLICKED),
            reinterpret_cast<LPARAM>(check));
    }
    std::printf("Twenty checkbox commands while calculation was paused: %llu ms.\n",
        GetTickCount64() - started);
    Require(SendMessageW(check, BM_GETCHECK, 0, 0) == BST_CHECKED,
        "checkbox state is immediately readable while calculation remains blocked");
    Require(calculatorWorkers.load() == 1, "rapid changes do not create a thread for each click");
    state.to = CalculatorDate(2026, 1, 4);
    state.highlights = CALCULATOR_HIGHLIGHT_SIXES;
    calculatorForm.Load(state);
    Require(calculatorForm.GetState().highlights == CALCULATOR_HIGHLIGHT_SIXES,
        "latest inputs replace pending calculation without waiting for earlier work");
    SetEvent(calculatorWorkerGate);
    WaitForCalculator();
    Require(GetControlText(CalculatorControl(ID_CALC_TOTAL_BASE)) == L"72",
        "cancelled work is replaced by the latest interval in the same open dialog");
    CheckCalculatorQuarterMask(0x8000004, 0, 0x80);
    ResetEvent(calculatorWorkerGate);
    SendMessageW(parent, WM_COMMAND, MAKEWPARAM(ID_CALC_HIGHLIGHT_BASE + 9, BN_CLICKED),
        reinterpret_cast<LPARAM>(check));
    while (PeekMessageW(&message, window, CALCULATOR_CALCULATE, CALCULATOR_CALCULATE, PM_REMOVE)) {
        DispatchMessageW(&message);
    }
    calculatorForm.Close();
    Require(calculatorForm.GetWindow() == nullptr && calculatorWorkers.load() == 1,
        "closing the form does not wait for its blocked worker");
    calculatorForm.Show(hInstance, calculatorWindowState);
    Require(calculatorForm.GetWindow() != nullptr,
        "reopening the calculator does not wait for its old worker");
    std::printf("GUI commands and reopen while the worker was paused: %llu ms.\n",
        GetTickCount64() - started);
    SetEvent(calculatorWorkerGate);
    WaitForCalculator();
    Require(GetControlText(CalculatorControl(ID_CALC_TOTAL_BASE)) == L"72",
        "obsolete completion cannot overwrite the latest interval after reopening");
    CheckCalculatorQuarterMask(0x8000004, 0, 0x80);
    Require(calculatorForm.GetState().highlights == CALCULATOR_HIGHLIGHT_SIXES,
        "obsolete completion cannot restore a previous highlighting selection");
    LoadCalculator(original);
}

/// Covers native month masks, checkbox mapping, start/zone changes, and state surviving style and window
/// changes.
static void TestCalculatorCalendarNotifications() {
    TimeCalculatorState original = calculatorForm.GetState();
    TimeCalculatorState state;
    state.fromZone = L"UTC+00:00";
    state.toZone = state.fromZone;
    state.startZone = state.fromZone;
    state.from = CalculatorDate(2026, 1, 1);
    state.to = CalculatorDate(2026, 4, 1);
    state.start = state.from;
    state.day = state.from;
    state.tab = 3;
    LoadCalculator(state);
    for (int index = 4; index < TIME_CALCULATOR_HIGHLIGHT_COUNT; index++) {
        Require(SendMessageW(CalculatorControl(ID_CALC_HIGHLIGHT_BASE + index), BM_GETCHECK, 0, 0)
            == BST_UNCHECKED, "each repeated-digit checkbox is initially unchecked");
    }
    const DWORD digitFlags[] = {
        CALCULATOR_HIGHLIGHT_ONES,
        CALCULATOR_HIGHLIGHT_TWOS,
        CALCULATOR_HIGHLIGHT_THREES,
        CALCULATOR_HIGHLIGHT_FOURS,
        CALCULATOR_HIGHLIGHT_FIVES,
        CALCULATOR_HIGHLIGHT_SIXES,
        CALCULATOR_HIGHLIGHT_SEVENS,
        CALCULATOR_HIGHLIGHT_EIGHTS,
        CALCULATOR_HIGHLIGHT_NINES
    };
    for (int digit = 0; digit < 9; digit++) {
        state.highlights = 0;
        LoadCalculator(state);
        HWND control = CalculatorControl(ID_CALC_HIGHLIGHT_BASE + 4 + digit);
        SendMessageW(control, BM_SETCHECK, BST_CHECKED, 0);
        CalculatorCommand(ID_CALC_HIGHLIGHT_BASE + 4 + digit);
        Require(calculatorForm.GetState().highlights == digitFlags[digit],
            "each digit checkbox maps to its own independent rule");
    }
    state.highlights = CALCULATOR_HIGHLIGHT_START;
    LoadCalculator(state);
    CheckCalculatorQuarterMask(0x1, 0, 0);
    state.highlights = CALCULATOR_HIGHLIGHT_FIRST_WEEKS;
    LoadCalculator(state);
    CheckCalculatorQuarterMask(0x10204080, 0x2040810, 0x10);
    state.highlights = CALCULATOR_HIGHLIGHT_ANNIVERSARIES;
    LoadCalculator(state);
    CheckCalculatorQuarterMask(0, 0x1, 0x1);
    state.highlights = CALCULATOR_HIGHLIGHT_ONES;
    LoadCalculator(state);
    CheckCalculatorQuarterMask(0x810, 0x8000, 0x40000);
    state.highlights = CALCULATOR_HIGHLIGHT_TWOS;
    LoadCalculator(state);
    CheckCalculatorQuarterMask(0x400200, 0, 0);
    state.highlights = CALCULATOR_HIGHLIGHT_SIXES;
    LoadCalculator(state);
    CheckCalculatorQuarterMask(0x8000004, 0, 0x80);
    state.highlights = CALCULATOR_HIGHLIGHT_NINES;
    LoadCalculator(state);
    CheckCalculatorQuarterMask(0x10, 0x400, 0);
    state.highlights = 0;
    LoadCalculator(state);
    CheckCalculatorQuarterMask(0, 0, 0);
    for (int index : { 9, 12 }) {
        HWND control = CalculatorControl(ID_CALC_HIGHLIGHT_BASE + index);
        SendMessageW(control, BM_SETCHECK, BST_CHECKED, 0);
        CalculatorCommand(ID_CALC_HIGHLIGHT_BASE + index);
    }
    Require(calculatorForm.GetState().highlights == (CALCULATOR_HIGHLIGHT_SIXES | CALCULATOR_HIGHLIGHT_NINES),
        "six and nine checkboxes control their own saved rule bits");
    CheckCalculatorQuarterMask(0x8000014, 0x400, 0x80);
    TimeCalculatorState chosen = calculatorForm.GetState();
    RefreshCalculator();
    Require(SameCalculatorState(chosen, calculatorForm.GetState()),
        "refresh preserves chosen calendar rules");
    CheckCalculatorQuarterMask(0x8000014, 0x400, 0x80);
    std::wstring previousFont = appFontFace;
    appFontFace = L"Cambria Math";
    Require(calculatorForm.ApplyStyle(true), "custom font applies to the selected highlight configuration");
    Require(SameCalculatorState(chosen, calculatorForm.GetState()), "font change preserves calendar rules");
    CheckCalculatorQuarterMask(0x8000014, 0x400, 0x80);
    appFontFace = previousFont;
    Require(calculatorForm.ApplyStyle(true), "original font restored after highlight-state coverage");
    calculatorForm.Close();
    ShowCalculator();
    Require(SameCalculatorState(chosen, calculatorForm.GetState()),
        "reopening preserves calendar rules and tab");
    CheckCalculatorQuarterMask(0x8000014, 0x400, 0x80);
    state.highlights = CALCULATOR_HIGHLIGHT_START;
    LoadCalculator(state);
    ChangeCalculatorDate(ID_CALC_START, CalculatorDate(2026, 2, 1));
    CheckCalculatorQuarterMask(0, 0x1, 0);
    ChangeCalculatorZone(2, L"UTC-01:00");
    CheckCalculatorQuarterMask(0x40000000, 0, 0);
    Require(calculatorForm.GetState().start.wMonth == 2 && calculatorForm.GetState().start.wDay == 1,
        "display-zone change moves the local starting date without moving its UTC instant");
    state.highlights = CALCULATOR_HIGHLIGHT_THREES;
    LoadCalculator(state);
    HWND calendar = CalculatorControl(ID_CALC_CALENDAR);
    SYSTEMTIME selected = CalculatorDate(2026, 1, 2);
    MonthCal_SetCurSel(calendar, &selected);
    NMHDR selection{ calendar, ID_CALC_CALENDAR, MCN_SELCHANGE };
    SendMessageW(GetParent(calendar), WM_NOTIFY, ID_CALC_CALENDAR, reinterpret_cast<LPARAM>(&selection));
    Require(GetControlText(CalculatorControl(ID_CALC_DAY_TOTAL_BASE)) == L"33 (09:00 UTC+00:00)",
        "native calendar selection displays the exact chosen repeated-hour milestone");
    HWND threes = CalculatorControl(ID_CALC_HIGHLIGHT_BASE + 6);
    SendMessageW(threes, BM_SETCHECK, BST_UNCHECKED, 0);
    CalculatorCommand(ID_CALC_HIGHLIGHT_BASE + 6);
    Require(GetControlText(CalculatorControl(ID_CALC_DAY_TOTAL_BASE)) == L"24",
        "disabling the displayed rule immediately removes its milestone time");
    state.highlights = CALCULATOR_HIGHLIGHT_START;
    state.startZone = L"Central Europe Standard Time";
    state.start = CalculatorDate(2026, 3, 1);
    state.day = CalculatorDate(2026, 3, 29);
    LoadCalculator(state);
    ChangeCalculatorDate(ID_CALC_START, CalculatorDate(2026, 3, 29, 2, 30));
    std::vector<MONTHDAYSTATE> masks = CalculatorDayMasks(CalculatorDate(2026, 3, 1), 3);
    Require(masks[0] == 0 && masks[1] == 0 && masks[2] == 0,
        "nonexistent spring start clears all previously highlighted calendar dates");
    Require(GetControlText(CalculatorControl(ID_CALC_DAY_TOTAL_BASE)) == L"—",
        "nonexistent spring start does not retain a valid selected-day result");
    ChangeCalculatorDate(ID_CALC_START, CalculatorDate(2026, 3, 29, 3, 30));
    masks = CalculatorDayMasks(CalculatorDate(2026, 3, 1), 3);
    Require(masks[0] == 0x10000000 && masks[1] == 0 && masks[2] == 0,
        "valid replacement start immediately restores the correct calendar mask");
    ChangeCalculatorDate(ID_CALC_START, CalculatorDate(2026, 10, 25, 2, 30));
    Require(SendMessageW(CalculatorControl(ID_CALC_OFFSET_BASE + 2), CB_GETCURSEL, 0, 0) == CB_ERR,
        "new repeated starting time requires an explicit occurrence");
    masks = CalculatorDayMasks(CalculatorDate(2026, 10, 1), 3);
    Require(masks[0] == 0
        && masks[1] == 0
        && masks[2] == 0
        && GetControlText(CalculatorControl(ID_CALC_DAY_TOTAL_BASE)) == L"—",
        "unresolved repeated start leaves neither stale highlighting nor stale totals");
    SendMessageW(CalculatorControl(ID_CALC_OFFSET_BASE + 2), CB_SETCURSEL, 1, 0);
    CalculatorCommand(ID_CALC_OFFSET_BASE + 2, CBN_SELCHANGE);
    masks = CalculatorDayMasks(CalculatorDate(2026, 10, 1), 3);
    Require(masks[0] == 0x1000000 && masks[1] == 0
        && masks[2] == 0
        && calculatorForm.GetState().start.wHour == 1
        && calculatorForm.GetState().start.wMinute == 30,
        "choosing the later occurrence restores its exact UTC instant and starting-day mask");
    LoadCalculator(original);
}

/// Checks initial values, all tabs, resource-authored outer margins and live/manual date restoration.
static void TestCalculatorInitialAndNow() {
    HWND window = calculatorForm.GetWindow();
    Require(window != nullptr
        && !IsWindowVisible(window)
        && (GetWindowLongPtrW(window, GWL_EXSTYLE) & WS_EX_NOACTIVATE) != 0,
        "calculator starts hidden and nonactivating on a private desktop");
    Require(GetControlText(CalculatorControl(ID_CALC_TOTAL_BASE)) == L"217", "initial hour total rendered");
    RECT tabs = {};
    GetWindowRect(CalculatorControl(ID_CALC_TABS), &tabs);
    MapWindowPoints(HWND_DESKTOP, window, reinterpret_cast<POINT*>(&tabs), 2);
    HFONT font = reinterpret_cast<HFONT>(SendMessageW(window, WM_GETFONT, 0, 0));
    SIZE margin = InformationDialogUnits(font, 8, 3);
    RECT client = {};
    GetClientRect(window, &client);
    Require(tabs.left == margin.cx
        && tabs.top == margin.cy
        && std::abs(client.bottom - tabs.bottom - tabs.top) <= 1,
        "tab control retains side margins and matching compact top and bottom spacing");
    const wchar_t* names[] = { L"calculator-interval", L"calculator-milestones", L"calculator-presets" };
    for (int tab = 0; tab < 3; tab++) {
        CalculatorPage(tab);
        CaptureCalculator(names[tab]);
    }
    CalculatorPage(0);
    SYSTEMTIME manual = calculatorForm.GetState().from;
    CheckDlgButton(GetParent(CalculatorControl(ID_CALC_FROM_NOW)), ID_CALC_FROM_NOW, BST_CHECKED);
    CalculatorCommand(ID_CALC_FROM_NOW);
    Require(!IsWindowEnabled(CalculatorControl(ID_CALC_FROM))
        && !IsWindowEnabled(CalculatorControl(ID_CALC_FROM_PRESET)), "Now disables picker and preset combo");
    Require(CompareCalculatorDates(manual, calculatorForm.GetState().from) == 0,
        "Now preserves the stored manual timestamp");
    SendMessageW(window, WM_TIMER, CALCULATOR_TIMER, 0);
    CheckDlgButton(GetParent(CalculatorControl(ID_CALC_FROM_NOW)), ID_CALC_FROM_NOW, BST_UNCHECKED);
    CalculatorCommand(ID_CALC_FROM_NOW);
    SYSTEMTIME restored = {};
    DateTime_GetSystemtime(CalculatorControl(ID_CALC_FROM), &restored);
    Require(CompareCalculatorDates(manual, restored) == 0 && IsWindowEnabled(CalculatorControl(ID_CALC_FROM)),
        "disabling Now immediately restores the exact manual minute");
}

/// Verifies native picker roundtrips at both limits and captures the longest interval in three languages.
static void TestCalculatorRangesAndLanguages() {
    TimeCalculatorState previous = calculatorForm.GetState();
    TimeCalculatorState imported = previous;
    imported.start = CalculatorDate(2000, 1, 1);
    imported.day = CalculatorDate(2005, 1, 1);
    LoadCalculator(imported);
    SYSTEMTIME importedSelection = {};
    Require(MonthCal_GetCurSel(CalculatorControl(ID_CALC_CALENDAR), &importedSelection) != FALSE,
        "imported calendar selection is available");
    Require(importedSelection.wYear == imported.day.wYear
        && importedSelection.wMonth == imported.day.wMonth
        && importedSelection.wDay == imported.day.wDay,
        "importing an earlier start updates calendar range before restoring selection");
    LoadCalculator(previous);
    const int ids[] = { ID_CALC_FROM, ID_CALC_TO, ID_CALC_START, ID_CALC_DATE };
    SYSTEMTIME limits[] = { CalculatorDate(1601, 1, 1), CalculatorDate(9999, 12, 31, 23, 59) };
    for (int id : ids) {
        for (const SYSTEMTIME& limit : limits) {
            Require(DateTime_SetSystemtime(CalculatorControl(id), GDT_VALID, &limit) != FALSE,
                "native date picker accepts the declared supported limit");
            SYSTEMTIME actual = {};
            Require(DateTime_GetSystemtime(CalculatorControl(id), &actual) == GDT_VALID
                && CompareCalculatorDates(actual, limit) == 0,
                "native date picker preserves the exact limit");
        }
    }
    TimeCalculatorState maximum = previous;
    maximum.from = limits[0];
    maximum.to = limits[1];
    maximum.tab = 0;
    LoadCalculator(maximum);
    const AppLanguage languages[] = { LANG_EN_US, LANG_CS, LANG_DE };
    const wchar_t* names[] = {
        L"calculator-maximum-en",
        L"calculator-maximum-cs",
        L"calculator-maximum-de"
    };
    const wchar_t* pages[] = {
        L"calculator-language-en",
        L"calculator-language-cs",
        L"calculator-language-de"
    };
    for (int index = 0; index < 3; index++) {
        appLanguage = languages[index];
        RefreshCalculator();
        VerifyCalculatorCalendarLanguage();
        TimeCalculatorState beforeSettings = calculatorForm.GetState();
        SendMessageW(CalculatorControl(ID_CALC_CALENDAR), WM_SETTINGCHANGE, 0,
            reinterpret_cast<LPARAM>(L"intl"));
        for (int id : ids) {
            SendMessageW(CalculatorControl(id), WM_SETTINGCHANGE, 0, reinterpret_cast<LPARAM>(L"intl"));
        }
        Require(SameCalculatorState(beforeSettings, calculatorForm.GetState()),
            "native international-setting refresh preserves calculator input values");
        VerifyCalculatorCalendarLanguage();
        Require(GetControlText(CalculatorControl(ID_CALC_TOTAL_BASE + 4)) == L"8398",
            "longest supported interval retains its year total after localization");
        for (int row = 0; row < TIME_CALCULATOR_TOTAL_COUNT; row++) {
            Require(!GetControlText(CalculatorControl(ID_CALC_PARTS_BASE + row)).empty(),
                "localized maximum interval has every decomposition");
        }
        CaptureCalculator(names[index]);
        CaptureCalculatorPages(pages[index]);
    }
    appLanguage = LANG_EN_US;
    LoadCalculator(previous);
}

/// Adds one preset through genuine native picker/edit notifications followed by the Add command.
static void AddCalculatorPreset(const SYSTEMTIME& time, const wchar_t* description) {
    ChangeCalculatorDate(ID_CALC_DATE, time);
    SetWindowTextW(CalculatorDescriptionEdit(), description);
    CalculatorCommand(ID_CALC_ADD);
}

/// Exercises presets, duplicate confirmations, sorted-item identities, editing and confirmed deletion.
static void TestCalculatorPresets() {
    CalculatorPage(2);
    HWND list = CalculatorControl(ID_CALC_LIST);
    SetWindowTextW(CalculatorDescriptionEdit(), L" \t ");
    Require(!IsWindowEnabled(CalculatorControl(ID_CALC_ADD)), "whitespace-only description disables Add");
    AddCalculatorPreset(CalculatorDate(2026, 5, 1, 8), L"  Later date  ");
    AddCalculatorPreset(CalculatorDate(2025, 4, 1, 9), L"Earlier date");
    Require(calculatorForm.GetPresets().size() == 2 && ListView_GetItemCount(list) == 2,
        "preset additions update stored collection and native list");
    Require(calculatorForm.GetPresets()[0].description == L"  Later date  ",
        "preset description whitespace is preserved");
    Require(CompareCalculatorDates(calculatorForm.GetPresets()[0].time, CalculatorDate(2026, 5, 1, 8)) == 0
        && CompareCalculatorDates(calculatorForm.GetPresets()[1].time, CalculatorDate(2025, 4, 1, 9)) == 0,
        "preset dates reflect genuine user-change notifications");
    calculatorAnswer = IDNO;
    AddCalculatorPreset(CalculatorDate(2025, 4, 1, 9), L"Another event");
    Require(calculatorForm.GetPresets().size() == 2, "duplicate declined without changing collection");
    calculatorAnswer = IDYES;
    CalculatorCommand(ID_CALC_ADD);
    Require(calculatorForm.GetPresets().size() == 3, "confirmed duplicate date remains supported");
    NMLISTVIEW sort = {};
    sort.hdr = NMHDR{ list, ID_CALC_LIST, LVN_COLUMNCLICK };
    sort.iSubItem = 0;
    SendMessageW(GetParent(list), WM_NOTIFY, ID_CALC_LIST, reinterpret_cast<LPARAM>(&sort));
    ListView_SetItemState(list, -1, 0, LVIS_SELECTED);
    ListView_SetItemState(list, 0, LVIS_SELECTED, LVIS_SELECTED);
    CalculatorCommand(ID_CALC_EDIT);
    Require(GetControlText(CalculatorDescriptionEdit()) == L"  Later date  ",
        "editing sorted row uses its stable preset identity");
    MSG escape = {};
    escape.hwnd = CalculatorDescriptionEdit();
    escape.message = WM_KEYDOWN;
    escape.wParam = VK_ESCAPE;
    HWND unchanged = calculatorForm.GetWindow();
    Require(calculatorForm.ProcessMessage(&escape)
        && calculatorForm.GetWindow() == unchanged
        && GetControlText(CalculatorDescriptionEdit()).empty(),
        "Escape cancels inline editing without closing the calculator");
    CalculatorCommand(ID_CALC_EDIT);
    SetWindowTextW(CalculatorDescriptionEdit(), L"Renamed later date");
    CalculatorCommand(ID_CALC_ADD);
    Require(calculatorForm.GetPresets().size() == 3
        && calculatorForm.GetPresets()[0].description == L"Renamed later date",
        "editing modifies exactly the selected record");
    ListView_SetItemState(list, 0, LVIS_SELECTED, LVIS_SELECTED);
    calculatorAnswer = IDCANCEL;
    CalculatorCommand(ID_CALC_DELETE);
    Require(calculatorForm.GetPresets().size() == 3, "canceling deletion preserves records");
    calculatorAnswer = IDOK;
    CalculatorCommand(ID_CALC_DELETE);
    Require(calculatorForm.GetPresets().size() == 2
        && calculatorForm.GetPresets()[0].description == L"Earlier date",
        "confirmed deletion removes the sorted row's original record");
    MSG enter = {};
    enter.hwnd = CalculatorControl(ID_CALC_DATE);
    enter.message = WM_KEYDOWN;
    enter.wParam = VK_RETURN;
    calculatorExpectedFocus = nullptr;
    Require(calculatorForm.ProcessMessage(&enter)
        && SettingsEdit::GetFrame(calculatorExpectedFocus) == CalculatorControl(ID_CALC_DESCRIPTION),
        "Enter in preset date requests description focus without committing");
    Require(calculatorPresetWrites > 0, "preset changes save to isolated standalone XML");
}

/// Verifies a settings import preserves user data and invalidates an outstanding modal editing operation.
static void TestCalculatorConfirmationImport() {
    TimeCalculatorState original = calculatorForm.GetState();
    std::vector<TimeCalculatorPreset> records = calculatorForm.GetPresets();
    calculatorConfirmationState = original;
    calculatorConfirmationState.from = CalculatorDate(2010, 6, 3);
    calculatorConfirmationState.highlights = CALCULATOR_HIGHLIGHT_SIXES | CALCULATOR_HIGHLIGHT_NINES;
    calculatorConfirmationState.tab = 3;
    calculatorAnswer = IDYES;
    calculatorLoadOnConfirmation = true;
    AddCalculatorPreset(records[0].time, L"Pending duplicate");
    Require(!calculatorLoadOnConfirmation && SameCalculatorState(calculatorForm.GetState(),
        calculatorConfirmationState),
        "settings import during confirmation updates only window settings");
    Require(SendMessageW(CalculatorControl(ID_CALC_HIGHLIGHT_BASE + 9), BM_GETCHECK, 0, 0) == BST_CHECKED
        && SendMessageW(CalculatorControl(ID_CALC_HIGHLIGHT_BASE + 12), BM_GETCHECK, 0, 0) == BST_CHECKED
        && SendMessageW(CalculatorControl(ID_CALC_HIGHLIGHT_BASE + 4), BM_GETCHECK, 0, 0) == BST_UNCHECKED,
        "imported highlight choices immediately replace the displayed checkbox states");
    Require(calculatorForm.GetPresets().size() == records.size()
        && calculatorForm.GetPresets()[0].description == records[0].description,
        "settings import preserves the existing user collection");
    LoadCalculator(original);
    HWND list = CalculatorControl(ID_CALC_LIST);
    ListView_SetItemState(list, 0, LVIS_SELECTED, LVIS_SELECTED);
    calculatorAnswer = IDOK;
    calculatorLoadOnConfirmation = true;
    CalculatorCommand(ID_CALC_DELETE);
    Require(!calculatorLoadOnConfirmation && calculatorForm.GetPresets().size() == records.size(),
        "settings import cancels pending deletion without removing user data");
    LoadCalculator(original);
}

/// Verifies exact import matching, additive merging, repeated imports and preservation on failed saves.
static void TestCalculatorMerge() {
    std::vector<TimeCalculatorPreset> original = calculatorForm.GetPresets();
    Require(!original.empty(), "merge fixture contains existing user data");
    std::vector<TimeCalculatorPreset> imported;
    imported.push_back(original[0]);
    TimeCalculatorPreset changed = original[0];
    changed.time.wMinute = 1;
    imported.push_back(changed);
    changed = original[0];
    changed.time.wDay = 2;
    imported.push_back(changed);
    changed = original[0];
    changed.time.wSecond = 1;
    imported.push_back(changed);
    changed = original[0];
    changed.time.wMilliseconds = 1;
    imported.push_back(changed);
    changed = original[0];
    changed.description += L" ";
    imported.push_back(changed);
    changed.description += L"A";
    imported.push_back(changed);
    changed.description.back() = L'a';
    imported.push_back(changed);
    imported.push_back(imported.back());
    Require(calculatorForm.MergePresets(imported), "import merges saved dates");
    Require(calculatorForm.GetPresets().size() == original.size() + 7,
        "exact duplicate skipped; different date, time, whitespace and letter case imported");
    for (size_t index = 0; index < original.size(); index++) {
        const TimeCalculatorPreset& retained = calculatorForm.GetPresets()[index];
        Require(CompareCalculatorDates(retained.time, original[index].time) == 0
            && retained.description == original[index].description,
            "every original record remains unchanged");
    }
    int writes = calculatorPresetWrites;
    Require(calculatorForm.MergePresets(imported) && calculatorPresetWrites == writes,
        "repeated identical import adds nothing and performs no write");
    TimeCalculatorState settings = calculatorForm.GetState();
    settings.tab = 1;
    LoadCalculator(settings);
    Require(calculatorForm.GetPresets().size() == original.size() + 7,
        "replacing window settings never replaces user data");
    size_t retainedCount = calculatorForm.GetPresets().size();
    imported.clear();
    imported.push_back(TimeCalculatorPreset{ CalculatorDate(2030, 1, 1), L"Save must fail" });
    calculatorPresetWriteFails = true;
    Require(!calculatorForm.MergePresets(imported) && calculatorForm.GetPresets().size() == retainedCount,
        "failed import save preserves the in-memory user collection");
    calculatorPresetWriteFails = false;
    std::vector<TimeCalculatorPreset> disk;
    Require(ReadCalculatorPresets(CalculatorTestPresetsPath(false), &disk) && disk.size() == retainedCount,
        "failed import save also preserves the standalone file");
    Require(calculatorForm.MergePresets(std::vector<TimeCalculatorPreset>{})
        && calculatorForm.GetPresets().size() == retainedCount,
        "settings-only import leaves all user data intact");
}
/// Checks that native calendar content fits without overlapping the adjacent fields or the footer.
static void CheckCalculatorCalendar() {
    HWND calendar = CalculatorControl(ID_CALC_CALENDAR);
    RECT minimum = {};
    Require(MonthCal_GetMinReqRect(calendar, &minimum) != FALSE, "native calendar minimum is available");
    RECT client = {};
    GetClientRect(calendar, &client);
    Require(client.right >= minimum.right && client.bottom >= minimum.bottom,
        "all calendar columns, weeks and the Today row fit inside the control");
    Require(client.right >= static_cast<LONG>(MonthCal_GetMaxTodayWidth(calendar)),
        "the complete Today text fits");
    RECT bounds = CalculatorControlBounds(GetParent(calendar), ID_CALC_CALENDAR);
    RECT fields = CalculatorControlBounds(GetParent(calendar), ID_CALC_START_LABEL);
    RECT note = CalculatorControlBounds(GetParent(calendar), ID_CALC_ROUND_NOTE);
    std::printf("Calendar: actual %ld x %ld, required %ld x %ld, space %ld x %ld.\n",
        client.right, client.bottom, minimum.right, minimum.bottom,
        fields.left - bounds.left, note.top - bounds.top);
    Require(bounds.right <= fields.left && bounds.bottom <= note.top,
        "calendar fits in its column above the footer without moving other controls");
    HFONT font = reinterpret_cast<HFONT>(SendMessageW(calendar, WM_GETFONT, 0, 0));
    HFONT formFont = reinterpret_cast<HFONT>(SendMessageW(calculatorForm.GetWindow(), WM_GETFONT, 0, 0));
    Require(font == formFont, "calendar retains the effective application font");
    HWND intervalPage = GetParent(CalculatorControl(ID_CALC_INTERVAL_NOTE));
    RECT intervalNote = CalculatorControlBounds(intervalPage, ID_CALC_INTERVAL_NOTE);
    SIZE intervalPosition = InformationDialogUnits(formFont, 3, 149);
    Require(intervalNote.top == intervalPosition.cy,
        "calendar expansion preserves the interval footer's resource position and 15-DLU spacing");
    if (GetWindowTheme(calendar) == nullptr) {
        Require(MonthCal_GetCalendarBorder(calendar) == 0, "inline classic calendar has zero border");
        HWND window = calculatorForm.GetWindow();
        Require(MonthCal_GetColor(calendar, MCSC_TITLEBK) == DialogFrame::GetColor(window, COLOR_HIGHLIGHT),
            "inline calendar title uses the dialog highlight color");
        Require(MonthCal_GetColor(calendar, MCSC_TITLETEXT) == DialogFrame::GetColor(window,
            COLOR_HIGHLIGHTTEXT), "inline calendar title text uses the dialog highlight text color");
    }
}

/// Checks native popup styling and captures the actual picker inset while keeping every window isolated.
static void CheckCalculatorPickerStyle() {
    HWND window = calculatorForm.GetWindow();
    HHOOK hook = SetWindowsHookExW(WH_CBT, CalculatorPopupIsolation, nullptr, GetCurrentThreadId());
    Require(hook != nullptr, "native popup activation is blocked during the private-desktop test");
    if (hook == nullptr) {
        return;
    }
    calculatorPresented = true;
    SetWindowPos(window, nullptr, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_SHOWWINDOW);
    HWND picker = CalculatorControl(ID_CALC_START);
    bool classic = GetWindowTheme(picker) == nullptr;
    std::wstring prefix = L"picker-themed";
    if (classic) {
        prefix = windows2000Style ? L"picker-windows2000" : L"picker-classic";
    }
    SetWindowSubclass(picker, CalculatorCalendarProc, CALCULATOR_LOCALE_SUBCLASS, 0);
    CaptureCalculatorImage(picker, (prefix + L"-native").c_str(), false);
    SetWindowSubclass(picker, CalculatorCalendarProc, CALCULATOR_LOCALE_SUBCLASS, 1);
    CaptureCalculatorImage(picker, (prefix + L"-inset").c_str(), false);
    SendMessageW(picker, WM_KEYDOWN, VK_F4, 0);
    HWND calendar = DateTime_GetMonthCal(picker);
    Require(calendar != nullptr, "native DateTime picker opens its real month calendar");
    if (calendar != nullptr) {
        Require((GetWindowLongPtrW(calendar, GWL_EXSTYLE) & WS_EX_NOACTIVATE) != 0,
            "native popup is nonactivating before presentation");
        Require((GetWindowTheme(calendar) == nullptr) == classic, "picker popup inherits its visual style");
        if (classic) {
            Require(MonthCal_GetCalendarBorder(calendar) == 0, "picker popup has zero calendar border");
            Require(MonthCal_GetColor(calendar, MCSC_TITLEBK) == DialogFrame::GetColor(window,
                COLOR_HIGHLIGHT), "picker popup title uses the dialog's highlight color");
            Require(MonthCal_GetColor(calendar, MCSC_TITLETEXT) == DialogFrame::GetColor(window,
                COLOR_HIGHLIGHTTEXT), "picker popup title text uses the dialog's highlighted text color");
        }
        RECT client = {};
        RECT minimum = {};
        GetClientRect(calendar, &client);
        MonthCal_GetMinReqRect(calendar, &minimum);
        std::printf("Popup: client %ld x %ld, minimum %ld x %ld, style %Ix, extended %Ix.\n",
            client.right, client.bottom, minimum.right, minimum.bottom,
            GetWindowLongPtrW(calendar, GWL_STYLE), GetWindowLongPtrW(calendar, GWL_EXSTYLE));
        Require(client.right >= minimum.right && client.bottom >= minimum.bottom,
            "the complete popup calendar fits after native drop-down positioning");
        CaptureCalculatorImage(calendar, (prefix + L"-calendar").c_str(), false);
        SendMessageW(picker, DTM_CLOSEMONTHCAL, 0, 0);
    }
    SetWindowPos(window, nullptr, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_HIDEWINDOW);
    calculatorPresented = false;
    UnhookWindowsHookEx(hook);
}

/// Changes every highlight checkbox through native notifications and verifies persistent form state.
static void TestCalculatorHighlightControls() {
    TimeCalculatorState original = calculatorForm.GetState();
    Require(TabCtrl_GetItemCount(CalculatorControl(ID_CALC_TABS)) == TIME_CALCULATOR_PAGE_COUNT,
        "calculator exposes the highlight settings tab");
    CalculatorPage(3);
    for (int index = 0; index < TIME_CALCULATOR_HIGHLIGHT_COUNT; index++) {
        HWND control = CalculatorControl(ID_CALC_HIGHLIGHT_BASE + index);
        Require(control != nullptr && !GetControlText(control).empty(),
            "highlight checkbox has a translated caption");
        SendMessageW(control, BM_SETCHECK, BST_UNCHECKED, 0);
        CalculatorCommand(ID_CALC_HIGHLIGHT_BASE + index);
    }
    Require(calculatorForm.GetState().highlights == 0, "unchecking all rules clears every highlight flag");
    NMDAYSTATE request = {};
    request.nmhdr.hwndFrom = CalculatorControl(ID_CALC_CALENDAR);
    request.nmhdr.idFrom = ID_CALC_CALENDAR;
    request.nmhdr.code = MCN_GETDAYSTATE;
    request.stStart = CalculatorDate(2026, 11, 1);
    request.cDayState = 1;
    SendMessageW(GetParent(request.nmhdr.hwndFrom), WM_NOTIFY, ID_CALC_CALENDAR,
        reinterpret_cast<LPARAM>(&request));
    Require(request.prgDayState != nullptr && request.prgDayState[0] == 0,
        "native calendar receives an empty bold-day mask when every rule is disabled");
    for (int index = 0; index < TIME_CALCULATOR_HIGHLIGHT_COUNT; index++) {
        HWND control = CalculatorControl(ID_CALC_HIGHLIGHT_BASE + index);
        SendMessageW(control, BM_SETCHECK, BST_CHECKED, 0);
        CalculatorCommand(ID_CALC_HIGHLIGHT_BASE + index);
    }
    Require(calculatorForm.GetState().highlights == TIME_CALCULATOR_ALL_HIGHLIGHTS,
        "all switches include repeated sixes and nines");
    RefreshCalculator();
    for (int index = 0; index < TIME_CALCULATOR_HIGHLIGHT_COUNT; index++) {
        Require(SendMessageW(CalculatorControl(ID_CALC_HIGHLIGHT_BASE + index),
            BM_GETCHECK, 0, 0) == BST_CHECKED, "refresh retains highlight selections");
    }
    LoadCalculator(original);
}

/// Checks input range, font/theme changes, window-handle preservation, recreation and small work-area
/// overflow.
static void TestCalculatorAppearance() {
    TestCalculatorHighlightControls();
    CaptureCalculatorPages(L"calculator-system");
    CalculatorPage(1);
    CheckCalculatorCalendar();
    HWND original = calculatorForm.GetWindow();
    TimeCalculatorState originalState = calculatorForm.GetState();
    SYSTEMTIME limits[2] = {};
    DWORD flags = DateTime_GetRange(CalculatorControl(ID_CALC_FROM), limits);
    Require((flags & (GDTR_MIN | GDTR_MAX)) == (GDTR_MIN | GDTR_MAX)
        && limits[0].wYear == 1601
        && limits[1].wYear == 9999, "date picker exposes full supported range");
    appFontFace = L"Cambria Math";
    Require(calculatorForm.ApplyStyle(true), "application font change relayout succeeds");
    Require(calculatorForm.GetWindow() == original && calculatorForm.GetState().tab == 1,
        "font relayout preserves HWND and selected tab");
    Require(SameCalculatorState(originalState, calculatorForm.GetState()),
        "font relayout preserves all input data");
    RefreshCalculator();
    for (int index = 0; index < 4; index++) {
        HWND combo = CalculatorControl(ID_CALC_ZONE_BASE + index);
        Require(GetSettingsComboBox(combo) != combo, "calculator uses the Settings combo renderer");
        Require(SendMessageW(combo, CB_GETCURSEL, 0, 0) != CB_ERR,
            "font change retains a selected time zone");
        HWND offset = CalculatorControl(ID_CALC_OFFSET_BASE + index);
        Require(SendMessageW(offset, CB_GETCURSEL, 0, 0) != CB_ERR,
            "font change retains a selected UTC offset");
    }
    CheckCalculatorCalendar();
    CaptureCalculatorPages(L"calculator-cambria");
    appLanguage = LANG_CS;
    RefreshCalculator();
    Require(calculatorForm.GetWindow() == original && calculatorForm.GetState().tab == 1,
        "language refresh preserves HWND and selected tab");
    Require(SameCalculatorState(originalState, calculatorForm.GetState()),
        "language refresh preserves all input data");
    themesDisabled = true;
    windows2000Style = true;
    ApplyUiStyle(original);
    Require(calculatorForm.ApplyStyle(true), "Windows 2000 style retains the custom application font");
    CheckCalculatorCalendar();
    CaptureCalculator(L"calculator-windows2000-cambria-calendar");
    appFontFace.clear();
    ApplyUiStyle(original);
    Require(calculatorForm.ApplyStyle(true), "Windows 2000 font and control style update succeeds");
    Require(calculatorForm.GetWindow() == original, "Windows 2000 style update retains the existing HWND");
    Require(SameCalculatorState(originalState, calculatorForm.GetState()),
        "Windows 2000 style preserves all input data");
    CheckCalculatorCalendar();
    CaptureCalculatorPages(L"calculator-windows2000");
    CheckCalculatorPickerStyle();
    windows2000Style = false;
    ApplyUiStyle(original);
    Require(calculatorForm.ApplyStyle(true), "plain classic style update succeeds");
    CheckCalculatorCalendar();
    CheckCalculatorPickerStyle();
    size_t presets = calculatorForm.GetPresets().size();
    calculatorForm.Close();
    themesDisabled = false;
    windows2000Style = false;
    ShowCalculator();
    Require(calculatorForm.GetWindow() != nullptr
        && calculatorForm.GetState().tab == 1
        && calculatorForm.GetPresets().size() == presets, "style recreation preserves tab and saved values");
    Require(SameCalculatorState(originalState, calculatorForm.GetState()),
        "style recreation preserves all input data");
    CheckCalculatorPickerStyle();
    calculatorSmallWorkArea = true;
    calculatorForm.ApplyStyle(true);
    RECT bounds = {};
    GetWindowRect(calculatorForm.GetWindow(), &bounds);
    Require(bounds.right - bounds.left <= 480 && bounds.bottom - bounds.top <= 320,
        "calculator fits a restricted work area");
    LONG_PTR style = GetWindowLongPtrW(calculatorForm.GetWindow(), GWL_STYLE);
    Require((style & WS_VSCROLL) != 0 && (style & WS_HSCROLL) != 0,
        "small work area exposes both overflow axes");
    RECT unscrolledTabs = {};
    GetWindowRect(CalculatorControl(ID_CALC_TABS), &unscrolledTabs);
    MapWindowPoints(HWND_DESKTOP, calculatorForm.GetWindow(), reinterpret_cast<POINT*>(&unscrolledTabs), 2);
    SendMessageW(calculatorForm.GetWindow(), WM_VSCROLL, SB_BOTTOM, 0);
    SendMessageW(calculatorForm.GetWindow(), WM_HSCROLL, SB_BOTTOM, 0);
    RECT note = {};
    RECT client = {};
    GetWindowRect(CalculatorControl(ID_CALC_ROUND_NOTE), &note);
    MapWindowPoints(HWND_DESKTOP, calculatorForm.GetWindow(), reinterpret_cast<POINT*>(&note), 2);
    GetClientRect(calculatorForm.GetWindow(), &client);
    Require(note.top >= 0 && note.bottom <= client.bottom && note.right <= client.right,
        "scrolling to the bottom reveals the final content row");
    CaptureCalculator(L"calculator-small-workarea");
    for (int pass = 0; pass < 2; pass++) {
        SendMessageW(calculatorForm.GetWindow(), WM_VSCROLL, SB_BOTTOM, 0);
        SendMessageW(calculatorForm.GetWindow(), WM_HSCROLL, SB_BOTTOM, 0);
        Require(GetScrollPos(calculatorForm.GetWindow(), SB_HORZ) > 0
            && GetScrollPos(calculatorForm.GetWindow(), SB_VERT) > 0, "both overflow axes were scrolled");
        if (pass == 0) {
            calculatorForm.ApplyStyle(true);
        } else {
            RefreshCalculator();
        }
        Require(GetScrollPos(calculatorForm.GetWindow(), SB_HORZ) == 0
            && GetScrollPos(calculatorForm.GetWindow(), SB_VERT) == 0,
            "font and language reflow reset both native scroll positions");
        RECT restoredTabs = {};
        GetWindowRect(CalculatorControl(ID_CALC_TABS), &restoredTabs);
        MapWindowPoints(HWND_DESKTOP, calculatorForm.GetWindow(), reinterpret_cast<POINT*>(&restoredTabs), 2);
        Require(EqualRect(&restoredTabs, &unscrolledTabs) != FALSE,
            "font and language reflow restore the original unscrolled content geometry");
    }
    calculatorSmallWorkArea = false;
}

/// Performs the explicitly requested brief visible check without activation, input or persisted user
/// settings.
static void TestCalculatorVisible() {
    HWND window = calculatorForm.GetWindow();
    LONG_PTR extended = GetWindowLongPtrW(window, GWL_EXSTYLE);
    extended = extended & ~WS_EX_APPWINDOW | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE;
    SetWindowLongPtrW(window, GWL_EXSTYLE, extended);
    TimeCalculatorState maximum = calculatorForm.GetState();
    maximum.from = CalculatorDate(1601, 1, 1);
    maximum.to = CalculatorDate(9999, 12, 31, 23, 59);
    maximum.tab = 0;
    LoadCalculator(maximum);
    const AppLanguage languages[] = { LANG_EN_US, LANG_CS, LANG_DE, LANG_EN_US };
    const wchar_t* names[] = {
        L"calculator-visible-en",
        L"calculator-visible-cs",
        L"calculator-visible-de",
        L"calculator-visible-cambria"
    };
    HWND foreground = GetForegroundWindow();
    ULONGLONG visibleMilliseconds = 0;
    for (int index = 0; index < 4; index++) {
        appLanguage = languages[index];
        if (index == 3) {
            appFontFace = L"Cambria Math";
            calculatorForm.ApplyStyle(true);
        }
        RefreshCalculator();
        ULONGLONG started = GetTickCount64();
        calculatorPresented = true;
        SetWindowPos(window, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
        MSG pending = {};
        while (PeekMessageW(&pending, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&pending);
            DispatchMessageW(&pending);
        }
        RedrawWindow(window, nullptr, nullptr,
            RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN | RDW_UPDATENOW);
        while (PeekMessageW(&pending, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&pending);
            DispatchMessageW(&pending);
        }
        GdiFlush();
        DwmFlush();
        Sleep(150);
        DwmFlush();
        if (!IsWindowVisible(window)) {
            Require(false, "capture window was hidden by native layout or paint");
            calculatorPresented = false;
            break;
        }
        std::wstring screen = std::wstring(names[index]) + L"-screen";
        CaptureCalculatorImage(window, screen.c_str(), true);
        SetWindowPos(window, nullptr, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_HIDEWINDOW);
        calculatorPresented = false;
        visibleMilliseconds += GetTickCount64() - started;
        if (visibleMilliseconds >= 5000) {
            break;
        }
    }
    calculatorForm.Close();
    Require(visibleMilliseconds < 5000, "explicit visible check remains below five seconds total");
    Require(GetForegroundWindow() == foreground, "brief visible check preserves foreground window");
    std::printf("Visible presentation lasted %llu milliseconds; calculator closed.\n", visibleMilliseconds);
}

/// Defaults to an unshown private desktop; the explicit visible mode retains every activation/storage
/// substitute.
int wmain(int argc, wchar_t** argv) {
    bool visibleCheck = argc == 3 && wcscmp(argv[2], L"--visible-check") == 0;
    bool pickerCheck = argc == 3 && wcscmp(argv[2], L"--picker-check") == 0;
    bool appearanceCheck = argc == 3 && wcscmp(argv[2], L"--appearance-check") == 0;
    bool calculationCheck = argc == 3 && wcscmp(argv[2], L"--calculation-check") == 0;
    bool wheelCheck = argc == 3 && wcscmp(argv[2], L"--wheel-check") == 0;
    if (argc != 2 && !visibleCheck && !pickerCheck && !appearanceCheck && !calculationCheck && !wheelCheck) {
        return 2;
    }
    calculatorGuiThread = GetCurrentThreadId();
    calculatorWorkerGate = CreateEventW(nullptr, TRUE, TRUE, nullptr);
    if (calculatorWorkerGate == nullptr) {
        return 2;
    }
    calculatorArtifacts = argv[1];
    DeleteFileW(CalculatorTestPresetsPath(false).c_str());
    testXmlPath = calculatorArtifacts + L"\\calculator-isolated.xml";
    HDESK previous = GetThreadDesktop(GetCurrentThreadId());
    std::wstring desktopName = L"CalClockCalculatorTests-" + std::to_wstring(GetCurrentProcessId());
    HDESK desktop = nullptr;
    if (!visibleCheck) {
        desktop = CreateDesktopW(desktopName.c_str(), nullptr, nullptr, 0, GENERIC_ALL, nullptr);
        if (desktop == nullptr || !SetThreadDesktop(desktop)) {
            std::fprintf(stderr, "Cannot create isolated desktop: %lu\n", GetLastError());
            return 2;
        }
    }
    INITCOMMONCONTROLSEX common{
        sizeof(common),
        ICC_WIN95_CLASSES | ICC_STANDARD_CLASSES | ICC_USEREX_CLASSES | ICC_DATE_CLASSES
    };
    InitCommonControlsEx(&common);
    InstallCalendarLocaleHook();
    LoadTimeZoneList(&timeZones);
    hInstance = GetModuleHandleW(nullptr);
    appLanguage = LANG_EN_US;
    useNtpTime = false;
    winsockReady = false;
    storageUsesXml = false;
    settingsWindowState.SetSavingOptions(PersistWindowStateSavingOptions::None);
    helpWindowState.SetSavingOptions(PersistWindowStateSavingOptions::None);
    aboutWindowState.SetSavingOptions(PersistWindowStateSavingOptions::None);
    calculatorWindowState.SetSavingOptions(PersistWindowStateSavingOptions::None);
    calculatorWindowState.SetSingleInstance(false);
    calculatorWindowState.SetDetectionOptions(WindowDetectionOptions::NoDetection);
    TimeCalculatorState state;
    state.fromZone = L"UTC+00:00";
    state.toZone = L"UTC+00:00";
    state.startZone = L"UTC+00:00";
    state.from = CalculatorDate(2026, 1, 1);
    state.to = CalculatorDate(2026, 1, 10, 1, 2);
    state.start = CalculatorDate(2026, 1, 1, 13, 37);
    state.day = CalculatorDate(2026, 1, 2);
    LoadCalculator(state);
    if (pickerCheck) {
        appLanguage = LANG_CS;
        themesDisabled = true;
        windows2000Style = true;
    }
    ShowCalculator();
    if (calculatorForm.GetWindow() != nullptr && wheelCheck) {
        TestCalculatorTabWheel();
        calculatorForm.Close();
    } else if (calculatorForm.GetWindow() != nullptr && pickerCheck) {
        CalculatorPage(1);
        CheckCalculatorCalendar();
        CaptureCalculator(L"calculator-picker-style");
        CheckCalculatorPickerStyle();
        calculatorForm.Close();
    } else if (calculatorForm.GetWindow() != nullptr && appearanceCheck) {
        TestCalculatorAppearance();
        calculatorForm.Close();
    } else if (calculatorForm.GetWindow() != nullptr && visibleCheck) {
        TestCalculatorVisible();
    } else if (calculatorForm.GetWindow() != nullptr) {
        TestCalculatorTimeZones();
        TestCalculatorInitialAndNow();
        TestCalculatorResultNotifications();
        TestCalculatorCalendarNotifications();
        TestCalculatorBackgroundWork();
        TestCalculatorTabWheel();
        if (!calculationCheck) {
            TestCalculatorRangesAndLanguages();
        }
        TestCalculatorPresets();
        TestCalculatorConfirmationImport();
        TestCalculatorMerge();
        if (!calculationCheck) {
            TestCalculatorAppearance();
        }
        calculatorForm.Close();
    } else {
        Require(false, "calculator form created from linked production resources");
    }
    WaitForCalculator();
    CloseHandle(calculatorWorkerGate);
    calculatorWorkerGate = nullptr;
    if (desktop != nullptr) {
        SetThreadDesktop(previous);
        CloseDesktop(desktop);
    }
    if (testFailures != 0) {
        return 1;
    }
    if (wheelCheck) {
        std::puts("PASS: shared combo focus, font/theme updates, dropdown acceptance and tab navigation; "
            "inactive tab scrolling.");
    } else if (pickerCheck) {
        std::puts("PASS: isolated picker styling and native calendar rendering.");
    } else if (appearanceCheck) {
        std::puts("PASS: isolated calculator fonts, classic and themed pickers, calendar sizing and "
            "overflow.");
    } else if (visibleCheck) {
        std::puts("PASS: explicit nonactivating visible calculator render check.");
    } else if (calculationCheck) {
        std::puts("PASS: isolated native interval results, calendar masks, rule choices, presets and "
            "import.");
    } else {
        std::puts("PASS: isolated calculator tabs, Now, presets, font/theme reflow, recreation and "
            "overflow.");
    }
    return 0;
}
