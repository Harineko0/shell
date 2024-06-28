#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmd.h"
#include "../lib/map.h"
#include "cd.h"
#define CMD_SIZE 100

typedef unsigned long long ull;

static HashMap *map = NULL;

void init_map() {
    map = h_create(CMD_SIZE);

    h_insert(map, "cd", cd);
}

c_fun c_get(char *cmd) {
    if (map == NULL) {
        init_map();
    }

    return h_get(map, cmd);
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
