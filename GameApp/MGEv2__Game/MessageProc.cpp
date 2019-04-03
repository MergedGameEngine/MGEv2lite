///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _CORE_EXPORT

#define _MATHTOOL_IMPORT
#define _BASE_IMPORT
#define _FILE_IMPORT
#define _MODEL_IMPORT
#define _THREAD_IMPORT
#define _RENDERER_IMPORT

#include "string.h"
//#include "../Base/Type.h"
//#include "../Base/Base.h"
#define _ARRAY_API _CORE_API
#include "MessageProc.hpp"

MGE2MessageProcessor::MGE2MessageProcessor() {
	rwLock.AttribInit();
	rwLock.Init();
}
MGE2MessageProcessor::~MGE2MessageProcessor() {
	rwLock.Destroy();
	rwLock.AttribDestroy();
	components.Resize(0);
}
const char *MGE2MessageProcessor::GetClassName() {
	return "MGE2MessageProcessor";
}

BOOL32 MGE2MessageProcessor::IsInstanceof(const char* className) {
	if (strcmp("MGE2MessageProcessor", className)) {
		return TRUE;
	}
	return FALSE;
}


void MGE2MessageProcessor::PostMessage(MGEMessage &msg) {
}
void MGE2MessageProcessor::MessageHandler(MGEMessage &msg) {
	unsigned int numcoms = 0;
	unsigned int i1 = 0;
	Command(msg);
	rwLock.ReadLock();
	numcoms = components.GetLength();
	for ( i1 = 0 ; i1 < numcoms ; i1 ++ ) {
		MGE2MessageProcessor *com = &components[i1];
		if ( com != NULL ) {
			com->MessageHandler(msg);
		}
	}
	rwLock.Unlock();
}
void MGE2MessageProcessor::AddComponent(MGE2MessageProcessor &src) {
	rwLock.WriteLock();
	unsigned int l = components.GetLength() + 1;
	components.Resize(l);
	components.Set(l - 1, &src);
	rwLock.Unlock();
}

void MGE2MessageProcessor::Command(MGEMessage &msg) {
	switch (msg.message) {
		case MGE2MSG_TIMER:
			{
				OnTimer(msg.parameter);
			}
			break;
		case GEM_KEYDOWN:
			{
				OnKeyDown((unsigned char)msg.parameter);
			}
			break;
		case GEM_KEYUP:
			{
				OnKeyUp((unsigned char)msg.parameter);
			}
			break;
		case GEM_CHAR:
			{
				OnChar((unsigned short)msg.parameter);
			}
			break;
		case GEM_DEADCHAR:
			{
				OnDeadChar((unsigned short)msg.parameter);
			}
			break;
		case GEM_SYSKEYDOWN:
			{
				OnSysKeyDown((unsigned char)msg.parameter);
			}
			break;
		case GEM_SYSKEYUP:
			{
				OnSysKeyUp((unsigned char)msg.parameter);
			}
			break;
		case GEM_SYSCHAR:
			{
				OnSysChar((unsigned short)msg.parameter);
			}
			break;
		case GEM_SYSDEADCHAR:
			{
				OnSysDeadChar((unsigned short)msg.parameter);
			}
			break;
		case GEM_MOUSEMOVE:
			{
				short x = (short)(msg.parameter >> 16);
				short y = (short)msg.parameter;
				OnMouseMove(x, y);
			}
			break;
		case GEM_LBUTTONDOWN:
			{
				OnLeftButtonDown();
			}
			break;
		case GEM_LBUTTONUP:
			{
				OnLeftButtonUp();
			}
			break;
		case GEM_LBUTTONDBLCLK:
			{
				OnLeftButtonDoubleClick();
			}
			break;
		case GEM_RBUTTONDOWN:
			{
				OnRightButtonDown();
			}
			break;
		case GEM_RBUTTONUP:
			{
				OnRightButtonUp();
			}
			break;
		case GEM_RBUTTONDBLCLK:
			{
				OnRightButtonDoubleClick();
			}
			break;
		case GEM_MBUTTONDOWN:
			{
				OnMiddleButtonDown();
			}
			break;
		case GEM_MBUTTONUP:
			{
				OnMiddleButtonUp();
			}
			break;
		case GEM_MBUTTONDBLCLK:
			{
				OnMiddleButtonDoubleClick();
			}
			break;
		case GEM_MOUSEWHEEL:
			{
				OnMouseWheel((short)msg.parameter);
			}
			break;
		default:
			break;
	}
}
void MGE2MessageProcessor::OnTimer(unsigned int _tid) {
}

void MGE2MessageProcessor::OnKeyDown(unsigned char key) {
}
void MGE2MessageProcessor::OnKeyUp(unsigned char key) {
}
void MGE2MessageProcessor::OnChar(unsigned short chr) {
}
void MGE2MessageProcessor::OnDeadChar(unsigned short chr) {
}
void MGE2MessageProcessor::OnSysKeyDown(unsigned char key) {
}
void MGE2MessageProcessor::OnSysKeyUp(unsigned char key) {
}
void MGE2MessageProcessor::OnSysChar(unsigned short chr) {
}
void MGE2MessageProcessor::OnSysDeadChar(unsigned short chr) {
}


void MGE2MessageProcessor::OnMouseMove(short x, short y) {
}
void MGE2MessageProcessor::OnLeftButtonDown() {
}
void MGE2MessageProcessor::OnLeftButtonUp() {
}
void MGE2MessageProcessor::OnLeftButtonDoubleClick() {
}
void MGE2MessageProcessor::OnRightButtonDown() {
}
void MGE2MessageProcessor::OnRightButtonUp() {
}
void MGE2MessageProcessor::OnRightButtonDoubleClick() {
}
void MGE2MessageProcessor::OnMiddleButtonDown() {
}
void MGE2MessageProcessor::OnMiddleButtonUp() {
}
void MGE2MessageProcessor::OnMiddleButtonDoubleClick() {
}
void MGE2MessageProcessor::OnMouseWheel(short zdelta) {
}
