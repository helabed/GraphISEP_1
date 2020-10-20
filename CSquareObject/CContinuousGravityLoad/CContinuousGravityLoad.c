/****
 * CContinuousGravityLoad.c
 *
 *  CContinuousLoad object class for a typical CTrussPane class
 *
 ****/
#include "CSquareObject.phs"


/*** Global Variables ***/

extern  CBartender *gBartender;
extern   short    gClicks;



void CContinuousGravityLoad::Draw( void )
{
  PenState     pnState;
  Rect      myRect;


  GetPenState ( &pnState);/* to save the pen setting */
  PenPat( black );

  MoveTo( bottomLeftCorner.h, bottomLeftCorner.v );
  LineTo( bottomRightCorner.h, bottomRightCorner.v );
  LineTo( topRightCorner.h, topRightCorner.v );
  LineTo( topLeftCorner.h, topLeftCorner.v );
  LineTo( bottomLeftCorner.h, bottomLeftCorner.v );

  SetPenState ( &pnState);/* to resotre pen settting */

  HandleArrows();
}

void CContinuousGravityLoad::HandleArrows()
{
  float    bSlope,tSlope;
  Point    arrowTail,arrowHead;
  int      arrowCounter = 0;

  arrowTail.h = 0; arrowTail.v = 0; arrowHead.h = 0; arrowHead.v = 0;

  tSlope = ( ((float)(topRightCorner.v - topLeftCorner.v ) ) /
        ( (float)(topRightCorner.h -topLeftCorner.h) ) );

  bSlope = ( ((float)(bottomRightCorner.v - bottomLeftCorner.v ) ) /
        ( (float)(bottomRightCorner.h -bottomLeftCorner.h) ) );

  arrowHead.h = bottomLeftCorner.h;
  arrowHead.v = bottomLeftCorner.v;

  arrowTail.v = topLeftCorner.v;
  arrowTail.h = arrowHead.h;

  MoveTo( arrowTail.h, arrowTail.v);
  LineTo( arrowHead.h, arrowHead.v);
  if( arrowHead.v >= arrowTail.v )
  {
    LineTo( arrowHead.h + ARROW_H_width, arrowHead.v - ARROW_H_height);
    MoveTo( arrowHead.h, arrowHead.v);
    LineTo( arrowHead.h - ARROW_H_width, arrowHead.v - ARROW_H_height);
  }
  else
  {
    LineTo( arrowHead.h + ARROW_H_width, arrowHead.v + ARROW_H_height);
    MoveTo( arrowHead.h, arrowHead.v);
    LineTo( arrowHead.h - ARROW_H_width, arrowHead.v + ARROW_H_height);
  }
  arrowCounter = 1;

  while( arrowTail.h <= (topRightCorner.h - ARROW_SPACING))
  {
    arrowTail.h = topLeftCorner.h + ARROW_SPACING * arrowCounter;
    arrowTail.v = topLeftCorner.v + (int)(tSlope * ARROW_SPACING *
                            arrowCounter);

    arrowHead.h = arrowTail.h;
    arrowHead.v = bottomLeftCorner.v + (int)( bSlope * ARROW_SPACING *
                            arrowCounter);

    MoveTo( arrowTail.h, arrowTail.v);
    LineTo( arrowHead.h, arrowHead.v);
    if( arrowHead.v >= arrowTail.v )
    {
      LineTo( arrowHead.h + ARROW_H_width, arrowHead.v -
                            ARROW_H_height);
      MoveTo( arrowHead.h, arrowHead.v);
      LineTo( arrowHead.h - ARROW_H_width, arrowHead.v -
                            ARROW_H_height);
    }
    else
    {
      LineTo( arrowHead.h + ARROW_H_width, arrowHead.v +
                            ARROW_H_height);
      MoveTo( arrowHead.h, arrowHead.v);
      LineTo( arrowHead.h - ARROW_H_width, arrowHead.v +
                            ARROW_H_height);
    }
    arrowCounter++;
  }
  arrowHead.h = bottomRightCorner.h;
  arrowHead.v = bottomRightCorner.v;

  arrowTail.v = topRightCorner.v;
  arrowTail.h = arrowHead.h;

  MoveTo( arrowTail.h, arrowTail.v);
  LineTo( arrowHead.h, arrowHead.v);
  if( arrowHead.v >= arrowTail.v )
  {
    LineTo( arrowHead.h + ARROW_H_width, arrowHead.v - ARROW_H_height);
    MoveTo( arrowHead.h, arrowHead.v);
    LineTo( arrowHead.h - ARROW_H_width, arrowHead.v - ARROW_H_height);
  }
  else
  {
    LineTo( arrowHead.h + ARROW_H_width, arrowHead.v + ARROW_H_height);
    MoveTo( arrowHead.h, arrowHead.v);
    LineTo( arrowHead.h - ARROW_H_width, arrowHead.v + ARROW_H_height);
  }
}

void CContinuousGravityLoad::MoveYourself( void )
{
  Point    temp1, temp2;
  int      XLengthToBottomRight, YLengthToBottomRight;
  int      XLengthToTopRight, YLengthToTopRight;
  int      XLengthToTopLeft, YLengthToTopLeft;

  /* bottomLeftCorner is our Quadrelateral anchor point */

  XLengthToBottomRight = bottomRightCorner.h - bottomLeftCorner.h;
  YLengthToBottomRight = bottomRightCorner.v - bottomLeftCorner.v;
  XLengthToTopRight = topRightCorner.h - bottomLeftCorner.h;
  YLengthToTopRight = bottomLeftCorner.v - topRightCorner.v;
  XLengthToTopLeft = bottomLeftCorner.h - topLeftCorner.h;
  YLengthToTopLeft = bottomLeftCorner.v - topLeftCorner.v;

  bottomLeftCorner.h = theHitPoint.h - offSet.h;
  bottomLeftCorner.v = theHitPoint.v - offSet.v;

  bottomRightCorner.h = bottomLeftCorner.h + XLengthToBottomRight;
  bottomRightCorner.v = bottomLeftCorner.v + YLengthToBottomRight;

  topLeftCorner.h = bottomLeftCorner.h - XLengthToTopLeft;
  topLeftCorner.v = bottomLeftCorner.v - YLengthToTopLeft;

  topRightCorner.h = bottomLeftCorner.h +  XLengthToTopRight;
  topRightCorner.v = bottomLeftCorner.v -  YLengthToTopRight;

  itsCenterPoint.v = (( bottomLeftCorner.v + topLeftCorner.v ) / 2 +
            ( bottomRightCorner.v + topRightCorner.v ) / 2)/2;
  itsCenterPoint.h = (( bottomLeftCorner.h + topLeftCorner.h ) / 2 +
            ( bottomRightCorner.h + topRightCorner.h ) / 2)/2;

  DragYourself();
}


void CContinuousGravityLoad::DoYourDialog( void )
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

  DHStandardNewRecord (&dhp, ContGravLoadDLOG_ID,
              ContGravLoadUpdateUserItemId,
              ContGravLoad1stMagnitude);


  the1stEndLoad = (float) (bottomLeftCorner.v - topLeftCorner.v);
  the2ndEndLoad = (float) (bottomRightCorner.v - topRightCorner.v);
  ContLoadLength = (float) ( bottomRightCorner.h - bottomLeftCorner.h);

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, ContGravLoad1stMagnitude,
    (the1stEndLoad * itsTrussPane->theLoadScale / SCREEN_DPI ),
      dForm, -MAXREAL, MAXREAL);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, ContGravLoad2ndMagnitude,
    ((the2ndEndLoad) * itsTrussPane->theLoadScale / SCREEN_DPI ),
      dForm, -MAXREAL, MAXREAL);  /* should be limit of drawing area*/

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, ContGravLoadLength,
    (ContLoadLength * itsTrussPane->theStructureScale / SCREEN_DPI ),
      dForm, 0.0, MAXREAL);  /* should be limit of drawing area*/

  if ( IamConnected && itsTElement)
  {
    dForm.digits = 2;
    dForm.style = FIXEDDECIMAL;
    DHAdvAddEditReal(dhp, ContGravLoadTEConnectionRatio,
      (TElementConnectionRatio ),
        dForm, 0.0, 1.0);

    DHADDCHECKBOX( dhp, ContGravLoadAlongStrutE, FALSE);
  }




  if (DHDialogHandler(dhp))
  {
    new1stEndLoad = DHGetEditReal(dhp, ContGravLoad1stMagnitude);
    new2ndEndLoad = DHGetEditReal(dhp, ContGravLoad2ndMagnitude);
    newContLoadLength = DHGetEditReal(dhp, ContGravLoadLength);
    if( IamConnected )
      newTElementConnectionRatio =
          DHGetEditReal(dhp, ContGravLoadTEConnectionRatio);

      /* 1st end Magnitude has changed */
    if( ! (Abs(new1stEndLoad -
        (the1stEndLoad * itsTrussPane->theLoadScale / SCREEN_DPI ) )
               <=  SMALL_FLOAT_VALUE) )
    {
      contLoadRatio = new1stEndLoad /
        (the1stEndLoad * itsTrussPane->theLoadScale / SCREEN_DPI );

      yLength = (float)(bottomLeftCorner.v - topLeftCorner.v);
      UnSelectYourself();
      Erase();

      topLeftCorner.v = topLeftCorner.v -
        (int)(( contLoadRatio - 1.0 )*(yLength));

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

      yLength = (float)(bottomRightCorner.v - topRightCorner.v);
      UnSelectYourself();
      Erase();

      topRightCorner.v = topRightCorner.v -
        (int)(( contLoadRatio - 1.0 )*(yLength));

      FromCornersToItsCenterPoint();
      DrawFinal();
    }


    theBoxIsChecked = DHIsBoxChecked( dhp,
                ContGravLoadAlongStrutE);
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

        xLength = (float)(bottomRightCorner.h - bottomLeftCorner.h);

        bottomRightCorner.h = bottomRightCorner.h +
          (int)(( contLoadRatio - 1.0 )*(xLength));

        xLength = (float)(topRightCorner.h - topLeftCorner.h);
        topRightCorner.h = topRightCorner.h +
          (int)(( contLoadRatio - 1.0 )*(xLength));

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






        /* rather than changing all the ResizeYourself(), we*/
        /* only need to change this one */
void  CContinuousGravityLoad::FromtheHitPointToCorners( void )
{
  if ( topLeftCornerFlag )
  {
    topLeftCorner.v = theHitPoint.v - offSet.v;
    if( ! IamConnected )
    {
      if ( (theHitPoint.h - offSet.h ) > (topRightCorner.h - SMALL_LENGTH))
      {
        topLeftCorner.h = topRightCorner.h - SMALL_LENGTH;
      }else
      {
        topLeftCorner.h = theHitPoint.h - offSet.h;
      }
      bottomLeftCorner.h = topLeftCorner.h;
    }
  }

  else if ( topRightCornerFlag )
  {
    topRightCorner.v = theHitPoint.v - offSet.v;
    if( ! IamConnected )
    {
      if ( ((theHitPoint.h - offSet.h ) < topLeftCorner.h + SMALL_LENGTH) )
      {
        topRightCorner.h = topLeftCorner.h + SMALL_LENGTH;
      }else
      {
        topRightCorner.h = theHitPoint.h - offSet.h;
      }
      bottomRightCorner.h = topRightCorner.h;
    }
  }

  else if ( bottomLeftCornerFlag )
  {
    if( ! IamConnected )
    {
      if ( (theHitPoint.h - offSet.h ) > (bottomRightCorner.h - SMALL_LENGTH))
      {
        bottomLeftCorner.h = bottomRightCorner.h - SMALL_LENGTH;
      }else
      {
        bottomLeftCorner.h = theHitPoint.h - offSet.h;
      }
      bottomLeftCorner.v = theHitPoint.v - offSet.v;
      bottomRightCorner.v = bottomLeftCorner.v;
      topLeftCorner.h = bottomLeftCorner.h;
    }
  }

  else if ( bottomRightCornerFlag )
  {
    if( ! IamConnected )
    {
      if ( ((theHitPoint.h - offSet.h ) < bottomLeftCorner.h + SMALL_LENGTH) )
      {
        bottomRightCorner.h = bottomLeftCorner.h + SMALL_LENGTH;
      }else
      {
        bottomRightCorner.h = theHitPoint.h - offSet.h;
      }
      bottomRightCorner.v = theHitPoint.v - offSet.v;
      bottomLeftCorner.v = bottomRightCorner.v;
      topRightCorner.h = bottomRightCorner.h;
    }
  }
}


void  CContinuousGravityLoad::FromCornersToItsCenterPoint( void )
{
  itsCenterPoint.v = (( bottomLeftCorner.v + topLeftCorner.v ) / 2 +
            ( bottomRightCorner.v + topRightCorner.v ) / 2)/2;
  itsCenterPoint.h = (( bottomLeftCorner.h + topLeftCorner.h ) / 2 +
            ( bottomRightCorner.h + topRightCorner.h ) / 2)/2;

}

