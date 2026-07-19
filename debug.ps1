$ErrorActionPreference = "Stop"

$BuildDir = "build"
$Iso = Join-Path $BuildDir "Citadel.iso"

$qemu = Get-Command qemu-system-x86_64 -ErrorAction Stop

& $qemu.Source `
    -cdrom $Iso `
    -m 512M `
    -cpu max `
    -machine q35 `
    -serial stdio `
    -monitor vc `
    -no-reboot `
    -no-shutdown `
    -s `
    -S