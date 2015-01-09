//---------------------------------------------------------------------------

#ifndef TSwitchH
#define TSwitchH

#include "Comm.h"
#include "TLine.h"

//---------------------------------------------------------------------------
enum eLinePos {lpNONE, lpSTART, lpMIDDLE, lpEND };
enum eLineType {ltUNKNOW, ltMAIN, ltBRANCH};

class TSwitchLine {
public:
	eLinePos Pos;
    eLineType Type;
    TLine * ptr;
};

class TSwitch {
public:
	double X, Y;
    vector<TSwitchLine> Lines;
	void __fastcall AddLine(eLinePos Pos, TLine * Line);
    void __fastcall UpdateAngle(void);
	void __fastcall Draw(TImage * Image, const double Scale, const double OriginX, const double OriginY);
};

class TSwitches : public vector<TSwitch> {
public:
	void __fastcall Draw(TImage * Image, const double Scale, const double OriginX, const double OriginY);
};
#endif
