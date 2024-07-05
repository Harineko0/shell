typedef struct {
    void **items;
    int top;
    int bottom;
    int size;
} Stack;

Stack *Stack_new(int size);
void Stack_push(Stack *stack, void *item);
void *Stack_pop(Stack *stack);
void *Stack_top(Stack *stack);
void Stack_free(Stack *stack);
