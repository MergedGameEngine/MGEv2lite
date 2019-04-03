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

MGEThread::MGEThread() {
}
MGEThread::~MGEThread() {
}

const char *MGEThread::GetClassName() {
	return "MGEThread";
}
BOOL32 MGEThread::IsInstanceof(const char* className) {
	if (strcmp("MGEThread", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

void  *MGEThread::ptEntry(void *arg) {
	MGEThread &pt = *(MGEThread*)arg;
	pt.Run();
	return (NULL);
}

void MGEThread::Run() {
	unsigned long long addr = (unsigned long long)this;
	printf("\n Hello World , PThread @ %8X \n ", addr);
}

void MGEThread::Exit() {
	pthread_exit (NULL);
}

int MGEThread::SetCancelState(int state, int &oldstate) {
	return pthread_setcancelstate (state, &oldstate);
}

int MGEThread::SetCancelType(int type, int &oldtype) {
	return pthread_setcanceltype (type, &oldtype);
}

void MGEThread::TestCancel() {
	pthread_testcancel();
}

void MGEThread::Start() {
	pthread_attr_init(&pthread_custom_attr);
	pthread_create(&pThread, &pthread_custom_attr, MGEThread::ptEntry, this);
}

int MGEThread::Create() {
	return pthread_create(&pThread, &pthread_custom_attr, MGEThread::ptEntry, this);
}

int MGEThread::Cancel() {
	return pthread_cancel(pThread);
}

int MGEThread::Detach() {
	return pthread_detach(pThread);
}

int MGEThread::Join() {
	return pthread_join(pThread, NULL);
}

int MGEThread::Delay(int sec, int nsec) {
	timespec delay;
	delay.tv_sec = sec;
	delay.tv_nsec = nsec;
///	return pthread_delay_np( &delay );
	return 0;
}

int MGEThread::NumProcessors() {
///	return pthread_num_processors_np();
	return 0;
}

int MGEThread::AttribInit() {
	return pthread_attr_init (&pthread_custom_attr);
}
int MGEThread::AttribDestroy() {
	return pthread_attr_destroy (&pthread_custom_attr);
}
int MGEThread::GetDetachState(int &detachstate) {
	return pthread_attr_getdetachstate (&pthread_custom_attr, &detachstate);
}
int MGEThread::GetStackAddress(void **stackaddr) {
	return pthread_attr_getstackaddr (&pthread_custom_attr, stackaddr);
}
int MGEThread::GetStackSize(unsigned int &stacksize) {
	size_t stks;
	int retcode = pthread_attr_getstacksize (&pthread_custom_attr, &stks);
	stacksize = (unsigned int)stks;
	return retcode;
}
int MGEThread::SetDetachState(int detachstate) {
	return pthread_attr_setdetachstate (&pthread_custom_attr, detachstate);
}
int MGEThread::SetStackAddress(void *stackaddr) {
	return pthread_attr_setstackaddr (&pthread_custom_attr, stackaddr);
}
int MGEThread::SetStackSize(unsigned int stacksize) {
	return pthread_attr_setstacksize (&pthread_custom_attr, (size_t)stacksize);
}
int MGEThread::GetSchedParam(int &priority) {
	priority = sche.sched_priority; 
	return pthread_attr_getschedparam (&pthread_custom_attr, &sche);
}
int MGEThread::SetSchedParam(int priority) {
	sche.sched_priority = priority;
	return pthread_attr_setschedparam (&pthread_custom_attr, &sche);
}
int MGEThread::SetSchedPolicy(int policy) {
	return pthread_attr_setschedpolicy (&pthread_custom_attr, policy);
}
int MGEThread::GetSchedPolicy(int &policy) {
	return pthread_attr_getschedpolicy (&pthread_custom_attr, &policy);
}
int MGEThread::SetInheritSched(int inheritsched) {
	return pthread_attr_setinheritsched(&pthread_custom_attr, inheritsched);
}
int MGEThread::GetInheritSched(int &inheritsched) {
	return pthread_attr_getinheritsched(&pthread_custom_attr, &inheritsched);
}
int MGEThread::SetScope(int scope) {
	return pthread_attr_setscope (&pthread_custom_attr, scope);
}
int MGEThread::GetScope(int &scope) {
	return pthread_attr_getscope (&pthread_custom_attr, &scope);
}
