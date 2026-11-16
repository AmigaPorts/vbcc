#include <locale.h>
#include <limits.h>

static const struct lconv __lconv={".","","","","","","","","","",
                                   CHAR_MAX,CHAR_MAX,CHAR_MAX,CHAR_MAX,
                                   CHAR_MAX,CHAR_MAX,CHAR_MAX,CHAR_MAX};

struct lconv *__lconvptr=NULL;

struct lconv *localeconv(void)
{
    if(__lconvptr==NULL)
        __lconvptr=(struct lconv *)&__lconv;
    return(__lconvptr);
}
