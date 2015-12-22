#pragma once

// This file is only here for windows because Windows is dumb and doesn't have a getline function

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t getline(char **lineptr, size_t *n, FILE *stream);

#ifdef __cplusplus
}
#endif