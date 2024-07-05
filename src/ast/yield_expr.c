#include <stdlib.h>
#include <string.h>
#include "../ast.h"
#include "../lib/io.h"

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
