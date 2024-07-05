#ifndef AST_H
#define AST_H

typedef char * Literal;
typedef struct execute_expression ExecuteExpression;

typedef enum {
    YE_LITERAL,
    YE_RUN,
    YE_VARIABLE,
} YieldExpressionType;

typedef struct yield_expression YieldExpression;
typedef Literal (*YieldExpressionRun)(YieldExpression *);
typedef void (*YieldExpressionFree)(YieldExpression *);
struct yield_expression {
    YieldExpressionType type;
    YieldExpressionRun run;
    YieldExpressionFree free;
};

typedef struct {
    YieldExpressionType type;
    YieldExpressionRun run;
    YieldExpressionFree free;

    Literal literal;
} LiteralExpression;

typedef struct {
    YieldExpressionType type;
    YieldExpressionRun run;
    YieldExpressionFree free;

    ExecuteExpression *expr;
} RunExpression;

typedef struct {
    YieldExpressionType type;
    YieldExpressionRun run;
    YieldExpressionFree free;

    Literal symbol;
} VariableExpression;

typedef enum {
    EE_COMMAND,
    EE_VARIABLE,
} ExecuteExpressionType;

typedef struct execute_expression ExecuteExpression;
typedef int (*ExecuteExpressionRun)(ExecuteExpression*);
typedef void (*ExecuteExpressionFree)(ExecuteExpression*);
struct execute_expression {
    ExecuteExpressionType type;
    ExecuteExpressionRun run;
    ExecuteExpressionFree free;
};

typedef struct {
    ExecuteExpressionType type;
    ExecuteExpressionRun run;
    ExecuteExpressionFree free;

    YieldExpression *command;
    YieldExpression **args;
    // [[ xxx ]] の場合は command="test", args=xxx になる
} CommandExpression;

typedef struct {
    ExecuteExpressionType type;
    ExecuteExpressionRun run;
    ExecuteExpressionFree free;

    Literal symbol;
    YieldExpression *value;
} AssignExpression;

typedef enum {
    S_IF,
    S_FOR,
    S_FUNC,
    S_EXP
} StatementType;

typedef struct statement Statement;
typedef void (*StatementRun)(Statement*);
typedef void (*StatementFree)(Statement*);
struct statement {
    StatementType type;
    StatementRun run;
    StatementFree free;
    Statement *next;
};

typedef struct {
    StatementType type;
    StatementRun run;
    StatementFree free;
    Statement *next;

    ExecuteExpression *expr; // CommandExpression or VariableExpression
} ExpressionStatement;

typedef struct {
    StatementType type;
    StatementRun run;
    StatementFree free;
    Statement *next;

    ExecuteExpression *condition;
    Statement *ifs; // if statement
    Statement *els; // else statement
} IfStatement;

typedef struct {
    Statement *state;
} Program;

LiteralExpression *LiteralExpression_new(Literal literal);

CommandExpression *CommandExpression_new(YieldExpression *cmd, YieldExpression **args);
AssignExpression *AssignExpression_new(Literal symbol, YieldExpression *value);

ExpressionStatement *ExpressionStatement_new(ExecuteExpression *expr);
Statement *Statement_append(Statement *prev, Statement *new);

Program *Program_new(Statement *state);
void Program_run(Program *prog);
int Program_free(Program *prog);

#endif