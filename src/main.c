#include <string.h>
#include <stdio.h>
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

        ull len = strlen(buff);
        buff[len - 1] = '\0';
        Stack_push(cmd_stack, strdup(buff));
        buff[len - 1] = '\n';

        Token *token = lexer(buff), *t = token;
        while (t != NULL) {
            debug("  token = %s", Token_to_string(t));
            t = t->next;
        }
        Program *prog = parser(token);
        Token_free(token);

        Program_run(prog);
//        Program_free(prog);
    }

    return 0;
}
