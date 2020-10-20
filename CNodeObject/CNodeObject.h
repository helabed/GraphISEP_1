/****
 * CNodeObject.h
 *
 *  Node object class for a typical CTrussPane class.
 *
 ****/

#define _H_CNodeObject      /* Include this file only once */

#include "CAbstractObject.h"
#include "CClustOfConcLoadsAndMoments.h"
#include "CClusterOfTElements.h"
#include "CConcLoadObject.h"
#include "CTrussElementObject.h"
#include "TrussCommands.h"
#include "TrussConstants.h"

struct CNodeObject : CAbstractObject {


            /* Instance variables */
  Point                itsCenterPoint;
  Point                offSet;
  Boolean                itsCenterPointFlag;
  CClustOfConcLoadsAndMoments      *theNodeLoads;
  CClusterOfTElements          *theNodeTElements;
  Boolean                ConcLandMAreConnected;
  Boolean                TElementsAreConnected;
  CAbstractObject            *thisObjectPointer;
  CTrussElementObject          *itsMotherTElement;
  Boolean                dumyBoolean;
  float                TElementConnectionRatio;
  BoundaryCondition          itsBoundaryCondition;

  Rect                pictureRectangle;
  PicHandle              pHandle;
  long                itsGlobalNumber;


        /* Methods */
  void    DoDrawing( void );
  void    Draw( void );
  void     DrawNodeOnly( void );
  void     SelectYourself( void );
  void     UnSelectYourself( void );
  void    UpDateObject( void );
  void    ResizeYourself( void );
  Boolean    WhichOneOfUsGotSelected( Point aPoint );
  void    DrawResizingHandles( Point aPoint );
  void    MoveYourself( void );
  void    InitializeYourself( void );
  void    AddToItsConcLandMCluster( CConcLoadObject *
                          theConcLoadOrMoment );
  void    AddToItsTElementsCluster( CTrussElementObject
                          *theTElementObject );
  void    DrawFinal( void );
  void     DoYourDialog( void );
  void    PrepareYourselfToBeUpdated( void );
  void    Dispose();
  Boolean    ConnectYourselfToTE(  CTrussElementObject
                          *theTElementObject );
  void    DisconnectYourself( void );
  void    DeleteYourself( void );
  void    DoDrawingFinal( void );
  void    AddPicture( void );
  void    RemovePicture( void );
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
};

