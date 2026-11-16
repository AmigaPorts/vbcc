#include <stdio.h>
#include <stdarg.h>

int printf(const char *format,...)
{
    va_list vl;
    va_start(vl,format);
    return vfprintf(stdout,format,vl);
}
