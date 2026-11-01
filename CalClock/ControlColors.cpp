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
 * Last modified for version 1.7.0.5
 */

#include "ControlColors.h"
#include <commctrl.h>
#include <new>

constexpr UINT_PTR ControlColorsSubclassId = 1;
constexpr COLORREF FaceColor = RGB(212, 208, 200);
constexpr COLORREF BackgroundColor = RGB(255, 255, 255);
constexpr COLORREF TextColor = RGB(0, 0, 0);
constexpr COLORREF DisabledTextColor = RGB(128, 128, 128);
constexpr COLORREF SelectionColor = RGB(10, 36, 106);
constexpr UINT ListViewGetMessages[]{ LVM_GETBKCOLOR, LVM_GETTEXTCOLOR, LVM_GETTEXTBKCOLOR };
constexpr UINT ListViewSetMessages[]{ LVM_SETBKCOLOR, LVM_SETTEXTCOLOR, LVM_SETTEXTBKCOLOR };
constexpr UINT TreeViewGetMessages[]{ TVM_GETBKCOLOR, TVM_GETTEXTCOLOR, TVM_GETLINECOLOR };
constexpr UINT TreeViewSetMessages[]{ TVM_SETBKCOLOR, TVM_SETTEXTCOLOR, TVM_SETLINECOLOR };
constexpr UINT ProgressGetMessages[]{ PBM_GETBKCOLOR, PBM_GETBARCOLOR };
constexpr UINT ProgressSetMessages[]{ PBM_SETBKCOLOR, PBM_SETBARCOLOR };
constexpr COLORREF ListViewColors[]{ BackgroundColor, TextColor, BackgroundColor };
constexpr COLORREF TreeViewColors[]{ BackgroundColor, TextColor, DisabledTextColor };
constexpr COLORREF ProgressColors[]{ FaceColor, SelectionColor };
constexpr int ControlColorIndices[]{
    COLOR_SCROLLBAR, COLOR_MENU,
    COLOR_WINDOW,
    COLOR_WINDOWFRAME,
    COLOR_MENUTEXT,
    COLOR_WINDOWTEXT,
    COLOR_APPWORKSPACE,
    COLOR_HIGHLIGHT,
    COLOR_HIGHLIGHTTEXT,
    COLOR_BTNFACE,
    COLOR_BTNSHADOW,
    COLOR_GRAYTEXT,
    COLOR_BTNTEXT,
    COLOR_BTNHIGHLIGHT,
    COLOR_3DDKSHADOW,
    COLOR_3DLIGHT,
    COLOR_INFOTEXT,
    COLOR_INFOBK,
    COLOR_HOTLIGHT,
    COLOR_MENUHILIGHT,
    COLOR_MENUBAR
};

constexpr COLORREF CONTROL_COLORS[]{
    FaceColor,
    FaceColor,
    BackgroundColor,
    TextColor,
    TextColor,
    TextColor,
    DisabledTextColor,
    SelectionColor,
    BackgroundColor,
    FaceColor,
    DisabledTextColor,
    DisabledTextColor,
    TextColor,
    BackgroundColor,
    RGB(64, 64, 64),
    FaceColor,
    TextColor,
    RGB(255, 255, 225),
    RGB(0, 0, 128),
    SelectionColor,
    FaceColor
};

thread_local bool recoloringControls = false;

/// Converts a COLORREF value to the RGB byte order used by a 32-bit DIB pixel.
static DWORD BitmapColor(COLORREF color) {
    return static_cast<DWORD>(GetRValue(color)) << 16
        | static_cast<DWORD>(GetGValue(color)) << 8
        | GetBValue(color);
}

/// Records the target and controlling window and creates the owned classic background brushes.
ControlColors::ControlColors(HWND targetWindow, HWND controller)
        : window(targetWindow), owner(controller) {
    faceBrush = CreateSolidBrush(FaceColor);
    backgroundBrush = CreateSolidBrush(BackgroundColor);
}

/// Releases the background brushes owned by this control state.
ControlColors::~ControlColors() {
    DeleteObject(faceBrush);
    DeleteObject(backgroundBrush);
}

/// Returns the state attached to the window subclass, or null when no state is installed.
ControlColors* ControlColors::Find(HWND window) {
    DWORD_PTR data = 0;
    return GetWindowSubclass(window, Procedure, ControlColorsSubclassId, &data)
        ? reinterpret_cast<ControlColors*>(data)
        : nullptr;
}

/// Reuses or installs state on a window owned by the current thread.
/// Pins the callback module for its lifetime and returns null if installation fails.
ControlColors* ControlColors::Attach(HWND window, HWND owner) {
    ControlColors* state = Find(window);
    if (state) {
        state->owner = owner;
        return state;
    }
    if (GetWindowThreadProcessId(window, nullptr) != GetCurrentThreadId()) {
        return nullptr;
    }
    HMODULE module = nullptr;
    if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_PIN,
            reinterpret_cast<LPCWSTR>(Procedure), &module)) {
        return nullptr;
    }
    state = new (std::nothrow) ControlColors(window, owner);
    if (!state) {
        return nullptr;
    }
    if (!state->faceBrush || !state->backgroundBrush || !SetWindowSubclass(window, Procedure,
        ControlColorsSubclassId, reinterpret_cast<DWORD_PTR>(state))) {
        delete state;
        return nullptr;
    }
    return state;
}

/// Saves and applies native list, tree or progress colors when enabled.
/// Restores saved values only where the control still uses the colors applied here.
void ControlColors::SetColors(bool enabled) {
    const UINT* getMessages = nullptr;
    const UINT* setMessages = nullptr;
    const COLORREF* colors = nullptr;
    size_t count = 0;
    if (kind == Kind::ListView) {
        getMessages = ListViewGetMessages;
        setMessages = ListViewSetMessages;
        colors = ListViewColors;
        count = ARRAYSIZE(ListViewColors);
    } else if (kind == Kind::TreeView) {
        getMessages = TreeViewGetMessages;
        setMessages = TreeViewSetMessages;
        colors = TreeViewColors;
        count = ARRAYSIZE(TreeViewColors);
    } else if (kind == Kind::Progress) {
        getMessages = ProgressGetMessages;
        setMessages = ProgressSetMessages;
        colors = ProgressColors;
        count = ARRAYSIZE(ProgressColors);
    }
    for (size_t index = 0; index < count; ++index) {
        COLORREF current = static_cast<COLORREF>(SendMessageW(window, getMessages[index], 0, 0));
        if (enabled) {
            previousColors[index] = current;
            SendMessageW(window, setMessages[index], 0, colors[index]);
        } else if (current == colors[index]) {
            SendMessageW(window, setMessages[index], 0, previousColors[index]);
        }
    }
}

/// Enables or removes local classic colors, attaching the parent when needed for color notifications.
/// Sets the caller's change flag when state changes; returns false if installation fails.
bool ControlColors::Apply(HWND window, HWND owner, bool enabled, bool& changed) {
    if (!enabled) {
        if (Find(window)) {
            Restore(window);
            changed = true;
        }
        return true;
    }
    ControlColors* state = Attach(window, owner);
    if (!state) {
        return false;
    }
    if (state->target) {
        return true;
    }
    HWND parent = GetParent(window);
    if (GetWindowLongPtrW(window, GWL_STYLE) & WS_CHILD) {
        if (!Attach(parent, owner)) {
            Restore(window);
            return false;
        }
    }
    wchar_t className[64]{};
    GetClassNameW(window, className, ARRAYSIZE(className));
    if (lstrcmpiW(className, WC_LISTVIEWW) == 0) {
        state->kind = Kind::ListView;
    } else if (lstrcmpiW(className, WC_TREEVIEWW) == 0) {
        state->kind = Kind::TreeView;
    } else if (lstrcmpiW(className, PROGRESS_CLASSW) == 0) {
        state->kind = Kind::Progress;
    }
    LONG_PTR style = GetWindowLongPtrW(window, GWL_STYLE);
    state->paintTarget = (style & WS_CHILD) != 0 || lstrcmpiW(className, L"ComboLBox") == 0;
    if (lstrcmpiW(className, WC_BUTTONW) == 0) {
        state->paintTarget = state->paintTarget
            && (style & BS_TYPEMASK) != BS_OWNERDRAW
            && !(style & (BS_ICON | BS_BITMAP));
    } else if (lstrcmpiW(className, WC_STATICW) == 0) {
        LONG_PTR type = style & SS_TYPEMASK;
        state->paintTarget = state->paintTarget
            && type != SS_ICON
            && type != SS_BITMAP
            && type != SS_ENHMETAFILE
            && type != SS_OWNERDRAW;
    }
    state->target = true;
    state->SetColors(true);
    changed = true;
    return true;
}

/// Removes the subclass, restores eligible saved colors, releases state and requests native repainting.
void ControlColors::Restore(HWND window) {
    ControlColors* state = Find(window);
    if (!state) {
        return;
    }
    RemoveWindowSubclass(window, Procedure, ControlColorsSubclassId);
    if (state->target) {
        state->SetColors(false);
    }
    delete state;
    RedrawWindow(window, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN);
}

/// Supplies classic text and background colors only for targets sharing this controlling window.
/// Returns the original result for other controls; returned custom brushes remain owned by this object.
LRESULT ControlColors::ColorControl(UINT message, WPARAM wParam, LPARAM lParam, LRESULT result) const {
    HWND control = reinterpret_cast<HWND>(lParam);
    ControlColors* state = Find(control);
    if (!state || !state->target || state->owner != owner) {
        return result;
    }
    bool background = message == WM_CTLCOLOREDIT || message == WM_CTLCOLORLISTBOX;
    HDC dc = reinterpret_cast<HDC>(wParam);
    SetBkColor(dc, background ? BackgroundColor : FaceColor);
    SetTextColor(dc, IsWindowEnabled(control) ? TextColor : DisabledTextColor);
    return reinterpret_cast<LRESULT>(background ? backgroundBrush : faceBrush);
}

/// Maps exact native system-color pixels to the classic palette within the current clipping region.
/// Uses window or client coordinates without changing control content, geometry or unrelated pixel colors.
void ControlColors::Recolor(HDC dc, bool nonClient) const {
    if (!dc) {
        return;
    }
    RECT bounds{};
    if (nonClient) {
        GetWindowRect(window, &bounds);
        OffsetRect(&bounds, -bounds.left, -bounds.top);
    } else {
        GetClientRect(window, &bounds);
    }
    RECT clip{};
    if (GetClipBox(dc, &clip) != ERROR) {
        IntersectRect(&bounds, &bounds, &clip);
    }
    int width = bounds.right - bounds.left;
    int height = bounds.bottom - bounds.top;
    if (width <= 0 || height <= 0) {
        return;
    }
    BITMAPINFO information{};
    information.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    information.bmiHeader.biWidth = width;
    information.bmiHeader.biHeight = -height;
    information.bmiHeader.biPlanes = 1;
    information.bmiHeader.biBitCount = 32;
    void* pixels = nullptr;
    HBITMAP bitmap = CreateDIBSection(dc, &information, DIB_RGB_COLORS, &pixels, nullptr, 0);
    HDC memory = CreateCompatibleDC(dc);
    if (bitmap && memory) {
        HGDIOBJ previous = SelectObject(memory, bitmap);
        if (previous && BitBlt(memory, 0, 0, width, height, dc, bounds.left, bounds.top, SRCCOPY)) {
            GdiFlush();
            std::array<DWORD, ARRAYSIZE(CONTROL_COLORS)> originals{};
            std::array<DWORD, ARRAYSIZE(CONTROL_COLORS)> desired{};
            for (size_t index = 0; index < originals.size(); ++index) {
                originals[index] = BitmapColor(GetSysColor(ControlColorIndices[index]));
                desired[index] = BitmapColor(CONTROL_COLORS[index]);
            }
            DWORD* data = static_cast<DWORD*>(pixels);
            size_t count = static_cast<size_t>(width) * height;
            bool changed = false;
            for (size_t pixel = 0; pixel < count; ++pixel) {
                DWORD color = data[pixel] & 0x00FFFFFF;
                for (size_t index = 0; index < originals.size(); ++index) {
                    if (color == originals[index]) {
                        if (color != desired[index]) {
                            data[pixel] = data[pixel] & 0xFF000000 | desired[index];
                            changed = true;
                        }
                        break;
                    }
                }
            }
            if (changed) {
                BitBlt(dc, bounds.left, bounds.top, width, height, memory, 0, 0, SRCCOPY);
            }
        }
        if (previous) {
            SelectObject(memory, previous);
        }
    }
    if (memory) {
        DeleteDC(memory);
    }
    if (bitmap) {
        DeleteObject(bitmap);
    }
}

/// Preserves native message handling and last-error state while applying enabled local color overrides.
/// Recolors completed painting without recursion and releases subclass state on window destruction.
LRESULT CALLBACK ControlColors::Procedure(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR data) {
    UNREFERENCED_PARAMETER(subclassId);
    DWORD entryError = GetLastError();
    ControlColors* state = reinterpret_cast<ControlColors*>(data);
    if (message == WM_NCDESTROY) {
        RemoveWindowSubclass(window, Procedure, ControlColorsSubclassId);
        delete state;
        SetLastError(entryError);
        return DefSubclassProc(window, message, wParam, lParam);
    }
    RECT paintBounds{};
    bool paintRegion = message == WM_PAINT && GetUpdateRect(window, &paintBounds, FALSE);
    SetLastError(entryError);
    LRESULT result = DefSubclassProc(window, message, wParam, lParam);
    DWORD previousError = GetLastError();
    state = Find(window);
    if (state
            && IsWindow(state->owner)
            && GetPropW(state->owner, CLASSIC_STYLE_ENABLED_PROPERTY)
            && GetPropW(state->owner, CLASSIC_CONTROL_COLORS_PROPERTY)) {
        if (message >= WM_CTLCOLORMSGBOX && message <= WM_CTLCOLORSTATIC) {
            result = state->ColorControl(message, wParam, lParam, result);
        }
        bool providedDc = message == WM_PRINT || message == WM_PRINTCLIENT || message == WM_ERASEBKGND;
        bool painted = providedDc
            || message == WM_PAINT
            || message == WM_NCPAINT
            || message == WM_ENABLE
            || message == WM_SETFOCUS
            || message == WM_KILLFOCUS
            || message == BM_SETSTATE
            || message == BM_SETCHECK
            || message == WM_UPDATEUISTATE;
        if (state->paintTarget && painted && !recoloringControls) {
            recoloringControls = true;
            bool nonClient = message == WM_NCPAINT || message == WM_PRINT && lParam & PRF_NONCLIENT;
            HDC dc = providedDc
                ? reinterpret_cast<HDC>(wParam)
                : nonClient ? GetWindowDC(window) : GetDC(window);
            int saved = SaveDC(dc);
            if (saved) {
                if (paintRegion) {
                    IntersectClipRect(dc, paintBounds.left, paintBounds.top, paintBounds.right,
                        paintBounds.bottom);
                }
                if (message == WM_NCPAINT) {
                    WINDOWINFO information{ sizeof(information) };
                    GetWindowInfo(window, &information);
                    ExcludeClipRect(dc, information.rcClient.left - information.rcWindow.left,
                        information.rcClient.top - information.rcWindow.top,
                        information.rcClient.right - information.rcWindow.left,
                        information.rcClient.bottom - information.rcWindow.top);
                }
                state->Recolor(dc, nonClient);
                RestoreDC(dc, saved);
            }
            if (!providedDc) {
                ReleaseDC(window, dc);
            }
            recoloringControls = false;
        }
    }
    SetLastError(previousError);
    return result;
}
