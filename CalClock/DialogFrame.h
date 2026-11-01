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

#pragma once

#include <windows.h>
#include <array>
#include <vector>

/// Supplies a thin classic nonclient frame only for dialogs explicitly attached by the application.
class DialogFrame {

public:
    /// Applies the theme mode and optional Windows 2000 caption without changing system metrics or client
    /// size.
    static bool Apply(HWND window, bool disableThemes, bool windows2000Style);

    /// Applies dialog-local colors to a control and its children, including owned dropdowns and tooltips.
    static bool ApplyControl(HWND control, HWND dialog);

    /// Returns the dialog's Windows 2000 color, or the native system color outside that mode.
    static COLORREF GetColor(HWND control, int colorIndex);

    /// Returns a brush owned by the dialog, or the native system brush outside Windows 2000 mode.
    static HBRUSH GetBrush(HWND control, int colorIndex);

    /// Maps completed native control drawing to dialog-local colors without changing its font or geometry.
    static void RecolorControl(HWND control, HDC context, const RECT& rectangle);

    /// Converts client bounds to outer bounds using the attached frame and native scrollbars.
    static BOOL AdjustRect(HWND window, RECT* rectangle, DWORD style, DWORD extendedStyle);

private:
    /// Shares caption, button and border geometry between rendering, input and accessibility.
    struct Layout {
        RECT bounds{};
        RECT caption{};
        RECT icon{};
        RECT buttons[3]{};
        int borderX = 0;
        int borderY = 0;
    };

    /// Carries the owning frame and accumulated result while applying colors to child controls.
    struct ColorEnumeration {
        DialogFrame* frame = nullptr;
        bool success = true;
    };

    HWND window = nullptr;
    std::array<HBRUSH, COLOR_MENUBAR + 1> colorBrushes{};
    SIZE frameSize{};
    UINT dpi = 0;
    int captionWidth = 0;
    bool disableThemes = false;
    bool windows2000Style = false;
    bool enabled = false;
    bool updating = false;
    bool active = false;
    int pressed = HTNOWHERE;
    bool pressedInside = false;
    std::vector<HWND> popupControls;

    /// Initializes per-window activation state; the window subclass owns this object.
    explicit DialogFrame(HWND target);

    /// Releases brushes and removes dialog-local state from any remaining owned popup controls.
    ~DialogFrame();

    /// Finds the attached dialog through a control's parent or owner chain.
    static DialogFrame* Find(HWND control);

    /// Applies or restores the shared color component for one control without changing its native content.
    bool ApplyControlColors(HWND control) const;

    /// Enumerates the current child controls while retaining application-owned color previews.
    static BOOL CALLBACK ApplyChildColors(HWND control, LPARAM parameter);

    /// Recolors only the native frame edges and caption buttons, preserving the caption gradient and icon.
    void RecolorFrame(HDC context, const Layout& layout) const;

    /// Maps native edge and button colors inside one nonclient rectangle.
    static void RecolorFrameRectangle(HDC context, const RECT& rectangle);

    /// Reads current metrics and recalculates the frame after theme, metric or DPI changes.
    bool Refresh(bool preserveClient = true);

    /// Calculates physical-pixel bounds, retaining native invisible overhang when maximized.
    Layout GetLayout() const;

    /// Reads DPI-scaled native metrics, using the configured classic caption-button width.
    int Metric(int index) const;

    /// Draws the classic frame with system or Windows 2000 caption styling, retaining native scrollbars
    /// and content.
    void Paint(HDC target = nullptr) const;

    /// Resolves screen coordinates against the same rectangles used for painting.
    LRESULT HitTest(POINT point) const;

    /// Honors window styles, enabled state and the system menu when checking caption commands.
    bool ButtonEnabled(int hit) const;

    /// Selects native frame cursors without invoking the system's separate caption repaint path.
    static bool SetNonClientCursor(int hit);

    /// Cancels only this frame's caption-button capture, leaving native move and resize capture alone.
    void CancelPress();

    /// Handles local nonclient layout and input, preserving native scrollbars and window commands.
    LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam);

    /// Dispatches the attached window and releases its frame object when the window is destroyed.
    static LRESULT CALLBACK SubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData);
};
