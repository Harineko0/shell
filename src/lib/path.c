#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "path.h"
#include "str.h"
#include "io.h"

typedef unsigned long long ull;

typedef enum {
    NUNUNU, // \0 \0 \0
    NUNUSL, // \0 \0 /
    NUSLPE, // \0 / .
    SLPEPE, // / . .
} State;

char *path_merge(char* a, char *b);
/// パスを正規化する. 成功したら 0 を, 失敗したら 1 を返す
int path_normalize(char *path);

int max(int a, int b) {
    return a > b ? a : b;
}

char *path_resolve(char *a, char *b) {
    char *merged = path_merge(a, b);
    int result = path_normalize(merged);

    if (result == 1) {
        free(merged);
        return NULL;
    }

    return merged;
}

char *path_merge(char* a, char *b) {
    ull alen = strlen(a);
    ull blen = strlen(b);

    int a_need_slash = a[alen - 1] != '/';
    int b_need_slash = b[blen - 1] != '/';
    ull reslen = alen + blen + a_need_slash + b_need_slash;
    char *merged = calloc(reslen, sizeof (char));
    merged[0] = '\0';

    strcat_s(merged, 100, a);
    if (a_need_slash) strcat_s(&merged[alen], MAX_DIR_LEN, "/");
    strcat_s(&merged[alen + a_need_slash], MAX_DIR_LEN, b);
    if (b_need_slash) strcat_s(&merged[alen + a_need_slash + blen], MAX_DIR_LEN, "/");

    return merged;
}

/**
 * x := [^./]
 * A[\0, \0, \0] --/-> B[\0, \0, /]
 * B[\0, \0, /] --/-> error
 * B[\0, \0, /] --.-> C[\0, /, .]
 * B[\0, \0, /] --x-> A[\0, \0, \0]
 * C[\0, /, .] --/-> A[\0, \0, \0] & new を一つ前の / まで戻す
 * C[\0, /, .] --.-> D[/, ., .]
 * C[\0, /, .] --x-> A[\0, \0, \0]
 * D[/, ., .] --/-> A[\0, \0, \0] & new を二つ前の / まで戻す
 * D[/, ., .] --.-> A[\0, \0, \0]
 * D[/, ., .] --x-> A[\0, \0, \0]
 */
int path_normalize(char *path) {
    int old = 0, new = 0;
    char c;
    State state = NUNUNU;

    // パスを一文字ずつ読む
    while ((c = path[old++]) != '\0') {
        switch (state) {
            case NUNUNU:
                if (c == '/') {
                    state = NUNUSL;
                }
                break;

            case NUNUSL:
                if (c == '/') {
                    // error
                    return 1;
                }
                if (c == '.') {
                    state = NUSLPE;
                } else {
                    state = NUNUNU;
                }
                break;

            case NUSLPE:
                if (c == '.') {
                    state = SLPEPE;
                    break;
                }

                if (c == '/') {
                    // 1 つ前の / まで戻す
                    int index = strfindback(path, '/', new, 2);
                    new = max(index, 0);
                }

                state = NUNUNU;
                break;

            case SLPEPE:
                if (c == '/') {
                    // 2 つ前の / まで戻す
                    int index = strfindback(path, '/', new, 3);
                    new = max(index, 0);
                }

                state = NUNUNU;
                break;
        }

        path[new++] = c;
    }

    path[new - 1] = '\0';
    return 0;
}
