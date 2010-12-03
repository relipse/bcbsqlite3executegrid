//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "NxCustomGrid.hpp"
#include "NxCustomGridControl.hpp"
#include "NxGrid.hpp"
#include "NxGridPrint.hpp"
#include "NxScrollControl.hpp"
#include "NxThemesSupport.hpp"
#include "SynEdit.hpp"
#include "SynEditHighlighter.hpp"
#include "SynHighlighterSQL.hpp"
#include "SynMemo.hpp"
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <StdActns.hpp>
#include "SQLITE3CLASS.h"
#include "SynAutoCorrect.hpp"
#include "SynCompletionProposal.hpp"
#include <vector>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TNxGridPrint *NxGridPrint1;
        TNxColorScheme *NxColorScheme1;
        TPanel *Panel1;
        TNextGrid *NextGrid1;
        TSplitter *Splitter1;
        TPanel *Panel2;
        TSynSQLSyn *SynSQLSyn1;
        TSynMemo *SynMemo1;
        TPanel *Panel3;
        TButton *btnExecSQL;
        TActionList *ActionList1;
        TFileOpen *FileOpen1;
        TStatusBar *StatusBar1;
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *Open1;
        TAction *actFileClose;
        TMenuItem *CloseDatabase1;
        TAction *actHelpAbout;
        TFileExit *FileExit1;
        TMenuItem *Exit1;
        TMenuItem *Help1;
        TMenuItem *About1;
        TAction *actExecuteSQL;
        TMenuItem *SQL1;
        TMenuItem *ExecuteSQL1;
        TSynCompletionProposal *SynCompletionProposal1;
        void __fastcall actExecuteSQLExecute(TObject *Sender);
        void __fastcall FileOpen1Accept(TObject *Sender);
        void __fastcall SynMemo1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall actFileCloseExecute(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
        SQLITE3* _pdb;
        //SQLITE3* _pAppSettings;
        String OpenedFileName;

        std::vector<String> runHistory;
        int runHistoryIndex;
        String runHistoryCurString;
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);


        bool ExecuteSQL(AnsiString sql);
};





//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
