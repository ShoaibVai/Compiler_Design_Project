#include "lexer.h"

#include <ctype.h>

static void skip_whitespace(Lexer *lexer) {
    while (lexer->source[lexer->index] == ' ' || lexer->source[lexer->index] == '\t') {
        lexer->index++;
    }
}

Lexer lexer_create(const char *source) {
    Lexer lexer = { source, 0 };
    return lexer;
}

Token lexer_next(Lexer *lexer) {
    skip_whitespace(lexer);

    char c = lexer->source[lexer->index];
    Token token = { TOK_INVALID, 0.0, lexer->index };

    if (c == '\0') {
        token.type = TOK_END;
        return token;
    }

    if (isdigit((unsigned char)c)) {
        double value = 0.0;
        while (isdigit((unsigned char)lexer->source[lexer->index])) {
            value = value * 10 + (lexer->source[lexer->index] - '0');
            lexer->index++;
        }
        token.type = TOK_NUMBER;
        token.value = value;
        return token;
    }

    lexer->index++; /* consume single-character tokens */

    switch (c) {
    case '+': token.type = TOK_PLUS; break;
    case '-': token.type = TOK_MINUS; break;
    case '*': token.type = TOK_STAR; break;
    case '/': token.type = TOK_SLASH; break;
    case '(': token.type = TOK_LPAREN; break;
    case ')': token.type = TOK_RPAREN; break;
    default: token.type = TOK_INVALID; break;
    }

    return token;
}
