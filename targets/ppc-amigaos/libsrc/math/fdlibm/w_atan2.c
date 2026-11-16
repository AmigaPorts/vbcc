/* atan2(y,x): wrapper for __ieee754_atan2, which handles all cases */
#include "fdlibm.h"

double atan2(double y, double x)
{
	return __ieee754_atan2(y,x);
}
