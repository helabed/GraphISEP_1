/****
 * CContinuousLoad.c
 *
 *  CContinuousLoad object class for a typical CTrussPane class
 *
 ****/
#include "CSquareObject.phs"
#include "CContinuousLoad.h"


/*** Global Variables ***/

extern  CBartender *gBartender;
extern   short    gClicks;



void CContinuousLoad::Draw( void )
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

  HandleArrows();
}

void CContinuousLoad::HandleArrows()
{
  float    bSlope,tSlope;
  Point    arrowTail,arrowHead;
  int      arrowCounter = 0;

  arrowTail.h = 0; arrowTail.v = 0; arrowHead.h = 0; arrowHead.v = 0;

  tSlope = ( ((float)(topRightCorner.v - topLeftCorner.v ) ) /
        ( (float)(topRightCorner.h -topLeftCorner.h) ) );

  bSlope = ( ((float)(bottomRightCorner.v - bottomLeftCorner.v ) ) /
        ( (float)(bottomRightCorner.h -bottomLeftCorner.h) ) );

  arrowHead.h = bottomLeftCorner.h;
  arrowHead.v = bottomLeftCorner.v;

  arrowTail.v = topLeftCorner.v;
  arrowTail.h = arrowHead.h;

  MoveTo( arrowTail.h, arrowTail.v);
  LineTo( arrowHead.h, arrowHead.v);
  if( arrowHead.v >= arrowTail.v )
  {
    LineTo( arrowHead.h + ARROW_H_width, arrowHead.v - ARROW_H_height);
    MoveTo( arrowHead.h, arrowHead.v);
    LineTo( arrowHead.h - ARROW_H_width, arrowHead.v - ARROW_H_height);
  }
  else
  {
    LineTo( arrowHead.h + ARROW_H_width, arrowHead.v + ARROW_H_height);
    MoveTo( arrowHead.h, arrowHead.v);
    LineTo( arrowHead.h - ARROW_H_width, arrowHead.v + ARROW_H_height);
  }
  arrowCounter = 1;

  while( arrowTail.h <= (topRightCorner.h - ARROW_SPACING))
  {
    arrowTail.h = topLeftCorner.h + ARROW_SPACING * arrowCounter;
    arrowTail.v = topLeftCorner.v + (int)(tSlope * ARROW_SPACING *
                            arrowCounter);

    arrowHead.h = arrowTail.h;
    arrowHead.v = bottomLeftCorner.v + (int)( bSlope * ARROW_SPACING *
                            arrowCounter);

    MoveTo( arrowTail.h, arrowTail.v);
    LineTo( arrowHead.h, arrowHead.v);
    if( arrowHead.v >= arrowTail.v )
    {
      LineTo( arrowHead.h + ARROW_H_width, arrowHead.v -
                            ARROW_H_height);
      MoveTo( arrowHead.h, arrowHead.v);
      LineTo( arrowHead.h - ARROW_H_width, arrowHead.v -
                            ARROW_H_height);
    }
    else
    {
      LineTo( arrowHead.h + ARROW_H_width, arrowHead.v +
                            ARROW_H_height);
      MoveTo( arrowHead.h, arrowHead.v);
      LineTo( arrowHead.h - ARROW_H_width, arrowHead.v +
                            ARROW_H_height);
    }
    arrowCounter++;
  }
  arrowHead.h = bottomRightCorner.h;
  arrowHead.v = bottomRightCorner.v;

  arrowTail.v = topRightCorner.v;
  arrowTail.h = arrowHead.h;

  MoveTo( arrowTail.h, arrowTail.v);
  LineTo( arrowHead.h, arrowHead.v);
  if( arrowHead.v >= arrowTail.v )
  {
    LineTo( arrowHead.h + ARROW_H_width, arrowHead.v - ARROW_H_height);
    MoveTo( arrowHead.h, arrowHead.v);
    LineTo( arrowHead.h - ARROW_H_width, arrowHead.v - ARROW_H_height);
  }
  else
  {
    LineTo( arrowHead.h + ARROW_H_width, arrowHead.v + ARROW_H_height);
    MoveTo( arrowHead.h, arrowHead.v);
    LineTo( arrowHead.h - ARROW_H_width, arrowHead.v + ARROW_H_height);
  }
}


void CContinuousLoad::MoveYourself( void )
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
void  CContinuousLoad::FromtheHitPointToCorners( void )
{
  if ( topLeftCornerFlag )
  {
    if ( (theHitPoint.h - offSet.h ) > (topRightCorner.h - SMALL_LENGTH))
    {
      topLeftCorner.h = topRightCorner.h - SMALL_LENGTH;
    }else
    {
      topLeftCorner.h = theHitPoint.h - offSet.h;
    }
    topLeftCorner.v = theHitPoint.v - offSet.v;

    bottomLeftCorner.h = topLeftCorner.h;
  }

  else if ( topRightCornerFlag )
  {
    if ( ((theHitPoint.h - offSet.h ) < topLeftCorner.h + SMALL_LENGTH) )
    {
      topRightCorner.h = topLeftCorner.h + SMALL_LENGTH;
    }else
    {
      topRightCorner.h = theHitPoint.h - offSet.h;
    }
    topRightCorner.v = theHitPoint.v - offSet.v;

    bottomRightCorner.h = topRightCorner.h;
  }

  else if ( bottomLeftCornerFlag )
  {
    if ( (theHitPoint.h - offSet.h ) > (bottomRightCorner.h - SMALL_LENGTH))
    {
      bottomLeftCorner.h = bottomRightCorner.h - SMALL_LENGTH;
    }else
    {
      bottomLeftCorner.h = theHitPoint.h - offSet.h;
    }
    bottomLeftCorner.v = theHitPoint.v - offSet.v;
    bottomRightCorner.v = bottomLeftCorner.v;
    topLeftCorner.h = bottomLeftCorner.h;
  }

  else if ( bottomRightCornerFlag )
  {
    if ( ((theHitPoint.h - offSet.h ) < bottomLeftCorner.h + SMALL_LENGTH) )
    {
      bottomRightCorner.h = bottomLeftCorner.h + SMALL_LENGTH;
    }else
    {
      bottomRightCorner.h = theHitPoint.h - offSet.h;
    }
    bottomRightCorner.v = theHitPoint.v - offSet.v;
    bottomLeftCorner.v = bottomRightCorner.v;
    topRightCorner.h = bottomRightCorner.h;
  }
}


void  CContinuousLoad::FromCornersToItsCenterPoint( void )
{
  itsCenterPoint.v = (( bottomLeftCorner.v + topLeftCorner.v ) / 2 +
            ( bottomRightCorner.v + topRightCorner.v ) / 2)/2;
  itsCenterPoint.h = (( bottomLeftCorner.h + topLeftCorner.h ) / 2 +
            ( bottomRightCorner.h + topRightCorner.h ) / 2)/2;

}


Boolean CContinuousLoad::ConnectYourselfToTE(
        struct CTrussElementObject  *theSelectedTEObject )
{
  return FALSE;
}
