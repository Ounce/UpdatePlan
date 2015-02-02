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
TCrossLine & __fastcall TCrossLine::operator = (TLine * Line) {
	StartX = Line->StartX;
    StartY = Line->StartY;
    EndX = Line->EndX;
    EndY = Line->EndY;
    Length = Line->Length;
    StartAngle = Line->StartAngle;
	Angle = Line->Angle;
    StartSign = Line->StartSign;
    EndSign = Line->EndSign;
    ptr = Line;
}

//---------------------------------------------------------------------------
void __fastcall TCross::AddLine(eLinePos Pos, TLine * Line) {
    TCrossLine sl;
    sl = Line;
    sl.Pos = Pos;
    Lines.push_back(sl);
    return;
}

//---------------------------------------------------------------------------
void __fastcall TCross::UpdateAngle(void) {
	int i, j, m = -1;
    double a = 90;
    CrossAngleList AngleList;     //转辙角列表
    TSwitchList SwitchList;
    int BranchLineNumber = -1;
    MainLineNumber = -1;
    eBranchSide BranchSide;
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
    	if (fabs(Lines[MainLineNumber].ptr->StartAngle - Lines[j].Angle) > 90) {
       		Lines[MainLineNumber].Angle = Lines[MainLineNumber].ptr->StartAngle;
	    } else {
    	    Lines[MainLineNumber].Angle = OppositeAngle(Lines[MainLineNumber].ptr->StartAngle);
	    }
    }
    MaxAngle = MinAngle = GetAngle(Lines[0].Angle, Lines[1].Angle);       //查找最大、最小角度
    MaxAngleA = MaxAngleB = MinAngleA = MinAngleB = -1;
    for (i = 0; i < Lines.size(); i++) {
        for (j = i + 1; j < Lines.size(); j++) {
        	a = GetAngle(Lines[i].Angle, Lines[j].Angle);
            if (a > MaxAngle) {
                MaxAngle = a;
                MaxAngleA = i;
                MaxAngleB = j;
            } else if (a < MinAngle) {
            	MinAngle = a;
                MinAngleA = i;
                MinAngleB = j;
            }
        }
    }
    for (i = 0; i < AngleList.size(); i++) {          //根据最小角查找对应的辙岔号。 —— 可能不用了。可以根据最小角进行判断。
        if (EqualAngle(MinAngle, AngleList[i].Angle)) {
        	FrogNumber = AngleList[i].FrogNumber;
            break;
        }
    }
    if (MainLineNumber < 0) {
		if (MaxAngleA == MinAngleA || MaxAngleA == MinAngleB) {		// 判断MainLineNumber
    	    MainLineNumber = MaxAngleB;
	    } else if (MaxAngleB == MinAngleB || MaxAngleB == MinAngleA) {
    		MainLineNumber = MaxAngleA;
	    } else {
    		Type = NoSwitch;
        	return;
	    }
    }
    switch (Lines.size()) {        //判断道岔类型
    	case 2:
        	if (MainLineNumber > -1) {          //单开道岔，直向和a值为一个线段。
                SetSimpleSwitchType(GetBranchSide(Lines[MainLineNumber].Angle, Lines[1 - MainLineNumber].Angle));
            }
            Type = NoSwitch;
            break;
        case 3:
        	if (EqualAngle(MaxAngle, 180)) {         //单开道岔
            	BranchSide = GetBranchSide(Lines[MainLineNumber].Angle, Lines[MinAngleA].Angle);
            	SetSimpleSwitchType(BranchSide);
                if (Type == NoSwitch) {
                	BranchSide = GetBranchSide(Lines[MainLineNumber].Angle, Lines[MinAngleB].Angle);
            		SetSimpleSwitchType(BranchSide);
                }
            } else if (Lines[MaxAngleA].ptr->pos == lpMIDDLE || Lines[MaxAngleB].ptr->pos == lpMIDDLE) {
            	Type = Treble;
            } else {
                Type = Symmetry;
            }
        	break;
        case 4:
        	Type = Treble;
            break;
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
void __fastcall TCross::SetSimpleSwitchType(const eBranchSide BranchSide) {
    switch (BranchSide) {
		case bsLEFT:
        	Type = SimpleLeft;     //左侧单开道岔
            break;
         case bsRIGHT:
         	Type = SimpleRight;
            break;
         default:
         	Type = NoSwitch;
            break;
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


