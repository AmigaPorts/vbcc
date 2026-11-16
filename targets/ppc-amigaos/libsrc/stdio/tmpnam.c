/*
** vbcc-AmigaOS4 version of tmpnam.c
*/

#include <stdio.h>
#include <proto/exec.h>
#include <dos/dosextens.h>

char *tmpnam(char *s)
{
    static char lastname[L_tmpnam];
    static int lastnum=0;
    struct Process *proc=(struct Process *)IExec->FindTask(NULL);
    unsigned long clinum=proc->pr_CliNum;

    if(!s) s=lastname;
    sprintf(s,"T:t_%d_%d",clinum,lastnum++);
    return(s);
}
