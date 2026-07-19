$ErrorActionPreference = "Stop"

$BuildDir = "build"
$Iso = Join-Path $BuildDir "Citadel.iso"

if (-not (Test-Path $Iso))
{
    Write-Host "ISO not found: $Iso" -ForegroundColor Red
    exit 1
}

$qemu = Get-Command qemu-system-x86_64 -ErrorAction Stop

& $qemu.Source `
    -cdrom $Iso `
    -m 512M `
    -cpu max `
    -machine q35 `
    -serial stdio `
    -monitor vc `
    -no-reboot `
    -no-shutdown