#include <string.h>
#include <stdlib.h>
#include "../ast.h"
#include "../lib/io.h"
#include "../global.h"
#include "../commands.h"
#define MAX_ARG 256

int CommandExpression_run(ExecuteExpression *expression) {
    CommandExpression *expr = (CommandExpression*) expression;
    Literal cmd = expr->command->run(expr->command);
    debug("try to get runner");
    Command_run runner = CommandMap_get(cmd);
    debug("got runner %d", runner);

    if (runner == NULL) {
        return 1;
    }

    Literal args_buf[256], *b = args_buf;

    YieldExpression **args = expr->args;
    YieldExpression *arg;

    while ((arg = *args++) != NULL) {
        *b++ = arg->run(arg);
    }

    b = NULL;

    runner(args_buf);
//    debug("CommandExpression_run: command = %s", cmd);

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
    Literal key = expr->symbol;
    Literal value = expr->value->run(expr->value);
    Map_insert(var_map, key, strdup(value));
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
