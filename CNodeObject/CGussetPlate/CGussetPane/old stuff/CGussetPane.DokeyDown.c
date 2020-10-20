/*************
 * DoKeyDown
 *
 * Do something when a certain key is pressed down.
 *
 ************************/
#include "CGussetPane.ph"

void CGussetPane::DoKeyDown(char theChar, Byte keyCode,
                EventRecord *macEvent)
{

/*__________________________IMPORTANT ___________________________*/
/* don't forget when you are removing objects, make sure they are not
  connected to anything */

/* don't forget to dispose of theNodeLoads, and theNodeTElements before
  you clear a node element, aslo before quitting, do that too...*/
/*------------------------very important ---------------------------*/

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

