<#
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

Last modified for version 1.6.0.0

.SYNOPSIS
Builds CalClock and checks panel content positions during native border changes.

.DESCRIPTION
Requires Windows Graphics Capture with secondary-window capture on the development computer.
Captures an opaque test checkerboard and both real native top-level panel windows in one continuous scene.
Keeps the native panel window classes, styles, parents, geometry, and real two-window position batch unchanged.
Checks native surfaces and client sizes, then rejects any scene other than the complete previous or complete new panel.
Allows at most two RGB levels of native text rasterization rounding inside the calendar only; positions and alpha remain exact.
Checks the client against its native surface composited at the configured opacity over the known checkerboard.
Queues late native calendar and clock repaints and delays their erase handlers to expose intermediate drawing.
Tests native border transitions with Segoe UI and Cambria Math, themes enabled and disabled,
100% and 65% opacity, and with and without additional clocks. Inconclusive capture is a failure.
Uses only test-owned secondary windows; aborts before copying a frame if a foreign secondary window could enter it.
On-screen test windows stay underneath existing opaque windows. The worker aborts if coverage is lost.
Does not activate, move, resize, hide, or capture another application's windows or switch the input desktop.
Generated files are placed in CalClock/Release/panel-rendering-tests.

.PARAMETER VisualStudioPath
Optional Visual Studio installation directory containing the C++ build tools.

.PARAMETER Cases
Optional case numbers from 0 through 15. By default runs every case.

.PARAMETER VerifyGapDetection
First deliberately hides the old widget before presenting its replacement and requires that control to be rejected.

#>
param([string]$VisualStudioPath, [ValidateRange(0, 15)][int[]]$Cases = 0..15, [switch]$VerifyGapDetection)

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
$buildRoot = Join-Path $projectRoot 'CalClock/Release/panel-rendering-tests'
New-Item -ItemType Directory -Path $buildRoot -Force | Out-Null
$previousVariant = $env:CALCLOCK_FRAME_TEST_VARIANT
$previousGap = $env:CALCLOCK_FRAME_TEST_GAP
Push-Location $projectRoot
try {
    & $env:ComSpec /d /s /c "`"$vcvars`" >nul && `"$msbuild`" CalClock.slnx /p:Configuration=Release /p:Platform=x86 /m /v:minimal /nologo"
    if ($LASTEXITCODE -ne 0) {
        throw 'CalClock build failed.'
    }
    $options = @('/nologo', '/std:c++20', '/EHsc', '/MT', '/O2', '/Gy', '/DUNICODE', '/D_UNICODE',
        "/Fo`"$buildRoot/PanelRenderingTests.obj`"", "/Fe`"$buildRoot/PanelRenderingTests.exe`"", 'tests/PanelRenderingTests.cpp')
    $options += Get-ChildItem CalClock/Release -Filter '*.obj' | Where-Object BaseName -ne 'CalClock' |
        ForEach-Object { '"' + $_.FullName + '"' }
    $options += @('CalClock/Release/CalClock.res', '/link', '/SUBSYSTEM:CONSOLE', '/DEBUG:NONE', '/OPT:REF', '/OPT:ICF',
        '/LTCG', '/MANIFEST:EMBED', '/MANIFESTINPUT:CalClock/CalClock.manifest.xml',
        'user32.lib', 'gdi32.lib', 'advapi32.lib', 'ole32.lib', 'uuid.lib', 'windowsapp.lib', 'd3d11.lib', 'dxgi.lib')
    $response = Join-Path $buildRoot 'PanelRenderingTests.rsp'
    Set-Content -LiteralPath $response -Value ($options -join ' ') -Encoding utf8
    & $env:ComSpec /d /s /c "`"$vcvars`" >nul && cl @`"$response`""
    if ($LASTEXITCODE -ne 0) {
        throw 'PanelRenderingTests build failed.'
    }
    if ($VerifyGapDetection) {
        $env:CALCLOCK_FRAME_TEST_VARIANT = '0'
        $env:CALCLOCK_FRAME_TEST_GAP = '1'
        $negativeOutput = & "$buildRoot/PanelRenderingTests.exe" 2>&1
        $negativeExit = $LASTEXITCODE
        $negativeOutput | Write-Output
        if ($negativeExit -ne 1 -or -not ($negativeOutput -match 'SCENE_GAP_DETECTED:')) {
            throw 'The scene capture did not conclusively reject the deliberate whole-window disappearance.'
        }
    }
    $env:CALCLOCK_FRAME_TEST_GAP = '0'
    foreach ($case in $Cases) {
        $env:CALCLOCK_FRAME_TEST_VARIANT = [string]$case
        & "$buildRoot/PanelRenderingTests.exe"
        if ($LASTEXITCODE -ne 0) {
            throw "Panel compositor test failed or was inconclusive in case $case."
        }
    }
} finally {
    $env:CALCLOCK_FRAME_TEST_VARIANT = $previousVariant
    $env:CALCLOCK_FRAME_TEST_GAP = $previousGap
    Pop-Location
}
