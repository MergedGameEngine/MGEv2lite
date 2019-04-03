///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _DDSTEXTURE_H_
#define _DDSTEXTURE_H_


#include "../MGE_Base/Base.h"
#include "Texture.h"

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned int uint;

struct RGBA {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;
};

struct RGB {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

extern "C" class MGEDDSTexture : public MGETextureData {
public:
	MGEDDSTexture();
	virtual ~MGEDDSTexture();
public:
	
	enum {
		// Flags for Header
		DDSD_CAPS			= 0x00000001,
		DDSD_HEIGHT			= 0x00000002,
		DDSD_WIDTH			= 0x00000004,
		DDSD_PITCH			= 0x00000010,
		DDSD_PIXELFORMAT	= 0x00001000,
		DDSD_MIPMAPCOUNT	= 0x00020000,
		DDSD_LINEARSIZE		= 0x00080000,
		DDSD_DEPTH			= 0x00800000,

		// Flags for Pixelformats
		DDPF_ALPHAPIXEL		= 0x00000001,
		DDPF_FOURCC			= 0x00000004,
		DDPF_RGB			= 0x00000040,
		DDPF_LUMINANCE		= 0x00020000,

		// Flags for complex caps
		DDSCAPS_COMPLEX		= 0x00000008,
		DDSCAPS_TEXTURE		= 0x00001000,
		DDSCAPS_MIPMAP		= 0x00400000,

		// Flags for cubemaps
		DDSCAPS2_CUBEMAP			= 0x00000200,
		DDSCAPS2_CUBEMAP_POSITIVEX	= 0x00000400,
		DDSCAPS2_CUBEMAP_NEGATIVEX	= 0x00000800,
		DDSCAPS2_CUBEMAP_POSITIVEY	= 0x00001000,
		DDSCAPS2_CUBEMAP_NEGATIVEY	= 0x00002000,
		DDSCAPS2_CUBEMAP_POSITIVEZ	= 0x00004000,
		DDSCAPS2_CUBEMAP_NEGATIVEZ	= 0x00008000,
		DDSCAPS2_VOLUME				= 0x00200000
	};
	
	enum {
		FORMAT_UNCOMPRESSED	= 0,
		FORMAT_DXT1		= 1,
		FORMAT_DXT2		= 2,
		FORMAT_DXT3		= 3,
		FORMAT_DXT4		= 4,
		FORMAT_DXT5		= 5
	};
private:
public:
	//
	unsigned int magic;		// Magic Number (has to be "DDS "
	unsigned int dsize;		// Size of the descriptor structure (should be 124)
	unsigned int flags;		// flags field
	unsigned int iheight;
	unsigned int iwidth;
	unsigned int linearsize;
	unsigned int depth;		// for volume textures: depth the FLAG_DEPTH flag // should be set in this case
	unsigned int mipmapcount;		// number of mipmap levels included. flags // should include FLAG_MIPMAPCOUNT in this case
	unsigned int alphabitdepth;		// depth of alpha buffer
	unsigned int reserved[10];
	//

	unsigned int _size;		// size of this structure (should be 32)
	unsigned int _flags;	// flags which values are present here
	char dxtcode[5];		// character code for image format
	unsigned int bitdepth;	// number of bits per pixel (usually 16,24 or 32)
	unsigned int redmask;	// mask for the red pixels (usually 0x00ff0000)
	unsigned int greenmask;	// mask for the green pixels (usually 0x0000ff00)
	unsigned int bluemask;	// mask for the blue pixels (usually 0x000000ff)
	unsigned int alphamask;	// mask for the alpha value in a pixel // (usually 0xff000000)
	//

	unsigned int caps1;
	unsigned int caps2;
	unsigned int _reserved[2];
	//

	unsigned int reserved001;

	unsigned char compressformat;

public:
public:
	/*
	BOOL32 ProbeDXT1Alpha (const uint8* source, int w, int h, int depth);
	void DecompressDXT1 (Color8888* buffer, const uint8* source,
		int w, int h, int depth, int planesize);
	void DecompressDXT2 (Color8888* buffer, const uint8* source,
		int w, int h, int depth, int planesize);
	void DecompressDXT3 (Color8888* buffer, const uint8* source,
		int w, int h, int depth, int planesize);
	void DecompressDXT4 (Color8888* buffer, const uint8* source,    
		int w, int h, int depth, int planesize);
	void DecompressDXT5 (Color8888* buffer, const uint8* source,
		int w, int h, int depth, int planesize);
	void DecompressRGB (Color8888* buffer, const uint8* source,
		int w, int h, int depth, const DDSPixelFormat& pf);
	void DecompressRGBA (Color8888* buffer, const uint8* source,
		int w, int h, int depth, const DDSPixelFormat& pf);
	void DecompressLum (Color8888* buffer, const uint8* source,
		int w, int h, int depth, const DDSPixelFormat& pf);
		*/
private:
	/*
	static void CorrectPremult (Color8888* buffer, int pixnum);
	*/
public:
	void ConvertARGBtoRGBA(BOOL32 swapEndian);
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
	void Serialize(MGEIOStream &iio);
};


#endif