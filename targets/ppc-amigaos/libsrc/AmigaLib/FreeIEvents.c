#include <devices/inputevent.h>
#include <proto/exec.h>

void FreeIEvents(struct InputEvent *events)
{
  struct InputEvent *next;

  while(events!=NULL)
  {
    next=events->ie_NextEvent;
    IExec->FreeVec(events);
    events=next;
  }
}
