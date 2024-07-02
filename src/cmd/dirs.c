#include <stdio.h>
#include "../global.h"

int dirs(char **argv) {
    int count = 0;
    int size = dir_stack->size;
    int top = dir_stack->top - 1;
    char *item = dir_stack->items[top];

    while (item != NULL && count < size) {
        printf(" %d %s\n", count++, item);

        top--;
        if (top < 0) {
            top = size - 1;
        }
        item = dir_stack->items[top];
    }

    return 0;
}
