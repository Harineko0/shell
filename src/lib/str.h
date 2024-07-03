#include <stdbool.h>

/// 文字列で from_index から後ろ向きに数えて key が count 回目に出現した top を返す
int strfindback(const char *str, char key, int from_index, int count);

bool strisnum(const char *str);

void strreplace(char *str, char from, char to);

bool strstart(const char *str1, const char *str2);
