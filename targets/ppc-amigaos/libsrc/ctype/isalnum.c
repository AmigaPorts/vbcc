#include <ctype.h>

#undef isalnum

int isalnum(int c)
{ return __ctype[1+c]&7; }
