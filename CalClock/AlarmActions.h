#pragma once

#include <windows.h>
#include <string>

bool LooksLikeAudio(const std::wstring& path);
bool IsRemoteScriptUrlValid(const std::wstring& url);
bool StartAudioPlaybackAsync(const std::wstring& path, bool loop, HWND notifyWindow, UINT notifyMessage, int widgetId, ULONG generation, HANDLE* stopEvent);
void StartLocalCommandAsync(const std::wstring& command);
void StartRemoteScriptAsync(const std::wstring& url);
