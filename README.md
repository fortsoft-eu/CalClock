# CalClock

CalClock is a native Win32/x86 application for Windows Vista and later that displays independently configured floating clocks and calendars on the Windows desktop. It runs in the notification area and does not require a permanent control window.

## Features

- Any number of independently configured widgets
- Per-widget language, time zone, time offset, visibility, and always-on-top state
- Analog clocks based on the Windows `ClockWndMain` control, with platform-detected sizes and second-hand support
- Configurable digital clocks with fonts, colours, opacity, padding, borders, an optional leading zero, and an optional transparent background
- Native Windows calendars with selectable dates, optional frames, week numbers, first-day settings, and 33 clipboard formats
- Calendar-and-clock panels with four clock-face sizes, optional frames and UTC text, a leading-zero option, and separate fonts for each text row
- Alarms with selectable weekdays, visual indication, internal audio playback, looping, local commands, and HTTP/HTTPS script calls
- Per-clock audible time signals at 1, 5, 10, 15, 30, or 60-minute intervals, with coincident signals merged into one sequence
- Per-clock Mute commands and a checked Mute all command in the notification-area menu
- Optional automatic startup with Windows
- Optional five-pixel snapping to work-area edges while dragging widgets, enabled by default, with edge attachment preserved when a widget changes size
- NTP synchronization without changing the Windows system clock
- Multiple NTP presets for Czechia and Slovakia, PTB, Ubuntu/NTP Pool, or custom servers
- Registry or XML settings storage, including XML import and export
- Notification-area controls with restoration of the most recently hidden widgets
- Widget identification and stable alignment to a non-overlapping grid
- Live appearance previews with cancellation and per-widget default appearance
- Application and widget fonts, visual-style controls, and GDI or ClearType font antialiasing
- Czech, US English, British English, Australian English, German, French, Spanish, Italian, Portuguese, Polish, Slovak, Danish, Finnish, Icelandic, Norwegian, Swedish, and Turkish interfaces

## Widget types

| Widget | Description |
| --- | --- |
| Analog clock | A floating Windows clock face with the sizes and optional second hand supplied by the current Windows version |
| Digital clock | A configurable floating digital display with optional UTC text, leading zero, borders, and transparent background |
| Calendar | A movable native month calendar with date selection, an optional frame, and clipboard formats |
| Calendar and clock | A combined panel with a native calendar, an analog clock, configurable text rows, UTC display, and an optional frame |
| Monitor clock | A digital clock filling one or more selected monitors, with optional blackout and UTC on a separate line |

On first launch, CalClock selects the application language from the Windows user-interface language and falls back to US English when it is unsupported. It creates one visible analog clock by default. Every widget retains its own position and settings between runs. While Settings is open, a monitor clock is always represented by a movable preview with the aspect ratio of its selected monitor. `Esc` dismisses a monitor clock and removes its blackout even when Settings is active.

## Controls

- Drag a clock or panel with the left mouse button.
- Drag a standalone calendar by its free area.
- Right-click a widget or the notification-area icon to open its context menu.
- Left-click the notification-area icon to hide the visible widgets. When all widgets are hidden, another click restores only the widgets hidden most recently.
- Double-click a clock face to toggle the seconds display.
- Press `F1` for Help, `B` for Settings, `M` to toggle Mute all, or `Esc` to hide a widget or stop an active alarm.
- Double-click a widget in Settings to make it visible if necessary, select `Visible`, and identify it briefly on the desktop.
- Open Settings from a widget's context menu to select that widget immediately.
- Use `Ctrl` or `Shift` for multiple selection in the widget list, `Ctrl+A` to select all, and `Del` to remove the selected widgets. `Insert` toggles the current item and moves the list cursor to the next row, as in Total Commander.
- Use `Ctrl+A` or triple-click in a text field to select all its text.

When several widgets are selected, their General, Appearance, Alarm, and Signal controls are disabled, while the global Time and Application tabs remain available. Settings remembers the last open tab and the last widget type added. On a small work area, the Settings window provides horizontal or vertical scrolling as required.

Calendar dates can be copied using 33 formats covering local, sortable, day-first, month-first, textual, and weekday forms. Every mask is available in every interface language. The default local short format follows the widget language, and textual month and weekday names also use that language. Format entries show the mask and a live example.

In a calendar-and-clock panel, the upper date is a link to today and is underlined while the pointer is over it. The native calendar remains fully interactive but omits its redundant Today row in this combined layout.

The `Arrange in a grid` command snaps visible desktop widgets to a stable, non-overlapping grid while preserving their approximate manual layout. The widget whose menu invoked the command remains in place; the notification-area command arranges each monitor independently. Monitor clocks are excluded.

## Appearance

Appearance changes are previewed immediately on the selected widget. `Cancel` restores unapplied appearance changes, while `Default appearance` restores the defaults for that widget type.

Digital widgets provide controls for font, font smoothing, colours, opacity, padding, border style and width, and transparent background where applicable. Font dialogs show only the choices used by their target; application and calendar UI fonts omit size, while digital and panel text fonts include it. Calendars and combined panels can show or hide their frame. A native calendar accepts a custom font only when visual styles are disabled for it or for the application.

Application language, UI font, font smoothing, visual styles, settings storage, Windows startup, and work-area edge snapping are global and are configured on the Application tab. The time source is also global. Widget language, font smoothing, visual styles, time zone, offset, alarm, and audible time signal are configured independently. Applying a new application language immediately rebuilds the open Settings window in that language.

The alarm weekday controls follow the first day of the week used by the selected application culture. Stored alarm days retain their meaning when the application language changes. Enabling an alarm from a widget menu when no weekday is selected opens that widget's Alarm tab instead of enabling an alarm that cannot run.

The default digital-clock border width is zero, and widgets that support a leading zero start with it disabled. Monitor clocks default to white text on a black background.

## Time and alarms

Each widget can use an arbitrary Windows time zone and a signed offset in the form `[-]HH:mm:ss.ff`. Compact offset input is interpreted from the right, starting with seconds.

CalClock can use either the Windows system time or an application-local correction obtained from NTP servers. This selection is global for all widgets. Synchronization never changes the Windows clock. If an NTP connection is lost after a successful synchronization, the last known correction remains active in process memory. Changing servers also retains the current valid correction until a new response is obtained.

Clock widgets support alarms on individually selected weekdays; all seven days are enabled by default. An alarm makes its hidden widget visible and brings it in front of other windows without permanently changing its always-on-top setting. WAV, MP3, WMA, MIDI, AAC, M4A, and FLAC files are recognized for internal playback once or continuously; actual decoding support is provided by the multimedia components installed in Windows. Other files and commands are passed to Windows asynchronously. An alarm can also call an HTTP or HTTPS URL. Independently of these actions, an alarm may use the six-pip time signal whose first short pip sounds five seconds before the configured alarm time.

Run a file or command enables its field, Browse button, Test button, and looping option. Test and looping additionally require a nonblank field, but a running test can always be stopped. The alarm Test button previews the visual indication and asynchronously tests the configured file, command, audio and remote-script URL. When the alarm time signal is selected, Test also plays its complete six-pip sequence; Stop test ends internal audio and the signal preview.

The per-widget Signal tab can disable audible time signals or schedule them every 1, 5, 10, 15, 30, or 60 minutes according to that widget's displayed time. Five short pips mark the final five seconds and a longer pip marks the exact boundary. Time zones, UTC mode, offsets, and the current NTP correction are respected. Alarm signals and the Signal tab remain independently configured; if any of their schedules meet at the same instant, CalClock plays only one shared sequence.

Alarm and time-signal enablement can also be toggled in each sound-capable widget's context menu. The alarm item shows its time and, unless all days are selected, its active weekdays. The checked Mute command affects its widget and is reflected by Muted on the General tab. A standalone Calendar has no alarm, time signal, or mute state, so these commands and settings are omitted or disabled for it. The notification-area command is named Mute all; pressing `M` on any widget performs the same global toggle. Global unmute restores only the widgets muted by the preceding global action. Internal audio continues silently and resumes when unmuted. A pip already in progress may finish, while subsequent pips are skipped until sound is enabled again. Non-audio commands and remote scripts are unaffected.

## Settings and menus

`Save` applies changes and closes Settings, `Apply` applies them while keeping Settings open, and `Cancel` discards changes not yet applied, including live appearance previews. Enter activates `Save`; Esc activates `Cancel`.

Each widget menu contains the commands applicable to that type—visibility, always-on-top state, seconds, analog size, or date-copy format—followed by `Arrange in a grid`, Settings, Help, About, and Exit. The notification-area menu lists every widget with its ordinal number, then provides Show all, Hide all, and Mute all. The separately grouped `Arrange in a grid` command follows before the application commands.

Showing or restoring widgets brings them in front of other windows without changing their always-on-top setting. CalClock ensures that at least one widget is visible after startup. A second launch activates the existing CalClock instance and restores the widgets hidden most recently when none are visible. The notification icon is registered again automatically if Windows Explorer restarts. If the system `ClockWndMain` control does not support a second hand at the selected size, the Seconds command is disabled while the stored preference is retained for another supported size.

## Settings storage

By default, settings are stored under:

```text
HKEY_CURRENT_USER\Software\FortSoft\CalClock
```

XML storage can be enabled in Settings. It uses:

```text
%AppData%\FortSoft\CalClock\settings.xml
```

After XML storage is written successfully, CalClock removes its application state from the registry. Switching back to registry storage analogously removes the automatic XML settings file and empty CalClock directories. Importing an XML file loads it into the current application state while preserving the currently selected storage backend. The mute state is stored independently for each sound-capable widget. Start with Windows is stored as the `CalClock` value under the current user's standard Windows `Run` registry key.

## Building

Requirements:

- Microsoft Visual Studio with the MSVC v145 toolset
- Windows SDK

Open `CalClock.slnx`, select `Release | Win32`, and build the solution. The executable is created as:

```text
Release\CalClock.exe
```

Only the Win32/x86 configuration is supported. The project intentionally does not provide an x64 configuration because its integration with the Windows clock control requires x86 compatibility.

## License

CalClock is available under the [MIT License](license.txt).

Copyright © Petr Červinka — FortSoft 2026
