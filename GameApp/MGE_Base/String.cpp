///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)	v2	Copyright 2018
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
//
//		string container
//		 Windows: local code
//		 Linux:UTF8
//
///////////////////////////////////////////////////////////////////



#include "stdio.h"
#include "string.h"
#include "stdarg.h"
#include "Type.h"
#include "Base.h"
#include "CRC32.h"

MGEObject::~MGEObject() {
}

MGEIOStream::~MGEIOStream() {
}

MGEString::MGEString() {
	buffer = NULL;
	length = 0;
	___this = this;
}

MGEString::MGEString(int value) {
	buffer = new char[12];
	sprintf(buffer, "%d", value);
	length = strlen(buffer);
	___this = this;
}

MGEString::MGEString(unsigned int value) {
	buffer = new char[12];
	sprintf(buffer, "%u", value);
	length = strlen(buffer);
	___this = this;
}

MGEString::MGEString(long long value) {
	buffer = new char[26];
	sprintf(buffer, "%lld", value);
	length = strlen(buffer);
	___this = this;
}

MGEString::MGEString(unsigned long long value) {
	buffer = new char[26];
	sprintf(buffer, "%llu", value);
	length = strlen(buffer);
	___this = this;
}

MGEString::MGEString(float value) {
	buffer = new char[26];
	sprintf(buffer, "%f", value);
	length = strlen(buffer);
	___this = this;
}

MGEString::MGEString(double value) {
	buffer = new char[26];
	sprintf(buffer, "%f", value);
	length = strlen(buffer);
	___this = this;
}


MGEString::~MGEString() {
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

MGEString::MGEString(const char* asciiStr) {
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
		buffer = new char[len + 1];
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

MGEString::MGEString(char* fmt, ...) {
#ifdef WIN32
	char		*argptr;    
	int			cnt;

	buffer = new char[65536];

	argptr = (char *)&fmt;
	argptr += sizeof(char *);
	cnt = vsprintf(buffer,fmt,argptr);    

	length = strlen(buffer);
	char *buf0 = new char[length + 1];
	memcpy(buf0, buffer, (length + 1) * sizeof(char));
	delete []buffer;
	buffer = buf0;

	___this = this;
#else
	va_list		argptr;    
	int			cnt;

	buffer = new char[65536];

//	argptr = (va_list)&fmt;
//	argptr += sizeof(char *);
	va_start(argptr, fmt);
	cnt = vsprintf(buffer,fmt,argptr);    

	length = strlen(buffer);
	char *buf0 = new char[length + 1];
	memcpy(buf0, buffer, (length + 1) * sizeof(char));
	delete []buffer;
	buffer = buf0;

	___this = this;
	
#endif

}


MGEString MGEString::operator + (const MGEString &src) {
	const char *srcBuffer = src.buffer;
	char *descBuffer = new char[length + src.length + 1];
	memcpy(descBuffer, buffer, length * sizeof(char));
	char *mpDescBuffer = &(descBuffer[length]);
	memcpy(mpDescBuffer, src.buffer, (src.length + 1) * sizeof(char));
	MGEString desc(descBuffer);
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

MGEString &MGEString::operator = (const MGEString& src) {
	if ( ___this == 0 ) {
		___this = this;
	}
	if ( ___this != this ) {
		buffer = new char[___this->length + 1];
		memcpy (buffer, ___this->buffer, (___this->length + 1) * sizeof(char));
		length = ___this->length;
		___this = this;
	}
	if (this != &src) {
		if ( buffer != NULL ) {
			delete []buffer;
		}
		if (src.___this == 0) {
			buffer = src.buffer;
		} else {
			if ( src.buffer != NULL ) {
				buffer = new char[src.length + 1];
				memcpy (buffer, src.buffer, (src.length + 1) * sizeof(char));
			} else {
				buffer = NULL;
				length = 0;
			}
		}
		length = src.length;
	}
	___this = this;
	return *this;
}

MGEString &MGEString::operator += (const MGEString& src) {
	if ( ___this != this ) {
		buffer = new char[___this->length + 1];
		memcpy (buffer, ___this->buffer, (___this->length + 1) * sizeof(char));
		length = ___this->length;
		___this = this;
	}
	const char *srcBuffer = src.buffer;
	char *descBuffer = new char[length + src.length + 1];
	memcpy(descBuffer, buffer, length * sizeof(char));
	char *mpDescBuffer = &(descBuffer[length]);
	memcpy(mpDescBuffer, src.buffer, (src.length + 1) * sizeof(char));
	if ( buffer ) {
		delete []buffer;
	}
	buffer = descBuffer;
	length += src.length;
	___this = this;
	if ( src.___this == 0 ) {
		if ( src.buffer ) {
			delete []src.buffer;
			(MGEString&)src.buffer = NULL;
		}
	}
	return *this;
}

BOOL32 MGEString::operator == (const MGEString &src) {
	return Equals(src);
}



BOOL32 MGEString::Equals(const MGEString &src) {
	if (src.length != length) {
		return FALSE;
	}
	const char *srcBuffer = src.buffer;
	for ( unsigned int i = 0 ; i < length ; i ++ ) {
		if (buffer[i] != srcBuffer[i]) {
			return FALSE;
		}
	}
	return TRUE;
}
	


MGEString MGEString::operator + (const char *src) {
	int _len = -1;
	if ( src ) {
		_len = strlen(src);
	} else {
		_len = 0;
	}
	if ( _len <= 0 ) {
		_len = 0;
		if ( buffer ) {
			MGEString desc0(buffer);
			desc0.___this = 0;
			if ( ___this == 0 ) {
				if ( buffer ) {
					delete []buffer;
					buffer = NULL;
				}
			}
			return desc0;
		} else {
			MGEString desc1("");
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
	char *descBuffer = new char[length + _len + 1];
	memcpy(descBuffer, buffer, length * sizeof(char));
	char *mpDescBuffer = &(descBuffer[length]);
	memcpy(mpDescBuffer, src, (_len + 1) * sizeof(char));
	MGEString desc(descBuffer);
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

MGEString &MGEString::operator = (const char *src) {
	if ( src ) {
		length = strlen(src);
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
		buffer = new char[length + 1];
		memcpy (buffer, src, (length + 1) * sizeof(char));
	} else {
		buffer = NULL;
		length = 0;
	}

	return *this;
}

MGEString &MGEString::operator += (const char *src) {
	if ( ___this != this ) {
		buffer = new char[___this->length + 1];
		memcpy (buffer, ___this->buffer, (___this->length + 1) * sizeof(char));
		length = ___this->length;
		___this = this;
	}
	int _len = strlen(src);
	char *descBuffer = 0;
	if ( _len > 0 ) {
		descBuffer = new char[length + _len + 1];
		memcpy(descBuffer, buffer, length * sizeof(char));
		char *mpDescBuffer = &(descBuffer[length]);
		memcpy(mpDescBuffer, src, (_len + 1) * sizeof(char));
		if ( buffer ) {
			delete []buffer;
			buffer = NULL;
		}
		buffer = descBuffer;
		length += _len;
	} else {
	}
	___this = this;
	return *this;
}


BOOL32 MGEString::operator == (const char *src) {
	MGEString src0(src);
	return Equals(src0);
}
	
const char *MGEString::GetBuffer() {
	return buffer;
}

unsigned int MGEString::GetLength() {
	return length;
}

char *MGEString::GetStringASC() {
	char *desc = new char[length + 1];
	for ( unsigned int i = 0 ; i < length ; i ++ ) {
		if ( (buffer[i]<0x0020) || (buffer[i]>0x007E) ) {
			break;
		} else {
			desc[i] = (char)buffer[i];
		}
	}
	desc[length] = 0;
	return desc;
}

unsigned int MGEString::GetStringASC(char *desc) {
	unsigned int i = 0;
	for ( i = 0 ; i < length ; i ++ ) {
		if ( (buffer[i]<0x0020) || (buffer[i]>0x007E) ) {
			break;
		} else {
			desc[i] = (char)buffer[i];
		}
	}
	desc[i] = 0;
	return i;
}

const char *MGEString::GetClassName() {
	return "MGEString";

}

int MGEString::GetHashCode() {
	return (int)CRC32::GetCRC32(buffer, length * sizeof(char));
}
	
BOOL32 MGEString::IsInstanceof(const char* className) {
	if (strcmp("MGEString", className)) {
		return TRUE;
	}
	return FALSE;
}
	
BOOL32 MGEString::IsEqualto(MGEObject &obj) {
	if (obj.IsInstanceof("MGEString")) {
		MGEString& str = (MGEString&)obj;
		if (str.GetLength() != length) {
			return FALSE;
		}
		const char *strBuffer = str.GetBuffer();
		for ( unsigned int i = 0 ; i < length ; i ++ ) {
			if (buffer[i] != strBuffer[i]) {
				return FALSE;
			}
		}
		return TRUE;
	}
	return FALSE;
}

void MGEString::Serialize(MGEIOStream &iio) {
}
	

int MGEString::Read(MGEIOStream &iio, unsigned int count) {
	if ( count > 0 ) {
		if ( ___this == this ) {
			delete buffer;
		}
		buffer = new char[count + 1];
		length = count;
		buffer[length] = 0;
	} else {
		return -1;
	}
	return iio.ReadBuffer(buffer, count, sizeof(char)); 
}
int MGEString::Write(MGEIOStream &iio, unsigned int count) {
	if (count > 0) {
		return iio.WriteBuffer(buffer, count, sizeof(char)); 
	}
	return -1;
}
void MGEString::Load(MGEIOStream &iio) {
	unsigned int count = 0;
	iio.Read(&count, sizeof(unsigned int));
	Read(iio, count);
}
void MGEString::Store(MGEIOStream &iio) {
	iio.Write(&length, sizeof(unsigned int));
	Write(iio, length);
}


int MGEString::Format(MGEString formats, ...) {
#ifdef WIN32
	char		*argptr;    
	int			cnt;

	if ( ___this == this ) {
		delete []buffer;
	}
	buffer = new char[65536];

	argptr = (char *)&formats;
	argptr += sizeof(MGEString);
	cnt = vsprintf(buffer,formats.GetBuffer(),argptr);    

#else
	
	va_list		argptr;    
	int			cnt;

	if ( ___this == this ) {
		delete []buffer;
	}
	buffer = new char[65536];

	char *fmt = (char *)&formats;
	fmt += sizeof(MGEString);
	fmt -= sizeof(char*);
	//argptr = (char *)&formats;
	//argptr += sizeof(MGEString);
	va_start(argptr, fmt);
	cnt = vsprintf(buffer,formats.GetBuffer(),argptr);    
#endif

	length = strlen(buffer);
	char *buf0 = new char[length + 1];
	memcpy(buf0, buffer, (length + 1) * sizeof(char));
	delete []buffer;
	buffer = buf0;

	return cnt;    
}
