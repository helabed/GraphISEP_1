/****
 * CConcMoment.h
 *
 *  Load object class for a typical CTrussPane class.
 *
 ****/


#define _H_CConcMoment      /* Include this file only once */

#include <WindowMgr.h>
#include <Quickdraw.h>
#include <MemoryMgr.h>
#include <MacTypes.h>
#include "CConcLoadObject.h"


struct CConcMoment : CConcLoadObject {


        /* Instance variables */
  Rect    pictureRectangle;
  WindowPtr  pictureWindow;
  PicHandle  pHandle;
  float    itsMagnitude;


        /* Methods */
  void    Draw( void );
  void    UpDateItsRegion( void );
  void    UpDateObject( void );
  Boolean    WhichOneOfUsGotSelected( Point aPoint );
  void    MoveYourself( void );
  void    InitializeYourself( void );
  void     DoDraw( void );
  void    PrepareYourselfToBeUpdated( void );
  void    PrepareYourselfToBeUpdatedByNode( void );
  void    SelectYourself( void );
  void    UnSelectYourself( void );
  Boolean    ConnectYourselfToNode(  struct CNodeObject
                      *theSelectedNodeObject );
  Boolean    ConnectYourselfToTE(  struct CTrussElementObject
                        *theSelectedTEObject );
  void    DrawFinal( void );
  void    DoYourDialog( void );
  void    DeleteYourself( void );
  void    DisconnectYourself();

};

