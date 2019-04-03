///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _FILEIOSTREAM_H_
#define _FILEIOSTREAM_H_

#include "../MGE_Base/Base.h"
#include "File.h"

extern "C" class MGEFileStream : public MGEIOStream {
public:
	MGEFileStream();
	MGEFileStream(MGEFile *file);
	virtual ~MGEFileStream();
public:
	void SetFile(MGEFile *file);
private:
	MGEFile *__file;
	unsigned int endian;
	unsigned int loadstoreType;

private:
	void swapEndian(const void* buffer, unsigned int length);

public:
public:
	virtual BOOL32 Open();
	virtual void Close();
	virtual void SetEndian(unsigned int endian);
	virtual unsigned int GetEndian();
	virtual void SetLoadStore(unsigned int loadstore);
	virtual unsigned int GetLoadStore();
	virtual unsigned int Read(const void* buf, const unsigned int length);
	virtual unsigned int Write(const void* buf, const unsigned int length);
	virtual unsigned int ReadBuffer(const void* buf, const unsigned int cells, const unsigned int celllength);
	virtual unsigned int WriteBuffer(const void* buf, const unsigned int cells, const unsigned int celllength);
	virtual unsigned int Seek(unsigned int length);
	virtual unsigned int Seek(unsigned int begin, unsigned int length);
	virtual unsigned int GetPosition();
	virtual BOOL32 IsEoF();

	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};

#endif
