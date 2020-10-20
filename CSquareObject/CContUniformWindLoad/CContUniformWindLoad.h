/****
 * CContUniformWindLoad.h
 *
 *   object class for a typical CTrussPane class.
 *
 ****/

#define _H_CContUniformWindLoad      /* Include this file only once */
#include "CContWindLoad.h"

struct CContUniformWindLoad : CContWindLoad {


        /* Instance variables */

        /* Methods */

    void FromtheHitPointToCorners( void );
    void HandleArrows();

    void    DoYourDialog( void );
};

