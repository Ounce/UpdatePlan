//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "BaseGrid.hpp"
#include <Vcl.Grids.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "TPlan.h"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TAdvStringGrid *PlanDataAdvStringGrid;
	TButton *OpenButton;
	TButton *CloseButton;
	TOpenDialog *ExcelOpenDialog;
	TImage *Image1;
	TButton *DrawButton;
	TButton *DistinguishButton;
	TLabel *Label1;
	TButton *DrawSwitchesButton;
	void __fastcall CloseButtonClick(TObject *Sender);
	void __fastcall OpenButtonClick(TObject *Sender);
	void __fastcall DrawButtonClick(TObject *Sender);
	void __fastcall DistinguishButtonClick(TObject *Sender);
	void __fastcall DrawSwitchesButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	TPlan Plan;
	__fastcall TMainForm(TComponent* Owner);
    void __fastcall Import(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
