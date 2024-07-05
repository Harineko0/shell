#include <string.h>
#include "../global.h"

int pushd(char **argv) {
    char *dir = strdup(cwd);
    Stack_push(dir_stack, dir);
    return 0;
}
