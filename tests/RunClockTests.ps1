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

Last modified for version 1.6.1.5

.SYNOPSIS
Builds CalClock and runs the continuous-clock regression tests.

.DESCRIPTION
Builds Release | x86, compiles the continuous-clock test executable, and runs it at four counter frequencies.
The tests simulate clock and counter values without changing the computer's clock. Generated files are placed in
CalClock/Release/clock-tests. A build or test failure stops the script with an error.

.PARAMETER VisualStudioPath
Optional Visual Studio installation directory containing VC/Auxiliary/Build/vcvars32.bat and MSBuild/Current/Bin.
When omitted, vswhere selects the latest installed Visual Studio with the C++ build tools, including prereleases.

.EXAMPLE
.\tests\RunClockTests.ps1

Builds and runs all clock regression tests using the automatically selected Visual Studio installation.
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
$buildRoot = Join-Path $projectRoot 'CalClock/Release/clock-tests'
New-Item -ItemType Directory -Path $buildRoot -Force | Out-Null
Push-Location $projectRoot
try {
    & $env:ComSpec /d /s /c "`"$vcvars`" >nul && `"$msbuild`" CalClock.slnx /p:Configuration=Release /p:Platform=x86 /m /v:minimal /nologo"
    if ($LASTEXITCODE -ne 0) {
        throw 'CalClock build failed.'
    }
    $commonOptions = @('/nologo', '/std:c++20', '/EHsc', '/MT', '/O2', '/Gy', '/DUNICODE', '/D_UNICODE')
    $testName = 'ClockTimeTests'
    $options = $commonOptions + @("/Fo`"$buildRoot/$testName.obj`"", "/Fe`"$buildRoot/$testName.exe`"",
        "tests/$testName.cpp", '/link', '/SUBSYSTEM:CONSOLE', '/DEBUG:NONE', '/OPT:REF', '/OPT:ICF',
        'user32.lib', 'gdi32.lib', 'advapi32.lib', 'ole32.lib', 'uuid.lib')
    $responsePath = Join-Path $buildRoot "$testName.rsp"
    Set-Content -LiteralPath $responsePath -Value ($options -join ' ') -Encoding utf8
    & $env:ComSpec /d /s /c "`"$vcvars`" >nul && cl @`"$responsePath`""
    if ($LASTEXITCODE -ne 0) {
        throw "$testName build failed."
    }
    foreach ($frequency in '3125000', '3579545', '10000000', '3000000000') {
        & "$buildRoot/ClockTimeTests.exe" $frequency
        if ($LASTEXITCODE -ne 0) {
            throw "ClockTimeTests failed at $frequency Hz."
        }
    }
} finally {
    Pop-Location
}
