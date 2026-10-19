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
 * Last modified for version 1.6.0.1
 */

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "MonitorInfo.h"
#include "Localization.h"
#include <cwchar>
#include <wrl/client.h>

#pragma comment(lib, "Dxgi.lib")

/// Optional display-configuration entry points, unavailable on Windows Vista.
using GetDisplayConfigSizes = LONG(WINAPI*)(UINT32, UINT32*, UINT32*);
using QueryCurrentDisplayConfig = LONG(WINAPI*)(UINT32, UINT32*, DISPLAYCONFIG_PATH_INFO*, UINT32*,
    DISPLAYCONFIG_MODE_INFO*, DISPLAYCONFIG_TOPOLOGY_ID*);
using GetDisplayConfigInfo = LONG(WINAPI*)(DISPLAYCONFIG_DEVICE_INFO_HEADER*);

/// Removes the Win32 device-namespace prefix only from the displayed monitor name.
std::wstring MonitorDisplayName(const std::wstring& device) {
    if (device.compare(0, 4, L"\\\\.\\") == 0) {
        return device.substr(4);
    }
    return device;
}

/// Reads the active monitor description, integer refresh rate and pixel depth using Vista-compatible APIs.
static void ReadLegacyMonitorDetails(const std::wstring& device, MonitorDetails& details) {
    DISPLAY_DEVICEW display{};
    display.cb = sizeof(display);
    for (DWORD index = 0; EnumDisplayDevicesW(device.c_str(), index, &display, 0); index++) {
        if ((display.StateFlags & DISPLAY_DEVICE_ACTIVE) != 0 && display.DeviceString[0] != L'\0') {
            details.model = display.DeviceString;
            break;
        }
        display = DISPLAY_DEVICEW{};
        display.cb = sizeof(display);
    }
    DEVMODEW mode{};
    mode.dmSize = sizeof(mode);
    if (EnumDisplaySettingsW(device.c_str(), ENUM_CURRENT_SETTINGS, &mode)) {
        if ((mode.dmFields & DM_DISPLAYFREQUENCY) != 0 && mode.dmDisplayFrequency > 1) {
            details.refreshRate.Numerator = mode.dmDisplayFrequency;
            details.refreshRate.Denominator = 1;
        }
        if ((mode.dmFields & DM_BITSPERPEL) != 0) {
            details.bitsPerPixel = mode.dmBitsPerPel;
        }
    }
}

/// Reads current target metadata without interpreting advanced-color support as an active color space.
static void ReadDisplayConfigTargetDetails(const DISPLAYCONFIG_PATH_INFO& path,
        const std::vector<DISPLAYCONFIG_MODE_INFO>& modes, GetDisplayConfigInfo getDeviceInfo, MonitorDetails& details) {
    DISPLAYCONFIG_TARGET_DEVICE_NAME target{};
    target.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
    target.header.size = sizeof(target);
    target.header.adapterId = path.targetInfo.adapterId;
    target.header.id = path.targetInfo.id;
    if (getDeviceInfo(&target.header) == ERROR_SUCCESS && target.monitorFriendlyDeviceName[0] != L'\0') {
        details.model = target.monitorFriendlyDeviceName;
    }
    DISPLAYCONFIG_RATIONAL rate = path.targetInfo.refreshRate;
    const UINT32 modeIndex = path.targetInfo.modeInfoIdx;
    if (modeIndex < modes.size()) {
        const DISPLAYCONFIG_MODE_INFO& mode = modes[modeIndex];
        if (mode.infoType == DISPLAYCONFIG_MODE_INFO_TYPE_TARGET
                && mode.id == path.targetInfo.id
                && mode.adapterId.HighPart == path.targetInfo.adapterId.HighPart
                && mode.adapterId.LowPart == path.targetInfo.adapterId.LowPart) {
            const DISPLAYCONFIG_RATIONAL signalRate = mode.targetMode.targetVideoSignalInfo.vSyncFreq;
            if (signalRate.Numerator != 0 && signalRate.Denominator != 0) {
                rate = signalRate;
            }
        }
    }
    if (rate.Numerator != 0 && rate.Denominator != 0) {
        details.refreshRate = rate;
    }
    DISPLAYCONFIG_GET_ADVANCED_COLOR_INFO color{};
    color.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_ADVANCED_COLOR_INFO;
    color.header.size = sizeof(color);
    color.header.adapterId = path.targetInfo.adapterId;
    color.header.id = path.targetInfo.id;
    if (getDeviceInfo(&color.header) == ERROR_SUCCESS) {
        details.bitsPerColor = color.bitsPerColorChannel;
        details.colorEncoding = color.colorEncoding;
    }
}

/// Upgrades legacy metadata from one consistent active display configuration, retrying topology changes.
static void ReadDisplayConfigMonitorDetails(const std::vector<DisplayMonitor>& monitors,
        std::vector<MonitorDetails>& details, GetDisplayConfigSizes getBufferSizes,
        QueryCurrentDisplayConfig queryDisplayConfig, GetDisplayConfigInfo getDeviceInfo) {
    if (!getBufferSizes || !queryDisplayConfig || !getDeviceInfo) {
        return;
    }
    for (int attempt = 0; attempt < 3; attempt++) {
        UINT32 pathCount = 0;
        UINT32 modeCount = 0;
        if (getBufferSizes(QDC_ONLY_ACTIVE_PATHS, &pathCount, &modeCount) != ERROR_SUCCESS) {
            return;
        }
        std::vector<DISPLAYCONFIG_PATH_INFO> paths(pathCount);
        std::vector<DISPLAYCONFIG_MODE_INFO> modes(modeCount);
        const LONG result =
            queryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &pathCount, paths.data(), &modeCount, modes.data(), nullptr);
        if (result == ERROR_INSUFFICIENT_BUFFER) {
            continue;
        }
        if (result != ERROR_SUCCESS) {
            return;
        }
        paths.resize(pathCount);
        modes.resize(modeCount);
        for (const DISPLAYCONFIG_PATH_INFO& path : paths) {
            if (!path.targetInfo.targetAvailable) {
                continue;
            }
            DISPLAYCONFIG_SOURCE_DEVICE_NAME source{};
            source.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            source.header.size = sizeof(source);
            source.header.adapterId = path.sourceInfo.adapterId;
            source.header.id = path.sourceInfo.id;
            if (getDeviceInfo(&source.header) != ERROR_SUCCESS) {
                continue;
            }
            for (std::size_t index = 0; index < monitors.size(); index++) {
                if (_wcsicmp(monitors[index].device.c_str(), source.viewGdiDeviceName) == 0) {
                    ReadDisplayConfigTargetDetails(path, modes, getDeviceInfo, details[index]);
                    break;
                }
            }
        }
        return;
    }
}

/// Reads current output color-space metadata through an optional COM interface, including on mixed adapters.
static void ReadDxgiMonitorDetails(const std::vector<DisplayMonitor>& monitors, std::vector<MonitorDetails>& details) {
    Microsoft::WRL::ComPtr<IDXGIFactory> factory;
    if (FAILED(CreateDXGIFactory(IID_PPV_ARGS(factory.GetAddressOf())))) {
        return;
    }
    for (UINT adapterIndex = 0; ; adapterIndex++) {
        Microsoft::WRL::ComPtr<IDXGIAdapter> adapter;
        if (FAILED(factory->EnumAdapters(adapterIndex, adapter.GetAddressOf()))) {
            break;
        }
        for (UINT outputIndex = 0; ; outputIndex++) {
            Microsoft::WRL::ComPtr<IDXGIOutput> output;
            if (FAILED(adapter->EnumOutputs(outputIndex, output.GetAddressOf()))) {
                break;
            }
            Microsoft::WRL::ComPtr<IDXGIOutput6> modernOutput;
            if (FAILED(output.As(&modernOutput))) {
                continue;
            }
            DXGI_OUTPUT_DESC1 description{};
            if (FAILED(modernOutput->GetDesc1(&description)) || !description.AttachedToDesktop) {
                continue;
            }
            for (std::size_t index = 0; index < monitors.size(); index++) {
                if (_wcsicmp(monitors[index].device.c_str(), description.DeviceName) == 0) {
                    if (details[index].bitsPerColor == 0) {
                        details[index].bitsPerColor = description.BitsPerColor;
                    }
                    details[index].colorSpace = description.ColorSpace;
                    break;
                }
            }
        }
    }
}

/// Collects monitor metadata without adding imports unavailable on Windows Vista.
std::vector<MonitorDetails> ReadMonitorDetails(const std::vector<DisplayMonitor>& monitors) {
    std::vector<MonitorDetails> details(monitors.size());
    for (std::size_t index = 0; index < monitors.size(); index++) {
        ReadLegacyMonitorDetails(monitors[index].device, details[index]);
    }
    const HMODULE userLibrary = GetModuleHandleW(L"user32.dll");
    if (userLibrary) {
        const GetDisplayConfigSizes getBufferSizes =
            reinterpret_cast<GetDisplayConfigSizes>(GetProcAddress(userLibrary, "GetDisplayConfigBufferSizes"));
        const QueryCurrentDisplayConfig queryDisplayConfig =
            reinterpret_cast<QueryCurrentDisplayConfig>(GetProcAddress(userLibrary, "QueryDisplayConfig"));
        const GetDisplayConfigInfo getDeviceInfo =
            reinterpret_cast<GetDisplayConfigInfo>(GetProcAddress(userLibrary, "DisplayConfigGetDeviceInfo"));
        ReadDisplayConfigMonitorDetails(monitors, details, getBufferSizes, queryDisplayConfig, getDeviceInfo);
    }
    ReadDxgiMonitorDetails(monitors, details);
    return details;
}

/// Formats the current refresh rate using the user's decimal separator and retaining fractional Hertz.
std::wstring MonitorRefreshRateText(const MonitorDetails& details) {
    const DISPLAYCONFIG_RATIONAL rate = details.refreshRate;
    if (rate.Numerator == 0 || rate.Denominator == 0) {
        return L"—";
    }
    wchar_t value[64]{};
    swprintf_s(value, L"%.2f", static_cast<double>(rate.Numerator) / rate.Denominator);
    wchar_t decimalSeparator[8] = L".";
    GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_SDECIMAL, decimalSeparator, 8);
    NUMBERFMTW format{};
    format.NumDigits = rate.Numerator % rate.Denominator == 0 ? 0 : 2;
    format.LeadingZero = 1;
    format.lpDecimalSep = decimalSeparator;
    format.lpThousandSep = const_cast<LPWSTR>(L"");
    format.NegativeOrder = 1;
    wchar_t localized[64]{};
    if (GetNumberFormatW(LOCALE_USER_DEFAULT, 0, value, &format, localized, 64)) {
        return std::wstring(localized) + L" Hz";
    }
    return std::wstring(value) + L" Hz";
}

/// Formats channel depth when available, otherwise explicitly identifies legacy pixel depth.
std::wstring MonitorBitDepthText(const MonitorDetails& details, AppLanguage language) {
    const MonitorColumnText& strings = MonitorColumnsText(language);
    wchar_t value[64]{};
    if (details.bitsPerColor != 0) {
        swprintf_s(value, strings.channelDepth, details.bitsPerColor);
        return value;
    }
    if (details.bitsPerPixel != 0) {
        swprintf_s(value, strings.pixelDepth, details.bitsPerPixel);
        return value;
    }
    return L"—";
}

/// Names the actual output color encoding without guessing from desktop pixel depth.
const wchar_t* MonitorColorFormatText(DISPLAYCONFIG_COLOR_ENCODING encoding) {
    switch (encoding) {
        case DISPLAYCONFIG_COLOR_ENCODING_RGB:
            return L"RGB";
        case DISPLAYCONFIG_COLOR_ENCODING_YCBCR444:
            return L"YCbCr 4:4:4";
        case DISPLAYCONFIG_COLOR_ENCODING_YCBCR422:
            return L"YCbCr 4:2:2";
        case DISPLAYCONFIG_COLOR_ENCODING_YCBCR420:
            return L"YCbCr 4:2:0";
        case DISPLAYCONFIG_COLOR_ENCODING_INTENSITY:
            return L"Y";
        default:
            return L"—";
    }
}

/// Names output color primaries and transfer characteristics reported by DXGI.
const wchar_t* MonitorColorSpaceText(DXGI_COLOR_SPACE_TYPE colorSpace) {
    switch (colorSpace) {
        case DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709:
            return L"sRGB (SDR)";
        case DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709:
            return L"BT.709 (linear)";
        case DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P709:
        case DXGI_COLOR_SPACE_YCBCR_FULL_G22_NONE_P709_X601:
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P709:
        case DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P709:
            return L"BT.709 (G22)";
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P601:
        case DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P601:
            return L"BT.601 (G22)";
        case DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P2020:
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P2020:
        case DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P2020:
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_TOPLEFT_P2020:
        case DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P2020:
            return L"BT.2020 (G22)";
        case DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020:
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G2084_LEFT_P2020:
        case DXGI_COLOR_SPACE_RGB_STUDIO_G2084_NONE_P2020:
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G2084_TOPLEFT_P2020:
            return L"BT.2020 (PQ/HDR10)";
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_GHLG_TOPLEFT_P2020:
        case DXGI_COLOR_SPACE_YCBCR_FULL_GHLG_TOPLEFT_P2020:
            return L"BT.2020 (HLG)";
        case DXGI_COLOR_SPACE_RGB_STUDIO_G24_NONE_P709:
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_LEFT_P709:
            return L"BT.709 (G24)";
        case DXGI_COLOR_SPACE_RGB_STUDIO_G24_NONE_P2020:
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_LEFT_P2020:
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_TOPLEFT_P2020:
            return L"BT.2020 (G24)";
        case DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P2020:
            return L"BT.2020 (linear)";
        default:
            return L"—";
    }
}
