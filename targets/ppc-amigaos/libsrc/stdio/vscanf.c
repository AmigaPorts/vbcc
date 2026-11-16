#include <stdio.h>
#include <stdarg.h>

int vscanf(const char *format,va_list vl)
{
    return vfscanf(stdin,format,vl);
}
