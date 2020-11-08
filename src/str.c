#include "error.h"
#include "mem.h"
#include "murmurhash.h"
#include "value.h"

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

static Dt_ValuePtr length(Dt_ValuePtr _this)
{
    return Dt_newInt(AS_STR(_this)->length);
}

static Dt_ValuePtr hash(Dt_ValuePtr _this)
{
    return Dt_newInt(STR_HASH(AS_STR(_this)->value, AS_STR(_this)->length));
}

static Dt_ValuePtr op_add(Dt_ValuePtr _this, Dt_ValuePtr a1)
{
    StrValue * r;
    StrValue * a1b = AS_STR(DT_invokeMethod0(a1, Dt_M_ToStr));

    if (!a1b->length)
    {
        DT_incRef(_this);
        r = AS_STR(_this);
    }
    else
    {
        Dt_Size len = AS_STR(_this)->length + a1b->length;
        r = (StrValue*)DT_ALLOCATE(sizeof(StrValue) + len + 1);

        r->_rc = 1;
        r->_tm = &Dt_StrType;
        r->length = len;

        memcpy(r->value, AS_STR(_this)->value, AS_STR(_this)->length);
        memcpy(r->value + AS_STR(_this)->length, a1b->value, a1b->length + 1);
    }

    DT_decRef((Dt_ValuePtr)a1b);
    return (Dt_ValuePtr)r;
}

static Dt_ValuePtr op_mul(Dt_ValuePtr _this, Dt_ValuePtr a1)
{
    if (!DT_isType(a1, Dt_IntType))
        __Dt_private_raise_error(Dt_TypeError, "%s * %s is not allowed",
            DT_TypeNameOf(_this), DT_TypeNameOf(a1));

    StrValue * r;
    uint32_t cnt = Dt_asInt(a1);

    if (cnt == 0)
    {
        r = (StrValue*)Dt_newStr("");
    }
    else if (cnt == 1)
    {
        DT_incRef(_this);
        r = AS_STR(_this);
    }
    else
    {
        Dt_Size len = AS_STR(_this)->length * cnt;
        r = (StrValue*)DT_ALLOCATE(sizeof(StrValue) + len + 1);

        r->_rc = 1;
        r->_tm = &Dt_StrType;
        r->length = len;

        for (uint32_t i = 0; i < cnt; i++)
            memcpy(r->value + i, AS_STR(_this)->value, AS_STR(_this)->length);
        r->value[r->length] = '\0';
    }

    return (Dt_ValuePtr)r;
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
        __Dt_private_self_incref_1a,
        length,
        hash,
        __Dt_private_self_incref_1a,
        __Dt_private_self_incref_1a,
        __Dt_private_self_incref_1a,
        __Dt_private_self_decref_1a,
        __Dt_private_delete_1a,
    },
    ._m1 =
    {
        __Dt_private_methodfn1_na,
        op_add,
        __Dt_private_method_na_2a,
        op_mul,
        __Dt_private_method_na_2a,
        __Dt_private_method_na_2a,
        __Dt_private_method_na_2a,
        op_add,
        __Dt_private_method_na_2a,
        __Dt_private_method_na_2a,
        __Dt_private_method_na_2a,
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
    {
        Dt_ValuePtr p = (Dt_ValuePtr)&str_empty;
        DT_incRef(p);
        return p;
    }

    const size_t len = strlen(v);
    StrValue * p = (StrValue*)DT_ALLOCATE(sizeof(StrValue) + len + 1);

    p->_rc = 1;
    p->_tm = &Dt_StrType;
    p->length = len;
    memcpy(p->value, v, len + 1);

    return (Dt_ValuePtr)p;
}

Dt_ValuePtr Dt_newStrN(Dt_Str v, Dt_Size len)
{
    if (v == NULL || *v == '\0')
    {
        Dt_ValuePtr p = (Dt_ValuePtr)&str_empty;
        DT_incRef(p);
        return p;
    }

    StrValue * p = (StrValue*)DT_ALLOCATE(sizeof(StrValue) + len + 1);

    p->_rc = 1;
    p->_tm = &Dt_StrType;
    p->length = len;
    memcpy(p->value, v, len + 1);

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
