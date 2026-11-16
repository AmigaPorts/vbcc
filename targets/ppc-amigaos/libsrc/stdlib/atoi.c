#include <stdlib.h>

#undef atoi

int atoi(const char *s)
{
    return(strtol(s,(char **)NULL,10));
}
