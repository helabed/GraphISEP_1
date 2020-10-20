/****
 * CTBWoodTElement.c
 *
 *  CGenericTElement object class for a typical CTrussPane class
 *
 ****/
#include "CRegularWoodTElement.phs"
#include "CTBWoodTElement.h"

/*** Global Variables ***/

extern  CBartender *gBartender;
extern   short    gClicks;

void CTBWoodTElement::InitializeYourself( void )
{
  inherited::InitializeYourself();
  UnSelectYourself();
  Erase();

  its1stEnd.h = itsCenterPoint.h - 90;
  its1stEnd.v = itsCenterPoint.v;
  its2ndEnd.h = itsCenterPoint.h + 90;
  its2ndEnd.v = itsCenterPoint.v;

  its1stEndHOffset = 0.0;
  its1stEndVOffset = 0.0;
  its2ndEndHOffset = 0.0;
  its2ndEndVOffset = 0.0;

  OpenRgn();
  UpDateItsRegion();
  CloseRgn(itsRegion);
  InsetRgn( itsRegion, RGN_EXPANSION_IN_PIXELS, RGN_EXPANSION_IN_PIXELS);
        /* make the region larger */

  DrawFinal();
}

void CTBWoodTElement::DoDrawing( void )
{
  PenState     pnState;


  GetPenState ( &pnState);/* to save the pen setting */
  PenPat( dkGray );
  CTrussElementObject::DoDrawing();
  SetPenState ( &pnState);/* to resotre pen settting */

}


void  CTBWoodTElement::FromtheHitPointToCorners( void )
{
  if ( its2ndEndFlag )
  {
      its2ndEnd.h = theHitPoint.h - offSet.h;
      its2ndEnd.v = its1stEnd.v;
  }
  else
  if ( its1stEndFlag )
  {
      its1stEnd.h = theHitPoint.h - offSet.h;
      its1stEnd.v = its2ndEnd.v;

  }
  if ( the1stEndConnected )
  {
    if( ! IamConnected )
    {
    its1stEnd.v = theHitPoint.v - offSet.v;
    its2ndEnd.v = its1stEnd.v;
    }
  }
  if( the2ndEndConnected )
  {
    if( ! IamConnected )
    {
    its2ndEnd.v = theHitPoint.v - offSet.v;
    its1stEnd.v = its2ndEnd.v;
    }
  }

}

void  CTBWoodTElement::FromCornersToItsCenterPoint( void )
{
  if ( the1stEndConnected )
  {
    its2ndEnd.v = its1stEnd.v;
  }
  if( the2ndEndConnected )
  {
    its1stEnd.v = its2ndEnd.v;
  }
  itsCenterPoint.v = ( its2ndEnd.v + its1stEnd.v ) / 2;
  itsCenterPoint.h = ( its2ndEnd.h + its1stEnd.h ) / 2;
}

        static void Apply_E( CTrussElementObject
            *theObject, CTrussElementObject **thisObjectPtr)
        {
            theObject->E = (*thisObjectPtr)->E;
        }
        static void Apply_CrossSectionHeight( CRegularWoodTElement
            *theObject, CRegularWoodTElement **thisObjectPtr)
        {
            theObject->CrossSectionHeight =
              (*thisObjectPtr)->CrossSectionHeight;
        }
        static void Apply_CrossSectionWidth( CRegularWoodTElement
            *theObject, CRegularWoodTElement **thisObjectPtr)
        {
            theObject->CrossSectionWidth =
              (*thisObjectPtr)->CrossSectionWidth;
        }
        static void Apply_BendingStrength( CTrussElementObject
            *theObject, CTrussElementObject **thisObjectPtr)
        {
            theObject->BendingStrength =
                 (*thisObjectPtr)->BendingStrength;
        }
        static void Apply_TensileStrength( CTrussElementObject
            *theObject, CTrussElementObject **thisObjectPtr)
        {
            theObject->TensileStrength =
                 (*thisObjectPtr)->TensileStrength;
        }
        static void Apply_CompressiveStrength( CTrussElementObject
            *theObject, CTrussElementObject **thisObjectPtr)
        {
            theObject->CompressiveStrength =
                 (*thisObjectPtr)->CompressiveStrength;
        }

        static void Perform_Draw( CAbstractObject
            *theObject)
        {
            theObject->DrawFinal();
        }



void  CTBWoodTElement::DoYourDialog( void )
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
    (TElementLength * itsTrussPane->theStructureScale / SCREEN_DPI ),
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
       (TElementLength * itsTrussPane->theStructureScale / SCREEN_DPI ))
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
    }else if( ( xLength !=
       ((its2ndEnd.h - its1stEnd.h) * itsTrussPane->theStructureScale
       / SCREEN_DPI ) ) || (yLength !=
       ((its2ndEnd.v - its1stEnd.v) * itsTrussPane->theStructureScale
       / SCREEN_DPI ) ) )
     {
      if( (the2ndEndConnected )  && ( ! the1stEndConnected ))
          /* subtract length from first end*/
      {
        UnSelectYourself();
        Erase();


        its1stEnd.h = its2ndEnd.h - (int)((xLength));
      /*  its1stEnd.v = its2ndEnd.v - (int)((yLength)); */

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
    /*    its2ndEnd.v = its1stEnd.v + (int)((yLength)/
            itsTrussPane->theStructureScale * SCREEN_DPI);
    */
        DrawFinal();
        theTEConcLoadsAndMoments->DoForEach(  Perform_Draw );
        theTEContLoadsAndMoments->DoForEach( Perform_Draw );
        theTENodes->DoForEach( Perform_Draw );

      }
    }
  }
  DHDeallocateRecord(dhp);
}

