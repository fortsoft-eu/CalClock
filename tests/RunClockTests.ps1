<#
This is open-source software licensed under the terms of the MIT License.

Copyright (c) 2026 Petr Červinka - FortSoft <cervinka@fortsoft.eu>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Last modified for version 1.7.1.3

.SYNOPSIS
Builds CalClock and runs continuous-clock, alarm, wake, playback and isolated Settings regression tests.

.DESCRIPTION
Builds Release | x86, then runs clock, alarm scheduling, wake, playback and Settings regression tests.
Tests use installed time-zone rules and simulated UTC instants for sleep, delayed processing, source changes,
offsets, weekdays and daylight-saving transitions. Actual production handlers are extracted for isolated
message and action tests. PCM tests never start audio hardware. Native Settings controls run hidden on a
private desktop without activation; local and remote alarm actions are captured instead of executed.
The computer is never suspended and its time is never changed. Actual hardware wake support is not tested.
Generated files are placed in CalClock/Release/clock-tests. A build or test failure stops the script.
Creating the private desktop requires a normal Windows process token rather than a restricted sandbox token.

.PARAMETER VisualStudioPath
Optional Visual Studio installation directory containing VC/Auxiliary/Build/vcvars32.bat and
MSBuild/Current/Bin.
When omitted, vswhere selects the latest installed Visual Studio with the C++ build tools, including
prereleases.

.EXAMPLE
.\tests\RunClockTests.ps1

Builds and runs all clock regression tests using the automatically selected Visual Studio installation.
#>
param([string]$VisualStudioPath)

# Extracts actual production functions for isolated tests without maintaining copies of scheduling logic.
function Get-TestFunctions([string]$Source, [string[]]$Names) {
    $parts = foreach ($functionName in $Names) {
        $escapedName = [regex]::Escape($functionName)
        $pattern = '(?ms)^[A-Za-z_][^\r\n;{}]*\b' + $escapedName + '\([^;{]*\)\s*\{.*?^\}'
        $matches = [regex]::Matches($Source, $pattern)
        if ($matches.Count -ne 1) { throw "Expected one definition: $functionName" }
        $matches[0].Value
    }
    return $parts -join "`r`n`r`n"
}

# Copies an exact marked source range and fails when its boundaries are missing or ambiguous.
function Get-TestRange([string]$Source, [string]$Start, [string]$End) {
    $first = $Source.IndexOf($Start, [StringComparison]::Ordinal)
    $last = $Source.IndexOf($End, $first + $Start.Length, [StringComparison]::Ordinal)
    if ($first -lt 0 -or $last -lt 0) { throw "Missing production range: $Start" }
    return $Source.Substring($first, $last - $first)
}

# Writes generated test inputs using the project's source encoding and line endings.
function Write-TestHeader([string]$Name, [string]$Content) {
    $normalized = $Content.Replace("`r`n", "`n").Replace("`n", "`r`n")
    [IO.File]::WriteAllText((Join-Path $buildRoot $Name), $normalized, [Text.UTF8Encoding]::new($true))
}

$ErrorActionPreference = 'Stop'
$projectRoot = Split-Path -Parent $PSScriptRoot
if (-not $VisualStudioPath) {
    $vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio/Installer/vswhere.exe'
    $VisualStudioPath = & $vswhere -latest -prerelease -products '*' `
        -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
}
if (-not $VisualStudioPath) {
    throw 'A Visual Studio installation with C++ build tools is required.'
}
$vcvars = Join-Path $VisualStudioPath 'VC/Auxiliary/Build/vcvars32.bat'
$msbuild = Join-Path $VisualStudioPath 'MSBuild/Current/Bin/MSBuild.exe'
$buildRoot = Join-Path $projectRoot 'CalClock/Release/clock-tests'
New-Item -ItemType Directory -Path $buildRoot -Force | Out-Null
Push-Location $projectRoot
try {
    $buildCommand = "`"$vcvars`" >nul && `"$msbuild`" CalClock.slnx " +
        '/p:Configuration=Release /p:Platform=x86 /m /v:minimal /nologo'
    & $env:ComSpec /d /s /c $buildCommand
    if ($LASTEXITCODE -ne 0) {
        throw 'CalClock build failed.'
    }
    $mainSource = [IO.File]::ReadAllText((Join-Path $projectRoot 'CalClock/CalClock.cpp'))
    $signalSource = [IO.File]::ReadAllText((Join-Path $projectRoot 'CalClock/TimeSignal.cpp'))
    $integrationFunctions = @('WidgetSupportsSound', 'GetApplicationTimeOffset',
        'GetApplicationFileTimeValue',
        'CancelAlarmWakeTimer', 'UpdateAlarmWakeTimer', 'AlarmSystemTimeZoneChanged',
        'AlarmUsesSystemTimeZone',
        'ResetAlarmSchedules',
        'CheckWidgetAlarm', 'CheckWidgetAlarms')
    Write-TestHeader 'AlarmIntegrationProduction.h' (Get-TestFunctions $mainSource $integrationFunctions)
    $integrationMessages = Get-TestRange $mainSource '        case WM_POWERBROADCAST:' `
        '        case WM_GETDPISCALEDSIZE:'
    $integrationMessages += Get-TestRange $mainSource '        case WM_NTP_RESULT:' `
        '        case WM_THEMECHANGED:'
    Write-TestHeader 'AlarmIntegrationMessages.h' $integrationMessages
    $playbackTypes = Get-TestRange $mainSource 'struct TimeSignalSourceGroup {' `
        '/// Pairs a live widget with a planned screen rectangle'
    Write-TestHeader 'AlarmPlaybackTypes.h' $playbackTypes
    $playbackFunctions = @('WidgetSupportsSound', 'GetWidgetUtcTime', 'GetDisplayedTime', 'SystemTimeValue',
        'HasUnmutedTimeSignalSource', 'UpdateCurrentTimeSignalMute', 'RetainCurrentTimeSignalSources',
        'CheckTimeSignals', 'CloseWidgetAudio', 'StopWidgetAlarm', 'StopAllAlarms', 'StartWidgetAlarm')
    Write-TestHeader 'AlarmPlaybackProduction.h' (Get-TestFunctions $mainSource $playbackFunctions)
    $playbackMessages = Get-TestRange $mainSource '        case WM_AUDIO_FINISHED:' `
        '        case WM_SETTINGS_AUDIO_FINISHED:'
    Write-TestHeader 'AlarmPlaybackMessages.h' $playbackMessages
    $signalMath = Get-TestRange $signalSource 'static const ULONGLONG FILE_TIME_TICKS_PER_MILLISECOND' `
        'static std::vector<std::unique_ptr<TimeSignalOutputRoute>> timeSignalOutputs;'
    $signalMath += Get-TestFunctions $signalSource @('IsTimeSignalBoundary', 'CalculateTimeSignalTarget')
    Write-TestHeader 'AlarmSignalMath.h' $signalMath
    $commonOptions = @('/nologo', '/std:c++20', '/EHsc', '/MT', '/O2', '/Gy', '/DUNICODE', '/D_UNICODE')
    $testNames = @('ClockTimeTests', 'AlarmScheduleTests', 'AlarmIntegrationTests', 'AlarmPlaybackTests',
        'AlarmWaveformTests', 'AlarmSettingsTests')
    foreach ($testName in $testNames) {
        $sources = @("tests/$testName.cpp")
        if ($testName -eq 'AlarmScheduleTests') {
            $sources += 'CalClock/AlarmSchedule.cpp', 'CalClock/TimeZoneSupport.cpp',
                'CalClock/TimeSignal.cpp'
        }
        if ($testName -eq 'AlarmIntegrationTests') {
            $sources += 'CalClock/AlarmSchedule.cpp'
        }
        if ($testName -eq 'AlarmPlaybackTests') {
            $sources += 'CalClock/AlarmSchedule.cpp', 'CalClock/TimeZoneSupport.cpp'
        }
        $extraOptions = @()
        $linkOptions = @('/link', '/SUBSYSTEM:CONSOLE', '/DEBUG:NONE', '/OPT:REF', '/OPT:ICF',
            'user32.lib', 'gdi32.lib', 'advapi32.lib', 'ole32.lib', 'uuid.lib')
        if ($testName -eq 'AlarmSettingsTests') {
            $extraOptions += '/DNDEBUG'
            $objects = Get-ChildItem -LiteralPath (Join-Path $projectRoot 'CalClock/Release') -Filter '*.obj'
            $sources += $objects | Where-Object Name -ne 'CalClock.obj' |
                ForEach-Object { '"' + $_.FullName + '"' }
            $sources += 'CalClock/Release/CalClock.res'
            $linkOptions += '/LTCG', 'oleaut32.lib', 'Usp10.lib'
        }
        $options = $commonOptions + $extraOptions + @("/Fo`"$buildRoot/`"", "/Fe`"$buildRoot/$testName.exe`"",
            "/I`"$buildRoot`"") + $sources + $linkOptions
        $responsePath = Join-Path $buildRoot "$testName.rsp"
        Set-Content -LiteralPath $responsePath -Value ($options -join ' ') -Encoding utf8
        & $env:ComSpec /d /s /c "`"$vcvars`" >nul && cl @`"$responsePath`""
        if ($LASTEXITCODE -ne 0) {
            throw "$testName build failed."
        }
        if ($testName -eq 'AlarmSettingsTests') {
            $manifestCommand = "`"$vcvars`" >nul && mt.exe /nologo /manifest CalClock/CalClock.manifest " +
                "/outputresource:`"$buildRoot/$testName.exe;#1`""
            & $env:ComSpec /d /s /c $manifestCommand
            if ($LASTEXITCODE -ne 0) { throw 'Alarm Settings test manifest failed.' }
        }
    }
    foreach ($frequency in '3125000', '3579545', '10000000', '3000000000') {
        & "$buildRoot/ClockTimeTests.exe" $frequency
        if ($LASTEXITCODE -ne 0) {
            throw "ClockTimeTests failed at $frequency Hz."
        }
    }
    foreach ($testName in 'AlarmScheduleTests', 'AlarmIntegrationTests', 'AlarmPlaybackTests',
        'AlarmWaveformTests') {
        & "$buildRoot/$testName.exe"
        if ($LASTEXITCODE -ne 0) { throw "$testName failed." }
    }
    $settingsTestXml = Join-Path $buildRoot 'alarm-settings-isolated.xml'
    & "$buildRoot/AlarmSettingsTests.exe" $settingsTestXml
    if ($LASTEXITCODE -ne 0) { throw 'AlarmSettingsTests failed.' }
} finally {
    Pop-Location
}
