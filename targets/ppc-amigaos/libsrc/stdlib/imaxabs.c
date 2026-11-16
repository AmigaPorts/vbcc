#include <inttypes.h>

intmax_t imaxabs(intmax_t x)
{
    if(x>=0) return(x); else return(-x);
}
