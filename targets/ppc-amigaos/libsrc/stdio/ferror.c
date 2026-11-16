#include <stdio.h>

#undef ferror

int ferror(FILE *f)
{
    return(f->flags&_ERR);
}

