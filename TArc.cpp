//---------------------------------------------------------------------------

#pragma hdrstop

#include "TArc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void __fastcall TArc::Draw(TImage * Image, double Scale, double OriginX, double OriginY) {
    Image->Canvas->MoveTo(Scale * (StartX - OriginX), Image->Height - Scale * ( StartY - OriginY));
	Image->Canvas->AngleArc(Scale * (CenterX - OriginX), Image->Height - Scale * (CenterY - OriginY), Scale * Radii, StartAngle, SweepAngle);
    return;
}
//---------------------------------------------------------------------------

