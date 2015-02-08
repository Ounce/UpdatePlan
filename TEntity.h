//---------------------------------------------------------------------------

#ifndef TEntityH
#define TEntityH

#include <boost/any.hpp>
#include "TArc.h"
#include "TCross.h"
//---------------------------------------------------------------------------
enum eEntityType {etUNKNOWN, etSWITCH, etARC};
/*
class TEntity {
public:
	eEntityType Type;
 	TArc * __fastcall GetArc(void) {
		if (Type == etARC)
			return static_cast<TArc*>(Ptr);
		else
			return NULL;
	}
	TSwitch * __fastcall GetSwitch(void) {
		if (Type == etSWITCH)
			return static_case<TSwitch *>(Ptr);
		else
			return NULL;
	}
	TEntity & __fastcall operator = (const TArc * ArcPtr) {
		Type = etARC;
		Ptr = ArcPtr;
		return *this;
	}
	TEntity & __fastcall operator = (const TSWitch * SwitchPtr) {
		Type = etSWITCH;
		Ptr = SwitchPtr;
		return *this;
	}
private:
	boost::any Ptr;
};      */

class TEntities : public vector<boost::any> {
public:
	TArc * GetArcPtr(const int i) {
		if (at(i).type() == typeid(TArc*))
			return boost::any_cast<TArc*>(at(i));
		else
			return NULL;
	}
	eEntityType __fastcall GetType(const int i) {
		if (at(i).type() == typeid(TArc*))
			return etARC;
		return etUNKNOWN;
    }
};
#endif
