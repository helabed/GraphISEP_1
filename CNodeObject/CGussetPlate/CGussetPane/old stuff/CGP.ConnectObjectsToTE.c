/***************************
 * CGussetPane::ConnectObjectsToTE.c
 * This function takes care of the Nitty gritties involved when connecting
 * an object to a node. If the connection conditions were met, i.e
 * connection was performed it returns TRUE, else False.
 *
 *************************************************/

#include "CGussetPane.ph"

Boolean CGussetPane::ConnectObjectsToTE( short modifierKeys )
{
  Boolean        connectionPerformed = FALSE;
      /* optionkey used, theSelectedTEObject
      is the last node selected */
  if( (theSelectedTEObject) && (modifierKeys == optionKey ))
  {
    switch( theSelectedObject )
    {
      case aConcLoadOrMoment:
        connectionPerformed = theConcLoadOrMoment->
          ConnectYourselfToTE( theSelectedTEObject );
        break;

      case aContLoadOrMoment:
        connectionPerformed = theContLoadOrMoment->
          ConnectYourselfToTE( theSelectedTEObject );
        break;


      case aTrussElementObject:
        theTElementObject->SelectYourself();
        return FALSE;
        break;

      case aNodeObject:
        connectionPerformed = theNodeObject->
          ConnectYourselfToTE( theSelectedTEObject );
        break;

      default:
        /* do nothing */
        return connectionPerformed;
        break;
    }        /* end of switch */
  }
  return connectionPerformed;
}
