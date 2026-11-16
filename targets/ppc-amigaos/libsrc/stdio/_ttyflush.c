/*
** vbcc-AmigaOS4 version of _ttyflush.c
*/

#include "inc.h"

/* flush all interactive output streams */
void _ttyflush(void)
{
    FILE *f;

    for(f=__firstfile;f;f=f->next){
        if((f->flags&(_ISTTY|_WRITE))==(_ISTTY|_WRITE)&&f->filehandle)
            _flushbuf(f);
    }
}
