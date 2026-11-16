#include <stdlib.h>

#undef atol

long atol(const char *s)
{
    return(strtol(s,(char **)NULL,10));
}
