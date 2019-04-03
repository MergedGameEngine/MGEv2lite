///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _THREAD_H_
#define _THREAD_H_

#include "stdio.h"
#include "sys/types.h"
#ifdef WIN32
#include "_pthread/pthread.h"
#include "_pthread/semaphore.h"
#else
#include "pthread.h"
#include "semaphore.h"
#endif
#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"

extern "C" class MGEThread : public MGEObject {
public:
	MGEThread();
	virtual ~MGEThread();
private:
	static void *ptEntry(void *arg);
protected:
	pthread_t pThread;
	pthread_attr_t pthread_custom_attr;
	sched_param sche;
public:
	virtual void Run();
	void Exit();
	int SetCancelState(int state, int &oldstate);
	int SetCancelType(int type, int &oldtype);
	void TestCancel();

public:
	virtual void Start();
	int Create();
	int Cancel();
	int Detach();
	int Join();
	int Delay(int sec, int nsec);
	int NumProcessors();

	int AttribInit();
	int AttribDestroy();
	int GetDetachState(int &detachstate);
	int GetStackAddress(void **stackaddr);
	int GetStackSize(unsigned int &stacksize);
	int SetDetachState(int detachstate);
	int SetStackAddress(void *stackaddr);
	int SetStackSize(unsigned int stacksize);
	int GetSchedParam(int &priority);
	int SetSchedParam(int priority);
	int SetSchedPolicy(int policy);
	int GetSchedPolicy(int &policy);
	int SetInheritSched(int inheritsched);
	int GetInheritSched(int &inheritsched);
	int SetScope(int scope);
	int GetScope(int &scope);
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};

extern "C" class MGESemaphore : public MGEObject {
public:
	MGESemaphore();
	virtual ~MGESemaphore();
private:
protected:
	sem_t *sem;
public:
	int Init(int pshared, unsigned int value);
	int Destroy();
	int TryWait();
	int SemWait();
	int TimedWait(const struct timespec * abstime);
	int Post();
	int PostMultiple(int count);
	int Open(const char * name, int oflag, mode_t &mode, unsigned int value);
	int Close();
	int Unlink(const char * name);
	int GetValue(int &sval);
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};

extern "C" class MGERWLock : public MGEObject {
public:
	MGERWLock();
	virtual ~MGERWLock();
private:
protected:
	pthread_rwlock_t lock;
	pthread_rwlockattr_t attr;
public:
	int Init();
	int Destroy();
	int TryReadLock();
	int TryWriteLock();
	int ReadLock();
	int TimedReadLock(const struct timespec *abstime);
	int WriteLock();
	int TimedWriteLock(const struct timespec *abstime);
	int Unlock();
	int AttribInit();
	int AttribDestroy();
	int GetpShared(int &pshared);
	int SetpShared(int pshared);
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};

extern "C" class MGESpinLock : public MGEObject {
public:
	MGESpinLock();
	virtual ~MGESpinLock();
private:
protected:
	pthread_spinlock_t lock;
public:
	int Init(int pshared);
	int Destroy();
	int Lock();
	int TryLock();
	int Unlock();
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};

extern "C" class MGEMutex : public MGEObject {
public:
	MGEMutex();
	virtual ~MGEMutex();
private:
protected:
	pthread_mutex_t mutex;
	pthread_mutexattr_t attr;
	pthread_cond_t cond;
	pthread_condattr_t condattr;
public:
	int Init();
	int Destroy();
	int Lock();
	int TimedLock(const struct timespec *abstime);
	int TryLock();
	int Unlock();
	int AttribInit();
	int AttribDestroy();
	int GetpShared(int &pshared);
	int SetpShared(int pshared);
	int GetType(int &kind);
	int SetType(int kind);
	int ConditionInit();
	int ConditionDestroy();
	int ConditionWait();
	int ConditionTimedwait(const struct timespec *abstime);
	int Signal();
	int Broadcast();
	int ConditionAttribInit();
	int ConditionAttribDestroy();
	int ConditionAttribGetpShared(int &pshared);
	int ConditionAttribSetpShared(int pshared);
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};

extern "C" class MGEBarrier : public MGEObject {
public:
	MGEBarrier();
	virtual ~MGEBarrier();
private:
protected:
	pthread_barrier_t barrier;
	pthread_barrierattr_t attr;
public:
	int Init(unsigned int count);
	int Destroy();
	int BarrierWait();
	int AttribInit();
	int AttribDestroy();
	int GetpShared(int &pshared);
	int SetpShared(int pshared);
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};


#endif