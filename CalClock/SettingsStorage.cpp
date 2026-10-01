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
 * Last modified for version 1.5.1.0
 */

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "SettingsStorage.h"
#include <windows.h>
#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <limits>
#include <locale>
#include <sstream>
#include <cwctype>
#include <shlobj.h>
#include <shlwapi.h>
#include <utility>
#include <vector>
#include <xmllite.h>

#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "XmlLite.lib")

const wchar_t REGISTRY_PATH[] = L"Software\\FortSoft\\CalClock";
const wchar_t VENDOR_REGISTRY_PATH[] = L"Software\\FortSoft";

/// Reads a registry value and reports whether it was retrieved as REG_DWORD.
static bool ReadDword(HKEY key, const wchar_t* name, DWORD* value) {
    DWORD type = 0;
    DWORD size = sizeof(*value);
    return RegQueryValueExW(key, name, nullptr, &type,
        reinterpret_cast<BYTE*>(value), &size) == ERROR_SUCCESS && type == REG_DWORD;
}

/// Reads a registry value into a signed 64-bit destination and reports whether its type is REG_QWORD.
static bool ReadQword(HKEY key, const wchar_t* name, LONGLONG* value) {
    DWORD type = 0;
    DWORD size = sizeof(*value);
    return RegQueryValueExW(key, name, nullptr, &type,
        reinterpret_cast<BYTE*>(value), &size) == ERROR_SUCCESS && type == REG_QWORD;
}

/// Reads a registry string without expanding environment variables, replacing the destination only on success.
static bool ReadString(HKEY key, const wchar_t* name, std::wstring* value) {
    DWORD type = 0;
    DWORD size = 0;
    if (RegQueryValueExW(key, name, nullptr, &type, nullptr, &size) != ERROR_SUCCESS
            || type != REG_SZ && type != REG_EXPAND_SZ || size < sizeof(wchar_t)) {
        return false;
    }
    std::vector<wchar_t> buffer(size / sizeof(wchar_t) + 1, 0);
    if (RegQueryValueExW(key, name, nullptr, &type, reinterpret_cast<BYTE*>(buffer.data()), &size) != ERROR_SUCCESS) {
        return false;
    }
    *value = buffer.data();
    return true;
}

/// Writes a 32-bit registry value as REG_DWORD without reporting write errors.
static void WriteDword(HKEY key, const wchar_t* name, DWORD value) {
    RegSetValueExW(key, name, 0, REG_DWORD, reinterpret_cast<const BYTE*>(&value), sizeof(value));
}

/// Writes a signed 64-bit value's representation as REG_QWORD without reporting write errors.
static void WriteQword(HKEY key, const wchar_t* name, LONGLONG value) {
    RegSetValueExW(key, name, 0, REG_QWORD, reinterpret_cast<const BYTE*>(&value), sizeof(value));
}

/// Writes a null-terminated Unicode REG_SZ value without reporting write errors.
static void WriteString(HKEY key, const wchar_t* name, const std::wstring& value) {
    RegSetValueExW(key, name, 0, REG_SZ, reinterpret_cast<const BYTE*>(value.c_str()),
        static_cast<DWORD>((value.size() + 1) * sizeof(wchar_t)));
}

/// Formats a double with locale-independent punctuation and enough precision for a round trip.
static std::wstring FormatRealNumber(double value) {
    std::wostringstream stream;
    stream.imbue(std::locale::classic());
    stream << std::setprecision(std::numeric_limits<double>::max_digits10) << value;
    return stream.str();
}

/// Parses a finite, locale-independent double, allowing surrounding whitespace but rejecting trailing nonspace text.
static bool ParseRealNumber(const std::wstring& text, double* value) {
    std::wistringstream stream(text);
    stream.imbue(std::locale::classic());
    double parsed = 0.0;
    if (!(stream >> parsed) || !std::isfinite(parsed)) {
        return false;
    }
    stream >> std::ws;
    if (!stream.eof()) {
        return false;
    }
    *value = parsed;
    return true;
}

/// Reads the stored generator volume from either an integral registry value or a decimal string.
static bool ReadTimeSignalVolume(HKEY key, double* volume) {
    DWORD integer = 0;
    if (ReadDword(key, L"TimeSignalVolume", &integer)) {
        *volume = integer;
        return true;
    }
    std::wstring text;
    return ReadString(key, L"TimeSignalVolume", &text) && ParseRealNumber(text, volume);
}

/// Clamps generator volume and writes whole steps as REG_DWORD or fractional steps as a decimal string.
static void WriteTimeSignalVolume(HKEY key, double volume) {
    volume = std::clamp<double>(volume, TIME_SIGNAL_VOLUME_MIN, TIME_SIGNAL_VOLUME_MAX);
    if (volume == std::floor(volume)) {
        WriteDword(key, L"TimeSignalVolume", static_cast<DWORD>(volume));
    } else {
        WriteString(key, L"TimeSignalVolume", FormatRealNumber(volume));
    }
}

/// Returns the per-user CalClock settings.xml path, optionally creating its directories.
/// Returns an empty string if the location cannot be obtained or created.
std::wstring AutomaticXmlSettingsPath(bool createDirectory) {
    wchar_t appData[MAX_PATH] = {};
    if (SHGetFolderPathW(nullptr, CSIDL_APPDATA | (createDirectory ? CSIDL_FLAG_CREATE : 0), nullptr, SHGFP_TYPE_CURRENT,
        appData) != S_OK) {
        return L"";
    }
    std::wstring vendorDirectory = std::wstring(appData) + L"\\FortSoft";
    if (createDirectory && !CreateDirectoryW(vendorDirectory.c_str(), nullptr) && GetLastError() != ERROR_ALREADY_EXISTS) {
        return L"";
    }
    std::wstring directory = vendorDirectory + L"\\CalClock";
    if (createDirectory && !CreateDirectoryW(directory.c_str(), nullptr) && GetLastError() != ERROR_ALREADY_EXISTS) {
        return L"";
    }
    return directory + L"\\settings.xml";
}

/// Deletes the automatic XML settings file and attempts to remove its now-empty application and vendor directories.
void RemoveAutomaticXmlSettings() {
    std::wstring path = AutomaticXmlSettingsPath(false);
    if (path.empty()) {
        return;
    }
    DeleteFileW(path.c_str());
    size_t separator = path.find_last_of(L"\\/");
    if (separator == std::wstring::npos) {
        return;
    }
    std::wstring applicationDirectory = path.substr(0, separator);
    RemoveDirectoryW(applicationDirectory.c_str());
    separator = applicationDirectory.find_last_of(L"\\/");
    if (separator == std::wstring::npos) {
        return;
    }
    std::wstring vendorDirectory = applicationDirectory.substr(0, separator);
    RemoveDirectoryW(vendorDirectory.c_str());
}

/// Writes a text attribute and returns the XML writer's HRESULT.
static HRESULT WriteXmlTextAttribute(IXmlWriter* writer, const wchar_t* name, const std::wstring& value) {
    return writer->WriteAttributeString(nullptr, name, nullptr, value.c_str());
}

/// Writes a signed integer as a decimal XML attribute and returns the writer's HRESULT.
static HRESULT WriteXmlNumberAttribute(IXmlWriter* writer, const wchar_t* name, LONGLONG value) {
    wchar_t text[32] = {};
    _i64tow_s(value, text, ARRAYSIZE(text), 10);
    return writer->WriteAttributeString(nullptr, name, nullptr, text);
}

/// Copies the widget's primary font properties into a FontSelection value.
static FontSelection GetWidgetFontSelection(const WidgetConfig& config) {
    FontSelection selection = {};
    selection.face = config.fontFace;
    selection.dialogSize = config.fontDialogSize;
    selection.weight = config.fontWeight;
    selection.italic = config.fontItalic;
    selection.underline = config.fontUnderline;
    selection.strikeOut = config.fontStrikeOut;
    selection.charSet = config.fontCharSet;
    return selection;
}

/// Serializes global settings and widgets to an XML stream and reports whether writing and flushing succeeded.
static bool WriteSettingsXmlStream(IStream* stream, const SettingsSnapshot& snapshot) {
    IXmlWriter* writer = nullptr;
    HRESULT result = CreateXmlWriter(__uuidof(IXmlWriter), reinterpret_cast<void**>(&writer), nullptr);
    if (SUCCEEDED(result)) {
        result = writer->SetOutput(stream);
    }
    if (SUCCEEDED(result)) {
        result = writer->SetProperty(XmlWriterProperty_Indent, TRUE);
    }
    if (SUCCEEDED(result)) {
        result = writer->WriteStartDocument(XmlStandalone_Omit);
    }
    if (SUCCEEDED(result)) {
        result = writer->WriteStartElement(nullptr, L"CalClockSettings", nullptr);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"version", 1);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"language", snapshot.language);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"disableThemes", snapshot.themesDisabled);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"generatedTimeSignal", snapshot.generatedTimeSignal ? 0 : 1);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlTextAttribute(writer, L"timeSignalVolume", FormatRealNumber(snapshot.timeSignalVolume));
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"snapWidgetsToWorkArea", snapshot.snapWidgetsToWorkArea);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"fontAntialiasing", snapshot.fontAntialiasing);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlTextAttribute(writer, L"fontFace", snapshot.fontFace);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"fontDialogSize", snapshot.fontDialogSize);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"fontWeight", snapshot.fontWeight);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"fontItalic", snapshot.fontItalic);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"useNtpTime", snapshot.useNtpTime);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"ntpPreset", snapshot.ntpPreset);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlTextAttribute(writer, L"ntpServers", snapshot.ntpServers);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"settingsX", snapshot.settingsX);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"settingsY", snapshot.settingsY);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"settingsTab", snapshot.settingsTab);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"lastAddedWidgetType", snapshot.lastAddedWidgetType);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"helpX", snapshot.helpX);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"helpY", snapshot.helpY);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"aboutX", snapshot.aboutX);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"aboutY", snapshot.aboutY);
    }
    if (SUCCEEDED(result)) {
        result = writer->WriteStartElement(nullptr, L"Widgets", nullptr);
    }
    for (size_t index = 0; index < snapshot.widgets.size() && SUCCEEDED(result); index++) {
        const WidgetConfig& config = snapshot.widgets[index];
        result = writer->WriteStartElement(nullptr, L"Widget", nullptr);
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"id", config.id);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"type", config.type);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlTextAttribute(writer, L"name", config.name);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"visible", config.visible);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"topMost", config.topMost);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"showSeconds", config.showSeconds);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"showUtc", config.showUtc);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"showUtcText", config.showUtcText);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"language", config.language);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlTextAttribute(writer, L"timeZoneKey", config.timeZoneKey);
        }
        for (int index = 0; index < ADDITIONAL_CLOCK_COUNT && SUCCEEDED(result); index++) {
            const AdditionalClockConfig& clock = config.additionalClocks[index];
            std::wstring prefix = L"additionalClock" + std::to_wstring(index + 1);
            result = WriteXmlNumberAttribute(writer, (prefix + L"Enabled").c_str(), clock.enabled);
            if (SUCCEEDED(result)) {
                result = WriteXmlTextAttribute(writer, (prefix + L"Name").c_str(), clock.name);
            }
            if (SUCCEEDED(result)) {
                result = WriteXmlTextAttribute(writer, (prefix + L"TimeZoneKey").c_str(), clock.timeZoneKey);
            }
            if (SUCCEEDED(result)) {
                result = WriteXmlNumberAttribute(writer, (prefix + L"Size").c_str(), clock.size);
            }
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlTextAttribute(writer, L"monitorDevices", config.monitorDevices);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"blackoutOtherMonitors", config.blackoutOtherMonitors);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"offsetMilliseconds", config.offsetMilliseconds);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"x", config.x);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"y", config.y);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"previewX", config.previewX);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"previewY", config.previewY);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"size", config.size);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"opacity", config.opacity);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"fontSize", config.fontSize);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"fontDialogSize", config.fontDialogSize);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"fontAntialiasing", config.fontAntialiasing);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"leadingZero", config.leadingZeroMode);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"showAmPm", config.showAmPm);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"timeFormat", config.timeFormat);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"transparentBackground", config.transparentBackground);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"disableThemes", config.disableThemes);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlTextAttribute(writer, L"fontFace", config.fontFace);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"fontWeight", config.fontWeight);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"fontItalic", config.fontItalic);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"fontUnderline", config.fontUnderline);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"fontStrikeOut", config.fontStrikeOut);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"fontCharSet", config.fontCharSet);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlTextAttribute(writer, L"panelTopFontFace", config.panelTopFont.face);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelTopFontSize", config.panelTopFont.dialogSize);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelTopFontWeight", config.panelTopFont.weight);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelTopFontItalic", config.panelTopFont.italic);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelTopFontUnderline", config.panelTopFont.underline);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelTopFontStrikeOut", config.panelTopFont.strikeOut);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelTopFontCharSet", config.panelTopFont.charSet);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlTextAttribute(writer, L"panelTimeFontFace", config.panelTimeFont.face);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelTimeFontSize", config.panelTimeFont.dialogSize);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelTimeFontWeight", config.panelTimeFont.weight);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelTimeFontItalic", config.panelTimeFont.italic);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelTimeFontUnderline", config.panelTimeFont.underline);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelTimeFontStrikeOut", config.panelTimeFont.strikeOut);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelTimeFontCharSet", config.panelTimeFont.charSet);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlTextAttribute(writer, L"panelBottomFontFace", config.panelBottomFont.face);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelBottomFontSize", config.panelBottomFont.dialogSize);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelBottomFontWeight", config.panelBottomFont.weight);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelBottomFontItalic", config.panelBottomFont.italic);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelBottomFontUnderline", config.panelBottomFont.underline);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelBottomFontStrikeOut", config.panelBottomFont.strikeOut);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelBottomFontCharSet", config.panelBottomFont.charSet);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"padding", config.padding);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"borderStyle", config.borderStyle);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"borderWidth", config.borderWidth);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"borderColor", static_cast<DWORD>(config.borderColor));
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"textColor", static_cast<DWORD>(config.textColor));
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"backgroundColor", static_cast<DWORD>(config.backgroundColor));
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"alarmTextColor", static_cast<DWORD>(config.alarmTextColor));
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"alarmBackgroundColor",
                static_cast<DWORD>(config.alarmBackgroundColor));
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"showToday", config.showToday);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"weekNumbers", config.weekNumbers);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"sundayFirst", config.sundayFirst);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"dateCopyFormat", config.dateCopyFormat);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"timeSignal", config.timeSignal);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"soundsMuted", config.soundsMuted);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"alarmEnabled", config.alarmEnabled);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"alarmDays", config.alarmDays);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"alarmTimeSignal", config.alarmTimeSignal);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"alarmHour", config.alarmHour);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"alarmMinute", config.alarmMinute);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"runCommand", config.runCommand);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"loopAudio", config.loopAudio);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"alarmVolume", config.alarmVolume);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlTextAttribute(writer, L"command", config.command);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"callRemoteScript", config.callRemoteScript);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlTextAttribute(writer, L"remoteScriptUrl", config.remoteScriptUrl);
        }
        if (SUCCEEDED(result)) {
            result = writer->WriteEndElement();
        }
    }
    if (SUCCEEDED(result)) {
        result = writer->WriteEndElement();
    }
    if (SUCCEEDED(result)) {
        result = writer->WriteEndElement();
    }
    if (SUCCEEDED(result)) {
        result = writer->WriteEndDocument();
    }
    if (SUCCEEDED(result)) {
        result = writer->Flush();
    }
    if (writer != nullptr) {
        writer->Release();
    }
    return SUCCEEDED(result);
}

/// Writes a nonempty, bounded widget snapshot to the specified XML file, creating or replacing that file.
/// Returns false for invalid input or a file or serialization error.
bool WriteSettingsXml(const std::wstring& path, const SettingsSnapshot& snapshot) {
    if (path.empty() || snapshot.widgets.empty() || snapshot.widgets.size() > MAX_WIDGET_COUNT) {
        return false;
    }
    IStream* stream = nullptr;
    if (FAILED(SHCreateStreamOnFileEx(path.c_str(),
        STGM_CREATE | STGM_WRITE | STGM_SHARE_DENY_WRITE, FILE_ATTRIBUTE_NORMAL, TRUE, nullptr, &stream))) {
        return false;
    }
    bool success = WriteSettingsXmlStream(stream, snapshot);
    stream->Release();
    return success;
}

/// Serializes selected widgets to bounded XML bytes, replacing data only when serialization succeeds.
bool SerializeWidgetClipboardData(const std::vector<WidgetConfig>& widgets, std::vector<BYTE>* data) {
    if (widgets.empty() || widgets.size() > MAX_WIDGET_COUNT || data == nullptr) {
        return false;
    }
    IStream* stream = SHCreateMemStream(nullptr, 0);
    if (stream == nullptr) {
        return false;
    }
    SettingsSnapshot snapshot;
    snapshot.widgets = widgets;
    STATSTG information = {};
    bool success = WriteSettingsXmlStream(stream, snapshot)
        && SUCCEEDED(stream->Stat(&information, STATFLAG_NONAME))
        && information.cbSize.HighPart == 0
        && information.cbSize.LowPart > 0
        && information.cbSize.LowPart <= MAX_WIDGET_CLIPBOARD_BYTES;
    std::vector<BYTE> serialized;
    if (success) {
        serialized.resize(information.cbSize.LowPart);
        LARGE_INTEGER beginning = {};
        ULONG bytesRead = 0;
        success = SUCCEEDED(stream->Seek(beginning, STREAM_SEEK_SET, nullptr))
            && SUCCEEDED(stream->Read(serialized.data(), information.cbSize.LowPart, &bytesRead))
            && bytesRead == information.cbSize.LowPart;
    }
    stream->Release();
    if (success) {
        *data = std::move(serialized);
    }
    return success;
}

/// Reads a named attribute into an owned string and restores the reader to the element after accessing its value.
static bool ReadXmlAttribute(IXmlReader* reader, const wchar_t* name, std::wstring* value) {
    if (reader->MoveToAttributeByName(name, nullptr) != S_OK) {
        return false;
    }
    const wchar_t* text = nullptr;
    UINT length = 0;
    HRESULT result = reader->GetValue(&text, &length);
    reader->MoveToElement();
    if (FAILED(result) || text == nullptr) {
        return false;
    }
    value->assign(text, length);
    return true;
}

/// Parses a nonempty decimal integer string and rejects unconsumed trailing characters.
static bool ParseXmlNumber(const std::wstring& text, LONGLONG* value) {
    if (text.empty()) {
        return false;
    }
    wchar_t* end = nullptr;
    LONGLONG parsed = _wcstoi64(text.c_str(), &end, 10);
    if (end == text.c_str() || *end != L'\0') {
        return false;
    }
    *value = parsed;
    return true;
}

/// Reads an XML attribute and parses its value as a decimal integer.
static bool ReadXmlNumberAttribute(IXmlReader* reader, const wchar_t* name, LONGLONG* value) {
    std::wstring text;
    return ReadXmlAttribute(reader, name, &text) && ParseXmlNumber(text, value);
}

/// Starts with type-specific widget defaults, then reads recognized XML attributes with range checks and clamping.
static void ReadWidgetXml(IXmlReader* reader, int index, AppLanguage defaultLanguage, int defaultFontAntialiasing,
        WidgetDefaultsFactory createDefaults, WidgetConfig* config) {
    LONGLONG number = 0;
    int type = WIDGET_ANALOG;
    if (ReadXmlNumberAttribute(reader, L"type", &number) && number >= 0 && number < WIDGET_TYPE_COUNT) {
        type = static_cast<int>(number);
    }
    *config = createDefaults(static_cast<WidgetType>(type), index, defaultLanguage, defaultFontAntialiasing);
    config->fontAntialiasing = std::clamp(defaultFontAntialiasing, 0, FONT_ANTIALIAS_COUNT - 1);
    std::wstring text;
    if (ReadXmlNumberAttribute(reader, L"id", &number) && number > 0 && number <= INT_MAX) {
        config->id = static_cast<int>(number);
    }
    config->type = static_cast<WidgetType>(type);
    if (ReadXmlAttribute(reader, L"name", &text)) {
        config->name = text;
    }
    if (ReadXmlNumberAttribute(reader, L"visible", &number)) {
        config->visible = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"topMost", &number)) {
        config->topMost = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"showSeconds", &number)) {
        config->showSeconds = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"showUtc", &number)) {
        config->showUtc = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"showUtcText", &number)) {
        config->showUtcText = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"language", &number) && number >= 0 && number < LANG_COUNT) {
        config->language = static_cast<AppLanguage>(number);
    }
    if (ReadXmlAttribute(reader, L"timeZoneKey", &text)) {
        config->timeZoneKey = text;
    }
    for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
        AdditionalClockConfig& clock = config->additionalClocks[index];
        std::wstring prefix = L"additionalClock" + std::to_wstring(index + 1);
        if (ReadXmlNumberAttribute(reader, (prefix + L"Enabled").c_str(), &number)) {
            clock.enabled = number != 0;
        }
        if (ReadXmlAttribute(reader, (prefix + L"Name").c_str(), &text)) {
            clock.name = text;
        }
        if (ReadXmlAttribute(reader, (prefix + L"TimeZoneKey").c_str(), &text)) {
            clock.timeZoneKey = text;
        }
        if (ReadXmlNumberAttribute(reader, (prefix + L"Size").c_str(), &number)) {
            clock.size = static_cast<int>(std::clamp<LONGLONG>(number, 48, 256));
        }
    }
    if (ReadXmlAttribute(reader, L"monitorDevices", &text)) {
        config->monitorDevices = text;
    }
    if (ReadXmlNumberAttribute(reader, L"blackoutOtherMonitors", &number)) {
        config->blackoutOtherMonitors = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"offsetMilliseconds", &number)) {
        config->offsetMilliseconds = number;
    }
    if (ReadXmlNumberAttribute(reader, L"x", &number) && number >= INT_MIN && number <= INT_MAX) {
        config->x = static_cast<int>(number);
    }
    if (ReadXmlNumberAttribute(reader, L"y", &number) && number >= INT_MIN && number <= INT_MAX) {
        config->y = static_cast<int>(number);
    }
    if (ReadXmlNumberAttribute(reader, L"previewX", &number) && number >= INT_MIN && number <= INT_MAX) {
        config->previewX = static_cast<int>(number);
    }
    if (ReadXmlNumberAttribute(reader, L"previewY", &number) && number >= INT_MIN && number <= INT_MAX) {
        config->previewY = static_cast<int>(number);
    }
    if (ReadXmlNumberAttribute(reader, L"size", &number)) {
        config->size = std::clamp(static_cast<int>(number), 104, 198);
    }
    if (ReadXmlNumberAttribute(reader, L"opacity", &number)) {
        config->opacity = std::clamp(static_cast<int>(number), WIDGET_OPACITY_MIN, WIDGET_OPACITY_MAX);
    }
    if (ReadXmlNumberAttribute(reader, L"fontSize", &number)) {
        int minimumFontSize = config->type == WIDGET_FULLSCREEN ? FULLSCREEN_FONT_SIZE_MIN : DIGITAL_FONT_SIZE_MIN;
        int maximumFontSize = config->type == WIDGET_FULLSCREEN ? FULLSCREEN_FONT_SIZE_MAX : DIGITAL_FONT_SIZE_MAX;
        config->fontSize = std::clamp(static_cast<int>(number), minimumFontSize, maximumFontSize);
    }
    if (config->type == WIDGET_DIGITAL) {
        config->fontDialogSize = config->fontSize * 10;
    }
    if (ReadXmlNumberAttribute(reader, L"fontDialogSize", &number)) {
        int savedSize = static_cast<int>(number);
        config->fontDialogSize = std::clamp(savedSize < 10 ? savedSize * 10 : savedSize, 10, 9990);
    }
    if (ReadXmlNumberAttribute(reader, L"fontAntialiasing", &number) && number >= 0 && number < FONT_ANTIALIAS_COUNT) {
        config->fontAntialiasing = static_cast<int>(number);
    }
    if (ReadXmlNumberAttribute(reader, L"timeFormat", &number) && number >= 0 && number < TIME_FORMAT_COUNT) {
        config->timeFormat = static_cast<int>(number);
    }
    if (ReadXmlNumberAttribute(reader, L"showAmPm", &number)) {
        config->showAmPm = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"leadingZero", &number)) {
        config->leadingZeroMode = std::clamp(static_cast<int>(number), 0, LEADING_ZERO_MODE_COUNT - 1);
    }
    if (ReadXmlNumberAttribute(reader, L"transparentBackground", &number)) {
        config->transparentBackground = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"disableThemes", &number)) {
        config->disableThemes = number != 0;
    }
    if (ReadXmlAttribute(reader, L"fontFace", &text) && text.size() < LF_FACESIZE) {
        config->fontFace = text;
    }
    if (ReadXmlNumberAttribute(reader, L"fontWeight", &number)) {
        config->fontWeight = std::clamp(static_cast<int>(number), 0, 1000);
    }
    if (ReadXmlNumberAttribute(reader, L"fontItalic", &number)) {
        config->fontItalic = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"fontUnderline", &number)) {
        config->fontUnderline = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"fontStrikeOut", &number)) {
        config->fontStrikeOut = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"fontCharSet", &number)) {
        config->fontCharSet = static_cast<BYTE>(std::clamp<LONGLONG>(number, 0, 255));
    }
    config->panelTopFont = GetWidgetFontSelection(*config);
    config->panelTimeFont = config->panelTopFont;
    config->panelBottomFont = config->panelTopFont;
    if (ReadXmlAttribute(reader, L"panelTopFontFace", &text) && text.size() < LF_FACESIZE) {
        config->panelTopFont.face = text;
    }
    if (ReadXmlNumberAttribute(reader, L"panelTopFontSize", &number)) {
        config->panelTopFont.dialogSize = std::clamp(static_cast<int>(number), 10, 9990);
    }
    if (ReadXmlNumberAttribute(reader, L"panelTopFontWeight", &number)) {
        config->panelTopFont.weight = std::clamp(static_cast<int>(number), 0, 1000);
    }
    if (ReadXmlNumberAttribute(reader, L"panelTopFontItalic", &number)) {
        config->panelTopFont.italic = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"panelTopFontUnderline", &number)) {
        config->panelTopFont.underline = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"panelTopFontStrikeOut", &number)) {
        config->panelTopFont.strikeOut = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"panelTopFontCharSet", &number)) {
        config->panelTopFont.charSet = static_cast<BYTE>(std::clamp<LONGLONG>(number, 0, 255));
    }
    if (ReadXmlAttribute(reader, L"panelTimeFontFace", &text) && text.size() < LF_FACESIZE) {
        config->panelTimeFont.face = text;
    }
    if (ReadXmlNumberAttribute(reader, L"panelTimeFontSize", &number)) {
        config->panelTimeFont.dialogSize = std::clamp(static_cast<int>(number), 10, 9990);
    }
    if (ReadXmlNumberAttribute(reader, L"panelTimeFontWeight", &number)) {
        config->panelTimeFont.weight = std::clamp(static_cast<int>(number), 0, 1000);
    }
    if (ReadXmlNumberAttribute(reader, L"panelTimeFontItalic", &number)) {
        config->panelTimeFont.italic = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"panelTimeFontUnderline", &number)) {
        config->panelTimeFont.underline = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"panelTimeFontStrikeOut", &number)) {
        config->panelTimeFont.strikeOut = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"panelTimeFontCharSet", &number)) {
        config->panelTimeFont.charSet = static_cast<BYTE>(std::clamp<LONGLONG>(number, 0, 255));
    }
    if (ReadXmlAttribute(reader, L"panelBottomFontFace", &text) && text.size() < LF_FACESIZE) {
        config->panelBottomFont.face = text;
    }
    if (ReadXmlNumberAttribute(reader, L"panelBottomFontSize", &number)) {
        config->panelBottomFont.dialogSize = std::clamp(static_cast<int>(number), 10, 9990);
    }
    if (ReadXmlNumberAttribute(reader, L"panelBottomFontWeight", &number)) {
        config->panelBottomFont.weight = std::clamp(static_cast<int>(number), 0, 1000);
    }
    if (ReadXmlNumberAttribute(reader, L"panelBottomFontItalic", &number)) {
        config->panelBottomFont.italic = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"panelBottomFontUnderline", &number)) {
        config->panelBottomFont.underline = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"panelBottomFontStrikeOut", &number)) {
        config->panelBottomFont.strikeOut = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"panelBottomFontCharSet", &number)) {
        config->panelBottomFont.charSet = static_cast<BYTE>(std::clamp<LONGLONG>(number, 0, 255));
    }
    if (ReadXmlNumberAttribute(reader, L"padding", &number)) {
        int maximumPadding = config->type == WIDGET_FULLSCREEN ? FULLSCREEN_PADDING_MAX : DIGITAL_PADDING_MAX;
        config->padding = std::clamp(static_cast<int>(number), 0, maximumPadding);
    }
    if (ReadXmlNumberAttribute(reader, L"borderStyle", &number)) {
        config->borderStyle = std::clamp(static_cast<int>(number), 0, DIGITAL_BORDER_STYLE_COUNT - 1);
    }
    if (ReadXmlNumberAttribute(reader, L"borderWidth", &number)) {
        config->borderWidth = std::clamp(static_cast<int>(number), 0, DIGITAL_BORDER_WIDTH_MAX);
    }
    if (ReadXmlNumberAttribute(reader, L"borderColor", &number)) {
        config->borderColor = static_cast<COLORREF>(number & 0xFFFFFF);
    }
    if (ReadXmlNumberAttribute(reader, L"textColor", &number)) {
        config->textColor = static_cast<COLORREF>(number & 0xFFFFFF);
    }
    if (ReadXmlNumberAttribute(reader, L"backgroundColor", &number)) {
        config->backgroundColor = static_cast<COLORREF>(number & 0xFFFFFF);
    }
    if (ReadXmlNumberAttribute(reader, L"alarmTextColor", &number)) {
        config->alarmTextColor = static_cast<COLORREF>(number & 0xFFFFFF);
    }
    if (ReadXmlNumberAttribute(reader, L"alarmBackgroundColor", &number)) {
        config->alarmBackgroundColor = static_cast<COLORREF>(number & 0xFFFFFF);
    }
    if (ReadXmlNumberAttribute(reader, L"showToday", &number)) {
        config->showToday = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"weekNumbers", &number)) {
        config->weekNumbers = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"sundayFirst", &number)) {
        config->sundayFirst = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"dateCopyFormat", &number)) {
        config->dateCopyFormat = std::clamp(static_cast<int>(number), 0, DATE_FORMAT_COUNT - 1);
    }
    if (ReadXmlNumberAttribute(reader, L"timeSignal", &number) && number >= 0 && number < TIME_SIGNAL_COUNT) {
        config->timeSignal = static_cast<TimeSignalMode>(number);
    }
    if (ReadXmlNumberAttribute(reader, L"soundsMuted", &number)) {
        config->soundsMuted = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"alarmEnabled", &number)) {
        config->alarmEnabled = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"alarmDays", &number)) {
        config->alarmDays = static_cast<unsigned int>(number) & ALARM_DAYS_ALL;
    }
    if (ReadXmlNumberAttribute(reader, L"alarmTimeSignal", &number)) {
        config->alarmTimeSignal = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"alarmHour", &number)) {
        config->alarmHour = std::clamp(static_cast<int>(number), 0, 23);
    }
    if (ReadXmlNumberAttribute(reader, L"alarmMinute", &number)) {
        config->alarmMinute = std::clamp(static_cast<int>(number), 0, 59);
    }
    if (ReadXmlNumberAttribute(reader, L"runCommand", &number)) {
        config->runCommand = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"loopAudio", &number)) {
        config->loopAudio = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"alarmVolume", &number)) {
        config->alarmVolume = static_cast<int>(std::clamp<LONGLONG>(number, ALARM_VOLUME_MIN, ALARM_VOLUME_MAX));
    }
    if (ReadXmlAttribute(reader, L"command", &text)) {
        config->command = text;
    }
    if (ReadXmlNumberAttribute(reader, L"callRemoteScript", &number)) {
        config->callRemoteScript = number != 0;
    }
    if (ReadXmlAttribute(reader, L"remoteScriptUrl", &text)) {
        config->remoteScriptUrl = text;
    }
}

/// Parses and validates a settings XML stream, including its root, widget count, and unique positive widget IDs.
/// Assigns the destination snapshot only after validation succeeds.
static bool ReadSettingsXmlStream(IStream* stream, AppLanguage defaultLanguage, WidgetDefaultsFactory createDefaults,
        SettingsSnapshot* snapshot) {
    IXmlReader* reader = nullptr;
    HRESULT result = CreateXmlReader(__uuidof(IXmlReader), reinterpret_cast<void**>(&reader), nullptr);
    if (SUCCEEDED(result)) {
        result = reader->SetInput(stream);
    }
    SettingsSnapshot loaded = {};
    loaded.language = defaultLanguage;
    bool rootFound = false;
    XmlNodeType nodeType = XmlNodeType_None;
    while (SUCCEEDED(result) && (result = reader->Read(&nodeType)) == S_OK) {
        if (nodeType != XmlNodeType_Element) {
            continue;
        }
        const wchar_t* localName = nullptr;
        UINT nameLength = 0;
        if (FAILED(reader->GetLocalName(&localName, &nameLength)) || localName == nullptr) {
            result = E_FAIL;
            break;
        }
        std::wstring element(localName, nameLength);
        if (element == L"CalClockSettings") {
            if (rootFound) {
                result = E_FAIL;
                break;
            }
            LONGLONG number = 0;
            if (!ReadXmlNumberAttribute(reader, L"version", &number) || number != 1) {
                result = E_FAIL;
                break;
            }
            rootFound = true;
            if (ReadXmlNumberAttribute(reader, L"language", &number) && number >= 0 && number < LANG_COUNT) {
                loaded.language = static_cast<AppLanguage>(number);
            }
            if (ReadXmlNumberAttribute(reader, L"disableThemes", &number)) {
                loaded.themesDisabled = number != 0;
            }
            if (ReadXmlNumberAttribute(reader, L"generatedTimeSignal", &number)) {
                loaded.generatedTimeSignal = number == 0;
            }
            std::wstring volumeText;
            double volume = 0.0;
            if (ReadXmlAttribute(reader, L"timeSignalVolume", &volumeText) && ParseRealNumber(volumeText, &volume)) {
                loaded.timeSignalVolume = std::clamp<double>(volume, TIME_SIGNAL_VOLUME_MIN, TIME_SIGNAL_VOLUME_MAX);
            }
            if (ReadXmlNumberAttribute(reader, L"snapWidgetsToWorkArea", &number)) {
                loaded.snapWidgetsToWorkArea = number != 0;
            }
            if (ReadXmlNumberAttribute(reader, L"fontAntialiasing", &number)
                    && number >= 0
                    && number < FONT_ANTIALIAS_COUNT) {
                loaded.fontAntialiasing = static_cast<int>(number);
            }
            std::wstring applicationFontFace;
            if (ReadXmlAttribute(reader, L"fontFace", &applicationFontFace) && applicationFontFace.size() < LF_FACESIZE) {
                loaded.fontFace = applicationFontFace;
            }
            if (ReadXmlNumberAttribute(reader, L"fontDialogSize", &number)) {
                int savedSize = static_cast<int>(number);
                loaded.fontDialogSize = std::clamp(savedSize < 10 ? savedSize * 10 : savedSize, 10, 9990);
            }
            if (ReadXmlNumberAttribute(reader, L"fontWeight", &number)) {
                loaded.fontWeight = std::clamp(static_cast<int>(number), 0, 1000);
            }
            if (ReadXmlNumberAttribute(reader, L"fontItalic", &number)) {
                loaded.fontItalic = number != 0;
            }
            if (ReadXmlNumberAttribute(reader, L"useNtpTime", &number)) {
                loaded.useNtpTime = number != 0;
            }
            if (ReadXmlNumberAttribute(reader, L"ntpPreset", &number) && number >= 0 && number < NTP_PRESET_COUNT) {
                loaded.ntpPreset = static_cast<int>(number);
            }
            std::wstring text;
            if (ReadXmlAttribute(reader, L"ntpServers", &text) && text.size() <= 1024) {
                loaded.ntpServers = text;
            }
            if (ReadXmlNumberAttribute(reader, L"settingsX", &number) && number >= INT_MIN && number <= INT_MAX) {
                loaded.settingsX = static_cast<int>(number);
            }
            if (ReadXmlNumberAttribute(reader, L"settingsY", &number) && number >= INT_MIN && number <= INT_MAX) {
                loaded.settingsY = static_cast<int>(number);
            }
            if (ReadXmlNumberAttribute(reader, L"settingsTab", &number) && number >= 0 && number < SETTINGS_TAB_COUNT) {
                loaded.settingsTab = static_cast<int>(number);
            }
            if (ReadXmlNumberAttribute(reader, L"lastAddedWidgetType", &number)
                    && number >= 0
                    && number < WIDGET_TYPE_COUNT) {
                loaded.lastAddedWidgetType = static_cast<WidgetType>(number);
            }
            if (ReadXmlNumberAttribute(reader, L"helpX", &number) && number >= INT_MIN && number <= INT_MAX) {
                loaded.helpX = static_cast<int>(number);
            }
            if (ReadXmlNumberAttribute(reader, L"helpY", &number) && number >= INT_MIN && number <= INT_MAX) {
                loaded.helpY = static_cast<int>(number);
            }
            if (ReadXmlNumberAttribute(reader, L"aboutX", &number) && number >= INT_MIN && number <= INT_MAX) {
                loaded.aboutX = static_cast<int>(number);
            }
            if (ReadXmlNumberAttribute(reader, L"aboutY", &number) && number >= INT_MIN && number <= INT_MAX) {
                loaded.aboutY = static_cast<int>(number);
            }
        } else if (element == L"Widget" && rootFound) {
            if (loaded.widgets.size() >= MAX_WIDGET_COUNT) {
                result = E_FAIL;
                break;
            }
            WidgetConfig config = {};
            ReadWidgetXml(reader, static_cast<int>(loaded.widgets.size()), defaultLanguage, loaded.fontAntialiasing,
                createDefaults, &config);
            loaded.widgets.push_back(config);
        }
    }
    bool valid = SUCCEEDED(result) && rootFound && !loaded.widgets.empty();
    if (valid) {
        std::vector<int> ids;
        for (size_t index = 0; index < loaded.widgets.size(); index++) {
            int id = loaded.widgets[index].id;
            if (id <= 0 || std::find(ids.begin(), ids.end(), id) != ids.end()) {
                valid = false;
                break;
            }
            ids.push_back(id);
        }
    }
    if (reader != nullptr) {
        reader->Release();
    }
    if (valid) {
        *snapshot = std::move(loaded);
    }
    return valid;
}

/// Loads and validates a settings XML file no larger than 4 MiB, leaving snapshot unchanged on failure.
bool ReadSettingsXml(const std::wstring& path, AppLanguage defaultLanguage, WidgetDefaultsFactory createDefaults,
        SettingsSnapshot* snapshot) {
    if (path.empty() || createDefaults == nullptr || snapshot == nullptr) {
        return false;
    }
    WIN32_FILE_ATTRIBUTE_DATA fileData = {};
    if (!GetFileAttributesExW(path.c_str(), GetFileExInfoStandard,
        &fileData) || fileData.nFileSizeHigh != 0 || fileData.nFileSizeLow > 4 * 1024 * 1024) {
        return false;
    }
    IStream* stream = nullptr;
    if (FAILED(SHCreateStreamOnFileEx(path.c_str(),
        STGM_READ | STGM_SHARE_DENY_WRITE, FILE_ATTRIBUTE_NORMAL, FALSE, nullptr, &stream))) {
        return false;
    }
    bool success = ReadSettingsXmlStream(stream, defaultLanguage, createDefaults, snapshot);
    stream->Release();
    return success;
}

/// Validates bounded clipboard XML and returns its widget configurations, leaving widgets unchanged on failure.
bool DeserializeWidgetClipboardData(const std::vector<BYTE>& data, AppLanguage defaultLanguage,
        WidgetDefaultsFactory createDefaults, std::vector<WidgetConfig>* widgets) {
    if (data.empty() || data.size() > MAX_WIDGET_CLIPBOARD_BYTES || createDefaults == nullptr || widgets == nullptr) {
        return false;
    }
    IStream* stream = SHCreateMemStream(data.data(), static_cast<UINT>(data.size()));
    if (stream == nullptr) {
        return false;
    }
    SettingsSnapshot snapshot;
    bool success = ReadSettingsXmlStream(stream, defaultLanguage, createDefaults, &snapshot);
    stream->Release();
    if (success) {
        *widgets = std::move(snapshot.widgets);
    }
    return success;
}

/// Overlays recognized registry values on an initialized widget configuration, validating or clamping bounded options.
static void ReadWidgetConfig(HKEY key, WidgetConfig* config) {
    DWORD value = 0;
    if (ReadDword(key, L"Id", &value)) {
        config->id = static_cast<int>(value);
    }
    if (ReadDword(key, L"Type", &value) && value < WIDGET_TYPE_COUNT) {
        config->type = static_cast<WidgetType>(value);
    }
    ReadString(key, L"Name", &config->name);
    if (ReadDword(key, L"Visible", &value)) {
        config->visible = value != 0;
    }
    if (ReadDword(key, L"TopMost", &value)) {
        config->topMost = value != 0;
    }
    if (ReadDword(key, L"ShowSeconds", &value)) {
        config->showSeconds = value != 0;
    }
    if (ReadDword(key, L"ShowUtc", &value)) {
        config->showUtc = value != 0;
    }
    if (ReadDword(key, L"ShowUtcText", &value)) {
        config->showUtcText = value != 0;
    }
    if (ReadDword(key, L"WidgetLanguage", &value) && value < LANG_COUNT) {
        config->language = static_cast<AppLanguage>(value);
    }
    ReadString(key, L"TimeZoneKey", &config->timeZoneKey);
    for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
        AdditionalClockConfig& clock = config->additionalClocks[index];
        std::wstring prefix = L"AdditionalClock" + std::to_wstring(index + 1);
        if (ReadDword(key, (prefix + L"Enabled").c_str(), &value)) {
            clock.enabled = value != 0;
        }
        ReadString(key, (prefix + L"Name").c_str(), &clock.name);
        ReadString(key, (prefix + L"TimeZoneKey").c_str(), &clock.timeZoneKey);
        if (ReadDword(key, (prefix + L"Size").c_str(), &value)) {
            clock.size = static_cast<int>(std::clamp<DWORD>(value, 48, 256));
        }
    }
    ReadString(key, L"MonitorDevices", &config->monitorDevices);
    if (ReadDword(key, L"BlackoutOtherMonitors", &value)) {
        config->blackoutOtherMonitors = value != 0;
    }
    ReadQword(key, L"OffsetMilliseconds", &config->offsetMilliseconds);
    if (ReadDword(key, L"X", &value)) {
        config->x = static_cast<int>(value);
    }
    if (ReadDword(key, L"Y", &value)) {
        config->y = static_cast<int>(value);
    }
    if (ReadDword(key, L"PreviewX", &value)) {
        config->previewX = static_cast<int>(value);
    }
    if (ReadDword(key, L"PreviewY", &value)) {
        config->previewY = static_cast<int>(value);
    }
    if (ReadDword(key, L"Size", &value)) {
        config->size = static_cast<int>(value);
    }
    if (ReadDword(key, L"Opacity", &value)) {
        config->opacity = std::clamp(static_cast<int>(value), WIDGET_OPACITY_MIN, WIDGET_OPACITY_MAX);
    }
    if (ReadDword(key, L"FontSize", &value)) {
        int minimumFontSize = config->type == WIDGET_FULLSCREEN ? FULLSCREEN_FONT_SIZE_MIN : DIGITAL_FONT_SIZE_MIN;
        int maximumFontSize = config->type == WIDGET_FULLSCREEN ? FULLSCREEN_FONT_SIZE_MAX : DIGITAL_FONT_SIZE_MAX;
        config->fontSize = std::clamp(static_cast<int>(value), minimumFontSize, maximumFontSize);
    }
    if (config->type == WIDGET_DIGITAL) {
        config->fontDialogSize = config->fontSize * 10;
    }
    if (ReadDword(key, L"FontDialogSize", &value)) {
        int savedSize = static_cast<int>(value);
        config->fontDialogSize = std::clamp(savedSize < 10 ? savedSize * 10 : savedSize, 10, 9990);
    }
    if (ReadDword(key, L"FontAntialiasing", &value) && value < FONT_ANTIALIAS_COUNT) {
        config->fontAntialiasing = static_cast<int>(value);
    }
    if (ReadDword(key, L"TimeFormat", &value) && value < TIME_FORMAT_COUNT) {
        config->timeFormat = static_cast<int>(value);
    }
    if (ReadDword(key, L"ShowAmPm", &value)) {
        config->showAmPm = value != 0;
    }
    if (ReadDword(key, L"LeadingZero", &value)) {
        config->leadingZeroMode = std::clamp(static_cast<int>(value), 0, LEADING_ZERO_MODE_COUNT - 1);
    }
    if (ReadDword(key, L"TransparentBackground", &value)) {
        config->transparentBackground = value != 0;
    }
    if (ReadDword(key, L"DisableThemes", &value)) {
        config->disableThemes = value != 0;
    }
    std::wstring defaultFontFace = config->fontFace;
    ReadString(key, L"FontFace", &config->fontFace);
    if (config->fontFace.empty()) {
        config->fontFace = defaultFontFace;
    }
    if (ReadDword(key, L"FontWeight", &value)) {
        config->fontWeight = std::clamp(static_cast<int>(value), 0, 1000);
    }
    if (ReadDword(key, L"FontItalic", &value)) {
        config->fontItalic = value != 0;
    }
    if (ReadDword(key, L"FontUnderline", &value)) {
        config->fontUnderline = value != 0;
    }
    if (ReadDword(key, L"FontStrikeOut", &value)) {
        config->fontStrikeOut = value != 0;
    }
    if (ReadDword(key, L"FontCharSet", &value)) {
        config->fontCharSet = static_cast<BYTE>(value);
    }
    config->panelTopFont = GetWidgetFontSelection(*config);
    config->panelTimeFont = config->panelTopFont;
    config->panelBottomFont = config->panelTopFont;
    ReadString(key, L"PanelTopFontFace", &config->panelTopFont.face);
    if (ReadDword(key, L"PanelTopFontSize", &value)) {
        config->panelTopFont.dialogSize = std::clamp(static_cast<int>(value), 10, 9990);
    }
    if (ReadDword(key, L"PanelTopFontWeight", &value)) {
        config->panelTopFont.weight = std::clamp(static_cast<int>(value), 0, 1000);
    }
    if (ReadDword(key, L"PanelTopFontItalic", &value)) {
        config->panelTopFont.italic = value != 0;
    }
    if (ReadDword(key, L"PanelTopFontUnderline", &value)) {
        config->panelTopFont.underline = value != 0;
    }
    if (ReadDword(key, L"PanelTopFontStrikeOut", &value)) {
        config->panelTopFont.strikeOut = value != 0;
    }
    if (ReadDword(key, L"PanelTopFontCharSet", &value)) {
        config->panelTopFont.charSet = static_cast<BYTE>(value);
    }
    ReadString(key, L"PanelTimeFontFace", &config->panelTimeFont.face);
    if (ReadDword(key, L"PanelTimeFontSize", &value)) {
        config->panelTimeFont.dialogSize = std::clamp(static_cast<int>(value), 10, 9990);
    }
    if (ReadDword(key, L"PanelTimeFontWeight", &value)) {
        config->panelTimeFont.weight = std::clamp(static_cast<int>(value), 0, 1000);
    }
    if (ReadDword(key, L"PanelTimeFontItalic", &value)) {
        config->panelTimeFont.italic = value != 0;
    }
    if (ReadDword(key, L"PanelTimeFontUnderline", &value)) {
        config->panelTimeFont.underline = value != 0;
    }
    if (ReadDword(key, L"PanelTimeFontStrikeOut", &value)) {
        config->panelTimeFont.strikeOut = value != 0;
    }
    if (ReadDword(key, L"PanelTimeFontCharSet", &value)) {
        config->panelTimeFont.charSet = static_cast<BYTE>(value);
    }
    ReadString(key, L"PanelBottomFontFace", &config->panelBottomFont.face);
    if (ReadDword(key, L"PanelBottomFontSize", &value)) {
        config->panelBottomFont.dialogSize = std::clamp(static_cast<int>(value), 10, 9990);
    }
    if (ReadDword(key, L"PanelBottomFontWeight", &value)) {
        config->panelBottomFont.weight = std::clamp(static_cast<int>(value), 0, 1000);
    }
    if (ReadDword(key, L"PanelBottomFontItalic", &value)) {
        config->panelBottomFont.italic = value != 0;
    }
    if (ReadDword(key, L"PanelBottomFontUnderline", &value)) {
        config->panelBottomFont.underline = value != 0;
    }
    if (ReadDword(key, L"PanelBottomFontStrikeOut", &value)) {
        config->panelBottomFont.strikeOut = value != 0;
    }
    if (ReadDword(key, L"PanelBottomFontCharSet", &value)) {
        config->panelBottomFont.charSet = static_cast<BYTE>(value);
    }
    if (ReadDword(key, L"Padding", &value)) {
        int maximumPadding = config->type == WIDGET_FULLSCREEN ? FULLSCREEN_PADDING_MAX : DIGITAL_PADDING_MAX;
        config->padding = std::clamp(static_cast<int>(value), 0, maximumPadding);
    }
    if (ReadDword(key, L"BorderStyle", &value)) {
        config->borderStyle = std::clamp(static_cast<int>(value), 0, DIGITAL_BORDER_STYLE_COUNT - 1);
    }
    if (ReadDword(key, L"BorderWidth", &value)) {
        config->borderWidth = std::clamp(static_cast<int>(value), 0, DIGITAL_BORDER_WIDTH_MAX);
    }
    if (ReadDword(key, L"BorderColor", &value)) {
        config->borderColor = static_cast<COLORREF>(value & 0xFFFFFF);
    }
    if (ReadDword(key, L"TextColor", &value)) {
        config->textColor = static_cast<COLORREF>(value);
    }
    if (ReadDword(key, L"BackgroundColor", &value)) {
        config->backgroundColor = static_cast<COLORREF>(value);
    }
    if (ReadDword(key, L"AlarmTextColor", &value)) {
        config->alarmTextColor = static_cast<COLORREF>(value);
    }
    if (ReadDword(key, L"AlarmBackgroundColor", &value)) {
        config->alarmBackgroundColor = static_cast<COLORREF>(value);
    }
    if (ReadDword(key, L"ShowToday", &value)) {
        config->showToday = value != 0;
    }
    if (ReadDword(key, L"WeekNumbers", &value)) {
        config->weekNumbers = value != 0;
    }
    if (ReadDword(key, L"SundayFirst", &value)) {
        config->sundayFirst = value != 0;
    }
    if (ReadDword(key, L"DateCopyFormat", &value) && value < DATE_FORMAT_COUNT) {
        config->dateCopyFormat = static_cast<int>(value);
    }
    if (ReadDword(key, L"TimeSignal", &value) && value < TIME_SIGNAL_COUNT) {
        config->timeSignal = static_cast<TimeSignalMode>(value);
    }
    if (ReadDword(key, L"SoundsMuted", &value)) {
        config->soundsMuted = value != 0;
    }
    if (ReadDword(key, L"AlarmEnabled", &value)) {
        config->alarmEnabled = value != 0;
    }
    if (ReadDword(key, L"AlarmDays", &value)) {
        config->alarmDays = value & ALARM_DAYS_ALL;
    }
    if (ReadDword(key, L"AlarmTimeSignal", &value)) {
        config->alarmTimeSignal = value != 0;
    }
    if (ReadDword(key, L"AlarmHour", &value) && value < 24) {
        config->alarmHour = static_cast<int>(value);
    }
    if (ReadDword(key, L"AlarmMinute", &value) && value < 60) {
        config->alarmMinute = static_cast<int>(value);
    }
    if (ReadDword(key, L"RunCommand", &value)) {
        config->runCommand = value != 0;
    }
    if (ReadDword(key, L"LoopAudio", &value)) {
        config->loopAudio = value != 0;
    }
    if (ReadDword(key, L"AlarmVolume", &value)) {
        config->alarmVolume = std::clamp(static_cast<int>(value), ALARM_VOLUME_MIN, ALARM_VOLUME_MAX);
    }
    ReadString(key, L"Command", &config->command);
    if (ReadDword(key, L"CallRemoteScript", &value)) {
        config->callRemoteScript = value != 0;
    }
    ReadString(key, L"RemoteScriptUrl", &config->remoteScriptUrl);
}

/// Writes one widget's settings to an open registry key and removes the obsolete frame value.
static void WriteWidgetConfig(HKEY key, const WidgetConfig& config) {
    RegDeleteValueW(key, L"ShowFrame");
    WriteDword(key, L"Id", config.id);
    WriteDword(key, L"Type", config.type);
    WriteString(key, L"Name", config.name);
    WriteDword(key, L"Visible", config.visible);
    WriteDword(key, L"TopMost", config.topMost);
    WriteDword(key, L"ShowSeconds", config.showSeconds);
    WriteDword(key, L"ShowUtc", config.showUtc);
    WriteDword(key, L"ShowUtcText", config.showUtcText);
    WriteDword(key, L"WidgetLanguage", config.language);
    WriteString(key, L"TimeZoneKey", config.timeZoneKey);
    for (int index = 0; index < ADDITIONAL_CLOCK_COUNT; index++) {
        const AdditionalClockConfig& clock = config.additionalClocks[index];
        std::wstring prefix = L"AdditionalClock" + std::to_wstring(index + 1);
        WriteDword(key, (prefix + L"Enabled").c_str(), clock.enabled);
        WriteString(key, (prefix + L"Name").c_str(), clock.name);
        WriteString(key, (prefix + L"TimeZoneKey").c_str(), clock.timeZoneKey);
        WriteDword(key, (prefix + L"Size").c_str(), clock.size);
    }
    WriteString(key, L"MonitorDevices", config.monitorDevices);
    WriteDword(key, L"BlackoutOtherMonitors", config.blackoutOtherMonitors);
    WriteQword(key, L"OffsetMilliseconds", config.offsetMilliseconds);
    WriteDword(key, L"X", config.x);
    WriteDword(key, L"Y", config.y);
    WriteDword(key, L"PreviewX", config.previewX);
    WriteDword(key, L"PreviewY", config.previewY);
    WriteDword(key, L"Size", config.size);
    WriteDword(key, L"Opacity", config.opacity);
    WriteDword(key, L"FontSize", config.fontSize);
    WriteDword(key, L"FontDialogSize", config.fontDialogSize);
    WriteDword(key, L"FontAntialiasing", config.fontAntialiasing);
    WriteDword(key, L"LeadingZero", config.leadingZeroMode);
    WriteDword(key, L"ShowAmPm", config.showAmPm);
    WriteDword(key, L"TimeFormat", config.timeFormat);
    WriteDword(key, L"TransparentBackground", config.transparentBackground);
    WriteDword(key, L"DisableThemes", config.disableThemes);
    WriteString(key, L"FontFace", config.fontFace);
    WriteDword(key, L"FontWeight", config.fontWeight);
    WriteDword(key, L"FontItalic", config.fontItalic);
    WriteDword(key, L"FontUnderline", config.fontUnderline);
    WriteDword(key, L"FontStrikeOut", config.fontStrikeOut);
    WriteDword(key, L"FontCharSet", config.fontCharSet);
    WriteString(key, L"PanelTopFontFace", config.panelTopFont.face);
    WriteDword(key, L"PanelTopFontSize", config.panelTopFont.dialogSize);
    WriteDword(key, L"PanelTopFontWeight", config.panelTopFont.weight);
    WriteDword(key, L"PanelTopFontItalic", config.panelTopFont.italic);
    WriteDword(key, L"PanelTopFontUnderline", config.panelTopFont.underline);
    WriteDword(key, L"PanelTopFontStrikeOut", config.panelTopFont.strikeOut);
    WriteDword(key, L"PanelTopFontCharSet", config.panelTopFont.charSet);
    WriteString(key, L"PanelTimeFontFace", config.panelTimeFont.face);
    WriteDword(key, L"PanelTimeFontSize", config.panelTimeFont.dialogSize);
    WriteDword(key, L"PanelTimeFontWeight", config.panelTimeFont.weight);
    WriteDword(key, L"PanelTimeFontItalic", config.panelTimeFont.italic);
    WriteDword(key, L"PanelTimeFontUnderline", config.panelTimeFont.underline);
    WriteDword(key, L"PanelTimeFontStrikeOut", config.panelTimeFont.strikeOut);
    WriteDword(key, L"PanelTimeFontCharSet", config.panelTimeFont.charSet);
    WriteString(key, L"PanelBottomFontFace", config.panelBottomFont.face);
    WriteDword(key, L"PanelBottomFontSize", config.panelBottomFont.dialogSize);
    WriteDword(key, L"PanelBottomFontWeight", config.panelBottomFont.weight);
    WriteDword(key, L"PanelBottomFontItalic", config.panelBottomFont.italic);
    WriteDword(key, L"PanelBottomFontUnderline", config.panelBottomFont.underline);
    WriteDword(key, L"PanelBottomFontStrikeOut", config.panelBottomFont.strikeOut);
    WriteDword(key, L"PanelBottomFontCharSet", config.panelBottomFont.charSet);
    WriteDword(key, L"Padding", config.padding);
    WriteDword(key, L"BorderStyle", config.borderStyle);
    WriteDword(key, L"BorderWidth", config.borderWidth);
    WriteDword(key, L"BorderColor", config.borderColor);
    WriteDword(key, L"TextColor", config.textColor);
    WriteDword(key, L"BackgroundColor", config.backgroundColor);
    WriteDword(key, L"AlarmTextColor", config.alarmTextColor);
    WriteDword(key, L"AlarmBackgroundColor", config.alarmBackgroundColor);
    WriteDword(key, L"ShowToday", config.showToday);
    WriteDword(key, L"WeekNumbers", config.weekNumbers);
    WriteDword(key, L"SundayFirst", config.sundayFirst);
    WriteDword(key, L"DateCopyFormat", config.dateCopyFormat);
    WriteDword(key, L"TimeSignal", config.timeSignal);
    WriteDword(key, L"SoundsMuted", config.soundsMuted);
    WriteDword(key, L"AlarmEnabled", config.alarmEnabled);
    WriteDword(key, L"AlarmDays", config.alarmDays);
    WriteDword(key, L"AlarmTimeSignal", config.alarmTimeSignal);
    WriteDword(key, L"AlarmHour", config.alarmHour);
    WriteDword(key, L"AlarmMinute", config.alarmMinute);
    WriteDword(key, L"RunCommand", config.runCommand);
    WriteDword(key, L"LoopAudio", config.loopAudio);
    WriteDword(key, L"AlarmVolume", static_cast<DWORD>(config.alarmVolume));
    WriteString(key, L"Command", config.command);
    WriteDword(key, L"CallRemoteScript", config.callRemoteScript);
    WriteString(key, L"RemoteScriptUrl", config.remoteScriptUrl);
}

/// Recognizes numeric widget subkeys outside the saved collection, including indices too large to represent.
static bool IsObsoleteWidgetRegistryKey(const wchar_t* name, size_t widgetCount) {
    if (name == nullptr || name[0] == L'\0') {
        return false;
    }
    size_t index = 0;
    for (const wchar_t* character = name; *character != L'\0'; character++) {
        if (!iswdigit(*character)) {
            return false;
        }
        size_t digit = static_cast<size_t>(*character - L'0');
        if (index > (SIZE_MAX - digit) / 10) {
            return true;
        }
        index = index * 10 + digit;
    }
    return index >= widgetCount;
}

/// Deletes numeric widget subkeys beyond the saved count while preserving unrelated subkeys.
static void RemoveObsoleteWidgetRegistryKeys(HKEY collection, size_t widgetCount) {
    std::vector<std::wstring> obsoleteKeys;
    for (DWORD keyIndex = 0;; keyIndex++) {
        wchar_t name[256] = {};
        DWORD nameLength = ARRAYSIZE(name);
        LSTATUS result = RegEnumKeyExW(collection, keyIndex, name, &nameLength, nullptr, nullptr, nullptr, nullptr);
        if (result == ERROR_NO_MORE_ITEMS) {
            break;
        }
        if (result != ERROR_SUCCESS) {
            break;
        }
        if (IsObsoleteWidgetRegistryKey(name, widgetCount)) {
            obsoleteKeys.push_back(name);
        }
    }
    for (size_t index = 0; index < obsoleteKeys.size(); index++) {
        RegDeleteTreeW(collection, obsoleteKeys[index].c_str());
    }
}

/// Loads per-user settings using supplied defaults and a widget-default factory, including the older single-widget
/// layout.
/// Returns false if arguments are invalid or the settings root cannot be opened.
bool ReadRegistrySettings(const SettingsSnapshot& defaults, WidgetDefaultsFactory createDefaults,
        SettingsSnapshot* snapshot) {
    if (createDefaults == nullptr || snapshot == nullptr) {
        return false;
    }
    HKEY root = nullptr;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, REGISTRY_PATH, 0, KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS, &root) !=
            ERROR_SUCCESS) {
        return false;
    }
    SettingsSnapshot loaded = defaults;
    loaded.widgets.clear();
    DWORD value = 0;
    if (ReadDword(root, L"Language", &value) && value < LANG_COUNT) {
        loaded.language = static_cast<AppLanguage>(value);
    }
    if (ReadDword(root, L"DisableThemes", &value)) {
        loaded.themesDisabled = value != 0;
    } else if (ReadDword(root, L"VisualStyles", &value)) {
        loaded.themesDisabled = value == 0;
    }
    if (ReadDword(root, L"GeneratedTimeSignal", &value)) {
        loaded.generatedTimeSignal = value == 0;
    }
    double volume = 0.0;
    if (ReadTimeSignalVolume(root, &volume)) {
        loaded.timeSignalVolume = std::clamp<double>(volume, TIME_SIGNAL_VOLUME_MIN, TIME_SIGNAL_VOLUME_MAX);
    }
    if (ReadDword(root, L"SnapWidgetsToWorkArea", &value)) {
        loaded.snapWidgetsToWorkArea = value != 0;
    }
    if (ReadDword(root, L"FontAntialiasing", &value) && value < FONT_ANTIALIAS_COUNT) {
        loaded.fontAntialiasing = static_cast<int>(value);
    }
    ReadString(root, L"FontFace", &loaded.fontFace);
    if (loaded.fontFace.size() >= LF_FACESIZE) {
        loaded.fontFace.clear();
    }
    if (ReadDword(root, L"FontDialogSize", &value)) {
        int savedSize = static_cast<int>(value);
        loaded.fontDialogSize = std::clamp(savedSize < 10 ? savedSize * 10 : savedSize, 10, 9990);
    }
    if (ReadDword(root, L"FontWeight", &value)) {
        loaded.fontWeight = std::clamp(static_cast<int>(value), 0, 1000);
    }
    if (ReadDword(root, L"FontItalic", &value)) {
        loaded.fontItalic = value != 0;
    }
    if (ReadDword(root, L"UseNtpTime", &value)) {
        loaded.useNtpTime = value != 0;
    }
    if (ReadDword(root, L"NtpPreset", &value) && value < NTP_PRESET_COUNT) {
        loaded.ntpPreset = static_cast<int>(value);
    }
    ReadString(root, L"NtpServers", &loaded.ntpServers);
    if (ReadDword(root, L"SettingsX", &value)) {
        loaded.settingsX = static_cast<int>(value);
    }
    if (ReadDword(root, L"SettingsY", &value)) {
        loaded.settingsY = static_cast<int>(value);
    }
    if (ReadDword(root, L"SettingsTab", &value) && value < SETTINGS_TAB_COUNT) {
        loaded.settingsTab = static_cast<int>(value);
    }
    if (ReadDword(root, L"LastAddedWidgetType", &value) && value < WIDGET_TYPE_COUNT) {
        loaded.lastAddedWidgetType = static_cast<WidgetType>(value);
    }
    if (ReadDword(root, L"HelpX", &value)) {
        loaded.helpX = static_cast<int>(value);
    }
    if (ReadDword(root, L"HelpY", &value)) {
        loaded.helpY = static_cast<int>(value);
    }
    if (ReadDword(root, L"AboutX", &value)) {
        loaded.aboutX = static_cast<int>(value);
    }
    if (ReadDword(root, L"AboutY", &value)) {
        loaded.aboutY = static_cast<int>(value);
    }
    HKEY collection = nullptr;
    DWORD count = 0;
    if (RegOpenKeyExW(root, L"Widgets", 0, KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS, &collection) == ERROR_SUCCESS
            && ReadDword(collection, L"Count", &count)) {
        count = std::min<DWORD>(count, MAX_WIDGET_COUNT);
        for (DWORD index = 0; index < count; index++) {
            wchar_t subkey[24] = {};
            swprintf_s(subkey, L"%u", index);
            HKEY item = nullptr;
            if (RegOpenKeyExW(collection, subkey, 0, KEY_QUERY_VALUE, &item) == ERROR_SUCCESS) {
                WidgetConfig config = createDefaults(WIDGET_ANALOG, static_cast<int>(index), loaded.language,
                    loaded.fontAntialiasing);
                ReadWidgetConfig(item, &config);
                loaded.widgets.push_back(config);
                RegCloseKey(item);
            }
        }
        RegCloseKey(collection);
    }
    if (loaded.widgets.empty()) {
        WidgetConfig config = createDefaults(WIDGET_ANALOG, 0, loaded.language, loaded.fontAntialiasing);
        if (ReadDword(root, L"ClockSize", &value)) {
            config.size = static_cast<int>(value);
        }
        if (ReadDword(root, L"ShowSeconds", &value)) {
            config.showSeconds = value != 0;
        }
        if (ReadDword(root, L"ShowUtc", &value)) {
            config.showUtc = value != 0;
        }
        if (ReadDword(root, L"AlwaysOnTop", &value)) {
            config.topMost = value != 0;
        }
        if (ReadDword(root, L"ClockVisible", &value)) {
            config.visible = value != 0;
        }
        if (ReadDword(root, L"PopupX", &value)) {
            config.x = static_cast<int>(value);
        }
        if (ReadDword(root, L"PopupY", &value)) {
            config.y = static_cast<int>(value);
        }
        if (ReadDword(root, L"AlarmEnabled", &value)) {
            config.alarmEnabled = value != 0;
        }
        if (ReadDword(root, L"AlarmHour", &value)) {
            config.alarmHour = static_cast<int>(value);
        }
        if (ReadDword(root, L"AlarmMinute", &value)) {
            config.alarmMinute = static_cast<int>(value);
        }
        if (ReadDword(root, L"AlarmRunCommand", &value)) {
            config.runCommand = value != 0;
        }
        if (ReadDword(root, L"AlarmLoopAudio", &value)) {
            config.loopAudio = value != 0;
        }
        ReadQword(root, L"ClockOffsetMilliseconds", &config.offsetMilliseconds);
        ReadString(root, L"TimeZoneKey", &config.timeZoneKey);
        ReadString(root, L"AlarmCommand", &config.command);
        loaded.widgets.push_back(config);
    }
    RegCloseKey(root);
    *snapshot = std::move(loaded);
    return true;
}

/// Writes global settings and widget subkeys, removes obsolete widget keys, and deletes automatic XML after success.
/// Reports key-creation failures; individual value writes do not return status.
bool WriteRegistrySettings(const SettingsSnapshot& snapshot) {
    if (snapshot.widgets.size() > MAX_WIDGET_COUNT) {
        return false;
    }
    HKEY root = nullptr;
    DWORD disposition = 0;
    if (RegCreateKeyExW(HKEY_CURRENT_USER, REGISTRY_PATH, 0, nullptr, 0,
        KEY_SET_VALUE | KEY_CREATE_SUB_KEY, nullptr, &root, &disposition) != ERROR_SUCCESS) {
        return false;
    }
    WriteDword(root, L"SchemaVersion", 15);
    WriteDword(root, L"Language", snapshot.language);
    WriteDword(root, L"DisableThemes", snapshot.themesDisabled);
    WriteDword(root, L"VisualStyles", !snapshot.themesDisabled);
    WriteDword(root, L"GeneratedTimeSignal", snapshot.generatedTimeSignal ? 0 : 1);
    WriteTimeSignalVolume(root, snapshot.timeSignalVolume);
    WriteDword(root, L"SnapWidgetsToWorkArea", snapshot.snapWidgetsToWorkArea);
    WriteDword(root, L"FontAntialiasing", snapshot.fontAntialiasing);
    WriteString(root, L"FontFace", snapshot.fontFace);
    WriteDword(root, L"FontDialogSize", snapshot.fontDialogSize);
    WriteDword(root, L"FontWeight", snapshot.fontWeight);
    WriteDword(root, L"FontItalic", snapshot.fontItalic);
    WriteDword(root, L"UseNtpTime", snapshot.useNtpTime);
    WriteDword(root, L"NtpPreset", snapshot.ntpPreset);
    WriteString(root, L"NtpServers", snapshot.ntpServers);
    WriteDword(root, L"SettingsX", snapshot.settingsX);
    WriteDword(root, L"SettingsY", snapshot.settingsY);
    WriteDword(root, L"SettingsTab", snapshot.settingsTab);
    WriteDword(root, L"LastAddedWidgetType", snapshot.lastAddedWidgetType);
    WriteDword(root, L"HelpX", snapshot.helpX);
    WriteDword(root, L"HelpY", snapshot.helpY);
    WriteDword(root, L"AboutX", snapshot.aboutX);
    WriteDword(root, L"AboutY", snapshot.aboutY);
    bool written = false;
    HKEY collection = nullptr;
    REGSAM collectionAccess = KEY_SET_VALUE | KEY_QUERY_VALUE | KEY_CREATE_SUB_KEY | KEY_ENUMERATE_SUB_KEYS | DELETE;
    if (RegCreateKeyExW(root, L"Widgets", 0, nullptr, 0, collectionAccess, nullptr, &collection, &disposition) ==
            ERROR_SUCCESS) {
        WriteDword(collection, L"Count", static_cast<DWORD>(snapshot.widgets.size()));
        written = true;
        for (size_t index = 0; index < snapshot.widgets.size(); index++) {
            wchar_t subkey[24] = {};
            swprintf_s(subkey, L"%zu", index);
            HKEY item = nullptr;
            if (RegCreateKeyExW(collection, subkey, 0, nullptr, 0, KEY_SET_VALUE, nullptr, &item, &disposition) ==
                    ERROR_SUCCESS) {
                WriteWidgetConfig(item, snapshot.widgets[index]);
                RegCloseKey(item);
            } else {
                written = false;
            }
        }
        RemoveObsoleteWidgetRegistryKeys(collection, snapshot.widgets.size());
        RegCloseKey(collection);
    }
    RegCloseKey(root);
    if (written) {
        RemoveAutomaticXmlSettings();
    }
    return written;
}

/// Deletes CalClock's per-user settings tree and attempts to remove the empty vendor key.
void RemoveRegistrySettings() {
    RegDeleteTreeW(HKEY_CURRENT_USER, REGISTRY_PATH);
    RegDeleteKeyW(HKEY_CURRENT_USER, VENDOR_REGISTRY_PATH);
}
