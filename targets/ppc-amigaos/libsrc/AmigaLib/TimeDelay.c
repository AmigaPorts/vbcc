#include <exec/memory.h>
#include <devices/timer.h>
#include <proto/exec.h>

#undef NEWLIST
#define NEWLIST(l) ((l)->lh_Head = (struct Node *)&(l)->lh_Tail, \
                    (l)->lh_TailPred = (struct Node *)&(l)->lh_Head)

LONG TimeDelay(long unit, unsigned long secs, unsigned long microsecs)
{
  struct PortIO {
    struct TimeRequest treq;
    struct MsgPort port;
  } *portio;
  long ret=-1;

  if ((portio=(struct PortIO *)IExec->AllocVec(sizeof(struct PortIO),MEMF_CLEAR|MEMF_PUBLIC)))
  {
    portio->port.mp_Node.ln_Type=NT_MSGPORT;
    if ((BYTE)(portio->port.mp_SigBit=IExec->AllocSignal(-1))>=0)
    {
      portio->port.mp_SigTask=IExec->FindTask(NULL);
      NEWLIST(&portio->port.mp_MsgList);

      portio->treq.Request.io_Message.mn_Node.ln_Type=NT_MESSAGE;
      portio->treq.Request.io_Message.mn_ReplyPort=&portio->port;
      if (!(IExec->OpenDevice(TIMERNAME,unit,&portio->treq.Request,0)))
      {
        portio->treq.Request.io_Command=TR_ADDREQUEST;
        portio->treq.Time.Seconds=secs;
        portio->treq.Time.Microseconds=microsecs;
        if (!IExec->DoIO(&portio->treq.Request))
          ret=0;
        IExec->CloseDevice(&portio->treq.Request);
      }
      IExec->FreeSignal(portio->port.mp_SigBit);
    }
    IExec->FreeVec(portio);
  }
  return ret;
}
