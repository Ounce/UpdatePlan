//---------------------------------------------------------------------------

#pragma hdrstop

#include "TLine.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void __fastcall TLine::Draw(TImage * Image, double Scale, double OriginX, double OriginY) {
    Image->Canvas->MoveTo(Scale * (StartX - OriginX), Scale * (StartY - OriginY));
    Image->Canvas->LineTo(Scale * (EndX - OriginX), Scale * (EndY - OriginY));
    return;
}
//---------------------------------------------------------------------------
