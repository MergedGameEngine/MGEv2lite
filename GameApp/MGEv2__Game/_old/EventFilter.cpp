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
#include "EventListener.hpp"
#include "EventProcessor.hpp"
#include "EventFilter.h"

_CORE_API TEventFilter::TEventFilter() {
}
_CORE_API TEventFilter::~TEventFilter() {
}
char _CORE_API *TEventFilter::GetClassName() {
	return "TEventFilter";
}
int _CORE_API TEventFilter::GetClassCode() {
	return CLSID_TEventFilter;
}
int _CORE_API TEventFilter::GetHashCode() {
	return 1;
}
BOOL32 _CORE_API TEventFilter::IsInstanceof(const char* className) {
	if (strcmp("TEventFilter", className)) {
		return TRUE;
	}
	return TThread::IsInstanceof(className);
}
BOOL32 _CORE_API TEventFilter::IsEqualto(IObject &obj) {
	return FALSE;
}
void _CORE_API TEventFilter::Serialize(IIOStream &iio) {
}
void _CORE_API TEventFilter::Wait() {
}
void _CORE_API TEventFilter::Notify() {
}
