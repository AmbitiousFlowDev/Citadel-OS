param(
    [ValidateSet("Debug", "Release")]
    [string]$Configuration = "Debug",

    [string]$BuildDir = "build",

    [switch]$Clean,
    [switch]$Run,
    [switch]$DebugQemu,

    [string]$ClangPath = "C:\Program Files\LLVM\bin\clang.exe",
    [string]$NasmPath = "C:\Users\AmbitiousFlow\AppData\Local\bin\NASM\nasm.exe"
)

$ErrorActionPreference = "Stop"

function Step($Message)
{
    Write-Host ""
    Write-Host "==> $Message" -ForegroundColor Cyan
}

#
# Locate Clang
#

if (!(Test-Path $ClangPath))
{
    $cmd = Get-Command clang -ErrorAction SilentlyContinue

    if ($cmd)
    {
        $ClangPath = $cmd.Source
    }
    else
    {
        throw "clang.exe not found."
    }
}

#
# Locate NASM
#

if (!(Test-Path $NasmPath))
{
    $cmd = Get-Command nasm -ErrorAction SilentlyContinue

    if ($cmd)
    {
        $NasmPath = $cmd.Source
    }
    else
    {
        throw "nasm.exe not found."
    }
}

Write-Host "Clang : $ClangPath"
Write-Host "NASM  : $NasmPath"

#
# Clean
#

if ($Clean -and (Test-Path $BuildDir))
{
    Step "Cleaning"

    Remove-Item $BuildDir -Recurse -Force
}

#
# Configure
#

Step "Configuring"

& cmake `
    -S . `
    -B "$BuildDir" `
    -G "Ninja" `
    "-DCMAKE_BUILD_TYPE=$Configuration" `
    "-DCMAKE_C_COMPILER=$ClangPath" `
    "-DCMAKE_ASM_NASM_COMPILER=$NasmPath"

if ($LASTEXITCODE -ne 0)
{
    exit $LASTEXITCODE
}

#
# Build
#

Step "Building"

& cmake `
    --build "$BuildDir" `
    --parallel

if ($LASTEXITCODE -ne 0)
{
    exit $LASTEXITCODE
}

#
# Run
#

if ($Run)
{
    Step "Running"

    & cmake `
        --build "$BuildDir" `
        --target run

    exit $LASTEXITCODE
}

#
# Debug
#

if ($DebugQemu)
{
    Step "Debugging"

    & cmake `
        --build "$BuildDir" `
        --target debug

    exit $LASTEXITCODE
}

Write-Host ""
Write-Host "Build completed successfully." -ForegroundColor Green