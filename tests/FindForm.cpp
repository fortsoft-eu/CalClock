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

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <iterator>

static HWND findTestActiveWindow = nullptr;
static bool findTestControl = false;
static bool findTestShift = false;

/// Supplies logical active-window state without activating any test window.
static HWND WINAPI FindTestGetActiveWindow() {
    return findTestActiveWindow;
}

/// Supplies shortcut modifiers without sending input or changing the keyboard layout.
static SHORT WINAPI FindTestGetKeyState(int key) {
    return (key == VK_CONTROL && findTestControl || key == VK_SHIFT && findTestShift)
        ? static_cast<SHORT>(0x8000)
        : 0;
}

#define GetActiveWindow FindTestGetActiveWindow
#define GetKeyState FindTestGetKeyState
#define wmain AlarmSettingsRegressionEntry
#include "AlarmSettings.cpp"
#undef wmain

#define SetFocus TestSetFocus
#define SetActiveWindow TestSetActiveWindow
#define SetForegroundWindow TestWindowActivation
#define BringWindowToTop TestWindowActivation
#define AttachThreadInput TestAttachThreadInput
#define AllowSetForegroundWindow TestAllowSetForegroundWindow
#define ShowWindow TestShowWindow
#define SetWindowPos TestSetWindowPos
#define CreateDialogIndirectParamW TestCreateDialogIndirectParamW
#define MessageBoxW TestMessageBoxW
#include "../CalClock/FindForm.cpp"
#include "../CalClock/AboutForm.cpp"
#include "../CalClock/HelpForm.cpp"
#include "../CalClock/PersistWindowState.cpp"
#undef SetFocus
#undef SetActiveWindow
#undef SetForegroundWindow
#undef BringWindowToTop
#undef AttachThreadInput
#undef AllowSetForegroundWindow
#undef ShowWindow
#undef SetWindowPos
#undef CreateDialogIndirectParamW
#undef MessageBoxW
#undef GetActiveWindow
#undef GetKeyState

/// Reads a file as bytes for extraction and serialized-options checks.
static std::string ReadTestBytes(const std::wstring& path) {
    std::ifstream input(path, std::ios::binary);
    return std::string(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>());
}

/// Checks full DLL extraction, cache reuse and repair, and every icon index at native sizes.
static void TestResourceLibrary(const std::wstring& directory) {
    std::wstring cache = directory + L"\\library-cache";
    Require(SUCCEEDED(iconLibrary.Initialize(hInstance, cache)), "extract complete embedded resource DLL");
    std::string expected = ReadTestBytes(L"CalClock\\Resources\\Resources.dll");
    Require(!expected.empty() && ReadTestBytes(iconLibrary.GetPath()) == expected,
        "extracted DLL is byte-identical to the source library");
    WIN32_FILE_ATTRIBUTE_DATA before = {};
    WIN32_FILE_ATTRIBUTE_DATA after = {};
    GetFileAttributesExW(iconLibrary.GetPath().c_str(), GetFileExInfoStandard, &before);
    Require(SUCCEEDED(iconLibrary.Initialize(hInstance, cache)), "reuse existing library cache");
    GetFileAttributesExW(iconLibrary.GetPath().c_str(), GetFileExInfoStandard, &after);
    Require(CompareFileTime(&before.ftLastWriteTime, &after.ftLastWriteTime) == 0,
        "valid library cache is not rewritten");
    const int sizes[] = { 16, 20, 24, 32, 48, 64, 256 };
    for (int index = 0; index < 5; index++) {
        for (int size : sizes) {
            HICON icon = iconLibrary.LoadIconAtIndex(index, size, size);
            Require(icon != nullptr, "load every indexed icon at every requested native size");
            if (icon != nullptr) {
                DestroyIcon(icon);
            }
        }
    }
    HANDLE file = CreateFileW(iconLibrary.GetPath().c_str(), GENERIC_WRITE, 0, nullptr,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    Require(file != INVALID_HANDLE_VALUE, "open isolated cache for corruption test");
    if (file != INVALID_HANDLE_VALUE) {
        DWORD written = 0;
        BYTE invalid = 0;
        WriteFile(file, &invalid, 1, &written, nullptr);
        CloseHandle(file);
    }
    Require(SUCCEEDED(iconLibrary.Initialize(hInstance, cache)), "repair corrupted resource cache");
    Require(ReadTestBytes(iconLibrary.GetPath()) == expected, "cache repair restores the complete DLL");
}

/// Checks packed XML flags, unknown bits, dependent options, and absence of legacy boolean fallback.
static void TestPackedOptions() {
    SettingsSnapshot value = {};
    value.widgets.push_back(AlarmConfiguration(1));
    value.options = 0x80000000;
    value.themesDisabled = true;
    value.windows2000Style = true;
    value.snapWidgetsToWorkArea = true;
    value.warnOnUnsavedChanges = true;
    value.generatedTimeSignal = true;
    value.fontItalic = true;
    value.useNtpTime = true;
    value.alternativeTrayIcon = true;
    value.classicTrayIcon = true;
    Require(WriteSettingsXml(testXmlPath, value), "serialize all packed application options");
    SettingsSnapshot restored = {};
    Require(ReadSettingsXml(testXmlPath, LANG_EN_US, CreateStoredWidgetDefaults, &restored),
        "read packed application options");
    Require(restored.options == 0x800001FF
            && restored.themesDisabled
            && restored.windows2000Style
            && restored.snapWidgetsToWorkArea
            && restored.warnOnUnsavedChanges
            && restored.generatedTimeSignal
            && restored.fontItalic
            && restored.useNtpTime
            && restored.alternativeTrayIcon
            && restored.classicTrayIcon,
        "all options and unknown bits survive XML round trip");
    std::string xml = ReadTestBytes(testXmlPath);
    std::string root = xml.substr(xml.find("<CalClockSettings"));
    root.resize(root.find('>') + 1);
    Require(root.find("disableThemes=") == std::string::npos
            && root.find("fontItalic=") == std::string::npos
            && root.find("useNtpTime=") == std::string::npos,
        "global boolean attributes are no longer written");
    value.themesDisabled = false;
    value.alternativeTrayIcon = false;
    Require(WriteSettingsXml(testXmlPath, value), "serialize disabled parent options");
    Require(ReadSettingsXml(testXmlPath, LANG_EN_US, CreateStoredWidgetDefaults, &restored),
        "read disabled parent options");
    Require(!restored.windows2000Style && !restored.classicTrayIcon,
        "dependent style and classic-icon flags require their parent options");
    xml = ReadTestBytes(testXmlPath);
    size_t start = xml.find("options=\"");
    Require(start != std::string::npos, "serialized XML contains one packed Options value");
    if (start != std::string::npos) {
        size_t end = xml.find('"', start + 9);
        xml.replace(start, end - start + 1,
            "disableThemes=\"1\" windows2000Style=\"1\" fontItalic=\"1\" useNtpTime=\"0\"");
        std::ofstream output(testXmlPath, std::ios::binary | std::ios::trunc);
        output.write(xml.data(), xml.size());
        output.close();
        restored = SettingsSnapshot{};
        Require(ReadSettingsXml(testXmlPath, LANG_EN_US, CreateStoredWidgetDefaults, &restored),
            "read XML containing only obsolete global flags");
        Require(!restored.themesDisabled
                && !restored.windows2000Style
                && !restored.fontItalic
                && restored.useNtpTime,
            "obsolete global XML flags have no fallback");
    }
}

/// Checks exclusive appearance modes and independent child themes in the packed Options value.
static void TestAppearanceOptions() {
    for (int mode = 0; mode < APPLICATION_STYLE_COUNT; mode++) {
        SettingsSnapshot value = {};
        value.widgets.push_back(AlarmConfiguration(1));
        value.options = 0x80000000;
        value.themesDisabled = true;
        value.basicWindowHeaders = mode == 1;
        value.windows2000Headers = mode == 2;
        value.windows2000Style = mode == 3;
        Require(WriteSettingsXml(testXmlPath, value), "write the selected appearance mode");
        SettingsSnapshot restored = {};
        Require(ReadSettingsXml(testXmlPath, LANG_EN_US, CreateStoredWidgetDefaults, &restored),
            "read the selected appearance mode");
        Require(restored.themesDisabled
                && restored.basicWindowHeaders == value.basicWindowHeaders
                && restored.windows2000Headers == value.windows2000Headers
                && restored.windows2000Style == value.windows2000Style
                && (restored.options & 0x80000000) != 0,
            "all four appearance modes preserve their state and unknown Options bits");
        value.themesDisabled = false;
        Require(WriteSettingsXml(testXmlPath, value), "write appearance options with themes enabled");
        Require(ReadSettingsXml(testXmlPath, LANG_EN_US, CreateStoredWidgetDefaults, &restored),
            "read appearance options with themes enabled");
        Require(!restored.themesDisabled
                && restored.basicWindowHeaders == value.basicWindowHeaders
                && restored.windows2000Headers == value.windows2000Headers
                && !restored.windows2000Style,
            "header choices survive enabled themes; complete Windows 2000 forms require disabled themes");
    }
}

/// Checks the existing modeless forms and the license's dedicated Consolas font with a custom UI font.
static void TestInformationForms() {
    appFontFace = L"Arial";
    aboutForm.Show(hInstance, aboutWindowState);
    helpForm.Show(hInstance, helpWindowState);
    HWND windows[] = { aboutForm.GetWindow(), helpForm.GetWindow() };
    for (HWND window : windows) {
        Require(window != nullptr && GetWindow(window, GW_OWNER) == nullptr,
            "information form remains modeless without an owner window");
        Require(GetWindowLongPtrW(window, GWL_STYLE) & WS_MINIMIZEBOX,
            "information form retains its minimize button");
        Require(GetWindowLongPtrW(window, GWL_EXSTYLE) & WS_EX_APPWINDOW,
            "information form retains its taskbar button");
        Require(!IsWindowVisible(window) && GetWindowLongPtrW(window, GWL_EXSTYLE) & WS_EX_NOACTIVATE,
            "information test form remains hidden and nonactivating");
        HWND edit = GetDlgItem(window, ID_INFO_TEXT);
        Require(GetWindowLongPtrW(edit, GWL_STYLE) & ES_NOHIDESEL,
            "information selection remains visible without focus");
        HWND button = GetDlgItem(window, ID_INFO_CLOSE);
        MSG correction = {};
        while (PeekMessageW(&correction, button, WM_RECOLOR_BUTTON, WM_RECOLOR_BUTTON, PM_REMOVE)) {
            DispatchMessageW(&correction);
        }
        SendMessageW(window, WM_ACTIVATE, WA_INACTIVE, 0);
        BOOL queued = PeekMessageW(&correction, button, WM_RECOLOR_BUTTON, WM_RECOLOR_BUTTON, PM_REMOVE);
        Require(queued != FALSE, "form deactivation queues the existing Close button color correction");
        if (queued) {
            DispatchMessageW(&correction);
        }
    }
    CheckResourceButtonHeights(aboutForm.GetWindow(), IDD_ABOUT);
    CheckResourceButtonHeights(helpForm.GetWindow(), IDD_HELP);
    const int sizes[] = { 90, 130 };
    for (int size : sizes) {
        appFontDialogSize = size;
        for (bool disabled : { false, true }) {
            themesDisabled = disabled;
            Require(aboutForm.ApplyStyle(true) && helpForm.ApplyStyle(true),
                "information form relayout succeeds after font and theme changes");
            CheckResourceButtonHeights(aboutForm.GetWindow(), IDD_ABOUT);
            CheckResourceButtonHeights(helpForm.GetWindow(), IDD_HELP);
        }
    }
    appFontDialogSize = 90;
    themesDisabled = false;
    Require(aboutForm.ApplyStyle(true) && helpForm.ApplyStyle(true), "restore information form styles");
    LOGFONTW license = {};
    HFONT font = reinterpret_cast<HFONT>(SendDlgItemMessageW(aboutForm.GetWindow(), ID_INFO_TEXT,
        WM_GETFONT, 0, 0));
    bool licenseUsesConsolas = GetObjectW(font, sizeof(license), &license) != 0
        && _wcsicmp(license.lfFaceName, L"Consolas") == 0;
    Require(licenseUsesConsolas, "About license retains Consolas with a different application font");
    appFontFace.clear();
}

/// Checks the actual edit selection independently of search implementation state.
static void RequireSelection(HWND edit, DWORD expectedStart, DWORD expectedEnd) {
    DWORD start = 0;
    DWORD end = 0;
    SendMessageW(edit, EM_GETSEL, reinterpret_cast<WPARAM>(&start), reinterpret_cast<LPARAM>(&end));
    if (start != expectedStart || end != expectedEnd) {
        std::fprintf(stderr, "Selection: %lu..%lu; expected %lu..%lu\n", start, end, expectedStart,
            expectedEnd);
    }
    Require(start == expectedStart && end == expectedEnd, "search selects the expected UTF-16 text");
}

/// Enters a query through the real ComboBoxEx edit and invokes the native Find Next command.
static void SearchFor(HWND owner, const wchar_t* query, bool resetSelection = true) {
    HWND dialog = find.GetWindow();
    HWND edit = FindHistoryEdit(dialog);
    SetWindowTextW(edit, query);
    SendMessageW(dialog, WM_COMMAND, MAKEWPARAM(IDC_FIND_TEXT, CBN_EDITCHANGE),
        reinterpret_cast<LPARAM>(GetDlgItem(dialog, IDC_FIND_TEXT)));
    Require(IsWindowEnabled(GetDlgItem(dialog, IDOK)) != FALSE, "typed query enables Find Next");
    if (resetSelection) {
        SendDlgItemMessageW(owner, ID_INFO_TEXT, EM_SETSEL, 0, 0);
    }
    findTestActiveWindow = dialog;
    SendMessageW(dialog, WM_COMMAND, IDOK, 0);
}

/// Keeps history highlights from changing matching options and restores unfinished text on cancellation.
static void TestFindHistoryCommit(HWND owner) {
    HWND dialog = find.GetWindow();
    HWND combo = GetDlgItem(dialog, IDC_FIND_TEXT);
    HWND edit = FindHistoryEdit(dialog);
    CheckDlgButton(dialog, IDC_FIND_REGEX, BST_UNCHECKED);
    CheckDlgButton(dialog, IDC_FIND_MATCH_CASE, BST_CHECKED);
    SearchFor(owner, L"Alpha");
    CheckDlgButton(dialog, IDC_FIND_MATCH_CASE, BST_UNCHECKED);
    SetComboSelection(combo, -1);
    SetWindowTextW(edit, L"unfinished query");
    SendMessageW(edit, EM_SETSEL, 2, 7);
    SendMessageW(dialog, WM_COMMAND, MAKEWPARAM(IDC_FIND_TEXT, CBN_EDITCHANGE), 0);
    SendMessageW(dialog, WM_COMMAND, MAKEWPARAM(IDC_FIND_TEXT, CBN_DROPDOWN), 0);
    SetComboSelection(combo, 0);
    SendMessageW(dialog, WM_COMMAND, MAKEWPARAM(IDC_FIND_TEXT, CBN_SELCHANGE), 0);
    SendMessageW(dialog, WM_COMMAND, MAKEWPARAM(IDC_FIND_TEXT, CBN_EDITCHANGE), 0);
    Require(IsDlgButtonChecked(dialog, IDC_FIND_MATCH_CASE) == BST_UNCHECKED,
        "history highlights do not apply stored matching options");
    SendMessageW(dialog, WM_COMMAND, MAKEWPARAM(IDC_FIND_TEXT, CBN_SELENDCANCEL), 0);
    SendMessageW(dialog, WM_COMMAND, MAKEWPARAM(IDC_FIND_TEXT, CBN_CLOSEUP), 0);
    Require(GetControlText(edit) == L"unfinished query",
        "cancelled history navigation restores unfinished text without an original selected item");
    RequireSelection(edit, 2, 7);
    SendMessageW(dialog, WM_COMMAND, MAKEWPARAM(IDC_FIND_TEXT, CBN_DROPDOWN), 0);
    SetComboSelection(combo, 0);
    SendMessageW(dialog, WM_COMMAND, MAKEWPARAM(IDC_FIND_TEXT, CBN_SELENDOK), 0);
    Require(IsDlgButtonChecked(dialog, IDC_FIND_MATCH_CASE) == BST_UNCHECKED,
        "history options remain unchanged until accepted dropdown closes");
    SendMessageW(dialog, WM_COMMAND, MAKEWPARAM(IDC_FIND_TEXT, CBN_CLOSEUP), 0);
    Require(IsDlgButtonChecked(dialog, IDC_FIND_MATCH_CASE) == BST_CHECKED
            && GetControlText(edit) == L"Alpha",
        "accepted history applies its text and matching options after close");
    CheckDlgButton(dialog, IDC_FIND_MATCH_CASE, BST_UNCHECKED);
    SetComboSelection(combo, -1);
    SetWindowTextW(edit, L"");
    SendMessageW(dialog, WM_COMMAND, MAKEWPARAM(IDC_FIND_TEXT, CBN_EDITCHANGE), 0);
    SendMessageW(dialog, WM_COMMAND, MAKEWPARAM(IDC_FIND_TEXT, CBN_DROPDOWN), 0);
    SetComboSelection(combo, 0);
    SendMessageW(dialog, WM_COMMAND, MAKEWPARAM(IDC_FIND_TEXT, CBN_EDITCHANGE), 0);
    find.SetTarget(GetDlgItem(owner, ID_INFO_TEXT));
    Require(!IsWindowEnabled(GetDlgItem(dialog, IDOK)),
        "history highlights cannot enable Find Next for an empty accepted query");
    SendMessageW(dialog, WM_COMMAND, MAKEWPARAM(IDC_FIND_TEXT, CBN_SELENDCANCEL), 0);
    SendMessageW(dialog, WM_COMMAND, MAKEWPARAM(IDC_FIND_TEXT, CBN_CLOSEUP), 0);
}

/// Checks native query editing, history, matching, keyboard routing and independent target changes.
static void TestFindControls(HWND owner) {
    HWND text = GetDlgItem(owner, ID_INFO_TEXT);
    SetWindowTextW(text, L"Alpha beta alphabet\r\nBETA čáp\r\nend beta");
    find.SetTarget(text);
    searchWindow = owner;
    find.Show(owner);
    HWND dialog = find.GetWindow();
    Require(dialog != nullptr, "create actual modeless Find dialog");
    if (dialog == nullptr) {
        return;
    }
    wchar_t name[32] = {};
    GetClassNameW(GetDlgItem(dialog, IDC_FIND_TEXT), name, ARRAYSIZE(name));
    Require(_wcsicmp(name, WC_COMBOBOXEXW) == 0 && FindHistoryEdit(dialog) != nullptr,
        "search history is an editable ComboBoxEx");
    Require(!IsWindowVisible(dialog) && GetWindowLongPtrW(dialog, GWL_EXSTYLE) & WS_EX_NOACTIVATE,
        "search test window remains hidden and nonactivating");
    Require(!IsWindowEnabled(GetDlgItem(dialog, IDOK)), "empty query disables Find Next");
    SearchFor(owner, L"beta");
    RequireSelection(text, 6, 10);
    SearchFor(owner, L"beta", false);
    RequireSelection(text, 21, 25);
    CheckDlgButton(dialog, IDC_FIND_MATCH_CASE, BST_CHECKED);
    SearchFor(owner, L"beta", false);
    RequireSelection(text, 35, 39);
    CheckDlgButton(dialog, IDC_FIND_MATCH_CASE, BST_UNCHECKED);
    CheckDlgButton(dialog, IDC_FIND_WHOLE_WORDS, BST_CHECKED);
    SearchFor(owner, L"alpha");
    RequireSelection(text, 0, 5);
    SearchFor(owner, L"alpha", false);
    RequireSelection(text, 0, 5);
    CheckDlgButton(dialog, IDC_FIND_WHOLE_WORDS, BST_UNCHECKED);
    CheckDlgButton(dialog, IDC_FIND_STARTS_WITH, BST_CHECKED);
    SearchFor(owner, L"beta");
    RequireSelection(text, 21, 25);
    CheckDlgButton(dialog, IDC_FIND_STARTS_WITH, BST_UNCHECKED);
    CheckDlgButton(dialog, IDC_FIND_ENDS_WITH, BST_CHECKED);
    SearchFor(owner, L"beta");
    RequireSelection(text, 35, 39);
    CheckDlgButton(dialog, IDC_FIND_ENDS_WITH, BST_UNCHECKED);
    CheckDlgButton(dialog, IDC_FIND_REGEX, BST_CHECKED);
    SendMessageW(dialog, WM_COMMAND, IDC_FIND_REGEX, 0);
    Require(!IsWindowEnabled(GetDlgItem(dialog, IDC_FIND_WHOLE_WORDS)),
        "regex disables literal-only matching options");
    SearchFor(owner, L"č.p");
    RequireSelection(text, 26, 29);
    SearchFor(owner, L"^");
    RequireSelection(text, 0, 0);
    SearchFor(owner, L"^", false);
    RequireSelection(text, 20, 20);
    SearchFor(owner, L"^", false);
    RequireSelection(text, 21, 21);
    int errors = testMessageCalls;
    SearchFor(owner, L"[");
    Require(testMessageCalls == errors + 1, "invalid regex produces one localized error");
    CheckDlgButton(dialog, IDC_FIND_REGEX, BST_UNCHECKED);
    SendMessageW(dialog, WM_COMMAND, IDC_FIND_REGEX, 0);
    for (int index = 0; index < 35; index++) {
        std::wstring query = L"missing-" + std::to_wstring(index);
        SearchFor(owner, query.c_str());
    }
    Require(SendMessageW(FindHistoryControl(dialog), CB_GETCOUNT, 0, 0) == 30,
        "history retains at most 30 real ComboBoxEx items");
    UpdateComboBoxDropDownMetrics(GetDlgItem(dialog, IDC_FIND_TEXT));
    RECT bounds = {};
    GetWindowRect(GetDlgItem(dialog, IDC_FIND_TEXT), &bounds);
    LRESULT dropdownWidth = SendMessageW(FindHistoryControl(dialog), CB_GETDROPPEDWIDTH, 0, 0);
    LONGLONG comboWidth = static_cast<LONGLONG>(bounds.right) - bounds.left;
    Require(dropdownWidth >= comboWidth, "dropdown is at least as wide as its ComboBoxEx");
    SetWindowTextW(FindHistoryEdit(dialog), L"");
    SendMessageW(dialog, WM_COMMAND, MAKEWPARAM(IDC_FIND_TEXT, CBN_EDITCHANGE), 0);
    Require(!IsWindowEnabled(GetDlgItem(dialog, IDOK)), "clearing a typed query disables Find Next");
    TestFindHistoryCommit(owner);
    SearchFor(owner, L"beta");
    find.Close();
    findTestActiveWindow = owner;
    findTestControl = true;
    MSG shortcut = {};
    shortcut.hwnd = text;
    shortcut.message = WM_KEYDOWN;
    shortcut.wParam = L'F';
    Require(TranslateInformationMessage(&shortcut) && find.GetWindow() != nullptr,
        "Ctrl+F opens Find through actual application message routing");
    findTestControl = false;
    shortcut.wParam = VK_F3;
    Require(TranslateInformationMessage(&shortcut), "F3 is routed to Find Next");
    RequireSelection(text, 21, 25);
    findTestShift = true;
    Require(TranslateInformationMessage(&shortcut), "Shift+F3 is routed to Find Previous");
    RequireSelection(text, 6, 10);
    findTestShift = false;
    HWND about = aboutForm.GetWindow();
    HWND license = GetDlgItem(about, ID_INFO_TEXT);
    SetWindowTextW(license, L"beta license text");
    findTestActiveWindow = about;
    UpdateFindTarget();
    SearchFor(about, L"beta");
    RequireSelection(license, 0, 4);
    RequireSelection(text, 6, 10);
}

/// Checks user-font propagation and actual native text baselines across localized Find layouts.
static void TestFindLayout() {
    HWND dialog = find.GetWindow();
    const wchar_t* fonts[] = { L"Segoe UI", L"Consolas", L"Arial" };
    const int weights[] = { FW_NORMAL, FW_BOLD };
    for (const wchar_t* face : fonts) {
        for (int weight : weights) {
            appFontFace = face;
            appFontWeight = weight;
            for (bool disabled : { false, true }) {
                themesDisabled = disabled;
                find.RefreshStyle();
                LOGFONTW actual = {};
                HFONT font = reinterpret_cast<HFONT>(SendMessageW(FindHistoryEdit(dialog), WM_GETFONT, 0, 0));
                Require(GetObjectW(font, sizeof(actual), &actual) != 0
                        && _wcsicmp(actual.lfFaceName, face) == 0
                        && actual.lfWeight == weight,
                    "editable query uses the selected user font and weight");
                for (int language = 0; language < LANG_COUNT; language++) {
                    appLanguage = static_cast<AppLanguage>(language);
                    find.RefreshLanguage();
                    CheckResourceButtonHeights(dialog, IDD_FIND);
                    LONG input = ControlTextBaseline(FindHistoryControl(dialog));
                    Require(std::abs(ControlTextBaseline(GetDlgItem(dialog, IDC_FIND_LABEL)) - input) <= 1,
                        "Find label shares the query text baseline");
                    Require(std::abs(ControlTextBaseline(GetDlgItem(dialog, IDOK)) - input) <= 1,
                        "Find Next shares the query text baseline");
                    Require(std::abs(ControlTextBaseline(GetDlgItem(dialog, IDCANCEL))
                            - ControlTextBaseline(GetDlgItem(dialog, IDC_FIND_WHOLE_WORDS))) <= 1,
                        "Find Close shares the last option row's text baseline");
                }
            }
        }
    }
    appLanguage = LANG_EN_US;
    appFontFace.clear();
    appFontWeight = FW_NORMAL;
    themesDisabled = false;
    find.RefreshStyle();
}

/// Checks immutable font/text capture and multipage rendering without any physical printer or print UI.
static void TestPrintSnapshot(HWND owner) {
    HWND edit = GetDlgItem(owner, ID_INFO_TEXT);
    std::wstring text;
    for (int index = 0; index < 120; index++) {
        text += L"Consolas: čáp, Alpha beta and a line of text.\r\n";
    }
    SetWindowTextW(edit, text.c_str());
    PrintJob* job = CapturePrintJob(owner, edit, L"CalClock test", printSettings.GetMargins());
    Require(job != nullptr && text == job->report, "printing snapshots the complete current edit text");
    if (job == nullptr) {
        return;
    }
    Require(_wcsicmp(job->font.lfFaceName, L"Consolas") == 0,
        "About printing uses the actual Consolas license font");
    SetWindowTextW(edit, L"changed after capture");
    Require(text == job->report, "printing does not access later edit contents");
    HDC dc = CreateCompatibleDC(nullptr);
    RECT content = { 0, 0, 600, 600 };
    PrintLayout layout;
    Require(layout.Initialize(*job, dc, content, 96, 96) && layout.GetPageCount() > 1,
        "reference print layout paginates captured text");
    HDC screen = GetDC(nullptr);
    HBITMAP bitmap = CreateCompatibleBitmap(screen, 600, 600);
    ReleaseDC(nullptr, screen);
    HGDIOBJ previous = SelectObject(dc, bitmap);
    Require(layout.DrawPage(dc, 0), "reference printing renders a page to an isolated memory bitmap");
    SelectObject(dc, previous);
    DeleteObject(bitmap);
    DeleteDC(dc);
    ModernPrintDialog* source = CreateModernPrint(job, printSettings, modernPrintCompleteMessage);
    Require(source != nullptr, "modern print source adopts the same captured job");
    if (source != nullptr) {
        CloseModernPrint(source);
    }
}

/// Checks independent header drafts, theme toggling, and the complete-form dependency on the actual page.
static void TestApplicationHeaderDraft() {
    bool available = AreVisualStylesActive();
    bool groupEnabled = IsWindowEnabled(hApplicationStyleGroup) != FALSE;
    Require(groupEnabled == available,
        "the appearance group is independent of Disable themes");
    Require(!IsWindowEnabled(hApplicationStyleRadios[3]),
        "complete Windows 2000 forms initially require Disable themes");
    if (!available) {
        return;
    }
    for (int mode = 1; mode <= 2; mode++) {
        Require(IsWindowEnabled(hApplicationStyleRadios[mode]),
            "both header choices are available with themed controls");
        CheckRadioButton(hApplicationPage, ID_STYLE_SYSTEM, ID_STYLE_2000_FORMS, APPLICATION_STYLE_IDS[mode]);
        HandleSettingsCommand(APPLICATION_STYLE_IDS[mode], BN_CLICKED);
        for (bool disabled : { true, false }) {
            SetCheck(hDisableThemesCheck, disabled);
            HandleSettingsCommand(ID_VISUAL_STYLES, BN_CLICKED);
            Require(settingsThemesDisabled == disabled
                    && settingsBasicWindowHeaders == (mode == 1)
                    && settingsWindows2000Headers == (mode == 2)
                    && GetCheck(hApplicationStyleRadios[mode]),
                "header drafts survive both directions of the control-theme change");
            bool completeEnabled = IsWindowEnabled(hApplicationStyleRadios[3]) != FALSE;
            Require(completeEnabled == disabled,
                "only complete Windows 2000 forms depend on Disable themes");
            Require(!themesDisabled
                    && GetApplicationDialogFrameMode() == DialogFrameMode::System,
                "header and theme drafts do not alter committed appearance before Apply");
        }
    }
    SetCheck(hDisableThemesCheck, true);
    HandleSettingsCommand(ID_VISUAL_STYLES, BN_CLICKED);
    CheckRadioButton(hApplicationPage, ID_STYLE_SYSTEM, ID_STYLE_2000_FORMS, ID_STYLE_2000_FORMS);
    HandleSettingsCommand(ID_STYLE_2000_FORMS, BN_CLICKED);
    Require(settingsWindows2000Style, "complete Windows 2000 forms can be selected with themes disabled");
    SetCheck(hDisableThemesCheck, false);
    HandleSettingsCommand(ID_VISUAL_STYLES, BN_CLICKED);
    Require(!settingsWindows2000Style
            && GetCheck(hApplicationStyleRadios[0])
            && !IsWindowEnabled(hApplicationStyleRadios[3]),
        "enabling themes leaves the complete Windows 2000 mode and selects System default");
}

/// Captures native client painting into memory without displaying or activating a test window.
static std::vector<BYTE> CaptureControlPixels(HWND control) {
    RECT bounds = {};
    GetClientRect(control, &bounds);
    int width = bounds.right - bounds.left;
    int height = bounds.bottom - bounds.top;
    HDC dc = CreateCompatibleDC(nullptr);
    BITMAPINFO information = {};
    information.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    information.bmiHeader.biWidth = width;
    information.bmiHeader.biHeight = -height;
    information.bmiHeader.biPlanes = 1;
    information.bmiHeader.biBitCount = 32;
    void* bits = nullptr;
    HBITMAP bitmap = CreateDIBSection(dc, &information, DIB_RGB_COLORS, &bits, nullptr, 0);
    Require(dc != nullptr && bitmap != nullptr && bits != nullptr, "allocate native control paint capture");
    std::vector<BYTE> pixels;
    if (dc != nullptr && bitmap != nullptr && bits != nullptr) {
        HGDIOBJ previous = SelectObject(dc, bitmap);
        size_t length = static_cast<size_t>(width) * height * 4;
        std::fill_n(static_cast<BYTE*>(bits), length, static_cast<BYTE>(0xFF));
        SendMessageW(control, WM_PRINTCLIENT, reinterpret_cast<WPARAM>(dc), PRF_CLIENT | PRF_ERASEBKGND);
        GdiFlush();
        pixels.assign(static_cast<BYTE*>(bits), static_cast<BYTE*>(bits) + length);
        SelectObject(dc, previous);
    }
    if (bitmap != nullptr) {
        DeleteObject(bitmap);
    }
    if (dc != nullptr) {
        DeleteDC(dc);
    }
    return pixels;
}

/// Locates actual painted glyph pixels with a shared caption, independently of baseline calculations.
static LONG RenderedControlTextTop(HWND control) {
    std::wstring caption = GetControlText(control);
    SetWindowTextW(control, L"");
    std::vector<BYTE> background = CaptureControlPixels(control);
    SetWindowTextW(control, L"HHH");
    std::vector<BYTE> painted = CaptureControlPixels(control);
    SetWindowTextW(control, caption.c_str());
    RECT bounds = {};
    GetClientRect(control, &bounds);
    int width = bounds.right - bounds.left;
    POINT origin = {};
    ClientToScreen(control, &origin);
    Require(!painted.empty() && painted.size() == background.size(), "capture complete native text painting");
    for (size_t offset = 0; offset + 3 < painted.size() && offset + 3 < background.size(); offset += 4) {
        if (painted[offset] != background[offset]
                || painted[offset + 1] != background[offset + 1]
                || painted[offset + 2] != background[offset + 2]) {
            return origin.y + static_cast<LONG>(offset / 4 / width);
        }
    }
    Require(false, "native control painting contains the shared text glyphs");
    return LONG_MIN;
}

/// Checks real glyph alignment after each Application button obtains its final native font metrics.
static void TestApplicationButtonPainting() {
    const HWND buttons[] = {
        hAppFontButton,
        hAppFontDefaultButton,
        hTimeSignalTestButton
    };
    const HWND labels[] = {
        hAppFontLabel,
        hAppFontLabel,
        GetDlgItem(hApplicationPage, IDC_TIME_SIGNAL_SOUND_LABEL)
    };
    for (HWND button : buttons) {
        RECT bounds = {};
        GetWindowRect(button, &bounds);
        SetWindowPos(button, nullptr, 0, 0, bounds.right - bounds.left, bounds.bottom - bounds.top - 1,
            SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
    }
    SendMessageW(hSettings, WM_ALIGN_SETTINGS_ACTION_BUTTONS, 0, 0);
    for (HWND button : buttons) {
        WPARAM font = static_cast<WPARAM>(SendMessageW(button, WM_GETFONT, 0, 0));
        SendMessageW(button, WM_SETFONT, font, FALSE);
    }
    MSG message = {};
    while (PeekMessageW(&message, hSettings, WM_ALIGN_SETTINGS_ACTION_BUTTONS,
            WM_ALIGN_SETTINGS_ACTION_BUTTONS, PM_REMOVE)) {
        DispatchMessageW(&message);
    }
    for (int index = 0; index < ARRAYSIZE(buttons); index++) {
        WINDOWINFO information = { sizeof(information) };
        GetWindowInfo(buttons[index], &information);
        TEXTMETRICW metrics = {};
        GetSettingsTextMetrics(buttons[index], &metrics);
        LONG baseline = ControlTextBaseline(buttons[index]);
        LONG referenceBaseline = ControlTextBaseline(labels[index]);
        LONG textTop = GetSettingsButtonTextTop(buttons[index], information, metrics);
        LONG actual = RenderedControlTextTop(buttons[index]);
        LONG expected = RenderedControlTextTop(labels[index]);
        if (actual != expected) {
            std::cerr << "Application button " << GetDlgCtrlID(buttons[index])
                << ": painted text top " << actual << ", label " << expected
                << ", measured baseline " << baseline << "/" << referenceBaseline
                << ", window top " << information.rcWindow.top
                << ", height " << information.rcClient.bottom - information.rcClient.top
                << ", font " << metrics.tmHeight << "/" << metrics.tmAscent
                << ", calculated text top " << textTop << "\n";
        }
        Require(actual == expected, "all three Application buttons paint on the static label baseline");
    }
}

/// Checks Application-page text baselines, icon controls, draft isolation and dependency gating.
static void TestTrayIconDraft() {
    std::unique_ptr<Widget> widget = std::make_unique<Widget>();
    widget->config = AlarmConfiguration(1);
    widgets.push_back(std::move(widget));
    settingsDraft.push_back(AlarmConfiguration(1));
    settingsAppliedWidgets = settingsDraft;
    settingsAppearanceOriginals = settingsDraft;
    selectedDraftIndex = 0;
    settingsTab = 5;
    useNtpTime = false;
    themesDisabled = false;
    alternativeTrayIcon = false;
    classicTrayIcon = false;
    settingsAlternativeTrayIcon = false;
    settingsClassicTrayIcon = false;
    hSettings = CreateSettingsDialog(IDD_SETTINGS, nullptr, SettingsDialogProc, 0);
    Require(hSettings != nullptr && CreateSettingsControls(5), "create actual Application settings page");
    LoadAlarm(AlarmConfiguration(1));
    TestApplicationHeaderDraft();
    SendMessageW(hSettings, WM_ALIGN_SETTINGS_ACTION_BUTTONS, 0, 0);
    TestApplicationButtonPainting();
    HWND soundLabel = GetDlgItem(hApplicationPage, IDC_TIME_SIGNAL_SOUND_LABEL);
    LONG soundBaseline = ControlTextBaseline(soundLabel);
    Require(ControlTextBaseline(hTimeSignalTestButton) == soundBaseline,
        "the sound Test button shares the static label baseline exactly");
    Require(ControlTextBaseline(hTimeSignalSoundCombo) == soundBaseline,
        "the sound combo shares the static label baseline exactly");
    widgets[0]->window = TestCreateWindowExW(WS_EX_NOACTIVATE, L"STATIC", L"", WS_POPUP,
        0, 0, 1, 1, nullptr, nullptr, hInstance, nullptr);
    if (hAlternativeTrayIconCheck != nullptr && hClassicTrayIconCheck != nullptr) {
        Require(!IsWindowEnabled(hClassicTrayIconCheck), "classic icon initially requires alternative icon");
        SetCheck(hAlternativeTrayIconCheck, true);
        HandleSettingsCommand(ID_ALTERNATIVE_TRAY_ICON, BN_CLICKED);
        Require(IsWindowEnabled(hClassicTrayIconCheck)
                && settingsAlternativeTrayIcon
                && !alternativeTrayIcon
                && TrayIconIndex() == 0,
            "changing the icon draft has no tray effect");
        SetCheck(hClassicTrayIconCheck, true);
        HandleSettingsCommand(ID_CLASSIC_TRAY_ICON, BN_CLICKED);
        Require(settingsClassicTrayIcon && !classicTrayIcon, "classic draft waits for Apply or OK");
        SetCheck(hAlternativeTrayIconCheck, false);
        HandleSettingsCommand(ID_ALTERNATIVE_TRAY_ICON, BN_CLICKED);
        Require(!IsWindowEnabled(hClassicTrayIconCheck)
                && !GetCheck(hClassicTrayIconCheck)
                && !settingsClassicTrayIcon,
            "turning off the parent disables and clears the classic draft");
        alternativeTrayIcon = true;
        classicTrayIcon = false;
        Require(TrayIconIndex() == 1, "committed alternative selects index one");
        classicTrayIcon = true;
        Require(TrayIconIndex() == 4, "committed classic selects index four");
        alternativeTrayIcon = false;
        Require(TrayIconIndex() == 0, "default tray uses index zero");
        classicTrayIcon = false;
        SetCheck(hAlternativeTrayIconCheck, true);
        HandleSettingsCommand(ID_ALTERNATIVE_TRAY_ICON, BN_CLICKED);
        SetCheck(hClassicTrayIconCheck, true);
        HandleSettingsCommand(ID_CLASSIC_TRAY_ICON, BN_CLICKED);
        HandleSettingsCommand(ID_APPLY, BN_CLICKED);
        Require(alternativeTrayIcon && classicTrayIcon && TrayIconIndex() == 4,
            "actual Apply commits both icon options");
        SetCheck(hAlternativeTrayIconCheck, false);
        HandleSettingsCommand(ID_ALTERNATIVE_TRAY_ICON, BN_CLICKED);
        warnOnUnsavedChanges = false;
        HandleSettingsCommand(ID_CANCEL, BN_CLICKED);
        Require(alternativeTrayIcon && classicTrayIcon && TrayIconIndex() == 4,
            "actual Cancel discards pending icon changes");
    }
    if (hSettings != nullptr) {
        DestroySettingsChildControls();
        DestroyWindow(hSettings);
        hSettings = nullptr;
    }
    RemoveTrayIcon();
    DestroyWidgetWindows();
    widgets.clear();
    settingsDraft.clear();
}

/// Runs real native controls on an unshown private desktop under an isolated registry root.
int wmain(int argc, wchar_t** argv) {
    if (argc != 2) {
        return 2;
    }
    std::wstring directory = argv[1];
    testXmlPath = directory + L"\\Options.xml";
    HDESK previous = GetThreadDesktop(GetCurrentThreadId());
    std::wstring desktopName = L"CalClockFindTests-" + std::to_wstring(GetCurrentProcessId());
    HDESK desktop = CreateDesktopW(desktopName.c_str(), nullptr, nullptr, 0, GENERIC_ALL, nullptr);
    if (desktop == nullptr || !SetThreadDesktop(desktop)) {
        std::fprintf(stderr, "Cannot create isolated desktop: %lu\n", GetLastError());
        return 2;
    }
    std::wstring registryName = L"Software\\CalClockFindTests-" + std::to_wstring(GetCurrentProcessId());
    HKEY isolated = nullptr;
    DWORD disposition = 0;
    LSTATUS createResult = RegCreateKeyExW(HKEY_CURRENT_USER, registryName.c_str(), 0, nullptr,
        REG_OPTION_VOLATILE, KEY_ALL_ACCESS, nullptr, &isolated, &disposition);
    if (createResult != ERROR_SUCCESS
            || disposition != REG_CREATED_NEW_KEY
            || RegOverridePredefKey(HKEY_CURRENT_USER, isolated) != ERROR_SUCCESS) {
        return 2;
    }
    INITCOMMONCONTROLSEX common = {
        sizeof(common),
        ICC_WIN95_CLASSES | ICC_STANDARD_CLASSES | ICC_USEREX_CLASSES
    };
    InitCommonControlsEx(&common);
    hInstance = GetModuleHandleW(nullptr);
    appLanguage = LANG_EN_US;
    TestResourceLibrary(directory);
    TestPackedOptions();
    TestAppearanceOptions();
    TestInformationForms();
    HWND owner = helpForm.GetWindow();
    Require(owner != nullptr, "create native information owner on the hidden desktop");
    if (owner != nullptr) {
        TestFindControls(owner);
        TestFindLayout();
        TestPrintSnapshot(aboutForm.GetWindow());
        find.Close();
        helpForm.Close();
        aboutForm.Close();
    }
    findTestActiveWindow = nullptr;
    TestTrayIconDraft();
    DeleteFileW(testXmlPath.c_str());
    RegOverridePredefKey(HKEY_CURRENT_USER, nullptr);
    RegCloseKey(isolated);
    RegDeleteTreeW(HKEY_CURRENT_USER, registryName.c_str());
    SetThreadDesktop(previous);
    CloseDesktop(desktop);
    if (testFailures != 0) {
        return 1;
    }
    std::puts("PASS: native ComboBoxEx Find, matching/history/fonts/layout, DLL cache, "
        "Options and print snapshots");
    return 0;
}
