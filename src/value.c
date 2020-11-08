#include <dyntypes.h>
#include "error.h"
#include "mem.h"
#include "value.h"

#include <stdarg.h>

Dt_ValuePtr __Dt_private_method_na_1a(Dt_ValuePtr _this)
{
    __Dt_private_raise_error(Dt_MethodError,
        "%s does not have this method", DT_TypeNameOf(_this));
    return Dt_Nil;
}

Dt_ValuePtr __Dt_private_method_na_2a(Dt_ValuePtr _this, Dt_ValuePtr a1)
{
    __Dt_private_raise_error(Dt_MethodError,
        "%s does not have this method", DT_TypeNameOf(_this));
    return Dt_Nil;
}

Dt_ValuePtr __Dt_private_return_self_1a(Dt_ValuePtr _this)
{
    return _this;
}

Dt_ValuePtr __Dt_private_self_incref_1a(Dt_ValuePtr _this)
{
    DT_incRef(_this);
    return _this;
}

Dt_ValuePtr __Dt_private_self_decref_1a(Dt_ValuePtr _this)
{
    DT_decRef(_this);
    return Dt_Nil;
}

Dt_ValuePtr __Dt_private_delete_1a(Dt_ValuePtr _this)
{
    DT_DEBUG_PRINTF("delete object at %p (type=%s)", _this, DT_TypeNameOf(_this));
    DT_DEALLOCATE(_this);
    return Dt_Nil;
}

Dt_ValuePtr Dt_invokeMethod(Dt_ValuePtr value, Dt_Method method_id, ...)
{
    if (method_id > __Dt_M_0__ && method_id < __Dt_M_0E__)
    {
        return DT_invokeMethod0(value, method_id);
    }
    else if (method_id > __Dt_M_1__ && method_id < __Dt_M_1E__)
    {
        va_list ap;
        Dt_ValuePtr arg;

        va_start(ap, method_id);
        arg = va_arg(ap, Dt_ValuePtr);
        va_end(ap);

        return DT_invokeMethod1(value, method_id, arg);
    }
    else if (method_id > __Dt_M_2__ && method_id < __Dt_M_2E__)
    {
        va_list ap;
        Dt_ValuePtr args[2];

        va_start(ap, method_id);
        args[0] = va_arg(ap, Dt_ValuePtr);
        args[1] = va_arg(ap, Dt_ValuePtr);
        va_end(ap);

        return DT_invokeMethod2(value, method_id, args[0], args[1]);
    }
    else
    {
        __Dt_private_raise_error(Dt_MethodError, "invalid method-id: %i", (int)method_id);
    }
}
