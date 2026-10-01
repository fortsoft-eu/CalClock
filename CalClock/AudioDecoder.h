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

#pragma once

#include "AudioProcessing.h"
#include <mfidl.h>
#include <mfreadwrite.h>
#include <vector>
#include <wrl/client.h>

/// Decodes the first audio stream to PCM using dynamically loaded Media Foundation APIs.
/// Owns the source reader, output format, and library handles; COM must be initialized by the caller.
class AudioDecoder {

public:
    /// Creates an unopened decoder without loading Media Foundation.
    AudioDecoder() = default;

    /// Prevents copying ownership of the decoder and Media Foundation resources.
    AudioDecoder(const AudioDecoder&) = delete;

    /// Prevents copying ownership of the decoder and Media Foundation resources.
    AudioDecoder& operator=(const AudioDecoder&) = delete;

    /// Releases the reader and wave format, shuts down Media Foundation, and unloads its libraries.
    ~AudioDecoder();

    /// Loads Media Foundation and opens the first audio stream with a supported PCM output format.
    /// Call once on a new decoder; returns a failing HRESULT if loading, decoding, or format negotiation fails.
    HRESULT Open(const std::wstring& path);

    /// Reads the next decoded block after Open succeeds and reports the end-of-stream flag through end.
    /// Returns a failing HRESULT for decoding errors or an incompatible midstream format change.
    HRESULT Read(std::vector<BYTE>& data, bool& end);

    /// Reopens the audio stream at its beginning using the negotiated output format.
    /// Replaces the current reader only on success, avoiding reliance on decoder seek support.
    HRESULT Restart(const std::wstring& path);

    /// Returns the decoder-owned wave format, or null before a format has been obtained.
    const WAVEFORMATEX* GetWaveFormat() const;

    /// Returns the sample layout established by a successful Open call.
    const AudioSampleFormat& GetSampleFormat() const;

private:
    HMODULE platform = nullptr;
    HMODULE readerLibrary = nullptr;
    HRESULT(WINAPI* startup)(ULONG, DWORD) = nullptr;
    HRESULT(WINAPI* shutdown)() = nullptr;
    HRESULT(WINAPI* createType)(IMFMediaType**) = nullptr;
    HRESULT(WINAPI* createReader)(LPCWSTR, IMFAttributes*, IMFSourceReader**) = nullptr;
    HRESULT(WINAPI* createWaveFormat)(IMFMediaType*, WAVEFORMATEX**, UINT32*, UINT32) = nullptr;
    Microsoft::WRL::ComPtr<IMFSourceReader> reader;
    AudioSampleFormat format;
    WAVEFORMATEX* wave = nullptr;
    bool started = false;
};
