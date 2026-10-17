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
 * Last modified for version 1.6.0.0
 */

#define NOMINMAX
#include "SettingsEdit.h"
#include <algorithm>
#include <commctrl.h>
#include <new>
#include <uxtheme.h>
#include <vssym32.h>

static const wchar_t SETTINGS_EDIT_CLASS[] = L"CalClock.SettingsEdit";
static const wchar_t SETTINGS_EDIT_FRAME_PROPERTY[] = L"CalClock.SettingsEditFrame";
static const UINT_PTR SETTINGS_EDIT_SUBCLASS_ID = 1004;

/// Creates a clipped native single-line edit and retains its native input, selection, caret, and text provider.
HWND SettingsEdit::Create(HINSTANCE instance, HWND parent, DWORD extended, DWORD style, const wchar_t* text, int x, int y,
        int width, int height, int id) {
    WNDCLASSW windowClass = {};
    windowClass.lpfnWndProc = FrameProc;
    windowClass.hInstance = instance;
    windowClass.lpszClassName = SETTINGS_EDIT_CLASS;
    if (RegisterClassW(&windowClass) == 0 && GetLastError() != ERROR_CLASS_ALREADY_EXISTS) {
        return nullptr;
    }
    SettingsEdit* state = new(std::nothrow) SettingsEdit;
    if (state == nullptr) {
        return nullptr;
    }
    HWND frame = CreateWindowExW(extended | WS_EX_CONTROLPARENT, SETTINGS_EDIT_CLASS, L"",
        WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | style & WS_VISIBLE, x, y, width, height,
        parent, reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)), instance, state);
    if (frame == nullptr) {
        delete state;
        return nullptr;
    }
    state->creating = false;
    HWND edit = CreateWindowExW(0, L"EDIT", text, style & ~WS_BORDER, 0, 0, width, height, frame,
        reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)), instance, nullptr);
    state->edit = edit;
    if (edit == nullptr
            || !SetPropW(edit, SETTINGS_EDIT_FRAME_PROPERTY, frame)
            || !SetWindowSubclass(edit, EditProc, SETTINGS_EDIT_SUBCLASS_ID, reinterpret_cast<DWORD_PTR>(state))) {
        if (edit != nullptr) {
            RemovePropW(edit, SETTINGS_EDIT_FRAME_PROPERTY);
        }
        DestroyWindow(frame);
        return nullptr;
    }
    SetWindowTheme(frame, nullptr, L"Edit");
    state->Layout();
    return edit;
}

/// Returns the height-limited visible field rectangle while keeping the public handle on the real native edit.
HWND SettingsEdit::GetFrame(HWND edit) {
    HWND frame = reinterpret_cast<HWND>(GetPropW(edit, SETTINGS_EDIT_FRAME_PROPERTY));
    return frame == nullptr ? edit : frame;
}

/// Resolves an edit frame during settings child enumeration and leaves unrelated controls untouched.
HWND SettingsEdit::GetEdit(HWND frame) {
    wchar_t className[64] = {};
    GetClassNameW(frame, className, ARRAYSIZE(className));
    if (wcscmp(className, SETTINGS_EDIT_CLASS) != 0) {
        return nullptr;
    }
    SettingsEdit* state = reinterpret_cast<SettingsEdit*>(GetWindowLongPtrW(frame, GWLP_USERDATA));
    return state == nullptr ? nullptr : state->edit;
}

/// Recalculates native text placement after a font, field size, or margin change.
void SettingsEdit::UpdateLayout(HWND edit) {
    HWND frame = GetFrame(edit);
    if (frame != edit) {
        SettingsEdit* state = reinterpret_cast<SettingsEdit*>(GetWindowLongPtrW(frame, GWLP_USERDATA));
        if (state != nullptr) {
            state->Layout();
        }
    }
}

/// Centers the native edit's full font line inside a stable clipped viewport, as native buttons center their text.
void SettingsEdit::Layout() const {
    RECT client = {};
    if (edit == nullptr || !GetClientRect(frame, &client)) {
        return;
    }
    LONG height = client.bottom;
    HDC dc = GetDC(edit);
    if (dc != nullptr) {
        HFONT font = reinterpret_cast<HFONT>(SendMessageW(edit, WM_GETFONT, 0, 0));
        HGDIOBJ previous = font == nullptr ? nullptr : SelectObject(dc, font);
        TEXTMETRICW metrics = {};
        if (GetTextMetricsW(dc, &metrics)) {
            height = std::max(1L, metrics.tmHeight);
        }
        if (previous != nullptr && previous != HGDI_ERROR) {
            SelectObject(dc, previous);
        }
        ReleaseDC(edit, dc);
    }
    LONG top = (client.bottom - height) / 2;
    RECT current = {};
    GetWindowRect(edit, &current);
    MapWindowPoints(HWND_DESKTOP, frame, reinterpret_cast<POINT*>(&current), 2);
    if (current.left != 0
            || current.top != top
            || current.right != client.right
            || current.bottom - current.top != height) {
        SetWindowPos(edit, nullptr, 0, top, client.right, height, SWP_NOZORDER | SWP_NOACTIVATE);
    }
}

/// Delegates the border to the native edit-border theme part and preserves the contained EDIT's client area.
bool SettingsEdit::PaintFrame(HDC dc) const {
    HTHEME theme = OpenThemeData(frame, L"Edit");
    if (theme == nullptr) {
        return false;
    }
    WINDOWINFO information = { sizeof(information) };
    bool drawn = false;
    if (GetWindowInfo(frame, &information)) {
        RECT bounds = information.rcWindow;
        OffsetRect(&bounds, -information.rcWindow.left, -information.rcWindow.top);
        RECT client = information.rcClient;
        OffsetRect(&client, -information.rcWindow.left, -information.rcWindow.top);
        int saved = SaveDC(dc);
        ExcludeClipRect(dc, client.left, client.top, client.right, client.bottom);
        int state;
        if (!IsWindowEnabled(edit)) {
            state = EPSN_DISABLED;
        } else if (GetFocus() == edit) {
            state = EPSN_FOCUSED;
        } else if (hot) {
            state = EPSN_HOT;
        } else {
            state = EPSN_NORMAL;
        }
        if (IsThemeBackgroundPartiallyTransparent(theme, EP_EDITBORDER_NOSCROLL, state)) {
            DrawThemeParentBackground(frame, dc, &bounds);
        }
        drawn = SUCCEEDED(DrawThemeBackground(theme, dc, EP_EDITBORDER_NOSCROLL, state, &bounds, nullptr));
        RestoreDC(dc, saved);
    }
    CloseThemeData(theme);
    return drawn;
}

/// Fills the entire viewport with the native edit brush, including the space above and below its text line.
void SettingsEdit::PaintBackground(HDC dc) const {
    RECT client = {};
    GetClientRect(frame, &client);
    int saved = SaveDC(dc);
    bool staticColor = !IsWindowEnabled(edit) || (GetWindowLongPtrW(edit, GWL_STYLE) & ES_READONLY) != 0;
    HBRUSH brush = reinterpret_cast<HBRUSH>(SendMessageW(GetParent(frame),
        staticColor ? WM_CTLCOLORSTATIC : WM_CTLCOLOREDIT, reinterpret_cast<WPARAM>(dc), reinterpret_cast<LPARAM>(edit)));
    if (brush == nullptr) {
        brush = GetSysColorBrush(staticColor ? COLOR_BTNFACE : COLOR_WINDOW);
    }
    FillRect(dc, &client, brush);
    RestoreDC(dc, saved);
}

/// Refreshes the edit border after native focus, hover, read-only, enable, or theme changes.
void SettingsEdit::InvalidateFrame() const {
    RedrawWindow(frame, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_NOCHILDREN);
}

/// Paints the native themed border and retains the default nonclient rendering when no theme can draw it.
LRESULT SettingsEdit::OnNonClientPaint(WPARAM wParam, LPARAM lParam) const {
    HDC dc = GetWindowDC(frame);
    bool painted = dc != nullptr && PaintFrame(dc);
    if (dc != nullptr) {
        ReleaseDC(frame, dc);
    }
    if (painted) {
        return 0;
    }
    return DefWindowProcW(frame, WM_NCPAINT, wParam, lParam);
}

/// Prints the viewport through the default procedure and applies the same border used by nonclient painting.
LRESULT SettingsEdit::OnPrint(WPARAM wParam, LPARAM lParam) const {
    LRESULT result = DefWindowProcW(frame, WM_PRINT, wParam, lParam);
    if ((lParam & PRF_NONCLIENT) != 0) {
        PaintFrame(reinterpret_cast<HDC>(wParam));
    }
    return result;
}

/// Paints the viewport's client background and completes the native paint cycle.
void SettingsEdit::OnPaint() const {
    PAINTSTRUCT paint = {};
    HDC dc = BeginPaint(frame, &paint);
    PaintBackground(dc);
    EndPaint(frame, &paint);
}

/// Tracks the first mouse entry until the native edit reports mouse leave and refreshes the themed border.
void SettingsEdit::OnMouseMove() {
    if (!hot) {
        hot = true;
        TRACKMOUSEEVENT tracking = { sizeof(tracking), TME_LEAVE, edit, 0 };
        TrackMouseEvent(&tracking);
        InvalidateFrame();
    }
}

/// Clears the frame's state pointer and leaves failed-creation cleanup with the caller that allocated the state.
void SettingsEdit::ReleaseFrameState(HWND window, SettingsEdit* state) {
    SetWindowLongPtrW(window, GWLP_USERDATA, 0);
    if (!state->creating) {
        delete state;
    }
}

/// Keeps a stable edit viewport and forwards native notifications and colors to the original settings page.
LRESULT CALLBACK SettingsEdit::FrameProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    SettingsEdit* state = reinterpret_cast<SettingsEdit*>(GetWindowLongPtrW(window, GWLP_USERDATA));
    if (message == WM_NCCREATE) {
        state = static_cast<SettingsEdit*>(reinterpret_cast<CREATESTRUCTW*>(lParam)->lpCreateParams);
        state->frame = window;
        SetWindowLongPtrW(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(state));
    }
    if (state == nullptr) {
        return DefWindowProcW(window, message, wParam, lParam);
    }
    switch (message) {
        case WM_SIZE:
            state->Layout();
            break;
        case WM_SETFOCUS:
        case WM_LBUTTONDOWN:
        case WM_NCLBUTTONDOWN:
            SetFocus(state->edit);
            return 0;
        case WM_COMMAND:
        case WM_CTLCOLOREDIT:
        case WM_CTLCOLORSTATIC:
            return SendMessageW(GetParent(window), message, wParam, lParam);
        case WM_NCPAINT:
            return state->OnNonClientPaint(wParam, lParam);
        case WM_PRINT:
            return state->OnPrint(wParam, lParam);
        case WM_THEMECHANGED:
            state->InvalidateFrame();
            break;
        case WM_ERASEBKGND:
        case WM_PRINTCLIENT:
            state->PaintBackground(reinterpret_cast<HDC>(wParam));
            return 1;
        case WM_PAINT:
            state->OnPaint();
            return 0;
        case WM_NCDESTROY:
            ReleaseFrameState(window, state);
            break;
    }
    return DefWindowProcW(window, message, wParam, lParam);
}

/// Preserves the original single-line EDIT procedure and updates only its clipping frame and native border state.
LRESULT CALLBACK SettingsEdit::EditProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    SettingsEdit* state = reinterpret_cast<SettingsEdit*>(referenceData);
    LRESULT result = DefSubclassProc(window, message, wParam, lParam);
    switch (message) {
        case WM_SETFONT:
            state->Layout();
            break;
        case WM_MOUSEMOVE:
            state->OnMouseMove();
            break;
        case WM_MOUSELEAVE:
            state->hot = false;
            state->InvalidateFrame();
            break;
        case WM_SETFOCUS:
        case WM_KILLFOCUS:
        case EM_SETREADONLY:
        case WM_THEMECHANGED:
            state->InvalidateFrame();
            break;
        case WM_ENABLE:
            EnableWindow(state->frame, wParam != 0);
            state->InvalidateFrame();
            break;
        case WM_NCDESTROY:
            RemovePropW(window, SETTINGS_EDIT_FRAME_PROPERTY);
            RemoveWindowSubclass(window, EditProc, subclassId);
            break;
    }
    return result;
}
