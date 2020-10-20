/****
 * CPlateBUPMouseTask.c
 *
 *   objects Mouse task class for a typical Object.
 *
 ****/

#include "CObjectMouseTask.phs"
#include "CGussetPane.h"
#include "CPlateBUPMouseTask.h"


void  CPlateBUPMouseTask::BeginTracking(  Point *startPt)

{
  if ( noObjectSelectedFlag )
  {
    /* do nothing */
  }
  else
  {
    switch( theObject->WhoAreYou() )
    {
      case aGussetPlate:
      case aTBGussetPlate:
        theGussetPlate = (CGussetPlate *)theObject;
        break;

      case aWoodElement:
      case aTopBottomWoodElement:
      case aRightLeftWoodElement:
        theWoodObject = (CRegularWoodTElement *)theObject;
        break;

    }
  }

}



void  CPlateBUPMouseTask::KeepTracking( Point *currPt, Point *prevPt,
                             Point *startPt)
{
  Rect      myRect;
  Point      hitPt;
  Boolean      autoScallingPerformed;

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
      theGussetPlate->theHitPoint = *prevPt;
      theGussetPlate->UpDateObject();
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
        theGussetPlate->theHitPoint = *currPt;
        theGussetPlate->UpDateObject();
      }
      else
      {
          /* erase the previous object */
        theGussetPlate->theHitPoint = *prevPt;
        theGussetPlate->UpDateObject();

          /* draw current object */
        theGussetPlate->theHitPoint = *currPt;
        theGussetPlate->UpDateObject();
      }
    }
    else
    {
        /* I should never get here, but just in case, do nothing */
    }
  }
  autoScallingPerformed = itsGussetPane->AutoScroll( *currPt );
  if( autoScallingPerformed )
    itsGussetPane->Refresh();
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

void  CPlateBUPMouseTask::EndTracking( Point *currPt, Point *prevPt,
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
      theGussetPlate->theHitPoint = *prevPt;
      theGussetPlate->UpDateObject();
      theGussetPlate->BUPErase();
    }
    else
    if ( (!EqualPt( *currPt, *startPt ))&&( EqualPt(*currPt, *prevPt)) )
    {
      theGussetPlate->theHitPoint = *startPt;
      theGussetPlate->UpDateObject();
      theGussetPlate->BUPErase();
    }
    else
    if ( (!EqualPt( *currPt, *startPt ))&&(! EqualPt(*currPt, *prevPt)) )
    {
      if ( EqualPt( *startPt, *prevPt ) )
      {
          /* erase start */
        theGussetPlate->theHitPoint = *startPt;
        theGussetPlate->UpDateObject();
        theGussetPlate->BUPErase();
          /* draw current object */
        theGussetPlate->theHitPoint = *currPt;
        theGussetPlate->UpDateObject();
      }
      else
      {
          /* erase start */
        theGussetPlate->theHitPoint = *startPt;
        theGussetPlate->UpDateObject();
        theGussetPlate->BUPErase();
          /* erase the previous object */
        theGussetPlate->theHitPoint = *prevPt;
        theGussetPlate->UpDateObject();
        theGussetPlate->BUPErase();

          /* draw current object */
        theGussetPlate->theHitPoint = *currPt;
        theGussetPlate->UpDateObject();
      }
    }

          /* erase currPt for all  cases */
          /* this is very important because it updates
            the object to the currPt */
          /* perform draw across the board takes care of drawing*/
    theGussetPlate->theHitPoint = *currPt;
    theGussetPlate->UpDateObject();


        /* perform draw across the board except the case where
          startPt is equal to both prevPt, and currPt.
          i.e the cursor didn't move */


      /* the following statement replaces the below commented lines*/
      /* it is the quick and dirty way of fixing bleeding in the */
      /* case where there is a closed loop ...*/
      /* this way of fixing my problem causes pain in the eyes */
    itsGussetPane->Refresh();


                /* for undoing */
    newhitPt = *currPt;
    oldhitPt = *startPt;
  }
}

void  CPlateBUPMouseTask::Undo( void )
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
    theGussetPlate->BUP_UnSelectYourself();
    theGussetPlate->BUPErase();

        /* Xoring newhitPt, i.e creating new point, i.e startPt */

    theGussetPlate->theHitPoint = newhitPt;

    theGussetPlate->UpDateObject();

    /* once we perform undo/redo with the crazy Xoring, the quick
      and dirty way of clearing the mess created by Xoring if
      two object cross or share a line, is to redraw everything
      in cluster using patCopy rather than Xoring */


    itsGussetPane->Refresh();
  }
}


