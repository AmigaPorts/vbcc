/*
** vbcc-AmigaOS4 version of _flushbuf.c
*/

#include "inc.h"

/* flushes remaining data from buffer */
int _flushbuf(FILE *f)
{
    _chkabort();
    if(!f) return(EOF);
    if(!f->bufsize){if(f->flags&_UNBUF) f->bufsize=1; else f->bufsize=BUFSIZ;}
    if(!f->base) return(0);
    if(f->flags&_WRITE){
        if(f->filehandle){
            int len=f->pointer-f->base;
            if(__write(f->filehandle,f->base,len)!=len){
                f->flags|=_ERR;
                return(EOF);
            }
        }else return(0);
        f->pointer=f->base;
        f->count=f->bufsize;
    }
    f->flags&=~(_READ|_WRITE);
    return(0);
}
