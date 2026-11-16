#include <string.h>

char *strcat(char *s1,const char *s2)
{
    char *d=s1,c;
    while(*s1) s1++;
    do{
        c=*s2++;
        *s1++=c;
    }while(c);
    return(d);
}
