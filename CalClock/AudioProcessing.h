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

/// Carries playback options, shared volume, stop and mute events, and completion notification details.
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

/// Describes a validated PCM or IEEE floating-point sample layout, including valid bits and frame alignment.
struct AudioSampleFormat {
    WORD tag = 0;
    WORD bits = 0;
    WORD validBits = 0;
    WORD blockAlign = 0;
};

/// Converts the current alarm level to linear sample gain, treating -18 dB as unity and the minimum as silence.
double AudioPlaybackGain(const AudioThreadParameters& parameters);
/// Validates a wave-format buffer and extracts the supported PCM or IEEE floating-point layout.
/// Returns false for truncated, inconsistent, or unsupported formats; use format only on success.
bool GetAudioSampleFormat(const BYTE* data, ULONG size, AudioSampleFormat& format);
/// Applies linear gain in place to complete sample frames using a validated format.
/// Clamps amplified samples to the representable range and writes format-correct silence for zero gain.
HRESULT ApplyAudioGain(BYTE* data, size_t length, const AudioSampleFormat& format, double gain);
/// Releases the COM-allocated format buffer and optional interface, then clears the media type.
void FreeAudioMediaType(AM_MEDIA_TYPE& type);
