#pragma once

class CSetting : public CDialogImpl<CSetting>
{
public:
	CSetting();   // standard constructor
	virtual ~CSetting();

// Dialog Data
	enum { IDD = IDD_DIALOG_SETTING };

protected:
	BEGIN_MSG_MAP(CSetting)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	END_MSG_MAP()
	DECLARE_UIG_MESSAGE_MAP(CSetting)

public:
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		
private:
	UIGears::IUIGearsWindow*	m_pWindow;

};
