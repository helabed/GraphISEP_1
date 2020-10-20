/****
 * CClustOfConcLoadsAndMoments.c
 *
 *  cluster of objects  for a typical CTrussPane class
 *
 ****/

#include "CClustOfConcLoadsAndMoments.phs"

/****
 *  ICluster
 * initialize a cluster, so that we can store  a reference to each of
 * the  objects in it
 */

void  CClustOfConcLoadsAndMoments::ICluster( void )
{
  CCluster::ICluster();
}

/*****
 *
 *   Add to the cluster, a  object reference, hitPt is the location
 *  where the mouse hit, I really don't know if it is in panorama units, but
 *  it should be in panorama units
 */

void  CClustOfConcLoadsAndMoments::AddToList( Point  hitPt, MyObjects whatKindOfObject )
{
  switch( whatKindOfObject )
  {
    case aConcentratedLoad:
      theConcLoadObject = new( CConcLoadObject );
      Add( theConcLoadObject );      /* add theConcLoadObject to cluster */
      theConcLoadObject->theHitPoint = hitPt;
      theConcLoadObject->InitializeYourself();
      theConcLoadObject->itsTrussPane = this->itsTrussPane;
      theConcLoadObject->theKindOfObjectIam = aConcentratedLoad;
      theConcLoadObject->theObjectNumber = this->numItems;
      break;
    case aConcentratedMoment:
      theConcMoment = new( CConcMoment );
      Add( theConcMoment );      /* add theConcMoment to cluster */
      theConcMoment->theHitPoint = hitPt;
      theConcMoment->InitializeYourself();
      theConcMoment->itsTrussPane = this->itsTrussPane;
      theConcMoment->theKindOfObjectIam = aConcentratedMoment;
      theConcMoment->theObjectNumber = this->numItems;
      break;
  }
}

/*****
 *
 * Dispose of all elements in this cluster
 *
 */
void  CClustOfConcLoadsAndMoments::DisposeAll(void)
{
  inherited::DisposeAll();
}
