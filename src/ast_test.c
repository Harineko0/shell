//#include <string.h>
//#include <stdlib.h>
//#include "ast.h"
//
//void test_new_free() {
//    char **args = calloc(3, sizeof (char *));
//    *args = strdup("ab");
//    *(args+1) = strdup("cd");
//    char *cmd1 = strdup("cat");
//    char *cmd2 = strdup("echo");
//
//    CommandExpression *expr = CommandExpression_new(cmd1, args);
//    CommandExpression *expr2 = CommandExpression_new(cmd2, NULL);
//    ExpressionStatement *state = ExpressionStatement_new((Expression *) expr);
//    ExpressionStatement *state2 = ExpressionStatement_new((Expression *) expr2);
//    state->next = (Statement *) state2;
//    Program *prog = Program_new((Statement *) state);
//    Program_run(prog);
//    Program_free(prog);
//}