///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_EXPORT

#ifndef WIN32
#include "wchar.h"
#endif
#include "Type.h"
#include "Base.h"
#include "stdio.h"
#include "string.h"
#include "stdarg.h"
#include "CRC32.h"


MGETString::MGETString() {
	buffer = NULL;
	length = 0;
	___this = this;
}

MGETString::~MGETString() {
	if (___this == this) {
		if ( buffer ) {
			delete []buffer;
		}
	} else if ( ___this == 0 ) {
	} else {
		buffer = NULL;
		___this = NULL;
	}
}

MGETString::MGETString(const char* asciiStr) {
	___this = this;
	if (asciiStr!=NULL) {
		int len = 0;
		int i = 0 ;
		for ( i = 0 ; i < 65536 ; i ++ ) {
			if ( (asciiStr[i]<0x1) || (asciiStr[i]>0x7E) ) {
				len = i;
				break;
			}
		}
		buffer = new unsigned short[len + 1];
		for ( i = 0 ; i < len ; i ++ ) {
			buffer[i] = asciiStr[i];
		}
		buffer[len] = 0;
		length = len;
	} else {
		buffer = NULL;
		length = 0;
	}
}

MGETString::MGETString(const wchar_t* wstr) {
	___this = this;
	if (wstr!=NULL) {
		int len = 0;
		int i;
		for ( i = 0 ; i <65536 ; i ++ ) {
			if (wstr[i] == 0) {
				len = i;
				break;
			}
		}
		buffer = new unsigned short[len + 1];
		for ( i = 0 ; i < len ; i ++ ) {
			buffer[i] = (unsigned short)wstr[i];
		}
		buffer[len] = 0;
		length = len;
	} else {
		buffer = NULL;
		length = 0;
	}
}

MGETString::MGETString(const unsigned short* wstr) {
	___this = this;
	if (wstr!=NULL) {
		int len = 0;
		int i;
		for ( i = 0 ; i <65536 ; i ++ ) {
			if (wstr[i] == 0) {
				len = i;
				break;
			}
		}
		buffer = new unsigned short[len + 1];
		for ( i = 0 ; i < len ; i ++ ) {
			buffer[i] = (unsigned short)wstr[i];
		}
		buffer[len] = 0;
		length = len;
	} else {
		buffer = new unsigned short[1];
		buffer[0] = 0;
		length = 0;
	}
}

MGETString::MGETString(const unsigned long* wstr) {
	___this = this;
	if (wstr!=NULL) {
		int len = 0;
		int i;
		for ( i = 0 ; i <65536 ; i ++ ) {
			if (wstr[i] == 0) {
				len = i;
				break;
			}
		}
		buffer = new unsigned short[len + 1];
		for ( i = 0 ; i < len ; i ++ ) {
			buffer[i] = (unsigned short)wstr[i];
		}
		buffer[len] = 0;
		length = len;
	} else {
		buffer = new unsigned short[1];
		buffer[0] = 0;
		length = 0;
	}
}

MGETString::MGETString(char* fmt, ...) {
#ifdef WIN32
	char		*argptr;    
	int			cnt;

	char *buffer0 = new char[65536];

	argptr = (char *)&fmt;
	argptr += sizeof(char *);
	cnt = vsprintf(buffer0,fmt,argptr);

	length = strlen(buffer0);
	unsigned short *buf0 = new unsigned short[length + 1];
	unsigned int _i1;
	for ( _i1 = 0 ; _i1 < length ; _i1 ++ ) {
		buf0[_i1] = (unsigned short)buffer0[_i1];
	}
	buf0[length] = 0;
	delete []buffer0;
	buffer = buf0;

	___this = this;
#else
	va_list		argptr;    
	int			cnt;

	char *buffer0 = new char[65536];

	va_start(argptr, fmt);
	cnt = vsprintf(buffer0,fmt,argptr);    

	length = strlen(buffer0);
	unsigned short *buf0 = new unsigned short[length + 1];
	unsigned int _i1;
	for ( _i1 = 0 ; _i1 < length ; _i1 ++ ) {
		buf0[_i1] = (unsigned short)buffer0[_i1];
	}
	buf0[length] = 0;
	delete []buffer0;
	buffer = buf0;

	___this = this;	
#endif
}


MGETString MGETString::operator + (const MGETString &src) {
	const unsigned short *srcBuffer = src.buffer;
	unsigned short *descBuffer = new unsigned short[length + src.length + 1];
	memcpy(descBuffer, buffer, length * sizeof(unsigned short));
	unsigned short *mpDescBuffer = &(descBuffer[length]);
	memcpy(mpDescBuffer, src.buffer, (src.length + 1) * sizeof(unsigned short));
	MGETString desc(descBuffer);
	desc.___this = 0;
	delete []descBuffer;
	if ( ___this == 0 ) {
		if ( buffer ) {
			delete []buffer;
			buffer = NULL;
		}
	}
	return desc;
}

MGETString &MGETString::operator = (const MGETString& src) {
	if ( ___this == 0 ) {
		___this = this;
	}
	if ( ___this != this ) {
		buffer = new unsigned short[___this->length + 1];
		memcpy (buffer, ___this->buffer, (___this->length + 1) * sizeof(unsigned short));
		length = ___this->length;
		___this = this;
	}
	if (this != &src) {
		if ( buffer ) {
			delete []buffer;
		}
		if (src.___this == 0) {
			buffer = src.buffer;
		} else {
			buffer = new unsigned short[src.length + 1];
			memcpy (buffer, src.buffer, (src.length + 1) * sizeof(unsigned short));
		}
		length = src.length;
	}
	___this = this;
	return *this;
}

MGETString &MGETString::operator += (const MGETString& src) {
	if ( ___this != this ) {
		buffer = new unsigned short[___this->length + 1];
		memcpy (buffer, ___this->buffer, (___this->length + 1) * sizeof(unsigned short));
		length = ___this->length;
		___this = this;
	}
	const unsigned short *srcBuffer = src.buffer;
	unsigned short *descBuffer = new unsigned short[length + src.length + 1];
	memcpy(descBuffer, buffer, length * sizeof(unsigned short));
	unsigned short *mpDescBuffer = &(descBuffer[length]);
	memcpy(mpDescBuffer, src.buffer, (src.length + 1) * sizeof(unsigned short));
	if ( buffer ) {
		delete []buffer;
	}
	buffer = descBuffer;
	length += src.length;
	___this = this;
	if ( src.___this == 0 ) {
		if ( src.buffer ) {
			delete []src.buffer;
			(MGETString&)src.buffer = NULL;
		}
	}
	return *this;
}

BOOL32 MGETString::operator == (const MGETString &src) {
	return Equals(src);
}

BOOL32 MGETString::Equals(const MGETString &src) {
	if (src.length != length) {
		return FALSE;
	}
	const unsigned short *srcBuffer = src.buffer;
	for ( unsigned int i = 0 ; i < length ; i ++ ) {
		if (buffer[i] != srcBuffer[i]) {
			return FALSE;
		}
	}
	return TRUE;
}



MGETString MGETString::operator + (const wchar_t *src) {
	int _len = -1;
	if ( src ) {
		_len = wcslen(src);
	} else {
		_len = 0;
	}
	if ( _len <= 0 ) {
		_len = 0;
		if ( buffer ) {
			MGETString desc0(buffer);
			desc0.___this = 0;
			if ( ___this == 0 ) {
				if ( buffer ) {
					delete []buffer;
					buffer = NULL;
				}
			}
			return desc0;
		} else {
			MGETString desc1(L"");
			desc1.___this = 0;
			if ( ___this == 0 ) {
				if ( buffer ) {
					delete []buffer;
					buffer = NULL;
				}
			}
			return desc1;
		}
	}
	MGETString __src(src);
	MGETString desc;
	desc = (*this) + __src;
	desc.___this = 0;
	if ( ___this == 0 ) {
		if ( buffer ) {
			delete []buffer;
			buffer = NULL;
		}
	}
	return desc;
}

MGETString &MGETString::operator = (const wchar_t *src) {
	if ( src ) {
		length = wcslen(src);
	} else {
		src = 0;
	}
	if ( ___this == this ) {
		if ( buffer ) {
			delete []buffer;
			buffer = NULL;
		}
	} else {
		___this = this;
	}

	if ( length > 0 ) {
		buffer = new unsigned short[length + 1];
		unsigned int cnt = 0;
		for ( cnt = 0 ; cnt < length ; cnt ++ ) {
			buffer[cnt] = (unsigned short)src[cnt];
		}
		buffer[length] = 0;
	} else {
		buffer = NULL;
		length = 0;
	}

	return *this;
}

MGETString &MGETString::operator += (const wchar_t *src) {
	if ( ___this != this ) {
		buffer = new unsigned short[___this->length + 1];
		memcpy (buffer, ___this->buffer, (___this->length + 1) * sizeof(unsigned short));
		length = ___this->length;
		___this = this;
	}
	int _len = wcslen(src);
	char *descBuffer = 0;
	if ( _len > 0 ) {
		(*this) += MGETString(src);
	} else {
	}
	___this = this;
	return *this;
}


BOOL32 MGETString::operator == (const wchar_t *src) {
	MGETString src0(src);
	return Equals(src0);
}
	






const unsigned short *MGETString::GetBuffer() {
	return buffer;
}

unsigned int MGETString::GetLength() {
	return length;
}

unsigned int MGETString::GetWString(wchar_t *desc) {
	unsigned int i = 0;
	for ( i = 0 ; i < length ; i ++ ) {
		desc[i] = (wchar_t)buffer[i];
	}
	desc[i] = 0;
	return i;
}

const char *MGETString::GetClassName() {
	return "MGETString";

}

int MGETString::GetHashCode() {
	return (int)CRC32::GetCRC32(buffer, length * sizeof(unsigned short));
}
	
BOOL32 MGETString::IsInstanceof(const char* className) {
	if (strcmp("MGETString", className)) {
		return TRUE;
	}
	return FALSE;
}
	
BOOL32 MGETString::IsEqualto(MGEObject &obj) {
	if (obj.IsInstanceof("MGETString")) {
		MGETString& str = (MGETString&)obj;
		if (str.GetLength() != length) {
			return FALSE;
		}
		const unsigned short *strBuffer = str.GetBuffer();
		for ( unsigned int i = 0 ; i < length ; i ++ ) {
			if (buffer[i] != strBuffer[i]) {
				return FALSE;
			}
		}
		return TRUE;
	}
	return FALSE;
}

void MGETString::Serialize(MGEIOStream &iio) {
}
	

int MGETString::Read(MGEIOStream &iio, unsigned int count) {
	if ( count > 0 ) {
		if ( ___this == this ) {
			delete buffer;
		}
		buffer = new unsigned short[count + 1];
		length = count;
		buffer[length] = 0;
	} else {
		return -1;
	}
	return iio.ReadBuffer(buffer, count, sizeof(unsigned short)); 
}
int MGETString::Write(MGEIOStream &iio, unsigned int count) {
	if (count > 0) {
		return iio.WriteBuffer(buffer, count, sizeof(unsigned short)); 
	}
	return -1;
}
void MGETString::Load(MGEIOStream &iio) {
	unsigned int count = 0;
	iio.Read(&count, sizeof(unsigned int));
	Read(iio, count);
}
void MGETString::Store(MGEIOStream &iio) {
	iio.Write(&length, sizeof(unsigned int));
	Write(iio, length);
}

