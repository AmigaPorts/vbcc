#include <stdio.h>

#undef rewind

void rewind(FILE *f)
{
    fseek(f,0L,SEEK_SET);
    clearerr(f);
}
