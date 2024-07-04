typedef char * Literal;

typedef enum {
    COMMAND,
    VARIABLE,
} ExpressionType;

typedef struct expression Expression;
typedef int (*ExpressionRun)(Expression);
typedef int (*ExpressionFree)(Expression);
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
    IF,
    FOR,
    FUNC,
    EXP
} StatementType;

typedef struct statement Statement;
typedef void (*StatementRun)(Statement);
typedef int (*StatementFree)(Statement);
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

    Expression *expression;
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
    Statement *statement;
} Program;
