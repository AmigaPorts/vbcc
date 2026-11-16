#include <stdio.h>

int __v0sprintf(char *d,const char *s)
{
    int n=-1;char c;
    do{
        c=*s++;
        *d++=c;
        n++;
    }while(c);
    return(n);
}

