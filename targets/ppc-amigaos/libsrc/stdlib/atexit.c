#include <stdlib.h>

extern struct __exitfuncs *__firstexit;

int atexit(void (*func)(void))
{
    struct __exitfuncs *p;
    if(!(p=malloc(sizeof(struct __exitfuncs)))) return(1);
    p->func=func;
    p->next=__firstexit;
    __firstexit=p;
    return(0);
}

