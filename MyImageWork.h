// MyImageWork.h : main header file for the MYIMAGEWORK application
//

#if !defined(AFX_MYIMAGEWORK_H__21E63643_CE87_4AFF_B521_B66FF20819B1__INCLUDED_)
#define AFX_MYIMAGEWORK_H__21E63643_CE87_4AFF_B521_B66FF20819B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyImageWorkApp:
// See MyImageWork.cpp for the implementation of this class
//

class CMyImageWorkApp : public CWinApp
{
public:
	CMyImageWorkApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyImageWorkApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMyImageWorkApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYIMAGEWORK_H__21E63643_CE87_4AFF_B521_B66FF20819B1__INCLUDED_)
