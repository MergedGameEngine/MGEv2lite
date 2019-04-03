///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _FILE_EXPORT

#include "../MGE_Base/Type.h"
#include "File.h"
#ifdef WIN32
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#endif
#include "stdio.h"
#include "string.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	ATTENTION:
//		FILE API(LIBC) conflicts with memory API(malloc,new), OpenGL, etc 
//		Linux system API instead
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MGEFile::MGEFile() {
#ifdef WIN32
	___file = NULL;
#endif
	fd = 0;
	accessMode = MGEFile::modeRead;
	filePathName = NULL;
	isError = TRUE;
	isEoF = TRUE;
}
MGEFile::~MGEFile() {
#ifdef WIN32
	if (___file != NULL) {
		fclose((FILE*)___file);
		___file = NULL;
	}
#else
	if (fd != 0) {
		close(fd);
		fd = 0;
	}
#endif
	if ( filePathName != NULL ) {
		delete filePathName;
		filePathName = NULL;
	}
}

BOOL32 MGEFile::Open() {
	if (filePathName == NULL) {
		return FALSE;
	}
#ifdef WIN32
	switch (accessMode) {
		case MGEFile::modeRead | MGEFile::typeBinary :
			 fopen_s((FILE**)&___file, filePathName, "rb+");
			break;
		case MGEFile::modeWrite | MGEFile::typeBinary :
			fopen_s((FILE**)&___file, filePathName, "wb");
			break;
		case MGEFile::modeReadWrite | MGEFile::typeBinary :
			fopen_s((FILE**)&___file, filePathName, "r+b");
			break;
		case MGEFile::modeCreate | MGEFile::typeBinary :
			fopen_s((FILE**)&___file, filePathName, "w+b");
			break;
		case MGEFile::modeRead | MGEFile::typeText :
			fopen_s((FILE**)&___file, filePathName, "rt");
			break;
		case MGEFile::modeWrite | MGEFile::typeText :
			fopen_s((FILE**)&___file, filePathName, "wt");
			break;
		case MGEFile::modeReadWrite | MGEFile::typeText :
			fopen_s((FILE**)&___file, filePathName, "r+t");
			break;
		case MGEFile::modeCreate | MGEFile::typeText :
			fopen_s((FILE**)&___file, filePathName, "w+t");
			break;
		default:
			return FALSE;
	}
	if (___file == NULL) {
		isError = TRUE;
		return FALSE;
	} else {
		isError = FALSE;
	}
#else
	switch (accessMode) {
		case MGEFile::modeRead | MGEFile::typeBinary :
			fd = open(filePathName, O_RDONLY, S_IRUSR | S_IWUSR);
			break;
		case MGEFile::modeWrite | MGEFile::typeBinary :
			fd = open(filePathName, O_WRONLY, S_IRUSR | S_IWUSR);
			break;
		case MGEFile::modeReadWrite | MGEFile::typeBinary :
			fd = open(filePathName, O_RDWR, S_IRUSR | S_IWUSR);
			break;
		case MGEFile::modeCreate | MGEFile::typeBinary :
			fd = open(filePathName, O_CREAT|O_RDWR, S_IRUSR | S_IWUSR);
			break;
		case MGEFile::modeRead | MGEFile::typeText :
			fd = open(filePathName, O_RDONLY, S_IRUSR | S_IWUSR);
			break;
		case MGEFile::modeWrite | MGEFile::typeText :
			fd = open(filePathName, O_WRONLY, S_IRUSR | S_IWUSR);
			break;
		case MGEFile::modeReadWrite | MGEFile::typeText :
			fd = open(filePathName, O_RDWR, S_IRUSR | S_IWUSR);
			break;
		case MGEFile::modeCreate | MGEFile::typeText :
			fd = open(filePathName, O_CREAT|O_RDWR, S_IRUSR | S_IWUSR);
			break;
		default:
			return FALSE;
	}
	if (fd == 0) {
		isError = TRUE;
		return FALSE;
	} else {
		isError = FALSE;
		isEoF = FALSE;
	}
#endif
	return TRUE;
}

void MGEFile::Close() {
#ifdef WIN32
	if ( ___file == NULL ) {
		return;
	}
	if (fclose((FILE*)___file) == 0) {
		isError = FALSE;
	} else {
		___file = NULL;
		isError = TRUE;
	}
#else
	if ( fd == 0 ) {
		return;
	}
	if (close(fd) == 0) {
		fd = 0;
		isError = FALSE;
	} else {
		fd = 0;
		isError = TRUE;
	}
#endif
	if ( filePathName != NULL ) {
		delete filePathName;
		filePathName = NULL;
	}
}

BOOL32 MGEFile::Seek(unsigned int offset, unsigned int type) {
#ifdef WIN32
	if (fseek((FILE*)___file, offset, type) == 0) {
		isError = FALSE;
		return TRUE;
	} else {
		isError = TRUE;
		return FALSE;
	}
#else
	if (lseek(fd, offset, type) == 0) {
		isError = FALSE;
		return TRUE;
	} else {
		isError = TRUE;
		return FALSE;
	}
#endif
}

BOOL32 MGEFile::IsEof() {
#ifdef WIN32
	if ( feof((FILE*)___file) ) {
		return TRUE;
	} else {
		return FALSE;
	}
#else
	return isEoF;
#endif
}

BOOL32 MGEFile::IsError() {
	return isError;
}

void MGEFile::Rewind() {
#ifdef WIN32		
	rewind((FILE*)___file);
#else
#endif
}

unsigned int MGEFile::Read(const void *buffer, const unsigned int celllength, const unsigned int cells) {
	///printf("fread buffer=[0x%016lX], cl=[%d], nc=[%d], file=[0x%016lX]\n", (unsigned long)buffer, celllength, cells, (unsigned long)___file);
#ifdef WIN32
	return fread((void*)buffer, celllength, cells, (FILE*)___file);
#else
	int _ret = (int)read(fd, (void*)buffer, celllength * cells);
	if ( _ret <= 0 ) {
		isEoF = TRUE;
		return 0;
	}
	return (unsigned int)_ret;
#endif
}

unsigned int MGEFile::Write(const void *buffer, const unsigned int celllength, const unsigned int cells) {
#ifdef WIN32
	return fwrite(buffer, celllength, cells, (FILE*)___file);
#else
	return (unsigned int)write(fd, buffer, celllength * cells);
#endif
}

void MGEFile::Flush() {
#ifdef WIN32		
	fflush((FILE*)___file);
#else
#endif
}
	
void MGEFile::GetFileName(const char* fileName) {
}
void MGEFile::GetFilePath(const char* filePath) {
}
void MGEFile::GetFileTitle(const char* fileTitle) {
}

void MGEFile::SetFilePathName(const char* fileName) {
	if (fileName != NULL ) {
		filePathName = new char[strlen(fileName) + 1];
		strcpy(filePathName, fileName);
	}
}

void MGEFile::SetOpenMode(unsigned int mode) {
	accessMode = mode;
}

int MGEFile::GetLength() {
#ifdef WIN32		
	if ( ___file!= NULL ) {
		return ((FILE*)___file)->_bufsiz;
	}
	return 0;
#else
	return (int)lseek(fd, 0, SEEK_END);
#endif
}
int MGEFile::GetPosition() {
#ifdef WIN32		
	return (int)ftell((FILE*)___file);
#else
	return (int)lseek(fd, 0, SEEK_CUR);
#endif
}

