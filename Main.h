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
	TButton *DistinguishCrossesButton;
	TLabel *Label1;
	TButton *DrawSwitchesButton;
	TListBox *ListBox1;
	TButton *DistinguishPathsButton;
	TButton *DrawPathsButton;
	TLabel *Label2;
	TListBox *ListBox2;
	TButton *Button1;
	TListBox *ListBox3;
	void __fastcall CloseButtonClick(TObject *Sender);
	void __fastcall OpenButtonClick(TObject *Sender);
	void __fastcall DrawButtonClick(TObject *Sender);
	void __fastcall DistinguishCrossesButtonClick(TObject *Sender);
	void __fastcall DrawSwitchesButtonClick(TObject *Sender);
	void __fastcall ListBox1Click(TObject *Sender);
	void __fastcall DistinguishPathsButtonClick(TObject *Sender);
	void __fastcall ListBox2Click(TObject *Sender);
	void __fastcall DrawPathsButtonClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
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
