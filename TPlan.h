//---------------------------------------------------------------------------

#ifndef TPlanH
#define TPlanH
//---------------------------------------------------------------------------

#include "Comm.h"
#include "TArc.h"
#include "TLine.h"
#include "TCross.h"
#include "TPath.h"

class TPlan {
public:
    double OriginX, OriginY;	// TImage基点（左下角）在Plan中的位置。
    double Scale;
	TArcs Arcs;
    TLines Lines;
	TCrosses Crosses;
	TPaths Paths;
	vector<TLine*> TrackLines;
	TLine * HumpLine;
    __fastcall TPlan();
    void __fastcall SetOrigin(TImage * Image);
	void __fastcall Clear(void);
	void __fastcall DistinguishSwitches(void);
	void __fastcall Draw(TImage * Image);
	void __fastcall DrawCrosses(TImage * Image);
	void __fastcall DistinguishPath(void);
private:
	double MaxX, MaxY, MinX, MinY, Width, Height;
	void __fastcall SetMaxMin(void);
	eLinePos __fastcall OnLine(const double x, const double y, TLine * Line);
	bool __fastcall IsTrackLine(TLine * Line) {
		if (fabs(Line->StartX - MaxX) < 5 || fabs(Line->EndX - MaxX) < 5)
			return true;
		else
			return false;
	};
	bool __fastcall IsHumpLine(TLine * Line) {
		if (fabs(Line->StartX - MinX) < 5 || fabs(Line->EndX - MinX) < 5)
			return true;
		else
			return false;
	};
	void __fastcall Next(const int p);
};
#endif
