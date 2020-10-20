
/*
 *  MacProto.h
 *
 *  Prototypes for ROM Routines
 *  by Stew Rubenstein and Darrell LeBlanc
 *  Copyright (c) 1989 Symantec Corporation.
 *
 */

 /* These prototypes are intended to be used with version 4.0 of THINK C. */
/*
  This is a complete list of Prototypes for Inside Macintosh Vol. I - V.

  Note that prototypes for ROM routines are not required even if
  "Prototypes Required" is turned on, but by including this header,
  prototype checking will be enforced.

  TrapType has been changed to an short type. ProcPtr is #defined to be a void *,
  except for GetCtlAction which *returns* a function pointer.

  SPECIAL NOTE: about  LLastClick and TEGetPoint functions...
  In C, it is not possible to do data structure assignment when the ROMs return
  a structure instead of a pointer to a structure (this is legal in Pascal). This means
  that special workarounds have to be used for LLastClick and TEGetPoint which
  both return structures.

  for LLastClick:
  *(long *)&lastCell = LLastClick(lHandle);    * LLastClick is prototyped to return a long *

  for TEGetPoint:
  *(long *)&myPoint = TEGetPoint(offset,hTE);  * TEGetPoint is prototyped to return a long *

  TWO COMMON ERROR MESSAGES...
   1) illegal function prototype - probably missing header file to declare
       data types for one or more parameters.
   2) invalid redeclaration of ... - all declarations, definitions and prototypes
       must match including return types and parameter types.

   Please report any bugs to:

   Darrell LeBlanc
   Symantec Corp.
   135 South Rd.
   Bedford, MA 01730
   (CIS #76666,2005)

*/

#ifndef _MacProto_
#define _MacProto_

#ifndef _MacTypes_
#include <MacTypes.h>
#endif  /*_MacTypes_*/

#define ProcPtr void*

#ifdef _DeskBus_  /* AppleDesktopBus [ADB] */
pascal OSErr ADBOp(void * data, ProcPtr compRout, void * buffer, short commandNum);
pascal void ADBReInit(void);
pascal short CountADBs(void);
pascal OSErr GetADBInfo(ADBDataBlock *info, ADBAddress ADBAddr);
pascal ADBAddress GetIndADB(ADBDataBlock *info, short devTableIndex);
pascal OSErr SetADBInfo(ADBSetInfoBlock *info, ADBAddress ADBAddr);
#endif  /*_DeskBus_*/

#ifdef _AppleTalk_  /* AppleTalk Manager [AT] */
pascal OSErr AFPCommand(XPPParmBlkPtr xParamBlock, Boolean async);
pascal OSErr ASPAbortOS(XPPParmBlkPtr xParamBlock, Boolean async);
pascal OSErr ASPCloseAll(XPPParmBlkPtr xParamBlock, Boolean async);
pascal OSErr ASPCloseSession(XPPParmBlkPtr xParamBlock, Boolean async);
pascal OSErr ASPGetParms(XPPParmBlkPtr xParamBlock, Boolean async);
pascal OSErr ASPGetStatus(XPPParmBlkPtr xParamBlock, Boolean async);
pascal OSErr ASPOpenSession(XPPParmBlkPtr xParamBlock, Boolean async);
pascal OSErr ASPUserCommand(XPPParmBlkPtr xParamBlock, Boolean async);
pascal OSErr ASPUserWrite(XPPParmBlkPtr xParamBlock, Boolean async);
pascal OSErr ATPAddRsp(ABRecHandle abRecord);
pascal OSErr ATPCloseSocket(short atpSocket);
pascal OSErr ATPGetRequest(ABRecHandle abRecord, Boolean async);
pascal OSErr ATPLoad(void);
pascal OSErr ATPOpenSocket(AddrBlock addrRcvd, short *atpSocket);
pascal OSErr ATPReqCancel(ABRecHandle abRecord, Boolean async);
pascal OSErr ATPRequest(ABRecHandle abRecord, Boolean async);
pascal OSErr ATPResponse(ABRecHandle abRecord, Boolean async);
pascal OSErr ATPRspCancel(ABRecHandle abRecord, Boolean async);
pascal OSErr ATPSndRequest(ABRecHandle abRecord, Boolean async);
pascal OSErr ATPSndRsp(ABRecHandle abRecord, Boolean async);
pascal OSErr ATPUnload(void);
pascal short BuildBDS(void * buffPtr, void * bdsPtr, short buffSize);
pascal void  BuildDDPwds(void * wdsPtr, void * headerPtr, void * dataPtr, AddrBlock destAddress, short DDPType, short dataLen);
pascal void  BuildLAPwds(void * wdsPtr, void * dataPtr, short destHost, short protoType, short frameLen);
pascal OSErr DDPCloseSocket(short theSocket);
pascal OSErr DDPOpenSocket(short *theSocket, void * sktListener);
pascal OSErr DDPRdCancel(ABRecHandle abRecord);
pascal OSErr DDPRead(ABRecHandle abRecord, Boolean retCksumErrs, Boolean async);
pascal OSErr DDPWrite(ABRecHandle abRecord, Boolean doChecksum, Boolean async);
pascal short   GetBridgeAddress(void);
pascal OSErr GetNodeAddress(short *myNode, short *myNet);
pascal Boolean IsATPOpen(void);
pascal Boolean IsMPPOpen(void);
pascal OSErr LAPCloseProtocol(ABByte *theLAPType);
pascal OSErr LAPOpenProtocol(ABByte *theLAPType, void * protoPtr);
pascal OSErr LAPRdCancel(ABRecHandle abRecord);
pascal OSErr LAPRead(ABRecHandle abRecord, Boolean async);
pascal OSErr LAPWrite(ABRecHandle abRecord, Boolean async);
pascal OSErr MPPClose(void);
pascal OSErr MPPOpen(void);
pascal OSErr NBPConfirm(ABRecHandle abRecord, Boolean async);
pascal OSErr NBPExtract(void * theBuffer, short numInBuf, short whichOne, EntityName *abEntity, AddrBlock *address);
pascal OSErr NBPExtract(void * theBuffer, short numInBuf, short WhichOne, EntityName *abEntity, AddrBlock *address);
pascal OSErr NBPLoad(void);
pascal OSErr NBPLookup(ABRecHandle abRecord, Boolean async);
pascal OSErr NBPRegister(ABRecHandle abRecord, Boolean async);
pascal OSErr NBPRemove(EntityPtr abEntity);
pascal void  NBPSetEntity(void * buffer, Str32 nbpObject, nbpType Str32, Str32 nbpZone);
pascal void  NBPSetNTE(void * ntePtr, Str32 nbpObject, Str32 nbpType, Str32 nbpZone, short Socket);
pascal OSErr NBPUnload(void);
pascal OSErr PAddResponse(MPPPBPtr thePBptr, Boolean async);
pascal OSErr PAttachPH(MPPPBPtr thePBptr, Boolean async);
pascal OSErr PCloseATPSkt(MPPPBPtr thePBptr, Boolean async);
pascal OSErr PCloseSkt(MPPPBPtr thePBptr, Boolean async);
pascal OSErr PConfirmName(MPPPBPtr thePBptr, Boolean async);
pascal OSErr PDetachPH(MPPPBPtr thePBptr, Boolean async);
pascal OSErr PGetRequest(MPPPBPtr thePBptr, Boolean async);
pascal OSErr PKillGetReq(ATPPBPtr thePBptr, Boolean async);
pascal OSErr PKillGetReq(MPPPBPtr thePBptr, Boolean async);
pascal OSErr PKillNBP(ATPPBPtr thePBptr, Boolean async);
pascal OSErr PKillNBP(MPPPBPtr thePBptr, Boolean async);
pascal OSErr PKillSendReq(ATPPBPtr thePBptr, Boolean async);
pascal OSErr PKillSendReq(MPPPBPtr thePBptr, Boolean async);
pascal OSErr PLookupName(MPPPBPtr thePBptr, Boolean async);
pascal OSErr PNSendRequest(ATPBPtr thePBptr, Boolean async);
pascal OSErr PNSendRequest(MPPPBPtr thePBptr, Boolean async);
pascal OSErr POpenATPSkt(MPPPBPtr thePBptr, Boolean async);
pascal OSErr POpenSkt(MPPPBPtr thePBptr, Boolean async);
pascal OSErr PRegisterName(MPPPBPtr thePBptr, Boolean async);
pascal OSErr PRelTCB(MPPPBPtr thePBptr, Boolean async);
pascal OSErr PRemoveName(MPPPBPtr thePBptr, Boolean async);
pascal OSErr PSendRequest(MPPPBPtr thePBptr, Boolean async);
pascal OSErr PSendResponse(MPPPBPtr thePBptr, Boolean async);
pascal OSErr PSetSelfSend(MPPPBPtr thePBptr, Boolean async);
pascal OSErr PSetSelfSend(MPPPBPtr thePBptr, Boolean async);
pascal OSErr PWriteDDP(MPPPBPtr thePBptr, Boolean async);
pascal OSErr PWriteLAP(MPPPBPtr thePBptr, Boolean async);
#endif  /*_AppleTalk_*/

#ifdef _Color_  /* Color Manager [CM] */
pascal void AddComp(ProcPtr compProc);
pascal void AddSearch(ProcPtr searchProc);
pascal long Color2Index(RGBColor *rgb);
pascal void DelComp(ProcPtr compProc);
pascal void DelSearch(ProcPtr searchProc);
pascal long GetCTSeed(void);
pascal void GetSubTable(CTabHandle myColors, short iTabRes, CTabHandle targetTbl);
pascal void Index2Color(long index, RGBColor *rgb);
pascal void InvertColor(RGBColor *theColor);
pascal void MakeITable(CTabHandle colorTab, ITabHandle inverseTab, short res);
pascal void ProtectEntry(short index, Boolean protect);
pascal short QDError(void);
pascal Boolean RealColor(RGBColor *color);
pascal void ReserveEntry(short index, Boolean reserve);
pascal void RestoreEntries(CTabHandle srcTable, CTabHandle dstTable, ReqListRec *selection);
pascal void SaveEntries(CTabHandle srcTable, CTabHandle resultTable, ReqListRec *selection);
pascal void SetClientID(short id);
pascal void SetEntries(short start, short count, CSpecArray aTable);
#endif  /*_Color_*/

#ifdef _Color_    /* Color Picker Package */
pascal void CMY2RGB(CMYColor *cColor, RGBColor *rColor);
pascal SmallFract Fix2SmallFract(Fixed f);
pascal Boolean GetColor(Point where, void *prompt, RGBColor *inColor, RGBColor *outColor);
pascal void HSL2RGB(HSLColor *hColor, HSLColor *rColor);
pascal void HSV2RGB(HSVColor *hColor, RGBColor *rColor);
pascal void RGB2CMY(RGBColor *rColor, CMYColor *cColor);
pascal void RGB2HSL(RGBColor *rColor, HSLColor *hColor);
pascal void RGB2HSV(RGBColor *rColor, HSVColor *hColor);
pascal Fixed SmallFract2Fix(SmallFract s);
#endif  /*_Color_*/

#ifdef _Color_  /* ColorQuickDraw IMV */
pascal void AllocCursor(void);
pascal void BackPixPat(PixPatHandle ppat);
pascal void CalcCMask(BitMap *srcBits, BitMap *dstBits, Rect *srcRect, Rect *dstRect, RGBColor *seedRGB, ProcPtr matchProc, long matchData);
pascal void CharExtra(Fixed extra);
pascal void CloseCPort(CGrafPtr port);
pascal void CopyPixMap(PixMapHandle srcPM, PixMapHandle DstPM);
pascal void CopyPixPat(PixPatHandle srcPP, PixPatHandle dstPP);
pascal void DisposCCursor(CCrsrHandle CCsr);
pascal void DisposCIcon(CIconHandle theIcon);
pascal void DisposCTable(CTabHandle ctTab);
pascal void DisposPixMap(PixMapHandle pm);
pascal void DisposPixPat(PixPatHandle ppat);
pascal void FillCArc(Rect *r, short startAngle, short arcAngle, PixPatHandle ppat);
pascal void FillCOval(Rect *r, PixPatHandle ppat);
pascal void FillCPoly(PolyHandle poly, PixPatHandle ppat);
pascal void FillCRect(Rect *r, PixPatHandle ppat);
pascal void FillCRgn(RgnHandle rgn, PixPatHandle ppat);
pascal void FillCRoundRect(Rect *r, short ovWd, short ovHt, PixPatHandle ppat);
pascal void GetBackColor(RGBColor *color);
pascal CCrsrHandle GetCCursor(short crsrID);
pascal CIconHandle GetCIcon(short id);
pascal void GetCPixel(short h, short v, RGBColor *cPix);
pascal CTabHandle GetCTable(short ctID);
pascal void GetForeColor(RGBColor *color);
pascal PixPatHandle GetPixPat(short patID);
pascal void HiliteColor(RGBColor *color);
pascal void InitCPort(CGrafPtr port);
pascal void MakeRGBPat(PixPatHandle ppat, RGBColor *myColor);
pascal PixMapHandle NewPixMap(void);
pascal PixPatHandle NewPixPat(void);
pascal void OpColor(RGBColor *color);
pascal void OpenCPort(CGrafPtr port);
pascal PicHandle OpenPicture(Rect *picFrame);
pascal void PenPixPat(PixPatHandle ppat);
pascal void PlotCIcon(Rect *theRect, CIconHandle theIcon);
pascal void RGBBackColor(RGBColor *color);
pascal void RGBForeColor(RGBColor *color);
pascal void SeedCFill(BitMap *srcBits, BitMap *DstBits, Rect *SrcRect, Rect *DstRect, short seedH, short seedV, ProcPtr matchProc, long matchData);
pascal void SetCCursor(CCrsrHandle CCrsr);
pascal void SetCPixel(short h, short v, RGBColor *cPix);
pascal void SetCPortPix(PixMapHandle pm);
pascal void SetStdCProcs(CQDProcs *cProcs);
#endif  /*_Color_*/

/* Control Manager [CM] */
#ifdef _ControlMgr_
#ifndef _ColorToolbox_
#include <ColorToolbox.h>
#endif
pascal void DisposeControl(ControlHandle theControl);
pascal void DragControl(ControlHandle theControl, Point start, Rect *limit, Rect *slop, short axis);
pascal void Draw1Control(ControlHandle theControl);
pascal void DrawControls(WindowPtr theWindow);
pascal short FindControl(Point where, WindowPtr theWindow, ControlHandle *ch);
pascal Boolean GetAuxCtl(ControlHandle theControl, CCTabHandle *acHndl);
pascal long GetCRefCon(ControlHandle theControl);
pascal void GetCTitle(ControlHandle theControl, void *title);
pascal short GetCVariant(ControlHandle theControl);
#undef ProcPtr
pascal ProcPtr GetCtlAction(ControlHandle theControl);
#define ProcPtr void*
pascal short GetCtlMax(ControlHandle theControl);
pascal short GetCtlMin(ControlHandle theControl);
pascal short GetCtlValue(ControlHandle theControl);
pascal ControlHandle GetNewControl(short controlID, WindowPtr theWindow);
pascal void HideControl(ControlHandle theControl);
pascal void HiliteControl(ControlHandle theControl, short hiliteState);
pascal void KillControls(WindowPtr theWindow);
pascal void MoveControl(ControlHandle theControl, short h, short v);
pascal ControlHandle NewControl(WindowPtr curWindow, Rect *bounds, void *title, Boolean visible, short value, short min, short max, short procID, long refCon);
pascal void SetCRefCon(ControlHandle theControl, long data);
pascal void SetCTitle(ControlHandle theControl, void *title);
pascal void SetCtlAction(ControlHandle theControl, ProcPtr actionProc);
pascal void SetCtlColor(ControlHandle theControl, CCTabHandle newColorTable);
pascal void SetCtlMax(ControlHandle theControl, short maxValue);
pascal void SetCtlMin(ControlHandle theControl, short minValue);
pascal void SetCtlValue(ControlHandle theControl, short maxValue);
pascal void ShowControl(ControlHandle theControl);
pascal void SizeControl(ControlHandle theControl, short w, short h);
pascal short TestControl(ControlHandle theControl, Point thePoint);
pascal short TrackControl(ControlHandle theControl, Point start, ProcPtr actionProc);
pascal void UpdtControl(WindowPtr theWindow, RgnHandle theRgn);
#endif  /*_ControlMgr_*/

#ifdef _DeskMgr_  /* Desk Manager [DS] */
pascal void CloseDeskAcc(short refnum);
pascal short OpenDeskAcc(void *theAcc);
pascal void SystemClick(EventRecord *theEvent, WindowPtr theWindow);
pascal Boolean SystemEdit(short editCmd);
pascal Boolean SystemEvent(EventRecord *theEvent);
pascal void SystemMenu(long menuResult);
pascal void SystemTask(void);
#endif  /*_DeskMgr_*/

#ifdef _DeviceMgr_  /* Device Manager [DM] also contains Control Panel calls*/
#ifndef _SlotMgr_
#include <SlotMgr.h>
#endif
pascal long cdev(short message, short Item, short numItems, short CPanelID, EventRecord *theEvent,long cdevValue, DialogPtr CPDialog);
pascal OSErr Device(short message, short caller, void *objName, void *zoneName, long p1, long p2);
pascal OSErr OpenSlot(ParmBlkPtr paramBlock, Boolean async);
pascal Boolean SetChooserAlert(Boolean f);
pascal OSErr SIntInstall(SQElemPtr sIntQElemPtr, short theSlot);
pascal OSErr SIntRemove(SQElemPtr sIntQElemPtr, short theSlot);
#endif  /*_DeviceMgr_*/

#ifdef _DialogMgr_  /* Dialog Manager [DL] */
pascal short Alert(short alertID, ProcPtr filterProc);
pascal short CautionAlert(short alertID, ProcPtr filterProc);
pascal void CloseDialog(DialogPtr theDialog);
pascal void CouldAlert(short alertID);
pascal void CouldDialog(short dialogID);
pascal Boolean DialogSelect(EventRecord *theEvent, DialogPtr *theDialog, short *itemHit);
pascal void DisposDialog(DialogPtr theDialog);
pascal void DlgCopy(DialogPtr theDialog);
pascal void DlgCut(DialogPtr theDialog);
pascal void DlgDelete(DialogPtr theDialog);
pascal void DlgPaste(DialogPtr theDialog);
pascal void DrawDialog(DialogPtr theDialog);
pascal void ErrorSound(ProcPtr soundProc);
pascal short FindDItem(DialogPtr theDialog, Point pt);
pascal void FreeAlert(short alertID);
pascal void FreeDialog(short dialogID);
pascal short GetAlrtStage(void);
pascal void GetDItem(DialogPtr theDialog, short itemNo, short *itemType, Handle *item, Rect *box);
pascal void GetIText(Handle item, void *text);
pascal DialogPtr GetNewDialog(short dlogID, DialogPeek dStorage, WindowPtr behind);
pascal void HideDItem(DialogPtr theDialog, short itemNo);
pascal void InitDialogs(ProcPtr resumeProc);
pascal Boolean IsDialogEvent(EventRecord *theEvent);
pascal void ModalDialog(ProcPtr filterProc, short *itemHit);
pascal WindowPtr NewCDialog(void * dStorage, Rect *boundsRect, void *title, Boolean visible, short procID, WindowPtr behind,Boolean goAwayFlag,long refCon, Handle items);
pascal DialogPtr NewDialog(DialogPeek dStorage, Rect *bounds, void *title, Boolean visible, short procID, WindowPtr behind, Boolean goAway, long refCon, Handle items);
pascal short NoteAlert(short alertID, ProcPtr filterProc);
pascal void ParamText(void *pm0, void * pm1, void *pm2,void *pm3);
pascal void ResetAlrtStage(void);
pascal void SelIText(DialogPtr theDialog, short itemNo, short strtSel, short endSel);
pascal void SetDAFont(short fontNum);
pascal void SetDItem(DialogPtr theDialog, short itemNo, short itemType, Handle item, Rect *box);
pascal void SetIText(Handle item, void *text);
pascal void ShowDItem(DialogPtr theDialog, short itemNo);
pascal short StopAlert(short alertID, ProcPtr filterProc);
pascal void UpdtDialog(DialogPtr theDialog, RgnHandle updateRgn);
#endif  /*_DialogMgr_*/

#ifdef _DiskDvr_  /* Disk Driver [DD] */
pascal OSErr DiskEject(short drvNum);
pascal OSErr DriveStatus(short drvNum, DrvSts *stat);
pascal OSErr SetTagBuffer(void * buffPtr);
#endif  /*_DiskDvr_*/

#ifdef _EventMgr_  /* Event Manager/OS [OE] */
pascal Boolean Button(void);
pascal Boolean EventAvail(short evtMask, EventRecord *Evt);
pascal void FlushEvents(short evtMask, short stopMask);
pascal long GetCaretTime(void);
pascal long GetDblTime(void);
pascal QHdrPtr GetEvQHdr(void);
pascal void GetKeys(KeyMap *theKeys);
pascal void GetMouse(Point *mouseLoc);
pascal Boolean GetNextEvent(short evtMask, EventRecord *Evt);
pascal Boolean GetOSEvent(short evtMask, EventRecord *Evt);
pascal long KeyTrans(void * transData, short keycode, long *state);
pascal Boolean OSEventAvail(short evtMask, EventRecord *Evt);
pascal OSErr PPostEvent(short evtCode, long evtMsg, EvQEl *qEl);
pascal OSErr PostEvent(short evtCode, long evtMsg);
pascal void SetEventMask(short theMask);
pascal Boolean StillDown(void);
pascal long TickCount(void);
pascal Boolean WaitMouseUp(void);
#endif  /*_EventMgr_*/

#ifdef _FileMgr_  /* File/Device Manager [FL/DV] */
pascal void  AddDrive(short drvrRefNum, short drvNum, short *refNum);
pascal OSErr Allocate(short refnum, long *count);
pascal OSErr AllocContig(short refNum, long *count);
pascal OSErr CatMove(short vRefNum, long dirID, void *oldName, long newDirID, void *newName);
pascal OSErr CloseDriver(short refNum);
pascal OSErr CloseWD(short wdRefNum);
pascal OSErr Control(short refNum, short csCode, void * csParamPtr);
pascal OSErr Create(void *fileName, short vRef, OSType creator, OSType fileType);
pascal OSErr DirCreate(short vRefNum,long parentDirID, void *dirName, long *createdID);
pascal OSErr Eject(void *volName, short vRef);
pascal void FInitQueue(void);
pascal OSErr FSClose(short ref);
pascal OSErr FSDelete(void *fileName, short vRef);
pascal OSErr FSOpen(void *fileName, short vRef, short *ref);
pascal OSErr FSRead(short refnum, long *count, void * buffPtr);
pascal OSErr FSWrite(short refnum, long *count, void * buffPtr);
pascal OSErr FlushVol(void *volName, short vRef);
pascal DCtlHandle GetDCtlEntry(short refNum);
pascal QHdrPtr GetDrvQHdr(void);
pascal OSErr GetEOF(short refnum, long *logEOF);
pascal OSErr GetFInfo(void *fileName, short vRef, FInfo *fndInfo);
pascal OSErr GetFPos(short refnum, long *filePos);
pascal QHdrPtr GetFSQHdr(void);
pascal QHdrPtr GetVCBQHdr(void);
pascal OSErr GetVInfo(short drvNum, void *volName, short *vRef, long *freeBytes);
pascal OSErr GetVRefNum(short pathRef, short *vRef);
pascal OSErr GetVol(void *volName, short *vRef);
pascal OSErr GetWDInfo(short wdRefNum, short *vRefNum, long *dirID, long *procID);
pascal OSErr HCreate(short vRefNum,long dirID,void *fileName, OSType creator, OSType fileType);
pascal OSErr HDelete(short vRefNum, long dirID, void *fileName);
pascal OSErr HOpen(short vRefNum, long dirID, void *fileName, SignedByte permission, short *refNum);
pascal OSErr HOpenRF(short vRefNum, long dirID, void *fileName, SignedByte permission, short *refNum);
pascal OSErr HGetVol(void *volName, short *vRefNum, long *dirID);
pascal OSErr HGetFInfo(short vRefNum, long dirID, void *fileName, FInfo *fndrInfo);
pascal OSErr HRename(short vRefNum, long dirID, void *oldName, void *newName);
pascal OSErr HRstFLock(short vRefNum, long dirID, void *fileName);
pascal OSErr HSetFInfo(short vRefNum, long dirID, void *fileName, FInfo *fndrInfo);
pascal OSErr HSetFLock(short vRefNum, long dirID, void *fileName);
pascal OSErr HSetVol(void *volName, short vRefNum, long dirID);
pascal OSErr KillIO(short refNum);
pascal OSErr OpenDriver(void *name, short *refNum);
pascal OSErr OpenRF(void *fileName, short vRef, short *ref);
pascal OSErr OpenWD(short vRefNum,long dirID, long procID, short *wdRefNum);
pascal OSErr PBAllocContig(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBAllocate(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBCatMove(CMovePBPtr parmBlk, Boolean async);
pascal OSErr PBClose(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBCloseWD(WDPBPtr parmBlk, Boolean async);
pascal OSErr PBControl( ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBCreate(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBDelete(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBDirCreate(HParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBEject(ParmBlkPtr parmBlk);
pascal OSErr PBFlushFile(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBFlushVol(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBGetCatInfo(CInfoPBPtr paramBlock, Boolean async);
pascal OSErr PBGetEOF(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBGetFCBInfo(FCBPBPtr parmBlk, Boolean async);
pascal OSErr PBGetFInfo(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBGetFPos(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBGetVInfo(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBGetVol(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBGetWDInfo(WDPBPtr parmBlk, Boolean async);
pascal OSErr PBHCopyFile(HParmBlkPtr paramBlock, Boolean async);
pascal OSErr PBHCreate(HParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBHDelete(HParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBHGetDirAccess(HParmBlkPtr paramBlock, Boolean async);
pascal OSErr PBHGetFInfo(HParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBHGetLogInInfo(HParmBlkPtr paramBlock, Boolean async);
pascal OSErr PBHGetVInfo(HParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBHGetVol(WDPBPtr parmBlk, Boolean async);
pascal OSErr PBHGetVolParms(HParmBlkPtr paramBlock, Boolean async);
pascal OSErr PBHMapID(HParmBlkPtr paramBlock, Boolean async);
pascal OSErr PBHMapName(HParmBlkPtr paramBlock, Boolean async);
pascal OSErr PBHMoveRename(HParmBlkPtr paramBlock, Boolean async);
pascal OSErr PBHOpen(HParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBHOpenDeny(HParmBlkPtr paramBlock, Boolean async);
pascal OSErr PBHOpenRF(HParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBHOpenRFDeny(HParmBlkPtr paramBlock, Boolean async);
pascal OSErr PBHRename(HParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBHRstFLock(HParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBHSetDirAccess(HParmBlkPtr paramBlock, Boolean async);
pascal OSErr PBHSetFInfo(HParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBHSetFLock(HParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBHSetVol(WDPBPtr parmBlk, Boolean async);
pascal OSErr PBKillIO(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBLockRange(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBMountVol(ParmBlkPtr parmBlk);
pascal OSErr PBOffLine(ParmBlkPtr parmBlk);
pascal OSErr PBOpen(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBOpenRF(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBOpenWD(WDPBPtr parmBlk, Boolean async);
pascal OSErr PBRead(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBRename(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBRstFLock(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBSetCatInfo(CInfoPBPtr parmBlk, Boolean async);
pascal OSErr PBSetEOF(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBSetFInfo(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBSetFLock(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBSetFPos(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBSetFVers(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBSetVInfo(HParmBlkPtr paramblock, Boolean async);
pascal OSErr PBSetVol(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBStatus(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBUnmountVol(ParmBlkPtr parmBlk);
pascal OSErr PBUnlockRange(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr PBWrite(ParmBlkPtr parmBlk, Boolean async);
pascal OSErr Rename(void *oldName, short vRef, void *newName);
pascal OSErr RstFLock(void *fileName, short vRef);
pascal OSErr SetEOF(short refnum, long logEOF);
pascal OSErr SetFInfo(void *fileName, short vRef, FInfo *fndInfo);
pascal OSErr SetFLock(void *fileName, short vRef);
pascal OSErr SetFPos(short refnum, short posMode, long posOff);
pascal OSErr SetVol(void *volName, short vRef);
pascal OSErr Status(short refNum, short csCode, void * csParamPtr);
pascal OSErr UnmountVol(void *volName, short vRef);
#endif  /*_FileMgr_*/

#ifdef _FontMgr_  /* Font Manager [FM] */
pascal FMOutPtr FMSwapFont(FMInput *inRec);
pascal void FontMetrics(FMetricRec *theMetrics);
pascal void GetFNum(void *fontName, short *theNum);
pascal void GetFontName(short fontNum, void *theName);
pascal void InitFonts(void);
pascal Boolean RealFont(short fontNum, short size);
pascal void SetFScaleDisable(Boolean fontScaleDisable);
pascal void SetFontLock(Boolean lockFlag);
pascal void SetFractEnable(Boolean fractEnable);
#endif  /*_FontMgr_*/

#ifdef _Color_ /* Graphics Devices [GD] */
pascal void DisposGDevice(GDHandle gdh);
pascal GDHandle GetDeviceList(void);
pascal GDHandle GetGDevice(void);
pascal GDHandle GetMainDevice(void);
pascal GDHandle GetMaxDevice(Rect *globalRect);
pascal GDHandle GetNextDevice(GDHandle curDevice);
pascal void InitGDevice(short gdRefNum, long mode, GDHandle gdh);
pascal GDHandle NewGDevice(short refNum, long mode);
pascal void SetDeviceAttribute(GDHandle gdh, short attribute, Boolean value);
pascal void SetGDevice(GDHandle gdh);
pascal Boolean TestDeviceAttribute(GDHandle gdh, short attribute);
#endif  /*_Color_*/

/* THINK C built in functions */
pascal void Debugger(void);
pascal void DebugStr(void *pascalstringliteral);

#ifdef _ListMgr_  /* List Manager [LM] */
pascal void LActivate(Boolean act, ListHandle lHandle);
pascal short LAddColumn(short count, short colNum, ListHandle lHandle);
pascal short LAddRow(short count, short rowNum, ListHandle lHandle);
pascal void LAddToCell(void * data, short dataLen, Cell theCell, ListHandle lHandle);
pascal void LAutoScroll(ListHandle lHandle);
pascal void LCellSize(Point cSize, ListHandle lHandle);
pascal Boolean LClick(Point pt, short modifiers, ListHandle lHandle);
pascal void LClrCell(Cell theCell, ListHandle lHandle);
pascal void LDelColumn(short count, short colNum, ListHandle lHandle);
pascal void LDelRow(short count, short rowNum, ListHandle lHandle);
pascal void LDispose(ListHandle lHandle);
pascal void LDoDraw(Boolean drawIt, ListHandle lHandle);
pascal void LDraw(Cell theCell, ListHandle lHandle);
pascal void LFind(short *offset, short *len, Cell theCell, ListHandle lHandle);
pascal void LGetCell(void * data, short *dataLen, Cell theCell, ListHandle lHandle);
pascal Boolean LGetSelect(Boolean next, Cell *theCell, ListHandle lHandle);
pascal long LLastClick(ListHandle lHandle);    /* really returns Cell, see note at top of this file */
pascal ListHandle LNew(Rect *rView, Rect *dataBounds, Point cSize, short theProc, WindowPtr theWindow, Boolean drawIt, Boolean hasGrow, Boolean scrollHoriz, Boolean scrollVert);
pascal Boolean LNextCell(Boolean hNext, Boolean vNext, Cell *theCell, ListHandle lHandle);
pascal void LRect(Rect *cellRect, Cell theCell, ListHandle lHandle);
pascal void LScroll(short dCols, short dRows, ListHandle lHandle);
pascal Boolean LSearch(void * dataPtr, short dataLen, short(*searchProc)(), Cell *theCell, ListHandle lHandle);
pascal void LSetCell(void * data, short dataLen, Cell theCell, ListHandle lHandle);
pascal void LSetSelect(Boolean setIt, Cell theCell, ListHandle lHandle);
pascal void LSize(short listWidth, short listHeight, ListHandle lHandle);
pascal void LUpdate(RgnHandle thRgn, ListHandle lHandle);
#endif  /*_ListMgr_*/

#ifdef _MemoryMgr_  /* Memory Manager [MM] */
pascal THz ApplicZone(void);
pascal void BlockMove(void * sourcePtr, void * destPtr, Size byteCount);
pascal Size CompactMem(Size cbNeeded);
pascal void DisposHandle(Handle h);
pascal void DisposPtr(void * p);
pascal void EmptyHandle(Handle h);
pascal long FreeMem(void);
pascal Handle GZSaveHnd(void);
pascal Ptr GetApplLimit(void);
pascal Size GetHandleSize(Handle h);
pascal Size GetPtrSize(void * p);
pascal THz GetZone(void);
pascal void HClrRBit(Handle h);
pascal SignedByte HGetState(Handle h);
pascal void HLock(Handle h);
pascal void HNoPurge(Handle h);
pascal void HPurge(Handle h);
pascal void HSetRBit(Handle h);
pascal void HSetState(Handle h, SignedByte flags);
pascal void HUnlock(Handle h);
pascal THz HandleZone(Handle h);
pascal void InitApplZone(void);
pascal void InitZone(ProcPtr pGrowZone, short cMoreMstrs, void * limitPtr, void * startPtr);
pascal void MaxApplZone(void);
pascal long MaxBlock(void);
pascal Size MaxMem(Size *grow);
pascal OSErr MemError(void);
pascal void MoreMasters(void);
pascal void MoveHHi(Handle h);
pascal Handle NewEmptyHandle(void);
pascal Handle NewHandle(Size logicalSize);
pascal Handle NewHandleSys(Size byteCount);
pascal Handle NewHandleClear(Size byteCount);
pascal Handle NewHandleSysClear(Size byteCount);
pascal Ptr NewPtr(Size logicalSize);
pascal Ptr NewPtrSys(Size byteCount);
pascal Ptr NewPtrClear(Size byteCount);
pascal Ptr NewPtrSysClear(Size byteCount);
pascal THz PtrZone(void * p);
pascal void PurgeMem(Size cbNeeded);
pascal void PurgeSpace(long *total, long *contig);
pascal void ReallocHandle(Handle h, Size logicalSize);
pascal Handle RecoverHandle(void * p);
pascal void ResrvMem(Size cbNeeded);
pascal void SetApplBase(void * startPtr);
pascal void SetApplLimit(void * zoneLimit);
pascal void SetGrowZone(ProcPtr growZone);
pascal void SetHandleSize(Handle h, Size newSize);
pascal void SetPtrSize(void * p, Size newSize);
pascal void SetZone(THz hz);
pascal long StackSpace(void);
pascal THz SystemZone(void);
pascal Ptr TopMem(void);
#endif  /*_MemoryMgr_*/

#ifdef _MenuMgr_  /* Menu Manager [MN] */
pascal void AddResMenu(MenuHandle theMenu, ResType theType);
pascal void AppendMenu(MenuHandle theMenu, void *data);
pascal void CalcMenuSize(MenuHandle theMenu);
pascal void CheckItem(MenuHandle theMenu, short item, Boolean checked);
pascal void ClearMenuBar(void);
pascal short CountMItems(MenuHandle theMenu);
pascal void DelMCEntries(short menuID, short MenuItem);
pascal void DelMenuItem(MenuHandle theMenu, short item);
pascal void DeleteMenu(short menuID);
pascal void DisableItem(MenuHandle theMenu, short item);
pascal void DispMCInfo(MCTableHandle menuCTbl);
pascal void DisposeMenu(MenuHandle theMenu);
pascal void DrawMenuBar(void);
pascal void EnableItem(MenuHandle theMenu, short item);
pascal void FlashMenuBar(short menuID);
pascal void GetItem(MenuHandle theMenu, short item, void *itemString);
pascal void GetItemCmd(MenuHandle theMenu, short item, short *cmdChar);
pascal void GetItemIcon(MenuHandle theMenu, short item, short *icon);
pascal void GetItemMark(MenuHandle theMenu, short item, short *markChar);
pascal void GetItemStyle(MenuHandle theMenu, short item, short *chStyle);
pascal MCEntryPtr GetMCEntry(short menuID, short menuItem);
pascal MCTableHandle GetMCInfo(void);
pascal MenuHandle GetMHandle(short menuID);
pascal MenuHandle GetMenu(short resourceID);
pascal Handle GetMenuBar(void);
pascal Handle GetNewMBar(short menuBarID);
pascal void HiliteMenu(short menuID);
pascal void InitMenus(void);
pascal void InitProcMenu(short mbResID);
pascal void InsMenuItem(MenuHandle theMenu, void *, short afterItem);
pascal void InsertMenu(MenuHandle theMenu, short beforeID);
pascal void InsertResMenu(MenuHandle theMenu, ResType theType, short afterItem);
pascal long MenuChoice(void);
pascal long MenuKey(short ch);
pascal long MenuSelect(Point startPt);
pascal MenuHandle NewMenu(short menuID, void *title);
pascal long PopUpMenuSelect(MenuHandle theMenu, short Top, short Left, short PopupItem);
pascal void SetItem(MenuHandle theMenu, short item, void *itemString);
pascal void SetItemCmd(MenuHandle theMenu, short item, short cmdChar);
pascal void SetItemIcon(MenuHandle theMenu, short item, short icon);
pascal void SetItemMark(MenuHandle theMenu, short item, short markChar);
pascal void SetItemStyle(MenuHandle theMenu, short item, short chStyle);
pascal void SetMCEntries(short numEntries, MCTablePtr menuCEntries);
pascal void SetMCInfo(MCTableHandle menuCTbl);
pascal void SetMenuBar(Handle menuList);
pascal void SetMenuFlash(short count);
#endif  /*_MenuMgr_*/

#ifdef _OSUtil_  /* OS Utilities [OU] */
pascal void Date2Secs(DateTimeRec *date, long *secs);
pascal OSErr Dequeue(QElemPtr qEntry, QHdrPtr theQueue);
pascal void Delay(long numTicks, long *finalTicks);
pascal OSErr DTInstall(QElemPtr dtTaskPtr);
pascal void Enqueue(QElemPtr qEntry, QHdrPtr theQueue);
pascal void Environs(short *rom, short *machine);
pascal Boolean EqualString(void *aStr, void *bStr, Boolean caseSens, Boolean diacSens);
pascal void GetDateTime(long *secs);
pascal Byte GetMMUMode(void);      /* Inside Mac Volume V page 592 is wrong */
pascal SysPPtr GetSysPPtr(void);
pascal void GetTime(DateTimeRec *date);
pascal long GetTrapAddress(short trapNum);
pascal OSErr HandAndHand(Handle aHandle, Handle bHandle);
pascal OSErr HandToHand(Handle *h);
pascal OSErr InitUtil(void);
pascal long NGetTrapAddress(short trapNum, Byte tType);
pascal void NSetTrapAddress(long trapAddr, short trapNum, Byte tType);
pascal OSErr PtrAndHand(void *, Handle, long size);
pascal OSErr PtrToHand(void * srcPtr, Handle dstHandle, long size);
pascal OSErr PtrToXHand(void * srcPtr, Handle dstHandle, long size);
pascal OSErr ReadDateTime(long *secs);
pascal short RelString(void *aStr, void *bStr, Boolean caseSens, Boolean diacSens);
pascal void Restart(void);
pascal void Secs2Date(long secs, DateTimeRec *date);
pascal OSErr SetDateTime(long secs);
pascal void SetTime(DateTimeRec *date);
pascal void SetTrapAddress(long trapAddr, short trapNum);
pascal long StripAddress(long theAdress);
pascal void SwapMMUMode(short *mode);
pascal OSErr SysEnvirons(short versRequested, SysEnvRec *theWorld);
pascal void SysBeep(short duration);
pascal void UprString(void *theString, Boolean diacSens);
pascal Boolean WaitNextEvent(short mask, EventRecord *event, long sleep, RgnHandle mouseRgn);
pascal OSErr WriteParam(void);
#endif  /*_OSUtil_*/


#ifdef _PackageMgr_ /* Package Manager [PK] *//* also contains Disk Initialization Package */
pascal short DIBadMount(Point where, long evtMessage);
pascal OSErr DIFormat(short drvNum);
pascal void DILoad(void);
pascal void DIUnload(void);
pascal OSErr DIVerify(short drvNum);
pascal OSErr DIZero(short drvNum, void *volName);
pascal void InitAllPacks(void);
pascal void InitPack(short packID);
pascal void NumToString(long theNum, void *theString);
pascal void StringToNum(void *theString, long *theNum);
#endif  /*_PackageMgr_*/

#ifdef _IntlPkg_  /* International Package [IP] */
pascal short IUCompString(void *aStr, void *bStr);
pascal void IUDatePString(long dateTime, DateForm form, void *result, Handle intlParam);
pascal void IUDateString(long dateTime, DateForm form, void *result);
pascal short IUEqualString(void *aStr, void *bStr);
pascal Handle IUGetIntl(short theID);
pascal short IUMagIDString(void * aPtr, void * bPtr, short aLen, short bLen);
pascal short IUMagString(void * aPtr, void * bPtr, short aLen, short bLen);
pascal Boolean IUMetric(void);
pascal void IUSetIntl(short refNum, short theID, Handle intlParam);
pascal void IUTimePString(long dateTime, Boolean wantSeconds, void *result, Handle intlParam);
pascal void IUTimeString(long dateTime, Boolean wantSeconds, void *result);
#endif  /*_IntlPkg_*/

#ifdef _StdFilePkg_  /* Standard File Package [STP] */
pascal void SFGetFile(Point where, char *prompt,  ProcPtr fileFilter, short numTypes, SFTypeList typeList, ProcPtr dlgHook, SFReply *reply);
pascal void SFPGetFile(Point where, void *prompt, ProcPtr fileFilter, short numTypes, SFTypeList *typeList, ProcPtr dlgHook, SFReply *reply, short dlgID, ProcPtr filterProc);
pascal void SFPPutFile(Point where, void *prompt, void *origName, ProcPtr dlgHook, SFReply *reply, short dlgID, ProcPtr filterProc);
pascal void SFPutFile(Point where, void *prompt, void *origName, ProcPtr dlgHook, SFReply *reply);
#endif  /*_StdFilePkg_*/

#ifdef _Color_ /* Palette Manager */
pascal void ActivatePalette(WindowPtr srcWindow);
pascal void AnimateEntry(WindowPtr dstWindow, short dstEntry, RGBColor *srcRGB);
pascal void AnimatePalette(WindowPtr dstWindow, CTabHandle srcCTab, short srcIndex, short dstEntry,short dstLength);
pascal void CTab2Palette(CTabHandle srcCTab, PaletteHandle dstPalette, short srcUsage, short srcTolerance);
pascal void DisposePalette(PaletteHandle srcPalette);
pascal void GetEntryColor(PaletteHandle srcPalette, short srcEntry, RGBColor *dstRGB);
pascal void GetEntryUsage(PaletteHandle srcPalette, short srcEntry, short *dstUsage, short *dstTolerance);
pascal PaletteHandle GetNewPalette(short paletteID);
pascal PaletteHandle GetPalette(WindowPtr srcWindow);
pascal void InitPalettes(void);
pascal PaletteHandle NewPalette(short entries, CTabHandle srcColors, short srcUsage, short srcTolerance);
pascal void Palette2CTab(PaletteHandle srcPalette, CTabHandle dstCTab);
pascal void PmBackColor(short myEntry);
pascal void PmForeColor(short myEntry);
pascal void SetEntryColor(PaletteHandle dstPalette, short dstEntry, RGBColor *srcRGB);
pascal void SetEntryUsage(PaletteHandle dstPalette, short dstEntry, short srcUsage, short srcTolerance);
pascal void SetPalette(WindowPtr dstWindow, PaletteHandle srcPalette, Boolean cUpdates);
#endif  /*_Color_*/

#ifdef _PrintMgr_  /* Print Manager [PR] */
pascal void PrClose(void);
pascal void PrCloseDoc(TPPrPort pPrPort);
pascal void PrClosePage(TPPrPort pPrPort);
pascal void PrCtlCall(short iWhichCtl, long lparm1, long lparm2, long lparm3);
pascal void PrDrvrClose(void);
pascal Handle PrDrvrDCE(void);
pascal void PrDrvrOpen(void);
pascal short PrDrvrVers(void);
pascal short PrError(void);
pascal void PrGeneral(void * pData);
pascal Boolean PrJobDialog(THPrint hPrint);
pascal void PrJobMerge(THPrint hPrintSrc, THPrint hPrintDst);
pascal void PrOpen(void);
pascal TPPrPort PrOpenDoc(THPrint hPrint, TPPrPort pPrPort, void * pIOBuf);
pascal void PrOpenPage(TPPrPort pPrPort, TPRect pPageFrame);
pascal void PrPicFile(THPrint hPrint, TPPrPort pPrPort, void * pIOBuf, void * pDevBuf, TPrStatus *prStatus);
pascal void PrSetError(short iErr);
pascal Boolean PrStlDialog(THPrint hPrint);
pascal Boolean PrValidate(THPrint hPrint);
pascal void PrintDefault(THPrint hPrint);
#endif  /*_PrintMgr_*/

#ifdef _Quickdraw_  /* QuickDraw [QD] */
pascal void AddPt(Point srcPt, Point *dstPt);
pascal void BackColor(long color);
pascal void BackPat(Pattern pat);
pascal void CalcMask(void * srcPtr, void * dstPtr, short srcRow, short dstRow, short height, short words);
pascal short CharWidth(short ch);
pascal void ClipRect(Rect *r);
pascal void ClosePicture(void);
pascal void ClosePoly(void);
pascal void ClosePort(GrafPtr port);
pascal void CloseRgn(RgnHandle dstRgn);
pascal void ColorBit(short whichBit);
pascal void CopyBits(BitMap *srcBits, BitMap *dstBits, Rect *srcRect, Rect *dstRect, short mode, RgnHandle maskRgn);
pascal void CopyMask(BitMap *srcBits, BitMap *maskBits, BitMap *dstBits, Rect *srcRect, Rect *maskRect, Rect *dstRect);
pascal void CopyRgn(RgnHandle srcRgn, RgnHandle dstRgn);
pascal void DiffRgn(RgnHandle srcRgnA, RgnHandle srcRgnB, RgnHandle dstRgn);
pascal void DisposeRgn(RgnHandle rgn);
pascal void DrawChar(short ch);
pascal void DrawPicture(PicHandle myPicture, Rect *dstRect);
pascal void DrawString(void *s);
pascal void DrawText(void * textBuf, short firstByte, short byteCount);
pascal Boolean EmptyRect(Rect *r);
pascal Boolean EmptyRgn(RgnHandle rgn);
pascal Boolean EqualPt(Point pt1, Point pt2);
pascal Boolean EqualRect(Rect *Rect1, Rect *Rect2);
pascal Boolean EqualRgn(RgnHandle rgnA, RgnHandle rgnB);
pascal void EraseArc(Rect *r, short startAngle, short arcAngle);
pascal void EraseOval(Rect *r);
pascal void ErasePoly(PolyHandle poly);
pascal void EraseRect(Rect *r);
pascal void EraseRgn(RgnHandle rgn);
pascal void EraseRoundRect(Rect *r, short ovalWidth, short ovalHeight);
pascal void FillArc(Rect *r, short startAngle, short arcAngle, Pattern pat);
pascal void FillOval(Rect *r, Pattern pat);
pascal void FillPoly(PolyHandle, Pattern pat);
pascal void FillRect(Rect *r, Pattern pat);
pascal void FillRgn(RgnHandle rgn, Pattern pat);
pascal void FillRoundRect(Rect *r, short ovalWidth, short ovalHeight, Pattern pat);
pascal void ForeColor(long color);
pascal void FrameArc(Rect *r, short startAngle, short arcAngle);
pascal void FrameOval(Rect *r);
pascal void FramePoly(PolyHandle poly);
pascal void FrameRect(Rect *r);
pascal void FrameRgn(RgnHandle rgn);
pascal void FrameRoundRect(Rect *r, short ovalWidth, short ovalHeight);
pascal void GetClip(RgnHandle rgn);
pascal void GetFontInfo(FontInfo *info);
pascal void GetPen(Point *p);
pascal void GetPenState(PenState *pnState);
pascal Boolean GetPixel(short h, short v);
pascal void GetPort(GrafPtr *port);
pascal void GlobalToLocal(Point *p);
pascal void GrafDevice(short device);
pascal void HideCursor(void);
pascal void HidePen(void);
pascal void InitCursor(void);
pascal void InitGraf(GrafPtr *GlobalPtr);    /*parameter should be &thePort*/
pascal void InitPort(GrafPtr *thePort);  /* &thePort changed to *thePort*/
pascal void InsetRect(Rect *r, short dh, short dv);
pascal void InsetRgn(RgnHandle rgn, short dh, short dv);
pascal void InvertArc(Rect *r, short startAngle, short arcAngle);
pascal void InvertOval(Rect *r);
pascal void InvertPoly(PolyHandle poly);
pascal void InvertRect(Rect *r);
pascal void InvertRgn(RgnHandle rgn);
pascal void InvertRoundRect(Rect *r, short ovalWidth, short ovalHeight);
pascal void KillPicture(PicHandle myPicture);
pascal void KillPoly(PolyHandle poly);
pascal void Line(short dh, short dv);
pascal void LineTo(short h, short v);
pascal void LocalToGlobal(Point *p);
pascal void MapPoly(PolyHandle poly, Rect *srcRect, Rect *dstRect);
pascal void MapPt(Point *p, Rect *srcRect, Rect *dstRect);
pascal void MapRect(Rect *r, Rect *srcRect, Rect *dstRect);
pascal void MapRgn(RgnHandle rgn, Rect *srcRect, Rect *dstRect);
pascal void MeasureText(short count, void * textAddr, void * charLocs);
pascal void Move(short dh, short dv);
pascal void MovePortTo(short leftGlobal, short topGlobal);
pascal void MoveTo(short h, short v);
pascal RgnHandle NewRgn(void);
pascal void ObscureCursor(void);
pascal void OffsetPoly(PolyHandle poly, short dh, short dv);
pascal void OffsetRect(Rect *r, short dh, short dv);
pascal void OffsetRgn(RgnHandle rgn, short dh, short dv);
pascal PolyHandle OpenPoly(void);
pascal void OpenPort(GrafPtr port);
pascal void OpenRgn(void);
pascal void PaintArc(Rect *r, short startAngle, short arcAngle);
pascal void PaintOval(Rect *r);
pascal void PaintPoly(PolyHandle poly);
pascal void PaintRect(Rect *r);
pascal void PaintRgn(RgnHandle rgn);
pascal void PaintRoundRect(Rect *r, short ovalWidth, short ovalHeight);
pascal void PenMode(short mode);
pascal void PenNormal(void);
pascal void PenPat(Pattern pat);
pascal void PenSize(short width, short height);
pascal void PicComment(short kind, short datasize, Handle dataHandle);
pascal void PortSize(short width, short height);
pascal void Pt2Rect(Point pt1, Point pt2, Rect *dstRect);
pascal Boolean PtInRect(Point pt, Rect *r);
pascal Boolean PtInRgn(Point pt, RgnHandle rgn);
pascal void PtToAngle(Rect *r, Point pt, short *angle);
pascal short Random(void);
pascal Boolean RectInRgn(Rect *r, RgnHandle rgn);
pascal void RectRgn(RgnHandle rgn, Rect *r);
pascal void ScalePt(Point *p, Rect *srcRect, Rect *dstRect);
pascal void ScrollRect(Rect *r, short dh, short dv, RgnHandle updateRgn);
pascal Boolean SectRect(Rect *src1, Rect *src2, Rect *dstRect);
pascal void SectRgn(RgnHandle srcRgnA, RgnHandle srcRgnB, RgnHandle dstRgn);
pascal void SeedFill(void * srcPtr, void * dstPtr, short srcRow, short dstRow, short height, short words, short seedH, short seedV);
pascal void SetClip(RgnHandle rgn);
pascal void SetCursor(Cursor *c);
pascal void SetEmptyRgn(RgnHandle rgn);
pascal void SetOrigin(short h, short v);
pascal void SetPenState(PenState *pnState);
pascal void SetPort(GrafPtr port);
pascal void SetPortBits(BitMap *bm);
pascal void SetPt(Point *p, short h, short v);
pascal void SetRect(Rect *r, short left, short top, short right, short bottom);
pascal void SetRectRgn(RgnHandle rgn, short left, short top, short right, short bottom);
pascal void SetStdProcs(QDProcs *procs);
pascal void ShowCursor(void);
pascal void ShowPen(void);
pascal void SpaceExtra(Fixed extra);
pascal void StdArc(GrafVerb verb, Rect *r, short startAngle, short arcAngle);
pascal void StdBits(BitMap *srcBits, Rect *srcRect, Rect *dstRect, short mode, RgnHandle maskRgn);
pascal void StdComment(short kind, short dataSize, Handle dataHandle);
pascal void StdGetPic(void * dataPtr, short byteCount);
pascal void StdLine(Point newPt);
pascal void StdOval(GrafVerb verb, Rect *r);
pascal void StdPoly(GrafVerb verb, PolyHandle poly);
pascal void StdPutPic(void * dataPtr, short byteCount);
pascal void StdRRect(GrafVerb verb, Rect *r, short ovalwidth, short ovalheight);
pascal void StdRect(GrafVerb verb, Rect *r);
pascal void StdRgn(GrafVerb verb, RgnHandle rgn);
pascal void StdText(short byteCount, void * textBuf, Point numer, Point denom);
pascal short StdTxMeas(short byteCount, void * textAddr, Point *numer, Point *denom, FontInfo *info);
pascal short StringWidth(void *s);
pascal void StuffHex(void * thingPtr, void *s);
pascal void SubPt(Point srcPt, Point *dstPT);
pascal void TextFace(short face);
pascal void TextFont(short font);
pascal void TextMode(short mode);
pascal void TextSize(short size);
pascal short TextWidth(void * textBuf, short firstByte, short byteCount);
pascal void UnionRect(Rect *src1, Rect *src2, Rect *dstRect);
pascal void UnionRgn(RgnHandle srcRgnA, RgnHandle srcRgnB, RgnHandle dstRgn);
pascal void XorRgn(RgnHandle srcRgnA, RgnHandle srcRgnB, RgnHandle dstRgn);
#endif  /*_Quickdraw_*/

#ifdef _ResourceMgr_  /* Resource Manager [RM] */
pascal void AddReference(Handle theResource, short theID, void *name);
pascal void AddResource(Handle theData, ResType theType, short theID, void *name);
pascal void ChangedResource(Handle theResource);
pascal void CloseResFile(short refNum);
pascal short Count1Resources(ResType theType);
pascal short Count1Types(void);
pascal short CountResources(ResType theType);
pascal short CountTypes(void);
pascal void CreateResFile(void *fileName);
pascal short CurResFile(void);
pascal void DetachResource(Handle theResource);
pascal Handle Get1IndResource(ResType theType, short index);
pascal void Get1IndType(ResType *theType, short index);
pascal Handle Get1NamedResource(ResType theType, void *name);
pascal Handle Get1Resource(ResType theType, short theID);
pascal Handle GetIndResource(ResType theType, short index);
pascal void GetIndType(ResType *theType, short index);
pascal Handle GetNamedResource(ResType theType, void *name);
pascal short GetResAttrs(Handle theResource);
pascal short GetResFileAttrs(short refNum);
pascal void GetResInfo(Handle theResource, short *theID, ResType *theType, void *name);
pascal Handle GetResource(ResType, short theID);
pascal short HomeResFile(Handle theResource);
pascal short InitResources(void);
pascal void LoadResource(Handle theResource);
pascal long MaxSizeRsrc(Handle);
pascal short OpenRFPerm(void *fileName, short vRefNum, Byte permission);
pascal short OpenResFile(void *fileName);
pascal Handle RGetResource(ResType theType, short theID);
pascal void ReleaseResource(Handle theResource);
pascal short ResError(void);
pascal void RmveResource(Handle theResource);
pascal long RsrcMapEntry(Handle);
pascal void RsrcZoneInit(void);
pascal void SetResAttrs(Handle theResource, short attrs);
pascal void SetResFileAttrs(short refNum, short attrs);
pascal void SetResInfo(Handle theResource, short theID, void *name);
pascal void SetResLoad(Boolean load);
pascal void SetResPurge(Boolean install);
pascal long SizeResource(Handle theResource);
pascal short Unique1ID(ResType theType);
pascal short UniqueID(ResType theType);
pascal void UpdateResFile(short refNum);
pascal void UseResFile(short refNum);
pascal void WriteResource(Handle theResource);
#endif  /*_ResourceMgr_*/

#ifdef _ScrapMgr_  /* Scrap Manager [SM] */
pascal long GetScrap(Handle hDest, ResType, long *offset);
pascal PScrapStuff InfoScrap(void);
pascal long LoadScrap(void);
pascal long PutScrap(long length, ResType, void * source);
pascal long UnloadScrap(void);
pascal long ZeroScrap(void);
#endif  /*_ScrapMgr_*/

#ifdef _ScriptMgr_  /* Script Manager [SM] */
pascal short Char2Pixel(Ptr textBuf, short textLen, short slop, short offset, short direction);
pascal short CharByte(Ptr textBuf, short textOffset);
pascal short CharType(Ptr textBuf, short textOffset);
pascal void DrawJust(Ptr textPtr, short textLength, short slop);
pascal void FindWord(Ptr textPtr, short textLength, short offset, Boolean leftSide, BreakTable *breaks, OffsetTable offsets);
pascal short Font2Script(short fontNumber);
pascal short FontScript(void);
pascal short GetAppFont(void);
pascal short GetDefFontSize(void);
pascal long GetEnvirons(short verb);
pascal short GetMBarHeight(void);
pascal long GetScript(short script, short verb);
pascal short GetSysFont(void);
pascal short GetSysJust(void);
pascal void HiliteText(Ptr textPtr, short textLength, short firstOffset, short secondOffset, OffsetTable offsets);
pascal short IntlScript(void);
pascal void KeyScript(short scriptCode);
pascal void MeasureJust(Ptr textPtr, short textLength, short slop, Ptr charLocs);
pascal short Pixel2Char(Ptr textBuf, short textLen, short slop, short pixelWidth, Boolean *leftSide);
pascal OSErr SetEnvirons(short verb, long param);
pascal OSErr SetScript(short script, short verb, long param);
pascal void SetSysJust(short newJust);
pascal short Transliterate(Handle srcHandle, Handle dstHandle, short target, long srcMask);
#endif  /*_ScriptMgr_*/

#ifdef _SCSIMgr_  /* SCSI Manager [SCSI] */
pascal OSErr SCSICmd(void * buffer, short count);
pascal OSErr SCSIComplete(short *stat, short *message, long wait);
pascal OSErr SCSIGet(void);
pascal OSErr SCSIMsgIn(short *message);
pascal OSErr SCSIMsgOut(short message);
pascal OSErr SCSIRBlind(void * tibPtr);
pascal OSErr SCSIRead(void * tibPtr);
pascal OSErr SCSIReset(void);
pascal OSErr SCSISelAtn(short targetID);
pascal OSErr SCSISelect(short targetID);
pascal short SCSIStat(void);
pascal OSErr SCSIWBlind(void * tibPtr);
pascal OSErr SCSIWrite(void * tibPtr);
#endif  /*_SCSIMgr_*/

#ifdef _SegmentLdr_  /* Segment Loader [SL] */
pascal void ClrAppFiles(short index);
pascal void CountAppFiles(short *message, short *count);
pascal void ExitToShell(void);
pascal void GetAppFiles(short index, AppFile *theFile);
pascal void GetAppParms(void *apName, short *apRefNum, Handle *apParam);
pascal void UnloadSeg(ProcPtr routineAddr);
#endif  /*_SegmentLdr_*/

#ifdef _SerialDvr_  /* Serial Driver [SR] */
pascal void RAMSDClose(SPortSel whichPort);
pascal OSErr RAMSDOpen(SPortSel whichPort);
pascal OSErr SerClrBrk(short refNum);
pascal OSErr SerGetBuf(short refNum, long *count);
pascal OSErr SerHShake(short refNum, SerShk *flags);
pascal OSErr SerReset(short refNum, short serConfig);
pascal OSErr SerSetBrk(short refNum);
pascal OSErr SerSetBuf(short refNum, void * serBPtr, short serBLen);
pascal OSErr SerStatus(short refNum, SerStaRec *serSta);
#endif  /*_SerialDvr_*/

#ifdef _OSUtil_  /* Operating System Utilities [OSU] */
pascal void ShutDwnInstall(ProcPtr shutDwnProc, short flags);
pascal void ShutDwnPower(void);
pascal void ShutDwnRemove(ProcPtr shutDwnProc);
pascal void ShutDwnStart(void);
#endif  /*_OSUtil_*/

#ifdef _SlotMgr_  /* Slot Manager [SM] */
pascal OSErr InitPRAMRecs(SpBlockPtr spBlkPtr);
pascal OSErr InitSDeclMgr(SpBlockPtr spBlkPtr);
pascal OSErr InitsRsrcTable(SpBlockPtr spBlkPtr);
pascal OSErr SCalcsPointer(SpBlockPtr spBlkPtr);
pascal OSErr SCalcStep(SpBlockPtr spBlkPtr);
pascal OSErr SCardChanged(SpBlockPtr spBlkPtr);
pascal OSErr SCkCardStatus(SpBlockPtr spBlkPtr);
pascal OSErr SDeleteSRTRec(SpBlockPtr spBlkPtr);
pascal OSErr SExec(SpBlockPtr spBlkPtr);
pascal OSErr SFindDevBase(SpBlockPtr spBlkPtr);
pascal OSErr SFindsRsrcPtr(SpBlockPtr spBlkPtr);
pascal OSErr SFindsInfoRecPtr(SpBlockPtr spBlkPtr);
pascal OSErr SFindStruct(SpBlockPtr spBlkPtr);
pascal OSErr SGetBlock(SpBlockPtr spBlkPtr);
pascal OSErr SGetDriver(SpBlockPtr spBlkPtr);
pascal OSErr SGetcString(SpBlockPtr spBlkPtr);
pascal OSErr SNextTypesRsrc(SpBlockPtr spBlkPtr);
pascal OSErr SNextsRsrc(SpBlockPtr spBlkPtr);
pascal OSErr SOffsetData(SpBlockPtr spBlkPtr);
pascal OSErr SPrimaryInit(SpBlockPtr spBlkPtr);
pascal OSErr SPtrToSlot(SpBlockPtr spBlkPtr);
pascal OSErr SPutPRAMRec(SpBlockPtr spBlkPtr);
pascal OSErr SReadByte(SpBlockPtr spBlkPtr);
pascal OSErr SReadDrvrName(SpBlockPtr spBlkPtr);
pascal OSErr SReadFHeader(SpBlockPtr spBlkPtr);
pascal OSErr SReadInfo(SpBlockPtr spBlkPtr);
pascal OSErr SReadLong(SpBlockPtr spBlkPtr);
pascal OSErr SReadPBSize(SpBlockPtr spBlkPtr);
pascal OSErr SReadPRAMRec(SpBlockPtr spBlkPtr);
pascal OSErr SReadStruct(SpBlockPtr spBlkPtr);
pascal OSErr SReadWord(SpBlockPtr spBlkPtr);
pascal OSErr SRsrcInfo(SpBlockPtr spBlkPtr);
pascal OSErr SSearchSRT(SpBlockPtr spBlkPtr);
pascal OSErr SUpdateSRT(SpBlockPtr spBlkPtr);
#endif  /*_SlotMgr_*/

#ifdef _SoundDvr_  /* Sound Driver [SN] */
pascal void GetSoundVol(short *level);
pascal void SetSoundVol(short level);
pascal OSErr SndAddModifier(SndChannelPtr chan, ProcPtr modifier, short id, long init);
pascal OSErr SndControl(short id, SndCommand *cmd);
pascal OSErr SndDisposeChannel(SndChannelPtr chan, Boolean quietNow);
pascal OSErr SndDoCommand(SndChannelPtr chan, SndCommand *cmd, Boolean noWait);
pascal OSErr SndDoImmediate(SndChannelPtr chan, SndCommand *cmd);
pascal OSErr SndNewChannel(SndChannelPtr *chan, short synth, long init, ProcPtr userRoutine);
pascal OSErr SndPlay(SndChannelPtr chan, Handle sndHndl, Boolean async);
pascal Boolean SoundDone(void);
pascal void StartSound(void * synthRec, long numBytes, ProcPtr completionRtn);
pascal void StopSound(void);
#endif  /*_SoundDvr_*/

#ifdef _StartMgr_  /* Start Manager [STM] */
pascal void GetDefaultStartup(DefStartPtr paramBlock);
pascal void GetOSDefault(DefOSPtr paramBlock);
pascal void GetTimeout(short *count);
pascal void GetVideoDefault(DefVideoPtr paramBlock);
pascal void SetDefaultStartup(DefStartPtr paramBlock);
pascal void SetOSDefault(DefOSPtr paramBlock);
pascal void SetTimeout(short count);
pascal void SetVideoDefault(DefVideoPtr paramBlock);
#endif  /*_StartMgr_*/

/* System Error Handler */
pascal void SysError(short errorCode);

#ifdef _TextEdit_  /* TextEdit [TE] */
pascal TEStyleHandle GetStylHandle(TEHandle hTE);
pascal StScrpHandle GetStylScrap(TEHandle hTE);
pascal void SetClikLoop(ProcPtr clikProc, TEHandle hTE);
pascal void SetStylHandle(TEStyleHandle theHandle,TEHandle hTE);
pascal void SetWordBreak(ProcPtr wBrkProc, TEHandle hTE);
pascal void TEActivate(TEHandle hTE);
pascal void TEAutoView(Boolean , TEHandle hTE);
pascal void TECalText(TEHandle hTE);
pascal void TEClick(Point pt, Boolean extend, TEHandle hTE);
pascal Boolean TEContinuousStyle(short *mode, TEStylePtr aStyle, TEHandle hTE);
pascal void TECopy(TEHandle hTE);
pascal void TECut(TEHandle hTE);
pascal void TEDeactivate(TEHandle hTE);
pascal void TEDelete(TEHandle hTE);
pascal void TEDispose(TEHandle hTE);
pascal OSErr TEFromScrap(void);
pascal long TEGetHeight(long endLine, long startLine, TEHandle hTE);
pascal short TEGetOffset(Point pt, TEHandle hTE);
pascal long TEGetPoint(short offset, TEHandle hTE);  /* really returns a Point */
pascal long TEGetScrapLen(void);
pascal void TEGetStyle(short offset, TextStyle *theStyle, short *lineHeight,  short *fontAscent, TEHandle hTE);
pascal CharsHandle TEGetText(TEHandle hTE);
pascal void TEIdle(TEHandle hTE);
pascal void TEInit(void);
pascal void TEInsert(void * text, long length, TEHandle hTE);
pascal void TEKey(short ch, TEHandle hTE);
pascal TEHandle TENew(Rect *dstRect, Rect *viewRect);
pascal void TEPaste(TEHandle hTE);
pascal void TEPinScroll(short dh, short dv, TEHandle hTE);
pascal void TEReplaceStyle(short mode, TextStyle *oldStyle, TextStyle *newStyle, Boolean redraw, TEHandle hTE);
pascal Handle TEScrapHandle(void);
pascal void TEScroll(short dh, short dv, TEHandle hTE);
pascal void TESelView(TEHandle hTE);
pascal void TESetJust(short just, TEHandle hTE);
pascal void TESetScrapLen(long length);
pascal void TESetSelect(long selStart, long selEnd, TEHandle hTE);
pascal void TESetStyle(short mode, TextStyle *newStyle, Boolean redraw, TEHandle hTE);
pascal void TESetText(void * text, long length, TEHandle hTE);
pascal void TEStylInsert(void * text, long length, StScrpHandle hST, TEHandle hTE);
pascal TEHandle TEStylNew(Rect *destRect, Rect *viewRect);
pascal void TEStylPaste(TEHandle hTE);
pascal OSErr TEToScrap(void);
pascal void TEUpdate(Rect *rUpdate, TEHandle hTE);
pascal void TextBox(void * text, long length, Rect *box, short just);
#endif  /*_TextEdit_*/

#ifdef _TimeMgr_  /* Time Manager [TIME] */
pascal void InsTime(QElemPtr tmTaskPtr);
pascal void PrimeTime(QElemPtr tmTaskPtr, long count);
pascal void RmvTime(QElemPtr tmTaskPtr);
#endif /*_TimeMgr_*/

#ifdef _ToolboxUtil_  /* ToolBox Utilities [TU] */
pascal short AngleFromSlope(Fixed slope);
pascal long BitAnd(long val1, long val2);
pascal void BitClr(void * bytePtr, long bitNum);
pascal long BitNot(long val);
pascal long BitOr(long val1, long val2);
pascal void BitSet(void * bytePtr, long bitNum);
pascal long BitShift(long val, short count);
pascal Boolean BitTst(void * bytePtr, long bitNum);
pascal long BitXor(long val1, long val2);
pascal long DeltaPoint(Point ptA, Point PtB);
pascal Fract Fix2Frac(Fixed x);
pascal long Fix2Long(Fixed x);
/* double Fix2X(Fixed x);  ** In ToolboxUtil.h ** */
pascal Fixed FixATan2(long a, long b);
pascal Fixed FixDiv(Fixed a, Fixed b);
pascal Fixed FixMul(Fixed a, Fixed b);
pascal Fixed FixRatio(short numer, short denom);
pascal short FixRound(Fixed x);
pascal Fixed Frac2Fix(Fract x);
/* double Frac2X(Fract x);  ** In ToolboxUtil.h ** */
pascal Fract FracCos(Fixed x);
pascal Fract FracDiv(Fract x, Fract y);
pascal Fract FracMul(Fract x, Fract y);
pascal Fract FracSin(Fixed x);
pascal Fract FracSqrt(Fract y);
pascal CursHandle GetCursor(short cursorID);
pascal Handle GetIcon(short iconID);
pascal void GetIndPattern(PatPtr thePattern, short patListID, short index);
pascal void GetIndString(void *theString, short strListID, short index);
pascal PatHandle GetPattern(short patID);
pascal PicHandle GetPicture(short picID);
pascal StringHandle GetString(short stringID);
pascal short HiWord(long x);
pascal short LoWord(long x);
pascal Fixed Long2Fix(long x);
pascal void LongMul(long a, long b, Int64Bit *dest);
pascal long Munger(Handle, long offset, void * ptr1, long len1, void * ptr2, long len2);
pascal StringHandle NewString(void *theString);
pascal void PackBits(Ptr *srcPtr, Ptr *dstPtr, short srcBytes);
pascal void PlotIcon(Rect *r, Handle theIcon);
pascal void ScreenRes(short *scrnVRes, short *scrnHres);
pascal void SetString(StringHandle h, void *theString);
pascal void ShieldCursor(Rect *shieldRect, Point offsetPt);
pascal Fixed SlopeFromAngle(short angle);
pascal void UnpackBits(Ptr *srcPtr, Ptr *dstPtr, short dstBytes);
pascal Fixed X2Fix(double *x);
pascal Fract X2Frac(double *x);
#endif  /*_ToolboxUtil_*/

#ifdef _VRetraceMgr_  /* Vertical Retrace [VR] */
pascal OSErr AttachVBL(short theSlot);
pascal OSErr DoVBLTask(short theSlot);
pascal QHdrPtr GetVBLQHdr(void);
pascal OSErr SlotVInstall(QElemPtr vblTaskPtr, short theSlot);
pascal OSErr SlotVRemove(QElemPtr vblTaskPtr, short theSlot);
pascal OSErr VInstall(QElemPtr vblTaskPtr);
pascal OSErr VRemove(QElemPtr vblTaskPtr);
#endif  /*_VRetraceMgr_*/

#ifndef _WindowMgr_  /* Window Manager [WM] */
#include "WindowMgr.h"
#endif
#ifndef _ColorToolbox_
#include "ColorToolbox.h"
#endif
#ifndef _ControlMgr_
#include "ControlMgr.h"
#endif

pascal void BeginUpdate(WindowPtr theWindow);
pascal void BringToFront(WindowPtr theWindow);
pascal void CalcVis(WindowPeek window);
pascal void CalcVisBehind(WindowPeek startWindow, RgnHandle clobberedRgn);
pascal Boolean CheckUpdate(EventRecord *theEvent);
pascal void ClipAbove(WindowPeek window);
pascal void CloseWindow(WindowPtr theWindow);
pascal void DisposeWindow(WindowPtr theWindow);
pascal long DragGrayRgn(RgnHandle theRgn, Point startPt, Rect *limitRect, Rect *slopRect, short axis, ProcPtr actionProc);
pascal void DragWindow(WindowPtr theWindow, Point startPt, Rect *boundsRect);
pascal void DrawGrowIcon(WindowPtr theWindow);
pascal void DrawNew(WindowPeek window, Boolean update);
pascal void EndUpdate(WindowPtr theWindow);
pascal short FindWindow(Point thePt, WindowPtr *whichWind);
pascal WindowPtr FrontWindow(void);
pascal Boolean GetAuxWin(WindowPtr theWindow, AuxWinHndl *colors);
pascal void GetCWMgrPort(CWindowPtr *wport);
pascal RgnHandle GetGrayRgn(void);
pascal WindowPtr GetNewCWindow(short WindowID, void * wStorage, CWindowPtr behind);
pascal WindowPtr GetNewWindow(short windowID, WindowPeek wStorage, WindowPtr behind);
pascal void GetWMgrPort(GrafPtr *wPort);
pascal long GetWRefCon(WindowPtr theWindow);
pascal void GetWTitle(WindowPtr theWindow, void *title);
pascal short GetWVariant(WindowPtr whichWindow);
pascal PicHandle GetWindowPic(WindowPtr theWindow);
pascal long GrowWindow(WindowPtr theWindow, Point startPt, Rect *sizeRect);
pascal void HideWindow(WindowPtr theWindow);
pascal void HiliteWindow(WindowPtr theWindow, Boolean fHilite);
pascal void InitWindows(void);
pascal void InvalRect(Rect *badRect);
pascal void InvalRgn(RgnHandle badRgn);
pascal void MoveWindow(WindowPtr theWindow, short hGlobal, short vGlobal, Boolean front);
pascal WindowPtr NewCWindow(void * wStorage, Rect *boundsRect, void *title, Boolean visible, short procID, WindowPtr behind, Boolean goAwayFlag, long refCon);
pascal WindowPtr NewWindow(WindowPeek wStorage, Rect *boundsRect, char *title, Boolean visible, short procID, WindowPtr behind,  Boolean goAwayFlag, long refCon);
pascal void PaintBehind(WindowPeek startWindow, RgnHandle clobberedRgn);
pascal void PaintOne(WindowPeek window, RgnHandle clobberedRgn);
pascal long PinRect(Rect *theRect, Point thePt);
pascal void SaveOld(WindowPeek window);
pascal void SelectWindow(WindowPtr theWindow);
pascal void SendBehind(WindowPtr theWindow, WindowPtr behindWindow);
pascal void SetDeskCPat(PixPatHandle deskPixPat);
pascal void SetWRefCon(WindowPtr theWindow, long data);
pascal void SetWTitle(WindowPtr theWindow, void *title);
pascal void SetWinColor(WindowPtr theWindow, CTabHandle newColorTable);
pascal void SetWindowPic(WindowPtr theWindow, PicHandle pic);
pascal void ShowHide(WindowPtr theWindow, Boolean showFlag);
pascal void ShowWindow(WindowPtr theWindow);
pascal void SizeWindow(WindowPtr theWindow, short w, short h, Boolean fUpdate);
pascal Boolean TrackBox(WindowPtr theWindow, Point , short partCode);
pascal Boolean TrackGoAway(WindowPtr theWindow, Point thePt);
pascal void ValidRect(Rect *goodRect);
pascal void ValidRgn(RgnHandle goodRgn);
pascal void ZoomWindow(WindowPtr theWindow, short partCode, Boolean front);
/*#endif*/  /*_WindowMgr_*/

#undef ProcPtr
#endif  /*_MacProtos_*/
