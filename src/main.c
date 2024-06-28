#include <stdio.h>
#include <string.h>
#include "cmd/cmd.h"
#include "lib/io.h"
#include "cmd/cd.h"
#include "lib/map.h"
#include "global.h"

#define MAX_LEN 256
#define MAX_ARG 10

int main() {
    char buff[MAX_LEN];

    init_global();

    while (fgets(buff, MAX_LEN, stdin) != NULL) {
        char eof;
        if ((eof = buff[strlen(buff) - 1]) != '\n') {
            error("Too long statement (max: %d)", MAX_LEN);
        }

        Command cmd = c_interprete(buff, MAX_ARG);

        c_fun fun = c_get(cmd.cmd);
        if (fun != NULL) {
            fun(cmd.argv);
        }
        break;
    }

    return 0;
}
