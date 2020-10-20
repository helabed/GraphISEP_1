/****
 * CClusterOfNodes.h
 *
 *  A cluster of Nodes inside CTrussPane.
 *
 ****/

#define _H_CClusterOfNodes      /* Include this file only once */

#include <CCluster.h>
#include "CGenericNode.h"
#include "CGussetPlate.h"
#include "CTBGussetPlate.h"

struct CClusterOfNodes : CCluster {

            /* instance variables */

  CGenericNode      *theGenericNode;
  CGussetPlate      *theCGussetPlate;
  CTBGussetPlate      *theTBGussetPlate;
  struct CTrussPane    *itsTrussPane;

            /* methods */

  void    ICluster(void);
  void    AddToList( Point  hitPt, MyObjects whatKindOfObject  );
  void    DisposeAll( void );

};

