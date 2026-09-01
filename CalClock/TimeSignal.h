#pragma once

#include "CalClockTypes.h"
#include <windows.h>

bool CalculateTimeSignalTarget(ULONGLONG displayedFileTime, ULONGLONG systemFileTime, TimeSignalMode mode, ULONGLONG* targetSystemFileTime);
bool CalculateAlarmTimeSignalTarget(ULONGLONG displayedFileTime, ULONGLONG systemFileTime, int alarmHour, int alarmMinute, bool alarmActive, ULONGLONG* targetSystemFileTime);
bool TimeSignalTargetsCoincide(ULONGLONG left, ULONGLONG right);
bool StartTimeSignalPlayback(ULONGLONG targetSystemFileTime, HWND notifyWindow, UINT notifyMessage);
void FinishTimeSignalPlayback();
void StopTimeSignalPlayback();
bool IsTimeSignalPlaybackRunning();
