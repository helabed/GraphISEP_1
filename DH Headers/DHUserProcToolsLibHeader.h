/* ---------------------------------------------------------------------------- */
/* Copyright ©1987-1989 by Gary Gregory and Neil Ticktin.  All rights reserved. */
/* Version 1.0                                  */
/* ---------------------------------------------------------------------------- */

#define _DHUserProcToolsLibHeader_


#ifndef _global_
  #include <global.h>
#endif

#ifndef _DHTypes_
  #include "DHTypes.h"
#endif

/*
 * Find tools
 */

extern CheckBoxPtr DHFindCheckBoxPtr(DialogHandlerRecordPtr dhp,
short  itemId);


extern CounterPtr DHFindCounterPtr(DialogHandlerRecordPtr dhp,
short  itemId);


extern DisplayTextPtr DHFindDisplayTextPtr(DialogHandlerRecordPtr dhp,
short  itemId);


extern EditStringPtr DHFindEditStringPtr(DialogHandlerRecordPtr dhp,
short  itemId);


extern EditIntegerPtr DHFindEditIntegerPtr(DialogHandlerRecordPtr dhp,
short  itemId);


extern EditLongIntegerPtr DHFindEditLongIntegerPtr(DialogHandlerRecordPtr dhp,
short  itemId);


extern EditRealPtr DHFindEditRealPtr(DialogHandlerRecordPtr dhp,
short  itemId);


extern IconPtr DHFindIconPtr(DialogHandlerRecordPtr dhp,
short  itemId);


extern PicturePtr DHFindPicturePtr(DialogHandlerRecordPtr dhp,
short  itemId);


extern PickListPtr DHFindPickListPtr(DialogHandlerRecordPtr dhp,
short  itemId);


extern PopUpMenuPtr DHFindPopUpMenuPtr(DialogHandlerRecordPtr dhp,
short  MENUid);


extern PullDownMenuPtr DHFindPullDownMenuPtrInBar(MenuBarPtr  aMenuBar,
short  MENUid);


extern PullDownMenuPtr DHFindPullDownMenuPtrInAllBars(DialogHandlerRecordPtr dhp,
short  MENUid);


extern PushButtonPtr DHFindPushButtonPtr(DialogHandlerRecordPtr dhp,
short  itemId);


extern RadioButtonPtr DHFindRadioButtonPtrInSet(RadioButtonSetPtr setPtr,
short  itemId);


extern RadioButtonPtr DHFindRadioButtonPtrInAllSets(DialogHandlerRecordPtr dhp,
short  itemId);

extern RadioButtonSetPtr DHFindRadioButtonSetPtr(DialogHandlerRecordPtr dhp,
short  itemId);

extern StaticStringPtr DHFindStaticStringPtr(DialogHandlerRecordPtr dhp,
short  itemId);


extern StaticIntegerPtr DHFindStaticIntegerPtr(DialogHandlerRecordPtr dhp,
short  itemId);


extern StaticLongIntegerPtr DHFindStaticLongIntegerPtr(DialogHandlerRecordPtr dhp,
short  itemId);


extern StaticRealPtr DHFindStaticRealPtr(DialogHandlerRecordPtr dhp,
short  itemId);

/*
 * Display text tools
 */

extern void  DHEraseDisplayText(DisplayTextPtr dTxPtr);


extern boolean DHChangeDisplayText(DialogHandlerRecordPtr dhp,
short  itemId,
short  newTEXTid,
DialogPtr  dp);

/*
 * Pick list tools
 */

extern short DHStringListCount(Handle  strRsrcHandle);


extern void  DHSelectPickListItem(ListHandle  listH,
short  index,
boolean setIt);


extern void  DHAddPickListStringList(ListHandle listH,
short  stringListId);


extern void  DHEmptyPickList(ListHandle listH);


extern boolean DHMouseInPickListScrollBar(DialogPtr dp,
short  itemId);

/*
 * Control tools
 */

extern boolean DHChangeControlTitleToString(short  itemId,
Str255  newTitle,
DialogPtr  dp);


extern boolean DHChangeControlTitleToRsrc(short itemId,
short  strListId,
short  index,
DialogPtr  dp);





