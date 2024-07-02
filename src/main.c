#include <stdio.h>
#include <string.h>
#include "cmd/cmd.h"
#include "lib/io.h"
#include "cmd/cd.h"
#include "lib/map.h"
#include "global.h"

#define MAX_LEN 256
#define MAX_ARG 10

typedef unsigned long long ull;

int main() {
    char buff[MAX_LEN];

    init_global();

    fputs(cwd, stdout);
    fputs(">", stdout);
    while (fgets(buff, MAX_LEN, stdin) != NULL) {
        ull len = strlen(buff);
        if (buff[len - 1] != '\n') {
            error("Too long statement (size: %d)", MAX_LEN);
        }

        char *newline = strchr(buff, '\n');
        if (newline) *newline = '\0';

        Command cmd = c_interprete(buff, MAX_ARG);

        c_fun fun = c_get(cmd.cmd);
        if (fun != NULL) {
            fun(cmd.argv);
        }

        fputs(cwd, stdout);
        fputs(">", stdout);
    }

    return 0;
}
