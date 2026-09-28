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
 * Last modified for version 1.5.0.0
 */

#pragma once

#include <windows.h>
#include <vector>

/// Associates a widget ID with its screen-space rectangle for arrangement without moving live windows.
struct WidgetPlacement {
    int id = 0;
    RECT rect = {};
};

/// Arranges widget rectangles on a common grid inside the work area.
/// Leaves items unchanged on failure; anchorId identifies a fixed widget or uses the work-area origin when absent.
bool ArrangeWidgetPlacements(std::vector<WidgetPlacement>* items, const RECT& work, int anchorId = -1);
/// Snaps a proposed widget position to nearby work-area edges within snapDistance pixels.
POINT SnapWidgetPositionToWorkArea(const RECT& widgetRect, const RECT& work, POINT position, int snapDistance);
/// Calculates a resized widget's position while preserving its attachment to nearby work-area edges.
/// Optionally reports whether each axis was attached; prefers left and top when both opposite edges qualify.
POINT PreserveWidgetWorkAreaAttachment(const RECT& widgetRect, const RECT& work, int newWidth, int newHeight, int snapDistance,
    bool* horizontalAttachment = nullptr, bool* verticalAttachment = nullptr);
