// COMTOOLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "COMTOOL.h"
#include "COMTOOLDlg.h"
#include "stdlib.h"
#include "StdioFileEx.h"
#include "FORNUM.h"
#include <math.h>
#include "afxmt.h"
#include "MyInput.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define EditBoxWidth 50


int BaudRate[]={300,600,1200,2400,4800,9600,14400,19200,38400,56000,57600,115200,230400,460800,921600};
int ParitySelNum=5;
CString Parity[]={_T("None"),_T("Odd"),_T("Even"),_T("Mark"),_T("Space")};
int DataBits[]={5,6,7,8};
int StopBits[]={1,2};
vector<UINT> g_vec;
//
	CString m_zt = "02";//帧头
	UINT u_zt = 0x02;

	//
	CRITICAL_SECTION cs;//可以理解为锁定一个资源
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCOMTOOLDlg dialog

CCOMTOOLDlg::CCOMTOOLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCOMTOOLDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCOMTOOLDlg)
	m_strSend = _T("");
	m_strReceive = _T("");
	m_bHexR = true;
	m_bHexS = true;
	m_bAutoSend = FALSE;
	m_nSendPeriod = 1000;
	m_strStatus = _T("关闭");
	m_strSendBytes = _T("0");
	m_strReceiveBytes = _T("0");
	m_strPortNO = _T("");
	m_strBaudRate = _T("");
	m_strDataBits = _T("");
	m_strStopBits = _T("");
	m_strParity = _T("");
	m_nSendBytes=0;
	m_nReceiveBytes=0;
	m_f1 = _T("");


	 m_dy_txt= _T("");
	 m_dy_txt= _T("");
	 xie_readnum=0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCOMTOOLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCOMTOOLDlg)
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Control(pDX, IDC_Description, m_DescriptionCtrl);
	DDX_Control(pDX, IDC_Send, m_SendCtrl);
	DDX_Control(pDX, IDC_OpenClose, m_OpenCloseCtrl);
	DDX_Control(pDX, IDC_StopBits, m_StopBits);
	DDX_Control(pDX, IDC_ParityBits, m_Parity);
	DDX_Control(pDX, IDC_COM, m_PortNO);
	DDX_Control(pDX, IDC_Baudrate, m_BaudRate);
	DDX_Control(pDX, IDC_DataBits, m_DataBits);
	DDX_Control(pDX, IDC_SendPeriod, m_SendPeriodCtrl);
	DDX_Text(pDX, IDC_SendEdit, m_strSend);
	DDX_Text(pDX, IDC_ReceiveEdit, m_strReceive);
	DDX_Check(pDX, IDC_BHexR, m_bHexR);
	DDX_Check(pDX, IDC_BHexS, m_bHexS);
	DDX_Check(pDX, IDC_BAutoSend, m_bAutoSend);
	DDX_Text(pDX, IDC_SendPeriod, m_nSendPeriod);
	DDX_Text(pDX, IDC_Status, m_strStatus);
	DDX_Text(pDX, IDC_SendBytes, m_strSendBytes);
	DDX_Text(pDX, IDC_ReceiveBytes, m_strReceiveBytes);
	DDX_CBString(pDX, IDC_COM, m_strPortNO);
	DDX_CBString(pDX, IDC_Baudrate, m_strBaudRate);
	DDX_CBString(pDX, IDC_DataBits, m_strDataBits);
	DDX_CBString(pDX, IDC_StopBits, m_strStopBits);
	DDX_CBString(pDX, IDC_ParityBits, m_strParity);
	DDX_Text(pDX, IDC_TAB1_TXT, m_f1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCOMTOOLDlg, CDialog)
	//{{AFX_MSG_MAP(CCOMTOOLDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_BN_CLICKED(IDC_QUIT, OnQuit)
	ON_BN_CLICKED(IDC_ClearS, OnClearSendEdit)
	ON_BN_CLICKED(IDC_ClearR, OnClearReceiveEdit)
	ON_BN_CLICKED(IDC_BAutoSend, OnBAutoSend)
	ON_BN_CLICKED(IDC_OpenClose, OnOpenClose)
	ON_BN_CLICKED(IDC_ClearCounter, OnClearCounter)
	ON_MESSAGE(WM_COMM_RXCHAR,OnReceiveChar)
	ON_BN_CLICKED(IDC_Send, OnSend)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BHexS, OnBHexS)
	ON_BN_CLICKED(IDC_BHexR, OnBHexR)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_EN_SETFOCUS(IDC_V14, OnSetfocusV14)
	ON_EN_SETFOCUS(IDC_V10, OnSetfocusV10)
	ON_EN_KILLFOCUS(IDC_V10, OnKillfocusV10)
	ON_EN_SETFOCUS(IDC_V11, OnSetfocusV11)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCOMTOOLDlg message handlers

BOOL CCOMTOOLDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_ini.SetPath(theApp.g_path + "\\sys\\config.ini");

	CString spath = m_ini.GetKeyValue("txt","path");
	SetDlgItemText(IDC_PATH,spath);
	CString m_sRtxt="";

  

	  // 初始化 MFC 并在失败时显示错误
    if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
    {
        // TODO: 更改错误代码以符合您的需要
        _tprintf(_T("错误: MFC 初始化失败/n"));
        AfxMessageBox(_T("错误: MFC 初始化失败/n"));
    }
  


 


/*

CFile file;
file.Open(spath,CFile::modeRead,NULL); 
DWORD len=file.GetLength();
char Buf[1024*256+1];
Buf[len]=0;  //0终止字符串，用于输出。
file.Read(Buf,len);   //Read( void* lpBuf, UINT nCount ) lpBuf是用于接收读取到的数据的Buf指针nCount是从文件读取的字节数
MessageBox(Buf);
*/

//	CStdioFile file; 
//	CString strLine;
//	if(!file.Open( spath,CFile::modeRead)) 
//		;//打开*.TXT这个文件，打开形式为读取
//	else
//	{
//	
//		while(file.ReadString(strLine))
//		{ 
//			m_sRtxt += strLine;
//		} 
//	}
//	file.Close();
	SetDlgItemText(IDC_TXT,m_sRtxt);
//AfxMessageBox(m_ini.GetKeyValue("cv","10001")) ;
	m_tab.InsertItem(0,"打印界面");
	m_tab.InsertItem(1,"详细状态配置标签");
	m_tab.InsertItem(2,"患者信息配置标签");


	for(int i=10001;i<10025;i++)
	{
		GetDlgItem(i)->ShowWindow(0);
		CString sd;
		sd.Format("%d",i);
		SetDlgItemText(i,m_ini.GetKeyValue("cv",sd));
	}

	for(i=20001;i<20025;i++)
		GetDlgItem(i)->ShowWindow(0);

	// TODO: Add extra initialization here
	m_SendPeriodCtrl.EnableWindow(m_bAutoSend);
	m_OpenCloseCtrl.SetWindowText(_T("打开串口"));
	m_DescriptionCtrl.SetWindowText("");
	if(m_bHexS)
		GetDlgItem(IDC_SendEdit)->ModifyStyle(0,ES_UPPERCASE,0);
	else
		GetDlgItem(IDC_SendEdit)->ModifyStyle(ES_UPPERCASE,0,0);

	if(m_bHexR)
		GetDlgItem(IDC_ReceiveEdit)->ModifyStyle(0,ES_UPPERCASE,0);
	else
		GetDlgItem(IDC_ReceiveEdit)->ModifyStyle(ES_UPPERCASE,0,0);
	CString temp;
	
	//显示波特率
	for( i=0;i<sizeof(BaudRate)/sizeof(int);i++)
	{
		temp.Format("%d",BaudRate[i]);
		m_BaudRate.AddString((LPCTSTR)temp);
	}
	temp.Format("%d",38400);
	m_BaudRate.SetCurSel(m_BaudRate.FindString(0,temp));
	
	
	//显示奇偶校验
	for (i=0;i<ParitySelNum;i++)
	{
		m_Parity.AddString((LPCTSTR) Parity[i]);
	}
	m_Parity.SetCurSel(m_Parity.FindString(0,_T("None")));
	//显示停止位
	for(i=0;i<sizeof(StopBits)/sizeof(int);i++)
	{
		temp.Format("%d",StopBits[i]);
		m_StopBits.AddString((LPCTSTR)temp);
	}
	temp.Format("%d",2);
	m_StopBits.SetCurSel(m_StopBits.FindString(0,(LPCTSTR)temp));
	
	//显示数据位
	for(i=0;i<sizeof(DataBits)/sizeof(int);i++)
	{
		temp.Format("%d",DataBits[i]);
		m_DataBits.AddString((LPCTSTR)temp);
	}
	temp.Format("%d",8);
	m_DataBits.SetCurSel(m_DataBits.FindString(0,(LPCTSTR)temp));
	
	//显示串口设置
	for(i=1;i<=MaxSerialPortNum-1;i++)
	{
		if(m_SerialPort.InitPort(this,i))
		{
			temp.Format("COM%d",i);		
			m_PortNO.AddString((LPCTSTR)temp);
		}
	}
	if(m_PortNO.GetCount())
	{
		m_SerialPort.InitPort(this,MaxSerialPortNum);
		m_PortNO.SetCurSel(0);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCOMTOOLDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCOMTOOLDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCOMTOOLDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCOMTOOLDlg::OnAbout() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}

void CCOMTOOLDlg::OnQuit() 
{
	// TODO: Add your control notification handler code here
	m_SerialPort.InitPort(this,MaxSerialPortNum);
	PostQuitMessage(0);
	
}

void CCOMTOOLDlg::OnClearSendEdit() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	m_strSend=_T("");
	UpdateData(false);
}

void CCOMTOOLDlg::OnClearReceiveEdit() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	m_strReceive=_T("");
	UpdateData(false);
}

void CCOMTOOLDlg::OnBAutoSend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	m_SendPeriodCtrl.EnableWindow(m_bAutoSend);
	if(m_bAutoSend)	
	{
		m_SendCtrl.SetWindowText("开始自动发送");
	}
	else
	{
		m_SendCtrl.SetWindowText("手动发送");
		KillTimer(1);
	}
}

void CCOMTOOLDlg::OnOpenClose() 
{
	// TODO: Add your control notification handler code here
	CString temp;
	m_OpenCloseCtrl.GetWindowText(temp);
	UpdateData(true);
	if(temp==_T("关闭串口"))
	{
		g_vec.clear();
	 
		try
		{
		//	m_SerialPort.InitPort(this,MaxSerialPortNum);
				m_SerialPort.ClosePort();
		}catch (...) {
			AfxMessageBox("d");
		}
		KillTimer(2);
		m_OpenCloseCtrl.SetWindowText(_T("打开串口"));
		m_strStatus=_T("关闭");
		UpdateData(false);
		
		m_DescriptionCtrl.SetWindowText("");
		m_SendCtrl.GetWindowText(temp);
		if(temp=="停止自动发送")
		{
			KillTimer(1);
			m_SendCtrl.SetWindowText("开始自动发送");
		}
	}
	else if( m_PortNO.GetCount())
	{	
		int SelPortNO,SelBaudRate,SelDataBits,SelStopBits;
		char SelParity;
		UpdateData(true);
		temp=m_strPortNO;
		temp.Delete(0,3);
		SelPortNO=atoi(temp);
		SelBaudRate=atoi(m_strBaudRate);
		SelDataBits=atoi(m_strDataBits);
		SelParity=m_strParity.GetAt(0);
		SelStopBits=atoi(m_strStopBits);
		if(m_SerialPort.InitPort(this,SelPortNO,SelBaudRate,SelParity,SelDataBits,SelStopBits,EV_RXCHAR|EV_CTS,512))		
		{
			m_SerialPort.StartMonitoring();
			m_OpenCloseCtrl.SetWindowText(_T("关闭串口"));
			m_strStatus=_T("打开");
			UpdateData(false);
			temp=m_strPortNO+"  , 波特率:  "+m_strBaudRate+"bps, 校验位:  "+m_strParity+
				", 数据为:  "+m_strDataBits+" , 停止位:  "+m_strStopBits;
			m_DescriptionCtrl.SetWindowText(temp);

			SetTimer(2,600,NULL);;
		}
		else 
			AfxMessageBox("该串口已经被其他应用程序所占用!\n请选择其它的串口");
	}
}

void CCOMTOOLDlg::OnClearCounter() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	m_nSendBytes=0;
	m_nReceiveBytes=0;
	m_strSendBytes=_T("0");
	m_strReceiveBytes=_T("0");
	m_dy_txt="";
		m_read_txt="";
	UpdateData(false);
}


void CCOMTOOLDlg::OnSend() 
{
	// TODO: Add your control notification handler code here
	CString temp;
	UpdateData(true);
	if(m_strStatus=="关闭")
	{
		AfxMessageBox("请首先打开串口");
		return;
	}
	if(!m_bAutoSend)
	{	
		temp=m_strSend;
		if(m_bHexS)
			temp=ChangeCharstr2Hexstr(temp);
		m_SerialPort.WriteToPort(temp.GetBuffer(temp.GetLength()),temp.GetLength());
		m_nSendBytes+=temp.GetLength();
		m_strSendBytes.Format("%d",m_nSendBytes);
		UpdateData(false);
	}
	else 
	{
		m_SendCtrl.GetWindowText(temp);
		if(temp=="停止自动发送")
		{
			KillTimer(1);
			m_SendCtrl.SetWindowText("开始自动发送");
			UpdateData(false);
		}
		else
		{
			SetTimer(1,m_nSendPeriod,NULL);
			m_SendCtrl.SetWindowText("停止自动发送");
		}
	}
	//temp.Format("%d",
	//AfxMessageBox(temp);
}

void CCOMTOOLDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default


	if (nIDEvent == 2)
	{
		CString ss;
		ss.Format("%d",xie_readnum);
		UpdateData(false);
		SetDlgItemText(IDC_ReceiveBytes,ss);
		SetDlgItemText(IDC_TAB1_TXT,m_dy_txt);
		SetDlgItemText(IDC_ReceiveEdit,m_read_txt);
		if (m_read_txt.GetLength() >0)
		{
				((CEdit*)GetDlgItem(IDC_ReceiveEdit))->LineScroll(m_strReceive.GetLength()/(((CEdit*)GetDlgItem(IDC_ReceiveEdit))->LineLength()));
			 
			
		}

		if (m_strReceive.GetLength() >0)
		{
				((CEdit*)GetDlgItem(IDC_ReceiveEdit))->LineScroll(m_strReceive.GetLength()/(((CEdit*)GetDlgItem(IDC_ReceiveEdit))->LineLength()));
			
		}
//		if (m_read_txt.GetLength() >10000)
//		{
//			m_read_txt = "";
//			m_dy_txt = "";
//		}
	}else
	{

		UpdateData(true);
		CString temp;
		temp=m_strSend;
		if(m_bHexS)
			temp=ChangeCharstr2Hexstr(temp);
		m_SerialPort.WriteToPort(temp.GetBuffer(temp.GetLength()),temp.GetLength());
		m_nSendBytes+=temp.GetLength();
		m_strSendBytes.Format("%d",m_nSendBytes);
		UpdateData(false);
	}
	CDialog::OnTimer(nIDEvent);
}
//////////////////////////////////////////////////////////////////////////

//BYTE g_re[10];
#define PKT_LEN_DEFAULT 128
UINT ThreadFun(LPVOID lpParam)
{
	EnterCriticalSection(&cs);//加锁 接下来的代码处理过程中不允许其他线程进行操作，除非遇到
	CCOMTOOLDlg* p = (CCOMTOOLDlg*)lpParam;
//SYSTEMTIME st1,st2;
CString strTime1,strTime2;
 
 
	try
	{
					CString m_XmlFile1;
					p->GetDlgItemText(IDC_PATH,m_XmlFile1);
					
					  CFile stdFile;
					  stdFile.Open(m_XmlFile1, CFile::modeRead | CFile::typeBinary);
					  DWORD fileLen = stdFile.GetLength();
					  char *pBuf = new char[PKT_LEN_DEFAULT]; 	  
					  stdFile.SeekToBegin();
					  
				/*	CStdioFile file,file2;		
					if(!file.Open("pd.txt", CFile::modeCreate | CFile::modeWrite))
					{
						AfxMessageBox("ee");
							return 0;
					}

					if(!file2.Open("pd2.txt", CFile::modeCreate | CFile::modeWrite))
					{
						AfxMessageBox("ee");
							return 0;
					}
				*/	

					  for (int i =0;i<fileLen/PKT_LEN_DEFAULT;i++)
					  {
						 // GetLocalTime(&st1);
						 
						 
						 
						memset(pBuf,0,sizeof(char)*PKT_LEN_DEFAULT);
						stdFile.Seek(PKT_LEN_DEFAULT*i,CFile::begin);
						int sl = stdFile.Read(pBuf, PKT_LEN_DEFAULT);
		  				p->m_SerialPort.WriteToPort(pBuf,PKT_LEN_DEFAULT);
						 
					//	p->m_nSendBytes+=sl;
						//p->m_strSendBytes.Format("%d",p->m_nSendBytes);
					 	Sleep(25);


					/*	GetLocalTime(&st2);
						 strTime2.Format("%2d:%2d:%2d\n",st2.wMinute,st2.wSecond,st2.wMilliseconds);
						 file2.WriteString(strTime2);
						 if( st2.wMinute*60*1000+st2.wSecond*1000+st2.wMilliseconds - (st1.wMinute*60*1000+st1.wSecond*1000+st1.wMilliseconds) >25)
						 {
							 CString str;
							 str.Format("%d\n", st2.wMinute*60*1000+st2.wSecond*1000+st2.wMilliseconds - (st1.wMinute*60*1000+st1.wSecond*1000+st1.wMilliseconds));
							 file.WriteString(str);
						 }
					*/	
					  }
					  delete pBuf;
					  stdFile.Close();
					 // file.Close();
	}catch (...) {
		//AfxMessageBox("发送失败");
	}
		 LeaveCriticalSection(&cs);//解锁+
       return 0;
}
void CCOMTOOLDlg::DoReceive(UINT ch)
{

	g_vec.push_back(ch);

	if (g_vec.size() == 6)
	{
		//详细状态
		if(g_vec[0] == 0x02 && g_vec[1] == 0x41 && g_vec[2] == 0x32 &&	g_vec[3] == 0x37 &&	g_vec[4] == 0x31 &&	g_vec[5] == 0x03)
		{
			CString tz = "02";
			UINT tz_0x = 0x02;

			CString ml = " 41 32 ";//命令
			UINT ml_0x1 = 0x41;
			UINT ml_0x2 = 0x32;


			CString zw = "03";//尾
			UINT zw_0x = 0x03;
			if(((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck())//头
			{
					tz = "00";
					tz_0x= 0x30;
			}

			if(((CButton *)GetDlgItem(IDC_CHECK2))->GetCheck())//尾
			{
					zw = "00";
					tz_0x= 0x30;
				
			}
		 
			if(((CButton *)GetDlgItem(IDC_CHECK4))->GetCheck())//命令字节
			{
				
				 ml = " 64 33 ";
				 ml_0x1 = 0x64;
				 ml_0x2 = 0x33;
			}
			
			
			

			CString str[16];
			CString temp=  ChangeCharstr2Hexstr(tz + ml);

			CString bcc_str;
			UINT bcc = tz_0x^ml_0x1^ml_0x2;
				
			for (int i=0;i<16;i++)
			{
				GetDlgItemText(i+10001,str[i]); 
			
				//============================================================
				if(((CButton *)GetDlgItem(IDC_CHECK5))->GetCheck())//数据区
				{
					str[i] = "error";
					
				}
				if(((CButton *)GetDlgItem(IDC_CHECK6))->GetCheck())//随机注入
				{
					int  ri = rand()%16 ;
					if (i = ri)
					{
						str[i] += "sjzr"; 
					}
					
				} 

				if (i==15)
				{
					temp += str[i];

				}else if(i==10 || i==9)
				{
					CString st10;
					st10.Format("%.0f",atof(str[i])*52);
					str[i] = st10;

					temp += st10 + ",";
					
				//	AfxMessageBox(st10);
				}
				else
					temp += str[i] + ",";

			
				//============================================================

				for (int j=0;j< str[i].GetLength();j++)
				{
					bcc ^= str[i][j];
		
				}
	
				if (i != 15)
				{
					bcc ^= ',';
				}
			}
			
			if(((CButton *)GetDlgItem(IDC_CHECK3))->GetCheck())//校验
			{
			 	bcc ^= ',';
			}


			bcc_str.Format("%02x",bcc);
			temp +=  bcc_str + ChangeCharstr2Hexstr(zw);
			m_SerialPort.WriteToPort(temp.GetBuffer(temp.GetLength()),temp.GetLength());
			m_nSendBytes+=temp.GetLength();
			m_strSendBytes.Format("%d",m_nSendBytes);
		//	UpdateData(false);


		}else if(g_vec[0] == 0x02 && g_vec[1] == 0x41 && g_vec[2] == 0x31 &&	g_vec[3] == 0x37 &&	g_vec[4] == 0x32 &&	g_vec[5] == 0x03)//患者信息
		{


			m_dy_txt += "读取患者信息:02 41 31 37 32 03\r\n";


			CString str[8];
			CString temp=  ChangeCharstr2Hexstr(m_zt + " 41 31 ");
		
			CString bcc_str;
			UINT bcc = u_zt^0x41^0x31;
			
			for (int i=0;i<8;i++)
			{
				GetDlgItemText(i+10017,str[i]); 
				if (i==7)
				{
					temp += str[i];
				}else
					temp += str[i] + ",";

			
				for (int j=0;j< str[i].GetLength();j++)
				{
					bcc ^= str[i][j];
		
				}
	
				if (i != 7)
				{
					bcc ^= ',';
				}
			}
			bcc_str.Format("%02x",bcc);
			temp +=  bcc_str+ChangeCharstr2Hexstr("03");


			m_SerialPort.WriteToPort(temp.GetBuffer(temp.GetLength()),temp.GetLength());
			m_nSendBytes+=temp.GetLength();
			m_strSendBytes.Format("%d",m_nSendBytes);
		//	UpdateData(false);
		}else if(g_vec[0] == 0x02 && g_vec[1] == 0x41 && g_vec[2] == 0x33 && g_vec[3] == 0x37 &&	g_vec[4] == 0x30 &&	g_vec[5] == 0x03)//获取控制器时间
		{

//			m_f1 += "获取控制器时间:";
//			for (int i=0;i<5;i++)
//			{
//				m_f1 += DevideHexChar(g_vec[i])+_T(",");
//			}
//			m_f1 += DevideHexChar(g_vec[5]);
//			m_f1 += "\r\n";
			m_dy_txt += "获取控制器时间:02 41 33 37 30 03\r\n";

			CString temp=  ChangeCharstr2Hexstr(m_zt + " 41 33 ");
			CString bcc_str;
			UINT bcc = u_zt^0x41^0x33;
			SYSTEMTIME st;
			CString strTime;
			GetLocalTime(&st);
			strTime.Format("%04d-%02d-%02d %02d:%02d:%02d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
			for (int j=0;j< strTime.GetLength();j++)
			{
				bcc ^= strTime[j];
			}

			bcc_str.Format("%02x",bcc);
			temp +=  strTime+bcc_str+ChangeCharstr2Hexstr("03");


			m_SerialPort.WriteToPort(temp.GetBuffer(temp.GetLength()),temp.GetLength());
			m_nSendBytes+=temp.GetLength();
			m_strSendBytes.Format("%d",m_nSendBytes);
		//	UpdateData(false);

		}else if(g_vec[0] == 0x02 && g_vec[1] == 0x41 && g_vec[2] == 0x34 && g_vec[3] == 0x37 && g_vec[4] == 0x37 &&	g_vec[5] == 0x03)//获取日志
		{
				m_dy_txt += "获取日志:02 41 34 37 37 03\r\n";
				InitializeCriticalSection(&cs);//初始化结构CRITICAL_SECTION
				CWinThread* pThread = AfxBeginThread(ThreadFun, this); //接下来做啥就直接调用pThead就行.
			/*
				CString m_XmlFile1;
				GetDlgItemText(IDC_PATH,m_XmlFile1);
				  CStdioFile stdFile;
				  stdFile.Open(m_XmlFile1, CFile::modeRead | CFile::typeBinary);
				  DWORD fileLen = stdFile.GetLength();
				  char *pBuf = new char[256];
				  for (int i =0;i<1024;i++)
				  {
					int sl = stdFile.Read(pBuf, 256);
					stdFile.Seek(256,CFile::current);
		  				m_SerialPort.WriteToPort(pBuf,256);
						Sleep(5);
				  }
				  delete pBuf;
				  stdFile.Close();
*/
		}
	}
 
	if (g_vec[g_vec.size()-1] == 0x03)
	{
		//AfxMessageBox("3");
		if (g_vec[0] == 0x02 && g_vec[1] == 0x30 && g_vec[2] == 0x31 )
		{
			
				CString ss;
				for (int i=3;i<g_vec.size()-3;i++)
				{
					CString str;
					str.Format("%c",g_vec[i]);
					ss += str;
				}
				ss += ",";
				
				CString strsub[8];
				 
					for (int j=0;j<8;j++)
					{
						AfxExtractSubString(strsub[j],ss,j,',');
						SetDlgItemText(10017+j,strsub[j]);
					}
				


			CString sinfo,stm;
			sinfo = "设置患者信息:";
			for ( i=0;i<g_vec.size();i++)
			{
				stm.Format("%02x ",g_vec[i]);
				sinfo+=stm;
			}
			m_dy_txt += sinfo + "\r\n";
			CString temp=  ChangeCharstr2Hexstr(m_zt + " 30 31 41 43 4B ");
			CString bcc_str;
			UINT bcc = u_zt^0x30^0x31^0x41^0x43^0x4B;
			 bcc_str.Format("%02x",bcc);
			temp +=   bcc_str + ChangeCharstr2Hexstr("03");


			m_SerialPort.WriteToPort(temp.GetBuffer(temp.GetLength()),temp.GetLength());
			m_nSendBytes+=temp.GetLength();
			m_strSendBytes.Format("%d",m_nSendBytes);
		//	UpdateData(false);

		}else if (g_vec[0] == 0x02 && g_vec[1] == 0x30 && g_vec[2] == 0x32 )
		{

			CString sinfo,stm;
			sinfo = "设置控制器时间:";
			for (int i=0;i<g_vec.size();i++)
			{
				stm.Format("%02x ",g_vec[i]);
				sinfo+=stm;
			}
			m_dy_txt += sinfo + "\r\n";
			CString temp=  ChangeCharstr2Hexstr(m_zt + " 30 32 41 43 4B ");
			CString bcc_str;
			UINT bcc = u_zt^0x30^0x32^0x41^0x43^0x4B;
			 bcc_str.Format("%02x",bcc);
			temp +=   bcc_str + ChangeCharstr2Hexstr("03");


			m_SerialPort.WriteToPort(temp.GetBuffer(temp.GetLength()),temp.GetLength());
			m_nSendBytes+=temp.GetLength();
			m_strSendBytes.Format("%d",m_nSendBytes);
		//	UpdateData(false);

		}else if (g_vec[0] == 0x02 && g_vec[1] == 0x30 && g_vec[2] == 0x33 )
		{
				CString sinfo,stm;

		 if (g_vec.size() > 3)
				if (g_vec[3] == 0x30)
				{
					SetDlgItemText(10003,"0");
						sinfo = "设置血泵停止:";
				}else if (g_vec[3] == 0x31)
				{
					SetDlgItemText(10003,"2");
						sinfo = "设置血泵启动:";
				}

			 
		
		
			for (int i=0;i<g_vec.size();i++)
			{
				stm.Format("%02x ",g_vec[i]);
				sinfo+=stm;
			}
			m_dy_txt += sinfo + "\r\n";
			CString temp=  ChangeCharstr2Hexstr(m_zt + " 30 33 41 43 4B ");
			CString bcc_str;
			UINT bcc = u_zt^0x30^0x33^0x41^0x43^0x4B;
			 bcc_str.Format("%02x",bcc);
			temp +=   bcc_str + ChangeCharstr2Hexstr("03");


			m_SerialPort.WriteToPort(temp.GetBuffer(temp.GetLength()),temp.GetLength());
			m_nSendBytes+=temp.GetLength();
			m_strSendBytes.Format("%d",m_nSendBytes);
		//	UpdateData(false);

		}else if (g_vec[0] == 0x02 && g_vec[1] == 0x30 && g_vec[2] == 0x34 )
		{
			
				CString sinfo,stm;

				if (g_vec.size() > 3)
					if (g_vec[3] == 0x2b)
						{
							CString strva,strvaadd;
							GetDlgItemText(10005,strva);
							strvaadd.Format("%d",atoi(strva)+20);
							SetDlgItemText(10005,strvaadd);	
						}else if (g_vec[3] == 0x2d)
						{
							CString strva,strvaadd;
							GetDlgItemText(10005,strva);
							strvaadd.Format("%d",atoi(strva)-20);
							SetDlgItemText(10005,strvaadd);	
							 
						}




		
			sinfo = "设置转速:";
			for (int i=0;i<g_vec.size();i++)
			{
				stm.Format("%02x ",g_vec[i]);
				sinfo+=stm;
			}
			m_dy_txt += sinfo + "\r\n";
			CString temp=  ChangeCharstr2Hexstr(m_zt + " 30 34 41 43 4B ");
			CString bcc_str;
			UINT bcc = u_zt^0x30^0x34^0x41^0x43^0x4B;
			 bcc_str.Format("%02x",bcc);
			temp +=   bcc_str + ChangeCharstr2Hexstr("03");


			m_SerialPort.WriteToPort(temp.GetBuffer(temp.GetLength()),temp.GetLength());
			m_nSendBytes+=temp.GetLength();
			m_strSendBytes.Format("%d",m_nSendBytes);
		//	UpdateData(false);

		}else if (g_vec[0] == 0x02 && g_vec[1] == 0x30 && g_vec[2] == 0x35 )
		{
			CString sinfo,stm;
		
			if (g_vec.size() > 3)
				if (g_vec[3] == 0x30)
					{
						SetDlgItemText(10013,"0");
							sinfo = "设置静音取消:";
					}else if (g_vec[3] == 0x31)
					{
						SetDlgItemText(10013,"1");
							sinfo = "设置静音:";
					}

			
			for (int i=0;i<g_vec.size();i++)
			{
				stm.Format("%02x ",g_vec[i]);
				sinfo+=stm;
			}
			m_dy_txt += sinfo + "\r\n";
			CString temp=  ChangeCharstr2Hexstr(m_zt + " 30 35 41 43 4B ");
			CString bcc_str;
			UINT bcc = u_zt^0x30^0x35^0x41^0x43^0x4B;
			 bcc_str.Format("%02x",bcc);
			temp +=   bcc_str + ChangeCharstr2Hexstr("03");


			m_SerialPort.WriteToPort(temp.GetBuffer(temp.GetLength()),temp.GetLength());
			m_nSendBytes+=temp.GetLength();
			m_strSendBytes.Format("%d",m_nSendBytes);
		//	UpdateData(false);

		}else if (g_vec[0] == 0x02 && g_vec[1] == 0x30 && g_vec[2] == 0x36 )
		{

			CString sinfo,stm;
			sinfo = "设置HCT:";
			for (int i=0;i<g_vec.size();i++)
			{
				stm.Format("%02x ",g_vec[i]);
				sinfo+=stm;
			}
			m_dy_txt += sinfo + "\r\n";
			CString temp=  ChangeCharstr2Hexstr(m_zt + " 30 36 41 43 4B ");
			CString bcc_str;
			UINT bcc = u_zt^0x30^0x36^0x41^0x43^0x4B;
			 bcc_str.Format("%02x",bcc);
			temp +=  bcc_str + ChangeCharstr2Hexstr("03");


			m_SerialPort.WriteToPort(temp.GetBuffer(temp.GetLength()),temp.GetLength());
			m_nSendBytes+=temp.GetLength();
			m_strSendBytes.Format("%d",m_nSendBytes);
		//	UpdateData(false);

		}
	}



	if (g_vec.size()>1000)
	{
		g_vec.clear();
	}
	
}
bool flag =true;
void CCOMTOOLDlg::OnReceiveChar(UINT ch, LONG port)
{
#ifndef IS_DOMESTIC
				OutputDebugString(">>>foreign\n");
				ch = unsigned char(~ch);
#else
				OutputDebugString(">>>domestic\n");
#endif
				UpdateData(true);
				m_nReceiveBytes++;
				CString temp;
				temp.Format("%d",m_nReceiveBytes);
				m_strReceiveBytes=temp;
			//	UpdateData(false);


				xie_readnum++;

				if(m_bHexR)
				{
					if (ch == 0x02)
					{
						g_vec.clear();
					}
					m_read_txt+=DevideHexChar(ch)+_T(" ");
				//	m_strReceive+=DevideHexChar(ch)+_T(" ");
					if (ch == 0x03)
					{
						m_read_txt+="\r\n";
					}
					DoReceive(ch);
				}
				else
					m_strReceive+=ch;
	//			UpdateData(false);

	/*			((CEdit*)GetDlgItem(IDC_ReceiveEdit))->LineScroll(
					m_strReceive.GetLength()/(((CEdit*)GetDlgItem(IDC_ReceiveEdit))->LineLength()));
*/
}

CString CCOMTOOLDlg::ChangeCharstr2Hexstr(CString Charstr)
{
	CString Hexstr=_T("");
	Charstr.MakeUpper();
	HexStringFilter(Charstr);
	int Length=Charstr.GetLength();
	if(Length%2)
		Charstr.Delete(Length-1);
	Length=Charstr.GetLength();
	for(int i=0;i<Length/2;i++)
	{
		Hexstr+=CombineHexChar(Charstr.GetAt(i*2),Charstr.GetAt(i*2+1));
	}
	return Hexstr;
}

void CCOMTOOLDlg::OnBHexS() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_bHexS)
		GetDlgItem(IDC_SendEdit)->ModifyStyle(0,ES_UPPERCASE,0);
	else
		GetDlgItem(IDC_SendEdit)->ModifyStyle(ES_UPPERCASE,0,0);
}

void CCOMTOOLDlg::OnBHexR() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_bHexR)
		GetDlgItem(IDC_ReceiveEdit)->ModifyStyle(0,ES_UPPERCASE,0);
	else
		GetDlgItem(IDC_ReceiveEdit)->ModifyStyle(ES_UPPERCASE,0,0);
}

void CCOMTOOLDlg::HexStringFilter(CString &str)
{
	BOOL bOK;
	for(int i=0;i<str.GetLength();)
	{
		bOK=((str.GetAt(i)>='0')&&(str.GetAt(i)<='9'))||
			((str.GetAt(i)>='A')&&(str.GetAt(i)<='F'))||
			((str.GetAt(i)>='a')&&(str.GetAt(i)<='f'));
		if(!bOK)
			str.Delete(i);
		else i++;	
	}
}
char CCOMTOOLDlg::CombineHexChar(char CharH,char CharL)
{
	char result;
	CString temp;
	if(CharH>='0'&&CharH<='9')			result=(CharH-'0');
	else if(CharH>='a'&&CharH<='f')		result=(CharH-'a'+10);
	else if(CharH>='A'&&CharH<='F')		result=(CharH-'A'+10);
	else								result=0;
	result<<=4;	
	if(CharL>='0'&&CharL<='9')			result+=(CharL-'0');
	else if(CharL>='a'&&CharL<='f')		result+=(CharL-'a'+10);
	else if(CharL>='A'&&CharL<='F')		result+=(CharL-'A'+10);
	else								result+=0;
	return result;
}


CString CCOMTOOLDlg::DevideHexChar(char HexChar)
{
	CString result=_T("");
	int temp=(HexChar&0xF0)>>4;
	if(temp<10)
		result+=(temp+'0');
	else 
		result+=(temp+'A'-10);
	temp=HexChar&0x0F;
	if(temp<10)
		result+=(temp+'0');
	else 
		result+=(temp+'A'-10);
	return result;
}
//文件

void CCOMTOOLDlg::OnButton1() 
{

			

 	 /*	CString m_XmlFile1;
				GetDlgItemText(IDC_PATH,m_XmlFile1);
				  CStdioFile stdFile;
				  stdFile.Open(m_XmlFile1, CFile::modeRead | CFile::typeBinary);
				  DWORD fileLen = stdFile.GetLength();
				  char *pBuf = new char[257];

				  for (int i =0;i<1024;i++)
				  {
					int sl = stdFile.Read(pBuf, 256);
					pBuf[256] = 0;
					stdFile.Seek(256,CFile::current);
		  				m_SerialPort.WriteToPort(pBuf,256);
						Sleep(5);
				  }
				  delete pBuf;
				  stdFile.Close();
	*/
	CString filter,m_XmlFile1;  
	filter="文本文档(*.LOG)|*.LOG|";  
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,filter);  
	if(dlg.DoModal()==IDOK)  
	{ 
		m_XmlFile1=dlg.GetPathName();  
		//AfxMessageBox();
		SetDlgItemText(IDC_PATH,m_XmlFile1);
		 
 
		m_ini.SetKeyValue("txt","path",m_XmlFile1);

	
	} 	
 
 
 
}



void CCOMTOOLDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if(m_tab.GetCurSel() == 0)
	{
 
GetDlgItem(IDC_TAB1_TXT)->ShowWindow(1);

		for(int i=10001;i<10025;i++)
			GetDlgItem(i)->ShowWindow(0);

		for(i=20001;i<20025;i++)
			GetDlgItem(i)->ShowWindow(0);

	}else if(m_tab.GetCurSel() == 1)
	{
 
		for(int i=10001;i<10017;i++)
			GetDlgItem(i)->ShowWindow(1);

		for(i=20001;i<20017;i++)
			GetDlgItem(i)->ShowWindow(1);


GetDlgItem(IDC_TAB1_TXT)->ShowWindow(0);

		for(i=10017;i<10025;i++)
			GetDlgItem(i)->ShowWindow(0);

		for(i=20017;i<20025;i++)
			GetDlgItem(i)->ShowWindow(0);

	}else if(m_tab.GetCurSel() == 2)
	{

		for(int i=10017;i<10025;i++)
			GetDlgItem(i)->ShowWindow(1);

		for(i=20017;i<20025;i++)
			GetDlgItem(i)->ShowWindow(1);
 
		GetDlgItem(IDC_TAB1_TXT)->ShowWindow(0);

		for( i=10001;i<10017;i++)
			GetDlgItem(i)->ShowWindow(0);

		for(i=20001;i<20017;i++)
			GetDlgItem(i)->ShowWindow(0);

	}
	*pResult = 0;
}

void CCOMTOOLDlg::OnSetfocusV14() 
{
	GetDlgItem(10001)->SetFocus();
	FORNUM dlg;
	if(IDOK == dlg.DoModal())
	{
		SetDlgItemText(IDC_V14,dlg.m_num);
		m_ini.SetKeyValue("cv","10014",dlg.m_num);
	
	}
	
}

void CCOMTOOLDlg::OnSetfocusV10() 
{
	 

	
	
	 
	
	
}

void CCOMTOOLDlg::OnKillfocusV10() 
{
	// TODO: Add your control notification handler code here
	
}

void CCOMTOOLDlg::OnSetfocusV11() 
{
	 
}
