/* exp(x): wrapper for __ieee754_exp, setting errno on overflow */
#include <errno.h>
#include "fdlibm.h"

static const double
o_threshold =  7.09782712893383973096e+02,  /* 0x40862E42, 0xFEFA39EF */
u_threshold = -7.45133219101941108420e+02;  /* 0xc0874910, 0xD52D3051 */

double exp(double x)
{
	if(x==x&&(x>o_threshold||x<u_threshold)) errno=ERANGE;
	return __ieee754_exp(x);
}
