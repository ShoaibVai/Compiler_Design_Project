# Presentation Guide for Professor

## Quick Overview (30 seconds)
"This is a mini-compiler for arithmetic expressions that demonstrates the four main phases of compilation: lexical analysis, parsing, intermediate code generation, and evaluation."

## Demo Flow (2-3 minutes)

### 1. Show Input
```
3 + 4 * (2 - 1)
```

### 2. Explain Lexical Analysis (Lexer)
**File:** `src/lexer.c`

"The lexer breaks the input into tokens:"
- Numbers: `3`, `4`, `2`, `1`
- Operators: `+`, `*`, `-`
- Parentheses: `(`, `)`

**Key function:** `lexer_next()` - returns one token at a time

### 3. Explain Parsing
**File:** `src/parser.c`

"The parser builds an Abstract Syntax Tree (AST) using recursive descent."

**Grammar:**
```
Expression → Term ((+ | -) Term)*
Term       → Factor ((* | /) Factor)*
Factor     → Number | (Expression)
```

This grammar ensures correct operator precedence (multiply/divide before add/subtract).

**Key functions:**
- `parse_expression()` - handles + and -
- `parse_term()` - handles * and /
- `parse_factor()` - handles numbers and parentheses

### 4. Show Intermediate Code
"The AST is traversed in postfix order (Reverse Polish Notation):"
```
3 4 2 1 - * +
```

This is easier for machines to evaluate than infix notation.

### 5. Explain Evaluation
"The evaluator walks the AST tree recursively:"
- For numbers: return the value
- For operators: evaluate left and right subtrees, then apply the operator

**Result:** `7.00`

## Code Walkthrough (If Asked)

### Lexer (Simple to Explain)
```c
// Main loop skips whitespace, then:
if (isdigit(c)) {
    // Build number token
} else {
    // Return operator token
}
```

### Parser (Recursive Descent)
```c
parse_expression() {
    node = parse_term();
    while (+ or -) {
        right = parse_term();
        node = make_binary_node(op, node, right);
    }
    return node;
}
```

### Evaluator (Tree Walking)
```c
eval_ast(node) {
    if (node is number) return value;
    left = eval_ast(node->left);
    right = eval_ast(node->right);
    return apply_operator(left, op, right);
}
```

## Questions You Might Get

**Q: Why not use Lex/Yacc?**
A: This demonstrates the underlying principles without tool-generated code, making it easier to explain.

**Q: Can it handle floating-point numbers?**
A: The parser supports integer input, but the evaluator uses `double` for division. Easy to extend to decimal input.

**Q: What about error handling?**
A: The parser reports position of errors and handles mismatched parentheses.

**Q: How would you extend this?**
A: Could add variables, functions, or more operators. The recursive descent structure makes this straightforward.

## Key Strengths to Mention

1. **Clean separation** - Each compiler phase is in its own function
2. **Standard techniques** - Recursive descent parsing is industry-standard
3. **C99 compliant** - Portable, follows best practices
4. **Well-structured** - Clear grammar, proper AST nodes, memory management
5. **Testable** - Easy to trace through with examples

## Time Allocation
- Overview: 30 seconds
- Live demo: 1 minute
- Code walkthrough: 2-3 minutes
- Questions: 1-2 minutes

**Total:** ~5-7 minutes (adjust based on requirements)

## Pro Tip
Have 2-3 example expressions ready to demonstrate:
1. Simple: `2 + 3` (shows basic operation)
2. Precedence: `2 + 3 * 4` (shows * before +)
3. Parentheses: `(2 + 3) * 4` (shows grammar recursion)
