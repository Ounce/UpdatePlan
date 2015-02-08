//---------------------------------------------------------------------------

#ifndef TPathH
#define TPathH

#include <TEntity.h>

//---------------------------------------------------------------------------

class TPath : public TEntities {
public:
	float Angle;	//识别道岔时，用于判断连接到哪个分支上，为了方便，使用线段的Start方向。
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
