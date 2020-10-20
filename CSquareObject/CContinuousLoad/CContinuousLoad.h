/****
 * CContinuousLoad.h
 *
 *   object class for a typical CTrussPane class.
 *
 ****/

#define _H_CContinuousLoad      /* Include this file only once */
#include "CQuadrelateralObject.h"
#include "TrussConstants.h"

struct CContinuousLoad : CQuadrelateralObject {


        /* Instance variables */

        /* Methods */

    void     Draw( void );
    void     FromtheHitPointToCorners( void );
    void     MoveYourself( void );
    void     FromCornersToItsCenterPoint( void );
    void     HandleArrows();
    Boolean   ConnectYourselfToTE(  struct CTrussElementObject
                       *theSelectedTEObject );

};

