/*****
 * CTrussApp.h
 *
 *  Application class for a typical application.
 *
 *****/

#define  _H_CTrussApp    /* Include this file only once */

#include <CApplication.h>

struct CTrussApp : CApplication {

  /* instance variables */

  long  structureNumber;

  /* Methods */


  void  ITrussApp(void);
  void  SetUpFileParameters(void);

  void  DoCommand(long theCommand);

  void  Exit(void);

  void  CreateDocument(void);
  void  OpenDocument(SFReply *macSFReply);

  void   SetUpMenus(void);
};

