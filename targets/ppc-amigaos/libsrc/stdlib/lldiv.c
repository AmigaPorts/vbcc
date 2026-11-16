#include <stdlib.h>

lldiv_t lldiv(long long num,long long denom)
{
    lldiv_t r;
    r.quot=num/denom;
    r.rem=num-denom*r.quot;
    return(r);
}
