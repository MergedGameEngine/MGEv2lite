#ifndef _PACKET_H_
#define _PACKET_H_

#include "..\Base\Base.h"
#include "Blowfish.h"

#ifndef LOCAL_MACHINE_ENDIAN
#define LOCAL_MACHINE_ENDIAN IIOStream::little_endian
#endif

extern "C" template class _BASE_API TArray<unsigned char>;

extern "C" class _NETWORK_API TPacket : public IIOStream {
public:
	TPacket();
	virtual ~TPacket();
private:
	unsigned int accessMode;
	BOOL32 isError;

protected:
	unsigned int loadstoreType;

private:
	void MemoryCopy(void *dest, const void *src, unsigned int length, BOOL32 swapendian);
	void MemoryCopy(void *dest, const void *src, unsigned int length);

protected:
	unsigned int endian;
	unsigned int actualBufferLength;
	unsigned int lBufferLength;
	BOOL32 isBuffer0Valid;
	BOOL32 isBuffer1Valid;
	BOOL32 isBufferValid;
	TArray<unsigned char> buffer0;//Max=16.7M
	TArray<unsigned char> buffer1;
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
	void CopyBuffer();
	void Decrypt0();
	void Decrypt1();
	//	Write
	void Reset(unsigned int len);
	void SetPacket();
	void Encrypt0();
	void Encrypt1();
	void *GetBuffer(BOOL32 isZero, unsigned int &pl); 
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

	virtual char* GetClassName();
	virtual int GetClassCode();
	virtual int GetHashCode();
	virtual BOOL32 IsInstanceof(const char* className);
	virtual BOOL32 IsEqualto(IObject &obj);
	virtual void Serialize(IIOStream &iio);
	virtual void Wait();
	virtual void Notify();

public:
	void Flush();
	void SetOpenMode(unsigned int mode);
	int GetLength();
};

#endif