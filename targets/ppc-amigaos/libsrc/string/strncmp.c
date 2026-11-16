#include <string.h>

#undef strncmp

int strncmp(const char *s1,const char *s2,size_t n)
/*  gehoert das so? */
{
    if(n==0) return 0;
    while(--n&&*s1==*s2){
        if(!*s1) return(0);
        s1++;s2++;
    }
    return(*(unsigned char *)s1-*(unsigned char *)s2);
}
