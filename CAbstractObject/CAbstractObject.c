/****
 * CAbstractObject.c
 *
 *  Abstract object class for a typical CTrussPane class
 *
 ****/
 
#include "CAbstractObject.phs"


/*** Global Variables ***/


  

/***
 * Draw
 *
 * this method should be overwritten by all objects that are
 * descendants of this one
 *
 ***/

void CAbstractObject::Draw( void )

{

}

void CAbstractObject::ReDraw( void )

{
  if ( !IamConnected )
  {
    DrawFinal();
  }
  if ( IamSelected )
  {
    this->SelectYourself();
  }
}

void CAbstractObject::Erase( void )
{
  PenState  pnState;


  GetPenState ( &pnState);/* to save the pen setting */        
  PenMode ( patBic );
  Draw();          /* this is needed to fill gaps */
  SetPenState ( &pnState);/* to resotre pen settting */
}

void CAbstractObject::DragYourself( void )
{
  PenState     pnState;
  
  GetPenState ( &pnState);/* to save the pen setting */        
  PenMode ( patXor );
  Draw();          /* this is needed to fill gaps */
  SetPenState ( &pnState);/* to resotre pen settting */
}

void CAbstractObject::DrawFinal( void )
{
  PenState     pnState;
  GetPenState ( &pnState);/* to save the pen setting */        
  PenMode ( patCopy );
  Draw();          /* this is needed to fill gaps */
  SetPenState ( &pnState);/* to resotre pen settting */
}



void CAbstractObject::SelectYourself( void )
{
  /* this is a method by wich an object should inform the user
    graphically that it got selected */
}

void CAbstractObject::UnSelectYourself( void )
{
}

 
void  CAbstractObject::UpDateObject( void )
{
  /* this is the method that CObjectMouseTask should send to any
    generic object, based on WhichOneOfUsGotSelected, the object
    itself should decide what to do: ResizeYourself, MoveYourself
    or anything else that it wants to do. */

  Draw();
}
void  CAbstractObject::ResizeYourself( void )
{

}

void CAbstractObject::DoYourDialog( void )
{
  OptionNotImplemented();
}


Boolean  CAbstractObject::WhichOneOfUsGotSelected( Point aPoint )
{
  /* this method should be overwritten by each descendant of this
    object */

}

void  CAbstractObject::EraseResizingHandles( Point aPoint )
{
  PenState     pnState;

  GetPenState ( &pnState);/* to save the pen setting */        
  PenMode ( patBic );
  DrawResizingHandles( aPoint );  
  SetPenState ( &pnState);/* to resotre pen settting */
}


void  CAbstractObject::DrawResizingHandles( Point giveMeAPoint )
{
  Rect  myRect;
  Point  hitPt;

  hitPt = giveMeAPoint;
  myRect.top = hitPt.v - 2;
  myRect.left = hitPt.h - 2;
  myRect.bottom = hitPt.v + 2;
  myRect.right = hitPt.h + 2;
  
  PaintRect( &myRect );
}

void  CAbstractObject::MoveYourself( void )
{

}


void  CAbstractObject::InitializeYourself( void )
{
    Draw();
    IamSelected = TRUE;
    ReSizingInProgress = FALSE;
    IamConnected = FALSE;
}

MyObjects  CAbstractObject::WhoAreYou( void )
{
  return  theKindOfObjectIam;
}


void  CAbstractObject::DisconnectYourself( void )
{
}
void  CAbstractObject::DeleteYourself( void )
{
}

void  CAbstractObject::PrintDebugInfo( void )
{
}
void  CAbstractObject::PrintFileStatics( void )
{
}
void  CAbstractObject::PrintFileFireWood( void )
{
}
void  CAbstractObject::KillYourself_IF_NOT_Connected( void )
{
  if( ! IamConnected )
  {
    DeleteYourself();
  }
}
void  CAbstractObject::SaveYourself( void )
{
}
void  CAbstractObject::LoadYourself( void )
{
}

void  CAbstractObject::InitializeGlobalNumbers( void )
{

}
void  CAbstractObject::PrintFileWood1( void )
{
}
void  CAbstractObject::PrintFileWood2( void )
{
}
void  CAbstractObject::PrintFileWood3( void )
{
}
void  CAbstractObject::PrintFileWood4( void )
{
}
