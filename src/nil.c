#include <dyntypes.h>
#include "error.h"
#include "mem.h"

static Dt_ValuePtr to_bool(Dt_ValuePtr _this)
{
    return Dt_newBool(false);
}

static Dt_ValuePtr to_int(Dt_ValuePtr _this)
{
    return Dt_newInt(0);
}

static Dt_ValuePtr to_float(Dt_ValuePtr _this)
{
    return Dt_newFloat(0);
}

static Dt_ValuePtr to_str(Dt_ValuePtr _this)
{
    return Dt_newStr("Nil");
}

static Dt_ValuePtr length(Dt_ValuePtr _this)
{
    return Dt_newInt(0);
}

Dt_Type Dt_NilType =
{
    .name = "nil",
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

static Dt_Value nil_const =
{
    ._rc = DT_CONST_RC0,
    ._tm = &Dt_NilType,
};

Dt_ValuePtr Dt_Nil = &nil_const;
