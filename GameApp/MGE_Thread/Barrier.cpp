///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _THREAD_EXPORT

#include "string.h"
#include "Thread.h"

MGEBarrier::MGEBarrier() {
}
MGEBarrier::~MGEBarrier() {
}

const char *MGEBarrier::GetClassName() {
	return "MGEBarrier";
}

BOOL32 MGEBarrier::IsInstanceof(const char* className) {
	if (strcmp("MGEBarrier", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

int MGEBarrier::Init(unsigned int count) {
	return pthread_barrier_init (&barrier, &attr, count);
}
int MGEBarrier::Destroy() {
	return pthread_barrier_destroy (&barrier);
}
int MGEBarrier::BarrierWait() {
	return pthread_barrier_wait (&barrier);
}
int MGEBarrier::AttribInit() {
	return pthread_barrierattr_init (&attr);
}
int MGEBarrier::AttribDestroy() {
	return pthread_barrierattr_destroy (&attr);
}
int MGEBarrier::GetpShared(int &pshared) {
	return pthread_barrierattr_getpshared (&attr, &pshared);
}
int MGEBarrier::SetpShared(int pshared) {
	return pthread_barrierattr_setpshared (&attr, pshared);
}
