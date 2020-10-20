/****
 * CClusterOfAbstracts.c
 *
 *  cluster of TElements  for a typical CTrussPane class
 *
 ****/


#include "CClusterOfAbstracts.phs"



/****
 *  ICluster
 * initialize a cluster, so that we can store  a reference to each of
 * the  objects in it
 */

void  CClusterOfAbstracts::ICluster( void )
{
  CCluster::ICluster();
}

/*****
 *
 *   Add to the cluster, a  object reference, hitPt is the location
 *  where the mouse hit, I really don't know if it is in panorama units, but
 *  it should be in panorama units
 */


void  CClusterOfAbstracts::AddToList( Point  hitPt, int whatKindOfObject )
{
}

/*****
 *
 * Dispose of all elements in this cluster
 *
 */
void  CClusterOfAbstracts::DisposeAll(void)
{
  inherited::DisposeAll();
}
