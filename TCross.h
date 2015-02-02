//---------------------------------------------------------------------------

#ifndef TCrossH
#define TCrossH

#include "Comm.h"
#include "TLine.h"
#include "TSwitch.h"

//---------------------------------------------------------------------------
enum eLinePos {lpNONE, lpSTART, lpMIDDLE, lpEND };
enum eLineType {ltUNKNOW, ltMAIN, ltBRANCH};

//---------------------------------------------------------------------------
class CrossAngle {
public:
	double Angle;
    int FrogNumber;
};

//---------------------------------------------------------------------------
class CrossAngleList : public vector<CrossAngle> {
public:
	__fastcall CrossAngleList();
};

//---------------------------------------------------------------------------
class TCrossLine : public TLine {
public:
	eLinePos Pos;
    TLine * ptr;
    eLineType Type;
    TCrossLine & __fastcall operator = (TLine * Line);
private:
};

//---------------------------------------------------------------------------
class TCross {
public:
	double X, Y;
    double MinAngle, MaxAngle;
    int MinAngleA, MinAngleB, MaxAngleA, MaxAngleB;
    int FrogNumber, MainLineNumber;
    eSwitchType Type;
    vector<TCrossLine> Lines;
	void __fastcall AddLine(eLinePos Pos, TLine * Line);
    void __fastcall UpdateAngle(void);
	void __fastcall Draw(TImage * Image, const double Scale, const double OriginX, const double OriginY);
private:
	void __fastcall SetSimpleSwitchType(const eBranchSide BranchSide);
};

//---------------------------------------------------------------------------
class TCrosses : public vector<TCross> {
public:
	void __fastcall Draw(TImage * Image, const double Scale, const double OriginX, const double OriginY);
};
#endif
