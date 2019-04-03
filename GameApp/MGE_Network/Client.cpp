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
#include "Client.hpp"


MGEClient::MGEClient() {
}

MGEClient::~MGEClient() {
}

const char *MGEClient::GetClassName() {
	return "TClient";
}


BOOL32 MGEClient::IsInstanceof(const char* className) {
	if (strcmp("TClient", className) == 0) {
		return TRUE;
	}
	return MGEClient::IsInstanceof(className);
}

BOOL32 MGEClient::Startup() {
	clientSocket.Socket(_SOCKET_FAMILY_IPV4_,_SOCKET_TYPE_STREAM_,_SOCKET_PROTOCOL_TCP_);
	if ( clientSocket.Connect() == FALSE ) {
		clientSocket.CloseSocket();

		return FALSE;
	}
	return TRUE;
}

int MGEClient::Send(const char *buf, int length) {
	unsigned int paklen = 0;
	printf("\nNEW SOCKET = [%4X]\n", clientSocket.sock);
	return clientSocket.Send(buf, length, 0);
}
int MGEClient::Receive(char *buf, int length) {
	return clientSocket.Receive(buf, length, 0);;
}
void MGEClient::Run() {
}

BOOL32 MGEClient::Cleanup() {
	clientSocket.CloseSocket();
	return TRUE;
}

