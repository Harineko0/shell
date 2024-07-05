#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "token.h"
#include "ast.h"
#include "lib/io.h"

#define MAX_ARG 64

ExpressionStatement *parse_expr_state(Token **token);
CommandExpression *parse_cmd_expr(Token **token);
AssignExpression *parse_assign_expr(Token **token);
YieldExpression *parse_yield_expr(Token **token);

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

        // state が初期化前
        if (state == NULL) {
            state = s;
        }
    }

    return Program_new(state);
}

ExpressionStatement *parse_expr_state(Token **token) {
    Token *next = (*token)->next;
    ExecuteExpression *expr;

    if (next != NULL && next->type == EQUAL) {
        expr = (ExecuteExpression *) parse_assign_expr(token);
    } else {
        expr = (ExecuteExpression *) parse_cmd_expr(token);
    }

    return ExpressionStatement_new(expr);
}

CommandExpression *parse_cmd_expr(Token **token) {
    Token *t = *token;
    if (t->string == NULL) {
        error("Token.string is NULL");
        exit(1);
    }
    YieldExpression *cmd = parse_yield_expr(token);

    YieldExpression *buf[MAX_ARG];\
    int bufI = 0;
    while ((*token)->type == LITERAL) {
        if (bufI >= MAX_ARG) {
            error("Too many arguments. (max 64)\n");
            exit(1);
        }
        buf[bufI++] = parse_yield_expr(token);
    }

    YieldExpression **args = calloc(bufI + 1, sizeof (YieldExpression *));
    YieldExpression **a = args, **b = buf;

    while ((a - args) < bufI) {
        *a++ = *b++;
//        debug("  CommandExpression.arg: %s", *(a - 1));
    }

    return CommandExpression_new(cmd, args);
}

AssignExpression *parse_assign_expr(Token **token) {
    Token *first = *token;
    *token = (*token)->next;
    Token *second = *token;
    if (second == NULL) {
        error("parse_assign_expr(): second token is NULL");
        exit(1);
    }
    *token = (*token)->next;
    Token *third = *token;
    *token = (*token)->next;

    if (first->type == LITERAL && second->type == EQUAL && third->type == LITERAL) {
        YieldExpression *value = parse_yield_expr(token);
        return AssignExpression_new(strdup(first->string), value);
    }

    fprintf(stderr, "Invalid token: %s=%s", first->string, third->string);
    return NULL;
}

YieldExpression *parse_yield_expr(Token **token) {
    Token *t = *token;

    if (t->type == LITERAL) {
        *token = t->next;
        return (YieldExpression *) LiteralExpression_new(t->string);
    }

//    if (t->type == DOLLAR) {
//        return
//    }
    return NULL;
}