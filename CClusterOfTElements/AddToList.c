/*****
 *
 *   Add to the cluster, a  object reference, hitPt is the location
 *  where the mouse hit, I really don't know if it is in panorama units, but
 *  it should be in panorama units
 */


#include <CCluster.h>
#include <CObject.h>
#include <CDocument.h>
#include <CBureaucrat.h>
#include "CClusterOfTElements.h"
#include "CTrussElementObject.h"
#include "TrussCommands.h"


void  CClusterOfTElements::AddToList( Point  hitPt, int whatKindOfObject )
{

    theTrussElementObject = new( CTrussElementObject );

    Add( theTrussElementObject );  /* add theTrussElementObject to cluster */

    theTrussElementObject->theHitPoint = hitPt;
    /* making sure that theTrussElementObject
      instance variable has a copy
      of the hitPt that was send to
      us from CTrussPane */

    PenPat( black );
    theTrussElementObject->InitializeYourself();
}

