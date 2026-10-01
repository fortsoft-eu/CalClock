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
 * Last modified for version 1.5.1.0
 */

#pragma once

#include "CalClockTypes.h"
#include <windows.h>

/// Maps the next displayed interval boundary to system FILETIME ticks, preserving fractional widget offsets.
/// Returns false for a disabled or invalid interval or a null output pointer.
bool CalculateTimeSignalTarget(ULONGLONG displayedFileTime, ULONGLONG systemFileTime, TimeSignalMode mode,
    ULONGLONG* targetSystemFileTime);

/// Maps the next occurrence of an alarm's displayed hour and minute to system FILETIME ticks.
/// Selects the following day when that time has already been reached; rejects invalid inputs.
bool CalculateAlarmTimeSignalTarget(ULONGLONG displayedFileTime, ULONGLONG systemFileTime, int alarmHour,
    int alarmMinute, ULONGLONG* targetSystemFileTime);

/// Tests exact equality of system-time targets so distinct fractional offsets remain separate.
bool TimeSignalTargetsCoincide(ULONGLONG left, ULONGLONG right);

/// Caches whether the Windows version requires generated audio instead of system Beep output.
bool IsTimeSignalGeneratorRequired();

/// Converts stored generator volume to decibels relative to full-scale sine amplitude.
/// Returns negative infinity for silence.
double TimeSignalVolumeDecibels(double volume);

/// Converts generator decibels to the interpolated stored volume scale, limiting positive levels to full scale.
double TimeSignalVolumeFromDecibels(double decibels);

/// Schedules a six-pip sequence whose final pip starts at targetSystemFileTime in system FILETIME ticks.
/// Deduplicates identical targets and starts the worker as needed; returns false for invalid notification data or
/// startup failure.
bool StartTimeSignalPlayback(ULONGLONG targetSystemFileTime, bool muted, bool generatedTone, double volume,
    HWND notifyWindow, UINT notifyMessage);

/// Starts or updates a preview merged with scheduled pips, beginning on the next whole system second.
/// Uses a long pip every fifth second and returns false if the playback worker cannot start.
bool StartTimeSignalVolumePreview(bool generatedTone, double volume);

/// Atomically updates the preview volume after clamping it to the stored generator-volume range.
void SetTimeSignalPreviewVolume(double volume);

/// Disables preview pips and releases the worker when no scheduled sequences remain.
void StopTimeSignalVolumePreview();

/// Shifts scheduled widget and alarm targets by a signed FILETIME adjustment after an application-clock correction.
/// Updates all targets under one lock, preserves preview timing, and wakes the worker to replan pending pips.
void AdjustTimeSignalPlaybackTime(LONGLONG adjustment);

/// Changes the mute state of the sequence with the given system-time target and wakes the playback worker.
void SetTimeSignalMuted(ULONGLONG target, bool muted);

/// Removes matching scheduled sequences and releases the worker if no other playback work remains.
void CancelTimeSignalPlayback(ULONGLONG target);

/// Releases an idle playback worker after sequence completion has been reported.
void FinishTimeSignalPlayback();

/// Clears all scheduled sequences and releases the worker if no preview remains active.
void StopTimeSignalPlayback();

/// Reports whether scheduled sequences remain, excluding preview-only playback.
bool IsTimeSignalPlaybackRunning();
