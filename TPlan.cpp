//---------------------------------------------------------------------------

#pragma hdrstop

#include "TPlan.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall TPlan::TPlan() {
}

//---------------------------------------------------------------------------
void __fastcall TPlan::Clear(void) {
    Arcs.clear();
    Lines.clear();
    return;
}

//---------------------------------------------------------------------------
void __fastcall TPlan::SetOrigin(TImage * Image) {
	SetMaxMin();
    double s1 = Image->Width / Width;
    double s2 = Image->Height / Height;
    if (s1 < s2) {	//图的X方向大于Y方向，即长度大于高度。
    	Scale = s1;
        OriginX = MinX;
        OriginY = MinY - (Image->Height / Scale - Height) * 0.5;
    } else {
        Scale = s2;
        OriginX = MinX - (Image->Width / Scale - Width) * 0.5;
        OriginY = MinY;
    }
    return;
}

//---------------------------------------------------------------------------
void __fastcall TPlan::Draw(TImage * Image) {
	SetOrigin(Image);
    Arcs.Draw(Image, Scale, OriginX, OriginY);
    Lines.Draw(Image, Scale, OriginX, OriginY);
    return;
}

//---------------------------------------------------------------------------
void __fastcall TPlan::DrawCrosses(TImage * Image) {
	Crosses.Draw(Image, Scale, OriginX, OriginY);
	return;
}

//---------------------------------------------------------------------------
void __fastcall TPlan::SetMaxMin(void) {
	Lines.SetMaxMin();
    Arcs.SetMaxMin();
	MaxX = (Lines.MaxX > Arcs.MaxX) ? Lines.MaxX : Arcs.MaxX;
    MinX = (Lines.MinX < Arcs.MinX) ? Lines.MinX : Arcs.MinX;
    MaxY = (Lines.MaxY > Arcs.MaxY) ? Lines.MaxY : Arcs.MaxY;
    MinY = (Lines.MinY < Arcs.MinY) ? Lines.MinY : Arcs.MinY;
    Width = abs(MaxX - MinX);
    Height = abs(MaxY - MinY);
    return;
}

//---------------------------------------------------------------------------
void __fastcall TPlan::DistinguishSwitches(void) {
	int i, j;
	eLinePos lp;
	TCross StartCross, EndCross;
	Crosses.clear();
	for (i = 0; i < Lines.size(); i++) {    //判断线段与线段的连接。
		if (Lines[i].Length < 5) continue;
		if (Lines[i].StartSign && Lines[i].EndSign) continue;
		StartCross.Lines.clear();
		EndCross.Lines.clear();
		for (j = 0; j < Lines.size(); j++) {
        	if (i == j) continue;
			if (Lines[j].Length < 5)continue;
			if (!Lines[i].StartSign) {
				lp = OnLine(Lines[i].StartX, Lines[i].StartY, &Lines[j]);
				switch (lp) {
					case lpSTART:
						Lines[j].StartSign = true;
						StartCross.AddLine(lp, &Lines[j]);
						break;
					case lpMIDDLE:
						StartCross.AddLine(lp, &Lines[j]);
						break;
					case lpEND:
						Lines[j].EndSign = true;
						StartCross.AddLine(lp, &Lines[j]);
						break;
					case lpNONE:
					default:
					;
				}
			}
			if (!Lines[i].EndSign) {
				lp = OnLine(Lines[i].EndX, Lines[i].EndY, &Lines[j]);
 				switch (lp) {
					case lpSTART:
						Lines[j].StartSign = true;
						EndCross.AddLine(lp, &Lines[j]);
						break;
					case lpMIDDLE:
						EndCross.AddLine(lp, &Lines[j]);
						break;
					case lpEND:
						Lines[j].EndSign = true;
						EndCross.AddLine(lp, &Lines[j]);
						break;
					case lpNONE:
					default:
					;
				}
            }
        }
		if (!StartCross.Lines.empty()) {
			Lines[i].StartSign = true;
            StartCross.X = Lines[i].StartX;
            StartCross.Y = Lines[i].StartY;
			StartCross.AddLine(lpSTART, &Lines[i]);
			Crosses.push_back(StartCross);
		}
		if (!EndCross.Lines.empty()) {
			Lines[i].EndSign = true;
            EndCross.X = Lines[i].EndX;
            EndCross.Y = Lines[i].EndY;
            EndCross.AddLine(lpEND, &Lines[i]);
            Crosses.push_back(EndCross);
        }
    }
    //删除非道岔
    for (i = Crosses.size() - 1; i > -1 ; i--) {
		if (Crosses[i].Lines.size() == 2 && Crosses[i].Lines[0].Pos != lpMIDDLE && Crosses[i].Lines[1].Pos != lpMIDDLE) {
			Crosses.erase(Crosses.begin() + i);
		} else {
			Crosses[i].UpdateAngle();
			if (Crosses[i].Type == sNone)
				Crosses.erase(Crosses.begin() + i);
		}
	}
	return;
}

//---------------------------------------------------------------------------
eLinePos __fastcall TPlan::OnLine(const double x, const double y, TLine * Line) {
	if (Line->Length < 5) return lpNONE;
	double xa = Line->EndX - Line->StartX;
	double ya = Line->EndY - Line->StartY;
	double xb = x - Line->StartX;
	double yb = y - Line->StartY;
	if (fabs(xa * yb - xb * ya) < 1 && min(Line->StartX, Line->EndX) <= x && x <= max(Line->StartX, Line->EndX) && min(Line->StartY, Line->EndY) <= y && y <= max(Line->StartY, Line->EndY)) {
		if (InRange(x, y, Line->StartX, Line->StartY, 1))
			return lpSTART;
		else if (InRange(x, y, Line->EndX, Line->EndY, 1))
			return lpEND;
		else
			return lpMIDDLE;

	} else
		return lpNONE;
}

//---------------------------------------------------------------------------
void __fastcall TPlan::DistinguishPath(void) {
	int i;
    int e;
	for (i = 0; i < Lines.size(); i++) {    // 获得股道和驼峰所在线段
		if (Lines[i].Length < 5) continue;
		if (IsHumpLine(&Lines[i])) {
			HumpLine = &Lines[i];
		}
		if (IsTrackLine(&Lines[i])) {
			TrackLines.push_back(&Lines[i]);
		}
	}
	for (i = 0; i < TrackLines.size(); i++) {
		TPath Path;
		Path.push_back(TrackLines[i]);
		Path.Angle = TrackLines[i]->StartAngle;
		Paths.push_back(Path);
		p = Paths.size() - 1;
		Next(p);
	}
	return;
}

//---------------------------------------------------------------------------
void __fastcall TPlan::Next(const int p) {
	bool f, fc;
	TArc *A;
	TLine *L;
	TCross *C;
	int i, j, e = Paths[p].size() - 1;
	if (Paths[p][e].type() == typeid(TArc *)) {      // 曲线只有可能连接线段。
		A = boost::any_cast<TArc*>(Paths[p][e]);
		for (i = 0; i < Lines.size(); i++) {
			if (Lines[i].Length < 5) continue;
			if (InRange(A->StartX, A->StartY, Lines[i].EndX, Lines[i].EndY, 1)) {
				Paths[p].Add(&Lines[i]);
				Next(p);
				return;
			}
		}
	} else if (Paths[p][e].type() == typeid(TLine *)) {	// 线段可能连接 道岔、曲线和线段
		L = boost::any_cast<TLine *>(Paths[p][e]);
		for (i = 0; i < Crosses.size(); i++) {
			if (OnLine(Crosses[i].X, Crosses[i].Y, L)) {
				if (Paths[p].FindCross(&Crosses[i]))
					continue;           //如果已经存在就跳过。
				Paths[p].push_back(&Crosses[i]);       // 线段可能有多个道岔。且只能是直股在这个线段上。
				if (InRange(Crosses[i].X, Crosses[i].Y, L->StartX, L->StartY, 1)) {      //Start点连接道岔
					TPath Path;
					TPaths Ps;
					if (Crosses[i].Main->Angle != Paths[p].Angle) {   //逆向道岔
						Paths[p].Add(Crosses[i].Main->ptr);
						Next(p);
						return;
					} else {                                   //顺序道岔
						for (j = 0; j < Crosses[i].Lines.size(); j++) {
							if (Crosses[i].Lines[j].Angle == Paths[p].Angle) continue;
							Path.Add(Crosses[i].Lines[j].ptr);
							Ps.push_back(Path);
						}
						for (j = 1; j < Ps.size(); j++) {
							Paths.push_back(Ps[j]);
						}
						Paths[p] = Ps[0];
						Next(p);
						return;
					}
				} else {                  // 线段中间有道岔。
					if (Crosses[i].Main->Angle == Paths[p].Angle) { // 顺向道岔。 逆向道岔就什么也不做，因为要加入的就是这个线段。
						TPath Path;
						if (Crosses[i].Left != NULL) {
							Path = Paths[p];
							Path.Add(Crosses[i].Left->ptr);
							Paths.push_back(Path);
						}
						if (Crosses[i].Right != NULL) {
							Path = Paths[p];
							Path.Add(Crosses[i].Right->ptr);
							Paths.push_back(Path);
						}
					}
				}
			}
		}
		for (i = 0; i < Arcs.size(); i++) {
			if (InRange(L->StartX, L->StartY, Arcs[i].EndX, Arcs[i].EndY, 1)) {
				Paths[p].push_back(&Arcs[i]);
				Paths[p].Angle = (Arcs[i].SweepAngle < 0) ? Arcs[i].StartAngle + 90 : Arcs[i].StartAngle + Arcs[i].SweepAngle - 90;
				Next(p);
				return;
			}
		}
		for (i = 0; i < Lines.size(); i++) {
			if (Lines[i].Length < 5) continue;
			if (InRange(L->StartX, L->StartY, Lines[i].EndX, Lines[i].EndY, 1)) {
				Paths[p].Add(&Lines[i]);
				Next(p);
				return;
			}
		}
	}
    if (Paths[p][e].type() == typeid(TLine *) && boost::any_cast<TLine *>(Paths[p][e]) == HumpLine) {    // 最后一个是驼峰？
        // DONE
        i = Paths.size();
	    if (p + 1 < Paths.size()) {             // 本股道产生的其他Path
	    	Next(p + 1);
            i = Paths.size();
        }
    } else {                     // 最后一个不是驼峰
	    Paths.erase(Paths.begin() + p);
        i = Paths.size();
	    if (p < Paths.size())
		    Next(p);
            i = Paths.size();
    }
	return;
}
