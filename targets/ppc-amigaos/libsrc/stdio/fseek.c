/*
** vbcc-AmigaOS4 version of fseek.c
*/

#include "inc.h"

int fseek(FILE *f,long offset,int origin)
{
    if(!f) return(EOF);
    if(origin==SEEK_CUR){
        if(f->flags&_READ) offset-=f->count;
    }
    if(f->flags&_WRITE) _flushbuf(f);
    f->flags&=~(_READ|_WRITE|_EOF);
    f->count=0;
    f->pointer=f->base;
    if(__seek(f->filehandle,offset,origin)==-1){
        f->flags|=_ERR;
        return(EOF);
    }
    return(0);
}
