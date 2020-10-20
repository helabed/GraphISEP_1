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

#include "CTrussPane.phs"


/*** Global Variables ***/

extern  CBartender *gBartender;
extern   short    gClicks;

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

      static void Perform_Draw(
                  CAbstractObject *theObject )
      {
          theObject->ReDraw();
      }


       /***
       * perform draw nodes  only for cluster redrawing
       */

      static void Perform_Draw_Nodes( CNodeObject  *theObject )
      {

        theObject->DrawNodeOnly();

      }



void CTrussPane::DoClick(Point hitPt, short modifierKeys, long when)

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

/*  pinRect.top = 0;
  pinRect.left = 0;
  pinRect.bottom = 1000;
  pinRect.right = 1000;
*/

  if( theObject )
    theObject->UnSelectYourself();


  objectSelected = SelectAnObject( hitPt, modifierKeys);
  if (  objectSelected )
  {

    if ( gClicks == DOUBLE_CLICKS )
    {
      theObject->DoYourDialog();
      return;
    }


    /* warning this is a kludge */
    if ( (theSelectedObject == aTrussElementObject) ||
       (theSelectedObject == aNodeObject) )
    {
      NodesCluster->DoForEach(
                Perform_Selection_UnSelection );
        /* this is done to erase the boundary condition*/
        /* picture before going to ObjectMouseTask*/
    }



    /* this is where you should do things if an object was selected
    or not, i.e use this if statment */

    switch( thePreviouslySelectedObject )
    {
      case aNodeObject:
        connectionPerformed = ConnectObjectsToNode( modifierKeys );
        if ( connectionPerformed )
        {
          NodesCluster->DoForEach( Perform_Draw_Nodes );

          return;      /* that means that the do click was used
                    somehow so return, i.e no purpose
                    in going through rest of routine */
        }
        break;
      case aTrussElementObject:
        connectionPerformed = ConnectObjectsToTE( modifierKeys );
        if ( connectionPerformed )
        {
          NodesCluster->DoForEach( Perform_Draw_Nodes );

          return;      /* that means that the do click was used
                    somehow so return, i.e no purpose
                    in going through rest of routine */
        }
        break;
    }

  }
  else    /* no object was selected, don't go to ObjectMouse task*/
  {
    if( theObject )
    {
      theObject->UnSelectYourself();
      if( (theObject->WhoAreYou() == aGenericNode ) ||
          ( (theObject->WhoAreYou() == aGussetPlate ) ||
          (theObject->WhoAreYou() == aTBGussetPlate ) ) )
      {
        ((CNodeObject *)theObject)->AddPicture();
      }
      NodesCluster->DoForEach( Perform_Draw_Nodes );
      theObject = NULL;
    }
    return;
  }



    /* UnSelection is needed in here so that if a previous object has
      been selected, it becomes unselected. The CObjectMouseTask takes
      care of selecting the Object to be moved       */


  if( theObject )
    theObject->UnSelectYourself();

    /* create an instance of the CObjectMouseTask class and initialize
      it*/
  myMover = new( CObjectMouseTask );

    /* to show Undo/Redo string in the STR# 130 resource */
  myMover->IObjectMouseTask( 1 );

    /* to tell the CObjectMouseTask what object it is dealing with,
      i.e what kind and which instance of that object */
  myMover->theSelectedObject = theSelectedObject;

  myMover->itsTrussPane = this;



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

/*  myMover->Dispose(); putting this here made the program bomb??*/
/* the reason why the program bombed is that the Notify() method disposes*/
/* of the last task done, so don't worry about it, you only have one live*/
/* task, and not an accumulation of new( mover) in the AppHeap...*/
}
