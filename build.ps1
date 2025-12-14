# PowerShell build script

Write-Host "Building Simple Compiler Demo..." -ForegroundColor Cyan

$compilerFound = $false

# Try gcc first (MinGW)
if (Get-Command gcc -ErrorAction SilentlyContinue) {
    Write-Host "Using GCC..." -ForegroundColor Green
    gcc -std=c99 -Wall -Wextra -pedantic src/main.c src/lexer.c src/parser.c -o simple_compiler.exe
    if ($LASTEXITCODE -eq 0) {
        Write-Host "Build successful! Run with: .\simple_compiler.exe" -ForegroundColor Green
        $compilerFound = $true
    }
}

# Try clang
if (-not $compilerFound -and (Get-Command clang -ErrorAction SilentlyContinue)) {
    Write-Host "Using Clang..." -ForegroundColor Green
    clang -std=c99 -Wall -Wextra -pedantic src/main.c src/lexer.c src/parser.c -o simple_compiler.exe
    if ($LASTEXITCODE -eq 0) {
        Write-Host "Build successful! Run with: .\simple_compiler.exe" -ForegroundColor Green
        $compilerFound = $true
    }
}

# Try MSVC
if (-not $compilerFound -and (Get-Command cl -ErrorAction SilentlyContinue)) {
    Write-Host "Using MSVC..." -ForegroundColor Green
    cl /W4 src/main.c src/lexer.c src/parser.c /Fe:simple_compiler.exe 2>&1 | Out-Null
    if ($LASTEXITCODE -eq 0) {
        Write-Host "Build successful! Run with: .\simple_compiler.exe" -ForegroundColor Green
        $compilerFound = $true
    }
}

if (-not $compilerFound) {
    Write-Host "`nERROR: No C compiler found!" -ForegroundColor Red
    Write-Host "Please install one of the following:" -ForegroundColor Yellow
    Write-Host "  - MinGW-w64: https://www.mingw-w64.org/" -ForegroundColor Yellow
    Write-Host "  - MSVC: Install Visual Studio or Build Tools" -ForegroundColor Yellow
    Write-Host "  - Clang: https://releases.llvm.org/" -ForegroundColor Yellow
    Write-Host "`nQuick install with winget (Windows Package Manager):" -ForegroundColor Cyan
    Write-Host "  winget install -e --id LLVM.LLVM" -ForegroundColor White
    exit 1
}
