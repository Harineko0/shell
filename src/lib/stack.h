typedef struct {
    void **items;
    int top;
    int bottom;
    int size;
} Stack;

Stack *s_create(int size);
void s_push(Stack *stack, void *item);
void *s_pop(Stack *stack);
void *s_top(Stack *stack);
void s_free(Stack *stack);
