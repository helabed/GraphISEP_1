/*****
 * Truss.c
 *
 *  A Truss main file for writing programs with the
 *  THINK Class Library
 *
 *****/
#include "CTrussApp.h"

extern  CApplication  *gApplication;

void main()

{
  gApplication = new(CTrussApp);
  ((CTrussApp *)gApplication)->ITrussApp();
  gApplication->Run();
  gApplication->Exit();
}

