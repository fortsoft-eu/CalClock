#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include "NtpClient.h"
#include <windows.h>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cwctype>
#include <memory>
#include <vector>

#pragma comment(lib, "Ws2_32.lib")

struct NtpThreadParameters {
    std::wstring serverList;
    ULONG generation = 0;
    HWND notifyWindow = nullptr;
    UINT notifyMessage = 0;
    std::atomic<bool>* stopRequested = nullptr;
    std::atomic<bool>* queryRunning = nullptr;
};

struct NtpSample {
    LONGLONG offset100Nanoseconds = 0;
    LONGLONG delay100Nanoseconds = 0;
    std::wstring server;
};

static int AutomaticNtpPreset() {
    wchar_t localeName[LOCALE_NAME_MAX_LENGTH] = {};
    wchar_t country[4] = {};
    if (GetUserDefaultLocaleName(localeName, ARRAYSIZE(localeName)) == 0 || GetLocaleInfoEx(localeName, LOCALE_SISO3166CTRYNAME, country, ARRAYSIZE(country)) == 0) {
        return NTP_PRESET_GLOBAL;
    }
    if (_wcsicmp(country, L"CZ") == 0 || _wcsicmp(country, L"SK") == 0) {
        return NTP_PRESET_CESNET;
    }
    const wchar_t* europeanCountries[] = {
        L"AL",
        L"AD",
        L"AT",
        L"BY",
        L"BE",
        L"BA",
        L"BG",
        L"HR",
        L"CY",
        L"DK",
        L"EE",
        L"FI",
        L"FR",
        L"DE",
        L"GR",
        L"HU",
        L"IS",
        L"IE",
        L"IT",
        L"XK",
        L"LV",
        L"LI",
        L"LT",
        L"LU",
        L"MT",
        L"MD",
        L"MC",
        L"ME",
        L"NL",
        L"MK",
        L"NO",
        L"PL",
        L"PT",
        L"RO",
        L"RU",
        L"SM",
        L"RS",
        L"SI",
        L"ES",
        L"SE",
        L"CH",
        L"TR",
        L"UA",
        L"GB",
        L"VA"
    };
    for (const wchar_t* europeanCountry : europeanCountries) {
        if (_wcsicmp(country, europeanCountry) == 0) {
            return NTP_PRESET_PTB;
        }
    }
    return NTP_PRESET_GLOBAL;
}

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
        return L"1.ntp.ubuntu.com; 2.ntp.ubuntu.com; 3.ntp.ubuntu.com; 4.ntp.ubuntu.com; 0.pool.ntp.org; 1.pool.ntp.org; 2.pool.ntp.org; 3.pool.ntp.org";
    }
    return std::wstring();
}

ULONGLONG CurrentFileTimeValue() {
    FILETIME fileTime = {};
    typedef VOID(WINAPI* GetPreciseTimeProc)(LPFILETIME fileTime);
    static GetPreciseTimeProc getPreciseTime = []() {
        HMODULE kernel = GetModuleHandleW(L"kernel32.dll");
        return kernel == nullptr ? static_cast<GetPreciseTimeProc>(nullptr) : reinterpret_cast<GetPreciseTimeProc>(GetProcAddress(kernel, "GetSystemTimePreciseAsFileTime"));
        }();
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

static void WriteNtpTimestamp(BYTE* destination, ULONGLONG fileTimeValue) {
    const ULONGLONG ntpEpochInFileTime = 94354848000000000ULL;
    ULONGLONG ntpValue = fileTimeValue - ntpEpochInFileTime;
    DWORD seconds = static_cast<DWORD>(ntpValue / 10000000ULL);
    DWORD fraction = static_cast<DWORD>(((ntpValue % 10000000ULL) << 32) / 10000000ULL);
    seconds = htonl(seconds);
    fraction = htonl(fraction);
    CopyMemory(destination, &seconds, sizeof(seconds));
    CopyMemory(destination + sizeof(seconds), &fraction, sizeof(fraction));
}

static ULONGLONG ReadNtpTimestamp(const BYTE* source, ULONGLONG referenceFileTime) {
    const ULONGLONG ntpEpochInFileTime = 94354848000000000ULL;
    DWORD secondsNetwork = 0;
    DWORD fractionNetwork = 0;
    CopyMemory(&secondsNetwork, source, sizeof(secondsNetwork));
    CopyMemory(&fractionNetwork, source + sizeof(secondsNetwork), sizeof(fractionNetwork));
    ULONGLONG seconds = ntohl(secondsNetwork);
    ULONGLONG fraction = ntohl(fractionNetwork);
    ULONGLONG referenceSeconds = (referenceFileTime - ntpEpochInFileTime) / 10000000ULL;
    ULONGLONG candidate = (referenceSeconds & 0xFFFFFFFF00000000ULL) | seconds;
    if (candidate + 0x80000000ULL < referenceSeconds) {
        candidate += 0x100000000ULL;
    } else if (candidate > referenceSeconds + 0x80000000ULL && candidate >= 0x100000000ULL) {
        candidate -= 0x100000000ULL;
    }
    return ntpEpochInFileTime + candidate * 10000000ULL + ((fraction * 10000000ULL) >> 32);
}

static std::vector<std::wstring> ParseNtpServerList(const std::wstring& serverList) {
    std::vector<std::wstring> servers;
    size_t start = 0;
    while (start < serverList.size()) {
        while (start < serverList.size() && (serverList[start] == L';' || serverList[start] == L',' || iswspace(serverList[start]))) {
            start++;
        }
        size_t end = start;
        while (end < serverList.size() && serverList[end] != L';' && serverList[end] != L',' && !iswspace(serverList[end])) {
            end++;
        }
        if (end > start) {
            std::wstring server = serverList.substr(start, end - start);
            if (server.size() <= 253 && servers.size() < 8 && std::find(servers.begin(), servers.end(), server) == servers.end()) {
                servers.push_back(server);
            }
        }
        start = end;
    }
    return servers;
}

static bool QueryNtpServer(const std::wstring& server, std::atomic<bool>* stopRequested, NtpSample* bestSample) {
    ADDRINFOW hints = {};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;
    PADDRINFOW addresses = nullptr;
    if (GetAddrInfoW(server.c_str(), L"123", &hints, &addresses) != 0) {
        return false;
    }
    bool success = false;
    for (int attempt = 0; attempt < 4 && !stopRequested->load(); attempt++) {
        for (PADDRINFOW address = addresses; address != nullptr && !stopRequested->load(); address = address->ai_next) {
            SOCKET socketHandle = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
            if (socketHandle == INVALID_SOCKET) {
                continue;
            }
            DWORD timeout = 1200;
            setsockopt(socketHandle, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout), sizeof(timeout));
            setsockopt(socketHandle, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout), sizeof(timeout));
            bool connected = connect(socketHandle, address->ai_addr, static_cast<int>(address->ai_addrlen)) != SOCKET_ERROR;
            BYTE request[48] = {};
            request[0] = 0x23;
            ULONGLONG t1 = CurrentFileTimeValue();
            WriteNtpTimestamp(request + 40, t1);
            int sent = connected ? send(socketHandle, reinterpret_cast<const char*>(request), sizeof(request), 0) : SOCKET_ERROR;
            BYTE response[48] = {};
            int received = sent == sizeof(request) ? recv(socketHandle, reinterpret_cast<char*>(response), sizeof(response), 0) : SOCKET_ERROR;
            ULONGLONG t4 = CurrentFileTimeValue();
            closesocket(socketHandle);
            BYTE leap = response[0] >> 6;
            BYTE version = (response[0] >> 3) & 7;
            BYTE mode = response[0] & 7;
            BYTE stratum = response[1];
            BYTE zeroTimestamp[8] = {};
            if (received < static_cast<int>(sizeof(response)) || leap == 3 || version < 3 || version > 4 || mode != 4 || stratum == 0 || stratum >= 16 || memcmp(response + 24, request + 40, 8) != 0 || memcmp(response + 40, zeroTimestamp, sizeof(zeroTimestamp)) == 0) {
                continue;
            }
            ULONGLONG t2 = ReadNtpTimestamp(response + 32, t4);
            ULONGLONG t3 = ReadNtpTimestamp(response + 40, t4);
            if (t3 < t2) {
                continue;
            }
            LONGLONG firstLeg = static_cast<LONGLONG>(t2) - static_cast<LONGLONG>(t1);
            LONGLONG secondLeg = static_cast<LONGLONG>(t3) - static_cast<LONGLONG>(t4);
            LONGLONG networkDelay = static_cast<LONGLONG>(t4 - t1) - static_cast<LONGLONG>(t3 - t2);
            if (networkDelay < 0 || networkDelay > 10LL * 10000000LL) {
                continue;
            }
            NtpSample sample = {};
            sample.offset100Nanoseconds = (firstLeg + secondLeg) / 2;
            sample.delay100Nanoseconds = networkDelay;
            sample.server = server;
            if (!success || sample.delay100Nanoseconds < bestSample->delay100Nanoseconds) {
                *bestSample = sample;
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

static DWORD WINAPI NtpThreadProc(void* parameter) {
    std::unique_ptr<NtpThreadParameters> parameters(static_cast<NtpThreadParameters*>(parameter));
    std::unique_ptr<NtpThreadResult> result(new NtpThreadResult());
    result->generation = parameters->generation;
    std::vector<std::wstring> servers = ParseNtpServerList(parameters->serverList);
    std::vector<NtpSample> samples;
    for (size_t index = 0; index < servers.size() && !parameters->stopRequested->load(); index++) {
        NtpSample sample = {};
        if (QueryNtpServer(servers[index], parameters->stopRequested, &sample)) {
            samples.push_back(sample);
        }
    }
    if (!samples.empty()) {
        std::vector<LONGLONG> sortedOffsets;
        for (size_t index = 0; index < samples.size(); index++) {
            sortedOffsets.push_back(samples[index].offset100Nanoseconds);
        }
        std::sort(sortedOffsets.begin(), sortedOffsets.end());
        size_t middle = sortedOffsets.size() / 2;
        LONGLONG medianOffset = sortedOffsets.size() % 2 == 0 ? sortedOffsets[middle - 1] / 2 + sortedOffsets[middle] / 2 : sortedOffsets[middle];
        LONGLONG minimumDelay = samples[0].delay100Nanoseconds;
        for (size_t index = 1; index < samples.size(); index++) {
            minimumDelay = std::min(minimumDelay, samples[index].delay100Nanoseconds);
        }
        long double rejectionLimit = static_cast<long double>(std::max(1000000LL, minimumDelay * 4));
        long double weightedOffset = 0.0L;
        long double totalWeight = 0.0L;
        size_t bestIndex = 0;
        bool acceptedAny = false;
        for (size_t index = 0; index < samples.size(); index++) {
            long double difference = std::fabs(static_cast<long double>(samples[index].offset100Nanoseconds) - static_cast<long double>(medianOffset));
            if (difference > rejectionLimit) {
                continue;
            }
            LONGLONG weightedDelay = std::max(10000LL, samples[index].delay100Nanoseconds);
            long double weight = 1.0L / static_cast<long double>(weightedDelay);
            weightedOffset += static_cast<long double>(samples[index].offset100Nanoseconds) * weight;
            totalWeight += weight;
            if (!acceptedAny || samples[index].delay100Nanoseconds < samples[bestIndex].delay100Nanoseconds) {
                bestIndex = index;
            }
            acceptedAny = true;
        }
        if (!acceptedAny) {
            for (size_t index = 1; index < samples.size(); index++) {
                if (samples[index].delay100Nanoseconds < samples[bestIndex].delay100Nanoseconds) {
                    bestIndex = index;
                }
            }
            result->offset100Nanoseconds = samples[bestIndex].offset100Nanoseconds;
        } else {
            result->offset100Nanoseconds = static_cast<LONGLONG>(std::llround(weightedOffset / totalWeight));
        }
        result->server = samples[bestIndex].server;
        result->success = true;
    }
    if (parameters->stopRequested->load()) {
        *parameters->queryRunning = false;
        return 0;
    }
    if (parameters->notifyWindow != nullptr && PostMessageW(parameters->notifyWindow, parameters->notifyMessage, 0, reinterpret_cast<LPARAM>(result.get()))) {
        result.release();
    } else {
        *parameters->queryRunning = false;
    }
    return 0;
}

bool HasNtpServers(const std::wstring& serverList) {
    return !ParseNtpServerList(serverList).empty();
}

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
