//---------------------------------------------------------------------------

#pragma hdrstop

#include "TPath.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
void __fastcall TPath::Draw(TImage * Image, float Scale, int OriginX, int OriginY) {
	for (int i = 0; i < size(); i++) {
		if (at(i).type() == typeid(TLine *)) {
			boost::any_cast<TLine *>(at(i))->Draw(Image, Scale, OriginX, OriginY);
		} else if (at(i).type() == typeid(TArc *)) {
			boost::any_cast<TArc *>(at(i))->Draw(Image, Scale, OriginX, OriginY);
		}
	}
}

void __fastcall TPaths::Draw(TImage * Image, float Scale, int OriginX, int OriginY) {
	for (int i = 0; i < size(); i++) {
		at(i).Draw(Image, Scale, OriginX, OriginY);
	}
	return;
}
