//---------------------------------------------------------------------------

#ifndef TSerialNumberH
#define TSerialNumberH

#include <vcl.h>
#include <vector.h>
#include <msxmldom.hpp>
#include <XMLDoc.hpp>
#include <xmldom.hpp>
#include <XMLIntf.hpp>

typedef WideString TSerialNumber;
//---------------------------------------------------------------------------

enum eElementType {ProfileElementType, CurveElementType, SwitchElementType,
						 RetarderElementType, CtrRetarderElementType, ArresterElementType,
						 TrackRetarderElementType, CutElementType, WarningMakeElementType,
						 StopPointElementType, WeatherElementType, TrackElementType, CheckElementType};

class TSerialNumbers : public vector<TSerialNumber>
{
public:
	TSerialNumbers __fastcall operator += (TSerialNumbers t);
	TSerialNumbers __fastcall Add(WideString SerialNumber);
	TSerialNumbers __fastcall Add(TSerialNumbers SerialNumbers);
	bool __fastcall Find(const WideString SerialNumber);
	WideString __fastcall Find(const TSerialNumbers SerialNumbers);
};

class TElementSerialNumber
{
public:
	TSerialNumber SerialNumber;
	WideString Name, Note;
	int Index;

//	int ListID, ElementID;
	bool __fastcall SetElementSerialNumber(const WideString UserID, const eElementType ElementType);
};

class TElementSerialNumbers : public TSerialNumbers
{
public:
	__fastcall TElementSerialNumbers();
	TElementSerialNumbers & operator = (TSerialNumbers t);
	bool __fastcall InList(const TSerialNumber SerialNumber);
};
#endif
