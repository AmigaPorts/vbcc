/* Auto-obtained interface, compiled once per "iface" line of auto.tab with
   -DIFACE=<interface variable> -DBASE=<library base> -DNAME=<interface name>
   -DVERSION=<interface version>.  */
#include <proto/exec.h>
#include <stdlib.h>

#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)

struct Interface *IFACE;
extern struct Library *BASE;

void CAT(_INIT_6_, IFACE)(void)
{
  IFACE = IExec->GetInterface(BASE, NAME, VERSION, NULL);
  if (IFACE == NULL)
    exit(20);
}

void CAT(_EXIT_6_, IFACE)(void)
{
  if (IFACE)
    IExec->DropInterface(IFACE);
}
