///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _FILE_EXPORT

#include "FileStream.h"
#include "string.h"

MGEFileStream::MGEFileStream() {
	__file = NULL;
}
MGEFileStream::MGEFileStream(MGEFile *f) {
	__file = f;
}

MGEFileStream::~MGEFileStream() {
}

void MGEFileStream::SetFile(MGEFile *f) {
	__file = f;
}


BOOL32 MGEFileStream::Open() {
	if ( __file != NULL ) {
		return __file->Open();
	} else {
		return FALSE;
	}
}
void MGEFileStream::Close() {
	if ( __file != NULL ) {
///		__file->Close();
		__file = NULL;
	}
}
void MGEFileStream::SetEndian(unsigned int e) {
	if ( ( e == MGEFileStream::big_endian ) || ( e == MGEFileStream::little_endian ) ) {
		endian = e;
	} else {
		endian = MGEFileStream::big_endian;
	}
}
unsigned int MGEFileStream::GetEndian() {
	return endian;
}
void MGEFileStream::SetLoadStore(unsigned int ls) {
	if ( ( ls == MGEFileStream::load ) || ( ls == MGEFileStream::store ) ) {
		loadstoreType = ls;
	} else {
		loadstoreType = MGEFileStream::load;
	}
}
unsigned int MGEFileStream::GetLoadStore() {
	return loadstoreType;
}

void MGEFileStream::swapEndian(const void* buffer, unsigned int length) {
	unsigned char* buf = (unsigned char*)buffer;
	unsigned char temp;
	int l = length / 2;
	for (int i = 0 ; i < l ; i ++ ) {
		temp = buf[i];
		buf[i] = buf[length - i - 1];
		buf[length - i - 1] = temp;
	}
}

unsigned int MGEFileStream::Read(const void* buf, const unsigned int length) {
	if ( __file == NULL ) { return 0xFFFFFFFF;}
	int retcode = (int)__file->Read(buf, length, 1);
	if (endian != _LOCAL_ENDIAN_) {
		swapEndian(buf, length);
	}
	return retcode;
}
unsigned int MGEFileStream::Write(const void* buf, const unsigned int length) {
	if ( __file == NULL ) { return 0xFFFFFFFF;}
	if (endian != _LOCAL_ENDIAN_) {
		swapEndian(buf, length);
	}
	return (int)__file->Write(buf, length, 1);
}
unsigned int MGEFileStream::ReadBuffer(const void* buf, const unsigned int cells, const unsigned int celllength) {
	if ( __file == NULL ) { return 0xFFFFFFFF;}
	int retcode = __file->Read(buf, celllength, cells);
	if (endian != _LOCAL_ENDIAN_) {
		unsigned char * pBuf = (unsigned char * )buf;
		for ( unsigned int i = 0 ; i < cells ; i ++ ) {
			swapEndian(&(pBuf[celllength * i]), celllength);
		}
	}
	return retcode;
}
unsigned int MGEFileStream::WriteBuffer(const void* buf, const unsigned int cells, const unsigned int celllength) {
	if ( __file == NULL ) { return 0xFFFFFFFF;}
	if (endian != _LOCAL_ENDIAN_) {
		unsigned char * pBuf = (unsigned char * )buf;
		for ( unsigned int i = 0 ; i < cells ; i ++ ) {
			swapEndian(&(pBuf[celllength * i]), celllength);
		}
	}
	return __file->Write(buf, celllength, cells);
}
unsigned int MGEFileStream::Seek(unsigned int length) {
	if ( __file == NULL ) { return 0xFFFFFFFF;}
	return (int)__file->Seek(length, MGEFile::seek_cur);
}
unsigned int MGEFileStream::Seek(unsigned int begin, unsigned int length) {
	if ( __file == NULL ) { return 0xFFFFFFFF;}
	__file->Seek(begin, MGEFile::seek_set);
	return (int)__file->Seek(length, MGEFile::seek_cur);
}
BOOL32 MGEFileStream::IsEoF() {
	if ( __file == NULL ) { return TRUE;}
	return (BOOL32)__file->IsEof();
}

unsigned int MGEFileStream::GetPosition() {
	if ( __file == NULL ) { return 0xFFFFFFFF;}
	return __file->GetPosition();
}

const char *MGEFileStream::GetClassName() {
	return "MGEFileStream";
}

BOOL32 MGEFileStream::IsInstanceof(const char* className) {
	if ( strcmp("MGEFileStream", className) == 0 ) {
		return TRUE;
	}
	return FALSE;
}
