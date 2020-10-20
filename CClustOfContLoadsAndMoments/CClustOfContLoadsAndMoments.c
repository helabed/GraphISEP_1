/****
 * CClustOfContLoadsAndMoments.c
 *
 *  cluster of Squares  for a typical CTrussPane class
 *
 ****/
#include "CClustOfContLoadsAndMoments.phs"


/****
 *  ICluster
 * initialize a cluster, so that we can store  a reference to each of
 * the Square objects in it
 */

void  CClustOfContLoadsAndMoments::ICluster( void )
{
  CCluster::ICluster();
}

/*****
 *
 *   Add to the cluster, a Square object reference, hitPt is the location
 *  where the mouse hit, I really don't know if it is in panorama units, but
 *  it should be in panorama units
 */

void  CClustOfContLoadsAndMoments::AddToList( Point  hitPt,
                      MyObjects whatKindOfObject )
{
  switch( whatKindOfObject )
  {
    case aContinuousLoad:
      theContinuousLoad = new( CContinuousLoad );
      Add( theContinuousLoad );      /* add theContinuousLoad to cluster */
      theContinuousLoad->theHitPoint = hitPt;
      theContinuousLoad->InitializeYourself();
      theContinuousLoad->itsTrussPane = this->itsTrussPane;
      theContinuousLoad->theKindOfObjectIam = aContinuousLoad;
      theContinuousLoad->theObjectNumber = this->numItems;
      break;
    case aContinuousGravityLoad:
      theContinuousGravityLoad = new( CContinuousGravityLoad );
      Add( theContinuousGravityLoad );  /* add theContinuousGravityLoad to cluster */
      theContinuousGravityLoad->theHitPoint = hitPt;
      theContinuousGravityLoad->InitializeYourself();
      theContinuousGravityLoad->itsTrussPane = this->itsTrussPane;
      theContinuousGravityLoad->theKindOfObjectIam = aContinuousGravityLoad;
      theContinuousGravityLoad->theObjectNumber = this->numItems;
      break;
    case aContUniformGravityLoad:
      theContUniformGravityLoad = new( CContUniformGravityLoad );
      Add( theContUniformGravityLoad );  /* add theContUniformGravityLoad to cluster */
      theContUniformGravityLoad->theHitPoint = hitPt;
      theContUniformGravityLoad->InitializeYourself();
      theContUniformGravityLoad->itsTrussPane = this->itsTrussPane;
      theContUniformGravityLoad->theKindOfObjectIam = aContUniformGravityLoad;
      theContUniformGravityLoad->theObjectNumber = this->numItems;
      break;
    case aContUniformWindLoad:
      theContUniformWindLoad = new( CContUniformWindLoad );
      Add( theContUniformWindLoad );  /* add theContUniformWindLoad to cluster */
      theContUniformWindLoad->theHitPoint = hitPt;
      theContUniformWindLoad->InitializeYourself();
      theContUniformWindLoad->itsTrussPane = this->itsTrussPane;
      theContUniformWindLoad->theKindOfObjectIam = aContUniformWindLoad;
      theContUniformWindLoad->theObjectNumber = this->numItems;
      break;
    case aContWindLoad:
      theContWindLoad = new( CContWindLoad );
      Add( theContWindLoad );      /* add theContWindLoad to cluster */
      theContWindLoad->theHitPoint = hitPt;
      theContWindLoad->InitializeYourself();
      theContWindLoad->itsTrussPane = this->itsTrussPane;
      theContWindLoad->theKindOfObjectIam = aContWindLoad;
      theContWindLoad->theObjectNumber = this->numItems;
      break;
    case aContinuousMoment:
      theContinuousMoment = new( CContinuousMoment );
      Add( theContinuousMoment );      /* add theContinuousMoment to cluster */
      theContinuousMoment->theHitPoint = hitPt;
      theContinuousMoment->InitializeYourself();
      theContinuousMoment->itsTrussPane = this->itsTrussPane;
      theContinuousMoment->theKindOfObjectIam = aContinuousMoment;
      theContinuousMoment->theObjectNumber = this->numItems;
      break;
  }
}

/*****
 *
 * Dispose of all elements in this cluster
 *
 */
void  CClustOfContLoadsAndMoments::DisposeAll(void)
{
  inherited::DisposeAll();
}
