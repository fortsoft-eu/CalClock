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
 * Last modified for version 1.5.2.0
 */

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "AlarmActions.h"
#include "AudioDecoder.h"
#include "AudioGainCallback.h"
#include "AudioProcessing.h"
#include "IAudioSampleGrabber.h"
#include <windows.h>
#include <algorithm>
#include <array>
#include <cwctype>
#include <cmath>
#include <cstring>
#include <dshow.h>
#include <memory>
#include <mmsystem.h>
#include <shellapi.h>
#include <string>
#include <vector>
#include <winhttp.h>
#include <wmp.h>
#include <wrl/client.h>

#pragma comment(lib, "Ole32.lib")
#pragma comment(lib, "OleAut32.lib")
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Strmiids.lib")
#pragma comment(lib, "Winhttp.lib")
#pragma comment(lib, "Winmm.lib")

/// Owns the command string passed to the shell-launch worker.
struct LocalCommandThreadParameters {
    std::wstring command;
};

/// Owns the URL passed to the asynchronous HTTP request worker.
struct RemoteScriptThreadParameters {
    std::wstring url;
};

/// Keeps a DirectShow Sample Grabber and its gain callback alive while the playback graph runs.
struct AudioGainFilter {
    Microsoft::WRL::ComPtr<IAudioSampleGrabber> grabber;
    Microsoft::WRL::ComPtr<AudioGainCallback> callback;
};

/// Owns one decoded audio chunk and its waveOut header until playback releases the buffer.
struct AudioOutputBuffer {
    WAVEHDR header = {};
    std::vector<BYTE> data;
};

const CLSID AUDIO_SAMPLE_GRABBER = {
    0xC1F400A0,
    0x3F08,
    0x11D3,
    {
        0x9F,
        0x0B,
        0x00,
        0x60,
        0x08,
        0x03,
        0x9E,
        0x37
    }
};

/// Recognizes supported audio filename extensions case-insensitively without opening the file.
bool LooksLikeAudio(const std::wstring& path) {
    size_t dot = path.find_last_of(L'.');
    if (dot == std::wstring::npos) {
        return false;
    }
    std::wstring extension = path.substr(dot);
    std::transform(extension.begin(), extension.end(), extension.begin(), towlower);
    return extension == L".wav"
        || extension == L".mp3"
        || extension == L".wma"
        || extension == L".mid"
        || extension == L".midi"
        || extension == L".aac"
        || extension == L".m4a"
        || extension == L".flac";
}

/// Accepts an HTTP or HTTPS URL with a nonempty host that WinHTTP can parse.
bool IsRemoteScriptUrlValid(const std::wstring& url) {
    if (url.empty()) {
        return false;
    }
    URL_COMPONENTSW components = {};
    components.dwStructSize = sizeof(components);
    components.dwHostNameLength = static_cast<DWORD>(-1);
    components.dwUrlPathLength = static_cast<DWORD>(-1);
    components.dwExtraInfoLength = static_cast<DWORD>(-1);
    if (!WinHttpCrackUrl(url.c_str(), 0, 0, &components)) {
        return false;
    }
    return (components.nScheme == INTERNET_SCHEME_HTTP || components.nScheme == INTERNET_SCHEME_HTTPS)
        && components.lpszHostName != nullptr
        && components.dwHostNameLength != 0;
}

/// Waits for cancellation or input for up to the requested milliseconds, pumping queued thread messages.
/// Returns true only when the stop event is signaled.
static bool WaitForAudioStop(HANDLE stopEvent, DWORD milliseconds) {
    DWORD result = MsgWaitForMultipleObjects(1, &stopEvent, FALSE, milliseconds, QS_ALLINPUT);
    if (result == WAIT_OBJECT_0) {
        return true;
    }
    if (result == WAIT_OBJECT_0 + 1) {
        MSG message = {};
        while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessageW(&message);
        }
    }
    return false;
}

/// Maps the current gain to a legacy player's integer volume range, limiting amplification to unity.
static long AudioPlaybackLinearVolume(const AudioThreadParameters& parameters, long maximum) {
    return std::lround(maximum * std::min(1.0, AudioPlaybackGain(parameters)));
}

/// Returns the first pin with the requested direction, transferring its COM reference to the caller.
/// Returns VFW_E_NOT_FOUND if no matching pin exists.
static HRESULT GetAudioFilterPin(IBaseFilter* filter, PIN_DIRECTION direction, IPin** result) {
    Microsoft::WRL::ComPtr<IEnumPins> pins;
    HRESULT status = filter->EnumPins(&pins);
    if (FAILED(status)) {
        return status;
    }
    Microsoft::WRL::ComPtr<IPin> pin;
    while (pins->Next(1, pin.ReleaseAndGetAddressOf(), nullptr) == S_OK) {
        PIN_DIRECTION candidate = PINDIR_INPUT;
        if (SUCCEEDED(pin->QueryDirection(&candidate)) && candidate == direction) {
            *result = pin.Detach();
            return S_OK;
        }
    }
    return VFW_E_NOT_FOUND;
}

/// Inserts a Sample Grabber between a connected audio input and its upstream pin and attaches live gain processing.
/// Returns a failing HRESULT if the format is unsupported or graph reconnection fails.
static HRESULT InsertAudioGainFilter(IGraphBuilder* graph, IPin* input, const AM_MEDIA_TYPE& type,
        const AudioThreadParameters& parameters, AudioGainFilter& gainFilter) {
    AudioSampleFormat format;
    if (type.formattype != FORMAT_WaveFormatEx || !GetAudioSampleFormat(type.pbFormat, type.cbFormat, format)) {
        return VFW_E_INVALIDMEDIATYPE;
    }
    Microsoft::WRL::ComPtr<IPin> upstream;
    HRESULT result = input->ConnectedTo(&upstream);
    Microsoft::WRL::ComPtr<IBaseFilter> filter;
    if (SUCCEEDED(result)) {
        result = CoCreateInstance(AUDIO_SAMPLE_GRABBER, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&filter));
    }
    if (SUCCEEDED(result)) {
        result = filter.As(&gainFilter.grabber);
    }
    if (SUCCEEDED(result)) {
        result = gainFilter.grabber->SetMediaType(&type);
    }
    if (SUCCEEDED(result)) {
        result = graph->AddFilter(filter.Get(), L"Alarm volume");
    }
    Microsoft::WRL::ComPtr<IPin> gainInput;
    Microsoft::WRL::ComPtr<IPin> gainOutput;
    if (SUCCEEDED(result)) {
        result = GetAudioFilterPin(filter.Get(), PINDIR_INPUT, &gainInput);
    }
    if (SUCCEEDED(result)) {
        result = GetAudioFilterPin(filter.Get(), PINDIR_OUTPUT, &gainOutput);
    }
    if (SUCCEEDED(result)) {
        result = graph->Disconnect(input);
    }
    if (SUCCEEDED(result)) {
        result = graph->Disconnect(upstream.Get());
    }
    if (SUCCEEDED(result)) {
        result = graph->ConnectDirect(upstream.Get(), gainInput.Get(), &type);
    }
    if (SUCCEEDED(result)) {
        result = graph->ConnectDirect(gainOutput.Get(), input, &type);
    }
    if (SUCCEEDED(result)) {
        gainFilter.callback.Attach(new AudioGainCallback(parameters, format));
        result = gainFilter.grabber->SetCallback(gainFilter.callback.Get(), 0);
    }
    return result;
}

/// Finds terminal audio renderer inputs and inserts a gain callback before each one.
/// Retains the filters and callbacks in gainFilters and reports missing inputs or insertion failures.
static HRESULT AddAudioGainFilters(IGraphBuilder* graph, const AudioThreadParameters& parameters,
        std::vector<AudioGainFilter>& gainFilters) {
    Microsoft::WRL::ComPtr<IEnumFilters> filters;
    HRESULT result = graph->EnumFilters(&filters);
    if (FAILED(result)) {
        return result;
    }
    std::vector<Microsoft::WRL::ComPtr<IPin>> inputs;
    Microsoft::WRL::ComPtr<IBaseFilter> filter;
    while (filters->Next(1, filter.ReleaseAndGetAddressOf(), nullptr) == S_OK) {
        Microsoft::WRL::ComPtr<IPin> output;
        if (SUCCEEDED(GetAudioFilterPin(filter.Get(), PINDIR_OUTPUT, &output))) {
            continue;
        }
        Microsoft::WRL::ComPtr<IEnumPins> pins;
        if (FAILED(filter->EnumPins(&pins))) {
            continue;
        }
        Microsoft::WRL::ComPtr<IPin> input;
        while (pins->Next(1, input.ReleaseAndGetAddressOf(), nullptr) == S_OK) {
            AM_MEDIA_TYPE type = {};
            if (SUCCEEDED(input->ConnectionMediaType(&type)) && type.majortype == MEDIATYPE_Audio) {
                inputs.push_back(input);
            }
            FreeAudioMediaType(type);
        }
    }
    if (inputs.empty()) {
        return VFW_E_NOT_FOUND;
    }
    for (const Microsoft::WRL::ComPtr<IPin>& input : inputs) {
        AM_MEDIA_TYPE type = {};
        result = input->ConnectionMediaType(&type);
        gainFilters.push_back(AudioGainFilter{});
        if (SUCCEEDED(result)) {
            result = InsertAudioGainFilter(graph, input.Get(), type, parameters, gainFilters.back());
        }
        FreeAudioMediaType(type);
        if (FAILED(result)) {
            return result;
        }
    }
    return S_OK;
}

/// Streams decoded PCM through short waveOut buffers, applying live gain and honoring loop and stop settings.
/// Releases output resources before returning; true means playback started or cancellation was handled.
static bool StreamDecodedAudio(AudioDecoder& decoder, const AudioThreadParameters& parameters) {
    HWAVEOUT output = nullptr;
    if (waveOutOpen(&output, WAVE_MAPPER, decoder.GetWaveFormat(), 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
        return false;
    }
    std::array<AudioOutputBuffer, 3> buffers;
    size_t frames = std::max<DWORD>(1, decoder.GetWaveFormat()->nSamplesPerSec / 50);
    size_t chunkSize = frames * decoder.GetWaveFormat()->nBlockAlign;
    for (AudioOutputBuffer& buffer : buffers) {
        buffer.data.resize(chunkSize);
    }
    std::vector<BYTE> decoded;
    size_t decodedOffset = 0;
    size_t nextBuffer = 0;
    bool end = false;
    bool hasSamples = false;
    bool started = false;
    bool stopped = false;
    HRESULT result = S_OK;
    while (SUCCEEDED(result)) {
        stopped = WaitForAudioStop(parameters.stopEvent, 0);
        if (stopped) {
            break;
        }
        AudioOutputBuffer& buffer = buffers[nextBuffer];
        if (buffer.header.dwFlags & WHDR_PREPARED) {
            if (!(buffer.header.dwFlags & WHDR_DONE)) {
                stopped = WaitForAudioStop(parameters.stopEvent, 5);
                if (stopped) {
                    break;
                }
                continue;
            }
            if (waveOutUnprepareHeader(output, &buffer.header, sizeof(buffer.header)) != MMSYSERR_NOERROR) {
                result = E_FAIL;
                break;
            }
        }
        if (decodedOffset == decoded.size()) {
            if (end) {
                if (!parameters.loop || !hasSamples) {
                    break;
                }
                result = decoder.Restart(parameters.path);
                end = false;
                hasSamples = false;
            }
            if (SUCCEEDED(result)) {
                result = decoder.Read(decoded, end);
            }
            decodedOffset = 0;
            if (FAILED(result)) {
                break;
            }
            if (decoded.empty()) {
                stopped = WaitForAudioStop(parameters.stopEvent, 1);
                if (stopped) {
                    break;
                }
                continue;
            }
            hasSamples = true;
        }
        size_t length = std::min(chunkSize, decoded.size() - decodedOffset);
        std::memcpy(buffer.data.data(), decoded.data() + decodedOffset, length);
        result = ApplyAudioGain(buffer.data.data(), length, decoder.GetSampleFormat(), AudioPlaybackGain(parameters));
        if (FAILED(result)) {
            break;
        }
        decodedOffset += length;
        buffer.header = WAVEHDR{};
        buffer.header.lpData = reinterpret_cast<LPSTR>(buffer.data.data());
        buffer.header.dwBufferLength = static_cast<DWORD>(length);
        if (waveOutPrepareHeader(output, &buffer.header, sizeof(buffer.header)) != MMSYSERR_NOERROR
                || waveOutWrite(output, &buffer.header, sizeof(buffer.header)) != MMSYSERR_NOERROR) {
            result = E_FAIL;
            break;
        }
        started = true;
        nextBuffer = (nextBuffer + 1) % buffers.size();
    }
    if (SUCCEEDED(result) && !stopped) {
        for (AudioOutputBuffer& buffer : buffers) {
            while (buffer.header.dwFlags & WHDR_PREPARED && !(buffer.header.dwFlags & WHDR_DONE)) {
                stopped = WaitForAudioStop(parameters.stopEvent, 5);
                if (stopped) {
                    break;
                }
            }
            if (stopped) {
                break;
            }
        }
    }
    waveOutReset(output);
    for (AudioOutputBuffer& buffer : buffers) {
        if (buffer.header.dwFlags & WHDR_PREPARED) {
            waveOutUnprepareHeader(output, &buffer.header, sizeof(buffer.header));
        }
    }
    waveOutClose(output);
    return started || stopped;
}

/// Initializes COM and tries Media Foundation decoding with PCM playback, releasing the decoder before COM shutdown.
static bool PlayDecodedAudio(const AudioThreadParameters& parameters) {
    HRESULT initialized = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(initialized)) {
        return false;
    }
    bool handled = false;
    {
        AudioDecoder decoder;
        if (SUCCEEDED(decoder.Open(parameters.path))) {
            handled = StreamDecodedAudio(decoder, parameters);
        }
    }
    CoUninitialize();
    return handled;
}

/// Tries DirectShow playback with sample gain filters, looping, live volume, and cancellation.
/// Releases the graph and callbacks before returning whether playback started or cancellation was handled.
static bool PlayWithDirectShow(const AudioThreadParameters& parameters) {
    HRESULT initialized = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(initialized)) {
        return false;
    }
    IGraphBuilder* graph = nullptr;
    IMediaControl* control = nullptr;
    IMediaEvent* events = nullptr;
    IMediaSeeking* seeking = nullptr;
    IBasicAudio* audio = nullptr;
    HRESULT result = CoCreateInstance(CLSID_FilterGraph, nullptr, CLSCTX_INPROC_SERVER, IID_IGraphBuilder,
        reinterpret_cast<void**>(&graph));
    if (SUCCEEDED(result)) {
        result = graph->RenderFile(parameters.path.c_str(), nullptr);
    }
    if (SUCCEEDED(result)) {
        result = graph->QueryInterface(IID_IMediaControl, reinterpret_cast<void**>(&control));
    }
    if (SUCCEEDED(result)) {
        result = graph->QueryInterface(IID_IMediaEvent, reinterpret_cast<void**>(&events));
    }
    if (SUCCEEDED(result)) {
        result = graph->QueryInterface(IID_IBasicAudio, reinterpret_cast<void**>(&audio));
    }
    if (SUCCEEDED(result) && parameters.loop) {
        result = graph->QueryInterface(IID_IMediaSeeking, reinterpret_cast<void**>(&seeking));
    }
    std::vector<AudioGainFilter> gainFilters;
    if (SUCCEEDED(result)) {
        result = AddAudioGainFilters(graph, parameters, gainFilters);
    }
    if (SUCCEEDED(result)) {
        result = audio->put_Volume(0);
    }
    bool started = false;
    bool stopped = WaitForSingleObject(parameters.stopEvent, 0) == WAIT_OBJECT_0;
    if (SUCCEEDED(result) && !stopped) {
        result = control->Run();
        started = SUCCEEDED(result);
    }
    bool finished = false;
    while (SUCCEEDED(result) && started && !finished && !stopped) {
        stopped = WaitForAudioStop(parameters.stopEvent, 20);
        long eventCode = 0;
        LONG_PTR first = 0;
        LONG_PTR second = 0;
        while (SUCCEEDED(events->GetEvent(&eventCode, &first, &second, 0))) {
            events->FreeEventParams(eventCode, first, second);
            if (eventCode == EC_COMPLETE) {
                if (parameters.loop && !stopped) {
                    LONGLONG beginning = 0;
                    result = seeking->SetPositions(&beginning, AM_SEEKING_AbsolutePositioning,
                        nullptr, AM_SEEKING_NoPositioning);
                    if (SUCCEEDED(result)) {
                        result = control->Run();
                    }
                } else {
                    finished = true;
                }
            } else if (eventCode == EC_ERRORABORT || eventCode == EC_USERABORT) {
                finished = true;
            }
        }
    }
    if (control != nullptr) {
        control->Stop();
        control->Release();
    }
    for (AudioGainFilter& gainFilter : gainFilters) {
        if (gainFilter.grabber != nullptr) {
            gainFilter.grabber->SetCallback(nullptr, 0);
        }
    }
    gainFilters.clear();
    if (audio != nullptr) {
        audio->Release();
    }
    if (seeking != nullptr) {
        seeking->Release();
    }
    if (events != nullptr) {
        events->Release();
    }
    if (graph != nullptr) {
        graph->Release();
    }
    CoUninitialize();
    return started || stopped;
}

/// Tries legacy Windows Media Player playback with looping and live volume limited to unity.
/// Restores the player's original volume and releases COM resources before returning.
static bool PlayWithWindowsMediaPlayer(const AudioThreadParameters& parameters) {
    HRESULT initialized = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(initialized)) {
        return false;
    }
    IWMPPlayer4* player = nullptr;
    IWMPSettings* settings = nullptr;
    IWMPControls* controls = nullptr;
    HRESULT result = CoCreateInstance(__uuidof(WindowsMediaPlayer), nullptr, CLSCTX_INPROC_SERVER,
        __uuidof(IWMPPlayer4), reinterpret_cast<void**>(&player));
    if (SUCCEEDED(result)) {
        result = player->get_settings(&settings);
    }
    if (SUCCEEDED(result)) {
        result = settings->put_enableErrorDialogs(VARIANT_FALSE);
    }
    if (SUCCEEDED(result)) {
        result = settings->put_autoStart(VARIANT_TRUE);
    }
    BSTR loopMode = SysAllocString(L"loop");
    if (SUCCEEDED(result) && loopMode == nullptr) {
        result = E_OUTOFMEMORY;
    }
    if (SUCCEEDED(result)) {
        result = settings->setMode(loopMode, parameters.loop ? VARIANT_TRUE : VARIANT_FALSE);
    }
    long originalVolume = 100;
    long volume = AudioPlaybackLinearVolume(parameters, 100);
    if (SUCCEEDED(result)) {
        settings->get_volume(&originalVolume);
        result = settings->put_volume(volume);
    }
    BSTR path = SysAllocString(parameters.path.c_str());
    if (SUCCEEDED(result) && path == nullptr) {
        result = E_OUTOFMEMORY;
    }
    if (SUCCEEDED(result)) {
        result = player->put_URL(path);
    }
    if (SUCCEEDED(result)) {
        result = player->get_controls(&controls);
    }
    bool stopRequested = false;
    bool playbackStarted = false;
    bool playRequested = false;
    ULONGLONG startupTick = GetTickCount64();
    while (SUCCEEDED(result)) {
        if (WaitForAudioStop(parameters.stopEvent, 50)) {
            stopRequested = true;
            break;
        }
        long currentVolume = AudioPlaybackLinearVolume(parameters, 100);
        if (currentVolume != volume) {
            settings->put_volume(currentVolume);
            volume = currentVolume;
        }
        WMPPlayState state = wmppsUndefined;
        result = player->get_playState(&state);
        if (FAILED(result)) {
            break;
        }
        if (state == wmppsPlaying || state == wmppsScanForward || state == wmppsScanReverse) {
            playbackStarted = true;
            continue;
        }
        if (playbackStarted && (state == wmppsMediaEnded || state == wmppsStopped || state == wmppsReady)) {
            if (!parameters.loop) {
                break;
            }
            result = controls->put_currentPosition(0.0);
            if (SUCCEEDED(result)) {
                result = controls->play();
            }
            continue;
        }
        if (!playbackStarted && !playRequested && (state == wmppsReady || state == wmppsStopped)) {
            result = controls->play();
            playRequested = SUCCEEDED(result);
        }
        if (!playbackStarted && GetTickCount64() - startupTick >= 8000) {
            result = E_FAIL;
        }
    }
    if (controls != nullptr) {
        controls->stop();
        controls->Release();
    }
    if (settings != nullptr) {
        settings->put_volume(originalVolume);
        settings->Release();
    }
    if (player != nullptr) {
        player->close();
        player->Release();
    }
    SysFreeString(path);
    SysFreeString(loopMode);
    CoUninitialize();
    return stopRequested || SUCCEEDED(result) && playbackStarted;
}

/// Owns playback parameters and tries decoded PCM, DirectShow, Windows Media Player, then MCI playback.
/// Closes the worker's event handles and posts the widget ID and playback generation on completion.
static DWORD WINAPI AudioThreadProc(void* parameter) {
    std::unique_ptr<AudioThreadParameters> parameters(static_cast<AudioThreadParameters*>(parameter));
    if (PlayDecodedAudio(*parameters)
            || PlayWithDirectShow(*parameters)
            || PlayWithWindowsMediaPlayer(*parameters)
            || WaitForSingleObject(parameters->stopEvent, 0) == WAIT_OBJECT_0) {
        CloseHandle(parameters->stopEvent);
        CloseHandle(parameters->muteEvent);
        PostMessageW(parameters->notifyWindow, parameters->notifyMessage, static_cast<WPARAM>(parameters->widgetId),
            static_cast<LPARAM>(parameters->generation));
        return 0;
    }
    std::wstring alias = L"calClockAudio" + std::to_wstring(GetCurrentThreadId()) + L"_"
        + std::to_wstring(parameters->generation);
    std::wstring command = L"open \"" + parameters->path + L"\" type mpegvideo alias " + alias;
    bool opened = mciSendStringW(command.c_str(), nullptr, 0, nullptr) == 0;
    if (opened && WaitForSingleObject(parameters->stopEvent, 0) != WAIT_OBJECT_0) {
        long volume = AudioPlaybackLinearVolume(*parameters, 1000);
        command = L"setaudio " + alias + L" volume to " + std::to_wstring(volume);
        bool volumeSet = mciSendStringW(command.c_str(), nullptr, 0, nullptr) == 0;
        command = L"play " + alias + (parameters->loop ? L" repeat" : L"");
        if (volumeSet && mciSendStringW(command.c_str(), nullptr, 0, nullptr) == 0) {
            while (WaitForSingleObject(parameters->stopEvent, 100) == WAIT_TIMEOUT) {
                long currentVolume = AudioPlaybackLinearVolume(*parameters, 1000);
                if (currentVolume != volume) {
                    command = L"setaudio " + alias + L" volume to " + std::to_wstring(currentVolume);
                    mciSendStringW(command.c_str(), nullptr, 0, nullptr);
                    volume = currentVolume;
                }
                if (!parameters->loop) {
                    wchar_t mode[32] = {};
                    command = L"status " + alias + L" mode";
                    if (mciSendStringW(command.c_str(), mode, ARRAYSIZE(mode), nullptr) != 0
                            || _wcsicmp(mode, L"playing") != 0 && _wcsicmp(mode, L"seeking") != 0) {
                        break;
                    }
                }
            }
        }
        command = L"stop " + alias;
        mciSendStringW(command.c_str(), nullptr, 0, nullptr);
    }
    if (opened) {
        command = L"close " + alias;
        mciSendStringW(command.c_str(), nullptr, 0, nullptr);
    }
    CloseHandle(parameters->stopEvent);
    CloseHandle(parameters->muteEvent);
    PostMessageW(parameters->notifyWindow, parameters->notifyMessage, static_cast<WPARAM>(parameters->widgetId),
        static_cast<LPARAM>(parameters->generation));
    return 0;
}

/// Starts an audio worker with independent stop and mute handles and a shared live volume value.
/// On success, transfers the returned event handles to the caller; the worker owns duplicate handles.
bool StartAudioPlaybackAsync(const std::wstring& path, bool loop, bool muted, const std::shared_ptr<std::atomic<int>>&
    volume, HWND notifyWindow, UINT notifyMessage, int widgetId, ULONG generation, HANDLE* stopEvent, HANDLE* muteEvent) {
    if (stopEvent == nullptr || muteEvent == nullptr) {
        return false;
    }
    HANDLE ownerEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (ownerEvent == nullptr) {
        return false;
    }
    HANDLE ownerMuteEvent = CreateEventW(nullptr, TRUE, muted, nullptr);
    if (ownerMuteEvent == nullptr) {
        CloseHandle(ownerEvent);
        return false;
    }
    HANDLE workerEvent = nullptr;
    if (!DuplicateHandle(GetCurrentProcess(), ownerEvent, GetCurrentProcess(), &workerEvent, 0, FALSE,
        DUPLICATE_SAME_ACCESS)) {
        CloseHandle(ownerEvent);
        CloseHandle(ownerMuteEvent);
        return false;
    }
    HANDLE workerMuteEvent = nullptr;
    if (!DuplicateHandle(GetCurrentProcess(), ownerMuteEvent, GetCurrentProcess(), &workerMuteEvent, 0, FALSE,
        DUPLICATE_SAME_ACCESS)) {
        CloseHandle(workerEvent);
        CloseHandle(ownerEvent);
        CloseHandle(ownerMuteEvent);
        return false;
    }
    std::unique_ptr<AudioThreadParameters> parameters(new AudioThreadParameters());
    parameters->path = path;
    parameters->loop = loop;
    parameters->volume = volume;
    parameters->stopEvent = workerEvent;
    parameters->muteEvent = workerMuteEvent;
    parameters->notifyWindow = notifyWindow;
    parameters->notifyMessage = notifyMessage;
    parameters->widgetId = widgetId;
    parameters->generation = generation;
    HANDLE thread = CreateThread(nullptr, 0, AudioThreadProc, parameters.get(), 0, nullptr);
    if (thread == nullptr) {
        CloseHandle(workerMuteEvent);
        CloseHandle(workerEvent);
        CloseHandle(ownerEvent);
        CloseHandle(ownerMuteEvent);
        return false;
    }
    parameters.release();
    CloseHandle(thread);
    *stopEvent = ownerEvent;
    *muteEvent = ownerMuteEvent;
    return true;
}

/// Signals or resets an existing mute event without stopping playback; ignores a null handle.
void SetAudioPlaybackMuted(HANDLE muteEvent, bool muted) {
    if (muteEvent == nullptr) {
        return;
    }
    if (muted) {
        SetEvent(muteEvent);
    } else {
        ResetEvent(muteEvent);
    }
}

/// Opens the supplied command through the shell and releases the worker parameters.
static DWORD WINAPI LocalCommandThreadProc(void* parameter) {
    std::unique_ptr<LocalCommandThreadParameters> parameters(static_cast<LocalCommandThreadParameters*>(parameter));
    ShellExecuteW(nullptr, L"open", parameters->command.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
    return 0;
}

/// Starts a detached shell-launch worker; releases its parameters if thread creation fails.
void StartLocalCommandAsync(const std::wstring& command) {
    std::unique_ptr<LocalCommandThreadParameters> parameters(new LocalCommandThreadParameters());
    parameters->command = command;
    HANDLE thread = CreateThread(nullptr, 0, LocalCommandThreadProc, parameters.get(), 0, nullptr);
    if (thread != nullptr) {
        parameters.release();
        CloseHandle(thread);
    }
}

/// Invokes the supplied URL with a WinHTTP GET request and releases all request handles and worker parameters.
static DWORD WINAPI RemoteScriptThreadProc(void* parameter) {
    std::unique_ptr<RemoteScriptThreadParameters> parameters(static_cast<RemoteScriptThreadParameters*>(parameter));
    URL_COMPONENTSW components = {};
    components.dwStructSize = sizeof(components);
    components.dwHostNameLength = static_cast<DWORD>(-1);
    components.dwUrlPathLength = static_cast<DWORD>(-1);
    components.dwExtraInfoLength = static_cast<DWORD>(-1);
    if (!WinHttpCrackUrl(parameters->url.c_str(), 0, 0, &components)) {
        return 0;
    }
    if (components.lpszHostName == nullptr || components.dwHostNameLength == 0) {
        return 0;
    }
    std::wstring host(components.lpszHostName, components.dwHostNameLength);
    std::wstring path;
    if (components.lpszUrlPath != nullptr && components.dwUrlPathLength != 0) {
        path.assign(components.lpszUrlPath, components.dwUrlPathLength);
    }
    if (components.lpszExtraInfo != nullptr && components.dwExtraInfoLength != 0) {
        path.append(components.lpszExtraInfo, components.dwExtraInfoLength);
    }
    if (path.empty()) {
        path = L"/";
    }
    HINTERNET session = WinHttpOpen(L"CalClock/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS, 0);
    if (session == nullptr) {
        return 0;
    }
    WinHttpSetTimeouts(session, 5000, 5000, 5000, 5000);
    HINTERNET connection = WinHttpConnect(session, host.c_str(), components.nPort, 0);
    DWORD flags = components.nScheme == INTERNET_SCHEME_HTTPS ? WINHTTP_FLAG_SECURE : 0;
    HINTERNET request = nullptr;
    if (connection != nullptr) {
        request = WinHttpOpenRequest(connection, L"GET", path.c_str(), nullptr, WINHTTP_NO_REFERER,
            WINHTTP_DEFAULT_ACCEPT_TYPES, flags);
    }
    if (request != nullptr
            && WinHttpSendRequest(request, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0)) {
        WinHttpReceiveResponse(request, nullptr);
    }
    if (request != nullptr) {
        WinHttpCloseHandle(request);
    }
    if (connection != nullptr) {
        WinHttpCloseHandle(connection);
    }
    WinHttpCloseHandle(session);
    return 0;
}

/// Validates an HTTP or HTTPS URL and starts a detached request worker when valid.
void StartRemoteScriptAsync(const std::wstring& url) {
    if (!IsRemoteScriptUrlValid(url)) {
        return;
    }
    std::unique_ptr<RemoteScriptThreadParameters> parameters(new RemoteScriptThreadParameters());
    parameters->url = url;
    HANDLE thread = CreateThread(nullptr, 0, RemoteScriptThreadProc, parameters.get(), 0, nullptr);
    if (thread != nullptr) {
        parameters.release();
        CloseHandle(thread);
    }
}
