#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#define MAX_LINE 256

void error(char *format, ...);

int main() {
    char buff[MAX_LINE];

    while (fgets(buff, MAX_LINE, stdin) != NULL) {
        if (buff[strlen(buff) - 1] != '\n') {
            error("Too long statement (max: %d)", MAX_LINE);
        }
    }

    return 0;
}

void error(char *format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "error: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
