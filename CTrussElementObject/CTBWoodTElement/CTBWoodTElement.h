/****
 * CTBWoodTElement.h
 *
 *   object class for a typical CTrussPane class.
 *
 ****/

#define _H_CTBWoodTElement      /* Include this file only once */
#include <MacTypes.h>
#include <Quickdraw.h>
#include "CRegularWoodTElement.h"
#include "CClustOfConcLoadsAndMoments.h"
#include "CClusterOfNodes.h"


struct CTBWoodTElement : CRegularWoodTElement {


        /* Instance variables */

        /* Methods */

    void  DoDrawing( void );
    void  InitializeYourself( void );
    void  FromtheHitPointToCorners( void );
    void  FromCornersToItsCenterPoint( void );
    void   DoYourDialog( void );

};

