// MyInput.cpp : implementation file
//

#include "stdafx.h"
#include "comtool.h"
#include "MyInput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyInput dialog


MyInput::MyInput(CWnd* pParent /*=NULL*/)
	: CDialog(MyInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(MyInput)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MyInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MyInput)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MyInput, CDialog)
	//{{AFX_MSG_MAP(MyInput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MyInput message handlers

BOOL MyInput::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void MyInput::OnOK() 
{
	GetDlgItemText(IDC_EDIT1,m_va);
	if(m_va=="")
	{
		AfxMessageBox("²»¿ÉÎª¿Õ");

		return;
	}
	
	CDialog::OnOK();
}
