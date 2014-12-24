//---------------------------------------------------------------------------

#ifndef TLineH
#define TLineH
//---------------------------------------------------------------------------

#include "TVector.h"

class TLine {
public:
	double StartX, StartY, EndX, EndY;
    void __fastcall Draw(TImage * Image, double Scale, double OriginX, double OriginY);
};
//---------------------------------------------------------------------------

class TLines : public Vector<TLine> {
};
//---------------------------------------------------------------------------

#endif
