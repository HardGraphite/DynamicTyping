#include <stdlib.h>
#include <stdint.h>

#define DT_ALLOCATE(_SIZE)      malloc(_SIZE)
#define DT_DEALLOCATE(_PTR)     free(_PTR)

#define _ALIGN_SIZE sizeof(size_t)
#define DT_SIZE_ALIGN(_SIZE) (_SIZE + (_ALIGN_SIZE - 1)) & (~(_ALIGN_SIZE - 1))

#define DT_DECL_MEM(_NAME, _SIZE)  uint8_t _NAME [ DT_SIZE_ALIGN(_SIZE) ]
#define DT_PTR_AS(_PTR, _TYPE)     ( ( _TYPE ) _PTR )
#define DT_MEM_AS(_MEM, _TYPE)     (*DT_PTR_AS(&_MEM, _TYPE*))

#define DT_CONST_RC0 (((Dt_Size)-1) / 2)
