#include "error.h"
#include "mem.h"
#include "value.h"
#include "vector.h"

#include <stdarg.h>
#include <string.h>

typedef struct
{
    __DT_VALUE_HEAD__
    Vector value;
} ListValue;

#define AS_LIST(_THIS) DT_PTR_AS(_THIS, ListValue*)

static Dt_ValuePtr to_bool(Dt_ValuePtr _this)
{
    return Dt_newBool(AS_LIST(_this)->value.used_size);
}

static Dt_ValuePtr to_str(Dt_ValuePtr _this)
{
    if (!AS_LIST(_this)->value.used_size)
        return Dt_newStr("[]");

    Dt_ValuePtr s = Dt_newStr("[");
    const Dt_Size len = AS_LIST(_this)->value.used_size;

    for (Dt_Size i = 0; i < len; i++)
    {
        Dt_ValuePtr v  = AS_LIST(_this)->value.data[i];
        Dt_ValuePtr vs = DT_invokeMethod0(v, Dt_M_ToStr);
        Dt_ValuePtr ns = Dt_format(DT_isType(v, Dt_StrType) ? "%s\"%s\"%c" : "%s%s%c",
            Dt_asStr(s), Dt_asStr(vs), (i == len - 1 ? ']' : ','));
        DT_decRef(vs);
        DT_decRef(s);
        s = ns;
    }

    return s;
}

static Dt_ValuePtr length(Dt_ValuePtr _this)
{
    return Dt_newInt(AS_LIST(_this)->value.used_size);
}

static Dt_ValuePtr clone(Dt_ValuePtr _this)
{
    Dt_Size len = AS_LIST(_this)->value.used_size;
    Dt_ValuePtr p = Dt_newList(len, NULL);
    memcpy(AS_LIST(p)->value.data, AS_LIST(_this)->value.data, sizeof(Dt_ValuePtr) * len);
    for (Dt_Size i = 0; i < len; i++)
        DT_incRef(AS_LIST(_this)->value.data[i]);
    return p;
}

static Dt_ValuePtr dclone(Dt_ValuePtr _this)
{
    Dt_Size len = AS_LIST(_this)->value.used_size;
    Dt_ValuePtr p = Dt_newList(len, NULL);
    for (Dt_Size i = 0; i < len; i++)
    {
        Dt_ValuePtr v = AS_LIST(_this)->value.data[i];
        AS_LIST(p)->value.data[i] = DT_invokeMethod0(v, Dt_M_DClone);
    }
    return p;
}

static Dt_ValuePtr delete_self(Dt_ValuePtr _this)
{
    DT_DEBUG_PRINTF("delete list at %p (type=%s)", _this, DT_TypeNameOf(_this));
    vec_deinit(&AS_LIST(_this)->value);
    DT_DEALLOCATE(_this);
    return Dt_Nil;
}

static Dt_ValuePtr op_add(Dt_ValuePtr _this, Dt_ValuePtr a1)
{
    
    if (!DT_isType(a1, Dt_ListType))
        __Dt_private_raise_error(Dt_TypeError, "%s + %s is not allowed",
            DT_TypeNameOf(_this), DT_TypeNameOf(a1));

    ListValue * r, * _thisb = AS_LIST(_this), * a1b = AS_LIST(a1);

    if (!a1b->value.used_size)
    {
        DT_incRef(_this);
        r = AS_LIST(_this);
    }
    else
    {
        const Dt_Size half_len = _thisb->value.used_size;
        const Dt_Size len = half_len + a1b->value.used_size;
        r = (ListValue*)Dt_newList(len, NULL);
        r->value.used_size = len;

        for (Dt_Size i = 0; i < half_len; i++)
        {
            r->value.data[i] = _thisb->value.data[i];
            DT_incRef(_thisb->value.data[i]);
        }

        for (Dt_Size i = 0; i < a1b->value.used_size; i++)
        {
            r->value.data[i + half_len] = a1b->value.data[i];
            DT_incRef(a1b->value.data[i]);
        }
    }

    return (Dt_ValuePtr)r;
}

static Dt_ValuePtr op_mul(Dt_ValuePtr _this, Dt_ValuePtr a1)
{
    if (!DT_isType(a1, Dt_IntType))
        __Dt_private_raise_error(Dt_TypeError, "%s * %s is not allowed",
            DT_TypeNameOf(_this), DT_TypeNameOf(a1));

    ListValue * r, * _thisb = AS_LIST(_this);
    uint32_t cnt = Dt_asInt(a1);

    if (cnt == 0)
    {
        r = (ListValue*)Dt_newList(0, NULL);
    }
    else if (cnt == 1)
    {
        DT_incRef(_this);
        r = AS_LIST(_this);
    }
    else
    {
        const Dt_Size len = _thisb->value.used_size * cnt;
        r = (ListValue*)Dt_newList(len, NULL);
        r->value.used_size = len;

        const Dt_Size part_len = _thisb->value.used_size;
        for (uint32_t loop = 0; loop < cnt; loop++)
        {
            for (Dt_Size i = 0; i < part_len; i++)
            {
                const Dt_Size off = part_len * loop;
                r->value.data[i + off] = _thisb->value.data[i];
                DT_incRef(_thisb->value.data[i]);
            }
        }
    }

    return (Dt_ValuePtr)r;
}

static Dt_ValuePtr op_shl(Dt_ValuePtr _this, Dt_ValuePtr a1)
{
    vec_insert(&AS_LIST(_this)->value, -1, a1);

    DT_incRef(_this);
    return _this;
}

Dt_Type Dt_ListType =
{
    .name = "list",
    ._m0 =
    {
        __Dt_private_methodfn0_na,
        to_bool,
        __Dt_private_method_na_1a,
        __Dt_private_return_self_1a,
        to_str,
        length,
        __Dt_private_method_na_1a,
        clone,
        dclone,
        __Dt_private_self_incref_1a,
        __Dt_private_self_decref_1a,
        delete_self,
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
        op_shl,
        __Dt_private_method_na_2a,
        __Dt_private_method_na_2a,
        __Dt_private_method_na_2a,
    },
};

Dt_ValuePtr Dt_newList(Dt_Size len, ...)
{
    va_list ap;
    ListValue * p = (ListValue*)DT_ALLOCATE(sizeof(ListValue));

    p->_rc = 1;
    p->_tm = &Dt_ListType;
    vec_init(&p->value, len);

    Dt_Size i = 0;
    va_start(ap, len);
    for (; i < len; i++)
    {
        Dt_ValuePtr v = va_arg(ap, Dt_ValuePtr);
        if (v == NULL)
            break;
        DT_incRef(v);
        p->value.data[i] = v;
    }
    va_end(ap);
    p->value.used_size = i;

    return (Dt_ValuePtr)p;
}
