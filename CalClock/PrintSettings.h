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
 * Last modified for version 1.7.2.5
 */

#pragma once

#include <windows.h>
#include <unknwn.h>

/// Retains one native RichEdit character-format run for the modern vector-printing path.
struct PrintTextRun {
    UINT start;
    UINT length;
    COLORREF color;
    LONG heightTwips;
    LONG weight;
    bool italic;
    bool underline;
    bool strikeOut;
    wchar_t family[LF_FACESIZE];
};

/// Owns a printer context and a report snapshot for one cancellable background print job.
struct PrintJob {
    HWND target;
    HDC printer;
    wchar_t* report;
    BYTE* richText;
    ULONG richTextSize;
    PrintTextRun* formats;
    UINT formatCount;
    HRESULT(*formatLayout)(const PrintJob* job, IUnknown* layout, IUnknown* context, UINT start, UINT length);
    LOGFONTW font;
    RECT margins;
    UINT fontDpi;
    wchar_t title[MAX_PATH];
    volatile LONG canceled;
    bool printToFile;
    bool success;
};

/// Stores one wrapped plain-text line as a UTF-16 source offset and length.
struct PrintLine {
    int start;
    int length;
};

/// Owns printer selections and page margins for the compatible native print and page setup dialogs.
class PrintSettings {

private:
    HGLOBAL deviceMode;
    HGLOBAL deviceNames;
    RECT margins;

    /// Replaces the retained printer configuration and releases the previous memory blocks.
    void ReplaceDevice(HGLOBAL mode, HGLOBAL names);

public:
    /// Initializes empty printer selections and margins of 12.7 mm on every side.
    PrintSettings();

    /// Releases the retained printer configuration buffers.
    ~PrintSettings();

    /// Opens native Page Setup with caller-supplied failure text and commits only accepted settings.
    bool PageSetup(HWND owner, const wchar_t* failureText, wchar_t* error, int capacity);

    /// Returns a caller-owned printer context, using caller-supplied failure text for dialog errors.
    HDC ChoosePrinter(HWND owner, bool* printToFile, const wchar_t* failureText, wchar_t* error,
            int capacity);

    /// Returns page margins in hundredths of a millimeter.
    RECT GetMargins() const;

    /// Copies the retained native printer settings into the supplied DEVMODE structure.
    bool GetDeviceMode(DEVMODEW& mode) const;
};

/// Paginates captured rich or plain text and renders pages using retained font and printer metrics.
class PrintLayout {

private:
    HWND richEdit;
    HDC richTarget;
    HFONT font;
    const wchar_t* text;
    RECT richArea;
    RECT richPage;
    RECT area;
    PrintLine* lines;
    UINT lineCount;
    UINT capacity;
    UINT rows;
    LONG lineHeight;

    /// Loads the captured RTF and paginates its native character and paragraph formatting.
    bool InitializeRichText(const PrintJob& job, HDC reference, const RECT& content, int dpiX, int dpiY);

    /// Appends a source text span, growing the line buffer as needed.
    bool AddLine(int start, int length);

    /// Clears pagination and releases the private RichEdit, font and cached line positions.
    void Reset();

public:
    /// Initializes an empty page layout without allocating font or line storage.
    PrintLayout();

    /// Releases the font and line positions owned by the page layout.
    ~PrintLayout();

    /// Measures the captured edit font and wraps its text into pages within the supplied content rectangle.
    bool Initialize(const PrintJob& job, HDC reference, const RECT& content, int dpiX, int dpiY);

    /// Draws one zero-based page with captured rich formatting or the saved plain-text font and line
    /// positions.
    bool DrawPage(HDC output, UINT page) const;

    /// Returns the number of pages in the prepared layout.
    UINT GetPageCount() const;
};

/// Releases an immutable print snapshot and its native resources allocated on the process heap.
void FreePrintJob(PrintJob* job);

/// Converts physical page margins to printer pixels and clips them to the printable area.
RECT PrintContentRect(HDC printer, const RECT& margins);
