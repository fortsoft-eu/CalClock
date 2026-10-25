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
 * Last modified for version 1.6.1.3
 */

#include "SystemDialogTemplate.h"
#include <cwchar>

static const SIZE_T EXTENDED_DIALOG_HEADER_SIZE = 26;
static const SIZE_T EXTENDED_FONT_HEADER_SIZE = 6;

UINT GetSystemDialogDpi(HWND window) {
    HDC dc = GetDC(window);
    if (dc == nullptr) {
        return 96;
    }
    UINT dpi = GetDeviceCaps(dc, LOGPIXELSY);
    ReleaseDC(window, dc);
    return dpi;
}

HFONT CreateSystemDialogFont(HWND window) {
    NONCLIENTMETRICSW metrics = {};
    metrics.cbSize = sizeof(metrics);
    if (!SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof(metrics), &metrics, 0)) {
        return nullptr;
    }
    UINT dpi = GetSystemDialogDpi(window);
    UINT systemDpi = GetSystemDialogDpi(nullptr);
    metrics.lfMessageFont.lfHeight = MulDiv(metrics.lfMessageFont.lfHeight, dpi, systemDpi);
    metrics.lfMessageFont.lfWidth = MulDiv(metrics.lfMessageFont.lfWidth, dpi, systemDpi);
    return CreateFontIndirectW(&metrics.lfMessageFont);
}

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
    return measured ? MulDiv(metrics.tmHeight - metrics.tmInternalLeading, 72, GetSystemDialogDpi(owner)) : 0;
}

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
    SIZE_T controlsOffset = fontOffset + 3 & ~static_cast<SIZE_T>(3);
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
    SIZE_T faceBytes = (wcslen(description.lfFaceName) + 1) * sizeof(wchar_t);
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
