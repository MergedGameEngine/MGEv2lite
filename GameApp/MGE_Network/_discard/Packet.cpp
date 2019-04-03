///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _NETWORK_EXPORT

#include <stdio.h>
#include <string.h>
#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"

#undef _ARRAY_API
#define _ARRAY_API _NETWORK_API
#include "Packet.hpp"


MGEPacket::MGEPacket() {
	endian = MGEIOStream::little_endian;
	actualBufferLength = 0;
	totalBufferLength = 0;
	buffer.Resize(0);
	crypter0 = NULL;
	crypter1 = NULL;
	isBufferValid = FALSE;
	flag = 0;
	pointer = NULL;
	isEoF = FALSE;
	isError = FALSE;
	counter = 0;
}
MGEPacket::~MGEPacket() {
	buffer.Resize(0);
}

void MGEPacket::SetCrypter0(Blowfish &cpy0) {
	crypter0 = &cpy0;
}
void MGEPacket::SetCrypter1(Blowfish &cpy1) {
	crypter1 = &cpy1;
}
//	Read
const void *MGEPacket::Fill(unsigned int len) {
	if ( len < 4 ) len = 4;
	totalBufferLength = (( len - 1 ) / 4 + 1) * 4;
	len = totalBufferLength;
	buffer.Resize(len);
	actualBufferLength = 0;
	isBufferValid = FALSE;
	flag = 0;
	pointer = ((unsigned char *)buffer.GetBuffer()) + 4;
	isEoF = FALSE;
	isError = FALSE;
	counter = 0;
	return buffer.GetBuffer();
}
void MGEPacket::SetPacket(unsigned int len) {
	if ( len <= buffer.GetLength() ) {
	} else {
	}
	if ( buffer.GetLength() >= 4 ) {
		unsigned char *buf = (unsigned char*)buffer.GetBuffer();
		flag = buf[0];
		actualBufferLength = 0x00FFFFFF & ( ( buf[1] << 16 ) | ( buf[2] << 8 ) | buf[3] ); 
		isError = FALSE;
		if ( actualBufferLength > (buffer.GetLength() - 4) ) {
			flag = 0;
			actualBufferLength = 0; 
			isError = TRUE;
		}
	} else {
		flag = 0;
		actualBufferLength = 0; 
		isError = TRUE;
	}
	counter = 0;
}
BOOL32 MGEPacket::IsEncrypted() {
	if ( ( ( flag & 0x1 ) == FALSE ) && ( ( totalBufferLength / 4 ) >= 1 ) ) {
		pointer = ((unsigned char *)buffer.GetBuffer()) + 4;
		isBufferValid = TRUE;
	}
	return (BOOL32)(flag & 0x1);
}
void MGEPacket::Decrypt0() {
	if ( totalBufferLength >= 12 ) {
		pointer = ((unsigned char *)buffer.GetBuffer()) + 4;
		unsigned int cl = totalBufferLength / 4 - 1;
		if ( crypter0 != NULL ) {
			crypter0->Decrypt(pointer, cl);
			isBufferValid = TRUE;
			flag &= 0xFE;
		}
	}
}
void MGEPacket::Decrypt1() {
	if ( totalBufferLength >= 12 ) {
		pointer = ((unsigned char *)buffer.GetBuffer()) + 4;
		unsigned int cl = totalBufferLength / 4 - 1;
		if ( crypter1 != NULL ) {
			crypter1->Decrypt(pointer, cl);
			isBufferValid = TRUE;
			flag &= 0xFE;
		}
	}
}
//	Write
void MGEPacket::Reset(unsigned int len) {
	if ( len < 4 ) len = 4;
	totalBufferLength = (( len - 1 ) / 4 + 1) * 4;
	len = totalBufferLength;
	buffer.Resize(len);
	actualBufferLength = len;
	isBufferValid = FALSE;
	flag = 0;
	pointer = ((unsigned char *)buffer.GetBuffer()) + 4;
	isEoF = FALSE;
	isError = FALSE;
	counter = 0;
}
void MGEPacket::SetPacket() {
	actualBufferLength = counter;
	if ( buffer.GetLength() >= 4 ) {
		unsigned char *buf = (unsigned char *)buffer.GetBuffer();
		buf[0] = flag;
		buf[1] = (unsigned char)(actualBufferLength << 16);
		buf[2] = (unsigned char)(actualBufferLength << 8);
		buf[3] = (unsigned char)actualBufferLength;
	} else {
		isError = TRUE;
	}
	totalBufferLength = (( counter - 1 ) / 4 + 1) * 4;
	if ( buffer.GetLength() < totalBufferLength ) {
		buffer.Resize(totalBufferLength);
		pointer = ((unsigned char *)buffer.GetBuffer()) + 4;
	}
}

void MGEPacket::Encrypt0() {
	if ( totalBufferLength >= 12 ) {
		pointer = ((unsigned char *)buffer.GetBuffer()) + 4;
		unsigned int cl = totalBufferLength / 4 - 1;
		if ( crypter0 != NULL ) {
			crypter0->Encrypt(pointer, cl);
		}
		unsigned char *buf = (unsigned char *)buffer.GetBuffer();
		buf[0] = flag;
	}
	flag |= 0x01;
}
void MGEPacket::Encrypt1() {
	if ( totalBufferLength >= 12 ) {
		pointer = ((unsigned char *)buffer.GetBuffer()) + 4;
		unsigned int cl = totalBufferLength / 4 - 1;
		if ( crypter1 != NULL ) {
			crypter1->Encrypt(pointer, cl);
		}
		unsigned char *buf = (unsigned char *)buffer.GetBuffer();
		buf[0] = flag;
	}
	flag |= 0x01;
}

void *MGEPacket::GetBuffer(unsigned int &pl) {
	pl = totalBufferLength;
	return (void*)buffer.GetBuffer();
}

BOOL32 MGEPacket::Open() {
	switch (accessMode) {
		case MGEPacket::modeRead | MGEPacket::typeBinary :
			break;
		case MGEPacket::modeWrite | MGEPacket::typeBinary :
			break;
		case MGEPacket::modeReadWrite | MGEPacket::typeBinary :
			break;
		case MGEPacket::modeCreate | MGEPacket::typeBinary :
			break;
		case MGEPacket::modeRead | MGEPacket::typeText :
			break;
		case MGEPacket::modeWrite | MGEPacket::typeText :
			break;
		case MGEPacket::modeReadWrite | MGEPacket::typeText :
			break;
		case MGEPacket::modeCreate | MGEPacket::typeText :
			break;
		default:
			return FALSE;
	}
	return TRUE;
}

void MGEPacket::Close() {
}
void MGEPacket::SetEndian(unsigned int e) {
	if ( ( e == MGEIOStream::big_endian ) || ( e == MGEIOStream::little_endian ) ) {
		endian = e;
	} else {
		endian = MGEIOStream::little_endian;
	}
	if ( flag & 0x1 ) {
		if ( endian != LOCAL_MACHINE_ENDIAN ) {
			pointer = ((unsigned char *)buffer.GetBuffer()) + 4;
			totalBufferLength = ( buffer.GetLength() / 4 ) * 4;
			SwapEndian(pointer, totalBufferLength / 4 - 1, 4);
		}
	}
	flag = ( flag & 0xFD ) | ( endian << 1 );
}
unsigned int MGEPacket::GetEndian() {
	endian = ( flag & 0xFD ) >> 1;
	return endian;
}
void MGEPacket::SetLoadStore(unsigned int ls) {
	if ( ( ls == MGEPacket::load ) || ( ls == MGEPacket::store ) ) {
		loadstoreType = ls;
	} else {
		loadstoreType = MGEPacket::load;
	}
}
unsigned int MGEPacket::GetLoadStore() {
	return loadstoreType;
}

void MGEPacket::MemoryCopy(void *dest, const void *src, unsigned int length, BOOL32 swapendian) {
	unsigned char* dbuf = (unsigned char*)dest;
	unsigned char* sbuf = (unsigned char*)src;

	if ( swapendian ) {
		for (unsigned int i1 = 0 ; i1 < length ; i1 ++ ) {
			dbuf[i1] = sbuf[length - i1 - 1];
		}
	} else {
		for (unsigned int i1 = 0 ; i1 < length ; i1 ++ ) {
			dbuf[i1] = sbuf[i1];
		}
	}
}

void MGEPacket::MemoryCopy(void *dest, const void *src, unsigned int length) {
	BOOL32 isswap = ( endian != LOCAL_MACHINE_ENDIAN ) ;
	MemoryCopy (dest, src, length, isswap);
}

void MGEPacket::SwapEndian(void *src, unsigned int cells, unsigned int celllength) {
	unsigned char *cbuf = (unsigned char *)src;
	unsigned char *tcbuf = NULL;
	unsigned char temp = 0;
	unsigned int halflength = celllength / 2;
	for ( unsigned int i2 = 0 ; i2 < cells ; i2 ++ ) {
		tcbuf = &cbuf[i2 * celllength];
		for ( unsigned int i3 = 0 ; i3 < halflength ; i3 ++ ) {
			temp = tcbuf[i3];tcbuf[i3] = tcbuf[celllength - i3 - 1];tcbuf[celllength - i3 - 1] = temp;
		}
	}
}

unsigned int MGEPacket::Read(const void* buf, const unsigned int length) {
	if ( (counter + length) <= actualBufferLength ) {
		if ( isBufferValid ) {
			MemoryCopy ( (void*)buf, &(pointer[counter]), length );
			counter += length;
			return TRUE;
		}
	}
	isError = TRUE;
	return FALSE;
}
unsigned int MGEPacket::Write(const void* buf, const unsigned int length) {
	if ( (counter + length) <= actualBufferLength ) {
		MemoryCopy ( &(pointer[counter]), buf, length );
		counter += length;
		return TRUE;
	}
	isError = TRUE;
	return FALSE;
}
unsigned int MGEPacket::ReadBuffer(const void* buf, const unsigned int cells, const unsigned int celllength) {
	if ( (counter + cells * celllength) <= actualBufferLength ) {
		if ( isBufferValid ) {
			for ( unsigned int i1 = 0 ; i1 < cells ; i1 ++ ) {
				MemoryCopy ( (void*)buf, &(pointer[counter]), celllength );
				counter += celllength;
			}
			return TRUE;
		}
	}
	isError = TRUE;
	return FALSE;
}
unsigned int MGEPacket::WriteBuffer(const void* buf, const unsigned int cells, const unsigned int celllength) {
	if ( (counter + cells * celllength) <= actualBufferLength ) {
		for ( unsigned int i1 = 0 ; i1 < cells ; i1 ++ ) {
			MemoryCopy ( &(pointer[counter]), buf, celllength );
			counter += celllength;
		}
		return TRUE;
	}
	isError = TRUE;
	return FALSE;
}
unsigned int MGEPacket::Seek(unsigned int length) {
	if ( length < actualBufferLength ) {
		counter = length;
		return TRUE;
	} else if ( length == actualBufferLength ) {
		counter = length;
		isEoF = TRUE;
		return TRUE;
	}
	isError = TRUE;
	return FALSE;
}
unsigned int MGEPacket::Seek(unsigned int begin, unsigned int length) {
	if ( ( begin + length ) < actualBufferLength ) {
		counter = begin + length;
		return TRUE;
	} else if ( ( begin + length ) == actualBufferLength ) {
		counter = begin + length;
		isEoF = TRUE;
		return TRUE;
	}
	isError = TRUE;
	return FALSE;
}
BOOL32 MGEPacket::IsEoF() {
	return isEoF;
}

unsigned int MGEPacket::GetPosition() {
	return counter;
}

const char *MGEPacket::GetClassName() {
	return "TPacket";
}
BOOL32 MGEPacket::IsInstanceof(const char* className) {
	if ( strcmp("TPacket", className) == 0 ) {
		return TRUE;
	}
	if ( strcmp("IIOStream", className) == 0 ) {
		return TRUE;
	}
	if ( strcmp("IObject", className) == 0 ) {
		return TRUE;
	}
	return FALSE;
}
BOOL32 MGEPacket::IsEqualto(MGEObject &obj) {
	return FALSE;
}
void MGEPacket::Serialize(MGEIOStream &iio) {
}


void MGEPacket::Flush() {
}
	
void MGEPacket::SetOpenMode(unsigned int mode) {
	accessMode = mode;
}

int MGEPacket::GetLength() {
	return actualBufferLength;
}
