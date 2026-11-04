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

#include "SystemDialogTemplate.h"

/// Native monitor handle hidden by SDK headers while targeting Windows NT 4.0.
#if WINVER < 0x0500 && !defined(HMONITOR_DECLARED)
#define HMONITOR_DECLARED
DECLARE_HANDLE(HMONITOR);
#endif

/// Signatures used to resolve optional window and monitor DPI exports without static imports.
typedef UINT(WINAPI* GetDpiForWindowProc)(HWND window);
typedef HMONITOR(WINAPI* MonitorFromWindowProc)(HWND window, DWORD flags);
typedef HRESULT(WINAPI* GetDpiForMonitorProc)(HMONITOR monitor, int type, UINT* dpiX, UINT* dpiY);

/// Byte lengths of the fixed extended-dialog header and extended font attributes.
static const SIZE_T EXTENDED_DIALOG_HEADER_SIZE = 26;
static const SIZE_T EXTENDED_FONT_HEADER_SIZE = 6;

/// System library names and native monitor-DPI query options.
static const wchar_t USER_LIBRARY_NAME[] = L"user32.dll";
static const wchar_t SHCORE_LIBRARY_SUFFIX[] = L"\\shcore.dll";
static const DWORD NEAREST_WINDOW_MONITOR = 0x00000002;
static const int EFFECTIVE_MONITOR_DPI = 0;

/// Returns window or monitor DPI when supported, otherwise DC DPI; a null window uses the screen DC.
/// Returns 96 if the device context or its DPI is unavailable.
UINT GetSystemDialogDpi(HWND window) {
    HMODULE module = GetModuleHandleW(USER_LIBRARY_NAME);
    GetDpiForWindowProc getDpi = nullptr;
    if (module != nullptr) {
        getDpi = reinterpret_cast<GetDpiForWindowProc>(GetProcAddress(module, "GetDpiForWindow"));
    }
    if (getDpi != nullptr && window != nullptr) {
        UINT dpi = getDpi(window);
        if (dpi != 0) {
            return dpi;
        }
    }
    MonitorFromWindowProc monitorFromWindow = module == nullptr
        ? nullptr
        : reinterpret_cast<MonitorFromWindowProc>(GetProcAddress(module, "MonitorFromWindow"));
    if (window != nullptr && monitorFromWindow != nullptr) {
        wchar_t path[MAX_PATH];
        UINT length = GetSystemDirectoryW(path, MAX_PATH);
        if (length != 0 && length + lstrlenW(SHCORE_LIBRARY_SUFFIX) < MAX_PATH) {
            lstrcatW(path, SHCORE_LIBRARY_SUFFIX);
            HMODULE scaling = LoadLibraryW(path);
            if (scaling != nullptr) {
                GetDpiForMonitorProc getMonitorDpi =
                    reinterpret_cast<GetDpiForMonitorProc>(GetProcAddress(scaling, "GetDpiForMonitor"));
                UINT dpiX = 0;
                UINT dpiY = 0;
                bool success = getMonitorDpi != nullptr && SUCCEEDED(getMonitorDpi(
                    monitorFromWindow(window, NEAREST_WINDOW_MONITOR), EFFECTIVE_MONITOR_DPI, &dpiX, &dpiY));
                FreeLibrary(scaling);
                if (success && dpiY != 0) {
                    return dpiY;
                }
            }
        }
    }
    HDC dc = GetDC(window);
    if (dc == nullptr) {
        return 96;
    }
    UINT dpi = GetDeviceCaps(dc, LOGPIXELSY);
    ReleaseDC(window, dc);
    return dpi == 0 ? 96 : dpi;
}

/// Creates the current system message font scaled from system DPI to the target window DPI.
/// Returns a caller-owned font, or null if system metrics or font creation fails.
HFONT CreateSystemDialogFont(HWND window) {
    NONCLIENTMETRICSW metrics = {};
    metrics.cbSize = static_cast<UINT>(FIELD_OFFSET(NONCLIENTMETRICSW, lfMessageFont)
        + sizeof(metrics.lfMessageFont));
    if (!SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, metrics.cbSize, &metrics, 0)) {
        return nullptr;
    }
    UINT dpi = GetSystemDialogDpi(window);
    UINT systemDpi = GetSystemDialogDpi(nullptr);
    metrics.lfMessageFont.lfHeight = MulDiv(metrics.lfMessageFont.lfHeight, dpi, systemDpi);
    metrics.lfMessageFont.lfWidth = MulDiv(metrics.lfMessageFont.lfWidth, dpi, systemDpi);
    return CreateFontIndirectW(&metrics.lfMessageFont);
}

/// Skips one empty, ordinal, or null-terminated UTF-16 field; returns false if its words are truncated.
static bool SkipDialogField(const WORD*& cursor, const WORD* end) {
    if (cursor == end) {
        return false;
    }
    WORD value = *cursor++;
    if (value == 0xFFFF) {
        if (cursor == end) {
            return false;
        }
        ++cursor;
        return true;
    }
    while (value != 0) {
        if (cursor == end) {
            return false;
        }
        value = *cursor++;
    }
    return true;
}

/// Converts the font's measured character height, excluding internal leading, to points at the owner's DPI.
/// Returns zero if the device context or font metrics cannot be obtained.
static UINT DialogFontPoints(HWND owner, HFONT font) {
    HDC dc = GetDC(owner);
    if (dc == nullptr) {
        return 0;
    }
    HGDIOBJ previous = SelectObject(dc, font);
    TEXTMETRICW metrics = {};
    BOOL measured = GetTextMetricsW(dc, &metrics);
    SelectObject(dc, previous);
    ReleaseDC(owner, dc);
    if (measured) {
        return MulDiv(metrics.tmHeight - metrics.tmInternalLeading, 72, GetSystemDialogDpi(owner));
    }
    return 0;
}

/// Copies an extended dialog resource without DS_SETFONT and inserts the supplied or current system message
/// font. Preserves menu, class, title, control data and DWORD alignment; the supplied font remains
/// caller-owned. Returns a template to free with HeapFree(GetProcessHeap(), 0, ...), or null on resource,
/// format, font or allocation failure.
DLGTEMPLATE* LoadSystemDialogTemplate(HINSTANCE instance, UINT resourceId, HWND owner, HFONT dialogFont) {
    HRSRC resource = FindResourceW(instance, MAKEINTRESOURCEW(resourceId), RT_DIALOG);
    HGLOBAL loaded = resource == nullptr ? nullptr : LoadResource(instance, resource);
    DWORD size = resource == nullptr ? 0 : SizeofResource(instance, resource);
    const BYTE* source = loaded == nullptr ? nullptr : static_cast<const BYTE*>(LockResource(loaded));
    if (source == nullptr
            || size < EXTENDED_DIALOG_HEADER_SIZE
            || reinterpret_cast<const WORD*>(source)[1] != 0xFFFF
            || *reinterpret_cast<const DWORD*>(source + 12) & DS_SETFONT) {
        return nullptr;
    }
    const WORD* cursor = reinterpret_cast<const WORD*>(source + EXTENDED_DIALOG_HEADER_SIZE);
    const WORD* end = reinterpret_cast<const WORD*>(source + size);
    for (UINT index = 0; index < 3; index++) {
        if (!SkipDialogField(cursor, end)) {
            return nullptr;
        }
    }
    SIZE_T fontOffset = reinterpret_cast<const BYTE*>(cursor) - source;
    SIZE_T controlsOffset = *reinterpret_cast<const WORD*>(source + 16) == 0
        ? fontOffset
        : fontOffset + 3 & ~static_cast<SIZE_T>(3);
    if (controlsOffset > size) {
        return nullptr;
    }
    HFONT font = dialogFont == nullptr ? CreateSystemDialogFont(owner) : dialogFont;
    LOGFONTW description = {};
    UINT points = font == nullptr ? 0 : DialogFontPoints(owner, font);
    bool described = font != nullptr && GetObjectW(font, sizeof(description), &description);
    if (dialogFont == nullptr && font != nullptr) {
        DeleteObject(font);
    }
    if (!described || points == 0 || points >= 0x7FFF) {
        return nullptr;
    }
    SIZE_T faceBytes = (lstrlenW(description.lfFaceName) + 1) * sizeof(wchar_t);
    SIZE_T fontSize = EXTENDED_FONT_HEADER_SIZE + faceBytes;
    SIZE_T newControlsOffset = fontOffset + fontSize + 3 & ~static_cast<SIZE_T>(3);
    SIZE_T newSize = newControlsOffset + size - controlsOffset;
    BYTE* copy = static_cast<BYTE*>(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, newSize));
    if (copy == nullptr) {
        return nullptr;
    }
    CopyMemory(copy, source, fontOffset);
    *reinterpret_cast<DWORD*>(copy + 12) |= DS_SETFONT;
    WORD* attributes = reinterpret_cast<WORD*>(copy + fontOffset);
    attributes[0] = static_cast<WORD>(points);
    attributes[1] = static_cast<WORD>(description.lfWeight);
    BYTE* flags = reinterpret_cast<BYTE*>(attributes + 2);
    flags[0] = description.lfItalic;
    flags[1] = description.lfCharSet;
    CopyMemory(copy + fontOffset + EXTENDED_FONT_HEADER_SIZE, description.lfFaceName, faceBytes);
    CopyMemory(copy + newControlsOffset, source + controlsOffset, size - controlsOffset);
    return reinterpret_cast<DLGTEMPLATE*>(copy);
}
