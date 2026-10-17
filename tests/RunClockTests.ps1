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
Builds CalClock and runs the clock and NTP regression tests.

.DESCRIPTION
Builds Release | x86, compiles both test executables, and runs the continuous-clock tests at four counter
frequencies before running the NTP and time-signal tests. The tests simulate time and network activity without
changing the computer's clock or contacting external servers. Generated files are placed in
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
    foreach ($testName in 'ClockTimeTests', 'TimeSourceTests') {
        $options = $commonOptions + @("/Fo`"$buildRoot/$testName.obj`"", "/Fe`"$buildRoot/$testName.exe`"", "tests/$testName.cpp")
        if ($testName -eq 'TimeSourceTests') {
            $options += Get-ChildItem CalClock/Release -Filter '*.obj' |
                Where-Object { $_.BaseName -notin 'CalClock', 'ClockTime', 'NtpClient', 'TimeSignal' } |
                ForEach-Object { '"' + $_.FullName + '"' }
        }
        $options += @('/link', '/SUBSYSTEM:CONSOLE', '/DEBUG:NONE', '/OPT:REF', '/OPT:ICF',
            'user32.lib', 'gdi32.lib', 'advapi32.lib', 'ole32.lib', 'uuid.lib')
        if ($testName -eq 'TimeSourceTests') {
            $options += '/LTCG'
        }
        $responsePath = Join-Path $buildRoot "$testName.rsp"
        Set-Content -LiteralPath $responsePath -Value ($options -join ' ') -Encoding utf8
        & $env:ComSpec /d /s /c "`"$vcvars`" >nul && cl @`"$responsePath`""
        if ($LASTEXITCODE -ne 0) {
            throw "$testName build failed."
        }
    }
    foreach ($frequency in '3125000', '3579545', '10000000', '3000000000') {
        & "$buildRoot/ClockTimeTests.exe" $frequency
        if ($LASTEXITCODE -ne 0) {
            throw "ClockTimeTests failed at $frequency Hz."
        }
    }
    & "$buildRoot/TimeSourceTests.exe"
    if ($LASTEXITCODE -ne 0) {
        throw 'TimeSourceTests failed.'
    }
} finally {
    Pop-Location
}
