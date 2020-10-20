/******************************************************************************
 TrussCommands.h

    Built-in commands and Menu numbers

    Copyright Esoft Internationalª 1989.

 ******************************************************************************/

#define _H_TrussCommands

  /**** M E N U S ****/

#define  MENUstyle    12  /* The style menu is not one of the reserved menus */
#define MENUsetUp    13
#define  MENUobjects    14  /* Objects menu is not one of the original menus*/
#define MENUanalysis  15
#define MENUresults    16
#define MENUmyfont    84  /*hier menu just for fun */
#define MENUmysize    83  /*hier menu just for fun */
#define MENUnodes    85  /*hier menu*/
#define MENUstructrualElements 86  /*hier menu*/
#define MENUloads    87   /*hier menu*/
#define MENUmoments    88   /*hier menu*/
#define MENUalign    89   /*hier menu*/
#define MENUscaling    90  /*hier menu just for fun */
#define MENUshowStructure  91 /*hier menu*/
#define MENUshowElement    92 /*hier menu*/
#define MENUwoodElements  93  /*hier menu*/

            /**** C O M M A N D S ****/

        /** Set Up Menu **/
#define cmdUnits          5001L
#define cmdLoads          5002L
#define cmdStructure        5003L
#define cmdDrawingSize        5004L
#define cmdLoadSteps        5005L

#define cmdHideLoads        5010L
#define cmdHideNodes        5011L
#define cmdHideStructElements    5012L

#define cmdRefreshWindow      5020L

#define cmdZoomIn          5030L
#define cmdZoomOut          5031L
#define cmdDefineConnecArea      5040L
#define cmdSetBoundaryCondition    5050L
#define cmdInheritPlateLoads    5060L

        /** Objects Menu **/

#define cmdNewNodes          6000L
#define cmdNewGenericNode          6001L
#define cmdNewGussetPlate          6002L
#define cmdNewTEGussetPlate          6003L

#define cmdNewStructuralElements  6010L
#define cmdNewWoodElement          6011L
#define cmdNewSteelElement          6012L
#define cmdNewConcreteElement        6013L
#define cmdNewPlasticElement        6014L
#define cmdNewCarbonFiberElement      6015L
#define cmdNewTopBottomWoodElement      6016L
#define cmdNewGenericElement        6017L

#define cmdNewLoads          6020L
#define cmdNewConcentratedLoad        6021L
#define cmdNewContinuousLoad        6022L
#define cmdNewContinuousGravityLoad      6023L
#define cmdNewContUniformGravityLoad    6024L
#define cmdNewContUniformWindLoad      6025L
#define cmdNewContWindLoad          6026L

#define cmdNewMoments        6030L
#define cmdNewConcentratedMoment      6031L
#define cmdNewContinuousMoment        6032L

#define cmdShowProperties      6040L
#define cmdDisconnectObject      6050L
#define cmdAlign          6060L
#define cmdAlignHorizontally        6061L
#define cmdAlignVertically          6062L

#define cmdFixSize          6070L
#define cmdFixDirection        6080L

        /** Analysis Menu **/

#define cmdGlobalNumbering      7000L
#define cmdStaticAnalysis      7001L
#define cmdDynamicAnalysis      7002L
#define cmdFireAnalysis        7003L
#define cmdPrintWoodFile      7004L
#define cmdPrintDebugInfo      7005L

        /** Results Menu **/

#define cmdStructureDisplacement      8000L
#define cmdStructureAxialForceDiagram    8001L
#define cmdStructureShearForceDiagram    8002L
#define cmdStructureBendingMomentDiagram  8003L

#define cmdElementDisplacement        8010L
#define cmdElementAxialForceDiagram      8011L
#define cmdElementShearForceDiagram      8012L
#define cmdElementBendingMomentDiagram    8013L


#include "TrussConstants.h"
