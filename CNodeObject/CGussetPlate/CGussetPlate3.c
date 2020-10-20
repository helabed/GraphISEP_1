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


void  CGussetPlate::PrintDebugInfo( void )
{
  float    xLocation;
  float    yLocation;
  float    scalingFactor;

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

  xLocation = (itsCenterPoint.h * itsTrussPane->theStructureScale
                  / SCREEN_DPI );
  yLocation = (itsCenterPoint.v * itsTrussPane->theStructureScale
                  / SCREEN_DPI );

  fprintf( Debug_Info_Out_File, "\n\nI am gussetPlate %ld\n\n",theObjectNumber );
  fprintf( Debug_Info_Out_File, "itsCenterPoint.h = %f\n",xLocation  );
  fprintf( Debug_Info_Out_File, "itsCenterPoint.v = %f\n",yLocation  );
/*  fprintf( Debug_Info_Out_File, "plateLength = %f\n",plateLength  );
  fprintf( Debug_Info_Out_File, "plateHeight = %f\n",plateHeight  );
  fprintf( Debug_Info_Out_File, "alpha = %f\n",alpha  );
  fprintf( Debug_Info_Out_File, "gamma = %f\n",gamma  );
  fprintf( Debug_Info_Out_File, "itsAngle = %f\n",itsAngle  );
  fprintf( Debug_Info_Out_File, "noOfTeethPerInch = %d\n",noOfTeethPerInch  );

  fprintf( Debug_Info_Out_File, "bottomLeftHOffset = %f\n",bottomLeftHOffset  );
  fprintf( Debug_Info_Out_File, "bottomLeftVOffset = %f\n",bottomLeftVOffset  );


  fprintf( Debug_Info_Out_File, "bottomLeftCorner.h = %f\n",bottomLeftCorner.h  );
  fprintf( Debug_Info_Out_File, "bottomLeftCorner.v = %f\n",bottomLeftCorner.v  );
  fprintf( Debug_Info_Out_File, "bottomRightCorner.h = %f\n",bottomRightCorner.h  );
  fprintf( Debug_Info_Out_File, "bottomRightCorner.v = %f\n",bottomRightCorner.v  );
  fprintf( Debug_Info_Out_File, "topRightCorner.h = %f\n",topRightCorner.h  );
  fprintf( Debug_Info_Out_File, "topRightCorner.v = %f\n",topRightCorner.v  );
  fprintf( Debug_Info_Out_File, "topLeftCorner.h = %f\n",topLeftCorner.h  );
  fprintf( Debug_Info_Out_File, "topLeftCorner.v = %f\n",topLeftCorner.v  );
*/  fprintf( Debug_Info_Out_File, "masterPlateLocation.h = %f\n",masterPlateLocation.h  );
  fprintf( Debug_Info_Out_File, "masterPlateLocation.v = %f\n",masterPlateLocation.v  );

  fprintf( Debug_Info_Out_File, "itsMotherTEGlobalNumber = %ld\n",
                          itsMotherTEGlobalNumber  );

  fprintf( Debug_Info_Out_File, "itsGlobalNumber = %ld\n",
                          itsGlobalNumber  );


/*struct  CGussetPDoc      *itsDocument;
    Boolean        positionningMasterPlateNode;
    Boolean        placingInProgress;
    Boolean        topLeftCornerFlag;
    Boolean        bottomRightCornerFlag;
    Boolean        bottomLeftCornerFlag;
    Boolean        topRightCornerFlag;
    Boolean        masterPlateFlag;
    Boolean        itsOwnAngleFlag;

    FloatPoint      itsMotherTEPolygon[ MAX_POINT_IN_POLYGON ];
    int          itsMotherTEPolyPointCounter;
    float        itsMotherTEConnectorArea;
    float        itsMotherTEIxx;
    float        itsMotherTEIyy;
    FloatPoint      itsMotherTECentroid;
    long        itsMotherTEGlobalNumber;
*/
}
void  CGussetPlate::PrintFileStatics( void )
{
}


void  CGussetPlate::PrintFileFireWood( void )
{
  FloatPoint      theTransformedPoint;
  float         itsCosine = 1.0;
  float         itsSine = 0.0;
  float        theHorizCenter;
  float        theVertCenter;
  FloatPoint      masterPlateLocation;
  FloatPoint      bottomLeftTEMP;
  Point        masterPlateLocationPoint;
  Point        bottomLeftTEMPpoint;
  float        scalingFactor;
  CGussetPlate    *thisObject;

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

  scalingFactor = SCREEN_DPI / ((( CGussetPane *)(thisObject->
        itsDocument->itsMainPane))->
                  theStructureScale);

  masterPlateLocation.v = this->masterPlateLocation.v* scalingFactor;
  masterPlateLocation.h = this->masterPlateLocation.h * scalingFactor;

  bottomLeftTEMP.h = bottomLeftHOffset * scalingFactor;
  bottomLeftTEMP.v = bottomLeftVOffset * scalingFactor;

  bottomLeftTEMPpoint = TransformTElementToPano( bottomLeftTEMP,
                 itsCenterPoint);



  masterPlateLocationPoint = TransformTElementToPano(masterPlateLocation,
                    bottomLeftTEMPpoint);


  fprintf( Wood_Out_File, "\n%.3f\t", plateLength );
  fprintf( Wood_Out_File, "%.3f\t", plateHeight );
  fprintf( Wood_Out_File, "%.3f\t", alpha );
  fprintf( Wood_Out_File, "%.3f\t", gamma );
  fprintf( Wood_Out_File, "%.3f\t", 360.0 - itsAngle );
  fprintf( Wood_Out_File, "%d\t", noOfTeethPerInch );

  if( itsMotherTElement )
  {
    theHorizCenter = tempCenter.h;
    theVertCenter = tempCenter.v;
  }
  else
  {
    theHorizCenter = (itsCenterPoint.h * itsTrussPane->theStructureScale / SCREEN_DPI );
    theVertCenter = (itsCenterPoint.v * itsTrussPane->theStructureScale / SCREEN_DPI );
  }

  theTransformedPoint  = TransformPanoToGloabal( masterPlateLocationPoint,
                    itsCenterPoint );
  theHorizCenter += theTransformedPoint.h/scalingFactor;
  theVertCenter += theTransformedPoint.v/scalingFactor;
  fprintf( Wood_Out_File, "%f\t", theHorizCenter );
  fprintf( Wood_Out_File, "%f\t",  LargestYValue - theVertCenter );

}

  static FloatPoint CalcCentroid_TE1stEndOffset( CGussetPlate *thePlate,
                      CRegularWoodTElement *theTE )
  {
    FloatPoint      theTransformedPoint;
    float        theHorizCenter;
    float        theVertCenter;
    FloatPoint      masterPlateLocation;
    FloatPoint      bottomLeftTEMP;
    FloatPoint      tempFloatPoint;
    Point        tempPoint;
    Point        masterPlateLocationPoint;
    Point        bottomLeftTEMPpoint;
    float        scalingFactor;
    CGussetPlate    *thisObject;

              /* first end centroid of connec. area  location */
    float      firstEndCentHorizLoc;
    float      firstEndCentVertLoc;
    FloatPoint    Centroid_TEEndOffset;

    FloatPoint      its1stEnd;
    FloatPoint      its2ndEnd;
    float        its1stEndHorz;
    float        its1stEndVert;
    float        its2ndEndHorz;
    float        its2ndEndVert;
    Point        itsCenterPoint;
    FloatPoint      tempCenter;


    if( thePlate->itsMotherTElement )
    {
      scalingFactor = SCREEN_DPI / (thePlate->itsTrussPane->theStructureScale);

      its1stEnd.v = ((float)thePlate->itsMotherTElement->its1stEnd.v) +
        (((CRegularWoodTElement *)thePlate->itsMotherTElement)->its1stEndVOffset * scalingFactor);
      its1stEnd.h = ((float)thePlate->itsMotherTElement->its1stEnd.h) +
        (((CRegularWoodTElement *)thePlate->itsMotherTElement)->its1stEndHOffset * scalingFactor);
      its2ndEnd.v = ((float)thePlate->itsMotherTElement->its2ndEnd.v) +
        (((CRegularWoodTElement *)thePlate->itsMotherTElement)->its2ndEndVOffset * scalingFactor);
      its2ndEnd.h = ((float)thePlate->itsMotherTElement->its2ndEnd.h) +
        (((CRegularWoodTElement *)thePlate->itsMotherTElement)->its2ndEndHOffset * scalingFactor);


      its1stEndHorz = (its1stEnd.h * thePlate->itsTrussPane->theStructureScale / SCREEN_DPI );
      its1stEndVert = (its1stEnd.v * thePlate->itsTrussPane->theStructureScale / SCREEN_DPI );
      its2ndEndHorz = (its2ndEnd.h * thePlate->itsTrussPane->theStructureScale / SCREEN_DPI );
      its2ndEndVert = (its2ndEnd.v * thePlate->itsTrussPane->theStructureScale / SCREEN_DPI );


      tempCenter.h = ((( thePlate->TElementConnectionRatio *
              (its2ndEndHorz -  its1stEndHorz ) ) +  its1stEndHorz ));
      tempCenter.v = ((( thePlate->TElementConnectionRatio *
              (its2ndEndVert -  its1stEndVert ) ) +  its1stEndVert ));

      itsCenterPoint.h = ((int)((tempCenter.h) * SCREEN_DPI / thePlate->itsTrussPane->theStructureScale));
      itsCenterPoint.v = ((int)((tempCenter.v) * SCREEN_DPI / thePlate->itsTrussPane->theStructureScale));


    }
    else
    {
      itsCenterPoint = thePlate->itsCenterPoint;
    }


    scalingFactor = SCREEN_DPI / ((( CGussetPane *)(thePlate->
          itsDocument->itsMainPane))->theStructureScale);

    masterPlateLocation.v = thePlate->masterPlateLocation.v * scalingFactor;
    masterPlateLocation.h = thePlate->masterPlateLocation.h * scalingFactor;

    bottomLeftTEMP.h = thePlate->bottomLeftHOffset * scalingFactor;
    bottomLeftTEMP.v = thePlate->bottomLeftVOffset * scalingFactor;

    bottomLeftTEMPpoint = thePlate->TransformTElementToPano( bottomLeftTEMP,
                  itsCenterPoint);



    masterPlateLocationPoint = thePlate->TransformTElementToPano(masterPlateLocation,
                      bottomLeftTEMPpoint);

    theHorizCenter = (itsCenterPoint.h *
          thePlate->itsTrussPane->theStructureScale / SCREEN_DPI );
    theVertCenter = (itsCenterPoint.v *
          thePlate->itsTrussPane->theStructureScale / SCREEN_DPI );

    theTransformedPoint  = thePlate->TransformPanoToGloabal( masterPlateLocationPoint,
                      itsCenterPoint );
          /* global coordinates of Master plate location */
    theHorizCenter += theTransformedPoint.h/scalingFactor;
    theVertCenter += theTransformedPoint.v/scalingFactor;

    firstEndCentHorizLoc = theHorizCenter + theTE->firstEndCentroid.h;
    firstEndCentVertLoc = theVertCenter + theTE->firstEndCentroid.v;

    scalingFactor = SCREEN_DPI / (theTE->itsTrussPane->theStructureScale);

    its1stEnd.v = ((float)theTE->its1stEnd.v) +  (theTE->its1stEndVOffset * scalingFactor);
    its1stEnd.h = ((float)theTE->its1stEnd.h) +  (theTE->its1stEndHOffset * scalingFactor);
    its2ndEnd.v = ((float)theTE->its2ndEnd.v) +  (theTE->its2ndEndVOffset * scalingFactor);
    its2ndEnd.h = ((float)theTE->its2ndEnd.h) +  (theTE->its2ndEndHOffset * scalingFactor);

    its1stEndHorz = (its1stEnd.h * theTE->itsTrussPane->theStructureScale / SCREEN_DPI );
    its1stEndVert = (its1stEnd.v * theTE->itsTrussPane->theStructureScale / SCREEN_DPI );
    its2ndEndHorz = (its2ndEnd.h * theTE->itsTrussPane->theStructureScale / SCREEN_DPI );
    its2ndEndVert = (its2ndEnd.v * theTE->itsTrussPane->theStructureScale / SCREEN_DPI );

    Centroid_TEEndOffset.h = its1stEndHorz - firstEndCentHorizLoc;
    Centroid_TEEndOffset.v = its1stEndVert - firstEndCentVertLoc;

    return Centroid_TEEndOffset;
  }

  static FloatPoint CalcCentroid_TE2ndEndOffset( CGussetPlate *thePlate,
                      CRegularWoodTElement *theTE )
  {
    FloatPoint      theTransformedPoint;
    float        theHorizCenter;
    float        theVertCenter;
    FloatPoint      masterPlateLocation;
    FloatPoint      bottomLeftTEMP;
    FloatPoint      tempFloatPoint;
    Point        tempPoint;
    Point        masterPlateLocationPoint;
    Point        bottomLeftTEMPpoint;
    float        scalingFactor;
    CGussetPlate    *thisObject;

                  /* second end centroid of connec. area  location */
    float      secondEndCentHorizLoc;
    float      secondEndCentVertLoc;
    FloatPoint    Centroid_TEEndOffset;

    FloatPoint      its1stEnd;
    FloatPoint      its2ndEnd;
    float        its1stEndHorz;
    float        its1stEndVert;
    float        its2ndEndHorz;
    float        its2ndEndVert;
    Point        itsCenterPoint;
    FloatPoint      tempCenter;


    if( thePlate->itsMotherTElement )
    {
      scalingFactor = SCREEN_DPI / (thePlate->itsTrussPane->theStructureScale);

      its1stEnd.v = ((float)thePlate->itsMotherTElement->its1stEnd.v) +
        (((CRegularWoodTElement *)thePlate->itsMotherTElement)->its1stEndVOffset * scalingFactor);
      its1stEnd.h = ((float)thePlate->itsMotherTElement->its1stEnd.h) +
        (((CRegularWoodTElement *)thePlate->itsMotherTElement)->its1stEndHOffset * scalingFactor);
      its2ndEnd.v = ((float)thePlate->itsMotherTElement->its2ndEnd.v) +
        (((CRegularWoodTElement *)thePlate->itsMotherTElement)->its2ndEndVOffset * scalingFactor);
      its2ndEnd.h = ((float)thePlate->itsMotherTElement->its2ndEnd.h) +
        (((CRegularWoodTElement *)thePlate->itsMotherTElement)->its2ndEndHOffset * scalingFactor);


      its1stEndHorz = (its1stEnd.h * thePlate->itsTrussPane->theStructureScale / SCREEN_DPI );
      its1stEndVert = (its1stEnd.v * thePlate->itsTrussPane->theStructureScale / SCREEN_DPI );
      its2ndEndHorz = (its2ndEnd.h * thePlate->itsTrussPane->theStructureScale / SCREEN_DPI );
      its2ndEndVert = (its2ndEnd.v * thePlate->itsTrussPane->theStructureScale / SCREEN_DPI );


      tempCenter.h = ((( thePlate->TElementConnectionRatio *
              (its2ndEndHorz -  its1stEndHorz ) ) +  its1stEndHorz ));
      tempCenter.v = ((( thePlate->TElementConnectionRatio *
              (its2ndEndVert -  its1stEndVert ) ) +  its1stEndVert ));

      itsCenterPoint.h = ((int)((tempCenter.h) * SCREEN_DPI / thePlate->itsTrussPane->theStructureScale));
      itsCenterPoint.v = ((int)((tempCenter.v) * SCREEN_DPI / thePlate->itsTrussPane->theStructureScale));


    }
    else
    {
      itsCenterPoint = thePlate->itsCenterPoint;
    }


    scalingFactor = SCREEN_DPI / ((( CGussetPane *)(thePlate->
          itsDocument->itsMainPane))->theStructureScale);

    masterPlateLocation.v = thePlate->masterPlateLocation.v * scalingFactor;
    masterPlateLocation.h = thePlate->masterPlateLocation.h * scalingFactor;

    bottomLeftTEMP.h = thePlate->bottomLeftHOffset * scalingFactor;
    bottomLeftTEMP.v = thePlate->bottomLeftVOffset * scalingFactor;

    bottomLeftTEMPpoint = thePlate->TransformTElementToPano( bottomLeftTEMP,
                  itsCenterPoint);



    masterPlateLocationPoint = thePlate->TransformTElementToPano(masterPlateLocation,
                      bottomLeftTEMPpoint);

    theHorizCenter = (itsCenterPoint.h *
          thePlate->itsTrussPane->theStructureScale / SCREEN_DPI );
    theVertCenter = (itsCenterPoint.v *
          thePlate->itsTrussPane->theStructureScale / SCREEN_DPI );

    theTransformedPoint  = thePlate->TransformPanoToGloabal( masterPlateLocationPoint,
                      itsCenterPoint );
          /* global coordinates of Master plate location */
    theHorizCenter += theTransformedPoint.h/scalingFactor;
    theVertCenter += theTransformedPoint.v/scalingFactor;

    secondEndCentHorizLoc = theHorizCenter + theTE->secondEndCentroid.h;
    secondEndCentVertLoc = theVertCenter + theTE->secondEndCentroid.v;

    scalingFactor = SCREEN_DPI / (theTE->itsTrussPane->theStructureScale);

    its1stEnd.v = ((float)theTE->its1stEnd.v) +  (theTE->its1stEndVOffset * scalingFactor);
    its1stEnd.h = ((float)theTE->its1stEnd.h) +  (theTE->its1stEndHOffset * scalingFactor);
    its2ndEnd.v = ((float)theTE->its2ndEnd.v) +  (theTE->its2ndEndVOffset * scalingFactor);
    its2ndEnd.h = ((float)theTE->its2ndEnd.h) +  (theTE->its2ndEndHOffset * scalingFactor);

    its1stEndHorz = (its1stEnd.h * theTE->itsTrussPane->theStructureScale / SCREEN_DPI );
    its1stEndVert = (its1stEnd.v * theTE->itsTrussPane->theStructureScale / SCREEN_DPI );
    its2ndEndHorz = (its2ndEnd.h * theTE->itsTrussPane->theStructureScale / SCREEN_DPI );
    its2ndEndVert = (its2ndEnd.v * theTE->itsTrussPane->theStructureScale / SCREEN_DPI );

    Centroid_TEEndOffset.h = its2ndEndHorz - secondEndCentHorizLoc;
    Centroid_TEEndOffset.v = its2ndEndVert - secondEndCentVertLoc;

    return Centroid_TEEndOffset;
  }


  static FloatPoint CalcCentroid_MotherTEEndOffset( CGussetPlate *thePlate,
                      CRegularWoodTElement *theTE )
  {
    FloatPoint      theTransformedPoint;
    float        theHorizCenter;
    float        theVertCenter;
    float        theHorizCenterPoint;
    float        theVertCenterPoint;
    FloatPoint      masterPlateLocation;
    FloatPoint      bottomLeftTEMP;
    FloatPoint      tempFloatPoint;
    Point        tempPoint;
    Point        masterPlateLocationPoint;
    Point        bottomLeftTEMPpoint;
    float        scalingFactor;
    CGussetPlate    *thisObject;

              /* mother TE  centroid of connec. area  location */
    float      motherTECentHorizLoc;
    float      motherTECentVertLoc;
    FloatPoint    Centroid_TEEndOffset;


    FloatPoint      its1stEnd;
    FloatPoint      its2ndEnd;
    float        its1stEndHorz;
    float        its1stEndVert;
    float        its2ndEndHorz;
    float        its2ndEndVert;
    Point        itsCenterPoint;
    FloatPoint      tempCenter;


    if( thePlate->itsMotherTElement )
    {
      scalingFactor = SCREEN_DPI / (thePlate->itsTrussPane->theStructureScale);

      its1stEnd.v = ((float)thePlate->itsMotherTElement->its1stEnd.v) +
        (((CRegularWoodTElement *)thePlate->itsMotherTElement)->its1stEndVOffset * scalingFactor);
      its1stEnd.h = ((float)thePlate->itsMotherTElement->its1stEnd.h) +
        (((CRegularWoodTElement *)thePlate->itsMotherTElement)->its1stEndHOffset * scalingFactor);
      its2ndEnd.v = ((float)thePlate->itsMotherTElement->its2ndEnd.v) +
        (((CRegularWoodTElement *)thePlate->itsMotherTElement)->its2ndEndVOffset * scalingFactor);
      its2ndEnd.h = ((float)thePlate->itsMotherTElement->its2ndEnd.h) +
        (((CRegularWoodTElement *)thePlate->itsMotherTElement)->its2ndEndHOffset * scalingFactor);


      its1stEndHorz = (its1stEnd.h * thePlate->itsTrussPane->theStructureScale / SCREEN_DPI );
      its1stEndVert = (its1stEnd.v * thePlate->itsTrussPane->theStructureScale / SCREEN_DPI );
      its2ndEndHorz = (its2ndEnd.h * thePlate->itsTrussPane->theStructureScale / SCREEN_DPI );
      its2ndEndVert = (its2ndEnd.v * thePlate->itsTrussPane->theStructureScale / SCREEN_DPI );


      tempCenter.h = ((( thePlate->TElementConnectionRatio *
              (its2ndEndHorz -  its1stEndHorz ) ) +  its1stEndHorz ));
      tempCenter.v = ((( thePlate->TElementConnectionRatio *
              (its2ndEndVert -  its1stEndVert ) ) +  its1stEndVert ));

      itsCenterPoint.h = ((int)((tempCenter.h) * SCREEN_DPI / thePlate->itsTrussPane->theStructureScale));
      itsCenterPoint.v = ((int)((tempCenter.v) * SCREEN_DPI / thePlate->itsTrussPane->theStructureScale));


    }
    else
    {
      itsCenterPoint = thePlate->itsCenterPoint;
    }


    scalingFactor = SCREEN_DPI / ((( CGussetPane *)(thePlate->
          itsDocument->itsMainPane))->theStructureScale);

    masterPlateLocation.v = thePlate->masterPlateLocation.v * scalingFactor;
    masterPlateLocation.h = thePlate->masterPlateLocation.h * scalingFactor;

    bottomLeftTEMP.h = thePlate->bottomLeftHOffset * scalingFactor;
    bottomLeftTEMP.v = thePlate->bottomLeftVOffset * scalingFactor;

    bottomLeftTEMPpoint = thePlate->TransformTElementToPano( bottomLeftTEMP,
                  itsCenterPoint);

    masterPlateLocationPoint = thePlate->TransformTElementToPano(masterPlateLocation,
                      bottomLeftTEMPpoint);

    theHorizCenterPoint = (itsCenterPoint.h *
          thePlate->itsTrussPane->theStructureScale / SCREEN_DPI );
    theVertCenterPoint = (itsCenterPoint.v *
          thePlate->itsTrussPane->theStructureScale / SCREEN_DPI );

    theTransformedPoint  = thePlate->TransformPanoToGloabal( masterPlateLocationPoint,
                      itsCenterPoint );

          /* global coordinates of Master plate location */
    theHorizCenter = theHorizCenterPoint + theTransformedPoint.h/scalingFactor;
    theVertCenter = theVertCenterPoint + theTransformedPoint.v/scalingFactor;

    motherTECentHorizLoc = theHorizCenter + thePlate->itsMotherTECentroid.h;
    motherTECentVertLoc = theVertCenter + thePlate->itsMotherTECentroid.v;

    Centroid_TEEndOffset.h = theHorizCenterPoint - motherTECentHorizLoc;
    Centroid_TEEndOffset.v = theVertCenterPoint - motherTECentVertLoc;

    return Centroid_TEEndOffset;
  }


  static void Print_TEGlobalNumber( CRegularWoodTElement *theObject,
                             CGussetPlate **thisObjectPtr)
  {
    Boolean    whichEndIsConnected;
    FloatPoint  Centroid_TEEndOffset;

    whichEndIsConnected = theObject->WhichEndIsConnected( (*thisObjectPtr) );
    if( whichEndIsConnected == 1)
    {
      fprintf( Wood_Out_File, "\n%ld\t", ++NumberOfPlateSprings );
      fprintf( Wood_Out_File, "%ld\t", (*thisObjectPtr)->itsGlobalNumber );
      fprintf( Wood_Out_File, "%ld\t", theObject->its1stEndGlobalNumber );
      fprintf( Wood_Out_File, "%f\t", theObject->firstEndConnectorArea );
      fprintf( Wood_Out_File, "%f\t", theObject->firstEndIxx );
      fprintf( Wood_Out_File, "%f\t", theObject->firstEndIyy );
      fprintf( Wood_Out_File, "%f\t", theObject->firstEndCentroid.h );
      fprintf( Wood_Out_File, "%f\t", -(theObject->firstEndCentroid.v) );

      Centroid_TEEndOffset = CalcCentroid_TE1stEndOffset( (*thisObjectPtr),
                          theObject );
      fprintf( Wood_Out_File, "%f\t", Centroid_TEEndOffset.h );
      fprintf( Wood_Out_File, "%f\t", -Centroid_TEEndOffset.v );

    }
    else if ( whichEndIsConnected == 2 )
    {
      fprintf( Wood_Out_File, "\n%ld\t", ++NumberOfPlateSprings );
      fprintf( Wood_Out_File, "%ld\t", (*thisObjectPtr)->itsGlobalNumber );
      fprintf( Wood_Out_File, "%ld\t", theObject->its2ndEndGlobalNumber );
      fprintf( Wood_Out_File, "%f\t", theObject->secondEndConnectorArea );
      fprintf( Wood_Out_File, "%f\t", theObject->secondEndIxx );
      fprintf( Wood_Out_File, "%f\t", theObject->secondEndIyy );
      fprintf( Wood_Out_File, "%f\t", theObject->secondEndCentroid.h );
      fprintf( Wood_Out_File, "%f\t", -(theObject->secondEndCentroid.v) );

      Centroid_TEEndOffset = CalcCentroid_TE2ndEndOffset( (*thisObjectPtr),
                          theObject );
      fprintf( Wood_Out_File, "%f\t", Centroid_TEEndOffset.h );
      fprintf( Wood_Out_File, "%f\t", -Centroid_TEEndOffset.v );


    }
  }

  static void Update_NumberOfSprings( CRegularWoodTElement *theObject,
                             CGussetPlate **thisObjectPtr)
  {
     ++NumberOfPlateSprings;
  }

void  CGussetPlate::PrintFileWood5( void )
{
  CGussetPlate  *thisObject;

  thisObject = this;

  theNodeTElements->DoForEach1( Update_NumberOfSprings, (long)(&thisObject) );
  if( itsMotherTElement )
  {
    ++NumberOfPlateSprings ;
  }
}


void  CGussetPlate::PrintFileWood1( void )
{
  CGussetPlate  *thisObject;
  FloatPoint  Centroid_TEEndOffset;

  thisObject = this;


  theNodeTElements->DoForEach1( Print_TEGlobalNumber, (long)(&thisObject) );
  if( itsMotherTElement )
  {
    fprintf( Wood_Out_File, "\n%ld\t", ++NumberOfPlateSprings );
    fprintf( Wood_Out_File, "%ld\t", itsGlobalNumber );
    fprintf( Wood_Out_File, "%ld\t", itsMotherTEGlobalNumber );
    fprintf( Wood_Out_File, "%f\t", itsMotherTEConnectorArea );
    fprintf( Wood_Out_File, "%f\t", itsMotherTEIxx );
    fprintf( Wood_Out_File, "%f\t", itsMotherTEIyy );
    fprintf( Wood_Out_File, "%f\t", itsMotherTECentroid.h );
    fprintf( Wood_Out_File, "%f\t", -itsMotherTECentroid.v );

    Centroid_TEEndOffset = CalcCentroid_MotherTEEndOffset( thisObject,
                        (CRegularWoodTElement *)itsMotherTElement );
    fprintf( Wood_Out_File, "%f\t", Centroid_TEEndOffset.h );
    fprintf( Wood_Out_File, "%f\t", -Centroid_TEEndOffset.v );

  }


}
void  CGussetPlate::PrintFileWood2( void )
{
  fprintf( Wood_Out_File, "\n%ld\t", itsGlobalNumber );
  fprintf( Wood_Out_File, "\n%12.2f\t\t", foschiNumbers[ 1 ][ 1 ] );
  fprintf( Wood_Out_File, "%12.2f\t\t", foschiNumbers[ 1 ][ 2 ] );
  fprintf( Wood_Out_File, "%12.2f\t\t", foschiNumbers[ 1 ][ 3 ] );
  fprintf( Wood_Out_File, "\n%12.2f\t\t", foschiNumbers[ 2 ][ 1 ] );
  fprintf( Wood_Out_File, "%12.2f\t\t", foschiNumbers[ 2 ][ 2 ] );
  fprintf( Wood_Out_File, "%12.2f\t\t", foschiNumbers[ 2 ][ 3 ] );
  fprintf( Wood_Out_File, "\n%12.2f\t\t", foschiNumbers[ 3 ][ 1 ] );
  fprintf( Wood_Out_File, "%12.2f\t\t", foschiNumbers[ 3 ][ 2 ] );
  fprintf( Wood_Out_File, "%12.2f\t\t", foschiNumbers[ 3 ][ 3 ] );
  fprintf( Wood_Out_File, "\n%12.2f\t\t", foschiNumbers[ 4 ][ 1 ] );
  fprintf( Wood_Out_File, "%12.2f\t\t", foschiNumbers[ 4 ][ 2 ] );
  fprintf( Wood_Out_File, "%12.2f\t\t", foschiNumbers[ 4 ][ 3 ] );
      /* foschi numbers matrix */
}


  static Boolean IsBoundaryConditionSet( CRegularWoodTElement *theObject,
            NodeAndGlobNumber    *thePlateAndGlobalNumPtr)
  {
    Boolean    boundaryConditionIsSet = FALSE;
    short    whichEndIsConnected;

    whichEndIsConnected = theObject->WhichEndIsConnected(
                      ((CGussetPlate *)((*thePlateAndGlobalNumPtr).theNode)) );
    if( whichEndIsConnected == 1)
    {
      if( theObject->its1stEndBCondIsSet )
      {
        boundaryConditionIsSet = TRUE;
        (*thePlateAndGlobalNumPtr).theGlobalNumber = theObject->its1stEndGlobalNumber;
      }
      else
      {
        boundaryConditionIsSet = FALSE;
      }
    }
    else if ( whichEndIsConnected == 2 )
    {
      if( theObject->its2ndEndBCondIsSet )
      {
        boundaryConditionIsSet = TRUE;
        (*thePlateAndGlobalNumPtr).theGlobalNumber = theObject->its2ndEndGlobalNumber;
      }
      else
      {
        boundaryConditionIsSet = FALSE;
      }
    }
    return ( boundaryConditionIsSet );
  }

void  CGussetPlate::PrintFileWood3( void )
{
  long          theGlobalNumber;
  CGussetPlate      *thisObject;
  CRegularWoodTElement   *theWoodMember;
  NodeAndGlobNumber    thePlateAndGlobalNum;

  thisObject = this;
  thePlateAndGlobalNum.theNode = this;


  theWoodMember = (CRegularWoodTElement *)theNodeTElements->
              FindItem1( IsBoundaryConditionSet,
              ( long )( &thePlateAndGlobalNum) );
  if ( theWoodMember )
  {
    theGlobalNumber =   thePlateAndGlobalNum.theGlobalNumber;

  }
  else if( itsMotherTElement && itsMotherTEBCIsSet )
  {
    theGlobalNumber = itsMotherTEGlobalNumber;
  }
  else
  {
    theGlobalNumber = itsGlobalNumber;
  }

  switch( itsBoundaryCondition )
  {
    case Free:
      break;

    case RotationFixed:
      fprintf( Wood_Out_File, "\n%ld\t", theGlobalNumber );
      fprintf( Wood_Out_File, "0\t0\t1" );
      break;

    case xTranslationFixed:
      fprintf( Wood_Out_File, "\n%ld\t", theGlobalNumber );
      fprintf( Wood_Out_File, "1\t0\t0" );
      break;

    case yTranslationFixed:
      fprintf( Wood_Out_File, "\n%ld\t", theGlobalNumber );
      fprintf( Wood_Out_File, "0\t1\t0" );
      break;

    case xyTranslationFixed:
      fprintf( Wood_Out_File, "\n%ld\t", theGlobalNumber );
      fprintf( Wood_Out_File, "1\t1\t0" );
      break;

    case xyTranslationAndRotationFixed:
      fprintf( Wood_Out_File, "\n%ld\t", theGlobalNumber );
      fprintf( Wood_Out_File, "1\t1\t1" );
      break;

    case xTranslationAndRotationFixed:
      fprintf( Wood_Out_File, "\n%ld\t", theGlobalNumber );
      fprintf( Wood_Out_File, "1\t0\t1" );
      break;

    case yTranslationAndRotationFixed:
      fprintf( Wood_Out_File, "\n%ld\t", theGlobalNumber );
      fprintf( Wood_Out_File, "0\t1\t1" );
      break;
  }
}

  static void Calc_JointForces( CConcLoadObject *theObject,
                JointForcesAndPlate  *forcesAndPlatePtr)
  {

    switch( theObject->WhoAreYou() )
    {
      case aConcentratedLoad:
        (*forcesAndPlatePtr).xComponentOfConcLoad +=
          ((theObject->its2ndEnd.h - theObject->its1stEnd.h) *
                  theObject->itsTrussPane->theLoadScale / SCREEN_DPI );
        (*forcesAndPlatePtr).yComponentOfConcLoad +=
          ((theObject->its2ndEnd.v - theObject->its1stEnd.v) *
                  theObject->itsTrussPane->theLoadScale / SCREEN_DPI );
        break;

      case aConcentratedMoment:
        (*forcesAndPlatePtr).concMoment +=   ((CConcMoment *)theObject)->itsMagnitude;
        break;
    }
  }


  static Boolean AreLoadsInherited( CRegularWoodTElement *theObject,
            NodeAndGlobNumber    *thePlateAndGlobalNumPtr)
  {
    Boolean    loadsAreInherited = FALSE;
    short    whichEndIsConnected;

    whichEndIsConnected = theObject->WhichEndIsConnected(
                      ((CGussetPlate *)((*thePlateAndGlobalNumPtr).theNode)) );
    if( whichEndIsConnected == 1)
    {
      if( theObject->inherit1stEndPlateLoads )
      {
        loadsAreInherited = TRUE;
        (*thePlateAndGlobalNumPtr).theGlobalNumber = theObject->its1stEndGlobalNumber;
      }
      else
      {
        loadsAreInherited = FALSE;
      }
    }
    else if ( whichEndIsConnected == 2 )
    {
      if( theObject->inherit2ndEndPlateLoads )
      {
        loadsAreInherited = TRUE;
        (*thePlateAndGlobalNumPtr).theGlobalNumber = theObject->its2ndEndGlobalNumber;
      }
      else
      {
        loadsAreInherited = FALSE;
      }
    }
    return ( loadsAreInherited );
  }



void  CGussetPlate::PrintFileWood4( void )
{
  JointForcesAndPlate      forcesAndPlate;
  long            theGlobalNumber;
  CGussetPlate        *thisObject;
  CRegularWoodTElement     *theWoodMember;
  NodeAndGlobNumber      thePlateAndGlobalNum;

  thisObject = this;
  thePlateAndGlobalNum.theNode = this;


  theWoodMember = (CRegularWoodTElement *)theNodeTElements->
              FindItem1( AreLoadsInherited,
              ( long )( &thePlateAndGlobalNum) );
  if ( theWoodMember )
  {
    theGlobalNumber =   thePlateAndGlobalNum.theGlobalNumber;

  }
  else if( itsMotherTElement && itsMotherTE_InheritsPlateLoads )
  {
    theGlobalNumber = itsMotherTEGlobalNumber;
  }
  else
  {
    theGlobalNumber = itsGlobalNumber;
  }

  thisObject = this;
  forcesAndPlate.xComponentOfConcLoad = 0;
  forcesAndPlate.yComponentOfConcLoad = 0;
  forcesAndPlate.concMoment = 0;
  forcesAndPlate.thePlate = thisObject;

  if ( ConcLandMAreConnected && theNodeLoads->numItems )
  {
    theNodeLoads->DoForEach1( Calc_JointForces, (long)(&forcesAndPlate) );
    fprintf( Wood_Out_File, "\n%ld\t", theGlobalNumber );
    fprintf( Wood_Out_File, "%f\t", forcesAndPlate.xComponentOfConcLoad );
    fprintf( Wood_Out_File, "%f\t", -forcesAndPlate.yComponentOfConcLoad);
    fprintf( Wood_Out_File, "%f\t", -forcesAndPlate.concMoment );
  }
}


void  CGussetPlate::KillYourself_IF_NOT_Connected( void )
{
  inherited::KillYourself_IF_NOT_Connected();
}
void  CGussetPlate::SaveYourself( void )
{
}
void  CGussetPlate::LoadYourself( void )
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

void CGussetPlate::PerformGlobalNumbering( long  *theGlobalNumberPtr )
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

     if( itsMotherTElement )
     {
       (*theGlobalNumberPtr)++;
       itsMotherTEGlobalNumber = (*theGlobalNumberPtr);
     }
}

void CGussetPlate::InitializeGlobalNumbers( void )
{
  inherited::InitializeGlobalNumbers();
  itsMotherTEGlobalNumber = 0L;
}

void CGussetPlate::Calc_itsMotherTEConnectorAreaProp(void)
{
  short        whichEndConnected;
  int          loopCounter;
  FloatPoint      tempFloatPoint1;
  FloatPoint      tempFloatPoint2;
  float        tempSumation1 = 0;
  float        tempSumation2 = 0;
  float        tempConncArea = 0;
  FloatPoint      itsMotherTEPolygon[ MAX_POINT_IN_POLYGON + 2];
  int          itsMotherTEPolyPointCounter;
  FloatPoint        one;
  FloatPoint        two;
  FloatPoint        dumy;

  itsMotherTEPolyPointCounter = this->itsMotherTEPolyPointCounter + 2;

  (itsMotherTEPolygon[ 0 ]).h = 0.0;
  (itsMotherTEPolygon[ 0 ]).v = 0.0;
  for( loopCounter = 0; loopCounter < (itsMotherTEPolyPointCounter - 1);
                      loopCounter++)
  {
    dumy = this->itsMotherTEPolygon[ loopCounter ];
    itsMotherTEPolygon[ loopCounter + 1 ] = dumy;
  }
  (itsMotherTEPolygon[ (itsMotherTEPolyPointCounter - 1) ]).h = 0.0;
  (itsMotherTEPolygon[ (itsMotherTEPolyPointCounter - 1) ]).v = 0.0;


  for( loopCounter = 0; loopCounter < (itsMotherTEPolyPointCounter - 1);
                      loopCounter++)
  {
    one = itsMotherTEPolygon[ loopCounter ];
    two = itsMotherTEPolygon[ (loopCounter + 1 )];

    tempConncArea =  ( ( one.h - two.h ) * ( one.v + two.v ) / 2);
    itsMotherTEConnectorArea +=  tempConncArea;
  }

  for( loopCounter = 0; loopCounter < (itsMotherTEPolyPointCounter - 1);
                      loopCounter++)
  {
    one = itsMotherTEPolygon[ loopCounter ];
    two = itsMotherTEPolygon[ (loopCounter + 1 )];

    itsMotherTECentroid.h += ( ( two.v - one.v ) * ( one.h * one.h + one.h * two.h + two.h * two.h ) ) / ( 6 * itsMotherTEConnectorArea);
    itsMotherTECentroid.v += ( ( one.h - two.h ) * ( one.v * one.v + one.v * two.v + two.v * two.v ) ) / ( 6 * itsMotherTEConnectorArea);


    itsMotherTEIxx +=  ( ( one.h - two.h ) * ( one.v * one.v * one.v + one.v * one.v * two.v + one.v * two.v * two.v + two.v * two.v * two.v ) ) / 12;
    itsMotherTEIyy +=  ( ( two.v - one.v ) * ( one.h * one.h * one.h + one.h * one.h * two.h + one.h * two.h * two.h + two.h * two.h * two.h ) ) / 12;
  }

  itsMotherTEIxx = Abs( itsMotherTEIxx - (itsMotherTEConnectorArea * itsMotherTECentroid.v * itsMotherTECentroid.v) );
  itsMotherTEIyy = Abs( itsMotherTEIyy - (itsMotherTEConnectorArea * itsMotherTECentroid.h * itsMotherTECentroid.h) );
  itsMotherTEConnectorArea = Abs( itsMotherTEConnectorArea );
}


