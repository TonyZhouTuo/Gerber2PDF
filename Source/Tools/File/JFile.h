//==============================================================================
// Copyright (C) John-Philip Taylor
// jpt13653903@gmail.com
//
// This file is part of a library
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

#ifndef JFile_H
#define JFile_H
//---------------------------------------------------------------------------

#if defined(__WIN64__) || defined(__WIN32__)
  #if !defined(NTDDI_VERSION) || !defined(WINVER) || !defined(_WIN32_WINNT)
    #define  NTDDI_VERSION 0x05010000 // Windown XP
    #define  WINVER        0x0501     // Windown XP
    #define _WIN32_WINNT   WINVER     // Windown XP
  #endif

  #include <windows.h>

#else
  #error JFile.cpp/h is platform dependant, \
         please create an implimentation for your platform
#endif
//---------------------------------------------------------------------------

#include "JString.h"
//---------------------------------------------------------------------------

class JFile{
  public:
    enum ACCESS{
      Read        = 0,
      Write       = 1,
      Create      = 2,
      WriteDevice = 3
    };
//---------------------------------------------------------------------------

  private:
    ACCESS  CurrentAccess;
    HANDLE  Handle;
    JString Filename;
//---------------------------------------------------------------------------

    bool LineInput(JString*    s);
    bool LinePrint(const char* s);
//---------------------------------------------------------------------------

  public:
    JFile();
   ~JFile();

    int  FormatLastError(JString*    Error);
    void ShowLastError  ();
    bool Open           (ACCESS      Access);
    bool ReadLine       (JString*    Line);
    bool WriteLine      (const char* Value);

    unsigned long ReadBuffer(
      char*         Buffer,
      unsigned long MustRead,
      bool*         Value
    );
    unsigned long WriteBuffer(
      const char*   Buffer,
      unsigned long MustWrite,
      bool*         Value
    );

    void Close();
//---------------------------------------------------------------------------

    char*       GetFilename  ();
    void        SetFilename  (const char* Value);
    long double GetSize      ();
    void*       GetFileHandle();
    long double GetPosition  ();
    void        SetPosition  (long double Value);
    bool        GetBusy      (void);
};
//---------------------------------------------------------------------------
#endif

