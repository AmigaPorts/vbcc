#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int vsscanf(const char *s,const char *format,va_list vl)
{
    FILE f;
    f.flags=_READABLE|_READ;
    f.base=f.pointer=(char *)s;
    f.bufsize=f.count=strlen(s);
    f.filehandle=0;
    return(vfscanf(&f,format,vl));
}
