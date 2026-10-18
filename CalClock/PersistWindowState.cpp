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
#define WIN32_LEAN_AND_MEAN
#include "PersistWindowState.h"
#include <algorithm>
#include <commctrl.h>

#pragma comment(lib, "Comctl32.lib")

/// Creates an unattached state tracker with native initial placement.
PersistWindowState::PersistWindowState() = default;

/// Removes the native window subclass when its owner is destroyed first.
PersistWindowState::~PersistWindowState() {
    if (window != nullptr) {
        RemoveWindowSubclass(window, WindowSubclassProc, reinterpret_cast<UINT_PTR>(this));
    }
}

/// Supplies saved state before creating and attaching the form.
void PersistWindowState::Load(const PersistWindowStateData& saved) {
    state = saved;
}

/// Returns the remembered state without changing the native window.
const PersistWindowStateData& PersistWindowState::GetState() const {
    return state;
}

/// Restores saved placement while hidden and subscribes to native placement and destruction messages.
/// Restores size only for resizable windows and maximization only when supported by their native style.
bool PersistWindowState::Attach(HWND target) {
    if (target == nullptr || window != nullptr || IsWindowVisible(target)) {
        return false;
    }
    RECT rect = {};
    if (!GetWindowRect(target, &rect)) {
        return false;
    }
    LONG_PTR style = GetWindowLongPtrW(target, GWL_STYLE);
    int x = state.x == CW_USEDEFAULT ? rect.left : state.x;
    int y = state.y == CW_USEDEFAULT ? rect.top : state.y;
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    if ((style & WS_THICKFRAME) != 0) {
        if (state.width > 0) {
            width = state.width;
        }
        if (state.height > 0) {
            height = state.height;
        }
    }
    MONITORINFO monitor = { sizeof(monitor) };
    if (!GetMonitorInfoW(MonitorFromPoint(POINT{ x, y }, MONITOR_DEFAULTTONEAREST), &monitor)) {
        return false;
    }
    width = std::min(width, static_cast<int>(monitor.rcWork.right - monitor.rcWork.left));
    height = std::min(height, static_cast<int>(monitor.rcWork.bottom - monitor.rcWork.top));
    x = std::clamp(x, static_cast<int>(monitor.rcWork.left), static_cast<int>(monitor.rcWork.right) - width);
    y = std::clamp(y, static_cast<int>(monitor.rcWork.top), static_cast<int>(monitor.rcWork.bottom) - height);
    if (!SetWindowPos(target, nullptr, x, y, width, height, SWP_NOZORDER | SWP_NOACTIVATE)
        || !SetWindowSubclass(target, WindowSubclassProc, reinterpret_cast<UINT_PTR>(this),
            reinterpret_cast<DWORD_PTR>(this))) {
        return false;
    }
    window = target;
    state.x = x;
    state.y = y;
    state.width = width;
    state.height = height;
    state.maximized = state.maximized && (style & WS_MAXIMIZEBOX) != 0;
    return true;
}

/// Captures current normal bounds or maximization, retaining the previous state while minimized.
const PersistWindowStateData& PersistWindowState::Save() {
    Capture();
    return state;
}

/// Displays the fully initialized form directly in its saved state and activates it.
void PersistWindowState::Show() const {
    if (window != nullptr) {
        int command = SW_SHOWNORMAL;
        if (state.maximized) {
            command = SW_SHOWMAXIMIZED;
        }
        ShowWindow(window, command);
        BringToFront();
    }
}

/// Restores a minimized form and activates it without changing an already maximized form.
void PersistWindowState::BringToFront() const {
    if (window != nullptr) {
        if (IsIconic(window)) {
            ShowWindow(window, SW_RESTORE);
        }
        SetForegroundWindow(window);
    }
}

/// Updates normal bounds and the last nonminimized state from the attached native window.
void PersistWindowState::Capture() {
    if (window == nullptr || !IsWindowVisible(window) || IsIconic(window)) {
        return;
    }
    state.maximized = IsZoomed(window) != FALSE;
    if (!state.maximized) {
        RECT rect = {};
        if (GetWindowRect(window, &rect)) {
            state.x = rect.left;
            state.y = rect.top;
            state.width = rect.right - rect.left;
            state.height = rect.bottom - rect.top;
        }
    }
}

/// Constrains normal bounds to the current monitor work area without disturbing maximized placement.
bool PersistWindowState::FitToWorkArea() const {
    if (window == nullptr || IsIconic(window) || IsZoomed(window)) {
        return false;
    }
    MONITORINFO monitor = { sizeof(monitor) };
    RECT rect = {};
    if (!GetMonitorInfoW(MonitorFromWindow(window, MONITOR_DEFAULTTONEAREST), &monitor)
            || !GetWindowRect(window, &rect)) {
        return false;
    }
    int width = std::min(rect.right - rect.left, monitor.rcWork.right - monitor.rcWork.left);
    int height = std::min(rect.bottom - rect.top, monitor.rcWork.bottom - monitor.rcWork.top);
    int x = std::clamp(rect.left, monitor.rcWork.left, monitor.rcWork.right - width);
    int y = std::clamp(rect.top, monitor.rcWork.top, monitor.rcWork.bottom - height);
    return SetWindowPos(window, nullptr, x, y, width, height, SWP_NOZORDER | SWP_NOACTIVATE) != FALSE;
}

/// Tracks completed placement changes and releases the attachment before native destruction completes.
LRESULT CALLBACK PersistWindowState::WindowSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    PersistWindowState* owner = reinterpret_cast<PersistWindowState*>(referenceData);
    if (message == WM_DESTROY) {
        owner->Capture();
    }
    if (message == WM_NCDESTROY) {
        RemoveWindowSubclass(window, WindowSubclassProc, subclassId);
        owner->window = nullptr;
    }
    LRESULT result = DefSubclassProc(window, message, wParam, lParam);
    if (message == WM_WINDOWPOSCHANGED) {
        owner->Capture();
    } else if (message == WM_SETTINGCHANGE || message == WM_DISPLAYCHANGE) {
        owner->FitToWorkArea();
    }
    return result;
}
