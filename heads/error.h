#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>

#define CHECK_ALLOC(ptr) do { \
    if (!(ptr)) { \
        fprintf(stderr, "Falha de alocacao (%s) em %s:%d\n", #ptr, __FILE__, __LINE__); \
        exit(EXIT_FAILURE); \
    } \
} while (0)

#endif