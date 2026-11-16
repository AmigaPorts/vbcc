/* The version an auto-opened library is opened with, one per "lib" line of
   auto.tab (-DBASE=<base variable>).  0 accepts any version; a program can
   ask for more by defining _<base>Ver itself.  */
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)

unsigned long CAT(CAT(_, BASE), Ver) = 0;
