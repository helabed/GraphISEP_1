/****
 * CGussetPlate.h
 *
 *   object class for a typical CTrussPane class.
 *
 ****/

#define _H_CGussetPlate      /* Include this file only once */
#include "CNodeObject.h"



struct CGussetPlate : CNodeObject {


        /* Instance variables */

    float        plateLength;
    float        plateHeight;
    float        alpha;
    float        gamma;
    float        itsAngle;
    int          noOfTeethPerInch;
struct  CGussetPDoc      *itsDocument;
    FloatPoint      bottomLeftCorner;
    FloatPoint      bottomRightCorner;
    FloatPoint      topRightCorner;
    FloatPoint      topLeftCorner;
    FloatPoint      masterPlateLocation;
    float        bottomLeftHOffset;
    float        bottomLeftVOffset;
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
    Boolean        itsMotherTEBCIsSet;
    Boolean        itsMotherTE_InheritsPlateLoads;
    float        foschiNumbers[ 5 ][ 4 ];





        /* Methods */

    void     InitializeYourself( void );
    void     DoDrawing( void );
    void     DrawNodeOnly( void );
    void     DoYourDialog( void );
    void     DoPlateDesignDialog( void );
    void     AddPicture( void );
    void     DoPlateDesignGraphically( void );
    void    DoFoshiNumDialog( void );
    void     Dispose();

    void    GetSineAndCosine( float  *theta, float *itsCosine,
              float *itsSine);
    void    TransformTElementToPanoNew( FloatPoint aRealPoint[],
                 Point theStartPoint, int numberOfPoints,
                 Point TransformedPoints[]);
    Point    TransformTElementToPano( FloatPoint aRealPoint,
             Point theStartPoint);
    FloatPoint   TransformPanoToTElement( Point aPoint,
             Point  firstEndLocation);
    void    BlowUpDraw( struct CGussetPlate *thePlate);
    void    UpDateObject( void );
    Boolean    BUP_WhichOneOfUsGotSelected( Point aPoint,
              struct CGussetPlate  *thePlate );
    void    BUPErase( void );
    Boolean    WhichOneOfUsGotSelected( Point aPoint );
    void    ResizeYourself( void );
    void    PositionMasterPlateNode( void );
    void    PlaceYourself( void );
    void    DrawMasterPlateLocator( void );
    void    BUP_SelectYourself( void );
    void    BUP_UnSelectYourself( void );
    void    Init_itsMotherTEPolygon( void );
    void    Define_itsMotherTEPolygon( Point theHitPoint );
    void    Draw_itsMotherTEPolygon( void );
    Boolean    ConnectYourselfToTE(  CTrussElementObject
                          *theSelectedTEObject );
    void    Calc_itsMotherTEConnectorAreaProp( void );
    void    PrintDebugInfo( void );
    void    PrintFileStatics( void );
    void    PrintFileFireWood( void );
    void    KillYourself_IF_NOT_Connected( void );
    void    SaveYourself( void );
    void    LoadYourself( void );
    void    PerformGlobalNumbering( long  *theGlobalNumberPtr );
    void    InitializeGlobalNumbers( void );
    void    PrintFileWood1( void );
    void    PrintFileWood2( void );
    void    PrintFileWood3( void );
    void    PrintFileWood4( void );
    void    PrintFileWood5( void );
    FloatPoint  TransformPanoToGloabal( Point aPoint,
               Point  firstEndLocation);
    Point    TransformGlobalToPano( FloatPoint aRealPoint,
                 Point theStartPoint);

};

struct JointForcesAndPlate
{
  float            xComponentOfConcLoad;
  float            yComponentOfConcLoad;
  float            concMoment;
  struct CGussetPlate      *thePlate;
};
typedef struct JointForcesAndPlate JointForcesAndPlate;



