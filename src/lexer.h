#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

typedef enum {
    TOK_NUMBER,
    TOK_PLUS,
    TOK_MINUS,
    TOK_STAR,
    TOK_SLASH,
    TOK_LPAREN,
    TOK_RPAREN,
    TOK_END,
    TOK_INVALID
} TokenType;

typedef struct {
    TokenType type;
    double value;
    size_t position; /* index in the source string */
} Token;

typedef struct {
    const char *source;
    size_t index;
} Lexer;

Lexer lexer_create(const char *source);
Token lexer_next(Lexer *lexer);

#endif /* LEXER_H */
