/* ---------------------------------------------------------------------------- */
/* Copyright ©1987-1989 by Gary Gregory and Neil Ticktin.  All rights reserved. */
/* Version 1.0                                  */
/* ---------------------------------------------------------------------------- */

/* DHTypes.h */

#ifndef _DHTypes_
#define _DHTypes_

#ifdef THINK_C
#include "ControlMgr.h"
#include "DeskMgr.h"
#include "DeviceMgr.h"
#include "DialogMgr.h"
#include "EventMgr.h"
#include "FileMgr.h"
#include "HFS.h"
#include "IntlPkg.h"
#include "ListMgr.h"
#include "MacTypes.h"
#include "MemoryMgr.h"
#include "MenuMgr.h"
#include "OSUtil.h"
#include "PackageMgr.h"
#include "Quickdraw.h"
#include "ResourceMgr.h"
#include "ScrapMgr.h"
#include "SegmentLdr.h"
#include "StdFilePkg.h"
#include "TextEdit.h"
#include "ToolboxUtil.h"
#include "WindowMgr.h"
#include "asm.h"
#include "pascal.h"

#include <string.h>
#include <stdio.h>  /* sscanf */

/*
 * The following macro is used to make an index into a DialogHandler pick list.
 * A pick list Cell is normaly a record but in LSC 4.0 it is a long.
 * The row is stored in the hi-word, so we shift the row index by 16L since a long
 * is 32 bits in LSC 4.0.
 */

#define DH_PICKLIST_ROW(index) ((long)(index) << 16L)

#else

/*  --------------------------- MPW --------------------------------- */

/* The two following #defines are only in THINK C's MacTypes.h */

#define topLeft(r)  (((Point *) &(r))[0])
#define botRight(r)  (((Point *) &(r))[1])

/* in MPW C, the header names are different from THINK C */
#include <types.h>
#include <Windows.h>
#include <Events.h>
#include <Controls.h>
#include <Menus.h>
#include <Toolutils.h>
#include <OSutils.h>
#include <OSEvents.h>
#include <Memory.h>
#include <Resources.h>
#include <Scrap.h>
#include <Packages.h>
#include <Files.h>
#include <Palette.h>
#include <Errors.h>
#include <Fonts.h>
#include <textedit.h>
#include <dialogs.h>
#include <desk.h>
#include <segload.h>
#include <Picker.h>
#include <Lists.h>
#include <String.h>
#include <Strings.h>
#include <stdio.h>

/* in MPW C, some types are different from THINK C */
#define  DecForm      decform
typedef  char      SignedByte;

/* in MPW C, certain variables are not explicitly global, but are part
  of the "qd" structure */
#define  arrow    qd.arrow
#define  white    qd.white
#define  black    qd.black
#define  ltGray    qd.ltGray
#define  dkGray    qd.dkGray
#define  screenBits  qd.screenBits
#define  thePort    qd.thePort

/* in MPW C, certain constants have different names */
#define  mainScrn  mainScreen
#define  scrnActive  screenActive

/* in MPW C, the string conversion functions are named differently */
#define  CtoPstr  c2pstr
#define  PtoCstr  p2cstr

/* in MPW C, PI is not defined, use the function instead */
#define  PI  pi()

#endif

/*  -------------------- End of MPW --------------------------------- */

#include <SANE.h>

#define boolean Boolean
typedef void (*CVoidProcPtr) ();

/* Since it is much faster to have a macro do the work of the DH routine, we'll */
/* define it here for both the Engine and the programmer to use.  It returns    */
/* true if the character passed is a digit, else returns false.          */

#define DHISDIGIT(c) (((c >= '0') && (c <= '9')) ? true : false)
#define DHIstDigit DHISDIGIT

#define  DHINT2STR(value, newStr)    NumToString(value, newStr)
#define  DHInt2Str DHINT2STR

#define  DHLONGINT2STR(value, newStr)  NumToString(value, newStr)
#define  DHLongInt2Str DHLONGINT2STR

/* ----------------------------------------------------------------------------------- */
/* --  PASCAL DELETE LAST CHARACTER                        -- */
/* --  DESCRIPTION:                                -- */
/* --  The routine deletes the last character in a pascal string.          -- */
/* --                                        -- */
/* --  PARAMETERS:                                  -- */
/* --  The pointer to the string to be changed.                  -- */
/* ----------------------------------------------------------------------------------- */

#define DHPDELETELASTCHAR(str)  ((*str)--)
#define DHPDeleteLastChar  DHPDELETELASTCHAR

/* ---------------------------------  DHArrowCursorKey    --------------------------- */
/*                                                */
/* Parameters and return type: (code : LONGINT) : BOOLEAN                   */
/* This routine returns a BOOLEAN true if the code passed in is an arrow key, up, down,   */
/* right or left.  false id returned otherwise.                        */
/*                                                */
/* ---------------------------------------------------------------------------------------- */

#define DHARROWCURSORKEY(code) \
  (((code == ArrowUp) || (code == ArrowDown) || \
    (code == ArrowLeft) || (code == ArrowRight)))
#define DHArrowCursorKey DHARROWCURSORKEY

#define pEmptyStr ((unsigned char *)"\p")

#define true 1
#define false 0


          /*      Don't define NULL it is defined in OOP, Global.h as 0L.
          #ifndef NULL
          #define NULL    ((void *) 0)
          #endif
          */


enum { EmptyStyleSet = (Style)0 };

/* For programming tools */

enum { NoEditFields = -1 };      /* There are no edit items in the dialog box */
enum { ArrowUp  = 0x1E };      /* The up arrow character */
enum { ArrowDown  = 0x1F };    /* The down arrow character */
enum { ArrowLeft  = 0x1C };    /* The left arrow character */
enum { ArrowRight  = 0x1D };    /* The right arrow character */

/* Internal program constants */

/* The following hexadecimal constants hexadecimal are used to check Cut, Copy and Paste */

enum { CAP_XHEX  = 0x58 };        /* 'X' */
enum { LO_XHEX  = 0x78 };        /* 'x' */
enum { CAP_CHEX  = 0x43 };        /* 'C' */
enum { LO_CHEX  = 0x63 };        /* 'c' */
enum { CAP_VHEX  = 0x56 };        /* 'V' */
enum { LO_VHEX  = 0x76 };        /* 'v' */
enum { ZEROx  = 0x30 };        /* '0' */
enum { NINEx  = 0x39 };      /* '9' */
enum { TAB    = 0x09 };      /* The tab character */
enum { MINUS  = 0x2D };      /* '-' */
enum { PLUS    = 0x2B };      /* '+' */
enum { BACKSPACE= 0x08 };      /* The backspace character */
enum { SMALLE  = 0x65 };      /* 'e' */
enum { BIGE    = 0x45 };      /* 'E' */

enum { charMINUS  = '-' };
enum { charPLUS  = '+' };
enum { ENTERKEY  = 0x03 };      /* The ENTER key character */
enum { RETURNKEY  = 0x0D };    /* The RETURN key character */
enum { MAXDIGITS  = 7 };      /* max digits in DecForm without losing accuracy */

enum { Up      = 1 };      /* Indicates that a counter was pressed up */
enum { Down    = -1 };       /* Indicates that a counter was pressed down */
enum { CheckBox  = 1 };        /* Indicates that a check box is checked */
enum { UnCheckBox  = 0 };      /* Indicates that a check box is unchecked */
enum { RadioOn  = 1 };        /* Indicates that a radio button is on */
enum { RadioOff  = 0 };        /* Indicates that a radio button is off */

/* Error resources */

enum { ERRSTRID  = 302 };      /* Error string resources  */
enum { ALERTID  = 301 };      /* Alert box resource id  */
enum { ALERT_ERR  = -1 };      /* Value returned by StopAlert if a problem occurs */

/* Error message numbers, offsets in the STR# resource */

enum { ErrIntegerRange  = 1 };    /* INTEGER out of range string number */
enum { ErrLongIntRange  = 2 };    /* Long INTEGER out of range string number */
enum { ErrRealRange    = 3 };    /* Real out of range string number */
enum { ErrIntegerChar    = 4 };  /* Bad character for an edit INTEGER string number */
enum { ErrLongIntChar    = 5 };  /* Bad character for an edit long INTEGER string number */
enum { ErrRealChar    = 6 };    /* Bad character for an edit real string number */
enum { ErrReturnEnterTEScrap= 7 };  /* No RETURN or ENTER in TEScrap string number */
enum { ErrTEScrapLength  = 8 };    /* Bad length in TEScrap string number */
enum { ErrIntegerPaste  = 9 };    /* Error pasting in an INTEGER */
enum { ErrLongIntPaste  = 10 };    /* Error pasting in a long INTEGER */
enum { ErrRealPaste    = 11 };    /* Error pasting in a real */
enum { ErrPictResource  = 12 };    /* Error with picture resource */
enum { ErrIconResource  = 13 };    /* Error with icon resource */
enum { ErrStringListResource= 14 };  /* Error with string list resource */
enum { ErrPopUpResource  = 15 };    /* Error with pop up menu resource */
enum { ErrPullDownResource  = 16 };  /* Error with pull down menu resource */
enum { ErrCounterNumber  = 17 };    /* Error with counter number item resource */
enum { ErrCounterPicture  = 18 };  /* Error with counter picture resource */
enum { ErrPickList    = 19 };    /* Error with pick list resource */
enum { ErrNoDlog      = 20 };  /* Error with dialog resource */
enum { ErrOldROM      = 21 };  /* ROM version is too old for certain features (popup) */
enum { ANDSTR        = 22 };  /* The 'and' string for range errors */
enum { RANGESTR      = 23 };    /* The 'range' string for range errors */
enum { ErrOutOfMemory    = 24 };  /* NewPtr returned nil in the front end */

/* For everybody, can be used in the front-end calls. */

/* Counter delays */

enum { NoDelay  = 0 };
enum { VeryShortDelay = 5 };
enum { ShortDelay  = 10 };
enum { MediumDelay  = 15 };
enum { LongDelay  = 20 };
enum { VeryLongDelay = 25 };

/* For various dialog items */

enum { ShowClick  = true };    /* Inverse rectangle for clicking on icons is on */
enum { DontShowClick = false };    /* Inverse rectangle for clicking on icons is off */
enum { UseCheckMark = true };    /* Use a check mark for popup menus */
enum { NoCheckMark  = false };    /* Do not use a check mark for popup menus */
enum { Exit = true };        /* Exit dialog box when item is hit */
enum { NoExit  = false };      /* Do not exit dialog box when item is hit */

enum { CCPOn  = true };      /* Cut, Copy, Paste enabled */
enum { CCPOff  = false };      /* Cut, Copy, Paste disabled */

enum { NoItemHit  = -1 };      /* No item hit in dialog */
enum { UpdateItemHit = -2 };    /* Pass to CallProcedure as the item hit for an update */
enum { StartupItemHit = -3 };    /* Pass to CallProcedure as the item hit for a startup */

enum { NoUpdateUserItem = -1 };    /* No update user item for DLOG box */
enum { NoCancelItem = -4 };      /* No cancel item for DLOG box */
enum { NoSelectedItem = -5 };    /* No selected item for DLOG box */
enum { DefaultItem  = true };    /* There is a default item in the dialog */
enum { NoDefaultItem = false };    /* No default item in the dialog */

enum { Checked  = true };      /* A check box is checked */
enum { NotChecked  = false };    /* A check box is not checked */
enum { CenteringOn  = true };    /* Center the dialog */
enum { CenteringOff = false };    /* Do not center the dialog */
enum { SaveCenteringOn = true };   /* Save centering information */
enum { SaveCenteringOff = false };  /* Do not save centering information */
enum { FitHorizontally = true };   /* Fit text in a display text rectangle, wrap line around */
enum { DontFitHorizontally = false };  /* Do not fit text in a display text rectangle */
enum { NoMenuChoice = 0 };      /* No menu choice has been made */
enum { MenuNotFound = -1 };      /* A menu was not found */
enum { UseDITLResource = -32768 };  /* Use the DILT resource for a dialog item */

/* Near the mouse pointer constants */

enum { NearOff  = -1 };        /* Turn it off */
enum { NearVCenter  = -2 };      /* Bring dialog so that mouse is in the vertical center */
enum { NearHCenter  = -3 };      /* Bring dialog so that mouse is in the horizontal center */
enum { NearTop  = -4 };        /* Bring dialog so that mouse is at the top */
enum { NearBottom  = -5 };      /* Bring dialog so that mouse is at the bottom */
enum { NearLeft  = -6 };        /* Bring dialog so that mouse is at the left */
enum { NearRight  = -7 };      /* Bring dialog so that mouse is at the right */

enum { Pressed  = true };      /* A dialog item was pressed */
enum { NotPressed  = false };    /* A dialog item was not pressed */

/* For key equivalence definition use. Parameters to DHMakeKeyEquiv */

enum { NORMAL  = 0 };        /* A simple keystroke */
enum { COMMAND  = cmdKey };      /* A Command key combination */
enum { SHIFT  = shiftKey };    /* A Shift key combination */

/* Numeric constants */

        /*    Don't define these they are defined in OOP, Global.h    */
        /*enum { MAXINT    = 32767 };      /* The smallest integer */
        /*enum { MININT    = -MAXINT - 1 };  /* The smallest integer */


/*
 * enum type is int !  Therefore, the following must be #defines
 */

#define MAXLONGINT  2147483647L      /* The largest long integer */
#define MINLONGINT  (-MAXLONGINT - 1)  /* The smallest long integer */

#define MAXREAL  (3.4E38)        /* The largest real */
#define MINREAL  (-MAXREAL)        /* The smallest real */


#define EMPTYSTRING pEmptyStr

enum { NULLCHAR = 0x00 };


/*
 * Pick List enums
 */

enum { ScrollBarWidth = 15 };

/*-----------------------------------------------------------------------------------*/
/* define record structures                               */
/*-----------------------------------------------------------------------------------*/


/*  Never used by user. For internals only  */

typedef struct comvarsType {    /* Common variables */
  boolean  okKeyEquiv;       /* Has a kay equivalent been pressed  */
  long  charCode;        /* Hex Code of key pressed  */
  short  charModifiers;      /* Modifier flag when key pressed  */
  boolean hiliteButton;      /* Hilite the itemHit push button  */
} comvarsType;

typedef struct PEIRecord *pEIptr;
typedef struct PEIRecord {
  short  itemId;          /* Id number of the item in DLOG box */
  pEIptr  next, before;      /* Doubly linked circular list, (applause, applause) */
} PEIRecord;


/* Record definition for a key equivalent */

typedef struct KeyEquivRecord {
  long  KEchar;          /* The character code */
  short  KEmodifiers;      /* The modifier keys; defined above */
} KeyEquivRecord;

typedef struct CheckBoxRecord *CheckBoxPtr;
typedef struct CheckBoxRecord {
  short  itemId;          /* Id number of the item in DLOG box */
  KeyEquivRecord  keyEquiv;    /* Key equivalent */
  boolean checked;        /* Was it checked or not */
  CVoidProcPtr  userHook;    /* Pointer to procedure to be called when this item is hit */
  CheckBoxPtr  next;        /* Pointer to next item in list */
} CheckBoxRecord;

typedef struct CounterRecord *CounterPtr;
typedef struct CounterRecord {
  short  numberId;        /* Item id of the static text item for the number */
  short  arrowPictureId;      /* Item id of the static text item for the picture */
  float  value;          /* Startup value */
  float  increment;        /* The counter's increment value */
  float  lowest;          /* Lowest legal value */
  float  highest;        /* Highest legal value */
  DecForm form;          /* Display attributes: digits and form */
  long  clickDelay;        /* Wait for this long before changing counter */
  KeyEquivRecord upKeyEquiv;    /* Increment key equivalent */
  KeyEquivRecord downKeyEquiv;  /* Decrement key equivalent */
  CVoidProcPtr  userProc;    /* Pointer to procedure to be called when this item is hit */
  CounterPtr  next;        /* Pointer to next item in list */
} CounterRecord;

typedef struct DisplayTextRecord *DisplayTextPtr;
typedef struct DisplayTextRecord {
  short  itemId;          /* Id number of the user item in DLOG box */
  short  TEXTid;          /* Resource id of TEXT to display, not in the DITL */
  TEHandle  textH;        /* The TEHandle for the TEXT read in */
  ControlHandle vscroll, hscroll; /* For vertical and horizontal scroll bars */
  short  horOffset, verOffset;  /* Internal. Used to calculated next scroll jump */
  boolean fitHoriz;        /* To fit horizontally, must use word wrap mode */
  CVoidProcPtr  userHook;    /* Pointer to procedure to be called when this item is hit */
  DisplayTextPtr  next;      /* Pointer to next item in list */
} DisplayTextRecord;

typedef struct EditIntegerRecord *EditIntegerPtr;  /* EditIntegerRecord */
typedef struct EditIntegerRecord {
  short  itemId;          /* Id number of the item in DLOG box */
  short  value;          /* INTEGER to be inserted */
  short  lowest;          /* Lowest legal value */
  short  highest;        /* Highest legal value */
  EditIntegerPtr  next;      /* Pointer to next item in list */
} EditIntegerRecord;

typedef struct EditLongIntegerRecord *EditLongIntegerPtr;  /* EditLongIntegerRecord */
typedef struct EditLongIntegerRecord {
  short  itemId;          /* Id number of the item in DLOG box */
  long  value;          /* Long INTEGER to be inserted */
  long  lowest;          /* Lowest legal value */
  long  highest;        /* Highest legal value */
  EditLongIntegerPtr  next;    /* Pointer to next item in list */
} EditLongIntegerRecord;

typedef struct EditRealRecord *EditRealPtr; /* EditRealRecord */
typedef struct EditRealRecord {
  short  itemId;          /* Id number of the item in DLOG box */
  float  value;          /* Real to be inserted */
  float  lowest;          /* Lowest legal value */
  float  highest;        /* Highest legal value */
  DecForm form;          /* Decimal form (consists of style and digits field) */
  EditRealPtr  next;        /* Pointer to next item in list */
} EditRealRecord;

typedef struct EditStringRecord *EditStringPtr; /* EditStringRecord */
typedef struct EditStringRecord {
  short  itemId;          /* Id number of the item in DLOG box */
  Str255  str;          /* String to be inserted */
  CVoidProcPtr  userProc;    /* Pointer to procedure to be called when this item is hit */
  EditStringPtr  next;      /* Pointer to next item in list */
} EditStringRecord;

typedef struct IconRecord *IconPtr;
typedef struct IconRecord {
  short  itemId;          /* Id number of the item in DLOG box */
  short  ICONid;          /* Resource id for the ICON */
  Handle  iconHandle;        /* Icon handle */
  KeyEquivRecord  keyEquiv;    /* Key equivalent */
  boolean  pressed;        /* Was it pressed or not */
  boolean  exit;          /* Exit when pressed or not */
  boolean  showClick;        /* Inverse item when item is pressed or not */
  CVoidProcPtr  userHook;    /* Pointer to procedure to be called when this item is hit */
  IconPtr  next;          /* Pointer to next item in list */
} IconRecord;

typedef struct PickListRecord *PickListPtr;
typedef struct PickListRecord {
  short  itemId;          /* Id number of the item in DLOG box */
  ListHandle  listH;        /* The List Manager handle */
  SignedByte  selectionFlags;    /* Pick list selection flag */
  CVoidProcPtr  startProc;    /* Pointer to procedure to be called to define pick list data */
  CVoidProcPtr  mouseClickProc; /* Pointer to procedure to be called when this item is hit */
  ProcPtr lClickLoopProc;      /* Pointer to procedure to be called from internal loop */
#ifdef THINK_C
  long  lastCell;        /* Last cell clicked in. LLastClick returns a long in LSC */
#else
  Cell  lastCell;        /* Last cell clicked in. LLastClick returns a Cell in MPW */
#endif
  long  lastClickTime;      /* Time last cell was clicked in */
  PickListPtr  next;        /* Pointer to next item in list */
} PickListRecord;

typedef struct PictureRecord *PicturePtr;
typedef struct PictureRecord {
  short  itemId;          /* Id number of the item in DLOG box */
  short  PICTid;          /* Resource id of the PICTure */
  PicHandle  pictureHandle;    /* The picture's handle */
  KeyEquivRecord  keyEquiv;    /* Key equivalent */
  boolean  pressed;        /* Was it pressed or not */
  boolean  exit;          /* Exit when pressed or not */
  boolean  showClick;        /* Inverse item when item is pressed or not */
  CVoidProcPtr  userHook;    /* Pointer to procedure to be called when this item is hit */
  PicturePtr  next;        /* Pointer to next item in list */
} PictureRecord;

typedef struct PopUpMenuRecord *PopUpMenuPtr;
typedef struct PopUpMenuRecord {
  short  MENUid;          /* The resource menu id */
  Rect  titleBox;        /* Internal */
  Rect  box;          /* Internal */
  MenuHandle  popUpMenuH;      /* The menu handle  */
  long  result;          /* Actual menu result */
  short  lastItemSelected;    /* Last item selected from the menu */
  boolean useCheckMark;      /* Use a check mark or not */
  CVoidProcPtr  userProc;    /* Pointer to procedure to be called when this item is hit */
  PopUpMenuPtr  next;      /* Pointer to next item in list */
} PopUpMenuRecord;

typedef struct PullDownMenuRecord *PullDownMenuPtr;
typedef struct PullDownMenuRecord {
  short  MENUid;          /* Resource id of the menu */
  MenuHandle  pullDownHandle;    /* Actual menu */
  long  result;          /* Menu result */
  Rect  textRect;        /* The menu title's rectangle */
  CVoidProcPtr  userProc;    /* Pointer to procedure to be called when this item is hit */
  PullDownMenuPtr  next;      /* Pointer to next item in list */
} PullDownMenuRecord;

typedef struct MenuBarRecord *MenuBarPtr;
typedef struct MenuBarRecord {
  short  top, left;        /* Top left coordinates of menu bar local to dialog */
  Rect  menuRect;        /* The menu's recangle box */
  PullDownMenuPtr  pullDowns;    /* Pointer to a list of menus for that menu bar */
  MenuBarPtr  next;        /* Pointer to next menu bar item in list */
} MenuBarRecord;

typedef struct PushButtonRecord *PushButtonPtr;
typedef struct PushButtonRecord {
  short  itemId;          /* Id number of the item in DLOG box */
  KeyEquivRecord  keyEquiv;    /* Key equivalent */
  boolean  pressed;        /* Was it pressed or not */
  CVoidProcPtr  userHook;    /* Pointer to procedure to be called when this item is hit */
  boolean  exit;          /* Exit when pressed or not */
  PushButtonPtr  next;      /* Pointer to next item in list */
} PushButtonRecord;

typedef struct RadioButtonRecord *RadioButtonPtr;
typedef struct RadioButtonRecord {
  short  itemId;          /* Id number of the item in DLOG box */
  KeyEquivRecord  keyEquiv;    /* Key equivalent */
  CVoidProcPtr  userHook;    /* Pointer to procedure to be called when this item is hit */
  RadioButtonPtr  next;      /* Pointer to next item in list */
} RadioButtonRecord;

typedef struct RadioButtonSetRecord *RadioButtonSetPtr;
typedef struct RadioButtonSetRecord {
  RadioButtonPtr rbuts;      /* Pointer to a set of radio buttons */
  short  rbuttonpressed;      /* Which radio button is on */
  RadioButtonSetPtr nextset;    /* Pointer to next item in list */
} RadioButtonSetRecord;

typedef struct StaticIntegerRecord *StaticIntegerPtr;  /* StaticIntegerRecord */
typedef struct StaticIntegerRecord {
  short  itemId;          /* Id number of the item in DLOG box */
  short  value;          /* INTEGER to be inserted */
  KeyEquivRecord  keyEquiv;    /* Key equivalent */
  boolean  pressed;        /* was it pressed or not */
  boolean  exit;          /* Exit when pressed or not */
  boolean  showClick;        /* Inverse the item rectangle or not */
  CVoidProcPtr  userHook;    /* Pointer to procedure to be called when this item is hit */
  StaticIntegerPtr  next;    /* Pointer to next item in list */
} StaticIntegerRecord;

typedef struct StaticLongIntegerRecord *StaticLongIntegerPtr;  /* StaticLongIntegerRecord */
typedef struct StaticLongIntegerRecord {
  short  itemId;          /* Id number of the item in DLOG box */
  long  value;          /* Long INTEGER to be inserted */
  KeyEquivRecord  keyEquiv;    /* Key equivalent */
  boolean  pressed;        /* Was it pressed or not */
  boolean  exit;          /* Exit when pressed or not */
  boolean  showClick;        /* Inverse the item rectangle or not */
  CVoidProcPtr  userHook;    /* Pointer to procedure to be called when this item is hit */
  StaticLongIntegerPtr  next;  /* Pointer to next item in list */
} StaticLongIntegerRecord;

typedef struct StaticRealRecord *StaticRealPtr; /* StaticRealRecord */
typedef struct StaticRealRecord {
  short  itemId;          /* Id number of the item in DLOG box */
  float  value;          /* Real to be inserted */
  DecForm form;          /* Decimal form (consists of style and digits field) */
  KeyEquivRecord  keyEquiv;    /* Key equivalent */
  boolean  pressed;        /* Was it pressed or not */
  boolean  exit;          /* Exit when pressed or not */
  boolean  showClick;        /* Inverse the item rectangle or not */
  CVoidProcPtr  userHook;    /* Pointer to procedure to be called when this item is hit */
  StaticRealPtr  next;      /* Pointer to next item in list */
} StaticRealRecord;

typedef struct StaticStringRecord *StaticStringPtr; /* StaticStringRecord */
typedef struct StaticStringRecord {
  short  itemId;          /* Id number of the item in DLOG box */
  Str255  str;          /* String to be inserted */
  KeyEquivRecord  keyEquiv;    /* Key equivalent */
  boolean  pressed;        /* Was it pressed or not */
  boolean  exit;          /* Exit when pressed or not */
  boolean  showClick;        /* Inverse the item rectangle or not */
  CVoidProcPtr  userHook;    /* Pointer to procedure to be called when this item is hit */
  StaticStringPtr  next;      /* Pointer to next item in list */
} StaticStringRecord;

typedef struct DialogHandlerRecord *DialogHandlerRecordPtr;
typedef struct DialogHandlerRecord {
  short  DLOGId;          /* Id number for dialog definition */
  PushButtonPtr  buttons;    /* Pointer to button list */
  RadioButtonSetPtr  radios;    /* Pointer to radio button set list */
  CheckBoxPtr  checks;        /* Pointer to check button list */
  StaticStringPtr  ssp;      /* Pointer to static string list */
  StaticIntegerPtr  sip;    /* Pointer to static INTEGER list */
  StaticLongIntegerPtr  slip;  /* Pointer to static INTEGER list */
  StaticRealPtr  srp;      /* Pointer to static Real list */
  EditStringPtr  esp;      /* Pointer to edit string list */
  EditIntegerPtr  eip;      /* Pointer to edit INTEGER list */
  EditLongIntegerPtr  elip;    /* Pointer to edit INTEGER list */
  EditRealPtr  erp;        /* Pointer to edit Real list */
  IconPtr  icons;          /* Pointer to icon list */
  PicturePtr  pictures;      /* Pointer to picture list */
  DisplayTextPtr  displayTexts;  /* Pointer to display text list */
  CounterPtr  counters;      /* Pointer to counter list */
  PopUpMenuPtr  popUps;      /* Pointer to popup list */
  MenuBarPtr  menuBars;      /* Pointer to pull down menu bar list */
  PickListPtr  pickLists;       /* Pointer to pick list list */
  short  cancelButton;      /* Optional */
  short  selectedItem;      /* Optional */
  boolean  cutCopyPaste;      /* Default is FALSE */
  boolean  alertUser;        /* Default is TRUE */
  boolean  beepOnly;        /* Default is FALSE */
  short  fontNum;        /* Font for the dialog */
  short  fontSize;        /* Size of the font for the dialog */
  Style  fontFace;        /* Style of the font for the dialog, this is a SET */
  boolean  callDMD;        /* Used internally. */
  boolean  timeToExit;        /* Used internally. Default is FALSE */
  short  previousEditItem;    /* Used internally. */
  pEIptr  previousEditItemPtr;  /* Used internally. */
  boolean  lastAutoWasKE;      /* The last event was auto key event with a KE. Used internally. */
  boolean  defaultItem;      /* Optional */
  CVoidProcPtr  updateProcPtr;  /* Pointer to proc to be called when an update event occurs */
  short  updateUserItem;     /* Id num of update user item in dlog list, may be shared by Default button and updateProcPtr */
  CVoidProcPtr  startupProcedure;  /* Pointer to proc to be called right before ModalDialog */
  short  verNearMouse;      /* Near the mouse pointe vertical coordinates */
  short  horNearMouse;      /* Near the mouse pointer horizontal coordinates */
  Handle  progItem1;        /* User hook for user defined item */
  long  progItem2;        /* User hook for user defined item */
  Handle  rsrv;          /* Reserved for future use */
} DialogHandlerRecord;

#endif

