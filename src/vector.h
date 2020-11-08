#pragma once

#include <dyntypes.h>

typedef struct _Vector
{
    Dt_Size     capacity;
    Dt_Size     used_size;
    Dt_Value ** data;
} Vector;

extern void vec_init(Vector * vec, Dt_Size cap);
extern void vec_deinit(Vector * _this);
extern void vec_insert(Vector * _this, Dt_Int index, Dt_ValuePtr value);
extern void vec_remove(Vector * _this, Dt_Int index);
