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

Last modified for version 1.7.2.5

.SYNOPSIS
Prepares the application icon and compressed resource library for the native build.

.DESCRIPTION
Extracts icon group zero from Resources\Resources.dll into CalClock.ico and compresses the complete library
into Resources.dll.bin for embedding in the executable. Creates the output directory when needed.

.PARAMETER OutputDirectory
The intermediate build directory that receives CalClock.ico and Resources.dll.bin.
#>

param([Parameter(Mandatory = $true)][string]$OutputDirectory)

$ErrorActionPreference = 'Stop'
[IO.Directory]::CreateDirectory($OutputDirectory) | Out-Null
$compilerLibraries = $env:LIB
try {
    $env:LIB = ''
    Add-Type -Path (Join-Path $PSScriptRoot 'ResourceIcons.cs')
    Add-Type -Path (Join-Path $PSScriptRoot 'ResourcePacker.cs') `
        -ReferencedAssemblies 'System.dll', 'System.IO.Compression.dll'
} finally {
    $env:LIB = $compilerLibraries
}
$library = Join-Path $PSScriptRoot 'Resources\Resources.dll'
$icon = Join-Path $OutputDirectory 'CalClock.ico'
[ResourceIcons]::Extract($library, 0, $icon)
[ResourcePacker]::Pack($library, (Join-Path $OutputDirectory 'Resources.dll.bin'), $true)
