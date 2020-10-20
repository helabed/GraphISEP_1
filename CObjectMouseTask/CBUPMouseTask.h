/****
 * CBUPMouseTask.h
 *
 *   object Mouse task class for a typical CTrussPane class.
 *
 ****/

#define _H_CBUPMouseTask      /* Include this file only once */

#include "CObjectMouseTask.h"


struct CBUPMouseTask : CObjectMouseTask {


        /* Instance variables */
  struct CGussetPane        *itsGussetPane;
  CRegularWoodTElement      *theWoodObject;
  CGussetPlate          *theGussetPlate;


        /* Methods */
  void    BeginTracking(  Point *startPt);
  void    KeepTracking( Point *currPt, Point *prevPt, Point *startPt);
  void    EndTracking( Point *currPt, Point *prevPt, Point *startPt);
  void    Undo(void);
};

