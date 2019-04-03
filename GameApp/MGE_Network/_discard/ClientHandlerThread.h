///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2016
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _CLIENTHANDLERTHREAD_H_
#define _CLIENTHANDLERTHREAD_H_

#include "../Thread/Thread.h"

extern "C" class _NETWORK_API TClientHandlerThread : public TThread {
public:
	TClientHandlerThread();
	virtual ~TClientHandlerThread();
public:
public:
	TSocket clientSocket;
public:
	int Send(const void *buf, int length, int flag);
	int Receive(void *buf, int length, int flag);
	int NonBlockSend(const void *buf, int length, int flag);
	int NonBlockReceive(void *buf, int length, int flag);

	BOOL32 Startup();

	BOOL32 Cleanup();

	virtual void OnReceive(int nErrorCode);
	virtual void Run();
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