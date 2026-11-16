#include <ctype.h>

#undef isgraph

int isgraph(int c)
{ return __ctype[1+c]&23; }
