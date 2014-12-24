//---------------------------------------------------------------------------

#ifndef TPlanH
#define TPlanH
//---------------------------------------------------------------------------

#include "TArc.h"
#include "TLine.h"

class TPlan {
public:
	TArcs Arcs;
    TLines Lines;
    void __fastcall Clear(void);
    void __fastcall Draw(TImage * Image);

private:
	double MaxX, MaxY, MinX, MinY, OriginX, OriginY;
	double __fastcall GetScale(TImage * Image);
    double __fastcall GetWidth(void);
    double __fastcall GetHeight(void);
    void __fastcall SetMaxMin(void);
};
#endif
