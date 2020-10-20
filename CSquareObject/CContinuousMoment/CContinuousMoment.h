/****
 * CContinuousMoment.h
 *
 *   object class for a typical CTrussPane class.
 *
 ****/

#define _H_CContinuousMoment      /* Include this file only once */
#include "CQuadrelateralObject.h"

struct CContinuousMoment : CQuadrelateralObject {


        /* Instance variables */

        /* Methods */

    void Draw( void );
    void FromtheHitPointToCorners( void );
    void MoveYourself( void );
    void FromCornersToItsCenterPoint( void );

};

