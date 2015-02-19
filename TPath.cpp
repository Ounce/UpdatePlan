//---------------------------------------------------------------------------

#pragma hdrstop

#include "TPath.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void __fastcall TPath::SetPosition(void) {
	float Position = 0;
	TLine* L;
	TCross* C;
	TArc * A;
	TEntities::iterator it;
	for (int i = size() - 1; i >= 0; i--) {
		if (at(i).type() == typeid(TLine *)) {
			L = boost::any_cast<TLine *>(at(i));
			Position += L->Length;
		} else if (at(i).type() == typeid(TArc *)) {
			A = boost::any_cast<TArc *>(at(i));
			if (A->Begin < 0.001) {
				A->Begin = Position;
				Position += A->Length;
				A->End = Position;
			}
		} else if (at(i).type() == typeid(TCross *)) {
			C = boost::any_cast<TCross *>(at(i));
			if (C->Position < 0.001) C->Position = Position;
		}
	}
	return;
}

//---------------------------------------------------------------------------
void __fastcall TPath::Draw(TImage * Image, float Scale, int OriginX, int OriginY) {
	for (int i = 0; i < size(); i++) {
		if (at(i).type() == typeid(TLine *)) {
			boost::any_cast<TLine *>(at(i))->Draw(Image, Scale, OriginX, OriginY);
		} else if (at(i).type() == typeid(TArc *)) {
			boost::any_cast<TArc *>(at(i))->Draw(Image, Scale, OriginX, OriginY);
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TPaths::SetPosition(void) {
	for (int i = 0; i < size(); i++) {
		at(i).SetPosition();
	}
	return;
}

//---------------------------------------------------------------------------
void __fastcall TPaths::Draw(TImage * Image, float Scale, int OriginX, int OriginY) {
	for (int i = 0; i < size(); i++) {
		at(i).Draw(Image, Scale, OriginX, OriginY);
	}
	return;
}


