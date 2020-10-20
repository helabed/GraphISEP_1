/****
 * CTrussPane.c
 *
 *  Pane methods for a typical application.
 *
 *  Most applications will want a scrollable window, so this
 *  class is based on the class CPanorama. All the methods here
 *  would still apply to classes based directly on CPane.
 *
 ****/

#include "CTrussPane.phs"

/*** Global Variables ***/

extern void  OptionNotImplementedHook(DialogPtr  dp, short  itemHit,
                DialogHandlerRecordPtr pdh);


/***
 * AdjustCursor
 *
 *  If you want the cursor to have a different shape in your pane,
 *  do it in this method. If you want a different cursor for different
 *  parts of the same pane, you'll need to change the mouseRgn like this:
 *    1. Create a region for the "special area" of your pane.
 *    2. Convert this region to global coordinates
 *    3. Set the mouseRgn to the intersection of this region
 *       and the original mouseRgn: SectRgn(mouseRgn, myRgn, mouseRgn);
 *
 *  The default method just sets the cursor to the arrow. If this is fine
 *  for you, don't override this method.
 *
 ***/

void CTrussPane::AdjustCursor(Point where, RgnHandle mouseRgn)

{
  inherited::AdjustCursor(where, mouseRgn);
}


/***
 * ScrollToSelection
 *
 *  If your pane is based on a Panorama (as this example is), you might
 *  want to define what it means to have a selection and what it means to
 *  scroll to that selection.
 *
 ***/

void CTrussPane::ScrollToSelection(void)

{
  /* scroll to the selection */
}


/*****
 *
 * Dispose of all my objects, in the cluster.
 */



void CTrussPane::Dispose( void )
 {
   ContLoadsAndMoments->DisposeAll();
   NodesCluster->DisposeAll();
   ConcLoadsAndMoments->DisposeAll();
    TElementsCluster->DisposeAll();

                    /* what a dog, If I tried to
                   do inherited::Dispose before
                   this line the program crashed.
                   I guess, it disposed of the Pane,
                   so as far as it was concerned the
                   CTrussPane, and its dispose method
                   don't exist anymore ????? */
   inherited::Dispose();

}






void CTrussPane::DoAutoKey(char theChar, Byte keyCode,
                    EventRecord *macEvent)
{
}



void CTrussPane::DoKeyUp(char theChar, Byte keyCode,
                    EventRecord *macEvent)
{

}

      static void  OptionNotImplementedHook(DialogPtr  dp, short itemHit,
                        DialogHandlerRecordPtr dhp)
      {
        RadioButtonSetPtr set1;

        if ( (itemHit == SystemOfUnitsSystemInternaional_ID ) ||
          (itemHit == SystemOfUnitsBritish_ID ) )
        {
          SysBeep(2);
          OptionNotImplemented();
        }
      }

void CTrussPane::DoSystemOfUnitsDialog( void )

{
  DialogHandlerRecordPtr dhp;
  RadioButtonSetPtr set1;

  DHStandardNewRecord (&dhp, SystemOfUnitsDLOG_ID,
                SystemOfUnitsUpdateUserItemId, NoSelectedItem);

  DHAddRadioSet(dhp, theSystemOfUnits, &set1);
  DHAdvAddRadioButtonToSet(&set1, SystemOfUnitsSystemInternaional_ID,
                  DHNoKeyEquiv(), OptionNotImplementedHook);
  DHAdvAddRadioButtonToSet(&set1, SystemOfUnitsUSCustomary_ID, DHNoKeyEquiv(),
                   NULL);
  DHAdvAddRadioButtonToSet(&set1, SystemOfUnitsBritish_ID, DHNoKeyEquiv(),
                   OptionNotImplementedHook);


  if (DHDialogHandler(dhp))
  {
    theSystemOfUnits = DHWhichRadioButtonIsSet(set1);
    if( (theSystemOfUnits == SystemOfUnitsSystemInternaional_ID) ||
      ( theSystemOfUnits == SystemOfUnitsBritish_ID) )
    {
      theSystemOfUnits = SystemOfUnitsUSCustomary_ID;
    }
  }

  DHDeallocateRecord(dhp);
}


void CTrussPane::DoLoadsScallingDialog( void )

{
  DialogHandlerRecordPtr   dhp;
  DecForm          dForm;

  DHStandardNewRecord (&dhp, LoadsScallingDLOG_ID,
            LoadsScallingUpdateUserItemId, LoadsScallingEditTextID);
  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, LoadsScallingEditTextID, theLoadScale, dForm, 0.0, MAXREAL);


  if (DHDialogHandler(dhp))
  {
    theLoadScale = DHGetEditReal(dhp, LoadsScallingEditTextID);
  }

  DHDeallocateRecord(dhp);
}

void CTrussPane::DoStructureScallingDialog( void )

{
  DialogHandlerRecordPtr   dhp;
  DecForm          dForm;

  DHStandardNewRecord (&dhp, StructureScallingDLOG_ID,
        StructureScallingUpdateUserItemId, StructureScallingEditTextID);
  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, StructureScallingEditTextID, theStructureScale,
                    dForm, 0.0, MAXREAL);

  if (DHDialogHandler(dhp))
  {
    theStructureScale = DHGetEditReal(dhp, StructureScallingEditTextID);
  }

  DHDeallocateRecord(dhp);
}

void CTrussPane::DoLoadStepsDialog( void )

{
  DialogHandlerRecordPtr   dhp;
  DecForm          dForm;

  DHStandardNewRecord (&dhp, LoadStepsDLOG_ID,
        LoadStepsUpdateUserItemId, LoadStepsNumber);
  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditInteger(dhp, LoadStepsNumber, numberOfLoadSteps,1, MAXINT);

  if (DHDialogHandler(dhp))
  {
    numberOfLoadSteps = DHGetEditInteger(dhp, LoadStepsNumber);
  }

  DHDeallocateRecord(dhp);
}

