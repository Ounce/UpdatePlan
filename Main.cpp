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
void __fastcall TMainForm::DrawButtonClick(TObject *Sender)
{
	Import();
    Plan.Draw(Image1);
    Image1->Show();
    return;
}
//---------------------------------------------------------------------------

