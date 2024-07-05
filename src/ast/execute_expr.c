#include <stdlib.h>
#include "../ast.h"
#include "../lib/io.h"

int CommandExpression_run(ExecuteExpression *expression) {
    CommandExpression *expr = (CommandExpression*) expression;
    Literal cmd = expr->command->run(expr->command);
    debug("CommandExpression_run: command = %s", cmd);

    YieldExpression **args = expr->args;
    YieldExpression *arg;

    while ((arg = *args++) != NULL) {
        debug("CommandExpression_run: args = %s", arg->run(arg));
    }

    return 0;
}

void CommandExpression_free(ExecuteExpression *expression) {
    CommandExpression *expr = (CommandExpression*) expression;

    YieldExpression **last = expr->args;
    YieldExpression **first = expr->args;
    YieldExpression *arg;
    while ((arg = *last++) != NULL);
    while (--last - first >= 0) {
        arg = *last;
        if (arg == 0) continue;
        arg->free(arg);
    }

    expr->command->free(expr->command);
    free(expr);
}

CommandExpression *CommandExpression_new(YieldExpression *cmd, YieldExpression **args) {
    CommandExpression *expr = malloc(sizeof (CommandExpression));
    expr->type = EE_COMMAND;
    expr->run = CommandExpression_run;
    expr->free = CommandExpression_free;
    expr->command = cmd;
    expr->args = args;
    return expr;
}

int AssignExpression_run(ExecuteExpression *expression) {
    AssignExpression *expr = (AssignExpression*) expression;
    debug("AssignExpression_run: %s = %s", expr->symbol, expr->value->run(expr->value));
    return 0;
}

void AssignExpression_free(ExecuteExpression *expression) {
    AssignExpression *expr = (AssignExpression*) expression;

    free(expr->symbol);
    expr->value->free(expr->value);
    free(expr);
}

AssignExpression *AssignExpression_new(Literal symbol, YieldExpression *value) {
    AssignExpression *expr = malloc(sizeof (AssignExpression));
    expr->type = EE_VARIABLE;
    expr->run = AssignExpression_run;
    expr->free = AssignExpression_free;
    expr->symbol = symbol;
    expr->value = value;
    return expr;
}
