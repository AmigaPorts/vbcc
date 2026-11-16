#include <ctype.h>

#undef isprint

int isprint(int c)
{ return __ctype[1+c]&151; }
