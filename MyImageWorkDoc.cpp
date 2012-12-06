// MyImageWorkDoc.cpp : implementation of the CMyImageWorkDoc class
// Download by http://www.codefans.net

#include "stdafx.h"
#include "MyImageWork.h"

#include "MyImageWorkDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyImageWorkDoc

IMPLEMENT_DYNCREATE(CMyImageWorkDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyImageWorkDoc, CDocument)
	//{{AFX_MSG_MAP(CMyImageWorkDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyImageWorkDoc construction/destruction

CMyImageWorkDoc::CMyImageWorkDoc()
{
	// TODO: add one-time construction code here

}

CMyImageWorkDoc::~CMyImageWorkDoc()
{
}

BOOL CMyImageWorkDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyImageWorkDoc serialization

void CMyImageWorkDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMyImageWorkDoc diagnostics

#ifdef _DEBUG
void CMyImageWorkDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyImageWorkDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyImageWorkDoc commands
