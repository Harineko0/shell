typedef struct {
    void **bottom;
    int index;
    int size;
} Stack;

Stack *s_create(int size);
void s_push(Stack *stack, void *item);
void *s_pop(Stack *stack);
void s_free(Stack *stack);
