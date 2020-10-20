/* ----------------------------------------------------------------------------  */
/* Copyright ©1987-1989 by Gary Gregory and Neil Ticktin.  All rights reserved.  */
/* Version 1.0.  Any portion of this demo can be used in your application as  */
/* long as you follow the terms in the Invention Software Licensing Agreement.  */
/* ----------------------------------------------------------------------------  */

/* Unit DemoCounters */


#include <DialogHandlerHeader.ph>

enum { CounterDLOG_ID = 605 };
enum { CounterOKId = 1 };
enum { CounterCancelId = 2 };
enum { CounterDispTextId = 3 };
enum { CounterUpdateUserItemId = 5 };
enum { CounterMoneyId = 7 };
enum { CounterMoneyArrowId = 9 };
enum { CounterDaysArrowId = 10 };
enum { CounterDaysId = 11 };

void  DoDialogItemsCounter(void)
{
  DialogHandlerRecordPtr dhp;
  DecForm  dForm;

  DHStandardNewRecord (&dhp, CounterDLOG_ID, CounterUpdateUserItemId, NoSelectedItem);

  dForm.digits = 4;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddCounter(dhp, CounterMoneyId, CounterMoneyArrowId, CounterMoneyValue, 0.01, 0.0, MAXREAL, DHMakeKeyEquiv(NORMAL, '+'), DHMakeKeyEquiv(NORMAL, '-'), dForm, VeryShortDelay, NULL);

  dForm.digits = 0;
  DHAdvAddCounter(dhp, CounterDaysId, CounterDaysArrowId, CounterDaysValue, 1.0, 0.0, 99.0, DHNoKeyEquiv(), DHNoKeyEquiv(), dForm, ShortDelay, NULL);

  DHSetDialogFont(dhp, monaco, 9, (Style)NULL);
/*  DHADDDISPLAYTEXT(dhp, CounterDispTextId, CounterDLOG_ID); /* CounterDLOG_ID is the same number as the TEXTid */

/*  DHSetCentering(dhp, PrefCenterHorizValue, PrefCenterVertValue, SaveCenteringOff);
  DHSetNearMousePointer(dhp, PrefNearHorizValue, PrefNearVertValue);
*/
  if (DHDialogHandler(dhp))
  {
    CounterMoneyValue = DHGetCounterValue(dhp, CounterMoneyId);
    CounterDaysValue = DHGetCounterValue(dhp, CounterDaysId);
  }

  DHDeallocateRecord(dhp);
}
