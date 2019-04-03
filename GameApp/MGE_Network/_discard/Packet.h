///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _PACKET_H_
#define _PACKET_H_

#include "../MGE_Base/Base.h"
#include "Blowfish.h"

#ifndef LOCAL_MACHINE_ENDIAN
#define LOCAL_MACHINE_ENDIAN MGEIOStream::little_endian
#endif

extern "C" template class MGEDataArray<unsigned char>;

extern "C" class MGEPacket : public MGEIOStream {
public:
	MGEPacket();
	virtual ~MGEPacket();
private:
	unsigned int accessMode;
	BOOL32 isError;

protected:
	unsigned int loadstoreType;

private:
	void MemoryCopy(void *dest, const void *src, unsigned int length, BOOL32 swapendian);
	void MemoryCopy(void *dest, const void *src, unsigned int length);
	void SwapEndian(void *src, unsigned int cells, unsigned int celllength);

protected:
	unsigned int endian;
	unsigned int actualBufferLength;
	unsigned int totalBufferLength;
	BOOL32 isBufferValid;
	MGEDataArray<unsigned char> buffer;//Max=16.7M
	Blowfish *crypter0;
	Blowfish *crypter1;
	unsigned char flag;
	unsigned char *pointer;
	unsigned int counter;
	BOOL32 isEoF;
public:
	void SetCrypter0(Blowfish &cpy0);
	void SetCrypter1(Blowfish &cpy1);
	//	Read
	const void *Fill(unsigned int len);
	void SetPacket(unsigned int len);
	BOOL32 IsEncrypted();
	void Decrypt0();
	void Decrypt1();
	//	Write
	void Reset(unsigned int len);
	void SetPacket();
	void Encrypt0();
	void Encrypt1();
	void *GetBuffer(unsigned int &pl); 
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
	virtual BOOL32 IsEqualto(MGEObject &obj);
	virtual void Serialize(MGEIOStream &iio);

public:
	void Flush();
	void SetOpenMode(unsigned int mode);
	int GetLength();
};

#endif