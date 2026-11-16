#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <ctype.h>
#include <locale.h>

/* a little macro to make life easier */

#define OUT(c)  do                           \
                { if(fputc((c),stream)==EOF) \
                    return outcount;         \
                  outcount++;                \
                }while(0)

#define BITSPERBYTE CHAR_BIT

#define MININTSIZE (sizeof(unsigned long long)*BITSPERBYTE/3+1)
#define MINPOINTSIZE (sizeof(void *)*BITSPERBYTE/4+1)
#define REQUIREDBUFFER (MININTSIZE>MINPOINTSIZE?MININTSIZE:MINPOINTSIZE)

#define ALTERNATEFLAG 1  /* '#' is set */
#define ZEROPADFLAG   2  /* '0' is set */
#define LALIGNFLAG    4  /* '-' is set */
#define BLANKFLAG     8  /* ' ' is set */
#define SIGNFLAG      16 /* '+' is set */

/* subtypes besides 'h', 'l' and 'L' */
#define LLONGTYPE     1  /* 'll' or 'j' */
#define CHARTYPE      2  /* 'hh' */


int vfprintf(FILE *stream,const char *format,va_list args)
{
  size_t outcount=0;

  while(*format)
  {
    if(*format=='%')
    {
      static const char flagc[]=
      { '#','0','-',' ','+' };
      static const char lowertabel[]=
      { '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f' };
      static const char uppertabel[]=
      { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
      size_t width=0,preci=ULONG_MAX,flags=0; /* Specifications */
      char type;
      int subtype='i';
      char buffer1[2];             /* Signs and that like */
      char buffer[REQUIREDBUFFER]; /* The body */
      char *buffer2=buffer;        /* So we can set this to any other strings */
      size_t size1=0,size2=0;      /* How many chars in buffer? */
      const char *ptr=format+1;    /* pointer to format string */
      size_t i,pad;                /* Some temporary variables */
      struct lconv *lc=localeconv();

      do /* read flags */
        for(i=0;i<sizeof(flagc);i++)
          if(flagc[i]==*ptr)
          { flags|=1<<i;
            ptr++;
            break; }
      while(i<sizeof(flagc));

      if(*ptr=='*') /* read width from arguments */
      { signed int a;
        ptr++;
        a=va_arg(args,signed int);
        if(a<0)
        { flags|=LALIGNFLAG;
          width=-a; }
        else
          width=a;
      }else
        while(isdigit((unsigned char)*ptr))
          width=width*10+(*ptr++-'0');

      if(*ptr==*lc->decimal_point)
      { ptr++;
        if(*ptr=='*') /* read precision from arguments */
        { signed int a;
          ptr++;
          a=va_arg(args,signed int);
          if(a>=0)
            preci=a;
        }else
        { preci=0;
          while(isdigit((unsigned char)*ptr))
            preci=preci*10+(*ptr++-'0');
        }
      }

      if(*ptr=='h'||*ptr=='l'||*ptr=='L'||*ptr=='j'||*ptr=='z'||*ptr=='t')
        subtype=*ptr++;
      if(subtype=='h'&&*ptr=='h')
      { subtype=CHARTYPE;
        ptr++; }
      if(subtype=='l'&&*ptr=='l')
      { subtype=LLONGTYPE;
        ptr++; }
      if(subtype=='j')
        subtype=LLONGTYPE;
      if(subtype=='z')
        subtype='l';
      if(subtype=='t')
        subtype='i';

      type=*ptr++;

      switch(type)
      { case 'd':
        case 'i':
        case 'o':
        case 'p':
        case 'u':
        case 'x':
        case 'X':
        { unsigned long long v;
          const char *tabel;
          int base;

          if(type=='p')
          { subtype='l'; /* This is written as %#lx */
            type='x';
            flags|=ALTERNATEFLAG; }

          if(type=='d'||type=='i') /* These are signed */
          { signed long long v2;
            if(subtype==LLONGTYPE)
              v2=va_arg(args,signed long long);
            else if(subtype=='l')
              v2=va_arg(args,signed long);
            else
            { v2=va_arg(args,signed int);
              if(subtype=='h')
                v2=(signed short)v2;
              if(subtype==CHARTYPE)
                v2=(signed char)v2;
            }
            if(v2<0)
            { buffer1[size1++]='-';
              v=-v2;
            }else
            { if(flags&SIGNFLAG)
                buffer1[size1++]='+';
              else if(flags&BLANKFLAG)
                buffer1[size1++]=' ';
              v=v2; }
          }else                    /* These are unsigned */
          { if(subtype==LLONGTYPE)
              v=va_arg(args,unsigned long long);
            else if(subtype=='l')
              v=va_arg(args,unsigned long);
            else
              v=va_arg(args,unsigned int);
            if(subtype=='h')
              v=(unsigned short)v;
            if(subtype==CHARTYPE)
              v=(unsigned char)v;
            if(flags&ALTERNATEFLAG)
            { if(type=='o'&&(preci||v))
                buffer1[size1++]='0';
              if((type=='x'||type=='X')&&v)
              { buffer1[size1++]='0';
                buffer1[size1++]=type; }
            }
          }

          buffer2=&buffer[sizeof(buffer)]; /* Calculate body string */
          base=type=='x'||type=='X'?16:(type=='o'?8:10);
          tabel=type!='X'?lowertabel:uppertabel;
          do
          { *--buffer2=tabel[v%base];
            v=v/base;
            size2++;
          }while(v);
          if(preci==ULONG_MAX) /* default */
            preci=0;
          else
            flags&=~ZEROPADFLAG;
          break;
        }
        case 'c':
          if(subtype=='l')
            *buffer2=va_arg(args,long);
          else
            *buffer2=va_arg(args,int);
          size2=1;
          preci=0;
          break;
        case 's':
          buffer2=va_arg(args,char *);
          { char *p=buffer2;
            size2=0;
            while((preci==0||size2<preci)&&*p){size2++;p++;}
          }
          preci=0;
          break;
        case '%':
          buffer2="%";
          size2=1;
          preci=0;
          break;
        case 'n':
          if(subtype==LLONGTYPE)
            *va_arg(args,long long *)=outcount;
          else if(subtype=='l')
            *va_arg(args,long *)=outcount;
          else if(subtype=='h')
            *va_arg(args,short *)=outcount;
          else if(subtype==CHARTYPE)
            *va_arg(args,char *)=outcount;
          else
            *va_arg(args,int *)=outcount;
          width=preci=0;
          break;
        default:
          if(!type)
            ptr--; /* We've gone too far - step one back */
          buffer2=(char *)format;
          size2=ptr-format;
          width=preci=0;
          break;
      }
      pad=size1+(size2>=preci?size2:preci); /* Calculate the number of characters */
      pad=pad>=width?0:width-pad; /* and the number of resulting pad bytes */

      if(flags&ZEROPADFLAG) /* print sign and that like */
        for(i=0;i<size1;i++)
          OUT(buffer1[i]);

      if(!(flags&LALIGNFLAG)) /* Pad left */
        for(i=0;i<pad;i++)
          OUT(flags&ZEROPADFLAG?'0':' ');

      if(!(flags&ZEROPADFLAG)) /* print sign if not zero padded */
        for(i=0;i<size1;i++)
          OUT(buffer1[i]);

      for(i=size2;i<preci;i++) /* extend to precision */
        OUT('0');

      for(i=0;i<size2;i++) /* print body */
        OUT(buffer2[i]);

      if(flags&LALIGNFLAG) /* Pad right */
        for(i=0;i<pad;i++)
          OUT(' ');

      format=ptr;
    }
    else
      OUT(*format++);
  }
  return outcount;
}
