#include <dyntypes.h>
#include "error.h"
#include "mem.h"

#include <stdio.h>

typedef struct
{
    __DT_VALUE_HEAD__
    Dt_Float value;
} FloatValue;

#define AS_FLOAT(_THIS) DT_PTR_AS(_THIS, FloatValue*)

static Dt_ValuePtr to_bool(Dt_ValuePtr _this)
{
    return Dt_newBool(AS_FLOAT(_this)->value);
}

static Dt_ValuePtr to_int(Dt_ValuePtr _this)
{
    return Dt_newInt(AS_FLOAT(_this)->value);
}

static Dt_ValuePtr to_float(Dt_ValuePtr _this)
{
    return _this;
}

static Dt_ValuePtr to_str(Dt_ValuePtr _this)
{
    char buffer[32];
    snprintf(buffer, 32, "%lf", AS_FLOAT(_this)->value);
    return Dt_newStr(buffer);
}

static Dt_ValuePtr length(Dt_ValuePtr _this)
{
    return Dt_newInt(0);
}

Dt_Type Dt_FloatType =
{
    .name = "float",
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

static FloatValue float_0 =
{
    ._rc = DT_CONST_RC0,
    ._tm = &Dt_FloatType,
    .value = 0,
};

Dt_ValuePtr Dt_newFloat(Dt_Float v)
{
    if (v == (Dt_Float)0)
        return (Dt_ValuePtr)&float_0;

    FloatValue * p = (FloatValue*)DT_ALLOCATE(sizeof(FloatValue));

    p->_rc = 1;
    p->_tm = &Dt_FloatType;
    p->value = v;

    return (Dt_ValuePtr)p;
}

Dt_Float Dt_asFloat(Dt_ValuePtr v)
{
    return AS_FLOAT(v)->value;
}
