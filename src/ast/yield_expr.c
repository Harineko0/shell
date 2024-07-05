#include <stdlib.h>
#include <string.h>
#include "../ast.h"
#include "../lib/io.h"
#include "../global.h"

Literal LiteralExpression_run(YieldExpression *expression) {
    LiteralExpression *expr = (LiteralExpression *)expression;
    return expr->literal;
}

void LiteralExpression_free(YieldExpression *expression) {
    LiteralExpression *expr = (LiteralExpression *)expression;
    debug("LiteralExpression_free: %s", expr->literal);
    free(expr->literal);
    free(expr);
}

LiteralExpression *LiteralExpression_new(Literal literal) {
    LiteralExpression *expr = malloc(sizeof (LiteralExpression));
    expr->type = YE_LITERAL;
    expr->run = LiteralExpression_run;
    expr->free = LiteralExpression_free;
    expr->literal = strdup(literal);
    return expr;
}

Literal VariableExpression_run(YieldExpression *expression) {
    VariableExpression *expr = (VariableExpression *) expression;
    Literal value = Map_get(var_map, expr->symbol);

    if (value == NULL) return "";
    return value;
}

void VariableExpression_free(YieldExpression *expression) {
    VariableExpression *expr = (VariableExpression *)expression;
    debug("VariableExpression_free: %s", expr->symbol);
    free(expr->symbol);
    free(expr);
}

VariableExpression *VariableExpression_new(Literal symbol) {
    VariableExpression *expr = malloc(sizeof (VariableExpression));
    expr->type = YE_VARIABLE;
    expr->run = VariableExpression_run;
    expr->free = VariableExpression_free;
    expr->symbol = symbol;
    return expr;
}