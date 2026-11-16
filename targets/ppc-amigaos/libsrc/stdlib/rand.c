#include <stdlib.h>

static unsigned int a=1;

int rand(void)
{
  a=a*1103515245+12345;
  return (a>>16)&RAND_MAX;
}

void srand(unsigned int seed)
{ a=seed; }
