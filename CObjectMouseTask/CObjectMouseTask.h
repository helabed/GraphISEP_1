/****
 * CObjectMouseTask.h
 *
 *   object Mouse task class for a typical CTrussPane class.
 *
 ****/

#define _H_CObjectMouseTask      /* Include this file only once */

#include <CMouseTask.h>
#include "CClustOfContLoadsAndMoments.h"
#include "CClusterOfNodes.h"
#include "CClustOfConcLoadsAndMoments.h"
#include "CClusterOfTElements.h"
#include "TrussCommands.h"


struct CObjectMouseTask : CMouseTask {


        /* Instance variables */
  Point              oldhitPt;
  Point              newhitPt;
  int                counter;
  CSquareObject          *theContLoadOrMoment;
  struct CNodeObject        *theNodeObject;
  CConcLoadObject          *theConcLoadOrMoment;
  CTrussElementObject        *theTElementObject;
  MyObjects            theSelectedObject;
  CAbstractObject          *theObject;
  Boolean              noObjectSelectedFlag;
  CClustOfContLoadsAndMoments    *ContLoadsAndMoments;
  CClusterOfTElements        *TElementsCluster;
  CClusterOfNodes          *NodesCluster;
  CClustOfConcLoadsAndMoments    *ConcLoadsAndMoments;
  struct CTrussPane        *itsTrussPane;


        /* Methods */
  void    IObjectMouseTask( short   aNameIndex);
  void    BeginTracking(  Point *startPt);
  void    KeepTracking( Point *currPt, Point *prevPt, Point *startPt);
  void    EndTracking( Point *currPt, Point *prevPt, Point *startPt);
  void    Undo(void);
  void    CastYSelfIntoCorrectObject( void );
};

