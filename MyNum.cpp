// MyNum.cpp : implementation file
//

#include "stdafx.h"
#include "COMTOOL.h"
#include "MyNum.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyNum dialog


MyNum::MyNum(CWnd* pParent /*=NULL*/)
	: CDialog(MyNum::IDD, pParent)
{
	//{{AFX_DATA_INIT(MyNum)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MyNum::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MyNum)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MyNum, CDialog)
	//{{AFX_MSG_MAP(MyNum)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MyNum message handlers
