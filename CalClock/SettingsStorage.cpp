#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "SettingsStorage.h"
#include <windows.h>
#include <algorithm>
#include <climits>
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

static bool ReadDword(HKEY key, const wchar_t* name, DWORD* value) {
    DWORD type = 0;
    DWORD size = sizeof(*value);
    return RegQueryValueExW(key, name, nullptr, &type, reinterpret_cast<BYTE*>(value), &size) == ERROR_SUCCESS && type == REG_DWORD;
}

static bool ReadQword(HKEY key, const wchar_t* name, LONGLONG* value) {
    DWORD type = 0;
    DWORD size = sizeof(*value);
    return RegQueryValueExW(key, name, nullptr, &type, reinterpret_cast<BYTE*>(value), &size) == ERROR_SUCCESS && type == REG_QWORD;
}

static bool ReadString(HKEY key, const wchar_t* name, std::wstring* value) {
    DWORD type = 0;
    DWORD size = 0;
    if (RegQueryValueExW(key, name, nullptr, &type, nullptr, &size) != ERROR_SUCCESS || type != REG_SZ && type != REG_EXPAND_SZ || size < sizeof(wchar_t)) {
        return false;
    }
    std::vector<wchar_t> buffer(size / sizeof(wchar_t) + 1, 0);
    if (RegQueryValueExW(key, name, nullptr, &type, reinterpret_cast<BYTE*>(buffer.data()), &size) != ERROR_SUCCESS) {
        return false;
    }
    *value = buffer.data();
    return true;
}

static void WriteDword(HKEY key, const wchar_t* name, DWORD value) {
    RegSetValueExW(key, name, 0, REG_DWORD, reinterpret_cast<const BYTE*>(&value), sizeof(value));
}

static void WriteQword(HKEY key, const wchar_t* name, LONGLONG value) {
    RegSetValueExW(key, name, 0, REG_QWORD, reinterpret_cast<const BYTE*>(&value), sizeof(value));
}

static void WriteString(HKEY key, const wchar_t* name, const std::wstring& value) {
    RegSetValueExW(key, name, 0, REG_SZ, reinterpret_cast<const BYTE*>(value.c_str()), static_cast<DWORD>((value.size() + 1) * sizeof(wchar_t)));
}

std::wstring AutomaticXmlSettingsPath(bool createDirectory) {
    wchar_t appData[MAX_PATH] = {};
    if (SHGetFolderPathW(nullptr, CSIDL_APPDATA | (createDirectory ? CSIDL_FLAG_CREATE : 0), nullptr, SHGFP_TYPE_CURRENT, appData) != S_OK) {
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

static HRESULT WriteXmlTextAttribute(IXmlWriter* writer, const wchar_t* name, const std::wstring& value) {
    return writer->WriteAttributeString(nullptr, name, nullptr, value.c_str());
}

static HRESULT WriteXmlNumberAttribute(IXmlWriter* writer, const wchar_t* name, LONGLONG value) {
    wchar_t text[32] = {};
    _i64tow_s(value, text, ARRAYSIZE(text), 10);
    return writer->WriteAttributeString(nullptr, name, nullptr, text);
}

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

bool WriteSettingsXml(const std::wstring& path, const SettingsSnapshot& snapshot) {
    if (path.empty() || snapshot.widgets.empty()) {
        return false;
    }
    IStream* stream = nullptr;
    if (FAILED(SHCreateStreamOnFileEx(path.c_str(), STGM_CREATE | STGM_WRITE | STGM_SHARE_DENY_WRITE, FILE_ATTRIBUTE_NORMAL, TRUE, nullptr, &stream))) {
        return false;
    }
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
            result = WriteXmlNumberAttribute(writer, L"leadingZero", config.leadingZero);
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
            result = WriteXmlNumberAttribute(writer, L"showFrame", config.showFrame);
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
            result = WriteXmlNumberAttribute(writer, L"alarmBackgroundColor", static_cast<DWORD>(config.alarmBackgroundColor));
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
            result = WriteXmlNumberAttribute(writer, L"alarmEnabled", config.alarmEnabled);
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
    stream->Release();
    return SUCCEEDED(result);
}

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

static bool ReadXmlNumberAttribute(IXmlReader* reader, const wchar_t* name, LONGLONG* value) {
    std::wstring text;
    return ReadXmlAttribute(reader, name, &text) && ParseXmlNumber(text, value);
}

static void ReadWidgetXml(IXmlReader* reader, int index, AppLanguage defaultLanguage, int defaultFontAntialiasing, WidgetDefaultsFactory createDefaults, WidgetConfig* config) {
    LONGLONG number = 0;
    int type = WIDGET_ANALOG;
    if (ReadXmlNumberAttribute(reader, L"type", &number) && number >= 0 && number < WIDGET_TYPE_COUNT) {
        type = static_cast<int>(number);
    }
    *config = createDefaults(static_cast<WidgetType>(type), index, defaultLanguage, defaultFontAntialiasing);
    config->showFrame = false;
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
    if (ReadXmlNumberAttribute(reader, L"leadingZero", &number)) {
        config->leadingZero = number != 0;
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
    if (ReadXmlNumberAttribute(reader, L"showFrame", &number)) {
        config->showFrame = number != 0;
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
    if (ReadXmlNumberAttribute(reader, L"alarmEnabled", &number)) {
        config->alarmEnabled = number != 0;
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

bool ReadSettingsXml(const std::wstring& path, AppLanguage defaultLanguage, WidgetDefaultsFactory createDefaults, SettingsSnapshot* snapshot) {
    if (path.empty() || createDefaults == nullptr || snapshot == nullptr) {
        return false;
    }
    WIN32_FILE_ATTRIBUTE_DATA fileData = {};
    if (!GetFileAttributesExW(path.c_str(), GetFileExInfoStandard, &fileData) || fileData.nFileSizeHigh != 0 || fileData.nFileSizeLow > 4 * 1024 * 1024) {
        return false;
    }
    IStream* stream = nullptr;
    if (FAILED(SHCreateStreamOnFileEx(path.c_str(), STGM_READ | STGM_SHARE_DENY_WRITE, FILE_ATTRIBUTE_NORMAL, FALSE, nullptr, &stream))) {
        return false;
    }
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
            if (ReadXmlNumberAttribute(reader, L"fontAntialiasing", &number) && number >= 0 && number < FONT_ANTIALIAS_COUNT) {
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
            if (ReadXmlNumberAttribute(reader, L"settingsTab", &number) && number >= 0 && number < 5) {
                loaded.settingsTab = static_cast<int>(number);
            }
            if (ReadXmlNumberAttribute(reader, L"lastAddedWidgetType", &number) && number >= 0 && number < WIDGET_TYPE_COUNT) {
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
            if (loaded.widgets.size() >= 32) {
                result = E_FAIL;
                break;
            }
            WidgetConfig config = {};
            ReadWidgetXml(reader, static_cast<int>(loaded.widgets.size()), defaultLanguage, loaded.fontAntialiasing, createDefaults, &config);
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
    stream->Release();
    if (valid) {
        *snapshot = std::move(loaded);
    }
    return valid;
}

static void ReadWidgetConfig(HKEY key, WidgetConfig* config) {
    DWORD value = 0;
    config->showFrame = false;
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
    if (ReadDword(key, L"LeadingZero", &value)) {
        config->leadingZero = value != 0;
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
    if (ReadDword(key, L"ShowFrame", &value)) {
        config->showFrame = value != 0;
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
    if (ReadDword(key, L"AlarmEnabled", &value)) {
        config->alarmEnabled = value != 0;
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
    ReadString(key, L"Command", &config->command);
    if (ReadDword(key, L"CallRemoteScript", &value)) {
        config->callRemoteScript = value != 0;
    }
    ReadString(key, L"RemoteScriptUrl", &config->remoteScriptUrl);
}

static void WriteWidgetConfig(HKEY key, const WidgetConfig& config) {
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
    WriteDword(key, L"LeadingZero", config.leadingZero);
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
    WriteDword(key, L"ShowFrame", config.showFrame);
    WriteDword(key, L"TextColor", config.textColor);
    WriteDword(key, L"BackgroundColor", config.backgroundColor);
    WriteDword(key, L"AlarmTextColor", config.alarmTextColor);
    WriteDword(key, L"AlarmBackgroundColor", config.alarmBackgroundColor);
    WriteDword(key, L"WeekNumbers", config.weekNumbers);
    WriteDword(key, L"SundayFirst", config.sundayFirst);
    WriteDword(key, L"DateCopyFormat", config.dateCopyFormat);
    WriteDword(key, L"TimeSignal", config.timeSignal);
    WriteDword(key, L"AlarmEnabled", config.alarmEnabled);
    WriteDword(key, L"AlarmTimeSignal", config.alarmTimeSignal);
    WriteDword(key, L"AlarmHour", config.alarmHour);
    WriteDword(key, L"AlarmMinute", config.alarmMinute);
    WriteDword(key, L"RunCommand", config.runCommand);
    WriteDword(key, L"LoopAudio", config.loopAudio);
    WriteString(key, L"Command", config.command);
    WriteDword(key, L"CallRemoteScript", config.callRemoteScript);
    WriteString(key, L"RemoteScriptUrl", config.remoteScriptUrl);
}

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

bool ReadRegistrySettings(const SettingsSnapshot& defaults, WidgetDefaultsFactory createDefaults, SettingsSnapshot* snapshot) {
    if (createDefaults == nullptr || snapshot == nullptr) {
        return false;
    }
    HKEY root = nullptr;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, REGISTRY_PATH, 0, KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS, &root) != ERROR_SUCCESS) {
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
    if (ReadDword(root, L"SettingsTab", &value) && value < 5) {
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
    if (RegOpenKeyExW(root, L"Widgets", 0, KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS, &collection) == ERROR_SUCCESS && ReadDword(collection, L"Count", &count)) {
        count = std::min<DWORD>(count, 32);
        for (DWORD index = 0; index < count; index++) {
            wchar_t subkey[24] = {};
            swprintf_s(subkey, L"%u", index);
            HKEY item = nullptr;
            if (RegOpenKeyExW(collection, subkey, 0, KEY_QUERY_VALUE, &item) == ERROR_SUCCESS) {
                WidgetConfig config = createDefaults(WIDGET_ANALOG, static_cast<int>(index), loaded.language, loaded.fontAntialiasing);
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

bool WriteRegistrySettings(const SettingsSnapshot& snapshot) {
    HKEY root = nullptr;
    DWORD disposition = 0;
    if (RegCreateKeyExW(HKEY_CURRENT_USER, REGISTRY_PATH, 0, nullptr, 0, KEY_SET_VALUE | KEY_CREATE_SUB_KEY, nullptr, &root, &disposition) != ERROR_SUCCESS) {
        return false;
    }
    WriteDword(root, L"SchemaVersion", 13);
    WriteDword(root, L"Language", snapshot.language);
    WriteDword(root, L"DisableThemes", snapshot.themesDisabled);
    WriteDword(root, L"VisualStyles", !snapshot.themesDisabled);
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
    if (RegCreateKeyExW(root, L"Widgets", 0, nullptr, 0, collectionAccess, nullptr, &collection, &disposition) == ERROR_SUCCESS) {
        WriteDword(collection, L"Count", static_cast<DWORD>(snapshot.widgets.size()));
        written = true;
        for (size_t index = 0; index < snapshot.widgets.size(); index++) {
            wchar_t subkey[24] = {};
            swprintf_s(subkey, L"%zu", index);
            HKEY item = nullptr;
            if (RegCreateKeyExW(collection, subkey, 0, nullptr, 0, KEY_SET_VALUE, nullptr, &item, &disposition) == ERROR_SUCCESS) {
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

void RemoveRegistrySettings() {
    RegDeleteTreeW(HKEY_CURRENT_USER, REGISTRY_PATH);
    RegDeleteKeyW(HKEY_CURRENT_USER, VENDOR_REGISTRY_PATH);
}
