#include <string.h>

char *strrchr(const char *s,int c)
{
    char *p=0;
    while(*s){
        if(*s==c) p=(char *)s;
        s++;
    }
    return(c?p:(char *)s);
}
