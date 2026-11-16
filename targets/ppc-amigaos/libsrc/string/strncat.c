#include <string.h>

char *strncat(char *d,const char *s,size_t n)
{
    char *dm=d;
    if(n!=0){
        while(*d) d++;
        do{
            if(!(*d=*s++)) break;
            d++;
        }while(--n);
        *d=0;
    }
    return(dm);
}

