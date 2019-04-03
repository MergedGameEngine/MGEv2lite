///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _EVENTLISTENER_H_
#define _EVENTLISTENER_H_

#include "../Base/Type.h"
#include "../Base/Base.h"
#include "../Thread/Thread.h"

class TEventListener;
class TEventProcessor;

struct TEvent {
	unsigned int uid;
	unsigned int actionCode;
	TEventListener *subject;
	unsigned short level;	//	Address Begin
	unsigned short area;
	unsigned short section;
	unsigned short point;	//	Address End
};

extern "C" class _CORE_API TEventListener : public TThread {
public:
	TEventListener();
	virtual ~TEventListener();
public:
	TRWLock rwLock;
	TEvent *eventOccur;
public:
	unsigned int uid;
	unsigned int actionCode;
	unsigned short aLevel;
	unsigned short aArea;
	unsigned short aSection;
	unsigned short aPoint;
public:
	TEventProcessor *eventProc;
public:
	virtual void Run();
	virtual void EventHandler(TEvent &e);
	void EventOccur(TEvent &e);
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