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
#include "ClientHandlerThread.h"


_NETWORK_API TClientHandlerThread::TClientHandlerThread() {
}

_NETWORK_API TClientHandlerThread::~TClientHandlerThread() {
}

char _NETWORK_API *TClientHandlerThread::GetClassName() {
	return "TClientHandlerThread";
}
int _NETWORK_API TClientHandlerThread::GetClassCode() {
	return CLSID_TClientHandler;
}
int _NETWORK_API TClientHandlerThread::GetHashCode() {
	return 1;
}
BOOL32 _NETWORK_API TClientHandlerThread::IsInstanceof(const char* className) {
	if (strcmp("TClientHandlerThread", className) == 0) {
		return TRUE;
	}
	return TThread::IsInstanceof(className);
}
BOOL32 _NETWORK_API TClientHandlerThread::IsEqualto(IObject &obj) {
	return FALSE;
}
void _NETWORK_API TClientHandlerThread::Serialize(IIOStream &iio) {
}
void _NETWORK_API TClientHandlerThread::Wait() {
}
void _NETWORK_API TClientHandlerThread::Notify() {
}


int _NETWORK_API TClientHandlerThread::Send(const void *buf, int length, int flag) {
	return clientSocket.Send((const char *)buf, length, flag);
}

int _NETWORK_API TClientHandlerThread::Receive(void *buf, int length, int flag) {
	return clientSocket.Receive((char *)buf, length, flag);
}

int _NETWORK_API TClientHandlerThread::NonBlockSend(const void *buf, int length, int flag) {
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

int _NETWORK_API TClientHandlerThread::NonBlockReceive(void *buf, int length, int flag) {
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

void _NETWORK_API TClientHandlerThread::Run() {
	while(TRUE) {
		clientSocket.SetInterval(0, 0);
		clientSocket.Select(TRUE, FALSE, FALSE, TRUE);
		if (clientSocket.IsReadable()) {
			OnReceive(0);
		}
		Delay(0, 50000);
	}
}

void _NETWORK_API TClientHandlerThread::OnReceive(int nErrorCode) {
}


BOOL32 _NETWORK_API TClientHandlerThread::Cleanup() {
	clientSocket.CloseSocket();
	////clientSocket.Cleanup();
	return TRUE;
}


BOOL32 _NETWORK_API TClientHandlerThread::Startup() {

	AttribInit();
	Create();

	return TRUE;
}
