#include "error.h"
#include "mem.h"
#include "value.h"

typedef struct
{
    __DT_VALUE_HEAD__
    Dt_Bool value;
} BoolValue;

#define AS_BOOL(_THIS) DT_PTR_AS(_THIS, BoolValue*)

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

static Dt_ValuePtr op_bitand(Dt_ValuePtr _this, Dt_ValuePtr a1)
{
    BoolValue * a1b = AS_BOOL(DT_invokeMethod0(a1, Dt_M_ToBool));
    Dt_ValuePtr r = AS_BOOL(_this)->value & a1b->value ? Dt_True : Dt_False;
    DT_decRef((Dt_ValuePtr)a1b);
    return r;
}

static Dt_ValuePtr op_bitor(Dt_ValuePtr _this, Dt_ValuePtr a1)
{
    BoolValue * a1b = AS_BOOL(DT_invokeMethod0(a1, Dt_M_ToBool));
    Dt_ValuePtr r = AS_BOOL(_this)->value | a1b->value ? Dt_True : Dt_False;
    DT_decRef((Dt_ValuePtr)a1b);
    return r;
}

Dt_Type Dt_BoolType =
{
    .name = "bool",
    ._m0 =
    {
        __Dt_private_methodfn0_na,
        __Dt_private_return_self_1a,
        to_int,
        to_float,
        to_str,
        length,
        to_int,
        __Dt_private_return_self_1a,
        __Dt_private_return_self_1a,
        __Dt_private_return_self_1a,
        __Dt_private_return_self_1a,
        __Dt_private_return_self_1a,
    },
    ._m1 =
    {
        __Dt_private_methodfn1_na,
        op_bitor,
        __Dt_private_method_na_2a,
        op_bitand,
        __Dt_private_method_na_2a,
        __Dt_private_method_na_2a,
        __Dt_private_method_na_2a,
        __Dt_private_method_na_2a,
        __Dt_private_method_na_2a,
        op_bitand,
        op_bitor,
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

Dt_ValuePtr Dt_True = DT_PTR_AS(&bool_true, Dt_Value*),
            Dt_False = DT_PTR_AS(&bool_false, Dt_Value*);

Dt_ValuePtr Dt_newBool(Dt_Bool v)
{
    Dt_ValuePtr p = v ?
        DT_PTR_AS(&bool_true, Dt_Value*) :
        DT_PTR_AS(&bool_false, Dt_Value*);

    DT_incRef(p);
    return p;
}

Dt_Bool Dt_asBool(Dt_ValuePtr v)
{
    return AS_BOOL(v)->value;
}
