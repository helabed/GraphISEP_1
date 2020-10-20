/****
 * CGussetPDoc.h
 *
 *  Document class for a typical application.
 *
 ****/

#define  _H_CGussetPDoc      /* Include this file only once */

#include <CDocument.h>
#include "TrussCommands.h"

struct CGussetPDoc : CDocument {

          /* instance variables*/
  SystemOfUnits        theSystemOfUnits;
  float            theLoadScale;
  float            theStructureScale;
  float            horzDrawingSize;
  float            vertDrawingSize;
  struct  CGussetPlate    *itsGussetPlate;



                  /** Construction/Destruction **/
  void    IGussetPDoc(CBureaucrat *aSupervisor, Boolean printable);
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

