///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _THREAD_IMPORT
#define _NETWORK_EXPORT

#include "string.h"

#ifdef WIN32

#include "winsock.h"

#else

#include "sys/socket.h"

#endif

#undef GetClassName
#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"

#include "TSocket.h"
#undef _ARRAY_API
#define _ARRAY_API _NETWORK_API
//#include "Packet.hpp"
#include "ClientHandler.hpp"
#include "Server.hpp"


MGEServer::MGEServer() {
	arrayLock.AttribInit();
	arrayLock.Init();
}

MGEServer::~MGEServer() {
	arrayLock.Destroy();
	arrayLock.AttribDestroy();
}

const char *MGEServer::GetClassName() {
	return "MGEServer";
}

BOOL32 MGEServer::IsInstanceof(const char* className) {
	if (strcmp("MGEServer", className) == 0) {
		return TRUE;
	}
	return MGEThread::IsInstanceof(className);
}

BOOL32 MGEServer::Startup() {
	serverSocket.Socket(_SOCKET_FAMILY_IPV4_,_SOCKET_TYPE_STREAM_,_SOCKET_PROTOCOL_TCP_);
	if ( serverSocket.Bind() == FALSE ) {
		return FALSE;
	}
	if ( serverSocket.Listen(10) == FALSE ) {
		return FALSE;
	}
	printf("\nServer is ready\n");

	AttribInit();
	Create();

	return TRUE;
}

void MGEServer::Run() {
	while(TRUE) {
		serverSocket.SetInterval(0, 0);
		serverSocket.Select(TRUE, FALSE, FALSE, TRUE);
//		if (serverSocket.IsReadable()) {
			MGEClientHandler *newbie = NewClientHandler();
			arrayLock.WriteLock();
			clientHandlers.Resize(clientHandlers.GetLength() + 1);
			clientHandlers.Set(clientHandlers.GetLength() - 1, newbie);
			arrayLock.Unlock();
			if ( serverSocket.Accept(newbie->clientSocket) == FALSE ) {
				printf("SOCKET serverSocket error\n");
				//delete newbie;
			} else {
				printf("Successfully accept a new client\n");
			}
//		}
	}
}

BOOL32 MGEServer::Cleanup() {
	serverSocket.CloseSocket();
	return TRUE;
}

MGEClientHandler *MGEServer::NewClientHandler() {
	return new MGEClientHandler();
}
