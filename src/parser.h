#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef enum {
    AST_NUMBER,
    AST_BINARY
} AstType;

typedef struct AstNode {
    AstType type;
    double value; /* used when type is AST_NUMBER */
    char op;      /* used when type is AST_BINARY */
    struct AstNode *left;
    struct AstNode *right;
} AstNode;

AstNode *parse_expression(Lexer *lexer);
void free_ast(AstNode *node);
double eval_ast(const AstNode *node);
void print_postfix(const AstNode *node);

#endif /* PARSER_H */
