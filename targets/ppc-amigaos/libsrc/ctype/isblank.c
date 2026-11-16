#include <ctype.h>

#undef isblank

int isblank(int c)
{ return c=='\t'||c==' '; }
