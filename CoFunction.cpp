//---------------------------------------------------------------------------


#pragma hdrstop

#include "CoFunction.h"
#include <math.h>
#include <SysUtils.hpp>
#include <Dialogs.hpp>
#include "dstring.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

AnsiString __fastcall FloatToStrF(const float Value)
{
	AnsiString Result;

	if (fabs(Value) < 0.0001) return "0";
	Result = Result.FormatFloat("#.###", fabs(Value));
	if (fabs(Value) < 1) {
		Result = "0" + Result;
	}
	if (Value < 0) {
		Result = "-" + Result;
	}
	return Result;
}
//---------------------------------------------------------------------------
AnsiString __fastcall FloatToStrF(const float Value, const unsigned short Digits)
{
	AnsiString Result;
	AnsiString Format;
	AnsiString DigitStr;

	if (fabs(Value) < 0.0001) return "0";
	DigitStr = DigitStr.StringOfChar('#', Digits);
	Format = "#." + DigitStr;
	Result = Result.FormatFloat(Format, fabs(Value));
	if (fabs(Value) < 1) {
		Result = "0" + Result;
	}
	if (Value < 0) {
		Result = "-" + Result;
	}
	return Result;
}

AnsiString __fastcall FloatToStrF(const float Value, const unsigned short Len, const unsigned short Digits)
{
	AnsiString S, R;
	int l;
	char a = ' ';
	S = FloatToStrF(Value, Digits);
	l = S.Length();
//	R.FloatToStrF(Value, )
//	S = R.FloatToStrF(Value, sffNumber, 8, 3);
	R = R.StringOfChar(a, 2 * (Len - l));
	R += S;
	return R;
}

//---------------------------------------------------------------------------
void __fastcall WriteFloat(const unsigned short x, const unsigned short y,
									TCanvas *Canvas, const float Value, const unsigned short Digits)
{
	unsigned short L, P;
	AnsiString Str, SF, SB;
	unsigned short lf, lb;
	unsigned short FL, BL;

	Str = FloatToStrF(Value, Digits);
//   Str = Str.FloatToStrF(Value, 2, 8, 3);
	P = Str.Pos('.');
	L = Str.Length();
	FL = (P < 1) ? L : P - 1;
	SF = Str.SubString(0, FL);
	SB = Str.SubString(P, L - FL);
	lf = Canvas->TextWidth(SF);
	lb = Canvas->TextWidth(SB);
	if (Value == 9999) {
		Canvas->TextOutW(x, y, "~~");
	} else
	if (Value == -9999) {
		Canvas->TextOutW(x, y, "--");
	} else {
		Canvas->TextOutW(x - lf, y, SF);
		Canvas->TextOutW(x, y, SB);
	}
}

//---------------------------------------------------------------------------
float __fastcall ReadFloat(const int Handle)
{
	float f;
	FileRead(Handle, &f, sizeof(float));
	return f;
}

//---------------------------------------------------------------------------
void __fastcall WriteFloat(const int Handle, const float F)
{
	FileWrite(Handle, &F, sizeof(float));
}

//---------------------------------------------------------------------------
void __fastcall WriteBool(const int Handle, const bool B)
{
	if (B) WriteFloat(Handle, 1);
	else WriteFloat(Handle, 0);
}

bool __fastcall ReadBool(const int Handle)
{
	if (ReadFloat(Handle) > 0.1) return true;
	else return false;
};

//---------------------------------------------------------------------------
int __fastcall ReadInt(const int Handle)
{
	int i;
	float f;
//	FileRead(Handle, &i, sizeof(int));
	FileRead(Handle, &f, sizeof(float));
/*	if (f > 0) {
		i = f + 0.000000001;
	}
	if (f < 0) {
		i = f - 0.000000001;
	} */
	i = f;
	return i;
}

//---------------------------------------------------------------------------
void __fastcall WriteInt(const int Handle, const int I)
{
	float f;
	f = I;
	FileWrite(Handle, &f, sizeof(float));
}

//---------------------------------------------------------------------------
void __fastcall PassDigit(char &Key)
{
	if (isdigit(Key)) return;
	if (iscntrl(Key)) return;
	if (Key == '.') return;
	if (Key == '-') return;
	Key = 0;
	ShowMessage("±ØÐëÊäÈëÊý×Ö£¡");
};

//---------------------------------------------------------------------------
void __fastcall PassDigit(char &Key, const eMeasurementType MeasurementType)
{
	if (isdigit(Key)) return;
	if (iscntrl(Key)) return;
	if (Key == '.') return;
	if (Key == '\xA1') return;
	if (Key == '-')
		switch (MeasurementType) {
			case mtLENGTH:
			case mtWEIGHT:
			case mtSPEED:
				return;
			default:
				break;
		}
	Key = 0;
	ShowMessage("±ØÐëÊäÈëÊý×Ö£¡");
}

//---------------------------------------------------------------------------
bool __fastcall IsDigit(const AnsiString Text, const eMeasurementType MeasurementType)
{
	double num;
	if (!TryStrToFloat(Text, num))
	{
		MessageBoxA(NULL, "ÊäÈë´íÎó£¡", "´íÎó£¡", MB_OK);
		return false;
	}
	switch (MeasurementType) {
		case mtLENGTH:
		case mtSPEED:
		case mtWEIGHT:
			if (num < 0) MessageBoxA(NULL, "ÊäÈë´íÎó£¡", "´íÎó£¡", MB_OK);
			return false;
			break;
		case mtGRADE: break;
		default:
		;
	}
	return true;
}

//---------------------------------------------------------------------------
float __fastcall TryStrToFloat(const AnsiString Text)
{
	float num;
	if (TryStrToFloat(Text, num))
		return num;
	else
		return 0;
}

bool __fastcall TryToFloat(const AnsiString Text, float & num)
{
	bool right;
	AnsiString Msg;

	num = 0;
	if (Text == "-") return true;
	if (Text == "-.") return true;
	if (Text.IsEmpty()) return true;
	right = TryStrToFloat(Text, num);
	if (right)
		return true;
	else {
		Msg = "\" " + Text + " \" °üº¬·Ç·¨×Ö·û£¡";
		MessageBoxA(NULL, Msg.c_str(), "´íÎó£¡", MB_OK +  MB_ICONERROR);
		return false;
	}
}

bool __fastcall StrToBool(const AnsiString Text)
{
	if (Text.UpperCase() == "TRUE")
		return true;
	else
		return false;
}
                  /*
AnsiString __fastcall BoolToStr(const bool Bool)
{
	if (Bool)
		return "TRUE";
	return "FALSE";
}               */

int __fastcall TryToInt(const AnsiString Text)
{
	float num;
	if (Text == "-") return 0;
	if (Text == "-.") return 0;
	if (Text.IsEmpty()) return 0;
	if (TryStrToFloat(Text, num))
		return num;
	else
		return -999;

}

//---------------------------------------------------------------------------
bool __fastcall EditDigit(const AnsiString Text, const eMeasurementType MeasurementType)
{
	if (Text.IsEmpty()) return true;
	return IsDigit(Text, MeasurementType);
}

//---------------------------------------------------------------------------
bool __fastcall IsFloat(const AnsiString Text, float &f, const AnsiString ErrorMessage, const int r)
{
	bool b;
	if (TryStrToFloat(Text, f))
		switch (r) {
			case -1:
				b = true;
				break;
			case 0:
				if (f < -0.0001) b = false;
				else b = true;
				break;
			case 1:
				if (f > 0.0001)	b = true;
				else b = false;
				break;
		}
	else
		if (r == -1 && Text == "-") b = true;
		else b = false;
	if (!b && !ErrorMessage.IsEmpty()) MessageBoxA(NULL, ErrorMessage.c_str(), "´íÎó£¡", MB_OK);
	return b;
}

//---------------------------------------------------------------------------
bool __fastcall IsInt(const AnsiString Text, int f, const AnsiString ErrorMessage, const int r)
{
	bool b;
	if (TryStrToInt(Text, f))
		switch (r) {
			case -1:
				b = true;
				break;
			case 0:
				if (f < 0) b = false;
				else b = true;
				break;
			case 1:
				if (f <= 0)	b = false;
				else b = true;
				break;
		}
	else
		b = false;
	if (!b && !ErrorMessage.IsEmpty()) MessageBoxA(NULL, ErrorMessage.c_str(), "´íÎó£¡", MB_OK);
	return b;
}

//---------------------------------------------------------------------------
bool __fastcall EditFloat(const AnsiString Text, float &f, const AnsiString ErrorMessage, const int r)
{
	if (Text.IsEmpty()) return true;
	return IsFloat(Text, f, ErrorMessage, r);
}

//---------------------------------------------------------------------------
bool __fastcall EditInt(const AnsiString Text, int &i, const AnsiString ErrorMessage, const int r)
{
	if (Text.IsEmpty()) return true;
	return IsInt(Text, i, ErrorMessage, r);
}

//---------------------------------------------------------------------------
void __fastcall TTest::SetA(void)
{
	a = 20;
}

//---------------------------------------------------------------------------
void __fastcall WriteAnsiStringCentreCanvas(TCanvas *Canvas, const AnsiString Text, const int Width, const int y)
{
	int x, l;
	l = Canvas->TextWidth(Text);
	x = 0.5 * (Width - l);
	Canvas->TextOutW(x, y, Text);
	return;
}

//---------------------------------------------------------------------------
AnsiString __fastcall FirstString(AnsiString &I)
{
	int e;
	AnsiString P;
	while (I.SubString(1, 1) == ',' || I.SubString(1, 1) == '/')
		I = I.SubString(2, I.Length());
	e = I.Pos(',');
	if (e == 0)
		e = I.Pos('/');
	if (e < 2) return NULL;
	P = I.SubString(1, e - 1);
	I = I.SubString(e, I.Length());
	return P.Trim();
}

//---------------------------------------------------------------------------


