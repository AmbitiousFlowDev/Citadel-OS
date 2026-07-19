param(
    [ValidateSet("Debug", "Release")]
    [string]$Configuration = "Debug",

    [switch]$Run,
    [switch]$DebugQemu,

    [string]$BuildDir = "build"
)

$ErrorActionPreference = "Stop"

Write-Host "==> Configuring project..." -ForegroundColor Cyan

cmake `
    -S . `
    -B $BuildDir `
    -G "Ninja" `
    -DCMAKE_BUILD_TYPE=$Configuration

Write-Host "==> Building project..." -ForegroundColor Cyan

cmake `
    --build $BuildDir `
    --parallel

if ($Run)
{
    Write-Host "==> Launching QEMU..." -ForegroundColor Green

    cmake `
        --build $BuildDir `
        --target run
}
elseif ($DebugQemu)
{
    Write-Host "==> Launching QEMU (waiting for GDB)..." -ForegroundColor Yellow

    cmake `
        --build $BuildDir `
        --target debug
}
else
{
    Write-Host ""
    Write-Host "Build completed successfully." -ForegroundColor Green
    Write-Host ""
    Write-Host "Artifacts:"
    Write-Host "  ELF : $BuildDir/kernel.elf"
    Write-Host "  ISO : $BuildDir/Citadel.iso"
}