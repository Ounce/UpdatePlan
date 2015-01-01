//---------------------------------------------------------------------------

#pragma hdrstop

#include "TSwitch.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void __fastcall TSwitch::AddLine(eLinePos Pos, TLine * Line) {
    TSwitchLine sl;
    sl.Pos = Pos;
    sl.Line = Line;
    Lines.push_back(sl);
    return;
}

//---------------------------------------------------------------------------
void __fastcall TSwitch::Draw(TImage * Image, const double Scale, const double OriginX, const double OriginY) {
	for (int i = 0; i < Lines.size(); i++) {
		Lines[i].Line->Draw(Image, Scale, OriginX, OriginY);
	}
	return;
}

//---------------------------------------------------------------------------
void __fastcall TSwitches::Draw(TImage * Image, const double Scale, const double OriginX, const double OriginY) {
	Image->Canvas->Pen->Color = clRed;
	for (int i = 0; i < size(); i++) {
		at(i).Draw(Image, Scale, OriginX, OriginY);
	}
	return;
}
