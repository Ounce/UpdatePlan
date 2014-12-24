//---------------------------------------------------------------------------

#ifndef TArcH
#define TArcH
//---------------------------------------------------------------------------

#include <vcl.h>
#include "TVector.h"

class TArc {
public:
	double CenterX, CenterY, StartX, StartY, EndX, EndY;
    double Radii;
    double StartAngle, SweepAngle;

	void __fastcall Draw(TImage * Image, double Scale, double OriginX, double OriginY);
};
//---------------------------------------------------------------------------

class TArcs : public Vector<TArc> {
};
//---------------------------------------------------------------------------

#endif
