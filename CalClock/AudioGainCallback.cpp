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
#include "AudioGainCallback.h"

/// Retains a reference to playback parameters and copies the initial decoded sample format.
AudioGainCallback::AudioGainCallback(const AudioThreadParameters& parameters, const AudioSampleFormat& format) : parameters(parameters), format(format) {}

/// Returns an AddRef'd IUnknown or sample callback interface; rejects unsupported IDs and null output pointers.
HRESULT STDMETHODCALLTYPE AudioGainCallback::QueryInterface(REFIID id, void** object) {
    if (object == nullptr) {
        return E_POINTER;
    }
    *object = nullptr;
    if (id != IID_IUnknown && id != __uuidof(IAudioSampleCallback)) {
        return E_NOINTERFACE;
    }
    *object = static_cast<IAudioSampleCallback*>(this);
    AddRef();
    return S_OK;
}

/// Atomically increments and returns the COM reference count.
ULONG STDMETHODCALLTYPE AudioGainCallback::AddRef() {
    return ++references;
}

/// Atomically decrements the COM reference count and deletes the callback when it reaches zero.
ULONG STDMETHODCALLTYPE AudioGainCallback::Release() {
    ULONG remaining = --references;
    if (remaining == 0) {
        delete this;
    }
    return remaining;
}

/// Validates sample format changes and applies the current playback gain directly to the sample data.
HRESULT STDMETHODCALLTYPE AudioGainCallback::SampleCB(double, IMediaSample* sample) {
    if (sample == nullptr) {
        return E_POINTER;
    }
    AM_MEDIA_TYPE* changedType = nullptr;
    if (sample->GetMediaType(&changedType) == S_OK && changedType != nullptr) {
        bool supported = changedType->majortype == MEDIATYPE_Audio && changedType->formattype == FORMAT_WaveFormatEx
            && GetAudioSampleFormat(changedType->pbFormat, changedType->cbFormat, format);
        FreeAudioMediaType(*changedType);
        CoTaskMemFree(changedType);
        if (!supported) {
            return VFW_E_INVALIDMEDIATYPE;
        }
    }
    BYTE* data = nullptr;
    HRESULT result = sample->GetPointer(&data);
    long length = sample->GetActualDataLength();
    if (FAILED(result) || length < 0) {
        return E_FAIL;
    }
    return ApplyAudioGain(data, static_cast<size_t>(length), format, AudioPlaybackGain(parameters));
}

/// Returns E_NOTIMPL because gain processing uses the sample callback interface.
HRESULT STDMETHODCALLTYPE AudioGainCallback::BufferCB(double, BYTE*, long) {
    return E_NOTIMPL;
}
