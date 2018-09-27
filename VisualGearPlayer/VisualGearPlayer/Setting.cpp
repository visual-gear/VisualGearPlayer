// CSetting.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "Setting.h"

// CSetting dialog
CSetting::CSetting()
{
	m_pWindow = NULL;
}

CSetting::~CSetting()
{
}

BEGIN_UIG_MESSAGE_MAP(CSetting)

END_UIG_MESSAGE_MAP()

// CSetting message handlers
LRESULT CSetting::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_pWindow = UIGears::CreateUIGearsWinByName(_T("Setting.json"), (void*)m_hWnd);

	CenterWindow();

	InitMessageMap();
	return 0;
}



