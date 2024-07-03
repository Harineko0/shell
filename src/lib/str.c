#include <stdlib.h>
#include "str.h"

int strfindback(const char *str, char key, int from_index, int count) {
    int found = 0;
    char c;

    while (from_index > 0 && found < count) {
        // 後ろから探索する
        c = str[from_index--];

        if (c == key) {
            found++;
        }
    }

    // 見つからなかった場合
    if (found < count) {
        return -1;
    }

    // 最後に from_index-- したので 1 戻す
    return from_index + 1;
}

bool strisnum(const char *str) {
    char c;
    while ((c = *str) != '\0') {
        if (c < '0' || c > '9') {
            return false;
        }
        str++;
    }
    return true;
}

void strreplace(char *str, char from, char to) {
    char c;
    while ((c = *str) != '\0') {
        if (c == from) {
            *str = to;
        }
        str++;
    }
}

bool strstart(const char *str1, const char *str2) {
    char c1, c2;

    while ((c1 = *str1++) != '\0' && (c2 = *str2++) != '\0') {
        if (c1 != c2) {
            return false;
        }
    }

    // str2 を最後まで探索してない
    if (c2 != '\0') {
        return false;
    }

    return true;
}

char *substr(const char *from, const char *to) {
    char *word = calloc(to - from + 1, sizeof (char *));
    char *w = word;

    while (to - from > 0) {
        *w++ = *from++;
    }
    *w = '\0';
    return word;
}