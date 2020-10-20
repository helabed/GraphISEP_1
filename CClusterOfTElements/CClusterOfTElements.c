/****
 * CClusterOfTElements.c
 *
 *  cluster of TElements  for a typical CTrussPane class
 *
 ****/

#include "CClusterOfTElements.phs"

/****
 *  ICluster
 * initialize a cluster, so that we can store  a reference to each of
 * the  objects in it
 */

void  CClusterOfTElements::ICluster( void )
{
  CCluster::ICluster();
}

/*****
 *
 *   Add to the cluster, a  object reference, hitPt is the location
 *  where the mouse hit, I really don't know if it is in panorama units, but
 *  it should be in panorama units
 */


void  CClusterOfTElements::AddToList( Point  hitPt, MyObjects whatKindOfObject )
{
  switch( whatKindOfObject )
  {
    case aGenericElement:
      theGenericTElement = new( CGenericTElement );
      Add( theGenericTElement );
      theGenericTElement->theHitPoint = hitPt;
      theGenericTElement->itsTrussPane = this->itsTrussPane;
      theGenericTElement->InitializeYourself();
      theGenericTElement->thisObjectPointer = theGenericTElement;
      theGenericTElement->theKindOfObjectIam = aGenericElement;
      theGenericTElement->theObjectNumber = this->numItems;
      break;
    case aWoodElement:
      theRegularWoodTElement = new( CRegularWoodTElement );
      Add( theRegularWoodTElement );  /* add theTrussElementObject to cluster */
      theRegularWoodTElement->theHitPoint = hitPt;
      theRegularWoodTElement->itsTrussPane = this->itsTrussPane;
      theRegularWoodTElement->InitializeYourself();
      theRegularWoodTElement->thisObjectPointer = theRegularWoodTElement;
      theRegularWoodTElement->theKindOfObjectIam = aWoodElement;
      theRegularWoodTElement->theObjectNumber = this->numItems;
      break;
    case aTopBottomWoodElement:
      theTBWoodTElement = new( CTBWoodTElement );
      Add( theTBWoodTElement );  /* add theTrussElementObject to cluster */
      theTBWoodTElement->theHitPoint = hitPt;
      theTBWoodTElement->itsTrussPane = this->itsTrussPane;
      theTBWoodTElement->InitializeYourself();
      theTBWoodTElement->thisObjectPointer = theTBWoodTElement;
      theTBWoodTElement->theKindOfObjectIam = aTopBottomWoodElement;
      theTBWoodTElement->theObjectNumber = this->numItems;
      break;
  }
}

/*****
 *
 * Dispose of all elements in this cluster
 *
 */
void  CClusterOfTElements::DisposeAll(void)
{
  inherited::DisposeAll();
}
