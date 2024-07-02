#include <stdio.h>
#include "history.h"
#include "../global.h"

int history(char **argv) {
    int count = 0;
    int size = cmd_stack->size;
    int bottom = cmd_stack->bottom;
    char *item = cmd_stack->items[bottom];

    while (item != NULL && count < size) {
        printf(" %d %s\n", count++, item);

        bottom++;
        if (bottom >= size) {
            bottom = 0;
        }

        item = cmd_stack->items[bottom];
    }

    return 0;
}
