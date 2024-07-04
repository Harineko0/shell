#include <stdio.h>
#include "lib/io.h"
#include "lib/str.h"
#include "lexer.h"

#define is_eof(c) (c == '\n' || c == EOF || c == '\0')

typedef unsigned long long ull;

typedef enum {
    DEFAULT,
    SPACE,
    ESCAPE,
    WORD
} State;

/// 字句解析
Token *lexer(char *str) {
    Token *first_token = Token_create();
    Token *token = first_token;
    char *s = str;
    char c;
    State state = DEFAULT;

    while ((c = *str++) != '\0') {
        debug("> %c (%d)", c, c);
        if (state == DEFAULT) {
            if (c == ' ') {
                state = SPACE;
            } else if (c == '\\') {
                state = ESCAPE;
            } else {
                // 普通の文字
                state = WORD;
            }
        }

        if (state == WORD) {
            debug("    WORD");
            if (c == ' ' || c == '\\' || is_eof(c)) {
                char *substring = substr(s, str - 1);
                token = Token_insert(token, LITERAL, substring);
                s = str;
                state = DEFAULT;
            }
        } else if (state == SPACE) {
            debug("    SPACE");
            if (c != ' ') {
                s = str - 1;
                state = DEFAULT;
            }
        } else if (state == ESCAPE) {
            // TODO
        }

        if (is_eof(c)) {
            break;
        }
    }

    debug("return");
    return first_token;
}