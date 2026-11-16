#include <stdio.h>

char *gets(char *s)
/*  gefaehrlich...      */
{
    char *p=s;int k,err;
    err=stdin->flags&_ERR;
    while(1){
        k=getchar();
        if(k==EOF||k=='\n') break;
        *p++=k;
    }
    *p=0;
    if(stdin->flags&_ERR) return(0);
    stdin->flags|=err;
    if(p==s&&k==EOF) return(0);
    return(s);
}
