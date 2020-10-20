/***
 * Draw
 *
 *  In this method, you draw whatever you need to display in
 *  your pane. The area parameter gives the portion of the
 *  pane that needs to be redrawn. Area is in frame coordinates.
 *
 ***/
#include "CTrussPane.phs"


        /***
         * perform draw for cluster redrawing
         */

        static void Perform_Draw( CAbstractObject *theObject )
        {
          PenPat( black );
          theObject->ReDraw();
        }

         /***
         * perform draw nodes  only for cluster redrawing
         */

        static void Perform_Draw_Nodes( CNodeObject  *theObject )
        {

          theObject->DrawNodeOnly();

        }



void CTrussPane::Draw(Rect *area)

{
  ContLoadsAndMoments->DoForEach( Perform_Draw );
  TElementsCluster->DoForEach( Perform_Draw );
  NodesCluster->DoForEach( Perform_Draw );
  ConcLoadsAndMoments->DoForEach( Perform_Draw );
  NodesCluster->DoForEach( Perform_Draw_Nodes );
}


void  CTrussPane::PrintPage(
  short    pageNum,        /* Number of the page to print    */
  short    pageWidth,        /* Width of printed page in pixels  */
  short    pageHeight)        /* Height of page in pixels      */
{
  Point    topOfPage;
  GrafPtr    savePort;
  long  pixWidth;
  long  pixHeight;
  long  numOfVertPages;
  long  numOfHorizPages;

                    /* Get dimensions of main pane  */
  GetPixelExtent(&pixWidth, &pixHeight);
                    /* Pages have a fixed pixel height  */
  numOfVertPages = pixHeight / pageHeight + 1;
  numOfHorizPages = pixWidth / pageWidth + 1;

  GetHomePosition(&topOfPage);

  topOfPage.h += ((pageNum - 1) / numOfVertPages)*(pageWidth / hScale);
  topOfPage.v += ((pageNum - 1) % numOfVertPages)*(pageHeight / vScale);

  GetPort(&savePort);
  ScrollTo(topOfPage, FALSE);
  SetPort(savePort);

  CPane::PrintPage(pageNum, pageWidth, pageHeight);
}

