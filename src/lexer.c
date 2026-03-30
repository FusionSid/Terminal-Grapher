#include "lexer.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_ARRAY_SIZE 16

void token_add(tokens_list_t* list, lexer_token_t token) {
    if (list->count == 0) {
        list->capacity = DEFAULT_ARRAY_SIZE;
        list->items =
            (lexer_token_t*)malloc(list->capacity * sizeof(lexer_token_t));
        printf("R: %i\n", list->items == NULL);
    }

    if (list->count == list->capacity) {
        list->capacity = list->capacity * 2;
        list->items = (lexer_token_t*)realloc(list->items, sizeof(lexer_token_t) * list->capacity);
       printf("R: %i\n", list->items == NULL);
    }

    list->items[list->count++] = token;
}

void lexer_tokenise(tokens_list_t* tokens_list, char* buffer) {
    int length = strlen(buffer);

    int i = 0;
    while (i < length) {
        char c = buffer[i];

        if (isspace(c)) {
            i++;
            continue;
        }

        lexer_token_t token = {0};

        if (isdigit(c) || c == '.') {
            char* end;
            double value = strtod(&buffer[i], &end);

            if (end != &buffer[i]) {
                token.value = value;
                token.type = LEXER_TOKEN_NUMBER;

                token_add(tokens_list, token);

                i = end - buffer;
                continue;
            }
        } else if (isalpha(c)) {
            char identifier_buffer[256];
            int identifier_buffer_idx = 0;

            while ((isalpha(buffer[i])) && identifier_buffer_idx < 255) {
                identifier_buffer[identifier_buffer_idx++] = buffer[i++];
            }
            identifier_buffer[identifier_buffer_idx] = '\0';

            strcpy(token.identifier, identifier_buffer);
            token.type = LEXER_TOKEN_IDENTIFIER;

            token_add(tokens_list, token);
            continue;
        } else if (c == '+') {
            token.type = LEXER_TOKEN_ADD;
        } else if (c == '-') {
            token.type = LEXER_TOKEN_SUBTRACT;
        } else if (c == '/') {
            token.type = LEXER_TOKEN_DIVIDE;
        } else if (c == '*') {
            token.type = LEXER_TOKEN_MULTIPLY;
        } else if (c == '^') {
            token.type = LEXER_TOKEN_EXP;
        } else if (c == '%') {
            token.type = LEXER_TOKEN_MOD;
        } else if (c == '(') {
            token.type = LEXER_TOKEN_LPAREN;
        } else if (c == ')') {
            token.type = LEXER_TOKEN_RPAREN;
        } else {
            i++;
            continue;
        }

        token_add(tokens_list, token);
        i++;
    }

    lexer_token_t end_token = {0};
    end_token.type = LEXER_TOKEN_END;
    token_add(tokens_list, end_token);
}