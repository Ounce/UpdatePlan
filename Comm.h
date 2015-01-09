//---------------------------------------------------------------------------

#ifndef CommH
#define CommH
//---------------------------------------------------------------------------

bool __fastcall InRange(const double x, const double y, const double X, const double Y, const double R) {
	double dx = X - x;
    double dy = Y - y;
    if (dx * dx + dy * dy < R * R)
        return true;
    else
    	return false;
}

double __fastcall OppositeAngle(const double Angle) {
    if (Angle >= 180) {
		return Angle - 180;
    } else {
		return Angle + 180;
    }
}
#endif
