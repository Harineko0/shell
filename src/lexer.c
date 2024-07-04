#include <stdio.h>
#include "lib/io.h"
#include "lib/str.h"
#include "lexer.h"

#define is_eof(c) (c == '\n' || c == EOF || c == '\0')
#define is_eol(c) (c == '\n' || c == ';')
#define is_literal(c) ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')

typedef unsigned long long ull;

typedef enum {
    DEFAULT,
    SPACE,
    ESCAPE,
    WORD,
    S_EOL,
    S_DOLLAR
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
        char next_c = *str;

        if (state == DEFAULT) {
            if (c == ' ') {
                state = SPACE;
            } else if (c == '\\') {
                state = ESCAPE;
            } else if (is_eol(c)) {
                state = S_EOL;
            } else if (c == '$' && is_literal(next_c)) {
                state =S_DOLLAR;
            } else {
                // 普通の文字
                state = WORD;
            }
        }

        if (state == WORD) {
            debug("    WORD");
            if (next_c == ' ' || is_eof(next_c)) {
                ull len = str - s;

                if (len == 2 && strstart(s, "if")) {
                    token = Token_insert(token, IF, NULL);
                } else {
                    char *substring = substr(s, str);
                    token = Token_insert(token, LITERAL, substring);
                }

                s = str;
                state = DEFAULT;
            }
        } else if (state == SPACE) {
            debug("    SPACE");
            if (next_c != ' ') {
                s = str;
                state = DEFAULT;
            }
        } else if (state == S_EOL) {
            if (!is_eol(next_c)) {
                token = Token_insert(token, EOL, NULL);
                s = str;
                state = DEFAULT;
            }
        } else if (state == S_DOLLAR) {
            // state == DEFAULT の部分で next_c の判定をしている
            token = Token_insert(token, DOLLAR, NULL);
            s = str;
            state = DEFAULT;
        } else if (state == ESCAPE) {
            // TODO
        }
    }

    debug("return");
    return first_token;
}