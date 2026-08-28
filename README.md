# CalClock

CalClock is a native Win32 application for displaying independently configured floating clocks and calendars on the Windows desktop. It runs in the notification area and does not require a permanent control window.

## Features

- Any number of independently configured widgets
- Per-widget language, time zone, time offset, visibility, and always-on-top state
- Analog clocks based on the Windows `ClockWndMain` control
- Configurable digital clocks with fonts, colours, opacity, padding, borders, and an optional transparent background
- Native Windows calendars with selectable dates, week numbers, first-day settings, and multiple copy formats
- Alarms with visual indication, internal audio playback, looping, local commands, and HTTP/HTTPS script calls
- NTP synchronization without changing the Windows system clock
- Multiple NTP presets for Czechia and Slovakia, PTB, Ubuntu/NTP Pool, or custom servers
- Registry or XML settings storage, including XML import and export
- Notification-area controls, widget identification, and alignment to a non-overlapping grid
- Application and widget font antialiasing options, including GDI and ClearType
- Czech, English, German, French, Spanish, Italian, Polish, and Slovak interfaces

## Widget types

| Widget | Description |
| --- | --- |
| Analog clock | A floating Windows clock face with four sizes and optional seconds |
| Digital clock | A configurable floating digital display with optional UTC text and transparent background |
| Calendar | A movable native month calendar with date selection and clipboard formats |
| Calendar and clock | A combined panel containing a native calendar, an analog clock, and a time display |
| Monitor clock | A digital clock filling one or more selected monitors, with optional blackout of the remaining monitors |

Every widget retains its own position and settings between runs. Monitor clocks also provide a movable preview in Settings and can always be dismissed with `Esc`.

## Controls

- Drag a clock or panel with the left mouse button.
- Drag a standalone calendar by its free area.
- Right-click a widget or the notification-area icon to open its context menu.
- Left-click the notification-area icon to show or hide all widgets.
- Double-click a clock face to toggle the seconds display.
- Press `F1` for Help, `B` for Settings, or `Esc` to hide a widget or stop an active alarm.
- Double-click a widget in Settings to identify it briefly on the desktop.

Calendar dates can be copied in local short and long forms or in a selection of fixed formats. The alignment command snaps visible desktop widgets to a stable, non-overlapping grid; monitor clocks are excluded.

## Time and alarms

Each widget can use an arbitrary Windows time zone and a signed offset in the form `[-]HH:mm:ss.ff`. Compact offset input is interpreted from the right, starting with seconds.

CalClock can use either the Windows system time or an application-local correction obtained from NTP servers. Synchronization never changes the Windows clock. If an NTP connection is lost after a successful synchronization, the last known correction remains active in process memory.

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

Copyright © 2026 Petr Červinka — FortSoft
