/*
** vbcc-AmigaOS4 version of fclose.c
*/

#include "inc.h"

/* closes files */
int fclose(FILE *f)
{
    if(!f) return(EOF);
    if(!f->filehandle) return(EOF);
    fflush(f);
    if(f->filehandle!=_stdin&&f->filehandle!=_stdout&&f->filehandle!=_stderr)
        IDOS->Close((BPTR)f->filehandle);
    if(f->prev) f->prev->next=f->next; else __firstfile=f->next;
    if(f->next) f->next->prev=f->prev; else __lastfile=f->prev;
    if(f->base&&!(f->flags&_NOTMYBUF)) free(f->base-1);
    free(f);
    return(0);
}
