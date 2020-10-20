/****
 * CAbstractObject.h
 *
 *  Abstract object class for a typical CTrussPane class.
 *
 ****/
#define _H_CAbstractObject      /* Include this file only once */


#include <CObject.h>
#include "TrussCommands.h"


struct CAbstractObject : CObject {


        /* Instance variables */
  Point        theHitPoint;
  Boolean        IamSelected;
  Boolean        ReSizingInProgress;
  Boolean        IamConnected;
  Boolean        IamBeingUpdated;
  MyObjects      theKindOfObjectIam;
  struct CTrussPane  *itsTrussPane;
  long        theObjectNumber;


        /* Methods */
  void    Draw( void );
  void    ReDraw( void );
  void    Erase( void );
  void    DragYourself( void );
  void    DrawFinal( void );
  void     SelectYourself( void );
  void     UnSelectYourself( void );
  void    UpDateObject( void );
  void    ResizeYourself( void );
  Boolean    WhichOneOfUsGotSelected( Point aPoint );
  void    DrawResizingHandles( Point aPoint );
  void    EraseResizingHandles( Point aPoint );
  void    MoveYourself( void );
  void    InitializeYourself( void );
  void    DoYourDialog( void );
  MyObjects  WhoAreYou( void );
  void    DisconnectYourself( void );
  void    DeleteYourself( void );
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
};

