/*
** vbcc-AmigaOS4 version of fwrite.c
*/

#include <string.h>
#include "inc.h"

size_t fwrite(void *ptr,size_t size,size_t nmemb,FILE *f)
{
    size_t total=size*nmemb;char *p=ptr;long result;
    if(!f||!total) return(0);
    if((f->flags&(_WRITEABLE|_READ|_EOF))!=_WRITEABLE) return(0);
    f->flags|=_WRITE;
    if(!f->bufsize){if(f->flags&_UNBUF) f->bufsize=1; else f->bufsize=BUFSIZ;}
    if(!f->base){
        char *b;
        if(!(b=malloc(f->bufsize+((f->flags&_LINEBUF)?2:1))))
            return(0);
        f->base=b+1;
        f->pointer=f->base;
        f->count=f->bufsize;
    }
    if(!f->count) _flushbuf(f);
    if(total<f->count){
    /*  fits into the buffer    */
        memcpy(f->pointer,p,total);
        f->pointer+=total;f->count-=total;
        f->flags|=_WRITE;
        return(nmemb);
    }
    _flushbuf(f);
    result=__write(f->filehandle,p,total);
    if(result==-1){f->flags|=_ERR;return(0);}
    return(result/size);
}
