#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <ctype.h>

/* some macros to cut this short
 * NEXT(c);     read next character
 * PREV(c);     ungetc a character
 * VAL(a)       leads to 1 if a is true and valid
 */
#define NEXT(c) ((c)=getc(stream),size++,incount++)
#define PREV(c) do{if((c)!=EOF)nungetc((c),stream);size--;incount--;}while(0)
#define VAL(a)  ((a)&&size<=width)

/* subtypes besides 'h', 'l' and 'L' */
#define LLONGTYPE     1  /* 'll' or 'j' */
#define CHARTYPE      2  /* 'hh' */


static void nungetc(int c,FILE *stream)
{
  if(stream==NULL)
    return;
  if(stream->pointer<stream->base)
    *stream->pointer=c;
  stream->count++;
  stream->pointer--;
}

int vfscanf(FILE *stream,const char *format,va_list args)
{
  size_t blocks=0,incount=0;
  int c=0;

  while(*format)
  {
    size_t size=0;

    if(*format=='%')
    {
      size_t width=ULONG_MAX;
      char type,subtype='i',ignore=0;
      const unsigned char *ptr=format+1;
      size_t i;

      if(isdigit(*ptr))
      { width=0;
        while(isdigit(*ptr))
          width=width*10+(*ptr++-'0'); }

      while(*ptr=='h'||*ptr=='l'||*ptr=='L'||*ptr=='z'||*ptr=='j'||
            *ptr=='t'||*ptr=='*')
      { if(*ptr=='*')
          ignore=1;
        else if(subtype=='h'&&*ptr=='h')
          subtype=CHARTYPE;
        else if(subtype=='l'&&*ptr=='l')
          subtype=LLONGTYPE;
        else
          subtype=*ptr;
        ptr++;
      }
      if(subtype=='j')
        subtype=LLONGTYPE;
      if(subtype=='t')
        subtype='i';
      if(subtype=='z')
        subtype='l';

      type=*ptr++;

      if(type&&type!='%'&&type!='c'&&type!='n'&&type!='[')
      { do /* ignore leading whitespace characters */
          NEXT(c);
        while(isspace((unsigned char)c));
        size=1; } /* The first non-whitespace character is already read */

      switch(type)
      { case 'c':
        { unsigned char *bp;

          if(width==ULONG_MAX) /* Default */
            width=1;

          if(!ignore)
            bp=va_arg(args,char *);
          else
            bp=NULL; /* Just to get the compiler happy */

          NEXT(c); /* 'c' did not skip whitespace */
          while(VAL(c!=EOF))
          { if(!ignore)
              *bp++=c;
            NEXT(c);
          }
          PREV(c);

          if(!ignore&&size)
            blocks++;
          break;
        }
        case '[':
        { unsigned char *bp;
          unsigned char tab[32],a,b;
          char circflag=0;

          if(*ptr=='^')
          { circflag=1;
            ptr++; }
          for(i=0;i<sizeof(tab);i++)
            tab[i]=circflag?255:0;
          do
          { if(!*ptr)
              break;
            a=*ptr++;
            if(*ptr=='-'&&ptr[1]>a)
            { ptr++;
              b=*ptr++;
            }else
              b=a;
            for(i=a;i<=b;i++)
              if(circflag)
                tab[i/8]&=~(1<<(i&7));
              else
                tab[i/8]|=1<<(i&7);
          }while(*ptr!=']');
          ptr++;

          if(!ignore)
            bp=va_arg(args,char *);
          else
            bp=NULL; /* Just to get the compiler happy */

          NEXT(c);
          while(VAL(c!=EOF&&tab[c/8]&(1<<(c&7))))
          { if(!ignore)
              *bp++=c;
            NEXT(c);
          }
          PREV(c);

          if(!ignore&&size)
          { *bp++='\0';
            blocks++; }
          break;
        }
        case 's':
        { unsigned char *bp;

          if(!ignore)
            bp=va_arg(args,char *);
          else
            bp=NULL; /* Just to get the compiler happy */

          while(VAL(c!=EOF&&!isspace((unsigned char)c)))
          { if(!ignore)
              *bp++=c;
            NEXT(c);
          }
          PREV(c);

          if(!ignore&&size)
          { *bp++='\0';
            blocks++; }
          break;
        }
        case '%':
          NEXT(c);
          if(c!='%')
            PREV(c); /* unget non-'%' character */
          break;
        case 'n':
          if(!ignore)
          { if(subtype==LLONGTYPE)
              *va_arg(args,long long *)=incount;
            else if(subtype=='l')
              *va_arg(args,long *)=incount;
            else if(subtype=='h')
              *va_arg(args,short *)=incount;
            else if(subtype==CHARTYPE)
              *va_arg(args,char *)=incount;
            else
              *va_arg(args,int *)=incount;
          }
          size=1; /* fake a valid argument */
          blocks++;
          break;
        default:
        { unsigned long long v=0;
          int base;
          int min=0;

          if(!type)
            ptr--; /* unparse NUL character */

          if(type=='p')
          { subtype='l'; /* This is the same as %lx */
            type='x'; }

          if(VAL((c=='-'&&type!='u')||c=='+'))
          { min=c;
            NEXT(c); }

          if(type=='i') /* which one to use ? */
          { if(VAL(c=='0')) /* Could be octal or sedecimal */
            { int d;
              NEXT(d); /* Get a look at next character */
              if(VAL(tolower((unsigned char)d)=='x'))
              { int e;
                NEXT(e); /* And the next */
                if(VAL(isxdigit((unsigned char)c)))
                  type='x'; /* Is a valid x number with '0x?' */
                PREV(e);
              }else
                type='o';
              PREV(d);
            }else if(VAL(!isdigit((unsigned char)c)&&isxdigit((unsigned char)c)))
              type='x'; /* Is a valid x number without '0x' */
          }

          while(type=='x'&&VAL(c=='0')) /* sedecimal */
          { int d;
            NEXT(d);
            if(VAL(tolower((unsigned char)d)=='x'))
            { int e;
              NEXT(e);
              if(VAL(isxdigit((unsigned char)e)))
              { c=e;
                break; } /* Used while just to do this ;-) */
              PREV(e);
            }
            PREV(d);
            break; /* Need no loop */
          }

          base=type=='x'||type=='X'?16:(type=='o'?8:10);
          while(VAL(isxdigit((unsigned char)c)&&(base!=10||isdigit((unsigned char)c))&&(base!=8||c<='7')))
          { v=v*base+(isdigit((unsigned char)c)?c-'0':0)+(isupper((unsigned char)c)?c-'A'+10:0)+(islower((unsigned char)c)?c-'a'+10:0);
            NEXT(c);
          }

          if(min&&size==2) /* If there is no valid character after sign, unget last */
          { PREV(c);
            c=min; }

          PREV(c);

          if(ignore||!size)
            break;

          if(type=='u')
            switch(subtype)
            { case LLONGTYPE:
                *va_arg(args,unsigned long long *)=v;
                break;
              case 'l':
                *va_arg(args,unsigned long *)=v;
                break;
              case 'h':
                *va_arg(args,unsigned short *)=v;
                break;
              case CHARTYPE:
                *va_arg(args,unsigned char *)=v;
                break;
              default:
                *va_arg(args,unsigned int *)=v;
                break;
            }
          else
          { signed long long v2;
            if(min=='-')
              v2=-v;
            else
              v2=v;
            switch(subtype)
            { case LLONGTYPE:
                *va_arg(args,signed long long *)=v2;
                break;
              case 'l':
                *va_arg(args,signed long *)=v2;
                break;
              case 'h':
                *va_arg(args,signed short *)=v2;
                break;
              case CHARTYPE:
                *va_arg(args,signed char *)=v2;
                break;
              default:
                *va_arg(args,signed int *)=v2;
                break;
            }
          }
          blocks++;
          break;
        }
      }
      format=ptr;
    }else
    { if(isspace((unsigned char)*format))
      { do
          NEXT(c);
        while(isspace((unsigned char)c));
        PREV(c);
        size=1; }
      else
      { NEXT(c);
        if(c!=*format)
          PREV(c); }
      format++;
    }
    if(!size)
      break;
  }

  if(c==EOF&&!blocks)
    return c;
  else
    return blocks;
}
