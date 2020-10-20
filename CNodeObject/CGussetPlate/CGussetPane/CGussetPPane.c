/****
 * CGussetPane.c
 *
 *  Pane methods for a typical application.
 *
 *  Most applications will want a scrollable window, so this
 *  class is based on the class CPanorama. All the methods here
 *  would still apply to classes based directly on CPane.
 *
 ****/

#include "CGussetPane.phs"
#include "CGussetPane.h"
#include "CBUPMouseTask.h"
#include "CPlateBUPMouseTask.h"


/*** Global Variables ***/

extern CBartender    *gBartender;
extern EventRecord    gLastMouseDown;
extern  CBartender     *gBartender;
extern   short      gClicks;

extern Boolean HitSameTEObject( CTrussElementObject *theObject,
         Point *hitPt );

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

void CGussetPane::AdjustCursor(Point where, RgnHandle mouseRgn)

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

void CGussetPane::ScrollToSelection(void)

{
  /* scroll to the selection */
}


/*****
 *
 * Dispose of all my objects, in the cluster.
 */



void CGussetPane::Dispose( void )
 {

/*    TElementsCluster->Dispose();
    When I disposed of this the program bombed */

/*   ContLoadsAndMoments->DisposeAll();
   NodesCluster->DisposeAll();
   ConcLoadsAndMoments->DisposeAll();

                    /* what a dog, If I tried to
                   do inherited::Dispose before
                   this line the program crashed.
                   I guess, it disposed of the Pane,
                   so as far as it was concerned the
                   CGussetPane, and its dispose method
                   don't exist anymore ????? */
   inherited::Dispose();

}






void CGussetPane::DoAutoKey(char theChar, Byte keyCode,
                    EventRecord *macEvent)
{
}



void CGussetPane::DoKeyUp(char theChar, Byte keyCode,
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

void CGussetPane::DoSystemOfUnitsDialog( void )

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


void CGussetPane::DoLoadsScallingDialog( void )

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

void CGussetPane::DoStructureScallingDialog( void )

{
  DialogHandlerRecordPtr dhp;
  DecForm          dForm;
  float          newtheStructureScale;

  DHStandardNewRecord (&dhp, StructureScallingDLOG_ID,
        StructureScallingUpdateUserItemId, StructureScallingEditTextID);
  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, StructureScallingEditTextID, theStructureScale,
                    dForm, 0.0, MAXREAL);

  if (DHDialogHandler(dhp))
  {
    newtheStructureScale = DHGetEditReal(dhp, StructureScallingEditTextID);

        /* Length field has changed, i.e new != old */
    if( ! (Abs(newtheStructureScale -
       (theStructureScale))
       <=  SMALL_FLOAT_VALUE) )
    {
      theStructureScale = newtheStructureScale;
      Refresh();
    }
  }

  DHDeallocateRecord(dhp);
}

/***************************
 * CGussetPane::ConnectObjectsToNode.c
 * This function takes care of the Nitty gritties involved when connecting
 * an object to a node. If the connection conditions were met, i.e
 * connection was performed it returns TRUE, else False.
 *
 *************************************************/


Boolean CGussetPane::ConnectObjectsToNode( short modifierKeys )

{
  Boolean        connectionPerformed = FALSE;

      /* optionKey is used, theSelectedNodeObject
      is the last node selected */
  if( (theSelectedNodeObject) && (modifierKeys == optionKey ))
  {
    switch( theSelectedObject )
    {
      case aConcLoadOrMoment:
        connectionPerformed = theConcLoadOrMoment->
          ConnectYourselfToNode( theSelectedNodeObject );
        break;

      case aTrussElementObject:
        connectionPerformed = theTElementObject->
          ConnectYourselfToNode( theSelectedNodeObject );
        break;

      case aNodeObject:
        theNodeObject->SelectYourself();
        return   FALSE;
        break;

      default:
        /* do nothing */
        return connectionPerformed;
        break;
    }        /* end of switch */
  }
  return connectionPerformed;
}

/***************************
 * CGussetPane::ConnectObjectsToTE.c
 * This function takes care of the Nitty gritties involved when connecting
 * an object to a node. If the connection conditions were met, i.e
 * connection was performed it returns TRUE, else False.
 *
 *************************************************/


Boolean CGussetPane::ConnectObjectsToTE( short modifierKeys )
{
  Boolean        connectionPerformed = FALSE;
      /* optionkey used, theSelectedTEObject
      is the last node selected */
  if( (theSelectedTEObject) && (modifierKeys == optionKey ))
  {
    switch( theSelectedObject )
    {
      case aConcLoadOrMoment:
        connectionPerformed = theConcLoadOrMoment->
          ConnectYourselfToTE( theSelectedTEObject );
        break;

      case aContLoadOrMoment:
        connectionPerformed = theContLoadOrMoment->
          ConnectYourselfToTE( theSelectedTEObject );
        break;


      case aTrussElementObject:
        theTElementObject->SelectYourself();
        return FALSE;
        break;

      case aNodeObject:
        connectionPerformed = theNodeObject->
          ConnectYourselfToTE( theSelectedTEObject );
        break;

      default:
        /* do nothing */
        return connectionPerformed;
        break;
    }        /* end of switch */
  }
  return connectionPerformed;
}

/***
 * DoClick
 *
 *  The mouse went down in the pane.
 *  In this method you do whatever is appropriate for your
 *  application. HitPt is given in frame coordinates. The other
 *  parameters, modiferKeys and when, are taken from the event
 *  record.
 *
 *  If you want to implement mouse tracking, this is the method
 *  to do it in. You need to create a subclass of CMouseTask and
 *  pass it in a TrackMouse() message to the pane.
 *
 ***/



/*** Global Variables ***/

      /******
      /*
      /* this is used to perform unselection when another object
      /* is selected
      /*
      /**************/

      static void Perform_Selection_UnSelection(
                  CAbstractObject *theObject )
      {
          theObject->SelectYourself();
          theObject->UnSelectYourself();

      }
      static void Perform_UnSelection(
                  CAbstractObject *theObject )
      {
        if ( theObject->IamSelected )
        {
          theObject->UnSelectYourself();
        }
      }


      /******
      /*
      /* this is used to perform drawing for all objects
      /*
      /**************/

/*      static void Perform_Draw(
                  CAbstractObject *theObject )
      {
          theObject->ReDraw();
      }
*/

       /***
       * perform draw nodes  only for cluster redrawing
       */

      static void Perform_Draw_Nodes( CNodeObject  *theObject )
      {

        theObject->DrawNodeOnly();

      }



void CGussetPane::DoClick(Point hitPt, short modifierKeys, long when)

{
  CObjectMouseTask  *myMover;
  Rect        pinRect;
  PenState      pnState;
  Boolean        objectSelected;
  Boolean       connectionPerformed;
  CAbstractObject    *thePreviousObject;

      /* the pinRect is needed so that the track mouse knows
        where it is allowed to do tracking, eventually
        the user would set these parameters, in a MacDraw
        like fashion */

  thePreviousObject = theObject;

  pinRect = this->bounds;

  if ( theObject )
  {
    switch( theObject->WhoAreYou() )
    {
      case aGussetPlate:
      case aTBGussetPlate:
        ((CGussetPlate *)theObject)->BUP_UnSelectYourself();
        break;

      case aWoodElement:
      case aTopBottomWoodElement:
      case aRightLeftWoodElement:
        ((CRegularWoodTElement *)theObject)->BUP_UnSelectYourself();
        break;

    }
  }

  objectSelected = SelectAnObject( hitPt, modifierKeys);
  if (  objectSelected )
  {

    if ( gClicks == DOUBLE_CLICKS )
    {
      theObject->DoYourDialog();
      return;
    }


  }
  else    /* no object was selected, don't go to ObjectMouse task*/
  {
    return;
  }



  /* UnSelection is needed in here so that if a previous object has
      been selected, it becomes unselected. The CObjectMouseTask takes
      care of selecting the Object to be moved       */


  /*  if( theObject )
      theObject->UnSelectYourself(); */

    /* create an instance of the CObjectMouseTask class and initialize
      it*/
  switch( theObject->WhoAreYou() )
  {
    case aGussetPlate:
    case aTBGussetPlate:
      myMover = ( CPlateBUPMouseTask *)new( CPlateBUPMouseTask );
      (( CPlateBUPMouseTask *)myMover)->itsGussetPane = (CGussetPane *)this;
      break;

    case aWoodElement:
    case aTopBottomWoodElement:
    case aRightLeftWoodElement:
      myMover = ( CBUPMouseTask *)new( CBUPMouseTask );
      (( CBUPMouseTask *)myMover)->itsGussetPane = (CGussetPane *)this;
      break;

  }

    /* to show Undo/Redo string in the STR# 130 resource */
  myMover->IObjectMouseTask( 1 );

    /* to tell the CObjectMouseTask what object it is dealing with,
      i.e what kind and which instance of that object */
  myMover->theSelectedObject = theSelectedObject;




  switch( theSelectedObject )
  {
    case aContLoadOrMoment:
      myMover->theObject = theContLoadOrMoment;
      break;

    case aConcLoadOrMoment:
      myMover->theObject = theConcLoadOrMoment;
      break;

    case aNodeObject:
      myMover->theObject = theNodeObject;
      break;

    case aTrussElementObject:
      myMover->theObject = theTElementObject;
      break;

    default:
      myMover->noObjectSelectedFlag = TRUE;
      NodesCluster->DoForEach( Perform_Draw_Nodes );
      theObject = NULL;
      return;

      break;
  }


  myMover->ContLoadsAndMoments   =  ContLoadsAndMoments;
  myMover->TElementsCluster =  TElementsCluster;
  myMover->NodesCluster   =  NodesCluster;
  myMover->ConcLoadsAndMoments   =  ConcLoadsAndMoments;



      /* keeping track of oldhitPt for undoing */
  myMover->oldhitPt = hitPt;

    /* call the TrackMouse method inherited from CView */
  this->TrackMouse( myMover, hitPt, &pinRect );


    /* we are notifying the boss of the pane in the chain of command,
      i.e itsSupervisor(theDocument), that we are done with a mouse
      task, and that this last task should be stored in the document's
      lastTask instance variable, when Undo is choosen, an Undo()
      message is sent to the instance of CMouseTask */

  itsSupervisor->Notify( myMover );

  if ( theObject )
  {
    switch( theObject->WhoAreYou() )
    {
      case aGussetPlate:
      case aTBGussetPlate:
        ((CGussetPlate *)theObject)->BUP_SelectYourself();
        break;

      case aWoodElement:
      case aTopBottomWoodElement:
      case aRightLeftWoodElement:
        ((CRegularWoodTElement *)theObject)->BUP_SelectYourself();
        break;

    }
  }
}


    static void Initialize_BC( CAbstractObject
        *theObject, CGussetPlate **thePlatePtr)
    {
      short        whichEndConnected;

      if ( theObject )
      {
        switch( theObject->WhoAreYou() )
        {
          case aWoodElement:
          case aTopBottomWoodElement:
          case aRightLeftWoodElement:
            whichEndConnected = ((CRegularWoodTElement *)theObject)->
                WhichEndIsConnected( (*thePlatePtr) );

            if( whichEndConnected == 1 )
            {
              ((CRegularWoodTElement *)theObject)->its1stEndBCondIsSet = FALSE;
            }
            else if( whichEndConnected == 2 )
            {
              ((CRegularWoodTElement *)theObject)->its2ndEndBCondIsSet = FALSE;
            }
            else if( whichEndConnected == 0 )
            {
              (*thePlatePtr)->itsMotherTEBCIsSet = FALSE;
            }
            break;
          case aGussetPlate:
              (*thePlatePtr)->itsMotherTEBCIsSet = FALSE;
            break;

        }
      }
    }

    static void Initialize_InheritanceOfLoads( CAbstractObject
        *theObject, CGussetPlate **thePlatePtr)
    {
      short        whichEndConnected;

      if ( theObject )
      {
        switch( theObject->WhoAreYou() )
        {
          case aWoodElement:
          case aTopBottomWoodElement:
          case aRightLeftWoodElement:
            whichEndConnected = ((CRegularWoodTElement *)theObject)->
                WhichEndIsConnected( (*thePlatePtr) );

            if( whichEndConnected == 1 )
            {
              ((CRegularWoodTElement *)theObject)->inherit1stEndPlateLoads = FALSE;
            }
            else if( whichEndConnected == 2 )
            {
              ((CRegularWoodTElement *)theObject)->inherit2ndEndPlateLoads = FALSE;
            }
            else if( whichEndConnected == 0 )
            {
              (*thePlatePtr)->itsMotherTE_InheritsPlateLoads = FALSE;
            }
            break;
          case aGussetPlate:
              (*thePlatePtr)->itsMotherTE_InheritsPlateLoads = FALSE;
            break;

        }
      }
    }



/***
 * DoCommand
 *
 *
 *  In this method, you handle all the commands your pane
 *  deals with.
 *
 *
 *  the avaialble commands are cmdGiveMeASquare, cmdGiveMeATruss,
 *  cmdGiveMeANode.
 *
 *
 *
 ***/


void CGussetPane::DoCommand(long theCommand)

{
  Point    myMouseClick, hitPt;
  short        whichEndConnected;



/****************** all this garbage in here is to ensure that ***********
 ******************  objects are created inside the window     ***********/

      myMouseClick = gLastMouseDown.where ;
      WindToFrame( &myMouseClick );
      hitPt = myMouseClick;
      if( EqualPt(hitPt,previousMouseLocation) )
      {
        hitPt.v = myMouseClick.v + 10;
        hitPt.h = myMouseClick.h + 15;
      }
      previousMouseLocation = hitPt;
      gLastMouseDown.where = hitPt;
/****************************** end of garbage ***************************/


  switch (theCommand) {

    /* your pane commands here */

      /* AddToList() adds creates a new instance of the*****Object
        and stores it in a CClusterOfObjects class that is
          referenced by ObjectsCluster. */


    case cmdStructure:
      DoStructureScallingDialog();    /* structure scalling */
      break;


    case cmdRefreshWindow:
      Refresh();
      break;

    case cmdZoomIn:
      theStructureScale = theStructureScale / 2;
      Refresh();
      break;

    case cmdZoomOut:
      theStructureScale = theStructureScale * 2;
      Refresh();
      break;

    case cmdDefineConnecArea:
      if ( theObject )
      {
        switch( theObject->WhoAreYou() )
        {
          case aWoodElement:
          case aTopBottomWoodElement:
          case aRightLeftWoodElement:
            ((CRegularWoodTElement *)theObject)->
              Init_ConnectorPolygon( itsGussetPlate );
            Refresh();
            ConnectAreaBeingDefined = TRUE;
            firstPointLocated = FALSE;
            break;

        }
      }
      break;

    case cmdSetBoundaryCondition:
      if ( theObject )
      {
        switch( theObject->WhoAreYou() )
        {
          case aWoodElement:
          case aTopBottomWoodElement:
          case aRightLeftWoodElement:
            /*itsGussetPlate->itsTrussPane->PerformGlobalRenumbering();*/
            theListOfObjects->DoForEach1( Initialize_BC, (long)(&itsGussetPlate) );
            whichEndConnected = ((CRegularWoodTElement *)theObject)->
                            WhichEndIsConnected( itsGussetPlate );

            if( whichEndConnected == 1 )
            {
              ((CRegularWoodTElement *)theObject)->its1stEndBCondIsSet = TRUE;
            }
            else if( whichEndConnected == 2 )
            {
              ((CRegularWoodTElement *)theObject)->its2ndEndBCondIsSet = TRUE;
            }
            else if( whichEndConnected == 0 )
            {
              itsGussetPlate->itsMotherTEBCIsSet = TRUE;
            }

            Refresh();
            break;
          case aGussetPlate:
            itsGussetPlate->itsTrussPane->PerformGlobalRenumbering();
            theListOfObjects->DoForEach1( Initialize_BC, (long)(&itsGussetPlate) );


            Refresh();
            break;

        }
      }
      break;

    case cmdInheritPlateLoads:
      if ( theObject )
      {
        switch( theObject->WhoAreYou() )
        {
          case aWoodElement:
          case aTopBottomWoodElement:
          case aRightLeftWoodElement:
            theListOfObjects->DoForEach1( Initialize_InheritanceOfLoads,
                                   (long)(&itsGussetPlate) );
            whichEndConnected = ((CRegularWoodTElement *)theObject)->
                            WhichEndIsConnected( itsGussetPlate );

            if( whichEndConnected == 1 )
            {
              ((CRegularWoodTElement *)theObject)->inherit1stEndPlateLoads = TRUE;
            }
            else if( whichEndConnected == 2 )
            {
              ((CRegularWoodTElement *)theObject)->inherit2ndEndPlateLoads = TRUE;
            }
            else if( whichEndConnected == 0 )
            {
              itsGussetPlate->itsMotherTE_InheritsPlateLoads = TRUE;
            }

            Refresh();
            break;

          case aGussetPlate:
            theListOfObjects->DoForEach1( Initialize_InheritanceOfLoads,
                                  (long)(&itsGussetPlate) );


            Refresh();
            break;
        }
      }
      break;


    case cmdShowProperties:
      if( theObject)
        theObject->DoYourDialog();
      break;


    default:
      inherited::DoCommand(theCommand);
      break;
  }
}


/*************
 * DoKeyDown
 *
 * Do something when a certain key is pressed down.
 *
 ************************/

void CGussetPane::DoKeyDown(char theChar, Byte keyCode,
                EventRecord *macEvent)
{
          /* dispose of object, clear = 47, delete = 33*/
  if ((objectAlreadySelected) && ( (keyCode == 0x47) || (keyCode == 0x33)))
  {
    switch( theSelectedObject )
    {
      case aContLoadOrMoment:
        theObject->DeleteYourself();
        break;

      case aConcLoadOrMoment:
        switch( theConcLoadOrMoment->WhoAreYou() )
        {
          case aConcentratedMoment:
          case aConcentratedLoad:
            theObject->DeleteYourself();
            break;
        }
        break;

      case aNodeObject:
        theObject->DeleteYourself();
        break;

      case aTrussElementObject:
        theObject->DeleteYourself();
        break;
    }
  }
}

/***
 * Draw
 *
 *  In this method, you draw whatever you need to display in
 *  your pane. The area parameter gives the portion of the
 *  pane that needs to be redrawn. Area is in frame coordinates.
 *
 ***/


    /***
     * perform draw for cluster redrawing
     */

    static void Perform_Draw( CRegularWoodTElement *theObject,
            CGussetPlate **thePlatePtr )
    {
      theObject->BlowUpDraw( *thePlatePtr );

      theObject->DrawItsPolygon( *thePlatePtr );
      if ( theObject->IamSelected )
      {
        theObject->BUP_SelectYourself();
      }
    }


void CGussetPane::Draw(Rect *area)

{
  TElementsCluster->DoForEach1( Perform_Draw,
                (long)(&itsGussetPlate) );
  if( itsMotherTElement )
  {
    ((CRegularWoodTElement *)(itsMotherTElement))->
              BlowUpDraw( itsGussetPlate );
    ((CRegularWoodTElement *)(itsMotherTElement))->
              DrawItsPolygon( itsGussetPlate );
    if( ((CRegularWoodTElement *)(itsMotherTElement))->IamSelected )
    {
      ((CRegularWoodTElement *)(itsMotherTElement))->
              BUP_SelectYourself();
    }
  }

  itsGussetPlate->BlowUpDraw( itsGussetPlate );
  if ( itsGussetPlate->IamSelected )
    itsGussetPlate->BUP_SelectYourself();
}


void  CGussetPane::PrintPage(
  short    pageNum,        /* Number of the page to print    */
  short    pageWidth,        /* Width of printed page in pixels  */
  short    pageHeight)        /* Height of page in pixels      */
{
  Point    topOfPage;
  GrafPtr    savePort;
  long  pixWidth;
  long  pixHeight;
  long  numOfVertPages;
  long  numOfHorizPages;

                    /* Get dimensions of main pane  */
  GetPixelExtent(&pixWidth, &pixHeight);
                    /* Pages have a fixed pixel height  */
  numOfVertPages = pixHeight / pageHeight + 1;
  numOfHorizPages = pixWidth / pageWidth + 1;

  GetHomePosition(&topOfPage);

  topOfPage.h += ((pageNum - 1) / numOfVertPages)*(pageWidth / hScale);
  topOfPage.v += ((pageNum - 1) % numOfVertPages)*(pageHeight / vScale);

  GetPort(&savePort);
  ScrollTo(topOfPage, FALSE);
  SetPort(savePort);

  CPane::PrintPage(pageNum, pageWidth, pageHeight);
}


/****
 * CGussetPane.ITrussPane.c
 *
 *  TrussPane initialization method for a typical application.
 *
 *
 ****/

void CGussetPane::IGussetPane(CView *anEnclosure, CBureaucrat *aSupervisor,
              short aWidth, short aHeight,
              short aHEncl, short aVEncl,
              SizingOption aHSizing, SizingOption aVSizing)
{
  CPanorama::IPanorama(anEnclosure, aSupervisor, aWidth, aHeight,
              aHEncl, aVEncl, aHSizing, aVSizing);

  this->SetWantsClicks(TRUE);  /* allow pane to accept mouse clicks */

    /* create an instance of all clusters class and initialize them */
  ContLoadsAndMoments = new ( CClustOfContLoadsAndMoments );
  ContLoadsAndMoments->ICluster();
  ContLoadsAndMoments->itsTrussPane = ( CTrussPane *)this;
  ConcLoadsAndMoments = new ( CClustOfConcLoadsAndMoments );
  ConcLoadsAndMoments->ICluster();
  ConcLoadsAndMoments->itsTrussPane = ( CTrussPane *)this;
  NodesCluster = new ( CClusterOfNodes );
  NodesCluster->ICluster();
  NodesCluster->itsTrussPane = ( CTrussPane *)this;
  TElementsCluster = new ( CClusterOfTElements );
  TElementsCluster->ICluster();
  TElementsCluster->itsTrussPane = ( CTrussPane *)this;

  theListOfObjects = new( CList );
  theListOfObjects->IList();

  ObjectPlacement = A_NICE_LOCATION;  /* for my pseudo Object decorator */
  previousMouseLocation.v = A_NICE_LOCATION;
  previousMouseLocation.h = A_NICE_LOCATION;


      /* setting theSelectedObject to Null so that only one
        object is selected for now.. */
  theSelectedObject = aNullObject;
  thePreviouslySelectedObject = aNullObject;
  objectAlreadySelected = FALSE;

  theSelectedNodeObject = NULL;
  theSelectedTEObject = NULL;
  theObject = NULL;

  ConnectAreaBeingDefined = FALSE;
  firstPointLocated = FALSE;

    /** I moved the init. of these variable from here into the
     ** BuildWindow() inside CTrussDoc.
     **

  theSystemOfUnits = USCustomary; /* see constants.h
  theLoadScale = 100.00;    /* 1000 lbs per inch of screen
  theStructureScale = 36.00;  /* 36 inches per inch of screen

    **/
}

/******************
 * CGussetPane::SelectAnObject.c
 * This method accepts a hitPt as an input and results in finding which
 * Object out of all object was selected. If an object was located it
 * returns a TRUE, else a FALSE.
 *
 * The static function HitSameObject is the boolean function needed
 * when we are searching a cluster.
 *
 ******************************************/



      /***
       * test to see if a mouse was pressed on top
       * of one of the objects, this is for selecting, moving and
       * resizing ...
       */


  static Boolean HitSameBUP_ANY_Object( CAbstractObject *theObject,
     HitPtAndObjectPtr *theHitPtAndObjectPtr )
  {
    Boolean            twoPointMatch = FALSE;
    CGussetPlate         *theGussetPlate;
    CRegularWoodTElement    *theWoodObject;

    switch( theObject->WhoAreYou() )
    {
      case aGussetPlate:
      case aTBGussetPlate:
        theGussetPlate = (CGussetPlate *)theObject;
        twoPointMatch =
          theGussetPlate->BUP_WhichOneOfUsGotSelected(
            theHitPtAndObjectPtr->thisHitPoint,
          (CGussetPlate *)(theHitPtAndObjectPtr->thisObjectPointer) );
        if( twoPointMatch )
        {
        }
        else
          twoPointMatch = FALSE;
        break;

      case aWoodElement:
      case aTopBottomWoodElement:
      case aRightLeftWoodElement:
        theWoodObject = (CRegularWoodTElement *)theObject;
        twoPointMatch =
          theWoodObject->BUP_WhichOneOfUsGotSelected(
            theHitPtAndObjectPtr->thisHitPoint,
          (CGussetPlate *)(theHitPtAndObjectPtr->thisObjectPointer) );
        if( twoPointMatch )
        {
        }
        else
          twoPointMatch = FALSE;
        break;

    }

    return ( twoPointMatch );
  }

Boolean    CGussetPane::SelectAnObject( Point hitPt, short modifierKeys )

{

  Boolean            theSameHitPoint;
  HitPtAndObjectPtr      theHitPtAndObjectPtr;
  Boolean            gussetPlateSelected;
  CGussetPlate         *theGussetPlate;
  CRegularWoodTElement    *theWoodObject;
  Boolean            thePlateGotSelected;

  theHitPtAndObjectPtr.thisObjectPointer = itsGussetPlate;
  theHitPtAndObjectPtr.thisHitPoint = hitPt;

      /* setting theSelectedObject to Null so that only one
        object is selected for now.. */
  theSelectedObject = aNullObject;
  objectAlreadySelected = FALSE;
  gussetPlateSelected = FALSE;

      /* we want to see if click occurred on one of the objects */

  if( ConnectAreaBeingDefined )
  {
    if( theObject )    /* define area for wood objects only */
      if( theObject->WhoAreYou() != aWoodElement )
        ConnectAreaBeingDefined = FALSE;
      else
      {
        if (firstPointLocated )
        {
          ((CRegularWoodTElement *)theObject)->
            Define_ConnectorPolygon( itsGussetPlate, hitPt );
        }
        else
        {
          thePlateGotSelected = itsGussetPlate->
                BUP_WhichOneOfUsGotSelected(
                     hitPt,itsGussetPlate );
          if (thePlateGotSelected )
            if( itsGussetPlate->masterPlateFlag )
            {
              firstPointLocated = TRUE;
            }
        }
        /* if this is the first click, see if the click*/
        /* is on the MasterPlateLocation if not ignore click*/
        /* if click is in master plate location and is first click*/
        /* then first click is located */

      }

  }
  else
  {
    if( !objectAlreadySelected )
      theObject = (CAbstractObject *)theListOfObjects->
              FindItem1( HitSameBUP_ANY_Object,
              ( long )( &theHitPtAndObjectPtr) );

    if( theObject )
    {
      switch( theObject->WhoAreYou() )
      {
        case aGussetPlate:
        case aTBGussetPlate:
          theGussetPlate = (CGussetPlate *)theObject;
          theSelectedObject = aNodeObject;
          objectAlreadySelected = TRUE;
          theSelectedNodeObject = itsGussetPlate;
          theObject = (CGussetPlate *)itsGussetPlate;
          theNodeObject = itsGussetPlate;
          if( ! (modifierKeys == optionKey ) )
          {
            thePreviouslySelectedObject = aTrussElementObject;
          }
          theListOfObjects->BringFront( theObject );
          break;

        case aWoodElement:
        case aTopBottomWoodElement:
        case aRightLeftWoodElement:
          theWoodObject = (CRegularWoodTElement *)theObject;
          theSelectedObject = aTrussElementObject;
          objectAlreadySelected = TRUE;
          theSelectedTEObject = (CTrussElementObject *)theWoodObject;
          theObject = (CRegularWoodTElement *)theWoodObject;
          theTElementObject = (CRegularWoodTElement *)theWoodObject;
          if( ! (modifierKeys == optionKey ) )
          {
            thePreviouslySelectedObject = aTrussElementObject;
          }
          theListOfObjects->BringFront( theObject );
          break;

      }
    }
  }
  return objectAlreadySelected;
}

