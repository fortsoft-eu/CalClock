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
 * Last modified for version 1.5.1.0
 */

#pragma once

#include <windows.h>

/// Suspends painting for a visible window during a batch of updates and requests a repaint on destruction.
/// Leaves initially hidden windows untouched so restoring redraw cannot make them visible.
class WindowRedrawScope {

public:
    /// Disables redraw only when target is a valid, currently visible window.
    explicit WindowRedrawScope(HWND target);

    /// Reenables redraw if the target still exists and invalidates its frame and child controls.
    ~WindowRedrawScope();

    /// Prevents copying responsibility for restoring window redraw.
    WindowRedrawScope(const WindowRedrawScope&) = delete;

    /// Prevents copying responsibility for restoring window redraw.
    WindowRedrawScope& operator=(const WindowRedrawScope&) = delete;

private:
    HWND window = nullptr;
};
