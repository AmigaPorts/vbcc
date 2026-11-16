/*
** vbcc-AmigaOS4 version of _fillbuf.c
*/

#include "inc.h"


/* fill buffer with new data */
int _fillbuf(FILE *f)
{
    char c;

    _chkabort();
    if(!f) return(EOF);
    if((f->flags&(_READABLE|_WRITE|_EOF))!=_READABLE) return(EOF);
    f->flags|=_READ;
    if(f->flags&_ISTTY) _ttyflush();
    if(!f->bufsize){if(f->flags&_UNBUF) f->bufsize=1; else f->bufsize=BUFSIZ;}
    if(!f->base){
        char *p;
        if(!(p=malloc(f->bufsize+((f->flags&_LINEBUF)?2:1))))
            return(EOF);
        f->base=p+1;
    }
    f->pointer=f->base;
    f->count=__read(f->filehandle,f->pointer,f->bufsize);
    if(--f->count<0){
        if(f->count==-1) f->flags|=_EOF;
         else            f->flags|=_ERR;
        f->count=0;
        return(EOF);
    }
    c=*f->pointer;
    f->pointer++;
    return((unsigned char)c);
}
