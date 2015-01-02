//---------------------------------------------------------------------------

#ifndef TVectorH
#define TVectorH

#include <vector.h>
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------
template <class T>
class Vector : public vector<T> {
public:
	double MaxX, MaxY, MinX, MinY;
	void __fastcall Draw(TImage * Image, double Scale, double OriginX, double OriginY);
	void __fastcall SetMaxMin(void);
    double __fastcall Width(void);
    double __fastcall Height(void);
private:
};

//---------------------------------------------------------------------------
template <class T>
void __fastcall Vector<T>::Draw(TImage * Image, double Scale, double OriginX, double OriginY) {
    for (int i = 0; i < size(); i++) {
        at(i).Draw(Image, Scale, OriginX, OriginY);
    }
    return;
}

//---------------------------------------------------------------------------
template <class T>
void __fastcall Vector<T>::SetMaxMin(void) {
    if (empty()) return;
    MaxX = at(0).StartX;
    MinX = MaxX;
    MaxY = at(0).StartY;
    MinY = MaxY;
    for (int i = 0; i < size(); i++) {
    	if (at(i).StartX > MaxX) MaxX = at(i).StartX;
        if (at(i).EndX > MaxX) MaxX = at(i).EndX;
		if (at(i).StartX < MinX) MinX = at(i).StartX;
        if (at(i).EndX < MinX) MinX = at(i).EndX;
    	if (at(i).StartY > MaxY) MaxY = at(i).StartY;
		if (at(i).EndY > MaxY) MaxY = at(i).EndY;
		if (at(i).StartY < MinY) MinY = at(i).StartY;
		if (at(i).EndY < MinY) MinY = at(i).EndY;
    }
    return;
}

//---------------------------------------------------------------------------
template <class T>
double __fastcall Vector<T>::Width(void) {
	return abs(MaxX - MinX);
}

//---------------------------------------------------------------------------
template <class T>
double __fastcall Vector<T>::Height(void) {
    return abs(MaxY - MinY);
}

#endif
