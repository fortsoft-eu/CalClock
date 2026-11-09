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
 * Last modified for version 1.7.2.1
 */

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "TimeCalculatorForm.h"
#include "CalClock.h"
#include "CalendarLocaleScope.h"
#include "DialogFrame.h"
#include "Localization.h"
#include "SelectionEdit.h"
#include "SettingsEdit.h"
#include "SettingsStorage.h"
#include "SystemDialogTemplate.h"
#include "WindowRedrawScope.h"
#include "resource.h"
#include <algorithm>
#include <cwchar>
#include <objbase.h>
#include <uxtheme.h>
#include <vsstyle.h>
#include <windowsx.h>

static constexpr UINT_PTR CALCULATOR_TIMER = 1;
static constexpr UINT CALCULATOR_CALCULATE = WM_APP + 310;
static constexpr UINT CALCULATOR_READY = WM_APP + 311;
static constexpr UINT_PTR CALCULATOR_LOCALE_SUBCLASS = 1;
static constexpr int CALCULATOR_SELECT_ALL = 3390;
static constexpr int CALCULATOR_RESOURCES[] = {
    IDD_CALCULATOR_INTERVAL,
    IDD_CALCULATOR_ROUND,
    IDD_CALCULATOR_PRESETS,
    IDD_CALCULATOR_HIGHLIGHTS
};

static constexpr TextId CALCULATOR_TABS[] = {
    TXT_CALCULATOR_INTERVAL,
    TXT_CALCULATOR_ROUND,
    TXT_CALCULATOR_PRESETS,
    TXT_CALCULATOR_HIGHLIGHTS
};

static constexpr DWORD CALCULATOR_HIGHLIGHT_FLAGS[] = {
    CALCULATOR_HIGHLIGHT_START,
    CALCULATOR_HIGHLIGHT_ROUND,
    CALCULATOR_HIGHLIGHT_FIRST_WEEKS,
    CALCULATOR_HIGHLIGHT_ANNIVERSARIES,
    CALCULATOR_HIGHLIGHT_ONES,
    CALCULATOR_HIGHLIGHT_TWOS,
    CALCULATOR_HIGHLIGHT_THREES,
    CALCULATOR_HIGHLIGHT_FOURS,
    CALCULATOR_HIGHLIGHT_FIVES,
    CALCULATOR_HIGHLIGHT_SIXES,
    CALCULATOR_HIGHLIGHT_SEVENS,
    CALCULATOR_HIGHLIGHT_EIGHTS,
    CALCULATOR_HIGHLIGHT_NINES
};

static constexpr TextId CALCULATOR_HIGHLIGHT_LABELS[] = {
    TXT_CALCULATOR_HIGHLIGHT_START,
    TXT_CALCULATOR_HIGHLIGHT_ROUND,
    TXT_CALCULATOR_HIGHLIGHT_WEEKS,
    TXT_CALCULATOR_HIGHLIGHT_ANNIVERSARIES,
    TXT_CALCULATOR_HIGHLIGHT_DIGITS,
    TXT_CALCULATOR_HIGHLIGHT_DIGITS,
    TXT_CALCULATOR_HIGHLIGHT_DIGITS,
    TXT_CALCULATOR_HIGHLIGHT_DIGITS,
    TXT_CALCULATOR_HIGHLIGHT_DIGITS,
    TXT_CALCULATOR_HIGHLIGHT_DIGITS,
    TXT_CALCULATOR_HIGHLIGHT_DIGITS,
    TXT_CALCULATOR_HIGHLIGHT_DIGITS,
    TXT_CALCULATOR_HIGHLIGHT_DIGITS
};

static constexpr unsigned int CALCULATOR_HIGHLIGHT_DIGITS[] = { 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
static constexpr int CALCULATOR_INPUT_PAGES[] = { 0, 0, 1, 2 };
static constexpr int CALCULATOR_INPUT_IDS[] = { ID_CALC_FROM, ID_CALC_TO, ID_CALC_START, ID_CALC_DATE };
static constexpr TextId CALCULATOR_UNITS[] = {
    TXT_CALCULATOR_HOURS,
    TXT_CALCULATOR_DAYS,
    TXT_CALCULATOR_WEEKS,
    TXT_CALCULATOR_MONTHS,
    TXT_CALCULATOR_YEARS
};

/// Skips one trusted resource-template string or ordinal without copying the resource.
static const WORD* SkipCalculatorTemplateString(const WORD* value) {
    if (*value == 0xFFFF) {
        return value + 2;
    }
    while (*value != 0) {
        value++;
    }
    return value + 1;
}

/// Updates text only when its value changes, avoiding timer-driven erasing of unchanged results.
static void SetCalculatorText(HWND parent, int id, const std::wstring& text) {
    HWND control = GetDlgItem(parent, id);
    if (control != nullptr && GetControlText(control) != text) {
        SetWindowTextW(control, text.c_str());
    }
}

/// Compares normalized local timestamps without applying a timezone conversion.
static int CompareCalculatorDates(const SYSTEMTIME& first, const SYSTEMTIME& second) {
    FILETIME left = {};
    FILETIME right = {};
    SystemTimeToFileTime(&first, &left);
    SystemTimeToFileTime(&second, &right);
    return CompareFileTime(&left, &right);
}

/// Formats local dates and times, retaining seconds and milliseconds when present.
static std::wstring FormatCalculatorDate(const SYSTEMTIME& value, bool includeTime,
        const wchar_t* locale = GetLanguageLocale(appLanguage)) {
    int count = GetDateFormatEx(locale, DATE_SHORTDATE, &value, nullptr, nullptr, 0, nullptr);
    std::wstring text(count > 0 ? count : 1, L'\0');
    if (count > 0) {
        GetDateFormatEx(locale, DATE_SHORTDATE, &value, nullptr, text.data(), count, nullptr);
    }
    text.resize(wcslen(text.c_str()));
    if (includeTime) {
        wchar_t time[24] = {};
        if (value.wSecond != 0 || value.wMilliseconds != 0) {
            swprintf_s(time, L" %02u:%02u:%02u.%03u", value.wHour, value.wMinute,
                value.wSecond, value.wMilliseconds);
        } else {
            swprintf_s(time, L" %02u:%02u", value.wHour, value.wMinute);
        }
        text += time;
    }
    return text;
}

/// Resolves exactly the same zone keys offered in the application's Settings selectors.
static const DYNAMIC_TIME_ZONE_INFORMATION* CalculatorZone(const std::wstring& key,
        const std::vector<DYNAMIC_TIME_ZONE_INFORMATION>& zones = timeZones) {
    for (const DYNAMIC_TIME_ZONE_INFORMATION& zone : zones) {
        if (_wcsicmp(zone.TimeZoneKeyName, key.c_str()) == 0) {
            return &zone;
        }
    }
    return nullptr;
}

/// Formats the offset of a real instant, independently of the current date's seasonal offset.
static std::wstring CalculatorOffset(const SYSTEMTIME& utc, const SYSTEMTIME& local) {
    FILETIME first = {};
    FILETIME second = {};
    SystemTimeToFileTime(&utc, &first);
    SystemTimeToFileTime(&local, &second);
    ULARGE_INTEGER left = { first.dwLowDateTime, first.dwHighDateTime };
    ULARGE_INTEGER right = { second.dwLowDateTime, second.dwHighDateTime };
    LONGLONG minutes = (static_cast<LONGLONG>(right.QuadPart) - static_cast<LONGLONG>(left.QuadPart))
        / 600000000;
    wchar_t sign = minutes < 0 ? L'-' : L'+';
    minutes = std::abs(minutes);
    wchar_t text[32] = {};
    swprintf_s(text, L"UTC%c%02lld:%02lld", sign, minutes / 60, minutes % 60);
    return text;
}

/// Shows the actual UTC instant and zone name, including the name behind the current-Windows selector.
static std::wstring CalculatorUtcText(const SYSTEMTIME& utc, const std::wstring& key,
        const std::vector<DYNAMIC_TIME_ZONE_INFORMATION>& zones = timeZones) {
    wchar_t text[40] = {};
    swprintf_s(text, L"%04u-%02u-%02u %02u:%02u:%02u.%03u UTC", utc.wYear, utc.wMonth, utc.wDay, utc.wHour,
        utc.wMinute, utc.wSecond, utc.wMilliseconds);
    std::wstring name = key;
    const DYNAMIC_TIME_ZONE_INFORMATION* zone = CalculatorZone(key, zones);
    if (_wcsicmp(key.c_str(), SYSTEM_TIME_ZONE_KEY) == 0) {
        TIME_ZONE_INFORMATION current = {};
        if (GetTimeZoneInformation(&current) != TIME_ZONE_ID_INVALID) {
            name = current.StandardName;
        }
    } else if (zone != nullptr) {
        name = zone->StandardName;
    }
    return text + (L" — " + name);
}

/// Formats a saved instant in its display zone while retaining the distinguishing UTC offset.
static std::wstring FormatCalculatorPreset(const TimeCalculatorPreset& preset,
        const std::vector<DYNAMIC_TIME_ZONE_INFORMATION>& zones, const wchar_t* locale) {
    const DYNAMIC_TIME_ZONE_INFORMATION* zone = CalculatorZone(preset.zone, zones);
    SYSTEMTIME local = {};
    if (zone == nullptr || !ConvertUtcToTimeZone(*zone, preset.time, &local)) {
        return CalculatorUtcText(preset.time, preset.zone, zones);
    }
    return FormatCalculatorDate(local, true, locale) + L" " + CalculatorOffset(preset.time, local);
}

/// Formats nonzero components in descending units using localized, inflection-independent abbreviations.
static std::wstring FormatCalculatorParts(const ULONGLONG* parts) {
    std::wstring source = T(TXT_CALCULATOR_UNITS);
    std::wstring units[TIME_CALCULATOR_PART_COUNT];
    size_t start = 0;
    for (std::wstring& unit : units) {
        size_t end = source.find(L'|', start);
        unit = source.substr(start, end - start);
        start = end == std::wstring::npos ? source.size() : end + 1;
    }
    const int order[] = { 4, 3, 2, 1, 0, 5 };
    std::wstring text;
    for (int index : order) {
        if (parts[index] != 0) {
            if (!text.empty()) {
                text += L", ";
            }
            text += std::to_wstring(parts[index]) + L" " + units[index];
        }
    }
    if (!text.empty()) {
        text = L"(" + text + L")";
    }
    return text;
}

/// Reads an already restored RC control rectangle in its parent dialog's coordinates.
static RECT CalculatorControlBounds(HWND parent, int id) {
    RECT bounds = {};
    GetWindowRect(GetDlgItem(parent, id), &bounds);
    MapWindowPoints(HWND_DESKTOP, parent, reinterpret_cast<POINT*>(&bounds), 2);
    return bounds;
}

/// Aligns a date picker through its native text-content rectangle and the adjacent label's current font.
static void AlignCalculatorDatePicker(HWND picker, HWND label) {
    HDC dc = GetDC(picker);
    if (dc == nullptr) {
        return;
    }
    HFONT font = reinterpret_cast<HFONT>(SendMessageW(picker, WM_GETFONT, 0, 0));
    HGDIOBJ previous = SelectObject(dc, font);
    TEXTMETRICW metrics = {};
    bool measured = GetTextMetricsW(dc, &metrics) != FALSE;
    SelectObject(dc, previous);
    RECT content = {};
    GetClientRect(picker, &content);
    HTHEME theme = GetWindowTheme(picker);
    if (theme != nullptr) {
        RECT native = content;
        GetThemeBackgroundContentRect(theme, dc, DP_DATETEXT, DPDT_NORMAL, &native, &content);
    }
    ReleaseDC(picker, dc);
    if (!measured) {
        return;
    }
    AlignSettingsControl(picker, label);
    int offset = content.top + (content.bottom - content.top - metrics.tmHeight) / 2;
    RECT bounds = {};
    GetWindowRect(picker, &bounds);
    MapWindowPoints(HWND_DESKTOP, GetParent(picker), reinterpret_cast<POINT*>(&bounds), 2);
    SetWindowPos(picker, nullptr, bounds.left, bounds.top - offset, 0, 0,
        SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS);
}

/// Applies the dialog palette to a native calendar and removes its extra border in classic modes.
static void StyleCalculatorCalendar(HWND calendar, HWND owner) {
    bool classic = GetWindowTheme(calendar) == nullptr;
    MonthCal_SetCalendarBorder(calendar, classic, 0);
    if (classic) {
        const int colors[] = {
            COLOR_WINDOW,
            COLOR_WINDOWTEXT,
            COLOR_HIGHLIGHT,
            COLOR_HIGHLIGHTTEXT,
            COLOR_WINDOW,
            COLOR_GRAYTEXT
        };
        for (int index = 0; index < ARRAYSIZE(colors); index++) {
            MonthCal_SetColor(calendar, index, DialogFrame::GetColor(owner, colors[index]));
        }
    }
}

/// Reads the classic picker's text area, excluding its native border and drop-down button.
static RECT CalculatorPickerTextRect(HWND picker) {
    RECT text = {};
    GetClientRect(picker, &text);
    InflateRect(&text, -GetSystemMetrics(SM_CXEDGE), -GetSystemMetrics(SM_CYEDGE));
    DATETIMEPICKERINFO information = { sizeof(information) };
    DateTime_GetDateTimePickerInfo(picker, &information);
    text.right = std::min(text.right, information.rcButton.left);
    return text;
}

/// Adds exactly one blank pixel before native picker text without moving its border or drop-down button.
static void InsetCalculatorPickerText(HWND picker, HDC dc) {
    RECT text = CalculatorPickerTextRect(picker);
    if (text.right - text.left <= 1 || text.bottom <= text.top) {
        return;
    }
    BitBlt(dc, text.left + 1, text.top, text.right - text.left - 1, text.bottom - text.top, dc, text.left,
        text.top, SRCCOPY);
    text.right = text.left + 1;
    int background = IsWindowEnabled(picker) ? COLOR_WINDOW : COLOR_BTNFACE;
    FillRect(dc, &text, DialogFrame::GetBrush(picker, background));
}

/// Preserves native popup margins while fitting the classic calendar before Windows paints the drop-down.
static LRESULT CALLBACK CalculatorPopupProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
    UINT_PTR subclassId, DWORD_PTR referenceData) {
    HWND calendar = reinterpret_cast<HWND>(referenceData);
    if (message == WM_WINDOWPOSCHANGING) {
        WINDOWPOS* position = reinterpret_cast<WINDOWPOS*>(lParam);
        RECT minimum = {};
        if ((position->flags & SWP_NOSIZE) == 0 && MonthCal_GetMinReqRect(calendar, &minimum)) {
            RECT bounds = {};
            RECT content = {};
            GetWindowRect(window, &bounds);
            GetWindowRect(calendar, &content);
            int horizontalMargin = bounds.right - bounds.left - (content.right - content.left);
            int verticalMargin = bounds.bottom - bounds.top - (content.bottom - content.top);
            LONG todayWidth = static_cast<LONG>(MonthCal_GetMaxTodayWidth(calendar));
            int width = std::max(minimum.right - minimum.left, todayWidth) + horizontalMargin;
            int height = minimum.bottom - minimum.top + verticalMargin;
            position->cx = std::max(position->cx, width);
            position->cy = std::max(position->cy, height);
            RECT proposed = {
                position->x,
                position->y,
                position->x + position->cx,
                position->y + position->cy
            };
            MONITORINFO monitor = { sizeof(monitor) };
            if ((position->flags & SWP_NOMOVE) == 0
                    && GetMonitorInfoW(MonitorFromRect(&proposed, MONITOR_DEFAULTTONEAREST), &monitor)) {
                position->x = std::max(monitor.rcWork.left,
                    std::min<LONG>(position->x, monitor.rcWork.right - position->cx));
                position->y = std::max(monitor.rcWork.top,
                    std::min<LONG>(position->y, monitor.rcWork.bottom - position->cy));
            }
        }
    }
    if (message == WM_NCDESTROY) {
        RemoveWindowSubclass(window, CalculatorPopupProc, subclassId);
    }
    return DefSubclassProc(window, message, wParam, lParam);
}

/// Keeps native picker and calendar formatting in the application language for every paint and input message.
static LRESULT CALLBACK CalculatorCalendarProc(HWND control, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData) {
    CalendarLocaleScope locale(GetLanguageLocale(appLanguage));
    bool inset = referenceData != 0 && GetWindowTheme(control) == nullptr;
    if (inset && message == WM_PAINT && wParam == 0) {
        PAINTSTRUCT paint = {};
        HDC target = BeginPaint(control, &paint);
        if (target == nullptr) {
            return 0;
        }
        RECT client = {};
        GetClientRect(control, &client);
        HDC dc = nullptr;
        HPAINTBUFFER buffer = BeginBufferedPaint(target, &client, BPBF_TOPDOWNDIB, nullptr, &dc);
        if (buffer == nullptr) {
            dc = target;
        }
        DefSubclassProc(control, WM_PRINTCLIENT, reinterpret_cast<WPARAM>(dc), PRF_CLIENT | PRF_ERASEBKGND);
        InsetCalculatorPickerText(control, dc);
        if (buffer != nullptr) {
            EndBufferedPaint(buffer, TRUE);
        }
        EndPaint(control, &paint);
        return 0;
    }
    if (inset && message == WM_ERASEBKGND) {
        return TRUE;
    }
    if (inset
        && (message == WM_LBUTTONDOWN
            || message == WM_LBUTTONDBLCLK
            || message == WM_LBUTTONUP
            || message == WM_MOUSEMOVE)) {
        POINT point = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
        RECT text = CalculatorPickerTextRect(control);
        if (PtInRect(&text, point) && point.x > text.left) {
            lParam = MAKELPARAM(point.x - 1, point.y);
        }
    }
    if (message == WM_NCDESTROY) {
        RemoveWindowSubclass(control, CalculatorCalendarProc, subclassId);
    }
    LRESULT result = DefSubclassProc(control, message, wParam, lParam);
    if (inset && (message == WM_PRINT || message == WM_PRINTCLIENT || message == WM_PAINT && wParam != 0)) {
        InsetCalculatorPickerText(control, reinterpret_cast<HDC>(wParam));
    }
    return result;
}

/// Returns the modeless window while it exists.
HWND TimeCalculatorForm::GetWindow() const {
    return window;
}

/// Exposes window settings to the selected application storage backend, excluding saved user data.
const TimeCalculatorState& TimeCalculatorForm::GetState() const {
    return state;
}

/// Exposes saved user data only to explicit exports, separately from the window-settings snapshot.
const std::vector<TimeCalculatorPreset>& TimeCalculatorForm::GetPresets() const {
    return presets;
}

/// Loads the independent file before its first use; failed reads never enable overwriting the unread file.
bool TimeCalculatorForm::EnsurePresetsLoaded() {
    if (presetsLoaded) {
        return true;
    }
    std::wstring path = CalculatorPresetsPath(false);
    if (!ReadCalculatorPresets(path, &presets)) {
        std::wstring message = T(TXT_CALCULATOR_READ_FAILED);
        message += L"\r\n\r\n" + path;
        MessageBoxW(window, message.c_str(), T(TXT_TIME_CALCULATOR), MB_OK | MB_ICONERROR);
        return false;
    }
    presetsLoaded = true;
    return true;
}

/// Saves a proposed collection first, preserving both current data and editor contents on write failure.
bool TimeCalculatorForm::SavePresets(const std::vector<TimeCalculatorPreset>& updated) {
    std::wstring path = CalculatorPresetsPath(true);
    if (!WriteCalculatorPresets(path, updated)) {
        std::wstring message = T(TXT_CALCULATOR_WRITE_FAILED);
        message += L"\r\n\r\n" + path;
        MessageBoxW(window, message.c_str(), T(TXT_TIME_CALCULATOR), MB_OK | MB_ICONERROR);
        return false;
    }
    presets = updated;
    presetDates.clear();
    presetsRevision++;
    if (window != nullptr) {
        CancelEdit();
        FillPresets();
    }
    return true;
}

/// Exports only saved user dates, retaining their UTC instants, zones and exact descriptions.
void TimeCalculatorForm::ExportPresets() {
    if (!EnsurePresetsLoaded()) {
        return;
    }
    std::wstring path;
    std::wstring prefix = GetApplicationName() + L"-times";
    if (!ChooseApplicationXmlFile(window, true, prefix.c_str(), &path)) {
        return;
    }
    if (!WriteCalculatorPresets(path, presets)) {
        std::wstring message = T(TXT_CALCULATOR_WRITE_FAILED);
        message += L"\r\n\r\n" + path;
        MessageBoxW(window, message.c_str(), T(TXT_TIME_CALCULATOR), MB_OK | MB_ICONERROR);
    }
}

/// Merges user dates from XML or legacy text without applying application, widget or calculator settings.
void TimeCalculatorForm::ImportPresets() {
    std::wstring path;
    if (!ChooseApplicationXmlFile(window, false, L"", &path, true)) {
        return;
    }
    std::vector<TimeCalculatorPreset> imported;
    const DYNAMIC_TIME_ZONE_INFORMATION* zone = CalculatorZone(entryZone);
    if (zone == nullptr || !ReadCalculatorPresetImport(path, *zone, entryZone, &imported)) {
        std::wstring message = T(TXT_CALCULATOR_READ_FAILED);
        message += L"\r\n\r\n" + path;
        MessageBoxW(window, message.c_str(), T(TXT_TIME_CALCULATOR), MB_OK | MB_ICONERROR);
        return;
    }
    MergePresets(imported);
}

/// Merges by the exact UTC instant and untrimmed description, preserving all existing records.
bool TimeCalculatorForm::MergePresets(const std::vector<TimeCalculatorPreset>& imported) {
    if (imported.empty()) {
        return true;
    }
    if (!EnsurePresetsLoaded()) {
        return false;
    }
    std::vector<TimeCalculatorPreset> merged = presets;
    for (const TimeCalculatorPreset& candidate : imported) {
        bool duplicate = false;
        for (const TimeCalculatorPreset& existing : merged) {
            if (CompareCalculatorDates(existing.time, candidate.time) == 0
                    && existing.description == candidate.description) {
                duplicate = true;
                break;
            }
        }
        if (!duplicate) {
            merged.push_back(candidate);
        }
    }
    return merged.size() == presets.size() || SavePresets(merged);
}

/// Replaces imported window settings while retaining the native window and independent user data.
void TimeCalculatorForm::Load(const TimeCalculatorState& saved) {
    state = saved;
    presetsRevision++;
    editing = -1;
    if (window != nullptr) {
        InitializeDates();
        UpdateInputs();
        Refresh();
    }
}

/// Initializes UTC instants and the separate local calendar date without modifying saved zone choices.
void TimeCalculatorForm::InitializeDates() {
    SYSTEMTIME now = {};
    GetSystemTime(&now);
    TimeCalculator::Normalize(&now);
    SYSTEMTIME* dates[] = { &state.from, &state.to, &state.start, &entryTime };
    for (SYSTEMTIME* date : dates) {
        SYSTEMTIME validated = *date;
        if (!TimeCalculator::Normalize(&validated)) {
            *date = now;
        }
    }
    if (!TimeCalculator::Normalize(&state.day)) {
        const DYNAMIC_TIME_ZONE_INFORMATION* zone = CalculatorZone(state.startZone);
        if (zone != nullptr) {
            ConvertUtcToTimeZone(*zone, now, &state.day);
        }
    }
    state.tab = std::clamp(state.tab, 0, TIME_CALCULATOR_PAGE_COUNT - 1);
}

/// Creates one resource-authored dialog using the same effective font path as the other application forms.
HWND TimeCalculatorForm::CreateFormDialog(UINT resource, HWND parent) {
    DLGTEMPLATE* definition = LoadSystemDialogTemplate(instance, resource, parent, uiFont);
    if (definition == nullptr) {
        return nullptr;
    }
    CalendarLocaleScope locale(GetLanguageLocale(appLanguage));
    HWND dialog = CreateDialogIndirectParamW(instance, definition, parent, DialogProc,
        reinterpret_cast<LPARAM>(this));
    HeapFree(GetProcessHeap(), 0, definition);
    if (dialog != nullptr) {
        ReadTemplateLayout(dialog, resource);
    }
    return dialog;
}

/// Retains exact DLU rectangles from our extended templates for subsequent font and DPI layout passes.
void TimeCalculatorForm::ReadTemplateLayout(HWND dialog, UINT resource) {
    HRSRC found = FindResourceW(instance, MAKEINTRESOURCEW(resource), RT_DIALOG);
    HGLOBAL loaded = found == nullptr ? nullptr : LoadResource(instance, found);
    const WORD* definition = loaded == nullptr ? nullptr : static_cast<const WORD*>(LockResource(loaded));
    if (definition == nullptr || definition[1] != 0xFFFF) {
        return;
    }
    SIZE size = { static_cast<short>(definition[11]), static_cast<short>(definition[12]) };
    if (resource == IDD_TIME_CALCULATOR) {
        dialogUnits = size;
    }
    WORD count = definition[8];
    const WORD* item = SkipCalculatorTemplateString(definition + 13);
    item = SkipCalculatorTemplateString(item);
    item = SkipCalculatorTemplateString(item);
    if ((definition[6] & DS_SETFONT) != 0) {
        item = SkipCalculatorTemplateString(item + 3);
    }
    for (WORD index = 0; index < count; index++) {
        item = reinterpret_cast<const WORD*>((reinterpret_cast<UINT_PTR>(item) + 3) & ~UINT_PTR{ 3 });
        RECT units = { static_cast<short>(item[6]), static_cast<short>(item[7]), 0, 0 };
        units.right = units.left + static_cast<short>(item[8]);
        units.bottom = units.top + static_cast<short>(item[9]);
        int id = item[10] | item[11] << 16;
        controls.push_back(ControlPlacement{ dialog, id, units });
        HWND control = GetDlgItem(dialog, id);
        if (GetSettingsComboBox(control) != control || resource == IDD_CALCULATOR_HIGHLIGHTS) {
            SetWindowSubclass(control, ApplicationControlSubclassProc, static_cast<UINT_PTR>(id), 0);
        }
        item = SkipCalculatorTemplateString(item + 12);
        item = SkipCalculatorTemplateString(item);
        WORD bytes = *item++;
        item = reinterpret_cast<const WORD*>(reinterpret_cast<const BYTE*>(item) + bytes);
    }
}

/// Prepares slow data outside the GUI thread, retaining one pending opening and the current form settings.
void TimeCalculatorForm::Show(HINSTANCE module, PersistWindowState& savedPlacement, HWND notifyWindow) {
    if (opening != nullptr) {
        return;
    }
    if (window != nullptr) {
        savedPlacement.BringToFront();
        return;
    }
    instance = module;
    placement = &savedPlacement;
    opening = std::make_shared<OpenData>();
    opening->notifyWindow = notifyWindow;
    opening->generation = ++openGeneration;
    opening->revision = presetsRevision;
    opening->language = appLanguage;
    opening->locale = GetLanguageLocale(appLanguage);
    opening->systemLabel = T(TXT_SYSTEM_TIME_ZONE_LABEL);
    opening->zones = timeZones;
    opening->readPresets = !presetsLoaded;
    if (presetsLoaded) {
        opening->presets = presets;
    }
    GetSystemTime(&opening->now);
    std::unique_ptr<std::shared_ptr<OpenData>> parameter =
        std::make_unique<std::shared_ptr<OpenData>>(opening);
    HANDLE thread = CreateThread(nullptr, 0, PrepareOpen, parameter.get(), 0, nullptr);
    if (thread == nullptr) {
        opening.reset();
        return;
    }
    parameter.release();
    CloseHandle(thread);
}

/// Loads user data and formats date/zone captions from owned snapshots without sending control messages.
DWORD WINAPI TimeCalculatorForm::PrepareOpen(void* parameter) {
    std::unique_ptr<std::shared_ptr<OpenData>> owner(static_cast<std::shared_ptr<OpenData>*>(parameter));
    const std::shared_ptr<OpenData>& data = *owner;
    HRESULT initialized = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    data->loaded = SUCCEEDED(initialized);
    if (data->loaded && data->readPresets && !data->cancelled.load()) {
        data->path = CalculatorPresetsPath(false);
        data->loaded = ReadCalculatorPresets(data->path, &data->presets);
    }
    if (data->loaded && !data->cancelled.load()) {
        data->zoneLabels = BuildSettingsTimeZoneLabels(data->zones, data->now, data->systemLabel);
        data->presetDates.reserve(data->presets.size());
        for (const TimeCalculatorPreset& preset : data->presets) {
            if (data->cancelled.load()) {
                break;
            }
            data->presetDates.push_back(FormatCalculatorPreset(preset, data->zones, data->locale.c_str()));
        }
    }
    if (SUCCEEDED(initialized)) {
        CoUninitialize();
    }
    data->finished.store(true, std::memory_order_release);
    if (!data->cancelled.load()) {
        PostMessageW(data->notifyWindow, OPEN_READY, data->generation, 0);
    }
    return 0;
}

/// Accepts one current opening, rejecting stale preparation after imports or application-language changes.
void TimeCalculatorForm::CompleteOpen(ULONG_PTR generation) {
    if (opening == nullptr
            || opening->generation != generation
            || !opening->finished.load(std::memory_order_acquire)) {
        return;
    }
    std::shared_ptr<OpenData> data = opening;
    if (data->cancelled.load()) {
        return;
    }
    if (data->revision != presetsRevision || data->language != appLanguage) {
        opening.reset();
        Show(instance, *placement, data->notifyWindow);
        return;
    }
    if (!data->loaded) {
        opening.reset();
        std::wstring message = T(TXT_CALCULATOR_READ_FAILED);
        message += L"\r\n\r\n" + data->path;
        MessageBoxW(window, message.c_str(), T(TXT_TIME_CALCULATOR), MB_OK | MB_ICONERROR);
        return;
    }
    presets = std::move(data->presets);
    presetsLoaded = true;
    presetDates = std::move(data->presetDates);
    presetLanguage = data->language;
    zoneLabels = std::move(data->zoneLabels);
    ContinueOpen();
}

/// Yields between native creation parts instead of blocking widget timers through the entire opening.
void TimeCalculatorForm::ContinueOpen() {
    if (opening == nullptr || !opening->finished.load(std::memory_order_acquire)) {
        return;
    }
    HWND notifyWindow = opening->notifyWindow;
    KillTimer(notifyWindow, OPEN_TIMER);
    CreatePreparedWindow();
    if (opening != nullptr && !SetTimer(notifyWindow, OPEN_TIMER, USER_TIMER_MINIMUM, nullptr)) {
        Close();
    }
}

/// Returns whether preparation or native creation is still pending.
bool TimeCalculatorForm::IsOpening() const {
    return opening != nullptr;
}

/// Builds one native creation part and leaves the hidden form unexposed until its final layout is ready.
void TimeCalculatorForm::CreatePreparedWindow() {
    int part = opening->part++;
    if (part == 0) {
        initializing = true;
        InitializeDates();
        controls.clear();
        dialogUnits = SIZE{};
        uiFont = CreateApplicationUiFont(nullptr);
        ownsFont = uiFont != nullptr;
        if (uiFont == nullptr) {
            Close();
            initializing = false;
            return;
        }
        window = CreateFormDialog(IDD_TIME_CALCULATOR, nullptr);
        if (window == nullptr) {
            DeleteObject(uiFont);
            uiFont = nullptr;
            ownsFont = false;
            Close();
            initializing = false;
            return;
        }
        SendMessageW(window, WM_SETFONT, reinterpret_cast<WPARAM>(uiFont), FALSE);
        EnumChildWindows(window, ApplyControlStyle, reinterpret_cast<LPARAM>(this));
        for (int index = 0; index < TIME_CALCULATOR_PAGE_COUNT; index++) {
            TCITEMW tab = {};
            tab.mask = TCIF_TEXT;
            tab.pszText = const_cast<wchar_t*>(T(CALCULATOR_TABS[index]));
            TabCtrl_InsertItem(GetDlgItem(window, ID_CALC_TABS), index, &tab);
        }
    } else if (part <= TIME_CALCULATOR_PAGE_COUNT) {
        int index = part - 1;
        if (part == 1) {
            index = state.tab;
        } else if (index <= state.tab) {
            index--;
        }
        pages[index] = CreateFormDialog(CALCULATOR_RESOURCES[index], window);
        if (pages[index] == nullptr) {
            Close();
            return;
        }
        SetWindowPos(pages[index], HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        ApplyControlStyle(pages[index], reinterpret_cast<LPARAM>(this));
        EnumChildWindows(pages[index], ApplyControlStyle, reinterpret_cast<LPARAM>(this));
        EnableThemeDialogTexture(pages[index],
            themesDisabled && AreVisualStylesActive() ? ETDT_DISABLE : ETDT_ENABLETAB);
    } else if (part == 5) {
        for (int index = 9; index < TIME_CALCULATOR_HIGHLIGHT_COUNT; index++) {
            SetWindowPos(GetDlgItem(pages[3], ID_CALC_HIGHLIGHT_BASE + index), HWND_TOP, 0, 0, 0, 0,
                SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        }
        HWND list = GetDlgItem(pages[2], ID_CALC_LIST);
        ListView_SetExtendedListViewStyle(list,
            LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER | LVS_EX_GRIDLINES);
        LVCOLUMNW column = {};
        column.mask = LVCF_TEXT;
        column.pszText = const_cast<wchar_t*>(T(TXT_CALCULATOR_DATE_COLUMN));
        ListView_InsertColumn(list, 0, &column);
        column.pszText = const_cast<wchar_t*>(T(TXT_CALCULATOR_DESCRIPTION_COLUMN));
        ListView_InsertColumn(list, 1, &column);
        HWND originalEdit = GetDlgItem(pages[2], ID_CALC_DESCRIPTION);
        RECT editBounds = {};
        GetWindowRect(originalEdit, &editBounds);
        MapWindowPoints(HWND_DESKTOP, pages[2], reinterpret_cast<POINT*>(&editBounds), 2);
        HWND previousControl = ::GetWindow(originalEdit, GW_HWNDPREV);
        DWORD editStyle = static_cast<DWORD>(GetWindowLongPtrW(originalEdit, GWL_STYLE));
        DWORD editExtended = static_cast<DWORD>(GetWindowLongPtrW(originalEdit, GWL_EXSTYLE));
        DestroyWindow(originalEdit);
        descriptionEdit = SettingsEdit::Create(instance, pages[2], editExtended, editStyle, L"",
            editBounds.left, editBounds.top, editBounds.right - editBounds.left,
            editBounds.bottom - editBounds.top, ID_CALC_DESCRIPTION);
        if (descriptionEdit == nullptr) {
            Close();
            return;
        }
        SetWindowPos(SettingsEdit::GetFrame(descriptionEdit), previousControl, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        HWND edit = descriptionEdit;
        SendMessageW(edit, EM_SETLIMITTEXT, TIME_CALCULATOR_MAX_DESCRIPTION, 0);
        InstallSelectionEditHandler(edit);
        initialized = true;
    } else if (part == 6) {
        HWND editFrame = SettingsEdit::GetFrame(descriptionEdit);
        ApplyControlStyle(editFrame, reinterpret_cast<LPARAM>(this));
        EnumChildWindows(editFrame, ApplyControlStyle, reinterpret_cast<LPARAM>(this));
    } else if (part == 7) {
        ApplyUiStyle(window);
        SetWindowTextW(descriptionEdit, entryDescription.c_str());
        CheckDlgButton(pages[0], ID_CALC_FROM_NOW, state.fromNow ? BST_CHECKED : BST_UNCHECKED);
        CheckDlgButton(pages[0], ID_CALC_TO_NOW, state.toNow ? BST_CHECKED : BST_UNCHECKED);
    } else if (part == 8) {
        Refresh();
    } else if (part < 13) {
        int index = part - 9;
        if (state.tab == 1 || state.tab == 2) {
            int preferred = state.tab + 1;
            if (index == 0) {
                index = preferred;
            } else if (index <= preferred) {
                index--;
            }
        }
        if (index < 0 || index >= static_cast<int>(ARRAYSIZE(inputValid))) {
            Close();
            return;
        }
        bool fromUtc = inputValid[index];
        FillTimeZones(index);
        UpdateTimeInput(index, fromUtc);
    } else if (part == 13) {
        initializing = false;
        Layout();
        SelectPage();
    } else {
        UpdateApplicationWindowIcons(window);
        placement->SetDisableSaveSize(true);
        placement->SetDisableSaveWindowState(true);
        const PersistWindowStateData& saved = placement->GetState();
        bool defaultPosition = saved.x == CW_USEDEFAULT || saved.y == CW_USEDEFAULT;
        if (defaultPosition && !PositionInformationWindowByWindowsDefault(window)
                || !placement->Attach(window, "TimeCalculator")) {
            Close();
            return;
        }
        SetTimer(window, CALCULATOR_TIMER, 1000, nullptr);
        placement->Show();
        opening.reset();
    }
}

/// Releases native windows while retaining inputs and the unfinished preset for style recreation.
void TimeCalculatorForm::Close() {
    if (opening != nullptr) {
        KillTimer(opening->notifyWindow, OPEN_TIMER);
        opening->cancelled.store(true);
        opening.reset();
    }
    if (window != nullptr) {
        DestroyWindow(window);
    }
}

/// Applies application fonts and theme overrides to existing child controls, including native picker popups.
BOOL CALLBACK TimeCalculatorForm::ApplyControlStyle(HWND control, LPARAM parameter) {
    TimeCalculatorForm* form = reinterpret_cast<TimeCalculatorForm*>(parameter);
    if (GetSettingsComboBox(GetParent(control)) == control) {
        return TRUE;
    }
    SendMessageW(control, WM_SETFONT, reinterpret_cast<WPARAM>(form->uiFont), FALSE);
    const wchar_t* theme = themesDisabled && AreVisualStylesActive() ? L"" : nullptr;
    SetWindowTheme(control, theme, theme);
    HWND combo = GetSettingsComboBox(control);
    if (combo != control) {
        SetWindowTheme(combo, theme, theme);
    }
    wchar_t className[32] = {};
    GetClassNameW(control, className, ARRAYSIZE(className));
    bool picker = _wcsicmp(className, DATETIMEPICK_CLASSW) == 0;
    if (picker) {
        SendMessageW(control, DTM_SETMCFONT, reinterpret_cast<WPARAM>(form->uiFont), FALSE);
    }
    if (picker || _wcsicmp(className, MONTHCAL_CLASSW) == 0) {
        SetWindowSubclass(control, CalculatorCalendarProc, CALCULATOR_LOCALE_SUBCLASS, picker);
    }
    return TRUE;
}

/// Reuses the application font selection and rebuilds only geometry, preserving all input and window handles.
bool TimeCalculatorForm::ApplyStyle(bool updateFont) {
    if (window == nullptr || styling) {
        return false;
    }
    HFONT font = updateFont ? CreateApplicationUiFont(window) : uiFont;
    if (font == nullptr) {
        return false;
    }
    styling = true;
    {
        WindowRedrawScope redraw(window);
        HFONT previous = updateFont && ownsFont ? uiFont : nullptr;
        uiFont = font;
        ownsFont = ownsFont || updateFont;
        SendMessageW(window, WM_SETFONT, reinterpret_cast<WPARAM>(uiFont), FALSE);
        EnumChildWindows(window, ApplyControlStyle, reinterpret_cast<LPARAM>(this));
        for (HWND page : pages) {
            EnableThemeDialogTexture(page,
                themesDisabled && AreVisualStylesActive() ? ETDT_DISABLE : ETDT_ENABLETAB);
        }
        if (previous != nullptr) {
            DeleteObject(previous);
        }
        Layout();
    }
    styling = false;
    if (!initializing) {
        layingOut = true;
        FitToWorkArea();
        layingOut = false;
    }
    return true;
}

/// Updates localized captions, date formatting and results without discarding the active tab or typed data.
void TimeCalculatorForm::Refresh() {
    if (!initialized) {
        return;
    }
    bool previousStyling = styling;
    styling = true;
    {
        WindowRedrawScope redraw(window);
        CalendarLocaleScope locale(GetLanguageLocale(appLanguage));
        RequestCalculation(false, !initializing);
        SetWindowTextW(window, BuildApplicationWindowTitle(TXT_CALCULATOR_WINDOW_TITLE).c_str());
        for (int index = 0; index < TIME_CALCULATOR_PAGE_COUNT; index++) {
            TCITEMW tab = {};
            tab.mask = TCIF_TEXT;
            tab.pszText = const_cast<wchar_t*>(T(CALCULATOR_TABS[index]));
            TabCtrl_SetItem(GetDlgItem(window, ID_CALC_TABS), index, &tab);
        }
        SetCalculatorText(pages[0], ID_CALC_FROM_LABEL, T(TXT_CALCULATOR_FROM));
        SetCalculatorText(pages[0], ID_CALC_TO_LABEL, T(TXT_CALCULATOR_TO));
        SetCalculatorText(pages[0], ID_CALC_FROM_NOW, T(TXT_CALCULATOR_NOW));
        SetCalculatorText(pages[0], ID_CALC_TO_NOW, T(TXT_CALCULATOR_NOW));
        SetCalculatorText(pages[0], ID_CALC_INTERVAL_NOTE, T(TXT_CALCULATOR_INTERVAL_NOTE));
        SetCalculatorText(pages[1], ID_CALC_START_LABEL, T(TXT_CALCULATOR_START));
        SetCalculatorText(pages[1], ID_CALC_PRESET_LABEL, T(TXT_CALCULATOR_PRESET));
        SetCalculatorText(pages[1], ID_CALC_SELECTED_LABEL, T(TXT_CALCULATOR_SELECTED_DAY));
        SetCalculatorText(pages[1], ID_CALC_ROUND_NOTE, T(TXT_CALCULATOR_ROUND_NOTE));
        SetCalculatorText(pages[2], ID_CALC_DATE_LABEL, T(TXT_CALCULATOR_DATE));
        SetCalculatorText(pages[2], ID_CALC_DESCRIPTION_LABEL, T(TXT_CALCULATOR_DESCRIPTION));
        SetCalculatorText(pages[2], ID_CALC_EDIT, T(TXT_CALCULATOR_EDIT));
        SetCalculatorText(pages[2], ID_CALC_DELETE, T(TXT_CALCULATOR_DELETE));
        SetCalculatorText(pages[2], ID_CALC_CANCEL, T(TXT_CANCEL));
        SetCalculatorText(pages[2], ID_CALC_IMPORT, T(TXT_CALCULATOR_IMPORT));
        SetCalculatorText(pages[2], ID_CALC_EXPORT, T(TXT_CALCULATOR_EXPORT));
        for (int index = 0; index < TIME_CALCULATOR_HIGHLIGHT_COUNT; index++) {
            const wchar_t* label = T(CALCULATOR_HIGHLIGHT_LABELS[index]);
            wchar_t text[256] = {};
            unsigned int digit = CALCULATOR_HIGHLIGHT_DIGITS[index];
            if (digit != 0) {
                swprintf_s(text, label, digit, digit * 11, digit * 111);
                label = text;
            }
            SetCalculatorText(pages[3], ID_CALC_HIGHLIGHT_BASE + index, label);
            bool checked = (state.highlights & CALCULATOR_HIGHLIGHT_FLAGS[index]) != 0;
            CheckDlgButton(pages[3], ID_CALC_HIGHLIGHT_BASE + index, checked ? BST_CHECKED : BST_UNCHECKED);
        }
        for (int index = 0; index < TIME_CALCULATOR_TOTAL_COUNT; index++) {
            SetCalculatorText(pages[0], ID_CALC_UNIT_BASE + index, T(CALCULATOR_UNITS[index]));
            SetCalculatorText(pages[1], ID_CALC_DAY_UNIT_BASE + index, T(CALCULATOR_UNITS[index]));
        }
        wchar_t dateFormat[128] = {};
        GetLocaleInfoEx(GetLanguageLocale(appLanguage), LOCALE_SSHORTDATE, dateFormat, ARRAYSIZE(dateFormat));
        std::wstring format = dateFormat;
        format += L" HH:mm";
        const HWND pickers[] = {
            GetDlgItem(pages[0], ID_CALC_FROM),
            GetDlgItem(pages[0], ID_CALC_TO),
            GetDlgItem(pages[1], ID_CALC_START),
            GetDlgItem(pages[2], ID_CALC_DATE)
        };
        SYSTEMTIME limits[2] = {};
        limits[0].wYear = 1601;
        limits[0].wMonth = 1;
        limits[0].wDay = 1;
        limits[1].wYear = 9999;
        limits[1].wMonth = 12;
        limits[1].wDay = 31;
        limits[1].wHour = 23;
        limits[1].wMinute = 59;
        bool previousUpdate = updating;
        updating = true;
        for (HWND picker : pickers) {
            SendMessageW(picker, WM_SETTINGCHANGE, 0, reinterpret_cast<LPARAM>(L"intl"));
            DateTime_SetRange(picker, GDTR_MIN | GDTR_MAX, limits);
            DateTime_SetFormat(picker, format.c_str());
        }
        updating = previousUpdate;
        LVCOLUMNW column = {};
        column.mask = LVCF_TEXT;
        column.pszText = const_cast<wchar_t*>(T(TXT_CALCULATOR_DATE_COLUMN));
        ListView_SetColumn(GetDlgItem(pages[2], ID_CALC_LIST), 0, &column);
        column.pszText = const_cast<wchar_t*>(T(TXT_CALCULATOR_DESCRIPTION_COLUMN));
        ListView_SetColumn(GetDlgItem(pages[2], ID_CALC_LIST), 1, &column);
        for (int index = 0; index < 4; index++) {
            SetCalculatorText(pages[CALCULATOR_INPUT_PAGES[index]],
                ID_CALC_ZONE_LABEL_BASE + index, T(TXT_TIMEZONE));
            if (!initializing) {
                FillTimeZones(index);
                UpdateTimeInput(index, inputValid[index]);
            }
        }
        FillPresets();
        UpdateNow();
        updating = true;
        SendMessageW(GetDlgItem(pages[1], ID_CALC_CALENDAR), WM_SETTINGCHANGE, 0,
            reinterpret_cast<LPARAM>(L"intl"));
        updating = previousUpdate;
        UpdateHighlights();
        Layout();
        SelectPage();
    }
    styling = previousStyling;
    if (!styling && !initializing) {
        layingOut = true;
        FitToWorkArea();
        layingOut = false;
    }
}
/// Restores resource DLU geometry using the current font and aligns each mixed row by its rendered text.
void TimeCalculatorForm::Layout() {
    if (!initialized || initializing || layingOut || IsIconic(window)) {
        return;
    }
    SIZE units = {};
    if (!GetDialogFontBaseUnits(uiFont, &units)) {
        return;
    }
    layingOut = true;
    for (const ControlPlacement& item : controls) {
        SIZE position = {
            MulDiv(item.units.left, units.cx, 4),
            DialogHeightFromUnits(item.units.top, units.cy)
        };
        SIZE size = {
            MulDiv(item.units.right - item.units.left, units.cx, 4),
            DialogHeightFromUnits(item.units.bottom - item.units.top, units.cy)
        };
        SetControlPosition(GetDlgItem(item.parent, item.id), position.cx, position.cy, size.cx, size.cy);
    }
    const int buttonIds[] = {
        ID_CALC_ADD,
        ID_CALC_EDIT,
        ID_CALC_DELETE,
        ID_CALC_CANCEL,
        ID_CALC_IMPORT,
        ID_CALC_EXPORT
    };
    RECT firstButton = CalculatorControlBounds(pages[2], ID_CALC_ADD);
    RECT listBounds = CalculatorControlBounds(pages[2], ID_CALC_LIST);
    RECT secondButton = CalculatorControlBounds(pages[2], ID_CALC_EDIT);
    LONG buttonGap = secondButton.left - firstButton.right;
    SIZE button = { firstButton.right - firstButton.left, firstButton.bottom - firstButton.top };
    for (int id : buttonIds) {
        button.cx = PreferredButtonWidth(GetDlgItem(pages[2], id), button.cx);
    }
    HWND measurement = CreateWindowExW(0, L"BUTTON", T(TXT_SAVE), WS_CHILD | BS_PUSHBUTTON,
        0, 0, 0, 0, pages[2], nullptr, instance, nullptr);
    if (measurement != nullptr) {
        SendMessageW(measurement, WM_SETFONT, reinterpret_cast<WPARAM>(uiFont), FALSE);
        const wchar_t* theme = GetWindowTheme(GetDlgItem(pages[2], ID_CALC_ADD)) == nullptr ? L"" : nullptr;
        SetWindowTheme(measurement, theme, theme);
        button.cx = PreferredButtonWidth(measurement, button.cx);
        DestroyWindow(measurement);
    }
    LONG buttonCount = static_cast<LONG>(ARRAYSIZE(buttonIds));
    LONG totalGaps = (buttonCount - 1) * buttonGap;
    LONG availableWidth = listBounds.right - firstButton.left;
    LONG fittedWidth = (availableWidth - totalGaps + buttonCount - 1) / buttonCount;
    button.cx = std::max(button.cx, fittedWidth);
    LONG rowWidth = buttonCount * button.cx + totalGaps;
    LONG extraWidth = firstButton.left + rowWidth - listBounds.right;
    if (extraWidth > 0) {
        for (const ControlPlacement& item : controls) {
            HWND control = GetDlgItem(item.parent, item.id);
            RECT bounds = CalculatorControlBounds(item.parent, item.id);
            if (item.parent == window && item.id == ID_CALC_TABS
                    || item.parent != window && item.units.right >= 235) {
                LONG left = bounds.left;
                LONG width = bounds.right - bounds.left;
                if (item.parent == pages[3]
                        && item.id >= ID_CALC_HIGHLIGHT_BASE + 9
                        && item.id < ID_CALC_HIGHLIGHT_BASE + TIME_CALCULATOR_HIGHLIGHT_COUNT) {
                    LONG shift = extraWidth / 2;
                    left += shift;
                    width += extraWidth - shift;
                } else if (item.parent != window && item.units.left >= 239) {
                    left += extraWidth;
                } else {
                    width += extraWidth;
                }
                SetControlPosition(control, left, bounds.top, width, bounds.bottom - bounds.top);
            }
        }
    }
    HWND calendar = GetDlgItem(pages[1], ID_CALC_CALENDAR);
    StyleCalculatorCalendar(calendar, window);
    RECT minimum = {};
    if (MonthCal_GetMinReqRect(calendar, &minimum)) {
        LONG todayWidth = static_cast<LONG>(MonthCal_GetMaxTodayWidth(calendar));
        LONG width = std::max(minimum.right - minimum.left, todayWidth);
        SetWindowPos(calendar, nullptr, 0, 0, width, minimum.bottom - minimum.top,
            SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
    }
    RECT calendarBounds = CalculatorControlBounds(pages[1], ID_CALC_CALENDAR);
    RECT lastRow = CalculatorControlBounds(pages[1], ID_CALC_DAY_UNIT_BASE + TIME_CALCULATOR_TOTAL_COUNT - 1);
    LONG extraHeight = std::max(0L, calendarBounds.bottom - lastRow.bottom);
    if (extraHeight > 0) {
        RECT note = CalculatorControlBounds(pages[1], ID_CALC_ROUND_NOTE);
        SetWindowPos(GetDlgItem(pages[1], ID_CALC_ROUND_NOTE), nullptr, note.left, note.top + extraHeight,
            0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
        RECT list = CalculatorControlBounds(pages[2], ID_CALC_LIST);
        SetWindowPos(GetDlgItem(pages[2], ID_CALC_LIST), nullptr, 0, 0, list.right - list.left,
            list.bottom - list.top + extraHeight, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
        RECT tabs = CalculatorControlBounds(window, ID_CALC_TABS);
        SetWindowPos(GetDlgItem(window, ID_CALC_TABS), nullptr, 0, 0, tabs.right - tabs.left,
            tabs.bottom - tabs.top + extraHeight, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
    }
    UpdateSettingsComboMetrics(GetDlgItem(pages[0], ID_CALC_FROM_PRESET));
    UpdateSettingsComboMetrics(GetDlgItem(pages[0], ID_CALC_TO_PRESET));
    UpdateSettingsComboMetrics(GetDlgItem(pages[1], ID_CALC_PRESET));
    for (int index = 0; index < 4; index++) {
        HWND page = pages[CALCULATOR_INPUT_PAGES[index]];
        UpdateSettingsComboMetrics(GetDlgItem(page, ID_CALC_ZONE_BASE + index));
        UpdateSettingsComboMetrics(GetDlgItem(page, ID_CALC_OFFSET_BASE + index));
    }
    UpdateEditMetrics(descriptionEdit);
    HWND tabs = GetDlgItem(window, ID_CALC_TABS);
    UpdateDialogTabMetrics(tabs);
    RECT display = {};
    GetClientRect(tabs, &display);
    TabCtrl_AdjustRect(tabs, FALSE, &display);
    MapWindowPoints(tabs, window, reinterpret_cast<POINT*>(&display), 2);
    for (HWND page : pages) {
        SetControlPosition(page, display.left, display.top,
            display.right - display.left, display.bottom - display.top);
    }
    const int pickerIds[] = { ID_CALC_FROM, ID_CALC_TO, ID_CALC_START, ID_CALC_DATE };
    const int labelIds[] = { ID_CALC_FROM_LABEL, ID_CALC_TO_LABEL, ID_CALC_START_LABEL, ID_CALC_DATE_LABEL };
    const int pageIndices[] = { 0, 0, 1, 2 };
    for (int index = 0; index < 4; index++) {
        HWND page = pages[pageIndices[index]];
        AlignCalculatorDatePicker(GetDlgItem(page, pickerIds[index]), GetDlgItem(page, labelIds[index]));
    }
    AlignSettingsControl(GetDlgItem(pages[0], ID_CALC_FROM_NOW), GetDlgItem(pages[0], ID_CALC_FROM_LABEL));
    AlignSettingsControl(GetDlgItem(pages[0], ID_CALC_TO_NOW), GetDlgItem(pages[0], ID_CALC_TO_LABEL));
    AlignSettingsControl(GetDlgItem(pages[0], ID_CALC_FROM_PRESET), GetDlgItem(pages[0], ID_CALC_FROM_LABEL));
    AlignSettingsControl(GetDlgItem(pages[0], ID_CALC_TO_PRESET), GetDlgItem(pages[0], ID_CALC_TO_LABEL));
    AlignSettingsControl(GetDlgItem(pages[1], ID_CALC_PRESET), GetDlgItem(pages[1], ID_CALC_PRESET_LABEL));
    for (int index = 0; index < 4; index++) {
        HWND page = pages[CALCULATOR_INPUT_PAGES[index]];
        HWND label = GetDlgItem(page, ID_CALC_ZONE_LABEL_BASE + index);
        AlignSettingsControl(GetDlgItem(page, ID_CALC_ZONE_BASE + index), label);
        AlignSettingsControl(GetDlgItem(page, ID_CALC_OFFSET_BASE + index), label);
        SetWindowPos(label, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
    AlignSettingsControl(descriptionEdit, GetDlgItem(pages[2], ID_CALC_DESCRIPTION_LABEL));
    POINT buttonPosition = { firstButton.left, firstButton.top };
    HWND buttonRow = GetDlgItem(pages[2], ID_CALC_BUTTON_ROW);
    for (int id : buttonIds) {
        SetControlPosition(GetDlgItem(pages[2], id), buttonPosition.x, buttonPosition.y, button.cx,
            button.cy);
        AlignSettingsControl(GetDlgItem(pages[2], id), buttonRow);
        buttonPosition.x += button.cx + buttonGap;
    }
    UpdatePresetColumns();
    const int labels[] = {
        ID_CALC_FROM_LABEL,
        ID_CALC_TO_LABEL,
        ID_CALC_START_LABEL,
        ID_CALC_PRESET_LABEL,
        ID_CALC_DATE_LABEL,
        ID_CALC_DESCRIPTION_LABEL
    };
    for (HWND page : pages) {
        for (int id : labels) {
            HWND label = GetDlgItem(page, id);
            if (label != nullptr) {
                SetWindowPos(label, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
            }
        }
    }
    contentSize = InformationDialogUnits(uiFont, dialogUnits.cx, dialogUnits.cy);
    contentSize.cx += extraWidth;
    contentSize.cy += extraHeight;
    if (!styling) {
        FitToWorkArea();
    }
    layingOut = false;
}

/// Fits the fixed natural size to the current work area and exposes overflow with native scrollbars.
void TimeCalculatorForm::FitToWorkArea() const {
    if (window == nullptr || contentSize.cx <= 0 || IsIconic(window)) {
        return;
    }
    MONITORINFO monitor = { sizeof(monitor) };
    RECT bounds = {};
    RECT client = {};
    if (!GetWindowRect(window, &bounds)
            || !GetMonitorInfoW(MonitorFromWindow(window, MONITOR_DEFAULTTONEAREST), &monitor)) {
        return;
    }
    DWORD currentStyle = static_cast<DWORD>(GetWindowLongPtrW(window, GWL_STYLE));
    DWORD style = currentStyle & ~(WS_HSCROLL | WS_VSCROLL);
    DWORD extended = static_cast<DWORD>(GetWindowLongPtrW(window, GWL_EXSTYLE));
    RECT outer = { 0, 0, contentSize.cx, contentSize.cy };
    if (!DialogFrame::AdjustRect(window, &outer, style, extended)) {
        return;
    }
    LONG desiredWidth = outer.right - outer.left;
    LONG desiredHeight = outer.bottom - outer.top;
    LONG workWidth = monitor.rcWork.right - monitor.rcWork.left;
    LONG workHeight = monitor.rcWork.bottom - monitor.rcWork.top;
    int horizontalScrollHeight = GetSystemMetrics(SM_CYHSCROLL);
    int verticalScrollWidth = GetSystemMetrics(SM_CXVSCROLL);
    bool horizontalScroll = desiredWidth > workWidth;
    bool verticalScroll = desiredHeight > workHeight;
    LONG width = 0;
    LONG height = 0;
    for (int pass = 0; pass < 2; pass++) {
        width = std::min(workWidth, desiredWidth + (verticalScroll ? verticalScrollWidth : 0));
        height = std::min(workHeight, desiredHeight + (horizontalScroll ? horizontalScrollHeight : 0));
        if (width - (verticalScroll ? verticalScrollWidth : 0) < desiredWidth) {
            horizontalScroll = true;
        }
        if (height - (horizontalScroll ? horizontalScrollHeight : 0) < desiredHeight) {
            verticalScroll = true;
        }
    }
    width = std::min(workWidth, desiredWidth + (verticalScroll ? verticalScrollWidth : 0));
    height = std::min(workHeight, desiredHeight + (horizontalScroll ? horizontalScrollHeight : 0));
    if (horizontalScroll) {
        style |= WS_HSCROLL;
    }
    if (verticalScroll) {
        style |= WS_VSCROLL;
    }
    LONG left = std::clamp(bounds.left, monitor.rcWork.left, monitor.rcWork.right - width);
    LONG top = std::clamp(bounds.top, monitor.rcWork.top, monitor.rcWork.bottom - height);
    UINT flags = SWP_NOZORDER | SWP_NOACTIVATE;
    if (style != currentStyle) {
        SetWindowLongPtrW(window, GWL_STYLE, style);
        flags |= SWP_FRAMECHANGED;
    }
    if (style != currentStyle
            || left != bounds.left
            || top != bounds.top
            || width != bounds.right - bounds.left
            || height != bounds.bottom - bounds.top) {
        SetWindowPos(window, nullptr, left, top, width, height, flags);
    }
    GetClientRect(window, &client);
    SCROLLINFO information = { sizeof(information), SIF_RANGE | SIF_PAGE | SIF_POS };
    if (horizontalScroll) {
        information.nMax = contentSize.cx - 1;
        information.nPage = client.right;
        SetScrollInfo(window, SB_HORZ, &information, TRUE);
    }
    if (verticalScroll) {
        information.nMax = contentSize.cy - 1;
        information.nPage = client.bottom;
        SetScrollInfo(window, SB_VERT, &information, TRUE);
    }
}

/// Scrolls the complete dialog surface without changing its DLU geometry or stealing activation.
void TimeCalculatorForm::Scroll(int bar, int request) const {
    SCROLLINFO information = { sizeof(information), SIF_ALL };
    if (!GetScrollInfo(window, bar, &information)) {
        return;
    }
    int previous = information.nPos;
    int line = InformationDialogUnits(uiFont, 8, 8).cy;
    switch (request) {
        case SB_LINEUP:
            information.nPos -= line;
            break;
        case SB_LINEDOWN:
            information.nPos += line;
            break;
        case SB_PAGEUP:
            information.nPos -= information.nPage;
            break;
        case SB_PAGEDOWN:
            information.nPos += information.nPage;
            break;
        case SB_THUMBTRACK:
        case SB_THUMBPOSITION:
            information.nPos = information.nTrackPos;
            break;
        case SB_TOP:
            information.nPos = information.nMin;
            break;
        case SB_BOTTOM:
            information.nPos = information.nMax;
            break;
        default: return;
    }
    int maximum = std::max(information.nMin, information.nMax - static_cast<int>(information.nPage) + 1);
    information.nPos = std::clamp(information.nPos, information.nMin, maximum);
    information.fMask = SIF_POS;
    SetScrollInfo(window, bar, &information, TRUE);
    int delta = previous - information.nPos;
    if (delta != 0) {
        ScrollWindowEx(window, bar == SB_HORZ ? delta : 0, bar == SB_VERT ? delta : 0,
            nullptr, nullptr, nullptr, nullptr, SW_SCROLLCHILDREN | SW_INVALIDATE | SW_ERASE);
    }
}

/// Shows exactly the selected resource page and preserves it across font, language and theme changes.
void TimeCalculatorForm::SelectPage() {
    if (initializing) {
        return;
    }
    bool changed = TabCtrl_GetCurSel(GetDlgItem(window, ID_CALC_TABS)) != state.tab;
    for (int index = 0; index < TIME_CALCULATOR_PAGE_COUNT; index++) {
        bool visible = (GetWindowLongPtrW(pages[index], GWL_STYLE) & WS_VISIBLE) != 0;
        changed = changed || visible != (index == state.tab);
    }
    if (!changed) {
        return;
    }
    WindowRedrawScope redraw(window);
    TabCtrl_SetCurSel(GetDlgItem(window, ID_CALC_TABS), state.tab);
    for (int index = 0; index < TIME_CALCULATOR_PAGE_COUNT; index++) {
        UINT visibility = index == state.tab ? SWP_SHOWWINDOW : SWP_HIDEWINDOW;
        SetWindowPos(pages[index], nullptr, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | visibility);
    }
}

/// Refills a zone selector from the exact Settings catalog without changing its saved key.
void TimeCalculatorForm::FillTimeZones(int index) {
    HWND combo = GetDlgItem(pages[CALCULATOR_INPUT_PAGES[index]], ID_CALC_ZONE_BASE + index);
    const std::wstring* keys[] = { &state.fromZone, &state.toZone, &state.startZone, &entryZone };
    WindowRedrawScope redraw(combo);
    SendMessageW(combo, CB_RESETCONTENT, 0, 0);
    for (size_t item = 0; item < timeZones.size(); item++) {
        const wchar_t* label = timeZones[item].StandardName;
        if (_wcsicmp(timeZones[item].TimeZoneKeyName, SYSTEM_TIME_ZONE_KEY) == 0) {
            label = T(TXT_SYSTEM_TIME_ZONE_LABEL);
        } else if (*label == L'\0') {
            label = timeZones[item].TimeZoneKeyName;
        }
        if (zoneLabels.size() == timeZones.size()) {
            label = zoneLabels[item].c_str();
        }
        LRESULT inserted = SendMessageW(combo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(label));
        if (inserted >= 0) {
            SendMessageW(combo, CB_SETITEMDATA, inserted, item);
            if (_wcsicmp(timeZones[item].TimeZoneKeyName, keys[index]->c_str()) == 0) {
                SendMessageW(combo, CB_SETCURSEL, inserted, 0);
            }
        }
    }
}

/// Resolves local input through Windows rules; an offset selection makes repeated local times unambiguous.
void TimeCalculatorForm::UpdateTimeInput(int index, bool fromUtc, int choice) {
    SYSTEMTIME* times[] = { &state.from, &state.to, &state.start, &entryTime };
    const std::wstring* keys[] = { &state.fromZone, &state.toZone, &state.startZone, &entryZone };
    HWND page = pages[CALCULATOR_INPUT_PAGES[index]];
    HWND picker = GetDlgItem(page, CALCULATOR_INPUT_IDS[index]);
    HWND offsets = GetDlgItem(page, ID_CALC_OFFSET_BASE + index);
    const DYNAMIC_TIME_ZONE_INFORMATION* zone = CalculatorZone(*keys[index]);
    bool current = index == 0 && state.fromNow || index == 1 && state.toNow;
    SYSTEMTIME instant = *times[index];
    if (current) {
        GetSystemTime(&instant);
        TimeCalculator::Normalize(&instant);
        fromUtc = true;
    }
    bool previousUpdate = updating;
    updating = true;
    SYSTEMTIME local = {};
    bool converted = zone != nullptr;
    if (converted && fromUtc) {
        converted = ConvertUtcToTimeZone(*zone, instant, &local);
        if (converted) {
            SYSTEMTIME displayed = {};
            if (DateTime_GetSystemtime(picker, &displayed) != GDT_VALID
                    || CompareCalculatorDates(displayed, local) != 0) {
                DateTime_SetSystemtime(picker, GDT_VALID, &local);
            }
        }
    } else if (converted) {
        converted = DateTime_GetSystemtime(picker, &local) == GDT_VALID && TimeCalculator::Normalize(&local);
    }
    ULONGLONG candidates[2] = {};
    unsigned int count = 0;
    converted = converted && GetTimeZoneUtcCandidates(*zone, local, candidates, count);
    int selected = -1;
    std::vector<std::wstring> offsetLabels;
    for (unsigned int item = 0; converted && item < count; item++) {
        ULARGE_INTEGER ticks = {};
        ticks.QuadPart = candidates[item];
        FILETIME file = { ticks.LowPart, ticks.HighPart };
        SYSTEMTIME utc = {};
        FileTimeToSystemTime(&file, &utc);
        offsetLabels.push_back(CalculatorOffset(utc, local));
        if (count == 1 || choice == static_cast<int>(item) || CompareCalculatorDates(instant, utc) == 0) {
            selected = static_cast<int>(item);
        }
    }
    if (choice >= 0 && choice < static_cast<int>(count)) {
        selected = choice;
    }
    bool labelsChanged =
        SendMessageW(offsets, CB_GETCOUNT, 0, 0) != static_cast<LRESULT>(offsetLabels.size());
    for (size_t item = 0; !labelsChanged && item < offsetLabels.size(); item++) {
        LRESULT length = SendMessageW(offsets, CB_GETLBTEXTLEN, item, 0);
        if (length == CB_ERR) {
            labelsChanged = true;
        } else {
            std::wstring label(static_cast<size_t>(length) + 1, L'\0');
            SendMessageW(offsets, CB_GETLBTEXT, item, reinterpret_cast<LPARAM>(label.data()));
            label.resize(static_cast<size_t>(length));
            labelsChanged = label != offsetLabels[item];
        }
    }
    if (labelsChanged) {
        WindowRedrawScope redraw(offsets);
        SendMessageW(offsets, CB_RESETCONTENT, 0, 0);
        for (const std::wstring& label : offsetLabels) {
            SendMessageW(offsets, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(label.c_str()));
        }
    }
    inputValid[index] = converted && selected >= 0;
    if (SendMessageW(offsets, CB_GETCURSEL, 0, 0) != selected) {
        SendMessageW(offsets, CB_SETCURSEL, selected, 0);
    }
    EnableWindow(offsets, count == 2 && !current);
    if (inputValid[index]) {
        ULARGE_INTEGER ticks = {};
        ticks.QuadPart = candidates[selected];
        FILETIME file = { ticks.LowPart, ticks.HighPart };
        FileTimeToSystemTime(&file, &instant);
        if (!current && !fromUtc) {
            *times[index] = instant;
        }
        SetCalculatorText(page, ID_CALC_UTC_BASE + index, CalculatorUtcText(instant, *keys[index]));
    } else {
        SetCalculatorText(page, ID_CALC_UTC_BASE + index,
            T(count == 2 ? TXT_CALCULATOR_SELECT_OFFSET : TXT_CALCULATOR_TIME_GAP));
    }
    updating = previousUpdate;
}

/// Restores UTC inputs through their display zones without treating notifications as user edits.
void TimeCalculatorForm::UpdateInputs() {
    updating = true;
    for (int index = 0; index < 4; index++) {
        FillTimeZones(index);
        UpdateTimeInput(index, true);
    }
    SetWindowTextW(descriptionEdit, entryDescription.c_str());
    CheckDlgButton(pages[0], ID_CALC_FROM_NOW, state.fromNow ? BST_CHECKED : BST_UNCHECKED);
    CheckDlgButton(pages[0], ID_CALC_TO_NOW, state.toNow ? BST_CHECKED : BST_UNCHECKED);
    MonthCal_SetCurSel(GetDlgItem(pages[1], ID_CALC_CALENDAR), &state.day);
    updating = false;
    SelectPage();
    UpdateNow();
}

/// Updates only live Now inputs so a timer cannot overwrite an unfinished manual time or offset choice.
void TimeCalculatorForm::UpdateNow() {
    const bool current[] = { state.fromNow, state.toNow };
    const int combos[] = { ID_CALC_FROM_PRESET, ID_CALC_TO_PRESET };
    const SYSTEMTIME manual[] = { state.from, state.to };
    SYSTEMTIME now = {};
    GetSystemTime(&now);
    TimeCalculator::Normalize(&now);
    lastNow = now;
    for (int index = 0; index < 2; index++) {
        if (current[index]) {
            UpdateTimeInput(index, true);
        }
        EnableWindow(GetDlgItem(pages[0], CALCULATOR_INPUT_IDS[index]), !current[index]);
        HWND combo = GetDlgItem(pages[0], combos[index]);
        EnableWindow(combo, !current[index] && !presets.empty());
        SelectPreset(combo, current[index] ? now : manual[index]);
    }
    UpdateResults();
}

/// Queues results without running calendar or time-zone calculations on the dialog thread.
void TimeCalculatorForm::UpdateResults() {
    RequestCalculation();
}

/// Coalesces rapid input changes and cancels obsolete work without waiting on the dialog thread.
void TimeCalculatorForm::RequestCalculation(bool highlights, bool labels) {
    if (!initialized) {
        return;
    }
    calculationPending = true;
    highlightsPending = highlightsPending || highlights;
    labelsPending = labelsPending || labels;
    if (calculation != nullptr) {
        calculation->cancelled.store(true);
    }
    if (!calculationQueued) {
        calculationQueued = PostMessageW(window, CALCULATOR_CALCULATE, 0, 0) != FALSE;
    }
}

/// Copies current inputs for one worker; additional requests replace pending work rather than spawning
/// threads.
void TimeCalculatorForm::StartCalculation() {
    if (!initialized || calculation != nullptr || !calculationPending) {
        return;
    }
    calculation = std::make_shared<Calculation>();
    calculation->window = window;
    calculation->generation = ++calculationGeneration;
    calculation->state = state;
    GetSystemTime(&calculation->now);
    TimeCalculator::Normalize(&calculation->now);
    if (state.fromNow) {
        calculation->state.from = calculation->now;
    }
    if (state.toNow) {
        calculation->state.to = calculation->now;
    }
    const DYNAMIC_TIME_ZONE_INFORMATION* fromZone = CalculatorZone(state.fromZone);
    const DYNAMIC_TIME_ZONE_INFORMATION* startZone = CalculatorZone(state.startZone);
    calculation->validInterval = inputValid[0] && inputValid[1] && fromZone != nullptr;
    calculation->validDay = inputValid[2] && startZone != nullptr;
    if (fromZone != nullptr) {
        calculation->fromZone = *fromZone;
    }
    if (startZone != nullptr) {
        calculation->startZone = *startZone;
    }
    calculation->highlights = highlightsPending;
    calculation->labels = labelsPending;
    calculation->firstMonth = firstMonth;
    calculation->monthCount = static_cast<int>(dayStates.size());
    if (labelsPending) {
        calculation->zones = timeZones;
        calculation->systemLabel = T(TXT_SYSTEM_TIME_ZONE_LABEL);
    }
    std::unique_ptr<std::shared_ptr<Calculation>> parameter =
        std::make_unique<std::shared_ptr<Calculation>>(calculation);
    HANDLE thread = CreateThread(nullptr, 0, Calculate, parameter.get(), 0, nullptr);
    calculationPending = false;
    if (thread == nullptr) {
        calculation.reset();
        OutputDebugStringW(L"CalClock: cannot start Time Calculator worker.\r\n");
        return;
    }
    parameter.release();
    CloseHandle(thread);
}

/// Calculates from an immutable snapshot and publishes completion without accessing any controls or live
/// form state.
DWORD WINAPI TimeCalculatorForm::Calculate(void* parameter) {
    std::unique_ptr<std::shared_ptr<Calculation>> owner(
        static_cast<std::shared_ptr<Calculation>*>(parameter));
    const std::shared_ptr<Calculation>& work = *owner;
    if (work->labels && !work->cancelled.load()) {
        work->zoneLabels = BuildSettingsTimeZoneLabels(work->zones, work->now, work->systemLabel);
    }
    if (!work->cancelled.load()) {
        if (_wcsicmp(work->fromZone.TimeZoneKeyName, SYSTEM_TIME_ZONE_KEY) == 0) {
            work->validInterval = work->validInterval
                && GetDynamicTimeZoneInformation(&work->fromZone) != TIME_ZONE_ID_INVALID;
        }
        if (_wcsicmp(work->startZone.TimeZoneKeyName, SYSTEM_TIME_ZONE_KEY) == 0) {
            work->validDay = work->validDay
                && GetDynamicTimeZoneInformation(&work->startZone) != TIME_ZONE_ID_INVALID;
        }
        work->validInterval = work->validInterval && TimeCalculator::CalculateUtc(
            work->state.from, work->state.to, work->fromZone, &work->interval);
    }
    if (!work->cancelled.load()) {
        work->validStart = work->validDay;
        work->validDay = work->validDay && TimeCalculator::CalculateDayUtc(
            work->state.start, work->state.day, work->startZone, &work->day, work->state.highlights);
        if (work->validDay && work->day.hasHourTime) {
            ConvertUtcToTimeZone(work->startZone, work->day.hourTime, &work->hourTime);
        }
    }
    if (work->highlights && !work->cancelled.load()) {
        work->dayStates.assign(work->monthCount, 0);
        SYSTEMTIME day = work->firstMonth;
        for (int month = 0; month < work->monthCount && !work->cancelled.load(); month++) {
            for (WORD date = 1; date <= 31 && !work->cancelled.load(); date++) {
                day.wDay = date;
                if (work->validStart && TimeCalculator::IsHighlightedDayUtc(
                    work->state.start, day, work->startZone, work->state.highlights)) {
                    work->dayStates[month] |= MONTHDAYSTATE{ 1 } << (date - 1);
                }
            }
            if (++day.wMonth > 12) {
                day.wMonth = 1;
                day.wYear++;
            }
        }
    }
    work->finished.store(true, std::memory_order_release);
    PostMessageW(work->window, CALCULATOR_READY, work->generation, 0);
    return 0;
}

/// Accepts only the current result; closed or reopened windows never consume an earlier worker's completion.
void TimeCalculatorForm::CompleteCalculation(ULONG_PTR generation) {
    if (calculation == nullptr
            || calculation->generation != generation
            || !calculation->finished.load(std::memory_order_acquire)) {
        return;
    }
    std::shared_ptr<Calculation> result = std::move(calculation);
    if (!result->cancelled.load()) {
        if (result->labels) {
            labelsPending = false;
            bool changed = zoneLabels != result->zoneLabels;
            zoneLabels = std::move(result->zoneLabels);
            if (changed) {
                for (int index = 0; index < 4; index++) {
                    HWND combo = GetDlgItem(pages[CALCULATOR_INPUT_PAGES[index]], ID_CALC_ZONE_BASE + index);
                    if (SendMessageW(GetSettingsComboBox(combo), CB_GETDROPPEDSTATE, 0, 0) == FALSE) {
                        FillTimeZones(index);
                    }
                }
            }
        }
        ApplyCalculation(*result);
        if (result->highlights) {
            highlightsPending = false;
            dayStates = std::move(result->dayStates);
            HWND calendar = GetDlgItem(pages[1], ID_CALC_CALENDAR);
            SYSTEMTIME range[2] = {};
            int count = MonthCal_GetMonthRange(calendar, GMR_DAYSTATE, range);
            if (count > 0
                    && count == static_cast<int>(dayStates.size())
                    && range[0].wYear == firstMonth.wYear
                    && range[0].wMonth == firstMonth.wMonth) {
                MonthCal_SetDayState(calendar, count, dayStates.data());
            }
        }
    }
    StartCalculation();
}

/// Applies completed totals and component breakdowns only from the dialog thread.
void TimeCalculatorForm::ApplyCalculation(const Calculation& result) const {
    for (int index = 0; index < TIME_CALCULATOR_TOTAL_COUNT; index++) {
        std::wstring total = result.validInterval
            ? std::to_wstring(result.interval.totals[index])
            : L"—";
        std::wstring parts = result.validInterval
            ? FormatCalculatorParts(result.interval.parts[index])
            : L"";
        SetCalculatorText(pages[0], ID_CALC_TOTAL_BASE + index, total);
        SetCalculatorText(pages[0], ID_CALC_PARTS_BASE + index, parts);
        total = result.validDay
            ? std::to_wstring(result.day.totals[index])
            : L"—";
        if (result.validDay && index == 0 && result.day.hasHourTime) {
            wchar_t time[20] = {};
            swprintf_s(time, L" (%02u:%02u ", result.hourTime.wHour, result.hourTime.wMinute);
            total += time + CalculatorOffset(result.day.hourTime, result.hourTime) + L")";
        }
        SetCalculatorText(pages[1], ID_CALC_DAY_TOTAL_BASE + index, total);
    }
    SetCalculatorText(pages[1], ID_CALC_SELECTED_DATE, FormatCalculatorDate(result.state.day, false));
}

/// Returns cached masks immediately and queues newly requested months without blocking native calendar
/// painting.
void TimeCalculatorForm::FillDayStates(const SYSTEMTIME& first, int count) {
    count = std::max(0, count);
    if (firstMonth.wYear == first.wYear
            && firstMonth.wMonth == first.wMonth
            && dayStates.size() == static_cast<size_t>(count)) {
        return;
    }
    firstMonth = first;
    firstMonth.wDay = 1;
    firstMonth.wHour = 0;
    firstMonth.wMinute = 0;
    firstMonth.wSecond = 0;
    firstMonth.wMilliseconds = 0;
    dayStates.assign(count, 0);
    RequestCalculation(true);
}

/// Recalculates anniversary highlighting after a start-date or displayed-month change.
void TimeCalculatorForm::UpdateHighlights() {
    HWND calendar = GetDlgItem(pages[1], ID_CALC_CALENDAR);
    SYSTEMTIME limits[2] = {};
    const DYNAMIC_TIME_ZONE_INFORMATION* zone = CalculatorZone(state.startZone);
    if (zone == nullptr || !ConvertUtcToTimeZone(*zone, state.start, &limits[0])) {
        return;
    }
    limits[0].wHour = 0;
    limits[0].wMinute = 0;
    limits[1].wYear = 9999;
    limits[1].wMonth = 12;
    limits[1].wDay = 31;
    bool previousUpdate = updating;
    updating = true;
    SYSTEMTIME existing[2] = {};
    DWORD flags = MonthCal_GetRange(calendar, existing);
    if (flags != (GDTR_MIN | GDTR_MAX)
            || CompareCalculatorDates(existing[0], limits[0]) != 0
            || CompareCalculatorDates(existing[1], limits[1]) != 0) {
        MonthCal_SetRange(calendar, GDTR_MIN | GDTR_MAX, limits);
    }
    if (CompareCalculatorDates(state.day, limits[0]) < 0) {
        state.day = limits[0];
    }
    SYSTEMTIME selected = {};
    if (!MonthCal_GetCurSel(calendar, &selected)
            || CompareCalculatorDates(selected, state.day) != 0) {
        MonthCal_SetCurSel(calendar, &state.day);
    }
    updating = previousUpdate;
    UpdateResults();
    SYSTEMTIME range[2] = {};
    int count = MonthCal_GetMonthRange(calendar, GMR_DAYSTATE, range);
    FillDayStates(range[0], count);
    RequestCalculation(true);
}

/// Selects the preset matching a displayed minute, or leaves the native combo without a selection.
void TimeCalculatorForm::SelectPreset(HWND combo, const SYSTEMTIME& time) const {
    int selected = -1;
    int count = static_cast<int>(SendMessageW(combo, CB_GETCOUNT, 0, 0));
    for (int item = 0; item < count; item++) {
        LRESULT index = SendMessageW(combo, CB_GETITEMDATA, item, 0);
        if (index >= 0
                && index < static_cast<LRESULT>(presets.size())
                && CompareCalculatorDates(presets[index].time, time) == 0) {
            selected = item;
            break;
        }
    }
    if (SendMessageW(combo, CB_GETCURSEL, 0, 0) != selected) {
        SendMessageW(combo, CB_SETCURSEL, selected, 0);
    }
}

/// Refills all preset views after an actual collection or language change, retaining the chosen dates.
void TimeCalculatorForm::FillPresets() {
    if (presetDates.size() != presets.size() || presetLanguage != appLanguage) {
        presetDates.clear();
        presetDates.reserve(presets.size());
        for (const TimeCalculatorPreset& preset : presets) {
            presetDates.push_back(FormatCalculatorPreset(preset, timeZones, GetLanguageLocale(appLanguage)));
        }
        presetLanguage = appLanguage;
    }
    updating = true;
    const HWND combos[] = {
        GetDlgItem(pages[0], ID_CALC_FROM_PRESET),
        GetDlgItem(pages[0], ID_CALC_TO_PRESET),
        GetDlgItem(pages[1], ID_CALC_PRESET)
    };
    for (HWND combo : combos) {
        SendMessageW(combo, CB_RESETCONTENT, 0, 0);
    }
    HWND list = GetDlgItem(pages[2], ID_CALC_LIST);
    WindowRedrawScope redraw(list);
    ListView_DeleteAllItems(list);
    for (size_t index = 0; index < presets.size(); index++) {
        const TimeCalculatorPreset& preset = presets[index];
        std::wstring date = presetDates[index];
        LVITEMW item = {};
        item.mask = LVIF_TEXT | LVIF_PARAM;
        item.iItem = static_cast<int>(index);
        item.pszText = date.data();
        item.lParam = index;
        int row = ListView_InsertItem(list, &item);
        ListView_SetItemText(list, row, 1, const_cast<wchar_t*>(preset.description.c_str()));
    }
    ApplyPresetSort();
    UpdatePresetColumns();
    for (int row = 0; row < ListView_GetItemCount(list); row++) {
        LVITEMW item = {};
        item.mask = LVIF_PARAM;
        item.iItem = row;
        if (!ListView_GetItem(list, &item)) {
            continue;
        }
        const TimeCalculatorPreset& preset = presets[item.lParam];
        std::wstring caption = presetDates[item.lParam] + L" — " + preset.description;
        for (HWND combo : combos) {
            LRESULT inserted = SendMessageW(combo, CB_ADDSTRING, 0,
                reinterpret_cast<LPARAM>(caption.c_str()));
            if (inserted >= 0) {
                SendMessageW(combo, CB_SETITEMDATA, inserted, item.lParam);
            }
        }
    }
    SelectPreset(combos[0], state.from);
    SelectPreset(combos[1], state.to);
    SelectPreset(combos[2], state.start);
    bool hasPresets = !presets.empty();
    EnableWindow(combos[0], hasPresets && !state.fromNow);
    EnableWindow(combos[1], hasPresets && !state.toNow);
    EnableWindow(combos[2], hasPresets);
    updating = false;
    UpdatePresetButtons();
}

/// Fits the date column to its header and all values, leaving the remaining client width for descriptions.
void TimeCalculatorForm::UpdatePresetColumns() const {
    HWND list = GetDlgItem(pages[2], ID_CALC_LIST);
    ListView_SetColumnWidth(list, 0, LVSCW_AUTOSIZE);
    int dateWidth = ListView_GetColumnWidth(list, 0);
    ListView_SetColumnWidth(list, 0, LVSCW_AUTOSIZE_USEHEADER);
    ListView_SetColumnWidth(list, 0, std::max(dateWidth, ListView_GetColumnWidth(list, 0)));
    ListView_SetColumnWidth(list, 1, LVSCW_AUTOSIZE_USEHEADER);
}

/// Applies the chosen preset order and native header arrow, matching the Settings lists.
void TimeCalculatorForm::ApplyPresetSort() const {
    HWND list = GetDlgItem(pages[2], ID_CALC_LIST);
    ListView_SortItems(list, ComparePresets, reinterpret_cast<LPARAM>(this));
    HWND header = ListView_GetHeader(list);
    if (header == nullptr) {
        return;
    }
    for (int column = 0; column < 2; column++) {
        HDITEMW item = {};
        item.mask = HDI_FORMAT;
        if (!Header_GetItem(header, column, &item)) {
            continue;
        }
        item.fmt &= ~(HDF_SORTUP | HDF_SORTDOWN);
        if (column == sortColumn) {
            item.fmt |= sortDescending ? HDF_SORTDOWN : HDF_SORTUP;
        }
        Header_SetItem(header, column, &item);
    }
}

/// Sorts native list items by timestamp or localized description while retaining stable preset indices.
int CALLBACK TimeCalculatorForm::ComparePresets(LPARAM first, LPARAM second, LPARAM parameter) {
    const TimeCalculatorForm* form = reinterpret_cast<const TimeCalculatorForm*>(parameter);
    const TimeCalculatorPreset& left = form->presets[first];
    const TimeCalculatorPreset& right = form->presets[second];
    int order = 0;
    if (form->sortColumn == 0) {
        order = CompareCalculatorDates(left.time, right.time);
    } else {
        order = CompareStringEx(GetLanguageLocale(appLanguage), SORT_STRINGSORT,
            left.description.c_str(), -1, right.description.c_str(), -1, nullptr, nullptr, 0) - CSTR_EQUAL;
    }
    return form->sortDescending ? -order : order;
}

/// Enables preset actions according to selection, editable text and the shared persistence limits.
void TimeCalculatorForm::UpdatePresetButtons() const {
    HWND list = GetDlgItem(pages[2], ID_CALC_LIST);
    UINT selected = ListView_GetSelectedCount(list);
    EnableWindow(GetDlgItem(pages[2], ID_CALC_EDIT), selected == 1);
    EnableWindow(GetDlgItem(pages[2], ID_CALC_DELETE), selected != 0);
    bool capacity = editing >= 0 || presets.size() < TIME_CALCULATOR_MAX_PRESETS;
    bool hasDescription = false;
    for (wchar_t character : entryDescription) {
        hasDescription = hasDescription || !IsUnicodeWhitespace(character);
    }
    EnableWindow(GetDlgItem(pages[2], ID_CALC_ADD), capacity && hasDescription && inputValid[3]);
    EnableWindow(GetDlgItem(pages[2], ID_CALC_CANCEL), editing >= 0);
    SetCalculatorText(pages[2], ID_CALC_ADD, T(editing >= 0 ? TXT_SAVE : TXT_ADD));
}

/// Adds or updates one minute-precision preset, confirming a duplicate date before saving the collection.
void TimeCalculatorForm::SavePreset() {
    std::wstring description = GetControlText(descriptionEdit);
    size_t begin = 0;
    while (begin < description.size() && IsUnicodeWhitespace(description[begin])) {
        begin++;
    }
    size_t end = description.size();
    while (end > begin && IsUnicodeWhitespace(description[end - 1])) {
        end--;
    }
    if (begin == end
            || description.size() > TIME_CALCULATOR_MAX_DESCRIPTION
            || editing < 0 && presets.size() >= TIME_CALCULATOR_MAX_PRESETS
            || !inputValid[3]
            || !TimeCalculator::Normalize(&entryTime)) {
        return;
    }
    bool changedDate = editing < 0 || CompareCalculatorDates(entryTime, presets[editing].time) != 0;
    for (size_t index = 0; index < presets.size(); index++) {
        if (changedDate
                && static_cast<int>(index) != editing
                && CompareCalculatorDates(entryTime, presets[index].time) == 0) {
            unsigned long revision = presetsRevision;
            int answer = MessageBoxW(window, T(TXT_CALCULATOR_DUPLICATE), T(TXT_TIME_CALCULATOR),
                MB_YESNO | MB_ICONQUESTION);
            if (answer != IDYES || revision != presetsRevision) {
                return;
            }
            break;
        }
    }
    TimeCalculatorPreset preset{ entryTime, description, entryZone };
    std::vector<TimeCalculatorPreset> updated = presets;
    if (editing >= 0) {
        updated[editing] = preset;
    } else {
        updated.push_back(preset);
    }
    if (SavePresets(updated)) {
        SetFocus(GetDlgItem(pages[2], ID_CALC_DATE));
    }
}

/// Loads the selected preset into the existing editor so editing needs no additional modal form.
void TimeCalculatorForm::EditPreset() {
    HWND list = GetDlgItem(pages[2], ID_CALC_LIST);
    if (ListView_GetSelectedCount(list) != 1) {
        return;
    }
    LVITEMW item = {};
    item.mask = LVIF_PARAM;
    item.iItem = ListView_GetNextItem(list, -1, LVNI_SELECTED);
    if (!ListView_GetItem(list, &item)) {
        return;
    }
    editing = static_cast<int>(item.lParam);
    const TimeCalculatorPreset& preset = presets[editing];
    entryTime = preset.time;
    entryZone = preset.zone;
    entryDescription = preset.description;
    updating = true;
    FillTimeZones(3);
    UpdateTimeInput(3, true);
    SetWindowTextW(descriptionEdit, entryDescription.c_str());
    updating = false;
    UpdatePresetButtons();
}

/// Removes exactly the selected preset records, independent of the current native sort order.
void TimeCalculatorForm::DeletePresets() {
    HWND list = GetDlgItem(pages[2], ID_CALC_LIST);
    std::vector<int> indices;
    int row = -1;
    while ((row = ListView_GetNextItem(list, row, LVNI_SELECTED)) != -1) {
        LVITEMW item = {};
        item.mask = LVIF_PARAM;
        item.iItem = row;
        if (ListView_GetItem(list, &item)) {
            indices.push_back(static_cast<int>(item.lParam));
        }
    }
    if (indices.empty()) {
        return;
    }
    UINT flags = MB_OKCANCEL | MB_ICONWARNING;
    if (indices.size() > 1) {
        flags |= MB_DEFBUTTON2;
    }
    unsigned long revision = presetsRevision;
    int answer = MessageBoxW(window, T(TXT_CALCULATOR_DELETE_CONFIRM), T(TXT_TIME_CALCULATOR), flags);
    if (answer != IDOK || revision != presetsRevision) {
        return;
    }
    std::sort(indices.begin(), indices.end(), std::greater<int>());
    std::vector<TimeCalculatorPreset> updated = presets;
    for (int index : indices) {
        updated.erase(updated.begin() + index);
    }
    SavePresets(updated);
}

/// Ends inline editing while leaving the chosen date ready for another preset.
void TimeCalculatorForm::CancelEdit() {
    editing = -1;
    entryDescription.clear();
    SetWindowTextW(descriptionEdit, L"");
    UpdatePresetButtons();
}

/// Provides the original preset editor's edit, delete and select-all commands with localized captions.
void TimeCalculatorForm::ShowPresetMenu(LPARAM position) {
    HWND list = GetDlgItem(pages[2], ID_CALC_LIST);
    HMENU menu = CreatePopupMenu();
    if (menu == nullptr) {
        return;
    }
    UINT count = ListView_GetSelectedCount(list);
    AppendMenuW(menu, MF_STRING | (count == 1 ? MF_ENABLED : MF_GRAYED), ID_CALC_EDIT,
        T(TXT_CALCULATOR_EDIT));
    AppendMenuW(menu, MF_STRING | (count > 0 ? MF_ENABLED : MF_GRAYED), ID_CALC_DELETE,
        T(TXT_CALCULATOR_DELETE));
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendMenuW(menu, MF_STRING, CALCULATOR_SELECT_ALL, T(TXT_CALCULATOR_SELECT_ALL));
    POINT point = { GET_X_LPARAM(position), GET_Y_LPARAM(position) };
    if (point.x == -1 && point.y == -1) {
        RECT bounds = {};
        GetWindowRect(list, &bounds);
        point = POINT{ bounds.left, bounds.top };
    }
    int command = TrackPopupMenu(menu, TPM_RETURNCMD | TPM_RIGHTBUTTON, point.x, point.y, 0, window, nullptr);
    DestroyMenu(menu);
    if (command == CALCULATOR_SELECT_ALL) {
        ListView_SetItemState(list, -1, LVIS_SELECTED, LVIS_SELECTED);
    } else if (command != 0) {
        HandleCommand(nullptr, command, BN_CLICKED);
    }
}

/// Routes buttons and native preset combo notifications to the calculator's own state.
void TimeCalculatorForm::HandleCommand(HWND source, int id, int notification) {
    if (updating) {
        return;
    }
    if (notification == CBN_DROPDOWN) {
        if (id >= ID_CALC_ZONE_BASE && id < ID_CALC_ZONE_BASE + 4) {
            FillTimeZones(id - ID_CALC_ZONE_BASE);
            RequestCalculation(false, true);
        }
    }
    if (HandleApplicationComboNotification(source, &notification, comboState)) {
        return;
    }
    if (notification == CBN_SELCHANGE && id >= ID_CALC_OFFSET_BASE && id < ID_CALC_OFFSET_BASE + 4) {
        int index = id - ID_CALC_OFFSET_BASE;
        int choice = static_cast<int>(SendMessageW(source, CB_GETCURSEL, 0, 0));
        UpdateTimeInput(index, false, choice);
        if (index == 2) {
            UpdateHighlights();
        } else {
            UpdateResults();
        }
        UpdatePresetButtons();
        return;
    }
    if (notification == CBN_SELCHANGE && id >= ID_CALC_ZONE_BASE && id < ID_CALC_ZONE_BASE + 4) {
        int index = id - ID_CALC_ZONE_BASE;
        LRESULT selected = SendMessageW(source, CB_GETCURSEL, 0, 0);
        LRESULT zone = SendMessageW(source, CB_GETITEMDATA, selected, 0);
        if (selected >= 0 && zone >= 0 && zone < static_cast<LRESULT>(timeZones.size())) {
            std::wstring* keys[] = { &state.fromZone, &state.toZone, &state.startZone, &entryZone };
            *keys[index] = timeZones[zone].TimeZoneKeyName;
            UpdateTimeInput(index, true);
            if (index == 2) {
                UpdateHighlights();
            } else {
                UpdateResults();
            }
            UpdatePresetButtons();
        }
        return;
    }
    if (notification == CBN_SELCHANGE) {
        LRESULT selected = SendMessageW(source, CB_GETCURSEL, 0, 0);
        if (selected >= 0) {
            selected = SendMessageW(source, CB_GETITEMDATA, selected, 0);
        }
        if (selected < 0 || selected >= static_cast<LRESULT>(presets.size())) {
            return;
        }
        int index = -1;
        if (id == ID_CALC_FROM_PRESET) {
            index = 0;
        } else if (id == ID_CALC_TO_PRESET) {
            index = 1;
        } else if (id == ID_CALC_PRESET) {
            index = 2;
        }
        if (index < 0) {
            return;
        }
        SYSTEMTIME* times[] = { &state.from, &state.to, &state.start };
        std::wstring* keys[] = { &state.fromZone, &state.toZone, &state.startZone };
        *times[index] = presets[selected].time;
        bool zoneChanged = *keys[index] != presets[selected].zone;
        *keys[index] = presets[selected].zone;
        if (zoneChanged) {
            FillTimeZones(index);
        }
        UpdateTimeInput(index, true);
        if (index == 2) {
            UpdateHighlights();
        } else {
            UpdateResults();
        }
        return;
    }
    if (id == ID_CALC_DESCRIPTION && notification == EN_CHANGE) {
        entryDescription = GetControlText(source);
        UpdatePresetButtons();
        return;
    }
    if (notification != BN_CLICKED) {
        return;
    }
    if (id >= ID_CALC_HIGHLIGHT_BASE && id < ID_CALC_HIGHLIGHT_BASE + TIME_CALCULATOR_HIGHLIGHT_COUNT) {
        DWORD flag = CALCULATOR_HIGHLIGHT_FLAGS[id - ID_CALC_HIGHLIGHT_BASE];
        if (IsDlgButtonChecked(pages[3], id) == BST_CHECKED) {
            state.highlights |= flag;
        } else {
            state.highlights &= ~flag;
        }
        RequestCalculation(true);
    } else if (id == ID_CALC_FROM_NOW || id == ID_CALC_TO_NOW) {
        state.fromNow = IsDlgButtonChecked(pages[0], ID_CALC_FROM_NOW) == BST_CHECKED;
        state.toNow = IsDlgButtonChecked(pages[0], ID_CALC_TO_NOW) == BST_CHECKED;
        UpdateTimeInput(id == ID_CALC_FROM_NOW ? 0 : 1, true);
        UpdateNow();
    } else if (id == ID_CALC_ADD) {
        SavePreset();
    } else if (id == ID_CALC_EDIT) {
        EditPreset();
    } else if (id == ID_CALC_DELETE) {
        DeletePresets();
    } else if (id == ID_CALC_IMPORT) {
        ImportPresets();
    } else if (id == ID_CALC_EXPORT) {
        ExportPresets();
    } else if (id == ID_CALC_CANCEL) {
        CancelEdit();
    }
}

/// Handles picker changes, calendar bold-day requests and the preset list's native keyboard and sorting.
INT_PTR TimeCalculatorForm::HandleNotification(NMHDR* notification) {
    if (notification == nullptr) {
        return FALSE;
    }
    if (notification->code == MCN_GETDAYSTATE) {
        NMDAYSTATE* request = reinterpret_cast<NMDAYSTATE*>(notification);
        FillDayStates(request->stStart, request->cDayState);
        request->prgDayState = dayStates.data();
        return TRUE;
    }
    if (updating) {
        return FALSE;
    }
    if (notification->code == TCN_SELCHANGE) {
        state.tab = TabCtrl_GetCurSel(GetDlgItem(window, ID_CALC_TABS));
        SelectPage();
        return TRUE;
    }
    if (notification->code == DTN_DATETIMECHANGE) {
        const NMDATETIMECHANGE* change = reinterpret_cast<const NMDATETIMECHANGE*>(notification);
        if (change->dwFlags != GDT_VALID) {
            return TRUE;
        }
        SYSTEMTIME date = change->st;
        if (!TimeCalculator::Normalize(&date)) {
            return TRUE;
        }
        for (int index = 0; index < 4; index++) {
            if (notification->idFrom == static_cast<UINT_PTR>(CALCULATOR_INPUT_IDS[index])) {
                UpdateTimeInput(index, false);
                if (index == 2) {
                    UpdateHighlights();
                }
            }
        }
        UpdatePresetButtons();
        SelectPreset(GetDlgItem(pages[0], ID_CALC_FROM_PRESET), state.from);
        SelectPreset(GetDlgItem(pages[0], ID_CALC_TO_PRESET), state.to);
        SelectPreset(GetDlgItem(pages[1], ID_CALC_PRESET), state.start);
        UpdateResults();
        return TRUE;
    }
    if (notification->code == DTN_DROPDOWN) {
        HWND calendar = DateTime_GetMonthCal(notification->hwndFrom);
        ApplyControlStyle(calendar, reinterpret_cast<LPARAM>(this));
        DialogFrame::ApplyControl(calendar, window);
        if (GetWindowTheme(calendar) == nullptr) {
            StyleCalculatorCalendar(calendar, window);
            SetWindowSubclass(GetParent(calendar), CalculatorPopupProc, CALCULATOR_LOCALE_SUBCLASS,
                reinterpret_cast<DWORD_PTR>(calendar));
        }
        return TRUE;
    }
    if (notification->code == MCN_SELCHANGE) {
        MonthCal_GetCurSel(notification->hwndFrom, &state.day);
        UpdateResults();
        return TRUE;
    }
    if (notification->idFrom == ID_CALC_LIST) {
        if (notification->code == LVN_COLUMNCLICK) {
            const NMLISTVIEW* column = reinterpret_cast<const NMLISTVIEW*>(notification);
            sortDescending = sortColumn == column->iSubItem && !sortDescending;
            sortColumn = column->iSubItem;
            ApplyPresetSort();
        } else if (notification->code == LVN_ITEMCHANGED) {
            UpdatePresetButtons();
        } else if (notification->code == NM_DBLCLK) {
            EditPreset();
        } else if (notification->code == LVN_KEYDOWN) {
            const NMLVKEYDOWN* key = reinterpret_cast<const NMLVKEYDOWN*>(notification);
            if (key->wVKey == VK_DELETE) {
                DeletePresets();
            } else if (key->wVKey == VK_F2 || key->wVKey == VK_RETURN) {
                EditPreset();
            } else if (key->wVKey == 'A' && GetKeyState(VK_CONTROL) < 0) {
                ListView_SetItemState(notification->hwndFrom, -1, LVIS_SELECTED, LVIS_SELECTED);
            }
        }
    }
    return FALSE;
}

/// Preserves native dialog navigation while using Enter to commit the preset editor rather than close it.
bool TimeCalculatorForm::ProcessMessage(MSG* message) {
    if (opening != nullptr || window == nullptr) {
        return false;
    }
    if (message->message == WM_MOUSEWHEEL
        && ScrollDialogTabHeaders(window, GetDlgItem(window, ID_CALC_TABS),
            message->wParam, message->lParam)) {
        return true;
    }
    bool belongs = message->hwnd == window || IsChild(window, message->hwnd);
    if (!belongs) {
        return false;
    }
    if (message->message == WM_KEYDOWN
            && message->wParam == VK_TAB
            && GetKeyState(VK_CONTROL) < 0) {
        bool backwards = GetKeyState(VK_SHIFT) < 0;
        state.tab = (state.tab + (backwards ? TIME_CALCULATOR_PAGE_COUNT - 1 : 1))
            % TIME_CALCULATOR_PAGE_COUNT;
        SelectPage();
        HWND tabs = GetDlgItem(window, ID_CALC_TABS);
        SendMessageW(window, WM_CHANGEUISTATE, MAKEWPARAM(UIS_CLEAR, UISF_HIDEFOCUS), 0);
        SendMessageW(window, WM_NEXTDLGCTL, reinterpret_cast<WPARAM>(tabs), TRUE);
        return true;
    }
    if (message->message == WM_KEYDOWN
            && message->wParam == VK_TAB
            && GetKeyState(VK_CONTROL) >= 0
            && state.tab == 3) {
        HWND tabs = GetDlgItem(window, ID_CALC_TABS);
        int index = GetDlgCtrlID(message->hwnd) - ID_CALC_HIGHLIGHT_BASE;
        if (message->hwnd == tabs || index >= 0 && index < TIME_CALCULATOR_HIGHLIGHT_COUNT) {
            bool backwards = GetKeyState(VK_SHIFT) < 0;
            if (message->hwnd == tabs) {
                index = backwards ? TIME_CALCULATOR_HIGHLIGHT_COUNT - 1 : 0;
            } else {
                index += backwards ? -1 : 1;
            }
            HWND target = tabs;
            if (index >= 0 && index < TIME_CALCULATOR_HIGHLIGHT_COUNT) {
                target = GetDlgItem(pages[3], ID_CALC_HIGHLIGHT_BASE + index);
            }
            SendMessageW(window, WM_CHANGEUISTATE, MAKEWPARAM(UIS_CLEAR, UISF_HIDEFOCUS), 0);
            SendMessageW(window, WM_NEXTDLGCTL, reinterpret_cast<WPARAM>(target), TRUE);
            return true;
        }
    }
    if (message->message == WM_KEYDOWN
            && message->wParam == VK_ESCAPE
            && comboState.open == nullptr
            && state.tab == 2
            && editing >= 0) {
        CancelEdit();
        return true;
    }
    if (message->message == WM_KEYDOWN && message->wParam == VK_RETURN && state.tab == 2) {
        int id = GetDlgCtrlID(message->hwnd);
        if (id == ID_CALC_DATE) {
            HWND edit = descriptionEdit;
            SetFocus(edit);
            SendMessageW(edit, EM_SETSEL, 0, -1);
            return true;
        }
        if (id == ID_CALC_DESCRIPTION) {
            SavePreset();
            return true;
        }
        if (id == ID_CALC_LIST) {
            EditPreset();
            return true;
        }
    }
    return IsDialogMessageW(window, message) != FALSE;
}

/// Handles calculator lifetime, data notifications, live Now values and application appearance changes.
INT_PTR TimeCalculatorForm::HandleMessage(HWND dialog, UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_GETFONT && uiFont != nullptr) {
        SetWindowLongPtrW(dialog, DWLP_MSGRESULT, reinterpret_cast<LONG_PTR>(uiFont));
        return TRUE;
    }
    if (message == WM_DRAWITEM) {
        const DRAWITEMSTRUCT* item = reinterpret_cast<const DRAWITEMSTRUCT*>(lParam);
        HWND reference = nullptr;
        if (item == nullptr || item->CtlType != ODT_STATIC) {
            return FALSE;
        }
        if (item->CtlID == ID_CALC_INTERVAL_NOTE) {
            reference = GetDlgItem(dialog, ID_CALC_UNIT_BASE);
        } else if (item->CtlID == ID_CALC_ROUND_NOTE) {
            reference = GetDlgItem(dialog, ID_CALC_DAY_UNIT_BASE);
        }
        RECT row = {};
        if (reference != nullptr) {
            GetClientRect(reference, &row);
        }
        return DrawWrappedTextItem(item, row.bottom - row.top);
    }
    if (message == WM_COMMAND) {
        int id = LOWORD(wParam);
        if (id == IDCANCEL) {
            Close();
            SaveAllSettings();
        } else {
            HandleCommand(reinterpret_cast<HWND>(lParam), id, HIWORD(wParam));
        }
        return TRUE;
    }
    if (message == WM_NOTIFY) {
        return HandleNotification(reinterpret_cast<NMHDR*>(lParam));
    }
    if (message == WM_CONTEXTMENU && reinterpret_cast<HWND>(wParam) == GetDlgItem(pages[2], ID_CALC_LIST)) {
        ShowPresetMenu(lParam);
        return TRUE;
    }
    if (dialog != window) {
        return FALSE;
    }
    if (message == WM_CLOSE) {
        Close();
        SaveAllSettings();
        return TRUE;
    }
    if (message == CALCULATOR_CALCULATE) {
        calculationQueued = false;
        StartCalculation();
        return TRUE;
    }
    if (message == CALCULATOR_READY) {
        CompleteCalculation(wParam);
        return TRUE;
    }
    if (message == WM_TIMER && wParam == CALCULATOR_TIMER) {
        if (state.fromNow || state.toNow) {
            SYSTEMTIME now = {};
            GetSystemTime(&now);
            TimeCalculator::Normalize(&now);
            if (CompareCalculatorDates(now, lastNow) != 0) {
                UpdateNow();
            }
        }
        return TRUE;
    }
    if (message == WM_THEMECHANGED || message == WM_SETTINGCHANGE || message == WM_TIMECHANGE) {
        UpdateApplicationWindowIcons(window);
        ApplyStyle(true);
        if (message == WM_SETTINGCHANGE || message == WM_TIMECHANGE) {
            Refresh();
        }
        return TRUE;
    }
    if (message == WM_DPICHANGED) {
        const RECT* suggested = reinterpret_cast<const RECT*>(lParam);
        SetWindowPos(window, nullptr, suggested->left, suggested->top, 0, 0,
            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS);
        UpdateApplicationWindowIcons(window);
        ApplyStyle(true);
        return TRUE;
    }
    if (message == WM_SIZE || message == WM_DISPLAYCHANGE) {
        Layout();
        return TRUE;
    }
    if ((message == WM_VSCROLL || message == WM_HSCROLL) && lParam == 0) {
        Scroll(message == WM_VSCROLL ? SB_VERT : SB_HORZ, LOWORD(wParam));
        return TRUE;
    }
    if (message == WM_MOUSEWHEEL) {
        if (ScrollDialogTabHeaders(window, GetDlgItem(window, ID_CALC_TABS), wParam, lParam)) {
            return TRUE;
        }
        LONG_PTR style = GetWindowLongPtrW(window, GWL_STYLE);
        int bar = (GET_KEYSTATE_WPARAM(wParam) & MK_SHIFT) != 0 && (style & WS_HSCROLL) != 0
            ? SB_HORZ
            : SB_VERT;
        if (bar == SB_HORZ && (style & WS_HSCROLL) == 0 || bar == SB_VERT && (style & WS_VSCROLL) == 0) {
            return FALSE;
        }
        int delta = GET_WHEEL_DELTA_WPARAM(wParam);
        for (int index = 0; index < abs(delta) / WHEEL_DELTA * 3; index++) {
            Scroll(bar, delta > 0 ? SB_LINEUP : SB_LINEDOWN);
        }
        return TRUE;
    }
    if (message == WM_NCDESTROY) {
        if (calculation != nullptr) {
            calculation->cancelled.store(true);
            calculation.reset();
        }
        calculationPending = false;
        calculationQueued = false;
        highlightsPending = false;
        labelsPending = false;
        dayStates.clear();
        firstMonth = SYSTEMTIME{};
        presetsRevision++;
        KillTimer(window, CALCULATOR_TIMER);
        ReleaseApplicationWindowIcons(window);
        if (ownsFont) {
            DeleteObject(uiFont);
        }
        window = nullptr;
        descriptionEdit = nullptr;
        comboState = ApplicationComboState{};
        uiFont = nullptr;
        ownsFont = false;
        initialized = false;
        initializing = false;
        controls.clear();
        for (HWND& page : pages) {
            page = nullptr;
        }
    }
    return FALSE;
}

/// Associates both the main dialog and its child pages with the same calculator instance.
INT_PTR CALLBACK TimeCalculatorForm::DialogProc(HWND dialog, UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_INITDIALOG) {
        TimeCalculatorForm* form = reinterpret_cast<TimeCalculatorForm*>(lParam);
        SetWindowLongPtrW(dialog, DWLP_USER, reinterpret_cast<LONG_PTR>(form));
        if (form->window == nullptr) {
            form->window = dialog;
        }
        return FALSE;
    }
    TimeCalculatorForm* form = reinterpret_cast<TimeCalculatorForm*>(GetWindowLongPtrW(dialog, DWLP_USER));
    return form == nullptr ? FALSE : form->HandleMessage(dialog, message, wParam, lParam);
}
