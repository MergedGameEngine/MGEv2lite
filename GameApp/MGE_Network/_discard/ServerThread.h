///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2016
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _SERVERTHREAD_H_
#define _SERVERTHREAD_H_

#include "../Thread/Thread.h"
#include "ClientHandlerThread.h"

extern "C" class _NETWORK_API TServerThread : public TThread {
public:
	TServerThread();
	virtual ~TServerThread();
public:
public:
public:
	TSocket serverSocket;
public:
	BOOL32 Startup();

	virtual void Run();
	BOOL32 Cleanup();

public:
	virtual void OnAccept(int nErrorCode);
	BOOL32 Accept(TClientHandlerThread &_client);

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