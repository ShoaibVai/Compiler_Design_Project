#include <stdio.h>
#include <string.h>

#include "lexer.h"
#include "parser.h"

static const char *token_name(TokenType type) {
    switch (type) {
    case TOK_NUMBER: return "NUMBER";
    case TOK_PLUS: return "PLUS";
    case TOK_MINUS: return "MINUS";
    case TOK_STAR: return "STAR";
    case TOK_SLASH: return "SLASH";
    case TOK_LPAREN: return "LPAREN";
    case TOK_RPAREN: return "RPAREN";
    case TOK_END: return "END";
    default: return "INVALID";
    }
}

static void run_lexer_demo(const char *input) {
    Lexer lexer = lexer_create(input);
    printf("Lexical analysis (token stream):\n");
    while (1) {
        Token t = lexer_next(&lexer);
        if (t.type == TOK_NUMBER) {
            printf("  %-7s value=%.0f at pos=%zu\n", token_name(t.type), t.value, t.position);
        } else {
            printf("  %-7s at pos=%zu\n", token_name(t.type), t.position);
        }
        if (t.type == TOK_END || t.type == TOK_INVALID) break;
    }
    printf("\n");
}

int main(void) {
    char input[256];

    printf("Simple C99 mini-compiler demo (expressions with + - * / and parentheses)\n");
    printf("Type an expression or 'q' to quit.\n\n");

    while (1) {
        printf("> ");
        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }

        /* strip newline */
        input[strcspn(input, "\n")] = '\0';
        if (strcmp(input, "q") == 0 || strcmp(input, "quit") == 0) {
            break;
        }
        if (input[0] == '\0') {
            continue;
        }

        run_lexer_demo(input);

        Lexer parser_lexer = lexer_create(input);
        AstNode *root = parse_expression(&parser_lexer);
        if (!root) {
            printf("Could not parse input. Please try again.\n\n");
            continue;
        }

        printf("Postfix (intermediate code):\n  ");
        print_postfix(root);
        printf("\n");

        double result = eval_ast(root);
        printf("Evaluation result: %.2f\n\n", result);

        free_ast(root);
    }

    printf("Goodbye!\n");
    return 0;
}
