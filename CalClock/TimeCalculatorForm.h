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

#include "CalClock.h"
#include "PersistWindowState.h"
#include "TimeCalculator.h"
#include <commctrl.h>
#include <atomic>
#include <memory>
#include <vector>

/// Owns the modeless interval, milestone-calendar and preset editor, including its persistent input values.
class TimeCalculatorForm {
public:
    /// Returns the calculator's native window while it is open.
    HWND GetWindow() const;
    /// Returns window settings for the selected application settings backend.
    const TimeCalculatorState& GetState() const;
    /// Returns the independent user-data collection for an explicit manual export.
    const std::vector<TimeCalculatorPreset>& GetPresets() const;
    /// Loads times.xml once, reporting failure without replacing unread data with an empty collection.
    bool EnsurePresetsLoaded();
    /// Adds only records that differ in date, time or exact description, retaining existing records.
    bool MergePresets(const std::vector<TimeCalculatorPreset>& imported);
    /// Applies a stored or imported calculator state without replacing an open form.
    void Load(const TimeCalculatorState& saved);
    /// Opens or activates the form with the application's font, style and position persistence.
    void Show(HINSTANCE module, PersistWindowState& placement);
    /// Destroys the native form while retaining its calculator state.
    void Close() const;
    /// Updates localized captions, formats, presets and calculated results.
    void Refresh();
    /// Applies the effective application font and theme to the existing form.
    bool ApplyStyle(bool updateFont = true);
    /// Handles calculator-specific keys and native modeless dialog navigation.
    bool ProcessMessage(MSG* message);

private:
    struct ControlPlacement {
        HWND parent = nullptr;
        int id = 0;
        RECT units = {};
    };

    struct Calculation {
        HWND window = nullptr;
        ULONG_PTR generation = 0;
        TimeCalculatorState state;
        DYNAMIC_TIME_ZONE_INFORMATION fromZone = {};
        DYNAMIC_TIME_ZONE_INFORMATION startZone = {};
        SYSTEMTIME now = {};
        SYSTEMTIME firstMonth = {};
        SYSTEMTIME hourTime = {};
        int monthCount = 0;
        bool validInterval = false;
        bool validDay = false;
        bool validStart = false;
        bool highlights = false;
        bool labels = false;
        TimeCalculatorInterval interval;
        TimeCalculatorDay day;
        std::vector<MONTHDAYSTATE> dayStates;
        std::vector<DYNAMIC_TIME_ZONE_INFORMATION> zones;
        std::vector<std::wstring> zoneLabels;
        std::wstring systemLabel;
        std::atomic<bool> cancelled = false;
        std::atomic<bool> finished = false;
    };

    HWND window = nullptr;
    HWND pages[TIME_CALCULATOR_PAGE_COUNT] = {};
    HWND descriptionEdit = nullptr;
    HINSTANCE instance = nullptr;
    HFONT uiFont = nullptr;
    PersistWindowState* placement = nullptr;
    TimeCalculatorState state;
    ApplicationComboState comboState;
    std::vector<TimeCalculatorPreset> presets;
    SYSTEMTIME entryTime = {};
    std::wstring entryDescription;
    std::wstring entryZone = SYSTEM_TIME_ZONE_KEY;
    bool inputValid[4] = { true, true, true, true };
    std::vector<ControlPlacement> controls;
    std::vector<MONTHDAYSTATE> dayStates;
    std::vector<std::wstring> zoneLabels;
    std::shared_ptr<Calculation> calculation;
    SYSTEMTIME firstMonth = {};
    SYSTEMTIME lastNow = {};
    ULONG_PTR calculationGeneration = 0;
    bool calculationPending = false;
    bool calculationQueued = false;
    bool highlightsPending = false;
    bool labelsPending = false;
    SIZE dialogUnits = {};
    SIZE contentSize = {};
    unsigned long presetsRevision = 0;
    int editing = -1;
    int sortColumn = 0;
    bool sortDescending = false;
    bool presetsLoaded = false;
    bool ownsFont = false;
    bool initialized = false;
    bool updating = false;
    bool styling = false;
    bool layingOut = false;

    void InitializeDates();
    HWND CreateFormDialog(UINT resource, HWND parent);
    void ReadTemplateLayout(HWND dialog, UINT resource);
    void Layout();
    void FitToWorkArea() const;
    void Scroll(int bar, int request) const;
    void SelectPage();
    void UpdateInputs();
    void FillTimeZones(int index);
    void UpdateTimeInput(int index, bool fromUtc, int choice = -1);
    void UpdateNow();
    void UpdateResults();
    void RequestCalculation(bool highlights = false, bool labels = false);
    void StartCalculation();
    void CompleteCalculation(ULONG_PTR generation);
    void ApplyCalculation(const Calculation& result) const;
    void UpdateHighlights();
    void FillDayStates(const SYSTEMTIME& first, int count);
    void FillPresets();
    void UpdatePresetColumns() const;
    void ApplyPresetSort() const;
    void SelectPreset(HWND combo, const SYSTEMTIME& time) const;
    void UpdatePresetButtons() const;
    bool SavePresets(const std::vector<TimeCalculatorPreset>& updated);
    void SavePreset();
    void EditPreset();
    void DeletePresets();
    void CancelEdit();
    void ShowPresetMenu(LPARAM position);
    void HandleCommand(HWND source, int id, int notification);
    INT_PTR HandleNotification(NMHDR* notification);
    INT_PTR HandleMessage(HWND dialog, UINT message, WPARAM wParam, LPARAM lParam);
    static INT_PTR CALLBACK DialogProc(HWND dialog, UINT message, WPARAM wParam, LPARAM lParam);
    static BOOL CALLBACK ApplyControlStyle(HWND control, LPARAM parameter);
    static int CALLBACK ComparePresets(LPARAM first, LPARAM second, LPARAM parameter);
    static DWORD WINAPI Calculate(void* parameter);
};
