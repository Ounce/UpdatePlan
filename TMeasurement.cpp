//---------------------------------------------------------------------------


#pragma hdrstop

#include "TMeasurement.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TMeasurement::TMeasurement()
{
	Type = mMETRIC;
	LengthRate = 1;
	SpeedRate = 1;
	GradeRate = 1;
	WeightRate = 1;
	LengthCaption = L"m";
	SpeedCaption = L"m/s";
	GradeCaption = L"бы";
	WeightCaption = L"T";
}

//---------------------------------------------------------------------------
void __fastcall TMeasurement::SetType(const eMeasurement NewMeasurement)
{
	Type = NewMeasurement;
	switch (NewMeasurement) {
	case mBRITISH:
		LengthRate = 0.3048;
		SpeedRate = 0.4444;
		GradeRate = 10;
		WeightRate = 0.9072;
		LengthCaption = L"ft";
		SpeedCaption = L"mph";
		GradeCaption = L"%";
		WeightCaption = L"ST";
		break;
	case mMETRIC:
	default:
		LengthRate = 1;
		SpeedRate = 1;
		GradeRate = 1;
		WeightRate = 1;
		LengthCaption = L"m";
		SpeedCaption = L"m/s";
		GradeCaption = L"бы";
		WeightCaption = L"T";
		break;
		;
	}
	return;
}


