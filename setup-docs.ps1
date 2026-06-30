$ErrorActionPreference = "Stop"

$root = Split-Path -Parent $MyInvocation.MyCommand.Path
$venvPath = Join-Path $root ".rtd-env"
$pythonInVenv = Join-Path $venvPath "Scripts\python.exe"
$autobuildExe = Join-Path $venvPath "Scripts\sphinx-autobuild.exe"
$requirementsFile = Join-Path $root "docs\requirements.txt"
$docsDir = Join-Path $root "docs"
$outputDir = Join-Path $root "_autobuild\html"

function Get-PythonCommand {
    if (Get-Command py -ErrorAction SilentlyContinue) {
        try {
            & py -3.11 -c "import sys; print(sys.version)"
            if ($LASTEXITCODE -eq 0) {
                return @("py", "-3.11")
            }
        } catch {
        }

        try {
            & py -3 -c "import sys; print(sys.version)"
            if ($LASTEXITCODE -eq 0) {
                return @("py", "-3")
            }
        } catch {
        }
    }

    if (Get-Command python -ErrorAction SilentlyContinue) {
        return @("python")
    }

    throw "Python not found. Please install Python 3.11 or newer first."
}

if (-not (Test-Path $requirementsFile)) {
    throw "Missing requirements file: $requirementsFile"
}

if (-not (Test-Path $pythonInVenv)) {
    Write-Host "Creating virtual environment in .rtd-env ..."
    $pythonCommand = Get-PythonCommand
    if ($pythonCommand.Length -gt 1) {
        & $pythonCommand[0] $pythonCommand[1] -m venv $venvPath
    } else {
        & $pythonCommand[0] -m venv $venvPath
    }
}

Write-Host "Upgrading pip ..."
& $pythonInVenv -m pip install --upgrade pip

Write-Host "Installing documentation dependencies ..."
& $pythonInVenv -m pip install -r $requirementsFile sphinx-autobuild

Write-Host "Starting sphinx-autobuild at http://127.0.0.1:8000/ ..."
& $autobuildExe $docsDir $outputDir --host 127.0.0.1 --port 8000
