/****
 * CGussetPDoc.c
 *
 *  Document methods for a typical application.
 *
 ****/

#include "CGussetPDoc.phs"
#include "CGussetPDoc.h"

#define GussetWIND  600


extern  CApplication *gApplication;  /* The application */
extern  CBartender  *gBartender;  /* The menu handling object */
extern  CDecorator  *gDecorator;  /* Window dressing object  */
extern  CDesktop  *gDesktop;    /* The enclosure for all windows */
extern  CBureaucrat  *gGopher;    /* The current boss in the chain of command */
extern  OSType    gSignature;    /* The application's signature */
extern  CError    *gError;    /* The global error handler */

/***
 * ITrussDoc
 *
 *  This is your document's initialization method.
 *  If your document has its own instance variables, initialize
 *  them here.
 *  The least you need to do is invoke the default method.
 *
 ***/

void CGussetPDoc::IGussetPDoc(CBureaucrat *aSupervisor, Boolean printable)

{
  CDocument::IDocument(aSupervisor, printable);
  theSystemOfUnits = USCustomary; /* see constants.h */
  theLoadScale = 100.00;    /* 1000 lbs per inch of screen */
  theStructureScale = 2.00;  /* 2 inches per inch of screen */

  horzDrawingSize = 8 * 12; /* 4 ft.*/
  vertDrawingSize= 8 * 12; /* 2 ft.*/

}

void CGussetPDoc::DrawingSizeDialog( void )
{
  DialogHandlerRecordPtr dhp;
  DecForm          dForm;
  float          newhorzDrawingSize;
  float          newvertDrawingSize;
  int            paneWidth;
  int            paneHeight;
  Rect          thePaneRect;


  DHStandardNewRecord (&dhp, DrawingSizeDLOG_ID,
        DrawingSizeUpdateUserItemId, DrawingSizeHorizontal);

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, DrawingSizeHorizontal, horzDrawingSize,
                    dForm, 0.0, MAXREAL);

  dForm.digits = 2;
  dForm.style = FIXEDDECIMAL;
  DHAdvAddEditReal(dhp, DrawingSizeVertical, vertDrawingSize,
                    dForm, 0.0, MAXREAL);

  if (DHDialogHandler(dhp))
  {
    newhorzDrawingSize = DHGetEditReal(dhp, DrawingSizeHorizontal);
    newvertDrawingSize = DHGetEditReal(dhp, DrawingSizeVertical);

    if( ! (Abs(newhorzDrawingSize -
       (horzDrawingSize  ))
       <=  SMALL_FLOAT_VALUE) )

    {
      /* value has changed respond*/
      horzDrawingSize = newhorzDrawingSize;
      paneWidth = (short)(horzDrawingSize/ theStructureScale * SCREEN_DPI);
      paneHeight =(short)(vertDrawingSize/ theStructureScale * SCREEN_DPI);
      thePaneRect.top = 0;
      thePaneRect.left = 0;
      thePaneRect.right = paneWidth;
      thePaneRect.bottom = paneHeight;
      ((CPanorama *)itsMainPane)->SetBounds( &thePaneRect );
    }
    if( ! (Abs(newvertDrawingSize -
       (vertDrawingSize ))
       <=  SMALL_FLOAT_VALUE) )

    {
      /* value has changed respond*/
      vertDrawingSize = newvertDrawingSize;
      paneWidth = (short)(horzDrawingSize/ theStructureScale * SCREEN_DPI);
      paneHeight =(short)(vertDrawingSize/ theStructureScale * SCREEN_DPI);
      thePaneRect.top = 0;
      thePaneRect.left = 0;
      thePaneRect.right = paneWidth;
      thePaneRect.bottom = paneHeight;
      ((CPanorama *)itsMainPane)->SetBounds( &thePaneRect );
    }
  }

  DHDeallocateRecord(dhp);
}

/***
 * Dispose
 *
 *  This is your document's destruction method.
 *  If you allocated memory in your initialization method
 *  or opened temporary files, this is the place to release them.
 *
 *  Be sure to call the default method!
 *
 ***/

void CGussetPDoc::Dispose()

{

  inherited::Dispose();
}


/***
 * DoCommand
 *
 *  This is the heart of your document.
 *  In this method, you handle all the commands your document
 *  deals with.
 *
 *  Be sure to call the default method to handle the standard
 *  document commands: cmdClose, cmdSave, cmdSaveAs, cmdRevert,
 *  cmdPageSetup, cmdPrint, and cmdUndo. To change the way these
 *  commands are handled, override the appropriate methods instead
 *  of handling them here.
 *
 ***/

void CGussetPDoc::DoCommand(long theCommand)

{
  switch (theCommand) {

    case cmdDrawingSize:
      DrawingSizeDialog();
      break;

    case cmdQuit:
      itsWindow->Hide();
      break;

    case cmdSave:
      itsWindow->Hide();
      break;

    case cmdSaveAs:
      itsWindow->Hide();
      break;

    case cmdClose:
      itsWindow->Hide();
      break;

    case cmdRevert:
      itsWindow->Hide();
      break;

    default:  inherited::DoCommand(theCommand);
          break;
  }
}



/***
 * Activate
 *
 *  Your document is becoming active-- the front window.
 *
 *  In this method you can enable menu commands that apply only when
 *  your document is active.
 *
 *  Be sure to call the default method to get the default behavior.
 *  The default method enables these commands: cmdClose, cmdSaveAs,
 *  cmdSave, cmdRevert, cmdPageSetup, cmdPrint, cmdUndo.
 *
 ***/

void CGussetPDoc::Activate(void)

{
  inherited::Activate();
  /* gBartender->DisableCmd( cmdQuit );  this one didn't work*/
}


/***
 * Deactivate
 *
 *  Your document is becoming inactive-- another window is in front
 *
 *  In this method you can disable menu commands that don't apply
 *  when your document isn't active.
 *
 *  Be sure to call the default method to get the default behavior.
 *  The default method disables these commands: cmdClose, cmdSaveAs,
 *  cmdSave, cmdRevert, cmdPageSetup, cmdPrint, cmdUndo.
 *
 ***/

void CGussetPDoc::Deactivate(void)

{
  inherited::Deactivate();
  itsWindow->Hide();
  /*gBartender->EnableCmd( cmdQuit ); this one didn't work */

}

/***
 * NewFile
 *
 *  When the user chooses New from the File menu, the CreateDocument()
 *  method in your Application class will send a newly created document
 *  this message. This method needs to create a new window, ready to
 *  work on a new document.
 *
 *  Since this method and the OpenFile() method share the code for creating
 *  the window, you should use an auxiliary window-building method.
 *
 ***/
void CGussetPDoc::NewFile(void)

{
    /**
     **  BuildWindow() is the method that
     **  does the work of creating a window.
     **  It's parameter should be the data that
     **  you want to display in the window.
     **  Since this is a new window, there's nothing
     **  to display.
     **
     **/

  Str255    wTitle;          /* Window title string        */
  short    wCount;          /* Index number of new window    */
  Str63    wNumber;        /* Index number as a string      */

    /* &&& Set up a new document, including an associated window  */

  BuildWindow(NULL);          /* XXX Here we use a BuildWindow()  */
                    /*   method with a NULL parameter.  */
                    /*   Usually, the OpenFile() method  */
                    /*   (see below), will also send a  */
                    /*   BuildWindow() message, but    */
                    /*   with a handle to some data.  */

  itsWindow->GetTitle(wTitle);    /* Append an index number to the  */
  wTitle[0] = 11;            /* char. count*/
  wTitle[1] = 'G';
  wTitle[2] = 'u';
  wTitle[3] = 's';
  wTitle[4] = 's';          /* quick and dirty way of doing it*/
  wTitle[5] = 'e';
  wTitle[6] = 't';
  wTitle[7] = 'P';
  wTitle[8] = 'l';
  wTitle[9] = 'a';
  wTitle[10] = 't';
  wTitle[11] = 'e';
  wCount = gDecorator->GetWCount();  /*   default name of the window    */
  NumToString((long)(itsGussetPlate->theObjectNumber), wNumber);
/*  NumToString((long)wCount, wNumber);
*/  ConcatPStrings(wTitle, (StringPtr) "\p-");
  ConcatPStrings(wTitle, wNumber);
  itsWindow->SetTitle(wTitle);    /* Make it the active window    */

    /**
     **  Send the window a Select() message to make
     **  it the active window.
     **/

/*  itsWindow->Select();*/
}


/***
 * OpenFile
 *
 *  When the user chooses OpenÉ from the File menu, the OpenDocument()
 *  method in your Application class will let the user choose a file
 *  and then send a newly created document this message. The information
 *  about the file is in the SFReply record.
 *
 *  In this method, you need to open the file and display its contents
 *  in a window. This method uses the auxiliary window-building method.
 *
 ***/

void CGussetPDoc::OpenFile(SFReply *macSFReply)

{
  CDataFile  *theFile;
  Handle    theData;
  Str63    theName;
  OSErr    theError;

    /**
     ** Create a file and send it a SFSpecify()
     **  message to set up the name, volume, and
     **  directory.
     **
     **/

  theFile = new(CDataFile);
  theFile->IDataFile();
  theFile->SFSpecify(macSFReply);

    /**
     **  Be sure to set the instance variable
     **  so other methods can use the file if they
     **  need to. This is especially important if
     **  you leave the file open in this method.
     **  If you close the file after reading it, you
     **  should be sure to set itsFile to NULL.
     **
     **/

  itsFile = theFile;

    /**
     **  Send the file an Open() message to
     **  open it. You can use the ReadSome() or
     **  ReadAll() methods to get the contents of the file.
     **
     **/

  theError = theFile->Open(fsRdWrPerm);

    /**
     **  Check to see if we were able to open
     **  the file. Send the error handler
     **  a CheckOSError() message. If there was
     **  an error, CheckOSError returns false
     **  and reports the error in an alert.
     **  The default error message displays the
     **  error number.
     **  You can use Estr resources to customize
     **  the error message.
     **
     **  Note that we send ourselves a Dispose()
     **  message. Since we're not going to open,
     **  we should get rid of the object.
     **/

  if (!gError->CheckOSError(theError)) {
    Dispose();
    return;
  }

    /**
     **  Make sure that the memory request to read
     **  the data from the file doesn't use up any
     **  of our rainy day fund and that the GrowMemory()
     **  method (in the application) knows that it's OK
     **  if we couldn't get enough memory.
     **
     **/

  gApplication->RequestMemory(FALSE, FALSE);
  theFile->ReadAll(&theData);    /* ReadAll() creates the handle */


    /**
     **  If there isn't enough memory to open,
     **  post the error (should be -108)
     ** and get rid of ourselves.
     **
     **/

  if (theData == NULL) {
    gError->CheckOSError(MemError());
    Dispose();
    return;
  }


  BuildWindow(theData);

    /**
     **  In your application, you'll probably store
     **  the data in some form as an instance variable
     **  in your document class. For this example, there's
     **  no need to save it, so we'll get rid of it.
     **
     **/

  DisposHandle(theData);

    /**
     **  In this implementation, we leave the file
     **  open. You might want to close it after
     **  you've read in all the data.
     **
     **/

  itsFile->GetName(theName);
  itsWindow->SetTitle(theName);
  itsWindow->Select();      /* Don't forget to make the window active */
}



/***
 * BuildWindow
 *
 *  This is the auxiliary window-building method that the
 *  NewFile() and OpenFile() methods use to create a window.
 *
 *  In this implementation, the argument is the data to display.
 *
 ***/

void CGussetPDoc::BuildWindow (Handle theData)

{
  CScrollPane    *theScrollPane;
  CGussetPane    *theMainPane;
  int        paneWidth;
  int        paneHeight;

    /**
     **  First create the window and initialize
     **  it. The first argument is the resource ID
     **  of the window. The second argument specifies
     **  whether the window is a floating window.
     **  The third argument is the window's enclosure; it
     **  should always be gDesktop. The last argument is
     **  the window's supervisor in the Chain of Command;
     **  it should always be the Document object.
     **
     **/

  itsWindow = new(CWindow);
  itsWindow->IWindow(GussetWIND, FALSE, gDesktop, this);
  itsWindow->Hide();

    /**
     **  After you create the window, you can use the
     **  SetSizeRect() message to set the windowÕs maximum
     **  and minimum size. Be sure to set the max & min
     **  BEFORE you send a PlaceNewWindow() message to the
     **  decorator.
     **
     ** The default minimum is 100 by 100 pixels. The
     **  default maximum is the bounds of GrayRgn() (The
     **  entire display area on all screens.)
     **
     **/


  theScrollPane = new(CScrollPane);

    /**
     **  You can initialize a scroll pane two ways:
     **    1. You can specify all the values
     **       right in your code, like this.
     **    2. You can create a ScPn resource and
     **       initialize the pane from the information
     **       in the resource.
     **
     **/

  theScrollPane->IScrollPane(itsWindow, this, 0, 0, 0, 0,
                sizELASTIC, sizELASTIC,
                TRUE, TRUE, TRUE);

    /**
     **  The FitToEnclFrame() method makes the
     **  scroll pane be as large as its enclosure.
     **  In this case, the enclosure is the window,
     **  so the scroll pane will take up the entire
     **  window.
     **
     **/

  theScrollPane->FitToEnclFrame(TRUE, TRUE);


    /**
     **  itsMainPane is the document's focus
     **  of attention. Some of the standard
     **  classes (particularly CPrinter) rely
     **  on itsMainPane pointing to the main
     **  pane of your window.
     **
     **  itsGopher specifies which object
     **  should become the gopher. By default
     **  the document becomes the gopher. ItÕs
     **  likely that your main pane handles commands
     **  so youÕll almost always want to set itsGopher
     **  to point to the same object as itsMainPane.
     **
     **  Note that the main pane is the
     **  panorama in the scroll pane and not
     **  the scroll pane itself.
     **
     **/

  theMainPane = new(CGussetPane);
  itsMainPane = theMainPane;
  itsGopher = theMainPane;

    /**  The FitToEnclosure() method makes the pane
     **  fit inside the enclosure. The inside (or
     **  interior) of a scroll pane is defined as
     **  the area inside the scroll bars.
     **/

  paneWidth = (short)(horzDrawingSize/ theStructureScale * SCREEN_DPI);
  paneHeight = (short)(vertDrawingSize/ theStructureScale * SCREEN_DPI);

  theMainPane->IGussetPane(theScrollPane, this, paneWidth, paneHeight, 0, 0, sizELASTIC, sizELASTIC);
  theMainPane->FitToEnclosure(TRUE, TRUE);

    /** these are here because I moved the initialization of these var.
     ** from CTrussPane.ITrussPane to here. Remember there is two sets
     ** of the following variables, one in CGussetPDoc, and the other is in
     ** CTrussPane
     **/

  theMainPane->theSystemOfUnits = theSystemOfUnits;
  theMainPane->theLoadScale = theLoadScale;
  theMainPane->theStructureScale = theStructureScale;
    /**
     **  Send the scroll pane an InstallPanorama()
     **  to associate our pane with the scroll pane.
     **
     **/

  theScrollPane->InstallPanorama(theMainPane);
  theScrollPane->SetSteps( 20, 20 );      /* scroll steps */

    /**
     **  The Decorator is a global object that takes care
     **  of placing and sizing windows on the screen.
     **  You don't have to use it.
     **
     **/

  gDecorator->PlaceNewWindow(itsWindow);

    /***
     * this is my dumb way of passing the pointer to itsWindow
     * to thePaneWindow in CTrussPane
     */

  theMainPane->thePaneWindow = (CWindow *)itsWindow;
}


/***
 * DoSave
 *
 *  This method handles what happens when the user chooses Save from the
 *  File menu. This method should return TRUE if the file save was successful.
 *  If there is no file associated with the document, you should send a
 *  DoSaveFileAs() message.
 *
 ***/

Boolean CGussetPDoc::DoSave(void)

{
    /**
     **  If you closed your file in your NewFile() method,
     **  you'll need a different way than this to determine
     **  if there's a file associated with your document.
     **
     **/

  if (itsFile == NULL)
    return(DoSaveFileAs());
  else {

    /**
     **  In your application, this is where you'd
     **  write out your file. if you left it open,
     **  send the WriteSome() or WriteAll() mesages
     **  to itsFile.
     **
     **/

    dirty = FALSE;          /* Document is no longer dirty    */
    gBartender->DisableCmd(cmdSave);
    return(TRUE);          /* Save was successful        */
  }
}


/***
 * DoSaveAs
 *
 *  This method handles what happens when the user chooses Save AsÉ from
 *  File menu. The default DoCommand() method for documents sends a DoSaveFileAs()
 *  message which displays a standard put file dialog and sends this message.
 *  The SFReply record contains all the information about the file you're about
 *  to create.
 *
 ***/

Boolean CGussetPDoc::DoSaveAs(SFReply *macSFReply)

{
    /**
     **  If there's a file associated with this document
     **  already, close it. The Dispose() method for files
     **  sends a Close() message to the file before releasing
     **  its memory.
     **
     **/

  if (itsFile != NULL)
    itsFile->Dispose();


    /**
     **  Create a new file, and then save it normally.
     **
     **/

  itsFile = new(CDataFile);
  ((CDataFile *)itsFile)->IDataFile();
  itsFile->SFSpecify(macSFReply);
  itsFile->CreateNew(gSignature, 'TEXT');
  itsFile->Open(fsRdWrPerm);

  itsWindow->SetTitle(macSFReply->fName);

  return( DoSave() );
}


/***
 * DoRevert
 *
 *  If your application supports the Revert command, this method
 *  should close the current file (without writing anything out)
 *  and read the last saved version of the file.
 *
 ***/

void CGussetPDoc::DoRevert(void)

{
}


/**************************************************************************
 PageCount------>not implemented yet

    Return the number of pages in a Document
 **************************************************************************/
short  CGussetPDoc::PageCount( void )
{
  long  pixWidth;
  long  pixHeight;
  long  height;
  long  width;

                    /* Get dimensions of main pane  */
  itsMainPane->GetPixelExtent(&pixWidth, &pixHeight);
                    /* Pages have a fixed pixel height  */
  height = pixHeight / pageHeight + 1;
  width = pixWidth / pageWidth + 1;

  return( height * width );
}


/**************************************************************************/

