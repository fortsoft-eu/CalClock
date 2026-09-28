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

#pragma once

#include "AudioProcessing.h"
#include "IAudioSampleCallback.h"

/// Applies live alarm gain and mute state to DirectShow samples through a reference-counted COM callback.
/// The referenced playback parameters must outlive the callback.
class AudioGainCallback final : public IAudioSampleCallback {
public:
    /// Retains a reference to playback parameters and copies the initial decoded sample format.
    AudioGainCallback(const AudioThreadParameters& parameters, const AudioSampleFormat& format);
    /// Returns an AddRef'd IUnknown or sample callback interface; rejects unsupported IDs and null output pointers.
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID id, void** object) override;
    /// Atomically increments and returns the COM reference count.
    ULONG STDMETHODCALLTYPE AddRef() override;
    /// Atomically decrements the COM reference count and deletes the callback when it reaches zero.
    ULONG STDMETHODCALLTYPE Release() override;
    /// Validates sample format changes and applies the current playback gain directly to the sample data.
    HRESULT STDMETHODCALLTYPE SampleCB(double time, IMediaSample* sample) override;
    /// Returns E_NOTIMPL because gain processing uses the sample callback interface.
    HRESULT STDMETHODCALLTYPE BufferCB(double time, BYTE* buffer, long length) override;

private:
    std::atomic<ULONG> references = 1;
    const AudioThreadParameters& parameters;
    AudioSampleFormat format;
};
