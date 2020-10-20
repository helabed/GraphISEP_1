/****
 * CContinuousMoment.c
 *
 *  CContinuousMoment object class for a typical CTrussPane class
 *
 ****/
#include "CSquareObject.phs"
#include "CContinuousMoment.h"


/*** Global Variables ***/

extern  CBartender *gBartender;
extern   short    gClicks;



void CContinuousMoment::Draw( void )
{
  PenState     pnState;
  Rect      myRect;


  GetPenState ( &pnState);/* to save the pen setting */
  PenPat( black );

  MoveTo( bottomLeftCorner.h, bottomLeftCorner.v );
  LineTo( bottomRightCorner.h, bottomRightCorner.v );
  LineTo( topRightCorner.h, topRightCorner.v );
  LineTo( topLeftCorner.h, topLeftCorner.v );
  LineTo( bottomLeftCorner.h, bottomLeftCorner.v );

  SetPenState ( &pnState);/* to resotre pen settting */

}

void CContinuousMoment::MoveYourself( void )
{
  Point    temp1, temp2;
  int      XLengthToBottomRight, YLengthToBottomRight;
  int      XLengthToTopRight, YLengthToTopRight;
  int      XLengthToTopLeft, YLengthToTopLeft;

  /* bottomLeftCorner is our Quadrelateral anchor point */

  XLengthToBottomRight = bottomRightCorner.h - bottomLeftCorner.h;
  YLengthToBottomRight = bottomRightCorner.v - bottomLeftCorner.v;
  XLengthToTopRight = topRightCorner.h - bottomLeftCorner.h;
  YLengthToTopRight = bottomLeftCorner.v - topRightCorner.v;
  XLengthToTopLeft = bottomLeftCorner.h - topLeftCorner.h;
  YLengthToTopLeft = bottomLeftCorner.v - topLeftCorner.v;

  bottomLeftCorner.h = theHitPoint.h - offSet.h;
  bottomLeftCorner.v = theHitPoint.v - offSet.v;

  bottomRightCorner.h = bottomLeftCorner.h + XLengthToBottomRight;
  bottomRightCorner.v = bottomLeftCorner.v + YLengthToBottomRight;

  topLeftCorner.h = bottomLeftCorner.h - XLengthToTopLeft;
  topLeftCorner.v = bottomLeftCorner.v - YLengthToTopLeft;

  topRightCorner.h = bottomLeftCorner.h +  XLengthToTopRight;
  topRightCorner.v = bottomLeftCorner.v -  YLengthToTopRight;

  itsCenterPoint.v = (( bottomLeftCorner.v + topLeftCorner.v ) / 2 +
            ( bottomRightCorner.v + topRightCorner.v ) / 2)/2;
  itsCenterPoint.h = (( bottomLeftCorner.h + topLeftCorner.h ) / 2 +
            ( bottomRightCorner.h + topRightCorner.h ) / 2)/2;

  DragYourself();
}
        /* rather than changing all the ResizeYourself(), we*/
        /* only need to change this one */
void  CContinuousMoment::FromtheHitPointToCorners( void )
{
  if ( topLeftCornerFlag )
  {
    if( ((theHitPoint.h - offSet.h ) < bottomLeftCorner.h) )
    {
      topLeftCorner.h = bottomLeftCorner.h;
    }else
    {
      if ( (theHitPoint.h - offSet.h ) > (topRightCorner.h - SMALL_LENGTH))
      {
        topLeftCorner.h = topRightCorner.h - SMALL_LENGTH;
      }else
      {
        topLeftCorner.h = theHitPoint.h - offSet.h;
      }
    }
    topLeftCorner.v = theHitPoint.v - offSet.v;
  }

  else
  if ( topRightCornerFlag )
  {
    if( ((theHitPoint.h - offSet.h ) > bottomRightCorner.h) )
    {
      topRightCorner.h = bottomRightCorner.h;
    }
    else
    {
    if ( ((theHitPoint.h - offSet.h ) < topLeftCorner.h + SMALL_LENGTH) )
      {
        topRightCorner.h = topLeftCorner.h + SMALL_LENGTH;
      }else
      {
        topRightCorner.h = theHitPoint.h - offSet.h;
      }
    }
    topRightCorner.v = theHitPoint.v - offSet.v;
  }

  else
  if ( bottomLeftCornerFlag )
  {
    if( (theHitPoint.h - offSet.h ) > topLeftCorner.h )
    {
      bottomLeftCorner.h = topLeftCorner.h;
    }
    else
    {
      bottomLeftCorner.h = theHitPoint.h - offSet.h;
    }
    bottomLeftCorner.v = theHitPoint.v - offSet.v;

    bottomRightCorner.v = theHitPoint.v - offSet.v;
  }

  else
  if ( bottomRightCornerFlag )
  {
    if( (theHitPoint.h - offSet.h ) < topRightCorner.h )
    {
      bottomRightCorner.h = topRightCorner.h;
    }
    else
    {
      bottomRightCorner.h = theHitPoint.h - offSet.h;
    }
    bottomRightCorner.v = theHitPoint.v - offSet.v;

    bottomLeftCorner.v = theHitPoint.v - offSet.v;
  }
}


void  CContinuousMoment::FromCornersToItsCenterPoint( void )
{
  itsCenterPoint.v = (( bottomLeftCorner.v + topLeftCorner.v ) / 2 +
            ( bottomRightCorner.v + topRightCorner.v ) / 2)/2;
  itsCenterPoint.h = (( bottomLeftCorner.h + topLeftCorner.h ) / 2 +
            ( bottomRightCorner.h + topRightCorner.h ) / 2)/2;

}

