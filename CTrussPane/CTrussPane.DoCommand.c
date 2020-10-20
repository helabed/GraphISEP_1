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
#include "CTrussPane.phs"
#include "CClusterOfAbstracts.h"
#include "CTrussDoc.h"


extern CBartender    *gBartender;
extern EventRecord    gLastMouseDown;
extern  CBureaucrat      *gGopher;    /* The current boss in the chain of command */

FILE    *Debug_Info_Out_File;
FILE    *Wood_Out_File;
long    NumberOfPlateSprings;
long    NumberOfMembersLoaded;      /* this means number of member loaded */
long    NumberOfJointsLoaded;
float    LargestYValue;

void CTrussPane::DoCommand(long theCommand)

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

    case cmdLoads:              /* loads scalling */
      DoLoadsScallingDialog();
      break;

    case cmdStructure:
      DoStructureScallingDialog();    /* structure scalling */
      break;

    case cmdLoadSteps:
      DoLoadStepsDialog();        /* number of load steps input */
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
      PerformGlobalRenumbering();
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

    case cmdPrintWoodFile:
      PrintWoodFile();
      break;

    case cmdPrintDebugInfo:
      PrintDebugInfo();
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
  static void Perform_KillYourself( CAbstractObject  *theObject )
  {
    theObject->KillYourself_IF_NOT_Connected();
  }

  static void Copy_Cluster( CAbstractObject
      *theObject, CClusterOfAbstracts
          **theTEMP_Cluster_ptr)
  {
         (*theTEMP_Cluster_ptr)->Add( theObject );
  }

  static void Perform_Node_Numbering( CNodeObject
      *theObject, long  *theGlobalNumberPtr)
  {
      theObject->PerformGlobalNumbering( theGlobalNumberPtr );
  }

  static void Perform_Plate_Numbering( CNodeObject
      *theObject, long  *theGlobalNumberPtr)
  {
    (*theGlobalNumberPtr)++;
      theObject->theObjectNumber = (*theGlobalNumberPtr);
  }

        /* Boundary Condition (BC) */
  static void Perform_BC_Numbering( CNodeObject
      *theObject, long  *theGlobalNumberPtr)
  {
    if ( theObject->itsBoundaryCondition != Free )
    {
      (*theGlobalNumberPtr)++;
      }
  }

  static void Perform_TE_Numbering( CTrussElementObject
      *theObject, long  *theGlobalNumberPtr)
  {
    long  numberOfSections = 0L;

    (*theGlobalNumberPtr)++;
      theObject->theObjectNumber = (*theGlobalNumberPtr);

    if( theObject->NodesAreConnected )
    {
      numberOfSections = (theObject->theTENodes->numItems);
      (*theGlobalNumberPtr) += numberOfSections;
    }
  }

  static void Perform_InitializeGlobalNumbers( CAbstractObject *theObject )
  {
    theObject->InitializeGlobalNumbers();
  }

void CTrussPane::PerformGlobalRenumbering( void )
{
  CClusterOfAbstracts   *theTEMP_Cluster;

  theGlobalNumber = 0L;
  thePlateNumber = 0L;
  theTENumber = 0L;
  theNumberOfBoundaryCond = 0L;
  NumberOfPlateSprings = 0L;
  NumberOfMembersLoaded = 0L;
  NumberOfJointsLoaded = 0L;
  LargestYValue = 0.0;


    /* 1.Create a temp cluster theTEMP_Cluster */
    /* 2.Copy each object inside TElementsCluster into*/
    /*     theTEMP_Cluster */
    /* 3.Using this temp cluster issue to each object in it a */
    /*    KillYourself_IF_NOT_Connected() message, thus making sure that */
    /*    all object will get it, and as a result each one of */
    /*   these object will Remove itself from TElementsCluster*/

  theTEMP_Cluster = new( CClusterOfAbstracts );
  theTEMP_Cluster->ICluster();
  TElementsCluster->DoForEach1( Copy_Cluster, (long)(&theTEMP_Cluster) );
  theTEMP_Cluster->DoForEach( Perform_KillYourself );

  theTEMP_Cluster->ICluster();
  ContLoadsAndMoments->DoForEach1( Copy_Cluster, (long)(&theTEMP_Cluster) );
  theTEMP_Cluster->DoForEach( Perform_KillYourself );

  theTEMP_Cluster->ICluster();
  ConcLoadsAndMoments->DoForEach1( Copy_Cluster, (long)(&theTEMP_Cluster) );
  theTEMP_Cluster->DoForEach( Perform_KillYourself );

  theTEMP_Cluster->ICluster();
  NodesCluster->DoForEach1( Copy_Cluster, (long)(&theTEMP_Cluster) );
  theTEMP_Cluster->DoForEach( Perform_KillYourself );

  theTEMP_Cluster->Dispose();

  Refresh();

      /* you may want to initialize all global numbers here before*/
      /* going and numbering...have an Initialize Global number method*/
      /* inside wood and gusset plate and TElement and Generic node*/
  NodesCluster->DoForEach( Perform_InitializeGlobalNumbers );
  TElementsCluster->DoForEach( Perform_InitializeGlobalNumbers );


  NodesCluster->DoForEach1( Perform_Node_Numbering, (long)(&theGlobalNumber) );
  NodesCluster->DoForEach1( Perform_Plate_Numbering, (long)(&thePlateNumber) );
  NodesCluster->DoForEach1( Perform_BC_Numbering, (long)(&theNumberOfBoundaryCond) );
  TElementsCluster->DoForEach1( Perform_TE_Numbering, (long)(&theTENumber) );
}


void CTrussPane::WoodFireAnalysis( void )
{

}

  static void Perform_printDebugInfo( CAbstractObject  *theObject )
  {
    theObject->PrintDebugInfo();
  }
  static void Perform_printFileWood( CAbstractObject  *theObject )
  {
    theObject->PrintFileFireWood();
  }
  static void Perform_PrintFileWood1( CAbstractObject  *theObject )
  {
    theObject->PrintFileWood1();
  }
  static void Perform_PrintFileWood2( CAbstractObject  *theObject )
  {
    theObject->PrintFileWood2();
  }
  static void Perform_PrintFileWood3( CAbstractObject  *theObject )
  {
    theObject->PrintFileWood3();
  }
  static void Perform_PrintFileWood4( CAbstractObject  *theObject )
  {
    theObject->PrintFileWood4();
  }
  static void Perform_PrintFileWood5( CNodeObject  *theObject )
  {
    theObject->PrintFileWood5();
  }


void CTrussPane::PrintDebugInfo( void )
{
  Str255      theWindowTitleTemp;
  char      *theWindowTitle;

  PerformGlobalRenumbering();
  Debug_Info_Out_File = fopen( "A_Debug.out", "w");
/*** this stuff didn't work
  ((CTrussDoc *)gGopher)->GetName( theWindowTitleTemp );
  theWindowTitle = PtoCstr( (char *)theWindowTitleTemp );
***/
  fprintf( Debug_Info_Out_File, "The Structure to be analyzed\n" );
  if( theObject )
    theObject->PrintDebugInfo();
  else
  {
    fprintf( Debug_Info_Out_File, "theGlobalNumber = %ld\n",
                      theGlobalNumber  );
    fprintf( Debug_Info_Out_File, "theTENumber = %ld\n",
                      theTENumber  );
    fprintf( Debug_Info_Out_File, "thePlateNumber = %ld\n",
                      thePlateNumber  );
    fprintf( Debug_Info_Out_File, "theNumberOfBoundaryCond = %ld\n",
                      theNumberOfBoundaryCond  );
    NodesCluster->DoForEach( Perform_printDebugInfo );
    TElementsCluster->DoForEach( Perform_printDebugInfo );
    ContLoadsAndMoments->DoForEach( Perform_printDebugInfo );
    ConcLoadsAndMoments->DoForEach( Perform_printDebugInfo );
  }
  fclose( Debug_Info_Out_File );

}

  static void Calc_NumberOfJointsLoaded( CNodeObject *theObject, long  *NumberOfJointsLoadedPtr)
  {
    if ( theObject->ConcLandMAreConnected && theObject->theNodeLoads->numItems )
    {
      (*NumberOfJointsLoadedPtr)++;
      }
  }

  static void Locate_Largest_Y_Value( CNodeObject  *theObject )
  {
    if ( LargestYValue <=  (theObject->itsCenterPoint.v  *
          theObject->itsTrussPane->theStructureScale / SCREEN_DPI ))
    {
      LargestYValue = (theObject->itsCenterPoint.v  *
            theObject->itsTrussPane->theStructureScale / SCREEN_DPI );
    }
  }

void CTrussPane::PrintWoodFile( void )
{
  PerformGlobalRenumbering();
  Wood_Out_File = fopen( "Wood.in", "w");

  NodesCluster->DoForEach( Locate_Largest_Y_Value );
  LargestYValue += 100.00;        /* add  100 inches to largest value for safety*/

  NodesCluster->DoForEach( Perform_PrintFileWood5 );

  fprintf( Wood_Out_File, "The Structure to be analyzed\n" );
  fprintf( Wood_Out_File, "%ld\t", theGlobalNumber  );
  fprintf( Wood_Out_File, "%ld\t", theTENumber  );
  fprintf( Wood_Out_File, "%ld\t", thePlateNumber  );
  fprintf( Wood_Out_File, "%ld\t", theNumberOfBoundaryCond  );
  fprintf( Wood_Out_File, "%ld\t", NumberOfPlateSprings  );
  fprintf( Wood_Out_File, "%d\n", numberOfLoadSteps  );

    /* set these to zero before extracting spring and connector area prop.*/
  NumberOfPlateSprings = 0L;

    /* print wood memeber location and connectivity */
  TElementsCluster->DoForEach( Perform_printFileWood );

    /* print wood member properties */
  TElementsCluster->DoForEach( Perform_PrintFileWood1 );

    /*  print gusset plate dimensions, and MasterPlateNode location*/
  fprintf( Wood_Out_File, "\n");
  NodesCluster->DoForEach( Perform_printFileWood );

    /* spring and connector area properties and deltas */
  fprintf( Wood_Out_File, "\n");
  NodesCluster->DoForEach( Perform_PrintFileWood1 );

    /* Foshi plate numbers */
  fprintf( Wood_Out_File, "\n");
  NodesCluster->DoForEach( Perform_PrintFileWood2 );

    /* Boundary conditions */
  fprintf( Wood_Out_File, "\n");
  NodesCluster->DoForEach( Perform_PrintFileWood3 );

    /* Calculate the number of members that are  loaded */
  TElementsCluster->DoForEach( Perform_PrintFileWood2 );

    /* calculate the number  of joints loaded */
  NodesCluster->DoForEach1( Calc_NumberOfJointsLoaded, (long)(&NumberOfJointsLoaded) );

  fprintf( Wood_Out_File, "\n");
  fprintf( Wood_Out_File, "\n%ld\t%ld\t", NumberOfJointsLoaded, NumberOfMembersLoaded  );

    /* print the Joints loads */
  NodesCluster->DoForEach( Perform_PrintFileWood4 );

    /* print the member loads */
  TElementsCluster->DoForEach( Perform_PrintFileWood3 );

  fprintf( Wood_Out_File, "\nf f");

  fclose( Wood_Out_File );
}


