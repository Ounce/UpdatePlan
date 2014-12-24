//---------------------------------------------------------------------------

#pragma hdrstop

#include "TArc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void __fastcall TArc::Draw(TImage * Image, double Scale, double OriginX, double OriginY) {
	Image->Canvas->AngleArc(Scale * (CenterX - OriginX), Scale * (CenterY - OriginY), Scale * Radii, StartAngle, SweepAngle);
    return;
}
//---------------------------------------------------------------------------

