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
 * Last modified for version 1.7.3.2
 */

#pragma once

#include <windows.h>
#include <string>
#include <vector>

/// Extracts the embedded icon library and owns all icons shared by application windows and controls.
class ProgramIcons {
    struct IconEntry {
        HICON icon;
        int index;
        int width;
        int height;
    };

public:
    ProgramIcons() = default;
    ~ProgramIcons();
    ProgramIcons(const ProgramIcons&) = delete;
    ProgramIcons& operator=(const ProgramIcons&) = delete;

    /// Validates and extracts the bundled DLL, reusing identical cached bytes and loaded icons.
    HRESULT Initialize(HINSTANCE instance, const std::wstring& cacheRoot);

    /// Returns a shared cached icon; this class retains ownership and callers must not destroy it.
    HICON LoadIconAtIndex(int index, int width, int height) const;

    /// Applies shared small and large icons using native metrics for the target window's current DPI.
    void Apply(HWND window, int iconIndex = 0) const;

    /// Returns the extracted library's absolute path after successful initialization.
    const std::wstring& GetPath() const;

private:
    std::wstring path;
    mutable std::vector<IconEntry> icons;

    void ClearIcons();
};
