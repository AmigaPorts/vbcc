#include <stdio.h>
#include <stdarg.h>
#include <limits.h>

int sprintf(char *s,const char *format,...)
{ int retval;
  FILE buffer;
  va_list args;
  va_start(args,format);
  buffer.base=buffer.pointer=s;
  buffer.flags=_WRITEABLE|_WRITE;
  buffer.count=buffer.bufsize=INT_MAX;
  buffer.filehandle=0;
  retval=vfprintf(&buffer,format,args);
  fputc('\0',&buffer);
  va_end(args);
  return retval;
}
