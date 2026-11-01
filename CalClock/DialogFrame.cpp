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
#include "DialogFrame.h"
#include "SystemDialogTemplate.h"
#include "ControlColors.h"
#include <algorithm>
#include <cerrno>
#include <climits>
#include <cwchar>
#include <commctrl.h>
#include <dwmapi.h>
#include <new>
#include <string>
#include <uxtheme.h>
#include <windowsx.h>

#pragma comment(lib, "Msimg32.lib")

using GetSystemMetricsForDpiProc = int(WINAPI*)(int index, UINT dpi);
using AdjustWindowRectExForDpiProc = BOOL(WINAPI*)(RECT* rectangle, DWORD style, BOOL menu,
    DWORD extendedStyle, UINT dpi);

static constexpr UINT_PTR DIALOG_FRAME_SUBCLASS_ID = 1;
static constexpr UINT WM_NCUAHDRAWCAPTION = 0x00AE;
static constexpr UINT WM_NCUAHDRAWFRAME = 0x00AF;
static constexpr int CAPTION_HITS[] = { HTCLOSE, HTMAXBUTTON, HTMINBUTTON };
static constexpr wchar_t COLOR_OWNER_PROPERTY[] = L"CalClock.DialogColorOwner";
static constexpr wchar_t COLOR_PREVIEW_PROPERTY[] = L"CalClock.SettingsColorButton";
static constexpr int CONTROL_COLOR_INDICES[] = {
    COLOR_SCROLLBAR,
    COLOR_MENU,
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

static constexpr COLORREF CONTROL_COLORS[] = {
    RGB(212, 208, 200),
    RGB(212, 208, 200),
    RGB(255, 255, 255),
    RGB(0, 0, 0),
    RGB(0, 0, 0),
    RGB(0, 0, 0),
    RGB(128, 128, 128),
    RGB(10, 36, 106),
    RGB(255, 255, 255),
    RGB(212, 208, 200),
    RGB(128, 128, 128),
    RGB(128, 128, 128),
    RGB(0, 0, 0),
    RGB(255, 255, 255),
    RGB(64, 64, 64),
    RGB(212, 208, 200),
    RGB(0, 0, 0),
    RGB(255, 255, 225),
    RGB(0, 0, 128),
    RGB(10, 36, 106),
    RGB(212, 208, 200)
};

/// Reads native caption metrics, replacing the themed button width with the configured classic width.
static HRESULT ReadSystemWindowMetrics(NONCLIENTMETRICSW& metrics) {
    metrics.cbSize = sizeof(metrics);
    if (!SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof(metrics), &metrics, 0)) {
        return HRESULT_FROM_WIN32(GetLastError());
    }
    wchar_t captionWidth[32]{};
    DWORD size = sizeof(captionWidth);
    LSTATUS status = RegGetValueW(HKEY_CURRENT_USER, L"Control Panel\\Desktop\\WindowMetrics",
        L"CaptionWidth", RRF_RT_REG_SZ, nullptr, captionWidth, &size);
    if (status != ERROR_SUCCESS) {
        return HRESULT_FROM_WIN32(status);
    }
    wchar_t* end = nullptr;
    errno = 0;
    long value = wcstol(captionWidth, &end, 10);
    if (errno == ERANGE || end == captionWidth || *end || value == LONG_MIN) {
        return HRESULT_FROM_WIN32(ERROR_INVALID_DATA);
    }
    HDC context = GetDC(nullptr);
    if (!context) {
        return E_FAIL;
    }
    int dpi = GetDeviceCaps(context, LOGPIXELSX);
    ReleaseDC(nullptr, context);
    int width = value < 0 ? MulDiv(-value, dpi, 1440) : MulDiv(value, dpi, 96);
    if (width <= 0) {
        return HRESULT_FROM_WIN32(ERROR_INVALID_DATA);
    }
    metrics.iCaptionWidth = width;
    return S_OK;
}

/// Initializes per-window activation state; the window subclass owns this object.
DialogFrame::DialogFrame(HWND target) : window(target) {
    active = GetActiveWindow() == window;
}

/// Releases brushes and removes dialog-local state from any remaining owned popup controls.
DialogFrame::~DialogFrame() {
    RemovePropW(window, CLASSIC_STYLE_ENABLED_PROPERTY);
    RemovePropW(window, CLASSIC_CONTROL_COLORS_PROPERTY);
    for (HWND control : popupControls) {
        if (GetPropW(control, COLOR_OWNER_PROPERTY) == window) {
            RemovePropW(control, COLOR_OWNER_PROPERTY);
            ControlColors::Restore(control);
        }
    }
    for (HBRUSH brush : colorBrushes) {
        if (brush != nullptr) {
            DeleteObject(brush);
        }
    }
}

/// Finds the attached dialog through a control's parent or owner chain.
DialogFrame* DialogFrame::Find(HWND control) {
    while (control != nullptr) {
        DWORD_PTR reference = 0;
        if (GetWindowSubclass(control, SubclassProc, DIALOG_FRAME_SUBCLASS_ID, &reference)) {
            return reinterpret_cast<DialogFrame*>(reference);
        }
        HWND parent = GetParent(control);
        HWND owner = reinterpret_cast<HWND>(GetPropW(control, COLOR_OWNER_PROPERTY));
        if (owner != nullptr && owner != control) {
            control = owner;
        } else {
            control = parent;
        }
    }
    return nullptr;
}

/// Returns the dialog's Windows 2000 color, or the native system color outside that mode.
COLORREF DialogFrame::GetColor(HWND control, int colorIndex) {
    DialogFrame* frame = Find(control);
    if (frame != nullptr && frame->windows2000Style) {
        for (size_t index = 0; index < ARRAYSIZE(CONTROL_COLOR_INDICES); ++index) {
            if (CONTROL_COLOR_INDICES[index] == colorIndex) {
                return CONTROL_COLORS[index];
            }
        }
    }
    return GetSysColor(colorIndex);
}

/// Returns a brush owned by the dialog, or the native system brush outside Windows 2000 mode.
HBRUSH DialogFrame::GetBrush(HWND control, int colorIndex) {
    DialogFrame* frame = Find(control);
    if (frame == nullptr || !frame->windows2000Style || colorIndex < 0 || colorIndex > COLOR_MENUBAR) {
        return GetSysColorBrush(colorIndex);
    }
    HBRUSH& brush = frame->colorBrushes[colorIndex];
    if (brush == nullptr) {
        brush = CreateSolidBrush(GetColor(control, colorIndex));
    }
    return brush;
}

/// Maps completed native control drawing to dialog-local colors without changing its font or geometry.
void DialogFrame::RecolorControl(HWND control, HDC context, const RECT& rectangle) {
    DialogFrame* frame = Find(control);
    if (context != nullptr && frame != nullptr && frame->windows2000Style) {
        RecolorFrameRectangle(context, rectangle);
    }
}

/// Applies or restores the shared color component for one control without changing its native content.
bool DialogFrame::ApplyControlColors(HWND control) const {
    if (GetPropW(control, COLOR_PREVIEW_PROPERTY) != nullptr) {
        ControlColors::Restore(control);
        return true;
    }
    wchar_t className[64]{};
    GetClassNameW(control, className, ARRAYSIZE(className));
    bool changed = false;
    if (!ControlColors::Apply(control, window, windows2000Style, changed)) {
        return false;
    }
    if (lstrcmpiW(className, TOOLTIPS_CLASSW) == 0) {
        SendMessageW(control, TTM_SETTIPBKCOLOR, GetColor(window, COLOR_INFOBK), 0);
        SendMessageW(control, TTM_SETTIPTEXTCOLOR, GetColor(window, COLOR_INFOTEXT), 0);
    }
    if (lstrcmpiW(className, WC_COMBOBOXW) == 0) {
        COMBOBOXINFO information{ sizeof(information) };
        if (GetComboBoxInfo(control, &information) && information.hwndList != nullptr) {
            return ApplyControl(information.hwndList, window);
        }
    }
    return true;
}

/// Enumerates the current child controls while retaining application-owned color previews.
BOOL CALLBACK DialogFrame::ApplyChildColors(HWND control, LPARAM parameter) {
    ColorEnumeration* enumeration = reinterpret_cast<ColorEnumeration*>(parameter);
    if (!enumeration->frame->ApplyControlColors(control)) {
        enumeration->success = false;
    }
    return TRUE;
}

/// Applies dialog-local colors to a control and its children, including owned dropdowns and tooltips.
bool DialogFrame::ApplyControl(HWND control, HWND dialog) {
    DialogFrame* frame = Find(dialog);
    if (control == nullptr || frame == nullptr) {
        return false;
    }
    wchar_t className[64]{};
    GetClassNameW(control, className, ARRAYSIZE(className));
    bool popup = control != frame->window
        && (!(GetWindowLongPtrW(control, GWL_STYLE) & WS_CHILD) || lstrcmpiW(className, L"ComboLBox") == 0);
    if (popup) {
        const wchar_t* theme = frame->disableThemes ? L"" : nullptr;
        SetWindowTheme(control, theme, theme);
    }
    if (popup && frame->windows2000Style) {
        if (!SetPropW(control, COLOR_OWNER_PROPERTY, frame->window)) {
            return false;
        }
        if (std::find(frame->popupControls.begin(), frame->popupControls.end(), control)
                == frame->popupControls.end()) {
            frame->popupControls.push_back(control);
        }
    }
    ColorEnumeration enumeration{ frame, frame->ApplyControlColors(control) };
    EnumChildWindows(control, ApplyChildColors, reinterpret_cast<LPARAM>(&enumeration));
    if (popup && !frame->windows2000Style) {
        RemovePropW(control, COLOR_OWNER_PROPERTY);
    }
    return enumeration.success;
}

/// Reads DPI-scaled native metrics, using the configured classic caption-button width.
int DialogFrame::Metric(int index) const {
    if (index == SM_CXSIZE) {
        return MulDiv(captionWidth, GetSystemDialogDpi(window), GetSystemDialogDpi(nullptr));
    }
    HMODULE module = GetModuleHandleW(L"user32.dll");
    GetSystemMetricsForDpiProc getMetric = nullptr;
    if (module != nullptr) {
        getMetric = reinterpret_cast<GetSystemMetricsForDpiProc>(GetProcAddress(module,
            "GetSystemMetricsForDpi"));
    }
    UINT windowDpi = GetSystemDialogDpi(window);
    if (getMetric != nullptr) {
        return getMetric(index, windowDpi);
    }
    return MulDiv(GetSystemMetrics(index), windowDpi, GetSystemDialogDpi(nullptr));
}

/// Applies the theme mode and optional Windows 2000 caption without changing system metrics or client size.
bool DialogFrame::Apply(HWND window, bool disableThemes, bool windows2000Style) {
    DWORD_PTR reference = 0;
    DialogFrame* frame = nullptr;
    if (GetWindowSubclass(window, SubclassProc, DIALOG_FRAME_SUBCLASS_ID, &reference)) {
        frame = reinterpret_cast<DialogFrame*>(reference);
    } else {
        frame = new(std::nothrow) DialogFrame(window);
        if (frame == nullptr) {
            return false;
        }
        if (!SetWindowSubclass(window, SubclassProc, DIALOG_FRAME_SUBCLASS_ID,
            reinterpret_cast<DWORD_PTR>(frame))) {
            delete frame;
            return false;
        }
    }
    bool nextStyle = disableThemes && windows2000Style;
    bool styleChanged = frame->windows2000Style != nextStyle;
    frame->windows2000Style = nextStyle;
    frame->disableThemes = disableThemes;
    if (nextStyle) {
        if (!SetPropW(window, CLASSIC_STYLE_ENABLED_PROPERTY, reinterpret_cast<HANDLE>(1))
                || !SetPropW(window, CLASSIC_CONTROL_COLORS_PROPERTY, reinterpret_cast<HANDLE>(1))) {
            RemovePropW(window, CLASSIC_STYLE_ENABLED_PROPERTY);
            RemovePropW(window, CLASSIC_CONTROL_COLORS_PROPERTY);
            return false;
        }
    } else {
        RemovePropW(window, CLASSIC_STYLE_ENABLED_PROPERTY);
        RemovePropW(window, CLASSIC_CONTROL_COLORS_PROPERTY);
        for (HWND control : frame->popupControls) {
            if (GetPropW(control, COLOR_OWNER_PROPERTY) == window) {
                ApplyControl(control, window);
            }
        }
        frame->popupControls.clear();
    }
    bool colorsApplied = ApplyControl(window, window);
    bool refreshed = frame->Refresh();
    if (refreshed && styleChanged) {
        frame->Paint();
        RedrawWindow(window, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN);
    }
    return refreshed && colorsApplied;
}

/// Converts client bounds to outer bounds using the attached frame and native scrollbars.
BOOL DialogFrame::AdjustRect(HWND window, RECT* rectangle, DWORD style, DWORD extendedStyle) {
    DWORD_PTR reference = 0;
    DialogFrame* frame = nullptr;
    if (GetWindowSubclass(window, SubclassProc, DIALOG_FRAME_SUBCLASS_ID, &reference)) {
        frame = reinterpret_cast<DialogFrame*>(reference);
    }
    if (frame != nullptr && frame->enabled) {
        Layout layout = frame->GetLayout();
        InflateRect(rectangle, layout.borderX, layout.borderY);
        rectangle->top -= frame->Metric(SM_CYCAPTION);
    } else {
        HMODULE module = GetModuleHandleW(L"user32.dll");
        AdjustWindowRectExForDpiProc adjust = nullptr;
        if (module != nullptr) {
            adjust = reinterpret_cast<AdjustWindowRectExForDpiProc>(GetProcAddress(module,
                "AdjustWindowRectExForDpi"));
        }
        BOOL adjusted = adjust == nullptr
            ? AdjustWindowRectEx(rectangle, style, FALSE, extendedStyle)
            : adjust(rectangle, style, FALSE, extendedStyle, GetSystemDialogDpi(window));
        if (!adjusted) {
            return FALSE;
        }
    }
    if (style & WS_VSCROLL) {
        int width = frame == nullptr ? GetSystemMetrics(SM_CXVSCROLL) : frame->Metric(SM_CXVSCROLL);
        if (extendedStyle & WS_EX_LEFTSCROLLBAR) {
            rectangle->left -= width;
        } else {
            rectangle->right += width;
        }
    }
    if (style & WS_HSCROLL) {
        rectangle->bottom += frame == nullptr ? GetSystemMetrics(SM_CYHSCROLL) : frame->Metric(SM_CYHSCROLL);
    }
    return TRUE;
}

/// Reads current metrics and recalculates the frame after theme, metric or DPI changes.
bool DialogFrame::Refresh(bool preserveClient) {
    if (updating) {
        return true;
    }
    bool next = disableThemes || !IsThemeActive();
    bool captionChanged = false;
    if (next) {
        NONCLIENTMETRICSW metrics{};
        if (FAILED(ReadSystemWindowMetrics(metrics))) {
            return false;
        }
        captionChanged = captionWidth != metrics.iCaptionWidth;
        captionWidth = metrics.iCaptionWidth;
    }
    Layout layout = GetLayout();
    SIZE nextSize{ 2 * layout.borderX, 2 * layout.borderY + Metric(SM_CYCAPTION) };
    UINT nextDpi = GetSystemDialogDpi(window);
    if (enabled == next
            && frameSize.cx == nextSize.cx
            && frameSize.cy == nextSize.cy
            && dpi == nextDpi
            && !captionChanged) {
        return true;
    }
    updating = true;
    CancelPress();
    RECT client{};
    GetClientRect(window, &client);
    enabled = next;
    frameSize = nextSize;
    dpi = nextDpi;
    active = GetActiveWindow() == window;
    DWMNCRENDERINGPOLICY policy = enabled ? DWMNCRP_DISABLED : DWMNCRP_USEWINDOWSTYLE;
    DwmSetWindowAttribute(window, DWMWA_NCRENDERING_POLICY, &policy, sizeof(policy));
    DWORD style = static_cast<DWORD>(GetWindowLongPtrW(window, GWL_STYLE));
    DWORD extendedStyle = static_cast<DWORD>(GetWindowLongPtrW(window, GWL_EXSTYLE));
    AdjustRect(window, &client, style, extendedStyle);
    UINT flags = SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED;
    if (!preserveClient || IsIconic(window) || IsZoomed(window)) {
        flags |= SWP_NOSIZE;
    }
    SetWindowPos(window, nullptr, 0, 0, client.right - client.left, client.bottom - client.top, flags);
    RedrawWindow(window, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN);
    updating = false;
    return true;
}

/// Calculates physical-pixel bounds, retaining native invisible overhang when maximized.
DialogFrame::Layout DialogFrame::GetLayout() const {
    Layout result;
    GetWindowRect(window, &result.bounds);
    OffsetRect(&result.bounds, -result.bounds.left, -result.bounds.top);
    DWORD style = static_cast<DWORD>(GetWindowLongPtrW(window, GWL_STYLE));
    if (IsZoomed(window)) {
        result.borderX = Metric(SM_CXFRAME) + Metric(SM_CXPADDEDBORDER);
        result.borderY = Metric(SM_CYFRAME) + Metric(SM_CXPADDEDBORDER);
    } else {
        result.borderX = Metric(SM_CXFIXEDFRAME);
        result.borderY = Metric(SM_CYFIXEDFRAME);
        if (style & WS_THICKFRAME) {
            int resizeBorder = MulDiv(1, GetSystemDialogDpi(window), GetSystemDialogDpi(nullptr));
            result.borderX += resizeBorder;
            result.borderY += resizeBorder;
        }
    }
    result.caption = RECT{ result.borderX, result.borderY, result.bounds.right - result.borderX,
        result.borderY + Metric(SM_CYCAPTION) };
    int insetX = Metric(SM_CXEDGE);
    int insetY = Metric(SM_CYEDGE);
    int width = std::max(1, Metric(SM_CXSIZE) - 2 * insetX);
    int height = std::max(1, Metric(SM_CYSIZE) - 2 * insetY);
    LONG right = result.caption.right - insetX;
    for (int index = 0; index < 3; ++index) {
        if (!(style & WS_SYSMENU) || index > 0 && !(style & (WS_MINIMIZEBOX | WS_MAXIMIZEBOX))) {
            continue;
        }
        result.buttons[index] = RECT{ std::max(result.caption.left, right - width),
            result.caption.top + insetY, right, result.caption.top + insetY + height };
        right -= width;
        if (index == 0) {
            right -= insetX;
        }
    }
    result.icon = result.caption;
    result.icon.right = std::min(result.icon.right, result.icon.left + Metric(SM_CXSMICON) + 2 * insetX);
    return result;
}

/// Honors window styles, enabled state and the system menu when checking caption commands.
bool DialogFrame::ButtonEnabled(int hit) const {
    DWORD style = static_cast<DWORD>(GetWindowLongPtrW(window, GWL_STYLE));
    if (!IsWindowEnabled(window)) {
        return false;
    }
    if (hit == HTMINBUTTON) {
        return (style & WS_MINIMIZEBOX) != 0;
    }
    if (hit == HTMAXBUTTON) {
        return (style & WS_MAXIMIZEBOX) != 0;
    }
    if (hit == HTCLOSE) {
        HMENU menu = GetSystemMenu(window, FALSE);
        if (menu == nullptr) {
            return false;
        }
        UINT state = GetMenuState(menu, SC_CLOSE, MF_BYCOMMAND);
        return state != static_cast<UINT>(-1) && !(state & (MF_DISABLED | MF_GRAYED));
    }
    return false;
}

/// Maps native edge and button colors inside one nonclient rectangle.
void DialogFrame::RecolorFrameRectangle(HDC context, const RECT& rectangle) {
    int width = rectangle.right - rectangle.left;
    int height = rectangle.bottom - rectangle.top;
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
    HBITMAP bitmap = CreateDIBSection(context, &information, DIB_RGB_COLORS, &pixels, nullptr, 0);
    HDC memory = CreateCompatibleDC(context);
    if (bitmap != nullptr && memory != nullptr) {
        HGDIOBJ previous = SelectObject(memory, bitmap);
        if (previous != nullptr
                && BitBlt(memory, 0, 0, width, height, context, rectangle.left, rectangle.top, SRCCOPY)) {
            GdiFlush();
            std::array<DWORD, ARRAYSIZE(CONTROL_COLORS)> source{};
            std::array<DWORD, ARRAYSIZE(CONTROL_COLORS)> destination{};
            for (size_t index = 0; index < source.size(); ++index) {
                COLORREF color = GetSysColor(CONTROL_COLOR_INDICES[index]);
                source[index] = static_cast<DWORD>(GetRValue(color)) << 16
                    | static_cast<DWORD>(GetGValue(color)) << 8
                    | GetBValue(color);
                color = CONTROL_COLORS[index];
                destination[index] = static_cast<DWORD>(GetRValue(color)) << 16
                    | static_cast<DWORD>(GetGValue(color)) << 8
                    | GetBValue(color);
            }
            DWORD* data = static_cast<DWORD*>(pixels);
            size_t count = static_cast<size_t>(width) * height;
            bool changed = false;
            for (size_t pixel = 0; pixel < count; ++pixel) {
                DWORD color = data[pixel] & 0x00FFFFFF;
                for (size_t index = 0; index < source.size(); ++index) {
                    if (color == source[index]) {
                        if (color != destination[index]) {
                            data[pixel] = data[pixel] & 0xFF000000 | destination[index];
                            changed = true;
                        }
                        break;
                    }
                }
            }
            if (changed) {
                BitBlt(context, rectangle.left, rectangle.top, width, height, memory, 0, 0, SRCCOPY);
            }
        }
        if (previous != nullptr) {
            SelectObject(memory, previous);
        }
    }
    if (memory != nullptr) {
        DeleteDC(memory);
    }
    if (bitmap != nullptr) {
        DeleteObject(bitmap);
    }
}

/// Recolors only the native frame edges and caption buttons, preserving the caption gradient and icon.
void DialogFrame::RecolorFrame(HDC context, const Layout& layout) const {
    if (!windows2000Style) {
        return;
    }
    RecolorFrameRectangle(context, RECT{ 0, 0, layout.bounds.right, layout.borderY });
    RecolorFrameRectangle(context, RECT{ 0, layout.borderY, layout.borderX,
        layout.bounds.bottom - layout.borderY });
    RecolorFrameRectangle(context, RECT{ layout.bounds.right - layout.borderX, layout.borderY,
        layout.bounds.right, layout.bounds.bottom - layout.borderY });
    RecolorFrameRectangle(context, RECT{ 0, layout.bounds.bottom - layout.borderY,
        layout.bounds.right, layout.bounds.bottom });
    for (const RECT& button : layout.buttons) {
        RecolorFrameRectangle(context, button);
    }
}

/// Draws the classic frame with system or Windows 2000 caption styling, retaining native scrollbars and
/// content. The Windows 2000 caption inherits the current dialog font's antialiasing quality.
void DialogFrame::Paint(HDC target) const {
    if (!enabled || IsIconic(window)) {
        return;
    }
    NONCLIENTMETRICSW metrics{};
    metrics.cbSize = sizeof(metrics);
    if (!SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof(metrics), &metrics, 0)) {
        return;
    }
    LOGFONTW interfaceDescription{};
    if (windows2000Style) {
        HFONT interfaceFont = reinterpret_cast<HFONT>(SendMessageW(window, WM_GETFONT, 0, 0));
        if (GetObjectW(interfaceFont, sizeof(interfaceDescription), &interfaceDescription) == 0) {
            return;
        }
    }
    HDC dc = target == nullptr ? GetWindowDC(window) : target;
    if (dc == nullptr) {
        return;
    }
    int saved = SaveDC(dc);
    Layout layout = GetLayout();
    RECT content = layout.bounds;
    InflateRect(&content, -layout.borderX, -layout.borderY);
    content.top = layout.caption.bottom;
    if (GetWindowLongPtrW(window, GWL_STYLE) & (WS_HSCROLL | WS_VSCROLL)) {
        RECT client{};
        RECT bounds{};
        GetClientRect(window, &client);
        GetWindowRect(window, &bounds);
        MapWindowPoints(window, nullptr, reinterpret_cast<POINT*>(&client), 2);
        OffsetRect(&client, -bounds.left, -bounds.top);
        int scrollClip = SaveDC(dc);
        IntersectClipRect(dc, content.left, content.top, content.right, content.bottom);
        ExcludeClipRect(dc, client.left, client.top, client.right, client.bottom);
        if (target == nullptr) {
            HRGN scrollRegion = CreateRectRgn(content.left + bounds.left, content.top + bounds.top,
                content.right + bounds.left, content.bottom + bounds.top);
            HRGN clientRegion = CreateRectRgn(client.left + bounds.left, client.top + bounds.top,
                client.right + bounds.left, client.bottom + bounds.top);
            if (scrollRegion != nullptr && clientRegion != nullptr) {
                if (CombineRgn(scrollRegion, scrollRegion, clientRegion, RGN_DIFF) != ERROR) {
                    DefWindowProcW(window, WM_NCPAINT, reinterpret_cast<WPARAM>(scrollRegion), 0);
                }
            }
            if (clientRegion != nullptr) {
                DeleteObject(clientRegion);
            }
            if (scrollRegion != nullptr) {
                DeleteObject(scrollRegion);
            }
        } else {
            DefWindowProcW(window, WM_PRINT, reinterpret_cast<WPARAM>(dc), PRF_NONCLIENT);
        }
        if (windows2000Style) {
            RecolorFrameRectangle(dc, content);
        }
        RestoreDC(dc, scrollClip);
    }
    ExcludeClipRect(dc, content.left, content.top, content.right, content.bottom);
    FillRect(dc, &layout.bounds, GetBrush(window, COLOR_3DFACE));
    if (layout.borderX > 0) {
        RECT edge = layout.bounds;
        DrawEdge(dc, &edge, EDGE_RAISED, BF_RECT);
    }
    BOOL gradient = FALSE;
    SystemParametersInfoW(SPI_GETGRADIENTCAPTIONS, 0, &gradient, 0);
    int captionColor = active ? COLOR_ACTIVECAPTION : COLOR_INACTIVECAPTION;
    COLORREF left = GetSysColor(captionColor);
    COLORREF right = GetSysColor(active ? COLOR_GRADIENTACTIVECAPTION : COLOR_GRADIENTINACTIVECAPTION);
    COLORREF textColor = GetSysColor(active ? COLOR_CAPTIONTEXT : COLOR_INACTIVECAPTIONTEXT);
    if (windows2000Style) {
        gradient = TRUE;
        left = active ? RGB(10, 36, 106) : RGB(128, 128, 128);
        right = active ? RGB(166, 202, 240) : RGB(192, 192, 192);
        textColor = active ? RGB(255, 255, 255) : RGB(212, 208, 200);
    }
    if (gradient) {
        TRIVERTEX vertices[] = {
            {
                layout.caption.left,
                layout.caption.top,
                static_cast<COLOR16>(GetRValue(left) << 8),
                static_cast<COLOR16>(GetGValue(left) << 8),
                static_cast<COLOR16>(GetBValue(left) << 8),
                0
            }, {
                layout.caption.right,
                layout.caption.bottom,
                static_cast<COLOR16>(GetRValue(right) << 8),
                static_cast<COLOR16>(GetGValue(right) << 8),
                static_cast<COLOR16>(GetBValue(right) << 8),
                0
            }
        };
        GRADIENT_RECT rectangle{ 0, 1 };
        GradientFill(dc, vertices, 2, &rectangle, 1, GRADIENT_FILL_RECT_H);
    } else {
        FillRect(dc, &layout.caption, GetSysColorBrush(captionColor));
    }
    LONG textRight = layout.caption.right;
    for (const RECT& button : layout.buttons) {
        if (!IsRectEmpty(&button)) {
            textRight = std::min(textRight, button.left - Metric(SM_CXEDGE));
        }
    }
    RECT title = layout.caption;
    title.right = std::max(title.left, textRight);
    HICON icon = reinterpret_cast<HICON>(SendMessageW(window, WM_GETICON, ICON_SMALL2, 0));
    if (icon != nullptr && GetWindowLongPtrW(window, GWL_STYLE) & WS_SYSMENU) {
        int iconHeight = Metric(SM_CYSMICON);
        int iconTop = layout.caption.top + (layout.caption.bottom - layout.caption.top - iconHeight) / 2;
        DrawIconEx(dc, layout.icon.left + Metric(SM_CXEDGE), iconTop, icon,
            Metric(SM_CXSMICON), iconHeight, 0, nullptr, DI_NORMAL);
        title.left = layout.icon.right;
    } else {
        title.left += Metric(SM_CXEDGE);
    }
    LOGFONTW font = metrics.lfCaptionFont;
    UINT systemDpi = GetSystemDialogDpi(nullptr);
    if (windows2000Style) {
        font.lfHeight = -MulDiv(10, systemDpi, 72);
        font.lfWidth = 0;
        font.lfWeight = FW_BOLD;
        font.lfQuality = interfaceDescription.lfQuality;
        wcscpy_s(font.lfFaceName, L"Tahoma");
    }
    font.lfHeight = MulDiv(font.lfHeight, dpi, systemDpi);
    font.lfWidth = MulDiv(font.lfWidth, dpi, systemDpi);
    HFONT caption = CreateFontIndirectW(&font);
    if (caption != nullptr) {
        HGDIOBJ previous = SelectObject(dc, caption);
        SetBkMode(dc, TRANSPARENT);
        SetTextColor(dc, textColor);
        int length = GetWindowTextLengthW(window);
        std::wstring text(static_cast<size_t>(length) + 1, L'\0');
        length = GetWindowTextW(window, text.data(), length + 1);
        DrawTextW(dc, text.c_str(), length, &title,
            DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS | DT_NOPREFIX);
        SelectObject(dc, previous);
        DeleteObject(caption);
    }
    for (int index = 0; index < 3; ++index) {
        RECT button = layout.buttons[index];
        if (IsRectEmpty(&button)) {
            continue;
        }
        UINT state = index == 0
            ? DFCS_CAPTIONCLOSE
            : index == 1 ? IsZoomed(window) ? DFCS_CAPTIONRESTORE : DFCS_CAPTIONMAX : DFCS_CAPTIONMIN;
        if (!ButtonEnabled(CAPTION_HITS[index])) {
            state |= DFCS_INACTIVE;
        }
        if (pressed == CAPTION_HITS[index] && pressedInside) {
            state |= DFCS_PUSHED;
        }
        DrawFrameControl(dc, &button, DFC_CAPTION, state);
    }
    RecolorFrame(dc, layout);
    RestoreDC(dc, saved);
    if (target == nullptr) {
        ReleaseDC(window, dc);
    }
}

/// Resolves screen coordinates against the same rectangles used for painting.
LRESULT DialogFrame::HitTest(POINT point) const {
    RECT screen{};
    GetWindowRect(window, &screen);
    if (!PtInRect(&screen, point)) {
        return HTNOWHERE;
    }
    POINT local{ point.x - screen.left, point.y - screen.top };
    Layout layout = GetLayout();
    DWORD style = static_cast<DWORD>(GetWindowLongPtrW(window, GWL_STYLE));
    bool left = local.x < layout.borderX;
    bool right = local.x >= layout.bounds.right - layout.borderX;
    bool top = local.y < layout.borderY;
    bool bottom = local.y >= layout.bounds.bottom - layout.borderY;
    if (left || right || top || bottom) {
        if (!(style & WS_THICKFRAME) || IsZoomed(window)) {
            return HTBORDER;
        }
        if (top) {
            return left ? HTTOPLEFT : right ? HTTOPRIGHT : HTTOP;
        }
        if (bottom) {
            return left ? HTBOTTOMLEFT : right ? HTBOTTOMRIGHT : HTBOTTOM;
        }
        return left ? HTLEFT : HTRIGHT;
    }
    for (int index = 0; index < 3; ++index) {
        if (PtInRect(&layout.buttons[index], local)) {
            return CAPTION_HITS[index];
        }
    }
    if (PtInRect(&layout.caption, local)) {
        return style & WS_SYSMENU && PtInRect(&layout.icon, local) ? HTSYSMENU : HTCAPTION;
    }
    for (LONG object : { OBJID_VSCROLL, OBJID_HSCROLL }) {
        SCROLLBARINFO scroll{ sizeof(scroll) };
        if (GetScrollBarInfo(window, object, &scroll)
                && !(scroll.rgstate[0] & STATE_SYSTEM_INVISIBLE)
                && PtInRect(&scroll.rcScrollBar, point)) {
            return object == OBJID_VSCROLL ? HTVSCROLL : HTHSCROLL;
        }
    }
    return HTCLIENT;
}

/// Selects native frame cursors without invoking the system's separate caption repaint path.
bool DialogFrame::SetNonClientCursor(int hit) {
    LPCWSTR cursor = IDC_ARROW;
    switch (hit) {
        case HTCLIENT:
        case HTERROR:
        case HTTRANSPARENT:
            return false;
        case HTLEFT:
        case HTRIGHT:
            cursor = IDC_SIZEWE;
            break;
        case HTTOP:
        case HTBOTTOM:
            cursor = IDC_SIZENS;
            break;
        case HTTOPLEFT:
        case HTBOTTOMRIGHT:
        case HTSIZE:
            cursor = IDC_SIZENWSE;
            break;
        case HTTOPRIGHT:
        case HTBOTTOMLEFT:
            cursor = IDC_SIZENESW;
            break;
    }
    SetCursor(LoadCursorW(nullptr, cursor));
    return true;
}

/// Cancels only this frame's caption-button capture, leaving native move and resize capture alone.
void DialogFrame::CancelPress() {
    bool captured = pressed != HTNOWHERE && GetCapture() == window;
    pressed = HTNOWHERE;
    pressedInside = false;
    if (captured) {
        ReleaseCapture();
    }
}

/// Handles local nonclient layout and input, preserving native scrollbars and window commands.
LRESULT DialogFrame::HandleMessage(UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_NCACTIVATE) {
        active = wParam != FALSE;
    }
    if (message == WM_DWMCOMPOSITIONCHANGED && enabled) {
        DWMNCRENDERINGPOLICY policy = DWMNCRP_DISABLED;
        DwmSetWindowAttribute(window, DWMWA_NCRENDERING_POLICY, &policy, sizeof(policy));
    }
    if (message == WM_THEMECHANGED
            || message == WM_SETTINGCHANGE
            || message == WM_DPICHANGED
            || message == WM_DWMCOMPOSITIONCHANGED) {
        LRESULT result = DefSubclassProc(window, message, wParam, lParam);
        Refresh(message != WM_DPICHANGED);
        Paint();
        return result;
    }
    if (!enabled || IsIconic(window)) {
        return DefSubclassProc(window, message, wParam, lParam);
    }
    if (message == WM_NCPAINT) {
        Paint();
        return 0;
    }
    if (message == WM_NCUAHDRAWCAPTION || message == WM_NCUAHDRAWFRAME) {
        return 0;
    }
    if (message == WM_SETCURSOR
            && reinterpret_cast<HWND>(wParam) == window
            && SetNonClientCursor(static_cast<short>(LOWORD(lParam)))) {
        return TRUE;
    }
    if (message == WM_NCCALCSIZE) {
        RECT* client = reinterpret_cast<RECT*>(lParam);
        RECT outer = *client;
        DefSubclassProc(window, message, wParam, lParam);
        Layout layout = GetLayout();
        *client = RECT{
            outer.left + layout.borderX,
            outer.top + layout.borderY + Metric(SM_CYCAPTION),
            outer.right - layout.borderX,
            outer.bottom - layout.borderY
        };
        DWORD style = static_cast<DWORD>(GetWindowLongPtrW(window, GWL_STYLE));
        DWORD extendedStyle = static_cast<DWORD>(GetWindowLongPtrW(window, GWL_EXSTYLE));
        if (style & WS_VSCROLL) {
            if (extendedStyle & WS_EX_LEFTSCROLLBAR) {
                client->left += Metric(SM_CXVSCROLL);
            } else {
                client->right -= Metric(SM_CXVSCROLL);
            }
        }
        if (style & WS_HSCROLL) {
            client->bottom -= Metric(SM_CYHSCROLL);
        }
        client->right = std::max(client->left, client->right);
        client->bottom = std::max(client->top, client->bottom);
        return 0;
    }
    if (message == WM_NCHITTEST) {
        return HitTest(POINT{ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) });
    }
    if (message == WM_NCLBUTTONDOWN || message == WM_NCLBUTTONDBLCLK) {
        int hit = static_cast<int>(wParam);
        if (hit == HTCLOSE || hit == HTMINBUTTON || hit == HTMAXBUTTON) {
            if (ButtonEnabled(hit)) {
                pressed = hit;
                pressedInside = true;
                SetCapture(window);
                Paint();
            }
            return 0;
        }
    }
    if ((message == WM_MOUSEMOVE || message == WM_LBUTTONUP) && pressed != HTNOWHERE) {
        POINT point{ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
        ClientToScreen(window, &point);
        bool inside = HitTest(point) == pressed;
        if (message == WM_LBUTTONUP) {
            int hit = pressed;
            CancelPress();
            Paint();
            if (inside && ButtonEnabled(hit)) {
                WPARAM command;
                if (hit == HTCLOSE) {
                    command = SC_CLOSE;
                } else if (hit == HTMINBUTTON) {
                    command = SC_MINIMIZE;
                } else if (IsZoomed(window)) {
                    command = SC_RESTORE;
                } else {
                    command = SC_MAXIMIZE;
                }
                PostMessageW(window, WM_SYSCOMMAND, command, MAKELPARAM(point.x, point.y));
            }
        } else if (inside != pressedInside) {
            pressedInside = inside;
            Paint();
        }
        return 0;
    }
    if ((message == WM_CANCELMODE || message == WM_CAPTURECHANGED) && pressed != HTNOWHERE) {
        CancelPress();
        Paint();
    }
    if (message == WM_NCACTIVATE) {
        active = wParam != FALSE;
        LRESULT result = DefSubclassProc(window, message, wParam, -1);
        Paint();
        return result;
    }
    bool printFrame = message == WM_PRINT && lParam & PRF_NONCLIENT;
    LPARAM nativeParameter = printFrame ? lParam & ~PRF_NONCLIENT : lParam;
    LRESULT result = DefSubclassProc(window, message, wParam, nativeParameter);
    if (message == WM_GETTITLEBARINFOEX) {
        TITLEBARINFOEX* information = reinterpret_cast<TITLEBARINFOEX*>(lParam);
        Layout layout = GetLayout();
        RECT bounds{};
        GetWindowRect(window, &bounds);
        information->rcTitleBar = layout.caption;
        OffsetRect(&information->rcTitleBar, bounds.left, bounds.top);
        const int indices[] = { 5, 3, 2 };
        for (int index = 0; index < 3; ++index) {
            int target = indices[index];
            information->rgrect[target] = layout.buttons[index];
            OffsetRect(&information->rgrect[target], bounds.left, bounds.top);
            if (IsRectEmpty(&layout.buttons[index])) {
                information->rgstate[target] = STATE_SYSTEM_INVISIBLE;
            } else if (ButtonEnabled(CAPTION_HITS[index])) {
                information->rgstate[target] = 0;
            } else {
                information->rgstate[target] = STATE_SYSTEM_UNAVAILABLE;
            }
            if (pressed == CAPTION_HITS[index] && pressedInside) {
                information->rgstate[target] |= STATE_SYSTEM_PRESSED;
            }
        }
    } else if (printFrame) {
        Paint(reinterpret_cast<HDC>(wParam));
    } else if (message == WM_SETTEXT
            || message == WM_SETICON
            || message == WM_ENABLE
            || message == WM_SYSCOLORCHANGE
            || message == WM_SIZE) {
        Paint();
    }
    return result;
}

/// Dispatches the attached window and releases its frame object when the window is destroyed.
LRESULT CALLBACK DialogFrame::SubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    DialogFrame* frame = reinterpret_cast<DialogFrame*>(referenceData);
    if (message == WM_NCDESTROY) {
        RemoveWindowSubclass(window, SubclassProc, subclassId);
        delete frame;
        return DefSubclassProc(window, message, wParam, lParam);
    }
    return frame->HandleMessage(message, wParam, lParam);
}
