object Form1: TForm1
  Left = 350
  Top = 185
  Width = 542
  Height = 490
  Caption = 'Sqlite3 Executor'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 301
    Width = 534
    Height = 3
    Cursor = crVSplit
    Align = alBottom
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 534
    Height = 301
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    object NextGrid1: TNextGrid
      Left = 0
      Top = 0
      Width = 534
      Height = 301
      Align = alClient
      TabOrder = 0
      TabStop = True
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 304
    Width = 534
    Height = 76
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    object SynMemo1: TSynMemo
      Left = 0
      Top = 0
      Width = 534
      Height = 76
      Align = alClient
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = []
      TabOrder = 0
      OnKeyDown = SynMemo1KeyDown
      Gutter.Font.Charset = DEFAULT_CHARSET
      Gutter.Font.Color = clWindowText
      Gutter.Font.Height = -11
      Gutter.Font.Name = 'Courier New'
      Gutter.Font.Style = []
      Highlighter = SynSQLSyn1
      Options = [eoAutoIndent, eoDragDropEditing, eoEnhanceEndKey, eoGroupUndo, eoShowScrollHint, eoSmartTabDelete, eoSmartTabs, eoTabsToSpaces]
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 380
    Width = 534
    Height = 56
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 2
    object btnExecSQL: TButton
      Left = 16
      Top = 8
      Width = 75
      Height = 25
      Action = actExecuteSQL
      TabOrder = 0
    end
    object StatusBar1: TStatusBar
      Left = 0
      Top = 37
      Width = 534
      Height = 19
      Panels = <>
      ParentShowHint = False
      ShowHint = True
      SimplePanel = True
    end
  end
  object NxGridPrint1: TNxGridPrint
    HeaderSize = 100
    Options = [poHorzGridLines]
    PageHeight = 0
    PageWidth = 0
    RowSize = 86
    Left = 64
    Top = 80
  end
  object NxColorScheme1: TNxColorScheme
    ColorScheme = csBlack
    Left = 32
    Top = 80
  end
  object SynSQLSyn1: TSynSQLSyn
    Left = 184
    Top = 304
  end
  object ActionList1: TActionList
    Left = 184
    Top = 8
    object FileOpen1: TFileOpen
      Category = 'File'
      Caption = '&Open Database...'
      Hint = 'Open|Opens an existing file'
      ImageIndex = 7
      ShortCut = 16463
      OnAccept = FileOpen1Accept
    end
    object actFileClose: TAction
      Category = 'File'
      Caption = 'Close Database'
      OnExecute = actFileCloseExecute
    end
    object actHelpAbout: TAction
      Category = 'File'
      Caption = 'About...'
      Hint = 'About Sqlite3 Executor'
    end
    object FileExit1: TFileExit
      Category = 'File'
      Caption = 'E&xit'
      Hint = 'Exit|Quits the application'
      ImageIndex = 43
    end
    object actExecuteSQL: TAction
      Category = 'SQL'
      Caption = 'Execute SQL'
      ShortCut = 16397
      OnExecute = actExecuteSQLExecute
    end
  end
  object MainMenu1: TMainMenu
    Left = 152
    Top = 8
    object File1: TMenuItem
      Caption = 'File'
      Hint = 'Exit|Quits the application'
      ImageIndex = 43
      object Open1: TMenuItem
        Action = FileOpen1
      end
      object CloseDatabase1: TMenuItem
        Action = actFileClose
      end
      object Exit1: TMenuItem
        Action = FileExit1
      end
    end
    object SQL1: TMenuItem
      Caption = 'SQL'
      object ExecuteSQL1: TMenuItem
        Action = actExecuteSQL
      end
    end
    object Help1: TMenuItem
      Caption = 'Help'
      object About1: TMenuItem
        Action = actHelpAbout
      end
    end
  end
  object SynCompletionProposal1: TSynCompletionProposal
    Options = [scoLimitToMatchedText, scoCompleteWithTab, scoCompleteWithEnter]
    ItemList.Strings = (
      'SELECT'
      'FROM'
      'sqlite_master'
      'WHERE'
      'ORDER BY'
      'GROUP BY')
    EndOfTokenChr = '()[]. '
    TriggerChars = '.'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clBtnText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = [fsBold]
    Columns = <>
    ShortCut = 16416
    Editor = SynMemo1
    Left = 192
    Top = 120
  end
end
