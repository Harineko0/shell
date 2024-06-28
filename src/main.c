#include <stdio.h>
#include <string.h>
#include "cmd.h"
#include "io.h"
#include "cd.h"
#include "map.h"

#define MAX_LEN 256
#define MAX_ARG 10

int main() {
    char buff[MAX_LEN];

    while (fgets(buff, MAX_LEN, stdin) != NULL) {
        if (buff[strlen(buff) - 1] != '\n') {
            error("Too long statement (max: %d)", MAX_LEN);
        }

        Command cmd = c_interprete(buff, MAX_ARG);
        puts(cmd.cmd);

        int i = 0;
        while (cmd.argv[i] != NULL) {
            puts(cmd.argv[i++]);
        }

        c_fun fun = c_get(cmd.cmd);
        if (fun != NULL) {
            fun(cmd.argv);
        }
        break;
    }

    return 0;
}
