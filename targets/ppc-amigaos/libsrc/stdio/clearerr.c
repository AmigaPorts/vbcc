#include <stdio.h>

#undef clearerr

void clearerr(FILE *f)
{
    f->flags&=~(_ERR|_EOF);
}
