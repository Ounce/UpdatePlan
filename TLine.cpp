//---------------------------------------------------------------------------

#pragma hdrstop

#include "TLine.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TLine::TLine() {
	StartSign = false;
	EndSign = false;
}
//---------------------------------------------------------------------------

void __fastcall TLine::ClearSign(void) {
	StartSign = false;
	EndSign = false;
	return;
}
//---------------------------------------------------------------------------

void __fastcall TLine::Draw(TImage * Image, double Scale, double OriginX, double OriginY) {
    Image->Canvas->MoveTo(Scale * (StartX - OriginX), Image->Height - Scale * (StartY - OriginY));
    Image->Canvas->LineTo(Scale * (EndX - OriginX), Image->Height - Scale * (EndY - OriginY));
    return;
}
//---------------------------------------------------------------------------
void __fastcall TLines::ClearSign(void) {
    for (int i = 0; i < size(); i++) {
        at(i).ClearSign();
    }
    return;
}
//---------------------------------------------------------------------------
