#include <string.h>
#include "../global.h"
#include "../lib/io.h"
#include "../lib/str.h"
#include "../commands.h"

typedef unsigned long long ull;

int ex(char *cmd) {
    debug("%s", cmd);
    strreplace(cmd, ' ', '\0');
    debug("%s", cmd);
    // FIXME: arg がない場合に 45 行目でセグフォが起きる
    char *arg = cmd + strlen(cmd);

    if (cmd[1] == '\0') {
        return 0;
    }

    char *restored;

    if (cmd[1] == '!') {
        // !!
        restored = Stack_top(cmd_stack);
    } else if (strisnum(cmd + 1)) {
        // !n
        int n = atoi(cmd + 1);
        restored = cmd_stack->items[(cmd_stack->bottom + n) % cmd_stack->size];
    } else if (cmd[1] == '-' && cmd[2] != '\0' && strisnum(cmd + 2)) {
        // !-n
        int n = atoi(cmd + 2);
        restored = cmd_stack->items[(cmd_stack->top - n) % cmd_stack->size];
    } else {
        return 0;
    }

    char *merged = calloc(strlen(restored) + strlen(arg) + 1, sizeof (char));
    *merged = '\0';

    debug("%s", merged);
    strcat(merged, restored);
    debug("%s", merged);
    strcat(merged, " ");
    debug("%s", merged);
    if (*arg != '\0') strcat(merged, arg);
    debug("%s", merged);
    
//    int result = C(merged);
//    return result;
    return 0;
}
