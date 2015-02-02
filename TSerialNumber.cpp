//---------------------------------------------------------------------------


#pragma hdrstop

#include "TSerialNumber.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

bool __fastcall TElementSerialNumber::SetElementSerialNumber(const TSerialNumber UserID,
															 const eElementType ElementType)
{
	static int Number = 0;
	int sl = 10;
	AnsiString S, s;
	S = UserID;
	if (S.Length() < sl) {
		s = s.StringOfChar('*', sl - S.Length());
		S += s;
	} else
	S = S.SubString(0, sl);
	s = Now().FormatString("yyyymmddhhnnss");
	S = S + s;
	s = s.sprintf("%2.2d%5.5d", ElementType, Number);
	SerialNumber = S + s;
	Number++;
	return true;
}

__fastcall TElementSerialNumbers::TElementSerialNumbers()
{

}

TElementSerialNumbers & TElementSerialNumbers::operator = (TSerialNumbers t)
{
	clear();
	for (int i = 0; i < t.size(); i++)
		push_back(t[i]);
    return *this;
}

bool __fastcall TElementSerialNumbers::InList(const TSerialNumber SerialNumber)
{
	for (int i = 0; i < size(); i++) {
		if (at(i) == SerialNumber) {
			return true;
		}
	}
	return false;
}

TSerialNumbers __fastcall TSerialNumbers::operator += (TSerialNumbers t)
{
	for (int i = 0; i < t.size(); i++) {
		push_back(t[i]);
	}
	return *this;
}

TSerialNumbers __fastcall TSerialNumbers::Add(WideString SerialNumber)
{
	for (int i = 0; i < size(); i++)
		if (at(i) == SerialNumber) return *this;
	push_back(SerialNumber);
	return *this;
}

TSerialNumbers __fastcall TSerialNumbers::Add(TSerialNumbers SerialNumbers)
{
	for (int i = 0; i < SerialNumbers.size(); i++)
		Add(SerialNumbers[i]);
	return *this;
}

bool __fastcall TSerialNumbers::Find(const WideString SerialNumber)
{
	for (int i = 0; i < size(); i++)
		if (SerialNumber == at(i)) return true;
	return false;
}

WideString __fastcall TSerialNumbers::Find(const TSerialNumbers SerialNumbers)
{
	for (int i = 0; i < SerialNumbers.size(); i++)
		for (int j = 0; j < size(); j++)
			if (SerialNumbers[i] == at(j)) return at(j);
	return L"";
}
