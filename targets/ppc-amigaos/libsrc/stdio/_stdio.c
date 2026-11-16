/*
** vbcc-AmigaOS4 version of _stdio.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <proto/dos.h>

extern BPTR _stdin,_stdout,_stderr;   /* set up by the startup code */
extern FILE *__firstfile,*__lastfile;

FILE *stdin,*stdout,*stderr;

/* set up the standard streams */
void _INIT_2_stdio(void)
{
    stdin=malloc(sizeof(FILE));
    stdout=malloc(sizeof(FILE));
    stderr=malloc(sizeof(FILE));
    if(!stdin||!stdout||!stderr) exit(20);
    stdin->filehandle=(char *)_stdin;
    stdin->flags=_READABLE;
    if(IDOS->IsInteractive(_stdin)) stdin->flags|=_ISTTY|_UNBUF;
    stdout->filehandle=(char *)_stdout;
    stdout->flags=_WRITEABLE;
    if(IDOS->IsInteractive(_stdout)) stdout->flags|=_ISTTY|_LINEBUF;
    stderr->filehandle=(char *)_stderr;
    stderr->flags=_WRITEABLE;
    if(IDOS->IsInteractive(_stderr)) stderr->flags|=_ISTTY|_LINEBUF;
    stdin->pointer=stdout->pointer=stderr->pointer=0;
    stdin->base=stdout->base=stderr->base=0;
    stdin->count=stdout->count=stderr->count=0;
    stdin->bufsize=stdout->bufsize=stderr->bufsize=0;
    stdin->prev=0;
    stdin->next=stdout;
    stdout->prev=stdin;
    stdout->next=stderr;
    stderr->prev=stdout;
    stderr->next=0;
    __firstfile=stdin;
    __lastfile=stderr;
}

/* flush all buffers on exit */
void _EXIT_3_stdio(void)
{
    fflush(NULL);
}
