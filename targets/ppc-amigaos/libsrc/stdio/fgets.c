#include <stdio.h>

char *fgets(char *s,int n,FILE *f)
{
    char *p=s;int k,err;
    if(n<=0) return(s);
    err=f->flags&_ERR;
    n--;
    do{
        k=getc(f);
        if(k==EOF) break;
        *p++=k;
    }while(--n&&k!='\n');
    *p=0;
    if(f->flags&_ERR) return(0);
    f->flags|=err;
    if(p==s) return(0); else return(s);
}
