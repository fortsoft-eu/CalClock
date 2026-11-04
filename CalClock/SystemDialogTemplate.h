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
 * Last modified for version 1.7.1.3
 */

#pragma once

#include <windows.h>

/// Returns window or monitor DPI when supported, otherwise DC DPI; a null window uses the screen DC.
/// Returns 96 if the device context or its DPI is unavailable.
UINT GetSystemDialogDpi(HWND window);

/// Creates the current system message font scaled from system DPI to the target window DPI.
/// Returns a caller-owned font, or null if system metrics or font creation fails.
HFONT CreateSystemDialogFont(HWND window);

/// Uses a supplied or system font for the copied dialog template; a supplied font remains owned by the
/// caller.
DLGTEMPLATE* LoadSystemDialogTemplate(HINSTANCE instance, UINT resourceId, HWND owner,
    HFONT dialogFont = nullptr);
