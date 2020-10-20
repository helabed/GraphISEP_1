/****
 * CQuadrelateralObject.c
 *
 *  CQuadrelateral object class for a typical CTrussPane class
 *
 ****/
#include "CSquareObject.phs"
#include "CQuadrelateralObject.h"
#include "CTrussElementObject.h"
#include "CClustOfContLoadsAndMoments.h"
#include "CTrussPane.h"

/*** Global Variables ***/

extern  CBartender *gBartender;
extern   short    gClicks;



void CQuadrelateralObject::InitializeYourself( void )
{
  inherited::InitializeYourself();
  itsTElement = NULL;
  loadAlongAllMember = FALSE;
}



void CQuadrelateralObject::Draw( void )
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

void CQuadrelateralObject::MoveYourself( void )
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
void  CQuadrelateralObject::FromtheHitPointToCorners( void )
{
    if ( topLeftCornerFlag )
    {
      topLeftCorner.h = theHitPoint.h - offSet.h;
      topLeftCorner.v = theHitPoint.v - offSet.v;
    }

    if ( topRightCornerFlag )
    {
      topRightCorner.h = theHitPoint.h - offSet.h;
      topRightCorner.v = theHitPoint.v - offSet.v;
    }

    if ( bottomLeftCornerFlag )
    {
      bottomLeftCorner.h = theHitPoint.h - offSet.h;
      bottomLeftCorner.v = theHitPoint.v - offSet.v;
    }

    if ( bottomRightCornerFlag )
    {
      bottomRightCorner.h = theHitPoint.h - offSet.h;
      bottomRightCorner.v = theHitPoint.v - offSet.v;
    }
}


void  CQuadrelateralObject::FromCornersToItsCenterPoint( void )
{
  itsCenterPoint.v = (( bottomLeftCorner.v + topLeftCorner.v ) / 2 +
            ( bottomRightCorner.v + topRightCorner.v ) / 2)/2;
  itsCenterPoint.h = (( bottomLeftCorner.h + topLeftCorner.h ) / 2 +
            ( bottomRightCorner.h + topRightCorner.h ) / 2)/2;

}

Boolean  CQuadrelateralObject::CreateTE2ndConnecRatio()
{
  double    bSlope;
  double    offSetLength;
  double    TElementLength;
  Point    TE1stEnd, TE2ndEnd;
  Point    aPoint;
  int      xLength, yLength;
  Point    connectToThisPoint;
  Boolean    TrussElementisOK = FALSE;

  TE1stEnd.h = itsTElement->its1stEnd.h;
  TE1stEnd.v = itsTElement->its1stEnd.v;
  TE2ndEnd.h = itsTElement->its2ndEnd.h;
  TE2ndEnd.v = itsTElement->its2ndEnd.v;

  if( Abs((TE2ndEnd.h -TE1stEnd.h)) <= SMALL_LENGTH )
    return FALSE;    /* no connection allowed division by zero!!*/

  bSlope = ( ((double)(TE2ndEnd.v - TE1stEnd.v ) ) /
        ( (double)(TE2ndEnd.h -TE1stEnd.h) ) );

  connectToThisPoint.h = ((int)((( double)(TE2ndEnd.h -TE1stEnd.h))
          *TElementConnectionRatio)) + TE1stEnd.h;
  connectToThisPoint.v = ((int)((( double)(TE2ndEnd.v -TE1stEnd.v))
          *TElementConnectionRatio)) + TE1stEnd.v;

  if( (TE2ndEnd.h - TE1stEnd.h) >= SMALL_LENGTH )
  {
    /* case 1 right hemisphere */
    if( loadAlongAllMember )
    {
      TElementConnectionRatio = 0.0;
      TElement2ndConnectionRatio = 1.0;
      TrussElementisOK =  TRUE;
    }
    else
    {
      if ( ( bottomRightCorner.h - bottomLeftCorner.h ) <=
                    (TE2ndEnd.h - connectToThisPoint.h) )
      {
        xLength = ( bottomRightCorner.h - bottomLeftCorner.h );
        yLength = ( ( int)(((double)(xLength))*bSlope)) ;
        aPoint.h = connectToThisPoint.h + xLength;
        aPoint.v = connectToThisPoint.v + yLength;


        offSetLength = ( double) sqrt( (double)(( ((double)
          (aPoint.h-TE1stEnd.h)) * ((double)(aPoint.h-TE1stEnd.h))) +
          ( ((double)(aPoint.v-TE1stEnd.v))*((double)(aPoint.v-TE1stEnd.v)))));

        TElementLength = (double) sqrt((double)(( (((double)(TE2ndEnd.v -
                TE1stEnd.v)) * ((double)(TE2ndEnd.v -TE1stEnd.v) )) +
                  ( ((double)(TE2ndEnd.h -TE1stEnd.h))*
                  ((double)(TE2ndEnd.h -TE1stEnd.h)) ) ) ) );

        TElement2ndConnectionRatio = (float)( offSetLength / TElementLength);
        TrussElementisOK =  TRUE;
      }
      else if( ! ( EqualPt(TE2ndEnd , connectToThisPoint) ) )
      {
        TElement2ndConnectionRatio = 1.0;
        TrussElementisOK =  TRUE;
      }
      else
        TrussElementisOK =  FALSE;
    }
  }
  else if( (TE1stEnd.h - TE2ndEnd.h) >= SMALL_LENGTH )
  {
    /* case 2 left hemisphere */
    if( loadAlongAllMember )
    {
      TElementConnectionRatio = 1.0;
      TElement2ndConnectionRatio = 0.0;
      TrussElementisOK =  TRUE;
    }
    else
    {
      if ( ( bottomRightCorner.h - bottomLeftCorner.h ) <=
                    (TE1stEnd.h - connectToThisPoint.h) )
      {
        xLength = ( bottomRightCorner.h - bottomLeftCorner.h );
        yLength = ( ( int)(((double)(xLength))*bSlope)) ;
        aPoint.h = connectToThisPoint.h + xLength;
        aPoint.v = connectToThisPoint.v + yLength;


        offSetLength = ( double) sqrt( (double)(( ((double)
          (aPoint.h-TE1stEnd.h)) * ((double)(aPoint.h-TE1stEnd.h))) +
          ( ((double)(aPoint.v-TE1stEnd.v))*((double)(aPoint.v-TE1stEnd.v)))));

        TElementLength = (double) sqrt((double)(( (((double)(TE2ndEnd.v -
                TE1stEnd.v)) * ((double)(TE2ndEnd.v -TE1stEnd.v) )) +
                  ( ((double)(TE2ndEnd.h -TE1stEnd.h))*
                  ((double)(TE2ndEnd.h -TE1stEnd.h)) ) ) ) );

        TElement2ndConnectionRatio = (float)( offSetLength / TElementLength);
        TrussElementisOK =  TRUE;
      }
      else if( ! ( EqualPt(TE1stEnd , connectToThisPoint) ) )
      {
        TElement2ndConnectionRatio = 0;
        TrussElementisOK =  TRUE;
      }
      else
      TrussElementisOK = FALSE;
    }
  }
  else
    TrussElementisOK = FALSE;


  return TrussElementisOK;
}


Boolean CQuadrelateralObject::ConnectYourselfToTE(
        struct CTrussElementObject  *theSelectedTEObject )
{
  Boolean    IsItOKToConnect = FALSE;

  if( ! this->IamConnected )
  {
    itsTElement = theSelectedTEObject;
    TElementConnectionRatio = itsTElement->lastClickLocatedAtRatio;

    IsItOKToConnect = CreateTE2ndConnecRatio();
    if( !   IsItOKToConnect )
    {
      return FALSE;
    }
    Erase();
    theSelectedTEObject->AddToItsContLandMCluster( this);
    this->ReSizingInProgress = FALSE;
    PrepareYourselfToBeUpdated();
    this->DrawFinal();
    this->IamConnected = TRUE;
    theSelectedTEObject->SelectYourself();
    itsTrussPane->theObject = theSelectedTEObject;
    return TRUE;
  }else
  {
    return FALSE;
  }
}


void CQuadrelateralObject::DoYourDialog( void )
{
  inherited::DoYourDialog();

}
void CQuadrelateralObject::Dispose( void )
{

  inherited::Dispose();

}

void CQuadrelateralObject::DisconnectYourself()
{
  int      YLengthToTopRight;
  int      YLengthToTopLeft;

  if( IamConnected )
  {
    UnSelectYourself();
    Erase();
    YLengthToTopRight = bottomRightCorner.v - topRightCorner.v;
    YLengthToTopLeft = bottomLeftCorner.v - topLeftCorner.v;

    bottomRightCorner.v = bottomLeftCorner.v;

    topRightCorner.v = bottomRightCorner.v - YLengthToTopRight;
    topLeftCorner.v = bottomLeftCorner.v - YLengthToTopLeft;

    FromCornersToItsCenterPoint();

    DrawFinal();
    SelectYourself();

    IamConnected = FALSE;
    loadAlongAllMember = FALSE;


    itsTElement->theTEContLoadsAndMoments->Remove( this );
    itsTElement->DrawFinal();
    itsTElement = NULL;
  }
}

void CQuadrelateralObject::DeleteYourself( void )
{
  DisconnectYourself();
  UnSelectYourself();
  Erase();
  itsTrussPane->ContLoadsAndMoments->Remove( this );
  itsTrussPane->theObject = NULL;
  Dispose();
}



void CQuadrelateralObject::PrepareYourselfToBeUpdated( void )
{
  Point    TE1stEnd, TE2ndEnd;
  Point    connectToThisPoint;
  Point    connectToThis2ndPoint;
  int      xLength, yLength;
  int      XLengthToTopRight, YLengthToTopRight;
  int      XLengthToTopLeft, YLengthToTopLeft;


  TE1stEnd.h = itsTElement->its1stEnd.h;
  TE1stEnd.v = itsTElement->its1stEnd.v;
  TE2ndEnd.h = itsTElement->its2ndEnd.h;
  TE2ndEnd.v = itsTElement->its2ndEnd.v;

  connectToThisPoint.h = ((int)((( float)(TE2ndEnd.h -TE1stEnd.h))
          *TElementConnectionRatio)) + TE1stEnd.h;
  connectToThisPoint.v = ((int)((( float)(TE2ndEnd.v -TE1stEnd.v))
          *TElementConnectionRatio)) + TE1stEnd.v;

  connectToThis2ndPoint.h = ((int)((( float)(TE2ndEnd.h -TE1stEnd.h))
          *TElement2ndConnectionRatio)) + TE1stEnd.h;
  connectToThis2ndPoint.v = ((int)((( float)(TE2ndEnd.v -TE1stEnd.v))
          *TElement2ndConnectionRatio)) + TE1stEnd.v;

  YLengthToTopRight = bottomRightCorner.v - topRightCorner.v;
  YLengthToTopLeft = bottomLeftCorner.v - topLeftCorner.v;

  bottomLeftCorner.h = connectToThisPoint.h;
  bottomLeftCorner.v = connectToThisPoint.v;

  bottomRightCorner.h = connectToThis2ndPoint.h;
  bottomRightCorner.v = connectToThis2ndPoint.v;

  topLeftCorner.h = bottomLeftCorner.h;
  topLeftCorner.v = bottomLeftCorner.v - YLengthToTopLeft;

  topRightCorner.h = bottomRightCorner.h;
  topRightCorner.v = bottomRightCorner.v -  YLengthToTopRight;

  itsCenterPoint.v = (( bottomLeftCorner.v + topLeftCorner.v ) / 2 +
            ( bottomRightCorner.v + topRightCorner.v ) / 2)/2;
  itsCenterPoint.h = (( bottomLeftCorner.h + topLeftCorner.h ) / 2 +
            ( bottomRightCorner.h + topRightCorner.h ) / 2)/2;
}

