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
#include "../Base/Type.h"
#include "../Base/Base.h"
#define _ARRAY_API _CORE_API
#include "Eventlistener.hpp"

_CORE_API TEventListener::TEventListener() {
	AttribInit();
	rwLock.AttribInit();
	rwLock.Init();
	eventOccur = NULL;
	eventProc = NULL;
	uid = 0;
	actionCode = 0;
}
_CORE_API TEventListener::~TEventListener() {
	AttribDestroy();
	rwLock.Destroy();
	rwLock.AttribDestroy();
}
char _CORE_API *TEventListener::GetClassName() {
	return "TEventListener";
}
int _CORE_API TEventListener::GetClassCode() {
	return CLSID_TEventListener;
}
int _CORE_API TEventListener::GetHashCode() {
	return 1;
}
BOOL32 _CORE_API TEventListener::IsInstanceof(const char* className) {
	if (strcmp("TEventListener", className)) {
		return TRUE;
	}
	return TThread::IsInstanceof(className);
}
BOOL32 _CORE_API TEventListener::IsEqualto(IObject &obj) {
	return FALSE;
}
void _CORE_API TEventListener::Serialize(IIOStream &iio) {
}
void _CORE_API TEventListener::Wait() {
}
void _CORE_API TEventListener::Notify() {
}

//	EventHandler
void _CORE_API TEventListener::Run() {
	if ( eventOccur != NULL ) {
		TEvent e = *eventOccur;
		if ( e.uid != uid ) {
			rwLock.WriteLock();
			EventHandler(e);
			rwLock.Unlock();
		}
	}
}

void _CORE_API TEventListener::EventHandler(TEvent &e) {
}

void _CORE_API TEventListener::EventOccur(TEvent &e) {
	eventOccur = &e;
	Create();
}
