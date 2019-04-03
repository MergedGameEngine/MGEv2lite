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

MGERWLock::MGERWLock() {
}
MGERWLock::~MGERWLock() {
}

const char *MGERWLock::GetClassName() {
	return "MGERWLock";
}
BOOL32 MGERWLock::IsInstanceof(const char* className) {
	if (strcmp("MGERWLock", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

int MGERWLock::Init() {
	return pthread_rwlock_init(&lock, &attr);
}
int MGERWLock::Destroy() {
	return pthread_rwlock_destroy(&lock);
}
int MGERWLock::TryReadLock() {
	return pthread_rwlock_tryrdlock(&lock);
}
int MGERWLock::TryWriteLock() {
	return pthread_rwlock_trywrlock(&lock);
}
int MGERWLock::ReadLock() {
	return pthread_rwlock_rdlock(&lock);
}
int MGERWLock::TimedReadLock(const struct timespec *abstime) {
	return pthread_rwlock_timedrdlock(&lock, abstime);
}
int MGERWLock::WriteLock() {
	return pthread_rwlock_wrlock(&lock);
}
int MGERWLock::TimedWriteLock(const struct timespec *abstime) {
	return pthread_rwlock_timedwrlock(&lock, abstime);
}
int MGERWLock::Unlock() {
	return pthread_rwlock_unlock(&lock);
}
int MGERWLock::AttribInit() {
	return pthread_rwlockattr_init (&attr);
}
int MGERWLock::AttribDestroy() {
	return pthread_rwlockattr_destroy (&attr);
}
int MGERWLock::GetpShared(int &pshared) {
	return pthread_rwlockattr_getpshared (&attr, &pshared);
}
int MGERWLock::SetpShared(int pshared) {
	return pthread_rwlockattr_setpshared (&attr, pshared);
}
