#include <math.h>

double acos(double x)
{
  return (fabs(atan2(sqrt(1-x*x),x)));
}
