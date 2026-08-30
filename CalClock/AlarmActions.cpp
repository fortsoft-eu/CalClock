#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "AlarmActions.h"
#include <windows.h>
#include <algorithm>
#include <cwctype>
#include <memory>
#include <mmsystem.h>
#include <shellapi.h>
#include <string>
#include <winhttp.h>

#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Winhttp.lib")
#pragma comment(lib, "Winmm.lib")

struct AudioThreadParameters {
    std::wstring path;
    bool loop = false;
    HANDLE stopEvent = nullptr;
    HWND notifyWindow = nullptr;
    UINT notifyMessage = 0;
    int widgetId = -1;
    ULONG generation = 0;
};

struct LocalCommandThreadParameters {
    std::wstring command;
};

struct RemoteScriptThreadParameters {
    std::wstring url;
};

bool LooksLikeAudio(const std::wstring& path) {
    size_t dot = path.find_last_of(L'.');
    if (dot == std::wstring::npos) {
        return false;
    }
    std::wstring extension = path.substr(dot);
    std::transform(extension.begin(), extension.end(), extension.begin(), towlower);
    return extension == L".wav"
        || extension == L".mp3"
        || extension == L".wma"
        || extension == L".mid"
        || extension == L".midi"
        || extension == L".aac"
        || extension == L".m4a"
        || extension == L".flac";
}

bool IsRemoteScriptUrlValid(const std::wstring& url) {
    if (url.empty()) {
        return false;
    }
    URL_COMPONENTSW components = {};
    components.dwStructSize = sizeof(components);
    components.dwHostNameLength = static_cast<DWORD>(-1);
    components.dwUrlPathLength = static_cast<DWORD>(-1);
    components.dwExtraInfoLength = static_cast<DWORD>(-1);
    if (!WinHttpCrackUrl(url.c_str(), 0, 0, &components)) {
        return false;
    }
    return (components.nScheme == INTERNET_SCHEME_HTTP || components.nScheme == INTERNET_SCHEME_HTTPS) && components.lpszHostName != nullptr && components.dwHostNameLength != 0;
}

static DWORD WINAPI AudioThreadProc(void* parameter) {
    std::unique_ptr<AudioThreadParameters> parameters(static_cast<AudioThreadParameters*>(parameter));
    std::wstring alias = L"calClockAudio" + std::to_wstring(GetCurrentThreadId()) + L"_" + std::to_wstring(parameters->generation);
    std::wstring command = L"open \"" + parameters->path + L"\" alias " + alias;
    bool opened = mciSendStringW(command.c_str(), nullptr, 0, nullptr) == 0;
    if (opened && WaitForSingleObject(parameters->stopEvent, 0) != WAIT_OBJECT_0) {
        command = L"play " + alias + (parameters->loop ? L" repeat" : L"");
        if (mciSendStringW(command.c_str(), nullptr, 0, nullptr) == 0) {
            while (WaitForSingleObject(parameters->stopEvent, 100) == WAIT_TIMEOUT) {
                if (!parameters->loop) {
                    wchar_t mode[32] = {};
                    command = L"status " + alias + L" mode";
                    if (mciSendStringW(command.c_str(), mode, ARRAYSIZE(mode), nullptr) != 0 || (_wcsicmp(mode, L"playing") != 0 && _wcsicmp(mode, L"seeking") != 0)) {
                        break;
                    }
                }
            }
        }
        command = L"stop " + alias;
        mciSendStringW(command.c_str(), nullptr, 0, nullptr);
    }
    if (opened) {
        command = L"close " + alias;
        mciSendStringW(command.c_str(), nullptr, 0, nullptr);
    }
    CloseHandle(parameters->stopEvent);
    PostMessageW(parameters->notifyWindow, parameters->notifyMessage, static_cast<WPARAM>(parameters->widgetId), static_cast<LPARAM>(parameters->generation));
    return 0;
}

bool StartAudioPlaybackAsync(const std::wstring& path, bool loop, HWND notifyWindow, UINT notifyMessage, int widgetId, ULONG generation, HANDLE* stopEvent) {
    if (stopEvent == nullptr) {
        return false;
    }
    HANDLE ownerEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (ownerEvent == nullptr) {
        return false;
    }
    HANDLE workerEvent = nullptr;
    if (!DuplicateHandle(GetCurrentProcess(), ownerEvent, GetCurrentProcess(), &workerEvent, 0, FALSE, DUPLICATE_SAME_ACCESS)) {
        CloseHandle(ownerEvent);
        return false;
    }
    std::unique_ptr<AudioThreadParameters> parameters(new AudioThreadParameters());
    parameters->path = path;
    parameters->loop = loop;
    parameters->stopEvent = workerEvent;
    parameters->notifyWindow = notifyWindow;
    parameters->notifyMessage = notifyMessage;
    parameters->widgetId = widgetId;
    parameters->generation = generation;
    HANDLE thread = CreateThread(nullptr, 0, AudioThreadProc, parameters.get(), 0, nullptr);
    if (thread == nullptr) {
        CloseHandle(workerEvent);
        CloseHandle(ownerEvent);
        return false;
    }
    parameters.release();
    CloseHandle(thread);
    *stopEvent = ownerEvent;
    return true;
}

static DWORD WINAPI LocalCommandThreadProc(void* parameter) {
    std::unique_ptr<LocalCommandThreadParameters> parameters(static_cast<LocalCommandThreadParameters*>(parameter));
    ShellExecuteW(nullptr, L"open", parameters->command.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
    return 0;
}

void StartLocalCommandAsync(const std::wstring& command) {
    std::unique_ptr<LocalCommandThreadParameters> parameters(new LocalCommandThreadParameters());
    parameters->command = command;
    HANDLE thread = CreateThread(nullptr, 0, LocalCommandThreadProc, parameters.get(), 0, nullptr);
    if (thread != nullptr) {
        parameters.release();
        CloseHandle(thread);
    }
}

static DWORD WINAPI RemoteScriptThreadProc(void* parameter) {
    std::unique_ptr<RemoteScriptThreadParameters> parameters(static_cast<RemoteScriptThreadParameters*>(parameter));
    URL_COMPONENTSW components = {};
    components.dwStructSize = sizeof(components);
    components.dwHostNameLength = static_cast<DWORD>(-1);
    components.dwUrlPathLength = static_cast<DWORD>(-1);
    components.dwExtraInfoLength = static_cast<DWORD>(-1);
    if (!WinHttpCrackUrl(parameters->url.c_str(), 0, 0, &components)) {
        return 0;
    }
    if (components.lpszHostName == nullptr || components.dwHostNameLength == 0) {
        return 0;
    }
    std::wstring host(components.lpszHostName, components.dwHostNameLength);
    std::wstring path;
    if (components.lpszUrlPath != nullptr && components.dwUrlPathLength != 0) {
        path.assign(components.lpszUrlPath, components.dwUrlPathLength);
    }
    if (components.lpszExtraInfo != nullptr && components.dwExtraInfoLength != 0) {
        path.append(components.lpszExtraInfo, components.dwExtraInfoLength);
    }
    if (path.empty()) {
        path = L"/";
    }
    HINTERNET session = WinHttpOpen(L"CalClock/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (session == nullptr) {
        return 0;
    }
    WinHttpSetTimeouts(session, 5000, 5000, 5000, 5000);
    HINTERNET connection = WinHttpConnect(session, host.c_str(), components.nPort, 0);
    DWORD flags = components.nScheme == INTERNET_SCHEME_HTTPS ? WINHTTP_FLAG_SECURE : 0;
    HINTERNET request = connection == nullptr ? nullptr : WinHttpOpenRequest(connection, L"GET", path.c_str(), nullptr, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, flags);
    if (request != nullptr && WinHttpSendRequest(request, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0)) {
        WinHttpReceiveResponse(request, nullptr);
    }
    if (request != nullptr) {
        WinHttpCloseHandle(request);
    }
    if (connection != nullptr) {
        WinHttpCloseHandle(connection);
    }
    WinHttpCloseHandle(session);
    return 0;
}

void StartRemoteScriptAsync(const std::wstring& url) {
    if (!IsRemoteScriptUrlValid(url)) {
        return;
    }
    std::unique_ptr<RemoteScriptThreadParameters> parameters(new RemoteScriptThreadParameters());
    parameters->url = url;
    HANDLE thread = CreateThread(nullptr, 0, RemoteScriptThreadProc, parameters.get(), 0, nullptr);
    if (thread != nullptr) {
        parameters.release();
        CloseHandle(thread);
    }
}
