//---------------------------------------------------------------------------

#ifndef TSwitchH
#define TSwitchH

#include "TLine.h"

//---------------------------------------------------------------------------
enum eLinePos {lpSTART, lpMiddle, lpEND };

class TSwitchLine {
public:
	eLinePos Pos;
    TLine * Line;
};

class TSwitch {
public:
	double X, Y;
    vector<TSwitchLine> Lines;
	void __fastcall AddLine(eLinePos Pos, TLine * Line);
	void __fastcall Draw(TImage * Image, const double Scale, const double OriginX, const double OriginY);
};

class TSwitches : public vector<TSwitch> {
public:
	void __fastcall Draw(TImage * Image, const double Scale, const double OriginX, const double OriginY);
};
#endif
