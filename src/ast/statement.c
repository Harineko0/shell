#include <stdlib.h>
#include "../ast.h"
#include "../lib/io.h"

void ExpressionStatement_run(Statement *statement) {
    ExpressionStatement *state = (ExpressionStatement*) statement;
    ExecuteExpression *expr = state->expr;
    if (expr != NULL) expr->run(expr);
    Statement *next = state->next;
    if (next != NULL) next->run(next);
}

void ExpressionStatement_free(Statement *statement) {
    ExpressionStatement *state = (ExpressionStatement*) statement;
    ExecuteExpression *expr = state->expr;
    if (expr != NULL) expr->free(expr);
    Statement *next = state->next;
    if (next != NULL) next->free(next);
    free(state);
}

ExpressionStatement *ExpressionStatement_new(ExecuteExpression *expr) {
    ExpressionStatement *state = malloc(sizeof (ExpressionStatement));
    state->type = S_EXP;
    state->run = ExpressionStatement_run;
    state->free = ExpressionStatement_free;
    state->next = NULL;
    state->expr = expr;
    return state;
}

Statement *Statement_append(Statement *prev, Statement *new) {
    if (prev != NULL) prev->next = new;
    return new;
}