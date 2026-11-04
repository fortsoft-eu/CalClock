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
Builds and runs isolated Time Calculator registry and XML storage tests in Release configuration.

.DESCRIPTION
Compiles the production storage implementation and calculator core with native C++ tests. The tests use
memory streams and a uniquely named temporary key under HKCU\Software\CalClockCalculatorStorageTests-*.
That key is removed after success or failure. Actual CalClock settings are neither read nor written.
No windows are created, and desktop focus, keyboard settings, and system time remain unchanged.
The process needs permission to create its temporary per-user registry key.
Build products remain under CalClock/Release/time-calculator-storage-tests.

.PARAMETER VisualStudioPath
Optional Visual Studio installation path; otherwise the installed C++ toolchain is discovered by vswhere.
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
$buildRoot = Join-Path $projectRoot 'CalClock/Release/time-calculator-storage-tests'
New-Item -ItemType Directory -Path $buildRoot -Force | Out-Null
$commonOptions = @('/nologo', '/std:c++20', '/EHsc', '/MT', '/O2', '/DNDEBUG', '/W4', '/WX',
    '/DUNICODE', '/D_UNICODE', '/ICalClock')
$coreOptions = $commonOptions + @('/c', "/Fo`"$buildRoot/TimeCalculatorCore.obj`"",
    'CalClock/TimeCalculator.cpp')
$testOptions = $commonOptions + @('/Gy', "/Fo`"$buildRoot/TimeCalculatorStorageTests.obj`"",
    "/Fe`"$buildRoot/TimeCalculatorStorageTests.exe`"", 'tests/TimeCalculatorStorageTests.cpp',
    "`"$buildRoot/TimeCalculatorCore.obj`"", "`"$buildRoot/TimeZoneSupport.obj`"",
    '/link', '/SUBSYSTEM:CONSOLE', '/DEBUG:NONE', '/OPT:REF',
    'user32.lib', 'advapi32.lib', 'ole32.lib')
$coreResponse = Join-Path $buildRoot 'TimeCalculatorCore.rsp'
$zoneOptions = $commonOptions + @('/c', "/Fo`"$buildRoot/TimeZoneSupport.obj`"",
    'CalClock/TimeZoneSupport.cpp')
$zoneResponse = Join-Path $buildRoot 'TimeZoneSupport.rsp'
Set-Content -LiteralPath $zoneResponse -Value ($zoneOptions -join ' ') -Encoding utf8
$testResponse = Join-Path $buildRoot 'TimeCalculatorStorageTests.rsp'
Set-Content -LiteralPath $coreResponse -Value ($coreOptions -join ' ') -Encoding utf8
Set-Content -LiteralPath $testResponse -Value ($testOptions -join ' ') -Encoding utf8
Push-Location $projectRoot
try {
    & $env:ComSpec /d /s /c "`"$vcvars`" >nul && cl @`"$coreResponse`""
    if ($LASTEXITCODE -ne 0) {
        throw 'Time Calculator core build failed.'
    }
    & $env:ComSpec /d /s /c "`"$vcvars`" >nul && cl @`"$zoneResponse`""
    if ($LASTEXITCODE -ne 0) {
        throw 'Time-zone support build failed.'
    }
    & $env:ComSpec /d /s /c "`"$vcvars`" >nul && cl @`"$testResponse`""
    if ($LASTEXITCODE -ne 0) {
        throw 'Time Calculator storage test build failed.'
    }
    & "$buildRoot/TimeCalculatorStorageTests.exe"
    if ($LASTEXITCODE -ne 0) {
        throw 'Time Calculator storage tests failed.'
    }
} finally {
    Pop-Location
}
