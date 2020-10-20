/* ---------------------------------------------------------------------------- */
/* Copyright ©1987-1989 by Gary Gregory and Neil Ticktin.  All rights reserved. */
/* Version 1.0                                  */
/* ---------------------------------------------------------------------------- */

#define _DHEngineLibHeader_

#ifndef _DHTypes_
  #include "DHTypes.h"
#endif

/* ---------------------------------------------------------------------------------------- */
/*                     M a c r o s                       */
/* ---------------------------------------------------------------------------------------- */

/* --------------------    DHCurEditTextFirstChar  --------------------------------------- */
/*                                                */
/* returns the first character of the current EditText item in the dialog whose       */
/* pointer is passed in dp.  Returns $00 if there is not edit text item.           */
/*                                                */
/* ---------------------------------------------------------------------------------------- */
#define DHCurEditTextFirstChar(dp) DHCurEditTextNthChar(dp, 0)
#define DHCUREDITTEXTFIRSTCHAR  DHCurEditTextFirstChar

/* ---------------------------------------------------------------------------------------- */
/*               E n d  M a c r o s                          */
/* ---------------------------------------------------------------------------------------- */

extern boolean DHDialogHandler(DialogHandlerRecordPtr dhp);

extern void  DHPasteDialog(short  itemId,
DialogPtr  dp,
DialogHandlerRecordPtr dhp);

extern pascal void  DHDebugWindowDefaultItem(WindowPtr theWindow,
short  itemId);
/* this is the procedure that draws the bold outline around the DHDebugWindow ok */

extern void  DHDebugWindow(Str255  str);
/* dispays a dialog box with and OK button and the string passed. */

extern void DHReal2Str(float  value,
DecForm form, StringPtr newStr);
/* returns a string containing the converted float passed in the form passed. */

extern void  DHStripLeadingSpaces(StringPtr str);
/* strips all leading spaces in the string passed. */

extern void  DHStripTrailingSpaces(StringPtr  str);
/* strips all trailing spaces in the string passed. */

extern boolean DHStr2Int(Str255 str,
short * value);
/* returns TRUE if the conversion of the string passed to an short was successful, else FALSE */

extern boolean DHStr2LongInt(Str255 str,
long *  value);
/* returns TRUE if the conversion of the string passed to an LONGINT was successful, else FALSE */

extern boolean DHStr2Real(Str255  str,
float * value);
/* returns TRUE if the conversion of the string passed to an float was successful, else FALSE */

extern short DHCurEditTextItem(DialogPtr  dp);
/* returns item number of current edittext item of a dialog or 0 if there are none */

extern short DHCurEditTextLength(DialogPtr  dp);
/* returns num characters  currently in the current edit text record of dp,  -1 if there are no EditText items in the dialog */

extern short DHCurEditTextInsertionPos(DialogPtr  dp);
/* returns the current position of the current edittext's insertion point */
/* returns -1 if there are no EditText items in the dialog */

extern unsigned char  DHCurEditTextNthChar(DialogPtr dp,
short  nTh);
/* returns the nth character of the current EditText item in the dialog whose */
/* pointer is passed in dp.  Returns $00 if there is not edit text item. */

extern void  DHSetEditTextInsertionPos(DialogPtr  dp,
short  position);

extern void  DHErrMsg (short, DialogHandlerRecordPtr ,Str255, Str255);

extern  boolean CheckIntOrReal(DialogHandlerRecordPtr, DialogPtr, short *);

/* called from Engine.c */

extern  void  MoveNearMousePointer(DialogHandlerRecordPtr);

extern  void  SetStaticStrings(DialogPtr, DialogHandlerRecordPtr);

extern  void  SetStaticIntegers(DialogPtr, DialogHandlerRecordPtr);

extern  void  SetStaticLongIntegers(DialogPtr, DialogHandlerRecordPtr);

extern  void  SetStaticReals(DialogPtr, DialogHandlerRecordPtr);

extern  void  SetEditStrings(DialogPtr, DialogHandlerRecordPtr);

extern  void  SetEditIntegers(DialogPtr, DialogHandlerRecordPtr);

extern  void  SetEditLongIntegers(DialogPtr, DialogHandlerRecordPtr);

extern  void  SetEditReals(DialogPtr, DialogHandlerRecordPtr);

extern  void  SetCheckBoxes(DialogPtr, DialogHandlerRecordPtr);

extern  void  SetRadioButtons(DialogPtr, DialogHandlerRecordPtr);

extern  void  SetPushButtons(DialogHandlerRecordPtr);

extern  void  LoadPictItems(DialogPtr, DialogHandlerRecordPtr);

extern  void  LoadIconItems(DialogPtr, DialogHandlerRecordPtr);

extern  void  LoadDisplayTexts(DialogPtr, DialogHandlerRecordPtr);

extern  void  LoadPopUpMenus(DialogHandlerRecordPtr);

extern  void  LoadMenuBars(DialogHandlerRecordPtr);

extern  void  LoadCounters(DialogPtr, DialogHandlerRecordPtr);

extern  void  LoadPickLists(DialogPtr, DialogHandlerRecordPtr);

extern  void  UnloadDispTexts(DialogHandlerRecordPtr);  /* Release the memory held by the TE Record(s) */

extern  void  UnloadPopUpMenus(DialogHandlerRecordPtr);  /* Dispose of the pop up menus loaded */

extern  void  UnloadMenuBars(DialogHandlerRecordPtr);  /* Dispose of the pop up menus loaded in each menu bar */

    /* Transfer data from the dialog box to the DialogHandler record */

extern  void  SaveEditStrings(DialogPtr, DialogHandlerRecordPtr);

extern  void  SaveStaticStrings(DialogPtr, DialogHandlerRecordPtr);

extern  void  SaveStaticIntegers(DialogPtr, DialogHandlerRecordPtr);

extern  void  SaveStaticLongIntegers(DialogPtr, DialogHandlerRecordPtr);

extern  void  SaveStaticReals(DialogPtr, DialogHandlerRecordPtr);

extern  void  PopUpChoice(PopUpMenuPtr);

extern  void  FilterEI(short, short, long, DialogHandlerRecordPtr, boolean *,
          short *);

extern  void  FilterER(short, short, long, DialogPtr, DialogHandlerRecordPtr,
          short *);

extern  boolean CheckForCCP(short, long, short, DialogPtr,  DialogHandlerRecordPtr);

extern  boolean FilterMouseDown(EventRecord, DialogPtr, DialogHandlerRecordPtr,
          short  *);

/*
 * Declared in NumberParsers.c
 *
 */

extern EditIntegerPtr  FindEipItem(EditIntegerPtr, short);

extern EditLongIntegerPtr  FindElipItem(EditLongIntegerPtr, short);

extern EditRealPtr  FindErpItem(EditRealPtr, short);


