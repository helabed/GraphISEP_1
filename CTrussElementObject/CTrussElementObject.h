/****
 * CTrussElementObject.h
 *
 *   object class for a typical CTrussPane class.
 *
 ****/

#define _H_CTrussElementObject      /* Include this file only once */

#include <Global.h>
#include "CAbstractObject.h"
#include "TrussCommands.h"

struct CTrussElementObject : CAbstractObject {


        /* Instance variables */
  Point                  itsCenterPoint;
  Point                  its1stEnd;
  Point                  its2ndEnd;
  Point                  offSet;
  Boolean                  itsCenterPointFlag;
  Boolean                  its1stEndFlag;
  Boolean                  its2ndEndFlag;
  struct CNodeObject            *the1stEndNode;
  struct CNodeObject             *the2ndEndNode;
  Boolean                  the1stEndConnected;
  Boolean                  the2ndEndConnected;
  RgnHandle                itsRegion;
  float                  CounterMoneyValue;
  float                  CounterDaysValue;
  struct CClustOfContLoadsAndMoments    *theTEContLoadsAndMoments;
  struct CClustOfConcLoadsAndMoments    *theTEConcLoadsAndMoments;
  struct CClusterOfNodes          *theTENodes;
  Boolean                  ConcLandMAreConnected;
  Boolean                  ContLandMAreConnected;
  Boolean                  NodesAreConnected;
  CAbstractObject              *thisObjectPointer;
  float                  lastClickLocatedAtRatio;
  float                  E;
  float                  Ixx;
  float                  Iyy;
  float                  BendingStrength;
  float                  TensileStrength;
  float                  CompressiveStrength;
  float                  CrossSectionalArea;
  float                  Area;
  Boolean                  MovingInProgress;
  long                  its1stEndGlobalNumber;
  long                  its2ndEndGlobalNumber;




        /* Methods */
  void    DoDrawing( void );
  void    Draw( void );
  void    UpDateItsRegion( void );
  void     SelectYourself( void );
  void     UnSelectYourself( void );
  void    UpDateObject( void );
  void    ResizeYourself( void );
  Boolean    WhichOneOfUsGotSelected( Point aPoint );
  void    DrawResizingHandles( Point aPoint );
  void    MoveYourself( void );
  void    InitializeYourself( void );
  void    FromtheHitPointToCorners( void );
  void    FromCornersToItsCenterPoint( void );
  void     DrawFinal( void );
  void     DoDialogItemsCounter(void);
  void    DoYourDialog( void );
  void    Dispose();
  void    AddToItsConcLandMCluster( struct CConcLoadObject
                        *theConcLoadOrMoment );
  void    AddToItsContLandMCluster( struct CQuadrelateralObject
                        *theContLoadOrMoment );
  void    AddToItsNodesCluster( struct CNodeObject *theNodeObject );
  Boolean    ConnectYourselfToNode(  struct CNodeObject *theNodeObject );
  void    DisconnectYourself( void );
  void    DeleteYourself( void );
  void    DoDrawingFinal( void );
  void    PrintDebugInfo( void );
  void    PrintFileStatics( void );
  void    PrintFileFireWood( void );
  void    PrintFileWood1( void );
  void    PrintFileWood2( void );
  void    PrintFileWood3( void );
  void    PrintFileWood4( void );
  void    KillYourself_IF_NOT_Connected( void );
  void    SaveYourself( void );
  void    LoadYourself( void );
  short    WhichEndIsConnected( struct CNodeObject *theNode );
  void    InitializeGlobalNumbers( void );
};



