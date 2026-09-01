#pragma once

#include <windows.h>

HWND CreateAnalogClockControl(HWND parent, int x, int y, int size, bool showSeconds, bool visible);
bool ConfigureAnalogClockControl(HWND control, int size, bool showSeconds);
bool SetAnalogClockSeconds(HWND control, int size, bool showSeconds);
void SetAnalogClockTime(HWND control, const SYSTEMTIME& time);
COLORREF ReadAnalogClockBackground(HWND control);
bool RenderAnalogClock(HWND control, HDC targetDC, DWORD background);
int GetSupportedAnalogClockSizes(int* sizes, int capacity);
bool AnalogClockSupportsSeconds(int size);
void ShutdownAnalogClockHost();
