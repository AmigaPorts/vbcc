/* pow(x,y): wrapper for __ieee754_pow, setting errno like the SVID/XOPEN
 * modes of fdlibm's w_pow.c: EDOM for 0**negative and negative**non-integer,
 * ERANGE on overflow and underflow. */
#include <errno.h>
#include "fdlibm.h"

static int finite(double x)
{
	int32_t hx;
	GET_HIGH_WORD(hx,x);
	return (int)((uint32_t)((hx&0x7fffffff)-0x7ff00000)>>31);
}

double pow(double x, double y)
{
	double z=__ieee754_pow(x,y);
	if(y!=y||x!=x) return z;
	if(x==0.0){
	    if(finite(y)&&y<0.0) errno=EDOM;	/* pow(0.0,negative) */
	    return z;
	}
	if(!finite(z)){
	    if(finite(x)&&finite(y))
	        errno=(z!=z)?EDOM:ERANGE;	/* neg**non-int, overflow */
	}else if(z==0.0&&finite(x)&&finite(y))
	    errno=ERANGE;			/* underflow */
	return z;
}
