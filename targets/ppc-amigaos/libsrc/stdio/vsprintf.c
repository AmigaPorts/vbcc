#include <stdio.h>
#include <stdarg.h>
#include <limits.h>

int vsprintf(char *s,const char *format,va_list args)
{
  int retval;
  FILE buffer;
  buffer.base=buffer.pointer=s;
  buffer.flags=_WRITEABLE|_WRITE;
  buffer.bufsize=INT_MAX;
  buffer.count=INT_MAX;
  buffer.filehandle=0;
  retval=vfprintf(&buffer,format,args);
  fputc('\0',&buffer);
  return retval;
}
