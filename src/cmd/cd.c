#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../global.h"
#include "../lib/io.h"

typedef unsigned long long ull;

char *path_resolve(char* a, char *b);

int cd(char **argv) {
    char *dir = argv[0];

    // 引数なし
    if (dir == NULL) {
        cwd = getenv("HOME");
        return 0;
    }

    char start = dir[0];
    ull dirlen = strlen(dir);
    char *tmp;

    // 絶対パス (/**)
    if (start == '/') {
        tmp = dir;
    } else if (start == '~') {
        if (dirlen > 1 && dir[1] != '/') {
            error("cd %s: No such file or directory", dir);
            return 1;
        }

        char *home = "/c/Users/harin"; // TODO: getenv("HOME");
        tmp = path_resolve(home, dir + 2);
    } else {
        tmp = path_resolve(cwd, dir);
    }

    printf("%s", tmp);
    return 0;
}

char *path_resolve(char* a, char *b) {
    ull alen = strlen(a);
    ull blen = strlen(b);
    int need_slash = a[alen - 1] != '/';
    ull reslen = alen + blen + need_slash;
    char *resolved = calloc(reslen, sizeof (char));
    resolved[0] = '\0';

    strcat_s(resolved, 100, a);
    if (need_slash) strcat_s(&resolved[alen], 100, "/");
    strcat_s(&resolved[alen + need_slash], 100, b);

    return resolved;
}

//char *path_normalize() {
//
//}
