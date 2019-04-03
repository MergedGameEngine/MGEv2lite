///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)	v2	Copyright 2018
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


MGEWString::MGEWString() {
	buffer = NULL;
	length = 0;
	___this = this;
}

MGEWString::~MGEWString() {
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

MGEWString::MGEWString(const char* asciiStr) {
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
		buffer = new unsigned int[len + 1];
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

MGEWString::MGEWString(const wchar_t* wstr) {
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
		buffer = new unsigned int[len + 1];
		for ( i = 0 ; i < len ; i ++ ) {
			buffer[i] = (unsigned int)wstr[i];
		}
		buffer[len] = 0;
		length = len;
	} else {
		buffer = NULL;
		length = 0;
	}
}

MGEWString::MGEWString(const unsigned int* wstr) {
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
		buffer = new unsigned int[len + 1];
		for ( i = 0 ; i < len ; i ++ ) {
			buffer[i] = (unsigned int)wstr[i];
		}
		buffer[len] = 0;
		length = len;
	} else {
		buffer = new unsigned int[1];
		buffer[0] = 0;
		length = 0;
	}
}

MGEWString::MGEWString(const unsigned short* wstr) {
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
		buffer = new unsigned int[len + 1];
		for ( i = 0 ; i < len ; i ++ ) {
			buffer[i] = (unsigned int)wstr[i];
			buffer[i] &= 0x0000FFFF;
		}
		buffer[len] = 0;
		length = len;
	} else {
		buffer = new unsigned int[1];
		buffer[0] = 0;
		length = 0;
	}
}

MGEWString::MGEWString(char* fmt, ...) {
#ifdef WIN32
	char		*argptr;    
	int			cnt;

	char *buffer0 = new char[65536];

	argptr = (char *)&fmt;
	argptr += sizeof(char *);
	cnt = vsprintf(buffer0,fmt,argptr);

	length = strlen(buffer0);
	unsigned int *buf0 = new unsigned int[length + 1];
	unsigned int _i1;
	for ( _i1 = 0 ; _i1 < length ; _i1 ++ ) {
		buf0[_i1] = (unsigned int)buffer0[_i1];
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
	unsigned int *buf0 = new unsigned int[length + 1];
	unsigned int _i1;
	for ( _i1 = 0 ; _i1 < length ; _i1 ++ ) {
		buf0[_i1] = (unsigned int)buffer0[_i1];
	}
	buf0[length] = 0;
	delete []buffer0;
	buffer = buf0;

	___this = this;	
#endif
}


MGEWString MGEWString::operator + (const MGEWString &src) {
	const unsigned int *srcBuffer = src.buffer;
	unsigned int *descBuffer = new unsigned int[length + src.length + 1];
	memcpy(descBuffer, buffer, length * sizeof(unsigned int));
	unsigned int *mpDescBuffer = &(descBuffer[length]);
	memcpy(mpDescBuffer, src.buffer, (src.length + 1) * sizeof(unsigned int));
	MGEWString desc(descBuffer);
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

MGEWString &MGEWString::operator = (const MGEWString& src) {
	if ( ___this == 0 ) {
		___this = this;
	}
	if ( ___this != this ) {
		buffer = new unsigned int[___this->length + 1];
		memcpy (buffer, ___this->buffer, (___this->length + 1) * sizeof(unsigned int));
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
			buffer = new unsigned int[src.length + 1];
			memcpy (buffer, src.buffer, (src.length + 1) * sizeof(unsigned int));
		}
		length = src.length;
	}
	___this = this;
	return *this;
}

MGEWString &MGEWString::operator += (const MGEWString& src) {
	if ( ___this != this ) {
		buffer = new unsigned int[___this->length + 1];
		memcpy (buffer, ___this->buffer, (___this->length + 1) * sizeof(unsigned int));
		length = ___this->length;
		___this = this;
	}
	const unsigned int *srcBuffer = src.buffer;
	unsigned int *descBuffer = new unsigned int[length + src.length + 1];
	memcpy(descBuffer, buffer, length * sizeof(unsigned int));
	unsigned int *mpDescBuffer = &(descBuffer[length]);
	memcpy(mpDescBuffer, src.buffer, (src.length + 1) * sizeof(unsigned int));
	if ( buffer ) {
		delete []buffer;
	}
	buffer = descBuffer;
	length += src.length;
	___this = this;
	if ( src.___this == 0 ) {
		if ( src.buffer ) {
			delete []src.buffer;
			(MGEWString&)src.buffer = NULL;
		}
	}
	return *this;
}

BOOL32 MGEWString::operator == (const MGEWString &src) {
	return Equals(src);
}

BOOL32 MGEWString::Equals(const MGEWString &src) {
	if (src.length != length) {
		return FALSE;
	}
	const unsigned int *srcBuffer = src.buffer;
	for ( unsigned int i = 0 ; i < length ; i ++ ) {
		if (buffer[i] != srcBuffer[i]) {
			return FALSE;
		}
	}
	return TRUE;
}



MGEWString MGEWString::operator + (const wchar_t *src) {
	int _len = -1;
	if ( src ) {
		_len = wcslen(src);
	} else {
		_len = 0;
	}
	if ( _len <= 0 ) {
		_len = 0;
		if ( buffer ) {
			MGEWString desc0(buffer);
			desc0.___this = 0;
			if ( ___this == 0 ) {
				if ( buffer ) {
					delete []buffer;
					buffer = NULL;
				}
			}
			return desc0;
		} else {
			MGEWString desc1(L"");
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
	MGEWString __src(src);
	MGEWString desc;
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

MGEWString &MGEWString::operator = (const wchar_t *src) {
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
		buffer = new unsigned int[length + 1];
		unsigned int cnt = 0;
		for ( cnt = 0 ; cnt < length ; cnt ++ ) {
			buffer[cnt] = (unsigned int)src[cnt];
		}
		buffer[length] = 0;
	} else {
		buffer = NULL;
		length = 0;
	}

	return *this;
}

MGEWString &MGEWString::operator += (const wchar_t *src) {
	if ( ___this != this ) {
		buffer = new unsigned int[___this->length + 1];
		memcpy (buffer, ___this->buffer, (___this->length + 1) * sizeof(unsigned int));
		length = ___this->length;
		___this = this;
	}
	int _len = wcslen(src);
	char *descBuffer = 0;
	if ( _len > 0 ) {
		(*this) += MGEWString(src);
	} else {
	}
	___this = this;
	return *this;
}


BOOL32 MGEWString::operator == (const wchar_t *src) {
	MGEWString src0(src);
	return Equals(src0);
}
	






const unsigned int *MGEWString::GetBuffer() {
	return buffer;
}

unsigned int MGEWString::GetLength() {
	return length;
}

unsigned int MGEWString::GetWString(wchar_t *desc) {
	unsigned int i = 0;
	for ( i = 0 ; i < length ; i ++ ) {
		desc[i] = (wchar_t)buffer[i];
	}
	desc[i] = 0;
	return i;
}

const char *MGEWString::GetClassName() {
	return "MGEWString";

}

int MGEWString::GetHashCode() {
	return (int)CRC32::GetCRC32(buffer, length * sizeof(unsigned int));
}
	
BOOL32 MGEWString::IsInstanceof(const char* className) {
	if (strcmp("MGEWString", className)) {
		return TRUE;
	}
	return FALSE;
}
	
BOOL32 MGEWString::IsEqualto(MGEObject &obj) {
	if (obj.IsInstanceof("MGEWString")) {
		MGEWString& str = (MGEWString&)obj;
		if (str.GetLength() != length) {
			return FALSE;
		}
		const unsigned int *strBuffer = str.GetBuffer();
		for ( unsigned int i = 0 ; i < length ; i ++ ) {
			if (buffer[i] != strBuffer[i]) {
				return FALSE;
			}
		}
		return TRUE;
	}
	return FALSE;
}

void MGEWString::Serialize(MGEIOStream &iio) {
}
	

int MGEWString::Read(MGEIOStream &iio, unsigned int count) {
	if ( count > 0 ) {
		if ( ___this == this ) {
			delete buffer;
		}
		buffer = new unsigned int[count + 1];
		length = count;
		buffer[length] = 0;
	} else {
		return -1;
	}
	return iio.ReadBuffer(buffer, count, sizeof(unsigned int)); 
}
int MGEWString::Write(MGEIOStream &iio, unsigned int count) {
	if (count > 0) {
		return iio.WriteBuffer(buffer, count, sizeof(unsigned int)); 
	}
	return -1;
}
void MGEWString::Load(MGEIOStream &iio) {
	unsigned int count = 0;
	iio.Read(&count, sizeof(unsigned int));
	Read(iio, count);
}
void MGEWString::Store(MGEIOStream &iio) {
	iio.Write(&length, sizeof(unsigned int));
	Write(iio, length);
}

