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
#include "winsock.h"
#undef GetClassName
#include "..\Base\Type.h"
#include "..\Base\Base.h"

#include "TSocket.h"
#include "ServerThread.h"


_NETWORK_API TServerThread::TServerThread() {
}

_NETWORK_API TServerThread::~TServerThread() {
}

char _NETWORK_API *TServerThread::GetClassName() {
	return "TServerThread";
}
int _NETWORK_API TServerThread::GetClassCode() {
	return CLSID_TServer;
}
int _NETWORK_API TServerThread::GetHashCode() {
	return 1;
}
BOOL32 _NETWORK_API TServerThread::IsInstanceof(const char* className) {
	if (strcmp("TServerThread", className) == 0) {
		return TRUE;
	}
	return TThread::IsInstanceof(className);
}
BOOL32 _NETWORK_API TServerThread::IsEqualto(IObject &obj) {
	return FALSE;
}
void _NETWORK_API TServerThread::Serialize(IIOStream &iio) {
}
void _NETWORK_API TServerThread::Wait() {
}
void _NETWORK_API TServerThread::Notify() {
}


BOOL32 _NETWORK_API TServerThread::Startup() {
	////unsigned short version = MAKEWORD(2,0);
	////int retCode = serverSocket.Startup(version);
	////if ( retCode != 0 ) {
	////	printf("\n WSAStartup Error \n");
	////	return FALSE;
	////}
	serverSocket.Socket(AF_INET,SOCK_STREAM,0);
	if ( serverSocket.Bind() == FALSE ) {//°ó¶¨
		return FALSE;
	}
	if ( serverSocket.Listen(10) == FALSE ) {//¼àÌý
		return FALSE;
	}
	printf("\nServer is ready\n");

	AttribInit();
	Create();

	return TRUE;
}

void _NETWORK_API TServerThread::Run() {
	while(TRUE) {
		serverSocket.SetInterval(0, 0);
		serverSocket.Select(TRUE, FALSE, FALSE, TRUE);
		if (serverSocket.IsReadable()) {
			OnAccept(0);
		}
		Delay(0, 50000);
	}
}

void _NETWORK_API TServerThread::OnAccept(int nErrorCode) {
}

BOOL32 _NETWORK_API TServerThread::Accept(TClientHandlerThread &_client) {
	return serverSocket.Accept(_client.clientSocket);
}

BOOL32 _NETWORK_API TServerThread::Cleanup() {
	serverSocket.CloseSocket();
	////serverSocket.Cleanup();
	return TRUE;
}

