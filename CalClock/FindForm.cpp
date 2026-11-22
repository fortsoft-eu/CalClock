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

#include "FindForm.h"
#include "CalClock.h"
#include <locale>
#include <commctrl.h>
#include <uxtheme.h>
#include "SelectionEdit.h"
#include "SystemDialogTemplate.h"
#include "resource.h"

/// Matching flags stored with one search-history entry.
static const DWORD findMatchCase = 0x01;
static const DWORD findBackward = 0x02;
static const DWORD findStartsWith = 0x04;
static const DWORD findEndsWith = 0x08;
static const DWORD findRegularExpression = 0x10;
static const DWORD findWholeWords = 0x20;

/// Returns the native editable combo inside the search-history ComboBoxEx.
static HWND FindHistoryControl(HWND window) {
    return GetSettingsComboBox(GetDlgItem(window, IDC_FIND_TEXT));
}

/// Returns the edit hosted by the search-history ComboBoxEx.
static HWND FindHistoryEdit(HWND window) {
    HWND combo = GetDlgItem(window, IDC_FIND_TEXT);
    return reinterpret_cast<HWND>(SendMessageW(combo, CBEM_GETEDITCONTROL, 0, 0));
}

/// Measures one localized caption with its current native font and mnemonic processing.
static LONG FindCaptionWidth(HWND control) {
    wchar_t* text = CopyControlText(control);
    HDC dc = GetDC(control);
    RECT bounds = RECT{};
    if (text && dc) {
        HGDIOBJ previous = SelectObject(dc, reinterpret_cast<HFONT>(SendMessageW(control, WM_GETFONT, 0, 0)));
        DrawTextW(dc, text, -1, &bounds, DT_CALCRECT | DT_SINGLELINE);
        SelectObject(dc, previous);
    }
    if (dc) {
        ReleaseDC(control, dc);
    }
    if (text) {
        HeapFree(GetProcessHeap(), 0, text);
    }
    return bounds.right - bounds.left;
}

/// Classifies letters, digits, underscores and combining marks as parts of a Unicode word.
static bool IsFindWordCharacter(wchar_t character) {
    if (character == L'_' || IsCharAlphaNumericW(character)) {
        return true;
    }
    WORD type = 0;
    BOOL classified = GetStringTypeW(CT_CTYPE3, &character, 1, &type);
    return classified && type & (C3_NONSPACING | C3_DIACRITIC | C3_VOWELMARK);
}

/// Accepts only a nonempty match delimited by the text edges or native nonword characters.
static bool IsFindWholeWord(const wchar_t* report, int start, int length) {
    return length > 0
        && (!start || !IsFindWordCharacter(report[start - 1]))
        && !IsFindWordCharacter(report[start + length]);
}

/// Compares a literal query and optionally requires complete native Unicode word boundaries.
static bool FindLiteralAt(const wchar_t* report, const wchar_t* query, int start, int length,
        bool wholeWords) {
    for (int index = 0; index < length; ++index) {
        if (report[start + index] != query[index]) {
            return false;
        }
    }
    return !wholeWords || IsFindWholeWord(report, start, length);
}

/// Initializes forward literal searching and an empty thirty-item session history.
FindForm::FindForm()
        : window(nullptr),
        ownerWindow(nullptr),
        target(nullptr),
        lastTarget(nullptr),
        uiFont(nullptr),
        minimumWidth(380),
        fixedHeight(0),
        query(nullptr),
        history(),
        matches(nullptr),
        historyCount(0),
        matchCount(0),
        matchCapacity(0),
        lastMatchStart(-1),
        lastMatchLength(0),
        ownsUiFont(false),
        matchCase(false),
        backward(false),
        wholeWords(false),
        startsWith(false),
        endsWith(false),
        regularExpression(false) {}

/// Closes the form and releases its font, expression, history and match buffers.
FindForm::~FindForm() {
    Close();
    if (ownsUiFont) {
        DeleteObject(uiFont);
    }
    if (query) {
        HeapFree(GetProcessHeap(), 0, query);
    }
    if (matches) {
        HeapFree(GetProcessHeap(), 0, matches);
    }
    for (UINT index = 0; index < historyCount; ++index) {
        HeapFree(GetProcessHeap(), 0, history[index].text);
    }
}

/// Uses the active form's text edit and invalidates the last zero-length match after retargeting.
void FindForm::SetTarget(HWND edit) {
    if (target != edit) {
        lastTarget = nullptr;
        lastMatchStart = -1;
    }
    target = edit;
    if (edit != nullptr) {
        ownerWindow = GetParent(edit);
    }
    UpdateFindButton();
}

/// Refreshes caption icons, applies the system font and recalculates native font- and DPI-aware geometry.
void FindForm::SetFonts(bool updateUi) {
    UpdateApplicationWindowIcons(window, 3);
    HFONT font = updateUi
        ? CreateApplicationUiFont(window)
        : reinterpret_cast<HFONT>(SendMessageW(window, WM_GETFONT, 0, 0));
    if (!font) {
        return;
    }
    if (updateUi) {
        SendMessageW(window, WM_SETFONT, reinterpret_cast<WPARAM>(font), FALSE);
    }
    const wchar_t* theme = themesDisabled && AreVisualStylesActive() ? L"" : nullptr;
    for (HWND control = ::GetWindow(window, GW_CHILD);
            control;
            control = ::GetWindow(control, GW_HWNDNEXT)) {
        SendMessageW(control, WM_SETFONT, reinterpret_cast<WPARAM>(font), TRUE);
        SetWindowTheme(control, theme, theme);
        HWND combo = GetSettingsComboBox(control);
        if (combo != control) {
            SetWindowTheme(combo, theme, theme);
        }
    }
    if (ownsUiFont) {
        DeleteObject(uiFont);
    }
    uiFont = font;
    ownsUiFont = updateUi;
    Layout();
}

/// Measures the minimum width and anchors controls without clipping localized option captions.
void FindForm::Layout() {
    if (!window || IsIconic(window)) {
        return;
    }
    HWND label = GetDlgItem(window, IDC_FIND_LABEL);
    HWND combo = GetDlgItem(window, IDC_FIND_TEXT);
    HWND next = GetDlgItem(window, IDOK);
    HWND close = GetDlgItem(window, IDCANCEL);
    UpdateSettingsComboMetrics(combo);
    SIZE margin = InformationDialogUnits(uiFont, 7, 7);
    LONG top = InformationDialogUnits(uiFont, 0, 6).cy;
    SIZE gap = InformationDialogUnits(uiFont, 4, 3);
    SIZE button = DialogResourceControlSize(IDD_FIND, IDOK, uiFont);
    SIZE closeSize = DialogResourceControlSize(IDD_FIND, IDCANCEL, uiFont);
    button.cx = std::max(button.cx, closeSize.cx);
    UINT dpi = GetSystemDialogDpi(window);
    button.cx = PreferredButtonSize(next, button).cx;
    button.cx = PreferredButtonSize(close, button).cx;
    LONG inputLeft = InformationDialogUnits(uiFont, 50, 0).cx;
    LONG labelWidth = FindCaptionWidth(label);
    if (margin.cx + labelWidth + gap.cx > inputLeft) {
        inputLeft = margin.cx + labelWidth + gap.cx;
    }
    LONG checkLeft = margin.cx;
    LONG firstWidth = InformationDialogUnits(uiFont, 92, 0).cx - checkLeft;
    LONG secondWidth = 0;
    LONG optionHeight = InformationDialogUnits(uiFont, 0, 9).cy;
    const int options[] = {
        IDC_FIND_MATCH_CASE,
        IDC_FIND_BACKWARD,
        IDC_FIND_WHOLE_WORDS,
        IDC_FIND_STARTS_WITH,
        IDC_FIND_ENDS_WITH,
        IDC_FIND_REGEX
    };
    for (int index = 0; index < static_cast<int>(ARRAYSIZE(options)); ++index) {
        SIZE size = PreferredButtonSize(GetDlgItem(window, options[index]), SIZE{ 0, optionHeight });
        if (index < 3 && size.cx + gap.cx > firstWidth) {
            firstWidth = size.cx + gap.cx;
        } else if (index >= 3 && size.cx > secondWidth) {
            secondWidth = size.cx;
        }
        if (size.cy > optionHeight) {
            optionHeight = size.cy;
        }
    }
    RECT bounds = RECT{};
    RECT client = RECT{};
    GetWindowRect(window, &bounds);
    GetClientRect(window, &client);
    LONG frameWidth = bounds.right - bounds.left - client.right;
    LONG frameHeight = bounds.bottom - bounds.top - client.bottom;
    LONG requiredWidth = checkLeft + firstWidth + secondWidth + gap.cx + button.cx + margin.cx;
    LONG inputWidth = inputLeft + InformationDialogUnits(uiFont, 129, 0).cx + gap.cx + button.cx + margin.cx;
    if (inputWidth > requiredWidth) {
        requiredWidth = inputWidth;
    }
    minimumWidth = requiredWidth + frameWidth;
    LONG referenceWidth = MulDiv(380, dpi, 96);
    if (minimumWidth < referenceWidth) {
        minimumWidth = referenceWidth;
    }
    LONG width = bounds.right - bounds.left;
    if (width < minimumWidth) {
        width = minimumWidth;
    }
    LONG rightButton = width - frameWidth - margin.cx - button.cx;
    PlaceControl(label, margin.cx, top, inputLeft - margin.cx - gap.cx, button.cy);
    RECT comboBounds = ControlRect(combo, window);
    PlaceControl(combo, inputLeft, top, rightButton - gap.cx - inputLeft,
        comboBounds.bottom - comboBounds.top);
    UpdateEditMetrics(FindHistoryEdit(window), combo);
    PlaceControl(next, rightButton, top, button.cx, button.cy);
    AlignControlBaseline(label, combo);
    AlignControlBaseline(next, combo);
    RECT textBounds = RECT{};
    ComboBoxTextRect(combo, &textBounds);
    comboBounds = ControlRect(combo, window);
    RECT nextBounds = ControlRect(next, window);
    LONG firstBottom = comboBounds.top + textBounds.bottom + GetSystemMetrics(SM_CYEDGE);
    if (nextBounds.bottom > firstBottom) {
        firstBottom = nextBounds.bottom;
    }
    LONG rowTop = firstBottom + gap.cy;
    LONG step = optionHeight + InformationDialogUnits(uiFont, 0, 1).cy;
    for (int index = 0; index < static_cast<int>(ARRAYSIZE(options)); ++index) {
        LONG left = index < 3 ? checkLeft : checkLeft + firstWidth;
        LONG controlWidth = index < 3 ? firstWidth - gap.cx : rightButton - gap.cx - left;
        PlaceControl(GetDlgItem(window, options[index]), left, rowTop + index % 3 * step,
            controlWidth, optionHeight);
    }
    PlaceControl(close, rightButton, rowTop + 2 * step, button.cx, closeSize.cy);
    AlignControlBaseline(close, GetDlgItem(window, IDC_FIND_WHOLE_WORDS));
    RECT closeBounds = ControlRect(close, window);
    fixedHeight = closeBounds.bottom + margin.cy + frameHeight;
    if (width != bounds.right - bounds.left || fixedHeight != bounds.bottom - bounds.top) {
        SetWindowPos(window, nullptr, 0, 0, width, fixedHeight, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
    }
    GetClientRect(window, &client);
    int gripWidth = GetSystemMetrics(SM_CXVSCROLL);
    int gripHeight = GetSystemMetrics(SM_CYHSCROLL);
    SetWindowPos(GetDlgItem(window, IDC_FIND_GRIP), HWND_BOTTOM,
        client.right - gripWidth, client.bottom - gripHeight, gripWidth, gripHeight,
        SWP_NOACTIVATE | (IsZoomed(window) ? SWP_HIDEWINDOW : SWP_SHOWWINDOW));
}

/// Enables Find Next only when the selected edit contains text and a search expression is available.
void FindForm::UpdateFindButton() const {
    if (!window) {
        return;
    }
    HWND button = GetDlgItem(window, IDOK);
    bool hasText = comboState.open != nullptr
        ? !comboState.initialText.empty()
        : GetWindowTextLengthW(FindHistoryEdit(window)) > 0;
    bool enabled = CanSearch() && hasText;
    if (!enabled && GetFocus() == button) {
        SetFocus(FindHistoryEdit(window));
    }
    EnableWindow(button, enabled);
}

/// Disables whole-word and line-edge options while regular expressions are selected.
void FindForm::UpdateRegexOptions() const {
    bool regex = IsDlgButtonChecked(window, IDC_FIND_REGEX) == BST_CHECKED;
    if (regex) {
        CheckDlgButton(window, IDC_FIND_WHOLE_WORDS, BST_UNCHECKED);
        CheckDlgButton(window, IDC_FIND_STARTS_WITH, BST_UNCHECKED);
        CheckDlgButton(window, IDC_FIND_ENDS_WITH, BST_UNCHECKED);
    }
    EnableWindow(GetDlgItem(window, IDC_FIND_WHOLE_WORDS), !regex);
    EnableWindow(GetDlgItem(window, IDC_FIND_STARTS_WITH), !regex);
    EnableWindow(GetDlgItem(window, IDC_FIND_ENDS_WITH), !regex);
}

/// Returns the six matching options stored with a session history entry.
DWORD FindForm::Options() const {
    return (matchCase ? findMatchCase : 0)
        | (backward ? findBackward : 0)
        | (startsWith ? findStartsWith : 0)
        | (endsWith ? findEndsWith : 0)
        | (regularExpression ? findRegularExpression : 0)
        | (wholeWords ? findWholeWords : 0);
}

/// Restores matching options when a search-history item is selected.
void FindForm::ApplyOptions(DWORD options) const {
    CheckDlgButton(window, IDC_FIND_MATCH_CASE, options & findMatchCase ? BST_CHECKED : BST_UNCHECKED);
    CheckDlgButton(window, IDC_FIND_BACKWARD, options & findBackward ? BST_CHECKED : BST_UNCHECKED);
    CheckDlgButton(window, IDC_FIND_STARTS_WITH, options & findStartsWith ? BST_CHECKED : BST_UNCHECKED);
    CheckDlgButton(window, IDC_FIND_ENDS_WITH, options & findEndsWith ? BST_CHECKED : BST_UNCHECKED);
    CheckDlgButton(window, IDC_FIND_REGEX, options & findRegularExpression ? BST_CHECKED : BST_UNCHECKED);
    CheckDlgButton(window, IDC_FIND_WHOLE_WORDS, options & findWholeWords ? BST_CHECKED : BST_UNCHECKED);
    UpdateRegexOptions();
}

/// Copies pending search text and options, retaining the last query if allocation fails.
bool FindForm::ReadOptions() {
    wchar_t* text = CopyControlText(FindHistoryEdit(window));
    if (!text) {
        return false;
    }
    DWORD previousOptions = Options();
    matchCase = IsDlgButtonChecked(window, IDC_FIND_MATCH_CASE) == BST_CHECKED;
    backward = IsDlgButtonChecked(window, IDC_FIND_BACKWARD) == BST_CHECKED;
    wholeWords = IsDlgButtonChecked(window, IDC_FIND_WHOLE_WORDS) == BST_CHECKED;
    startsWith = IsDlgButtonChecked(window, IDC_FIND_STARTS_WITH) == BST_CHECKED;
    endsWith = IsDlgButtonChecked(window, IDC_FIND_ENDS_WITH) == BST_CHECKED;
    regularExpression = IsDlgButtonChecked(window, IDC_FIND_REGEX) == BST_CHECKED;
    if (!query || lstrcmpW(query, text) || previousOptions != Options()) {
        lastTarget = nullptr;
        lastMatchStart = -1;
    }
    if (query) {
        HeapFree(GetProcessHeap(), 0, query);
    }
    query = text;
    return true;
}

/// Repopulates the editable combo without changing its current text or text selection.
void FindForm::PopulateHistory() const {
    HWND combo = GetDlgItem(window, IDC_FIND_TEXT);
    HWND input = FindHistoryEdit(window);
    DWORD start = 0;
    DWORD end = 0;
    SendMessageW(input, EM_GETSEL, reinterpret_cast<WPARAM>(&start), reinterpret_cast<LPARAM>(&end));
    SendMessageW(combo, CB_RESETCONTENT, 0, 0);
    for (UINT index = 0; index < historyCount; ++index) {
        COMBOBOXEXITEMW item = {};
        item.mask = CBEIF_TEXT;
        item.iItem = -1;
        item.pszText = history[index].text;
        SendMessageW(combo, CBEM_INSERTITEMW, 0, reinterpret_cast<LPARAM>(&item));
    }
    SetWindowTextW(FindHistoryControl(window), query ? query : L"");
    SendMessageW(input, EM_SETSEL, start, end);
    UpdateFindButton();
}

/// Moves the current expression to the front of the bounded session history.
bool FindForm::RememberSearch() {
    SIZE_T bytes = (static_cast<SIZE_T>(lstrlenW(query)) + 1) * sizeof(wchar_t);
    wchar_t* copy = static_cast<wchar_t*>(HeapAlloc(GetProcessHeap(), 0, bytes));
    if (!copy) {
        return false;
    }
    CopyMemory(copy, query, bytes);
    UINT found = 0;
    while (found < historyCount && lstrcmpW(history[found].text, query)) {
        ++found;
    }
    if (found < historyCount) {
        HeapFree(GetProcessHeap(), 0, history[found].text);
        for (UINT index = found + 1; index < historyCount; ++index) {
            history[index - 1] = history[index];
        }
        --historyCount;
    }
    if (historyCount == ARRAYSIZE(history)) {
        HeapFree(GetProcessHeap(), 0, history[--historyCount].text);
    }
    for (UINT index = historyCount; index > 0; --index) {
        history[index] = history[index - 1];
    }
    history[0] = FindHistoryEntry{ copy, Options() };
    ++historyCount;
    if (window) {
        PopulateHistory();
    }
    return true;
}

/// Appends one match while checking process-heap allocation and buffer size limits.
bool FindForm::AddMatch(int start, int length) {
    if (matchCount == matchCapacity) {
        UINT capacity = matchCapacity ? matchCapacity * 2 : 64;
        if (capacity < matchCapacity || capacity > MAXDWORD / sizeof(FindTextMatch)) {
            return false;
        }
        SIZE_T bytes = capacity * sizeof(FindTextMatch);
        void* buffer = matches
            ? HeapReAlloc(GetProcessHeap(), 0, matches, bytes)
            : HeapAlloc(GetProcessHeap(), 0, bytes);
        if (!buffer) {
            return false;
        }
        matches = static_cast<FindTextMatch*>(buffer);
        matchCapacity = capacity;
    }
    matches[matchCount++] = FindTextMatch{ start, length };
    return true;
}

/// Collects literal matches, optionally restricted to the beginning or end of logical lines.
bool FindForm::FindLiteral(wchar_t* report) {
    int length = lstrlenW(query);
    int reportLength = lstrlenW(report);
    SIZE_T bytes = (static_cast<SIZE_T>(length) + 1) * sizeof(wchar_t);
    wchar_t* needle = static_cast<wchar_t*>(HeapAlloc(GetProcessHeap(), 0, bytes));
    if (!needle) {
        return false;
    }
    CopyMemory(needle, query, bytes);
    bool success = true;
    if (!matchCase) {
        success = CharUpperBuffW(report, reportLength) == static_cast<DWORD>(reportLength)
            && CharUpperBuffW(needle, length) == static_cast<DWORD>(length);
    }
    if (success && (startsWith || endsWith)) {
        int first = 0;
        while (success && first < reportLength) {
            int last = first;
            while (last < reportLength && report[last] != L'\r' && report[last] != L'\n') {
                ++last;
            }
            int suffix = last - length;
            bool prefix = startsWith
                && length <= last - first
                && FindLiteralAt(report, needle, first, length, wholeWords);
            if (prefix) {
                success = AddMatch(first, length);
            }
            if (success
                    && endsWith
                    && suffix >= first
                    && (!prefix || suffix != first)
                    && FindLiteralAt(report, needle, suffix, length, wholeWords)) {
                success = AddMatch(suffix, length);
            }
            first = last;
            while (first < reportLength && (report[first] == L'\r' || report[first] == L'\n')) {
                ++first;
            }
        }
    } else if (success) {
        int last = reportLength - length;
        int position = 0;
        while (success && position <= last) {
            if (FindLiteralAt(report, needle, position, length, wholeWords)) {
                success = AddMatch(position, length);
                position += length;
            } else {
                ++position;
            }
        }
    }
    HeapFree(GetProcessHeap(), 0, needle);
    return success;
}

/// Collects native C++ multiline regular-expression matches, including zero-length expressions.
bool FindForm::FindRegex(const wchar_t* report) {
    RegexSearch expression;
    if (!expression.Compile(query, matchCase)) {
        wchar_t message[512];
        wsprintfW(message, T(TXT_FIND_REGEX_ERROR), expression.GetError());
        MessageBoxW(window ? window : ownerWindow, message, PRODUCT_NAME, MB_OK | MB_ICONERROR);
        return false;
    }
    int length = lstrlenW(report);
    int offset = 0;
    while (offset <= length) {
        int start = 0;
        int matched = 0;
        RegexSearchResult result = expression.Next(report, length, offset, &start, &matched);
        if (result == RegexSearchResult::NotFound) {
            return true;
        }
        if (result == RegexSearchResult::Error) {
            wchar_t message[512];
            wsprintfW(message, T(TXT_FIND_REGEX_ERROR), expression.GetError());
            MessageBoxW(window ? window : ownerWindow, message, PRODUCT_NAME, MB_OK | MB_ICONERROR);
            return false;
        }
        if (!AddMatch(start, matched)) {
            MessageBoxW(window ? window : ownerWindow, T(TXT_FIND_FAILED), PRODUCT_NAME,
                MB_OK | MB_ICONERROR);
            return false;
        }
        offset = start + matched;
        if (!matched) {
            if (offset == length) {
                return true;
            }
            bool surrogate = report[offset] >= 0xD800
                && report[offset] <= 0xDBFF
                && offset + 1 < length
                && report[offset + 1] >= 0xDC00
                && report[offset + 1] <= 0xDFFF;
            offset += surrogate ? 2 : 1;
        }
    }
    return true;
}

/// Selects the next or previous collected match, wrapping once at the ends of the report.
void FindForm::SelectMatch(bool reverse) {
    DWORD start = 0;
    DWORD end = 0;
    SendMessageW(target, EM_GETSEL, reinterpret_cast<WPARAM>(&start), reinterpret_cast<LPARAM>(&end));
    bool repeatEmpty = lastTarget == target
        && !lastMatchLength
        && start == end
        && start == static_cast<DWORD>(lastMatchStart);
    UINT selected = 0;
    if (backward != reverse) {
        selected = matchCount - 1;
        for (UINT index = matchCount; index > 0; --index) {
            const FindTextMatch& match = matches[index - 1];
            if (match.start + match.length <= static_cast<int>(start)
                    && !(repeatEmpty && !match.length && match.start == lastMatchStart)) {
                selected = index - 1;
                break;
            }
        }
    } else {
        for (UINT index = 0; index < matchCount; ++index) {
            const FindTextMatch& match = matches[index];
            if (match.start >= static_cast<int>(end)
                    && !(repeatEmpty && !match.length && match.start == lastMatchStart)) {
                selected = index;
                break;
            }
        }
    }
    const FindTextMatch& match = matches[selected];
    lastTarget = target;
    lastMatchStart = match.start;
    lastMatchLength = match.length;
    bool dialogActive = window && GetActiveWindow() == window;
    if (dialogActive) {
        SendMessageW(ownerWindow, findMatchMessage, reinterpret_cast<WPARAM>(GetParent(target)),
            reinterpret_cast<LPARAM>(window));
    } else {
        SetFocus(target);
    }
    SendMessageW(target, EM_SETSEL, match.start, match.start + match.length);
    SendMessageW(target, EM_SCROLLCARET, 0, 0);
}

/// Searches the selected text edit, reversing the selected direction for Find Previous or Shift.
void FindForm::FindNext(HWND owner, bool reverse) {
    if (comboState.open != nullptr) {
        return;
    }
    ownerWindow = owner;
    if (!CanSearch()) {
        SetTarget(nullptr);
        return;
    }
    bool dialogSearch = window && GetActiveWindow() == window;
    if (dialogSearch && !ReadOptions()) {
        MessageBoxW(window, T(TXT_FIND_FAILED), PRODUCT_NAME, MB_OK | MB_ICONERROR);
        return;
    }
    if (!query || !query[0]) {
        Show(ownerWindow);
        return;
    }
    if (dialogSearch) {
        HWND input = FindHistoryEdit(window);
        SetFocus(input);
        SendMessageW(input, EM_SETSEL, 0, -1);
    }
    if (dialogSearch && !RememberSearch()) {
        MessageBoxW(window ? window : ownerWindow, T(TXT_FIND_FAILED), PRODUCT_NAME,
            MB_OK | MB_ICONERROR);
        return;
    }
    wchar_t* report = CopyControlText(target);
    if (!report) {
        MessageBoxW(window ? window : ownerWindow, T(TXT_FIND_FAILED), PRODUCT_NAME,
            MB_OK | MB_ICONERROR);
        return;
    }
    matchCount = 0;
    bool success = regularExpression ? FindRegex(report) : FindLiteral(report);
    HeapFree(GetProcessHeap(), 0, report);
    if (!success) {
        if (!regularExpression) {
            MessageBoxW(window ? window : ownerWindow, T(TXT_FIND_FAILED), PRODUCT_NAME,
                MB_OK | MB_ICONERROR);
        }
    } else if (!matchCount) {
        MessageBoxW(window ? window : ownerWindow, T(TXT_FIND_NOT_FOUND), PRODUCT_NAME,
            MB_OK | MB_ICONINFORMATION);
    } else {
        SelectMatch(reverse);
    }
}

/// Initializes the editable combo, native controls, icons and persisted form placement.
bool FindForm::Initialize() {
    RECT bounds = {};
    HWND input = FindHistoryEdit(window);
    if (!input || !InstallSelectionEditHandler(input)) {
        return false;
    }
    SendMessageW(input, EM_SETLIMITTEXT, 0x7FFFFFFE, 0);
    PopulateHistory();
    ApplyOptions(Options());
    SetFonts(false);
    RefreshLanguage();
    RECT ownerBounds = RECT{};
    if (GetWindowRect(ownerWindow, &ownerBounds) && GetWindowRect(window, &bounds)) {
        int x = ownerBounds.left + (ownerBounds.right - ownerBounds.left - bounds.right + bounds.left) / 2;
        int y = ownerBounds.top + (ownerBounds.bottom - ownerBounds.top - bounds.bottom + bounds.top) / 2;
        SetWindowPos(window, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    }
    placement.SetDetectionOptions(WindowDetectionOptions::NoDetection);
    placement.SetFixHeight(true);
    placement.SetUseWindowsDefaultSize(false);
    placement.SetUseWindowsDefaultLocation(false);
    if (!placement.Attach(window, "FindWindow")) {
        return false;
    }
    Layout();
    UpdateFindButton();
    return true;
}

/// Refreshes all captions and their geometry after a committed interface-language change.
void FindForm::RefreshLanguage() {
    if (!window) {
        return;
    }
    wchar_t title[256];
    wsprintfW(title, T(TXT_FIND_TITLE), PRODUCT_NAME);
    SetWindowTextW(window, title);
    SetDlgItemTextW(window, IDC_FIND_LABEL, T(TXT_FIND_WHAT));
    SetDlgItemTextW(window, IDOK, T(TXT_FIND_NEXT));
    SetDlgItemTextW(window, IDCANCEL, T(TXT_CLOSE));
    SetDlgItemTextW(window, IDC_FIND_MATCH_CASE, T(TXT_FIND_MATCH_CASE));
    SetDlgItemTextW(window, IDC_FIND_BACKWARD, T(TXT_FIND_BACKWARD));
    SetDlgItemTextW(window, IDC_FIND_WHOLE_WORDS, T(TXT_FIND_WHOLE_WORDS));
    SetDlgItemTextW(window, IDC_FIND_STARTS_WITH, T(TXT_FIND_STARTS_WITH));
    SetDlgItemTextW(window, IDC_FIND_ENDS_WITH, T(TXT_FIND_ENDS_WITH));
    SetDlgItemTextW(window, IDC_FIND_REGEX, T(TXT_FIND_REGEX));
    Layout();
}

/// Reports whether the selected edit still exists and contains searchable text.
bool FindForm::CanSearch() const {
    return target && IsWindow(target) && GetWindowTextLengthW(target) > 0;
}

/// Retains logical search state when an existing report edit is replaced for native style changes.
void FindForm::ReplaceTarget(HWND original, HWND replacement) {
    if (target == original) {
        target = replacement;
    }
    if (lastTarget == original) {
        lastTarget = replacement;
    }
}

/// Opens or activates the modeless search form only when its selected edit contains text.
void FindForm::Show(HWND owner) {
    if (!CanSearch()) {
        return;
    }
    ownerWindow = owner;
    if (!window) {
        HINSTANCE instance = GetModuleHandleW(nullptr);
        HFONT font = CreateApplicationUiFont(owner);
        DLGTEMPLATE* definition = LoadSystemDialogTemplate(instance, IDD_FIND, owner, font);
        if (font != nullptr) {
            DeleteObject(font);
        }
        if (!definition) {
            MessageBoxW(owner, T(TXT_FIND_FAILED), PRODUCT_NAME, MB_OK | MB_ICONERROR);
            return;
        }
        HWND created = CreateDialogIndirectParamW(instance, definition, nullptr, DialogProc,
            reinterpret_cast<LPARAM>(this));
        HeapFree(GetProcessHeap(), 0, definition);
        if (!created || !window) {
            MessageBoxW(owner, T(TXT_FIND_FAILED), PRODUCT_NAME, MB_OK | MB_ICONERROR);
            return;
        }
        if (!SendMessageW(ownerWindow, findVisibilityChangedMessage, 0, 0)) {
            Close();
            SendMessageW(ownerWindow, findVisibilityChangedMessage, 0, 0);
            MessageBoxW(owner, T(TXT_FIND_FAILED), PRODUCT_NAME, MB_OK | MB_ICONERROR);
            return;
        }
        ApplyUiStyle(window);
        placement.Show();
    } else {
        placement.BringToFront();
    }
    SetFocus(FindHistoryEdit(window));
    HWND input = FindHistoryEdit(window);
    SendMessageW(input, EM_SETSEL, 0, -1);
}

/// Closes the form while retaining expressions and options only in this running instance.
void FindForm::Close() const {
    if (window) {
        DestroyWindow(window);
    }
}

/// Closes a user-dismissed form and restores ordinary report-selection visibility.
INT_PTR FindForm::HandleClose() const {
    Close();
    if (!SendMessageW(ownerWindow, findVisibilityChangedMessage, 0, 0)) {
        MessageBoxW(ownerWindow, T(TXT_FIND_FAILED), PRODUCT_NAME, MB_OK | MB_ICONERROR);
    }
    return TRUE;
}

/// Restores history options during navigation and selects the text after the choice is committed.
void FindForm::ChooseHistory(bool selectText) const {
    int index = GetApplicationComboSelection(GetDlgItem(window, IDC_FIND_TEXT), comboState);
    if (index >= 0 && static_cast<UINT>(index) < historyCount) {
        ApplyOptions(history[index].options);
        if (selectText) {
            HWND input = FindHistoryEdit(window);
            SetFocus(input);
            SendMessageW(input, EM_SETSEL, 0, -1);
        }
    }
    UpdateFindButton();
}

/// Handles combo notifications, search options, Find Next and Close commands.
INT_PTR FindForm::HandleCommand(WPARAM wParam) {
    HWND combo = GetDlgItem(window, IDC_FIND_TEXT);
    int notification = HIWORD(wParam);
    bool closed = notification == CBN_CLOSEUP;
    if (LOWORD(wParam) == IDC_FIND_TEXT
            && HandleApplicationComboNotification(combo, &notification, comboState)) {
        return TRUE;
    }
    switch (LOWORD(wParam)) {
        case IDOK:
            FindNext(ownerWindow, (GetKeyState(VK_SHIFT) & 0x8000) != 0);
            return TRUE;
        case IDCANCEL:
            return HandleClose();
        case IDC_FIND_TEXT:
            if (notification == CBN_SELCHANGE) {
                ChooseHistory(closed);
            } else if (notification == CBN_EDITCHANGE) {
                UpdateFindButton();
            }
            return TRUE;
        case IDC_FIND_REGEX:
            UpdateRegexOptions();
            return TRUE;
    }
    return FALSE;
}

/// Applies suggested DPI bounds and refreshes native fonts and geometry.
INT_PTR FindForm::HandleDpiChange(LPARAM lParam) {
    RECT* bounds = reinterpret_cast<RECT*>(lParam);
    SetWindowPos(window, nullptr, bounds->left, bounds->top, bounds->right - bounds->left,
        bounds->bottom - bounds->top, SWP_NOZORDER | SWP_NOACTIVATE);
    SetFonts(true);
    return TRUE;
}

/// Supplies the measured minimum width while PersistWindowState fixes the form's height.
INT_PTR FindForm::HandleMinMax(LPARAM lParam) const {
    MINMAXINFO* limits = reinterpret_cast<MINMAXINFO*>(lParam);
    limits->ptMinTrackSize.x = minimumWidth;
    limits->ptMinTrackSize.y = fixedHeight;
    return TRUE;
}

/// Dispatches native modeless form messages without changing the shared selection component.
INT_PTR CALLBACK FindForm::DialogProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    FindForm* owner = reinterpret_cast<FindForm*>(GetWindowLongPtrW(window, DWLP_USER));
    if (message == WM_INITDIALOG) {
        owner = reinterpret_cast<FindForm*>(lParam);
        owner->window = window;
        SetWindowLongPtrW(window, DWLP_USER, reinterpret_cast<LONG_PTR>(owner));
        if (!owner->Initialize()) {
            owner->Close();
            return FALSE;
        }
        return TRUE;
    }
    if (!owner) {
        return FALSE;
    }
    switch (message) {
        case WM_COMMAND:
            return owner->HandleCommand(wParam);
        case WM_HELP:
            SendMessageW(owner->ownerWindow, WM_COMMAND, ID_HELP_CONTENTS, 0);
            return TRUE;
        case WM_CLOSE:
            return owner->HandleClose();
        case WM_SIZE:
            owner->Layout();
            return TRUE;
        case WM_GETMINMAXINFO:
            return owner->HandleMinMax(lParam);
        case WM_SETTINGCHANGE:
        case WM_THEMECHANGED:
        case WM_DISPLAYCHANGE:
            owner->SetFonts(true);
            return TRUE;
        case WM_DPICHANGED:
            return owner->HandleDpiChange(lParam);
        case WM_NCDESTROY:
            ReleaseApplicationWindowIcons(window);
            owner->comboState = ApplicationComboState{};
            owner->window = nullptr;
            break;
    }
    return FALSE;
}

/// Preserves the reference form's Insert overwrite mode through native edit selection.
void FindForm::PrepareOverwrite(MSG* message) const {
    HWND input = FindHistoryEdit(window);
    if (message->message != WM_CHAR || message->hwnd != input || !(GetKeyState(VK_INSERT) & 1)) {
        return;
    }
    wchar_t character = static_cast<wchar_t>(message->wParam);
    WORD type = 0;
    if (!GetStringTypeW(CT_CTYPE1, &character, 1, &type) || type & C1_CNTRL) {
        return;
    }
    DWORD start = 0;
    DWORD end = 0;
    SendMessageW(input, EM_GETSEL, reinterpret_cast<WPARAM>(&start), reinterpret_cast<LPARAM>(&end));
    if (start == end && start < static_cast<DWORD>(GetWindowTextLengthW(input))) {
        SendMessageW(input, EM_SETSEL, start, start + 1);
    }
}

/// Routes search shortcuts and native dialog navigation only for this form and its children.
bool FindForm::Translate(MSG* message) {
    if (!window || message->hwnd != window && !IsChild(window, message->hwnd)) {
        return false;
    }
    if (message->message == WM_KEYDOWN) {
        if (message->wParam == VK_F3
            || message->wParam == VK_RETURN
                && GetFocus() != GetDlgItem(window, IDCANCEL)
                && !SendMessageW(FindHistoryControl(window), CB_GETDROPPEDSTATE, 0, 0)) {
            FindNext(ownerWindow, (GetKeyState(VK_SHIFT) & 0x8000) != 0);
            return true;
        }
        if (message->wParam == L'F' && GetKeyState(VK_CONTROL) & 0x8000) {
            Show(ownerWindow);
            return true;
        }
    }
    PrepareOverwrite(message);
    return IsDialogMessageW(window, message) != FALSE;
}

/// Applies the current application font, theme and native control measurements.
void FindForm::RefreshStyle() {
    if (window != nullptr) {
        ApplyUiStyle(window);
        SetFonts(true);
    }
}

/// Returns this viewer's search form or null when it is closed.
HWND FindForm::GetWindow() const {
    return window;
}

/// Compiles a multiline ECMAScript expression with the requested case sensitivity and localizes failures.
bool RegexSearch::Compile(const wchar_t* pattern, bool matchCase) {
    error.clear();
    try {
        expression.imbue(std::locale(""));
        std::regex_constants::syntax_option_type options =
            std::regex_constants::ECMAScript | std::regex_constants::multiline;
        if (!matchCase) {
            options |= std::regex_constants::icase;
        }
        expression.assign(pattern, options);
        return true;
    } catch (const std::regex_error& failure) {
        SetError(failure.code());
    } catch (const std::exception&) {
        error = T(TXT_REGEX_COMPLEXITY);
    }
    return false;
}

/// Finds the next UTF-16 match at or after the offset, preserving preceding context for expression anchors.
RegexSearchResult RegexSearch::Next(const wchar_t* text, int length, int offset, int* start,
        int* matchLength) {
    if (offset < 0 || offset > length) {
        return RegexSearchResult::NotFound;
    }
    try {
        std::wcmatch match;
        std::regex_constants::match_flag_type flags = std::regex_constants::match_default;
        if (offset > 0) {
            flags |= std::regex_constants::match_prev_avail;
        }
        if (!std::regex_search(text + offset, text + length, match, expression, flags)) {
            return RegexSearchResult::NotFound;
        }
        *start = offset + static_cast<int>(match.position());
        *matchLength = static_cast<int>(match.length());
        return RegexSearchResult::Match;
    } catch (const std::regex_error& failure) {
        SetError(failure.code());
    } catch (const std::exception&) {
        error = T(TXT_REGEX_COMPLEXITY);
    }
    return RegexSearchResult::Error;
}

/// Returns the localized diagnostic from the last failed compilation or match operation.
const wchar_t* RegexSearch::GetError() const {
    return error.c_str();
}

/// Maps native regular-expression error codes to the application's localized diagnostics.
void RegexSearch::SetError(std::regex_constants::error_type code) {
    TextId key = TXT_REGEX_INVALID;
    switch (code) {
        case std::regex_constants::error_escape:
            key = TXT_REGEX_ESCAPE;
            break;
        case std::regex_constants::error_brack:
            key = TXT_REGEX_BRACKET;
            break;
        case std::regex_constants::error_paren:
            key = TXT_REGEX_PARENTHESIS;
            break;
        case std::regex_constants::error_badrepeat:
        case std::regex_constants::error_badbrace:
        case std::regex_constants::error_brace:
            key = TXT_REGEX_REPEAT;
            break;
        case std::regex_constants::error_range:
            key = TXT_REGEX_RANGE;
            break;
        case std::regex_constants::error_space:
        case std::regex_constants::error_stack:
        case std::regex_constants::error_complexity:
            key = TXT_REGEX_COMPLEXITY;
            break;
    }
    error = T(key);
}
