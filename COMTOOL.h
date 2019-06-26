// COMTOOL.h : main header file for the COMTOOL application
//

#if !defined(AFX_COMTOOL_H__6AD8468A_F275_419D_B3CC_5409147203DF__INCLUDED_)
#define AFX_COMTOOL_H__6AD8468A_F275_419D_B3CC_5409147203DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCOMTOOLApp:
// See COMTOOL.cpp for the implementation of this class
//

class CCOMTOOLApp : public CWinApp
{
public:
	CCOMTOOLApp();

	CString g_path;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCOMTOOLApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCOMTOOLApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CCOMTOOLApp theApp;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMTOOL_H__6AD8468A_F275_419D_B3CC_5409147203DF__INCLUDED_)
