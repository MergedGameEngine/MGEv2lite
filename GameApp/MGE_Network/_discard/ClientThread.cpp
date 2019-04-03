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
#include "ClientThread.h"


_NETWORK_API TClientThread::TClientThread() {
}

_NETWORK_API TClientThread::~TClientThread() {
}

char _NETWORK_API *TClientThread::GetClassName() {
	return "TClientThread";
}
int _NETWORK_API TClientThread::GetClassCode() {
	return CLSID_TClient;
}
int _NETWORK_API TClientThread::GetHashCode() {
	return 1;
}
BOOL32 _NETWORK_API TClientThread::IsInstanceof(const char* className) {
	if (strcmp("TClientThread", className) == 0) {
		return TRUE;
	}
	return TThread::IsInstanceof(className);
}
BOOL32 _NETWORK_API TClientThread::IsEqualto(IObject &obj) {
	return FALSE;
}
void _NETWORK_API TClientThread::Serialize(IIOStream &iio) {
}
void _NETWORK_API TClientThread::Wait() {
}
void _NETWORK_API TClientThread::Notify() {
}


int _NETWORK_API TClientThread::Send(const void *buf, int length, int flag) {
	return clientSocket.Send((const char *)buf, length, flag);
}

int _NETWORK_API TClientThread::Receive(void *buf, int length, int flag) {
	return clientSocket.Receive((char *)buf, length, flag);
}

int _NETWORK_API TClientThread::NonBlockSend(const void *buf, int length, int flag) {
	int rcv = 0;
	clientSocket.SetInterval(0, 0);
	clientSocket.Select(FALSE, TRUE, FALSE, TRUE);
	if(clientSocket.IsWritable()) {
		rcv = clientSocket.Send((const char *)buf, length, flag);
		if ( rcv < 0 ) {
			rcv = WSAGetLastError();
			rcv |= 0xFFFF0000;
		}
	} else {
	}
	return rcv;
}

int _NETWORK_API TClientThread::NonBlockReceive(void *buf, int length, int flag) {
	int rcv = 0;
	clientSocket.SetInterval(0, 0);
	clientSocket.Select(TRUE, FALSE, FALSE, TRUE);
	if(clientSocket.IsReadable()) {
		rcv = clientSocket.Receive((char *)buf, length, flag);
		if ( rcv < 0 ) {
			rcv = WSAGetLastError();
			rcv |= 0xFFFF0000;
		}
	} else {
	}
	return rcv;
}

void _NETWORK_API TClientThread::Run() {
	while(TRUE) {
		clientSocket.SetInterval(0, 0);
		clientSocket.Select(TRUE, FALSE, FALSE, TRUE);
		if (clientSocket.IsReadable()) {
			OnReceive(0);
		}
	}
}


BOOL32 _NETWORK_API TClientThread::Startup() {
	////unsigned short version = MAKEWORD(2,0);
	////int retCode = clientSocket.Startup(version);
	////if ( retCode != 0 ) {
	////	printf("\n WSAStartup Error \n");
	////	return FALSE;
	////}
	clientSocket.Socket(AF_INET,SOCK_STREAM,0);
	if ( clientSocket.Connect() == FALSE ) {//主动连接服务器
		clientSocket.CloseSocket();
		OutputDebugStringA("\nCONNECT FAILED\n");
		return FALSE;
	}

	AttribInit();
	Create();

	return TRUE;
}


void _NETWORK_API TClientThread::OnReceive(int nErrorCode) {
}


BOOL32 _NETWORK_API TClientThread::Cleanup() {
	clientSocket.CloseSocket();
	////clientSocket.Cleanup();
	return TRUE;
}

