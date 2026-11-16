#include <locale.h>
#include <proto/exec.h>
#include <proto/locale.h>

extern struct lconv *__lconvptr;
struct lconv __lconv;

char *setlocale(int mode,const char *name)
{
    struct Library *LocaleBase;
    struct LocaleIFace *ILocale;
    struct Locale *loc;

    if(name==NULL||(name[0]=='C'&&name[1]=='\0')){
        __lconvptr=NULL;
        return("C");
    }
    if(*name=='\0'&&(mode==LC_ALL||mode==LC_NUMERIC)){
        if(LocaleBase=IExec->OpenLibrary("locale.library",0)){
            if(ILocale=(struct LocaleIFace *)IExec->GetInterface(LocaleBase,"main",1,NULL)){
                loc=ILocale->OpenLocale(NULL);
                __lconvptr=&__lconv;
                __lconv.decimal_point=loc->loc_DecimalPoint;
                __lconv.thousands_sep=loc->loc_GroupSeparator;
                __lconv.grouping=(char *)loc->loc_Grouping;
                __lconv.int_curr_symbol=loc->loc_MonIntCS;
                __lconv.currency_symbol=loc->loc_MonCS;
                __lconv.mon_decimal_point=loc->loc_MonDecimalPoint;
                __lconv.mon_thousands_sep=loc->loc_MonGroupSeparator;
                __lconv.mon_grouping=(char *)loc->loc_MonGrouping;
                __lconv.positive_sign=loc->loc_MonPositiveSign;
                __lconv.negative_sign=loc->loc_MonNegativeSign;
                __lconv.int_frac_digits=loc->loc_MonFracDigits;
                __lconv.frac_digits=loc->loc_MonFracDigits;
                __lconv.p_cs_precedes=loc->loc_MonPositiveCSPos;
                __lconv.p_sep_by_space=loc->loc_MonPositiveSpaceSep;
                __lconv.n_cs_precedes=loc->loc_MonNegativeCSPos;
                __lconv.n_sep_by_space=loc->loc_MonNegativeSpaceSep;
                __lconv.p_sign_posn=loc->loc_MonPositiveSignPos;
                __lconv.n_sign_posn=loc->loc_MonNegativeSignPos;
                ILocale->CloseLocale(loc);
                IExec->DropInterface((struct Interface *)ILocale);
            }
            IExec->CloseLibrary(LocaleBase);
            return(loc->loc_LanguageName);
        }
    }
    return(NULL);
}
