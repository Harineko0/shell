#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "map.h"

typedef unsigned int uint;

HashMap *h_create(int size) {
    HashMap *hashmap = malloc(sizeof(HashMap));
    hashmap->size = size;

    hashmap->entries = malloc(sizeof(Entry) * size);
    for (int i = 0; i < size; i++) {
        hashmap->entries[i] = NULL;
    }

    return hashmap;
}

uint hash(const char *key, const int size) {
    uint hash = 0;
    int i = 0;

    while (key[i++] != '\0') {
        hash = 31 * hash + key[i];
    }

    return hash % size;
}

void h_insert(const HashMap *map, const char *key, void *value) {
    uint index = hash(key, map->size);

    Entry *entry = map->entries[index];

    // ハッシュが重複していたら next に入れる
    while (entry != NULL) {
        // キーが重複していたら, value を上書きする
        if (strcmp(entry->key, key) == 0) {
            free(entry->value);
            // FIXME: 関数ポインタの場合は複製する
            entry->value = value;
            return;
        }
        entry = entry->next;
    }

    entry = malloc(sizeof(Entry));
    entry->key = strdup(key);
    // FIXME: 関数ポインタの場合は複製する
    entry->value = value;
    entry->next = map->entries[index];

    map->entries[index] = entry;
}

void *h_get(const HashMap *map, const char *key) {
    uint index = hash(key, map->size);

    Entry *entry = map->entries[index];

    if (entry == NULL) return NULL;

    while (strcmp(entry->key, key) != 0 && entry != NULL) {
        entry = entry->next;
    }

    return entry->value;
}

int h_delete(const HashMap *map, const char *key, bool free_val) {
    uint index = hash(key, map->size);
    Entry *entry = map->entries[index];

    // find the entry and its predecessor
    Entry *pred = NULL;
    while (entry != NULL && strcmp(entry->key, key) != 0) {
        pred = entry;
        entry = entry->next;
    }

    if (entry == NULL) return 1;
    if (pred == NULL) {
        map->entries[index] = entry->next;
    } else {
        pred->next = entry->next;
    }

    free(entry->key);
    if (free_val) {
        free(entry->value);
    }
    free(entry);

    return 0;
}

void h_free(HashMap *map, bool free_val) {
    // free entries
    int i = 0;

    while (i++ < map->size) {
        Entry *entry = map->entries[i];

        while (entry != NULL) {
            Entry *next = entry->next;
            free(entry->key);
            if (free_val) {
                free(entry->value);
            }
            free(entry);
            entry = next;
        }
    }

    // free hashmap
    free(map->entries);
    free(map);
}
