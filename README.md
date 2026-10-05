# CalClock

[Čeština](docs/README.cs-CZ.md) · **English (US)** · [Deutsch](docs/README.de-DE.md) · [Français](docs/README.fr-FR.md) · [Español](docs/README.es-ES.md) · [Italiano](docs/README.it-IT.md) · [Polski](docs/README.pl-PL.md) · [Slovenčina](docs/README.sk-SK.md) · [English (UK)](docs/README.en-GB.md) · [English (Australia)](docs/README.en-AU.md) · [Português](docs/README.pt-PT.md) · [Norsk](docs/README.nb-NO.md) · [Svenska](docs/README.sv-SE.md) · [Suomi](docs/README.fi-FI.md) · [Dansk](docs/README.da-DK.md) · [Íslenska](docs/README.is-IS.md) · [Türkçe](docs/README.tr-TR.md)

CalClock is a native Win32/x86 application for Windows Vista and later that displays independently configured floating clocks and calendars on the Windows desktop. It runs in the notification area and does not require a permanent control window.

## Features

- Up to 32 independently configured widgets
- Per-widget language, time zone, time offset, visibility, and always-on-top state
- Analog clocks based on the Windows `ClockWndMain` control, with platform-detected sizes and second-hand support
- Configurable digital clocks with fonts, colors, opacity, padding, borders, an optional leading zero, and an optional transparent background
- Native Windows calendars with selectable dates, four border styles, configurable border color, week numbers, first-day settings, and 33 clipboard formats
- Calendar-and-clock panels with up to two additional named clocks in independent time zones, separate clock-face sizes, four border styles, configurable border color, UTC text, a leading-zero option, and separate fonts for each text row
- Alarms with selectable weekdays, visual indication, internal audio playback, looping, local commands, and HTTP/HTTPS script calls
- Per-clock audible time signals at 1, 5, 10, 15, 20, 30, or 60-minute intervals, with coincident signals merged into one sequence
- Per-clock Mute commands and a checked Mute all command in the notification-area menu
- Optional automatic startup with Windows
- Optional five-pixel snapping to work-area edges while dragging widgets, enabled by default, with edge attachment preserved when a widget changes size
- NTP synchronization without changing the Windows system clock
- Multiple NTP presets for Czechia and Slovakia, PTB, Ubuntu/NTP Pool, or custom servers
- Registry or XML settings storage, including XML import and export
- Notification-area controls with restoration of the most recently hidden widgets
- Widget identification and stable alignment to a non-overlapping grid
- Live appearance previews with cancellation and per-widget default appearance
- Application and widget fonts, visual-style controls, and ClearType, GDI, or no font antialiasing
- Czech, US English, British English, Australian English, German, French, Spanish, Italian, Portuguese, Polish, Slovak, Danish, Finnish, Icelandic, Norwegian, Swedish, and Turkish interfaces

## Widget types

| Widget | Description |
| --- | --- |
| Analog clock | A floating Windows clock face with the sizes and optional second hand supplied by the current Windows version |
| Digital clock | A configurable floating digital display with optional UTC text, leading zero, borders, and transparent background |
| Calendar | A movable native month calendar with date selection, configurable borders, and clipboard formats |
| Calendar and clock | A combined panel with a native calendar, an analog clock, configurable text rows, UTC display, and configurable borders |
| Monitor clock | A digital clock filling one or more selected monitors, with optional blackout and UTC on a separate line |

On first launch, CalClock selects the application language from the Windows user-interface language and falls back to US English when it is unsupported. It creates one visible analog clock by default. Every widget retains its own position and settings between runs. While Settings is open, a monitor clock is always represented by a movable preview with the aspect ratio of its selected monitor. `Esc` dismisses a monitor clock and removes its blackout even when Settings is active. The pointer hides after a short period of inactivity over monitor clocks and blacked-out monitors and reappears when the mouse moves. It stays visible over the small Settings preview.

## Controls

- Drag a clock or panel with the left mouse button.
- Drag a standalone calendar by its free area.
- Right-click a widget or the notification-area icon to open its context menu.
- Left-click the notification-area icon to hide the visible widgets. When all widgets are hidden, another click restores only the widgets hidden most recently.
- Double-click a clock face to toggle the seconds display. In a calendar-and-clock panel, only a double-click directly on the main analog clock face toggles the second hand. Additional clocks have no second hand.
- Press `F1` for Help, `B` for Settings, `M` to toggle Mute all, or `Esc` to hide a widget or stop an active alarm.
- Press `Alt+0`, `Alt+1`, `Alt+2`, or `Alt+3` on an Analog clock or Calendar with clock widget to select the main clock face size, from smallest to largest.
- Double-click a widget in Settings to make it visible if necessary, select `Visible`, and identify it briefly on the desktop.
- Open Settings from a widget's context menu to select that widget immediately.
- Use `Ctrl` or `Shift` for multiple selection in the widget list, `Ctrl+A` to select all, and `Del` to remove the selected widgets. `Insert` toggles the current item and moves the list cursor to the next row, as in Total Commander.
- All widget-list shortcuts also work while the Remove or Duplicate button has focus. Using a shortcut on either button moves focus to the widget list and performs the action. Use `Ctrl+C` to copy selected widgets and `Ctrl+V` to append copies in list order. Copies include all widget settings and receive a name suffix in the application language. The Duplicate button performs the same duplication directly. Up to 32 widgets are allowed. If there is not enough room for all copies, those that fit are added in list order and a notification appears for the remaining copies.
- Use `Ctrl+A` or triple-click in a text field to select all its text.

When several widgets are selected, their General, Appearance, Alarm, and Signal controls are disabled, while the global Time and Application tabs remain available. Settings remembers the last open tab and the last widget type added. On a small work area, the Settings window provides horizontal or vertical scrolling as required.

Calendar dates can be copied using 33 formats covering local, sortable, day-first, month-first, textual, and weekday forms. Every mask is available in every interface language. The default local short format follows the widget language, and textual month and weekday names also use that language. Format entries show the mask and a live example.

A calendar-and-clock panel can show up to two additional clocks. Enable each clock on the General tab and choose its name and time zone. Named zones follow their own daylight saving rules; fixed UTC offsets remain fixed. When additional clocks are enabled, each clock shows its local day of the week below its time. The three size lists on the Appearance tab control the main clock, Clock 1, and Clock 2 in that order. Right-click an additional clock face to choose its size. Additional clocks always omit seconds and share the widget's language, time format, fonts, and time offset. Adding, removing, or resizing clocks keeps the widget attached to the same work-area edges.

In a calendar-and-clock panel, the upper date is a link that returns the calendar to today, while the lower time-zone text opens the classic Windows Date and Time settings. Both links can be reached with `Tab`, show a focus rectangle, and can be activated from the keyboard. The native calendar remains fully interactive but omits its redundant Today row in this combined layout.

The `Arrange in a grid` command snaps visible desktop widgets to a stable, non-overlapping grid while preserving their approximate manual layout. The widget whose menu invoked the command remains in place; the notification-area command arranges each monitor independently. Monitor clocks are excluded.

## Appearance

For standalone calendars, **Today row** in the widget menu or on the Appearance tab in Settings controls whether the bottom Today row is visible. It is checked by default; clear it to hide the row and shrink the calendar to fit. The choice is saved separately for each widget. **Go to Today** remains available in the menu and returns to the month view. When the date changes according to each widget’s time, calendars select today automatically while preserving their current view.

Appearance changes are previewed immediately on the selected widget. `Cancel` restores unapplied appearance changes, while `Default appearance` restores the defaults for that widget type.

Digital clocks, calendars, and combined panels share four border styles. The single-line style also has a configurable border color; the border-width control is available where the selected widget supports it. Transparent digital clocks retain the same style choices as opaque ones. Font dialogs show only the choices used by their target and omit the unused preview and effects; application and calendar UI fonts omit size, while digital and panel text fonts include it. A native calendar accepts a custom font only when visual styles are disabled for it or for the application.

Application language, UI font, font smoothing, visual styles, settings storage, Windows startup, and work-area edge snapping are global and are configured on the Application tab. The time source is also global. Widget language, font smoothing, visual styles, time zone, offset, alarm, and audible time signal are configured independently. Applying a new application language immediately rebuilds the open Settings window in that language. Font antialiasing offers **ClearType**, **GDI**, and **None**. On the Appearance tab, font antialiasing and the option to disable themes occupy the same position for every widget type, with **Default appearance** below them.

The **Audio volume** slider on the Alarm tab controls internally played audio files separately for each widget and shows the level in dB. The default is **−18 dB**, which preserves the file’s original level (**100%**). Moving the slider to the right amplifies the audio; the **0 dB** maximum is approximately **794%** of the original amplitude. The leftmost position is **−∞ dB** (silence). Changes take effect during the audio test. The slider is disabled for files opened in an external application. Amplification applies to decoded audio, including WAV, MP3, WMA, AAC, M4A, and FLAC when supported by Windows. Legacy playback for files that cannot be decoded, such as MIDI, is limited to 100%.

The alarm weekday controls follow the first day of the week used by the selected application culture. Stored alarm days retain their meaning when the application language changes. Enabling an alarm from a widget menu when no weekday is selected opens that widget's Alarm tab instead of enabling an alarm that cannot run.

The default digital-clock border width is zero. **Leading zero** offers **Show** (the default), **Keep space**, and **No space**. **Keep space** hides the zero while reserving its actual width in the selected font, so the other digits keep their positions even with proportional fonts. Floating digital clocks align time to the left and keep a fixed size as time advances. Monitor clocks center a fixed time area sized for the selected font and format, including space for two hour digits. Changing time does not recenter or resize the text. The AM/PM or UTC row stays centered independently. Monitor clocks default to white text on a black background.

## Time and alarms

Digital clocks, calendar-and-clock panels, and monitor clocks offer **Language default**, **12 hours**, and **24 hours** under **Time format** on the General tab. **Language default** is the default and follows the widget language: for example, US and Australian English use 12-hour time, while British English uses 24-hour time. A manual cycle selection is retained when the widget language changes. Time separators and AM/PM markers follow the selected culture; cultures without their own markers use **AM/PM** in 12-hour mode.

The **AM/PM** checkbox is checked by default. Turning it off hides the marker without changing the 12-hour cycle. It is disabled in 24-hour mode and for widgets without a digital time display. Monitor clocks display the marker on a separate line below the time, just like the UTC label. **UTC always uses 24-hour time**; the cycle and AM/PM controls are disabled while UTC is selected, and the saved choices are retained for returning to local time. The leading-zero setting still controls whether the initial zero is shown, hidden with its space reserved, or omitted.

Named time zones show the civil time of the selected location and automatically follow that location's daylight saving rules. The offset next to each name reflects the current date and is refreshed when the list opens. Standalone **UTC** entries provide fixed offsets from **UTC−12:00** through **UTC+14:00**, in 15-minute steps, without daylight saving changes. Choose your local zone, any other named zone, or a fixed UTC offset independently for each widget.

Each widget can use an arbitrary Windows time zone and a signed offset in the form `[-]HH:mm:ss.ff`. Compact offset input is interpreted from the right, starting with seconds.

The offset is useful in broadcast studios, for example, to compensate for transmission path delay. Advancing the studio clock by the measured delay allows its time signal to reach listeners at the intended time.

CalClock can use either the Windows system time or an application-local correction obtained from NTP servers. This selection is global for all widgets. Synchronization never changes the Windows clock. If an NTP connection is lost after a successful synchronization, the last known correction remains active in process memory. Changing servers also retains the current valid correction until a new response is obtained.

Clock widgets support alarms on individually selected weekdays; all seven days are enabled by default. An alarm makes its hidden widget visible and brings it in front of other windows without permanently changing its always-on-top setting. WAV, MP3, WMA, MIDI, AAC, M4A, and FLAC files are recognized for internal playback once or continuously; actual decoding support is provided by the multimedia components installed in Windows. Other files and commands are passed to Windows asynchronously. An alarm can also call an HTTP or HTTPS URL. Independently of these actions, an alarm may use the six-pip time signal whose first short pip sounds five seconds before the configured alarm time.

Run a file or command enables its field, Browse button, Test button, and looping option. Test and looping additionally require a nonblank field, but a running test can always be stopped. The alarm Test button previews the visual indication and asynchronously tests the configured file, command, audio and remote-script URL. When the alarm time signal is selected, Test also plays its complete six-pip sequence; Stop test ends internal audio and the signal preview.

The Signal tab has a Time signal active checkbox and radio buttons for intervals of 1, 5, 10, 15, 20, 30, or 60 minutes according to the widget's displayed time. Signals are initially off, with an hourly interval selected. Turning Signal off and on in the widget menu retains the interval. The menu shows the alarm time and signal interval in parentheses. The 20-minute interval signals at :00, :20, and :40 according to that displayed time. The signal follows the **Greenwich Time Signal (GTS)** pattern: five short pips mark the final five seconds and a longer pip marks the exact boundary. Time zones, UTC mode, offsets, and the current NTP correction are respected. Alarm signals and the Signal tab remain independently configured; if any of their schedules meet at the same instant, CalClock plays only one shared sequence. Fractional widget offsets are respected, and overlapping widget, alarm, and test tones play continuously until the last overlap ends.

**Time signal sound** on the Application tab lets you choose between **Built-in generator** (the default) and **System beep**. The choice applies to time signals from all widgets, including alarm time signals, and is saved with the global settings. For **Built-in generator**, the **Time signal volume** slider shows the level in dB for the entire application. The rightmost position is **0 dB**, the maximum undistorted sine-wave amplitude; silence is **−∞ dB**. The default volume is **−18 dB**. The slider follows a decibel scale, with −18 dB at the midpoint. The built-in generator starts and ends tones at a zero crossing, including when a test is stopped. Stopping the test lets the current pip finish; a long pip can take up to half a second to end. Click **Test** next to **Time signal sound** to start a continuous preview, or **Stop test** to end it. Both **System beep** and **Built-in generator** can be tested; the test is not saved. Holding the volume slider also plays a preview until the mouse is released, unless the button test is running. Playback starts on the next whole second, with short tones every second and a long tone at :00, :05, :10, and so on. The preview and simultaneous widget or alarm time signals share a single tone. Only the volume slider is disabled for **System beep**. The sound choice is available only when the system supports both options.

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

After XML storage is written successfully, CalClock removes its application state from the registry. Switching back to registry storage analogously removes the automatic XML settings file and empty CalClock directories. Importing an XML file immediately loads and saves its settings to the currently selected storage backend without changing the storage type. The mute state is stored independently for each sound-capable widget. Start with Windows is stored as the `CalClock` value under the current user's standard Windows `Run` registry key.

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
