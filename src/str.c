#include <dyntypes.h>
#include "error.h"
#include "mem.h"

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define STRING_BUFFER_SIZE (2048)

_Thread_local static char string_buffer[STRING_BUFFER_SIZE];

typedef struct
{
    __DT_VALUE_HEAD__
    Dt_Size length;
    char    value[];
} StrValue;

#define AS_STR(_THIS) DT_PTR_AS(_THIS, StrValue*)

static Dt_ValuePtr to_bool(Dt_ValuePtr _this)
{
    return Dt_newBool(AS_STR(_this)->length);
}

static Dt_ValuePtr to_int(Dt_ValuePtr _this)
{
    return Dt_newInt(atol(AS_STR(_this)->value));
}

static Dt_ValuePtr to_float(Dt_ValuePtr _this)
{
    return Dt_newFloat(atof(AS_STR(_this)->value));
}

static Dt_ValuePtr to_str(Dt_ValuePtr _this)
{
    return _this;
}

static Dt_ValuePtr length(Dt_ValuePtr _this)
{
    return Dt_newInt(AS_STR(_this)->length);
}

Dt_Type Dt_StrType =
{
    .name = "str",
    ._m0 =
    {
        __Dt_private_methodfn0_na,
        to_bool,
        to_int,
        to_float,
        to_str,
        length,
    },
};

static StrValue str_empty =
{
    ._rc = DT_CONST_RC0,
    ._tm = &Dt_StrType,
    .length = 0,
    .value = "",
};

Dt_ValuePtr Dt_newStr(Dt_Str v)
{
    if (v == NULL || *v == '\0')
        return (Dt_ValuePtr)&str_empty;

    const size_t len = strlen(v);
    StrValue * p = (StrValue*)DT_ALLOCATE(sizeof(StrValue) + len + 1);

    p->_rc = 1;
    p->_tm = &Dt_StrType;
    p->length = len;
    memcpy(p->value, v, len);

    return (Dt_ValuePtr)p;
}

Dt_Str Dt_asStr(Dt_ValuePtr v)
{
    return AS_STR(v)->value;
}

Dt_ValuePtr Dt_format(const char * restrict fmtstr, ...)
{
    va_list ap;

    va_start(ap, fmtstr);
    vsnprintf(string_buffer, STRING_BUFFER_SIZE, fmtstr, ap);
    va_end(ap);

    return Dt_newStr(string_buffer);
}
