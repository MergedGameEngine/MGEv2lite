///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

//
//		Foundation of GUI
//

#ifndef _MESSAGEPROC_H_
#define _MESSAGEPROC_H_


#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
//#include "../MGE__MathTool/MathTool.h"
//#include "../MGE__MathTool/MathTool.hpp"

#include "../MGE_Thread/Thread.h"


struct MGEMessage {
	unsigned int message;
	unsigned int parameter;
	unsigned int extend;
};

extern "C" class MGE2MessageProcessor : public MGEThread {
public:
	MGE2MessageProcessor();
	virtual ~MGE2MessageProcessor();
public:
	MGERefArray<MGE2MessageProcessor> components;
	MGERWLock rwLock;
public:
	//	MGE_MESSAGE
	enum {
		MGE2MSG_TIMER		=	0x0113,
	};

	enum {
		GEM_KEYDOWN			=	0x0100,
		GEM_KEYUP			=	0x0101,
		GEM_CHAR			=	0x0102,	//	IME char(Unicode) input
		GEM_DEADCHAR		=	0x0103,
		GEM_SYSKEYDOWN		=	0x0104,
		GEM_SYSKEYUP		=	0x0105,
		GEM_SYSCHAR			=	0x0106,
		GEM_SYSDEADCHAR		=	0x0107,
		GEM_MOUSEMOVE		=	0x0200,
		GEM_LBUTTONDOWN		=	0x0201,
		GEM_LBUTTONUP		=	0x0202,
		GEM_LBUTTONDBLCLK	=	0x0203,
		GEM_RBUTTONDOWN		=	0x0204,
		GEM_RBUTTONUP		=	0x0205,
		GEM_RBUTTONDBLCLK	=	0x0206,
		GEM_MBUTTONDOWN		=	0x0207,
		GEM_MBUTTONUP		=	0x0208,
		GEM_MBUTTONDBLCLK	=	0x0209,
		GEM_MOUSEWHEEL		=	0x020A
	};
	enum {
		GE_VK_BACK			=	0x08,
		GE_VK_TAB			=	0x09,
		GE_VK_CLEAR			=	0x0C,
		GE_VK_RETURN		=	0x0D,
		GE_VK_SHIFT			=	0x10,
		GE_VK_CONTROL		=	0x11,
		GE_VK_MENU			=	0x12,
		GE_VK_PAUSE			=	0x13,
		GE_VK_CAPITAL		=	0x14,
		GE_VK_ESCAPE		=	0x1B,

		GE_VK_SPACE			=	0x20,
		GE_VK_PRIOR			=	0x21,
		GE_VK_NEXT			=	0x22,
		GE_VK_END			=	0x23,
		GE_VK_HOME			=	0x24,
		GE_VK_LEFT			=	0x25,
		GE_VK_UP			=	0x26,
		GE_VK_RIGHT			=	0x27,
		GE_VK_DOWN			=	0x28,
		GE_VK_SELECT		=	0x29,
		GE_VK_PRINT			=	0x2A,
		GE_VK_EXECUTE		=	0x2B,
		GE_VK_SNAPSHOT		=	0x2C,
		GE_VK_INSERT		=	0x2D,
		GE_VK_DELETE		=	0x2E,
		GE_VK_HELP			=	0x2F,
		GE_VK_SLEEP			=	0x5F,

		GE_VK_NUMPAD0		=	0x60,
		GE_VK_NUMPAD1		=	0x61,
		GE_VK_NUMPAD2		=	0x62,
		GE_VK_NUMPAD3		=	0x63,
		GE_VK_NUMPAD4		=	0x64,
		GE_VK_NUMPAD5		=	0x65,
		GE_VK_NUMPAD6		=	0x66,
		GE_VK_NUMPAD7		=	0x67,
		GE_VK_NUMPAD8		=	0x68,
		GE_VK_NUMPAD9		=	0x69,
		GE_VK_MULTIPLY		=	0x6A,
		GE_VK_ADD			=	0x6B,
		GE_VK_SEPARATOR		=	0x6C,
		GE_VK_SUBTRACT		=	0x6D,
		GE_VK_DECIMAL		=	0x6E,
		GE_VK_DIVIDE		=	0x6F,
		GE_VK_F1			=	0x70,
		GE_VK_F2			=	0x71,
		GE_VK_F3			=	0x72,
		GE_VK_F4			=	0x73,
		GE_VK_F5			=	0x74,
		GE_VK_F6			=	0x75,
		GE_VK_F7			=	0x76,
		GE_VK_F8			=	0x77,
		GE_VK_F9			=	0x78,
		GE_VK_F10			=	0x79,
		GE_VK_F11			=	0x7A,
		GE_VK_F12			=	0x7B,
		GE_VK_F13			=	0x7C,
		GE_VK_F14			=	0x7D,
		GE_VK_F15			=	0x7E,
		GE_VK_F16			=	0x7F,
		GE_VK_F17			=	0x80,
		GE_VK_F18			=	0x81,
		GE_VK_F19			=	0x82,
		GE_VK_F20			=	0x83,
		GE_VK_F21			=	0x84,
		GE_VK_F22			=	0x85,
		GE_VK_F23			=	0x86,
		GE_VK_F24			=	0x87,

		GE_VK_NUMLOCK		=	0x90,
		GE_VK_SCROLL		=	0x91,
		GE_VK_LSHIFT		=	0xA0,
		GE_VK_RSHIFT		=	0xA1,
		GE_VK_LCONTROL		=	0xA2,
		GE_VK_RCONTROL		=	0xA3,
		GE_VK_LMENU			=	0xA4,
		GE_VK_RMENU			=	0xA5
	};
public:
	void PostMessage(MGEMessage &msg);
public:
	virtual void MessageHandler(MGEMessage &msg);
	virtual void AddComponent(MGE2MessageProcessor &src);
public:
	void Command(MGEMessage &msg);
public://Commands
	virtual void OnTimer(unsigned int _tid);

	virtual void OnKeyDown(unsigned char key);
	virtual void OnKeyUp(unsigned char key);
	virtual void OnChar(unsigned short chr);
	virtual void OnDeadChar(unsigned short chr);
	virtual void OnSysKeyDown(unsigned char key);
	virtual void OnSysKeyUp(unsigned char key);
	virtual void OnSysChar(unsigned short chr);
	virtual void OnSysDeadChar(unsigned short chr);

	virtual void OnMouseMove(short x, short y);
	virtual void OnLeftButtonDown();
	virtual void OnLeftButtonUp();
	virtual void OnLeftButtonDoubleClick();
	virtual void OnRightButtonDown();
	virtual void OnRightButtonUp();
	virtual void OnRightButtonDoubleClick();
	virtual void OnMiddleButtonDown();
	virtual void OnMiddleButtonUp();
	virtual void OnMiddleButtonDoubleClick();
	virtual void OnMouseWheel(short zdelta);

public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};


#endif