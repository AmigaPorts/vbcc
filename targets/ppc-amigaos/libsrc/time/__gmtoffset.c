/*
** Greenwich mean time offset (in minutes)
** Initialized from the current locale on startup.
*/

#include <proto/exec.h>
#include <proto/locale.h>

long __gmtoffset;


void _INIT_5_time(void)
{
  struct Library *LocaleBase;
  struct LocaleIFace *ILocale;
  struct Locale *loc;

  if(LocaleBase=IExec->OpenLibrary("locale.library",0)){
    if(ILocale=(struct LocaleIFace *)IExec->GetInterface(LocaleBase,"main",1,NULL)){
      loc=ILocale->OpenLocale(NULL);
      __gmtoffset=loc->loc_GMTOffset;
      ILocale->CloseLocale(loc);
      IExec->DropInterface((struct Interface *)ILocale);
    }
    IExec->CloseLibrary(LocaleBase);
  }
}
