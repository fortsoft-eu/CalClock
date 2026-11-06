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
 * Last modified for version 1.7.2.0
 */

#pragma once

#include "CalClock.h"

const size_t MAX_WIDGET_CLIPBOARD_BYTES = 4 * 1024 * 1024;

using WidgetDefaultsFactory = WidgetConfig(*)(WidgetType type, int index, AppLanguage language,
    int fontAntialiasing);

/// Returns the per-user CalClock settings.xml path, optionally creating its directories.
/// Returns an empty string if the location cannot be obtained or created.
std::wstring AutomaticXmlSettingsPath(bool createDirectory);

/// Returns the independent times.xml path in roaming AppData, optionally creating its directories.
std::wstring CalculatorPresetsPath(bool createDirectory);

/// Reads standalone user XML; optionally extracts only user dates from a settings or export document.
/// A missing file denotes an empty collection only when loading the standalone application data.
bool ReadCalculatorPresets(const std::wstring& path, std::vector<TimeCalculatorPreset>* presets,
    bool allowSettings = false);

/// Reads XML or legacy UTF-8 text with an optional BOM, converting local text dates in the supplied zone.
/// Preserves the destination on failure, including ambiguous or nonexistent local timestamps.
bool ReadCalculatorPresetImport(const std::wstring& path, const DYNAMIC_TIME_ZONE_INFORMATION& zone,
    const std::wstring& zoneKey, std::vector<TimeCalculatorPreset>* presets);

/// Writes user-supplied dates through a temporary file, preserving the existing file on failure.
bool WriteCalculatorPresets(const std::wstring& path, const std::vector<TimeCalculatorPreset>& presets);

/// Deletes the automatic XML settings file and attempts to remove its now-empty application and vendor
/// directories.
void RemoveAutomaticXmlSettings();

/// Deletes CalClock's per-user settings tree and attempts to remove the empty vendor key.
void RemoveRegistrySettings();

/// Writes a nonempty, bounded widget snapshot to the specified XML file, creating or replacing that file.
/// An optional user-data collection is included only for explicit exports, never for automatic settings
/// saves. Returns false for invalid input or a file or serialization error.
bool WriteSettingsXml(const std::wstring& path, const SettingsSnapshot& snapshot,
    const std::vector<TimeCalculatorPreset>* presets = nullptr);

/// Loads and validates a settings XML file no larger than 32 MiB, leaving destinations unchanged on failure.
/// Returns exported user data separately; the caller merges it rather than replacing existing data.
/// An explicit presetsOnly output also permits a standalone user-data document, leaving snapshot unchanged.
bool ReadSettingsXml(const std::wstring& path, AppLanguage defaultLanguage,
    WidgetDefaultsFactory createDefaults, SettingsSnapshot* snapshot,
    std::vector<TimeCalculatorPreset>* presets = nullptr, bool* presetsOnly = nullptr);

/// Loads per-user settings using supplied defaults and a widget-default factory, including the older
/// single-widget layout. Returns false if arguments are invalid or the settings root cannot be opened.
bool ReadRegistrySettings(const SettingsSnapshot& defaults, WidgetDefaultsFactory createDefaults,
    SettingsSnapshot* snapshot);

/// Writes global settings and widget subkeys, removes obsolete widget keys, and deletes automatic XML
/// after success. Reports key-creation failures; individual value writes do not return status.
bool WriteRegistrySettings(const SettingsSnapshot& snapshot);

/// Serializes selected widgets to bounded XML bytes, replacing data only when serialization succeeds.
bool SerializeWidgetClipboardData(const std::vector<WidgetConfig>& widgets, std::vector<BYTE>* data);

/// Validates bounded clipboard XML and returns its widget configurations, leaving widgets unchanged on
/// failure.
bool DeserializeWidgetClipboardData(const std::vector<BYTE>& data, AppLanguage defaultLanguage,
    WidgetDefaultsFactory createDefaults, std::vector<WidgetConfig>* widgets);
