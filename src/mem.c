#include <dyntypes.h>
#include "mem.h"

void Dt_delValue(Dt_ValuePtr v)
{
    DT_DEALLOCATE(v);
}
