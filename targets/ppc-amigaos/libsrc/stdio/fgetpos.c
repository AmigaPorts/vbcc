#include <stdio.h>

#undef fgetpos

int fgetpos(FILE *f,fpos_t *ptr)
{
    long l;
    l=ftell(f);
    if(l==-1L) return(1);
    *ptr=l;
    return(0);
}
