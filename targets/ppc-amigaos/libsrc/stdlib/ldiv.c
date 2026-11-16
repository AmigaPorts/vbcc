#include <stdlib.h>

ldiv_t ldiv(long num,long denom)
{
    ldiv_t r;
    r.quot=num/denom;
    r.rem=num-denom*r.quot;
    return(r);
}
