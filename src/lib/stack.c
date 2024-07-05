#include <stdlib.h>
#include "stack.h"
#include "io.h"

Stack *Stack_new(int size) {
    Stack *stack = malloc(sizeof (Stack));

    if (stack == NULL) {
        error("Cannot instantiate Stack");
    }

    stack->top = 0;
    stack->bottom = 0;
    stack->size = size;
    stack->items = calloc(size, sizeof (void *));
    return stack;
}

void Stack_push(Stack *stack, void *item) {
    int top = (stack->top + 1) % stack->size;
    stack->items[top] = item;
    if (top <= stack->bottom) {
        stack->bottom++;
    }
    stack->top = top;
}

void *Stack_pop(Stack *stack) {
    int top = stack->top;

    if (top == stack->bottom) return NULL;

    void *item = stack->items[top];
    stack->items[top] = NULL;
    stack->top = (top - 1) % stack->size;

    return item;
}

void *Stack_top(Stack *stack) {
    return stack->items[stack->top - 1];
}

void Stack_free(Stack *stack) {
    free(stack->items);
    free(stack);
}
