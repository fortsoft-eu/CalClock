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
 * Last modified for version 1.5.2.0
 */

#include "SelectionEdit.h"
#include <windowsx.h>
#include <commctrl.h>

enum class SelectionUnit {
    None,
    Native,
    Word,
    Line
};

enum class CharacterType {
    Word,
    Space,
    Punctuation,
    LineBreak
};

struct SelectionState {
    wchar_t* text;
    int length;
    int clickCount;
    ULONGLONG clickTime;
    POINT clickPoint;
    POINT mousePoint;
    SelectionUnit unit;
    int anchorStart;
    int anchorEnd;
};

static constexpr UINT_PTR selectionSubclassId = 1003;
static constexpr UINT_PTR selectionScrollTimer = 0xCC02;

/// Clears the private gesture without changing the visible selection.
static void EndSelection(HWND window, SelectionState& state) {
    state.unit = SelectionUnit::None;
    KillTimer(window, selectionScrollTimer);
    if (state.text) {
        HeapFree(GetProcessHeap(), 0, state.text);
        state.text = nullptr;
    }
    if (GetCapture() == window) {
        ReleaseCapture();
    }
}

/// Tests consecutive presses against the system double-click time and rectangle.
static bool ContinuesClickSequence(const SelectionState& state, POINT point, ULONGLONG time) {
    if (state.clickCount == 0 || time - state.clickTime > GetDoubleClickTime()) {
        return false;
    }
    int width = GetSystemMetrics(SM_CXDOUBLECLK);
    int height = GetSystemMetrics(SM_CYDOUBLECLK);
    if (width < 1) {
        width = 1;
    }
    if (height < 1) {
        height = 1;
    }
    RECT area = RECT{
        state.clickPoint.x - width / 2,
        state.clickPoint.y - height / 2,
        state.clickPoint.x - width / 2 + width,
        state.clickPoint.y - height / 2 + height
    };
    return PtInRect(&area, point) != FALSE;
}

/// Snapshots text only for a held word or line gesture, with no runtime-library dependency.
static bool ReadSelectionText(HWND window, SelectionState& state) {
    const int capacity = GetWindowTextLengthW(window);
    const SIZE_T bytes = (static_cast<SIZE_T>(capacity) + 1) * sizeof(wchar_t);
    state.text = static_cast<wchar_t*>(HeapAlloc(GetProcessHeap(), 0, bytes));
    if (!state.text) {
        return false;
    }
    state.length = GetWindowTextW(window, state.text, capacity + 1);
    return true;
}

/// Hit-tests inside the formatting rectangle and restores the edit's full character index.
static int SelectionPosition(HWND window, POINT point) {
    RECT area = RECT{};
    SendMessageW(window, EM_GETRECT, 0, reinterpret_cast<LPARAM>(&area));
    if (area.right <= area.left || area.bottom <= area.top) {
        GetClientRect(window, &area);
    }
    if (point.x < area.left) {
        point.x = area.left;
    }
    if (point.x >= area.right) {
        point.x = area.right > area.left ? area.right - 1 : area.left;
    }
    if (point.y < area.top) {
        point.y = area.top;
    }
    if (point.y >= area.bottom) {
        point.y = area.bottom > area.top ? area.bottom - 1 : area.top;
    }
    const LRESULT hit = SendMessageW(window, EM_CHARFROMPOS, 0, MAKELPARAM(point.x, point.y));
    const int lineStart = static_cast<int>(SendMessageW(window, EM_LINEINDEX, HIWORD(hit), 0));
    if (lineStart < 0) {
        return 0;
    }
    int position = lineStart & ~0xffff | LOWORD(hit);
    if (position < lineStart) {
        position += 0x10000;
    }
    const int length = GetWindowTextLengthW(window);
    return position > length ? length : position;
}

/// Classifies Unicode letters, digits and combining marks separately from spacing and punctuation.
static CharacterType SelectionCharacterType(wchar_t character) {
    if (character == L'\r' || character == L'\n') {
        return CharacterType::LineBreak;
    }
    WORD basic = 0;
    WORD extended = 0;
    GetStringTypeW(CT_CTYPE1, &character, 1, &basic);
    GetStringTypeW(CT_CTYPE3, &character, 1, &extended);
    if (character == L'_' || character >= 0x0300 && character <= 0x036f
            || character >= 0x1ab0 && character <= 0x1aff
            || character >= 0x1dc0 && character <= 0x1dff
            || character >= 0x20d0 && character <= 0x20ff
            || character >= 0xfe20 && character <= 0xfe2f
            || basic & (C1_ALPHA | C1_DIGIT)
            || extended & (C3_NONSPACING | C3_DIACRITIC | C3_VOWELMARK)) {
        return CharacterType::Word;
    }
    if (basic & C1_SPACE) {
        return CharacterType::Space;
    }
    return CharacterType::Punctuation;
}

/// Returns a complete word, spacing run or punctuation run without crossing a line break.
static void SelectionWordBounds(const SelectionState& state, int position, int& start, int& end) {
    start = position;
    end = position;
    if (state.length == 0) {
        return;
    }
    if (position == state.length) {
        --position;
    }
    const CharacterType type = SelectionCharacterType(state.text[position]);
    if (type == CharacterType::LineBreak) {
        return;
    }
    start = position;
    end = position + 1;
    while (start > 0 && SelectionCharacterType(state.text[start - 1]) == type) {
        --start;
    }
    while (end < state.length && SelectionCharacterType(state.text[end]) == type) {
        ++end;
    }
}

/// Returns the entire logical line and excludes only its final CR, LF or CRLF.
static void SelectionLineBounds(const SelectionState& state, int position, int& start, int& end) {
    if (position > 0 && position < state.length && state.text[position] == L'\n' && state.text[position - 1] == L'\r') {
        --position;
    }
    start = position;
    while (start > 0 && state.text[start - 1] != L'\r' && state.text[start - 1] != L'\n') {
        --start;
    }
    end = position;
    while (end < state.length && state.text[end] != L'\r' && state.text[end] != L'\n') {
        ++end;
    }
}

/// Scrolls held selections outside the viewport, including when the pointer remains stationary.
static void ScrollSelection(HWND window, POINT point) {
    RECT area = RECT{};
    SendMessageW(window, EM_GETRECT, 0, reinterpret_cast<LPARAM>(&area));
    if (point.y < area.top) {
        SendMessageW(window, WM_VSCROLL, SB_LINEUP, 0);
        SetTimer(window, selectionScrollTimer, 50, nullptr);
    } else if (point.y >= area.bottom) {
        SendMessageW(window, WM_VSCROLL, SB_LINEDOWN, 0);
        SetTimer(window, selectionScrollTimer, 50, nullptr);
    } else {
        KillTimer(window, selectionScrollTimer);
    }
}

/// Keeps the original unit selected while inside it, and extends from its opposite edge outside it.
static void UpdateSelection(HWND window, SelectionState& state, POINT point, bool scroll) {
    state.mousePoint = point;
    if (scroll) {
        ScrollSelection(window, point);
    }
    const int position = SelectionPosition(window, point);
    if (position >= state.anchorStart && position <= state.anchorEnd) {
        SendMessageW(window, EM_SETSEL, state.anchorStart, state.anchorEnd);
        return;
    }
    int start = 0;
    int end = 0;
    if (state.unit == SelectionUnit::Line) {
        SelectionLineBounds(state, position, start, end);
    } else {
        SelectionWordBounds(state, position, start, end);
    }
    state.clickCount = 0;
    if (position < state.anchorStart) {
        SendMessageW(window, EM_SETSEL, state.anchorEnd, start);
    } else {
        SendMessageW(window, EM_SETSEL, state.anchorStart, end);
    }
}

/// Starts a private word or line gesture without synthesizing a mouse-button release.
static bool BeginSelection(HWND window, SelectionState& state, POINT point) {
    if (!ReadSelectionText(window, state)) {
        return false;
    }
    const int position = SelectionPosition(window, point);
    state.unit = state.clickCount == 3 ? SelectionUnit::Line : SelectionUnit::Word;
    if (state.unit == SelectionUnit::Line) {
        SelectionLineBounds(state, position, state.anchorStart, state.anchorEnd);
    } else {
        SelectionWordBounds(state, position, state.anchorStart, state.anchorEnd);
    }
    state.mousePoint = point;
    SetCapture(window);
    SendMessageW(window, EM_SETSEL, state.anchorStart, state.anchorEnd);
    return true;
}

/// Adds system-sized repeated clicks and anchored selection while preserving native ordinary and modifier gestures.
static LRESULT CALLBACK SelectionEditProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR subclassId,
        DWORD_PTR referenceData) {
    SelectionState& state = *reinterpret_cast<SelectionState*>(referenceData);
    switch (message) {
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
        {
            EndSelection(window, state);
            if (wParam & (MK_SHIFT | MK_CONTROL)) {
                state.clickCount = 0;
                return DefSubclassProc(window, message, wParam, lParam);
            }
            SetFocus(window);
            const POINT point = POINT{
                GET_X_LPARAM(lParam),
                GET_Y_LPARAM(lParam)
            };
            const ULONGLONG time = GetTickCount64();
            if (!ContinuesClickSequence(state, point, time)) {
                state.clickCount = 1;
            } else if (state.clickCount == 2) {
                state.clickCount = 3;
            } else {
                state.clickCount = 2;
            }
            state.clickPoint = point;
            state.clickTime = time;
            if (state.clickCount >= 2 && BeginSelection(window, state, point)) {
                return 0;
            }
            state.unit = SelectionUnit::Native;
            return DefSubclassProc(window, WM_LBUTTONDOWN, wParam, lParam);
        }
        case WM_MOUSEMOVE:
            if (state.unit == SelectionUnit::Word || state.unit == SelectionUnit::Line) {
                if (wParam & MK_LBUTTON) {
                    UpdateSelection(window, state, POINT{
                        GET_X_LPARAM(lParam),
                        GET_Y_LPARAM(lParam)
                    }, true);
                } else {
                    state.clickCount = 0;
                    EndSelection(window, state);
                }
                return 0;
            }
            break;
        case WM_LBUTTONUP:
            if (state.unit == SelectionUnit::Word || state.unit == SelectionUnit::Line) {
                UpdateSelection(window, state, POINT{
                    GET_X_LPARAM(lParam),
                    GET_Y_LPARAM(lParam)
                }, false);
                EndSelection(window, state);
                return 0;
            }
            if (state.unit == SelectionUnit::Native) {
                state.unit = SelectionUnit::None;
                const LRESULT result = DefSubclassProc(window, message, wParam, lParam);
                DWORD start = 0;
                DWORD end = 0;
                SendMessageW(window, EM_GETSEL, reinterpret_cast<WPARAM>(&start), reinterpret_cast<LPARAM>(&end));
                if (start != end) {
                    state.clickCount = 0;
                }
                return result;
            }
            break;
        case WM_TIMER:
            if (wParam == selectionScrollTimer) {
                if (state.unit == SelectionUnit::Word || state.unit == SelectionUnit::Line) {
                    UpdateSelection(window, state, state.mousePoint, true);
                }
                return 0;
            }
            break;
        case WM_CAPTURECHANGED:
            if (reinterpret_cast<HWND>(lParam) != window && state.unit != SelectionUnit::None) {
                state.clickCount = 0;
                EndSelection(window, state);
            }
            break;
        case WM_KEYDOWN:
            state.clickCount = 0;
            EndSelection(window, state);
            if (wParam == L'A' && GetKeyState(VK_CONTROL) & 0x8000) {
                SendMessageW(window, EM_SETSEL, 0, -1);
                return 0;
            }
            break;
        case WM_CHAR:
            if (wParam == 1) {
                SendMessageW(window, EM_SETSEL, 0, -1);
                return 0;
            }
            break;
        case WM_CANCELMODE:
        case WM_KILLFOCUS:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONDBLCLK:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONDBLCLK:
        case WM_XBUTTONDOWN:
        case WM_XBUTTONDBLCLK:
        case WM_SETTEXT:
            state.clickCount = 0;
            EndSelection(window, state);
            break;
        case WM_NCDESTROY:
            EndSelection(window, state);
            RemoveWindowSubclass(window, SelectionEditProc, subclassId);
            HeapFree(GetProcessHeap(), 0, &state);
            break;
    }
    return DefSubclassProc(window, message, wParam, lParam);
}

/// Allocates the text field's independent gesture state.
bool InstallSelectionEditHandler(HWND window) {
    SelectionState* state =
        static_cast<SelectionState*>(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(SelectionState)));
    if (!state) {
        return false;
    }
    if (!SetWindowSubclass(window, SelectionEditProc, selectionSubclassId, reinterpret_cast<DWORD_PTR>(state))) {
        HeapFree(GetProcessHeap(), 0, state);
        return false;
    }
    return true;
}
