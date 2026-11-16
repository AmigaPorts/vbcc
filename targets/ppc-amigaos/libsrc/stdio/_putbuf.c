/*
** vbcc-AmigaOS4 version of _putbuf.c
*/

#include "inc.h"

/* write data from buffer */
/* inserts c as a new character */
int _putbuf(int c,FILE *f)
{
    _chkabort();
    if(!f) return(EOF);
    if((f->flags&(_WRITEABLE|_READ|_EOF))!=_WRITEABLE) return(EOF);
    if(!f->bufsize){if(f->flags&_UNBUF) f->bufsize=1; else f->bufsize=BUFSIZ;}
    if(!f->base){
        char *p;
        if(!(p=malloc(f->bufsize+((f->flags&_LINEBUF)?2:1))))
            return(EOF);
        f->base=p+1;
    }else{
        if(f->filehandle){
            int len;
            if((f->flags&_LINEBUF)&&c=='\n'){
                *f->pointer++=c;
                return(_flushbuf(f));
            }
            len=f->pointer-f->base;
            if(__write(f->filehandle,f->base,len)!=len){
                f->flags|=_ERR;
                return(EOF);
            }
        }else return(0);
    }
    f->flags|=_WRITE;
    *f->base=c;
    f->pointer=f->base+1;
    f->count=f->bufsize-1;
    return(0);
}
