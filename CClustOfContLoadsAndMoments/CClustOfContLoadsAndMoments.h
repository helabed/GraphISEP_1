/****
 * CClustOfContLoadsAndMoments.h
 *
 *  A cluster of Squares inside CTrussPane.
 *
 ****/

#define _H_CClustOfContLoadsAndMoments      /* Include this file only once */

#include <CCluster.h>
#include "CQuadrelateralObject.h"
#include "CContinuousLoad.h"
#include "CContinuousGravityLoad.h"
#include "CContUniformGravityLoad.h"
#include "CContUniformWindLoad.h"
#include "CContWindLoad.h"
#include "CContinuousMoment.h"

struct CClustOfContLoadsAndMoments : CCluster {

            /* instance variables */

  CContinuousLoad        *theContinuousLoad;
  CContinuousGravityLoad    *theContinuousGravityLoad;
  CContUniformGravityLoad    *theContUniformGravityLoad;
  CContUniformWindLoad    *theContUniformWindLoad;
  CContWindLoad        *theContWindLoad;
  CContinuousMoment      *theContinuousMoment;
  struct CTrussPane      *itsTrussPane;

            /* methods */

  void    ICluster(void);
  void    AddToList( Point  hitPt,  MyObjects whatKindOfObject   );
  void    DisposeAll( void );

};

