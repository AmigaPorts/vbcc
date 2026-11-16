/*
** vbcc-AmigaOS4 version of fopen.c
*/

#include "inc.h"


/* initializes a FILE structure and opens the file */
FILE *__open_file(const char *name,const char *mode,FILE *f)
{
    long amigamode;int append;
    if(*mode=='w') amigamode=MODE_NEWFILE; else amigamode=MODE_OLDFILE;
    if(*mode=='a') {append=1;amigamode=MODE_READWRITE;} else append=0;
    f->count=0;
    f->base=0;
    f->bufsize=0;
    f->prev=0;
    f->next=0;
    if(*mode=='r') f->flags=_READABLE; else f->flags=_WRITEABLE;
    if(*++mode=='b') mode++;
    if(*mode=='+') f->flags|=_READABLE|_WRITEABLE;
    f->filehandle=(char *)IDOS->Open((STRPTR)name,amigamode);
    if(!f->filehandle){free(f);return(0);}
    if(!f->filehandle){free(f);return(0);}
    if((f->flags&_WRITEABLE)&&amigamode!=MODE_NEWFILE){
        /* get exclusive access for writing */
        if(!IDOS->ChangeMode(CHANGE_FH,(BPTR)f->filehandle,EXCLUSIVE_LOCK)){
            IDOS->Close((BPTR)f->filehandle);
            free(f);
            return(0);
        }
    }
    if(IDOS->IsInteractive((BPTR)f->filehandle)) f->flags|=_LINEBUF|_ISTTY;
    if(__lastfile){
        __lastfile->next=f;f->prev=__lastfile;__lastfile=f;
    }else{
        __firstfile=__lastfile=f;
    }
    if(append) fseek(f,0,SEEK_END);
    return(f);
}


/* opens files */
FILE *fopen(const char *name,const char *mode)
{
    FILE *f;
    if(!(f=malloc(sizeof(FILE)))) return(0);
    return(__open_file(name,mode,f));
}


/* close all open files on exit */
void _EXIT_2_fopen(void)
{
    while(__firstfile&&!fclose(__firstfile));
}
