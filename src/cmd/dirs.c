#include <stdio.h>
#include "../global.h"
#include "../commands.h"

int dirs(char **argv) {
    int count = 0;
    int size = dir_stack->size;
    int top = dir_stack->top;
    int bottom = dir_stack->bottom;

    for (int i = top; i != bottom; i = (i - 1) % size) {
        char *item = dir_stack->items[i];
        printf(" %d %s\n", count++, item);
    }

    return 0;
}
