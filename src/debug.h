#pragma once

#include <stdio.h>

#ifndef DT_DEBUG
# define DT_DEBUG 0
#endif

#if DT_DEBUG
#define DT_DEBUG_PRINTF(...) \
{ \
    fputs("\x1b[35;1m[DEBUG-MSG]\x1b[0m ", stderr); \
    fprintf(stderr, __VA_ARGS__); \
    fputc('\n', stderr); \
}
#else
#define DT_DEBUG_PRINTF(...) ((void)0)
#endif // DT_DEBUG
