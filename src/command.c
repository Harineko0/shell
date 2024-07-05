#include "commands.h"

CommandMap *commandMap;

void CommandMap_init(int size) {
    Map *map = Map_new(size);

    Map_insert(map, "cd", cd);
    Map_insert(map, "pushd", pushd);
    Map_insert(map, "dirs", dirs);
    Map_insert(map, "popd", popd);
    Map_insert(map, "history", history);

    commandMap = (CommandMap *) map;
}

Command_run CommandMap_get(char * key) {
    return Map_get((const Map *) commandMap, key);
}

void CommandMap_free() {
    Map_free((Map *) commandMap, false);
}