#include <string.h>
#include "global.h"

char *cwd;

void init_global() {
//    cwd = strdup(getenv("HOME"));
    cwd = "/c/Users/harin"; // TODO: getenv("HOME");
}
