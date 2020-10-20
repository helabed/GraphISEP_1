/****
 * CClusterOfNodes.c
 *
 *  cluster of Nodes  for a typical CTrussPane class
 *
 ****/
#include "CClusterOfNodes.phs"


/****
 *  ICluster
 * initialize a cluster, so that we can store  a reference to each of
 * the Node objects in it
 */

void  CClusterOfNodes::ICluster( void )
{
  CCluster::ICluster();
}

/*****
 *
 *   Add to the cluster, a Node object reference, hitPt is the location
 *  where the mouse hit, I really don't know if it is in panorama units, but
 *  it should be in panorama units
 */

void  CClusterOfNodes::AddToList( Point  hitPt, MyObjects whatKindOfObject )
{
  switch( whatKindOfObject )
  {
    case aGenericNode:
      theGenericNode = new( CGenericNode );
      Add( theGenericNode );      /* add theNodeObject to cluster */
      theGenericNode->theHitPoint = hitPt;
      theGenericNode->theObjectNumber = this->numItems;
      theGenericNode->InitializeYourself();
      theGenericNode->itsTrussPane = this->itsTrussPane;
      theGenericNode->thisObjectPointer = theGenericNode;
      theGenericNode->theKindOfObjectIam = aGenericNode;
      break;
    case aGussetPlate:
      theCGussetPlate = new( CGussetPlate );
      Add( theCGussetPlate );      /* add theNodeObject to cluster */
      theCGussetPlate->theHitPoint = hitPt;
      theCGussetPlate->theObjectNumber = this->numItems;
      theCGussetPlate->InitializeYourself();
      theCGussetPlate->itsTrussPane = this->itsTrussPane;
      theCGussetPlate->thisObjectPointer = theCGussetPlate;
      theCGussetPlate->theKindOfObjectIam = aGussetPlate;
      break;
    case aTBGussetPlate:
      theTBGussetPlate = new( CTBGussetPlate );
      Add( theTBGussetPlate );      /* add theNodeObject to cluster */
      theTBGussetPlate->theHitPoint = hitPt;
      theTBGussetPlate->theObjectNumber = this->numItems;
      theTBGussetPlate->InitializeYourself();
      theTBGussetPlate->itsTrussPane = this->itsTrussPane;
      theTBGussetPlate->thisObjectPointer = theTBGussetPlate;
      theTBGussetPlate->theKindOfObjectIam = aTBGussetPlate;
      break;
  }
}

        static void Remove_LCluster( CNodeObject
            *theObject)
        {
          if (theObject->ConcLandMAreConnected);
          {
            theObject->theNodeLoads->Dispose();
          }
        }
        static void Remove_TECluster( CNodeObject
            *theObject)
        {
          if (theObject->TElementsAreConnected);
          {
            theObject->theNodeTElements->Dispose();
          }
        }



/*****
 *
 * Dispose of all elements in this cluster
 *
 */
void  CClusterOfNodes::DisposeAll(void)
{
/*  DoForEach( Remove_LCluster );
  DoForEach( Remove_TECluster );
*/  inherited::DisposeAll();
}

