//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "SQLITE3CLASS.h"
#include "Sqlite3NextSuite.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NxCustomGrid"
#pragma link "NxCustomGridControl"
#pragma link "NxGrid"
#pragma link "NxGridPrint"
#pragma link "NxScrollControl"
#pragma link "NxThemesSupport"
#pragma link "SynEdit"
#pragma link "SynEditHighlighter"
#pragma link "SynHighlighterSQL"
#pragma link "SynMemo"
#pragma link "SynCompletionProposal"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool TForm1::ExecuteSQL(AnsiString sql)
{
   if (!_pdb || OpenedFileName == ""){
     StatusBar1->SimpleText = "Open a sqlite database file first (Ctrl+O)";
     return false;
   }

   char* zErrorMessage;
   if (!Sqlite3NextSuite::ExeToGrid(sql, NextGrid1, _pdb, zErrorMessage))
   {
      StatusBar1->SimpleText = zErrorMessage;
      return false;
   }
   else
   {
      StatusBar1->SimpleText = "# results: " + String(NextGrid1->RowCount);
      return true;
   }


   //old version below

   


   nsSQLITE3::quick_results qr;
   _pdb->quick_exe(sql.c_str(), qr);

   if (qr.result == 0){
      bool retVal = true;
       if (strlen(qr.zErrMsg) > 0){
          StatusBar1->SimpleText = qr.zErrMsg;
          retVal = false;
       }else{
          StatusBar1->SimpleText = "# results: 0";
          retVal = true;
       }
       //free results and return
       _pdb->free(qr.result);
       return retVal;
   }

   //ok no error with the statement
   StatusBar1->SimpleText = " # results: " + String(qr.nrow);

    TNxTextColumn *nxhColumn = NULL;
    NextGrid1->BeginUpdate();
    NextGrid1->Columns->Clear();
    NextGrid1->ClearRows();
    NextGrid1->AddRow(qr.nrow);

   for (int r = 0; r <= qr.nrow; ++r){
     String curColumn;
     for(int c = 0; c < qr.ncol; ++c){
        String cur = qr.result[ SQLITE3::calc_absolute_index(r, c, qr.ncol) ];

        //grab column from first row
        curColumn = qr.result[ SQLITE3::calc_absolute_index(0, c, qr.ncol) ];
        if (r == 0){

        
            //add to synedit autocomplete
            if (SynCompletionProposal1->ItemList->IndexOf(cur) == -1)
               SynCompletionProposal1->ItemList->Add(cur);



            nxhColumn = new TNxTextColumn(this);

            //nxhColumn->Name = "nxhWindow";
            nxhColumn->Font->Charset = DEFAULT_CHARSET;
            nxhColumn->Font->Color = clWindowText;
            nxhColumn->Font->Height = -11;
            nxhColumn->Font->Name = "MS Sans Serif";
            nxhColumn->Font->Style = TFontStyles();
            nxhColumn->Header->Caption = cur;
            nxhColumn->Position = r;
            nxhColumn->SortType = stAlphabetic;
            NextGrid1->Columns->AddColumn(nxhColumn);
        }else{ //normal row

            //auto-detect numeric rows by checking ONLY first data row
            if (r == 1){
                if (nxhColumn->SortType == stAlphabetic)
                {
                   try{
                      StrToInt(cur);
                      nxhColumn->SortType = stNumeric;
                   }catch(EConvertError& e){ }
                }
            }

            NextGrid1->Cell[c][r-1]->AsString = cur;
        }
     }
   }
   _pdb->free(qr.result);
   NextGrid1->BestFitColumns(bfBoth);
   NextGrid1->EndUpdate();
   return true;
}



void __fastcall TForm1::actExecuteSQLExecute(TObject *Sender)
{
   runHistory.push_back(SynMemo1->Text);
   runHistoryIndex = runHistory.size();

   if (ExecuteSQL(SynMemo1->Text))
   {
      SynMemo1->Clear();
   }
   else //do not clear memo
   {

   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FileOpen1Accept(TObject *Sender)
{
   delete _pdb;
   try{
      _pdb = new SQLITE3(FileOpen1->Dialog->FileName.c_str());
      OpenedFileName = FileOpen1->Dialog->FileName;
      StatusBar1->SimpleText = OpenedFileName;
      if (SynMemo1->Text.Length() == 0){
         SynMemo1->Lines->Add("SELECT * FROM sqlite_master ORDER BY rootpage DESC");
         actExecuteSQL->Execute();
      }
   }
   catch(...){
      OpenedFileName = "";
      _pdb = NULL;
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SynMemo1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   bool UpOrDown = false;
   if (Shift.Contains(ssCtrl) && Key == VK_RETURN)
   {
      actExecuteSQL->Execute();
   }
   else if (Key == VK_UP)
   {
      if (runHistoryIndex == runHistory.size()-1){
         runHistoryCurString = SynMemo1->Text;
      }
      runHistoryIndex--;
      Key = 0;
      UpOrDown = true;
   }
   else if (Key == VK_DOWN)
   {
      runHistoryIndex++;
      Key = 0;
      UpOrDown = true;
   }


   if (UpOrDown)
   {
     if (runHistoryIndex < runHistory.size())
     {
       if (runHistoryIndex >= 0)
          SynMemo1->Text = runHistory[runHistoryIndex];
     }
     else //index >= size()
     {
        SynMemo1->Text = runHistoryCurString;
     }
     
   }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::actFileCloseExecute(TObject *Sender)
{
   delete _pdb;
   _pdb = NULL;
   OpenedFileName = "";
   StatusBar1->SimpleText = "No file opened.";        
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCreate(TObject *Sender)
{
  actFileClose->Execute();        
}
//---------------------------------------------------------------------------






