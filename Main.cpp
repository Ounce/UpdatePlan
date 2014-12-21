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
