#include <errno.h>
#include <string.h>

extern char *_errors[];

char *strerror(int n)
{
    if(n>ERANGE) n=0;
    return(_errors[n]);
}

