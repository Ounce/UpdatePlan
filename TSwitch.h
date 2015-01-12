//---------------------------------------------------------------------------

#ifndef TSwitchH
#define TSwitchH

#include <system.hpp>
#include <vector.h>
#include <deque.h>
#include <Graphics.hpp>
#include "TSerialNumber.h"
#include "TMeasurement.h"

//---------------------------------------------------------------------------

//enum eConnectWay {Straight = 0, Side};
enum eSwitchHandType {shtSTRAIGHT,	//直向
                      shtSIDE,		//侧向
                      shtLEFT,		//左
                      shtRIGHT,		//右
                      shtLEFTBACKWARD,	//左反向（菱形交叉使用）
                      shtRIGHTBACKWARD};	//右反向
enum eSwitchDirection {sdBACKWARD, sdFORWARD};     //逆向、 顺向
enum eSwitchType {Symmetry = 0,	//单开对称道岔
                  SimpleLeft,				//左开单开道岔
                  SimpleRight,				//右开单开道岔
				  Treble,			//三开对称道岔
                  DiamondCrossing};		//菱形交叉
enum eSwitch {sNone, sSimpleLeft6, sSimpleLeft7, sSimpleLeft9, sSymmetry6, sSymmetry65, sSymmetry9, sTreble7, sDiamondCrossing,
              sSimpleRight6, sSimpleRight7, sSimpleRight9};

#define TSwitchHandNumber unsigned short int

class TSwitchHandNumbers : public vector<TSwitchHandNumber> {

};

class TSwitch : public TElementSerialNumber
{
private:
	float Fa, Fb;
	float FLength;
	float FAngle;
	float FRadii;

	float FBegin, FEnd;
	float FPosition;
	int FDirection;
	WideString FModel;
	float FFrogNumber;
	float FH;
	float FGrade;

	bool Init;

    float __fastcall GetInPos(void);
    float __fastcall GetOutPos(void);

    void __fastcall SetPosition(const float Value);
    void __fastcall SetBeginEnd(void);
	void __fastcall SetDirection(const int Value);

public:
	unsigned short Number;  //编号
	eSwitch ModelIndex;
	eSwitchType Type;
	float CircuitLength;        //岔内轨道电路长度
	float SortRailLength;       //绝缘短轨长度
//	int DirectionQuantity;
	float ioPosition, ioSortRailLength;
	float Angle;

    unsigned short UsedHandNumber;
    vector<eSwitchHandType> HandTypes;		//按照从左至右存储个分支的性质，其数量就是连接的方向数。
	int DrawSide;		// 绘图方向 1——左；	-1——右。 为了兼容0版数据文件格式保留这个变量。
//	eHandType ConnectWay;    //  侧向
//	bool Symmetry;		//是否为对称道岔。
//	bool DiamondCrossing;		//是否是菱形交叉渡线。

	float CH;  	//Curve Height	曲线能高
	float SH;	// Switch Height	道岔能高

	__property float a = { read=Fa, write=Fa };
	__property float b = { read=Fb, write=Fb };
	__property float Length = { read=FLength, write=FLength };
	__property float Radii = { read=FRadii, write=FRadii };
	__property float FrogNumber = { read=FFrogNumber, write=FFrogNumber };

	__property float Position = { read=FPosition, write=SetPosition };
	__property float InPos = { read=GetInPos };
	__property float OutPos = { read=GetOutPos };
	__property int Direction = { read=FDirection, write=SetDirection };	// 方向 1——顺向；0——逆向；
	__property float Begin = { read=FBegin };
	__property float End = { read=FEnd };

   __property WideString Model = { read=FModel, write=FModel };

   __property float H = { read=FH, write=FH };
   __property float Grade = { read=FGrade, write=FGrade };

   __fastcall TSwitch();
	bool __fastcall Initialize(const TMeasurement Measurement);
	TSwitch & __fastcall operator = (const TSwitch & t);
	void __fastcall Save(const int Handle);
	void __fastcall Load(const int Handle);
    void __fastcall SetHandNumber(unsigned short HandNumber);
};

class ptrTSwitches : public vector<TSwitch *>
{

};

class TSwitches : public vector<TSwitch>
{
public:
	__fastcall TSwitches();
//	TItemCaption PositionCaption, SortRailLengthCaption;
	TSwitches & __fastcall operator = (const TSwitches & t);
	bool __fastcall VerifyInput(const WideString PositionText,
										 const WideString SwitchNumberText,
										 const WideString SortRailLengthText);
	bool __fastcall Initialize(const TMeasurement Measurement);
	void __fastcall Add(const WideString ModelName, const float Position);
	void __fastcall Save(const int Handle);
	void __fastcall Load(const int Handle);
	void __fastcall ResetIndex(void);
	TSwitch __fastcall Find(const WideString SerialNumber);
    ptrTSwitches __fastcall Find(const TSerialNumbers SerialNumbers);
	void __fastcall WriteListView(TListView * ListView);

	void __fastcall Draw(TCanvas *Canvas, const int PlanBase, const float Scale,
								const float BeginPos, const float EndPos, const int PlanHeight);
};

//---------------------------------------------------------------------------
class TSwitchList : public vector<TSwitch>
{
public:
   __fastcall TSwitchList();
//   TSwitchList & __fastcall operator = (const TSwitchList & List);
	TSwitch __fastcall Which(const WideString ModelName);
	TSwitch __fastcall Which(const unsigned short ModelIndex);
	unsigned short __fastcall Index(const WideString ModelName);
	WideString __fastcall Model(const unsigned short Index);
//    TSwitch __fastcall Model(const unsigned short Index);
private:
	TSwitch __fastcall New(const unsigned short ModelIndex, const WideString ModelName,
								  const float FrogNumber, const float a, const float b,
								  const float FH);

	TSwitch __fastcall New(const unsigned short ModelIndex, const WideString ModelName,
								  const float Angle, const float a, const float b,
								  const float CircuitLength,
								  const eSwitchType Type);
};

class TSwitchesList : public vector<TSwitches>
{

};

#endif


