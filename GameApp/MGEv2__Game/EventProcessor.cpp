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
#include "EventProcessor.hpp"

_CORE_API TEventProcessor::TEventProcessor() {
	eventQueue.Resize(128);
	queueHead = 0;
	queueTail = 0;
	queueLength = eventQueue.GetLength();
	queueRWLock.AttribInit();
	queueRWLock.Init();
	arrayRWLock.AttribInit();
	arrayRWLock.Init();
	interval = 0;
}
_CORE_API TEventProcessor::~TEventProcessor() {
	queueRWLock.Destroy();
	queueRWLock.AttribDestroy();
	arrayRWLock.Destroy();
	arrayRWLock.AttribDestroy();
	eventQueue.Resize(0);
	listeners.Resize(0);
}
char _CORE_API *TEventProcessor::GetClassName() {
	return "TEventProcessor";
}
int _CORE_API TEventProcessor::GetClassCode() {
	return CLSID_TEventProcessor;
}
int _CORE_API TEventProcessor::GetHashCode() {
	return 1;
}
BOOL32 _CORE_API TEventProcessor::IsInstanceof(const char* className) {
	if (strcmp("TEventProcessor", className)) {
		return TRUE;
	}
	return TThread::IsInstanceof(className);
}
BOOL32 _CORE_API TEventProcessor::IsEqualto(IObject &obj) {
	return FALSE;
}
void _CORE_API TEventProcessor::Serialize(IIOStream &iio) {
}
void _CORE_API TEventProcessor::Wait() {
}
void _CORE_API TEventProcessor::Notify() {
}

void _CORE_API TEventProcessor::Run() {
	unsigned int numlisteners = 0;
	unsigned int i1 = 0;
	TEvent event;
	while(TRUE) {
		if ( queueHead != queueTail ) {
			queueRWLock.ReadLock();
			event = eventQueue[queueTail];
			queueTail ++;
			queueTail = queueTail % queueLength;
			queueRWLock.Unlock();
			arrayRWLock.ReadLock();
			numlisteners = listeners.GetLength();
			for ( i1 = 0 ; i1 < numlisteners ; i1 ++ ) {
				TEventListener *el = &listeners[i1];
				if ( el != NULL ) {
					el->EventHandler(event);
				}
			}
			arrayRWLock.Unlock();
		}
		Delay(0, interval);
	}
}

void _CORE_API TEventProcessor::PostEvent(TEvent &e) {
	if ( queueTail == ( ( queueHead + 1 ) % queueLength ) ) {
		Delay(0, interval);
	} else {
		queueRWLock.WriteLock();
		eventQueue[queueHead] = e;
		queueHead ++;
		queueHead = queueHead % queueLength;
		queueRWLock.Unlock();
	}
}

void _CORE_API TEventProcessor::AddListener(TEventListener &listener) {
	arrayRWLock.WriteLock();
	unsigned int l = listeners.GetLength() + 1;
	listeners.Resize(l);
	listeners.Set(l - 1, &listener);
	arrayRWLock.Unlock();
}
