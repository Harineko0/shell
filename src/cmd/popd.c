#include "../global.h"

int popd(char **argv) {
    char *dir = s_pop(dir_stack);

    if (dir == NULL) {
        return 0;
    }

    char *old = cwd;
    cwd = dir;
    free(old);
    return 0;
}
