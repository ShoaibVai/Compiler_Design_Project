@echo off
REM Build script for Windows CMD/PowerShell

echo Building Simple Compiler Demo...

REM Try gcc first (MinGW)
where gcc >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo Using GCC...
    gcc -std=c99 -Wall -Wextra -pedantic src\main.c src\lexer.c src\parser.c -o simple_compiler.exe
    if %ERRORLEVEL% EQU 0 (
        echo Build successful! Run with: simple_compiler.exe
        exit /b 0
    )
)

REM Try clang
where clang >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo Using Clang...
    clang -std=c99 -Wall -Wextra -pedantic src\main.c src\lexer.c src\parser.c -o simple_compiler.exe
    if %ERRORLEVEL% EQU 0 (
        echo Build successful! Run with: simple_compiler.exe
        exit /b 0
    )
)

REM Try MSVC
where cl >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo Using MSVC...
    cl /W4 src\main.c src\lexer.c src\parser.c /Fe:simple_compiler.exe
    if %ERRORLEVEL% EQU 0 (
        echo Build successful! Run with: simple_compiler.exe
        exit /b 0
    )
)

echo ERROR: No C compiler found!
echo Please install one of the following:
echo   - MinGW-w64: https://www.mingw-w64.org/
echo   - MSVC: Install Visual Studio or Build Tools
echo   - Clang: https://releases.llvm.org/
exit /b 1
