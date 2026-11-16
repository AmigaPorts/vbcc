#include <stdio.h>

int __v0fprintf(FILE *f,const char *s)
{
    int n=0;
    while(*s){
        if(putc(*s,f)==EOF) return(EOF);
        s++;n++;
    }
    return(n);
}

