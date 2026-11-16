#include <string.h>

size_t strxfrm(char *s1,const char *s2,size_t n)
{
    size_t len=strlen(s2);
    if(n){
        size_t l=len<n?len:n-1;
        memcpy(s1,s2,l);
        s1[l]=0;
    }
    return(len);
}
