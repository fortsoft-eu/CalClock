#pragma once

#include "CalClockTypes.h"
#include <windows.h>

bool CalculateTimeSignalTarget(ULONGLONG displayedFileTime, ULONGLONG systemFileTime, TimeSignalMode mode, ULONGLONG* targetSystemFileTime);
bool CalculateAlarmTimeSignalTarget(ULONGLONG displayedFileTime, ULONGLONG systemFileTime, int alarmHour, int alarmMinute, ULONGLONG* targetSystemFileTime);
bool TimeSignalTargetsCoincide(ULONGLONG left, ULONGLONG right);
bool StartTimeSignalPlayback(ULONGLONG targetSystemFileTime, bool muted, HWND notifyWindow, UINT notifyMessage);
void SetTimeSignalMuted(bool muted);
void FinishTimeSignalPlayback();
void StopTimeSignalPlayback();
bool IsTimeSignalPlaybackRunning();
