#include <stdio.h>
#include <stdarg.h>

int vprintf(const char *format,va_list vl)
{
    return vfprintf(stdout,format,vl);
}
