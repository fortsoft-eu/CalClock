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
 * Last modified for version 1.4.1.3
 */

#pragma once

#include "CalClockTypes.h"
#include <windows.h>

bool CalculateTimeSignalTarget(ULONGLONG displayedFileTime, ULONGLONG systemFileTime,
    TimeSignalMode mode, ULONGLONG* targetSystemFileTime);
bool CalculateAlarmTimeSignalTarget(ULONGLONG displayedFileTime, ULONGLONG systemFileTime,
    int alarmHour, int alarmMinute, ULONGLONG* targetSystemFileTime);
bool TimeSignalTargetsCoincide(ULONGLONG left, ULONGLONG right);
bool StartTimeSignalPlayback(ULONGLONG targetSystemFileTime, bool muted, HWND notifyWindow,
    UINT notifyMessage);
void SetTimeSignalMuted(bool muted);
void FinishTimeSignalPlayback();
void StopTimeSignalPlayback();
bool IsTimeSignalPlaybackRunning();
