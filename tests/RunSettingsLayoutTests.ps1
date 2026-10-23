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

Last modified for version 1.6.1.1

.SYNOPSIS
Builds CalClock and verifies the settings height ceiling and native text rendering, including Cambria Math.

.DESCRIPTION
Runs opaque native test windows on a separate hidden desktop without switching the user's input desktop.
Runs native combo, edit, label, button, and checkbox checks with system-sized fonts, normal and bold weights,
italic styles, and themed and classic controls. Checks actual rendered glyph bounds, dropdown opening,
scrolling, native text editing, visibility, and font changes. Compares complete field backgrounds with native Windows
controls and verifies localized initial clock names and deliberately empty names through settings and XML round trips.
Compares actual edit-border pixels with unmodified native Windows edits during hover, focus, blur, disable, and
read-only transitions, and verifies that image rendering includes the same border as the real window surface.
Checks tab headers and all six complete settings pages for every widget type after font and theme changes.
Exercises every directed widget-type transition, verifies incoming control order and protected foreground pixels,
and checks visible native text against actual form captures made before WM_PRINT or forced repainting.
Observes intermediate Appearance frames through the real application window procedure on an ordinary settings window;
requires every captured frame to retain the old complete layout or show the completed new layout.
Verifies visible labels, shared value-label baselines, complete descriptive text, and page/header separation.
Checks compact widget, monitor, and log rows, 32-item scrolling, multiple selection, and retained log records.
Checks monitor checkbox hit testing, stable device identities during sorting, localized columns and initial width fitting;
saves whole-form images for visual review. Captures both displayed reports before WM_PRINT or forced redraws,
then compares their headers, rows and scrollbars with native rendering. Smaller targeted fields remain smaller;
the maximum is 28 pixels.
Exercises native unsaved-settings questions, save/discard/cancel, application exit, validation failures, and XML defaults.
Application saves are captured in memory. The tests do not read or write user settings.
Generated files are placed in CalClock/Release/settings-layout-tests.

.PARAMETER VisualStudioPath
Optional Visual Studio installation directory containing the C++ build tools.

.EXAMPLE
.\tests\RunSettingsLayoutTests.ps1
#>
param([string]$VisualStudioPath)

$ErrorActionPreference = 'Stop'
$projectRoot = Split-Path -Parent $PSScriptRoot
if (-not $VisualStudioPath) {
    $vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio/Installer/vswhere.exe'
    $VisualStudioPath = & $vswhere -latest -prerelease -products '*' -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
}
if (-not $VisualStudioPath) {
    throw 'A Visual Studio installation with C++ build tools is required.'
}
$vcvars = Join-Path $VisualStudioPath 'VC/Auxiliary/Build/vcvars32.bat'
$msbuild = Join-Path $VisualStudioPath 'MSBuild/Current/Bin/MSBuild.exe'
$buildRoot = Join-Path $projectRoot 'CalClock/Release/settings-layout-tests'
New-Item -ItemType Directory -Path $buildRoot -Force | Out-Null
Push-Location $projectRoot
try {
    & $env:ComSpec /d /s /c "`"$vcvars`" >nul && `"$msbuild`" CalClock.slnx /p:Configuration=Release /p:Platform=x86 `"/p:OutDir=$buildRoot/app/`" /m /v:minimal /nologo"
    if ($LASTEXITCODE -ne 0) {
        throw 'CalClock build failed.'
    }
    $options = @('/nologo', '/std:c++20', '/EHsc', '/MT', '/O2', '/Gy', '/DUNICODE', '/D_UNICODE',
        "/Fo`"$buildRoot/SettingsLayoutTests.obj`"", "/Fe`"$buildRoot/SettingsLayoutTests.exe`"", 'tests/SettingsLayoutTests.cpp')
    $options += Get-ChildItem CalClock/Release -Filter '*.obj' | Where-Object BaseName -ne 'CalClock' |
        ForEach-Object { '"' + $_.FullName + '"' }
    $options += @('CalClock/Release/CalClock.res', '/link', '/SUBSYSTEM:CONSOLE', '/DEBUG:NONE', '/OPT:REF', '/OPT:ICF',
        '/LTCG', '/MANIFEST:EMBED', '/MANIFESTINPUT:CalClock/CalClock.manifest.xml',
        'user32.lib', 'gdi32.lib', 'advapi32.lib', 'ole32.lib', 'uuid.lib')
    $response = Join-Path $buildRoot 'SettingsLayoutTests.rsp'
    Set-Content -LiteralPath $response -Value ($options -join ' ') -Encoding utf8
    & $env:ComSpec /d /s /c "`"$vcvars`" >nul && cl @`"$response`""
    if ($LASTEXITCODE -ne 0) {
        throw 'SettingsLayoutTests build failed.'
    }
    & "$buildRoot/SettingsLayoutTests.exe"
    if ($LASTEXITCODE -ne 0) {
        throw 'SettingsLayoutTests failed.'
    }
} finally {
    Pop-Location
}
