#include "error.h"
#include "mem.h"
#include "value.h"

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

static Dt_ValuePtr hash(Dt_ValuePtr _this)
{
    return Dt_newInt(-1);
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
        hash,
        __Dt_private_return_self_1a,
        __Dt_private_return_self_1a,
        __Dt_private_return_self_1a,
        __Dt_private_return_self_1a,
        __Dt_private_return_self_1a,
    },
    ._m1 =
    {
        __Dt_private_methodfn1_na,
        __Dt_private_method_na_2a,
        __Dt_private_method_na_2a,
        __Dt_private_method_na_2a,
        __Dt_private_method_na_2a,
        __Dt_private_method_na_2a,
        __Dt_private_method_na_2a,
        __Dt_private_method_na_2a,
        __Dt_private_method_na_2a,
        __Dt_private_method_na_2a,
        __Dt_private_method_na_2a,
    }
};

static Dt_Value nil_const =
{
    ._rc = DT_CONST_RC0,
    ._tm = &Dt_NilType,
};

Dt_ValuePtr Dt_Nil = &nil_const;
