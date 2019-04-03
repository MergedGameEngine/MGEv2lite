///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _TGATEXTURE_H_
#define _TGATEXTURE_H_

#include "../MGE_Base/Base.h"
#include "Texture.h"

extern "C" class MGETGATexture : public MGETextureData {
public:
	MGETGATexture();
	virtual ~MGETGATexture();
public:
	unsigned char	identsize;				// Size of ID field that follows header (0)
	unsigned char	colorMapType;			// 0 = None, 1 = paletted
	unsigned char	imageType;				// 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
	unsigned short	colorMapStart;			// First colour map entry
	unsigned short	colorMapLength;			// Number of colors
	unsigned char 	colorMapBits;			// bits per palette entry
	unsigned short	xstart;					// image x origin
	unsigned short	ystart;					// image y origin
	unsigned char	bits;					// bits per pixel (8 16, 24, 32)
	unsigned char	descriptor;				// image descriptor
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
	void Serialize(MGEIOStream &iio);
};


#endif