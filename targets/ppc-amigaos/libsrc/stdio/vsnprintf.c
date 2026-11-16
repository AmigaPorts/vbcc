#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <limits.h>

int vsnprintf(char *s,size_t n,const char *format,va_list args)
{
  int retval;
  FILE buffer;
  if((int)n<0){
    errno=EINVAL;
    return -1;
  }
  if(s==NULL)
    n=0;
  buffer.base=buffer.pointer=s;
  buffer.flags=_WRITEABLE|_WRITE;
  buffer.count=buffer.bufsize=n?n-1:0;
  buffer.filehandle=0;
  retval=vfprintf(&buffer,format,args);
  if(retval>=n-1){
    if(n)
      s[n-1]='\0';
  }
  else
    fputc('\0',&buffer);
  return retval;
}
