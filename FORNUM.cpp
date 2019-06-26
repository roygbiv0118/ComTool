// FORNUM.cpp : implementation file
//

#include "stdafx.h"
#include "COMTOOL.h"
#include "FORNUM.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FORNUM dialog


FORNUM::FORNUM(CWnd* pParent /*=NULL*/)
	: CDialog(FORNUM::IDD, pParent)
{
	//{{AFX_DATA_INIT(FORNUM)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void FORNUM::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FORNUM)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FORNUM, CDialog)
	//{{AFX_MSG_MAP(FORNUM)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FORNUM message handlers

void FORNUM::OnOK() 
{
	 long sum  = 0;
	 if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck())
	 {
		 sum += 2;
	 }
	 if (((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck())
	 {
		 sum += 2*2;
	 }
	 if (((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck())
	 {
		 sum += 2*2*2;
	 }
	 if (((CButton*)GetDlgItem(IDC_CHECK4))->GetCheck())
	 {
		 sum += 2*2*2*2;
	 }
	 if (((CButton*)GetDlgItem(IDC_CHECK5))->GetCheck())
	 {
		 sum += 2*2*2*2*2;
	 }
	 if (((CButton*)GetDlgItem(IDC_CHECK6))->GetCheck())
	 {
		 sum += 2*2*2*2*2*2;
	 }
	 if (((CButton*)GetDlgItem(IDC_CHECK7))->GetCheck())
	 {
		 sum += 2*2*2*2*2*2*2;
	 }
	 if (((CButton*)GetDlgItem(IDC_CHECK8))->GetCheck())
	 {
		 sum += 2*2*2*2*2*2*2*2;
	 }
	 if (((CButton*)GetDlgItem(IDC_CHECK9))->GetCheck())
	 {
		 sum += 2*2*2*2*2*2*2*2*2;
	 }
	 if (((CButton*)GetDlgItem(IDC_CHECK10))->GetCheck())
	 {
		 sum += 2*2*2*2*2*2*2*2*2*2;
	 }
	 if (((CButton*)GetDlgItem(IDC_CHECK11))->GetCheck())
	 {
		 sum += 2*2*2*2*2*2*2*2*2*2*2;
	 }

	 m_num.Format("%d",sum);
	
	CDialog::OnOK();
}
