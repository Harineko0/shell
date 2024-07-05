#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmd.h"
#include "lib/map.h"
#include "cmd/cd.h"
#include "cmd/pushd.h"
#include "cmd/dirs.h"
#include "cmd/popd.h"
#include "cmd/history.h"
#include "global.h"
#include "lib/io.h"
#include "cmd/ex.h"

#define CMD_SIZE 100
#define MAX_ARG 10

typedef unsigned long long ull;

static Map *map = NULL;

void init_map() {
    map = Map_new(CMD_SIZE);

    Map_insert(map, "cd", cd);
    Map_insert(map, "pushd", pushd);
    Map_insert(map, "dirs", dirs);
    Map_insert(map, "popd", popd);
    Map_insert(map, "history", history);
}

int c_execute(char *cmd) {
    if (cmd[0] == '!') {
        return ex(cmd);
    }

    Stack_push(cmd_stack, strdup(cmd));
    Command command = c_interprete(cmd, MAX_ARG);

    c_fun fun = c_get(command.cmd);
    if (fun == NULL) {
        error("Command not found: %s", cmd);
        return 1;
    }

    return fun(command.argv);
}

c_fun c_get(char *cmd) {
    if (map == NULL) {
        init_map();
    }

    return Map_get(map, cmd);
}

Command c_interprete(char *input, int argc) {
    Command cmd;
    cmd.cmd = strtok(input, " ");

    cmd.argv = malloc((sizeof (void*)) * argc);
    int i = 0;
    while ((cmd.argv[i++] = strtok(NULL, " ")) != NULL){
        if (i >= argc) {
            fprintf(stderr, "Too many arguments.");
            break;
        }
    }
    return cmd;
}
