/****
 * CSquareObject.h
 *
 *  Square object class for a typical CTrussPane class.
 *
 ****/

#define _H_CSquareObject      /* Include this file only once */

#include "CAbstractObject.h"
#include "TrussCommands.h"


struct CSquareObject : CAbstractObject {


        /* Instance variables */
  Point    topLeftCorner;
  Point    bottomRightCorner;
  Point    bottomLeftCorner;
  Point    topRightCorner;
  Point    itsCenterPoint;
  Point    offSet;
  Boolean    topLeftCornerFlag;
  Boolean    bottomRightCornerFlag;
  Boolean    bottomLeftCornerFlag;
  Boolean    topRightCornerFlag;
  RgnHandle  itsRegion;


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
  void     DrawFinal( void );
  void    Dispose();


};

