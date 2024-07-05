#include <stdio.h>
#include "lib/io.h"
#include "lib/str.h"
#include "lexer.h"

#define is_eol(c) (c == '\n' || c == ';')
#define is_literal(c) ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_' || c == '.' || c == '/')

typedef unsigned long long ull;

typedef enum {
    DEFAULT,
    SPACE,
    S_LITERAL,
    S_EOL,
    S_DOLLAR,
    S_EQUAL,
    S_DQUOTE
} State;

/// 字句解析
Token *lexer(char *str) {
    Token *first_token = Token_new();
    Token *token = first_token;
    char *s = str;
    char c;
    State state = DEFAULT;

    char prev_c = 0;

    while ((c = *str++) != '\0') {
//        debug("> %c (%d)", c, c);
        char next_c = *str;

        if (state == DEFAULT) {
            if (c == ' ') {
                state = SPACE;
            } else if (is_eol(c)) {
                state = S_EOL;
            } else if (c == '$' && is_literal(next_c)) {
                state = S_DOLLAR;
            } else if (is_literal(prev_c) && c == '=' && next_c != ' ') {
                state = S_EQUAL;
            } else if (c == '\"') {
                state = S_DQUOTE;
            } else {
                // 普通の文字
                state = S_LITERAL;
            }
        }

        if (state == S_LITERAL) {
//            debug("    S_LITERAL");
            char next_next_c = *(str + 1);

            // literal ではない かつ 次に来る文字が "= " ではない
            if (!is_literal(next_c) && !(next_c == '=' && next_next_c == ' ')) {
                ull len = str - s;

                if (len == 2 && strstart(s, "if")) {
                    token = Token_insert(token, IF, NULL);

                } else if (len == 4 && strstart(s, "then")) {
                    token = Token_insert(token, THEN, NULL);

                } else if (len == 4 && strstart(s, "elif")) {
                    token = Token_insert(token, ELIF, NULL);

                } else if (len == 4 && strstart(s, "else")) {
                    token = Token_insert(token, ELSE, NULL);

                } else if (len == 2 && strstart(s, "fi")) {
                    token = Token_insert(token, FI, NULL);

                } else if (len == 3 && strstart(s, "for")) {
                    token = Token_insert(token, FOR, NULL);

                } else if (len == 2 && strstart(s, "do")) {
                    token = Token_insert(token, DO, NULL);

                } else if (len == 4 && strstart(s, "done")) {
                    token = Token_insert(token, DONE, NULL);

                } else {
                    char *substring = substr(s, str);
                    token = Token_insert(token, LITERAL, substring);
                }

                s = str;
                state = DEFAULT;
            }
        } else if (state == SPACE) {
//            debug("    SPACE");
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
        } else if (state == S_EQUAL) {
            token = Token_insert(token, EQUAL, NULL);
            s = str;

            // = が連続したら必ず S_LITERAL
            if (next_c == '=') {
                state = S_LITERAL;
            } else {
                state = DEFAULT;
            }
        } else if (state == S_DQUOTE) {
            if (next_c == '\"') {
                char *substring = substr(s + 1, str);
                token = Token_insert(token, LITERAL, substring);
                str++;
                s = str;
                state = DEFAULT;
            }
        }

        prev_c = c;
    }

    return first_token;
}