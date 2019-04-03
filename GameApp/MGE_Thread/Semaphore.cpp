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

MGESemaphore::MGESemaphore() {
}
MGESemaphore::~MGESemaphore() {
}

const char *MGESemaphore::GetClassName() {
	return "MGESemaphore";
}

BOOL32 MGESemaphore::IsInstanceof(const char* className) {
	if (strcmp("MGESemaphore", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

int MGESemaphore::Init(int pshared, unsigned int value) {
	return sem_init (sem, pshared, value);
}
int MGESemaphore::Destroy() {
	return sem_destroy (sem);
}
int MGESemaphore::TryWait() {
	return sem_trywait (sem);
}
int MGESemaphore::SemWait() {
	return sem_wait (sem);
}
int MGESemaphore::TimedWait(const struct timespec * abstime) {
	return sem_timedwait (sem, abstime);
}
int MGESemaphore::Post() {
	return sem_post (sem);
}
int MGESemaphore::PostMultiple(int count) {
	///return sem_post_multiple (&sem, count);
	return 0;
}
int MGESemaphore::Open(const char * name, int oflag, mode_t &mode, unsigned int value) {
#ifdef WIN32
	return sem_open (name, oflag, mode, value);
#else
	sem = sem_open (name, oflag, mode, value);
	return 1;
#endif
}
int MGESemaphore::Close() {
	return sem_close (sem);
}
int MGESemaphore::Unlink(const char * name) {
	return sem_unlink (name);
}
int MGESemaphore::GetValue(int &sval) {
	return sem_getvalue (sem, &sval);
}
