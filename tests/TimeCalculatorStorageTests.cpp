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
 * Last modified for version 1.7.2.2
 */

#include "../CalClock/SettingsStorage.cpp"
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>

/// Supplies an unrelated widget-caption dependency without linking the application UI.
std::wstring DefaultAdditionalClockName(AppLanguage language, int index) {
    UNREFERENCED_PARAMETER(language);
    UNREFERENCED_PARAMETER(index);
    return L"Clock";
}

/// Stops a failed scenario while allowing the caller to remove its isolated registry key.
static void Require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

/// Creates a valid widget so calculator storage is exercised through the complete XML snapshot.
static WidgetConfig Defaults(WidgetType type, int index, AppLanguage language, int antialiasing) {
    WidgetConfig config;
    config.id = index + 1;
    config.type = type;
    config.language = language;
    config.fontAntialiasing = antialiasing;
    return config;
}

/// Parses known test inputs through the production storage parser.
static SYSTEMTIME Time(const wchar_t* text) {
    SYSTEMTIME time = {};
    Require(ParseCalculatorTime(text, &time), "test date parses");
    return time;
}

/// Writes and reads settings in memory, including user data only for an explicit export.
static SettingsSnapshot RoundTrip(const SettingsSnapshot& original,
        const std::vector<TimeCalculatorPreset>* exported = nullptr,
        std::vector<TimeCalculatorPreset>* imported = nullptr) {
    IStream* stream = SHCreateMemStream(nullptr, 0);
    Require(stream != nullptr, "memory stream");
    bool written = WriteSettingsXmlStream(stream, original, exported);
    LARGE_INTEGER beginning = {};
    HRESULT seek = stream->Seek(beginning, STREAM_SEEK_SET, nullptr);
    SettingsSnapshot loaded;
    bool read = written
        && SUCCEEDED(seek)
        && ReadSettingsXmlStream(stream, LANG_EN_US, Defaults, &loaded, imported);
    stream->Release();
    Require(read, "XML round trip");
    return loaded;
}

/// Reads deliberately malformed or older XML documents through the actual import implementation.
static bool ReadText(const char* text, SettingsSnapshot* result = nullptr) {
    IStream* stream = SHCreateMemStream(reinterpret_cast<const BYTE*>(text), static_cast<UINT>(strlen(text)));
    SettingsSnapshot loaded;
    std::vector<TimeCalculatorPreset> presets;
    bool presetsOnly = false;
    bool read = ReadSettingsXmlStream(stream, LANG_EN_US, Defaults, &loaded, &presets, &presetsOnly);
    stream->Release();
    if (read && result != nullptr) {
        *result = std::move(loaded);
    }
    return read;
}

/// Inspects the exported XML structure independently of the production reader.
static std::string ExportText(const SettingsSnapshot& settings,
        const std::vector<TimeCalculatorPreset>* presets) {
    IStream* stream = SHCreateMemStream(nullptr, 0);
    Require(stream != nullptr, "export inspection memory stream");
    Require(WriteSettingsXmlStream(stream, settings, presets), "export inspection write");
    STATSTG information = {};
    Require(SUCCEEDED(stream->Stat(&information, STATFLAG_NONAME)), "export inspection size");
    LARGE_INTEGER start = {};
    Require(SUCCEEDED(stream->Seek(start, STREAM_SEEK_SET, nullptr)), "export inspection rewind");
    std::string text(information.cbSize.LowPart, '\0');
    ULONG read = 0;
    Require(SUCCEEDED(stream->Read(text.data(),
        static_cast<ULONG>(text.size()), &read)) && read == text.size(), "export inspection read");
    stream->Release();
    return text;
}

/// Compares user records without normalizing case, accents or surrounding whitespace.
static bool SamePresets(const std::vector<TimeCalculatorPreset>& first,
        const std::vector<TimeCalculatorPreset>& second) {
    if (first.size() != second.size()) {
        return false;
    }
    for (size_t index = 0; index < first.size(); index++) {
        if (FormatCalculatorTime(first[index].time) != FormatCalculatorTime(second[index].time)
                || first[index].description != second[index].description
                || first[index].zone != second[index].zone) {
            return false;
        }
    }
    return true;
}

/// Verifies all rule masks, missing settings and malformed imports using only isolated storage.
static void TestHighlightStorage(HKEY key, const SettingsSnapshot& original) {
    SettingsSnapshot candidate = original;
    std::vector<DWORD> masks{
        DWORD{ 0 },
        TIME_CALCULATOR_DEFAULT_HIGHLIGHTS,
        TIME_CALCULATOR_ALL_HIGHLIGHTS
    };
    for (DWORD flag = 1; flag <= CALCULATOR_HIGHLIGHT_NINES; flag <<= 1) {
        masks.push_back(flag);
    }
    for (DWORD mask : masks) {
        candidate.calculator.highlights = mask;
        candidate.calculator.tab = 3;
        SettingsSnapshot loaded = RoundTrip(candidate);
        Require(loaded.calculator.highlights == mask && loaded.calculator.tab == 3,
            "XML retains each independent highlight switch, all switches and the empty selection");
        Require(WriteCalculatorRegistry(key, candidate), "isolated highlight registry write");
        loaded = SettingsSnapshot{};
        ReadCalculatorRegistry(key, &loaded);
        Require(loaded.calculator.highlights == mask && loaded.calculator.tab == 3,
            "registry retains each independent highlight switch, all switches and the empty selection");
    }
    SettingsSnapshot loaded;
    Require(ReadText("<CalClockSettings version='1'><Calculator/><Widget id='1'/></CalClockSettings>",
        &loaded) && loaded.calculator.highlights == TIME_CALCULATOR_DEFAULT_HIGHLIGHTS,
        "missing XML highlight choices use the new defaults");
    Require(ReadText("<CalClockSettings version='1'><Calculator highlights='0'/>"
        "<Widget id='1'/></CalClockSettings>", &loaded) && loaded.calculator.highlights == 0,
        "explicit zero XML mask differs from a missing choice");
    const char* invalid[] = { "-1", "8192", "4294967295", "text", "" };
    for (const char* value : invalid) {
        std::string xml = "<CalClockSettings version='1'><Calculator highlights='";
        xml += value;
        xml += "'/><Widget id='1'/></CalClockSettings>";
        Require(!ReadText(xml.c_str()), "XML rejects unknown rule bits and malformed masks");
    }
    HKEY calculator = nullptr;
    Require(RegOpenKeyExW(key, L"Calculator", 0, KEY_SET_VALUE, &calculator) == ERROR_SUCCESS,
        "open isolated calculator branch for missing-value coverage");
    Require(RegDeleteValueW(calculator, L"Highlights") == ERROR_SUCCESS,
        "remove only isolated highlight choice");
    loaded = SettingsSnapshot{};
    ReadCalculatorRegistry(key, &loaded);
    Require(loaded.calculator.highlights == TIME_CALCULATOR_DEFAULT_HIGHLIGHTS,
        "missing registry choice uses the same defaults as missing XML choice");
    DWORD invalidMask = 0x2000;
    Require(RegSetValueExW(calculator, L"Highlights", 0, REG_DWORD, reinterpret_cast<const BYTE*>(
        &invalidMask), sizeof(invalidMask)) == ERROR_SUCCESS, "write isolated unsupported rule mask");
    RegCloseKey(calculator);
    loaded = SettingsSnapshot{};
    ReadCalculatorRegistry(key, &loaded);
    Require(loaded.calculator.highlights == TIME_CALCULATOR_DEFAULT_HIGHLIGHTS,
        "registry ignores unsupported rule bits instead of applying them");
    Require(WriteCalculatorRegistry(key, original), "restore isolated calculator fixture");
}

/// Verifies both storage backends preserve an unset Today date and leave fixed dates unchanged.
static void TestCalendarDateStorage(HKEY key, const SettingsSnapshot& original) {
    for (const SYSTEMTIME& day : { SYSTEMTIME{}, Time(L"2027-01-03T00:00:00.000Z") }) {
        SettingsSnapshot candidate = original;
        candidate.calculator.day = day;
        SettingsSnapshot loaded = RoundTrip(candidate);
        Require(FormatCalculatorTime(loaded.calculator.day) == FormatCalculatorTime(day),
            "XML preserves Today following separately from a fixed calendar date");
        Require(WriteCalculatorRegistry(key, candidate), "isolated calendar date registry write");
        loaded = SettingsSnapshot{};
        ReadCalculatorRegistry(key, &loaded);
        Require(FormatCalculatorTime(loaded.calculator.day) == FormatCalculatorTime(day),
            "registry preserves Today following separately from a fixed calendar date");
    }
    Require(WriteCalculatorRegistry(key, original), "restore isolated calculator date fixture");
}

/// Replaces an isolated fixture with exact bytes, including optional BOMs and malformed documents.
static void WriteImportFixture(const std::wstring& path, const std::string& text) {
    HANDLE file = CreateFileW(path.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, 0, nullptr);
    Require(file != INVALID_HANDLE_VALUE, "create isolated import fixture");
    DWORD written = 0;
    BOOL saved = WriteFile(file, text.data(), static_cast<DWORD>(text.size()), &written, nullptr);
    CloseHandle(file);
    Require(saved && written == text.size(), "write complete isolated import fixture");
}

/// Verifies that both UTF-16 byte orders reach the XML reader and preserve the stored Unicode text and instant.
static void TestUtf16PresetImports(const std::wstring& path, const DYNAMIC_TIME_ZONE_INFORMATION& zone) {
    const std::wstring xml = L"<?xml version='1.0' encoding='UTF-16'?>"
        L"<TimeCalculatorPresets version='2'><Preset time='2026-01-15T06:49:56.000Z' "
        L"zone='UTC+05:45' description='Žluťoučký'/></TimeCalculatorPresets>";
    const bool byteOrders[] = { false, true };
    for (bool bigEndian : byteOrders) {
        std::string bytes = "\xFF\xFE";
        if (bigEndian) {
            bytes = "\xFE\xFF";
        }
        for (wchar_t character : xml) {
            char low = static_cast<char>(character & 0xFF);
            char high = static_cast<char>(character >> 8);
            if (bigEndian) {
                bytes += high;
                bytes += low;
            } else {
                bytes += low;
                bytes += high;
            }
        }
        WriteImportFixture(path, bytes);
        std::vector<TimeCalculatorPreset> loaded;
        Require(ReadCalculatorPresetImport(path, zone, zone.TimeZoneKeyName, &loaded),
            "UTF-16 XML imports in either byte order");
        Require(loaded.size() == 1 && loaded[0].description == L"Žluťoučký"
            && loaded[0].zone == L"UTC+05:45"
            && FormatCalculatorTime(loaded[0].time) == L"2026-01-15T06:49:56.000Z",
            "UTF-16 import preserves Unicode text, the display zone and the exact UTC instant");
    }
}

/// Verifies extraction without applying settings, legacy locale dates, BOMs, exact text and DST validation.
static void TestPresetImports(const std::wstring& path, const SettingsSnapshot& settings,
        const std::vector<TimeCalculatorPreset>& record) {
    std::vector<DYNAMIC_TIME_ZONE_INFORMATION> zones;
    LoadTimeZoneList(&zones);
    const DYNAMIC_TIME_ZONE_INFORMATION* prague = nullptr;
    const DYNAMIC_TIME_ZONE_INFORMATION* fixed = nullptr;
    for (const DYNAMIC_TIME_ZONE_INFORMATION& zone : zones) {
        if (wcscmp(zone.TimeZoneKeyName, L"Central Europe Standard Time") == 0) {
            prague = &zone;
        }
        if (wcscmp(zone.TimeZoneKeyName, L"UTC+05:45") == 0) {
            fixed = &zone;
        }
    }
    Require(prague != nullptr && fixed != nullptr, "named and fixed-offset import zones available");
    TestUtf16PresetImports(path, *prague);
    std::vector<TimeCalculatorPreset> loaded;
    WriteImportFixture(path, ExportText(settings, &record));
    Require(!ReadCalculatorPresets(path, &loaded), "automatic user-data reader remains standalone-only");
    Require(ReadCalculatorPresetImport(path, *prague, prague->TimeZoneKeyName, &loaded)
        && SamePresets(record, loaded), "preset import extracts only values from a combined settings export");
    WriteImportFixture(path, ExportText(settings, nullptr));
    Require(ReadCalculatorPresetImport(path, *prague, prague->TimeZoneKeyName, &loaded) && loaded.empty(),
        "settings without saved user data import no values");
    const std::string legacy = "\r\n   \r\ninvalid\tSkipped\r\nmissing separator\r\n"
        "2026-01-15 12:34:56\t  Winter & <event>  \textra field\r\n"
        "2026-07-15 12:34:56\tSummer\n"
        "2026-01-15 12:34:56\t";
    for (bool bom : { false, true }) {
        WriteImportFixture(path, (bom ? "\xEF\xBB\xBF" : "") + legacy);
        Require(ReadCalculatorPresetImport(path, *prague, prague->TimeZoneKeyName, &loaded)
            && loaded.size() == 3, "legacy import accepts UTF-8 with/without BOM and skips invalid rows");
        Require(FormatCalculatorTime(loaded[0].time) == L"2026-01-15T11:34:56.000Z"
            && FormatCalculatorTime(loaded[1].time) == L"2026-07-15T10:34:56.000Z",
            "legacy import applies the selected named zone and the date's daylight saving rules");
        Require(loaded[0].description == L"  Winter & <event>  " && loaded[2].description.empty(),
            "legacy parser keeps exactly the second tab-separated field, including whitespace and emptiness");
        Require(loaded[0].zone == prague->TimeZoneKeyName, "legacy import retains the selected display zone");
        Require(ReadCalculatorPresetImport(path, *fixed, fixed->TimeZoneKeyName, &loaded)
            && FormatCalculatorTime(loaded[0].time) == L"2026-01-15T06:49:56.000Z",
            "legacy import honors a selected fixed UTC offset");
    }
    const std::vector<TimeCalculatorPreset> before = loaded;
    const char* const invalidImports[] = {
        "<TimeCalculatorPresets version='2'><Preset time='broken'/></TimeCalculatorPresets>",
        "<CalClockExport version='1'><TimeCalculatorPresets version='2'/><TimeCalculatorPresets version='2'/>"
        "</CalClockExport>",
        "<CalClockExport version='1'><TimeCalculatorPresets version='2'/>",
        "2026-03-29 02:30:00\tNonexistent time",
        "2026-10-25 02:30:00\tAmbiguous time",
        "2026-01-15 12:34:56\t\xFF"
    };
    for (const char* text : invalidImports) {
        WriteImportFixture(path, text);
        Require(!ReadCalculatorPresetImport(path, *prague, prague->TimeZoneKeyName, &loaded)
            && SamePresets(before, loaded), "invalid or unresolved imports leave existing values untouched");
    }
}

/// Exercises independent user XML, explicit exports and window settings using isolated storage only.
int wmain() {
    HKEY key = nullptr;
    HANDLE locked = INVALID_HANDLE_VALUE;
    std::wstring path;
    std::wstring testKey = L"Software\\CalClockCalculatorStorageTests-"
        + std::to_wstring(GetCurrentProcessId()) + L"-" + std::to_wstring(GetTickCount64());
    try {
        wchar_t temporary[MAX_PATH] = {};
        wchar_t file[MAX_PATH] = {};
        Require(GetTempPathW(ARRAYSIZE(temporary), temporary) != 0, "temporary directory");
        Require(GetTempFileNameW(temporary, L"CCT", 0, file) != 0, "isolated user-data file");
        path = file;
        DeleteFileW(path.c_str());
        SettingsSnapshot original;
        original.widgets.push_back(Defaults(WIDGET_PANEL, 0, LANG_EN_US, FONT_ANTIALIAS_GDI));
        original.calculator.from = Time(L"2024-02-29T23:59:00.000Z");
        original.calculator.to = Time(L"2026-11-03T15:13:00.000Z");
        original.calculator.start = Time(L"1601-01-01T00:00:00.000Z");
        original.calculator.day = Time(L"9999-12-31T23:59:00.000Z");
        original.calculator.fromZone = L"Central Europe Standard Time";
        original.calculator.toZone = L"UTC+05:45";
        original.calculator.fromNow = true;
        original.calculator.tab = 3;
        original.calculator.highlights = CALCULATOR_HIGHLIGHT_SIXES | CALCULATOR_HIGHLIGHT_NINES;
        original.calculatorWindowState.x = -123;
        original.calculatorWindowState.y = 456;
        std::vector<TimeCalculatorPreset> presets;
        presets.push_back(TimeCalculatorPreset{
            original.calculator.from, L"Příliš žluťoučký & <tag> \"quoted\"\n\t\U0001F600" });
        presets.push_back(TimeCalculatorPreset{ original.calculator.from, L"  whitespace\t  " });
        presets.push_back(TimeCalculatorPreset{ original.calculator.to, L"" });
        presets.push_back(TimeCalculatorPreset{ Time(L"2026-11-03T15:13:05.123Z"), L"Exact timestamp" });
        presets[0].zone = L"Central Europe Standard Time";
        presets[1].zone = L"UTC-03:30";
        std::string fullExport = ExportText(original, &presets);
        Require(fullExport.starts_with("\xEF\xBB\xBF"), "combined export includes the UTF-8 BOM");
        Require(ReadText(fullExport.c_str()) && ReadText(fullExport.c_str() + 3),
            "combined export imports with or without a BOM");
        size_t settingsEnd = fullExport.find("</CalClockSettings>");
        size_t userData = fullExport.find("<TimeCalculatorPresets");
        Require(fullExport.find("<CalClockExport") < fullExport.find("<CalClockSettings")
            && settingsEnd != std::string::npos
            && settingsEnd < userData
            && userData < fullExport.find("</CalClockExport>"),
            "export keeps settings and user data in separate sibling elements");
        Require(fullExport.find("2026-11-03T15:13:05.123Z") != std::string::npos,
            "user timestamps explicitly identify UTC with Z");
        std::string settingsOnly = ExportText(original, nullptr);
        Require(settingsOnly.starts_with("\xEF\xBB\xBF"), "settings XML includes the UTF-8 BOM");
        Require(ReadText(settingsOnly.c_str()) && ReadText(settingsOnly.c_str() + 3),
            "settings XML imports with or without a BOM");
        Require(settingsOnly.find("<CalClockExport") == std::string::npos
            && settingsOnly.find("<TimeCalculatorPresets") == std::string::npos
            && settingsOnly.find("<CalClockSettings") != std::string::npos,
            "settings-only document keeps the original settings root");
        const std::vector<TimeCalculatorPreset> emptyPresets;
        Require(ExportText(original, &emptyPresets) == settingsOnly,
            "export without saved user data needs no extra root");
        std::vector<TimeCalculatorPreset> loadedPresets = presets;
        Require(ReadCalculatorPresets(path, &loadedPresets) && loadedPresets.empty(),
            "missing user file is empty");
        Require(WriteCalculatorPresets(path, presets), "write independent user XML");
        std::string userXml;
        {
            std::ifstream input(path.c_str(), std::ios::binary);
            Require(input.is_open(), "open saved user XML for encoding inspection");
            userXml.assign(std::istreambuf_iterator<char>{ input }, std::istreambuf_iterator<char>{});
            Require(!input.bad(), "read saved user XML bytes");
        }
        Require(userXml.starts_with("\xEF\xBB\xBF"), "user XML includes the UTF-8 BOM");
        Require(ReadText(userXml.c_str()) && ReadText(userXml.c_str() + 3),
            "standalone user XML imports with or without a BOM");
        {
            std::ofstream output(path.c_str(), std::ios::binary | std::ios::trunc);
            output.write(userXml.data() + 3, static_cast<std::streamsize>(userXml.size() - 3));
            output.close();
            Require(!output.fail(), "save a user XML fixture without a BOM");
        }
        Require(ReadCalculatorPresets(path, &loadedPresets) && SamePresets(presets, loadedPresets),
            "automatic user-data loading accepts XML without a BOM and preserves all Unicode text");
        Require(WriteCalculatorPresets(path, presets), "restore user XML with a BOM");
        Require(ReadCalculatorPresets(path, &loadedPresets) && SamePresets(presets, loadedPresets),
            "user XML preserves duplicate dates, Unicode and exact whitespace");
        SettingsSnapshot standalone = original;
        bool presetsOnly = false;
        Require(ReadSettingsXml(path, LANG_EN_US, Defaults, &standalone, &loadedPresets, &presetsOnly)
            && presetsOnly
            && SamePresets(presets, loadedPresets), "standalone times XML imports by content");
        Require(standalone.calculator.fromZone == original.calculator.fromZone
            && standalone.calculator.tab == original.calculator.tab
            && standalone.widgets.size() == original.widgets.size(),
                "standalone import leaves settings unchanged");
        Require(!ReadSettingsXml(path, LANG_EN_US, Defaults, &standalone),
            "automatic settings loading cannot mistake user data for application settings");
        std::wstring textPath = path + L".txt";
        Require(CopyFileW(path.c_str(), textPath.c_str(), TRUE) != FALSE,
            "test copy uses a non-XML extension");
        bool textRead = ReadSettingsXml(textPath, LANG_EN_US, Defaults, &standalone, &loadedPresets,
            &presetsOnly);
        DeleteFileW(textPath.c_str());
        Require(textRead && presetsOnly && SamePresets(presets, loadedPresets),
            "XML content is accepted under a txt filename");
        SettingsSnapshot loaded = RoundTrip(original, nullptr, &loadedPresets);
        Require(loadedPresets.empty(), "automatic settings XML contains no user data");
        Require(loaded.calculator.tab == 3 && loaded.calculator.fromNow && !loaded.calculator.toNow,
            "XML window inputs and selected tab");
        Require(loaded.calculator.highlights == original.calculator.highlights,
            "XML roundtrip preserves independent highlight choices");
        Require(loaded.calculator.fromZone == original.calculator.fromZone
            && loaded.calculator.toZone == original.calculator.toZone, "XML stores selected display zones");
        Require(loaded.calculatorWindowState.x == -123 && loaded.calculatorWindowState.y == 456,
            "XML window position");
        loaded = RoundTrip(original, &presets, &loadedPresets);
        Require(SamePresets(presets, loadedPresets), "explicit export contains user data separately");
        Require(FormatCalculatorTime(loaded.calculator.day) == FormatCalculatorTime(original.calculator.day),
            "export retains the settings date boundary");
        DWORD disposition = 0;
        Require(RegCreateKeyExW(HKEY_CURRENT_USER, testKey.c_str(), 0, nullptr, REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS, nullptr, &key, &disposition) == ERROR_SUCCESS, "isolated registry key");
        Require(WriteCalculatorRegistry(key, original), "registry settings write");
        loaded = SettingsSnapshot{};
        ReadCalculatorRegistry(key, &loaded);
        Require(loaded.calculator.tab == 3 && loaded.calculatorWindowState.x == -123,
            "registry retains window settings");
        Require(loaded.calculator.highlights == original.calculator.highlights,
            "registry roundtrip preserves independent highlight choices");
        Require(FormatCalculatorTime(loaded.calculator.from) == FormatCalculatorTime(original.calculator.from)
            && loaded.calculator.fromZone == original.calculator.fromZone, "registry stores UTC and zone");
        HKEY absent = nullptr;
        Require(RegOpenKeyExW(key, L"Calculator\\Presets", 0, KEY_READ, &absent) == ERROR_FILE_NOT_FOUND,
            "registry has no user-data collection");
        TestHighlightStorage(key, original);
        TestCalendarDateStorage(key, original);
        Require(ReadCalculatorPresets(path, &loadedPresets) && SamePresets(presets, loadedPresets),
            "settings writes never alter the independent user file");
        locked = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
        Require(locked != INVALID_HANDLE_VALUE, "lock original user file against replacement");
        std::vector<TimeCalculatorPreset> changed = presets;
        changed.erase(changed.begin());
        Require(!WriteCalculatorPresets(path, changed), "replacement failure is reported");
        CloseHandle(locked);
        locked = INVALID_HANDLE_VALUE;
        Require(ReadCalculatorPresets(path, &loadedPresets) && SamePresets(presets, loadedPresets),
            "failed save preserves every original user record");
        Require(WriteCalculatorPresets(path, changed), "successful deletion rewrites user file");
        Require(ReadCalculatorPresets(path, &loadedPresets) && SamePresets(changed, loadedPresets),
            "explicit deletion removes only the selected record");
        Require(ReadText("<CalClockExport version=\"1\"><TimeCalculatorPresets version=\"2\"/>"
            "<CalClockSettings version=\"1\"><Widgets><Widget id=\"1\"/></Widgets></CalClockSettings>"
            "</CalClockExport>"), "sibling sections can appear in either order");
        Require(ReadText("<TimeCalculatorPresets version=\"2\"/>"), "empty standalone collection is valid");
        Require(!ReadText("<TimeCalculatorPresets version=\"2\"><Preset time=\"2023-02-29T01:00:00.000Z\" "
            "zone=\"UTC+00:00\" description=\"bad\"/></TimeCalculatorPresets>"),
            "standalone import validates actual calendar dates");
        Require(!ReadText("<TimeCalculatorPresets version=\"2\"><Preset time=\"2026-11-03T01:00:00.000\" "
            "zone=\"UTC+00:00\" description=\"bad\"/></TimeCalculatorPresets>"),
            "standalone import rejects timestamps that do not identify UTC");
        Require(!ReadText("<CalClockExport version=\"1\"><CalClockSettings version=\"1\">"
            "<Widgets><Widget id=\"1\"/></Widgets></CalClockSettings></CalClockExport>"),
            "wrapper without user data is not a valid export structure");
        SYSTEMTIME invalid = {};
        Require(!ParseCalculatorTime(L"2026-11-03T12:30:00.000", &invalid), "reject a timestamp without UTC");
        Require(!ParseCalculatorTime(L"2023-02-29T01:00:00.000Z", &invalid), "reject non-leap date");
        Require(!ParseCalculatorTime(L"2024-04-31T01:00:00.000Z", &invalid), "reject impossible day");
        Require(!ParseCalculatorTime(L"2024-01-01T24:00:00.000Z", &invalid), "reject invalid hour");
        Require(!ReadText("<CalClockSettings version=\"1\"><TimeCalculatorPresets version=\"1\">"
            "<Preset time=\"2023-02-29T01:00:00.000\" description=\"bad\"/></TimeCalculatorPresets>"
            "<Widget id=\"1\"/></CalClockSettings>"), "reject invalid imported user date");
        Require(ReadText("<CalClockSettings version=\"1\"><Widget id=\"1\"/></CalClockSettings>"),
            "older settings without calculator data remain importable");
        TestPresetImports(path, original, presets);
        std::vector<TimeCalculatorPreset> maximum(TIME_CALCULATOR_MAX_PRESETS,
            TimeCalculatorPreset{
                original.calculator.from,
                std::wstring(TIME_CALCULATOR_MAX_DESCRIPTION, L'&')
            });
        Require(WriteCalculatorPresets(path, maximum)
            && ReadCalculatorPresets(path, &loadedPresets)
            && SamePresets(maximum, loadedPresets), "maximum escaped user collection round trip");
        maximum.push_back(presets[0]);
        Require(!WriteCalculatorPresets(path, maximum), "oversized collection rejected before writing");
        maximum.resize(1);
        maximum[0].description.assign(1, 0xD800);
        Require(!WriteCalculatorPresets(path, maximum), "broken Unicode rejected before writing");
        HANDLE malformed = CreateFileW(path.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, 0, nullptr);
        Require(malformed != INVALID_HANDLE_VALUE, "write malformed fixture");
        const char invalidXml[] = "<TimeCalculatorPresets version=\"1\"><Preset";
        DWORD written = 0;
        BOOL stored = WriteFile(malformed, invalidXml, sizeof(invalidXml) - 1, &written, nullptr);
        CloseHandle(malformed);
        Require(stored != FALSE && written == sizeof(invalidXml) - 1, "malformed fixture saved");
        loadedPresets = presets;
        Require(!ReadCalculatorPresets(path, &loadedPresets)
            && SamePresets(presets, loadedPresets), "failed read preserves the destination collection");
        RegCloseKey(key);
        key = nullptr;
        RegDeleteTreeW(HKEY_CURRENT_USER, testKey.c_str());
        DeleteFileW(path.c_str());
        std::cout << "PASS: independent times XML, settings/export separation, "
            "exact text and failure preservation.\n";
        return 0;
    } catch (const std::exception& error) {
        if (locked != INVALID_HANDLE_VALUE) {
            CloseHandle(locked);
        }
        if (key != nullptr) {
            RegCloseKey(key);
        }
        RegDeleteTreeW(HKEY_CURRENT_USER, testKey.c_str());
        if (!path.empty()) {
            DeleteFileW(path.c_str());
            DeleteFileW((path + L".tmp").c_str());
        }
        std::cerr << error.what() << '\n';
        return 1;
    }
}
