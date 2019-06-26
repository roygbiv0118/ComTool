#if !defined(AFX_MYNUM_H__59E513FA_497C_4523_B1A6_001F68C6CE5F__INCLUDED_)
#define AFX_MYNUM_H__59E513FA_497C_4523_B1A6_001F68C6CE5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyNum.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MyNum dialog

class MyNum : public CDialog
{
// Construction
public:
	MyNum(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MyNum)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyNum)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MyNum)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYNUM_H__59E513FA_497C_4523_B1A6_001F68C6CE5F__INCLUDED_)
