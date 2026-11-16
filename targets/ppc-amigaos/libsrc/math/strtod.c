#include <stdio.h>
#include <string.h>

double strtod(const char *nptr,char **endptr)
{
  FILE f;double a;
  f.flags=_READABLE|_READ;
  f.base=f.pointer=(char *)nptr;
  f.bufsize=f.count=strlen(nptr)+1;
  f.filehandle=0;
  fscanf(&f,"%lf",&a);
  if(endptr)
    *endptr=f.pointer;
  return a;
}
