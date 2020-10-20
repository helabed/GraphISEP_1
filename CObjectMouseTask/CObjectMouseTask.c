/****
 * CObjectMouseTask.c
 *
 *   objects Mouse task class for a typical Object.
 *
 ****/

#include "CObjectMouseTask.phs"
#include "CTrussPane.h"

void  CObjectMouseTask::BeginTracking(  Point *startPt)

{
  if ( noObjectSelectedFlag )
  {
    /* do nothing */
  }
  else
  {
    /* do nothing in here because, by the time
    the object gets here, it is UnSelected, and already drawn.
    i.e let the KeepTracking() take care of it */
  }

}

void  CObjectMouseTask::KeepTracking( Point *currPt, Point *prevPt,
                             Point *startPt)
{
  Rect      myRect;
  Point      hitPt;
  Boolean      autoScallingPerformed;

  autoScallingPerformed = itsTrussPane->AutoScroll( *currPt );
  if( autoScallingPerformed )
    itsTrussPane->Refresh();

  if ( noObjectSelectedFlag )
  {
    /* do nothing */
  }
  else
  {
    if ( (EqualPt ( *currPt, *startPt )) && (EqualPt ( *currPt, *prevPt )))
    {
      /* do nothing */
    }
    else
    if ( ( EqualPt( *currPt, *startPt )) && (! EqualPt( *currPt, *prevPt )))
    {
        /* in here we only erase( xOr)
          prevPt, i.e we didn't xOr currPt */

        /* erase previous object */
      theObject->theHitPoint = *prevPt;
      theObject->UpDateObject();
    }
    else
    if ( ( ! EqualPt( *currPt, *startPt )) && (EqualPt(*currPt, *prevPt)) )
    {
      /* do nothing */
    }
    else
    if ( (! EqualPt( *currPt, *startPt )) && (! EqualPt(*currPt, *prevPt)))
    {
      if ( EqualPt( *startPt, *prevPt ) )
      {
          /* draw current object */
        theObject->theHitPoint = *currPt;
        theObject->UpDateObject();
      }
      else
      {
          /* erase the previous object */
        theObject->theHitPoint = *prevPt;
        theObject->UpDateObject();

          /* draw current object */
        theObject->theHitPoint = *currPt;
        theObject->UpDateObject();
      }
    }
    else
    {
        /* I should never get here, but just in case, do nothing */
    }
  }
}

/**********
 *
 * the purpose of the endtracking is to clean up our act after the mouse
 * is up. we will first Xor the gray of KeepTracking, then replace it with
 * black. Note we Xor with black both startPt and currPt, the idea is that
 * Xoring something will erase it. finally we set instance variables to
 * their values. These are used in case there is an undo/redo command.
 * notice how swapping was done to be able to undo/redo
 *
 ******/
         /***
         * perform draw for cluster redrawing
         */

        static void Perform_DoTEDraw( CTrussElementObject  *theObject )
        {
          theObject->DoDrawingFinal();
        }
        static void Perform_DoNDraw( CNodeObject  *theObject )
        {
          theObject->DoDrawing();
        }
        static void Perform_Draw( CAbstractObject  *theObject )
        {
          theObject->DrawFinal();
        }

         /***
         * perform draw nodes  only for cluster redrawing
         */

        static void Perform_Draw_Nodes( CNodeObject  *theObject )
        {
          theObject->DrawNodeOnly();
        }

void  CObjectMouseTask::EndTracking( Point *currPt, Point *prevPt,
                            Point *startPt)
{
  Rect  myRect;
  Point  hitPt;

  if ( noObjectSelectedFlag )
  {
    /* do nothing */
  }
  else
  {
    if ( (EqualPt ( *currPt, *startPt )) && (EqualPt ( *currPt, *prevPt )) )
    {
      /* do nothing */
    }
    else
    if ( ( EqualPt( *currPt, *startPt )) && (! EqualPt( *currPt, *prevPt )))
    {
      theObject->theHitPoint = *prevPt;
      theObject->UpDateObject();
      theObject->Erase();
    }
    else
    if ( (!EqualPt( *currPt, *startPt ))&&( EqualPt(*currPt, *prevPt)) )
    {
      theObject->theHitPoint = *startPt;
      theObject->UpDateObject();
      theObject->Erase();
    }
    else
    if ( (!EqualPt( *currPt, *startPt ))&&(! EqualPt(*currPt, *prevPt)) )
    {
      if ( EqualPt( *startPt, *prevPt ) )
      {
          /* erase start */
        theObject->theHitPoint = *startPt;
        theObject->UpDateObject();
        theObject->Erase();
          /* draw current object */
        theObject->theHitPoint = *currPt;
        theObject->UpDateObject();
      }
      else
      {
          /* erase start */
        theObject->theHitPoint = *startPt;
        theObject->UpDateObject();
        theObject->Erase();
          /* erase the previous object */
        theObject->theHitPoint = *prevPt;
        theObject->UpDateObject();
        theObject->Erase();

          /* draw current object */
        theObject->theHitPoint = *currPt;
        theObject->UpDateObject();
      }
    }

          /* erase currPt for all  cases */
          /* this is very important because it updates
            the object to the currPt */
          /* perform draw across the board takes care of drawing*/
    theObject->theHitPoint = *currPt;
    theObject->UpDateObject();

        /* perform draw across the board except the case where
          startPt is equal to both prevPt, and currPt.
          i.e the cursor didn't move */


      /* the following statement replaces the below commented lines*/
      /* it is the quick and dirty way of fixing bleeding in the */
      /* case where there is a closed loop ...*/
      /* this way of fixing my problem causes pain in the eyes */
/*    theObject->itsTrussPane->Refresh();

/* */  TElementsCluster->DoForEach( Perform_DoTEDraw );
    ContLoadsAndMoments->DoForEach( Perform_Draw );
    ConcLoadsAndMoments->DoForEach( Perform_Draw );
    NodesCluster->DoForEach( Perform_DoNDraw );

    NodesCluster->DoForEach( Perform_Draw_Nodes );
/* */  theObject->SelectYourself();

                /* for undoing */
    newhitPt = *currPt;
    oldhitPt = *startPt;
  }
}

void  CObjectMouseTask::Undo( void )
{
  Point   temp;
  PenState  pnState;

  temp = oldhitPt;
  oldhitPt = newhitPt;
  newhitPt = temp;

  if ( noObjectSelectedFlag )
  {
    /* do nothing */
  }
  else
  {
        /* Xoring oldhitPt, i.e erasing  old point, i.e currPt */
    theObject->UnSelectYourself();
    theObject->Erase();

        /* Xoring newhitPt, i.e creating new point, i.e startPt */

    theObject->theHitPoint = newhitPt;

    theObject->UpDateObject();

    /* once we perform undo/redo with the crazy Xoring, the quick
      and dirty way of clearing the mess created by Xoring if
      two object cross or share a line, is to redraw everything
      in cluster using patCopy rather than Xoring */


    TElementsCluster->DoForEach( Perform_DoTEDraw );
    ContLoadsAndMoments->DoForEach( Perform_Draw );
    ConcLoadsAndMoments->DoForEach( Perform_Draw );
    NodesCluster->DoForEach( Perform_DoNDraw );

    NodesCluster->DoForEach( Perform_Draw_Nodes );
    theObject->SelectYourself();
  }
}

/************
 * Initializing the ObjectMouseTask
 *
 ************/
void  CObjectMouseTask::IObjectMouseTask(short aNameIndex )
{
      /* aNameIndex contains a the index of STR# 130, i.e the
        Undo move/Redo move string */

  CMouseTask::IMouseTask( aNameIndex );
}

/*****
 * cast yourself into the correct object based on theSelectedObject
 *
 ******/

void  CObjectMouseTask::CastYSelfIntoCorrectObject( void )
{
      /* this is to see what object we are dealing with and to cast
        our theObject pointer to that object */

  noObjectSelectedFlag = FALSE;

  switch( theSelectedObject )
  {
    case aContLoadOrMoment:
      theObject = theContLoadOrMoment;
      break;

    case aConcLoadOrMoment:
      theObject = theConcLoadOrMoment;
      break;

    case aNodeObject:
      theObject = theNodeObject;
      break;

    case aTrussElementObject:
      theObject = theTElementObject;
      break;

    default:
      noObjectSelectedFlag = TRUE;
      break;
  }
}

