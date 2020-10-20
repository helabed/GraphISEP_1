#include "CTrussPane.ph"


      Boolean HitSameTEObject( CTrussElementObject *theObject,
        Point *hitPt )
      {
        Boolean    twoPointMatch = FALSE;
        PenState  pnState;

        twoPointMatch =
              theObject->WhichOneOfUsGotSelected( *hitPt );
        if( twoPointMatch )
        {
        }
        else
          twoPointMatch = FALSE;

        return ( twoPointMatch );
      }

