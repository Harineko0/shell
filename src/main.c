#include <stdio.h>
#include <string.h>
#include "cmd.h"
#include "lib/io.h"
#include "cmd/cd.h"
#include "lib/map.h"
#include "global.h"

#define MAX_LEN 256

typedef unsigned long long ull;

int main() {
    char buff[MAX_LEN];

    init_global();

    while (true) {
        fputs(cwd, stdout);
        fputs(">", stdout);

        fgets(buff, MAX_LEN, stdin);

        ull len = strlen(buff);

        if (len == 0) {
            continue;
        }

        if (strcmp(buff, "exit") == 0) {
            break;
        }

        if (buff[len - 1] != '\n') {
            error("Too long statement (size: %d)", MAX_LEN);
        }

        char *newline = strchr(buff, '\n');
        if (newline) *newline = '\0';

        c_execute(buff);
    }

    return 0;
}
