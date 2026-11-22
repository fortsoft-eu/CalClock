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

Last modified for version 1.7.3.0

.SYNOPSIS
Builds and runs native search, resource-cache, Options, and print-snapshot regression tests.

.DESCRIPTION
Runs actual ComboBoxEx controls on an unshown private desktop. Activation and input APIs are replaced
with inert test substitutes. Registry access is isolated. No print job is submitted to a printer.
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
$vcvars = Join-Path $VisualStudioPath 'Common7/Tools/VsDevCmd.bat'
$toolEnvironment = "`"$vcvars`" -arch=x86 -host_arch=x64 >nul"
$msbuild = Join-Path $VisualStudioPath 'MSBuild/Current/Bin/MSBuild.exe'
$buildRoot = Join-Path $projectRoot 'CalClock/Release/find-form-tests'
New-Item -ItemType Directory -Path $buildRoot -Force | Out-Null
Push-Location $projectRoot
try {
    $build = "$toolEnvironment && `"$msbuild`" CalClock.slnx " +
        '/p:Configuration=Release /p:Platform=x86 /p:PreferredToolArchitecture=x64 /m /v:minimal /nologo'
    & $env:ComSpec /d /s /c $build
    if ($LASTEXITCODE -ne 0) {
        throw 'CalClock Release build failed.'
    }
    $objects = Get-ChildItem -LiteralPath (Join-Path $projectRoot 'CalClock/Release') -Filter '*.obj' |
        Where-Object Name -notin @('CalClock.obj', 'FindForm.obj', 'PersistWindowState.obj',
            'AboutForm.obj', 'HelpForm.obj')
    $options = @('/nologo', '/std:c++20', '/EHsc', '/MT', '/O2', '/Gy', '/DNDEBUG', '/DUNICODE',
        '/D_UNICODE', "/Fo`"$buildRoot/FindForm.obj`"", "/Fe`"$buildRoot/FindForm.exe`"",
        'tests/FindForm.cpp')
    $options += $objects | ForEach-Object { '"' + $_.FullName + '"' }
    $options += @('CalClock/Release/CalClock.res', '/link', '/SUBSYSTEM:CONSOLE', '/DEBUG:NONE',
        '/OPT:REF', '/OPT:ICF', '/LTCG', 'user32.lib', 'gdi32.lib', 'advapi32.lib', 'ole32.lib',
        'uuid.lib', 'oleaut32.lib', 'Usp10.lib')
    $response = Join-Path $buildRoot 'FindForm.rsp'
    Set-Content -LiteralPath $response -Value ($options -join ' ') -Encoding utf8
    & $env:ComSpec /d /s /c "$toolEnvironment && cl @`"$response`""
    if ($LASTEXITCODE -ne 0) {
        throw 'Find form test build failed.'
    }
    $manifest = "$toolEnvironment && mt.exe /nologo /manifest CalClock/CalClock.manifest " +
        "/outputresource:`"$buildRoot/FindForm.exe;#1`""
    & $env:ComSpec /d /s /c $manifest
    if ($LASTEXITCODE -ne 0) {
        throw 'Find form test manifest failed.'
    }
    & "$buildRoot/FindForm.exe" $buildRoot
    if ($LASTEXITCODE -ne 0) {
        throw 'Find form tests failed.'
    }
} finally {
    Pop-Location
}
