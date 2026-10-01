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

#include "IAudioSampleCallback.h"

/// Declares the legacy DirectShow Sample Grabber interface for configuring sample delivery and callbacks.
struct __declspec(uuid("6B652FFF-11FE-4FCE-92AD-0266B5D7C78F")) IAudioSampleGrabber : IUnknown {

    /// Enables or disables stopping the graph after one sample has been delivered.
    virtual HRESULT STDMETHODCALLTYPE SetOneShot(BOOL oneShot) = 0;

    /// Constrains the media type accepted by the Sample Grabber.
    virtual HRESULT STDMETHODCALLTYPE SetMediaType(const AM_MEDIA_TYPE* type) = 0;

    /// Copies the connected media type to the caller, which must release its format buffer and interface.
    virtual HRESULT STDMETHODCALLTYPE GetConnectedMediaType(AM_MEDIA_TYPE* type) = 0;

    /// Enables or disables retaining the latest sample for buffer retrieval.
    virtual HRESULT STDMETHODCALLTYPE SetBufferSamples(BOOL bufferSamples) = 0;

    /// Reports the required byte count or copies the retained sample into the caller's buffer.
    virtual HRESULT STDMETHODCALLTYPE GetCurrentBuffer(long* size, long* buffer) = 0;

    /// Returns an AddRef'd reference to the retained media sample, which the caller must release.
    virtual HRESULT STDMETHODCALLTYPE GetCurrentSample(IMediaSample** sample) = 0;

    /// Registers a callback and selects SampleCB with method 0 or BufferCB with method 1.
    virtual HRESULT STDMETHODCALLTYPE SetCallback(IAudioSampleCallback* callback, long method) = 0;
};
