/****
 * CClusterOfTElements.h
 *
 *  A cluster of TElements inside CTrussPane.
 *
 ****/

#define _H_CClusterOfTElements      /* Include this file only once */

#include <CCluster.h>
#include "CTrussElementObject.h"
#include "CGenericTElement.h"
#include "CRegularWoodTElement.h"

struct CClusterOfTElements : CCluster {

            /* instance variables */

  CTrussElementObject      *theTrussElementObject;
  CGenericTElement      *theGenericTElement;
  CRegularWoodTElement    *theRegularWoodTElement;
  struct CTBWoodTElement    *theTBWoodTElement;
  struct CTrussPane      *itsTrussPane;

            /* methods */

  void    ICluster(void);
  void    AddToList( Point  hitPt,  MyObjects whatKindOfObject   );
  void    DisposeAll( void );

};

