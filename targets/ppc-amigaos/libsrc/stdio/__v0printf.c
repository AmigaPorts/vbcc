#include <stdio.h>

int __v0printf(const char *s)
{
    int n=0;
    while(*s){
        if(putchar(*s)==EOF) return(EOF);
        s++;n++;
    }
    return(n);
}
