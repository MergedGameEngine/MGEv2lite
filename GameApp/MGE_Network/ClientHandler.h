///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _CLIENTHANDLER_H_
#define _CLIENTHANDLER_H_

#include "../MGE_Thread/Thread.h"

extern "C" class MGEClientHandler : public MGEThread {
public:
	MGEClientHandler();
	virtual ~MGEClientHandler();
public:
public:
	MGESocket clientSocket;
public:
	int Send(const char *buf, int length);
	int Receive(char *buf, int length);
	virtual void Run();
	BOOL32 Cleanup();
	int NonBlockReceive(char *buf, int length);
	virtual void PacketHandler(char *buf);
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};

#endif