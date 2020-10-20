/****
 * CRegularWoodTElement.h
 *
 *   object class for a typical CTrussPane class.
 *
 ****/

#define _H_CRegularWoodTElement      /* Include this file only once */
#include "CTrussElementObject.h"

struct CRegularWoodTElement : CTrussElementObject {


        /* Instance variables */
    float    CrossSectionWidth;
    float    CrossSectionHeight;
    FloatPoint  its1stEndTip;
    FloatPoint  its1stEndRightCorner;
    FloatPoint  its1stEndLeftCorner;
    FloatPoint  its2ndEndTip;
    FloatPoint  its2ndEndRightCorner;
    FloatPoint  its2ndEndLeftCorner;
    float    its1stEndHOffset;
    float    its1stEndVOffset;
    float    its2ndEndHOffset;
    float    its2ndEndVOffset;

    Point    itsOtherEnd;

    Boolean    its1stEndTipFlag;
    Boolean    its1stEndRightCornerFlag;
    Boolean    its1stEndLeftCornerFlag;
    Boolean    its2ndEndTipFlag;
    Boolean    its2ndEndRightCornerFlag;
    Boolean    its2ndEndLeftCornerFlag;
    Boolean    precisionCuttingInProgress;
    Boolean    placingInProgress;

struct CGussetPlate    *itsGussetPlate;
    FloatPoint    its1stEndPolygon[ MAX_POINT_IN_POLYGON ];
    FloatPoint    its2ndEndPolygon[ MAX_POINT_IN_POLYGON ];
    int        firstEndPolyPointCounter;
    int        secondEndPolyPointCounter;
    float      firstEndConnectorArea;
    float      secondEndConnectorArea;
    float      firstEndIxx;
    float      secondEndIxx;
    float      firstEndIyy;
    float      secondEndIyy;
    FloatPoint    firstEndCentroid;
    FloatPoint    secondEndCentroid;
    Boolean      its1stEndBCondIsSet;
    Boolean      its2ndEndBCondIsSet;
    Boolean      inherit1stEndPlateLoads;
    Boolean      inherit2ndEndPlateLoads;
    float        firstEndcenterPointsHOffset;
    float        firstEndcenterPointsVOffset;
    float        secondEndcenterPointsHOffset;
    float        secondEndcenterPointsVOffset;

        /* Methods */
    void      InitializeYourself( void );
    void    DoDrawing( void );
    void    DoYourDialog( void );
    void    GetSineAndCosine( float  *theta, float *itsCosine,
              float *itsSine);
    short    WhichEndIsConnected( struct CNodeObject *thePlate );
    float    WhatIsYourLength( void );
    void    TransformTElementToPanoNew( FloatPoint aRealPoint[],
                 Point theStartPoint, int numberOfPoints,
                 Point TransformedPoints[]);
    Point    TransformTElementToPano( FloatPoint aRealPoint,
             Point theStartPoint);
    FloatPoint   TransformPanoToTElement( Point aPoint,
             Point  firstEndLocation);
    void    BlowUpDraw( struct CGussetPlate *thePlate);
    void    StretchTheOtherEnd( short whichEnd, float totalLength,
                   struct CGussetPlate *thePlate);
    void    StretchBothEnds( Point *its1stStretchedEnd,
                Point *its2ndStretchedEnd ,
                struct CGussetPlate *thePlate);
    void    UpDateObject( void );
    Boolean    BUP_WhichOneOfUsGotSelected( Point aPoint,
              struct CGussetPlate  *thePlate );
    void    PrecisionCutYourself( void );
    void    PlaceYourself( void );
    void    BUPErase( void );
    Boolean    WhichOneOfUsGotSelected( Point aPoint );
    void    BUP_SelectYourself( void );
    void    BUP_UnSelectYourself( void );
    void    Init_ConnectorPolygon( struct CGussetPlate *thePlate );
    void    Define_ConnectorPolygon( struct CGussetPlate *thePlate,
                Point theHitPoint );
    void    DrawItsPolygon( struct CGussetPlate *thePlate);
    Boolean    ConnectYourselfToNode( struct  CNodeObject
                      *theSelectedNodeObject );
    void    CalcConnectorAreaProp( void );
    void    PrintDebugInfo( void );
    void    PrintFileStatics( void );
    void    PrintFileFireWood( void );
    void    KillYourself_IF_NOT_Connected( void );
    void    SaveYourself( void );
    void    LoadYourself( void );
    void    InitializeGlobalNumbers( void );
  void    PrintFileWood1( void );
  void    PrintFileWood2( void );
  void    PrintFileWood3( void );
  void    PrintFileWood4( void );
  void    DisconnectYourself( void );

};


struct WoodAndConcLandMnum
{
  long            theConcLNumber;
  long            theConcMNumber;
  float            firstEndTEConnectionRatio;
  float            secondEndTEConnectionRatio;
  struct CRegularWoodTElement  *theWoodElement;
};
typedef struct WoodAndConcLandMnum WoodAndConcLandMnum;

struct WoodAndContLoad
{
  float            totalContLoad;
  struct CRegularWoodTElement  *theWoodElement;
};
typedef struct WoodAndContLoad WoodAndContLoad;

struct WoodElementAndPlate
{
  struct CRegularWoodTElement    *theWoodElement;
  struct CGussetPlate        *thePlate;
};
typedef struct WoodElementAndPlate WoodElementAndPlate;

