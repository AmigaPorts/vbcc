/*
** vbcc-AmigaOS4 version of fread.c
*/

#include <string.h>
#include "inc.h"

size_t fread(void *ptr,size_t size,size_t nmemb,FILE *f)
{
    size_t cnt,total=size*nmemb;
    char *p=ptr;
    long result;
    if(!f||!total) return(0);
    if((f->flags&(_READABLE|_WRITE|_EOF))!=_READABLE) return(0);
    f->flags|=_READ;
    if(!f->bufsize){if(f->flags&_UNBUF) f->bufsize=1; else f->bufsize=BUFSIZ;}
    if(!f->base){
        char *b;
        if(!(b=malloc(f->bufsize+((f->flags&_LINEBUF)?2:1))))
            return(0);
        f->base=b+1;
        f->pointer=f->base;
        f->count=0;
    }
    if(cnt=f->count){
    /*  Buffer lesen    */
        if(total<=cnt){
            memcpy(p,f->pointer,total);
            f->pointer+=total;f->count-=total;
            return(nmemb);
        }else{
            memcpy(p,f->pointer,cnt);
            total-=cnt;p+=cnt;
            f->count=0;
            f->pointer=f->base;
        }
    }
    if(total<f->bufsize){
    /*  small read: refill the buffer first */
        *p++=_fillbuf(f);
        if(f->flags&_EOF) return(cnt/size);
        total--;cnt++;
        if(f->count>=total){
            memcpy(p,f->pointer,total);
            f->pointer+=total;f->count-=total;
            return(nmemb);
        }else{
            memcpy(p,f->pointer,f->count);
            cnt+=f->count;
            f->count=0;
            return(cnt/size);
        }
    }
    result=__read(f->filehandle,p,total);
    if(result==-1){f->flags|=_ERR;return(cnt/size);}
    if(result<total){
        f->flags|=_EOF;
        return((cnt+result)/size);
    }else{
        return(nmemb);
    }
}
