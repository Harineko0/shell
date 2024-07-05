#include "stdlib.h"
#include "../ast.h"
#include "../lib/io.h"

Program *Program_new(Statement *state) {
    Program *prog = malloc(sizeof (Program));
    prog->state = state;
    return prog;
}

void Program_run(Program *prog) {
    Statement *state = prog->state;
    if (state != NULL) {
        state->run(state);
    }
}

int Program_free(Program *prog) {
    Statement *state = prog->state;
    if (state != NULL) {
        state->free(state);
    }
    free(prog);
    return 0;
}
