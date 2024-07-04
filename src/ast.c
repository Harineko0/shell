#include "stdlib.h"
#include "ast.h"
#include "lib/io.h"

int CommandExpression_run(Expression *expression) {
    CommandExpression *expr = (CommandExpression*) expression;
    debug("%s", expr->command);

    if (expr->args != NULL) {
        Literal *arg = expr->args;
        while (*arg != NULL) {
            debug("%s", *arg++);
        }
    }

    return 0;
}

void CommandExpression_free(Expression *expression) {
    CommandExpression *expr = (CommandExpression*) expression;
    Literal *args = expr->args;

    if (args != NULL) {
        Literal *last = args;
        while (*++last != NULL);
        while (last - args >= 0) {
            free(last);
            last--;
        }
        free(args);
    }

    free(expr->command);
    free(expr);
}

CommandExpression *CommandExpression_new(Literal cmd, Literal *args) {
    CommandExpression *expr = malloc(sizeof (CommandExpression));
    expr->type = E_COMMAND;
    expr->run = CommandExpression_run;
    expr->free = CommandExpression_free;
    expr->command = cmd;
    expr->args = args;
    return expr;
}

void ExpressionStatement_run(Statement *statement) {
    ExpressionStatement *state = (ExpressionStatement*) statement;
    Expression *expr = state->expr;
    if (expr != NULL) expr->run(expr);
    Statement *next = state->next;
    if (next != NULL) next->run(next);
}

void ExpressionStatement_free(Statement *statement) {
    ExpressionStatement *state = (ExpressionStatement*) statement;
    Expression *expr = state->expr;
    if (expr != NULL) expr->free(expr);
    Statement *next = state->next;
    if (next != NULL) next->free(next);
    free(state);
}

ExpressionStatement *ExpressionStatement_new(Expression *expr) {
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

Program *Program_new(Statement *state) {
    Program *prog = malloc(sizeof (Program));
    prog->state = state;
    return prog;
}

void Program_run(Program *prog) {
    Statement *state = prog->state;
    if (state != NULL) {
        state->run(state);
    }
}

int Program_free(Program *prog) {
    Statement *state = prog->state;
    if (state != NULL) {
        state->free(state);
    }
    free(prog);
    return 0;
}