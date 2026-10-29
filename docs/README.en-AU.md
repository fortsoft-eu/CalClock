# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [English (UK)](README.en-GB.md) · **English (Australia)** · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Português](README.pt-PT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [Dansk](README.da-DK.md) · [Suomi](README.fi-FI.md) · [Íslenska](README.is-IS.md) · [Norsk (bokmål)](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Türkçe](README.tr-TR.md) · [Eesti](README.et-EE.md) · [Gaeilge](README.ga-IE.md) · [Lietuvių](README.lt-LT.md) · [Latviešu](README.lv-LV.md) · [Magyar](README.hu-HU.md) · [Malti](README.mt-MT.md) · [Nederlands](README.nl-NL.md) · [Română](README.ro-RO.md) · [Ελληνικά](README.el-GR.md) · [Bosanski](README.bs-Latn-BA.md) · [Hrvatski](README.hr-HR.md) · [Slovenščina](README.sl-SI.md) · [Crnogorski](README.cnr-Latn-ME.md) · [Беларуская](README.be-BY.md) · [Български](README.bg-BG.md) · [Македонски](README.mk-MK.md) · [Српски](README.sr-Cyrl-RS.md) · [Українська](README.uk-UA.md) · [Русский](README.ru-RU.md)

CalClock is a native Win32/x86 application for Windows Vista and later that displays independently configured floating clocks and calendars on the Windows desktop. It runs in the notification area and does not require a permanent control window.

## Features

- Up to 32 independently configured widgets
- Per-widget language, time zone, time offset, visibility, and always-on-top state
- Analog clocks based on the Windows `ClockWndMain` control, with platform-detected sizes and second-hand support
- Configurable digital clocks with fonts, colours, opacity, padding, borders, an optional leading zero, and an optional transparent background
- Native Windows calendars with selectable dates, four border styles, configurable border colour, week numbers, first-day settings, and 33 clipboard formats
- Calendar-and-clock panels with up to two additional named clocks in independent time zones, separate clock-face sizes, four border styles, configurable border colour, UTC text, a leading-zero option, and separate fonts for each text row
- Alarms with selectable weekdays, visual indication, internal audio playback, looping, local commands, and HTTP/HTTPS script calls
- Per-clock audible time signals at 1, 5, 10, 15, 20, 30, or 60-minute intervals, with coincident signals merged into one sequence on the same audio output
- Per-clock Mute commands and a checked Mute all command in the notification-area menu
- Optional automatic startup with Windows
- Optional five-pixel snapping to work-area edges while dragging widgets, enabled by default, with edge attachment preserved when a widget changes size
- NTP synchronisation without changing the Windows system clock
- Multiple NTP presets for Czechia and Slovakia, PTB, Ubuntu/NTP Pool, or custom servers
- Registry or XML settings storage, including XML import and export
- Notification-area controls with restoration of the most recently hidden widgets
- Widget identification and stable alignment to a non-overlapping grid
- Live appearance previews with cancellation and per-widget default appearance
- Application and widget fonts, visual-style controls, and ClearType, GDI, or no font antialiasing
- Interfaces in 36 language variants, with independent language selection for the application and each widget

## Widget types

| Widget | Description |
| --- | --- |
| Analog clock | A floating Windows clock face with the sizes and optional second hand supplied by the current Windows version |
| Digital clock | A configurable floating digital display with optional UTC text, leading zero, borders, and transparent background |
| Calendar | A movable native month calendar with date selection, configurable borders, and clipboard formats |
| Calendar with clock | A combined panel with a native calendar, an analog clock, configurable text rows, UTC display, and configurable borders |
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
- Remove or Del removes all selected items when the changes are applied. `Insert` toggles the current item and moves the list cursor down one row.
- Use `Ctrl+C` to copy selected widgets and `Ctrl+V` to append copies in list order. Copies include all widget settings and receive a name suffix in the application language. The Duplicate button performs the same duplication directly. Up to 32 widgets are allowed. If there is not enough room for all copies, those that fit are added in list order and a notification appears for the remaining copies.

Opening Settings from the notification-area icon returns to the last selected widget.

Settings remembers the last open tab and the last widget type added.

Calendar dates can be copied using 33 formats covering local, sortable, day-first, month-first, textual, and weekday forms. Every mask is available in every interface language. The default local short format follows the widget language, and textual month and weekday names also use that language. Format entries show the mask and a live example.

A calendar-and-clock panel can show up to two additional clocks. Enable each clock on the General tab and choose its name and time zone. Named zones follow their own daylight saving rules; fixed UTC offsets remain fixed. When additional clocks are enabled, each clock shows its local day of the week below its time. The three size lists on the Appearance tab control the main clock, Clock 1, and Clock 2 in that order. Right-click an additional clock face to choose its size. Additional clocks always omit seconds and share the widget's language, time format, fonts, and time offset. Adding, removing, or resizing clocks keeps the widget attached to the same work-area edges.

In a calendar-and-clock panel, the upper date is a link that returns the calendar to today, while the lower time-zone text opens the classic Windows Date and Time settings.

Calendar-and-clock panels can show Windows date and time notices above the lower link. **Date and time notices** on the **General** tab is enabled by default and saved separately for each panel. When several notices apply, they appear one below another as in Windows. If the option is off or there is no applicable notice, the panel keeps its original size and layout with no empty space reserved.

The `Arrange in a grid` command snaps visible desktop widgets to a stable, non-overlapping grid while preserving their approximate manual layout. The widget whose menu invoked the command remains in place; the notification-area command arranges each monitor independently. Monitor clocks are excluded.

## Appearance

For standalone calendars, **Today row** in the widget menu or on the Appearance tab in Settings controls whether the bottom Today row is visible. It is checked by default; clear it to hide the row and shrink the calendar to fit. The choice is saved separately for each widget. **Go to Today** remains available in the menu and returns to the month view. When the date changes according to each widget’s time, calendars select today automatically while preserving their current view.

Appearance changes are previewed immediately on the selected widget. `Default appearance` restores the defaults for that widget type. Closing Settings with unapplied changes asks whether to save them. This warning is enabled by default and can be turned off on the Application tab.

Digital clocks, calendars, and combined panels share four border styles. The single-line style also has a configurable border colour; the border-width control is available where the selected widget supports it. Transparent digital clocks retain the same style choices as opaque ones. Custom calendar fonts are supported with the Windows classic appearance or with visual styles turned off for the application or widget.

Application language, UI font, font smoothing, visual styles, settings storage, Windows startup, and work-area edge snapping are global and are configured on the Application tab. The time source is also global. Widget language, font smoothing, visual styles, time zone, offset, alarm, and audible time signal are configured independently. Font antialiasing offers **ClearType**, **GDI**, and **None**.

The **Audio volume** slider on the Alarm tab controls internally played audio files separately for each widget and shows the level in dB. The default is **−18 dB**, which preserves the file’s original level (**100%**). Moving the slider to the right amplifies the audio; the **0 dB** maximum is approximately **794%** of the original amplitude. The leftmost position is **−∞ dB** (silence). Changes take effect during the audio test. Amplification applies to decoded audio, including WAV, MP3, WMA, AAC, M4A, and FLAC when supported by Windows. Legacy playback for files that cannot be decoded, such as MIDI, is limited to 100%.

The alarm weekday controls follow the first day of the week used by the selected application culture. Stored alarm days retain their meaning when the application language changes. Enabling an alarm from a widget menu when no weekday is selected opens that widget's Alarm tab instead of enabling an alarm that cannot run.

**Leading zero** offers **Yes** (the default), **No, keep space**, and **No, without space**. **No, keep space** hides the zero while reserving its actual width in the selected font, so the other digits keep their positions even with proportional fonts. Monitor clocks default to white text on a black background.

## Time and alarms

Digital clocks, calendar-and-clock panels, and monitor clocks offer **Language default**, **12 hours**, and **24 hours** under **Time format** on the General tab. **Language default** is the default and follows the widget language: for example, US and Australian English use 12-hour time, while British English uses 24-hour time. A manual cycle selection is retained when the widget language changes. Time separators and AM/PM markers follow the selected culture; cultures without their own markers use **AM/PM** in 12-hour mode.

The **AM/PM** checkbox is checked by default. Turning it off hides the marker without changing the 12-hour cycle. Monitor clocks display the marker on a separate line below the time, just like the UTC label. UTC always uses 24-hour time. The leading-zero setting still controls whether the initial zero is shown, hidden with its space reserved, or omitted.

Named time zones show the civil time of the selected location and automatically follow that location's daylight saving rules. The offset next to each name reflects the current date and is refreshed when the list opens. Standalone **UTC** entries provide fixed offsets from **UTC−12:00** through **UTC+14:00**, in 15-minute steps, without daylight saving changes. Choose your local zone, any other named zone, or a fixed UTC offset independently for each widget.

New widgets default to **Current Windows time zone**, which follows the current Windows time zone and its automatic daylight saving setting. Existing widgets retain their selected zones. This choice affects the time zone; the shared Windows or NTP time source remains independent of it.

Each widget can use an arbitrary Windows time zone and a signed offset in the form `[-]HH:mm:ss.ff`. Compact offset input is interpreted from the right, starting with seconds.

The offset is useful in broadcast studios, for example, to compensate for transmission path delay. Advancing the studio clock by the measured delay allows its time signal to reach listeners at the intended time.

The widget offset is applied to UTC before conversion to its time zone, so it also shifts the instant of a daylight saving transition. A clock advanced by ten seconds changes ten seconds early; a clock delayed by ten seconds changes ten seconds late. Clock hands, digital text, calendar dates, alarms, and time signals use the resulting time.

The Time tab selects Windows system time or the configured NTP servers for the whole application and therefore for all widgets. NTP corrects only the time displayed by CalClock; the Windows clock is never changed. System time is used until the first valid reply. NTP is the default. The automatic set chooses Czech and Slovak servers, PTB for Europe, or the global pool according to the system region. Multiple measurements are filtered by network delay and outlying replies. Synchronise now starts a fresh measurement immediately.

After synchronisation, CalClock keeps time independently of later changes to Windows system time. If the connection fails or servers change, it continues from the last valid synchronisation until a new reply arrives; this state is retained until the application closes.

The Time tab records NTP server queries since the application started. Each entry contains the date and local computer time, server, and status. OK identifies a valid reply, with θ showing its offset from Windows system time. ERR gives the failure reason and any error code. The final entry in a query group also shows the combined offset Θ when usable measurements are available.

Offsets are displayed in milliseconds with four decimal places. A positive value means the server clock is ahead of Windows; a negative value means it is behind. The combined offset Θ reflects the accepted measurements and is also shown in the synchronisation status.

Save log exports the records to CSV, including offsets and failure details. Records are not retained between application sessions; save them before exiting if you want to keep them.

Clock widgets support alarms on individually selected weekdays; all seven days are enabled by default. An alarm makes its hidden widget visible and brings it in front of other windows without permanently changing its always-on-top setting. WAV, MP3, WMA, MIDI, AAC, M4A, and FLAC files are recognised for internal playback once or continuously; actual decoding support is provided by the multimedia components installed in Windows. Other files and commands are passed to Windows asynchronously. An alarm can also call an HTTP or HTTPS URL. Independently of these actions, an alarm may use the six-pip time signal whose first short pip sounds five seconds before the configured alarm time.

Alarm pips are scheduled from the actual upcoming alarm time after time-zone conversion and the widget offset. They start five elapsed seconds before that instant, including when the displayed clock jumps directly to the alarm time. A skipped spring alarm time produces neither an alarm nor its pips. During a repeated autumn hour, an alarm and its pips occur only once for the same date and configured time.

The alarm Test button previews the visual indication and asynchronously tests the configured file, command, audio and remote-script URL. When the alarm time signal is selected, Test also plays its complete six-pip sequence; Stop test ends internal audio and the signal preview.

The Signal tab has a Time signal active checkbox and radio buttons for intervals of 1, 5, 10, 15, 20, 30, or 60 minutes according to the widget's displayed time. Signals are initially off, with an hourly interval selected. Turning Signal off and on in the widget menu retains the interval. The menu shows the alarm time and signal interval in parentheses. The 20-minute interval signals at :00, :20, and :40 according to that displayed time. The signal follows the **Greenwich Time Signal (GTS)** pattern: five short pips mark the final five seconds and a longer pip marks the exact boundary. Time zones, UTC mode, offsets, and the current NTP correction are respected. Alarm signals and the Signal tab remain independently configured. Fractional widget offsets are respected. On each audio output, overlapping widget, alarm, and test tones play continuously until the last overlap ends.

**Time signal sound** on the Application tab lets you choose between **Built-in generator** (the default) and **System beep**. The choice applies to time signals from all widgets, including alarm time signals, and is saved with the global settings. For **Built-in generator**, the **Time signal volume** slider shows the level in dB for the entire application. The rightmost position is **0 dB**, the maximum undistorted sine-wave amplitude; silence is **−∞ dB**. The default volume is **−18 dB**. Stopping the test lets the current pip finish; a long pip can take up to half a second to end. Click **Test** next to **Time signal sound** to start a continuous preview, or **Stop test** to end it. Both **System beep** and **Built-in generator** can be tested; the test is not saved. Holding the volume slider also plays a preview until the mouse is released, unless the button test is running. Playback starts on the next whole second, with short tones every second and a long tone at :00, :05, :10, and so on. The sound choice is available only when the system supports both options.

**Audio output**

**Audio output** on the **Signal** tab selects a device for each sound-capable widget's regular time signals. This
does not change the widget's time zone, offset, or interval. The generator choice and signal volume remain global on
the **Application** tab. With **System beep**, the selector stays visible but greyed out and retains its device;
**Built-in generator** enables it again. Windows Vista uses the generator automatically.

**Windows default device** follows the current Windows default output. A specifically selected device remains selected
if disconnected and appears as **Unavailable device**; its signals stay silent until it becomes available or another
output is selected. The device list refreshes when opened. The selection is saved separately for each widget in
registry or XML settings.

Signals merge automatically for each output. An explicit device choice and Windows default device pointing to
that same device share one output. Different devices operate independently; the sine waveform, continuous
phase, and starts and ends at zero amplitude are preserved. Test audio output on the Application tab saves the
device for generator tests and volume previews. System beep disables only this selector. Alarms continue to
use the Windows default output. They merge with regular signals only on a shared output.

Alarm and time-signal enablement can also be toggled in each sound-capable widget's context menu. The alarm item shows its time and, unless all days are selected, its active weekdays. The checked Mute command affects its widget and is reflected by Muted on the General tab. A standalone Calendar supports neither alarms, time signals nor muting. The notification-area command is named Mute all; pressing `M` on any widget performs the same global toggle. Global unmute restores only the widgets muted by the preceding global action. Internal audio continues silently and resumes when unmuted. A pip already in progress may finish, while subsequent pips are skipped until sound is enabled again. Non-audio commands and remote scripts are unaffected.

## Settings and menus

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

Importing an XML file immediately loads and saves its settings to the currently selected storage backend without changing the storage type. The mute state is stored independently for each sound-capable widget.

## Building

Requirements:

- Microsoft Visual Studio with the MSVC v145 toolset
- Windows SDK

Open `CalClock.slnx`, select `Release | x86`, and build the solution. The executable is created as:

```text
Release\CalClock.exe
```

Only the Win32/x86 configuration is supported. The project intentionally does not provide an x64 configuration because its integration with the Windows clock control requires x86 compatibility.

After building, run `.\PackageRelease.ps1` to create `CalClock-<version>-win32.zip` containing the program and its
licence.

Signing parameters also take their defaults from Windows user environment variables: `BUILD_SIGNER_NAME`,
`BUILD_CERTIFICATE_THUMBPRINT`, `BUILD_SIGNTOOL_PATH`, `BUILD_TIMESTAMP_SERVER`. Explicit command-line arguments take
precedence.

## Licence

CalClock is available under the [MIT License](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
