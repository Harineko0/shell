#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    UNDEFINED,
    LITERAL,
    IF,
    THEN,
    ELIF,
    ELSE,
    FI,
    FOR,
    DO,
    DONE,
    EQUAL,
//    LEFTPARE,
//    RIGHTPARE,
//    LEFTCURLY,
//    RIGHTCURLY,
    EOL, // ;, \n
    DOLLAR,
    DQUOTE, // "
} TokenType;

typedef struct token Token;
struct token {
    TokenType type;
    char *string; // LITERAL 以外は NULL
    Token *next;
};

Token *Token_new();
Token *Token_insert(Token *prev, TokenType type, char *string);
void Token_free(Token *first);
char *Token_to_string(Token *token);

#endif