// CMainPage.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "MainPage.h"

// CMainPage dialog
CMainPage::CMainPage()
{
		m_pWindow = NULL;

}

CMainPage::~CMainPage()
{
}

BEGIN_UIG_MESSAGE_MAP(CMainPage)

END_UIG_MESSAGE_MAP()

// CMainPage message handlers
LRESULT CMainPage::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_pWindow = UIGears::CreateUIGearsWinByName(_T("MainPage.json"), (void*)m_hWnd);

	CenterWindow();

	InitMessageMap();
	return 0;
}




