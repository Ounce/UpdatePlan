//---------------------------------------------------------------------------

#ifndef TLineH
#define TLineH
//---------------------------------------------------------------------------

#include "TVector.h"

class TLine {
public:
	double StartX, StartY, EndX, EndY, Length, StartAngle, Angle;
	bool StartSign, EndSign;
	__fastcall TLine();
    void __fastcall ClearSign(void);
    void __fastcall Draw(TImage * Image, double Scale, double OriginX, double OriginY);
};
//---------------------------------------------------------------------------

class TLines : public Vector<TLine> {
	void __fastcall ClearSign(void);
};
//---------------------------------------------------------------------------

#endif
