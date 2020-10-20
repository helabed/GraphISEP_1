/*****
 * CTrussApp.c
 *
 *  Application methods for a typical application.
 *
 *****/

#include "CTrussApp.phs"

extern  OSType    gSignature;
extern  CBartender *gBartender;

/***
 * ITrussApp
 *
 *  Initialize the application. Your initialization method should
 *  at least call the inherited method. If your application class
 *  defines its own instance variables or global variables, this
 *  is a good place to initialize them.
 *
 ***/

void CTrussApp::ITrussApp(void)

{
  CApplication::IApplication(4, 20480L, 2048L);
  structureNumber = 0L;
}



/***
 * SetUpFileParameters
 *
 *  In this routine, you specify the kinds of files your
 *  application opens.
 *
 *
 ***/

void CTrussApp::SetUpFileParameters(void)

{
  inherited::SetUpFileParameters();  /* Be sure to call the default method */

    /**
     **  sfNumTypes is the number of file types
     **  your application knows about.
     **  sfFileTypes[] is an array of file types.
     **  You can define up to 4 file types in
     **  sfFileTypes[].
     **
     **/

  sfNumTypes = 1;
  sfFileTypes[0] = 'TEXT';

    /**
     **  Although it's not an instance variable,
     **  this method is a good place to set the
     **  gSignature global variable. Set this global
     **  to your application's signature. You'll use it
     **  to create a file (see CFile::CreateNew()).
     **
     **/

  gSignature = 'Hani';
}



/***
 * DoCommand
 *
 *  Your application will probably handle its own commands.
 *  Remember, the command numbers from 1-1023 are reserved.
 *  The file Commands.h contains all the reserved commands.
 *
 *  Be sure to call the default method, so you can get
 *  the default behvior for standard commands.
 *
 ***/
void CTrussApp::DoCommand(long theCommand)

{
  switch (theCommand) {

    /* Your commands go here */

    default:  inherited::DoCommand(theCommand);
          break;
  }
}

/***
 * Exit
 *
 *  Chances are you won't need this method.
 *  This is the last chance your application gets to clean up
 *  things like temporary files.
 *
 ***/

void CTrussApp::Exit()

{
  /* your exit handler here */
}


/***
 * CreateDocument
 *
 *  The user chose New from the File menu.
 *  In this method, you need to create a document and send it
 *  a NewFile() message.
 *
 ***/

void CTrussApp::CreateDocument()

{
  CTrussDoc  *theDocument;

  theDocument = new(CTrussDoc);

    /**
     **  Send your document an initialization
     **  message. The first argument is the
     **  supervisor (the application). The second
     **  argument is TRUE if the document is printable.
     **
     **/

  theDocument->ITrussDoc(this, TRUE);

  structureNumber++;
    /**
     **  Send the document a NewFile() message.
     **  The document will open a window, and
     **  set up the heart of the application.
     **
     **/
  theDocument->NewFile();

}

/***
 * OpenDocument
 *
 *  The user chose OpenÉ from the File menu.
 *  In this method you need to create a document
 *  and send it an OpenFile() message.
 *
 *  The macSFReply is a good SFReply record that contains
 *  the name and vRefNum of the file the user chose to
 *  open.
 *
 ***/

void CTrussApp::OpenDocument(SFReply *macSFReply)

{
  CTrussDoc  *theDocument;

  theDocument = new(CTrussDoc);

    /**
     **  Send your document an initialization
     **  message. The first argument is the
     **  supervisor (the application). The second
     **  argument is TRUE if the document is printable.
     **
     **/

  theDocument->ITrussDoc(this, TRUE);

    /**
     **  Send the document an OpenFile() message.
     **  The document will open a window, open
     **  the file specified in the macSFReply record,
     **  and display it in its window.
     **
     **/
  theDocument->OpenFile(macSFReply);
}

/***
 * SetUpMenus
 *
 *  In this method, you add special menu items and set the
 *  menu item dimming and checking options for your menus.
 *  The most common special menu items are the names of the
 *  fonts. For this tiny editor( this part was borrowed from tinyEdit),
 *  you also want to set up the
 *  dimming and checking options so only the current font
 *  and size are checked.
 *
 ***/

void CTrussApp::SetUpMenus(void)

{
    /**
     ** Let the default method read the menus from
     **  the MBAR 1 resource.
     **
     **/

  inherited::SetUpMenus();

    /**
     ** Add the fonts in the  system to the
     **  Font menu. Remember, MENUfont is one
     **  of the reserved font numbers.
     **
     **/

/*  gBartender->InsertHierMenu( MENUmyfont, cmdNull, MENUstyle, 10 );*/
    /* it seems I didn't need to include this line for my hier
      menu because I was able to create the whole menu from
      resources.. */

  AddResMenu(GetMHandle(MENUmyfont), 'FONT');  /* see bartender */


    /**
     **  The UpdateMenus() method sets up the dimming
     **  for menu items. By default, the bartender dims
     **  all the menus, and each bureaucrat is reponsible
     **  for turning on the items that correspond to the commands
     **  it can handle.
     **
     **  Set up the options here. The TrussPane's UpdateMenus()
     **  method takes care of doing the work.
     **
     **  For Font and Size menus, you want all the items to
     **  be enabled all the time. In other words, you don't
     **  want the bartender to ever dim any of the items
     **  in these two menus.
     **
     **/

  gBartender->SetDimOption( MENUstyle, dimNONE );
    gBartender->SetDimOption( MENUmyfont, dimNONE );
    gBartender->SetDimOption( MENUmysize, dimNONE );

  gBartender->SetDimOption( MENUsetUp, dimNONE );
    gBartender->SetDimOption( MENUscaling, dimNONE );

  gBartender->SetDimOption( MENUobjects, dimNONE );
    gBartender->SetDimOption( MENUnodes, dimNONE );
    gBartender->SetDimOption( MENUstructrualElements, dimNONE );
      gBartender->SetDimOption( MENUwoodElements, dimNONE );
    gBartender->SetDimOption( MENUloads, dimNONE );
    gBartender->SetDimOption( MENUmoments, dimNONE );
    gBartender->SetDimOption( MENUalign, dimNONE );

  gBartender->SetDimOption( MENUanalysis, dimNONE );

  gBartender->SetDimOption( MENUresults, dimNONE );
    gBartender->SetDimOption( MENUshowStructure, dimNONE );
    gBartender->SetDimOption( MENUshowElement, dimNONE );

    /**
     **  For Font and Size menus, one of the items
     **  is always checked. Setting the unchecking option
     **  to TRUE lets the bartender know that it should
     **  uncheck all the menu items because an UpdateMenus()
     **  method will check the right items.
     **  For the Style menu, uncheck all the items and
     **  let the edit pane's UpdateMenus() method check the
     **  appropriate ones.
     **
     **/

  gBartender->SetUnchecking(MENUmyfont, TRUE);
  gBartender->SetUnchecking(MENUmysize, TRUE);
  gBartender->SetUnchecking(MENUstyle, TRUE);
}

