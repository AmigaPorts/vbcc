#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <inttypes.h>

intmax_t strtoimax(const char *nptr,char **endptr,int base)
{ const char *p=nptr;
  char *q;
  uintmax_t r;
  while(isspace((unsigned char)*p))
    p++;
  r=strtoull(p,&q,base);
  if(endptr!=NULL)
  { if(q==p)
      *endptr=(char *)nptr;
    else
      *endptr=q;
  }
  if(*p=='-')
  { if((intmax_t)r>0)
    { errno=ERANGE;
      return INTMAX_MIN; }
    else
      return r;
  }else
  { if((intmax_t)r<0)
    { errno=ERANGE;
      return INTMAX_MAX; }
    else
      return r;
  }
}
