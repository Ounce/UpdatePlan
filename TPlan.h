//---------------------------------------------------------------------------

#ifndef TPlanH
#define TPlanH
//---------------------------------------------------------------------------

#include "Comm.h"
#include "TArc.h"
#include "TLine.h"
#include "TCross.h"

class TPlan {
public:
    double OriginX, OriginY;	// TImage基点（左下角）在Plan中的位置。
    double Scale;
	TArcs Arcs;
    TLines Lines;
    TCrosses Crosses;
    __fastcall TPlan();
    void __fastcall SetOrigin(TImage * Image);
    void __fastcall Clear(void);
    void __fastcall DistinguishSwitches(void);
	void __fastcall Draw(TImage * Image);
	void __fastcall DrawSwitches(TImage * Image);
private:
	double MaxX, MaxY, MinX, MinY, Width, Height;
    void __fastcall SetMaxMin(void);
	eLinePos __fastcall OnLine(const double x, const double y, TLine * Line);
};
#endif
