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
extern  long      NumberOfJointsLoaded;
extern  float      LargestYValue;



  static void EnforcePhysCondAndDoUpdates( CGussetPlate  *thePlate)
  {
    if(   thePlate->masterPlateLocation.h  > thePlate->bottomRightCorner.h)
    {
      thePlate->masterPlateLocation.h = thePlate->bottomRightCorner.h;
    }
    if(   thePlate->masterPlateLocation.h  < thePlate->bottomLeftCorner.h)
    {
      thePlate->masterPlateLocation.h = thePlate->bottomLeftCorner.h;
    }
    if(   thePlate->masterPlateLocation.v  > thePlate->bottomLeftCorner.v)
    {
      thePlate->masterPlateLocation.v = thePlate->bottomLeftCorner.v;
    }
    if(   thePlate->masterPlateLocation.v  < thePlate->topLeftCorner.v)
    {
      thePlate->masterPlateLocation.v = thePlate->topLeftCorner.v;
    }

    thePlate->plateLength = Abs(thePlate->bottomRightCorner.h -
                      thePlate->bottomLeftCorner.h);
    thePlate->plateHeight = Abs(thePlate->bottomLeftCorner.v -
                      thePlate->topLeftCorner.v);

    thePlate->alpha = Abs((thePlate->masterPlateLocation.h -
          thePlate->bottomLeftCorner.h)) / (thePlate->plateLength);
    thePlate->gamma = Abs((thePlate->masterPlateLocation.v -
          thePlate->bottomLeftCorner.v)) / (thePlate->plateHeight);
  }

void CGussetPlate::DrawMasterPlateLocator( void )
{
  PenState      pnState;

  FloatPoint      masterPlateLocation;
  FloatPoint      masterPlateLocation1;
  FloatPoint      masterPlateLocation2;
  FloatPoint      masterPlateLocation3;
  FloatPoint      masterPlateLocation4;
  FloatPoint      masterPlateLocation5;
  FloatPoint      masterPlateLocation6;
  FloatPoint      bottomLeftTEMP;

  Point        masterPlateLocationPoint;
  Point        masterPlateLocationPoint1;
  Point        masterPlateLocationPoint2;
  Point        masterPlateLocationPoint3;
  Point        masterPlateLocationPoint4;
  Point        masterPlateLocationPoint5;
  Point        masterPlateLocationPoint6;
  Point        bottomLeftTEMPpoint;

  float        scalingFactor;
  CGussetPlate    *thisObject;
  FloatPoint      arrayOfFloatPoints[ 7 ];
  Point        TransformedPoints[ 7 ];

  FloatPoint      its1stEnd;
  FloatPoint      its2ndEnd;
  float        its1stEndHorz;
  float        its1stEndVert;
  float        its2ndEndHorz;
  float        its2ndEndVert;
  Point        itsCenterPoint;
  FloatPoint      tempCenter;



  thisObject = this;
  EnforcePhysCondAndDoUpdates( thisObject);


  scalingFactor = SCREEN_DPI / ((( CGussetPane *)(thisObject->
        itsDocument->itsMainPane))->
                  theStructureScale);

  masterPlateLocation.v = this->masterPlateLocation.v* scalingFactor;
  masterPlateLocation.h = this->masterPlateLocation.h * scalingFactor;
  masterPlateLocation1.v = this->masterPlateLocation.v * scalingFactor;
  masterPlateLocation1.h = (this->masterPlateLocation.h  + .5)* scalingFactor;
  masterPlateLocation2.v = (this->masterPlateLocation.v + .5 )* scalingFactor;
  masterPlateLocation2.h = this->masterPlateLocation.h * scalingFactor;
  masterPlateLocation3.v = this->masterPlateLocation.v* scalingFactor;
  masterPlateLocation3.h = (this->masterPlateLocation.h - .5)* scalingFactor;
  masterPlateLocation4.v = (this->masterPlateLocation.v -.5)* scalingFactor;
  masterPlateLocation4.h = this->masterPlateLocation.h * scalingFactor;
  masterPlateLocation5.v = (this->masterPlateLocation.v -.1)* scalingFactor;
  masterPlateLocation5.h = (this->masterPlateLocation.h +.3)* scalingFactor;
  masterPlateLocation6.v = (this->masterPlateLocation.v +.1)* scalingFactor;
  masterPlateLocation6.h = (this->masterPlateLocation.h +.3)* scalingFactor;

  bottomLeftTEMP.h = bottomLeftHOffset * scalingFactor;
  bottomLeftTEMP.v = bottomLeftVOffset * scalingFactor;


  arrayOfFloatPoints[ 0 ] = masterPlateLocation;
  arrayOfFloatPoints[ 1 ] = masterPlateLocation1;
  arrayOfFloatPoints[ 2 ] = masterPlateLocation2;
  arrayOfFloatPoints[ 3 ] = masterPlateLocation3;
  arrayOfFloatPoints[ 4 ] = masterPlateLocation4;
  arrayOfFloatPoints[ 5 ] = masterPlateLocation5;
  arrayOfFloatPoints[ 6 ] = masterPlateLocation6;


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

  bottomLeftTEMPpoint = TransformTElementToPano( bottomLeftTEMP,
                 itsCenterPoint);



  TransformTElementToPanoNew(arrayOfFloatPoints, bottomLeftTEMPpoint, 7,
                TransformedPoints);

  masterPlateLocationPoint = TransformedPoints[ 0 ];
  masterPlateLocationPoint1 = TransformedPoints[ 1 ];
  masterPlateLocationPoint2 = TransformedPoints[ 2 ];
  masterPlateLocationPoint3 = TransformedPoints[ 3 ];
  masterPlateLocationPoint4 = TransformedPoints[ 4 ];
  masterPlateLocationPoint5 = TransformedPoints[ 5 ];
  masterPlateLocationPoint6 = TransformedPoints[ 6 ];


  GetPenState ( &pnState);/* to save the pen setting */
  PenSize( 2,2 );


/*  myPolygon = OpenPoly(); */

  MoveTo( masterPlateLocationPoint.h,
      masterPlateLocationPoint.v);
  LineTo( masterPlateLocationPoint1.h,
      masterPlateLocationPoint1.v);
  MoveTo( masterPlateLocationPoint.h,
      masterPlateLocationPoint.v);
  LineTo( masterPlateLocationPoint2.h,
      masterPlateLocationPoint2.v);
  MoveTo( masterPlateLocationPoint.h,
      masterPlateLocationPoint.v);
  LineTo( masterPlateLocationPoint3.h,
      masterPlateLocationPoint3.v);
  MoveTo( masterPlateLocationPoint.h,
      masterPlateLocationPoint.v);
  LineTo( masterPlateLocationPoint4.h,
      masterPlateLocationPoint4.v);
  MoveTo( masterPlateLocationPoint1.h,
      masterPlateLocationPoint1.v);
  LineTo( masterPlateLocationPoint5.h,
      masterPlateLocationPoint5.v);
  MoveTo( masterPlateLocationPoint1.h,
      masterPlateLocationPoint1.v);
  LineTo( masterPlateLocationPoint6.h,
      masterPlateLocationPoint6.v);

  SetPenState ( &pnState);/* to resotre pen settting */
}



void CGussetPlate::BlowUpDraw( CGussetPlate *thePlate)
{
  PenState      pnState;

  FloatPoint      bottomLeftCorner;
  FloatPoint      bottomRightCorner;
  FloatPoint      topRightCorner;
  FloatPoint      topLeftCorner;
  FloatPoint      bottomLeftTEMP;

  Point        bottomLeftCornerPoint;
  Point        bottomRightCornerPoint;
  Point        topRightCornerPoint;
  Point        topLeftCornerPoint;
  Point        bottomLeftTEMPpoint;

  float        scalingFactor;
  CGussetPlate    *thisObject;
  FloatPoint      arrayOfFloatPoints[ 4 ];
  Point        TransformedPoints[ 4 ];

  FloatPoint      its1stEnd;
  FloatPoint      its2ndEnd;
  float        its1stEndHorz;
  float        its1stEndVert;
  float        its2ndEndHorz;
  float        its2ndEndVert;
  Point        itsCenterPoint;
  FloatPoint      tempCenter;


  thisObject = this;
  EnforcePhysCondAndDoUpdates( this );


  scalingFactor = SCREEN_DPI / ((( CGussetPane *)(thePlate->
        itsDocument->itsMainPane))->
                  theStructureScale);

  bottomLeftCorner.v = this->bottomLeftCorner.v * scalingFactor;
  bottomLeftCorner.h = this->bottomLeftCorner.h * scalingFactor;
  bottomRightCorner.v = this->bottomRightCorner.v  * scalingFactor;
  bottomRightCorner.h = (this->bottomRightCorner.h )* scalingFactor;
  topRightCorner.v = (this->topRightCorner.v  )* scalingFactor;
  topRightCorner.h = (this->topRightCorner.h   )* scalingFactor;
  topLeftCorner.v = (this->topLeftCorner.v    )* scalingFactor;
  topLeftCorner.h = this->topLeftCorner.h * scalingFactor;

  bottomLeftTEMP.h = bottomLeftHOffset * scalingFactor;
  bottomLeftTEMP.v = bottomLeftVOffset * scalingFactor;


  arrayOfFloatPoints[ 0 ] = bottomLeftCorner;
  arrayOfFloatPoints[ 1 ] = bottomRightCorner;
  arrayOfFloatPoints[ 2 ] = topRightCorner;
  arrayOfFloatPoints[ 3 ] = topLeftCorner;



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

  bottomLeftTEMPpoint = TransformTElementToPano( bottomLeftTEMP,
                 itsCenterPoint);



  TransformTElementToPanoNew(arrayOfFloatPoints, bottomLeftTEMPpoint, 4,
                TransformedPoints);

  bottomLeftCornerPoint = TransformedPoints[ 0 ];
  bottomRightCornerPoint = TransformedPoints[ 1 ];
  topRightCornerPoint = TransformedPoints[ 2 ];
  topLeftCornerPoint = TransformedPoints[ 3 ];

  MoveTo( bottomLeftCornerPoint.h,
      bottomLeftCornerPoint.v);
  LineTo( bottomRightCornerPoint.h,
      bottomRightCornerPoint.v);
  LineTo( topRightCornerPoint.h,
      topRightCornerPoint.v);
  LineTo( topLeftCornerPoint.h,
      topLeftCornerPoint.v);
  LineTo( bottomLeftCornerPoint.h,
      bottomLeftCornerPoint.v);

  DrawMasterPlateLocator();

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

Boolean CGussetPlate::WhichOneOfUsGotSelected( Point aPoint )
{
  inherited::WhichOneOfUsGotSelected( aPoint );
  positionningMasterPlateNode = FALSE;
  placingInProgress = FALSE;
  ReSizingInProgress = FALSE;

}


Boolean CGussetPlate::BUP_WhichOneOfUsGotSelected( Point aPoint,
              CGussetPlate  *thePlate )
{
  float    offSetLength;
  float    scalingFactor;
  FloatPoint      bottomLeftCorner;
  FloatPoint      bottomRightCorner;
  FloatPoint      topRightCorner;
  FloatPoint      topLeftCorner;
  FloatPoint      masterPlateLocation;
  FloatPoint      bottomLeftTEMP;
  Point        bottomLeftTEMPpoint;
  Point        masterPlateLocationPoint;

  GrafPtr          oldPort;
  GrafPort        privatePort;
  int            bits;
  BitMap          map;
  PenState         pnState;

  FloatPoint      its1stEnd;
  FloatPoint      its2ndEnd;
  float        its1stEndHorz;
  float        its1stEndVert;
  float        its2ndEndHorz;
  float        its2ndEndVert;
  Point        itsCenterPoint;
  FloatPoint      tempCenter;


  if( itsMotherTElement )
  {
    scalingFactor = SCREEN_DPI / (itsTrussPane->theStructureScale);

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

  scalingFactor = SCREEN_DPI / ((( CGussetPane *)(thePlate->
        itsDocument->itsMainPane))->
                  theStructureScale);

  bottomLeftCorner.v = this->bottomLeftCorner.v * scalingFactor;
  bottomLeftCorner.h = this->bottomLeftCorner.h * scalingFactor;
  bottomRightCorner.v = this->bottomRightCorner.v  * scalingFactor;
  bottomRightCorner.h = (this->bottomRightCorner.h )* scalingFactor;
  topRightCorner.v = (this->topRightCorner.v  )* scalingFactor;
  topRightCorner.h = (this->topRightCorner.h   )* scalingFactor;
  topLeftCorner.v = (this->topLeftCorner.v    )* scalingFactor;
  topLeftCorner.h = this->topLeftCorner.h * scalingFactor;
  masterPlateLocation.v = this->masterPlateLocation.v* scalingFactor;
  masterPlateLocation.h = this->masterPlateLocation.h * scalingFactor;

  bottomLeftTEMP.h = bottomLeftHOffset * scalingFactor;
  bottomLeftTEMP.v = bottomLeftVOffset * scalingFactor;

  bottomLeftTEMPpoint = TransformTElementToPano( bottomLeftTEMP,
                 itsCenterPoint);

  masterPlateLocationPoint = TransformTElementToPano( masterPlateLocation,
                 bottomLeftTEMPpoint);



  if ( ( HitSamePart( (TransformTElementToPano(bottomLeftCorner, bottomLeftTEMPpoint)),
      aPoint, &offSet  ) ) )
  {
    positionningMasterPlateNode = FALSE;
    placingInProgress = FALSE;
    ReSizingInProgress = TRUE;

    topLeftCornerFlag = FALSE;
    bottomRightCornerFlag = FALSE;
    bottomLeftCornerFlag = TRUE;
    topRightCornerFlag = FALSE;
    masterPlateFlag = FALSE;

    itsCenterPointFlag = FALSE;

    return ( TRUE );
  }
  else if ( ( HitSamePart( (TransformTElementToPano(bottomRightCorner, bottomLeftTEMPpoint)),
      aPoint, &offSet  ) ) )
  {
    positionningMasterPlateNode = FALSE;
    placingInProgress = FALSE;
    ReSizingInProgress = TRUE;

    topLeftCornerFlag = FALSE;
    bottomRightCornerFlag = TRUE;
    bottomLeftCornerFlag = FALSE;
    topRightCornerFlag = FALSE;
    masterPlateFlag = FALSE;

    itsCenterPointFlag = FALSE;

    return ( TRUE );
  }
  else if ( ( HitSamePart( (TransformTElementToPano(topRightCorner, bottomLeftTEMPpoint)),
      aPoint, &offSet  ) ) )
  {
    positionningMasterPlateNode = FALSE;
    placingInProgress = FALSE;
    ReSizingInProgress = TRUE;

    topLeftCornerFlag = FALSE;
    bottomRightCornerFlag = FALSE;
    bottomLeftCornerFlag = FALSE;
    topRightCornerFlag = TRUE;
    masterPlateFlag = FALSE;

    itsCenterPointFlag = FALSE;

    return ( TRUE );
  }
  else if ( ( HitSamePart( (TransformTElementToPano(topLeftCorner, bottomLeftTEMPpoint)),
      aPoint, &offSet  ) ) )
  {
    positionningMasterPlateNode = FALSE;
    placingInProgress = FALSE;
    ReSizingInProgress = TRUE;

    topLeftCornerFlag = TRUE;
    bottomRightCornerFlag = FALSE;
    bottomLeftCornerFlag = FALSE;
    topRightCornerFlag = FALSE;
    masterPlateFlag = FALSE;

    itsCenterPointFlag = FALSE;

    return ( TRUE );
  }
  else
  {
    GetPort( &oldPort );
    OpenPort( &privatePort );
    PortSize( 16, 1 );

    map.baseAddr = (void *)&bits;
    map.rowBytes = 2;
    SetRect( &(map.bounds), 0, 0, 16, 1);

    SetPortBits( &map );

    SetOrigin( aPoint.h-15, aPoint.v );

    bits = 0;

    GetPenState ( &pnState);/* to save the pen setting */
    PenSize( 2,2 );
    DrawMasterPlateLocator();
    SetPenState ( &pnState);/* to resotre pen settting */

    if( odd( bits ) )
    {

      offSet.v = aPoint.v - masterPlateLocationPoint.v;
      offSet.h = aPoint.h - masterPlateLocationPoint.h;


      positionningMasterPlateNode = TRUE;
      placingInProgress = FALSE;
      ReSizingInProgress = FALSE;

      topLeftCornerFlag = FALSE;
      bottomRightCornerFlag = FALSE;
      bottomLeftCornerFlag = FALSE;
      topRightCornerFlag = FALSE;
      masterPlateFlag = TRUE;

      itsCenterPointFlag = FALSE;

      SetPort( oldPort );
      ClosePort( &privatePort );
      return( TRUE );
    }
    else
    {
      SetPort( oldPort );
      ClosePort( &privatePort );
    }


    GetPort( &oldPort );
    OpenPort( &privatePort );
    PortSize( 16, 1 );

    map.baseAddr = (void *)&bits;
    map.rowBytes = 2;
    SetRect( &(map.bounds), 0, 0, 16, 1);

    SetPortBits( &map );

    SetOrigin( aPoint.h-15, aPoint.v );

    bits = 0;

    GetPenState ( &pnState);/* to save the pen setting */
    PenSize( 2,2 );
    BlowUpDraw( this );
    SetPenState ( &pnState);/* to resotre pen settting */

    if( odd( bits ) )
    {

      offSet.v = aPoint.v - bottomLeftTEMPpoint.v;
      offSet.h = aPoint.h - bottomLeftTEMPpoint.h;

      positionningMasterPlateNode = FALSE;
      placingInProgress = TRUE;
      ReSizingInProgress = FALSE;

      topLeftCornerFlag = FALSE;
      bottomRightCornerFlag = FALSE;
      bottomLeftCornerFlag = FALSE;
      topRightCornerFlag = FALSE;
      masterPlateFlag = FALSE;

      itsCenterPointFlag = FALSE;

      SetPort( oldPort );
      ClosePort( &privatePort );
      return( TRUE );
    }
    else
    {
      positionningMasterPlateNode = FALSE;
      placingInProgress = FALSE;
      ReSizingInProgress = FALSE;

      topLeftCornerFlag = FALSE;
      bottomRightCornerFlag = FALSE;
      bottomLeftCornerFlag = FALSE;
      topRightCornerFlag = FALSE;
      masterPlateFlag = FALSE;

      itsCenterPointFlag = FALSE;
      SetPort( oldPort );
      ClosePort( &privatePort );
      return( FALSE );
    }
  }

  return FALSE;
}

void CGussetPlate::UpDateObject( void )
{
  if ( ReSizingInProgress )
  {
    ResizeYourself();
  }
  else if( placingInProgress )
  {
    PlaceYourself();
  }
  else if( positionningMasterPlateNode )
  {
    PositionMasterPlateNode();
  }
  else
  {
    MoveYourself();
  }
}

      static void BUP_DragYourself(  CGussetPlate *thisObject )
      {
        PenState     pnState;

        GetPenState ( &pnState);/* to save the pen setting */
        PenMode ( patXor );
        thisObject->BlowUpDraw( thisObject );
        SetPenState ( &pnState);/* to resotre pen settting */
      }
      static void BUP_DragMasterPlateLocator( CGussetPlate *thisObject )
      {
        PenState     pnState;

        GetPenState ( &pnState);/* to save the pen setting */
        PenMode ( patXor );
        thisObject->DrawMasterPlateLocator();
        SetPenState ( &pnState);/* to resotre pen settting */
      }




void CGussetPlate::ResizeYourself( void )
{
  CGussetPlate    *thisObject;
  float        scalingFactor;
  Point        bottomLeftTEMPpoint;

  FloatPoint      bottomLeftCorner;
  FloatPoint      bottomRightCorner;
  FloatPoint      topRightCorner;
  FloatPoint      topLeftCorner;
  FloatPoint      masterPlateLocation;
  FloatPoint      bottomLeftTEMP;
  FloatPoint      theTransformedPoint;
  Point        tempPoint;

  FloatPoint      its1stEnd;
  FloatPoint      its2ndEnd;
  float        its1stEndHorz;
  float        its1stEndVert;
  float        its2ndEndHorz;
  float        its2ndEndVert;
  Point        itsCenterPoint;
  FloatPoint      tempCenter;


  if( itsMotherTElement )
  {
    scalingFactor = SCREEN_DPI / (itsTrussPane->theStructureScale);

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



  thisObject = this;

  scalingFactor = SCREEN_DPI / ((( CGussetPane *)(this->
        itsDocument->itsMainPane))->
                  theStructureScale);

  bottomLeftCorner.v = this->bottomLeftCorner.v * scalingFactor;
  bottomLeftCorner.h = this->bottomLeftCorner.h * scalingFactor;
  bottomRightCorner.v = this->bottomRightCorner.v  * scalingFactor;
  bottomRightCorner.h = (this->bottomRightCorner.h )* scalingFactor;
  topRightCorner.v = (this->topRightCorner.v  )* scalingFactor;
  topRightCorner.h = (this->topRightCorner.h   )* scalingFactor;
  topLeftCorner.v = (this->topLeftCorner.v    )* scalingFactor;
  topLeftCorner.h = this->topLeftCorner.h * scalingFactor;
  masterPlateLocation.v = this->masterPlateLocation.v* scalingFactor;
  masterPlateLocation.h = this->masterPlateLocation.h * scalingFactor;

  bottomLeftTEMP.h = bottomLeftHOffset * scalingFactor;
  bottomLeftTEMP.v = bottomLeftVOffset * scalingFactor;

  bottomLeftTEMPpoint = TransformTElementToPano( bottomLeftTEMP,
                 itsCenterPoint);


  tempPoint.v = (theHitPoint.v - offSet.v);
  tempPoint.h = (theHitPoint.h - offSet.h);

  theTransformedPoint  = TransformPanoToTElement( tempPoint, bottomLeftTEMPpoint );

  if( bottomLeftCornerFlag )
  {
    this->bottomLeftCorner.v = theTransformedPoint.v / scalingFactor;
    this->bottomLeftCorner.h = theTransformedPoint.h / scalingFactor;

    this->bottomRightCorner.v = theTransformedPoint.v / scalingFactor;
    this->topLeftCorner.h = theTransformedPoint.h / scalingFactor;
  }

  else if( bottomRightCornerFlag )
  {
    this->bottomRightCorner.v = theTransformedPoint.v / scalingFactor;
    this->bottomRightCorner.h = theTransformedPoint.h / scalingFactor;

    this->bottomLeftCorner.v = theTransformedPoint.v / scalingFactor;
    this->topRightCorner.h = theTransformedPoint.h / scalingFactor;
  }

  else if ( topRightCornerFlag )
  {
    this->topRightCorner.v = theTransformedPoint.v / scalingFactor;
    this->topRightCorner.h = theTransformedPoint.h / scalingFactor;

    this->bottomRightCorner.h = theTransformedPoint.h / scalingFactor;
    this->topLeftCorner.v = theTransformedPoint.v / scalingFactor;
  }
  else if( topLeftCornerFlag )
  {
    this->topLeftCorner.v = theTransformedPoint.v / scalingFactor;
    this->topLeftCorner.h = (theTransformedPoint.h / scalingFactor);

    this->bottomLeftCorner.h = theTransformedPoint.h / scalingFactor;
    this->topRightCorner.v = theTransformedPoint.v / scalingFactor;
  }
  BUP_DragYourself( thisObject );
}


void CGussetPlate::PositionMasterPlateNode( void )
{
  CGussetPlate    *thisObject;
  float        scalingFactor;
  FloatPoint      bottomLeftTEMP;
  FloatPoint      theTransformedPoint;
  Point        tempPoint;
  Point        bottomLeftTEMPpoint;
  FloatPoint      bottomLeftCorner;
  FloatPoint      bottomRightCorner;
  FloatPoint      topRightCorner;
  FloatPoint      topLeftCorner;

  FloatPoint      its1stEnd;
  FloatPoint      its2ndEnd;
  float        its1stEndHorz;
  float        its1stEndVert;
  float        its2ndEndHorz;
  float        its2ndEndVert;
  Point        itsCenterPoint;
  FloatPoint      tempCenter;


  if( itsMotherTElement )
  {
    scalingFactor = SCREEN_DPI / (itsTrussPane->theStructureScale);

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

  bottomLeftTEMP.h = bottomLeftHOffset * scalingFactor;
  bottomLeftTEMP.v = bottomLeftVOffset * scalingFactor;

  bottomLeftCorner.v = this->bottomLeftCorner.v * scalingFactor;
  bottomLeftCorner.h = this->bottomLeftCorner.h * scalingFactor;
  bottomRightCorner.v = this->bottomRightCorner.v  * scalingFactor;
  bottomRightCorner.h = (this->bottomRightCorner.h )* scalingFactor;
  topRightCorner.v = (this->topRightCorner.v  )* scalingFactor;
  topRightCorner.h = (this->topRightCorner.h   )* scalingFactor;
  topLeftCorner.v = (this->topLeftCorner.v    )* scalingFactor;
  topLeftCorner.h = this->topLeftCorner.h * scalingFactor;

  bottomLeftTEMPpoint = TransformTElementToPano( bottomLeftTEMP,
                 itsCenterPoint);

  tempPoint.v = (theHitPoint.v - offSet.v);
  tempPoint.h = (theHitPoint.h - offSet.h);

  theTransformedPoint  = TransformPanoToTElement( tempPoint, bottomLeftTEMPpoint );


    if(   theTransformedPoint.h  > bottomRightCorner.h)
    {
      theTransformedPoint.h = bottomRightCorner.h;
    }
    if(   theTransformedPoint.h  < bottomLeftCorner.h)
    {
      theTransformedPoint.h = bottomLeftCorner.h;
    }
    if(   theTransformedPoint.v  > bottomLeftCorner.v)
    {
      theTransformedPoint.v = bottomLeftCorner.v;
    }
    if(   theTransformedPoint.v  < topLeftCorner.v)
    {
      theTransformedPoint.v = topLeftCorner.v;
    }

  thisObject = this;

  if ( masterPlateFlag )
  {
    this->masterPlateLocation.v = theTransformedPoint.v / scalingFactor;
    this->masterPlateLocation.h = (theTransformedPoint.h / scalingFactor);
  }
  BUP_DragMasterPlateLocator( thisObject);
}

void CGussetPlate::PlaceYourself( void )
{
  float        scalingFactor;
  CGussetPlate    *thisObject;
  FloatPoint      newbottomLeftTEMP;
  Point        tempPoint;

  FloatPoint      its1stEnd;
  FloatPoint      its2ndEnd;
  float        its1stEndHorz;
  float        its1stEndVert;
  float        its2ndEndHorz;
  float        its2ndEndVert;
  Point        itsCenterPoint;
  FloatPoint      tempCenter;


  if( itsMotherTElement )
  {
    scalingFactor = SCREEN_DPI / (itsTrussPane->theStructureScale);

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

  tempPoint.v = (theHitPoint.v - offSet.v);
  tempPoint.h = (theHitPoint.h - offSet.h);

  newbottomLeftTEMP  = TransformPanoToTElement( tempPoint, itsCenterPoint );


  thisObject = this;

  bottomLeftVOffset = ((float)((newbottomLeftTEMP.v) ) )
              /scalingFactor;
  bottomLeftHOffset = ((float)((newbottomLeftTEMP.h) ) )
              /scalingFactor;

  BUP_DragYourself( thisObject);
}

void CGussetPlate::BUPErase( void )
{
  PenState  pnState;


  GetPenState ( &pnState);/* to save the pen setting */
  PenMode ( patBic );
  BlowUpDraw( this );
  SetPenState ( &pnState);/* to resotre pen settting */

}
void CGussetPlate::BUP_SelectYourself( void )
{
  PenState      pnState;

  FloatPoint      bottomLeftCorner;
  FloatPoint      bottomRightCorner;
  FloatPoint      topRightCorner;
  FloatPoint      topLeftCorner;
  FloatPoint      bottomLeftTEMP;

  Point        bottomLeftCornerPoint;
  Point        bottomRightCornerPoint;
  Point        topRightCornerPoint;
  Point        topLeftCornerPoint;
  Point        bottomLeftTEMPpoint;

  float        scalingFactor;
  CGussetPlate    *thisObject;
  FloatPoint      arrayOfFloatPoints[ 4 ];
  Point        TransformedPoints[ 4 ];

  FloatPoint      its1stEnd;
  FloatPoint      its2ndEnd;
  float        its1stEndHorz;
  float        its1stEndVert;
  float        its2ndEndHorz;
  float        its2ndEndVert;
  Point        itsCenterPoint;
  FloatPoint      tempCenter;


  if( itsMotherTElement )
  {
    scalingFactor = SCREEN_DPI / (itsTrussPane->theStructureScale);

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

  thisObject = this;
  EnforcePhysCondAndDoUpdates( this );


  scalingFactor = SCREEN_DPI / ((( CGussetPane *)(this->
        itsDocument->itsMainPane))->
                  theStructureScale);

  bottomLeftCorner.v = this->bottomLeftCorner.v * scalingFactor;
  bottomLeftCorner.h = this->bottomLeftCorner.h * scalingFactor;
  bottomRightCorner.v = this->bottomRightCorner.v  * scalingFactor;
  bottomRightCorner.h = (this->bottomRightCorner.h )* scalingFactor;
  topRightCorner.v = (this->topRightCorner.v  )* scalingFactor;
  topRightCorner.h = (this->topRightCorner.h   )* scalingFactor;
  topLeftCorner.v = (this->topLeftCorner.v    )* scalingFactor;
  topLeftCorner.h = this->topLeftCorner.h * scalingFactor;

  bottomLeftTEMP.h = bottomLeftHOffset * scalingFactor;
  bottomLeftTEMP.v = bottomLeftVOffset * scalingFactor;


  arrayOfFloatPoints[ 0 ] = bottomLeftCorner;
  arrayOfFloatPoints[ 1 ] = bottomRightCorner;
  arrayOfFloatPoints[ 2 ] = topRightCorner;
  arrayOfFloatPoints[ 3 ] = topLeftCorner;


  bottomLeftTEMPpoint = TransformTElementToPano( bottomLeftTEMP,
                 itsCenterPoint);



  TransformTElementToPanoNew(arrayOfFloatPoints, bottomLeftTEMPpoint, 4,
                TransformedPoints);

  bottomLeftCornerPoint = TransformedPoints[ 0 ];
  bottomRightCornerPoint = TransformedPoints[ 1 ];
  topRightCornerPoint = TransformedPoints[ 2 ];
  topLeftCornerPoint = TransformedPoints[ 3 ];

  DrawResizingHandles( bottomLeftCornerPoint );
  DrawResizingHandles( bottomRightCornerPoint );
  DrawResizingHandles( topRightCornerPoint );
  DrawResizingHandles( topLeftCornerPoint );

  IamSelected = TRUE;

}
void CGussetPlate::BUP_UnSelectYourself( void )
{
  PenState      pnState;

  GetPenState ( &pnState);/* to save the pen setting */
  PenMode ( patBic );
  BUP_SelectYourself();
  SetPenState ( &pnState);/* to resotre pen settting */
  BlowUpDraw( this );
  IamSelected = FALSE;
}


void CGussetPlate::Init_itsMotherTEPolygon( void )
{
  itsMotherTEPolyPointCounter = 0;
  itsMotherTEConnectorArea = 0;
  itsMotherTEIxx = 0;
  itsMotherTEIyy = 0;
  itsMotherTECentroid.h = 0.0;
  itsMotherTECentroid.v = 0.0;
}



void CGussetPlate::Define_itsMotherTEPolygon( Point theHitPoint )
{
  short          whichEndConnected;
  PenState      pnState;
  FloatPoint      masterPlateLocation;
  FloatPoint      bottomLeftTEMP;

  Point        masterPlateLocationPoint;
  Point        bottomLeftTEMPpoint;
  Boolean        thePlateGotSelected;

  float        scalingFactor;
  FloatPoint      aTempFloatPoint;
  Point        aTempPoint;
  FloatPoint      theTransformedPoint;

  FloatPoint      its1stEnd;
  FloatPoint      its2ndEnd;
  float        its1stEndHorz;
  float        its1stEndVert;
  float        its2ndEndHorz;
  float        its2ndEndVert;
  Point        itsCenterPoint;
  FloatPoint      tempCenter;


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

  masterPlateLocation.v = this->masterPlateLocation.v* scalingFactor;
  masterPlateLocation.h = this->masterPlateLocation.h * scalingFactor;

  bottomLeftTEMP.h = this->bottomLeftHOffset * scalingFactor;
  bottomLeftTEMP.v = this->bottomLeftVOffset * scalingFactor;


  bottomLeftTEMPpoint = this->TransformTElementToPano( bottomLeftTEMP,
                itsCenterPoint);


  masterPlateLocationPoint = this->TransformTElementToPano( masterPlateLocation,
                 bottomLeftTEMPpoint);


/*  aTempFloatPoint  = this->TransformPanoToTElement( theHitPoint,
                        masterPlateLocationPoint );
*/  aTempFloatPoint  = this->TransformPanoToGloabal( theHitPoint,
                        masterPlateLocationPoint );


  thePlateGotSelected = this->
              BUP_WhichOneOfUsGotSelected(
                   theHitPoint,this );
  if (thePlateGotSelected && this->masterPlateFlag)
  {
    if( (itsMotherTEPolyPointCounter > 2))
    {
      (( CGussetPane *)(this->
          itsDocument->itsMainPane))->
              ConnectAreaBeingDefined = FALSE;
      Calc_itsMotherTEConnectorAreaProp();
      (( CGussetPane *)(this->
          itsDocument->itsMainPane))->Refresh();

    }
  }
  else
  {
    if(  itsMotherTEPolyPointCounter < MAX_POINT_IN_POLYGON )
    {
      aTempFloatPoint.v = aTempFloatPoint.v / scalingFactor;
      aTempFloatPoint.h = aTempFloatPoint.h / scalingFactor;
      itsMotherTEPolygon[ itsMotherTEPolyPointCounter ] = aTempFloatPoint;
      itsMotherTEPolyPointCounter++;
      Draw_itsMotherTEPolygon();
    }
    else
    {
      (( CGussetPane *)(this->
          itsDocument->itsMainPane))->
              ConnectAreaBeingDefined = FALSE;
      Calc_itsMotherTEConnectorAreaProp();
      (( CGussetPane *)(this->
          itsDocument->itsMainPane))->Refresh();
    }
  }
}

void CGussetPlate::Draw_itsMotherTEPolygon( void )
{
  short          whichEndConnected;
  PenState      pnState;
  FloatPoint      masterPlateLocation;
  FloatPoint      bottomLeftTEMP;

  Point        masterPlateLocationPoint;
  Point        bottomLeftTEMPpoint;
  Point        tempPoint;

  float        scalingFactor;
  int          loopCounter;
  FloatPoint      Local1stEndPolygon[ MAX_POINT_IN_POLYGON ];
  FloatPoint      tempFloatPoint;
  FloatPoint      tempFloatPoint2;

  FloatPoint      its1stEnd;
  FloatPoint      its2ndEnd;
  float        its1stEndHorz;
  float        its1stEndVert;
  float        its2ndEndHorz;
  float        its2ndEndVert;
  Point        itsCenterPoint;
  FloatPoint      tempCenter;


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

  masterPlateLocation.v = this->masterPlateLocation.v* scalingFactor;
  masterPlateLocation.h = this->masterPlateLocation.h * scalingFactor;

  bottomLeftTEMP.h = this->bottomLeftHOffset * scalingFactor;
  bottomLeftTEMP.v = this->bottomLeftVOffset * scalingFactor;

  bottomLeftTEMPpoint = this->TransformTElementToPano( bottomLeftTEMP,
                itsCenterPoint);

  masterPlateLocationPoint = this->TransformTElementToPano( masterPlateLocation,
                 bottomLeftTEMPpoint);

  MoveTo( masterPlateLocationPoint.h,  masterPlateLocationPoint.v);

  for( loopCounter = 0; loopCounter < itsMotherTEPolyPointCounter; loopCounter++)
  {
    tempFloatPoint = itsMotherTEPolygon[ loopCounter ];
    tempFloatPoint2.v = tempFloatPoint.v * scalingFactor;
    tempFloatPoint2.h = tempFloatPoint.h * scalingFactor;
    Local1stEndPolygon[ loopCounter ] = tempFloatPoint2;
  }
  for( loopCounter = 0; loopCounter < itsMotherTEPolyPointCounter; loopCounter++)
  {
/*    tempPoint = this->TransformTElementToPano(
          Local1stEndPolygon[ loopCounter ],
               masterPlateLocationPoint);
*/    tempPoint = this->TransformGlobalToPano(
          Local1stEndPolygon[ loopCounter ],
               masterPlateLocationPoint);

    GetPenState ( &pnState);/* to save the pen setting */
    PenSize( 2,2 );
    LineTo( tempPoint.h,  tempPoint.v);
    SetPenState ( &pnState);/* to resotre pen settting */
    MoveTo( tempPoint.h,  tempPoint.v);

    DrawResizingHandles( tempPoint );
  }
      /* draw line to masterloc. only when connection is */
      /* no longer beingdefined */
  if ( !((( CGussetPane *)(this->
          itsDocument->itsMainPane))->
              ConnectAreaBeingDefined )  )
  {
    GetPenState ( &pnState);/* to save the pen setting */
    PenSize( 2,2 );
    LineTo( masterPlateLocationPoint.h,
                   masterPlateLocationPoint.v);
    SetPenState ( &pnState);/* to resotre pen settting */
    tempFloatPoint2.v = itsMotherTECentroid.v * scalingFactor;
    tempFloatPoint2.h = itsMotherTECentroid.h * scalingFactor;
    tempPoint = this->TransformGlobalToPano(
          tempFloatPoint2,
               masterPlateLocationPoint);
    DrawResizingHandles( tempPoint );
  }
}

Boolean CGussetPlate::ConnectYourselfToTE(  CTrussElementObject
                          *theSelectedTEObject )
{
  if ( ( theSelectedTEObject->WhoAreYou() == aWoodElement ) )
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
  else
    return FALSE;
}




