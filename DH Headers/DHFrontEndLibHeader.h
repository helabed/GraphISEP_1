/* ---------------------------------------------------------------------------- */
/* Copyright ©1987-1989 by Gary Gregory and Neil Ticktin.  All rights reserved. */
/* Version 1.0                                  */
/* ---------------------------------------------------------------------------- */

#define _DHFrontEndLibHeader_

#ifndef _DHTypes_
  #include "DHTypes.h"
#endif

/* ---------------------------------------------------------------------------------------- */
/*                     M a c r o s                       */
/* ---------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------ */
/*      *********   DIALOG HANDLER RECORDS LOADING ROUTINES   *********        */
/*                                            */
/*      *********   THESE ROUTINES HAVE AN ADVANCED VERSION   *********        */
/* ------------------------------------------------------------------------------------ */

/* ============================   DHADDSTATICSTRING   ===================================== */

/* If no memory is available the advanced routine gives an error message           */
/* This routines adds a new record by calling its advanced version: DHAdvAddStaticString  */
/* The new record describes a static string item and is initialized with the         */
/* parameters passed in to this routine. The parameters not supplied from the Standard     */
/* routine (this one) are given a default to the Advanced version               */
/* In the routine the last 4 parameters to the Advanced version are defaults         */

/* ---------------------------------------------------------------------------------------- */

#define DHAddStaticString(dhp, itemId, str) \
  DHAdvAddStaticString(dhp, itemId, str, false, DHNoKeyEquiv(), false, NULL)
#define DHADDSTATICSTRING DHAddStaticString


/* ============================   DHADDSTATICINTEGER  ===================================== */

/* If no memory is available the advanced routine gives an error message           */
/* This routines adds a new record by calling its advanced version: DHAdvAddStaticInteger   */
/* The new record describes a static integer item and is initialized with the         */
/* parameters passed in to this routine. The parameters not supplied from the Standard     */
/* routine (this one) are given a default to the Advanced version               */
/* In the routine the last 4 parameters to the Advanced version are defaults         */

/* ---------------------------------------------------------------------------------------- */

#define DHAddStaticInteger(dhp, itemId, value) \
  DHAdvAddStaticInteger(dhp, itemId, value, false, DHNoKeyEquiv(), false, NULL)
#define DHADDSTATICINTEGER DHAddStaticInteger


/* ============================   DHAddStaticLongInteger  ===================================== */

/* If no memory is available the advanced routine gives an error message            */
/* This routines adds a new record by calling its advanced version: DHAdvAddStaticLongInteger  */
/* The new record describes a static long integer item and is initialized with the         */
/* parameters passed in to this routine. The parameters not supplied from the Standard       */
/* routine (this one) are given a default to the Advanced version                 */
/* In the routine the last 4 parameters to the Advanced version are defaults           */

/* -------------------------------------------------------------------------------------------- */

#define DHAddStaticLongInteger(dhp, itemId, value) \
  DHAdvAddStaticInteger(dhp, itemId, value, false, DHNoKeyEquiv(), false, NULL)
#define DHADDSTATICLONGINTEGER DHAddStaticLongInteger

/* ============================   DHAddStaticReal ============================================= */

/* If no memory is available the advanced routine gives an error message            */
/* This routines adds a new record by calling its advanced version: DHAdvAddStaticReal       */
/* The new record describes a static float item and is initialized with the           */
/* parameters passed in to this routine. The parameters not supplied from the Standard       */
/* routine (this one) are given a default to the Advanced version                 */
/* In the routine the last 5 parameters to the Advanced version are defaults           */

/* -------------------------------------------------------------------------------------------- */

#define DHAddStaticReal(dhp, itemId, value, dForm) \
  DHAdvAddStaticReal(dhp, itemId, value, dForm, false, DHNoKeyEquiv(), false, NULL)
#define DHADDSTATICREAL  DHAddStaticReal


/* ============================   DHAddEditString ============================================= */

/* If no memory is available the advanced routine gives an error message            */
/* This routines adds a new record by calling its advanced version: DHAdvAddEditString       */
/* The new record describes an edit string item and is initialized with the           */
/* parameters passed in to this routine. The parameters not supplied from the Standard       */
/* routine (this one) are given a default to the Advanced version                 */
/* In the routine the last parameter to the Advanced version is a default             */

/* -------------------------------------------------------------------------------------------- */

#define DHAddEditString(dhp, itemId, str) \
  DHAdvAddEditString(dhp, itemId, str, NULL)
#define DHADDEDITSTRING  DHAddEditString


/* ============================   DHAddEditInteger    ========================================= */

/* If no memory is available the advanced routine gives an error message            */
/* This routines adds a new record by calling its advanced version: DHAdvAddEditInteger     */
/* The new record describes an edit integer item and is initialized with the           */
/* parameters passed in to this routine. The parameters not supplied from the Standard       */
/* routine (this one) are given a default to the Advanced version                 */
/* In the routine the last 2 parameters to the Advanced version are defaults           */

/* -------------------------------------------------------------------------------------------- */

#define DHAddEditInteger(dhp, itemId, value) \
  DHAdvAddEditInteger(dhp, itemId, value, MININT, MAXINT)
#define DHADDEDITINTEGER  DHAddEditInteger


/* ============================   DHAddEditLongInteger    ===================================== */

/* If no memory is available the advanced routine gives an error message            */
/* This routines adds a new record by calling its advanced version: DHAdvAddEditLongInteger   */
/* The new record describes an edit long integer item and is initialized with the         */
/* parameters passed in to this routine. The parameters not supplied from the Standard       */
/* routine (this one) are given a default to the Advanced version                 */
/* In the routine the last 2 parameters to the Advanced version are defaults           */

/* -------------------------------------------------------------------------------------------- */

#define DHAddEditLongInteger(dhp, itemId, value) \
  DHAdvAddEditLongInteger(dhp, itemId, value, MINLONGINT, MAXLONGINT)
#define DHADDEDITLONGINTEGER  DHAddEditLongInteger


/* ============================   DHAddEditReal   ============================================= */

/* If no memory is available the advanced routine gives an error message            */
/* This routines adds a new record by calling its advanced version: DHAdvAddEditReal       */
/* The new record describes an edit float item and is initialized with the             */
/* parameters passed in to this routine. The parameters not supplied from the Standard       */
/* routine (this one) are given a default to the Advanced version                 */
/* In the routine the last 3 parameters to the Advanced version are defaults           */

/* -------------------------------------------------------------------------------------------- */

#define DHAddEditReal(dhp, itemId, value, dForm) \
  DHAdvAddEditReal(dhp, itemId, value, dForm, MINREAL, MAXREAL)
#define DHADDEDITREAL  DHAddEditReal


/* ============================   DHAddCheckBox   ============================================= */

/* If no memory is available the advanced routine gives an error message            */
/* This routines adds a new record by calling its advanced version: DHAdvAddCheckBox       */
/* The new record describes a check box item and is initialized with the             */
/* parameters passed in to this routine. The parameters not supplied from the Standard       */
/* routine (this one) are given a default to the Advanced version                 */
/* In the routine the last 3 parameters to the Advanced version are defaults           */

/* -------------------------------------------------------------------------------------------- */

#define DHAddCheckBox(dhp,itemId,checked) \
  DHAdvAddCheckBox(dhp, itemId, checked, DHNoKeyEquiv(), NULL)
#define DHADDCHECKBOX  DHAddCheckBox


/* ============================   DHAddPushButton ============================================= */

/* If no memory is available the advanced routine gives an error message            */
/* This routines adds a new record by calling its advanced version: DHAdvAddPushButton       */
/* The new record describes a push button item and is initialized with the             */
/* parameters passed in to this routine. The parameters not supplied from the Standard       */
/* routine (this one) are given a default to the Advanced version                 */
/* In the routine the last 3 parameters to the Advanced version are defaults           */

/* -------------------------------------------------------------------------------------------- */

#define DHAddPushButton(dhp,itemId,exitYesNo) \
  DHAdvAddPushButton(dhp, itemId, exitYesNo, DHNoKeyEquiv(), NULL)
#define DHADDPUSHBUTTON DHAddPushButton


/* ============================   DHAddRadioButtonToSet  ====================================== */

/* If no memory is available the advanced routine gives an error message            */
/* This routines adds a new record by calling its advanced version: DHAdvAddRadioButtonToSet   */
/* The new record describes a radio button item and is initialized with the           */
/* parameters passed in to this routine. The parameters not supplied from the Standard       */
/* routine (this one) are given a default to the Advanced version                 */
/* In the routine the last 2 parameters to the Advanced version are defaults           */

/* -------------------------------------------------------------------------------------------- */

#define  DHAddRadioButtonToSet(setPtr, itemId) \
  DHAdvAddRadioButtonToSet(setPtr, itemId, DHNoKeyEquiv(), NULL)
#define  DHADDRADIOBUTTONTOSET DHAddRadioButtonToSet


/* ============================   DHAddIcon   ================================================= */

/* If no memory is available the advanced routine gives an error message            */
/* This routines adds a new record by calling its advanced version: DHAdvAddIcon         */
/* The new record describes a icon item and is initialized with the               */
/* parameters passed in to this routine. The parameters not supplied from the Standard       */
/* routine (this one) are given a default to the Advanced version                 */
/* In the routine the last 4 parameters to the Advanced version are defaults           */

/* -------------------------------------------------------------------------------------------- */

#define DHAddIcon(dhp,itemId,ICONId) \
  DHAdvAddIcon(dhp, itemId, ICONId, false, DHNoKeyEquiv(), false, NULL)
#define DHADDICON DHAddIcon


/* ============================   DHAddPicture    ============================================= */

/* If no memory is available the advanced routine gives an error message            */
/* This routines adds a new record by calling its advanced version: DHAdvAddPicture       */
/* The new record describes a picture item and is initialized with the               */
/* parameters passed in to this routine. The parameters not supplied from the Standard       */
/* routine (this one) are given a default to the Advanced version                 */
/* In the routine the last 4 parameters to the Advanced version are defaults           */

/* -------------------------------------------------------------------------------------------- */

#define DHAddPicture(dhp,itemId,PICTid) \
  DHAdvAddPicture(dhp, itemId, PICTid, false, DHNoKeyEquiv(), false, NULL)
#define DHADDPICTURE DHAddPicture


/* ============================   DHAddDisplayText    ========================================= */

/* If no memory is available the advanced routine gives an error message            */
/* This routines adds a new record by calling its advanced version: DHAdvAddDisplayText     */
/* The new record describes a display text item and is initialized with the           */
/* parameters passed in to this routine. The parameters not supplied from the Standard       */
/* routine (this one) are given a default to the Advanced version                 */
/* In the routine the last 2 parameters to the Advanced version are defaults           */

/* -------------------------------------------------------------------------------------------- */

#define DHAddDisplayText(dhp,itemId,TEXTid) \
  DHAdvAddDisplayText(dhp, itemId, TEXTid, false, NULL)
#define DHADDDISPLAYTEXT DHAddDisplayText


/* ============================   DHAddPopUpMenu  ============================================= */

/* If no memory is available the advanced routine gives an error message            */
/* This routines adds a new record by calling its advanced version: DHAdvAddPopUpMenu       */
/* The new record describes a pop up menu item and is initialized with the             */
/* parameters passed in to this routine. The parameters not supplied from the Standard       */
/* routine (this one) are given a default to the Advanced version                 */
/* In the routine the last 2 parameters to the Advanced version are defaults           */

/* -------------------------------------------------------------------------------------------- */

#define DHAddPopUpMenu(dhp,MENUid,top,left,firstChoice) \
  DHAdvAddPopUpMenu(dhp, MENUid, top, left, firstChoice, false, NULL)
#define DHADDPOPUPMENU DHAddPopUpMenu


/* ============================   DHAddPickList   ============================================= */

/* If no memory is available the advanced routine gives an error message            */
/* This routines adds a new record by calling its advanced version: DHAdvAddPickList       */
/* The new record describes a pick list item and is initialized with the             */
/* parameters passed in to this routine. The parameters not supplied from the Standard       */
/* routine (this one) are given a default to the Advanced version                 */
/* In the routine the last 3 parameters to the Advanced version are defaults           */

/* -------------------------------------------------------------------------------------------- */

#define DHAddPickList(dhp,itemId,startProc) \
  DHAdvAddPickList(dhp, itemId, startProc, lOnlyOne, NULL, NULL)
#define DHADDPICKLIST DHAddPickList


/* ============================   DHLastPickListRow   ============================= */

/* DHLastPickListRow return the index of the last row in a pick list         */
/* We need to substarct one (1) from dataBound.botttom since the top left is (0, 0) */
/* Reference: Inside Macintosh Volume IV-264 (List Manager Chapter 30)         */

/* -------------------------------------------------------------------------------- */

#define DHLastPickListRow(listH) \
  ((**listH).dataBounds.bottom - 1)
#define DHLASTPICKLISTROW DHLastPickListRow


/* ============================   DHSetDefaultItem  =============== */

/* Set the default item number for a dialog             */
/* Only called in unusual circumstances. Normaly set in DHNewRecord */

/* ---------------------------------------------------------------- */

#define DHSetDefaultItem(dhp, defaultExists) \
  (dhp->defaultItem = defaultExists)
#define DHSETDEFAULTITEM DHSetDefaultItem


/* ============================   DHSetUpdateUserItem  ============ */

/* Set the update user item number for a dialog           */
/* Only called in unusual circumstances. Normaly set in DHNewRecord */

/* ---------------------------------------------------------------- */

#define DHSetUpdateUserItem(dhp, itemId) \
  (dhp->updateUserItem = itemId)
#define DHSETUPDATEUSERITEM DHSetUpdateUserItem


/* ============================   DHSetCancelButton  ========================== */

/* Set the cancel item number for a dialog                     */
/* Only called in unusual circumstances. Normaly set in DHNewRecord       */

/* ---------------------------------------------------------------------------- */

#define DHSetCancelButton(dhp, itemId) \
  (dhp->cancelButton = itemId)
#define DHSETCANCELBUTTON DHSetCancelButton


/* ============================   DHSetSelectedItem =========================== */

/* Set the selected item number for a dialog                   */
/* Only called in unusual circumstances. Normaly set in DHNewRecord       */

/* ---------------------------------------------------------------------------- */

#define DHSetSelectedItem(dhp, itemId) \
  (dhp->selectedItem = itemId)
#define DHSETSELECTEDITEM DHSetSelectedItem


/* ============================   DHSetAlert  ===================================== */

/* Tell DHDialogHandler wether or not to bring up an Alert box in case of an error   */
/* An Alert box always beeps                             */

/* -------------------------------------------------------------------------------- */

#define DHSetAlert(dhp, alertOnOff) \
  (dhp->alertUser = alertOnOff)
#define DHSETALERT DHSetAlert


/* ============================   DHSetBeep =============================== */

/* Tell DHDialogHandler wether or not to Beep in case of an error       */

/* ------------------------------------------------------------------------ */

#define DHSetBeep(dhp, beepOnOff) \
  (dhp->beepOnly = beepOnOff)
#define DHSETBEEP DHSetBeep


/* ============================   DHSetStartupProcedure =============================== */

/* Give DHDialogHandler a routine to call just before the dialog is shown on the screen */

/* ------------------------------------------------------------------------------------ */



#define DHSetStartupProcedure(dhp, userProc) \
  (dhp->startupProcedure = userProc)
#define DHSETSTARTUPPROCEDURE DHSetStartupProcedure

/* ============================   DHSetUpdateProcPtr  ============================= */

/* Give DHDialogHandler a routine to call when an update event occures         */
/* You need to set up such a routine to do any drawing in the dialog so updating   */
/* is done properly                                 */
/* You *MUST* have an update user item defined to DialogHandler so the routine     */
/* you pass may be attached to that item                       */

/* -------------------------------------------------------------------------------- */

#define DHSetUpdateProcPtr(dhp, userProc) \
  (dhp->updateProcPtr = userProc)
#define DHSETUPDATEPROCPTR DHSetUpdateProcPtr


/* ============================   DHSetCutCopyPaste  ============================== */

/* Tell DHDialogHandler wether or not to allow the use of Command-X-C-V       */
/* for Cut/Copy/Paste operations. If this feature is off you cannot Cut/Copy/Paste   */

/* -------------------------------------------------------------------------------- */

#define DHSetCutCopyPaste(dhp, ccpOnOff) \
  (dhp->cutCopyPaste = ccpOnOff)
#define DHSETCUTCOPYPASTE DHSetCutCopyPaste

/* ---------------------------------------------------------------------------------------- */
/*               E n d  M a c r o s                          */
/* ---------------------------------------------------------------------------------------- */

extern void  DHInitRecord(DialogHandlerRecordPtr dhp);

extern void DHStandardNewRecord (DialogHandlerRecordPtr * dhp,
short  DLOGId,
short  updateUserItem,
short  selectedItem);

extern void  DHNewRecord(DialogHandlerRecordPtr * dhp,
short  DLOGId,
boolean defaultItem,
short  updateUserItem,
short  cancelButton,
short  selectedItem);

/*  ********* DIALOG HANDLER RECORDS BOOLEAN SWITCH ROUTINES *****  */

extern void  DHSetCentering(DialogHandlerRecordPtr dhp,
boolean centerHorizontal,
boolean centerVertical,
boolean saveCentering);

extern void  DHSetNearMousePointer(DialogHandlerRecordPtr dhp,
short  nearMouseHor,
short  nearMouseVer);

extern void  DHSetDialogFont(DialogHandlerRecordPtr dhp,
short  font,
short  size,
Style  face);

/*  ********* DIALOG HANDLER RECORDS LOADING ROUTINES *********  */


extern KeyEquivRecord DHMakeKeyEquiv(short  modifierkeys,
unsigned char  c);

extern KeyEquivRecord DHNoKeyEquiv(void);

extern void  DHAdvAddStaticString(DialogHandlerRecordPtr dhp,
short  itemId,
unsigned char *  str,    /* pascal string pointer */
boolean exitYesNo,
KeyEquivRecord keyEquiv,
boolean showClick,
CVoidProcPtr  userProc);

extern void  DHAdvAddStaticInteger(DialogHandlerRecordPtr dhp,
short  itemId,
short  value,
boolean exitYesNo,
KeyEquivRecord keyEquiv,
boolean showClick,
CVoidProcPtr  userProc);

extern void  DHAdvAddStaticLongInteger(DialogHandlerRecordPtr dhp,
short  itemId,
long  value,
boolean exitYesNo,
KeyEquivRecord keyEquiv,
boolean showClick,
CVoidProcPtr  userProc);

extern void  DHAdvAddStaticReal(DialogHandlerRecordPtr dhp,
short  itemId,
float  value,
DecForm  dForm,
boolean exitYesNo,
KeyEquivRecord keyEquiv,
boolean showClick,
CVoidProcPtr  userProc);

extern void  DHAdvAddEditString(DialogHandlerRecordPtr dhp,
short  itemId,
unsigned char *  str,    /* pascal string pointer */
CVoidProcPtr  userProc);

extern void  DHAdvAddEditInteger(DialogHandlerRecordPtr dhp,
short  itemId,
short  value,
short  lowest,
short  highest);

extern void  DHAdvAddEditLongInteger(DialogHandlerRecordPtr dhp,
short  itemId,
long  value,
long  lowest,
long  highest);

extern void  DHAdvAddEditReal(DialogHandlerRecordPtr dhp,
short  itemId,
float  value,
DecForm  dForm,
float  lowest,
float  highest);

extern void  DHAdvAddCheckBox(DialogHandlerRecordPtr dhp,
short  itemId,
boolean checked,
KeyEquivRecord keyEquiv,
CVoidProcPtr  userProc);

extern void  DHAdvAddPushButton(DialogHandlerRecordPtr dhp,
short  itemId,
boolean exitYesNo,
KeyEquivRecord keyEquiv,
CVoidProcPtr  userProc);

extern void  DHAddRadioSet(DialogHandlerRecordPtr dhp,
short  firstButtonOn,
RadioButtonSetPtr * setPtr);

extern void  DHAdvAddRadioButtonToSet(RadioButtonSetPtr * setPtr,
short  itemId,
KeyEquivRecord keyEquiv,
CVoidProcPtr  userProc);

extern void  DHAdvAddIcon(DialogHandlerRecordPtr dhp,
short  itemId,
short  ICONid,
boolean exitYesNo,
KeyEquivRecord keyEquiv,
boolean showClick,
CVoidProcPtr  userProc);

extern void  DHAdvAddPicture(DialogHandlerRecordPtr dhp,
short  itemId,
short  PICTid,
boolean exitYesNo,
KeyEquivRecord keyEquiv,
boolean showClick,
CVoidProcPtr  userProc);

extern void  DHAdvAddDisplayText(DialogHandlerRecordPtr dhp,
short  itemId,
short  TEXTid,
boolean fitHoriz,
CVoidProcPtr  userProc);

extern void  DHAdvAddPopUpMenu(DialogHandlerRecordPtr dhp,
short  MENUid,
short  top,
short  left,
short  firstChoice,
boolean useCheckMark,
CVoidProcPtr  userProc);

extern void  DHAdvAddPopUpMenuHandle(DialogHandlerRecordPtr dhp,
MenuHandle  menuHdl,
short  top,
short  left,
short  firstChoice,
boolean useCheckMark,
CVoidProcPtr  userProc);

extern void  DHAdvAddCounter(DialogHandlerRecordPtr dhp,
short  numberId,
short  arrowPictureId,
float  value,
float  increment,
float  lowest,
float  highest,
KeyEquivRecord upKeyEquiv,
KeyEquivRecord downKeyEquiv,
DecForm  dForm,
long  clickDelay,
CVoidProcPtr  userProc);

extern void  DHAdvAddPickList(DialogHandlerRecordPtr dhp,
short  itemId,
CVoidProcPtr  startProc,
SignedByte  selectionFlags,
CVoidProcPtr  mouseClickProc,
ProcPtr lClickLoopProc);

extern void  DHAddPickListString(ListHandle listH,
unsigned char *  str,    /* pascal string pointer */
short  index);

extern void  DHAdvAddPickListData (ListHandle listH,
Ptr  dataPointer,
short  dataLength,
short  index);

extern void  DHAddPickListData(ListHandle  listH,
Ptr dataPointer,
short  dataLength,
short  index);

extern MenuBarPtr DHAddPullDownMenuBar(DialogHandlerRecordPtr dhp,
short  top,
short  left);

extern void  DHAddPullDownMenu(MenuBarPtr * menuBar,
short  MENUid,
CVoidProcPtr  userProc);

extern void  DHAddPullDownMenuHandle(MenuBarPtr * menuBar,
MenuHandle  menuHdl,
CVoidProcPtr  userProc);

/*  ********* DIALOG HANDLER RECORDS LOADING ROUTINES -- THESE HAVE ADVANCED VERSIONS  *********  */

extern void  DHAddCounter(DialogHandlerRecordPtr dhp,
short  numberId,
short  arrowPictureId,
float  value,
float  increment);

/*  ********* DIALOG HANDLER RECORDS UNLOADING ROUTINES *********  */

extern void  DHDeleteStaticStrings(DialogHandlerRecordPtr dhp);

extern void  DHDeleteStaticIntegers(DialogHandlerRecordPtr dhp);

extern void  DHDeleteStaticLongIntegers(DialogHandlerRecordPtr dhp);

extern void  DHDeleteStaticReals(DialogHandlerRecordPtr dhp);

extern void  DHDeleteEditStrings(DialogHandlerRecordPtr dhp);

extern void  DHDeleteEditIntegers(DialogHandlerRecordPtr dhp);

extern void  DHDeleteEditLongIntegers(DialogHandlerRecordPtr dhp);

extern void  DHDeleteEditReals(DialogHandlerRecordPtr dhp);

extern void  DHDeleteCheckBoxes(DialogHandlerRecordPtr dhp);

extern void  DHDeletePushButtons(DialogHandlerRecordPtr dhp);

extern void  DHDeleteRadioButtons(DialogHandlerRecordPtr dhp);

extern void  DHDeleteIcons(DialogHandlerRecordPtr dhp);

extern void  DHDeletePictures(DialogHandlerRecordPtr dhp);

extern void  DHDeleteDisplayTexts(DialogHandlerRecordPtr dhp);

extern void  DHDeletePopUpMenus(DialogHandlerRecordPtr dhp);

extern void  DHDeletePullDownMenuBars(DialogHandlerRecordPtr dhp);

extern void  DHDeleteCounters(DialogHandlerRecordPtr dhp);

extern void  DHDeletePickLists(DialogHandlerRecordPtr dhp);

extern void  DHDeallocateRecord(DialogHandlerRecordPtr dhp);

extern void  DeleteTabToList (DialogHandlerRecordPtr dhp);

/*  ********* DIALOG HANDLER RECORDS RETRIEVAL ROUTINES *********  */


extern short DHWhichRadioButtonIsSet(RadioButtonSetPtr setPtr);

extern long DHWhichPopUpMenuChoice(DialogHandlerRecordPtr dhp,
short  MENUid);

extern long DHWhichPullDownMenuChoice(DialogHandlerRecordPtr dhp,
short  MENUid);

extern MenuHandle DHGetPopUpMenuHandle(DialogHandlerRecordPtr dhp,
short  MENUid);

extern MenuHandle DHGetPullDownMenuHandle(DialogHandlerRecordPtr dhp,
short  MENUid);

extern short DHGetMenuItem(long MenuResult);

extern short DHGetMenuId(long  MenuResult);

extern boolean DHIsBoxChecked(DialogHandlerRecordPtr dhp,
short  itemId);

extern boolean DHWasPushButtonPressed(DialogHandlerRecordPtr dhp,
short  itemId);

extern boolean DHWasStaticIntegerPressed(DialogHandlerRecordPtr dhp,
short  itemId);

extern boolean DHWasStaticLongIntegerPressed(DialogHandlerRecordPtr dhp,
short  itemId);

extern boolean DHWasStaticRealPressed(DialogHandlerRecordPtr dhp,
short  itemId);

extern boolean DHWasStaticStringPressed(DialogHandlerRecordPtr dhp,
short  itemId);

extern boolean DHWasIconPressed(DialogHandlerRecordPtr dhp,
short  itemId);

extern boolean DHWasPicturePressed(DialogHandlerRecordPtr dhp,
short  itemId);

extern void DHGetStaticString(DialogHandlerRecordPtr dhp,
short  itemId,
unsigned char *  str);    /* pascal string pointer */

extern short DHGetStaticInteger(DialogHandlerRecordPtr dhp,
short  itemId);

extern long DHGetStaticLongInteger(DialogHandlerRecordPtr dhp,
short  itemId);

extern float  DHGetStaticReal(DialogHandlerRecordPtr dhp,
short  itemId);

extern void DHGetEditString(DialogHandlerRecordPtr dhp,
short  itemId,
unsigned char *  str);    /* pascal string pointer */

extern short DHGetEditInteger(DialogHandlerRecordPtr dhp,
short  itemId);

extern long DHGetEditLongInteger(DialogHandlerRecordPtr dhp,
short  itemId);

extern float  DHGetEditReal(DialogHandlerRecordPtr dhp,
short  itemId);

extern float  DHGetCounterValue(DialogHandlerRecordPtr dhp,
short  itemId);

extern ListHandle DHGetPickListHandle(DialogHandlerRecordPtr dhp,
short  itemId);

extern boolean DHIsPickListItemSelected(ListHandle  listH,
short  index);

extern void  DHSystemProblem(short);


