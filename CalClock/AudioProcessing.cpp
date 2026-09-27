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
#include "AudioProcessing.h"
#include "CalClockTypes.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <mmreg.h>

#pragma comment(lib, "Ole32.lib")
#pragma comment(lib, "Strmiids.lib")

static bool IsAudioMuted(HANDLE muteEvent) {
    return muteEvent != nullptr && WaitForSingleObject(muteEvent, 0) == WAIT_OBJECT_0;
}

static int AudioPlaybackVolume(const AudioThreadParameters& parameters) {
    if (IsAudioMuted(parameters.muteEvent)) {
        return ALARM_VOLUME_MIN;
    }
    return parameters.volume == nullptr ? ALARM_VOLUME_DEFAULT : std::clamp(parameters.volume->load(), ALARM_VOLUME_MIN, ALARM_VOLUME_MAX);
}

double AudioPlaybackGain(const AudioThreadParameters& parameters) {
    int volume = AudioPlaybackVolume(parameters);
    return volume == ALARM_VOLUME_MIN ? 0.0 : std::pow(10.0, (volume - ALARM_VOLUME_UNITY) / 2000.0);
}

bool GetAudioSampleFormat(const BYTE* data, ULONG size, AudioSampleFormat& format) {
    if (data == nullptr || size < sizeof(PCMWAVEFORMAT)) {
        return false;
    }
    WAVEFORMATEX wave = {};
    std::memcpy(&wave, data, std::min<size_t>(size, sizeof(wave)));
    format.tag = wave.wFormatTag;
    format.bits = wave.wBitsPerSample;
    format.validBits = wave.wBitsPerSample;
    format.blockAlign = wave.nBlockAlign;
    if (wave.wFormatTag == WAVE_FORMAT_EXTENSIBLE) {
        if (size < sizeof(WAVEFORMATEXTENSIBLE) || wave.cbSize < sizeof(WAVEFORMATEXTENSIBLE) - sizeof(WAVEFORMATEX)) {
            return false;
        }
        WAVEFORMATEXTENSIBLE extended = {};
        std::memcpy(&extended, data, sizeof(extended));
        if (extended.SubFormat == MEDIASUBTYPE_PCM) {
            format.tag = WAVE_FORMAT_PCM;
        } else if (extended.SubFormat == MEDIASUBTYPE_IEEE_FLOAT) {
            format.tag = WAVE_FORMAT_IEEE_FLOAT;
        } else {
            return false;
        }
        if (extended.Samples.wValidBitsPerSample != 0) {
            format.validBits = extended.Samples.wValidBitsPerSample;
        }
    }
    if (wave.nChannels == 0 || wave.nSamplesPerSec == 0 || format.blockAlign != wave.nChannels * (format.bits / 8)) {
        return false;
    }
    if (format.tag == WAVE_FORMAT_IEEE_FLOAT) {
        return (format.bits == 32 || format.bits == 64) && format.validBits == format.bits;
    }
    return format.tag == WAVE_FORMAT_PCM && format.validBits > 0 && format.validBits <= format.bits
        && (format.bits == 8 || format.bits == 16 || format.bits == 24 || format.bits == 32);
}

HRESULT ApplyAudioGain(BYTE* data, size_t length, const AudioSampleFormat& format, double gain) {
    if (data == nullptr || format.blockAlign == 0 || length % format.blockAlign != 0) {
        return E_INVALIDARG;
    }
    if (gain == 1.0) {
        return S_OK;
    }
    if (gain == 0.0) {
        std::memset(data, format.tag == WAVE_FORMAT_PCM && format.bits == 8 ? 128 : 0, length);
        return S_OK;
    }
    size_t bytes = format.bits / 8;
    if (format.tag == WAVE_FORMAT_IEEE_FLOAT) {
        for (size_t offset = 0; offset < length; offset += bytes) {
            double value = 0.0;
            if (format.bits == 32) {
                float sample = 0.0f;
                std::memcpy(&sample, data + offset, sizeof(sample));
                value = sample;
            } else {
                std::memcpy(&value, data + offset, sizeof(value));
            }
            value = std::isfinite(value) ? std::clamp(value * gain, -1.0, 1.0) : 0.0;
            if (format.bits == 32) {
                float sample = static_cast<float>(value);
                std::memcpy(data + offset, &sample, sizeof(sample));
            } else {
                std::memcpy(data + offset, &value, sizeof(value));
            }
        }
        return S_OK;
    }
    int signBit = format.bits - 1;
    int validSignBit = format.validBits - 1;
    int paddingBits = format.bits - format.validBits;
    int64_t sign = int64_t{ 1 } << signBit;
    int64_t minimum = -(int64_t{ 1 } << validSignBit);
    int64_t maximum = -minimum - 1;
    int64_t step = int64_t{ 1 } << paddingBits;
    for (size_t offset = 0; offset < length; offset += bytes) {
        int64_t value = 0;
        std::memcpy(&value, data + offset, bytes);
        if (format.bits == 8) {
            value -= 128;
        } else if (value & sign) {
            value -= int64_t{ 1 } << format.bits;
        }
        double scaled = std::clamp(value * gain / step, static_cast<double>(minimum), static_cast<double>(maximum));
        value = std::llround(scaled) * step;
        if (format.bits == 8) {
            value += 128;
        }
        std::memcpy(data + offset, &value, bytes);
    }
    return S_OK;
}

void FreeAudioMediaType(AM_MEDIA_TYPE& type) {
    CoTaskMemFree(type.pbFormat);
    if (type.pUnk != nullptr) {
        type.pUnk->Release();
    }
    type = AM_MEDIA_TYPE{};
}
