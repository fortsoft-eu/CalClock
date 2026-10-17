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
#include "../CalClock/ClockTime.h"
#include <cstdio>
#include <cstdlib>

static const ULONGLONG TEST_UTC = 132000000000000000ULL;
static ULONGLONG systemTime = TEST_UTC;
static LONGLONG counter = 0;
static LONGLONG frequency = 10000000;
static int frequencyReads = 0;
static int systemReads = 0;

static BOOL WINAPI TestPerformanceFrequency(LARGE_INTEGER* value);
static BOOL WINAPI TestPerformanceCounter(LARGE_INTEGER* value);
static HMODULE WINAPI TestGetModuleHandle(LPCWSTR name);
static void WINAPI TestSystemTime(FILETIME* value);

#define QueryPerformanceFrequency TestPerformanceFrequency
#define QueryPerformanceCounter TestPerformanceCounter
#define GetModuleHandleW TestGetModuleHandle
#define GetSystemTimeAsFileTime TestSystemTime
#include "../CalClock/ClockTime.cpp"
#undef QueryPerformanceFrequency
#undef QueryPerformanceCounter
#undef GetModuleHandleW
#undef GetSystemTimeAsFileTime

/// Returns the simulated counter frequency and counts queries to verify that initialization reads it only once.
static BOOL WINAPI TestPerformanceFrequency(LARGE_INTEGER* value) {
    frequencyReads++;
    value->QuadPart = frequency;
    return TRUE;
}

/// Returns the counter value controlled by the test without reading or advancing the real performance counter.
static BOOL WINAPI TestPerformanceCounter(LARGE_INTEGER* value) {
    value->QuadPart = counter;
    return TRUE;
}

/// Disables precise-time API lookup so initialization uses the controlled GetSystemTimeAsFileTime replacement.
static HMODULE WINAPI TestGetModuleHandle(LPCWSTR name) {
    return nullptr;
}

/// Writes simulated system UTC as FILETIME ticks and counts reads to detect repeated use of the system clock.
static void WINAPI TestSystemTime(FILETIME* value) {
    systemReads++;
    ULARGE_INTEGER time = {};
    time.QuadPart = systemTime;
    value->dwLowDateTime = time.LowPart;
    value->dwHighDateTime = time.HighPart;
}

/// Writes the failure message to standard error and exits with status 1 when the required condition is false.
static void Require(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "%s\n", message);
        std::exit(1);
    }
}

/// Tests clock-jump independence, simulated sleep, fractional precision, polling drift, and long uptime.
/// Uses the counter frequency supplied in argv[1], or 10 MHz by default; returns 0 if all checks pass.
int main(int argc, char** argv) {
    if (argc > 1) {
        frequency = _strtoi64(argv[1], nullptr, 10);
    }
    Require(frequency > 0, "Invalid test frequency");
    ULONGLONG tolerance = (CLOCK_TICKS_PER_SECOND + frequency - 1) / frequency;
    Require(MonotonicFileTimeValue() == TEST_UTC, "Initial epoch mismatch");
    systemTime += 90 * CLOCK_TICKS_PER_SECOND;
    counter += frequency;
    Require(MonotonicFileTimeValue() == TEST_UTC + CLOCK_TICKS_PER_SECOND, "Forward system jump changed ticks");
    systemTime -= 180 * CLOCK_TICKS_PER_SECOND;
    counter += frequency;
    Require(MonotonicFileTimeValue() == TEST_UTC + 2 * CLOCK_TICKS_PER_SECOND, "Backward system jump changed ticks");
    counter = 86400LL * frequency + frequency / 8;
    Require(std::llabs(static_cast<LONGLONG>(MonotonicFileTimeValue() - TEST_UTC
        - 86400ULL * CLOCK_TICKS_PER_SECOND) - 1250000) <= static_cast<LONGLONG>(tolerance),
        "Sleep interval or fractional conversion mismatch");
    for (LONGLONG index = 0; index < 100000; index++) {
        counter = index * frequency / 100;
        Require(std::llabs(static_cast<LONGLONG>(MonotonicFileTimeValue() - TEST_UTC) - index * 100000)
            <= static_cast<LONGLONG>(tolerance), "Repeated reads accumulated drift");
    }
    counter = 400LL * 86400 * frequency;
    Require(MonotonicFileTimeValue() == TEST_UTC + 400ULL * 86400 * CLOCK_TICKS_PER_SECOND,
        "Long uptime overflowed counter conversion");
    Require(frequencyReads == 1 && systemReads == 1, "Continuous clock reread the system clock or frequency");
    std::printf("PASS: clock jumps, sleep, fractional precision, polling drift, long uptime at %lld Hz\n", frequency);
    return 0;
}
