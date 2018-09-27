#pragma once

#ifndef UIGEARS_CORE
#define UIGEARS_CORE

#include <string>
#include <vector>

#ifdef EXPORT_UIGEARS
#define UIGEARS_API _declspec(dllexport)
#else
#define UIGEARS_API _declspec(dllimport)
#pragma comment(lib, "UIGearsCore.lib")
#endif

#ifdef WIN32
#include <windows.h>
#endif

#ifdef UNICODE
#define tchar wchar_t
#define tstring wstring
#else
#define tchar char
#define tstring string
#endif

#ifdef _WIN64
typedef __int64				PARAM;
#else
typedef int					PARAM;
#endif

// key
#define UIG_KEY_DOWN			0x01
#define UIG_KEY_UP				0x02

// control
#define UIG_CTRL_RESIZE			0x10
#define UIG_CTRL_VISIBLE_CHANGE	0x11

// container
#define UIG_CONTAINER_CLICK 0x20

// button
#define UIG_BTN_CLICK		0x100
#define UIG_BTN_DOWN		0x101
#define UIG_BTN_UP			0x102
#define UIG_BTN_DBCLICK		0x103

// slider
#define UIG_SLD_CHANGE		0x200
#define UIG_SLG_LBUTTONUP	0x201

// list
#define UIG_LIST_SELECTED		0x300
#define UIG_LIST_UPDATEDDATE	0x301
#define UIG_LIST_RMOUSEUP		0x302
#define UIG_LIST_DBCLICK		0x303
#define UIG_LIST_ITEMDOWN		0x304
#define UIG_LIST_MOUSEMOVE		0x305
#define UIG_LIST_DRAGITEM		0x306
#define UIG_LIST_EDIT_KILLFOCUS 0x307

// checkbox
#define UIG_CB_CHANGED		0x400

// radio
#define UIG_RAD_SELECTED	0x500

// tree
#define UIG_TREE_SELECTED		0x600
#define UIG_TREE_RMOUSEUP		0x601
#define UIG_TREE_DBCLICK		0x602

// combobox
#define UIG_COMBOBOX_CHANGED	0x700

// tab
#define UIG_TAB_SELECTITEM		0x800

// menu
#define UIG_MENU_COMMAND		0x900

// canvas
#define	UIG_CANVAS_ADD			0x1000
#define UIG_CANVAS_REMOVE		0x1001
#define UIG_CANVAS_SELECT		0x1002
#define UIG_CANVAS_CLEARSELECT	0x1003	
#define UIG_CANVAS_MOVE			0x1004
#define UIG_CANVAS_MOVEUPDOWN	0x1005
#define UIG_CANVAS_RMOUSEUP		0x1006

// edit
#define UIG_EDIT_SETFOCUS			0x2000
#define UIG_EDIT_KILLFOCUS			0x2001
#define UIG_EDIT_TEXTCHANGE			0x2002
#define UIG_EDIT_DEFOREINPUTTEXT	0x2003
#define UIG_EDIT_KEYDOWN			0x2004
#define UIG_EDIT_KEYUP				0x2005

// scrollbar
#define UIG_SCROLL_POSCHANGE		0x2100

// splitter
#define UIG_SPLITTER_POSCHANGE		0x2201

namespace UIGears
{
	class IUIGearsControl;
}

class IEventRecevier;
struct NotifyInfo
{
	unsigned int						nMsgId;
	UIGears::IUIGearsControl			*pCtrl;
	void*								ctrlPtr;
	PARAM								wParam;
	PARAM								lParam;
};

class IEventRecevier {
public:
	virtual int EventNofiy(NotifyInfo* pNotify) = 0;
};

template <class o, class T>
class CDelegateObj : public IEventRecevier
{
public:
	typedef bool (T::* Fn)(void*);

	CDelegateObj()
	{
		m_pObject = NULL;
		m_pFn = NULL;
	}

	CDelegateObj(o* obj, Fn pFn)
	{
		m_pObject = obj;
		m_pFn = pFn;
	}

	void SetDelegate(o* obj, Fn pFn)
	{
		m_pObject = obj;
		m_pFn = pFn;
	}

	virtual ~CDelegateObj() {}

	virtual int EventNofiy(NotifyInfo* pNotify)
	{
		return (m_pObject->*m_pFn)(pNotify);
	}

private:
	o* m_pObject;
	Fn m_pFn;
};

#define DECLARE_UIG_MESSAGE_MAP(thisClass) bool InitMessageMap(void *pMsg = NULL); CDelegateObj<thisClass, thisClass> m_delegate;
#define BEGIN_UIG_MESSAGE_MAP(theClass) bool theClass::InitMessageMap(void *pMsg) { typedef theClass thisClass; NotifyInfo *pNotify = (NotifyInfo*)pMsg; if(pNotify == NULL) { MAKE_DELEGATE(m_delegate, this, theClass); }
#define END_UIG_MESSAGE_MAP() return true; }
#define INIT_UIG_MESSAGE() InitMessageMap();
#define MAKE_DELEGATE(delegate, obj, classname) delegate.SetDelegate(this, &classname::InitMessageMap)
#define RELEASE_DELEGATE(obj) if(obj != NULL) {	obj->RemoveEventReceiver(NULL); }

#define ON_UIG_RESIZE(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_CTRL_RESIZE) { func(pNotify->pCtrl); return true;} } }
#define ON_UIG_VISIBLECHANGE(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_CTRL_VISIBLE_CHANGE) { func(pNotify->pCtrl); return true;} } }
#define ON_UIG_BN_CLICKED(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_BTN_CLICK) { func(pNotify->pCtrl); return true;} } }
#define ON_UIG_BN_DOWN(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_BTN_DOWN) { func(pNotify->pCtrl); return true;} } }
#define ON_UIG_BN_UP(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_BTN_UP) { func(pNotify->pCtrl); return true;} } }
#define ON_UIG_BN_DBCLICKED(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_BTN_DBCLICK) { func(pNotify->pCtrl); return true;} } }
#define ON_UIG_SLIDER_CHANGE(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_SLD_CHANGE) { func(pNotify->pCtrl, (int)pNotify->wParam); return true;} } }
#define ON_UIG_SLIDER_LBUTTONUP(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_SLG_LBUTTONUP) { func(pNotify->pCtrl, (int)pNotify->wParam); return true;} } }
#define ON_UIG_LIST_SEL_CHANGE(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_LIST_SELECTED) { func(pNotify->pCtrl, (int)pNotify->wParam, (int)pNotify->lParam); return true;} } }
#define ON_UIG_LIST_MOUSE_MOVE(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_LIST_MOUSEMOVE) { func(pNotify->pCtrl, (int)pNotify->wParam); return true;} } }
#define ON_UIG_LIST_ITEM_DOWN(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_LIST_ITEMDOWN) { func(pNotify->pCtrl, pNotify->wParam); return true;} } }
#define ON_UIG_LIST_DBCLICK(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_LIST_DBCLICK) { func(pNotify->pCtrl, (int)pNotify->wParam); return true;} } }
#define ON_UIG_LIST_DRAGITEM(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_LIST_DRAGITEM) { func(pNotify->pCtrl, (int)pNotify->wParam, (int)pNotify->lParam); return true;} } }
#define ON_UIG_CB_CHANGE(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_CB_CHANGED) { func(pNotify->pCtrl, (UICheckState)pNotify->wParam); return true;} } }
#define ON_UIG_RAD_SELECTED(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_RAD_SELECTED) { func(pNotify->pCtrl, (int)pNotify->wParam); return true;} } }
#define ON_UIG_LIST_UDPATEDATA(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_LIST_UPDATEDDATE) { func(pNotify->pCtrl, (UIGears::IUIGearsControl*)pNotify->wParam, pNotify->lParam); return true;} } }
#define ON_UIG_COMBOBOX_CHANGED(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_COMBOBOX_CHANGED) { func(pNotify->pCtrl, (int)pNotify->wParam); return true;} } }
#define ON_UIG_TREE_RMOUSEUP(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_TREE_RMOUSEUP) { func(pNotify->pCtrl, (TreeNode*)pNotify->wParam); return true;} } }
#define ON_UIG_TREE_DBCLICK(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_TREE_DBCLICK) { func(pNotify->pCtrl, (TreeNode*)pNotify->wParam); return true;} } }
#define ON_UIG_TREE_SELECTED(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_TREE_SELECTED) { func(pNotify->pCtrl, (TreeNode*)pNotify->wParam); return true;} } }
#define ON_UIG_MENU_COMMAND(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_MENU_COMMAND) { func(pNotify->pCtrl, (int)pNotify->wParam); return true;} } }
#define ON_UIG_TAB_SELECTED(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_TAB_SELECTITEM) { func(pNotify->pCtrl, (int)pNotify->wParam); return true;} } }
#define ON_UIG_WIN_KEYDOWN(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_KEY_DOWN) { func(pNotify->pCtrl, pNotify->wParam); return true;} } }
#define ON_UIG_WIN_KEYUP(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if(pNotify->nMsgId == UIG_KEY_UP) { func(pNotify->wParam, pNotify->lParam); } }
#define ON_UIG_CANVAS_ADD(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_CANVAS_ADD) { func(pNotify->pCtrl, (UIGears::IUIGearsControl*)pNotify->wParam); return true;} } }
#define ON_UIG_CANVAS_REMOVE(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_CANVAS_REMOVE) { func(pNotify->pCtrl, (UIGears::IUIGearsControl*)pNotify->wParam); return true;} } }
#define ON_UIG_CANVAS_SELECTED(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_CANVAS_SELECT) { func(pNotify->pCtrl, (UIGears::IUIGearsControl*)pNotify->wParam); return true;} } }
#define ON_UIG_CANVAS_CLEARSELECTED(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_CANVAS_CLEARSELECT) { func(pNotify->pCtrl); return true;} } }
#define ON_UIG_CANVAS_MOVE(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_CANVAS_MOVE) { func(pNotify->pCtrl); return true;} } }
#define ON_UIG_CANVAS_MOVEUPDOWN(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_CANVAS_MOVEUPDOWN) { func(pNotify->pCtrl, (UIGears::IUIGearsControl*)pNotify->wParam, (UIGears::IUIGearsControl*)pNotify->lParam); return true;} } }
#define ON_UIG_CANVAS_RMOUSEUP(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_CANVAS_RMOUSEUP) { func(pNotify->pCtrl, (int)pNotify->wParam, (int)pNotify->lParam); return true;} } }
#define ON_UIG_EDIT_SETFOCUS(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_EDIT_SETFOCUS) { func(pNotify->pCtrl); return true;} } }
#define ON_UIG_EDIT_KILLFOCUS(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_EDIT_KILLFOCUS) { func(pNotify->pCtrl); return true;} } }
#define ON_UIG_EDIT_TEXTCHNAGE(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_EDIT_TEXTCHANGE) { func(pNotify->pCtrl); return true;} } }
#define ON_UIG_CONTAINER_CLICK(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_CONTAINER_CLICK) { func(pNotify->pCtrl); return true;} } }
#define ON_UIG_SCROLL_POSCHANGE(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_SCROLL_POSCHANGE) { func(pNotify->pCtrl, (int)pNotify->wParam); return true;} } }
#define ON_UIG_SPLITTER_POSCHANGE(ctrl, func) if(pNotify == NULL) { if(ctrl != NULL) { ctrl->AppendEventReceiver(&m_delegate); } } else { if( pNotify->pCtrl == ctrl) { if(pNotify->nMsgId == UIG_SPLITTER_POSCHANGE) { func(pNotify->pCtrl, (int)pNotify->wParam); return true;} } }
#define ON_UIG_POPUP_MENU_COMMAND(func){ if(pNotify && pNotify->nMsgId == UIG_MENU_COMMAND){func(pNotify->pCtrl, (int)pNotify->wParam);} }
#define ON_UIG_USER_CALLBACK(msgId, func){ if(pNotify && pNotify->nMsgId == msgId){func(pNotify->pCtrl);} }
#define ON_UIG_USER_CALLBACK_WITH_PARAM(msgId, func){ if(pNotify && pNotify->nMsgId == msgId){func(pNotify->pCtrl, pNotify->wParam, pNotify->lParam);} }
namespace UIGears
{
	enum UIState
	{
		UI_NORMAL = 0,
		UI_HOT,
		UI_PRESSED,
		UI_DISABLE
	};

	enum UICommonState
	{
		UI_COMMON_NORMAL = 0,
		UI_COMMON_DISABLE
	};

	enum CBK_UIState
	{
		UNCHECK_NORMAL = 0,
		UNCHECK_HOT,
		UNCHECK_PRESSED,
		UNCHECK_DISABLE,
		CHECKED_NORMAL,
		CHECKED_HOT,
		CHECKED_PRESSED,
		CHECKED_DISABLE
	};

	enum GB_POSITION
	{
		GB_LEFTTOP,
		GB_RIGHTTOP,
		GB_LEFTBOTTOM,
		GB_RIGHTBOTTOM
	};

	enum UIGControlType
	{
		UIG_BUTTON = 0,
		UIG_CONTAINER,
		UIG_CHECKBOX,
		UIG_RADIOBOX,
		UIG_LIST,
		UIG_MENULIST,
		UIG_LABEL,
		UIG_SCROLLBAR,
		UIG_EDIT,
		UIG_COMBOBOX,
		UIG_PICTURE,
		UIG_SLIDER,
		UIG_TEMPLATELIST,
		UIG_DATAGRID,
		UIG_TREE,
		UIG_POPUPMENU,
		UIG_MENUBAR,
		UIG_TAB,
		UIG_SPLITTER,
		UIG_PROGRESSBAR,
		UIG_DEDIT,
		UIG_DNUMEDIT,
		UIG_GROUPBOX,
		UIG_IPEDIT,
		UIG_SCROLLVIEW,
		// customer 
		UIG_DIAL,
		UIG_LIGHT,
		UIG_LAST
	};

	enum UIGChildrenLayout
	{
		UIG_CL_HOR,
		UIG_CL_VER,
		UIG_CL_HORFLOAT,
		UIG_CL_VERFLOAT,
		UIG_CL_NOUSE,
		UIG_CL_LAST
	};

	enum UIGDataGridMode
	{
		UIG_DG_REPORT,
		UIG_DG_ICON,
		UIG_DB_SMALLICON,
		UIG_DG_LAST
	};

	enum UIGMenuType
	{
		UIG_MENU_PUSHBUTTON,
		UIG_MENU_RADIOBOX,
		UIG_MENU_CHECKBOX,
		UIG_MENU_SEPERATOR,
		UIG_MENU_KEEPSAME
	};

	enum UIGLayoutType
	{
		UIG_LAYOUT_DOCK = 0,
		UIG_LAYOUT_FILL,
		UIG_LAYOUT_PERCENTAGE,
		UIG_LAYOUT_ABOSOLUTE
	};

	enum StyleType
	{
		UIG_POINTSYLE = 0,
		UIG_RECTSTYLE,
		UIG_FONTSTYLE
	};

	enum FontAlign
	{
		UIG_TOPLEFT = 0,
		UIG_MIDDLECENTER,
		UIG_BOTTOMRIGHT
	};

	enum DockType
	{
		UIG_DOCK_LEFTTOP = 0,
		UIG_DOCK_CENTERMIDDLE,
		UIG_DOCK_RIGHTBOTTOM
	};

	enum DeviceType
	{
		UIG_MOBILE_IPHONE5 = 0,
		UIG_MOBILE_IPHONE8,
		UIG_MOBILE_IPHONE8P,
		UIG_MOBILE_IPHONEX,
		UIG_MOBILE_ANDROID_5_3,
		UIG_MOBILE_ANDROID_16_9,
		UIG_MOBILE_OTHER
	};

	enum OrientationType
	{
		UIG_MOBILE_PORTRAIT = 0,
		UIG_MOBILE_LANDSCAPE
	};

	enum DockSizeType
	{
		UIG_FIX_SIZE = 0,
		UIG_DOCK_SIZE
	};

	enum PercentOffsetType
	{
		UIG_PERCENT_OFFSET_ABS = 0,
		UIG_PERCENT_OFFSET_PER
	};

	// checkbox
	enum UICheckState
	{
		UIG_UNCHECKED = 0,
		UIG_CHECKED,
		UIG_HALFCHECKED
	};

	enum ListDragItemState
	{
		LS_STARTDRAG = 0,
		LS_MOVEDRAG,
		LS_ENDDRAG
	};

	enum ItemMode
	{
		ITEM_LIST = 0,
		ITEM_ICON
	};

	class IScrollOwner
	{
	public:
		virtual void OnVScroll(int pos) = 0;
		virtual void OnHScroll(int pos) = 0;
	};

	class IUIGearsWindow;

	class IUIGearsLayout {
	public:
		/*
		@name GetLayoutType
		@desc ��ȡ��������
		@param void
		@return UIGLayoutType
		*/
		virtual UIGLayoutType GetLayoutType() = 0;
	};

	class IUIGearsPercentageLayout : public IUIGearsLayout
	{
	public:
		/*
		@name GetOffsetX
		@desc ��ȡˮƽƫ����
		@param void
		@return int
		*/
		virtual int GetOffsetX() = 0;
		/*
		@name GetOffsetY
		@desc ��ȡ��ֱƫ����
		@param void
		@return int
		*/
		virtual int GetOffsetY() = 0;
		/*
		@name SetOffsetX
		@desc ����ˮƽƫ����
		@param x int ˮƽƫ����
		@return void
		*/
		virtual void SetOffsetX(int x) = 0;
		/*
		@name SetOffsetY
		@desc ���ô�ֱƫ����
		@param y int ��ֱƫ����
		@return void
		*/
		virtual void SetOffsetY(int y) = 0;
		/*
		@name GetPercentW
		@desc ��ȡ�ٷֱȿ��
		@param void
		@return int
		*/
		virtual int GetPercentW() = 0;
		/*
		@name GetPercentH
		@desc ��ȡ�ٷֱȸ߶�
		@param void
		@return int
		*/
		virtual int GetPercentH() = 0;
		/*
		@name SetPercentW
		@desc ���ðٷֱȿ��
		@param x int �ٷֱȿ�ȣ�����50����50%
		@return void
		*/
		virtual void SetPercentW(int x) = 0;
		/*
		@name SetPercentH
		@desc ���ðٷֱȸ߶�
		@param y int �ٷֱȸ߶ȣ�����50����50%
		@return void
		*/
		virtual void SetPercentH(int y) = 0;
		/*
		@name GetPercentXType
		@desc ��ȡ�ٷֱ�ˮƽƫ�����ͣ�����Ϊ�������꣬���߰ٷֱ�����
		@param void
		@return PercentOffsetType
		*/
		virtual PercentOffsetType GetPercentXType() = 0;
		/*
		@name GetPercentYType
		@desc ��ȡ�ٷֱȴ�ֱƫ�����ͣ�����Ϊ�������꣬���߰ٷֱ�����
		@param void
		@return PercentOffsetType
		*/
		virtual PercentOffsetType GetPercentYType() = 0;
		/*
		@name SetPercentXType
		@desc ���ðٷֱ�ˮƽƫ�����ͣ�����Ϊ�������꣬���߰ٷֱ�����
		@param type PercentOffsetType ƫ������
		@return void
		*/
		virtual void SetPercentXType(PercentOffsetType type) = 0;
		/*
		@name SetPercentYType
		@desc ���ðٷֱȴ�ֱƫ�����ͣ�����Ϊ�������꣬���߰ٷֱ�����
		@param type PercentOffsetType ƫ������
		@return void
		*/
		virtual void SetPercentYType(PercentOffsetType type) = 0;
	};

	class IUIGearsDockLayout : public IUIGearsLayout {
	public:
		/*
		@name SetHorDockType
		@desc ����ˮƽͣ������
		@param hor DockType ͣ������
		@return void
		~
		enum DockType
		{
		UIG_DOCK_LEFTTOP = 0,  // ������߿���
		UIG_DOCK_CENTERMIDDLE, // ����
		UIG_DOCK_RIGHTBOTTOM // ���һ��߿���
		};
		~
		*/
		virtual void SetHorDockType(DockType hor) = 0;
		/*
		@name SetVerDockType
		@desc ���ô�ֱͣ������
		@param hor DockType ͣ������
		@return void
		~
		enum DockType
		{
		UIG_DOCK_LEFTTOP = 0,  // ������߿���
		UIG_DOCK_CENTERMIDDLE, // ����
		UIG_DOCK_RIGHTBOTTOM // ���һ��߿���
		};
		~
		*/
		virtual void SetVerDockType(DockType ver) = 0;
		/*
		@name GetHorDockType
		@desc ��ȡˮƽͣ������
		@param void
		@return DockType
		~
		enum DockType
		{
		UIG_DOCK_LEFTTOP = 0,  // ������߿���
		UIG_DOCK_CENTERMIDDLE, // ����
		UIG_DOCK_RIGHTBOTTOM // ���һ��߿���
		};
		~
		*/
		virtual DockType GetHorDockType() = 0;
		/*
		@name GetVerDockType
		@desc ���ô�ֱͣ������
		@param void
		@return DockType
		~
		enum DockType
		{
		UIG_DOCK_LEFTTOP = 0,  // ������߿���
		UIG_DOCK_CENTERMIDDLE, // ����
		UIG_DOCK_RIGHTBOTTOM // ���һ��߿���
		};
		~
		*/
		virtual DockType GetVerDockType() = 0;
		/*
		@name GetDockWidthType
		@desc ��ȡ�������
		@param void
		@return DockSizeType
		~
		enum DockSizeType
		{
		UIG_FIX_SIZE = 0, // ����ֵ
		UIG_DOCK_SIZE // ͣ��ֵ
		};
		~
		*/
		virtual DockSizeType GetDockWidthType() = 0;
		/*
		@name GetDockWidthType
		@desc ��ȡ�߶�����
		@param void
		@return DockSizeType
		~
		enum DockSizeType
		{
		UIG_FIX_SIZE = 0, // ����ֵ
		UIG_DOCK_SIZE // ͣ��ֵ
		};
		~
		*/
		virtual DockSizeType GetDockHeightType() = 0;
		/*
		@name SetDockWidthType
		@desc ���ÿ������
		@param type DockSizeType ����
		@return void
		*/
		virtual void SetDockWidthType(DockSizeType type) = 0;
		/*
		@name SetDockHeightType
		@desc ���ø߶�����
		@param type DockSizeType ����
		@return void
		*/
		virtual void SetDockHeightType(DockSizeType type) = 0;
		/*
		@name GetOffsetX
		@desc ��ȡˮƽƫ����
		@param void
		@return int
		*/
		virtual int GetOffsetX() = 0;
		/*
		@name GetOffsetY
		@desc ��ȡ�߶�ƫ����
		@param void
		@return int
		*/
		virtual int GetOffsetY() = 0;
		/*
		@name GetOffsetRight
		@desc ��ȡ�Ҳ�ƫ����
		@param void
		@return int
		*/
		virtual int GetOffsetRight() = 0;
		/*
		@name GetOffsetBottom
		@desc ��ȡ�ײ�ƫ����
		@param void
		@return int
		*/
		virtual int GetOffsetBottom() = 0;
		/*
		@name SetOffsetX
		@desc ����ˮƽƫ����
		@param x int ƫ����
		@return void
		*/
		virtual void SetOffsetX(int x) = 0;
		/*
		@name SetOffsetY
		@desc ���ô�ֱƫ����
		@param y int ƫ����
		@return void
		*/
		virtual void SetOffsetY(int y) = 0;
		/*
		@name SetOffsetRight
		@desc �����Ҳ�ƫ����
		@param r int ƫ����
		@return void
		*/
		virtual void SetOffsetRight(int r) = 0;
		/*
		@name SetOffsetBottom
		@desc ���õײ�ƫ����
		@param b int ƫ����
		@return void
		*/
		virtual void SetOffsetBottom(int b) = 0;
		/*
		@name SetFixWidth
		@desc ���ÿ�Ⱦ���ֵ
		@param w int ���ֵ
		@return void
		*/
		virtual void SetFixWidth(int w) = 0;
		/*
		@name SetFixHeight
		@desc ���ø߶Ⱦ���ֵ
		@param h int �߶�ֵ
		@return void
		*/
		virtual void SetFixHeight(int h) = 0;
		/*
		@name GetFixWidth
		@desc ��ȡ��Ⱦ���ֵ
		@param void
		@return int
		*/
		virtual int GetFixWidth() = 0;
		/*
		@name GetFixHeight
		@desc ��ȡ�߶Ⱦ���ֵ
		@param void
		@return int
		*/
		virtual int GetFixHeight() = 0;
	};

	class IUIGearsFillLayout : public IUIGearsLayout {
	public:
		/*
		@name SetMarginRight
		@desc ���þ����Ҳ��С
		@param r int �������
		@return void
		*/
		virtual void SetMarginRight(int r) = 0;
		/*
		@name SetMarginBottom
		@desc ���þ����²��С
		@param b int �������
		@return void
		*/
		virtual void SetMarginBottom(int b) = 0;
		/*
		@name SetMarginX
		@desc ���þ�������С
		@param x int �������
		@return void
		*/
		virtual void SetMarginX(int x) = 0;
		/*
		@name SetMarginY
		@desc ���þ����Ϸ���С
		@param y int �������
		@return void
		*/
		virtual void SetMarginY(int y) = 0;
		/*
		@name SetMarginOffset
		@desc ���þ������ܴ�С
		@param x int �������С
		@param y int �ϲ�����С
		@param r int �Ҳ�����С
		@param b int �²�����С
		@return void
		*/
		virtual void SetMarginOffset(int x, int y, int r, int b) = 0;
		/*
		@name GetMarginX
		@desc ��ȡ���������
		@param void
		@return int
		*/
		virtual int GetMarginX() = 0;
		/*
		@name GetMarginY
		@desc ��ȡ�ϲ�������
		@param void
		@return int
		*/
		virtual int GetMarginY() = 0;
		/*
		@name GetMarginY
		@desc ��ȡ�Ҳ�������
		@param void
		@return int
		*/
		virtual int GetMarginRight() = 0;
		/*
		@name GetMarginY
		@desc ��ȡ�²�������
		@param void
		@return int
		*/
		virtual int GetMarginBottom() = 0;
	};

	class IUIGearsStyle {
	public:
		/*
		@name GetStyleName
		@desc ��ȡ��ʽ����
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetStyleName() = 0;
	};

	class IUIGearsRectStyle : public IUIGearsStyle {
	public:
		/*
		@name GetUseFill
		@desc ��ȡ�Ƿ�ʹ����ɫ���
		@param void
		@return bool
		*/
		virtual bool GetUseFill() = 0;
		/*
		@name GetUseBorder
		@desc ��ȡ�Ƿ���Ʊ߿�
		@param void
		@return bool
		*/
		virtual bool GetUseBorder() = 0;
		/*
		@name GetUserImage
		@desc ��ȡ�Ƿ�ʹ��ͼƬ���
		@param void
		@return bool
		*/
		virtual bool GetUserImage() = 0;
		/*
		@name SetUseFill
		@desc �����Ƿ�ʹ����ɫ���
		@param bUse bool �Ƿ�ʹ��
		@return void
		*/
		virtual void SetUseFill(bool bUse) = 0;
		/*
		@name SetUseBorder
		@desc �����Ƿ����߿�
		@param bUse bool �Ƿ�ʹ��
		@return void
		*/
		virtual void SetUseBorder(bool bUse) = 0;
		/*
		@name SetUserImage
		@desc �����Ƿ����ͼƬ
		@param bUse bool �Ƿ�ʹ��
		@return void
		*/
		virtual void SetUserImage(bool bUse) = 0;
		/*
		@name GetFillColor
		@desc ��ȡ�����ɫ
		@param void
		@return unsigned int
		*/
		virtual unsigned int GetFillColor() = 0;
		/*
		@name SetFillColor
		@desc ���������ɫ
		@param color  unsigned int  ��ɫֵ
		@return void
		*/
		virtual void SetFillColor(unsigned int color) = 0;
		/*
		@name GetBorderColor
		@desc ��ȡ�߿���ɫ
		@param void
		@return unsigned int
		*/
		virtual unsigned int GetBorderColor() = 0;
		/*
		@name SetBorderColor
		@desc ���ñ߿���ɫ
		@param color  unsigned int  ��ɫֵ
		@return void
		*/
		virtual void SetBorderColor(unsigned int color) = 0;
		/*
		@name GetBorderSize
		@desc ��ȡ�߿��С
		@param void
		@return unsigned int
		*/
		virtual unsigned int GetBorderSize() = 0;
		/*
		@name SetBorderSize
		@desc ���ñ߿��С
		@param size  unsgined int  ��С
		@return void
		*/
		virtual void SetBorderSize(unsigned int size) = 0;
		/*
		@name GetRoundSize
		@desc ��ȡԲ�Ǵ�С
		@param void
		@return unsigned int
		*/
		virtual unsigned int GetRoundSize() = 0;
		/*
		@name SetRoundSize
		@desc ����Բ�Ǵ�С
		@param unsigned int Բ�Ǵ�С
		@return void
		*/
		virtual void SetRoundSize(unsigned int size) = 0;
		/*
		@name SetImageName
		@desc ����ͼƬ·��
		@param strImageName  const tchar*  ͼƬ·��
		@return void
		*/
		virtual void SetImageName(const tchar* strImageName) = 0;
		/*
		@name GetImageName
		@desc ��ȡͼƬ·��
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetImageName() = 0;
		/*
		@name GetMargin
		@desc ��ȡ�Ź��ָ����ܼ��
		@param left int& �����
		@param top int& �ϲ���
		@param right int& �Ҳ���
		@param bottom int& �²���
		@return void
		*/
		virtual void GetMargin(int& left, int& top, int& right, int& bottom) = 0;
		/*
		@name SetMargin
		@desc ���þŹ��ָ����ܼ��
		@param left int �����
		@param top int �ϲ���
		@param right int �Ҳ���
		@param bottom int �²���
		@return void
		*/
		virtual void SetMargin(int left, int top, int right, int bottom) = 0;
		/*
		@name SetDrawBorder
		@desc ���ñ߿����
		@param left int ���߿�
		@param top int �ϲ�߿�
		@param right int �Ҳ�߿�
		@param bottom int �²�߿�
		@return void
		*/
		virtual void SetDrawBorder(bool left, bool top, bool right, bool bottom) = 0;
		/*
		@name GetDrawBorder
		@desc ��ȡ�߿����
		@param left int& ���߿�
		@param top int& �ϲ�߿�
		@param right int& �Ҳ�߿�
		@param bottom int& �²�߿�
		@return void
		*/
		virtual void GetDrawBorder(bool& left, bool& top, bool& right, bool& bottom) = 0;
		/*
		@name SetRepeatImage
		@desc ����ͼƬ��ƽ�̻�������
		@param left bool ���ͼƬ
		@param top bool �ϲ�ͼƬ
		@param center bool ����ͼƬ
		@param right bool �Ҳ�ͼƬ
		@param bottom bool �²�ͼƬ
		@return void
		*/
		virtual void SetRepeatImage(bool left, bool top, bool center, bool right, bool bottom) = 0;
		/*
		@name SetRepeatImage
		@desc ��ȡͼƬ��ƽ�̻�������
		@param left bool& ���ͼƬ
		@param top bool& �ϲ�ͼƬ
		@param center bool& ����ͼƬ
		@param right bool& �Ҳ�ͼƬ
		@param bottom bool& �²�ͼƬ
		@return void
		*/
		virtual void GetRepeatImage(bool& left, bool& top, bool& center, bool& right, bool& bottom) = 0;
	};

	class IUIGearsTextStyle : public IUIGearsStyle {
	public:
		/*
		@name GetStyleName
		@desc ��ȡ��ʽ����
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetStyleName() = 0;
		/*
		@name GetFontColor
		@desc ��ȡ������ɫ
		@param void
		@return int
		*/
		virtual int GetFontColor() = 0;
		/*
		@name SetFontColor
		@desc ����������ɫ
		@param clr int ��ɫ
		@return void
		*/
		virtual void SetFontColor(int clr) = 0;
		/*
		@name GetFontSize
		@desc ��ȡ������ɫ
		@param void
		@return int
		*/
		virtual int GetFontSize() = 0;
		/*
		@name SetFontSize
		@desc ��ȡ�����С
		@param void
		@return int
		*/
		virtual void SetFontSize(int size) = 0;
		/*
		@name SetOffsetX
		@desc �������ƫ����
		@param offsetX int ƫ����
		@return void
		*/
		virtual void SetOffsetX(int offsetX) = 0;
		/*
		@name GetOffsetX
		@desc ��ȡ���ƫ����
		@param void
		@return int
		*/
		virtual int GetOffsetX() = 0;
		/*
		@name SetOffsetY
		@desc ���ô�ֱƫ����
		@param offsetY int ƫ����
		@return void
		*/
		virtual void SetOffsetY(int offsetY) = 0;
		/*
		@name GetOffsetY
		@desc ��ȡ��ֱƫ����
		@param void
		@return int
		*/
		virtual int GetOffsetY() = 0;
		/*
		@name SetBold
		@desc �����Ƿ�Ӵ�
		@param bold bool �Ӵ�
		@return void
		*/
		virtual void SetBold(bool bold) = 0;
		/*
		@name GetBold
		@desc ��ȡ�Ƿ�Ӵ�
		@param void
		@return bool
		*/
		virtual bool GetBold() = 0;
		/*
		@name SetItalic
		@desc �����Ƿ�б��
		@param italic bool б��
		@return void
		*/
		virtual void SetItalic(bool italic) = 0;
		/*
		@name GetItalic
		@desc ��ȡ�Ƿ�б��
		@param void
		@return bool
		*/
		virtual bool GetItalic() = 0;
		/*
		@name SetHorAlign
		@desc ����ˮƽ���뷽ʽ
		@param align FontAlign ���뷽ʽ
		@return void
		~
		enum FontAlign
		{
		UIG_TOPLEFT = 0,
		UIG_MIDDLECENTER,
		UIG_BOTTOMRIGHT
		};
		~
		*/
		virtual void SetHorAlign(UIGears::FontAlign align) = 0;
		/*
		@name GetHorAlign
		@desc ��ȡˮƽ���뷽ʽ
		@param void
		@return FontAlign
		~
		enum FontAlign
		{
		UIG_TOPLEFT = 0,
		UIG_MIDDLECENTER,
		UIG_BOTTOMRIGHT
		};
		~
		*/
		virtual UIGears::FontAlign GetHorAlign() = 0;
		/*
		@name SetVerAlign
		@desc ���ô�ֱ���뷽ʽ
		@param align FontAlign ���뷽ʽ
		@return void
		~
		enum FontAlign
		{
		UIG_TOPLEFT = 0,
		UIG_MIDDLECENTER,
		UIG_BOTTOMRIGHT
		};
		~
		*/
		virtual void SetVerAlign(UIGears::FontAlign align) = 0;
		/*
		@name GetHorAlign
		@desc ��ȡ��ֱ���뷽ʽ
		@param void
		@return FontAlign
		~
		enum FontAlign
		{
		UIG_TOPLEFT = 0,
		UIG_MIDDLECENTER,
		UIG_BOTTOMRIGHT
		};
		~
		*/
		virtual UIGears::FontAlign GetVerAlign() = 0;
		/*
		@name SetSingleLine
		@desc �����Ƿ�����ʾ
		@param singleLine bool �Ƿ�����ʾ
		@return void
		*/
		virtual void SetSingleLine(bool singleLine) = 0;
		/*
		@name GetSingleLine
		@desc ��ȡ�Ƿ�����ʾ
		@param void
		@return bool
		*/
		virtual bool GetSingleLine() = 0;
		/*
		@name SetUnderline
		@desc �����Ƿ����»���
		@param bool underline �»���
		@return void
		*/
		virtual void SetUnderline(bool underline) = 0;
		/*
		@name GetUnderline
		@desc ��ȡ�Ƿ����»���
		@param void
		@return bool
		*/
		virtual bool GetUnderline() = 0;
		/*
		@name GetFontFamily
		@desc ��ȡ����
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetFontFamily() = 0;
		/*
		@name GetFontFamilyA
		@desc ��ȡ���壬����ֵΪchar
		@param void
		@return const char*
		*/
		virtual const char* GetFontFamilyA() = 0;
		/*
		@name SetFontFamily
		@desc ��������
		@param family  const tchar*  ��������
		@return void
		*/
		virtual void SetFontFamily(const tchar* family) = 0;
		/*
		@name GetIsLCD
		@desc ��ȡ���壬����ֵΪchar
		@param void
		@return const char*
		*/
		virtual bool GetIsLCD() = 0;
		/*
		@name SetIsLCD
		@desc ��������
		@param family  const tchar*  ��������
		@return void
		*/
		virtual void SetIsLCD(bool isLCD  ) = 0;
	};

	class IUIGearsControl {
	public:
		/*
		@name Invalidate
		@desc ���»��ƿؼ�,ע�⣺�˲���Ϊ�첽����
		@param void
		@return void
		*/
		virtual void Invalidate() = 0;
		/*
		@name Invalidate
		@desc ���»��ƿؼ�,ע�⣺�˲���Ϊ�첽����,�Դ���ָ����������ػ棬ָ����λ��Ϊ�����ϵľ�������λ�ã����Ͻ�Ϊ0,0�� ���½�Ϊ���ڵĿ�ȣ��߶ȡ�
		@param x int ���λ��
		@param y int �ϲ�λ��
		@param w int �ػ���
		@param h int �ػ�߶�
		@return void
		*/
		virtual void Invalidate(int x, int y, int w, int h) = 0;
		/*
		@name Resize
		@desc ���¼���ؼ������ڲ��ӿؼ���λ�úʹ�С��ע�⣺�˲���Ϊ�첽��������������ִ��
		@param void
		@return void
		*/
		virtual void Resize() = 0;
		/*
		@name ResizeSync
		@desc ��������ؼ��ļ����ӿؼ���λ�úʹ�С,ע�⣺�˲���Ϊͬ������������ִ�д�С����
		@param void
		@return void
		*/
		virtual void ResizeSync() = 0;
		/*
		@name AppendEventReceiver
		@desc ���ؼ������¼������������Ը��ؼ����ö���¼�������
		@param pDelegateObj IEventRecevier* �¼�������ָ��
		@return void
		*/
		virtual void AppendEventReceiver(IEventRecevier* pDelegateObj) = 0;
		/*
		@name RemoveEventReceiver
		@desc ���ؼ���ĳ���¼��������Ƴ���
		@param pDelegateObj IEventRecevier* �¼�������ָ��
		@return void
		*/
		virtual void RemoveEventReceiver(IEventRecevier* pDelegateObj) = 0;
		/*
		@name RemoveAllEventReceiver
		@desc ���ؼ������е��¼��������Ƴ���
		@param void
		@return void
		*/
		virtual void RemoveAllEventReceiver() = 0;
		/*
		@name SetVisibility
		@desc ���ÿؼ��Ƿ���ʾ
		@param visibility bool �Ƿ���ʾ
		@return void
		*/
		virtual void SetVisibility(bool visibility) = 0;
		/*
		@name GetVisibility
		@desc ��ȡ�ؼ�����ʾ״̬
		@param void
		@return bool
		*/
		virtual bool GetVisibility() = 0;
		/*
		@name SetEnable
		@desc ���ÿؼ��Ƿ����ã����Ϊfalse����ÿؼ����û������ɵ���ÿؼ������еĿؼ��������µ�״̬Ҳ�����
		@param enable bool �Ƿ�����
		@return void
		*/
		virtual void SetEnable(bool enable) = 0;
		/*
		@name GetEnable
		@desc ��ȡ�ؼ�������״̬
		@param void
		@return bool
		*/
		virtual bool GetEnable() = 0;
		/*
		@name SetRect
		@desc ���ÿؼ�������λ�ã�������Ϊ����ڴ��ڵ����꣬���Ͻ�Ϊ0,0
		@param x int ���λ��
		@param y int �ϲ�λ��
		@param w int �ؼ����
		@param h int �ؼ��߶�
		@return bool
		*/
		virtual void SetRect(int x, int y, int w, int h) = 0;
		/*
		@name GetControlByName
		@desc �������ƻ�ȡ�ӿؼ�
		@param name  const tchar*  �ؼ�����
		@return UIGears::IUIGearsControl*
		*/
		virtual IUIGearsControl* GetControlByName(const tchar* name) = 0;
		/*
		@name GetWindowX
		@desc ��ȡ�ؼ��ڴ����ϵ�X������λ��
		@param void
		@return int
		*/
		virtual int GetWindowX() = 0;
		/*
		@name GetWindowY
		@desc ��ȡ�ؼ��ڴ����ϵ�Y������λ��
		@param void
		@return int
		*/
		virtual int GetWindowY() = 0;
		/*
		@name GetX
		@desc ��ȡ�ؼ��ڸ��ؼ��ϵ�X������λ��
		@param void
		@return int
		*/
		virtual int GetX() = 0;
		/*
		@name GetY
		@desc ��ȡ�ؼ��ڸ��ؼ��ϵ�Y������λ��
		@param void
		@return int
		*/
		virtual int GetY() = 0;
		/*
		@name GetWidth
		@desc ��ȡ�ؼ��Ŀ��
		@param void
		@return int
		*/
		virtual int GetWidth() = 0;
		/*
		@name GetHeight
		@desc ��ȡ�ؼ��ĸ߶�
		@param void
		@return int
		*/
		virtual int GetHeight() = 0;
		/*
		@name SetX
		@desc ���ÿؼ����븸�ؼ����ľ���
		@param x int �������ľ���
		@return void
		*/
		virtual void SetX(int x) = 0;
		/*
		@name SetY
		@desc ���ÿؼ����븸�ؼ��Ϸ��ľ���
		@param y int �����ϲ�ľ���
		@return void
		*/
		virtual void SetY(int y) = 0;
		/*
		@name SetWidth
		@desc ���ÿؼ����
		@param w int �ؼ����
		@return void
		*/
		virtual void SetWidth(int w) = 0;
		/*
		@name SetHeight
		@desc ���ÿؼ��ĸ߶�
		@param h int �ؼ��߶�
		@return void
		*/
		virtual void SetHeight(int h) = 0;
		/*
		@name GetWindowPos
		@desc ��ȡ�ؼ��ڴ����ϵ�λ��
		@param x int& �ؼ�x����λ��
		@param y int& �ؼ�y����λ��
		@return void
		*/
		virtual void GetWindowPos(int& x, int& y) = 0;
		/*
		@name GetLayout
		@desc ��ȡ�ؼ��Ĳ��ֶ���,ע�⣺����ÿؼ�ʹ�õ��Ǿ��Բ��֣���ô��ȡ���Ĳ��ֶ���Ϊ��
		@param void
		@return IUIGearsLayout*
		*/
		virtual IUIGearsLayout* GetLayout() = 0;
		/*
		@name SetLayout
		@desc ���ؼ����ò��ֶ����������ΪNULL����ʹ�þ��Բ���
		@param UIGLayoutType type
		@return IUIGearsLayout*
		*/
		virtual IUIGearsLayout* SetLayout(UIGLayoutType type) = 0;
		/*
		@name GetChildrenCount
		@desc ��ȡ�ÿؼ����ӿؼ�����
		@param void
		@return int
		*/
		virtual int GetChildrenCount() = 0;
		/*
		@name GetControlByIndex
		@desc ͨ�������Ż�ȡ�ӿؼ�
		@param index int ������
		@return IUIGearsControl*
		*/
		virtual IUIGearsControl* GetControlByIndex(int index) = 0;
		/*
		@name RemoveChild
		@desc ɾ���ӿؼ�
		@param index int �ӿؼ��������ţ����ܳ����ӿؼ�������
		@return bool
		*/
		virtual bool RemoveChild(IUIGearsControl* pEle) = 0;
		/*
		@name RemoveChild
		@desc ��ȡ�ؼ�������
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetControlName() = 0;
		/*
		@name GetControlTypeName
		@desc ��ȡ�ؼ�����������
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetControlTypeName() = 0;
		/*
		@name SetControlName
		@desc �޸Ŀؼ�������
		@param name  const tchar*  �ؼ��µ�����
		@return void
		*/
		virtual void SetControlName(const tchar* name) = 0;
		/*
		@name SetUserData
		@desc ����һ���û��Զ�������
		@param data PARAM �û�����
		@return void
		*/
		virtual void SetUserData(PARAM data) = 0;
		/*
		@name GetUserData
		@desc ��ȡ�û��Զ�������
		@param void
		@return PARAM
		*/
		virtual PARAM GetUserData() = 0;
		/*
		@name GetParentControl
		@desc ��ȡ���ؼ���ָ��
		@param void
		@return UIGears::IUIGearsControl*
		*/
		virtual IUIGearsControl* GetParentControl() = 0;
		/*
		@name GetTooltip
		@desc ��ȡ�ؼ���Tooltip�ı�
		@param void
		@return const tchar* 
		*/
		virtual const tchar* GetTooltip() = 0;
		/*
		@name GetTooltip
		@desc ���ÿؼ���Tooltip�ı�
		@param tooltip const tchar* tooltip�ı�
		@return void
		*/
		virtual void SetTooltip(const tchar* tooltip) = 0;
		virtual void SetMarkDelete(bool isDelete) = 0;
		virtual bool GetMarkDelete() = 0;
		virtual void* ExecuteMethod(int methodId, void** params, int size) = 0;
		virtual void EnableExportCode(bool enable) = 0;
		virtual bool IsEnableExportCode() = 0;
		virtual const tchar* GetExportControlName() = 0;
		virtual void SetExportControlName(const tchar* name) = 0;
		virtual const tchar* GetExportFun(const tchar* fun) = 0;
		virtual void SetExportFun(const tchar* fun, const tchar* name) = 0;
		/*
		@name Copy
		@desc ����ǰ�ؼ����ӿؼ�������ָ���ؼ���
		@param name  const tchar*  �¿ؼ�����
		@param pParent UIGears::IUIGearsControl* ���ؼ�ָ��
		@param insertPos int �ڸ��ؼ���λ�ã�Ĭ��ֵ-1�������뵽���ؼ���ĩβ�ؼ�
		@return UIGears::IUIGearsControl* �����¿��������Ŀؼ�
		*/
		virtual IUIGearsControl* Copy(const tchar* name, IUIGearsControl* pParent, int insertPos = -1) = 0;
		virtual void SetAlpha(unsigned char alpha) = 0;
		virtual unsigned char GetAlpha() = 0;
	};

	class IUIGButton : public IUIGearsControl
	{
	public:
		/*
		@name SetText
		@desc ���ð�ť�ı�����
		@param text  const tchar*  ��ť�ı�����
		@return void
		*/
		virtual void SetText(const tchar* text) = 0;
		/*
		@name GetText
		@desc ��ȡ��ť�ı�����
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetText() = 0;
		/*
		@name SetIcon
		@desc ���ð�ťͼ��
		@param iconPath  const tchar*  ͼ��·��
		@return void
		*/
		virtual void SetIcon(const tchar* iconPath) = 0;
		/*
		@name GetIcon
		@desc ��ȡ��ťͼ��·��
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetIcon() = 0;
		/*
		@name SetHotIcon
		@desc ���ð�ť����״̬ͼ��
		@param iconPath  const tchar*  ͼ��·��
		@return void
		*/
		virtual void SetHotIcon(const tchar* iconPath) = 0;
		/*
		@name GetHotIcon
		@desc ��ȡ��ť����״̬ͼ��·��
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetHotIcon() = 0;
		/*
		@name SetUseIcon
		@desc ��ȡ�Ƿ���ʾͼ��
		@param use bool �Ƿ���ʾͼ��
		@return void
		*/
		virtual void SetUseIcon(bool use) = 0;
		/*
		@name GetUseIcon
		@desc ��ȡ�Ƿ���ʾͼ��
		@param void
		@return bool
		*/
		virtual bool GetUseIcon() = 0;
		/*
		@name SetTextX
		@desc ���ð�ť����ˮƽƫ����
		@param x int ƫ����
		@return void
		*/
		virtual void SetTextX(int x) = 0;
		/*
		@name GetTextX
		@desc ��ȡ��ť����ˮƽƫ����
		@param void
		@return int
		*/
		virtual int GetTextX() = 0;
		/*
		@name SetTextY
		@desc ���ð�ť���ִ�ֱƫ����
		@param y int ƫ����
		@return void
		*/
		virtual void SetTextY(int y) = 0;
		/*
		@name GetTextY
		@desc ��ȡ��ť���ִ�ֱƫ����
		@param void
		@return int
		*/
		virtual int GetTextY() = 0;
		/*
		@name SetShowText
		@desc �����Ƿ���ʾ�ı�
		@param show bool �Ƿ���ʾ�ı�
		@return void
		*/
		virtual void SetShowText(bool show) = 0;
		/*
		@name GetShowText
		@desc ��ȡ�Ƿ���ʾ�ı�
		@param void
		@return bool
		*/
		virtual bool GetShowText() = 0;
		/*
		@name SetBackgroundStyle
		@desc ���ñ�����ʽ
		@param state UIState ״̬ö��
		@param style IUIGearsRectStyle* ״̬����ָ��
		@return bool
		*/
		virtual bool SetBackgroundStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc ��ȡ������ʽ
		@param state UIState ״̬ö��
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UIState state) = 0;
		/*
		@name SetTextStyle
		@desc ����������ʽ
		@param state UIState ״̬ö��
		@param style IUIGearsRectStyle* ������ʽָ��
		@return bool
		*/
		virtual bool SetTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetTextStyle
		@desc ��ȡ������ʽ
		@param state UIState ״̬ö��
		@return IUIGearsTextStyle*
		*/
		virtual IUIGearsTextStyle* GetTextStyle(UIState state) = 0;
		/*
		@name SetIconHorDockType
		@desc ����ͼ��ˮƽͣ������
		@param dock DockType ���뷽ʽö��
		@return void
		*/
		virtual void SetIconHorDockType(DockType dock) = 0;
		/*
		@name GetIconHorDockType
		@desc ��ȡͼ��ˮƽͣ������
		@param void
		@return DockType
		*/
		virtual DockType GetIconHorDockType() = 0;
		/*
		@name SetIconVerDockType
		@desc ����ͼ�괹ֱͣ������
		@param dock DockType ���뷽ʽö��
		@return DockType
		*/
		virtual void SetIconVerDockType(DockType dock) = 0;
		/*
		@name GetIconVerDockType
		@desc ��ȡͼ�괹ֱͣ������
		@param void
		@return DockType
		*/
		virtual DockType GetIconVerDockType() = 0;
		/*
		@name SetIconX
		@desc ����ͼ�괹ֱƫ����
		@param x int ƫ����
		@return void
		*/
		virtual void SetIconX(int x) = 0;
		/*
		@name GetIconX
		@desc ��ȡͼ��ˮƽƫ����
		@param void
		@return int
		*/
		virtual int GetIconX() = 0;
		/*
		@name SetIconY
		@desc ����ͼ�괹ֱƫ����
		@param y int ƫ����
		@return void
		*/
		virtual void SetIconY(int y) = 0;
		/*
		@name GetIconY
		@desc ��ȡͼ�괹ֱƫ����
		@param void
		@return int
		*/
		virtual int GetIconY() = 0;
	};

	class IUIGGroupBox : public IUIGearsControl
	{
	public:
		/*
		@name SetText
		@desc ������ʾ�ı�����
		@param type  const tchar*  �ı�����
		@return void
		*/
		virtual void SetText(const tchar* text) = 0;
		/*
		@name GetText
		@desc ��ȡ��ʾ�ı�����
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetText() = 0;
		/*
		@name SetShowText
		@desc �����Ƿ���ʾ�ı�
		@param show bool �Ƿ���ʾ�ı�
		@return void
		*/
		virtual void SetShowText(bool show) = 0;
		/*
		@name GetShowText
		@desc ��ȡ�Ƿ���ʾ�ı�
		@param void
		@return bool
		*/
		virtual bool GetShowText() = 0;
		/*
		@name SetLineOffset
		@desc �����ߺ����ܵļ��
		@param offset int �����С
		@return void
		*/
		virtual void SetLineOffset(int offset) = 0;
		/*
		@name GetLineOffset
		@desc ��ȡ�ߺ����ܵļ��
		@param void
		@return int
		*/
		virtual int GetLineOffset() = 0;
		/*
		@name SetLineColor
		@desc �����ߵ���ɫ
		@param color int ��ɫֵ������0xffff0000
		@return void
		*/
		virtual void SetLineColor(int color) = 0;
		/*
		@name GetLineColor
		@desc ��ȡ�ߵ���ɫ
		@param void
		@return int ��ɫֵ������0xffff0000
		*/
		virtual int GetLineColor() = 0;
		/*
		@name SetLineSize
		@desc �����ߵĴ�ϸ
		@param size int ��ϸ����ֵ
		@return void
		*/
		virtual void SetLineSize(int size) = 0;
		/*
		@name GetLineSize
		@desc ��ȡ�ߵĴ�ϸ
		@param void
		@return int ��ϸ����ֵ
		*/
		virtual int GetLineSize() = 0;
		/*
		@name SetTextPosition
		@desc �������ֵĶ���λ��
		@param pos GB_POSITION ����ö��
		@return void
		~
		enum GB_POSITION
		{
		GB_LEFTTOP,
		GB_RIGHTTOP,
		GB_LEFTBOTTOM,
		GB_RIGHTBOTTOM
		};
		~
		*/
		virtual void SetTextPosition(GB_POSITION pos) = 0;
		/*
		@name GetTextPosition
		@desc ��ȡ���ֵĶ���λ��
		@param posvoid
		@return GB_POSITION
		~
		enum GB_POSITION
		{
		GB_LEFTTOP,
		GB_RIGHTTOP,
		GB_LEFTBOTTOM,
		GB_RIGHTBOTTOM
		};
		~
		*/
		virtual GB_POSITION GetTextPosition() = 0;
		/*
		@name SetBackgroundStyle
		@desc ���ñ�����ʽ
		@param state UICommonState ״̬ö��
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool �Ƿ�ɹ�
		~
		enum GB_POSITION
		{
		GB_LEFTTOP,
		GB_RIGHTTOP,
		GB_LEFTBOTTOM,
		GB_RIGHTBOTTOM
		};
		~
		*/
		virtual bool SetBackgroundStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc ��ȡ������ʽ
		@param state UICommonState ״̬ö��
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UICommonState state) = 0;
		/*
		@name SetTextStyle
		@desc ����������ʽ
		@param state UICommonState ״̬ö��
		@param style IUIGearsRectStyle* ����ָ��
		@return bool �Ƿ�ɹ�
		*/
		virtual bool SetTextStyle(UICommonState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc ��ȡ������ʽ
		@param state UICommonState ״̬ö��
		@return IUIGearsTextStyle*
		*/
		virtual IUIGearsTextStyle* GetTextStyle(UICommonState state) = 0;
	};

	class IUIGTab : public IUIGearsControl
	{
	public:
		/*
		@name AppendItem
		@desc ���item��Ŀ
		@param text  const tchar*  �ı�����
		@return bool
		*/
		virtual bool AppendItem(const tchar* text) = 0;
		/*
		@name SetSelectedItem
		@desc ����ѡ��item
		@param index int ������
		@return bool
		*/
		virtual bool SetSelectedItem(int index) = 0;
		/*
		@name GetSelectedItem
		@desc ��ȡѡ��item
		@param void
		@return int
		*/
		virtual int GetSelectedItem() = 0;
		/*
		@name GetItemText
		@desc ����������ȡitem���ı�
		@param index int ������
		@return const tchar*
		*/
		virtual const tchar* GetItemText(int index) = 0;
		/*
		@name SetItemData
		@desc ����item��data����
		@param index int ������
		@param data PARAM data����
		@return void
		*/
		virtual void SetItemData(int index, PARAM data) = 0;
		/*
		@name GetItemData
		@desc ��ȡitem������
		@param index int ������
		@return PARAM
		*/
		virtual PARAM GetItemData(int index) = 0;
		/*
		@name GetItemCount
		@desc ��ȡitem������
		@param void
		@return int
		*/
		virtual int GetItemCount() = 0;
		/*
		@name GetIsHorizontal
		@desc ��ȡ�Ƿ���ˮƽ��ʾ
		@param void
		@return bool
		*/
		virtual bool GetIsHorizontal() = 0;
		/*
		@name SetIsHorizontal
		@desc �����Ƿ���ˮƽ��ʾ
		@param isHor bool �Ƿ�ˮƽ��ʾ
		@return void
		*/
		virtual void SetIsHorizontal(bool isHor) = 0;
		/*
		@name SetItemSize
		@desc ����item�Ŀ�Ȼ��߸߶�
		@param size int ��С
		@return void
		*/
		virtual void SetItemSize(int size) = 0;
		/*
		@name GetItemSize
		@desc ��ȡitem�Ŀ�Ȼ��߸߶�
		@param void
		@return int
		*/
		virtual int GetItemSize() = 0;
		/*
		@name SetShowText
		@desc �����Ƿ���ʾ����
		@param showText bool �Ƿ���ʾ����
		@return void
		*/
		virtual void SetShowText(bool showText) = 0;
		/*
		@name GetShowText
		@desc ��ѯ�Ƿ���ʾ����
		@param void
		@return bool
		*/
		virtual bool GetShowText() = 0;
		/*
		@name SetShowIcon
		@desc �����Ƿ���ʾͼ��
		@param showIcon bool �Ƿ���ʾͼ��
		@return void
		*/
		virtual void SetShowIcon(bool showIcon) = 0;
		/*
		@name GetShowIcon
		@desc ��ѯ�Ƿ���ʾͼ��
		@param void
		@return bool
		*/
		virtual bool GetShowIcon() = 0;
		/*
		@name SetItemSpace
		@desc ����item�ļ��
		@param space int �����С
		@return void
		*/
		virtual void SetItemSpace(int space) = 0;
		/*
		@name GetItemSpace
		@desc ��ȡitem�ļ��
		@param void
		@return int
		*/
		virtual int GetItemSpace() = 0;
		/*
		@name SetBackgroundStyle
		@desc ���ñ�����ʽ
		@param state UICommonState ״̬ö��
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetBackgroundStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc ��ȡ������ʽ
		@param state UICommonState ״̬ö��
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UICommonState state) = 0;
		/*
		@name SetItemStyle
		@desc ����item������ʽ
		@param state UICommonState ״̬ö��
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetItemStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetItemStyle
		@desc ��ȡitem������ʽ
		@param state UICommonState ״̬ö��
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetItemStyle(UIState state) = 0;
		/*
		@name SetTextStyle
		@desc ����item������ʽ
		@param state UICommonState ״̬ö��
		@param style IUIGearsTextStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetTextStyle
		@desc ��ȡitem������ʽ
		@param state UICommonState ״̬ö��
		@return IUIGearsTextStyle*
		*/
		virtual IUIGearsTextStyle* GetTextStyle(UIState state) = 0;
		/*
		@name RemoveAll
		@desc ɾ�����е�items
		@param void
		@return void
		*/
		virtual void RemoveAll() = 0;
		/*
		@name RemoveItem
		@desc ��������ɾ��item
		@param index  unsigned int  ������
		@return bool
		*/
		virtual bool RemoveItem(unsigned int index) = 0;
	};

	class IUIGCheckBox : public IUIGearsControl
	{
	public:
		/*
		@name IsChecked
		@desc �Ƿ�ѡ��
		@param void
		@return bool   �Ƿ�ѡ��
		*/
		virtual bool IsChecked() = 0;
		/*
		@name SetChecked
		@desc �����Ƿ�ѡ��
		@param bCheck  bool  �Ƿ�ѡ��
		@return void
		*/
		virtual void SetChecked(bool bCheck) = 0;
		/*
		@name SetText
		@desc �����ı�
		@param text  const tchar*  �Ƿ�ѡ��
		@return void
		*/
		virtual void SetText(const tchar* text) = 0;
		/*
		@name GetText
		@desc ��ȡ�ı�
		@param void
		@return const tchar* �ı�����
		*/
		virtual const tchar* GetText() = 0;
		/*
		@name SetShowText
		@desc �����Ƿ���ʾ�ı�
		@param show   bool  �Ƿ���ʾ�ı�
		@return void
		*/
		virtual void SetShowText(bool show) = 0;
		/*
		@name GetShowText
		@desc ��ȡ�Ƿ���ʾ�ı�
		@param void
		@return bool �Ƿ���ʾ
		*/
		virtual bool GetShowText() = 0;
		/*
		@name SetShowIcon
		@desc �����Ƿ���ʾͼ��
		@param show  bool  �Ƿ���ʾ
		@return void
		*/
		virtual void SetShowIcon(bool show) = 0;
		/*
		@name GetShowIcon
		@desc ��ȡ�Ƿ���ʾͼ��
		@param void
		@return bool �Ƿ���ʾ
		*/
		virtual bool GetShowIcon() = 0;
		/*
		@name SetUncheckIcon
		@desc ����δѡ��ͼ��
		@param iconPath  const tchar*  ͼ��·��
		@return bool �Ƿ�ɹ�
		*/
		virtual bool SetUncheckIcon(const tchar* iconPath) = 0;
		/*
		@name GetUncheckIcon
		@desc ��ȡδѡ��ͼ��
		@param void
		@return const tchar* ͼ��·������·�����Ǿ���·����Ϊ��Դ����·��
		*/
		virtual const tchar* GetUncheckIcon() = 0;
		/*
		@name SetCheckedIcon
		@desc ����ѡ��ͼ��
		@param iconPath  const tchar*  ͼ��·��
		@return bool �Ƿ�ɹ�
		*/
		virtual bool SetCheckedIcon(const tchar* iconPath) = 0;
		/*
		@name GetCheckedIcon
		@desc ��ȡѡ��ͼ��
		@param void
		@return const tchar* ͼ��·������·�����Ǿ���·����Ϊ��Դ����·��
		*/
		virtual const tchar* GetCheckedIcon() = 0;
		/*
		@name SetUncheckHotIcon
		@desc ����δѡ�и���ͼ��
		@param iconPath  const tchar*  ͼ��·��
		@return bool �Ƿ�ɹ�
		*/
		virtual bool SetUncheckHotIcon(const tchar* iconPath) = 0;
		/*
		@name GetUncheckHotIcon
		@desc ��ȡδѡ�и���ͼ��
		@param void
		@return const tchar* ͼ��·������·�����Ǿ���·����Ϊ��Դ����·��
		*/
		virtual const tchar* GetUncheckHotIcon() = 0;
		/*
		@name SetCheckedHotIcon
		@desc ����ѡ�и���ͼ��
		@param iconPath  const tchar*  ͼ��·��
		@return bool �Ƿ�ɹ�
		*/
		virtual bool SetCheckedHotIcon(const tchar* iconPath) = 0;
		/*
		@name GetUncheckHotIcon
		@desc ��ȡѡ�и���ͼ��
		@param void
		@return const tchar* ͼ��·������·�����Ǿ���·����Ϊ��Դ����·��
		*/
		virtual const tchar* GetCheckedHotIcon() = 0;
		/*
		@name SetCheckedHotIcon
		@desc ���ý���ͼ��
		@param iconPath  const tchar*  ͼ��·��
		@return bool �Ƿ�ɹ�
		*/
		virtual bool SetDisableIcon(const tchar* iconPath) = 0;
		/*
		@name GetDisableIcon
		@desc ��ȡ����ͼ��
		@param void
		@return const tchar* ͼ��·������·�����Ǿ���·����Ϊ��Դ����·��
		*/
		virtual const tchar* GetDisableIcon() = 0;
		/*
		@name SetBackgroundStyle
		@desc ���ñ�����ʽ
		@param state  CBK_UIState  ״̬ö��
		@param style  IUIGearsTextStyle*  ��ʽָ��
		@return bool �Ƿ�ɹ�
		*/
		virtual bool SetBackgroundStyle(CBK_UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc ��ȡ������ʽ
		@param state  CBK_UIState  ״̬ö��
		@return IUIGearsRectStyle* ͼ��·����ʽָ��
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(CBK_UIState state) = 0;
		/*
		@name SetTextStyle
		@desc ����������ʽ
		@param state  CBK_UIState  ״̬ö��
		@param style  IUIGearsTextStyle*  ��ʽָ��
		@return bool �Ƿ�ɹ�
		*/
		virtual bool SetTextStyle(CBK_UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetTextStyle
		@desc ��ȡ������ʽ
		@param state  CBK_UIState  ״̬ö��
		@return IUIGearsTextStyle* ��ʽָ��
		*/
		virtual IUIGearsTextStyle* GetTextStyle(CBK_UIState state) = 0;
		/*
		@name SetIconHorAlign
		@desc ����ͼ��ˮƽ���뷽ʽ
		@param type  DockType  ���뷽ʽö��
		@return void
		~ 
		enum DockType
		{
		UIG_DOCK_LEFTTOP = 0,
		UIG_DOCK_CENTERMIDDLE,
		UIG_DOCK_RIGHTBOTTOM
		};
		~
		*/
		virtual void SetIconHorAlign(DockType type) = 0;
		/*
		@name GetIconHorAlign
		@desc ��ȡͼ��ˮƽ���뷽ʽ
		@param void
		@return DockType
		~
		enum DockType
		{
		UIG_DOCK_LEFTTOP = 0,
		UIG_DOCK_CENTERMIDDLE,
		UIG_DOCK_RIGHTBOTTOM
		};
		~
		*/
		virtual DockType GetIconHorAlign() = 0;
		/*
		@name SetIconVerAlign
		@desc ����ͼ�괹ֱ���뷽ʽ
		@param type  DockType  ���뷽ʽö��
		@return void
		~
		enum DockType
		{
		UIG_DOCK_LEFTTOP = 0,
		UIG_DOCK_CENTERMIDDLE,
		UIG_DOCK_RIGHTBOTTOM
		};
		~
		*/
		virtual void SetIconVerAlign(DockType type) = 0;
		/*
		@name GetIconVerAlign
		@desc ��ȡͼ�괹ֱ���뷽ʽ
		@param void
		@return DockType
		~
		enum DockType
		{
		UIG_DOCK_LEFTTOP = 0,
		UIG_DOCK_CENTERMIDDLE,
		UIG_DOCK_RIGHTBOTTOM
		};
		~
		*/
		virtual DockType GetIconVerAlign() = 0;
		/*
		@name SetIconOffsetX
		@desc ����ͼ��ˮƽƫ����
		@param x  int  ˮƽƫ����
		@return void
		*/
		virtual void SetIconOffsetX(int x) = 0;
		/*
		@name GetIconOffsetX
		@desc ��ȡͼ��ˮƽƫ����
		@param void
		@return int ˮƽƫ����
		*/
		virtual int GetIconOffsetX() = 0;
		/*
		@name SetIconOffsetY
		@desc ����ͼ�괹ֱƫ����
		@param x  int  ˮƽƫ����
		@return void
		*/
		virtual void SetIconOffsetY(int y) = 0;
		/*
		@name GetIconOffsetY
		@desc ��ȡͼ�괹ֱƫ����
		@param void
		@return int ��ֱƫ����
		*/
		virtual int GetIconOffsetY() = 0;
		/*
		@name SetAlignTextToLeft
		@desc ���������Ƿ������࿪ʼ������ʾ
		@param alignLeft bool �Ƿ������࿪ʼ������ʾ
		@return void
		*/
		virtual void SetAlignTextToLeft(bool alignLeft) = 0;
		/*
		@name GetAlignTextToLeft
		@desc ��ȡ�����Ƿ������࿪ʼ������ʾ
		@param void
		@return bool
		*/
		virtual bool GetAlignTextToLeft() = 0;

	};

	class IUIGRadioBox : public IUIGearsControl
	{
	public:
		/*
		@name IsSelected
		@desc �Ƿ�ѡ��
		@param void
		@return bool
		*/
		virtual bool IsSelected() = 0;
		/*
		@name SetSelected
		@desc �����Ƿ�ѡ��
		@param bSelected bool �Ƿ�ѡ��
		@return bool
		*/
		virtual void SetSelected(bool bSelected) = 0;
		/*
		@name GetId
		@desc ��ȡ����id
		@param void
		@return unsigned int
		*/
		virtual unsigned int GetId() = 0;
		/*
		@name SetId
		@desc ���÷���id
		@param id  int  unsigned int
		@return unsigned int
		*/
		virtual void SetId(unsigned int id) = 0;
		/*
		@name SetBackgroundStyle
		@desc ���ñ�����ʽ
		@param state CBK_UIState ״̬ö��
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		~
		enum CBK_UIState
		{
		UNCHECK_NORMAL = 0,
		UNCHECK_HOT,
		UNCHECK_PRESSED,
		UNCHECK_DISABLE,
		CHECKED_NORMAL,
		CHECKED_HOT,
		CHECKED_PRESSED,
		CHECKED_DISABLE
		};
		~
		*/
		virtual bool SetBackgroundStyle(CBK_UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc ��ȡ������ʽ
		@param state CBK_UIState ״̬ö��
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(CBK_UIState state) = 0;
		/*
		@name SetTextStyle
		@desc ����������ʽ
		@param state CBK_UIState ״̬ö��
		@param style IUIGearsTextStyle* ��ʽָ��
		@return bool
		~
		enum CBK_UIState
		{
		UNCHECK_NORMAL = 0,
		UNCHECK_HOT,
		UNCHECK_PRESSED,
		UNCHECK_DISABLE,
		CHECKED_NORMAL,
		CHECKED_HOT,
		CHECKED_PRESSED,
		CHECKED_DISABLE
		};
		~
		*/
		virtual bool SetTextStyle(CBK_UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetTextStyle
		@desc ��ȡ������ʽ
		@param state CBK_UIState ״̬ö��
		@return IUIGearsTextStyle*
		*/
		virtual IUIGearsTextStyle* GetTextStyle(CBK_UIState state) = 0;
		/*
		@name SetUnselectIcon
		@desc ����δѡ��ͼ��·��
		@param iconPath  const tchar*  ͼ��·��
		@return void
		*/
		virtual void SetUnselectIcon(const tchar* iconPath) = 0;
		/*
		@name GetUnselectIcon
		@desc ��ȡδѡ��ͼ��·��
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetUnselectIcon() = 0;
		/*
		@name SetSelectedIcon
		@desc ����ѡ��ͼ��·��
		@param  iconPath  const tchar*  ͼ��·��
		@return void
		*/
		virtual void SetSelectedIcon(const tchar* iconPath) = 0;
		/*
		@name GetSelectedIcon
		@desc ��ȡѡ��ͼ��·��
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetSelectedIcon() = 0;
		/*
		@name SetDisableIcon
		@desc ���ý���ͼ��·��
		@param  iconPath  const tchar*  ͼ��·��
		@return void
		*/
		virtual void SetDisableIcon(const tchar* iconPath) = 0;
		/*
		@name GetDisableIcon
		@desc ��ȡ����ͼ��·��
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetDisableIcon() = 0;
		/*
		@name SetShowText
		@desc �����Ƿ���ʾ�ı�
		@param show bool �Ƿ���ʾ
		@return void
		*/
		virtual void SetShowText(bool show) = 0;
		/*
		@name GetShowText
		@desc ��ȡ�Ƿ���ʾ�ı�
		@param void
		@return bool
		*/
		virtual bool GetShowText() = 0;
		/*
		@name SetShowIcon
		@desc ��ȡ�Ƿ���ʾͼ��
		@param show bool �Ƿ���ʾ
		@return void
		*/
		virtual void SetShowIcon(bool show) = 0;
		/*
		@name GetShowIcon
		@desc ��ȡ�Ƿ���ʾͼ��
		@param void
		@return bool
		*/
		virtual bool GetShowIcon() = 0;
		/*
		@name SetText
		@desc �����ı�
		@param text  const tchar*  �ı�����
		@return void
		*/
		virtual void SetText(const tchar* text) = 0;
		/*
		@name GetText
		@desc ��ȡ�ı�
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetText() = 0;
		/*
		@name SetIconHorAlign
		@desc ����ͼ��ˮƽ��������
		@param type DockType ��������
		@return void
		~
		enum DockType
		{
		UIG_DOCK_LEFTTOP = 0,
		UIG_DOCK_CENTERMIDDLE,
		UIG_DOCK_RIGHTBOTTOM
		};
		~
		*/
		virtual void SetIconHorAlign(DockType type) = 0;
		/*
		@name GetIconHorAlign
		@desc ��ȡͼ��ˮƽ��������
		@param void
		@return DockType
		*/
		virtual DockType GetIconHorAlign() = 0;
		/*
		@name SetIconVerAlign
		@desc ����ͼ�괹ֱ��������
		@param type DockType ��������
		@return void
		~
		enum DockType
		{
		UIG_DOCK_LEFTTOP = 0,
		UIG_DOCK_CENTERMIDDLE,
		UIG_DOCK_RIGHTBOTTOM
		};
		~
		*/
		virtual void SetIconVerAlign(DockType type) = 0;
		/*
		@name GetIconVerAlign
		@desc ��ȡͼ�괹ֱ��������
		@param void
		@return DockType
		*/
		virtual DockType GetIconVerAlign() = 0;
		/*
		@name SetIconOffsetX
		@desc ����ͼ��ˮƽƫ����
		@param x int ƫ����
		@return void
		*/
		virtual void SetIconOffsetX(int x) = 0;
		/*
		@name GetIconOffsetX
		@desc ��ȡͼ��ˮƽƫ����
		@param void
		@return int
		*/
		virtual int GetIconOffsetX() = 0;
		/*
		@name SetIconOffsetX
		@desc ����ͼ�괹ֱƫ����
		@param x int ƫ����
		@return void
		*/
		virtual void SetIconOffsetY(int y) = 0;
		/*
		@name GetIconOffsetX
		@desc ��ȡͼ�괹ֱƫ����
		@param void
		@return int
		*/
		virtual int GetIconOffsetY() = 0;
		/*
		@name SetIconOffsetX
		@desc ����ͼ���Ƿ��������ʾ
		@param alignLeft bool �Ƿ��������ʾ
		@return void
		*/
		virtual void SetAlignTextToLeft(bool alignLeft) = 0;
		/*
		@name GetAlignTextToLeft
		@desc ��ȡͼ���Ƿ��������ʾ
		@param void
		@return bool
		*/
		virtual bool GetAlignTextToLeft() = 0;
	};

	class IUIGPicture : public IUIGearsControl
	{
	public:
		/*
		@name SetImage
		@desc ������ʾ��ͼƬ·��
		@param path  const tchar*  ͼƬ·��
		@return void
		*/
		virtual void SetImage(const tchar* path) = 0;
		/*
		@name SetImage
		@desc ������ʾ��ͼƬ·�������ͷ�ǰһ��ͼƬ
		@param path  const tchar*  ͼƬ·��
		@param bDeletePreviousImage  bool  �Ƿ��ͷ�ǰһ��ͼƬ
		@return void
		*/
		virtual void SetImage(const tchar* path, bool bDeletePreviousImage) = 0;
		/*
		@name SetImage
		@desc ͨ�����������ݣ�������ʾ��ͼƬ��ֻ֧��pngͼƬ������
		@param imageName  const tchar*  ͼƬ����
		@param imageBuffer  void*  ������
		@param length  unsigned int  ���ݳ���
		@return bool
		*/
		virtual bool SetImage(const tchar* imageName, void* imageBuffer, unsigned int length) = 0;
		/*
		@name GetImage
		@desc ��ȡ��ʾ��ͼƬ·��
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetImage() = 0;
		/*
		@name SetFillImage
		@desc ������ʾ��ͼƬ�Ƿ����������ʾ
		@param bFill bool �Ƿ�����
		@return void
		*/
		virtual void SetFillImage(bool bFill) = 0;
		/*
		@name GetFillImage
		@desc ��ȡ��ʾ��ͼƬ�Ƿ����������ʾ
		@param void
		@return bool
		*/
		virtual bool GetFillImage() = 0;
		/*
		@name SetUserImage
		@desc ������ʾ�û�λͼ����Ҫ�ⲿ�ͷ�
		@param hBitmap HBITMAP �û�λͼ
		@return void
		*/
		virtual void SetUserImage(HBITMAP hBitmap) = 0;
		/*
		@name GetUserImage
		@desc ��ȡ�û�λͼ
		@param void
		@return HBITMAP
		*/
		virtual HBITMAP GetUserImage() = 0;
	};

	class IUIGearsDial : public IUIGearsControl
	{
	public:
		virtual void SetVerAngle(float angle) = 0;
		virtual void SetHorAngle(float angle) = 0;

		virtual float GetVerAngle() = 0;
		virtual float GetHorAngle() = 0;
	};

	class IUIGSlider : public IUIGearsControl
	{
	public:
		/*
		@name SetValue
		@desc ���õ�ǰֵ
		@param pos int ��ǰֵ
		@return void
		*/
		virtual void SetValue(int pos) = 0;
		/*
		@name GetValue
		@desc ��ȡ��ǰֵ
		@param void
		@return int
		*/
		virtual int GetValue() = 0;
		/*
		@name SetRange
		@desc �����϶���Χֵ
		@param min int ��Сֵ
		@param max int ���ֵ
		@return void
		*/
		virtual void SetRange(int min, int max) = 0;
		/*
		@name GetRange
		@desc ��ȡ�϶���Χֵ
		@param min int& ��Сֵ
		@param max int& ���ֵ
		@return void
		*/
		virtual void GetRange(int& min, int& max) = 0;
		/*
		@name SetIsHor
		@desc �����Ƿ�ˮƽ��ʾ
		@param isHor bool �Ƿ�ˮƽ��ʾ
		@return void
		*/
		virtual void SetIsHor(bool isHor) = 0;
		/*
		@name GetIsHor
		@desc ��ȡ�Ƿ�ˮƽ��ʾ
		@param void
		@return bool
		*/
		virtual bool GetIsHor() = 0;
		/*
		@name SetThumbSize
		@desc ���û����С
		@param w int ���
		@param h int �߶�
		@return void
		*/
		virtual void SetThumbSize(int w, int h) = 0;
		/*
		@name GetThumbSize
		@desc ��ȡ�����С
		@param w int& ���
		@param h int& �߶�
		@return void
		*/
		virtual void GetThumbSize(int& w, int& h) = 0;
		/*
		@name SetChannelSize
		@desc ���û��۴�С
		@param size int ��С
		@return void
		*/
		virtual void SetChannelSize(int size) = 0;
		/*
		@name GetChannelSize
		@desc ��ȡ���۴�С
		@param void
		@return int
		*/
		virtual int GetChannelSize() = 0;
		/*
		@name SetBackgroundStyle
		@desc ���ñ�����ʽ
		@param state UICommonState ״̬ö��
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetBackgroundStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc ��ȡ������ʽ
		@param state UICommonState ״̬ö��
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UICommonState state) = 0;
		/*
		@name SetFrontStyle
		@desc ����ǰ����ʽ
		@param state UICommonState ״̬ö��
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetFrontStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetFrontStyle
		@desc ��ȡǰ����ʽ
		@param state UICommonState ״̬ö��
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetFrontStyle(UICommonState state) = 0;
		/*
		@name SetThumbStyle
		@desc ���û�����ʽ
		@param state UICommonState ״̬ö��
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetThumbStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetThumbStyle
		@desc ��ȡ������ʽ
		@param state UICommonState ״̬ö��
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetThumbStyle(UIState state) = 0;
	};

	class IUIGProgressBar : public IUIGearsControl
	{
	public:
		/*
		@name SetValue
		@desc ���õ�ǰ����ֵ
		@param pos int ����ֵ
		@return void
		*/
		virtual void SetValue(int pos) = 0;
		/*
		@name GetValue
		@desc ��ȡ��ǰ����ֵ
		@param void
		@return int
		*/
		virtual int GetValue() = 0;
		/*
		@name SetChannelSize
		@desc ���û��۴�С
		@param size int ���۴�С
		@return void
		*/
		virtual void SetChannelSize(int size) = 0;
		/*
		@name GetChannelSize
		@desc ��ȡ���۴�С
		@param void
		@return int
		*/
		virtual int GetChannelSize() = 0;
		/*
		@name SetRange
		@desc ���ý��ȷ�Χ
		@param min int ��С����ֵ
		@param max int ������ֵ
		@return void
		*/
		virtual void SetRange(int min, int max) = 0;
		/*
		@name GetRange
		@desc ��ȡ���ȷ�Χ
		@param min int& ��С����ֵ
		@param max int& ������ֵ
		@return void
		*/
		virtual void GetRange(int& min, int& max) = 0;
		/*
		@name SetIsHor
		@desc �����Ƿ���ˮƽ������
		@param isHor bool �Ƿ�ˮƽ��ʾ
		@return void
		*/
		virtual void SetIsHor(bool isHor) = 0;
		/*
		@name GetIsHor
		@desc ��ȡ�Ƿ���ˮƽ������
		@param void
		@return bool
		*/
		virtual bool GetIsHor() = 0;
		/*
		@name SetShowText
		@desc �����Ƿ���ʾ����
		@param show bool �Ƿ���ʾ����
		@return void
		*/
		virtual void SetShowText(bool show) = 0;
		/*
		@name GetShowText
		@desc ��ȡ�Ƿ���ʾ����
		@param void
		@return bool
		*/
		virtual bool GetShowText() = 0;
		/*
		@name SetNoStretchFront
		@desc ����ǰ���Ƿ�ü���ʾ��������Ҳ���ǲü���ʾ
		@param noStretch bool �Ƿ�ü���ʾ
		@return void
		*/
		virtual void SetNoStretchFront(bool noStretch) = 0;
		/*
		@name GetNoStretchFront
		@desc ��ȡǰ���Ƿ�ü���ʾ
		@param void
		@return bool
		*/
		virtual bool GetNoStretchFront() = 0;
		/*
		@name SetBackgroundStyle
		@desc ���ñ�����ʽ
		@param state UICommonState ״̬��ʽö��
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetBackgroundStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc ��ȡ������ʽ
		@param state UICommonState ״̬��ʽö��
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UICommonState state) = 0;
		/*
		@name SetFrontStyle
		@desc ����ǰ����ʽ
		@param state UICommonState ״̬��ʽö��
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetFrontStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetFrontStyle
		@desc ��ȡ������ʽ
		@param state UICommonState ״̬��ʽö��
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetFrontStyle(UICommonState state) = 0;
		/*
		@name SetTextStyle
		@desc ����������ʽ
		@param state UICommonState ״̬��ʽö��
		@param style IUIGearsTextStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetTextStyle(UICommonState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetTextStyle
		@desc ��ȡ������ʽ
		@param state UICommonState ״̬��ʽö��
		@return IUIGearsTextStyle*
		*/
		virtual IUIGearsTextStyle* GetTextStyle(UICommonState state) = 0;

	};

	class IUIGList : public IUIGearsControl
	{
	public:
		/*
		@name AddItem
		@desc ���item
		@param text  const tchar*  item�ı�����
		@return bool
		*/
		virtual bool AddItem(const tchar* text) = 0;
		/*
		@name InsertItem
		@desc ����item
		@param index int ��������λ�ã���0��ʼ
		@param text  const tchar*  item�ı�����
		@return bool
		*/
		virtual bool InsertItem(int index, const tchar* text) = 0;
		/*
		@name SetItemTooltip
		@desc ����item��tooltip�ı�
		@param index int ����λ�ã���0��ʼ
		@param text  const tchar*  tooltip�ı�����
		@return bool
		*/
		virtual bool SetItemTooltip(int index, const tchar* text) = 0;
		/*
		@name GetItemTooltip
		@desc ��ȡitem��tooltip�ı�
		@param index int ����λ�ã���0��ʼ
		@return const tchar*
		*/
		virtual const tchar* GetItemTooltip(int index) = 0;
		/*
		@name AddItemWithData
		@desc ���Item������һ���û�����
		@param text  const tchar*  item�ı�
		@param data PARAM �û�����
		@return bool
		*/
		virtual bool AddItemWithData(const tchar* text, PARAM data) = 0;
		/*
		@name RemoveAll
		@desc ɾ�����е�item
		@param void
		@return void
		*/
		virtual void RemoveAll() = 0;
		/*
		@name RemoveItem
		@desc ���������Ƴ�item
		@param index int ������
		@return bool
		*/
		virtual bool RemoveItem(int index) = 0;
		/*
		@name SetItemIcon
		@desc ����item��ͼ��
		@param index int ������
		@param iconPath  const tchar*  ͼ����Դ·��������Դ���е�·��
		@return bool
		*/
		virtual bool SetItemIcon(int index, const tchar* iconPath) = 0;
		/*
		@name GetItemIcon
		@desc ��ȡitem��ͼ��
		@param index int ������
		@return const tchar* ͼ����Դ·��������Դ���е�·��
		*/
		virtual const tchar* GetItemIcon(int index) = 0;
		/*
		@name GetSelectedIndex
		@desc ��ȡѡ������
		@param void
		@return int
		*/
		virtual int GetSelectedIndex() = 0;
		/*
		@name SetSelectedIndex
		@desc ����ѡ�����������Ϊ-1���ʾ�������ѡ��
		@param index int ������
		@return void
		*/
		virtual void SetSelectedIndex(int index) = 0;
		/*
		@name GetItemText
		@desc ��ȡitem��������
		@param index int ������
		@return const tchar*
		*/
		virtual const tchar* GetItemText(int index) = 0;
		/*
		@name SetItemText
		@desc ����item��������
		@param index int ������
		@param text  const tchar*  ��������
		@return bool
		*/
		virtual bool SetItemText(int index, const tchar* text) = 0;
		/*
		@name SetVerticalScrollBar
		@desc �󶨴�ֱ������
		@param pScrollBar IUIGearsControl* �������ؼ�ָ��
		@return void
		*/
		virtual void SetVerticalScrollBar(IUIGearsControl* pScrollbar) = 0;
		/*
		@name SetHorizontalScrollBar
		@desc ��ˮƽ������
		@param pScrollBar IUIGearsControl* �������ؼ�ָ��
		@return void
		*/
		virtual void SetHorizontalScrollBar(IUIGearsControl* pScrollbar) = 0;
		/*
		@name SetMultiSelect
		@desc �����Ƿ�֧�ֶ�ѡ
		@param multiSelect bool �Ƿ�֧�ֶ�ѡ
		@return void
		*/
		virtual void SetMultiSelect(bool multiSelect) = 0;
		/*
		@name GetMultiSelect
		@desc ��ȡ�Ƿ�֧�ֶ�ѡ
		@param void
		@return bool
		*/
		virtual bool GetMultiSelect() = 0;
		/*
		@name SetDragSelect
		@desc �����Ƿ����קѡ��ѡ��
		@param dragSelect bool ��קѡ��
		@return void
		*/
		virtual void SetDragSelect(bool dragSelect) = 0;
		/*
		@name GetDragSelect
		@desc ��ȡ�Ƿ����קѡ��ѡ��
		@param void
		@return bool
		*/
		virtual bool GetDragSelect() = 0;
		/*
		@name IsSelected
		@desc �Ƿ�ѡ��ĳ��
		@param index int ����
		@return bool
		*/
		virtual bool IsSelected(int index) = 0;
		/*
		@name GetMultiSelectedItems
		@desc ��ȡ��ѡ��ѡ��
		@param void
		@return std::vector<int> �����б�
		*/
		virtual	std::vector<int> GetMultiSelectedItems() = 0;
		virtual void UpdateData(int index) = 0;
		/*
		@name GetItemCount
		@desc ��ȡitem����
		@param void
		@return int
		*/
		virtual int GetItemCount() = 0;
		/*
		@name SetItemHeight
		@desc ����item�߶�
		@param height int item�߶�
		@return void
		*/
		virtual void SetItemHeight(int height) = 0;
		/*
		@name GetItemHeight
		@desc ��ȡitem�߶�
		@param void
		@return int
		*/
		virtual int GetItemHeight() = 0;
		/*
		@name SetShowIcon
		@desc �����Ƿ���ʾͼ��
		@param show bool ��ʾͼ��
		@return void
		*/
		virtual void SetShowIcon(bool show) = 0;
		/*
		@name GetShowIcon
		@desc ��ѯ�Ƿ���ʾͼ��
		@param void
		@return bool
		*/
		virtual bool GetShowIcon() = 0;
		/*
		@name SetIconOffset
		@desc ����ͼ������ƫ����
		@param offset int ƫ����
		@return void
		*/
		virtual void SetIconOffset(int offset) = 0;
		/*
		@name GetIconOffset
		@desc ��ȡͼ������ƫ����
		@param void
		@return int
		*/
		virtual int GetIconOffset() = 0;
		/*
		@name SetDrawBorder
		@desc �����Ƿ���Ʊ߿�
		@param show bool �Ƿ���Ʊ߿�
		@return void
		*/
		virtual void SetDrawBorder(bool show) = 0;
		/*
		@name GetDrawBorder
		@desc ��ȡ�Ƿ���Ʊ߿�
		@param void
		@return bool
		*/
		virtual bool GetDrawBorder() = 0;
		/*
		@name SetBorderColor
		@desc ���ñ߿���ɫ
		@param color int ��ɫֵ����0xffff0000
		@return void
		*/
		virtual void SetBorderColor(int color) = 0;
		/*
		@name GetBorderColor
		@desc ��ȡ�߿���ɫ
		@param void
		@return int
		*/
		virtual int GetBorderColor() = 0;
		/*
		@name SetBorderSize
		@desc ���ñ߿��ϸ
		@param size int ��ϸ
		@return void
		*/
		virtual void SetBorderSize(int size) = 0;
		/*
		@name GetBorderSize
		@desc ��ȡ�߿��ϸ
		@param void
		@return int
		*/
		virtual int GetBorderSize() = 0;
		/*
		@name SetCanCancelSelected
		@desc �����Ƿ���Ե���հ�λ��ȡ��ѡ��
		@param cancelSelected bool �Ƿ�����ȡ��ѡ��
		@return void
		*/
		virtual void SetCanCancelSelected(bool cancelSelected) = 0;
		/*
		@name GetCanCancelSelected
		@desc ��ѯ�Ƿ���Ե���հ�λ��ȡ��ѡ��
		@param void
		@return bool
		*/
		virtual bool GetCanCancelSelected() = 0;
		/*
		@name SetBackgroundStyle
		@desc ���ñ�����ʽ
		@param state UICommonState ״̬����
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetBackgroundStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc ��ѯ������ʽ
		@param state UICommonState ״̬����
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UICommonState state) = 0;
		/*
		@name SetItemStyle
		@desc ����Item������ʽ
		@param state UICommonState ״̬����
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetItemStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetItemStyle
		@desc ��ѯItem������ʽ
		@param state UICommonState ״̬����
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetItemStyle(UIState state) = 0;
		/*
		@name SetTextStyle
		@desc ����Item������ʽ
		@param state UICommonState ״̬����
		@param style IUIGearsTextStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetTextStyle
		@desc ��ѯItem������ʽ
		@param state UICommonState ״̬����
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsTextStyle* GetTextStyle(UIState state) = 0;
		/*
		@name GetLMouseUpSelected
		@desc ��ȡ�Ƿ����̧��ѡ��Ĭ���ǰ���ѡ��
		@param void
		@return bool
		*/
		virtual bool GetLMouseUpSelected() = 0;
		/*
		@name SetLMouseUpSelected
		@desc �����Ƿ����̧��ѡ��Ĭ���ǰ���ѡ��
		@param enable bool �Ƿ��
		@return void
		*/
		virtual void SetLMouseUpSelected(bool enable) = 0;
		/*
		@name SetEnableDragItem
		@desc �����Ƿ�������קitem���򿪺�������ק�¼�
		@param enable bool �Ƿ��
		@return void
		*/
		virtual void SetEnableDragItem(bool enable) = 0;
		/*
		@name SetEnableDragItem
		@desc ��ѯ�Ƿ�������קitem���򿪺�������ק�¼�
		@param void
		@return bool
		*/
		virtual bool GetEnableDragItem() = 0;
		/*
		@name SetItemData
		@desc ����item���û�����
		@param index int ������
		@param data void* �û�����
		@return bool
		*/
		virtual bool SetItemData(int index, void* data) = 0;
		/*
		@name GetItemData
		@desc ��ȡitem���û�����
		@param index int ������
		@return void*
		*/
		virtual void*	GetItemData(int index) = 0;
		/*
		@name SetItemMode
		@desc ����item����ʾģʽ
		@param mode ItemMode ��ʾģʽ
		@return void
		*/
		virtual void SetItemMode(ItemMode mode) = 0;
		/*
		@name GetItemMode
		@desc ��ȡitem����ʾģʽ
		@param void
		@return ItemMode
		*/
		virtual ItemMode GetItemMode() = 0;
		/*
		@name SetItemWidth
		@desc ����item�Ŀ��
		@param width  int  unsigned int
		@return void
		*/
		virtual void SetItemWidth(unsigned int width) = 0;
		/*
		@name GetItemWidth
		@desc ��ȡitem�Ŀ��
		@param void
		@return int
		*/
		virtual unsigned int GetItemWidth() = 0;
	};

	class IUIGMenuList : public IUIGearsControl
	{
	public:
		virtual bool AddItem(const tchar* text) = 0;
		virtual bool AddItemWithData(const tchar* text, PARAM data) = 0;
		virtual bool InsertButtonItem(int id, const tchar* text, const tchar* icon, const tchar* shortcut, int pos = -1) = 0;
		virtual bool InsertSperator(int pos = -1) = 0;
		virtual bool InsertRadioItem(int id, const tchar* text, int groupId, const tchar* shortcut, int pos = -1) = 0;
		virtual bool InsertCheckItem(int id, const tchar* text, const tchar* shortcut, int pos = -1) = 0;
		virtual bool ModifyItem(int pos, int id, const tchar* text, const tchar* icon, const tchar* shortcut, UIGears::UIGMenuType type = UIGears::UIG_MENU_KEEPSAME, int groupid = -1) = 0;
		virtual void RemoveAll() = 0;
		virtual bool RemoveItem(int index) = 0;
		virtual bool SetItemIcon(int index, const tchar* iconPath) = 0;
		virtual const tchar* GetItemIcon(int index) = 0;
		virtual int GetSelectedIndex() = 0;
		virtual void SetSelectedIndex(int index) = 0;
		virtual const tchar* GetItemText(int index) = 0;
		virtual bool IsSelected(int index) = 0;
		virtual void UpdateData(int index) = 0;
		virtual int GetItemCount() = 0;
		virtual void SetItemHeight(int height) = 0;
		virtual int GetItemHeight() = 0;
		virtual void SetShowIcon(bool show) = 0;
		virtual bool GetShowIcon() = 0;
		virtual void SetIconOffset(int offset) = 0;
		virtual int GetIconOffset() = 0;
		virtual void SetDrawBorder(bool show) = 0;
		virtual bool GetDrawBorder() = 0;
		virtual void SetBorderColor(int color) = 0;
		virtual int GetBorderColor() = 0;
		virtual void SetBorderSize(int size) = 0;
		virtual int GetBorderSize() = 0;
		virtual void SetCanCancelSelected(bool cancelSelected) = 0;
		virtual bool GetCanCancelSelected() = 0;
		virtual bool SetBackgroundStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		virtual IUIGearsRectStyle* GetBackgroundStyle(UICommonState state) = 0;
		virtual bool SetItemStyle(UIState state, IUIGearsRectStyle* style) = 0;
		virtual IUIGearsRectStyle* GetItemStyle(UIState state) = 0;
		virtual bool SetTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		virtual IUIGearsTextStyle* GetTextStyle(UIState state) = 0;
		virtual bool SetItemData(int index, void* data) = 0;
		virtual void*	GetItemData(int index) = 0;
		virtual void ClearArrawInfo() = 0;
		virtual void SetShowArraw(int index) = 0;
		virtual void SetLMouseUpSelected(bool enable) = 0;
		virtual bool GetLMouseUpSelected() = 0;
		virtual void OnMouseMove(int flag, short x, short y) = 0;
		virtual void OnLMouseDown(int flag, short x, short y) = 0;
		virtual void OnLMouseUp(int flag, short x, short y) = 0;
		virtual bool SetChecked(int index, bool checked) = 0;
	};

	typedef void* TreeNode;
	typedef void* MenuItem;

	class IUIGTemplateList : public IUIGearsControl
	{
	public:
		/*
		@name AddItem
		@desc ���item
		@param text  const tchar*  item�ı�����
		@return bool
		*/
		virtual bool AddItem(const tchar* text) = 0;
		/*
		@name RemoveAll
		@desc ɾ�����е�item
		@param void
		@return void
		*/
		virtual void RemoveAll() = 0;
		/*
		@name RemoveItem
		@desc ���������Ƴ�item
		@param index int ������
		@return bool
		*/
		virtual bool RemoveItem(int index) = 0;
		/*
		@name GetSelectedIndex
		@desc ��ȡѡ������
		@param void
		@return int
		*/
		virtual int GetSelectedIndex() = 0;
		/*
		@name SetSelectedIndex
		@desc ����ѡ�����������Ϊ-1���ʾ�������ѡ��
		@param index int ������
		@return void
		*/
		virtual void SetSelectedIndex(int index) = 0;
		/*
		@name SetTemplateName
		@desc ����itemģ��ؼ�����
		@param name  const tchar*  ģ��ؼ�����
		@return void
		*/
		virtual void SetTemplateName(const tchar*name) = 0;
		/*
		@name GetTemplateName
		@desc ��ȡģ��ؼ�����
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetTemplateName() = 0;
		/*
		@name SetVerticalScrollBar
		@desc �󶨴�ֱ������
		@param pScrollBar IUIGearsControl* �������ؼ�ָ��
		@return void
		*/
		virtual void SetVerticalScrollBar(IUIGearsControl* pScrollbar) = 0;
		/*
		@name SetHorizontalScrollBar
		@desc ��ˮƽ������
		@param pScrollBar IUIGearsControl* �������ؼ�ָ��
		@return void
		*/
		virtual void SetHorizontalScrollBar(IUIGearsControl* pScrollbar) = 0;
		/*
		@name SetMultiSelect
		@desc �����Ƿ�֧�ֶ�ѡ
		@param multiSelect bool �Ƿ�֧�ֶ�ѡ
		@return void
		*/
		virtual void SetMultiSelect(bool multiSelect) = 0;
		/*
		@name IsSelected
		@desc �Ƿ�ѡ��ĳ��
		@param index int ����
		@return bool
		*/
		virtual bool IsSelected(int index) = 0;
		/*
		@name GetMultiSelectedItems
		@desc ��ȡ��ѡ��ѡ��
		@param void
		@return std::vector<int> �����б�
		*/
		virtual	std::vector<int> GetMultiSelectedItems() = 0;
		/*
		@name UpdateData
		@desc ǿ�Ƹ���ĳһ����Զ����͸����¼�
		@param index int ������
		@return void
		*/
		virtual void UpdateData(int index) = 0;
		/*
		@name GetItemCount
		@desc ��ȡitem����
		@param void
		@return int
		*/
		virtual int GetItemCount() = 0;
		/*
		@name RefreshData
		@desc ˢ�������б�����ݣ����Զ����͸����¼�
		@param void
		@return void
		*/
		virtual void RefreshData() = 0;
		/*
		@name SetItemHeight
		@desc ����item�߶�
		@param height int item�߶�
		@return void
		*/
		virtual void SetItemHeight(int height) = 0;
		/*
		@name GetItemHeight
		@desc ��ȡitem�߶�
		@param void
		@return int
		*/
		virtual int GetItemHeight() = 0;
		/*
		@name SetDrawBorder
		@desc �����Ƿ���Ʊ߿�
		@param show bool �Ƿ���Ʊ߿�
		@return void
		*/
		virtual void SetDrawBorder(bool show) = 0;
		/*
		@name GetDrawBorder
		@desc ��ȡ�Ƿ���Ʊ߿�
		@param void
		@return bool
		*/
		virtual bool GetDrawBorder() = 0;
		/*
		@name SetBorderColor
		@desc ���ñ߿���ɫ
		@param color int ��ɫֵ����0xffff0000
		@return void
		*/
		virtual void SetBorderColor(int color) = 0;
		/*
		@name GetBorderColor
		@desc ��ȡ�߿���ɫ
		@param void
		@return int
		*/
		virtual int GetBorderColor() = 0;
		/*
		@name SetBorderSize
		@desc ���ñ߿��ϸ
		@param size int ��ϸ
		@return void
		*/
		virtual void SetBorderSize(int size) = 0;
		/*
		@name GetBorderSize
		@desc ��ȡ�߿��ϸ
		@param void
		@return int
		*/
		virtual int GetBorderSize() = 0;
		/*
		@name SetCanCancelSelected
		@desc �����Ƿ���Ե���հ�λ��ȡ��ѡ��
		@param cancelSelected bool �Ƿ�����ȡ��ѡ��
		@return void
		*/
		virtual void SetCanCancelSelected(bool cancelSelected) = 0;
		/*
		@name GetCanCancelSelected
		@desc ��ѯ�Ƿ���Ե���հ�λ��ȡ��ѡ��
		@param void
		@return bool
		*/
		virtual bool GetCanCancelSelected() = 0;
		/*
		@name SetBackgroundStyle
		@desc ���ñ�����ʽ
		@param state UICommonState ״̬����
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetBackgroundStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc ��ѯ������ʽ
		@param state UICommonState ״̬����
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UICommonState state) = 0;
		/*
		@name SetItemStyle
		@desc ����Item������ʽ
		@param state UICommonState ״̬����
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetItemStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetItemStyle
		@desc ��ѯItem������ʽ
		@param state UICommonState ״̬����
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetItemStyle(UIState state) = 0;
		/*
		@name SetTextStyle
		@desc ����Item������ʽ
		@param state UICommonState ״̬����
		@param style IUIGearsTextStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetTextStyle
		@desc ��ѯItem������ʽ
		@param state UICommonState ״̬����
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsTextStyle* GetTextStyle(UIState state) = 0;
		/*
		@name SetEnableDragItem
		@desc �����Ƿ�������קitem���򿪺�������ק�¼�
		@param enable bool �Ƿ��
		@return void
		*/
		virtual void SetEnableDragItem(bool enable) = 0;
		/*
		@name SetEnableDragItem
		@desc ��ѯ�Ƿ�������קitem���򿪺�������ק�¼�
		@param void
		@return bool
		*/
		virtual bool GetEnableDragItem() = 0;
		/*
		@name SetItemData
		@desc ����item���û�����
		@param index int ������
		@param data void* �û�����
		@return bool
		*/
		virtual bool SetItemData(int index, void* data) = 0;
		/*
		@name GetItemData
		@desc ��ȡitem���û�����
		@param index int ������
		@return void*
		*/
		virtual void* GetItemData(int index) = 0;
		/*
		@name SetItemMode
		@desc ����item����ʾģʽ
		@param mode ItemMode ��ʾģʽ
		@return void
		*/
		virtual void SetItemMode(ItemMode mode) = 0;
		/*
		@name GetItemMode
		@desc ��ȡitem����ʾģʽ
		@param void
		@return ItemMode
		*/
		virtual ItemMode GetItemMode() = 0;
		/*
		@name SetItemWidth
		@desc ����item�Ŀ��
		@param width  int  unsigned int
		@return void
		*/
		virtual void SetItemWidth(unsigned int width) = 0;
		/*
		@name GetItemWidth
		@desc ��ȡitem�Ŀ��
		@param void
		@return int
		*/
		virtual unsigned int GetItemWidth() = 0;
	};

	class IUIGScrollBar : public IUIGearsControl
	{
	public:
		virtual void SetOwnerCtrl(IScrollOwner* scollowner) = 0;
		/*
		@name SetScrollInfo
		@desc ���ù�����Χ
		@param docHeight  unsigned int  ������Ҫ��ʾ�ĸ߶Ȼ��߿��
		@param visibleHeight  unsigned int  �ɼ��߶Ȼ��߿��
		@return void
		*/
		virtual void SetScrollInfo(unsigned int  docHeight, unsigned int  visibleHeight) = 0;
		/*
		@name GetScrollPos
		@desc ��ȡ��ǰ����λ��
		@param void
		@return int
		*/
		virtual unsigned int GetScrollPos() = 0;
		/*
		@name SetScrollPos
		@desc ���õ�ǰ����λ��
		@param pos  unsigned int  ����λ��
		@return void
		*/
		virtual void SetScrollPos(unsigned int pos) = 0;
		/*
		@name SetIsHor
		@desc �����Ƿ���ˮƽ������
		@param isHor bool ˮƽ������
		@return void
		*/
		virtual void SetIsHor(bool isHor) = 0;
		/*
		@name GetIsHor
		@desc ��ȡ�Ƿ���ˮƽ������
		@param void
		@return bool
		*/
		virtual bool GetIsHor() = 0;
		/*
		@name SetBackgroundStyle
		@desc ���ñ�����ʽ
		@param state UICommonState ״̬����
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetBackgroundStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc ��ѯ������ʽ
		@param state UICommonState ״̬����
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UICommonState state) = 0;
		/*
		@name SetUpBtnStyle
		@desc �����ϰ�ť��ʽ
		@param state UICommonState ״̬����
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetUpBtnStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetUpBtnStyle
		@desc ��ѯ�ϰ�ť��ʽ
		@param state UICommonState ״̬����
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetUpBtnStyle(UIState state) = 0;
		/*
		@name SetDownBtnStyle
		@desc �����°�ť��ʽ
		@param state UICommonState ״̬����
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetDownBtnStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetDownBtnStyle
		@desc ��ѯ�°�ť��ʽ
		@param state UICommonState ״̬����
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetDownBtnStyle(UIState state) = 0;
		/*
		@name SetThumbBtnStyle
		@desc ���û�����ʽ
		@param state UICommonState ״̬����
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetThumbBtnStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetThumbBtnStyle
		@desc ��ѯ������ʽ
		@param state UICommonState ״̬����
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetThumbBtnStyle(UIState state) = 0;
		/*
		@name SetBtnSize
		@desc ���û����С
		@param size int �����С
		@return void
		*/
		virtual	void SetBtnSize(int size) = 0;
		/*
		@name GetBtnSize
		@desc ��ѯ�����С
		@param void
		@return int
		*/
		virtual int GetBtnSize() = 0;
		/*
		@name SetUpBtnIcon
		@desc �����ϰ�ťͼ��
		@param path  const tchar*  ͼ����Դ·��
		@return void
		*/
		virtual void SetUpBtnIcon(const tchar* path) = 0;
		/*
		@name GetUpBtnIcon
		@desc ��ѯ�ϰ�ťͼ��
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetUpBtnIcon() = 0;
		/*
		@name SetDownBtnIcon
		@desc �����°�ťͼ��
		@param path  const tchar*  ͼ����Դ·��
		@return void
		*/
		virtual void SetDownBtnIcon(const tchar* path) = 0;
		/*
		@name GetDownBtnIcon
		@desc ��ѯ�°�ťͼ��
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetDownBtnIcon() = 0;
		/*
		@name SetThumbIcon
		@desc ���û���ͼ��
		@param path  const tchar*  ͼ����Դ·��
		@return void
		*/
		virtual void SetThumbIcon(const tchar* path) = 0;
		/*
		@name GetThumbIcon
		@desc ��ѯ����ͼ��
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetThumbIcon() = 0;
	};

	class IUIGContainer : public IUIGearsControl
	{
	public:
		/*
		@name GetBackColor
		@desc ��ȡ������ɫ
		@param void
		@return unsigned int
		*/
		virtual unsigned int GetBackColor() = 0;
		/*
		@name SetBackColor
		@desc ���ñ�����ɫ
		@param color  unsigned int  ������ɫ
		@return bool
		*/
		virtual bool SetBackColor(unsigned int color) = 0;
		/*
		@name AttchChildControl
		@desc ���Ӵ���
		@param ctrlHandle void �Ӵ��ھ��
		@return void
		*/
		virtual void AttchChildControl(void* ctrlHandle) = 0;
		/*
		@name SetBackImage
		@desc ���ñ���ͼƬ
		@param imagePath  const tchar*  ͼƬ��Դ·��
		@return bool
		*/
		virtual bool SetBackImage(const tchar* imagePath) = 0;
		/*
		@name RemoveAllChildControl
		@desc �Ƴ����а��ӿؼ�
		@param void
		@return void
		*/
		virtual void RemoveAllChildControl() = 0;
		/*
		@name RemoveChildControl
		@desc ���ݾ���Ƴ����а��ӿؼ�
		@param ctrlHandle void* �Ӵ��ھ��
		@return bool
		*/
		virtual bool RemoveChildControl(void* ctrlHandle) = 0;
		/*
		@name SetBackgroundStyle
		@desc ���ñ�����ʽ
		@param state UIState ״̬ö��
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetBackgroundStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc ��ȡ������ʽ
		@param state UIState ״̬ö��
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UIState state) = 0;
		/*
		@name SetBorderColor
		@desc ���ñ߿���ɫ
		@param color  unsigned int  ��ɫֵ
		@return void
		*/
		virtual void SetBorderColor(unsigned int color) = 0;
		/*
		@name GetBorderColor
		@desc ��ȡ�߿���ɫ
		@param void
		@return unsigned int
		*/
		virtual int GetBorderColor() = 0;
		/*
		@name SetUseBorder
		@desc �����Ƿ���Ʊ߿�
		@param use bool �Ƿ�ʹ��
		@return void
		*/
		virtual void SetUseBorder(bool use) = 0;
		/*
		@name GetUseBorder
		@desc ��ȡ�Ƿ���Ʊ߿�
		@param void
		@return bool
		*/
		virtual bool GetUseBorder() = 0;
		/*
		@name SetChildLayout
		@desc �����ӿؼ��Ĳ�������
		@param layout UIGChildrenLayout ����ö��
		@return void
		~
		enum UIGChildrenLayout
		{
		UIG_CL_HOR,  // ˮƽ����
		UIG_CL_VER,  // ��ֱ����
		UIG_CL_HORFLOAT, // ˮƽ�������ȴ����ң�Ȼ����ϵ���
		UIG_CL_VERFLOAT, // ��ֱ�������ȴ��ϵ��£�Ȼ�������
		UIG_CL_NOUSE, // ��ʹ�ò���
		UIG_CL_LAST 
		};
		~
		*/
		virtual void SetChildLayout(UIGChildrenLayout layout) = 0;
		/*
		@name GetChildLayout
		@desc ��ȡ�ӿؼ��Ĳ�������
		@param void
		@return UIGChildrenLayout
		*/
		virtual UIGChildrenLayout GetChildLayout() = 0;
		/*
		@name SetChildrenSpace
		@desc �����ӿؼ�֮��Ĳ��ּ�����������ӿؼ����ֺ����Ч
		@param space int ���
		@return void
		*/
		virtual void SetChildrenSpace(int space) = 0;
		/*
		@name GetChildrenSpace
		@desc ��ȡ�ӿؼ���ļ��
		@param void
		@return int
		*/
		virtual int GetChildrenSpace() = 0;
		/*
		@name SetNeedClickEvent
		@desc �����Ƿ���Ҫ����¼���Ĭ��û�е���¼�
		@param needEvent bool �Ƿ��
		@return void
		*/
		virtual void SetNeedClickEvent(bool needEvent) = 0;
		/*
		@name GetNeedClickEvent
		@desc ��ȡ�Ƿ��е���¼���Ĭ��û�е���¼�
		@param void
		@return bool
		*/
		virtual bool GetNeedClickEvent() = 0;
		/*
		@name BindScrollBar
		@desc �󶨹��������������ӿؼ����ֺ���԰󶨹��������й���
		@param pScrollbar IUIGScrollBar* ������ָ��
		@param isHor bool �Ƿ���ˮƽ������
		@return bool
		*/
		virtual bool BindScrollBar(IUIGScrollBar* pScrollbar, bool isHor) = 0;
	};

	class IUIGScrollView : public IUIGContainer
	{
	public:
		virtual void SetOffsetY(int offset) = 0;
		virtual int GetOffsetY() = 0;
	};

	class IUIGDataGrid : public IUIGearsControl
	{
	public:
		/*
		@name AddItem
		@desc ���item
		@param text  const tchar*  item�ı�����
		@return bool
		*/
		virtual bool AddItem(const tchar* text) = 0;
		/*
		@name RemoveAll
		@desc ɾ�����е�item
		@param void
		@return void
		*/
		virtual void RemoveAll() = 0;
		/*
		@name RemoveAllColumns
		@desc ɾ�����е���
		@param void
		@return void
		*/
		virtual void RemoveAllColumns() = 0;
		/*
		@name RemoveItem
		@desc ���������Ƴ�item
		@param index int ������
		@return bool
		*/
		virtual bool RemoveItem(int index) = 0;
		/*
		@name RemoveColumn
		@desc ���������Ƴ�ĳһ��
		@param index int ������
		@return bool
		*/
		virtual bool RemoveColumn(int index) = 0;
		/*
		@name GetColumnCount
		@desc ��ȡ�е�����
		@param void
		@return int
		*/
		virtual int GetColumnCount() = 0;
		/*
		@name GetColumnHeaderText
		@desc ����������ȡ��ͷ������
		@param index int ������
		@return const tchar*
		*/
		virtual const tchar* GetColumnHeaderText(int index) = 0;
		/*
		@name SetColumnHeaderText
		@desc ��������������ͷ������
		@param index int ������
		@param text  const tchar*  ��������
		@return void
		*/
		virtual void SetColumnHeaderText(int index, const tchar* text) = 0;
		/*
		@name GetEditable
		@desc ��ȡ�Ƿ���Ա༭
		@param void
		@return bool
		*/
		virtual bool GetEditable() = 0;
		/*
		@name SetEditable
		@desc �����Ƿ���Ա༭
		@param editable bool �Ƿ�ɱ༭
		@return void
		*/
		virtual void SetEditable(bool editable) = 0;
		/*
		@name GetSelectedIndex
		@desc ��ȡѡ������
		@param void
		@return int
		*/
		virtual int GetSelectedIndex() = 0;
		/*
		@name SetSelectedIndex
		@desc ����ѡ�����������Ϊ-1���ʾ�������ѡ��
		@param index int ������
		@return void
		*/
		virtual void SetSelectedIndex(int index) = 0;
		/*
		@name GetItemText
		@desc ��ȡitem��������
		@param row int ��������
		@param col int ��������
		@return const tchar*
		*/
		virtual const tchar* GetItemText(int row, int col) = 0;
		/*
		@name SetVerticalScrollBar
		@desc �󶨴�ֱ������
		@param pScrollBar IUIGearsControl* �������ؼ�ָ��
		@return void
		*/
		virtual void SetVerticalScrollBar(IUIGearsControl* pScrollbar) = 0;
		/*
		@name SetHorizontalScrollBar
		@desc ��ˮƽ������
		@param pScrollBar IUIGearsControl* �������ؼ�ָ��
		@return void
		*/
		virtual void SetHorizontalScrollBar(IUIGearsControl* pScrollbar) = 0;
		/*
		@name SetMultiSelect
		@desc �����Ƿ�֧�ֶ�ѡ
		@param multiSelect bool �Ƿ�֧�ֶ�ѡ
		@return void
		*/
		virtual void SetMultiSelect(bool multiSelect) = 0;
		/*
		@name GetMultiSelect
		@desc ��ȡ�Ƿ�֧�ֶ�ѡ
		@param void
		@return bool
		*/
		virtual bool GetMultiSelect() = 0;
		/*
		@name SetDragSelect
		@desc �����Ƿ����קѡ��ѡ��
		@param dragSelect bool ��קѡ��
		@return void
		*/
		virtual void SetDragSelect(bool dragSelect) = 0;
		/*
		@name GetDragSelect
		@desc ��ȡ�Ƿ����קѡ��ѡ��
		@param void
		@return bool
		*/
		virtual bool GetDragSelect() = 0;
		/*
		@name IsSelected
		@desc �Ƿ�ѡ��ĳ��
		@param index int ����
		@return bool
		*/
		virtual bool IsSelected(int index) = 0;
		/*
		@name GetMultiSelectedItems
		@desc ��ȡ��ѡ��ѡ��
		@param void
		@return std::vector<int> �����б�
		*/
		virtual	std::vector<int> GetMultiSelectedItems() = 0;
		/*
		@name GetItemCount
		@desc ��ȡitem����
		@param void
		@return int
		*/
		virtual int GetItemCount() = 0;
		virtual void SetDataMode(UIGDataGridMode mode) = 0;
		/*
		@name AppendColumn
		@desc ������
		@param colName  const tchar*  ��ͷ����
		@param colWidth  int  ��ͷ��ȣ�Ĭ��100
		@return void
		*/
		virtual void AppendColumn(const tchar* colName, int colWidth = 100) = 0;
		/*
		@name SetItemText
		@desc ����item��������
		@param row int ��������
		@param col int ��������
		@param text  const tchar*  ��������
		@return bool
		*/
		virtual bool SetItemText(int row, int col, const tchar* text) = 0;
		/*
		@name SetBackgroundStyle
		@desc ���ñ�����ʽ
		@param state UICommonState ״̬����
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetBackgroundStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc ��ѯ������ʽ
		@param state UICommonState ״̬����
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UICommonState state) = 0;
		/*
		@name SetItemStyle
		@desc ����Item������ʽ
		@param state UICommonState ״̬����
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetItemStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetItemStyle
		@desc ��ѯItem������ʽ
		@param state UICommonState ״̬����
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetItemStyle(UIState state) = 0;
		/*
		@name SetItemTextStyle
		@desc ����Item������ʽ
		@param state UICommonState ״̬����
		@param style IUIGearsTextStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetItemTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetItemTextStyle
		@desc ��ѯItem������ʽ
		@param state UICommonState ״̬����
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsTextStyle* GetItemTextStyle(UIState state) = 0;
		/*
		@name SetHeaderBackgroundStyle
		@desc ���ñ�ͷ������ʽ
		@param state UICommonState ״̬����
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetHeaderBackgroundStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetHeaderBackgroundStyle
		@desc ��ȡ��ͷ������ʽ
		@param state UICommonState ״̬����
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual IUIGearsRectStyle* GetHeaderBackgroundStyle(UICommonState state) = 0;
		/*
		@name SetHeaderTextStyle
		@desc ���ñ�ͷ������ʽ
		@param state UIState ״̬����
		@param style IUIGearsTextStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetHeaderTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetHeaderTextStyle
		@desc ��ȡ��ͷ������ʽ
		@param state UIState ״̬����
		@return IUIGearsTextStyle*
		*/
		virtual IUIGearsTextStyle* GetHeaderTextStyle(UIState state) = 0;
		/*
		@name SetItemHeight
		@desc ����item�߶�
		@param height int item�߶�
		@return void
		*/
		virtual void SetItemHeight(int height) = 0;
		/*
		@name GetItemCount
		@desc ��ȡitem����
		@param void
		@return int
		*/
		virtual int GetItemHeight() = 0;
		/*
		@name SetScrollIndex
		@desc ���ù���λ��
		@param index  unsinged int  ��������λ��
		@return bool
		*/
		virtual bool SetScrollIndex(unsigned int index) = 0;
		/*
		@name GetScrollIndex
		@desc ��ȡ��ǰ�������λ��
		@param void
		@return unsigned int
		*/
		virtual unsigned int GetScrollIndex() = 0;
	};

	class IUIGTree : public IUIGearsControl
	{
	public:
		/*
		@name RemoveAll
		@desc ɾ�����нڵ�
		@param void
		@return void
		*/
		virtual void RemoveAll() = 0;
		/*
		@name SetVerticalScrollBar
		@desc �󶨴�ֱ������
		@param pScrollBar IUIGearsControl* �������ؼ�ָ��
		@return void
		*/
		virtual void SetVerticalScrollBar(IUIGearsControl* pScrollbar) = 0;
		/*
		@name SetHorizontalScrollBar
		@desc ��ˮƽ������
		@param pScrollBar IUIGearsControl* �������ؼ�ָ��
		@return void
		*/
		virtual void SetHorizontalScrollBar(IUIGearsControl* pScrollbar) = 0;
		/*
		@name SetMultiSelect
		@desc �����Ƿ�֧�ֶ�ѡ
		@param multiSelect bool �Ƿ�֧�ֶ�ѡ
		@return void
		*/
		virtual void SetMultiSelect(bool multiSelect) = 0;
		/*
		@name InsertItem
		@desc ����ڵ�
		@param parent TreeNode ���ڵ㣬�����NULL�������ڵ���
		@param pos int ����λ���±�
		@param text  const tchar*  ��������
		@return TreeNode
		*/
		virtual TreeNode InsertItem(TreeNode parent, unsigned int pos, const tchar* text) = 0;
		/*
		@name AppendItem
		@desc ��ĩβ����ڵ�
		@param parent TreeNode ���ڵ㣬�����NULL�������ڵ���
		@param text  const tchar*  ��������
		@return TreeNode
		*/
		virtual TreeNode AppendItem(TreeNode parent, const tchar* text) = 0;
		/*
		@name DeleteNode
		@desc ɾ���ڵ�
		@param item TreeNode �ڵ�ָ��
		@return bool
		*/
		virtual bool DeleteNode(TreeNode item) = 0; 
		/*
		@name SetItemText
		@desc ���ýڵ��ı�
		@param item TreeNode �ڵ�ָ��
		@param text  const tchar*  �ڵ�ָ��
		@return bool
		*/
		virtual bool SetItemText(TreeNode node, const tchar* text) = 0;
		/*
		@name SetItemIcon
		@desc ���ýڵ�ͼ��
		@param item TreeNode �ڵ�ָ��
		@param iconPath  const tchar*  ͼ����Դ·��
		@return bool
		*/
		virtual bool SetItemIcon(TreeNode node, const tchar* iconPath) = 0;
		/*
		@name SetItemIcon
		@desc ���ýڵ�ͼ��
		@param item TreeNode �ڵ�ָ��
		@param iconPath  const tchar*  ��Դ����
		@param iconBuffer void* ����������ָ��
		@param length  unsigned int  ���ݳ���
		@return bool
		*/
		virtual bool SetItemIcon(TreeNode node, const tchar* iconName, void* iconBuffer, unsigned int length) = 0;
		/*
		@name SetItemData
		@desc �����û�����ָ��
		@param item TreeNode �ڵ�ָ��
		@param data void* �û�����
		@return bool
		*/
		virtual bool SetItemData(TreeNode node, void* data) = 0;
		/*
		@name GetItemData
		@desc ��ȡ�û�����ָ��
		@param void
		@return void*
		*/
		virtual void*	GetItemData(TreeNode node) = 0;
		/*
		@name GetSelectedNodes
		@desc ��ȡѡ�еĽڵ� 
		@param void
		@return std::vector<TreeNode*>*
		*/
		virtual std::vector<TreeNode*>* GetSelectedNodes() = 0;
		/*
		@name SetSelectedNode
		@desc ����ѡ�еĽڵ�
		@param node TreeNode ѡ�нڵ�
		@return bool
		*/
		virtual bool SetSelectedNode(TreeNode node) = 0;
		/*
		@name SwapNode
		@desc ���������ڵ�
		@param node1 TreeNode �ڵ�1
		@param node2 TreeNode �ڵ�2
		@return bool
		*/
		virtual bool SwapNode(TreeNode node1, TreeNode node2) = 0;
		/*
		@name ScrollToNode
		@desc ������ĳһ�ڵ�
		@param node TreeNode ��Ҫ�������Ľڵ�
		@return bool
		*/
		virtual bool ScrollToNode(TreeNode node) = 0;
		/*
		@name GetItemText
		@desc ��ȡ�ڵ��ı�
		@param node TreeNode �ڵ�
		@return const tchar*
		*/
		virtual const tchar* GetItemText(TreeNode node) = 0;
		/*
		@name GetParentNode
		@desc ��ȡ���ڵ�
		@param node TreeNode �ڵ㣬����ΪNULL
		@return TreeNode
		*/
		virtual TreeNode GetParentNode(TreeNode node) = 0;
		/*
		@name GetChildrenNodeCount
		@desc ��ȡ�ӽڵ������
		@param node TreeNode �ڵ�
		@return unsigned int
		*/
		virtual unsigned int GetChildrenNodeCount(TreeNode node) = 0;
		/*
		@name GetChildNodeByIndex
		@desc ͨ��������ȡ���ڵ���ӽڵ�
		@param node TreeNode ���ڵ�
		@param index  unsgined int  ������
		@return TreeNode
		*/
		virtual TreeNode GetChildNodeByIndex(TreeNode node, unsigned int index) = 0;
		/*
		@name SetExpandIcon
		@desc ����չ��ͼ��
		@param pIconPath  const tchar*  ͼ��·��
		@return void
		*/
		virtual void SetExpandIcon(const tchar* pIconPath) = 0;
		/*
		@name GetExpandIcon
		@desc ��ȡչ��ͼ��
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetExpandIcon() = 0;
		/*
		@name SetUnExpandIcon
		@desc ��������ͼ��
		@param pIconPath  const tchar*  ��Դ·��
		@return void
		*/
		virtual void SetUnExpandIcon(const tchar* pIconPath) = 0;
		/*
		@name GetUnExpandIcon
		@desc ��ȡ����ͼ��
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetUnExpandIcon() = 0;
		/*
		@name SetItemOffset
		@desc ���ò㼶֮ǰ��ƫ����
		@param offset int ƫ����
		@return void
		*/
		virtual void SetItemOffset(int offset) = 0;
		/*
		@name GetItemOffset
		@desc ��ȡ�㼶֮ǰ��ƫ����
		@param void
		@return int
		*/
		virtual int GetItemOffset() = 0;
		/*
		@name SetIconWidth
		@desc ����ͼ��Ŀ�ȣ�Ĭ����16
		@param width int ���ֵ
		@return void
		*/
		virtual void SetIconWidth(int width) = 0;
		/*
		@name GetIconWidth
		@desc ��ȡͼ��Ŀ��
		@param void
		@return int
		*/
		virtual int GetIconWidth() = 0;
		/*
		@name SetExpandIconWidth
		@desc ����չ��ͼ��Ŀ��
		@param width int ���
		@return void
		*/
		virtual void SetExpandIconWidth(int width) = 0;
		/*
		@name GetExpandIconWidth
		@desc ��ȡչ��ͼ��Ŀ��
		@param void
		@return int
		*/
		virtual int GetExpandIconWidth() = 0;
		/*
		@name SetShowIcon
		@desc �����Ƿ���ʾͼ��
		@param show bool �Ƿ���ʾ
		@return void
		*/
		virtual void SetShowIcon(bool show) = 0;
		/*
		@name GetShowIcon
		@desc ��ȡ�Ƿ���ʾͼ��
		@param void
		@return bool
		*/
		virtual bool GetShowIcon() = 0;
		/*
		@name SetItemHeight
		@desc ����item�߶�
		@param height int item�߶�
		@return void
		*/
		virtual void SetItemHeight(int height) = 0;
		/*
		@name GetItemCount
		@desc ��ȡitem����
		@param void
		@return int
		*/
		virtual int GetItemHeight() = 0;
		/*
		@name SetBackgroundStyle
		@desc ���ñ�����ʽ
		@param state UICommonState ״̬����
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetBackgroundStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc ��ѯ������ʽ
		@param state UICommonState ״̬����
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UICommonState state) = 0;
		/*
		@name SetItemStyle
		@desc ����Item������ʽ
		@param state UICommonState ״̬����
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetItemStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetItemStyle
		@desc ��ѯItem������ʽ
		@param state UICommonState ״̬����
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetItemStyle(UIState state) = 0;
		/*
		@name SetItemTextStyle
		@desc ����Item������ʽ
		@param state UICommonState ״̬����
		@param style IUIGearsTextStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetItemTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetItemTextStyle
		@desc ��ѯItem������ʽ
		@param state UICommonState ״̬����
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsTextStyle* GetItemTextStyle(UIState state) = 0;
	};

	class IUIGEdit : public IUIGearsControl
	{
	public:
		/*
		@name SetText
		@desc �����ı�����
		@param text  const tchar*  �ı�����
		@return bool
		*/
		virtual bool SetText(const tchar* text) = 0;
		/*
		@name GetText
		@desc ��ȡ�ı�����
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetText() = 0;
		/*
		@name GetIsPassword
		@desc �Ƿ���������ʾ
		@param void
		@return bool
		*/
		virtual bool GetIsPassword() = 0;
		/*
		@name SetIsPassword
		@desc ����������ʾ
		@param password bool ������ʾ
		@return void
		*/
		virtual void SetIsPassword(bool password) = 0;
		/*
		@name SetPasswordChar
		@desc ����������ʾ������ַ�
		@param passchar  const tchar*  �ַ�����
		@return void
		*/
		virtual void SetPasswordChar(const tchar* passchar) = 0;
		/*
		@name GetPasswordChar
		@desc ��ȡ������ʾ������ַ�
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetPasswordChar() = 0;
		/*
		@name GetIsNumberOnly
		@desc ��ȡ�Ƿ�ֻ����ʾ��ֵ
		@param void
		@return bool
		*/
		virtual bool GetIsNumberOnly() = 0;
		/*
		@name SetIsNumberOnly
		@desc �����Ƿ�ֻ��������ֵ
		@param numberOnly bool ֻ��������ֵ
		@return void
		*/
		virtual void SetIsNumberOnly(bool numberOnly) = 0;
		/*
		@name GetHasNegativeNum
		@desc ��ȡ�Ƿ��������븺ֵ
		@param void
		@return bool
		*/
		virtual bool GetHasNegativeNum() = 0;
		/*
		@name SetHasNegativeNum
		@desc �����Ƿ������и�ֵ
		@param negativeNum bool ����ֵ
		@return void
		*/
		virtual void SetHasNegativeNum(bool negativeNum) = 0;
		/*
		@name SetNumber
		@desc ������ʾ����ֵ
		@param number int ��ֵ����
		@return void
		*/
		virtual void SetNumber(int number) = 0;
		/*
		@name GetNumber
		@desc ��ȡ��ֵ����
		@param void
		@return int
		*/
		virtual int GetNumber() = 0;
		/*
		@name SetNumberCount
		@desc ���ÿ�������ֵ��λ��
		@param count int �������λ��
		@return void
		*/
		virtual void SetNumberCount(int count) = 0;
		/*
		@name GetNumberCount
		@desc ��ȡ��������ֵ��λ��
		@param void
		@return int
		*/
		virtual int GetNumberCount() = 0;
		/*
		@name SetDigitNumCount
		@desc ����С����λ��
		@param count int С��λ��
		@return void
		*/
		virtual void SetDigitNumCount(int count) = 0;
		/*
		@name GetDigitNumCount
		@desc ��ȡС����λ��
		@param void
		@return int
		*/
		virtual int GetDigitNumCount() = 0;
		/*
		@name SetRange
		@desc ������ֵ�ķ�Χ
		@param min int ��Сֵ
		@param max int ���ֵ
		@return void
		*/
		virtual void SetRange(int min, int max) = 0;
		/*
		@name GetRange
		@desc ��ȡ��ֵ�ķ�Χ
		@param min int& ��Сֵ
		@param max int& ���ֵ
		@return void
		*/
		virtual void GetRange(int& min, int& max) = 0;
		/*
		@name SetBackgroundStyle
		@desc ���ñ�����ʽ
		@param state UIState ״̬
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetBackgroundStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc ��ȡ������ʽ
		@param state UIState ״̬
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UIState state) = 0;
		/*
		@name SetMargin
		@desc �������ҵļ��
		@param left int �����
		@param right int �Ҳ���
		@return void
		*/
		virtual void SetMargin(int left, int right) = 0;
		/*
		@name GetMargin
		@desc ��ȡ���ҵļ��
		@param left int& �����
		@param right int& �Ҳ���
		@return void
		*/
		virtual void GetMargin(int& left, int& right) = 0;
		/*
		@name GetFontSize
		@desc ��ȡ�����С
		@param void
		@return unsigned int
		*/
		virtual unsigned int GetFontSize() = 0;
		/*
		@name SetFontSize
		@desc ���������С
		@param size  unsigned int  �����С
		@return void
		*/
		virtual void SetFontSize(unsigned int size) = 0;
		/*
		@name SetFontSize
		@desc ���������С
		@param size  unsigned int  �����С
		@return void
		*/
		virtual unsigned int GetFontColor() = 0;
		/*
		@name SetFontColor
		@desc ����������ɫ
		@param color  unsigned int  ������ɫ
		@return void
		*/
		virtual void SetFontColor(unsigned int color) = 0;
		/*
		@name GetDisableFontColor
		@desc ��ȡ����������ɫ
		@param void
		@return unsigned int
		*/
		virtual unsigned int GetDisableFontColor() = 0;
		/*
		@name SetDisableFontColor
		@desc ���ý���������ɫ
		@param color  unsigned int  ������ɫ
		@return void
		*/
		virtual void SetDisableFontColor(unsigned int color) = 0;
		/*
		@name SetTipFontColor
		@desc ����tip������ɫ
		@param color  unsigned int  ������ɫ
		@return void
		*/
		virtual void SetTipFontColor(unsigned int color) = 0;
		/*
		@name GetTipFontColor
		@desc ��ȡtip������ɫ
		@param void
		@return unsigned int
		*/
		virtual unsigned int GetTipFontColor() = 0;
		/*
		@name SetTipText
		@desc ����tip��������
		@param text  const tchar*  ��ʾ��������
		@return viod
		*/
		virtual void SetTipText(const tchar* text) = 0;
		/*
		@name GetTipText
		@desc ��ȡtip��������
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetTipText() = 0;
		/*
		@name SetShowTipText
		@desc �����Ƿ���ʾtip����
		@param show bool �Ƿ���ʾtip����
		@return void
		*/
		virtual void SetShowTipText(bool show) = 0;
		/*
		@name GetShowTipText
		@desc ��ȡ�Ƿ���ʾtip����
		@param void
		@return bool
		*/
		virtual bool GetShowTipText() = 0;
		/*
		@name SetFontFamily
		@desc ��������
		@param family  const tchar*  ����
		@return void
		*/
		virtual void SetFontFamily(const tchar* family) = 0;
		/*
		@name GetFontFamily
		@desc ��ȡ����
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetFontFamily() = 0;
		/*
		@name SetLeftMargin
		@desc ���������
		@param margin int �����С
		@return void
		*/
		virtual void SetLeftMargin(int margin) = 0;
		/*
		@name GetLeftMargin
		@desc ��ȡ�����
		@param void
		@return int
		*/
		virtual int GetLeftMargin() = 0;
		/*
		@name SetRightMargin
		@desc �����Ҳ���
		@param margin int �����С
		@return void
		*/
		virtual void SetRightMargin(int margin) = 0;
		/*
		@name GetRightMargin
		@desc ��ȡ�Ҳ���
		@param void
		@return int
		*/
		virtual int GetRightMargin() = 0;
		/*
		@name SetUseShortcut
		@desc �����Ƿ�ʹ�ÿ�ݼ�ģʽ
		@param shortcut bool ��ݼ�
		@return void
		*/
		virtual void SetUseShortcut(bool shortcut) = 0;
		/*
		@name GetUseShortcut
		@desc ��ѯ�Ƿ�ʹ�ÿ�ݼ�ģʽ
		@param void
		@return bool
		*/
		virtual bool GetUseShortcut() = 0;
		/*
		@name SetReadonly
		@desc ����ֻ��ģʽ
		@param readonly bool ֻ��ģʽ
		@return void
		*/
		virtual void SetReadonly(bool readonly) = 0;
		/*
		@name GetReadonly
		@desc �Ƿ�Ϊֻ��ģʽ
		@param void
		@return bool
		*/
		virtual bool GetReadonly() = 0;
	};

	class IUIGDrawMultiEdit : public IUIGearsControl
	{
	public:
	};

	class IUIGNumberEdit : public IUIGearsControl
	{
	public:
		/*
		@name SetText
		@desc �����ı�����
		@param text  const tchar*  �ı�����
		@return bool
		*/
		virtual bool SetText(const tchar* text) = 0;
		/*
		@name GetText
		@desc ��ȡ�ı�����
		@param void
		@return const tchar* 
		*/
		virtual const tchar* GetText() = 0;
		/*
		@name SetNumber
		@desc ������ֵ
		@param number int ��ֵ
		@return void
		*/
		virtual void SetNumber(int number) = 0;
		/*
		@name GetNumber
		@desc ��ȡ��ֵ
		@param void
		@return int
		*/
		virtual int GetNumber() = 0;
		/*
		@name SetRange
		@desc ���÷�Χ
		@param min int ��Сֵ
		@param max int ���ֵ
		@return void
		*/
		virtual void SetRange(int min, int max) = 0;
		/*
		@name GetRange
		@desc ��ȡ��Χ
		@param min int& ��Сֵ
		@param max int& ���ֵ
		@return void
		*/
		virtual void GetRange(int& min, int& max) = 0;
		/*
		@name SetBackgroundStyle
		@desc ���ñ�����ʽ
		@param state UIState ״̬ö��
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetBackgroundStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc ��ȡ������ʽ
		@param state UIState ״̬ö��
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UIState state) = 0;
		/*
		@name SetMargin
		@desc ���ü��
		@param left int ����
		@param right int �Ҽ��
		@return void
		*/
		virtual void SetMargin(int left, int right) = 0;
		/*
		@name GetMargin
		@desc ��ȡ���
		@param left int& ����
		@param right int& �Ҽ��
		@return void
		*/
		virtual void GetMargin(int& left, int& right) = 0;
		/*
		@name GetFontSize
		@desc ��ȡ�����С
		@param void
		@return int
		*/
		virtual int GetFontSize() = 0;
		/*
		@name SetFontSize
		@desc ���������С
		@param size int �����С
		@return void
		*/
		virtual void SetFontSize(int size) = 0;
		/*
		@name GetFontColor
		@desc ��ȡ������ɫ
		@param void
		@return int
		*/
		virtual int GetFontColor() = 0;
		/*
		@name SetFontColor
		@desc ����������ɫ
		@param color int ������ɫ
		@return void
		*/
		virtual void SetFontColor(int color) = 0;
		/*
		@name SetUpBtnStyle
		@desc �����ϰ�ť��ʽ
		@param state UIState ״̬ö��
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetUpBtnStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetUpBtnStyle
		@desc ��ȡ�ϰ�ť��ʽ
		@param state UIState ״̬ö��
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetUpBtnStyle(UIState state) = 0;
		/*
		@name SetDownBtnStyle
		@desc �����°�ť��ʽ
		@param state UIState ״̬ö��
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetDownBtnStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetDownBtnStyle
		@desc ��ȡ�°�ť��ʽ
		@param state UIState ״̬ö��
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetDownBtnStyle(UIState state) = 0;
		/*
		@name SetLeftMargin
		@desc ��������
		@param margin int ���
		@return void
		*/
		virtual void SetLeftMargin(int margin) = 0;
		/*
		@name GetLeftMargin
		@desc ��ȡ����
		@param void
		@return int
		*/
		virtual int GetLeftMargin() = 0;
		/*
		@name SetRightMargin
		@desc �����Ҽ��
		@param margin int ���
		@return void
		*/
		virtual void SetRightMargin(int margin) = 0;
		/*
		@name GetRightMargin
		@desc ��ȡ�Ҽ��
		@param void
		@return int
		*/
		virtual int GetRightMargin() = 0;
	};

	class IUIGIPEdit : public IUIGearsControl
	{
	public:
		/*
		@name SetIP
		@desc ����IP��ַ
		@param text  const tchar*  ip��ַ�ַ�����"127.0.0.1"
		@return void
		*/
		virtual void SetIP(const tchar* text) = 0;
		/*
		@name GetIP
		@desc ��ȡIP��ַ�ַ���
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetIP() = 0;
		/*
		@name SetBackgroundStyle
		@desc ���ñ�����ʽ
		@param state UIState ״̬ö��
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetBackgroundStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc ��ȡ������ʽ
		@param state UIState ״̬ö��
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UIState state) = 0;
		/*
		@name GetFontSize
		@desc ��ȡ�����С
		@param void
		@return int
		*/
		virtual int GetFontSize() = 0;
		/*
		@name SetFontSize
		@desc ���������С
		@param size int �����С
		@return void
		*/
		virtual void SetFontSize(int size) = 0;
		/*
		@name GetFontColor
		@desc ��ȡ�����С
		@param void
		@return int
		*/
		virtual int GetFontColor() = 0;
		/*
		@name SetFontColor
		@desc ����������ɫ
		@param color int ��ɫֵ����0xff000000
		@return void
		*/
		virtual void SetFontColor(int color) = 0;
		/*
		@name GetDisableFontColor
		@desc ��ȡ����������ɫ
		@param void
		@return int
		*/
		virtual int GetDisableFontColor() = 0;
		/*
		@name SetDisableFontColor
		@desc ���ý���������ɫ
		@param color int ��ɫֵ����0xff000000
		@return void
		*/
		virtual void SetDisableFontColor(int color) = 0;
		/*
		@name SetFontFamily
		@desc ��������
		@param family  const tchar*  ����
		@return void
		*/
		virtual void SetFontFamily(const tchar* family) = 0;
		/*
		@name GetFontFamily
		@desc ��ȡ����
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetFontFamily() = 0;
	};

	class IUIGComboBox : public IUIGearsControl
	{
	public:
		/*
		@name AddItem
		@desc ���item
		@param text  const tchar*  ��������
		@return void
		*/
		virtual void AddItem(const tchar* text) = 0;
		/*
		@name RemoveItem
		@desc �Ƴ�item
		@param index int ������
		@return void
		*/
		virtual void RemoveItem(int index) = 0;
		/*
		@name SetSelectedIndex
		@desc ������������ѡ����
		@param index unsigned int ������
		@return void
		*/
		virtual void SetSelectedIndex(unsigned int index) = 0;
		/*
		@name RemoveAllItems
		@desc ɾ��������
		@param void
		@return void
		*/
		virtual void RemoveAllItems() = 0;
		/*
		@name GetSelectedIndex
		@desc ��ȡѡ����
		@param void
		@return void
		*/
		virtual int GetSelectedIndex() = 0;
		/*
		@name SetText
		@desc ������ʾ����
		@param text  const tchar*  ��������
		@return void
		*/
		virtual void SetText(const tchar* text) = 0;
		/*
		@name GetText
		@desc ��ȡ��ʾ����
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetText() = 0;
		/*
		@name SetBackgroundStyle
		@desc ���ñ�����ʽ
		@param state UIState ״̬ö��
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetBackgroundStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc ��ȡ������ʽ
		@param state UIState ״̬ö��
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UIState state) = 0;
		/*
		@name SetBtnStyle
		@desc ���ð�ť��ʽ
		@param state UIState ״̬ö��
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetBtnStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBtnStyle
		@desc ��ȡ��ť��ʽ
		@param state UIState ״̬ö��
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBtnStyle(UIState state) = 0;
		/*
		@name GetTextStyle
		@desc ��ȡ������ʽ
		@param state UIState ״̬ö��
		@return IUIGearsTextStyle*
		*/
		virtual IUIGearsTextStyle* GetTextStyle(UIState state) = 0;
		/*
		@name SetTextStyle
		@desc ����������ʽ
		@param state UIState ״̬ö��
		@param style IUIGearsTextStyle* ��ʽָ��
		@return IUIGearsTextStyle*
		*/
		virtual bool SetTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name SetTextStyle
		@desc ������߶�
		@param height int ��߶�
		@return void
		*/
		virtual void SetItemHeight(int height) = 0;
		/*
		@name GetItemHeight
		@desc ��ȡ��߶�
		@param void
		@return int
		*/
		virtual int GetItemHeight() = 0;
		/*
		@name SetPopupMenuBg
		@desc ���������б���
		@param state UICommonState ״̬ö��
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetPopupMenuBg(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetPopupMenuBg
		@desc ��ȡ�����б���
		@param state UICommonState ״̬ö��
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetPopupMenuBg(UICommonState state) = 0;
		/*
		@name SetPopupItemStyle
		@desc �������������ʽ
		@param state UICommonState ״̬ö��
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetPopupItemStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetPopupItemStyle
		@desc ��ȡ���������ʽ
		@param state UICommonState ״̬ö��
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetPopupItemStyle(UIState state) = 0;
		/*
		@name SetPopupTextStyle
		@desc ��������������ʽ
		@param state UICommonState ״̬ö��
		@param style IUIGearsTextStyle* ������ʽ
		@return bool
		*/
		virtual bool SetPopupTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetPopupTextStyle
		@desc ��ȡ����������ʽ
		@param state UICommonState ״̬ö��
		@return IUIGearsTextStyle*
		*/
		virtual IUIGearsTextStyle* GetPopupTextStyle(UIState state) = 0;
		/*
		@name SetItemData
		@desc �����û��Զ�������
		@param index int ������
		@param data PARAM �û�����
		@return bool
		*/
		virtual bool SetItemData(int index, PARAM data) = 0;
		/*
		@name GetItemData
		@desc ��ȡ�û��Զ�������
		@param index int ������
		@return PARAM
		*/
		virtual PARAM GetItemData(int index) = 0;
		/*
		@name SetItemText
		@desc �޸���������������
		@param index int ������
		@param text  const tchar*  ��������
		@return bool
		*/
		virtual bool SetItemText(int index, const tchar* text) = 0;
		/*
		@name GetItemText
		@desc ��ȡ��������������
		@param index int ������
		@return const tchar*
		*/
		virtual const tchar* GetItemText(int index) = 0;
		/*
		@name GetEditable
		@desc ��ȡ�Ƿ�ɱ༭
		@param void
		@return bool
		*/
		virtual bool GetEditable() = 0;
		/*
		@name SetEditable
		@desc �����Ƿ�ɱ༭
		@param editable bool �Ƿ�ɱ༭
		@return void
		*/
		virtual void SetEditable(bool editable) = 0;
	};

	class IUIGLabel : public IUIGearsControl
	{
	public:
		/*
		@name SetText
		@desc ������������
		@param text  const tchar*  ��������
		@return void
		*/
		virtual void SetText(const tchar* text) = 0;
		/*
		@name GetText
		@desc ��ȡ��������
		@param void
		@return const tchar*
		*/
		virtual const tchar*  GetText() = 0;
		/*
		@name SetColor
		@desc ����������ɫ
		@param textClr  unsigned int  ������ɫ
		@return void
		*/
		virtual void SetColor(unsigned int textClr) = 0;
		/*
		@name GetColor
		@desc ��ȡ������ɫ
		@param void
		@return unsgined int
		*/
		virtual unsigned int GetColor() = 0;
		/*
		@name SetIsSingleline
		@desc �����Ƿ�����ʾ
		@param void
		@return unsgined int
		*/
		virtual void SetIsSingleline(bool singleline) = 0;
		/*
		@name GetIsSingleline
		@desc ��ȡ�Ƿ�����ʾ
		@param void
		@return bool
		*/
		virtual bool GetIsSingleline() = 0;
		/*
		@name GetTextStyle
		@desc ��ȡ������ʽ
		@param state UIState ״̬ö��
		@return IUIGearsTextStyle*
		*/
		virtual IUIGearsTextStyle* GetTextStyle(UIState state) = 0;
		/*
		@name SetTextStyle
		@desc ����������ʽ
		@param state UIState ״̬ö��
		@param style IUIGearsTextStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetIsLCD
		@desc ��ȡ�Ƿ���LCD����
		@param void
		@return bool
		*/
		virtual bool GetIsLCD() = 0;
		/*
		@name SetIsLCD
		@desc �����Ƿ���LCD����
		@param isLCD bool �Ƿ���LCD����
		@return void
		*/
		virtual void SetIsLCD(bool isLCD) = 0;
	};

	class IUIGCanvas : public IUIGearsControl
	{
	public:
		virtual bool OpenJsonFile(const tchar* filePath) = 0;
		virtual bool CloseCurPage() = 0;
		virtual bool OpenPreviousPage() = 0;
		virtual bool OpenNextPage() = 0;
		virtual void DeleteSelected() = 0;
		virtual void CloseAllPage() = 0;
		virtual bool SaveCurPage() = 0;
		virtual bool SavePage(const tchar* filePath) = 0;
		virtual const tchar* UpdatePagePath(const tchar* filePath) = 0;
		virtual void CreateNewPage(int width, int height) = 0;
		virtual void SetProjectPath(const tchar* projPath) = 0;
		virtual IUIGearsWindow* GetCurWindow() = 0;
		virtual void SetSelectedControl(IUIGearsControl* ctrl) = 0;
		virtual void ClearSelection() = 0;
		virtual bool SaveStyle(const tchar* filePath) = 0;
		virtual void SetScrollbar(IUIGScrollBar* pScrollBar, bool isHor) = 0;
		virtual void CloseSolution() = 0;
		virtual void MoveSelectedUp() = 0;
		virtual void MoveSelectedDown() = 0;
		virtual const tchar* GetCurPagePath() = 0;
		virtual bool RemovePage(const tchar* filePath) = 0;
		virtual bool StartCreateControl(const char* typeName, int x, int y) = 0;
		virtual void SetReadFromProjet(bool readFromProject) = 0;
		virtual bool ReloadProjectLanguage(const tchar* languageFilePath) = 0;
		virtual void SetSameX() = 0;
		virtual void SetSameY() = 0;
		virtual void SetSameRight() = 0;
		virtual void SetSameBottom() = 0;
		virtual void SetSameSize() = 0;
		virtual void SetSameWidth() = 0;
		virtual void SetSameHeight() = 0;
		virtual void SetAverageWidth() = 0;
		virtual void SetAverageHeight() = 0;
		virtual void Undo() = 0;
		virtual void Redo() = 0;
		virtual void Copy() = 0;
		virtual void Cut() = 0;
		virtual void Paste() = 0;
		virtual bool PtInCanvas(int x, int y) = 0;
	};

	class IUIGPopupMenu : public IUIGearsControl
	{
	public:
		/*
		@name RemoveAllItems
		@desc ɾ������item��Ŀ
		@param void
		@return void
		*/
		virtual void RemoveAllItems() = 0;
		/*
		@name AppendMenuItem
		@desc ���item��Ŀ
		@param parentItem MenuItem ��item�������ΪNULL�����Ǹ�����
		@param text  const tchar*  ��ʾ�ı�
		@param id int �˵�id
		@param type UIGMenuType �˵�����
		@return MenuItem
		*/
		virtual MenuItem AppendMenuItem(MenuItem parentItem, const tchar* text, int id, UIGMenuType type = UIG_MENU_PUSHBUTTON) = 0;
		/*
		@name SetItemIcon
		@desc ����item��ͼ��
		@param item MenuItem item�������ΪNULL�����Ǹ�����
		@param iconPath  const tchar*  ͼ��·��
		@return bool
		*/
		virtual bool SetItemIcon(MenuItem item, const tchar* iconPath) = 0;
		/*
		@name SetShortcutText
		@desc ����item�Ŀ�ݼ�����
		@param item MenuItem item����
		@param iconPath  const tchar*  ͼ��·��
		@return bool
		*/
		virtual bool SetShortcutText(MenuItem item, const tchar* shortcutText) = 0;
		/*
		@name SetRadioGroupId
		@desc ����item�ķ���id��������radio���͵Ĳ˵���
		@param item MenuItem item����
		@param id int ����id
		@return bool
		*/
		virtual bool SetRadioGroupId(MenuItem item, int id) = 0;
		/*
		@name SetSelected
		@desc ����item���Ƿ�ѡ��
		@param item MenuItem item���󣬿�����radio����check���Ͳ˵���
		@param selected bool �Ƿ�ѡ��
		@return bool
		*/
		virtual bool SetSelected(MenuItem item, bool selected) = 0;
		/*
		@name RemoveAllItems
		@desc ɾ����item��ָ��������item��Ŀ�������NULL���������
		@param parentItem MenuItem ��item����
		@param index int ��Ҫɾ��������
		@return bool
		*/
		virtual bool RemoveMenuItem(MenuItem parentItem, int index) = 0;
		/*
		@name TrackPopupMenu
		@desc �����˵�
		@param x int ����ˮƽ���꣬Ϊ��Ļ����
		@param y int ������ֱ���꣬Ϊ��Ļ����
		@return bool
		*/
		virtual int TrackPopupMenu(int x, int y, bool bWantReturn) = 0;
	};

	class IUIGMenuBar : public IUIGearsControl
	{
	public:
		/*
		@name AppendMenuItem
		@desc ����Ӳ˵���
		@param parentItem MenuItem ���˵���
		@param text  const tchar*  ��������
		@param id int id��
		@param type UIGMenuType �˵�����
		@return bool
		*/
		virtual MenuItem AppendMenuItem(MenuItem parentItem, const tchar* text, int id, UIGMenuType type = UIG_MENU_PUSHBUTTON) = 0;
		/*
		@name SetMenuItemIcon
		@desc ���ò˵�item��icon
		@param item MenuItem �˵���
		@param iconPath  const tchar*  ͼ��·��
		@return bool
		*/
		virtual bool SetMenuItemIcon(MenuItem item, const tchar* iconPath) = 0;
		/*
		@name SetBackgroundStyle
		@desc ���ò˵���������ʽ
		@param state UICommonState ״̬����ö��
		@param style IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetBackgroundStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc ��ȡ�˵���������ʽ
		@param state UICommonState ״̬����ö��
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UICommonState state) = 0;
		/*
		@name SetItemStyle
		@desc ���ò˵���item������ʽ
		@param state UICommonState ״̬����ö��
		@param state IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetItemStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetItemStyle
		@desc ��ȡ�˵���item������ʽ
		@param state UICommonState ״̬����ö��
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetItemStyle(UIState state) = 0;
		/*
		@name SetTextStyle
		@desc ��ȡ�˵���item������ʽ
		@param state UIState ״̬����ö��
		@param style IUIGearsTextStyle* ������ʽ
		@return bool
		*/
		virtual bool SetTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetTextStyle
		@desc ��ȡ�˵���item������ʽ
		@param state UIState ״̬����ö��
		@return IUIGearsTextStyle*
		*/
		virtual IUIGearsTextStyle* GetTextStyle(UIState state) = 0;
		/*
		@name SetItemSpace
		@desc ���ò˵���֮��ļ��
		@param space int �����С
		@return void
		*/
		virtual void SetItemSpace(int space) = 0;
		/*
		@name GetItemSpace
		@desc ��ȡ�˵���֮��ļ��
		@param void
		@return int
		*/
		virtual int GetItemSpace() = 0;
		/*
		@name SetPopupMenuBg
		@desc ���õ����˵�������ʽ
		@param state UICommonState ״̬����ö��
		@param state IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetPopupMenuBg(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetPopupMenuBg
		@desc ��ȡ�����˵�������ʽ
		@param state UICommonState ״̬����ö��
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetPopupMenuBg(UICommonState state) = 0;
		/*
		@name SetPopupItemStyle
		@desc ���õ����˵�item�����ʽ
		@param state UICommonState ״̬����ö��
		@param state IUIGearsRectStyle* ��ʽָ��
		@return bool
		*/
		virtual bool SetPopupItemStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetPopupItemStyle
		@desc ��ȡ�����˵�item�����ʽ
		@param state UICommonState ״̬����ö��
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetPopupItemStyle(UIState state) = 0;
		/*
		@name SetPopupTextStyle
		@desc ���õ����˵���������ʽ
		@param state UIState ״̬����ö��
		@param style IUIGearsTextStyle* ������ʽָ��
		@return bool
		*/
		virtual bool SetPopupTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetPopupTextStyle
		@desc ��ѯ�����˵���������ʽ
		@param state UIState ״̬����ö��
		@return IUIGearsTextStyle*
		*/
		virtual IUIGearsTextStyle* GetPopupTextStyle(UIState state) = 0;
		/*
		@name SetBindPopupMenu
		@desc ���ð󶨵Ĳ˵��ļ�����
		@param name  const tchar*  �˵��ļ���
		@return void
		*/
		virtual void SetBindPopupMenu(const tchar* name) = 0;
		/*
		@name GetBindPopupMenu
		@desc ��ȡ�󶨵Ĳ˵��ļ�����
		@param void
		@return const tchar* 
		*/
		virtual const tchar* GetBindPopupMenu() = 0;
	};

	class IUIGSplitter : public IUIGearsControl
	{
	public:
		/*
		@name SetIsHor
		@desc �����Ƿ���ˮƽ�ָ�����ˮƽ�ָ���ֻ��������ק�������Ǵ�ֱ�ָ�������ֱ�ָ���������ק 
		@param isHor bool �Ƿ���ˮƽ�ָ���
		@return void
		*/
		virtual void SetIsHor(bool isHor) = 0;
		/*
		@name GetIsHor
		@desc ��ȡ�Ƿ���ˮƽ�ָ�����ˮƽ�ָ���ֻ��������ק�������Ǵ�ֱ�ָ�������ֱ�ָ���������ק
		@param void
		@return bool
		*/
		virtual bool GetIsHor() = 0;
		/*
		@name SetLeftTopControlName
		@desc ��������Ϸָ�ؼ�
		@param controlName  const tchar*  �ؼ�����
		@return void
		*/
		virtual void SetLeftTopControlName(const tchar* controlName) = 0;
		/*
		@name GetLeftTopControlName
		@desc ��ȡ����Ϸָ�ؼ�
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetLeftTopControlName() = 0;
		/*
		@name SetRightBottomControlName
		@desc �������·ָ�ؼ�
		@param controlName  const tchar*  �ؼ�����
		@return void
		*/
		virtual void SetRightBottomControlName(const tchar* controlName) = 0;
		/*
		@name GetRightBottomControlName
		@desc ��ȡ���·ָ�ؼ�
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetRightBottomControlName() = 0;
		/*
		@name SetLimitLeftTopSize
		@desc �������Ͽؼ������ƴ�С
		@param size int ���ƴ�С
		@return void
		*/
		virtual void SetLimitLeftTopSize(int size) = 0;
		/*
		@name GetLimitLeftTopSize
		@desc ��ȡ���Ͽؼ������ƴ�С
		@param void
		@return int
		*/
		virtual int GetLimitLeftTopSize() = 0;
		/*
		@name SetLimitRightBottomSize
		@desc �������¿ؼ������ƴ�С
		@param size int ���ƴ�С
		@return void
		*/
		virtual void SetLimitRightBottomSize(int size) = 0;
		/*
		@name GetLimitRightBottomSize
		@desc ��ȡ���¿ؼ������ƴ�С
		@param void
		@return int
		*/
		virtual int GetLimitRightBottomSize() = 0;
	};

	class IUIGearsWindow
	{
	public:
		/*
		@name SetWinName
		@desc ���ô��������
		@param name  const tchar*  ��������
		@return void
		*/
		virtual void SetWinName(const tchar* name) = 0;
		/*
		@name GetWinName
		@desc ��ȡ���������
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetWinName() = 0;
		/*
		@name GetTypeName
		@desc ��ȡ��������
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetTypeName() = 0;
		/*
		@name GetButton
		@desc �������ƻ�ȡ��ť�ؼ�
		@param name  const tchar*  ��ť����
		@return IUIGButton*
		*/
		virtual IUIGButton* GetButton(const tchar* name) = 0;
		/*
		@name GetControl
		@desc �������ƻ�ȡ�ؼ�
		@param name  const tchar*  �ؼ�����
		@return IUIGearControl*
		*/
		virtual IUIGearsControl* GetControl(const tchar* name) = 0;
		/*
		@name ChangeTheme
		@desc �ı������ļ�
		@param themepath  const tchar*  �����ļ���Դ·��
		@return bool
		*/
		virtual bool ChangeTheme(const tchar* themePath) = 0;
		/*
		@name GetString
		@desc ���ݹؼ��ֻ�ȡ�ַ���
		@param key  const tchar*  �ؼ���
		@return const tchar*
		*/
		virtual const tchar* GetString(const tchar* key) = 0;
		/*
		@name CreateControl
		@desc ��̬�����ؼ�
		@param type UIGControlType �ؼ�����ö��
		@param pParent IUIGearsControl* ���ؼ�ָ��
		@param pName  const tchar*  �ؼ�����
		@param x int �ؼ���x����
		@param y int �ؼ���y����
		@param w int �ؼ��Ŀ��
		@param h int �ؼ��ĸ߶�
		@return IUIGearsControl*
		*/
		virtual IUIGearsControl* CreateControl(UIGControlType type, IUIGearsControl* pParent, const tchar* pName, int x, int y, int w, int h) = 0;
		/*
		@name CreatePopupMenu
		@desc ���������˵�
		@param pMenuConfig  const tchar*  �˵������ļ�����
		@param menuId int �˵���id��
		@return IUIGPopupMenu*
		*/
		virtual IUIGPopupMenu* CreatePopupMenu(const tchar* pMenuConfig, int menuId) = 0;
		/*
		@name Invalidate
		@desc �ػ洰��
		@param redrawNow bool �Ƿ������ػ棬����Ϊ�첽�ػ棬Ĭ�����첽
		@return void
		*/
		virtual void Invalidate(bool redrawNow = false) = 0;
		/*
		@name AppendEventReceiver
		@desc ����¼����ն���
		@param pDelegateObj IEventRecevier* �¼����ն���
		@return void
		*/
		virtual void AppendEventReceiver(IEventRecevier* pDelegateObj) = 0;
		/*
		@name RemoveEventReceiver
		@desc �Ƴ��¼����ն���
		@param pDelegateObj IEventRecevier* �¼����ն���
		@return void
		*/
		virtual void RemoveEventReceiver(IEventRecevier* pDelegateObj) = 0;
		/*
		@name RemoveAllEventReceiver
		@desc �Ƴ����������е��¼����ն���
		@param void
		@return void
		*/
		virtual void RemoveAllEventReceiver() = 0;
		/*
		@name GetChildrenCount
		@desc ��ȡ�������ӿؼ�����
		@param void
		@return int
		*/
		virtual int GetChildrenCount() = 0;
		/*
		@name GetControlByIndex
		@desc ����������ȡ�ӿؼ�
		@param index int ������
		@return IUIGearsControl*
		*/
		virtual IUIGearsControl* GetControlByIndex(int index) = 0;
		/*
		@name RemoveChild
		@desc ���ݿؼ�ָ��ɾ���ؼ�
		@param pEle IUIGearsControl* �ؼ�ָ��
		@return bool
		*/
		virtual bool RemoveChild(IUIGearsControl* pEle) = 0;
		/*
		@name GetWidth
		@desc ��ȡ������
		@param void
		@return int
		*/
		virtual int GetWidth() = 0;
		/*
		@name GetHeight
		@desc ��ȡ����߶�
		@param void
		@return int
		*/
		virtual int GetHeight() = 0;
		/*
		@name SetWidth
		@desc ���ô�����
		@param width int ���
		@return void
		*/
		virtual void SetWidth(int width) = 0;
		/*
		@name SetHeight
		@desc ���ô���߶�
		@param height int ���
		@return void
		*/
		virtual void SetHeight(int height) = 0;
		/*
		@name SetMinWidth
		@desc ���ô�����С���
		@param height int ��С���
		@return void
		*/
		virtual void SetMinWidth(int minWidth) = 0;
		/*
		@name SetMinHeight
		@desc ���ô�����С�߶�
		@param height int ��С���
		@return void
		*/
		virtual void SetMinHeight(int minHeight) = 0;
		/*
		@name GetMinWidth
		@desc ��ȡ������С�߶�
		@param void
		@return int
		*/
		virtual int GetMinWidth() = 0;
		/*
		@name GetMinHeight
		@desc  ��ȡ��С�߶�
		@param void
		@return int
		*/
		virtual int GetMinHeight() = 0;
		/*
		@name GetDBClickToMax
		@desc ��ѯ�Ƿ�����˫�����
		@param void
		@return int
		*/
		virtual bool GetDBClickToMax() = 0;
		/*
		@name SetDBClickToMax
		@desc �����Ƿ�����˫�����
		@param enable bool �Ƿ��������
		@return void
		*/
		virtual void SetDBClickToMax(bool enable) = 0;
		/*
		@name GetDBClickCaptionHeight
		@desc ��ȡ˫���������ĸ߶�
		@param void
		@return int
		*/
		virtual int GetDBClickCaptionHeight() = 0;
		/*
		@name SetDBClickCaptionHeight
		@desc ����˫���������ĸ߶�
		@param height int �������߶�
		@return void
		*/
		virtual void SetDBClickCaptionHeight(int height) = 0;
		/*
		@name GetCanResize
		@desc ��ȡ�Ƿ���Ե����߿��С
		@param void
		@return bool
		*/
		virtual bool GetCanResize() = 0;
		/*
		@name SetCanResize
		@desc �����Ƿ���������С
		@param enable bool �Ƿ���������С
		@return void
		*/
		virtual void SetCanResize(bool enable) = 0;
		/*
		@name GetIsTransparentWindow
		@desc ��ȡ�Ƿ�֧�ְ�͸������
		@param void
		@return bool
		*/
		virtual bool GetIsTransparentWindow() = 0;
		/*
		@name SetIsTransparentWindow
		@desc �����Ƿ�֧�ְ�͸������
		@param enable bool �Ƿ�֧�ְ�͸������
		@return void
		*/
		virtual void SetIsTransparentWindow(bool enable) = 0;
		/*
		@name GetCanDrag
		@desc ��ȡ�Ƿ�֧����ק����λ��
		@param void
		@return bool
		*/
		virtual bool GetCanDrag() = 0;
		/*
		@name SetCanDrag
		@desc ��ȡ�Ƿ�֧����ק����λ��
		@param enable bool �Ƿ�֧����ק
		@return void
		*/
		virtual void SetCanDrag(bool enable) = 0;
		/*
		@name GetOnlyDragOnCaption
		@desc ��ȡ�Ƿ�ֻ��ͨ����������ק�ı䴰��λ��
		@param void
		@return bool
		*/
		virtual bool GetOnlyDragOnCaption() = 0;
		/*
		@name SetOnlyDragOnCaption
		@desc �����Ƿ�ֻ��ͨ����������ק�ı䴰��λ��
		@param enable bool �Ƿ��
		@return void
		*/
		virtual void SetOnlyDragOnCaption(bool enable) = 0;

#ifdef MOBILE
		/*
		@name GetDeviceType
		@desc ��ȡ�豸����Ԥ��
		@param void
		@return DeviceType
		*/
		virtual DeviceType GetDeviceType() = 0;

		/*
		@name SetDeviceType
		@desc �����豸����Ԥ��
		@param type DeviceType �豸����Ԥ��
		@return void
		*/
		virtual void SetDeviceType(DeviceType type) = 0;

		virtual OrientationType GetOrientationType() = 0;
		virtual void SetOrientationType(OrientationType type) = 0;
		virtual void SetIsItemTemp(bool bUseItemTemp) = 0;
		virtual bool GetIsItemTemp() = 0;
		virtual void SetItemHeight(int itemHeight) = 0;
		virtual int GetItemHeight() = 0;
#endif
	};

	typedef void (IUIGearsControl::*SetStyleFun)(UIGears::UIState, UIGears::IUIGearsStyle*);
	typedef void (IUIGearsControl::*SetStringFun)(const tchar*);
	typedef const tchar* (IUIGearsControl::*GetStringFun)(void);
	typedef void (IUIGearsControl::*SetBoolFun)(bool);
	typedef bool (IUIGearsControl::*GetBoolFun)(void);
	typedef void (IUIGearsControl::*SetNumFun)(int);
	typedef int (IUIGearsControl::*GetNumFun)(void);
	typedef void (IUIGearsControl::*Set2NumFun)(int, int);
	typedef void (IUIGearsControl::*Get2NumFun)(int&, int&);
	typedef void (IUIGearsControl::*SetStyleFun)(UIGears::UIState, UIGears::IUIGearsStyle*);
	typedef UIGears::IUIGearsStyle* (IUIGearsControl::*GetStyleFun)(UIGears::UIState);
	typedef void (IUIGearsControl::*SetStateStringFun)(UIGears::UIState, const tchar*);
	typedef const tchar* (IUIGearsControl::*GetStateStringFun)(UIGears::UIState);

	enum PropType
	{
		PT_EDIT,
		PT_EDIT_TRANSLATE,
		PT_STATIC,
		PT_CHECK,
		PT_LINE,
		PT_RECTSTYLE,
		PT_TEXTSTYLE,
		PT_IMAGESTYLE,
		PT_IMAGE,
		PT_NUM,
		PT_2NUM,
		PT_COMBO,
		PT_COLOR,
		PT_FAMILY
	};

	enum ResType
	{
		RT_DEFAULT = 0,
		RT_STYLE,
		RT_PROJECT
	};

	struct PropertyDef
	{
		std::tstring	name;
		int				type;
		SetStringFun	setStringFun;
		GetStringFun	getStringFun;
		SetBoolFun		setBoolFun;
		GetBoolFun		getBoolFun;
		SetStyleFun		setStyleFun;
		GetStyleFun		getStyleFun;
		SetStateStringFun setStateStringFun;
		GetStateStringFun getStateStringFun;
		GetNumFun		getNumFun;
		SetNumFun		setNumFun;
		Get2NumFun		get2NumFun;
		Set2NumFun		set2NumFun;
		IUIGearsControl*			control;
		std::vector<int>			vecStates;
		std::vector<std::tstring>	vecStatesName;
		bool			effectOtherProp;
		std::tstring	tip;
		PropertyDef()
		{
			effectOtherProp = false;
			control = NULL;
			setStringFun = NULL;
			getStringFun = NULL;
			setBoolFun = NULL;
			getBoolFun = NULL;
			setStyleFun = NULL;
			getStyleFun = NULL;
			getNumFun = NULL;
			setNumFun = NULL;
			get2NumFun = NULL;
			set2NumFun = NULL;
			getStateStringFun = NULL;
			setStateStringFun = NULL;
		}
	};

	struct EventInfo
	{
		std::tstring					eventName;
		std::tstring					helpString;
		std::vector<std::tstring>		parameterName;
	};

	struct ControlInfo
	{
		bool						displayInControl;
		std::string					typeName;
		std::string					className;
		std::tstring				displayName;
		const char*					iconData;
		std::tstring				descrption;
		std::vector<PropertyDef>	props;
		std::vector<EventInfo>		events;
		void*						bigImg;
		unsigned int				imgLen;
		void*						smallImg;
		unsigned int				simgLen;
		ControlInfo()
		{
			displayInControl = true;
			iconData = 0;
			bigImg = 0;
			imgLen = 0;
			smallImg = 0;
			simgLen = 0;
		}
	};

	typedef void(*EventCallBackFun)(int msgId, void* control, void* ctrlPtr, void* wParam, void* lParam);
	typedef void* (*CreateControlFun)();

	UIGEARS_API IUIGearsStyle** GetStyle(StyleType type, int& count, ResType resType = RT_STYLE);

	UIGEARS_API IUIGearsStyle* CreateNewStyle(StyleType type, const tchar* name, ResType resType = RT_STYLE);

	UIGEARS_API IUIGearsStyle*	GetStyleByName(StyleType type, const tchar* name, ResType resType = RT_STYLE);

	UIGEARS_API bool RemoveStyle(StyleType type, const tchar* name, ResType resType = RT_STYLE);

	UIGEARS_API bool InitUIGears(const tchar* skinRootPath = NULL);

	UIGEARS_API bool SetCurrentLanguage(const tchar* languageName);

	UIGEARS_API bool UpdateProjectLanguageFile();

	UIGEARS_API bool ShutdownUIGears();

	UIGEARS_API void SetEnableMiniDump(bool enable);

	UIGEARS_API void SetNeedTouch(bool needTouch);

	UIGEARS_API IUIGearsWindow* CreateUIGearsWin(void* handle);

	UIGEARS_API IUIGearsWindow* CreateUIGearsWinByName(const tchar* fileName, void* handle);

	UIGEARS_API std::vector<ControlInfo> GetRegisterControlInfo();

	UIGEARS_API IUIGearsControl* GetControlByName(IUIGearsWindow* winPtr, const tchar* controlName);

	UIGEARS_API const tchar* GetControlTypeName(IUIGearsControl* ctrl);

	UIGEARS_API void* ExecuteControlMethod(IUIGearsControl* ctrl, int methodId, void** param, int size);

	UIGEARS_API void* RegisterControlEventObj(IUIGearsControl* ctrl, EventCallBackFun callBack);

	UIGEARS_API bool UIGRegisterControl(const char* typeName, CreateControlFun fun, int id, UIGears::ControlInfo* info);

	UIGEARS_API void ImportImageRes(const tchar* dllName, const char* resName, int id);

	UIGEARS_API void ImportElementConfig(const tchar* dllName, int id);

	UIGEARS_API void ImportStyleConfig(const tchar* dllName, int id);

	UIGEARS_API const tchar* GetString(const tchar* key);
}

#endif