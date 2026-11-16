#include <stdio.h>
#include <stdarg.h>

int __aprintf(const char *format,...)
{
    va_list vl;
    va_start(vl,format);
    return vfprintf(stderr,format,vl);
}
