///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "../MGE_Base/Base.h"

extern "C" class MGETextureData : public MGEObject {
public:
	MGETextureData();
	virtual ~MGETextureData();
public:
	unsigned short	width;	// width in pixels
	unsigned short	height;	// height in pixels
	unsigned char	colordeepth;
	void *buffer;
public:
	virtual void Set(unsigned short width, unsigned short height, unsigned char colordeepth, void *buffer);
	virtual void Get(unsigned short &width, unsigned short &height, unsigned char &colordeepth, void *&buffer);
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};


#endif