#include <stdio.h>

#undef feof

int feof(FILE *f)
{
    return(f->flags&_EOF);
}

