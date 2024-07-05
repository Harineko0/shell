#include <stdio.h>
#include "../global.h"
#include "../commands.h"

int history(char **argv) {
    int count = 0;
    int size = cmd_stack->size;
    int top = cmd_stack->top;
    int bottom = dir_stack->bottom;

    for (int i = bottom; i != top; i = (i + 1) % size) {
        char *item = cmd_stack->items[i];
        if (item != NULL)
            printf(" %d %s\n", count++, item);
    }

    return 0;
}
