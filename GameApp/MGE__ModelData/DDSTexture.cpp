///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _MODEL_EXPORT

#include "string.h"
//#include "..\Base\Type.h"
//#include "..\Base\Base.h"
#undef _ARRAY_API
#define _ARRAY_API _MODEL_API
#include "DDSTexture.hpp"


MGEDDSTexture::MGEDDSTexture() {
	buffer = NULL;
}

MGEDDSTexture::~MGEDDSTexture() {
	if ( buffer != NULL ) {
		delete []buffer;
		buffer = NULL;
	}
}

const char *MGEDDSTexture::GetClassName() {
	return "MGEDDSTexture";
}
BOOL32 MGEDDSTexture::IsInstanceof(const char* className) {
	if (strcmp("MGEDDSTexture", className) == 0) {
		return TRUE;
	}
	return FALSE;
}
void MGEDDSTexture::Serialize(MGEIOStream &iio) {
	if (iio.GetLoadStore() == MGEIOStream::load) {
		iio.Read(&magic, sizeof(unsigned int));
		if (magic == 0x20534444) {
			iio.SetEndian(MGEIOStream::little_endian);
		} else if (magic == 0x44445320) {
			iio.SetEndian(MGEIOStream::big_endian);
		} else {
			return;
		}
		iio.ReadBuffer(&dsize, 20, sizeof(unsigned int));
		iio.ReadBuffer(dxtcode, 4, sizeof(char));
		dxtcode[4] = 0;
		iio.ReadBuffer(&bitdepth, 10, sizeof(unsigned int));
		width = (unsigned short)iwidth;
		height = (unsigned short)iheight;
		colordeepth = (unsigned char)(bitdepth / 8);
		if (strcmp("DXT1", dxtcode) == 1) {
			compressformat = MGEDDSTexture::FORMAT_DXT1;
		} else if (strcmp("DXT2", dxtcode) == 1) {
			compressformat = MGEDDSTexture::FORMAT_DXT2;
		} else if (strcmp("DXT3", dxtcode) == 1) {
			compressformat = MGEDDSTexture::FORMAT_DXT3;
		} else if (strcmp("DXT4", dxtcode) == 1) {
			compressformat = MGEDDSTexture::FORMAT_DXT4;
		} else if (strcmp("DXT5", dxtcode) == 1) {
			compressformat = MGEDDSTexture::FORMAT_DXT5;
		} else {
			compressformat = MGEDDSTexture::FORMAT_UNCOMPRESSED;
		}
		unsigned int imagesize = width * height * colordeepth;
		if ( compressformat == MGEDDSTexture::FORMAT_UNCOMPRESSED ) {
			buffer = new unsigned char[imagesize];
			iio.ReadBuffer(buffer, imagesize, sizeof(unsigned char));
		} else {
			buffer = new unsigned char[linearsize];
			iio.ReadBuffer(buffer, linearsize / 2, sizeof(unsigned short));
		}
		return;
	}
	if (iio.GetLoadStore() == MGEIOStream::store) {
		iio.WriteBuffer("DDS ", 4, sizeof(char));
		iio.WriteBuffer(&dsize, 20, sizeof(uint32));
	}
}

void MGEDDSTexture::ConvertARGBtoRGBA(BOOL32 swapEndian) {
	if ( swapEndian ) {
		if ( colordeepth == 4 ) {
			unsigned int __rgb = 0;
			unsigned int __size = width * height;
			unsigned int __alpha = 0;
			unsigned int *_buf = (unsigned int*)buffer;
			for ( unsigned int i1 = 0 ; i1 < __size ; i1 ++ ) {
				__alpha = _buf[i1];
				__rgb = __alpha << 8;
				__alpha = __alpha >> 24;
				__rgb = (__rgb & 0xFFFFFF00) | (__alpha & 0x000000FF);
				unsigned char *__p = (unsigned char *)&__rgb;
				__alpha = __p[0];__p[0] = __p[3];__p[3] = (unsigned char)__alpha;
				__alpha = __p[1];__p[1] = __p[2];__p[2] = (unsigned char)__alpha;
				_buf[i1] = __rgb;
			}
			redmask		=	0xFF000000;	// mask for the red pixels (usually 0x00ff0000)
			greenmask	=	0x00FF0000;	// mask for the green pixels (usually 0x0000ff00)
			bluemask	=	0x0000FF00;	// mask for the blue pixels (usually 0x000000ff)
			alphamask	=	0x000000FF;	// mask for the alpha value in a pixel // (usually 0xff000000)
		}
	} else {
		if ( colordeepth == 4 ) {
			unsigned int __rgb = 0;
			unsigned int __size = width * height;
			unsigned int __alpha = 0;
			unsigned int *_buf = (unsigned int*)buffer;
			for ( unsigned int i1 = 0 ; i1 < __size ; i1 ++ ) {
				__alpha = _buf[i1];
				__rgb = __alpha << 8;
				__alpha = __alpha >> 24;
				_buf[i1] = (__rgb & 0xFFFFFF00) | (__alpha & 0x000000FF);
			}
			redmask		=	0xFF000000;	// mask for the red pixels (usually 0x00ff0000)
			greenmask	=	0x00FF0000;	// mask for the green pixels (usually 0x0000ff00)
			bluemask	=	0x0000FF00;	// mask for the blue pixels (usually 0x000000ff)
			alphamask	=	0x000000FF;	// mask for the alpha value in a pixel // (usually 0xff000000)
		}
	}
}
