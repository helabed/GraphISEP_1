/****
 * CTBGussetPlate.h
 *
 *   object class for a typical CTrussPane class.
 *
 ****/

#define _H_CTBGussetPlate      /* Include this file only once */
#include "CGussetPlate.h"

struct CTBGussetPlate : CGussetPlate {


        /* Instance variables */


        /* Methods */

    void DoDrawing( void );
    void DrawNodeOnly( void );
    void DrawFinal( void );
    void InitializeYourself( void );
    void Draw( void );
    void AddPicture( void );
    void RemovePicture( void );
    void UnSelectYourself( void );
    void SelectYourself( void );

};

