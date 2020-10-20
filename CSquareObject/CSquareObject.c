/****
 * CSquareObject.c
 *
 *  Square object class for a typical CTrussPane class
 *
 ****/

#include "CSquareObject.phs"


/*** Global Variables ***/

extern  CBartender *gBartender;
extern   short    gClicks;


void CSquareObject::InitializeYourself( void )

{
  Rect  myRect;
  Point  hitPt;

  offSet.h = 0;
  offSet.v = 0;

  hitPt.h = theHitPoint.h - offSet.h;
  hitPt.v = theHitPoint.v - offSet.v;

  itsCenterPoint.h = theHitPoint.h - offSet.h;
  itsCenterPoint.v = theHitPoint.v - offSet.v;

  topLeftCorner.v  = myRect.top = hitPt.v - 20;
  topLeftCorner.h  = myRect.left = hitPt.h - 20;
  bottomRightCorner.v  = myRect.bottom = hitPt.v + 20;
  bottomRightCorner.h  = myRect.right = hitPt.h + 20;
  topRightCorner.h = bottomRightCorner.h;
  topRightCorner.v = topLeftCorner.v;
  bottomLeftCorner.h = topLeftCorner.h;
  bottomLeftCorner.v = bottomRightCorner.v;

  itsRegion = NewRgn();

  OpenRgn();
  UpDateItsRegion();
  CloseRgn(itsRegion);
  InsetRgn( itsRegion, RGN_EXPANSION_IN_PIXELS, RGN_EXPANSION_IN_PIXELS);
        /* make the region larger */


  Draw();
  IamSelected = FALSE;
  ReSizingInProgress = FALSE;

  topLeftCornerFlag = FALSE;
  bottomRightCornerFlag = FALSE;
  bottomLeftCornerFlag = FALSE;
  topRightCornerFlag = FALSE;
  IamConnected = FALSE;

}



void CSquareObject::SelectYourself( void )
{

  DrawResizingHandles( topRightCorner );
  DrawResizingHandles( topLeftCorner );
  DrawResizingHandles( bottomRightCorner );
  DrawResizingHandles( bottomLeftCorner );
  DrawResizingHandles( itsCenterPoint );

  IamSelected = TRUE;
}


void CSquareObject::UnSelectYourself( void )
{
  PenState  pnState;

  if ( IamSelected )
  {
      /* this will have effect of erasing squares */
    EraseResizingHandles( topRightCorner );
    EraseResizingHandles( topLeftCorner );
    EraseResizingHandles( bottomRightCorner );
    EraseResizingHandles( bottomLeftCorner );
    EraseResizingHandles( itsCenterPoint );

    Draw();


    IamSelected = FALSE;
  }
}


void CSquareObject::Draw( void )
{
  Rect  myRect;

  myRect.top = topLeftCorner.v  ;
  myRect.left = topLeftCorner.h ;
  myRect.bottom = bottomRightCorner.v;
  myRect.right = bottomRightCorner.h;

  FrameRect( &myRect );

  UpDateItsRegion();
}

void CSquareObject::UpDateItsRegion( void )
{
  MoveTo( bottomLeftCorner.h, bottomLeftCorner.v);
  LineTo( bottomRightCorner.h, bottomRightCorner.v);
  LineTo( topRightCorner.h , topRightCorner.v );
  LineTo( topLeftCorner.h, topLeftCorner.v );
  LineTo( bottomLeftCorner.h, bottomLeftCorner.v);
}

void CSquareObject::MoveYourself( void )
{
  Point    temp1, temp2;
  int      xLength, yLength;


  xLength = bottomRightCorner.h - bottomLeftCorner.h;
  yLength = bottomRightCorner.v - topRightCorner.v;

  bottomLeftCorner.h = theHitPoint.h - offSet.h;
  bottomLeftCorner.v = theHitPoint.v - offSet.v;

  bottomRightCorner.h = bottomLeftCorner.h + xLength;
  bottomRightCorner.v = bottomLeftCorner.v;

  topLeftCorner.h = bottomLeftCorner.h;
  topLeftCorner.v = bottomLeftCorner.v - yLength;

  topRightCorner.h = bottomLeftCorner.h + xLength;
  topRightCorner.v = bottomLeftCorner.v - yLength;

  itsCenterPoint.v = ( bottomLeftCorner.v + topRightCorner.v ) / 2;
  itsCenterPoint.h = ( bottomLeftCorner.h + topRightCorner.h ) / 2;

  DragYourself();
}


void CSquareObject::UpDateObject( void )
{
  if ( ReSizingInProgress )
  {
    ResizeYourself();
  }
  else
  {
    if( ! IamConnected )
      MoveYourself();
  }
}

      /*****
      /* this is to see if two point are close to each other
      /*
      /************/

      static  Boolean  HitSamePart(Point pointA, Point pointB,
                        Point *offSetPtr )
      {
        Rect  luckyRect;
        Point  offSet;

        luckyRect.top = pointA.v - WITHIN_N_PIXELS;
        luckyRect.left = pointA.h - WITHIN_N_PIXELS;
        luckyRect.right = pointA.h + WITHIN_N_PIXELS;
        luckyRect.bottom = pointA.v + WITHIN_N_PIXELS;

        if ( (( pointB.v > luckyRect.top ) &&
                ( pointB.v < luckyRect.bottom ))
          && (( pointB.h > luckyRect.left ) &&
                ( pointB.h < luckyRect.right)) )
        {
          offSet.v = pointB.v - pointA.v;
          offSet.h = pointB.h - pointA.h;
          (*offSetPtr) = offSet;
          return ( TRUE );
        }
        else
        {
          offSet.v = 0;
          offSet.h = 0;
          (*offSetPtr) = offSet;
          return ( FALSE );
        }
      }

Boolean CSquareObject::WhichOneOfUsGotSelected( Point aPoint )
{
  if ( ( HitSamePart( topLeftCorner, aPoint, &offSet  ) ) )
  {
    ReSizingInProgress = TRUE;

    topLeftCornerFlag = FALSE;
    bottomRightCornerFlag = FALSE;
    bottomLeftCornerFlag = FALSE;
    topRightCornerFlag = FALSE;

    topLeftCornerFlag = TRUE;
    return ( TRUE );
  }

  else if ( ( HitSamePart( topRightCorner, aPoint, &offSet  ) ) )
  {
    ReSizingInProgress = TRUE;

    topLeftCornerFlag = FALSE;
    bottomRightCornerFlag = FALSE;
    bottomLeftCornerFlag = FALSE;
    topRightCornerFlag = FALSE;

    topRightCornerFlag = TRUE;
    return ( TRUE );
  }

  else if ( ( HitSamePart( bottomRightCorner, aPoint, &offSet  ) ) )
  {
    ReSizingInProgress = TRUE;

    topLeftCornerFlag = FALSE;
    bottomRightCornerFlag = FALSE;
    bottomLeftCornerFlag = FALSE;
    topRightCornerFlag = FALSE;

    bottomRightCornerFlag = TRUE;
    return ( TRUE );
  }

  else if ( ( HitSamePart( bottomLeftCorner, aPoint, &offSet  ) ) )
  {
    ReSizingInProgress = TRUE;

    topLeftCornerFlag = FALSE;
    bottomRightCornerFlag = FALSE;
    bottomLeftCornerFlag = FALSE;
    topRightCornerFlag = FALSE;

    bottomLeftCornerFlag = TRUE;
    return ( TRUE );
  }

  else if ( /*( HitSamePart( itsCenterPoint, aPoint, &offSet ) )*/ FALSE)
  {
    ReSizingInProgress = FALSE;

    topLeftCornerFlag = FALSE;
    bottomRightCornerFlag = FALSE;
    bottomLeftCornerFlag = FALSE;
    topRightCornerFlag = FALSE;

    return ( TRUE );
  }
  else if( PtInRgn( aPoint, itsRegion )) /* in truss element in region */
  {

/*    if ( gClicks == DOUBLE_CLICKS )
    {
      this->DoYourDialog();
      return( FALSE );
    }
*/
    offSet.v = aPoint.v - bottomLeftCorner.v;
    offSet.h = aPoint.h - bottomLeftCorner.h;

    ReSizingInProgress = FALSE;

    topLeftCornerFlag = FALSE;
    bottomRightCornerFlag = FALSE;
    bottomLeftCornerFlag = FALSE;
    topRightCornerFlag = FALSE;

    return( TRUE );
  }
  else
  {
    ReSizingInProgress = FALSE;

    topLeftCornerFlag = FALSE;
    bottomRightCornerFlag = FALSE;
    bottomLeftCornerFlag = FALSE;
    topRightCornerFlag = FALSE;
    return ( FALSE );
  }

}

void CSquareObject::DrawResizingHandles( Point giveMeAPoint )
{
  Rect  myRect;
  Point  hitPt;

  hitPt = giveMeAPoint;
  myRect.top = hitPt.v - 2;
  myRect.left = hitPt.h - 2;
  myRect.bottom = hitPt.v + 2;
  myRect.right = hitPt.h + 2;

  PaintRect( &myRect );
}

void CSquareObject::ResizeYourself( void )
{

  FromtheHitPointToCorners();
  DragYourself();
  FromCornersToItsCenterPoint();
}

void  CSquareObject::FromtheHitPointToCorners( void )
{
    if ( topLeftCornerFlag )
    {
      topLeftCorner.h = theHitPoint.h - offSet.h;
      topLeftCorner.v = theHitPoint.v - offSet.v;
      bottomLeftCorner.h = topLeftCorner.h;
      topRightCorner.v = topLeftCorner.v;
    }

    if ( topRightCornerFlag )
    {
      topRightCorner.h = theHitPoint.h - offSet.h;
      topRightCorner.v = theHitPoint.v - offSet.v;
      topLeftCorner.v = topRightCorner.v;
      bottomRightCorner.h = topRightCorner.h;
    }

    if ( bottomLeftCornerFlag )
    {
      bottomLeftCorner.h = theHitPoint.h - offSet.h;
      bottomLeftCorner.v = theHitPoint.v - offSet.v;
      bottomRightCorner.v = bottomLeftCorner.v;
      topLeftCorner.h = bottomLeftCorner.h;
    }

    if ( bottomRightCornerFlag )
    {
      bottomRightCorner.h = theHitPoint.h - offSet.h;
      bottomRightCorner.v = theHitPoint.v - offSet.v;
      bottomLeftCorner.v = bottomRightCorner.v;
      topRightCorner.h = bottomRightCorner.h;
    }

}


void  CSquareObject::FromCornersToItsCenterPoint( void )
{
  itsCenterPoint.v = ( topLeftCorner.v + bottomRightCorner.v ) / 2;
  itsCenterPoint.h = ( topLeftCorner.h + bottomRightCorner.h ) / 2;

}
void CSquareObject::DrawFinal( void )
{
  PenState     pnState;

  OpenRgn();
  UpDateItsRegion();
  CloseRgn(itsRegion);
  InsetRgn( itsRegion, RGN_EXPANSION_IN_PIXELS, RGN_EXPANSION_IN_PIXELS);
        /* make the region larger */


  GetPenState ( &pnState);/* to save the pen setting */
  PenMode ( patCopy );
  Draw();          /* this is needed to fill gaps */
  SetPenState ( &pnState);/* to resotre pen settting */


}

void CSquareObject::Dispose()
{
  DisposHandle( itsRegion );

  inherited::Dispose();
}

