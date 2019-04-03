///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _FILE_H_
#define _FILE_H_

#include "../MGE_Base/Base.h"

extern "C" class MGEFile {
public:
	MGEFile();
	virtual ~MGEFile();
private:
#ifdef WIN32
	void *___file;///4 Windows
#endif
	int fd;///4 Linux
	char *filePathName;
	unsigned int accessMode;
	BOOL32 isError;
	BOOL32 isEoF;
public:
	enum { 
		modeRead = 0x01,
		modeWrite = 0x10,
		modeReadWrite = 0x11,
		modeCreate = 0x00,
		typeText = 0x00010000,
		typeBinary = 0x00000000
	};

	enum {
		seek_set = 0x0,
		seek_cur = 0x1,
		seek_end = 0x2,
	};

public:
	BOOL32 Open(); 
	void Close(); 
	BOOL32 Seek(unsigned int offset, unsigned int type); 
	BOOL32 IsEof(); 
	BOOL32 IsError(); 
	void Rewind(); 
	unsigned int Read(const void *buffer, const unsigned int celllength, const unsigned int cells); 
	unsigned int Write(const void *buffer, const unsigned int celllength, const unsigned int cells); 
	void Flush();
	
	void GetFileName(const char* fileName);
	void GetFilePath(const char* filePath);
	void GetFileTitle(const char* fileTitle);

	void SetFilePathName(const char* fileName);
	void SetOpenMode(unsigned int mode);

	int GetLength();
	int GetPosition();
};

#endif