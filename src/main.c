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

    char **args = calloc(3, sizeof (char *));
    *args = strdup("ab");
    *(args+1) = strdup("cd");
    char *cmd1 = strdup("cat");
    char *cmd2 = strdup("echo");

    CommandExpression *expr = CommandExpression_new(cmd1, args);
    CommandExpression *expr2 = CommandExpression_new(cmd2, NULL);
    ExpressionStatement *state = ExpressionStatement_new((Expression *) expr);
    ExpressionStatement *state2 = ExpressionStatement_new((Expression *) expr2);
    state->next = (Statement *) state2;
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
