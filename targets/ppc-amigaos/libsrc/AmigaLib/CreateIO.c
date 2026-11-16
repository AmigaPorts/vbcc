#include <exec/io.h>
#include <exec/memory.h>
#include <clib/alib_protos.h>
#include <proto/exec.h>

struct IORequest *CreateExtIO(struct MsgPort *port,long iosize)
{
  struct IORequest *ioreq=NULL;

  if (port && (ioreq=IExec->AllocVec(iosize,MEMF_CLEAR|MEMF_PUBLIC)))
  {
    ioreq->io_Message.mn_Node.ln_Type=NT_MESSAGE;
    ioreq->io_Message.mn_ReplyPort=port;
    ioreq->io_Message.mn_Length=iosize;
  }
  return ioreq;
}

struct IOStdReq *CreateStdIO(struct MsgPort *port)
{
  return (struct IOStdReq *)CreateExtIO(port,sizeof(struct IOStdReq));
}

void DeleteExtIO(struct IORequest *ioreq)
{
  if (ioreq)
  {
    ioreq->io_Message.mn_Node.ln_Type=-1;
    ioreq->io_Device=(struct Device *)-1;
    ioreq->io_Unit=(struct Unit *)-1;
    IExec->FreeVec(ioreq);
  }
}

void DeleteStdIO(struct IOStdReq *ioreq)
{
  if (ioreq)
  {
    ioreq->io_Message.mn_Node.ln_Type=-1;
    ioreq->io_Device=(struct Device *)-1;
    ioreq->io_Unit=(struct Unit *)-1;
    IExec->FreeVec(ioreq);
  }
}
