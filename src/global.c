#include "global.h"
#include "commands.h"

char *cwd;
Stack *dir_stack;
Stack *cmd_stack;
Map *var_map;

void init_global() {
//    cwd = strdup(getenv("HOME"));
    cwd = "/c/Users/harin"; // TODO: getenv("HOME");

    dir_stack = Stack_new(10);
    cmd_stack = Stack_new(32);
    var_map = Map_new(32);
    CommandMap_init(32);
}
