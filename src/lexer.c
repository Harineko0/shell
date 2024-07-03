#include <stdlib.h>
#include <stdio.h>
#include "lib/io.h"
#include "lib/str.h"

#define MAX_TOKEN 256
#define is_eof(c) (c == '\n' || c == EOF || c == '\0')

typedef unsigned long long ull;

typedef enum {
    DEFAULT,
    SPACE,
    ESCAPE,
    WORD
} State;

/// 字句解析
char** lexer(char *str) {
    char *tokens[MAX_TOKEN], **t = tokens, *s = str;
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
                *t++ = substr(s, str - 1);
                s = str;
                state = DEFAULT;
            }
        } else if (state == SPACE) {
            debug("    SPACE");
            if (c != ' ') {
                *t++ = substr(s - 1, str - 1);
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

    char **result = calloc(t - tokens + 1, sizeof (char *));
    char **r = result, **_t = tokens;

    while (t - _t > 0) {
        *r++ = *_t++;
    }

    *r = NULL;

    return result;
}