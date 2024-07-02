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
