/****
 * CQuadrelateral.h
 *
 *   object class for a typical CTrussPane class.
 *
 ****/

#define _H_CQuadrelateralObject      /* Include this file only once */
#include "CSquareObject.h"

struct CQuadrelateralObject : CSquareObject {


        /* Instance variables */
  struct CTrussElementObject      *itsTElement;
  float                TElementConnectionRatio;
  float                TElement2ndConnectionRatio;
  Boolean                loadAlongAllMember;

        /* Methods */

    void   Draw( void );
    void   FromtheHitPointToCorners( void );
    void   MoveYourself( void );
    void   FromCornersToItsCenterPoint( void );
    Boolean ConnectYourselfToTE(  struct CTrussElementObject
                          *theTElementObject );
    void    DoYourDialog( void );
    void    Dispose( void );
    void    PrepareYourselfToBeUpdated( void );
    Boolean    CreateTE2ndConnecRatio();
    void    DisconnectYourself( void );
    void    DeleteYourself( void );
    void    InitializeYourself( void );

};

