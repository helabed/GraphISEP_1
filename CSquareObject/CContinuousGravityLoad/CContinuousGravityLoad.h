/****
 * CContinuousGravityLoad.h
 *
 *   object class for a typical CTrussPane class.
 *
 ****/

#define _H_CContinuousGravityLoad      /* Include this file only once */
#include "CQuadrelateralObject.h"

struct CContinuousGravityLoad : CQuadrelateralObject {


        /* Instance variables */

        /* Methods */

    void Draw( void );
    void FromtheHitPointToCorners( void );
    void MoveYourself( void );
    void FromCornersToItsCenterPoint( void );
    void HandleArrows();
    void DoYourDialog( void );

};

