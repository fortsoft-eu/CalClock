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
 * Last modified for version 1.6.0.0
 */

#define NOMINMAX
#include "ClockTime.h"

using GetPreciseTimeProc = VOID(WINAPI*)(LPFILETIME fileTime);

/// Pairs the initial UTC reading with its performance-counter reference and fixed counter frequency.
struct ClockTimeReference {
    ULONGLONG utc = 0;
    LONGLONG counter = 0;
    LONGLONG frequency = 0;
};

static const ULONGLONG CLOCK_TICKS_PER_SECOND = 10000000;

/// Resolves the precise-time function from the loaded kernel32 module, returning null when it is unavailable.
static GetPreciseTimeProc ResolvePreciseTimeProc() {
    HMODULE kernel = GetModuleHandleW(L"kernel32.dll");
    GetPreciseTimeProc procedure = nullptr;
    if (kernel != nullptr) {
        procedure = reinterpret_cast<GetPreciseTimeProc>(GetProcAddress(kernel, "GetSystemTimePreciseAsFileTime"));
    }
    return procedure;
}

/// Returns current UTC as Windows FILETIME ticks, using the precise system clock when available.
ULONGLONG CurrentFileTimeValue() {
    FILETIME fileTime = {};
    static const GetPreciseTimeProc getPreciseTime = ResolvePreciseTimeProc();
    if (getPreciseTime != nullptr) {
        getPreciseTime(&fileTime);
    } else {
        GetSystemTimeAsFileTime(&fileTime);
    }
    ULARGE_INTEGER value = {};
    value.LowPart = fileTime.dwLowDateTime;
    value.HighPart = fileTime.dwHighDateTime;
    return value.QuadPart;
}

/// Captures the system UTC epoch and the performance-counter state once for the process's continuous timeline.
static ClockTimeReference CreateClockTimeReference() {
    ClockTimeReference reference;
    LARGE_INTEGER frequency = {};
    QueryPerformanceFrequency(&frequency);
    reference.frequency = frequency.QuadPart;
    reference.utc = CurrentFileTimeValue();
    LARGE_INTEGER counter = {};
    QueryPerformanceCounter(&counter);
    reference.counter = counter.QuadPart;
    return reference;
}

/// Returns a continuous FILETIME timeline anchored once to system UTC and advanced by QueryPerformanceCounter.
/// Subsequent system-clock adjustments do not change this timeline; elapsed time includes system sleep.
ULONGLONG MonotonicFileTimeValue() {
    static const ClockTimeReference reference = CreateClockTimeReference();
    LARGE_INTEGER counter = {};
    QueryPerformanceCounter(&counter);
    ULONGLONG elapsed = static_cast<ULONGLONG>(counter.QuadPart - reference.counter);
    ULONGLONG frequency = static_cast<ULONGLONG>(reference.frequency);
    return reference.utc
        + elapsed / frequency * CLOCK_TICKS_PER_SECOND
        + elapsed % frequency * CLOCK_TICKS_PER_SECOND / frequency;
}
