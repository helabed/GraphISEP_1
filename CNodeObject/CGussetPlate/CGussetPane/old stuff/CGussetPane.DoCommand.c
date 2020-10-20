/***
 * DoCommand
 *
 *
 *  In this method, you handle all the commands your pane
 *  deals with.
 *
 *
 *  the avaialble commands are cmdGiveMeASquare, cmdGiveMeATruss,
 *  cmdGiveMeANode.
 *
 *
 *
 ***/
#include "CGussetPane.ph"


extern CBartender    *gBartender;
extern EventRecord    gLastMouseDown;


void CGussetPane::DoCommand(long theCommand)

{
  Point    myMouseClick, hitPt;



/****************** all this garbage in here is to ensure that ***********
 ******************  objects are created inside the window     ***********/

      myMouseClick = gLastMouseDown.where ;
      WindToFrame( &myMouseClick );
      hitPt = myMouseClick;
      if( EqualPt(hitPt,previousMouseLocation) )
      {
        hitPt.v = myMouseClick.v + 10;
        hitPt.h = myMouseClick.h + 10;
      }
      previousMouseLocation = hitPt;
      gLastMouseDown.where = hitPt;
/****************************** end of garbage ***************************/


  switch (theCommand) {

    /* your pane commands here */

      /* AddToList() adds creates a new instance of the*****Object
        and stores it in a CClusterOfObjects class that is
          referenced by ObjectsCluster. */

    case cmdUnits:
      this->DoSystemOfUnitsDialog();
      break;

    case cmdLoads:          /* loads scalling */
      DoLoadsScallingDialog();
      break;

    case cmdStructure:
      DoStructureScallingDialog();    /* structure scalling */
      break;

    case cmdHideLoads:
      OptionNotImplemented();
      break;

    case cmdHideNodes:
      OptionNotImplemented();
      break;

    case cmdHideStructElements:
      OptionNotImplemented();
      break;

    case cmdRefreshWindow:
      Refresh();
      break;

    case cmdNewGenericNode:
      NodesCluster->AddToList( hitPt, aGenericNode);
      break;

    case cmdNewGussetPlate:
      NodesCluster->AddToList( hitPt, aGussetPlate);
      break;

    case cmdNewTEGussetPlate:
      NodesCluster->AddToList( hitPt, aTBGussetPlate);
      break;

    case cmdNewGenericElement:
      TElementsCluster->AddToList( hitPt, aGenericElement);
      break;

    case cmdNewWoodElement:
      TElementsCluster->AddToList( hitPt, aWoodElement);
      break;

    case cmdNewTopBottomWoodElement:
      TElementsCluster->AddToList( hitPt, aTopBottomWoodElement);
      break;

    case cmdNewSteelElement:
      OptionNotImplemented();
      break;

    case cmdNewConcreteElement:
      OptionNotImplemented();
      break;

    case cmdNewPlasticElement:
      OptionNotImplemented();
      break;

    case cmdNewCarbonFiberElement:
      OptionNotImplemented();
      break;

    case cmdNewConcentratedLoad:
      ConcLoadsAndMoments->AddToList( hitPt, aConcentratedLoad);
      break;

    case cmdNewConcentratedMoment:
      ConcLoadsAndMoments->AddToList( hitPt, aConcentratedMoment);
      break;

    case cmdNewContinuousLoad:
      ContLoadsAndMoments->AddToList( hitPt, aContinuousLoad );
      break;

    case cmdNewContinuousGravityLoad:
      ContLoadsAndMoments->AddToList( hitPt, aContinuousGravityLoad );
      break;

    case cmdNewContUniformGravityLoad:
      ContLoadsAndMoments->AddToList( hitPt, aContUniformGravityLoad );
      break;

    case cmdNewContUniformWindLoad:
      ContLoadsAndMoments->AddToList( hitPt, aContUniformWindLoad );
      break;

    case cmdNewContWindLoad:
      ContLoadsAndMoments->AddToList( hitPt, aContWindLoad );
      break;

      case cmdNewContinuousMoment:
      ContLoadsAndMoments->AddToList( hitPt, aContinuousMoment );
      break;

    case cmdNewMoments:
      OptionNotImplemented();
      break;

    case cmdShowProperties:
      if( theObject)
        theObject->DoYourDialog();
      break;

    case cmdDisconnectObject:
      if( theObject)
        theObject->DisconnectYourself();
      break;

    case cmdAlignHorizontally:
      OptionNotImplemented();
      break;

    case cmdAlignVertically:
      OptionNotImplemented();
      break;

    case cmdFixSize:
      OptionNotImplemented();
      break;

    case cmdFixDirection:
      OptionNotImplemented();
      break;

    case cmdGlobalNumbering:
      OptionNotImplemented();
      break;

    case cmdStaticAnalysis:
      OptionNotImplemented();
      break;

    case cmdDynamicAnalysis:
      OptionNotImplemented();
      break;

    case cmdFireAnalysis:
      OptionNotImplemented();
      break;

    case cmdStructureDisplacement:
      OptionNotImplemented();
      break;

    case cmdStructureAxialForceDiagram:
      OptionNotImplemented();
      break;

    case cmdStructureShearForceDiagram:
      OptionNotImplemented();
      break;

    case cmdStructureBendingMomentDiagram:
      OptionNotImplemented();
      break;

    case cmdElementDisplacement:
      OptionNotImplemented();
      break;

    case cmdElementAxialForceDiagram:
      OptionNotImplemented();
      break;

    case cmdElementShearForceDiagram:
      OptionNotImplemented();
      break;

    case cmdElementBendingMomentDiagram:
      OptionNotImplemented();
      break;

    default:
      inherited::DoCommand(theCommand);
      break;
  }
}

