#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "lib/io.h"

Token *Token_create() {
    Token *token = malloc(sizeof (Token));
    token->type = UNDEFINED;
    token->string = NULL;
    token->next = NULL;
    return token;
}

Token *Token_insert(Token *prev, TokenType type, char *string) {
    if (prev->type == UNDEFINED) {
        prev->type = type;
        prev->string = string;
        return prev;
    }

    Token *next = malloc(sizeof (Token));
    prev->next = next;
    next->type = type;
    next->string = string;
    next->next = NULL;
    return next;
}

void Token_free(Token *first) {
    while (first != NULL) {
        Token *next = first->next;
        if (first->string != NULL)
            free(first->string);
        free(first);
        first = next;
    }
}

char *Token_to_string(Token *token) {
    if (token == NULL) return "";

    char *type = "";

    switch (token->type) {
        case UNDEFINED:
            type = "UNDEFINED";
            break;
        case LITERAL:
            type = "LITERAL";
            break;
        case IF:
            type = "IF";
            break;
        case EQUAL:
            type = "EQUAL";
            break;
        case EOL:
            type = "EOL";
            break;
        case DOLLAR:
            type = "DOLLAR";
            break;
    }

    if (token->string == NULL) return type;

    char *buff = calloc(strlen(type) + 3 + strlen(token->string), sizeof (char));
    strcat_s(buff, 100, type);
    strcat_s(buff, 100, " (");
    strcat_s(buff, 100, token->string);
    strcat_s(buff, 100, ")");
    return buff;
}