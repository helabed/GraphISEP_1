/******************************************************************************
 CApp.cp

        My Application Class

  Copyright � 1996 Esoft International. All rights reserved.

  Generated by Visual Architect� 12:55 AM Thu, Mar 21, 1996

  This file is only generated once. You can modify it by filling
  in the placeholder methods and adding any new methods you wish.

  If you change the name of the application, a fresh version of this
  file will be generated. If you have made any changes to the file
  with the old name, you will have to copy those changes to the new
  file by hand.

 ******************************************************************************/

#include "CApp.h"

#include <CDialog.h>
#include <TCLForceReferences.h>

//#include "AppCommands.h"      // Remove comments if DoCommand overridden

TCL_DEFINE_CLASS_M1(CApp, x_CApp);

/**** C O N S T R U C T I O N / D E S T R U C T I O N   M E T H O D S ****/


/******************************************************************************
 ICApp

    Initialize an Application.

 ******************************************************************************/

void  CApp::ICApp()

{
    // The values below are:
    //
    //   extraMasters    - The number of additional master pointer blocks
    //              to be allocated.
    //   aRainyDayFund    - The total amount of reserved memory. When
    //              allocation digs into the rainy day fund, the
    //              user is notified that memory is low. Set this
    //              value to the sum of aCriticalBalance plus
    //              aToolboxBalance plus a fudge for user warning.
    //   aCriticalBalance  - The part of the rainy day fund reserved for
    //              critical operations, like Save or Quit. Set
    //              this value to the memory needed for the largest
    //              possible Save plus aToolboxBalance. This
    //              memory will only be used if SetCriticalOperation()
    //              is set TRUE or if RequestMemory()/SetAllocation()
    //              is set FALSE (kAllocCantFail).
    //   aToolboxBalance  - The part of the rainy day fund reserved for
    //              ToolBox bozos that bomb if a memory request fails.
    //              This memory is used unless RequestMemory()/
    //              SetAllocation() is set TRUE (kAllocCanFail).
    //              Almost all TCL memory allocation is done with
    //              kAllocCanFail, and yours should be, too. The
    //              default 2K is probably enough.

  Ix_CApp(4, 24000L, 20480L, 2048L);

    // Initialize your own application data here.

}


/******************************************************************************
 ForceClassReferences  {OVERRIDE}

  Reference classes that do object I/O or are created only
  by new_by_name.
 ******************************************************************************/

void CApp::ForceClassReferences(void)

{
  x_CApp::ForceClassReferences();

    // Insert your own class references here
    // by calling TCL_FORCE_REFERENCE for each class
    // See x_CApp.cp
}


/**** C O M M A N D   M E T H O D S ****/


/******************************************************************************
 DoCommand  {OVERRIDE}

  Handle application commands
 ******************************************************************************/

void CApp::DoCommand(long theCommand)

{
  switch (theCommand)
  {

      // Insert your command cases here

    default:
      x_CApp::DoCommand(theCommand);
      break;
  }
}


/******************************************************************************
 GetDocTypeFromDialog

  Get the document type from the dialog. If you have multiple
  document types, you must override this function to extract
  the type from the dialog state. (The dialog has been executed
  and OK'd by the user.) If you do not have multiple document
  types, you can remove this function.
 ******************************************************************************/

OSType CApp::GetDocTypeFromDialog(CDialogDirector *dialog)

{
  return 0;
}

