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

#pragma once

#include <windows.h>
#include <array>

/// Marks a dialog whose classic style is enabled.
inline constexpr wchar_t CLASSIC_STYLE_ENABLED_PROPERTY[] = L"CalClock.ClassicStyle.Enabled";

/// Enables classic control colors for controls attached to the marked dialog.
inline constexpr wchar_t CLASSIC_CONTROL_COLORS_PROPERTY[] = L"CalClock.ClassicStyle.ControlColors";

/// Applies a local Windows 2000 control palette and restores saved native colors when detached.
class ControlColors {

public:
    /// Enables or removes local colors; sets changed when state changes and reports installation failures.
    static bool Apply(HWND window, HWND owner, bool enabled, bool& changed);

    /// Removes local color handling, restores eligible saved colors and requests native repainting.
    static void Restore(HWND window);

private:
    /// Identifies native controls requiring color properties or direct-paint handling.
    enum class Kind {
        Other,
        Edit,
        ListView,
        TreeView,
        Progress
    };

    HWND window = nullptr;
    HWND owner = nullptr;
    HBRUSH faceBrush = nullptr;
    HBRUSH backgroundBrush = nullptr;
    Kind kind = Kind::Other;
    bool target = false;
    bool paintTarget = false;
    bool scrollRecolorPending = false;
    std::array<COLORREF, 3> previousColors{};

    /// Records the target and controlling window and creates the owned background brushes.
    ControlColors(HWND window, HWND owner);

    /// Releases the background brushes owned by this control state.
    ~ControlColors();

    /// Returns the attached subclass state, or null when the window has no local color state.
    static ControlColors* Find(HWND window);

    /// Reuses or installs state on the current thread, pinning the callback module; returns null on failure.
    static ControlColors* Attach(HWND window, HWND owner);

    /// Observes mouse moves consumed by native scrollbar tracking and queues the existing color correction.
    static LRESULT CALLBACK ScrollMessageFilter(int code, WPARAM wParam, LPARAM lParam);

    /// Preserves native handling while recoloring enabled targets and releasing state on destruction.
    static LRESULT CALLBACK Procedure(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR data);

    /// Saves and applies native color properties, or restores those still holding the applied values.
    void SetColors(bool enabled);

    /// Maps exact system-color pixels within the clipped client or nonclient area to the classic palette.
    void Recolor(HDC dc, bool nonClient) const;

    /// Recolors native scrollbars after scrolling, range updates or deferred tracking painting.
    void RecolorScrollBars() const;

    /// Supplies owned brushes and text colors for targets of this owner; otherwise preserves the result.
    LRESULT ColorControl(UINT message, WPARAM wParam, LPARAM lParam, LRESULT result) const;
};
