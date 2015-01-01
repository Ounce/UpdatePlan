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
	TSwitch StartSwitch, EndSwitch;
	Switches.clear();
    for (i = 0; i < Lines.size(); i++) {
    	if (Lines[i].StartSign && Lines[i].EndSign) continue;
        StartSwitch.Lines.clear();
		EndSwitch.Lines.clear();
    	for (j = i + 1; j < Lines.size(); j++) {
        	if (!Lines[i].StartSign) {
	        	if (!Lines[j].StartSign && InRange(Lines[i].StartX, Lines[i].StartY, Lines[j].StartX, Lines[j].StartY, 1)) {
					Lines[j].StartSign = true;
        	    	StartSwitch.AddLine(lpSTART, &Lines[j]);
				} else if (!Lines[j].EndSign && InRange(Lines[i].StartX, Lines[i].StartY, Lines[j].EndX, Lines[j].EndY, 1)) {
					Lines[j].EndSign = true;
	                StartSwitch.AddLine(lpEND, &Lines[j]);
                }
			} else if (!Lines[i].EndSign) {
            	if (!Lines[j].StartSign && InRange(Lines[i].EndX, Lines[i].EndY, Lines[j].StartX, Lines[j].StartY, 1)) {
					Lines[j].StartSign = true;
                    EndSwitch.AddLine(lpSTART, &Lines[j]);
				} else if (!Lines[j].EndSign && InRange(Lines[i].EndX, Lines[i].EndY, Lines[j].EndX, Lines[j].EndY, 1)) {
                	Lines[j].EndSign = true;
                    EndSwitch.AddLine(lpEND, &Lines[j]);
                }
            }
        }
		if (!StartSwitch.Lines.empty()) {
			Lines[i].StartSign = true;
			StartSwitch.AddLine(lpSTART, &Lines[i]);
			Switches.push_back(StartSwitch);
		}
		if (!EndSwitch.Lines.empty()) {
			Lines[i].EndSign = true;
            EndSwitch.AddLine(lpEND, &Lines[i]);
            Switches.push_back(EndSwitch);
        }
    }
    return;
}

//---------------------------------------------------------------------------
bool __fastcall TPlan::InRange(const double x, const double y, const double X, const double Y, const double R) {
	double dx = X - x;
    double dy = Y - y;
    if (dx * dx + dy * dy < R * R)
        return true;
    else
    	return false;
}
