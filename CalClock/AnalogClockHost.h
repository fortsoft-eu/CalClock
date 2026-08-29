#pragma once

#include <windows.h>

HWND CreateAnalogClockControl(HWND parent, int x, int y, int size, bool showSeconds, bool visible);
void SetAnalogClockTime(HWND control, const SYSTEMTIME& time);
COLORREF ReadAnalogClockBackground(HWND control);
bool RenderAnalogClock(HWND control, HDC targetDC, DWORD background);
void ShutdownAnalogClockHost();
