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

#pragma once

#include <windows.h>
#include <string>
#include <vector>

/// Identifies an installed waveform output by its persistent Windows endpoint ID and display name.
struct AudioOutputDevice {
    std::wstring id;
    std::wstring name;
};

/// Lists currently available waveform outputs with their persistent endpoint IDs and full Windows names.
std::vector<AudioOutputDevice> EnumerateAudioOutputDevices();

/// Resolves an endpoint to its current waveOut index; an empty ID selects the current Windows default.
/// Returns false when the selected output is unavailable, without redirecting sound to another device.
bool ResolveAudioOutputDevice(const std::wstring& requested, std::wstring* endpoint, UINT* deviceId);
