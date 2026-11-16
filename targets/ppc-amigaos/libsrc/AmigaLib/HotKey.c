#include <libraries/commodities.h>
#include <proto/commodities.h>

CxObj *HotKey(STRPTR description, struct MsgPort *port, long id)
{
  CxObj *filter;

  if ((filter=ICommodities->CreateCxObj(CX_FILTER,(long)description,0)))
  {
    ICommodities->AttachCxObj(filter, ICommodities->CreateCxObj(CX_SEND, (long)port, id));
    ICommodities->AttachCxObj(filter, ICommodities->CreateCxObj(CX_TRANSLATE, 0, 0));
    if (ICommodities->CxObjError(filter))
    {
      ICommodities->DeleteCxObjAll(filter); filter=NULL;
    }
  }
  return filter;
}
