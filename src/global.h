#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdlib.h>
#include "lib/stack.h"
#include "lib/map.h"

/// current working directory
extern char *cwd;

extern Stack *dir_stack;
extern Stack *cmd_stack;
extern Map *var_map;

void init_global();

#endif