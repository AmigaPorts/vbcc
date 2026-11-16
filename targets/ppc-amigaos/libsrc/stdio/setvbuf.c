#include <stdlib.h>
#include <stdio.h>

int setvbuf(FILE *f,char *buf,int mode,size_t size)
{
    if(f->flags&(_READ|_WRITE)) return(EOF);
    if(mode==_IONBF){
        f->flags|=_UNBUF;
        size=1;
        buf=NULL;
    }else{
        f->flags&=~_UNBUF;
        if(size<3) return(EOF);
    }
    if(mode==_IOLBF) f->flags|=_LINEBUF; else f->flags&=~_LINEBUF;
    if(buf){
        size-=(f->flags&_LINEBUF)?2:1;  /* reserve space for ungetc() */
        f->base=buf+1;
        f->flags|=_NOTMYBUF;
    }else{
        char *p=malloc(size+((f->flags&_LINEBUF)?2:1));
        f->flags&=~_NOTMYBUF;
        if(!p) return(EOF);
        f->base=p+1;
    }
    f->bufsize=size;
    f->pointer=f->base;
    f->count=0;
    return(0);
}
