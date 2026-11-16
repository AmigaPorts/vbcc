/*
** vbcc-AmigaOS4 version of rename.c
*/

#include <stdio.h>
#include <proto/dos.h>

int rename(const char *old,const char *new)
{
    return(!IDOS->Rename((STRPTR)old,(STRPTR)new));
}
