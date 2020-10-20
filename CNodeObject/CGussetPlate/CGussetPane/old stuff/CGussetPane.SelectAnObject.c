/******************
 * CGussetPane::SelectAnObject.c
 * This method accepts a hitPt as an input and results in finding which
 * Object out of all object was selected. If an object was located it
 * returns a TRUE, else a FALSE.
 *
 * The static function HitSameObject is the boolean function needed
 * when we are searching a cluster.
 *
 ******************************************/

#include "CGussetPane.ph"

extern Boolean HitSameTEObject( CTrussElementObject *theObject,
         Point *hitPt );

      /***
       * test to see if a mouse was pressed on top
       * of one of the objects, this is for selecting, moving and
       * resizing ...
       */

      static Boolean HitSameObject( CAbstractObject *theObject,
        Point *hitPt )
      {
        Boolean    twoPointMatch = FALSE;
        PenState  pnState;

        twoPointMatch =
              theObject->WhichOneOfUsGotSelected( *hitPt );

        return ( twoPointMatch );
      }


Boolean    CGussetPane::SelectAnObject( Point hitPt, short modifierKeys )

{

  Boolean        theSameHitPoint;

      /* setting theSelectedObject to Null so that only one
        object is selected for now.. */
  theSelectedObject = aNullObject;
  objectAlreadySelected = FALSE;

      /* we want to see if click occurred on one of the objects */


  if( (modifierKeys == controlKey ) )
  {
    if( !objectAlreadySelected )
      theTElementObject = ( CTrussElementObject *)TElementsCluster->
              FindItem1( HitSameTEObject, ( long )( &hitPt) );

    if( theTElementObject && !objectAlreadySelected)
    {
      theNodeObject = ( CNodeObject *)NodesCluster->FindItem1(
            HitSameObject, ( long )( &hitPt) );
      if( theNodeObject->itsMotherTElement == theTElementObject )
      {
        theSelectedObject = aTrussElementObject;
        objectAlreadySelected = TRUE;
        theSelectedTEObject = theTElementObject;
        theObject = (CTrussElementObject *)theTElementObject;
        if( ! (modifierKeys == optionKey ) )
        {
          thePreviouslySelectedObject = aTrussElementObject;
        }
      }
      else
      {
        TElementsCluster->Remove( theTElementObject );
        TElementsCluster->Add( theTElementObject );
        if( !objectAlreadySelected )
        {
          theTElementObject = ( CTrussElementObject *)
          TElementsCluster-> FindItem1( HitSameTEObject,
          ( long )( &hitPt) );
          theNodeObject = ( CNodeObject *)NodesCluster->FindItem1(
                HitSameObject, ( long )( &hitPt) );
          if( theNodeObject->itsMotherTElement == theTElementObject )
          {
            theSelectedObject = aTrussElementObject;
            objectAlreadySelected = TRUE;
            theSelectedTEObject = theTElementObject;
            theObject = (CTrussElementObject *)theTElementObject;
            if( ! (modifierKeys == optionKey ) )
            {
              thePreviouslySelectedObject = aTrussElementObject;
            }
          }
        }

      }
    }
  }

  if( !objectAlreadySelected )
    theNodeObject = ( CNodeObject *)NodesCluster->FindItem1(
            HitSameObject, ( long )( &hitPt) );

  if( theNodeObject && !objectAlreadySelected)
  {
    theSelectedObject = aNodeObject;
    objectAlreadySelected = TRUE;
    theSelectedNodeObject = theNodeObject;
    theObject = (CNodeObject *)theNodeObject;
      /* saving a copy theNode object so that we can */
      /* connect to it different  objects */

    if( ! (modifierKeys == optionKey ) )
    {
      thePreviouslySelectedObject = aNodeObject;
    }
  }


  if( !objectAlreadySelected )
    theTElementObject = ( CTrussElementObject *)TElementsCluster->
            FindItem1( HitSameObject, ( long )( &hitPt) );

  if( theTElementObject && !objectAlreadySelected)
  {
    theSelectedObject = aTrussElementObject;
    objectAlreadySelected = TRUE;
    theSelectedTEObject = theTElementObject;
    theObject = (CTrussElementObject *)theTElementObject;
    if( ! (modifierKeys == optionKey ) )
    {
      thePreviouslySelectedObject = aTrussElementObject;
    }
  }

  if( !objectAlreadySelected )
    theContLoadOrMoment = ( CQuadrelateralObject *)ContLoadsAndMoments->
          FindItem1( HitSameObject, ( long )( &hitPt));

  if( theContLoadOrMoment && !objectAlreadySelected)
  {
    theSelectedObject = aContLoadOrMoment;
    objectAlreadySelected = TRUE;
    theObject = (CQuadrelateralObject *)theContLoadOrMoment;

  }


  if( !objectAlreadySelected )
    theConcLoadOrMoment = ( CConcLoadObject *)ConcLoadsAndMoments->
          FindItem1( HitSameObject, ( long )( &hitPt) );

  if( theConcLoadOrMoment && !objectAlreadySelected)
  {
    theSelectedObject = aConcLoadOrMoment;
    objectAlreadySelected = TRUE;
    theObject = (CConcLoadObject *)theConcLoadOrMoment;
  }

  return objectAlreadySelected;
}

