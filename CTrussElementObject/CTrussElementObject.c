/****
 * CTurssElementObject.c
 *
 *  Truss element object class for a typical CTrussPane class
 *
 ****/

#include "CTrussElementObject.phs"

/*** Global Variables ***/

extern  CBartender *gBartender;
extern   short    gClicks;

void CTrussElementObject::InitializeYourself( void )

{
  offSet.h = 0;
  offSet.v = 0;

  itsCenterPoint.h = theHitPoint.h - offSet.h;
  itsCenterPoint.v = theHitPoint.v - offSet.v;

  its1stEnd.h = itsCenterPoint.h - 30;
  its1stEnd.v = itsCenterPoint.v - 30;
  its2ndEnd.h = itsCenterPoint.h + 30;
  its2ndEnd.v = itsCenterPoint.v + 30;

  E = 29000000;
  Ixx = 1000;
  Iyy = 40;
  BendingStrength = 36000;
  TensileStrength = 36000;
  CompressiveStrength = 36000;
  Area = 35;

  CounterMoneyValue = 5000;
  CounterDaysValue = 60;

  itsRegion = NewRgn();

  OpenRgn();
  UpDateItsRegion();
  CloseRgn(itsRegion);
  InsetRgn( itsRegion, RGN_EXPANSION_IN_PIXELS, RGN_EXPANSION_IN_PIXELS);
        /* make the region larger */

  Draw();

  IamSelected = FALSE;
  ReSizingInProgress = FALSE;
  itsCenterPointFlag = FALSE;
  its1stEndFlag = FALSE;
  its2ndEndFlag = FALSE;
  IamConnected = FALSE;
  the1stEndNode = NULL;
  the2ndEndNode = NULL;
  the1stEndConnected = FALSE;
  the2ndEndConnected = FALSE;

  theTEConcLoadsAndMoments = new( CClustOfConcLoadsAndMoments );
  theTEConcLoadsAndMoments->ICluster();
  theTEContLoadsAndMoments = new( CClustOfContLoadsAndMoments );
  theTEContLoadsAndMoments->ICluster();
  theTENodes = new( CClusterOfNodes );
  theTENodes->ICluster();
  ConcLandMAreConnected = FALSE;
  ContLandMAreConnected = FALSE;
  NodesAreConnected = FALSE;

  its1stEndGlobalNumber = 0L;
  its2ndEndGlobalNumber = 0L;

}



void CTrussElementObject::SelectYourself( void )
{

  DrawResizingHandles( itsCenterPoint );
  DrawResizingHandles( its1stEnd );
  DrawResizingHandles( its2ndEnd );

  IamSelected = TRUE;
}
      static void Perform_UnSelection(
                  CAbstractObject *theObject )
      {
          theObject->UnSelectYourself();
      }


void CTrussElementObject::UnSelectYourself( void )
{
  PenState  pnState;

  if ( IamSelected )
  {
      /* this will have effect of erasing squares */
    EraseResizingHandles( itsCenterPoint );
    EraseResizingHandles( its1stEnd );
    EraseResizingHandles( its2ndEnd );

    Draw();
    IamSelected = FALSE;
  }
  if( NodesAreConnected )
      theTENodes->DoForEach(
                Perform_UnSelection );
}

        static void Perform_ConcLandMUpdate( CConcLoadObject
          *theObject, HitPtAndObjectPtr *theHitPtAndObjectPtr)
        {

          if( (theObject->itsTElement) ==
            theHitPtAndObjectPtr->thisObjectPointer)
          {
            theObject->PrepareYourselfToBeUpdated();
            theObject->Draw();
          }
        }
        static void Perform_ContLandMUpdate( CQuadrelateralObject
             *theObject, HitPtAndObjectPtr *theHitPtAndObjectPtr)
        {

          if( (theObject->itsTElement) ==
            theHitPtAndObjectPtr->thisObjectPointer)
          {
            theObject->PrepareYourselfToBeUpdated();
            theObject->Draw();
          }
        }
        static void Perform_NUpdate( CNodeObject
            *theObject, HitPtAndObjectPtr *theHitPtAndObjectPtr )
        {
          if( theObject->itsMotherTElement ==
                theHitPtAndObjectPtr->thisObjectPointer)
          {
            theObject->PrepareYourselfToBeUpdated();
            theObject->Draw();
          }
        }

void CTrussElementObject::DoDrawing( void )
{

  MoveTo( its1stEnd.h, its1stEnd.v);
  PenSize( 2,2);
  LineTo( its2ndEnd.h, its2ndEnd.v);
  PenSize( 1,1);
/*  UpDateItsRegion();
*/
}

void CTrussElementObject::Draw( void )
{
  HitPtAndObjectPtr  theHitPtAndObjectPtr;

  DoDrawing();

  theHitPtAndObjectPtr.thisObjectPointer = this->thisObjectPointer;
  theHitPtAndObjectPtr.thisHitPoint.v = itsCenterPoint.v;
  theHitPtAndObjectPtr.thisHitPoint.h = itsCenterPoint.h;
  theHitPtAndObjectPtr.ReSizingInProgress = ReSizingInProgress;

  if( ConcLandMAreConnected )
  {
    theTEConcLoadsAndMoments->DoForEach1( Perform_ConcLandMUpdate,
                (long)(&theHitPtAndObjectPtr) );
  }
  if( ContLandMAreConnected )
  {
    theTEContLoadsAndMoments->DoForEach1( Perform_ContLandMUpdate,
                (long)(&theHitPtAndObjectPtr) );
  }
  if ( NodesAreConnected )
  {
    theTENodes->DoForEach1( Perform_NUpdate,
                (long)(&theHitPtAndObjectPtr) );
  }
}

void CTrussElementObject::UpDateItsRegion( void )
{
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

void CTrussElementObject::MoveYourself( void )
{
  Point    temp1, temp2;
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


void CTrussElementObject::UpDateObject( void )
{
  if ( ReSizingInProgress )
  {
    ResizeYourself();
  }
  else if( ( ! the1stEndConnected) && ( ! the2ndEndConnected ) )
  {
    MoveYourself();
  }
  else
  {
    /*DoYourDialog(); if an Object is being moved when it is conn.*/
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

Boolean CTrussElementObject::WhichOneOfUsGotSelected( Point aPoint )
{
  float    offSetLength;
  float    TElementLength;

  if ( ( HitSamePart( its2ndEnd, aPoint, &offSet ) ) )
  {
    ReSizingInProgress = TRUE;
    MovingInProgress = FALSE;

    itsCenterPointFlag = FALSE;
    its1stEndFlag = FALSE;
    its2ndEndFlag = TRUE;

    lastClickLocatedAtRatio = 1.0;

    return ( TRUE );
  }

  else if ( ( HitSamePart( its1stEnd, aPoint, &offSet  ) ) )
  {
    ReSizingInProgress = TRUE;
    MovingInProgress = FALSE;

    itsCenterPointFlag = FALSE;
    its1stEndFlag = TRUE;
    its2ndEndFlag = FALSE;

    lastClickLocatedAtRatio = 0.0;


    return ( TRUE );
  }

  else if( PtInRgn( aPoint, itsRegion )) /* in truss element in region */
  {

    offSet.v = aPoint.v - its1stEnd.v;
    offSet.h = aPoint.h - its1stEnd.h;

    offSetLength = ( float) sqrt( (double)(( ((float)(aPoint.h-its1stEnd.h))*
            ((float)(aPoint.h-its1stEnd.h))) +
            ( ((float)(aPoint.v-its1stEnd.v))*
            ((float)(aPoint.v-its1stEnd.v))) ) );

    TElementLength = (float) sqrt((double)(( (((float)(its2ndEnd.v -its1stEnd.v))*
              ((float)(its2ndEnd.v -its1stEnd.v) )) +
              ( ((float)(its2ndEnd.h -its1stEnd.h))*
              ((float)(its2ndEnd.h -its1stEnd.h)) ) ) ) );

    lastClickLocatedAtRatio =  offSetLength / TElementLength;

    ReSizingInProgress = FALSE;
    MovingInProgress = TRUE;

    itsCenterPointFlag = FALSE;
    its1stEndFlag = FALSE;
    its2ndEndFlag = FALSE;

    return( TRUE );
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


void CTrussElementObject::DoYourDialog( void )
{
  inherited::DoYourDialog();
}

void CTrussElementObject::DrawResizingHandles( Point giveMeAPoint )
{
  inherited::DrawResizingHandles(  giveMeAPoint );
}

void CTrussElementObject::ResizeYourself( void )
{

  FromtheHitPointToCorners();
  DragYourself();
  FromCornersToItsCenterPoint();
}

void  CTrussElementObject::FromtheHitPointToCorners( void )
{
  if ( its2ndEndFlag )
  {
    its2ndEnd.h = theHitPoint.h - offSet.h;
    its2ndEnd.v = theHitPoint.v - offSet.v;
  }
  else
  if ( its1stEndFlag )
  {
    its1stEnd.h = theHitPoint.h - offSet.h;
    its1stEnd.v = theHitPoint.v - offSet.v;
  }
}


void  CTrussElementObject::FromCornersToItsCenterPoint( void )
{
  itsCenterPoint.v = ( its2ndEnd.v + its1stEnd.v ) / 2;
  itsCenterPoint.h = ( its2ndEnd.h + its1stEnd.h ) / 2;
}

void CTrussElementObject::DrawFinal( void )
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
void CTrussElementObject::DoDrawingFinal( void )
{
  PenState     pnState;

  OpenRgn();
  UpDateItsRegion();
  CloseRgn(itsRegion);
  InsetRgn( itsRegion, RGN_EXPANSION_IN_PIXELS, RGN_EXPANSION_IN_PIXELS);
        /* make the region larger */


  GetPenState ( &pnState);/* to save the pen setting */
  PenMode ( patCopy );
  DoDrawing();          /* this is needed to fill gaps */
  SetPenState ( &pnState);/* to resotre pen settting */


}

/* ----------------------------------------------------------------------------  */
/* Copyright ©1987-1989 by Gary Gregory and Neil Ticktin.  All rights reserved.  */
/* Version 1.0.  Any portion of this demo can be used in your application as  */
/* long as you follow the terms in the Invention Software Licensing Agreement.  */
/* ----------------------------------------------------------------------------  */

/* Unit DemoCounters */

void CTrussElementObject::DoDialogItemsCounter(void)
{
  DialogHandlerRecordPtr dhp;
  DecForm  dForm;

  DHStandardNewRecord (&dhp, CounterDLOG_ID, CounterUpdateUserItemId, NoSelectedItem);

  dForm.digits = 4;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddCounter(dhp, CounterMoneyId, CounterMoneyArrowId, CounterMoneyValue, 0.01, 0.0, MAXREAL, DHMakeKeyEquiv(NORMAL, '+'), DHMakeKeyEquiv(NORMAL, '-'), dForm, VeryShortDelay, NULL);

  dForm.digits = 0;
  DHAdvAddCounter(dhp, CounterDaysId, CounterDaysArrowId, CounterDaysValue, 1.0, 0.0, 99.0, DHNoKeyEquiv(), DHNoKeyEquiv(), dForm, ShortDelay, NULL);

  DHSetDialogFont(dhp, monaco, 9, (Style)NULL);
/*  DHADDDISPLAYTEXT(dhp, CounterDispTextId, CounterDLOG_ID); /* CounterDLOG_ID is the same number as the TEXTid */

/*  DHSetCentering(dhp, PrefCenterHorizValue, PrefCenterVertValue, SaveCenteringOff);
  DHSetNearMousePointer(dhp, PrefNearHorizValue, PrefNearVertValue);
*/
  if (DHDialogHandler(dhp))
  {
    CounterMoneyValue = DHGetCounterValue(dhp, CounterMoneyId);
    CounterDaysValue = DHGetCounterValue(dhp, CounterDaysId);
  }

  DHDeallocateRecord(dhp);
}


void CTrussElementObject::AddToItsContLandMCluster( struct
            CQuadrelateralObject   *theContLoadOrMoment )
{
  Point    connectToThisPoint;

  connectToThisPoint.h = ((int)((( float)(its2ndEnd.h -its1stEnd.h))
          *lastClickLocatedAtRatio)) + its1stEnd.h;
  connectToThisPoint.v = ((int)((( float)(its2ndEnd.v -its1stEnd.v))
          *lastClickLocatedAtRatio)) + its1stEnd.v;

  theTEContLoadsAndMoments->Add( theContLoadOrMoment );
  theContLoadOrMoment->theHitPoint = connectToThisPoint;
  theContLoadOrMoment->offSet.h = 0;
  theContLoadOrMoment->offSet.v = 0;
  ContLandMAreConnected = TRUE;
}

Boolean CTrussElementObject::ConnectYourselfToNode(   CNodeObject
                      *theSelectedNodeObject )
{
  if( ( ! theTENodes->Includes( theSelectedNodeObject ) ) )
      /* this is to make sure that the selected*/
      /* node is not already in the TENodes cluster */
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
    theSelectedNodeObject->AddToItsTElementsCluster( this );
    IamConnected = TRUE;
    this->UnSelectYourself();
    theSelectedNodeObject->SelectYourself();
    itsTrussPane->theObject = theSelectedNodeObject;
    return TRUE;
  }
  else
    return FALSE;

}



        static void Disconnect_ConLandM( CConcLoadObject
            *theObject, HitPtAndObjectPtr *theHitPtAndObjectPtr)
        {
            theObject->the1stEndConnected = FALSE;
            theObject->the1stEndNode = NULL;
            theObject->the2ndEndConnected = FALSE;
            theObject->the2ndEndNode = NULL;

               theObject->IamConnected = FALSE;
        }
        static void Copy_Cluster( CQuadrelateralObject
            *theObject, CClustOfContLoadsAndMoments
                **theTEMP_TEContLAndM_ptr)
        {
               (*theTEMP_TEContLAndM_ptr)->Add( theObject );
        }
        static void Disconnect_ContLandM( CQuadrelateralObject
            *theObject, HitPtAndObjectPtr *theHitPtAndObjectPtr)
        {
               theObject->DisconnectYourself();
               theObject->IamConnected = FALSE;
               theObject->loadAlongAllMember = FALSE;
            theObject->UnSelectYourself();
        }

        static void Disconnect_Nodes( CNodeObject
            *theObject, HitPtAndObjectPtr *theHitPtAndObjectPtr)
        {
               theObject->IamConnected = FALSE;
               theObject->itsMotherTElement = NULL;
        }

        static void Perform_Draw( CAbstractObject
            *theObject)
        {
            theObject->DrawFinal();
        }


void CTrussElementObject::DisconnectYourself( void )
{
  HitPtAndObjectPtr  theHitPtAndObjectPtr;
  Boolean        DisconnectionOK = FALSE;
  CClustOfContLoadsAndMoments    *theTEMP_TEContLAndM;


  theHitPtAndObjectPtr.thisObjectPointer = this;
  theHitPtAndObjectPtr.thisHitPoint.v = itsCenterPoint.v;
  theHitPtAndObjectPtr.thisHitPoint.h = itsCenterPoint.h;

  if( IamConnected )  /* i.e IamConnected to Nodes*/
  {
    UnSelectYourself();
    Erase();
    IamConnected = FALSE;
    if ( the1stEndConnected )
    {
      the1stEndNode->theNodeTElements
          ->Remove( this );
      the1stEndNode->DrawFinal();
      the1stEndNode = NULL;
      the1stEndConnected = FALSE;
    }
    if (the2ndEndConnected )
    {
      the2ndEndNode->theNodeTElements
          ->Remove( this );
      the2ndEndNode->DrawFinal();
      the2ndEndNode = NULL;
      the2ndEndConnected = FALSE;
    }
    IamConnected = FALSE;

    DisconnectionOK = TRUE;
  }
  else
  {
    if( ConcLandMAreConnected )
    {
      DisconnectionOK = TRUE;
      theTEConcLoadsAndMoments->DoForEach1(
        Disconnect_ConLandM, (long)(&theHitPtAndObjectPtr) );
      UnSelectYourself();
      Erase();
      IamConnected = FALSE;

      ConcLandMAreConnected = FALSE;
      theTEConcLoadsAndMoments->DoForEach( Perform_Draw );
      theTEConcLoadsAndMoments->ICluster();
    }
    if( ContLandMAreConnected )
    {
      DisconnectionOK = TRUE;
        /* this is a very interesting way of doing things*/
        /* I wanted to issue a DisconnectYourself() message*/
        /* to all object in theTEContLoadsAndMoments cluster*/
        /* the problem is that the DisconnectYourself() method*/
        /* itself modifies the theTEContLoadsAndMoments because*/
        /* it Remove( theContLorM) from the cluster, and thus*/
        /* NOT_All theContLorM would be Disconnected*/
        /* the Solution: */
        /* 1.Create a temp cluster theTEMP_TEContLAndM */
        /* 2.Copy each object inside theTEContLoadsAndMoments into*/
        /*     theTEMP_TEContLAndM */
        /* 3.Using this temp cluster issue to each object in it */
        /* a DisconnectYourself() message, thus making sure that */
        /* all object will get it, and as a result each one of */
        /*these object will Remove itself from theTEContLoadsAndMoments*/

      theTEMP_TEContLAndM = new( CClustOfContLoadsAndMoments );
      theTEMP_TEContLAndM->ICluster();
      theTEContLoadsAndMoments->DoForEach1(
        Copy_Cluster, (long)(&theTEMP_TEContLAndM) );

      theTEMP_TEContLAndM->DoForEach1(
        Disconnect_ContLandM, (long)(&theHitPtAndObjectPtr) );
      UnSelectYourself();
      Erase();
      IamConnected = FALSE;

      ContLandMAreConnected = FALSE;
      theTEMP_TEContLAndM->DoForEach(  Perform_Draw );
      theTEContLoadsAndMoments->ICluster();

      theTEMP_TEContLAndM->Dispose();
    }
    if ( NodesAreConnected )
    {
      DisconnectionOK = TRUE;
      theTENodes->DoForEach1(
        Disconnect_Nodes, (long)(&theHitPtAndObjectPtr) );
      UnSelectYourself();
      Erase();
      IamConnected = FALSE;

      NodesAreConnected = FALSE;
      theTENodes->DoForEach(  Perform_Draw );
      theTENodes->ICluster();
    }
  }
  if( DisconnectionOK )
  {
    theHitPoint.h = its1stEnd.h + SMALL_LENGTH;
    theHitPoint.v = its1stEnd.v - SMALL_LENGTH;
    offSet.h = 0;
    offSet.v = 0;
    ReSizingInProgress = FALSE;
    UpDateObject();
    DrawFinal();
    SelectYourself();
  }
}

void CTrussElementObject::DeleteYourself( void )
{
  Rect  aRect;

  DisconnectYourself();
  DisconnectYourself();
  UnSelectYourself();
  Erase();
  itsTrussPane->TElementsCluster->Remove( this );
  itsTrussPane->Draw( &aRect );
  itsTrussPane->theObject = NULL;
  Dispose();
}


void CTrussElementObject::AddToItsConcLandMCluster( CConcLoadObject *theConcLoadOrMoment )
{
  Point    connectToThisPoint;

  connectToThisPoint.h = ((int)((( float)(its2ndEnd.h -its1stEnd.h))
          *lastClickLocatedAtRatio)) + its1stEnd.h;
  connectToThisPoint.v = ((int)((( float)(its2ndEnd.v -its1stEnd.v))
          *lastClickLocatedAtRatio)) + its1stEnd.v;

  theTEConcLoadsAndMoments->Add( theConcLoadOrMoment );
  theConcLoadOrMoment->UnSelectYourself();
  theConcLoadOrMoment->Erase();
  theConcLoadOrMoment->theHitPoint = connectToThisPoint;
  theConcLoadOrMoment->TElementConnectionRatio = lastClickLocatedAtRatio;
  theConcLoadOrMoment->ReSizingInProgress = TRUE;
  theConcLoadOrMoment->offSet.h = 0;
  theConcLoadOrMoment->offSet.v = 0;
  theConcLoadOrMoment->UpDateObject();
  theConcLoadOrMoment->DrawFinal();
  theConcLoadOrMoment->UnSelectYourself();
  theConcLoadOrMoment->IamConnected = TRUE;
  ConcLandMAreConnected = TRUE;
}

void CTrussElementObject::AddToItsNodesCluster( CNodeObject *theNodeObject )
{
  Point    connectToThisPoint;

  connectToThisPoint.h = ((int)((( float)(its2ndEnd.h -its1stEnd.h))
          *lastClickLocatedAtRatio)) + its1stEnd.h;
  connectToThisPoint.v = ((int)((( float)(its2ndEnd.v -its1stEnd.v))
          *lastClickLocatedAtRatio)) + its1stEnd.v;

  theTENodes->Add( theNodeObject );
  theNodeObject->UnSelectYourself();
  theNodeObject->Erase();
  theNodeObject->theHitPoint = connectToThisPoint;
  theNodeObject->TElementConnectionRatio = lastClickLocatedAtRatio;
  theNodeObject->offSet.h = 0;
  theNodeObject->offSet.v = 0;
  theNodeObject->UpDateObject();
  theNodeObject->DrawFinal();
  theNodeObject->UnSelectYourself();
  theNodeObject->IamConnected = TRUE;
  NodesAreConnected = TRUE;
}

void CTrussElementObject::Dispose()
{
  DisposHandle( itsRegion );
  theTEConcLoadsAndMoments->Dispose();
  theTEContLoadsAndMoments->Dispose();
  theTENodes->Dispose();

  inherited::Dispose();
}

void  CTrussElementObject::PrintDebugInfo( void )
{
}
void  CTrussElementObject::PrintFileStatics( void )
{
}
void  CTrussElementObject::PrintFileFireWood( void )
{
}
void  CTrussElementObject::PrintFileWood1( void )
{
}
void  CTrussElementObject::PrintFileWood2( void )
{
}
void  CTrussElementObject::PrintFileWood3( void )
{
}
void  CTrussElementObject::PrintFileWood4( void )
{
}



void  CTrussElementObject::KillYourself_IF_NOT_Connected( void )
{
  if( ! IamConnected )
  {
    if( NodesAreConnected )
    {
      if( theTENodes->numItems == 0 )
      {
        DeleteYourself();
      }
    }
    else
      DeleteYourself();
  }

}
void  CTrussElementObject::SaveYourself( void )
{
}
void  CTrussElementObject::LoadYourself( void )
{
}

short CTrussElementObject::WhichEndIsConnected( CNodeObject *theNode )
{
  if( theNode == the1stEndNode)
    return ( 1 );
  else
  if( theNode == the2ndEndNode )
    return( 2 );
  else
    return( 0 );
}


void CTrussElementObject::InitializeGlobalNumbers( void )
{
  its1stEndGlobalNumber = 0L;
  its2ndEndGlobalNumber = 0L;
  theObjectNumber = 0L;
}

