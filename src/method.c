#include <dyntypes.h>
#include "error.h"

#include <stdarg.h>

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
        __Dt_private_raise_error("invalid method-id: %i", (int)method_id);
    }
}
