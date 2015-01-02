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
	Plan.Clear();
    TLine Line;
    TArc Arc;
    for (int i = 1; i < PlanDataAdvStringGrid->RowCount; i++) {
		if (PlanDataAdvStringGrid->Cells[1][i] == L"Ö±Ïß") {
        	Line.StartX = PlanDataAdvStringGrid->Floats[17][i];
            Line.StartY = PlanDataAdvStringGrid->Floats[18][i];
            Line.EndX = PlanDataAdvStringGrid->Floats[13][i];
			Line.EndY = PlanDataAdvStringGrid->Floats[14][i];
			Line.Length = PlanDataAdvStringGrid->Floats[5][i];
            Plan.Lines.push_back(Line);
        }
        if (PlanDataAdvStringGrid->Cells[1][i] == L"Ô²»¡") {
            Arc.CenterX = PlanDataAdvStringGrid->Floats[6][i];
            Arc.CenterY = PlanDataAdvStringGrid->Floats[7][i];
            Arc.Radii = PlanDataAdvStringGrid->Floats[2][i];
            Arc.StartAngle = PlanDataAdvStringGrid->Floats[4][i];
            Arc.SweepAngle = PlanDataAdvStringGrid->Floats[9][i];
            Arc.StartX = Arc.CenterX + cos(Arc.StartAngle * 0.017453) * Arc.Radii;
            Arc.StartY = Arc.CenterY + sin(Arc.StartAngle * 0.017453) * Arc.Radii;
            Arc.EndX = Arc.CenterX + cos((Arc.StartAngle + Arc.SweepAngle) * 0.017453) * Arc.Radii;
            Arc.EndY = Arc.CenterY + sin((Arc.StartAngle + Arc.SweepAngle) * 0.017453) * Arc.Radii;
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

void __fastcall TMainForm::DistinguishButtonClick(TObject *Sender)
{
	Plan.DistinguishSwitches();
	Label1->Caption = Plan.Switches.size();
	for (int i = 0; i < Plan.Switches.size(); i++) {
		ListBox1->Items->Add(IntToStr(i) + L" --- " + Plan.Switches[i].Lines.size());
	}
	return;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DrawSwitchesButtonClick(TObject *Sender)
{
	Plan.DrawSwitches(Image1);
	return;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ListBox1Click(TObject *Sender)
{
	Image1->Canvas->Pen->Color = clRed;
	Plan.Switches[ListBox1->ItemIndex].Draw(Image1, Plan.Scale, Plan.OriginX, Plan.OriginY);
	return;
}
//---------------------------------------------------------------------------

