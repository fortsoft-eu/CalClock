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

/// Manages the About dialog, its controls and fonts, and its saved position.
class AboutForm {

public:
    /// Returns this form's native window, or null while it is closed.
    HWND GetWindow() const;

    /// Creates or activates this form with its own template, state, controls and saved placement.
    void Show(HINSTANCE module, PersistWindowState& state);

    /// Updates this form's localized captions and content without changing the other form.
    void Refresh() const;

    /// Applies the effective interface font and current theme while keeping the About license in Consolas.
    bool ApplyStyle(bool updateFont = true);

    /// Destroys this form and releases its controls and owned fonts.
    void Close() const;

private:
    HWND window = nullptr;
    HWND tooltip = nullptr;
    HFONT uiFont = nullptr;
    HFONT licenseFont = nullptr;
    HINSTANCE instance = nullptr;
    PersistWindowState* placement = nullptr;
    SIZE referenceLicense = {};
    UINT referenceDpi = 96;
    wchar_t tooltipText[256] = {};
    bool ownsFont = false;
    bool initialized = false;

    /// Builds the natural About layout from its fixed license dimensions, then fits it to the monitor work
    /// area. Resize notifications anchor the edit to the right and bottom edges and the Close button to the
    /// bottom right.
    void Layout(bool resize = true) const;

    /// Handles this form's native commands, layout, theme, DPI changes and resource cleanup.
    INT_PTR HandleMessage(UINT message, WPARAM wParam, LPARAM lParam);

    /// Fits the About window to its monitor work area after its natural layout, without saving the adjusted
    /// size.
    void FitToWorkArea() const;

    /// Decodes the embedded UTF-8 license, removes an optional BOM and a case-insensitive MIT License heading,
    /// and trims outer whitespace. Accepts whitespace between heading words, preserves the license body, and
    /// normalizes line endings for the edit control.
    std::wstring LoadLicenseText() const;

    /// Opens the About website and reports failures in the selected application language.
    void OpenWebsite() const;

    /// Displays the applicable About context commands and handles opening the website or copying its URL
    /// or product information.
    void ShowContextMenu(HWND source, LPARAM location) const;

    /// Adds the About context menu to product and website controls and removes the subclass on destruction.
    static LRESULT CALLBACK ControlSubclassProc(HWND control, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData);

    /// Associates the native dialog with its form object and dispatches only this form's messages.
    static INT_PTR CALLBACK DialogProc(HWND dialog, UINT message, WPARAM wParam, LPARAM lParam);
};
