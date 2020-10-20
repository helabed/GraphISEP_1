/****
 * CGussetPane.ITrussPane.c
 *
 *  TrussPane initialization method for a typical application.
 *
 *
 ****/

#include "CGussetPane.ph"
#include "CTrussPane.h"

void CGussetPane::IGussetPane(CView *anEnclosure, CBureaucrat *aSupervisor,
              short aWidth, short aHeight,
              short aHEncl, short aVEncl,
              SizingOption aHSizing, SizingOption aVSizing)
{
  CPanorama::IPanorama(anEnclosure, aSupervisor, aWidth, aHeight,
              aHEncl, aVEncl, aHSizing, aVSizing);

  this->SetWantsClicks(TRUE);  /* allow pane to accept mouse clicks */

    /* create an instance of all clusters class and initialize them */
  ContLoadsAndMoments = new ( CClustOfContLoadsAndMoments );
  ContLoadsAndMoments->ICluster();
  ContLoadsAndMoments->itsTrussPane = ( CTrussPane *)this;
  ConcLoadsAndMoments = new ( CClustOfConcLoadsAndMoments );
  ConcLoadsAndMoments->ICluster();
  ConcLoadsAndMoments->itsTrussPane = ( CTrussPane *)this;
  NodesCluster = new ( CClusterOfNodes );
  NodesCluster->ICluster();
  NodesCluster->itsTrussPane = ( CTrussPane *)this;
  TElementsCluster = new ( CClusterOfTElements );
  TElementsCluster->ICluster();
  TElementsCluster->itsTrussPane = ( CTrussPane *)this;

  ObjectPlacement = A_NICE_LOCATION;  /* for my pseudo Object decorator */
  previousMouseLocation.v = A_NICE_LOCATION;
  previousMouseLocation.h = A_NICE_LOCATION;


      /* setting theSelectedObject to Null so that only one
        object is selected for now.. */
  theSelectedObject = aNullObject;
  thePreviouslySelectedObject = aNullObject;
  objectAlreadySelected = FALSE;

  theSelectedNodeObject = NULL;
  theSelectedTEObject = NULL;
  theObject = NULL;

    /** I moved the init. of these variable from here into the
     ** BuildWindow() inside CTrussDoc.
     **

  theSystemOfUnits = USCustomary; /* see constants.h
  theLoadScale = 100.00;    /* 1000 lbs per inch of screen
  theStructureScale = 36.00;  /* 36 inches per inch of screen

    **/
}

