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

#include "CalClockTypes.h"
#include <atomic>
#include <string>

/// Carries an NTP query generation, success state, selected server, and clock offset back to the UI thread.
struct NtpThreadResult {
    bool success = false;
    LONGLONG offset100Nanoseconds = 0;
    std::wstring server;
    ULONG generation = 0;
};

/// Returns the preset's server list, resolving the automatic preset from the user's region.
/// Returns an empty string for the custom preset.
std::wstring NtpServersForPreset(int preset);
/// Reports whether the server list contains at least one accepted server name.
bool HasNtpServers(const std::wstring& serverList);
/// Returns current UTC as Windows FILETIME ticks, using the precise system clock when available.
ULONGLONG CurrentFileTimeValue();
/// Starts an NTP worker and returns its thread handle, or null on failure.
/// The caller owns the handle and must keep both atomic flags alive until the worker exits; the receiver owns posted
/// results.
HANDLE StartNtpQueryThread(const std::wstring& serverList, ULONG generation, HWND notifyWindow, UINT notifyMessage, std::atomic<bool>* stopRequested,
    std::atomic<bool>* queryRunning);
