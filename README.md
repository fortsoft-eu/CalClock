# CalClock

CalClock is a native Win32 application for displaying independently configured floating clocks and calendars on the Windows desktop. It runs in the notification area and does not require a permanent control window.

## Features

- Any number of independently configured widgets
- Per-widget language, time zone, time offset, visibility, and always-on-top state
- Analog clocks based on the Windows `ClockWndMain` control
- Configurable digital clocks with fonts, colours, opacity, padding, borders, an optional leading zero, and an optional transparent background
- Native Windows calendars with selectable dates, optional frames, week numbers, first-day settings, and 33 clipboard formats
- Calendar-and-clock panels with four clock-face sizes, optional frames and UTC text, a leading-zero option, and separate fonts for each text row
- Alarms with visual indication, internal audio playback, looping, local commands, and HTTP/HTTPS script calls
- NTP synchronization without changing the Windows system clock
- Multiple NTP presets for Czechia and Slovakia, PTB, Ubuntu/NTP Pool, or custom servers
- Registry or XML settings storage, including XML import and export
- Notification-area controls with restoration of the most recently hidden widgets
- Widget identification and stable alignment to a non-overlapping grid
- Live appearance previews with cancellation and per-widget default appearance
- Application and widget fonts, visual-style controls, and GDI or ClearType font antialiasing
- Czech, English, German, French, Spanish, Italian, Polish, and Slovak interfaces

## Widget types

| Widget | Description |
| --- | --- |
| Analog clock | A floating Windows clock face with four sizes and optional seconds |
| Digital clock | A configurable floating digital display with optional UTC text, leading zero, borders, and transparent background |
| Calendar | A movable native month calendar with date selection, an optional frame, and clipboard formats |
| Calendar and clock | A combined panel with a native calendar, an analog clock, configurable text rows, UTC display, and an optional frame |
| Monitor clock | A digital clock filling one or more selected monitors, with optional blackout of the remaining monitors |

Every widget retains its own position and settings between runs. While Settings is open, a monitor clock is always represented by a movable preview with the aspect ratio of its selected monitor. `Esc` dismisses a monitor clock and removes its blackout even when Settings is active.

## Controls

- Drag a clock or panel with the left mouse button.
- Drag a standalone calendar by its free area.
- Right-click a widget or the notification-area icon to open its context menu.
- Left-click the notification-area icon to hide the visible widgets. When all widgets are hidden, another click restores only the widgets hidden most recently.
- Double-click a clock face to toggle the seconds display.
- Press `F1` for Help, `B` for Settings, or `Esc` to hide a widget or stop an active alarm.
- Double-click a widget in Settings to identify it briefly on the desktop.
- Open Settings from a widget's context menu to select that widget immediately.
- Use `Ctrl` or `Shift` for multiple selection in the widget list, `Ctrl+A` to select all, and `Del` to remove the selected widgets.
- Use `Ctrl+A` or triple-click in a text field to select all its text.

When several widgets are selected, their General, Appearance, and Alarm controls are disabled, while the global Time tab remains available. Settings remembers the last open tab and the last widget type added.

Calendar dates can be copied using 33 formats covering local, sortable, day-first, month-first, textual, and weekday forms. Every mask is available in every interface language. The default local short format follows the widget language, and textual month and weekday names also use that language. Format entries show the mask and a live example.

The alignment command snaps visible desktop widgets to a stable, non-overlapping grid while preserving their approximate manual layout. Monitor clocks are excluded.

## Appearance

Appearance changes are previewed immediately on the selected widget. `Cancel` restores unapplied appearance changes, while `Default appearance` restores the defaults for that widget type.

Digital widgets provide controls for font, font smoothing, colours, opacity, padding, border style and width, and transparent background where applicable. Calendars and combined panels can show or hide their frame. A native calendar accepts a custom font only when visual styles are disabled for it or for the application.

The default digital-clock border width is zero, and widgets that support a leading zero start with it disabled. Monitor clocks default to white text on a black background.

## Time and alarms

Each widget can use an arbitrary Windows time zone and a signed offset in the form `[-]HH:mm:ss.ff`. Compact offset input is interpreted from the right, starting with seconds.

CalClock can use either the Windows system time or an application-local correction obtained from NTP servers. This selection is global for all widgets. Synchronization never changes the Windows clock. If an NTP connection is lost after a successful synchronization, the last known correction remains active in process memory. Changing servers also retains the current valid correction until a new response is obtained.

Clock widgets support alarms. Audio files can be played internally once or continuously, while other files and commands are passed to Windows asynchronously. An alarm can also call an HTTP or HTTPS URL.

## Settings storage

By default, settings are stored under:

```text
HKEY_CURRENT_USER\Software\FortSoft\CalClock
```

XML storage can be enabled in Settings. It uses:

```text
%AppData%\FortSoft\CalClock\settings.xml
```

After XML storage is written successfully, CalClock removes its application state from the registry. Switching back to registry storage analogously removes the automatic XML settings file and empty CalClock directories. Importing an XML file loads it into the current application state while preserving the currently selected storage backend.

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
