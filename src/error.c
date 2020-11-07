#include "error.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define ERRMSG_STRBUF_SIZE (128)

_Thread_local static char errmsg_strbuf[ERRMSG_STRBUF_SIZE];

static void _default_error_handler(const char * msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);

    abort();
}

static void (*error_handler)(const char *) = _default_error_handler;

void Dt_setErrorHandler(void (*handler)(const char *))
{
    error_handler = (handler == NULL) ?
        _default_error_handler : handler;
}

void __Dt_private_raise_error(const char * fmt, ...)
{
    {
        va_list ap;
        va_start(ap, fmt);
        vsnprintf(errmsg_strbuf, ERRMSG_STRBUF_SIZE, fmt, ap);
        va_end(ap);
    }

    error_handler(errmsg_strbuf);
}

Dt_Value * __Dt_private_methodfn0_na(Dt_Value * _0)
{
    __Dt_private_raise_error("not a method");
    return NULL;
}

Dt_Value * __Dt_private_methodfn1_na(Dt_Value * _0, Dt_Value * _1)
{
    __Dt_private_raise_error("not a method");
    return NULL;
}

Dt_Value * __Dt_private_methodfn2_na(Dt_Value * _0, Dt_Value * _1, Dt_Value * _2)
{
    __Dt_private_raise_error("not a method");
    return NULL;
}
