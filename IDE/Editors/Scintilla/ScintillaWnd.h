/* @doc
 * @module ScintillaWnd.h | Definition of a Scintilla syntax coloring edit control for MFC<nl>
 * This program is an example how to use the excellent scintilla edit control of Neil Hodgson.<nl>
 * See www.scintilla.org for details<nl>
 * Author: Horst Br�ckner, hb@ec-logic.com<nl>
 * Environment: VisualC++ Version 6, static Build of Scintilla, SciLexer.dll as Lexer<nl>
 */

#ifndef __SCINTILLAWND_H__
#define __SCINTILLAWND_H__

#include "include\scintilla.h"
#include "include\scilexer.h"

////////////////////////////////////
// @class CScintillaWnd | Class of a GCL Scintilla syntax coloring edit control for MFC
// @base public | CWnd
//
class CScintillaWnd : public CWnd  
{
public:
// @access public constructor - destructor
// @cmember empty Constructor
	CScintillaWnd();
// @cmember destructor
	virtual ~CScintillaWnd();

	int ID;

public:
// @access public macro members
// @cmember return linenumber display flag
   BOOL GetDisplayLinenumbers (){return m_bLinenumbers;};
// @cmember return selection display flag
   BOOL GetDisplaySelection (){return m_bSelection;};
// @cmember return folding margin display flag
   BOOL GetDisplayFolding (){return m_bFolding;};
// @cmember set search flags
   virtual void SetSearchflags (int nSearchflags){m_nSearchflags = nSearchflags;};
   

public:
// @access public function members
// @cmember register a window class to use scintilla in a dialog
   static BOOL Register(CWinApp *app, UINT id);
// @cmember try to load Lexer DLL
   static HMODULE LoadScintillaDll (LPCSTR szLexerDll = NULL);
// @cmember create window
   virtual BOOL Create (LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
// @cmember Set Text to the Scintilla control
   virtual void SetText (LPCSTR szText);
// @cmember Get Text from the Scintilla control
   virtual void GetText (CString &strText);
// @cmember Get Text from the Scintilla control
   virtual LPSTR GetText();
// @cmember Load a file
   virtual BOOL LoadFile (LPCSTR szFile);
// @cmember Save a file
   virtual BOOL SaveFile (LPCSTR szFile);
// @cmember try to find lexer format from extension
   virtual int GetFormatFromExtension (LPCSTR szExtension);
// @cmember calcluate number of chars needed for linenumberdisplay
   virtual int GetLinenumberChars ();
// @cmember calcluate number of pixels for linenumber display
   virtual int GetLinenumberWidth ();
// @cmember set display of linenumbers on/off
   virtual void SetDisplayLinenumbers(BOOL bFlag = TRUE);
// @cmember set display of selection/bookmark margin on/off
   virtual void SetDisplaySelection(BOOL bFlag = TRUE);
// @cmember set display of source folding margin on/off
   virtual void SetDisplayFolding(BOOL bFlag = TRUE);
// @cmember cut selection to clipboard
   virtual void Cut();
// @cmember copy selection to clipboard
   virtual void Copy();
// @cmember paste from clipboard
   virtual void Paste();
// @cmember clear selection
   virtual void Clear();
// @cmember undo last change
   virtual void Undo();
// @cmember redo last change
   virtual void Redo();
// @cmember check if we can undo
   virtual BOOL CanUndo();
// @cmember check if we can redo
   virtual BOOL CanRedo();
// @cmember check if we have something to paste from clipboard
   virtual BOOL CanPaste();
// @cmember select complete text
   virtual void SelectAll();
// @cmember return the current line number
   virtual long GetCurrentLine();
// @cmember return the current column number
   virtual long GetCurrentColumn();
// @cmember return the current character position within the file
   virtual long GetCurrentPosition();
// @cmember return the current style number at the current character position
   virtual int GetCurrentStyle();
// @cmember return the current folding level at the current character position
   virtual int GetCurrentFoldinglevel();
// @cmember set the fontname for a style number
   virtual void SetFontname(int nStyle, LPCSTR szFontname);
// @cmember set the fontname height in points for a style number
   virtual void SetFontheight(int nStyle, int nHeight);
// @cmember set the foregroundcolor for a style number
   virtual void SetForeground(int nStyle, COLORREF crForeground);
// @cmember set the backgroundcolor for a style number
   virtual void SetBackground(int nStyle, COLORREF crBackground);
// @cmember set given style to bold
   virtual void SetBold(int nStyle, BOOL bFlag);
// @cmember set given style to bold
   virtual void SetItalic(int nStyle, BOOL bFlag);
// @cmember set given style to bold
   virtual void SetUnderline(int nStyle, BOOL bFlag);
// @cmember get flag if we are in overstrike mode
   virtual BOOL GetOverstrike();
// @cmember set flag for overstrike mode
   virtual void SetOverstrike(BOOL bOverstrike);
// @cmember init the view with reasonable defaults
   virtual void Init();
// @cmember called whenever the text is changed - we can update any indicators and do brace matching
   virtual void UpdateUI();
// @cmember do default folding 
   virtual void DoDefaultFolding(int nMargin, long lPosition);
// @cmember refresh lexer and display after new settings
   virtual void Refresh();
// @cmember add a bookmark = marker type 0
   virtual void AddBookmark(long lLine);
// @cmember delete a bookmark = marker type 0
   virtual void DeleteBookmark(long lLine);
// @cmember check for bookmark = marker type 0
   virtual BOOL HasBookmark(long lLine);
// @cmember Find next bookmark
   virtual void FindNextBookmark();
// @cmember Find previous bookmark
   virtual void FindPreviousBookmark();
// @cmember goto line
   virtual void GotoLine(long lLine);
// @cmember goto position
   virtual void GotoPosition(long lPos);
// @cmember search forward for a given text
   virtual BOOL SearchForward(LPSTR szText);
// @cmember search backward for a given text
   virtual BOOL SearchBackward(LPSTR szText);
// @cmember replace a text found by SearchForward or SearchBackward
   virtual void ReplaceSearchedText(LPCSTR szText);
// @cmember Set your own lexer
   virtual void SetLexer(int nLexer);
// @cmember return start position of selection
   virtual long GetSelectionStart();
// @cmember return end position of selection
   virtual long GetSelectionEnd();
// @cmember get selected text
   virtual CString GetSelectedText();
// @cmember replace all in buffer or selection
   virtual int ReplaceAll(LPCSTR szFind, LPCSTR szReplace, BOOL bSelection = TRUE);


protected:
// @access protected data members
// @cmember flag if we should display line numbers
   BOOL m_bLinenumbers;
// @cmember flag if we should display selection and bookmark margin
   BOOL m_bSelection;
// @cmember flag if we should display folding margin
   BOOL m_bFolding;
// @cmember search flags
   int  m_nSearchflags;

};
#define STR_SCINTILLAWND _T("Scintilla")
#define STR_LEXERDLL     _T("scilexer.dll")

#endif // !__SCINTILLAWND_H__
