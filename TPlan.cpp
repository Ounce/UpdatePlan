//---------------------------------------------------------------------------

#pragma hdrstop

#include "TPlan.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
void __fastcall TPlan::Clear(void) {
    Arcs.clear();
    Lines.clear();
}

//---------------------------------------------------------------------------
double __fastcall TPlan::GetWidth(void) {
    return abs(MaxX - MinX);
}

//---------------------------------------------------------------------------

double __fastcall TPlan::GetHeight(void) {
    return abs(MaxY - MinY);
}

//---------------------------------------------------------------------------
double __fastcall TPlan::GetScale(TImage * Image) {
    double s1 = Image->Width / GetWidth();
    double s2 = Image->Height / GetHeight();
    return (s1 > s2) ? s2 : s1;
}

//---------------------------------------------------------------------------
void __fastcall TPlan::Draw(TImage * Image) {
	SetMaxMin();
    double Scale = GetScale(Image);
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
    OriginX = MinX;
    OriginY = MinY;
    return;
}

