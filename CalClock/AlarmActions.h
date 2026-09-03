#pragma once

#include <windows.h>
#include <string>

bool LooksLikeAudio(const std::wstring& path);
bool IsRemoteScriptUrlValid(const std::wstring& url);
bool StartAudioPlaybackAsync(const std::wstring& path, bool loop, bool muted, HWND notifyWindow, UINT notifyMessage, int widgetId, ULONG generation, HANDLE* stopEvent, HANDLE* muteEvent);
void SetAudioPlaybackMuted(HANDLE muteEvent, bool muted);
void StartLocalCommandAsync(const std::wstring& command);
void StartRemoteScriptAsync(const std::wstring& url);
