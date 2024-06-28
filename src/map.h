/* https://zenn.dev/derbuihan/articles/acc5c3d4deab29 */

typedef struct Entry Entry;
struct Entry {
    char *key;
    void *value;
    Entry *next;
};

typedef struct {
    Entry **entries;
    int size;
} HashMap;

HashMap *h_create(int size);
void h_insert(const HashMap *map, const char *key, void *value);
void *h_get(const HashMap *map, const char *key);
int h_delete(const HashMap *map, const char *key, bool free_val);
void h_free(HashMap *map, bool free_val);
