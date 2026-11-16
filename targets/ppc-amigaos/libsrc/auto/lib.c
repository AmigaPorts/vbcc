/* Auto-open stub for one library, compiled once per "lib" line of auto.tab
   with -DBASE=<base variable> -DNAME=<library name>.  */
#include <proto/exec.h>
#include <stdlib.h>

#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define BASEVER CAT(CAT(_, BASE), Ver)

struct Library *BASE;
extern unsigned long BASEVER;

void CAT(_INIT_5_, BASE)(void)
{
  BASE = IExec->OpenLibrary(NAME, BASEVER);
  if (BASE == NULL)
    exit(20);
}

void CAT(_EXIT_5_, BASE)(void)
{
  if (BASE)
    IExec->CloseLibrary(BASE);
}
