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

#include "JPDF.h"
//------------------------------------------------------------------------------

JPDF::JPDF(){
  First = Last = 0;

  Info.Object = new pdfDictionary;
  AddIndirect(&Info);
  AddIndirect(&Catalogue);
}
//------------------------------------------------------------------------------

JPDF::~JPDF(){
  delete Info.Object;

  while(First){
    Last  = First;
    First = First->Next;
    delete Last;
  }
}
//------------------------------------------------------------------------------

void JPDF::AddIndirect(pdfIndirect* Indirect){
  Element* Temp = new Element;

  Temp->Object = Indirect;
  Temp->Next   = 0;

  if(First){
    Temp->Object->Reference = Last->Object->Reference+1;
    Last->Next = Temp;
  }else{
    Temp->Object->Reference = 1;
    First = Temp;
  }
  Last = Temp;
}
//------------------------------------------------------------------------------

void JPDF::AddType1Font(pdfType1Font* Font){
  AddIndirect(  Font);
  AddIndirect(&(Font->Widths));
  AddIndirect(&(Font->FontDescriptor));
  AddIndirect(&(Font->FontDescriptor.FontFile));
}
//------------------------------------------------------------------------------

void JPDF::AddType3Font(pdfType3Font* Font){
  Font->SetWidths();
  Font->SetEncoding();

  AddIndirect(  Font);
  AddIndirect(&(Font->Widths   ));
  AddIndirect(&(Font->Encoding ));
  AddIndirect(&(Font->CharProcs));
}
//------------------------------------------------------------------------------

static void GetXRefEntry(char* Buffer, unsigned Offset, unsigned GN){
  int j;
  for(j = 9; j >= 0; j--){
    Buffer[j] = (Offset % 10) + '0';
    Offset   /= 10;
  }
  for(j = 15; j >= 11; j--){
    Buffer[j] = (GN % 10) + '0';
    GN       /= 10;
  }
}
//------------------------------------------------------------------------------

void JPDF::WritePDF(const char* FileName){
  int            BufferLength = 20;
  int            Length;
  bool           b;
  char*          Buffer = new char[20];
  unsigned       FilePointer = 0;
  Element*       Temp;
  pdfNumber      Size;
  pdfNumber      StartRef;
  pdfDictionary  Trailer;
  pdfDictionary* d = (pdfDictionary*)Info.Object;

  d->Clear();
  pdfName Type;
  Type.Set("Info");
  if(!Type        .Empty()) d->AddEntry("Type"        , &Type);
  if(!Title       .Empty()) d->AddEntry("Title"       , &Title);
  if(!Author      .Empty()) d->AddEntry("Author"      , &Author);
  if(!Subject     .Empty()) d->AddEntry("Subject"     , &Subject);
  if(!Keywords    .Empty()) d->AddEntry("Keywords"    , &Keywords);
  if(!Creator     .Empty()) d->AddEntry("Creator"     , &Creator);
  if(!Producer    .Empty()) d->AddEntry("Producer"    , &Producer);
  if(!CreationDate.Empty()) d->AddEntry("CreationDate", &CreationDate);

  if(Last){
    Size.Value = Last->Object->Reference+1;
  }else{
    Size.Value = 1;
  }

  File.SetFilename(FileName);
  if(File.Open(JFile::Create)){
    // Header
    FilePointer += File.WriteBuffer("%" PDF_Version "\n", 9, &b);
    FilePointer += File.WriteBuffer("%\x85\x9A\xF0\xC7\n", 6, &b);

    // Body
    Temp = First;
    while(Temp){
      Temp->Offset = FilePointer;
      Length = Temp->Object->GetBodyLength();
      if(Length > BufferLength){
        delete[] Buffer;
        Buffer = new char[Length];
        BufferLength = Length;
      }
      Temp->Object->GetBody(Buffer);
      FilePointer += File.WriteBuffer(Buffer, Length, &b);
      Temp = Temp->Next;
    }

    //XRef
    StartRef.Value = FilePointer;
    FilePointer += File.WriteBuffer("xref\n", 5, &b);

    pdfNumber n;
    n.Value = Last->Object->Reference+1;
    FilePointer += File.WriteBuffer("0 ", 2, &b);
    Length = n.GetLength();
    if(Length > BufferLength){
      delete[] Buffer;
      Buffer = new char[Length];
      BufferLength = Length;
    }
    n.GetOutput(Buffer);
    FilePointer += File.WriteBuffer(Buffer, Length, &b);
    FilePointer += File.WriteBuffer("\n", 1, &b);

    Buffer[10] = ' ';
    Buffer[16] = ' ';
    Buffer[17] = 'f';
    Buffer[18] = ' ';
    Buffer[19] = '\n';

    GetXRefEntry(Buffer, 0, 65535);
    FilePointer += File.WriteBuffer(Buffer, 20, &b);

    Buffer[17] = 'n';
    Length = 20;
    Temp = First;
    while(Temp){
      GetXRefEntry(Buffer, Temp->Offset, 0);
      FilePointer += File.WriteBuffer(Buffer, 20, &b);
      Temp = Temp->Next;
    }

    // Trailer________________________________________
                      Trailer.AddEntry("Size", &Size);
                      Trailer.AddEntry("Root", &Catalogue);
    if(d->GetCount()) Trailer.AddEntry("Info", &Info);

    FilePointer += File.WriteBuffer("trailer\n", 8, &b);
    Length = Trailer.GetLength();
    if(Length > BufferLength){
      delete[] Buffer;
      Buffer = new char[Length];
      BufferLength = Length;
    }
    Trailer.GetOutput(Buffer);
    FilePointer += File.WriteBuffer(Buffer, Length, &b);
    FilePointer += File.WriteBuffer("\nstartxref\n", 11, &b);
    Length = StartRef.GetLength();
    if(Length > BufferLength){
      delete[] Buffer;
      Buffer = new char[Length];
      BufferLength = Length;
    }
    StartRef.GetOutput(Buffer);
    FilePointer += File.WriteBuffer(Buffer, Length, &b);
    FilePointer += File.WriteBuffer("\n%%EOF\n", 7, &b);
    File.Close();
  }else{
    File.ShowLastError();
  }

  delete[] Buffer;
}
//------------------------------------------------------------------------------
