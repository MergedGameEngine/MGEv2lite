#define _BASE_IMPORT
#define _NETWORK_EXPORT

#include "Stdio.h"
#include "String.h"
#include "..\Base\Type.h"
#include "..\Base\Base.h"

#undef _ARRAY_API
#define _ARRAY_API _NETWORK_API
#include "Packet.hpp"


_NETWORK_API TPacket::TPacket() {
	endian = IIOStream::little_endian;
	actualBufferLength = 0;
	lBufferLength = 0;
	buffer0.Resize(0);
	buffer1.Resize(0);
	crypter0 = NULL;
	crypter1 = NULL;
	isBuffer0Valid = FALSE;
	isBuffer1Valid = FALSE;
	flag = 0;
	pointer = NULL;
	isEoF = FALSE;
	isError = FALSE;
	counter = 0;
}
_NETWORK_API TPacket::~TPacket() {
	buffer0.Resize(0);
	buffer1.Resize(0);
}

void _NETWORK_API TPacket::SetCrypter0(Blowfish &cpy0) {
	crypter0 = &cpy0;
}
void _NETWORK_API TPacket::SetCrypter1(Blowfish &cpy1) {
	crypter1 = &cpy1;
}
//	Read
const void _NETWORK_API *TPacket::Fill(unsigned int len) {
	if ( len < 4 ) len = 4;
	lBufferLength = ( len - 1 ) / 4 + 1;
	len = lBufferLength * 4;
	buffer0.Resize(len);
	buffer1.Resize(len);
	actualBufferLength = 0;
	isBuffer0Valid = FALSE;
	isBuffer1Valid = FALSE;
	isBufferValid = FALSE;
	flag = 0;
	pointer = ((unsigned char *)buffer0.GetBuffer()) + 4;
	isEoF = FALSE;
	isError = FALSE;
	counter = 0;
	return buffer0.GetBuffer();
}
void _NETWORK_API TPacket::SetPacket(unsigned int len) {
	if ( len <= buffer0.GetLength() ) {
		lBufferLength = len / 4;
	} else {
		lBufferLength = buffer0.GetLength() / 4;
	}
	if ( buffer0.GetLength() >= 4 ) {
		unsigned char *buf = (unsigned char*)buffer0.GetBuffer();
		flag = buf[0];
		actualBufferLength = 0x00FFFFFF & ( ( buf[1] << 16 ) | ( buf[2] << 8 ) | buf[3] ); 
		isError = FALSE;
		if ( actualBufferLength > (buffer0.GetLength() - 4) ) {
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
BOOL32 _NETWORK_API TPacket::IsEncrypted() {
	if ( ( ( flag & 0x1 ) == FALSE ) && ( lBufferLength >= 1 ) ) {
		pointer = ((unsigned char *)buffer0.GetBuffer()) + 4;
		isBuffer0Valid = TRUE;
		isBufferValid = TRUE;
	}
	return (BOOL32)(flag & 0x1);
}
void _NETWORK_API TPacket::CopyBuffer() {
	if ( buffer0.GetLength() > 0 ) {
		if ( buffer1.GetLength() < buffer0.GetLength() ) {
			buffer1.Resize(buffer0.GetLength());
		}
		unsigned int *cbuf0 = (unsigned int *)buffer0.GetBuffer();
		unsigned int *cbuf1 = (unsigned int *)buffer1.GetBuffer();
		for ( unsigned int i1 = 0 ; i1 < lBufferLength ; i1 ++ ) {
			cbuf1[i1] = cbuf0[i1];
		}
	}
}
void _NETWORK_API TPacket::Decrypt0() {
	if ( lBufferLength >= 3 ) {
		pointer = ((unsigned char *)buffer0.GetBuffer()) + 4;
		unsigned int cl = lBufferLength - 1;
		if ( crypter0 != NULL ) {
			crypter0->Decrypt(pointer, cl);
			isBuffer0Valid = TRUE;
			isBufferValid = TRUE;
		}
	}
	flag &= 0xFE;
}
void _NETWORK_API TPacket::Decrypt1() {
	if ( lBufferLength >= 3 ) {
		pointer = ((unsigned char *)buffer1.GetBuffer()) + 4;
		unsigned int cl = lBufferLength - 1;
		if ( crypter1 != NULL ) {
			crypter1->Decrypt(pointer, cl);
			isBuffer1Valid = TRUE;
			isBufferValid = TRUE;
		}
	}
	flag &= 0xFE;
}
//	Write
void _NETWORK_API TPacket::Reset(unsigned int len) {
	if ( len < 4 ) len = 4;
	lBufferLength = ( len - 1 ) / 4 + 1;
	len = lBufferLength * 4;
	buffer0.Resize(len);
	buffer1.Resize(len);
	actualBufferLength = len;
	isBuffer0Valid = FALSE;
	isBuffer1Valid = FALSE;
	isBufferValid = FALSE;
	flag = 0;
	pointer = ((unsigned char *)buffer0.GetBuffer()) + 4;
	isEoF = FALSE;
	isError = FALSE;
	counter = 0;
}
void _NETWORK_API TPacket::SetPacket() {
	actualBufferLength = counter;
	if ( buffer0.GetLength() >= 4 ) {
		unsigned char *buf = (unsigned char *)buffer0.GetBuffer();
		buf[0] = flag;
		buf[1] = (unsigned char)(actualBufferLength << 16);
		buf[2] = (unsigned char)(actualBufferLength << 8);
		buf[3] = (unsigned char)actualBufferLength;
	}
	lBufferLength = ( counter - 1 ) / 4 + 1;
	if ( buffer0.GetLength() < ( lBufferLength * 4 ) ) {
		buffer0.Resize(lBufferLength * 4);
		pointer = ((unsigned char *)buffer0.GetBuffer()) + 4;
	}
}

void _NETWORK_API TPacket::Encrypt0() {
	if ( lBufferLength >= 3 ) {
		pointer = ((unsigned char *)buffer0.GetBuffer()) + 4;
		unsigned int cl = lBufferLength - 1;
		if ( crypter0 != NULL ) {
			crypter0->Encrypt(pointer, cl);
		}
		unsigned char *buf = (unsigned char *)buffer0.GetBuffer();
		buf[0] = flag;
	}
	flag |= 0x01;
}
void _NETWORK_API TPacket::Encrypt1() {
	if ( lBufferLength >= 3 ) {
		pointer = ((unsigned char *)buffer0.GetBuffer()) + 4;
		unsigned int cl = lBufferLength - 1;
		if ( crypter1 != NULL ) {
			crypter1->Encrypt(pointer, cl);
		}
		unsigned char *buf = (unsigned char *)buffer1.GetBuffer();
		buf[0] = flag;
	}
	flag |= 0x01;
}

void _NETWORK_API *TPacket::GetBuffer(BOOL32 isZero, unsigned int &pl) {
	pl = lBufferLength * 4;
	if ( isZero ) {
		return (void*)buffer0.GetBuffer();
	} else {
		return (void*)buffer1.GetBuffer();
	}
}

BOOL32 _NETWORK_API TPacket::Open() {
	switch (accessMode) {
		case TPacket::modeRead | TPacket::typeBinary :
			break;
		case TPacket::modeWrite | TPacket::typeBinary :
			break;
		case TPacket::modeReadWrite | TPacket::typeBinary :
			break;
		case TPacket::modeCreate | TPacket::typeBinary :
			break;
		case TPacket::modeRead | TPacket::typeText :
			break;
		case TPacket::modeWrite | TPacket::typeText :
			break;
		case TPacket::modeReadWrite | TPacket::typeText :
			break;
		case TPacket::modeCreate | TPacket::typeText :
			break;
		default:
			return FALSE;
	}
	return TRUE;
}

void _NETWORK_API TPacket::Close() {
}
void _NETWORK_API TPacket::SetEndian(unsigned int e) {
	if ( ( e == IIOStream::big_endian ) || ( e == IIOStream::little_endian ) ) {
		endian = e;
	} else {
		endian = IIOStream::little_endian;
	}
	if ( flag & 0x1 ) {
		if ( endian != LOCAL_MACHINE_ENDIAN ) {
			if ( buffer1.GetLength() < buffer0.GetLength() ) {
				buffer1.Resize(buffer0.GetLength());
			}
			unsigned int *ibuf0 = (unsigned int *)buffer0.GetBuffer();
			unsigned int *ibuf1 = (unsigned int *)buffer1.GetBuffer();
			unsigned int llen = lBufferLength;
			for ( unsigned int i1 = 1 ; i1 < lBufferLength ; i1 ++ ) {
				MemoryCopy(&(ibuf1[i1]), &(ibuf0[i1]), 4, TRUE);
				MemoryCopy(&(ibuf0[i1]), &(ibuf1[i1]), 4, FALSE);
			}
		}
	}
	flag = ( flag & 0xFD ) | ( endian << 1 );
}
unsigned int _NETWORK_API TPacket::GetEndian() {
	endian = ( flag & 0xFD ) >> 1;
	return endian;
}
void _NETWORK_API TPacket::SetLoadStore(unsigned int ls) {
	if ( ( ls == TPacket::load ) || ( ls == TPacket::store ) ) {
		loadstoreType = ls;
	} else {
		loadstoreType = TPacket::load;
	}
}
unsigned int _NETWORK_API TPacket::GetLoadStore() {
	return loadstoreType;
}

void _NETWORK_API TPacket::MemoryCopy(void *dest, const void *src, unsigned int length, BOOL32 swapendian) {
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

void _NETWORK_API TPacket::MemoryCopy(void *dest, const void *src, unsigned int length) {
	BOOL32 isswap = ( endian != LOCAL_MACHINE_ENDIAN ) ;
	MemoryCopy (dest, src, length, isswap);
}

unsigned int _NETWORK_API TPacket::Read(const void* buf, const unsigned int length) {
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
unsigned int _NETWORK_API TPacket::Write(const void* buf, const unsigned int length) {
	if ( (counter + length) <= actualBufferLength ) {
		MemoryCopy ( &(pointer[counter]), buf, length );
		counter += length;
		return TRUE;
	}
	isError = TRUE;
	return FALSE;
}
unsigned int _NETWORK_API TPacket::ReadBuffer(const void* buf, const unsigned int cells, const unsigned int celllength) {
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
unsigned int _NETWORK_API TPacket::WriteBuffer(const void* buf, const unsigned int cells, const unsigned int celllength) {
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
unsigned int _NETWORK_API TPacket::Seek(unsigned int length) {
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
unsigned int _NETWORK_API TPacket::Seek(unsigned int begin, unsigned int length) {
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
BOOL32 _NETWORK_API TPacket::IsEoF() {
	return isEoF;
}

unsigned int _NETWORK_API TPacket::GetPosition() {
	return counter;
}

char _NETWORK_API *TPacket::GetClassName() {
	return "TPacket";
}
int _NETWORK_API TPacket::GetClassCode() {
	return CLSID_TPacket;
}
int _NETWORK_API TPacket::GetHashCode() {
	return 1;
}
BOOL32 _NETWORK_API TPacket::IsInstanceof(const char* className) {
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
BOOL32 _NETWORK_API TPacket::IsEqualto(IObject &obj) {
	return FALSE;
}
void _NETWORK_API TPacket::Serialize(IIOStream &iio) {
}
void _NETWORK_API TPacket::Wait() {
}
void _NETWORK_API TPacket::Notify() {
}


void _NETWORK_API TPacket::Flush() {
}
	
void _NETWORK_API TPacket::SetOpenMode(unsigned int mode) {
	accessMode = mode;
}

int _NETWORK_API TPacket::GetLength() {
	return actualBufferLength;
}
