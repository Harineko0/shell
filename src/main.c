#include <stdio.h>
#include <string.h>
#include "cmd.h"
#include "lib/io.h"
#include "cmd/cd.h"
#include "lib/map.h"
#include "global.h"
#include "lib/str.h"
#include "lexer.h"
#include "ast.h"

#define MAX_LEN 256

typedef unsigned long long ull;

int main() {
    char buff[MAX_LEN];

    init_global();

//    char *args[] = {"ab", "cd", NULL};
    char **args = calloc(3, sizeof (char *));
    char *arg1 = calloc(3, sizeof (char));
    *arg1 = 'a';
    *(arg1+1) = 'b';
    *args = arg1;
    char *arg2 = calloc(3, sizeof (char));
    *arg2 = 'c';
    *(arg2+1) = 'd';
    *(args+1) = arg2;
    *(args+2) = NULL;

    CommandExpression *expr = CommandExpression_new("cat", args);
    ExpressionStatement *state = ExpressionStatement_new((Expression *) expr);
    Program *prog = Program_new((Statement *) state);
    Program_run(prog);
    Program_free(prog);

    while (true) {
        fputs(cwd, stdout);
        fputs(">", stdout);

        fgets(buff, MAX_LEN, stdin);

        Token *token = lexer(buff);
        while (token != NULL) {
            debug("  token = %s", Token_to_string(token));
            token = token->next;
        }

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
