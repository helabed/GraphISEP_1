/****
 * CConcLoadObject.h
 *
 *  Load object class for a typical CTrussPane class.
 *
 ****/

#define _H_CConcLoadObject      /* Include this file only once */


#include <Global.h>
#include "CAbstractObject.h"
#include "TrussCommands.h"


struct CConcLoadObject : CAbstractObject {


        /* Instance variables */
  Point          itsCenterPoint;
  Point          its1stEnd;
  Point          its2ndEnd;
  Point          offSet;
  Boolean          itsCenterPointFlag;
  Boolean          its1stEndFlag;
  Boolean          its2ndEndFlag;
  Boolean          the2ndEndConnected;
  struct CNodeObject     *the1stEndNode;
  struct CNodeObject     *the2ndEndNode;
  Boolean          the1stEndConnected;
struct CTrussElementObject  *itsTElement;
  RgnHandle        itsRegion;
  float          LoadCounterMoneyValue;
  float          LoadCounterDaysValue;
  float          TElementConnectionRatio;


        /* Methods */
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
  void    HandleTheArrow( void );
  void     DoDraw( void );
  void     DrawFinal( void );
  void    DoDialogItemsCounter(void);
  void    DoYourDialog( void );
  void    Dispose( void );
  void    PrepareYourselfToBeUpdated( void );
  void    PrepareYourselfToBeUpdatedByNode( void );
  Boolean   ConnectYourselfToTE( struct CTrussElementObject
                          *theTElementObject );
  Boolean    ConnectYourselfToNode(  struct CNodeObject
                      *theNodeObject );
  void    DisconnectYourself( void );
  void    DeleteYourself( void );


};

