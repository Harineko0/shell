#include <string.h>
#include "global.h"

char *cwd;
Stack *dir_stack;

void init_global() {
//    cwd = strdup(getenv("HOME"));
    cwd = "/c/Users/harin"; // TODO: getenv("HOME");

    dir_stack = s_create(10);
}
