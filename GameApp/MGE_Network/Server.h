///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _SERVER_H_
#define _SERVER_H_

#include "../MGE_Thread/Thread.h"

extern "C" class MGEServer : public MGEThread {
public:
	MGEServer();
	virtual ~MGEServer();
public:
public:
public:
	MGESocket serverSocket;
	MGERefArray<MGEClientHandler> clientHandlers;
	MGERWLock arrayLock;
public:
	BOOL32 Startup();
	virtual void Run();
	BOOL32 Cleanup();

	virtual MGEClientHandler *NewClientHandler();
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};

#endif