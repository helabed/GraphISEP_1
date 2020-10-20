/****
 * CRegularWoodTElement2.c
 *
 *  CRegularWoodTElement object class for a typical CTrussPane class, Part 2
 *
 ****/
#include "CRegularWoodTElement.phs"
#include "CClusterOfAbstracts.h"

/*** Global Variables ***/

extern  CBartender *gBartender;
extern   short    gClicks;
extern  FILE      *Debug_Info_Out_File;
extern  FILE      *Wood_Out_File;
extern  long      NumberOfMembersLoaded;
extern  float      LargestYValue;




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



Boolean CRegularWoodTElement::BUP_WhichOneOfUsGotSelected( Point aPoint,
              CGussetPlate  *thePlate )
{
  float    offSetLength;
  float    TElementLength;
  Point    its2ndEnd;
  Point    its1stEnd;
  float    scalingFactor;
  short          whichEndConnected;
  Point          its1stStretchedEnd;
  Point          its2ndStretchedEnd;

  FloatPoint        its1stEndTip;
  FloatPoint        its1stEndRightCorner;
  FloatPoint        its1stEndLeftCorner;
  FloatPoint        its2ndEndTip;
  FloatPoint        its2ndEndRightCorner;
  FloatPoint        its2ndEndLeftCorner;

  GrafPtr          oldPort;
  GrafPort        privatePort;
  int            bits;
  BitMap          map;
  PenState         pnState;

  scalingFactor = SCREEN_DPI / ((( CGussetPane *)(thePlate->
        itsDocument->itsMainPane))->
                  theStructureScale);

  its1stEndTip.v = this->its1stEndTip.v * scalingFactor;
  its1stEndTip.h = this->its1stEndTip.h * scalingFactor;
  its1stEndRightCorner.v = this->its1stEndRightCorner.v * scalingFactor;
  its1stEndRightCorner.h = this->its1stEndRightCorner.h * scalingFactor;
  its1stEndLeftCorner.v = this->its1stEndLeftCorner.v * scalingFactor;
  its1stEndLeftCorner.h = this->its1stEndLeftCorner.h * scalingFactor;
  its2ndEndTip.v = this->its2ndEndTip.v * scalingFactor;
  its2ndEndTip.h = (this->its2ndEndTip.h + WhatIsYourLength()) * scalingFactor;
  its2ndEndRightCorner.v = this->its2ndEndRightCorner.v * scalingFactor;
  its2ndEndRightCorner.h = (this->its2ndEndRightCorner.h + WhatIsYourLength()) * scalingFactor;
  its2ndEndLeftCorner.v = this->its2ndEndLeftCorner.v * scalingFactor;
  its2ndEndLeftCorner.h = (this->its2ndEndLeftCorner.h + WhatIsYourLength()) * scalingFactor;


  its1stEnd.v = this->its1stEnd.v + (int) (its1stEndVOffset * scalingFactor);
  its1stEnd.h = this->its1stEnd.h + (int) (its1stEndHOffset * scalingFactor);
  its2ndEnd.v = this->its2ndEnd.v + (int) (its2ndEndVOffset * scalingFactor);
  its2ndEnd.h = this->its2ndEnd.h + (int) (its2ndEndHOffset * scalingFactor);

  whichEndConnected = WhichEndIsConnected( thePlate );

  if( whichEndConnected == 1 )
  {

    if ( ( HitSamePart( (TransformTElementToPano(its1stEndTip, its1stEnd)),
        aPoint, &offSet  ) ) )
    {
      precisionCuttingInProgress = TRUE;
      placingInProgress = FALSE;
      ReSizingInProgress = FALSE;
      MovingInProgress = FALSE;

      its1stEndTipFlag = TRUE;
      its1stEndRightCornerFlag = FALSE;
      its1stEndLeftCornerFlag = FALSE;
      its2ndEndTipFlag = FALSE;
      its2ndEndRightCornerFlag = FALSE;
      its2ndEndLeftCornerFlag = FALSE;

      itsCenterPointFlag = FALSE;
      its1stEndFlag = FALSE;
      its2ndEndFlag = FALSE;

      return ( TRUE );
    }
    else if ( ( HitSamePart( (TransformTElementToPano(its1stEndRightCorner,
        its1stEnd)),  aPoint, &offSet  ) ) )
    {
      precisionCuttingInProgress = TRUE;
      placingInProgress = FALSE;
      ReSizingInProgress = FALSE;
      MovingInProgress = FALSE;

      its1stEndTipFlag = FALSE;
      its1stEndRightCornerFlag = TRUE;
      its1stEndLeftCornerFlag = FALSE;
      its2ndEndTipFlag = FALSE;
      its2ndEndRightCornerFlag = FALSE;
      its2ndEndLeftCornerFlag = FALSE;

      itsCenterPointFlag = FALSE;
      its1stEndFlag = FALSE;
      its2ndEndFlag = FALSE;

      return ( TRUE );
    }
    else if ( ( HitSamePart( (TransformTElementToPano(its1stEndLeftCorner,
        its1stEnd)),  aPoint, &offSet  ) ) )
    {
      precisionCuttingInProgress = TRUE;
      placingInProgress = FALSE;
      ReSizingInProgress = FALSE;
      MovingInProgress = FALSE;

      its1stEndTipFlag = FALSE;
      its1stEndRightCornerFlag = FALSE;
      its1stEndLeftCornerFlag = TRUE;
      its2ndEndTipFlag = FALSE;
      its2ndEndRightCornerFlag = FALSE;
      its2ndEndLeftCornerFlag = FALSE;

      itsCenterPointFlag = FALSE;
      its1stEndFlag = FALSE;
      its2ndEndFlag = FALSE;

      return ( TRUE );
    }
    else if ( ( HitSamePart( its1stEnd, aPoint, &offSet  ) ) )
    {
      precisionCuttingInProgress = FALSE;
      placingInProgress = TRUE;
      ReSizingInProgress = FALSE;
      MovingInProgress = FALSE;

      its1stEndTipFlag = FALSE;
      its1stEndRightCornerFlag = FALSE;
      its1stEndLeftCornerFlag = FALSE;
      its2ndEndTipFlag = FALSE;
      its2ndEndRightCornerFlag = FALSE;
      its2ndEndLeftCornerFlag = FALSE;

      itsCenterPointFlag = FALSE;
      its1stEndFlag = TRUE;
      its2ndEndFlag = FALSE;

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
      BlowUpDraw( itsGussetPlate );
      SetPenState ( &pnState);/* to resotre pen settting */

      if( odd( bits ) )
      {

        offSet.v = aPoint.v - its1stEnd.v;
        offSet.h = aPoint.h - its1stEnd.h;

        precisionCuttingInProgress = FALSE;
        placingInProgress = TRUE;
        ReSizingInProgress = FALSE;
        MovingInProgress = FALSE;

        its1stEndTipFlag = FALSE;
        its1stEndRightCornerFlag = FALSE;
        its1stEndLeftCornerFlag = FALSE;
        its2ndEndTipFlag = FALSE;
        its2ndEndRightCornerFlag = FALSE;
        its2ndEndLeftCornerFlag = FALSE;

        itsCenterPointFlag = FALSE;
        its1stEndFlag = TRUE;
        its2ndEndFlag = FALSE;

        SetPort( oldPort );
        ClosePort( &privatePort );
        return( TRUE );
      }
      else
      {
        SetPort( oldPort );
        ClosePort( &privatePort );
        return( FALSE );
      }
    }
  }
  else if( whichEndConnected == 2)
  {
    if ( ( HitSamePart( (TransformTElementToPano(its2ndEndTip, itsOtherEnd)),
        aPoint, &offSet  ) ) )
    {
      precisionCuttingInProgress = TRUE;
      placingInProgress = FALSE;
      ReSizingInProgress = FALSE;
      MovingInProgress = FALSE;

      its1stEndTipFlag = FALSE;
      its1stEndRightCornerFlag = FALSE;
      its1stEndLeftCornerFlag = FALSE;
      its2ndEndTipFlag = TRUE;
      its2ndEndRightCornerFlag = FALSE;
      its2ndEndLeftCornerFlag = FALSE;

      itsCenterPointFlag = FALSE;
      its1stEndFlag = FALSE;
      its2ndEndFlag = FALSE;

      return ( TRUE );
    }
    else if ( ( HitSamePart( (TransformTElementToPano(its2ndEndRightCorner,
        itsOtherEnd)),  aPoint, &offSet  ) ) )
    {
      precisionCuttingInProgress = TRUE;
      placingInProgress = FALSE;
      ReSizingInProgress = FALSE;
      MovingInProgress = FALSE;

      its1stEndTipFlag = FALSE;
      its1stEndRightCornerFlag = FALSE;
      its1stEndLeftCornerFlag = FALSE;
      its2ndEndTipFlag = FALSE;
      its2ndEndRightCornerFlag = TRUE;
      its2ndEndLeftCornerFlag = FALSE;

      itsCenterPointFlag = FALSE;
      its1stEndFlag = FALSE;
      its2ndEndFlag = FALSE;

      return ( TRUE );
    }
    else if ( ( HitSamePart( (TransformTElementToPano(its2ndEndLeftCorner,
        itsOtherEnd)),  aPoint, &offSet  ) ) )
    {
      precisionCuttingInProgress = TRUE;
      placingInProgress = FALSE;
      ReSizingInProgress = FALSE;
      MovingInProgress = FALSE;

      its1stEndTipFlag = FALSE;
      its1stEndRightCornerFlag = FALSE;
      its1stEndLeftCornerFlag = FALSE;
      its2ndEndTipFlag = FALSE;
      its2ndEndRightCornerFlag = FALSE;
      its2ndEndLeftCornerFlag = TRUE;

      itsCenterPointFlag = FALSE;
      its1stEndFlag = FALSE;
      its2ndEndFlag = FALSE;

      return ( TRUE );
    }
    else if ( ( HitSamePart( its2ndEnd, aPoint, &offSet ) ) )
    {
      precisionCuttingInProgress = FALSE;
      placingInProgress = TRUE;
      ReSizingInProgress = FALSE;
      MovingInProgress = FALSE;

      its1stEndTipFlag = FALSE;
      its1stEndRightCornerFlag = FALSE;
      its1stEndLeftCornerFlag = FALSE;
      its2ndEndTipFlag = FALSE;
      its2ndEndRightCornerFlag = FALSE;
      its2ndEndLeftCornerFlag = FALSE;

      itsCenterPointFlag = FALSE;
      its1stEndFlag = FALSE;
      its2ndEndFlag = TRUE;
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
      BlowUpDraw( itsGussetPlate );
      SetPenState ( &pnState);/* to resotre pen settting */

      if( odd( bits ) )
      {
        offSet.v = aPoint.v - its2ndEnd.v;
        offSet.h = aPoint.h - its2ndEnd.h;

        precisionCuttingInProgress = FALSE;
        placingInProgress = TRUE;
        ReSizingInProgress = FALSE;
        MovingInProgress = FALSE;

        its1stEndTipFlag = FALSE;
        its1stEndRightCornerFlag = FALSE;
        its1stEndLeftCornerFlag = FALSE;
        its2ndEndTipFlag = FALSE;
        its2ndEndRightCornerFlag = FALSE;
        its2ndEndLeftCornerFlag = FALSE;

        itsCenterPointFlag = FALSE;
        its1stEndFlag = FALSE;
        its2ndEndFlag = TRUE;

        SetPort( oldPort );
        ClosePort( &privatePort );
        return( TRUE );
      }
      else
      {
        SetPort( oldPort );
        ClosePort( &privatePort );
        return( FALSE );
      }
    }

  }
  else if( whichEndConnected == 0)
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
    BlowUpDraw( itsGussetPlate );
    SetPenState ( &pnState);/* to resotre pen settting */

    if( odd( bits ) )
    {
      offSet.v = aPoint.v - its2ndEnd.v;
      offSet.h = aPoint.h - its2ndEnd.h;

      precisionCuttingInProgress = FALSE;
      placingInProgress = TRUE;
      ReSizingInProgress = FALSE;
      MovingInProgress = FALSE;

      its1stEndTipFlag = FALSE;
      its1stEndRightCornerFlag = FALSE;
      its1stEndLeftCornerFlag = FALSE;
      its2ndEndTipFlag = FALSE;
      its2ndEndRightCornerFlag = FALSE;
      its2ndEndLeftCornerFlag = FALSE;

      itsCenterPointFlag = FALSE;
      its1stEndFlag = FALSE;
      its2ndEndFlag = TRUE;

      SetPort( oldPort );
      ClosePort( &privatePort );
      return( TRUE );
    }
    else
    {
      SetPort( oldPort );
      ClosePort( &privatePort );
      return( FALSE );
    }
  }

  return FALSE;
}

void CRegularWoodTElement::UpDateObject( void )
{
  if ( ReSizingInProgress )
  {
    ResizeYourself();
  }
  else if( (( ! the1stEndConnected) && ( ! the2ndEndConnected ) ) &&
              MovingInProgress )
  {
    MoveYourself();
  }
  else if( precisionCuttingInProgress )
  {
    PrecisionCutYourself();
  }
  else if( placingInProgress )
  {
    PlaceYourself();
  }
}

      static void BUP_DragYourself( CRegularWoodTElement *thisObject,
                  CGussetPlate *itsGussetPlate )
      {
        PenState     pnState;

        GetPenState ( &pnState);/* to save the pen setting */
        PenMode ( patXor );
        thisObject->BlowUpDraw( itsGussetPlate );
        SetPenState ( &pnState);/* to resotre pen settting */
      }




void CRegularWoodTElement::PrecisionCutYourself( void )
{
  Point    its2ndEnd;
  Point    its1stEnd;
  float    scalingFactor;
  Boolean    whichEndConnected;
  CRegularWoodTElement  *thisObject;
  FloatPoint        its1stEndTip;
  FloatPoint        its1stEndRightCorner;
  FloatPoint        its1stEndLeftCorner;
  FloatPoint        its2ndEndTip;
  FloatPoint        its2ndEndRightCorner;
  FloatPoint        its2ndEndLeftCorner;
  FloatPoint        theTransformedPoint;
  Point          tempPoint;

  thisObject = this;

  scalingFactor = SCREEN_DPI / ((( CGussetPane *)(itsGussetPlate->
        itsDocument->itsMainPane))->
                  theStructureScale);

  its1stEndTip.v = this->its1stEndTip.v * scalingFactor;
  its1stEndTip.h = this->its1stEndTip.h * scalingFactor;
  its1stEndRightCorner.v = this->its1stEndRightCorner.v * scalingFactor;
  its1stEndRightCorner.h = this->its1stEndRightCorner.h * scalingFactor;
  its1stEndLeftCorner.v = this->its1stEndLeftCorner.v * scalingFactor;
  its1stEndLeftCorner.h = this->its1stEndLeftCorner.h * scalingFactor;
  its2ndEndTip.v = this->its2ndEndTip.v * scalingFactor;
  its2ndEndTip.h = (this->its2ndEndTip.h + WhatIsYourLength()) * scalingFactor;
  its2ndEndRightCorner.v = this->its2ndEndRightCorner.v * scalingFactor;
  its2ndEndRightCorner.h = (this->its2ndEndRightCorner.h + WhatIsYourLength())
                   * scalingFactor;
  its2ndEndLeftCorner.v = this->its2ndEndLeftCorner.v * scalingFactor;
  its2ndEndLeftCorner.h = (this->its2ndEndLeftCorner.h + WhatIsYourLength())
                  * scalingFactor;

  its1stEnd.v = this->its1stEnd.v + (int) (its1stEndVOffset * scalingFactor);
  its1stEnd.h = this->its1stEnd.h + (int) (its1stEndHOffset * scalingFactor);
  its2ndEnd.v = this->its2ndEnd.v + (int) (its2ndEndVOffset * scalingFactor);
  its2ndEnd.h = this->its2ndEnd.h + (int) (its2ndEndHOffset * scalingFactor);


  tempPoint.v = (theHitPoint.v - offSet.v);
  tempPoint.h = (theHitPoint.h - offSet.h);

  theTransformedPoint  = TransformPanoToTElement( tempPoint, its1stEnd );

  if( its1stEndTipFlag )
  {
    this->its1stEndTip.v = theTransformedPoint.v / scalingFactor;
    this->its1stEndTip.h = theTransformedPoint.h / scalingFactor;

  }

  else if( its1stEndRightCornerFlag )
  {
    this->its1stEndRightCorner.v = theTransformedPoint.v / scalingFactor;
    this->its1stEndRightCorner.h = theTransformedPoint.h / scalingFactor;

  }

  else if ( its1stEndLeftCornerFlag )
  {
    this->its1stEndLeftCorner.v = theTransformedPoint.v / scalingFactor;
    this->its1stEndLeftCorner.h = theTransformedPoint.h / scalingFactor;

  }
  else if( its2ndEndTipFlag )
  {
    theTransformedPoint  = TransformPanoToTElement( tempPoint, itsOtherEnd );

    this->its2ndEndTip.v = theTransformedPoint.v / scalingFactor;
    this->its2ndEndTip.h = (theTransformedPoint.h / scalingFactor) -
                  WhatIsYourLength();
  }

  else if( its2ndEndRightCornerFlag )
  {

    theTransformedPoint  = TransformPanoToTElement( tempPoint, itsOtherEnd );

    this->its2ndEndRightCorner.v = theTransformedPoint.v / scalingFactor;
    this->its2ndEndRightCorner.h = (theTransformedPoint.h / scalingFactor) -
                  WhatIsYourLength();
  }

  else if ( its2ndEndLeftCornerFlag )
  {

    theTransformedPoint  = TransformPanoToTElement( tempPoint, itsOtherEnd );

    this->its2ndEndLeftCorner.v = theTransformedPoint.v / scalingFactor;
    this->its2ndEndLeftCorner.h = (theTransformedPoint.h / scalingFactor) -
                  WhatIsYourLength();
  }
  BUP_DragYourself( thisObject, itsGussetPlate);
}


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
      theObject->its1stEndHOffset =  theObject->its1stEndHOffset - (((float)(tempCenter.h - oldCenter.h)));
      theObject->its1stEndVOffset =  theObject->its1stEndVOffset - (((float)(tempCenter.v - oldCenter.v)));
    }
    else if ( whichEndConnected == 2 )
    {
      theObject->its2ndEndHOffset = theObject->its2ndEndHOffset - (((float)(tempCenter.h - oldCenter.h)));
      theObject->its2ndEndVOffset = theObject->its2ndEndVOffset - (((float)(tempCenter.v - oldCenter.v)));
    }

  }


  static void Update_Offsets( CGussetPlate *theObject, CRegularWoodTElement
                              **thisWoodObjectPtr)
  {
    WoodElementAndPlate    thePlateAndWoodMember;

    thePlateAndWoodMember.thePlate = theObject;
    thePlateAndWoodMember.theWoodElement = (*thisWoodObjectPtr);

    if ( theObject->theNodeTElements && theObject->theNodeTElements->numItems )
    {
      theObject->theNodeTElements->DoForEach1( Update_WoodOffsets, (long)(&thePlateAndWoodMember) );
      }
  }



void CRegularWoodTElement::PlaceYourself( void )
{
  Point    its2ndEnd;
  Point    its1stEnd;
  float    scalingFactor;
  short    whichEndConnected;
  CRegularWoodTElement  *thisObject;
  Point          its1stStretchedEnd;
  Point          its2ndStretchedEnd;

  thisObject = this;

  scalingFactor = SCREEN_DPI / ((( CGussetPane *)(itsGussetPlate->
        itsDocument->itsMainPane))->
                  theStructureScale);

  its1stEnd.v = this->its1stEnd.v + (int) (its1stEndVOffset * scalingFactor);
  its1stEnd.h = this->its1stEnd.h + (int) (its1stEndHOffset * scalingFactor);
  its2ndEnd.v = this->its2ndEnd.v + (int) (its2ndEndVOffset * scalingFactor);
  its2ndEnd.h = this->its2ndEnd.h + (int) (its2ndEndHOffset * scalingFactor);


  whichEndConnected = WhichEndIsConnected( itsGussetPlate );



  if( whichEndConnected == 1 )
  {
  its1stEndVOffset = ((float)((theHitPoint.v - offSet.v)-(this->its1stEnd.v) ) )
              /scalingFactor;
  its1stEndHOffset = ((float)((theHitPoint.h - offSet.h)-(this->its1stEnd.h) ) )
              /scalingFactor;

/*  if( theTENodes && (theTENodes->numItems) )
  {
    theTENodes->DoForEach1( Update_Offsets, (long)(&thisObject) );


  }
*/
  }
  else if( whichEndConnected == 2 )
  {
  its2ndEndVOffset = ((float)((theHitPoint.v - offSet.v)-(this->its2ndEnd.v) ) )
              /scalingFactor;
  its2ndEndHOffset = ((float)((theHitPoint.h - offSet.h)-(this->its2ndEnd.h) ) )
              /scalingFactor;
  }
  else if( whichEndConnected == 0) /* the plate's mother TE */
  {
    StretchBothEnds( &its1stStretchedEnd, &its2ndStretchedEnd ,
           itsGussetPlate);

    if ( its1stEndFlag )
    {

    }
    else if ( its2ndEndFlag )
    {

    }

  }
  BUP_DragYourself( thisObject, itsGussetPlate);
}

void CRegularWoodTElement::BUPErase( void )
{
  PenState  pnState;


  GetPenState ( &pnState);/* to save the pen setting */
  PenMode ( patBic );
  BlowUpDraw( itsGussetPlate );
  SetPenState ( &pnState);/* to resotre pen settting */
}


void CRegularWoodTElement::BUP_SelectYourself( void )
{
  FloatPoint        its1stEndTip;
  FloatPoint        its1stEndRightCorner;
  FloatPoint        its1stEndLeftCorner;
  FloatPoint        its2ndEndTip;
  FloatPoint        its2ndEndRightCorner;
  FloatPoint        its2ndEndLeftCorner;
  Point        its1stEndTipPoint;
  Point        its1stEndRightCornerPoint;
  Point        its1stEndLeftCornerPoint;
  Point        its2ndEndTipPoint;
  Point        its2ndEndRightCornerPoint;
  Point        its2ndEndLeftCornerPoint;
  float          scalingFactor;
  CRegularWoodTElement  *thisObject;
  short          whichEndConnected;
  Point          OLDits1stEnd;
  Point          its1stStretchedEnd;
  Point          its2ndStretchedEnd;
  FloatPoint        arrayOfFloatPoints[ 6 ];
  Point          TransformedPoints[ 6 ];


  thisObject = this;

  scalingFactor = SCREEN_DPI / ((( CGussetPane *)(itsGussetPlate->
        itsDocument->itsMainPane))->
                  theStructureScale);

  its1stEndTip.v = this->its1stEndTip.v * scalingFactor;
  its1stEndTip.h = this->its1stEndTip.h * scalingFactor;
  its1stEndRightCorner.v = this->its1stEndRightCorner.v * scalingFactor;
  its1stEndRightCorner.h = this->its1stEndRightCorner.h * scalingFactor;
  its1stEndLeftCorner.v = this->its1stEndLeftCorner.v * scalingFactor;
  its1stEndLeftCorner.h = this->its1stEndLeftCorner.h * scalingFactor;
  its2ndEndTip.v = this->its2ndEndTip.v * scalingFactor;
  its2ndEndTip.h = (this->its2ndEndTip.h + WhatIsYourLength()) * scalingFactor;
  its2ndEndRightCorner.v = this->its2ndEndRightCorner.v * scalingFactor;
  its2ndEndRightCorner.h = (this->its2ndEndRightCorner.h + WhatIsYourLength()) * scalingFactor;
  its2ndEndLeftCorner.v = this->its2ndEndLeftCorner.v * scalingFactor;
  its2ndEndLeftCorner.h = (this->its2ndEndLeftCorner.h + WhatIsYourLength()) * scalingFactor;

  arrayOfFloatPoints[ 0 ] = its1stEndTip;
  arrayOfFloatPoints[ 1 ] = its1stEndRightCorner;
  arrayOfFloatPoints[ 2 ] = its1stEndLeftCorner;
  arrayOfFloatPoints[ 3 ] = its2ndEndTip;
  arrayOfFloatPoints[ 4 ] = its2ndEndRightCorner;
  arrayOfFloatPoints[ 5 ] = its2ndEndLeftCorner;

  whichEndConnected = WhichEndIsConnected( itsGussetPlate );

  StretchTheOtherEnd( whichEndConnected,
                WhatIsYourLength(), itsGussetPlate);


  if( whichEndConnected == 1 )
  {
    its1stStretchedEnd.h = (its1stEnd.h+ (int) (its1stEndHOffset * scalingFactor));
    its1stStretchedEnd.v = (its1stEnd.v+ (int) (its1stEndVOffset * scalingFactor));

    TransformTElementToPanoNew(arrayOfFloatPoints, its1stStretchedEnd, 6,
                  TransformedPoints);

    its1stEndTipPoint = TransformedPoints[ 0 ];
    its1stEndRightCornerPoint = TransformedPoints[ 1 ];
    its1stEndLeftCornerPoint = TransformedPoints[ 2 ];
    its2ndEndTipPoint = TransformedPoints[ 3 ];
    its2ndEndRightCornerPoint = TransformedPoints[ 4 ];
    its2ndEndLeftCornerPoint = TransformedPoints[ 5 ];

  }
  else if( whichEndConnected == 2)
  {
    TransformTElementToPanoNew(arrayOfFloatPoints, itsOtherEnd, 6,
                  TransformedPoints);

    its1stEndTipPoint = TransformedPoints[ 0 ];
    its1stEndRightCornerPoint = TransformedPoints[ 1 ];
    its1stEndLeftCornerPoint = TransformedPoints[ 2 ];
    its2ndEndTipPoint = TransformedPoints[ 3 ];
    its2ndEndRightCornerPoint = TransformedPoints[ 4 ];
    its2ndEndLeftCornerPoint = TransformedPoints[ 5 ];

  }
  else if( whichEndConnected == 0) /* the plate's mother TE */
  {
    StretchBothEnds( &its1stStretchedEnd, &its2ndStretchedEnd ,
           itsGussetPlate);

    TransformTElementToPanoNew(arrayOfFloatPoints, its1stStretchedEnd, 6,
                  TransformedPoints);

    its1stEndTipPoint = TransformedPoints[ 0 ];
    its1stEndRightCornerPoint = TransformedPoints[ 1 ];
    its1stEndLeftCornerPoint = TransformedPoints[ 2 ];
    its2ndEndTipPoint = TransformedPoints[ 3 ];
    its2ndEndRightCornerPoint = TransformedPoints[ 4 ];
    its2ndEndLeftCornerPoint = TransformedPoints[ 5 ];

  }
  DrawResizingHandles( its1stEndTipPoint );
  DrawResizingHandles( its1stEndLeftCornerPoint );
  DrawResizingHandles( its2ndEndLeftCornerPoint );
  DrawResizingHandles( its2ndEndTipPoint );
  DrawResizingHandles( its2ndEndRightCornerPoint );
  DrawResizingHandles( its1stEndRightCornerPoint );

  IamSelected = TRUE;
}
void CRegularWoodTElement::BUP_UnSelectYourself( void )
{
  PenState      pnState;

  GetPenState ( &pnState);/* to save the pen setting */
  PenMode ( patBic );
  BUP_SelectYourself();
  SetPenState ( &pnState);/* to resotre pen settting */
  BlowUpDraw( itsGussetPlate );
  IamSelected = FALSE;
}
void CRegularWoodTElement::Init_ConnectorPolygon( CGussetPlate *thePlate )
{
  short          whichEndConnected;

  whichEndConnected = WhichEndIsConnected( thePlate );

  if( whichEndConnected == 1 )
  {
    firstEndPolyPointCounter = 0;
    firstEndConnectorArea = 0;
    firstEndIxx = 0;
    firstEndIyy = 0;
    firstEndCentroid.h =  0;
    firstEndCentroid.v =  0;

  }
  else if( whichEndConnected == 2 )
  {
    secondEndPolyPointCounter = 0;
    secondEndConnectorArea = 0;
    secondEndIxx = 0;
    secondEndIyy = 0;
    secondEndCentroid.h =  0;
    secondEndCentroid.v =  0;
  }
  else if( whichEndConnected == 0 )
  {
    thePlate->Init_itsMotherTEPolygon();
  }
}
void CRegularWoodTElement::Define_ConnectorPolygon( CGussetPlate *thePlate,
                      Point theHitPoint  )
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
  CRegularWoodTElement  *theWoodTE;


  if( thePlate->itsMotherTElement  )
  {
    theWoodTE = ((CRegularWoodTElement *)thePlate->itsMotherTElement);
    scalingFactor = SCREEN_DPI / (itsTrussPane->theStructureScale);

    scalingFactor = SCREEN_DPI / ((( CGussetPane *)(thePlate->
          itsDocument->itsMainPane))->
                    theStructureScale);
    its1stEnd.v = ((float)theWoodTE->its1stEnd.v) + (theWoodTE->its1stEndVOffset * scalingFactor);
    its1stEnd.h = ((float)theWoodTE->its1stEnd.h) + (theWoodTE->its1stEndHOffset * scalingFactor);
    its2ndEnd.v = ((float)theWoodTE->its2ndEnd.v) + (theWoodTE->its2ndEndVOffset * scalingFactor);
    its2ndEnd.h = ((float)theWoodTE->its2ndEnd.h) + (theWoodTE->its2ndEndHOffset * scalingFactor);


    its1stEndHorz = (its1stEnd.h * itsTrussPane->theStructureScale / SCREEN_DPI );
    its1stEndVert = (its1stEnd.v * itsTrussPane->theStructureScale / SCREEN_DPI );
    its2ndEndHorz = (its2ndEnd.h * itsTrussPane->theStructureScale / SCREEN_DPI );
    its2ndEndVert = (its2ndEnd.v * itsTrussPane->theStructureScale / SCREEN_DPI );


    tempCenter.h = ((( thePlate->TElementConnectionRatio *
            (its2ndEndHorz -  its1stEndHorz ) ) +  its1stEndHorz ));
    tempCenter.v = ((( thePlate->TElementConnectionRatio *
            (its2ndEndVert -  its1stEndVert ) ) +  its1stEndVert ));

    itsCenterPoint.h = ((int)((tempCenter.h) * SCREEN_DPI / itsTrussPane->theStructureScale));
    itsCenterPoint.v = ((int)((tempCenter.v) * SCREEN_DPI / itsTrussPane->theStructureScale));


  }
  else
  {
    itsCenterPoint = thePlate->itsCenterPoint;
  }

  scalingFactor = SCREEN_DPI / ((( CGussetPane *)(thePlate->
        itsDocument->itsMainPane))->
                  theStructureScale);

  masterPlateLocation.v = thePlate->masterPlateLocation.v* scalingFactor;
  masterPlateLocation.h = thePlate->masterPlateLocation.h * scalingFactor;

  bottomLeftTEMP.h = thePlate->bottomLeftHOffset * scalingFactor;
  bottomLeftTEMP.v = thePlate->bottomLeftVOffset * scalingFactor;


  bottomLeftTEMPpoint = thePlate->TransformTElementToPano( bottomLeftTEMP,
                 itsCenterPoint);


  masterPlateLocationPoint = thePlate->TransformTElementToPano( masterPlateLocation,
                 bottomLeftTEMPpoint);


  aTempFloatPoint  = thePlate->TransformPanoToGloabal( theHitPoint,
                        masterPlateLocationPoint );


  whichEndConnected = WhichEndIsConnected( thePlate );

  if( whichEndConnected == 1 )
  {
    thePlateGotSelected = thePlate->
                BUP_WhichOneOfUsGotSelected(
                     theHitPoint,thePlate );
    if (thePlateGotSelected && thePlate->masterPlateFlag)
    {
      if( (firstEndPolyPointCounter > 2))
      {
        (( CGussetPane *)(thePlate->
            itsDocument->itsMainPane))->
                ConnectAreaBeingDefined = FALSE;
        CalcConnectorAreaProp();
        (( CGussetPane *)(thePlate->
            itsDocument->itsMainPane))->Refresh();

      }
    }
    else
    {
      if(  firstEndPolyPointCounter < MAX_POINT_IN_POLYGON )
      {
        aTempFloatPoint.v = aTempFloatPoint.v / scalingFactor;
        aTempFloatPoint.h = aTempFloatPoint.h / scalingFactor;
        its1stEndPolygon[ firstEndPolyPointCounter ] = aTempFloatPoint;
        firstEndPolyPointCounter++;
        DrawItsPolygon( thePlate );
      }
      else
      {
        (( CGussetPane *)(thePlate->
            itsDocument->itsMainPane))->
                ConnectAreaBeingDefined = FALSE;
        CalcConnectorAreaProp();
        (( CGussetPane *)(thePlate->
            itsDocument->itsMainPane))->Refresh();
      }
    }
  }
  else if( whichEndConnected == 2 )
  {
    thePlateGotSelected = thePlate->
                BUP_WhichOneOfUsGotSelected(
                     theHitPoint,thePlate );
    if (thePlateGotSelected && thePlate->masterPlateFlag)
    {
      if( (secondEndPolyPointCounter > 2))
      {
        (( CGussetPane *)(thePlate->
            itsDocument->itsMainPane))->
                ConnectAreaBeingDefined = FALSE;
        CalcConnectorAreaProp();
        (( CGussetPane *)(thePlate->
            itsDocument->itsMainPane))->Refresh();

      }
    }
    else
    {
      if(  secondEndPolyPointCounter < MAX_POINT_IN_POLYGON )
      {
        aTempFloatPoint.v = aTempFloatPoint.v / scalingFactor;
        aTempFloatPoint.h = aTempFloatPoint.h / scalingFactor;
        its2ndEndPolygon[ secondEndPolyPointCounter ] = aTempFloatPoint;
        secondEndPolyPointCounter++;
        DrawItsPolygon( thePlate );
      }
      else
      {
        (( CGussetPane *)(thePlate->
            itsDocument->itsMainPane))->
                ConnectAreaBeingDefined = FALSE;
        CalcConnectorAreaProp();
        (( CGussetPane *)(thePlate->
            itsDocument->itsMainPane))->Refresh();
      }
    }

  }
  else if( whichEndConnected == 0 )
  {
    thePlate->Define_itsMotherTEPolygon( theHitPoint );
  }
}

void CRegularWoodTElement::DrawItsPolygon( struct CGussetPlate *thePlate)
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
  CRegularWoodTElement  *theWoodTE;

  if( thePlate->itsMotherTElement  )
  {
    theWoodTE = ((CRegularWoodTElement *)thePlate->itsMotherTElement);
    scalingFactor = SCREEN_DPI / (itsTrussPane->theStructureScale);

    scalingFactor = SCREEN_DPI / ((( CGussetPane *)(thePlate->
          itsDocument->itsMainPane))->
                    theStructureScale);
    its1stEnd.v = ((float)theWoodTE->its1stEnd.v) + (theWoodTE->its1stEndVOffset * scalingFactor);
    its1stEnd.h = ((float)theWoodTE->its1stEnd.h) + (theWoodTE->its1stEndHOffset * scalingFactor);
    its2ndEnd.v = ((float)theWoodTE->its2ndEnd.v) + (theWoodTE->its2ndEndVOffset * scalingFactor);
    its2ndEnd.h = ((float)theWoodTE->its2ndEnd.h) + (theWoodTE->its2ndEndHOffset * scalingFactor);


    its1stEndHorz = (its1stEnd.h * itsTrussPane->theStructureScale / SCREEN_DPI );
    its1stEndVert = (its1stEnd.v * itsTrussPane->theStructureScale / SCREEN_DPI );
    its2ndEndHorz = (its2ndEnd.h * itsTrussPane->theStructureScale / SCREEN_DPI );
    its2ndEndVert = (its2ndEnd.v * itsTrussPane->theStructureScale / SCREEN_DPI );


    tempCenter.h = ((( thePlate->TElementConnectionRatio *
            (its2ndEndHorz -  its1stEndHorz ) ) +  its1stEndHorz ));
    tempCenter.v = ((( thePlate->TElementConnectionRatio *
            (its2ndEndVert -  its1stEndVert ) ) +  its1stEndVert ));

    itsCenterPoint.h = ((int)((tempCenter.h) * SCREEN_DPI / itsTrussPane->theStructureScale));
    itsCenterPoint.v = ((int)((tempCenter.v) * SCREEN_DPI / itsTrussPane->theStructureScale));


  }
  else
  {
    itsCenterPoint = thePlate->itsCenterPoint;
  }

  scalingFactor = SCREEN_DPI / ((( CGussetPane *)(thePlate->
        itsDocument->itsMainPane))->
                  theStructureScale);

  masterPlateLocation.v = thePlate->masterPlateLocation.v* scalingFactor;
  masterPlateLocation.h = thePlate->masterPlateLocation.h * scalingFactor;

  bottomLeftTEMP.h = thePlate->bottomLeftHOffset * scalingFactor;
  bottomLeftTEMP.v = thePlate->bottomLeftVOffset * scalingFactor;


  bottomLeftTEMPpoint = thePlate->TransformTElementToPano( bottomLeftTEMP,
                itsCenterPoint);

  masterPlateLocationPoint = thePlate->TransformTElementToPano( masterPlateLocation,
                 bottomLeftTEMPpoint);

  MoveTo( masterPlateLocationPoint.h,  masterPlateLocationPoint.v);

  whichEndConnected = WhichEndIsConnected( thePlate );

  if( whichEndConnected == 1 )
  {
    for( loopCounter = 0; loopCounter < firstEndPolyPointCounter; loopCounter++)
    {
      tempFloatPoint = its1stEndPolygon[ loopCounter ];
      tempFloatPoint2.v = tempFloatPoint.v * scalingFactor;
      tempFloatPoint2.h = tempFloatPoint.h * scalingFactor;
      Local1stEndPolygon[ loopCounter ] = tempFloatPoint2;
    }
    for( loopCounter = 0; loopCounter < firstEndPolyPointCounter; loopCounter++)
    {
      tempPoint = thePlate->TransformGlobalToPano(
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
    if ( !((( CGussetPane *)(thePlate->
            itsDocument->itsMainPane))->
                ConnectAreaBeingDefined )  )
    {
      GetPenState ( &pnState);/* to save the pen setting */
      PenSize( 2,2 );
      LineTo( masterPlateLocationPoint.h,
                     masterPlateLocationPoint.v);
      SetPenState ( &pnState);/* to resotre pen settting */

      tempFloatPoint2.v = firstEndCentroid.v * scalingFactor;
      tempFloatPoint2.h = firstEndCentroid.h * scalingFactor;
      tempPoint = thePlate->TransformGlobalToPano(
            tempFloatPoint2,
                 masterPlateLocationPoint);
      DrawResizingHandles( tempPoint );
    }

  }
  else if( whichEndConnected == 2 )
  {
    for( loopCounter = 0; loopCounter < secondEndPolyPointCounter; loopCounter++)
    {
      tempFloatPoint = its2ndEndPolygon[ loopCounter ];
      tempFloatPoint2.v = tempFloatPoint.v * scalingFactor;
      tempFloatPoint2.h = tempFloatPoint.h * scalingFactor;
      Local1stEndPolygon[ loopCounter ] = tempFloatPoint2;
    }
    for( loopCounter = 0; loopCounter < secondEndPolyPointCounter; loopCounter++)
    {
      tempPoint = thePlate->TransformGlobalToPano(
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
    if ( !((( CGussetPane *)(thePlate->
            itsDocument->itsMainPane))->
                ConnectAreaBeingDefined )  )
    {
      GetPenState ( &pnState);/* to save the pen setting */
      PenSize( 2,2 );
      LineTo( masterPlateLocationPoint.h,
                     masterPlateLocationPoint.v);
      SetPenState ( &pnState);/* to resotre pen settting */

      tempFloatPoint2.v = secondEndCentroid.v * scalingFactor;
      tempFloatPoint2.h = secondEndCentroid.h * scalingFactor;
      tempPoint = thePlate->TransformGlobalToPano(
            tempFloatPoint2,
                 masterPlateLocationPoint);
      DrawResizingHandles( tempPoint );
    }
  }
  else if( whichEndConnected == 0 )
  {
    thePlate->Draw_itsMotherTEPolygon();
  }
}

Boolean CRegularWoodTElement::ConnectYourselfToNode(   CNodeObject
                      *theSelectedNodeObject )
{
  inherited::ConnectYourselfToNode( theSelectedNodeObject );
}

void CRegularWoodTElement::CalcConnectorAreaProp( void )
{
  short        whichEndConnected;
  int          loopCounter;
  FloatPoint      tempFloatPoint1;
  FloatPoint      tempFloatPoint2;
  float        tempSumation1 = 0;
  float        tempSumation2 = 0;
  float        tempConncArea = 0;
  FloatPoint    its1stEndPolygon[ MAX_POINT_IN_POLYGON + 2];
  FloatPoint    its2ndEndPolygon[ MAX_POINT_IN_POLYGON + 2];
    int        firstEndPolyPointCounter;
    int        secondEndPolyPointCounter;
  FloatPoint        one;
  FloatPoint        two;
  FloatPoint        dumy;


  firstEndPolyPointCounter = this->firstEndPolyPointCounter + 2;
  secondEndPolyPointCounter = this->secondEndPolyPointCounter  + 2;

  whichEndConnected = WhichEndIsConnected( itsGussetPlate );

  if( whichEndConnected == 1 )
  {
    (its1stEndPolygon[ 0 ]).h = 0.0;
    (its1stEndPolygon[ 0 ]).v = 0.0;
    for( loopCounter = 0; loopCounter < (firstEndPolyPointCounter - 1);
                        loopCounter++)
    {
      dumy = this->its1stEndPolygon[ loopCounter ];
      its1stEndPolygon[ loopCounter + 1 ] = dumy;
    }
    (its1stEndPolygon[ (firstEndPolyPointCounter - 1) ]).h = 0.0;
    (its1stEndPolygon[ (firstEndPolyPointCounter - 1) ]).v = 0.0;


    for( loopCounter = 0; loopCounter < (firstEndPolyPointCounter - 1);
                        loopCounter++)
    {
      one = its1stEndPolygon[ loopCounter ];
      two = its1stEndPolygon[ (loopCounter + 1 )];

      tempConncArea =  ( ( one.h - two.h ) * ( one.v + two.v ) / 2);
      firstEndConnectorArea +=  tempConncArea;
    }

    for( loopCounter = 0; loopCounter < (firstEndPolyPointCounter - 1);
                        loopCounter++)
    {
      one = its1stEndPolygon[ loopCounter ];
      two = its1stEndPolygon[ (loopCounter + 1 )];

      firstEndCentroid.h += ( ( two.v - one.v ) * ( one.h * one.h + one.h * two.h + two.h * two.h ) ) / ( 6 * firstEndConnectorArea);
      firstEndCentroid.v += ( ( one.h - two.h ) * ( one.v * one.v + one.v * two.v + two.v * two.v ) ) / ( 6 * firstEndConnectorArea);


      firstEndIxx +=  ( ( one.h - two.h ) * ( one.v * one.v * one.v + one.v * one.v * two.v + one.v * two.v * two.v + two.v * two.v * two.v ) ) / 12;
      firstEndIyy +=  ( ( two.v - one.v ) * ( one.h * one.h * one.h + one.h * one.h * two.h + one.h * two.h * two.h + two.h * two.h * two.h ) ) / 12;
    }

    firstEndIxx = Abs( firstEndIxx - (firstEndConnectorArea * firstEndCentroid.v * firstEndCentroid.v) );
    firstEndIyy = Abs( firstEndIyy - (firstEndConnectorArea * firstEndCentroid.h * firstEndCentroid.h) );
    firstEndConnectorArea = Abs( firstEndConnectorArea );
  }
  else if( whichEndConnected == 2 )
  {
    (its2ndEndPolygon[ 0 ]).h = 0.0;
    (its2ndEndPolygon[ 0 ]).v = 0.0;
    for( loopCounter = 0; loopCounter < (secondEndPolyPointCounter - 1);
                        loopCounter++)
    {
      dumy = this->its2ndEndPolygon[ loopCounter ];
      its2ndEndPolygon[ loopCounter + 1 ] = dumy;
    }
    (its2ndEndPolygon[ (secondEndPolyPointCounter - 1) ]).h = 0.0;
    (its2ndEndPolygon[ (secondEndPolyPointCounter - 1) ]).v = 0.0;


    for( loopCounter = 0; loopCounter < (secondEndPolyPointCounter - 1);
                        loopCounter++)
    {
      one = its2ndEndPolygon[ loopCounter ];
      two = its2ndEndPolygon[ (loopCounter + 1 )];

      tempConncArea =  ( ( one.h - two.h ) * ( one.v + two.v ) / 2);
      secondEndConnectorArea +=  tempConncArea;
    }

    for( loopCounter = 0; loopCounter < (secondEndPolyPointCounter - 1);
                        loopCounter++)
    {
      one = its2ndEndPolygon[ loopCounter ];
      two = its2ndEndPolygon[ (loopCounter + 1 )];

      secondEndCentroid.h += ( ( two.v - one.v ) * ( one.h * one.h + one.h * two.h + two.h * two.h ) ) / ( 6 * secondEndConnectorArea);
      secondEndCentroid.v += ( ( one.h - two.h ) * ( one.v * one.v + one.v * two.v + two.v * two.v ) ) / ( 6 * secondEndConnectorArea);


      secondEndIxx +=  ( ( one.h - two.h ) * ( one.v * one.v * one.v + one.v * one.v * two.v + one.v * two.v * two.v + two.v * two.v * two.v ) ) / 12;
      secondEndIyy +=  ( ( two.v - one.v ) * ( one.h * one.h * one.h + one.h * one.h * two.h + one.h * two.h * two.h + two.h * two.h * two.h ) ) / 12;
    }

    secondEndIxx = Abs( secondEndIxx - (secondEndConnectorArea * secondEndCentroid.v * secondEndCentroid.v) );
    secondEndIyy = Abs( secondEndIyy - (secondEndConnectorArea * secondEndCentroid.h * secondEndCentroid.h) );
    secondEndConnectorArea = Abs( secondEndConnectorArea );

  }
  else if( whichEndConnected == 0 )
  {
    itsGussetPlate->Calc_itsMotherTEConnectorAreaProp();
  }
}

    static Boolean Is_CN_TEConnRatioLarger( CNodeObject
        *theObject, CNodeObject **theNodeToBeTestedPtr)
    {
      if( theObject->TElementConnectionRatio <
              (*theNodeToBeTestedPtr)->TElementConnectionRatio)
      {
        return TRUE;
      }
      else
        return FALSE;
    }

    static void Create_OrderedList( CNodeObject
        *theObject, CList **theListPtr)
    {
      CNodeObject   *theNodeBefore;
      CNodeObject    *theCurrentNode;

      theCurrentNode = theObject;

      if ((*theListPtr)->IsEmpty() )
      {
        (*theListPtr)->Add( theCurrentNode );
      }
      else
      {      /* Current Node (CN) */
        theNodeBefore = ((CNodeObject *)(*theListPtr)->LastSuccess1(
          Is_CN_TEConnRatioLarger, (long)( &theCurrentNode ) ));
        if( theNodeBefore )
        {
          (*theListPtr)->InsertAfter( theCurrentNode, theNodeBefore );
        }
        else
        {
          (*theListPtr)->Prepend( theCurrentNode );
        }
      }
    }

void  CRegularWoodTElement::PrintDebugInfo( void )
{
  long      numberOfSections = 0L;
  CList      *orderedNodeList;
  CGussetPlate  *aMiddleNode;
  long      sectionCounter = 0L;

  fprintf( Debug_Info_Out_File, "\n\nI am Wood member = %ld\n",
                          theObjectNumber  );


  if( NodesAreConnected && theTENodes->numItems )
  {
    orderedNodeList = new( CList );
    orderedNodeList->IList();
    theTENodes->DoForEach1(
        Create_OrderedList, (long)(&orderedNodeList) );

    fprintf( Debug_Info_Out_File, "---------------------------\n"  );

    numberOfSections = (theTENodes->numItems) + 1;
    if ( numberOfSections == 2 )
    {
      fprintf( Debug_Info_Out_File, "\nI am Wood member = %ld\n",
                          theObjectNumber  );
      fprintf( Debug_Info_Out_File, "its1stEndGlobalNumber = %ld\n",
                          its1stEndGlobalNumber  );
      fprintf( Debug_Info_Out_File, "its2ndEndGlobalNumber = %ld\n",
        ((CGussetPlate *)(orderedNodeList->FirstItem()))->
              itsMotherTEGlobalNumber );

      fprintf( Debug_Info_Out_File, "\nI am Wood member = %ld\n",
                          theObjectNumber+1  );
      fprintf( Debug_Info_Out_File, "its1stEndGlobalNumber = %ld\n",
        ((CGussetPlate *)(orderedNodeList->FirstItem()))->
              itsMotherTEGlobalNumber );
      fprintf( Debug_Info_Out_File, "its2ndEndGlobalNumber = %ld\n",
                      its2ndEndGlobalNumber );

    }
    else
    {
      fprintf( Debug_Info_Out_File, "\nI am Wood member = %ld\n",
                          theObjectNumber  );
      fprintf( Debug_Info_Out_File, "its1stEndGlobalNumber = %ld\n",
                          its1stEndGlobalNumber  );

      aMiddleNode = ((CGussetPlate*)(orderedNodeList->FirstItem()));
      fprintf( Debug_Info_Out_File, "its2ndEndGlobalNumber = %ld\n",
                aMiddleNode->itsMotherTEGlobalNumber );
      orderedNodeList->Remove( aMiddleNode );

      for( sectionCounter = 1; sectionCounter < (numberOfSections - 1);
                sectionCounter++ )
      {
        fprintf( Debug_Info_Out_File, "\nI am Wood member = %ld\n",
                      theObjectNumber+sectionCounter  );
        fprintf( Debug_Info_Out_File, "its1stEndGlobalNumber = %ld\n",
                  aMiddleNode->itsMotherTEGlobalNumber  );
        aMiddleNode = ((CGussetPlate*)(orderedNodeList->FirstItem()));
        fprintf( Debug_Info_Out_File, "its2ndEndGlobalNumber = %ld\n",
                  aMiddleNode->itsMotherTEGlobalNumber );
        orderedNodeList->Remove( aMiddleNode );

      }

      fprintf( Debug_Info_Out_File, "\nI am Wood member = %ld\n",
                    theObjectNumber+(numberOfSections-1)  );
      fprintf( Debug_Info_Out_File, "its1stEndGlobalNumber = %ld\n",
                  aMiddleNode->itsMotherTEGlobalNumber  );
      fprintf( Debug_Info_Out_File, "its2ndEndGlobalNumber = %ld\n",
                      its2ndEndGlobalNumber );

    }
    orderedNodeList->Dispose();
  }
  else
  {
    fprintf( Debug_Info_Out_File, "its1stEndGlobalNumber = %ld\n",
                            its1stEndGlobalNumber  );
    fprintf( Debug_Info_Out_File, "its2ndEndGlobalNumber = %ld\n",
                            its2ndEndGlobalNumber  );
  }
}
void  CRegularWoodTElement::PrintFileStatics( void )
{
}
void  CRegularWoodTElement::PrintFileFireWood( void )
{
  long      numberOfSections = 0L;
  CList      *orderedNodeList;
  CGussetPlate  *aMiddleNode;
  CGussetPlate  *previousMiddleNode;
  long      sectionCounter = 0L;
  FloatPoint    its1stEnd;
  FloatPoint    its2ndEnd;
  float      scalingFactor;
  float      theta;
  float       itsCosine;
  float       itsSine;
  float      its1stEndHorz;
  float      its1stEndVert;
  float      its2ndEndHorz;
  float      its2ndEndVert;

  scalingFactor = SCREEN_DPI / (itsTrussPane->theStructureScale);

  its1stEnd.v = ((float)this->its1stEnd.v) +  (its1stEndVOffset * scalingFactor);
  its1stEnd.h = ((float)this->its1stEnd.h) +  (its1stEndHOffset * scalingFactor);
  its2ndEnd.v = ((float)this->its2ndEnd.v) +  (its2ndEndVOffset * scalingFactor);
  its2ndEnd.h = ((float)this->its2ndEnd.h) +  (its2ndEndHOffset * scalingFactor);

  GetSineAndCosine( &theta, &itsCosine, &itsSine);
  theta = (float) ( ( theta)  / PI * 180.0 );

  its1stEndHorz = (its1stEnd.h * itsTrussPane->theStructureScale / SCREEN_DPI );
  its1stEndVert = (its1stEnd.v * itsTrussPane->theStructureScale / SCREEN_DPI );
  its2ndEndHorz = (its2ndEnd.h * itsTrussPane->theStructureScale / SCREEN_DPI );
  its2ndEndVert = (its2ndEnd.v * itsTrussPane->theStructureScale / SCREEN_DPI );

  if( NodesAreConnected && theTENodes->numItems )
  {
    orderedNodeList = new( CList );
    orderedNodeList->IList();
    theTENodes->DoForEach1(
        Create_OrderedList, (long)(&orderedNodeList) );

    numberOfSections = (theTENodes->numItems) + 1;
    if ( numberOfSections == 2 )
    {
      aMiddleNode = ((CGussetPlate *)(orderedNodeList->FirstItem()));
      fprintf( Wood_Out_File, "\n%ld\t", its1stEndGlobalNumber  );
      fprintf( Wood_Out_File, "%ld\t", aMiddleNode->itsMotherTEGlobalNumber );
      fprintf( Wood_Out_File, "%ld\t", theObjectNumber );
      fprintf( Wood_Out_File, "%f\t",  360.0 - theta );
      fprintf( Wood_Out_File, "%f\t", its1stEndHorz );
      fprintf( Wood_Out_File, "%f\t", LargestYValue - its1stEndVert );
      fprintf( Wood_Out_File, "%f\t", ((aMiddleNode->TElementConnectionRatio *
            (its2ndEndHorz -  its1stEndHorz ) ) +  its1stEndHorz ));
      fprintf( Wood_Out_File, "%f\t",LargestYValue - (((aMiddleNode->TElementConnectionRatio *
            (its2ndEndVert -  its1stEndVert ) ) +  its1stEndVert ) ) );

      fprintf( Wood_Out_File, "\n%ld\t", aMiddleNode->itsMotherTEGlobalNumber );
      fprintf( Wood_Out_File, "%ld\t", its2ndEndGlobalNumber );
      fprintf( Wood_Out_File, "%ld\t", theObjectNumber+1 );
      fprintf( Wood_Out_File, "%f\t", 360.0 - theta );
      fprintf( Wood_Out_File, "%f\t", ((aMiddleNode->TElementConnectionRatio *
            (its2ndEndHorz -  its1stEndHorz ) ) +  its1stEndHorz ) );
      fprintf( Wood_Out_File, "%f\t",LargestYValue - (((aMiddleNode->TElementConnectionRatio *
            (its2ndEndVert -  its1stEndVert ) ) +  its1stEndVert ) ) );
      fprintf( Wood_Out_File, "%f\t", its2ndEndHorz );
      fprintf( Wood_Out_File, "%f\t", LargestYValue - its2ndEndVert );
      }
    else
    {
      fprintf( Wood_Out_File, "\n%ld\t", its1stEndGlobalNumber  );
      aMiddleNode = ((CGussetPlate*)(orderedNodeList->FirstItem()));
      fprintf( Wood_Out_File, "%ld\t", aMiddleNode->itsMotherTEGlobalNumber );
      fprintf( Wood_Out_File, "%ld\t", theObjectNumber  );
      fprintf( Wood_Out_File, "%f\t", 360.0 - theta );
      fprintf( Wood_Out_File, "%f\t", its1stEndHorz );
      fprintf( Wood_Out_File, "%f\t", LargestYValue - its1stEndVert );
      fprintf( Wood_Out_File, "%f\t", ((aMiddleNode->TElementConnectionRatio *
            (its2ndEndHorz -  its1stEndHorz ) ) +  its1stEndHorz ));
      fprintf( Wood_Out_File, "%f\t",LargestYValue - (((aMiddleNode->TElementConnectionRatio *
            (its2ndEndVert -  its1stEndVert ) ) +  its1stEndVert ) ) );
      orderedNodeList->Remove( aMiddleNode );

      for( sectionCounter = 1; sectionCounter < (numberOfSections - 1);
                sectionCounter++ )
      {
        previousMiddleNode = aMiddleNode;
        fprintf( Wood_Out_File, "\n%ld\t", previousMiddleNode->itsMotherTEGlobalNumber  );
        aMiddleNode = ((CGussetPlate*)(orderedNodeList->FirstItem()));
        fprintf( Wood_Out_File, "%ld\t", aMiddleNode->itsMotherTEGlobalNumber );
        orderedNodeList->Remove( aMiddleNode );
        fprintf( Wood_Out_File, "%ld\t", theObjectNumber+sectionCounter  );
        fprintf( Wood_Out_File, "%f\t", 360.0 - theta );
        fprintf( Wood_Out_File, "%f\t", ((previousMiddleNode->TElementConnectionRatio *
              (its2ndEndHorz -  its1stEndHorz ) ) +  its1stEndHorz ));
        fprintf( Wood_Out_File, "%f\t",LargestYValue - (((previousMiddleNode->TElementConnectionRatio *
              (its2ndEndVert -  its1stEndVert ) ) +  its1stEndVert ) ) );
        fprintf( Wood_Out_File, "%f\t", ((aMiddleNode->TElementConnectionRatio *
              (its2ndEndHorz -  its1stEndHorz ) ) +  its1stEndHorz ));
        fprintf( Wood_Out_File, "%f\t",LargestYValue - (((aMiddleNode->TElementConnectionRatio *
              (its2ndEndVert -  its1stEndVert ) ) +  its1stEndVert ) ) );
      }

      fprintf( Wood_Out_File, "\n%ld\t", aMiddleNode->itsMotherTEGlobalNumber  );
      fprintf( Wood_Out_File, "%ld\t", its2ndEndGlobalNumber );
      fprintf( Wood_Out_File, "%ld\t", theObjectNumber+(numberOfSections-1)  );
      fprintf( Wood_Out_File, "%f\t", 360.0 - theta );
      fprintf( Wood_Out_File, "%f\t", ((aMiddleNode->TElementConnectionRatio *
            (its2ndEndHorz -  its1stEndHorz ) ) +  its1stEndHorz ));
      fprintf( Wood_Out_File, "%f\t",LargestYValue - (((aMiddleNode->TElementConnectionRatio *
            (its2ndEndVert -  its1stEndVert ) ) +  its1stEndVert ) ) );
      fprintf( Wood_Out_File, "%f\t", its2ndEndHorz );
      fprintf( Wood_Out_File, "%f\t",   LargestYValue - its2ndEndVert );
    }
    orderedNodeList->Dispose();
  }
  else
  {
    fprintf( Wood_Out_File, "\n%ld\t", its1stEndGlobalNumber  );
    fprintf( Wood_Out_File, "%ld\t", its2ndEndGlobalNumber  );
    fprintf( Wood_Out_File, "%ld\t", theObjectNumber  );
    fprintf( Wood_Out_File, "%f\t", 360.0 - theta );
    fprintf( Wood_Out_File, "%f\t", its1stEndHorz );
    fprintf( Wood_Out_File, "%f\t", LargestYValue - its1stEndVert );
    fprintf( Wood_Out_File, "%f\t", its2ndEndHorz );
    fprintf( Wood_Out_File, "%f\t", LargestYValue - its2ndEndVert );
  }
}

void  CRegularWoodTElement::PrintFileWood1( void )
{
  long      numberOfSections = 0L;
  CList      *orderedNodeList;
  CGussetPlate  *aMiddleNode;
  CGussetPlate  *previousMiddleNode;
  long      sectionCounter = 0L;


  if( NodesAreConnected && theTENodes->numItems )
  {
    orderedNodeList = new( CList );
    orderedNodeList->IList();
    theTENodes->DoForEach1(
        Create_OrderedList, (long)(&orderedNodeList) );

    numberOfSections = (theTENodes->numItems) + 1;
    if ( numberOfSections == 2 )
    {
      fprintf( Wood_Out_File, "\n%f\t", CrossSectionHeight );
      fprintf( Wood_Out_File, "%f\t", CrossSectionWidth );
      fprintf( Wood_Out_File, "%f\t", E );
      fprintf( Wood_Out_File, "%f\t", BendingStrength );
      fprintf( Wood_Out_File, "%f\t", TensileStrength );
      fprintf( Wood_Out_File, "%f\t", CompressiveStrength );

      fprintf( Wood_Out_File, "\n%f\t", CrossSectionHeight );
      fprintf( Wood_Out_File, "%f\t", CrossSectionWidth );
      fprintf( Wood_Out_File, "%f\t", E );
      fprintf( Wood_Out_File, "%f\t", BendingStrength );
      fprintf( Wood_Out_File, "%f\t", TensileStrength );
      fprintf( Wood_Out_File, "%f\t", CompressiveStrength );
    }
    else
    {
      fprintf( Wood_Out_File, "\n%f\t", CrossSectionHeight );
      fprintf( Wood_Out_File, "%f\t", CrossSectionWidth );
      fprintf( Wood_Out_File, "%f\t", E );
      fprintf( Wood_Out_File, "%f\t", BendingStrength );
      fprintf( Wood_Out_File, "%f\t", TensileStrength );
      fprintf( Wood_Out_File, "%f\t", CompressiveStrength );

      for( sectionCounter = 1; sectionCounter < (numberOfSections - 1);
                sectionCounter++ )
      {
        fprintf( Wood_Out_File, "\n%f\t", CrossSectionHeight );
        fprintf( Wood_Out_File, "%f\t", CrossSectionWidth );
        fprintf( Wood_Out_File, "%f\t", E );
        fprintf( Wood_Out_File, "%f\t", BendingStrength );
        fprintf( Wood_Out_File, "%f\t", TensileStrength );
        fprintf( Wood_Out_File, "%f\t", CompressiveStrength );
      }
      fprintf( Wood_Out_File, "\n%f\t", CrossSectionHeight );
      fprintf( Wood_Out_File, "%f\t", CrossSectionWidth );
      fprintf( Wood_Out_File, "%f\t", E );
      fprintf( Wood_Out_File, "%f\t", BendingStrength );
      fprintf( Wood_Out_File, "%f\t", TensileStrength );
      fprintf( Wood_Out_File, "%f\t", CompressiveStrength );
    }
    orderedNodeList->Dispose();
  }
  else
  {
    fprintf( Wood_Out_File, "\n%f\t", CrossSectionHeight );
    fprintf( Wood_Out_File, "%f\t", CrossSectionWidth );
    fprintf( Wood_Out_File, "%f\t", E );
    fprintf( Wood_Out_File, "%f\t", BendingStrength );
    fprintf( Wood_Out_File, "%f\t", TensileStrength );
    fprintf( Wood_Out_File, "%f\t", CompressiveStrength );
  }
}


  static void Perform_DeleteYourself( CAbstractObject  *theObject )
  {
    theObject->DeleteYourself();
  }

  static void Copy_Cluster( CAbstractObject *theObject, CClusterOfAbstracts
          **theTEMP_Cluster_ptr)
  {
         (*theTEMP_Cluster_ptr)->Add( theObject );
  }

  static void Spread_And_Disconnect( CQuadrelateralObject
                    *theObject, CRegularWoodTElement **theWoodObjPtr)
  {
    CTrussElementObject    *oldTE;
    Boolean          connectionPerformed=FALSE;

    switch( theObject->WhoAreYou() )
    {
      case aContinuousLoad:
      case aContinuousGravityLoad:
      case aContUniformWindLoad:
      case aContWindLoad:
      case aContinuousMoment:
        theObject->DeleteYourself();

        break;
      case aContUniformGravityLoad:
        oldTE = theObject->itsTElement;
        theObject->DisconnectYourself();
        theObject->UnSelectYourself();
        theObject->Erase();

        theObject->loadAlongAllMember = TRUE;
        connectionPerformed =  theObject->ConnectYourselfToTE( oldTE );

        if( ! connectionPerformed )
          SysBeep(2);
        break;
    }
  }

  static void Upddate_ConcLandMNumber( CConcLoadObject *theObject,
                    WoodAndConcLandMnum *concLandMNum_and_ThisObjectPTR)
  {
    if  (   ( theObject->TElementConnectionRatio <
            (*concLandMNum_and_ThisObjectPTR).secondEndTEConnectionRatio ) &&
        ( theObject->TElementConnectionRatio >=
            (*concLandMNum_and_ThisObjectPTR).firstEndTEConnectionRatio ) )
    {
      switch( theObject->WhoAreYou() )
      {
        case aConcentratedLoad:
          ((*concLandMNum_and_ThisObjectPTR).theConcLNumber)++;
          break;

        case aConcentratedMoment:
          ((*concLandMNum_and_ThisObjectPTR).theConcMNumber)++;
          break;

      }
    }
  }


void  CRegularWoodTElement::PrintFileWood2( void )
{
  long          numberOfSections = 0L;
  CList          *orderedNodeList;
  CGussetPlate      *aMiddleNode;
  CGussetPlate      *previousMiddleNode;
  long          sectionCounter = 0L;
  CRegularWoodTElement  *thisObject;
  CClusterOfAbstracts   *theTEMP_Cluster;
  WoodAndConcLandMnum    concLandMNum_and_ThisObject;
  long            oldConcLNumber;
  long            oldConcMNumber;

  thisObject = this;
  concLandMNum_and_ThisObject.theConcLNumber = 0;
  concLandMNum_and_ThisObject.theConcMNumber = 0;
      /* these are defaults values for members with no nodes */
  concLandMNum_and_ThisObject.firstEndTEConnectionRatio = 0;
  concLandMNum_and_ThisObject.secondEndTEConnectionRatio = 1.01;
  concLandMNum_and_ThisObject.theWoodElement = thisObject;

  if( ContLandMAreConnected && theTEContLoadsAndMoments->numItems )
  {
    theTEMP_Cluster = new( CClusterOfAbstracts );
    theTEMP_Cluster->ICluster();
    theTEContLoadsAndMoments->
          DoForEach1( Copy_Cluster, (long)(&theTEMP_Cluster) );
    theTEMP_Cluster->DoForEach( Spread_And_Disconnect );
    theTEMP_Cluster->Dispose();
  }
  if( ContLandMAreConnected && theTEContLoadsAndMoments->numItems )
  {
    if( NodesAreConnected && theTENodes->numItems )
    {
      orderedNodeList = new( CList );
      orderedNodeList->IList();
      theTENodes->DoForEach1(
          Create_OrderedList, (long)(&orderedNodeList) );

      numberOfSections = (theTENodes->numItems) + 1;
      if ( numberOfSections == 2 )
      {
        NumberOfMembersLoaded++;
        NumberOfMembersLoaded++;
      }
      else
      {
        NumberOfMembersLoaded++;
        for( sectionCounter = 1; sectionCounter < (numberOfSections - 1);
                  sectionCounter++ )
        {
          NumberOfMembersLoaded++;
        }
        NumberOfMembersLoaded++;
      }
      orderedNodeList->Dispose();
    }
    else
    {
        NumberOfMembersLoaded++;
    }
  }
  else if( ConcLandMAreConnected && theTEConcLoadsAndMoments->numItems )
  {
    if( NodesAreConnected && theTENodes->numItems )
    {
      orderedNodeList = new( CList );
      orderedNodeList->IList();
      theTENodes->DoForEach1(
          Create_OrderedList, (long)(&orderedNodeList) );

      numberOfSections = (theTENodes->numItems) + 1;
      if ( numberOfSections == 2 )
      {
        aMiddleNode = ((CGussetPlate *)(orderedNodeList->FirstItem()));
        oldConcLNumber = concLandMNum_and_ThisObject.theConcLNumber;
        oldConcMNumber = concLandMNum_and_ThisObject.theConcMNumber;
        concLandMNum_and_ThisObject.firstEndTEConnectionRatio = 0;
        concLandMNum_and_ThisObject.secondEndTEConnectionRatio =
                        aMiddleNode->TElementConnectionRatio;
        theTEConcLoadsAndMoments->
          DoForEach1( Upddate_ConcLandMNumber, (long)(&concLandMNum_and_ThisObject) );
        if( (concLandMNum_and_ThisObject.theConcLNumber > oldConcLNumber ) ||
            (concLandMNum_and_ThisObject.theConcMNumber > oldConcMNumber )    )
        {
          NumberOfMembersLoaded++;
        }

        oldConcLNumber = concLandMNum_and_ThisObject.theConcLNumber;
        oldConcMNumber = concLandMNum_and_ThisObject.theConcMNumber;
        concLandMNum_and_ThisObject.firstEndTEConnectionRatio =
                        aMiddleNode->TElementConnectionRatio;
        concLandMNum_and_ThisObject.secondEndTEConnectionRatio = 1.01;
        theTEConcLoadsAndMoments->
          DoForEach1( Upddate_ConcLandMNumber, (long)(&concLandMNum_and_ThisObject) );
        if( (concLandMNum_and_ThisObject.theConcLNumber > oldConcLNumber ) ||
            (concLandMNum_and_ThisObject.theConcMNumber > oldConcMNumber )    )
        {
          NumberOfMembersLoaded++;
        }
      }
      else
      {
        aMiddleNode = ((CGussetPlate*)(orderedNodeList->FirstItem()));

        oldConcLNumber = concLandMNum_and_ThisObject.theConcLNumber;
        oldConcMNumber = concLandMNum_and_ThisObject.theConcMNumber;
        concLandMNum_and_ThisObject.firstEndTEConnectionRatio = 0;
        concLandMNum_and_ThisObject.secondEndTEConnectionRatio =
                        aMiddleNode->TElementConnectionRatio;
        theTEConcLoadsAndMoments->
          DoForEach1( Upddate_ConcLandMNumber, (long)(&concLandMNum_and_ThisObject) );
        if( (concLandMNum_and_ThisObject.theConcLNumber > oldConcLNumber ) ||
            (concLandMNum_and_ThisObject.theConcMNumber > oldConcMNumber )    )
        {
          NumberOfMembersLoaded++;
        }

        orderedNodeList->Remove( aMiddleNode );

        for( sectionCounter = 1; sectionCounter < (numberOfSections - 1);
                  sectionCounter++ )
        {
          previousMiddleNode = aMiddleNode;
          aMiddleNode = ((CGussetPlate*)(orderedNodeList->FirstItem()));
          oldConcLNumber = concLandMNum_and_ThisObject.theConcLNumber;
          oldConcMNumber = concLandMNum_and_ThisObject.theConcMNumber;
          concLandMNum_and_ThisObject.firstEndTEConnectionRatio =
                        previousMiddleNode->TElementConnectionRatio;
          concLandMNum_and_ThisObject.secondEndTEConnectionRatio =
                          aMiddleNode->TElementConnectionRatio;
          theTEConcLoadsAndMoments->
            DoForEach1( Upddate_ConcLandMNumber, (long)(&concLandMNum_and_ThisObject) );
          if( (concLandMNum_and_ThisObject.theConcLNumber > oldConcLNumber ) ||
              (concLandMNum_and_ThisObject.theConcMNumber > oldConcMNumber )    )
          {
            NumberOfMembersLoaded++;
          }

          orderedNodeList->Remove( aMiddleNode );

        }

        oldConcLNumber = concLandMNum_and_ThisObject.theConcLNumber;
        oldConcMNumber = concLandMNum_and_ThisObject.theConcMNumber;
        concLandMNum_and_ThisObject.firstEndTEConnectionRatio =
                        aMiddleNode->TElementConnectionRatio;
        concLandMNum_and_ThisObject.secondEndTEConnectionRatio = 1.01;
        theTEConcLoadsAndMoments->
          DoForEach1( Upddate_ConcLandMNumber, (long)(&concLandMNum_and_ThisObject) );
        if( (concLandMNum_and_ThisObject.theConcLNumber > oldConcLNumber ) ||
            (concLandMNum_and_ThisObject.theConcMNumber > oldConcMNumber )    )
        {
          NumberOfMembersLoaded++;
        }

      }
      orderedNodeList->Dispose();
    }
    else
    {
      NumberOfMembersLoaded++;
    }
  }
}

  static void MakeVertical( CConcLoadObject
      *theObject, CRegularWoodTElement **theWoodObjPtr)
  {
    CTrussElementObject    *oldTE;
    Boolean          connectionPerformed=FALSE;

    switch( theObject->WhoAreYou() )
    {
      case aConcentratedLoad:
        if( (theObject->the2ndEndConnected )  && ( ! theObject->the1stEndConnected ))
        {
          theObject->UnSelectYourself();
          theObject->Erase();
          theObject->its1stEnd.h = theObject->its2ndEnd.h;
          theObject->DrawFinal();
        }
        else if( ! theObject->the2ndEndConnected )  /* add length to second end*/
        {
          theObject->UnSelectYourself();
          theObject->Erase();
          theObject->its2ndEnd.h = theObject->its1stEnd.h;
          theObject->DrawFinal();
        }
        break;

      case aConcentratedMoment:
        break;
    }
  }

  static void Calc_TotalContLoad( CQuadrelateralObject *theObject,
                WoodAndContLoad  *wood_and_contLoadPtr)
  {

    switch( theObject->WhoAreYou() )
    {
      case aContUniformGravityLoad:
        (*wood_and_contLoadPtr).totalContLoad +=
          (((float) (theObject->bottomLeftCorner.v - theObject->topLeftCorner.v)) *
                      theObject->itsTrussPane->theLoadScale / SCREEN_DPI );
      break;
    }
  }

  static void Print_ConcLoads( CConcLoadObject *theObject,
                    WoodAndConcLandMnum *concLandMNum_and_ThisObjectPTR)
  {
    if  (   ( theObject->TElementConnectionRatio <
            (*concLandMNum_and_ThisObjectPTR).secondEndTEConnectionRatio ) &&
        ( theObject->TElementConnectionRatio >=
            (*concLandMNum_and_ThisObjectPTR).firstEndTEConnectionRatio ) )
    {
      switch( theObject->WhoAreYou() )
      {
        case aConcentratedLoad:
          fprintf( Wood_Out_File, "\n%f\t",
              -(((float)(theObject->its2ndEnd.v - theObject->its1stEnd.v)) *
                    theObject->itsTrussPane->theLoadScale / SCREEN_DPI ) );
          fprintf( Wood_Out_File, "%f\t", (theObject->its2ndEnd.h *
                theObject->itsTrussPane->theStructureScale / SCREEN_DPI ) );
          break;
      }
    }
  }

  static void Print_ConcMoments( CConcLoadObject *theObject,
                    WoodAndConcLandMnum *concLandMNum_and_ThisObjectPTR)
  {
    if  (   ( theObject->TElementConnectionRatio <
            (*concLandMNum_and_ThisObjectPTR).secondEndTEConnectionRatio ) &&
        ( theObject->TElementConnectionRatio >=
            (*concLandMNum_and_ThisObjectPTR).firstEndTEConnectionRatio ) )
    {
      switch( theObject->WhoAreYou() )
      {
        case aConcentratedMoment:
          fprintf( Wood_Out_File, "\n%f\t", -((CConcMoment *)theObject)->itsMagnitude );
          fprintf( Wood_Out_File, "%f\t",
              (((CConcMoment *)theObject)->itsCenterPoint.h *
                theObject->itsTrussPane->theStructureScale / SCREEN_DPI ) );
          break;

      }
    }
  }


void  CRegularWoodTElement::PrintFileWood3( void )
{
  long          numberOfSections = 0L;
  CList          *orderedNodeList;
  CGussetPlate      *aMiddleNode;
  CGussetPlate      *previousMiddleNode;
  long          sectionCounter = 0L;
  CRegularWoodTElement  *thisObject;
  CClusterOfAbstracts   *theTEMP_Cluster;
  WoodAndConcLandMnum    concLandMNum_and_ThisObject;
  long            oldConcLNumber;
  long            oldConcMNumber;
  WoodAndContLoad       wood_and_contLoad;


  thisObject = this;
  concLandMNum_and_ThisObject.theConcLNumber = 0;
  concLandMNum_and_ThisObject.theConcMNumber = 0;
      /* these are defaults values for members with no nodes */
  concLandMNum_and_ThisObject.firstEndTEConnectionRatio = 0;
  concLandMNum_and_ThisObject.secondEndTEConnectionRatio = 1.01;
  concLandMNum_and_ThisObject.theWoodElement = thisObject;

  wood_and_contLoad.totalContLoad = 0.000;
  wood_and_contLoad.theWoodElement = thisObject;

  if( ConcLandMAreConnected && theTEConcLoadsAndMoments->numItems )
  {
    theTEMP_Cluster = new( CClusterOfAbstracts );
    theTEMP_Cluster->ICluster();
    theTEConcLoadsAndMoments->
          DoForEach1( Copy_Cluster, (long)(&theTEMP_Cluster) );
    theTEMP_Cluster->DoForEach( MakeVertical );
    theTEMP_Cluster->Dispose();

  }

  if( NodesAreConnected && theTENodes->numItems )
  {
    orderedNodeList = new( CList );
    orderedNodeList->IList();
    theTENodes->DoForEach1(
        Create_OrderedList, (long)(&orderedNodeList) );

    numberOfSections = (theTENodes->numItems) + 1;
    if ( numberOfSections == 2 )
    {
          /*****************first section of wood member *************/
      aMiddleNode = ((CGussetPlate *)(orderedNodeList->FirstItem()));

      concLandMNum_and_ThisObject.theConcLNumber = 0;
      concLandMNum_and_ThisObject.theConcMNumber = 0;
          /* these are defaults values for members with no nodes */
      concLandMNum_and_ThisObject.firstEndTEConnectionRatio = 0.000;
      concLandMNum_and_ThisObject.secondEndTEConnectionRatio =
                      aMiddleNode->TElementConnectionRatio;
      concLandMNum_and_ThisObject.theWoodElement = thisObject;
      if( ContLandMAreConnected && theTEContLoadsAndMoments->numItems )
      {
        wood_and_contLoad.totalContLoad = 0.000;
        wood_and_contLoad.theWoodElement = thisObject;
        theTEContLoadsAndMoments->DoForEach1( Calc_TotalContLoad, (long)(&wood_and_contLoad) );
      }

      if( ConcLandMAreConnected && theTEConcLoadsAndMoments->numItems )
      {
        theTEConcLoadsAndMoments->
          DoForEach1( Upddate_ConcLandMNumber, (long)(&concLandMNum_and_ThisObject) );
      }
      if( ( ConcLandMAreConnected && theTEConcLoadsAndMoments->numItems ) ||
        ( ContLandMAreConnected && theTEContLoadsAndMoments->numItems )    )
      {
        fprintf( Wood_Out_File, "\n%ld\t", theObjectNumber  );
        fprintf( Wood_Out_File, "%ld\t", (concLandMNum_and_ThisObject.theConcLNumber));
        fprintf( Wood_Out_File, "%f\t", -wood_and_contLoad.totalContLoad  );
        fprintf( Wood_Out_File, "%ld\t", (concLandMNum_and_ThisObject.theConcMNumber) );

        concLandMNum_and_ThisObject.firstEndTEConnectionRatio = 0.000;
        concLandMNum_and_ThisObject.secondEndTEConnectionRatio =
                        aMiddleNode->TElementConnectionRatio;
        concLandMNum_and_ThisObject.theWoodElement = thisObject;
        if( ConcLandMAreConnected && theTEConcLoadsAndMoments->numItems )
        {
          theTEConcLoadsAndMoments->
            DoForEach1( Print_ConcLoads, (long)(&concLandMNum_and_ThisObject) );
          theTEConcLoadsAndMoments->
            DoForEach1( Print_ConcMoments, (long)(&concLandMNum_and_ThisObject) );
        }
      }
          /*****************second section of wood member *************/
      concLandMNum_and_ThisObject.theConcLNumber = 0;
      concLandMNum_and_ThisObject.theConcMNumber = 0;
          /* these are defaults values for members with no nodes */
      concLandMNum_and_ThisObject.firstEndTEConnectionRatio =
                      aMiddleNode->TElementConnectionRatio;
      concLandMNum_and_ThisObject.secondEndTEConnectionRatio = 1.01;
      concLandMNum_and_ThisObject.theWoodElement = thisObject;
      if( ContLandMAreConnected && theTEContLoadsAndMoments->numItems )
      {
        wood_and_contLoad.totalContLoad = 0.000;
        wood_and_contLoad.theWoodElement = thisObject;
        theTEContLoadsAndMoments->DoForEach1( Calc_TotalContLoad, (long)(&wood_and_contLoad) );
      }

      if( ConcLandMAreConnected && theTEConcLoadsAndMoments->numItems )
      {
        theTEConcLoadsAndMoments->
          DoForEach1( Upddate_ConcLandMNumber, (long)(&concLandMNum_and_ThisObject) );
      }
      if( ( ConcLandMAreConnected && theTEConcLoadsAndMoments->numItems ) ||
        ( ContLandMAreConnected && theTEContLoadsAndMoments->numItems )    )
      {
        fprintf( Wood_Out_File, "\n%ld\t", theObjectNumber+1  );
        fprintf( Wood_Out_File, "%ld\t", (concLandMNum_and_ThisObject.theConcLNumber));
        fprintf( Wood_Out_File, "%f\t", -wood_and_contLoad.totalContLoad  );
        fprintf( Wood_Out_File, "%ld\t", (concLandMNum_and_ThisObject.theConcMNumber) );

        concLandMNum_and_ThisObject.firstEndTEConnectionRatio =
                        aMiddleNode->TElementConnectionRatio;
        concLandMNum_and_ThisObject.secondEndTEConnectionRatio = 1.01;
        concLandMNum_and_ThisObject.theWoodElement = thisObject;
        if( ConcLandMAreConnected && theTEConcLoadsAndMoments->numItems )
        {
          theTEConcLoadsAndMoments->
            DoForEach1( Print_ConcLoads, (long)(&concLandMNum_and_ThisObject) );
          theTEConcLoadsAndMoments->
            DoForEach1( Print_ConcMoments, (long)(&concLandMNum_and_ThisObject) );
        }
      }

    }
    else
    {
          /*****************first section of wood member *************/
      aMiddleNode = ((CGussetPlate *)(orderedNodeList->FirstItem()));

      concLandMNum_and_ThisObject.theConcLNumber = 0;
      concLandMNum_and_ThisObject.theConcMNumber = 0;
          /* these are defaults values for members with no nodes */
      concLandMNum_and_ThisObject.firstEndTEConnectionRatio = 0.000;
      concLandMNum_and_ThisObject.secondEndTEConnectionRatio =
                      aMiddleNode->TElementConnectionRatio;
      concLandMNum_and_ThisObject.theWoodElement = thisObject;
      if( ContLandMAreConnected && theTEContLoadsAndMoments->numItems )
      {
        wood_and_contLoad.totalContLoad = 0.000;
        wood_and_contLoad.theWoodElement = thisObject;
        theTEContLoadsAndMoments->DoForEach1( Calc_TotalContLoad, (long)(&wood_and_contLoad) );
      }

      if( ConcLandMAreConnected && theTEConcLoadsAndMoments->numItems )
      {
        theTEConcLoadsAndMoments->
          DoForEach1( Upddate_ConcLandMNumber, (long)(&concLandMNum_and_ThisObject) );
      }
      if( ( ConcLandMAreConnected && theTEConcLoadsAndMoments->numItems ) ||
        ( ContLandMAreConnected && theTEContLoadsAndMoments->numItems )    )
      {
        fprintf( Wood_Out_File, "\n%ld\t", theObjectNumber  );
        fprintf( Wood_Out_File, "%ld\t", (concLandMNum_and_ThisObject.theConcLNumber));
        fprintf( Wood_Out_File, "%f\t", -wood_and_contLoad.totalContLoad  );
        fprintf( Wood_Out_File, "%ld\t", (concLandMNum_and_ThisObject.theConcMNumber) );

        concLandMNum_and_ThisObject.firstEndTEConnectionRatio = 0.000;
        concLandMNum_and_ThisObject.secondEndTEConnectionRatio =
                        aMiddleNode->TElementConnectionRatio;
        concLandMNum_and_ThisObject.theWoodElement = thisObject;
        if( ConcLandMAreConnected && theTEConcLoadsAndMoments->numItems )
        {
          theTEConcLoadsAndMoments->
            DoForEach1( Print_ConcLoads, (long)(&concLandMNum_and_ThisObject) );
          theTEConcLoadsAndMoments->
            DoForEach1( Print_ConcMoments, (long)(&concLandMNum_and_ThisObject) );
        }
      }
      orderedNodeList->Remove( aMiddleNode );

          /*****************Middle sections of wood member *************/
      for( sectionCounter = 1; sectionCounter < (numberOfSections - 1);
                sectionCounter++ )
      {
        previousMiddleNode = aMiddleNode;

            /*****************each middle section of wood member *************/
        aMiddleNode = ((CGussetPlate *)(orderedNodeList->FirstItem()));

        concLandMNum_and_ThisObject.theConcLNumber = 0;
        concLandMNum_and_ThisObject.theConcMNumber = 0;

        concLandMNum_and_ThisObject.firstEndTEConnectionRatio =
                        previousMiddleNode->TElementConnectionRatio;
        concLandMNum_and_ThisObject.secondEndTEConnectionRatio =
                        aMiddleNode->TElementConnectionRatio;
        concLandMNum_and_ThisObject.theWoodElement = thisObject;
        if( ContLandMAreConnected && theTEContLoadsAndMoments->numItems )
        {
          wood_and_contLoad.totalContLoad = 0.000;
          wood_and_contLoad.theWoodElement = thisObject;
          theTEContLoadsAndMoments->DoForEach1( Calc_TotalContLoad, (long)(&wood_and_contLoad) );
        }

        if( ConcLandMAreConnected && theTEConcLoadsAndMoments->numItems )
        {
          theTEConcLoadsAndMoments->
            DoForEach1( Upddate_ConcLandMNumber, (long)(&concLandMNum_and_ThisObject) );
        }
        if( ( ConcLandMAreConnected && theTEConcLoadsAndMoments->numItems ) ||
          ( ContLandMAreConnected && theTEContLoadsAndMoments->numItems )    )
        {
          fprintf( Wood_Out_File, "\n%ld\t", theObjectNumber+sectionCounter   );
          fprintf( Wood_Out_File, "%ld\t", (concLandMNum_and_ThisObject.theConcLNumber));
          fprintf( Wood_Out_File, "%f\t", -wood_and_contLoad.totalContLoad  );
          fprintf( Wood_Out_File, "%ld\t", (concLandMNum_and_ThisObject.theConcMNumber) );

          concLandMNum_and_ThisObject.firstEndTEConnectionRatio =
                          previousMiddleNode->TElementConnectionRatio;
          concLandMNum_and_ThisObject.secondEndTEConnectionRatio =
                          aMiddleNode->TElementConnectionRatio;
          concLandMNum_and_ThisObject.theWoodElement = thisObject;
          if( ConcLandMAreConnected && theTEConcLoadsAndMoments->numItems )
          {
            theTEConcLoadsAndMoments->
              DoForEach1( Print_ConcLoads, (long)(&concLandMNum_and_ThisObject) );
            theTEConcLoadsAndMoments->
              DoForEach1( Print_ConcMoments, (long)(&concLandMNum_and_ThisObject) );
          }
        }

          /*****************end of each middle section of wood member *************/

        orderedNodeList->Remove( aMiddleNode );

      }


          /*****************Last section of wood member *************/
      concLandMNum_and_ThisObject.theConcLNumber = 0;
      concLandMNum_and_ThisObject.theConcMNumber = 0;
          /* these are defaults values for members with no nodes */
      concLandMNum_and_ThisObject.firstEndTEConnectionRatio =
                      aMiddleNode->TElementConnectionRatio;
      concLandMNum_and_ThisObject.secondEndTEConnectionRatio = 1.01;
      concLandMNum_and_ThisObject.theWoodElement = thisObject;
      if( ContLandMAreConnected && theTEContLoadsAndMoments->numItems )
      {
        wood_and_contLoad.totalContLoad = 0.000;
        wood_and_contLoad.theWoodElement = thisObject;
        theTEContLoadsAndMoments->DoForEach1( Calc_TotalContLoad, (long)(&wood_and_contLoad) );
      }

      if( ConcLandMAreConnected && theTEConcLoadsAndMoments->numItems )
      {
        theTEConcLoadsAndMoments->
          DoForEach1( Upddate_ConcLandMNumber, (long)(&concLandMNum_and_ThisObject) );
      }
      if( ( ConcLandMAreConnected && theTEConcLoadsAndMoments->numItems ) ||
        ( ContLandMAreConnected && theTEContLoadsAndMoments->numItems )    )
      {
        fprintf( Wood_Out_File, "\n%ld\t", theObjectNumber+(numberOfSections-1) );
        fprintf( Wood_Out_File, "%ld\t", (concLandMNum_and_ThisObject.theConcLNumber));
        fprintf( Wood_Out_File, "%f\t", -wood_and_contLoad.totalContLoad  );
        fprintf( Wood_Out_File, "%ld\t", (concLandMNum_and_ThisObject.theConcMNumber) );

        concLandMNum_and_ThisObject.firstEndTEConnectionRatio =
                        aMiddleNode->TElementConnectionRatio;
        concLandMNum_and_ThisObject.secondEndTEConnectionRatio = 1.01;
        concLandMNum_and_ThisObject.theWoodElement = thisObject;
        if( ConcLandMAreConnected && theTEConcLoadsAndMoments->numItems )
        {
          theTEConcLoadsAndMoments->
            DoForEach1( Print_ConcLoads, (long)(&concLandMNum_and_ThisObject) );
          theTEConcLoadsAndMoments->
            DoForEach1( Print_ConcMoments, (long)(&concLandMNum_and_ThisObject) );
        }
      }
    }
    orderedNodeList->Dispose();
  }
  else
  {
      /*****************one section (only) wood member *************/
    concLandMNum_and_ThisObject.theConcLNumber = 0;
    concLandMNum_and_ThisObject.theConcMNumber = 0;
        /* these are defaults values for members with no nodes */
    concLandMNum_and_ThisObject.firstEndTEConnectionRatio = 0.000;
    concLandMNum_and_ThisObject.secondEndTEConnectionRatio = 1.01;
    concLandMNum_and_ThisObject.theWoodElement = thisObject;
    if( ContLandMAreConnected && theTEContLoadsAndMoments->numItems )
    {
      wood_and_contLoad.totalContLoad = 0.000;
      wood_and_contLoad.theWoodElement = thisObject;
      theTEContLoadsAndMoments->DoForEach1( Calc_TotalContLoad, (long)(&wood_and_contLoad) );
    }

    if( ConcLandMAreConnected && theTEConcLoadsAndMoments->numItems )
    {
      theTEConcLoadsAndMoments->
        DoForEach1( Upddate_ConcLandMNumber, (long)(&concLandMNum_and_ThisObject) );
    }
    if( ( ConcLandMAreConnected && theTEConcLoadsAndMoments->numItems ) ||
      ( ContLandMAreConnected && theTEContLoadsAndMoments->numItems )    )
    {
      fprintf( Wood_Out_File, "\n%ld\t", theObjectNumber  );
      fprintf( Wood_Out_File, "%ld\t", (concLandMNum_and_ThisObject.theConcLNumber));
      fprintf( Wood_Out_File, "%f\t", -wood_and_contLoad.totalContLoad  );
      fprintf( Wood_Out_File, "%ld\t", (concLandMNum_and_ThisObject.theConcMNumber) );

      concLandMNum_and_ThisObject.firstEndTEConnectionRatio = 0.000;
      concLandMNum_and_ThisObject.secondEndTEConnectionRatio = 1.01;
      concLandMNum_and_ThisObject.theWoodElement = thisObject;
      if( ConcLandMAreConnected && theTEConcLoadsAndMoments->numItems )
      {
        theTEConcLoadsAndMoments->
          DoForEach1( Print_ConcLoads, (long)(&concLandMNum_and_ThisObject) );
        theTEConcLoadsAndMoments->
          DoForEach1( Print_ConcMoments, (long)(&concLandMNum_and_ThisObject) );
      }
    }

  }
}

void  CRegularWoodTElement::PrintFileWood4( void )
{
}



void  CRegularWoodTElement::KillYourself_IF_NOT_Connected( void )
{
  inherited::KillYourself_IF_NOT_Connected();
}
void  CRegularWoodTElement::SaveYourself( void )
{
}
void  CRegularWoodTElement::LoadYourself( void )
{
}


void CRegularWoodTElement::InitializeGlobalNumbers( void )
{
  inherited::InitializeGlobalNumbers();
}

