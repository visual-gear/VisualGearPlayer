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

	CenterWindow();

	InitMessageMap();

	DWORD dwThread = 0;
	CreateThread(NULL, NULL, CStartUp::LoadingProgress, this, NULL, &dwThread);

	return 0;
}

DWORD WINAPI CStartUp::LoadingProgress(LPVOID lParam)
{
	CStartUp* pWin = (CStartUp*)lParam;

	int i = 0;

	while (true)
	{
		i++;

		pWin->m_progress->SetValue(i);

		Sleep(10);

		if (i == 100)
		{
			break;
		}
	}

	pWin->EndDialog(0);
	
	return 0;
}



