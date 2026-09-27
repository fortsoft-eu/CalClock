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

#include <windows.h>
#include <dshow.h>
#include <atomic>
#include <cstddef>
#include <memory>
#include <string>

struct AudioThreadParameters {
    std::wstring path;
    bool loop = false;
    std::shared_ptr<std::atomic<int>> volume;
    HANDLE stopEvent = nullptr;
    HANDLE muteEvent = nullptr;
    HWND notifyWindow = nullptr;
    UINT notifyMessage = 0;
    int widgetId = -1;
    ULONG generation = 0;
};

struct AudioSampleFormat {
    WORD tag = 0;
    WORD bits = 0;
    WORD validBits = 0;
    WORD blockAlign = 0;
};

double AudioPlaybackGain(const AudioThreadParameters& parameters);
bool GetAudioSampleFormat(const BYTE* data, ULONG size, AudioSampleFormat& format);
HRESULT ApplyAudioGain(BYTE* data, size_t length, const AudioSampleFormat& format, double gain);
void FreeAudioMediaType(AM_MEDIA_TYPE& type);
