#include <stdio.h>
#include <stdarg.h>
#include <errno.h>

int snprintf(char *s,size_t n,const char *format,...)
{
  int retval;
  FILE buffer;
  va_list vl;
  if((int)n<0){
    errno=EINVAL;
    return -1;
  }
  if(s==NULL)
    n=0;
  va_start(vl,format);
  buffer.base=buffer.pointer=s;
  buffer.flags=_WRITEABLE|_WRITE;
  buffer.count=buffer.bufsize=n?n-1:0;
  buffer.filehandle=0;
  retval=vfprintf(&buffer,format,vl);
  if(retval>=n-1){
    if(n)
      s[n-1]='\0';
  }
  else
    fputc('\0',&buffer);
  return retval;
}
