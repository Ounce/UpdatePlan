//---------------------------------------------------------------------------

#ifndef TCrossH
#define TCrossH

#include "Comm.h"
#include "TLine.h"
#include "TSwitch.h"

//---------------------------------------------------------------------------
enum eLinePos {lpNONE, lpSTART, lpMIDDLE, lpEND};
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
    eBranchSide Type;
    TCrossLine & __fastcall operator = (TLine * Line);
    TCrossLine & __fastcall operator = (const TCrossLine & CrossLine);
    bool __fastcall operator < (const TCrossLine & CrossLine) {
    	return this->Angle < CrossLine.Angle;
    };
    bool __fastcall operator == (const TCrossLine & CrossLine) {
        return this->Angle == CrossLine.Angle;
    };
private:
};

//---------------------------------------------------------------------------
class TCross {
public:
	double X, Y;
    double MinAngle, MaxAngle;
    int MinAngleA, MinAngleB, MaxAngleA, MaxAngleB;
	int FrogNumber, MainLineNumber;
    eSwitch Type;
	vector<TCrossLine> Lines;
	__fastcall TCross();
	void __fastcall AddLine(eLinePos Pos, TLine * Line);
    void __fastcall UpdateAngle(void);
	void __fastcall Draw(TImage * Image, const double Scale, const double OriginX, const double OriginY);
	void __fastcall SetLineType(eBranchSide BranchSide, int LineNumber);
	__property TCrossLine * Main = { read=GetMainLine };
	__property TCrossLine * Left = { read=GetLeftLine };
	__property TCrossLine * Right = { read=GetRightLine };
	__property TCrossLine * Straight = { read=GetStraight };
private:
	TCrossLine * __fastcall GetLine(eBranchSide BranchSide);
	TCrossLine * __fastcall GetMainLine(void);
	TCrossLine * __fastcall GetLeftLine(void);
	TCrossLine * __fastcall GetRightLine(void);
	TCrossLine * __fastcall GetStraight(void);
	int MainNumber, LeftNumber, RightNumber, StraightNumber;
	vector<TCrossLine>::iterator vi;
	void __fastcall SetSimpleSwitchType(const eBranchSide BranchSide);
};

//---------------------------------------------------------------------------
class TCrosses : public vector<TCross> {
public:
	void __fastcall Draw(TImage * Image, const double Scale, const double OriginX, const double OriginY);
};
#endif
