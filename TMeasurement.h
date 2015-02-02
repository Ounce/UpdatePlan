//---------------------------------------------------------------------------

#ifndef TMeasurementH
#define TMeasurementH
#include <vector.h>
#include <ComCtrls.hpp>

//---------------------------------------------------------------------------
enum eMeasurement { mMETRIC = 0, mBRITISH };
enum eMeasurementType {mtLENGTH, mtSPEED, mtGRADE, mtWEIGHT};

class TMeasurement
{
public:
	eMeasurement Type;
	float LengthRate;
	float SpeedRate;
	float GradeRate;
	float WeightRate;
	WideString LengthCaption,
			   SpeedCaption,
			   GradeCaption,
			   WeightCaption;
	__fastcall TMeasurement();
	void __fastcall SetType(const eMeasurement NewMeasurement);
private:
};
#endif
