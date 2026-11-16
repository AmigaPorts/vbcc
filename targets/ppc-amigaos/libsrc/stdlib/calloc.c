#include <stddef.h>
#include <stdlib.h>

/*  ob das so passt??   */
void *calloc(size_t nmemb,size_t size)
{
    size_t len=nmemb*size;void *mem;
    if(!(mem=malloc(len))) return(0);
    memset(mem,0,len);
    return(mem);
}

