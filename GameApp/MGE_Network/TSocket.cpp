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

#ifdef _LINUX_ 

#include "sys/socket.h"
#include "unistd.h"
#include "netinet/in.h"
#include "arpa/inet.h"

#endif

#ifdef WIN32

#include "winsock.h"

#endif

#undef GetClassName
#undef SetPort
#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "TSocket.h"

MGESocket::MGESocket() {
	sock = 0;
}
MGESocket::~MGESocket() {
}
void MGESocket::SetAddress(char *ip) {
	addr.sin_addr.s_addr = inet_addr(ip);
///	addr.sin_addr.S_un.S_addr = inet_addr(ip);
}
void MGESocket::SetFamily(short f) {
	if ( f == _SOCKET_FAMILY_IPV4_ ) {
		addr.sin_family = AF_INET;
	}
}
void MGESocket::SetPort(unsigned short p) {
	addr.sin_port = htons(p);
}
int MGESocket::SetOption(int _level, int _optname, const char * _optvar, int _optlen) {
	return setsockopt(sock, _level, _optname, _optvar, _optlen);
}

void MGESocket::SetAddress(unsigned long _IPv4) {
	addr.sin_addr.s_addr = _IPv4;
///	addr.sin_addr.S_un.S_addr = _IPv4;
}
int MGESocket::Startup() {
	
#ifdef WIN32

	WSADATA wsaData;
	return WSAStartup(MAKEWORD(2,0), &wsaData);

#else

	return 0;

#endif

}

int MGESocket::GetLastError() {
	
#ifdef WIN32

	return WSAGetLastError();

#else

	return 0;

#endif

}

int MGESocket::Cleanup() {
	
#ifdef WIN32

	return WSACleanup();

#else

	return 0;

#endif

}

BOOL32 MGESocket::CloseSocket() {
	if ( closesocket(sock) == SOCKET_ERROR ) {
		return FALSE;
	}
	return TRUE;
}

int MGESocket::Receive(char *buf, int length, int flag) {
	return recv(sock, buf, length, flag);
}
int MGESocket::Send(const char *buf, int length, int flag) {
	return send(sock, buf, length, flag);
}

BOOL32 MGESocket::Socket(int family, int type, int protocol) {
	if ( family == _SOCKET_FAMILY_IPV4_ ) {
		family = AF_INET;//IPv4协议
	}
	if ( type == _SOCKET_TYPE_STREAM_ ) {
		type = SOCK_STREAM;//字节流套接字
	}
	if ( protocol == _SOCKET_PROTOCOL_TCP_ ) {
		protocol = IPPROTO_TCP;//TCP传输协议
	}
	if ( ( sock = socket(family, type, protocol) ) == INVALID_SOCKET ) {
		return FALSE;
	}
	return TRUE;
}

//	Used by server
BOOL32 MGESocket::Bind() {
	if ( bind(sock, (sockaddr*)&addr, sizeof(sockaddr)) == SOCKET_ERROR ) {
		return FALSE;
	}
	return TRUE;
}
BOOL32 MGESocket::Listen(int backlog) {
	if ( listen(sock, backlog) == SOCKET_ERROR ) {
		return FALSE;
	}
	return TRUE; 
}

BOOL32 MGESocket::Accept(MGESocket &tar) {

#ifndef WIN32 

	unsigned int sockaddrlen = sizeof(sockaddr);

#else

	int sockaddrlen = sizeof(sockaddr);

#endif

	if ( (tar.sock = accept(sock, (sockaddr*)&tar.addr, &sockaddrlen)) == INVALID_SOCKET ) {
		return FALSE;
	}
	return TRUE;
}

//	Used by client
BOOL32 MGESocket::Connect() {
	if ( connect(sock, (sockaddr*)&addr, sizeof(sockaddr)) == SOCKET_ERROR ) {
		return FALSE;
	}
	return TRUE;
}


//	Probo
void MGESocket::SetInterval(unsigned int sec, unsigned int usec) {
	interval.tv_sec = (long)sec;
	interval.tv_usec = (long)usec;
}
BOOL32 MGESocket::Select(BOOL32 enableread, BOOL32 enablewrite, BOOL32 enableexcept, BOOL32 enabletimeval) {
	fd_set *pfdrecv = NULL;
	fd_set *pfdsend = NULL;
	fd_set *pfdexcp = NULL;
	timeval *pinterval = NULL;
	if ( enableread ) {
		FD_ZERO(&fdrecv);
		FD_SET(sock, &fdrecv);
		pfdrecv = &fdrecv;
	}
	if ( enablewrite ) {
		FD_ZERO(&fdsend);
		FD_SET(sock, &fdsend);
		pfdsend = &fdsend;
	}
	if ( enableexcept ) {
		FD_ZERO(&fdexcp);
		FD_SET(sock, &fdexcp);
		pfdexcp = &fdexcp;
	}
	if ( enabletimeval ) {
		pinterval = &interval;
	}
	if ( enableread || enablewrite || enableexcept ) {
		if ( select(0, pfdrecv, pfdsend, pfdexcp, pinterval) == SOCKET_ERROR ) {
			return FALSE;
		}
	} else {
		return FALSE;
	}
	return TRUE;
}
BOOL32 MGESocket::IsReadable() {
	if(FD_ISSET(sock, &fdrecv)) {
		return TRUE;
	} else {
		return FALSE;
	}
}
BOOL32 MGESocket::IsWritable() {
	if(FD_ISSET(sock, &fdsend)) {
		return TRUE;
	} else {
		return FALSE;
	}
}
