#include <proto/dos.h>

LONG DoPkt0(struct MsgPort *port, long action)
{
  return IDOS->DoPkt(port, action, 0, 0, 0, 0, 0);
}

LONG DoPkt1(struct MsgPort *port, long action, long arg1)
{
  return IDOS->DoPkt(port, action, arg1, 0, 0, 0, 0);
}

LONG DoPkt2(struct MsgPort *port, long action, long arg1, long arg2)
{
  return IDOS->DoPkt(port, action, arg1, arg2, 0, 0, 0);
}

LONG DoPkt3(struct MsgPort *port, long action, long arg1, long arg2, long arg3)
{
  return IDOS->DoPkt(port, action, arg1, arg2, arg3, 0, 0);
}

LONG DoPkt4(struct MsgPort *port, long action, long arg1, long arg2, long arg3, long arg4)
{
  return IDOS->DoPkt(port, action, arg1, arg2, arg3, arg4, 0);
}

LONG DoPkt5(struct MsgPort *port, long action, long arg1, long arg2, long arg3, long arg4, long arg5)
{
  return IDOS->DoPkt(port, action, arg1, arg2, arg3, arg4, arg5);
}
