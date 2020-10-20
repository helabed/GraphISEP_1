/****
 * CContWindLoad.h
 *
 *   object class for a typical CTrussPane class.
 *
 ****/

#define _H_CContWindLoad      /* Include this file only once */
#include "CContinuousGravityLoad.h"

struct CContWindLoad : CContinuousGravityLoad {


        /* Instance variables */

        /* Methods */

    void FromtheHitPointToCorners( void );
    void HandleArrows();

    void    DoYourDialog( void );
    void    PrepareYourselfToBeUpdated( void );
    Boolean    CreateTE2ndConnecRatio();
    void    DisconnectYourself( void );
    Boolean ConnectYourselfToTE(  struct CTrussElementObject
                          *theTElementObject );

};

