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

/// Hosts a native single-line EDIT in a clipped viewport while preserving its selected font and native input.
class SettingsEdit {

public:
    /// Creates the viewport and native edit; returns the edit handle or null if either window cannot be created.
    static HWND Create(HINSTANCE instance, HWND parent, DWORD extended, DWORD style, const wchar_t* text, int x, int y,
        int width, int height, int id);

    /// Returns the viewport for a hosted edit, or the supplied handle for an ordinary control.
    static HWND GetFrame(HWND edit);

    /// Returns the native edit belonging to a viewport, or null for an unrelated window.
    static HWND GetEdit(HWND frame);

    /// Recalculates native text placement after the font, viewport size, or edit margins change.
    static void UpdateLayout(HWND edit);

private:
    /// Owns the visible viewport and native themed border around the edit.
    HWND frame = nullptr;

    /// Retains native text editing, selection, caret, notifications, and accessibility.
    HWND edit = nullptr;

    /// Selects the native border's hover state while the pointer is inside the edit.
    bool hot = false;

    /// Leaves state cleanup with the creator until the viewport has been created successfully.
    bool creating = true;

    /// Centers the selected font's full native text line inside the viewport without changing its visible height.
    void Layout() const;

    /// Draws the native edit-border theme part outside the viewport's client area.
    bool PaintFrame(HDC dc) const;

    /// Fills the viewport with the brush supplied by the original parent for the current native edit state.
    void PaintBackground(HDC dc) const;

    /// Requests repainting of the viewport background and border after a native control-state change.
    void InvalidateFrame() const;

    /// Paints the nonclient border and falls back to the default window procedure when themed drawing is unavailable.
    LRESULT OnNonClientPaint(WPARAM wParam, LPARAM lParam) const;

    /// Prints the viewport with the same themed border that is displayed on its native window surface.
    LRESULT OnPrint(WPARAM wParam, LPARAM lParam) const;

    /// Paints the viewport's client background within a balanced BeginPaint and EndPaint pair.
    void OnPaint() const;

    /// Starts native mouse-leave tracking on entry and refreshes the border's hover state.
    void OnMouseMove();

    /// Clears the frame's state pointer and deletes the state only after successful viewport creation.
    static void ReleaseFrameState(HWND window, SettingsEdit* state);

    /// Routes viewport layout, focus, parent notifications, painting, and destruction messages.
    static LRESULT CALLBACK FrameProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

    /// Calls the native edit procedure first, then updates viewport layout, hover, enable state, and subclass cleanup.
    static LRESULT CALLBACK EditProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData);
};
