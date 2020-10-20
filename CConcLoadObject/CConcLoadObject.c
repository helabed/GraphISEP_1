/****
 * CConcLoadObject.c
 *
 *  Load object class for a typical CTrussPane class
 *
 ****/

#include "CConcLoadObject.phs"


/*** Global Variables ***/
extern  CBartender *gBartender;
extern   short    gClicks;

/*** External functions ***/
extern int abs( int i );

void CConcLoadObject::InitializeYourself( void )

{
  offSet.h = 0;
  offSet.v = 0;

  itsCenterPoint.h = theHitPoint.h - offSet.h;
  itsCenterPoint.v = theHitPoint.v - offSet.v;

  LoadCounterMoneyValue = 500;
  LoadCounterDaysValue = 40;

  its1stEnd.h = itsCenterPoint.h;
  its1stEnd.v = itsCenterPoint.v - HALF_ARROW;
  its2ndEnd.h = itsCenterPoint.h;
  its2ndEnd.v = itsCenterPoint.v + HALF_ARROW;

  itsRegion = NewRgn();

  OpenRgn();
  UpDateItsRegion();
  CloseRgn(itsRegion);
  InsetRgn( itsRegion, RGN_EXPANSION_IN_PIXELS, RGN_EXPANSION_IN_PIXELS);
        /* make the region larger */

  IamSelected = FALSE;
  ReSizingInProgress = FALSE;
  the1stEndConnected = FALSE;
  the2ndEndConnected = FALSE;

  itsCenterPointFlag = FALSE;
  its1stEndFlag = FALSE;
  its2ndEndFlag = FALSE;
  IamConnected = FALSE;

  the1stEndNode = NULL;
  the2ndEndNode = NULL;
  itsTElement = NULL;

  Draw();
}



void CConcLoadObject::SelectYourself( void )
{

  DrawResizingHandles( itsCenterPoint );
  DrawResizingHandles( its1stEnd );
  DrawResizingHandles( its2ndEnd );

  IamSelected = TRUE;
}


void CConcLoadObject::UnSelectYourself( void )
{
  if ( IamSelected )
  {
      /* this will have effect of erasing squares */
    EraseResizingHandles( itsCenterPoint );
    EraseResizingHandles( its1stEnd );
    EraseResizingHandles( its2ndEnd );

    Draw();
    IamSelected = FALSE;
  }
}

void CConcLoadObject::Draw( void )
{
  DoDraw();
}

void CConcLoadObject::DoDraw( void )
{
  MoveTo( its1stEnd.h, its1stEnd.v);
  PenSize( 1,1);
  LineTo( its2ndEnd.h, its2ndEnd.v);
  PenSize( 1,1);

  HandleTheArrow();
}

void CConcLoadObject::HandleTheArrow( void )
{
  double    Ry, Rx, m, d, xLength, yLength, length, sqrtOnePlusM2;
  int      Sx, Sy, Tx, Ty;

    /* see page 118 of Computer Graphics Software Construction */

  Rx = LAMDA1 * ( double )its1stEnd.h + ( 1.0 - LAMDA1 ) * (double)its2ndEnd.h;
  Ry = LAMDA1 * ( double )its1stEnd.v + ( 1.0 - LAMDA1 ) * (double)its2ndEnd.v;

  m = (( (double) (its2ndEnd.v - its1stEnd.v ) ) / ( (double )
                      (its2ndEnd.h - its1stEnd.h ) ));

  xLength =  (( its2ndEnd.h - its1stEnd.h )*
              ( its2ndEnd.h - its1stEnd.h )) ;
  yLength =  (( its2ndEnd.v - its1stEnd.v )*
              ( its2ndEnd.v - its1stEnd.v )) ;
  length = sqrt((double)( xLength + yLength ) );
  d = ( LAMDA1 * length / 3.0 ) + 5.0;
/*  d = 5.0 ; */

  if ( ((its2ndEnd.h - its1stEnd.h) == 0 ) || ( fabs( m ) >= 0.9 ))
  {
    Sx = ( int )(Rx -  d);
    Tx = ( int )(Rx +  d);

    Sy = ( int ) Ry;
    Ty = ( int ) Ry;
  }
  else if ( fabs( m ) <= 0.2 )
  {
    Sy = ( int )(Ry -  d);
    Ty = ( int )(Ry +  d);

    Sx = ( int ) Rx;
    Tx = ( int ) Rx;
  }
  else
  {
    sqrtOnePlusM2 = sqrt( 1.0 + m*m );

    Sx = ( int )( Rx - ( d / sqrtOnePlusM2 ));
    Tx = ( int )( Rx + ( d / sqrtOnePlusM2 ));

    Sy = ( int ) (Ry + (  m * d / sqrtOnePlusM2 ));
    Ty = ( int ) (Ry - (  m * d / sqrtOnePlusM2 ));

  }
  LineTo( Sx, Sy );
  MoveTo( its2ndEnd.h, its2ndEnd.v);
  LineTo( Tx, Ty );
  MoveTo( its2ndEnd.h, its2ndEnd.v);
}

void CConcLoadObject::UpDateItsRegion( void )
{
  Rect  myRect;
  Point  pt1, pt2, pt3, pt4;

  if ( (its1stEnd.v >= its2ndEnd.v) && ( its2ndEnd.h >= its1stEnd.h ) )
  {    /* 1st Quadrant */
    pt1.h = its1stEnd.h + RGN_NEIGHBORHOOD;
    pt1.v = its1stEnd.v + RGN_NEIGHBORHOOD;
    pt2.h = its2ndEnd.h + RGN_NEIGHBORHOOD;
    pt2.v = its2ndEnd.v + RGN_NEIGHBORHOOD;
    pt3.h = its2ndEnd.h - RGN_NEIGHBORHOOD;
    pt3.v = its2ndEnd.v - RGN_NEIGHBORHOOD;
    pt4.h = its1stEnd.h - RGN_NEIGHBORHOOD;
    pt4.v = its1stEnd.v - RGN_NEIGHBORHOOD;
  }
  else
  if ( (its1stEnd.v >= its2ndEnd.v) && ( its1stEnd.h >= its2ndEnd.h ) )
  {    /* 2nd Quadrant */
    pt1.h = its1stEnd.h + RGN_NEIGHBORHOOD;
    pt1.v = its1stEnd.v - RGN_NEIGHBORHOOD;
    pt2.h = its2ndEnd.h + RGN_NEIGHBORHOOD;
    pt2.v = its2ndEnd.v - RGN_NEIGHBORHOOD;
    pt3.h = its2ndEnd.h - RGN_NEIGHBORHOOD;
    pt3.v = its2ndEnd.v + RGN_NEIGHBORHOOD;
    pt4.h = its1stEnd.h - RGN_NEIGHBORHOOD;
    pt4.v = its1stEnd.v + RGN_NEIGHBORHOOD;
  }
  else
  if ( (its2ndEnd.v >= its1stEnd.v) && ( its1stEnd.h >= its2ndEnd.h ) )
  {    /* 3rd Quadrant */
    pt1.h = its1stEnd.h - RGN_NEIGHBORHOOD;
    pt1.v = its1stEnd.v - RGN_NEIGHBORHOOD;
    pt2.h = its2ndEnd.h - RGN_NEIGHBORHOOD;
    pt2.v = its2ndEnd.v - RGN_NEIGHBORHOOD;
    pt3.h = its2ndEnd.h + RGN_NEIGHBORHOOD;
    pt3.v = its2ndEnd.v + RGN_NEIGHBORHOOD;
    pt4.h = its1stEnd.h + RGN_NEIGHBORHOOD;
    pt4.v = its1stEnd.v + RGN_NEIGHBORHOOD;
  }
  else
  if ( (its2ndEnd.v >= its1stEnd.v) && ( its2ndEnd.h >= its1stEnd.h ) )
  {    /* 4th Quadrant */
    pt1.h = its1stEnd.h - RGN_NEIGHBORHOOD;
    pt1.v = its1stEnd.v + RGN_NEIGHBORHOOD;
    pt2.h = its2ndEnd.h - RGN_NEIGHBORHOOD;
    pt2.v = its2ndEnd.v + RGN_NEIGHBORHOOD;
    pt3.h = its2ndEnd.h + RGN_NEIGHBORHOOD;
    pt3.v = its2ndEnd.v - RGN_NEIGHBORHOOD;
    pt4.h = its1stEnd.h + RGN_NEIGHBORHOOD;
    pt4.v = its1stEnd.v - RGN_NEIGHBORHOOD;
  }
  MoveTo( its1stEnd.h, its1stEnd.v );
  LineTo( pt1.h, pt1.v );
  LineTo( pt2.h, pt2.v );
  LineTo( its2ndEnd.h, its2ndEnd.v );
  LineTo( pt3.h, pt3.v );
  LineTo( pt4.h, pt4.v );
  LineTo( its1stEnd.h, its1stEnd.v );
}


void CConcLoadObject::MoveYourself( void )
{
  int      xLength, yLength;

  xLength = its2ndEnd.h - its1stEnd.h;
  yLength = its2ndEnd.v - its1stEnd.v;

  its1stEnd.h = theHitPoint.h - offSet.h;
  its1stEnd.v = theHitPoint.v - offSet.v;

  its2ndEnd.h = its1stEnd.h + xLength;
  its2ndEnd.v = its1stEnd.v + yLength;

  itsCenterPoint.v = ( its2ndEnd.v + its1stEnd.v ) / 2;
  itsCenterPoint.h = ( its2ndEnd.h + its1stEnd.h ) / 2;

  DragYourself();
}

void CConcLoadObject::UpDateObject( void )
{
  if ( ReSizingInProgress )
  {
    ResizeYourself();
  }
  else if( ( ! the1stEndConnected) && ( ! the2ndEndConnected ) )
  {
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

Boolean CConcLoadObject::WhichOneOfUsGotSelected( Point aPoint )
{
/*  if( PtInRgn( aPoint, itsRegion ))
  {
    if ( gClicks == DOUBLE_CLICKS )
    {
      this->DoYourDialog();
      return( FALSE );
    }
  }
*/
  if ( ( HitSamePart( its2ndEnd, aPoint, &offSet  ) ) )
  {
    ReSizingInProgress = TRUE;

    itsCenterPointFlag = FALSE;
    its1stEndFlag = FALSE;
    its2ndEndFlag = FALSE;

    its2ndEndFlag = TRUE;
    return ( TRUE );
  }

  else if ( ( HitSamePart( its1stEnd, aPoint, &offSet  ) ) )
  {
    ReSizingInProgress = TRUE;

    itsCenterPointFlag = FALSE;
    its1stEndFlag = TRUE;
    its2ndEndFlag = FALSE;

    return ( TRUE );
  }

  else if (/*( HitSamePart( itsCenterPoint, aPoint, &offSet ) )*/ FALSE)
  {
    ReSizingInProgress = FALSE;

    itsCenterPointFlag = TRUE;
    its1stEndFlag = FALSE;
    its2ndEndFlag = FALSE;

    return ( TRUE );
  }
  else if( PtInRgn( aPoint, itsRegion )) /* in truss element in region */
  {
/*    if ( gClicks == DOUBLE_CLICKS )
    {
      this->DoYourDialog();
      return( FALSE );
    }
*/    ReSizingInProgress = FALSE;

    itsCenterPointFlag = FALSE;
    its1stEndFlag = FALSE;
    its2ndEndFlag = FALSE;

    offSet.v = aPoint.v - its1stEnd.v;
    offSet.h = aPoint.h - its1stEnd.h;

    return ( TRUE );
  }
  else
  {
    ReSizingInProgress = FALSE;

    itsCenterPointFlag = FALSE;
    its1stEndFlag = FALSE;
    its2ndEndFlag = FALSE;
    return ( FALSE );
  }
}

void CConcLoadObject::DrawResizingHandles( Point giveMeAPoint )
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

void CConcLoadObject::ResizeYourself( void )
{

  FromtheHitPointToCorners();
  DragYourself();
  FromCornersToItsCenterPoint();
}

void  CConcLoadObject::FromtheHitPointToCorners( void )
{
    if ( its2ndEndFlag )
    {
      its2ndEnd.h = theHitPoint.h - offSet.h;
      its2ndEnd.v = theHitPoint.v - offSet.v;
    }
    if ( its1stEndFlag )
    {
      its1stEnd.h = theHitPoint.h - offSet.h;
      its1stEnd.v = theHitPoint.v - offSet.v;
    }
}


void  CConcLoadObject::FromCornersToItsCenterPoint( void )
{
  itsCenterPoint.v = ( its2ndEnd.v + its1stEnd.v ) / 2;
  itsCenterPoint.h = ( its2ndEnd.h + its1stEnd.h ) / 2;
}

void CConcLoadObject::DrawFinal( void )
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

/* ----------------------------------------------------------------------------  */
/* Copyright ©1987-1989 by Gary Gregory and Neil Ticktin.  All rights reserved.  */
/* Version 1.0.  Any portion of this demo can be used in your application as  */
/* long as you follow the terms in the Invention Software Licensing Agreement.  */
/* ----------------------------------------------------------------------------  */

/* This is demo I used to learn about dialog handler ignore it, hani says */

void CConcLoadObject::DoDialogItemsCounter(void)
{
  DialogHandlerRecordPtr dhp;
  DecForm  dForm;

  DHStandardNewRecord (&dhp, LoadCounterDLOG_ID, LoadCounterUpdateUserItemId, NoSelectedItem);

  dForm.digits = 4;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddCounter(dhp, LoadCounterMoneyId, LoadCounterMoneyArrowId, LoadCounterMoneyValue, 0.01, 0.0, MAXREAL, DHMakeKeyEquiv(NORMAL, '+'), DHMakeKeyEquiv(NORMAL, '-'), dForm, VeryShortDelay, NULL);

  dForm.digits = 0;
  DHAdvAddCounter(dhp, LoadCounterDaysId, LoadCounterDaysArrowId, LoadCounterDaysValue, 1.0, 0.0, 99.0, DHNoKeyEquiv(), DHNoKeyEquiv(), dForm, ShortDelay, NULL);

  DHSetDialogFont(dhp, monaco, 9, (Style)NULL);
/*  DHADDDISPLAYTEXT(dhp, LoadCounterDispTextId, LoadCounterDLOG_ID); /* LoadCounterDLOG_ID is the same number as the TEXTid */

/*  DHSetCentering(dhp, PrefCenterHorizValue, PrefCenterVertValue, SaveCenteringOff);
  DHSetNearMousePointer(dhp, PrefNearHorizValue, PrefNearVertValue);
*/
  if (DHDialogHandler(dhp))
  {
    LoadCounterMoneyValue = DHGetCounterValue(dhp, LoadCounterMoneyId);
    LoadCounterDaysValue = DHGetCounterValue(dhp, LoadCounterDaysId);
  }

  DHDeallocateRecord(dhp);
}



void CConcLoadObject::DoYourDialog( void )
{
  DialogHandlerRecordPtr   dhp;
  DecForm          dForm;
  float          xLength;
  float          yLength;
  float          newConcLoad;
  float          ConcLoadLength;
  Boolean          theBoxIsChecked;
  CConcLoadObject      *thisObject;
  float          newConcLoadRatio;
  float          newTElementConnectionRatio;

  thisObject = this;

  DHStandardNewRecord (&dhp, ConcLoadDLOG_ID,
              ConcLoadUpdateUserItemId,
              ConcLoadMagnitude);


  ConcLoadLength = (float) sqrt((double)(( (((float)(its2ndEnd.v -its1stEnd.v))*
            ((float)(its2ndEnd.v -its1stEnd.v) )) +
            ( ((float)(its2ndEnd.h -its1stEnd.h))*
            ((float)(its2ndEnd.h -its1stEnd.h)) ) ) ) );

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, ConcLoadMagnitude,
    (ConcLoadLength * itsTrussPane->theLoadScale / SCREEN_DPI ),
      dForm, 0.0, MAXREAL);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, ConcLoadHorzComp,
    ((its2ndEnd.h - its1stEnd.h) * itsTrussPane->theLoadScale / SCREEN_DPI ),
      dForm, -MAXREAL, MAXREAL);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, ConcLoadVertComp,
    ((its2ndEnd.v - its1stEnd.v) * itsTrussPane->theLoadScale / SCREEN_DPI ),
      dForm, -MAXREAL, MAXREAL);  /* should be limit of drawing area*/

  if ( IamConnected && itsTElement)
  {
    dForm.digits = 2;
    dForm.style = FIXEDDECIMAL;
    DHAdvAddEditReal(dhp, ConcLoadTEConnectionRatio,
      (TElementConnectionRatio ),
        dForm, 0.0, 1.0);
  }

  if (DHDialogHandler(dhp))
  {

    newConcLoad = DHGetEditReal(dhp, ConcLoadMagnitude);
    xLength = DHGetEditReal(dhp, ConcLoadHorzComp);
    yLength = DHGetEditReal(dhp, ConcLoadVertComp);
    if( IamConnected )
      newTElementConnectionRatio =
          DHGetEditReal(dhp, ConcLoadTEConnectionRatio);

        /* Length field has changed, i.e new != old */
    if( ! (Abs(newConcLoad -
       (ConcLoadLength * itsTrussPane->theLoadScale / SCREEN_DPI ))
       <=  SMALL_FLOAT_VALUE) )
    {
      newConcLoadRatio = newConcLoad /
      (ConcLoadLength * itsTrussPane->theLoadScale / SCREEN_DPI );

      if( (the2ndEndConnected )  && ( ! the1stEndConnected ))
          /* subtract length from first end*/
      {
        xLength = (float)(its2ndEnd.h - its1stEnd.h);
        yLength = (float)(its2ndEnd.v - its1stEnd.v);
        UnSelectYourself();
        Erase();


        its1stEnd.h = its1stEnd.h - (int)(( newConcLoadRatio - 1.0 )
                    *(xLength));
        its1stEnd.v = its1stEnd.v - (int)(( newConcLoadRatio - 1.0 )
                    *(yLength));

        DrawFinal();
/*        theTEConcLoadsAndMoments->DoForEach(  Perform_Draw );
        theTEContLoadsAndMoments->DoForEach( Perform_Draw );
        theTENodes->DoForEach( Perform_Draw );
*/      }
      else if( ! the2ndEndConnected )  /* add length to second end*/
      {
        xLength = (float)(its2ndEnd.h - its1stEnd.h);
        yLength = (float)(its2ndEnd.v - its1stEnd.v);
        UnSelectYourself();
        Erase();


        its2ndEnd.h = its2ndEnd.h + (int)(( newConcLoadRatio - 1.0 )
                    *(xLength));
        its2ndEnd.v = its2ndEnd.v + (int)(( newConcLoadRatio - 1.0 )
                    *(yLength));

        DrawFinal();
/*        theTEConcLoadsAndMoments->DoForEach(  Perform_Draw );
        theTEContLoadsAndMoments->DoForEach( Perform_Draw );
        theTENodes->DoForEach( Perform_Draw );
*/
      }


        /* components of Length field have changed */
/*    }else if( ( xLength !=
       ((its2ndEnd.h - its1stEnd.h) * itsTrussPane->theLoadScale
       / SCREEN_DPI ) ) || (yLength !=
       ((its2ndEnd.v - its1stEnd.v) * itsTrussPane->theLoadScale
       / SCREEN_DPI ) ) )
*/    }else if( (! (Abs(xLength -
       ((its2ndEnd.h - its1stEnd.h) * itsTrussPane->theLoadScale
       / SCREEN_DPI )) <=  SMALL_FLOAT_VALUE) )  ||
       ( ! (Abs(yLength -
       ((its2ndEnd.v - its1stEnd.v) * itsTrussPane->theLoadScale
       / SCREEN_DPI )) <=  SMALL_FLOAT_VALUE) ) )
     {
      if( (the2ndEndConnected )  && ( ! the1stEndConnected ))
          /* subtract length from first end*/
      {
        UnSelectYourself();
        Erase();


        its1stEnd.h = its2ndEnd.h - (int)(((xLength)/
            itsTrussPane->theLoadScale * SCREEN_DPI));
        its1stEnd.v = its2ndEnd.v - (int)(((yLength)/
            itsTrussPane->theLoadScale * SCREEN_DPI));

        DrawFinal();
/*        theTEConcLoadsAndMoments->DoForEach(  Perform_Draw );
        theTEContLoadsAndMoments->DoForEach( Perform_Draw );
        theTENodes->DoForEach( Perform_Draw );
*/      }
      else if( ! the2ndEndConnected )  /* add length to second end*/
      {
        UnSelectYourself();
        Erase();


        its2ndEnd.h = its1stEnd.h + (int)((xLength)/
            itsTrussPane->theLoadScale * SCREEN_DPI);
        its2ndEnd.v = its1stEnd.v + (int)((yLength)/
            itsTrussPane->theLoadScale * SCREEN_DPI);

        DrawFinal();
/*        theTEConcLoadsAndMoments->DoForEach(  Perform_Draw );
        theTEContLoadsAndMoments->DoForEach( Perform_Draw );
        theTENodes->DoForEach( Perform_Draw );
*/
      }
    }

    if ( IamConnected && itsTElement)
    {
      if ( newTElementConnectionRatio != TElementConnectionRatio  )
      {
        UnSelectYourself();
        Erase();

        TElementConnectionRatio = newTElementConnectionRatio;
        itsTElement->DrawFinal();
        DrawFinal();
/*        theNodeTElements->DoForEach(  Perform_Draw );
        theNodeLoads->DoForEach( Perform_Draw );
*/      }
    }

  }

  DHDeallocateRecord(dhp);
}


void CConcLoadObject::Dispose()
{
  DisposHandle( itsRegion );

  inherited::Dispose();
}

void CConcLoadObject::PrepareYourselfToBeUpdated( void )
{
  Point    TE1stEnd, TE2ndEnd;
  Point    connectToThisPoint;
  int      xLength, yLength;

  TE1stEnd.h = itsTElement->its1stEnd.h;
  TE1stEnd.v = itsTElement->its1stEnd.v;
  TE2ndEnd.h = itsTElement->its2ndEnd.h;
  TE2ndEnd.v = itsTElement->its2ndEnd.v;


  connectToThisPoint.h = ((int)((( float)(TE2ndEnd.h -TE1stEnd.h))
          *TElementConnectionRatio)) + TE1stEnd.h;
  connectToThisPoint.v = ((int)((( float)(TE2ndEnd.v -TE1stEnd.v))
          *TElementConnectionRatio)) + TE1stEnd.v;


  xLength = its2ndEnd.h - its1stEnd.h;
  yLength = its2ndEnd.v - its1stEnd.v;

  its2ndEnd.h = connectToThisPoint.h;
  its2ndEnd.v = connectToThisPoint.v;

  its1stEnd.h = its2ndEnd.h - xLength;
  its1stEnd.v = its2ndEnd.v - yLength;

  FromCornersToItsCenterPoint();

}
Boolean CConcLoadObject::ConnectYourselfToNode(  CNodeObject
                      *theSelectedNodeObject )
{
  if( (!(this->the1stEndConnected ) &&
    !(this->the2ndEndConnected )) )
      /* to make sure that it is not already connected*/
  {
    this->SelectYourself();
    if( this->its1stEndFlag )
    {
      this->the1stEndNode = theSelectedNodeObject;
      this->the1stEndConnected = TRUE;
    }
    if( this->its2ndEndFlag )
    {
      this->the2ndEndNode = theSelectedNodeObject;
      this->the2ndEndConnected = TRUE;
    }
    theSelectedNodeObject->AddToItsConcLandMCluster(
                    this);
    IamConnected = TRUE;
    this->UnSelectYourself();
    theSelectedNodeObject->SelectYourself();
    itsTrussPane->theObject = theSelectedNodeObject;
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}
Boolean CConcLoadObject::ConnectYourselfToTE(  CTrussElementObject
                        *theSelectedTEObject )
{
  if( (!(this->the1stEndConnected ) &&
    !(this->the2ndEndConnected )) &&
    this->its2ndEndFlag )
      /* to make sure that it is not already connected*/
  {
    this->SelectYourself();
    theSelectedTEObject->AddToItsConcLandMCluster(
                    this);
    if( this->its1stEndFlag )
    {
      this->itsTElement = theSelectedTEObject;
      this->the1stEndConnected = TRUE;
    }
    if( this->its2ndEndFlag )
    {
      this->itsTElement = theSelectedTEObject;
      this->the2ndEndConnected = TRUE;
    }
    IamConnected = TRUE;
    this->UnSelectYourself();
    theSelectedTEObject->SelectYourself();
    itsTrussPane->theObject = theSelectedTEObject;
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}
void CConcLoadObject::DisconnectYourself()
{
  if( IamConnected )
  {
    UnSelectYourself();
    Erase();


    if ( the1stEndConnected )
    {
      if( the1stEndNode )  /* 1st end connected to a node */
      {
        the1stEndNode->theNodeLoads
            ->Remove( this );
        the1stEndNode->DrawNodeOnly();
        the1stEndNode = NULL;
      }else
      if( itsTElement)  /* 1st end connected to truss element*/
      {
        itsTElement->theTEConcLoadsAndMoments->Remove( this );
        itsTElement->DrawFinal();
        itsTElement = NULL;
      }
      the1stEndConnected = FALSE;
    }
    else if ( the2ndEndConnected )
    {
      if( the2ndEndNode )  /* 2nd end connected to a node */
      {
        the2ndEndNode->theNodeLoads
            ->Remove( this );
        the2ndEndNode->DrawNodeOnly();
        the2ndEndNode = NULL;
      }else
      if( itsTElement)  /* 2nd end connected to truss element*/
      {
        itsTElement->theTEConcLoadsAndMoments->Remove( this );
        itsTElement->DrawFinal();
        itsTElement = NULL;
      }
      the2ndEndConnected = FALSE;
    }

    offSet.h = its2ndEnd.h - its1stEnd.h;
    offSet.v = its2ndEnd.v - its1stEnd.v;
    theHitPoint.h = its2ndEnd.h + SMALL_LENGTH;
    theHitPoint.v = its2ndEnd.v - SMALL_LENGTH;

    its1stEndFlag = FALSE;
    its2ndEndFlag = FALSE;
    IamConnected = FALSE;

    its2ndEndFlag = TRUE;
    ReSizingInProgress = FALSE;
    UpDateObject();

    DrawFinal();
    SelectYourself();
  }
}

void CConcLoadObject::DeleteYourself( void )
{
  DisconnectYourself();
  UnSelectYourself();
  Erase();
  itsTrussPane->ConcLoadsAndMoments->Remove( this );
  itsTrussPane->theObject = NULL;
  Dispose();
}

void CConcLoadObject::PrepareYourselfToBeUpdatedByNode( void )
{
  int      xLength, yLength;

  xLength = its2ndEnd.h - its1stEnd.h;
  yLength = its2ndEnd.v - its1stEnd.v;

  if ( the2ndEndConnected )
  {
    its2ndEnd.h = the2ndEndNode->itsCenterPoint.h;
    its2ndEnd.v = the2ndEndNode->itsCenterPoint.v;

    its1stEnd.h = its2ndEnd.h - xLength;
    its1stEnd.v = its2ndEnd.v - yLength;

  }
  else if( the1stEndConnected )
  {
    its1stEnd.h = the1stEndNode->itsCenterPoint.h;
    its1stEnd.v = the1stEndNode->itsCenterPoint.v;

    its2ndEnd.h = its1stEnd.h + xLength;
    its2ndEnd.v = its1stEnd.v + yLength;
  }
  FromCornersToItsCenterPoint();
}


