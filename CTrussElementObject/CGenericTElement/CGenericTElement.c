/****
 * CGenericTElement.c
 *
 *  CGenericTElement object class for a typical CTrussPane class
 *
 ****/

#include "CTrussElementObject.phs"
#include "CGenericTElement.h"

/*** Global Variables ***/

extern  CBartender *gBartender;
extern   short    gClicks;


void CGenericTElement::Draw( void )
{
  PenState     pnState;


  GetPenState ( &pnState);/* to save the pen setting */
  inherited::Draw();
  SetPenState ( &pnState);/* to resotre pen settting */

}
Boolean CGenericTElement::ConnectYourselfToNode(   CNodeObject
                      *theSelectedNodeObject )
{
  if ( ( theSelectedNodeObject->WhoAreYou() != aGussetPlate))
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
  else
    return FALSE;
}

        static void Apply_E( CTrussElementObject
            *theObject, CTrussElementObject **thisObjectPtr)
        {
            theObject->E = (*thisObjectPtr)->E;
        }
        static void Apply_Ixx( CTrussElementObject
            *theObject, CTrussElementObject **thisObjectPtr)
        {
            theObject->Ixx = (*thisObjectPtr)->Ixx;
        }
        static void Apply_Iyy( CTrussElementObject
            *theObject, CTrussElementObject **thisObjectPtr)
        {
            theObject->Iyy = (*thisObjectPtr)->Iyy;
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

        static void Apply_CrossSectionalArea( CTrussElementObject
            *theObject, CTrussElementObject **thisObjectPtr)
        {
            theObject->Area =
                 (*thisObjectPtr)->Area;
        }

        static void Perform_Draw( CAbstractObject
            *theObject)
        {
            theObject->DrawFinal();
        }


void CGenericTElement::DoYourDialog( void )
{
  DialogHandlerRecordPtr   dhp;
  DecForm          dForm;
  float          xLength;
  float          yLength;
  float          newTElementLength;
  float          TElementLength;
  Boolean          theBoxIsChecked;
  CTrussElementObject    *thisObject;
  float          newTElementRatio;

  thisObject = this;

  DHStandardNewRecord (&dhp, GenericElementDLOG_ID,
              GenericElementUpdateUserItemId,
              GenericElementModulusOfElasticity);


  TElementLength = (float) sqrt((double)(( (((float)(its2ndEnd.v -its1stEnd.v))*
            ((float)(its2ndEnd.v -its1stEnd.v) )) +
            ( ((float)(its2ndEnd.h -its1stEnd.h))*
            ((float)(its2ndEnd.h -its1stEnd.h)) ) ) ) );

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GenericElementLength,
    (TElementLength * itsTrussPane->theStructureScale / SCREEN_DPI ),
      dForm, 0.0, MAXREAL);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GenericElementHorzLength,
    ((its2ndEnd.h - its1stEnd.h) * itsTrussPane->theStructureScale / SCREEN_DPI ),
      dForm, -MAXREAL, MAXREAL);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GenericElementVertLength,
    ((its2ndEnd.v - its1stEnd.v) * itsTrussPane->theStructureScale / SCREEN_DPI ),
      dForm, -MAXREAL, MAXREAL);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GenericElementModulusOfElasticity,
    (E ), dForm, 0.0, MAXREAL);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GenericElementXAxisMOfInertia,
    (Ixx ), dForm, 0.0, MAXREAL);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GenericElementYAxisMOfInertia,
    (Iyy), dForm, 0.0, MAXREAL);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GenericElementBendingStrength,
    (BendingStrength),dForm, 0.0, 50000);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GenericElementTensileStrength,
    (TensileStrength), dForm, 0.0, 50000);/* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GenericElementCompressiveStrength,
    (CompressiveStrength), dForm, 0.0, 50000); /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, GenericElementCrossSectArea,
    (Area), dForm, 0.0, 1000); /* should be limit of drawing area*/

  DHADDCHECKBOX( dhp, GenericElementModulusOfElasticityApplyToAll, FALSE);
  DHADDCHECKBOX( dhp, GenericElementXAxisMOfInertiaApplyToAll, FALSE);
  DHADDCHECKBOX( dhp, GenericElementYAxisMOfInertiaApplyToAll, FALSE);
  DHADDCHECKBOX( dhp, GenericElementBendingStrengthApplyToAll, FALSE);
  DHADDCHECKBOX( dhp, GenericElementTensileStrengthApplyToAll, FALSE);
  DHADDCHECKBOX( dhp, GenericElementCompressiveStrengthApplyToAll, FALSE);
  DHADDCHECKBOX( dhp, GenericElementCrossSectAreaApplyToAll, FALSE);

  if (DHDialogHandler(dhp))
  {

    newTElementLength = DHGetEditReal(dhp, GenericElementLength);
    xLength = DHGetEditReal(dhp, GenericElementHorzLength);
    yLength = DHGetEditReal(dhp, GenericElementVertLength);
    E = DHGetEditReal(dhp, GenericElementModulusOfElasticity);
    Ixx =  DHGetEditReal(dhp, GenericElementXAxisMOfInertia);
    Iyy = DHGetEditReal(dhp, GenericElementYAxisMOfInertia);
    BendingStrength = DHGetEditReal(dhp, GenericElementBendingStrength);
    TensileStrength = DHGetEditReal(dhp, GenericElementTensileStrength);
    CompressiveStrength =  DHGetEditReal(dhp, GenericElementCompressiveStrength);
    Area =  DHGetEditReal(dhp, GenericElementCrossSectArea);


    theBoxIsChecked = DHIsBoxChecked( dhp,
                GenericElementModulusOfElasticityApplyToAll);
    if( theBoxIsChecked )
    {
      itsTrussPane->TElementsCluster->DoForEach1(
        Apply_E, (long)(&thisObject) );
    }

    theBoxIsChecked = DHIsBoxChecked( dhp,
                GenericElementXAxisMOfInertiaApplyToAll);
    if( theBoxIsChecked )
    {
      itsTrussPane->TElementsCluster->DoForEach1(
        Apply_Ixx, (long)(&thisObject) );
    }
    theBoxIsChecked = DHIsBoxChecked( dhp,
                GenericElementYAxisMOfInertiaApplyToAll);
    if( theBoxIsChecked )
    {
      itsTrussPane->TElementsCluster->DoForEach1(
        Apply_Iyy, (long)(&thisObject) );
    }
    theBoxIsChecked = DHIsBoxChecked( dhp,
                GenericElementBendingStrengthApplyToAll);
    if( theBoxIsChecked )
    {
      itsTrussPane->TElementsCluster->DoForEach1(
        Apply_BendingStrength, (long)(&thisObject) );
    }
    theBoxIsChecked = DHIsBoxChecked( dhp,
                GenericElementTensileStrengthApplyToAll);
    if( theBoxIsChecked )
    {
      itsTrussPane->TElementsCluster->DoForEach1(
        Apply_TensileStrength, (long)(&thisObject) );
    }
    theBoxIsChecked = DHIsBoxChecked( dhp,
                GenericElementCompressiveStrengthApplyToAll);
    if( theBoxIsChecked )
    {
      itsTrussPane->TElementsCluster->DoForEach1(
        Apply_CompressiveStrength, (long)(&thisObject) );
    }
    theBoxIsChecked = DHIsBoxChecked( dhp,
                GenericElementCrossSectAreaApplyToAll);
    if( theBoxIsChecked )
    {
      itsTrussPane->TElementsCluster->DoForEach1(
        Apply_CrossSectionalArea, (long)(&thisObject) );
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

