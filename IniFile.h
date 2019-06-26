// File: IniFile.h
// Date: October 2004
// Author: lixiaosan
// Email: airforcetwo@163.com
// Copyright (c) 2004. All Rights Reserved.
//////////////////////////////////////////////////////////////////////////

// IniFile.h: interface for the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILE_H__FE97DC93_3D4E_4298_877A_41928B1A8C7D__INCLUDED_)
#define AFX_INIFILE_H__FE97DC93_3D4E_4298_877A_41928B1A8C7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIniFile  
{
public:
         CIniFile();
         virtual ~CIniFile();

         //设置ini文件路径
		// 成功返回TRUE;否则返回FALSE
         BOOL   SetPath(CString strPath);         

		//检查section是否存在
		//存在返回TRUE;否则返回FALSE
         BOOL SectionExist(CString strSection);

		//从指定的Section和Key读取KeyValue
        //返回KeyValue
         CString GetKeyValue(CString strSection, CString strKey); 

         //设置Section、Key以及KeyValue，若Section或者Key不存在则创建
         void SetKeyValue(CString strSection, CString strKey, CString strKeyValue);
         
		 //    删除指定Section下的一个Key
         void DeleteKey(CString strSection, CString strKey);

         //    删除指定的Section以及其下的所有Key
         void DeleteSection(CString strSection);

		//    获得所有的Section
		//    返回Section数目
         int GetAllSections(CStringArray& strArrSection);         

		//    根据指定Section得到其下的所有Key和KeyValue
        //    返回Key的数目
         int GetAllKeysAndValues(CString strSection, CStringArray& strArrKey, CStringArray& strArrKeyValue);

         //       删除所有Section
         void DeleteAllSections();
private:
         //       ini文件路径
         CString m_strPath;
};

#endif // !defined(AFX_INIFILE_H__FE97DC93_3D4E_4298_877A_41928B1A8C7D__INCLUDED_)

 

