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
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include "../CalClock/NtpClient.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

static const ULONGLONG TEST_NOW = 132000000000000000ULL;
static const LONGLONG TEST_CORRECTION = 1234567;
static ULONGLONG monotonicTime = TEST_NOW;
static ULONGLONG systemTime = TEST_NOW;
static ULONGLONG sendTime = 0;
static LONGLONG systemJumpOnReceive = 0;
static BYTE lastRequest[48] = {};
static ADDRINFOW testAddress = {};
static NtpThreadResult* capturedResult = nullptr;
static bool invalidReply = false;

static int WSAAPI TestGetAddrInfo(PCWSTR node, PCWSTR service, const ADDRINFOW* hints, PADDRINFOW* result);
static void WSAAPI TestFreeAddrInfo(PADDRINFOW address);
static SOCKET WSAAPI TestSocket(int family, int type, int protocol);
static int WSAAPI TestConnect(SOCKET handle, const sockaddr* address, int length);
static int WSAAPI TestSetSocketOption(SOCKET handle, int level, int option, const char* value, int length);
static int WSAAPI TestSend(SOCKET handle, const char* buffer, int length, int flags);
static int WSAAPI TestReceive(SOCKET handle, char* buffer, int length, int flags);
static int WSAAPI TestCloseSocket(SOCKET handle);
static BOOL WINAPI TestPostMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

#include "../CalClock/CalClock.cpp"
#define GetAddrInfoW TestGetAddrInfo
#define FreeAddrInfoW TestFreeAddrInfo
#define socket TestSocket
#define connect TestConnect
#define setsockopt TestSetSocketOption
#define send TestSend
#define recv TestReceive
#define closesocket TestCloseSocket
#define PostMessageW TestPostMessage
#include "../CalClock/NtpClient.cpp"
#undef GetAddrInfoW
#undef FreeAddrInfoW
#undef socket
#undef connect
#undef setsockopt
#undef send
#undef recv
#undef closesocket
#undef PostMessageW
#include "../CalClock/TimeSignal.cpp"

/// Returns simulated Windows UTC in 100-nanosecond FILETIME ticks, including system-clock jumps made by the test.
ULONGLONG CurrentFileTimeValue() {
    return systemTime;
}

/// Returns the independently advanced simulated continuous clock in 100-nanosecond FILETIME ticks.
ULONGLONG MonotonicFileTimeValue() {
    return monotonicTime;
}

/// Returns the shared fake server address without DNS lookup; the caller borrows it rather than owning it.
static int WSAAPI TestGetAddrInfo(PCWSTR node, PCWSTR service, const ADDRINFOW* hints, PADDRINFOW* result) {
    *result = &testAddress;
    return 0;
}

/// Leaves the shared fake address intact because the resolver replacement does not allocate address records.
static void WSAAPI TestFreeAddrInfo(PADDRINFOW address) {}

/// Returns a fixed fake socket handle without creating an operating-system socket.
static SOCKET WSAAPI TestSocket(int family, int type, int protocol) {
    return 1;
}

/// Reports a successful connection for the fake socket without contacting a server.
static int WSAAPI TestConnect(SOCKET handle, const sockaddr* address, int length) {
    return 0;
}

/// Accepts socket options for the simulated exchange without configuring a real socket.
static int WSAAPI TestSetSocketOption(SOCKET handle, int level, int option, const char* value, int length) {
    return 0;
}

/// Saves the 48-byte NTP request and its continuous-clock send time, then reports success without transmission.
static int WSAAPI TestSend(SOCKET handle, const char* buffer, int length, int flags) {
    std::memcpy(lastRequest, buffer, sizeof(lastRequest));
    sendTime = monotonicTime;
    return length;
}

/// Builds a valid or deliberately invalid 48-byte NTP reply using the saved request and fixed server correction.
/// Advances simulated time by 12 ms and applies the requested system-clock jump during receipt.
static int WSAAPI TestReceive(SOCKET handle, char* buffer, int length, int flags) {
    BYTE response[48] = {};
    response[0] = invalidReply ? 0xE4 : 0x24;
    response[1] = 1;
    std::memcpy(response + 24, lastRequest + 40, 8);
    WriteNtpTimestamp(response + 32, sendTime + TEST_CORRECTION + 50000);
    WriteNtpTimestamp(response + 40, sendTime + TEST_CORRECTION + 70000);
    monotonicTime += 120000;
    systemTime = static_cast<ULONGLONG>(static_cast<LONGLONG>(systemTime) + 120000 + systemJumpOnReceive);
    std::memcpy(buffer, response, sizeof(response));
    return sizeof(response);
}

/// Reports successful closure of the fake socket without releasing an operating-system resource.
static int WSAAPI TestCloseSocket(SOCKET handle) {
    return 0;
}

/// Captures the worker result instead of queuing a window message so the test controls when it is delivered.
static BOOL WINAPI TestPostMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    capturedResult = reinterpret_cast<NtpThreadResult*>(lParam);
    return TRUE;
}

/// Writes the failure message to standard error and exits with status 1 when the required condition is false.
static void Require(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "%s\n", message);
        std::exit(1);
    }
}

/// Runs the NTP worker synchronously against two fake servers with the current generation and cancellation flags.
/// Fails the test if the worker does not return a captured result.
static void RunQuery() {
    NtpThreadParameters* parameters = new NtpThreadParameters;
    parameters->serverList = L"one; two";
    parameters->notifyWindow = reinterpret_cast<HWND>(1);
    parameters->generation = ntpGeneration.load();
    parameters->stopRequested = &ntpStopRequested;
    parameters->queryRunning = &ntpQueryRunning;
    NtpThreadProc(parameters);
    Require(capturedResult != nullptr, "NTP worker did not return a result");
}

/// Tests NTP corrections across system-clock jumps, delayed delivery, failed synchronization, and system fallback.
/// Also verifies that time-signal targets and planned tones ignore system-clock jumps; returns 0 on success.
int main() {
    testAddress.ai_family = AF_INET;
    testAddress.ai_socktype = SOCK_DGRAM;
    testAddress.ai_protocol = IPPROTO_UDP;
    const LONGLONG jumps[] = { 0LL, 300000000LL, -300000000LL };
    for (LONGLONG jump : jumps) {
        systemJumpOnReceive = jump;
        RunQuery();
        Require(capturedResult->success, "System-clock change invalidated an NTP query");
        Require(std::llabs(capturedResult->clockOffset100Nanoseconds - TEST_CORRECTION) <= 2,
            "System-clock change contaminated the combined NTP time");
        Require(capturedResult->offset100Nanoseconds == static_cast<LONGLONG>(monotonicTime)
            + capturedResult->clockOffset100Nanoseconds - static_cast<LONGLONG>(systemTime),
            "NTP log offset no longer describes the Windows clock");
        ULONGLONG deliveredTime = monotonicTime + capturedResult->clockOffset100Nanoseconds;
        monotonicTime += 7 * 10000000ULL;
        systemTime += 90 * 10000000ULL;
        WindowProc(nullptr, WM_NTP_RESULT, 0, reinterpret_cast<LPARAM>(capturedResult));
        capturedResult = nullptr;
        Require(GetApplicationFileTimeValue() == deliveredTime + 7 * 10000000ULL,
            "Delayed NTP delivery or a system-clock change shifted application time");
        LONGLONG oldOffset = GetApplicationTimeOffset(monotonicTime);
        ULONGLONG target = 0;
        Require(CalculateTimeSignalTarget(GetApplicationFileTimeValue(), monotonicTime, TIME_SIGNAL_EVERY_MINUTE, &target),
            "Time signal target calculation failed");
        systemTime -= 180 * 10000000ULL;
        ULONGLONG repeatedTarget = 0;
        CalculateTimeSignalTarget(GetApplicationFileTimeValue(), monotonicTime, TIME_SIGNAL_EVERY_MINUTE, &repeatedTarget);
        Require(target == repeatedTarget && oldOffset == GetApplicationTimeOffset(monotonicTime),
            "System-clock change shifted a time signal target");
    }
    invalidReply = true;
    ULONGLONG beforeFailure = GetApplicationFileTimeValue();
    ULONGLONG beforeFailureTick = monotonicTime;
    RunQuery();
    Require(!capturedResult->success, "Invalid replies were accepted");
    WindowProc(nullptr, WM_NTP_RESULT, 0, reinterpret_cast<LPARAM>(capturedResult));
    capturedResult = nullptr;
    Require(ntpTimeValid && GetApplicationFileTimeValue() ==
        beforeFailure + monotonicTime - beforeFailureTick, "Failed synchronization discarded the running NTP clock");
    useNtpTime = false;
    Require(GetApplicationFileTimeValue() == systemTime, "System time source did not follow Windows time");
    useNtpTime = true;
    ntpTimeValid = false;
    Require(GetApplicationFileTimeValue() == systemTime, "Unsynchronized clock did not use system time");
    hTimeSignalStopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    Require(hTimeSignalStopEvent != nullptr, "Could not create the signal test event");
    timeSignalSequences.push_back(TimeSignalSequence{ monotonicTime + 6 * FILE_TIME_TICKS_PER_SECOND, false, true });
    std::vector<TimeSignalTone> beforeJump = PlanTimeSignalIntervals(MonotonicFileTimeValue());
    systemTime += 600 * FILE_TIME_TICKS_PER_SECOND;
    std::vector<TimeSignalTone> afterJump = PlanTimeSignalIntervals(MonotonicFileTimeValue());
    Require(!beforeJump.empty() && beforeJump.size() == afterJump.size(), "System jump changed planned pips");
    for (size_t index = 0; index < beforeJump.size(); index++) {
        Require(beforeJump[index].start ==
            afterJump[index].start && beforeJump[index].end == afterJump[index].end, "System jump shifted a planned pip");
    }
    timeSignalSequences.clear();
    CloseHandle(hTimeSignalStopEvent);
    hTimeSignalStopEvent = nullptr;
    std::puts("PASS: NTP clock jumps, delayed delivery, offsets, signal targets and pips, failed sync, system fallback");
    return 0;
}
