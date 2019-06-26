// StdioFileEx.cpp: implementation of the CStdioFileEx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "COMTOOL.h"
#include "StdioFileEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*static*/ const  int  CStdioFileEx::PREDEFINEDSIZE=1024;
CStdioFileEx::CStdioFileEx():CStdioFile()
{
    m_FileType=ANSI;//ָ��Ĭ������
}
CStdioFileEx::CStdioFileEx(FILE* pOpenStream):CStdioFile(pOpenStream)
{
  CString filepath=pOpenStream->_tmpfname;//?  �в����File*�ṹ
  m_FileType=GetFileType(filepath);
}
CStdioFileEx::CStdioFileEx(LPCTSTR lpszFileName, UINT nOpenFlags):CStdioFile(lpszFileName,ProcessFlags(lpszFileName, nOpenFlags,m_FileType) )
{
}
CStdioFileEx::~CStdioFileEx()
{
 
}
// --------------------------------------------------------------------------------------------
//CStdioFileEx::GetFileType  ��̬����  ����ı��ļ�����
// --------------------------------------------------------------------------------------------
/*static */ TextCode CStdioFileEx::GetFileType(LPCTSTR lpszFileName)
{
    CFile file;
    byte  buf[3];//unsigned char
    TextCode tc;
    try
    {
        if(file.Open(lpszFileName,CFile::modeRead|CFile::shareDenyNone|CFile::typeBinary))
        {   
            file.Read(buf,3);
            if(buf[0]==0xEF && buf[1]==0xBB && buf[2]==0xBF)
                tc=UTF8;
            else
            if(buf[0]==0xFF && buf[1]==0xFE )
                tc=UNICODE ;
            else
            if(buf[0]==0xFE && buf[1]==0xFF )
                tc=UNICODEBIGENDIAN;
            else
                tc=ANSI;
        }
        else
            tc=FILEERROR;
    }
    catch (CFileException ex)
    {   
        CString errormsg;
        errormsg.Format(_T("�����ļ�%sʱ�����쳣!"),ex.m_strFileName);
        AfxMessageBox(errormsg);
    }
    return tc;
}
// --------------------------------------------------------------------------------------------
//CStdioFileEx::Readstring ���ж�ȡ�ı��ļ�
//���ݲ�ͬ�ļ����� ���ò�ͬ�Ķ�ȡ����
// --------------------------------------------------------------------------------------------
BOOL CStdioFileEx::ReadString(CString& rString)
{    
    BOOL flag=FALSE;
     switch(m_FileType)
     {
     case ANSI:
          flag=ReadStringFromAnsiFile(rString);
          break;
     case UNICODE:
     case UNICODEBIGENDIAN:
          flag=ReadStringFromUnicodeFile(rString);
          break;
     case UTF8:
         flag=ReadStringFromUTF8File(rString);
         break;
     case FILEERROR:
         flag=FALSE;
         break;
     default:
         break;
     }
     return flag;
}
// --------------------------------------------------------------------------------------------
//CStdioFileEx::ReadstringFromAnsiFile  ��ANSI�ļ���ȡ�ַ���
// --------------------------------------------------------------------------------------------
BOOL CStdioFileEx::ReadStringFromAnsiFile(CString& rString)
{   
    BOOL flag;
    try
    {   
        flag=CStdioFile::ReadString(rString);
        rString+="\r\n";
    }
    catch(CFileException ex)
    {
        CString errormsg;
        errormsg.Format(_T("�����ļ�%sʱ�����쳣!"),ex.m_strFileName);
        AfxMessageBox(errormsg);
    }
    return flag;
}
// --------------------------------------------------------------------------------------------
//CStdioFileEx::ReadstringFromUTF8File ��UTF8�ļ��а��ж�ȡ 
//����UTF-8������ֽڱ����Ҹ����ַ����Ȳ�ͬ,�жϻس�������Ҫ�ж����������ֽ�  
// --------------------------------------------------------------------------------------------
BOOL  CStdioFileEx::ReadStringFromUTF8File(CString& rString)
{
    long    index;
    byte    cr=0x0d;//�س����з�
    byte    lf=0x0a;
    byte    temp[2];
    byte    tempbyte;
    byte    *pbuf=new byte[PREDEFINEDSIZE+1];
    memset(pbuf,0,(PREDEFINEDSIZE+1)*sizeof(byte));
    UINT    readlen;
    try
    {   
        //�����ļ�ͷ �ƶ��ļ�ָ��
        if (m_pStream && ( GetPosition() == 0))
        {
            CStdioFile::Seek(3*sizeof(byte),CFile::begin);
        }
        index=0;
        do
        {
            memset(temp,0,2*sizeof(byte));
            readlen=CFile::Read(temp,2);//CStdioFile::ReadЧ����ͬ ��ʡȥ�س���0x0d
            if(!readlen)
                return FALSE;
            //Ԫ�ش������ֽ�������
            pbuf[index++]=temp[0];
            pbuf[index++]=temp[1];
            tempbyte=temp[1];
            //�жϻس�����
            if( ( tempbyte==cr && temp[0]==lf) ||(temp[0]==cr && temp[1]==lf))
                break;
        } while (readlen==2 && index<PREDEFINEDSIZE );
        pbuf[index]=0;
        rString=UTF8ToUnicode(pbuf);//UTF8����ת����UNICODE
    }
    catch (CFileException ex)
    {
        CString errormsg;
        errormsg.Format(_T("�����ļ�%sʱ�����쳣!"),ex.m_strFileName);
        AfxMessageBox(errormsg);
    }
    delete[] pbuf;
    return TRUE;
}
// --------------------------------------------------------------------------------------------
//��UNICODE��UNICODE big endian�ļ����ж�ȡ
//����ȡ�ֽ�С������ֵ(�ļ�����)���߳���Ԥ����ռ�ʱ�������˳�ѭ��
//wChLine���ÿ���ַ�,wchtemp�����ʱ��ȡ�ַ�
//������ΪUNICODE big endian ʱ�����ߵ��ֽ� ,����ת����UNICODE�ַ���
// --------------------------------------------------------------------------------------------
BOOL  CStdioFileEx::ReadStringFromUnicodeFile(CString& rString)
{
    long    index;
    UINT    readlen;
    wchar_t wchcr=MAKEWORD(0x0d,0x00);;//�س���  MakeWord(�͡����ֽ�˳��) 
    wchar_t wchlf=MAKEWORD(0x0a,0x00);
    wchar_t *wChLine=new wchar_t[PREDEFINEDSIZE+1];
    memset(wChLine,0,(PREDEFINEDSIZE+1)*sizeof(wchar_t));
    wchar_t wchtemp[2];
    BOOL   flag=TRUE;
    try
    {   
        //�����ļ�ͷ �ƶ��ļ�ָ��
        if (m_pStream && ( GetPosition() ==0))
        {
            Seek(2*sizeof(byte),CFile::begin);
        }
        index=0;
        do
        {   
            memset(wchtemp,0,2*sizeof(wchar_t));
            readlen=CFile::Read(wchtemp,sizeof(wchar_t)*2);//CStdioFile::ReadЧ����ͬ
            if(!readlen)
                 break;
            //UNICODE big endian�����ߵ��ֽ�
            if(UNICODEBIGENDIAN==m_FileType)
            {   
                unsigned char high, low;
                high = (wchtemp[0] & 0xFF00) >>8;
                low  = wchtemp[0] & 0x00FF;
                wchtemp[0] = ( low <<8) | high;
                high = (wchtemp[1] & 0xFF00) >>8;
                low  = wchtemp[1] & 0x00FF;
                wchtemp[1] = ( low <<8) | high;
            }
            wChLine[index++]=wchtemp[0];
            wChLine[index++]=wchtemp[1];
            //�жϻس�����
            if(wchtemp[0]==wchcr && wchtemp[1]==wchlf)
                break;
        }
        while( (readlen==sizeof(wchar_t)*2) && index<PREDEFINEDSIZE );
        wChLine[index]=0;
        CString strtext(wChLine,index);
        rString=strtext;
        if(rString.IsEmpty())
           flag=FALSE;
    }
    catch (CFileException ex)
    {
        CString errormsg;
        errormsg.Format(_T("�����ļ�%sʱ�����쳣!"),ex.m_strFileName);
        AfxMessageBox(errormsg);
    }
    delete[] wChLine;
    return flag;
}
// --------------------------------------------------------------------------------------------
//CStdioFileEx::UTF8ToUnicode  UTF-8�ַ���ת����UNICODE�ַ���
// --------------------------------------------------------------------------------------------
CString CStdioFileEx::UTF8ToUnicode(byte  *szUTF8)
{   
    CString strret;
    strret=_T("");
    if(!szUTF8)
        return strret;
    //��ȡת�������贮�ռ�ĳ��� 
    int   wcsLen =  MultiByteToWideChar(CP_UTF8,0,(LPSTR)szUTF8,strlen((char*)szUTF8),NULL,0);
    LPWSTR   lpw=new   WCHAR[wcsLen+1]; 
    if(!lpw)
        return strret;
    memset(lpw,0,(wcsLen+1)*sizeof(wchar_t)); 
    //ʵʩת��
    MultiByteToWideChar(CP_UTF8,0, (LPSTR)szUTF8, 
        strlen((char *)szUTF8),  (LPWSTR)lpw,  wcsLen); 
    CString str(lpw);
    delete[]   lpw;
    return str;
}
// --------------------------------------------------------------------------------------------
//CStdioFileEx::GetFileType��ȡ�ļ�����
// --------------------------------------------------------------------------------------------
TextCode CStdioFileEx::GetFileType()
{   
    return m_FileType;
}
// --------------------------------------------------------------------------------------------
//CStdioFileEx::FileTypeToString �ļ�����ö��ֵת��Ϊ�ַ���ֵ
// --------------------------------------------------------------------------------------------
CString CStdioFileEx::FileTypeToString()
{   
    CString strtype;
    switch(m_FileType)
    {
    case ANSI:
        strtype.Format("%s",_T("ANSI"));
        break;
    case UTF8:
        strtype.Format("%s",_T("UTF8"));
        break;
    case UNICODE:
        strtype.Format("%s",_T("UNICODE"));
        break;
    case UNICODEBIGENDIAN:
        strtype.Format("%s",_T("UNICODE big endian"));
        break;
    case FILEERROR:
        strtype.Format("%s",_T("FILEERROR"));
        break;
    default:
        break;
    }
    return strtype;
}
// --------------------------------------------------------------------------------------------
//CStdioFileEx::Open ���ظ�����ļ��򿪲��� �ı䲻ͬ�����ļ��Ĵ򿪷�ʽ
// --------------------------------------------------------------------------------------------
BOOL CStdioFileEx::Open( LPCTSTR lpszFileName, UINT nOpenFlags, CFileException* pError)
{   
    ProcessFlags(lpszFileName,nOpenFlags,m_FileType);//�����ļ��򿪷�ʽ
    return CStdioFile::Open(lpszFileName, nOpenFlags,pError);
}
// --------------------------------------------------------------------------------------------
//CStdioFileEx::ProcessFlags ����ͬ�ļ��Ĵ򿪷�ʽ
//ANSI�ļ������ı���ȡ��UNICODE��UNICDOE big endian��UTF-8���ö����Ʒ�ʽ��ȡ
// --------------------------------------------------------------------------------------------
UINT CStdioFileEx::ProcessFlags(LPCTSTR lpszFileName, UINT& nOpenFlags,TextCode &tc)
{
    tc=CStdioFileEx::GetFileType(lpszFileName);
    if ((nOpenFlags & CFile::modeReadWrite)|| (nOpenFlags & CFile::modeRead) )
    {
        switch(tc)
        {
        case ANSI:
            nOpenFlags|= CFile::typeText;
            nOpenFlags&=~CFile::typeBinary;
            break;
        case UTF8:
            nOpenFlags |= CFile::typeBinary;
            nOpenFlags&= ~CFile::typeText;
            break;
        case UNICODE:
            nOpenFlags |= CFile::typeBinary;
            nOpenFlags&= ~CFile::typeText;
            break;
        case UNICODEBIGENDIAN:
            nOpenFlags |= CFile::typeBinary;
            nOpenFlags&= ~CFile::typeText;
            break;
        case FILEERROR:
            break;
        default:
            break;
        }
    }
    nOpenFlags|=CFile::shareDenyNone;
    return nOpenFlags;
}