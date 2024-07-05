#ifndef COMMANDS_H
#define COMMANDS_H

#include "lib/map.h"

int cd(char **argv);
int dirs(char **argv);
/// !! (exclamation exclamation)
int ex(char *cmd);
int history(char **argv);
int popd(char **argv);
int pushd(char **argv);

typedef Map CommandMap;

typedef int (*Command_run)(char**);
void CommandMap_init(int size);
Command_run CommandMap_get(char *key);
void CommandMap_free();

#endif