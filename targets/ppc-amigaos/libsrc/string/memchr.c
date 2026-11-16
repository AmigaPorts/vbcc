#include <string.h>

void *memchr(const void *s,int c,size_t n)
{
    char *p=(char *)s;
    while(n) {n--;if(*p==c) return(p); else p++;}
    return(0);
}
