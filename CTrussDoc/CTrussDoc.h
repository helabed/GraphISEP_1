/****
 * CTrussDoc.h
 *
 *  Document class for a typical application.
 *
 ****/

#define  _H_CTrussDoc      /* Include this file only once */

#include <CDocument.h>
#include "TrussCommands.h"

struct CTrussDoc : CDocument {

          /* instance variables*/
  SystemOfUnits        theSystemOfUnits;
  float            theLoadScale;
  float            theStructureScale;
  float            horzDrawingSize;
  float            vertDrawingSize;



                  /** Construction/Destruction **/
  void    ITrussDoc(CBureaucrat *aSupervisor, Boolean printable);
  void    Dispose();

  void    DoCommand(long theCommand);

  void    Activate(void);
  void    Deactivate(void);

  void    NewFile(void);
  void    OpenFile(SFReply *macSFReply);
  void    BuildWindow(Handle theData);

                  /** Filing **/
  Boolean    DoSave(void);
  Boolean    DoSaveAs(SFReply *macSFReply);
  void    DoRevert(void);
  short    PageCount( void );
  void    DrawingSizeDialog( void );
};

