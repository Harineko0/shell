#include <stdio.h>
#include <string.h>
#include "cmd.h"
#include "lib/io.h"
#include "lib/map.h"
#include "lib/str.h"
#include "global.h"
#include "lexer.h"
#include "parser.h"

#define MAX_LEN 256

typedef unsigned long long ull;

int main() {
    char buff[MAX_LEN];

    init_global();

    while (true) {
        fputs(cwd, stdout);
        fputs(">", stdout);

        fgets(buff, MAX_LEN, stdin);

        Token *token = lexer(buff), *t = token;
        while (t != NULL) {
            debug("  token = %s", Token_to_string(t));
            t = t->next;
        }
        Program *prog = parser(token);
        Token_free(token);

        Program_run(prog);
//        Program_free(prog);

        continue;
        ull len = strlen(buff);

        if (len <= 1) {
            continue;
        }

        if (strstart(buff, "exit")) {
            break;
        }

        if (buff[len - 1] != '\n') {
            error("Too long state (size: %d)", MAX_LEN);
        }

        char *newline = strchr(buff, '\n');
        if (newline) *newline = '\0';

        c_execute(buff);
    }

    return 0;
}
