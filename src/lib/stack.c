#include <stdlib.h>
#include "stack.h"
#include "io.h"

Stack *s_create(int size) {
    Stack *stack = malloc(sizeof (Stack));

    if (stack == NULL) {
        error("Cannot create Stack");
        return NULL;
    }

    stack->top = 0;
    stack->bottom = 0;
    stack->size = size;
    stack->items = calloc(size, sizeof (void *));
    return stack;
}

void s_push(Stack *stack, void *item) {
    int top = stack->top;
    stack->items[top] = item;
    top++;

    // 最大サイズまで格納したら古いものを上書き
    if (top >= stack->size) {
        top = 0;
    }

    if (top <= stack->bottom) {
        stack->bottom++;
    }

    stack->top = top;
}

void *s_pop(Stack *stack) {
    int index = stack->top;
    void *item = stack->items[index];
    stack->items[index] = NULL;

    if (index-- < 0) {
        index = stack->size - 1;
    }
    stack->top = index;

    return item;
}

void s_free(Stack *stack) {
    free(stack->items);
    free(stack);
}
