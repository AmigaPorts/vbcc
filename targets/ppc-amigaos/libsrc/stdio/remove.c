/*
** vbcc-AmigaOS4 version of remove.c
*/

#include <stdio.h>
#include <proto/dos.h>

int remove(const char *name)
{
    return(!IDOS->Delete((STRPTR)name));
}
