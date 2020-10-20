/****
 * CGussetPlate.c
 *
 *  CGenericNode object class for a typical CTrussPane class
 *
 ****/
#include "CGussetPlate.phs"
#include "CGussetPlate.h"

/*** Global Variables ***/

extern  CBartender     *gBartender;
extern   short      gClicks;
extern  CApplication   *gApplication;  /* The application */

extern  FILE      *Debug_Info_Out_File;
extern  FILE      *Wood_Out_File;
extern  long      NumberOfPlateSprings;



void  CGussetPlate::InitializeYourself( void )
{
  inherited::InitializeYourself();

  itsBoundaryCondition = Free;

  plateLength = 4.0;
  plateHeight = 3.0;
  alpha = 0.5;
  gamma = 0.5;
  itsAngle = 0.0;
  noOfTeethPerInch = 8;

  itsDocument = new( CGussetPDoc );
  itsDocument->IGussetPDoc( gApplication, TRUE );
  itsDocument->itsGussetPlate = this;
  itsDocument->NewFile();
  (( CGussetPane *)(itsDocument->itsMainPane))->TElementsCluster = theNodeTElements;
  (( CGussetPane *)(itsDocument->itsMainPane))->itsGussetPlate = this;
  (( CGussetPane *)(itsDocument->itsMainPane))->itsMotherTElement = this->itsMotherTElement;

  bottomLeftHOffset = -plateLength/2;
  bottomLeftVOffset = plateHeight/2;

  bottomLeftCorner.v = 0.0;
  bottomLeftCorner.h = 0.0;
  bottomRightCorner.v = 0.0;
  bottomRightCorner.h = plateLength;
  topRightCorner.v =  -plateHeight;
  topRightCorner.h =  plateLength;
  topLeftCorner.v =  -plateHeight;
  topLeftCorner.h = 0.0;

  masterPlateLocation.v = -plateHeight/2;
  masterPlateLocation.h = plateLength/2;

  itsOwnAngleFlag = FALSE;
  itsMotherTEPolyPointCounter = 0;
  itsMotherTEConnectorArea = 0.0;
  itsMotherTEIxx = 0.0;
  itsMotherTEIyy = 0.0;
  itsMotherTECentroid.h = 0.0;
  itsMotherTECentroid.v = 0.0;

      /* foschi numbers matrix */
  foschiNumbers[ 1 ][ 1 ] = 18829.2;
  foschiNumbers[ 2 ][ 1 ] =  7234.8;
  foschiNumbers[ 3 ][ 1 ] = 16679.7;
  foschiNumbers[ 4 ][ 1 ] =  8713.2;
  foschiNumbers[ 1 ][ 2 ] =   103.4;
  foschiNumbers[ 2 ][ 2 ] =    58.8;
  foschiNumbers[ 3 ][ 2 ] =   111.0;
  foschiNumbers[ 4 ][ 2 ] =   103.6;
  foschiNumbers[ 1 ][ 3 ] =     0.0;
  foschiNumbers[ 2 ][ 3 ] =     0.0;
  foschiNumbers[ 3 ][ 3 ] =     0.0;
  foschiNumbers[ 4 ][ 3 ] =     0.0;

  itsGlobalNumber = 0L;
  itsMotherTEGlobalNumber = 0L;
  itsMotherTEBCIsSet = FALSE;
  itsMotherTE_InheritsPlateLoads = FALSE;


}

void CGussetPlate::AddPicture( void )
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


void CGussetPlate::DoDrawing( void )

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



  FrameRect( &myRect2 );


  GetPenState ( &pnState);  /* to save the pen setting */
  PenPat ( ltGray );
  PaintRect( &myRect1 );
  SetPenState ( &pnState);  /* to resotre pen settting */

}


void CGussetPlate::DrawNodeOnly( void )
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




  FrameRect( &myRect2 );


  GetPenState ( &pnState);  /* to save the pen setting */
  PenPat ( ltGray );
  PaintRect( &myRect1 );
  SetPenState ( &pnState);  /* to resotre pen settting */

}

    static void Perform_Draw( CAbstractObject
        *theObject)
    {
        theObject->DrawFinal();
    }

    static void  DoConnectionDesignDialogHook(DialogPtr dp,
        short  itemHit, DialogHandlerRecordPtr dhp)
    {
      CGussetPlate  *aPlateObject;

      aPlateObject = ( CGussetPlate  *)dhp->progItem1;
      /*aPlateObject->DoPlateDesignDialog();*/
      aPlateObject->DoPlateDesignGraphically();
    }
    static void  DoPlateDesignDialogHook(DialogPtr dp,
        short  itemHit, DialogHandlerRecordPtr dhp)
    {
      CGussetPlate  *aPlateObject;

      aPlateObject = ( CGussetPlate  *)dhp->progItem1;
      aPlateObject->DoPlateDesignDialog();
      /*aPlateObject->DoPlateDesignGraphically();*/
    }
    static void  DoFoschiNumDialogHook(DialogPtr dp,
        short  itemHit, DialogHandlerRecordPtr dhp)
    {
      CGussetPlate  *aPlateObject;

      aPlateObject = ( CGussetPlate  *)dhp->progItem1;
      aPlateObject->DoFoshiNumDialog();
    }


    static void Apply_Length( CGussetPlate
        *theObject, CGussetPlate **thisObjectPtr)
    {
      if( ((theObject->WhoAreYou() == aGussetPlate ) ||
        (theObject->WhoAreYou() == aTBGussetPlate)) )
      {
        theObject->plateLength =
            (*thisObjectPtr)->plateLength;
        theObject->bottomRightCorner.h =
          theObject->bottomLeftCorner.h + theObject->plateLength;
        theObject->topRightCorner.h =
          theObject->topLeftCorner.h + theObject->plateLength;
      }
    }
    static void Apply_Height( CGussetPlate
        *theObject, CGussetPlate **thisObjectPtr)
    {
      if( ((theObject->WhoAreYou() == aGussetPlate ) ||
        (theObject->WhoAreYou() == aTBGussetPlate)) )
      {
        theObject->plateHeight =
          (*thisObjectPtr)->plateHeight;
        theObject->topRightCorner.v =
          theObject->bottomRightCorner.v - theObject->plateHeight;
        theObject->topLeftCorner.v =
          theObject->bottomLeftCorner.v - theObject->plateHeight;
      }
    }
    static void Apply_ALPHA( CGussetPlate
        *theObject, CGussetPlate **thisObjectPtr)
    {
      if( ((theObject->WhoAreYou() == aGussetPlate ) ||
        (theObject->WhoAreYou() == aTBGussetPlate)) )
      {
        theObject->alpha =
          (*thisObjectPtr)->alpha;
        theObject->masterPlateLocation.h =
          (theObject->alpha*theObject->plateLength +
                    theObject->bottomLeftCorner.h);
      }
    }
    static void Apply_GAMMA( CGussetPlate
        *theObject, CGussetPlate **thisObjectPtr)
    {
      if( ((theObject->WhoAreYou() == aGussetPlate ) ||
        (theObject->WhoAreYou() == aTBGussetPlate)) )
      {
        theObject->gamma =
             (*thisObjectPtr)->gamma;
        theObject->masterPlateLocation.v =
          (theObject->bottomLeftCorner.v -
                theObject->gamma*theObject->plateHeight);
      }
    }
    static void Apply_PlateAngle( CGussetPlate
        *theObject, CGussetPlate **thisObjectPtr)
    {
      if( ((theObject->WhoAreYou() == aGussetPlate ) ||
        (theObject->WhoAreYou() == aTBGussetPlate)) )
        theObject->itsAngle =
             (*thisObjectPtr)->itsAngle;
    }
    static void Apply_NoOfTeethPerInchSq( CGussetPlate
        *theObject, CGussetPlate **thisObjectPtr)
    {
      if( ((theObject->WhoAreYou() == aGussetPlate ) ||
        (theObject->WhoAreYou() == aTBGussetPlate)) )
        theObject->noOfTeethPerInch =
             (*thisObjectPtr)->noOfTeethPerInch;
    }

    static void Update_itsGussetPlate( CRegularWoodTElement
        *theObject, CGussetPlate **thisObjectPtr)
    {
      theObject->itsGussetPlate = (*thisObjectPtr);
    }
    static void Add_ObjectsToList( CRegularWoodTElement
        *theObject, CGussetPlate **thisObjectPtr)
    {
      (( CGussetPane *)(
        (*thisObjectPtr)->
        itsDocument->
        itsMainPane))->
        theListOfObjects->Append( theObject );
    }

/*
  static void Update_WoodOffsets( CRegularWoodTElement *theObject, WoodElementAndPlate
                              *theWoodAndPlate)
  {
    CRegularWoodTElement    *theOriginalWoodMember;
    CGussetPlate        *thePlate;

    FloatPoint      its1stEnd;
    FloatPoint      its2ndEnd;
    double        its1stEndHorz;
    double        its1stEndVert;
    double        its2ndEndHorz;
    double        its2ndEndVert;
    Point        itsCenterPoint;
    FloatPoint      tempCenter;
    FloatPoint      oldCenter;
    double        scalingFactor;
    short          whichEndConnected;

    thePlate = (*theWoodAndPlate).thePlate;
    theOriginalWoodMember = (*theWoodAndPlate).theWoodElement;


    scalingFactor = (double)( SCREEN_DPI / ((( CGussetPane *)(thePlate->
          itsDocument->itsMainPane))->
                    theStructureScale));

    scalingFactor = (double)(SCREEN_DPI / (theOriginalWoodMember->itsTrussPane->theStructureScale));

    its1stEnd.v = ((float)(((double)(theOriginalWoodMember->its1stEnd.v)) + ((double)theOriginalWoodMember->its1stEndVOffset * scalingFactor)));
    its1stEnd.h = ((float)(((double)(theOriginalWoodMember->its1stEnd.h)) + ((double)theOriginalWoodMember->its1stEndHOffset * scalingFactor)));
    its2ndEnd.v = ((float)(((double)(theOriginalWoodMember->its2ndEnd.v)) + ((double)theOriginalWoodMember->its2ndEndVOffset * scalingFactor)));
    its2ndEnd.h = ((float)(((double)(theOriginalWoodMember->its2ndEnd.h)) + ((double)theOriginalWoodMember->its2ndEndHOffset * scalingFactor)));


    its1stEndHorz = ((double)its1stEnd.h * (double)theOriginalWoodMember->itsTrussPane->theStructureScale / SCREEN_DPI );
    its1stEndVert = ((double)its1stEnd.v * (double)theOriginalWoodMember->itsTrussPane->theStructureScale / SCREEN_DPI );
    its2ndEndHorz = ((double)its2ndEnd.h * (double)theOriginalWoodMember->itsTrussPane->theStructureScale / SCREEN_DPI );
    its2ndEndVert = ((double)its2ndEnd.v * (double)theOriginalWoodMember->itsTrussPane->theStructureScale / SCREEN_DPI );



    tempCenter.h = (float)((( (double)thePlate->TElementConnectionRatio *
            ((double)its2ndEndHorz -  (double)its1stEndHorz ) ) +  (double)its1stEndHorz ));
    tempCenter.v = (float)((( (double)thePlate->TElementConnectionRatio *
            ((double)its2ndEndVert -  (double)its1stEndVert ) ) +  (double)its1stEndVert ));

    itsCenterPoint.h = ((int)((tempCenter.h) * SCREEN_DPI / theOriginalWoodMember->itsTrussPane->theStructureScale));
    itsCenterPoint.v = ((int)((tempCenter.v) * SCREEN_DPI / theOriginalWoodMember->itsTrussPane->theStructureScale));


    oldCenter.h = ((float)(thePlate->itsCenterPoint.h)) / (float)scalingFactor;
    oldCenter.v = ((float)(thePlate->itsCenterPoint.v)) / (float)scalingFactor;


    whichEndConnected = theObject->WhichEndIsConnected( thePlate );

    if( whichEndConnected == 1 )
    {
      theObject->its1stEndHOffset =  theObject->its1stEndHOffset - theObject->firstEndcenterPointsHOffset;
      theObject->its1stEndVOffset =  theObject->its1stEndVOffset - theObject->firstEndcenterPointsVOffset;
      theObject->its1stEndHOffset =  theObject->its1stEndHOffset + (((float)(tempCenter.h - oldCenter.h)));
      theObject->its1stEndVOffset =  theObject->its1stEndVOffset + (((float)(tempCenter.v - oldCenter.v)));
      theObject->firstEndcenterPointsHOffset = (((float)(tempCenter.h - oldCenter.h)));
      theObject->firstEndcenterPointsVOffset = (((float)(tempCenter.v - oldCenter.v)));
    }
    else if ( whichEndConnected == 2 )
    {
      theObject->its1stEndHOffset =  theObject->its2ndEndHOffset - theObject->secondEndcenterPointsHOffset;
      theObject->its1stEndVOffset =  theObject->its2ndEndVOffset - theObject->secondEndcenterPointsVOffset;
      theObject->its2ndEndHOffset = theObject->its2ndEndHOffset + (((float)(tempCenter.h - oldCenter.h)));
      theObject->its2ndEndVOffset = theObject->its2ndEndVOffset + (((float)(tempCenter.v - oldCenter.v)));
      theObject->secondEndcenterPointsHOffset = (((float)(tempCenter.h - oldCenter.h)));
      theObject->secondEndcenterPointsVOffset = (((float)(tempCenter.v - oldCenter.v)));
    }

  }
*/
  static void Update_WoodOffsets( CRegularWoodTElement *theObject, WoodElementAndPlate
                              *theWoodAndPlate)
  {
    CRegularWoodTElement    *theOriginalWoodMember;
    CGussetPlate        *thePlate;

    FloatPoint      its1stEnd;
    FloatPoint      its2ndEnd;
    float        its1stEndHorz;
    float        its1stEndVert;
    float        its2ndEndHorz;
    float        its2ndEndVert;
    Point        itsCenterPoint;
    FloatPoint      tempCenter;
    FloatPoint      oldCenter;
    float        scalingFactor;
    short          whichEndConnected;

    thePlate = (*theWoodAndPlate).thePlate;
    theOriginalWoodMember = (*theWoodAndPlate).theWoodElement;


    scalingFactor = SCREEN_DPI / ((( CGussetPane *)(thePlate->
          itsDocument->itsMainPane))->
                    theStructureScale);

    scalingFactor = SCREEN_DPI / (theOriginalWoodMember->itsTrussPane->theStructureScale);

    its1stEnd.v = ((float)(theOriginalWoodMember->its1stEnd.v)) + (theOriginalWoodMember->its1stEndVOffset * scalingFactor);
    its1stEnd.h = ((float)(theOriginalWoodMember->its1stEnd.h)) + (theOriginalWoodMember->its1stEndHOffset * scalingFactor);
    its2ndEnd.v = ((float)(theOriginalWoodMember->its2ndEnd.v)) + (theOriginalWoodMember->its2ndEndVOffset * scalingFactor);
    its2ndEnd.h = ((float)(theOriginalWoodMember->its2ndEnd.h)) + (theOriginalWoodMember->its2ndEndHOffset * scalingFactor);


    its1stEndHorz = (its1stEnd.h * theOriginalWoodMember->itsTrussPane->theStructureScale / SCREEN_DPI );
    its1stEndVert = (its1stEnd.v * theOriginalWoodMember->itsTrussPane->theStructureScale / SCREEN_DPI );
    its2ndEndHorz = (its2ndEnd.h * theOriginalWoodMember->itsTrussPane->theStructureScale / SCREEN_DPI );
    its2ndEndVert = (its2ndEnd.v * theOriginalWoodMember->itsTrussPane->theStructureScale / SCREEN_DPI );


    tempCenter.h = ((( thePlate->TElementConnectionRatio *
            (its2ndEndHorz -  its1stEndHorz ) ) +  its1stEndHorz ));
    tempCenter.v = ((( thePlate->TElementConnectionRatio *
            (its2ndEndVert -  its1stEndVert ) ) +  its1stEndVert ));

    itsCenterPoint.h = ((int)((tempCenter.h) * SCREEN_DPI / theOriginalWoodMember->itsTrussPane->theStructureScale));
    itsCenterPoint.v = ((int)((tempCenter.v) * SCREEN_DPI / theOriginalWoodMember->itsTrussPane->theStructureScale));

    oldCenter.h = ((float)(thePlate->itsCenterPoint.h)) / scalingFactor;
    oldCenter.v = ((float)(thePlate->itsCenterPoint.v)) / scalingFactor;


    whichEndConnected = theObject->WhichEndIsConnected( thePlate );

    if( whichEndConnected == 1 )
    {
      theObject->its1stEndHOffset =  theObject->its1stEndHOffset - theObject->firstEndcenterPointsHOffset;
      theObject->its1stEndVOffset =  theObject->its1stEndVOffset - theObject->firstEndcenterPointsVOffset;
      theObject->its1stEndHOffset =  theObject->its1stEndHOffset + (((float)(tempCenter.h - oldCenter.h)));
      theObject->its1stEndVOffset =  theObject->its1stEndVOffset + (((float)(tempCenter.v - oldCenter.v)));
      theObject->firstEndcenterPointsHOffset = (((float)(tempCenter.h - oldCenter.h)));
      theObject->firstEndcenterPointsVOffset = (((float)(tempCenter.v - oldCenter.v)));
    }
    else if ( whichEndConnected == 2 )
    {
      theObject->its2ndEndHOffset =  theObject->its2ndEndHOffset - theObject->secondEndcenterPointsHOffset;
      theObject->its2ndEndVOffset =  theObject->its2ndEndVOffset - theObject->secondEndcenterPointsVOffset;
      theObject->its2ndEndHOffset = theObject->its2ndEndHOffset + (((float)(tempCenter.h - oldCenter.h)));
      theObject->its2ndEndVOffset = theObject->its2ndEndVOffset + (((float)(tempCenter.v - oldCenter.v)));
      theObject->secondEndcenterPointsHOffset = (((float)(tempCenter.h - oldCenter.h)));
      theObject->secondEndcenterPointsVOffset = (((float)(tempCenter.v - oldCenter.v)));
    }

  }






void  CGussetPlate::DoPlateDesignGraphically( void )
{
  Point          aNicePosition;
  short          theHSpan, theVSpan;
  CGussetPlate      *thisObject;
  Rect          boundRect;
  Rect          deltaRect;
  long          theHExtent, theVExtent;
  Str255    wTitle;          /* Window title string        */
  short    wCount;          /* Index number of new window    */
  Str63    wNumber;        /* Index number as a string      */

  float        scalingFactor;
  FloatPoint      its1stEnd;
  FloatPoint      its2ndEnd;
  float        its1stEndHorz;
  float        its1stEndVert;
  float        its2ndEndHorz;
  float        its2ndEndVert;
  Point        itsCenterPoint;
  FloatPoint      tempCenter;

  FloatPoint      masterPlateLocation;
  FloatPoint      bottomLeftTEMP;

  Point        masterPlateLocationPoint;
  Point        bottomLeftTEMPpoint;
  Point        tempPoint;

  WoodElementAndPlate    thePlateAndWoodMember;


  if( itsMotherTElement )
  {
    scalingFactor = SCREEN_DPI / (itsTrussPane->theStructureScale);

    scalingFactor = SCREEN_DPI / ((( CGussetPane *)(this->
          itsDocument->itsMainPane))->
                    theStructureScale);

    its1stEnd.v = ((float)itsMotherTElement->its1stEnd.v) +
      (((CRegularWoodTElement *)itsMotherTElement)->its1stEndVOffset * scalingFactor);
    its1stEnd.h = ((float)itsMotherTElement->its1stEnd.h) +
      (((CRegularWoodTElement *)itsMotherTElement)->its1stEndHOffset * scalingFactor);
    its2ndEnd.v = ((float)itsMotherTElement->its2ndEnd.v) +
      (((CRegularWoodTElement *)itsMotherTElement)->its2ndEndVOffset * scalingFactor);
    its2ndEnd.h = ((float)itsMotherTElement->its2ndEnd.h) +
      (((CRegularWoodTElement *)itsMotherTElement)->its2ndEndHOffset * scalingFactor);


    its1stEndHorz = (its1stEnd.h * itsTrussPane->theStructureScale / SCREEN_DPI );
    its1stEndVert = (its1stEnd.v * itsTrussPane->theStructureScale / SCREEN_DPI );
    its2ndEndHorz = (its2ndEnd.h * itsTrussPane->theStructureScale / SCREEN_DPI );
    its2ndEndVert = (its2ndEnd.v * itsTrussPane->theStructureScale / SCREEN_DPI );


    tempCenter.h = ((( TElementConnectionRatio *
            (its2ndEndHorz -  its1stEndHorz ) ) +  its1stEndHorz ));
    tempCenter.v = ((( TElementConnectionRatio *
            (its2ndEndVert -  its1stEndVert ) ) +  its1stEndVert ));

    itsCenterPoint.h = ((int)((tempCenter.h) * SCREEN_DPI / itsTrussPane->theStructureScale));
    itsCenterPoint.v = ((int)((tempCenter.v) * SCREEN_DPI / itsTrussPane->theStructureScale));


  }
  else
  {
    itsCenterPoint = this->itsCenterPoint;
  }

  scalingFactor = SCREEN_DPI / ((( CGussetPane *)(this->
        itsDocument->itsMainPane))->
                  theStructureScale);

  scalingFactor = SCREEN_DPI / (itsTrussPane->theStructureScale);

  masterPlateLocation.v = masterPlateLocation.v * scalingFactor;
  masterPlateLocation.h = masterPlateLocation.h * scalingFactor;

  bottomLeftTEMP.h = bottomLeftHOffset * scalingFactor;
  bottomLeftTEMP.v = bottomLeftVOffset * scalingFactor;


  bottomLeftTEMPpoint = TransformTElementToPano( bottomLeftTEMP,
                itsCenterPoint);

  masterPlateLocationPoint = TransformTElementToPano( masterPlateLocation,
                 bottomLeftTEMPpoint);


  thisObject = this;

  (( CGussetPane *)(itsDocument->itsMainPane))->
              theListOfObjects->IList();

  wTitle[0] = 11;            /* char. count*/
  wTitle[1] = 'G';
  wTitle[2] = 'u';
  wTitle[3] = 's';
  wTitle[4] = 's';          /* quick and dirty way of doing it*/
  wTitle[5] = 'e';
  wTitle[6] = 't';
  wTitle[7] = 'P';
  wTitle[8] = 'l';
  wTitle[9] = 'a';
  wTitle[10] = 't';
  wTitle[11] = 'e';
  NumToString((long)(theObjectNumber), wNumber);
  ConcatPStrings(wTitle, (StringPtr) "\p-");
  ConcatPStrings(wTitle, wNumber);
  itsDocument->itsWindow->SetTitle(wTitle);/* Make it the active window*/

  if( itsMotherTElement )
  {
    (( CGussetPane *)(itsDocument->itsMainPane))->itsMotherTElement =
              this->itsMotherTElement;
    ((CRegularWoodTElement *)((( CGussetPane *)(itsDocument->itsMainPane))->
          itsMotherTElement))->itsGussetPlate = thisObject;
    (( CGussetPane *)(itsDocument->itsMainPane))->theListOfObjects->
        Append( itsMotherTElement );
  }
  else
  {
    (( CGussetPane *)(itsDocument->itsMainPane))->itsMotherTElement = NULL;
  }

  (( CGussetPane *)(itsDocument->itsMainPane))->
              GetExtent( &theHExtent, &theVExtent );

/*  boundRect.top = itsCenterPoint.v - (int)( theVExtent/2 );
  boundRect.left = itsCenterPoint.h - (int)( theHExtent/2 );
  boundRect.bottom = itsCenterPoint.v + (int)( theVExtent/2 );
  boundRect.right = itsCenterPoint.h + (int)( theHExtent/2 );
*/
  boundRect.top = masterPlateLocationPoint.v - (int)( theVExtent/2 );
  boundRect.left = masterPlateLocationPoint.h - (int)( theHExtent/2 );
  boundRect.bottom = masterPlateLocationPoint.v + (int)( theVExtent/2 );
  boundRect.right = masterPlateLocationPoint.h + (int)( theHExtent/2 );


  (( CGussetPane *)(itsDocument->itsMainPane))->
              SetBounds( &boundRect );


  (( CGussetPane *)(itsDocument->itsMainPane))->
              GetFrameSpan( &theHSpan,&theVSpan );
  aNicePosition.h = itsCenterPoint.h - theHSpan/2;
  aNicePosition.v = itsCenterPoint.v - theVSpan/2;
  (( CGussetPane *)(itsDocument->itsMainPane))->
              ScrollTo( aNicePosition, TRUE );
  theNodeTElements->DoForEach1( Update_itsGussetPlate, (long)(&thisObject) );
  theNodeTElements->DoForEach1( Add_ObjectsToList, (long)(&thisObject) );

  (( CGussetPane *)(itsDocument->itsMainPane))->theListOfObjects->
        Append( thisObject );

  if( itsMotherTElement )
  {

    thePlateAndWoodMember.thePlate = thisObject;
    thePlateAndWoodMember.theWoodElement = (CRegularWoodTElement *)itsMotherTElement;

    if ( theNodeTElements && theNodeTElements->numItems )
    {
      theNodeTElements->DoForEach1( Update_WoodOffsets, (long)(&thePlateAndWoodMember) );
      }

  }
  itsDocument->itsWindow->Select();
}

    static void Apply_FoschiNum( CGussetPlate
        *theObject, CGussetPlate **thisObjectPtr)
    {
      if( ((theObject->WhoAreYou() == aGussetPlate ) ||
        (theObject->WhoAreYou() == aTBGussetPlate)) )
      {
        theObject->foschiNumbers[ 1 ][ 1 ] =
            (*thisObjectPtr)->foschiNumbers[ 1 ][ 1 ];
        theObject->foschiNumbers[ 2 ][ 1 ] =
            (*thisObjectPtr)->foschiNumbers[ 2 ][ 1 ];
        theObject->foschiNumbers[ 3 ][ 1 ] =
            (*thisObjectPtr)->foschiNumbers[ 3 ][ 1 ];
        theObject->foschiNumbers[ 4 ][ 1 ] =
            (*thisObjectPtr)->foschiNumbers[ 4 ][ 1 ];
        theObject->foschiNumbers[ 1 ][ 2 ] =
            (*thisObjectPtr)->foschiNumbers[ 1 ][ 2 ];
        theObject->foschiNumbers[ 2 ][ 2 ] =
            (*thisObjectPtr)->foschiNumbers[ 2 ][ 2 ];
        theObject->foschiNumbers[ 3 ][ 2 ] =
            (*thisObjectPtr)->foschiNumbers[ 3 ][ 2 ];
        theObject->foschiNumbers[ 4 ][ 2 ] =
            (*thisObjectPtr)->foschiNumbers[ 4 ][ 2 ];
        theObject->foschiNumbers[ 1 ][ 3 ] =
            (*thisObjectPtr)->foschiNumbers[ 1 ][ 3 ];
        theObject->foschiNumbers[ 2 ][ 3 ] =
            (*thisObjectPtr)->foschiNumbers[ 2 ][ 3 ];
        theObject->foschiNumbers[ 3 ][ 3 ] =
            (*thisObjectPtr)->foschiNumbers[ 3 ][ 3 ];
        theObject->foschiNumbers[ 4 ][ 3 ] =
            (*thisObjectPtr)->foschiNumbers[ 4 ][ 3 ];
      }
    }


void  CGussetPlate::DoFoshiNumDialog( void )
{
  DialogHandlerRecordPtr   dhp;
  DecForm          dForm;
  Boolean          theBoxIsChecked;
  CGussetPlate      *thisObject;

  thisObject = this;


  DHStandardNewRecord (&dhp, GPFoschiParamDLOG_ID,
              GPFoschiParamUpdateUserItemId,
              GPDesignLength);


  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GPFoschiParamOneOne,
    (foschiNumbers[ 1 ][ 1 ] ),  dForm, 0.0, MAXREAL);

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GPFoschiParamTwoOne,
    (foschiNumbers[ 2 ][ 1 ] ),  dForm, 0.0, MAXREAL);

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GPFoschiParamThreeOne,
    (foschiNumbers[ 3 ][ 1 ] ),  dForm, 0.0, MAXREAL);

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GPFoschiParamFourOne,
    (foschiNumbers[ 4 ][ 1 ] ),  dForm, 0.0, MAXREAL);

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GPFoschiParamOneTwo,
    (foschiNumbers[ 1 ][ 2 ] ),  dForm, 0.0, MAXREAL);

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GPFoschiParamTwoTwo,
    (foschiNumbers[ 2 ][ 2 ] ),  dForm, 0.0, MAXREAL);

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GPFoschiParamThreeTwo,
    (foschiNumbers[ 3 ][ 2 ] ),  dForm, 0.0, MAXREAL);

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GPFoschiParamFourTwo,
    (foschiNumbers[ 4 ][ 2 ] ),  dForm, 0.0, MAXREAL);

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GPFoschiParamOneThree,
    (foschiNumbers[ 1 ][ 3 ] ),  dForm, 0.0, MAXREAL);

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GPFoschiParamTwoThree,
    (foschiNumbers[ 2 ][ 3 ] ),  dForm, 0.0, MAXREAL);

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GPFoschiParamThreeThree,
    (foschiNumbers[ 3 ][ 3 ] ),  dForm, 0.0, MAXREAL);

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GPFoschiParamFourThree,
    (foschiNumbers[ 4 ][ 3 ] ),  dForm, 0.0, MAXREAL);

  DHADDCHECKBOX( dhp, GPFoschiParamApplyToAll, FALSE);


  if (DHDialogHandler(dhp))
  {

    foschiNumbers[ 1 ][ 1 ] = DHGetEditReal(dhp, GPFoschiParamOneOne);
    foschiNumbers[ 2 ][ 1 ] = DHGetEditReal(dhp, GPFoschiParamTwoOne);
    foschiNumbers[ 3 ][ 1 ] = DHGetEditReal(dhp, GPFoschiParamThreeOne);
    foschiNumbers[ 4 ][ 1 ] = DHGetEditReal(dhp, GPFoschiParamFourOne);
    foschiNumbers[ 1 ][ 2 ] = DHGetEditReal(dhp, GPFoschiParamOneTwo);
    foschiNumbers[ 2 ][ 2 ] = DHGetEditReal(dhp, GPFoschiParamTwoTwo);
    foschiNumbers[ 3 ][ 2 ] = DHGetEditReal(dhp, GPFoschiParamThreeTwo);
    foschiNumbers[ 4 ][ 2 ] = DHGetEditReal(dhp, GPFoschiParamFourTwo);
    foschiNumbers[ 1 ][ 3 ] = DHGetEditReal(dhp, GPFoschiParamOneThree);
    foschiNumbers[ 2 ][ 3 ] = DHGetEditReal(dhp, GPFoschiParamTwoThree);
    foschiNumbers[ 3 ][ 3 ] = DHGetEditReal(dhp, GPFoschiParamThreeThree);
    foschiNumbers[ 4 ][ 3 ] = DHGetEditReal(dhp, GPFoschiParamFourThree);

    theBoxIsChecked = DHIsBoxChecked( dhp,
                GPFoschiParamApplyToAll);
    if( theBoxIsChecked )
    {
      itsTrussPane->NodesCluster->DoForEach1(
        Apply_FoschiNum, (long)(&thisObject) );
    }

  }
  DHDeallocateRecord(dhp);
}
void  CGussetPlate::DoPlateDesignDialog( void )
{
  DialogHandlerRecordPtr   dhp;
  DecForm          dForm;
  float          xLength;
  float          yLength;
  float          newTElementLength;
  float          TElementLength;
  Boolean          theBoxIsChecked;
  CGussetPlate      *thisObject;
  float          newTElementRatio;
  float          newplateLength;
  float          newplateHeight;
  float          newalpha;
  float          newgamma;
  float          theta;
  float           itsCosine;
  float           itsSine;
  float          newAngle;

  thisObject = this;

  DHStandardNewRecord (&dhp, GPDesignDLOG_ID,
              GPDesignUpdateUserItemId,
              GPDesignLength);

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GPDesignLength,
    (plateLength ),
      dForm, 1.0, 20.0);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GPDesignHeight,
    (plateHeight ),
      dForm, 1.0, 20.0);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GPDesignALPHA,
    (alpha ),
      dForm, 0.0, 1.0);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GPDesignGAMMA,
    (gamma ), dForm, 0.0, 1.0);  /* should be limit of drawing area*/


  if( itsMotherTElement )
  {
        /* this is to force an update in angle even if the*/
        /* Design Connection button was not pressed */
    GetSineAndCosine( &theta, &itsCosine, &itsSine);
  }

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GPDesignPlateAngle,
    (itsAngle ), dForm, 0.0, MAXREAL);  /* should be limit of drawing area*/

  DHAdvAddEditInteger(dhp, GPDesignNoOfTeethPerInchSq,
    (noOfTeethPerInch), 2, 16);  /* should be limit of drawing area*/


  DHADDCHECKBOX( dhp, GPDesignLengthApplyToAll, FALSE);
  DHADDCHECKBOX( dhp, GPDesignHeightApplyToAll, FALSE);
  DHADDCHECKBOX( dhp, GPDesignALPHAApplyToAll, FALSE);
  DHADDCHECKBOX( dhp, GPDesignGAMMAApplyToAll, FALSE);
  DHADDCHECKBOX( dhp, GPDesignPlateAngleApplyToAll, FALSE);
  DHADDCHECKBOX( dhp, GPDesignNoOfTeethPerInchSqApplyToAll, FALSE);
  if( itsMotherTElement )
  {
    DHADDCHECKBOX( dhp, GPDesignAlignWithMember, FALSE);
  }


  if (DHDialogHandler(dhp))
  {

    newplateLength = DHGetEditReal(dhp, GPDesignLength);
    newplateHeight = DHGetEditReal(dhp, GPDesignHeight);
    newalpha = DHGetEditReal(dhp, GPDesignALPHA);
    newgamma = DHGetEditReal(dhp, GPDesignGAMMA);

    if( ! (Abs(newplateLength - plateLength) <= SMALL_FLOAT_VALUE) )
    {
      bottomRightCorner.h = bottomLeftCorner.h + newplateLength;
      topRightCorner.h = topLeftCorner.h + newplateLength;
      plateLength = newplateLength;
    }

    if( ! (Abs(newplateHeight - plateHeight) <= SMALL_FLOAT_VALUE) )
    {
      topRightCorner.v = bottomRightCorner.v - newplateHeight;
      topLeftCorner.v = bottomLeftCorner.v - newplateHeight;
      plateHeight = newplateHeight;
    }

    if( ! (Abs(newalpha - alpha) <= SMALL_FLOAT_VALUE) )
    {
      masterPlateLocation.h = (newalpha*plateLength + bottomLeftCorner.h);
      alpha = newalpha;
    }

    if( ! (Abs(newgamma - gamma) <= SMALL_FLOAT_VALUE) )
    {
      masterPlateLocation.v = (bottomLeftCorner.v - newgamma*plateHeight);
      gamma = newgamma;
    }


     newAngle =  DHGetEditReal(dhp, GPDesignPlateAngle);

    if( ! (Abs(newAngle - itsAngle) <= SMALL_FLOAT_VALUE) )
    {
      itsOwnAngleFlag = TRUE;
      itsAngle = newAngle;
    }


    noOfTeethPerInch = DHGetEditInteger(dhp, GPDesignNoOfTeethPerInchSq);


    theBoxIsChecked = DHIsBoxChecked( dhp,
                GPDesignLengthApplyToAll);
    if( theBoxIsChecked )
    {
      itsTrussPane->NodesCluster->DoForEach1(
        Apply_Length, (long)(&thisObject) );
    }

    theBoxIsChecked = DHIsBoxChecked( dhp,
                GPDesignHeightApplyToAll);
    if( theBoxIsChecked )
    {
      itsTrussPane->NodesCluster->DoForEach1(
        Apply_Height, (long)(&thisObject) );
    }

    theBoxIsChecked = DHIsBoxChecked( dhp,
                GPDesignALPHAApplyToAll);
    if( theBoxIsChecked )
    {
      itsTrussPane->NodesCluster->DoForEach1(
        Apply_ALPHA, (long)(&thisObject) );
    }

    theBoxIsChecked = DHIsBoxChecked( dhp,
                GPDesignGAMMAApplyToAll);
    if( theBoxIsChecked )
    {
      itsTrussPane->NodesCluster->DoForEach1(
        Apply_GAMMA, (long)(&thisObject) );
    }

    theBoxIsChecked = DHIsBoxChecked( dhp,
                GPDesignPlateAngleApplyToAll);
    if( theBoxIsChecked )
    {
      itsTrussPane->NodesCluster->DoForEach1(
        Apply_PlateAngle, (long)(&thisObject) );
    }

    theBoxIsChecked = DHIsBoxChecked( dhp,
                GPDesignNoOfTeethPerInchSqApplyToAll);
    if( theBoxIsChecked )
    {
      itsTrussPane->NodesCluster->DoForEach1(
        Apply_NoOfTeethPerInchSq, (long)(&thisObject) );
    }

    theBoxIsChecked = DHIsBoxChecked( dhp,
                GPDesignAlignWithMember);
    if( theBoxIsChecked )
    {
      itsOwnAngleFlag = FALSE;
    }
    (( CGussetPane *)(this->itsDocument->itsMainPane))->Refresh();
  }
  DHDeallocateRecord(dhp);
}

void CGussetPlate::DoYourDialog( void )
{
  DialogHandlerRecordPtr   dhp;
  RadioButtonSetPtr     set1;
  DecForm          dForm;
  float          xLocation;
  float          yLocation;
  float          newTElementConnectionRatio;
  CGussetPlate      *thisObject;
  BoundaryCondition    newBoundaryCondition;

  DHStandardNewRecord (&dhp, GussetPlateDLOG_ID,
                GussetPlateUpdateUserItemId, NoSelectedItem);
      /* always make use of dhp after memory has been allocated*/
      /* for it, i.e after the record has been created. If the*/
      /* next two lines were located before DHStandardNewRecord*/
      /* the program crashed */
  thisObject = this;
  dhp->progItem1 = (Handle)thisObject;

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GussetPlateEditTextXLocation,
    (itsCenterPoint.h * itsTrussPane->theStructureScale / SCREEN_DPI ),
      dForm, 0.0, MAXREAL);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GussetPlateEditTextYLocation,
    (itsCenterPoint.v  * itsTrussPane->theStructureScale / SCREEN_DPI ),
      dForm, 0.0, MAXREAL); /* should be limit of drawing area*/

  if ( IamConnected )
  {
    dForm.digits = 2;
    dForm.style = FIXEDDECIMAL;
    DHAdvAddEditReal(dhp, GussetPlateTEConnectionRatio,
      (TElementConnectionRatio ),
        dForm, 0.0, 1.0);
  }

  DHAddRadioSet(dhp, itsBoundaryCondition, &set1);
  DHAdvAddRadioButtonToSet(&set1, GussetPlateFree,
                  DHNoKeyEquiv(), NULL);
  DHAdvAddRadioButtonToSet(&set1, GussetPlateRotationFixed, DHNoKeyEquiv(),
                   NULL);
  DHAdvAddRadioButtonToSet(&set1, GussetPlateXTranslationFixed, DHNoKeyEquiv(),
                   NULL);
  DHAdvAddRadioButtonToSet(&set1, GussetPlateYTranslationFixed,
                  DHNoKeyEquiv(), NULL);
  DHAdvAddRadioButtonToSet(&set1, GussetPlateXYTranslationFixed,
                  DHNoKeyEquiv(), NULL);
  DHAdvAddRadioButtonToSet(&set1, GussetPlateXYTranslationAndRotationFixed,
                  DHNoKeyEquiv(), NULL);
  DHAdvAddRadioButtonToSet(&set1, GussetPlateXTranslationAndRotationFixed,
                  DHNoKeyEquiv(), NULL);
  DHAdvAddRadioButtonToSet(&set1, GussetPlateYTranslationAndRotationFixed,
                  DHNoKeyEquiv(), NULL);

  DHAdvAddPushButton(dhp, GussetPlateDesignConnection, Exit,
              DHNoKeyEquiv(), DoConnectionDesignDialogHook);

  DHAdvAddPushButton(dhp, GussetPlateDesignPlate, Exit,
              DHNoKeyEquiv(), DoPlateDesignDialogHook);

  DHAdvAddPushButton(dhp, GussetPlateFoschiNumbers, NoExit,
              DHNoKeyEquiv(), DoFoschiNumDialogHook);

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



void CGussetPlate::Dispose()
{

  itsDocument->Dispose();
  inherited::Dispose();

}



void CGussetPlate::GetSineAndCosine( float  *theta, float *itsCosine,
            float *itsSine )
{
  Point          its1stEnd;
  Point          its2ndEnd;
  float          xLength,yLength, TElementLength;
  float          scalingFactor;
  CRegularWoodTElement  *itsMotherTElement;

  if ( this->itsMotherTElement )
  {
    itsMotherTElement = (CRegularWoodTElement  *)(this->itsMotherTElement);


    scalingFactor = SCREEN_DPI / (itsTrussPane->theStructureScale);

    its1stEnd.v = itsMotherTElement->its1stEnd.v + (int) (itsMotherTElement->its1stEndVOffset * scalingFactor);
    its1stEnd.h = itsMotherTElement->its1stEnd.h + (int) (itsMotherTElement->its1stEndHOffset * scalingFactor);
    its2ndEnd.v = itsMotherTElement->its2ndEnd.v + (int) (itsMotherTElement->its2ndEndVOffset * scalingFactor);
    its2ndEnd.h = itsMotherTElement->its2ndEnd.h + (int) (itsMotherTElement->its2ndEndHOffset * scalingFactor);

    TElementLength = (float) sqrt((double)(( (((float)(its2ndEnd.v -its1stEnd.v))*
              ((float)(its2ndEnd.v -its1stEnd.v) )) +
              ( ((float)(its2ndEnd.h -its1stEnd.h))*
              ((float)(its2ndEnd.h -its1stEnd.h)) ) ) ) );

    if ( (its1stEnd.v >= its2ndEnd.v) && ( its2ndEnd.h >= its1stEnd.h ) )
    {    /* 4th Quadrant */
      xLength = (float)(Abs( its2ndEnd.h - its1stEnd.h ));
      yLength = (float)(Abs( its2ndEnd.v - its1stEnd.v));

      *theta = (float) ( ( 360 ) * PI / 180.0 ) -
              (float)( atan( (double)(yLength/xLength) ) );
      *itsCosine = xLength / TElementLength;
      *itsSine = -yLength / TElementLength;
    }
    else
    if ( (its1stEnd.v >= its2ndEnd.v) && ( its1stEnd.h >= its2ndEnd.h ) )
    {    /* 3rd Quadrant */
      xLength = (float)(Abs( its2ndEnd.h - its1stEnd.h ));
      yLength = (float)(Abs( its2ndEnd.v - its1stEnd.v));

      *theta = (float) ( ( 180 ) * PI / 180.0 ) +
              (float)( atan( (double)(yLength/xLength) ) );
      *itsCosine = -xLength / TElementLength;
      *itsSine = -yLength / TElementLength;
    }
    else
    if ( (its2ndEnd.v >= its1stEnd.v) && ( its1stEnd.h >= its2ndEnd.h ) )
    {    /* 2nd Quadrant */
      xLength = (float)(Abs( its2ndEnd.h - its1stEnd.h ));
      yLength = (float)( its2ndEnd.v - its1stEnd.v);

      *theta = (float) ( ( 180 ) * PI / 180.0 ) -
              (float)( atan( (double)(yLength/xLength) ) );
      *itsCosine = -xLength / TElementLength;
      *itsSine = yLength / TElementLength;
    }
    else
    if ( (its2ndEnd.v >= its1stEnd.v) && ( its2ndEnd.h >= its1stEnd.h ) )
    {    /* 1st Quadrant */
      xLength = (float)( its2ndEnd.h - its1stEnd.h);
      yLength = (float)( its2ndEnd.v - its1stEnd.v);

      *theta = (float)( atan( (double)(yLength/xLength) ) );
      *itsCosine = xLength / TElementLength;
      *itsSine = yLength / TElementLength;
    }

    if (  itsOwnAngleFlag )      /* give the user a chance to change it*/
    {
      *theta = (float) ( itsAngle * PI / 180.0 );
      *itsCosine = (float) cos( (double)( ( itsAngle * PI / 180.0 )));
      *itsSine = (float) sin( (double)( ( itsAngle * PI / 180.0 )));
    }
    else
      itsAngle = (float) ( ( *theta)  / PI * 180.0 ); /* align with member*/


  }
  else
  {
    *theta = (float) ( itsAngle * PI / 180.0 );
    *itsCosine = (float) cos( (double)(*theta));
    *itsSine = (float) sin( (double)( *theta));
  }
}

Point CGussetPlate::TransformTElementToPano( FloatPoint aRealPoint,
                 Point theStartPoint)
{
  Point    theTransformedPoint;
  float    theta;
  float     itsCosine;
  float     itsSine;


  GetSineAndCosine( &theta, &itsCosine, &itsSine);

  theTransformedPoint.h = (((int) (aRealPoint.h * itsCosine) -
                (aRealPoint.v * itsSine)) + theStartPoint.h);
  theTransformedPoint.v = (((int) (aRealPoint.h * itsSine) +
                (aRealPoint.v * itsCosine)) + theStartPoint.v);

  return( theTransformedPoint );

}

Point CGussetPlate::TransformGlobalToPano( FloatPoint aRealPoint,
                 Point theStartPoint)
{
  Point    theTransformedPoint;
  float    theta = 0;
  float     itsCosine = 1.0;
  float     itsSine = 0.0;


/*  GetSineAndCosine( &theta, &itsCosine, &itsSine);
*/
  theTransformedPoint.h = (((int) (aRealPoint.h * itsCosine) -
                (aRealPoint.v * itsSine)) + theStartPoint.h);
  theTransformedPoint.v = (((int) (aRealPoint.h * itsSine) +
                (aRealPoint.v * itsCosine)) + theStartPoint.v);

  return( theTransformedPoint );

}


void CGussetPlate::TransformTElementToPanoNew( FloatPoint aRealPoint[],
                 Point theStartPoint, int numberOfPoints,
                 Point TransformedPoints[])
{
  float    theta;
  float     itsCosine;
  float     itsSine;
  int      counter = 0;


  GetSineAndCosine( &theta, &itsCosine, &itsSine);

  for( counter = 0; counter < numberOfPoints; counter++ )
  {

    (TransformedPoints[counter]).h = (((int) ((aRealPoint[counter]).h * itsCosine) -
             ((aRealPoint[counter]).v * itsSine)) + theStartPoint.h);
    (TransformedPoints[counter]).v = (((int) ((aRealPoint[counter]).h * itsSine) +
            ((aRealPoint[counter]).v * itsCosine)) + theStartPoint.v);
  }
}
FloatPoint CGussetPlate::TransformPanoToTElement( Point aPoint,
               Point  firstEndLocation)
{
  FloatPoint  theTransformedPoint;
  float    theta;
  float     itsCosine;
  float     itsSine;


  GetSineAndCosine( &theta, &itsCosine, &itsSine);

  theTransformedPoint.h =
      (((float) (aPoint.h - firstEndLocation.h) * itsCosine) +
      ((float)(aPoint.v - firstEndLocation.v) * itsSine));

  theTransformedPoint.v =
      (((float) (aPoint.h - firstEndLocation.h) * (-itsSine)) +
      ((float)(aPoint.v - firstEndLocation.v) * itsCosine));

  return( theTransformedPoint );
}

FloatPoint CGussetPlate::TransformPanoToGloabal( Point aPoint,
               Point  firstEndLocation)
{
  FloatPoint  theTransformedPoint;
  float    theta = 0;
  float     itsCosine = 1.0;
  float     itsSine = 0;


/*  GetSineAndCosine( &theta, &itsCosine, &itsSine);
*/
  theTransformedPoint.h =
      (((float) (aPoint.h - firstEndLocation.h) * itsCosine) +
      ((float)(aPoint.v - firstEndLocation.v) * itsSine));

  theTransformedPoint.v =
      (((float) (aPoint.h - firstEndLocation.h) * (-itsSine)) +
      ((float)(aPoint.v - firstEndLocation.v) * itsCosine));

  return( theTransformedPoint );
}



