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
 * Last modified for version 1.7.0.0
 */

#pragma once

#include "PersistWindowState.h"
#include <string>

/// Manages the resizable Help dialog, its controls and fonts, and its saved placement.
class HelpForm {

public:
    /// Returns this form's native window, or null while it is closed.
    HWND GetWindow() const;

    /// Creates or activates this form with its own template, state, controls and saved placement.
    void Show(HINSTANCE module, PersistWindowState& state);

    /// Updates this form's localized captions and content without changing the other form.
    void Refresh() const;

    /// Applies the effective application font and theme to the Help controls.
    bool ApplyStyle(bool updateFont = true);

    /// Destroys this form and releases its controls and owned fonts.
    void Close() const;

private:
    HWND window = nullptr;
    HFONT uiFont = nullptr;
    HINSTANCE instance = nullptr;
    PersistWindowState* placement = nullptr;
    bool ownsFont = false;
    bool initialized = false;

    /// Anchors the Help edit and Close button to the current client area.
    void Layout() const;

    /// Handles this form's native commands, layout, theme, DPI changes and resource cleanup.
    INT_PTR HandleMessage(UINT message, WPARAM wParam, LPARAM lParam);

    /// Associates the native dialog with its form object and dispatches only this form's messages.
    static INT_PTR CALLBACK DialogProc(HWND dialog, UINT message, WPARAM wParam, LPARAM lParam);
};
