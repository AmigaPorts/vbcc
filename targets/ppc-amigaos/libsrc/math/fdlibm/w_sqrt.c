/* sqrt(x): wrapper for __ieee754_sqrt, setting errno on domain errors */
#include <errno.h>
#include "fdlibm.h"

double sqrt(double x)
{
	if(x<0.0) errno=EDOM;
	return __ieee754_sqrt(x);
}
