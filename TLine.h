//---------------------------------------------------------------------------

#ifndef TLineH
#define TLineH
//---------------------------------------------------------------------------

#include "TVector.h"

class TLine {
public:
	double StartX, StartY, EndX, EndY, Length;
    bool StartSign, EndSign;
    void __fastcall ClearSign(void);
    void __fastcall Draw(TImage * Image, double Scale, double OriginX, double OriginY);
};
//---------------------------------------------------------------------------

class TLines : public Vector<TLine> {
	void __fastcall ClearSign(void);
};
//---------------------------------------------------------------------------

#endif
