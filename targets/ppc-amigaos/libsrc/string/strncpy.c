#include <string.h>

#undef strncpy

char *strncpy(char *s1,const char *s2,size_t n)
{
    char *d=s1;
    while (n--)
      if (*s1++=*s2)
        s2++;
    return(d);
}
