#include <exec/memory.h>
#include <devices/inputevent.h>
#include <libraries/commodities.h>
#include <clib/alib_protos.h>
#include <proto/exec.h>
#include <proto/commodities.h>

static struct InputEvent *ParseString(UBYTE *str, CONST struct KeyMap *km)
{
  struct InputEvent *ev,*last=NULL,*head=NULL;

  while (str && *str!='\0')
  {
    /* sic: FreeIEvents() frees these with FreeVec() */
    if (!(ev=IExec->AllocMem(sizeof(struct InputEvent),MEMF_PUBLIC|MEMF_CLEAR)))
    {
      if (head)
        FreeIEvents(head);
      return NULL;
    }
    if (!head)
      head=ev;
    if (last)
      last->ie_NextEvent=ev;
    last=ev;
    ev->ie_Class=IECLASS_RAWKEY;
    ev->ie_EventAddress=NULL;

    switch (*str)
    {
      case '\\':
      {
        UBYTE c;

        switch (*++str)
        {
          case 't': c='\t'; break;
          case 'n':
          case 'r': c='\n'; break;
          case '\\': c='\\'; break;
          default: c=*str; break;
        }
        if (ICommodities->InvertKeyMap(c,ev,km)==FALSE)
        {
          FreeIEvents(head);
          return NULL;
        }
        str++;
        break;
      }
      case '<':
      {
        IX ix={0};
        UBYTE *start;
        LONG err;

        start=++str;
        while (*str && *str!='>')
          str++;
        *str='\0';
        err=ICommodities->ParseIX(start,&ix);
        *str++='>';
        if (err<0)
        {
          FreeIEvents(head);
          return NULL;
        }
        ev->ie_Class=ix.ix_Class;
        ev->ie_Code=ix.ix_Code;
        ev->ie_Qualifier=ix.ix_Qualifier;
        break;
      }
      default:
        if (ICommodities->InvertKeyMap(*str++,ev,km)==FALSE)
        {
          FreeIEvents(head);
          return NULL;
        }
        break;
    }
  }
  return head;
}

struct InputEvent *InvertString(CONST_STRPTR str, CONST struct KeyMap *km)
{
  struct InputEvent *first,*ev,*next,*prev;

  if ((ev=ParseString((UBYTE *)str,km)))
  {
    first=ev;
    next=ev->ie_NextEvent;
    while (next)
    {
      prev=ev;
      ev=next;
      next=next->ie_NextEvent;
      ev->ie_NextEvent=prev;
    }
    first->ie_NextEvent=NULL;
  }
  return ev;
}
