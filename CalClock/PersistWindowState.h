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

#pragma once

#include <windows.h>

/// Matching rules used to locate an existing instance of the attached form.
enum class WindowDetectionOptions {
    Default,
    TitleContains,
    TitleStartsWith,
    TitleEndsWith,
    TitleEquals,
    NoDetection
};

/// Storage options for persisting a form's window state.
enum class PersistWindowStateSavingOptions {
    None,
    Registry
};

/// Persisted normal bounds, show state and topmost status of a native window.
struct PersistWindowStateData {
    int x = CW_USEDEFAULT;
    int y = CW_USEDEFAULT;
    int width = 0;
    int height = 0;
    bool maximized = false;
    bool minimized = false;
    bool topMost = false;
    bool restoreMaximized = false;
};

/// Registry handle and native error code supplied to persistence event callbacks.
struct PersistWindowStateEventArgs {
    HKEY registryKey;
    DWORD errorCode;
};

/// Restores and persists native window bounds, show state and instance registration.
class PersistWindowState;
typedef void (*PersistWindowStateEventHandler)(PersistWindowState*, const PersistWindowStateEventArgs&, void*);

/// Restores and persists native window bounds, show state and instance registration.
class PersistWindowState {

private:
    HWND window;
    HANDLE instanceMutex;
    bool attached;
    bool registrationLocked;
    bool allowSaveMinimized;
    bool allowSaveTopMost;
    bool disableSaveHeight;
    bool disableSavePosition;
    bool disableSaveSize;
    bool disableSaveWidth;
    bool disableSaveWindowState;
    bool fixHeight;
    bool fixWidth;
    bool placeOnScreenAfterLoad;
    bool singleInstance;
    bool useWindowsDefaultLocation;
    bool useWindowsDefaultSize;
    bool hasState;
    bool applying;
    bool restoredShowState;
    WindowDetectionOptions detectionOptions;
    PersistWindowStateSavingOptions savingOptions;
    wchar_t* registryPath;
    char identity[MAX_PATH];
    char instanceProperty[64];
    wchar_t* initialTitle;
    PersistWindowStateData state;
    DWORD errorCode;
    PersistWindowStateEventHandler errorHandler;
    PersistWindowStateEventHandler loadedHandler;
    PersistWindowStateEventHandler savedHandler;
    void* errorContext;
    void* loadedContext;
    void* savedContext;

    /// Reports a native error through the registered callback without throwing or displaying UI.
    void ReportError(DWORD code, HKEY key = nullptr);

    /// Derives the default registry path from the host executable's declared company and product metadata.
    void InitializeRegistryPath();

    /// Reads enabled window-state values from the configured registry path.
    void ReadRegistry();

    /// Writes enabled values while preserving registry fields that the caller disabled.
    void WriteRegistry();

    /// Reads one value identified by the form name and the requested suffix.
    DWORD ReadValue(HKEY key, const wchar_t* suffix, DWORD type, void* data, DWORD bytes);

    /// Writes one value identified by the form name and reports native registry failures.
    bool WriteValue(HKEY key, const wchar_t* suffix, DWORD type, const void* data, DWORD bytes);

    /// Constructs the per-form registry value name without depending on the translated window caption.
    void ValueName(const wchar_t* suffix, wchar_t* name) const;

    /// Returns whether the native form supports saving its show state.
    bool CanSaveWindowState() const;

    /// Returns whether the native form supports restoring or persisting its dimensions.
    bool CanSaveSize() const;

    /// Serializes form registration using a stable application and form identity.
    bool RegisterForm(HWND target, bool* alreadyRunning);

    /// Releases the registration lock before callbacks or attachment cleanup can close its handle.
    void ReleaseRegistrationLock();

    /// Releases the registered identity, subclass and mutex without destroying the form.
    void UnregisterForm();

    /// Records normal screen bounds, show state and topmost state without taking minimized bounds.
    void Capture();

    /// Fits normal bounds to actual monitor work areas after a display or system-setting change.
    bool FitToWorkArea();

    /// Checks the visible Z-order relation while omitting the caller's excluded windows.
    bool IsNextWindow(HWND target, const HWND* skip, UINT count) const;

    /// Restores and activates another registered instance of the form.
    static void BringWindowToFront(HWND target);

    /// Reads Windows-selected bounds without displaying or activating the temporary native window.
    static bool ReadWindowsDefaultBounds(int width, int height, RECT* bounds);

    /// Handles native lifecycle, placement, fixed dimensions and automatic saving.
    static LRESULT CALLBACK WindowSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR subclassId, DWORD_PTR referenceData);

public:
    /// Creates a native state tracker with registry saving and Windows-selected initial bounds.
    PersistWindowState();

    /// Captures the retained state and releases the attached subclass, mutex and owned registry path.
    ~PersistWindowState();

    /// Prevents copying ownership of a registered native form.
    PersistWindowState(const PersistWindowState&) = delete;

    /// Prevents assigning ownership of a registered native form.
    PersistWindowState& operator=(const PersistWindowState&) = delete;

    /// Allows persisting a minimized state and its normal or maximized restore state.
    void SetAllowSaveMinimized(bool enabled);

    /// Returns the current AllowSaveMinimized setting.
    bool GetAllowSaveMinimized() const;

    /// Allows restoring and persisting the native topmost state.
    void SetAllowSaveTopMost(bool enabled);

    /// Returns the current AllowSaveTopMost setting.
    bool GetAllowSaveTopMost() const;

    /// Disables restoration and persistence of the saved height.
    void SetDisableSaveHeight(bool enabled);

    /// Returns the current DisableSaveHeight setting.
    bool GetDisableSaveHeight() const;

    /// Disables restoration and persistence of the saved position.
    void SetDisableSavePosition(bool enabled);

    /// Returns the current DisableSavePosition setting.
    bool GetDisableSavePosition() const;

    /// Disables restoration and persistence of both saved dimensions.
    void SetDisableSaveSize(bool enabled);

    /// Returns the current DisableSaveSize setting.
    bool GetDisableSaveSize() const;

    /// Disables restoration and persistence of the saved width.
    void SetDisableSaveWidth(bool enabled);

    /// Returns the current DisableSaveWidth setting.
    bool GetDisableSaveWidth() const;

    /// Disables restoration and persistence of the saved show state.
    void SetDisableSaveWindowState(bool enabled);

    /// Returns the current DisableSaveWindowState setting.
    bool GetDisableSaveWindowState() const;

    /// Keeps the form's own height, ignoring saved heights and limiting interactive sizing.
    void SetFixHeight(bool enabled);

    /// Returns the current FixHeight setting.
    bool GetFixHeight() const;

    /// Keeps the form's own width, ignoring saved widths and limiting interactive sizing.
    void SetFixWidth(bool enabled);

    /// Returns the current FixWidth setting.
    bool GetFixWidth() const;

    /// Fits restored bounds to real monitor work areas when enabled.
    void SetPlaceOnScreenAfterLoad(bool enabled);

    /// Returns the current PlaceOnScreenAfterLoad setting.
    bool GetPlaceOnScreenAfterLoad() const;

    /// Reuses an existing registered form with the same identity when enabled.
    void SetSingleInstance(bool enabled);

    /// Returns the current SingleInstance setting.
    bool GetSingleInstance() const;

    /// Uses native Windows placement when no saved position can be applied.
    void SetUseWindowsDefaultLocation(bool enabled);

    /// Returns the current UseWindowsDefaultLocation setting.
    bool GetUseWindowsDefaultLocation() const;

    /// Uses native Windows sizing instead of the form's initial size when no dimensions were saved.
    void SetUseWindowsDefaultSize(bool enabled);

    /// Returns the current UseWindowsDefaultSize setting.
    bool GetUseWindowsDefaultSize() const;

    /// Selects detection by stable form identity, title pattern, or no detection.
    void SetDetectionOptions(WindowDetectionOptions options);

    /// Returns the configured form-instance detection mode.
    WindowDetectionOptions GetDetectionOptions() const;

    /// Selects registry saving or state retained only in this tracker.
    void SetSavingOptions(PersistWindowStateSavingOptions options);

    /// Returns the configured persistence mode.
    PersistWindowStateSavingOptions GetSavingOptions() const;

    /// Copies a caller-selected current-user registry path; an empty path selects memory-only persistence.
    bool SetRegistryPath(const wchar_t* path);

    /// Returns the owned current-user registry path.
    const wchar_t* GetRegistryPath() const;

    /// Installs the Error event handler and its caller-owned context.
    void SetErrorHandler(PersistWindowStateEventHandler handler, void* context = nullptr);

    /// Installs the Loaded event handler and its caller-owned context.
    void SetLoadedHandler(PersistWindowStateEventHandler handler, void* context = nullptr);

    /// Installs the Saved event handler and its caller-owned context.
    void SetSavedHandler(PersistWindowStateEventHandler handler, void* context = nullptr);

    /// Returns the most recent native failure or ERROR_SUCCESS.
    DWORD GetErrorCode() const;

    /// Attaches or replaces the parent form, capturing and detaching the previous parent first.
    bool SetParent(HWND target, const char* formIdentity);

    /// Returns the parent window handle or null when detached.
    HWND GetParent() const;

    /// Attaches a form, restores enabled settings, or reuses its existing single instance.
    bool Attach(HWND target, const char* formIdentity = "Window");

    /// Captures and detaches the current parent while retaining memory-only state.
    void Detach();

    /// Returns whether the tracker owns an attached window.
    bool IsAttached() const;

    /// Supplies retained state before attaching; registry values still take precedence when enabled.
    void Load(const PersistWindowStateData& saved);

    /// Returns retained state without performing a registry write.
    const PersistWindowStateData& GetState() const;

    /// Captures state and saves enabled fields according to the selected persistence mode.
    const PersistWindowStateData& Save();

    /// Displays the form in its configured normal, minimized or maximized state.
    void Show();

    /// Restores a minimized parent without explicitly activating it.
    void Restore() const;

    /// Restores and brings the parent to the user.
    void BringToFront() const;

    /// Reveals the parent beneath a caller-selected window, omitting excluded windows during Z-order checks.
    void SetVisible(HWND target, const HWND* skip = nullptr, UINT count = 0);
};
