// MAP.h : main header file for the MAP application
//

#if !defined(AFX_MAP_H__2597C220_039F_48CA_89AF_9DB39A3515C6__INCLUDED_)
#define AFX_MAP_H__2597C220_039F_48CA_89AF_9DB39A3515C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMAPApp:
// See MAP.cpp for the implementation of this class
//

class CMAPApp : public CWinApp
{
public:
	CMAPApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMAPApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMAPApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAP_H__2597C220_039F_48CA_89AF_9DB39A3515C6__INCLUDED_)
