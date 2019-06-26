// StdioFileEx.h: interface for the CStdioFileEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STDIOFILEEX_H__46D7F0A3_CD1A_42F8_B869_A41EFF2D784A__INCLUDED_)
#define AFX_STDIOFILEEX_H__46D7F0A3_CD1A_42F8_B869_A41EFF2D784A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//class CStdioFileEx  
//{
//public:
//	CStdioFileEx();
//	virtual ~CStdioFileEx();
//
//};
// --------------------------------------------------------------------------------------------
//������;�����ж�ȡ����(����ANSI��UNICODE��UNICODE  big endian��UTF-8)��ʽ���ı��ļ�    
//�������ߣ�����ʦ��ѧԺ�������ѧ�뼼��ѧԺ  ������                                 
//�����㷨��CStdioFileEx�̳���CStdioFile�� ����CStdioFile�� BOOL ReadString(CString& rString)����, 
//          ���ݲ�ͬ�ļ�����������Ѱ���ļ��س����з��ж϶�ȡ�н������ļ��������ж��ļ�����                                   
//          ��ⲻͬ�ļ�����ͷ������ȡ�ļ����ͺ���ò�ͬ�Ķ�ȡ����
//���Խ��:��Windows7 VC6.0�����²����������ָ�ʽ��txt�ļ�ͨ��
//��δ���:δ����CStdioFile�� virtual LPTSTR ReadString( LPTSTR lpsz, UINT nMax )����
//         δ���WriteString����,δ��VC UNICODE �����µĲ���                                                           
//����ʱ�䣺2012-04-19                                             
//�����Ȩ:���빫����ѧϰ����ʹ��  ��ӭָ������  �����㷨                                                
// --------------------------------------------------------------------------------------------
#include "stdafx.h"
//�ı��ļ�����ö��ֵ
typedef enum TextCodeType
{
    UTF8=0,
    UNICODE =1,
    UNICODEBIGENDIAN=2,
    ANSI=3,
    FILEERROR=4
}TextCode;
class CStdioFileEx  :public CStdioFile
{
public:
    CStdioFileEx();
    CStdioFileEx(FILE* pOpenStream);
    CStdioFileEx(LPCTSTR lpszFileName, UINT nOpenFlags);
    virtual ~CStdioFileEx();
    virtual BOOL Open( LPCTSTR lpszFileName, UINT nOpenFlags, CFileException* pError = NULL);
public:
    //�ļ�����ֵת�����ַ���
    CString  FileTypeToString();
    //��ȡ�ļ�����
    TextCode GetFileType();
    //���ж�ȡ�ļ�
    BOOL     ReadString(CString& rString);
    //��̬����  ��ȡ�ļ�����
    static   TextCode GetFileType( LPCTSTR lpszFileName);
protected:
    TextCode m_FileType;//�����ļ�����
    const static int  PREDEFINEDSIZE;//Ԥ����һ���ļ�����ռ�
protected:
    //��UTF-8�ļ����ж�ȡ
    BOOL     ReadStringFromUTF8File(CString& rString);
    //��ANSI�ļ����ж�ȡ
    BOOL     ReadStringFromAnsiFile(CString& rString);
    //��UNCIDOE��UNICODE big endian�ļ���ȡ
    BOOL     ReadStringFromUnicodeFile(CString& rString);
    //UTF-8�ַ���ת����UNICODE�ַ���
    CString  UTF8ToUnicode(byte  *szUTF8);
    //�����ļ��򿪱�־
    UINT     ProcessFlags(LPCTSTR lpszFileName, UINT& nOpenFlags,TextCode &tc);
};
#endif // !defined(AFX_STDIOFILEEX_H__46D7F0A3_CD1A_42F8_B869_A41EFF2D784A__INCLUDED_)
