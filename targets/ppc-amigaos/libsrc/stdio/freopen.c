/*
** vbcc-AmigaOS4 version of freopen.c
*/

#include "inc.h"


/* closes the stream and reopens it with a new file */
FILE *freopen(const char *name,const char *mode,FILE *f)
{
    if(f->filehandle){
        fflush(f);
        if(f->filehandle!=_stdin&&f->filehandle!=_stdout&&f->filehandle!=_stderr)
            IDOS->Close((BPTR)f->filehandle);
        if(f->prev) f->prev->next=f->next; else __firstfile=f->next;
        if(f->next) f->next->prev=f->prev; else __lastfile=f->prev;
        if(f->base&&!(f->flags&_NOTMYBUF)) free(f->base-1);
    }
    return(__open_file(name,mode,f));
}
