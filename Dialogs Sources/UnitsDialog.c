


void  RadioButtonsBeepHook(DialogPtr  dp,
short  itemHit,
DialogHandlerRecordPtr pdh)
{


}



void  RadioButtonsBeepHook(DialogPtr  dp,
short  itemHit,
DialogHandlerRecordPtr pdh)
{
  if (itemHit == RadioUserProc1Id)
    SysBeep(2);
  else
  {
    SysBeep(2);
    SysBeep(2);
  }
}


void  SetStationName(s, dp)
Str255    s;
DialogPtr  dp;
{
  short  itemType;
  Handle  itemHandle;
  Rect  itemRect;


  GetDItem(dp, RadioStationNameId, &itemType, &itemHandle, &itemRect);
  SetIText(itemHandle, s);
}


void  RadioButtonsUserHook(DialogPtr  dp,
short  itemHit,
DialogHandlerRecordPtr pdh)
{
  if (itemHit == StartupItemHit)
  {
    itemHit = RadioStationValue;
  }
  switch (itemHit) {

    case RadioKMPCId:
      SetStationName("\pKMPC", dp);
      break;
    case RadioKEARTHId:
      SetStationName("\pKEARTH", dp);
      break;
    case RadioKLSXId:
      SetStationName("\pKLSX", dp);
      break;
    case RadioKLOSId:
      SetStationName("\pKLOS", dp);
      break;
    case RadioKNXId:
      SetStationName("\pKNX", dp);
      break;
    default:
      ;
  }
}


