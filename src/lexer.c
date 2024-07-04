#include <stdio.h>
#include <string.h>
#include "lib/io.h"
#include "lib/str.h"
#include "lexer.h"

#define is_eof(c) (c == '\n' || c == EOF || c == '\0')
#define is_eol(c) (c == '\n' || c == ';')

typedef unsigned long long ull;

typedef enum {
    DEFAULT,
    SPACE,
    ESCAPE,
    WORD,
    EOLine
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
            } else if (is_eol(c)) {
                state = EOLine;
            } else {
                // 普通の文字
                state = WORD;
            }
        }

        char next_c = *str;

        if (state == WORD) {
            debug("    WORD");
            if (next_c == ' ' || next_c == '\\' || is_eof(next_c)) {
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
        } else if (state == EOLine) {
            if (!is_eol(next_c)) {
                token = Token_insert(token, EOL, NULL);
                s = str;
                state = DEFAULT;
            }
        } else if (state == ESCAPE) {
            // TODO
        }
    }

    debug("return");
    return first_token;
}