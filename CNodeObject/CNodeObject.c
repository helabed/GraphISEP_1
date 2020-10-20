/****
 * CNodeObject.c
 *
 *  Node object class for a typical CTrussPane class
 *
 ****/

#include "CNodeObject.phs"


/*** Global Variables ***/
extern  CBartender *gBartender;
extern   short    gClicks;


void CNodeObject::InitializeYourself( void )

{
  Rect  myRect;
  Point  hitPt;


  offSet.h = 0;
  offSet.v = 0;

  itsCenterPoint.h = theHitPoint.h - offSet.h;
  itsCenterPoint.v = theHitPoint.v - offSet.v;

  IamSelected = FALSE;
  ReSizingInProgress = FALSE;
  IamConnected = FALSE;

  itsBoundaryCondition = Free;

  itsCenterPointFlag = FALSE;

  theNodeLoads = new( CClustOfConcLoadsAndMoments );
  theNodeLoads->ICluster();
  theNodeTElements = new( CClusterOfTElements );
  theNodeTElements->ICluster();
  ConcLandMAreConnected = FALSE;
  TElementsAreConnected = FALSE;
  dumyBoolean = FALSE;

  itsMotherTElement = NULL;
  itsGlobalNumber = 0L;

  DrawFinal();
}



void CNodeObject::SelectYourself( void )
{
  Point    topLeftCorner;
  Point    bottomRightCorner;
  Point    bottomLeftCorner;
  Point    topRightCorner;


  topLeftCorner.h = itsCenterPoint.h - 7;
  topLeftCorner.v = itsCenterPoint.v - 7;
  bottomRightCorner.h = itsCenterPoint.h + 7;
  bottomRightCorner.v = itsCenterPoint.v + 7;
  bottomLeftCorner.h = itsCenterPoint.h - 7;
  bottomLeftCorner.v = itsCenterPoint.v +7;
  topRightCorner.h = itsCenterPoint.h + 7;
  topRightCorner.v = itsCenterPoint.v - 7;

  DrawResizingHandles( topRightCorner );
  DrawResizingHandles( topLeftCorner );
  DrawResizingHandles( bottomRightCorner );
  DrawResizingHandles( bottomLeftCorner );

  IamSelected = TRUE;
}
void CNodeObject::AddPicture( void )
{
  switch( itsBoundaryCondition )
  {
    case Free:
      /*do nothing */
      break;

    case RotationFixed:
      pictureRectangle.top =  itsCenterPoint.v -10;
      pictureRectangle.bottom = itsCenterPoint.v + 10;
      pictureRectangle.left =  itsCenterPoint.h - 10;
      pictureRectangle.right =  itsCenterPoint.h + 10;
      DrawPicture( pHandle, &pictureRectangle);
      break;


    case yTranslationAndRotationFixed:
    case xyTranslationAndRotationFixed:
    case xyTranslationFixed:
    case yTranslationFixed:
      pictureRectangle.top =  itsCenterPoint.v-3;
      pictureRectangle.bottom = itsCenterPoint.v +17;
      pictureRectangle.left =  itsCenterPoint.h-10;
      pictureRectangle.right =  itsCenterPoint.h+10;
      DrawPicture( pHandle, &pictureRectangle);
      break;

    case xTranslationFixed:
    case xTranslationAndRotationFixed:
      pictureRectangle.top =  itsCenterPoint.v-10;
      pictureRectangle.bottom = itsCenterPoint.v +10;
      pictureRectangle.left =  itsCenterPoint.h-17;
      pictureRectangle.right =  itsCenterPoint.h+3;
      DrawPicture( pHandle, &pictureRectangle);
      break;
  }

}
void CNodeObject::RemovePicture( void )
{
  Rect        myRect1, myRect2;
  Point        hitPt;
  PenState      pnState;

  hitPt.h = itsCenterPoint.h;
  hitPt.v = itsCenterPoint.v;


  myRect1.top = hitPt.v - 5;
  myRect1.left = hitPt.h - 10;
  myRect1.bottom = hitPt.v + 5;
  myRect1.right = hitPt.h + 10;

  myRect2.top = hitPt.v - 6;
  myRect2.left = hitPt.h - 11;
  myRect2.bottom = hitPt.v + 6;
  myRect2.right = hitPt.h + 11;


  EraseRect( &pictureRectangle);
  GetPenState ( &pnState);
  PenMode ( patBic );

  PaintRect( &myRect2 );
  SetPenState ( &pnState);

  GetPenState ( &pnState);/* to save the pen setting */
  PenMode ( patCopy );
  Draw();          /* this is needed to fill gaps */
  SetPenState ( &pnState);/* to resotre pen settting */

}

      static void Perform_UnSelection(
                  CAbstractObject *theObject )
      {
          theObject->UnSelectYourself();
      }

void CNodeObject::UnSelectYourself( void )
{
  PenState  pnState;
  Point    topLeftCorner;
  Point    bottomRightCorner;
  Point    bottomLeftCorner;
  Point    topRightCorner;


  topLeftCorner.h = itsCenterPoint.h - 7;
  topLeftCorner.v = itsCenterPoint.v - 7;
  bottomRightCorner.h = itsCenterPoint.h + 7;
  bottomRightCorner.v = itsCenterPoint.v + 7;
  bottomLeftCorner.h = itsCenterPoint.h - 7;
  bottomLeftCorner.v = itsCenterPoint.v +7;
  topRightCorner.h = itsCenterPoint.h + 7;
  topRightCorner.v = itsCenterPoint.v - 7;

  if ( IamSelected )
  {
      /* this will have effect of erasing squares */
    EraseResizingHandles( topRightCorner );
    EraseResizingHandles( topLeftCorner );
    EraseResizingHandles( bottomRightCorner );
    EraseResizingHandles( bottomLeftCorner );

    DrawFinal();
    IamSelected = FALSE;
  }
  RemovePicture();
  if( TElementsAreConnected )
      theNodeTElements->DoForEach(
                Perform_UnSelection );

}


    static void Perform_ConcL_and_MUpdate( CConcLoadObject *theObject,
            HitPtAndObjectPtr *theHitPtAndObjectPtr)
    {

      if( (theObject->the1stEndNode) ==
        theHitPtAndObjectPtr->thisObjectPointer)
      {
        theObject->PrepareYourselfToBeUpdatedByNode();
        theObject->Draw();
      }
      else if( theObject->the2ndEndNode ==
        theHitPtAndObjectPtr->thisObjectPointer )
      {
        theObject->PrepareYourselfToBeUpdatedByNode();
        theObject->Draw();
      }
    }
    static void Perform_TEUpdate( CTrussElementObject
        *theObject, HitPtAndObjectPtr *theHitPtAndObjectPtr )
    {

      if( theObject->the1stEndNode ==
            theHitPtAndObjectPtr->thisObjectPointer)
      {
        theObject->its1stEnd = theHitPtAndObjectPtr->thisHitPoint;
        theObject->FromCornersToItsCenterPoint();
        theObject->Draw();
      }
      else if( theObject->the2ndEndNode ==
            theHitPtAndObjectPtr->thisObjectPointer )
      {
        theObject->its2ndEnd = theHitPtAndObjectPtr->thisHitPoint;
        theObject->FromCornersToItsCenterPoint();
        theObject->Draw();
      }
    }

void CNodeObject::DoDrawing( void )
{
  Rect        myRect1, myRect2;
  Point        hitPt;
  PenState      pnState;

  hitPt.h = itsCenterPoint.h;
  hitPt.v = itsCenterPoint.v;

  myRect1.top = hitPt.v - 5;
  myRect1.left = hitPt.h - 5;
  myRect1.bottom = hitPt.v + 5;
  myRect1.right = hitPt.h + 5;

  myRect2.top = hitPt.v - 6;
  myRect2.left = hitPt.h - 6;
  myRect2.bottom = hitPt.v + 6;
  myRect2.right = hitPt.h + 6;

  FrameOval( &myRect2 );


  GetPenState ( &pnState);  /* to save the pen setting */
  PenPat ( ltGray );
  PaintOval( &myRect1 );
  SetPenState ( &pnState);  /* to resotre pen settting */

}


void CNodeObject::Draw( void )

{
  HitPtAndObjectPtr  theHitPtAndObjectPtr;

  theHitPtAndObjectPtr.thisObjectPointer = this->thisObjectPointer;
  theHitPtAndObjectPtr.thisHitPoint.v = itsCenterPoint.v;
  theHitPtAndObjectPtr.thisHitPoint.h = itsCenterPoint.h;

  if( ConcLandMAreConnected )
  {
    theNodeLoads->DoForEach1( Perform_ConcL_and_MUpdate, (long)(&theHitPtAndObjectPtr) );
  }
  if ( TElementsAreConnected )
  {
    theNodeTElements->DoForEach1( Perform_TEUpdate, (long)(&theHitPtAndObjectPtr) );
  }
  DoDrawing();

}

void CNodeObject::DrawNodeOnly( void )
{
  Rect        myRect1, myRect2;
  Point        hitPt;
  PenState      pnState;

  AddPicture();

  hitPt.h = itsCenterPoint.h;
  hitPt.v = itsCenterPoint.v;

  myRect1.top = hitPt.v - 5;
  myRect1.left = hitPt.h - 5;
  myRect1.bottom = hitPt.v + 5;
  myRect1.right = hitPt.h + 5;

  myRect2.top = hitPt.v - 6;
  myRect2.left = hitPt.h - 6;
  myRect2.bottom = hitPt.v + 6;
  myRect2.right = hitPt.h + 6;

  FrameOval( &myRect2 );


  GetPenState ( &pnState);  /* to save the pen setting */
  PenPat ( ltGray );
  PaintOval( &myRect1 );
  SetPenState ( &pnState);  /* to resotre pen settting */
}

void CNodeObject::MoveYourself( void )
{
  if( ! IamConnected )  /* i.e if it is not connected to TE */
              /* this is different from having TE */
              /* connected to it */
  {
    itsCenterPoint.h = theHitPoint.h - offSet.h;
    itsCenterPoint.v = theHitPoint.v - offSet.v;

    DragYourself();
  }
}


void CNodeObject::UpDateObject( void )
{
  if ( ReSizingInProgress )
  {
    ResizeYourself();  /* this is almost never used */
  }
  else
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

Boolean CNodeObject::WhichOneOfUsGotSelected( Point aPoint )
{
  if ( ( HitSamePart( itsCenterPoint, aPoint, &offSet  ) ) )
  {
    ReSizingInProgress = FALSE;

    itsCenterPointFlag = TRUE;

    return ( TRUE );
  }

}

void CNodeObject::DrawResizingHandles( Point giveMeAPoint )
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

void CNodeObject::ResizeYourself( void )
{
  itsCenterPoint.h = theHitPoint.h - offSet.h;
  itsCenterPoint.v = theHitPoint.v - offSet.v;


  DragYourself();
}



void CNodeObject::AddToItsConcLandMCluster( CConcLoadObject *theConcLoadOrMoment )
{

  theNodeLoads->Add( theConcLoadOrMoment );
  ConcLandMAreConnected = TRUE;
  theConcLoadOrMoment->UnSelectYourself();
  theConcLoadOrMoment->Erase();
  theConcLoadOrMoment->theHitPoint = this->itsCenterPoint;
  theConcLoadOrMoment->ReSizingInProgress = TRUE;
  theConcLoadOrMoment->offSet.h = 0;
  theConcLoadOrMoment->offSet.v = 0;
  theConcLoadOrMoment->UpDateObject();
  theConcLoadOrMoment->UnSelectYourself();
  theConcLoadOrMoment->DrawFinal();
}


void CNodeObject::AddToItsTElementsCluster( CTrussElementObject
                          *theTElementObject )
{

  theNodeTElements->Add( theTElementObject );
  TElementsAreConnected = TRUE;
  theTElementObject->UnSelectYourself();
  theTElementObject->Erase();
  theTElementObject->theHitPoint = this->itsCenterPoint;
  theTElementObject->ReSizingInProgress = TRUE;
  theTElementObject->offSet.h = 0;
  theTElementObject->offSet.v = 0;
  theTElementObject->UpDateObject();
  theTElementObject->UnSelectYourself();
  theTElementObject->DrawFinal();

}


void CNodeObject::DrawFinal( void )
{
  PenState     pnState;

  AddPicture();
  GetPenState ( &pnState);/* to save the pen setting */
  PenMode ( patCopy );
  Draw();          /* this is needed to fill gaps */
  SetPenState ( &pnState);/* to resotre pen settting */

  dumyBoolean = FALSE;
}
void CNodeObject::DoDrawingFinal( void )
{
  PenState     pnState;

  GetPenState ( &pnState);/* to save the pen setting */
  PenMode ( patCopy );
  DoDrawing();          /* this is needed to fill gaps */
  SetPenState ( &pnState);/* to resotre pen settting */

  dumyBoolean = FALSE;
}


void CNodeObject::Dispose()
{
  theNodeLoads->Dispose();
  theNodeTElements->Dispose();
  ReleaseResource( pHandle );
  inherited::Dispose();
}

        static void Perform_Draw( CAbstractObject
            *theObject)
        {
            theObject->DrawFinal();
        }


void CNodeObject::DoYourDialog( void )
{
  DialogHandlerRecordPtr   dhp;
  RadioButtonSetPtr     set1;
  DecForm          dForm;
  float          xLocation;
  float          yLocation;
  float          newTElementConnectionRatio;
  BoundaryCondition    newBoundaryCondition;

  DHStandardNewRecord (&dhp, GenericNodeDLOG_ID,
                GenericNodeUpdateUserItemId, NoSelectedItem);

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GenericNodeEditTextXLocation,
    (itsCenterPoint.h * itsTrussPane->theStructureScale / SCREEN_DPI ),
      dForm, 0.0, MAXREAL);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GenericNodeEditTextYLocation,
    (itsCenterPoint.v  * itsTrussPane->theStructureScale / SCREEN_DPI ),
      dForm, 0.0, MAXREAL); /* should be limit of drawing area*/

  if ( IamConnected )
  {
    dForm.digits = 2;
    dForm.style = FIXEDDECIMAL;
    DHAdvAddEditReal(dhp, GenericNodeTEConnectionRatio,
      (TElementConnectionRatio ),
        dForm, 0.0, 1.0);
  }

  DHAddRadioSet(dhp, itsBoundaryCondition, &set1);
  DHAdvAddRadioButtonToSet(&set1, GenericNodeFree,
                  DHNoKeyEquiv(), NULL);
  DHAdvAddRadioButtonToSet(&set1, GenericNodeRotationFixed, DHNoKeyEquiv(),
                   NULL);
  DHAdvAddRadioButtonToSet(&set1, GenericNodeXTranslationFixed, DHNoKeyEquiv(),
                   NULL);
  DHAdvAddRadioButtonToSet(&set1, GenericNodeYTranslationFixed,
                  DHNoKeyEquiv(), NULL);
  DHAdvAddRadioButtonToSet(&set1, GenericNodeXYTranslationFixed,
                  DHNoKeyEquiv(), NULL);
  DHAdvAddRadioButtonToSet(&set1, GenericNodeXYTranslationAndRotationFixed,
                  DHNoKeyEquiv(), NULL);
  DHAdvAddRadioButtonToSet(&set1, GenericNodeXTranslationAndRotationFixed,
                  DHNoKeyEquiv(), NULL);
  DHAdvAddRadioButtonToSet(&set1, GenericNodeYTranslationAndRotationFixed,
                  DHNoKeyEquiv(), NULL);



  if (DHDialogHandler(dhp))
  {
    newBoundaryCondition = DHWhichRadioButtonIsSet(set1);
    xLocation = DHGetEditReal(dhp, GenericNodeEditTextXLocation);
    yLocation = DHGetEditReal(dhp, GenericNodeEditTextYLocation);
    if( IamConnected )
      newTElementConnectionRatio =
          DHGetEditReal(dhp, GenericNodeTEConnectionRatio);


    if( newBoundaryCondition != itsBoundaryCondition)
    {
      itsBoundaryCondition = newBoundaryCondition;
      switch( newBoundaryCondition )
      {
        case Free:
          /*do nothing */
          break;

        case RotationFixed:
          /*ReleaseResource( pHandle ); */
          pHandle = GetPicture( PICT_BASE_ID + RotationFixed);
          break;

        case xTranslationFixed:
          /*ReleaseResource( pHandle ); */
          pHandle = GetPicture( PICT_BASE_ID +
            xTranslationFixed);
          break;

        case yTranslationFixed:
          /*ReleaseResource( pHandle ); */
          pHandle = GetPicture( PICT_BASE_ID +
            yTranslationFixed);
          break;

        case xyTranslationFixed:
          /*ReleaseResource( pHandle ); */
          pHandle = GetPicture( PICT_BASE_ID +
            xyTranslationFixed);
          break;

        case xyTranslationAndRotationFixed:
          /*ReleaseResource( pHandle ); */
          pHandle = GetPicture( PICT_BASE_ID +
            xyTranslationAndRotationFixed);
          break;

        case xTranslationAndRotationFixed:
          /*ReleaseResource( pHandle ); */
          pHandle = GetPicture( PICT_BASE_ID +
            xTranslationAndRotationFixed);
          break;

        case yTranslationAndRotationFixed:
          /*ReleaseResource( pHandle ); */
          pHandle = GetPicture( PICT_BASE_ID +
            yTranslationAndRotationFixed);
          break;

      }
      DrawFinal();
    }


    if( xLocation !=
      (itsCenterPoint.h  * itsTrussPane->theStructureScale /
      SCREEN_DPI ) )
    {
      if ( ! IamConnected )
      {
        UnSelectYourself();
        Erase();
        itsCenterPoint.h = (int)(xLocation /
          itsTrussPane->theStructureScale *
          SCREEN_DPI );
        DrawFinal();
        theNodeTElements->DoForEach(  Perform_Draw );
        theNodeLoads->DoForEach( Perform_Draw );
      }
    }
    if( yLocation !=
      (itsCenterPoint.v  * itsTrussPane->theStructureScale /
      SCREEN_DPI ) )
    {
      if ( ! IamConnected )
      {
        UnSelectYourself();
        Erase();
        itsCenterPoint.v = (int)(yLocation /
          itsTrussPane->theStructureScale *
          SCREEN_DPI );
        DrawFinal();
        theNodeTElements->DoForEach(  Perform_Draw );
        theNodeLoads->DoForEach( Perform_Draw );
      }
    }

    if(  IamConnected )
    {
      if ( newTElementConnectionRatio != TElementConnectionRatio  )
      {
        UnSelectYourself();
        Erase();

        TElementConnectionRatio = newTElementConnectionRatio;
        itsMotherTElement->DrawFinal();
        theNodeTElements->DoForEach(  Perform_Draw );
        theNodeLoads->DoForEach( Perform_Draw );
      }
    }
  }

  DHDeallocateRecord(dhp);
}


void CNodeObject::PrepareYourselfToBeUpdated( void )
{
  Point    TE1stEnd, TE2ndEnd;
  Point    connectToThisPoint;

  TE1stEnd.h = itsMotherTElement->its1stEnd.h;
  TE1stEnd.v = itsMotherTElement->its1stEnd.v;
  TE2ndEnd.h = itsMotherTElement->its2ndEnd.h;
  TE2ndEnd.v = itsMotherTElement->its2ndEnd.v;

  connectToThisPoint.h = ((int)((( float)(TE2ndEnd.h -TE1stEnd.h))
          *TElementConnectionRatio)) + TE1stEnd.h;
  connectToThisPoint.v = ((int)((( float)(TE2ndEnd.v -TE1stEnd.v))
          *TElementConnectionRatio)) + TE1stEnd.v;

  itsCenterPoint.h = connectToThisPoint.h;
  itsCenterPoint.v = connectToThisPoint.v;
}

Boolean CNodeObject::ConnectYourselfToTE(  CTrussElementObject
                          *theSelectedTEObject )
{
  if( (! this->IamConnected ) &&
    ( this != theSelectedTEObject->the1stEndNode ) &&
    ( this != theSelectedTEObject->the2ndEndNode ) )
  {
    this->SelectYourself();
    theSelectedTEObject->AddToItsNodesCluster(
                      this);
    this->itsMotherTElement = theSelectedTEObject;
    this->UnSelectYourself();
    theSelectedTEObject->SelectYourself();
    itsTrussPane->theObject = theSelectedTEObject;
    IamConnected = TRUE;
    return TRUE;
  }else
  {
    return FALSE;
  }
}

        static void Disconnect_ConLandM( CConcLoadObject
            *theObject, HitPtAndObjectPtr *theHitPtAndObjectPtr)
        {
          if ( theObject->the1stEndNode ==
            theHitPtAndObjectPtr->thisObjectPointer)
          {
            theObject->the1stEndConnected = FALSE;
            theObject->the1stEndNode = NULL;
          }
          else
          if ( theObject->the2ndEndNode ==
            theHitPtAndObjectPtr->thisObjectPointer)
          {
            theObject->the2ndEndConnected = FALSE;
            theObject->the2ndEndNode = NULL;
          }
          if ( ( theObject->the2ndEndConnected == FALSE ) &&
                ( theObject->the1stEndConnected == FALSE ) )
                theObject->IamConnected = FALSE;
        }

        static void Disconnect_TElements( CTrussElementObject
            *theObject, HitPtAndObjectPtr *theHitPtAndObjectPtr)
        {
          if ( theObject->the1stEndNode ==
            theHitPtAndObjectPtr->thisObjectPointer)
          {
            theObject->the1stEndConnected = FALSE;
            theObject->the1stEndNode = NULL;
          }
          else
          if ( theObject->the2ndEndNode ==
            theHitPtAndObjectPtr->thisObjectPointer)
          {
            theObject->the2ndEndConnected = FALSE;
            theObject->the2ndEndNode = NULL;
          }

          if ( ( theObject->the2ndEndConnected == FALSE ) &&
                ( theObject->the1stEndConnected == FALSE ) )
                theObject->IamConnected = FALSE;
        }

void CNodeObject::DisconnectYourself( void )
{
  HitPtAndObjectPtr  theHitPtAndObjectPtr;
  Boolean        DisconnectionOK = FALSE;

  theHitPtAndObjectPtr.thisObjectPointer = this;
  theHitPtAndObjectPtr.thisHitPoint.v = itsCenterPoint.v;
  theHitPtAndObjectPtr.thisHitPoint.h = itsCenterPoint.h;

  if( IamConnected )  /* i.e IamConnected to truss element*/
  {
    UnSelectYourself();
    Erase();
    IamConnected = FALSE;
    DisconnectionOK = TRUE;
    if( itsMotherTElement)  /* Node connected to truss element*/
    {
      itsMotherTElement->theTENodes->Remove( this );
      itsMotherTElement->DrawFinal();
      itsMotherTElement = NULL;
    }
  }
  else
  {
    if( ConcLandMAreConnected )
    {
      theNodeLoads->DoForEach1(
        Disconnect_ConLandM, (long)(&theHitPtAndObjectPtr) );
      UnSelectYourself();
      Erase();
      IamConnected = FALSE;
      DisconnectionOK = TRUE;
      ConcLandMAreConnected = FALSE;
      theNodeLoads->DoForEach( Perform_Draw );
      theNodeLoads->ICluster();
    }
    if ( TElementsAreConnected )
    {
      theNodeTElements->DoForEach1(
        Disconnect_TElements, (long)(&theHitPtAndObjectPtr) );
      UnSelectYourself();
      Erase();
      IamConnected = FALSE;
      DisconnectionOK = TRUE;
      TElementsAreConnected = FALSE;
      theNodeTElements->DoForEach(  Perform_Draw );
      theNodeTElements->ICluster();
    }
  }
  if( DisconnectionOK )
  {
    theHitPoint.h = itsCenterPoint.h + SMALL_LENGTH;
    theHitPoint.v = itsCenterPoint.v - SMALL_LENGTH;
    offSet.h = 0;
    offSet.v = 0;
    ReSizingInProgress = FALSE;
    UpDateObject();
    DrawFinal();
    SelectYourself();
  }
}
void CNodeObject::DeleteYourself( void )
{
  Rect  aRect;

  DisconnectYourself();
  DisconnectYourself();
  UnSelectYourself();
  Erase();
  itsTrussPane->NodesCluster->Remove( this );
  itsTrussPane->Draw( &aRect );
  itsTrussPane->theObject = NULL;
  Dispose();
}

void  CNodeObject::PrintDebugInfo( void )
{
}
void  CNodeObject::PrintFileStatics( void )
{
}
void  CNodeObject::PrintFileFireWood( void )
{
}

void  CNodeObject::PrintFileWood1( void )
{
}
void  CNodeObject::PrintFileWood2( void )
{
}
void  CNodeObject::PrintFileWood3( void )
{
}
void  CNodeObject::PrintFileWood4( void )
{
}
void  CNodeObject::PrintFileWood5( void )
{
}


void  CNodeObject::KillYourself_IF_NOT_Connected( void )
{
  if( ! IamConnected )
  {
    if( TElementsAreConnected )
    {
      if( theNodeTElements->numItems == 0 )
      {
        DeleteYourself();
      }
    }
    else
      DeleteYourself();
  }
}

void  CNodeObject::SaveYourself( void )
{
}
void  CNodeObject::LoadYourself( void )
{
}
  static void Perform_TE_Numbering( CTrussElementObject
      *theObject, NodeAndGlobNumber  *myStructure)
  {
    short    whichEndConnected;

    whichEndConnected = theObject->WhichEndIsConnected(
                        ( myStructure->theNode ));

    if( whichEndConnected == 1 )
    {
      (myStructure->theGlobalNumber)++;
      theObject->its1stEndGlobalNumber = (myStructure->theGlobalNumber);
    }
    else if ( whichEndConnected == 2 )
    {
      (myStructure->theGlobalNumber)++;
      theObject->its2ndEndGlobalNumber = (myStructure->theGlobalNumber);
    }

  }

void CNodeObject::PerformGlobalNumbering( long  *theGlobalNumberPtr )
{
  NodeAndGlobNumber  myStructure;

  (*theGlobalNumberPtr)++;
     itsGlobalNumber = (*theGlobalNumberPtr);
  myStructure.theNode = this;
  myStructure.theGlobalNumber = (*theGlobalNumberPtr);
     if ( TElementsAreConnected )
     {
        theNodeTElements->DoForEach1(
             Perform_TE_Numbering, (long)(&myStructure) );
     }
     (*theGlobalNumberPtr)  = myStructure.theGlobalNumber;

}


void CNodeObject::InitializeGlobalNumbers( void )
{
  itsGlobalNumber = 0L;
  theObjectNumber = 0L;
}

