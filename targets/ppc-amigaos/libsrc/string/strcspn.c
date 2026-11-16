#include <string.h>

size_t strcspn(const char *s1,const char *s2)
{
    size_t n=0;
    while(*s1&&!strchr(s2,*s1++)) n++;
    return(n);
}
