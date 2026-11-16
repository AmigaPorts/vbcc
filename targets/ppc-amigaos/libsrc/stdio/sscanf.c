#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int sscanf(const char *s,const char *format,...)
{
    FILE f;va_list vl;
    f.flags=_READABLE|_READ|_EOF;
    f.base=f.pointer=(char *)s;
    f.bufsize=f.count=strlen(s);
    f.filehandle=0;
    va_start(vl,format);
    return vfscanf(&f,format,vl);
}
