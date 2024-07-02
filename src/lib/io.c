#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "io.h"

void error(char *format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}

void debug(char *format, ...) {
#ifdef DEBUG
    va_list args;
    va_start(args, format);
    fprintf(stdout, "Debug: ");
    vfprintf(stdout, format, args);
    fprintf(stdout, "\n");
    va_end(args);
#endif
}