//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "BaseGrid"
#pragma resource "*.dfm"
TMainForm *MainForm;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::CloseButtonClick(TObject *Sender)
{
	Close();
    return;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenButtonClick(TObject *Sender)
{
	if (!ExcelOpenDialog->Execute()) return;
	PlanDataAdvStringGrid->LoadFromXLSSheet(ExcelOpenDialog->FileName, L"Summary");
	return;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Import(void) {
	float s;
	Plan.Clear();
    TLine Line;
    TArc Arc;
    for (int i = 1; i < PlanDataAdvStringGrid->RowCount; i++) {
		if (PlanDataAdvStringGrid->Cells[1][i] == L"直线") {
			if (PlanDataAdvStringGrid->Floats[17][i] > PlanDataAdvStringGrid->Floats[13][i]) {
				Line.StartX = PlanDataAdvStringGrid->Floats[13][i];
				Line.StartY = PlanDataAdvStringGrid->Floats[14][i];
				Line.EndX = PlanDataAdvStringGrid->Floats[17][i];
				Line.EndY = PlanDataAdvStringGrid->Floats[18][i];
				Line.StartAngle = OppositeAngle(PlanDataAdvStringGrid->Floats[16][i]);
			} else {
				Line.StartX = PlanDataAdvStringGrid->Floats[17][i];
				Line.StartY = PlanDataAdvStringGrid->Floats[18][i];
				Line.EndX = PlanDataAdvStringGrid->Floats[13][i];
				Line.EndY = PlanDataAdvStringGrid->Floats[14][i];
				Line.StartAngle = PlanDataAdvStringGrid->Floats[16][i];
            }
			Line.Length = PlanDataAdvStringGrid->Floats[5][i];
			Plan.Lines.push_back(Line);
        }
        if (PlanDataAdvStringGrid->Cells[1][i] == L"圆弧") {         // Arc.SweepAngle < 0 凸曲线
            Arc.CenterX = PlanDataAdvStringGrid->Floats[6][i];		//	Arc.SweepAngle > 0 凹曲线
            Arc.CenterY = PlanDataAdvStringGrid->Floats[7][i];
            Arc.Radii = PlanDataAdvStringGrid->Floats[2][i];
            Arc.StartAngle = PlanDataAdvStringGrid->Floats[4][i];
            Arc.SweepAngle = PlanDataAdvStringGrid->Floats[9][i];
            Arc.StartX = Arc.CenterX + cos(Arc.StartAngle * 0.017453) * Arc.Radii;
            Arc.StartY = Arc.CenterY + sin(Arc.StartAngle * 0.017453) * Arc.Radii;
            Arc.EndX = Arc.CenterX + cos((Arc.StartAngle + Arc.SweepAngle) * 0.017453) * Arc.Radii;
			Arc.EndY = Arc.CenterY + sin((Arc.StartAngle + Arc.SweepAngle) * 0.017453) * Arc.Radii;
			if (Arc.StartX > Arc.EndX) {
				s = Arc.StartX;
				Arc.StartX = Arc.EndX;
				Arc.EndX = s;
				s = Arc.StartY;
				Arc.StartY = Arc.EndY;
				Arc.EndY = s;
				Arc.StartAngle += Arc.SweepAngle;
				Arc.SweepAngle = -Arc.SweepAngle;
			}
            Plan.Arcs.push_back(Arc);
        }
    }
    return;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DrawButtonClick(TObject *Sender)
{
	Import();
	Image1->Canvas->Pen->Color = clBlack;
    Plan.Draw(Image1);
    Image1->Show();
    return;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DistinguishCrossesButtonClick(TObject *Sender)
{
	Plan.DistinguishSwitches();
	Label1->Caption = Plan.Crosses.size();
	for (int i = 0; i < Plan.Crosses.size(); i++) {
		ListBox1->Items->Add(IntToStr(i) + L" --- " + Plan.Crosses[i].Lines.size());
	}
	return;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DrawSwitchesButtonClick(TObject *Sender)
{
	Plan.DrawCrosses(Image1);
	return;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ListBox1Click(TObject *Sender)
{
	Image1->Canvas->Pen->Color = clRed;
	Plan.Crosses[ListBox1->ItemIndex].Draw(Image1, Plan.Scale, Plan.OriginX, Plan.OriginY);
	return;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DistinguishPathsButtonClick(TObject *Sender)
{
	Plan.DistinguishPath();
    Label2->Caption = Plan.Paths.size();
    return;
}
//---------------------------------------------------------------------------

