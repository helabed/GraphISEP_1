/****
 * CTBGussetPlate.c
 *
 *  CTBGussetPlate object class for a typical CTrussPane class
 *
 ****/
#include "CNodeObject.phs"
#include "CTBGussetPlate.h"


/*** Global Variables ***/


void CTBGussetPlate::InitializeYourself( void )

{
  /*inherited::InitializeYourself();*/

  offSet.h = 0;
  offSet.v = 0;

  itsCenterPoint.h = theHitPoint.h - offSet.h;
  itsCenterPoint.v = theHitPoint.v - offSet.v;

  IamSelected = FALSE;
  ReSizingInProgress = FALSE;
  IamConnected = FALSE;

  itsBoundaryCondition = RotationFixed;

  plateLength = 4.0;
  plateHeight = 3.0;
  alpha = 0.5;
  gamma = 0.5;
  itsAngle = 0.0;
  noOfTeethPerInch = 8;

  itsCenterPointFlag = FALSE;

  theNodeLoads = new( CClustOfConcLoadsAndMoments );
  theNodeLoads->ICluster();
  theNodeTElements = new( CClusterOfTElements );
  theNodeTElements->ICluster();
  ConcLandMAreConnected = FALSE;
  TElementsAreConnected = FALSE;
  dumyBoolean = FALSE;

  itsMotherTElement = NULL;
  DrawFinal();
}
void CTBGussetPlate::AddPicture( void )
{
  inherited::AddPicture();
}

void CTBGussetPlate::RemovePicture( void )
{
  inherited::RemovePicture();
}
void CTBGussetPlate::SelectYourself( void )
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

void CTBGussetPlate::UnSelectYourself( void )
{
  inherited::UnSelectYourself();
  RemovePicture();
}

void CTBGussetPlate::DrawFinal( void )
{
  AddPicture();
  inherited::DrawFinal();
}


void CTBGussetPlate::DoDrawing( void )

{
  inherited::DoDrawing();
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


void CTBGussetPlate::Draw( void )

{
  inherited::Draw();
}


void CTBGussetPlate::DrawNodeOnly( void )
{
  AddPicture();
  inherited::DrawNodeOnly();
}


