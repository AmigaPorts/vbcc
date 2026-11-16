/*
** private stdio header for vclib (ppc-amigaos)
**
** The FILE structure and the flags are those of the public <stdio.h>:
**   0 filehandle, 4 pointer, 8 base, 12 next, 16 prev,
**  20 count, 24 flags, 28 bufsize  (sizeof(FILE)==32)
**
** The __read/__write/__seek macros are those that <stdio.h> provides
** under __BUILD_LIB, except that the SDK used here names IDOS->Seek()
** OBSOLETESeek().
*/

#ifndef __INC_H
#define __INC_H 1

#include <stddef.h>
#include <stdio.h>
#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>

#include <dos/dos.h>
#include <proto/dos.h>

#undef __read
#undef __write
#undef __seek
#define __read(x,y,z) IDOS->Read((BPTR)(x),y,(long)z)
#define __write(x,y,z) IDOS->Write((BPTR)(x),y,(long)z)
#define __seek(x,y,z) IDOS->OBSOLETESeek((BPTR)(x),y,z)  /* Seek() in older SDKs */

extern FILE *__firstfile,*__lastfile;
extern char *_stdin,*_stdout,*_stderr;

void _chkabort(void);
FILE *__open_file(const char *,const char *,FILE *);

#endif
