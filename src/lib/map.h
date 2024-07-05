#ifndef MAP_H
#define MAP_H

/* https://zenn.dev/derbuihan/articles/acc5c3d4deab29 */
#include <stdbool.h>

typedef struct Entry Entry;
struct Entry {
    char *key;
    void *value;
    Entry *next;
};

typedef struct {
    Entry **entries;
    int size;
} Map;

Map *Map_new(int size);
void Map_insert(const Map *map, const char *key, void *value);
void *Map_get(const Map *map, const char *key);
int Map_delete(const Map *map, const char *key, bool free_val);
void Map_free(Map *map, bool free_val);

#endif