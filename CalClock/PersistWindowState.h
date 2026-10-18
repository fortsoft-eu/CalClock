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

#pragma once

#include <windows.h>

/// Retains normal screen bounds separately from the last nonminimized window state.
struct PersistWindowStateData {
    int x = CW_USEDEFAULT;
    int y = CW_USEDEFAULT;
    int width = 0;
    int height = 0;
    bool maximized = false;
};

/// Restores a hidden form before its first display and tracks its normal bounds and nonminimized state.
/// Persistence is supplied by the application's existing settings backend.
class PersistWindowState {

public:
    /// Creates an unattached state tracker with native initial placement.
    PersistWindowState();

    /// Removes the native window subclass when its owner is destroyed first.
    ~PersistWindowState();

    /// Prevents copying a tracker attached to a native window.
    PersistWindowState(const PersistWindowState&) = delete;

    /// Prevents copying a tracker attached to a native window.
    PersistWindowState& operator=(const PersistWindowState&) = delete;

    /// Supplies saved state before creating and attaching the form.
    void Load(const PersistWindowStateData& saved);

    /// Returns the remembered state without changing the native window.
    const PersistWindowStateData& GetState() const;

    /// Restores saved placement while hidden and subscribes to native placement and destruction messages.
    /// Restores size only for resizable windows and maximization only when supported by their native style.
    bool Attach(HWND target);

    /// Captures current normal bounds or maximization, retaining the previous state while minimized.
    const PersistWindowStateData& Save();

    /// Displays the fully initialized form directly in its saved state and activates it.
    void Show() const;

    /// Restores a minimized form and activates it without changing an already maximized form.
    void BringToFront() const;

private:
    HWND window = nullptr;
    PersistWindowStateData state;

    /// Updates normal bounds and the last nonminimized state from the attached native window.
    void Capture();

    /// Constrains normal bounds to the current monitor work area without disturbing maximized placement.
    bool FitToWorkArea() const;

    /// Tracks completed placement changes and releases the attachment before native destruction completes.
    static LRESULT CALLBACK WindowSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData);
};
