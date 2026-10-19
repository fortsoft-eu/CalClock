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
 * Last modified for version 1.6.0.1
 */

#pragma once

#include "Localization.h"
#include <windows.h>
#include <dxgi1_6.h>
#include <string>
#include <vector>

/// Geometry and device identity of one enumerated display monitor.
struct DisplayMonitor {
    RECT rect{};
    RECT work{};
    std::wstring device;
    bool primary = false;
};

/// Current monitor metadata, retaining unknown values when the operating system cannot report them.
struct MonitorDetails {
    std::wstring model;
    DISPLAYCONFIG_RATIONAL refreshRate{};
    UINT bitsPerColor = 0;
    UINT bitsPerPixel = 0;
    DISPLAYCONFIG_COLOR_ENCODING colorEncoding = DISPLAYCONFIG_COLOR_ENCODING_FORCE_UINT32;
    DXGI_COLOR_SPACE_TYPE colorSpace = DXGI_COLOR_SPACE_CUSTOM;
};

/// Removes the Win32 device-namespace prefix only from the displayed monitor name.
std::wstring MonitorDisplayName(const std::wstring& device);

/// Collects current monitor metadata while retaining compatibility with Windows Vista.
std::vector<MonitorDetails> ReadMonitorDetails(const std::vector<DisplayMonitor>& monitors);

/// Formats the current refresh rate using the user's decimal separator and retaining fractional Hertz.
std::wstring MonitorRefreshRateText(const MonitorDetails& details);

/// Formats channel depth when available, otherwise explicitly identifies legacy pixel depth.
std::wstring MonitorBitDepthText(const MonitorDetails& details, AppLanguage language);

/// Names the actual output color encoding without guessing from desktop pixel depth.
const wchar_t* MonitorColorFormatText(DISPLAYCONFIG_COLOR_ENCODING encoding);

/// Names output color primaries and transfer characteristics reported by DXGI.
const wchar_t* MonitorColorSpaceText(DXGI_COLOR_SPACE_TYPE colorSpace);
