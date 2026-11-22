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

#include "CalClock.h"
#include <regex>
#include <string>
#include "PersistWindowState.h"

/// Stores one session-only search expression together with its six matching options.
struct FindHistoryEntry {
    wchar_t* text;
    DWORD options;
};

/// Identifies one UTF-16 match without retaining pointers into the report buffer.
struct FindTextMatch {
    int start;
    int length;
};

/// Identifies a native regular-expression match, a missing match or a matching failure.
enum class RegexSearchResult {
    Match,
    NotFound,
    Error
};

/// Wraps native C++ regular expressions and localized diagnostics for the search controller.
class RegexSearch {

public:
    /// Compiles a multiline ECMAScript expression with the requested case sensitivity and localizes failures.
    bool Compile(const wchar_t* pattern, bool matchCase);

    /// Finds the next UTF-16 match at or after the offset, preserving preceding context for expression
    /// anchors.
    RegexSearchResult Next(const wchar_t* text, int length, int offset, int* start, int* matchLength);

    /// Returns the localized diagnostic from the last failed compilation or match operation.
    const wchar_t* GetError() const;

private:
    /// Compiled expression and the diagnostic retained from its most recent failure.
    std::wregex expression;
    std::wstring error;

    /// Maps native regular-expression error codes to the application's localized diagnostics.
    void SetError(std::regex_constants::error_type code);
};

/// Owns the modeless search form, session history and matching state for the active form's text edit.
class FindForm {

private:
    HWND window;
    HWND ownerWindow;
    HWND target;
    HWND lastTarget;

    HFONT uiFont;
    PersistWindowState placement;
    SIZE buttonSize;
    UINT templateDpi;
    LONG minimumWidth;
    LONG fixedHeight;
    wchar_t* query;
    FindHistoryEntry history[30];
    FindTextMatch* matches;
    UINT historyCount;
    UINT matchCount;
    UINT matchCapacity;
    int lastMatchStart;
    int lastMatchLength;
    bool ownsUiFont;
    bool matchCase;
    bool backward;
    bool wholeWords;
    bool startsWith;
    bool endsWith;
    bool regularExpression;

    /// Initializes the editable combo, native controls, icons and persisted form placement.
    bool Initialize();

    /// Refreshes caption icons, applies the system font and recalculates native font- and DPI-aware geometry.
    void SetFonts(bool updateUi);

    /// Measures the minimum width and anchors controls without clipping localized option captions.
    void Layout();

    /// Enables Find Next only when a report and a nonempty search expression are available.
    void UpdateFindButton() const;

    /// Disables whole-word and line-edge options while regular expressions are selected.
    void UpdateRegexOptions() const;

    /// Copies pending search text and options, retaining the last query if allocation fails.
    bool ReadOptions();

    /// Returns the six matching options stored with a session history entry.
    DWORD Options() const;

    /// Restores matching options when a search-history item is selected.
    void ApplyOptions(DWORD options) const;

    /// Moves the current expression to the front of the bounded session history.
    bool RememberSearch();

    /// Repopulates the editable combo without changing its current text or text selection.
    void PopulateHistory() const;

    /// Appends one match while checking process-heap allocation and buffer size limits.
    bool AddMatch(int start, int length);

    /// Collects literal matches, optionally restricted to the beginning or end of logical lines.
    bool FindLiteral(wchar_t* report);

    /// Collects native C++ multiline regular-expression matches, including zero-length expressions.
    bool FindRegex(const wchar_t* report);

    /// Selects the next or previous collected match, wrapping once at the ends of the report.
    void SelectMatch(bool reverse);

    /// Restores history options during navigation and selects the text after the choice is committed.
    void ChooseHistory(bool selectText) const;

    /// Closes a user-dismissed form and restores ordinary report-selection visibility.
    INT_PTR HandleClose() const;

    /// Handles combo notifications, search options, Find Next and Close commands.
    INT_PTR HandleCommand(WPARAM wParam);

    /// Applies suggested DPI bounds and refreshes native fonts and geometry.
    INT_PTR HandleDpiChange(LPARAM lParam);

    /// Supplies the measured minimum width while PersistWindowState fixes the form's height.
    INT_PTR HandleMinMax(LPARAM lParam) const;

    /// Preserves the reference form's Insert overwrite mode through native edit selection.
    void PrepareOverwrite(MSG* message) const;

    /// Dispatches native modeless form messages without changing the shared selection component.
    static INT_PTR CALLBACK DialogProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

public:
    /// Initializes forward literal searching and an empty thirty-item session history.
    FindForm();

    /// Closes the form and releases its font, expression, history and match buffers.
    ~FindForm();

    /// Uses the active form's text edit and invalidates the last zero-length match after retargeting.
    void SetTarget(HWND edit);

    /// Reports whether the selected edit still exists and contains searchable text.
    bool CanSearch() const;

    /// Retains logical search state when an existing report edit is replaced for native style changes.
    void ReplaceTarget(HWND original, HWND replacement);

    /// Opens or activates the modeless search form only when its selected edit contains text.
    void Show(HWND owner);

    /// Closes the form while retaining expressions and options only in this running instance.
    void Close() const;

    /// Searches the selected text edit, reversing the selected direction for Find Previous or Shift.
    void FindNext(HWND owner, bool reverse);

    /// Refreshes all captions and their geometry after a committed interface-language change.
    void RefreshLanguage();

    /// Applies the current application font, theme and native control measurements.
    void RefreshStyle();

    /// Routes search shortcuts and native dialog navigation only for this form and its children.
    bool Translate(MSG* message);

    /// Returns this viewer's search form or null when it is closed.
    HWND GetWindow() const;
};
