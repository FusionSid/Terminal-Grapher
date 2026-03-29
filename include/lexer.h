#pragma once

#define MAX_IDENTIFIER_SIZE 256

#define LEXER_TOKEN_LIST      \
    X(LEXER_TOKEN_IDENTIFIER) \
    X(LEXER_TOKEN_LPAREN)     \
    X(LEXER_TOKEN_RPAREN)     \
    X(LEXER_TOKEN_EXP)        \
    X(LEXER_TOKEN_DIVIDE)     \
    X(LEXER_TOKEN_MULTIPLY)   \
    X(LEXER_TOKEN_MOD)        \
    X(LEXER_TOKEN_ADD)        \
    X(LEXER_TOKEN_SUBTRACT)   \
    X(LEXER_TOKEN_NUMBER)     \
    X(LEXER_TOKEN_END)        \
    X(LEXER_TOKEN__COUNT)

#define X(name) name,
typedef enum { LEXER_TOKEN_LIST } lexer_token_e;
#undef X

typedef struct {
    lexer_token_e type;
    union {
        char identifier[MAX_IDENTIFIER_SIZE];
        double value;
    };
} lexer_token_t;

static inline const char* token_to_string(lexer_token_e token) {
    switch (token) {
#define X(name) \
    case name:  \
        return #name;
        LEXER_TOKEN_LIST
#undef X
        default:
            return "invalid token type";
    }
}