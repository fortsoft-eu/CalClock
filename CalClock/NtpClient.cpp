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
#include "NtpClient.h"
#include "ClockTime.h"
#include <windows.h>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cwctype>
#include <memory>
#include <vector>

#pragma comment(lib, "Ws2_32.lib")

/// Passes server names, notification details, and borrowed cancellation and activity flags to the NTP worker.
struct NtpThreadParameters {
    std::wstring serverList;
    ULONG generation = 0;
    HWND notifyWindow = nullptr;
    UINT notifyMessage = 0;
    std::atomic<bool>* stopRequested = nullptr;
    std::atomic<bool>* queryRunning = nullptr;
};

/// Stores a validated server sample's correction to the continuous clock and network delay in 100-nanosecond units.
struct NtpSample {
    LONGLONG clockOffset100Nanoseconds = 0;
    LONGLONG delay100Nanoseconds = 0;
    std::wstring server;
};

/// Chooses a regional NTP preset from the user's locale country, defaulting to the global pool.
static int AutomaticNtpPreset() {
    wchar_t localeName[LOCALE_NAME_MAX_LENGTH] = {};
    wchar_t country[4] = {};
    if (GetUserDefaultLocaleName(localeName, ARRAYSIZE(localeName)) == 0
            || GetLocaleInfoEx(localeName, LOCALE_SISO3166CTRYNAME, country, ARRAYSIZE(country)) == 0) {
        return NTP_PRESET_GLOBAL;
    }
    if (_wcsicmp(country, L"CZ") == 0 || _wcsicmp(country, L"SK") == 0) {
        return NTP_PRESET_CESNET;
    }
    const wchar_t* europeanCountries[] = {
        L"AL", L"AD", L"AT", L"BY", L"BE", L"BA", L"BG", L"HR", L"CY",
        L"DK", L"EE", L"FI", L"FR", L"DE", L"GR", L"HU", L"IS", L"IE",
        L"IT", L"XK", L"LV", L"LI", L"LT", L"LU", L"MT", L"MD", L"MC",
        L"ME", L"NL", L"MK", L"NO", L"PL", L"PT", L"RO", L"RU", L"SM",
        L"RS", L"SI", L"ES", L"SE", L"CH", L"TR", L"UA", L"GB", L"VA"
    };
    for (const wchar_t* europeanCountry : europeanCountries) {
        if (_wcsicmp(country, europeanCountry) == 0) {
            return NTP_PRESET_PTB;
        }
    }
    return NTP_PRESET_GLOBAL;
}

/// Returns the preset's server list, resolving the automatic preset from the user's region.
/// Returns an empty string for the custom preset.
std::wstring NtpServersForPreset(int preset) {
    int selected = std::clamp(preset, 0, NTP_PRESET_COUNT - 1);
    if (selected == NTP_PRESET_AUTO) {
        selected = AutomaticNtpPreset();
    }
    if (selected == NTP_PRESET_CESNET) {
        return L"tik.cesnet.cz; tak.cesnet.cz; ntp.nic.cz";
    }
    if (selected == NTP_PRESET_PTB) {
        return L"ptbtime1.ptb.de; ptbtime2.ptb.de; ptbtime3.ptb.de; ptbtime4.ptb.de";
    }
    if (selected == NTP_PRESET_GLOBAL) {
        return L"1.ntp.ubuntu.com; 2.ntp.ubuntu.com; 3.ntp.ubuntu.com; 4.ntp.ubuntu.com;"
            L" 0.pool.ntp.org; 1.pool.ntp.org; 2.pool.ntp.org; 3.pool.ntp.org";
    }
    return std::wstring();
}

/// Encodes a FILETIME timestamp into an eight-byte, network-order NTP timestamp.
static void WriteNtpTimestamp(BYTE* destination, ULONGLONG fileTimeValue) {
    const ULONGLONG ntpEpochInFileTime = 94354848000000000ULL;
    ULONGLONG ntpValue = fileTimeValue - ntpEpochInFileTime;
    DWORD seconds = static_cast<DWORD>(ntpValue / 10000000ULL);
    DWORD fraction = static_cast<DWORD>((ntpValue % 10000000ULL << 32) / 10000000ULL);
    seconds = htonl(seconds);
    fraction = htonl(fraction);
    CopyMemory(destination, &seconds, sizeof(seconds));
    CopyMemory(destination + sizeof(seconds), &fraction, sizeof(fraction));
}

/// Decodes an eight-byte NTP timestamp to FILETIME ticks, choosing the era nearest referenceFileTime.
static ULONGLONG ReadNtpTimestamp(const BYTE* source, ULONGLONG referenceFileTime) {
    const ULONGLONG ntpEpochInFileTime = 94354848000000000ULL;
    DWORD secondsNetwork = 0;
    DWORD fractionNetwork = 0;
    CopyMemory(&secondsNetwork, source, sizeof(secondsNetwork));
    CopyMemory(&fractionNetwork, source + sizeof(secondsNetwork), sizeof(fractionNetwork));
    ULONGLONG seconds = ntohl(secondsNetwork);
    ULONGLONG fraction = ntohl(fractionNetwork);
    ULONGLONG referenceSeconds = (referenceFileTime - ntpEpochInFileTime) / 10000000ULL;
    ULONGLONG candidate = referenceSeconds & 0xFFFFFFFF00000000ULL | seconds;
    if (candidate + 0x80000000ULL < referenceSeconds) {
        candidate += 0x100000000ULL;
    } else if (candidate > referenceSeconds + 0x80000000ULL && candidate >= 0x100000000ULL) {
        candidate -= 0x100000000ULL;
    }
    return ntpEpochInFileTime + candidate * 10000000ULL + (fraction * 10000000ULL >> 32);
}

/// Splits server names on whitespace, commas, or semicolons and keeps at most eight distinct names of valid length.
static std::vector<std::wstring> ParseNtpServerList(const std::wstring& serverList) {
    std::vector<std::wstring> servers;
    size_t start = 0;
    while (start < serverList.size()) {
        while (start < serverList.size()
                && (serverList[start] == L';' || serverList[start] == L',' || iswspace(serverList[start]))) {
            start++;
        }
        size_t end = start;
        while (end < serverList.size()
                && serverList[end] != L';'
                && serverList[end] != L','
                && !iswspace(serverList[end])) {
            end++;
        }
        if (end > start) {
            std::wstring server = serverList.substr(start, end - start);
            if (server.size() <= 253
                    && servers.size() < 8
                    && std::find(servers.begin(), servers.end(), server) == servers.end()) {
                servers.push_back(server);
            }
        }
        start = end;
    }
    return servers;
}

/// Queries a server's UDP endpoints, validates NTP replies, and retains the successful sample with the least delay.
/// Checks cancellation between attempts and records the last failure if no valid sample is received.
static bool QueryNtpServer(const std::wstring& server, std::atomic<bool>* stopRequested, NtpSample* bestSample,
        NtpQueryLogEntry* logEntry) {
    ADDRINFOW hints = {};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;
    PADDRINFOW addresses = nullptr;
    int addressResult = GetAddrInfoW(server.c_str(), L"123", &hints, &addresses);
    if (addressResult != 0) {
        logEntry->error = NtpQueryError::NameResolution;
        logEntry->errorCode = addressResult;
        return false;
    }
    bool success = false;
    for (int attempt = 0; attempt < 4 && !stopRequested->load(); attempt++) {
        for (PADDRINFOW address = addresses; address != nullptr && !stopRequested->load(); address = address->ai_next) {
            SOCKET socketHandle = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
            if (socketHandle == INVALID_SOCKET) {
                logEntry->error = NtpQueryError::Network;
                logEntry->errorCode = WSAGetLastError();
                continue;
            }
            DWORD timeout = 1200;
            setsockopt(socketHandle, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout), sizeof(timeout));
            setsockopt(socketHandle, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout), sizeof(timeout));
            int connectionResult = connect(socketHandle, address->ai_addr, static_cast<int>(address->ai_addrlen));
            if (connectionResult == SOCKET_ERROR) {
                logEntry->error = NtpQueryError::Network;
                logEntry->errorCode = WSAGetLastError();
                closesocket(socketHandle);
                continue;
            }
            BYTE request[48] = {};
            request[0] = 0x23;
            ULONGLONG t1 = CurrentFileTimeValue();
            WriteNtpTimestamp(request + 40, t1);
            ULONGLONG sentTime = MonotonicFileTimeValue();
            int sent = send(socketHandle, reinterpret_cast<const char*>(request), sizeof(request), 0);
            if (sent != sizeof(request)) {
                logEntry->error = NtpQueryError::Network;
                logEntry->errorCode = sent == SOCKET_ERROR ? WSAGetLastError() : 0;
                closesocket(socketHandle);
                continue;
            }
            BYTE response[48] = {};
            int received = recv(socketHandle, reinterpret_cast<char*>(response), sizeof(response), 0);
            int receiveError = received == SOCKET_ERROR ? WSAGetLastError() : 0;
            ULONGLONG receivedTime = MonotonicFileTimeValue();
            ULONGLONG systemReceivedTime = CurrentFileTimeValue();
            closesocket(socketHandle);
            if (received == SOCKET_ERROR) {
                logEntry->error = receiveError == WSAETIMEDOUT ? NtpQueryError::Timeout : NtpQueryError::Network;
                logEntry->errorCode = receiveError;
                continue;
            }
            logEntry->error = NtpQueryError::InvalidResponse;
            logEntry->errorCode = 0;
            if (received < static_cast<int>(sizeof(response))) {
                continue;
            }
            BYTE leap = response[0] >> 6;
            BYTE version = response[0] >> 3 & 7;
            BYTE mode = response[0] & 7;
            BYTE stratum = response[1];
            BYTE zeroTimestamp[8] = {};
            bool invalidResponse = leap == 3
                || version < 3
                || version > 4
                || mode != 4
                || stratum == 0
                || stratum >= 16
                || memcmp(response + 24, request + 40, 8) != 0
                || memcmp(response + 40, zeroTimestamp, sizeof(zeroTimestamp)) == 0;
            if (invalidResponse) {
                continue;
            }
            ULONGLONG t2 = ReadNtpTimestamp(response + 32, t1);
            ULONGLONG t3 = ReadNtpTimestamp(response + 40, t1);
            if (t3 < t2) {
                continue;
            }
            LONGLONG networkDelay = static_cast<LONGLONG>(receivedTime - sentTime) - static_cast<LONGLONG>(t3 - t2);
            if (networkDelay < 0 || networkDelay > 10LL * 10000000LL) {
                continue;
            }
            LONGLONG synchronizedTime = static_cast<LONGLONG>(t3) + networkDelay / 2;
            NtpSample sample = {};
            sample.clockOffset100Nanoseconds = synchronizedTime - static_cast<LONGLONG>(receivedTime);
            sample.delay100Nanoseconds = networkDelay;
            sample.server = server;
            if (!success || sample.delay100Nanoseconds < bestSample->delay100Nanoseconds) {
                *bestSample = sample;
                logEntry->offset100Nanoseconds = synchronizedTime - static_cast<LONGLONG>(systemReceivedTime);
            }
            success = true;
            break;
        }
        if (attempt < 3 && !stopRequested->load()) {
            Sleep(40);
        }
    }
    FreeAddrInfoW(addresses);
    return success;
}

/// Queries configured servers, rejects offset outliers, and combines accepted samples using inverse-delay weights.
/// Transfers a heap-allocated result to the notification receiver on a successful post; otherwise releases it locally.
static DWORD WINAPI NtpThreadProc(void* parameter) {
    std::unique_ptr<NtpThreadParameters> parameters(static_cast<NtpThreadParameters*>(parameter));
    std::unique_ptr<NtpThreadResult> result(new NtpThreadResult());
    result->generation = parameters->generation;
    std::vector<std::wstring> servers = ParseNtpServerList(parameters->serverList);
    std::vector<NtpSample> samples;
    for (size_t index = 0; index < servers.size() && !parameters->stopRequested->load(); index++) {
        NtpSample sample = {};
        NtpQueryLogEntry entry = {};
        entry.server = servers[index];
        entry.success = QueryNtpServer(servers[index], parameters->stopRequested, &sample, &entry);
        entry.completedTime = CurrentFileTimeValue();
        if (entry.success) {
            samples.push_back(sample);
        }
        result->logEntries.push_back(entry);
    }
    if (!samples.empty()) {
        std::vector<LONGLONG> sortedOffsets;
        size_t fastestIndex = 0;
        for (size_t index = 0; index < samples.size(); index++) {
            sortedOffsets.push_back(samples[index].clockOffset100Nanoseconds);
            if (samples[index].delay100Nanoseconds < samples[fastestIndex].delay100Nanoseconds) {
                fastestIndex = index;
            }
        }
        std::sort(sortedOffsets.begin(), sortedOffsets.end());
        size_t middle = sortedOffsets.size() / 2;
        LONGLONG medianOffset = sortedOffsets.size() % 2 == 0
            ? sortedOffsets[middle - 1] / 2 + sortedOffsets[middle] / 2
            : sortedOffsets[middle];
        LONGLONG minimumDelay = samples[fastestIndex].delay100Nanoseconds;
        long double rejectionLimit = static_cast<long double>(std::max(1000000LL, minimumDelay * 4));
        long double weightedOffset = 0.0L;
        long double totalWeight = 0.0L;
        size_t bestIndex = 0;
        bool acceptedAny = false;
        for (size_t index = 0; index < samples.size(); index++) {
            long double difference = std::fabs(static_cast<long double>(samples[index].clockOffset100Nanoseconds)
                - static_cast<long double>(medianOffset));
            if (difference > rejectionLimit) {
                continue;
            }
            LONGLONG weightedDelay = std::max(10000LL, samples[index].delay100Nanoseconds);
            long double weight = 1.0L / static_cast<long double>(weightedDelay);
            weightedOffset += static_cast<long double>(samples[index].clockOffset100Nanoseconds) * weight;
            totalWeight += weight;
            if (!acceptedAny || samples[index].delay100Nanoseconds < samples[bestIndex].delay100Nanoseconds) {
                bestIndex = index;
            }
            acceptedAny = true;
        }
        if (!acceptedAny) {
            bestIndex = fastestIndex;
            result->clockOffset100Nanoseconds = samples[bestIndex].clockOffset100Nanoseconds;
        } else {
            result->clockOffset100Nanoseconds = static_cast<LONGLONG>(std::llround(weightedOffset / totalWeight));
        }
        ULONGLONG now = MonotonicFileTimeValue();
        result->offset100Nanoseconds = static_cast<LONGLONG>(now) + result->clockOffset100Nanoseconds
            - static_cast<LONGLONG>(CurrentFileTimeValue());
        result->server = samples[bestIndex].server;
        result->success = true;
    }
    if (result->success && !result->logEntries.empty()) {
        NtpQueryLogEntry& lastEntry = result->logEntries.back();
        lastEntry.hasCombinedOffset = true;
        lastEntry.combinedOffset100Nanoseconds = result->offset100Nanoseconds;
    }
    if (parameters->stopRequested->load()) {
        *parameters->queryRunning = false;
        return 0;
    }
    if (parameters->notifyWindow != nullptr
        && PostMessageW(parameters->notifyWindow, parameters->notifyMessage, 0,
            reinterpret_cast<LPARAM>(result.get()))) {
        result.release();
    } else {
        *parameters->queryRunning = false;
    }
    return 0;
}

/// Reports whether the server list contains at least one accepted server name.
bool HasNtpServers(const std::wstring& serverList) {
    return !ParseNtpServerList(serverList).empty();
}

/// Starts an NTP worker and returns its thread handle, or null on failure. The caller owns the handle and must
/// keep both atomic flags alive until the worker exits; the receiver owns posted results.
HANDLE StartNtpQueryThread(const std::wstring& serverList, ULONG generation, HWND notifyWindow, UINT notifyMessage,
    std::atomic<bool>* stopRequested, std::atomic<bool>* queryRunning) {
    if (stopRequested == nullptr || queryRunning == nullptr) {
        return nullptr;
    }
    std::unique_ptr<NtpThreadParameters> parameters(new NtpThreadParameters());
    parameters->serverList = serverList;
    parameters->generation = generation;
    parameters->notifyWindow = notifyWindow;
    parameters->notifyMessage = notifyMessage;
    parameters->stopRequested = stopRequested;
    parameters->queryRunning = queryRunning;
    HANDLE thread = CreateThread(nullptr, 0, NtpThreadProc, parameters.get(), 0, nullptr);
    if (thread != nullptr) {
        parameters.release();
    }
    return thread;
}
