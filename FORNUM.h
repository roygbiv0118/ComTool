#if !defined(AFX_FORNUM_H__67B779F4_9A0B_4DEE_BBEA_396B01BDBFF8__INCLUDED_)
#define AFX_FORNUM_H__67B779F4_9A0B_4DEE_BBEA_396B01BDBFF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FORNUM.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FORNUM dialog

class FORNUM : public CDialog
{
// Construction
public:
	FORNUM(CWnd* pParent = NULL);   // standard constructor
CString m_num;
// Dialog Data
	//{{AFX_DATA(FORNUM)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FORNUM)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(FORNUM)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORNUM_H__67B779F4_9A0B_4DEE_BBEA_396B01BDBFF8__INCLUDED_)
