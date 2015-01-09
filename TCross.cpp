//---------------------------------------------------------------------------

#pragma hdrstop

#include "TCross.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall CrossAngleList::CrossAngleList() {
	CrossAngle sa;
    sa.Angle = 9.462222;
    sa.FrogNumber = 6;
    push_back(sa);

    sa.Angle = 6.340278;
    sa.FrogNumber = 9;
    push_back(sa);

    sa.Angle = 8.13;
    sa.FrogNumber = 7;
    push_back(sa);

    sa.Angle = 8.079494;
    sa.FrogNumber = 65;
    push_back(sa);
}

//---------------------------------------------------------------------------
void __fastcall TCross::AddLine(eLinePos Pos, TLine * Line) {
    TCrossLine sl;
    sl.Pos = Pos;
    sl.ptr = Line;
    Lines.push_back(sl);
    return;
}

//---------------------------------------------------------------------------
void __fastcall TCross::UpdateAngle(void) {
	int i, j, m = -1;
    double a = 90;
    CrossAngleList AngleList;
    MainLineNumber = -1;
	for (i = 0; i < Lines.size(); i++) {
		if (InRange(X, Y, Lines[i].ptr->StartX, Lines[i].ptr->StartY, 1)) {
            Lines[i].ptr->Angle = Lines[i].ptr->StartAngle;
        } else if (InRange(X, Y, Lines[i].ptr->EndX, Lines[i].ptr->EndY, 1)) {
        	Lines[i].ptr->Angle = OppositeAngle(Lines[i].ptr->StartAngle);
        }
        if (Lines[i].Pos == lpMIDDLE) {
        	MainLineNumber = i;
            Lines[i].Type = ltMAIN;
        }
    }
    if (MainLineNumber > -1) {                      //如果有lpMIDDLE，设置其角度。
	    j = (MainLineNumber - 1 < 0) ? MainLineNumber + 1 : MainLineNumber - 1;
    	if (fabs(Lines[MainLineNumber].ptr->StartAngle - Lines[j].ptr->Angle) > 90) {
       		Lines[MainLineNumber].ptr->Angle = Lines[MainLineNumber].ptr->StartAngle;
	    } else {
    	    Lines[MainLineNumber].ptr->Angle = OppositeAngle(Lines[MainLineNumber].ptr->StartAngle);
	    }
    }
    MaxAngle = MinAngle = GetAngle(Lines[0].ptr->Angle, Lines[1].ptr->Angle);       //查找最大、最小角度
    MaxAngleA = MaxAngleB = MinAngleA = MinAngleB = -1;
    for (i = 0; i < Lines.size(); i++) {
        for (j = i + 1; j < Lines.size(); j++) {
        	a = GetAngle(Lines[i].ptr->Angle, Lines[j].ptr->Angle);
            if (a > MaxAngle) {
                MaxAngle = a;
                MaxAngleA = i;
                MaxAngleB = j;
            }
            if (a < MinAngle) {
            	MinAngle = a;
                MinAngleA = i;
                MinAngleB = j;
            }
        }
    }
    for (i = 0; i < AngleList.size(); i++) {          //根据最小角查找对应的辙岔号。
        if (EqualAngle(MinAngle, AngleList[i].Angle)) {
        	FrogNumber = AngleList[i].FrogNumber;
            break;
        }
    }
    switch (Lines.size()) {
    	case 2:
        	if (MainLineNumber > -1) {          //单开道岔，直向和a值为一个线段。
            	m = 1 - MainLineNumber;
                switch (GetBranchSide(Lines[MainLineNumber].ptr->Angle, Lines[m].ptr->Angle)) {
                    case bsLEFT:
                    	//左侧单开道岔
                }
            }

    default:
        ;
    }
    return;
}

//---------------------------------------------------------------------------
void __fastcall TCross::Draw(TImage * Image, const double Scale, const double OriginX, const double OriginY) {
	for (int i = 0; i < Lines.size(); i++) {
		Lines[i].ptr->Draw(Image, Scale, OriginX, OriginY);
	}
	return;
}

//---------------------------------------------------------------------------
void __fastcall TCrosses::Draw(TImage * Image, const double Scale, const double OriginX, const double OriginY) {
	Image->Canvas->Pen->Color = clRed;
	for (int i = 0; i < size(); i++) {
		at(i).Draw(Image, Scale, OriginX, OriginY);
	}
	return;
}
