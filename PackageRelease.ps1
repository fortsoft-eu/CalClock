[CmdletBinding()]
param (
    [string]$SignerName,
    [string]$CertificateThumbprint,
    [string]$SignToolPath,
    [string]$TimestampServer
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

$root = Split-Path -Parent $PSCommandPath
$solutionName = "CalClock"
$platform = "win32"
$archive = Join-Path $root ($solutionName + ".zip")

# The release executable and license are placed directly in the ZIP root.
$projects = @(
    [PSCustomObject]@{
        Name    = "CalClock"
        Files   = @(
            (Join-Path $root "Release\CalClock.exe")
        )
        License = Join-Path $root "license.txt"
    }
)

# Remove archives from previous runs before packaging. A later failure must not leave a stale ZIP behind.
$staleArchives = @($archive)
$versionedArchivePattern = "^{0}-\d+\.\d+\.\d+\.\d+-{1}\.zip`$" -f [regex]::Escape($solutionName), [regex]::Escape($platform)
$versionedArchives = Get-ChildItem -LiteralPath $root -Filter "$solutionName-*-$platform.zip" -File
foreach ($versionedArchive in $versionedArchives) {
    if ($versionedArchive.Name -match $versionedArchivePattern) {
        $staleArchives += $versionedArchive.FullName
    }
}
foreach ($staleArchive in ($staleArchives | Select-Object -Unique)) {
    if (Test-Path -LiteralPath $staleArchive) {
        Remove-Item -LiteralPath $staleArchive -Force
        Write-Host "Removed previous package: $staleArchive"
    }
}

# Returns the four-part file version of the Release executable used to name the solution package.
function Get-PackageVersion {
    param (
        [Parameter(Mandatory)][string]$Path
    )

    if (-not (Test-Path -LiteralPath $Path -PathType Leaf)) {
        throw "Missing Release executable: $Path"
    }

    $versionInfo = [System.Diagnostics.FileVersionInfo]::GetVersionInfo($Path)
    if ([string]::IsNullOrEmpty($versionInfo.FileVersion)) {
        throw "The Release executable has no file version: $Path"
    }

    return "{0}.{1}.{2}.{3}" -f $versionInfo.FileMajorPart, $versionInfo.FileMinorPart, $versionInfo.FileBuildPart, $versionInfo.FilePrivatePart
}

# Returns the newest valid current-user code-signing certificate with a private key that matches the supplied name
# or thumbprint; returns null when no signer was requested or no matching certificate exists.
function Find-SignerCertificate {
    param (
        [string]$Name,
        [string]$Thumbprint
    )

    if (-not $Name -and -not $Thumbprint) {
        return $null
    }

    $now = Get-Date
    if ($Thumbprint) {
        $normalizedThumbprint = $Thumbprint.Replace(" ", "")
    } else {
        $normalizedThumbprint = $null
    }
    $certificates = @(Get-ChildItem Cert:\CurrentUser\My -CodeSigningCert |
        Where-Object {
            $_.HasPrivateKey -and
            $_.NotBefore -le $now -and
            $_.NotAfter -gt $now -and
            (-not $normalizedThumbprint -or $_.Thumbprint -ieq $normalizedThumbprint) -and
            (-not $Name -or $_.GetNameInfo([Security.Cryptography.X509Certificates.X509NameType]::SimpleName, $false) -ieq $Name)
        } |
        Sort-Object NotAfter -Descending)

    return $certificates | Select-Object -First 1
}

# Resolves the requested signing tool or searches PATH and installed Windows SDK versions; returns null if unavailable.
function Find-SignTool {
    param (
        [string]$RequestedPath
    )

    if ($RequestedPath) {
        if (Test-Path -LiteralPath $RequestedPath -PathType Leaf) {
            return [IO.Path]::GetFullPath($RequestedPath)
        }
        return $null
    }

    $command = Get-Command signtool.exe -ErrorAction SilentlyContinue | Select-Object -First 1
    if ($command) {
        return $command.Source
    }

    $kitsRoot = Join-Path ${env:ProgramFiles(x86)} "Windows Kits\10\bin"
    if (-not (Test-Path -LiteralPath $kitsRoot -PathType Container)) {
        return $null
    }

    $versionDirectories = Get-ChildItem -LiteralPath $kitsRoot -Directory |
        Where-Object {
            $_.Name -match "^\d+\.\d+\.\d+\.\d+`$"
        } |
        Sort-Object {
            [version]$_.Name
        } -Descending
    foreach ($directory in $versionDirectories) {
        foreach ($architecture in @("x64", "x86")) {
            $candidate = Join-Path $directory.FullName "$architecture\signtool.exe"
            if (Test-Path -LiteralPath $candidate -PathType Leaf) {
                return $candidate
            }
        }
    }

    foreach ($architecture in @("x64", "x86")) {
        $candidate = Join-Path $kitsRoot "$architecture\signtool.exe"
        if (Test-Path -LiteralPath $candidate -PathType Leaf) {
            return $candidate
        }
    }

    return $null
}

# Verifies Authenticode trust using SignTool when available, otherwise using PowerShell's signature status.
function Test-BinarySignature {
    param (
        [Parameter(Mandatory)][string]$Path,
        [string]$ToolPath
    )

    if ($ToolPath) {
        & $ToolPath verify /pa /q $Path *> $null
        return $LASTEXITCODE -eq 0
    }

    $signature = Get-AuthenticodeSignature -LiteralPath $Path
    return $null -ne $signature.SignerCertificate -and $signature.Status -eq "Valid"
}

# Reports whether the binary contains a signer certificate, independently of whether its signature is trusted.
function Test-BinaryHasSignature {
    param (
        [Parameter(Mandatory)][string]$Path
    )

    $signature = Get-AuthenticodeSignature -LiteralPath $Path
    return $null -ne $signature.SignerCertificate
}

# Signs a staged copy with SHA-256, retries without timestamping if that request fails, and verifies the resulting signature.
# Throws on signing or verification failure so an invalid package cannot be reported as successfully signed.
function Sign-Binary {
    param (
        [Parameter(Mandatory)][string]$Path,
        [Parameter(Mandatory)]$Certificate,
        [Parameter(Mandatory)][string]$ToolPath,
        [string]$RequestedSignerName,
        [string]$TimestampUrl
    )

    if ($RequestedSignerName) {
        $certificateSelector = @("/n", $RequestedSignerName)
    } else {
        $certificateSelector = @("/sha1", $Certificate.Thumbprint)
    }

    Write-Host "Signing $([IO.Path]::GetFileName($Path))"
    $signedWithTimestamp = $false
    if ($TimestampUrl) {
        & $ToolPath sign @certificateSelector /fd SHA256 /tr $TimestampUrl /td SHA256 /v $Path
        $signedWithTimestamp = $LASTEXITCODE -eq 0
        if (-not $signedWithTimestamp) {
            Write-Warning "Signing with a timestamp failed; retrying without a timestamp."
        }
    }

    if (-not $signedWithTimestamp) {
        & $ToolPath sign @certificateSelector /fd SHA256 /v $Path
        if ($LASTEXITCODE -ne 0) {
            throw "Signing failed for '$Path'."
        }
    }

    if (-not (Test-BinarySignature -Path $Path -ToolPath $ToolPath)) {
        throw "Authenticode verification failed after signing '$Path'."
    }
}

# Performs verbose SignTool verification of the staged binary, reporting success or throwing on failure.
function Confirm-BinarySignature {
    param (
        [Parameter(Mandatory)][string]$Path,
        [Parameter(Mandatory)][string]$ToolPath
    )

    & $ToolPath verify /pa /v $Path
    if ($LASTEXITCODE -ne 0) {
        throw "Authenticode verification failed for '$Path'."
    }
    Write-Host "Signature verified successfully: $Path"
}

# Searches PATH and standard installation directories for 7-Zip; returns null to select ZIP creation through .NET.
function Find-SevenZip {
    $command = Get-Command 7z.exe -ErrorAction SilentlyContinue | Select-Object -First 1
    if ($command) {
        return $command.Source
    }

    foreach ($candidate in @((Join-Path $env:ProgramFiles "7-Zip\7z.exe"), (Join-Path ${env:ProgramFiles(x86)} "7-Zip\7z.exe"))) {
        if (Test-Path -LiteralPath $candidate -PathType Leaf) {
            return $candidate
        }
    }
    return $null
}

$version = Get-PackageVersion -Path $projects[0].Files[0]
$archiveName = "{0}-{1}-{2}.zip" -f $solutionName, $version, $platform
$archive = Join-Path $root $archiveName

$certificate = Find-SignerCertificate -Name $SignerName -Thumbprint $CertificateThumbprint
$resolvedSignTool = Find-SignTool -RequestedPath $SignToolPath
if ($SignerName -or $CertificateThumbprint) {
    if (-not $certificate) {
        Write-Warning "The requested valid code-signing certificate with a private key was not found. Unsigned binaries will remain unsigned."
    } elseif (-not $resolvedSignTool) {
        Write-Warning "signtool.exe was not found. Unsigned binaries will remain unsigned."
        $certificate = $null
    }
} else {
    Write-Host "No signer was specified. Existing valid signatures will be preserved; unsigned binaries will remain unsigned."
}

$staging = Join-Path ([IO.Path]::GetTempPath()) ($solutionName + "-package-" + [guid]::NewGuid().ToString("N"))
$unsignedBinaries = [Collections.Generic.List[string]]::new()

try {
    New-Item -ItemType Directory -Path $staging | Out-Null

    foreach ($project in $projects) {
        if (-not (Test-Path -LiteralPath $project.License -PathType Leaf)) {
            throw "Missing license for '$($project.Name)': $($project.License)"
        }

        $destination = $staging

        foreach ($file in $project.Files) {
            if (-not (Test-Path -LiteralPath $file -PathType Leaf)) {
                throw "Missing Release binary for '$($project.Name)': $file"
            }

            $stagedFile = Join-Path $destination ([IO.Path]::GetFileName($file))
            Copy-Item -LiteralPath $file -Destination $stagedFile
            $hasExistingSignature = Test-BinaryHasSignature -Path $stagedFile
            $hasValidSignature = Test-BinarySignature -Path $stagedFile -ToolPath $resolvedSignTool
            if ($hasExistingSignature) {
                Write-Host "Existing signature detected; it will not be replaced: $([IO.Path]::GetFileName($file))"
                if (-not $hasValidSignature) {
                    throw "The existing Authenticode signature could not be verified and will not be replaced: '$stagedFile'."
                }
            } elseif ($certificate -and $resolvedSignTool) {
                Sign-Binary -Path $stagedFile -Certificate $certificate -ToolPath $resolvedSignTool -RequestedSignerName $SignerName -TimestampUrl $TimestampServer
                $hasValidSignature = $true
            } else {
                $unsignedBinaries.Add([IO.Path]::GetFileName($file)) | Out-Null
            }

            if ($hasValidSignature) {
                if (-not $resolvedSignTool) {
                    throw "signtool.exe is required for verbose verification of '$stagedFile'."
                }
                Confirm-BinarySignature -Path $stagedFile -ToolPath $resolvedSignTool
            }
        }

        Copy-Item -LiteralPath $project.License -Destination (Join-Path $destination "license.txt")
    }

    $sevenZip = Find-SevenZip
    if ($sevenZip) {
        Push-Location $staging
        try {
            & $sevenZip a -tzip -mx=9 -mmt=on -y $archive "*"
            if ($LASTEXITCODE -ne 0) {
                throw "7-Zip failed to create '$archive'."
            }
        } finally {
            Pop-Location
        }
    } else {
        Add-Type -AssemblyName System.IO.Compression.FileSystem
        [IO.Compression.ZipFile]::CreateFromDirectory($staging, $archive, [IO.Compression.CompressionLevel]::Optimal, $false)
    }

    Write-Host "Created solution package: $archive"
    if ($unsignedBinaries.Count -eq 0) {
        Write-Host "The package contains only verified Authenticode-signed binaries."
    } else {
        Write-Warning ("The package contains unsigned binaries: " + ($unsignedBinaries -join ", "))
    }
} finally {
    if (Test-Path -LiteralPath $staging) {
        $resolvedStaging = [IO.Path]::GetFullPath((Resolve-Path -LiteralPath $staging).ProviderPath)
        $temporaryDirectory = [IO.Path]::GetFullPath([IO.Path]::GetTempPath()).TrimEnd([IO.Path]::DirectorySeparatorChar)
        if ([IO.Path]::GetDirectoryName($resolvedStaging) -ine $temporaryDirectory) {
            throw "The staging directory is outside the temporary directory: $resolvedStaging"
        }
        Remove-Item -LiteralPath $resolvedStaging -Recurse -Force
    }
}
