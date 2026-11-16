#include <signal.h>

/*  hmm...nicht die allerbeste Implementation...    */

void (*signal(int sig,void (*handler)(int)))(int)
{
    return(SIG_ERR);
}

