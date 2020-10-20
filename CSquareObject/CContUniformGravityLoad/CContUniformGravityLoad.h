/****
 * CContUniformGravityLoad.h
 *
 *   object class for a typical CTrussPane class.
 *
 ****/

#define _H_CContUniformGravityLoad      /* Include this file only once */
#include "CContinuousGravityLoad.h"

struct CContUniformGravityLoad : CContinuousGravityLoad {


        /* Instance variables */

        /* Methods */

    void Draw( void );
    void FromtheHitPointToCorners( void );
    void MoveYourself( void );
    void FromCornersToItsCenterPoint( void );
    void HandleArrows();
    void DoYourDialog( void );

};

