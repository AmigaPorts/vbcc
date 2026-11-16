#include <exec/types.h>

ULONG FastRand(ULONG seed)
{ ULONG a=seed<<1;
  if((LONG)seed<=0)
    a^=0x1d872b41;
  return a;
}

