//---------------------------------------------------------------------------

#ifndef TSwitchH
#define TSwitchH

#include "TLine.h"

//---------------------------------------------------------------------------
class TSwitch {
public:
	double X, Y;
    vector<TLine *> Lines;
};

class TSwitches : public vector<TSwitch> {

};
#endif
