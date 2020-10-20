/* ---------------------------------------------------------------------------- */
/* Copyright ©1987-1989 by Gary Gregory and Neil Ticktin.  All rights reserved. */
/* Version 1.0                                  */
/* ---------------------------------------------------------------------------- */

#define _DHExtraProgToolsLibHeader_

#ifndef _global_
  #include <global.h>
#endif


#ifndef _DHTypes_
  #include "DHTypes.h"
#endif

extern void  DHInitToolbox(void);


extern void  DHShowArrowCursor(void);
/* This procedure changes the cursor to an arrow cursor. */


extern void  DHShowWatchCursor(void);
/* This procedure changes the cursor to a watch cursor. */


extern void  DHShowIBeamCursor(void);
/* This procedure changes the cursor to an iBeam cursor. */


extern void  DHShowPlusCursor(void);
/* This procedure changes the cursor to a plus cursor. */


extern void  DHShowCrossCursor(void);
/* This procedure changes the cursor to a cross cursor. */


extern pascal short SFDeleteChangeButton(short itemId,
  DialogPtr  theDialog);

/* this routine is a hook to change the 'Open' button to 'Delete' in the DHSFDelete routine */


extern OSErr DHSFDelete(SFReply *  aReply,
  short  DLOGId);


extern boolean DHSetDocumentTypeAndCreator(SFReply  reply,
  OSType  ftype,
  OSType  fcreator);


extern void  DHUserDefinedAlert(short  alertId,
  short  stringListId,
  short  stringIndex,
  Str255  paramA,
  Str255  paramB,
  Str255  paramC);

extern void  DHDebugWindow(Str255  str);

/* ----------------------------------------------------------------------------------- */
/* --                                        -- */
/* --  The following functions are NOT in the Pascal version of DialogHandler.    -- */
/* --                                        -- */
/* --      void DHPStrCopy(pSource, pDest)                    -- */
/* --      void DHPDeleteFirstChar (str)                    -- */
/* --      void DHPInsert (newChar, str, pos)                  -- */
/* --      void DHPStrCat(s1, s2)                        -- */
/* --                                         -- */
/* ----------------------------------------------------------------------------------- */

extern void DHPStrCopy(unsigned char *pSource,
  unsigned char *pDest);

extern void DHPDeleteFirstChar (Str255 str);

extern void DHPInsert (unsigned char newChar,
  Str255 str,
  short pos);

extern void DHPStrCat(Str255 s1,
  Str255 s2);

