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
		@desc 获取布局类型
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
		@desc 获取水平偏移量
		@param void
		@return int
		*/
		virtual int GetOffsetX() = 0;
		/*
		@name GetOffsetY
		@desc 获取垂直偏移量
		@param void
		@return int
		*/
		virtual int GetOffsetY() = 0;
		/*
		@name SetOffsetX
		@desc 设置水平偏移量
		@param x int 水平偏移量
		@return void
		*/
		virtual void SetOffsetX(int x) = 0;
		/*
		@name SetOffsetY
		@desc 设置垂直偏移量
		@param y int 垂直偏移量
		@return void
		*/
		virtual void SetOffsetY(int y) = 0;
		/*
		@name GetPercentW
		@desc 获取百分比宽度
		@param void
		@return int
		*/
		virtual int GetPercentW() = 0;
		/*
		@name GetPercentH
		@desc 获取百分比高度
		@param void
		@return int
		*/
		virtual int GetPercentH() = 0;
		/*
		@name SetPercentW
		@desc 设置百分比宽度
		@param x int 百分比宽度，输入50代表50%
		@return void
		*/
		virtual void SetPercentW(int x) = 0;
		/*
		@name SetPercentH
		@desc 设置百分比高度
		@param y int 百分比高度，输入50代表50%
		@return void
		*/
		virtual void SetPercentH(int y) = 0;
		/*
		@name GetPercentXType
		@desc 获取百分比水平偏移类型，可以为绝对坐标，或者百分比坐标
		@param void
		@return PercentOffsetType
		*/
		virtual PercentOffsetType GetPercentXType() = 0;
		/*
		@name GetPercentYType
		@desc 获取百分比垂直偏移类型，可以为绝对坐标，或者百分比坐标
		@param void
		@return PercentOffsetType
		*/
		virtual PercentOffsetType GetPercentYType() = 0;
		/*
		@name SetPercentXType
		@desc 设置百分比水平偏移类型，可以为绝对坐标，或者百分比坐标
		@param type PercentOffsetType 偏移类型
		@return void
		*/
		virtual void SetPercentXType(PercentOffsetType type) = 0;
		/*
		@name SetPercentYType
		@desc 设置百分比垂直偏移类型，可以为绝对坐标，或者百分比坐标
		@param type PercentOffsetType 偏移类型
		@return void
		*/
		virtual void SetPercentYType(PercentOffsetType type) = 0;
	};

	class IUIGearsDockLayout : public IUIGearsLayout {
	public:
		/*
		@name SetHorDockType
		@desc 设置水平停靠方向
		@param hor DockType 停靠方向
		@return void
		~
		enum DockType
		{
		UIG_DOCK_LEFTTOP = 0,  // 靠左或者靠上
		UIG_DOCK_CENTERMIDDLE, // 居中
		UIG_DOCK_RIGHTBOTTOM // 靠右或者靠下
		};
		~
		*/
		virtual void SetHorDockType(DockType hor) = 0;
		/*
		@name SetVerDockType
		@desc 设置垂直停靠方向
		@param hor DockType 停靠方向
		@return void
		~
		enum DockType
		{
		UIG_DOCK_LEFTTOP = 0,  // 靠左或者靠上
		UIG_DOCK_CENTERMIDDLE, // 居中
		UIG_DOCK_RIGHTBOTTOM // 靠右或者靠下
		};
		~
		*/
		virtual void SetVerDockType(DockType ver) = 0;
		/*
		@name GetHorDockType
		@desc 获取水平停靠方向
		@param void
		@return DockType
		~
		enum DockType
		{
		UIG_DOCK_LEFTTOP = 0,  // 靠左或者靠上
		UIG_DOCK_CENTERMIDDLE, // 居中
		UIG_DOCK_RIGHTBOTTOM // 靠右或者靠下
		};
		~
		*/
		virtual DockType GetHorDockType() = 0;
		/*
		@name GetVerDockType
		@desc 设置垂直停靠方向
		@param void
		@return DockType
		~
		enum DockType
		{
		UIG_DOCK_LEFTTOP = 0,  // 靠左或者靠上
		UIG_DOCK_CENTERMIDDLE, // 居中
		UIG_DOCK_RIGHTBOTTOM // 靠右或者靠下
		};
		~
		*/
		virtual DockType GetVerDockType() = 0;
		/*
		@name GetDockWidthType
		@desc 获取宽度类型
		@param void
		@return DockSizeType
		~
		enum DockSizeType
		{
		UIG_FIX_SIZE = 0, // 绝对值
		UIG_DOCK_SIZE // 停靠值
		};
		~
		*/
		virtual DockSizeType GetDockWidthType() = 0;
		/*
		@name GetDockWidthType
		@desc 获取高度类型
		@param void
		@return DockSizeType
		~
		enum DockSizeType
		{
		UIG_FIX_SIZE = 0, // 绝对值
		UIG_DOCK_SIZE // 停靠值
		};
		~
		*/
		virtual DockSizeType GetDockHeightType() = 0;
		/*
		@name SetDockWidthType
		@desc 设置宽度类型
		@param type DockSizeType 类型
		@return void
		*/
		virtual void SetDockWidthType(DockSizeType type) = 0;
		/*
		@name SetDockHeightType
		@desc 设置高度类型
		@param type DockSizeType 类型
		@return void
		*/
		virtual void SetDockHeightType(DockSizeType type) = 0;
		/*
		@name GetOffsetX
		@desc 获取水平偏移量
		@param void
		@return int
		*/
		virtual int GetOffsetX() = 0;
		/*
		@name GetOffsetY
		@desc 获取高度偏移量
		@param void
		@return int
		*/
		virtual int GetOffsetY() = 0;
		/*
		@name GetOffsetRight
		@desc 获取右侧偏移量
		@param void
		@return int
		*/
		virtual int GetOffsetRight() = 0;
		/*
		@name GetOffsetBottom
		@desc 获取底部偏移量
		@param void
		@return int
		*/
		virtual int GetOffsetBottom() = 0;
		/*
		@name SetOffsetX
		@desc 设置水平偏移量
		@param x int 偏移量
		@return void
		*/
		virtual void SetOffsetX(int x) = 0;
		/*
		@name SetOffsetY
		@desc 设置垂直偏移量
		@param y int 偏移量
		@return void
		*/
		virtual void SetOffsetY(int y) = 0;
		/*
		@name SetOffsetRight
		@desc 设置右侧偏移量
		@param r int 偏移量
		@return void
		*/
		virtual void SetOffsetRight(int r) = 0;
		/*
		@name SetOffsetBottom
		@desc 设置底部偏移量
		@param b int 偏移量
		@return void
		*/
		virtual void SetOffsetBottom(int b) = 0;
		/*
		@name SetFixWidth
		@desc 设置宽度绝对值
		@param w int 宽度值
		@return void
		*/
		virtual void SetFixWidth(int w) = 0;
		/*
		@name SetFixHeight
		@desc 设置高度绝对值
		@param h int 高度值
		@return void
		*/
		virtual void SetFixHeight(int h) = 0;
		/*
		@name GetFixWidth
		@desc 获取宽度绝对值
		@param void
		@return int
		*/
		virtual int GetFixWidth() = 0;
		/*
		@name GetFixHeight
		@desc 获取高度绝对值
		@param void
		@return int
		*/
		virtual int GetFixHeight() = 0;
	};

	class IUIGearsFillLayout : public IUIGearsLayout {
	public:
		/*
		@name SetMarginRight
		@desc 设置距离右侧大小
		@param r int 间隔距离
		@return void
		*/
		virtual void SetMarginRight(int r) = 0;
		/*
		@name SetMarginBottom
		@desc 设置距离下侧大小
		@param b int 间隔距离
		@return void
		*/
		virtual void SetMarginBottom(int b) = 0;
		/*
		@name SetMarginX
		@desc 设置距离左侧大小
		@param x int 间隔距离
		@return void
		*/
		virtual void SetMarginX(int x) = 0;
		/*
		@name SetMarginY
		@desc 设置距离上方大小
		@param y int 间隔距离
		@return void
		*/
		virtual void SetMarginY(int y) = 0;
		/*
		@name SetMarginOffset
		@desc 设置距离四周大小
		@param x int 左侧间隔大小
		@param y int 上侧间隔大小
		@param r int 右侧间隔大小
		@param b int 下侧间隔大小
		@return void
		*/
		virtual void SetMarginOffset(int x, int y, int r, int b) = 0;
		/*
		@name GetMarginX
		@desc 获取左侧间隔距离
		@param void
		@return int
		*/
		virtual int GetMarginX() = 0;
		/*
		@name GetMarginY
		@desc 获取上侧间隔距离
		@param void
		@return int
		*/
		virtual int GetMarginY() = 0;
		/*
		@name GetMarginY
		@desc 获取右侧间隔距离
		@param void
		@return int
		*/
		virtual int GetMarginRight() = 0;
		/*
		@name GetMarginY
		@desc 获取下侧间隔距离
		@param void
		@return int
		*/
		virtual int GetMarginBottom() = 0;
	};

	class IUIGearsStyle {
	public:
		/*
		@name GetStyleName
		@desc 获取样式名称
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetStyleName() = 0;
	};

	class IUIGearsRectStyle : public IUIGearsStyle {
	public:
		/*
		@name GetUseFill
		@desc 获取是否使用颜色填充
		@param void
		@return bool
		*/
		virtual bool GetUseFill() = 0;
		/*
		@name GetUseBorder
		@desc 获取是否绘制边框
		@param void
		@return bool
		*/
		virtual bool GetUseBorder() = 0;
		/*
		@name GetUserImage
		@desc 获取是否使用图片填充
		@param void
		@return bool
		*/
		virtual bool GetUserImage() = 0;
		/*
		@name SetUseFill
		@desc 设置是否使用颜色填充
		@param bUse bool 是否使用
		@return void
		*/
		virtual void SetUseFill(bool bUse) = 0;
		/*
		@name SetUseBorder
		@desc 设置是否填充边框
		@param bUse bool 是否使用
		@return void
		*/
		virtual void SetUseBorder(bool bUse) = 0;
		/*
		@name SetUserImage
		@desc 设置是否填充图片
		@param bUse bool 是否使用
		@return void
		*/
		virtual void SetUserImage(bool bUse) = 0;
		/*
		@name GetFillColor
		@desc 获取填充颜色
		@param void
		@return unsigned int
		*/
		virtual unsigned int GetFillColor() = 0;
		/*
		@name SetFillColor
		@desc 设置填充颜色
		@param color  unsigned int  颜色值
		@return void
		*/
		virtual void SetFillColor(unsigned int color) = 0;
		/*
		@name GetBorderColor
		@desc 获取边框颜色
		@param void
		@return unsigned int
		*/
		virtual unsigned int GetBorderColor() = 0;
		/*
		@name SetBorderColor
		@desc 设置边框颜色
		@param color  unsigned int  颜色值
		@return void
		*/
		virtual void SetBorderColor(unsigned int color) = 0;
		/*
		@name GetBorderSize
		@desc 获取边框大小
		@param void
		@return unsigned int
		*/
		virtual unsigned int GetBorderSize() = 0;
		/*
		@name SetBorderSize
		@desc 设置边框大小
		@param size  unsgined int  大小
		@return void
		*/
		virtual void SetBorderSize(unsigned int size) = 0;
		/*
		@name GetRoundSize
		@desc 获取圆角大小
		@param void
		@return unsigned int
		*/
		virtual unsigned int GetRoundSize() = 0;
		/*
		@name SetRoundSize
		@desc 设置圆角大小
		@param unsigned int 圆角大小
		@return void
		*/
		virtual void SetRoundSize(unsigned int size) = 0;
		/*
		@name SetImageName
		@desc 设置图片路径
		@param strImageName  const tchar*  图片路径
		@return void
		*/
		virtual void SetImageName(const tchar* strImageName) = 0;
		/*
		@name GetImageName
		@desc 获取图片路径
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetImageName() = 0;
		/*
		@name GetMargin
		@desc 获取九宫分割四周间隔
		@param left int& 左侧间隔
		@param top int& 上侧间隔
		@param right int& 右侧间隔
		@param bottom int& 下侧间隔
		@return void
		*/
		virtual void GetMargin(int& left, int& top, int& right, int& bottom) = 0;
		/*
		@name SetMargin
		@desc 设置九宫分割四周间隔
		@param left int 左侧间隔
		@param top int 上侧间隔
		@param right int 右侧间隔
		@param bottom int 下侧间隔
		@return void
		*/
		virtual void SetMargin(int left, int top, int right, int bottom) = 0;
		/*
		@name SetDrawBorder
		@desc 设置边框绘制
		@param left int 左侧边框
		@param top int 上侧边框
		@param right int 右侧边框
		@param bottom int 下侧边框
		@return void
		*/
		virtual void SetDrawBorder(bool left, bool top, bool right, bool bottom) = 0;
		/*
		@name GetDrawBorder
		@desc 获取边框绘制
		@param left int& 左侧边框
		@param top int& 上侧边框
		@param right int& 右侧边框
		@param bottom int& 下侧边框
		@return void
		*/
		virtual void GetDrawBorder(bool& left, bool& top, bool& right, bool& bottom) = 0;
		/*
		@name SetRepeatImage
		@desc 设置图片是平铺还是拉伸
		@param left bool 左侧图片
		@param top bool 上侧图片
		@param center bool 中央图片
		@param right bool 右侧图片
		@param bottom bool 下侧图片
		@return void
		*/
		virtual void SetRepeatImage(bool left, bool top, bool center, bool right, bool bottom) = 0;
		/*
		@name SetRepeatImage
		@desc 获取图片是平铺还是拉伸
		@param left bool& 左侧图片
		@param top bool& 上侧图片
		@param center bool& 中央图片
		@param right bool& 右侧图片
		@param bottom bool& 下侧图片
		@return void
		*/
		virtual void GetRepeatImage(bool& left, bool& top, bool& center, bool& right, bool& bottom) = 0;
	};

	class IUIGearsTextStyle : public IUIGearsStyle {
	public:
		/*
		@name GetStyleName
		@desc 获取样式名称
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetStyleName() = 0;
		/*
		@name GetFontColor
		@desc 获取字体颜色
		@param void
		@return int
		*/
		virtual int GetFontColor() = 0;
		/*
		@name SetFontColor
		@desc 设置字体颜色
		@param clr int 颜色
		@return void
		*/
		virtual void SetFontColor(int clr) = 0;
		/*
		@name GetFontSize
		@desc 获取字体颜色
		@param void
		@return int
		*/
		virtual int GetFontSize() = 0;
		/*
		@name SetFontSize
		@desc 获取字体大小
		@param void
		@return int
		*/
		virtual void SetFontSize(int size) = 0;
		/*
		@name SetOffsetX
		@desc 设置左侧偏移量
		@param offsetX int 偏移量
		@return void
		*/
		virtual void SetOffsetX(int offsetX) = 0;
		/*
		@name GetOffsetX
		@desc 获取左侧偏移量
		@param void
		@return int
		*/
		virtual int GetOffsetX() = 0;
		/*
		@name SetOffsetY
		@desc 设置垂直偏移量
		@param offsetY int 偏移量
		@return void
		*/
		virtual void SetOffsetY(int offsetY) = 0;
		/*
		@name GetOffsetY
		@desc 获取垂直偏移量
		@param void
		@return int
		*/
		virtual int GetOffsetY() = 0;
		/*
		@name SetBold
		@desc 设置是否加粗
		@param bold bool 加粗
		@return void
		*/
		virtual void SetBold(bool bold) = 0;
		/*
		@name GetBold
		@desc 获取是否加粗
		@param void
		@return bool
		*/
		virtual bool GetBold() = 0;
		/*
		@name SetItalic
		@desc 设置是否斜体
		@param italic bool 斜体
		@return void
		*/
		virtual void SetItalic(bool italic) = 0;
		/*
		@name GetItalic
		@desc 获取是否斜体
		@param void
		@return bool
		*/
		virtual bool GetItalic() = 0;
		/*
		@name SetHorAlign
		@desc 设置水平对齐方式
		@param align FontAlign 对齐方式
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
		@desc 获取水平对齐方式
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
		@desc 设置垂直对齐方式
		@param align FontAlign 对齐方式
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
		@desc 获取垂直对齐方式
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
		@desc 设置是否单行显示
		@param singleLine bool 是否单行显示
		@return void
		*/
		virtual void SetSingleLine(bool singleLine) = 0;
		/*
		@name GetSingleLine
		@desc 获取是否单行显示
		@param void
		@return bool
		*/
		virtual bool GetSingleLine() = 0;
		/*
		@name SetUnderline
		@desc 设置是否有下划线
		@param bool underline 下划线
		@return void
		*/
		virtual void SetUnderline(bool underline) = 0;
		/*
		@name GetUnderline
		@desc 获取是否有下划线
		@param void
		@return bool
		*/
		virtual bool GetUnderline() = 0;
		/*
		@name GetFontFamily
		@desc 获取字体
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetFontFamily() = 0;
		/*
		@name GetFontFamilyA
		@desc 获取字体，返回值为char
		@param void
		@return const char*
		*/
		virtual const char* GetFontFamilyA() = 0;
		/*
		@name SetFontFamily
		@desc 设置字体
		@param family  const tchar*  字体名称
		@return void
		*/
		virtual void SetFontFamily(const tchar* family) = 0;
		/*
		@name GetIsLCD
		@desc 获取字体，返回值为char
		@param void
		@return const char*
		*/
		virtual bool GetIsLCD() = 0;
		/*
		@name SetIsLCD
		@desc 设置字体
		@param family  const tchar*  字体名称
		@return void
		*/
		virtual void SetIsLCD(bool isLCD  ) = 0;
	};

	class IUIGearsControl {
	public:
		/*
		@name Invalidate
		@desc 重新绘制控件,注意：此操作为异步操作
		@param void
		@return void
		*/
		virtual void Invalidate() = 0;
		/*
		@name Invalidate
		@desc 重新绘制控件,注意：此操作为异步操作,对窗口指定区域进行重绘，指定的位置为窗口上的绝对坐标位置，左上角为0,0， 右下角为窗口的宽度，高度。
		@param x int 左侧位置
		@param y int 上侧位置
		@param w int 重绘宽度
		@param h int 重绘高度
		@return void
		*/
		virtual void Invalidate(int x, int y, int w, int h) = 0;
		/*
		@name Resize
		@desc 重新计算控件及其内部子控件的位置和大小，注意：此操作为异步操作，不会立即执行
		@param void
		@return void
		*/
		virtual void Resize() = 0;
		/*
		@name ResizeSync
		@desc 立即计算控件的及其子控件的位置和大小,注意：此操作为同步操作，立即执行大小计算
		@param void
		@return void
		*/
		virtual void ResizeSync() = 0;
		/*
		@name AppendEventReceiver
		@desc 给控件设置事件接收器，可以给控件设置多个事件接收器
		@param pDelegateObj IEventRecevier* 事件接收器指针
		@return void
		*/
		virtual void AppendEventReceiver(IEventRecevier* pDelegateObj) = 0;
		/*
		@name RemoveEventReceiver
		@desc 将控件的某个事件处理器移除掉
		@param pDelegateObj IEventRecevier* 事件接收器指针
		@return void
		*/
		virtual void RemoveEventReceiver(IEventRecevier* pDelegateObj) = 0;
		/*
		@name RemoveAllEventReceiver
		@desc 将控件的所有的事件处理器移除掉
		@param void
		@return void
		*/
		virtual void RemoveAllEventReceiver() = 0;
		/*
		@name SetVisibility
		@desc 设置控件是否显示
		@param visibility bool 是否显示
		@return void
		*/
		virtual void SetVisibility(bool visibility) = 0;
		/*
		@name GetVisibility
		@desc 获取控件的显示状态
		@param void
		@return bool
		*/
		virtual bool GetVisibility() = 0;
		/*
		@name SetEnable
		@desc 设置控件是否启用，如果为false则禁用控件，用户将不可点击该控件，所有的控件高亮按下等状态也会禁用
		@param enable bool 是否启用
		@return void
		*/
		virtual void SetEnable(bool enable) = 0;
		/*
		@name GetEnable
		@desc 获取控件的启用状态
		@param void
		@return bool
		*/
		virtual bool GetEnable() = 0;
		/*
		@name SetRect
		@desc 设置控件的坐标位置，该坐标为相对于窗口的坐标，左上角为0,0
		@param x int 左侧位置
		@param y int 上侧位置
		@param w int 控件宽度
		@param h int 控件高度
		@return bool
		*/
		virtual void SetRect(int x, int y, int w, int h) = 0;
		/*
		@name GetControlByName
		@desc 根据名称获取子控件
		@param name  const tchar*  控件名称
		@return UIGears::IUIGearsControl*
		*/
		virtual IUIGearsControl* GetControlByName(const tchar* name) = 0;
		/*
		@name GetWindowX
		@desc 获取控件在窗口上的X轴坐标位置
		@param void
		@return int
		*/
		virtual int GetWindowX() = 0;
		/*
		@name GetWindowY
		@desc 获取控件在窗口上的Y轴坐标位置
		@param void
		@return int
		*/
		virtual int GetWindowY() = 0;
		/*
		@name GetX
		@desc 获取控件在父控件上的X轴坐标位置
		@param void
		@return int
		*/
		virtual int GetX() = 0;
		/*
		@name GetY
		@desc 获取控件在父控件上的Y轴坐标位置
		@param void
		@return int
		*/
		virtual int GetY() = 0;
		/*
		@name GetWidth
		@desc 获取控件的宽度
		@param void
		@return int
		*/
		virtual int GetWidth() = 0;
		/*
		@name GetHeight
		@desc 获取控件的高度
		@param void
		@return int
		*/
		virtual int GetHeight() = 0;
		/*
		@name SetX
		@desc 设置控件距离父控件左侧的距离
		@param x int 距离左侧的距离
		@return void
		*/
		virtual void SetX(int x) = 0;
		/*
		@name SetY
		@desc 设置控件距离父控件上方的距离
		@param y int 距离上侧的距离
		@return void
		*/
		virtual void SetY(int y) = 0;
		/*
		@name SetWidth
		@desc 设置控件宽度
		@param w int 控件宽度
		@return void
		*/
		virtual void SetWidth(int w) = 0;
		/*
		@name SetHeight
		@desc 设置控件的高度
		@param h int 控件高度
		@return void
		*/
		virtual void SetHeight(int h) = 0;
		/*
		@name GetWindowPos
		@desc 获取控件在窗口上的位置
		@param x int& 控件x坐标位置
		@param y int& 控件y坐标位置
		@return void
		*/
		virtual void GetWindowPos(int& x, int& y) = 0;
		/*
		@name GetLayout
		@desc 获取控件的布局对象,注意：如果该控件使用的是绝对布局，那么获取到的布局对象为空
		@param void
		@return IUIGearsLayout*
		*/
		virtual IUIGearsLayout* GetLayout() = 0;
		/*
		@name SetLayout
		@desc 给控件设置布局对象，如果设置为NULL代表使用绝对布局
		@param UIGLayoutType type
		@return IUIGearsLayout*
		*/
		virtual IUIGearsLayout* SetLayout(UIGLayoutType type) = 0;
		/*
		@name GetChildrenCount
		@desc 获取该控件的子控件数量
		@param void
		@return int
		*/
		virtual int GetChildrenCount() = 0;
		/*
		@name GetControlByIndex
		@desc 通过索引号获取子控件
		@param index int 索引号
		@return IUIGearsControl*
		*/
		virtual IUIGearsControl* GetControlByIndex(int index) = 0;
		/*
		@name RemoveChild
		@desc 删除子控件
		@param index int 子控件的索引号，不能超过子控件的数量
		@return bool
		*/
		virtual bool RemoveChild(IUIGearsControl* pEle) = 0;
		/*
		@name RemoveChild
		@desc 获取控件的名称
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetControlName() = 0;
		/*
		@name GetControlTypeName
		@desc 获取控件的类型名称
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetControlTypeName() = 0;
		/*
		@name SetControlName
		@desc 修改控件的名称
		@param name  const tchar*  控件新的名称
		@return void
		*/
		virtual void SetControlName(const tchar* name) = 0;
		/*
		@name SetUserData
		@desc 设置一个用户自定义数据
		@param data PARAM 用户数据
		@return void
		*/
		virtual void SetUserData(PARAM data) = 0;
		/*
		@name GetUserData
		@desc 获取用户自定义数据
		@param void
		@return PARAM
		*/
		virtual PARAM GetUserData() = 0;
		/*
		@name GetParentControl
		@desc 获取父控件的指针
		@param void
		@return UIGears::IUIGearsControl*
		*/
		virtual IUIGearsControl* GetParentControl() = 0;
		/*
		@name GetTooltip
		@desc 获取控件的Tooltip文本
		@param void
		@return const tchar* 
		*/
		virtual const tchar* GetTooltip() = 0;
		/*
		@name GetTooltip
		@desc 设置控件的Tooltip文本
		@param tooltip const tchar* tooltip文本
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
		@desc 将当前控件和子控件拷贝到指定控件下
		@param name  const tchar*  新控件名称
		@param pParent UIGears::IUIGearsControl* 父控件指针
		@param insertPos int 在父控件的位置，默认值-1，即插入到父控件的末尾控件
		@return UIGears::IUIGearsControl* 返回新拷贝出来的控件
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
		@desc 设置按钮文本内容
		@param text  const tchar*  按钮文本内容
		@return void
		*/
		virtual void SetText(const tchar* text) = 0;
		/*
		@name GetText
		@desc 获取按钮文本内容
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetText() = 0;
		/*
		@name SetIcon
		@desc 设置按钮图标
		@param iconPath  const tchar*  图标路径
		@return void
		*/
		virtual void SetIcon(const tchar* iconPath) = 0;
		/*
		@name GetIcon
		@desc 获取按钮图标路径
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetIcon() = 0;
		/*
		@name SetHotIcon
		@desc 设置按钮高亮状态图标
		@param iconPath  const tchar*  图标路径
		@return void
		*/
		virtual void SetHotIcon(const tchar* iconPath) = 0;
		/*
		@name GetHotIcon
		@desc 获取按钮高亮状态图标路径
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetHotIcon() = 0;
		/*
		@name SetUseIcon
		@desc 获取是否显示图标
		@param use bool 是否显示图标
		@return void
		*/
		virtual void SetUseIcon(bool use) = 0;
		/*
		@name GetUseIcon
		@desc 获取是否显示图标
		@param void
		@return bool
		*/
		virtual bool GetUseIcon() = 0;
		/*
		@name SetTextX
		@desc 设置按钮文字水平偏移量
		@param x int 偏移量
		@return void
		*/
		virtual void SetTextX(int x) = 0;
		/*
		@name GetTextX
		@desc 获取按钮文字水平偏移量
		@param void
		@return int
		*/
		virtual int GetTextX() = 0;
		/*
		@name SetTextY
		@desc 设置按钮文字垂直偏移量
		@param y int 偏移量
		@return void
		*/
		virtual void SetTextY(int y) = 0;
		/*
		@name GetTextY
		@desc 获取按钮文字垂直偏移量
		@param void
		@return int
		*/
		virtual int GetTextY() = 0;
		/*
		@name SetShowText
		@desc 设置是否显示文本
		@param show bool 是否显示文本
		@return void
		*/
		virtual void SetShowText(bool show) = 0;
		/*
		@name GetShowText
		@desc 获取是否显示文本
		@param void
		@return bool
		*/
		virtual bool GetShowText() = 0;
		/*
		@name SetBackgroundStyle
		@desc 设置背景样式
		@param state UIState 状态枚举
		@param style IUIGearsRectStyle* 状态对象指针
		@return bool
		*/
		virtual bool SetBackgroundStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc 获取背景样式
		@param state UIState 状态枚举
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UIState state) = 0;
		/*
		@name SetTextStyle
		@desc 设置文字样式
		@param state UIState 状态枚举
		@param style IUIGearsRectStyle* 文字样式指针
		@return bool
		*/
		virtual bool SetTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetTextStyle
		@desc 获取文字样式
		@param state UIState 状态枚举
		@return IUIGearsTextStyle*
		*/
		virtual IUIGearsTextStyle* GetTextStyle(UIState state) = 0;
		/*
		@name SetIconHorDockType
		@desc 设置图标水平停靠类型
		@param dock DockType 对齐方式枚举
		@return void
		*/
		virtual void SetIconHorDockType(DockType dock) = 0;
		/*
		@name GetIconHorDockType
		@desc 获取图标水平停靠类型
		@param void
		@return DockType
		*/
		virtual DockType GetIconHorDockType() = 0;
		/*
		@name SetIconVerDockType
		@desc 设置图标垂直停靠类型
		@param dock DockType 对齐方式枚举
		@return DockType
		*/
		virtual void SetIconVerDockType(DockType dock) = 0;
		/*
		@name GetIconVerDockType
		@desc 获取图标垂直停靠类型
		@param void
		@return DockType
		*/
		virtual DockType GetIconVerDockType() = 0;
		/*
		@name SetIconX
		@desc 设置图标垂直偏移量
		@param x int 偏移量
		@return void
		*/
		virtual void SetIconX(int x) = 0;
		/*
		@name GetIconX
		@desc 获取图标水平偏移量
		@param void
		@return int
		*/
		virtual int GetIconX() = 0;
		/*
		@name SetIconY
		@desc 设置图标垂直偏移量
		@param y int 偏移量
		@return void
		*/
		virtual void SetIconY(int y) = 0;
		/*
		@name GetIconY
		@desc 获取图标垂直偏移量
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
		@desc 设置显示文本内容
		@param type  const tchar*  文本内容
		@return void
		*/
		virtual void SetText(const tchar* text) = 0;
		/*
		@name GetText
		@desc 获取显示文本内容
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetText() = 0;
		/*
		@name SetShowText
		@desc 设置是否显示文本
		@param show bool 是否显示文本
		@return void
		*/
		virtual void SetShowText(bool show) = 0;
		/*
		@name GetShowText
		@desc 获取是否显示文本
		@param void
		@return bool
		*/
		virtual bool GetShowText() = 0;
		/*
		@name SetLineOffset
		@desc 设置线和四周的间隔
		@param offset int 间隔大小
		@return void
		*/
		virtual void SetLineOffset(int offset) = 0;
		/*
		@name GetLineOffset
		@desc 获取线和四周的间隔
		@param void
		@return int
		*/
		virtual int GetLineOffset() = 0;
		/*
		@name SetLineColor
		@desc 设置线的颜色
		@param color int 颜色值，比如0xffff0000
		@return void
		*/
		virtual void SetLineColor(int color) = 0;
		/*
		@name GetLineColor
		@desc 获取线的颜色
		@param void
		@return int 颜色值，比如0xffff0000
		*/
		virtual int GetLineColor() = 0;
		/*
		@name SetLineSize
		@desc 设置线的粗细
		@param size int 粗细像素值
		@return void
		*/
		virtual void SetLineSize(int size) = 0;
		/*
		@name GetLineSize
		@desc 获取线的粗细
		@param void
		@return int 粗细像素值
		*/
		virtual int GetLineSize() = 0;
		/*
		@name SetTextPosition
		@desc 设置文字的对齐位置
		@param pos GB_POSITION 对齐枚举
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
		@desc 获取文字的对齐位置
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
		@desc 设置背景样式
		@param state UICommonState 状态枚举
		@param style IUIGearsRectStyle* 样式指针
		@return bool 是否成功
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
		@desc 获取背景样式
		@param state UICommonState 状态枚举
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UICommonState state) = 0;
		/*
		@name SetTextStyle
		@desc 设置文字样式
		@param state UICommonState 状态枚举
		@param style IUIGearsRectStyle* 文字指针
		@return bool 是否成功
		*/
		virtual bool SetTextStyle(UICommonState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc 获取文字样式
		@param state UICommonState 状态枚举
		@return IUIGearsTextStyle*
		*/
		virtual IUIGearsTextStyle* GetTextStyle(UICommonState state) = 0;
	};

	class IUIGTab : public IUIGearsControl
	{
	public:
		/*
		@name AppendItem
		@desc 添加item项目
		@param text  const tchar*  文本内容
		@return bool
		*/
		virtual bool AppendItem(const tchar* text) = 0;
		/*
		@name SetSelectedItem
		@desc 设置选中item
		@param index int 索引号
		@return bool
		*/
		virtual bool SetSelectedItem(int index) = 0;
		/*
		@name GetSelectedItem
		@desc 获取选中item
		@param void
		@return int
		*/
		virtual int GetSelectedItem() = 0;
		/*
		@name GetItemText
		@desc 根据索引获取item的文本
		@param index int 索引号
		@return const tchar*
		*/
		virtual const tchar* GetItemText(int index) = 0;
		/*
		@name SetItemData
		@desc 设置item的data数据
		@param index int 索引号
		@param data PARAM data数据
		@return void
		*/
		virtual void SetItemData(int index, PARAM data) = 0;
		/*
		@name GetItemData
		@desc 获取item的数据
		@param index int 索引号
		@return PARAM
		*/
		virtual PARAM GetItemData(int index) = 0;
		/*
		@name GetItemCount
		@desc 获取item的数量
		@param void
		@return int
		*/
		virtual int GetItemCount() = 0;
		/*
		@name GetIsHorizontal
		@desc 获取是否是水平显示
		@param void
		@return bool
		*/
		virtual bool GetIsHorizontal() = 0;
		/*
		@name SetIsHorizontal
		@desc 设置是否是水平显示
		@param isHor bool 是否水平显示
		@return void
		*/
		virtual void SetIsHorizontal(bool isHor) = 0;
		/*
		@name SetItemSize
		@desc 设置item的宽度或者高度
		@param size int 大小
		@return void
		*/
		virtual void SetItemSize(int size) = 0;
		/*
		@name GetItemSize
		@desc 获取item的宽度或者高度
		@param void
		@return int
		*/
		virtual int GetItemSize() = 0;
		/*
		@name SetShowText
		@desc 设置是否显示文字
		@param showText bool 是否显示文字
		@return void
		*/
		virtual void SetShowText(bool showText) = 0;
		/*
		@name GetShowText
		@desc 查询是否显示文字
		@param void
		@return bool
		*/
		virtual bool GetShowText() = 0;
		/*
		@name SetShowIcon
		@desc 设置是否显示图标
		@param showIcon bool 是否显示图标
		@return void
		*/
		virtual void SetShowIcon(bool showIcon) = 0;
		/*
		@name GetShowIcon
		@desc 查询是否显示图标
		@param void
		@return bool
		*/
		virtual bool GetShowIcon() = 0;
		/*
		@name SetItemSpace
		@desc 设置item的间隔
		@param space int 间隔大小
		@return void
		*/
		virtual void SetItemSpace(int space) = 0;
		/*
		@name GetItemSpace
		@desc 获取item的间隔
		@param void
		@return int
		*/
		virtual int GetItemSpace() = 0;
		/*
		@name SetBackgroundStyle
		@desc 设置背景样式
		@param state UICommonState 状态枚举
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetBackgroundStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc 获取背景样式
		@param state UICommonState 状态枚举
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UICommonState state) = 0;
		/*
		@name SetItemStyle
		@desc 设置item背景样式
		@param state UICommonState 状态枚举
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetItemStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetItemStyle
		@desc 获取item背景样式
		@param state UICommonState 状态枚举
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetItemStyle(UIState state) = 0;
		/*
		@name SetTextStyle
		@desc 设置item文字样式
		@param state UICommonState 状态枚举
		@param style IUIGearsTextStyle* 样式指针
		@return bool
		*/
		virtual bool SetTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetTextStyle
		@desc 获取item文字样式
		@param state UICommonState 状态枚举
		@return IUIGearsTextStyle*
		*/
		virtual IUIGearsTextStyle* GetTextStyle(UIState state) = 0;
		/*
		@name RemoveAll
		@desc 删除所有的items
		@param void
		@return void
		*/
		virtual void RemoveAll() = 0;
		/*
		@name RemoveItem
		@desc 根据索引删除item
		@param index  unsigned int  索引号
		@return bool
		*/
		virtual bool RemoveItem(unsigned int index) = 0;
	};

	class IUIGCheckBox : public IUIGearsControl
	{
	public:
		/*
		@name IsChecked
		@desc 是否选中
		@param void
		@return bool   是否选中
		*/
		virtual bool IsChecked() = 0;
		/*
		@name SetChecked
		@desc 设置是否选中
		@param bCheck  bool  是否选中
		@return void
		*/
		virtual void SetChecked(bool bCheck) = 0;
		/*
		@name SetText
		@desc 设置文本
		@param text  const tchar*  是否选中
		@return void
		*/
		virtual void SetText(const tchar* text) = 0;
		/*
		@name GetText
		@desc 获取文本
		@param void
		@return const tchar* 文本内容
		*/
		virtual const tchar* GetText() = 0;
		/*
		@name SetShowText
		@desc 设置是否显示文本
		@param show   bool  是否显示文本
		@return void
		*/
		virtual void SetShowText(bool show) = 0;
		/*
		@name GetShowText
		@desc 获取是否显示文本
		@param void
		@return bool 是否显示
		*/
		virtual bool GetShowText() = 0;
		/*
		@name SetShowIcon
		@desc 设置是否显示图标
		@param show  bool  是否显示
		@return void
		*/
		virtual void SetShowIcon(bool show) = 0;
		/*
		@name GetShowIcon
		@desc 获取是否显示图标
		@param void
		@return bool 是否显示
		*/
		virtual bool GetShowIcon() = 0;
		/*
		@name SetUncheckIcon
		@desc 设置未选中图标
		@param iconPath  const tchar*  图标路径
		@return bool 是否成功
		*/
		virtual bool SetUncheckIcon(const tchar* iconPath) = 0;
		/*
		@name GetUncheckIcon
		@desc 获取未选中图标
		@param void
		@return const tchar* 图标路径，此路径不是绝对路径，为资源包内路径
		*/
		virtual const tchar* GetUncheckIcon() = 0;
		/*
		@name SetCheckedIcon
		@desc 设置选中图标
		@param iconPath  const tchar*  图标路径
		@return bool 是否成功
		*/
		virtual bool SetCheckedIcon(const tchar* iconPath) = 0;
		/*
		@name GetCheckedIcon
		@desc 获取选中图标
		@param void
		@return const tchar* 图标路径，此路径不是绝对路径，为资源包内路径
		*/
		virtual const tchar* GetCheckedIcon() = 0;
		/*
		@name SetUncheckHotIcon
		@desc 设置未选中高亮图标
		@param iconPath  const tchar*  图标路径
		@return bool 是否成功
		*/
		virtual bool SetUncheckHotIcon(const tchar* iconPath) = 0;
		/*
		@name GetUncheckHotIcon
		@desc 获取未选中高亮图标
		@param void
		@return const tchar* 图标路径，此路径不是绝对路径，为资源包内路径
		*/
		virtual const tchar* GetUncheckHotIcon() = 0;
		/*
		@name SetCheckedHotIcon
		@desc 设置选中高亮图标
		@param iconPath  const tchar*  图标路径
		@return bool 是否成功
		*/
		virtual bool SetCheckedHotIcon(const tchar* iconPath) = 0;
		/*
		@name GetUncheckHotIcon
		@desc 获取选中高亮图标
		@param void
		@return const tchar* 图标路径，此路径不是绝对路径，为资源包内路径
		*/
		virtual const tchar* GetCheckedHotIcon() = 0;
		/*
		@name SetCheckedHotIcon
		@desc 设置禁用图标
		@param iconPath  const tchar*  图标路径
		@return bool 是否成功
		*/
		virtual bool SetDisableIcon(const tchar* iconPath) = 0;
		/*
		@name GetDisableIcon
		@desc 获取禁用图标
		@param void
		@return const tchar* 图标路径，此路径不是绝对路径，为资源包内路径
		*/
		virtual const tchar* GetDisableIcon() = 0;
		/*
		@name SetBackgroundStyle
		@desc 设置背景样式
		@param state  CBK_UIState  状态枚举
		@param style  IUIGearsTextStyle*  样式指针
		@return bool 是否成功
		*/
		virtual bool SetBackgroundStyle(CBK_UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc 获取背景样式
		@param state  CBK_UIState  状态枚举
		@return IUIGearsRectStyle* 图标路径样式指针
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(CBK_UIState state) = 0;
		/*
		@name SetTextStyle
		@desc 设置文字样式
		@param state  CBK_UIState  状态枚举
		@param style  IUIGearsTextStyle*  样式指针
		@return bool 是否成功
		*/
		virtual bool SetTextStyle(CBK_UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetTextStyle
		@desc 获取文字样式
		@param state  CBK_UIState  状态枚举
		@return IUIGearsTextStyle* 样式指针
		*/
		virtual IUIGearsTextStyle* GetTextStyle(CBK_UIState state) = 0;
		/*
		@name SetIconHorAlign
		@desc 设置图标水平对齐方式
		@param type  DockType  对齐方式枚举
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
		@desc 获取图标水平对齐方式
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
		@desc 设置图标垂直对齐方式
		@param type  DockType  对齐方式枚举
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
		@desc 获取图标垂直对齐方式
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
		@desc 设置图标水平偏移量
		@param x  int  水平偏移量
		@return void
		*/
		virtual void SetIconOffsetX(int x) = 0;
		/*
		@name GetIconOffsetX
		@desc 获取图标水平偏移量
		@param void
		@return int 水平偏移量
		*/
		virtual int GetIconOffsetX() = 0;
		/*
		@name SetIconOffsetY
		@desc 设置图标垂直偏移量
		@param x  int  水平偏移量
		@return void
		*/
		virtual void SetIconOffsetY(int y) = 0;
		/*
		@name GetIconOffsetY
		@desc 获取图标垂直偏移量
		@param void
		@return int 垂直偏移量
		*/
		virtual int GetIconOffsetY() = 0;
		/*
		@name SetAlignTextToLeft
		@desc 设置文字是否从最左侧开始对齐显示
		@param alignLeft bool 是否从最左侧开始对齐显示
		@return void
		*/
		virtual void SetAlignTextToLeft(bool alignLeft) = 0;
		/*
		@name GetAlignTextToLeft
		@desc 获取文字是否从最左侧开始对齐显示
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
		@desc 是否选中
		@param void
		@return bool
		*/
		virtual bool IsSelected() = 0;
		/*
		@name SetSelected
		@desc 设置是否选中
		@param bSelected bool 是否选中
		@return bool
		*/
		virtual void SetSelected(bool bSelected) = 0;
		/*
		@name GetId
		@desc 获取分组id
		@param void
		@return unsigned int
		*/
		virtual unsigned int GetId() = 0;
		/*
		@name SetId
		@desc 设置分组id
		@param id  int  unsigned int
		@return unsigned int
		*/
		virtual void SetId(unsigned int id) = 0;
		/*
		@name SetBackgroundStyle
		@desc 设置背景样式
		@param state CBK_UIState 状态枚举
		@param style IUIGearsRectStyle* 样式指针
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
		@desc 获取背景样式
		@param state CBK_UIState 状态枚举
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(CBK_UIState state) = 0;
		/*
		@name SetTextStyle
		@desc 设置文字样式
		@param state CBK_UIState 状态枚举
		@param style IUIGearsTextStyle* 样式指针
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
		@desc 获取文字样式
		@param state CBK_UIState 状态枚举
		@return IUIGearsTextStyle*
		*/
		virtual IUIGearsTextStyle* GetTextStyle(CBK_UIState state) = 0;
		/*
		@name SetUnselectIcon
		@desc 设置未选中图标路径
		@param iconPath  const tchar*  图标路径
		@return void
		*/
		virtual void SetUnselectIcon(const tchar* iconPath) = 0;
		/*
		@name GetUnselectIcon
		@desc 获取未选中图标路径
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetUnselectIcon() = 0;
		/*
		@name SetSelectedIcon
		@desc 设置选中图标路径
		@param  iconPath  const tchar*  图标路径
		@return void
		*/
		virtual void SetSelectedIcon(const tchar* iconPath) = 0;
		/*
		@name GetSelectedIcon
		@desc 获取选中图标路径
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetSelectedIcon() = 0;
		/*
		@name SetDisableIcon
		@desc 设置禁用图标路径
		@param  iconPath  const tchar*  图标路径
		@return void
		*/
		virtual void SetDisableIcon(const tchar* iconPath) = 0;
		/*
		@name GetDisableIcon
		@desc 获取禁用图标路径
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetDisableIcon() = 0;
		/*
		@name SetShowText
		@desc 设置是否显示文本
		@param show bool 是否显示
		@return void
		*/
		virtual void SetShowText(bool show) = 0;
		/*
		@name GetShowText
		@desc 获取是否显示文本
		@param void
		@return bool
		*/
		virtual bool GetShowText() = 0;
		/*
		@name SetShowIcon
		@desc 获取是否显示图标
		@param show bool 是否显示
		@return void
		*/
		virtual void SetShowIcon(bool show) = 0;
		/*
		@name GetShowIcon
		@desc 获取是否显示图标
		@param void
		@return bool
		*/
		virtual bool GetShowIcon() = 0;
		/*
		@name SetText
		@desc 设置文本
		@param text  const tchar*  文本内容
		@return void
		*/
		virtual void SetText(const tchar* text) = 0;
		/*
		@name GetText
		@desc 获取文本
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetText() = 0;
		/*
		@name SetIconHorAlign
		@desc 设置图标水平对齐类型
		@param type DockType 对齐类型
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
		@desc 获取图标水平对齐类型
		@param void
		@return DockType
		*/
		virtual DockType GetIconHorAlign() = 0;
		/*
		@name SetIconVerAlign
		@desc 设置图标垂直对齐类型
		@param type DockType 对齐类型
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
		@desc 获取图标垂直对齐类型
		@param void
		@return DockType
		*/
		virtual DockType GetIconVerAlign() = 0;
		/*
		@name SetIconOffsetX
		@desc 设置图标水平偏移量
		@param x int 偏移量
		@return void
		*/
		virtual void SetIconOffsetX(int x) = 0;
		/*
		@name GetIconOffsetX
		@desc 获取图标水平偏移量
		@param void
		@return int
		*/
		virtual int GetIconOffsetX() = 0;
		/*
		@name SetIconOffsetX
		@desc 设置图标垂直偏移量
		@param x int 偏移量
		@return void
		*/
		virtual void SetIconOffsetY(int y) = 0;
		/*
		@name GetIconOffsetX
		@desc 获取图标垂直偏移量
		@param void
		@return int
		*/
		virtual int GetIconOffsetY() = 0;
		/*
		@name SetIconOffsetX
		@desc 设置图标是否最左侧显示
		@param alignLeft bool 是否靠最左侧显示
		@return void
		*/
		virtual void SetAlignTextToLeft(bool alignLeft) = 0;
		/*
		@name GetAlignTextToLeft
		@desc 获取图标是否最左侧显示
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
		@desc 设置显示的图片路径
		@param path  const tchar*  图片路径
		@return void
		*/
		virtual void SetImage(const tchar* path) = 0;
		/*
		@name SetImage
		@desc 设置显示的图片路径，并释放前一张图片
		@param path  const tchar*  图片路径
		@param bDeletePreviousImage  bool  是否释放前一张图片
		@return void
		*/
		virtual void SetImage(const tchar* path, bool bDeletePreviousImage) = 0;
		/*
		@name SetImage
		@desc 通过二进制数据，设置显示的图片，只支持png图片数据流
		@param imageName  const tchar*  图片名称
		@param imageBuffer  void*  数据流
		@param length  unsigned int  数据长度
		@return bool
		*/
		virtual bool SetImage(const tchar* imageName, void* imageBuffer, unsigned int length) = 0;
		/*
		@name GetImage
		@desc 获取显示的图片路径
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetImage() = 0;
		/*
		@name SetFillImage
		@desc 设置显示的图片是否拉伸填充显示
		@param bFill bool 是否拉伸
		@return void
		*/
		virtual void SetFillImage(bool bFill) = 0;
		/*
		@name GetFillImage
		@desc 获取显示的图片是否拉伸填充显示
		@param void
		@return bool
		*/
		virtual bool GetFillImage() = 0;
		/*
		@name SetUserImage
		@desc 设置显示用户位图，需要外部释放
		@param hBitmap HBITMAP 用户位图
		@return void
		*/
		virtual void SetUserImage(HBITMAP hBitmap) = 0;
		/*
		@name GetUserImage
		@desc 获取用户位图
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
		@desc 设置当前值
		@param pos int 当前值
		@return void
		*/
		virtual void SetValue(int pos) = 0;
		/*
		@name GetValue
		@desc 获取当前值
		@param void
		@return int
		*/
		virtual int GetValue() = 0;
		/*
		@name SetRange
		@desc 设置拖动范围值
		@param min int 最小值
		@param max int 最大值
		@return void
		*/
		virtual void SetRange(int min, int max) = 0;
		/*
		@name GetRange
		@desc 获取拖动范围值
		@param min int& 最小值
		@param max int& 最大值
		@return void
		*/
		virtual void GetRange(int& min, int& max) = 0;
		/*
		@name SetIsHor
		@desc 设置是否水平显示
		@param isHor bool 是否水平显示
		@return void
		*/
		virtual void SetIsHor(bool isHor) = 0;
		/*
		@name GetIsHor
		@desc 获取是否水平显示
		@param void
		@return bool
		*/
		virtual bool GetIsHor() = 0;
		/*
		@name SetThumbSize
		@desc 设置滑块大小
		@param w int 宽度
		@param h int 高度
		@return void
		*/
		virtual void SetThumbSize(int w, int h) = 0;
		/*
		@name GetThumbSize
		@desc 获取滑块大小
		@param w int& 宽度
		@param h int& 高度
		@return void
		*/
		virtual void GetThumbSize(int& w, int& h) = 0;
		/*
		@name SetChannelSize
		@desc 设置滑槽大小
		@param size int 大小
		@return void
		*/
		virtual void SetChannelSize(int size) = 0;
		/*
		@name GetChannelSize
		@desc 获取滑槽大小
		@param void
		@return int
		*/
		virtual int GetChannelSize() = 0;
		/*
		@name SetBackgroundStyle
		@desc 设置背景样式
		@param state UICommonState 状态枚举
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetBackgroundStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc 获取背景样式
		@param state UICommonState 状态枚举
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UICommonState state) = 0;
		/*
		@name SetFrontStyle
		@desc 设置前景样式
		@param state UICommonState 状态枚举
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetFrontStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetFrontStyle
		@desc 获取前景样式
		@param state UICommonState 状态枚举
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetFrontStyle(UICommonState state) = 0;
		/*
		@name SetThumbStyle
		@desc 设置滑槽样式
		@param state UICommonState 状态枚举
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetThumbStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetThumbStyle
		@desc 获取滑块样式
		@param state UICommonState 状态枚举
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetThumbStyle(UIState state) = 0;
	};

	class IUIGProgressBar : public IUIGearsControl
	{
	public:
		/*
		@name SetValue
		@desc 设置当前进度值
		@param pos int 进度值
		@return void
		*/
		virtual void SetValue(int pos) = 0;
		/*
		@name GetValue
		@desc 获取当前进度值
		@param void
		@return int
		*/
		virtual int GetValue() = 0;
		/*
		@name SetChannelSize
		@desc 设置滑槽大小
		@param size int 滑槽大小
		@return void
		*/
		virtual void SetChannelSize(int size) = 0;
		/*
		@name GetChannelSize
		@desc 获取滑槽大小
		@param void
		@return int
		*/
		virtual int GetChannelSize() = 0;
		/*
		@name SetRange
		@desc 设置进度范围
		@param min int 最小进度值
		@param max int 最大进度值
		@return void
		*/
		virtual void SetRange(int min, int max) = 0;
		/*
		@name GetRange
		@desc 获取进度范围
		@param min int& 最小进度值
		@param max int& 最大进度值
		@return void
		*/
		virtual void GetRange(int& min, int& max) = 0;
		/*
		@name SetIsHor
		@desc 设置是否是水平进度条
		@param isHor bool 是否水平显示
		@return void
		*/
		virtual void SetIsHor(bool isHor) = 0;
		/*
		@name GetIsHor
		@desc 获取是否是水平进度条
		@param void
		@return bool
		*/
		virtual bool GetIsHor() = 0;
		/*
		@name SetShowText
		@desc 设置是否显示文字
		@param show bool 是否显示文字
		@return void
		*/
		virtual void SetShowText(bool show) = 0;
		/*
		@name GetShowText
		@desc 获取是否显示文字
		@param void
		@return bool
		*/
		virtual bool GetShowText() = 0;
		/*
		@name SetNoStretchFront
		@desc 设置前景是否裁剪显示，不拉伸也就是裁剪显示
		@param noStretch bool 是否裁剪显示
		@return void
		*/
		virtual void SetNoStretchFront(bool noStretch) = 0;
		/*
		@name GetNoStretchFront
		@desc 获取前景是否裁剪显示
		@param void
		@return bool
		*/
		virtual bool GetNoStretchFront() = 0;
		/*
		@name SetBackgroundStyle
		@desc 设置背景样式
		@param state UICommonState 状态样式枚举
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetBackgroundStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc 获取背景样式
		@param state UICommonState 状态样式枚举
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UICommonState state) = 0;
		/*
		@name SetFrontStyle
		@desc 设置前景样式
		@param state UICommonState 状态样式枚举
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetFrontStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetFrontStyle
		@desc 获取背景样式
		@param state UICommonState 状态样式枚举
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetFrontStyle(UICommonState state) = 0;
		/*
		@name SetTextStyle
		@desc 设置文字样式
		@param state UICommonState 状态样式枚举
		@param style IUIGearsTextStyle* 样式指针
		@return bool
		*/
		virtual bool SetTextStyle(UICommonState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetTextStyle
		@desc 获取文字样式
		@param state UICommonState 状态样式枚举
		@return IUIGearsTextStyle*
		*/
		virtual IUIGearsTextStyle* GetTextStyle(UICommonState state) = 0;

	};

	class IUIGList : public IUIGearsControl
	{
	public:
		/*
		@name AddItem
		@desc 添加item
		@param text  const tchar*  item文本内容
		@return bool
		*/
		virtual bool AddItem(const tchar* text) = 0;
		/*
		@name InsertItem
		@desc 插入item
		@param index int 插入索引位置，从0开始
		@param text  const tchar*  item文本内容
		@return bool
		*/
		virtual bool InsertItem(int index, const tchar* text) = 0;
		/*
		@name SetItemTooltip
		@desc 设置item的tooltip文本
		@param index int 索引位置，从0开始
		@param text  const tchar*  tooltip文本内容
		@return bool
		*/
		virtual bool SetItemTooltip(int index, const tchar* text) = 0;
		/*
		@name GetItemTooltip
		@desc 获取item的tooltip文本
		@param index int 索引位置，从0开始
		@return const tchar*
		*/
		virtual const tchar* GetItemTooltip(int index) = 0;
		/*
		@name AddItemWithData
		@desc 添加Item并设置一个用户数据
		@param text  const tchar*  item文本
		@param data PARAM 用户数据
		@return bool
		*/
		virtual bool AddItemWithData(const tchar* text, PARAM data) = 0;
		/*
		@name RemoveAll
		@desc 删除所有的item
		@param void
		@return void
		*/
		virtual void RemoveAll() = 0;
		/*
		@name RemoveItem
		@desc 根据索引移除item
		@param index int 索引号
		@return bool
		*/
		virtual bool RemoveItem(int index) = 0;
		/*
		@name SetItemIcon
		@desc 设置item的图标
		@param index int 索引号
		@param iconPath  const tchar*  图标资源路径，在资源包中的路径
		@return bool
		*/
		virtual bool SetItemIcon(int index, const tchar* iconPath) = 0;
		/*
		@name GetItemIcon
		@desc 获取item的图标
		@param index int 索引号
		@return const tchar* 图标资源路径，在资源包中的路径
		*/
		virtual const tchar* GetItemIcon(int index) = 0;
		/*
		@name GetSelectedIndex
		@desc 获取选中索引
		@param void
		@return int
		*/
		virtual int GetSelectedIndex() = 0;
		/*
		@name SetSelectedIndex
		@desc 设置选中索引，如果为-1则表示清除所有选中
		@param index int 索引号
		@return void
		*/
		virtual void SetSelectedIndex(int index) = 0;
		/*
		@name GetItemText
		@desc 获取item文字内容
		@param index int 索引号
		@return const tchar*
		*/
		virtual const tchar* GetItemText(int index) = 0;
		/*
		@name SetItemText
		@desc 设置item文字内容
		@param index int 索引号
		@param text  const tchar*  文字内容
		@return bool
		*/
		virtual bool SetItemText(int index, const tchar* text) = 0;
		/*
		@name SetVerticalScrollBar
		@desc 绑定垂直滚动条
		@param pScrollBar IUIGearsControl* 滚动条控件指针
		@return void
		*/
		virtual void SetVerticalScrollBar(IUIGearsControl* pScrollbar) = 0;
		/*
		@name SetHorizontalScrollBar
		@desc 绑定水平滚动条
		@param pScrollBar IUIGearsControl* 滚动条控件指针
		@return void
		*/
		virtual void SetHorizontalScrollBar(IUIGearsControl* pScrollbar) = 0;
		/*
		@name SetMultiSelect
		@desc 设置是否支持多选
		@param multiSelect bool 是否支持多选
		@return void
		*/
		virtual void SetMultiSelect(bool multiSelect) = 0;
		/*
		@name GetMultiSelect
		@desc 获取是否支持多选
		@param void
		@return bool
		*/
		virtual bool GetMultiSelect() = 0;
		/*
		@name SetDragSelect
		@desc 设置是否打开拖拽选框选择
		@param dragSelect bool 拖拽选择
		@return void
		*/
		virtual void SetDragSelect(bool dragSelect) = 0;
		/*
		@name GetDragSelect
		@desc 获取是否打开拖拽选框选择
		@param void
		@return bool
		*/
		virtual bool GetDragSelect() = 0;
		/*
		@name IsSelected
		@desc 是否选择某项
		@param index int 索引
		@return bool
		*/
		virtual bool IsSelected(int index) = 0;
		/*
		@name GetMultiSelectedItems
		@desc 获取多选的选择
		@param void
		@return std::vector<int> 索引列表
		*/
		virtual	std::vector<int> GetMultiSelectedItems() = 0;
		virtual void UpdateData(int index) = 0;
		/*
		@name GetItemCount
		@desc 获取item数量
		@param void
		@return int
		*/
		virtual int GetItemCount() = 0;
		/*
		@name SetItemHeight
		@desc 设置item高度
		@param height int item高度
		@return void
		*/
		virtual void SetItemHeight(int height) = 0;
		/*
		@name GetItemHeight
		@desc 获取item高度
		@param void
		@return int
		*/
		virtual int GetItemHeight() = 0;
		/*
		@name SetShowIcon
		@desc 设置是否显示图标
		@param show bool 显示图标
		@return void
		*/
		virtual void SetShowIcon(bool show) = 0;
		/*
		@name GetShowIcon
		@desc 查询是否显示图标
		@param void
		@return bool
		*/
		virtual bool GetShowIcon() = 0;
		/*
		@name SetIconOffset
		@desc 设置图标的左侧偏移量
		@param offset int 偏移量
		@return void
		*/
		virtual void SetIconOffset(int offset) = 0;
		/*
		@name GetIconOffset
		@desc 获取图标的左侧偏移量
		@param void
		@return int
		*/
		virtual int GetIconOffset() = 0;
		/*
		@name SetDrawBorder
		@desc 设置是否绘制边框
		@param show bool 是否绘制边框
		@return void
		*/
		virtual void SetDrawBorder(bool show) = 0;
		/*
		@name GetDrawBorder
		@desc 获取是否绘制边框
		@param void
		@return bool
		*/
		virtual bool GetDrawBorder() = 0;
		/*
		@name SetBorderColor
		@desc 设置边框颜色
		@param color int 颜色值，如0xffff0000
		@return void
		*/
		virtual void SetBorderColor(int color) = 0;
		/*
		@name GetBorderColor
		@desc 获取边框颜色
		@param void
		@return int
		*/
		virtual int GetBorderColor() = 0;
		/*
		@name SetBorderSize
		@desc 设置边框粗细
		@param size int 粗细
		@return void
		*/
		virtual void SetBorderSize(int size) = 0;
		/*
		@name GetBorderSize
		@desc 获取边框粗细
		@param void
		@return int
		*/
		virtual int GetBorderSize() = 0;
		/*
		@name SetCanCancelSelected
		@desc 设置是否可以点击空白位置取消选择
		@param cancelSelected bool 是否允许取消选择
		@return void
		*/
		virtual void SetCanCancelSelected(bool cancelSelected) = 0;
		/*
		@name GetCanCancelSelected
		@desc 查询是否可以点击空白位置取消选择
		@param void
		@return bool
		*/
		virtual bool GetCanCancelSelected() = 0;
		/*
		@name SetBackgroundStyle
		@desc 设置背景样式
		@param state UICommonState 状态类型
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetBackgroundStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc 查询背景样式
		@param state UICommonState 状态类型
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UICommonState state) = 0;
		/*
		@name SetItemStyle
		@desc 设置Item背景样式
		@param state UICommonState 状态类型
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetItemStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetItemStyle
		@desc 查询Item背景样式
		@param state UICommonState 状态类型
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetItemStyle(UIState state) = 0;
		/*
		@name SetTextStyle
		@desc 设置Item字体样式
		@param state UICommonState 状态类型
		@param style IUIGearsTextStyle* 样式指针
		@return bool
		*/
		virtual bool SetTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetTextStyle
		@desc 查询Item字体样式
		@param state UICommonState 状态类型
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsTextStyle* GetTextStyle(UIState state) = 0;
		/*
		@name GetLMouseUpSelected
		@desc 获取是否左键抬起选择，默认是按下选择
		@param void
		@return bool
		*/
		virtual bool GetLMouseUpSelected() = 0;
		/*
		@name SetLMouseUpSelected
		@desc 设置是否左键抬起选择，默认是按下选择
		@param enable bool 是否打开
		@return void
		*/
		virtual void SetLMouseUpSelected(bool enable) = 0;
		/*
		@name SetEnableDragItem
		@desc 设置是否允许拖拽item，打开后会产生拖拽事件
		@param enable bool 是否打开
		@return void
		*/
		virtual void SetEnableDragItem(bool enable) = 0;
		/*
		@name SetEnableDragItem
		@desc 查询是否允许拖拽item，打开后会产生拖拽事件
		@param void
		@return bool
		*/
		virtual bool GetEnableDragItem() = 0;
		/*
		@name SetItemData
		@desc 设置item的用户数据
		@param index int 索引号
		@param data void* 用户数据
		@return bool
		*/
		virtual bool SetItemData(int index, void* data) = 0;
		/*
		@name GetItemData
		@desc 获取item的用户数据
		@param index int 索引号
		@return void*
		*/
		virtual void*	GetItemData(int index) = 0;
		/*
		@name SetItemMode
		@desc 设置item的显示模式
		@param mode ItemMode 显示模式
		@return void
		*/
		virtual void SetItemMode(ItemMode mode) = 0;
		/*
		@name GetItemMode
		@desc 获取item的显示模式
		@param void
		@return ItemMode
		*/
		virtual ItemMode GetItemMode() = 0;
		/*
		@name SetItemWidth
		@desc 设置item的宽度
		@param width  int  unsigned int
		@return void
		*/
		virtual void SetItemWidth(unsigned int width) = 0;
		/*
		@name GetItemWidth
		@desc 获取item的宽度
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
		@desc 添加item
		@param text  const tchar*  item文本内容
		@return bool
		*/
		virtual bool AddItem(const tchar* text) = 0;
		/*
		@name RemoveAll
		@desc 删除所有的item
		@param void
		@return void
		*/
		virtual void RemoveAll() = 0;
		/*
		@name RemoveItem
		@desc 根据索引移除item
		@param index int 索引号
		@return bool
		*/
		virtual bool RemoveItem(int index) = 0;
		/*
		@name GetSelectedIndex
		@desc 获取选中索引
		@param void
		@return int
		*/
		virtual int GetSelectedIndex() = 0;
		/*
		@name SetSelectedIndex
		@desc 设置选中索引，如果为-1则表示清除所有选中
		@param index int 索引号
		@return void
		*/
		virtual void SetSelectedIndex(int index) = 0;
		/*
		@name SetTemplateName
		@desc 设置item模板控件名称
		@param name  const tchar*  模板控件名称
		@return void
		*/
		virtual void SetTemplateName(const tchar*name) = 0;
		/*
		@name GetTemplateName
		@desc 获取模板控件名称
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetTemplateName() = 0;
		/*
		@name SetVerticalScrollBar
		@desc 绑定垂直滚动条
		@param pScrollBar IUIGearsControl* 滚动条控件指针
		@return void
		*/
		virtual void SetVerticalScrollBar(IUIGearsControl* pScrollbar) = 0;
		/*
		@name SetHorizontalScrollBar
		@desc 绑定水平滚动条
		@param pScrollBar IUIGearsControl* 滚动条控件指针
		@return void
		*/
		virtual void SetHorizontalScrollBar(IUIGearsControl* pScrollbar) = 0;
		/*
		@name SetMultiSelect
		@desc 设置是否支持多选
		@param multiSelect bool 是否支持多选
		@return void
		*/
		virtual void SetMultiSelect(bool multiSelect) = 0;
		/*
		@name IsSelected
		@desc 是否选择某项
		@param index int 索引
		@return bool
		*/
		virtual bool IsSelected(int index) = 0;
		/*
		@name GetMultiSelectedItems
		@desc 获取多选的选择
		@param void
		@return std::vector<int> 索引列表
		*/
		virtual	std::vector<int> GetMultiSelectedItems() = 0;
		/*
		@name UpdateData
		@desc 强制更新某一项，会自动发送更新事件
		@param index int 索引号
		@return void
		*/
		virtual void UpdateData(int index) = 0;
		/*
		@name GetItemCount
		@desc 获取item数量
		@param void
		@return int
		*/
		virtual int GetItemCount() = 0;
		/*
		@name RefreshData
		@desc 刷新整个列表的数据，会自动发送更新事件
		@param void
		@return void
		*/
		virtual void RefreshData() = 0;
		/*
		@name SetItemHeight
		@desc 设置item高度
		@param height int item高度
		@return void
		*/
		virtual void SetItemHeight(int height) = 0;
		/*
		@name GetItemHeight
		@desc 获取item高度
		@param void
		@return int
		*/
		virtual int GetItemHeight() = 0;
		/*
		@name SetDrawBorder
		@desc 设置是否绘制边框
		@param show bool 是否绘制边框
		@return void
		*/
		virtual void SetDrawBorder(bool show) = 0;
		/*
		@name GetDrawBorder
		@desc 获取是否绘制边框
		@param void
		@return bool
		*/
		virtual bool GetDrawBorder() = 0;
		/*
		@name SetBorderColor
		@desc 设置边框颜色
		@param color int 颜色值，如0xffff0000
		@return void
		*/
		virtual void SetBorderColor(int color) = 0;
		/*
		@name GetBorderColor
		@desc 获取边框颜色
		@param void
		@return int
		*/
		virtual int GetBorderColor() = 0;
		/*
		@name SetBorderSize
		@desc 设置边框粗细
		@param size int 粗细
		@return void
		*/
		virtual void SetBorderSize(int size) = 0;
		/*
		@name GetBorderSize
		@desc 获取边框粗细
		@param void
		@return int
		*/
		virtual int GetBorderSize() = 0;
		/*
		@name SetCanCancelSelected
		@desc 设置是否可以点击空白位置取消选择
		@param cancelSelected bool 是否允许取消选择
		@return void
		*/
		virtual void SetCanCancelSelected(bool cancelSelected) = 0;
		/*
		@name GetCanCancelSelected
		@desc 查询是否可以点击空白位置取消选择
		@param void
		@return bool
		*/
		virtual bool GetCanCancelSelected() = 0;
		/*
		@name SetBackgroundStyle
		@desc 设置背景样式
		@param state UICommonState 状态类型
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetBackgroundStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc 查询背景样式
		@param state UICommonState 状态类型
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UICommonState state) = 0;
		/*
		@name SetItemStyle
		@desc 设置Item背景样式
		@param state UICommonState 状态类型
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetItemStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetItemStyle
		@desc 查询Item背景样式
		@param state UICommonState 状态类型
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetItemStyle(UIState state) = 0;
		/*
		@name SetTextStyle
		@desc 设置Item字体样式
		@param state UICommonState 状态类型
		@param style IUIGearsTextStyle* 样式指针
		@return bool
		*/
		virtual bool SetTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetTextStyle
		@desc 查询Item字体样式
		@param state UICommonState 状态类型
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsTextStyle* GetTextStyle(UIState state) = 0;
		/*
		@name SetEnableDragItem
		@desc 设置是否允许拖拽item，打开后会产生拖拽事件
		@param enable bool 是否打开
		@return void
		*/
		virtual void SetEnableDragItem(bool enable) = 0;
		/*
		@name SetEnableDragItem
		@desc 查询是否允许拖拽item，打开后会产生拖拽事件
		@param void
		@return bool
		*/
		virtual bool GetEnableDragItem() = 0;
		/*
		@name SetItemData
		@desc 设置item的用户数据
		@param index int 索引号
		@param data void* 用户数据
		@return bool
		*/
		virtual bool SetItemData(int index, void* data) = 0;
		/*
		@name GetItemData
		@desc 获取item的用户数据
		@param index int 索引号
		@return void*
		*/
		virtual void* GetItemData(int index) = 0;
		/*
		@name SetItemMode
		@desc 设置item的显示模式
		@param mode ItemMode 显示模式
		@return void
		*/
		virtual void SetItemMode(ItemMode mode) = 0;
		/*
		@name GetItemMode
		@desc 获取item的显示模式
		@param void
		@return ItemMode
		*/
		virtual ItemMode GetItemMode() = 0;
		/*
		@name SetItemWidth
		@desc 设置item的宽度
		@param width  int  unsigned int
		@return void
		*/
		virtual void SetItemWidth(unsigned int width) = 0;
		/*
		@name GetItemWidth
		@desc 获取item的宽度
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
		@desc 设置滚动范围
		@param docHeight  unsigned int  整个需要显示的高度或者宽度
		@param visibleHeight  unsigned int  可见高度或者宽度
		@return void
		*/
		virtual void SetScrollInfo(unsigned int  docHeight, unsigned int  visibleHeight) = 0;
		/*
		@name GetScrollPos
		@desc 获取当前滚动位置
		@param void
		@return int
		*/
		virtual unsigned int GetScrollPos() = 0;
		/*
		@name SetScrollPos
		@desc 设置当前滚动位置
		@param pos  unsigned int  滚动位置
		@return void
		*/
		virtual void SetScrollPos(unsigned int pos) = 0;
		/*
		@name SetIsHor
		@desc 设置是否是水平滚动条
		@param isHor bool 水平滚动条
		@return void
		*/
		virtual void SetIsHor(bool isHor) = 0;
		/*
		@name GetIsHor
		@desc 获取是否是水平滚动条
		@param void
		@return bool
		*/
		virtual bool GetIsHor() = 0;
		/*
		@name SetBackgroundStyle
		@desc 设置背景样式
		@param state UICommonState 状态类型
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetBackgroundStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc 查询背景样式
		@param state UICommonState 状态类型
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UICommonState state) = 0;
		/*
		@name SetUpBtnStyle
		@desc 设置上按钮样式
		@param state UICommonState 状态类型
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetUpBtnStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetUpBtnStyle
		@desc 查询上按钮样式
		@param state UICommonState 状态类型
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetUpBtnStyle(UIState state) = 0;
		/*
		@name SetDownBtnStyle
		@desc 设置下按钮样式
		@param state UICommonState 状态类型
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetDownBtnStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetDownBtnStyle
		@desc 查询下按钮样式
		@param state UICommonState 状态类型
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetDownBtnStyle(UIState state) = 0;
		/*
		@name SetThumbBtnStyle
		@desc 设置滑块样式
		@param state UICommonState 状态类型
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetThumbBtnStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetThumbBtnStyle
		@desc 查询滑块样式
		@param state UICommonState 状态类型
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetThumbBtnStyle(UIState state) = 0;
		/*
		@name SetBtnSize
		@desc 设置滑块大小
		@param size int 滑块大小
		@return void
		*/
		virtual	void SetBtnSize(int size) = 0;
		/*
		@name GetBtnSize
		@desc 查询滑块大小
		@param void
		@return int
		*/
		virtual int GetBtnSize() = 0;
		/*
		@name SetUpBtnIcon
		@desc 设置上按钮图标
		@param path  const tchar*  图标资源路径
		@return void
		*/
		virtual void SetUpBtnIcon(const tchar* path) = 0;
		/*
		@name GetUpBtnIcon
		@desc 查询上按钮图标
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetUpBtnIcon() = 0;
		/*
		@name SetDownBtnIcon
		@desc 设置下按钮图标
		@param path  const tchar*  图标资源路径
		@return void
		*/
		virtual void SetDownBtnIcon(const tchar* path) = 0;
		/*
		@name GetDownBtnIcon
		@desc 查询下按钮图标
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetDownBtnIcon() = 0;
		/*
		@name SetThumbIcon
		@desc 设置滑块图标
		@param path  const tchar*  图标资源路径
		@return void
		*/
		virtual void SetThumbIcon(const tchar* path) = 0;
		/*
		@name GetThumbIcon
		@desc 查询滑块图标
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
		@desc 获取背景颜色
		@param void
		@return unsigned int
		*/
		virtual unsigned int GetBackColor() = 0;
		/*
		@name SetBackColor
		@desc 设置背景颜色
		@param color  unsigned int  背景颜色
		@return bool
		*/
		virtual bool SetBackColor(unsigned int color) = 0;
		/*
		@name AttchChildControl
		@desc 绑定子窗口
		@param ctrlHandle void 子窗口句柄
		@return void
		*/
		virtual void AttchChildControl(void* ctrlHandle) = 0;
		/*
		@name SetBackImage
		@desc 设置背景图片
		@param imagePath  const tchar*  图片资源路径
		@return bool
		*/
		virtual bool SetBackImage(const tchar* imagePath) = 0;
		/*
		@name RemoveAllChildControl
		@desc 移除所有绑定子控件
		@param void
		@return void
		*/
		virtual void RemoveAllChildControl() = 0;
		/*
		@name RemoveChildControl
		@desc 根据句柄移除所有绑定子控件
		@param ctrlHandle void* 子窗口句柄
		@return bool
		*/
		virtual bool RemoveChildControl(void* ctrlHandle) = 0;
		/*
		@name SetBackgroundStyle
		@desc 设置背景样式
		@param state UIState 状态枚举
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetBackgroundStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc 获取背景样式
		@param state UIState 状态枚举
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UIState state) = 0;
		/*
		@name SetBorderColor
		@desc 设置边框颜色
		@param color  unsigned int  颜色值
		@return void
		*/
		virtual void SetBorderColor(unsigned int color) = 0;
		/*
		@name GetBorderColor
		@desc 获取边框颜色
		@param void
		@return unsigned int
		*/
		virtual int GetBorderColor() = 0;
		/*
		@name SetUseBorder
		@desc 设置是否绘制边框
		@param use bool 是否使用
		@return void
		*/
		virtual void SetUseBorder(bool use) = 0;
		/*
		@name GetUseBorder
		@desc 获取是否绘制边框
		@param void
		@return bool
		*/
		virtual bool GetUseBorder() = 0;
		/*
		@name SetChildLayout
		@desc 设置子控件的布局类型
		@param layout UIGChildrenLayout 布局枚举
		@return void
		~
		enum UIGChildrenLayout
		{
		UIG_CL_HOR,  // 水平布局
		UIG_CL_VER,  // 垂直布局
		UIG_CL_HORFLOAT, // 水平浮动，先从左到右，然后从上到下
		UIG_CL_VERFLOAT, // 垂直浮动，先从上到下，然后从左到右
		UIG_CL_NOUSE, // 不使用布局
		UIG_CL_LAST 
		};
		~
		*/
		virtual void SetChildLayout(UIGChildrenLayout layout) = 0;
		/*
		@name GetChildLayout
		@desc 获取子控件的布局类型
		@param void
		@return UIGChildrenLayout
		*/
		virtual UIGChildrenLayout GetChildLayout() = 0;
		/*
		@name SetChildrenSpace
		@desc 设置子控件之间的布局间隔，当设置子控件布局后才生效
		@param space int 间隔
		@return void
		*/
		virtual void SetChildrenSpace(int space) = 0;
		/*
		@name GetChildrenSpace
		@desc 获取子控件间的间隔
		@param void
		@return int
		*/
		virtual int GetChildrenSpace() = 0;
		/*
		@name SetNeedClickEvent
		@desc 设置是否需要点击事件，默认没有点击事件
		@param needEvent bool 是否打开
		@return void
		*/
		virtual void SetNeedClickEvent(bool needEvent) = 0;
		/*
		@name GetNeedClickEvent
		@desc 获取是否有点击事件，默认没有点击事件
		@param void
		@return bool
		*/
		virtual bool GetNeedClickEvent() = 0;
		/*
		@name BindScrollBar
		@desc 绑定滚动条，当设置子控件布局后可以绑定滚动条进行滚动
		@param pScrollbar IUIGScrollBar* 滚动条指针
		@param isHor bool 是否是水平滚动条
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
		@desc 添加item
		@param text  const tchar*  item文本内容
		@return bool
		*/
		virtual bool AddItem(const tchar* text) = 0;
		/*
		@name RemoveAll
		@desc 删除所有的item
		@param void
		@return void
		*/
		virtual void RemoveAll() = 0;
		/*
		@name RemoveAllColumns
		@desc 删除所有的列
		@param void
		@return void
		*/
		virtual void RemoveAllColumns() = 0;
		/*
		@name RemoveItem
		@desc 根据索引移除item
		@param index int 索引号
		@return bool
		*/
		virtual bool RemoveItem(int index) = 0;
		/*
		@name RemoveColumn
		@desc 根据索引移除某一列
		@param index int 索引号
		@return bool
		*/
		virtual bool RemoveColumn(int index) = 0;
		/*
		@name GetColumnCount
		@desc 获取列的数量
		@param void
		@return int
		*/
		virtual int GetColumnCount() = 0;
		/*
		@name GetColumnHeaderText
		@desc 根据索引获取列头的文字
		@param index int 索引号
		@return const tchar*
		*/
		virtual const tchar* GetColumnHeaderText(int index) = 0;
		/*
		@name SetColumnHeaderText
		@desc 根据索引设置列头的文字
		@param index int 索引号
		@param text  const tchar*  文字内容
		@return void
		*/
		virtual void SetColumnHeaderText(int index, const tchar* text) = 0;
		/*
		@name GetEditable
		@desc 获取是否可以编辑
		@param void
		@return bool
		*/
		virtual bool GetEditable() = 0;
		/*
		@name SetEditable
		@desc 设置是否可以编辑
		@param editable bool 是否可编辑
		@return void
		*/
		virtual void SetEditable(bool editable) = 0;
		/*
		@name GetSelectedIndex
		@desc 获取选中索引
		@param void
		@return int
		*/
		virtual int GetSelectedIndex() = 0;
		/*
		@name SetSelectedIndex
		@desc 设置选中索引，如果为-1则表示清除所有选中
		@param index int 索引号
		@return void
		*/
		virtual void SetSelectedIndex(int index) = 0;
		/*
		@name GetItemText
		@desc 获取item文字内容
		@param row int 行索引号
		@param col int 列索引号
		@return const tchar*
		*/
		virtual const tchar* GetItemText(int row, int col) = 0;
		/*
		@name SetVerticalScrollBar
		@desc 绑定垂直滚动条
		@param pScrollBar IUIGearsControl* 滚动条控件指针
		@return void
		*/
		virtual void SetVerticalScrollBar(IUIGearsControl* pScrollbar) = 0;
		/*
		@name SetHorizontalScrollBar
		@desc 绑定水平滚动条
		@param pScrollBar IUIGearsControl* 滚动条控件指针
		@return void
		*/
		virtual void SetHorizontalScrollBar(IUIGearsControl* pScrollbar) = 0;
		/*
		@name SetMultiSelect
		@desc 设置是否支持多选
		@param multiSelect bool 是否支持多选
		@return void
		*/
		virtual void SetMultiSelect(bool multiSelect) = 0;
		/*
		@name GetMultiSelect
		@desc 获取是否支持多选
		@param void
		@return bool
		*/
		virtual bool GetMultiSelect() = 0;
		/*
		@name SetDragSelect
		@desc 设置是否打开拖拽选框选择
		@param dragSelect bool 拖拽选择
		@return void
		*/
		virtual void SetDragSelect(bool dragSelect) = 0;
		/*
		@name GetDragSelect
		@desc 获取是否打开拖拽选框选择
		@param void
		@return bool
		*/
		virtual bool GetDragSelect() = 0;
		/*
		@name IsSelected
		@desc 是否选择某项
		@param index int 索引
		@return bool
		*/
		virtual bool IsSelected(int index) = 0;
		/*
		@name GetMultiSelectedItems
		@desc 获取多选的选择
		@param void
		@return std::vector<int> 索引列表
		*/
		virtual	std::vector<int> GetMultiSelectedItems() = 0;
		/*
		@name GetItemCount
		@desc 获取item数量
		@param void
		@return int
		*/
		virtual int GetItemCount() = 0;
		virtual void SetDataMode(UIGDataGridMode mode) = 0;
		/*
		@name AppendColumn
		@desc 插入列
		@param colName  const tchar*  表头名称
		@param colWidth  int  表头宽度，默认100
		@return void
		*/
		virtual void AppendColumn(const tchar* colName, int colWidth = 100) = 0;
		/*
		@name SetItemText
		@desc 设置item文字内容
		@param row int 行索引号
		@param col int 列索引号
		@param text  const tchar*  文字内容
		@return bool
		*/
		virtual bool SetItemText(int row, int col, const tchar* text) = 0;
		/*
		@name SetBackgroundStyle
		@desc 设置背景样式
		@param state UICommonState 状态类型
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetBackgroundStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc 查询背景样式
		@param state UICommonState 状态类型
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UICommonState state) = 0;
		/*
		@name SetItemStyle
		@desc 设置Item背景样式
		@param state UICommonState 状态类型
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetItemStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetItemStyle
		@desc 查询Item背景样式
		@param state UICommonState 状态类型
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetItemStyle(UIState state) = 0;
		/*
		@name SetItemTextStyle
		@desc 设置Item字体样式
		@param state UICommonState 状态类型
		@param style IUIGearsTextStyle* 样式指针
		@return bool
		*/
		virtual bool SetItemTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetItemTextStyle
		@desc 查询Item字体样式
		@param state UICommonState 状态类型
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsTextStyle* GetItemTextStyle(UIState state) = 0;
		/*
		@name SetHeaderBackgroundStyle
		@desc 设置表头背景样式
		@param state UICommonState 状态类型
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetHeaderBackgroundStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetHeaderBackgroundStyle
		@desc 获取表头背景样式
		@param state UICommonState 状态类型
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual IUIGearsRectStyle* GetHeaderBackgroundStyle(UICommonState state) = 0;
		/*
		@name SetHeaderTextStyle
		@desc 设置表头文字样式
		@param state UIState 状态类型
		@param style IUIGearsTextStyle* 样式指针
		@return bool
		*/
		virtual bool SetHeaderTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetHeaderTextStyle
		@desc 获取表头文字样式
		@param state UIState 状态类型
		@return IUIGearsTextStyle*
		*/
		virtual IUIGearsTextStyle* GetHeaderTextStyle(UIState state) = 0;
		/*
		@name SetItemHeight
		@desc 设置item高度
		@param height int item高度
		@return void
		*/
		virtual void SetItemHeight(int height) = 0;
		/*
		@name GetItemCount
		@desc 获取item数量
		@param void
		@return int
		*/
		virtual int GetItemHeight() = 0;
		/*
		@name SetScrollIndex
		@desc 设置滚动位置
		@param index  unsinged int  滚动索引位置
		@return bool
		*/
		virtual bool SetScrollIndex(unsigned int index) = 0;
		/*
		@name GetScrollIndex
		@desc 获取当前最顶部滚动位置
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
		@desc 删除所有节点
		@param void
		@return void
		*/
		virtual void RemoveAll() = 0;
		/*
		@name SetVerticalScrollBar
		@desc 绑定垂直滚动条
		@param pScrollBar IUIGearsControl* 滚动条控件指针
		@return void
		*/
		virtual void SetVerticalScrollBar(IUIGearsControl* pScrollbar) = 0;
		/*
		@name SetHorizontalScrollBar
		@desc 绑定水平滚动条
		@param pScrollBar IUIGearsControl* 滚动条控件指针
		@return void
		*/
		virtual void SetHorizontalScrollBar(IUIGearsControl* pScrollbar) = 0;
		/*
		@name SetMultiSelect
		@desc 设置是否支持多选
		@param multiSelect bool 是否支持多选
		@return void
		*/
		virtual void SetMultiSelect(bool multiSelect) = 0;
		/*
		@name InsertItem
		@desc 插入节点
		@param parent TreeNode 父节点，如果是NULL则插入根节点下
		@param pos int 插入位置下标
		@param text  const tchar*  文字内容
		@return TreeNode
		*/
		virtual TreeNode InsertItem(TreeNode parent, unsigned int pos, const tchar* text) = 0;
		/*
		@name AppendItem
		@desc 在末尾插入节点
		@param parent TreeNode 父节点，如果是NULL则插入根节点下
		@param text  const tchar*  文字内容
		@return TreeNode
		*/
		virtual TreeNode AppendItem(TreeNode parent, const tchar* text) = 0;
		/*
		@name DeleteNode
		@desc 删除节点
		@param item TreeNode 节点指针
		@return bool
		*/
		virtual bool DeleteNode(TreeNode item) = 0; 
		/*
		@name SetItemText
		@desc 设置节点文本
		@param item TreeNode 节点指针
		@param text  const tchar*  节点指针
		@return bool
		*/
		virtual bool SetItemText(TreeNode node, const tchar* text) = 0;
		/*
		@name SetItemIcon
		@desc 设置节点图标
		@param item TreeNode 节点指针
		@param iconPath  const tchar*  图标资源路径
		@return bool
		*/
		virtual bool SetItemIcon(TreeNode node, const tchar* iconPath) = 0;
		/*
		@name SetItemIcon
		@desc 设置节点图标
		@param item TreeNode 节点指针
		@param iconPath  const tchar*  资源名称
		@param iconBuffer void* 二进制数据指针
		@param length  unsigned int  数据长度
		@return bool
		*/
		virtual bool SetItemIcon(TreeNode node, const tchar* iconName, void* iconBuffer, unsigned int length) = 0;
		/*
		@name SetItemData
		@desc 设置用户数据指针
		@param item TreeNode 节点指针
		@param data void* 用户数据
		@return bool
		*/
		virtual bool SetItemData(TreeNode node, void* data) = 0;
		/*
		@name GetItemData
		@desc 获取用户数据指针
		@param void
		@return void*
		*/
		virtual void*	GetItemData(TreeNode node) = 0;
		/*
		@name GetSelectedNodes
		@desc 获取选中的节点 
		@param void
		@return std::vector<TreeNode*>*
		*/
		virtual std::vector<TreeNode*>* GetSelectedNodes() = 0;
		/*
		@name SetSelectedNode
		@desc 设置选中的节点
		@param node TreeNode 选中节点
		@return bool
		*/
		virtual bool SetSelectedNode(TreeNode node) = 0;
		/*
		@name SwapNode
		@desc 交换两个节点
		@param node1 TreeNode 节点1
		@param node2 TreeNode 节点2
		@return bool
		*/
		virtual bool SwapNode(TreeNode node1, TreeNode node2) = 0;
		/*
		@name ScrollToNode
		@desc 滚动到某一节点
		@param node TreeNode 需要滚动到的节点
		@return bool
		*/
		virtual bool ScrollToNode(TreeNode node) = 0;
		/*
		@name GetItemText
		@desc 获取节点文本
		@param node TreeNode 节点
		@return const tchar*
		*/
		virtual const tchar* GetItemText(TreeNode node) = 0;
		/*
		@name GetParentNode
		@desc 获取父节点
		@param node TreeNode 节点，不能为NULL
		@return TreeNode
		*/
		virtual TreeNode GetParentNode(TreeNode node) = 0;
		/*
		@name GetChildrenNodeCount
		@desc 获取子节点的数量
		@param node TreeNode 节点
		@return unsigned int
		*/
		virtual unsigned int GetChildrenNodeCount(TreeNode node) = 0;
		/*
		@name GetChildNodeByIndex
		@desc 通过索引获取父节点的子节点
		@param node TreeNode 父节点
		@param index  unsgined int  索引号
		@return TreeNode
		*/
		virtual TreeNode GetChildNodeByIndex(TreeNode node, unsigned int index) = 0;
		/*
		@name SetExpandIcon
		@desc 设置展开图标
		@param pIconPath  const tchar*  图标路径
		@return void
		*/
		virtual void SetExpandIcon(const tchar* pIconPath) = 0;
		/*
		@name GetExpandIcon
		@desc 获取展开图标
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetExpandIcon() = 0;
		/*
		@name SetUnExpandIcon
		@desc 设置收缩图标
		@param pIconPath  const tchar*  资源路径
		@return void
		*/
		virtual void SetUnExpandIcon(const tchar* pIconPath) = 0;
		/*
		@name GetUnExpandIcon
		@desc 获取收缩图标
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetUnExpandIcon() = 0;
		/*
		@name SetItemOffset
		@desc 设置层级之前的偏移量
		@param offset int 偏移量
		@return void
		*/
		virtual void SetItemOffset(int offset) = 0;
		/*
		@name GetItemOffset
		@desc 获取层级之前的偏移量
		@param void
		@return int
		*/
		virtual int GetItemOffset() = 0;
		/*
		@name SetIconWidth
		@desc 设置图标的宽度，默认是16
		@param width int 宽度值
		@return void
		*/
		virtual void SetIconWidth(int width) = 0;
		/*
		@name GetIconWidth
		@desc 获取图标的宽度
		@param void
		@return int
		*/
		virtual int GetIconWidth() = 0;
		/*
		@name SetExpandIconWidth
		@desc 设置展开图标的宽度
		@param width int 宽度
		@return void
		*/
		virtual void SetExpandIconWidth(int width) = 0;
		/*
		@name GetExpandIconWidth
		@desc 获取展开图标的宽度
		@param void
		@return int
		*/
		virtual int GetExpandIconWidth() = 0;
		/*
		@name SetShowIcon
		@desc 设置是否显示图标
		@param show bool 是否显示
		@return void
		*/
		virtual void SetShowIcon(bool show) = 0;
		/*
		@name GetShowIcon
		@desc 获取是否显示图标
		@param void
		@return bool
		*/
		virtual bool GetShowIcon() = 0;
		/*
		@name SetItemHeight
		@desc 设置item高度
		@param height int item高度
		@return void
		*/
		virtual void SetItemHeight(int height) = 0;
		/*
		@name GetItemCount
		@desc 获取item数量
		@param void
		@return int
		*/
		virtual int GetItemHeight() = 0;
		/*
		@name SetBackgroundStyle
		@desc 设置背景样式
		@param state UICommonState 状态类型
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetBackgroundStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc 查询背景样式
		@param state UICommonState 状态类型
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UICommonState state) = 0;
		/*
		@name SetItemStyle
		@desc 设置Item背景样式
		@param state UICommonState 状态类型
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetItemStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetItemStyle
		@desc 查询Item背景样式
		@param state UICommonState 状态类型
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetItemStyle(UIState state) = 0;
		/*
		@name SetItemTextStyle
		@desc 设置Item字体样式
		@param state UICommonState 状态类型
		@param style IUIGearsTextStyle* 样式指针
		@return bool
		*/
		virtual bool SetItemTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetItemTextStyle
		@desc 查询Item字体样式
		@param state UICommonState 状态类型
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsTextStyle* GetItemTextStyle(UIState state) = 0;
	};

	class IUIGEdit : public IUIGearsControl
	{
	public:
		/*
		@name SetText
		@desc 设置文本内容
		@param text  const tchar*  文本内容
		@return bool
		*/
		virtual bool SetText(const tchar* text) = 0;
		/*
		@name GetText
		@desc 获取文本内容
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetText() = 0;
		/*
		@name GetIsPassword
		@desc 是否是密码显示
		@param void
		@return bool
		*/
		virtual bool GetIsPassword() = 0;
		/*
		@name SetIsPassword
		@desc 设置密码显示
		@param password bool 密码显示
		@return void
		*/
		virtual void SetIsPassword(bool password) = 0;
		/*
		@name SetPasswordChar
		@desc 设置密码显示的替代字符
		@param passchar  const tchar*  字符内容
		@return void
		*/
		virtual void SetPasswordChar(const tchar* passchar) = 0;
		/*
		@name GetPasswordChar
		@desc 获取密码显示的替代字符
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetPasswordChar() = 0;
		/*
		@name GetIsNumberOnly
		@desc 获取是否只能显示数值
		@param void
		@return bool
		*/
		virtual bool GetIsNumberOnly() = 0;
		/*
		@name SetIsNumberOnly
		@desc 设置是否只能输入数值
		@param numberOnly bool 只能输入数值
		@return void
		*/
		virtual void SetIsNumberOnly(bool numberOnly) = 0;
		/*
		@name GetHasNegativeNum
		@desc 获取是否允许输入负值
		@param void
		@return bool
		*/
		virtual bool GetHasNegativeNum() = 0;
		/*
		@name SetHasNegativeNum
		@desc 设置是否允许有负值
		@param negativeNum bool 允许负值
		@return void
		*/
		virtual void SetHasNegativeNum(bool negativeNum) = 0;
		/*
		@name SetNumber
		@desc 设置显示的数值
		@param number int 数值内容
		@return void
		*/
		virtual void SetNumber(int number) = 0;
		/*
		@name GetNumber
		@desc 获取数值内容
		@param void
		@return int
		*/
		virtual int GetNumber() = 0;
		/*
		@name SetNumberCount
		@desc 设置可输入数值的位数
		@param count int 可输入的位数
		@return void
		*/
		virtual void SetNumberCount(int count) = 0;
		/*
		@name GetNumberCount
		@desc 获取可输入数值的位数
		@param void
		@return int
		*/
		virtual int GetNumberCount() = 0;
		/*
		@name SetDigitNumCount
		@desc 设置小数的位数
		@param count int 小数位数
		@return void
		*/
		virtual void SetDigitNumCount(int count) = 0;
		/*
		@name GetDigitNumCount
		@desc 获取小数的位数
		@param void
		@return int
		*/
		virtual int GetDigitNumCount() = 0;
		/*
		@name SetRange
		@desc 设置数值的范围
		@param min int 最小值
		@param max int 最大值
		@return void
		*/
		virtual void SetRange(int min, int max) = 0;
		/*
		@name GetRange
		@desc 获取数值的范围
		@param min int& 最小值
		@param max int& 最大值
		@return void
		*/
		virtual void GetRange(int& min, int& max) = 0;
		/*
		@name SetBackgroundStyle
		@desc 设置背景样式
		@param state UIState 状态
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetBackgroundStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc 获取背景样式
		@param state UIState 状态
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UIState state) = 0;
		/*
		@name SetMargin
		@desc 设置左右的间隔
		@param left int 左侧间隔
		@param right int 右侧间隔
		@return void
		*/
		virtual void SetMargin(int left, int right) = 0;
		/*
		@name GetMargin
		@desc 获取左右的间隔
		@param left int& 左侧间隔
		@param right int& 右侧间隔
		@return void
		*/
		virtual void GetMargin(int& left, int& right) = 0;
		/*
		@name GetFontSize
		@desc 获取字体大小
		@param void
		@return unsigned int
		*/
		virtual unsigned int GetFontSize() = 0;
		/*
		@name SetFontSize
		@desc 设置字体大小
		@param size  unsigned int  字体大小
		@return void
		*/
		virtual void SetFontSize(unsigned int size) = 0;
		/*
		@name SetFontSize
		@desc 设置字体大小
		@param size  unsigned int  字体大小
		@return void
		*/
		virtual unsigned int GetFontColor() = 0;
		/*
		@name SetFontColor
		@desc 设置字体颜色
		@param color  unsigned int  字体颜色
		@return void
		*/
		virtual void SetFontColor(unsigned int color) = 0;
		/*
		@name GetDisableFontColor
		@desc 获取禁用字体颜色
		@param void
		@return unsigned int
		*/
		virtual unsigned int GetDisableFontColor() = 0;
		/*
		@name SetDisableFontColor
		@desc 设置禁用字体颜色
		@param color  unsigned int  字体颜色
		@return void
		*/
		virtual void SetDisableFontColor(unsigned int color) = 0;
		/*
		@name SetTipFontColor
		@desc 设置tip字体颜色
		@param color  unsigned int  字体颜色
		@return void
		*/
		virtual void SetTipFontColor(unsigned int color) = 0;
		/*
		@name GetTipFontColor
		@desc 获取tip字体颜色
		@param void
		@return unsigned int
		*/
		virtual unsigned int GetTipFontColor() = 0;
		/*
		@name SetTipText
		@desc 设置tip文字内容
		@param text  const tchar*  提示文字内容
		@return viod
		*/
		virtual void SetTipText(const tchar* text) = 0;
		/*
		@name GetTipText
		@desc 获取tip文字内容
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetTipText() = 0;
		/*
		@name SetShowTipText
		@desc 设置是否显示tip文字
		@param show bool 是否显示tip文字
		@return void
		*/
		virtual void SetShowTipText(bool show) = 0;
		/*
		@name GetShowTipText
		@desc 获取是否显示tip文字
		@param void
		@return bool
		*/
		virtual bool GetShowTipText() = 0;
		/*
		@name SetFontFamily
		@desc 设置字体
		@param family  const tchar*  字体
		@return void
		*/
		virtual void SetFontFamily(const tchar* family) = 0;
		/*
		@name GetFontFamily
		@desc 获取字体
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetFontFamily() = 0;
		/*
		@name SetLeftMargin
		@desc 设置左侧间隔
		@param margin int 间隔大小
		@return void
		*/
		virtual void SetLeftMargin(int margin) = 0;
		/*
		@name GetLeftMargin
		@desc 获取左侧间隔
		@param void
		@return int
		*/
		virtual int GetLeftMargin() = 0;
		/*
		@name SetRightMargin
		@desc 设置右侧间隔
		@param margin int 间隔大小
		@return void
		*/
		virtual void SetRightMargin(int margin) = 0;
		/*
		@name GetRightMargin
		@desc 获取右侧间隔
		@param void
		@return int
		*/
		virtual int GetRightMargin() = 0;
		/*
		@name SetUseShortcut
		@desc 设置是否使用快捷键模式
		@param shortcut bool 快捷键
		@return void
		*/
		virtual void SetUseShortcut(bool shortcut) = 0;
		/*
		@name GetUseShortcut
		@desc 查询是否使用快捷键模式
		@param void
		@return bool
		*/
		virtual bool GetUseShortcut() = 0;
		/*
		@name SetReadonly
		@desc 设置只读模式
		@param readonly bool 只读模式
		@return void
		*/
		virtual void SetReadonly(bool readonly) = 0;
		/*
		@name GetReadonly
		@desc 是否为只读模式
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
		@desc 设置文本内容
		@param text  const tchar*  文本内容
		@return bool
		*/
		virtual bool SetText(const tchar* text) = 0;
		/*
		@name GetText
		@desc 获取文本内容
		@param void
		@return const tchar* 
		*/
		virtual const tchar* GetText() = 0;
		/*
		@name SetNumber
		@desc 设置数值
		@param number int 数值
		@return void
		*/
		virtual void SetNumber(int number) = 0;
		/*
		@name GetNumber
		@desc 获取数值
		@param void
		@return int
		*/
		virtual int GetNumber() = 0;
		/*
		@name SetRange
		@desc 设置范围
		@param min int 最小值
		@param max int 最大值
		@return void
		*/
		virtual void SetRange(int min, int max) = 0;
		/*
		@name GetRange
		@desc 获取范围
		@param min int& 最小值
		@param max int& 最大值
		@return void
		*/
		virtual void GetRange(int& min, int& max) = 0;
		/*
		@name SetBackgroundStyle
		@desc 设置背景样式
		@param state UIState 状态枚举
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetBackgroundStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc 获取背景样式
		@param state UIState 状态枚举
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UIState state) = 0;
		/*
		@name SetMargin
		@desc 设置间隔
		@param left int 左间隔
		@param right int 右间隔
		@return void
		*/
		virtual void SetMargin(int left, int right) = 0;
		/*
		@name GetMargin
		@desc 获取间隔
		@param left int& 左间隔
		@param right int& 右间隔
		@return void
		*/
		virtual void GetMargin(int& left, int& right) = 0;
		/*
		@name GetFontSize
		@desc 获取字体大小
		@param void
		@return int
		*/
		virtual int GetFontSize() = 0;
		/*
		@name SetFontSize
		@desc 设置字体大小
		@param size int 字体大小
		@return void
		*/
		virtual void SetFontSize(int size) = 0;
		/*
		@name GetFontColor
		@desc 获取字体颜色
		@param void
		@return int
		*/
		virtual int GetFontColor() = 0;
		/*
		@name SetFontColor
		@desc 设置字体颜色
		@param color int 字体颜色
		@return void
		*/
		virtual void SetFontColor(int color) = 0;
		/*
		@name SetUpBtnStyle
		@desc 设置上按钮样式
		@param state UIState 状态枚举
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetUpBtnStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetUpBtnStyle
		@desc 获取上按钮样式
		@param state UIState 状态枚举
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetUpBtnStyle(UIState state) = 0;
		/*
		@name SetDownBtnStyle
		@desc 设置下按钮样式
		@param state UIState 状态枚举
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetDownBtnStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetDownBtnStyle
		@desc 获取下按钮样式
		@param state UIState 状态枚举
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetDownBtnStyle(UIState state) = 0;
		/*
		@name SetLeftMargin
		@desc 设置左间隔
		@param margin int 间隔
		@return void
		*/
		virtual void SetLeftMargin(int margin) = 0;
		/*
		@name GetLeftMargin
		@desc 获取左间隔
		@param void
		@return int
		*/
		virtual int GetLeftMargin() = 0;
		/*
		@name SetRightMargin
		@desc 设置右间隔
		@param margin int 间隔
		@return void
		*/
		virtual void SetRightMargin(int margin) = 0;
		/*
		@name GetRightMargin
		@desc 获取右间隔
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
		@desc 设置IP地址
		@param text  const tchar*  ip地址字符，如"127.0.0.1"
		@return void
		*/
		virtual void SetIP(const tchar* text) = 0;
		/*
		@name GetIP
		@desc 获取IP地址字符串
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetIP() = 0;
		/*
		@name SetBackgroundStyle
		@desc 设置背景样式
		@param state UIState 状态枚举
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetBackgroundStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc 获取背景样式
		@param state UIState 状态枚举
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UIState state) = 0;
		/*
		@name GetFontSize
		@desc 获取字体大小
		@param void
		@return int
		*/
		virtual int GetFontSize() = 0;
		/*
		@name SetFontSize
		@desc 设置字体大小
		@param size int 字体大小
		@return void
		*/
		virtual void SetFontSize(int size) = 0;
		/*
		@name GetFontColor
		@desc 获取字体大小
		@param void
		@return int
		*/
		virtual int GetFontColor() = 0;
		/*
		@name SetFontColor
		@desc 设置字体颜色
		@param color int 颜色值，如0xff000000
		@return void
		*/
		virtual void SetFontColor(int color) = 0;
		/*
		@name GetDisableFontColor
		@desc 获取禁用字体颜色
		@param void
		@return int
		*/
		virtual int GetDisableFontColor() = 0;
		/*
		@name SetDisableFontColor
		@desc 设置禁用字体颜色
		@param color int 颜色值，如0xff000000
		@return void
		*/
		virtual void SetDisableFontColor(int color) = 0;
		/*
		@name SetFontFamily
		@desc 设置字体
		@param family  const tchar*  字体
		@return void
		*/
		virtual void SetFontFamily(const tchar* family) = 0;
		/*
		@name GetFontFamily
		@desc 获取字体
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
		@desc 添加item
		@param text  const tchar*  文字内容
		@return void
		*/
		virtual void AddItem(const tchar* text) = 0;
		/*
		@name RemoveItem
		@desc 移除item
		@param index int 索引号
		@return void
		*/
		virtual void RemoveItem(int index) = 0;
		/*
		@name SetSelectedIndex
		@desc 根据索引设置选择项
		@param index unsigned int 索引号
		@return void
		*/
		virtual void SetSelectedIndex(unsigned int index) = 0;
		/*
		@name RemoveAllItems
		@desc 删除所有项
		@param void
		@return void
		*/
		virtual void RemoveAllItems() = 0;
		/*
		@name GetSelectedIndex
		@desc 获取选择项
		@param void
		@return void
		*/
		virtual int GetSelectedIndex() = 0;
		/*
		@name SetText
		@desc 设置显示文字
		@param text  const tchar*  文字内容
		@return void
		*/
		virtual void SetText(const tchar* text) = 0;
		/*
		@name GetText
		@desc 获取显示文字
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetText() = 0;
		/*
		@name SetBackgroundStyle
		@desc 设置背景样式
		@param state UIState 状态枚举
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetBackgroundStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc 获取背景样式
		@param state UIState 状态枚举
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UIState state) = 0;
		/*
		@name SetBtnStyle
		@desc 设置按钮样式
		@param state UIState 状态枚举
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetBtnStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBtnStyle
		@desc 获取按钮样式
		@param state UIState 状态枚举
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBtnStyle(UIState state) = 0;
		/*
		@name GetTextStyle
		@desc 获取文字样式
		@param state UIState 状态枚举
		@return IUIGearsTextStyle*
		*/
		virtual IUIGearsTextStyle* GetTextStyle(UIState state) = 0;
		/*
		@name SetTextStyle
		@desc 设置文字样式
		@param state UIState 状态枚举
		@param style IUIGearsTextStyle* 样式指针
		@return IUIGearsTextStyle*
		*/
		virtual bool SetTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name SetTextStyle
		@desc 设置项高度
		@param height int 项高度
		@return void
		*/
		virtual void SetItemHeight(int height) = 0;
		/*
		@name GetItemHeight
		@desc 获取项高度
		@param void
		@return int
		*/
		virtual int GetItemHeight() = 0;
		/*
		@name SetPopupMenuBg
		@desc 设置下拉列表背景
		@param state UICommonState 状态枚举
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetPopupMenuBg(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetPopupMenuBg
		@desc 获取下拉列表背景
		@param state UICommonState 状态枚举
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetPopupMenuBg(UICommonState state) = 0;
		/*
		@name SetPopupItemStyle
		@desc 设置下拉项背景样式
		@param state UICommonState 状态枚举
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetPopupItemStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetPopupItemStyle
		@desc 获取下拉项背景样式
		@param state UICommonState 状态枚举
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetPopupItemStyle(UIState state) = 0;
		/*
		@name SetPopupTextStyle
		@desc 设置下拉文字样式
		@param state UICommonState 状态枚举
		@param style IUIGearsTextStyle* 字体样式
		@return bool
		*/
		virtual bool SetPopupTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetPopupTextStyle
		@desc 获取下拉文字样式
		@param state UICommonState 状态枚举
		@return IUIGearsTextStyle*
		*/
		virtual IUIGearsTextStyle* GetPopupTextStyle(UIState state) = 0;
		/*
		@name SetItemData
		@desc 设置用户自定义数据
		@param index int 索引号
		@param data PARAM 用户数据
		@return bool
		*/
		virtual bool SetItemData(int index, PARAM data) = 0;
		/*
		@name GetItemData
		@desc 获取用户自定义数据
		@param index int 索引号
		@return PARAM
		*/
		virtual PARAM GetItemData(int index) = 0;
		/*
		@name SetItemText
		@desc 修改下拉项文字内容
		@param index int 索引号
		@param text  const tchar*  文字内容
		@return bool
		*/
		virtual bool SetItemText(int index, const tchar* text) = 0;
		/*
		@name GetItemText
		@desc 获取下拉项文字内容
		@param index int 索引号
		@return const tchar*
		*/
		virtual const tchar* GetItemText(int index) = 0;
		/*
		@name GetEditable
		@desc 获取是否可编辑
		@param void
		@return bool
		*/
		virtual bool GetEditable() = 0;
		/*
		@name SetEditable
		@desc 设置是否可编辑
		@param editable bool 是否可编辑
		@return void
		*/
		virtual void SetEditable(bool editable) = 0;
	};

	class IUIGLabel : public IUIGearsControl
	{
	public:
		/*
		@name SetText
		@desc 设置文字内容
		@param text  const tchar*  文字内容
		@return void
		*/
		virtual void SetText(const tchar* text) = 0;
		/*
		@name GetText
		@desc 获取文字内容
		@param void
		@return const tchar*
		*/
		virtual const tchar*  GetText() = 0;
		/*
		@name SetColor
		@desc 设置文字颜色
		@param textClr  unsigned int  文字颜色
		@return void
		*/
		virtual void SetColor(unsigned int textClr) = 0;
		/*
		@name GetColor
		@desc 获取文字颜色
		@param void
		@return unsgined int
		*/
		virtual unsigned int GetColor() = 0;
		/*
		@name SetIsSingleline
		@desc 设置是否单行显示
		@param void
		@return unsgined int
		*/
		virtual void SetIsSingleline(bool singleline) = 0;
		/*
		@name GetIsSingleline
		@desc 获取是否单行显示
		@param void
		@return bool
		*/
		virtual bool GetIsSingleline() = 0;
		/*
		@name GetTextStyle
		@desc 获取文字样式
		@param state UIState 状态枚举
		@return IUIGearsTextStyle*
		*/
		virtual IUIGearsTextStyle* GetTextStyle(UIState state) = 0;
		/*
		@name SetTextStyle
		@desc 设置文字样式
		@param state UIState 状态枚举
		@param style IUIGearsTextStyle* 样式指针
		@return bool
		*/
		virtual bool SetTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetIsLCD
		@desc 获取是否是LCD字体
		@param void
		@return bool
		*/
		virtual bool GetIsLCD() = 0;
		/*
		@name SetIsLCD
		@desc 设置是否是LCD字体
		@param isLCD bool 是否是LCD字体
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
		@desc 删除所有item项目
		@param void
		@return void
		*/
		virtual void RemoveAllItems() = 0;
		/*
		@name AppendMenuItem
		@desc 添加item项目
		@param parentItem MenuItem 父item对象，如果为NULL代表是根对象
		@param text  const tchar*  显示文本
		@param id int 菜单id
		@param type UIGMenuType 菜单类型
		@return MenuItem
		*/
		virtual MenuItem AppendMenuItem(MenuItem parentItem, const tchar* text, int id, UIGMenuType type = UIG_MENU_PUSHBUTTON) = 0;
		/*
		@name SetItemIcon
		@desc 设置item的图标
		@param item MenuItem item对象，如果为NULL代表是根对象
		@param iconPath  const tchar*  图标路径
		@return bool
		*/
		virtual bool SetItemIcon(MenuItem item, const tchar* iconPath) = 0;
		/*
		@name SetShortcutText
		@desc 设置item的快捷键文字
		@param item MenuItem item对象
		@param iconPath  const tchar*  图标路径
		@return bool
		*/
		virtual bool SetShortcutText(MenuItem item, const tchar* shortcutText) = 0;
		/*
		@name SetRadioGroupId
		@desc 设置item的分组id，必须是radio类型的菜单项
		@param item MenuItem item对象
		@param id int 分组id
		@return bool
		*/
		virtual bool SetRadioGroupId(MenuItem item, int id) = 0;
		/*
		@name SetSelected
		@desc 设置item的是否选中
		@param item MenuItem item对象，可以是radio或者check类型菜单项
		@param selected bool 是否选中
		@return bool
		*/
		virtual bool SetSelected(MenuItem item, bool selected) = 0;
		/*
		@name RemoveAllItems
		@desc 删除父item下指定索引的item项目，如果是NULL代表跟对象
		@param parentItem MenuItem 父item对象
		@param index int 需要删除的索引
		@return bool
		*/
		virtual bool RemoveMenuItem(MenuItem parentItem, int index) = 0;
		/*
		@name TrackPopupMenu
		@desc 弹出菜单
		@param x int 弹出水平坐标，为屏幕坐标
		@param y int 弹出垂直坐标，为屏幕坐标
		@return bool
		*/
		virtual int TrackPopupMenu(int x, int y, bool bWantReturn) = 0;
	};

	class IUIGMenuBar : public IUIGearsControl
	{
	public:
		/*
		@name AppendMenuItem
		@desc 添加子菜单项
		@param parentItem MenuItem 父菜单项
		@param text  const tchar*  文字内容
		@param id int id号
		@param type UIGMenuType 菜单类型
		@return bool
		*/
		virtual MenuItem AppendMenuItem(MenuItem parentItem, const tchar* text, int id, UIGMenuType type = UIG_MENU_PUSHBUTTON) = 0;
		/*
		@name SetMenuItemIcon
		@desc 设置菜单item的icon
		@param item MenuItem 菜单项
		@param iconPath  const tchar*  图标路径
		@return bool
		*/
		virtual bool SetMenuItemIcon(MenuItem item, const tchar* iconPath) = 0;
		/*
		@name SetBackgroundStyle
		@desc 设置菜单条背景样式
		@param state UICommonState 状态类型枚举
		@param style IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetBackgroundStyle(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetBackgroundStyle
		@desc 获取菜单条背景样式
		@param state UICommonState 状态类型枚举
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetBackgroundStyle(UICommonState state) = 0;
		/*
		@name SetItemStyle
		@desc 设置菜单条item背景样式
		@param state UICommonState 状态类型枚举
		@param state IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetItemStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetItemStyle
		@desc 获取菜单条item背景样式
		@param state UICommonState 状态类型枚举
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetItemStyle(UIState state) = 0;
		/*
		@name SetTextStyle
		@desc 获取菜单条item文字样式
		@param state UIState 状态类型枚举
		@param style IUIGearsTextStyle* 字体样式
		@return bool
		*/
		virtual bool SetTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetTextStyle
		@desc 获取菜单条item文字样式
		@param state UIState 状态类型枚举
		@return IUIGearsTextStyle*
		*/
		virtual IUIGearsTextStyle* GetTextStyle(UIState state) = 0;
		/*
		@name SetItemSpace
		@desc 设置菜单项之间的间隔
		@param space int 间隔大小
		@return void
		*/
		virtual void SetItemSpace(int space) = 0;
		/*
		@name GetItemSpace
		@desc 获取菜单项之间的间隔
		@param void
		@return int
		*/
		virtual int GetItemSpace() = 0;
		/*
		@name SetPopupMenuBg
		@desc 设置弹出菜单背景样式
		@param state UICommonState 状态类型枚举
		@param state IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetPopupMenuBg(UICommonState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetPopupMenuBg
		@desc 获取弹出菜单背景样式
		@param state UICommonState 状态类型枚举
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetPopupMenuBg(UICommonState state) = 0;
		/*
		@name SetPopupItemStyle
		@desc 设置弹出菜单item项背景样式
		@param state UICommonState 状态类型枚举
		@param state IUIGearsRectStyle* 样式指针
		@return bool
		*/
		virtual bool SetPopupItemStyle(UIState state, IUIGearsRectStyle* style) = 0;
		/*
		@name GetPopupItemStyle
		@desc 获取弹出菜单item项背景样式
		@param state UICommonState 状态类型枚举
		@return IUIGearsRectStyle*
		*/
		virtual IUIGearsRectStyle* GetPopupItemStyle(UIState state) = 0;
		/*
		@name SetPopupTextStyle
		@desc 设置弹出菜单的字体样式
		@param state UIState 状态类型枚举
		@param style IUIGearsTextStyle* 字体样式指针
		@return bool
		*/
		virtual bool SetPopupTextStyle(UIState state, IUIGearsTextStyle* style) = 0;
		/*
		@name GetPopupTextStyle
		@desc 查询弹出菜单的字体样式
		@param state UIState 状态类型枚举
		@return IUIGearsTextStyle*
		*/
		virtual IUIGearsTextStyle* GetPopupTextStyle(UIState state) = 0;
		/*
		@name SetBindPopupMenu
		@desc 设置绑定的菜单文件名称
		@param name  const tchar*  菜单文件名
		@return void
		*/
		virtual void SetBindPopupMenu(const tchar* name) = 0;
		/*
		@name GetBindPopupMenu
		@desc 获取绑定的菜单文件名称
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
		@desc 设置是否是水平分割条，水平分隔条只能上下拖拽，否则是垂直分隔条，垂直分隔条左右拖拽 
		@param isHor bool 是否是水平分隔条
		@return void
		*/
		virtual void SetIsHor(bool isHor) = 0;
		/*
		@name GetIsHor
		@desc 获取是否是水平分割条，水平分隔条只能上下拖拽，否则是垂直分隔条，垂直分隔条左右拖拽
		@param void
		@return bool
		*/
		virtual bool GetIsHor() = 0;
		/*
		@name SetLeftTopControlName
		@desc 设置左侧上分割控件
		@param controlName  const tchar*  控件名称
		@return void
		*/
		virtual void SetLeftTopControlName(const tchar* controlName) = 0;
		/*
		@name GetLeftTopControlName
		@desc 获取左侧上分割控件
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetLeftTopControlName() = 0;
		/*
		@name SetRightBottomControlName
		@desc 设置右下分割控件
		@param controlName  const tchar*  控件名称
		@return void
		*/
		virtual void SetRightBottomControlName(const tchar* controlName) = 0;
		/*
		@name GetRightBottomControlName
		@desc 获取右下分割控件
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetRightBottomControlName() = 0;
		/*
		@name SetLimitLeftTopSize
		@desc 设置左上控件的限制大小
		@param size int 限制大小
		@return void
		*/
		virtual void SetLimitLeftTopSize(int size) = 0;
		/*
		@name GetLimitLeftTopSize
		@desc 获取左上控件的限制大小
		@param void
		@return int
		*/
		virtual int GetLimitLeftTopSize() = 0;
		/*
		@name SetLimitRightBottomSize
		@desc 设置右下控件的限制大小
		@param size int 限制大小
		@return void
		*/
		virtual void SetLimitRightBottomSize(int size) = 0;
		/*
		@name GetLimitRightBottomSize
		@desc 获取右下控件的限制大小
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
		@desc 设置窗体的名称
		@param name  const tchar*  窗体名称
		@return void
		*/
		virtual void SetWinName(const tchar* name) = 0;
		/*
		@name GetWinName
		@desc 获取窗体的名称
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetWinName() = 0;
		/*
		@name GetTypeName
		@desc 获取类型名称
		@param void
		@return const tchar*
		*/
		virtual const tchar* GetTypeName() = 0;
		/*
		@name GetButton
		@desc 根据名称获取按钮控件
		@param name  const tchar*  按钮名称
		@return IUIGButton*
		*/
		virtual IUIGButton* GetButton(const tchar* name) = 0;
		/*
		@name GetControl
		@desc 根据名称获取控件
		@param name  const tchar*  控件名称
		@return IUIGearControl*
		*/
		virtual IUIGearsControl* GetControl(const tchar* name) = 0;
		/*
		@name ChangeTheme
		@desc 改变主题文件
		@param themepath  const tchar*  主题文件资源路径
		@return bool
		*/
		virtual bool ChangeTheme(const tchar* themePath) = 0;
		/*
		@name GetString
		@desc 根据关键字获取字符串
		@param key  const tchar*  关键字
		@return const tchar*
		*/
		virtual const tchar* GetString(const tchar* key) = 0;
		/*
		@name CreateControl
		@desc 动态创建控件
		@param type UIGControlType 控件类型枚举
		@param pParent IUIGearsControl* 父控件指针
		@param pName  const tchar*  控件名称
		@param x int 控件的x坐标
		@param y int 控件的y坐标
		@param w int 控件的宽度
		@param h int 控件的高度
		@return IUIGearsControl*
		*/
		virtual IUIGearsControl* CreateControl(UIGControlType type, IUIGearsControl* pParent, const tchar* pName, int x, int y, int w, int h) = 0;
		/*
		@name CreatePopupMenu
		@desc 创建弹出菜单
		@param pMenuConfig  const tchar*  菜单配置文件名称
		@param menuId int 菜单的id好
		@return IUIGPopupMenu*
		*/
		virtual IUIGPopupMenu* CreatePopupMenu(const tchar* pMenuConfig, int menuId) = 0;
		/*
		@name Invalidate
		@desc 重绘窗口
		@param redrawNow bool 是否立即重绘，否则为异步重绘，默认是异步
		@return void
		*/
		virtual void Invalidate(bool redrawNow = false) = 0;
		/*
		@name AppendEventReceiver
		@desc 添加事件接收对象
		@param pDelegateObj IEventRecevier* 事件接收对象
		@return void
		*/
		virtual void AppendEventReceiver(IEventRecevier* pDelegateObj) = 0;
		/*
		@name RemoveEventReceiver
		@desc 移除事件接收对象
		@param pDelegateObj IEventRecevier* 事件接收对象
		@return void
		*/
		virtual void RemoveEventReceiver(IEventRecevier* pDelegateObj) = 0;
		/*
		@name RemoveAllEventReceiver
		@desc 移除窗口中所有的事件接收对象
		@param void
		@return void
		*/
		virtual void RemoveAllEventReceiver() = 0;
		/*
		@name GetChildrenCount
		@desc 获取窗口下子控件数量
		@param void
		@return int
		*/
		virtual int GetChildrenCount() = 0;
		/*
		@name GetControlByIndex
		@desc 根据索引获取子控件
		@param index int 索引号
		@return IUIGearsControl*
		*/
		virtual IUIGearsControl* GetControlByIndex(int index) = 0;
		/*
		@name RemoveChild
		@desc 根据控件指针删除控件
		@param pEle IUIGearsControl* 控件指针
		@return bool
		*/
		virtual bool RemoveChild(IUIGearsControl* pEle) = 0;
		/*
		@name GetWidth
		@desc 获取窗体宽度
		@param void
		@return int
		*/
		virtual int GetWidth() = 0;
		/*
		@name GetHeight
		@desc 获取窗体高度
		@param void
		@return int
		*/
		virtual int GetHeight() = 0;
		/*
		@name SetWidth
		@desc 设置窗体宽度
		@param width int 宽度
		@return void
		*/
		virtual void SetWidth(int width) = 0;
		/*
		@name SetHeight
		@desc 设置窗体高度
		@param height int 宽度
		@return void
		*/
		virtual void SetHeight(int height) = 0;
		/*
		@name SetMinWidth
		@desc 设置窗体最小宽度
		@param height int 最小宽度
		@return void
		*/
		virtual void SetMinWidth(int minWidth) = 0;
		/*
		@name SetMinHeight
		@desc 设置窗体最小高度
		@param height int 最小宽度
		@return void
		*/
		virtual void SetMinHeight(int minHeight) = 0;
		/*
		@name GetMinWidth
		@desc 获取窗体最小高度
		@param void
		@return int
		*/
		virtual int GetMinWidth() = 0;
		/*
		@name GetMinHeight
		@desc  获取最小高度
		@param void
		@return int
		*/
		virtual int GetMinHeight() = 0;
		/*
		@name GetDBClickToMax
		@desc 查询是否允许双击最大化
		@param void
		@return int
		*/
		virtual bool GetDBClickToMax() = 0;
		/*
		@name SetDBClickToMax
		@desc 设置是否允许双击最大化
		@param enable bool 是否允许最大化
		@return void
		*/
		virtual void SetDBClickToMax(bool enable) = 0;
		/*
		@name GetDBClickCaptionHeight
		@desc 获取双击标题栏的高度
		@param void
		@return int
		*/
		virtual int GetDBClickCaptionHeight() = 0;
		/*
		@name SetDBClickCaptionHeight
		@desc 设置双击标题栏的高度
		@param height int 标题栏高度
		@return void
		*/
		virtual void SetDBClickCaptionHeight(int height) = 0;
		/*
		@name GetCanResize
		@desc 获取是否可以调整边框大小
		@param void
		@return bool
		*/
		virtual bool GetCanResize() = 0;
		/*
		@name SetCanResize
		@desc 设置是否可以拉伸大小
		@param enable bool 是否可以拉伸大小
		@return void
		*/
		virtual void SetCanResize(bool enable) = 0;
		/*
		@name GetIsTransparentWindow
		@desc 获取是否支持半透明窗口
		@param void
		@return bool
		*/
		virtual bool GetIsTransparentWindow() = 0;
		/*
		@name SetIsTransparentWindow
		@desc 设置是否支持半透明窗口
		@param enable bool 是否支持半透明窗口
		@return void
		*/
		virtual void SetIsTransparentWindow(bool enable) = 0;
		/*
		@name GetCanDrag
		@desc 获取是否支持拖拽窗体位置
		@param void
		@return bool
		*/
		virtual bool GetCanDrag() = 0;
		/*
		@name SetCanDrag
		@desc 获取是否支持拖拽窗体位置
		@param enable bool 是否支持拖拽
		@return void
		*/
		virtual void SetCanDrag(bool enable) = 0;
		/*
		@name GetOnlyDragOnCaption
		@desc 获取是否只能通过标题栏拖拽改变窗口位置
		@param void
		@return bool
		*/
		virtual bool GetOnlyDragOnCaption() = 0;
		/*
		@name SetOnlyDragOnCaption
		@desc 设置是否只能通过标题栏拖拽改变窗口位置
		@param enable bool 是否打开
		@return void
		*/
		virtual void SetOnlyDragOnCaption(bool enable) = 0;

#ifdef MOBILE
		/*
		@name GetDeviceType
		@desc 获取设备类型预设
		@param void
		@return DeviceType
		*/
		virtual DeviceType GetDeviceType() = 0;

		/*
		@name SetDeviceType
		@desc 设置设备类型预设
		@param type DeviceType 设备类型预设
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