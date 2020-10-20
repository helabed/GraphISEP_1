/***************************
 * CGussetPane::ConnectObjectsToNode.c
 * This function takes care of the Nitty gritties involved when connecting
 * an object to a node. If the connection conditions were met, i.e
 * connection was performed it returns TRUE, else False.
 *
 *************************************************/

#include "CGussetPane.ph"

Boolean CGussetPane::ConnectObjectsToNode( short modifierKeys )

{
  Boolean        connectionPerformed = FALSE;

      /* optionKey is used, theSelectedNodeObject
      is the last node selected */
  if( (theSelectedNodeObject) && (modifierKeys == optionKey ))
  {
    switch( theSelectedObject )
    {
      case aConcLoadOrMoment:
        connectionPerformed = theConcLoadOrMoment->
          ConnectYourselfToNode( theSelectedNodeObject );
        break;

      case aTrussElementObject:
        connectionPerformed = theTElementObject->
          ConnectYourselfToNode( theSelectedNodeObject );
        break;

      case aNodeObject:
        theNodeObject->SelectYourself();
        return   FALSE;
        break;

      default:
        /* do nothing */
        return connectionPerformed;
        break;
    }        /* end of switch */
  }
  return connectionPerformed;
}
