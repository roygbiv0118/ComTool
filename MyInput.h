#if !defined(AFX_MYINPUT_H__EEA3917C_B63E_4602_AA8B_AE116899091E__INCLUDED_)
#define AFX_MYINPUT_H__EEA3917C_B63E_4602_AA8B_AE116899091E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyInput.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MyInput dialog

class MyInput : public CDialog
{
// Construction
public:
	MyInput(CWnd* pParent = NULL);   // standard constructor

	CString m_va;
// Dialog Data
	//{{AFX_DATA(MyInput)
	enum { IDD = IDD_DLG_INPUT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MyInput)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYINPUT_H__EEA3917C_B63E_4602_AA8B_AE116899091E__INCLUDED_)
