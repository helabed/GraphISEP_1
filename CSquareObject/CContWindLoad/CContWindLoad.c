/****
 * CContWindLoad.c
 *
 *  CContWindLoad object class for a typical CTrussPane class
 *
 ****/
#include "CSquareObject.phs"
#include "TrussConstants.h"
#include "CContWindLoad.h"
#include "CTrussElementObject.h"
#include "CClustOfContLoadsAndMoments.h"
#include "CTrussPane.h"


/*** Global Variables ***/

extern  CBartender *gBartender;
extern   short    gClicks;


void CContWindLoad::HandleArrows()
{
  float    invLeftSlope,invRightSlope; /* inverse of the slopes*/
  Point    arrowTail,arrowHead;
  int      arrowCounter = 0;

  arrowTail.h = 0; arrowTail.v = 0; arrowHead.h = 0; arrowHead.v = 0;

  invRightSlope = ( ( (float)(topRightCorner.h -bottomRightCorner.h) )  /
          ((float)(topRightCorner.v - bottomRightCorner.v ) ) );

  invLeftSlope = ( ( (float)(topLeftCorner.h -bottomLeftCorner.h) )   /
        ((float)(topLeftCorner.v - bottomLeftCorner.v ) ) );

  arrowHead.h = bottomRightCorner.h;
  arrowHead.v = bottomRightCorner.v;

  arrowTail.v = bottomLeftCorner.v;
  arrowTail.h = bottomLeftCorner.h;

  MoveTo( arrowTail.h, arrowTail.v);
  LineTo( arrowHead.h, arrowHead.v);
  if( arrowHead.h >= arrowTail.h )
  {
    LineTo( arrowHead.h - ARROW_H_height, arrowHead.v - ARROW_H_width);
    MoveTo( arrowHead.h, arrowHead.v);
    LineTo( arrowHead.h - ARROW_H_height, arrowHead.v + ARROW_H_width);
  }
  else
  {
    LineTo( arrowHead.h + ARROW_H_height, arrowHead.v - ARROW_H_width);
    MoveTo( arrowHead.h, arrowHead.v);
    LineTo( arrowHead.h + ARROW_H_height, arrowHead.v + ARROW_H_width);
  }
  arrowCounter = 1;

  while( arrowTail.v >= (topLeftCorner.v + ARROW_SPACING))
  {
    arrowTail.v = bottomLeftCorner.v - ARROW_SPACING * arrowCounter;
    arrowTail.h = bottomLeftCorner.h - (int)(invLeftSlope * ARROW_SPACING *
                            arrowCounter);

    arrowHead.v = arrowTail.v;
    arrowHead.h = bottomRightCorner.h - (int)( invRightSlope * ARROW_SPACING *
                            arrowCounter);

    MoveTo( arrowTail.h, arrowTail.v);
    LineTo( arrowHead.h, arrowHead.v);
    if( arrowHead.h >= arrowTail.h )
    {
      LineTo( arrowHead.h - ARROW_H_height, arrowHead.v - ARROW_H_width);
      MoveTo( arrowHead.h, arrowHead.v);
      LineTo( arrowHead.h - ARROW_H_height, arrowHead.v + ARROW_H_width);
    }
    else
    {
      LineTo( arrowHead.h + ARROW_H_height, arrowHead.v - ARROW_H_width);
      MoveTo( arrowHead.h, arrowHead.v);
      LineTo( arrowHead.h + ARROW_H_height, arrowHead.v + ARROW_H_width);
    }
    arrowCounter++;
  }
  arrowHead.h = topRightCorner.h;
  arrowHead.v = topRightCorner.v;

  arrowTail.v = topLeftCorner.v;
  arrowTail.h = topLeftCorner.h;

  MoveTo( arrowTail.h, arrowTail.v);
  LineTo( arrowHead.h, arrowHead.v);
  if( arrowHead.h >= arrowTail.h )
  {
    LineTo( arrowHead.h - ARROW_H_height, arrowHead.v - ARROW_H_width);
    MoveTo( arrowHead.h, arrowHead.v);
    LineTo( arrowHead.h - ARROW_H_height, arrowHead.v + ARROW_H_width);
  }
  else
  {
    LineTo( arrowHead.h + ARROW_H_height, arrowHead.v - ARROW_H_width);
    MoveTo( arrowHead.h, arrowHead.v);
    LineTo( arrowHead.h + ARROW_H_height, arrowHead.v + ARROW_H_width);
  }
}

        /* rather than changing all the ResizeYourself(), we*/
        /* only need to change this one */
void  CContWindLoad::FromtheHitPointToCorners( void )
{
  if ( topLeftCornerFlag )
  {
    topLeftCorner.h = theHitPoint.h - offSet.h;
    if( ! IamConnected )
    {
      if ( (theHitPoint.v - offSet.v) > (bottomLeftCorner.v - SMALL_LENGTH))
      {
        topLeftCorner.v = bottomLeftCorner.v - SMALL_LENGTH;
      }else
      {
        topLeftCorner.v = theHitPoint.v - offSet.v;
      }
      topRightCorner.v = topLeftCorner.v;
    }

/*    bottomLeftCorner.h = topLeftCorner.h;
*/  }

  else if ( topRightCornerFlag )
  {
    if( ! IamConnected )
    {
      if ( ((theHitPoint.v - offSet.v ) > bottomRightCorner.v - SMALL_LENGTH) )
      {
        topRightCorner.v = bottomRightCorner.v + SMALL_LENGTH;
      }else
      {
        topRightCorner.v = theHitPoint.v - offSet.v;
      }
      topRightCorner.h = theHitPoint.h - offSet.h;
      topLeftCorner.v = topRightCorner.v;

      bottomRightCorner.h = topRightCorner.h;
    }
  }

  else if ( bottomLeftCornerFlag )
  {
    bottomLeftCorner.h = theHitPoint.h - offSet.h;
    if( ! IamConnected )
    {
      if ( (theHitPoint.v - offSet.v ) < (topLeftCorner.v + SMALL_LENGTH))
      {
        bottomLeftCorner.v = topLeftCorner.v + SMALL_LENGTH;
      }else
      {
        bottomLeftCorner.v = theHitPoint.v - offSet.v;
      }
      bottomRightCorner.v = bottomLeftCorner.v;
    }

/*    topLeftCorner.h = bottomLeftCorner.h;
*/  }

  else if ( bottomRightCornerFlag )
  {
    if( ! IamConnected )
    {
      if ( ((theHitPoint.v - offSet.v ) < topRightCorner.v + SMALL_LENGTH) )
      {
        bottomRightCorner.v = topRightCorner.v + SMALL_LENGTH;
      }else
      {
        bottomRightCorner.v = theHitPoint.v - offSet.v;
      }
      bottomRightCorner.h = theHitPoint.h - offSet.h;
      bottomLeftCorner.v = bottomRightCorner.v;

      topRightCorner.h = bottomRightCorner.h;
    }
  }
}

Boolean  CContWindLoad::CreateTE2ndConnecRatio()
{
  double    inverseSlope;
  double    offSetLength;
  double    TElementLength;
  Point    TE1stEnd, TE2ndEnd;
  Point    aPoint;
  int      xLength, yLength;
  Point    connectToThisPoint;
  Boolean    TrussElementisOK = FALSE;

  TE1stEnd.h = itsTElement->its1stEnd.h;
  TE1stEnd.v = itsTElement->its1stEnd.v;
  TE2ndEnd.h = itsTElement->its2ndEnd.h;
  TE2ndEnd.v = itsTElement->its2ndEnd.v;

  if( Abs((TE2ndEnd.v -TE1stEnd.v)) <= SMALL_LENGTH )
    return FALSE;    /* no connection allowed division by zero!!*/

  inverseSlope = ( ( (double)(TE2ndEnd.h -TE1stEnd.h) ) /
        ((double)(TE2ndEnd.v - TE1stEnd.v ) ) );

  connectToThisPoint.h = ((int)((( double)(TE2ndEnd.h -TE1stEnd.h))
          *TElementConnectionRatio)) + TE1stEnd.h;
  connectToThisPoint.v = ((int)((( double)(TE2ndEnd.v -TE1stEnd.v))
          *TElementConnectionRatio)) + TE1stEnd.v;

  if( (TE2ndEnd.v - TE1stEnd.v) >= SMALL_LENGTH )
  {
    /* case 1 bottom hemisphere */
    if( loadAlongAllMember )
    {
      TElementConnectionRatio = 0.0;
      TElement2ndConnectionRatio = 1.0;
      TrussElementisOK =  TRUE;
    }
    else
    {
      if ( ( bottomRightCorner.v - topRightCorner.v ) <=
                    (TE2ndEnd.v - connectToThisPoint.v) )
      {
        yLength = ( bottomRightCorner.v - topRightCorner.v );
        xLength = ( ( int)(((double)(yLength))*inverseSlope)) ;
        aPoint.h = connectToThisPoint.h + xLength;
        aPoint.v = connectToThisPoint.v + yLength;

        offSetLength = ( double) sqrt( (double)(( ((double)
          (aPoint.h-TE1stEnd.h)) * ((double)(aPoint.h-TE1stEnd.h))) +
          (((double)(aPoint.v-TE1stEnd.v))*((double)(aPoint.v-TE1stEnd.v)))));

        TElementLength = (double) sqrt((double)(( (((double)(TE2ndEnd.v -
            TE1stEnd.v)) * ((double)(TE2ndEnd.v -TE1stEnd.v) )) +
              ( ((double)(TE2ndEnd.h -TE1stEnd.h))*
              ((double)(TE2ndEnd.h -TE1stEnd.h)) ) ) ) );

        TElement2ndConnectionRatio = (float)( offSetLength / TElementLength);
        TrussElementisOK =  TRUE;
      }
      else if( ! ( EqualPt(TE2ndEnd , connectToThisPoint) ) )
      {
        TElement2ndConnectionRatio = 1.0;
        TrussElementisOK =  TRUE;
      }
      else
        TrussElementisOK =  FALSE;
    }
  }
  else if( (TE1stEnd.v - TE2ndEnd.v) >= SMALL_LENGTH )
  {
    /* case 2 top hemisphere */
    if( loadAlongAllMember )
    {
      TElementConnectionRatio = 1.0;
      TElement2ndConnectionRatio = 0.0;
      TrussElementisOK =  TRUE;
    }
    else
    {
      if ( ( bottomRightCorner.v - topRightCorner.v ) <=
                    (TE1stEnd.v - connectToThisPoint.v) )
      {
        yLength = ( bottomRightCorner.v - topRightCorner.v );
        xLength = ( ( int)(((double)(yLength))*inverseSlope)) ;
        aPoint.h = connectToThisPoint.h + xLength;
        aPoint.v = connectToThisPoint.v + yLength;

        offSetLength = ( double) sqrt( (double)(( ((double)
          (aPoint.h-TE1stEnd.h)) * ((double)(aPoint.h-TE1stEnd.h))) +
          (((double)(aPoint.v-TE1stEnd.v))*((double)(aPoint.v-TE1stEnd.v)))));

        TElementLength = (double) sqrt((double)(( (((double)(TE2ndEnd.v -
            TE1stEnd.v)) * ((double)(TE2ndEnd.v -TE1stEnd.v) )) +
              ( ((double)(TE2ndEnd.h -TE1stEnd.h))*
              ((double)(TE2ndEnd.h -TE1stEnd.h)) ) ) ) );

        TElement2ndConnectionRatio = (float)( offSetLength / TElementLength);
        TrussElementisOK =  TRUE;
      }
      else if( ! ( EqualPt(TE1stEnd , connectToThisPoint) ) )
      {
        TElement2ndConnectionRatio = 0;
        TrussElementisOK =  TRUE;
      }
      else
        TrussElementisOK =  FALSE;
    }
  }
  else
    TrussElementisOK = FALSE;

  return TrussElementisOK;
}


Boolean CContWindLoad::ConnectYourselfToTE(
        struct CTrussElementObject  *theSelectedTEObject )
{
  Boolean    IsItOKToConnect = FALSE;

  if( ! this->IamConnected )
  {
    itsTElement = theSelectedTEObject;
    TElementConnectionRatio = itsTElement->lastClickLocatedAtRatio;

    IsItOKToConnect = CreateTE2ndConnecRatio();
    if( !   IsItOKToConnect )
    {
      return FALSE;
    }
    Erase();
    theSelectedTEObject->AddToItsContLandMCluster( this);
    this->ReSizingInProgress = FALSE;
    PrepareYourselfToBeUpdated();
    this->DrawFinal();
    this->IamConnected = TRUE;
    theSelectedTEObject->SelectYourself();
    itsTrussPane->theObject = theSelectedTEObject;
    return TRUE;
  }else
  {
    return FALSE;
  }
}


void CContWindLoad::DoYourDialog( void )
{
  DialogHandlerRecordPtr   dhp;
  DecForm          dForm;
  float          the1stEndLoad;
  float          the2ndEndLoad;
  float          new1stEndLoad;
  float          new2ndEndLoad;
  float          ContLoadLength;
  float          newContLoadLength;
  Boolean          theBoxIsChecked;
  Boolean          connectionPerformed=FALSE;
  float          newTElementConnectionRatio;
  CTrussElementObject    *oldTE;
  float          contLoadRatio;
  float          xLength;
  float          yLength;

  DHStandardNewRecord (&dhp, ContWindLoadDLOG_ID,
              ContWindLoadUpdateUserItemId,
              ContWindLoad1stMagnitude);


  the1stEndLoad = (float) (topRightCorner.h - topLeftCorner.h);
  the2ndEndLoad = (float) (bottomRightCorner.h - bottomLeftCorner.h);
  ContLoadLength = (float) ( bottomRightCorner.v - topRightCorner.v);

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, ContWindLoad1stMagnitude,
    (the1stEndLoad * itsTrussPane->theLoadScale / SCREEN_DPI ),
      dForm, -MAXREAL, MAXREAL);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, ContWindLoad2ndMagnitude,
    ((the2ndEndLoad) * itsTrussPane->theLoadScale / SCREEN_DPI ),
      dForm, -MAXREAL, MAXREAL);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, ContWindLoadLength,
    (ContLoadLength * itsTrussPane->theStructureScale / SCREEN_DPI ),
      dForm, 0.0, MAXREAL);  /* should be limit of drawing area*/

  if ( IamConnected && itsTElement)
  {
    dForm.digits = 2;
    dForm.style = FIXEDDECIMAL;
    DHAdvAddEditReal(dhp, ContWindLoadTEConnectionRatio,
      (TElementConnectionRatio ),
        dForm, 0.0, 1.0);

    DHADDCHECKBOX( dhp, ContWindLoadAlongStrutE, FALSE);
  }

  if (DHDialogHandler(dhp))
  {
    new1stEndLoad = DHGetEditReal(dhp, ContWindLoad1stMagnitude);
    new2ndEndLoad = DHGetEditReal(dhp, ContWindLoad2ndMagnitude);
    newContLoadLength = DHGetEditReal(dhp, ContWindLoadLength);
    if( IamConnected )
      newTElementConnectionRatio =
          DHGetEditReal(dhp, ContWindLoadTEConnectionRatio);

      /* 1st end Magnitude has changed */
    if( ! (Abs(new1stEndLoad -
        (the1stEndLoad * itsTrussPane->theLoadScale / SCREEN_DPI ) )
               <=  SMALL_FLOAT_VALUE) )
    {
      contLoadRatio = new1stEndLoad /
        (the1stEndLoad * itsTrussPane->theLoadScale / SCREEN_DPI );

      xLength = (float)(topRightCorner.h - topLeftCorner.h);
      UnSelectYourself();
      Erase();

      topLeftCorner.h = topLeftCorner.h -
        (int)(( contLoadRatio - 1.0 )*(xLength));

      FromCornersToItsCenterPoint();
      DrawFinal();
    }

      /* 2nd end Magnitude has changed */
    if( ! (Abs(new2ndEndLoad -
        (the2ndEndLoad * itsTrussPane->theLoadScale / SCREEN_DPI ) )
               <=  SMALL_FLOAT_VALUE) )
    {
      contLoadRatio = new2ndEndLoad /
        (the2ndEndLoad * itsTrussPane->theLoadScale / SCREEN_DPI );

      xLength = (float)(bottomRightCorner.h - bottomLeftCorner.h);
      UnSelectYourself();
      Erase();

      bottomLeftCorner.h = bottomLeftCorner.h -
        (int)(( contLoadRatio - 1.0 )*(xLength));

      FromCornersToItsCenterPoint();
      DrawFinal();
    }


    theBoxIsChecked = DHIsBoxChecked( dhp,
                ContWindLoadAlongStrutE);
    if( theBoxIsChecked )
    {
      loadAlongAllMember = TRUE;
      if( IamConnected)
      {
        oldTE = itsTElement;
        DisconnectYourself();
        UnSelectYourself();
        Erase();

        loadAlongAllMember = TRUE;
        connectionPerformed =  ConnectYourselfToTE( oldTE );

        if( ! connectionPerformed )
          SysBeep(2);
      }
    }else
    {
          /*  Length field have changed */
      if( ! ( ( Abs( newContLoadLength -
          (ContLoadLength * itsTrussPane->theStructureScale / SCREEN_DPI )
            ) ) <= SMALL_FLOAT_VALUE ) )
      {
        oldTE = itsTElement;
        DisconnectYourself();
        UnSelectYourself();
        Erase();

        contLoadRatio = newContLoadLength /
          (ContLoadLength * itsTrussPane->theStructureScale / SCREEN_DPI );

        yLength = (float)(bottomRightCorner.v - topRightCorner.v);

        bottomRightCorner.v = bottomRightCorner.v +
          (int)(( contLoadRatio - 1.0 )*(yLength));

        yLength = (float)(bottomLeftCorner.v - topLeftCorner.v);
        bottomLeftCorner.v = bottomLeftCorner.v +
          (int)(( contLoadRatio - 1.0 )*(yLength));

        if( oldTE )    /* if it was connected before lengthening*/
        {
          connectionPerformed =  ConnectYourselfToTE( oldTE );

          if( ! connectionPerformed )
            SysBeep(2);
        }
        else
          DrawFinal();
      }

        /* TElementConnectionRatio has changed */
        /* these two conditions mean the same thing for this object*/
      if ( IamConnected && itsTElement)
      {
        if ( ! ( Abs( newTElementConnectionRatio - TElementConnectionRatio)
            <= SMALL_FLOAT_VALUE ) )
        {
          oldTE = itsTElement;
          DisconnectYourself();
          UnSelectYourself();
          Erase();

          TElementConnectionRatio = newTElementConnectionRatio;
          oldTE->lastClickLocatedAtRatio = newTElementConnectionRatio;

          connectionPerformed =  ConnectYourselfToTE( oldTE );

          if( ! connectionPerformed )
            SysBeep(2);
          itsTElement->DrawFinal();
        }
      }
    }
  }

  DHDeallocateRecord(dhp);
}


void CContWindLoad::DisconnectYourself()
{
  int      XLengthToTopLeft, XLengthToBottomLeft;

  if( IamConnected )
  {
    UnSelectYourself();
    Erase();
    XLengthToTopLeft = topRightCorner.h - topLeftCorner.h;
    XLengthToBottomLeft = bottomRightCorner.h - bottomLeftCorner.h;

    bottomRightCorner.h = topRightCorner.h;

    topLeftCorner.h = topRightCorner.h - XLengthToTopLeft;
    bottomLeftCorner.h = bottomRightCorner.h - XLengthToBottomLeft;

    FromCornersToItsCenterPoint();

    DrawFinal();
    SelectYourself();

    IamConnected = FALSE;
    loadAlongAllMember = FALSE;

    itsTElement->theTEContLoadsAndMoments->Remove( this );
    itsTElement->DrawFinal();
    itsTElement = NULL;
  }
}

void CContWindLoad::PrepareYourselfToBeUpdated( void )
{
  Point    TE1stEnd, TE2ndEnd;
  Point    connectToThisPoint;
  Point    connectToThis2ndPoint;
  int      xLength, yLength;
  int      XLengthToTopLeft, YLengthToTopRight;
  int      XLengthToBottomLeft, YLengthToTopLeft;


  TE1stEnd.h = itsTElement->its1stEnd.h;
  TE1stEnd.v = itsTElement->its1stEnd.v;
  TE2ndEnd.h = itsTElement->its2ndEnd.h;
  TE2ndEnd.v = itsTElement->its2ndEnd.v;

  connectToThisPoint.h = ((int)((( float)(TE2ndEnd.h -TE1stEnd.h))
          *TElementConnectionRatio)) + TE1stEnd.h;
  connectToThisPoint.v = ((int)((( float)(TE2ndEnd.v -TE1stEnd.v))
          *TElementConnectionRatio)) + TE1stEnd.v;

  connectToThis2ndPoint.h = ((int)((( float)(TE2ndEnd.h -TE1stEnd.h))
          *TElement2ndConnectionRatio)) + TE1stEnd.h;
  connectToThis2ndPoint.v = ((int)((( float)(TE2ndEnd.v -TE1stEnd.v))
          *TElement2ndConnectionRatio)) + TE1stEnd.v;

  XLengthToTopLeft = topRightCorner.h - topLeftCorner.h;
  XLengthToBottomLeft = bottomRightCorner.h - bottomLeftCorner.h;

  topRightCorner.h = connectToThisPoint.h;
  topRightCorner.v = connectToThisPoint.v;

  bottomRightCorner.h = connectToThis2ndPoint.h;
  bottomRightCorner.v = connectToThis2ndPoint.v;

  topLeftCorner.h = topRightCorner.h - XLengthToTopLeft;
  topLeftCorner.v = topRightCorner.v;

  bottomLeftCorner.h = bottomRightCorner.h -  XLengthToBottomLeft;
  bottomLeftCorner.v = bottomRightCorner.v;

  itsCenterPoint.v = (( bottomLeftCorner.v + topLeftCorner.v ) / 2 +
            ( bottomRightCorner.v + topRightCorner.v ) / 2)/2;
  itsCenterPoint.h = (( bottomLeftCorner.h + topLeftCorner.h ) / 2 +
            ( bottomRightCorner.h + topRightCorner.h ) / 2)/2;
}

