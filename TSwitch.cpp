//---------------------------------------------------------------------------

#pragma hdrstop

#include "TSwitch.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void __fastcall TSwitch::AddLine(eLinePos Pos, TLine * Line) {
    TSwitchLine sl;
    sl.Pos = Pos;
    sl.ptr = Line;
    Lines.push_back(sl);
    return;
}

//---------------------------------------------------------------------------
void __fastcall TSwitch::UpdateAngle(void) {
	int i, j, m = -1;
    double a = 90;
	for (i = 0; i < Lines.size(); i++) {
		if (InRange(X, Y, Lines[i].ptr->StartX, Lines[i].ptr->StartY, 1)) {
            Lines[i].ptr->Angle = Lines[i].ptr->StartAngle;
        } else if (InRange(X, Y, Lines[i].ptr->EndX, Lines[i].ptr->EndY, 1)) {
        	Lines[i].ptr->Angle = OppositeAngle(Lines[i].ptr->StartAngle);
        }
        if (Lines[i].Pos == lpMIDDLE) m = i;
    }
    j = (m - 1 < 0) ? m + 1 : m - 1;
    if (fabs(Lines[m].ptr->StartAngle - Lines[j].ptr->Angle) > 90) {
       	Lines[m].ptr->Angle = Lines[m].ptr->StartAngle;
    } else {
        Lines[m].ptr->Angle = OppositeAngle(Lines[m].ptr->StartAngle);
    }
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
