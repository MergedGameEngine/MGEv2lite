#define _BASE_IMPORT
#define _NETWORK_EXPORT

#include "string.h"
#include "..\Base\Type.h"
#include "..\Base\Base.h"

#undef _ARRAY_API
#define _ARRAY_API _NETWORK_API
#include "Packet.hpp"
#include "NetworkIOStream.h"
#include "String.h"

_NETWORK_API TNetworkIOStream::TNetworkIOStream() {
	package = NULL;
}
_NETWORK_API TNetworkIOStream::TNetworkIOStream(TPacket *p) {
	package = p;
}

_NETWORK_API TNetworkIOStream::~TNetworkIOStream() {
}

void _NETWORK_API TNetworkIOStream::SetPacket(TPacket *p) {
	package = p;
}


BOOL32 _NETWORK_API TNetworkIOStream::Open() {
	if ( package != NULL ) {
		return package->Open();
	} else {
		return FALSE;
	}
}
void _NETWORK_API TNetworkIOStream::Close() {
	if ( package != NULL ) {
		package->Close();
		package = NULL;
	}
}
void _NETWORK_API TNetworkIOStream::SetEndian(unsigned int e) {
	if ( ( e == TNetworkIOStream::big_endian ) || ( e == TNetworkIOStream::little_endian ) ) {
		endian = e;
	} else {
		endian = TNetworkIOStream::big_endian;
	}
}
unsigned int _NETWORK_API TNetworkIOStream::GetEndian() {
	return endian;
}
void _NETWORK_API TNetworkIOStream::SetLoadStore(unsigned int ls) {
	if ( ( ls == TNetworkIOStream::load ) || ( ls == TNetworkIOStream::store ) ) {
		loadstoreType = ls;
	} else {
		loadstoreType = TNetworkIOStream::load;
	}
}
unsigned int _NETWORK_API TNetworkIOStream::GetLoadStore() {
	return loadstoreType;
}

void _NETWORK_API TNetworkIOStream::swapEndian(const void* buffer, unsigned int length) {
	unsigned char* buf = (unsigned char*)buffer;
	unsigned char temp;
	int l = length / 2;
	for (int i = 0 ; i < l ; i ++ ) {
		temp = buf[i];
		buf[i] = buf[length - i - 1];
		buf[length - i - 1] = temp;
	}
}

unsigned int _NETWORK_API TNetworkIOStream::Read(const void* buf, const unsigned int length) {
	if ( package == NULL ) { return 0xFFFFFFFF;}
	int retcode = (int)package->Read(buf, length, 1);
	if (endian != LOCAL_MACHINE_ENDIAN) {
		swapEndian(buf, length);
	}
	return retcode;
}
unsigned int _NETWORK_API TNetworkIOStream::Write(const void* buf, const unsigned int length) {
	if ( package == NULL ) { return 0xFFFFFFFF;}
	if (endian != LOCAL_MACHINE_ENDIAN) {
		swapEndian(buf, length);
	}
	return (int)package->Write(buf, length, 1);
}
unsigned int _NETWORK_API TNetworkIOStream::ReadBuffer(const void* buf, const unsigned int cells, const unsigned int celllength) {
	if ( package == NULL ) { return 0xFFFFFFFF;}
	int retcode = package->Read(buf, celllength, cells);
	if (endian != LOCAL_MACHINE_ENDIAN) {
		unsigned char * pBuf = (unsigned char * )buf;
		for ( unsigned int i = 0 ; i < cells ; i ++ ) {
			swapEndian(&(pBuf[celllength * i]), celllength);
		}
	}
	return retcode;
}
unsigned int _NETWORK_API TNetworkIOStream::WriteBuffer(const void* buf, const unsigned int cells, const unsigned int celllength) {
	if ( package == NULL ) { return 0xFFFFFFFF;}
	if (endian != LOCAL_MACHINE_ENDIAN) {
		unsigned char * pBuf = (unsigned char * )buf;
		for ( unsigned int i = 0 ; i < cells ; i ++ ) {
			swapEndian(&(pBuf[celllength * i]), celllength);
		}
	}
	return package->Write(buf, celllength, cells);
}
unsigned int _NETWORK_API TNetworkIOStream::Seek(unsigned int length) {
	if ( package == NULL ) { return 0xFFFFFFFF;}
	return (int)package->Seek(length, TPacket::seek_cur);
}
unsigned int _NETWORK_API TNetworkIOStream::Seek(unsigned int begin, unsigned int length) {
	if ( package == NULL ) { return 0xFFFFFFFF;}
	package->Seek(begin, TPacket::seek_set);
	return (int)package->Seek(length, TPacket::seek_cur);
}
BOOL32 _NETWORK_API TNetworkIOStream::IsEoF() {
	if ( package == NULL ) { return 0xFFFFFFFF;}
	return package->IsEof();
}

unsigned int _NETWORK_API TNetworkIOStream::GetPosition() {
	if ( package == NULL ) { return 0xFFFFFFFF;}
	return package->GetPosition();
}

char _NETWORK_API *TNetworkIOStream::GetClassName() {
	return "TNetworkIOStream";
}
int _NETWORK_API TNetworkIOStream::GetClassCode() {
	return CLSID_TNetworkIOStream;
}
int _NETWORK_API TNetworkIOStream::GetHashCode() {
	return 1;
}
BOOL32 _NETWORK_API TNetworkIOStream::IsInstanceof(const char* className) {
	if ( strcmp("TNetworkIOStream", className) == 0 ) {
		return TRUE;
	}
	return FALSE;
}
BOOL32 _NETWORK_API TNetworkIOStream::IsEqualto(IObject &obj) {
	return FALSE;
}
void _NETWORK_API TNetworkIOStream::Serialize(IIOStream &iio) {
}
void _NETWORK_API TNetworkIOStream::Wait() {
}
void _NETWORK_API TNetworkIOStream::Notify() {
}