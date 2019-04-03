///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _TSOCKET_H_
#define _TSOCKET_H_

#ifndef WIN32 

#include "sys/socket.h"
#include "unistd.h"
#include "netinet/in.h"
#include "arpa/inet.h"

#else

#include "winsock.h"

#endif

#ifndef WIN32

#define closesocket close

#endif

#define _SOCKET_FAMILY_IPV4_    4
#define _SOCKET_TYPE_STREAM_    0
#define _SOCKET_PROTOCOL_TCP_   0

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif

extern "C" class MGESocket {
public:
	MGESocket();
	virtual ~MGESocket();
public:
	sockaddr_in addr;
	int sock;
	///SOCKET sock;

	fd_set fdrecv;
	fd_set fdsend;
	fd_set fdexcp;
	timeval interval;
public:
public:
	void SetAddress(char *ip);
	void SetFamily(short f);
	void SetPort(unsigned short p);
	int SetOption(int _level, int _optname, const char * _optvar, int _optlen);
	void SetAddress(unsigned long _IPv4);
	static int Startup();
	static int GetLastError();
	static int Cleanup();
	BOOL32 CloseSocket();

	int Receive(char *buf, int length, int flag);
	int Send(const char *buf, int length, int flag);

	BOOL32 Socket(int family, int type, int protocol);

//	Used by server
	BOOL32 Bind();
	BOOL32 Listen(int backlog);

	BOOL32 Accept(MGESocket &tar);

//	Used by client
	BOOL32 Connect();


//	Probo
	void SetInterval(unsigned int sec, unsigned int usec);
	BOOL32 Select(BOOL32 enableread, BOOL32 enablewrite, BOOL32 enableexcept, BOOL32 enabletimeval);
	BOOL32 IsReadable();
	BOOL32 IsWritable();
};

#endif