Param (
  [Parameter(Mandatory=$true)][String] $Path
)

[String] $toolsHost = "http://azertyvortex.free.fr/download"

function cdTemplate {
  Write-Host "setup cd_template"
  Download $toolsHost/neobuild-cd_template.zip $Path\neobuild-cd_template.zip
  Expand-Archive -Path $Path\neobuild-cd_template.zip -DestinationPath $Path -Force
}

function raine {
  Write-Host "setup raine emulator"
  Download $toolsHost/neobuild-raine.zip $Path\neobuild-raine.zip
  Expand-Archive -Path $Path\neobuild-raine.zip -DestinationPath $Path -Force
}

function raineConfig {
  Write-Host "configure raine"
  $content = [System.IO.File]::ReadAllText("$Path\raine\config\raine32_sdl.cfg").Replace("/*neocd_bios*/","neocd_bios = $Path\raine\roms\NEOCD.BIN")
  [System.IO.File]::WriteAllText("$Path\raine\config\raine32_sdl.cfg", $content)
}

function bin {
  Write-Host "setup bin"
  Download $toolsHost/neocore-bin.zip $Path\neocore-bin.zip
  Expand-Archive -Path $Path\neocore-bin.zip -DestinationPath $Path -Force
}

function sdk {
  Write-Host "setup sdk"
  Download $toolsHost/neodev-sdk.zip $Path\neodev-sdk.zip
  Expand-Archive -Path $Path\neodev-sdk.zip -DestinationPath $Path -Force
}

function Download([String] $url, [String] $targetFile){
  Write-Host "download : $url $targetFile"
  Import-Module BitsTransfer

  $start_time = Get-Date
  Start-BitsTransfer -Source $url -Destination $targetFile
  Write-Output "Time taken: $((Get-Date).Subtract($start_time).Seconds) second(s)"
}

function Main {
  if ((Test-Path -Path $Path) -eq $true) { Remove-Item -Force -Recurse -Path $Path }
  New-Item -ItemType Directory -Force -Path $Path
  sdk
  cdTemplate
  raine
  raineConfig
  bin
}

Main
