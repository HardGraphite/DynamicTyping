#include <dyntypes.h>
#include "error.h"
#include "mem.h"

typedef struct
{
    __DT_VALUE_HEAD__
    Dt_Bool value;
} BoolValue;

#define AS_BOOL(_THIS) DT_PTR_AS(_THIS, BoolValue*)

static Dt_ValuePtr to_bool(Dt_ValuePtr _this)
{
    return _this;
}

static Dt_ValuePtr to_int(Dt_ValuePtr _this)
{
    return Dt_newInt(AS_BOOL(_this)->value ? 1 : 0);
}

static Dt_ValuePtr to_float(Dt_ValuePtr _this)
{
    return Dt_newFloat(AS_BOOL(_this)->value ? 1 : 0);
}

static Dt_ValuePtr to_str(Dt_ValuePtr _this)
{
    return Dt_newStr(AS_BOOL(_this)->value ? "True" : "False");
}

static Dt_ValuePtr length(Dt_ValuePtr _this)
{
    return Dt_newInt(0);
}

Dt_Type Dt_BoolType =
{
    .name = "bool",
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

static BoolValue bool_true =
{
    ._rc = DT_CONST_RC0,
    ._tm = &Dt_BoolType,
    .value = true,
};

static BoolValue bool_false =
{
    ._rc = DT_CONST_RC0,
    ._tm = &Dt_BoolType,
    .value = false,
};

Dt_ValuePtr Dt_True = &bool_true, Dt_False = &bool_false;

Dt_ValuePtr Dt_newBool(Dt_Bool v)
{
    return v ?
        DT_PTR_AS(&bool_true, Dt_Value*) :
        DT_PTR_AS(&bool_false, Dt_Value*);
}

Dt_Bool Dt_asBool(Dt_ValuePtr v)
{
    return AS_BOOL(v)->value;
}
