//---------------------------------------------------------------------------

#ifndef CommonFunctionH
#define CommonFunctionH

#include <system.hpp>
#include <Graphics.hpp>
#include <stdio.h>
#include "TMeasurement.h"

//---------------------------------------------------------------------------
enum TStringFloatFormat {
  sffGeneral,
  sffExponent,
  sffFixed,
  sffNumber,
  sffCurrency
};


AnsiString __fastcall FloatToStrF(const float Value);
AnsiString __fastcall FloatToStrF(const float Value, const unsigned short Digits);
AnsiString __fastcall FloatToStrF(const float Value, const unsigned short Len, const unsigned short Digits);

void __fastcall WriteFloat(const unsigned short x, const unsigned short y,
                           TCanvas *Canvas, const float Value, const unsigned short Digits);

void __fastcall WriteFloat(const int Handle, const float F);
float __fastcall ReadFloat(const int Handle);

void __fastcall WriteBool(const int Handle, const bool B);
bool __fastcall ReadBool(const int Handle);

void __fastcall WriteInt(const int Handle, const int I);
int __fastcall ReadInt(const int Handle);

void __fastcall PassDigit(char &Key);
void __fastcall PassDigit(char &Key, const eMeasurementType MeasurementType);
bool __fastcall IsDigit(const AnsiString Text, const eMeasurementType MeasurementType);
float __fastcall TryStrToFloat(const AnsiString Text);
bool __fastcall TryToFloat(const AnsiString Text, float & num);
bool __fastcall StrToBool(const AnsiString Text);
//AnsiString __fastcall BoolToStr(const bool Bool);
int __fastcall TryToInt(const AnsiString Text);
bool __fastcall EditDigit(const AnsiString Text, const eMeasurementType MeasurementType);
bool __fastcall IsFloat(const AnsiString Text, float &f, const AnsiString ErrorMessage, const int r);
bool __fastcall IsInt(const AnsiString Text, int f, const AnsiString ErrorMessage, const int r);
bool __fastcall EditFloat(const AnsiString Text, float &f, const AnsiString ErrorMessage, const int r);
bool __fastcall EditInt(const AnsiString Text, int &i, const AnsiString ErrorMessage, const int r);
void __fastcall WriteAnsiStringCentreCanvas(TCanvas *Canvas, const AnsiString Text, const int Width, const int y);
AnsiString __fastcall FirstString(AnsiString &I);
class TTest
{
	public:
		int a;
		void __fastcall SetA(void);
};
#endif
