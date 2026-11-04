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
Builds and runs the real Time Calculator form on a hidden, nonactivating private desktop.

.DESCRIPTION
Uses production Release objects and resources, the real application layout helpers, and the existing
Alarm Settings test isolation. Calculator and window persistence sources are compiled with inert activation
functions. All settings writes and confirmation boxes are intercepted. No keyboard or mouse input is sent.
Bitmap captures are written under CalClock/Release/time-calculator-form-tests. The desktop is never switched.

.PARAMETER VisualStudioPath
Optional Visual Studio installation path, otherwise discovered with vswhere.
#>
param([string]$VisualStudioPath)

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
$buildRoot = Join-Path $projectRoot 'CalClock/Release/time-calculator-form-tests'
New-Item -ItemType Directory -Path $buildRoot -Force | Out-Null
$objects = Get-ChildItem -LiteralPath (Join-Path $projectRoot 'CalClock/Release') -Filter '*.obj' |
    Where-Object Name -notin @('CalClock.obj', 'TimeCalculatorForm.obj', 'PersistWindowState.obj')
$options = @('/nologo', '/std:c++20', '/EHsc', '/MT', '/O2', '/Gy', '/DNDEBUG', '/DUNICODE', '/D_UNICODE',
    "/Fo`"$buildRoot/TimeCalculatorFormTests.obj`"", "/Fe`"$buildRoot/TimeCalculatorFormTests.exe`"",
    'tests/TimeCalculatorFormTests.cpp')
$options += $objects | ForEach-Object { '"' + $_.FullName + '"' }
$options += @("`"$buildRoot/CalClock.res`"", '/link', '/SUBSYSTEM:CONSOLE', '/DEBUG:NONE', '/OPT:REF',
    '/OPT:ICF', '/LTCG', 'user32.lib', 'gdi32.lib', 'advapi32.lib', 'ole32.lib', 'uuid.lib',
    'oleaut32.lib', 'Usp10.lib')
$responsePath = Join-Path $buildRoot 'TimeCalculatorFormTests.rsp'
Set-Content -LiteralPath $responsePath -Value ($options -join ' ') -Encoding utf8
Push-Location $projectRoot
try {
    Push-Location (Join-Path $projectRoot 'CalClock')
    try {
        & $env:ComSpec /d /s /c "`"$vcvars`" >nul && rc /nologo /fo `"$buildRoot/CalClock.res`" CalClock.rc"
        if ($LASTEXITCODE -ne 0) {
            throw 'Time Calculator form test resources failed.'
        }
    } finally {
        Pop-Location
    }
    & $env:ComSpec /d /s /c "`"$vcvars`" >nul && cl @`"$responsePath`""
    if ($LASTEXITCODE -ne 0) {
        throw 'Time Calculator form test build failed.'
    }
    $manifest = "`"$vcvars`" >nul && mt.exe /nologo /manifest CalClock/CalClock.manifest " +
        "/outputresource:`"$buildRoot/TimeCalculatorFormTests.exe;#1`""
    & $env:ComSpec /d /s /c $manifest
    if ($LASTEXITCODE -ne 0) {
        throw 'Time Calculator form test manifest failed.'
    }
    & "$buildRoot/TimeCalculatorFormTests.exe" $buildRoot
    if ($LASTEXITCODE -ne 0) {
        throw 'Time Calculator form tests failed.'
    }
} finally {
    Pop-Location
}
