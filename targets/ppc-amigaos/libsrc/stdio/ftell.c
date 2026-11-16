/*
** vbcc-AmigaOS4 version of ftell.c
*/

#include "inc.h"

long ftell(FILE *f)
{
    long offset;
    offset=__seek(f->filehandle,0L,0L);
    if(f->flags&_READ) offset-=f->count;
    if(f->flags&_WRITE) offset+=f->bufsize-f->count;
    return(offset);
}
