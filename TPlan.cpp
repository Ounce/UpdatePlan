//---------------------------------------------------------------------------

#pragma hdrstop

#include "TPlan.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall TPlan::TPlan() {
}

//---------------------------------------------------------------------------
void __fastcall TPlan::Clear(void) {
    Arcs.clear();
    Lines.clear();
    return;
}

//---------------------------------------------------------------------------
void __fastcall TPlan::SetOrigin(TImage * Image) {
	SetMaxMin();
    double s1 = Image->Width / Width;
    double s2 = Image->Height / Height;
    if (s1 < s2) {	//图的X方向大于Y方向，即长度大于高度。
    	Scale = s1;
        OriginX = MinX;
        OriginY = MinY - (Image->Height / Scale - Height) * 0.5;
    } else {
        Scale = s2;
        OriginX = MinX - (Image->Width / Scale - Width) * 0.5;
        OriginY = MinY;
    }
    return;
}

//---------------------------------------------------------------------------
void __fastcall TPlan::Draw(TImage * Image) {
	SetOrigin(Image);
    Arcs.Draw(Image, Scale, OriginX, OriginY);
    Lines.Draw(Image, Scale, OriginX, OriginY);
    return;
}

//---------------------------------------------------------------------------
void __fastcall TPlan::DrawCrosses(TImage * Image) {
	Crosses.Draw(Image, Scale, OriginX, OriginY);
	return;
}

//---------------------------------------------------------------------------
void __fastcall TPlan::SetMaxMin(void) {
	Lines.SetMaxMin();
    Arcs.SetMaxMin();
	MaxX = (Lines.MaxX > Arcs.MaxX) ? Lines.MaxX : Arcs.MaxX;
    MinX = (Lines.MinX < Arcs.MinX) ? Lines.MinX : Arcs.MinX;
    MaxY = (Lines.MaxY > Arcs.MaxY) ? Lines.MaxY : Arcs.MaxY;
    MinY = (Lines.MinY < Arcs.MinY) ? Lines.MinY : Arcs.MinY;
    Width = abs(MaxX - MinX);
    Height = abs(MaxY - MinY);
    return;
}

//---------------------------------------------------------------------------
void __fastcall TPlan::DistinguishSwitches(void) {
	int i, j;
	eLinePos lp;
	TCross StartCross, EndCross;
	Crosses.clear();
	for (i = 0; i < Lines.size(); i++) {    //判断线段与线段的连接。
		if (Lines[i].Length < 5) continue;
		if (Lines[i].StartSign && Lines[i].EndSign) continue;
		StartCross.Lines.clear();
		EndCross.Lines.clear();
		for (j = i + 1; j < Lines.size(); j++) {
			if (Lines[j].Length < 5)continue;
			if (!Lines[i].StartSign) {
				lp = OnLine(Lines[i].StartX, Lines[i].StartY, &Lines[j]);
				switch (lp) {
					case lpSTART:
						Lines[j].StartSign = true;
						StartCross.AddLine(lp, &Lines[j]);
						break;
					case lpMIDDLE:
						StartCross.AddLine(lp, &Lines[j]);
						break;
					case lpEND:
						Lines[j].EndSign = true;
						StartCross.AddLine(lp, &Lines[j]);
						break;
					case lpNONE:
					default:
					;
				}
			}
			if (!Lines[i].EndSign) {
				lp = OnLine(Lines[i].EndX, Lines[i].EndY, &Lines[j]);
 				switch (lp) {
					case lpSTART:
						Lines[j].StartSign = true;
						EndCross.AddLine(lp, &Lines[j]);
						break;
					case lpMIDDLE:
						EndCross.AddLine(lp, &Lines[j]);
						break;
					case lpEND:
						Lines[j].EndSign = true;
						EndCross.AddLine(lp, &Lines[j]);
						break;
					case lpNONE:
					default:
					;
				}
            }
        }
		if (!StartCross.Lines.empty()) {
			Lines[i].StartSign = true;
            StartCross.X = Lines[i].StartX;
            StartCross.Y = Lines[i].StartY;
			StartCross.AddLine(lpSTART, &Lines[i]);
			Crosses.push_back(StartCross);
		}
		if (!EndCross.Lines.empty()) {
			Lines[i].EndSign = true;
            EndCross.X = Lines[i].EndX;
            EndCross.Y = Lines[i].EndY;
            EndCross.AddLine(lpEND, &Lines[i]);
            Crosses.push_back(EndCross);
        }
    }

    //删除非道岔
    for (i = Crosses.size() - 1; i > -1 ; i--) {
        if (Crosses[i].Lines.size() == 2) {
            if (Crosses[i].Lines[0].Pos != lpMIDDLE && Crosses[i].Lines[1].Pos != lpMIDDLE) {
                Crosses.erase(Crosses.begin() + i);
            }
        }
    }
    for (i = 0; i < Crosses.size(); i++) {
        Crosses[i].UpdateAngle();
    }                                              /*
    for (i = Crosses.size() - 1; i > -1; i--) {
        if (Crosses[i].Type == sNone) {
            Crosses.erase(Crosses.begin() + i);
        }
    }                                       */
    return;
}

//---------------------------------------------------------------------------
eLinePos __fastcall TPlan::OnLine(const double x, const double y, TLine * Line) {
	if (Line->Length < 5) return lpNONE;
	double xa = Line->EndX - Line->StartX;
	double ya = Line->EndY - Line->StartY;
	double xb = x - Line->StartX;
	double yb = y - Line->StartY;
	if (fabs(xa * yb - xb * ya) < 1 && min(Line->StartX, Line->EndX) <= x && x <= max(Line->StartX, Line->EndX) && min(Line->StartY, Line->EndY) <= y && y <= max(Line->StartY, Line->EndY)) {
		if (InRange(x, y, Line->StartX, Line->StartY, 1))
			return lpSTART;
		else if (InRange(x, y, Line->EndX, Line->EndY, 1))
			return lpEND;
		else
			return lpMIDDLE;

	} else
		return lpNONE;
}
