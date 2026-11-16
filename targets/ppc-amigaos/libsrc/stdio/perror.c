#include <stdio.h>
#include <errno.h>

extern char *_errors[];

void perror(const char *s)
{
    fprintf(stderr,"%s: %s\n",s,_errors[errno]);
}
