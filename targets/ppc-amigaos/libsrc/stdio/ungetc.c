#include <stdlib.h>
#include <stdio.h>

int ungetc(int c,FILE *f)
{
    if(!f) return(EOF);
    if((f->flags&(_READABLE|_WRITE|_EOF))!=_READABLE) return(EOF);
    f->flags|=_READ;
    if(!f->bufsize){if(f->flags&_UNBUF) f->bufsize=1; else f->bufsize=BUFSIZ;}
    if(!f->base){
        char *p=malloc(f->bufsize+((f->flags&_LINEBUF)?2:1));
        if(!p) return(EOF);
        f->base=p+1;
        f->pointer=f->base;
    }
    if(f->pointer<f->base){
    /*  Buffer voll und bereits ein Zeichen reingestopft, also wird es  */
    /*  ueberschrieben                                                  */
        return(*f->pointer=c);
    }
    f->count++;
    return(*--f->pointer=c);
}
