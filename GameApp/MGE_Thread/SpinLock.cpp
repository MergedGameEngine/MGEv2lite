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

MGESpinLock::MGESpinLock() {
}
MGESpinLock::~MGESpinLock() {
}

const char *MGESpinLock::GetClassName() {
	return "MGESpinLock";
}

BOOL32 MGESpinLock::IsInstanceof(const char* className) {
	if (strcmp("MGESpinLock", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

int MGESpinLock::Init(int pshared) {
	return pthread_spin_init (&lock, pshared);
}
int MGESpinLock::Destroy() {
	return pthread_spin_destroy (&lock);
}
int MGESpinLock::Lock() {
	return pthread_spin_lock (&lock);
}
int MGESpinLock::TryLock() {
	return pthread_spin_trylock (&lock);
}
int MGESpinLock::Unlock() {
	return pthread_spin_unlock (&lock);
}
