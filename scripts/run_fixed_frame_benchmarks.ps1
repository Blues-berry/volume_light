param(
    [string]$ExePath = "C:\Users\Bluesky\Desktop\codex_test\HybridRenderingEngine\build\Release\hybridRenderer.exe",
    [string]$WorkingDirectory = "C:\Users\Bluesky\Desktop\codex_test\HybridRenderingEngine\build",
    [string]$OutputDirectory = "C:\Users\Bluesky\Desktop\codex_test\HybridRenderingEngine\docs\artifacts\benchmarks\manual-run",
    [int]$FrameCount = 120
)

$scenes = @("Sponza", "MetalRoughSpheres", "DamagedHelmet")

New-Item -ItemType Directory -Force -Path $OutputDirectory | Out-Null

foreach ($scene in $scenes) {
    $baseName = ($scene.ToLower())
    $outPath = Join-Path $OutputDirectory "$baseName-$FrameCount.txt"
    $errPath = Join-Path $OutputDirectory "$baseName-$FrameCount.err.txt"

    if (Test-Path $outPath) { Remove-Item $outPath -Force }
    if (Test-Path $errPath) { Remove-Item $errPath -Force }

    Write-Host "Running benchmark: $scene ($FrameCount frames)"
    $process = Start-Process `
        -FilePath $ExePath `
        -ArgumentList $scene, $FrameCount `
        -WorkingDirectory $WorkingDirectory `
        -RedirectStandardOutput $outPath `
        -RedirectStandardError $errPath `
        -PassThru

    $process.WaitForExit()

    $result = Get-Item $outPath
    Write-Host ("Saved: " + $result.FullName)
}
