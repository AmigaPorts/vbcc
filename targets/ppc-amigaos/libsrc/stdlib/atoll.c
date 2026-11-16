#include <stdlib.h>

#undef atoll

long long atoll(const char *s)
{
    return(strtoll(s,(char **)NULL,10));
}
