#include <stdio.h>

int fputs(const char *s,FILE *f)
/*  muss fputs wirklich nur irgendeinen pos. Wert zurueckgeben? */
{
    while(*s){
        if(__putc(*s,f)==EOF) return(EOF);
        s++;
    }
    return(1);
}
