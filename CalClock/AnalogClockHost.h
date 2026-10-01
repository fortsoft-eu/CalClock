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

/// Creates and configures a native ClockWndMain child with the requested size, visibility, and second hand.
/// Returns null on failure; the parent or caller is responsible for destroying the returned window.
HWND CreateAnalogClockControl(HWND parent, int x, int y, int size, bool showSeconds, bool visible);

/// Applies implementation-specific instance configuration to an existing native clock control.
bool ConfigureAnalogClockControl(HWND control, int size, bool showSeconds);

/// Updates the native clock instance's second-hand state without recreating it.
/// Returns false if the instance state is unavailable or its profile does not match the requested size.
bool SetAnalogClockSeconds(HWND control, int size, bool showSeconds);

/// Sends the displayed time to the native clock control; ignores a null window handle.
void SetAnalogClockTime(HWND control, const SYSTEMTIME& time);

/// Reads the native clock's background color when supported, otherwise returning the system window color.
COLORREF ReadAnalogClockBackground(HWND control);

/// Renders the native clock into the supplied DC over a packed RGB background, restoring private background state
/// afterward.
bool RenderAnalogClock(HWND control, HDC targetDC, DWORD background);

/// Returns the number of supported native sizes and copies at most capacity entries into sizes when provided.
/// Returns zero if the native clock implementation cannot be loaded.
int GetSupportedAnalogClockSizes(int* sizes, int capacity);

/// Reports whether the selected native size supports a second hand; assumes support if detection fails.
bool AnalogClockSupportsSeconds(int size);

/// Clears cached native clock pointers and profiles and unloads timedate.cpl after its controls have been destroyed.
void ShutdownAnalogClockHost();
