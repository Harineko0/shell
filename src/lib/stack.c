#include <stdlib.h>
#include "stack.h"
#include "io.h"

Stack *s_create(int size) {
    Stack *stack = malloc(sizeof (Stack));

    if (stack == NULL) {
        error("Cannot create Stack");
        return NULL;
    }

    stack->index = 0;
    stack->size = size;
    stack->bottom = calloc(size, sizeof (void *));
    return stack;
}

void s_push(Stack *stack, void *item) {
    int index = stack->index++;
    index++;

    // 最大サイズまで格納したら古いものを上書き
    if (index >= stack->size) {
        index = 0;
    }

    stack->index = index;
    stack->bottom[index] = item;
}

void *s_pop(Stack *stack) {
    int index = stack->index;
    void *item = stack->bottom[index];
    stack->bottom[index] = NULL;

    if (index-- < 0) {
        index = stack->size - 1;
    }
    stack->index = index;

    return item;
}

void s_free(Stack *stack) {
    free(stack->bottom);
    free(stack);
}
