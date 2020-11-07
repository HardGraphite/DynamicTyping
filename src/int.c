#include <dyntypes.h>
#include "error.h"
#include "mem.h"

#include <stdio.h>

typedef struct
{
    __DT_VALUE_HEAD__
    Dt_Int value;
} IntValue;

#define AS_INT(_THIS) DT_PTR_AS(_THIS, IntValue*)

static Dt_ValuePtr to_bool(Dt_ValuePtr _this)
{
    return Dt_newBool(AS_INT(_this)->value);
}

static Dt_ValuePtr to_int(Dt_ValuePtr _this)
{
    return _this;
}

static Dt_ValuePtr to_float(Dt_ValuePtr _this)
{
    return Dt_newFloat(AS_INT(_this)->value);
}

static Dt_ValuePtr to_str(Dt_ValuePtr _this)
{
    char buffer[32];
    snprintf(buffer, 32, "%i", AS_INT(_this)->value);
    return Dt_newStr(buffer);
}

static Dt_ValuePtr length(Dt_ValuePtr _this)
{
    return Dt_newInt(0);
}

Dt_Type Dt_IntType =
{
    .name = "int",
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

#define INT_CONSTS_BEG ((Dt_Int)-16)
#define INT_CONSTS_END ((Dt_Int)63)
#define INT_CONSTS_CNT (INT_CONSTS_END - INT_CONSTS_BEG + 1)
#define MAKE_INT_CONST(INDEX) \
    {._rc = DT_CONST_RC0, ._tm = &Dt_IntType, .value = INDEX + INT_CONSTS_BEG}

static IntValue int_consts[INT_CONSTS_CNT] =
{
MAKE_INT_CONST( 0), MAKE_INT_CONST( 1), MAKE_INT_CONST( 2), MAKE_INT_CONST( 3),
MAKE_INT_CONST( 4), MAKE_INT_CONST( 5), MAKE_INT_CONST( 6), MAKE_INT_CONST( 7),
MAKE_INT_CONST( 8), MAKE_INT_CONST( 9), MAKE_INT_CONST(10), MAKE_INT_CONST(11),
MAKE_INT_CONST(12), MAKE_INT_CONST(13), MAKE_INT_CONST(14), MAKE_INT_CONST(15),
MAKE_INT_CONST(16), MAKE_INT_CONST(17), MAKE_INT_CONST(18), MAKE_INT_CONST(19),
MAKE_INT_CONST(20), MAKE_INT_CONST(21), MAKE_INT_CONST(22), MAKE_INT_CONST(23),
MAKE_INT_CONST(24), MAKE_INT_CONST(25), MAKE_INT_CONST(26), MAKE_INT_CONST(27),
MAKE_INT_CONST(28), MAKE_INT_CONST(29), MAKE_INT_CONST(30), MAKE_INT_CONST(31),
MAKE_INT_CONST(32), MAKE_INT_CONST(33), MAKE_INT_CONST(34), MAKE_INT_CONST(35),
MAKE_INT_CONST(36), MAKE_INT_CONST(37), MAKE_INT_CONST(38), MAKE_INT_CONST(39),
MAKE_INT_CONST(40), MAKE_INT_CONST(41), MAKE_INT_CONST(42), MAKE_INT_CONST(43),
MAKE_INT_CONST(44), MAKE_INT_CONST(45), MAKE_INT_CONST(46), MAKE_INT_CONST(47),
MAKE_INT_CONST(48), MAKE_INT_CONST(49), MAKE_INT_CONST(50), MAKE_INT_CONST(51),
MAKE_INT_CONST(52), MAKE_INT_CONST(53), MAKE_INT_CONST(54), MAKE_INT_CONST(55),
MAKE_INT_CONST(56), MAKE_INT_CONST(57), MAKE_INT_CONST(58), MAKE_INT_CONST(59),
MAKE_INT_CONST(60), MAKE_INT_CONST(61), MAKE_INT_CONST(62), MAKE_INT_CONST(63),
MAKE_INT_CONST(64), MAKE_INT_CONST(65), MAKE_INT_CONST(66), MAKE_INT_CONST(67),
MAKE_INT_CONST(68), MAKE_INT_CONST(69), MAKE_INT_CONST(70), MAKE_INT_CONST(71),
MAKE_INT_CONST(72), MAKE_INT_CONST(73), MAKE_INT_CONST(74), MAKE_INT_CONST(75),
MAKE_INT_CONST(76), MAKE_INT_CONST(77), MAKE_INT_CONST(78), MAKE_INT_CONST(79),
};
_Static_assert(79 - 0 + 1 == INT_CONSTS_CNT, "incorrect number of constants");

Dt_ValuePtr Dt_newInt(Dt_Int v)
{
    if (v >= INT_CONSTS_BEG && v <= INT_CONSTS_END)
        return (Dt_ValuePtr)(int_consts + v - INT_CONSTS_BEG);

    IntValue * p = (IntValue*)DT_ALLOCATE(sizeof(IntValue));

    p->_rc = 1;
    p->_tm = &Dt_IntType;
    p->value = v;
    
    return (Dt_ValuePtr)p;
}

Dt_Int Dt_asInt(Dt_ValuePtr v)
{
    return AS_INT(v)->value;
}
