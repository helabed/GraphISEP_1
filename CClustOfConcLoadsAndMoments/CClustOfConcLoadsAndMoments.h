/****
 * CClustOfConcLoadsAndMoments.h
 *
 *  A cluster of objects inside CTrussPane.
 *
 ****/

#define _H_CClustOfConcLoadsAndMoments      /* Include this file only once */


#include <CCluster.h>
#include "CConcLoadObject.h"
#include "CConcMoment.h"

struct CClustOfConcLoadsAndMoments : CCluster {

            /* instance variables */

  CConcLoadObject      *theConcLoadObject;
  CConcMoment        *theConcMoment;
  struct CTrussPane    *itsTrussPane;


            /* methods */

  void    ICluster(void);
  void    AddToList( Point  hitPt,  MyObjects whatKindOfObject   );
  void    DisposeAll( void );

};

