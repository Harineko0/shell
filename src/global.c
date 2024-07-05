#include <string.h>
#include "global.h"

char *cwd;
Stack *dir_stack;
Stack *cmd_stack;

void init_global() {
//    cwd = strdup(getenv("HOME"));
    cwd = "/c/Users/harin"; // TODO: getenv("HOME");

    dir_stack = Stack_new(10);
    cmd_stack = Stack_new(32);
}
