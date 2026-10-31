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
 * Last modified for version 1.6.3.0
 */

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "PersistWindowState.h"
#include <commctrl.h>
#include <winver.h>

#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "Version.lib")

/// Physical monitor bounds and the corresponding taskbar-adjusted work area.
struct MonitorWorkArea {
    RECT monitor;
    RECT work;
};

/// Owned monitor work areas and the first error reported during enumeration.
struct MonitorCollection {
    MonitorWorkArea* areas;
    UINT count;
    DWORD error;
};

/// Best usable window rectangle and its area and distance ranking.
struct PlacementCandidate {
    RECT bounds;
    LONGLONG area;
    LONGLONG distance;
    bool found;
};

/// Identity and matching options used while locating another instance of a form.
struct ExistingFormSearch {
    HWND target;
    HWND existing;
    const char* property;
    const wchar_t* title;
    WindowDetectionOptions options;
    DWORD error;
};

/// Language and code-page pair identifying a version-resource string table.
struct VersionResourceTranslation {
    WORD language;
    WORD codePage;
};

static const wchar_t placementProperty[] = L"FortSoft.PersistWindowState";

/// Adds a physical monitor and its taskbar-adjusted work rectangle to the owned collection.
static BOOL CALLBACK CollectMonitor(HMONITOR monitor, HDC, RECT*, LPARAM parameter) {
    MonitorCollection* collection = reinterpret_cast<MonitorCollection*>(parameter);
    MONITORINFO information = { sizeof(information) };
    if (!GetMonitorInfoW(monitor, &information)) {
        collection->error = GetLastError();
        return FALSE;
    }
    if (IsRectEmpty(&information.rcWork)) {
        return TRUE;
    }
    SIZE_T bytes = static_cast<SIZE_T>(collection->count + 1) * sizeof(MonitorWorkArea);
    void* memory = collection->areas
        ? HeapReAlloc(GetProcessHeap(), 0, collection->areas, bytes)
        : HeapAlloc(GetProcessHeap(), 0, bytes);
    if (!memory) {
        collection->error = ERROR_NOT_ENOUGH_MEMORY;
        return FALSE;
    }
    collection->areas = static_cast<MonitorWorkArea*>(memory);
    collection->areas[collection->count++] = MonitorWorkArea{ information.rcMonitor, information.rcWork };
    return TRUE;
}

/// Reads physical monitor work areas through the native monitor APIs.
static DWORD ReadMonitorWorkAreas(MonitorWorkArea** areas, UINT* count) {
    if (!areas || !count) {
        return ERROR_INVALID_PARAMETER;
    }
    *areas = nullptr;
    *count = 0;
    MonitorCollection collection = MonitorCollection{ nullptr, 0, ERROR_SUCCESS };
    if (EnumDisplayMonitors(nullptr, nullptr, CollectMonitor, reinterpret_cast<LPARAM>(&collection)) && collection.count) {
        *areas = collection.areas;
        *count = collection.count;
        return ERROR_SUCCESS;
    }
    HeapFree(GetProcessHeap(), 0, collection.areas);
    return collection.error ? collection.error : ERROR_GEN_FAILURE;
}

/// Reads the native monitor associated with a maximized or minimized window.
static bool ReadWindowMonitorWorkArea(HWND window, MonitorWorkArea* area) {
    MONITORINFO native = { sizeof(native) };
    if (!GetMonitorInfoW(MonitorFromWindow(window, MONITOR_DEFAULTTONEAREST), &native)) {
        return false;
    }
    *area = MonitorWorkArea{ native.rcMonitor, native.rcWork };
    return true;
}

/// Returns squared screen-coordinate separation without losing precision for negative monitor coordinates.
static LONGLONG Distance(LONG x, LONG y) {
    return static_cast<LONGLONG>(x) * x + static_cast<LONGLONG>(y) * y;
}

/// Finds the monitor with greatest intersection or smallest separation from a screen rectangle.
static UINT NearestMonitorWorkArea(const RECT& bounds, const MonitorWorkArea* areas, UINT count) {
    UINT nearest = 0;
    LONGLONG greatest = -1;
    LONGLONG closest = 0;
    for (UINT index = 0; index < count; ++index) {
        const RECT& monitor = areas[index].monitor;
        RECT intersection = RECT{};
        IntersectRect(&intersection, &bounds, &monitor);
        LONGLONG area = (static_cast<LONGLONG>(intersection.right) - intersection.left)
            * (static_cast<LONGLONG>(intersection.bottom) - intersection.top);
        LONG dx = bounds.right < monitor.left
            ? monitor.left - bounds.right
            : monitor.right < bounds.left ? bounds.left - monitor.right : 0;
        LONG dy = bounds.bottom < monitor.top
            ? monitor.top - bounds.bottom
            : monitor.bottom < bounds.top ? bounds.top - monitor.bottom : 0;
        LONGLONG distance = Distance(dx, dy);
        if (area > greatest || area == greatest && distance < closest) {
            nearest = index;
            greatest = area;
            closest = distance;
        }
    }
    return nearest;
}

/// Clamps one coordinate to an available interval while retaining the near edge for oversized fixed forms.
static LONG ClampPosition(LONG value, LONG minimum, LONG maximum) {
    return value < minimum || maximum < minimum ? minimum : value > maximum ? maximum : value;
}

/// Retains the largest usable window and then the placement nearest its requested screen location.
static void ConsiderCandidate(const RECT& bounds, const RECT& requested, PlacementCandidate* best) {
    LONGLONG area = (static_cast<LONGLONG>(bounds.right) - bounds.left)
        * (static_cast<LONGLONG>(bounds.bottom) - bounds.top);
    LONGLONG distance = Distance(bounds.left - requested.left, bounds.top - requested.top);
    if (!best->found || area > best->area || area == best->area && distance < best->distance) {
        best->bounds = bounds;
        best->area = area;
        best->distance = distance;
        best->found = true;
    }
}

/// Tests complete containment in the work-area union, including taskbar strips and gaps between monitors.
static bool RegionContains(HRGN available, HRGN rectangle, HRGN outside, const RECT& bounds) {
    return SetRectRgn(rectangle, bounds.left, bounds.top, bounds.right, bounds.bottom)
        && CombineRgn(outside, rectangle, available, RGN_DIFF) == NULLREGION;
}

/// Inserts an edge into an ordered coordinate array, suppressing duplicates.
static void InsertEdge(LONG* edges, UINT* count, LONG value) {
    UINT index = 0;
    while (index < *count && edges[index] < value) {
        ++index;
    }
    if (index < *count&& edges[index] == value) {
        return;
    }
    for (UINT current = *count; current > index; --current) {
        edges[current] = edges[current - 1];
    }
    edges[index] = value;
    ++*count;
}

/// Fits a window to the union of actual work areas, retaining spans across adjacent monitors and fixed dimensions.
static bool FitWindowToWorkAreas(RECT* bounds, const MonitorWorkArea* areas, UINT count, bool resizeWidth,
        bool resizeHeight, SIZE minimum = SIZE{ 0, 0 }) {
    if (!count || IsRectEmpty(bounds)) {
        return false;
    }
    HRGN available = CreateRectRgn(0, 0, 0, 0);
    HRGN rectangle = CreateRectRgn(0, 0, 0, 0);
    HRGN outside = CreateRectRgn(0, 0, 0, 0);
    LONG* edges = static_cast<LONG*>(HeapAlloc(GetProcessHeap(), 0, 4 * static_cast<SIZE_T>(count) * sizeof(LONG)));
    if (!available || !rectangle || !outside || !edges) {
        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        DeleteObject(available);
        DeleteObject(rectangle);
        DeleteObject(outside);
        HeapFree(GetProcessHeap(), 0, edges);
        return false;
    }
    UINT xCount = 0;
    UINT yCount = 0;
    LONG* xEdges = edges;
    LONG* yEdges = edges + 2 * count;
    for (UINT index = 0; index < count; ++index) {
        const RECT& work = areas[index].work;
        SetRectRgn(rectangle, work.left, work.top, work.right, work.bottom);
        CombineRgn(available, available, rectangle, RGN_OR);
        InsertEdge(xEdges, &xCount, work.left);
        InsertEdge(xEdges, &xCount, work.right);
        InsertEdge(yEdges, &yCount, work.top);
        InsertEdge(yEdges, &yCount, work.bottom);
    }
    bool contained = RegionContains(available, rectangle, outside, *bounds);
    PlacementCandidate best = PlacementCandidate{};
    LONG width = bounds->right - bounds->left;
    LONG height = bounds->bottom - bounds->top;
    if (!contained) {
        for (UINT left = 0; left < xCount; ++left) {
            for (UINT right = left + 1; right < xCount; ++right) {
                for (UINT top = 0; top < yCount; ++top) {
                    for (UINT bottom = top + 1; bottom < yCount; ++bottom) {
                        RECT space = RECT{ xEdges[left], yEdges[top], xEdges[right], yEdges[bottom] };
                        if (!resizeWidth && width > space.right - space.left
                                || !resizeHeight && height > space.bottom - space.top
                                || !RegionContains(available, rectangle, outside, space)) {
                            continue;
                        }
                        LONG candidateWidth = resizeWidth && width > space.right - space.left
                            ? space.right - space.left
                            : width;
                        LONG candidateHeight = resizeHeight && height > space.bottom - space.top
                            ? space.bottom - space.top
                            : height;
                        if (candidateWidth < minimum.cx || candidateHeight < minimum.cy) {
                            continue;
                        }
                        LONG x = ClampPosition(bounds->left, space.left, space.right - candidateWidth);
                        LONG y = ClampPosition(bounds->top, space.top, space.bottom - candidateHeight);
                        ConsiderCandidate(RECT{ x, y, x + candidateWidth, y + candidateHeight }, *bounds, &best);
                    }
                }
            }
        }
        if (!best.found) {
            const RECT& work = areas[NearestMonitorWorkArea(*bounds, areas, count)].work;
            if (resizeWidth && width > work.right - work.left) {
                width = work.right - work.left < minimum.cx ? minimum.cx : work.right - work.left;
            }
            if (resizeHeight && height > work.bottom - work.top) {
                height = work.bottom - work.top < minimum.cy ? minimum.cy : work.bottom - work.top;
            }
            LONG x = ClampPosition(bounds->left, work.left, work.right - width);
            LONG y = ClampPosition(bounds->top, work.top, work.bottom - height);
            best.bounds = RECT{ x, y, x + width, y + height };
            best.found = true;
        }
    }
    if (best.found) {
        *bounds = best.bounds;
    }
    HeapFree(GetProcessHeap(), 0, edges);
    DeleteObject(outside);
    DeleteObject(rectangle);
    DeleteObject(available);
    return best.found;
}

/// Compares a requested span of Unicode title text without changing case or relying on the process main window.
static bool TitleSpanEqual(const wchar_t* first, const wchar_t* second, int length) {
    for (int index = 0; index < length; ++index) {
        if (first[index] != second[index]) {
            return false;
        }
    }
    return true;
}

/// Applies the original title-detection modes to registered forms of the same executable and form identity.
static bool TitleMatches(const wchar_t* title, const wchar_t* pattern, WindowDetectionOptions options) {
    int length = lstrlenW(title);
    int patternLength = lstrlenW(pattern);
    if (options == WindowDetectionOptions::Default) {
        return true;
    }
    if (length < patternLength) {
        return false;
    }
    if (options == WindowDetectionOptions::TitleEquals) {
        return length == patternLength && TitleSpanEqual(title, pattern, length);
    }
    if (options == WindowDetectionOptions::TitleStartsWith) {
        return TitleSpanEqual(title, pattern, patternLength);
    }
    if (options == WindowDetectionOptions::TitleEndsWith) {
        return TitleSpanEqual(title + length - patternLength, pattern, patternLength);
    }
    for (int index = 0; index <= length - patternLength; ++index) {
        if (TitleSpanEqual(title + index, pattern, patternLength)) {
            return true;
        }
    }
    return false;
}

/// Copies the complete native caption, preserving long form titles used by the original detection modes.
static wchar_t* CopyWindowCaption(HWND window) {
    int length = GetWindowTextLengthW(window);
    wchar_t* text =
        static_cast<wchar_t*>(HeapAlloc(GetProcessHeap(), 0, (static_cast<SIZE_T>(length) + 1) * sizeof(wchar_t)));
    if (!text) {
        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        return nullptr;
    }
    text[0] = 0;
    GetWindowTextW(window, text, length + 1);
    return text;
}

/// Finds another registered form on the current desktop, including forms in the same process.
static BOOL CALLBACK FindExistingForm(HWND window, LPARAM parameter) {
    ExistingFormSearch* search = reinterpret_cast<ExistingFormSearch*>(parameter);
    if (window != search->target && GetPropA(window, search->property)) {
        wchar_t* title = CopyWindowCaption(window);
        if (!title) {
            search->error = GetLastError();
            return FALSE;
        }
        bool matches = TitleMatches(title, search->title, search->options);
        HeapFree(GetProcessHeap(), 0, title);
        if (matches) {
            search->existing = window;
            return FALSE;
        }
    }
    return TRUE;
}

/// Adds a Unicode string to a pair of stable application-identity hashes without CRT dependencies.
static void HashIdentity(const wchar_t* text, DWORD* first, DWORD* second, bool ignoreCase = false) {
    for (const wchar_t* character = text; *character; ++character) {
        wchar_t value = *character;
        if (ignoreCase) {
            CharLowerBuffW(&value, 1);
        }
        *first = (*first ^ value) * 16777619;
        *second = (*second ^ value) * 65599;
    }
}

/// Converts restored bounds between screen and workspace coordinates without including taskbar offsets twice.
static RECT ConvertWorkspaceBounds(HWND window, RECT bounds, bool toScreen) {
    if (!(GetWindowLongPtrW(window, GWL_EXSTYLE) & WS_EX_TOOLWINDOW)) {
        MonitorWorkArea current = MonitorWorkArea{};
        if (toScreen && ReadWindowMonitorWorkArea(window, &current)) {
            OffsetRect(&bounds, current.work.left - current.monitor.left, current.work.top - current.monitor.top);
            return bounds;
        }
        MonitorWorkArea* areas = nullptr;
        UINT count = 0;
        if (ReadMonitorWorkAreas(&areas, &count) == ERROR_SUCCESS) {
            const MonitorWorkArea& area = areas[NearestMonitorWorkArea(bounds, areas, count)];
            LONG x = area.work.left - area.monitor.left;
            LONG y = area.work.top - area.monitor.top;
            OffsetRect(&bounds, toScreen ? x : -x, toScreen ? y : -y);
            HeapFree(GetProcessHeap(), 0, areas);
        }
    }
    return bounds;
}

/// Converts native restored bounds from workspace to screen coordinates, including top and left taskbars.
static bool ReadNormalWindowBounds(HWND window, RECT* bounds) {
    if (!IsIconic(window) && !IsZoomed(window)) {
        return GetWindowRect(window, bounds) != FALSE;
    }
    WINDOWPLACEMENT placement = WINDOWPLACEMENT{};
    placement.length = sizeof(placement);
    if (!GetWindowPlacement(window, &placement)) {
        return false;
    }
    *bounds = ConvertWorkspaceBounds(window, placement.rcNormalPosition, true);
    return true;
}

/// Reads application tracking limits through the native window procedure without changing the form.
static MINMAXINFO TrackingLimits(HWND window) {
    MINMAXINFO limits = MINMAXINFO{};
    SendMessageW(window, WM_GETMINMAXINFO, 0, reinterpret_cast<LPARAM>(&limits));
    return limits;
}

/// Applies native minimum and maximum dimensions to a resizable axis before restoring registry data.
static LONG ConstrainDimension(LONG value, LONG minimum, LONG maximum) {
    if (minimum > 0 && value < minimum) {
        value = minimum;
    }
    if (maximum > 0 && value > maximum) {
        value = maximum;
    }
    return value;
}

/// Creates a native state tracker with registry saving and Windows-selected initial bounds.
PersistWindowState::PersistWindowState()
    : window(nullptr), instanceMutex(nullptr), attached(false), registrationLocked(false), allowSaveMinimized(false),
    allowSaveTopMost(false), disableSaveHeight(false), disableSavePosition(false), disableSaveSize(false),
    disableSaveWidth(false), disableSaveWindowState(false), fixHeight(false), fixWidth(false),
    placeOnScreenAfterLoad(true), singleInstance(false), useWindowsDefaultLocation(true), useWindowsDefaultSize(true),
    hasState(false), applying(false), restoredShowState(false), detectionOptions(WindowDetectionOptions::Default),
    savingOptions(PersistWindowStateSavingOptions::Registry), registryPath(nullptr), initialTitle(nullptr),
    errorCode(ERROR_SUCCESS), errorHandler(nullptr), loadedHandler(nullptr), savedHandler(nullptr), errorContext(nullptr),
    loadedContext(nullptr), savedContext(nullptr) {
    identity[0] = 0;
    instanceProperty[0] = 0;
    InitializeRegistryPath();
}

/// Derives the default registry path from the host executable's declared company and product metadata.
void PersistWindowState::InitializeRegistryPath() {
    wchar_t module[MAX_PATH];
    DWORD length = GetModuleFileNameW(nullptr, module, ARRAYSIZE(module));
    if (!length || length >= ARRAYSIZE(module)) {
        return;
    }
    DWORD bytes = GetFileVersionInfoSizeW(module, nullptr);
    if (!bytes) {
        return;
    }
    void* information = HeapAlloc(GetProcessHeap(), 0, bytes);
    if (!information) {
        ReportError(ERROR_NOT_ENOUGH_MEMORY);
        return;
    }
    VersionResourceTranslation* translations = nullptr;
    UINT translationBytes = 0;
    if (GetFileVersionInfoW(module, 0, bytes, information) && VerQueryValueW(information, L"\\VarFileInfo\\Translation",
        reinterpret_cast<void**>(&translations), &translationBytes)) {
        for (UINT index = 0; index < translationBytes / sizeof(*translations); index++) {
            wchar_t query[64];
            wchar_t* company = nullptr;
            wchar_t* product = nullptr;
            UINT companyLength = 0;
            UINT productLength = 0;
            wsprintfW(query, L"\\StringFileInfo\\%04X%04X\\CompanyName",
                translations[index].language, translations[index].codePage);
            if (!VerQueryValueW(information, query, reinterpret_cast<void**>(&company), &companyLength)
                    || companyLength <= 1
                    || !company[0]) {
                continue;
            }
            wsprintfW(query, L"\\StringFileInfo\\%04X%04X\\ProductName",
                translations[index].language, translations[index].codePage);
            if (!VerQueryValueW(information, query, reinterpret_cast<void**>(&product), &productLength)
                    || productLength <= 1
                    || !product[0]) {
                continue;
            }
            SIZE_T characters = static_cast<SIZE_T>(companyLength) + productLength + ARRAYSIZE(L"Software\\") - 1;
            registryPath = static_cast<wchar_t*>(HeapAlloc(GetProcessHeap(), 0, characters * sizeof(wchar_t)));
            if (!registryPath) {
                ReportError(ERROR_NOT_ENOUGH_MEMORY);
                break;
            }
            lstrcpyW(registryPath, L"Software\\");
            lstrcatW(registryPath, company);
            lstrcatW(registryPath, L"\\");
            lstrcatW(registryPath, product);
            break;
        }
    }
    HeapFree(GetProcessHeap(), 0, information);
}

/// Captures the retained state and releases the attached subclass, mutex and owned registry path.
PersistWindowState::~PersistWindowState() {
    Detach();
    HeapFree(GetProcessHeap(), 0, registryPath);
    HeapFree(GetProcessHeap(), 0, initialTitle);
}

/// Allows persisting a minimized state and its normal or maximized restore state.
void PersistWindowState::SetAllowSaveMinimized(bool enabled) {
    allowSaveMinimized = enabled;
}

/// Returns the current AllowSaveMinimized setting.
bool PersistWindowState::GetAllowSaveMinimized() const {
    return allowSaveMinimized;
}

/// Allows restoring and persisting the native topmost state.
void PersistWindowState::SetAllowSaveTopMost(bool enabled) {
    allowSaveTopMost = enabled;
}

/// Returns the current AllowSaveTopMost setting.
bool PersistWindowState::GetAllowSaveTopMost() const {
    return allowSaveTopMost;
}

/// Disables restoration and persistence of the saved height.
void PersistWindowState::SetDisableSaveHeight(bool enabled) {
    disableSaveHeight = enabled;
}

/// Returns the current DisableSaveHeight setting.
bool PersistWindowState::GetDisableSaveHeight() const {
    return disableSaveHeight;
}

/// Disables restoration and persistence of the saved position.
void PersistWindowState::SetDisableSavePosition(bool enabled) {
    disableSavePosition = enabled;
}

/// Returns the current DisableSavePosition setting.
bool PersistWindowState::GetDisableSavePosition() const {
    return disableSavePosition;
}

/// Disables restoration and persistence of both saved dimensions.
void PersistWindowState::SetDisableSaveSize(bool enabled) {
    disableSaveSize = enabled;
}

/// Returns the current DisableSaveSize setting.
bool PersistWindowState::GetDisableSaveSize() const {
    return disableSaveSize;
}

/// Disables restoration and persistence of the saved width.
void PersistWindowState::SetDisableSaveWidth(bool enabled) {
    disableSaveWidth = enabled;
}

/// Returns the current DisableSaveWidth setting.
bool PersistWindowState::GetDisableSaveWidth() const {
    return disableSaveWidth;
}

/// Disables restoration and persistence of the saved show state.
void PersistWindowState::SetDisableSaveWindowState(bool enabled) {
    disableSaveWindowState = enabled;
}

/// Returns the current DisableSaveWindowState setting.
bool PersistWindowState::GetDisableSaveWindowState() const {
    return disableSaveWindowState;
}

/// Keeps the form's own height, ignoring saved heights and limiting interactive sizing.
void PersistWindowState::SetFixHeight(bool enabled) {
    fixHeight = enabled;
}

/// Returns the current FixHeight setting.
bool PersistWindowState::GetFixHeight() const {
    return fixHeight;
}

/// Keeps the form's own width, ignoring saved widths and limiting interactive sizing.
void PersistWindowState::SetFixWidth(bool enabled) {
    fixWidth = enabled;
}

/// Returns the current FixWidth setting.
bool PersistWindowState::GetFixWidth() const {
    return fixWidth;
}

/// Fits restored bounds to real monitor work areas when enabled.
void PersistWindowState::SetPlaceOnScreenAfterLoad(bool enabled) {
    placeOnScreenAfterLoad = enabled;
}

/// Returns the current PlaceOnScreenAfterLoad setting.
bool PersistWindowState::GetPlaceOnScreenAfterLoad() const {
    return placeOnScreenAfterLoad;
}

/// Reuses an existing registered form with the same identity when enabled.
void PersistWindowState::SetSingleInstance(bool enabled) {
    singleInstance = enabled;
}

/// Returns the current SingleInstance setting.
bool PersistWindowState::GetSingleInstance() const {
    return singleInstance;
}

/// Uses native Windows placement when no saved position can be applied.
void PersistWindowState::SetUseWindowsDefaultLocation(bool enabled) {
    useWindowsDefaultLocation = enabled;
}

/// Returns the current UseWindowsDefaultLocation setting.
bool PersistWindowState::GetUseWindowsDefaultLocation() const {
    return useWindowsDefaultLocation;
}

/// Uses native Windows sizing instead of the form's initial size when no dimensions were saved.
void PersistWindowState::SetUseWindowsDefaultSize(bool enabled) {
    useWindowsDefaultSize = enabled;
}

/// Returns the current UseWindowsDefaultSize setting.
bool PersistWindowState::GetUseWindowsDefaultSize() const {
    return useWindowsDefaultSize;
}

/// Selects detection by stable form identity, title pattern, or no detection.
void PersistWindowState::SetDetectionOptions(WindowDetectionOptions options) {
    detectionOptions = options;
}

/// Returns the configured form-instance detection mode.
WindowDetectionOptions PersistWindowState::GetDetectionOptions() const {
    return detectionOptions;
}

/// Selects registry saving or state retained only in this tracker.
void PersistWindowState::SetSavingOptions(PersistWindowStateSavingOptions options) {
    savingOptions = options;
}

/// Returns the configured persistence mode.
PersistWindowStateSavingOptions PersistWindowState::GetSavingOptions() const {
    return savingOptions;
}

/// Copies a caller-selected current-user registry path; an empty path selects memory-only persistence.
bool PersistWindowState::SetRegistryPath(const wchar_t* path) {
    if (!path) {
        path = L"";
    }
    SIZE_T bytes = (static_cast<SIZE_T>(lstrlenW(path)) + 1) * sizeof(wchar_t);
    wchar_t* copy = static_cast<wchar_t*>(HeapAlloc(GetProcessHeap(), 0, bytes));
    if (!copy) {
        ReportError(ERROR_NOT_ENOUGH_MEMORY);
        return false;
    }
    CopyMemory(copy, path, bytes);
    HeapFree(GetProcessHeap(), 0, registryPath);
    registryPath = copy;
    return true;
}

/// Returns the owned current-user registry path.
const wchar_t* PersistWindowState::GetRegistryPath() const {
    return registryPath ? registryPath : L"";
}

/// Installs the Error event handler and its caller-owned context.
void PersistWindowState::SetErrorHandler(PersistWindowStateEventHandler handler, void* context) {
    errorHandler = handler;
    errorContext = context;
}

/// Installs the Loaded event handler and its caller-owned context.
void PersistWindowState::SetLoadedHandler(PersistWindowStateEventHandler handler, void* context) {
    loadedHandler = handler;
    loadedContext = context;
}

/// Installs the Saved event handler and its caller-owned context.
void PersistWindowState::SetSavedHandler(PersistWindowStateEventHandler handler, void* context) {
    savedHandler = handler;
    savedContext = context;
}

/// Returns the most recent native failure or ERROR_SUCCESS.
DWORD PersistWindowState::GetErrorCode() const {
    return errorCode;
}

/// Reports a native error through the registered callback without throwing or displaying UI.
void PersistWindowState::ReportError(DWORD code, HKEY key) {
    errorCode = code;
    if (errorHandler) {
        errorHandler(this, PersistWindowStateEventArgs{ key, code }, errorContext);
    }
}

/// Constructs the per-form registry value name without depending on the translated window caption.
void PersistWindowState::ValueName(const wchar_t* suffix, wchar_t* name) const {
    MultiByteToWideChar(CP_ACP, 0, identity, -1, name, MAX_PATH);
    lstrcatW(name, suffix);
}

/// Reads one value identified by the form name and the requested suffix.
DWORD PersistWindowState::ReadValue(HKEY key, const wchar_t* suffix, DWORD type, void* data, DWORD bytes) {
    if (!data) {
        ReportError(ERROR_INVALID_PARAMETER, key);
        return ERROR_INVALID_PARAMETER;
    }
    wchar_t name[MAX_PATH + 32];
    ValueName(suffix, name);
    DWORD actualType = 0;
    DWORD actualBytes = bytes;
    DWORD result = RegQueryValueExW(key, name, nullptr, &actualType, static_cast<BYTE*>(data), &actualBytes);
    if (result == ERROR_FILE_NOT_FOUND) {
        return result;
    }
    if (result == ERROR_MORE_DATA || result == ERROR_SUCCESS && (actualType != type || actualBytes != bytes)) {
        result = ERROR_INVALID_DATA;
    }
    if (result != ERROR_SUCCESS) {
        ReportError(result, key);
    }
    return result;
}

/// Writes one value identified by the form name and reports native registry failures.
bool PersistWindowState::WriteValue(HKEY key, const wchar_t* suffix, DWORD type, const void* data, DWORD bytes) {
    wchar_t name[MAX_PATH + 32];
    ValueName(suffix, name);
    DWORD result = RegSetValueExW(key, name, 0, type, static_cast<const BYTE*>(data), bytes);
    if (result != ERROR_SUCCESS) {
        ReportError(result, key);
    }
    return result == ERROR_SUCCESS;
}

/// Returns whether the native form supports saving its show state.
bool PersistWindowState::CanSaveWindowState() const {
    LONG_PTR style = window ? GetWindowLongPtrW(window, GWL_STYLE) : 0;
    return !disableSaveWindowState && style & WS_SYSMENU && style & (WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
}

/// Returns whether the native form supports restoring or persisting its dimensions.
bool PersistWindowState::CanSaveSize() const {
    return window && !disableSaveSize && GetWindowLongPtrW(window, GWL_STYLE) & WS_THICKFRAME;
}

/// Reads enabled window-state values from the configured registry path.
void PersistWindowState::ReadRegistry() {
    if (savingOptions != PersistWindowStateSavingOptions::Registry || !registryPath || !registryPath[0]) {
        return;
    }
    HKEY key = nullptr;
    DWORD result = RegOpenKeyExW(HKEY_CURRENT_USER, registryPath, 0, KEY_QUERY_VALUE, &key);
    if (result == ERROR_FILE_NOT_FOUND) {
        return;
    }
    if (result != ERROR_SUCCESS) {
        ReportError(result);
        return;
    }
    POINT location = POINT{};
    if (!disableSavePosition && ReadValue(key, L"Location", REG_BINARY, &location, sizeof(location)) == ERROR_SUCCESS) {
        if (location.x >= -100000 && location.x <= 100000 && location.y >= -100000 && location.y <= 100000) {
            state.x = location.x;
            state.y = location.y;
        } else {
            ReportError(ERROR_INVALID_DATA, key);
        }
    }
    SIZE size = SIZE{};
    if (CanSaveSize() && ReadValue(key, L"Size", REG_BINARY, &size, sizeof(size)) == ERROR_SUCCESS) {
        if (size.cx >= 0 && size.cx <= 100000 && size.cy >= 0 && size.cy <= 100000) {
            if (!disableSaveWidth && !fixWidth && size.cx) {
                state.width = size.cx;
            }
            if (!disableSaveHeight && !fixHeight && size.cy) {
                state.height = size.cy;
            }
        } else {
            ReportError(ERROR_INVALID_DATA, key);
        }
    }
    DWORD show = 0;
    if ((CanSaveWindowState() || allowSaveTopMost)
            && ReadValue(key, L"State", REG_DWORD, &show, sizeof(show)) == ERROR_SUCCESS) {
        DWORD restore = LOWORD(show) == 2 ? 2 : 0;
        ReadValue(key, L"RestoreState", REG_DWORD, &restore, sizeof(restore));
        if (CanSaveWindowState()) {
            state.minimized = LOWORD(show) == 1 && allowSaveMinimized;
            state.maximized = LOWORD(show) == 2 || LOWORD(show) == 1 && !allowSaveMinimized && restore == 2;
            state.restoreMaximized = restore == 2;
            restoredShowState = true;
        }
        if (allowSaveTopMost) {
            state.topMost = HIWORD(show) != 0;
        }
    }
    RegCloseKey(key);
}

/// Writes enabled values while preserving registry fields that the caller disabled.
void PersistWindowState::WriteRegistry() {
    HKEY key = nullptr;
    DWORD disposition = 0;
    DWORD result = RegCreateKeyExW(HKEY_CURRENT_USER, registryPath, 0, nullptr, 0, KEY_QUERY_VALUE | KEY_SET_VALUE,
        nullptr, &key, &disposition);
    if (result != ERROR_SUCCESS) {
        ReportError(result);
        return;
    }
    bool success = true;
    if (!disableSavePosition) {
        POINT location = POINT{ state.x, state.y };
        success = WriteValue(key, L"Location", REG_BINARY, &location, sizeof(location)) && success;
    }
    if (CanSaveSize() && (!disableSaveWidth || !disableSaveHeight)) {
        SIZE size = SIZE{};
        DWORD readResult = ERROR_SUCCESS;
        if (disableSaveWidth || disableSaveHeight) {
            readResult = ReadValue(key, L"Size", REG_BINARY, &size, sizeof(size));
        }
        if (readResult == ERROR_SUCCESS || readResult == ERROR_FILE_NOT_FOUND) {
            if (!disableSaveWidth) {
                size.cx = state.width;
            }
            if (!disableSaveHeight) {
                size.cy = state.height;
            }
            success = WriteValue(key, L"Size", REG_BINARY, &size, sizeof(size)) && success;
        } else {
            success = false;
        }
    }
    if (CanSaveWindowState() || allowSaveTopMost) {
        DWORD previous = 0;
        DWORD readResult = ERROR_SUCCESS;
        if (!CanSaveWindowState() || !allowSaveTopMost) {
            readResult = ReadValue(key, L"State", REG_DWORD, &previous, sizeof(previous));
        }
        if (readResult == ERROR_SUCCESS || readResult == ERROR_FILE_NOT_FOUND) {
            DWORD show = state.minimized && allowSaveMinimized ? 1 : state.maximized
                || state.minimized && state.restoreMaximized ? 2 : 0;
            DWORD value = CanSaveWindowState() ? show : LOWORD(previous);
            value |= allowSaveTopMost ? state.topMost ? 0x10000 : 0 : previous & 0xFFFF0000;
            success = WriteValue(key, L"State", REG_DWORD, &value, sizeof(value)) && success;
            if (CanSaveWindowState()) {
                DWORD restore = state.restoreMaximized ? 2 : 0;
                success = WriteValue(key, L"RestoreState", REG_DWORD, &restore, sizeof(restore)) && success;
            }
        } else {
            success = false;
        }
    }
    if (success && savedHandler) {
        savedHandler(this, PersistWindowStateEventArgs{ key, ERROR_SUCCESS }, savedContext);
    }
    RegCloseKey(key);
}

/// Serializes form registration using a stable application and form identity.
bool PersistWindowState::RegisterForm(HWND target, bool* alreadyRunning) {
    wchar_t module[MAX_PATH];
    DWORD length = GetModuleFileNameW(nullptr, module, ARRAYSIZE(module));
    if (!length || length >= ARRAYSIZE(module)) {
        ReportError(ERROR_BUFFER_OVERFLOW);
        return false;
    }
    CharLowerBuffW(module, length);
    DWORD first = 2166136261;
    DWORD second = 5381;
    const wchar_t* executableName = module;
    for (const wchar_t* character = module; *character; ++character) {
        if (*character == L'\\' || *character == L'/') {
            executableName = character + 1;
        }
    }
    HashIdentity(executableName, &first, &second);
    wchar_t wideIdentity[MAX_PATH];
    MultiByteToWideChar(CP_ACP, 0, identity, -1, wideIdentity, ARRAYSIZE(wideIdentity));
    HashIdentity(wideIdentity, &first, &second, true);
    wsprintfA(instanceProperty, "FortSoft.PersistWindowState.%08lX%08lX", first, second);
    instanceMutex = CreateMutexA(nullptr, FALSE, instanceProperty);
    if (!instanceMutex) {
        ReportError(GetLastError());
        return false;
    }
    DWORD lock = WaitForSingleObject(instanceMutex, INFINITE);
    if (lock != WAIT_OBJECT_0 && lock != WAIT_ABANDONED) {
        DWORD failure = GetLastError();
        CloseHandle(instanceMutex);
        instanceMutex = nullptr;
        ReportError(failure);
        return false;
    }
    registrationLocked = true;
    *alreadyRunning = false;
    if (singleInstance || detectionOptions != WindowDetectionOptions::NoDetection) {
        ExistingFormSearch search = ExistingFormSearch{
            target,
            nullptr,
            instanceProperty,
            initialTitle,
            singleInstance ? WindowDetectionOptions::Default : detectionOptions, ERROR_SUCCESS
        };
        BOOL enumerated = EnumWindows(FindExistingForm, reinterpret_cast<LPARAM>(&search));
        if (!enumerated && !search.existing && !search.error) {
            search.error = GetLastError();
            if (!search.error) {
                search.error = ERROR_GEN_FAILURE;
            }
        }
        if (search.error) {
            ReleaseRegistrationLock();
            CloseHandle(instanceMutex);
            instanceMutex = nullptr;
            ReportError(search.error);
            return false;
        }
        *alreadyRunning = search.existing != nullptr;
        if (singleInstance && search.existing) {
            ReleaseRegistrationLock();
            CloseHandle(instanceMutex);
            instanceMutex = nullptr;
            BringWindowToFront(search.existing);
            SendMessageW(target, WM_CLOSE, 0, 0);
            return false;
        }
    }
    return true;
}

/// Releases the registration lock before callbacks or attachment cleanup can close its handle.
void PersistWindowState::ReleaseRegistrationLock() {
    if (registrationLocked) {
        ReleaseMutex(instanceMutex);
        registrationLocked = false;
    }
}

/// Releases the registered identity, subclass and mutex without destroying the form.
void PersistWindowState::UnregisterForm() {
    if (window && IsWindow(window)) {
        RemoveWindowSubclass(window, WindowSubclassProc, reinterpret_cast<UINT_PTR>(this));
        RemovePropW(window, placementProperty);
        RemovePropA(window, instanceProperty);
    }
    window = nullptr;
    attached = false;
    ReleaseRegistrationLock();
    if (instanceMutex) {
        CloseHandle(instanceMutex);
        instanceMutex = nullptr;
    }
}

/// Reads Windows-selected bounds without displaying or activating the temporary native window.
bool PersistWindowState::ReadWindowsDefaultBounds(int width, int height, RECT* bounds) {
    HWND positionWindow = CreateWindowExW(WS_EX_NOACTIVATE, L"STATIC", L"", WS_OVERLAPPED, CW_USEDEFAULT, CW_USEDEFAULT,
        width, height, nullptr, nullptr, GetModuleHandleW(nullptr), nullptr);
    if (!positionWindow) {
        return false;
    }
    bool success = GetWindowRect(positionWindow, bounds) != FALSE;
    DestroyWindow(positionWindow);
    return success;
}

/// Attaches or replaces the parent form, capturing and detaching the previous parent first.
bool PersistWindowState::SetParent(HWND target, const char* formIdentity) {
    if (target == window) {
        return true;
    }
    Detach();
    return !target || Attach(target, formIdentity);
}

/// Returns the parent window handle or null when detached.
HWND PersistWindowState::GetParent() const {
    return window;
}

/// Attaches a form, restores enabled settings, or reuses its existing single instance.
bool PersistWindowState::Attach(HWND target, const char* formIdentity) {
    errorCode = ERROR_SUCCESS;
    if (!target || window || !formIdentity || !formIdentity[0] || lstrlenA(formIdentity) >= MAX_PATH) {
        ReportError(ERROR_INVALID_PARAMETER);
        return false;
    }
    if (GetPropW(target, placementProperty)) {
        ReportError(ERROR_ALREADY_EXISTS);
        return false;
    }
    RECT rect = RECT{};
    if (!ReadNormalWindowBounds(target, &rect)) {
        ReportError(GetLastError());
        return false;
    }
    lstrcpyA(identity, formIdentity);
    wchar_t* title = CopyWindowCaption(target);
    if (!title) {
        ReportError(GetLastError());
        return false;
    }
    HeapFree(GetProcessHeap(), 0, initialTitle);
    initialTitle = title;
    bool alreadyRunning = false;
    if (!RegisterForm(target, &alreadyRunning)) {
        return false;
    }
    window = target;
    LONG_PTR style = GetWindowLongPtrW(window, GWL_STYLE);
    bool visible = IsWindowVisible(window) != FALSE;
    bool initialMaximized = IsZoomed(window) != FALSE;
    bool initialMinimized = IsIconic(window) != FALSE;
    bool initialTopMost = GetWindowLongPtrW(window, GWL_EXSTYLE) & WS_EX_TOPMOST;
    restoredShowState = hasState;
    if (!hasState) {
        state.maximized = initialMaximized;
        state.minimized = initialMinimized;
        state.topMost = initialTopMost;
    }
    ReadRegistry();
    if (window != target) {
        return false;
    }
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    bool resizeWidth = CanSaveSize() && !disableSaveWidth && !fixWidth;
    bool resizeHeight = CanSaveSize() && !disableSaveHeight && !fixHeight;
    if (resizeWidth && state.width > 0) {
        width = state.width;
    }
    if (resizeHeight && state.height > 0) {
        height = state.height;
    }
    bool restoreX = !disableSavePosition && !alreadyRunning && state.x != CW_USEDEFAULT;
    bool restoreY = !disableSavePosition && !alreadyRunning && state.y != CW_USEDEFAULT;
    bool defaultPosition = useWindowsDefaultLocation && (!restoreX || !restoreY);
    bool defaultWidth = useWindowsDefaultSize
        && style & WS_THICKFRAME
        && !fixWidth
        && (!resizeWidth || state.width <= 0);
    bool defaultHeight = useWindowsDefaultSize
        && style & WS_THICKFRAME
        && !fixHeight
        && (!resizeHeight || state.height <= 0);
    bool defaultSize = defaultWidth || defaultHeight;
    if (defaultPosition || defaultSize) {
        RECT defaults = RECT{};
        int requestedWidth = defaultSize ? CW_USEDEFAULT : width;
        int requestedHeight = defaultSize ? CW_USEDEFAULT : height;
        if (!ReadWindowsDefaultBounds(requestedWidth, requestedHeight, &defaults)) {
            DWORD failure = GetLastError();
            ReleaseRegistrationLock();
            UnregisterForm();
            ReportError(failure);
            return false;
        }
        if (defaultPosition) {
            rect.left = defaults.left;
            rect.top = defaults.top;
        }
        if (defaultWidth) {
            width = defaults.right - defaults.left;
        }
        if (defaultHeight) {
            height = defaults.bottom - defaults.top;
        }
    }
    MINMAXINFO limits = TrackingLimits(window);
    if (style & WS_THICKFRAME && !fixWidth) {
        width = ConstrainDimension(width, limits.ptMinTrackSize.x, limits.ptMaxTrackSize.x);
    }
    if (style & WS_THICKFRAME && !fixHeight) {
        height = ConstrainDimension(height, limits.ptMinTrackSize.y, limits.ptMaxTrackSize.y);
    }
    int x = restoreX ? state.x : rect.left;
    int y = restoreY ? state.y : rect.top;
    RECT placed = RECT{ x, y, x + width, y + height };
    if (placeOnScreenAfterLoad) {
        MonitorWorkArea* areas = nullptr;
        UINT count = 0;
        DWORD result = ReadMonitorWorkAreas(&areas, &count);
        if (result == ERROR_SUCCESS) {
            FitWindowToWorkAreas(&placed, areas, count, style & WS_THICKFRAME && !fixWidth,
                style & WS_THICKFRAME && !fixHeight, SIZE{ limits.ptMinTrackSize.x, limits.ptMinTrackSize.y });
            HeapFree(GetProcessHeap(), 0, areas);
        } else {
            ReportError(result);
            if (window != target) {
                return false;
            }
        }
    }
    applying = true;
    UINT flags = SWP_NOACTIVATE;
    HWND after = nullptr;
    if (allowSaveTopMost) {
        after = state.topMost ? HWND_TOPMOST : HWND_NOTOPMOST;
    } else {
        flags |= SWP_NOZORDER;
    }
    bool positioned = false;
    if (initialMaximized || initialMinimized) {
        WINDOWPLACEMENT native = WINDOWPLACEMENT{};
        native.length = sizeof(native);
        if (GetWindowPlacement(window, &native)) {
            native.rcNormalPosition = ConvertWorkspaceBounds(window, placed, false);
            native.showCmd = !visible ? SW_HIDE : initialMinimized ? SW_SHOWMINNOACTIVE : SW_SHOWMAXIMIZED;
            positioned = SetWindowPlacement(window, &native) != FALSE;
            if (positioned && allowSaveTopMost) {
                positioned = SetWindowPos(window, after, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE) != FALSE;
            }
        }
    } else {
        positioned = SetWindowPos(window, after, placed.left, placed.top,
            placed.right - placed.left, placed.bottom - placed.top, flags) != FALSE;
    }
    bool registered = positioned
        && SetPropW(window, placementProperty, this)
        && SetPropA(window, instanceProperty, window);
    if (registered) {
        SetLastError(ERROR_SUCCESS);
        attached = SetWindowSubclass(window, WindowSubclassProc, reinterpret_cast<UINT_PTR>(this),
            reinterpret_cast<DWORD_PTR>(this)) != FALSE;
        registered = attached;
    }
    applying = false;
    if (!registered) {
        DWORD failure = GetLastError();
        ReleaseRegistrationLock();
        UnregisterForm();
        ReportError(failure ? failure : ERROR_GEN_FAILURE);
        return false;
    }
    state.x = placed.left;
    state.y = placed.top;
    state.width = placed.right - placed.left;
    state.height = placed.bottom - placed.top;
    if (alreadyRunning || !CanSaveWindowState() || !restoredShowState) {
        state.maximized = initialMaximized;
        state.minimized = initialMinimized;
    } else {
        if (state.minimized && (!allowSaveMinimized || !(style & WS_MINIMIZEBOX))) {
            state.minimized = false;
            state.maximized = state.restoreMaximized;
        }
        state.maximized = state.maximized && style & WS_MAXIMIZEBOX;
    }
    hasState = true;
    ReleaseRegistrationLock();
    if (visible) {
        Show();
    }
    if (loadedHandler) {
        HKEY key = nullptr;
        if (savingOptions == PersistWindowStateSavingOptions::Registry && registryPath && registryPath[0]) {
            RegOpenKeyExW(HKEY_CURRENT_USER, registryPath, 0, KEY_QUERY_VALUE, &key);
        }
        loadedHandler(this, PersistWindowStateEventArgs{ key, ERROR_SUCCESS }, loadedContext);
        if (key) {
            RegCloseKey(key);
        }
    }
    return GetPropW(target, placementProperty) == this;
}

/// Captures and detaches the current parent while retaining memory-only state.
void PersistWindowState::Detach() {
    Capture();
    UnregisterForm();
}

/// Returns whether the tracker owns an attached window.
bool PersistWindowState::IsAttached() const {
    return window && attached;
}

/// Supplies retained state before attaching; registry values still take precedence when enabled.
void PersistWindowState::Load(const PersistWindowStateData& saved) {
    state = saved;
    if (state.x < -100000 || state.x > 100000) {
        state.x = CW_USEDEFAULT;
    }
    if (state.y < -100000 || state.y > 100000) {
        state.y = CW_USEDEFAULT;
    }
    if (state.width < 0 || state.width > 100000) {
        state.width = 0;
    }
    if (state.height < 0 || state.height > 100000) {
        state.height = 0;
    }
    hasState = true;
    restoredShowState = true;
}

/// Returns retained state without performing a registry write.
const PersistWindowStateData& PersistWindowState::GetState() const {
    return state;
}

/// Captures state and saves enabled fields according to the selected persistence mode.
const PersistWindowStateData& PersistWindowState::Save() {
    if (!window || !attached) {
        return state;
    }
    errorCode = ERROR_SUCCESS;
    Capture();
    if (savingOptions == PersistWindowStateSavingOptions::Registry && registryPath && registryPath[0]) {
        WriteRegistry();
    } else if (savedHandler) {
        savedHandler(this, PersistWindowStateEventArgs{ nullptr, ERROR_SUCCESS }, savedContext);
    }
    return state;
}

/// Displays the form in its configured normal, minimized or maximized state.
void PersistWindowState::Show() {
    if (!window) {
        return;
    }
    applying = true;
    if (state.minimized) {
        WINDOWPLACEMENT placement = WINDOWPLACEMENT{};
        placement.length = sizeof(placement);
        if (GetWindowPlacement(window, &placement)) {
            placement.flags = state.restoreMaximized ? WPF_RESTORETOMAXIMIZED : 0;
            placement.showCmd = SW_SHOWMINNOACTIVE;
            if (!SetWindowPlacement(window, &placement)) {
                ReportError(GetLastError());
            }
        }
    } else {
        ShowWindow(window, state.maximized ? SW_SHOWMAXIMIZED : SW_SHOWNORMAL);
        SetForegroundWindow(window);
    }
    applying = false;
}

/// Restores a minimized parent without explicitly activating it.
void PersistWindowState::Restore() const {
    if (window && IsIconic(window)) {
        ShowWindow(window, SW_RESTORE);
    }
}

/// Restores and brings the parent to the user.
void PersistWindowState::BringToFront() const {
    if (window) {
        BringWindowToFront(window);
    }
}

/// Restores and activates another registered instance of the form.
void PersistWindowState::BringWindowToFront(HWND target) {
    if (IsIconic(target)) {
        ShowWindow(target, SW_RESTORE);
    } else if (!IsWindowVisible(target)) {
        ShowWindow(target, SW_SHOW);
    }
    SetForegroundWindow(target);
}

/// Checks the visible Z-order relation while omitting the caller's excluded windows.
bool PersistWindowState::IsNextWindow(HWND target, const HWND* skip, UINT count) const {
    bool found = false;
    for (HWND current = GetTopWindow(nullptr); current; current = GetWindow(current, GW_HWNDNEXT)) {
        bool excluded = false;
        for (UINT index = 0; index < count; ++index) {
            if (skip[index] == current) {
                excluded = true;
                break;
            }
        }
        if (!excluded && IsWindowVisible(current)) {
            if (found) {
                return current == window;
            }
            found = current == target;
        }
    }
    return false;
}

/// Reveals the parent beneath a caller-selected window, omitting excluded windows during Z-order checks.
void PersistWindowState::SetVisible(HWND target, const HWND* skip, UINT count) {
    if (!window) {
        return;
    }
    if (IsIconic(window)) {
        Restore();
        SetForegroundWindow(target);
    } else if (!IsNextWindow(target, skip, count)) {
        BringWindowToFront(window);
        SetForegroundWindow(target);
    }
}

/// Records normal screen bounds, show state and topmost state without taking minimized bounds.
void PersistWindowState::Capture() {
    if (!window || applying || !IsWindowVisible(window)) {
        return;
    }
    bool minimized = IsIconic(window) != FALSE;
    bool maximized = IsZoomed(window) != FALSE;
    RECT bounds = RECT{};
    if (ReadNormalWindowBounds(window, &bounds)) {
        state.x = bounds.left;
        state.y = bounds.top;
        state.width = bounds.right - bounds.left;
        state.height = bounds.bottom - bounds.top;
    }
    if (!minimized) {
        state.restoreMaximized = maximized;
        state.maximized = maximized;
    } else {
        WINDOWPLACEMENT placement = WINDOWPLACEMENT{};
        placement.length = sizeof(placement);
        if (GetWindowPlacement(window, &placement) && placement.flags & WPF_RESTORETOMAXIMIZED) {
            state.restoreMaximized = true;
        }
    }
    state.minimized = minimized;
    state.topMost = GetWindowLongPtrW(window, GWL_EXSTYLE) & WS_EX_TOPMOST;
}

/// Fits normal bounds to actual monitor work areas after a display or system-setting change.
bool PersistWindowState::FitToWorkArea() {
    if (!window || !placeOnScreenAfterLoad || IsIconic(window) || IsZoomed(window)) {
        return false;
    }
    RECT bounds = RECT{};
    if (!GetWindowRect(window, &bounds)) {
        ReportError(GetLastError());
        return false;
    }
    MonitorWorkArea* areas = nullptr;
    UINT count = 0;
    DWORD result = ReadMonitorWorkAreas(&areas, &count);
    if (result != ERROR_SUCCESS) {
        ReportError(result);
        return false;
    }
    LONG_PTR style = GetWindowLongPtrW(window, GWL_STYLE);
    MINMAXINFO limits = TrackingLimits(window);
    bool changed = FitWindowToWorkAreas(&bounds, areas, count, style & WS_THICKFRAME && !fixWidth,
        style & WS_THICKFRAME && !fixHeight, SIZE{ limits.ptMinTrackSize.x, limits.ptMinTrackSize.y });
    HeapFree(GetProcessHeap(), 0, areas);
    return changed && SetWindowPos(window, nullptr, bounds.left, bounds.top, bounds.right - bounds.left,
        bounds.bottom - bounds.top, SWP_NOZORDER | SWP_NOACTIVATE);
}

/// Handles native lifecycle, placement, fixed dimensions and automatic saving.
LRESULT CALLBACK PersistWindowState::WindowSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR, DWORD_PTR referenceData) {
    PersistWindowState* owner = reinterpret_cast<PersistWindowState*>(referenceData);
    if (message == WM_DESTROY || message == WM_QUERYENDSESSION) {
        owner->Save();
        if (GetPropW(window, placementProperty) != owner) {
            return DefSubclassProc(window, message, wParam, lParam);
        }
    }
    if (message == WM_NCDESTROY) {
        owner->UnregisterForm();
        return DefSubclassProc(window, message, wParam, lParam);
    }
    LRESULT result = DefSubclassProc(window, message, wParam, lParam);
    if (GetPropW(window, placementProperty) != owner) {
        return result;
    }
    if (message == WM_GETMINMAXINFO && (owner->fixWidth || owner->fixHeight)) {
        MINMAXINFO* info = reinterpret_cast<MINMAXINFO*>(lParam);
        if (owner->fixWidth) {
            info->ptMinTrackSize.x = owner->state.width;
            info->ptMaxTrackSize.x = owner->state.width;
            info->ptMaxSize.x = owner->state.width;
        }
        if (owner->fixHeight) {
            info->ptMinTrackSize.y = owner->state.height;
            info->ptMaxTrackSize.y = owner->state.height;
            info->ptMaxSize.y = owner->state.height;
        }
    } else if (message == WM_WINDOWPOSCHANGED) {
        owner->Capture();
    } else if (message == WM_SETTINGCHANGE || message == WM_DISPLAYCHANGE) {
        owner->FitToWorkArea();
    }
    return result;
}
