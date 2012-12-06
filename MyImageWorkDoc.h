// MyImageWorkDoc.h : interface of the CMyImageWorkDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYIMAGEWORKDOC_H__A14C0780_80E9_4F8C_8F02_818C21B87C50__INCLUDED_)
#define AFX_MYIMAGEWORKDOC_H__A14C0780_80E9_4F8C_8F02_818C21B87C50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyImageWorkDoc : public CDocument
{
protected: // create from serialization only
	CMyImageWorkDoc();
	DECLARE_DYNCREATE(CMyImageWorkDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyImageWorkDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyImageWorkDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyImageWorkDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYIMAGEWORKDOC_H__A14C0780_80E9_4F8C_8F02_818C21B87C50__INCLUDED_)
