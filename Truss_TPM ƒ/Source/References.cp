/******************************************************************************
 References.cp

      Create dummy references for Object I/O classes in TCL

  Generated by Visual Architect. 12:55 AM Thu, Mar 21, 1996

  This file is only generated once per project. You can modify it
  to remove references to classes that your project does not
  contain. If your project contains a class, it should remain.

  In a separate file to allow ReferenceStdClasses to
  be unloaded after initialization. For this reason, it is a
  good idea to put this and any other initialization-only
  files in a separate segment.

 ******************************************************************************/

  // TCL References

#include <CArrayPane.h>
#include <CArrowPopupPane.h>
#include <CBitMap.h>
#include <CBitMapPane.h>
#include <CCheckBox.h>
#include <CDataFile.h>
#include <CDialog.h>
#include <CDialogText.h>
#include <CEditText.h>
#include <CEnvironment.h>
#include <CIconPane.h>
#include <CIntegerText.h>
#include <CPaneBorder.h>
#include <CPicture.h>
#include <CPopupMenu.h>
#include <CRadioControl.h>
#include <CRadioGroupPane.h>
#include <CRunArray.h>
#include <CScrollBar.h>
#include <CScrollPane.h>
#include <CStaticText.h>
#include <CStdPopupPane.h>
#include <CStyleText.h>
#include <CTable.h>
#include <CTextEnvirons.h>
#include <CWindow.h>

#include <CColorTextEnvirons.h>
#include <CIconButton.h>
#include <CLine.h>
#include <CPICTGrid.h>
#include <CPictureButton.h>
#include <CPolyButton.h>
#include <CRectOvalButton.h>
#include <CRoundRectButton.h>
#include <CSubviewDisplayer.h>


#include "References.h"


/*============================================================================
 ReferenceStdClasses

    Reference all standard TCL classes (which do I/O)
 ============================================================================*/

void  ReferenceStdClasses(void)

{
  TCL_FORCE_REFERENCE(CArray);
  TCL_FORCE_REFERENCE(CArrayPane);
  TCL_FORCE_REFERENCE(CArrowPopupPane);
  TCL_FORCE_REFERENCE(CBitMap);
  TCL_FORCE_REFERENCE(CBitMapPane);
  TCL_FORCE_REFERENCE(CButton);
  TCL_FORCE_REFERENCE(CCheckBox);
  TCL_FORCE_REFERENCE(CDialog);
  TCL_FORCE_REFERENCE(CDialogText);
  TCL_FORCE_REFERENCE(CEditText);
  TCL_FORCE_REFERENCE(CEnvironment);
  TCL_FORCE_REFERENCE(CIconPane);
  TCL_FORCE_REFERENCE(CIntegerText);
  TCL_FORCE_REFERENCE(CPane);
  TCL_FORCE_REFERENCE(CPaneBorder);
  TCL_FORCE_REFERENCE(CPanorama);
  TCL_FORCE_REFERENCE(CPicture);
  TCL_FORCE_REFERENCE(CPopupMenu);
  TCL_FORCE_REFERENCE(CRadioControl);
  TCL_FORCE_REFERENCE(CRadioGroupPane);
  TCL_FORCE_REFERENCE(CRunArray);
  TCL_FORCE_REFERENCE(CScrollBar);
  TCL_FORCE_REFERENCE(CScrollPane);
  TCL_FORCE_REFERENCE(CStaticText);
  TCL_FORCE_REFERENCE(CStdPopupPane);
  TCL_FORCE_REFERENCE(CStyleText);
  TCL_FORCE_REFERENCE(CTable);
  TCL_FORCE_REFERENCE(CTextEnvirons);
  TCL_FORCE_REFERENCE(CWindow);

  TCL_FORCE_REFERENCE(CColorTextEnvirons);
  TCL_FORCE_REFERENCE(CIconButton);
  TCL_FORCE_REFERENCE(CLine);
  TCL_FORCE_REFERENCE(CPICTGrid);
  TCL_FORCE_REFERENCE(CPictureButton);
  TCL_FORCE_REFERENCE(CPolyButton);
  TCL_FORCE_REFERENCE(CRectOvalButton);
  TCL_FORCE_REFERENCE(CRoundRectButton);
  TCL_FORCE_REFERENCE(CSubviewDisplayer);
}

