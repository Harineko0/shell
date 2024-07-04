#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdlib.h>
#include "lib/stack.h"

/// current working directory
extern char *cwd;
extern Stack *dir_stack;
extern Stack *cmd_stack;

void init_global();

#endif