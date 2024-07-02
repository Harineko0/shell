#include "../global.h"
#include "../cmd.h"
#include "../lib/io.h"

int exex(char **argv) {
    char *cmd = s_top(cmd_stack);
    int result = c_execute(cmd);
    return result;
}
