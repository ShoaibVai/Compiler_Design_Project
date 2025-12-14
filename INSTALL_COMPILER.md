# Installation Guide for C Compiler

## Problem
The project requires a C99-compatible compiler, but none is currently installed on your system.

## Solution: Install a C Compiler

### Option 1: Clang via winget (Recommended - Fastest)
Open PowerShell and run:
```powershell
winget install -e --id LLVM.LLVM
```
Then restart your terminal and run `.\build.ps1`

### Option 2: MinGW-w64 via winget
```powershell
winget install -e --id mingw.mingw
```

### Option 3: Visual Studio Build Tools (Microsoft)
Install Visual Studio Community or Build Tools from:
https://visualstudio.microsoft.com/downloads/

During installation, select "Desktop development with C++"

### Option 4: Manual MinGW Installation
1. Download from: https://www.mingw-w64.org/
2. Install to `C:\mingw64` (or similar)
3. Add `C:\mingw64\bin` to your PATH environment variable

## After Installation
1. **Restart your terminal** (important!)
2. Verify installation: `gcc --version` or `clang --version`
3. Build the project: `.\build.ps1`
4. Run: `.\simple_compiler.exe`

## Alternative: Use Online Compiler
If you can't install a compiler, copy all `.c` and `.h` files to an online C compiler:
- https://www.onlinegdb.com/online_c_compiler
- https://replit.com/languages/c
- https://www.programiz.com/c-programming/online-compiler/

Select "Create multiple files", copy each file, and click Run.
