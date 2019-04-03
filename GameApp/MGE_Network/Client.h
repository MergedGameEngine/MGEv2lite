///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "../MGE_Thread/Thread.h"

extern "C" class MGEClient : public MGEThread {
public:
	MGEClient();
	virtual ~MGEClient();
public:
public:
	MGESocket clientSocket;
public:
	BOOL32 Startup();
	int Send(const char *buf, int length);
	int Receive(char *buf, int length);
	virtual void Run();
	BOOL32 Cleanup();
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};

#endif