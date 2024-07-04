#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "token.h"
#include "ast.h"
#include "lib/io.h"

#define MAX_ARG 64

ExpressionStatement *parse_expr_state(Token **token);
CommandExpression *parse_cmd_expr(Token **token);
VariableExpression *parse_var_expr(Token **token);

/// 構文解析
Program *parser(Token *token) {
    Statement *state = NULL, *s = state;
    Token *t = token;

    while (t != NULL) {
        TokenType type = t->type;

        if (type == LITERAL) {
            ExpressionStatement *expr_state = parse_expr_state(&t);
            s = Statement_append(s, (Statement *) expr_state);
        } else if (type == EOL) {
            t = t->next;
        }

        if (state == NULL) {
            state = s;
        }
    }

    return Program_new(state);
}

ExpressionStatement *parse_expr_state(Token **token) {
    Token *next = (*token)->next;
    Expression *expr;

    if (next != NULL && next->type == EQUAL) {
        expr = (Expression *) parse_var_expr(token);
    } else {
        expr = (Expression *) parse_cmd_expr(token);
    }

    return ExpressionStatement_new(expr);
}

CommandExpression *parse_cmd_expr(Token **token) {
    Token *t = *token;
    if (t->string == NULL) return NULL;
    Literal cmd = strdup(t->string);
    *token = t->next;

    Literal buf[MAX_ARG];
    int bufI = 0;

    while ((t = *token)->type == LITERAL) {
        if (bufI >= MAX_ARG) {
            fputs("Too many arguments. (max 64)\n", stdout);
            exit(1);
        }
        buf[bufI++] = strdup(t->string);
        *token = t->next;
    }

    Literal *args = calloc(bufI + 1, sizeof (Literal));
    Literal *a = args, *b = buf;

//    debug("  CommandExpression.cmd: %s", cmd);

    while ((a - args) < bufI) {
        *a++ = *b++;
//        debug("  CommandExpression.arg: %s", *(a - 1));
    }

    return CommandExpression_new(cmd, args);
}

VariableExpression *parse_var_expr(Token **token) {
    return NULL;
}
