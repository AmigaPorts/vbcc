/*
** _main.c for vbcc-AmigaOS4/PPC
**
** __main() is called by the startup code. It runs the constructors
** and then main(). exit() runs the atexit() functions, _Exit() the
** destructors before leaving through __exit() in startup.o.
*/

#include <stdlib.h>

struct __exitfuncs *__firstexit;

extern void (*__CTOR_LIST__[])(void);
extern void (*__DTOR_LIST__[])(void);

extern int main(int,char **);
extern void __exit(int);


void _Exit(int returncode)
{
  void (**p)(void)=__DTOR_LIST__;
  int i;

  if(__DTOR_LIST__){
    /* call destructors in reverse order */
    for(i=1;p[i];i++);
    while(--i)
      p[i]();
  }
  __exit(returncode);
}


void exit(int returncode)
{
  static int exiting=0;
  struct __exitfuncs *p;

  if(!exiting){
    p=__firstexit;
    exiting=1;
    while(p){
      p->func();  /* execute atexit() routines */
      p=p->next;
    }
    _Exit(returncode);
  }
}


void __main(int argc,char **argv)
{
  void (**p)(void)=__CTOR_LIST__+1;

  if(__CTOR_LIST__){
    /* call constructors */
    while(*p)
      (*p++)();
  }
  exit(main(argc,argv));
}
