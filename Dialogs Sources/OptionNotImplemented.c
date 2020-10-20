#include "CTrussPane.phs"

void OptionNotImplemented( void )
{
  DialogHandlerRecordPtr dhp;

  DHStandardNewRecord (&dhp, OptionNotImplementedDLOG_ID, 3/*NoUpdateUserItem*/, NoSelectedItem);

  if (DHDialogHandler(dhp))
  {

  }

  DHDeallocateRecord(dhp);
}

