#include "inc.h"

int fflush(FILE *f)
{
    if(f){
        _flushbuf(f);
    }else{
        f=__firstfile;
        while(f){
            if(f->flags&_WRITE)_flushbuf(f);
            f=f->next;
        }
    }
    return(0);
}
