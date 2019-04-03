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
#include "../MGE_Base/Type.h"
#include "TSocket.h"
///#include "winsock.h"
#undef GetClassName
#include "../MGE_Base/Base.h"

#undef _ARRAY_API
#define _ARRAY_API _NETWORK_API
//#include "Packet.hpp"
#include "ClientHandler.hpp"


MGEClientHandler::MGEClientHandler() {
}

MGEClientHandler::~MGEClientHandler() {
}

const char *MGEClientHandler::GetClassName() {
	return "MGEClientHandler";
}

BOOL32 MGEClientHandler::IsInstanceof(const char* className) {
	if (strcmp("MGEClientHandler", className) == 0) {
		return TRUE;
	}
	return MGEThread::IsInstanceof(className);
}


int MGEClientHandler::Send(const char *buf, int length) {
	unsigned int paklen = 0;
	printf("\nNEW SOCKET = [%4X]\n", clientSocket.sock);
	return clientSocket.Send(buf, length, 0);
}

int MGEClientHandler::NonBlockReceive(char *buf, int length) {
	clientSocket.SetInterval(0, 0);
	clientSocket.Select(TRUE, FALSE, FALSE, TRUE);
	if(clientSocket.IsReadable()) {
		return clientSocket.Receive(buf, length, 0);
	} else {
	}
	return 0;
}

int MGEClientHandler::Receive(char *buf, int length) {
	return clientSocket.Receive(buf, length, 0);
}
void MGEClientHandler::Run() {
}

BOOL32 MGEClientHandler::Cleanup() {
	clientSocket.CloseSocket();
	////clientSocket.Cleanup();
	return TRUE;
}

void MGEClientHandler::PacketHandler(char *buf) {
}
