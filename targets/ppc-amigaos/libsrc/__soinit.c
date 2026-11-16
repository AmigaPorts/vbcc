/*
** Initialization/termination of shared objects (dynamic linking),
** called from the startup code.
*/

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/elf.h>


void __so_init(BOOL init)
{
  struct Library *ElfBase;
  struct ElfIFace *IElf;
  BPTR seglist;
  Elf32_Handle elfhandle;

  if(ElfBase=IExec->OpenLibrary("elf.library",52)){
    if(ElfBase->lib_Version>52 || ElfBase->lib_Revision>1){
      /* elf.library V52.2 or better */
      if((IElf=(struct ElfIFace *)IExec->GetInterface(ElfBase,"main",1,NULL))
         && IDOS){
        if(seglist=IDOS->GetProcSegList(NULL,GPSLF_CLI|GPSLF_SEG)){
          if(IDOS->GetSegListInfoTags(seglist,GSLI_ElfHandle,&elfhandle,
                                      TAG_DONE)==1 && elfhandle)
            IElf->InitSHLibs(elfhandle,init);
        }
        IExec->DropInterface((struct Interface *)IElf);
      }
    }
    IExec->CloseLibrary(ElfBase);
  }
}
