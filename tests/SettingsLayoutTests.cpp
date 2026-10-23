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
 * Last modified for version 1.6.1.1
 */

#define WriteRegistrySettings CaptureTestRegistrySettings
#include "../CalClock/CalClock.cpp"
#undef WriteRegistrySettings
#include <cstdio>
#include <initializer_list>

#pragma comment(lib, "Msimg32.lib")

struct TextInk {
    int top;
    int bottom;
    int pixels;
};

struct FieldImage {
    int width;
    int height;
    std::vector<DWORD> pixels;
};

struct WidgetSelectionControl {
    HWND window;
    RECT bounds;
    int moves;
};

struct ProtectedSettingsControl {
    HWND window;
    FieldImage pixels;
};

struct AppearanceTransitionFrame {
    ULONGLONG hash;
    UINT message;
    int control;
    bool loading;
};

static const SYSTEMTIME panelPaintingTimes[] = {
    { 2026, 10, 6, 17, 0, 0, 0, 0 },
    { 2026, 10, 6, 17, 3, 15, 30, 0 },
    { 2026, 10, 6, 17, 6, 30, 15, 0 },
    { 2026, 10, 6, 17, 9, 45, 45, 0 },
    { 2026, 10, 6, 17, 17, 42, 5, 0 },
    { 2026, 10, 6, 17, 23, 59, 59, 0 }
};

static HHOOK panelClockTimeHook = nullptr;
static HHOOK settingsCloseDialogHook = nullptr;
static HHOOK widgetSelectionPaintHook = nullptr;
static HHOOK appearanceTransitionHook = nullptr;
static int testSettingsDialogResponse = IDCANCEL;
static int testSettingsSaveQuestions = 0;
static int testSettingsValidationMessages = 0;
static int testSettingsWrites = 0;
static int checks = 0;
static int failures = 0;
static int nativeChanges = 0;
static int monitorOwnerDrawMessages = 0;
static int widgetSelectionHiddenUpdates = 0;
static int widgetSelectionRepeatedMoves = 0;
static int widgetSelectionFormRedraws = 0;
static int widgetSelectionSurroundingPaints = 0;
static int widgetSelectionBufferedTextPaints = 0;
static int widgetSelectionExposedTextPaints = 0;
static int widgetSelectionCoveredControlChanges = 0;
static int widgetSelectionVisibilityEvents = 0;
static int widgetSelectionFirstHide = 0;
static int widgetSelectionLastReveal = 0;
static int widgetSelectionRevealOrderFailures = 0;
static int widgetSelectionReplacementOrderFailures = 0;
static bool observingWidgetSelection = false;
static bool observingAppearanceTransition = false;
static bool capturingAppearanceTransition = false;
static ULONGLONG appearanceTransitionBeforeHash = 0;
static SettingsSnapshot testSavedSettings;
static FieldImage appearanceTransitionFirstChange;
static std::vector<HWND> panelClockTimeWindows;
static std::vector<WidgetSelectionControl> widgetSelectionControls;
static std::vector<HWND> widgetSelectionRevealedControls;
static std::vector<AppearanceTransitionFrame> appearanceTransitionFrames;

/// Renders a native field or an entire visible settings window into a test image.
static FieldImage ReadFieldImage(HWND control, bool children = false, bool native = false);

/// Finds the label explicitly associated with a settings field in its parent page.
static HWND GetSettingsFieldLabel(HWND field) {
    if (field == nullptr) {
        return nullptr;
    }
    for (HWND label = GetWindow(GetParent(field), GW_CHILD); label != nullptr; label = GetWindow(label, GW_HWNDNEXT)) {
        if (GetPropW(label, SETTINGS_FIELD_LABEL_PROPERTY) == field) {
            return label;
        }
    }
    return nullptr;
}

/// Records native-control assertions without stopping after the first failure.
static void Check(bool condition, const char* description) {
    checks++;
    if (!condition) {
        failures++;
        std::printf("FAIL: %s\n", description);
    }
}

/// Captures application persistence in memory so settings-close actions cannot modify the user's registry or XML.
bool CaptureTestRegistrySettings(const SettingsSnapshot& snapshot) {
    testSavedSettings = snapshot;
    testSettingsWrites++;
    return true;
}

/// Answers real native message boxes on this test thread and verifies their owner, buttons, and localized warning.
static LRESULT CALLBACK SettingsCloseDialogHook(int code, WPARAM wParam, LPARAM lParam) {
    if (code == HCBT_ACTIVATE) {
        HWND dialog = reinterpret_cast<HWND>(wParam);
        wchar_t className[32] = {};
        GetClassNameW(dialog, className, ARRAYSIZE(className));
        if (wcscmp(className, L"#32770") == 0 && GetWindow(dialog, GW_OWNER) == hSettings) {
            bool saveQuestion = GetDlgItem(dialog, IDYES) != nullptr;
            if (saveQuestion) {
                testSettingsSaveQuestions++;
                Check(GetDlgItem(dialog, IDNO) != nullptr && GetDlgItem(dialog, IDCANCEL) != nullptr,
                    "unsaved settings use native Yes, No, and Cancel buttons");
                Check(GetControlText(dialog) == T(TXT_SETTINGS), "save question uses the settings title");
                bool localizedWarning = false;
                for (HWND child = GetWindow(dialog, GW_CHILD); child != nullptr; child = GetWindow(child, GW_HWNDNEXT)) {
                    localizedWarning = localizedWarning || GetControlText(child) == UNSAVED_SETTINGS_PROMPTS[appLanguage];
                }
                Check(localizedWarning, "save question displays the current application-language warning");
            } else {
                testSettingsValidationMessages++;
            }
            SetWindowPos(dialog, nullptr, -10000, -10000, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
            if (saveQuestion && testSettingsDialogResponse != 0) {
                PostMessageW(dialog, WM_COMMAND, MAKEWPARAM(testSettingsDialogResponse, BN_CLICKED), 0);
            } else {
                PostMessageW(dialog, WM_CLOSE, 0, 0);
            }
        }
    }
    return CallNextHookEx(settingsCloseDialogHook, code, wParam, lParam);
}

/// Hosts native controls without loading, saving, or changing the user's application settings.
static LRESULT CALLBACK TestWindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_DRAWITEM && DrawSettingsListItem(reinterpret_cast<DRAWITEMSTRUCT*>(lParam))) {
        return TRUE;
    }
    if (message == WM_COMMAND && HIWORD(wParam) == EN_CHANGE) {
        nativeChanges++;
    }
    return DefWindowProcW(window, message, wParam, lParam);
}

/// Reads the visible field rectangle, including the clipped viewport around a native single-line edit.
static RECT FieldBounds(HWND control) {
    RECT bounds = {};
    GetWindowRect(SettingsEdit::GetFrame(control), &bounds);
    return bounds;
}

/// Compares native text pixels with the same control's empty state to locate actual rendered glyphs.
static TextInk ReadInk(HWND control, bool combo) {
    wchar_t className[32] = {};
    GetClassNameW(control, className, ARRAYSIZE(className));
    if (wcscmp(className, L"EDIT") == 0) {
        SendMessageW(control, EM_SETCUEBANNER, FALSE, reinterpret_cast<LPARAM>(L""));
    }
    std::wstring original = GetControlText(control);
    LRESULT originalSelection = combo ? SendMessageW(control, CB_GETCURSEL, 0, 0) : CB_ERR;
    HWND rendered = combo ? GetSettingsComboBox(control) : control;
    RECT client = {};
    GetClientRect(rendered, &client);
    BITMAPINFO information = {};
    information.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    information.bmiHeader.biWidth = client.right;
    information.bmiHeader.biHeight = -client.bottom;
    information.bmiHeader.biPlanes = 1;
    information.bmiHeader.biBitCount = 32;
    HDC dc = CreateCompatibleDC(nullptr);
    void* bits = nullptr;
    HBITMAP bitmap = CreateDIBSection(dc, &information, DIB_RGB_COLORS, &bits, nullptr, 0);
    HGDIOBJ previous = SelectObject(dc, bitmap);
    std::vector<DWORD> empty;
    POINT origin = {};
    ClientToScreen(rendered, &origin);
    TextInk ink = { INT_MAX, -1, 0 };
    for (int pass = 0; pass < 2; pass++) {
        const wchar_t* text = pass == 0 ? L"" : L"Agyp";
        LRESULT temporaryItem = CB_ERR;
        if (combo) {
            temporaryItem = SendMessageW(control, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(text));
            SendMessageW(control, CB_SETCURSEL, temporaryItem, 0);
        } else {
            SetWindowTextW(control, text);
        }
        FillRect(dc, &client, GetSysColorBrush(COLOR_BTNFACE));
        SendMessageW(rendered, WM_PRINTCLIENT, reinterpret_cast<WPARAM>(dc), PRF_CLIENT | PRF_ERASEBKGND);
        GdiFlush();
        DWORD* pixels = static_cast<DWORD*>(bits);
        if (pass == 0) {
            empty.assign(pixels, pixels + static_cast<size_t>(client.right) * client.bottom);
        } else {
            for (int y = 0; y < client.bottom; y++) {
                for (int x = 0; x < client.right; x++) {
                    size_t index = static_cast<size_t>(y) * client.right + x;
                    if ((empty[index] & 0xFFFFFF) != (pixels[index] & 0xFFFFFF)) {
                        ink.top = std::min(ink.top, static_cast<int>(origin.y) + y);
                        ink.bottom = std::max(ink.bottom, static_cast<int>(origin.y) + y);
                        ink.pixels++;
                    }
                }
            }
        }
        if (combo && temporaryItem >= 0) {
            SendMessageW(control, CB_DELETESTRING, temporaryItem, 0);
        }
    }
    SelectObject(dc, previous);
    DeleteObject(bitmap);
    DeleteDC(dc);
    if (combo) {
        SendMessageW(control, CB_SETCURSEL, originalSelection, 0);
    } else {
        SetWindowTextW(control, original.c_str());
    }
    return ink;
}

/// Compares the rendered descenders of identical text in the same font to verify a shared text baseline.
static void CheckBaseline(const TextInk& reference, HWND control, const char* description) {
    TextInk ink = ReadInk(control, false);
    Check(reference.pixels > 0 && ink.pixels > 0 && ink.bottom == reference.bottom, description);
    if (ink.bottom != reference.bottom) {
        std::printf("  reference=%d..%d actual=%d..%d\n", reference.top, reference.bottom, ink.top, ink.bottom);
    }
}

/// Checks every translated warning-checkbox caption against the native button width in its current font and theme.
static void CheckUnsavedSettingsCaptionWidths() {
    std::wstring original = GetControlText(hWarnUnsavedChangesCheck);
    RECT bounds = FieldBounds(hWarnUnsavedChangesCheck);
    for (int language = 0; language < LANG_COUNT; language++) {
        SetWindowTextW(hWarnUnsavedChangesCheck, WARN_UNSAVED_CHANGES_LABELS[language]);
        SIZE ideal = {};
        LRESULT measured = SendMessageW(hWarnUnsavedChangesCheck, BCM_GETIDEALSIZE, 0, reinterpret_cast<LPARAM>(&ideal));
        bool fits = measured != 0 && ideal.cx <= bounds.right - bounds.left;
        Check(fits, "translated unsaved-warning checkbox fits its native available width");
        if (!fits) {
            std::printf("  language=%d idealWidth=%ld availableWidth=%ld measured=%lld\n",
                language, ideal.cx, bounds.right - bounds.left, static_cast<long long>(measured));
        }
    }
    SetWindowTextW(hWarnUnsavedChangesCheck, original.c_str());
}

/// Measures Application row baselines, their peers, the linked slider placement, and repeat-layout stability.
static void CheckApplicationRowSpacing() {
    CheckUnsavedSettingsCaptionWidths();
    const HWND labels[] = {
        hAppFontLabel,
        GetSettingsFieldLabel(hAppAntialiasCombo),
        GetSettingsFieldLabel(hLanguageCombo),
        GetSettingsFieldLabel(hTimeSignalSoundCombo),
        hTimeSignalVolumeLabel,
        hDisableThemesCheck,
        hUseXmlSettingsCheck,
        hSnapToWorkAreaCheck,
        hStartWithWindowsCheck,
        hWarnUnsavedChangesCheck
    };
    TextInk previous = ReadInk(labels[0], false);
    for (size_t index = 1; index < ARRAYSIZE(labels); index++) {
        TextInk current = ReadInk(labels[index], false);
        if (index != 5) {
            int expectedDistance = index == 4 ? 36 : 34;
            bool correct = previous.pixels > 0
                && current.pixels > 0
                && current.bottom - previous.bottom == expectedDistance;
            Check(correct, "same-kind Application rows retain their requested rendered baseline distances");
            if (!correct) {
                std::printf("  Application rows %zu..%zu: distance=%d\n", index, index + 1,
                    current.bottom - previous.bottom);
            }
        }
        previous = current;
    }
    CheckBaseline(ReadInk(hAppFontLabel, false), hAppFontButton, "application font button shares its label baseline");
    CheckBaseline(ReadInk(hAppFontLabel, false), hAppFontDefaultButton, "default font button shares its label baseline");
    const HWND combos[] = {
        hAppAntialiasCombo,
        hLanguageCombo,
        hTimeSignalSoundCombo
    };
    for (HWND combo : combos) {
        LRESULT count = SendMessageW(combo, CB_GETCOUNT, 0, 0);
        LRESULT selection = SendMessageW(combo, CB_GETCURSEL, 0, 0);
        TextInk ink = ReadInk(combo, true);
        CheckBaseline(ink, GetSettingsFieldLabel(combo), "Application combo shares its label baseline");
        Check(count == SendMessageW(combo, CB_GETCOUNT, 0, 0) && selection == SendMessageW(combo, CB_GETCURSEL, 0, 0),
            "baseline measurement preserves combo items and selection");
    }
    CheckBaseline(ReadInk(GetSettingsFieldLabel(hTimeSignalSoundCombo), false), hTimeSignalTestButton,
        "time signal test button shares its label baseline");
    CheckBaseline(ReadInk(hTimeSignalVolumeLabel, false), hTimeSignalVolumeValue,
        "time signal volume value shares its label baseline");
    std::vector<PositionedControl> placements;
    for (HWND control : applicationControls) {
        placements.push_back(PositionedControl{ control, FieldBounds(control) });
    }
    AlignSettingsControls();
    for (const PositionedControl& placement : placements) {
        RECT bounds = FieldBounds(placement.window);
        Check(EqualRect(&bounds, &placement.rect), "repeated Application alignment preserves every control rectangle");
    }
    OffsetSettingsControl(hAppAntialiasCombo, 7);
    OffsetSettingsControl(hAppFontButton, 7);
    OffsetSettingsControl(hTimeSignalVolumeValue, 7);
    OffsetSettingsControl(hTimeSignalVolumeTrackBar, 7);
    AlignSettingsControls();
    for (const PositionedControl& placement : placements) {
        RECT bounds = FieldBounds(placement.window);
        Check(EqualRect(&bounds, &placement.rect),
            "right fields realign to fixed left anchors without moving other Application controls");
    }
}

/// Renders visible native windows with their real sibling clipping and parent-client clipping into a supplied test DC.
static void PrintWindowTree(HWND window, HDC dc, const RECT& clip, const POINT& origin) {
    if (!IsWindowVisible(window)) {
        return;
    }
    WINDOWINFO info = { sizeof(info) };
    GetWindowInfo(window, &info);
    RECT bounds = info.rcWindow;
    OffsetRect(&bounds, -origin.x, -origin.y);
    int saved = SaveDC(dc);
    IntersectClipRect(dc, clip.left, clip.top, clip.right, clip.bottom);
    IntersectClipRect(dc, bounds.left, bounds.top, bounds.right, bounds.bottom);
    if ((info.dwStyle & WS_CHILD) != 0) {
        for (HWND sibling = GetWindow(window, GW_HWNDPREV);
                sibling != nullptr;
                sibling = GetWindow(sibling, GW_HWNDPREV)) {
            if (IsWindowVisible(sibling)) {
                RECT covered = {};
                GetWindowRect(sibling, &covered);
                OffsetRect(&covered, -origin.x, -origin.y);
                ExcludeClipRect(dc, covered.left, covered.top, covered.right, covered.bottom);
            }
        }
    }
    FieldImage source = ReadFieldImage(window, false, true);
    BITMAPINFO information = {};
    information.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    information.bmiHeader.biWidth = source.width;
    information.bmiHeader.biHeight = -source.height;
    information.bmiHeader.biPlanes = 1;
    information.bmiHeader.biBitCount = 32;
    HDC sourceDc = CreateCompatibleDC(dc);
    void* bits = nullptr;
    HBITMAP bitmap = CreateDIBSection(sourceDc, &information, DIB_RGB_COLORS, &bits, nullptr, 0);
    HGDIOBJ previous = SelectObject(sourceDc, bitmap);
    std::copy(source.pixels.begin(), source.pixels.end(), static_cast<DWORD*>(bits));
    TransparentBlt(dc, bounds.left, bounds.top, source.width, source.height, sourceDc, 0, 0, source.width, source.height,
        RGB(255, 0, 255));
    SelectObject(sourceDc, previous);
    DeleteObject(bitmap);
    DeleteDC(sourceDc);
    RestoreDC(dc, saved);
    RECT client = info.rcClient;
    OffsetRect(&client, -origin.x, -origin.y);
    RECT childClip = {};
    if (!IntersectRect(&childClip, &clip, &client)) {
        return;
    }
    for (HWND child = GetWindow(window, GW_CHILD); child != nullptr; child = GetWindow(child, GW_HWNDNEXT)) {
        PrintWindowTree(child, dc, childClip, origin);
    }
}

/// Renders the complete field, including the edit viewport's padding and native child, onto a sentinel background.
static FieldImage ReadFieldImage(HWND control, bool children, bool native) {
    HWND frame = native ? control : SettingsEdit::GetFrame(control);
    WINDOWINFO info = { sizeof(info) };
    GetWindowInfo(frame, &info);
    FieldImage result = { info.rcWindow.right - info.rcWindow.left, info.rcWindow.bottom - info.rcWindow.top, {} };
    BITMAPINFO information = {};
    information.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    information.bmiHeader.biWidth = result.width;
    information.bmiHeader.biHeight = -result.height;
    information.bmiHeader.biPlanes = 1;
    information.bmiHeader.biBitCount = 32;
    HDC dc = CreateCompatibleDC(nullptr);
    void* bits = nullptr;
    HBITMAP bitmap = CreateDIBSection(dc, &information, DIB_RGB_COLORS, &bits, nullptr, 0);
    HGDIOBJ previous = SelectObject(dc, bitmap);
    RECT bounds = { 0, 0, result.width, result.height };
    HBRUSH sentinel = CreateSolidBrush(RGB(255, 0, 255));
    FillRect(dc, &bounds, sentinel);
    DeleteObject(sentinel);
    if (children) {
        const POINT origin = { info.rcWindow.left, info.rcWindow.top };
        PrintWindowTree(frame, dc, bounds, origin);
    } else {
        LPARAM flags = PRF_CLIENT | PRF_NONCLIENT | PRF_ERASEBKGND;
        if (GetSettingsComboBox(frame) != frame) {
            flags |= PRF_CHILDREN;
        }
        SendMessageW(frame, WM_PRINT, reinterpret_cast<WPARAM>(dc), flags);
    }
    if (frame != control) {
        int saved = SaveDC(dc);
        RECT clip = info.rcClient;
        OffsetRect(&clip, -info.rcWindow.left, -info.rcWindow.top);
        IntersectClipRect(dc, clip.left, clip.top, clip.right, clip.bottom);
        POINT origin = {};
        ClientToScreen(control, &origin);
        SetViewportOrgEx(dc, origin.x - info.rcWindow.left, origin.y - info.rcWindow.top, nullptr);
        SendMessageW(control, WM_PRINTCLIENT, reinterpret_cast<WPARAM>(dc), PRF_CLIENT | PRF_ERASEBKGND);
        RestoreDC(dc, saved);
    }
    GdiFlush();
    DWORD* pixels = static_cast<DWORD*>(bits);
    result.pixels.assign(pixels, pixels + static_cast<size_t>(result.width) * result.height);
    SelectObject(dc, previous);
    DeleteObject(bitmap);
    DeleteDC(dc);
    return result;
}

/// Reads the real native window surface after nonclient painting, including borders omitted by default WM_PRINT.
static FieldImage ReadWindowSurface(HWND window, bool repaint = true) {
    RECT bounds = {};
    GetWindowRect(window, &bounds);
    FieldImage image = { bounds.right - bounds.left, bounds.bottom - bounds.top, {} };
    BITMAPINFO information = {};
    information.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    information.bmiHeader.biWidth = image.width;
    information.bmiHeader.biHeight = -image.height;
    information.bmiHeader.biPlanes = 1;
    information.bmiHeader.biBitCount = 32;
    HDC dc = CreateCompatibleDC(nullptr);
    void* bits = nullptr;
    HBITMAP bitmap = CreateDIBSection(dc, &information, DIB_RGB_COLORS, &bits, nullptr, 0);
    HGDIOBJ previous = SelectObject(dc, bitmap);
    if (repaint) {
        RedrawWindow(window, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_UPDATENOW | RDW_ALLCHILDREN);
    }
    HDC source = GetWindowDC(window);
    Check(source != nullptr, "native window surface is available for border comparison");
    Check(source != nullptr && BitBlt(dc, 0, 0, image.width, image.height, source, 0, 0, SRCCOPY),
        "native border surface is copied successfully");
    if (source != nullptr) {
        ReleaseDC(window, source);
    }
    GdiFlush();
    image.pixels.assign(static_cast<DWORD*>(bits), static_cast<DWORD*>(bits) +
        static_cast<size_t>(image.width) * image.height);
    SelectObject(dc, previous);
    DeleteObject(bitmap);
    DeleteDC(dc);
    return image;
}

/// Compares every nonclient border pixel while excluding native text and caret rendering inside the client area.
static bool SameFieldBorder(const FieldImage& actual, const FieldImage& reference, HWND window) {
    if (actual.width != reference.width || actual.height != reference.height) {
        return false;
    }
    WINDOWINFO information = { sizeof(information) };
    GetWindowInfo(window, &information);
    RECT client = information.rcClient;
    OffsetRect(&client, -information.rcWindow.left, -information.rcWindow.top);
    for (int y = 0; y < actual.height; y++) {
        for (int x = 0; x < actual.width; x++) {
            if (x < client.left || x >= client.right || y < client.top || y >= client.bottom) {
                size_t pixel = static_cast<size_t>(y) * actual.width + x;
                if ((actual.pixels[pixel] & 0xFFFFFF) != (reference.pixels[pixel] & 0xFFFFFF)) {
                    return false;
                }
            }
        }
    }
    return true;
}

/// Saves rendered controls for direct visual inspection without capturing any other application or desktop content.
static void SaveFieldComparison(const wchar_t* name, const std::vector<FieldImage>& images, int columns = 2) {
    int width = columns * images[0].width + 10 * (columns + 1);
    int rowHeight = images[0].height + 12;
    int height = (static_cast<int>(images.size()) + columns - 1) / columns * rowHeight + 12;
    std::vector<DWORD> pixels(static_cast<size_t>(width) * height, 0x00D0D0D0);
    for (size_t index = 0; index < images.size(); index++) {
        const FieldImage& source = images[index];
        int x = 10 + static_cast<int>(index % columns) * (source.width + 10);
        int y = 6 + static_cast<int>(index / columns) * rowHeight;
        for (int row = 0; row < source.height; row++) {
            std::copy_n(source.pixels.data() + static_cast<size_t>(row) * source.width, source.width,
                pixels.data() + (static_cast<size_t>(y) + row) * width + x);
        }
    }
    wchar_t executable[MAX_PATH] = {};
    GetModuleFileNameW(nullptr, executable, ARRAYSIZE(executable));
    PathRemoveFileSpecW(executable);
    std::wstring path = std::wstring(executable) + L"/" + name;
    HANDLE file = CreateFileW(path.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE) {
        return;
    }
    BITMAPFILEHEADER fileHeader = {};
    fileHeader.bfType = 0x4D42;
    fileHeader.bfOffBits = sizeof(fileHeader) + sizeof(BITMAPINFOHEADER);
    fileHeader.bfSize = fileHeader.bfOffBits + static_cast<DWORD>(pixels.size() * sizeof(DWORD));
    BITMAPINFOHEADER info = {};
    info.biSize = sizeof(info);
    info.biWidth = width;
    info.biHeight = -height;
    info.biPlanes = 1;
    info.biBitCount = 32;
    DWORD written = 0;
    WriteFile(file, &fileHeader, sizeof(fileHeader), &written, nullptr);
    WriteFile(file, &info, sizeof(info), &written, nullptr);
    WriteFile(file, pixels.data(), static_cast<DWORD>(pixels.size() * sizeof(DWORD)), &written, nullptr);
    CloseHandle(file);
}

/// Creates an ordinary native combo with an empty text field as an independent disabled-background reference.
static HWND CreateDisabledComboReference(HWND control, HFONT font, bool classic) {
    RECT bounds = FieldBounds(control);
    HWND reference = CreateWindowExW(0, WC_COMBOBOXW, L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST,
        700, 350, bounds.right - bounds.left, 220, hSettings, nullptr, hInstance, nullptr);
    SendMessageW(reference, WM_SETFONT, reinterpret_cast<WPARAM>(font), FALSE);
    SetWindowTheme(reference, classic ? L"" : nullptr, classic ? L"" : nullptr);
    RECT natural = FieldBounds(reference);
    LRESULT selectedHeight = SendMessageW(reference, CB_GETITEMHEIGHT, static_cast<WPARAM>(-1), 0);
    LONG chrome = natural.bottom - natural.top - static_cast<LONG>(selectedHeight);
    SendMessageW(reference, CB_SETITEMHEIGHT, static_cast<WPARAM>(-1),
        static_cast<LPARAM>(bounds.bottom) - bounds.top - chrome);
    EnableWindow(reference, FALSE);
    return reference;
}

/// Creates an unmodified system ComboBoxEx with the same font, theme, and closed-field dimensions as the tested control.
static HWND CreateNativeComboReference(HWND control, HFONT font, bool classic) {
    RECT bounds = FieldBounds(control);
    HWND reference = CreateWindowExW(0, WC_COMBOBOXEXW, L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST,
        700, 350, bounds.right - bounds.left, 220, hSettings, nullptr, hInstance, nullptr);
    SendMessageW(reference, WM_SETFONT, reinterpret_cast<WPARAM>(font), FALSE);
    SetWindowTheme(reference, classic ? L"" : nullptr, classic ? L"" : nullptr);
    HWND combo = GetSettingsComboBox(reference);
    SetWindowTheme(combo, classic ? L"" : nullptr, classic ? L"" : nullptr);
    RECT natural = FieldBounds(combo);
    LRESULT selectedHeight = SendMessageW(combo, CB_GETITEMHEIGHT, static_cast<WPARAM>(-1), 0);
    LONG chrome = natural.bottom - natural.top - static_cast<LONG>(selectedHeight);
    SendMessageW(combo, CB_SETITEMHEIGHT, static_cast<WPARAM>(-1),
        static_cast<LPARAM>(bounds.bottom) - bounds.top - chrome);
    SendMessageW(combo, CB_SETITEMHEIGHT, 0, SendMessageW(control, CB_GETITEMHEIGHT, 0, 0));
    SetWindowPos(reference, nullptr, 0, 0, bounds.right - bounds.left, bounds.bottom - bounds.top,
        SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
    SetWindowPos(combo, nullptr, 0, 0, bounds.right - bounds.left, 220, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
    return reference;
}

/// Compares all interior background rows with an unmodified Windows control, including enabled and disabled states.
static void CheckFieldBackgrounds(HWND edit, HWND combo, HFONT font, bool classic, bool saveImages) {
    std::vector<FieldImage> images;
    const HWND controls[] = { edit, combo };
    for (HWND control : controls) {
        bool isCombo = control == combo;
        RECT bounds = FieldBounds(control);
        HWND reference = isCombo
            ? CreateNativeComboReference(control, font, classic)
            : CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
                700, 300, bounds.right - bounds.left, bounds.bottom - bounds.top, hSettings, nullptr, hInstance, nullptr);
        if (!isCombo) {
            SendMessageW(reference, WM_SETFONT, reinterpret_cast<WPARAM>(font), FALSE);
            SetWindowTheme(reference, classic ? L"" : nullptr, classic ? L"" : nullptr);
        }
        if (isCombo) {
            SendMessageW(control, CB_RESETCONTENT, 0, 0);
            SendMessageW(control, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L""));
            SendMessageW(control, CB_SETCURSEL, 0, 0);
            COMBOBOXEXITEMW item = {};
            item.mask = CBEIF_TEXT;
            item.iItem = 0;
            item.pszText = const_cast<wchar_t*>(L"");
            SendMessageW(reference, CBEM_INSERTITEMW, 0, reinterpret_cast<LPARAM>(&item));
            SendMessageW(reference, CB_SETCURSEL, 0, 0);
        } else {
            SetWindowTextW(control, L"");
            SendMessageW(control, EM_SETCUEBANNER, FALSE, reinterpret_cast<LPARAM>(L""));
        }
        HWND disabledReference = isCombo ? CreateDisabledComboReference(control, font, classic) : nullptr;
        for (int state = 0; state < (isCombo ? 2 : 3); state++) {
            bool enabled = state != 1;
            EnableWindow(control, enabled);
            EnableWindow(reference, enabled);
            if (!isCombo) {
                SendMessageW(control, EM_SETREADONLY, state == 2, 0);
                SendMessageW(reference, EM_SETREADONLY, state == 2, 0);
            }
            FieldImage actual = ReadFieldImage(control);
            HWND expected = isCombo && !enabled ? disabledReference : reference;
            FieldImage native = ReadFieldImage(expected);
            bool matches = actual.width == native.width && actual.height == native.height;
            if (isCombo) {
                for (size_t pixel = 0; matches && pixel < actual.pixels.size(); pixel++) {
                    matches = (actual.pixels[pixel] & 0xFFFFFF) == (native.pixels[pixel] & 0xFFFFFF);
                }
            } else {
                int x = actual.width / 2;
                for (int y = 3; matches && y < actual.height - 3; y++) {
                    size_t pixel = static_cast<size_t>(y) * actual.width + x;
                    matches = (actual.pixels[pixel] & 0xFFFFFF) == (native.pixels[pixel] & 0xFFFFFF);
                }
            }
            Check(matches, isCombo
                ? "entire combo background, border and arrow match native Windows control"
                : "complete edit background matches native Windows control");
            if (!matches) {
                std::printf("  background class=%s state=%d classic=%d\n", isCombo ? "combo" : "edit", state, classic);
                const std::vector<FieldImage> comparison = {
                    actual,
                    native
                };
                SaveFieldComparison(L"SettingsBackgrounds-failure.bmp", comparison);
            }
            images.push_back(actual);
            images.push_back(native);
        }
        EnableWindow(control, TRUE);
        if (!isCombo) {
            SendMessageW(control, EM_SETREADONLY, FALSE, 0);
        }
        if (disabledReference != nullptr) {
            DestroyWindow(disabledReference);
        }
        DestroyWindow(reference);
    }
    if (saveImages) {
        LOGFONTW description = {};
        GetObjectW(font, sizeof(description), &description);
        SaveFieldComparison(wcscmp(description.lfFaceName, L"Cambria Math") == 0
            ? L"SettingsBackgrounds-CambriaMath.bmp"
            : L"SettingsBackgrounds.bmp", images);
    }
}

/// Compares the actual dropdown window with an unmodified native ComboBoxEx, including selection and scrolling.
static void CheckComboDropDownAppearance(HWND combo, HFONT font, bool classic) {
    HWND reference = CreateNativeComboReference(combo, font, classic);
    const HWND fields[] = { combo, reference };
    COMBOBOXINFO actualInfo = { sizeof(actualInfo) };
    COMBOBOXINFO nativeInfo = { sizeof(nativeInfo) };
    GetComboBoxInfo(GetSettingsComboBox(combo), &actualInfo);
    GetComboBoxInfo(GetSettingsComboBox(reference), &nativeInfo);
    for (HWND field : fields) {
        COMBOBOXINFO info = { sizeof(info) };
        GetComboBoxInfo(GetSettingsComboBox(field), &info);
        SetWindowLongPtrW(info.hwndList, GWL_EXSTYLE,
            GetWindowLongPtrW(info.hwndList, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_NOACTIVATE);
        SetLayeredWindowAttributes(info.hwndList, 0, 0, LWA_ALPHA);
    }
    const int counts[] = { 3, LANG_COUNT };
    for (int count : counts) {
        for (HWND field : fields) {
            SendMessageW(field, CB_RESETCONTENT, 0, 0);
        }
        for (int index = 0; index < count; index++) {
            SendMessageW(combo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(LANGUAGE_NAMES[index]));
            COMBOBOXEXITEMW item = {};
            item.mask = CBEIF_TEXT;
            item.iItem = index;
            item.pszText = const_cast<wchar_t*>(LANGUAGE_NAMES[index]);
            SendMessageW(reference, CBEM_INSERTITEMW, 0, reinterpret_cast<LPARAM>(&item));
        }
        for (HWND field : fields) {
            UpdateComboBoxDropDownWidth(field);
        }
        const int selections[] = { 0, count - 1 };
        for (int selection : selections) {
            for (HWND field : fields) {
                SendMessageW(field, CB_SETCURSEL, selection, 0);
            }
            SendMessageW(combo, CB_SHOWDROPDOWN, TRUE, 0);
            FieldImage actual = ReadWindowSurface(actualInfo.hwndList);
            LONG_PTR actualStyle = GetWindowLongPtrW(actualInfo.hwndList, GWL_STYLE);
            SendMessageW(combo, CB_SHOWDROPDOWN, FALSE, 0);
            SendMessageW(reference, CB_SHOWDROPDOWN, TRUE, 0);
            FieldImage native = ReadWindowSurface(nativeInfo.hwndList);
            LONG_PTR nativeStyle = GetWindowLongPtrW(nativeInfo.hwndList, GWL_STYLE);
            SendMessageW(reference, CB_SHOWDROPDOWN, FALSE, 0);
            bool matches = actual.width == native.width && actual.height == native.height;
            for (size_t pixel = 0; matches && pixel < actual.pixels.size(); pixel++) {
                matches = (actual.pixels[pixel] & 0xFFFFFF) == (native.pixels[pixel] & 0xFFFFFF);
            }
            Check(matches, "opened dropdown text, selection, border and scrollbar match native ComboBoxEx");
            Check((actualStyle & WS_VSCROLL) == (nativeStyle & WS_VSCROLL)
                && (actualStyle & WS_VSCROLL) != 0 == (count == LANG_COUNT),
                "native dropdown shows a scrollbar only when its items do not fit");
            LOGFONTW description = {};
            GetObjectW(font, sizeof(description), &description);
            if (!matches) {
                std::printf("  dropdown font=%ls classic=%d count=%d selection=%d actual=%dx%d native=%dx%d\n",
                    description.lfFaceName, classic, count, selection, actual.width, actual.height, native.width,
                    native.height);
            }
            wchar_t name[160] = {};
            swprintf_s(name, L"SettingsDropDown-%ls-%d-%d-%d-actual.bmp", description.lfFaceName, classic, count,
                selection);
            SaveFieldComparison(name, std::vector<FieldImage>{ actual }, 1);
            swprintf_s(name, L"SettingsDropDown-%ls-%d-%d-%d-native.bmp", description.lfFaceName, classic, count,
                selection);
            SaveFieldComparison(name, std::vector<FieldImage>{ native }, 1);
        }
    }
    DestroyWindow(reference);
}

/// Checks populated disabled fields against an ordinary native combo's full background and the enabled field's glyph
/// positions.
static void CheckDisabledComboSelection(HWND combo, HFONT font, bool classic) {
    HWND native = CreateNativeComboReference(combo, font, classic);
    HWND background = CreateDisabledComboReference(combo, font, classic);
    const HWND fields[] = { combo, native };
    for (HWND field : fields) {
        COMBOBOXEXITEMW item = {};
        item.mask = CBEIF_TEXT;
        item.iItem = -1;
        item.pszText = const_cast<wchar_t*>(L"Agyp   Agyp");
        SendMessageW(field, CB_RESETCONTENT, 0, 0);
        SendMessageW(field, CBEM_INSERTITEMW, 0, reinterpret_cast<LPARAM>(&item));
        SendMessageW(field, CB_SETCURSEL, 0, 0);
        SendMessageW(GetSettingsComboBox(field), WM_MOUSELEAVE, 0, 0);
    }
    SetFocus(hSettings);
    FieldImage glyphs = ReadWindowSurface(combo);
    SendMessageW(combo, CB_SETCURSEL, static_cast<WPARAM>(-1), 0);
    FieldImage empty = ReadWindowSurface(combo);
    SendMessageW(combo, CB_SETCURSEL, 0, 0);
    EnableWindow(combo, FALSE);
    FieldImage actual = ReadWindowSurface(combo);
    FieldImage expected = ReadWindowSurface(background);
    bool matches = actual.width == expected.width
        && actual.height == expected.height
        && actual.width == glyphs.width
        && actual.height == glyphs.height;
    COLORREF gray = GetSysColor(COLOR_GRAYTEXT);
    DWORD foreground = RGB(GetBValue(gray), GetGValue(gray), GetRValue(gray));
    bool disabledColor = true;
    RECT nativeInk = { INT_MAX, INT_MAX, -1, -1 };
    RECT actualInk = nativeInk;
    for (int y = 0;
            y < actual.height
            && actual.width == expected.width
            && actual.height == expected.height
            && actual.width == glyphs.width
            && actual.height == glyphs.height;
            y++) {
        for (int x = 0; x < actual.width; x++) {
            size_t pixel = static_cast<size_t>(y) * actual.width + x;
            bool glyph = (glyphs.pixels[pixel] & 0xFFFFFF) != (empty.pixels[pixel] & 0xFFFFFF);
            bool ink = (actual.pixels[pixel] & 0xFFFFFF) != (expected.pixels[pixel] & 0xFFFFFF);
            if (glyph) {
                nativeInk.left = std::min(nativeInk.left, static_cast<LONG>(x));
                nativeInk.top = std::min(nativeInk.top, static_cast<LONG>(y));
                nativeInk.right = std::max(nativeInk.right, static_cast<LONG>(x));
                nativeInk.bottom = std::max(nativeInk.bottom, static_cast<LONG>(y));
            } else if (ink) {
                matches = false;
            }
            if (ink) {
                for (int shift = 0; shift < 24; shift += 8) {
                    DWORD value = actual.pixels[pixel] >> shift & 0xFF;
                    DWORD surface = expected.pixels[pixel] >> shift & 0xFF;
                    DWORD text = foreground >> shift & 0xFF;
                    disabledColor &= value >= std::min(text, surface) && value <= std::max(text, surface);
                }
                actualInk.left = std::min(actualInk.left, static_cast<LONG>(x));
                actualInk.top = std::min(actualInk.top, static_cast<LONG>(y));
                actualInk.right = std::max(actualInk.right, static_cast<LONG>(x));
                actualInk.bottom = std::max(actualInk.bottom, static_cast<LONG>(y));
            }
        }
    }
    bool textMatches = nativeInk.right >= nativeInk.left && EqualRect(&nativeInk, &actualInk);
    Check(matches, "populated disabled combo preserves every native background pixel outside native glyphs");
    Check(textMatches, "disabled combo text retains the enabled field font and glyph positions");
    Check(disabledColor, "disabled combo glyphs use the system disabled text color");
    if (!matches || !textMatches || !disabledColor) {
        LOGFONTW description = {};
        GetObjectW(font, sizeof(description), &description);
        std::printf("  disabled combo font=%ls classic=%d background=%d text=%d\n", description.lfFaceName, classic,
            matches, textMatches);
        const std::vector<FieldImage> images = { actual, expected, glyphs, empty };
        SaveFieldComparison(L"SettingsDisabledCombo-failure.bmp", images);
    }
    EnableWindow(combo, TRUE);
    DestroyWindow(background);
    DestroyWindow(native);
}

/// Compares native combo chrome through hover, focus, blur, disable, and dropdown opening.
/// Selected text is checked separately against row baselines and the enabled/disabled centering contract.
static void CheckComboAppearance(HWND combo, HFONT font, bool classic) {
    HWND reference = CreateNativeComboReference(combo, font, classic);
    SendMessageW(combo, CB_RESETCONTENT, 0, 0);
    SendMessageW(combo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"Agyp"));
    SendMessageW(combo, CB_SETCURSEL, 0, 0);
    COMBOBOXEXITEMW item = {};
    item.mask = CBEIF_TEXT;
    item.iItem = 0;
    item.pszText = const_cast<wchar_t*>(L"Agyp");
    SendMessageW(reference, CBEM_INSERTITEMW, 0, reinterpret_cast<LPARAM>(&item));
    SendMessageW(reference, CB_SETCURSEL, 0, 0);
    std::vector<FieldImage> images;
    const HWND fields[] = { combo, reference };
    for (HWND field : fields) {
        COMBOBOXINFO information = { sizeof(information) };
        GetComboBoxInfo(GetSettingsComboBox(field), &information);
        SetWindowLongPtrW(information.hwndList, GWL_EXSTYLE,
            GetWindowLongPtrW(information.hwndList, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_NOACTIVATE);
        SetLayeredWindowAttributes(information.hwndList, 0, 0, LWA_ALPHA);
    }
    for (int state = 0; state < 6; state++) {
        for (HWND field : fields) {
            EnableWindow(field, state != 4);
            SendMessageW(GetSettingsComboBox(field), WM_MOUSELEAVE, 0, 0);
        }
        SetFocus(hSettings);
        if (state == 1) {
            for (HWND field : fields) {
                SendMessageW(GetSettingsComboBox(field), WM_MOUSEMOVE, 0, MAKELPARAM(10, 10));
            }
        } else if (state == 2) {
            SetFocus(combo);
            Check(GetFocus() == GetSettingsComboBox(combo), "combo receives native keyboard focus");
        } else if (state == 3) {
            SetFocus(combo);
            SetFocus(hSettings);
        } else if (state == 5) {
            SendMessageW(combo, CB_SHOWDROPDOWN, TRUE, 0);
        }
        HWND disabledReference = nullptr;
        if (state == 4) {
            disabledReference = CreateDisabledComboReference(combo, font, classic);
            SendMessageW(combo, CB_SETCURSEL, static_cast<WPARAM>(-1), 0);
        }
        FieldImage actual = ReadWindowSurface(combo);
        if (state == 2) {
            SetFocus(reference);
        } else if (state == 3) {
            SetFocus(reference);
            SetFocus(hSettings);
        } else if (state == 5) {
            SendMessageW(combo, CB_SHOWDROPDOWN, FALSE, 0);
            SendMessageW(reference, CB_SHOWDROPDOWN, TRUE, 0);
        }
        FieldImage native = ReadWindowSurface(disabledReference != nullptr ? disabledReference : reference);
        bool matches = actual.width == native.width && actual.height == native.height;
        COMBOBOXINFO information = { sizeof(information) };
        GetComboBoxInfo(GetSettingsComboBox(combo), &information);
        RECT frame = FieldBounds(combo);
        RECT inner = FieldBounds(GetSettingsComboBox(combo));
        RECT selection = information.rcItem;
        OffsetRect(&selection, inner.left - frame.left, inner.top - frame.top);
        for (int y = 0; matches && y < actual.height; y++) {
            for (int x = 0; matches && x < actual.width; x++) {
                if (state == 4
                    || x < selection.left
                    || x >= selection.right
                    || y < selection.top
                    || y >= selection.bottom) {
                    size_t pixel = static_cast<size_t>(y) * actual.width + x;
                    matches = (actual.pixels[pixel] & 0xFFFFFF) == (native.pixels[pixel] & 0xFFFFFF);
                }
            }
        }
        Check(matches, "combo frame, arrow, and outer focus states match unmodified Windows Common Controls");
        if (!matches) {
            std::printf("  combo appearance state=%d classic=%d\n", state, classic);
            const std::vector<FieldImage> comparison = { actual, native };
            SaveFieldComparison(L"SettingsComboAppearance-failure.bmp", comparison);
        }
        images.push_back(actual);
        images.push_back(native);
        if (disabledReference != nullptr) {
            DestroyWindow(disabledReference);
            SendMessageW(combo, CB_SETCURSEL, 0, 0);
        }
        SendMessageW(reference, CB_SHOWDROPDOWN, FALSE, 0);
    }
    LOGFONTW description = {};
    GetObjectW(font, sizeof(description), &description);
    wchar_t name[128] = {};
    swprintf_s(name, L"SettingsComboAppearance-%ls-%ls.bmp", description.lfFaceName, classic ? L"classic" : L"themed");
    SaveFieldComparison(name, images);
    SetFocus(hSettings);
    EnableWindow(combo, TRUE);
    DestroyWindow(reference);
}

/// Verifies real native edit borders through hover, focus, blur, disable, and read-only transitions with both themes.
static void CheckEditBorders(HWND edit, HFONT font, bool classic, bool saveImages) {
    RECT bounds = FieldBounds(edit);
    HWND reference = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 700, 350,
        bounds.right - bounds.left, bounds.bottom - bounds.top, hSettings, nullptr, hInstance, nullptr);
    SendMessageW(reference, WM_SETFONT, reinterpret_cast<WPARAM>(font), FALSE);
    SetWindowTheme(reference, classic ? L"" : nullptr, classic ? L"" : nullptr);
    std::vector<FieldImage> images;
    for (int state = 0; state < 7; state++) {
        const HWND fields[] = { edit, reference };
        for (HWND field : fields) {
            EnableWindow(field, state != 4);
            SendMessageW(field, EM_SETREADONLY, state >= 5, 0);
            SendMessageW(field, WM_MOUSELEAVE, 0, 0);
        }
        SetFocus(hSettings);
        if (state == 1) {
            SendMessageW(edit, WM_MOUSEMOVE, 0, MAKELPARAM(10, 10));
            SendMessageW(reference, WM_MOUSEMOVE, 0, MAKELPARAM(10, 10));
        } else if (state == 2 || state == 6) {
            SetFocus(edit);
            Check(GetFocus() == edit, "edit receives native keyboard focus for border comparison");
            HideCaret(edit);
        } else if (state == 3) {
            SetFocus(edit);
            SetFocus(hSettings);
        }
        FieldImage actual = ReadWindowSurface(SettingsEdit::GetFrame(edit));
        FieldImage printed = ReadFieldImage(edit);
        if (state == 2 || state == 6) {
            SetFocus(reference);
            Check(GetFocus() == reference, "reference edit receives native keyboard focus for border comparison");
            HideCaret(reference);
        } else if (state == 3) {
            SetFocus(reference);
            SetFocus(hSettings);
        }
        FieldImage native = ReadWindowSurface(reference);
        bool matches = SameFieldBorder(actual, native, reference);
        Check(matches, "edit border matches actual native Windows rendering in every state");
        Check(SameFieldBorder(actual, printed, reference), "printed edit border matches its actual window surface");
        if (!matches) {
            std::printf("  edit border state=%d classic=%d\n", state, classic);
            const std::vector<FieldImage> comparison = { actual, native };
            SaveFieldComparison(L"SettingsEditBorders-failure.bmp", comparison);
        }
        images.push_back(actual);
        images.push_back(native);
    }
    if (saveImages) {
        LOGFONTW description = {};
        GetObjectW(font, sizeof(description), &description);
        wchar_t name[128] = {};
        swprintf_s(name, L"SettingsEditBorders-%ls-%ls.bmp", description.lfFaceName, classic ? L"classic" : L"themed");
        SaveFieldComparison(name, images);
    }
    SetFocus(hSettings);
    EnableWindow(edit, TRUE);
    SendMessageW(edit, EM_SETREADONLY, FALSE, 0);
    DestroyWindow(reference);
}

/// Saves complete text-bearing fields in enabled and disabled states for direct inspection of background and glyphs.
static void SaveRenderedFields(HWND edit, HWND combo, const wchar_t* face) {
    SetWindowTextW(edit, L"Agyp Hodiny 1");
    SendMessageW(combo, CB_RESETCONTENT, 0, 0);
    SendMessageW(combo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"Agyp Hodiny 1"));
    SendMessageW(combo, CB_SETCURSEL, 0, 0);
    std::vector<FieldImage> images;
    const bool enabledStates[] = { true, false };
    for (bool enabled : enabledStates) {
        EnableWindow(edit, enabled);
        EnableWindow(combo, enabled);
        images.push_back(ReadFieldImage(edit));
        images.push_back(ReadFieldImage(combo));
    }
    SaveFieldComparison(wcscmp(face, L"Cambria Math") == 0
        ? L"SettingsFields-CambriaMath.bmp"
        : L"SettingsFields.bmp", images);
    EnableWindow(edit, TRUE);
    EnableWindow(combo, TRUE);
}

/// Exercises the height ceiling, smaller natural rows, Cambria Math, and native font, theme, and editing operations.
static void TestFields() {
    HWND label = AddUnderlayStatic(hSettings, L"", WS_VISIBLE, 8, 24, 22);
    HWND combo = AddControl(0, WC_COMBOBOXW, L"", CBS_DROPDOWNLIST, 150, 20, 210, 220, hSettings, 50001, nullptr, label);
    HWND editLabel = AddUnderlayStatic(hSettings, L"", WS_VISIBLE, 8, 90, 22);
    HWND edit = AddControl(WS_EX_CLIENTEDGE, L"EDIT", L"", ES_AUTOHSCROLL, 150, 86, 210, 24, hSettings, 50002, nullptr,
        editLabel);
    HWND button = AddControl(0, L"BUTTON", L"", BS_PUSHBUTTON, 410, 20, 200, UI_BUTTON_HEIGHT, hSettings, 50003);
    HWND checkbox = AddControl(0, L"BUTTON", L"", BS_AUTOCHECKBOX, 8, 20, 230, 24, hSettings, 50004);
    HWND note = AddControl(0, L"STATIC", L"A paragraph that may wrap onto several lines", SS_LEFT, 8, 160, 100, 80,
        hSettings, 50005);
    UpdateSettingsTextControlLayout(hSettings);
    const bool classicStates[] = { false, true };
    for (bool classic : classicStates) {
        themesDisabled = classic;
        const wchar_t* const faces[] = {
            L"Segoe UI",
            L"Cambria Math",
            L"Tahoma",
            L"Arial",
            L"Cambria Math",
            L"Segoe UI"
        };
        const int weights[] = { FW_NORMAL, FW_BOLD };
        const bool italicStates[] = { false, true };
        for (const wchar_t* face : faces) {
            for (int weight : weights) {
                for (bool italic : italicStates) {
                    int previousFailures = failures;
                    NONCLIENTMETRICSW system = { sizeof(system) };
                    SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof(system), &system, 0);
                    wcsncpy_s(system.lfMessageFont.lfFaceName, face, _TRUNCATE);
                    system.lfMessageFont.lfWeight = weight;
                    system.lfMessageFont.lfItalic = italic;
                    HFONT font = CreateFontIndirectW(&system.lfMessageFont);
                    hUiFont = font;
                    EnumChildWindows(hSettings, ApplyFontAndTheme, 0);
                    EnumChildWindows(hSettings, UpdateSettingsFieldMetrics, 0);
                    AlignSettingsControl(label, combo);
                    AlignSettingsControl(editLabel, edit);
                    AlignSettingsControl(button, combo);
                    AlignSettingsControl(checkbox, combo);
                    RECT comboBounds = FieldBounds(combo);
                    RECT editBounds = FieldBounds(edit);
                    LONG comboHeight = comboBounds.bottom - comboBounds.top;
                    LONG editHeight = editBounds.bottom - editBounds.top;
                    LONG labelHeight = FieldBounds(label).bottom - FieldBounds(label).top;
                    Check(comboHeight <= 28 && editHeight <= 28 && labelHeight <= 28,
                        "all targeted controls respect the height ceiling");
                    if (wcscmp(face, L"Cambria Math") == 0) {
                        Check(comboHeight == 28 && editHeight == 28 && labelHeight == 28,
                            "Cambria Math is capped at28 with its own font retained");
                    } else {
                        Check(comboHeight < 28 && editHeight < 28 && labelHeight < 28,
                            "smaller selected font metrics produce smaller controls");
                    }
                    Check(FieldBounds(note).bottom - FieldBounds(note).top == 80, "wrapped note remains unrestricted");
                    Check(reinterpret_cast<HFONT>(SendMessageW(edit, WM_GETFONT, 0, 0)) == font,
                        "chosen native edit font is preserved");
                    TextInk comboInk = ReadInk(combo, true);
                    CheckBaseline(comboInk, label, "combo and row label share rendered baseline");
                    CheckBaseline(comboInk, button, "combo and native button share rendered baseline");
                    CheckBaseline(comboInk, checkbox, "combo and native checkbox share rendered baseline");
                    TextInk editInk = ReadInk(edit, false);
                    CheckBaseline(editInk, editLabel, "native edit and row label share rendered baseline");
                    RECT viewport = FieldBounds(edit);
                    Check(editInk.top >= viewport.top && editInk.bottom < viewport.bottom,
                        "native edit text remains visible inside its height-limited viewport");
                    SetWindowTextW(edit, L"abcdef");
                    SendMessageW(edit, EM_SETSEL, 2, 4);
                    SendMessageW(edit, EM_REPLACESEL, TRUE, reinterpret_cast<LPARAM>(L"XY"));
                    Check(GetControlText(edit) == L"abXYef", "native replacement and selection preserved");
                    SendMessageW(edit, EM_UNDO, 0, 0);
                    Check(GetControlText(edit) == L"abcdef", "native undo preserved");
                    Check(nativeChanges > 0, "native edit notifications reach original settings parent");
                    SetControlVisible(edit, false);
                    Check((GetWindowLongPtrW(SettingsEdit::GetFrame(edit), GWL_STYLE) & WS_VISIBLE) == 0,
                        "hiding an edit hides its viewport");
                    SetControlVisible(edit, true);
                    EnableWindow(edit, FALSE);
                    Check(!IsWindowEnabled(SettingsEdit::GetFrame(edit)), "disabled edit disables viewport");
                    EnableWindow(edit, TRUE);
                    Check(IsWindowEnabled(SettingsEdit::GetFrame(edit)), "edit viewport re-enables");
                    SetControlPosition(edit, 150, 86, 210, 100);
                    Check(FieldBounds(edit).bottom - FieldBounds(edit).top == editHeight,
                        "relayout cannot enlarge single-line edit");
                    CheckFieldBackgrounds(edit, combo, font, classic,
                        (wcscmp(face, L"Segoe UI") == 0 || wcscmp(face, L"Cambria Math") == 0)
                            && weight == FW_NORMAL && !italic && !classic);
                    if ((wcscmp(face, L"Segoe UI") == 0 || wcscmp(face, L"Cambria Math") == 0)
                            && weight == FW_NORMAL && !italic) {
                        CheckComboAppearance(combo, font, classic);
                        CheckComboDropDownAppearance(combo, font, classic);
                    }
                    CheckDisabledComboSelection(combo, font, classic);
                    CheckEditBorders(edit, font, classic,
                        (wcscmp(face, L"Segoe UI") == 0 || wcscmp(face, L"Cambria Math") == 0)
                            && weight == FW_NORMAL
                            && !italic);
                    if ((wcscmp(face, L"Segoe UI") == 0 || wcscmp(face, L"Cambria Math") == 0)
                            && weight == FW_NORMAL
                            && !italic
                            && !classic) {
                        SaveRenderedFields(edit, combo, face);
                    }
                    COMBOBOXINFO info = { sizeof(info) };
                    GetComboBoxInfo(GetSettingsComboBox(combo), &info);
                    SetWindowLongPtrW(info.hwndList, GWL_EXSTYLE,
                        GetWindowLongPtrW(info.hwndList, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_NOACTIVATE);
                    SetLayeredWindowAttributes(info.hwndList, 0, 0, LWA_ALPHA);
                    SendMessageW(combo, CB_RESETCONTENT, 0, 0);
                    for (int item = 0; item < LANG_COUNT; item++) {
                        SendMessageW(combo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(LANGUAGE_NAMES[item]));
                    }
                    SendMessageW(combo, CB_SETCURSEL, LANG_COUNT - 1, 0);
                    SendMessageW(combo, CB_SHOWDROPDOWN, TRUE, 0);
                    Check(FieldBounds(combo).bottom - FieldBounds(combo).top == comboHeight,
                        "opening dropdown cannot enlarge closed field");
                    SCROLLINFO scroll = { sizeof(scroll), SIF_ALL };
                    GetScrollInfo(info.hwndList, SB_VERT, &scroll);
                    Check(scroll.nMax + 1 > static_cast<int>(scroll.nPage), "long dropdown has vertical scrolling");
                    Check(SendMessageW(combo, CB_GETCURSEL, 0, 0) == LANG_COUNT - 1,
                        "last language remains selectable");
                    SendMessageW(combo, CB_SHOWDROPDOWN, FALSE, 0);
                    HFONT stock = static_cast<HFONT>(GetStockObject(DEFAULT_GUI_FONT));
                    hUiFont = stock;
                    EnumChildWindows(hSettings, ApplyFontAndTheme, 0);
                    DeleteObject(font);
                    if (failures != previousFailures) {
                        std::printf("Font=%ls weight=%d italic=%d classic=%d\n", face, weight, italic, classic);
                    }
                }
            }
        }
    }
    hUiFont = nullptr;
}

/// Verifies actual localized initial text, deliberately empty names, and XML persistence without touching user settings.
static void TestAdditionalClockNames() {
    settingsDraft.resize(1);
    Check(DefaultAdditionalClockName(LANG_CS, 0) == L"Hodiny 1"
        && DefaultAdditionalClockName(LANG_CS, 1) == L"Hodiny 2", "Czech initial names match timedate.cpl resources");
    for (int value = 0; value < LANG_COUNT; value++) {
        AppLanguage language = static_cast<AppLanguage>(value);
        WidgetConfig config = CreateStoredWidgetDefaults(WIDGET_PANEL, 0, language, FONT_ANTIALIAS_CLEARTYPE);
        settingsDraft[0] = config;
        LoadDraftIntoControls();
        for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
            std::wstring expected = DefaultAdditionalClockName(language, index);
            Check(!expected.empty() && config.additionalClocks[index].name == expected,
                "new clock contains a localized name in its stored configuration");
            Check(GetControlText(hAdditionalNameEdits[index]) == expected,
                "localized initial clock name is actual editable text");
            wchar_t cue[128] = {};
            SendMessageW(hAdditionalNameEdits[index], EM_GETCUEBANNER, reinterpret_cast<WPARAM>(cue), ARRAYSIZE(cue));
            Check(cue[0] == L'\0', "additional clock edit has no placeholder");
            SetWindowTextW(hAdditionalNameEdits[index], L"");
        }
        Check(ReadWidgetControls(config, false), "cleared clock names pass normal settings validation");
        settingsDraft[0] = config;
        LoadDraftIntoControls();
        for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
            Check(config.additionalClocks[index].name.empty() && AdditionalClockName(config, index).empty()
                && GetControlText(hAdditionalNameEdits[index]).empty(),
                "empty name remains empty in settings and in the rendered clock label");
        }
        config.additionalClocks[1].name = L"Київ <&> Москва";
        std::vector<BYTE> bytes;
        std::vector<WidgetConfig> loaded;
        Check(SerializeWidgetClipboardData(std::vector<WidgetConfig>{ config }, & bytes)
            && DeserializeWidgetClipboardData(bytes, LANG_EN_US, CreateStoredWidgetDefaults, &loaded)
            && loaded.size() == 1, "additional clock name snapshot round trip");
        if (loaded.size() == 1) {
            Check(loaded[0].additionalClocks[0].name.empty()
                && loaded[0].additionalClocks[1].name == config.additionalClocks[1].name,
                "XML round trip preserves empty and custom Unicode names exactly");
        }
        std::string xml = "<CalClockSettings version=\"1\"><Widget id=\"1\" language=\""
            + std::to_string(value) + "\" additionalClock1Name=\"\"/></CalClockSettings>";
        bytes.assign(xml.begin(), xml.end());
        loaded.clear();
        Check(DeserializeWidgetClipboardData(bytes, LANG_EN_US, CreateStoredWidgetDefaults, &loaded)
            && loaded.size() == 1, "older snapshot with a missing clock name loads");
        if (loaded.size() == 1) {
            Check(loaded[0].additionalClocks[0].name.empty()
                && loaded[0].additionalClocks[1].name == DefaultAdditionalClockName(language, 1),
                "only a missing name receives its widget-language default; a saved empty name is retained");
        }
    }
    SettingsSnapshot snapshot;
    snapshot.widgets = settingsDraft;
    wchar_t executable[MAX_PATH] = {};
    GetModuleFileNameW(nullptr, executable, ARRAYSIZE(executable));
    PathRemoveFileSpecW(executable);
    std::wstring path = std::wstring(executable) + L"/AdditionalClockNames.xml";
    SettingsSnapshot loaded;
    Check(WriteSettingsXml(path, snapshot) && ReadSettingsXml(path, LANG_EN_US, CreateStoredWidgetDefaults, &loaded)
        && loaded.widgets.size() == 1 && loaded.widgets[0].additionalClocks[0].name.empty()
        && loaded.widgets[0].additionalClocks[1].name.empty(),
        "empty clock names survive saving and reopening a settings file");
    Check(DeleteFileW(path.c_str()) != FALSE, "temporary settings snapshot removed");
}

/// Verifies that a complete descriptive text fits by rendering an unrestricted-height reference with the same font
/// and width.
static void CheckWrappedTextFits(HWND control) {
    RECT bounds = {};
    GetClientRect(control, &bounds);
    int height = 1024;
    BITMAPINFO information = {};
    information.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    information.bmiHeader.biWidth = bounds.right;
    information.bmiHeader.biHeight = -height;
    information.bmiHeader.biPlanes = 1;
    information.bmiHeader.biBitCount = 32;
    HDC dc = CreateCompatibleDC(nullptr);
    void* bits = nullptr;
    HBITMAP bitmap = CreateDIBSection(dc, &information, DIB_RGB_COLORS, &bits, nullptr, 0);
    HGDIOBJ previous = SelectObject(dc, bitmap);
    HFONT font = reinterpret_cast<HFONT>(SendMessageW(control, WM_GETFONT, 0, 0));
    HGDIOBJ previousFont = SelectObject(dc, font);
    RECT canvas = { 0, 0, bounds.right, height };
    FillRect(dc, &canvas, GetSysColorBrush(COLOR_WINDOW));
    SetTextColor(dc, RGB(0, 0, 0));
    SetBkMode(dc, TRANSPARENT);
    DrawWordWrappedText(dc, GetControlText(control), canvas);
    GdiFlush();
    DWORD* pixels = static_cast<DWORD*>(bits);
    DWORD background = LayeredOpaquePixel(GetSysColor(COLOR_WINDOW)) & 0xFFFFFF;
    bool fits = true;
    for (int y = bounds.bottom; fits && y < height; y++) {
        for (int x = 0; x < bounds.right; x++) {
            if ((pixels[static_cast<size_t>(y) * bounds.right + x] & 0xFFFFFF) != background) {
                fits = false;
                break;
            }
        }
    }
    Check(fits, "complete wrapped description fits inside its visible control");
    SelectObject(dc, previousFont);
    SelectObject(dc, previous);
    DeleteObject(bitmap);
    DeleteDC(dc);
}

/// Compares a native checkbox's glyph and text with the complete page image, ignoring its uniform empty background.
static bool IsCheckboxContentVisible(HWND control) {
    HWND parent = GetParent(control);
    FieldImage checkbox = ReadFieldImage(control);
    FieldImage page = ReadFieldImage(parent, true);
    RECT bounds = FieldBounds(control);
    RECT parentBounds = FieldBounds(parent);
    OffsetRect(&bounds, -parentBounds.left, -parentBounds.top);
    DWORD background = checkbox.pixels.front() & 0xFFFFFF;
    int contentPixels = 0;
    for (int y = 0; y < checkbox.height; y++) {
        for (int x = 0; x < checkbox.width; x++) {
            DWORD pixel = checkbox.pixels[static_cast<size_t>(y) * checkbox.width + x] & 0xFFFFFF;
            if (pixel == background) {
                continue;
            }
            contentPixels++;
            LONG pageX = bounds.left + x;
            LONG pageY = bounds.top + y;
            if (pageX < 0
                    || pageX >= page.width
                    || pageY < 0
                    || pageY >= page.height
                    || (page.pixels[static_cast<size_t>(pageY) * page.width + pageX] & 0xFFFFFF) != pixel) {
                return false;
            }
        }
    }
    return contentPixels > 0;
}

/// Checks the three Size fields against their actual row label in both enabled states without moving their frames.
static void CheckPanelSizeComboBaselines() {
    TextInk label = ReadInk(hSizeLabel, false);
    const HWND controls[] = { hSizeCombo, hAdditionalSizeCombos[0], hAdditionalSizeCombos[1] };
    for (HWND combo : controls) {
        bool enabled = IsWindowEnabled(combo) != FALSE;
        RECT before = FieldBounds(combo);
        EnableWindow(combo, TRUE);
        TextInk active = ReadInk(combo, true);
        EnableWindow(combo, FALSE);
        TextInk inactive = ReadInk(combo, true);
        RECT after = FieldBounds(combo);
        Check(active.pixels > 0
            && inactive.pixels > 0
            && label.pixels > 0
            && active.top == inactive.top
            && active.bottom == inactive.bottom,
            "Size text remains at the identical vertical position when enabled or disabled");
        Check(active.bottom == label.bottom && inactive.bottom == label.bottom,
            "all three Size combos share the rendered label baseline in both enabled states");
        Check(EqualRect(&before, &after), "enabling a Size combo never moves its frame");
        EnableWindow(combo, enabled);
    }
}

/// Verifies every settings row and native tab order after changing fonts and widget layout in the complete form.
static void TestCompleteSettings() {
    DWORD style = 0;
    int width = 0;
    int height = 0;
    GetSettingsWindowLayout(0, &style, &width, &height);
    SetWindowPos(hSettings, nullptr, 0, 0, settingsContentWidth, settingsContentHeight, SWP_NOZORDER | SWP_NOACTIVATE);
    for (int index = 0; index < 6; index++) {
        NtpQueryLogEntry entry;
        entry.server = L"pool.ntp.org";
        entry.success = index % 2 == 0;
        FILETIME timestamp = {};
        GetSystemTimeAsFileTime(&timestamp);
        entry.completedTime = static_cast<ULONGLONG>(timestamp.dwHighDateTime) << 32 | timestamp.dwLowDateTime;
        ntpSynchronizationLog.push_back(entry);
    }
    Check(CreateSettingsControls(), "complete settings form creation");
    for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
        Check(GetControlText(hAdditionalNameEdits[index]) == DefaultAdditionalClockName(appLanguage, index),
            "newly created edit contains its actual localized initial name");
    }
    std::vector<HWND> fields;
    for (HWND page : {hSettings, hGeneralPage, hAppearancePage, hAlarmPage, hTimeSignalPage, hTimePage,
            hApplicationPage}) {
        for (HWND child = GetWindow(page, GW_CHILD); child != nullptr; child = GetWindow(child, GW_HWNDNEXT)) {
            wchar_t className[64] = {};
            GetClassNameW(child, className, ARRAYSIZE(className));
            if (GetPropW(child, SETTINGS_FIELD_LABEL_PROPERTY) != nullptr
                    || wcscmp(className, WC_COMBOBOXW) == 0
                    || wcscmp(className, WC_COMBOBOXEXW) == 0
                    || SettingsEdit::GetEdit(child) != nullptr) {
                fields.push_back(child);
            }
        }
    }
    Check(fields.size() > 40, "all settings field types are covered");
    for (int index = 0; index < MAX_WIDGET_COUNT; index++) {
        WidgetConfig config = CreateStoredWidgetDefaults(WIDGET_PANEL, index, LANG_CS, FONT_ANTIALIAS_CLEARTYPE);
        config.name = L"Widget " + std::to_wstring(index + 1) + L" ČŠŽýgp";
        settingsDraft.push_back(config);
        SendMessageW(hWidgetList, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(config.name.c_str()));
        SendMessageW(hWidgetList, LB_SETITEMDATA, index, index);
    }
    selectedDraftIndex = 0;
    SendMessageW(hWidgetList, LB_SETSEL, TRUE, 0);
    LoadDraftIntoControls();
    const bool classicStates[] = { false, true };
    const wchar_t* const faces[] = { L"Segoe UI", L"Cambria Math", L"Segoe UI" };
    for (bool classic : classicStates) {
        themesDisabled = classic;
        for (const wchar_t* face : faces) {
            settingsAppFontFace = face;
            settingsAppFontWeight = FW_NORMAL;
            settingsAppFontItalic = false;
            SetCheck(hDisableThemesCheck, classic);
            ApplyApplicationFontPreview();
            UpdateApplicationFontButtons();
            SendMessageW(hWidgetList, LB_SETSEL, TRUE, -1);
            Check(SendMessageW(hWidgetList, LB_GETSELCOUNT, 0, 0) == MAX_WIDGET_COUNT,
                "compact widget rows retain native multiple selection");
            SendMessageW(hWidgetList, LB_SETSEL, FALSE, -1);
            SendMessageW(hWidgetList, LB_SETSEL, TRUE, 0);
            SendMessageW(hWidgetList, LB_SETTOPINDEX, MAX_WIDGET_COUNT - 1, 0);
            RECT lastRow = {};
            RECT listClient = {};
            GetClientRect(hWidgetList, &listClient);
            SendMessageW(hWidgetList, LB_GETITEMRECT, MAX_WIDGET_COUNT - 1, reinterpret_cast<LPARAM>(&lastRow));
            Check(lastRow.top >= 0 && lastRow.bottom <= listClient.bottom,
                "last widget row remains fully visible after scrolling");
            Check(SendMessageW(hWidgetList, LB_GETITEMDATA, MAX_WIDGET_COUNT - 1, 0) == MAX_WIDGET_COUNT - 1,
                "compact widget rows retain item identities");
            SendMessageW(hWidgetList, LB_SETTOPINDEX, 0, 0);
            RECT header = {};
            TabCtrl_GetItemRect(hTabs, 0, &header);
            Check(header.bottom - header.top <= UI_BUTTON_HEIGHT, "tab headers remain bounded with the chosen font");
            if (wcscmp(face, L"Segoe UI") == 0) {
                Check(header.bottom - header.top < UI_BUTTON_HEIGHT,
                    "tab headers shrink back with ordinary font metrics");
            }
            for (int value = 0; value < WIDGET_TYPE_COUNT; value++) {
                WidgetType type = static_cast<WidgetType>(value);
                settingsDraft[0] = CreateStoredWidgetDefaults(type, 0, LANG_CS, FONT_ANTIALIAS_CLEARTYPE);
                settingsDraft[0].additionalClocks[0].enabled = true;
                settingsDraft[0].additionalClocks[1].enabled = true;
                LoadDraftIntoControls();
                const HWND lists[] = { hWidgetList };
                for (HWND list : lists) {
                    LRESULT rowHeight = SendMessageW(list, LB_GETITEMHEIGHT, 0, 0);
                    Check(rowHeight > 0 && rowHeight <= UI_BUTTON_HEIGHT,
                        "widget list rows remain compact in their selected font");
                    Check(reinterpret_cast<HFONT>(SendMessageW(list, WM_GETFONT, 0, 0)) == hUiFont,
                        "widget list preserves the application font");
                }
                Check(SendMessageW(hWidgetList, LB_GETSELCOUNT, 0, 0) == 1
                    && SendMessageW(hWidgetList, LB_GETITEMDATA, 0, 0) == 0,
                    "font changes preserve widget selection and identity");
                for (int tab = 0; tab < SETTINGS_TAB_COUNT; tab++) {
                    TabCtrl_SetCurSel(hTabs, tab);
                    ShowSettingsTab(tab);
                    RECT display = {};
                    GetClientRect(hTabs, &display);
                    TabCtrl_AdjustRect(hTabs, FALSE, &display);
                    RECT page = FieldBounds(GetSettingsPage(tab));
                    MapWindowPoints(HWND_DESKTOP, hTabs, reinterpret_cast<POINT*>(&page), 2);
                    Check(EqualRect(&display, &page), "active page exactly fits the native tab display area");
                    Check(page.top >= header.bottom, "page content cannot cover tab headers");
                    Check(IsWindowVisible(GetSettingsPage(tab)) != FALSE, "selected settings page is visible");
                    for (int other = 0; other < SETTINGS_TAB_COUNT; other++) {
                        if (other != tab) {
                            Check(IsWindowVisible(GetSettingsPage(other)) == FALSE,
                                "inactive settings pages remain hidden");
                        }
                    }
                    if (wcscmp(face, L"Cambria Math") == 0 || type == WIDGET_PANEL) {
                        wchar_t name[128] = {};
                        swprintf_s(name, L"Settings-%s-%s-widget%d-tab%d.bmp", face, classic ? L"classic" : L"themed",
                            value, tab);
                        FieldImage complete = ReadFieldImage(hSettings, true);
                        RECT selectedRow = {};
                        SendMessageW(hWidgetList, LB_GETITEMRECT, 0, reinterpret_cast<LPARAM>(&selectedRow));
                        MapWindowPoints(hWidgetList, hSettings, reinterpret_cast<POINT*>(&selectedRow), 2);
                        DWORD textColor = LayeredOpaquePixel(GetSysColor(COLOR_HIGHLIGHTTEXT)) & 0xFFFFFF;
                        bool visibleText = false;
                        for (int y = selectedRow.top + 1; y < selectedRow.bottom - 1; y++) {
                            for (int x = selectedRow.left + 1; x < selectedRow.right - 1; x++) {
                                if ((complete.pixels[static_cast<size_t>(y) * complete.width + x] & 0xFFFFFF)
                                        == textColor) {
                                    visibleText = true;
                                }
                            }
                        }
                        Check(visibleText, "widget item text is visible in the complete form image");
                        const std::vector<FieldImage> images = {
                            complete
                        };
                        SaveFieldComparison(name, images, 1);
                    }
                    HWND active = GetSettingsPage(tab);
                    for (HWND control = GetWindow(active, GW_CHILD);
                            control != nullptr;
                            control = GetWindow(control, GW_HWNDNEXT)) {
                        wchar_t className[32] = {};
                        GetClassNameW(control, className, ARRAYSIZE(className));
                        if (wcscmp(className, L"Static") == 0
                                && IsWindowVisible(control)
                                && !GetControlText(control).empty()) {
                            Check(ReadInk(control, false).pixels > 0,
                                "every visible nonempty settings label renders text");
                        }
                    }
                    if (tab == 0 && type == WIDGET_FULLSCREEN) {
                        HWND monitorHeader = ListView_GetHeader(hMonitorList);
                        RECT row = {};
                        Check(ListView_GetItemRect(hMonitorList, 0, &row, LVIR_BOUNDS) != FALSE,
                            "monitor report contains the actual display row");
                        Check(row.bottom > row.top && row.bottom - row.top <= UI_BUTTON_HEIGHT,
                            "monitor report rows remain compact with the selected font");
                        Check(FieldBounds(monitorHeader).bottom - FieldBounds(monitorHeader).top <= UI_BUTTON_HEIGHT,
                            "monitor report header remains compact with the selected font");
                        Check(reinterpret_cast<HFONT>(SendMessageW(hMonitorList, WM_GETFONT, 0, 0)) == hUiFont,
                            "monitor report preserves the selected application font");
                        RECT monitor = FieldBounds(hMonitorList);
                        RECT log = FieldBounds(hNtpLogList);
                        RECT label = FieldBounds(hMonitorLabel);
                        RECT blackout = FieldBounds(hBlackoutMonitorsCheck);
                        Check(monitor.right - monitor.left == log.right - log.left
                            && monitor.bottom - monitor.top == log.bottom - log.top,
                            "monitor report matches the Time log width and height");
                        Check(monitor.top - label.top == 25,
                            "monitor report retains the requested label spacing");
                        Check(blackout.top >= monitor.bottom,
                            "monitor report fits above the blackout checkbox");
                        Check(IsCheckboxContentVisible(hBlackoutMonitorsCheck),
                            "blackout checkbox glyph and text remain fully visible in the complete page");
                        Check(monitorColumnsInitialized,
                            "monitor columns fit when the fullscreen controls become visible");
                        Check((GetWindowLongPtrW(hMonitorList, GWL_STYLE) & LVS_OWNERDRAWFIXED) == 0,
                            "every monitor font and theme layout retains native row painting");
                    } else if (tab == 1) {
                        if (type == WIDGET_PANEL) {
                            CheckPanelSizeComboBaselines();
                        }
                        CheckBaseline(ReadInk(hOpacityLabel, false), hOpacityValue,
                            "opacity value shares its row's text baseline");
                    } else if (tab == 3) {
                        CheckWrappedTextFits(GetDlgItem(hTimeSignalPage, ID_TIME_SIGNAL_NOTE));
                    } else if (tab == 4) {
                        RECT logHeader = FieldBounds(ListView_GetHeader(hNtpLogList));
                        RECT row = {};
                        ListView_GetItemRect(hNtpLogList, 0, &row, LVIR_BOUNDS);
                        Check(logHeader.bottom - logHeader.top <= UI_BUTTON_HEIGHT,
                            "log header remains compact in the selected font");
                        Check(row.bottom > row.top && ListView_GetCountPerPage(hNtpLogList) >= 3,
                            "synchronization log retains space for multiple complete records");
                        Check(ListView_GetItemCount(hNtpLogList) == 6,
                            "font and theme changes preserve every log record");
                        CheckWrappedTextFits(hNtpServersLabel);
                        CheckWrappedTextFits(hNtpStatus);
                        CheckWrappedTextFits(hTimeGlobalNote);
                        RECT status = FieldBounds(hNtpStatus);
                        RECT log = FieldBounds(hNtpLogList);
                        RECT note = FieldBounds(hTimeGlobalNote);
                        RECT save = FieldBounds(hNtpSaveLogButton);
                        Check(status.bottom <= log.top && note.top >= save.bottom,
                            "synchronization notes cannot cover the log or its export button");
                    } else if (tab == 5) {
                        CheckApplicationRowSpacing();
                    }
                }
                for (HWND field : fields) {
                    RECT bounds = FieldBounds(field);
                    Check(bounds.bottom - bounds.top <= 28,
                        "complete settings field respects maximum height after font, theme, and widget changes");
                }
            }
            Check(GetPropW(hNtpStatus, SETTINGS_FIELD_LABEL_PROPERTY) == nullptr,
                "synchronization status retains its separate multiline layout");
            ShowWindow(hGeneralPage, SW_SHOW);
            TabCtrl_SetCurSel(hTabs, 0);
            std::vector<HWND> order = GetSettingsTabOrder();
            Check(std::find(order.begin(), order.end(), hNameEdit) != order.end(),
                "native edit remains in original settings tab order");
            TextInk nameInk = ReadInk(hNameEdit, false);
            for (HWND label = GetWindow(hGeneralPage, GW_CHILD);
                    label != nullptr;
                    label = GetWindow(label, GW_HWNDNEXT)) {
                if (GetPropW(label, SETTINGS_FIELD_LABEL_PROPERTY) == hNameEdit) {
                    CheckBaseline(nameInk, label, "complete settings Name field baseline");
                }
            }
        }
    }
}

/// Verifies Application baselines, fixed left anchors, and a linked slider through font and theme changes.
static void TestApplicationRowFonts() {
    const wchar_t* const faces[] = { L"Segoe UI", L"Cambria Math", L"Tahoma", L"Arial", L"Segoe UI" };
    const int weights[] = { FW_NORMAL, FW_BOLD };
    const bool italicStates[] = { false, true };
    const bool classicStates[] = { false, true };
    const HWND anchors[] = {
        hAppFontLabel,
        GetSettingsFieldLabel(hAppAntialiasCombo),
        GetSettingsFieldLabel(hLanguageCombo),
        GetSettingsFieldLabel(hTimeSignalSoundCombo),
        hTimeSignalVolumeLabel,
        hDisableThemesCheck,
        hUseXmlSettingsCheck,
        hSnapToWorkAreaCheck,
        hStartWithWindowsCheck,
        hWarnUnsavedChangesCheck
    };
    std::vector<PositionedControl> anchorPositions;
    for (HWND control : anchors) {
        RECT bounds = FieldBounds(control);
        MapWindowPoints(HWND_DESKTOP, hApplicationPage, reinterpret_cast<POINT*>(&bounds), 2);
        anchorPositions.push_back(PositionedControl{ control, bounds });
    }
    RECT initialSlider = FieldBounds(hTimeSignalVolumeTrackBar);
    MapWindowPoints(HWND_DESKTOP, hApplicationPage, reinterpret_cast<POINT*>(&initialSlider), 2);
    RECT initialValue = FieldBounds(hTimeSignalVolumeValue);
    MapWindowPoints(HWND_DESKTOP, hApplicationPage, reinterpret_cast<POINT*>(&initialValue), 2);
    bool sliderMoved = false;
    for (bool classic : classicStates) {
        themesDisabled = classic;
        SetCheck(hDisableThemesCheck, classic);
        for (const wchar_t* face : faces) {
            for (int weight : weights) {
                for (bool italic : italicStates) {
                    int previousFailures = failures;
                    settingsAppFontFace = face;
                    settingsAppFontWeight = weight;
                    settingsAppFontItalic = italic;
                    ApplyApplicationFontPreview();
                    UpdateApplicationFontButtons();
                    TabCtrl_SetCurSel(hTabs, 5);
                    ShowSettingsTab(5);
                    CheckApplicationRowSpacing();
                    for (const PositionedControl& anchor : anchorPositions) {
                        RECT bounds = FieldBounds(anchor.window);
                        MapWindowPoints(HWND_DESKTOP, hApplicationPage, reinterpret_cast<POINT*>(&bounds), 2);
                        Check(bounds.left == anchor.rect.left && bounds.top == anchor.rect.top,
                            "left Application labels and checkboxes retain their positions through font and theme "
                            "changes");
                    }
                    RECT slider = FieldBounds(hTimeSignalVolumeTrackBar);
                    MapWindowPoints(HWND_DESKTOP, hApplicationPage, reinterpret_cast<POINT*>(&slider), 2);
                    RECT value = FieldBounds(hTimeSignalVolumeValue);
                    MapWindowPoints(HWND_DESKTOP, hApplicationPage, reinterpret_cast<POINT*>(&value), 2);
                    Check(slider.top - initialSlider.top == value.top - initialValue.top,
                        "volume slider follows its value's baseline adjustment through font and theme changes");
                    Check(slider.left == initialSlider.left
                        && slider.right == initialSlider.right
                        && slider.bottom - slider.top == initialSlider.bottom - initialSlider.top,
                        "volume slider baseline adjustment preserves its horizontal position and size");
                    sliderMoved = sliderMoved || slider.top != initialSlider.top;
                    if (failures != previousFailures) {
                        std::printf("  Application font=%ls weight=%d italic=%d classic=%d\n", face, weight, italic,
                            classic);
                    }
                }
            }
        }
    }
    Check(sliderMoved, "font changes exercise the volume slider's baseline adjustment");
}

/// Verifies that native DCs keep the sound fields above the slider and clip expanded labels beneath all three controls.
static void CheckApplicationSliderClipping(bool requireUpperOverlap, bool requireUpperLabel = false) {
    Check(GetTopWindow(hApplicationPage) == hTimeSignalSoundCombo
        && GetWindow(hTimeSignalSoundCombo, GW_HWNDNEXT) == hTimeSignalTestButton
        && GetWindow(hTimeSignalTestButton, GW_HWNDNEXT) == hTimeSignalVolumeTrackBar,
        "Application sound fields stay above the volume slider and expanded labels");
    WINDOWINFO slider = {};
    slider.cbSize = sizeof(slider);
    GetWindowInfo(hTimeSignalVolumeTrackBar, &slider);
    HDC sliderDc = GetDC(hTimeSignalVolumeTrackBar);
    Check(sliderDc != nullptr, "native slider DC is available for clipping checks");
    if (sliderDc == nullptr) {
        return;
    }
    int overlaps = 0;
    int protectedOverlaps = 0;
    int upperLabels = 0;
    for (HWND control = GetWindow(hApplicationPage, GW_CHILD);
            control != nullptr;
            control = GetWindow(control, GW_HWNDNEXT)) {
        if (control == hTimeSignalVolumeTrackBar || !IsWindowVisible(control)) {
            continue;
        }
        WINDOWINFO information = {};
        information.cbSize = sizeof(information);
        GetWindowInfo(control, &information);
        RECT overlap = {};
        if (!IntersectRect(&overlap, &slider.rcClient, &information.rcClient)) {
            continue;
        }
        overlaps++;
        bool protectedField = control == hTimeSignalSoundCombo || control == hTimeSignalTestButton;
        if (protectedField) {
            protectedOverlaps++;
        } else if (information.rcWindow.top < slider.rcWindow.top
                && GetSettingsControlLayer(control) == SETTINGS_CONTROL_LABEL) {
            upperLabels++;
        }
        RECT controlClip = overlap;
        OffsetRect(&controlClip, -information.rcClient.left, -information.rcClient.top);
        HDC controlDc = GetDC(control);
        bool drawable = controlDc != nullptr && RectVisible(controlDc, &controlClip) != FALSE;
        bool correct = controlDc != nullptr && drawable == protectedField;
        Check(correct, "native sound fields remain drawable while labels exclude the slider overlap");
        if (!correct) {
            std::printf("  Application clipping control id=%d protected=%d overlap=%ld,%ld..%ld,%ld\n",
                GetDlgCtrlID(control), protectedField, overlap.left, overlap.top, overlap.right, overlap.bottom);
        }
        if (controlDc != nullptr) {
            ReleaseDC(control, controlDc);
        }
        if (protectedField) {
            OffsetRect(&overlap, -slider.rcClient.left, -slider.rcClient.top);
            Check(!RectVisible(sliderDc, &overlap),
                "native slider DC excludes the sound combo and test button completely");
        }
    }
    RECT client = {};
    GetClientRect(hTimeSignalVolumeTrackBar, &client);
    Check(RectVisible(sliderDc, &client) != FALSE, "volume slider retains its exposed native drawable area");
    ReleaseDC(hTimeSignalVolumeTrackBar, sliderDc);
    Check(overlaps >= 2, "native clipping covers both adjacent volume labels");
    if (requireUpperOverlap) {
        Check(protectedOverlaps == 2, "native clipping preserves both controls in the preceding row");
    }
    if (requireUpperLabel) {
        Check(upperLabels > 0, "Cambria Math upper-row label is clipped beneath the slider");
    }
}

/// Exercises slider clipping against sound fields, labels, and the lower checkbox with Cambria Math and Segoe UI.
static void TestApplicationSliderClipping() {
    RECT initialSlider = FieldBounds(hTimeSignalVolumeTrackBar);
    RECT initialValue = FieldBounds(hTimeSignalVolumeValue);
    LONG valueOffset = initialValue.top - initialSlider.top;
    const wchar_t* const faces[] = { L"Cambria Math", L"Segoe UI" };
    const bool classicStates[] = { false, true };
    const bool enabledStates[] = { true, false };
    for (bool classic : classicStates) {
        themesDisabled = classic;
        SetCheck(hDisableThemesCheck, classic);
        for (const wchar_t* face : faces) {
            int previousFailures = failures;
            settingsAppFontFace = face;
            settingsAppFontWeight = FW_NORMAL;
            settingsAppFontItalic = false;
            SetWindowPos(hTimeSignalTestButton, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
            ApplyApplicationFontPreview();
            UpdateApplicationFontButtons();
            TabCtrl_SetCurSel(hTabs, 5);
            ShowSettingsTab(5);
            RECT slider = FieldBounds(hTimeSignalVolumeTrackBar);
            RECT value = FieldBounds(hTimeSignalVolumeValue);
            Check(value.top - slider.top == valueOffset, "volume slider follows the baseline-aligned volume value");
            for (bool enabled : enabledStates) {
                EnableWindow(hTimeSignalVolumeTrackBar, enabled);
                RedrawWindow(hApplicationPage, nullptr, nullptr,
                    RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ALLCHILDREN);
                CheckApplicationSliderClipping(false);
                RECT upper = FieldBounds(hTimeSignalSoundCombo);
                LONG displacement = upper.bottom - slider.top - 2;
                OffsetSettingsControl(hTimeSignalVolumeTrackBar, displacement);
                RedrawWindow(hApplicationPage, nullptr, nullptr,
                    RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ALLCHILDREN);
                CheckApplicationSliderClipping(true, wcscmp(face, L"Cambria Math") == 0);
                OffsetSettingsControl(hTimeSignalVolumeTrackBar, -displacement);
                RECT lower = FieldBounds(hDisableThemesCheck);
                LONG lowerDisplacement = lower.top - slider.bottom + 2;
                OffsetSettingsControl(hTimeSignalVolumeTrackBar, lowerDisplacement);
                RECT movedSlider = FieldBounds(hTimeSignalVolumeTrackBar);
                RECT lowerOverlap = {};
                Check(IntersectRect(&lowerOverlap, &lower, &movedSlider) != FALSE,
                    "native clipping check includes the expanded lower checkbox");
                RedrawWindow(hApplicationPage, nullptr, nullptr,
                    RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ALLCHILDREN);
                CheckApplicationSliderClipping(false);
                OffsetSettingsControl(hTimeSignalVolumeTrackBar, -lowerDisplacement);
            }
            EnableWindow(hTimeSignalVolumeTrackBar, TRUE);
            SetWindowPos(hTimeSignalTestButton, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
            UpdateSettingsTextControlLayout(hApplicationPage);
            CheckApplicationSliderClipping(false);
            if (failures != previousFailures) {
                std::printf("  slider clipping font=%ls classic=%d\n", face, classic);
            }
        }
    }
}

/// Verifies that every native NTP log column fits the text of every row currently displayed.
static void CheckNtpLogContentWidths() {
    int rows = ListView_GetItemCount(hNtpLogList);
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < 3; column++) {
            wchar_t text[512] = {};
            ListView_GetItemText(hNtpLogList, row, column, text, ARRAYSIZE(text));
            Check(ListView_GetColumnWidth(hNtpLogList, column) >= ListView_GetStringWidth(hNtpLogList, text),
                "NTP log column fits every row in the complete group");
        }
    }
}

/// Checks first-group fitting with an open or hidden Time page, later manual widths, and recreated settings controls.
static void TestFirstNtpLogBatch() {
    const std::vector<NtpQueryLogEntry> originalLog = ntpSynchronizationLog;
    int originalTab = TabCtrl_GetCurSel(hTabs);
    const bool visibleStates[] = { true, false };
    const wchar_t* const servers[] = {
        L"a.test",
        L"second-server-with-a-longer-name.example.test",
        L"third-server-with-the-longest-name-in-the-first-group.example.test"
    };
    const int manualWidths[] = { 71, 83, 97 };
    for (bool visible : visibleStates) {
        ListView_DeleteAllItems(hNtpLogList);
        ntpSynchronizationLog.clear();
        ntpLogColumnsInitialized = false;
        TabCtrl_SetCurSel(hTabs, 4);
        ShowSettingsTab(4);
        Check(ntpLogColumnsInitialized, "empty NTP log has already initialized its header widths");
        for (int column = 0; column < 3; column++) {
            ListView_SetColumnWidth(hNtpLogList, column, manualWidths[column]);
        }
        if (!visible) {
            TabCtrl_SetCurSel(hTabs, 0);
            ShowSettingsTab(0);
        }
        std::vector<NtpQueryLogEntry> group;
        for (const wchar_t* server : servers) {
            NtpQueryLogEntry entry;
            entry.server = server;
            entry.completedTime = 134049600000000000ULL;
            entry.success = true;
            group.push_back(entry);
        }
        group.back().hasCombinedOffset = true;
        AppendNtpSynchronizationLog(group);
        Check(ListView_GetItemCount(hNtpLogList) == 3, "first NTP group appends all three server results");
        if (!visible) {
            Check(!ntpLogColumnsInitialized, "hidden Time page keeps first-group fitting pending");
            TabCtrl_SetCurSel(hTabs, 4);
            ShowSettingsTab(4);
        }
        Check(ntpLogColumnsInitialized, "first complete NTP group refits columns in the open form");
        CheckNtpLogContentWidths();
        for (int column = 0; column < 3; column++) {
            ListView_SetColumnWidth(hNtpLogList, column, manualWidths[column]);
        }
        NtpQueryLogEntry later = group.back();
        later.server += L".another-later-long-server-name.test";
        AppendNtpSynchronizationLog(std::vector<NtpQueryLogEntry>{ later });
        for (int column = 0; column < 3; column++) {
            Check(ListView_GetColumnWidth(hNtpLogList, column) == manualWidths[column],
                "later NTP groups retain manually resized column widths");
        }
        RebuildSettingsControls();
        Check(ListView_GetItemCount(hNtpLogList) == 4 && ntpLogColumnsInitialized,
            "recreated settings restore all NTP rows and refit their columns");
        CheckNtpLogContentWidths();
    }
    ListView_DeleteAllItems(hNtpLogList);
    ntpSynchronizationLog = originalLog;
    for (size_t index = 0; index < ntpSynchronizationLog.size(); index++) {
        InsertNtpLogEntry(ntpSynchronizationLog[index], index);
    }
    ApplyNtpLogSort();
    ntpLogColumnsInitialized = false;
    TabCtrl_SetCurSel(hTabs, originalTab);
    ShowSettingsTab(originalTab);
}

/// Detects any attempt to paint monitor rows through an owner-draw notification.
static LRESULT CALLBACK ObserveMonitorDrawing(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    UNREFERENCED_PARAMETER(referenceData);
    if (message == WM_DRAWITEM && reinterpret_cast<DRAWITEMSTRUCT*>(lParam)->hwndItem == hMonitorList) {
        monitorOwnerDrawMessages++;
    }
    if (message == WM_NCDESTROY) {
        RemoveWindowSubclass(window, ObserveMonitorDrawing, subclassId);
    }
    return DefSubclassProc(window, message, wParam, lParam);
}

/// Finds a displayed monitor row through its stable source index after column sorting.
static int MonitorRowForSource(size_t index) {
    for (int row = 0; row < ListView_GetItemCount(hMonitorList); row++) {
        LVITEMW item = {};
        item.mask = LVIF_PARAM;
        item.iItem = row;
        if (ListView_GetItem(hMonitorList, &item) && static_cast<size_t>(item.lParam) == index) {
            return row;
        }
    }
    return -1;
}

/// Exercises native report sorting, checkbox identity, keyboard commands, initial fitting and reopening.
static void TestMonitorReport() {
    int originalTab = TabCtrl_GetCurSel(hTabs);
    WidgetConfig original = settingsDraft[selectedDraftIndex];
    settingsDraft[selectedDraftIndex].type = WIDGET_FULLSCREEN;
    LoadDraftIntoControls();
    TabCtrl_SetCurSel(hTabs, 0);
    ShowSettingsTab(0);
    wchar_t className[64] = {};
    GetClassNameW(hMonitorList, className, ARRAYSIZE(className));
    Check(wcscmp(className, WC_LISTVIEWW) == 0, "monitor picker uses a native ListView");
    Check((GetWindowLongPtrW(hMonitorList, GWL_STYLE) & LVS_OWNERDRAWFIXED) == 0,
        "monitor rows and checkboxes retain native painting");
    monitorOwnerDrawMessages = 0;
    SetWindowSubclass(hGeneralPage, ObserveMonitorDrawing, ID_MONITOR_LIST, 0);
    Check(Header_GetItemCount(ListView_GetHeader(hMonitorList)) == MONITOR_COLUMN_COUNT,
        "monitor report exposes all eight Flying Solids columns");
    DWORD requiredStyles = LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER;
    Check((ListView_GetExtendedListViewStyle(hMonitorList) & requiredStyles) == requiredStyles,
        "monitor report retains native checkboxes, selection, grid lines and buffering");
    bool previousUpdating = updatingSettingsControls;
    updatingSettingsControls = true;
    ListView_DeleteAllItems(hMonitorList);
    monitorListEntries.clear();
    for (size_t index = 0; index < 3; index++) {
        MonitorListEntry entry = {};
        entry.monitor.device = L"TEST_DISPLAY" + std::to_wstring(index + 1);
        entry.details.refreshRate = DISPLAYCONFIG_RATIONAL{ 60000, 1001 };
        if (index == 1) {
            entry.details.refreshRate = DISPLAYCONFIG_RATIONAL{ 60, 1 };
        } else if (index == 2) {
            entry.details.refreshRate = DISPLAYCONFIG_RATIONAL{ 144, 1 };
        }
        entry.details.bitsPerColor = 8 + static_cast<UINT>(index) * 2;
        entry.text[0] = entry.monitor.device;
        entry.text[1] = index == 1 ? L"Long monitor model used to verify native content fitting" : L"Monitor model";
        entry.text[2] = L"1920 × 1080";
        entry.text[3] = MonitorRefreshRateText(entry.details);
        entry.text[4] = MonitorBitDepthText(entry.details, appLanguage);
        entry.text[5] = L"RGB";
        entry.text[6] = L"sRGB (SDR)";
        entry.text[7] = L"x=0, y=0";
        monitorListEntries.push_back(entry);
        LVITEMW item = {};
        item.mask = LVIF_TEXT | LVIF_PARAM;
        item.iItem = static_cast<int>(index);
        item.pszText = entry.text[0].data();
        item.lParam = static_cast<LPARAM>(index);
        int row = ListView_InsertItem(hMonitorList, &item);
        for (int column = 1; column < MONITOR_COLUMN_COUNT; column++) {
            ListView_SetItemText(hMonitorList, row, column, entry.text[column].data());
        }
        ListView_SetCheckState(hMonitorList, row, index != 1);
    }
    updatingSettingsControls = previousUpdating;
    monitorSortColumn = -1;
    monitorSortAscending = true;
    monitorColumnsInitialized = false;
    InitializeMonitorColumnWidths();
    Check(monitorColumnsInitialized, "populated monitor columns fit on first display");
    Check(ListView_GetColumnWidth(hMonitorList, 1) >= ListView_GetStringWidth(hMonitorList,
        monitorListEntries[1].text[1].c_str()), "initial monitor widths fit the longest model");
    const std::wstring devices = L"TEST_DISPLAY1;TEST_DISPLAY3";
    Check(GetSelectedMonitorDevices() == devices, "checked devices serialize in stable source order");
    HWND monitorList = hMonitorList;
    hMonitorList = nullptr;
    Check(GetSelectedMonitorDevices().empty(), "closed monitor controls cannot return stale device selections");
    hMonitorList = monitorList;
    ListView_SetItemState(hMonitorList, -1, LVIS_SELECTED, LVIS_SELECTED);
    Check(GetSelectedMonitorDevices() == devices, "row selection does not change checked outputs");
    int manualWidths[MONITOR_COLUMN_COUNT] = {};
    for (int column = 0; column < MONITOR_COLUMN_COUNT; column++) {
        manualWidths[column] = 150 + column * 13;
        ListView_SetColumnWidth(hMonitorList, column, manualWidths[column]);
    }
    NMLISTVIEW click = {};
    click.hdr.hwndFrom = hMonitorList;
    click.hdr.idFrom = ID_MONITOR_LIST;
    click.hdr.code = LVN_COLUMNCLICK;
    for (int column = 0; column < MONITOR_COLUMN_COUNT; column++) {
        click.iSubItem = column;
        SendMessageW(hGeneralPage, WM_NOTIFY, ID_MONITOR_LIST, reinterpret_cast<LPARAM>(&click));
        Check(monitorSortColumn == column && monitorSortAscending, "heading click selects ascending monitor sorting");
        if (column == 3 || column == 4) {
            Check(MonitorRowForSource(0) == 0 && MonitorRowForSource(2) == 2,
                "refresh rates and bit depths sort by their numeric values");
        }
        Check(GetSelectedMonitorDevices() == devices, "ascending sorting retains checked monitor identities");
        SendMessageW(hGeneralPage, WM_NOTIFY, ID_MONITOR_LIST, reinterpret_cast<LPARAM>(&click));
        Check(!monitorSortAscending, "second heading click reverses monitor sorting");
        if (column == 3 || column == 4) {
            Check(MonitorRowForSource(2) == 0 && MonitorRowForSource(0) == 2,
                "descending numeric monitor sorting retains fractional refresh rates");
        }
        Check(GetSelectedMonitorDevices() == devices, "descending sorting retains checked monitor identities");
        for (int other = 0; other < MONITOR_COLUMN_COUNT; other++) {
            Check(ListView_GetColumnWidth(hMonitorList, other) == manualWidths[other],
                "monitor sorting preserves every manually adjusted column width");
            HDITEMW header = {};
            header.mask = HDI_FORMAT;
            Header_GetItem(ListView_GetHeader(hMonitorList), other, &header);
            int arrow = other == column ? HDF_SORTDOWN : 0;
            Check((header.fmt & (HDF_SORTUP | HDF_SORTDOWN)) == arrow,
                "only the sorted monitor heading exposes the correct native arrow");
        }
    }
    int row = MonitorRowForSource(0);
    ListView_EnsureVisible(hMonitorList, row, FALSE);
    ListView_Scroll(hMonitorList, -10000, 0);
    ListView_SetCheckState(hMonitorList, row, FALSE);
    FieldImage unchecked = ReadFieldImage(hMonitorList, true);
    ListView_SetCheckState(hMonitorList, row, TRUE);
    FieldImage checked = ReadFieldImage(hMonitorList, true);
    RECT rowBounds = {};
    ListView_GetItemRect(hMonitorList, row, &rowBounds, LVIR_BOUNDS);
    int statePixels = 0;
    int stateX = -1;
    for (int x = 0; x < ListView_GetColumnWidth(hMonitorList, 0); x++) {
        LVHITTESTINFO hit = {};
        hit.pt = POINT{ x, rowBounds.top + (rowBounds.bottom - rowBounds.top) / 2 };
        if (ListView_HitTest(hMonitorList, &hit) == row && (hit.flags & LVHT_ONITEMSTATEICON) != 0) {
            stateX = x;
            for (int y = rowBounds.top; y < rowBounds.bottom; y++) {
                if (y >= 0 && y < checked.height && x < checked.width) {
                    size_t pixel = static_cast<size_t>(y) * checked.width + x;
                    statePixels += checked.pixels[pixel] != unchecked.pixels[pixel];
                }
            }
        }
    }
    Check(statePixels > 0 && stateX >= 0,
        "checked and unchecked native checkbox images are visible inside their hit region");
    NMITEMACTIVATE doubleClick = {};
    doubleClick.hdr.hwndFrom = hMonitorList;
    doubleClick.hdr.idFrom = ID_MONITOR_LIST;
    doubleClick.hdr.code = NM_DBLCLK;
    doubleClick.iItem = row;
    SendMessageW(hGeneralPage, WM_NOTIFY, ID_MONITOR_LIST, reinterpret_cast<LPARAM>(&doubleClick));
    Check(ListView_GetCheckState(hMonitorList, row) == FALSE, "row double-click toggles the native monitor checkbox");
    SendMessageW(hGeneralPage, WM_NOTIFY, ID_MONITOR_LIST, reinterpret_cast<LPARAM>(&doubleClick));
    Check(GetSelectedMonitorDevices() == devices, "second double-click restores the original checked device identities");
    BYTE originalKeyboard[256] = {};
    GetKeyboardState(originalKeyboard);
    BYTE keyboard[256] = {};
    keyboard[VK_CONTROL] = 0x80;
    SetKeyboardState(keyboard);
    SendMessageW(hMonitorList, WM_KEYDOWN, L'A', 0);
    SetKeyboardState(originalKeyboard);
    Check(ListView_GetSelectedCount(hMonitorList) == 3 && GetSelectedMonitorDevices() == devices,
        "Ctrl+A selects monitor rows without changing checked devices");
    InitializeMonitorColumnWidths();
    Check(ListView_GetColumnWidth(hMonitorList, 1) == manualWidths[1],
        "later fitting requests preserve manual monitor widths");
    for (int language = 0; language < LANG_COUNT; language++) {
        for (const wchar_t* heading : MONITOR_COLUMN_LABELS[language]) {
            Check(heading != nullptr && *heading != L'\0',
                "all monitor headings are localized in every application language");
        }
        MonitorDetails details = {};
        details.bitsPerColor = 10;
        Check(MonitorBitDepthText(details, static_cast<AppLanguage>(language)).find(L"10") != std::wstring::npos,
            "localized channel depth formats the actual output value");
    }
    bool originalThemesDisabled = themesDisabled;
    themesDisabled = false;
    SetWindowTheme(hMonitorList, nullptr, nullptr);
    Check(GetSelectedMonitorDevices() == devices, "enabling monitor themes preserves checked device identities");
    themesDisabled = true;
    SetWindowTheme(hMonitorList, L"", L"");
    Check(GetSelectedMonitorDevices() == devices, "disabling monitor themes preserves checked device identities");
    themesDisabled = originalThemesDisabled;
    SetWindowTheme(hMonitorList, themesDisabled ? L"" : nullptr, themesDisabled ? L"" : nullptr);
    for (int index = 3; index < 34; index++) {
        MonitorListEntry entry = monitorListEntries.front();
        entry.monitor.device = L"EXTRA_DISPLAY" + std::to_wstring(index);
        entry.text[0] = entry.monitor.device;
        monitorListEntries.push_back(entry);
        LVITEMW item = {};
        item.mask = LVIF_TEXT | LVIF_PARAM;
        item.iItem = index;
        item.pszText = entry.text[0].data();
        item.lParam = index;
        ListView_InsertItem(hMonitorList, &item);
    }
    UpdateSettingsReportMetrics(hMonitorList);
    Check((GetWindowLongPtrW(hMonitorList, GWL_STYLE) & WS_VSCROLL) != 0,
        "monitor row measurement preserves native vertical scrolling for a long list");
    ListView_EnsureVisible(hMonitorList, 33, FALSE);
    RECT last = {};
    RECT client = {};
    ListView_GetItemRect(hMonitorList, 33, &last, LVIR_BOUNDS);
    GetClientRect(hMonitorList, &client);
    Check(last.top >= client.top && last.bottom <= client.bottom,
        "native monitor scrolling exposes the complete last row");
    ReadFieldImage(hMonitorList, true);
    Check(monitorOwnerDrawMessages == 0, "Windows paints monitor rows without any owner-draw requests");
    Check((GetWindowLongPtrW(hMonitorList, GWL_STYLE) & LVS_OWNERDRAWFIXED) == 0,
        "monitor row measurement always restores native painting");
    RemoveWindowSubclass(hGeneralPage, ObserveMonitorDrawing, ID_MONITOR_LIST);
    RebuildSettingsControls();
    Check(monitorColumnsInitialized && ListView_GetColumnWidth(hMonitorList, 1) != manualWidths[1],
        "reopening settings refits monitor widths to the actual connected displays");
    settingsDraft[selectedDraftIndex] = original;
    LoadDraftIntoControls();
    TabCtrl_SetCurSel(hTabs, originalTab);
    ShowSettingsTab(originalTab);
}

/// Registers the application window procedure and ordinary class styles for native-window rendering tests.
static ATOM RegisterApplicationTestWindowClass() {
    WNDCLASSW windowClass = {};
    windowClass.style = CS_DBLCLKS;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = hInstance;
    windowClass.hIcon = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_CLOCK));
    windowClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    windowClass.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
    windowClass.lpszClassName = CLASS_NAME;
    return RegisterClassW(&windowClass);
}

/// Creates an isolated settings form with no widget windows, no network synchronization, and captured persistence.
/// Can use the application window procedure and ordinary settings-window styles for displayed-frame checks.
static void CreateSettingsCloseTestForm(bool warningEnabled, bool nativeWindow = false) {
    warnOnUnsavedChanges = warningEnabled;
    storageUsesXml = false;
    useNtpTime = false;
    settingsDraft.clear();
    settingsAppliedWidgets.clear();
    selectedDraftIndex = -1;
    settingsAppFontFace = appFontFace;
    settingsAppFontDialogSize = appFontDialogSize;
    settingsAppFontWeight = appFontWeight;
    settingsAppFontItalic = appFontItalic;
    DWORD extendedStyle = nativeWindow ? WS_EX_CONTROLPARENT : WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE;
    DWORD style = 0;
    int width = 0;
    int height = 0;
    GetSettingsWindowLayout(nativeWindow ? extendedStyle : 0, &style, &width, &height);
    if (nativeWindow) {
        Check(RegisterApplicationTestWindowClass() != 0, "application settings-window class registered");
    } else {
        width = settingsContentWidth;
        height = settingsContentHeight;
        style = WS_POPUP;
    }
    const wchar_t* className = nativeWindow ? CLASS_NAME : L"CalClock.SettingsLayoutTest";
    hSettings = CreateWindowExW(extendedStyle, className, T(TXT_SETTINGS), style, 0, 0, width, height, nullptr, nullptr,
        hInstance, nullptr);
    if (!nativeWindow) {
        SetLayeredWindowAttributes(hSettings, 0, 255, LWA_ALPHA);
    }
    Check(CreateSettingsControls(), "isolated settings-close form creation");
    ShowWindow(hSettings, SW_SHOWNOACTIVATE);
    Check(GetCheck(hWarnUnsavedChangesCheck) == warningEnabled, "warning checkbox reflects the applied preference");
    Check(!HasPendingSettingsChanges() && !IsWindowEnabled(GetDlgItem(hSettings, ID_APPLY)),
        "new settings-close form has no pending changes and inactive Apply");
}

/// Exercises actual native dropdown keyboard and mouse notifications without sending input to the user's desktop.
static void CheckSettingsComboCommit(HWND combo) {
    HWND inner = GetSettingsComboBox(combo);
    HWND apply = GetDlgItem(hSettings, ID_APPLY);
    int original = static_cast<int>(SendMessageW(combo, CB_GETCURSEL, 0, 0));
    int count = static_cast<int>(SendMessageW(combo, CB_GETCOUNT, 0, 0));
    Check(original >= 0 && count > 1, "combo commit fixture has multiple items and a current selection");
    if (original < 0 || count < 2) {
        return;
    }
    UINT next = original + 1 < count ? VK_DOWN : VK_UP;
    UINT previous = next == VK_DOWN ? VK_UP : VK_DOWN;
    SendMessageW(combo, CB_SHOWDROPDOWN, TRUE, 0);
    SendMessageW(inner, WM_KEYDOWN, next, 0);
    Check(SendMessageW(combo, CB_GETCURSEL, 0, 0) != original, "native dropdown navigation changes its highlighted item");
    UpdateSettingsApplyButton();
    Check(!IsWindowEnabled(apply), "browsing an open dropdown never activates Apply");
    SendMessageW(inner, WM_KEYDOWN, VK_ESCAPE, 0);
    Check(hSettingsOpenCombo == nullptr
        && SendMessageW(combo, CB_GETCURSEL, 0, 0) == original
        && !IsWindowEnabled(apply)
        && !HasPendingSettingsChanges(),
        "Escape restores the original selection without a pending change");
    SendMessageW(combo, CB_SHOWDROPDOWN, TRUE, 0);
    SendMessageW(inner, WM_KEYDOWN, next, 0);
    SendMessageW(inner, WM_KEYDOWN, previous, 0);
    SendMessageW(inner, WM_KEYDOWN, VK_RETURN, 0);
    Check(!IsWindowEnabled(apply) && !HasPendingSettingsChanges(),
        "confirming the original item after browsing does not create a change");
    SendMessageW(combo, CB_SHOWDROPDOWN, TRUE, 0);
    COMBOBOXINFO information = { sizeof(information) };
    GetComboBoxInfo(inner, &information);
    int chosen = next == VK_DOWN ? original + 1 : original - 1;
    RECT item = {};
    SendMessageW(information.hwndList, LB_GETITEMRECT, chosen, reinterpret_cast<LPARAM>(&item));
    LPARAM point = MAKELPARAM(item.left + 4, item.top + (item.bottom - item.top) / 2);
    SendMessageW(information.hwndList, WM_LBUTTONDOWN, MK_LBUTTON, point);
    Check(!IsWindowEnabled(apply), "mouse selection does not activate Apply before native acceptance and closeup");
    SendMessageW(information.hwndList, WM_LBUTTONUP, 0, point);
    Check(!SendMessageW(combo, CB_GETDROPPEDSTATE, 0, 0)
        && hSettingsOpenCombo == nullptr
        && SendMessageW(combo, CB_GETCURSEL, 0, 0) == chosen
        && IsWindowEnabled(apply),
        "a mouse-confirmed choice activates Apply after the dropdown closes");
    SendMessageW(combo, CB_SHOWDROPDOWN, TRUE, 0);
    SendMessageW(inner, WM_KEYDOWN, previous, 0);
    SendMessageW(inner, WM_KEYDOWN, VK_ESCAPE, 0);
    Check(IsWindowEnabled(apply) && SendMessageW(combo, CB_GETCURSEL, 0, 0) == chosen,
        "cancelling later navigation preserves an already committed pending change");
}

/// Verifies shared dropdown commit handling, dependent controls, closed-list keys, and closure without false save
/// prompts.
static void TestSettingsComboCommit() {
    bool originalWarning = warnOnUnsavedChanges;
    bool originalNtp = useNtpTime;
    bool originalThemes = themesDisabled;
    settingsCloseDialogHook = SetWindowsHookExW(WH_CBT, SettingsCloseDialogHook, nullptr, GetCurrentThreadId());
    Check(settingsCloseDialogHook != nullptr, "combo close-warning observer installed");
    testSettingsDialogResponse = IDCANCEL;
    const bool states[] = { false, true };
    for (bool classic : states) {
        themesDisabled = classic;
        for (int field = 0; field < 3; field++) {
            CreateSettingsCloseTestForm(true, true);
            int tab = field == 0 ? 4 : 5;
            TabCtrl_SetCurSel(hTabs, tab);
            ShowSettingsTab(tab);
            HWND combo = field == 0 ? hTimeSourceCombo : field == 1 ? hLanguageCombo : hAppAntialiasCombo;
            CheckSettingsComboCommit(combo);
            CloseSettingsWindow();
            Check(UnregisterClassW(CLASS_NAME, hInstance) != FALSE, "combo commit form class unregistered");
        }
    }
    CreateSettingsCloseTestForm(true, true);
    TabCtrl_SetCurSel(hTabs, 4);
    ShowSettingsTab(4);
    SendMessageW(hTimeSourceCombo, CB_SHOWDROPDOWN, TRUE, 0);
    SendMessageW(GetSettingsComboBox(hTimeSourceCombo), WM_KEYDOWN, VK_DOWN, 0);
    Check(!IsWindowEnabled(hNtpPresetCombo), "dropdown navigation leaves dependent controls unchanged");
    int questions = testSettingsSaveQuestions;
    RequestCloseSettingsWindow();
    Check(hSettings == nullptr && testSettingsSaveQuestions == questions,
        "closing while browsing an uncommitted dropdown never asks to save");
    CloseSettingsWindow();
    Check(UnregisterClassW(CLASS_NAME, hInstance) != FALSE, "uncommitted combo closure form class unregistered");
    CreateSettingsCloseTestForm(true, true);
    TabCtrl_SetCurSel(hTabs, 4);
    ShowSettingsTab(4);
    SendMessageW(GetSettingsComboBox(hTimeSourceCombo), WM_KEYDOWN, VK_DOWN, 0);
    Check(IsWindowEnabled(GetDlgItem(hSettings, ID_APPLY)) && IsWindowEnabled(hNtpPresetCombo),
        "arrow-key selection in a closed combo commits immediately and updates dependent controls");
    CloseSettingsWindow();
    Check(UnregisterClassW(CLASS_NAME, hInstance) != FALSE, "closed combo keyboard form class unregistered");
    Check(UnhookWindowsHookEx(settingsCloseDialogHook) != FALSE, "combo close-warning observer removed");
    settingsCloseDialogHook = nullptr;
    themesDisabled = originalThemes;
    warnOnUnsavedChanges = originalWarning;
    useNtpTime = originalNtp;
    ResetUiFont();
}

/// Checks actual foreground pixels before and after a background label or checkbox paints during widget selection.
static LRESULT CALLBACK ObserveSettingsTextPaint(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR) {
    std::vector<ProtectedSettingsControl> protectedControls;
    if (observingWidgetSelection && message == WM_PAINT && wParam == 0) {
        RECT bounds = FieldBounds(window);
        bool above = true;
        for (HWND sibling = GetWindow(GetParent(window), GW_CHILD);
                sibling != nullptr;
                sibling = GetWindow(sibling, GW_HWNDNEXT)) {
            if (sibling == window) {
                above = false;
                continue;
            }
            if (IsWindowVisible(sibling) && GetSettingsControlLayer(sibling) == SETTINGS_CONTROL_FOREGROUND) {
                RECT foreground = FieldBounds(sibling);
                RECT overlap = {};
                if (IntersectRect(&overlap, &bounds, &foreground)) {
                    if (!above) {
                        widgetSelectionCoveredControlChanges++;
                    }
                    protectedControls.push_back(ProtectedSettingsControl{ sibling, ReadWindowSurface(sibling, false) });
                }
            }
        }
    }
    LRESULT result = DefSubclassProc(window, message, wParam, lParam);
    for (const ProtectedSettingsControl& control : protectedControls) {
        FieldImage after = ReadWindowSurface(control.window, false);
        for (size_t pixel = 0; pixel < after.pixels.size(); pixel++) {
            if ((after.pixels[pixel] & 0xFFFFFF) != (control.pixels.pixels[pixel] & 0xFFFFFF)) {
                widgetSelectionCoveredControlChanges++;
                break;
            }
        }
    }
    if (message == WM_NCDESTROY) {
        RemoveWindowSubclass(window, ObserveSettingsTextPaint, subclassId);
    }
    return result;
}

/// Observes control updates and intermediate moves, including paints requested after selection loading completes.
/// Rejects redraw suspension and painting of the surrounding form or tab headers during an isolated widget switch.
static LRESULT CALLBACK WidgetSelectionPaintHook(int code, WPARAM wParam, LPARAM lParam) {
    if (code >= 0 && observingWidgetSelection) {
        const CWPSTRUCT* message = reinterpret_cast<const CWPSTRUCT*>(lParam);
        HWND textControl = nullptr;
        HDC textDc = nullptr;
        if (message->message == WM_CTLCOLORBTN || message->message == WM_CTLCOLORSTATIC) {
            textControl = reinterpret_cast<HWND>(message->lParam);
            textDc = reinterpret_cast<HDC>(message->wParam);
        } else if (message->message == WM_DRAWITEM) {
            const DRAWITEMSTRUCT* item = reinterpret_cast<const DRAWITEMSTRUCT*>(message->lParam);
            textControl = item->hwndItem;
            textDc = item->hDC;
        }
        if (textControl != nullptr && GetSettingsControlLayer(textControl) != SETTINGS_CONTROL_FOREGROUND) {
            if (GetObjectType(textDc) == OBJ_MEMDC) {
                widgetSelectionBufferedTextPaints++;
            } else {
                widgetSelectionExposedTextPaints++;
            }
        }
        if (message->message == WM_SHOWWINDOW
                && IsSettingsPageWindow(GetParent(message->hwnd))
                && IsWindowVisible(GetParent(message->hwnd))) {
            widgetSelectionVisibilityEvents++;
            if (message->wParam != 0) {
                widgetSelectionLastReveal = widgetSelectionVisibilityEvents;
                widgetSelectionRevealedControls.push_back(message->hwnd);
            } else {
                if (widgetSelectionFirstHide == 0) {
                    widgetSelectionFirstHide = widgetSelectionVisibilityEvents;
                }
                RECT outgoing = FieldBounds(message->hwnd);
                for (HWND incoming : widgetSelectionRevealedControls) {
                    if (GetParent(incoming) != GetParent(message->hwnd)
                            || GetSettingsControlLayer(incoming) != GetSettingsControlLayer(message->hwnd)) {
                        continue;
                    }
                    RECT replacement = FieldBounds(incoming);
                    RECT overlap = {};
                    if (IntersectRect(&overlap, &outgoing, &replacement)) {
                        bool above = false;
                        for (HWND sibling = GetWindow(message->hwnd, GW_HWNDPREV);
                                sibling != nullptr;
                                sibling = GetWindow(sibling, GW_HWNDPREV)) {
                            above = above || sibling == incoming;
                        }
                        if (!above) {
                            widgetSelectionReplacementOrderFailures++;
                            std::printf("  obscured incoming id=%d outgoing id=%d\n",
                                GetDlgCtrlID(incoming), GetDlgCtrlID(message->hwnd));
                        }
                    }
                }
            }
        }
        bool painting = message->message == WM_PAINT
            || message->message == WM_ERASEBKGND
            || message->message == WM_NCPAINT;
        if (message->hwnd == hSettings || message->hwnd == hTabs) {
            if (message->message == WM_SETREDRAW) {
                widgetSelectionFormRedraws++;
            }
            if (painting) {
                widgetSelectionSurroundingPaints++;
            }
        }
        if (hSettings != nullptr && IsChild(hSettings, message->hwnd) && updatingSettingsControls) {
            bool visible = IsWindowVisible(message->hwnd) != FALSE;
            bool updating = message->message == WM_SETTEXT
                || message->message == CB_SETCURSEL
                || message->message == TBM_SETPOS
                || message->message == BM_SETCHECK
                || message->message == WM_ENABLE
                || message->message == WM_WINDOWPOSCHANGING;
            if (updating && !visible) {
                widgetSelectionHiddenUpdates++;
            }
        }
        if (message->message == WM_WINDOWPOSCHANGED) {
            for (WidgetSelectionControl& control : widgetSelectionControls) {
                if (control.window == message->hwnd) {
                    RECT bounds = {};
                    if (GetWindowRect(control.window, &bounds) && !EqualRect(&control.bounds, &bounds)) {
                        control.bounds = bounds;
                        control.moves++;
                    }
                    break;
                }
            }
        }
    }
    return CallNextHookEx(widgetSelectionPaintHook, code, wParam, lParam);
}

/// Switches a native selection inside an existing redraw batch without allowing nested loading to restore it early.
static void SwitchWidgetInsideRedrawBatch(int index) {
    WindowRedrawScope redraw(hSettings);
    SelectOnlyWidgetIndex(index, false);
    HandleSettingsCommand(ID_LIST_WIDGETS, LBN_SELCHANGE);
    Check(!IsWindowVisible(hSettings), "nested widget loading keeps its caller's redraw batch suspended");
}

/// Records page control geometry before selection, excluding internal windows belonging to native combos and edits.
static void RememberWidgetSelectionControlBounds() {
    widgetSelectionControls.clear();
    const std::vector<HWND>* groups[] = {
        &generalControls,
        &appearanceControls,
        &alarmControls,
        &timeSignalControls,
        &timeControls,
        &applicationControls
    };
    for (const std::vector<HWND>* group : groups) {
        for (HWND window : *group) {
            WidgetSelectionControl control = {};
            control.window = SettingsEdit::GetFrame(window);
            GetWindowRect(control.window, &control.bounds);
            widgetSelectionControls.push_back(control);
        }
    }
}

/// Dispatches normal queued messages without forcing a repaint that could conceal a missing first display.
static void DispatchSettingsPaints() {
    MSG message = {};
    while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&message);
        DispatchMessageW(&message);
    }
    GdiFlush();
}

/// Extracts a control's displayed pixels from a previously captured form without asking the control to paint again.
static FieldImage ExtractDisplayedControl(HWND control, const FieldImage& form) {
    RECT root = FieldBounds(GetAncestor(control, GA_ROOT));
    RECT bounds = FieldBounds(control);
    FieldImage result = { bounds.right - bounds.left, bounds.bottom - bounds.top, {} };
    for (int y = 0; y < result.height; y++) {
        size_t start = static_cast<size_t>(bounds.top - root.top + y) * form.width + bounds.left - root.left;
        result.pixels.insert(result.pixels.end(), form.pixels.begin() + start, form.pixels.begin() + start
            + result.width);
    }
    return result;
}

/// Hashes displayed RGB pixels while ignoring the unused DIB alpha channel.
static ULONGLONG AppearanceFrameHash(const FieldImage& image) {
    ULONGLONG hash = 14695981039346656037ULL;
    for (DWORD pixel : image.pixels) {
        hash ^= pixel & 0xFFFFFF;
        hash *= 1099511628211ULL;
    }
    return hash;
}

/// Captures only the displayed Appearance page without requesting printing or another paint.
static FieldImage ReadDisplayedAppearance() {
    return ExtractDisplayedControl(hAppearancePage, ReadWindowSurface(hSettings, false));
}

/// Samples actual pixels after native mutations and paints, including the final publication of the prepared page.
static LRESULT CALLBACK ObserveAppearanceTransition(int code, WPARAM wParam, LPARAM lParam) {
    if (code >= 0 && observingAppearanceTransition && !capturingAppearanceTransition) {
        const CWPRETSTRUCT* event = reinterpret_cast<const CWPRETSTRUCT*>(lParam);
        const bool appearanceWindow = event->hwnd == hAppearancePage
            || IsChild(hAppearancePage, event->hwnd);
        const bool observedMessage = event->message == WM_PAINT
            || event->message == WM_ERASEBKGND
            || event->message == WM_NCPAINT
            || event->message == WM_WINDOWPOSCHANGED
            || event->message == WM_ENABLE
            || event->message == WM_SETTEXT
            || event->message == WM_SHOWWINDOW
            || event->message == WM_SETREDRAW;
        if (appearanceWindow && observedMessage) {
            capturingAppearanceTransition = true;
            FieldImage frame = ReadDisplayedAppearance();
            ULONGLONG hash = AppearanceFrameHash(frame);
            appearanceTransitionFrames.push_back(AppearanceTransitionFrame{
                hash, event->message, GetDlgCtrlID(event->hwnd), updatingSettingsControls
            });
            if (hash != appearanceTransitionBeforeHash && appearanceTransitionFirstChange.pixels.empty()) {
                appearanceTransitionFirstChange = std::move(frame);
            }
            capturingAppearanceTransition = false;
        }
    }
    return CallNextHookEx(appearanceTransitionHook, code, wParam, lParam);
}

/// Compares displayed headers, rows and scrollbars with native rendering, excluding WM_PRINT's different frame style.
static void CheckDisplayedReport(HWND list, const FieldImage& form, const wchar_t* imageName) {
    FieldImage actual = ExtractDisplayedControl(list, form);
    FieldImage reference = ReadFieldImage(list, true);
    RECT bounds = FieldBounds(list);
    POINT inset = {};
    ClientToScreen(list, &inset);
    inset.x -= bounds.left;
    inset.y -= bounds.top;
    int differences = 0;
    for (int y = inset.y; y < actual.height - inset.y; y++) {
        for (int x = inset.x; x < actual.width - inset.x; x++) {
            size_t pixel = static_cast<size_t>(y) * actual.width + x;
            if ((actual.pixels[pixel] & 0xFFFFFF) != (reference.pixels[pixel] & 0xFFFFFF)) {
                differences++;
            }
        }
    }
    Check(differences == 0, list == hMonitorList
        ? "displayed monitor header, rows and scrollbar match native rendering"
        : "displayed NTP header, rows and scrollbars match native rendering");
    if (differences != 0) {
        std::printf("  report=%d differing displayed pixels=%d\n", GetDlgCtrlID(list), differences);
    }
    SaveFieldComparison(imageName, std::vector<FieldImage>{ actual, reference });
}

/// Checks solid native text pixels in the displayed form, excluding areas covered by higher visible siblings.
static void CheckDisplayedSettingsText(const FieldImage& form, int source) {
    RECT root = FieldBounds(hSettings);
    HWND page = GetActiveSettingsPage();
    for (HWND control = GetWindow(page, GW_CHILD); control != nullptr; control = GetWindow(control, GW_HWNDNEXT)) {
        if (!IsWindowVisible(control) || GetControlText(control).empty() && GetSettingsComboBox(control) == control) {
            continue;
        }
        RECT bounds = FieldBounds(control);
        FieldImage expected = ReadFieldImage(control);
        std::vector<RECT> covered;
        for (HWND sibling = GetWindow(SettingsEdit::GetFrame(control), GW_HWNDPREV);
                sibling != nullptr;
                sibling = GetWindow(sibling, GW_HWNDPREV)) {
            if (IsWindowVisible(sibling)) {
                covered.push_back(FieldBounds(sibling));
            }
        }
        COLORREF color = GetSysColor(IsWindowEnabled(control) ? COLOR_WINDOWTEXT : COLOR_GRAYTEXT);
        DWORD ink = GetRValue(color) << 16 | GetGValue(color) << 8 | GetBValue(color);
        int missing = 0;
        for (int y = 0; y < expected.height; y++) {
            for (int x = 0; x < expected.width; x++) {
                size_t pixel = static_cast<size_t>(y) * expected.width + x;
                if ((expected.pixels[pixel] & 0xFFFFFF) != ink) {
                    continue;
                }
                POINT point = { bounds.left + x, bounds.top + y };
                if (point.x < root.left || point.x >= root.left + form.width
                        || point.y < root.top || point.y >= root.top + form.height) {
                    continue;
                }
                bool obscured = false;
                for (const RECT& rectangle : covered) {
                    obscured = obscured || PtInRect(&rectangle, point);
                }
                if (!obscured) {
                    size_t displayed = static_cast<size_t>(point.y - root.top) * form.width + point.x - root.left;
                    missing += (form.pixels[displayed] & 0xFFFFFF) != ink;
                }
            }
        }
        Check(missing == 0, "visible control text is present in the normally painted form");
        if (missing != 0) {
            int target = settingsDraft[selectedDraftIndex].type;
            std::printf("  missing text pixels=%d control=%d source=%d target=%d caption=%ls\n",
                missing, GetDlgCtrlID(control), source, target, GetControlText(control).c_str());
            wchar_t name[180] = {};
            swprintf_s(name, L"MissingText-%ls-%d-%d-%d-%d.bmp", settingsAppFontFace.c_str(), themesDisabled,
                source, target, GetDlgCtrlID(control));
            SaveFieldComparison(name, std::vector<FieldImage>{ ExtractDisplayedControl(control, form), expected });
        }
    }
}

/// Checks both reports' first displayed images before any WM_PRINT, then repeats tab and widget switches in both fonts.
static void TestDisplayedReports() {
    bool originalThemes = themesDisabled;
    bool originalWarning = warnOnUnsavedChanges;
    const std::vector<NtpQueryLogEntry> originalLog = ntpSynchronizationLog;
    const wchar_t* faces[] = { L"Segoe UI", L"Cambria Math" };
    const bool classicStates[] = { false, true };
    for (bool classic : classicStates) {
        themesDisabled = classic;
        for (const wchar_t* face : faces) {
            ntpSynchronizationLog.clear();
            CreateSettingsCloseTestForm(false);
            settingsDraft.push_back(CreateStoredWidgetDefaults(WIDGET_FULLSCREEN, 1, LANG_CS, FONT_ANTIALIAS_CLEARTYPE));
            settingsDraft.push_back(CreateStoredWidgetDefaults(WIDGET_PANEL, 2, LANG_CS, FONT_ANTIALIAS_CLEARTYPE));
            RefreshWidgetList(false, false);
            selectedDraftIndex = 0;
            SelectOnlyWidgetIndex(0, false);
            settingsAppFontFace = face;
            ApplyApplicationFontPreview();
            LoadDraftIntoControls();
            for (int index = 0; index < 6; index++) {
                NtpQueryLogEntry entry;
                entry.server = L"visible-row.example.test";
                entry.success = true;
                FILETIME now = {};
                GetSystemTimeAsFileTime(&now);
                entry.completedTime = static_cast<ULONGLONG>(now.dwHighDateTime) << 32 | now.dwLowDateTime;
                ntpSynchronizationLog.push_back(entry);
                InsertNtpLogEntry(entry, static_cast<size_t>(index));
            }
            const int tabs[] = { 0, 4, 0, 4, 0 };
            int iteration = 0;
            for (int tab : tabs) {
                if (iteration == 2 || iteration == 4) {
                    SelectOnlyWidgetIndex(iteration == 2 ? 1 : 0, false);
                    HandleSettingsCommand(ID_LIST_WIDGETS, LBN_SELCHANGE);
                }
                TabCtrl_SetCurSel(hTabs, tab);
                ShowSettingsTab(tab);
                DispatchSettingsPaints();
                FieldImage form = ReadWindowSurface(hSettings, false);
                wchar_t name[160] = {};
                swprintf_s(name, L"DisplayedReport-%ls-%d-%d-%d.bmp", face, classic, iteration, tab);
                if (tab == 4 || iteration != 2) {
                    HWND list = tab == 0 ? hMonitorList : hNtpLogList;
                    Check(IsWindowVisible(list) != FALSE && ListView_GetItemCount(list) > 0,
                        "displayed report is visible and contains real records");
                    CheckDisplayedReport(list, form, name);
                }
                iteration++;
            }
            CloseSettingsWindow();
            ResetUiFont();
        }
    }
    ntpSynchronizationLog = originalLog;
    themesDisabled = originalThemes;
    warnOnUnsavedChanges = originalWarning;
}

/// Checks complete displayed frames during every Appearance transition, including background erasure and final paints.
static void TestAppearanceTransitionFrames() {
    bool originalThemes = themesDisabled;
    bool originalNtp = useNtpTime;
    bool originalWarning = warnOnUnsavedChanges;
    CreateSettingsCloseTestForm(false, true);
    for (int type = 0; type < WIDGET_TYPE_COUNT; type++) {
        settingsDraft.push_back(CreateStoredWidgetDefaults(static_cast<WidgetType>(type), type + 1, LANG_CS,
            FONT_ANTIALIAS_CLEARTYPE));
    }
    RefreshWidgetList(false, false);
    selectedDraftIndex = 0;
    SelectOnlyWidgetIndex(0, false);
    LoadDraftIntoControls();
    TabCtrl_SetCurSel(hTabs, 1);
    ShowSettingsTab(1);
    appearanceTransitionHook =
        SetWindowsHookExW(WH_CALLWNDPROCRET, ObserveAppearanceTransition, nullptr, GetCurrentThreadId());
    Check(appearanceTransitionHook != nullptr, "Appearance intermediate-frame observer installed");
    const wchar_t* faces[] = { L"Segoe UI", L"Cambria Math" };
    const bool classicStates[] = { false, true };
    for (bool classic : classicStates) {
        themesDisabled = classic;
        SetCheck(hDisableThemesCheck, classic);
        for (const wchar_t* face : faces) {
            settingsAppFontFace = face;
            ApplyApplicationFontPreview();
            for (int source = 0; source < WIDGET_TYPE_COUNT; source++) {
                for (int target = 0; target < WIDGET_TYPE_COUNT; target++) {
                    SelectOnlyWidgetIndex(source, false);
                    SendMessageW(hSettings, WM_COMMAND, MAKEWPARAM(ID_LIST_WIDGETS, LBN_SELCHANGE),
                        reinterpret_cast<LPARAM>(hWidgetList));
                    DispatchSettingsPaints();
                    SelectOnlyWidgetIndex(target, false);
                    DispatchSettingsPaints();
                    FieldImage before = ReadDisplayedAppearance();
                    appearanceTransitionBeforeHash = AppearanceFrameHash(before);
                    appearanceTransitionFrames.clear();
                    appearanceTransitionFirstChange = FieldImage{};
                    observingAppearanceTransition = true;
                    SendMessageW(hSettings, WM_COMMAND, MAKEWPARAM(ID_LIST_WIDGETS, LBN_SELCHANGE),
                        reinterpret_cast<LPARAM>(hWidgetList));
                    DispatchSettingsPaints();
                    observingAppearanceTransition = false;
                    FieldImage after = ReadDisplayedAppearance();
                    ULONGLONG afterHash = AppearanceFrameHash(after);
                    bool intact = true;
                    bool published = false;
                    for (const AppearanceTransitionFrame& frame : appearanceTransitionFrames) {
                        intact = intact && (frame.loading
                            ? frame.hash == appearanceTransitionBeforeHash
                            : frame.hash == appearanceTransitionBeforeHash || frame.hash == afterHash);
                        if (afterHash != appearanceTransitionBeforeHash && frame.hash == afterHash) {
                            published = true;
                        } else if (published && frame.hash != afterHash) {
                            intact = false;
                        }
                    }
                    Check(!appearanceTransitionFrames.empty() || source == target,
                        "Appearance observer samples real state changes during widget transitions");
                    Check(intact, "Appearance displays only the previous complete image or the completed new image");
                    if (!intact) {
                        std::printf("  partial Appearance frame: source=%d target=%d face=%ls classic=%d\n",
                            source, target, face, classic);
                        wchar_t name[180] = {};
                        swprintf_s(name, L"AppearanceTransition-%ls-%d-%d-%d.bmp", face, classic, source, target);
                        const std::vector<FieldImage> images = { before, appearanceTransitionFirstChange, after };
                        SaveFieldComparison(name, images, 3);
                    }
                    CheckDisplayedSettingsText(ReadWindowSurface(hSettings, false), source);
                }
            }
        }
    }
    Check(UnhookWindowsHookEx(appearanceTransitionHook) != FALSE, "Appearance intermediate-frame observer removed");
    appearanceTransitionHook = nullptr;
    appearanceTransitionFrames.clear();
    appearanceTransitionFirstChange = FieldImage{};
    CloseSettingsWindow();
    Check(UnregisterClassW(CLASS_NAME, hInstance) != FALSE, "application settings-window class unregistered");
    ResetUiFont();
    themesDisabled = originalThemes;
    useNtpTime = originalNtp;
    warnOnUnsavedChanges = originalWarning;
}

/// Verifies widget switches move controls directly into place without redrawing the surrounding form or tab headers.
/// Preserves active pages, hidden forms, and an existing outer redraw batch.
static void TestWidgetSelectionRedraw() {
    bool originalThemes = themesDisabled;
    bool originalNtp = useNtpTime;
    bool originalWarning = warnOnUnsavedChanges;
    CreateSettingsCloseTestForm(false);
    for (int type = 0; type < WIDGET_TYPE_COUNT; type++) {
        WidgetConfig config =
            CreateStoredWidgetDefaults(static_cast<WidgetType>(type), type + 1, LANG_CS, FONT_ANTIALIAS_CLEARTYPE);
        config.name = L"Selection " + std::to_wstring(type);
        settingsDraft.push_back(config);
    }
    RefreshWidgetList(false, false);
    selectedDraftIndex = 0;
    SelectOnlyWidgetIndex(0, false);
    LoadDraftIntoControls();
    widgetSelectionHiddenUpdates = 0;
    widgetSelectionRepeatedMoves = 0;
    widgetSelectionFormRedraws = 0;
    widgetSelectionSurroundingPaints = 0;
    widgetSelectionBufferedTextPaints = 0;
    widgetSelectionExposedTextPaints = 0;
    widgetSelectionCoveredControlChanges = 0;
    widgetSelectionRevealOrderFailures = 0;
    widgetSelectionReplacementOrderFailures = 0;
    const HWND pages[] = { hGeneralPage, hAppearancePage, hAlarmPage, hTimeSignalPage, hTimePage, hApplicationPage };
    for (HWND page : pages) {
        for (HWND control = GetWindow(page, GW_CHILD); control != nullptr; control = GetWindow(control, GW_HWNDNEXT)) {
            if (GetSettingsControlLayer(control) != SETTINGS_CONTROL_FOREGROUND) {
                SetWindowSubclass(control, ObserveSettingsTextPaint, 1, 0);
            }
        }
    }
    widgetSelectionPaintHook = SetWindowsHookExW(WH_CALLWNDPROC, WidgetSelectionPaintHook, nullptr, GetCurrentThreadId());
    Check(widgetSelectionPaintHook != nullptr, "widget selection native-paint observer installed");
    const wchar_t* faces[] = { L"Segoe UI", L"Cambria Math" };
    const bool classicStates[] = { false, true };
    for (bool classic : classicStates) {
        themesDisabled = classic;
        SetCheck(hDisableThemesCheck, classic);
        for (const wchar_t* face : faces) {
            settingsAppFontFace = face;
            ApplyApplicationFontPreview();
            for (int tab = 0; tab < SETTINGS_TAB_COUNT; tab++) {
                TabCtrl_SetCurSel(hTabs, tab);
                ShowSettingsTab(tab);
                for (int index = 0; index < WIDGET_TYPE_COUNT * WIDGET_TYPE_COUNT * 2; index++) {
                    int target = index / 2 / WIDGET_TYPE_COUNT;
                    if (index % 2 != 0) {
                        target = index / 2 % WIDGET_TYPE_COUNT;
                    }
                    SelectOnlyWidgetIndex(target, false);
                    DispatchSettingsPaints();
                    RememberWidgetSelectionControlBounds();
                    widgetSelectionRevealedControls.clear();
                    widgetSelectionVisibilityEvents = 0;
                    widgetSelectionFirstHide = 0;
                    widgetSelectionLastReveal = 0;
                    observingWidgetSelection = true;
                    HandleSettingsCommand(ID_LIST_WIDGETS, LBN_SELCHANGE);
                    Check(selectedDraftIndex == target && GetControlText(hNameEdit) == settingsDraft[target].name,
                        "widget selection displays the completed target configuration");
                    Check(IsWindowVisible(hSettings) && !updatingSettingsControls,
                        "widget selection restores form painting and edit notifications");
                    HWND note = GetDlgItem(hTimeSignalPage, ID_TIME_SIGNAL_NOTE);
                    bool noteVisible = IsWindowVisible(note) != FALSE;
                    bool noteEnabled = IsWindowEnabled(note) != FALSE;
                    Check(noteVisible == (tab == 3) && noteEnabled == WidgetSupportsSound(settingsDraft[target].type),
                        "Greenwich description retains visibility and follows the selected widget's availability");
                    for (int page = 0; page < SETTINGS_TAB_COUNT; page++) {
                        bool visible = IsWindowVisible(GetSettingsPage(page)) != FALSE;
                        Check(visible == (page == tab),
                            "widget selection preserves the active tab and hides every other page");
                    }
                    DispatchSettingsPaints();
                    observingWidgetSelection = false;
                    if (index % 2 != 0) {
                        FieldImage displayed = ReadWindowSurface(hSettings, false);
                        CheckDisplayedSettingsText(displayed, index / 2 / WIDGET_TYPE_COUNT);
                        if (index < WIDGET_TYPE_COUNT * 2) {
                            wchar_t name[180] = {};
                            swprintf_s(name, L"DisplayedSettings-%ls-%d-widget%d-tab%d.bmp", face, classic, target, tab);
                            SaveFieldComparison(name, std::vector<FieldImage>{ displayed }, 1);
                        }
                    }
                    if (widgetSelectionFirstHide != 0 && widgetSelectionLastReveal > widgetSelectionFirstHide) {
                        widgetSelectionRevealOrderFailures++;
                    }
                    for (const WidgetSelectionControl& control : widgetSelectionControls) {
                        if (control.moves > 1 && IsWindowVisible(control.window)) {
                            widgetSelectionRepeatedMoves++;
                        }
                    }
                }
            }
        }
    }
    Check(widgetSelectionReplacementOrderFailures == 0, "incoming controls are above outgoing peers during replacement");
    Check(widgetSelectionRevealOrderFailures == 0, "new controls are revealed before old controls are hidden");
    Check(widgetSelectionCoveredControlChanges == 0,
        "painting background labels and checkboxes never changes overlapping foreground control pixels");
    Check(widgetSelectionBufferedTextPaints > 0 && widgetSelectionExposedTextPaints == 0,
        "changed descriptions and checkboxes draw their backgrounds and text only into local memory DCs");
    if (widgetSelectionExposedTextPaints != 0) {
        std::printf("  exposed text paints=%d buffered text paints=%d\n",
            widgetSelectionExposedTextPaints, widgetSelectionBufferedTextPaints);
    }
    Check(widgetSelectionHiddenUpdates > 0, "widget selection observer sees real native control updates");
    Check(widgetSelectionRepeatedMoves == 0,
        "widget selection places visible controls directly without intermediate moves");
    Check(widgetSelectionFormRedraws == 0, "widget selection never suspends redraw of the form or tab headers");
    Check(widgetSelectionSurroundingPaints == 0, "widget selection never repaints the surrounding form or tab headers");
    if (widgetSelectionRepeatedMoves != 0 || widgetSelectionFormRedraws != 0 || widgetSelectionSurroundingPaints != 0) {
        std::printf("  selection repeated moves=%d, form redraw changes=%d, surrounding paints=%d\n",
            widgetSelectionRepeatedMoves, widgetSelectionFormRedraws, widgetSelectionSurroundingPaints);
    }
    SwitchWidgetInsideRedrawBatch(0);
    Check(IsWindowVisible(hSettings) != FALSE, "outer redraw batch restores the prepared form");
    ShowWindow(hSettings, SW_HIDE);
    SelectOnlyWidgetIndex(1, false);
    LoadDraftIntoControls();
    Check(!IsWindowVisible(hSettings), "loading an initially hidden form never shows it prematurely");
    Check(UnhookWindowsHookEx(widgetSelectionPaintHook) != FALSE, "widget selection native-paint observer removed");
    widgetSelectionPaintHook = nullptr;
    widgetSelectionControls.clear();
    CloseSettingsWindow();
    themesDisabled = originalThemes;
    useNtpTime = originalNtp;
    warnOnUnsavedChanges = originalWarning;
}

/// Verifies default-on, enabled/disabled XML round trips and compatibility with settings saved before the option existed.
static void TestUnsavedSettingsXml() {
    SettingsSnapshot snapshot;
    Check(snapshot.warnOnUnsavedChanges, "unsaved-settings warning defaults to enabled");
    snapshot.widgets.push_back(CreateStoredWidgetDefaults(WIDGET_DIGITAL, 1, LANG_CS, FONT_ANTIALIAS_CLEARTYPE));
    wchar_t executable[MAX_PATH] = {};
    GetModuleFileNameW(nullptr, executable, ARRAYSIZE(executable));
    PathRemoveFileSpecW(executable);
    std::wstring path = std::wstring(executable) + L"/UnsavedSettings.xml";
    const bool states[] = { true, false };
    for (bool enabled : states) {
        snapshot.warnOnUnsavedChanges = enabled;
        SettingsSnapshot loaded;
        Check(WriteSettingsXml(path, snapshot)
            && ReadSettingsXml(path, LANG_CS, CreateStoredWidgetDefaults, &loaded)
            && loaded.warnOnUnsavedChanges == enabled, "warning preference survives settings XML save and load");
    }
    HANDLE file = CreateFileW(path.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL, nullptr);
    Check(file != INVALID_HANDLE_VALUE, "open generated settings XML for legacy-default check");
    if (file == INVALID_HANDLE_VALUE) {
        return;
    }
    DWORD size = GetFileSize(file, nullptr);
    std::string xml(size, '\0');
    DWORD transferred = 0;
    bool read = ReadFile(file, xml.data(), size, &transferred, nullptr) && transferred == size;
    std::string attribute = " warnOnUnsavedChanges=\"0\"";
    size_t position = xml.find(attribute);
    Check(read && position != std::string::npos, "settings XML contains the disabled warning preference");
    if (read && position != std::string::npos) {
        xml.erase(position, attribute.size());
        SetFilePointer(file, 0, nullptr, FILE_BEGIN);
        Check(WriteFile(file, xml.data(), static_cast<DWORD>(xml.size()), &transferred, nullptr)
            && transferred == xml.size()
            && SetEndOfFile(file), "create settings XML without the new warning attribute");
    }
    CloseHandle(file);
    SettingsSnapshot legacy;
    Check(ReadSettingsXml(path, LANG_CS, CreateStoredWidgetDefaults, &legacy) && legacy.warnOnUnsavedChanges,
        "older settings XML keeps the new warning enabled by default");
    Check(DeleteFileW(path.c_str()) != FALSE, "temporary warning settings XML removed");
}

/// Exercises native save questions for Cancel, close, Apply, Save, invalid input, disabled warnings, and application
/// exit.
static void TestUnsavedSettingsClose() {
    CloseSettingsWindow();
    bool originalWarning = warnOnUnsavedChanges;
    bool originalSnap = snapWidgetsToWorkArea;
    bool originalNtp = useNtpTime;
    settingsCloseDialogHook = SetWindowsHookExW(WH_CBT, SettingsCloseDialogHook, nullptr, GetCurrentThreadId());
    Check(settingsCloseDialogHook != nullptr, "native settings-close dialog observer installed");
    if (settingsCloseDialogHook == nullptr) {
        return;
    }
    int questions = testSettingsSaveQuestions;
    CreateSettingsCloseTestForm(true);
    WindowProc(hSettings, WM_CLOSE, 0, 0);
    Check(hSettings == nullptr && testSettingsSaveQuestions == questions, "unchanged settings close without a warning");
    CreateSettingsCloseTestForm(true);
    SetCheck(hSnapToWorkAreaCheck, !snapWidgetsToWorkArea);
    UpdateSettingsApplyButton();
    Check(IsWindowEnabled(GetDlgItem(hSettings, ID_APPLY)), "changing a setting activates Apply");
    int writes = testSettingsWrites;
    testSettingsDialogResponse = IDCANCEL;
    HandleWindowCommand(hSettings, nullptr, MAKEWPARAM(ID_CANCEL, BN_CLICKED), 0);
    Check(hSettings != nullptr && testSettingsSaveQuestions == questions + 1 && testSettingsWrites == writes,
        "Cancel in the native save question keeps the form and draft without saving");
    Check(GetCheck(hSnapToWorkAreaCheck) != snapWidgetsToWorkArea, "canceling closure retains pending input");
    testSettingsDialogResponse = 0;
    WindowProc(hSettings, WM_CLOSE, 0, 0);
    Check(hSettings != nullptr && testSettingsSaveQuestions == questions + 2 && testSettingsWrites == writes,
        "closing the native save question itself leaves settings and pending input open");
    testSettingsDialogResponse = IDNO;
    WindowProc(hSettings, WM_CLOSE, 0, 0);
    Check(hSettings == nullptr
        && snapWidgetsToWorkArea == originalSnap
        && testSavedSettings.snapWidgetsToWorkArea == originalSnap, "No discards unapplied settings before closing");
    questions = testSettingsSaveQuestions;
    CreateSettingsCloseTestForm(true);
    EnableWindow(GetDlgItem(hSettings, ID_APPLY), TRUE);
    testSettingsDialogResponse = IDCANCEL;
    RequestCloseSettingsWindow();
    Check(hSettings != nullptr && testSettingsSaveQuestions == questions + 1,
        "active Apply triggers the warning even after values were reverted");
    testSettingsDialogResponse = IDNO;
    RequestCloseSettingsWindow();
    questions = testSettingsSaveQuestions;
    CreateSettingsCloseTestForm(true);
    SetCheck(hWarnUnsavedChangesCheck, false);
    UpdateSettingsApplyButton();
    testSettingsDialogResponse = IDYES;
    writes = testSettingsWrites;
    WindowProc(hSettings, WM_CLOSE, 0, 0);
    Check(hSettings == nullptr
        && !warnOnUnsavedChanges
        && !testSavedSettings.warnOnUnsavedChanges
        && testSettingsWrites > writes,
        "Yes saves the warning preference through the existing save action before closing");
    Check(testSettingsSaveQuestions == questions + 1, "saving from a warning does not ask again");
    questions = testSettingsSaveQuestions;
    CreateSettingsCloseTestForm(false);
    SetCheck(hSnapToWorkAreaCheck, !snapWidgetsToWorkArea);
    UpdateSettingsApplyButton();
    WindowProc(hSettings, WM_CLOSE, 0, 0);
    Check(hSettings == nullptr && testSettingsSaveQuestions == questions && snapWidgetsToWorkArea == originalSnap,
        "a disabled warning preserves the previous discard-on-close behavior");
    CreateSettingsCloseTestForm(false);
    SetCheck(hWarnUnsavedChangesCheck, true);
    UpdateSettingsApplyButton();
    HandleSettingsCommand(ID_APPLY, BN_CLICKED);
    Check(warnOnUnsavedChanges
        && testSavedSettings.warnOnUnsavedChanges
        && !IsWindowEnabled(GetDlgItem(hSettings, ID_APPLY)),
        "Apply commits the warning preference and becomes inactive");
    WindowProc(hSettings, WM_CLOSE, 0, 0);
    Check(hSettings == nullptr && testSettingsSaveQuestions == questions, "closing after Apply does not show a warning");
    CreateSettingsCloseTestForm(true);
    SetCheck(hSnapToWorkAreaCheck, !snapWidgetsToWorkArea);
    UpdateSettingsApplyButton();
    HandleSettingsCommand(ID_SAVE, BN_CLICKED);
    Check(hSettings == nullptr && testSettingsSaveQuestions == questions && snapWidgetsToWorkArea != originalSnap,
        "explicit Save commits changes and closes without a redundant warning");
    snapWidgetsToWorkArea = originalSnap;
    CreateSettingsCloseTestForm(true);
    WidgetConfig config = CreateStoredWidgetDefaults(WIDGET_DIGITAL, 1, LANG_CS, FONT_ANTIALIAS_CLEARTYPE);
    settingsDraft.push_back(config);
    settingsAppliedWidgets = settingsDraft;
    SendMessageW(hWidgetList, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(config.name.c_str()));
    SendMessageW(hWidgetList, LB_SETITEMDATA, 0, config.id);
    SendMessageW(hWidgetList, LB_SETSEL, TRUE, 0);
    selectedDraftIndex = 0;
    LoadDraftIntoControls();
    SetWindowTextW(hOffsetEdit, L"invalid");
    UpdateSettingsApplyButton();
    writes = testSettingsWrites;
    int validationMessages = testSettingsValidationMessages;
    hController = CreateWindowExW(0, L"CalClock.SettingsLayoutTest", L"", WS_POPUP, 0, 0, 1, 1, nullptr, nullptr,
        hInstance, nullptr);
    Check(hController != nullptr, "isolated invalid-input exit controller created");
    testSettingsDialogResponse = IDYES;
    WindowProc(hController, WM_CLOSE, 0, 0);
    Check(hSettings != nullptr
        && IsWindow(hController)
        && testSettingsWrites == writes
        && testSettingsValidationMessages == validationMessages + 1,
        "invalid input prevents both saving and application exit from Yes");
    testSettingsDialogResponse = IDNO;
    RequestCloseSettingsWindow();
    DestroyWindow(hController);
    hController = nullptr;

    CreateSettingsCloseTestForm(true);
    SetCheck(hSnapToWorkAreaCheck, !snapWidgetsToWorkArea);
    UpdateSettingsApplyButton();
    hController = CreateWindowExW(0, L"CalClock.SettingsLayoutTest", L"", WS_POPUP, 0, 0, 1, 1, nullptr, nullptr,
        hInstance, nullptr);
    Check(hController != nullptr, "isolated application-exit controller created");
    testSettingsDialogResponse = IDCANCEL;
    HandleWindowCommand(hController, nullptr, MAKEWPARAM(ID_MENU_EXIT, 0), 0);
    Check(hSettings != nullptr && IsWindow(hController), "canceling Exit keeps application and settings windows alive");
    testSettingsDialogResponse = IDNO;
    WindowProc(hController, WM_CLOSE, 0, 0);
    Check(hSettings == nullptr && !IsWindow(hController), "controller close discards only after an explicit No");
    hController = nullptr;
    CreateSettingsCloseTestForm(true);
    SetCheck(hSnapToWorkAreaCheck, !snapWidgetsToWorkArea);
    UpdateSettingsApplyButton();
    hController = CreateWindowExW(0, L"CalClock.SettingsLayoutTest", L"", WS_POPUP, 0, 0, 1, 1, nullptr, nullptr,
        hInstance, nullptr);
    Check(hController != nullptr, "isolated save-on-exit controller created");
    testSettingsDialogResponse = IDYES;
    HandleWindowCommand(hController, nullptr, MAKEWPARAM(ID_MENU_EXIT, 0), 0);
    Check(hSettings == nullptr
        && !IsWindow(hController)
        && snapWidgetsToWorkArea != originalSnap
        && testSavedSettings.snapWidgetsToWorkArea != originalSnap,
        "Yes saves pending changes before application Exit destroys either form");
    hController = nullptr;
    Check(UnhookWindowsHookEx(settingsCloseDialogHook) != FALSE, "native settings-close dialog observer removed");
    settingsCloseDialogHook = nullptr;
    warnOnUnsavedChanges = originalWarning;
    snapWidgetsToWorkArea = originalSnap;
    useNtpTime = originalNtp;
    TestUnsavedSettingsXml();
}

/// Observes native time delivery during frame previews without altering the clock's own message handling.
static LRESULT CALLBACK ObservePanelClockTime(int code, WPARAM wParam, LPARAM lParam) {
    if (code >= 0) {
        const CWPSTRUCT* event = reinterpret_cast<const CWPSTRUCT*>(lParam);
        if (event->message == WM_USER + 1 && event->lParam != 0) {
            wchar_t name[64] = {};
            GetClassNameW(event->hwnd, name, ARRAYSIZE(name));
            if (wcscmp(name, L"ClockWndMain") == 0) {
                panelClockTimeWindows.push_back(event->hwnd);
            }
        }
    }
    return CallNextHookEx(panelClockTimeHook, code, wParam, lParam);
}

/// Verifies that every panel row uses its chosen font's full height and restores the original size after a font change.
/// Exercises live previews and all native frames with and without additional clocks and control themes.
static void TestPanelFontSizing() {
    Check(RegisterApplicationTestWindowClass() != 0, "panel font test window class registered");
    panelClockTimeHook = SetWindowsHookExW(WH_CALLWNDPROC, ObservePanelClockTime, nullptr, GetCurrentThreadId());
    Check(panelClockTimeHook != nullptr, "native clock time observer installed");
    bool originalThemes = themesDisabled;
    bool originalSnap = snapWidgetsToWorkArea;
    snapWidgetsToWorkArea = false;
    const bool states[] = { false, true };
    const int sizes[] = { 90, 180 };
    for (bool classic : states) {
        themesDisabled = classic;
        for (bool additional : states) {
            Widget widget;
            widget.config = CreateStoredWidgetDefaults(WIDGET_PANEL, 8100, LANG_CS, FONT_ANTIALIAS_CLEARTYPE);
            widget.config.visible = true;
            widget.config.x = 100;
            widget.config.y = 100;
            widget.config.panelTopFont.face = L"Segoe UI";
            widget.config.panelTimeFont.face = L"Segoe UI";
            widget.config.panelBottomFont.face = L"Segoe UI";
            for (AdditionalClockConfig& clock : widget.config.additionalClocks) {
                clock.enabled = additional;
            }
            CreateWidgetWindow(&widget);
            Check(widget.window != nullptr, "live panel font test window created");
            DispatchSettingsPaints();
            RECT initial = {};
            GetClientRect(widget.window, &initial);
            RECT initialClock = FieldBounds(widget.analogChild);
            RECT initialCalendar = FieldBounds(widget.calendarChild);
            WidgetConfig original = widget.config;
            for (int row = 0; row < 3; row++) {
                for (int size : sizes) {
                    WidgetConfig appearance = original;
                    FontSelection* fonts[] = {
                        &appearance.panelTopFont,
                        &appearance.panelTimeFont,
                        &appearance.panelBottomFont
                    };
                    fonts[row]->face = L"Cambria Math";
                    fonts[row]->dialogSize = size;
                    HFONT font = CreatePanelFont(*fonts[row], appearance.fontAntialiasing);
                    HDC dc = GetDC(nullptr);
                    HGDIOBJ previous = SelectObject(dc, font);
                    TEXTMETRICW metrics = {};
                    Check(GetTextMetricsW(dc, &metrics) != FALSE, "selected panel font metrics measured");
                    SelectObject(dc, previous);
                    ReleaseDC(nullptr, dc);
                    DeleteObject(font);
                    ApplyWidgetAppearancePreview(&widget, appearance, false);
                    DispatchSettingsPaints();
                    RECT tall = {};
                    GetClientRect(widget.window, &tall);
                    Check(tall.bottom > initial.bottom,
                        "each individual tall panel font increases the live client height");
                    PanelLayout layout = CalculatePanelLayout(widget.config);
                    RECT text = row == 1 ? layout.times[0]
                        : FieldBounds(row == 0 ? widget.panelDateLink : widget.panelTimeZoneLink);
                    Check(text.bottom - text.top >= metrics.tmHeight + 4,
                        "the selected panel row retains its full native font height and padding");
                    SYSTEMTIME selected = {};
                    MonthCal_GetCurSel(widget.calendarChild, &selected);
                    selected.wYear = 2031;
                    selected.wMonth = 6;
                    selected.wDay = 17;
                    MonthCal_SetCurSel(widget.calendarChild, &selected);
                    for (int border = 0; border < DIGITAL_BORDER_STYLE_COUNT; border++) {
                        panelClockTimeWindows.clear();
                        appearance.borderStyle = border;
                        ApplyWidgetAppearancePreview(&widget, appearance, false);
                        DispatchSettingsPaints();
                        const HWND clocks[] = {
                            widget.analogChild,
                            widget.additionalAnalogChildren[0],
                            widget.additionalAnalogChildren[1]
                        };
                        for (HWND clock : clocks) {
                            if (clock != nullptr) {
                                Check(std::find(panelClockTimeWindows.begin(), panelClockTimeWindows.end(), clock)
                                    != panelClockTimeWindows.end(),
                                    "every current native clock receives the widget time during its frame update");
                            }
                        }
                        Check((GetWindowLongPtrW(widget.window, GWL_EXSTYLE) & WS_EX_COMPOSITED) == 0,
                            "panel frame updates leave no persistent composited control subtree");
                        SYSTEMTIME currentSelection = {};
                        MonthCal_GetCurSel(widget.calendarChild, &currentSelection);
                        Check(selected.wYear == currentSelection.wYear
                            && selected.wMonth == currentSelection.wMonth
                            && selected.wDay == currentSelection.wDay,
                            "panel frame changes preserve the selected calendar date");
                        RECT client = {};
                        GetClientRect(widget.window, &client);
                        Check(client.right == tall.right && client.bottom == tall.bottom,
                            "frame changes preserve the complete font-dependent panel client size");
                        RECT clock = FieldBounds(widget.analogChild);
                        RECT calendar = FieldBounds(widget.calendarChild);
                        Check(clock.right - clock.left == initialClock.right - initialClock.left
                            && clock.bottom - clock.top == initialClock.bottom - initialClock.top
                            && calendar.right - calendar.left == initialCalendar.right - initialCalendar.left
                            && calendar.bottom - calendar.top == initialCalendar.bottom - initialCalendar.top,
                            "panel text and frame changes preserve the native clock and calendar sizes");
                    }
                    if (size == sizes[0]) {
                        std::wstring name = L"PanelFont-" + std::to_wstring(classic) + L"-"
                            + std::to_wstring(additional) + L"-" + std::to_wstring(row) + L".bmp";
                        SaveFieldComparison(name.c_str(),
                            std::vector<FieldImage>{ ReadWindowSurface(widget.window, false) }, 1);
                    }
                    ApplyWidgetAppearancePreview(&widget, original, false);
                    DispatchSettingsPaints();
                    RECT restored = {};
                    GetClientRect(widget.window, &restored);
                    Check(restored.right == initial.right && restored.bottom == initial.bottom,
                        "restoring a panel row font restores the original live client size");
                }
            }
            DestroyWidgetWindow(&widget);
        }
    }
    UnhookWindowsHookEx(panelClockTimeHook);
    panelClockTimeHook = nullptr;
    themesDisabled = originalThemes;
    snapWidgetsToWorkArea = originalSnap;
    Check(UnregisterClassW(CLASS_NAME, hInstance) != FALSE, "panel font test window class unregistered");
}

/// Compares the entire face against an unmodified native ClockWndMain control.
static void CheckNativePanelClockSurface(HWND actualClock, HWND referenceClock) {
    FieldImage actual = ReadWindowSurface(actualClock, false);
    FieldImage reference = ReadWindowSurface(referenceClock, false);
    int different = 0;
    Check(actual.width == reference.width && actual.height == reference.height, "native reference size matches");
    if (actual.width != reference.width || actual.height != reference.height) {
        return;
    }
    Check(!reference.pixels.empty() && std::any_of(reference.pixels.begin(), reference.pixels.end(),
        [&reference](DWORD pixel) { return (pixel & 0xFFFFFF) != (reference.pixels[0] & 0xFFFFFF); }),
        "native reference contains a painted clock face");
    for (size_t pixel = 0; pixel < actual.pixels.size(); pixel++) {
        if ((actual.pixels[pixel] & 0xFFFFFF) != (reference.pixels[pixel] & 0xFFFFFF)) {
            different++;
        }
    }
    if (different != 0) {
        SaveFieldComparison(L"ClockPainting-native-failure.bmp", std::vector<FieldImage>{ actual, reference });
    }
    Check(different == 0, "the complete face matches the unmodified native control without hand trails or stale "
        "background");
}

/// Exercises initial paint and repeated time changes at every supported native clock size on an isolated desktop.
static void TestNativePanelClockPainting() {
    bool originalThemes = themesDisabled;
    Check(RegisterApplicationTestWindowClass() != 0, "clock erasure test window class registered");
    int sizes[8] = {};
    int count = GetSupportedAnalogClockSizes(sizes, ARRAYSIZE(sizes));
    Check(count > 0, "native clock sizes are available for erasure comparison");
    const bool states[] = { false, true };
    for (bool classic : states) {
        themesDisabled = classic;
        for (int index = 0; index < count; index++) {
            Widget actual;
            Widget reference;
            actual.config = CreateStoredWidgetDefaults(WIDGET_PANEL, 8100, LANG_CS, FONT_ANTIALIAS_CLEARTYPE);
            actual.config.visible = false;
            actual.config.x = 100;
            actual.config.y = 100;
            actual.config.opacity = 99;
            actual.config.size = sizes[index];
            for (AdditionalClockConfig& additional : actual.config.additionalClocks) {
                additional.enabled = true;
                additional.size = sizes[index];
            }
            reference.config = actual.config;
            CreateWidgetWindow(&actual);
            CreateWidgetWindow(&reference);
            Check(SetWindowLongPtrW(reference.analogChild, GWLP_WNDPROC,
                reinterpret_cast<LONG_PTR>(reference.analogProc)) == reinterpret_cast<LONG_PTR>(AnalogChildProc),
                "primary reference restores the unmodified native clock procedure");
            for (int clock = 0; clock < ADDITIONAL_CLOCK_COUNT; clock++) {
                Check(RemoveWindowSubclass(reference.additionalAnalogChildren[clock], AdditionalAnalogChildProc,
                    static_cast<UINT_PTR>(clock) + 1) != FALSE,
                    "additional reference restores the unmodified native clock procedure");
            }
            const HWND actualClocks[] = {
                actual.analogChild,
                actual.additionalAnalogChildren[0],
                actual.additionalAnalogChildren[1]
            };
            const HWND referenceClocks[] = {
                reference.analogChild, reference.additionalAnalogChildren[0],
                reference.additionalAnalogChildren[1]
            };
            actual.config.visible = true;
            reference.config.visible = true;
            ShowWindow(actual.window, SW_SHOWNOACTIVATE);
            ShowWindow(reference.window, SW_SHOWNOACTIVATE);
            RenderWidget(&actual);
            RenderWidget(&reference);
            for (int repeat = 0; repeat < 3; repeat++) {
                for (const SYSTEMTIME& time : panelPaintingTimes) {
                    for (size_t clock = 0; clock < ARRAYSIZE(actualClocks); clock++) {
                        SetAnalogClockTime(actualClocks[clock], time);
                        SetAnalogClockTime(referenceClocks[clock], time);
                        RedrawWindow(actualClocks[clock], nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
                        RedrawWindow(referenceClocks[clock], nullptr, nullptr,
                            RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
                        CheckNativePanelClockSurface(actualClocks[clock], referenceClocks[clock]);
                        HDC target = GetDC(actualClocks[clock]);
                        Check(target != nullptr, "clock erasure target is available");
                        SendMessageW(actualClocks[clock], WM_ERASEBKGND, reinterpret_cast<WPARAM>(target), 0);
                        ReleaseDC(actualClocks[clock], target);
                        CheckNativePanelClockSurface(actualClocks[clock], referenceClocks[clock]);
                    }
                }
            }
            DestroyWidgetWindow(&actual);
            DestroyWidgetWindow(&reference);
        }
    }
    themesDisabled = originalThemes;
    Check(UnregisterClassW(CLASS_NAME, hInstance) != FALSE, "native clock painting test window class unregistered");
}

/// Runs native rendering checks in the application's Common Controls manifest on the isolated test desktop.
static int RunSettingsLayoutTests() {
    hInstance = GetModuleHandleW(nullptr);
    INITCOMMONCONTROLSEX controls = {
        sizeof(controls),
        ICC_WIN95_CLASSES | ICC_DATE_CLASSES | ICC_LINK_CLASS | ICC_USEREX_CLASSES
    };
    InitCommonControlsEx(&controls);
    InitializeLanguageLocales();
    appLanguage = LANG_CS;
    LoadTimeZones();
    Check(IsFontAvailable(L"Cambria Math"), "Cambria Math is installed for the regression test");
    WNDCLASSW windowClass = {};
    windowClass.lpfnWndProc = TestWindowProc;
    windowClass.hInstance = hInstance;
    windowClass.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
    windowClass.lpszClassName = L"CalClock.SettingsLayoutTest";
    RegisterClassW(&windowClass);
    hSettings = CreateWindowExW(WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE, windowClass.lpszClassName, L"",
        WS_POPUP, 0, 0, 1000, 600, nullptr, nullptr, hInstance, nullptr);
    SetLayeredWindowAttributes(hSettings, 0, 255, LWA_ALPHA);
    ShowWindow(hSettings, SW_SHOWNOACTIVATE);
    TestFields();
    DestroyWindow(hSettings);
    hSettings = CreateWindowExW(WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE, windowClass.lpszClassName, L"",
        WS_POPUP, 0, 0, 1000, 600, nullptr, nullptr, hInstance, nullptr);
    SetLayeredWindowAttributes(hSettings, 0, 255, LWA_ALPHA);
    ShowWindow(hSettings, SW_SHOWNOACTIVATE);
    TestCompleteSettings();
    TestApplicationRowFonts();
    TestApplicationSliderClipping();
    TestAdditionalClockNames();
    TestFirstNtpLogBatch();
    TestMonitorReport();
    DestroyWindow(hSettings);
    hSettings = nullptr;
    TestSettingsComboCommit();
    TestUnsavedSettingsClose();
    TestDisplayedReports();
    TestAppearanceTransitionFrames();
    TestWidgetSelectionRedraw();
    TestPanelFontSizing();
    TestNativePanelClockPainting();
    ShutdownAnalogClockHost();
    ResetUiFont();
    std::printf("Settings layout: %d checks, %d failures\n", checks, failures);
    return failures == 0 ? 0 : 1;
}

/// Runs opaque native test windows on a separate desktop and verifies that the user's input desktop is unchanged.
int main(int argc, char** argv) {
    if (argc == 2 && strcmp(argv[1], "--hidden-desktop") == 0) {
        return RunSettingsLayoutTests();
    }
    HDESK input = OpenInputDesktop(0, FALSE, DESKTOP_READOBJECTS);
    wchar_t originalInput[256] = {};
    DWORD needed = 0;
    if (input == nullptr || !GetUserObjectInformationW(input, UOI_NAME, originalInput, sizeof(originalInput), &needed)) {
        if (input != nullptr) {
            CloseDesktop(input);
        }
        std::printf("Cannot identify input desktop: %lu\n", GetLastError());
        return 2;
    }
    CloseDesktop(input);
    wchar_t name[128] = {};
    swprintf_s(name, L"CalClock.SettingsTests.%lu", GetCurrentProcessId());
    HDESK hidden = CreateDesktopW(name, nullptr, nullptr, 0, GENERIC_ALL, nullptr);
    if (hidden == nullptr) {
        std::printf("Cannot create hidden test desktop: %lu\n", GetLastError());
        return 2;
    }
    wchar_t executable[MAX_PATH] = {};
    GetModuleFileNameW(nullptr, executable, ARRAYSIZE(executable));
    std::wstring command = L"\"" + std::wstring(executable) + L"\" --hidden-desktop";
    STARTUPINFOW startup = { sizeof(startup) };
    startup.lpDesktop = name;
    startup.dwFlags = STARTF_USESTDHANDLES;
    startup.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    startup.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    startup.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    PROCESS_INFORMATION process = {};
    int result = 2;
    if (CreateProcessW(executable, command.data(), nullptr, nullptr, TRUE, CREATE_NO_WINDOW,
        nullptr, nullptr, &startup, &process)) {
        WaitForSingleObject(process.hProcess, INFINITE);
        DWORD exitCode = 2;
        GetExitCodeProcess(process.hProcess, &exitCode);
        result = static_cast<int>(exitCode);
        CloseHandle(process.hThread);
        CloseHandle(process.hProcess);
    } else {
        std::printf("Cannot launch hidden desktop tests: %lu\n", GetLastError());
    }
    input = OpenInputDesktop(0, FALSE, DESKTOP_READOBJECTS);
    wchar_t finalInput[256] = {};
    if (input == nullptr
            || !GetUserObjectInformationW(input, UOI_NAME, finalInput, sizeof(finalInput), &needed)
            || wcscmp(originalInput, finalInput) != 0) {
        std::printf("Input desktop identity check failed.\n");
        result = 1;
    }
    if (input != nullptr) {
        CloseDesktop(input);
    }
    if (!CloseDesktop(hidden)) {
        std::printf("Cannot close hidden test desktop: %lu\n", GetLastError());
        result = 1;
    }
    std::printf("Hidden desktop tests finished; input desktop: %ls.\n", finalInput);
    return result;
}
