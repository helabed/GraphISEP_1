/****
 * CRegularWoodTElement.c
 *
 *  CRegularWoodTElement object class for a typical CTrussPane class
 *
 ****/
#include "CRegularWoodTElement.phs"

/*** Global Variables ***/

extern  CBartender *gBartender;
extern   short    gClicks;
extern  FILE      *Debug_Info_Out_File;
extern  FILE      *Wood_Out_File;




void CRegularWoodTElement::InitializeYourself( void )
{
  inherited::InitializeYourself();

  CrossSectionWidth = 1.5;
  CrossSectionHeight = 3.5;
  E = 1770000;
  BendingStrength = 7300;
  TensileStrength = 3830;
  CompressiveStrength = 4400;

  its1stEndTip.v = 0.0;
  its1stEndTip.h = -1;
  its1stEndRightCorner.v = CrossSectionHeight/2;
  its1stEndRightCorner.h = 0;
  its1stEndLeftCorner.v = -CrossSectionHeight/2;
  its1stEndLeftCorner.h = 0;
  its2ndEndTip.v = 0.0;
  its2ndEndTip.h = 1;
  its2ndEndRightCorner.v = CrossSectionHeight/2;
  its2ndEndRightCorner.h = 0;      /* dumy for now */
  its2ndEndLeftCorner.v = -CrossSectionHeight/2;
  its2ndEndLeftCorner.h =  0;      /* dumy for now */
  its1stEndHOffset = 0;
  its1stEndVOffset = 0;
  its2ndEndHOffset = 0;
  its2ndEndVOffset = 0;

  itsOtherEnd = its2ndEnd;

  firstEndPolyPointCounter = 0;
  secondEndPolyPointCounter = 0;

  firstEndConnectorArea = 0;
  secondEndConnectorArea = 0;
  firstEndIxx = 0;
  secondEndIxx = 0;
  firstEndIyy = 0;
  secondEndIyy = 0;
  firstEndCentroid.h =  0;
  firstEndCentroid.v =  0;
  secondEndCentroid.h =  0;
  secondEndCentroid.v =  0;
  its1stEndBCondIsSet = FALSE;
  its2ndEndBCondIsSet = FALSE;
  inherit1stEndPlateLoads = FALSE;
  inherit2ndEndPlateLoads = FALSE;
  firstEndcenterPointsHOffset = 0;
  firstEndcenterPointsVOffset = 0;
  secondEndcenterPointsHOffset = 0;
  secondEndcenterPointsVOffset = 0;

}

void CRegularWoodTElement::DoDrawing( void )
{
  PenState     pnState;


  GetPenState ( &pnState);/* to save the pen setting */
  PenPat( ltGray );
  CTrussElementObject::DoDrawing();
  SetPenState ( &pnState);/* to resotre pen settting */

}

        static void Apply_E( CTrussElementObject
            *theObject, CTrussElementObject **thisObjectPtr)
        {
          if( ((theObject->WhoAreYou() == aWoodElement ) ||
            (theObject->WhoAreYou() == aTopBottomWoodElement))||
            (theObject->WhoAreYou() == aRightLeftWoodElement ))
            theObject->E = (*thisObjectPtr)->E;
        }
        static void Apply_CrossSectionHeight( CRegularWoodTElement
            *theObject, CRegularWoodTElement **thisObjectPtr)
        {
          if( ((theObject->WhoAreYou() == aWoodElement ) ||
            (theObject->WhoAreYou() == aTopBottomWoodElement))||
            (theObject->WhoAreYou() == aRightLeftWoodElement ))
            theObject->CrossSectionHeight =
              (*thisObjectPtr)->CrossSectionHeight;
        }
        static void Apply_CrossSectionWidth( CRegularWoodTElement
            *theObject, CRegularWoodTElement **thisObjectPtr)
        {
          if( ((theObject->WhoAreYou() == aWoodElement ) ||
            (theObject->WhoAreYou() == aTopBottomWoodElement))||
            (theObject->WhoAreYou() == aRightLeftWoodElement ))
            theObject->CrossSectionWidth =
              (*thisObjectPtr)->CrossSectionWidth;
        }
        static void Apply_BendingStrength( CTrussElementObject
            *theObject, CTrussElementObject **thisObjectPtr)
        {
          if( ((theObject->WhoAreYou() == aWoodElement ) ||
            (theObject->WhoAreYou() == aTopBottomWoodElement))||
            (theObject->WhoAreYou() == aRightLeftWoodElement ))
            theObject->BendingStrength =
                 (*thisObjectPtr)->BendingStrength;
        }
        static void Apply_TensileStrength( CTrussElementObject
            *theObject, CTrussElementObject **thisObjectPtr)
        {
          if( ((theObject->WhoAreYou() == aWoodElement ) ||
            (theObject->WhoAreYou() == aTopBottomWoodElement))||
            (theObject->WhoAreYou() == aRightLeftWoodElement ))
            theObject->TensileStrength =
                 (*thisObjectPtr)->TensileStrength;
        }
        static void Apply_CompressiveStrength( CTrussElementObject
            *theObject, CTrussElementObject **thisObjectPtr)
        {
          if( ((theObject->WhoAreYou() == aWoodElement ) ||
            (theObject->WhoAreYou() == aTopBottomWoodElement))||
            (theObject->WhoAreYou() == aRightLeftWoodElement ))
            theObject->CompressiveStrength =
                 (*thisObjectPtr)->CompressiveStrength;
        }

        static void Perform_Draw( CAbstractObject
            *theObject)
        {
            theObject->DrawFinal();
        }


void CRegularWoodTElement::DoYourDialog( void )
{
  DialogHandlerRecordPtr   dhp;
  DecForm          dForm;
  float          xLength;
  float          yLength;
  float          newTElementLength;
  float          TElementLength;
  Boolean          theBoxIsChecked;
  CTrussElementObject    *thisObject;
  CRegularWoodTElement  *thisWoodObject;
  float          newTElementRatio;
  float          scalingFactor;
  float          theta;
  float           itsCosine;
  float           itsSine;
  float          itsAngle;

  thisObject = this;
  thisWoodObject = this;

  DHStandardNewRecord (&dhp, WoodElementDLOG_ID,
              WoodElementUpdateUserItemId,
              WoodElementModulusOfElasticity);


  TElementLength = (float) sqrt((double)(( (((float)(its2ndEnd.v -its1stEnd.v))*
            ((float)(its2ndEnd.v -its1stEnd.v) )) +
            ( ((float)(its2ndEnd.h -its1stEnd.h))*
            ((float)(its2ndEnd.h -its1stEnd.h)) ) ) ) );

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, WoodElementLength,
    (WhatIsYourLength() ),
      dForm, 0.0, MAXREAL);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, WoodElementHorzLength,
    ((its2ndEnd.h - its1stEnd.h) * itsTrussPane->theStructureScale / SCREEN_DPI ),
      dForm, -MAXREAL, MAXREAL);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, WoodElementVertLength,
    ((its2ndEnd.v - its1stEnd.v) * itsTrussPane->theStructureScale / SCREEN_DPI ),
      dForm, -MAXREAL, MAXREAL);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, WoodElementModulusOfElasticity,
    (E ), dForm, 0.0, MAXREAL);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, WoodElementCrossSHeight,
    (CrossSectionHeight ), dForm, 0.0, MAXREAL);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, WoodElementCrossSWidth,
    (CrossSectionWidth), dForm, 0.0, MAXREAL);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, WoodElementBendingStrength,
    (BendingStrength),dForm, 0.0, 50000);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, WoodElementTensileStrength,
    (TensileStrength), dForm, 0.0, 50000);/* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, WoodElementCompressiveStrength,
    (CompressiveStrength), dForm, 0.0, 50000); /* should be limit of drawing area*/

        /* to find the angle */
  GetSineAndCosine( &theta, &itsCosine, &itsSine);
  itsAngle = (float) ( ( theta)  / PI * 180.0 );


  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, WoodElementAngle,
    (itsAngle), dForm, 0.0, 360); /* should be limit of drawing area*/


  DHADDCHECKBOX( dhp, WoodElementModulusOfElasticityApplyToAll, FALSE);
  DHADDCHECKBOX( dhp, WoodElementCrossSHeightApplyToAll, FALSE);
  DHADDCHECKBOX( dhp, WoodElementCrossSWidthApplyToAll, FALSE);
  DHADDCHECKBOX( dhp, WoodElementBendingStrengthApplyToAll, FALSE);
  DHADDCHECKBOX( dhp, WoodElementTensileStrengthApplyToAll, FALSE);
  DHADDCHECKBOX( dhp, WoodElementCompressiveStrengthApplyToAll, FALSE);

  if (DHDialogHandler(dhp))
  {

    newTElementLength = DHGetEditReal(dhp, WoodElementLength);
    xLength = DHGetEditReal(dhp, WoodElementHorzLength);
    yLength = DHGetEditReal(dhp, WoodElementVertLength);
    E = DHGetEditReal(dhp, WoodElementModulusOfElasticity);
    CrossSectionHeight =  DHGetEditReal(dhp, WoodElementCrossSHeight);
    CrossSectionWidth = DHGetEditReal(dhp, WoodElementCrossSWidth);
    BendingStrength = DHGetEditReal(dhp, WoodElementBendingStrength);
    TensileStrength = DHGetEditReal(dhp, WoodElementTensileStrength);
    CompressiveStrength =  DHGetEditReal(dhp, WoodElementCompressiveStrength);


    theBoxIsChecked = DHIsBoxChecked( dhp,
                WoodElementModulusOfElasticityApplyToAll);
    if( theBoxIsChecked )
    {
      itsTrussPane->TElementsCluster->DoForEach1(
        Apply_E, (long)(&thisObject) );
    }

    theBoxIsChecked = DHIsBoxChecked( dhp,
                WoodElementCrossSHeightApplyToAll);
    if( theBoxIsChecked )
    {
      itsTrussPane->TElementsCluster->DoForEach1(
        Apply_CrossSectionHeight, (long)(&thisWoodObject) );
    }
    theBoxIsChecked = DHIsBoxChecked( dhp,
                WoodElementCrossSWidthApplyToAll);
    if( theBoxIsChecked )
    {
      itsTrussPane->TElementsCluster->DoForEach1(
        Apply_CrossSectionWidth, (long)(&thisWoodObject) );
    }
    theBoxIsChecked = DHIsBoxChecked( dhp,
                WoodElementBendingStrengthApplyToAll);
    if( theBoxIsChecked )
    {
      itsTrussPane->TElementsCluster->DoForEach1(
        Apply_BendingStrength, (long)(&thisObject) );
    }
    theBoxIsChecked = DHIsBoxChecked( dhp,
                WoodElementTensileStrengthApplyToAll);
    if( theBoxIsChecked )
    {
      itsTrussPane->TElementsCluster->DoForEach1(
        Apply_TensileStrength, (long)(&thisObject) );
    }
    theBoxIsChecked = DHIsBoxChecked( dhp,
                WoodElementCompressiveStrengthApplyToAll);
    if( theBoxIsChecked )
    {
      itsTrussPane->TElementsCluster->DoForEach1(
        Apply_CompressiveStrength, (long)(&thisObject) );
    }


        /* Length field has changed, i.e new != old */
    if( ! (Abs(newTElementLength -
       (WhatIsYourLength() ))
       <=  SMALL_FLOAT_VALUE) )
    {
      newTElementRatio = newTElementLength /
      (TElementLength * itsTrussPane->theStructureScale / SCREEN_DPI );
      if( (the2ndEndConnected )  && ( ! the1stEndConnected ))
          /* subtract length from first end*/
      {
        xLength = (float)(its2ndEnd.h - its1stEnd.h);
        yLength = (float)(its2ndEnd.v - its1stEnd.v);
        UnSelectYourself();
        Erase();


        its1stEnd.h = its1stEnd.h - (int)(( newTElementRatio - 1.0 )
                    *(xLength));
        its1stEnd.v = its1stEnd.v - (int)(( newTElementRatio - 1.0 )
                    *(yLength));

        DrawFinal();
        theTEConcLoadsAndMoments->DoForEach(  Perform_Draw );
        theTEContLoadsAndMoments->DoForEach( Perform_Draw );
        theTENodes->DoForEach( Perform_Draw );
      }
      else if( ! the2ndEndConnected )  /* add length to second end*/
      {
        xLength = (float)(its2ndEnd.h - its1stEnd.h);
        yLength = (float)(its2ndEnd.v - its1stEnd.v);
        UnSelectYourself();
        Erase();


        its2ndEnd.h = its2ndEnd.h + (int)(( newTElementRatio - 1.0 )
                    *(xLength));
        its2ndEnd.v = its2ndEnd.v + (int)(( newTElementRatio - 1.0 )
                    *(yLength));

        DrawFinal();
        theTEConcLoadsAndMoments->DoForEach(  Perform_Draw );
        theTEContLoadsAndMoments->DoForEach( Perform_Draw );
        theTENodes->DoForEach( Perform_Draw );

      }


        /* components of Length field have changed */
    }else if( (! (Abs(xLength -
       ((its2ndEnd.h - its1stEnd.h) * itsTrussPane->theStructureScale
       / SCREEN_DPI )) <=  SMALL_FLOAT_VALUE) )  ||
       ( ! (Abs(yLength -
       ((its2ndEnd.v - its1stEnd.v) * itsTrussPane->theStructureScale
       / SCREEN_DPI )) <=  SMALL_FLOAT_VALUE) ) )
     {
      if( (the2ndEndConnected )  && ( ! the1stEndConnected ))
          /* subtract length from first end*/
      {
        UnSelectYourself();
        Erase();


        its1stEnd.h = its2ndEnd.h - (int)((xLength));
        its1stEnd.v = its2ndEnd.v - (int)((yLength));

        DrawFinal();
        theTEConcLoadsAndMoments->DoForEach(  Perform_Draw );
        theTEContLoadsAndMoments->DoForEach( Perform_Draw );
        theTENodes->DoForEach( Perform_Draw );
      }
      else if( ! the2ndEndConnected )  /* add length to second end*/
      {
        UnSelectYourself();
        Erase();


        its2ndEnd.h = its1stEnd.h + (int)((xLength)/
            itsTrussPane->theStructureScale * SCREEN_DPI);
        its2ndEnd.v = its1stEnd.v + (int)((yLength)/
            itsTrussPane->theStructureScale * SCREEN_DPI);

        DrawFinal();
        theTEConcLoadsAndMoments->DoForEach(  Perform_Draw );
        theTEContLoadsAndMoments->DoForEach( Perform_Draw );
        theTENodes->DoForEach( Perform_Draw );

      }
    }
  }

  DHDeallocateRecord(dhp);
}



void CRegularWoodTElement::GetSineAndCosine( float  *theta, float *itsCosine,
            float *itsSine )
{
  Point    its1stEnd;
  Point    its2ndEnd;
  float    xLength,yLength, TElementLength;
  float          scalingFactor;

  scalingFactor = SCREEN_DPI / (itsTrussPane->theStructureScale);

  its1stEnd.v = this->its1stEnd.v + (int) (its1stEndVOffset * scalingFactor);
  its1stEnd.h = this->its1stEnd.h + (int) (its1stEndHOffset * scalingFactor);
  its2ndEnd.v = this->its2ndEnd.v + (int) (its2ndEndVOffset * scalingFactor);
  its2ndEnd.h = this->its2ndEnd.h + (int) (its2ndEndHOffset * scalingFactor);

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

}
short CRegularWoodTElement::WhichEndIsConnected( CNodeObject *thePlate )
{
  if( thePlate == the1stEndNode)
    return ( 1 );
  else
  if( thePlate == the2ndEndNode )
    return( 2 );
  else
    return( 0 );
}
float CRegularWoodTElement::WhatIsYourLength( void )
{
  float    TElementLength;
  Point    its1stEnd;
  Point    its2ndEnd;
  float          scalingFactor;

  scalingFactor = SCREEN_DPI / (itsTrussPane->theStructureScale);

  its1stEnd.v = this->its1stEnd.v + (int) (its1stEndVOffset * scalingFactor);
  its1stEnd.h = this->its1stEnd.h + (int) (its1stEndHOffset * scalingFactor);
  its2ndEnd.v = this->its2ndEnd.v + (int) (its2ndEndVOffset * scalingFactor);
  its2ndEnd.h = this->its2ndEnd.h + (int) (its2ndEndHOffset * scalingFactor);



  TElementLength = (float) sqrt((double)(( (((float)(its2ndEnd.v -its1stEnd.v))*
            ((float)(its2ndEnd.v -its1stEnd.v) )) +
            ( ((float)(its2ndEnd.h -its1stEnd.h))*
            ((float)(its2ndEnd.h -its1stEnd.h)) ) ) ) );


  return( (TElementLength * itsTrussPane->theStructureScale / SCREEN_DPI ));
}


void CRegularWoodTElement::StretchBothEnds( Point *its1stStretchedEnd,
        Point *its2ndStretchedEnd ,CGussetPlate *thePlate)
{
  int     xOffset;
  int      yOffset;
  float    theta;
  float     itsCosine;
  float     itsSine;
  float    itsLength;
  float    the1stLength;
  float    the2ndLength;
  float          scalingFactor;

  Point    its1stEnd;
  Point    its2ndEnd;
  Point    connectionPoint;

  scalingFactor = SCREEN_DPI / ((( CGussetPane *)(thePlate->
        itsDocument->itsMainPane))->
                  theStructureScale);

  scalingFactor = SCREEN_DPI / (itsTrussPane->theStructureScale);

  scalingFactor = SCREEN_DPI / ((( CGussetPane *)(thePlate->
        itsDocument->itsMainPane))->
                  theStructureScale);

  its1stEnd.v = this->its1stEnd.v + (int) (its1stEndVOffset * scalingFactor);
  its1stEnd.h = this->its1stEnd.h + (int) (its1stEndHOffset * scalingFactor);
  its2ndEnd.v = this->its2ndEnd.v + (int) (its2ndEndVOffset * scalingFactor);
  its2ndEnd.h = this->its2ndEnd.h + (int) (its2ndEndHOffset * scalingFactor);

  GetSineAndCosine( &theta, &itsCosine, &itsSine);

  itsLength = WhatIsYourLength();

  the2ndLength = itsLength * ( 1 -  (thePlate->TElementConnectionRatio));
  the1stLength = itsLength * (thePlate->TElementConnectionRatio);


  connectionPoint.h = ((int)((( float)(its2ndEnd.h -its1stEnd.h))
        *(thePlate->TElementConnectionRatio))) + its1stEnd.h;
  connectionPoint.v = ((int)((( float)(its2ndEnd.v -its1stEnd.v))
        *(thePlate->TElementConnectionRatio))) + its1stEnd.v;

  xOffset = (int)( the1stLength * SCREEN_DPI /
    (((( CGussetPane *)(thePlate->
      itsDocument->itsMainPane))->
                theStructureScale) )
    * itsCosine);

  yOffset = (int)( the1stLength * SCREEN_DPI /
    (((( CGussetPane *)(thePlate->
      itsDocument->itsMainPane))->
                theStructureScale))
    * itsSine);

  (*its1stStretchedEnd).h = connectionPoint.h - xOffset;
  (*its1stStretchedEnd).v = connectionPoint.v - yOffset;

/*  connectionPoint.h = ((int)((( float)(its2ndEnd.h -its1stEnd.h))
        *(thePlate->TElementConnectionRatio))) + its1stEnd.h;
  connectionPoint.v = ((int)((( float)(its2ndEnd.v -its1stEnd.v))
        *(thePlate->TElementConnectionRatio))) + its1stEnd.v;
*/
  xOffset = (int)( the2ndLength * SCREEN_DPI /
    (((( CGussetPane *)(thePlate->
      itsDocument->itsMainPane))->
                theStructureScale) )
    * itsCosine);

  yOffset = (int)( the2ndLength * SCREEN_DPI /
    (((( CGussetPane *)(thePlate->
      itsDocument->itsMainPane))->
                theStructureScale))
    * itsSine);

  (*its2ndStretchedEnd).h = connectionPoint.h + xOffset;
  (*its2ndStretchedEnd).v = connectionPoint.v + yOffset;

}

void CRegularWoodTElement::StretchTheOtherEnd( short whichEnd,
                float totalLength, CGussetPlate *thePlate)
{
  int     xOffset;
  int      yOffset;
  float    theta;
  float     itsCosine;
  float     itsSine;
  float          scalingFactor;

  Point    its1stEnd;
  Point    its2ndEnd;

  scalingFactor = SCREEN_DPI / ((( CGussetPane *)(thePlate->
        itsDocument->itsMainPane))->
                  theStructureScale);


  its1stEnd.v = this->its1stEnd.v + (int) (its1stEndVOffset * scalingFactor);
  its1stEnd.h = this->its1stEnd.h + (int) (its1stEndHOffset * scalingFactor);
  its2ndEnd.v = this->its2ndEnd.v + (int) (its2ndEndVOffset * scalingFactor);
  its2ndEnd.h = this->its2ndEnd.h + (int) (its2ndEndHOffset * scalingFactor);

  GetSineAndCosine( &theta, &itsCosine, &itsSine);

  if( whichEnd == 1 )  /* the end that is connected, stretch the */
            /* other end,i.e end 2 */
  {
    xOffset = (int)( totalLength * SCREEN_DPI /
      (((( CGussetPane *)(thePlate->
        itsDocument->itsMainPane))->
                  theStructureScale) )
      * itsCosine);
    yOffset = (int)( totalLength * SCREEN_DPI /
      (((( CGussetPane *)(thePlate->
        itsDocument->itsMainPane))->
                  theStructureScale))
      * itsSine);

    itsOtherEnd.h = its1stEnd.h + xOffset;
    itsOtherEnd.v = its1stEnd.v + yOffset;
  }
  if( whichEnd == 2 )
  {
    xOffset = (int)( totalLength * SCREEN_DPI /
      (((( CGussetPane *)(thePlate->
        itsDocument->itsMainPane))->
                  theStructureScale))
      * itsCosine);
    yOffset = (int)( totalLength * SCREEN_DPI /
      (((( CGussetPane *)(thePlate->
        itsDocument->itsMainPane))->
                  theStructureScale))
      * itsSine);

    itsOtherEnd.h = its2ndEnd.h - xOffset;
    itsOtherEnd.v = its2ndEnd.v - yOffset;
  }
}
Point CRegularWoodTElement::TransformTElementToPano( FloatPoint aRealPoint,
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
void CRegularWoodTElement::TransformTElementToPanoNew( FloatPoint aRealPoint[],
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
FloatPoint CRegularWoodTElement::TransformPanoToTElement( Point aPoint,
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


  static void EnforcePhysicalCondition(   CRegularWoodTElement *thisObject,
                CGussetPlate  *thePlate)
  {
    thisObject->its1stEndRightCorner.v = thisObject->CrossSectionHeight/2;
    thisObject->its1stEndLeftCorner.v = -thisObject->CrossSectionHeight/2;
    thisObject->its2ndEndRightCorner.v = thisObject->CrossSectionHeight/2;
    thisObject->its2ndEndLeftCorner.v = -thisObject->CrossSectionHeight/2;
    if(   thisObject->its1stEndTip.v  > thisObject->CrossSectionHeight/2)
    {
      thisObject->its1stEndTip.v = thisObject->CrossSectionHeight/2;
    }
    if(   thisObject->its1stEndTip.v  < -thisObject->CrossSectionHeight/2)
    {
      thisObject->its1stEndTip.v = -thisObject->CrossSectionHeight/2;
    }
    if(   thisObject->its2ndEndTip.v  > thisObject->CrossSectionHeight/2)
    {
      thisObject->its2ndEndTip.v = thisObject->CrossSectionHeight/2;
    }
    if(   thisObject->its2ndEndTip.v  < -thisObject->CrossSectionHeight/2)
    {
      thisObject->its2ndEndTip.v = -thisObject->CrossSectionHeight/2;
    }
  }




void CRegularWoodTElement::BlowUpDraw( CGussetPlate *thePlate)
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
  EnforcePhysicalCondition( thisObject, thePlate);


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

  arrayOfFloatPoints[ 0 ] = its1stEndTip;
  arrayOfFloatPoints[ 1 ] = its1stEndRightCorner;
  arrayOfFloatPoints[ 2 ] = its1stEndLeftCorner;
  arrayOfFloatPoints[ 3 ] = its2ndEndTip;
  arrayOfFloatPoints[ 4 ] = its2ndEndRightCorner;
  arrayOfFloatPoints[ 5 ] = its2ndEndLeftCorner;

  whichEndConnected = WhichEndIsConnected( thePlate );

  StretchTheOtherEnd( whichEndConnected,
                WhatIsYourLength(), thePlate);


  if( whichEndConnected == 1 )
  {
    its1stStretchedEnd.h = (its1stEnd.h+ (int) (its1stEndHOffset * scalingFactor));
    its1stStretchedEnd.v = (its1stEnd.v+ (int) (its1stEndVOffset * scalingFactor));

    MoveTo( its1stStretchedEnd.h , its1stStretchedEnd.v );
    LineTo( itsOtherEnd.h, itsOtherEnd.v );

    TransformTElementToPanoNew(arrayOfFloatPoints, its1stStretchedEnd, 6,
                  TransformedPoints);

    its1stEndTipPoint = TransformedPoints[ 0 ];
    its1stEndRightCornerPoint = TransformedPoints[ 1 ];
    its1stEndLeftCornerPoint = TransformedPoints[ 2 ];
    its2ndEndTipPoint = TransformedPoints[ 3 ];
    its2ndEndRightCornerPoint = TransformedPoints[ 4 ];
    its2ndEndLeftCornerPoint = TransformedPoints[ 5 ];

    MoveTo( its1stEndTipPoint.h,
        its1stEndTipPoint.v);
    LineTo( its1stEndRightCornerPoint.h,
        its1stEndRightCornerPoint.v);
    LineTo( its2ndEndRightCornerPoint.h,
        its2ndEndRightCornerPoint.v);
    LineTo( its2ndEndTipPoint.h,
        its2ndEndTipPoint.v);
    LineTo( its2ndEndLeftCornerPoint.h,
        its2ndEndLeftCornerPoint.v);
    LineTo( its1stEndLeftCornerPoint.h,
        its1stEndLeftCornerPoint.v);
    LineTo( its1stEndTipPoint.h,
        its1stEndTipPoint.v);
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

    MoveTo( (its2ndEnd.h+ (int) (its2ndEndHOffset * scalingFactor)),
         (its2ndEnd.v+ (int) (its2ndEndVOffset * scalingFactor)));
    LineTo( itsOtherEnd.h, itsOtherEnd.v );

    MoveTo( its2ndEndTipPoint.h,
        its2ndEndTipPoint.v);
    LineTo( its2ndEndRightCornerPoint.h,
        its2ndEndRightCornerPoint.v);
    LineTo( its1stEndRightCornerPoint.h,
        its1stEndRightCornerPoint.v);
    LineTo( its1stEndTipPoint.h,
        its1stEndTipPoint.v);
    LineTo( its1stEndLeftCornerPoint.h,
        its1stEndLeftCornerPoint.v);
    LineTo( its2ndEndLeftCornerPoint.h,
        its2ndEndLeftCornerPoint.v);
    LineTo( its2ndEndTipPoint.h,
        its2ndEndTipPoint.v);
  }
  else if( whichEndConnected == 0) /* the plate's mother TE */
  {
    StretchBothEnds( &its1stStretchedEnd, &its2ndStretchedEnd ,
           thePlate);

    TransformTElementToPanoNew(arrayOfFloatPoints, its1stStretchedEnd, 6,
                  TransformedPoints);

    its1stEndTipPoint = TransformedPoints[ 0 ];
    its1stEndRightCornerPoint = TransformedPoints[ 1 ];
    its1stEndLeftCornerPoint = TransformedPoints[ 2 ];
    its2ndEndTipPoint = TransformedPoints[ 3 ];
    its2ndEndRightCornerPoint = TransformedPoints[ 4 ];
    its2ndEndLeftCornerPoint = TransformedPoints[ 5 ];

    MoveTo( its1stStretchedEnd.h, its1stStretchedEnd.v);
    LineTo( its2ndStretchedEnd.h, its2ndStretchedEnd.v);

    MoveTo( its1stEndTipPoint.h,
        its1stEndTipPoint.v);
    LineTo( its1stEndLeftCornerPoint.h,
        its1stEndLeftCornerPoint.v);
    LineTo( its2ndEndLeftCornerPoint.h,
        its2ndEndLeftCornerPoint.v);
    LineTo( its2ndEndTipPoint.h,
        its2ndEndTipPoint.v);
    LineTo( its2ndEndRightCornerPoint.h,
        its2ndEndRightCornerPoint.v);
    LineTo( its1stEndRightCornerPoint.h,
        its1stEndRightCornerPoint.v);
    LineTo( its1stEndTipPoint.h,
        its1stEndTipPoint.v);
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

Boolean CRegularWoodTElement::WhichOneOfUsGotSelected( Point aPoint )
{
  inherited::WhichOneOfUsGotSelected( aPoint );
  precisionCuttingInProgress = FALSE;
  placingInProgress = FALSE;

}

void CRegularWoodTElement::DisconnectYourself( void )
{
  inherited::DisconnectYourself();
  firstEndcenterPointsHOffset = 0;
  firstEndcenterPointsVOffset = 0;
  secondEndcenterPointsHOffset = 0;
  secondEndcenterPointsVOffset = 0;


}


