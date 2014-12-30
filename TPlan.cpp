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

