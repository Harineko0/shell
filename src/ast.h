#ifndef AST_H
#define AST_H

typedef char * Literal;

typedef enum {
    E_COMMAND,
    E_VARIABLE,
} ExpressionType;

typedef struct expression Expression;
typedef int (*ExpressionRun)(Expression*);
typedef void (*ExpressionFree)(Expression*);
struct expression {
    ExpressionType type;
    ExpressionRun run;
    ExpressionFree free;
};

typedef struct {
    ExpressionType type;
    ExpressionRun run;
    ExpressionFree free;

    Literal command;
    Literal *args;
    // [[ xxx ]] の場合は command="test", args=xxx になる
} CommandExpression;

typedef struct {
    ExpressionType type;
    ExpressionRun run;
    ExpressionFree free;

    Literal symbol;
    Literal value;
} VariableExpression;

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

    Expression *expr;
} ExpressionStatement;

typedef struct {
    StatementType type;
    StatementRun run;
    StatementFree free;
    Statement *next;

    Expression *condition;
    Statement *ifs; // if statement
    Statement *els; // else statement
} IfStatement;

typedef struct {
    Statement *state;
} Program;


CommandExpression *CommandExpression_new(Literal cmd, Literal *args);

ExpressionStatement *ExpressionStatement_new(Expression *expr);
Statement *Statement_append(Statement *prev, Statement *new);

Program *Program_new(Statement *state);
void Program_run(Program *prog);
int Program_free(Program *prog);

#endif