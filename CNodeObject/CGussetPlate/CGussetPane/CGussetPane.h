/****
 * CGussetPane.h
 *
 *  Pane class for a typical application.
 *
 ****/

#define _H_CGussetPane      /* Include this file only once */
#include <Commands.h>
#include <CBartender.h>
#include <CCluster.h>
#include <CView.h>
#include <CDesktop.h>
#include <CObject.h>
#include <CPanorama.h>
#include <CWindow.h>
#include "CQuadrelateralObject.h"
#include "CNodeObject.h"
#include "CTrussElementObject.h"
#include "CConcLoadObject.h"
#include "CClustOfContLoadsAndMoments.h"
#include "CClusterOfNodes.h"
#include "CClusterOfTElements.h"
#include "CClustOfConcLoadsAndMoments.h"
#include "CObjectMouseTask.h"
#include "TrussCommands.h"

struct CGussetPane : CPanorama {

        /**************Instance Variables *************/
  CClustOfContLoadsAndMoments  *ContLoadsAndMoments;
  CClusterOfTElements      *TElementsCluster;
  CClusterOfNodes        *NodesCluster;
  CClustOfConcLoadsAndMoments  *ConcLoadsAndMoments;
  CWindow            *thePaneWindow;
  int              ObjectPlacement; /* for clean object placement */
  CQuadrelateralObject    *theContLoadOrMoment;
      /* all cont. objects are  descendants of CQuadrelateralObject*/
  CConcLoadObject        *theConcLoadOrMoment;
      /* all conc. objects are  descendants of CConcLoadObject*/
  CTrussElementObject      *theTElementObject;
  CNodeObject          *theNodeObject;
  CNodeObject          *theSelectedNodeObject;
  CTrussElementObject      *theSelectedTEObject;
  CAbstractObject        *theObject;
  MyObjects          theSelectedObject;
  MyObjects          thePreviouslySelectedObject;
  Boolean            objectAlreadySelected;
  SystemOfUnits        theSystemOfUnits;
  float            theLoadScale;
  float            theStructureScale;
  Point            previousMouseLocation;
  struct  CGussetPlate    *itsGussetPlate;
  CTrussElementObject      *itsMotherTElement;
  CList            *theListOfObjects;
  Boolean            ConnectAreaBeingDefined;
  Boolean            firstPointLocated;

        /*********************Methods *****************/

                  /** Contruction/Destruction **/
  void    IGussetPane(CView *anEnclosure, CBureaucrat *aSupervisor,
              short aWidth, short aHeight,
              short aHEncl, short aVEncl,
              SizingOption aHSizing, SizingOption aVSizing);

                  /** Drawing **/
  void    Draw(Rect *area);

                  /** Mouse **/
  void    DoClick(Point hitPt, short modifierKeys, long when);
  Boolean    SelectAnObject( Point hitPt, short modifierKeys );
  Boolean   ConnectObjectsToNode( short modifierKeys );
  Boolean    ConnectObjectsToTE( short modifierKeys );


                  /** Cursor **/
  void    AdjustCursor(Point where, RgnHandle mouseRgn);

                  /** Scrolling **/
  void    ScrollToSelection(void);

                  /* cleaning after ourselves */
  void    Dispose( void );
                  /*keyboard or menu events */
  void     DoCommand(long theCommand);
  void    DoKeyDown(char theChar, Byte keyCode, EventRecord *macEvent);
  void    DoAutoKey(char theChar, Byte keyCode, EventRecord *macEvent);
  void    DoKeyUp(char theChar, Byte keyCode, EventRecord *macEvent);
                  /* handle its Dialogs */

  void    DoSystemOfUnitsDialog( void );
  void    DoLoadsScallingDialog( void );
  void    DoStructureScallingDialog( void );
  void    PrintPage(short pageNum, short pageWidth, short pageHeight);


};

