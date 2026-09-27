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
 * Last modified for version 1.5.0.0
 */

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "AudioDecoder.h"
#include <mfapi.h>
#include <mferror.h>

#pragma comment(lib, "Mfuuid.lib")
#pragma comment(lib, "Ole32.lib")

AudioDecoder::~AudioDecoder() {
    reader.Reset();
    CoTaskMemFree(wave);
    if (started) {
        shutdown();
    }
    if (readerLibrary != nullptr) {
        FreeLibrary(readerLibrary);
    }
    if (platform != nullptr) {
        FreeLibrary(platform);
    }
}

HRESULT AudioDecoder::Open(const std::wstring& path) {
    wchar_t directory[MAX_PATH] = {};
    UINT length = GetSystemDirectoryW(directory, ARRAYSIZE(directory));
    if (length == 0 || length >= ARRAYSIZE(directory)) {
        return E_FAIL;
    }
    std::wstring platformPath = std::wstring(directory) + L"\\mfplat.dll";
    std::wstring readerPath = std::wstring(directory) + L"\\mfreadwrite.dll";
    platform = LoadLibraryW(platformPath.c_str());
    readerLibrary = LoadLibraryW(readerPath.c_str());
    if (platform == nullptr || readerLibrary == nullptr) {
        return E_NOINTERFACE;
    }
    startup = reinterpret_cast<decltype(startup)>(GetProcAddress(platform, "MFStartup"));
    shutdown = reinterpret_cast<decltype(shutdown)>(GetProcAddress(platform, "MFShutdown"));
    createType = reinterpret_cast<decltype(createType)>(GetProcAddress(platform, "MFCreateMediaType"));
    createWaveFormat = reinterpret_cast<decltype(createWaveFormat)>(GetProcAddress(platform, "MFCreateWaveFormatExFromMFMediaType"));
    createReader = reinterpret_cast<decltype(createReader)>(GetProcAddress(readerLibrary, "MFCreateSourceReaderFromURL"));
    if (startup == nullptr || shutdown == nullptr || createType == nullptr || createWaveFormat == nullptr || createReader == nullptr) {
        return E_NOINTERFACE;
    }
    HRESULT result = startup(MF_VERSION, MFSTARTUP_FULL);
    started = SUCCEEDED(result);
    if (SUCCEEDED(result)) {
        result = createReader(path.c_str(), nullptr, &reader);
    }
    if (SUCCEEDED(result)) {
        result = reader->SetStreamSelection(static_cast<DWORD>(MF_SOURCE_READER_ALL_STREAMS), FALSE);
    }
    if (SUCCEEDED(result)) {
        result = reader->SetStreamSelection(static_cast<DWORD>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), TRUE);
    }
    Microsoft::WRL::ComPtr<IMFMediaType> type;
    if (SUCCEEDED(result)) {
        result = createType(&type);
    }
    if (SUCCEEDED(result)) {
        result = type->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
    }
    if (SUCCEEDED(result)) {
        result = type->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
    }
    if (SUCCEEDED(result)) {
        result = reader->SetCurrentMediaType(static_cast<DWORD>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), nullptr, type.Get());
    }
    if (SUCCEEDED(result)) {
        result = reader->GetCurrentMediaType(static_cast<DWORD>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), type.ReleaseAndGetAddressOf());
    }
    UINT32 size = 0;
    if (SUCCEEDED(result)) {
        result = createWaveFormat(type.Get(), &wave, &size, MFWaveFormatExConvertFlag_Normal);
    }
    if (SUCCEEDED(result) && !GetAudioSampleFormat(reinterpret_cast<BYTE*>(wave), size, format)) {
        result = MF_E_INVALIDMEDIATYPE;
    }
    return result;
}

HRESULT AudioDecoder::Read(std::vector<BYTE>& data, bool& end) {
    Microsoft::WRL::ComPtr<IMFSample> sample;
    DWORD flags = 0;
    HRESULT result = reader->ReadSample(static_cast<DWORD>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), 0, nullptr, &flags, nullptr, &sample);
    if (FAILED(result)) {
        return result;
    }
    if (flags & MF_SOURCE_READERF_ERROR) {
        return E_FAIL;
    }
    if (flags & MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED) {
        Microsoft::WRL::ComPtr<IMFMediaType> type;
        WAVEFORMATEX* changedWave = nullptr;
        UINT32 size = 0;
        result = reader->GetCurrentMediaType(static_cast<DWORD>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), &type);
        if (SUCCEEDED(result)) {
            result = createWaveFormat(type.Get(), &changedWave, &size, MFWaveFormatExConvertFlag_Normal);
        }
        bool sameFormat = SUCCEEDED(result)
            && changedWave->nSamplesPerSec == wave->nSamplesPerSec
            && changedWave->nChannels == wave->nChannels
            && changedWave->wBitsPerSample == wave->wBitsPerSample
            && changedWave->wFormatTag == wave->wFormatTag
            && changedWave->nBlockAlign == wave->nBlockAlign;
        CoTaskMemFree(changedWave);
        if (!sameFormat) {
            return MF_E_INVALIDMEDIATYPE;
        }
    }
    end = (flags & MF_SOURCE_READERF_ENDOFSTREAM) != 0;
    data.clear();
    if (sample == nullptr) {
        return S_OK;
    }
    Microsoft::WRL::ComPtr<IMFMediaBuffer> buffer;
    result = sample->ConvertToContiguousBuffer(&buffer);
    if (FAILED(result)) {
        return result;
    }
    BYTE* source = nullptr;
    DWORD length = 0;
    result = buffer->Lock(&source, nullptr, &length);
    if (SUCCEEDED(result)) {
        data.assign(source, source + length);
        buffer->Unlock();
    }
    return result;
}

HRESULT AudioDecoder::Restart(const std::wstring& path) {
    Microsoft::WRL::ComPtr<IMFMediaType> type;
    HRESULT result = reader->GetCurrentMediaType(static_cast<DWORD>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), &type);
    Microsoft::WRL::ComPtr<IMFSourceReader> replacement;
    if (SUCCEEDED(result)) {
        result = createReader(path.c_str(), nullptr, &replacement);
    }
    if (SUCCEEDED(result)) {
        result = replacement->SetStreamSelection(static_cast<DWORD>(MF_SOURCE_READER_ALL_STREAMS), FALSE);
    }
    if (SUCCEEDED(result)) {
        result = replacement->SetStreamSelection(static_cast<DWORD>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), TRUE);
    }
    if (SUCCEEDED(result)) {
        result = replacement->SetCurrentMediaType(static_cast<DWORD>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), nullptr, type.Get());
    }
    if (SUCCEEDED(result)) {
        reader = replacement;
    }
    return result;
}

const WAVEFORMATEX* AudioDecoder::GetWaveFormat() const {
    return wave;
}

const AudioSampleFormat& AudioDecoder::GetSampleFormat() const {
    return format;
}
