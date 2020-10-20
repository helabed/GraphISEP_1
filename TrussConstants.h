/******************************************************************************
 TrussConstants.h

    Built-in Constants

    Copyright Esoft Internationalª 1990.

 ******************************************************************************/
#define _H_TrussConstants      /* Include this file only once */

                  /* some static variables */
#define A_NICE_LOCATION         70
#define  WITHIN_N_PIXELS          10
#define HALF_ARROW            30
    /* see page 118 of Computer Graphics Software Construction */
#define LAMDA1              0.1
            /* these are for the continuous loads arrows*/
#define SMALL_LENGTH          10
#define ARROW_SPACING          15
#define ARROW_H_width           2
#define ARROW_H_height          10

#define RGN_NEIGHBORHOOD         2
#define RGN_EXPANSION_IN_PIXELS      -0
#define DOUBLE_CLICKS           2
#define SCREEN_DPI            72.0
#define SMALL_FLOAT_VALUE        0.01  /* for float comparisons*/
#define RECTANGLE_HALF_SIDE        30
#define PICT_BASE_ID          6000
#define PI                3.141592654
#define odd(x)               (x % 2 ? 1 : 0)
#define  WINDTruss            500   /* Resource ID for WIND template */
#define MAX_POINT_IN_POLYGON      10

        /* these are used for Dialogs */
enum { CounterDLOG_ID = 605 };
enum { CounterOKId = 1 };
enum { CounterCancelId = 2 };
enum { CounterDispTextId = 3 };
enum { CounterUpdateUserItemId = 5 };
enum { CounterMoneyId = 7 };
enum { CounterMoneyArrowId = 9 };
enum { CounterDaysArrowId = 10 };
enum { CounterDaysId = 11 };


enum { LoadCounterDLOG_ID = 605 };
enum { LoadCounterOKId = 1 };
enum { LoadCounterCancelId = 2 };
enum { LoadCounterDispTextId = 3 };
enum { LoadCounterUpdateUserItemId = 5 };
enum { LoadCounterMoneyId = 7 };
enum { LoadCounterMoneyArrowId = 9 };
enum { LoadCounterDaysArrowId = 10 };
enum { LoadCounterDaysId = 11 };


enum { SystemOfUnitsDLOG_ID = 5001 };
enum { SystemOfUnitsOKId = 1 };
enum { SystemOfUnitsCancelId = 2 };
enum { SystemOfUnitsDispTextId = 3 };
enum { SystemOfUnitsSystemInternaional_ID= 4 };
enum { SystemOfUnitsUSCustomary_ID=5 };
enum { SystemOfUnitsBritish_ID=6 };
enum { SystemOfUnitsUpdateUserItemId = 7 };
enum { SystemOfUnitsUserProc1Id = 11 };
enum { SystemOfUnitsUserProc2Id = 10 };

enum { OptionNotImplementedDLOG_ID = 20000 };
enum { OptionNotImplementedOKId = 1 };


enum { LoadsScallingDLOG_ID = 5002 };
enum { LoadsScallingOKId = 1 };
enum { LoadsScallingCancelId = 2 };
enum { LoadsScallingDispTextId = 5 };
enum { LoadsScallingDispTextPoundsId = 4 };
enum { LoadsScallingEditTextID= 3 };
enum { LoadsScallingUpdateUserItemId = 6 };

enum { StructureScallingDLOG_ID = 5003 };
enum { StructureScallingOKId = 1 };
enum { StructureScallingCancelId = 2 };
enum { StructureScallingDispTextId = 5 };
enum { StructureScallingDispTextPoundsId = 4 };
enum { StructureScallingEditTextID= 3 };
enum { StructureScallingUpdateUserItemId = 6 };

enum { DrawingSizeDLOG_ID = 5004 };
enum { DrawingSizeOKId = 1 };
enum { DrawingSizeCancelId = 2 };
enum { DrawingSizeHorizontal= 3 };
enum { DrawingSizeVertical= 4 };
enum { DrawingSizeUpdateUserItemId = 5 };

enum { LoadStepsDLOG_ID = 5005 };
enum { LoadStepsOKId = 1 };
enum { LoadStepsCancelId = 2 };
enum { LoadStepsNumber= 3 };
enum { LoadStepsUpdateUserItemId = 4 };

enum { GenericNodeDLOG_ID = 6001 };
enum { GenericNodeOKId = 1 };
enum { GenericNodeCancelId = 2 };
enum { GenericNodeFree = 3 };
enum { GenericNodeRotationFixed = 4 };
enum { GenericNodeXTranslationFixed = 5 };
enum { GenericNodeYTranslationFixed = 6 };
enum { GenericNodeXYTranslationFixed = 7 };
enum { GenericNodeXYTranslationAndRotationFixed = 8 };
enum { GenericNodeXTranslationAndRotationFixed = 9 };
enum { GenericNodeYTranslationAndRotationFixed = 10 };
enum { GenericNodeDispTextId = 5 };
enum { GenericNodeDispTextPoundsId = 4 };
enum { GenericNodeEditTextXLocation= 11 };
enum { GenericNodeEditTextYLocation= 12 };
enum { GenericNodeUpdateUserItemId = 19 };
enum { GenericNodeTEConnectionRatio = 21 };
enum { GenericNodeDesignConnection = 22 };


enum { GussetPlateDLOG_ID = 6002 };
enum { GussetPlateOKId = 1 };
enum { GussetPlateCancelId = 2 };
enum { GussetPlateFree = 3 };
enum { GussetPlateRotationFixed = 4 };
enum { GussetPlateXTranslationFixed = 5 };
enum { GussetPlateYTranslationFixed = 6 };
enum { GussetPlateXYTranslationFixed = 7 };
enum { GussetPlateXYTranslationAndRotationFixed = 8 };
enum { GussetPlateXTranslationAndRotationFixed = 9 };
enum { GussetPlateYTranslationAndRotationFixed = 10 };
enum { GussetPlateDispTextId = 5 };
enum { GussetPlateDispTextPoundsId = 4 };
enum { GussetPlateEditTextXLocation= 11 };
enum { GussetPlateEditTextYLocation= 12 };
enum { GussetPlateUpdateUserItemId = 19 };
enum { GussetPlateTEConnectionRatio = 21 };
enum { GussetPlateDesignConnection = 22 };
enum { GussetPlateDesignPlate = 23 };
enum { GussetPlateFoschiNumbers = 24 };

        /* gusset plate Design plate Dialog */
enum { GPDesignDLOG_ID = 6000 };
enum { GPDesignOKId = 1 };
enum { GPDesignCancelId = 2 };
enum { GPDesignLength = 3 };
enum { GPDesignHeight = 4 };
enum { GPDesignALPHA = 5 };
enum { GPDesignGAMMA = 6 };
enum { GPDesignPlateAngle = 7 };
enum { GPDesignNoOfTeethPerInchSq = 8 };
enum { GPDesignLengthApplyToAll = 9 };
enum { GPDesignHeightApplyToAll = 10 };
enum { GPDesignALPHAApplyToAll = 11 };
enum { GPDesignGAMMAApplyToAll = 12 };
enum { GPDesignPlateAngleApplyToAll = 13 };
enum { GPDesignNoOfTeethPerInchSqApplyToAll = 14 };
enum { GPDesignUpdateUserItemId = 18 };
enum { GPDesignAlignWithMember = 23 };

        /* gusset plate Foschi Parm dialog */
        /* row number then column number*/
enum { GPFoschiParamDLOG_ID = 6004 };
enum { GPFoschiParamOKId = 1 };
enum { GPFoschiParamCancelId = 2 };
enum { GPFoschiParamOneOne = 3 };
enum { GPFoschiParamTwoOne = 4 };
enum { GPFoschiParamThreeOne = 5 };
enum { GPFoschiParamFourOne = 6 };
enum { GPFoschiParamOneTwo = 7 };
enum { GPFoschiParamTwoTwo = 8 };
enum { GPFoschiParamThreeTwo = 9 };
enum { GPFoschiParamFourTwo = 10 };
enum { GPFoschiParamOneThree = 11 };
enum { GPFoschiParamTwoThree = 12 };
enum { GPFoschiParamThreeThree = 13 };
enum { GPFoschiParamFourThree = 14 };
enum { GPFoschiParamUpdateUserItemId = 15 };
enum { GPFoschiParamApplyToAll = 16 };

enum { GenericElementDLOG_ID = 6017 };
enum { GenericElementOKId = 1 };
enum { GenericElementCancelId = 2 };
enum { GenericElementLength = 3 };
enum { GenericElementHorzLength = 4 };
enum { GenericElementVertLength = 5 };
enum { GenericElementModulusOfElasticity = 6 };
enum { GenericElementXAxisMOfInertia = 7 };
enum { GenericElementYAxisMOfInertia = 8 };
enum { GenericElementBendingStrength = 9 };
enum { GenericElementTensileStrength = 10 };
enum { GenericElementCompressiveStrength = 11 };
enum { GenericElementModulusOfElasticityApplyToAll = 12 };
enum { GenericElementXAxisMOfInertiaApplyToAll = 13 };
enum { GenericElementYAxisMOfInertiaApplyToAll = 14 };
enum { GenericElementBendingStrengthApplyToAll = 15 };
enum { GenericElementTensileStrengthApplyToAll = 16 };
enum { GenericElementCompressiveStrengthApplyToAll = 17 };
enum { GenericElementUpdateUserItemId = 18 };
enum { GenericElementTEConnectionRatio = 19 };
enum { GenericElementDesignConnection = 20 };
enum { GenericElementCrossSectArea = 30 };
enum { GenericElementCrossSectAreaApplyToAll = 31 };

enum { WoodElementDLOG_ID = 6011 };
enum { WoodElementOKId = 1 };
enum { WoodElementCancelId = 2 };
enum { WoodElementLength = 3 };
enum { WoodElementHorzLength = 4 };
enum { WoodElementVertLength = 5 };
enum { WoodElementModulusOfElasticity = 6 };
enum { WoodElementCrossSHeight = 7 };
enum { WoodElementCrossSWidth = 8 };
enum { WoodElementBendingStrength = 9 };
enum { WoodElementTensileStrength = 10 };
enum { WoodElementCompressiveStrength = 11 };
enum { WoodElementModulusOfElasticityApplyToAll = 12 };
enum { WoodElementCrossSHeightApplyToAll = 13 };
enum { WoodElementCrossSWidthApplyToAll = 14 };
enum { WoodElementBendingStrengthApplyToAll = 15 };
enum { WoodElementTensileStrengthApplyToAll = 16 };
enum { WoodElementCompressiveStrengthApplyToAll = 17 };
enum { WoodElementUpdateUserItemId = 18 };
enum { WoodElementAngle = 19 };

enum { ConcLoadDLOG_ID = 6021 };
enum { ConcLoadOKId = 1 };
enum { ConcLoadCancelId = 2 };
enum { ConcLoadMagnitude = 3 };
enum { ConcLoadHorzComp = 4 };
enum { ConcLoadVertComp = 5 };
enum { ConcLoadTEConnectionRatio = 6 };
enum { ConcLoadUpdateUserItemId = 7 };

enum { ConcMomentDLOG_ID = 6031 };
enum { ConcMomentOKId = 1 };
enum { ConcMomentCancelId = 2 };
enum { ConcMomentMagnitude = 3 };
enum { ConcMomentTEConnectionRatio = 4 };
enum { ConcMomentUpdateUserItemId = 5 };


enum { ContGravLoadDLOG_ID = 6023 };
enum { ContGravLoadOKId = 1 };
enum { ContGravLoadCancelId = 2 };
enum { ContGravLoad1stMagnitude = 3 };
enum { ContGravLoad2ndMagnitude = 4 };
enum { ContGravLoadLength = 5 };
enum { ContGravLoadTEConnectionRatio = 6 };
enum { ContGravLoadUpdateUserItemId = 7 };
enum { ContGravLoadAlongStrutE = 8 };

enum { ContUnifGravLoadDLOG_ID = 6024 };
enum { ContUnifGravLoadOKId = 1 };
enum { ContUnifGravLoadCancelId = 2 };
enum { ContUnifGravLoad1stMagnitude = 3 };
enum { ContUnifGravLoadLength = 4 };
enum { ContUnifGravLoadTEConnectionRatio = 5 };
enum { ContUnifGravLoadUpdateUserItemId = 6 };
enum { ContUnifGravLoadAlongStrutE = 7 };

enum { ContWindLoadDLOG_ID = 6026 };
enum { ContWindLoadOKId = 1 };
enum { ContWindLoadCancelId = 2 };
enum { ContWindLoad1stMagnitude = 3 };
enum { ContWindLoad2ndMagnitude = 4 };
enum { ContWindLoadLength = 5 };
enum { ContWindLoadTEConnectionRatio = 6 };
enum { ContWindLoadUpdateUserItemId = 7 };
enum { ContWindLoadAlongStrutE = 8 };


enum { ContUnifWindLoadDLOG_ID = 6025 };
enum { ContUnifWindLoadOKId = 1 };
enum { ContUnifWindLoadCancelId = 2 };
enum { ContUnifWindLoad1stMagnitude = 3 };
enum { ContUnifWindLoadLength = 4 };
enum { ContUnifWindLoadTEConnectionRatio = 5 };
enum { ContUnifWindLoadUpdateUserItemId = 6 };
enum { ContUnifWindLoadAlongStrutE = 7 };
                  /* different kind of Boundary */
                  /* conditions for nodes */

enum BoundaryCondition
{
  Free = 3,
  RotationFixed = 4,
  xTranslationFixed = 5,
  yTranslationFixed = 6,
  xyTranslationFixed = 7,
  xyTranslationAndRotationFixed = 8,
  xTranslationAndRotationFixed = 9,
  yTranslationAndRotationFixed = 10
};
typedef enum BoundaryCondition  BoundaryCondition;

                  /* different kind of objects */
enum MyObjects
{
  aNullObject=0,
  aConcLoadOrMoment,
  aContLoadOrMoment,
  aTrussElementObject,
  aNodeObject,

  aGenericNode,
  aGussetPlate,
  aTBGussetPlate,

  aWoodElement,
  aSteelElement,
  aConcreteElement,
  aPlasticElement,
  aCarbonFiberElement,
  aTopBottomWoodElement,
  aRightLeftWoodElement,
  aGenericElement,

  aConcentratedLoad,
  aContinuousLoad,
  aContinuousGravityLoad,
  aContUniformGravityLoad,
  aContUniformWindLoad,
  aContWindLoad,
  aConcentratedMoment,
  aContinuousMoment
};
typedef enum MyObjects  MyObjects;


struct HitPtAndObjectPtr
{
  struct CAbstractObject    *thisObjectPointer;
  Point            thisHitPoint;
  Boolean            ReSizingInProgress;
};
typedef struct HitPtAndObjectPtr HitPtAndObjectPtr;

struct FloatPoint
{
  float  h;
  float  v;
};
typedef struct FloatPoint FloatPoint;

struct NodeAndGlobNumber
{
  long          theGlobalNumber;
  struct CNodeObject    *theNode;
};
typedef struct NodeAndGlobNumber NodeAndGlobNumber;


enum  SystemOfUnits
{
  SystemInternaional=4,
  USCustomary=5,
  British=6
};
typedef  enum SystemOfUnits  SystemOfUnits;

