#pragma once

#include "AboutDlg.h"

class CMainPage : public CDialogImpl<CMainPage>
{
public:
	CMainPage();   // standard constructor
	virtual ~CMainPage();

// Dialog Data
	enum { IDD = IDD_MAINDLG };

protected:
	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	END_MSG_MAP()

	DECLARE_UIG_MESSAGE_MAP(CMainPage)

public:
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	
	void BtnClicked(IUIGearsControl* pCtrl);
	void MaxChanged(IUIGearsControl* pCtrl, UIGears::UICheckState state);
	void PinChanged(IUIGearsControl* pCtrl, UIGears::UICheckState state);
	void EpxandChange(IUIGearsControl* pCtrl, UIGears::UICheckState state);
	void VolumeChanged(IUIGearsControl* pCtrl, int value);
	void ProgressChanged(IUIGearsControl* pCtrl, int value);
	void UpdateItem(IUIGearsControl* pCtrl, IUIGearsControl* pItem, int index);
	
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CAboutDlg dlg;
		dlg.DoModal();
		return 0;
	}

	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add validation code 
		CloseDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CloseDialog(wID);
		return 0;
	}

	void CloseDialog(int nVal)
	{
		DestroyWindow();
		::PostQuitMessage(nVal);
	}
		
private:
	UIGears::IUIGearsWindow*	m_pWindow;
	UIGears::IUIGButton*			m_btnClose;
	UIGears::IUIGCheckBox*			m_cbkMax;
	UIGears::IUIGButton*			m_btnMin;
	UIGears::IUIGButton*			m_btnSetting;
	UIGears::IUIGCheckBox*			m_cbkPin;
	UIGears::IUIGTemplateList*			m_playList;
	UIGears::IUIGButton*			m_btnDelete;
	UIGears::IUIGButton*			m_btnSort;
	UIGears::IUIGButton*			m_btnOpen;
	UIGears::IUIGButton*			m_btnNext;
	UIGears::IUIGButton*			m_btnPrevious;
	UIGears::IUIGButton*			m_btnStop;
	UIGears::IUIGSlider*			m_volumeSlider;
	UIGears::IUIGButton*			m_btnPlay;
	UIGears::IUIGCheckBox*			m_btnExpand;
	UIGears::IUIGButton*			m_volumnBtn;
	UIGears::IUIGSlider*			m_progressSlider;
	UIGears::IUIGLabel*			m_time;

};
