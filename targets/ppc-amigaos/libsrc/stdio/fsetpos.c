#include <stdio.h>

#undef fsetpos

int fsetpos(FILE *f,const fpos_t *ptr)
{
    return(fseek(f,*ptr,SEEK_SET));
}

