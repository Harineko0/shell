#include <stdio.h>
#include "../global.h"

int dirs(char **argv) {
    int count = 0;
    int index = dir_stack->index;
    char *top = dir_stack->bottom[index];

    while (top != NULL) {
        printf(" %d %s\n", count++, top);

        index--;
        if (index < 0) {
            index = dir_stack->size - 1;
        }
        top = dir_stack->bottom[index];
    }

    return 0;
}
