#include <ctype.h>

#undef isupper

int isupper(int c)
{ return __ctype[1+c]&1; }
