#include <stdio.h>
#include <stdarg.h>

int scanf(const char *fmt,...)
{
    va_list vl;
    va_start(vl,fmt);
    return vfscanf(stdin,fmt,vl);
}
