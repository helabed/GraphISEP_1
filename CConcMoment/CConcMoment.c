/****
 * CConcMoment.c
 *
 *  CConcMoment object class for a typical CTrussPane class
 *
 ****/

#include "CConcMoment.phs"



/*** Global Variables ***/

extern  CBartender *gBartender;
extern   short    gClicks;


void CConcMoment::InitializeYourself( void )
{
  offSet.h = 0;
  offSet.v = 0;

  itsCenterPoint.h = theHitPoint.h - offSet.h;
  itsCenterPoint.v = theHitPoint.v - offSet.v;

/*  pHandle = GetPicture( 4000 );
  pictureRectangle.top =  itsCenterPoint.v-16;
  pictureRectangle.bottom = itsCenterPoint.v +16;
  pictureRectangle.left =  itsCenterPoint.h-16;
  pictureRectangle.right =  itsCenterPoint.h+16;
  MoveTo( itsCenterPoint.h, itsCenterPoint.v );
  DrawPicture( pHandle, &pictureRectangle);
  IamBeingUpdated = FALSE;
*/
  LoadCounterMoneyValue = 500;
  LoadCounterDaysValue = 40;
  itsMagnitude = 1000.0;    /* 1000 lbs.-in. */


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

  DrawFinal();
}


void CConcMoment::SelectYourself( void )
{
  Point    pt1, pt2, pt3, pt4;

  pt1.h = itsCenterPoint.h;
  pt1.v = itsCenterPoint.v - 9;

  pt2.h = itsCenterPoint.h + 19;
  pt2.v = itsCenterPoint.v - 9;

  pt3.h = itsCenterPoint.h + 19;
  pt3.v = itsCenterPoint.v + 17;

  pt4.h = itsCenterPoint.h - 11;
  pt4.v = itsCenterPoint.v + 17;

  DrawResizingHandles( itsCenterPoint );
  DrawResizingHandles( pt1 );
  DrawResizingHandles( pt2 );
  DrawResizingHandles( pt3 );
  DrawResizingHandles( pt4 );

  IamSelected = TRUE;
}


void CConcMoment::UnSelectYourself( void )
{
  Point    pt1, pt2, pt3, pt4;

  if ( IamSelected )
  {
    pt1.h = itsCenterPoint.h;
    pt1.v = itsCenterPoint.v - 9;

    pt2.h = itsCenterPoint.h + 19;
    pt2.v = itsCenterPoint.v - 9;

    pt3.h = itsCenterPoint.h + 19;
    pt3.v = itsCenterPoint.v + 17;

    pt4.h = itsCenterPoint.h - 11;
    pt4.v = itsCenterPoint.v + 17;
      /* this will have effect of erasing squares */
    EraseResizingHandles( itsCenterPoint );
    EraseResizingHandles( pt1 );
    EraseResizingHandles( pt2 );
    EraseResizingHandles( pt3 );
    EraseResizingHandles( pt4 );

    DrawFinal();

    IamSelected = FALSE;
  }
}
void CConcMoment::DrawFinal( void )
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


/*  pictureRectangle.top =  itsCenterPoint.v-16;
  pictureRectangle.bottom = itsCenterPoint.v +16;
  pictureRectangle.left =  itsCenterPoint.h-16;
  pictureRectangle.right =  itsCenterPoint.h+16;
  MoveTo( itsCenterPoint.h, itsCenterPoint.v );
  DrawPicture( pHandle, &pictureRectangle);
  IamBeingUpdated = FALSE;
*/


}


void CConcMoment::Draw( void )
{
/*  if( ! IamBeingUpdated )
    EraseRect( &pictureRectangle);

  IamBeingUpdated = TRUE;
*/
  DoDraw();
}

void CConcMoment::DoDraw( void )
{
  MoveTo( itsCenterPoint.h, itsCenterPoint.v );
  LineTo( itsCenterPoint.h + 2, itsCenterPoint.v - 7);
  LineTo( itsCenterPoint.h + 7, itsCenterPoint.v - 9);
  LineTo( itsCenterPoint.h + 13, itsCenterPoint.v - 9);
  LineTo( itsCenterPoint.h + 16, itsCenterPoint.v - 7);
  LineTo( itsCenterPoint.h + 19, itsCenterPoint.v - 3);
  LineTo( itsCenterPoint.h + 19, itsCenterPoint.v +5 );
  LineTo( itsCenterPoint.h + 16, itsCenterPoint.v +11 );
  LineTo( itsCenterPoint.h + 12, itsCenterPoint.v +15 );
  LineTo( itsCenterPoint.h + 9, itsCenterPoint.v +17 );
  LineTo( itsCenterPoint.h + 4, itsCenterPoint.v +18 );
  LineTo( itsCenterPoint.h - 9, itsCenterPoint.v +18 );
  LineTo( itsCenterPoint.h + 2, itsCenterPoint.v +16 );
  MoveTo( itsCenterPoint.h - 9, itsCenterPoint.v +18 );
  LineTo( itsCenterPoint.h + 2, itsCenterPoint.v +20 );
}

void CConcMoment::UpDateItsRegion( void )
{
  MoveTo( itsCenterPoint.h, itsCenterPoint.v );
  LineTo( itsCenterPoint.h + 2, itsCenterPoint.v - 5);
  LineTo( itsCenterPoint.h + 7, itsCenterPoint.v - 8);
  LineTo( itsCenterPoint.h + 13, itsCenterPoint.v - 9);
  LineTo( itsCenterPoint.h + 16, itsCenterPoint.v - 7);
  LineTo( itsCenterPoint.h + 19, itsCenterPoint.v - 3);
  LineTo( itsCenterPoint.h + 19, itsCenterPoint.v +5 );
  LineTo( itsCenterPoint.h + 16, itsCenterPoint.v +11 );
  LineTo( itsCenterPoint.h + 12, itsCenterPoint.v +15 );
  LineTo( itsCenterPoint.h + 9, itsCenterPoint.v +17 );
  LineTo( itsCenterPoint.h + 4, itsCenterPoint.v +18 );
  LineTo( itsCenterPoint.h - 9, itsCenterPoint.v +18 );
  LineTo( itsCenterPoint.h + 2, itsCenterPoint.v +16 );
  LineTo( itsCenterPoint.h, itsCenterPoint.v);
}


void CConcMoment::MoveYourself( void )
{
  Point    temp1, temp2;
  int      xLength, yLength;


/*  xLength = its2ndEnd.h - its1stEnd.h;
  yLength = its2ndEnd.v - its1stEnd.v;
*/
  itsCenterPoint.h  = theHitPoint.h - offSet.h;
  itsCenterPoint.v = theHitPoint.v - offSet.v;

/*  its2ndEnd.h = its1stEnd.h + xLength;
  its2ndEnd.v = its1stEnd.v + yLength;
*/
/*  itsCenterPoint.v = ( its2ndEnd.v + its1stEnd.v ) / 2;
  itsCenterPoint.h = ( its2ndEnd.h + its1stEnd.h ) / 2;
*/
  DragYourself();
}

void CConcMoment::UpDateObject( void )
{
  if ( ReSizingInProgress )
  {
    MoveYourself();
  }
  else if( ! IamConnected )
  {
    MoveYourself();
  }
}

Boolean CConcMoment::WhichOneOfUsGotSelected( Point aPoint )
{
  if( PtInRgn( aPoint, itsRegion )) /* in truss element in region */
  {
/*    if ( gClicks == DOUBLE_CLICKS )
    {
      this->DoYourDialog();
      return( FALSE );
    }
*/
    ReSizingInProgress = FALSE;

    itsCenterPointFlag = FALSE;
    its1stEndFlag = FALSE;
    its2ndEndFlag = TRUE;    /* this is true, i.e its arrowTail*/

    offSet.v = aPoint.v - itsCenterPoint.v;
    offSet.h = aPoint.h - itsCenterPoint.h;

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
void CConcMoment::DisconnectYourself()
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

    offSet.h = 0;
    offSet.v = 0;
    theHitPoint.h = itsCenterPoint.h + SMALL_LENGTH;
    theHitPoint.v = itsCenterPoint.v - SMALL_LENGTH;

    its1stEndFlag = FALSE;
    its2ndEndFlag = FALSE;
    IamConnected = FALSE;

    its1stEndFlag = TRUE;
    ReSizingInProgress = FALSE;
    UpDateObject();

    DrawFinal();
    SelectYourself();
  }
}

void CConcMoment::DeleteYourself( void )
{
  DisconnectYourself();
  UnSelectYourself();
  Erase();
  itsTrussPane->ConcLoadsAndMoments->Remove( this );
  itsTrussPane->theObject = NULL;
  Dispose();
}

void CConcMoment::DoYourDialog( void )
{
  DialogHandlerRecordPtr   dhp;
  DecForm          dForm;
  float          xLocation;
  float          yLocation;
  float          newTElementConnectionRatio;

  DHStandardNewRecord (&dhp, ConcMomentDLOG_ID,
                ConcMomentUpdateUserItemId, ConcMomentMagnitude);

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, ConcMomentMagnitude,
    (itsMagnitude),
      dForm, MINREAL, MAXREAL);  /* should be limit of drawing area*/


  if ( IamConnected && itsTElement)
  {
    dForm.digits = 2;
    dForm.style = FIXEDDECIMAL;
    DHAdvAddEditReal(dhp, ConcMomentTEConnectionRatio,
      (TElementConnectionRatio ),
        dForm, 0.0, 1.0);
  }




  if (DHDialogHandler(dhp))
  {
    itsMagnitude = DHGetEditReal(dhp, ConcMomentMagnitude);
    if( IamConnected )
      newTElementConnectionRatio =
          DHGetEditReal(dhp, ConcMomentTEConnectionRatio);


    if(  IamConnected  && itsTElement) /* i.e only if connected to TE*/
    {
      if ( ! (Abs(newTElementConnectionRatio -
        TElementConnectionRatio) <= SMALL_FLOAT_VALUE)  )
      {
        UnSelectYourself();
        Erase();

        TElementConnectionRatio = newTElementConnectionRatio;
        itsTElement->DrawFinal();
        DrawFinal();
      }
    }
  }

  DHDeallocateRecord(dhp);
}




void CConcMoment::PrepareYourselfToBeUpdated( void )
{
  Point    TE1stEnd, TE2ndEnd;
  Point    connectToThisPoint;

  TE1stEnd.h = itsTElement->its1stEnd.h;
  TE1stEnd.v = itsTElement->its1stEnd.v;
  TE2ndEnd.h = itsTElement->its2ndEnd.h;
  TE2ndEnd.v = itsTElement->its2ndEnd.v;


  connectToThisPoint.h = ((int)((( float)(TE2ndEnd.h -TE1stEnd.h))
          *TElementConnectionRatio)) + TE1stEnd.h;
  connectToThisPoint.v = ((int)((( float)(TE2ndEnd.v -TE1stEnd.v))
          *TElementConnectionRatio)) + TE1stEnd.v;

  itsCenterPoint.h = connectToThisPoint.h;
  itsCenterPoint.v = connectToThisPoint.v;

/*  FromCornersToItsCenterPoint();
*/
}

Boolean CConcMoment::ConnectYourselfToNode(  struct CNodeObject
                      *theSelectedNodeObject )
{
  if( ! this->IamConnected )
      /* to make sure that it is not already connected*/
  {
    this->SelectYourself();
          /* this should be changed-->*/
    this->the1stEndNode = theSelectedNodeObject;
    this->the1stEndConnected = TRUE;
    theSelectedNodeObject->AddToItsConcLandMCluster( this );
    this->UnSelectYourself();
    theSelectedNodeObject->SelectYourself();
    itsTrussPane->theObject = theSelectedNodeObject;
    IamConnected = TRUE;
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

Boolean CConcMoment::ConnectYourselfToTE(  CTrussElementObject
                        *theSelectedTEObject )
{
  if( ! this->IamConnected )
  /* to make sure that it is not already connected*/
  {
    this->SelectYourself();
    theSelectedTEObject->AddToItsConcLandMCluster(   /* this should be*/
    this);              /*changed-->*/
    this->itsTElement = theSelectedTEObject;
        /* this should be changed-->*/
    this->the1stEndConnected = TRUE;
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


void CConcMoment::PrepareYourselfToBeUpdatedByNode( void )
{

  if ( the1stEndConnected )
  {
    itsCenterPoint.h = the1stEndNode->itsCenterPoint.h;
    itsCenterPoint.v = the1stEndNode->itsCenterPoint.v;
  }
  else if( the2ndEndConnected )
  {
  }
}


