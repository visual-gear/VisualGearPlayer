// CMainPage.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "MainPage.h"
#include "Setting.h"

// CMainPage dialog
CMainPage::CMainPage()
{
		m_pWindow = NULL;

		m_btnClose = NULL;
		m_cbkMax = NULL;
		m_btnMin = NULL;
		m_btnSetting = NULL;
		m_cbkPin = NULL;
		m_playList = NULL;
		m_btnDelete = NULL;
		m_btnSort = NULL;
		m_btnOpen = NULL;
		m_btnNext = NULL;
		m_btnPrevious = NULL;
		m_btnStop = NULL;
		m_volumeSlider = NULL;
		m_btnPlay = NULL;
		m_btnExpand = NULL;
		m_volumnBtn = NULL;
		m_progressSlider = NULL;
		m_time = NULL;
}

CMainPage::~CMainPage()
{
}

BEGIN_UIG_MESSAGE_MAP(CMainPage)

	ON_UIG_BN_CLICKED(m_btnClose, BtnClicked)
	ON_UIG_BN_CLICKED(m_btnMin, BtnClicked)
	ON_UIG_BN_CLICKED(m_btnSetting, BtnClicked)
	ON_UIG_BN_CLICKED(m_btnOpen, BtnClicked)
	ON_UIG_BN_CLICKED(m_btnNext, BtnClicked)
	ON_UIG_BN_CLICKED(m_btnPrevious, BtnClicked)
	ON_UIG_BN_CLICKED(m_btnStop, BtnClicked)
	ON_UIG_BN_CLICKED(m_btnPlay, BtnClicked)
	ON_UIG_BN_CLICKED(m_volumnBtn, BtnClicked)
	ON_UIG_CB_CHANGE(m_cbkMax, MaxChanged)
	ON_UIG_CB_CHANGE(m_cbkPin, PinChanged)
	ON_UIG_CB_CHANGE(m_btnExpand, EpxandChange)
	ON_UIG_SLIDER_CHANGE(m_volumeSlider, VolumeChanged)
	ON_UIG_SLIDER_CHANGE(m_progressSlider, ProgressChanged)
	ON_UIG_LIST_UDPATEDATA(m_playList, UpdateItem)
END_UIG_MESSAGE_MAP()

// CMainPage message handlers
LRESULT CMainPage::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_pWindow = UIGears::CreateUIGearsWinByName(_T("MainPage.json"), (void*)m_hWnd);
	m_btnClose = (UIGears::IUIGButton*)m_pWindow->GetControl(_T("btnClose"));
	m_cbkMax = (UIGears::IUIGCheckBox*)m_pWindow->GetControl(_T("cbkMax"));
	m_btnMin = (UIGears::IUIGButton*)m_pWindow->GetControl(_T("btnMin"));
	m_btnSetting = (UIGears::IUIGButton*)m_pWindow->GetControl(_T("btnSetting"));
	m_cbkPin = (UIGears::IUIGCheckBox*)m_pWindow->GetControl(_T("cbkPin"));
	m_playList = (UIGears::IUIGTemplateList*)m_pWindow->GetControl(_T("playList"));
	m_btnDelete = (UIGears::IUIGButton*)m_pWindow->GetControl(_T("btnDelete"));
	m_btnSort = (UIGears::IUIGButton*)m_pWindow->GetControl(_T("btnSort"));
	m_btnOpen = (UIGears::IUIGButton*)m_pWindow->GetControl(_T("btnOpen"));
	m_btnNext = (UIGears::IUIGButton*)m_pWindow->GetControl(_T("btnNext"));
	m_btnPrevious = (UIGears::IUIGButton*)m_pWindow->GetControl(_T("btnPrevious"));
	m_btnStop = (UIGears::IUIGButton*)m_pWindow->GetControl(_T("btnStop"));
	m_volumeSlider = (UIGears::IUIGSlider*)m_pWindow->GetControl(_T("volumeSlider"));
	m_btnPlay = (UIGears::IUIGButton*)m_pWindow->GetControl(_T("btnPlay"));
	m_btnExpand = (UIGears::IUIGCheckBox*)m_pWindow->GetControl(_T("btnExpand"));
	m_volumnBtn = (UIGears::IUIGButton*)m_pWindow->GetControl(_T("volumnBtn"));
	m_progressSlider = (UIGears::IUIGSlider*)m_pWindow->GetControl(_T("progressSlider"));
	m_time = (UIGears::IUIGLabel*)m_pWindow->GetControl(_T("time"));

	CenterWindow();

	for (size_t i = 0; i < 100; i++)
	{
		TCHAR buffer[64] = { 0 };
		wsprintf(buffer, _T("item%d"), i);
		m_playList->AddItem(buffer);
	}

	InitMessageMap();
	return 0;
}


void CMainPage::BtnClicked(IUIGearsControl* pCtrl)
{
	if(pCtrl == m_btnClose)
	{
		CloseDialog(0);
	}
	else if(pCtrl == m_btnMin)
	{
		ShowWindow(SW_MINIMIZE);
	}
	else if(pCtrl == m_btnSetting)
	{
		CSetting dlgSetting;
		dlgSetting.DoModal();
	}
	else if(pCtrl == m_btnOpen)
	{
	}
	else if(pCtrl == m_btnNext)
	{
	}
	else if(pCtrl == m_btnPrevious)
	{
	}
	else if(pCtrl == m_btnStop)
	{
	}
	else if(pCtrl == m_btnPlay)
	{
	}
	else if(pCtrl == m_volumnBtn)
	{
	}
}

void CMainPage::MaxChanged(IUIGearsControl* pCtrl, UIGears::UICheckState state)
{
	if(pCtrl == m_cbkMax)
	{
		if (state == UIG_CHECKED)
		{
			ShowWindow(SW_MAXIMIZE);
		}
		else
		{
			ShowWindow(SW_RESTORE);
		}
	}
}

void CMainPage::PinChanged(IUIGearsControl* pCtrl, UIGears::UICheckState state)
{
	if(pCtrl == m_cbkPin)
	{
		RECT rc = { 0 };
		if (state == UIG_CHECKED)
		{
			SetWindowPos(HWND_TOPMOST, &rc, SWP_NOMOVE | SWP_NOSIZE);
		}
		else
		{
			SetWindowPos(HWND_NOTOPMOST, &rc, SWP_NOMOVE | SWP_NOSIZE);
		}
	}
}

void CMainPage::EpxandChange(IUIGearsControl* pCtrl, UIGears::UICheckState state)
{
	if(pCtrl == m_btnExpand)
	{
	}
}

void CMainPage::VolumeChanged(IUIGearsControl* pCtrl, int value)
{
	if(pCtrl == m_volumeSlider)
	{
	}
}

void CMainPage::ProgressChanged(IUIGearsControl* pCtrl, int value)
{
	if(pCtrl == m_progressSlider)
	{
	}
}

void CMainPage::UpdateItem(IUIGearsControl* pCtrl, IUIGearsControl* pItem, int index)
{
	if(pCtrl == m_playList)
	{
		IUIGLabel* pTitle = (IUIGLabel*)pItem->GetControlByName(_T("title"));
		IUIGLabel* pTime = (IUIGLabel*)pItem->GetControlByName(_T("time"));

		TCHAR buffer[64] = { 0 };
		wsprintf(buffer, _T("Video - %d"), index);
		if (pTitle)
		{
			pTitle->SetText(buffer);
		}

		if (pTime)
		{
			int timeCount = rand();
			int hour = timeCount / (60 * 60);
			int minute = timeCount % (60 * 60) / 60;
			int second = timeCount % 60;
			wsprintf(buffer, _T("%02d:%02d:%02d"), hour, minute, second);
			pTime->SetText(buffer);
		}

	}
}

