#include "parser.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    Lexer *lexer;
    Token current;
} Parser;

static void advance(Parser *parser) {
    parser->current = lexer_next(parser->lexer);
}

static AstNode *make_number(double value) {
    AstNode *node = (AstNode *)malloc(sizeof(AstNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed for number node.\n");
        exit(EXIT_FAILURE);
    }
    node->type = AST_NUMBER;
    node->value = value;
    node->op = '\0';
    node->left = NULL;
    node->right = NULL;
    return node;
}

static AstNode *make_binary(char op, AstNode *left, AstNode *right) {
    AstNode *node = (AstNode *)malloc(sizeof(AstNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed for binary node.\n");
        exit(EXIT_FAILURE);
    }
    node->type = AST_BINARY;
    node->value = 0.0;
    node->op = op;
    node->left = left;
    node->right = right;
    return node;
}

static AstNode *parse_expression_internal(Parser *parser);
static AstNode *parse_term(Parser *parser);
static AstNode *parse_factor(Parser *parser);

static AstNode *parse_factor(Parser *parser) {
    Token t = parser->current;

    if (t.type == TOK_NUMBER) {
        advance(parser);
        return make_number(t.value);
    }

    if (t.type == TOK_LPAREN) {
        advance(parser);
        AstNode *expr = parse_expression_internal(parser);
        if (parser->current.type != TOK_RPAREN) {
            fprintf(stderr, "Parse error: expected ')' at position %zu\n", parser->current.position);
            free_ast(expr);
            return NULL;
        }
        advance(parser);
        return expr;
    }

    fprintf(stderr, "Parse error: unexpected token at position %zu\n", t.position);
    return NULL;
}

static AstNode *parse_term(Parser *parser) {
    AstNode *node = parse_factor(parser);
    if (!node) return NULL;

    while (parser->current.type == TOK_STAR || parser->current.type == TOK_SLASH) {
        char op = (parser->current.type == TOK_STAR) ? '*' : '/';
        advance(parser);
        AstNode *right = parse_factor(parser);
        if (!right) {
            free_ast(node);
            return NULL;
        }
        node = make_binary(op, node, right);
    }

    return node;
}

static AstNode *parse_expression_internal(Parser *parser) {
    AstNode *node = parse_term(parser);
    if (!node) return NULL;

    while (parser->current.type == TOK_PLUS || parser->current.type == TOK_MINUS) {
        char op = (parser->current.type == TOK_PLUS) ? '+' : '-';
        advance(parser);
        AstNode *right = parse_term(parser);
        if (!right) {
            free_ast(node);
            return NULL;
        }
        node = make_binary(op, node, right);
    }

    return node;
}

AstNode *parse_expression(Lexer *lexer) {
    Parser parser = { lexer, { TOK_INVALID, 0.0, 0 } };
    advance(&parser);

    AstNode *root = parse_expression_internal(&parser);
    if (!root) return NULL;

    if (parser.current.type != TOK_END) {
        fprintf(stderr, "Parse error: leftover input starting at position %zu\n", parser.current.position);
        free_ast(root);
        return NULL;
    }

    return root;
}

void free_ast(AstNode *node) {
    if (!node) return;
    free_ast(node->left);
    free_ast(node->right);
    free(node);
}

double eval_ast(const AstNode *node) {
    if (!node) return 0.0;

    if (node->type == AST_NUMBER) {
        return node->value;
    }

    double left = eval_ast(node->left);
    double right = eval_ast(node->right);

    switch (node->op) {
    case '+': return left + right;
    case '-': return left - right;
    case '*': return left * right;
    case '/': return right != 0 ? left / right : 0.0;
    default: return 0.0;
    }
}

void print_postfix(const AstNode *node) {
    if (!node) return;

    print_postfix(node->left);
    print_postfix(node->right);

    if (node->type == AST_NUMBER) {
        printf("%.0f ", node->value);
    } else {
        printf("%c ", node->op);
    }
}
