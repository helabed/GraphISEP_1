/****
 * CClusterOfAbstracts.h
 *
 *  A cluster of Abstracts inside CTrussPane.
 *
 ****/

#define _H_CClusterOfAbstracts      /* Include this file only once */

#include <CCluster.h>
#include <CObject.h>

struct CClusterOfAbstracts : CCluster {

            /* instance variables */



            /* methods */

  void    ICluster(void);
  void    AddToList( Point  hitPt,  int whatKindOfObject   );
  void    DisposeAll( void );

};

