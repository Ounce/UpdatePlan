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
