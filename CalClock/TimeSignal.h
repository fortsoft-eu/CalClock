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
 * Last modified for version 1.7.0.0
 */

#pragma once

#include "CalClock.h"
#include <windows.h>

/// Reports whether a displayed FILETIME value is an exact boundary of the enabled signal interval.
bool IsTimeSignalBoundary(ULONGLONG displayedFileTime, TimeSignalMode mode);

/// Maps the next displayed interval boundary to continuous FILETIME ticks, preserving fractional widget
/// offsets. Returns false for a disabled or invalid interval or a null output pointer.
bool CalculateTimeSignalTarget(ULONGLONG displayedFileTime, ULONGLONG timelineFileTime, TimeSignalMode mode,
    ULONGLONG* targetTimelineFileTime);

/// Caches whether the Windows version requires generated audio instead of system Beep output.
bool IsTimeSignalGeneratorRequired();

/// Converts stored generator volume to decibels relative to full-scale sine amplitude.
/// Returns negative infinity for silence.
double TimeSignalVolumeDecibels(double volume);

/// Converts generator decibels to the interpolated stored volume scale, limiting positive levels to full scale.
double TimeSignalVolumeFromDecibels(double decibels);

/// Schedules a six-pip sequence whose final pip starts at targetTimelineFileTime in continuous FILETIME ticks.
/// Deduplicates identical targets on the same endpoint; returns false for invalid notification data or
/// startup failure.
bool StartTimeSignalPlayback(ULONGLONG targetTimelineFileTime, bool muted, bool generatedTone, double volume,
    HWND notifyWindow, UINT notifyMessage, const std::wstring& outputDevice);

/// Starts or updates the test on its selected output, merging with signals on that output. System Beep
/// uses the Windows default. Returns false when the selected device or playback worker is unavailable.
bool StartTimeSignalVolumePreview(bool generatedTone, double volume, bool scheduledGeneratedTone,
    const std::wstring& outputDevice);

/// Atomically updates the preview volume after clamping it to the stored generator-volume range.
void SetTimeSignalPreviewVolume(double volume);

/// Disables preview pips and releases the worker when no scheduled sequences remain.
void StopTimeSignalVolumePreview();

/// Shifts scheduled widget and alarm targets by a signed FILETIME adjustment after an application-clock
/// correction. Locks each output's schedule separately, preserves preview timing, and wakes its worker
/// to replan pips.
void AdjustTimeSignalPlaybackTime(LONGLONG adjustment);

/// Changes the matching endpoint sequence's mute state and wakes its worker only when that state changes.
void SetTimeSignalMuted(ULONGLONG target, bool muted, const std::wstring& outputDevice);

/// Removes the target from one endpoint and releases idle workers without affecting other output sequences.
void CancelTimeSignalPlayback(ULONGLONG target, const std::wstring& outputDevice);

/// Releases an idle playback worker after sequence completion has been reported.
void FinishTimeSignalPlayback();

/// Clears all scheduled sequences and releases the worker if no preview remains active.
void StopTimeSignalPlayback();

/// Reports whether scheduled sequences remain, excluding preview-only playback.
bool IsTimeSignalPlaybackRunning();
