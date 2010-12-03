//---------------------------------------------------------------------------

#ifndef Sqlite3NextSuiteH
#define Sqlite3NextSuiteH
//---------------------------------------------------------------------------
#include <vcl>
#include "NxGrid.hpp"
#include "SQLITE3CLASS.h"

class Sqlite3NextSuite
{
public:
    static int isNumeric(char* str)
    {
        int len = strlen(str);          // get the length of string for iterations
        int i = 0;                      // iterator
        int ret = 1;                    // for the return type
        int deccnt = 0;                 // decimal counter
        while(i < len && ret != 0)
        {
            if(str[i] == '.')           // is there a decimal
            {
                deccnt++;               // count a decimal
                if(deccnt > 1)          // is there too many decimal points
                    ret = 0;            // too many decimals set return for not numeric
            }
            else
                ret = isdigit(str[i]); // is this character numeric
            i++;                       // increment to next character
        }
        return ret;                    // return result =0 not numeric !=0 is numeric
    }


    static bool ExeToGrid(const String& sql, TNextGrid* NextGrid, SQLITE3* pdb, char*& zErrorMsg)
    {
       nsSQLITE3::quick_results qr;
       pdb->quick_exe(sql.c_str(), qr);
       zErrorMsg = qr.zErrMsg;

       NextGrid->Columns->Clear();
       NextGrid->ClearRows();

       if (qr.result == 0){
          bool retVal = true;
           if (strlen(qr.zErrMsg) > 0){
              //StatusBar1->SimpleText = qr.zErrMsg;
              retVal = false;
           }else{
              //StatusBar1->SimpleText = "# results: 0";
              retVal = true;
           }
           //free results and return
           qr.free();
           return retVal;
       }

       //ok no error with the statement
       //StatusBar1->SimpleText = " # results: " + String(qr.nrow);

        TNxTextColumn *nxhColumn = NULL;
        NextGrid->BeginUpdate();
        NextGrid->AddRow(qr.nrow);

       for (int r = 0; r <= qr.nrow; ++r){
         String curColumn;
         for(int c = 0; c < qr.ncol; ++c){
            char* cur = qr.result[ SQLITE3::calc_absolute_index(r, c, qr.ncol) ];

            //grab column from first row
            curColumn = qr.result[ SQLITE3::calc_absolute_index(0, c, qr.ncol) ];
            if (r == 0){

                /*
                //add to synedit autocomplete
                if (SynCompletionProposal1->ItemList->IndexOf(cur) == -1)
                   SynCompletionProposal1->ItemList->Add(cur);
                */


                nxhColumn = new TNxTextColumn(NextGrid);

                //nxhColumn->Name = "nxhWindow";
                nxhColumn->Font->Charset = DEFAULT_CHARSET;
                nxhColumn->Font->Color = clWindowText;
                nxhColumn->Font->Height = -11;
                nxhColumn->Font->Name = "MS Sans Serif";
                nxhColumn->Font->Style = TFontStyles();
                nxhColumn->Header->Caption = cur;
                nxhColumn->Position = r;
                nxhColumn->SortType = stAlphabetic;
                NextGrid->Columns->AddColumn(nxhColumn);
            }else{ //normal row

                //auto-detect numeric rows by checking ONLY first data row
                if (r == 1){
                          if (Sqlite3NextSuite::isNumeric(cur))
                             nxhColumn->SortType = stNumeric;
                }

                NextGrid->Cell[c][r-1]->AsString = cur;
            }
         }
       }
       qr.free();
       NextGrid->BestFitColumns(bfBoth);
       NextGrid->EndUpdate();
       return true;
    }

};
#endif
