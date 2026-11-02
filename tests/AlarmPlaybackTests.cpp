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
 * Last modified for version 1.7.0.6
 */

#define NOMINMAX
#include "../CalClock/CalClock.h"
#include "../CalClock/AlarmActions.h"
#include "../CalClock/TimeSignal.h"
#include "../CalClock/TimeZoneSupport.h"
#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include "AlarmPlaybackTypes.h"

struct PlaybackRequest {
    ULONGLONG target;
    std::wstring output;
    bool muted;
};

static const UINT WM_AUDIO_FINISHED = WM_APP + 4;
static const UINT WM_TIME_SIGNAL_FINISHED = WM_APP + 8;
static const ULONGLONG SECOND = 10000000;
static HWND hController = reinterpret_cast<HWND>(1);
static std::vector<std::unique_ptr<Widget>> widgets;
static std::vector<DYNAMIC_TIME_ZONE_INFORMATION> timeZones;
static std::vector<TimeSignalSourceGroup> currentTimeSignalSources;
static std::vector<PlaybackRequest> playback;
static ULONGLONG timelineNow = 0;
static LONGLONG applicationOffset = 0;
static LONGLONG currentTimeSignalOffset = 0;
static bool settingsTimeSignalTestActive = false;
static bool settingsVisualPreviewActive = false;
static int settingsVisualPreviewWidgetId = -1;
static bool timeSignalVolumeDragging = false;
static bool generatedTimeSignal = true;
static bool failPlayback = false;
static double timeSignalVolume = TIME_SIGNAL_VOLUME_DEFAULT;
static int signalStarts = 0;
static int signalCancels = 0;
static int audioStarts = 0;
static int commandStarts = 0;
static int remoteStarts = 0;
static int raises = 0;
static int renders = 0;
static bool audioMuted = false;
static bool audioLoop = false;
static int audioVolume = 0;
static std::wstring lastCommand;
static std::wstring lastRemote;

/// Stops immediately on an observed mismatch; no simulated action reaches an external resource.
static void Require(bool value, const char* message) {
    if (!value) {
        std::fprintf(stderr, "FAIL: %s\n", message);
        std::exit(1);
    }
}

/// Creates one UTC test instant using Windows calendar conversion.
static ULONGLONG Utc(int year, int month, int day, int hour, int minute, int second = 0) {
    SYSTEMTIME time{};
    time.wYear = static_cast<WORD>(year);
    time.wMonth = static_cast<WORD>(month);
    time.wDay = static_cast<WORD>(day);
    time.wHour = static_cast<WORD>(hour);
    time.wMinute = static_cast<WORD>(minute);
    time.wSecond = static_cast<WORD>(second);
    FILETIME file{};
    Require(SystemTimeToFileTime(&time, &file) != FALSE, "valid UTC fixture");
    ULARGE_INTEGER result{};
    result.LowPart = file.dwLowDateTime;
    result.HighPart = file.dwHighDateTime;
    return result.QuadPart;
}

/// Returns the controlled monotonic clock without changing Windows time.
static ULONGLONG MonotonicFileTimeValue() {
    return timelineNow;
}

/// Returns the controlled application correction without querying an NTP server.
static LONGLONG GetApplicationTimeOffset(ULONGLONG) {
    return applicationOffset;
}

/// Returns application UTC from the two controlled clocks.
static ULONGLONG GetApplicationFileTimeValue() {
    return static_cast<ULONGLONG>(static_cast<LONGLONG>(timelineNow) + applicationOffset);
}

/// Finds a live fixture using the same persistent widget identifier as the application.
static Widget* FindWidgetById(int id) {
    for (const std::unique_ptr<Widget>& widget : widgets) {
        if (widget->config.id == id) {
            return widget.get();
        }
    }
    return nullptr;
}

/// Makes preview-volume updates inert; waveform generation is outside this dispatcher test.
static void UpdateTimeSignalVolumePreview() {}

/// Supplies a stable fake endpoint without accessing installed audio hardware.
static bool ResolveAudioOutputDevice(const std::wstring&, std::wstring* output, UINT* device) {
    *output = L"default";
    *device = 0;
    return true;
}

/// Allows both system-Beep and generated-output scheduling to be tested deterministically.
bool IsTimeSignalGeneratorRequired() {
    return false;
}

/// Records a scheduled signal rather than creating a playback thread or sounding a device.
bool StartTimeSignalPlayback(ULONGLONG target, bool muted, bool, double, HWND, UINT,
        const std::wstring& output) {
    if (failPlayback) {
        return false;
    }
    signalStarts++;
    playback.push_back(PlaybackRequest{ target, output, muted });
    return true;
}

/// Records cancellation without disturbing another target or endpoint.
void CancelTimeSignalPlayback(ULONGLONG target, const std::wstring& output) {
    signalCancels++;
    playback.erase(std::remove_if(playback.begin(), playback.end(),
        [target, &output](const PlaybackRequest& item) {
        return item.target == target && item.output == output;
    }), playback.end());
}

/// Records the audible state selected by the production contributor logic.
void SetTimeSignalMuted(ULONGLONG target, bool muted, const std::wstring& output) {
    for (PlaybackRequest& item : playback) {
        if (item.target == target && item.output == output) {
            item.muted = muted;
        }
    }
}

/// Applies a simulated NTP correction to already scheduled playback records.
void AdjustTimeSignalPlaybackTime(LONGLONG adjustment) {
    for (PlaybackRequest& item : playback) {
        item.target = static_cast<ULONGLONG>(static_cast<LONGLONG>(item.target) + adjustment);
    }
}

/// Recognizes the fixture audio file without opening it.
bool LooksLikeAudio(const std::wstring& path) {
    return path == L"fixture.wav";
}

/// Captures audio options and returns only private kernel events, never an audio worker.
bool StartAudioPlaybackAsync(const std::wstring&, bool loop, bool muted,
        const std::shared_ptr<std::atomic<int>>& volume, HWND, UINT, int, ULONG,
        HANDLE* stopEvent, HANDLE* muteEvent) {
    audioStarts++;
    audioMuted = muted;
    audioLoop = loop;
    audioVolume = volume->load();
    *stopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    *muteEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    Require(*stopEvent != nullptr && *muteEvent != nullptr, "private audio events");
    return true;
}

/// Captures the local action without launching its file or command.
void StartLocalCommandAsync(const std::wstring& command) {
    commandStarts++;
    lastCommand = command;
}

/// Captures the remote action without performing a network request.
void StartRemoteScriptAsync(const std::wstring& url) {
    remoteStarts++;
    lastRemote = url;
}

/// Changes fixture visibility without creating, positioning or activating a window.
static void SetWidgetVisible(Widget* widget, bool visible) {
    widget->config.visible = visible;
}

/// Counts alarm raising requests without interacting with the desktop.
static void RaiseWidgetForAlarm(Widget*) {
    raises++;
}

/// Counts render requests without touching a graphics device or window.
static void RenderWidget(Widget*) {
    renders++;
}

#include "AlarmSignalMath.h"
#include "AlarmPlaybackProduction.h"

/// Delivers the actual audio-completion handler against private event handles.
static LRESULT AudioFinished(int id, ULONG generation) {
    HWND window = hController;
    UINT msg = WM_AUDIO_FINISHED;
    WPARAM wParam = static_cast<WPARAM>(id);
    LPARAM lParam = static_cast<LPARAM>(generation);
    switch (msg) {
#include "AlarmPlaybackMessages.h"
    }
    return 0;
}

/// Clears private fixture state and all owned event handles between scenarios.
static void Reset(ULONGLONG now) {
    for (const std::unique_ptr<Widget>& widget : widgets) {
        CloseWidgetAudio(widget.get());
    }
    widgets.clear();
    playback.clear();
    currentTimeSignalSources.clear();
    timelineNow = now;
    applicationOffset = currentTimeSignalOffset = 0;
    generatedTimeSignal = true;
    failPlayback = false;
    signalStarts = signalCancels = audioStarts = commandStarts = remoteStarts = raises = renders = 0;
    lastCommand.clear();
    lastRemote.clear();
}

/// Adds a clock fixture with a default UTC alarm and independent occurrence history.
static Widget* AddClock(int id, WidgetType type = WIDGET_DIGITAL) {
    widgets.push_back(std::make_unique<Widget>());
    Widget* widget = widgets.back().get();
    widget->config.id = id;
    widget->config.type = type;
    widget->config.alarmEnabled = true;
    widget->config.alarmTimeSignal = true;
    widget->config.showUtc = true;
    widget->config.alarmHour = 8;
    widget->config.alarmMinute = 0;
    widget->alarmSchedule.Reset(widget->config, timeZones, GetApplicationFileTimeValue());
    return widget;
}

/// Checks exact shared alarm targets, endpoint isolation, mute contributors and stopping only one alarm.
static void TestContributors() {
    Reset(Utc(2026, 11, 2, 7, 59, 54));
    Widget* first = AddClock(1);
    Widget* second = AddClock(2);
    first->config.soundsMuted = true;
    CheckTimeSignals();
    Require(signalStarts == 1 && playback.size() == 1, "shared alarm pips scheduled once");
    Require(!playback[0].muted, "one unmuted contributor keeps shared pips audible");
    CheckTimeSignals();
    Require(signalStarts == 1, "repeated check does not reschedule same pips");
    timelineNow += SECOND;
    StopWidgetAlarm(first);
    Require(signalCancels == 0 && !playback[0].muted, "stop one preserves other alarm");
    CheckTimeSignals();
    Require(currentTimeSignalSources[0].alarmWidgetIds.size() == 1, "canceled alarm not readded");
    second->config.timeSignalEnabled = true;
    second->config.timeSignal = TIME_SIGNAL_EVERY_HOUR;
    CheckTimeSignals();
    StopWidgetAlarm(second);
    Require(signalCancels == 0 && !playback[0].muted, "regular signal survives alarm cancellation");
    CheckTimeSignals();
    Require(currentTimeSignalSources[0].alarmWidgetIds.empty(), "both canceled alarms remain removed");
    second->config.soundsMuted = true;
    UpdateCurrentTimeSignalMute();
    Require(playback[0].muted, "last audible contributor muted");
    Reset(Utc(2026, 11, 2, 7, 59, 54));
    first = AddClock(1);
    first->config.timeSignalEnabled = true;
    first->config.timeSignal = TIME_SIGNAL_EVERY_HOUR;
    first->config.timeSignalOutputDevice = L"separate";
    CheckTimeSignals();
    Require(playback.size() == 2 && playback[0].output != playback[1].output,
        "alarm stays on default output");
}

/// Checks silent calendars, late resume, shifted targets, NTP retiming and rejected output startup.
static void TestTiming() {
    Reset(Utc(2026, 11, 2, 7, 59, 54));
    Widget* calendar = AddClock(1, WIDGET_CALENDAR);
    calendar->config.timeSignalEnabled = true;
    calendar->config.timeSignal = TIME_SIGNAL_EVERY_HOUR;
    CheckTimeSignals();
    Require(playback.empty(), "calendar does not produce alarm or regular pips");
    Reset(Utc(2026, 11, 2, 7, 59, 54));
    Widget* widget = AddClock(1);
    timelineNow = Utc(2026, 11, 2, 8, 10);
    Require(widget->alarmSchedule.Check(widget->config, timeZones, timelineNow),
        "catch up alarm after sleep");
    StartWidgetAlarm(widget);
    CheckTimeSignals();
    Require(playback.empty() && widget->alarmActive, "late visual alarm without replaying old pips");
    Reset(Utc(2026, 11, 2, 7, 59, 50));
    widget = AddClock(1);
    widget->config.offsetMilliseconds = 2500;
    widget->alarmSchedule.Reset(widget->config, timeZones, timelineNow);
    CheckTimeSignals();
    Require(playback.size() == 1 && playback[0].target == Utc(2026, 11, 2, 8, 0) - 25000000,
        "fractional widget offset preserved in pips");
    applicationOffset = 2 * SECOND;
    widget->alarmSchedule.Check(widget->config, timeZones, GetApplicationFileTimeValue());
    CheckTimeSignals();
    Require(currentTimeSignalSources.size() == 1
        && currentTimeSignalSources[0].target == Utc(2026, 11, 2, 8, 0) - 45000000,
        "NTP retimes existing pips and keeps contributors");
    Reset(Utc(2026, 11, 2, 7, 59, 54));
    AddClock(1);
    failPlayback = true;
    CheckTimeSignals();
    Require(currentTimeSignalSources.empty(), "failed playback does not register phantom contributors");
    failPlayback = false;
    CheckTimeSignals();
    Require(currentTimeSignalSources.size() == 1, "output may recover before alarm");
}

/// Checks actual action dispatch, generation-based stale completion rejection and all-alarm cancellation.
static void TestActions() {
    Reset(Utc(2026, 11, 2, 7, 59, 54));
    Widget* widget = AddClock(1);
    widget->config.visible = false;
    widget->config.runCommand = true;
    widget->config.command = L"fixture.wav";
    widget->config.loopAudio = true;
    widget->config.soundsMuted = true;
    widget->config.alarmVolume = -1800;
    widget->config.callRemoteScript = true;
    widget->config.remoteScriptUrl = L"https://example.invalid/alarm";
    StartWidgetAlarm(widget);
    Require(widget->alarmActive && widget->flashPhase && widget->config.visible && raises == 1,
        "alarm reveals hidden widget and starts visual indication");
    Require(audioStarts == 1 && audioMuted && audioLoop && audioVolume == -1800,
        "audio options reach playback unchanged");
    Require(remoteStarts == 1 && lastRemote == widget->config.remoteScriptUrl, "remote action dispatched");
    ULONG oldGeneration = widget->audioGeneration;
    StartWidgetAlarm(widget);
    HANDLE currentEvent = widget->audioStopEvent;
    AudioFinished(1, oldGeneration);
    Require(widget->audioStopEvent == currentEvent, "stale completion cannot close newer playback");
    AudioFinished(1, widget->audioGeneration);
    Require(widget->audioStopEvent == nullptr && widget->audioMuteEvent == nullptr && widget->alarmActive,
        "audio completion releases events but retains visible alarm");
    widget->config.command = L"fixture-command";
    StartWidgetAlarm(widget);
    Require(commandStarts == 1 && lastCommand == widget->config.command, "non-audio local action dispatched");
    Widget* another = AddClock(2);
    StartWidgetAlarm(another);
    StopAllAlarms();
    Require(!widget->alarmActive && !another->alarmActive && !widget->flashPhase,
        "stop all clears every alarm");
    StartWidgetAlarm(nullptr);
    StopWidgetAlarm(nullptr);
    AudioFinished(999, 1);
}

/// Runs production alarm dispatch and signal-contributor code with inert external actions.
int main() {
    LoadTimeZoneList(&timeZones);
    TestContributors();
    TestTiming();
    TestActions();
    Reset(0);
    std::puts("PASS: alarm actions, shared pips, cancellation, output routing and stale audio completion");
    return 0;
}
