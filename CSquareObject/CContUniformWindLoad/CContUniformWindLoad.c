/****
 * CContUniformWindLoad.c
 *
 *  CContUniformWindLoad object class for a typical CTrussPane class
 *
 ****/
#include "CSquareObject.phs"
#include "CContUniformWindLoad.h"
#include "CTrussElementObject.h"
#include "CClustOfContLoadsAndMoments.h"



/*** Global Variables ***/

extern  CBartender *gBartender;
extern   short    gClicks;


void CContUniformWindLoad::HandleArrows()
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
void  CContUniformWindLoad::FromtheHitPointToCorners( void )
{
  int    horizontalOffset;

  if ( topLeftCornerFlag )
  {
    horizontalOffset = bottomLeftCorner.h - topLeftCorner.h;
    topLeftCorner.h = theHitPoint.h - offSet.h;
    bottomLeftCorner.h = topLeftCorner.h + horizontalOffset;
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

  }

  else if ( topRightCornerFlag )
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

  else if ( bottomLeftCornerFlag )
  {
    horizontalOffset = bottomLeftCorner.h - topLeftCorner.h;
    bottomLeftCorner.h = theHitPoint.h - offSet.h;
    topLeftCorner.h = bottomLeftCorner.h - horizontalOffset;
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
  }

  else if ( bottomRightCornerFlag )
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


void CContUniformWindLoad::DoYourDialog( void )
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

  DHStandardNewRecord (&dhp, ContUnifWindLoadDLOG_ID,
              ContUnifWindLoadUpdateUserItemId,
              ContUnifWindLoad1stMagnitude);


  the1stEndLoad = (float) (topRightCorner.h - topLeftCorner.h);
  ContLoadLength = (float) ( bottomRightCorner.v - topRightCorner.v);

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, ContUnifWindLoad1stMagnitude,
    (the1stEndLoad * itsTrussPane->theLoadScale / SCREEN_DPI ),
      dForm, -MAXREAL, MAXREAL);  /* should be limit of drawing area*/


  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, ContUnifWindLoadLength,
    (ContLoadLength * itsTrussPane->theStructureScale / SCREEN_DPI ),
      dForm, 0.0, MAXREAL);  /* should be limit of drawing area*/

  if ( IamConnected && itsTElement)
  {
    dForm.digits = 2;
    dForm.style = FIXEDDECIMAL;
    DHAdvAddEditReal(dhp, ContUnifWindLoadTEConnectionRatio,
      (TElementConnectionRatio ),
        dForm, 0.0, 1.0);


    DHADDCHECKBOX( dhp, ContUnifWindLoadAlongStrutE, FALSE);
  }




  if (DHDialogHandler(dhp))
  {
    new1stEndLoad = DHGetEditReal(dhp, ContUnifWindLoad1stMagnitude);
    newContLoadLength = DHGetEditReal(dhp, ContUnifWindLoadLength);
    if( IamConnected )
      newTElementConnectionRatio =
          DHGetEditReal(dhp, ContUnifWindLoadTEConnectionRatio);

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

      bottomLeftCorner.h = bottomLeftCorner.h -
        (int)(( contLoadRatio - 1.0 )*(xLength));

      FromCornersToItsCenterPoint();
      DrawFinal();
    }


    theBoxIsChecked = DHIsBoxChecked( dhp,
                ContUnifWindLoadAlongStrutE);
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


