#include "error.h"
#include "mem.h"
#include "value.h"

#include <math.h>
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

static Dt_ValuePtr hash(Dt_ValuePtr _this)
{
    Dt_Float f = AS_FLOAT(_this)->value;
    Dt_Int h;

    if (f == (Dt_Float)0)
        h = (Dt_Int)0; // +0 and -0 will have the same hash code
    else if (isnan(f))
        h = DT_CONST_RC0;
    else
        h = *(Dt_Int*)&f;

    return Dt_newInt(h);
}

static Dt_ValuePtr op_add(Dt_ValuePtr _this, Dt_ValuePtr a1)
{
    FloatValue * a1b = AS_FLOAT(DT_invokeMethod0(a1, Dt_M_ToInt));
    Dt_ValuePtr r = Dt_newFloat(AS_FLOAT(_this)->value + a1b->value);
    DT_decRef((Dt_ValuePtr)a1b);
    return r;
}

static Dt_ValuePtr op_sub(Dt_ValuePtr _this, Dt_ValuePtr a1)
{
    FloatValue * a1b = AS_FLOAT(DT_invokeMethod0(a1, Dt_M_ToInt));
    Dt_ValuePtr r = Dt_newFloat(AS_FLOAT(_this)->value - a1b->value);
    DT_decRef((Dt_ValuePtr)a1b);
    return r;
}

static Dt_ValuePtr op_mul(Dt_ValuePtr _this, Dt_ValuePtr a1)
{
    FloatValue * a1b = AS_FLOAT(DT_invokeMethod0(a1, Dt_M_ToInt));
    Dt_ValuePtr r = Dt_newFloat(AS_FLOAT(_this)->value * a1b->value);
    DT_decRef((Dt_ValuePtr)a1b);
    return r;
}

static Dt_ValuePtr op_div(Dt_ValuePtr _this, Dt_ValuePtr a1)
{
    FloatValue * a1b = AS_FLOAT(DT_invokeMethod0(a1, Dt_M_ToInt));
    Dt_ValuePtr r = Dt_newFloat(AS_FLOAT(_this)->value / a1b->value);
    DT_decRef((Dt_ValuePtr)a1b);
    return r;
}

static Dt_ValuePtr op_pow(Dt_ValuePtr _this, Dt_ValuePtr a1)
{
    FloatValue * a1b = AS_FLOAT(DT_invokeMethod0(a1, Dt_M_ToInt));
    Dt_ValuePtr r = Dt_newFloat(pow(AS_FLOAT(_this)->value, a1b->value));
    DT_decRef((Dt_ValuePtr)a1b);
    return r;
}

Dt_Type Dt_FloatType =
{
    .name = "float",
    ._m0 =
    {
        __Dt_private_methodfn0_na,
        to_bool,
        to_int,
        __Dt_private_self_incref_1a,
        to_str,
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
        op_sub,
        op_mul,
        op_div,
        op_pow,
        __Dt_private_method_na_2a,
        __Dt_private_method_na_2a,
        __Dt_private_method_na_2a,
        __Dt_private_method_na_2a,
        __Dt_private_method_na_2a,
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
    {
        Dt_ValuePtr p = (Dt_ValuePtr)&float_0;
        DT_incRef(p);
        return p;
    }

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
