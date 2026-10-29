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
 * Last modified for version 1.7.0.0
 */

#define NOMINMAX
#include "AudioOutput.h"
#include <cwchar>
#include <utility>
#include <initguid.h>
#include <mmdeviceapi.h>
#include <functiondiscoverykeys_devpkey.h>
#include <mmsystem.h>
#include <mmddk.h>
#include <wrl/client.h>

#pragma comment(lib, "Ole32.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Uuid.lib")

/// Reads the opaque Windows endpoint ID associated with one current waveOut device index.
static bool ReadAudioOutputEndpoint(UINT deviceId, std::wstring* endpoint) {
    HWAVEOUT device = reinterpret_cast<HWAVEOUT>(static_cast<UINT_PTR>(deviceId));
    ULONG bytes = 0;
    if (waveOutMessage(device, DRV_QUERYFUNCTIONINSTANCEIDSIZE, reinterpret_cast<DWORD_PTR>(&bytes), 0)
            != MMSYSERR_NOERROR || bytes < sizeof(wchar_t)) {
        return false;
    }
    std::wstring value(bytes / sizeof(wchar_t), L'\0');
    if (waveOutMessage(device, DRV_QUERYFUNCTIONINSTANCEID, reinterpret_cast<DWORD_PTR>(value.data()), bytes)
            != MMSYSERR_NOERROR) {
        return false;
    }
    value.resize(wcsnlen_s(value.data(), value.size()));
    if (value.empty()) {
        return false;
    }
    *endpoint = std::move(value);
    return true;
}

/// Uses the endpoint property store for full device names, retaining the native waveOut name on a lookup
/// failure.
static std::wstring ReadAudioOutputName(IMMDeviceEnumerator* enumerator, const std::wstring& endpoint,
        const wchar_t* fallback) {
    Microsoft::WRL::ComPtr<IMMDevice> device;
    Microsoft::WRL::ComPtr<IPropertyStore> properties;
    PROPVARIANT name = {};
    std::wstring result = fallback;
    if (enumerator != nullptr && SUCCEEDED(enumerator->GetDevice(endpoint.c_str(), &device))
            && SUCCEEDED(device->OpenPropertyStore(STGM_READ, &properties))
            && SUCCEEDED(properties->GetValue(PKEY_Device_FriendlyName, &name))
            && name.vt == VT_LPWSTR && name.pwszVal != nullptr) {
        result = name.pwszVal;
    }
    PropVariantClear(&name);
    return result;
}

/// Enumerates waveform devices while COM is available, keeping transient device indices out of saved settings.
static std::vector<AudioOutputDevice> ReadAudioOutputDevices() {
    Microsoft::WRL::ComPtr<IMMDeviceEnumerator> enumerator;
    bool hasEnumerator = SUCCEEDED(CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr,
        CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&enumerator)));
    std::vector<AudioOutputDevice> devices;
    UINT count = waveOutGetNumDevs();
    for (UINT index = 0; index < count; index++) {
        WAVEOUTCAPSW capabilities = {};
        std::wstring endpoint;
        if (waveOutGetDevCapsW(index, &capabilities, sizeof(capabilities)) == MMSYSERR_NOERROR
                && ReadAudioOutputEndpoint(index, &endpoint)) {
            devices.push_back(AudioOutputDevice{
                endpoint, ReadAudioOutputName(hasEnumerator ? enumerator.Get() : nullptr,
                    endpoint, capabilities.szPname) });
        }
    }
    return devices;
}

/// Lists currently available waveform outputs with their persistent endpoint IDs and full Windows names.
std::vector<AudioOutputDevice> EnumerateAudioOutputDevices() {
    HRESULT initialized = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    std::vector<AudioOutputDevice> devices = ReadAudioOutputDevices();
    if (SUCCEEDED(initialized)) {
        CoUninitialize();
    }
    return devices;
}

/// Resolves an endpoint to its current waveOut index; an empty ID selects the current Windows default.
/// Returns false when the selected output is unavailable, without redirecting sound to another device.
bool ResolveAudioOutputDevice(const std::wstring& requested, std::wstring* endpoint, UINT* deviceId) {
    if (requested.empty()) {
        DWORD preferred = WAVE_MAPPER;
        DWORD flags = 0;
        HWAVEOUT mapper = reinterpret_cast<HWAVEOUT>(static_cast<UINT_PTR>(WAVE_MAPPER));
        if (waveOutMessage(mapper, DRVM_MAPPER_PREFERRED_GET, reinterpret_cast<DWORD_PTR>(&preferred),
            reinterpret_cast<DWORD_PTR>(&flags)) != MMSYSERR_NOERROR
                || preferred == WAVE_MAPPER
                || !ReadAudioOutputEndpoint(preferred, endpoint)) {
            return false;
        }
        *deviceId = preferred;
        return true;
    }
    UINT count = waveOutGetNumDevs();
    for (UINT index = 0; index < count; index++) {
        std::wstring current;
        if (ReadAudioOutputEndpoint(index, &current) && current == requested) {
            *endpoint = std::move(current);
            *deviceId = index;
            return true;
        }
    }
    return false;
}
