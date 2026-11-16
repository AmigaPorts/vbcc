/*
** vbcc-AmigaOS4 version of system.c
*/

#include <stdlib.h>
#include <utility/tagitem.h>
#include <proto/dos.h>

static struct TagItem notags[]={
  { TAG_DONE,0 }
};

int system(const char *string)
{
  if(string==NULL)
    return(1);  /* a command processor is available */
  return(IDOS->SystemTagList(string,notags));
}
