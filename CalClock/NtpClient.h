#pragma once

#include "CalClockTypes.h"
#include <atomic>
#include <string>

struct NtpThreadResult {
    bool success = false;
    LONGLONG offset100Nanoseconds = 0;
    std::wstring server;
    ULONG generation = 0;
};

std::wstring NtpServersForPreset(int preset);
bool HasNtpServers(const std::wstring& serverList);
ULONGLONG CurrentFileTimeValue();
HANDLE StartNtpQueryThread(const std::wstring& serverList, ULONG generation, HWND notifyWindow, UINT notifyMessage, std::atomic<bool>* stopRequested, std::atomic<bool>* queryRunning);
