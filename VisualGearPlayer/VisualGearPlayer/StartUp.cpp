// CStartUp.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "StartUp.h"

// CStartUp dialog
CStartUp::CStartUp()
{
		m_pWindow = NULL;

		m_label = NULL;
		m_progress = NULL;
}

CStartUp::~CStartUp()
{
}

BEGIN_UIG_MESSAGE_MAP(CStartUp)

END_UIG_MESSAGE_MAP()

// CStartUp message handlers
LRESULT CStartUp::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_pWindow = UIGears::CreateUIGearsWinByName(_T("StartUp.json"), (void*)m_hWnd);
	m_label = (UIGears::IUIGLabel*)m_pWindow->GetControl(_T("label"));
	m_progress = (UIGears::IUIGProgressBar*)m_pWindow->GetControl(_T("progress"));



	InitMessageMap();
	return 0;
}



