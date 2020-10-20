/*************
 * DoKeyDown
 *
 * Do something when a certain key is pressed down.
 *
 ************************/
#include "CTrussPane.phs"

void CTrussPane::DoKeyDown(char theChar, Byte keyCode,
                EventRecord *macEvent)
{
          /* dispose of object, clear = 47, delete = 33*/
  if ((objectAlreadySelected) && ( (keyCode == 0x47) || (keyCode == 0x33)))
  {
    switch( theSelectedObject )
    {
      case aContLoadOrMoment:
        theObject->DeleteYourself();
        break;

      case aConcLoadOrMoment:
        switch( theConcLoadOrMoment->WhoAreYou() )
        {
          case aConcentratedMoment:
          case aConcentratedLoad:
            theObject->DeleteYourself();
            break;
        }
        break;

      case aNodeObject:
        theObject->DeleteYourself();
        break;

      case aTrussElementObject:
        theObject->DeleteYourself();
        break;
    }
  }
}

