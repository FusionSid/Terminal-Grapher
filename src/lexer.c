#include "lexer.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lexer_tokenise(char* buffer) {
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

                printf("%s, Number: %f\n",
                       token_to_string(LEXER_TOKEN_NUMBER), value);

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

            printf("%s, Identifier: %s\n",
                   token_to_string(LEXER_TOKEN_IDENTIFIER), identifier_buffer);
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

        printf("%s\n", token_to_string(token.type));
        i++;
    }

    lexer_token_t end_token = {0};
    end_token.type = LEXER_TOKEN_END;
    printf("%s\n", token_to_string(end_token.type));
}