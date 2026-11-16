#include <inttypes.h>

imaxdiv_t imaxdiv(intmax_t num,intmax_t denom)
{
    imaxdiv_t r;
    r.quot=num/denom;
    r.rem=num%denom;
    if(denom<0) r.rem=-r.rem;
    return(r);
}
