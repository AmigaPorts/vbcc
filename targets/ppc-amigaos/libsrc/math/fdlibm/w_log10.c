/* log10(x): wrapper for __ieee754_log10, setting errno for x<=0 */
#include <errno.h>
#include "fdlibm.h"

double log10(double x)
{
	if(x==0.0) errno=ERANGE;
	else if(x<0.0) errno=EDOM;
	return __ieee754_log10(x);
}
