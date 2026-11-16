#include <stdio.h>

int fscanf(FILE *f,const char *fmt,...)
{
    va_list vl;int n;
    va_start(vl,fmt);
    n=vfscanf(f,fmt,vl);
    va_end(vl);
    return(n);
}
