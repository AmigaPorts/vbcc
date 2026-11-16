/*
** vbcc-AmigaOS4 version of newmalloc.c
** utilizes the Amiga pooled memory functions
*/

#include <stdlib.h>
#include <string.h>
#include <proto/exec.h>


size_t _nalloc=16384;
void *_first_mlist=0;

void _EXIT_1_malloc(void)
/*  Gibt allen Speicher frei    */
{
    if(_first_mlist) IExec->DeletePool(_first_mlist);
}
void *malloc(size_t nbytes)
{
    size_t *p;
    if(!nbytes) return(0);
    if(!_first_mlist) _first_mlist=IExec->CreatePool(0,_nalloc,_nalloc);
    if(!_first_mlist) return(0);
    p=IExec->AllocPooled(_first_mlist,nbytes+sizeof(size_t));
    if(!p) return(0);
    *p=nbytes+sizeof(size_t);
    return(p+1);
}
void free(void *ap)
{
    size_t *p=ap;
    if(!p||!_first_mlist) return;
    p--;
    IExec->FreePooled(_first_mlist,p,*p);
}

void *realloc(void *old,size_t nsize)
{
    size_t osize;void *new;
    if(!old) return(malloc(nsize));
    osize=*((size_t *)old-1);
    if(new=malloc(nsize)){
        memcpy(new,old,osize>nsize ? nsize:osize);
        free(old);
    }
    return(new);
}
