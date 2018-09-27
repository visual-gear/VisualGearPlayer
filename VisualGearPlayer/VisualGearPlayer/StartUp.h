#pragma once

class CStartUp : public CDialogImpl<CStartUp>
{
public:
	CStartUp();   // standard constructor
	virtual ~CStartUp();

// Dialog Data
	enum { IDD = IDD_DIALOG_STARTUP };

protected:
	BEGIN_MSG_MAP(CStartUp)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	END_MSG_MAP()
	DECLARE_UIG_MESSAGE_MAP(CStartUp)

public:
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	static DWORD WINAPI LoadingProgress(LPVOID lParam);
		
private:
	UIGears::IUIGearsWindow*	m_pWindow;
	UIGears::IUIGLabel*			m_label;
	UIGears::IUIGProgressBar*			m_progress;

};
