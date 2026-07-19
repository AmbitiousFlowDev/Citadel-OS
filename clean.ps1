$ErrorActionPreference = "Stop"

if (Test-Path build)
{
    Remove-Item build -Recurse -Force
    Write-Host "Build directory removed."
}
else
{
    Write-Host "Nothing to clean."
}