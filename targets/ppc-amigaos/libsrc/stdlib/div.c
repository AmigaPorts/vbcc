#include <stdlib.h>

div_t div(int num,int denom)
{
    div_t r;
    r.quot=num/denom;
    r.rem=num-denom*r.quot;
    return(r);
}
