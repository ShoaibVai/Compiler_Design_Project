# Simple Compiler Design Demo (C99)

This tiny project demonstrates core compiler phases on a single arithmetic expression:

- **Lexical analysis** → split the input into tokens (`NUMBER`, `PLUS`, `MINUS`, `STAR`, `SLASH`, parentheses).
- **Parsing** → recursive-descent parser builds a minimal AST using the grammar below.
- **Intermediate form** → postfix (Reverse Polish) walk of the AST.
- **Evaluation** → interpret the AST to produce the numeric result.

The code is intentionally small and easy to explain to highlight each phase separately.

## Grammar (recursive-descent)

```
Expr  -> Term (("+" | "-") Term)*
Term  -> Factor (("*" | "/") Factor)*
Factor-> NUMBER | "(" Expr ")"
```

## Files

- `src/lexer.h/.c` – token definitions and a whitespace-skipping lexer.
- `src/parser.h/.c` – AST nodes, recursive-descent parser, postfix printer, and evaluator.
- `src/main.c` – CLI loop that shows tokens, prints postfix, and evaluates the expression.
- `Makefile` – convenience build target (requires `make`).

## Building

You need a C compiler that supports C99 (e.g., GCC via MinGW, Clang, or MSVC).

### Quick Build (Windows)

**Option 1: Use the build script (easiest)**
```powershell
.\build.ps1
```
or
```cmd
build.bat
```

The script will automatically detect and use any available compiler (gcc, clang, or cl).

**Option 2: Install a compiler first**

If no compiler is found, install one:
- **MinGW-w64**: Download from https://www.mingw-w64.org/ or use `winget install -e --id LLVM.LLVM`
- **Visual Studio**: Install Visual Studio Community (includes MSVC)
- **Clang**: Download from https://releases.llvm.org/

### Build Manually

**With GCC (MinGW):**
```bash
gcc -std=c99 -Wall -Wextra -pedantic src/main.c src/lexer.c src/parser.c -o simple_compiler
```

**With Make:**
```bash
make
```

**With MSVC:**
```cmd
cl /W4 src/main.c src/lexer.c src/parser.c /Fe:simple_compiler.exe
```

## Running

```
./simple_compiler
```

Type an expression (or `q` to quit). Supported operators: `+ - * /` and parentheses.

## Example session

```
> 3 + 4 * (2 - 1)
Lexical analysis (token stream):
	NUMBER  value=3 at pos=0
	PLUS    at pos=2
	NUMBER  value=4 at pos=4
	STAR    at pos=6
	LPAREN  at pos=8
	NUMBER  value=2 at pos=9
	MINUS   at pos=11
	NUMBER  value=1 at pos=13
	RPAREN  at pos=14
	END     at pos=15

Postfix (intermediate code):
	3 4 2 1 - * +
Evaluation result: 7.00
```

## How to explain this to a professor

- Show the **lexer** turning characters into tokens, highlighting how whitespace is skipped.
- Walk through the grammar above and how each function (`parse_expression`, `parse_term`, `parse_factor`) matches it.
- Print the AST in postfix order as a stand-in for “intermediate code”.
- Evaluate the AST to show semantic processing / interpretation.

That’s it—four small C files that map cleanly onto classic compiler phases.

