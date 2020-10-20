/****
 * CGenericTElement.h
 *
 *   object class for a typical CTrussPane class.
 *
 ****/

#define _H_CGenericTElement      /* Include this file only once */
#include "CTrussElementObject.h"

struct CGenericTElement : CTrussElementObject {


        /* Instance variables */

        /* Methods */

    void Draw( void );
    Boolean    ConnectYourselfToNode( struct  CNodeObject
                      *theSelectedNodeObject );
    void    DoYourDialog( void );

};

