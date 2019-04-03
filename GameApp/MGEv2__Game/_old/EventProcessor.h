///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _EVENTPROCESSOR_H_
#define _EVENTPROCESSOR_H_

#include "../Base/Type.h"
#include "../Base/Base.h"
#include "../Thread/Thread.h"

extern "C" class _CORE_API TEventProcessor : public TThread {
public:
	TEventProcessor();
	virtual ~TEventProcessor();
public:
	TArray<TEvent> eventQueue;
	TRefArray<TEventListener> listeners;
	TRWLock queueRWLock;
	TRWLock arrayRWLock;
	unsigned int queueHead;
	unsigned int queueTail;
	unsigned int queueLength;
	unsigned short pointId;
public:
	unsigned int interval;
public:
	virtual void Run();
	void PostEvent(TEvent &e);
	void AddListener(TEventListener &listener);
public:
	virtual char* GetClassName();
	virtual int GetClassCode();
	virtual int GetHashCode();
	virtual BOOL32 IsInstanceof(const char* className);
	virtual BOOL32 IsEqualto(IObject &obj);
	virtual void Serialize(IIOStream &iio);
	virtual void Wait();
	virtual void Notify();
};


#endif