// MyImageWorkView.h : interface of the CMyImageWorkView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYIMAGEWORKVIEW_H__69990981_733B_4E21_B6CA_5198A5F8EF9F__INCLUDED_)
#define AFX_MYIMAGEWORKVIEW_H__69990981_733B_4E21_B6CA_5198A5F8EF9F__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DIB.h"
class CMyImageWorkView : public CView
{
protected: // create from serialization only
	CMyImageWorkView();
	DECLARE_DYNCREATE(CMyImageWorkView)
 

// Attributes
public:
	CMyImageWorkDoc* GetDocument();
    int ImageStyle;//显示的模式：0－－原大小，非0－－全屏
 
	CDib m_Dib;
    bool have_open_a_file;
	bool embed, pick;
	bool show_contrast;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyImageWorkView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	 
	virtual ~CMyImageWorkView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyImageWorkView)
	afx_msg void OnNormal();
	afx_msg void OnStretch();
	afx_msg void OnFileOpen();
	afx_msg void OnEmbed();
	afx_msg void OnPick();
	afx_msg void OnUpdatePick(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEmbed(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyImageWorkView.cpp
inline CMyImageWorkDoc* CMyImageWorkView::GetDocument()
   { return (CMyImageWorkDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYIMAGEWORKVIEW_H__69990981_733B_4E21_B6CA_5198A5F8EF9F__INCLUDED_)
