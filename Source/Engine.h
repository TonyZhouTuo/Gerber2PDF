//==============================================================================
// Copyright (C) John-Philip Taylor
// jpt13653903@gmail.com
//
// This file is part of Gerber2PDF
//
// This file is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>
//==============================================================================

#ifndef Engine_h
#define Engine_h
//------------------------------------------------------------------------------

#ifdef __linux__
  #include <unistd.h>
#endif
//------------------------------------------------------------------------------

#include "JPDF.h"
#include "JGerber.h"
//------------------------------------------------------------------------------

struct ENGINE{
  public: // Externally-controlled mode
    enum PAGE_SIZE{
      PS_Tight = 0,
      PS_Extents,
      PS_A3,
      PS_A4,
      PS_Letter
    } PageSize;

    bool Mirror;
    bool Combine;
    bool NewPage;
    bool Negative;

    struct COLOUR{
      double R, G, B, A;
      COLOUR();
    } Light, Dark;

    bool ConvertStrokesToFills;
//------------------------------------------------------------------------------

  private: // Internal structures
    int OpaqueCount;
    struct OPAQUE_STACK{
      pdfOpaque*    Opaque;
      OPAQUE_STACK* Next;

      OPAQUE_STACK(double Value, int& OpaqueCount);
     ~OPAQUE_STACK();
    };
    OPAQUE_STACK* OpaqueStack;

    struct APERTURE{
      pdfForm*  Aperture;
      APERTURE* Next;
    };

    struct LEVEL_FORM{
      pdfForm*    Level;
      LEVEL_FORM* Next;

      LEVEL_FORM();
     ~LEVEL_FORM();
    };

    struct LAYER{
      char*    Filename;
      pdfForm* Form;
      LAYER*   Next;

      bool    Negative;
      double  Left, Bottom, Right, Top;
      JString Title;

      LAYER();
     ~LAYER();
    };
    LAYER* Layers; // Stack of layer XObjects
//------------------------------------------------------------------------------

  private: // Internal State
    JPDF pdf;

    APERTURE* ApertureStack;
    APERTURE* TempApertureStack;

    int      ApertureCount;
    pdfForm* Apertures[1000];
    pdfForm* CurrentAperture;

    pdfOpaque* Opaque;

    bool   SolidCircle;
    bool   SolidRectangle;
    bool   OutlinePath;
    double LineWidth;
    double RectW;
    double RectH;
    double RectX;
    double RectY;

    int     PageCount;
    int     Result;
    bool    ThePageUsed;
    double  ThePageLeft;
    double  ThePageBottom;
    double  ThePageRight;
    double  ThePageTop;

    // PDF Variables and Structures
    pdfPages    Pages;    // Single level page tree
    pdfOutlines Outlines; // Single level outline tree

    LEVEL_FORM* LevelStack;
    int         LevelCount;

    pdfPage*         Page;        // Page for each gerber file
    pdfPage*         ThePage;     // Page on which to combine outputs
    pdfContents*     Contents;    // Contents for each page
    pdfContents*     TheContents; // Contents of ThePage
    pdfOutlineItems* Outline;     // Outline item for each page

    int PageIndex;
    int PageAllocationCount;
//------------------------------------------------------------------------------

  private: // Functions
    void DrawAperture(
      pdfContents*  Contents,
      GerberRender* Render,
      double Left,
      double Bottom,
      double Right,
      double Top
    );
    void DrawRectLine(
      pdfContents* Contents,
      double x1, double y1, // Start
      double x2, double y2, // End
      double w , double h   // Rect Width; Height
    );
    int RenderLayer(
      pdfForm*     Form,
      pdfContents* Contents,
      GerberLevel* Level
    );
    LAYER* NewLayer (const char* Filename);
    LAYER* FindLayer(const char* Filename);
//------------------------------------------------------------------------------

  public: // Functions
    // NumPages is an estimate -- set to the maximum anticipated count
    ENGINE(int NumPages);
   ~ENGINE();

    // Call Run for each Gerber file in the list, then call Finish once
    int  Run   (const char* FileName, const char* Title);
    void Finish(const char* OutputFileName);
};
//------------------------------------------------------------------------------

#endif
//------------------------------------------------------------------------------
