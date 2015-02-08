//---------------------------------------------------------------------------

#ifndef TPathH
#define TPathH

#include <TEntity.h>

//---------------------------------------------------------------------------

class TPath : public TEntities {
public:
	bool __fastcall FindCross(TCross * C) {
		for (int i = 0; i < size(); i++) {
			if (at(i).type() == typeid(TCross *) && boost::any_cast<TCross *>(at(i)) == C) {
				return true;
			}
		}
		return false;
	}
};

class TPaths : public vector<TPath> {

};
#endif
