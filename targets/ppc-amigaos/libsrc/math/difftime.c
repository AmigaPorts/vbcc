#include <time.h>

#undef difftime

double difftime(time_t a,time_t b)
{ return a-b; }
