///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _CRC32_H_
#define _CRC32_H_

#include "Type.h"

extern "C" class CRC32 {
public:
	CRC32();
	virtual ~CRC32();
public:
	static unsigned int GetCRC32(void *buffer, unsigned int len);
	static unsigned int GetCRC32SwapEndian(void *buf, unsigned int len);

private:
	static unsigned int crc32_tab[];
};

#endif