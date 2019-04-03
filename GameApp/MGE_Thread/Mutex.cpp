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

MGEMutex::MGEMutex() {
}
MGEMutex::~MGEMutex() {
}

const char *MGEMutex::GetClassName() {
	return "MGEMutex";
}
BOOL32 MGEMutex::IsInstanceof(const char* className) {
	if (strcmp("MGEMutex", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

int MGEMutex::Init() {
	return pthread_mutex_init (&mutex, &attr);
}
int MGEMutex::Destroy() {
	return pthread_mutex_destroy (&mutex);
}
int MGEMutex::Lock() {
	return pthread_mutex_lock (&mutex);
}
int MGEMutex::TimedLock(const struct timespec *abstime) {
	return pthread_mutex_timedlock(&mutex, abstime);
}
int MGEMutex::TryLock() {
	return pthread_mutex_trylock (&mutex);
}
int MGEMutex::Unlock() {
	return pthread_mutex_unlock (&mutex);
}
int MGEMutex::AttribInit() {
	return pthread_mutexattr_init (&attr);
}
int MGEMutex::AttribDestroy() {
	return pthread_mutexattr_destroy (&attr);
}
int MGEMutex::GetpShared(int &pshared) {
	return pthread_mutexattr_getpshared (&attr, &pshared);
}
int MGEMutex::SetpShared(int pshared) {
	return pthread_mutexattr_setpshared (&attr, pshared);
}
int MGEMutex::GetType(int &kind) {
	return pthread_mutexattr_gettype (&attr, &kind);
}
int MGEMutex::SetType(int kind) {
	return pthread_mutexattr_settype (&attr, kind);
}


int MGEMutex::ConditionInit() {
	return pthread_cond_init (&cond, &condattr);
}
int MGEMutex::ConditionDestroy() {
	return pthread_cond_destroy (&cond);
}
int MGEMutex::ConditionWait() {
	return pthread_cond_wait (&cond, &mutex);
}
int MGEMutex::ConditionTimedwait(const struct timespec *abstime) {
	return pthread_cond_timedwait (&cond, &mutex, abstime);
}
int MGEMutex::Signal() {
	return pthread_cond_signal (&cond);
}
int MGEMutex::Broadcast() {
	return pthread_cond_broadcast (&cond);
}
int MGEMutex::ConditionAttribInit() {
	return pthread_condattr_init (&condattr);
}
int MGEMutex::ConditionAttribDestroy() {
	return pthread_condattr_destroy (&condattr);
}
int MGEMutex::ConditionAttribGetpShared(int &pshared) {
	return pthread_condattr_getpshared (&condattr, &pshared);
}
int MGEMutex::ConditionAttribSetpShared(int pshared) {
	return pthread_condattr_setpshared (&condattr, pshared);
}
